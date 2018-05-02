/**
    CSCI-453 Computer Architecture
    utilityOperations.cpp
    
    Utility operations for the z88 architecture.

    @author Stephen Allan <swa9846>
 */


#include "includes.h"


/**
    Print all register values to cout for debugging.
    TODO: Remove
 */
void dumpAllRegisters()
{
    for (int i = 0; i < connectionObjects.size(); ++i)
    {
        cout << "  " << (*connectionObjects[i]);

        if ((i + 1) % 4 == 0) { cout << endl; }
    }
    cout << endl;
}

/**
    Print all the non-zero general register values to cout.
 */
void dumpGeneralRegisters()
{
    int displayCount = 0;

    for (int i = 0; i < generalRegisters.size(); ++i)
    {
        if (generalRegisters[i]->value() != 0)
        {
            if (displayCount > 0 && displayCount % 4 == 0) { cout << endl; }

            cout << "  " << (*generalRegisters[i]);
            displayCount = displayCount + 1;
        }
    }

    if (displayCount > 0) { cout << endl; }
}

/**
    TODO: Documentation
 */
void displayRecord(string instructionMnemonic, bool specialOp)
{
    printf("%08lx:  %02lx ", memwbRegister.pc.value(), memwbRegister.ir(31, 26));

    if (specialOp)
    {
        printf("%02lx ", memwbRegister.ir(5, 0));
    }
    else
    {
        cout << "   ";
    }

    printf("%-7s", instructionMnemonic.c_str());

    // If any GPR was updated, print one space and then its contents.
    if (memwbRegister.modifiedRegister > 0)
    {
        cout << " " << (*generalRegisters[memwbRegister.modifiedRegister]);
    }

    cout << endl;
}

/**
    Print out the error text for an unimplemented operation code error.
    Halt the program.
 */
void displayUnimplementedOpCodeError()
{
    cout << "Machine Halted - unimplemented instruction" << endl;
    done = true;
}

/**
    Print out the error text for an undefined operation code error.
    Halt the program.
 */
void displayUndefinedOpCodeError()
{
    cout << "Machine Halted - undefined instruction" << endl;
    done = true;
}
