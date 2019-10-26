/*
 * main.c
 *
 *  Created on: Oct 21, 2019
 *      Author: AVE-LAP-069
 */

#include "led.h"
#include "pushButton.h"
#include "softwareDelay.h"
#include "timers.h"
#include "interruptLib.h"
#include "sevenSeg_BCD.h"
#include "MotorDC.h"

#include "avr/io.h"

/*
 * README:
 * 	- Requirements 1, 2, 3, 4, 5 are used in the other requirements starts from REQ_6
 * 	- Every requirement that test a specific functionality has a macro -> OPEN_REQ_x where x may be 6...14
 * 	- Un-Comment only one Macro to test a specific Requirement
 */

/* #define OPEN_REQ_6 */
/* #define OPEN_REQ_7 */
/* #define OPEN_REQ_9 */
/* #define OPEN_REQ_10 */
/* #define OPEN_REQ_12 */
/* #define OPEN_REQ_14	*/

/* @note: REQ_8 uses the timer delay but it tested in REQ_9 */

#ifdef OPEN_REQ_14
void timer_app_req10(void);


extern uint16 t0_extern_prescalarValue;
volatile uint32 ovf_times = 0;
volatile uint8 ovf_times_remainder = 0;
volatile uint64 counts;

TIMER0_OVF_Handler(){

	if(ovf_times <= 0){
		if(ovf_times_remainder <= 0){
			timer_app_req10();
			ovf_times = counts/256;
			ovf_times_remainder = counts % 256;
		}else{
			TCNT0 = 255 - ovf_times_remainder;
			ovf_times_remainder = 0;
		}

	}else{
		ovf_times --;
	}
}

int main(){

	SEI();
	Ave_timer0Init(T0_NORMAL_MODE, T0_OC0_DIS, T0_PRESCALER_256, 0, 0, T0_INTERRUPT_NORMAL);
	Ave_pushButton_Init(BTN_0);
	sevenSeg_Init();
	counts = ((5 * (F_CPU/(double)t0_extern_prescalarValue)/1000.0) - 1);
	ovf_times = counts/256;
	ovf_times_remainder = counts % 256;
	Ave_timer0Start();

	while(1){
		Ave_pushButton_Update();
	}

}
void timer_app_req10(void){
	static uint16 tick_count = 0;
	static uint16 press_count = 0;
	static uint8 displayedNumber = 0;
	static uint8 switchSegment = 0;



	switchSegment += SYS_TICK_MS;
	if(switchSegment == 5){
		sevenSeg_Write(SEG_0, displayedNumber%10);
	}
	if(switchSegment == 10){
		sevenSeg_Write(SEG_1, displayedNumber/10);
		switchSegment = 0;
	}

	tick_count += SYS_TICK_MS;
	if((Ave_pushButton_GetStatus(BTN_0) == Prereleased)){
		press_count ++;
		tick_count = 0;
	}

	if(tick_count == 1000){
		press_count = 0;
		tick_count = 0;
	}
	if(tick_count > 500){
		displayedNumber = press_count/(SYS_TICK_MS/5);
	}
	if((tick_count % 500) != 0){
		return;
	}

}
#endif

#ifdef OPEN_REQ_12
int main(void){
	uint8 speed = 0;
	uint8 ticks = 0;
	uint8 dirFlag = 0;
	Ave_timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_256, 0, 0, 0);
	MotorDC_Init(MOT_1);
	MotorDC_Dir(MOT_1, BACKWARD);
	MotorDC_Dir(MOT_2, BACKWARD);
	while(1){

		MotorDC_Speed(speed+40);
		Ave_timer0Delay_ms(1);
		ticks ++;
		if(ticks >= 9){
			ticks = 0;
			if(speed >= 59){
				dirFlag = 1;
			}
			if(dirFlag == 1){
				speed --;
				if(speed == 0){
					MotorDC_Dir(MOT_1, FORWARD);
					MotorDC_Dir(MOT_2, BACKWARD);
					ticks = 65;
					while(ticks --){
						MotorDC_Speed(80);
						Ave_timer0Delay_ms(1);
					}
					MotorDC_Dir(MOT_1, STOP);
					MotorDC_Dir(MOT_2, STOP);
					break;
				}
			}else{
				speed ++;
			}
			speed %= 60;
		}


	}

	return 0;
}

#endif


#ifdef OPEN_REQ_10
void timer_app_req10(void);

int main(void){

	Ave_timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_256, 0, 0, 0);
	Ave_pushButton_Init(BTN_0);
	sevenSeg_Init();

	while(1){
		Ave_pushButton_Update();
		timer_app_req10();
		Ave_timer0Delay_ms(SYS_TICK_MS);

	}

	return 0;
}
#endif

