# Define the compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Werror -std=c++17

# Linker flags
LDFLAGS = -lz -lbz2 -llzma -lzstd

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Executable name
TARGET = $(BIN_DIR)/shazam

# Source files
SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/utils.cpp $(SRC_DIR)/Compressor.cpp

# Object files (replace src/ with obj/ and .cpp with .o in paths)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default target
all: $(TARGET)

# Rule to link the program
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Rule to compile the source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the build
clean:
	rm -f $(TARGET)
	rm -rf $(OBJ_DIR)

# Phony targets
.PHONY: all clean
