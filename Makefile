# Build the C++ passes and regenerate all artifacts
#
#   make              build both binaries
#   make gen          regenerate data for N=1..7
#   make gen-<n>      regenerate data only for a specific N
#   make -j7 gen      regenerate multiple N values in parallel
#   make clean        remove binaries and artifacts

CXX      ?= g++
CXXFLAGS ?= -O3 -march=native -std=c++23 -Wall -Wextra
OMPFLAGS ?= -fopenmp

SRC  := src
BIN  := bin
DATA := data

NODES := 1 2 3 4 5 6 7

PROGRAMS     := $(BIN)/enumerate $(BIN)/profile
GEN_TARGETS := $(NODES:%=gen-%)

.PHONY: all gen clean $(GEN_TARGETS)

all: $(PROGRAMS)

gen: $(GEN_TARGETS)

$(BIN) $(DATA):
	mkdir -p $@

$(BIN)/%: $(SRC)/%.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) $(OMPFLAGS) -o $@ $<

# "gen-N" is expanded into gen-1, gen-2, ..., gen-7.
# In this rule, $* is the corresponding N value.
$(GEN_TARGETS): gen-%: $(PROGRAMS) | $(DATA)
	@echo "  enumerate n=$*"
	@$(BIN)/enumerate $* > $(DATA)/catalog-$*.txt.tmp
	@mv $(DATA)/catalog-$*.txt.tmp $(DATA)/catalog-$*.txt

	@echo "  profile n=$* level=4"
	@EMIT_JSON=$(DATA)/table-$*.json \
	 DUMP_COLLISIONS=$(DATA)/collisions-$*-node.txt \
	 DUMP_LEVEL=4 \
	   $(BIN)/profile $* $(DATA)/catalog-$*.txt \
	   > $(DATA)/separation-$*.txt 2>/dev/null

	@echo "  profile n=$* level=5"
	@DUMP_COLLISIONS=$(DATA)/collisions-$*-full.txt \
	 DUMP_LEVEL=5 \
	   $(BIN)/profile $* $(DATA)/catalog-$*.txt \
	   >/dev/null 2>/dev/null

clean:
	rm -rf $(BIN) $(DATA)
