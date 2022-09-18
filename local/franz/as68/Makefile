FILES = mical.h inst.h scan.h MegaStab.h scan.c error.c init.c \
        ins.c ps.c rel.c sdi.c sym.c \
        MegaStab.c Makefile a.out.h b.out.h stab.h

OBJECTS = MegaStab.o error.o init.o ins.o ps.o rel.o sdi.o sym.o scan.o
XOBJECTS= MegaStab.o error.o init.o ins.o xps.o xrel.o sdi.o xsym.o scan.o
DESTDIR = /usr/lib/lisp

# CFLAGS = -g
# CC= /bin/cc
CFLAGS= -Dmc68000 -I.
XFLAGS= $(CFLAGS) -DLOCAL_AOUTH

as: $(OBJECTS)
	$(CC) $(OBJECTS)
	mv a.out as

xas: $(XOBJECTS)
	$(CC) $(XOBJECTS)
	mv a.out xas

install: as
	rm -f ${DESTDIR}/as
	cp as ${DESTDIR}/as

print:
	pr ${FILES} | lpr

scriptcat: ${FILES}
	@../scriptcat . as68 ${FILES}

MegaStab.o:	scan.h mical.h inst.h
error.o:	mical.h
init.o:		mical.h inst.h
ins.o:		mical.h inst.h
ps.o:		mical.h
rel.o:		mical.h a.out.h b.out.h
scan.o:		inst.h scan.h mical.h
sdi.o:		mical.h
sym.o:		mical.h scan.h

xps.o:		ps.c mical.h
	-ln ps.c xps.c
	$(CC) $(XFLAGS) -c xps.c
	rm xps.c

xrel.o:		rel.c mical.h a.out.h b.out.h
	-ln rel.c xrel.c
	$(CC) $(XFLAGS) -c xrel.c
	rm xrel.c

xsym.o:		sym.c mical.h scan.h
	-ln sym.c xsym.c
	$(CC) $(XFLAGS) -c xsym.c
	rm xsym.c

