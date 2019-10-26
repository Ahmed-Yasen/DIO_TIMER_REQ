/*
 * pushButton.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Think
 */

#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_
#include "pushButtonConfig.h"
#include "softwareDelay.h"

typedef enum{
	BTN_0,
	BTN_1,
	BTN_2,
	BTN_3
}BtnId_TypeDef;

typedef enum{
	Released,
	Prepressed,
	Pressed,
	Prereleased

}BtnStatus_TypeDef;

/**
 * Description: Initialize the BTN_x Pin state (where x 0, 1, 2, 3) to Input
 * @param btn_id: The btn to be initialized and it takes
 * 				  one of the enum (BtnId_TypeDef) parameters
 *
 */
void Ave_pushButton_Init(BtnId_TypeDef btn_id);
/**
 * Description: read all BTN_x (where x 0, 1, 2, 3) states and store it in the program
 *
 * @note : this function must be called in the system tick hundler or in the super loop hundler
 */
void Ave_pushButton_Update(void);
/**
 * Description: read BTN_x (where x 0, 1, 2, 3) state which is stored in the program
 * 				in the update function
 *
 */
BtnStatus_TypeDef Ave_pushButton_GetStatus(BtnId_TypeDef btn_id);

#endif /* PUSHBUTTON_H_ */
