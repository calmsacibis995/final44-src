h53515
s 00012/00009/00057
d D 1.2 93/07/27 09:17:19 bostic 2 1
c checkpoint; Mike Karels left this checked out.
e
s 00066/00000/00000
d D 1.1 90/11/02 15:01:09 karels 1 0
c date and time created 90/11/02 15:01:09 by karels
e
u
U
t
T
I 2
#	%W% (Berkeley) %G%

E 2
I 1
CFLAGS=	-O
D 2
LIBC=	/lib/libc.a
E 2
I 2
LIBC=	/usr/lib/libc.a
E 2

# Programs that live in subdirectories, and have makefiles of their own.
#
SUBDIR=	cmd.${MACHINE}

# Shell scripts that need only be installed and are never removed.
#
SCRIPT= Correct Spell difftc itroff

# C sources that live in the current directory
#
D 2
SRCS=	20b.c 2621.c chgbars.c cpr.c dis.c dl.c \
	doorcard.c la.c rinfo.c sdiff.c showtc.c yank.c
E 2
I 2
SRCS=	20b.c chgbars.c doorcard.c la.c rinfo.c sdiff.c showtc.c
E 2

# C programs that live in the current directory and do not need
# explicit make lines.
#
D 2
STD=	20b 2621 chgbars cpr dl doorcard rinfo sdiff yank
E 2
I 2
STD=	20b chgbars doorcard rinfo sdiff
E 2

# C programs that live in the current directory and need explicit make lines.
#
D 2
NSTD=	dis showtc
E 2
I 2
NSTD=	showtc
E 2

# Programs that get installed with special permissions
#
PERM=	la

all:	${SUBDIR} ${STD} ${PERM} ${NSTD}

${SUBDIR}: FRC
	cd $@; make ${MFLAGS}

D 2
${STD} ${PERM}: ${LIBC}
E 2
I 2
${STD}: ${LIBC}
E 2
	${CC} ${CFLAGS} -o $@ $@.c

clean cleandir: FRC
	-for i in ${SUBDIR} cmd.vax cmd.tahoe; do \
		(cd $$i; make ${MFLAGS} clean); \
	done
	rm -f a.out core *.s *.o ${STD} ${PERM} ${NSTD}

depend: ldepend
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS} depend); done

ldepend: FRC
	mkdep -p ${CFLAGS} ${SRCS}

install: FRC
	-for i in ${SUBDIR}; do \
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} install); done
	-for i in ${SCRIPT}; do \
D 2
		(install -c -o bin -g bin -m 755 $$i.sh ${DESTDIR}/usr/local/$$i); \
E 2
I 2
		(install -c -o bin -g bin -m 755 $$i.sh ${DESTDIR}/usr/local/bin/$$i); \
E 2
	done
D 2
	install -s -o bin -g bin -m 755 ${STD} ${NSTD} ${DESTDIR}/usr/local
E 2
I 2
	install -s -o bin -g bin -m 755 ${STD} ${NSTD} ${DESTDIR}/usr/local/bin
E 2
# programs that run with special permissions
D 2
	install -s -o bin -g kmem -m 2755 la ${DESTDIR}/usr/local/la
E 2
I 2
	install -s -o bin -g kmem -m 2755 la ${DESTDIR}/usr/local/bin/la
E 2

FRC:

# Files listed in ${NSTD} and ${OPTIONAL} have explicit make lines given below.

showtc dis:
	${CC} ${CFLAGS} -o $@ $@.c -ltermcap

I 2
la:
	${CC} ${CFLAGS} -o $@ $@.c -lutil
E 2
E 1
