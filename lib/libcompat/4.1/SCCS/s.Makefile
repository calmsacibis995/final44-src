h45896
s 00069/00023/00037
d D 5.13 90/03/22 14:36:25 bostic 16 15
c checkpoint before pmake
e
s 00000/00026/00060
d D 5.12 88/08/30 16:06:17 bostic 15 14
c remove dependency list
e
s 00010/00005/00076
d D 5.11 88/07/09 11:13:16 bostic 14 13
c install approved copyright notice
e
s 00004/00007/00077
d D 5.10 88/06/09 19:21:01 bostic 13 12
c remove str{cat,cmp,cpy}n.c from distribution
e
s 00013/00007/00071
d D 5.9 88/06/03 18:24:22 bostic 12 11
c add {strcat,strcmp,strcpy}n.c; they aren't Sys V routines, they're
c 32v routines.
e
s 00001/00000/00077
d D 5.8 88/05/20 15:02:02 bostic 11 10
c set DEFS to compile in SCCS ids.
e
s 00025/00016/00052
d D 5.7 88/05/20 13:46:04 bostic 10 9
c restructuring libc
e
s 00001/00001/00067
d D 5.6 87/08/31 15:31:25 bostic 9 8
c spelling check
e
s 00023/00017/00045
d D 5.5 87/06/06 14:58:42 bostic 8 7
c new template
e
s 00022/00001/00040
d D 5.4 85/09/05 11:51:35 bloom 7 5
c fix make clean and add make depend
e
s 00022/00001/00040
d R 5.4 85/09/05 09:49:41 bloom 6 5
c fix make clean and add make depend
e
s 00001/00001/00040
d D 5.3 85/06/18 22:46:08 mckusick 5 4
c add DEFS
e
s 00012/00001/00029
d D 5.2 85/05/30 22:34:36 sam 4 3
c add tags
e
s 00006/00001/00024
d D 5.1 85/05/30 09:50:53 dist 3 2
c Add copyright
e
s 00001/00001/00024
d D 4.2 83/07/05 19:51:34 sam 2 1
c reset goes back to machine dependent
e
s 00025/00000/00000
d D 4.1 83/07/04 11:56:05 sam 1 0
c date and time created 83/07/04 11:56:05 by sam
e
u
U
t
T
I 1
D 3
#	%M%	%I%	%E%
E 3
I 3
#
D 10
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 10
I 10
# Copyright (c) 1988 Regents of the University of California.
# All rights reserved.
E 10
#
I 10
# Redistribution and use in source and binary forms are permitted
D 14
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 14
I 14
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
D 16
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 16
I 16
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 16
E 14
#
E 10
#	%W% (Berkeley) %G%
E 3
#
I 11
D 16
DEFS=	-DLIBC_SCCS
E 11
D 5
CFLAGS=	-O
E 5
I 5
CFLAGS=	-O ${DEFS}
E 16
E 5
I 4
D 12
STDSRCS=ftime.c gtty.c nice.c pause.c rand.c stty.c tell.c \
	times.c utime.c vlimit.c vtimes.c
E 4
STD=	ftime.o gtty.o nice.o pause.o rand.o stty.o tell.o \
	times.o utime.o vlimit.o vtimes.o
E 12
I 12

D 13
STDSRCS=ftime.c gtty.c nice.c pause.c rand.c strcatn.c strcmpn.c strcpyn.c \
	stty.c tell.c times.c utime.c vlimit.c vtimes.c
STDOBJS=ftime.o gtty.o nice.o pause.o rand.o strcatn.o strcmpn.o strcpyn.o \
	stty.o tell.o times.o utime.o vlimit.o vtimes.o
E 13
I 13
D 16
STDSRCS=ftime.c gtty.c nice.c pause.c rand.c stty.c tell.c times.c \
	utime.c vlimit.c vtimes.c
STDOBJS=ftime.o gtty.o nice.o pause.o rand.o stty.o tell.o times.o \
E 16
I 16
OBJS=	ftime.o getpw.o gtty.o rand.o reset.o stty.o tell.o times.o \
E 16
	utime.o vlimit.o vtimes.o
I 16
SRCS=	ftime.c getpw.c gtty.c rand.c stty.c tell.c times.c utime.c \
	vlimit.c vtimes.c
