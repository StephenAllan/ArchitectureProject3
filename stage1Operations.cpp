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

    long opcode = ir(31, 26);
    long rs = ir(25, 21);
    long rt = ir(20, 16);
    long imm = ir(15, 0);

    idABus.IN().pullFrom((*generalRegisters[rs]));
    idexRegister.a.latchFrom(idABus.OUT());

    idBBus.IN().pullFrom((*generalRegisters[rt]));
    idexRegister.b.latchFrom(idBBus.OUT());

    if (opcode == 0 || opcode == 1) {
        ifidRegister.instrType = R_TYPE;
    } else if (opcode == 2 || opcode == 3) {
        ifidRegister.instrType = J_TYPE;
    } else {
        ifidRegister.instrType = I_TYPE;
    }

    if (opcode == 2 || opcode == 3)
    {
        bitBus_26.IN().pullFrom(ir);
        idexRegister.zeroExtImm.latchFrom(bitBus_26.OUT());
        ifidRegister.incrPc = false;
    }
    else
    {
        bitBus_16.IN().pullFrom(ir);
        idexRegister.zeroExtImm.latchFrom(bitBus_16.OUT());
    }
    extensionAlu.OP1().pullFrom(ir);
    extensionAlu.OP2().pullFrom(bitMask_16);
    extensionAlu.perform(BusALU::op_extendSign);
    idexRegister.imm.latchFrom(extensionAlu.OUT());
}

/**
    TODO: Documentation
 */
void executeStage1()
{
    if (idexRegister.v.value() == 0) { return; }

    long opcode = idexRegister.ir(31, 26);
    long rs = idexRegister.ir(25, 21);
    long rt = idexRegister.ir(20, 16);
    long rd = idexRegister.ir(15, 11);
    long sh = idexRegister.ir(10, 6);
    long funct = idexRegister.ir(5, 0);

    // Handle I-, R-, and J-type instructions in separate cases
    if (idexRegister.instrType == R_TYPE)
    {
        exFuncAlu.OP1().pullFrom(idexRegister.a);
        exFuncAlu.OP2().pullFrom(idexRegister.b);
        exFuncAlu.perform(BusALU::op_zero); // Ignore the no operation error

        if (funct == 16 || funct == 18 || funct == 20 || funct == 21 || funct == 22 || funct == 37 ||
            funct == 38 || funct == 39 || funct == 45 || funct == 46 || funct == 47)
        {
            idexRegister.c.latchFrom(exFuncAlu.OUT());     // Pass result down pipeline
        }

        if (funct == 16 || funct == 18)
        {
            generalRegisters[rd]->latchFrom(exFuncAlu.OUT());
            idexRegister.modifiedRegister = rd;
        }
        else if (funct == 37 || funct == 38 || funct == 39)
        {
            exFuncAlu.OP1().pullFrom(idexRegister.b);
            exFuncAlu.OP2().pullFrom((*shiftConstants[sh]));
        }
        else if (funct == 45 || funct == 46 || funct == 47)
        {
            exFuncAlu.OP1().pullFrom(idexRegister.b);
            exFuncAlu.OP2().pullFrom(idexRegister.a);

            long value = generalRegisters[rs]->value();
            if (value >= 32)
            {
                value = value % 32;
                exFuncAlu.OP2().pullFrom((*shiftConstants[value]));
            }
        }

        if (rd <= 0) { return; }

        switch (funct)
        {
            case 16: // ADD
                exFuncAlu.perform(BusALU::op_add); break;
            case 18: // SUB
                exFuncAlu.perform(BusALU::op_sub); break;
            case 20: // AND
                exFuncAlu.perform(BusALU::op_and); break;
            case 21: // OR
                exFuncAlu.perform(BusALU::op_or); break;
            case 22: // XOR
                exFuncAlu.perform(BusALU::op_xor); break;

            case 24: // SLT
            {
                long signedRs = idexRegister.a(30, 0);
                if (idexRegister.a(31) == 1) { signedRs = signedRs * -1; }

                long signedRt = idexRegister.b(30, 0);
                if (idexRegister.b(31) == 1) { signedRt = signedRt * -1; }

                if (signedRs < signedRt) { compareBus.IN().pullFrom(const_1); }
                else { compareBus.IN().pullFrom(const_0); }

                idexRegister.c.latchFrom(compareBus.OUT()); // Pass result down pipeline
                break;
            }
            case 25: // SLTU
                if (idexRegister.a.value() < idexRegister.b.value()) { compareBus.IN().pullFrom(const_1); }
                else { compareBus.IN().pullFrom(const_0); }
                
                idexRegister.c.latchFrom(compareBus.OUT()); // Pass result down pipeline
                break;

            case 37: // SLL
                exFuncAlu.perform(BusALU::op_lshift); break;
            case 38: // SRL
                exFuncAlu.perform(BusALU::op_rshift); break;
            case 39: // SRA
                exFuncAlu.perform(BusALU::op_rashift); break;
            case 45: // SLLV
                exFuncAlu.perform(BusALU::op_lshift); break;
            case 46: // SRLV
                exFuncAlu.perform(BusALU::op_rshift); break;
            case 47: // SRAV
                exFuncAlu.perform(BusALU::op_rashift); break;
        }
    }
    else if (idexRegister.instrType == I_TYPE)
    {
        exFuncAlu.OP1().pullFrom(idexRegister.a);
        exFuncAlu.OP2().pullFrom(idexRegister.imm);
        exFuncAlu.perform(BusALU::op_zero); // Ignore the no operation error

        if (opcode == 16 || opcode == 20 || opcode == 21 || opcode == 22 || opcode == 39)
        {
            idexRegister.c.latchFrom(exFuncAlu.OUT());  // Pass result down pipeline
            if (rt <= 0) { return; }
        }

        switch (opcode)
        {
            case 16: // ADDI
                exFuncAlu.perform(BusALU::op_add);
                break;

            case 20: // ANDI
                exFuncAlu.OP2().pullFrom(idexRegister.zeroExtImm);
                exFuncAlu.perform(BusALU::op_and);
                break;

            case 21: // ORI
                exFuncAlu.OP2().pullFrom(idexRegister.zeroExtImm);
                exFuncAlu.perform(BusALU::op_or);
                break;

            case 22: // XORI
                exFuncAlu.OP2().pullFrom(idexRegister.zeroExtImm);
                exFuncAlu.perform(BusALU::op_xor);
                break;

            case 24: // SLTI
            {
                long signedRs = idexRegister.a(30, 0);
                if (idexRegister.a(31) == 1) { signedRs = signedRs * -1; }

                long signedImm = idexRegister.imm(30, 0);
                if (idexRegister.imm(31) == 1) { signedImm = signedImm * -1; }

                if (signedRs < signedImm) { compareBus.IN().pullFrom(const_1); }
                else { compareBus.IN().pullFrom(const_0); }

                idexRegister.c.latchFrom(compareBus.OUT()); // Pass result down pipeline
                break;
            }

            case 35: // LW
                exFuncAlu.perform(BusALU::op_add);
                dm.MAR().latchFrom(exFuncAlu.OUT());
                idexRegister.modifiedRegister = rt;
                break;

            case 39: // LUI
                exFuncAlu.OP1().pullFrom(idexRegister.imm);
                exFuncAlu.OP2().pullFrom(luiShiftAmount);
                exFuncAlu.perform(BusALU::op_lshift);
                break;

            case 43: // SW
                exFuncAlu.perform(BusALU::op_add);
                dm.MAR().latchFrom(exFuncAlu.OUT());
                break;

            default: // In the case of unrecognized/unimplemented opcode, just don't do anything
                break; // Data needs to be passed to WB phase, where it will be printed and halt
        }
    }
}

