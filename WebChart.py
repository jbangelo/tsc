#!/usr/bin/python
# -*- coding: utf-8 -*-

from PIL import Image, ImageDraw, ImageFont, ImageFile
from astro import *
import stardate, Star, Degree
import Sun, Mercury, Venus, Earth, Moon, Mars, Jupiter, Saturn, Neptune, Uranus

imageWidth = imageHeight = 600
letterPadding = 16
circleWidth = imageWidth-letterPadding*2
circleHeight = imageHeight-letterPadding*2

im = Image.new("RGB",(imageWidth,imageHeight))
draw = ImageDraw.Draw(im)
font = ImageFont.truetype("resources/arial.ttf",12)

#date = stardate.stardate(2013,2,8,8)
date = stardate.today()
Lat = Degree.new(34.166013)
Lng = Degree.new(117.254914)
Horizon = Degree.new(0.0)
starMag = 6.0

def drawCircle(draw,font):
	# Draw the circle in the center with enough room for the cardinal direction text
	draw.ellipse([(letterPadding,letterPadding),(circleWidth+letterPadding,circleHeight+letterPadding)],outline="#ff0000")
	(Nwidth, Nheight) = draw.textsize("N",font=font)
	draw.text([imageWidth/2-Nwidth/2, 0],"N", fill="#ff0000", font=font)
	(Swidth, Sheight) = draw.textsize("S",font=font)
	draw.text([imageWidth/2-Swidth/2, imageHeight-Sheight], "S", fill="#ff0000",font=font)
	(Ewidth, Eheight) = draw.textsize("E",font=font)
	draw.text([0, imageHeight/2-Sheight/2], "E", fill="#ff0000", font=font)
	(Wwidth, Wheight) = draw.textsize("W",font=font)
	draw.text([imageWidth-Wwidth, imageHeight/2-Sheight/2], "W", fill="#ff0000", font=font)

def drawStars(draw, date, Lat, Lng, mag):
	sl = Star.getStarsByMag("<=",mag)

	print "Found %d stars." % (len(sl))
	i = 0

	for s in sl:
		(Alt,Az) = s.getAltAz(Lat,Lng,date)
		if Alt >= Horizon:
			i += 1
			(x,y) = AltAz2XY(Alt,Az,circleWidth,circleHeight)
			draw.point([(x+letterPadding,y+letterPadding)],fill="#ffffff")

	print "%d stars up." % (i)
	return i

def drawPlanets(canvas, date, Lat, Lng):
	earth = Earth.new()
	earth.calculateInfo(date)

	sun = Sun.new(earth)
	mercury = Mercury.new(earth)
	venus = Venus.new(earth)
	moon = Moon.new(earth,sun)
	mars = Mars.new(earth)
	jupiter = Jupiter.new(earth)
	saturn = Saturn.new(earth)
	neptune = Neptune.new(earth)
	uranus = Uranus.new(earth)

	planets = [sun, mercury, venus, moon, mars, jupiter, saturn, uranus, neptune]
	up = []

	for p in planets:
		p.calculateInfo(date)
		(Alt,Az) = p.getAltAz(Lat,Lng,date)

		if (Alt >= Horizon):
			print "%s is up." % (p.Name())
			up.append((p,Alt,Az))
			symbol = Image.open("resources/"+p.imageName())
			symbol = symbol.resize((20,20))
			(symwidth, symheight) = symbol.size

			(x,y) = AltAz2XY(Alt,Az,circleWidth,circleHeight)
			x += letterPadding
			y += letterPadding
			box = (int(x-symwidth/2), int(y-symheight/2), int(x+symwidth/2), int(y+symheight/2))
			canvas.paste(symbol, box)

	return up

def drawStats(draw,scount,smag,planets):
	countText = "%d stars up" % (scount)
	magText = "Minimum magnitude: %.1f" % (smag)
	(countWidth, countHeight) = draw.textsize(countText,font=font)
	(magWidth, magHeight) = draw.textsize(magText,font=font)
	draw.text([2, imageHeight-countHeight-magHeight],countText,fill="#ff0000",font=font)
	draw.text([2, imageHeight-magHeight],magText,fill="#ff0000",font=font)

	planets.reverse()
	additionalHeight = 0
	for p in planets:
		(p, Alt, Az) = p
		planetText = p.Name()
		AltText =  "Alt: %s" % (Alt)
		AzText = "Az: %s" % (Az)
		(planetWidth, planetHeight) = draw.textsize(planetText,font=font)
		(AltWidth, AltHeight) = draw.textsize(AltText,font=font)
		(AzWidth, AzHeight) = draw.textsize(AzText,font=font)

		draw.text([imageWidth-AzWidth-2,imageHeight-AzHeight-additionalHeight],AzText,fill="#ff0000",font=font)
		additionalHeight += AzHeight
		draw.text([imageWidth-AltWidth-2,imageHeight-AltHeight-additionalHeight],AltText,fill="#ff0000",font=font)
		additionalHeight += AltHeight
		draw.text([imageWidth-planetWidth-2,imageHeight-planetHeight-additionalHeight],planetText,fill="#ff0000",font=font)
		additionalHeight += planetHeight



starCount = drawStars(draw,date,Lat,Lng, starMag)
planetsUp = drawPlanets(im,date,Lat,Lng)
drawCircle(draw,font)
drawStats(draw, starCount, starMag, planetsUp)

im.save("resources/test.png")
