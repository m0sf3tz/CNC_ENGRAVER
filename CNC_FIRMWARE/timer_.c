/*
 * timer_.c
 *
 *  Created on: Feb 1, 2016
 *      Author: suma
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"

#include "timer_.h"
#include "global.h"

inline void toggle_PWM(){
	if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1))
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
	else
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
}

inline void set_PWM(){
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
}

inline void CLR_PWM(){
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
}

inline void GPIO_PIN_SET(){
	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_6, GET_ROT_BIT  (lineElm[currentBuff_execute][lineElm_iter].flags)<<6 );
	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_7, GET_LASE_BIT (lineElm[currentBuff_execute][lineElm_iter].flags)<<7 );
}


inline void GPIO_PIN_CLR(){
	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_6,0);
	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_7, GPIO_PIN_7 );
}


void Timer0IntHandler(void)
{
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);		//clear the timer interrupt

	if(pwm_count < (pwm_steps-1)){							// -1 to account for initilaly setting the value of the pulse in the start_line_elm_execution() function
		toggle_PWM();										//toggle PWM signle
		pwm_count++;										//increment pwm_count
	}else{
		//check to see if the current lineLem is a stop bit...
		if( GET_STOP_BIT(lineElm[currentBuff_execute][lineElm_iter].flags) == 1){
			CLR_BUFFER(validBuffers,currentBuff_execute);					//clear the valid bit for current buffer as it is all used up
			GPIO_PIN_CLR();													//claer all the GPIO bits (lase, rot, etc)

			//reset values
			currentBuff_fill	 = 0;  								        //0,1,2,3 valid
			lineElm_iter 		 = 0;
			currentBuff_execute	 = 0;




			TimerDisable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);					//disable the timer (stop bit condition)
		}else{																//current lineElm not stop bit
			lineElm_iter++;													//increment buffer iteration
			if(lineElm_iter == BUFFER_SIZE){								//we have reached the final lineLem
				if(!IS_BUFFER_VALID(validBuffers,(currentBuff_execute+1)%4)){	//check if the next buffer we will load has valid data in it
					//defensive programming...
					//load deramp
					while(1);
				}

				TimerDisable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);				//disable timer until new values are locked in

				CLR_BUFFER(validBuffers,currentBuff_execute);				//clear the valid bit for current buffer as it is all used up
			    currentBuff_execute = ((currentBuff_execute+1)%4);			//increment current buffer; resest if = 4

			    GPIO_PIN_SET();												//update other stuff(lase,direction ectc)
				pwm_steps     = lineElm[currentBuff_execute][0].steps;
				pwm_frequency = lineElm[currentBuff_execute][0].frequency;	//grab stuff(always get it from the first one)..
				TimerLoadSet(TIMER0_BASE, TIMER_A, pwm_frequency);			//load frequency into timer

				lineElm_iter = 0; 											//set lineElm_iter back to zero
				pwm_count	 = 0;										    //reset PWM count (how many PWM signals have been sent in the current pulse train)
				set_PWM();													//set PWM signal high

				TimerEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);				//let timer run free

			}else{															//typical case - inside a buffer; Nth element done; grab info from (N+1)th element
				TimerDisable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);				//disable timer until nee values are locked in
			    GPIO_PIN_SET();												//update other stuff(lase,direction ectc)

				pwm_frequency = lineElm[currentBuff_execute][lineElm_iter].frequency;	//Grab next pulse train info
				TimerLoadSet(TIMER0_BASE, TIMER_A, pwm_frequency);
				pwm_steps     = lineElm[currentBuff_execute][lineElm_iter].steps;

				pwm_count	 = 0;													    //reset PWM count (how many PWM signals have been sent in the current pulse train)
				set_PWM();																//set PWM signal high
				TimerEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);							//let timer run free

			}
		}

	}
}
