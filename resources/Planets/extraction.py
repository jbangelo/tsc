#!/usr/bin/python

import sqlite3
import sys

def extract(filename, cursor):
	dataFile = open(filename,"r")
	lines = dataFile.readlines()
	dataFile.close()
	
	planet = ""
	lbr = ""
	order = 0
	index = 0
	firstLine = True

	for line in lines:
		if line[1] == "V":
			planet = line[18:27].strip().lower()
			lbr = line[40:43].strip().lower()
			order = line[59:61].strip().lower()
	
			if lbr == "1":
				lbr = "l"
			elif lbr == "2":
				lbr = "b"
			elif lbr == "3":
				lbr = "r"
			else:
				print "Invalid lbr value: " + lbr
				print line
				exit()
			if firstLine:
				cmd = "CREATE TABLE " + planet + " (LBR CHAR, power INT, element INT, A DOUBLE, B DOUBLE, C DOUBLE)"
				cursor.execute(cmd)
				firstLine = False
		else:
			index = line[5:11].strip().lower()
			A = line[79:98]
			B = line[98:112]
			C = line[112:132]
			cmd = "INSERT INTO " + planet + " VALUES ('" + lbr + "'," + order + "," + index + "," + A + "," + B + "," + C + ")"
			cursor.execute(cmd)


files = ["VSOP87D.ear",  "VSOP87D.mar",  "VSOP87D.nep",  "VSOP87D.ura", "VSOP87D.jup",  "VSOP87D.mer",  "VSOP87D.sat",  "VSOP87D.ven"]

conn = sqlite3.connect("planet.sql")
c = conn.cursor()


for f in files:
	extract(f, c)

conn.commit()
conn.close()

