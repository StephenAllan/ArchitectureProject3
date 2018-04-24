/**
    CSCI-453 Computer Architecture
    stage1Operations.cpp
    
    Setup operations for the first clock tick of the z88 architecture.

    @author Stephen Allan <swa9846>
 */


#include "includes.h"


/**
    TODO: Documentation
 */
void instructionFetchStage1()
{
    // Move address into MAR
    instructionBus.IN().pullFrom(pc);
    im.MAR().latchFrom(instructionBus.OUT());
}

/**
    TODO: Documentation
 */
void instructionDecodeStage1()
{
    // TODO: Implement Unknown Operation Code
    // displayRecord(currentPC, mdr.value(), "????");
    // cout << endl << "Machine Halted - opcode error" << endl;
    // done = true;
}

/**
    TODO: Documentation
 */
void executeStage1()
{

}

/**
    TODO: Documentation
 */
void memoryAccessStage1()
{

}

/**
    TODO: Documentation
 */
void writeBackStage1()
{

}
