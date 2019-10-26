/*
 * softwareDelay.c
 *
 *  Created on: Oct 21, 2019
 *      Author: Think
 */


#include "softwareDelay.h"

/*
 *
 * (1/f) = cycle time
 *
 * n/(1/f) = required counts = nf
 *
 *
 *
 *
 *
 */
static sint64  loop;
void Ave_SwDelay_ms(uint32 n){
	loop = n * (F_CPU / 1000) / 70;
	while((loop --) > 0);
}

void Ave_SwDelayUntil_ms(uint32 n){

}
