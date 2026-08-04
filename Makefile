# Build the main driver and reproduce the finite-DAG data products.
#
#   make
#   make compdb
#   make tidy
#   make findings-2
#   THREADS=32 SORT_MEM=2G make findings-43
#   THREADS=32 make findings-103-scaling
#   THREADS=32 make findings-105
#   make verify
#   make clean

PYTHON     ?= python3
CLANG_TIDY ?= clang-tidy

CPPFLAGS    ?=
CXXFLAGS    ?= -O3 -march=native -std=c++23 -Wall -Wextra
LTOFLAGS    ?= -flto=thin
THREADFLAGS ?= -pthread

LDLIBS  ?=
LDFLAGS ?=

SRC   := src
BIN   := bin
BUILD := build
DATA  := data

DRIVER_SOURCES := \
    $(SRC)/digraph6.cxx \
    $(SRC)/driver.cxx \
    $(SRC)/graph.cxx \
    $(SRC)/spectral_profile.cxx \
    $(SRC)/wl_profile.cxx

GAP_SOURCES := \
    $(SRC)/gap_benchmark.cxx \
    $(SRC)/gap_output.cxx \
    $(SRC)/reference_dag.cxx \
    $(SRC)/route_bridge.cxx \
    $(SRC)/route_scaling.cxx

CLOCK_SOURCES := \
    $(SRC)/gap_clock_control.cxx

FINITE_SOURCES := \
    $(SRC)/gap_finite_closure.cxx \
    $(SRC)/reference_dag.cxx \
    $(SRC)/route_bridge.cxx

DRIVER_OBJECTS := $(patsubst $(SRC)/%.cxx,$(BUILD)/%.o,$(DRIVER_SOURCES))
GAP_OBJECTS    := $(patsubst $(SRC)/%.cxx,$(BUILD)/%.o,$(GAP_SOURCES))
CLOCK_OBJECTS  := $(patsubst $(SRC)/%.cxx,$(BUILD)/%.o,$(CLOCK_SOURCES))
FINITE_OBJECTS := $(patsubst $(SRC)/%.cxx,$(BUILD)/%.o,$(FINITE_SOURCES))

ALL_SOURCES    := $(sort $(DRIVER_SOURCES) $(GAP_SOURCES) \
                         $(CLOCK_SOURCES) $(FINITE_SOURCES))
ALL_OBJECTS    := $(patsubst $(SRC)/%.cxx,$(BUILD)/%.o,$(ALL_SOURCES))
THREAD_OBJECTS := $(sort $(GAP_OBJECTS) $(CLOCK_OBJECTS) $(FINITE_OBJECTS))
DEPENDENCIES   := $(ALL_OBJECTS:.o=.d)

DRIVER_PROGRAM := $(BIN)/driver
GAP_PROGRAM    := $(BIN)/gap-benchmark
CLOCK_PROGRAM  := $(BIN)/gap-clock-control
FINITE_PROGRAM := $(BIN)/gap-finite-closure
VERIFY_SCRIPTS := $(sort $(wildcard scripts/verify_*.py))
COMPDB_TOOL    := scripts/write_compile_commands.py

.PHONY: all clean check-docs compdb tidy verify
.PHONY: findings-2 findings-43 findings-103 findings-103-scaling findings-104
.PHONY: findings-105

all: $(DRIVER_PROGRAM) $(GAP_PROGRAM) $(CLOCK_PROGRAM) $(FINITE_PROGRAM)

check-docs:
	@npm --prefix tools/check-docs ci --ignore-scripts --silent
	@npm --prefix tools/check-docs run check --silent
	@npm --prefix tools/check-docs run validate --silent

compdb:
	@$(PYTHON) "$(COMPDB_TOOL)" --output $(BUILD)/compile_commands.json -- \
		$(MAKE) --no-print-directory -Bn $(ALL_OBJECTS)

tidy: compdb
	$(CLANG_TIDY) -p $(BUILD) $(ALL_SOURCES)

verify: $(GAP_PROGRAM) $(CLOCK_PROGRAM) $(FINITE_PROGRAM)
	@set -eu; \
	count=0; \
	for script in $(VERIFY_SCRIPTS); do \
		printf '==> %s\n' "$$script"; \
		$(PYTHON) "$$script"; \
		count=$$((count + 1)); \
	done;

findings-2: $(DRIVER_PROGRAM)
	@scripts/generate_spectral.sh 4 $(DATA)/findings-2/n4
	@scripts/generate_spectral.sh 5 $(DATA)/findings-2/n5
	@scripts/generate_spectral.sh 6 $(DATA)/findings-2/n6

findings-43: $(DRIVER_PROGRAM)
	@scripts/generate_wl.sh 7 $(DATA)/findings-43/n7
	@scripts/generate_wl.sh 8 $(DATA)/findings-43/n8

findings-103: $(GAP_PROGRAM)
	@THREADS="$(THREADS)" scripts/run_gap_benchmark.sh

findings-103-scaling: $(GAP_PROGRAM)
	@THREADS="$(THREADS)" scripts/run_gap_scaling_benchmark.sh

findings-104: $(CLOCK_PROGRAM)
	@THREADS="$(THREADS)" scripts/run_gap_clock_control.sh

findings-105: $(FINITE_PROGRAM)
	@THREADS="$(THREADS)" scripts/run_gap_finite_closure.sh

$(THREAD_OBJECTS): PRIVATE_CXXFLAGS := $(THREADFLAGS)

$(BUILD)/%.o: $(SRC)/%.cxx
	@mkdir -p "$(@D)"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LTOFLAGS) $(PRIVATE_CXXFLAGS) \
		-MMD -MP -MF "$(@:.o=.d)" -c "$<" -o "$@"

$(DRIVER_PROGRAM): $(DRIVER_OBJECTS)
	@mkdir -p "$(@D)"
	$(CXX) $(CXXFLAGS) $(LTOFLAGS) $(LDFLAGS) \
		-o "$@" $(DRIVER_OBJECTS) $(LDLIBS)

$(GAP_PROGRAM): $(GAP_OBJECTS)
	@mkdir -p "$(@D)"
	$(CXX) $(CXXFLAGS) $(LTOFLAGS) $(THREADFLAGS) $(LDFLAGS) \
		-o "$@" $(GAP_OBJECTS) $(LDLIBS)

$(CLOCK_PROGRAM): $(CLOCK_OBJECTS)
	@mkdir -p "$(@D)"
	$(CXX) $(CXXFLAGS) $(LTOFLAGS) $(THREADFLAGS) $(LDFLAGS) \
		-o "$@" $(CLOCK_OBJECTS) $(LDLIBS)

$(FINITE_PROGRAM): $(FINITE_OBJECTS)
	@mkdir -p "$(@D)"
	$(CXX) $(CXXFLAGS) $(LTOFLAGS) $(THREADFLAGS) $(LDFLAGS) \
		-o "$@" $(FINITE_OBJECTS) $(LDLIBS)

clean:
	rm -rf $(BIN) $(BUILD) $(DATA)
