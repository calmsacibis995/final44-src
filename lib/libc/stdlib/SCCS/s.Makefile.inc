h13040
s 00002/00002/00023
d D 8.3 95/02/04 08:32:57 pendry 21 20
c realpath now in gen/getcwd.c
e
s 00003/00002/00022
d D 8.2 94/02/16 13:36:35 bostic 20 19
c add realpath{3,c}; From: Jan-Simon Pendry <pendry@vangogh>
e
s 00000/00000/00024
d D 8.1 93/06/04 13:04:10 bostic 19 18
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00022
d D 5.18 93/05/26 17:11:10 bostic 18 17
c move multibyte stuff into ../locale
e
s 00002/00003/00022
d D 5.17 93/05/26 16:42:11 bostic 17 16
c delete multibyte.c; rune support from Paul Borman
e
s 00001/00001/00024
d D 5.16 93/04/16 08:33:39 bostic 16 15
c add mergesort link to qsort
e
s 00002/00002/00023
d D 5.15 93/03/02 17:56:30 bostic 15 14
c BSDI just gave us a multibyte(3)
e
s 00005/00004/00020
d D 5.14 93/02/10 20:58:47 bostic 14 13
c add atof.c to the SRCS lists
e
s 00002/00002/00022
d D 5.13 93/01/08 17:33:30 bostic 13 12
c add strtod, merge
e
s 00002/00000/00022
d D 5.12 92/06/25 09:16:49 bostic 12 11
c add strtoq.3 strtouq.3
e
s 00004/00013/00018
d D 5.11 92/06/25 09:14:46 bostic 11 10
c add strtoq, strtouq; break up machine dependent stuff
e
s 00001/00001/00030
d D 5.10 92/06/04 15:07:53 mckusick 10 9
c add support for luna68k from Omron
e
s 00002/00000/00029
d D 5.9 92/03/07 09:19:01 ralph 9 8
c added mips case
e
s 00006/00006/00023
d D 5.8 91/11/14 14:45:21 bostic 8 7
c move getsubopt.3 from libc/gen
e
s 00001/00001/00028
d D 5.7 91/08/06 11:44:55 torek 7 6
c MAN3+=, not MAN+3=
e
s 00004/00003/00025
d D 5.6 91/06/04 10:15:03 bostic 6 5
c add heapsort
e
s 00004/00004/00024
d D 5.5 91/05/02 04:50:42 cael 5 4
c deleted links to malloc, added files alloca,calloc,free,realloc,
c memory.
e
s 00006/00004/00022
d D 5.4 91/03/06 16:04:20 bostic 4 3
c add getopt(3), make links for random
e
s 00002/00002/00024
d D 5.3 91/02/18 10:32:26 donn 3 2
c Add our (trivial) multibyte character support.
e
s 00004/00004/00022
d D 5.2 90/11/11 09:05:15 bostic 2 1
c add radixsort
e
s 00026/00000/00000
d D 5.1 90/06/23 16:23:33 bostic 1 0
c date and time created 90/06/23 16:23:33 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 11
# stdlib sources
E 11
I 11
# machine-independent stdlib sources
E 11
.PATH: ${.CURDIR}/${MACHINE}/stdlib ${.CURDIR}/stdlib

D 14
SRCS+=	abort.c atexit.c atoi.c atol.c bsearch.c calloc.c div.c exit.c \
D 2
	getenv.c labs.c ldiv.c malloc.c putenv.c qsort.c rand.c setenv.c \
	strtol.c strtoul.c system.c
E 2
I 2
D 3
	getenv.c labs.c ldiv.c malloc.c putenv.c qsort.c radixsort.c \
	rand.c setenv.c strtol.c strtoul.c system.c
E 3
I 3
D 4
	getenv.c labs.c ldiv.c malloc.c multibyte.c putenv.c qsort.c \
	radixsort.c rand.c setenv.c strtol.c strtoul.c system.c
E 4
I 4
D 6
	getenv.c getopt.c labs.c ldiv.c malloc.c multibyte.c putenv.c \
	qsort.c radixsort.c rand.c random.c setenv.c strtol.c strtoul.c \
	system.c
E 6
I 6
D 8
	getenv.c getopt.c heapsort.c labs.c ldiv.c malloc.c multibyte.c \
	putenv.c qsort.c radixsort.c rand.c random.c setenv.c strtol.c \
	strtoul.c system.c
E 8
I 8
	getenv.c getopt.c getsubopt.c heapsort.c labs.c ldiv.c malloc.c \
D 13
	multibyte.c putenv.c qsort.c radixsort.c rand.c random.c setenv.c \
D 11
	strtol.c strtoul.c system.c
E 11
I 11
	strtol.c strtoq.c strtoul.c strtouq.c system.c
E 13
I 13
	merge.c multibyte.c putenv.c qsort.c radixsort.c rand.c random.c \
	setenv.c strtod.c strtol.c strtoq.c strtoul.c strtouq.c system.c
