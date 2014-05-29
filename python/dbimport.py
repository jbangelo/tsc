import sqlite3, Degree

def Asteroid():
	conn = sqlite3.connect("resources/skyobjects.sql")
	cur = conn.cursor()

	fd = open("resources/astorb.dat","r")

	try:
		cur.execute("CREATE TABLE Asteroids(AsteroidID INTEGER, Name TEXT, Computer TEXT, AbsMag REAL, Slope REAL, Color REAL, IRASDiameter REAL, IRASClass TEXT, CrossingType INTEGER, OrbitComputation INTEGER, SurveyID INTEGER, MPCNumber INTEGER, DiscovererID INTEGER, USNORank INTEGER, OrbitalArc INTEGER, ObservationCount INTEGER,OsculationEpoch TEXT, Anomaly REAL, Perihelion REAL, AscendingNode REAL, Inclination REAL, Eccentricity REAL, SemimajorAxis REAL, ComputationDate TEXT, CEU REAL, CEUChange REAL, CEUDate TEXT, NextPEU TEXT, GreatestPEU TEXT, GreatestPEU2 TEXT)")
	except:
		cur.execute("DROP TABLE Messier")
		cur.execute("CREATE TABLE Messier(AsteroidID INTEGER, Name TEXT, Computer TEXT, AbsMag REAL, Slope REAL, Color REAL, IRASDiameter REAL, IRASClass TEXT, CrossingType INTEGER, OrbitComputation INTEGER, SurveyID INTEGER, MPCNumber INTEGER, DiscovererID INTEGER, USNORank INTEGER, OrbitalArc INTEGER, ObservationCount INTEGER, OsculationEpoch TEXT, Anomaly REAL, Perihelion REAL, AscendingNode REAL, Inclination REAL, Eccentricity REAL, SemimajorAxis REAL, ComputationDate TEXT, CEU REAL, CEUChange REAL, CEUDate TEXT, NextPEU TEXT, GreatestPEU TEXT, GreatestPEU2 TEXT)")

	for line in fd:
		try:
			astroID = int(line[0:6])
		except:
			astroID = 0
		name = line[7:25].strip()
		computer = line[26:40].strip()
		absMag = float(line[41:47])
		slope = float(line[48:53])
		try:
			color = float(line[54:58])
		except:
			color = -1.0
		try:
			IRASdia = float(line[59:64])
		except:
			IRASdia = -1.0
		IRASclass = line[65:69].strip()
		misccode = line[70:94] # Split these
		crossingID = int(misccode[0:4])
		orbitcomputation = int(misccode[4:8])
		surveyID = int(misccode[8:12])
		MPCnumber = int(misccode[12:16])
		discovererID = int(misccode[16:20])
		useRank = int(misccode[20:24])
		orbitarc = int(line[95:100])
		obslen = int(line[100:105])
		oscepoch = line[106:114].strip()
		meananomaly = float(line[115:125])
		argperihelion = float(line[126:136])
		longAscending = float(line[137:147])
		inclination = float(line[148:157])
		eccentricity = float(line[158:168])
		semimajor = float(line[169:181])
		computationdate = line[182:190].strip()
		ephemerisuncertanty = float(line[191:198])
		CEUchange = float(line[199:207])
		CEUdate = line[208:216].strip()
		nextPEU = line[217:233].strip()
		greatestPEU = line[234:250].strip()
		greatestPEU2 = line[251:267].strip()

		cur.execute("INSERT INTO Asteroids VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)", (astroID, name, computer, absMag, slope, color, IRASdia, IRASclass, crossingID, orbitcomputation, surveyID, MPCnumber, discovererID, useRank, orbitarc, obslen, oscepoch, meananomaly, argperihelion, longAscending, inclination, eccentricity, semimajor, computationdate, ephemerisuncertanty, CEUchange, CEUdate, nextPEU, greatestPEU, greatestPEU2))

	conn.commit()
	conn.close()
	fd.close()

