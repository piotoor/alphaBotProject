import collections

class state:
	def __init__ (self, pwma, pwmb):
		#self.state_name = state_name
		self.pwmVals = [pwma, pwmb]


class stateHistory:

	def __init__(self, period = 100):
		self.state_history = collections.deque(maxlen=100)
		self.period = period
		self.iteration = 0

	def add(self, pwma, pwmb):
		self.state_history.append(state(pwma, pwmb))

	def addBasedOnPeriod(self, pwma, pwmb):
		if (self.iteration + 1) % self.period == 0:
			self.add(pwma, pwmb)

		self.iteration = self.iteration+1