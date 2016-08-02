/*
 * ADC.c
 *
 *  Created on: Mar 10, 2016
 *      Author: sumax2
 */




//this contains the ADC converter

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#include "init_adc.h"
#include "global.h"
#include "ADC.h"

void ADC_convert(){

	ADCProcessorTrigger(ADC0_BASE, 3);

	while(!ADCIntStatus(ADC0_BASE, 3, false)); //Wait for conversion to be completed.

	ADCIntClear(ADC0_BASE, 3);	        		// Clear the ADC interrupt flag.


	//
	// Read ADC Value.
	//
	ADCSequenceDataGet(ADC0_BASE, 3, lase_adc_temp);

}
