/**
    CSCI-453 Computer Architecture
    memwbRegister.cpp
    
    Container class for the MEM/WB pipeline register for the z88 architecture.

    @author Stephen Allan <swa9846>
    @author Thomas Andaloro <tra5374>
 */


#include "includes.h"


MemWbRegister::MemWbRegister():
    // subconstructors must be used to initialize the data members
    instrType(0),
    modifiedRegister(-1),
    v("MemWb_V", 1),
    pc("MemWb_PC", ADDRESS_SIZE_BITS),
    npc("MemWb_NPC", ADDRESS_SIZE_BITS),
    ir("MemWb_IR", ADDRESS_SIZE_BITS),
    a("MemWb_A", ADDRESS_SIZE_BITS),
    b("MemWb_B", ADDRESS_SIZE_BITS),
    imm("MemWb_IMM", ADDRESS_SIZE_BITS),
    branch("IdEx_Branch", ADDRESS_SIZE_BITS),
    c("MemWb_C", ADDRESS_SIZE_BITS),
    lmd("MemWb_LMD", ADDRESS_SIZE_BITS)
{

}
