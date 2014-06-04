CXX=g++

BIN=tsc
CXXSOURCES=src/main.cpp src/Math/Degree.cpp src/Math/AstroMath.cpp src/Time/Stardate.cpp src/SkyObject/SkyObject.cpp
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
LDFLAGS=-g

all: $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $(BIN)

clean:
	rm -f $(OBJECTS) $(BIN)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $< -o $@

