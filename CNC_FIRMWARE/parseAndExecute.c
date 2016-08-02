#include <stdint.h>
#include <stdbool.h>
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
#include "driverlib/timer.h"

#include "crc.h"
#include "ADC.h"
#include "pwm.h"

#include "global.h"
#include "parseAndExecute.h"
#include "lineElm.h"

#define RED_LED   GPIO_PIN_1
#define BLUE_LED  GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3

//extern  unsigned short  pwm_steps;
//extern  unsigned short  pwm_frequency;



void parseAndExecute(unsigned char messageArr[]){
	uint32_t message = messageArr[1] | messageArr[2] << 8 |  messageArr[3] << 16;

	switch(messageArr[0] & 0xFF){
		case LEDOFF:
			GPIOPinWrite(GPIO_PORTF_BASE, BLUE_LED, 0);
			GPIOPinWrite(GPIO_PORTF_BASE, RED_LED, 0);
			GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, 0);
			break;
		case LEDON:
			GPIOPinWrite(GPIO_PORTF_BASE, RED_LED, RED_LED);
			break;
		case GREENON:
			GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, GREEN_LED);
			break;
		case BLUEON:
			GPIOPinWrite(GPIO_PORTF_BASE, BLUE_LED, BLUE_LED);
			break;
		case CC_CCW:
			cc_ccw(messageArr[1]);
			break;
		case SET_FREQUENCY:
			set_frequency(message);
			break;
		case SET_STEPS:
			set_steps(message);
			break;
		case FILL_BUFF:
			fill_buff();
			break;
		case START_LINE_ELM_EXECUTION:
			start_line_elm_execution();
			break;
		case TEST_ZONE:
			test_zone();
			break;
		case CHECK_BUFFER_STAT:
			check_buffer_stat();
			break;
		case CHECK_SYSTEM:
			check_system();
			break;
		case SET_DUTY:
			pwm_duty(message);
			break;
		case IS_IDLE:
			is_idle();
			break;
		case PWM_ENABLE_SWITCH:
			pwm_enable_switch();
			break;
		case PWM_ENABLE_READ:
			pwm_enable_read();
			break;
		case PWM_ENABLE_X:
			pwm_enable_X();
			break;
		case PWM_ENABLE_Y:
			pwm_enable_Y();
			break;
		case SET_MAG:
			set_mag(message);
			break;


		default:
			GPIOPinWrite(GPIO_PORTF_BASE, BLUE_LED, BLUE_LED);
			GPIOPinWrite(GPIO_PORTF_BASE, RED_LED, RED_LED);
			GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, GREEN_LED);
			while(1);
	}

}


void ledOn(){
	GPIOPinWrite(GPIO_PORTF_BASE, RED_LED, RED_LED);
	ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_0);

}

void ledOff(){
	GPIOPinWrite(GPIO_PORTF_BASE, RED_LED, 0);
}

void greenOn(){
	GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, GREEN_LED);
}

void greenOff(){
	GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, 0);
}

void pwm_set(){
	ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_0);
}

void cc_ccw(unsigned char direction){
	if (direction == 0xFF){
		GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2,0);							//CW_CWW     (PA2)	//left
	}else{
		GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2,GPIO_PIN_2);					//CW_CWW     (PA2)  //
	}

}

void set_frequency(uint32_t frequency){
//	pwm_frequency = frequency;
//
//	//uint32_t ui32PWMClock = SysCtlClockGet() / 64;
//	uint32_t ui32Load = (ui32PWMClock / pwm_frequency) - 1;
//	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, ui32Load);
//	ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, ui32Load / 2);

}

void set_steps(uint32_t steps){
	//pwm_steps = steps;
}

int pick_lineElm();

