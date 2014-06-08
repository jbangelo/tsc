CXX=g++
CC=gcc

BIN=tsc
CXXSOURCES=src/main.cpp src/Math/Degree.cpp src/Math/AstroMath.cpp src/Time/Stardate.cpp src/SkyObject/SkyObject.cpp src/SkyObject/Planet.cpp
CSOURCES=src/sqlite3.c
OBJECTS=$(CSOURCES:.c=.o) $(CXXSOURCES:.cpp=.o)

# Compiler Flags:
#	-c - Compile and assemble, but don't link. Outputs object code
#	-g - Keep debug information
#	-Wall - Enable all warnings
CXXFLAGS=-c -g -Wall -std=c++0x

# Compiler Pre-processor Flags:
#	-I - Search this directory for included files
CPPFLAGS=-I$(CURDIR)/include/

# Link Flags:
#	-g - Keep debug information
LDFLAGS=-g 

all: $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $(BIN)

clean:
	rm -f $(OBJECTS) $(BIN)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $< -o $@

src/sqlite3.o : src/sqlite3.c
	$(CC) -c -DSQLITE_THREADSAFE=0 -DSQLITE_OMIT_LOAD_EXTENSION -O2 $< -o $@
