CFLAGS=cflags() caposdefs()
I=includedir()
NBPFLAGS=nbpflags()
LIBABSRCS=abatp.c abddp.c abmisc.c abnbp.c \
	abpap.c abpapc.c abpaps.c abpp.c abqueue.c abasp.c \
	abzip.c abversion.c atalkdbm.c absched.c abkip.c
LIBABOBJS=abatp.o abddp.o abmisc.o abnbp.o \
	abpap.o abpapc.o abpaps.o abpp.o abqueue.o abasp.o \
	abzip.o abversion.o atalkdbm.o absched.o abkip.o
LIBCAP=caplib()
DESTDIR=libdestdir()

$(LIBCAP):	$(LIBABOBJS)
	ifdef([uselordertsort],[ar cr $(LIBCAP) `lorder $(LIBABOBJS) | tsort`],
	[ar rv  $(LIBCAP) $(LIBABOBJS)])

clean:
	-rm ${LIBABOBJS} ${LIBCAP} core *~

install:	$(LIBCAP)
	ifdef([sysvinstall],[install -f $(DESTDIR)],[install]) $(LIBCAP) $(DESTDIR)
ifdef([uselordertsort],[],[	ranlib $(DESTDIR)/$(LIBCAP)])

dist:
	@cat todist

lint:	$(LIBABSRCS)
	lint $(LIBABSRCS)

atalkdbm.o:     atalkdbm.c
	${CC} ${CFLAGS} -c -DTAB=atalklocal() -DCONFIGDIR=configdir() atalkdbm.c

abnbp.o:        abnbp.c		$I/netat/appletalk.h $I/netat/aberrors.h \
				$I/netat/abqueue.h  $I/netat/abnbp.h
	${CC} ${CFLAGS} ${NBPFLAGS} -c abnbp.c

abatp.o:        abatp.c		$I/netat/appletalk.h $I/netat/aberrors.h \
				$I/netat/abqueue.h abatp.h 
abatpaux.o:     abatpaux.c	$I/netat/appletalk.h \
				$I/netat/aberrors.h $I/netat/abqueue.h \
				abatp.h 
abddp.o:        abddp.c		$I/netat/appletalk.h $I/netat/aberrors.h \
				$I/netat/abqueue.h cap_conf.h 
abmisc.o:       abmisc.c	$I/netat/appletalk.h $I/netat/aberrors.h \
				$I/netat/abqueue.h 
abkip.o:        abkip.c		$I/netat/appletalk.h $I/netat/aberrors.h \
				$I/netat/abqueue.h
abpap.o:        abpap.c		$I/netat/appletalk.h $I/netat/aberrors.h \
				$I/netat/abqueue.h abpap.h cap_conf.h
abpapc.o:       abpapc.c	$I/netat/appletalk.h $I/netat/aberrors.h \
				$I/netat/abqueue.h abpap.h cap_conf.h 
abpaps.o:       abpaps.c	$I/netat/appletalk.h $I/netat/aberrors.h \
				$I/netat/abqueue.h abpap.h cap_conf.h 
abpp.o:         abpp.c		$I/netat/appletalk.h $I/netat/aberrors.h \
				$I/netat/abqueue.h 
abqueue.o:      abqueue.c       $I/netat/abqueue.h 
abasp.o:        abasp.c		$I/netat/appletalk.h $I/netat/aberrors.h \
				$I/netat/abqueue.h abasp.h 
abzip.o:	abzip.c		$I/netat/appletalk.h
abversion.o:	abversion.c	$I/netat/appletalk.h
absched.o:	absched.c	$I/netat/appletalk.h $I/netat/compat.h
atalkdbm.o:     atalkdbm.c
