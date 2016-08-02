/*
 * init_uart.c
 *
 *  Created on: Mar 5, 2016
 *      Author: sumax2
 */


#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"




extern void init_uart(){

	 SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	 //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	 GPIOPinConfigure(GPIO_PA0_U0RX);
	 GPIOPinConfigure(GPIO_PA1_U0TX);
	 GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	 UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
	 (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}


