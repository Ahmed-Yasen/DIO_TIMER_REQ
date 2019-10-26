/*
 * MotorDC.c
 *
 *  Created on: Oct 26, 2019
 *      Author: Think
 */


#include "MotorDC.h"

void MotorDC_Init(MOTOR_TypeDef MOT_x){
	Ave_gpioPinDirection(MOTOR_EN_1_GPIO, MOTOR_EN_1_BIT, OUTPUT);
	Ave_gpioPinDirection(MOTOR_EN_2_GPIO, MOTOR_EN_2_BIT, OUTPUT);

	Ave_gpioPinDirection(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, OUTPUT);
	Ave_gpioPinDirection(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, OUTPUT);
	Ave_gpioPinDirection(MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT, OUTPUT);
	Ave_gpioPinDirection(MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT, OUTPUT);
}
void MotorDC_Dir(MOTOR_TypeDef MOT_x, MOTOR_DIR_TypeDef dir){

	if(MOT_x == MOT_1){
		switch(dir){
		case STOP:{
			Ave_gpioPinWrite(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, LOW);
			Ave_gpioPinWrite(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, LOW);
		}break;
		case FORWARD:{
			Ave_gpioPinWrite(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, HIGH);
			Ave_gpioPinWrite(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, LOW);
		}break;
		case BACKWARD:{
			Ave_gpioPinWrite(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, LOW);
			Ave_gpioPinWrite(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, HIGH);
		}break;
		}

	}else if(MOT_x == MOT_2){
		switch(dir){
				case STOP:{
					Ave_gpioPinWrite(MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT, LOW);
					Ave_gpioPinWrite(MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT, LOW);
				}break;
				case FORWARD:{
					Ave_gpioPinWrite(MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT, LOW);
					Ave_gpioPinWrite(MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT, HIGH);
				}break;
				case BACKWARD:{
					Ave_gpioPinWrite(MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT, HIGH);
					Ave_gpioPinWrite(MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT, LOW);
				}break;
				}
	}
}

void MotorDC_Speed(uint8 speed){
	uint16 off = (speed/100.0) * 255;
	uint16 on = 255 - off;

	Ave_gpioPinWrite(MOTOR_EN_1_GPIO, MOTOR_EN_1_BIT, HIGH);
	Ave_gpioPinWrite(MOTOR_EN_2_GPIO, MOTOR_EN_2_BIT, HIGH);
	TCNT0 = on;
	Ave_timer0Start();
	while((TIFR & 0x01) == 0);
	Ave_timer0Stop();
	TIFR |= 0x01;

	Ave_gpioPinWrite(MOTOR_EN_1_GPIO, MOTOR_EN_1_BIT, LOW);
	Ave_gpioPinWrite(MOTOR_EN_2_GPIO, MOTOR_EN_2_BIT, LOW);
	TCNT0 = off;
	Ave_timer0Start();
	while((TIFR & 0x01) == 0);
	Ave_timer0Stop();

	TIFR |= 0x01;

}
