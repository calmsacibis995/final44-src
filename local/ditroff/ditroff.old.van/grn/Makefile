BINDIR	= /usr/local
DESTFILE= grn
GREMLIB = /usr/local/gremlib
DEVDIR	= "/usr/local/lib/font"
CFLAGS	= -O '-DDEVDIR=$(DEVDIR)' '-DGREMLIB="$(GREMLIB)/"'
LDFLAGS	= -lm

OBJS	= hdb.o hpoint.o hgraph.o main.o
SOURCE	= gprint.h hdb.c hpoint.c hgraph.c main.c

grn:  $(OBJS)
	cc -o grn $(OBJS) $(LDFLAGS)

install: $(BINDIR)/$(DESTFILE)

$(BINDIR)/$(DESTFILE): grn
	install -c -s grn $(BINDIR)/$(DESTFILE)

clean:
	/bin/rm -f *.o errs make.out grn

$(OBJS): gprint.h dev.h
