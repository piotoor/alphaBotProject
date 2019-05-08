
class pid:
    def __init__(self):
        self.last_proportional = 0
        self.integral = 0

    def calculateDifference(self, position, proportionalCoefficient, derivativeCoefficient, integralCoefficient):
        # The "proportional" term should be 0 when we are on the line.
        proportional = position - 2000

        # Compute the derivative (change) and integral (sum) of the position.
        derivative = proportional - self.last_proportional
        self.integral += proportional

        # Remember the last position.
        self.last_proportional = proportional

        return proportional / proportionalCoefficient + derivative / derivativeCoefficient  # + integral/1000
        #return proportional / 25 + derivative / 100  # + integral/1000
