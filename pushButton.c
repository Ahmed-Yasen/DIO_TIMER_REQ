/*
 * pushButton.c
 *
 *  Created on: Oct 21, 2019
 *      Author: Think
 */


#include "pushButton.h"


#define BTN_CHK_PERIOD (20)
#define ReleasedLevel	(0)
#define PressedLevel	(1)
typedef struct{
	uint8 BTN_Samples[2];
	BtnStatus_TypeDef BtnState;
}BTN_TypeDef;

BTN_TypeDef BTN[BTN_MAX_NUM];




static uint8 Ave_pushButton_Read(BtnId_TypeDef btn_id);



void Ave_pushButton_Init(BtnId_TypeDef btn_id){
	switch(btn_id){
	case BTN_0:{
		Ave_gpioPinDirection(BTN_0_GPIO, BTN_0_BIT, INPUT);
	}break;
	case BTN_1:{
		Ave_gpioPinDirection(BTN_1_GPIO, BTN_1_BIT, INPUT);
	}break;
	case BTN_2:{
		Ave_gpioPinDirection(BTN_2_GPIO, BTN_2_BIT, INPUT);
	}break;
	case BTN_3:{
		Ave_gpioPinDirection(BTN_3_GPIO, BTN_3_BIT, INPUT);
	}break;
	}

	for(uint8 loopIndex = 0; loopIndex < BTN_MAX_NUM; loopIndex ++){
		BTN[loopIndex].BTN_Samples[0] = ReleasedLevel;
		BTN[loopIndex].BTN_Samples[1] = ReleasedLevel;
		BTN[loopIndex].BtnState = Released;
	}

}

void Ave_pushButton_Update(void){
	static uint16 tick_counter = 0;
	uint8 loopIndex = 0;
	tick_counter += SYS_TICK_MS;


	if(tick_counter != BTN_CHK_PERIOD){
		return;
	}

	tick_counter = 0;


	for(loopIndex = 0; loopIndex < BTN_MAX_NUM; loopIndex ++){
		BTN[loopIndex].BTN_Samples[0] = BTN[loopIndex].BTN_Samples[1];
		BTN[loopIndex].BTN_Samples[1] = Ave_pushButton_Read(loopIndex);

		switch(BTN[loopIndex].BtnState){

		case Released:{
			if((BTN[loopIndex].BTN_Samples[0] == PressedLevel) &&
					(BTN[loopIndex].BTN_Samples[1] == PressedLevel)){
				BTN[loopIndex].BtnState = Prepressed;
			}
		}break;
		case Prepressed:{
			if(BTN[loopIndex].BTN_Samples[1] == PressedLevel){
				BTN[loopIndex].BtnState = Pressed;
			}
		}break;
		case Pressed:{
			if((BTN[loopIndex].BTN_Samples[0] == ReleasedLevel) &&
					(BTN[loopIndex].BTN_Samples[1] == ReleasedLevel)){
				BTN[loopIndex].BtnState = Prereleased;
			}
		}break;
		case Prereleased:{
			if(BTN[loopIndex].BTN_Samples[1] == ReleasedLevel){
				BTN[loopIndex].BtnState = Released;
			}
		}break;
		}
	}

}


static uint8 Ave_pushButton_Read(BtnId_TypeDef btn_id){
	uint8 status = 0;

	switch(btn_id){
	case BTN_0:{
		status = Ave_gpioPinRead(BTN_0_GPIO, BTN_0_BIT);
	}break;
	case BTN_1:{
		status = Ave_gpioPinRead(BTN_1_GPIO, BTN_1_BIT);
	}break;
	case BTN_2:{
		status = Ave_gpioPinRead(BTN_2_GPIO, BTN_2_BIT);
	}break;
	case BTN_3:{
		status = Ave_gpioPinRead(BTN_3_GPIO, BTN_3_BIT);
	}break;
	}
	return status;
}

BtnStatus_TypeDef Ave_pushButton_GetStatus(BtnId_TypeDef btn_id){
	return BTN[btn_id].BtnState;
}
