h41538
s 00000/00000/00009
d D 8.1 93/06/04 13:02:06 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00009/00000/00000
d D 5.1 92/06/25 06:34:21 torek 1 0
c date and time created 92/06/25 06:34:21 by torek
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

# machine-independent string sources (from ../../string)
SRCS+=	bcmp.c bcopy.c index.c memchr.c memcmp.c memset.c rindex.c strcat.c \
	strcmp.c strcpy.c strcspn.c strncat.c strncmp.c strncpy.c strpbrk.c \
	strsep.c strspn.c strstr.c

# machine-dependent string sources
SRCS+=	bzero.s ffs.s strlen.s
E 1
