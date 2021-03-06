/**
    CSCI-453 Computer Architecture
    utilityOperations.cpp
    
    Utility operations for the z88 architecture.

    @author Stephen Allan <swa9846>
 */


#include "includes.h"


/**
    Print all the non-zero general register values to cout.
 */
void dumpGeneralRegisters()
{
    int displayCount = 0;

    for (int i = 0; i < generalRegisters.size(); ++i)
    {
        if (generalRegisters[i]->value() != 0 && vectorContains(modifiedRegisters, i))
        {
            if (displayCount > 0 && displayCount % 4 == 0) { cout << endl; }

            if (displayCount % 4 == 0 && i < 10) { cout << " "; }

            if (displayCount % 4 == 0) { cout << "    " << (*generalRegisters[i]); }
            else
            {
                if (i < 10) { cout << "  "; }
                else { cout << " "; }
                cout << (*generalRegisters[i]);
            }

            displayCount = displayCount + 1;
        }
    }

    if (displayCount > 0) { cout << endl; }
}

/**
    Display the formatted execution record.
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
    if (memwbRegister.modifiedRegister > -1)
    {
        if (!vectorContains(modifiedRegisters, memwbRegister.modifiedRegister))
        {
            modifiedRegisters.push_back(memwbRegister.modifiedRegister);
        }

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

/**
    Check if value is an element within vector.
 */
bool vectorContains(vector<int> vector, int value)
{
    if (find(vector.begin(), vector.end(), value) == vector.end()) { return false; }
    return true;
}