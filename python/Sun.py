#!/usr/bin/python

import Planet, Degree
from astro import *

def new(earth):
	return Sun(earth)

class Sun(Planet.Planet):
	def Name(self):
		return "Sun"

	def calcMag(self):
		self.M = -26.74

	def heliocentricCoords(self,t):
		pass

	def geocentricEclipticCoords(self,date):
		T = date.J2000c()
		U = T/100.0

		(eL,eB,eR) = self.earth.getHeliocentricCoords()

		self.Lambda = eL+Degree.new(180.0)
		self.Beta = eB*-1
		self.R = eR

		E = date.meanObliquity()

		self.X = self.R*cos(self.Beta)*cos(self.Lambda)
		self.Y = self.R*(cos(self.Beta)*sin(self.Lambda)*cos(E) - sin(self.Beta)*sin(E))
		self.Z = self.R*(cos(self.Beta)*sin(self.Lambda)*sin(E) + sin(self.Beta)*cos(E))
		self.earthDist = sqrt(self.X*self.X + self.Y*self.Y + self.Z*self.Z)

	def calcLightDelay(self,date):
		pass

	def illuminatedFraction(self):
		pass

	def calcPosition(self,date):
		t = date.J2000m()

		self.geocentricEclipticCoords(date)
		self.geocentricEquatorialCoords()
	def imageName(self):
		return "Sun_symbol.png"

	def rectCoordsFromOtherEquinox(self,epoch,equinox):
		print "Epoch JD =", epoch.toJulianDate()
		print "Equinox JD =", equinox.toJulianDate()
		t = (epoch.toJulianDate() - 2451545.0)/36525.0
		print "t =",t
		X0 = self.X + 0.000000440360*self.Y - 0.000000190919*self.Z
		Y0 = -0.000000479966*self.X + 0.917482137087*self.Y - 0.397776982902*self.Z
		Z0 = 0.397776982902*self.Y + 0.917482137087*self.Z
		print "X0 =",X0
		print "Y0 =",Y0
		print "Z0 =",Z0

		ksi = Degree.new_DMS(0,0,2306.2181)*t + Degree.new_DMS(0,0,0.30188)*t*t + Degree.new_DMS(0,0,0.017998)*t*t*t
		zeta = Degree.new_DMS(0,0,2306.2181)*t + Degree.new_DMS(0,0,1.09468)*t*t + Degree.new_DMS(0,0,0.018203)*t*t*t
		theta = Degree.new_DMS(0,0,2004.3109)*t - Degree.new_DMS(0,0,0.42665)*t*t - Degree.new_DMS(0,0,0.041833)*t*t*t
		print "ksi =",ksi
		print "zeta =",zeta
		print "theta =",theta

		Xx = cos(ksi)*cos(zeta)*cos(theta) - sin(ksi)*sin(zeta)
		Xy = sin(ksi)*cos(zeta) + cos(ksi)*sin(zeta)*cos(theta)
		Xz = cos(ksi)*sin(theta)
		Yx = -cos(ksi)*sin(zeta) - sin(ksi)*cos(zeta)*cos(theta)
		Yy = cos(ksi)*cos(zeta) - sin(ksi)*sin(zeta)*cos(theta)
		Yz = -sin(ksi)*sin(theta)
		Zx = -cos(zeta)*sin(theta)
		Zy = -sin(zeta)*sin(theta)
		Zz = cos(theta)
		print "Xx =",Xx
		print "Xy =",Xy
		print "Xz =",Xz
		print "Yx =",Yx
		print "Yy =",Yy
		print "Yz =",Yz
		print "Zx =",Zx
		print "Zy =",Zy
		print "Zz =",Zz

		Xs = Xx*X0 + Yx*Y0 + Zx*Z0
		Ys = Xy*X0 + Yy*Y0 + Zy*Z0
		Zs = Xz*X0 + Yz*Y0 + Zz*Z0

		return (Xs,Ys,Zs)



