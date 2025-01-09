# Makefile for the mkramp program.
#



.DEFAULT: all

all: mkramp

.PHONY: clean

mkramp: mkramp.c makefile
	@echo "Compiling mkramp.c"
	gcc -Wall --pedantic -O2 -o mkramp mkramp.c

clean:
	rm -rf *.o mkramp


