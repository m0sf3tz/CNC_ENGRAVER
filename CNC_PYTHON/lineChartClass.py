from COMMANDS import *

class lineElm:
    def __init__(self, ):
        self.iter = 0
        self.array = []
        self.byteSteam = []
        self.iter = 0


    def append(self, frequency, steps,lasew_pwm,lase,stop):
        if(self.iter == 128):
            print "ERROR: lineElm size exceeded"
            return False
        t_arr = [frequency,steps,lasew_pwm,lase,stop]
        self.array.append(t_arr)


        if( steps >> (2**11-1)):
            print "Steps too big"
            return -1

        if( frequency >> (2**12-1)):
            print "Steps too big"
            return -1

        val = (frequency) | ((steps) <<12) | (stop<<30)

        self.byteSteam.append(val>>0  & 0xFF)
        self.byteSteam.append(val>>8  & 0xFF)
        self.byteSteam.append(val>>16 & 0xFF)
        self.byteSteam.append(val>>24 & 0xFF)
        self.iter = self.iter + 1

    def modeLine(self,elem, frequency, steps,lasew_pwm,lase,stop):

        val = (frequency) | ((steps) <<12) | (stop<<30)

        self.byteSteam[elem*4+0] =   val & 0xFF
        self.byteSteam[elem*4+1] =  (val>>8    & 0xFF)
        self.byteSteam[elem*4+2] =  (val>>16    & 0xFF)
        self.byteSteam[elem*4+3] =  (val>>24    & 0xFF)

        return True



# lineElm = lineElm()
# lineElm.append(400,23,2,1,1)
# lineElm.append(800,23,2,1,1)
#
# blah = [0]*512
# makeLineElm(array = blah,element = 0, frequency = 400,  steps = 23,lasew_pwm = 2,lase=1 ,stop = 1)
# makeLineElm(array = blah,element = 1, frequency = 800,  steps = 23,lasew_pwm = 2,lase=1 ,stop = 1)


print "opi"