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
    idexRegister.v.latchFrom(idVBus.OUT());
    idPcBus.IN().pullFrom(ifidRegister.pc);
    idexRegister.pc.latchFrom(idPcBus.OUT());
    idNpcBus.IN().pullFrom(ifidRegister.npc);
    idexRegister.npc.latchFrom(idNpcBus.OUT());
    idIrBus.IN().pullFrom(ifidRegister.ir);
    idexRegister.ir.latchFrom(idIrBus.OUT());
}

/**
    TODO: Documentation
 */
void executeStage2()
{
    if (idexRegister.v.value() == 0) { return; }

    // Advance data in pipeline registers
    exVBus.IN().pullFrom(idexRegister.v);
    exPcBus.IN().pullFrom(idexRegister.pc);
    exIrBus.IN().pullFrom(idexRegister.ir);
    exmemRegister.v.latchFrom(exVBus.OUT());
    exmemRegister.pc.latchFrom(exPcBus.OUT());
    exmemRegister.ir.latchFrom(exIrBus.OUT());
}

/**
    TODO: Documentation
 */
void memoryAccessStage2()
{
    if (exmemRegister.v.value() == 0) { return; }
    
    memVBus.IN().pullFrom(exmemRegister.v);
    memwbRegister.v.latchFrom(memVBus.OUT());
    memPcBus.IN().pullFrom(exmemRegister.pc);
    memwbRegister.pc.latchFrom(memPcBus.OUT());
    memNpcBus.IN().pullFrom(exmemRegister.npc);
    memwbRegister.npc.latchFrom(memNpcBus.OUT());
    memIrBus.IN().pullFrom(exmemRegister.ir);
    memwbRegister.ir.latchFrom(memIrBus.OUT());
    memCBus.IN().pullFrom(exmemRegister.c);
    memwbRegister.c.latchFrom(memCBus.OUT());
}

/**
    TODO: Documentation
 */
void writeBackStage2()
{
    if (memwbRegister.v.value() == 0) { return; }

    // Print to console
    cout << memwbRegister.pc.value() << ":  " << memwbRegister.ir.value() << endl;
    if (memwbRegister.ir.value() == 0) {
        cout << "Machine Halted - HALT instruction executed";
        done = true;
    }
}
