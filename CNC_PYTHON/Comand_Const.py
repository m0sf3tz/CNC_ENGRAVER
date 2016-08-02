#################################################################################
#                         COMMANDS WITH NO RESPONSE REQUIRED                    #
#################################################################################

LEDOFF                          =		 	  0
LEDON                           =    	  	  1
GREENON                         =	   		  2

SET_MAG  			 			=     		  19
SET_FREQUENCY		 			=     	      6
SET_STEPS		     			=	          7


GREENOFF                        =             3
FILL_BUFF                       =             8
START_LINE_ELM_EXECUTION        =             10

TEST_ZONE                       =             11
SET_DUTY                        =             13

PWM_ENABLE_SWITCH 	  			=	          15

PWM_ENABLE_X 	  		    	=	          17
PWM_ENABLE_Y 	  			    =	          18



#################################################################################
#                         COMMANDS WITH  RESPONSE REQUIRED                      #
#################################################################################

CHECK_BUFFER_STAT               =             12
CHECK_SYSTEM                    =             0xA1
IS_IDLE 	  					=		      14
PWM_ENABLE_READ                 =             16
#################################################################################
#                                OTHER CONSTANTS                                #
#################################################################################

BAD_CRC               =          0xEE       #used in sending both types of commands
GOOD_CRC              =          0xDD

#################################################################################
#                                   RESPONSES                                   #
#################################################################################

ALL_BUFFERS_FILLED_RESPONSE             =          0          #uC is saying that it's four internal buffers are not all full
BUFFERS_CAPACITY_AVIALIBLE_RESPONSE     =          1          #uC is saying it has room in it's buffers
