h64917
s 00008/00001/00029
d D 4.3 91/04/18 16:49:26 bostic 3 2
c new copyright; att/bsd/shared
e
s 00002/00003/00028
d D 4.2 83/08/11 21:26:40 sam 2 1
c standardize sccs keyword lines
e
s 00031/00000/00000
d D 4.1 82/06/07 15:44:57 rrh 1 0
c date and time created 82/06/07 15:44:57 by rrh
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
/* typewriter driving table structure*/
struct {
	int bset;
	int breset;
	int Hor;
	int Vert;
	int Newline;
	int Char;
	int Em;
	int Halfline;
	int Adj;
	char *twinit;
	char *twrest;
	char *twnl;
	char *hlr;
	char *hlf;
	char *flr;
	char *bdon;
	char *bdoff;
	char *ploton;
	char *plotoff;
	char *up;
	char *down;
	char *right;
	char *left;
	char *codetab[256-32];
	char *zzz;
	} t;
E 1
