CFLAGS=cflags()
I=includedir()
# Valid are: -DADOBE_DSC2_CONFORMANT
SIMPLEFLAGS=simpleflags()
LWSRVOBJS=fontlist.o lwsrv.o papstream.o procset.o simple.o spmisc.o

# for other libraries (like BSD on hpux)
SLIB=libspecial()
LIBCAP=libcap()

# make sure that you define point getopt to att_getopt.o if your system
# doesn't have it builtin
ATT_GETOPT=ifdef([needgetopt],[needgetopt])

DESTDIR=capdestdir()

lwsrv:	${LWSRVOBJS} ${ATT_GETOPT}
	${CC} -o lwsrv ${LFLAGS} ${LWSRVOBJS} ${ATT_GETOPT} ${LIBCAP} ${SLIB}

clean:
	-rm *.o lwsrv att_getopt.c

install: lwsrv
	ifdef([sysvinstall],[install -f $(DESTDIR)],[install]) lwsrv ${DESTDIR}

dist:
	@cat todist

att_getopt.c:
	ln -s ../../extras/att_getopt.c

simple.o:       simple.c
	${CC} ${CFLAGS} ${SIMPLEFLAGS} -c simple.c

# Dependencies
lwsrv.o:        lwsrv.c		$I/netat/appletalk.h $I/netat/aberrors.h \
				$I/netat/abqueue.h $I/netat/sysvcompat.h \
				$I/netat/compat.h papstream.h 
simple.o:       simple.c        $I/netat/appletalk.h $I/netat/aberrors.h \
				$I/netat/abqueue.h $I/netat/sysvcompat.h \
				$I/netat/sysvcompat.h $I/netat/compat.h \
				spmisc.h \
				procset.h fontlist.h papstream.h 
fontlist.o:     fontlist.c      $I/netat/appletalk.h \
				$I/netat/aberrors.h $I/netat/abqueue.h \
				$I/netat/sysvcompat.h fontlist.h \
				spmisc.h papstream.h 
papstream.o:    papstream.c     $I/netat/appletalk.h \
				$I/netat/aberrors.h $I/netat/abqueue.h \
				$I/netat/sysvcompat.h papstream.h 
procset.o:      procset.c       $I/netat/appletalk.h $I/netat/aberrors.h \
				$I/netat/abqueue.h $I/netat/sysvcompat.h \
				$I/netat/sysvcompat.h $I/netat/compat.h \
				procset.h \
				spmisc.h 
spmisc.o:       spmisc.c        $I/netat/appletalk.h $I/netat/aberrors.h \
				$I/netat/abqueue.h $I/netat/sysvcompat.h \
				$I/netat/sysvcompat.h $I/netat/compat.h \
				spmisc.h 
