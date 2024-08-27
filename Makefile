# Compiler and flags
CXX ?= g++
CXXFLAGS ?= -std=c++23
INCLUDES ?= -Iinclude

# Directories
SRC_DIR ?= src
INCLUDE_DIR ?= include
TESTS_DIR ?= tests
BUILD_DIR ?= build
OBJ_DIR ?= $(BUILD_DIR)/obj
EXAMPLES_DIR ?= examples
BIN_DIR ?= $(BUILD_DIR)/bin

# Build type and mode
BUILD_TYPE ?= STATIC
BUILD_MODE ?= RELEASE

# Compiler flags based on build mode
ifeq ($(BUILD_MODE), RELEASE)
    CXXFLAGS += -O3 -s
else ifeq ($(BUILD_MODE), DEBUG)
    CXXFLAGS += -g
endif

# Output library name
ifeq ($(BUILD_TYPE), STATIC)
    LIBRARY ?= libauspicious_library.a
else ifeq ($(BUILD_TYPE), SHARED)
    LIBRARY ?= libauspicious_library.so
    LDFLAGS += -shared
endif

# Sources and objects
SRC_FILES ?= $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES ?= $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

TEST_SRC_FILES ?= $(wildcard $(TESTS_DIR)/*.cpp)
TEST_OBJ_FILES ?= $(patsubst $(TESTS_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_SRC_FILES))

EXAMPLE_SRC_FILES ?= $(wildcard $(EXAMPLES_DIR)/*.cpp)
EXAMPLE_OBJ_FILES ?= $(patsubst $(EXAMPLES_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(EXAMPLE_SRC_FILES))
EXAMPLE_TARGETS ?= $(patsubst $(EXAMPLES_DIR)/%.cpp, $(BUILD_DIR)/%, $(EXAMPLE_SRC_FILES))

# Header files
HEADERS ?= $(wildcard $(INCLUDE_DIR)/*.hpp)
TEST_HEADERS ?= $(HEADERS) $(wildcard $(TESTS_DIR)/*.hpp)
EXAMPLE_HEADERS ?= $(HEADERS)

# Installation directories
PREFIX ?= /usr/local
LIBDIR ?= $(PREFIX)/lib
INCLUDEDIR ?= $(PREFIX)/include

# Targets
.PHONY: all clean test examples install

all: $(LIBRARY) test

# Library target
$(LIBRARY): $(OBJ_FILES)
ifeq ($(BUILD_TYPE), STATIC)
	ar rcs $(BUILD_DIR)/$(LIBRARY) $(OBJ_FILES)
else
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(BUILD_DIR)/$(LIBRARY) $(OBJ_FILES)
endif

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Objects targets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(TESTS_DIR)/%.cpp $(TEST_HEADERS) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(EXAMPLES_DIR)/%.cpp $(EXAMPLE_HEADERS) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Binary targets
test: $(LIBRARY) $(TEST_OBJ_FILES) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(BIN_DIR)/tester $(TEST_OBJ_FILES) -L$(BUILD_DIR) -lauspicious_library

examples: $(LIBRARY) $(EXAMPLE_TARGETS) | $(BIN_DIR)

$(BIN_DIR)/%: $(OBJ_DIR)/%.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $ $< -L$(BIN_DIR) -lauspicious_library

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BUILD_DIR)
