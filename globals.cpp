/**
    CSCI-453 Computer Architecture
    globals.cpp
    
    Global variables for the z88 architecture.

    @author Stephen Allan <swa9846>
    @author Thomas Andaloro <tra5374>
 */


#include "includes.h"


/** Constants */
const unsigned int ADDRESS_SIZE_BITS(32);   // 32-bit address => 4,294,967,296 units of memory
const unsigned int BYTE_SIZE_BITS(8);

/** Vectors */
vector<StorageObject*> connectionObjects;
vector<StorageObject*> generalRegisters;
vector<StorageObject*> shiftConstants;
vector<int> modifiedRegisters;

/** Buses */
Bus op1("Op1Bus", ADDRESS_SIZE_BITS);
Bus op2("Op2Bus", ADDRESS_SIZE_BITS);
Bus out("OutBus", ADDRESS_SIZE_BITS);

Bus instructionBus("InstructionBus", ADDRESS_SIZE_BITS);
Bus pcBus("PcBus", ADDRESS_SIZE_BITS);
Bus irBus("IrBus", ADDRESS_SIZE_BITS);
Bus loadBus("LoadBus", ADDRESS_SIZE_BITS);
Bus bitBus_16("BitBus_16", 16);
Bus bitBus_26("BitBus_26", 26);
Bus jumpBus("jumpbus", ADDRESS_SIZE_BITS);

Bus idVBus("Id_vBus", 1);
Bus idPcBus("Id_pcBus", ADDRESS_SIZE_BITS);
Bus idNpcBus("Id_npcBus", ADDRESS_SIZE_BITS);
Bus idIrBus("Id_irBus", ADDRESS_SIZE_BITS);
Bus idABus("Id_aBus", ADDRESS_SIZE_BITS);
Bus idBBus("Id_bBus", ADDRESS_SIZE_BITS);
Bus idImmBus("Id_immBus", ADDRESS_SIZE_BITS);

Bus exVBus("Ex_vBus", 1);
Bus exPcBus("Ex_pcBus", ADDRESS_SIZE_BITS);
Bus exNpcBus("Ex_npcBus", ADDRESS_SIZE_BITS);
Bus exIrBus("Ex_irBus", ADDRESS_SIZE_BITS);
Bus exABus("Ex_aBus", ADDRESS_SIZE_BITS);
Bus exBBus("Ex_bBus", ADDRESS_SIZE_BITS);
Bus exImmBus("Ex_immBus", ADDRESS_SIZE_BITS);

Bus memVBus("Mem_vBus", 1);
Bus memPcBus("Mem_pcBus", ADDRESS_SIZE_BITS);
Bus memNpcBus("Mem_npcBus", ADDRESS_SIZE_BITS);
Bus memIrBus("Mem_irBus", ADDRESS_SIZE_BITS);
Bus memABus("Mem_aBus", ADDRESS_SIZE_BITS);
Bus memBBus("Mem_bBus", ADDRESS_SIZE_BITS);
Bus memImmBus("Mem_immBus", ADDRESS_SIZE_BITS);
Bus memCBus("Mem_cBus", ADDRESS_SIZE_BITS);

/** Registers */
StorageObject r0("R0", ADDRESS_SIZE_BITS);
StorageObject r1("R1", ADDRESS_SIZE_BITS);
StorageObject r2("R2", ADDRESS_SIZE_BITS);
StorageObject r3("R3", ADDRESS_SIZE_BITS);
StorageObject r4("R4", ADDRESS_SIZE_BITS);
StorageObject r5("R5", ADDRESS_SIZE_BITS);
StorageObject r6("R6", ADDRESS_SIZE_BITS);
StorageObject r7("R7", ADDRESS_SIZE_BITS);
StorageObject r8("R8", ADDRESS_SIZE_BITS);
StorageObject r9("R9", ADDRESS_SIZE_BITS);
StorageObject r10("R10", ADDRESS_SIZE_BITS);
StorageObject r11("R11", ADDRESS_SIZE_BITS);
StorageObject r12("R12", ADDRESS_SIZE_BITS);
StorageObject r13("R13", ADDRESS_SIZE_BITS);
StorageObject r14("R14", ADDRESS_SIZE_BITS);
StorageObject r15("R15", ADDRESS_SIZE_BITS);
StorageObject r16("R16", ADDRESS_SIZE_BITS);
StorageObject r17("R17", ADDRESS_SIZE_BITS);
StorageObject r18("R18", ADDRESS_SIZE_BITS);
StorageObject r19("R19", ADDRESS_SIZE_BITS);
StorageObject r20("R20", ADDRESS_SIZE_BITS);
StorageObject r21("R21", ADDRESS_SIZE_BITS);
StorageObject r22("R22", ADDRESS_SIZE_BITS);
StorageObject r23("R23", ADDRESS_SIZE_BITS);
StorageObject r24("R24", ADDRESS_SIZE_BITS);
StorageObject r25("R25", ADDRESS_SIZE_BITS);
StorageObject r26("R26", ADDRESS_SIZE_BITS);
StorageObject r27("R27", ADDRESS_SIZE_BITS);
StorageObject r28("R28", ADDRESS_SIZE_BITS);
StorageObject r29("R29", ADDRESS_SIZE_BITS);
StorageObject r30("R30", ADDRESS_SIZE_BITS);
StorageObject r31("R31", ADDRESS_SIZE_BITS);