ASRCS=	reset.s
MAN=	ftime.0 getpw.0 rand.0 stty.0 times.0 utime.0 vlimit.0 vtimes.0
E 16
E 13

E 12
D 16
# these should just be pitched, but in the interest of compatibility...
I 4
D 12
TRASHSRC=getpw.c
E 4
D 2
TRASH=	getpw.o reset.o
E 2
I 2
TRASH=	getpw.o 
E 12
I 12
TRASHSRCS=getpw.c
TRASHOBJS=getpw.o
E 12
I 4
SRCS=	${STDSRCS} ${TRASHSRCS}
E 4
E 2
D 12
OBJS=	${STD} ${TRASH}
E 12
I 12
OBJS=	${STDOBJS} ${TRASHOBJS}
E 16
I 16
# Tahoe specific sources
TSRC=	${SRCS}
TASRC=	${ASRCS}

# Vax specific sources
#VSRC=	${SRCS}
#VASRC=	${ASRCS}

VPATH=	${MACHINE}
FLAGS=	-I${MACHINE} -I../../libc/${MACHINE}
DEFS=	-DLIBC_SCCS
CFLAGS=	-O ${DEFS}
E 16
E 12
I 4
TAGSFILE=tags
I 16
MDIR=	/usr/man/cat3
E 16
E 4

I 16
.SUFFIXES:
.SUFFIXES: .o .s .c .3 .0

.s.o:
	@${CPP} -E ${FLAGS} -DPROF $*.s | ${AS} -o $*.o
	@ld -X -o profiled/$*.o -r $*.o
	${CPP} -E ${FLAGS} $*.s | ${AS} -o $*.o
	@ld -x -r $*.o
	@mv a.out $*.o

E 16
.c.o:
D 10
	${CC} -p ${CFLAGS} -c $*.c
	-ld -X -r $*.o
	mv a.out profiled/$*.o
E 10
I 10
	@${CC} -p ${CFLAGS} -c $*.c
	@-ld -X -o profiled/$*.o -r $*.o
E 10
	${CC} ${CFLAGS} -c $*.c
D 10
	-ld -x -r $*.o
	mv a.out $*.o
E 10
I 10
	@-ld -x -r $*.o
	@mv a.out $*.o
E 10

D 10
compat-4.1lib compat-4.1lib_p: ${OBJS}
	@echo "building profiled compat-4.1lib"
	@cd profiled; ar cru ../compat-4.1lib_p ${OBJS}
D 9
	@echo "buiding normal compat-4.1lib"
E 9
I 9
	@echo "building normal compat-4.1lib"
E 9
	@ar cru compat-4.1lib ${OBJS}
E 10
I 10
all: ${OBJS}
E 10

I 10
D 16
link: ${OBJS}
	(cd ../library; rm -f ${OBJS})
	(cd ../profiled; rm -f ${OBJS})
	ln ${OBJS} ../library
	(cd profiled; ln ${OBJS} ../../profiled)
