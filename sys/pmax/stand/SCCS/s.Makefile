h41232
s 00002/00004/00075
d D 8.4 94/07/03 15:02:28 mckusick 12 11
c move address of boot program. Kernels were getting too large. (from ralph)
e
s 00003/00003/00076
d D 8.3 94/02/16 12:18:30 bostic 11 10
c fix "make clean"
c From: ralphc@pyramid.com (Ralph Campbell)
e
s 00002/00002/00077
d D 8.2 93/11/30 16:20:51 mckusick 10 9
c move rather than copy boot binaries
e
s 00000/00000/00079
d D 8.1 93/06/29 15:14:51 mckusick 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00077
d D 5.7 93/06/29 15:14:39 mckusick 8 6
c optimize boot program
e
s 00000/00000/00079
d R 8.1 93/06/10 23:31:38 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00004/00002/00075
d D 5.6 93/05/09 18:11:01 ralph 6 5
c added dec_label program
e
s 00001/00001/00076
d D 5.5 93/04/05 21:45:15 ralph 5 4
c make boot work for either 3100 or 5000 and still fit in 15 sectors.
e
s 00013/00011/00064
d D 5.4 93/02/15 11:22:41 ralph 4 3
c use old DS3100 style entry point for SCSI disk I/O
e
s 00055/00031/00020
d D 5.3 92/10/24 14:24:17 ralph 3 2
c new version with libsa
e
s 00002/00001/00049
d D 5.2 92/09/13 11:50:49 ralph 2 1
c use libkern.a for long long support
e
s 00050/00000/00000
d D 5.1 92/05/04 17:19:50 bostic 1 0
c date and time created 92/05/04 17:19:50 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

DESTDIR=
D 3
STAND=	/stand
INCPATH= -I../.. -I../../sys
DEFS=	${INCPATH} -DSTANDALONE -D_MONFUNCS -DSMALL
E 3
I 3
STAND=	../../stand
D 11
INCPATH=-I. -I../..
E 11
I 11
INCPATH=-I. -I/sys
E 11
VPATH=	${STAND}
E 3

D 3
# Collections of C options:
#	COPTS	device drivers/assembler, not optimized
#	CFLAGS	everything else
E 3
I 3
D 12
# RELOC=80200000 allows for boot prog up to 1D0000 (1900544) bytes long
RELOC=	80200000
E 12
I 12
# RELOC=80300000 allows for boot prog up to 2D0000 (2949120) bytes long
RELOC=	80300000
E 12
E 3

D 3
COPTS=	${DEFS}
CFLAGS=	-O ${DEFS}
E 3
I 3
D 5
DEFS= -DSTANDALONE -DDS5000 -DSMALL
E 5
I 5
DEFS= -DSTANDALONE -DSMALL
E 5
D 8
CFLAGS=	-O ${INCPATH} ${DEFS}
AFLAGS=	-O ${INCPATH} ${DEFS} -DLOCORE
E 8
I 8
CFLAGS=	-O2 ${INCPATH} ${DEFS}
AFLAGS=	-O2 ${INCPATH} ${DEFS} -DLOCORE
E 8
E 3

D 3
SRCS=	mkboot.c
E 3
I 3
D 4
DRIVERS=asc.c rz.c sii.c scsi.c
SRCS=	conf.c machdep.c trap.c ${DRIVERS}
E 4
I 4
DRIVERS= rz.c
SRCS=	${DRIVERS}
E 4
LIBS=	libdrive.a libsa/libsa.a ../../libkern/obj/libkern.a
E 3

D 3
ALL=	mkboot boot mkboottape
E 3
I 3
D 6
#ALL=	boot mkboot mkboottape
ALL=	boot
E 6
I 6
ALL=	boot mkboot mkboottape dec_label
E 6
E 3

I 4
.s.o:
	${CPP} -E ${CFLAGS:M-[ID]*} ${AINC} ${.IMPSRC} | \
	    ${AS} -o ${.TARGET}

E 4
all: ${ALL}
D 12

D 3
mkboot: mkboot.c
	${CC} ${CFLAGS} -o $@ mkboot.c
E 3
I 3
boot: ${LIBS}
E 12
E 3

