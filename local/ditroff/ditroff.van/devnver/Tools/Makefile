#
#  make the tools for generating the bitmaps for ndver80
#
PROGS = bitmaps cdata checkdisk fntinfo prects 
CFLAGS=-O

prects: prects.o error.o
	$(CC) $(CFLAGS) -o prects prects.o error.o

cdata:  error.o cdata.o subr.o
	$(CC) $(CFLAGS) -o cdata cdata.o error.o subr.o

fntinfo: error.o fntinfo.o subr.o
	$(CC) $(CFLAGS) -o fntinfo fntinfo.o error.o subr.o

checkdisk:	error.o checkdisk.o subr.o
	$(CC) $(CFLAGS) -o checkdisk checkdisk.o error.o subr.o

bitmaps: bitmaps.o downscale.o error.o
	$(CC) $(CFLAGS) -o bitmaps bitmaps.o downscale.o error.o -lm

cdata.o:	../defs.h
checkdisk.o:	../defs.h
subr.o:		../defs.h
fntinfo.o:	../defs.h
bitmaps.o:	../defs.h chardata.h
downscale.o:	../defs.h chardata.h flip.h
prects.o:	../defs.h huff14.h huff7.h Ptable.h


all:	$(PROGS)

clean:
	rm -f *.o make.out

# don't do anything.
install:;
