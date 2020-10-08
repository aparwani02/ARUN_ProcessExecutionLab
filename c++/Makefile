SRCDIR = src
OBJSDIR = build
INCLUDESDIR = include
TESTDIR = tests

SOURCES = shell_utils.cpp process.cpp main.cpp
TESTS = test_parseProcess.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = shell

CXX = g++
CXXFLAGS = -Wall -g -I$(INCLUDESDIR)

all: directories shell 

directories:
	mkdir -p $(OBJSDIR)

# Create the program binary
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) \
			$(OBJSDIR)/*.o

# Compile rules for each dependecy
main.o: $(SRCDIR)/main.cpp
	$(CXX) $(CXXFLAGS) -c -o $(OBJSDIR)/main.o $(SRCDIR)/main.cpp

process.o: $(SRCDIR)/process.cpp
	$(CXX) $(CXXFLAGS) -c -o $(OBJSDIR)/process.o $(SRCDIR)/process.cpp

shell_utils.o: $(SRCDIR)/shell_utils.cpp
	$(CXX) $(CXXFLAGS) -c -o $(OBJSDIR)/shell_utils.o $(SRCDIR)/shell_utils.cpp

# Make the test_runner
test: $(TESTDIR)/test_parseProcess.cpp $(SRCDIR)/process.cpp
	$(CXX) $(CXXFLAGS) -Isrc/ -o test_runner $(TESTDIR)/test_*.cpp $(SRCDIR)/process.cpp

# Rule to clean up intermediate file and executable
clean:
	rm -rf $(OBJSDIR)
	rm -f $(TARGET) test_runner *.o
	
