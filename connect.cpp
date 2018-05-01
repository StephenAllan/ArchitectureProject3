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
    for (int i = 0; i < generalRegisters.size(); ++i)
    {
        generalRegisters[i]->connectsTo(idABus.IN());
        generalRegisters[i]->connectsTo(idBBus.IN());
        generalRegisters[i]->connectsTo(idImmBus.IN());
        generalRegisters[i]->connectsTo(exFuncAlu.OUT());
        generalRegisters[i]->connectsTo(dm.READ());
    }

    /** Memory Components */
    im.MAR().connectsTo(instructionBus.OUT());
    dm.MAR().connectsTo(loadBus.OUT());
    
    /** Instruction Fetch Connections */
    pc.connectsTo(im.READ());
    pc.connectsTo(instructionBus.IN());
    ir.connectsTo(im.READ());

    pc.connectsTo(pcBus.IN());
    ifidRegister.pc.connectsTo(pcBus.OUT());

    pc.connectsTo(pcAlu.OP1());
    pcIncr.connectsTo(pcAlu.OP2());
    pc.connectsTo(pcAlu.OUT());
    ifidRegister.npc.connectsTo(pcAlu.OUT());
    
    /** Instruction Decode Connections */
    ifidRegister.v.connectsTo(idVBus.IN());
    ifidRegister.pc.connectsTo(idPcBus.IN());
    ifidRegister.npc.connectsTo(idNpcBus.IN());
    ifidRegister.ir.connectsTo(idIrBus.IN());
    idexRegister.v.connectsTo(idVBus.OUT());
    idexRegister.pc.connectsTo(idPcBus.OUT());
    idexRegister.npc.connectsTo(idNpcBus.OUT());
    idexRegister.ir.connectsTo(idIrBus.OUT());
    idexRegister.a.connectsTo(idABus.OUT());
    idexRegister.b.connectsTo(idBBus.OUT());
    idexRegister.imm.connectsTo(idImmBus.OUT());

    ir.connectsTo(idIrBus.IN());
    ifidRegister.ir.connectsTo(idIrBus.OUT());

    ir.connectsTo(extensionAlu.OP1());
    bitMask_16.connectsTo(extensionAlu.OP2());
    idexRegister.imm.connectsTo(extensionAlu.OUT());

    /** Execution Stage Connections */
    idexRegister.v.connectsTo(exVBus.IN());
    idexRegister.pc.connectsTo(exPcBus.IN());
    idexRegister.npc.connectsTo(exNpcBus.IN());
    idexRegister.ir.connectsTo(exIrBus.IN());
    idexRegister.a.connectsTo(exABus.IN());
    idexRegister.b.connectsTo(exBBus.IN());
    idexRegister.imm.connectsTo(exImmBus.IN());
    exmemRegister.v.connectsTo(exVBus.OUT());
    exmemRegister.pc.connectsTo(exPcBus.OUT());
    exmemRegister.npc.connectsTo(exNpcBus.OUT());
    exmemRegister.ir.connectsTo(exIrBus.OUT());
    exmemRegister.a.connectsTo(exABus.OUT());
    exmemRegister.b.connectsTo(exBBus.OUT());
    exmemRegister.imm.connectsTo(exImmBus.OUT());

    idexRegister.a.connectsTo(exFuncAlu.OP1());
    idexRegister.b.connectsTo(exFuncAlu.OP2());
    idexRegister.imm.connectsTo(exFuncAlu.OP2());
    exmemRegister.c.connectsTo(exFuncAlu.OUT());

    idexRegister.imm.connectsTo(loadBus.IN());

    /** Memory Stage Connections */
    exmemRegister.v.connectsTo(memVBus.IN());
    exmemRegister.pc.connectsTo(memPcBus.IN());
    exmemRegister.npc.connectsTo(memNpcBus.IN());
    exmemRegister.ir.connectsTo(memIrBus.IN());
    exmemRegister.a.connectsTo(memABus.IN());
    exmemRegister.b.connectsTo(memBBus.IN());
    exmemRegister.imm.connectsTo(memImmBus.IN());
    exmemRegister.c.connectsTo(memCBus.IN());
    memwbRegister.v.connectsTo(memVBus.OUT());
    memwbRegister.pc.connectsTo(memPcBus.OUT());
    memwbRegister.npc.connectsTo(memNpcBus.OUT());
    memwbRegister.ir.connectsTo(memIrBus.OUT());
    memwbRegister.a.connectsTo(memABus.OUT());
    memwbRegister.b.connectsTo(memBBus.OUT());
    memwbRegister.imm.connectsTo(memImmBus.OUT());
    memwbRegister.c.connectsTo(memCBus.OUT());
}
