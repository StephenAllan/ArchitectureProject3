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

/** Pipeline Operations */
void instructionFetchStage1();
void instructionDecodeStage1();
void executeStage1();
void memoryAccessStage1();
void writeBackStage1();

void instructionFetchStage2();
void instructionDecodeStage2();
void executeStage2();
void memoryAccessStage2();

/** Utility Operations */
void dumpGeneralRegisters();
void displayRecord(string, bool = false);
void displayUnimplementedOpCodeError();
void displayUndefinedOpCodeError();
bool vectorContains(vector<int>, int);

#endif
