import unittest
import Infrared_Line_Tracking


class Infrared_Line_Tracking_Test(unittest.TestCase):
    def test_dummy(self):
        pass

    def test_AnalogRead(self):
        TR = Infrared_Line_Tracking.TRSensor()
        TR.AnalogRead()

    def test_calibrate(self):
        TR = Infrared_Line_Tracking.TRSensor()
        TR.calibrate()

    def test_readCalibrated(self):
        TR = Infrared_Line_Tracking.TRSensor()
        TR.readCalibrated()

    def test_readLine(self):
        TR = Infrared_Line_Tracking.TRSensor()
        TR.readLine()



if __name__ == '__main__':
    unittest.main()