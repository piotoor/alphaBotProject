import AlphaBot as AlphaBot
import unittest

class TRSensor_Test(unittest.TestCase):

    def test_forward(self):
        ab = AlphaBot.AlphaBot()
        ab.forward()

    def test_stop(self):
        ab = AlphaBot.AlphaBot()
        ab.stop()

    def test_backward(self):
        ab = AlphaBot.AlphaBot()
        ab.backward()

    def test_left(self):
        ab = AlphaBot.AlphaBot()
        ab.left()

    def test_right(self):
        ab = AlphaBot.AlphaBot()
        ab.right()

    def test_setPWMA(self):
        ab = AlphaBot.AlphaBot()
        ab.setPWMA(1)

    def test_setPWMB(self):
        ab = AlphaBot.AlphaBot()
        ab.setPWMB(1)

    def test_setMotor(self):
        ab = AlphaBot.AlphaBot()
        ab.setMotor(1,1)


if __name__ == '__main__':
    unittest.main()