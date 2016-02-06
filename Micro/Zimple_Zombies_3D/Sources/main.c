/* ###################################################################
**     Filename    : main.c
**     Project     : Zimple_Zombies_3D
**     Processor   : MC9S08QE128CLK
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2016-01-19, 00:35, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.12
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


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

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "ZimpleZombies.h"

extern byte PROGRAM_STATE;
extern volatile accel_u accel;

void main(void)
{
  /* Write your local variable definition here */
	byte error = 0;
	PROGRAM_STATE = STATE_SETUP;
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  while(TRUE){
	  switch(PROGRAM_STATE){
	  case STATE_SETUP:
		  PROGRAM_STATE = STATE_IDLE;
		  break;
	  case STATE_MEASURE_ACCEL:
		  error = AD1_MeasureChan(ADC_HOLD, ADC_ACCEL_X);
		  PROGRAM_STATE = STATE_WORK_ACCEL;
		  break;
	  case STATE_MEASURE_FLEX:
		  break;
	  case STATE_WORK_ACCEL:
		  error = AD1_GetChanValue(ADC_ACCEL_X, &accel.sData.x);
		  PROGRAM_STATE = STATE_SEND_ACCEL;
		  break;
	  case STATE_WORK_FLEX:
		  break;
	  case STATE_SEND_ACCEL:
		  sendData(ID_ACCEL);
		  break;
	  case STATE_SEND_FLEX:
		  break;
	  case STATE_IDLE:
	  default:
		  break;
	  }
  }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
