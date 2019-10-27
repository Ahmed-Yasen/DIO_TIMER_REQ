/*
 * interruptLib.h
 *
 *  Created on: Oct 24, 2019
 *      Author: Think
 */

#ifndef INTERRUPTLIB_H_
#define INTERRUPTLIB_H_




#define INT_HANDLER(vector,...)	\
void vector(void) __attribute__((signal, used, external)) __VA_ARGS__;	\
void vector(void)


/*
 * Interrupt handlers
 * - to use one of the following interrupts you need to follow these steps
 * 		* enable the global interrupt
 * 		* use one of the following handlers
 *
 * - example of using external interrupt 0
 * 		  SEI();
 * 		  INT0_Handler(){
 * 		  	//your code
 * 		  }
 *
 *
 * @note : to disable the global interrupt use CLI()
 */


#define INT0_Handler()				INT_HANDLER(__vector_1)
#define INT1_Handler()				INT_HANDLER(__vector_2)
#define INT2_Handler()				INT_HANDLER(__vector_3)
#define TIMER2_COMP_Handler()		INT_HANDLER(__vector_4)
#define TIMER2_OVF_Handler()		INT_HANDLER(__vector_5)
#define TIMER1_CAPT_Handler()		INT_HANDLER(__vector_6)
#define TIMER1_COMPA_Handler()		INT_HANDLER(__vector_7)
#define TIMER1_COMPB_Handler()		INT_HANDLER(__vector_8)
#define TIMER1_OVF_Handler()		INT_HANDLER(__vector_9)
#define TIMER0_COMP_Handler()		INT_HANDLER(__vector_10)
#define TIMER0_OVF_Handler()		INT_HANDLER(__vector_11)
#define	SPI_STC_Handler()			INT_HANDLER(__vector_12)
#define USART_RXC_Handler()			INT_HANDLER(__vector_13)
#define USART_UDRE_Handler()		INT_HANDLER(__vector_14)
#define USART_TXC_Handler()			INT_HANDLER(__vector_15)
#define ADC_Handler()				INT_HANDLER(__vector_16)
#define EE_RDY_Handler()			INT_HANDLER(__vector_17)
#define ANA_COMP_Handler()			INT_HANDLER(__vector_18)
#define TWI_Handler()				INT_HANDLER(__vector_19)
#define SPM_RDY_Handler()			INT_HANDLER(__vector_20)


#define STATUS_REG	(*(volatile unsigned char *)0x5F)

#define SEI()	(STATUS_REG |= 0x80)
#define CLI()	(STATUS_REG &= 0x7F)

#endif /* INTERRUPTLIB_H_ */
