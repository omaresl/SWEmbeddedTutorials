/*
 * app_PIT.c
 *
 *  Created on: 23/10/2017
 *      Author: uidj2522
 */


/******************************************
 * Includes
 ******************************************/
#include "MKL25Z4.h"
#include "stdtypedef.h"
#include "app_PIT.h"
#include "fsl_pit.h"

/******************************************
 * Defines
 ******************************************/

/******************************************
 * Variables
 ******************************************/
T_UBYTE	rub_PITAlarm;

/******************************************
 * Prototypes
 ******************************************/


/******************************************
 * Code
 ******************************************/

/***********************************************
 * Function Name: app_PIT_Init
 * Description: Function that initializes the
 * PIT Module.
 ***********************************************/
void app_PIT_Init(void)
{
	pit_config_t ls_PitConfig;

	/* Get Default Config */
	PIT_GetDefaultConfig(&ls_PitConfig);

	/* PIT Init */
	PIT_Init(PIT, &ls_PitConfig);

	/* PIT Set Period at 1 ms*/
	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, USEC_TO_COUNT(1000,CLOCK_GetFreq(kCLOCK_BusClk)));

	/* Enable PIT Interrutps */
	PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);

	/* Enable at the NVIC */
	EnableIRQ(PIT_IRQn);

	/* Start Timer */
	PIT_StartTimer(PIT, kPIT_Chnl_0);
}

/***********************************************
 * Function Name: PIT_IRQHandler
 * Description: PIT IRQ Handler
 ***********************************************/
void PIT_IRQHandler(void)
{
	/* Clear Interrupt Flag */
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
	/* Set PIT Alarm */
	rub_PITAlarm = TRUE;
}
