/*
 * app_GPIO.c
 *
 *  Created on: 14/10/2017
 *      Author: uidj2522
 */

#include "stdio.h"
#include "MKL25Z4.h"
#include "stdtypedef.h"
#include "app_GPIO.h"
#include "fsl_clock.h"
#include "fsl_port.h"
#include "fsl_gpio.h"

void app_GPIO_Init(void)
{
	/* Enable the clock for the modules needed */
	/* Habilitar los relojes de los modulos necesarios */

	CLOCK_EnableClock(kCLOCK_PortC); //Habilitar reloj para el modulo del puerto C
	CLOCK_EnableClock(kCLOCK_PortB);
	/*
	 * (*(volatile T_ULONG)(0x40048038)) |= (1U << 11U)
	 */

	/* PORT Module Configuration for PORTC */
	/* Configuracion de modulo PORT para PUERTO C */

	port_pin_config_t ls_PinConfig;

	ls_PinConfig.mux = kPORT_MuxAsGpio;

	port_pin_config_t *lps_PinConfig;

	lps_PinConfig = &ls_PinConfig;

	PORT_SetPinConfig(PORTC, 9U, lps_PinConfig); //Configuracion de funcionalidad del PIN
	PORT_SetPinConfig(PORTB, 19U, lps_PinConfig); //Configuracion de funcionalidad del PIN
	/*
	 * (*(volatile T_ULONG)(0x4004B024)) |= (0x01U << 8U)
	 */

	/* GPIO Configuration for PTC9 as Input */
	/* Configuracion de GPIO para PTC9 como entrada */

	gpio_pin_config_t ls_GPIOPinConfig;

	ls_GPIOPinConfig.pinDirection = kGPIO_DigitalInput;
	ls_GPIOPinConfig.outputLogic = FALSE;

	gpio_pin_config_t *lps_GPIOPinConfig;

	lps_GPIOPinConfig = &ls_GPIOPinConfig;

	GPIO_PinInit(GPIOC, 9U, lps_GPIOPinConfig);

	ls_GPIOPinConfig.pinDirection = kGPIO_DigitalOutput;
	ls_GPIOPinConfig.outputLogic = TRUE;
	GPIO_PinInit(GPIOB, 19U, lps_GPIOPinConfig);
	/*
	 * (*(volatile T_ULONG)(0x400FF094)) &= ~(0x01U << 9U)
	 */

}

T_UBYTE app_GPIO_GetPinValue(GPIO_Type *lps_BaseAddress, T_UBYTE lub_PinNumber)
{
	T_UBYTE lub_PinValue;

	lub_PinValue = (T_UBYTE)GPIO_ReadPinInput(lps_BaseAddress, lub_PinNumber);
	/*
	 * lub_PinValue = ((*(volatile T_ULONG)(0x400FF090) >> 9U) & 0x01U;
	 */

	if(lub_PinValue == TRUE)
	{
		GPIO_ClearPinsOutput(GPIOB, 1U << 19U); //LED Verde encendido
	}
	else
	{//lub_PinValue == FALSE
		GPIO_SetPinsOutput(GPIOB, 1U << 19U); //LED Verde Apagado
	}

	return lub_PinValue;
}
