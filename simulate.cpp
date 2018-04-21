/**
    CSCI-453 Computer Architecture
    simulate.cpp
    
    Primary execution loop for the z88 architecture.

    @author Stephen Allan <swa9846>
 */


#include "includes.h"


/**
    Fetch, decode, and execute all instructions found in the object file.

    @param objectFile The strictly formatted file containing execution instructions
 */
void simulate(char* objectFile)
{
    // Load the object files
    im.load(objectFile);
    dm.load(objectFile);


    // Testing Packet
    Packet packet1;
    cout << packet1.ir;


    // Set the entry point
    // r7.latchFrom(memory.READ());
    // Clock::tick();

    // Continue fetching, decoding, and executing instructions until we stop the simulation
    // while (!done)
    // {
    //     // Fetch instruction into the mdr
    //     fetch(r7, mdr, abus);
    //     long currentPC = r7.value();

    //     // Increment program counter for next instruction
    //     r7.perform(Counter::incr2);
    //     Clock::tick();

    //     // Decode and execute
    //     execute(opCodeFunctions, currentPC);

    //     if (unalignedMemoryError) { displayUnalignedMemoryError(); }
    // }
}

/**
    Decode and execute the instruction in the instruction register.
    
    @param opCodeFunction Functions handling varying opcode lengths
    @param currentPC The count of the currently executing instruction
 */
void execute(long currentPC)
{
    // TODO: Giant switch

    
    // for (int i = 0; i < 6; ++i)
    // {
    //     if (opCodeFunctions[i](currentPC)) { return; }
    // }

    // // Unknown Operation Code
    // displayRecord(currentPC, mdr.value(), "????");
    
    // cout << endl << "Machine Halted - opcode error" << endl;
    // done = true;
}
