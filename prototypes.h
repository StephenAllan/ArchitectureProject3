/**
    CSCI-453 Computer Architecture
    prototypes.h
    
    Function prototypes for the z88 architecture.

    @author Stephen Allan <swa9846>
 */


#ifndef _PROTOTYPES_H
#define _PROTOTYPES_H


/** General Functions */
void connect();
void simulate(char *);
void execute(long);

/** Utility Operations */
// void dumpRegisters();
// void displayRecord(long, long, string, string = "");
// void displayRecord(long , vector<long>, string, string = "");
// void displayModeError();
// void displayUnalignedMemoryError();
// string numToString(long);
// void branchPC(bool, bool);

/** Component Operations */
// void fetch(StorageObject &, StorageObject &, Bus &);
// void write(StorageObject &, StorageObject &);
// void registerCopy(StorageObject &, StorageObject &, Bus &);
// void aluOperation(StorageObject &, StorageObject &, BusALU::Operation, StorageObject &);

/** ALU Operations */
// void addRegister(StorageObject &, StorageObject &, StorageObject &);
// void subRegister(StorageObject &, StorageObject &, StorageObject &);
// void clearRegister(StorageObject &);
// void complementRegister(StorageObject &);

#endif
