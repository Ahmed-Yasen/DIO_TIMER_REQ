/*
 * sevenSeg_BCD.h
 *
 *  Created on: Oct 24, 2019
 *      Author: Think
 */

#ifndef SEVENSEG_BCD_H_
#define SEVENSEG_BCD_H_

#include "gpio.h"




#include "sevenSeg_BCD_CFG.h"


typedef enum{
	SEG_0,
	SEG_1,
	SEG_2,
	SEG_3
}SevenSeg_TypeDef;

void sevenSeg_Init(void);
void sevenSeg_On(SevenSeg_TypeDef segment);
void sevenSeg_Off(SevenSeg_TypeDef segment);
void sevenSeg_Write(SevenSeg_TypeDef segment, uint8 number);


#endif /* SEVENSEG_BCD_H_ */
