#!/usr/bin/python

import astro, Degree
import time

LONGMONTH = (1,3,5,7,8,10,12)
SHORTMONTH = (4,6,9,11)

class stardate(object):
	def __init__(self,year,month,day,hour=0,minute=0,second=0):
		self.setYear(year)
		self.setMonth(month)
		self.setDay(day)
		self.setHour(hour)
		self.setMinute(minute)
		self.setSecond(second)

		self.JD = None

	def setYear(self,year):
		self.year = year

	def setMonth(self,month):
		if month > 12:
			self.month = month%12
			self.setYear(self.year + self.month/12)
		else:
			self.month = month
		if LONGMONTH.count(month) : # odd month
			self.monthLength = 31
		elif SHORTMONTH.count(month):
			self.monthLength = 30
		else: # February
			if self.year < 1583: #Julian 
				if self.year%4 == 0:
					self.monthLength = 29
				else:
					self.monthLength = 28
			else: #Gregorian
				if self.year%4 == 0:
					if self.year%100!=0:
						self.monthLength = 29
					elif self.year%400==0:
						self.monthLength = 29
					else:
						self.monthLength = 28
				else:
					self.monthLength = 28

	def setDay(self,day):
		while day > self.monthLength:
			day -= (self.monthLength)
			self.day = 1
			self.setMonth(self.month+1)
		self.day = day

	def setHour(self,hour):
		if hour >= 24:
			self.setDay(self.day+(hour/24))
			self.hour = hour%24
		else:
			self.hour = hour

	def setMinute(self,minute):
		if minute >= 60:
			self.setHour(self.hour + (minute/60))
			self.minute = minute%60
		else:
			self.minute = minute

	def setSecond(self,second):
		if second >= 60:
			self.setMinute(self.minute + (second/60))
			self.second = second%60
		else:
			self.second = second

	def addDays(self,days):
		self.setDay(self.day+days)

	def toJulianDate(self):
		if self.JD != None:
			return self.JD
		Y = self.year
		M = self.month
		D = self.day + (self.hour + (self.minute+self.second/60.0)/60.0)/24.0
		if M <= 2:
			Y -= 1
			M += 12
	
		A = int(Y/100)
		B = 2 - A + int(A/4)
	
		if self < GREGORIAN_START:
			B = 0
	
		self.JD = int(365.25*(Y+4716)) + int(30.6001*(M+1)) + D + B - 1524.5
		return self.JD

	def J2000(self):
		"""J2000(): Returns the number of days since the J2000 epoch"""
		return self.toJulianDate()-2451545.0

	def J2000m(self, deltaDays=0.0):
		"""J2000m(): Returns the number of millenia since the J2000 epoch"""
		return (self.J2000()-deltaDays)/365250.0

	def J2000c(self):
		"""J2000c(): Returns the number of centuries since the J2000 epoch"""
		return self.J2000()/36525.0

	def toJulianCalendar(self):
		if self.isJulian():
			return stardate(self.year,self.month,self.day)
		X = self.year
		M = self.month
		D = self.day

		if M < 3:
			X -= 1
			M += 12

		a = astro.INT(X/100.0)
		B = 2 - a + astro.INT(a/4.0)
		b = astro.INT(365.25*X)+astro.INT(30.6001*(M+1))+D+1722519+B
		c = astro.INT((b-122.1)/365.25)
		d = astro.INT(365.25*c)
		e = astro.INT((b-d)/30.6001)

		day = b-d-astro.INT(30.6001*e)
		if e < 14:
			month = e-1
		elif e > 13:
			month = e - 13
		if month > 2:
			year = c - 4716
		elif month < 3:
			year = c - 4715
		return stardate(year,month,day)

	def isJulian(self):
		return self < GREGORIAN_START

	def isGregorian(self):
		return not self.isJulian()

	def meanSidereal(self):
		T = self.J2000c()
		JD = self.toJulianDate()
		meanSidereal = 280.46061838 + 360.98564736629*(JD-2451545.0) + 0.000387933*T*T - (T*T*T)/38710000.0

		while meanSidereal < 0:
			meanSidereal += 360

		while meanSidereal > 360:
			meanSidereal -= 360

		return Degree.Degree(meanSidereal)

	def nutation(self, trueObliq=True):
		T = self.J2000c()

		Omega = 125.04452 - 1934.136261*T + 0.0020708*T*T + (T*T*T)/450000
		D = (297.85036 +445267.111480*T - 0.0019142*T*T + (T*T*T)/189474)
		M = (357.52772 + 35999.050340*T - 0.0001603*T*T - (T*T*T)/300000)
		Mp= (134.96298 + 477198.867398*T + 0.0086972*T*T + (T*T*T)/56250)
		F = (93.27191 + 483202.017538*T - 0.0036825*T*T + (T*T*T)/327270)

		dPsi = 0.0
		dE = 0.0

		for t in nutTerms:
			arg = Degree.new(D*t[0] + M*t[1] + Mp*t[2] + F*t[3] + Omega*t[4])
			dPsi += (t[5]+(t[6]*T))*astro.sin(arg)
			dE += (t[7]+(t[8]*T))*astro.cos(arg)

		if trueObliq:
			dE = self.meanObliquity() + Degree.new_DMS(0,0,dE*0.0001)
		else:
			dE = degree.new_DMS(0,0,dE*0.0001)

		dPsi = Degree.new_HMS(0,0,dPsi*0.0001)

		return (dPsi,dE)

	def meanObliquity(self):
		T = self.J2000c()
		U = T/100.0

		E0 = Degree.new_DMS(23,26,21.448)-Degree.new_DMS(0,0,4680.93)*U -\
			1.55*U*U + 1999.25*U*U*U - 51.38*pow(U,4) - \
			249.67*pow(U,5) - 39.05*pow(U,6) + 7.12*pow(U,7) + \
			27.87*pow(U,8) + 5.79*pow(U,9) + 2.45*pow(U,10)

		return E0

	def apparentSidereal(self):
		(dPsi, E) = self.nutation(True)

		nutation = (dPsi/15.0)*astro.cos(E)

		return self.meanSidereal() + nutation

	def __ne__(self,other):
		if type(self) != type(other):
			return True
		elif self.year != other.year:
			return True
		elif self.month != other.month:
			return True
		elif self.day != other.day:
			return True
		elif self.hour != other.hour:
			return True
		elif self.minute != other.minute:
			return True
		elif self.second != other.second:
			return True
		else:
			return False

	def __lt__(self,other):
		if self.year < other.year:
			return True
		elif self.year > other.year:
			return False

		if self.month < other.month:
			return True
		elif self.month > other.month:
			return False

		if self.day < other.day:
			return True
		elif self.day > other.day:
			return False

		if self.hour < other.hour:
			return True
		elif self.hour > other.hour:
			return False

		if self.minute < other.minute:
			return True
		elif self.minute > other.minute:
			return False

		if self.second < other.second:
			return True
		elif self.second > other.second:
			return False

		return False

	def __repr__(self):
		if self.month == 1:
			strMonth = "Jan."
		elif self.month == 2:
			strMonth = "Feb."
		elif self.month == 3:
			strMonth = "Mar."
		elif self.month == 4:
			strMonth = "Apr."
		elif self.month == 5:
			strMonth = "May."
		elif self.month == 6:
			strMonth = "Jun."
		elif self.month == 7:
			strMonth = "Jul."
		elif self.month == 8:
			strMonth = "Aug."
		elif self.month == 9:
			strMonth = "Sep."
		elif self.month == 10:
			strMonth = "Oct."
		elif self.month == 11:
			strMonth = "Nov."
		elif self.month == 12:
			strMonth = "Dec."
		else:
			strMonth = "Err."

		date = "%s %d %d" % (strMonth,self.day,self.year)
		time = "%.2d:%.2d:%.2d" % (self.hour, self.minute, self.second)

		return date+" "+time

