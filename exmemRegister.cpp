/**
    CSCI-453 Computer Architecture
    exmemRegister.cpp
    
    Container class for the EX/MEM pipeline register for the z88 architecture.

    @author Stephen Allan <swa9846>
 */


#include "includes.h"


ExMemRegister::ExMemRegister():
    // subconstructors must be used to initialize the data members
    v("ExMem_V", 1),
    pc("ExMem_PC", 32),
    npc("ExMem_NPC", 32),
    ir("ExMem_IR", 32),
    a("ExMem_A", 32),
    b("ExMem_B", 32),
    imm("ExMem_IMM", 32),
    c("ExMem_C", 32)
{

}
