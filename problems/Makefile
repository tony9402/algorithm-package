UV ?= uv
CXX ?= g++

ifneq ($(wildcard ../testlib.h),)
JUDGE_SOURCE_ROOT ?= ..
else ifneq ($(wildcard ../../algorithm-local-judge/testlib.h),)
JUDGE_SOURCE_ROOT ?= ../../algorithm-local-judge
else
JUDGE_SOURCE_ROOT ?= ../algorithm-local-judge
endif

PROJECT_ROOT ?= ..
JUDGE_SOURCE_ROOT_ABS := $(abspath $(JUDGE_SOURCE_ROOT))
PROJECT_ROOT_ABS := $(abspath $(PROJECT_ROOT))
UV_CACHE_DIR ?= $(JUDGE_SOURCE_ROOT_ABS)/.uv-cache
PYTHON ?= UV_CACHE_DIR=$(UV_CACHE_DIR) $(UV) run python
PROBLEMS := $(sort $(patsubst %/problem.json,%,$(wildcard */problem.json)))
PROBLEM ?= $(firstword $(PROBLEMS))
PROFILE ?= sample
USER_SRC ?= $(PROBLEM)/solutions/main_solution.ac.cpp
USER_SRC_PATH := $(if $(filter /%,$(USER_SRC)),$(USER_SRC),$(CURDIR)/$(USER_SRC))
PACK_ID ?= basic
PACK_OUT ?= $(PROJECT_ROOT_ABS)/dist/packs
PLATFORM ?=
BUILD_DIR ?= $(PROJECT_ROOT_ABS)/build/tools

JUDGE := cd $(JUDGE_SOURCE_ROOT_ABS) && ALJ_PROJECT_ROOT=$(PROJECT_ROOT_ABS) $(PYTHON) -m judge
CXXFLAGS ?= -std=c++17 -O2 -pipe -I$(JUDGE_SOURCE_ROOT_ABS)

ALL_TOOL_TARGETS := $(foreach P,$(PROBLEMS),$(BUILD_DIR)/$(P)/generator $(BUILD_DIR)/$(P)/validator $(BUILD_DIR)/$(P)/checker $(BUILD_DIR)/$(P)/solution)
PROBLEM_TOOL_TARGETS := $(if $(PROBLEM),$(BUILD_DIR)/$(PROBLEM)/generator $(BUILD_DIR)/$(PROBLEM)/validator $(BUILD_DIR)/$(PROBLEM)/checker $(BUILD_DIR)/$(PROBLEM)/solution)

.DEFAULT_GOAL := help
.PRECIOUS: $(BUILD_DIR)/%/.dir

.PHONY: help all require-problem tools problem-tools compile cases-compile generate run smoke list-problems validate-problems build-pack pack-verify clean

help:
	@echo "Problem targets:"
	@echo "  make tools                       Build tools for every discovered problem"
	@echo "  make problem-tools               Build tools for PROBLEM"
	@echo "  make compile                     Alias for problem-tools"
	@echo "  make cases-compile               Validate cases.yml for PROBLEM/PROFILE"
	@echo "  make generate                    Generate test data for PROBLEM"
	@echo "  make run                         Judge USER_SRC"
	@echo "  make smoke                       Build tools, generate, run, and validate numbering"
	@echo "  make list-problems               List discovered problems"
	@echo "  make validate-problems           Check numbering starts at 1 and is contiguous"
	@echo "  make build-pack                  Build source-free problem pack"
	@echo "  make pack-verify PACK=path       Verify a problem pack"
	@echo "  make clean                       Remove problem tool build outputs"
	@echo ""
	@echo "Variables:"
	@echo "  PROBLEMS=$(PROBLEMS)"
	@echo "  PROBLEM=$(PROBLEM)"
	@echo "  PROFILE=$(PROFILE)"
	@echo "  USER_SRC=$(USER_SRC)"
	@echo "  USER_SRC_PATH=$(USER_SRC_PATH)"
	@echo "  PACK_ID=$(PACK_ID)"
	@echo "  PACK_OUT=$(PACK_OUT)"
	@echo "  JUDGE_SOURCE_ROOT=$(JUDGE_SOURCE_ROOT_ABS)"
	@echo "  PROJECT_ROOT=$(PROJECT_ROOT_ABS)"
	@echo ""
	@echo "Examples:"
	@echo "  make generate PROBLEM=06 PROFILE=sample"
	@echo "  make run PROBLEM=06 USER_SRC=path/to/main.cpp"
	@echo "  make build-pack PROBLEM=06 PACK_ID=basic PLATFORM=macos-arm64"

all: tools

require-problem:
	@if [ -z "$(PROBLEM)" ]; then \
		echo "No problem found. Put problem directories next to this Makefile or pass PROBLEM=<id>."; \
		exit 1; \
	fi

tools: $(ALL_TOOL_TARGETS)

problem-tools: require-problem $(PROBLEM_TOOL_TARGETS)

compile: problem-tools

cases-compile: require-problem
	$(JUDGE) cases compile $(PROBLEM) --profile $(PROFILE)

$(BUILD_DIR)/%/.dir:
	mkdir -p $(@D)
	touch $@

$(BUILD_DIR)/%/generator: %/generator/generator.cpp $(JUDGE_SOURCE_ROOT_ABS)/testlib.h | $(BUILD_DIR)/%/.dir
	$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/%/validator: %/validator/validator.cpp $(JUDGE_SOURCE_ROOT_ABS)/testlib.h | $(BUILD_DIR)/%/.dir
	$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/%/checker: %/checker/judge.cpp $(JUDGE_SOURCE_ROOT_ABS)/testlib.h | $(BUILD_DIR)/%/.dir
	$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/%/solution: %/solutions/main_solution.ac.cpp | $(BUILD_DIR)/%/.dir
	$(CXX) $(CXXFLAGS) $< -o $@

generate: require-problem problem-tools
	$(JUDGE) generate $(PROBLEM) --profile $(PROFILE)

run: require-problem
	$(JUDGE) --problem $(PROBLEM) --profile $(PROFILE) $(USER_SRC_PATH)

smoke: problem-tools generate run validate-problems

list-problems:
	$(JUDGE) list

validate-problems:
	$(JUDGE) list --validate

build-pack: require-problem problem-tools
	$(JUDGE) pack build $(CURDIR)/$(PROBLEM) --pack-id $(PACK_ID) --out $(PACK_OUT) $(if $(PLATFORM),--platform $(PLATFORM),)

pack-verify:
	$(JUDGE) pack verify $(PACK)

clean:
	rm -rf $(BUILD_DIR)
