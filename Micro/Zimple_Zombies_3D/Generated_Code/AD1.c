/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : AD1.c
**     Project     : Zimple_Zombies_3D
**     Processor   : MC9S08QE128CLK
**     Component   : ADC
**     Version     : Component 01.697, Driver 01.30, CPU db: 3.00.067
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2016-02-15, 18:38, # CodeGen: 17
**     Abstract    :
**         This device "ADC" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
**     Settings    :
**          Component name                                 : AD1
**          A/D converter                                  : ADC
**          Sharing                                        : Disabled
**          Interrupt service/event                        : Enabled
**            A/D interrupt                                : Vadc
**            A/D interrupt priority                       : medium priority
**          A/D channels                                   : 3
**            Channel0                                     : 
**              A/D channel (pin)                          : PTA0_KBI1P0_TPM1CH0_ADP0_ACMP1PLUS
**              A/D channel (pin) signal                   : 
**            Channel1                                     : 
**              A/D channel (pin)                          : PTA1_KBI1P1_TPM2CH0_ADP1_ACMP1MINUS
**              A/D channel (pin) signal                   : 
**            Channel2                                     : 
**              A/D channel (pin)                          : PTF0_ADP10
**              A/D channel (pin) signal                   : 
**          A/D resolution                                 : 8 bits
**          Conversion time                                : 4.768372 �s
**          Low-power mode                                 : Disabled
**          Sample time                                    : short
**          Internal trigger                               : Disabled
**          Number of conversions                          : 1
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Events enabled in init.                      : yes
**          CPU clock/speed selection                      : 
**            High speed mode                              : This component enabled
**            Low speed mode                               : This component disabled
**            Slow speed mode                              : This component disabled
**          High input limit                               : 1
**          Low input limit                                : 0
**          Get value directly                             : yes
**          Wait for result                                : yes
**     Contents    :
**         MeasureChan  - byte AD1_MeasureChan(bool WaitForResult, byte Channel);
**         GetChanValue - byte AD1_GetChanValue(byte Channel, void* Value);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file AD1.c
** @version 01.30
** @brief
**         This device "ADC" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
*/         
/*!
**  @addtogroup AD1_module AD1 module documentation
**  @{
*/         


/* MODULE AD1. */

#include "Events.h"
#include "AD1.h"



#define STOP            0x00U          /* STOP state           */
#define MEASURE         0x01U          /* MESURE state         */
#define CONTINUOUS      0x02U          /* CONTINUOS state      */
#define SINGLE          0x03U          /* SINGLE state         */

static const  byte Table[3] = {0x01U,0x02U,0x04U};  /* Table of mask constants */

static const  byte Channels[3] = {0x40U,0x41U,0x4AU};  /* Contents for the device control register */

static volatile byte OutFlg;           /* Measurement finish flag */
static volatile byte SumChan;          /* Number of measured channels */
static volatile byte ModeFlg;          /* Current state of device */

volatile byte AD1_OutV[3];             /* Sum of measured values */





/*
** ===================================================================
**     Method      :  AD1_Interrupt (component ADC)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
ISR(AD1_Interrupt)
{
  AD1_OutV[SumChan] = ADCRL;           /* Save measured value */
    /*lint -save  -e740 -e931 Disable MISRA rule (1.2) checking. */
    OutFlg |= Table[SumChan];          /* Value of measured channel is available */
    /*lint -restore Enable MISRA rule (1.2) checking. */
    AD1_OnEnd();                       /* Invoke user event */
    ModeFlg = STOP;                    /* Set the device to the stop mode */
}

/*
** ===================================================================
**     Method      :  AD1_HWEnDi (component ADC)
**
**     Description :
**         Enables or disables the peripheral(s) associated with the 
**         component. The method is called automatically as a part of the 
**         Enable and Disable methods and several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void AD1_HWEnDi(void)
{
  if (ModeFlg) {                       /* Start or stop measurement? */
    /*lint -save  -e740 -e931 Disable MISRA rule (1.2) checking. */
    OutFlg &= (byte)(~(byte)Table[SumChan]); /* Output value isn't available */
    /*lint -restore Enable MISRA rule (1.2) checking. */
    AD1_OutV[SumChan] = 0U;            /* Set variable for storing measured values to 0 */
    ADCSC1 = Channels[SumChan];        /* If yes then start the conversion */
  }
}

