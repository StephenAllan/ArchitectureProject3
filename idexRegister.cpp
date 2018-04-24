/**
    CSCI-453 Computer Architecture
    idexRegister.cpp
    
    Container class for the ID/EX pipeline register for the z88 architecture.

    @author Stephen Allan <swa9846>
 */


#include "includes.h"


IdExRegister::IdExRegister():
    // subconstructors must be used to initialize the data members
    a("IdEx_A", 32),
    b("IdEx_B", 32),
    imm("IdEx_Imm", 32)
{

}
