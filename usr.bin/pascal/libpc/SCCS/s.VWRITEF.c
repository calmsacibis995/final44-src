h37499
s 00002/00002/00032
d D 8.1 93/06/06 15:20:27 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00025
d D 1.3 90/04/09 18:28:07 bostic 3 2
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00000/00004/00027
d D 1.2 89/01/11 15:09:28 mckusick 2 1
c update to use <stdarg.h>
e
s 00031/00000/00000
d D 1.1 89/01/09 15:34:28 mckusick 1 0
c from John Gilmore to support gcc
e
u
U
t
T
I 1
D 3
/* Copyright (c) 1989 Regents of the University of California */
E 3
I 3
/*-
D 4
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1989, 1993
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

#include "h00vars.h"

D 2
#ifdef notdef
E 2
#include <stdarg.h>
D 2
#else
typedef char *va_list;
#endif
E 2

VWRITEF(curfile, file, format, args)

	register struct iorec	*curfile;
	FILE			*file;
	char 			*format;
	va_list			args;
{

	if (curfile->funit & FREAD) {
		ERROR("%s: Attempt to write, but open for reading\n",
			curfile->pfname);
		return;
	}
	vfprintf(file, format, args);
	if (ferror(curfile->fbuf)) {
		PERROR("Could not write to ", curfile->pfname);
		return;
	}
}
E 1
