# Run from cpp/:  make dayNN [2025] [DEBUG=1]
# Layout: util/*.{h,cpp} shared by every year, <YEAR>/dayNN.cpp per puzzle.
# Binaries run from the input/YEAR/ folder, so input paths are just the input filename.

CXX   := g++
# a bare year on the command line picks the year: make day01 2025
YEAR_ARG := $(firstword $(filter 20%,$(MAKECMDGOALS)))
YEAR     ?= $(or $(YEAR_ARG),2026)
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
	@echo "  make dayNN [2025] [DEBUG=1]        build and run dayNN (year defaults to 2026)"
	@echo "  make clean                         remove all build products"

$(UTIL_OBJ_DIR)/%.o: util/%.cpp | $(UTIL_OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DAY_OBJ_DIR)/day%.o: $(YEAR)/day%.cpp | $(DAY_OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/day%: $(DAY_OBJ_DIR)/day%.o $(UTIL_OBJ) | $(BIN_DIR)
	$(CXX) $(OPTFLAGS) $^ -o $@

day%: $(BIN_DIR)/day%
	cd .. && ./cpp/$< input/$(YEAR)/day$*.txt

$(UTIL_OBJ_DIR) $(DAY_OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

clean:
	rm -rf build

-include $(wildcard $(UTIL_OBJ_DIR)/*.d $(DAY_OBJ_DIR)/*.d)

# keep objects and binaries between runs instead of deleting them as intermediates
.SECONDARY:
.PHONY: all help clean

# the year is not a real target; give it a silent no-op so make doesn't complain
ifneq ($(YEAR_ARG),)
.PHONY: $(YEAR_ARG)
$(YEAR_ARG):
	@:
endif
