CXX=g++
CC=gcc

BIN=tsc
CXXSOURCES=src/main.cpp src/Math/Degree.cpp src/Math/AstroMath.cpp src/Time/Stardate.cpp src/SkyObject/SkyObject.cpp src/SkyObject/Planet.cpp src/SkyObject/Sun.cpp src/SkyObject/Star.cpp
CSOURCES=#src/sqlite3.c
OBJECTS=$(CSOURCES:.c=.o) $(CXXSOURCES:.cpp=.o)

# Compiler Flags:
#	-c - Compile and assemble, but don't link. Outputs object code
#	-g - Keep debug information
#	-Wall - Enable all warnings
CXXFLAGS=-c -g -Wall

# Compiler Pre-processor Flags:
#	-I - Search this directory for included files
CPPFLAGS=-I$(CURDIR)/include/

# Link Flags:
#	-g - Keep debug information
LDFLAGS=-g -lsqlite3

all: $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(BIN) $(LDFLAGS)

clean:
	rm -f $(OBJECTS) $(BIN)

test: $(OBJECTS)
	$(MAKE) -C test/

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $< -o $@

src/sqlite3.o : src/sqlite3.c
	$(CC) -c -DSQLITE_THREADSAFE=0 -DSQLITE_OMIT_LOAD_EXTENSION -O2 $< -o $@
