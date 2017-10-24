/*
 * app_LED.h
 *
 *  Created on: 20/10/2017
 *      Author: uidj2522
 */

#ifndef APP_LED_H_
#define APP_LED_H_

#include "fsl_gpio.h"

/******************************************
 * Defines
 ******************************************/
#define LED_RED_ON()	GPIO_ClearPinsOutput(GPIOB, 1U << 18U)
#define LED_RED_OFF()	GPIO_SetPinsOutput(GPIOB, 1U << 18U)
#define LED_RED_TOGGLE()	GPIO_TogglePinsOutput(GPIOB, 1U << 18U)

#define LED_GREEN_ON()	GPIO_ClearPinsOutput(GPIOB, 1U << 19U)
#define LED_GREEN_OFF()	GPIO_SetPinsOutput(GPIOB, 1U << 19U)

#define LED_BLUE_ON()	GPIO_ClearPinsOutput(GPIOD, 1U << 1U)
#define LED_BLUE_OFF()	GPIO_SetPinsOutput(GPIOD, 1U << 1U)

/******************************************
 * Prototypes
 ******************************************/
extern void app_LED_Task(void);

#endif /* APP_LED_H_ */
