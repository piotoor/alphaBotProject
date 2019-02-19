import unittest
import TRSensor as TRSensor

class TRSensor_Test(unittest.TestCase):
    def test_dummy(self):
        pass

    def test_AnalogRead(self):
        TR = TRSensor.TRSensor()
        TR.AnalogRead()

    def test_calibrate(self):
        sensor_values = [ 0, 0, 0, 0, 0]
        TR = TRSensor.TRSensor()
        TR.calibrate(sensor_values)

    def test_readCalibrated(self):
        sensor_values = [0, 0, 0, 0, 0]
        TR = TRSensor.TRSensor()
        TR.readCalibrated(sensor_values)

    def test_readLine(self):
        sensor_values = [0, 0, 0, 0, 0]
        TR = TRSensor.TRSensor()
        TR.readLine(sensor_values)



if __name__ == '__main__':
    unittest.main()