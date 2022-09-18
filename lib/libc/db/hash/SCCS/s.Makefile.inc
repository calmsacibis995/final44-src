h40945
s 00000/00000/00006
d D 8.1 93/06/04 15:21:30 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00001/00004
d D 5.2 91/09/04 12:56:16 bostic 2 1
c Rev #2.  ANSI/POSIX and reformatting, a few bug fixes thrown in
e
s 00005/00000/00000
d D 5.1 91/02/12 20:25:02 bostic 1 0
c date and time created 91/02/12 20:25:02 by bostic
e
u
U
t
T
I 1
#       %W% (Berkeley) %G%

.PATH: ${.CURDIR}/db/hash

D 2
SRCS+=  bigkey.c buf.c dynahash.c hfunc.c hsearch.c log2.c ndbm.c page.c
E 2
I 2
SRCS+=	hash.c hash_bigkey.c hash_buf.c hash_func.c hash_log2.c \
	hash_page.c hsearch.c ndbm.c
E 2
E 1
