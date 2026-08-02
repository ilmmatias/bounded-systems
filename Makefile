# Build the main driver and reproduce the finite-DAG data products.
#
#   make
#   make findings-2
#   THREADS=32 SORT_MEM=2G make findings-43
#   THREADS=32 make findings-103-scaling
#   THREADS=32 make findings-105
#   make verify
#   make clean

CXX    ?= clang++
PYTHON ?= python3

CPPFLAGS    ?=
CXXFLAGS    ?= -O3 -march=native -std=c++23 -Wall -Wextra
LTOFLAGS    ?= -flto=thin
THREADFLAGS ?= -pthread

LDLIBS  ?=
LDFLAGS ?=

SRC  := src
BIN  := bin
DATA := data

SOURCES := \
    $(SRC)/digraph6.cxx \
    $(SRC)/driver.cxx \
    $(SRC)/graph.cxx \
    $(SRC)/spectral_profile.cxx \
    $(SRC)/wl_profile.cxx

HEADERS := \
    $(SRC)/digraph6.hxx \
    $(SRC)/graph.hxx \
    $(SRC)/spectral_profile.hxx \
    $(SRC)/wl_profile.hxx

GAP_SOURCES := \
    $(SRC)/gap_benchmark.cxx \
    $(SRC)/gap_output.cxx \
    $(SRC)/reference_dag.cxx \
    $(SRC)/route_bridge.cxx \
    $(SRC)/route_scaling.cxx

GAP_HEADERS := \
    $(SRC)/gap_benchmark.hxx \
    $(SRC)/gap_output.hxx \
    $(SRC)/reference_dag.hxx \
    $(SRC)/route_bridge.hxx \
    $(SRC)/route_scaling.hxx

FINITE_SOURCES := \
    $(SRC)/gap_finite_closure.cxx \
    $(SRC)/reference_dag.cxx \
    $(SRC)/route_bridge.cxx

FINITE_HEADERS := \
    $(SRC)/reference_dag.hxx \
    $(SRC)/route_bridge.hxx

PROGRAM        := $(BIN)/driver
GAP_PROGRAM    := $(BIN)/gap-benchmark
CLOCK_PROGRAM  := $(BIN)/gap-clock-control
FINITE_PROGRAM := $(BIN)/gap-finite-closure
VERIFY_SCRIPTS := $(sort $(wildcard scripts/verify_*.py))

.PHONY: all clean check-docs verify
.PHONY: findings-2 findings-43 findings-103 findings-103-scaling findings-104
.PHONY: findings-105

all: $(PROGRAM) $(GAP_PROGRAM) $(CLOCK_PROGRAM) $(FINITE_PROGRAM)

check-docs:
	@npm --prefix tools/check-docs ci --ignore-scripts --silent
	@npm --prefix tools/check-docs run check --silent
	@npm --prefix tools/check-docs run validate --silent

verify: $(GAP_PROGRAM) $(CLOCK_PROGRAM) $(FINITE_PROGRAM)
	@set -eu; \
	count=0; \
	for script in $(VERIFY_SCRIPTS); do \
		printf '==> %s\n' "$$script"; \
		$(PYTHON) "$$script"; \
		count=$$((count + 1)); \
	done;

findings-2: $(PROGRAM)
	@scripts/generate_spectral.sh 4 $(DATA)/findings-2/n4
	@scripts/generate_spectral.sh 5 $(DATA)/findings-2/n5
	@scripts/generate_spectral.sh 6 $(DATA)/findings-2/n6

findings-43: $(PROGRAM)
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

$(BIN) $(DATA):
	mkdir -p $@

$(PROGRAM): $(SOURCES) $(HEADERS) | $(BIN)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LTOFLAGS) \
		$(LDFLAGS) -o $@ $(SOURCES) $(LDLIBS)

$(GAP_PROGRAM): $(GAP_SOURCES) $(GAP_HEADERS) | $(BIN)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LTOFLAGS) $(THREADFLAGS) \
		$(LDFLAGS) -o $@ $(GAP_SOURCES) $(LDLIBS)

$(CLOCK_PROGRAM): $(SRC)/gap_clock_control.cxx | $(BIN)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LTOFLAGS) $(THREADFLAGS) \
		$(LDFLAGS) -o $@ $< $(LDLIBS)

$(FINITE_PROGRAM): $(FINITE_SOURCES) $(FINITE_HEADERS) | $(BIN)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LTOFLAGS) $(THREADFLAGS) \
		$(LDFLAGS) -o $@ $(FINITE_SOURCES) $(LDLIBS)

clean:
	rm -rf $(BIN) $(DATA)
