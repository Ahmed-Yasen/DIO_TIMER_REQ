/*
 * MotorDC.h
 *
 *  Created on: Oct 26, 2019
 *      Author: Think
 */

#ifndef MOTORDC_H_
#define MOTORDC_H_
#include "MotorDC_CFG.h"
#include "timers.h"

typedef enum {
	MOT_1,
	MOT_2
}MOTOR_TypeDef;

typedef enum {
	STOP,
	FORWARD,
	BACKWARD
}MOTOR_DIR_TypeDef;

void MotorDC_Init(MOTOR_TypeDef MOT_x);
void MotorDC_Dir(MOTOR_TypeDef MOT_x, MOTOR_DIR_TypeDef dir);
void MotorDC_Speed(uint8 speed);

#endif /* MOTORDC_H_ */
