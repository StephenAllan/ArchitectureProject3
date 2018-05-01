/**
    CSCI-453 Computer Architecture
    connect.cpp
    
    Connect all CPU components for the z88 architecture.

    @author Stephen Allan <swa9846>
    @author Thomas Andaloro <tra5374>
 */


#include "includes.h"


/**
    Connect InFlow and OutFlow pipes of all CPUObjects.
 */
void connect()
{
    // we can definitely do something like this for the registers, but should we be doing this for
    // basically all the objects in the system?
    // Simple and easy solution to a clunky mechanic. Theres no penality (by grading or by the program)
    // for over-connecting. Feel free to manually setup every connection though, it just takes time
    // away from implementing functionality that gets tested.
    for (int i = 0; i < connectionObjects.size(); ++i)
    {
        connectionObjects[i]->connectsTo(op1.IN());
        connectionObjects[i]->connectsTo(op1.OUT());
        connectionObjects[i]->connectsTo(op2.IN());
        connectionObjects[i]->connectsTo(op2.OUT());
        connectionObjects[i]->connectsTo(out.IN());
        connectionObjects[i]->connectsTo(out.OUT());

        connectionObjects[i]->connectsTo(alu2.OP1());
        connectionObjects[i]->connectsTo(alu2.OP2());
        connectionObjects[i]->connectsTo(alu2.OUT());
        connectionObjects[i]->connectsTo(alu3.OP1());
        connectionObjects[i]->connectsTo(alu3.OP2());
        connectionObjects[i]->connectsTo(alu3.OUT());
        connectionObjects[i]->connectsTo(alu4.OP1());
        connectionObjects[i]->connectsTo(alu4.OP2());
        connectionObjects[i]->connectsTo(alu4.OUT());

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

    pc.connectsTo(pcBus.IN());
    ifidRegister.pc.connectsTo(pcBus.OUT());
    ifidRegister.npc.connectsTo(pcAlu.OUT());

    ir.connectsTo(idIrBus.IN());
    ifidRegister.ir.connectsTo(idIrBus.OUT());

    ifidRegister.v.connectsTo(idVBus.IN());
    idexRegister.v.connectsTo(idVBus.OUT());
    ifidRegister.pc.connectsTo(idPcBus.IN());
    idexRegister.pc.connectsTo(idPcBus.OUT());
    ifidRegister.npc.connectsTo(idNpcBus.IN());
    idexRegister.npc.connectsTo(idNpcBus.OUT());
    ifidRegister.ir.connectsTo(idIrBus.IN());
    idexRegister.ir.connectsTo(idIrBus.OUT());

    idexRegister.v.connectsTo(exVBus.IN());
    exmemRegister.v.connectsTo(exVBus.OUT());
    idexRegister.pc.connectsTo(exPcBus.IN());
    exmemRegister.pc.connectsTo(exPcBus.OUT());
    idexRegister.npc.connectsTo(exNpcBus.IN());
    exmemRegister.npc.connectsTo(exNpcBus.OUT());
    idexRegister.ir.connectsTo(exIrBus.IN());
    exmemRegister.ir.connectsTo(exIrBus.OUT());

    exmemRegister.v.connectsTo(memVBus.IN());
    memwbRegister.v.connectsTo(memVBus.OUT());
    exmemRegister.pc.connectsTo(memPcBus.IN());
    memwbRegister.pc.connectsTo(memPcBus.OUT());
    exmemRegister.npc.connectsTo(memNpcBus.IN());
    memwbRegister.npc.connectsTo(memNpcBus.OUT());
    exmemRegister.ir.connectsTo(memIrBus.IN());
    memwbRegister.ir.connectsTo(memIrBus.OUT());
    exmemRegister.c.connectsTo(memCBus.IN());
    memwbRegister.c.connectsTo(memCBus.OUT());
    
    /** Instruction Decode Connections */
    ifidRegister.v.connectsTo(idVBus.IN());
    ifidRegister.pc.connectsTo(idPcBus.IN());
    ifidRegister.npc.connectsTo(idNpcBus.IN());
    ifidRegister.ir.connectsTo(idIrBus.IN());
    idexRegister.v.connectsTo(idVBus.OUT());
    idexRegister.pc.connectsTo(idPcBus.OUT());
    idexRegister.npc.connectsTo(idNpcBus.OUT());
    idexRegister.ir.connectsTo(idIrBus.OUT());

    /** Execution Stage Connections */
    idexRegister.v.connectsTo(exVBus.IN());
    idexRegister.pc.connectsTo(exPcBus.IN());
    idexRegister.ir.connectsTo(exIrBus.IN());
    exmemRegister.v.connectsTo(exVBus.OUT());
    exmemRegister.pc.connectsTo(exPcBus.OUT());
    exmemRegister.ir.connectsTo(exIrBus.OUT());

    /** Memory Stage Connections */
    exmemRegister.v.connectsTo(memVBus.IN());
    exmemRegister.pc.connectsTo(memPcBus.IN());
    exmemRegister.ir.connectsTo(memIrBus.IN());
    memwbRegister.v.connectsTo(memVBus.OUT());
    memwbRegister.pc.connectsTo(memPcBus.OUT());
    memwbRegister.ir.connectsTo(memIrBus.OUT());

    im.MAR().connectsTo(instructionBus.OUT());
}
