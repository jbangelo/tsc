#!/usr/bin/python

import Degree
from astro import *

class SkyObject(object):
	def __init__(self):
		#Geocentric Equitorial Coordinates (in degrees)
		self.alpha = None
		self.delta = None
		self.M = None
		self.name = None
		self.distance = None

	def setName(self,Name):
		if type(Name) != str:
			Name = str(Name)
		self.name = Name

	def Name(self):
		return self.name

	def getAltAz(self,Lat,Lng,date):
		H = date.apparentSidereal() - Lng - self.alpha
		H.normalize()
	
		y = sin(H)
		x = cos(H)*sin(Lat) - tan(self.delta)*cos(Lat)
		Az = atan2(y, x)
		Alt = asin(sin(Lat)*sin(self.delta) + cos(Lat)*cos(self.delta)*cos(H))

		return (Alt,Az)

	def setRaDec(self,RA,Dec):
		if type(RA) == float:
			RA = Degree.new(RA)
		if type(Dec) == float:
			Dec = Degree.new(Dec)

		self.alpha = RA
		self.delta = Dec
	
	def getRaDec(self):
		return (self.alpha, self.delta)

	def setMag(self,M):
		self.M = M

	def getMag(self):
		return self.M

	def setDistance(self,dist):
		self.distance = dist

	def getDistance(self):
		return self.distance