/*
** ===================================================================
**     Method      :  AD1_MeasureChan (component ADC)
*/
/*!
**     @brief
**         This method performs measurement on one channel. (Note: If
**         the [number of conversions] is more than one the conversion
**         of the A/D channel is performed specified number of times.)
**     @param
**         WaitForResult   - Wait for a result of
**                           conversion. If the [interrupt service] is
**                           disabled and at the same time a [number of
**                           conversions] is greater than 1, the
**                           WaitForResult parameter is ignored and the
**                           method waits for each result every time.
**     @param
**         Channel         - Channel number. If only one
**                           channel in the component is set this
**                           parameter is ignored, because the parameter
**                           is set inside this method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSY - A conversion is already running
**                           ERR_RANGE - Parameter "Channel" out of range
*/
/* ===================================================================*/
byte AD1_MeasureChan(bool WaitForResult,byte Channel)
{
  if (Channel >= 3U) {                 /* Is channel number greater than or equal to 3 */
    return ERR_RANGE;                  /* If yes then error */
  }
  if (ModeFlg != STOP) {               /* Is the device in different mode than "stop"? */
    return ERR_BUSY;                   /* If yes then error */
  }
  ModeFlg = SINGLE;                    /* Set state of device to the measure mode */
  SumChan = Channel;                   /* Set required channel */
  AD1_HWEnDi();                        /* Enable the device */
  if (WaitForResult) {                 /* Is WaitForResult TRUE? */
    while (ModeFlg == SINGLE) {}       /* If yes then wait for end of measurement */
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AD1_GetChanValue (component ADC)
*/
/*!
**     @brief
**         Returns the last measured value of the required channel.
**         Format and width of the value is a native format of the A/D
**         converter.
**     @param
**         Channel         - Channel number. If only one
**                           channel in the component is set then this
**                           parameter is ignored.
**     @param
**         Value           - Pointer to the measured value. Data
**                           type is a byte, a word or an int. It
**                           depends on the supported modes, resolution,
**                           etc. of the AD converter. See the Version
**                           specific information for the current CPU in
**                           [General Info].
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_NOTAVAIL - Requested value not
**                           available
**                           ERR_RANGE - Parameter "Channel" out of
**                           range
**                           ERR_OVERRUN - External trigger overrun flag
**                           was detected after the last value(s) was
**                           obtained (for example by GetValue). This
**                           error may not be supported on some CPUs
**                           (see generated code).
*/
/* ===================================================================*/
byte AD1_GetChanValue(byte Channel,void* Value)
{
  if (Channel >= 3U) {                 /* Is channel number greater than or equal to 3 */
    return ERR_RANGE;                  /* If yes then error */
  }
  if ((OutFlg & Table[Channel]) == 0U) { /* Is output flag set? */
    return ERR_NOTAVAIL;               /* If no then error */
  }
  *(byte*)Value = AD1_OutV[Channel];   /* Save measured values to the output buffer */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AD1_Init (component ADC)
**
**     Description :
**         Initializes the associated peripheral(s) and the component's 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void AD1_Init(void)
{
  /* ADCSC1: COCO=0,AIEN=0,ADCO=0,ADCH4=1,ADCH3=1,ADCH2=1,ADCH1=1,ADCH0=1 */
  setReg8(ADCSC1, 0x1FU);              /* Disable the module */ 
  /* ADCSC2: ADACT=0,ADTRG=0,ACFE=0,ACFGT=0,??=0,??=0,??=0,??=0 */
  setReg8(ADCSC2, 0x00U);              /* Disable HW trigger and autocompare */ 
  OutFlg = 0U;                         /* No measured value */
  SumChan = 0U;
  ModeFlg = STOP;                      /* Device isn't running */
  /* ADCCFG: ADLPC=0,ADIV1=1,ADIV0=0,ADLSMP=0,MODE1=0,MODE0=0,ADICLK1=0,ADICLK0=0 */
  setReg8(ADCCFG, 0x40U);              /* Set prescaler bits */ 
}


/* END AD1. */

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
