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

    // Create IF/ID object here?
    // Need to add fetch address field to each object to propagate it through to the write-back stage for displaying

    // Increment program counter for next instruction
    pc.perform(Counter::incr4);
}

/**
    TODO: Documentation
 */
void instructionDecodeStage2()
{
    
}

/**
    TODO: Documentation
 */
void executeStage2()
{

}

/**
    TODO: Documentation
 */
void memoryAccessStage2()
{

}

/**
    TODO: Documentation
 */
void writeBackStage2()
{

}
