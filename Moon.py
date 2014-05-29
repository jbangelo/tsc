#!/usr/bin/python

# The algorithm here was taken from javascript in 
# http://www.stargazing.net/kepler/jsmoon.html
# The author of that page claims it is a simplified version of a algorithm from 
# 'Astronomical Algorithms' (1st Ed. Chap. 51)

from astro import *
import Planet, Degree

def new(earth,sun):
	return Moon(earth,sun)

class Moon(Planet.Planet):
	def __init__(self,earth,sun):
		Planet.Planet.__init__(self,earth)
		self.sun = sun

	def Name(self):
		return "Moon"

	def calculateInfo(self,date):
		if date != self.lastUsedDate:
			self.lastUsedDate = date

			self.calcPosition(date)
			#self.calcLightDelay(date)
			self.illuminatedFraction()
			self.calcMag()

	def calcPosition(self,date):
		t = date.J2000m()

		self.geocentricEclipticCoords(date)
		self.geocentricEquatorialCoords()

	def heliocentricCoords(self,t):
		pass

	def geocentricEclipticCoords(self,date):
		T = date.J2000c()

		Lp = Degree.new(218.316447) + \
			Degree.new(481267.88123421)*T - \
			Degree.new(0.0015786)*T*T + \
			T*T*T/538841 - T*T*T*T/65194000
		D = Degree.new(297.8501921) + \
			Degree.new(445267.1114034)*T - \
			Degree.new(0.0018819)*T*T + \
			T*T*T/545868 - T*T*T*T/113065000
		M = Degree.new(357.5291092) + \
			Degree.new(35999.0502909)*T - \
			Degree.new(0.0001536)*T*T + \
			T*T*T/24490000
		Mp = Degree.new(134.9633964) + \
			Degree.new(477198.8675055)*T + \
			Degree.new(0.0087414)*T + \
			T*T*T/3526000 + T*T*T*T/14712000
		F = Degree.new(93.2720950) + \
			Degree.new(483202.0175233)*T - \
			Degree.new(0.0036539)*T*T - \
			T*T*T/3526000 + T*T*T*T/863310000
		A1 = Degree.new(119.75) + Degree.new(131.849)*T
		A2 = Degree.new(53.09) + Degree.new(479264.290)*T
		A3 = Degree.new(313.45) + Degree.new(481266.484)*T

		Lsum = 0.0
		Rsum = 0.0
		Bsum = 0.0

		for t in LRterms:
			arg = D*t[0] + M*t[1] + Mp*t[2] + F*t[3]
			Lsum += t[4]*sin(arg)
			Rsum += t[5]*cos(arg)

		for t in Bterms:
			arg = D*t[0] + M*t[1] + Mp*t[2] + F*t[3]
			Bsum += t[4]*sin(arg)

		Lsum += 3958*sin(A1) + 1962*sin(Lp - F) + 318*sin(A2)
		Bsum += -2235*sin(Lp) + 382*sin(A3) + 175*sin(A1 - F) + \
			175*sin(A1 + F) + 127*sin(Lp - Mp) - 115*sin(Lp + Mp)

		self.Lambda = Lp + (Lsum/1000000)
		self.Lambda.normalize()
		self.Beta = Degree.new(Bsum/1000000)
		self.earthDist = (385000.56 + Rsum/1000)/149597870.7

	def illuminatedFraction(self):
		(sRA, sDec) = self.sun.getRaDec()
		#(sX,sY,sZ,sLambda,sBeta) = self.sun.getGeocentricEclipticCoords()

		Psi = acos(sin(sDec)*sin(self.delta) + cos(sDec)*cos(self.delta)*cos(sRA-self.alpha))
		#print Psi

		y = self.sun.earthDist*sin(Psi)
		x = self.earthDist - self.sun.earthDist*cos(Psi)
		self.i = atan2(y,x)

		self.k = (1 + cos(self.i))/2



LRterms = [
(0, 0, 1, 0,6288774, -20905355),
(2, 0,-1, 0,1274027,  -3699111),
(2, 0, 0, 0, 658314,  -2955968),
(0, 0, 2, 0, 213618,   -569925),
(0, 1, 0, 0,-185116,     48888),
(0, 0, 0, 2,-114332,     -3149),
(2, 0,-2, 0,  58793,    246158),
(2,-1,-1, 0,  57066,   -152138),
(2, 0, 1, 0,  53322,   -170733),
(2,-1, 0, 0,  45758,   -204586),
(0, 1,-1, 0, -40923,   -129620),
(1, 0, 0, 0, -34720,    108743),
(0, 1, 1, 0, -30383,    104755),
(2, 0, 0,-2, +15327,     10321),
(0, 0, 1, 2, -12528,         0),
(0, 0, 1,-2,  10980,     79661),
(4, 0,-1, 0,  10675,    -34782),
(0, 0, 3, 0,  10034,    -23210),
(4, 0,-2, 0,  +8548,    -21636),
(2, 1,-1, 0,  -7888,     24208),
(2, 1, 0, 0,  -6766,     30824),
(1, 0,-1, 0,  -5163,     -8379),
(1, 1, 0, 0,   4987,    -16675),
(2,-1, 1, 0,   4036,    -12831),
(2, 0, 2, 0,   3994,    -10445),
(4, 0, 0, 0,   3861,    -11650),
(2, 0,-3, 0,  +3665,     14403),
(0, 1,-2, 0,  -2689,     -7003),
(2, 0,-1, 2,  -2602,         0),
(2,-1,-2, 0,  +2390,     10056),
(1, 0, 1, 0,  -2348,      6322),
(2,-2, 0, 0,   2236,     -9884),
(0, 1, 2, 0,  -2120,      5751),
(0, 2, 0, 0,  -2069,         0),
(2,-2,-1, 0,   2048,     -4950),
(2, 0, 1,-2,  -1773,      4130),
(2, 0, 0, 2,  -1595,         0),
(4,-1,-1, 0,   1215,     -3958),
(0, 0, 2, 2,  -1110,         0),
(3, 0,-1, 0,   -892,      3258),
(2, 1, 1, 0,   -810,      2616),
(4,-1,-2, 0,    759,     -1897),
(0, 2,-1, 0,   -713,     -2117),
(2, 2,-1, 0,   -700,      2354),
(2, 1,-2, 0,    691,         0),
(2,-1, 0,-2,    596,         0),
(4, 0, 1, 0,    549,     -1423),
(0, 0, 4, 0,    537,     -1117),
(4,-1, 0, 0,    520,     -1571),
(1, 0,-2, 0,   -487,     -1739),
(2, 1, 0,-2,   -399,         0),
(0, 0, 2,-2,   -381,     -4421),
(1, 1, 1, 0,    351,         0),
(3, 0,-2, 0,   -340,         0),
(4, 0,-3, 0,    330,         0),
(2,-1, 2, 0,    327,         0),
(0, 2, 1, 0,   -323,      1165),
(1, 1,-1, 0,    299,         0),
(2, 0, 3, 0,    294,         0),
(2, 0,-1,-2,      0,      8752)
]