E 14
I 14
SRCS+=	abort.c atexit.c atof.c atoi.c atol.c bsearch.c calloc.c div.c \
	exit.c getenv.c getopt.c getsubopt.c heapsort.c labs.c ldiv.c \
D 17
	malloc.c merge.c multibyte.c putenv.c qsort.c radixsort.c rand.c \
	random.c setenv.c strtod.c strtol.c strtoq.c strtoul.c strtouq.c \
	system.c
E 17
I 17
	malloc.c merge.c putenv.c qsort.c radixsort.c rand.c random.c \
D 20
	setenv.c strtod.c strtol.c strtoq.c strtoul.c strtouq.c system.c
E 20
I 20
D 21
	realpath.c setenv.c strtod.c strtol.c strtoq.c strtoul.c \
E 21
I 21
	setenv.c strtod.c strtol.c strtoq.c strtoul.c \
E 21
	strtouq.c system.c
E 20
E 17
E 14
E 13
E 11
E 8
E 6
E 4
E 3
E 2

D 10
.if   (${MACHINE} == "hp300")
E 10
I 10
D 11
.if   (${MACHINE} == "hp300" || ${MACHINE} == "luna68k")
E 10
SRCS+=	abs.s atof.c
.elif (${MACHINE} == "i386")
SRCS+=	abs.s atof.c
I 9
.elif (${MACHINE} == "mips")
SRCS+=	abs.s atof.c
E 9
.elif (${MACHINE} == "tahoe")
SRCS+=	abs.s atof.s
.elif (${MACHINE} == "vax")
SRCS+=	abs.s atof.s
.endif
E 11
I 11
# machine-dependent stdlib sources
.include "${.CURDIR}/${MACHINE}/stdlib/Makefile.inc"
E 11

D 5
MAN3+=	abort.0 abs.0 atexit.0 atof.0 atoi.0 atol.0 bsearch.0 div.0 exit.0 \
D 2
	getenv.0 labs.0 ldiv.0 malloc.0 qsort.0 rand.0 strtod.0 strtol.0 \
	strtoul.0 system.0
E 2
I 2
D 4
	getenv.0 labs.0 ldiv.0 malloc.0 qsort.0 radixsort.0 rand.0 strtod.0 \
	strtol.0 strtoul.0 system.0
E 4
I 4
	getenv.0 getopt.0 labs.0 ldiv.0 malloc.0 qsort.0 radixsort.0 rand.0 \
	random.0 strtod.0 strtol.0 strtoul.0 system.0
E 5
I 5
D 7
MAN+3=	abort.0 abs.0 alloca.0 atexit.0 atof.0 atoi.0 atol.0 bsearch.0 \
E 7
I 7
MAN3+=	abort.0 abs.0 alloca.0 atexit.0 atof.0 atoi.0 atol.0 bsearch.0 \
E 7
D 8
	calloc.0 div.0 exit.0 free.0 getenv.0 getopt.0 labs.0 ldiv.0 \
	malloc.0 memory.0 qsort.0 radixsort.0 rand.0 random.0 realloc.0 \
	strtod.0 strtol.0 strtoul.0 system.0
E 8
I 8
	calloc.0 div.0 exit.0 free.0 getenv.0 getopt.0 getsubopt.0 labs.0 \
D 15
	ldiv.0 malloc.0 memory.0 qsort.0 radixsort.0 rand.0 random.0 \
	realloc.0 strtod.0 strtol.0 strtoul.0 system.0
E 15
I 15
D 18
	ldiv.0 malloc.0 memory.0 multibyte.0 qsort.0 radixsort.0 rand.0 \
	random.0 realloc.0 strtod.0 strtol.0 strtoul.0 system.0
E 18
I 18
	ldiv.0 malloc.0 memory.0 qsort.0 radixsort.0 rand.0 random.0 \
D 20
	realloc.0 strtod.0 strtol.0 strtoul.0 system.0
E 20
I 20
D 21
	realloc.0 realpath.0 strtod.0 strtol.0 strtoul.0 system.0
E 21
I 21
	realloc.0 strtol.0 strtoul.0 system.0
E 21
E 20
E 18
E 15
E 8
E 5
E 4
E 2

D 5
MLINKS+=malloc.3 alloca.3 malloc.3 calloc.3 malloc.3 free.3 malloc.3 realloc.3
E 5
MLINKS+=getenv.3 setenv.3 getenv.3 unsetenv.3 getenv.3 putenv.3
I 6
D 16
MLINKS+=qsort.3 heapsort.3
E 16
I 16
MLINKS+=qsort.3 heapsort.3 qsort.3 mergesort.3
E 16
E 6
MLINKS+=rand.3 srand.3
I 4
MLINKS+=random.3 initstate.3 random.3 setstate.3 random.3 srandom.3
I 12
MLINKS+=strtol.3 strtoq.3
MLINKS+=strtoul.3 strtouq.3
E 12
E 4
E 1
