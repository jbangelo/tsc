from astro import *
import SkyObject, Sun, Earth, Degree
import sqlite3

DBFILE = "resources/skyobjects.sql"

class Asteroid(SkyObject.SkyObject):
	def __init__(self):
		SkyObject.SkyObject.__init__(self)
		self.name = ""

	def setName(self,name):
		self.name = name

	def Name(self):
		return self.name

	def setOrbitalParams(self,a,e,i,p,l,n):
		self.semimajor = a
		self.eccen = e
		self.inclin = i
		self.perihel = p
		self.asendNode = l
		self.meanAnomaly = n
		self.meanMotion = 0.9856076686/(a*sqrt(a))

	def setEpoch(self,epoch):
		self.osculationEpoch = epoch

	def calcPosition(self, date):
		earth = Earth.new()
		earth.calcPosition(date)
		sun = Sun.new(earth)
		sun.calcPosition(date)

		#self.heliocentricCoords()
		#self.geocentricEclipticCoords()
		#self.geocentricEquatorialCoords()

		se = sin(self.osculationEpoch.meanObliquity())
		ce = cos(self.osculationEpoch.meanObliquity())

		F = cos(self.asendNode)
		G = sin(self.asendNode)*ce
		H = sin(self.asendNode)*se
		P = -sin(self.asendNode)*cos(self.inclin)
		Q = cos(self.asendNode)*cos(self.inclin)*ce - sin(self.inclin)*se
		R = cos(self.asendNode)*cos(self.inclin)*se + sin(self.inclin)*ce

		if (F*F + G*G + H*H != 1.0):
			print "F=%f,G=%f,H=%f,%f" % (F,G,H,F*F+G*G+H*H)
		if (P*P + Q*Q + R*R != 1.0):
			print "P=%f,Q=%f,R=%f,%.17f" % (P,Q,R,P*P+Q*Q+R*R)

		A = atan2(F,P)
		B = atan2(G,Q)
		C = atan2(H,R)
		a = sqrt(F*F + P*P)
		b = sqrt(G*G + Q*Q)
		c = sqrt(H*H + R*R)

		Eprev = Degree.new(90)
		E = self.meanAnomaly
		while abs(E.value-Eprev.value) >= Degree.new_DMS(0,0,0.00000001).value:
			Eprev = E
			E = self.meanAnomaly + (180.0/pi)*self.eccen*sin(E)

		self.E = E

		v = atan(sqrt((1+self.eccen)/(1-self.eccen))*tan(self.E/2))*2
		r = self.semimajor*(1-self.eccen*cos(self.E))

		x = r*a*sin(A+self.perihel+v)
		y = r*b*sin(B+self.perihel+v)
		z = r*c*sin(C+self.perihel+v)

		print "x =",x
		print "y =",y
		print "z =",z

		(Xs,Ys,Zs) = sun.rectCoordsFromOtherEquinox(self.osculationEpoch,date)

		print "X' =",Xs
		print "Y' =",Ys
		print "Z' =",Zs

		ksi = Xs + x
		nu = Ys + y
		zeta = Zs + z

		self.alpha = atan2(nu,ksi)
		self.delta = atan2(zeta,sqrt(ksi*ksi + nu*nu))
		self.earthDist = sqrt(ksi*ksi + nu*nu + zeta*zeta)

	def heliocentricCoords(self):
		Eprev = Degree.new(90)
		E = self.meanAnomaly
		while abs(E.value-Eprev.value) >= Degree.new_DMS(0,0,0.00000001).value:
			Eprev = E
			E = self.meanAnomaly + (180.0/pi)*self.eccen*sin(E)

		self.E = E

		v = atan(sqrt((1+self.eccen)/(1-self.eccen))*tan(self.E/2))*2
		r = self.semimajor*(1-self.eccen*cos(self.E))

		u = self.perihel + v
		x = r*(cos(self.asendNode)*cos(u) - sin(self.asendNode)*sin(u)*cos(self.inclin))
		y = r*(sin(self.asendNode)*cos(u) + cos(self.asendNode)*sin(u)*cos(self.inclin))
		z = r*sin(self.inclin)*sin(u)
		self.L = atan2(y,x)
		self.B = asin(z/r)
		self.R = r

	def geocentricEclipticCoords(self):
		(eL,eB,eR) = self.earth.getHeliocentricCoords()

		self.X = self.R*cos(self.B)*cos(self.L) - eR*cos(eB)*cos(eL)
		self.Y = self.R*cos(self.B)*sin(self.L) - eR*cos(eB)*sin(eL)
		self.Z = self.R*sin(self.B) - eR*sin(eB)

		self.Lambda = atan2(self.Y,self.X)
		self.Lambda.normalize()

		self.Beta = atan2(self.Z,sqrt(pow(self.X,2)+pow(self.Y,2)))

		self.earthDist = sqrt(pow(self.X,2)+pow(self.Y,2)+pow(self.Z,2))

	def geocentricEquatorialCoords(self):
		ec = Degree.new(23.4392911)

		self.alpha = atan2(sin(self.Lambda)*cos(ec)-tan(self.Beta)*sin(ec),cos(self.Lambda))
		self.alpha.normalize()

		self.delta = asin(sin(self.Beta)*cos(ec) + cos(self.Beta)*sin(ec)*sin(self.Lambda))

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

			Eprev = Degree.new(90)
			E = self.meanAnomaly
			while abs(E.value-Eprev.value) >= Degree.new_DMS(0,0,0.00000001).value:
				Eprev = E
				E = self.meanAnomaly + (180.0/pi)*self.eccen*sin(E)

			v = atan(sqrt((1+self.eccen)/(1-self.eccen))*tan(self.E/2))*2
			r = self.semimajor*(1-self.eccen*cos(self.E))

			u = self.perihel + v
			x = r*(cos(self.asendNode)*cos(u) - sin(self.asendNode)*sin(u)*cos(self.inclin))
			y = r*(sin(self.asendNode)*cos(u) + cos(self.asendNode)*sin(u)*cos(self.inclin))
			z = r*sin(self.inclin)*sin(u)
			L = atan2(y,x)
			B = asin(z/r)
			R = r

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




def getByName(name):
	conn = sqlite3.connect(DBFILE)
	conn.row_factory = sqlite3.Row
	cur = conn.cursor()

	cur.execute("SELECT * FROM Asteroids WHERE Name=?", (name,))

	row = cur.fetchone()

	if (row == None):
		a = None
	else:
		a = Asteroid()
		a.setName(row["Name"])

		a.setOrbitalParams(row["SemimajorAxis"],row["Eccentricity"],Degree.new(row["Inclination"]),Degree.new(row["Perihelion"]),Degree.new(row["AscendingNode"]),Degree.new(row["Anomaly"]))

	return a