Bterms = [
(0, 0, 0, 1, 5128122),
(0, 0, 1, 1,  280602),
(0, 0, 1,-1,  277693),
(2, 0, 0,-1,  173237),
(2, 0,-1, 1,   55413),
(2, 0,-1,-1,   46271),
(2, 0, 0, 1,   32573),
(0, 0, 2, 1,   17198),
(2, 0, 1,-1,    9266),
(0, 0, 2,-1,    8822),
(2,-1, 0,-1,    8216),
(2, 0,-2,-1,    4324),
(2, 0, 1, 1,    4200),
(2, 1, 0,-1,   -3359),
(2,-1,-1, 1,    2463),
(2,-1, 0, 1,    2211),
(2,-1,-1,-1,    2065),
(0, 1,-1,-1,   -1870),
(4, 0,-1,-1,    1828),
(0, 1, 0, 1,   -1794),
(0, 0, 0, 3,   -1749),
(0, 1,-1, 1,   -1565),
(1, 0, 0, 1,   -1491),
(0, 1, 1, 1,   -1475),
(0, 1, 1,-1,   -1410),
(0, 1, 0,-1,   -1344),
(1, 0, 0,-1,   -1335),
(0, 0, 3, 1,    1107),
(4, 0, 0,-1,    1021),
(4, 0,-1, 1,     833),
(0, 0, 1,-3,     777),
(4, 0,-2, 1,     671),
(2, 0, 0,-3,     607),
(2, 0, 2,-1,     596),
(2,-1, 1,-1,     491),
(2, 0,-2, 1,    -451),
(0, 0, 3,-1,     439),
(2, 0, 2, 1,     422),
(2, 0,-3,-1,     421),
(2, 1,-1, 1,    -366),
(2, 1, 0, 1,    -351),
(4, 0, 0, 1,     331),
(2,-1, 1, 1,     315),
(2,-2, 0,-1,     302),
(0, 0, 1, 3,    -283),
(2, 1, 1,-1,    -229),
(1, 1, 0,-1,     223),
(1, 1, 0, 1,     223),
(0, 1,-2,-1,    -220),
(2, 1,-1,-1,    -220),
(1, 0, 1, 1,    -185),
(2,-1,-2,-1,     181),
(0, 1, 2, 1,    -177),
(4, 0,-2,-1,     176),
(4,-1,-1,-1,     166),
(1, 0, 1,-1,    -164),
(4, 0, 1,-1,     132),
(1, 0,-1,-1,    -119),
(4,-1, 0,-1,     115),
(2,-2, 0, 1,     107)
]





def getPosition(today=None):
	t = daysSinceJ2000()/36525.0

	# Obliquity of ecliptic
	Obl = (84381.448 - 46.815*t)/3600

	# Mean longitude 
	L2 = (218.316 + 481268*t) % 360
	
	# Mean Anomaly for the Sun
	Ms = (357.529+35999*t - 0.0001536*t*t + t*t*t/24490000) % 360

	# Mean Anomaly for the moon
	Mm = (134.963 + 477199*t + 0.008997*t*t + t*t*t/69700) % 360

	# Argument of latitude
	F = (93.2721 + 483202*t - 0.003403*t*t - t*t*t/3526000) % 360
	
	# Mean elongation
	D = (297.85 + 445267*t - 0.00163*t*t + t*t*t/545900) % 360

	# Geocentric Latitude of the moon
	B = 5.128*sind(F) + 0.2806*sind(Mm + F);
	B += 0.2777*sind(Mm - F) + 0.1732*sind(2*D - F);

	# Geocentric Longitude of the moon
	L = 6.289*sind(Mm) + 1.274*sind(2*D - Mm) + 0.6583*sind(2*D)
	L += 0.2136*sind(2*Mm) - 0.1851*sind(Ms) - 0.1143*sind(2*F)
	L += 0.0588*sind(2*D - 2*Mm) + 0.0572*sind(2*D - Ms - Mm)
	L += 0.0533*sind(2*D + Mm) + L2;

	# Right Ascension
	ra = atan2d(sind(L)*cosd(Obl) - tand(B)*sind(Obl), cosd(L))
	dec = asind(sind(B)*cosd(Obl) + cosd(B)*sind(Obl)*sind(L))

	return (ra,dec)



