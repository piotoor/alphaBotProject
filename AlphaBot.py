import RPi.GPIO as GPIO
import time

PINS = {
	"IN1": 12,
	"IN2": 13,
	"IN3": 20,
	"IN4": 21,
	"ENA": 6,
	"ENB": 26
}

class AlphaBot(object):

	#def __init__(self,in1=12,in2=13,ena=6,in3=20,in4=21,enb=26):
	def __init__(self):
		self.IN1 = PINS["IN1"]
		self.IN2 = PINS["IN2"]
		self.IN3 = PINS["IN3"]
		self.IN4 = PINS["IN4"]
		self.ENA = PINS["ENA"]
		self.ENB = PINS["ENB"]

		GPIO.setmode(GPIO.BCM)
		GPIO.setwarnings(False)
		GPIO.setup(self.IN1,GPIO.OUT)
		GPIO.setup(self.IN2,GPIO.OUT)
		GPIO.setup(self.IN3,GPIO.OUT)
		GPIO.setup(self.IN4,GPIO.OUT)
		GPIO.setup(self.ENA,GPIO.OUT)
		GPIO.setup(self.ENB,GPIO.OUT)
		self.forward()
		self.PWMA = GPIO.PWM(self.ENA,500)
		self.PWMB = GPIO.PWM(self.ENB,500)
		self.PWMA.start(50)
		self.PWMB.start(50)

		self.PMMACurrentValue = 0
		self.PMMBCurrentValue = 0

		self.useIpc = False
		self.sim = None

	def forward(self):
		GPIO.output(self.IN1,GPIO.HIGH)
		GPIO.output(self.IN2,GPIO.LOW)
		GPIO.output(self.IN3,GPIO.LOW)
		GPIO.output(self.IN4,GPIO.HIGH)

	def stop(self):
		GPIO.output(self.IN1,GPIO.LOW)
		GPIO.output(self.IN2,GPIO.LOW)
		GPIO.output(self.IN3,GPIO.LOW)
		GPIO.output(self.IN4,GPIO.LOW)

	def backward(self):
		GPIO.output(self.IN1,GPIO.LOW)
		GPIO.output(self.IN2,GPIO.HIGH)
		GPIO.output(self.IN3,GPIO.HIGH)
		GPIO.output(self.IN4,GPIO.LOW)

	def left(self):
		GPIO.output(self.IN1,GPIO.LOW)
		GPIO.output(self.IN2,GPIO.LOW)
		GPIO.output(self.IN3,GPIO.LOW)
		GPIO.output(self.IN4,GPIO.HIGH)

	def right(self):
		GPIO.output(self.IN1,GPIO.HIGH)
		GPIO.output(self.IN2,GPIO.LOW)
		GPIO.output(self.IN3,GPIO.LOW)
		GPIO.output(self.IN4,GPIO.LOW)

	def setIpc(self, val):
		self.useIpc = val

	def ChangeDutyCycle(self, pwm, val):  # ipc - inter-process communication
		if self.useIpc:
			pwm.ChangeDutyCycle_ipc(self.sim, val)
		else:
			pwm.ChangeDutyCycle(val)

	def setPWMA(self,value):
		self.PMMACurrentValue = value

		if value > 100: #max
			value = 100
		self.ChangeDutyCycle(self.PWMA, value)

	def setPWMB(self,value):
		self.PMMBCurrentValue = value


		if value > 100:  # max
			value = 100

		self.ChangeDutyCycle(self.PWMB, value)
		
	def setMotor(self, left, right):
		if((right >= 0) and (right <= 100)):
			GPIO.output(self.IN1,GPIO.HIGH)
			GPIO.output(self.IN2,GPIO.LOW)
			self.ChangeDutyCycle(self.PWMA, right)
		elif((right < 0) and (right >= -100)):
			GPIO.output(self.IN1,GPIO.LOW)
			GPIO.output(self.IN2,GPIO.HIGH)
			self.ChangeDutyCycle(self.PWMA, 0 - right)
		if((left >= 0) and (left <= 100)):
			GPIO.output(self.IN3,GPIO.HIGH)
			GPIO.output(self.IN4,GPIO.LOW)
			self.ChangeDutyCycle(self.PWMB, left)
		elif((left < 0) and (left >= -100)):
			GPIO.output(self.IN3,GPIO.LOW)
			GPIO.output(self.IN4,GPIO.HIGH)
			self.ChangeDutyCycle(self.PWMB, 0 - left)

	
