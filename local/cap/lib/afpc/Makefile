# Makefile autoconfigured for a: \
	SunOS system on Wed Sep 14 03:40:04 PDT 1988



MFLAGS=
LFLAGS=
CC=cc
LD=ld
CFLAGS=-O -DSYSLOG -I/usr/include/4.3syslog 
I=/usr/include
LIBAFPCSRCS=afpc.c afpcc.c
LIBAFPCOBJS=afpc.o afpcc.o
LIBAFPC=libafpc.a
DESTDIR=/usr/local/lib

$(LIBAFPC):	$(LIBAFPCOBJS)
	ar rv  $(LIBAFPC) $(LIBAFPCOBJS)

clean:
	-rm ${LIBAFPCOBJS} ${LIBAFPC}.a core *~

install:	$(LIBAFPC)
	install $(LIBAFPC) $(DESTDIR)
	ranlib $(DESTDIR)/$(LIBAFPC)

dist:
	@cat todist

lint:	$(LIBAFPCSRCS)
	lint $(LIBAFPCSRCS)

afpc.o:         afpc.c		$I/netat/appletalk.h $I/netat/aberrors.h \
				$I/netat/abqueue.h $I/netat/afpc.h 
afpcc.o:        afpcc.c		$I/netat/appletalk.h $I/netat/aberrors.h \
				$I/netat/abqueue.h $I/netat/afpc.h 
