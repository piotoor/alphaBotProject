import unittest
import pid

class Pid_Test(unittest.TestCase):
    def testCalculateDifference(self):
        pidObj = pid.pid()
        print(pidObj.calculateDifference(1000, 25, 100, 1000))

    def testOnLine(self):
        pidObj = pid.pid()
        self.assertEqual(pidObj.calculateDifference(2000, 25, 100, 1000), 0)

if __name__ == '__main__':
    unittest.main()