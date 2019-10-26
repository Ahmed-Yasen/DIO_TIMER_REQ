/*
 * gpio.c
 *
 *  Created on: Oct 21, 2019
 *      Author: AVE-LAP-069
 */


#include "gpio.h"
#include "registers.h"

#define get_reg(port, offset)	(*(volatile uint8 *)((0x3B - (port*3) - offset) & 0xFF))



void Ave_gpioPortDirection(uint8 port, uint8 direction){
	get_reg(port, 1) = direction;
}

void Ave_gpioPortWrite(uint8 port, uint8 value){
	get_reg(port, 0) = value;
}

void Ave_gpioPortToggle(uint8 port){
	get_reg(port, 0) ^= 0xFF;
}

uint8 Ave_gpioPortRead(uint8 port){
	return get_reg(port, 2);
}

void Ave_gpioPinDirection(uint8 port, uint8 pins, uint8 direction){
	uint8 temp = get_reg(port, 1);

	temp &= ~(pins);

	if(direction != 0){
		temp |= pins;

	}else{
		temp &= ~(pins);
	}
//	(*(volatile uint8 *) 0x37) = temp;
	get_reg(port, 1) = temp;
}

void Ave_gpioPinWrite(uint8 port, uint8 pins, uint8 value){

	uint8 temp = get_reg(port, 0);
	uint8 tem = 0;
	for(uint8 pinPos = 1; pinPos != 0x80; pinPos <<= 1){
		if(pinPos & pins){
			if((value & pinPos) != 0){
				temp |= pinPos;
			}else{
				temp &= ~(pinPos);
			}
		}
	}

	get_reg(port, 0) = temp;

}
void Ave_gpioPinToggle(uint8 port, uint8 pins){
	get_reg(port, 0) ^= pins;
}
#include "avr/io.h"
uint8 Ave_gpioPinRead(uint8 port, uint8 pin){
	uint8 ret = 0;
	ret = (get_reg(port, 2)&pin);
	if(ret != 0){
		ret = 1;
	}else{
		ret = 0;
	}
	return ret;
}

void Ave_gpioUpperNibbleDirection(uint8 port, uint8 direction){
	if(direction != 0){
		get_reg(port, 1) |= 0xF0;
	}else{
		get_reg(port, 1) &= 0x0F;
	}

}

void Ave_gpioUpperNibbleWrite(uint8 port, uint8 value){
	if(value != 0){
		get_reg(port, 0) |= 0xF0;
	}else{
		get_reg(port, 0) &= 0x0F;
	}
}

void Ave_gpioUpperNibbleToggle(uint8 port){
	get_reg(port, 0) ^= 0xF0;
}

uint8 Ave_gpioUpperNibbleRead(uint8 port){
	return ((get_reg(port, 2)&0xF0) >> 4);
}

void Ave_gpioLowerNibbleDirection(uint8 port, uint8 direction){
	if(direction != 0){
		get_reg(port, 1) |= 0x0F;
	}else{
		get_reg(port, 1) &= 0xF0;
	}
}

void Ave_gpioLowerNibbleWrite(uint8 port, uint8 value){
	if(value != 0){
		get_reg(port, 0) |= 0x0F;
	}else{
		get_reg(port, 0) &= 0xF0;
	}
}

void Ave_gpioLowerNibbleToggle(uint8 port){
	get_reg(port, 0) ^= 0x0F;
}

uint8 Ave_gpioLowerNibbleRead(uint8 port){
	return (get_reg(port, 2)&0xF0);
}
