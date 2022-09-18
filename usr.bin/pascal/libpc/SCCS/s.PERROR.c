h33956
s 00002/00002/00029
d D 8.1 93/06/06 15:17:50 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00022
d D 1.3 90/04/09 18:27:02 bostic 3 2
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00001/00002/00023
d D 1.2 83/01/10 16:43:00 mckusick 2 1
c SETRACE() -> kill()
e
s 00025/00000/00000
d D 1.1 81/06/10 00:48:04 mckusick 1 0
c date and time created 81/06/10 00:48:04 by mckusick
e
u
U
t
T
I 1
D 3
/* Copyright (c) 1979 Regents of the University of California */
E 3
I 3
/*-
D 4
 * Copyright (c) 1979 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1979, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 */
E 3

D 3
static char sccsid[] = "%Z%%M% %I% %G%";
E 3
I 3
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

#include	<stdio.h>
#include	<signal.h>
D 2
#include	"h00vars.h"
E 2

/*
 * Routine PERROR is called from the runtime library when a runtime
 * I/O error occurs. Its arguments are a pointer to an error message and 
 * the name of the offending file.
 */
long
PERROR(msg, fname)

	char	*msg, *fname;
{
	PFLUSH();
	fputc('\n',stderr);
D 2
	SETRACE();
E 2
	fputs(msg, stderr);
	perror(fname);
I 2
	kill(getpid(), SIGTRAP);
E 2
	return 0;
}
E 1