D 3
boot: start.o boot.o conf.o sys.o
D 2
	ld -N -T 80100000 -o $@ start.o boot.o conf.o sys.o
E 2
I 2
	ld -N -T 80100000 -o $@ start.o boot.o conf.o sys.o \
		../../libkern/obj/libkern.a
E 3
I 3
libsa/libsa.a::
	cd libsa; make
E 3
E 2

D 3
mkboottape: mkboottape.c
	${CC} ${CFLAGS} -o $@ mkboottape.c
E 3
I 3
D 4
libdrive.a: conf.o machdep.o trap.o ${DRIVERS:.c=.o}
E 4
I 4
libdrive.a: conf.o ${DRIVERS:.c=.o}
E 4
	ar crv $@ $?
	ranlib $@
E 3

D 3
# for testing
tboot: boot.c
	cc -o $@ ${CFLAGS} -DTEST boot.c
E 3
I 3
D 4
${DRIVERS}: samachdep.h
E 3

E 4
D 3
clean:
	rm -f *.o ${ALL} a.out core errs
E 3
I 3
# depend on DEFS
E 3

D 3
depend: ${SRCS}
	mkdep ${INCPATH} -DSTANDALONE ${SRCS}
E 3
I 3
D 4
machdep.o rz.o trap.o: Makefile
cons.o dca.o hil.o: Makefile
ite.o ite_subr.o ite_dv.o ite_gb.o ite_hy.o ite_rb.o ite_tc.o: Makefile
E 3

E 4
D 3
install: FRC
	mkboot boot ${DESTDIR}/usr/mdec/rzboot ${DESTDIR}/usr/mdec/bootrz
E 3
I 3
# bootable from real disks
E 3

D 3
lint: ${SRCS}
	lint ${COPTS} -hxbn boot.c ${SRCS}
E 3
I 3
D 4
boot:	locore.o boot.o bootconf.o ${LIBS}
	ld -N -T ${RELOC} -e start locore.o boot.o bootconf.o ${LIBS} -o $@ 
E 4
I 4
boot:	start.o boot.o bootconf.o ${LIBS}
	ld -N -Ttext ${RELOC} -e start start.o boot.o bootconf.o ${LIBS} -o $@ 

start.o: start.s
	${CPP} -E ${CFLAGS:M-[ID]*} -DLOCORE ${AINC} ${.IMPSRC} | \
	    ${AS} -o ${.TARGET}
E 4
E 3

D 3
tags: ${SRCS}
	ctags ${SRCS}
E 3
I 3
bootconf.o: conf.o
	rm -f bootconf.c
	ln -s conf.c bootconf.c
	${CC} -c ${CFLAGS} -DBOOT bootconf.c
	rm -f bootconf.c
E 3

D 3
FRC:
E 3
I 3
mkboot: mkboot.c
	${CC} ${CFLAGS} -o mkboot mkboot.c
E 3

I 3
mkboottape: mkboottape.c
	${CC} ${CFLAGS} -o mkboottape mkboottape.c
I 6

dec_label: dec_label.c
	${CC} ${CFLAGS} -o dec_label dec_label.c
E 6

# utilities

clean cleandir:
	rm -f .depend *.o *.exe *.i errs make.out core*
D 11
	rm -f a.out boot cat
E 11
I 11
	rm -f a.out ${ALL}
E 11
	rm -f boot[a-z][a-z] [a-z][a-z]boot
D 11
	rm -f libdrive.a mkboot mkboottape
E 11
I 11
	rm -f libdrive.a
E 11
	cd libsa; make cleandir

install:
	./mkboot boot rzboot bootrz
D 10
	install -s -o bin -g bin -m 444 rzboot ${DESTDIR}/usr/mdec
	install -s -o bin -g bin -m 444 bootrz ${DESTDIR}/usr/mdec
E 10
I 10
	install -o bin -g bin -m 444 rzboot ${DESTDIR}/usr/mdec
	install -o bin -g bin -m 444 bootrz ${DESTDIR}/usr/mdec
E 10

depend: ${SRCS}
	mkdep ${INCPATH} ${DEFS} ${SRCS}
	mkdep -a -p ${INCPATH} ${DEFS} mkboot.c mkboottape.c
	cd libsa; make depend
E 3
E 1
