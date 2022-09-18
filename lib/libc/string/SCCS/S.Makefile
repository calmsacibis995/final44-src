h39856
s 00007/00007/00121
d D 5.2 90/03/15 21:55:21 mckusick 2 1
c update for separate machine compilation
e
s 00128/00000/00000
d D 5.1 90/03/11 18:23:46 bostic 1 0
c date and time created 90/03/11 18:23:46 by bostic
e
u
U
t
T
I 1
#
# Copyright (c) 1989 The Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
#	%W% (Berkeley) %G%
#
OBJS=	atof.o atoi.o atol.o bcmp.o bcopy.o bzero.o ffs.o fnmatch.o \
	glob.o index.o \
	mktemp.o rindex.o strcasecmp.o strcat.o strcmp.o strcpy.o \
	strerror.o strftime.o strlen.o strncat.o strncmp.o strncpy.o \
	swab.o
SRCS=	atoi.c atol.c fnmatch.c mktemp.c strcasecmp.c strerror.c \
	strftime.c swab.c
ASRCS=	atof.s bcmp.s bcopy.s bzero.s ffs.s strcat.s strcmp.s strcpy.s \
	strlen.s strncat.s strncmp.s strncpy.s
MAN=	atof.0 bstring.0 fnmatch.0 glob.0 mktemp.0 strftime.0 string.0 \
	strtok.0 swab.0

# Tahoe specific sources
TSRC=	${SRCS} index.c rindex.c
TASRC=	${ASRCS}

# Vax specific sources
D 2
#VSRC=	${SRCS}
#VASRC=	${ASRCS} index.s rindex.s
E 2
I 2
VSRC=	${SRCS}
VASRC=	${ASRCS} index.s rindex.s
E 2

VPATH=	${MACHINE}
DEFS=	-DLIBC_SCCS
FLAGS=	-I../${MACHINE} ${DEFS}
CFLAGS=	-O ${DEFS}
MDIR=	${DESTDIR}/usr/man/cat3
TAGSFILE=tags

.SUFFIXES:
.SUFFIXES: .o .s .c .3 .0

.s.o:
	@${CPP} -E ${FLAGS} -DPROF $< | ${AS} -o $*.o
	@ld -X -o profiled/$*.o -r $*.o
	${CPP} -E ${FLAGS} $< | ${AS} -o $*.o
	@ld -x -r $*.o
D 2
	@mv a.out $*.o
E 2
I 2
	@mv ${OBJDIR}a.out ${OBJDIR}$*.o
E 2

.c.o:
	@${CC} -p ${CFLAGS} -c $<
	@-ld -X -o profiled/$*.o -r $*.o
	${CC} ${CFLAGS} -c $<
	@-ld -x -r $*.o
D 2
	@mv a.out $*.o
E 2
I 2
	@mv ${OBJDIR}a.out ${OBJDIR}$*.o
E 2

all: ${OBJS}
	cd ../library; rm -f ${OBJS}
D 2
	ln ${OBJS} ../library
E 2
I 2
	cd ${OBJDIR}.; ln ${OBJS} ../library
E 2
	cd ../profiled; rm -f ${OBJS}
D 2
	cd profiled; ln ${OBJS} ../../profiled
E 2
I 2
	cd ${OBJDIR}./profiled; ln ${OBJS} ../../profiled
E 2

clean:
D 2
	rm -f *.o profiled/* a.out core
E 2
I 2
	rm -f ${OBJDIR}*.o profiled/* ${OBJDIR}a.out core
E 2

cleandir: clean
	rm -f ${MAN} tags .depend

depend: depend.${MACHINE}

depend.tahoe: ${TSRC}
	mkdep ${CFLAGS} ${TSRC}

depend.vax: ${VSRC}
	mkdep ${CFLAGS} ${VSRC}

tags: tags.${MACHINE}

tags.tahoe: ${TASRC} ${TSRC}
	rm -f ${TAGSFILE}
	cwd=`pwd`; \
	for i in ${TSRC}; do \
		ctags -a -f ${TAGSFILE} $$cwd/$$i; \
	done
	(P=`pwd`; \
	egrep "^ENTRY(.*)|^SYSCALL(.*)" ${TASRC} | sed \
"s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 $$P/\1 /^\2(\3\4$$/;" \
	>> ${TAGSFILE})

tags.vax: ${VASRC} ${VSRC}
	rm -f ${TAGSFILE}
	cwd=`pwd`; \
	for i in ${VSRC}; do \
		ctags -a -f ${TAGSFILE} $$cwd/$$i; \
	done
	(P=`pwd`; \
	egrep "^ENTRY(.*)|^SYSCALL(.*)" ${VASRC} | sed \
"s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 $$P/\1 /^\2(\3\4$$/;" \
	>> ${TAGSFILE})

install: ${MAN}
	install -c -o bin -g bin -m 444 ${MAN} ${MDIR}
	rm -f ${MDIR}/atoi.0; ln ${MDIR}/atof.0 ${MDIR}/atoi.0
	rm -f ${MDIR}/atol.0; ln ${MDIR}/atof.0 ${MDIR}/atol.0
	rm -f ${MDIR}/bcmp.0; ln ${MDIR}/bstring.0 ${MDIR}/bcmp.0
	rm -f ${MDIR}/bcopy.0; ln ${MDIR}/bstring.0 ${MDIR}/bcopy.0
	rm -f ${MDIR}/bzero.0; ln ${MDIR}/bstring.0 ${MDIR}/bzero.0
	rm -f ${MDIR}/ffs.0; ln ${MDIR}/bstring.0 ${MDIR}/ffs.0
	rm -f ${MDIR}/index.0; ln ${MDIR}/string.0 ${MDIR}/index.0
	rm -f ${MDIR}/mkstemp.0; ln ${MDIR}/mktemp.0 ${MDIR}/mkstemp.0
	rm -f ${MDIR}/rindex.0; ln ${MDIR}/string.0 ${MDIR}/rindex.0
	rm -f ${MDIR}/strcat.0; ln ${MDIR}/string.0 ${MDIR}/strcat.0
	rm -f ${MDIR}/strcmp.0; ln ${MDIR}/string.0 ${MDIR}/strcmp.0
	rm -f ${MDIR}/strcpy.0; ln ${MDIR}/string.0 ${MDIR}/strcpy.0
	rm -f ${MDIR}/strlen.0; ln ${MDIR}/string.0 ${MDIR}/strlen.0
	rm -f ${MDIR}/strncat.0; ln ${MDIR}/string.0 ${MDIR}/strncat.0
	rm -f ${MDIR}/strncmp.0; ln ${MDIR}/string.0 ${MDIR}/strncmp.0
	rm -f ${MDIR}/strcasecmp.0; ln ${MDIR}/string.0 ${MDIR}/strcasecmp.0
	rm -f ${MDIR}/strncasecmp.0; ln ${MDIR}/string.0 ${MDIR}/strncasecmp.0
	rm -f ${MDIR}/strncpy.0; ln ${MDIR}/string.0 ${MDIR}/strncpy.0
	rm -f ${MDIR}/strsep.0; ln ${MDIR}/strtok.0 ${MDIR}/strsep.0
	rm -f ${MDIR}/globfree.0; ln ${MDIR}/glob.0 ${MDIR}/globfree.0
E 1
