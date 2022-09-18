h47558
s 00001/00001/00017
d D 1.3 87/07/16 14:07:13 jaap 3 2
c nvsort should be installed as nvsort80
e
s 00004/00002/00014
d D 1.2 87/04/01 16:48:37 jaap 2 1
c minor corrections
e
s 00016/00000/00000
d D 1.1 87/04/01 16:45:39 jaap 1 0
c date and time created 87/04/01 16:45:39 by jaap
e
u
U
t
T
I 1
#
I 2
#  %I%	(CWI)	%E%
E 2
#
# nvsort
#
D 2
DESTFILE=/usr/lib/nvsort80
E 2
I 2
DESTDIR =
LIBDIR=/usr/lib
E 2

all:	nvsort

install: nvsort
D 2
	 install -c nvsort $(DESTFILE)
E 2
I 2
D 3
	 install -c nvsort $(DESTDIR)${LIBDIR}/nvsort
E 3
I 3
	 install -c nvsort $(DESTDIR)${LIBDIR}/nvsort80
E 3
E 2

clean:
	rm -f make.out nvsort

nvsort:	nvsort.c
	cc $(CFLAGS) -DVER80 -o nvsort nvsort.c -lm
E 1
