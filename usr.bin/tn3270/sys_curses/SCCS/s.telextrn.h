h28387
s 00002/00002/00043
d D 8.1 93/06/06 16:52:58 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00045
d D 4.3 93/05/11 10:04:35 bostic 4 3
c make tn3270 compile again
e
s 00009/00000/00037
d D 4.2 91/04/26 16:09:07 bostic 3 2
c new copyright; att/bsd/shared
e
s 00000/00000/00037
d D 4.1 88/12/04 15:33:27 minshall 2 1
c Release 4.1
e
s 00037/00000/00000
d D 1.1 88/12/04 15:24:12 minshall 1 0
c date and time created 88/12/04 15:24:12 by minshall
e
u
U
t
T
I 3
/*-
D 5
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 3
I 1
/*
 * Definitions of external routines and variables for tn3270
 */

/*
 * Pieces exported from the telnet susbsection.
 */

extern int
#if defined(unix)
	HaveInput,
#endif /* defined(unix) */
	tout,
	tin;

extern char	*transcom;

extern int
	netflush(),
	quit(),
	TtyChars(),
	DataToTerminal();

extern void
	outputPurge(),
	EmptyTerminal(),
	StringToTerminal(),
D 4
	_putchar(),
E 4
	ExitPerror(),
	setcommandmode();

/*
 * Pieces exported from other random locations.
 */

extern char
	*strsave();
E 1
