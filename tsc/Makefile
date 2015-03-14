CXX=g++
CC=gcc

BIN=tsc
CXXSOURCES=src/main.cpp src/Math/Degree.cpp src/Math/AstroMath.cpp src/Time/Stardate.cpp src/SkyObject/SkyObject.cpp src/SkyObject/Planet.cpp src/SkyObject/Sun.cpp src/SkyObject/Star.cpp
CSOURCES=
OBJECTS=$(CSOURCES:.c=.o) $(CXXSOURCES:.cpp=.o)

TESTBIN=tsc_test
TESTSOURCES=src/test/test_main.cpp src/test/TestStardate.cpp src/test/TestDegree.cpp src/test/TestPlanet.cpp
TESTOBJECTS=$(TESTSOURCES:.cpp=.o)

# Compiler Flags:
#   -c - Compile and assemble, but don't link. Outputs object code
#   -g - Keep debug information
#   -Wall - Enable all warnings
CXXFLAGS=-c -g -Wall

# Compiler Pre-processor Flags:
#   -I - Search this directory for included files
CPPFLAGS=-I$(CURDIR)/include/

# Link Flags:
#   -g - Keep debug information
LDFLAGS=-g -lsqlite3

$(BIN): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(BIN) $(LDFLAGS)

all: $(BIN) $(TESTBIN)

clean:
	rm -f $(OBJECTS) $(BIN) $(TESTOBJECTS) $(TESTBIN)

$(TESTBIN): $(TESTOBJECTS) $(OBJECTS)
	$(CXX) $(TESTOBJECTS) $(filter-out src/main.o,$(OBJECTS)) -o $(TESTBIN) $(LDFLAGS) -lcppunit

test: $(TESTBIN)
	./$(TESTBIN)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $< -o $@

