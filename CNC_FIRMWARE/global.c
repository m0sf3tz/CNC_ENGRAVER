/*
 * global.c
 *
 *  Created on: Mar 5, 2016
 *      Author: sumax2
 */


#include "global.h"



//################# PWM variables ############################3
int 	 pwm_frequency;		//the frequency of the current PWM being executed
int		 pwm_steps;			//this is how many steps are in the current PWM being executed
int		 pwm_count;			//this is how many steps OF the current pwm cyle _have_ been executed

int32_t  pulseCount;		//used in validating the total pulse counts sent
uint32_t systemClock;
int currentEnabledOutput;
int pwmStepMagnification;


//################# BUFFER variables ############################3

uint8_t currentBuff_fill;
uint8_t currentBuff_execute;
uint8_t validBuffers;
uint16_t lineElm_iter;


LineElm lineElm[4][128];

//################# laser variables ############################3

uint32_t lase_adc_temp[1];	 //used to hold the ACD converter value for the thermocouple on the laser
