h58783
s 00000/00000/00016
d D 8.1 93/06/06 16:27:21 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00001/00011
d D 5.1 91/04/16 16:44:10 bostic 3 2
c new copyright; att/bsd/shared
e
s 00002/00003/00010
d D 4.2 83/08/11 21:07:44 sam 2 1
c standardize sccs keyword lines
e
s 00013/00000/00000
d D 4.1 83/02/11 15:44:59 rrh 1 0
c date and time created 83/02/11 15:44:59 by rrh
e
u
U
t
T
I 1
D 2
/*
 *	%W%	(Berkeley)	%E%
 */
E 2
I 2
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
/*-
 * %sccs.include.proprietary.c%
 *
 *	%W% (Berkeley) %G%
 */
E 3

E 2
extern int xxindent, xxval, newflag, xxmaxchars, xxbpertab;
extern int xxlineno;		/* # of lines already output */
#define xxtop	100		/* max size of xxstack */
extern int xxstind, xxstack[xxtop], xxlablast, xxt;
struct node
	{int op;
	char *lit;
	struct node *left;
	struct node *right;
	};
E 1
