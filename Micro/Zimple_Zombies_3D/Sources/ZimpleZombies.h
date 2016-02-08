/*
 * ZimpleZombies.h
 *
 *  Created on: Jan 25, 2016
 *      Author: Pacho
 */
/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Accel_Timer.h"
#include "AS1.h"
#include "AD1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#ifndef ZIMPLEZOMBIES_H_
#define ZIMPLEZOMBIES_H_

//	Accelerometer data structure
typedef struct accel_struct1{	//	Unsigned data structure
	byte id;
	byte x;
	byte y;
	byte z;
}accel_us;
typedef struct accel_struct2{	//	Signed data structure
	char id;
	char x;
	char y;
	char z;
}accel_s;
typedef union accel_union{
	byte rData[4];
	accel_s sData;		//	In case we can figure out how to send raw signed data through the serial port.
	accel_us uData;
}accel_u;

//	Accelerometer constants
#define ACCEL_OFFSET_X	117
#define ACCEL_OFFSET_Y	117
#define ACCEL_OFFSET_Z	117

#define ACCEL_SCALER_X	1
#define ACCEL_SCALER_Y	1
#define ACCEL_SCALER_Z	0

//	Sensor ID for communications
#define ID_ACCEL	0
#define	ID_FLEX		1

//	Program states
#define STATE_MEASURE_ACCEL		1
#define	STATE_MEASURE_FLEX		2
#define	STATE_WORK_ACCEL		3
#define	STATE_WORK_FLEX			4
#define	STATE_SEND_ACCEL		5
#define	STATE_SEND_FLEX			6
#define	STATE_IDLE				7


//	Function prototypes
byte ADC_queue(byte channel);
byte ADC_processData(byte channel);
byte sendData(bool ID);

#endif /* ZIMPLEZOMBIES_H_ */
