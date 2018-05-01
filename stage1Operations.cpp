/**
    CSCI-453 Computer Architecture
    stage1Operations.cpp
    
    Setup operations for the first clock tick of the z88 architecture.

    @author Stephen Allan <swa9846>
    @author Thomas Andaloro <tra5374>
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

    idIrBus.IN().pullFrom(ir);
    ifidRegister.ir.latchFrom(idIrBus.OUT());
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

    // Debug
    // cout << endl;
    // cout << memwbRegister.v << endl;
    // cout << memwbRegister.pc << endl;
    // cout << memwbRegister.npc << endl;
    // cout << memwbRegister.ir << endl;
    // cout << memwbRegister.c << endl;
    // cout << memwbRegister.lmd << endl;
    // cout << endl;

    /** Instruction Format
    opCode = ir(31, 26)
    rs = ir(25, 21)
    rt = ir(20, 16)

    imm = ir(15, 0)

    rd = ir(15, 11)
    sh = ir(10, 6)
    funct = ir(5, 0)

    target = ir(25, 0)
    **/

    long opcode = memwbRegister.ir(31, 26);
    long funct = memwbRegister.ir(5, 0);
    switch (opcode)
    {
        case 0: // Special
        {
            switch (funct)
            {
                case 0: // HALT
                    cout << "Machine halted - HALT instruction executed" << endl;
                    done = true;
                    break;

                case 6:  // Unimplemented
                case 17:
                case 19:
                case 23:
                    displayUnimplementedOpCodeError(true);
                    break;

                default: // Unknown
                    displayUndefinedOpCodeError(true);
            }
            break;
        }

        case 1: // NOP
            break;

        case 2: // J
            break;

        case 3: // JAL
            break;

        case 16: // ADDI
            break;

        case 20: // ANDI
            break;

        case 21: // ORI
            break;

        case 22: // XORI
            break;

        case 24: // SLTI
            break;

        case 35: // LW
            break;

        case 39: // LUI
            break;

        case 43: // SW
            break;

        case 60: // BEQ
            break;

        case 61: // BNE
            break;

        case 17:  // Unimplemented
        case 25:
        case 32:
        case 33:
        case 36:
        case 37:
        case 40:
        case 41:
        case 50:
        case 51:
        case 58:
        case 59:
        case 62:
        case 63:
            displayUnimplementedOpCodeError();
            break;

        default: // Unknown
            displayUndefinedOpCodeError();
    }
}