StorageObject pc("PC", ADDRESS_SIZE_BITS);
StorageObject ir("IR", ADDRESS_SIZE_BITS);
StorageObject mar("MAR", ADDRESS_SIZE_BITS);
StorageObject mdr("MDR", ADDRESS_SIZE_BITS);
StorageObject iar("IAR", ADDRESS_SIZE_BITS);
StorageObject temp("TEMP", ADDRESS_SIZE_BITS);

StorageObject ra("RA", ADDRESS_SIZE_BITS);
StorageObject rb("RB", ADDRESS_SIZE_BITS);
StorageObject rc("RC", ADDRESS_SIZE_BITS);

/** Components */
Memory im("IMemory", ADDRESS_SIZE_BITS, BYTE_SIZE_BITS, 0xffff, 4);
Memory dm("DMemory", ADDRESS_SIZE_BITS, BYTE_SIZE_BITS, 0xffff, 4);

BusALU pcAlu("PC_ALU", ADDRESS_SIZE_BITS);
BusALU exFuncAlu("EX_FUNC_ALU", ADDRESS_SIZE_BITS);
BusALU extensionAlu("Extension_ALU", ADDRESS_SIZE_BITS);
BusALU alu4("ALU4", ADDRESS_SIZE_BITS);

/** Pipeline Registers */
IfIdRegister ifidRegister;
IdExRegister idexRegister;
ExMemRegister exmemRegister;
MemWbRegister memwbRegister;

/** Constants */
StorageObject pcIncr("PcIncr", ADDRESS_SIZE_BITS, 4);
StorageObject luiShiftAmount("LuiShiftAmount", ADDRESS_SIZE_BITS, 16);

StorageObject bitMask_16("BitMask_16", ADDRESS_SIZE_BITS, 0x8000);      // 1000 0000 0000 0000
StorageObject bitMask_26("BitMask_26", ADDRESS_SIZE_BITS, 0x2000000);

StorageObject const_0("Shift_0", ADDRESS_SIZE_BITS, 0);
StorageObject const_1("Shift_1", ADDRESS_SIZE_BITS, 1);
StorageObject const_2("Shift_2", ADDRESS_SIZE_BITS, 2);
StorageObject const_3("Shift_3", ADDRESS_SIZE_BITS, 3);
StorageObject const_4("Shift_4", ADDRESS_SIZE_BITS, 4);
StorageObject const_5("Shift_5", ADDRESS_SIZE_BITS, 5);
StorageObject const_6("Shift_6", ADDRESS_SIZE_BITS, 6);
StorageObject const_7("Shift_7", ADDRESS_SIZE_BITS, 7);
StorageObject const_8("Shift_8", ADDRESS_SIZE_BITS, 8);
StorageObject const_9("Shift_9", ADDRESS_SIZE_BITS, 9);
StorageObject const_10("Shift_10", ADDRESS_SIZE_BITS, 10);
StorageObject const_11("Shift_11", ADDRESS_SIZE_BITS, 11);
StorageObject const_12("Shift_12", ADDRESS_SIZE_BITS, 12);
StorageObject const_13("Shift_13", ADDRESS_SIZE_BITS, 13);
StorageObject const_14("Shift_14", ADDRESS_SIZE_BITS, 14);
StorageObject const_15("Shift_15", ADDRESS_SIZE_BITS, 15);
StorageObject const_16("Shift_16", ADDRESS_SIZE_BITS, 16);
StorageObject const_17("Shift_17", ADDRESS_SIZE_BITS, 17);
StorageObject const_18("Shift_18", ADDRESS_SIZE_BITS, 18);
StorageObject const_19("Shift_19", ADDRESS_SIZE_BITS, 19);
StorageObject const_20("Shift_20", ADDRESS_SIZE_BITS, 20);
StorageObject const_21("Shift_21", ADDRESS_SIZE_BITS, 21);
StorageObject const_22("Shift_22", ADDRESS_SIZE_BITS, 22);
StorageObject const_23("Shift_23", ADDRESS_SIZE_BITS, 23);
StorageObject const_24("Shift_24", ADDRESS_SIZE_BITS, 24);
StorageObject const_25("Shift_25", ADDRESS_SIZE_BITS, 25);
StorageObject const_26("Shift_26", ADDRESS_SIZE_BITS, 26);
StorageObject const_27("Shift_27", ADDRESS_SIZE_BITS, 27);
StorageObject const_28("Shift_28", ADDRESS_SIZE_BITS, 28);
StorageObject const_29("Shift_29", ADDRESS_SIZE_BITS, 29);
StorageObject const_30("Shift_30", ADDRESS_SIZE_BITS, 30);
StorageObject const_31("Shift_31", ADDRESS_SIZE_BITS, 31);

/** Control Variables */
bool done(false);   // is the simulation over?
