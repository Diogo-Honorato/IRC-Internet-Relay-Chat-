CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -g -std=c++23
LDFLAGS = -pthread

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
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	@echo $<
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(BIN_DIR) $(OBJ_DIR)

TARGET ?= client
run: all
	@$(BIN_DIR)/$(TARGET)

.PRECIOUS: $(OBJS)
.PHONY: all clean run

