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

    // Set the entry point
    pc.latchFrom(im.READ());
    Clock::tick();

    // Continue fetching, decoding, and executing instructions until we stop the simulation
    while (!done)
    {
        // The writeup discusses using a valid bit field in all of the pipeline registers to
        // indicate if there is valid data. The first thing each stage should do is check if the
        // valid bit is set or not. If not, then the stage does nothing.
        instructionFetchStage1();
        instructionDecodeStage1();
        executeStage1();
        memoryAccessStage1();
        writeBackStage1();

        Clock::tick();

        instructionFetchStage2();
        instructionDecodeStage2();
        executeStage2();
        memoryAccessStage2();
        writeBackStage2();
        
        Clock::tick();

        // Just stop if 0 for testing
        if (ir.value() == 0)
        {
            done = true;
        }

        // Debug printing
        cout << pc << endl;
        cout << ir << endl;
        cout << endl;
    }
}
