h35405
s 00005/00001/00013
d D 1.2 88/03/04 17:05:49 jaap 2 1
c cleaning up
e
s 00014/00000/00000
d D 1.1 87/04/27 15:17:35 jaap 1 0
c date and time created 87/04/27 15:17:35 by jaap
e
u
U
t
T
I 1
#
# terminal Makefile %W% (CWI) %E%
#
DESTDIR =
BIN = /usr/local
LIBDIR = /usr/local/lib/ditroff/term
TABS = tab.1650.10 tab.1650.12 tab.37 tab.450 tab.lp

all:	${TABS}


D 2
install: ${TABS}
E 2
I 2
install: ${TABS} $(LIBDIR)
E 2
	for i in ${TABS}; do install -m 644 -c $$i ${LIBDIR}/$$i; done
I 2

$(LIBDIR):
	mkdir $(LIBDIR)

E 2
clean:
E 1
