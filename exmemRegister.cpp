/**
    CSCI-453 Computer Architecture
    exmemRegister.cpp
    
    Container class for the EX/MEM pipeline register for the z88 architecture.

    @author Stephen Allan <swa9846>
 */


#include "includes.h"


ExMemRegister::ExMemRegister():
    // subconstructors must be used to initialize the data members
    // TODO: Add correct fields
    v("ExMem_V", 1),
    a("ExMem_A", 32),
    fetchAddress(0)
{

}
