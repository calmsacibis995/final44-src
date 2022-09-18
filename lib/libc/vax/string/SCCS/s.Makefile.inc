h50916
s 00000/00000/00006
d D 8.1 93/06/04 15:41:56 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00005
d D 5.2 92/10/16 17:29:27 torek 2 1
c we have a perfectly good index.s; let's use it
e
s 00006/00000/00000
d D 5.1 92/06/26 06:54:09 bostic 1 0
c date and time created 92/06/26 06:54:09 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
SRCS+=	bcmp.s bcopy.s bzero.s ffs.s index.c memchr.s memcmp.s memset.s \
E 2
I 2
SRCS+=	bcmp.s bcopy.s bzero.s ffs.s index.s memchr.s memcmp.s memset.s \
E 2
	rindex.s strcat.s strcmp.s strcpy.s strcspn.s strlen.s strncat.s \
	strncmp.s strncpy.s strpbrk.s strsep.s strspn.s strstr.s
SRCS+=	memmove.s strchr.s strrchr.s
E 1
