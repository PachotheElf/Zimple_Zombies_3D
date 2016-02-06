/*
 * ZimpleZombies.c
 *
 *  Created on: Jan 25, 2016
 *      Author: Pacho
 */
#include "ZimpleZombies.h"

//	Sensor data arrays
volatile accel_u accel = {0,0,0,0};
volatile byte flex[4]	=	{	0,	0,	0, 0};	//	ID_CRC, 1, 2, 3
//	Sensor data block size
int dataBlockSize = 4;

//	Program state variable
byte PROGRAM_STATE = STATE_SETUP;

byte sendData(bool id){
	byte error;
	switch(id){
	case ID_ACCEL:
		accel.sData.id = 0b11110011;
		error = AS1_SendBlock(accel.rData, 4, &dataBlockSize);
		break;
	case ID_FLEX:
		error = AS1_SendBlock(flex, 4, &dataBlockSize);
		break;
	default:
		error = 0;
		break;
	}
	return error;
}
