/**
    CSCI-453 Computer Architecture
    idexRegister.cpp
    
    Container class for the ID/EX pipeline register for the z88 architecture.

    @author Stephen Allan <swa9846>
 */


#include "includes.h"


IdExRegister::IdExRegister():
    // subconstructors must be used to initialize the data members
    instrType(0),
    v("IdEx_V", 1),
    pc("IdEx_PC", ADDRESS_SIZE_BITS),
    npc("IdEx_NPC", ADDRESS_SIZE_BITS),
    ir("IdEx_IR", ADDRESS_SIZE_BITS),
    a("IdEx_A", ADDRESS_SIZE_BITS),
    b("IdEx_B", ADDRESS_SIZE_BITS),
    imm("IdEx_Imm", ADDRESS_SIZE_BITS)
{

}
