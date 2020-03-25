import unittest
import States

class States_Test(unittest.TestCase):
    def testExample(self):
        print("testExample")

    def testAdd(self):
        history = States.stateHistory()

        history.add(1,1)
        history.add(1,2)
        history.add(1,3)
        history.add(1,4)

        self.assertEqual(len(history.state_history), 4)

    def testAddToCyclicBuffer(self):
        historyLength = 4
        history = States.stateHistory(maxsize=historyLength)

        #add historyLength+1 elements to overflow the collection/buffer
        history.add(1,1)
        history.add(1,2)
        history.add(1,3)
        history.add(1,4)
        history.add(1,5)

        self.assertEqual(len(history.state_history), historyLength)
        self.assertEqual(history.state_history[0].pwmVals[1], 2)   #oldest elem in collection
        self.assertEqual(history.state_history[historyLength-1].pwmVals[1], 5)  #newest elem in collection




if __name__ == '__main__':
    unittest.main()