E 16
I 16
clean:
	rm -f *.o profiled/* a.out core
E 16

E 10
I 4
D 16
tags:
E 16
I 16
cleandir: clean
	rm -f ${MAN} tags .depend

depend: depend.${MACHINE}

depend.tahoe: ${TSRC}
	mkdep ${CFLAGS} ${TSRC}

depend.vax: ${VSRC}
	mkdep ${CFLAGS} ${VSRC}

tags: tags.${MACHINE}

tags.tahoe: ${TSRC} ${TASRC}
	rm -f ${TAGSFILE}
E 16
	cwd=`pwd`; \
D 16
	for i in ${SRCS}; do \
E 16
I 16
	for i in ${TSRC}; do \
E 16
		ctags -a -f ${TAGSFILE} $$cwd/$$i; \
	done
I 16
	(P=`pwd`; \
	egrep "^ENTRY(.*)|^SYSCALL(.*)" ${TASRC} | sed \
"s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 $$P/\1 /^\2(\3\4$$/;" \
	>> ${TAGSFILE})
E 16

E 4
D 16
clean:
D 4
	rm -f compat-4.1lib compat-4.1lib_p ${OBJS} profiled/*.o
E 4
I 4
D 7
	rm -f compat-4.1lib compat-4.1lib_p ${OBJS} profiled/*.o tags
E 7
I 7
D 8
	rm -f compat-4.1lib compat-4.1lib_p *.o profiled/*.o tags Makefile.bak
E 8
I 8
D 10
	rm -f compat-4.1lib compat-4.1lib_p *.o profiled/*.o tags
E 10
I 10
	rm -f *.o profiled/* a.out core ${TAGSFILE}
E 16
I 16
tags.vax: ${VSRC} ${VASRC}
	rm -f ${TAGSFILE}
	cwd=`pwd`; \
	for i in ${VSRC}; do \
		ctags -a -f ${TAGSFILE} $$cwd/$$i; \
	done
	(P=`pwd`; \
	egrep "^ENTRY(.*)|^SYSCALL(.*)" ${VASRC} | sed \
"s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 $$P/\1 /^\2(\3\4$$/;" \
	>> ${TAGSFILE})
E 16
E 10
E 8

D 16
depend:
D 8
	for i in ${SRCS}; do \
	    cc -M ${CFLAGS} $$i | awk ' { if ($$1 != prev) \
		{ if (rec != "") print rec; rec = $$0; prev = $$1; } \
		else { if (length(rec $$2) > 78) { print rec; rec = $$0; } \
		else rec = rec " " $$2 } } \
		END { print rec } ' >> makedep; done
	echo '/^# DO NOT DELETE THIS LINE/+2,$$d' >eddep
	echo '$$r makedep' >>eddep
	echo 'w' >>eddep
	cp Makefile Makefile.bak
	ed - Makefile < eddep
	rm eddep makedep
	echo '# DEPENDENCIES MUST END AT END OF FILE' >> Makefile
	echo '# IF YOU PUT STUFF HERE IT WILL GO AWAY' >> Makefile
	echo '# see make depend above' >> Makefile
E 8
I 8
	mkdep ${CFLAGS} ${SRCS}
E 8

E 16
I 16
install: ${MAN}
	cd ../library; rm -f ${OBJS}
	ln ${OBJS} ../library
	cd ../profiled; rm -f ${OBJS}
	cd profiled; ln ${OBJS} ../../profiled
	install -c -o bin -g bin -m 444 ${MAN} ${MDIR}
	rm -f ${MDIR}/srand.0; ln ${MDIR}/rand.0 ${MDIR}/srand.0
	rm -f ${MDIR}/gtty.0; ln ${MDIR}/stty.0 ${MDIR}/gtty.0
E 16
D 8
# DO NOT DELETE THIS LINE -- make depend uses it
E 8
I 8
D 15
# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.
E 8

I 8
ftime.o: ftime.c /usr/include/sys/types.h /usr/include/sys/time.h
ftime.o: /usr/include/time.h
gtty.o: gtty.c /usr/include/sgtty.h /usr/include/sys/ioctl.h
D 10
gtty.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
E 10
I 10
gtty.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydefaults.h
gtty.o: /usr/include/sys/ttydev.h
E 10
nice.o: nice.c /usr/include/sys/time.h /usr/include/time.h
nice.o: /usr/include/sys/resource.h
pause.o: pause.c
rand.o: rand.c
I 12
D 13
strcatn.o: strcatn.c
strcmpn.o: strcmpn.c
strcpyn.o: strcpyn.c
E 13
E 12
stty.o: stty.c /usr/include/sgtty.h /usr/include/sys/ioctl.h
D 10
stty.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
E 10
I 10
stty.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydefaults.h
stty.o: /usr/include/sys/ttydev.h
E 10
tell.o: tell.c
times.o: times.c /usr/include/sys/time.h /usr/include/time.h
times.o: /usr/include/sys/resource.h
utime.o: utime.c /usr/include/sys/time.h /usr/include/time.h
vlimit.o: vlimit.c /usr/include/sys/time.h /usr/include/time.h
vlimit.o: /usr/include/sys/resource.h /usr/include/errno.h
vtimes.o: vtimes.c /usr/include/sys/time.h /usr/include/time.h
vtimes.o: /usr/include/sys/resource.h
I 12
getpw.o: getpw.c /usr/include/stdio.h
E 12
E 8

I 8
# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 15
E 8
E 7
E 4
E 1
