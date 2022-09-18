h20349
s 00008/00008/00064
d D 8.2 94/08/05 16:42:18 mckusick 7 6
c inline => __inline (from cgd)
e
s 00002/00002/00070
d D 8.1 93/06/10 22:07:35 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00071
d D 7.5 92/11/17 13:45:16 bostic 5 4
c add rindex()
e
s 00049/00009/00022
d D 7.4 92/07/12 20:10:05 bostic 4 3
c make the min/max functions inlines
e
s 00001/00000/00030
d D 7.3 92/06/24 01:09:51 torek 3 2
c add random(); note, this is not the libc random
e
s 00013/00003/00017
d D 7.2 92/06/21 10:33:10 bostic 2 1
c add the rest of the routines to libkern.h; use it in kernel source
e
s 00017/00000/00000
d D 7.1 92/06/21 10:22:06 bostic 1 0
c date and time created 92/06/21 10:22:06 by bostic
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 2
#include <sys/types.h>

E 2
D 4
/* Prototypes for non-quad routines. */
E 4
I 4
D 7
static inline int
E 7
I 7
static __inline int
E 7
imax(a, b)
	int a, b;
{
	return (a > b ? a : b);
}
D 7
static inline int
E 7
I 7
static __inline int
E 7
imin(a, b)
	int a, b;
{
	return (a < b ? a : b);
}
D 7
static inline long
E 7
I 7
static __inline long
E 7
lmax(a, b)
	long a, b;
{
	return (a > b ? a : b);
}
D 7
static inline long
E 7
I 7
static __inline long
E 7
lmin(a, b)
	long a, b;
{
	return (a < b ? a : b);
}
D 7
static inline u_int
E 7
I 7
static __inline u_int
E 7
max(a, b)
	u_int a, b;
{
	return (a > b ? a : b);
}
D 7
static inline u_int
E 7
I 7
static __inline u_int
E 7
min(a, b)
	u_int a, b;
{
	return (a < b ? a : b);
}
D 7
static inline u_long
E 7
I 7
static __inline u_long
E 7
ulmax(a, b)
	u_long a, b;
{
	return (a > b ? a : b);
}
D 7
static inline u_long
E 7
I 7
static __inline u_long
E 7
ulmin(a, b)
	u_long a, b;
{
	return (a < b ? a : b);
}
E 4

I 4
/* Prototypes for non-quad routines. */
E 4
int	 bcmp __P((const void *, const void *, size_t));
int	 ffs __P((int));
D 2
int	 locc __P((int mask, char *cp, unsigned size));
int	 scanc __P((unsigned size, u_char *cp, u_char *table, int mask));
int	 skpc __P((int mask, int size, char *cp));
E 2
I 2
D 4
int	 imax __P((int, int));
int	 imin __P((int, int));
long	 lmax __P((long, long));
long	 lmin __P((long, long));
E 4
int	 locc __P((int, char *, u_int));
D 4
u_int	 max __P((u_int, u_int));
u_int	 min __P((u_int, u_int));
E 4
I 3
u_long	 random __P((void));
I 5
char	*rindex __P((const char *, int));
E 5
E 3
int	 scanc __P((u_int, u_char *, u_char *, int));
int	 skpc __P((int, int, char *));
E 2
char	*strcat __P((char *, const char *));
char	*strcpy __P((char *, const char *));
size_t	 strlen __P((const char *));
char	*strncpy __P((char *, const char *, size_t));
I 2
D 4
u_long	 ulmax __P((u_long, u_long));
u_long	 ulmin __P((u_long, u_long));
E 4
E 2
E 1
