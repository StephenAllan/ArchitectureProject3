/**
    CSCI-453 Computer Architecture
    memwbRegister.cpp
    
    Container class for the MEM/WB pipeline register for the z88 architecture.

    @author Stephen Allan <swa9846>
 */


#include "includes.h"


MemWbRegister::MemWbRegister():
    // subconstructors must be used to initialize the data members
    // TODO: Add correct fields
    v("MemWb_V", 1),
    a("MemWb_A", 32),
    fetchAddress(0)
{

}
