/*
 * parseAndExecute.h
 *
 *  Created on: Nov 18, 2015
 *      Author: Suamx
 */

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

#include "init_per.h"
#include "init_uart.h"
#include "timer_init.h"
#include "pulseCounter.h"
#include "parseAndExecute.h"
#include "main_loop.h"

#include "global.h"
#include "crc.h"

#define RED_LED   GPIO_PIN_1
#define BLUE_LED  GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3


void toggle(){

	if(GPIOPinRead(GPIO_PORTF_BASE, GREEN_LED)){
		 GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, 0);
	 }else{
		 GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, GREEN_LED);
	 }

}

void redOn(){
	GPIOPinWrite(GPIO_PORTF_BASE, RED_LED, RED_LED);
}

void redOff(){
	GPIOPinWrite(GPIO_PORTF_BASE, RED_LED, 0);
}

void main_loop(){

	unsigned char message[5];
	int count = 0;
	//pwmCounter = 0;
	//parse and execute loop
	while (1)
    {

    	if (UARTCharsAvail(UART0_BASE)){
    		if(count==0){
    			message[0] =  UARTCharGet(UART0_BASE);	//grab first byte
    			//toggle();
    		}
    		if(count==1){
    			message[1] = UARTCharGet(UART0_BASE);
    			//toggle();
    		}
    		if(count==2){
    			message[2] = UARTCharGet(UART0_BASE);
    			//toggle();
    		}
    		if(count==3){
    			message[3] = UARTCharGet(UART0_BASE); //grab last byte
    			//toggle();
    		}
    		if(count==4){
    			message[4] = UARTCharGet(UART0_BASE); //grab CRC
				if (crc8(0,message,4)==message[4]){
					UARTCharPut(UART0_BASE, 0xFF);	//CRC good (tell python end that)
					parseAndExecute(message);
				}else{
					UARTCharPut(UART0_BASE, 0x00);	//CRC bad
					redOn();
				}
    		}

    		count = count + 1;
    		if(count == 5)
    				count = 0;

    	}
    }
}









