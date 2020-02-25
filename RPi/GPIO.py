
BCM = 1

OUT = 0
IN = 1
PUD_UP = 0

LOW = 0
HIGH = 1

class PWM:

    def __init__(self, type, val):
        self.type = type
        pass

    def start(self, val):
        pass

    def ChangeDutyCycle(self,val):
        pass

    def ChangeDutyCycle_ipc(self,sim, val):
        #TODO - implement ipc for communication between simulator and script

        from  Simulator import Simulator

        sim.updatePWM(self.type, val)
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