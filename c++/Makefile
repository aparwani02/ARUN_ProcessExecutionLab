TARGET = shell

SRCDIR = ./src
BUILDDIR = ./build
INCLUDESDIR = ./include
TESTDIR = ./tests

# Find all the cpp files for sources
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Substitute .cpp with .o for the generic build rule
OBJS = $(SOURCES:$(SRCDIR)/%.cpp=%.o)

# Gather tests
TESTS = $(wildcard $(TESTDIR)/test_*.cpp)
# CPP files required for the tests
TESTSCPP = $(SRCDIR)/process.cpp


CXX = g++
CXXFLAGS = -Wall -g -I$(INCLUDESDIR)

all: directories $(TARGET)

directories:
	mkdir -p $(BUILDDIR)

# Create the program binary
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) \
			$(BUILDDIR)/*.o

# Generic .cpp to .o rule
%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $(BUILDDIR)/$@

# Make the test_runner
test: $(TESTS) $(TESTSCPP)
	$(CXX) $(CXXFLAGS) -Isrc/ -o test_runner $^

# Rule to clean up intermediate file and executable
clean:
	rm -rf $(BUILDDIR)
	rm -f $(TARGET) test_runner *.o
	