#Time Zones
tz = {"PST": -8.0,
"PDT": -7.0,
"MST": -7.0,
"MDT": -6.0,
"GMT": +0.0
}

GREGORIAN_START = stardate(1582,2,24)

def today(tz=False):
	if tz:
		today = time.localtime()
	else:
		today = time.gmtime()

	return stardate(today.tm_year, today.tm_mon, today.tm_mday, today.tm_hour, today.tm_min, today.tm_sec)

def midnight():
	tzShift = time.mktime(time.localtime()) - time.mktime(time.gmtime())
	present = time.localtime()
	midnight = time.localtime(time.time() + (24-present.tm_hour-1)*3600.0 + (60-present.tm_min-1)*60.0 + (60-present.tm_sec) - tzShift)

	return stardate(midnight.tm_year, midnight.tm_mon, midnight.tm_mday, midnight.tm_hour, midnight.tm_min, midnight.tm_sec)
	

nutTerms = [
#D  M  M' F  O	      dPsi             dE
(0, 0, 0, 0, 1, -171996, -174.2, +92025, +8.9),
(-2,0, 0, 2, 2,  -13187,   -1.6,  +5736, -3.1),
(0, 0, 0, 2, 2,   -2274,   -0.2,   +977, -0.5),
(0, 0, 0, 0, 2,   +2062,   +0.2,   -895, +0.5),
(0, 1, 0, 0, 0,   +1426,   -3.4,    +54, -0.1),
(0, 0, 1, 0, 0,    +712,   +0.1,     -7,    0),
(-2,1, 0, 2, 2,    -517,   +1.2,   +224, -0.6),
(0, 0, 0, 2, 1,    -386,   -0.4,   +200,    0),
(0, 0, 1, 2, 2,    -301,      0,   +129, -0.1),
(-2,-1,0, 2, 2,    +217,   -0.5,    -95, +0.3),
(-2,0, 1, 0, 0,    -158,      0,      0,    0),
(-2,0, 0, 2, 1,    +129,   +0.1,    -70,    0),
(0, 0,-1, 2, 2,    +123,      0,    -53,    0),
(2, 0, 0, 0, 0,     +63,      0,      0,    0),
(0, 0, 1, 0, 1,     +63,   +0.1,    -33,    0),
(2, 0,-1, 2, 2,     -59,      0,    +26,    0),
(0, 0,-1, 0, 1,     -58,   -0.1,    +32,    0),
(0, 0, 1, 2, 1,     -51,      0,    +27,    0),
(-2,0, 2, 0, 0,     +48,      0,      0,    0),
(0, 0,-2, 2, 1,     +46,      0,    -24,    0),
(2, 0, 0, 2, 2,     -38,      0,    +16,    0),
(0, 0, 2, 2, 2,     -31,      0,    +13,    0),
(0, 0, 2, 0, 0,     +29,      0,      0,    0),
(-2,0, 1, 2, 2,     +29,      0,    -12,    0),
(0, 0, 0, 2, 0,     +26,      0,      0,    0),
(-2,0, 0, 2, 0,     -22,      0,      0,    0),
(0, 0,-1, 2, 1,     +21,      0,    -10,    0),
(0, 2, 0, 0, 0,     +17,   -0.1,      0,    0),
(2, 0,-1, 0, 1,     +16,      0,     -8,    0),
(-2,2, 0, 2, 2,     -16,   +0.1,     +7,    0),
(0, 1, 0, 0, 1,     -15,      0,     +9,    0),
(-2,0, 1, 0, 1,     -13,      0,     +7,    0),
(0,-1, 0, 0, 1,     -12,      0,     +6,    0),
(0, 0, 2,-2, 0,     +11,      0,      0,    0),
(2, 0,-1, 2, 1,     -10,      0,     +5,    0),
(2, 0, 1, 2, 2,      -8,      0,     +3,    0),
(0, 1, 0, 2, 2,      +7,      0,     -3,    0),
(-2,1, 1, 0, 0,      -7,      0,      0,    0),
(0,-1, 0, 2, 2,      -7,      0,     +3,    0),
(2, 0, 0, 2, 1,      -7,      0,     +3,    0),
(2, 0, 1, 0, 0,      +6,      0,      0,    0),
(-2,0, 2, 2, 2,      +6,      0,     -3,    0),
(-2,0, 1, 2, 1,      +6,      0,     -3,    0),
(2, 0,-2, 0, 1,      -6,      0,     +3,    0),
(2, 0, 0, 0, 1,      -6,      0,     +3,    0),
(0,-1, 1, 0, 0,      +5,      0,      0,    0),
(-2,-1,0, 2, 1,      -5,      0,     +3,    0),
(-2,0, 0, 0, 1,      -5,      0,     +3,    0),
(0, 0, 2, 2, 1,      -5,      0,     +3,    0),
(-2,0, 2, 0, 1,      +4,      0,      0,    0),
(-2,1, 0, 2, 1,      +4,      0,      0,    0),
(0, 0, 1,-2, 0,      +4,      0,      0,    0),
(-1,0, 1, 0, 0,      -4,      0,      0,    0),
(-2,1, 0, 0, 0,      -4,      0,      0,    0),
(1, 0, 0, 0, 0,      -4,      0,      0,    0),
(0, 0, 1, 2, 0,      +3,      0,      0,    0),
(0, 0,-2, 2, 2,      -3,      0,      0,    0),
(-1,-1,1, 0, 0,      -3,      0,      0,    0),
(0, 1, 1, 0, 0,      -3,      0,      0,    0),
(0,-1, 1, 2, 2,      -3,      0,      0,    0),
(2,-1,-1, 2, 2,      -3,      0,      0,    0),
(0, 0, 3, 2, 2,      -3,      0,      0,    0),
(2,-1, 0, 2, 2,      -3,      0,      0,    0)
]







