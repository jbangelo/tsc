#!/usr/bin/python

import planets, moon, astro, stardate

testLng = -117.254763
testLat = 34.165675
#today = stardate.stardate(2012,11,25,5,55,11)
today = stardate.stardate(1992,12,16)

if __name__ == "__main__":
	print today.millenniaSinceJ2000()
	for ID in range(7):
		planet = planets.getPlanet(ID)
		planets.calculateInfo(planet,today)
		RA = planet.alpha
		Dec = planet.delta
		print "%s: RA = %s (%s), Dec = %s (%s)" % (planets.names[ID], astro.deg2HMS_str(RA), astro.deg2HMS_str(planet.alphadelay),astro.deg2DMS_str(Dec), astro.deg2DMS_str(planet.deltadelay))
