/**
    CSCI-453 Computer Architecture
    packet.cpp
    
    Execution unit containing information about the current stage in the pipeline for the z88 architecture.

    @author Stephen Allan <swa9846>
 */


#include "includes.h"


Packet::Packet() :
    // FIXME: This is creating new StorageObjects during runtime... is this allowed?
    v("IfId_V", 1),     // subconstructors must be used to
    ir("IfId_IR", 32)  // initialize the data members
{

}
