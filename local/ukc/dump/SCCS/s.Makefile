h27897
s 00001/00001/00078
d D 1.3 87/08/11 22:36:11 pc 3 2
c Add dumplabel to Makefile
e
s 00016/00007/00063
d D 1.2 87/08/08 16:50:10 pc 2 1
c Add label handling and rewind off line
e
s 00070/00000/00000
d D 1.1 87/08/07 18:33:24 pc 1 0
c date and time created 87/08/07 18:33:24 by pc
e
u
U
t
T
I 1
#
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	@(#)Makefile	5.4 (Berkeley) 5/28/86
I 2
#	%Z%%M%	%I% (UKC) %G%
E 2
#
#	dump.h			header file
#	dumpitime.c		reads /etc/dumpdates
#	dumpmain.c		driver
#	dumpoptr.c		operator interface
#	dumptape.c		handles the mag tape and opening/closing
I 2
#	dumplab.c		deal with tape labels
E 2
#	dumptraverse.c		traverses the file system
#	unctime.c		undo ctime
#
I 2
#	dumplabel.c		General tape label management program
#
E 2
#	DEBUG			use local directory to find ddate and dumpdates
#	TDEBUG			trace out the process forking
#
PSRCS = \
	/usr/include/protocols/dumprestore.h dump.h \
D 2
	dumpmain.c dumptraverse.c dumptape.c dumpoptr.c dumpitime.c unctime.c
E 2
I 2
	dumpmain.c dumptraverse.c dumptape.c dumplab.c \
	dumpoptr.c dumpitime.c unctime.c dumplabel.c
E 2

SRCS =  \
	dump.h dumpitime.c \
D 2
	dumpmain.c dumpoptr.c dumprmt.c dumprtape.c \
E 2
I 2
	dumpmain.c dumpoptr.c dumprmt.c dumprtape.c dumplab.c \
E 2
	dumptraverse.c unctime.c

D 2
OBJS = dumpitime.o dumpmain.o dumpoptr.o \
E 2
I 2
OBJS = dumpitime.o dumpmain.o dumpoptr.o dumplab.o \
E 2
	dumptape.o dumptraverse.o unctime.o

D 2
ROBJS = dumpitime.o dumprmain.o dumpoptr.o \
E 2
I 2
ROBJS = dumpitime.o dumprmain.o dumpoptr.o dumplab.o \
E 2
	dumprmt.o dumprtape.o dumptraverse.o unctime.o

DFLAGS =
CFLAGS = -O $(DFLAGS)

D 2
all: dump rdump
E 2
I 2
all: dump rdump dumplabel
E 2

rdump:	$(ROBJS)
D 2
	$(CC) $(CFLAGS) $(ROBJS) -o rdump
E 2
I 2
	$(CC) $(CFLAGS) $(ROBJS) -o rdump -lm
E 2

dump:	$(OBJS)
D 2
	$(CC) $(CFLAGS) $(OBJS) -o dump
E 2
I 2
	$(CC) $(CFLAGS) $(OBJS) -o dump -lm
E 2

I 2
dumplabel: dumplabel.o
	$(CC) $(CFLAGS) dumplabel.o -o dumplabel

E 2
install: rdump dump
	install -s -m 6755 -g tty rdump $(DESTDIR)/etc
	install -s -m 2755 -g tty dump $(DESTDIR)/etc
I 2
	install -s -m 755 -g tty $(DESTDIR)/etc
E 2

dumprmain.c:
	ln -s dumpmain.c dumprmain.c
dumprmain.o: dumprmain.c
	${CC} -c -DRDUMP ${CFLAGS} dumprmain.c

dumprtape.c:
	ln -s dumptape.c dumprtape.c
dumprtape.o: dumprtape.c
	${CC} -c -DRDUMP ${CFLAGS} dumprtape.c

clean:
D 3
	rm -f *.o rdump dump errs dumprmain.c dumprtape.c
E 3
I 3
	rm -f *.o rdump dump errs dumprmain.c dumprtape.c dumplabel
E 3

lint:
	lint $(DFLAGS) $(SRCS)

print:
	pr $(PSRCS) | lpr

$(OBJS): dump.h /usr/include/sys/param.h
$(OBJS): /usr/include/sys/fs.h /usr/include/sys/inode.h
$(OBJS): /usr/include/protocols/dumprestore.h /usr/include/sys/stat.h
E 1
