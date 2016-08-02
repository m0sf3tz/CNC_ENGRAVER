import serial
from Comand_Const import *
from array import *
from const import *
import random
import time
def computeCRC(crc,codeword,len):
    crcLUT = [
    0x00, 0x3e, 0x7c, 0x42, 0xf8, 0xc6, 0x84, 0xba, 0x95, 0xab, 0xe9, 0xd7,
    0x6d, 0x53, 0x11, 0x2f, 0x4f, 0x71, 0x33, 0x0d, 0xb7, 0x89, 0xcb, 0xf5,
    0xda, 0xe4, 0xa6, 0x98, 0x22, 0x1c, 0x5e, 0x60, 0x9e, 0xa0, 0xe2, 0xdc,
    0x66, 0x58, 0x1a, 0x24, 0x0b, 0x35, 0x77, 0x49, 0xf3, 0xcd, 0x8f, 0xb1,
    0xd1, 0xef, 0xad, 0x93, 0x29, 0x17, 0x55, 0x6b, 0x44, 0x7a, 0x38, 0x06,
    0xbc, 0x82, 0xc0, 0xfe, 0x59, 0x67, 0x25, 0x1b, 0xa1, 0x9f, 0xdd, 0xe3,
    0xcc, 0xf2, 0xb0, 0x8e, 0x34, 0x0a, 0x48, 0x76, 0x16, 0x28, 0x6a, 0x54,
    0xee, 0xd0, 0x92, 0xac, 0x83, 0xbd, 0xff, 0xc1, 0x7b, 0x45, 0x07, 0x39,
    0xc7, 0xf9, 0xbb, 0x85, 0x3f, 0x01, 0x43, 0x7d, 0x52, 0x6c, 0x2e, 0x10,
    0xaa, 0x94, 0xd6, 0xe8, 0x88, 0xb6, 0xf4, 0xca, 0x70, 0x4e, 0x0c, 0x32,
    0x1d, 0x23, 0x61, 0x5f, 0xe5, 0xdb, 0x99, 0xa7, 0xb2, 0x8c, 0xce, 0xf0,
    0x4a, 0x74, 0x36, 0x08, 0x27, 0x19, 0x5b, 0x65, 0xdf, 0xe1, 0xa3, 0x9d,
    0xfd, 0xc3, 0x81, 0xbf, 0x05, 0x3b, 0x79, 0x47, 0x68, 0x56, 0x14, 0x2a,
    0x90, 0xae, 0xec, 0xd2, 0x2c, 0x12, 0x50, 0x6e, 0xd4, 0xea, 0xa8, 0x96,
    0xb9, 0x87, 0xc5, 0xfb, 0x41, 0x7f, 0x3d, 0x03, 0x63, 0x5d, 0x1f, 0x21,
    0x9b, 0xa5, 0xe7, 0xd9, 0xf6, 0xc8, 0x8a, 0xb4, 0x0e, 0x30, 0x72, 0x4c,
    0xeb, 0xd5, 0x97, 0xa9, 0x13, 0x2d, 0x6f, 0x51, 0x7e, 0x40, 0x02, 0x3c,
    0x86, 0xb8, 0xfa, 0xc4, 0xa4, 0x9a, 0xd8, 0xe6, 0x5c, 0x62, 0x20, 0x1e,
    0x31, 0x0f, 0x4d, 0x73, 0xc9, 0xf7, 0xb5, 0x8b, 0x75, 0x4b, 0x09, 0x37,
    0x8d, 0xb3, 0xf1, 0xcf, 0xe0, 0xde, 0x9c, 0xa2, 0x18, 0x26, 0x64, 0x5a,
    0x3a, 0x04, 0x46, 0x78, 0xc2, 0xfc, 0xbe, 0x80, 0xaf, 0x91, 0xd3, 0xed,
    0x57, 0x69, 0x2b, 0x15]

    if(len == 0):
        return crc
    crc = crc ^ 0xff
    count = 0
    crc = crcLUT[crc ^ codeword[count]]
    count = count + 1
    while not (count==len):
        crc = crcLUT[crc ^ codeword[(count)]]
        count = count + 1

    return crc ^ 0xff;


def computeCRC_16(codeword,len):
    crcLUT = [
    0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
	0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
	0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
	0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
	0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
	0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
	0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
	0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
	0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
	0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
	0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
	0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
	0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
	0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
	0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
	0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
	0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
	0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
	0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
	0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
	0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
	0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
	0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
	0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
	0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
	0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
	0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
	0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
	0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
	0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
	0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
	0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
    ]

    crc = 0
    for i in range(0,len):
        crc = (crc<<8) ^ crcLUT[((crc>>8) ^ codeword[i]) & 0x00FF];
    return crc & 0xFFFF


