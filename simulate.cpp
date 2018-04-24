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


    // Testing pipeline register
    // IfIdRegister ifidRegister;
    // cout << ifidRegister.ir;


    // Set the entry point
    pc.latchFrom(im.READ());
    Clock::tick();

    int iteration = 0;

    // Continue fetching, decoding, and executing instructions until we stop the simulation
    while (!done)
    {
        // TODO: These switches may not be needed... Should the pipeline be able to handle itself being empty at start?
        switch (iteration)
        {
            default:
                writeBackStage1();
            case 3:
                memoryAccessStage1();
            case 2:
                executeStage1();
            case 1:
                instructionDecodeStage1();
            case 0:
                instructionFetchStage1();
        }
        Clock::tick();

        switch (iteration)
        {
            default:
                writeBackStage2();
            case 3:
                memoryAccessStage2();
            case 2:
                executeStage2();
            case 1:
                instructionDecodeStage2();
            case 0:
                instructionFetchStage2();
        }
        Clock::tick();

        iteration = iteration + 1;



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
