#!/usr/bin/python
# -*- coding: utf-8 -*-

import astro

def new_HMS(hour,minute,second):
	return Degree((hour+(astro.sign(hour)*minute/60.0)+(astro.sign(hour)*second/3600.0))*15.0)

def new_H(hour):
	return Degree(hour*15.0)

def new_DMS(degree,minute,second):
	return Degree(degree+(astro.sign(degree)*minute/60.0)+(astro.sign(degree)*second/3600.0))

def new_Rad(rad):
	return Degree(rad * (180.0/astro.pi))

def new_str(s):
	return new(float(s))

def new_strH(s):
	return new_H(float(s))

def new(degree):
	return Degree(degree)

class Degree(object):
	def __init__(self,value):
		self.value = value
		self.updateDMS()
		self.updateHMS()

	def updateDMS(self):
		self.degree = int(self.value)
		self.arcFraction = abs(self.value - self.degree)
		self.arcMinute = int(self.arcFraction*60.0)
		self.arcSecond = (self.arcFraction*60.0 - self.arcMinute)*60.0

	def updateHMS(self):
		self.hour = int(self.value/15.0)
		self.fraction = abs((self.value/15.0) - self.hour)
		self.minute = int(self.fraction*60.0)
		self.second = (self.fraction*60.0 - self.minute)*60.0

	def deg(self):
		return self.value

	def abs(self):
		return Degree(abs(self.value))

	def rad(self):
		return self.value*(astro.pi/180.0)

	def arcSec(self):
		return self.arcSecond

	def Deg_str(self):
		return u"%f" % self.value

	def HMS_str(self):
		return "%dh%dm%fs" % (self.hour, self.minute, self.second)

	def DMS_str(self):
		return u'%d°%d\'%f"' % (self.degree, self.arcMinute, self.arcSecond)

	def DM_str(self):
		return u"%d°%f'" % (self.degree, self.arcMinute+(self.arcSecond/60.0))

	def HM_str(self):
		return "%dh%fm" % (self.degree, self.minute+(self.second/60.0))

	def D_str(self):
		return u"%f°" % self.value

	def normalize(self):
		while self.value < 0.0:
			self.value += 360.0
		while self.value > 360.0:
			self.value -= 360.0

		self.updateDMS()
		self.updateHMS()

	def __repr__(self):
		return self.Deg_str()#self.DMS_str()

	def __add__(self,other):
		if type(other) == type(self):
			return Degree(self.value+other.value)
		else:
			return Degree(self.value+other)
	def __sub__(self,other):
		if type(other) == type(self):
			return Degree(self.value-other.value)
		else:
			return Degree(self.value-other)
	def __mul__(self,other):
		if type(other) == type(self):
			return Degree(self.value*other.value)
		else:
			return Degree(self.value*other)
	def __div__(self,other):
		if type(other) == type(self):
			return Degree(self.value/other.value)
		else:
			return Degree(self.value/other)
	def __le__(self,other):
		return self.value <= other.value
	def __ge__(self,other):
		return self.value >= other.value
	def __eq__(self,other):
		if type(self) == type(other):
			return self.value == other.value
		elif type(other) == type(None):
			return False
		else:
			return self.value == other



