#!/usr/bin/python
# -*- coding: utf-8 -*-

import math, time
import Degree

pi = math.pi

def sqrt(x):
	return math.sqrt(x)
def log10(x):
	return math.log10(x)
def sin(x):
	if type(x) == Degree.Degree:
		return math.sin(x.rad())
	else:
		raise TypeError
def cos(x):
	if type(x) == Degree.Degree:
		return math.cos(x.rad())
	else:
		raise TypeError
def tan(x):
	if type(x) == Degree.Degree:
		return math.tan(x.rad())
	else:
		raise TypeError()
def asin(x):
	return Degree.new_Rad(math.asin(x))
def acos(x):
	return Degree.new_Rad(math.acos(x))
def atan(x):
	return Degree.new_Rad(math.atan(x))
def atan2(y,x):
	return Degree.new_Rad(math.atan2(y,x))
def sign(x):
	if x == 0:
		return 1
	else:
		return (x/abs(x))

def FIX(x):
	return int(x)

def INT(x):
	if x < 0:
		return int(x)-1
	else:
		return int(x)

def radRange(x):
	b = x/(2*pi)
	a = 2*pi*(b-int(b))
	if a < 0:
		a += 2*pi
	return a

def sumTerms(terms,t):
	total = 0.0
	for i in range(len(terms)):
		subTerm = 0.0
		for j in range(len(terms[i])):
			A = terms[i][j][0]
			B = terms[i][j][1]
			C = terms[i][j][2]
			subTerm += A*math.cos(B + C*t)
		total += subTerm*math.pow(t,i)
	return total/(pow(10,8))

def RADec2AltAz(RA,Dec,Lat,Lng,t):
	H = t.apparentSidereal() - Lng - RA
	H.normalize()
	
	y = sin(H)
	x = cos(H)*sin(Lat) - tan(Dec)*cos(Lat)
	Az = atan2(y, x)

	Alt = asin(sin(Lat)*sin(Dec) + cos(Lat)*cos(Dec)*cos(H))

	return (Alt,Az)

def deg2HMS_str(deg):
	hour = (deg/360.0)*24.0
	decimal = hour - int(hour)
	
	hour = int(hour)
	minute = int(decimal*60.0)
	second = int((decimal*60 - minute)*60)

	return "%dh%dm%ds" % (hour, minute, second)

def deg2DM_str(deg):
	decimal = deg - int(deg)

	minute = decimal*60
	if minute < 0:
		minute *= -1
	second = int(decimal*3600) - minute

	return "%d°%f'" % (int(deg),minute)

def deg2DMS_str(deg):
	decimal = deg - int(deg)

	minute = decimal*60
	if minute < 0:
		minute *= -1
	second = (minute - int(minute))*60.0

	return "%d°%f'%f\"" % (int(deg),int(minute),second)

def pol2rect(r,q):
	x = r*cos(q)
	y = r*sin(q)

	return (x,y)

def AltAz2XY(Alt,Az, circleWidth, circleHeight):
	# My first thought was to use cos(Alt) as the radius, but this produced an image with with stars pushed towards the edges. This linear mapping produces more evenly distrubuted images
	r = (-Alt.value/90)+1
	# This manipulation of the Azimuth causes North to be up, and west to be to the right. This make the image mirror the sky when held up to the sky
	q = (Az-90)*-1
	(x,y) = pol2rect(r,q)
	# Scale the x and y coords to the circle size, and center them in the circle
	x = (x*circleHeight/2) + circleHeight/2
	y = (y*circleHeight/2) + circleHeight/2

	return (x,y)

