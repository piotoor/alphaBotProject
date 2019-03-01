import unittest
from Infrared_Line_Tracking import InfraredLineTracker

class TRSensor_Test(unittest.TestCase):

    def test_init(self):
        tracker = InfraredLineTracker()

    def test_calculateNewPower(self):
        #TODO expand test
        tracker = InfraredLineTracker()
        tracker.calculateNewPower(1,1)

    def test_calculatePowerUpdate(self):
        #TODO expand test
        tracker = InfraredLineTracker()
        tracker.calculatePowerUpdate(1)

if __name__ == '__main__':
    unittest.main()