import unittest
import TRSensor as TRSensor


class TRSensor_Test(unittest.TestCase):
    def test_dummy(self):
        pass

    def test_AnalogRead(self):
        TR = TRSensor.TRSensor()
        TR.AnalogRead()

    def test_calibrate(self):
        TR = TRSensor.TRSensor()
        TR.calibrate()

    def test_readCalibrated(self):
        TR = TRSensor.TRSensor()
        TR.readCalibrated()

    def test_readLine(self):
        TR = TRSensor.TRSensor()
        TR.readLine()



if __name__ == '__main__':
    unittest.main()