
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

    def ChangeDutyCycle(self,val):
        pass

    def ChangeDutyCycle_ipc(self,val):
        #TODO - implement ipc for communication between simulator and script
        pass

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