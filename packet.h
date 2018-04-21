/**
    CSCI-453 Computer Architecture
    packet.h
    
    Header file declerations for the Packet class for the z88 architecture.

    @author Stephen Allan <swa9846>
 */


#include "includes.h"


class Packet
{
    public:
       Packet();

       Clearable v;
       StorageObject ir;
};
