# Makefile autoconfigured for a: \
	SunOS system on Wed Sep 14 03:40:13 PDT 1988



MFLAGS=
LFLAGS=
CC=cc
LD=ld
CFLAGS=-O -DSYSLOG
I=/usr/include

# See README file for notes about defines
# Valid: SFLOWQ=[1,2,3,4,5,6,7,8]
LWFLAGS=
# Valid: IDLESTUFF, NO_STRUCT, NOACCT, CAPPRINTERS=location
PAPFLAGS=-DIDLESTUFF 
PAPBANNER=-DCHARGEBANNER
# USEVPRINTF - use vprintf in logging
VPRINTF=-DUSEVPRINTF
# If you have Transcript from Adobe for your laserWriter and want to
#  print text files, uncomment the next line and set the location properly
# WPSTEXT="-DPSTEXT=\"/usr/local/lib/ps/pstext\"

# This is if you have transcript and and want page reversal if possible
# WPSREVERSE=-DPSREVERSE=\"/usr/local/lib/ps/psrev\"

CAPLIB=-lcap
# for other libraries (like BSD on hpux)
SLIB=
DESTDIR=/usr/local/cap

all:	papif papof

papif:	papif.o $(O)
	${CC} ${LFLAGS} -o papif papif.o $(O) $(CAPLIB) ${SLIB}

papif.o: papif.c
	${CC} ${CFLAGS} ${VPRINTF} ${PAPBANNER} ${PAPFLAGS} ${LWFLAGS} \
		${WPSTEXT} ${WPSREVERSE} -c papif.c




papof.o: papof.c
	${CC} -c ${CFLAGS} ${PAPBANNER} papof.c

papof:	papof.o
	${CC} ${LFLAGS} -o papof papof.o ${SLIB}


clean:
	-rm papif papof *.o


install: papif papof
	install papif $(DESTDIR)
	install papof $(DESTDIR)


dist:
	@cat todist
