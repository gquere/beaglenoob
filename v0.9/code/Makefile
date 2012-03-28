IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = gpio.h lcd.h useful.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

CFILES = $(shell ls *.c)
OFILES = $(CFILES:.c=.o)
BINFILES = $(CFILES:.c=)


default : $(BINFILES)

debug :
	@echo "OFILES='$(OFILES)'"
	@echo "BINFILES='$(BINFILES)'"
	@echo "DEPS='$(DEPS)'"

%.o: %.c $(DEPS)
	$(CC) -c -o  $@ $< $(CFLAGS) 

lib : 
	$(MAKE) -C ../lib

$(BINFILES) : % : %.o lib 
	gcc -o $@ $< ../lib/beagle.a $(LIBS) $(CFLAGS) 

.PHONY: lib default clean

clean:
	rm -f *.o *~ core $(INCDIR)/*~ 
