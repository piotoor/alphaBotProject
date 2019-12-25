
BCM = 1

OUT = 0
IN = 1
PUD_UP = 0

LOW = 0
HIGH = 1

class PWM:
    def __init__(self, ena, val):
        pass

    def start(self, val):
        pass

    def ChangeDutyCycle_mock(self,val):
        pass

    def ChangeDutyCycle_itc(self,val):
        #TODO - implement itc for communication between simulator and script
        pass

    def ChangeDutyCycle(self,val, useItc):  #itc - inter-process communication
        if useItc:
            self.ChangeDutyCycle_itc(val)
        else:
            self.ChangeDutyCycle_mock(val)

def setmode(mode):
    pass

def setwarnings(mode):
    pass

def setup(clock, gpiomode, pudmode = 0):
    pass

def output(cs, gpiomode):
    pass

def input(dataOut):
    pass