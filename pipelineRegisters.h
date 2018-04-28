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
       long fetchAddress;
};

class IdExRegister : public IfIdRegister
{
    public:
       IdExRegister();

       Clearable v;
       StorageObject a;
       StorageObject b;
       StorageObject imm;
       long fetchAddress;
};

class ExMemRegister : public IdExRegister
{
    public:
       ExMemRegister();

       Clearable v;
       StorageObject a;
       long fetchAddress;
};

class MemWbRegister : public ExMemRegister
{
    public:
       MemWbRegister();

       Clearable v;
       StorageObject a;
       long fetchAddress;
};
