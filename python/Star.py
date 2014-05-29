#!/usr/bin/python

import struct, sqlite3
import SkyObject, Degree

DBFILE = "resources/skyobjects.sql"

def new():
	return Star()

class Star(SkyObject.SkyObject):
	def __init__(self):
		SkyObject.SkyObject.__init__(self)
		self.BayFlam = ""
		self.Gliese = ""
		self.distance = ""

	def setMag(self, Mag, AbsMag):
		self.M = Mag
		self.absM = AbsMag

	def setBayFlam(self, BF):
		self.BayFlam = BF

	def setGliese(self, G):
		self.GLiese = G

	def setDist(self, d):
		self.distance = d

	def __repr__(self):
		s = "%s (%f, %s, %s)" % (self.name, self.M, self.alpha, self.delta)
		return s

def row2Star(row):
	s = Star()
	s.setName(row["Name"])
	s.setRaDec(Degree.new_H(row["RA"]),Degree.new(row["Dec"]))
	s.setMag(float(row["Mag"]), float(row["AbsMag"]))
	s.setBayFlam(row["BayerFlamsteed"])
	s.setGliese(row["Gliese"])
	s.setDist(row["Distance"])

	return s

def getStarList():
	conn = sqlite3.connect(DBFILE)
	conn.row_factory = sqlite3.Row # Makes rows act like dictionaries
	cur = conn.cursor()

	sl = []

	cur.execute("SELECT * FROM Stars")

	row = cur.fetchone()

	for row in cur.fetchall():
		s = row2Star(row)
		sl.append(s)

	conn.close()

	return sl

def getStarsByMag(relation, mag):
	if type(mag) != float:
		raise TypeError

	conn = sqlite3.connect(DBFILE)
	conn.row_factory = sqlite3.Row
	cur = conn.cursor()

	sl = []

	if relation == ">=":
		cur.execute("SELECT * FROM Stars WHERE Mag >= ? ORDER BY Mag",(mag,))
	elif relation == "<=":
		cur.execute("SELECT * FROM Stars WHERE Mag <= ? ORDER BY Mag",(mag,))
	elif relation == ">":
		cur.execute("SELECT * FROM Stars WHERE Mag > ? ORDER BY Mag",(mag,))
	elif relation == "<":
		cur.execute("SELECT * FROM Stars WHERE Mag < ? ORDER BY Mag", (mag,))

	for row in cur.fetchall():
		s = row2Star(row)
		sl.append(s)

	conn.close()

	return sl


