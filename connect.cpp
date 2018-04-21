/**
    CSCI-453 Computer Architecture
    connect.cpp
    
    Connect all CPU components for the z88 architecture.

    @author Stephen Allan <swa9846>
 */


#include "includes.h"


/**
    Connect InFlow and OutFlow pipes of all CPUObjects.
 */
void connect()
{
    for (int i = 0; i < connectionObjects.size(); ++i)
    {
        // connectionObjects[i]->connectsTo(abus.IN());
        // connectionObjects[i]->connectsTo(abus.OUT());
        // connectionObjects[i]->connectsTo(alu.OP1());
        // connectionObjects[i]->connectsTo(alu.OP2());
        // connectionObjects[i]->connectsTo(alu.OUT());
        // connectionObjects[i]->connectsTo(alu.CARRY());
        // connectionObjects[i]->connectsTo(memory.READ());
        // connectionObjects[i]->connectsTo(memory.WRITE());
    }

    // memory.MAR().connectsTo(abus.OUT());
}
