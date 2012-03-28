IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

CFILES=$(shell ls *.c)
OFILES=$(CFILES:.c=.o)

LIBS=-lm


default : beagle.a

debug :
	@echo "OFILES='$(OFILES)'"

%.o: %.c 
	$(CC) -c -o  $@ $< $(CFLAGS) 

beagle.a : $(OFILES)
	ar cr $@ $^

.PHONY: default clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
