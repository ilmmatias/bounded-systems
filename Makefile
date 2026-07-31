# Build the main driver and reproduce the finite-DAG data products.
#
#   make
#   make findings-2
#   THREADS=32 SORT_MEM=2G make findings-43
#   make verify
#   make clean

CXX      ?= clang++
CPPFLAGS ?=
CXXFLAGS ?= -O3 -march=native -std=c++23 -Wall -Wextra
LTOFLAGS ?= -flto=thin
LDFLAGS  ?=
LDLIBS   ?=
PYTHON   ?= python3

SRC   := src
BIN   := bin
DATA  := data

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

PROGRAM        := $(BIN)/driver
VERIFY_SCRIPTS := $(sort $(wildcard scripts/verify_*.py))

.PHONY: all clean check-docs verify
.PHONY: findings-2 findings-43

all: $(PROGRAM)

check-docs:
	@npm --prefix tools/check-docs ci --ignore-scripts --silent
	@npm --prefix tools/check-docs run check --silent
	@npm --prefix tools/check-docs run validate --silent

verify:
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

$(BIN) $(DATA):
	mkdir -p $@

$(PROGRAM): $(SOURCES) $(HEADERS) | $(BIN)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LTOFLAGS) $(LDFLAGS) -o $@ $(SOURCES) $(LDLIBS)

clean:
	rm -rf $(BIN) $(DATA)
