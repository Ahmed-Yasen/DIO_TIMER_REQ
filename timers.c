/*
 * timers.c
 *
 *  Created on: Oct 22, 2019
 *      Author: Think
 */


#include "timers.h"

uint16 t0_extern_prescalarValue;

static uint16 t0_global_prescalar_value;
static uint8 t0_global_prescalar;

static uint16 t1_global_prescalar_value;
static uint8 t1_global_prescalar;

static uint16 t2_global_prescalar_value;
static uint8 t2_global_prescalar;

void Ave_timer0Init(T0_MODE mode,T0_COM OC0,T0_PRESCALER prescal, uint8 initialValue, uint8 outputCompare, uint8 interruptMask){
	uint8 control = mode|OC0|prescal;
	TCCR0 = (control & 0xf8);
	TCNT0 = initialValue;
	OCR0 = outputCompare;
	TIMSK |= interruptMask;

	t0_global_prescalar = control & 0x07;

	switch(prescal){
	case T0_NO_CLOCK:{
		//do nothing
	}break;
	case T0_PRESCALER_NO:{
		t0_global_prescalar_value = 1;
	}break;
	case T0_PRESCALER_8:{
		t0_global_prescalar_value = 8;
	}break;
	case T0_PRESCALER_64:{
		t0_global_prescalar_value = 64;
	}break;
	case T0_PRESCALER_256:{
		t0_global_prescalar_value = 256;
	}break;
	case T0_PRESCALER_1024:{
		t0_global_prescalar_value = 1024;
	}break;
	}
	t0_extern_prescalarValue = t0_global_prescalar_value;
}

void Ave_timer0Set(uint8 value){
	TCNT0 = value;
}

uint8 Ave_timer0Read(void){
	return TCNT0;
}

void Ave_timer0Start(void){

	TCCR0 |= t0_global_prescalar;


}

void Ave_timer0Stop(void){
	TCCR0 &= ~(0x07);
}


void Ave_timer0Delay_ms(uint16 delay){
	uint64 counts = 0;

	uint8 mode;
	uint32 ovf_times = 0;
	uint8 ovf_times_remainder = 0;

	counts = ((delay * (F_CPU/(double)t0_global_prescalar_value)/1000.0) - 1);//=3905


	mode = TCCR0 & 0x48;
	if(mode == T0_COMP_MODE){
		ovf_times = counts/OCR0;//=15
		ovf_times_remainder = counts % OCR0;//=65
	}else if(mode == T0_NORMAL_MODE){
		ovf_times = counts/256;//=15
		ovf_times_remainder = counts % 256;//=65
	}
	Ave_timer0Start();

	if(mode == T0_COMP_MODE){
		while(ovf_times > 0){

			while((TIFR & 0x02) == 0);

			TIFR |= 0x02;

			ovf_times --;

		}
	}else if(mode == T0_NORMAL_MODE){
		while(ovf_times > 0){

			while((TIFR & 0x01) == 0);

			TIFR |= 0x01;

			ovf_times --;

		}
	}


	if(mode == T0_COMP_MODE){
		TCNT0 = OCR0 - ovf_times_remainder;
		while((TIFR & 0x01) == 0);
		TIFR |= 0x01;
	}else if(mode == T0_NORMAL_MODE){
		TCNT0 = 256 - ovf_times_remainder;
		while((TIFR & 0x01) == 0);
		TIFR |= 0x01;
	}




	Ave_timer0Stop();


}

void Ave_timer0SwPWM(uint8 dutyCycle,uint8 freq){

	uint16 off = (dutyCycle/100.0) * freq;
	uint16 on = freq - off;

	Ave_gpioPinDirection(T0_PWM_GPIO, T0_PWM_BIT, OUTPUT);

	while(1){
		Ave_gpioPinWrite(T0_PWM_GPIO, T0_PWM_BIT, HIGH);
		TCNT0 = on;
		Ave_timer0Start();
		while((TIFR & 0x01) == 0);
		Ave_timer0Stop();
		TIFR |= 0x01;

		Ave_gpioPinWrite(T0_PWM_GPIO, T0_PWM_BIT, LOW);
		TCNT0 = off;
		Ave_timer0Start();
		while((TIFR & 0x01) == 0);
		Ave_timer0Stop();

		TIFR |= 0x01;
	}



}

void Ave_timer1Init(T1_MODE mode,T1_COM OC,T1_PRESCALER prescal, uint16 initialValue, uint8 outputCompareLow, uint8 outputCompareHigh,uint16 inputCapture, uint8 interruptMask){
	TCCR1 = mode | OC;
	TCNT1 = initialValue;
	OCR1A = (outputCompareHigh << 8) | (outputCompareLow);
	OCR1B = (outputCompareHigh << 8) | (outputCompareLow);
	TIMSK |= interruptMask;
	ICR1 |= inputCapture;

	t1_global_prescalar = prescal;
	switch(prescal){
	case T1_NO_CLOCK:{
		//do nothing
	}break;
	case T1_PRESCALER_NO:{
		t1_global_prescalar_value = 1;
	}break;
	case T1_PRESCALER_8:{
		t1_global_prescalar_value = 8;
	}break;
	case T1_PRESCALER_64:{
		t1_global_prescalar_value = 64;
	}break;
	case T1_PRESCALER_256:{
		t1_global_prescalar_value = 256;
	}break;
	case T1_PRESCALER_1024:{
		t1_global_prescalar_value = 1024;
	}break;
	}
}

void Ave_timer1SetA(uint8 value){
	TCNT1L = value;
}

void Ave_timer1SetB(uint8 value){
	TCNT1H = value;
}

