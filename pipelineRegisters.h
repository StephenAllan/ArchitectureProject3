/**
    CSCI-453 Computer Architecture
    pipelineRegisters.h
    
    Header file declerations for the pipeline register classes for the z88 architecture.

    @author Stephen Allan <swa9846>
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
       StorageObject a;     // Operand A
       StorageObject b;     // Operand B
       StorageObject imm;   // Sign-extended immediate
       StorageObject branch;
       StorageObject zeroExtImm;
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
       StorageObject branch;
       StorageObject c;     // Execution result
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
       StorageObject branch;
       StorageObject c;
       StorageObject lmd;   // LMD
};
