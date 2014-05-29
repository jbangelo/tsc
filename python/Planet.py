#!/usr/bin/python
# -*- coding: utf-8 -*-

import Degree, SkyObject
from astro import *

class Planet(SkyObject.SkyObject):
	def __init__(self,earth):
		SkyObject.SkyObject.__init__(self)
		#Heliocentric Coordinates
		self.L = None
		self.B = None
		self.R = None
		#Geocentric Ecliptic Coordinates
		self.X = None
		self.Y = None
		self.Z = None
		self.Lambda = None 
		self.Beta = None
		self.earthDist = None #(In A.U.)
		#Phase angle to earth (in degrees)
		self.i = None
		#Illuminated fraction (in %)
		self.k = None
		#light-time delay (in days)
		self.dt = None
		#Light Delay adjusted variables
		self.earthDistdelay = None
		self.Ldelay = None
		self.Bdelay = None
		self.Rdelay = None
		self.Xdelay = None
		self.Ydelay = None
		self.Zdelay = None
		self.Lambdadelay = None
		self.Betadelay = None

		self.lastUsedDate = None

		self.earth = earth

		self.Lterms = None
		self.Bterms = None
		self.Rterms = None
		self.loadTerms()

	def loadTerms(self):
		# A stub function to be implemented by individual planet
		pass

	def heliocentricCoords(self,t):
		self.L = Degree.new_Rad(sumTerms(self.Lterms,t))
		self.B = Degree.new_Rad(sumTerms(self.Bterms,t))
		self.R = sumTerms(self.Rterms,t)

	def getHeliocentricCoords(self):
		if self.L == None or self.B == None or self.R == None:
			self.heliocentricCoords(t)
		return (self.L,self.B,self.R)

	def geocentricEclipticCoords(self):
		(eL,eB,eR) = self.earth.getHeliocentricCoords()

		self.X = self.R*cos(self.B)*cos(self.L) - eR*cos(eB)*cos(eL)
		self.Y = self.R*cos(self.B)*sin(self.L) - eR*cos(eB)*sin(eL)
		self.Z = self.R*sin(self.B) - eR*sin(eB)

		self.Lambda = atan2(self.Y,self.X)
		self.Lambda.normalize()

		self.Beta = atan2(self.Z,sqrt(pow(self.X,2)+pow(self.Y,2)))

		self.earthDist = sqrt(pow(self.X,2)+pow(self.Y,2)+pow(self.Z,2))

	def getGeocentricEclipticCoords(self):
		if self.X == None or self.Y == None or self.Z == None:
			self.geocentircEclipticCoords()
		return (self.X,self.Y,self.Z,self.Lambda,self.Beta)

	def geocentricEquatorialCoords(self):
		ec = Degree.new(23.4392911)

		self.alpha = atan2(sin(self.Lambda)*cos(ec)-tan(self.Beta)*sin(ec),cos(self.Lambda))
		self.alpha.normalize()

		self.delta = asin(sin(self.Beta)*cos(ec) + cos(self.Beta)*sin(ec)*sin(self.Lambda))

	def calcPosition(self,date):
		t = date.J2000m()

		self.heliocentricCoords(t)
		self.geocentricEclipticCoords()
		self.geocentricEquatorialCoords()

	def calcLightDelay(self,date):
		L = self.L
		B = self.B
		R = self.R
		(eL,eB,eR) = self.earth.getHeliocentricCoords()

		dt = 0
		dtprev = 1

		while dt != dtprev:
			dtprev = dt
			t = date.J2000m(deltaDays=dt)

			L = Degree.new(sumTerms(self.Lterms,t))
			B = Degree.new(sumTerms(self.Bterms,t))
			R = sumTerms(self.Rterms,t)

			X = R*cos(B)*cos(L) - eR*cos(eB)*cos(eL)
			Y = R*cos(B)*sin(L) - eR*cos(eB)*sin(eL)
			Z = R*sin(B) - eR*sin(eB)
			Lambda = atan2(Y,X)
			Lambda.normalize()

			Beta = atan2(Z,sqrt(pow(X,2)+pow(Y,2)))
			dt = 0.0057755*sqrt(X*X+Y*Y+Z*Z)

		self.dt = 0.0057755*sqrt(X*X+Y*Y+Z*Z)
		self.earthDistdelay = sqrt(X*X+Y*Y+Z*Z)
		self.Ldelay = L
		self.Bdelay = B
		self.Rdelay = R
		self.Xdelay = X
		self.Ydelay = Y
		self.Zdelay = Z
		self.Lambdadelay = Lambda
		self.Betadelay = Beta
		#geocentricEquatorialCoords(planet,True)

	def getLightDelay(self):
		return self.dt

	def illuminatedFraction(self):
		(eL,eB,eR) = self.earth.getHeliocentricCoords()

		self.i = acos((pow(self.R,2) + pow(self.earthDist,2) - pow(eR,2))/(2*self.R*self.earthDist))

		self.k = (1 + cos(self.i))/2

	def getIlluminatedFraction(self):
		return self.k

	def getPhaseAngle(self):
		return self.i

	def calcMag(self):
		#dummy function to be implimented in individual planets
		pass

	def calculateInfo(self,date):
		if date != self.lastUsedDate:
			self.lastUsedDate = date

			self.calcPosition(date)
			self.calcLightDelay(date)
			self.illuminatedFraction()
			self.calcMag()


