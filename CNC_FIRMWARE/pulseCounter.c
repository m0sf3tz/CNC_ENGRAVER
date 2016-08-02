/*
 * pulseCounter.c
 *
 *  Created on: Mar 7, 2016
 *      Author: sumax2
 */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "inc/hw_memmap.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "inc/hw_ints.h"

#include "global.h"



void pulse_count_increment() {
    if (GPIOIntStatus(GPIO_PORTF_BASE, false) & GPIO_PIN_4) {
    	// PF4 was interrupt cause
        GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);  // Clear interrupt flag
        pulseCount++;
    }
}


void init_Pulse_counter(){
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);  // Init PF4 as input
	GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);  // Enable weak pullup resistor for PF4


    GPIOIntDisable(GPIO_PORTF_BASE, GPIO_PIN_4);       						// Disable interrupt for PF4 (in case it was enabled)
    GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);     							// Clear pending interrupts for PF4

    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4,GPIO_RISING_EDGE);           // Configure PF4 for RISING  edge trigger

    //GPIOIntRegister(GPIO_PORTF_BASE, onPulse);    					    // Register our handler function for port F
    IntEnable(INT_GPIOF);

    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4);    							// Enable interrupt for PF4

}
