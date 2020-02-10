import zmq

class Simulator:

    def __init__(self):
        #self.rspSocket = self.context.socket(zmq.REP)
        #self.rspSocket.bind("tcp://*:5555")
        print("GSDEBUG 0")

        self.context = zmq.Context()
        print("GSDEBUG 1")

        self.socket = self.context.socket(zmq.REQ)
        print("GSDEBUG 2")

        self.socket.connect("tcp://localhost:5555")


        pass

    def getSensorValues(self):
        #TODO implement IPC

        self.socket.send(b"getSensorVals")

        print("GSDEBUG waiting for data from sim")

        reply = self.socket.recv()

        return self.parseGetSensorValsMsg(reply)

    def updatePWM(self, pwm, val):
        #TODO implement IPC

        print("GSDEBUG send updatePWM to sim")


        msg = "updatePWM:"+str(val)

        self.socket.send(msg.encode("utf-8"))

        pass

    def parseGetSensorValsMsg(self, msg):
        #TODO implement parsing msg
        return [0]*5
