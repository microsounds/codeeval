## generic makefile
# source file should be named '<pname>.c'
# directory should be named '000_<pname>'

LANG=c
CC=gcc
CFLAGS=-O2 -ansi
LDFLAGS=
PNAME:=$(shell basename $(shell pwd) | sed 's/[0-9]*_//g')
OUTPUT:=$(PNAME)
INPUT:=$(PNAME).$(LANG)

all: $(INPUT)
ifdef LDFLAGS
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(OUTPUT) $(INPUT)
else
	$(CC) $(CFLAGS) -o $(OUTPUT) $(INPUT)
endif

clean:
	rm -rf $(OUTPUT)
        
