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

       Clearable v;
       StorageObject pc;
       StorageObject npc;
       StorageObject ir;
};

class IdExRegister : public IfIdRegister
{
    public:
       IdExRegister();

       StorageObject a;
       StorageObject b;
       StorageObject imm;
};

class ExMemRegister : public IdExRegister
{
    public:
       ExMemRegister();

       StorageObject a;
};

class MemWbRegister : public ExMemRegister
{
    public:
       MemWbRegister();

       StorageObject a;
};
