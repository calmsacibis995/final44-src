h10817
s 00000/00000/00092
d D 8.1 93/06/04 15:09:58 bostic 13 12
c 4.4BSD snapshot (revision 8.1)
e
s 00014/00000/00078
d D 5.12 93/05/12 11:04:50 bostic 12 11
c build bzero(3) from memset(3)
e
s 00007/00033/00071
d D 5.11 92/06/25 09:16:02 bostic 11 10
c break up machine dependent stuff
e
s 00001/00001/00103
d D 5.10 92/06/04 15:09:45 mckusick 10 9
c add support for luna68k from Omron
e
s 00004/00003/00100
d D 5.9 91/09/14 10:36:07 bostic 9 8
c move strerror from stdio to here
e
s 00000/00000/00103
d D 5.8 91/09/06 18:36:11 ralph 8 7
c added mips
e
s 00005/00000/00098
d D 5.7 91/09/06 18:32:38 ralph 7 6
c added mips
e
s 00001/00001/00097
d D 5.6 91/03/05 15:04:50 bostic 6 5
c mv strerror into ../stdio
e
s 00001/00001/00097
d D 5.5 91/02/24 13:45:12 bostic 5 4
c typo
e
s 00001/00001/00097
d D 5.4 90/06/25 21:11:04 bostic 4 3
c Chris hadn't tested another one
e
s 00005/00000/00093
d D 5.3 90/06/24 14:12:05 bostic 3 2
c forgot the links for the strn* routines
e
s 00002/00003/00091
d D 5.2 90/06/24 14:08:11 bostic 2 1
c fold strn{casecmp,cat,cmp,cpy}.3 into str{casecmp,cat,cmp,cpy}.3
e
s 00094/00000/00000
d D 5.1 90/06/23 16:23:39 bostic 1 0
c date and time created 90/06/23 16:23:39 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 11
# string sources
E 11
.PATH: ${.CURDIR}/${MACHINE}/string ${.CURDIR}/string

I 11
# machine-independent string sources
E 11
D 6
SRCS+=	memccpy.c strcasecmp.c strcoll.c strdup.c strerror.c \
E 6
I 6
D 9
SRCS+=	memccpy.c strcasecmp.c strcoll.c strdup.c \
E 9
I 9
SRCS+=	memccpy.c strcasecmp.c strcoll.c strdup.c strerror.c \
E 9
E 6
	strftime.c strmode.c strtok.c strxfrm.c swab.c

D 10
.if   (${MACHINE} == "hp300")
E 10
I 10
D 11
.if   (${MACHINE} == "hp300" || ${MACHINE} == "luna68k")
E 10
SRCS+=	bcmp.s bcopy.s bzero.s ffs.s index.s memchr.c memcmp.c memset.c \
	rindex.s strcat.c strcmp.s strcpy.s strcspn.c strlen.s \
	strncat.c strncmp.s strncpy.s strpbrk.c strsep.c \
D 5
	strstr.c strstr.c
E 5
I 5
	strspn.c strstr.c
E 5
.elif (${MACHINE} == "i386")
SRCS+=	bcmp.c bcopy.c bzero.s ffs.c index.c memchr.c memcmp.c memset.c \
	rindex.c strcat.c strcmp.c strcpy.c strcspn.c strlen.c \
	strncat.c strncmp.c strncpy.c strpbrk.c strsep.c \
	strspn.c strstr.c
I 7
.elif (${MACHINE} == "mips")
SRCS+=	bcmp.s bcopy.s bzero.s ffs.s index.s memchr.c memcmp.c memset.c \
	rindex.s strcat.c strcmp.s strcpy.c strcspn.c strlen.s \
	strncat.c strncmp.c strncpy.c strpbrk.c strsep.c \
	strspn.c strstr.c
E 7
.elif (${MACHINE} == "tahoe")
D 4
SRCS+=	bcmp.s bcopy.s bzero.s ffs.s index.c memchr.c memcmp.s memset.s \
E 4
I 4
SRCS+=	bcmp.s bcopy.s bzero.s ffs.s index.c memchr.c memcmp.s memset.c \
E 4
	rindex.c strcat.s strcmp.s strcpy.s strcspn.c strlen.s \
	strncat.s strncmp.s strncpy.s strpbrk.c strsep.c \
	strspn.c strstr.c
SRCS+=	memmove.s
.elif (${MACHINE} == "vax")
SRCS+=	bcmp.s bcopy.s bzero.s ffs.s index.c memchr.s memcmp.s memset.s \
	rindex.s strcat.s strcmp.s strcpy.s strcspn.s strlen.s \
	strncat.s strncmp.s strncpy.s strpbrk.s strsep.s \
	strspn.s strstr.s
SRCS+=	memmove.s strchr.s strrchr.s
.endif
E 11
I 11
# machine-dependent string sources
.include "${.CURDIR}/${MACHINE}/string/Makefile.inc"
E 11

