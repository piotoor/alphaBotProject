import unittest
import Simulator as Simulator
import AlphaBot

class TRSensor_Test(unittest.TestCase):
    def test_dummy(self):
        pass

    def test_getValues(self):
        sim = Simulator.Simulator()
        vals = sim.getSensorValues()
        self.assertEqual(len(vals), 5)

    def test_updatePWM(self):
        ab = AlphaBot.AlphaBot()
        sim = Simulator.Simulator()
        sim.updatePWM(ab.PWMA, 50)

if __name__ == '__main__':
    unittest.main()