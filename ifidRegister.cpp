/**
    CSCI-453 Computer Architecture
    ifidRegister.cpp
    
    Container class for the IF/ID pipeline register for the z88 architecture.

    @author Stephen Allan <swa9846>
 */


#include "includes.h"


IfIdRegister::IfIdRegister():
    // subconstructors must be used to initialize the data members
    incrPc(true),
    v("IfId_V", 1),
    pc("IfId_PC", ADDRESS_SIZE_BITS),
    npc("IfId_NPC", ADDRESS_SIZE_BITS),
    ir("IfId_IR", ADDRESS_SIZE_BITS)
{

}
