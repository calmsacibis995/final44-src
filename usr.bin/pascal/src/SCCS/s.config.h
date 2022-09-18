h27856
s 00002/00002/00037
d D 8.1 93/06/06 16:08:06 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00033
d D 5.4 91/04/16 16:25:18 bostic 7 6
c new copyright; att/bsd/shared
e
s 00003/00003/00035
d D 5.3 91/04/01 09:08:02 bostic 6 5
c ANSI changes didn't quite work
e
s 00002/00002/00036
d D 5.2 91/03/07 13:36:08 donn 5 4
c Save 8 bytes and avoid writing constants.
e
s 00008/00002/00030
d D 5.1 85/06/05 15:43:11 dist 4 3
c Add copyright
e
s 00000/00000/00032
d D 2.1 84/02/08 20:49:04 aoki 3 2
c synchronize to version 2
e
s 00000/00000/00032
d D 1.2 83/09/19 07:08:23 thien 2 1
c changing to unlinted source
e
s 00032/00000/00000
d D 1.1 82/03/31 12:54:30 peter 1 0
c date and time created 82/03/31 12:54:30 by peter
e
u
U
t
T
I 4
D 7
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
/*-
D 8
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
E 7
 *
D 6
 *	%W% (Berkeley) %G%
E 6
I 6
D 7
 *	@(#)config.h	5.1 (Berkeley) 6/5/85
E 7
I 7
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
E 7
E 6
 */

E 4
I 1
    /*
     *	external declarations of things from 
     *		CONFIG.c
     *
     */
D 4

    /*	sccsid: %W% (Berkeley) %E% */
E 4

    /*
     *	the version of translator
     */
extern char	*version;

    /*
     *	the location of the error strings
     *	and the length of the path to it
     *	(in case of execution of pc0 as a.out)
     */
D 5
extern char	*err_file;
E 5
I 5
D 6
extern char	err_file[];
E 6
I 6
extern char	*err_file;
E 6
E 5
extern int	err_pathlen;

    /*
     *	the location of the short explanation
     *	and the length of the path to it
     *	the null at the end is so pix can change it to pi'x' from pi.
     */
D 5
extern char	*how_file;
E 5
I 5
D 6
extern char	how_file[];
E 6
I 6
extern char	*how_file;
E 6
E 5
extern int	how_pathlen;
extern char	*px_header;
extern char	*pi_comp;
extern char	*px_intrp;
extern char	*px_debug;
E 1
