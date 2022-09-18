#	%W%	%I%	%G%
CFLAGS=-O
SRCS=people.c dbase.c peoplesort.c peopledbm.c
OBJS=people.o dbase.o peoplesort.o peopledbm.o
HDRS=
TARGET=people peoplesort peopledbm
DESTDIR=/usr/cur/pc/bin

all:	people peoplesort peopledbm

people:	people.o dbase.o
	cc -o people $(CFLAGS) people.o dbase.o -ldbm

peoplesort:	peoplesort.o dbase.o
	cc -o peoplesort $(CFLAGS) peoplesort.o dbase.o -ldbm

peopledbm:	peopledbm.o dbase.o
	cc -o peopledbm $(CFLAGS) peopledbm.o dbase.o -ldbm

sources:	$(SRCS) $(HDRS)

$(SRCS) $(HDRS):
	sccs get $@

tags:	$(SRCS) $(HDRS)
	ctags $(HDRS) $(SRCS)

clean:
	-rm -f $(TARGET) ph work email home *.o errs comment tags

install:
	install -s people $(DESTDIR)
	chmod 750 $(DESTDIR)/people
	install -s peoplesort $(DESTDIR)
	install -s peopledbm $(DESTDIR)
	rm -f $(DESTDIR)/ph; ln $(DESTDIR)/people $(DESTDIR)/ph
	rm -f $(DESTDIR)/work; ln $(DESTDIR)/people $(DESTDIR)/work
	rm -f $(DESTDIR)/email; ln $(DESTDIR)/people $(DESTDIR)/email
	rm -f $(DESTDIR)/home; ln $(DESTDIR)/people $(DESTDIR)/home

