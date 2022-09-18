h43828
s 00002/00002/00050
d D 8.1 93/06/06 16:07:33 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00006/00045
d D 5.6 91/04/16 16:04:10 bostic 14 13
c new copyright; att/bsd/shared
e
s 00004/00003/00047
d D 5.5 91/04/01 09:08:01 bostic 13 12
c ANSI changes didn't quite work
e
s 00002/00002/00048
d D 5.4 91/03/07 13:35:34 donn 12 11
c Save 8 bytes and avoid writing constants.
e
s 00005/00005/00045
d D 5.3 90/06/29 11:45:44 bostic 11 10
c redo how pascal finds things.
e
s 00000/00000/00050
d D 5.2 89/05/09 15:49:43 kfall 10 9
c no change
e
s 00010/00004/00040
d D 5.1 85/06/04 11:32:59 dist 9 8
c Add copyright
e
s 00000/00000/00044
d D 2.7 84/02/08 20:48:57 aoki 8 7
c synchronize to version 2
e
s 00001/00001/00043
d D 2.6 84/02/08 12:05:44 aoki 7 6
c missing ifndef PXP
e
s 00000/00000/00044
d D 2.5 83/09/19 06:57:26 thien 6 5
c Restoring to unlinted version
e
s 00007/00000/00037
d D 2.4 83/08/19 04:54:55 thien 5 4
c The changes were made to allow successful linting
e
s 00002/00002/00035
d D 2.3 82/04/01 15:47:55 peter 4 3
c sizeof("...") returns the size including the trailing null.
e
s 00010/00005/00027
d D 2.2 82/04/01 13:51:31 peter 3 2
c version number and date come from makefile.
e
s 00000/00000/00032
d D 2.1 82/03/31 12:58:14 peter 2 1
c going to version 2.1 for the next distribution.
e
s 00032/00000/00000
d D 1.1 82/03/31 12:53:59 peter 1 0
c date and time created 82/03/31 12:53:59 by peter
e
u
U
t
T
I 9
D 14
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 14
I 14
/*-
D 15
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
 * %sccs.include.redist.c%
E 14
 */

#ifndef lint
D 13
static char sccsid[] = "%W% (Berkeley) %G%";
E 13
I 13
D 14
static char sccsid[] = "@(#)CONFIG.c	5.3 (Berkeley) 6/29/90";
E 13
#endif not lint
E 14
I 14
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 14

E 9
I 1
    /*
     *	make sure you are editing
     *		CONFIG.c
     *	editing config.c won't work
     */
D 9

I 5
#ifndef lint
E 5
static	char *sccsid = "%W% (Berkeley) %E%";
I 5
#endif
E 9
E 5

    /*
     *	the version of translator
     */
D 3
char	*version = "%I% (VERSION %G%)";
E 3
I 3
char	*version = "VERSION (DATE)";
E 3

    /*
     *	the location of the error strings
     *	and the length of the path to it
D 3
     *	(in case of execution of pc0 as a.out)
E 3
I 3
     *	(in case of execution as a.something)
E 3
     */
D 11
char	*err_file = "LIBDIR/ERRORSTRINGS";
D 4
int	err_pathlen = sizeof("LIBDIR/");
E 4
I 4
int	err_pathlen = sizeof("LIBDIR/")-1;
E 11
I 11
D 12
char	*err_file = "LIBDATA/ERRORSTRINGS";
E 12
I 12
D 13
char	err_file[] = "LIBDATA/ERRORSTRINGS";
E 13
I 13
char	*err_file = "LIBDATA/ERRORSTRINGS";
E 13
E 12
int	err_pathlen = sizeof("LIBDATA/")-1;
E 11
E 4

    /*
     *	the location of the short explanation
     *	and the length of the path to it
     *	the null at the end is so pix can change it to pi'x' from pi.
     */
D 11
char	*how_file = "LIBDIR/HOWFILE\0";
D 4
int	how_pathlen = sizeof("LIBDIR/");
E 4
I 4
int	how_pathlen = sizeof("LIBDIR/")-1;
E 11
I 11
D 12
char	*how_file = "LIBDATA/HOWFILE\0";
E 12
I 12
D 13
char	how_file[] = "LIBDATA/HOWFILE\0";
E 13
I 13
char	how_string[] = "LIBDATA/HOWFILE\0";
char	*how_file = how_string;
E 13
E 12
int	how_pathlen = sizeof("LIBDATA/")-1;
E 11
E 4
I 3
    
    /*
     *	things about the interpreter.
     *	these are not used by the compiler.
     */
I 5
#ifndef PC
E 5
E 3
D 11
char	*px_header = "LIBDIR/px_header";	/* px_header's name */
E 11
I 11
char	*px_header = "LIBEXEC/px_header";	/* px_header's name */
E 11
I 5
#endif

D 7
#ifdef PXP
E 7
I 7
#ifndef PXP
E 7
E 5
D 3
char	*pi_comp = "INTERPDIR/pi";		/* the compiler's name */
char	*px_intrp = "INTERPDIR/px";		/* the interpreter's name */
char	*px_debug = "INTERPDIR/pdx";		/* the debugger's name */
E 3
I 3
char	*pi_comp = "INSTALLDIR/pi";		/* the compiler's name */
char	*px_intrp = "INSTALLDIR/px";		/* the interpreter's name */
char	*px_debug = "INSTALLDIR/pdx";		/* the debugger's name */
I 5
#endif
E 5
E 3
E 1
