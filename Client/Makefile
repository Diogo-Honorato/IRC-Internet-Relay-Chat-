# Detect platform
ifeq ($(OS),Windows_NT)
    PLATFORM := windows
    RM := del /Q /S
    MKDIR_P := mkdir
    PLATFORM_LIBS := -lws2_32
    
else
    PLATFORM := unix
    RM := rm -rf
    MKDIR_P := mkdir -p
    PLATFORM_LIBS :=
    
endif

CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -g -std=c++23
LDFLAGS = -pthread $(PLATFORM_LIBS)

SRC_DIR = source
HEADER_DIRS = include Config ../Config
BIN_DIR = bin
OBJ_DIR = objects

INCLUDES = $(foreach dir, $(HEADER_DIRS), -I$(dir))

SRCS = $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
EXECUTABLES = $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%, $(SRCS))

all: $(BIN_DIR) $(OBJ_DIR) $(EXECUTABLES)

$(BIN_DIR)/%: $(OBJ_DIR)/%.o
	@$(MKDIR_P) $(@D)
	@$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(MKDIR_P) $(@D)
	@echo Compiling $<
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BIN_DIR):
	@$(MKDIR_P) $(BIN_DIR)

$(OBJ_DIR):
	@$(MKDIR_P) $(OBJ_DIR)

clean:
	@$(RM) $(BIN_DIR) $(OBJ_DIR)

TARGET ?= client
run: all
	@$(BIN_DIR)/$(TARGET)
	
platform:
	@echo Detected platform: $(PLATFORM)

.PRECIOUS: $(OBJS)
.PHONY: all clean run

