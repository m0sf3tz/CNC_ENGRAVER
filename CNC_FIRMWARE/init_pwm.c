/*
 * init_pwm.c
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
#include "init_pwm.h"


void init_pwm(){

	volatile uint32_t ui32Load;
	volatile uint32_t ui32PWMClock;
	volatile uint8_t ui8Adjust;

	ROM_SysCtlPWMClockSet(SYSCTL_PWMDIV_64);

	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

	ROM_GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0);
	ROM_GPIOPinConfigure(GPIO_PD0_M1PWM0);

	ui32PWMClock = SysCtlClockGet() / 64;
	ui32Load = (ui32PWMClock / PWM_FREQUENCY) - 1;
	PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, ui32Load);

	ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, ui32Load / (4));
	ROM_PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, true);
	ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_0);

}
