/**
    CSCI-453 Computer Architecture
    stage2Operations.cpp
    
    Operations for the second clock tick of the z88 architecture.

    @author Stephen Allan <swa9846>
    @author Thomas Andaloro <tra5374>
 */


#include "includes.h"


/**
    TODO: Documentation
 */
void instructionFetchStage2()
{
    // Read word from memory into destination
    im.read();
    ir.latchFrom(im.READ());

    idexRegister.instrType = ifidRegister.instrType;
    ifidRegister.v.set();

    // Move PC to pipeline register
    // This has to be done in the second stage so it gets copied to
    // the next register in the pipeline before getting overwritten
    pcBus.IN().pullFrom(pc);
    ifidRegister.pc.latchFrom(pcBus.OUT());

    // Increment PC by 4 for next instruction
    pcAlu.OP1().pullFrom(pc);
    pcAlu.OP2().pullFrom(pcIncr);
    pcAlu.perform(BusALU::op_add);

    if (ifidRegister.incrPc) {
        pc.latchFrom(pcAlu.OUT());
        ifidRegister.npc.latchFrom(pcAlu.OUT()); // also send incremented PC to pipeline register
    } else {
        jumpBus.IN().pullFrom(idexRegister.imm);
        pc.latchFrom(jumpBus.OUT());
        ifidRegister.npc.latchFrom(jumpBus.OUT());
        ifidRegister.incrPc = true;
    }
}

/**
    TODO: Documentation
 */
void instructionDecodeStage2()
{
    long opcode = ir(31, 26);
    long rs = ir(25, 21);
    long rt = ir(20, 16);

    // I originally had this in the execute stage
    // It was branching correctly, but printing too many NOPs after the branch instruction
    // I thought moving it to earlier in the pipeline would reduce the number of extra instructions executed
    // (This is the earliest we can execute it... we need the immediate value sign extended)
    // Unfortunatly, moving it here from execute1 actually made it execute more NOPs after the branch...
    // Not sure why.
    // But branching functionality works in the execute1 stage, just the displayed output isn't 100% correct.

    if (ifidRegister.v.value() == 0) { return; }

    if (opcode == 60) // BEQ
    {
        if (generalRegisters[rs]->value() == generalRegisters[rt]->value())
        {
            branchAlu.OP1().pullFrom(ifidRegister.pc);
            branchAlu.OP2().pullFrom(idexRegister.imm);
            branchAlu.perform(BusALU::op_add);
            pc.latchFrom(branchAlu.OUT());
            ifidRegister.pc.latchFrom(branchAlu.OUT());
        }
    }
    else if (opcode == 61) // BNE
    {
        if (generalRegisters[rs]->value() != generalRegisters[rt]->value())
        {
            branchAlu.OP1().pullFrom(ifidRegister.pc);
            branchAlu.OP2().pullFrom(idexRegister.imm);
            branchAlu.perform(BusALU::op_add);
            pc.latchFrom(branchAlu.OUT());
            ifidRegister.pc.latchFrom(branchAlu.OUT());
        }
    }

    // Send all of the previous pipeline register data to the next stage
    idVBus.IN().pullFrom(ifidRegister.v);
    idPcBus.IN().pullFrom(ifidRegister.pc);
    idNpcBus.IN().pullFrom(ifidRegister.npc);
    idIrBus.IN().pullFrom(ifidRegister.ir);
    idexRegister.v.latchFrom(idVBus.OUT());
    idexRegister.pc.latchFrom(idPcBus.OUT());
    idexRegister.npc.latchFrom(idNpcBus.OUT());
    idexRegister.ir.latchFrom(idIrBus.OUT());
}

/**
    TODO: Documentation
 */
void executeStage2()
{
    if (idexRegister.v.value() == 0) { return; }

    long opcode = idexRegister.ir(31, 26);
    long rt = idexRegister.ir(20, 16);

    if (rt > 0)
    {
        switch (opcode)
        {
            case 35: // LW
                dm.read();
                generalRegisters[rt]->latchFrom(dm.READ());
                break;
            case 43: // SW
                dm.WRITE().pullFrom((*generalRegisters[rt]));
                dm.write();
                break;
        }
    }

    // Advance data in pipeline registers
    exVBus.IN().pullFrom(idexRegister.v);
    exPcBus.IN().pullFrom(idexRegister.pc);
    exNpcBus.IN().pullFrom(idexRegister.npc);
    exIrBus.IN().pullFrom(idexRegister.ir);
    exABus.IN().pullFrom(idexRegister.a);
    exBBus.IN().pullFrom(idexRegister.b);
    exImmBus.IN().pullFrom(idexRegister.imm);
    exmemRegister.v.latchFrom(exVBus.OUT());
    exmemRegister.pc.latchFrom(exPcBus.OUT());
    exmemRegister.npc.latchFrom(exNpcBus.OUT());
    exmemRegister.ir.latchFrom(exIrBus.OUT());
    exmemRegister.a.latchFrom(exABus.OUT());
    exmemRegister.b.latchFrom(exBBus.OUT());
    exmemRegister.imm.latchFrom(exImmBus.OUT());

    exmemRegister.instrType = idexRegister.instrType;
    exmemRegister.modifiedRegister = idexRegister.modifiedRegister;
    idexRegister.modifiedRegister = -1;
}

/**
    TODO: Documentation
 */
void memoryAccessStage2()
{
    if (exmemRegister.v.value() == 0) { return; }
    
    memVBus.IN().pullFrom(exmemRegister.v);
    memPcBus.IN().pullFrom(exmemRegister.pc);
    memNpcBus.IN().pullFrom(exmemRegister.npc);
    memIrBus.IN().pullFrom(exmemRegister.ir);
    memABus.IN().pullFrom(exmemRegister.a);
    memBBus.IN().pullFrom(exmemRegister.b);
    memImmBus.IN().pullFrom(exmemRegister.imm);
    memCBus.IN().pullFrom(exmemRegister.c);
    memwbRegister.v.latchFrom(memVBus.OUT());
    memwbRegister.pc.latchFrom(memPcBus.OUT());
    memwbRegister.npc.latchFrom(memNpcBus.OUT());
    memwbRegister.ir.latchFrom(memIrBus.OUT());
    memwbRegister.a.latchFrom(memABus.OUT());
    memwbRegister.b.latchFrom(memBBus.OUT());
    memwbRegister.imm.latchFrom(memImmBus.OUT());
    memwbRegister.c.latchFrom(memCBus.OUT());

    memwbRegister.instrType = exmemRegister.instrType;
    memwbRegister.modifiedRegister = exmemRegister.modifiedRegister;
}

/**
    TODO: Documentation
 */
void writeBackStage2()
{
    if (memwbRegister.v.value() == 0) { return; }
}
