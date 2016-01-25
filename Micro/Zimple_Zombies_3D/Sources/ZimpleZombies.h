/*
 * ZimpleZombies.h
 *
 *  Created on: Jan 25, 2016
 *      Author: Pacho
 */
/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "TI1.h"
#include "AS1.h"
#include "AD1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#ifndef ZIMPLEZOMBIES_H_
#define ZIMPLEZOMBIES_H_



#define ID_ACCEL	0
#define	ID_FLEX		1

byte sendData(bool ID);

#endif /* ZIMPLEZOMBIES_H_ */