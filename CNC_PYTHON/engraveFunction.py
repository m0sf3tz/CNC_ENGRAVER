from PIL import Image
from COMMANDS import *
from Comand_Const import *

from PIL import Image
from COMMANDS import *
from Comand_Const import *
from lineParser import*

ser = serial.Serial(
    port='\\.\COM4',
    baudrate=115200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
)

if  ser.isOpen():
    print "Am Open ::)"



def engraveStart(MAX_FREQUENCY,MAX_STEPS,prune,ser):

    entirePictureParsed = []
    lineParser(MAX_FREQUENCY = MAX_FREQUENCY,MAX_STEPS = MAX_STEPS,entirePictureParsed = entirePictureParsed,prune=prune)

    for lineElm in entirePictureParsed:



        sendCommand(PWM_ENABLE_X,ser)
        lineElm.sendLine(ser)

        blockTillDone(ser)
        #now we are done with the above lineElm
        singleStep("y",steps = prune,frequency = 100,rot = 0,ser = ser)
        blockTillDone(ser)

setMag(1,ser)
sendCommand(LEDON,ser)
sendCommand(LEDOFF,ser)


setDutyPWM(100,ser)
time.sleep(1)

engraveStart(700,1023,prune=25,ser=ser)

blockTillDone(ser)
setDutyPWM(1,ser)
time.sleep(1)


