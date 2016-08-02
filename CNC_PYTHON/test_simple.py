
import serial
import random
from Comand_Const import *
from time import *
from time import gmtime, strftime
import array

from COMMANDS import *

array = [1,2,3,4,5]

arr_r = list(reversed(array))






# # configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
    port='\\.\COM4',
    baudrate=115200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
)

if  ser.isOpen():
    print "Am Open ::)"

print 'Enter your commands below.\r\nInsert "exit" to leave the application.'

sendCommand(LEDON,ser)

sendCommand(LEDOFF,ser)

setMag(10,ser)


# setDutyPWM(0,ser)
# setDutyPWM(5,ser)
# setDutyPWM(10,ser)
# setDutyPWM(20,ser)
# setDutyPWM(30,ser)
# setDutyPWM(40,ser)
# setDutyPWM(50,ser)
setDutyPWM(70,ser)
# setDutyPWM(30,ser)
# setDutyPWM(100,ser)
sleep(1)
lineElm = lineElm()

dir  = 1
sendCommand(PWM_ENABLE_Y, ser)
f = 500
lineElm.continouse_step_lase(0,500,f)

lineElm.continouse_step_lase(1,500,f)
lineElm.continouse_step_lase(0,500,f)
lineElm.continouse_step_lase(1,500,f)
lineElm.continouse_step_lase(0,500,f)
lineElm.continouse_step_lase(1,500,f)


lineElm.finalize()
lineElm.createChunks()
lineElm.sendLine(ser)


blockTillDone(ser)
setDutyPWM(1,ser)
sleep(1)
setMag(1,ser)

ser.close()


