/*
 * app_ADC.c
 *
 *  Created on: 07/03/2018
 *      Author: uidj2522
 */

 /******************************************
 * Interfaces
 ******************************************/
#include "stdtypedef.h"
#include "fsl_adc16.h"
#include "app_ADC.h"

 /******************************************
 * Private Macros
 ******************************************/
#define APP_ADC_CHANNEL 		0u
#define APP_ADC_CHANNEL_GROUP 	0u
 
 /******************************************
 * Private Typedef
 ******************************************/
 
 /******************************************
 * Public Const
 ******************************************/
 
 /******************************************
 * Private Const
 ******************************************/
 
 /******************************************
 * Public Variables
 ******************************************/
 
 /******************************************
 * Private Variables
 ******************************************/
static T_UWORD ruw_ADCValue = 0u;
static T_UBYTE rub_ConversionInProgressFlag = FALSE;
 
 /******************************************
 * Private Prototypes
 ******************************************/
static void app_ADC_Trigger(void);
static T_UBYTE app_ADC_IsConversionCompleted(void);
static T_UWORD app_ADC_GetValue(void);

 /******************************************
 * Code
 ******************************************/

/***********************************************
 * Function Name: app_ADC_Init
 * Description: TBD
 ***********************************************/
void app_ADC_Init(void)
{
	adc16_config_t ls_ADCConfig;

	//Initialize structure with default values
	ADC16_GetDefaultConfig(&ls_ADCConfig);

	//Init ADC Module
	ADC16_Init(ADC0, &ls_ADCConfig);

	//Disable Hardware Trigger
	ADC16_EnableHardwareTrigger(ADC0, FALSE); /* Make sure the software trigger is used. */

	//Perform Autocalibration
	(void)ADC16_DoAutoCalibration(ADC0);
}

/***********************************************
 * Function Name: app_ADC_Trigger
 * Description: TBD
 ***********************************************/
static void app_ADC_Trigger(void)
{
	adc16_channel_config_t ls_ChannelConfig;

	//Channel Selection
	ls_ChannelConfig.channelNumber = APP_ADC_CHANNEL;

	//Disable Interrupt when Conversion is completed
	ls_ChannelConfig.enableInterruptOnConversionCompleted = FALSE;

	//Disable Differential Conversion
	ls_ChannelConfig.enableDifferentialConversion = FALSE;

	ADC16_SetChannelConfig(ADC0, APP_ADC_CHANNEL_GROUP, &ls_ChannelConfig);
}

/***********************************************
 * Function Name: app_ADC_IsConversionCompleted
 * Description: TBD
 ***********************************************/
static T_UBYTE app_ADC_IsConversionCompleted(void)
{
	T_UBYTE lub_Return;

	lub_Return = FALSE;

	//Check if Conversion was completed
	if(kADC16_ChannelConversionDoneFlag &
			ADC16_GetChannelStatusFlags(ADC0, APP_ADC_CHANNEL_GROUP))
	{
		//Conversion Completed
		lub_Return = TRUE;
	}
	else
	{
		//Conversion not completed
		lub_Return = FALSE;
	}

	return lub_Return;
}

/***********************************************
 * Function Name: app_ADC_GetValue
 * Description: TBD
 ***********************************************/
static T_UWORD app_ADC_GetValue(void)
{
	//Return Last Conversion Value
	return ADC16_GetChannelConversionValue(ADC0, APP_ADC_CHANNEL_GROUP);
}

/***********************************************
 * Function Name: app_ADC_Task
 * Description: TBD
 ***********************************************/
void app_ADC_Task(void)
{
	//Check if a conversion is in progress
	if(TRUE == rub_ConversionInProgressFlag)
	{
		//Check if Conversion was completed
		if(TRUE == app_ADC_IsConversionCompleted())
		{
			//Store the ADC Value
			ruw_ADCValue = app_ADC_GetValue();

			//Clear conversion in progress flag
			rub_ConversionInProgressFlag = FALSE;
		}
		else
		{
			/* Do nothing */
		}
	}
	else
	{
		//Trigger the ADC Conversion
		app_ADC_Trigger();

		//Set Conversion in progress flag
		rub_ConversionInProgressFlag = TRUE;
	}
}