def StarList():
	conn = sqlite3.connect("resources/skyobjects.sql")
	cur = conn.cursor()

	fd = open("resources/starlist.csv")

	fd.readline()

	cur.execute("CREATE TABLE Stars(Name TEXT, BayerFlamsteed TEXT, Gliese TEXT, ID INTEGER, RA REAL, Dec REAL, Mag REAL, AbsMag REAL, Distance REAL)")

	for line in fd:
		tok = line.split(",")
		id = int(tok[0])
		name = tok[6]
		BayFlam = tok[5]
		Gli = tok[4]
		if tok[7] != "":
			RA = float(tok[7])
		else:
			RA = 0.0
		if tok[8] != "":
			Dec = float(tok[8])
		else:
			Dec = 0.0
		if tok[13] != "":
			Mag = float(tok[13])
		else:
			Mag = 0.0
		if tok[14] != "":
			AbsMag = float(tok[14])
		else:
			AbsMag = 0.0
		if tok[9] != "":
			Dis = float(tok[9])
		else:
			Dis = 0.0
		cur.execute("INSERT INTO Stars VALUES (?,?,?,?,?,?,?,?,?)", (name, BayFlam, Gli, id, RA, Dec, Mag, AbsMag, Dis) )

	conn.commit()
	fd.close()
	conn.close()

def Messier():
	conn = sqlite3.connect("resources/skyobjects.sql")
	cur = conn.cursor()

	fd = open("resources/messier.dat","r")

	try:
		cur.execute("CREATE TABLE Messier(MessierNumber INTEGER, NGCNumber INTEGER, Constellation TEXT, Type TEXT, Subtype TEXT, RA REAL, Dec REAL, Mag REAL, Diameter TEXT, Distance REAL, Comment TEXT)")
	except:
		cur.execute("DROP TABLE Messier")
		cur.execute("CREATE TABLE Messier(MessierNumber INTEGER, NGCNumber INTEGER, Constellation TEXT, Type TEXT, Subtype TEXT, RA REAL, Dec REAL, Mag REAL, Diameter TEXT, Distance REAL, Comment TEXT)")

	for line in fd:
		if (line[0] == "#"):
			continue
		MN = int(line[0:3])
		NGC = int(line[5:9])
		Const = line[10:26].replace('"',"").replace(" ","")

		Type = line[34:36].replace(" ","")
		if Type == "1":
			Type = "Open Cluster"
		elif Type == "2":
			Type = "Globular Cluster"
		elif Type == "3":
			Type = "Planetary Nebula"
		elif Type == "4":
			Type = "Diffuse Nebula"
		elif Type == "5":
			Type = "Spiral Galaxy"
		elif Type == "6":
			Type = "Elliptical Galaxy"
		elif Type == "7":
			Type = "Irregular Galaxy"
		elif Type == "8":
			Type = "Lenticular Galaxy"
		elif Type == "9":
			Type = "Supernova Remnant"
		elif Type == "A":
			Type = "System of 4 stars or Asterism"
		elif Type == "B":
			Type = "Milky Way Patch"
		elif Type == "C":
			Type = "Binary star"

		Subtype = line[37:42].replace(" ","")
		RAHour = int(line[43:45])
		RAMin = float(line[46:50])
		DecDeg = int(line[51:54])
		DecMin = int(line[55:57])
		Mag = float(line[58:62])
		Dia = line[63:72].replace(" ","")
		Dis = float(line[73:82])
		Comm = line[83:]

		RA = Degree.new_HMS(RAHour, RAMin, 0.0)
		Dec = Degree.new_DMS(DecDeg, DecMin, 0.0)

		cur.execute("INSERT INTO Messier VALUES (?,?,?,?,?,?,?,?,?,?,?)", (MN, NGC, Const, Type, Subtype, RA.value, Dec.value, Mag, Dia, Dis, Comm))

	conn.commit()
	conn.close()
	fd.close()


#def Planets():
#	import Earth
#	conn = sqlite3.connect("resources/skyobjects.sql")
#	cur = conn.cursor()
#
#	cur.execute("CREATE TABLE Earth(Term TEXT, Index INTEGER, A REAL, B REAL, C REAL)")
#
#	for t in Eath.Lterms:
#		term = "L0"
