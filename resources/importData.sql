CREATE TABLE planets (tid INT, rank INT, ml1 INT, ml2 INT, ml3 INT, ml4 INT, ml5 INT, ml6 INT, ml7 INT, ml8 INT, ml9 INT, ml10 INT, ml11 INT, ml12 INT, S DOUBLE, K DOUBLE, A DOUBLE, B DOUBLE, C DOUBLE);
.mode csv
.import planets_vsop87d.csv planets
--CREATE TABLE messier (messierID INT,ngcID INT,contellation TEXT,objectType INT,subtype TEXT,raHours REAL,raMinutes REAL,decDegress REAL,decMinutes REAL,magnitude REAL,diameter TEXT,distance REAL,name TEXT);
--.import messier.csv messier
--CREATE TABLE ngc2000 (ngcID TEXT,type TEXT,raHour REAL,raMin REAL,decDegree REAL,decMin REAL,source INT,constellation TEXT,sizeLimit TEXT,size TEXT,mag REAL,photoMag TEXT,description TEXT,properName TEXT,comment TEXT);
--.import ngc2000.csv ngc2000
CREATE TABLE stars (StarID INT,HIP INT,HD INT,HR INT,Gliese INT,BayerFlamsteed TEXT,ProperName TEXT,RA REAL,Dec REAL,Distance REAL,PMRA REAL,PMDec REAL,RV REAL,Mag REAL,AbsMag REAL,Spectrum TEXT,ColorIndex TEXT,X REAL,Y REAL,Z REAL,VX REAL,VY REAL,VZ REAL);
.import starlist.csv stars
