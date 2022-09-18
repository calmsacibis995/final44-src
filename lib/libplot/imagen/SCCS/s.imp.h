h35594
s 00002/00002/00018
d D 8.1 93/06/04 17:44:49 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00004/00014
d D 5.3 91/04/22 15:55:15 bostic 3 2
c new copyright; att/bsd/shared
e
s 00002/00000/00016
d D 5.2 85/09/21 16:21:37 sam 2 1
c bring in most up to date code; removes hardcoded printer resolution; 
c adds 2 pixels to effective plotting resolution; parameterizes font and point size; 
c make linemod a hack to set font from plot file
e
s 00016/00000/00000
d D 5.1 85/09/21 15:05:45 sam 1 0
c date and time created 85/09/21 15:05:45 by sam
e
u
U
t
T
I 1
D 3
/*
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
D 4
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
E 3
 *
I 3
 * %sccs.include.proprietary.c%
 *
E 3
 *	%W% (Berkeley) %G%
 */

#include <stdio.h>
I 3

E 3
extern float obotx;
extern float boty;
extern float botx;
extern float oboty;
extern float scalex;
extern float scaley;
int imPx, imPy;
I 2
extern int imPcsize;
extern char *imP_charset;
E 2
E 1
