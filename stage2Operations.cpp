/**
    CSCI-453 Computer Architecture
    stage2Operations.cpp
    
    Operations for the second clock tick of the z88 architecture.

    @author Stephen Allan <swa9846>
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

    //ifidRegister.fetchAddress = pc.value();
    // Transfer data using buses
}

/**
    TODO: Documentation
 */
void instructionDecodeStage2()
{
    if (ifidRegister.v.value() == 0) { return; }

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
    exmemRegister.instruction = idexRegister.instruction;
    exmemRegister.v.set();
}

/**
    TODO: Documentation
 */
void memoryAccessStage2()
{
    if (exmemRegister.v.value() == 0) { return; }
    memwbRegister.instruction = exmemRegister.instruction;
    memwbRegister.v.set();
}

/**
    TODO: Documentation
 */
void writeBackStage2()
{
    if (memwbRegister.v.value() == 0) { return; }

    done = true;
}
