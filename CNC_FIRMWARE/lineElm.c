/*
 * lineElm.c
 *
 *  Created on: Mar 5, 2016
 *      Author: sumax2
 */




#include<stdint.h>
#include "global.h"

void parse_lineElm(unsigned char lineElm_Temp[]){

	int i = 0;
	for(i = 0; i < CHUNK_SIZE; i = i + 4){

		uint32_t command = lineElm_Temp[i] | (lineElm_Temp[i+1] << 8) | (lineElm_Temp[i+2] << 16) | (lineElm_Temp[i+3] << 24);  //this is the command that python sends in 8 bit chunks through uart...

		lineElm[currentBuff_fill][i/4].steps 	 = GET_STEPS_FROM_PYTHON(command)*2*pwmStepMagnification;		//two interupts per cycle, magnification turns pixels into multiple steps if desired
		lineElm[currentBuff_fill][i/4].frequency = (systemClock / (GET_FREQ_FROM_PYTHON(command)*2) );			//do the math... (set frequecny)
		lineElm[currentBuff_fill][i/4].flags	 = GET_FLAG_FROM_PYTHON(command);								//grab flags
	}
}