def sendCommand(command,ser):
    #command: DWORD
    if (command > 0xFFFFFFFF):
        print "VALUE CHOSEN FOR COMMAND LARGER THAN 4 BYTES"
    crcCalc = []
    crcCalc.append(command & 0xFF)
    crcCalc.append(command >> 8  & 0xFF)
    crcCalc.append(command >> 16 & 0xFF)
    crcCalc.append(command >> 24 & 0xFF)

    retry = 0
    sent = 1
    while sent:
        if(retry==5):
            print("FIVE CONSECUTIVE SEND CYCLES FAILED")
            return False

        ser.write(chr(crcCalc[0]))
        ser.write(chr(crcCalc[1]))
        ser.write(chr(crcCalc[2]))
        ser.write(chr(crcCalc[3]))

        crc = computeCRC(0,crcCalc,4)


        ser.write(chr(crc))
        ackNack =  ser.read(1)
        if  ( (ord(ackNack) == 255)):
            return True
        elif( (ord(ackNack) == 0)):
            sent = 0
            retry = retry + 1
        else:
            sent = 0
            retry = retry + 1

def setDutyPWM(duty,ser):
    if duty > 100:
        print "ERROR: duty cycle larger than 100"
        return -1
    if duty < 1:
        print "ERROR: duty cycle smaller than 5"
        return -1

    command = SET_DUTY | (duty << 8)
    sendCommand(command,ser)


def sendChunk(buf,ser):
    #sends a chunck of info
    #accepts an arary filled with elements which are 16 bits long.
    #breaks it into two sends (CRC_16 can protect a maximum of 256 byes)
    sendCommand(FILL_BUFF,ser)

    retry = 0
    sent = 1
    while sent:
        if(retry==5):
            print("FIVE CONSECUTIVE SEND CYCLES FAILED")
            return False

        ackNack =  ser.read(1)  #processor ready to accept stuff?

        if  ( (ord(ackNack) == 0xAB)):  #yes
            break
        else:
            sent = 0                   #no, retry
            retry = retry + 1

    if (len(buf) != 512):
        print("ERROR: MESSAGE NOT LONG ENOUGH - HERE")

    crc_0_255   = computeCRC_16(buf[0:256]  ,256)
    crc_256_512 = computeCRC_16(buf[256:512],256)


    print ("crc_0_255:   %d" %crc_0_255)
    print ("crc_256_512: %d" %crc_256_512)

    crc_0_7_  = crc_0_255 & 0xFF
    crc_8_15_ = crc_0_255 >> 8

    buf.append(crc_0_7_)
    buf.append(crc_8_15_)

    crc_0_7_  = crc_256_512 & 0xFF
    crc_8_15_ = crc_256_512 >> 8

    buf.append(crc_0_7_)
    buf.append(crc_8_15_)

    ser.write(array('B',buf).tostring())

    ackNack =  ser.read(1)  #read reply;

    if  ( (ord(ackNack) == GOOD_CRC)):  #yes
        print "CRC GOOD :>"
        return True
    else:
        print "CRC BAD :("
        return False

def makeLineElm(array,element, frequency, steps,lasew_pwm,lase,stop,rot = COUNTER_CLOCK_WISE, verbose = False):


    if( steps >> (2**11-1)):
        print "Steps too big"
        return -1

    if( frequency >> (2**12-1)):
        print "Steps too big"
        return -1

    flag = stop | lase << 1 | rot <<2

    #flag = 0xA1
    val = (frequency) | ((steps) <<12) | (flag << 24)

    array[element*4+0] =   val & 0xFF
    array[element*4+1] =  (val>>8    & 0xFF)
    array[element*4+2] =  (val>>16    & 0xFF)
    array[element*4+3] =  (val>>24    & 0xFF)

    if verbose:
        print("lineElm %d unit32 val is %d" %(element,val))



