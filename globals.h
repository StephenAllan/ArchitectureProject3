/**
    CSCI-453 Computer Architecture
    globals.h
    
    External declarations of global variables for the z88 architecture.

    @author Stephen Allan <swa9846>
    @author Thomas Andaloro <tra5374>
 */


#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "includes.h"


extern const unsigned int ADDRESS_SIZE_BITS;
extern const unsigned int BYTE_SIZE_BITS;

extern vector<StorageObject*> connectionObjects;
extern vector<StorageObject*> generalRegisters;

extern Bus op1;
extern Bus op2;
extern Bus out;

extern Bus instructionBus;
extern Bus pcBus;
extern Bus irBus;

// Buses to bring IF/ID data to ID/EX registers
extern Bus idVBus;
extern Bus idPcBus;
extern Bus idNpcBus;
extern Bus idIrBus;

extern Bus exVBus;
extern Bus exPcBus;
extern Bus exNpcBus;
extern Bus exIrBus;

extern Bus memVBus;
extern Bus memPcBus;
extern Bus memNpcBus;
extern Bus memIrBus;
extern Bus memCBus;

extern StorageObject r0;
extern StorageObject r1;
extern StorageObject r2;
extern StorageObject r3;
extern StorageObject r4;
extern StorageObject r5;
extern StorageObject r6;
extern StorageObject r7;
extern StorageObject r8;
extern StorageObject r9;
extern StorageObject r10;
extern StorageObject r11;
extern StorageObject r12;
extern StorageObject r13;
extern StorageObject r14;
extern StorageObject r15;
extern StorageObject r16;
extern StorageObject r17;
extern StorageObject r18;
extern StorageObject r19;
extern StorageObject r20;
extern StorageObject r21;
extern StorageObject r22;
extern StorageObject r23;
extern StorageObject r24;
extern StorageObject r25;
extern StorageObject r26;
extern StorageObject r27;
extern StorageObject r28;
extern StorageObject r29;
extern StorageObject r30;
extern StorageObject r31;

extern StorageObject pc;
extern StorageObject ir;
extern StorageObject mar;
extern StorageObject mdr;
extern StorageObject iar;
extern StorageObject temp;

extern StorageObject ra;
extern StorageObject rb;
extern StorageObject rc;

extern Memory im;
extern Memory dm;

extern BusALU pcAlu;
extern BusALU alu2;
extern BusALU alu3;
extern BusALU alu4;

extern IfIdRegister ifidRegister;
extern IdExRegister idexRegister;
extern ExMemRegister exmemRegister;
extern MemWbRegister memwbRegister;

extern StorageObject pcIncr;

extern bool done;   // is the simulation over?

#endif
