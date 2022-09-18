h41311
s 00001/00001/00072
d D 8.3 94/04/02 10:07:14 pendry 5 4
c add 1994 copyright
e
s 00011/00009/00062
d D 8.2 94/04/01 07:42:09 pendry 4 3
c fix error message.
c prettyness police
e
s 00002/00002/00069
d D 8.1 93/06/06 14:28:08 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00070
d D 5.2 92/06/21 13:35:19 bostic 2 1
c off_t is a quad, use %qd; 2nd arg to mmap is an int
e
s 00071/00000/00000
d D 5.1 91/10/27 14:14:57 bostic 1 0
c date and time created 91/10/27 14:14:57 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
D 5
 * Copyright (c) 1991, 1993
E 5
I 5
 * Copyright (c) 1991, 1993, 1994
E 5
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
D 4
#include <errno.h>
E 4
I 4

#include <err.h>
E 4
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
I 4

E 4
#include "extern.h"

void
c_special(fd1, file1, skip1, fd2, file2, skip2)
	int fd1, fd2;
	char *file1, *file2;
D 4
	register off_t skip1, skip2;
E 4
I 4
	off_t skip1, skip2;
E 4
{
D 4
	register int ch1, ch2;
	register off_t byte, line;
E 4
I 4
	int ch1, ch2;
	off_t byte, line;
E 4
	FILE *fp1, *fp2;
	int dfound;

	if ((fp1 = fdopen(fd1, "r")) == NULL)
D 4
		err("%s: %s", file1, strerror(errno));
E 4
I 4
		err(ERR_EXIT, "%s", file1);
E 4
	if ((fp2 = fdopen(fd2, "r")) == NULL)
D 4
		err("%s: %s", file1, strerror(errno));
E 4
I 4
		err(ERR_EXIT, "%s", file2);
E 4

	while (skip1--)
		if (getc(fp1) == EOF)
			goto eof;
	while (skip2--)
		if (getc(fp2) == EOF)
			goto eof;

	dfound = 0;
	for (byte = line = 1;; ++byte) {
		ch1 = getc(fp1);
		ch2 = getc(fp2);
		if (ch1 == EOF || ch2 == EOF)
			break;
		if (ch1 != ch2)
			if (lflag) {
				dfound = 1;
D 2
				(void)printf("%6ld %3o %3o\n", byte, ch1, ch2);
E 2
I 2
				(void)printf("%6qd %3o %3o\n", byte, ch1, ch2);
E 2
			} else
				diffmsg(file1, file2, byte, line);
				/* NOTREACHED */
		if (ch1 == '\n')
			++line;
	}

eof:	if (ferror(fp1))
D 4
		err("%s: %s", file1, strerror(errno));
E 4
I 4
		err(ERR_EXIT, "%s", file1);
E 4
	if (ferror(fp2))
D 4
		err("%s: %s", file2, strerror(errno));
E 4
I 4
		err(ERR_EXIT, "%s", file2);
E 4
	if (feof(fp1)) {
		if (!feof(fp2))
			eofmsg(file1);
	} else
		if (feof(fp2))
			eofmsg(file2);
	if (dfound)
D 4
		exit(1);
E 4
I 4
		exit(DIFF_EXIT);
E 4
}
E 1