def sendCommandAndWaitForResponse(command,ser):


    #command: DWORD
    if (command > 0xFFFFFFFF):
        print "VALUE CHOSEN FOR COMMAND LARGER THAN 4 BYTES"
    crcCalc = []
    crcCalc.append(command & 0xFF)
    crcCalc.append(command >> 8  & 0xFF)
    crcCalc.append(command >> 16 & 0xFF)
    crcCalc.append(command >> 24 & 0xFF)

    retry = 0
    sent = 1
    while sent:
        if(retry==5):
            print("FIVE CONSECUTIVE SEND CYCLES FAILED")
            return False

        ser.write(chr(crcCalc[0]))
        ser.write(chr(crcCalc[1]))
        ser.write(chr(crcCalc[2]))
        ser.write(chr(crcCalc[3]))

        crc = computeCRC(0,crcCalc,4)


        ser.write(chr(crc))
        ackNack =  ser.read(1)
        if  ( (ord(ackNack) == 255)):
            pass
        elif( (ord(ackNack) == 0)):
            sent = 0
            retry = retry + 1
        else:
            sent = 0
            retry = retry + 1

        return  ord(ser.read(1))  #get the response of the question back


def getSystemUpdate(ser):

    command = CHECK_SYSTEM
    #command: DWORD
    if (command > 0xFFFFFFFF):
        print "VALUE CHOSEN FOR COMMAND LARGER THAN 4 BYTES"
    crcCalc = []
    crcCalc.append(command & 0xFF)
    crcCalc.append(command >> 8  & 0xFF)
    crcCalc.append(command >> 16 & 0xFF)
    crcCalc.append(command >> 24 & 0xFF)

    retry = 0
    sent = 1
    while sent:
        if(retry==5):
            print("FIVE CONSECUTIVE SEND CYCLES FAILED")
            return False

        ser.write(chr(crcCalc[0]))
        ser.write(chr(crcCalc[1]))
        ser.write(chr(crcCalc[2]))
        ser.write(chr(crcCalc[3]))

        crc = computeCRC(0,crcCalc,4)


        ser.write(chr(crc))
        ackNack =  ser.read(1)
        if  ( (ord(ackNack) == 255)):
            pass
        elif( (ord(ackNack) == 0)):
            sent = 0
            retry = retry + 1
        else:
            sent = 0
            retry = retry + 1

        returnVal = []
        for i in range (0,4):
           returnVal.append( ord(ser.read(1)) )

        return (returnVal[0] | (returnVal[1] << 8) | (returnVal[2] << 16) |(returnVal[3] << 24))



