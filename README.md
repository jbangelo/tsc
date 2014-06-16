tsc
=============

tsc - Short for TinyStarChart

A program to plot the location of planets, stars and other celestial objects in the sky.

# Data and Algorithms

## Planetary Positions

The positions of the planets are estimated using the VSOP87 data and algorithm. 
This was originally developed by P. Bretagnon and G. Francou at the Bureau des 
Longitudes in Paris. The data was downloaded from the  Institut de mécanique 
céleste et de calcul des éphémérides (IMCEE) 
[ftp site](ftp://ftp.imcce.fr/pub/ephem/planets/vsop87/).

## Stars

All of the star location data comes from the HYG catalog, which was created by 
[David Nash](http://www.astronexus.com/) and is a compilation of a selection of 
stars from  the Hipparcos Catalog,the Yale Bright Star Catalog (5th Edition), 
and the Gliese Catalog of Nearby Stars (3rd Edition). The data was downloaded 
from the dataset's [github repo](https://github.com/astronexus/HYG-Database).

## Deep Sky Objects

The NGC2000.0 catalog is used for the deep sky object data set. This is a 
revised and updated version of the original New General Catalog and Index 
Catalog containing many corrections with coordinates based on the J2000.0 epoch. 
The NGC2000.0 catalog was created by R.W. Sinnott at Sky Publishing Corporation 
and is copyrighted by Sky Publishing Corporation. The data was downloaded from 
the Université de Strasbourg 
[VizieR service](ftp://cdsarc.u-strasbg.fr/cats/VII/118/).

## Lunar Position
The position of the Moon is estimated using the ELP2000-82B data and algorithm.
This was originally developed by M. Chapront-Touze, J. Chapront at the Bureau 
des Longitudes in Paris. The data was downloaded from the Institut de mécanique 
céleste et de calcul des éphémérides (IMCEE) 
[ftp site](ftp://ftp.imcce.fr/pub/ephem/moon/elp82b/).

