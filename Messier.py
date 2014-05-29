import sqlite3
import SkyObject, Degree

DBFILE = "resources/skyobjects.sql"

class Messier(SkyObject.SkyObject):
	def __init__(self):
		SkyObject.SkyObject.__init__(self)
		self.Mnumber = None
		self.NGCnumber = None
		self.MType = None

	def setMessierNumber(self,num):
		self.Mnumber = num

	def getMessierNumber(self):
		return self.Mnumber

	def setNGCNumber(self,num):
		self.NGCNumber = num

	def getNGCNumber(self):
		return self.NGCNumber

	def setType(self,MType):
		if MType == "1":
			self.MType = "Open Cluster"
		elif MType == "2":
			self.MType = "Globular Cluster"
		elif MType == "3":
			self.MType = "Planetary Nebula"
		elif MType == "4":
			self.MType = "Diffuse Nebula"
		elif MType == "5":
			self.MType = "Spiral Galaxy"
		elif MType == "6":
			self.MType = "Elliptical Galaxy"
		elif MType == "7":
			self.MType = "Irregular Galaxy"
		elif MType == "8":
			self.MType = "Lenticular Galaxy"
		elif MType == "9":
			self.MType = "Supernova Remnant"
		elif MType == "A":
			self.MType = "System of 4 stars"
		elif MType == "B":
			self.MType = "Milky Way Patch"
		elif MType == "C":
			self.MType = "Binary star"
		else:
			self.MType = "Error"

def row2Messier(row):
	m = Messier()
	m.setName(row["Comment"])
	m.setMessierNumber(row["MessierNumber"])
	m.setNGCNumber(row["NGCNumber"])
	m.setType(row["Type"])
	m.setRaDec(row["RA"], row["Dec"])
	m.setDistance(row["Distance"])
	m.setMag(row["Mag"])
	return m


def getMessierList():
	conn = sqlite3.connect(DBFILE)
	conn.row_factory = sqlite3.Row # Makes rows act like dictionaries
	cur = conn.cursor()

	ml = []

	cur.execute("SELECT * FROM Messier")

	#row = cur.fetchone()

	for row in cur.fetchall():
		ml.append(row2Messier(row))

	conn.close()

	return ml