/**
    TODO: Documentation
 */
void memoryAccessStage1()
{
    if (exmemRegister.v.value() == 0) { return; }

    long opcode = exmemRegister.ir(31, 26);
    long rt = exmemRegister.ir(20, 16);
    long rd = exmemRegister.ir(15, 11);
    long funct = exmemRegister.ir(5, 0);

    if (rt <= 0) { return; }

    if (exmemRegister.instrType == R_TYPE)
    {
        switch (funct)
        {
            case 20:
            case 21:
            case 22:
            case 24:
            case 25:
            case 37:
            case 38:
            case 39:
            case 45:
            case 46:
            case 47:
                saveBus.IN().pullFrom(exmemRegister.c);
                generalRegisters[rd]->latchFrom(saveBus.OUT());
                exmemRegister.modifiedRegister = rd;
                break;
        }
    }
    else if (exmemRegister.instrType == I_TYPE)
    {
        switch (opcode)
        {
            case 16:
            case 20:
            case 21:
            case 22:
            case 24:
            case 39:
                saveBus.IN().pullFrom(exmemRegister.c);
                generalRegisters[rt]->latchFrom(saveBus.OUT());
                exmemRegister.modifiedRegister = rt;
                break;

            case 35: // LW
                dm.read();
                generalRegisters[rt]->latchFrom(dm.READ());
                break;

            case 43: // SW
                dm.WRITE().pullFrom((*generalRegisters[rt]));
                dm.write();
                break;
        }
    }
}

/**
    TODO: Documentation
 */
