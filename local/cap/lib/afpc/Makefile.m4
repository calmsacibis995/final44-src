CFLAGS=cflags() bigcflags()
I=includedir()
LIBAFPCSRCS=afpc.c afpcc.c
LIBAFPCOBJS=afpc.o afpcc.o
LIBAFPC=afpclib()
DESTDIR=libdestdir()

$(LIBAFPC):	$(LIBAFPCOBJS)
	ifdef([uselordertsort],[ar cr $(LIBAFPC) `lorder $(LIBAFPCOBJS)|tsort`],
	[ar rv  $(LIBAFPC) $(LIBAFPCOBJS)])

clean:
	-rm ${LIBAFPCOBJS} ${LIBAFPC}.a core *~

install:	$(LIBAFPC)
	ifdef([sysvinstall],[install -f $(DESTDIR)],[install]) $(LIBAFPC) $(DESTDIR)
ifdef([uselordertsort],[],[	ranlib $(DESTDIR)/$(LIBAFPC)])

dist:
	@cat todist

lint:	$(LIBAFPCSRCS)
	lint $(LIBAFPCSRCS)

afpc.o:         afpc.c		$I/netat/appletalk.h $I/netat/aberrors.h \
				$I/netat/abqueue.h $I/netat/afpc.h 
afpcc.o:        afpcc.c		$I/netat/appletalk.h $I/netat/aberrors.h \
				$I/netat/abqueue.h $I/netat/afpc.h 
