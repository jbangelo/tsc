#!/usr/bin/python

import sys
import stardate, Degree
import Star, Messier
import Sun, Mercury, Venus, Earth, Moon, Mars, Jupiter, Saturn, Neptune, Uranus

Lat = Degree.new(34.166013)
Lng = Degree.new(117.254914)
Horizon = Degree.new(0.0)

args = sys.argv[0:]

if args[1] == "Tonight":
	date = stardate.midnight()
else:
	year = int(args[1])
	month = int(args[2])
	day = int(args[3])
	hour = int(args[4])
	timezone = args[5]
	date = stardate.new(year,month,day,hour-stardate.tz[timezone])

print "Calculating positions for %s GMT" % (date)

earth = Earth.new()
earth.calculateInfo(date)

planets = []
sun = Sun.new(earth)
planets.append(sun)
#mercury = Mercury.new(earth)
planets.append(Mercury.new(earth))
#venus = Venus.new(earth)
planets.append(Venus.new(earth))
#moon = Moon.new(earth,sun)
planets.append(Moon.new(earth,sun))
#mars = Mars.new(earth)
planets.append(Mars.new(earth))
#jupiter = Jupiter.new(earth)
planets.append(Jupiter.new(earth))
#saturn = Saturn.new(earth)
planets.append(Saturn.new(earth))
#neptune = Neptune.new(earth)
planets.append(Neptune.new(earth))
#uranus = Uranus.new(earth)
planets.append(Uranus.new(earth))


print "Planets that are up:"

for p in planets:
	p.calculateInfo(date)
	(Alt,Az) = p.getAltAz(Lat,Lng,date)
	if Alt >= Horizon:
		print "%s: %s Alt, %s Az" % (p.Name(), Alt, Az)

print "Stars that are up:"
starList = Star.getStarsByMag("<=", +1.0)
for s in starList:
	(Alt,Az) = s.getAltAz(Lat,Lng,date)
	if Alt >= Horizon and s.Name() != "":
		print "%s: %s Alt, %s Az, %f Mag" % (s.Name(), Alt, Az, s.getMag())

print "Messier Objects that are up:"
messierList = Messier.getMessierList()
for m in messierList:
	(Alt,Az) = m.getAltAz(Lat,Lng,date)
	if Alt >= Horizon:
		if (m.Name() == ""):
			name = "M%d (NGC%d)" % (m.getMessierNumber(), m.getNGCNumber())
		else:
			name = m.Name()[:-1]
		print "%s %s Alt, %s Az, %f Mag" % (name, Alt, Az, m.getMag())

