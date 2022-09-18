CFLAGS=cflags() bigcflags()
I=includedir()
OSDEFS=afposdefs()
LIBAFPSRCS=afperr.c afpcmd.c afppacks.c afposlock.c
LIBAFPOBJS=afperr.o afpcmd.o afppacks.o afposlock.o des.o
LIBAFP=afplib()
DESTDIR=libdestdir()
DES=desloc()

$(LIBAFP):	$(LIBAFPOBJS)
	ifdef([uselordertsort],[ar cr $(LIBAFP) `lorder $(LIBAFPOBJS)| tsort`],
	[ar rv  $(LIBAFP) $(LIBAFPOBJS)])

des.o: ${DES}/des.c
	(cd ${DES}; make des.o)
	cp ${DES}/des.o .

clean:
	-rm ${LIBAFPOBJS} ${LIBAFP} core *~

install:	$(LIBAFP)
	ifdef([sysvinstall],[install -f $(DESTDIR)],[install]) $(LIBAFP) $(DESTDIR)
ifdef([uselordertsort],[],[	ranlib $(DESTDIR)/$(LIBAFP)])

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
