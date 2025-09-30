# Detect platform
ifeq ($(OS),Windows_NT)
    PLATFORM := windows
    RM := rmdir /S /Q
    define MKDIR_P
        if not exist "$(1)" mkdir "$(1)"
    endef
    PLATFORM_LIBS := -lws2_32
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        PLATFORM := linux
        RM := rm -rf
        define MKDIR_P
            mkdir -p $(1)
        endef
        PLATFORM_LIBS := -lpthread
    else
        $(error Unsupported platform: $(UNAME_S))
    endif
endif

CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -g -std=c++23
LDFLAGS = $(PLATFORM_LIBS)

SRC_DIR = source
HEADER_DIRS = include Config ../Config
BIN_DIR = bin
OBJ_DIR = objects

INCLUDES = $(foreach dir, $(HEADER_DIRS), -I$(dir))

SRCS := $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
EXECUTABLES := $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%, $(SRCS))

all: $(BIN_DIR) $(OBJ_DIR) $(EXECUTABLES)

$(BIN_DIR)/%: $(OBJ_DIR)/%.o
	@$(call MKDIR_P,$(@D))
	@$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "$<"
	@$(call MKDIR_P,$(@D))
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BIN_DIR):
	@$(call MKDIR_P,$(BIN_DIR))

$(OBJ_DIR):
	@$(call MKDIR_P,$(OBJ_DIR))

clean:
	@-$(RM) $(BIN_DIR)
	@-$(RM) $(OBJ_DIR)

TARGET ?= server
run: 
	@$(BIN_DIR)/$(TARGET) $(ARGS)
	
platform:
	@echo Detected platform: $(PLATFORM)

.PRECIOUS: $(OBJS)
.PHONY: all clean run