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

    // If we are moving values into pipeline registers that are not within ArchLib,
    // they have to be moved during the second clock tick or the new value will be over written too soon.
    long opcode = ir(31, 26);
    if (opcode == 0 || opcode == 1) {
        idexRegister.instrType = R_TYPE;
    } else if (opcode == 2 || opcode == 3) {
        idexRegister.instrType = J_TYPE;
    } else {
        idexRegister.instrType = I_TYPE;
    }

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

    pc.latchFrom(pcAlu.OUT());
    ifidRegister.npc.latchFrom(pcAlu.OUT()); // also send incremented PC to pipeline register
}

/**
    TODO: Documentation
 */
void instructionDecodeStage2()
{
    // if (ifidRegister.v.value() == 0) { return; }

    // Probably need to do some modification to PC and ID/EX.NPC here if a branch was decoded

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
    // if (idexRegister.v.value() == 0) { return; }

    long opcode = idexRegister.ir(31, 26);
    long rt = idexRegister.ir(20, 16);

    switch (opcode)
    {
        case 35: // LW
            dm.read();
            generalRegisters[rt]->latchFrom(dm.READ());
            break;
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
}

/**
    TODO: Documentation
 */
void memoryAccessStage2()
{
    // if (exmemRegister.v.value() == 0) { return; }
    
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
}

/**
    TODO: Documentation
 */
void writeBackStage2()
{
    // if (memwbRegister.v.value() == 0) { return; }
}
