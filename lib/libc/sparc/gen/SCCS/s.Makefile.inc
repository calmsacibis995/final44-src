h26243
s 00000/00000/00041
d D 8.1 93/06/04 13:01:57 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00002/00040
d D 5.4 93/04/12 17:46:59 torek 4 3
c main.s no longer needed (libc/gen has it)
e
s 00004/00000/00038
d D 5.3 92/07/24 14:29:29 bostic 3 2
c create mode 444, so don't look writeable in the kernel library
e
s 00009/00002/00029
d D 5.2 92/07/09 19:33:12 torek 2 1
c sort; copy multiply/divide code to libkern
e
s 00031/00000/00000
d D 5.1 92/06/25 06:16:58 torek 1 0
c date and time created 92/06/25 06:16:58 by torek
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

# machine-dependent gen sources
D 4
SRCS+=	_setjmp.s fabs.s fixunsdfsi.s main.s modf.s mul.s saveregs.s \
	setjmp.s umul.s
E 4
I 4
SRCS+=	_setjmp.s fabs.s fixunsdfsi.s modf.s mul.s saveregs.s setjmp.s umul.s
E 4
SRCS+=	frexp.c isinf.c isnan.c ldexp.c

# `source' files built from m4 source
# the name `div.o' is taken for the ANSI C `div' function, hence sdiv here
D 2
SRCS+=	sdiv.s udiv.s rem.s urem.s
CLEANFILES+=sdiv.s udiv.s rem.s urem.s
E 2
I 2
SRCS+=	rem.s sdiv.s udiv.s urem.s
CLEANFILES+=rem.s sdiv.s udiv.s urem.s

# these are copied down to the kernel library
KMSRCS+=mul.s rem.s sdiv.s udiv.s umul.s urem.s

# need DEFS.h too
libkern.sparc::
	cp -p ${.CURDIR}/sparc/DEFS.h /sys/libkern/sparc
E 2

sdiv.s: divrem.m4
	@echo 'building ${.TARGET} from ${.ALLSRC}'
	@(echo "define(NAME,\`.div')define(OP,\`div')define(S,\`true')"; \
	 cat ${.ALLSRC}) | m4 > ${.TARGET}
I 3
	@chmod 444 ${.TARGET}
E 3

udiv.s: divrem.m4
	@echo 'building ${.TARGET} from ${.ALLSRC}'
	@(echo "define(NAME,\`.udiv')define(OP,\`div')define(S,\`false')"; \
	 cat ${.ALLSRC}) | m4 > ${.TARGET}
I 3
	@chmod 444 ${.TARGET}
E 3

rem.s: divrem.m4
	@echo 'building ${.TARGET} from ${.ALLSRC}'
	@(echo "define(NAME,\`.rem')define(OP,\`rem')define(S,\`true')"; \
	 cat ${.ALLSRC}) | m4 > ${.TARGET}
I 3
	@chmod 444 ${.TARGET}
E 3

urem.s: divrem.m4
	@echo 'building ${.TARGET} from ${.ALLSRC}'
	@(echo "define(NAME,\`.urem')define(OP,\`rem')define(S,\`false')"; \
	 cat ${.ALLSRC}) | m4 > ${.TARGET}
I 3
	@chmod 444 ${.TARGET}
E 3
E 1
