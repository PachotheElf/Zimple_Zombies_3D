/*
 * ZimpleZombies.c
 *
 *  Created on: Jan 25, 2016
 *      Author: Pacho
 */
#include "ZimpleZombies.h"

//	ADC	related variables
const bool	ADC_HOLD	=	FALSE;
const byte	ADC_ACCEL_X	=	0;
const byte	ADC_ACCEL_Y	=	1;
const byte	ADC_PRXMT_1	=	2;

//	Sensor data arrays
volatile char testData = 0;
volatile sensor_u sensors[SENSOR_BUFFER_SIZE];
volatile sensor_u averagedData;
volatile char sensorDataCount = 0;

//	Sensor data block size
int dataBlockSize = 4;

//	Program state variable
byte PROGRAM_STATE = STATE_IDLE;

byte averageData(){
	byte error = 0;
	int i;
	int sum[3] = {0,0,0};
	for(i = 0; i < SENSOR_BUFFER_SIZE; i++){
		sum[0] = sensors[i].uData.accel_x;		//	Accel X sum
		sum[1] = sensors[i].uData.accel_y;		//	Accel Y sum
		sum[2] = sensors[i].uData.prxmt_1;		//	Prxmt sum
	}
	averagedData.uData.accel_x = ((char)(sum[0]/SENSOR_BUFFER_SIZE) - ACCEL_OFFSET_X)*ACCEL_SCALER_X;
	averagedData.uData.accel_y = ((char)(sum[1]/SENSOR_BUFFER_SIZE) - ACCEL_OFFSET_Y)*ACCEL_SCALER_Y;
	averagedData.uData.prxmt_1 = ((char)(sum[2]/SENSOR_BUFFER_SIZE) - PRXMT_OFFSET_1)*PRXMT_SCALER_1;
	
	return error;
}
byte sendData(){
	byte error;
	averagedData.uData.id = Hall_Effect_Bit_GetVal() ? 0xFF : 0x00;	//	Replace with hall pin
	error = AS1_SendBlock(averagedData.rData, 4, &dataBlockSize);
	return error;
}
