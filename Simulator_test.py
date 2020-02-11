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

        rspDecoded = ","
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

    def test_parseGetSensorValsMsg(self):
        print("test_parseGetSensorValsMsg")

        sim = Simulator.Simulator()

        msg = "getSensorValsRsp:0,0,0,0,0"
        result = sim.parseGetSensorValsMsg(msg)
        self.assertEqual(result, [0,0,0,0,0])

        msg = "getSensorValsRsp:10,20,30,40,50"
        result = sim.parseGetSensorValsMsg(msg)
        self.assertEqual(result, [10,20,30,40,50])

        msg = "getSensorValsRsp:100,210,330,440,550"
        result = sim.parseGetSensorValsMsg(msg)
        self.assertEqual(result, [100,210,330,440,550])

        msg = "getSensorValsRsp:1000,1020,1015,959,23"
        result = sim.parseGetSensorValsMsg(msg)
        self.assertEqual(result, [1000,1020,1015,959,23])

        msg = "getSensorValsRsp:1,2"
        result = sim.parseGetSensorValsMsg(msg)
        self.assertFalse(result)

if __name__ == '__main__':
    unittest.main()