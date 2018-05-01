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

       Clearable v;         // Valid bit
       StorageObject pc;    // Program counter
       StorageObject npc;   // New program counter
       StorageObject ir;    // Instruction Register
};

class IdExRegister
{
    public:
       IdExRegister();

       Clearable v;
       StorageObject pc;
       StorageObject npc;
       StorageObject ir;
       StorageObject a;     // Operand A
       StorageObject b;     // Operand B
       StorageObject imm;   // Sign-extended immediate
};

class ExMemRegister
{
    public:
       ExMemRegister();

       Clearable v;
       StorageObject pc;
       StorageObject npc;
       StorageObject ir;
       StorageObject a;
       StorageObject b;
       StorageObject imm;
       StorageObject c;     // Execution result
};

class MemWbRegister
{
    public:
       MemWbRegister();

       Clearable v;
       StorageObject pc;
       StorageObject npc;
       StorageObject ir;
       StorageObject a;
       StorageObject b;
       StorageObject imm;
       StorageObject c;
       StorageObject lmd;   // LMD
};