class lineElm:
    def __init__(self, max_frequency = 500):
        self.lineNum = 0
        self.array = []
        self.byteStream = []
        self.chunkAr = []
        self.numChunks = 0
        self.isEmpty = True
        self.maxFrequency = max_frequency


        #MOVE INTO GLOBAL CONSANTS
        #PACKING
        self.STOP_BIT_IN_LIST = 4
        '''
        frequency = element[0]
        steps     = element[1]
        lase      = element[2]
        rot       = element[3]
        stop      = element[4]
        '''


    def __setStopBit(self):
        #the final lineElm  appended to the array needs to be modified to have it's stop but (bit #3) set to 1 for the stop bit
        self.array[-1][self.STOP_BIT_IN_LIST] = 1

    def finalize(self):
        self.__setStopBit()
        self.__makeByteStream()

    def append(self, frequency,steps,lase,rot,stop=0):

        self.isEmpty = False

        if( steps >> (2**12-1)):
            print "Steps too big"
            return -1

        if( frequency >> (2**12-1)):
            print "Frequency too large"
            return -1

        if not ( (lase== 0) or (lase== 1)):
            print "lase set wrong"
            return - 1

        if not ( (rot== 0) or (rot== 1)):
            print "rot set wrong"
            return - 1

        if not ( (stop== 0) or (stop== 1)):
            print "stop set wrong"
            return - 1

        lase = not lase             #due to hardware
        t_arr = [frequency,steps,lase,rot,stop]
        self.array.append(t_arr)



    def __makeByteStream(self):
        #go through the list of lists... in each list.. grab out the values and pack them into sendable format

        for element in self.array:
            frequency = element[0]
            steps     = element[1]
            lase      = element[2]
            rot       = element[3]
            stop      = element[4]

            flag = stop | lase << 1 | rot <<2           #flag is read into an 8 bit register
            val = (frequency) | ((steps) <<12) | (flag << 24)

            self.byteStream.append(val >> 0 & 0xFF)
            self.byteStream.append(val >> 8 & 0xFF)
            self.byteStream.append(val >> 16 & 0xFF)
            self.byteStream.append(val >> 24 & 0xFF)

    def createChunks(self):
        '''
        packs the bytesream array into 512 chunks meant to be sent through UART
        :return:
        '''

        if self.isEmpty == True:
            print "Cant send an empty Chunk"
            return -1

        temp_stream = []
        iter = 0                #
        for element in self.byteStream:
            if iter != CHUNK_SIZE:
                temp_stream.append (element)                #build first element
                iter = iter + 1
            else:
                self.chunkAr.append(temp_stream)            #overFlow emenents
                temp_stream = []
                temp_stream.append(element)
                iter = 1

        #add overFlow that's not filled, first element that's not filled. First element that's filled w/ size = CHUNK_SIZE
        if len(temp_stream) != 0:
            while(len(temp_stream))!= CHUNK_SIZE:       #pad the chunk so it's 512 bytes long as it should be
                temp_stream.append(0)
            self.chunkAr.append(temp_stream)

        self.numChunks = len(self.chunkAr)





    def selfValidify(self,byteStremCount):
        if byteStremCount!= 0:
            self.isEmpty = False

        self.byteStream = []
        for i in range (0,byteStremCount):
            self.byteStream.append(random.randint(0, 255))

    def continouse_step(self,rot,steps,frequency):
        self.append(frequency = frequency,steps = steps,rot = rot, lase = 0, stop = 0)

    def continouse_step_lase(self,rot,steps,frequency):
        self.append(frequency = frequency,steps = steps,rot = rot, lase = 1, stop = 0)


    def ramp_up(self, rot,f_max):
        RAMP_STEPS = 40
        TOTAL_FREQUENCY_INCREMENTS = 40
        STEPS_PER_INCREMENT = int(RAMP_STEPS / TOTAL_FREQUENCY_INCREMENTS)
        for i in range(0, TOTAL_FREQUENCY_INCREMENTS):
            frequency = f_max * (i + 1) / (TOTAL_FREQUENCY_INCREMENTS)
            self.append(frequency=frequency, steps=STEPS_PER_INCREMENT, rot=rot, lase=1, stop=0)


    def ramp_down(self, rot,f_max):            #injects final stop bit
        RAMP_STEPS = 40
        TOTAL_FREQUENCY_INCREMENTS = 40
        STEPS_PER_INCREMENT = int(RAMP_STEPS / TOTAL_FREQUENCY_INCREMENTS)
        for i in range(0, TOTAL_FREQUENCY_INCREMENTS):
            frequency = f_max - f_max * (i) / (TOTAL_FREQUENCY_INCREMENTS)                               #i instead of (i+1) so we don't get an element with 0 frequency at the end
            self.append(frequency=frequency, steps=STEPS_PER_INCREMENT, rot=rot, lase=1, stop=0)

    def sendLine(self,ser):

        if  ser.isOpen():
            print "SERIAL port open internally ::)"

        if self.numChunks == 0:
            print "can't send empty lineElm"
            return -1

        sendChunk(self.chunkAr[0],ser)

        #a = sendCommandAndWaitForResponse(CHECK_BUFFER_STAT,ser)

        sendCommand(START_LINE_ELM_EXECUTION,ser)
        self.chunkAr.pop(0) #already sent first list, work on rest

        for chunkBuf in self.chunkAr:
            while not (sendCommandAndWaitForResponse(CHECK_BUFFER_STAT,ser)):
                pass
            sendChunk(chunkBuf,ser)



class lineElmArr:
    def __init__(self, ):

        self.arrayMatrix = []
        self.totalLines = 0

    def Append(self, lineElm):
        self.totalLines = self.totalLines + 1
        self.arrayMatrix.append(lineElm)


def singleStep(axis,steps,frequency,rot,ser):

    #check to see if the uC is busy processing previous commands, if so wait till uC is done
    while not(sendCommandAndWaitForResponse(IS_IDLE,ser)):
        pass


    if not (axis == "x" or axis == "y"):
        print "picked wrong axis"
    if axis == "x":
        sendCommand(PWM_ENABLE_X,ser)
    elif axis == "y":
        sendCommand(PWM_ENABLE_Y,ser)
    else:
        print "ERROR: failed to set X/Y enabled"


    lineElmInstance = lineElm()
    lineElmInstance.append(frequency = frequency,steps=steps,lase=0,rot=rot)
    lineElmInstance.finalize()
    lineElmInstance.createChunks()


    lineElmInstance.sendLine(ser)

def setMag(mag,ser):

    if mag <= 0:
        print "ERROR: mag less than 1"
        return -1
    if mag >= 255:
        print "ERROR: mag larger than 1024"
        return -1

    command = SET_MAG | (mag <<8)
    sendCommand(command,ser)


def blockTillDone(ser):
    while not(sendCommandAndWaitForResponse(IS_IDLE,ser)):
        time.sleep(.1)
