import unittest
import Simulator as Simulator
import AlphaBot

class TRSensor_Test(unittest.TestCase):
    def test_dummy(self):
        pass

    def test_getValues(self):
        sim = Simulator.Simulator()
        vals = sim.getSensorValues()

        valsString = [str(i) for i in vals]

        rspDecoded = ""
        rspDecoded = rspDecoded.join(valsString)
        #rspDecoded = str(rspDecoded)

        print("Simulator_test::test_getValues  Rsp: "+rspDecoded)
        self.assertEqual(len(vals), 5)

    def test_updatePWM(self):
        ab = AlphaBot.AlphaBot()
        sim = Simulator.Simulator()
        sim.updatePWM(ab.PWMA, 50)

        rsp = sim.socket.recv()

        print("Simulator_test::test_updatePWM  Rsp: "+rsp.decode("utf-8"))
        self.assertEqual(rsp, b"updatePwmRsp")

if __name__ == '__main__':
    unittest.main()