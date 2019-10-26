/*
 * sevenSeg_BCD.c
 *
 *  Created on: Oct 24, 2019
 *      Author: Think
 */


#include "sevenSeg_BCD.h"



void sevenSeg_Init(void){
	//data bits
	Ave_gpioPinDirection(SEG_BCD_GPIO, SEG_BCD_BITS, OUTPUT);
	//decimal point
	Ave_gpioPinDirection(SEG_BCD_DP_GPIO, SEG_BCD_DP_BIT, OUTPUT);
	//enable bits
	Ave_gpioPinDirection(SEG_EN1_GPIO, SEG_EN1_BIT, OUTPUT);
	Ave_gpioPinDirection(SEG_EN2_GPIO, SEG_EN2_BIT, OUTPUT);
	Ave_gpioPinDirection(SEG_EN3_GPIO, SEG_EN3_BIT, OUTPUT);
	Ave_gpioPinDirection(SEG_EN4_GPIO, SEG_EN4_BIT, OUTPUT);
}

#include "avr/io.h"
void sevenSeg_Write(SevenSeg_TypeDef segment, uint8 number){
	Ave_gpioPinWrite(SEG_BCD_GPIO, SEG_BCD_BITS, number);
	Ave_gpioPinWrite(SEG_EN1_GPIO, SEG_EN1_BIT, LOW);
	Ave_gpioPinWrite(SEG_EN2_GPIO, SEG_EN2_BIT, LOW);
	Ave_gpioPinWrite(SEG_EN3_GPIO, SEG_EN3_BIT, LOW);
	Ave_gpioPinWrite(SEG_EN4_GPIO, SEG_EN4_BIT, LOW);

	switch(segment){
	case SEG_0:{
		Ave_gpioPinWrite(SEG_EN1_GPIO, SEG_EN1_BIT, HIGH);
	}break;
	case SEG_1:{
		Ave_gpioPinWrite(SEG_EN2_GPIO, SEG_EN2_BIT, HIGH);
	}break;
	case SEG_2:{
		Ave_gpioPinWrite(SEG_EN3_GPIO, SEG_EN3_BIT, HIGH);
	}break;
	case SEG_3:{
		Ave_gpioPinWrite(SEG_EN4_GPIO, SEG_EN4_BIT, HIGH);
	}break;
	}
}
