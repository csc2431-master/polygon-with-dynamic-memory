# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -g

# Directories
BUILDDIR = build
EXEDIR   = exe

# Executable names
TARGET = $(EXEDIR)/polygon
TEST_TARGET = $(EXEDIR)/polygon_test

# Source files
MAIN_SRC = main.cpp
TEST_SRC = test.cpp
POINT_SRC = point.cpp

# Object files
MAIN_OBJ = $(BUILDDIR)/main.o
TEST_OBJ = $(BUILDDIR)/test.o
POINT_OBJ = $(BUILDDIR)/point.o
POLYGON_OBJ = $(BUILDDIR)/polygon.o

# Default rule
all: $(TARGET)

# Build the regular program
$(TARGET): $(MAIN_OBJ) $(POINT_OBJ) $(POLYGON_OBJ) | $(EXEDIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(MAIN_OBJ) $(POINT_OBJ) $(POLYGON_OBJ)

# Build the test program
test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJ) $(POINT_OBJ) $(POLYGON_OBJ) | $(EXEDIR)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJ) $(POINT_OBJ) $(POLYGON_OBJ)

# Pattern rule for compiling .cpp into build/*.o
$(BUILDDIR)/%.o: %.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure the build and exe directories exist
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(EXEDIR):
	mkdir -p $(EXEDIR)

# Cleanup
clean:
	rm -rf $(BUILDDIR) $(EXEDIR)

.PHONY: all clean test