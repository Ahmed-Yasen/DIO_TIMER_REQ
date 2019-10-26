/*
 * timers.h
 *
 *  Created on: Oct 22, 2019
 *      Author: Think
 */

#ifndef TIMERS_H_
#define TIMERS_H_

#include "registers.h"
#include "gpio.h"

/*
 * User Configuration Macros
 */

#define T0_PWM_GPIO	GPIOD
#define T0_PWM_BIT	BIT0

#define T1_PWM_GPIO	GPIOD
#define T1_PWM_BIT	BIT1

#define T2_PWM_GPIO GPIOD
#define T2_PWM_BIT	BIT2


typedef enum {
	T0_NORMAL_MODE=0,T0_COMP_MODE=0x08
}T0_MODE;

typedef enum {
	T0_OC0_DIS=0,T0_OC0_TOGGLE=0x10,T0_OC0_CLEAR=0x20,T0_OC0_SET=0x30
}T0_COM;

typedef enum {
	T0_NO_CLOCK=0,T0_PRESCALER_NO=0x01,T0_PRESCALER_8=0x02,T0_PRESCALER_64=0x03,T0_PRESCALER_256=0x04,T0_PRESCALER_1024=0x05
}T0_PRESCALER;

typedef enum {
	T0_POLLING=0,T0_INTERRUPT_NORMAL=0x01,T0_INTERRUPT_CMP=0x02
}T0_INTERRUPT;





// for timer 1
typedef enum {
	T1_NORMAL_MODE=0x0000,T1_COMP_MODE_OCR1A_TOP=0x0008, T1_COMP_MODE_ICR1_TOP = 0x0018

}T1_MODE;
typedef enum {
	T1_OC0_DIS=0,T1_OC1A_TOGGLE=0x4000,T1_OC1B_TOGGLE=0x1000,T1_OC1A_CLEAR=0x8000,T1_OC1B_CLEAR=0x2000,T1_OC1A_SET=0xC000,T1_OC1B_SET=0x3000
}T1_COM;

typedef enum {
	T1_NO_CLOCK=0x0000,T1_PRESCALER_NO=0x0001,T1_PRESCALER_8=0x0002,T1_PRESCALER_64=0x0003,T1_PRESCALER_256=0x0004,T1_PRESCALER_1024=0x0005
}T1_PRESCALER;

typedef enum {
	T1_POLLING=0,T1_INTERRUPT_NORMAL=0x04,T0_INTERRUPT_CMP_1B=0x08, T1_INTERRUPT_CMP_1A=0x10, T1_INTERRUPT_ICAPTURE = 0x20
}T1_INTERRUPT;




// for timer 2
typedef enum {
	T2_NORMAL_MODE=0,T2_COMP_MODE=0x08
}T2_MODE;

typedef enum {
	T2_OC0_DIS=0,T2_OC0_TOGGLE=0x10,T2_OC0_CLEAR=0x20,T2_OC0_SET=0x30
}T2_COM;

typedef enum {
	T2_NO_CLOCK=0,T2_PRESCALER_NO=0x01,T2_PRESCALER_8=0x02, T2_PRESCALER_32=0x03, T2_PRESCALER_64=0x04, T2_PRESCALER_128=0x05, T2_PRESCALER_256 = 0x06, T2_PRESCALER_1024=0x07
}T2_PRESCALER;

typedef enum {
	T2_POLLING=0,T2_INTERRUPT_NORMAL=0x40,T2_INTERRUPT_CMP=0x80
}T2_INTERRUPT;







/*===========================Timer0 Control===============================*/
/**
 * Description:
 * @param control
 * @param initialValue
 * @param outputCompare
 * @param interruptMask
 */
void Ave_timer0Init(T0_MODE mode,T0_COM OC0,T0_PRESCALER prescal, uint8 initialValue, uint8 outputCompare, uint8 interruptMask);

/**
 * Description:
 * @param value
 */
void Ave_timer0Set(uint8 value);

/**
 * Description:
 * @return
 */
uint8 Ave_timer0Read(void);

/**
 * Description:
 */
void Ave_timer0Start(void);

/**
 * Description:
 */
void Ave_timer0Stop(void);

/**
 * Description:
 * @param delay
 */
void Ave_timer0Delay_ms(uint16 delay);

/**
 * Description:
 * @param dutyCycle
 */
void Ave_timer0SwPWM(uint8 dutyCycle,uint8 freq);









/*===========================Timer1 Control===============================*/
/**
 * Description:
 * @param controlA
 * @param controlB
 * @param initialValue
 * @param outputCompare
 * @param interruptMask
 */
void Ave_timer1Init(T1_MODE mode,T1_COM OC,T1_PRESCALER prescal, uint16 initialValue, uint8 outputCompareLow, uint8 outputCompareHigh,uint16 inputCapture, uint8 interruptMask);

/**
 * Description:
 * @param value
 */
void Ave_timer1SetA(uint8 value);

/**
 * Description:
 * @param value
 */
void Ave_timer1SetB(uint8 value);

/**
 * Description:
 * @return
 */
uint8 Ave_timer1ReadA(void);

/**
 * Description:
 * @return
 */
uint8 Ave_timer1ReadB(void);

/**
 * Description:
 */
void Ave_timer1Start(void);

/**
 * Description:
 */
void Ave_timer1Stop(void);

/**
 * Description:
 * @param delay
 */
void Ave_timer1Delay_ms(uint16 delay);

/**
 * Description:
 * @param dutyCycle
 */
void Ave_timer1SwPWM(uint8 dutyCycle,uint8 freq);





/*===========================Timer2 Control===============================*/
/**
 * Description:
 * @param control
 * @param initialValue
 * @param outputCompare
 * @param interruptMask
 */
void Ave_timer2Init(T2_MODE mode,T2_COM OC,T2_PRESCALER prescal, uint8 initialValue, uint8 outputCompare, uint8 assynchronous, uint8 interruptMask);
/**
 * Description:
 * @param value
 */
void Ave_timer2Set(uint8 value);

/**
 * Description:
 * @return
 */
uint8 Ave_timer2Read(void);

/**
 * Description:
 */
void Ave_timer2Start(void);

/**
 * Description:
 */
void Sprints_timer2Stop(void);

/**
 * Description:
 * @param delay
 */
void Ave_timer2Delay_ms(uint16 delay);

/**
 * Description:
 * @param dutyCycle
 */
void Ave_timer2SwPWM(uint8 dutyCycle,uint8 freq);


#endif /* TIMERS_H_ */
