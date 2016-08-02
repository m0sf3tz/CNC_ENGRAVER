/*
 * global.c
 *
 *  Created on: Mar 5, 2016
 *      Author: sumax2
 */
#include <stdint.h>

#define PWM_FREQUENCY 									   1000

#define CHUNK_SIZE										   512
#define BUFFER_SIZE										   128
#define CRC_BYTES_PER_CHUNK				  				   4

#define BAD_CRC                        					   0xEE       //#used in sending both types of commands
#define GOOD_CRC                      					   0xDD

#define ALL_BUFFERS_FILLED_RESPONSE                        0//          #uC is saying that it's four internal buffers are not all full
#define BUFFERS_CAPACITY_AVIALIBLE_RESPONSE                1//          #uC is saying it has room in it's buffers

#define IS_IDLE_RESPONSE                        			1//          #uC is saying that it is idle
#define IS_NOT_IDLE_RESPONSE              					0//          #uC is saying it is not idle

#define PWM_ENABLED_X              							0//
#define PWM_ENABLED_Y                        				1//


//blah..
#define GET_FLAG_FROM_PYTHON(a)  (((unsigned int)(a) >> 24) & 0xFF )
#define GET_STEPS_FROM_PYTHON(a) (((unsigned int)(a) >> 12) & 0xFFF)
#define GET_FREQ_FROM_PYTHON(a)  (((unsigned int)(a) >> 0)  & 0xFFF)

#define SET_BUFFER(a,b) (a = a | (1<< b))
#define CLR_BUFFER(a,b) ((a) &= ~((1) << (b)))
#define IS_BUFFER_VALID(a,b) ( (a >> (b)) & 0b1 ) 	//see if the buffer held in position "B" is valid





/*################# This looks into the flag bit set in LineElm and grabs the info out of it #################*/
#define GET_STOP_BIT(a) ( ( a >> 0 ) & 0x1 )
#define GET_LASE_BIT(a) ( ( a >> 1 ) & 0x1 )
#define GET_ROT_BIT(a)  ( ( a >> 2 ) & 0x1 )




/*
################# FLAG STRUCTURE #################
bit 0: stopb bit



 */


typedef struct LineElm
{
	uint32_t frequency;  	// data buffer
	uint32_t steps; 		// end of data buffer
	uint8_t  flags;  		// maximum number of items in the buffer
} LineElm;


//################# PWM Varibles ############################3

extern int pwm_frequency;
extern int pwm_steps;
extern int pwm_count;

extern int32_t  pulseCount;		//used in validating the total pulse counts sent

extern uint32_t systemClock;	//40Mhz; used in calculating pulse duration


extern int currentEnabledOutput;	// 0 = Y axis, 1 = X axis
extern int pwmStepMagnification;


//################# buffer variables ############################3
extern LineElm lineElm[4][128];

extern uint8_t currentBuff_fill;
extern uint8_t validBuffers;			//one hot encoded, tells you which one of the 4 buffers has valid data
extern uint8_t currentBuff_execute;		//which of the 4 bufferes is being used to set the PWM
extern uint16_t lineElm_iter;

//################# laser variables ############################3

extern uint32_t lase_adc_temp[1];