I 12
# If no machine specific bzero(3), build one out of memset(3).
.if empty(SRCS:Mbzero.s)
OBJS+=	bzero.o
bzero.o: memset.c
	${CC} -DBZERO ${CFLAGS} -c ${.ALLSRC} -o ${.TARGET}
	@${LD} -x -r ${.TARGET}
	@mv a.out ${.TARGET}

bzero.po: memset.c
	${CC} -DBZERO ${CFLAGS} -c -p ${.ALLSRC} -o ${.TARGET}
	@${LD} -X -r ${.TARGET}
	@mv a.out ${.TARGET}
.endif

E 12
D 11
# if no machine specific memmove(3), build one out of bcopy(3).
E 11
I 11
# If no machine specific memmove(3), build one out of bcopy(3).
E 11
.if empty(SRCS:Mmemmove.s)
OBJS+=	memmove.o
memmove.o: bcopy.c
	${CC} -DMEMMOVE ${CFLAGS} -c ${.ALLSRC} -o ${.TARGET}
	@${LD} -x -r ${.TARGET}
	@mv a.out ${.TARGET}

memmove.po: bcopy.c
	${CC} -DMEMMOVE ${CFLAGS} -c -p ${.ALLSRC} -o ${.TARGET}
	@${LD} -X -r ${.TARGET}
	@mv a.out ${.TARGET}
.endif

D 11
# if no machine specific memcpy(3), build one out of bcopy(3).
E 11
I 11
# If no machine specific memcpy(3), build one out of bcopy(3).
E 11
.if empty(SRCS:Mmemcpy.s)
OBJS+=	memcpy.o
memcpy.o: bcopy.c
	${CC} -DMEMCOPY ${CFLAGS} -c ${.ALLSRC} -o ${.TARGET}
	@${LD} -x -r ${.TARGET}
	@mv a.out ${.TARGET}

memcpy.po: bcopy.c
	${CC} -DMEMCOPY ${CFLAGS} -c -p ${.ALLSRC} -o ${.TARGET}
	@${LD} -X -r ${.TARGET}
	@mv a.out ${.TARGET}
.endif

D 11
# if no machine specific strchr(3), build one out of index(3).
E 11
I 11
# If no machine specific strchr(3), build one out of index(3).
E 11
.if empty(SRCS:Mstrchr.s)
OBJS+=	strchr.o
strchr.o: index.c
	${CC} -DSTRCHR ${CFLAGS} -c ${.ALLSRC} -o ${.TARGET}
	@${LD} -x -r ${.TARGET}
	@mv a.out ${.TARGET}

strchr.po: index.c
	${CC} -DSTRCHR ${CFLAGS} -c -p ${.ALLSRC} -o ${.TARGET}
	@${LD} -X -r ${.TARGET}
	@mv a.out ${.TARGET}
.endif

D 11
# if no machine specific strrchr(3), build one out of rindex(3).
E 11
I 11
# If no machine specific strrchr(3), build one out of rindex(3).
E 11
.if empty(SRCS:Mstrrchr.s)
OBJS+=	strrchr.o
strrchr.o: rindex.c
	${CC} -DSTRRCHR ${CFLAGS} -c ${.ALLSRC} -o ${.TARGET}
	@${LD} -x -r ${.TARGET}
	@mv a.out ${.TARGET}

strrchr.po: rindex.c
	${CC} -DSTRRCHR ${CFLAGS} -c -p ${.ALLSRC} -o ${.TARGET}
	@${LD} -X -r ${.TARGET}
	@mv a.out ${.TARGET}
.endif

MAN3+=	bcmp.0 bcopy.0 bstring.0 bzero.0 ffs.0 index.0 memccpy.0 memchr.0 \
	memcmp.0 memcpy.0 memmove.0 memset.0 rindex.0 strcasecmp.0 strcat.0 \
	strchr.0 strcmp.0 strcoll.0 strcpy.0 strcspn.0 strftime.0 string.0 \
D 2
	strlen.0 strmode.0 strdup.0 strncasecmp.0 strncat.0 strncmp.0 \
	strncpy.0 strpbrk.0 strrchr.0 strsep.0 strspn.0 strstr.0 strtok.0 \
	strxfrm.0 swab.0
E 2
I 2
D 9
	strlen.0 strmode.0 strdup.0 strpbrk.0 strrchr.0 strsep.0 strspn.0 \
	strstr.0 strtok.0 strxfrm.0 swab.0
E 9
I 9
	strlen.0 strmode.0 strdup.0 strerror.0 strpbrk.0 strrchr.0 strsep.0 \
	strspn.0 strstr.0 strtok.0 strxfrm.0 swab.0
E 9
I 3

MLINKS+=strcasecmp.3 strncasecmp.3
MLINKS+=strcat.3 strncat.3
MLINKS+=strcmp.3 strncmp.3
MLINKS+=strcpy.3 strncpy.3
I 9
MLINKS+=strerror.3 perror.3
E 9
E 3
E 2
E 1
