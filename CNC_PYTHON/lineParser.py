from PIL import Image
from COMMANDS import *
from Comand_Const import *

from PIL import Image
from COMMANDS import *
from Comand_Const import *



def switchDirection(dir):
    return (dir+1)%2




def split(sTemp,MAX_STEP):
    lenght = sTemp[0]
    val    = sTemp[1]
    complete   = lenght/MAX_STEP
    remaninder =  lenght - complete*MAX_STEP
    returnArr = []
    tempArr = []
    for i in range(0,complete):
        temp = []
        temp.append(MAX_STEP)
        temp.append(val)
        returnArr.append(temp)

    if remaninder!=0:
        temp = []
        temp.append(remaninder)
        temp.append(val)
        returnArr.append(temp)

    return returnArr


def rebuild(sTempArr,MAX_STEP):
    sTempFinal = []
    for sTemp in sTempArr:
        if sTemp[0] > MAX_STEP:
            sBrokenUp = split(sTemp,MAX_STEP)
            for sTempNew in sBrokenUp:
                sTempFinal.append(sTempNew)
        else:
            sTempFinal.append(sTemp)

    return sTempFinal

def linePrune(entirePictureParsed):
    arrNew = []
    iter = 0
    for scanline in entirePictureParsed:
        if iter == 50:
            iter = 0
            arrNew.append(scanline)
        else:
            iter = iter + 1
            pass
    return arrNew

def lineParser(MAX_FREQUENCY,MAX_STEPS,entirePictureParsed,prune,initialDir = 'L'):
    # if initialDir == "L":
    #     currentDir = 0
    # elif initialDir == "R":
    #     currentDir = 1
    # else:
    #     print "Picked wrong initial direction L/R only"
    #     return -1

    currentDir = 0                                  #initially go ?right?

    im = Image.open('s.bmp')

    pixels = list(im.getdata())
    width, height = im.size
    pixels = [pixels[i * width:(i + 1) * width] for i in xrange(height)]
    iter = 0
    for line in pixels:
        if iter == prune:
            iter = 0
            if currentDir == 1:                         #reverse list on the return path
                line = list(reversed(line))

            lineIterLead = 0
            lineIterLag  = 0
            currentLineparseLenght = 0

            sTempArr = []
            for lookAhead in range(0,len(line)):
                sTemp = []
                lineIterLead = lineIterLead + 1
                if lineIterLead == len(line):
                    sTemp.append (currentLineparseLenght+1)
                    sTemp.append (bool(line[lineIterLag]))
                    sTempArr.append(sTemp)
                    break

                if (line[lineIterLead] == line[lineIterLag]):
                    currentLineparseLenght = currentLineparseLenght + 1
                else:
                    sTemp.append (currentLineparseLenght+1)
                    sTemp.append (bool(line[lineIterLag]))
                    sTempArr.append(sTemp)
                    lineIterLag =  lineIterLead
                    currentLineparseLenght = 0

            sTempArr = rebuild(sTempArr,MAX_STEPS)


            lineElmInstance = lineElm()

            #lineElmInstance.ramp_up(currentDir,MAX_FREQUENCY)

            for continousLineSegment in sTempArr:
                steps = continousLineSegment[0]
                lase  = continousLineSegment[1]
                lineElmInstance.append(frequency=MAX_FREQUENCY,steps=steps,lase=lase,rot=currentDir)

            #lineElmInstance.ramp_down(currentDir,MAX_FREQUENCY)

            lineElmInstance.finalize()
            lineElmInstance.createChunks()
            entirePictureParsed.append(lineElmInstance)

            currentDir = switchDirection(currentDir)                                          #change direction or rotation
        else:
            iter = iter + 1


