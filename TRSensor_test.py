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

    def test_iteration_count(self):
        sensor_values = [0, 0, 0, 0, 0]
        TR = TRSensor.TRSensor()
        TR.readLine(sensor_values)
        TR.readLine(sensor_values)
        TR.readLine(sensor_values)

        self.assertEqual(TR.iteration, 3)


    def test_record_state(self):
        sensor_values = [0, 0, 0, 0, 0]
        TR = TRSensor.TRSensor()
        TR.STATE_HISTORY_PERIOD = 1
        TR.readLine(sensor_values)
        self.assertEqual(len(TR.state_history), 1)

if __name__ == '__main__':
    unittest.main()