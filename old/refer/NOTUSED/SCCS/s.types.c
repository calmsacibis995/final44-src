h46763
s 00006/00002/00016
d D 4.2 91/04/18 16:33:12 bostic 2 1
c new copyright; att/bsd/shared
e
s 00018/00000/00000
d D 4.1 83/05/06 23:50:10 tut 1 0
c date and time created 83/05/06 23:50:10 by tut
e
u
U
t
T
I 2
/*-
 * %sccs.include.proprietary.c%
 */

E 2
I 1
#ifndef lint
D 2
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

#if LONG
# define ptr long
# define uptr long
# define getp getl
# define putp putl
# define MONE -1L
extern long getl();
#else
# define ptr int
# define uptr unsigned
# define getp getw
# define putp putw
# define MONE -1
#endif
E 1
