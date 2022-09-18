h43279
s 00008/00001/00003
d D 4.3 91/04/18 16:49:11 bostic 3 2
c new copyright; att/bsd/shared
e
s 00002/00003/00002
d D 4.2 83/08/11 21:26:26 sam 2 1
c standardize sccs keyword lines
e
s 00005/00000/00000
d D 4.1 82/06/07 15:44:51 rrh 1 0
c date and time created 82/06/07 15:44:51 by rrh
e
u
U
t
T
I 1
D 2
/*
 *	%W% %G%
 */
E 2
I 2
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 *
 *	%W% (Berkeley) %G%
 */
E 3

E 2
struct d {filep op; int dnl,dimac,ditrap,ditf,alss,blss,nls,mkline,
		maxl,hnl,curd;} d[NDI], *dip;
E 1
