/*
 * ZimpleZombies.c
 *
 *  Created on: Jan 25, 2016
 *      Author: Pacho
 */
#include "ZimpleZombies.h"

volatile byte accel[4] =	{	0,	0,	0, 0};	//	ID_CRC, X, Y, Z
volatile byte flex[4]	=	{	0,	0,	0, 0};	//	ID_CRC, 1, 2, 3
int dataBlockSize = 4;

byte sendData(bool id){
	byte error;
	switch(id){
	case ID_ACCEL:
		accel[3] = 
		error = AS1_SendBlock(accel, 4, &dataBlockSize);
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
