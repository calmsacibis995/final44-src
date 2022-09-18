h20885
s 00002/00002/00056
d D 8.1 93/06/06 15:18:34 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00049
d D 1.8 90/04/09 18:27:21 bostic 8 7
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00001/00002/00050
d D 1.7 89/01/09 15:39:12 mckusick 7 6
c update from John Gilmore for gcc
e
s 00000/00002/00052
d D 1.6 83/10/28 17:22:20 mckusick 6 5
c semantic cleanup of UNSYNC()
e
s 00007/00008/00047
d D 1.5 81/06/10 00:43:58 mckusic 5 4
c move the text of error messages from ERROR to the functions
c which generate them.
e
s 00002/00003/00053
d D 1.4 81/03/07 16:00:38 mckusic 4 3
c merge in onyx changes
e
s 00001/00000/00055
d D 1.3 81/01/28 20:33:54 mckusic 3 2
c clear EOLN so that partial last lines can be detected
e
s 00008/00002/00047
d D 1.2 81/01/24 17:25:16 mckusic 2 1
c check for EOF after data read
e
s 00049/00000/00000
d D 1.1 80/10/30 00:34:44 mckusick 1 0
c date and time created 80/10/30 00:34:44 by mckusick
e
u
U
t
T
I 1
D 8
/* Copyright (c) 1979 Regents of the University of California */
E 8
I 8
/*-
D 9
 * Copyright (c) 1979 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1979, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * %sccs.include.redist.c%
 */
E 8

D 8
static char sccsid[] = "%Z%%M% %I% %G%";
E 8
I 8
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 8

#include "h00vars.h"
D 5
#include "h01errs.h"
E 5

I 4
long
E 4
READE(curfile, name)

	register struct iorec	*curfile;
	char			*name;
{
D 4
	long			data;

E 4
	register short	*sptr;
	register int	len;
	register int	nextlen;
	register int	cnt;
	char		*cp;
	char		namebuf[NAMSIZ];
I 2
	int		retval;
E 2

	if (curfile->funit & FWRITE) {
D 5
		ERROR(EREADIT, curfile->pfname);
E 5
I 5
		ERROR("%s: Attempt to read, but open for writing\n",
			curfile->pfname);
E 5
D 7
		return;
E 7
	}
	UNSYNC(curfile);
D 2
	if (fscanf(curfile->fbuf,
E 2
I 2
	retval = fscanf(curfile->fbuf,
E 2
	    "%*[ \t\n]%74[abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789]",
D 2
	    namebuf) == 0) {
E 2
I 2
	    namebuf);
	if (retval == EOF) {
D 5
		ERROR(EPASTEOF, curfile->pfname);
E 5
I 5
		ERROR("%s: Tried to read past end of file\n", curfile->pfname);
E 5
D 7
		return;
E 7
	}
D 5
	if (retval == 0) {
E 2
		ERROR(ENUMNTFD, namebuf);
		return;
	}
E 5
I 5
	if (retval == 0)
		goto ename;
E 5
I 3
D 6
	curfile->funit &= ~EOLN;
E 3
	curfile->funit |= SYNC;
E 6
	for (len = 0; len < NAMSIZ && namebuf[len]; len++)
		/* void */;
	len++;
	sptr = (short *)name;
	cnt = *sptr++;
	cp = name + sizeof (short) + *sptr;
	do	{
		nextlen = *sptr++;
		nextlen = *sptr - nextlen;
		if (nextlen == len && RELEQ(len, namebuf, cp)) {
			return *((short *) name) - cnt;
		}
D 4
		cp += nextlen;
E 4
I 4
		cp += (int)nextlen;
E 4
	} while (--cnt);
D 5
	ERROR(ENUMNTFD, namebuf);
E 5
I 5
ename:
	ERROR("Unknown name \"%s\" found on enumerated type read\n", namebuf);
I 7
	return 0;
E 7
E 5
}
E 1
