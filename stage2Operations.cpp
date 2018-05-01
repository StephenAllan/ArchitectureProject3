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

    //ifidRegister.fetchAddress = pc.value();
    // Transfer data using buses
    ifidRegister.v.set();
}

/**
    TODO: Documentation
 */
void instructionDecodeStage2()
{
    if (ifidRegister.v.value() == 0) { return; }

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

    // Advance data in pipeline registers
    memVBus.IN().pullFrom(exmemRegister.v);
    memPcBus.IN().pullFrom(exmemRegister.pc);
    memIrBus.IN().pullFrom(exmemRegister.ir);
    memwbRegister.v.latchFrom(memVBus.OUT());
    memwbRegister.pc.latchFrom(memPcBus.OUT());
    memwbRegister.ir.latchFrom(memIrBus.OUT());
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
