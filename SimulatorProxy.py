import zmq


class SimulatorProxy:

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
        reply = reply.decode("utf-8")

        return self.parseGetSensorValsMsg(reply)

    def updatePWM(self, pwm, val):
        #TODO implement IPC

#        pwmCode = str(pwm.type)

#        from AlphaBot import PINS
#
#        if pwm.type == PINS["ENA"]:
#            pwmCode = "A"
#        elif pwm.type == PINS["ENB"]:
#            pwmCode = "B"
#        else:
#            pwmCode = "N"

        from AlphaBot import PINS

        if pwm == PINS["ENA"]:
            pwmCode = "A"
        elif pwm == PINS["ENB"]:
            pwmCode = "B"
        else:
            pwmCode = "N"

        msg = "updatePWM:"+pwmCode+":"+str(val)
        print("sending = {}".format(msg))

        self.socket.send(msg.encode("utf-8"))
        rsp = self.socket.recv()
        print("rsp = {}".format(rsp))

        pass

    def parseGetSensorValsMsg(self, msgDecoded):
        #TODO implement parsing msg

        #TODO check if header matches?

        sections = msgDecoded.split(":")

        msgContent = sections[1].split(',')
        print("parseGetSensorValsMsg");
        print("sections = {}".format(sections))
        print("msgContent = {}".format(msgContent))


        if len(msgContent) != 5:
            print("ERROR parseGetSensorValsMsg - incorrect number of sensor inputs received!")
            return False

        result = [int(x) for x in msgContent]

        return result

