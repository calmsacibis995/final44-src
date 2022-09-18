h31261
s 00002/00002/00047
d D 8.2 93/08/15 13:15:04 mckusick 4 3
c final update from Akito Fujita
e
s 00000/00000/00049
d D 8.1 93/06/10 22:32:22 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00007/00007/00042
d D 7.2 92/12/19 09:57:30 akito 2 1
c use SRCS -> OBJS macro
e
s 00049/00000/00000
d D 7.1 92/12/13 03:50:06 akito 1 0
c date and time created 92/12/13 03:50:06 by akito
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

AS=	as ${DEBUG}
CC=	cc ${DEBUG}
LD=	ld
CPP=	cpp

S= ../..

INCLUDES= -I${.CURDIR} -I${.CURDIR}/$S 
COPTS=	${INCLUDES} ${IDENT} -DKERNEL
D 4
CFLAGS=	-g -O ${COPTS}
E 4
I 4
CFLAGS=	-g -O
E 4

LDFLAGS= -N

NOMAN=

D 4
LIBS=	-lc
E 4
I 4
LIBS=	-L/usr/libexec/gcc2 -lgcc -lc
E 4

D 2
SRC=	trap.c machdep.c romcons.c sio.c bmc.c cons.c subr_prf.c kern_clock.c \
E 2
I 2
SRCS=	trap.c machdep.c romcons.c sio.c bmc.c cons.c subr_prf.c kern_clock.c \
E 2
	boot.c sys.c conf.c ufs_disksubr.c disklabel.c scsi.c sc.c sd.c st.c\
	screen.c bmd.c font.c tape.c fsdump.c kbd.c \
	getline.c parse.c ioconf.c autoconf.c

D 2
OBJ=	trap.o machdep.o romcons.o sio.o bmc.o cons.o subr_prf.o kern_clock.o \
	sys.o conf.o ufs_disksubr.o disklabel.o scsi.o sc.o sd.o st.o\
	screen.o bmd.o font.o ioconf.o autoconf.o tape.o fsdump.o kbd.o \
	boot.o getline.o parse.o
E 2
I 2
#OBJ=	trap.o machdep.o romcons.o sio.o bmc.o cons.o subr_prf.o kern_clock.o \
#	sys.o conf.o ufs_disksubr.o disklabel.o scsi.o sc.o sd.o st.o\
#	screen.o bmd.o font.o ioconf.o autoconf.o tape.o fsdump.o kbd.o \
#	boot.o getline.o parse.o
E 2

.PATH:	${.CURDIR}/../font

PROG=   boot

D 2
boot:	init_main.o locore.o ${OBJ}
	${LD} ${LDFLAGS} -e Reset -T 700000 -o boot locore.o ${OBJ} init_main.o ${LIBS}
E 2
I 2
boot:	init_main.o locore.o ${OBJS}
	${LD} ${LDFLAGS} -e Reset -T 700000 -o boot locore.o ${OBJS} init_main.o ${LIBS}
E 2

locore.o: vectors.h locore.s
	cp ${.CURDIR}/locore.s locore.c
	${CC} -traditional -E -DLOCORE -DFPCOPROC ${COPTS} locore.c > locore.i
	${AS} -o locore.o ${AHEADS} locore.i
	@rm -f locore.c locore.i

install: boot
	cp boot /nn ; sync ; sync ; sync ; sync

clean:
	rm -f boot tags a.out *.o locore.i *~

.include <bsd.prog.mk>
E 1