void fill_buff(){
	UARTCharPut(UART0_BASE, 0xAB);	//shake back
	int count = 0;
	unsigned short CRC_GIVEN_0_255;
	unsigned short CRC_GIVEN_256_511;

	unsigned short CRC_CALC_0_255;
	unsigned short CRC_CALC_256_511;


	unsigned char lineElm_Temp[CHUNK_SIZE+CRC_BYTES_PER_CHUNK];		//temp storage of the uart buffer recieved from python + CRC [256 DATA, 256 DATA, 2 BYTES CRC (first), 2 BYTES CRC (second)]

	while (count!=(CHUNK_SIZE+CRC_BYTES_PER_CHUNK))
    {

    	if (UARTCharsAvail(UART0_BASE)){
			lineElm_Temp[count] =  UARTCharGet(UART0_BASE);
			count++;
    	}
    }

	CRC_GIVEN_0_255   = lineElm_Temp[CHUNK_SIZE]   |  (unsigned short)(lineElm_Temp[CHUNK_SIZE+1] << 8);
	CRC_GIVEN_256_511 = lineElm_Temp[CHUNK_SIZE+2] |  (unsigned short)(lineElm_Temp[CHUNK_SIZE+3] << 8);

	CRC_CALC_0_255 	 = crc16_ccitt(lineElm_Temp, CHUNK_SIZE/2);					//each chunck size has 2 CRC's in it
	CRC_CALC_256_511 = crc16_ccitt(&lineElm_Temp[CHUNK_SIZE/2], CHUNK_SIZE/2);

	SET_BUFFER(validBuffers,currentBuff_fill);		//keep track of which of the 4 buffers are "valid"

	parse_lineElm(lineElm_Temp);					//take from "python 32bit value" to a struct that's more recognizable (also update which
	currentBuff_fill = ((currentBuff_fill+1)%4);		//update which buffer to use next

	if ((CRC_CALC_0_255==CRC_GIVEN_0_255) & (CRC_CALC_256_511==CRC_GIVEN_256_511)){
		UARTCharPut(UART0_BASE, (unsigned char)GOOD_CRC);
	}else{
		UARTCharPut(UART0_BASE, (unsigned char)BAD_CRC);
	}



}


void start_line_elm_execution(){

		//load the very first

		pwm_count = 0;						//at this point, none of the PWM pulses have been sent out to the stepper motor
		currentBuff_execute = 0;			//always start at the first buffer


		GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_6, GET_ROT_BIT(lineElm[0][0].flags)<<6 );
		GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_7, GET_LASE_BIT (lineElm[0][0].flags)<<7 );

		pwm_frequency = lineElm[0][0].frequency;
		pwm_steps     = lineElm[0][0].steps;

		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);		//initialy, we start on the "ON" cycle of the PWM


		TimerLoadSet(TIMER0_BASE, TIMER_A, pwm_frequency);
		TimerEnable(TIMER0_BASE, TIMER_A);

		//the rest of the PWM is taken care in the interrupt for timer0
}

void test_zone(){
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
}

void check_buffer_stat(){
	if(validBuffers == 0b1111)
		UARTCharPut(UART0_BASE,ALL_BUFFERS_FILLED_RESPONSE);
	else
		UARTCharPut(UART0_BASE,BUFFERS_CAPACITY_AVIALIBLE_RESPONSE);
}


void is_idle(){
	if(validBuffers == 0b0000)
		UARTCharPut(UART0_BASE,IS_IDLE_RESPONSE);
	else
		UARTCharPut(UART0_BASE,IS_NOT_IDLE_RESPONSE);

}

void pwm_enable_switch(){
	if (currentEnabledOutput == 1){
		currentEnabledOutput = 0;
		GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_1, GPIO_PIN_1);
		GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2, 0 );
	}
	else if(currentEnabledOutput == 0){
		currentEnabledOutput = 1;
		GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_1, 0);
		GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2, GPIO_PIN_2 );
	}
	else{
		//should not get here
		while(1);
	}
}


void pwm_enable_X(){
		currentEnabledOutput = 0;
		GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_1, GPIO_PIN_1);
		GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2, 0 );
}

void pwm_enable_Y(){
		currentEnabledOutput = 1;
		GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_1, 0);
		GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2, GPIO_PIN_2 );
}


void pwm_enable_read(){
	if(validBuffers == currentEnabledOutput)
		UARTCharPut(UART0_BASE,PWM_ENABLED_X);
	else
		UARTCharPut(UART0_BASE,PWM_ENABLED_Y);
}


void set_mag(int mag){
	pwmStepMagnification = mag;
}

void check_system(){
	ADC_convert();


	int i = 0;
	uint8_t responce[4];

	responce[0] = (lase_adc_temp[0]>>0)  & 0xFF;
	responce[1] = (lase_adc_temp[0]>>8)  & 0xFF;
	responce[2] = (lase_adc_temp[0]>>16) & 0xFF;
	responce[3] = (lase_adc_temp[0]>>24) & 0xFF;


	while(i!=4){
		UARTCharPut(UART0_BASE,responce[i]);
		i++;
	}
}


