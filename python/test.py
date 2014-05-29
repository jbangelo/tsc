#!/usr/bin/python
# -*- coding: utf-8 -*-

import Degree
import stardate
import Calendar
from astro import *
import sys
import Sun, Mercury, Venus, Earth, Moon, Mars, Jupiter, Saturn, Neptune, Uranus
import Star, Asteroid
from PIL import Image, ImageDraw

print "AltAz test:"
d1 = stardate.stardate(1987,4,10,19,21,00)
print "meanSidereal0 = %s" % (d1.meanSidereal().HMS_str())
Lng = Degree.new_HMS(5,8,15.7)
print "Lng = %s" % (Lng.HMS_str())
Lat = Degree.new_DMS(38,55,17)
print "Lat = %s" % (Lat.DMS_str())
RA = Degree.new_HMS(23,9,16.641)
Dec = Degree.new_DMS(-6,43,11.61)
print "Apparent sidereal = %s" %(d1.apparentSidereal().HMS_str())
(Alt,Az) = RADec2AltAz(RA,Dec,Lat,Lng,d1)
print "Alt = %s" % Alt
print "Az = %s" % Az


print "\n\n\n"
#d2 = stardate.stardate(2012,11,24,00,00,00)
#d2 = stardate.stardate(1992,12,20,00,00,00)
d2 = stardate.stardate(2013,1,13,8)

earth = Earth.new()
earth.calculateInfo(d2)

sun = Sun.new(earth)
mercury = Mercury.new(earth)
venus = Venus.new(earth)
moon = Moon.new(earth,sun)
mars = Mars.new(earth)
jupiter = Jupiter.new(earth)
saturn = Saturn.new(earth)
neptune = Neptune.new(earth)
uranus = Uranus.new(earth)

planets = [sun, mercury, venus, moon, mars, jupiter, saturn, uranus, neptune]

print "Planet Info test:"

for p in planets:
	p.calculateInfo(d2)

t = d2.J2000m()
print d2.toJulianDate()
print "%.12f" % t

print "L=",venus.L
print "B=",venus.B
print "R=",venus.R
print "X=", venus.X
print "Y=",venus.Y
print "Z=",venus.Z
print "lambda=",venus.Lambda
print "beta=",venus.Beta
print "alpha=",venus.alpha.HMS_str()
print "delta=",venus.delta.DM_str()
print "EarthDist=",venus.earthDist
print "dt=",venus.dt
print "k=",venus.k
print "cos(i)=",cos(venus.i)
print "mag=",venus.M

print "\n\n\n"

#Lat = Degree.new_DMS(33.0,52, 16)
#Lng = Degree.new_DMS(115, 47, 2)
Lat = Degree.new(34.166013)
Lng = Degree.new(117.254914)

print Lat.DMS_str()
print Lng.DMS_str()

for p in planets:
	#p = planets[i]
	(Alt,Az) = p.getAltAz(Lat,Lng,d2)
	print p.Name()
	#print "alpha=",p.alpha.HMS_str()
	#print "delta=",p.delta.DM_str()
	print "Alt=",Alt.D_str()
	print "Az=",Az.D_str()


print "\n\n\n"
print "Moon test:"
d3 = stardate.stardate(1992,4,12)
#d3 = stardate.stardate(2013,1,11)
earth.calculateInfo(d3)
sun.calculateInfo(d3)
moon = Moon.Moon(earth,sun)
moon.calculateInfo(d3)


print "Phase Angle:",moon.i
print "Illuminated Fraction: %d%%" % int(round(moon.k*100))

k1 = moon.k
d4 = stardate.stardate(1992,4,12,0,0,1)
earth.calculateInfo(d4)
sun.calculateInfo(d4)
moon.calculateInfo(d4)
print "1 second variation:", (k1-moon.k)

print "\n\n\n"
print "Stars test:"

print "Loading star database...",
sys.stdout.flush()
sl = Star.getStarsByMag("<",2.0)
print "done!"
i = len(sl)

print i

width = height = 600
print "\n\n\n"
print "Image test:"
im = Image.new("RGB",(width,height))
draw = ImageDraw.Draw(im)
draw.ellipse([(0,0),(width-31,height-31)],outline="#ff0000")

Horizon = Degree.new(0.0)

d5 = stardate.stardate(2013,2,8,6)

for s in sl:
	(Alt,Az) = s.getAltAz(Lat,Lng,d2)
	if Alt >= Horizon:
		r = cos(Alt)
		q = (Az+90)
		(x,y) = pol2rect(r,q)
		x = ((x*width/2) + width/2)*-1 + width
		y = (y*height/2) + height/2
		draw.point([(x,y)],fill="#ffffff")
		print s.Name(), Alt, Az ,x, y


im.save("resources/test.png")

print "\n\n\nAsteroid test:"
epoch = stardate.stardate(1990,10,28,13,0,29)
date = stardate.stardate(1990,10,6)
earth.calcPosition(date)
a = 2.2091404
e = 0.8502196
i = Degree.new(11.94524)
O = Degree.new(334.75006)
w = Degree.new(186.23352)
ma = Degree.new(-6.767367)

ester = Asteroid.Asteroid()
ester.setOrbitalParams(a,e,i,w,O,ma)
ester.setEpoch(epoch)
ester.calcPosition(date)
print "RA =", ester.alpha.HMS_str()
print "Dec =", ester.delta.DMS_str()

#sun.rectCoordsFromOtherEquinox(stardate.stardate(2044,1,1,12),stardate.stardate(1992,10,13))
#print "2012 DA 14 Test:"
#date2 = stardate.stardate(2013,2,15,19,25)
#da14 = Asteroid.getByName("2012 DA14")
#da14.calcPosition(date2)
#print da14.earthDist

d = Degree.new(1.2)

print d.D_str()
print d.DM_str()
print d.DMS_str()
print d.arcFraction
print d.arcMinute
print "%.15f" % d.arcSecond
