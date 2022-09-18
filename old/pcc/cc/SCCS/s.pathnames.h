h21983
s 00001/00001/00020
d D 5.7 91/11/14 10:22:21 bostic 7 6
c mv ld to /usr/old/bin
e
s 00005/00005/00016
d D 5.6 91/02/01 12:07:27 bostic 6 5
c move to /usr/old
e
s 00001/00011/00020
d D 5.5 90/06/01 15:57:45 bostic 5 4
c new copyright notice
e
s 00003/00003/00028
d D 5.4 90/05/12 15:37:56 bostic 4 3
c move crt files to /usr/lib
e
s 00011/00009/00020
d D 5.3 89/05/10 22:19:09 bostic 3 2
c file reorg, pathnames.h paths.h
c rip out `standard backup' directory
e
s 00010/00007/00019
d D 5.2 89/04/02 11:54:08 bostic 2 1
c missed a few paths
e
s 00026/00000/00000
d D 5.1 89/03/05 21:16:46 bostic 1 0
c date and time created 89/03/05 21:16:46 by bostic
e
u
U
t
T
I 1
/*
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
D 5
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
 * %sccs.include.redist.c%
E 5
 *
 *	%W% (Berkeley) %G%
 */

D 2
#define	_PATH_AS	"/bin/as";
#define	_PATH_C2	"/lib/c2";
#define	_PATH_CCOM	"/lib/ccom";
#define	_PATH_CPP	"/lib/cpp";
#define	_PATH_CRT0	"/lib/crt0.o";
#define	_PATH_LD	"/bin/ld";
#define	_PATH_SCCOM	"/lib/sccom";
E 2
I 2
D 3
#define	_PATH_AS	"/bin/as"
#define	_PATH_C2	"/lib/c2"
#define	_PATH_CCOM	"/lib/ccom"
#define	_PATH_CPP	"/lib/cpp"
#define	_PATH_CRT0	"/lib/crt0.o"
#define	_PATH_GCRT0	"/usr/lib/gcrt0.o"
#define	_PATH_LD	"/bin/ld"
#define	_PATH_MCRT0	"/lib/mcrt0.o"
#define	_PATH_SCCOM	"/lib/sccom"
E 3
I 3
#include <paths.h>

D 6
#define	_PATH_AS	"/usr/bin/as"
#define	_PATH_C2	"/usr/libexec/c2"
#define	_PATH_CCOM	"/usr/libexec/ccom"
#define	_PATH_CPP	"/usr/bin/cpp"
E 6
I 6
#define	_PATH_AS	"/usr/old/bin/as"
#define	_PATH_C2	"/usr/old/libexec/c2"
#define	_PATH_CCOM	"/usr/old/libexec/ccom"
#define	_PATH_CPP	"/usr/old/bin/cpp"
E 6
D 4
#define	_PATH_CRT0	"/usr/libexec/crt0.o"
#define	_PATH_GCRT0	"/usr/libexec/gcrt0.o"
E 4
I 4
#define	_PATH_CRT0	"/usr/lib/crt0.o"
#define	_PATH_GCRT0	"/usr/lib/gcrt0.o"
E 4
D 7
#define	_PATH_LD	"/usr/bin/ld"
E 7
I 7
#define	_PATH_LD	"/usr/old/bin/ld"
E 7
D 4
#define	_PATH_MCRT0	"/usr/libexec/mcrt0.o"
E 4
I 4
#define	_PATH_MCRT0	"/usr/lib/mcrt0.o"
E 4
D 6
#define	_PATH_SCCOM	"/usr/libexec/sccom"
E 6
I 6
#define	_PATH_SCCOM	"/usr/old/libexec/sccom"
E 6
E 3
#define	_PATH_USRNEW	"/usr/new"
E 2
E 1
