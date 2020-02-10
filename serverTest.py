import zmq
import time

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5555")


while True:
    #  Wait for next request from client
    message = socket.recv()
    print("Received request: %s" % message)

    #  Do some 'work'
    time.sleep(0.001)

    message = message.decode("utf-8")

    #  Send reply back to client

    if message == "getSensorVals":
        socket.send(b"getSensorValsRsp")
    elif message == "updatePWM":
        socket.send(b"updatePwmRsp")
    else:
        socket.send(b"Hello")
