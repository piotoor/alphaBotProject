#!/usr/bin/python
# -*- coding:utf-8 -*-
import RPi.GPIO as GPIO
import time
import pid
from TRSensor import TRSensor
from AlphaBot import AlphaBot
from TRSensor import STATE

class InfraredLineTracker:
	def __init__(self):

		self.maximum = 35
		self.integral = 0
		self.last_proportional = 0
		
		self.calibrationIterationCount = 400
		self.proportionalCoefficient = 25
		self.derivativeCoefficient = 100
		self.integralCoefficient = 1000

		self.TR = TRSensor()
		self.Ab = AlphaBot()
		self.Ab.stop()

	def run(self, numberOfIterations=-1):
		print("Line follow Example")
		time.sleep(0.5)

		for i in range(0, self.calibrationIterationCount):
			self.TR.calibrate(self.TR.AnalogRead())
			#print (i)

		print(self.TR.calibratedMin)
		print(self.TR.calibratedMax)
		time.sleep(0.5)

		self.Ab.backward()

		iterationCount = numberOfIterations

		while True:
			position = self.TR.readLine(self.TR.AnalogRead())
			pwmaPower, pwmbPower = self.calculatePowerUpdate(position)

			self.Ab.setPWMB(pwmbPower)
			self.Ab.setPWMA(pwmaPower)

			iterationCount = iterationCount-1

			#when numberOfIterations == -1 then run indefinitely
			if iterationCount<0 and numberOfIterations != -1:
				break

			if self.TR.currentState == STATE.outOfTrack:
                #try to get back based on history
				pass


	def calculatePowerUpdate(self, position):
		# x+=1
		# print(position)
		# # The "proportional" term should be 0 when we are on the line.
		# proportional = position - 2000
		#
		# # Compute the derivative (change) and integral (sum) of the position.
		# derivative = proportional - last_proportional
		# integral += proportional
		#
		# # Remember the last position.
		# last_proportional = proportional
		#
		'''
                    // Compute the difference between the two motor power settings,
                    // m1 - m2.  If this is a positive number the robot will turn
                    // to the right.  If it is a negative number, the robot will
                    // turn to the left, and the magnitude of the number determines
                    // the sharpness of the turn.  You can adjust the constants by which
                    // the proportional, integral, and derivative terms are multiplied to
                    // improve performance.
                    '''
		# power_difference = proportional/25 + derivative/100 #+ integral/1000;
		pidObj = pid.pid()
		power_difference = pidObj.calculateDifference(position, self.proportionalCoefficient,
													  self.derivativeCoefficient,
													  self.integralCoefficient)
		pwmaPower, pwmbPower = self.calculateNewPower( power_difference)
		print(position, power_difference)

		return pwmaPower, pwmbPower

	def calculateNewPower(self, power_difference):
		if power_difference > self.maximum:
			power_difference = self.maximum
		if power_difference < - self.maximum:
			power_difference = - self.maximum
		#print(position, power_difference)
		if power_difference < 0:
			pwmbPower = self.maximum + power_difference
			pwmaPower = self.maximum
		else:
			pwmbPower = self.maximum
			pwmaPower = self.maximum - power_difference
		return pwmaPower, pwmbPower


# Simple example prints accel/mag data once per second:
if __name__ == '__main__':

	tracker = InfraredLineTracker()
	tracker.run()
