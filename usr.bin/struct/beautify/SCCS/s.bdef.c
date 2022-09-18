h51196
s 00000/00000/00012
d D 8.1 93/06/06 16:27:22 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00002/00006
d D 5.1 91/04/16 16:44:12 bostic 2 1
c new copyright; att/bsd/shared
e
s 00008/00000/00000
d D 4.1 83/02/11 15:45:02 rrh 1 0
c date and time created 83/02/11 15:45:02 by rrh
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
static char sccsid[] = "%W%	(Berkeley)	%G%";
#endif not lint
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

#define xxtop	100		/* max size of xxstack */
int xxindent, xxval, newflag, xxmaxchars, xxbpertab;
int xxlineno;		/* # of lines already output */
int xxstind, xxstack[xxtop], xxlablast, xxt;
E 1