#ifdef OPEN_REQ_6
void led_app_req6(void);

int main(void){

	Led_Init(LED_1);
	Ave_pushButton_Init(BTN_1);

	while(1){
		Ave_pushButton_Update();

		led_app_req6();

		/*
		 * The following Line represent the system tick (or the heart beat system)
		 * @note: DON'T REMOVE IT
		 */
		Ave_SwDelay_ms(SYS_TICK_MS);
	}

	return 0;
}

#endif


#ifdef OPEN_REQ_7


typedef enum {
	GET_READY,
	GO,
	STOP
}Req7_States;

void led_app_req7(void);

int main(void){

	Led_Init(LED_0);
	Led_Init(LED_1);
	Led_Init(LED_2);

	while(1){
		led_app_req7();
		/*
		 * The following Line represent the system tick (or the heart beat system)
		 * @note: DON'T REMOVE IT
		 */
		Ave_SwDelay_ms(SYS_TICK_MS);

	}

	return 0;
}

#endif

#ifdef OPEN_REQ_9

typedef enum {
	GET_READY,
	GO,
	STOP
}Req9_States;

void timer_app_req9(void);

int main(void){

	Ave_timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_256, 0, 0, 0);
	Ave_pushButton_Init(BTN_1);

	Led_Init(LED_0);
	Led_Init(LED_1);
	Led_Init(LED_2);

	while(1){
		Ave_pushButton_Update();

		timer_app_req9();
		Ave_timer0Delay_ms(SYS_TICK_MS);

	}

	return 0;
}

#endif


#ifdef OPEN_REQ_7
void led_app_req7(void){
	static Req7_States state = 0;
	static uint16 tick_count = 0;

	tick_count += SYS_TICK_MS;

	if(tick_count != 1000){
		return;
	}
	tick_count = 0;
	switch(state){
	case GET_READY:{
		state = 1;
		Led_On(LED_0);
		Led_Off(LED_1);
		Led_Off(LED_2);
	}break;
	case GO:{
		state = 2;
		Led_Off(LED_0);
		Led_On(LED_1);
		Led_Off(LED_2);
	}break;
	case STOP:{
		state = 0;
		Led_Off(LED_0);
		Led_Off(LED_1);
		Led_On(LED_2);
	}break;
	}
}
#endif

#ifdef OPEN_REQ_10
void timer_app_req10(void){
	static uint16 tick_count = 0;
	static uint16 press_count = 0;
	static uint8 displayedNumber = 0;
	static uint8 switchSegment = 0;



	switchSegment += SYS_TICK_MS;
	if(switchSegment == 5){
		sevenSeg_Write(SEG_0, displayedNumber%10);
	}
	if(switchSegment == 10){
		sevenSeg_Write(SEG_1, displayedNumber/10);
		switchSegment = 0;
	}

	tick_count += SYS_TICK_MS;
	if((Ave_pushButton_GetStatus(BTN_0) == Prereleased)){
		press_count ++;
		tick_count = 0;
	}

	if(tick_count == 1000){
		press_count = 0;
		tick_count = 0;
	}
	if(tick_count > 500){
		displayedNumber = press_count/(SYS_TICK_MS/5);
	}
	if((tick_count % 500) != 0){
		return;
	}

}
#endif

#ifdef OPEN_REQ_9

void timer_app_req9(void){
	static Req9_States state = 0;
	static uint16 tick_count = 0;

	tick_count += SYS_TICK_MS;
	if((Ave_pushButton_GetStatus(BTN_1) == Pressed)){
		state = 2;
		tick_count = 1000;
	}
	if(tick_count != 1000){
		return;
	}

	tick_count = 0;
	switch(state){
	case GET_READY:{
		state = 1;
		Led_On(LED_0);
		Led_Off(LED_1);
		Led_Off(LED_2);
	}break;
	case GO:{
		state = 2;
		Led_Off(LED_0);
		Led_On(LED_1);
		Led_Off(LED_2);
	}break;
	case STOP:{
		state = 0;
		Led_Off(LED_0);
		Led_Off(LED_1);
		Led_On(LED_2);
	}break;
	}
}
#endif

#ifdef OPEN_REQ_7
void led_app_req6(void){
	static uint16 tick_count = 0;
	static uint8 counter = 0;
	BtnStatus_TypeDef btnState;
	btnState = Ave_pushButton_GetStatus(BTN_1);

	if(btnState == Prepressed){
		counter ++;
	}

	tick_count += 20;

	if(tick_count != 1000){
		return;
	}

	tick_count = 0;
	if(counter > 0){

		Led_On(LED_1);
		btnState = Ave_pushButton_GetStatus(BTN_1);
		if(btnState != Pressed){
			counter --;
		}
	}else {
		Led_Off(LED_1);
	}


}
#endif
