/*
 * OS_Sched_Tasks.c
 *
 *  Created on: 17/11/2017
 *      Author: uidj2522
 */

/******************************************
 * Interfaces
 ******************************************/
#include "OS_Sched_Tasks.h"
#include "app_ADC.h"


/******************************************
 * Code
 ******************************************/

/***********************************************
 * Function Name: app_OS_Sched_Task_1tk
 * Description: TBD
 ***********************************************/
void app_OS_Sched_Task_1tk(void)
{
	//Every 1 ms
	//app_LED_Task();

	/* Functions Executed Every Loop */
	//app_BtnDbnc_TaskMngr();

	/* DAC Task */
	//app_DAC_TaskMngr();

	/* ADC Task */
	app_ADC_Task();
}
