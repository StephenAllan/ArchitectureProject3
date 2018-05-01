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

/** Buses */
Bus op1("Op1Bus", ADDRESS_SIZE_BITS);
Bus op2("Op2Bus", ADDRESS_SIZE_BITS);
Bus out("OutBus", ADDRESS_SIZE_BITS);

Bus instructionBus("InstructionBus", ADDRESS_SIZE_BITS);
Bus pcBus("PcBus", ADDRESS_SIZE_BITS);
Bus irBus("IrBus", ADDRESS_SIZE_BITS);

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
StorageObject bitMask_16("BitMask_16", ADDRESS_SIZE_BITS, 32768);   // 1000 0000 0000 0000
StorageObject bitMask_26("BitMask_26", ADDRESS_SIZE_BITS, 0x2000000);

/** Control Variables */
bool done(false);   // is the simulation over?
