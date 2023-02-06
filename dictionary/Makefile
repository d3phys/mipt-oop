# Make shure to define rule for each target
SHELL := bash

CXX := g++
CXXFLAGS := -Wall
include txx.mk

# Determine the object files
OBJ := main.o dict.o word_types.o

# Target specific object files
#
cdict: $(OBJ)
	$(CXX) -o $@ $(OBJ) $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o
	rm -rf *.d

.PHONY: clean

# Dependencies
include $(OBJ:.o=.d)

%.d: %.cc
	./depend.sh `dirname $*` $(CXXFLAGS) $< > $@