uint8 Ave_timer1ReadA(void){
	return TCNT1L;
}


uint8 Ave_timer1ReadB(void){
	return TCNT1H;
}

void Ave_timer1Start(void){
	TCCR1 |= t1_global_prescalar;
}

void Ave_timer1Stop(void){
	TCCR1 &= ~(0x0007);
}

void Ave_timer1Delay_ms(uint16 delay){
	uint64 counts = 0;
	uint64 ovf_times = 0;
	uint16 ovf_times_remainder = 0;

	counts = ((delay * (F_CPU/(double)t1_global_prescalar_value)/1000.0) - 1);//=3905


	ovf_times = counts/65535;//=15
	ovf_times_remainder = counts % 65535;//=65

	Ave_timer1Start();


	while(ovf_times > 0){
		while((TIFR & 0x04) == 0);

		TIFR |= 0x04;

		ovf_times --;

	}

	TCNT0 = 65535 - ovf_times_remainder;
	while((TIFR & 0x04) == 0);
	TIFR |= 0x04;

	Ave_timer1Stop();

}

void Ave_timer1SwPWM(uint8 dutyCycle,uint8 freq){

	uint16 off = (dutyCycle/100.0) * freq;
	uint16 on = freq - off;

	Ave_gpioPinDirection(T1_PWM_GPIO, T1_PWM_BIT, OUTPUT);

	while(1){
		Ave_gpioPinWrite(T1_PWM_GPIO, T1_PWM_BIT, HIGH);
		TCNT1 = on;
		Ave_timer1Start();
		while((TIFR & 0x04) == 0);
		Ave_timer1Stop();
		TIFR |= 0x04;

		Ave_gpioPinWrite(T1_PWM_GPIO, T1_PWM_BIT, LOW);
		TCNT1 = off;
		Ave_timer1Start();
		while((TIFR & 0x04) == 0);
		Ave_timer1Stop();

		TIFR |= 0x04;
	}
}

void Ave_timer2Init(T2_MODE mode,T2_COM OC,T2_PRESCALER prescal, uint8 initialValue, uint8 outputCompare, uint8 assynchronous, uint8 interruptMask){
	uint8 control = mode|OC|prescal;
	TCCR2 = (control & 0xf8);
	TCNT2 = initialValue;
	OCR2 = outputCompare;
	TIMSK |= interruptMask;

	t2_global_prescalar = control & 0x07;

	switch(prescal){
	case T2_NO_CLOCK:{
		//do nothing
	}break;
	case T2_PRESCALER_NO:{
		t2_global_prescalar_value = 1;
	}break;
	case T2_PRESCALER_8:{
		t2_global_prescalar_value = 8;
	}break;
	case T2_PRESCALER_32:{
		t2_global_prescalar_value = 32;
	}break;
	case T2_PRESCALER_64:{
		t2_global_prescalar_value = 64;
	}break;
	case T2_PRESCALER_128:{
		t2_global_prescalar_value = 128;
	}break;

	case T2_PRESCALER_256:{
		t0_global_prescalar_value = 256;
	}break;
	case T2_PRESCALER_1024:{
		t0_global_prescalar_value = 1024;
	}break;
	}
}

void Ave_timer2Set(uint8 value){
	TCCR2 = value;
}

uint8 Ave_timer2Read(void){
	return TCCR2;
}

void Ave_timer2Start(void){

	TCCR2 |= t2_global_prescalar;


}

void Ave_timer2Stop(void){
	TCCR2 &= ~(0x07);
}


void Ave_timer2Delay_ms(uint16 delay){
	uint32 counts = 0;
	uint32 ovf_times = 0;
	uint8 mode;
	uint8 ovf_times_remainder = 0;

	counts = ((delay * (F_CPU/t2_global_prescalar_value)/1000.0) - 1);//=3905


	mode = TCCR2 & 0x48;
	if(mode == T2_COMP_MODE){
		ovf_times = counts/OCR2;//=15
		ovf_times_remainder = counts % OCR2;//=65
	}else if(mode == T2_NORMAL_MODE){
		ovf_times = counts/256;//=15
		ovf_times_remainder = counts % 256;//=65
	}
	Ave_timer2Start();

	if(mode == T2_COMP_MODE){
		while(ovf_times > 0){

			while((TIFR & 0x40) == 0);

			TIFR |= 0x40;

			ovf_times --;

		}
	}else if(mode == T2_NORMAL_MODE){
		while(ovf_times > 0){

			while((TIFR & 0x40) == 0);
			TIFR |= 0x40;
			ovf_times --;

		}
	}



	TCNT0 = 256 - ovf_times_remainder;
	while((TIFR & 0x40) == 0);
	TIFR |= 0x40;


	Ave_timer2Stop();


}

void Ave_timer2SwPWM(uint8 dutyCycle,uint8 freq){

	uint16 off = (dutyCycle/100.0) * freq;
	uint16 on = freq - off;

	Ave_gpioPinDirection(T2_PWM_GPIO, T2_PWM_BIT, OUTPUT);

	while(1){
		Ave_gpioPinWrite(T2_PWM_GPIO, T2_PWM_BIT, HIGH);
		TCNT2 = on;
		Ave_timer2Start();
		while((TIFR & 0x40) == 0);
		Ave_timer2Stop();
		TIFR |= 0x40;

		Ave_gpioPinWrite(T2_PWM_GPIO, T2_PWM_BIT, LOW);
		TCNT2 = off;
		Ave_timer2Start();
		while((TIFR & 0x40) == 0);
		Ave_timer2Stop();

		TIFR |= 0x40;
	}



}
