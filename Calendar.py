#!/usr/bin/python

import stardate, astro

ISLAMICSTART = stardate.stardate(622,7,16)

def gregorianEaster(year):
	a = year%19
	b = year/100
	c = year%100
	d = b/4
	e = b%4
	f = (b+8)/25
	g = (b-f+1)/3
	h = (19*a+b-d-g+15)%30
	i = c/4
	k = c%4
	l = (32+2*e+2*i-h-k)%7
	m = (a+11*h+22*l)/451
	n = (h+l-7*m+114)/31
	p = (h+l-7*m+114)%31

	return stardate.stardate(year,n,p+1)

def julianEaster(year):
	a = year%4
	b = year%7
	c = year%19
	d = (19*c+15)%30
	e = (2*a+4*b-d+34)%7
	f = (d+e+114)/31
	g = (d+e+114)%31

	return stardate.stardate(year,f,g+1)

def getEaster(year):
	if year >= 1583:
		return gregorianEaster(year)
	else:
		return julianEaster(year)

def getPesach(year):
	C = astro.INT(year/100.0)
	S = astro.INT((3.0*C-5)/4.0)
	A = year+3760

	a = (12*year+12)%19
	b = year%4

	Q = -1.904412361576 + 1.554241796621*a + 0.25*b - 0.003177794022*year + S
	j = (astro.INT(Q) + 3*year + 5*b + 2 - S)%7
	r = Q - astro.INT(Q)

	if j == 2 or j == 4 or j == 6:
		D = astro.INT(Q)+23
	elif j == 1 and a > 6 and r >= 0.632870370:
		D = astro.INT(Q) + 24
	elif j == 0 and a > 11 and r >= 0.897723765:
		D = astro.INT(Q) + 23
	else:
		D = astro.INT(Q) + 22

	if D > 31:
		date = stardate.stardate(year,4,D-31)
	else:
		date = stardate.stardate(year,3,D)

	return (date,A)

def getJewishDate(gregorianDate):
	(jewishYearStart,jewishYear) = getPesach(gregorianDate.year-1)
	jewishYearStart.addDays(163)
	print jewishYearStart
	pass

def getIslamicDate(date):
	if date < ISLAMICSTART:
		print "These dates are meaningless since they are before", ISLAMICSTART
	date = date.toJulianCalendar()

	X = date.year
	M = date.month
	D = date.day

	if X%4 == 0:
		W = 1
	else:
		W = 2
	N = astro.INT((275*M)/9.0) - W*astro.INT((M+9)/12.0) + D - 30
	A = X-623
	B = astro.INT(A/4.0)
	C = A%4
	C1 = 365.2501*C
	C2 = astro.INT(C1)
	if C1-C2>0.5:
		C2 += 1
	Dp = 1461*B + 170 + C2
	Q = astro.INT(Dp/10631.0)
	R = Dp%10631
	J = astro.INT(R/354)
	K = R%354
	O = astro.INT((11.0*J + 14)/30.0)
	H = 30*Q + J + 1
	JJ = K - O + N - 1

	if JJ > 354:
		CL = H%30
		DL = (11*CL+3)%30
		if DL < 19:
			JJ -= 354
			H += 1
		elif DL > 18:
			JJ -= 355
			H += 1
		if JJ == 0:
			JJ = 355
			H -= 1

	if JJ == 355:
		m = 12
		d = 30
	else:
		S = astro.INT((JJ - 1)/29.5)
		m = 1 + S
		d = astro.INT(JJ - 29.5*S)

	return (H,m,d)

def getIslamicDate_str(date):
	(Y,M,D) = getIslamicDate(date)

	if M == 1:
		month = "Muharram"
	elif M == 2:
		month = "Safar"
	elif M == 3:
		month = "Rabi'al-Awwal"
	elif M == 4:
		month = "Rabi'ath-Thani"
	elif M == 5:
		month = "Jumada l-Ula"
	elif M == 6:
		month = "Jumada t-Tania"
	elif M == 7:
		month = "Rajab"
	elif M == 8:
		month = "Sha'ban"
	elif M == 9:
		month = "Ramadan"
	elif M == 10:
		month = "Shawwal"
	elif M == 11:
		month = "Dhu l-Qa'da"
	elif M == 12:
		month = "Dhu l-Hijja"
	else:
		month = "Error"

	return "%d %s A.H. %d" % (D,month,Y)


