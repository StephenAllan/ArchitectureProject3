/**
    CSCI-453 Computer Architecture
    globals.cpp
    
    Global variables for the z88 architecture.

    @author Stephen Allan <swa9846>
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

Counter pc("PC", ADDRESS_SIZE_BITS);
StorageObject ir("IR", ADDRESS_SIZE_BITS);
StorageObject mar("MAR", ADDRESS_SIZE_BITS);
StorageObject mdr("MDR", ADDRESS_SIZE_BITS);
StorageObject iar("IAR", ADDRESS_SIZE_BITS);
StorageObject temp("TEMP", ADDRESS_SIZE_BITS);

StorageObject ra("RA", ADDRESS_SIZE_BITS);
StorageObject rb("RB", ADDRESS_SIZE_BITS);
StorageObject rc("RC", ADDRESS_SIZE_BITS);

/** Components */
Memory im("InstructionMemory", ADDRESS_SIZE_BITS, BYTE_SIZE_BITS, 0xffff, 4);
Memory dm("DataMemory", ADDRESS_SIZE_BITS, BYTE_SIZE_BITS, 0xffff, 4);

BusALU alu1("ALU1", ADDRESS_SIZE_BITS);
BusALU alu2("ALU2", ADDRESS_SIZE_BITS);
BusALU alu3("ALU3", ADDRESS_SIZE_BITS);
BusALU alu4("ALU4", ADDRESS_SIZE_BITS);

/** Pipeline Registers */
IfIdRegister ifidRegister;
IdExRegister idexRegister;
ExMemRegister exmemRegister;
MemWbRegister memwbRegister;

/** Control Variables */
bool done(false);   // is the simulation over?
