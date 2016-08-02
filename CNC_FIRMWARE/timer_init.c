/*
 * timer_init.h
 *
 *  Created on: Mar 5, 2016
 *      Author: sumax2
 */


#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "inc/hw_ints.h"


void init_timer(){

	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

	//uint32_t ui32Period = (SysCtlClockGet() / 10) / 2;
	//TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period -1);

	IntEnable(INT_TIMER0A);
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	//IntMasterEnable();
	//TimerEnable(TIMER0_BASE, TIMER_A);
}

