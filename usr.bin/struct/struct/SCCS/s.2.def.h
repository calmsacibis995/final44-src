h58458
s 00000/00000/00010
d D 8.1 93/06/06 16:29:19 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00001/00005
d D 4.3 91/04/16 16:48:38 bostic 3 2
c new copyright; att/bsd/shared
e
s 00002/00003/00004
d D 4.2 83/08/11 21:07:30 sam 2 1
c standardize sccs keyword lines
e
s 00007/00000/00000
d D 4.1 83/02/11 15:44:23 rrh 1 0
c date and time created 83/02/11 15:44:23 by rrh
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
extern int accessnum;		/* number of nodes accessible from START */
extern VERT *after;		/* node numbers associated with after numbers of depth first search */
extern int *ntobef;		/* before numbers associated with nodes */
extern int *ntoaft;		/* after numbers associated with nodes */
E 1
