/*
 * init_per.c
 *
 *  Created on: Mar 5, 2016
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

#include "init_per.h"

#ifndef INIT_PER_C_
#define INIT_PER_C_


extern void init_perh(){

	 SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

	 SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);				//portF
	 SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	 SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);				//uart + flag outputs
	 SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);				//PWM output


	 GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	 GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_6|GPIO_PIN_7);			//flags
	 GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_7, GPIO_PIN_7 );

	 GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_1|GPIO_PIN_2);			//used for selecting which PWM will be enabled on the poulou module

	 GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_1, GPIO_PIN_1);					//initilize enable pin
	 GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2, 0 );

}


#endif /* INIT_PER_C_ */
