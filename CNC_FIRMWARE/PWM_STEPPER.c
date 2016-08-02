#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "parseAndExecute.h"

#include "driverlib/pwm.h"
#include "driverlib/rom.h"
#include "PWM_STEPPER.H"
#include "global.h"


/*
void PWM1IntHandler(void){
	//GPIOPinWrite(GPIO_PORTF_BASE, RED_LED, RED_LED);

	PWMGenIntClear(PWM1_BASE,PWM_GEN_0,PWM_INT_CNT_ZERO);
	if(pwmCounter > pwm_steps){
		ROM_PWMGenDisable(PWM1_BASE, PWM_GEN_0);
		pwmCounter = 0;
	}
	pwmCounter++;
}
*/

void PWM1IntHandler(void){

}
