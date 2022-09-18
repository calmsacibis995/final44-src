h11471
s 00002/00002/00042
d D 8.1 93/06/06 15:18:22 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00035
d D 1.10 90/04/09 18:27:16 bostic 10 9
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00000/00005/00037
d D 1.9 89/01/09 15:39:02 mckusick 9 8
c update from John Gilmore for gcc
e
s 00000/00002/00042
d D 1.8 83/10/28 17:22:16 mckusick 8 7
c semantic cleanup of UNSYNC()
e
s 00001/00001/00043
d D 1.7 83/10/01 01:19:27 mckusick 7 6
c PERROR is missing an argument
e
s 00011/00000/00033
d D 1.6 82/04/09 15:28:51 mckusick 6 5
c put in checking for overflow/underflow
e
s 00004/00004/00029
d D 1.5 81/06/10 00:43:48 mckusic 5 4
c move the text of error messages from ERROR to the functions
c which generate them.
e
s 00003/00001/00030
d D 1.4 81/03/07 16:00:26 mckusic 4 3
c merge in onyx changes
e
s 00001/00000/00030
d D 1.3 81/01/28 20:33:46 mckusic 3 2
c clear EOLN so that partial last lines can be detected
e
s 00007/00002/00023
d D 1.2 81/01/24 17:25:06 mckusic 2 1
c check for EOF after data read
e
s 00025/00000/00000
d D 1.1 80/10/30 00:34:38 mckusick 1 0
c date and time created 80/10/30 00:34:38 by mckusick
e
u
U
t
T
I 1
D 10
/* Copyright (c) 1979 Regents of the University of California */
E 10
I 10
/*-
D 11
 * Copyright (c) 1979 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1979, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * %sccs.include.redist.c%
 */
E 10

D 10
static char sccsid[] = "%Z%%M% %I% %G%";
E 10
I 10
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 10

#include "h00vars.h"
I 6
#include <errno.h>
extern int errno;
E 6
D 5
#include "h01errs.h"
E 5

I 4
long
E 4
READ4(curfile)

	register struct iorec	*curfile;
{
D 2
	int			data;
E 2
I 2
D 4
	int			data, retval;
E 4
I 4
	long			data;
	int			retval;
E 4
E 2

	if (curfile->funit & FWRITE) {
D 5
		ERROR(EREADIT, curfile->pfname);
E 5
I 5
		ERROR("%s: Attempt to read, but open for writing\n",
			curfile->pfname);
E 5
D 9
		return;
E 9
	}
	UNSYNC(curfile);
I 6
	errno = 0;
E 6
D 2
	if (fscanf(curfile->fbuf, "%ld", &data) == 0) {
E 2
I 2
	retval = fscanf(curfile->fbuf, "%ld", &data);
	if (retval == EOF) {
D 5
		ERROR(EPASTEOF, curfile->pfname);
E 5
I 5
		ERROR("%s: Tried to read past end of file\n", curfile->pfname);
E 5
D 9
		return;
E 9
	}
	if (retval == 0) {
E 2
D 5
		ERROR(EBADINUM, curfile->pfname);
E 5
I 5
		ERROR("%s: Bad data found on integer read\n", curfile->pfname);
I 6
D 9
		return;
E 9
	}
	if (errno == ERANGE) {
		ERROR("%s: Overflow on integer read\n", curfile->pfname);
D 9
		return;
E 9
	}
	if (errno != 0) {
D 7
		PERROR(curfile->pfname);
E 7
I 7
		PERROR("Error encountered on integer read ", curfile->pfname);
E 7
E 6
E 5
D 9
		return;
E 9
	}
I 3
D 8
	curfile->funit &= ~EOLN;
E 3
	curfile->funit |= SYNC;
E 8
	return data;
}
E 1
