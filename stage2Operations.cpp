/**
    CSCI-453 Computer Architecture
    stage2Operations.cpp
    
    Operations for the second clock tick of the z88 architecture.

    @author Stephen Allan <swa9846>
    @author Thomas Andaloro <tra5374>
 */


#include "includes.h"


/**
    Perform the second half of the Instruction Fetch stage.
    - Read the instruction into the IR
    - Determine the next PC value
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

    if (jumping)
    {
        ifidRegister.npc.latchFrom(pcAlu.OUT());
        jumping = false;
        return;
    }

    if (ifidRegister.incrPc) {
        pc.latchFrom(pcAlu.OUT());
        ifidRegister.npc.latchFrom(pcAlu.OUT()); // also send incremented PC to pipeline register
    } else {
        jumpBus.IN().pullFrom(idexRegister.zeroExtImm);
        pc.latchFrom(jumpBus.OUT());
        ifidRegister.npc.latchFrom(jumpBus.OUT());
        ifidRegister.incrPc = true;
    }
}

/**
    Perform the second half of the Instruction Decode stage.
    - Determine if a jump/branch needs to be performed
 */
void instructionDecodeStage2()
{
    if (ifidRegister.v.value() == 0) { return; }

    long opcode = ir(31, 26);
    long rd = idexRegister.ir(15, 11);
    long funct = ir(5, 0);

    if (opcode == 0 && funct == 2) // JR
    {
        jumping = true;

        jumpBus.IN().pullFrom(idexRegister.a);
        pc.latchFrom(jumpBus.OUT());
    }
    else if (opcode == 0 && funct == 3) // JALR
    {
        jumping = true;

        jumpBus.IN().pullFrom(idexRegister.a);
        pc.latchFrom(jumpBus.OUT());

        exFuncAlu.OP1().pullFrom(idexRegister.npc);
        exFuncAlu.OP2().pullFrom(const_8);
        exFuncAlu.perform(BusALU::op_add);
        idexRegister.c.latchFrom(exFuncAlu.OUT());
        generalRegisters[31]->latchFrom(exFuncAlu.OUT());
        idexRegister.modifiedRegister = 31;
    }
    else if (opcode == 3) // JAL
    {
        exFuncAlu.OP1().pullFrom(idexRegister.npc);
        exFuncAlu.OP2().pullFrom(const_8);
        exFuncAlu.perform(BusALU::op_add);
        idexRegister.c.latchFrom(exFuncAlu.OUT());
        generalRegisters[31]->latchFrom(exFuncAlu.OUT());
        idexRegister.modifiedRegister = 31;
    }
    else if (opcode == 60) // BEQ
    {
        if (idexRegister.a.value() == idexRegister.b.value())
        {
            jumping = true;
            branchAlu.OP1().pullFrom(ifidRegister.npc);
            branchAlu.OP2().pullFrom(idexRegister.imm);
            branchAlu.perform(BusALU::op_add);
            pc.latchFrom(branchAlu.OUT());
        }
    }
    else if (opcode == 61) // BNE
    {
        if (idexRegister.a.value() != idexRegister.b.value())
        {
            jumping = true;
            branchAlu.OP1().pullFrom(ifidRegister.npc);
            branchAlu.OP2().pullFrom(idexRegister.imm);
            branchAlu.perform(BusALU::op_add);
            pc.latchFrom(branchAlu.OUT());
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
    Perform the second half of the execution stage.
 */
void executeStage2()
{
    if (idexRegister.v.value() == 0) { return; }

    // Advance data in pipeline registers
    exVBus.IN().pullFrom(idexRegister.v);
    exPcBus.IN().pullFrom(idexRegister.pc);
    exNpcBus.IN().pullFrom(idexRegister.npc);
    exIrBus.IN().pullFrom(idexRegister.ir);
    exABus.IN().pullFrom(idexRegister.a);
    exBBus.IN().pullFrom(idexRegister.b);
    exImmBus.IN().pullFrom(idexRegister.imm);
    exCBus.IN().pullFrom(idexRegister.c);
    exmemRegister.v.latchFrom(exVBus.OUT());
    exmemRegister.pc.latchFrom(exPcBus.OUT());
    exmemRegister.npc.latchFrom(exNpcBus.OUT());
    exmemRegister.ir.latchFrom(exIrBus.OUT());
    exmemRegister.a.latchFrom(exABus.OUT());
    exmemRegister.b.latchFrom(exBBus.OUT());
    exmemRegister.imm.latchFrom(exImmBus.OUT());
    exmemRegister.c.latchFrom(exCBus.OUT());

    exmemRegister.instrType = idexRegister.instrType;
    exmemRegister.modifiedRegister = idexRegister.modifiedRegister;
    idexRegister.modifiedRegister = -1;
}

/**
    Perform the second half of the Memory stage.
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
