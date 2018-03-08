/*
 * app_Init.c
 *
 *  Created on: 23/10/2017
 *      Author: uidj2522
 */

/******************************************
 * Includes
 ******************************************/
#include "app_Init.h"
#include "app_GPIO.h"
#include "app_BtnDbnc.h"
#include "app_PIT.h"
#include "app_DAC.h"
#include "app_ADC.h"

/******************************************
 * Defines
 ******************************************/

/******************************************
 * Variables
 ******************************************/

/******************************************
 * Prototypes
 ******************************************/

/******************************************
 * Code
 ******************************************/

/***********************************************
 * Function Name: app_Init
 * Description: TBD
 ***********************************************/
void app_Init(void)
{
    /* PIT Module Init */
    app_PIT_Init();

    /* GPIO Module Init */
    app_GPIO_Init();

    /* DAC Module Init */
    app_DAC_Init();

    /* ADC Module Init */
    app_ADC_Init();

    /* Button Debounce App Init */
    app_BtnDbnc_Init();

}
