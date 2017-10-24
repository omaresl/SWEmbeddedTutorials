/*
 * app_LED.c
 *
 *  Created on: 23/10/2017
 *      Author: uidj2522
 */

/******************************************
 * Includes
 ******************************************/
#include "MKL25Z4.h"
#include "stdtypedef.h"
#include "app_LED.h"

/******************************************
 * Defines
 ******************************************/

/******************************************
 * Variables
 ******************************************/
static T_UBYTE rub_LEDTaskCounter = 0U;

/******************************************
 * Prototypes
 ******************************************/

/******************************************
 * Code
 ******************************************/

void app_LED_Task(void)
{
	/* Check if the task has been called 100 times since last execution */
	if(rub_LEDTaskCounter >= 100U)
	{//100 times passed already
		/* Clear Counter */
		rub_LEDTaskCounter = 0U;

		/* LED Toggle */
		LED_RED_TOGGLE();
	}
	else
	{//100 times not passed yet
		/* Increase Counter */
		rub_LEDTaskCounter++;
	}
}
