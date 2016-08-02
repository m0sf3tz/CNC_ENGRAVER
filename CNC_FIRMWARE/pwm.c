/*
 * pwm.c
 *
 *  Created on: Jul 13, 2016
 *      Author: sumax2
 */




#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/pwm.h"
#include "driverlib/rom.h"
#include "global.h"
#include "pwm.h"


void pwm_duty(int duty){



	volatile uint32_t ui32Load;
	volatile uint32_t ui32PWMClock;
	volatile uint32_t divisor;


	ui32PWMClock = SysCtlClockGet() / 64;
	ui32Load = (ui32PWMClock / PWM_FREQUENCY) - 1;

	divisor = duty*ui32Load/100;

	ROM_PWMGenDisable(PWM1_BASE, PWM_GEN_0);
	ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, divisor);
	ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_0);

}
