
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>	//printf

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/pwm.h"
#include "driverlib/rom.h"
#include "stdbool.h"
#include "driverlib/timer.h"

#include "init_pwm.h"
#include "init_adc.h"
#include "init_per.h"
#include "init_uart.h"
#include "timer_init.h"
#include "pulseCounter.h"
#include "parseAndExecute.h"
#include "main_loop.h"

#include "global.h"
#include "crc.h"
#include "ADC.h"
#include "pwm.h"

#define RED_LED   GPIO_PIN_1
#define BLUE_LED  GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3




int main(void) {





	init_perh();
	init_uart();
	init_pwm();
	init_timer();
	init_Pulse_counter();
	init_adc();
	//#############################	AFTER THIS POINT ALL INTS ENABLED ###############################
	IntMasterEnable();
	//###############################################################################################


	systemClock = SysCtlClockGet();

	currentBuff_fill  		= 0; //0,1,2,3 valid
	validBuffers      		= 0; //one hot encoding
	pulseCount		  		= 0;
	lineElm_iter	  		= 0;
	currentEnabledOutput 	= 0; //for pwm enabled (NOTE: At the start both outputes are disabled by the pins, one needs to be set first, and they will switch in a ping pong fasion later)
	pwmStepMagnification	= 1; //ratio between python steps and actuall PWM pulses
	pwm_duty(1);				 //duty sets lase intensity (set it as low as it goes)

	main_loop();		//begin UART trasactions

}


