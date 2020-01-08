import unittest
import Simulator as Simulator

class TRSensor_Test(unittest.TestCase):
    def test_dummy(self):
        pass

    def test_getValues(self):
        sim = Simulator.Simulator()
        vals = sim.getSensorValues()
        self.assertEqual(len(vals), 5)


if __name__ == '__main__':
    unittest.main()