h26749
s 00002/00002/00051
d D 8.1 93/06/06 15:19:14 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00044
d D 1.9 90/04/09 18:27:42 bostic 9 8
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00001/00001/00045
d D 1.8 86/02/19 01:18:03 lepreau 8 7
c make work with new fseek (and old one too, going to put it back)
e
s 00002/00002/00044
d D 1.7 82/07/23 15:09:43 mckusick 7 6
c fix initialization of "input" file
e
s 00007/00000/00039
d D 1.6 82/02/08 20:21:51 mckusic 6 5
c make it an error to reset a temporary file that has not been rewritten first
e
s 00002/00000/00037
d D 1.5 81/11/22 16:43:29 mckusic 5 4
c zero length text files do not get a pseudo-newline appended to them.
e
s 00002/00003/00035
d D 1.4 81/06/10 00:44:08 mckusic 4 3
c move the text of error messages from ERROR to the functions
c which generate them.
e
s 00001/00001/00037
d D 1.3 81/05/07 19:09:14 mckusic 3 2
c change rewind to fseek(file, 0, 0)
e
s 00002/00002/00036
d D 1.2 81/03/07 16:02:36 mckusic 2 1
c merge in onyx changes
e
s 00038/00000/00000
d D 1.1 80/10/30 00:35:23 mckusick 1 0
c date and time created 80/10/30 00:35:23 by mckusick
e
u
U
t
T
I 1
D 9
/* Copyright (c) 1979 Regents of the University of California */
E 9
I 9
/*-
D 10
 * Copyright (c) 1979 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1979, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * %sccs.include.redist.c%
 */
E 9

D 9
static char sccsid[] = "%Z%%M% %I% %G%";
E 9
I 9
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 9

#include "h00vars.h"
D 4
#include "h01errs.h"
E 4

RESET(filep, name, maxnamlen, datasize)

	register struct iorec	*filep;
	char			*name;
D 2
	int			maxnamlen;
	int			datasize;
E 2
I 2
	long			maxnamlen;
	long			datasize;
E 2
{
	if (name == NULL && filep == INPUT && filep->fname[0] == '\0') {
D 3
		if (rewind(filep->fbuf)) {
E 3
I 3
D 8
		if (fseek(filep->fbuf, (long)0, 0)) {
E 8
I 8
		if (fseek(filep->fbuf, (long)0, 0) == -1) {
E 8
E 3
D 4
			ERROR(ESEEK, filep->pfname);
E 4
I 4
			PERROR("Could not reset ", filep->pfname);
E 4
			return;
		}
D 7
		filep->funit &= ~(EOFF | EOLN);
		filep->funit |= SYNC;
E 7
I 7
		filep->funit &= ~EOFF;
		filep->funit |= (SYNC | EOLN);
E 7
		return;
	}
	filep = GETNAME(filep, name, maxnamlen, datasize);
	filep->fbuf = fopen(filep->fname, "r");
	if (filep->fbuf == NULL) {
I 6
		/*
		 * This allows unnamed temp files to be opened even if
		 * they have not been rewritten yet. We decided to remove
		 * this feature since the standard requires that files be
		 * defined before being reset.
		 *
E 6
		if (filep->funit & TEMP) {
			filep->funit |= (EOFF | SYNC | FREAD);
			return;
		}
I 6
		 */
E 6
D 4
		ERROR(EOPEN, filep->pfname);
E 4
I 4
		PERROR("Could not open ", filep->pfname);
E 4
		return;
	}
	filep->funit |= (SYNC | FREAD);
I 5
	if (filep->funit & FTEXT)
		filep->funit |= EOLN;
E 5
	if (filep->fblk > PREDEF) {
		setbuf(filep->fbuf, &filep->buf[0]);
	}
}
E 1
