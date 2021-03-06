/**
    CSCI-453 Computer Architecture
    pipelineRegisters.h
    
    Header file declerations for the pipeline register classes for the z88 architecture.

    @author Stephen Allan <swa9846>
    @author Thomas Andaloro <tra5374>
 */


#include "includes.h"


class IfIdRegister
{
    public:
       IfIdRegister();

       bool incrPc;
       unsigned short instrType;

       Clearable v;         // Valid bit
       StorageObject pc;    // Program counter
       StorageObject npc;   // New program counter
       StorageObject ir;    // Instruction Register
};

class IdExRegister
{
    public:
       IdExRegister();

       unsigned short instrType;
       short modifiedRegister;

       Clearable v;
       StorageObject pc;
       StorageObject npc;
       StorageObject ir;
       StorageObject a;           // Operand A
       StorageObject b;           // Operand B
       StorageObject imm;         // Sign-extended immediate
       StorageObject c;           // Execution result
       StorageObject zeroExtImm;  // Zero-extended immediate
};

class ExMemRegister
{
    public:
       ExMemRegister();

       unsigned short instrType;
       short modifiedRegister;

       Clearable v;
       StorageObject pc;
       StorageObject npc;
       StorageObject ir;
       StorageObject a;
       StorageObject b;
       StorageObject imm;
       StorageObject c;
};

class MemWbRegister
{
    public:
       MemWbRegister();

       unsigned short instrType;
       short modifiedRegister;

       Clearable v;
       StorageObject pc;
       StorageObject npc;
       StorageObject ir;
       StorageObject a;
       StorageObject b;
       StorageObject imm;
       StorageObject c;
};
