/**
    CSCI-453 Computer Architecture
    includes.h
    
    Master include file for the z88 architecture.

    @author Stephen Allan <swa9846>
 */


#ifndef _INCLUDES_H
#define _INCLUDES_H


/** System Include Files */
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <vector>

/** Arch Library Header Files */
#include <Bus.h>
#include <BusALU.h>
#include <Clearable.h>
#include <Clock.h>
#include <Counter.h>
#include <Memory.h>
#include <ShiftRegister.h>
#include <StorageObject.h>

/** Variable Definition Includes */
#include "pipelineRegisters.h"
#include "globals.h"
#include "prototypes.h"

/** Namespace */
using namespace std;

#endif
