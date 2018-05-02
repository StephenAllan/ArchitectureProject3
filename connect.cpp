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
        generalRegisters[i]->connectsTo(exFuncAlu.OP2());
        generalRegisters[i]->connectsTo(exFuncAlu.OUT());
        generalRegisters[i]->connectsTo(compareBus.OUT());
        generalRegisters[i]->connectsTo(saveBus.OUT());
        generalRegisters[i]->connectsTo(dm.READ());
        generalRegisters[i]->connectsTo(dm.WRITE());
    }

    for (int i = 0; i < shiftConstants.size(); ++i)
    {
        shiftConstants[i]->connectsTo(exFuncAlu.OP2());
    }

    /** Memory Components */
    im.MAR().connectsTo(instructionBus.OUT());
    dm.MAR().connectsTo(exFuncAlu.OUT());
    
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

    pc.connectsTo(jumpBus.OUT());
    ifidRegister.npc.connectsTo(jumpBus.OUT());
    idexRegister.zeroExtImm.connectsTo(jumpBus.IN());
    idexRegister.a.connectsTo(jumpBus.IN());
    
    /** Instruction Decode Connections */
    bitMask_26.connectsTo(extensionAlu.OP2());

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

    ir.connectsTo(bitBus_16.IN());
    idexRegister.zeroExtImm.connectsTo(bitBus_16.OUT());
    ir.connectsTo(bitBus_26.IN());
    idexRegister.zeroExtImm.connectsTo(bitBus_26.OUT());

    generalRegisters[31]->connectsTo(exFuncAlu.OUT());

    const_0.connectsTo(compareBus.IN());
    const_1.connectsTo(compareBus.IN());
    idexRegister.c.connectsTo(compareBus.OUT());

    ifidRegister.npc.connectsTo(branchAlu.OP1());
    idexRegister.imm.connectsTo(branchAlu.OP2());
    ifidRegister.pc.connectsTo(branchAlu.OUT());
    pc.connectsTo(branchAlu.OUT());

    /** Execution Stage Connections */
    idexRegister.v.connectsTo(exVBus.IN());
    idexRegister.pc.connectsTo(exPcBus.IN());
    idexRegister.npc.connectsTo(exNpcBus.IN());
    idexRegister.ir.connectsTo(exIrBus.IN());
    idexRegister.a.connectsTo(exABus.IN());
    idexRegister.b.connectsTo(exBBus.IN());
    idexRegister.imm.connectsTo(exImmBus.IN());
    idexRegister.c.connectsTo(exCBus.IN());
    exmemRegister.v.connectsTo(exVBus.OUT());
    exmemRegister.pc.connectsTo(exPcBus.OUT());
    exmemRegister.npc.connectsTo(exNpcBus.OUT());
    exmemRegister.ir.connectsTo(exIrBus.OUT());
    exmemRegister.a.connectsTo(exABus.OUT());
    exmemRegister.b.connectsTo(exBBus.OUT());
    exmemRegister.imm.connectsTo(exImmBus.OUT());
    exmemRegister.c.connectsTo(exCBus.OUT());

    idexRegister.a.connectsTo(exFuncAlu.OP1());
    idexRegister.a.connectsTo(exFuncAlu.OP2());
    idexRegister.b.connectsTo(exFuncAlu.OP1());
    idexRegister.b.connectsTo(exFuncAlu.OP2());
    idexRegister.imm.connectsTo(exFuncAlu.OP2());
    idexRegister.npc.connectsTo(exFuncAlu.OP1());
    idexRegister.c.connectsTo(exFuncAlu.OUT());

    pc.connectsTo(exFuncAlu.OUT());
    idexRegister.pc.connectsTo(exFuncAlu.OP1());
    idexRegister.imm.connectsTo(exFuncAlu.OP1());
    idexRegister.zeroExtImm.connectsTo(exFuncAlu.OP2());
    luiShiftAmount.connectsTo(exFuncAlu.OP2());

    idexRegister.imm.connectsTo(loadBus.IN());

    idexRegister.pc.connectsTo(exPcBus.IN());
    idexRegister.c.connectsTo(exPcBus.OUT());

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

    exmemRegister.c.connectsTo(saveBus.IN());
}
