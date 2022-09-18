# Makefile autoconfigured for a: \
	SunOS system on Wed Sep 14 03:40:02 PDT 1988



MFLAGS=
LFLAGS=
CC=cc
LD=ld
CFLAGS=-O -DSYSLOG -I/usr/include/4.3syslog 
I=/usr/include
OSDEFS=
LIBAFPSRCS=afperr.c afpcmd.c afppacks.c afposlock.c
LIBAFPOBJS=afperr.o afpcmd.o afppacks.o afposlock.o des.o
LIBAFP=libafp.a
DESTDIR=/usr/local/lib
DES=../../extras

$(LIBAFP):	$(LIBAFPOBJS)
	ar rv  $(LIBAFP) $(LIBAFPOBJS)

des.o: ${DES}/des.c
	(cd ${DES}; make des.o)
	cp ${DES}/des.o .

clean:
	-rm ${LIBAFPOBJS} ${LIBAFP} core *~

install:	$(LIBAFP)
	install $(LIBAFP) $(DESTDIR)
	ranlib $(DESTDIR)/$(LIBAFP)

dist:
	@cat todist

lint:	$(LIBAFPSRCS)
	lint $(LIBAFPSRCS)

afposlock.o:	afposlock.c
	${CC} ${OSDEFS} ${CFLAGS} -c afposlock.c

# Dependencies
afpcmd.o:       afpcmd.c	$I/netat/appletalk.h $I/netat/aberrors.h \
				$I/netat/abqueue.h $I/netat/sysvcompat.h \
				$I/netat/afp.h $I/netat/afpcmd.h 
afperr.o:       afperr.c        $I/netat/appletalk.h \
				$I/netat/aberrors.h $I/netat/abqueue.h \
				$I/netat/sysvcompat.h $I/netat/afp.h 
afppacks.o:     afppacks.c      $I/netat/appletalk.h \
				$I/netat/aberrors.h $I/netat/abqueue.h \
				$I/netat/sysvcompat.h $I/netat/afp.h \
				$I/netat/afpcmd.h 
afposlock.o:    afposlock.c	$I/netat/appletalk.h $I/netat/aberrors.h \
				$I/netat/abqueue.h $I/netat/sysvcompat.h \
				$I/netat/afp.h $I/netat/afpcmd.h
