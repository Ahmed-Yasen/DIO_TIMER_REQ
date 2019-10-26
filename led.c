/*
 * led.c
 *
 *  Created on: Oct 21, 2019
 *      Author: Think
 */


#include "led.h"

void Led_Init(LedId_TypeDef led_id){
	switch(led_id){
	case LED_0:{
		Ave_gpioPinDirection(LED_0_GPIO, LED_0_BIT, OUTPUT);
	}break;
	case LED_1:{
		Ave_gpioPinDirection(LED_1_GPIO, LED_1_BIT, OUTPUT);
	}break;
	case LED_2:{
		Ave_gpioPinDirection(LED_2_GPIO, LED_2_BIT, OUTPUT);
	}break;
	case LED_3:{
		Ave_gpioPinDirection(LED_3_GPIO, LED_3_BIT, OUTPUT);
	}break;

	}
}
void Led_On(LedId_TypeDef led_id){
	switch(led_id){
	case LED_0:{
		Ave_gpioPinWrite(LED_0_GPIO, LED_0_BIT, HIGH);
	}break;
	case LED_1:{
		Ave_gpioPinWrite(LED_1_GPIO, LED_1_BIT, HIGH);
	}break;
	case LED_2:{
		Ave_gpioPinWrite(LED_2_GPIO, LED_2_BIT, HIGH);
	}break;
	case LED_3:{
		Ave_gpioPinWrite(LED_3_GPIO, LED_3_BIT, HIGH);
	}break;

	}
}
void Led_Off(LedId_TypeDef led_id){
	switch(led_id){
	case LED_0:{
		Ave_gpioPinWrite(LED_0_GPIO, LED_0_BIT, LOW);
	}break;
	case LED_1:{
		Ave_gpioPinWrite(LED_1_GPIO, LED_1_BIT, LOW);
	}break;
	case LED_2:{
		Ave_gpioPinWrite(LED_2_GPIO, LED_2_BIT, LOW);
	}break;
	case LED_3:{
		Ave_gpioPinWrite(LED_3_GPIO, LED_3_BIT, LOW);
	}break;

	}
}

void Led_Toggle(LedId_TypeDef led_id){
	switch(led_id){
	case LED_0:{
		Ave_gpioPinToggle(LED_0_GPIO, LED_0_BIT);
	}break;
	case LED_1:{
		Ave_gpioPinToggle(LED_1_GPIO, LED_1_BIT);
	}break;
	case LED_2:{
		Ave_gpioPinToggle(LED_2_GPIO, LED_2_BIT);
	}break;
	case LED_3:{
		Ave_gpioPinToggle(LED_3_GPIO, LED_3_BIT);
	}break;

	}
}


