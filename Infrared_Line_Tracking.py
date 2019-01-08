#!/usr/bin/python
# -*- coding:utf-8 -*-
from RPi import RPi as GPIO
import time
import pid
from TRSensor import TRSensor

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(TRSensor.Clock,GPIO.OUT)
GPIO.setup(TRSensor.Address,GPIO.OUT)
GPIO.setup(TRSensor.CS,GPIO.OUT)
GPIO.setup(TRSensor.DataOut,GPIO.IN,GPIO.PUD_UP)

# Simple example prints accel/mag data once per second:
if __name__ == '__main__':

	from AlphaBot import AlphaBot
	
	maximum = 35
	integral = 0
	last_proportional = 0
	
	TR = TRSensor()
	Ab = AlphaBot()
	Ab.stop()
	print("Line follow Example")
	time.sleep(0.5)
	for i in range(0,400):
		TR.calibrate()
		print (i)
	print(TR.calibratedMin)
	print(TR.calibratedMax)
	time.sleep(0.5)	
	Ab.backward()
	while True:
		position = TR.readLine()
		#x+=1
		#print(position)
		
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
		#power_difference = proportional/25 + derivative/100 #+ integral/1000;
		pidObj = pid.pid()
		power_difference = pidObj.calculateDifference(position, 25, 100, 1000)

		if power_difference > maximum:
			power_difference = maximum
		if power_difference < - maximum:
			power_difference = - maximum
		print(position,power_difference)
		if power_difference < 0:
			Ab.setPWMB(maximum + power_difference)
			Ab.setPWMA(maximum)
		else:
			Ab.setPWMB(maximum)
			Ab.setPWMA(maximum - power_difference)
			 

