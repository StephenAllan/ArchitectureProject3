/**
    CSCI-453 Computer Architecture
    z88.cpp
    
    Simulator for an architecture called the z88.

    @author Stephen Allan <swa9846>
 */


#include "includes.h"


/**
    Program entry point.
    Validate command line argument, set debug level, and begin the simulation.

    @param argc Number of command line arguments
    @param argv Command line arguments
 */
int main(int argc, char** argv)
{
    cout << hex;    // set up base for all future printing

    // Validate argument count
    if(argc < 2)
    {
        cerr << "Missing object file argument" << endl;
        cerr << "Usage: " << argv[0] << " <object-file-name>" << endl << endl;
        exit(2);
    }

    // Enable debug options
    if(argc > 2)
    {
        char* options = argv[2];
        int numOptions = strlen(options);

        for(int i = 0;  i < numOptions; ++i)
        {
            switch(options[i])
            {
                case 'c':
                    CPUObject::debug |= CPUObject::create;
                    break;

                case 'r':
                    CPUObject::debug |= CPUObject::trace;
                    break;
                    
                case 'm':
                    CPUObject::debug |= CPUObject::memload;
                    break;
                    
                case 's':
                    CPUObject::debug |= CPUObject::stats;
                    break;
                    
                case 't':
                    CPUObject::debug |= CPUObject::trace_ticks;
                    break;
            }
        }
    }

    // Build Connection Objects vector
    connectionObjects.push_back(&r0);
    connectionObjects.push_back(&r1);
    connectionObjects.push_back(&r2);
    connectionObjects.push_back(&r3);
    connectionObjects.push_back(&r4);
    connectionObjects.push_back(&r5);
    connectionObjects.push_back(&r6);
    connectionObjects.push_back(&r7);
    connectionObjects.push_back(&r8);
    connectionObjects.push_back(&r9);
    connectionObjects.push_back(&r10);
    connectionObjects.push_back(&r11);
    connectionObjects.push_back(&r12);
    connectionObjects.push_back(&r13);
    connectionObjects.push_back(&r14);
    connectionObjects.push_back(&r15);
    connectionObjects.push_back(&r16);
    connectionObjects.push_back(&r17);
    connectionObjects.push_back(&r18);
    connectionObjects.push_back(&r19);
    connectionObjects.push_back(&r20);
    connectionObjects.push_back(&r21);
    connectionObjects.push_back(&r22);
    connectionObjects.push_back(&r23);
    connectionObjects.push_back(&r24);
    connectionObjects.push_back(&r25);
    connectionObjects.push_back(&r26);
    connectionObjects.push_back(&r27);
    connectionObjects.push_back(&r28);
    connectionObjects.push_back(&r29);
    connectionObjects.push_back(&r30);
    connectionObjects.push_back(&r31);

    connectionObjects.push_back(&pc);
    connectionObjects.push_back(&ir);
    connectionObjects.push_back(&mar);
    connectionObjects.push_back(&mdr);
    connectionObjects.push_back(&iar);
    connectionObjects.push_back(&temp);

    connectionObjects.push_back(&ra);
    connectionObjects.push_back(&rb);
    connectionObjects.push_back(&rc);

    // Build General Registers vector
    generalRegisters.push_back(&r0);
    generalRegisters.push_back(&r1);
    generalRegisters.push_back(&r2);
    generalRegisters.push_back(&r3);
    generalRegisters.push_back(&r4);
    generalRegisters.push_back(&r5);
    generalRegisters.push_back(&r6);
    generalRegisters.push_back(&r7);
    generalRegisters.push_back(&r8);
    generalRegisters.push_back(&r9);
    generalRegisters.push_back(&r10);
    generalRegisters.push_back(&r11);
    generalRegisters.push_back(&r12);
    generalRegisters.push_back(&r13);
    generalRegisters.push_back(&r14);
    generalRegisters.push_back(&r15);
    generalRegisters.push_back(&r16);
    generalRegisters.push_back(&r17);
    generalRegisters.push_back(&r18);
    generalRegisters.push_back(&r19);
    generalRegisters.push_back(&r20);
    generalRegisters.push_back(&r21);
    generalRegisters.push_back(&r22);
    generalRegisters.push_back(&r23);
    generalRegisters.push_back(&r24);
    generalRegisters.push_back(&r25);
    generalRegisters.push_back(&r26);
    generalRegisters.push_back(&r27);
    generalRegisters.push_back(&r28);
    generalRegisters.push_back(&r29);
    generalRegisters.push_back(&r30);
    generalRegisters.push_back(&r31);

    // Build Shift Constants vector
    shiftConstants.push_back(&const_0);
    shiftConstants.push_back(&const_1);
    shiftConstants.push_back(&const_2);
    shiftConstants.push_back(&const_3);
    shiftConstants.push_back(&const_4);
    shiftConstants.push_back(&const_5);
    shiftConstants.push_back(&const_6);
    shiftConstants.push_back(&const_7);
    shiftConstants.push_back(&const_8);
    shiftConstants.push_back(&const_9);
    shiftConstants.push_back(&const_10);
    shiftConstants.push_back(&const_11);
    shiftConstants.push_back(&const_12);
    shiftConstants.push_back(&const_13);
    shiftConstants.push_back(&const_14);
    shiftConstants.push_back(&const_15);
    shiftConstants.push_back(&const_16);
    shiftConstants.push_back(&const_17);
    shiftConstants.push_back(&const_18);
    shiftConstants.push_back(&const_19);
    shiftConstants.push_back(&const_20);
    shiftConstants.push_back(&const_21);
    shiftConstants.push_back(&const_22);
    shiftConstants.push_back(&const_23);
    shiftConstants.push_back(&const_24);
    shiftConstants.push_back(&const_25);
    shiftConstants.push_back(&const_26);
    shiftConstants.push_back(&const_27);
    shiftConstants.push_back(&const_28);
    shiftConstants.push_back(&const_29);
    shiftConstants.push_back(&const_30);
    shiftConstants.push_back(&const_31);

    // Simulate the z88
    try
    {
        connect();

        simulate(argv[1]);
    }
    catch(ArchLibError &err)
    {
        cout << endl
             << "Simulation aborted - ArchLib runtime error"
             << endl
             << "Cause: " << err.what()
             << endl;
        return(1);
    }

    return(0);
}
