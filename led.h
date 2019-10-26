/*
 * led.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Think
 */

#ifndef LED_H_
#define LED_H_

#include "gpio.h"
#include "std_types.h"
#include "ledConfig.h"

typedef enum{
	LED_0,
	LED_1,
	LED_2,
	LED_3
}LedId_TypeDef;

/**
 * Description: Initialize the LED_x (where x 0, 1, 2, 3) as output
 * @param led_id: The led to be initialized and it takes
 * 				  one of the enum (LedId_TypeDef) parameters
 *
 */
void Led_Init(LedId_TypeDef led_id);
/**
 * Description: Change the LED_x state (where x 0, 1, 2, 3) to be on
 * @param led_id: The led to be initialized and it takes
 * 				  one of the enum (LedId_TypeDef) parameters
 *
 */
void Led_On(LedId_TypeDef led_id);
/**
 * Description: Change the LED_x state (where x 0, 1, 2, 3) to be off
 * @param led_id: The led to be initialized and it takes
 * 				  one of the enum (LedId_TypeDef) parameters
 *
 */
void Led_Off(LedId_TypeDef led_id);
/**
 * Description: Toggle the LED_x state (where x 0, 1, 2, 3)
 * @param led_id: The led to be initialized and it takes
 * 				  one of the enum (LedId_TypeDef) parameters
 *
 */
void Led_Toggle(LedId_TypeDef led_id);



#endif /* LED_H_ */
