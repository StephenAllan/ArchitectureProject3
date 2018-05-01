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

class IdExRegister : public IfIdRegister
{
    public:
       IdExRegister();

       StorageObject a;     // Operand A
       StorageObject b;     // Operand B
       StorageObject imm;   // Sign-extended immediate
};

class ExMemRegister : public IdExRegister
{
    public:
       ExMemRegister();

       StorageObject c;     // Execution result
};

class MemWbRegister : public ExMemRegister
{
    public:
       MemWbRegister();

       StorageObject lmd;   // LMD
};
