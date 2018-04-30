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

    ifidRegister.fetchAddress = pc.value();
    ifidRegister.v.set();

    // Increment program counter for next instruction
    pc.perform(Counter::incr4);
}

/**
    TODO: Documentation
 */
void instructionDecodeStage2()
{
    if (ifidRegister.v.value() == 0) { return; }
    idexRegister.fetchAddress = ifidRegister.fetchAddress;
    idexRegister.v.set();
}

/**
    TODO: Documentation
 */
void executeStage2()
{
    if (idexRegister.v.value() == 0) { return; }
    exmemRegister.instruction = idexRegister.instruction;
    exmemRegister.fetchAddress = idexRegister.fetchAddress;
    exmemRegister.v.set();
}

/**
    TODO: Documentation
 */
void memoryAccessStage2()
{
    if (exmemRegister.v.value() == 0) { return; }
    memwbRegister.instruction = exmemRegister.instruction;
    memwbRegister.fetchAddress = exmemRegister.fetchAddress;
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