void writeBackStage1()
{
    if (memwbRegister.v.value() == 0) { return; }

    long opcode = memwbRegister.ir(31, 26);
    long funct = memwbRegister.ir(5, 0);
    
    switch (opcode)
    {
        case 0: // Special
        {
            switch (funct)
            {
                case 0: // HALT
                    displayRecord("HALT", true);
                    cout << "Machine Halted - HALT instruction executed" << endl;
                    done = true;
                    break;

                case 2: // JR
                    displayRecord("JR", true); break;
                case 3: // JALR
                    displayRecord("JALR", true); break;

                case 7: // BREAK
                    displayRecord("BREAK", true);
                    dumpGeneralRegisters();
                    break;

                case 16: // ADD
                    displayRecord("ADD", true); break;
                case 18: // SUB
                    displayRecord("SUB", true); break;
                case 20: // AND
                    displayRecord("AND", true); break;
                case 21: // OR
                    displayRecord("OR", true); break;
                case 22: // XOR
                    displayRecord("XOR", true); break;

                case 24: // SLT
                    displayRecord("SLT", true); break;
                case 25: // SLTU
                    displayRecord("SLTU", true); break;

                case 37: // SLL
                    displayRecord("SLL", true); break;
                case 38: // SRL
                    displayRecord("SRL", true); break;
                case 39: // SRA
                    displayRecord("SRA", true); break;
                case 45: // SLLV
                    displayRecord("SLLV", true); break;
                case 46: // SRLV
                    displayRecord("SRLV", true); break;
                case 47: // SRAV
                    displayRecord("SRAV", true); break;

                // Unimplemented
                case 6:  // SYSCALL
                    displayRecord("SYSCALL", true);
                    displayUnimplementedOpCodeError();
                    break;
                case 17: // ADDU
                    displayRecord("ADDU", true);
                    displayUnimplementedOpCodeError();
                    break;
                case 19: // SUBU
                    displayRecord("SUBU", true);
                    displayUnimplementedOpCodeError();
                    break;
                case 23: // NOR
                    displayRecord("NOR", true);
                    displayUnimplementedOpCodeError();
                    break;

                default: // Unknown
                    displayRecord("???????", true);
                    displayUndefinedOpCodeError();
            }
            break;
        }

        case 1: // NOP
            displayRecord("NOP");
            break;

        case 2: // JR
            displayRecord("J"); break;
        case 3: // JAL
            displayRecord("JAL"); break;

        case 16: // ADDI
            displayRecord("ADDI"); break;
        case 20: // ANDI
            displayRecord("ANDI"); break;
        case 21: // ORI
            displayRecord("ORI"); break;
        case 22: // XORI
            displayRecord("XORI"); break;

        case 24: // SLTI
            displayRecord("SLTI"); break;

        case 35: // LW
            displayRecord("LW"); break;

        case 39: // LUI
            displayRecord("LUI"); break;

        case 43: // SW
            displayRecord("SW"); break;

        case 60: // BEQ
            displayRecord("BEQ"); break;
        case 61: // BNE
            displayRecord("BNE"); break;

        // Unimplemented
        case 17: // ADDIU
            displayRecord("ADDIU");
            displayUnimplementedOpCodeError();
            break;
        case 25: // SLTIU
            displayRecord("SLTIU");
            displayUnimplementedOpCodeError();
            break;
        case 32: // LB
            displayRecord("LB");
            displayUnimplementedOpCodeError();
            break;
        case 33: // LH
            displayRecord("LH");
            displayUnimplementedOpCodeError();
            break;
        case 36: // LBU
            displayRecord("LBU");
            displayUnimplementedOpCodeError();
            break;
        case 37: // LHU
            displayRecord("LHU");
            displayUnimplementedOpCodeError();
            break;
        case 40: // SB
            displayRecord("SB");
            displayUnimplementedOpCodeError();
            break;
        case 41: // SH
            displayRecord("SH");
            displayUnimplementedOpCodeError();
            break;
        case 50: // BLTZ
            displayRecord("BLTZ");
            displayUnimplementedOpCodeError();
            break;
        case 51: // BLTZAL
            displayRecord("BLTZAL");
            displayUnimplementedOpCodeError();
            break;
        case 58: // BGEZ
            displayRecord("BGEZ");
            displayUnimplementedOpCodeError();
            break;
        case 59: // BGEZAL
            displayRecord("BGEZAL");
            displayUnimplementedOpCodeError();
            break;
        case 62: // BLEZ
            displayRecord("BLEZ");
            displayUnimplementedOpCodeError();
            break;
        case 63: // BGTZ
            displayRecord("BGTZ");
            displayUnimplementedOpCodeError();
            break;

        default: // Unknown
            displayRecord("???????");
            displayUndefinedOpCodeError();
    }
}
