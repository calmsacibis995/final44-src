h52130
s 00002/00002/00069
d D 8.1 93/06/06 15:16:48 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00062
d D 1.6 90/04/09 18:26:36 bostic 7 6
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00004/00004/00060
d D 1.5 81/06/10 00:38:14 mckusic 6 5
c move the text of error messages from ERROR to the functions
c which generate them.
e
s 00001/00001/00063
d D 1.4 81/03/07 15:57:17 mckusic 5 4
c merge in onyx changes
e
s 00021/00012/00043
d D 1.3 81/01/26 12:36:19 mckusic 4 2
c append a newline to unterminated last lines when reading text files
e
s 00001/00000/00055
d R 1.3 81/01/24 16:38:48 mckusic 3 2
c prevent error when ``readln'' used on partial last line in file
e
s 00004/00000/00051
d D 1.2 81/01/24 15:13:31 mckusic 2 1
c set file^ to blank on eof (for text files)
e
s 00051/00000/00000
d D 1.1 80/10/30 00:33:36 mckusick 1 0
c date and time created 80/10/30 00:33:36 by mckusick
e
u
U
t
T
I 1
D 7
/* Copyright (c) 1979 Regents of the University of California */
E 7
I 7
/*-
D 8
 * Copyright (c) 1979 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1979, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * %sccs.include.redist.c%
 */
E 7

D 7
static char sccsid[] = "%Z%%M% %I% %G%";
E 7
I 7
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 7

#include "h00vars.h"
D 6
#include "h01errs.h"
E 6

/*
 * insure that a usable image is in the buffer window
 */
IOSYNC(curfile)

	register struct iorec	*curfile;
{
D 4
	register short		unit = curfile->funit;
E 4
	char			*limit, *ptr;

D 4
	if (unit & FWRITE) {
E 4
I 4
	if (curfile->funit & FWRITE) {
E 4
D 6
		ERROR(EREADIT, curfile->pfname);
E 6
I 6
		ERROR("%s: Attempt to read, but open for writing\n",
			curfile->pfname);
E 6
		return;
	}
D 4
	if ((unit & SYNC) == 0) {
E 4
I 4
	if ((curfile->funit & SYNC) == 0) {
E 4
		return;
	}
D 4
	if (unit & EOFF) {
E 4
I 4
	if (curfile->funit & EOFF) {
E 4
D 6
		ERROR(EPASTEOF, curfile->pfname);
E 6
I 6
		ERROR("%s: Tried to read past end of file\n", curfile->pfname);
E 6
		return;
	}
D 4
	unit &= ~SYNC;
E 4
I 4
	curfile->funit &= ~SYNC;
	if (curfile->funit & SPEOLN) {
		curfile->funit &= ~(SPEOLN|EOLN);
		curfile->funit |= EOFF;
		return;
	}
E 4
D 5
	fread(curfile->fileptr, curfile->fsize, 1, curfile->fbuf);
E 5
I 5
	fread(curfile->fileptr, (int)curfile->fsize, 1, curfile->fbuf);
E 5
	if (ferror(curfile->fbuf)) {
D 6
		ERROR(EPASTEOF, curfile->pfname);
E 6
I 6
		ERROR("%s: Tried to read past end of file\n", curfile->pfname);
E 6
		return;
	}
	if (feof(curfile->fbuf)) {
D 4
		curfile->funit = unit | EOFF;
I 2
		if (unit & FTEXT) {
E 4
I 4
		if (curfile->funit & FTEXT) {
E 4
			*curfile->fileptr = ' ';
I 4
			if (curfile->funit & EOLN) {
				curfile->funit &= ~EOLN;
				curfile->funit |= EOFF;
				return;
			}
			curfile->funit |= (SPEOLN|EOLN);
E 4
			return;
		}
I 4
		curfile->funit |= EOFF;
E 4
E 2
		limit = &curfile->fileptr[curfile->fsize];
		for (ptr = curfile->fileptr; ptr < limit; )
			*ptr++ = 0;
		return;
	}
D 4
	if (unit & FTEXT) {
E 4
I 4
	if (curfile->funit & FTEXT) {
E 4
		if (*curfile->fileptr == '\n') {
D 4
			unit |= EOLN;
E 4
I 4
			curfile->funit |= EOLN;
E 4
			*curfile->fileptr = ' ';
D 4
		} else {
			unit &= ~EOLN;
E 4
I 4
			return;
E 4
		}
I 4
		curfile->funit &= ~EOLN;
E 4
	}
D 4
	curfile->funit = unit;
E 4
}
E 1
