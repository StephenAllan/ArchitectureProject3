/**
    CSCI-453 Computer Architecture
    ifidRegister.cpp
    
    Container class for the IF/ID pipeline register for the z88 architecture.

    @author Stephen Allan <swa9846>
 */


#include "includes.h"


IfIdRegister::IfIdRegister():
    // subconstructors must be used to initialize the data members
    v("IfId_V", 1),
    pc("IfId_PC", 32),
    npc("IfId_NPC", 32),
    ir("IfId_IR", 32)
{
    
}
