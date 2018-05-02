/**
    CSCI-453 Computer Architecture
    exmemRegister.cpp
    
    Container class for the EX/MEM pipeline register for the z88 architecture.

    @author Stephen Allan <swa9846>
 */


#include "includes.h"


ExMemRegister::ExMemRegister():
    // subconstructors must be used to initialize the data members
    instrType(0),
    modifiedRegister(-1),
    v("ExMem_V", 1),
    pc("ExMem_PC", ADDRESS_SIZE_BITS),
    npc("ExMem_NPC", ADDRESS_SIZE_BITS),
    ir("ExMem_IR", ADDRESS_SIZE_BITS),
    a("ExMem_A", ADDRESS_SIZE_BITS),
    b("ExMem_B", ADDRESS_SIZE_BITS),
    imm("ExMem_IMM", ADDRESS_SIZE_BITS),
    branch("IdEx_Branch", ADDRESS_SIZE_BITS),
    c("ExMem_C", ADDRESS_SIZE_BITS)
{

}
