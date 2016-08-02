/*
 * parseAndExecute.h
 *
 *  Created on: Nov 18, 2015
 *      Author: Suamx
 */

#ifndef PARSEANDEXECUTE_H_
#define PARSEANDEXECUTE_H_

#define LEDOFF  		 	 					0		//command
#define LEDON       	  	 					1		//command
#define GREENON 			 					2		//command

#define BLUEON   			 					3		//command

#define CC_CCW 		 		 					5		//command

#define SET_FREQUENCY		 			     	6		//command
#define SET_STEPS		     				    7		//command

#define FILL_BUFF			 					8		//command
#define START_LINE_ELM_EXECUTION			 	10		//command
#define TEST_ZONE								11		//command



#define CHECK_BUFFER_STAT						12		//question
#define SET_DUTY	  							13		//command
#define IS_IDLE 	  							14		//question

#define PWM_ENABLE_SWITCH 	  				    15		//command
#define PWM_ENABLE_READ 	  				    16		//question

#define PWM_ENABLE_X							17		//command
#define PWM_ENABLE_Y							18		//command

#define SET_MAG								    19   	//command

#define CHECK_SYSTEM							0xA1	//question (check vital stats..) returns 32 uart bytes

#define FILL_BUFF_SHAKE_BACK 	0xAB


void parseAndExecute();

void ledOn();
void ledOff();
void greenOn();

void greenOff();
void pwm_set();
void cc_ccw(unsigned char);

void set_frequency(uint32_t);
void set_steps(uint32_t);

void fill_buff();
void start_line_elm_execution();

void test_zone();

void check_buffer_stat();

void is_idle();

void pwm_enable_switch();
void pwm_enable_read();

void pwm_enable_Y();
void pwm_enable_X();

void check_system();
void set_mag();

#endif /* PARSEANDEXECUTE_H_ */
