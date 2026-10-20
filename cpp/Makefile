# Run from cpp/:  make dayNN [YEAR=2025] [DEBUG=1]
# Layout: util/*.{h,cpp} shared by every year, <YEAR>/dayNN.cpp per puzzle.
# Binaries run from the repo root, so input paths are relative to aoc/.

CXX   := g++
YEAR  ?= 2025
DEBUG ?= 0

ifeq ($(DEBUG), 1)
    MODE     := debug
    OPTFLAGS := -g -O0 -DDEBUG
else
    MODE     := release
    OPTFLAGS := -O2
endif

# -I. makes #include "util/io.h" resolve to cpp/util/io.h
# -MMD -MP write a .d file per object listing the headers it used
CXXFLAGS := -Wall -Wextra -std=c++20 -I. $(OPTFLAGS) -MMD -MP

# debug and release build into separate trees, so switching never reuses stale objects
BUILD_DIR    := build/$(MODE)
UTIL_OBJ_DIR := $(BUILD_DIR)/util
DAY_OBJ_DIR  := $(BUILD_DIR)/$(YEAR)/obj
BIN_DIR      := $(BUILD_DIR)/$(YEAR)/bin

UTIL_SRC := $(wildcard util/*.cpp)
UTIL_OBJ := $(patsubst util/%.cpp,$(UTIL_OBJ_DIR)/%.o,$(UTIL_SRC))

all: help

help:
	@echo "Usage:"
	@echo "  make dayNN [YEAR=2025] [DEBUG=1]   build and run dayNN"
	@echo "  make clean                         remove all build products"

$(UTIL_OBJ_DIR)/%.o: util/%.cpp | $(UTIL_OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DAY_OBJ_DIR)/day%.o: $(YEAR)/day%.cpp | $(DAY_OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/day%: $(DAY_OBJ_DIR)/day%.o $(UTIL_OBJ) | $(BIN_DIR)
	$(CXX) $(OPTFLAGS) $^ -o $@

day%: $(BIN_DIR)/day%
	cd .. && ./cpp/$<

$(UTIL_OBJ_DIR) $(DAY_OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

clean:
	rm -rf build

-include $(wildcard $(UTIL_OBJ_DIR)/*.d $(DAY_OBJ_DIR)/*.d)

# keep objects and binaries between runs instead of deleting them as intermediates
.SECONDARY:
.PHONY: all help clean
