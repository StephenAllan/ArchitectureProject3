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
    if (ifidRegister.v.value() == 0) { return; }

    stringstream ss;
    string instruction;

    for (int i = 31; i >= 0; --i)
    {
        ss << ir(i);
    }

    ss >> instruction;
    idexRegister.instruction = instruction;
}

/**
    TODO: Documentation
 */
void executeStage1()
{
    if (idexRegister.v.value() == 0) { return; }
}

/**
    TODO: Documentation
 */
void memoryAccessStage1()
{
    if (exmemRegister.v.value() == 0) { return; }
}

/**
    TODO: Documentation
 */
void writeBackStage1()
{
    if (memwbRegister.v.value() == 0) { return; }

    string standardOpCode = idexRegister.instruction.substr(0, 5);

    if (standardOpCode == "000000")
    {
        string specialOpCode = idexRegister.instruction.substr(26, 31);

        if (specialOpCode == "000000")
        {
            cout << "Machine halted - HALT instruction executed" << endl;
            done = true;
        }
        else if (specialOpCode == "000110" || specialOpCode == "010001" || specialOpCode == "010011" ||
            specialOpCode == "010111")
        {
            cout << "Machine halted - unimplemented instruction" << endl;
            done = true;
        }
        else
        {
            cout << "Machine halted - undefined instruction" << endl;
            done = true;
        }
    }
    else if (standardOpCode == "010001" || standardOpCode == "011001" || standardOpCode == "100000" ||
        standardOpCode == "100001" || standardOpCode == "100100" || standardOpCode == "100101" ||
        standardOpCode == "101000" || standardOpCode == "101001" || standardOpCode == "110010" ||
        standardOpCode == "110011" || standardOpCode == "111010" || standardOpCode == "111011" ||
        standardOpCode == "111110" || standardOpCode == "111111")
    {
        cout << "Machine halted - unimplemented instruction" << endl;
        done = true;
    }
    else
    {
        cout << "Machine halted - undefined instruction" << endl;
        done = true;
    }
}
