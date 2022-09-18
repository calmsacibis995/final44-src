DEVDIR	= "/usr/local/lib/font"

ditfilt	:ditfilt.c idfilt.h dev.h
	cc '-DDEVDIR=$(DEVDIR)' -o ../filter ditfilt.c

idfilt.o	:idfilt.c idfilt.h

4014.o	:4014.c idfilt.h

4filt	:idfilt.o 4014.o
	cc -o ../filter 4014.o idfilt.o -l4014 -lm

pout.o	:pout.c

pfilt	:idfilt.o pout.o
	cc -o ../filter pout.o idfilt.o -lplot -lm

202.o	:202.c idfilt.h

tfilt	:idfilt.o 202.o
	cc -o ../filter 202.o idfilt.o

aps.o	:aps.c

apsfilt	:aps.o idfilt.o
	cc -o ../filter aps.o idfilt.o

idsort	:idsort.c
	cc -o idsort idsort.c

clean	:
	/bin/rm -f *.o make.out *filtn idsort
