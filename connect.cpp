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
    // we can definitely do something like this for the registers, but should we be doing this for
    // basically all the objects in the system?
    for (int i = 0; i < connectionObjects.size(); ++i)
    {
        connectionObjects[i]->connectsTo(op1.IN());
        connectionObjects[i]->connectsTo(op1.OUT());
        connectionObjects[i]->connectsTo(op2.IN());
        connectionObjects[i]->connectsTo(op2.OUT());
        connectionObjects[i]->connectsTo(out.IN());
        connectionObjects[i]->connectsTo(out.OUT());

        connectionObjects[i]->connectsTo(pcAlu.OP1());
        connectionObjects[i]->connectsTo(pcAlu.OP2());
        connectionObjects[i]->connectsTo(pcAlu.OUT());
        connectionObjects[i]->connectsTo(alu2.OP1());
        connectionObjects[i]->connectsTo(alu2.OP2());
        connectionObjects[i]->connectsTo(alu2.OUT());
        connectionObjects[i]->connectsTo(alu3.OP1());
        connectionObjects[i]->connectsTo(alu3.OP2());
        connectionObjects[i]->connectsTo(alu3.OUT());
        connectionObjects[i]->connectsTo(alu4.OP1());
        connectionObjects[i]->connectsTo(alu4.OP2());
        connectionObjects[i]->connectsTo(alu4.OUT());
        // connectionObjects[i]->connectsTo(alu.CARRY());

        connectionObjects[i]->connectsTo(im.READ());
        connectionObjects[i]->connectsTo(im.WRITE());
        connectionObjects[i]->connectsTo(dm.READ());
        connectionObjects[i]->connectsTo(dm.WRITE());
    }
    
    /** Instruction Fetch Connections */
    pc.connectsTo(pcAlu.OP1());
    pc.connectsTo(pcAlu.OUT());
    pcIncr.connectsTo(pcAlu.OP2());
    pc.connectsTo(instructionBus.IN());
    pc.connectsTo(instructionBus.OUT());

    pc.connectsTo(pcBus.IN());
    ifidRegister.pc.connectsTo(pcBus.OUT());
    ifidRegister.npc.connectsTo(pcAlu.OUT());
    
    im.MAR().connectsTo(instructionBus.OUT());
}
