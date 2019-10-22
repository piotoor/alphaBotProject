import unittest
from Infrared_Line_Tracking import InfraredLineTracker
from TRSensor import STATE
from TRSensor import TRSensor
from unittest.mock import Mock

class TRSensor_Test(unittest.TestCase):

    def test_init(self):
        tracker = InfraredLineTracker()

    def test_calculateNewPower(self):
        #TODO expand test
        tracker = InfraredLineTracker()
        tracker.calculateNewPower(1)

    def test_calculatePowerUpdate(self):
        #TODO expand test
        tracker = InfraredLineTracker()
        tracker.calculatePowerUpdate(1)

    def test_run(self):
        #TODO expand test
        tracker = InfraredLineTracker()
        tracker.run(10)

    def test_run_runWithRouteCorrection(self):
        tracker = InfraredLineTracker()
        tracker.testRunWithTestCorrection = True

        #test flow with out of track
        TRSensor.AnalogRead = Mock()
        TRSensor.AnalogRead.return_value = [0, 0, 0, 0, 0]
        tracker.run(10)

        #test flow with on track
        TRSensor.AnalogRead = Mock()
        inputVal = tracker.TR.LINE_THRESHOLD + 50
        TRSensor.AnalogRead.return_value = [inputVal, inputVal, inputVal, inputVal, inputVal]
        tracker.run(10)


if __name__ == '__main__':
    unittest.main()