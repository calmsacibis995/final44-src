h35447
s 00001/00001/00071
d D 8.3 94/04/02 10:07:06 pendry 8 7
c add 1994 copyright
e
s 00007/00006/00065
d D 8.2 94/04/01 07:42:23 pendry 7 6
c prettyness police
e
s 00002/00002/00069
d D 8.1 93/06/06 14:28:05 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00002/00064
d D 5.5 92/06/24 09:45:10 bostic 5 4
c delete MAP_FILE, check for file larger than a mappable size
e
s 00002/00002/00064
d D 5.4 92/06/21 13:37:58 bostic 4 3
c second arg to mmap is a size_t
e
s 00003/00003/00063
d D 5.3 92/06/21 13:35:18 bostic 3 2
c off_t is a quad, use %qd; 2nd arg to mmap is an int
e
s 00002/00002/00064
d D 5.2 91/11/16 18:59:39 bostic 2 1
c handle 0 length files
e
s 00066/00000/00000
d D 5.1 91/10/27 14:14:54 bostic 1 0
c date and time created 91/10/27 14:14:54 by bostic
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
D 8
 * Copyright (c) 1991, 1993
E 8
I 8
 * Copyright (c) 1991, 1993, 1994
E 8
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <sys/mman.h>
#include <sys/stat.h>
I 5

I 7
#include <err.h>
E 7
#include <limits.h>
E 5
D 7
#include <errno.h>
E 7
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
I 7

E 7
#include "extern.h"

void
c_regular(fd1, file1, skip1, len1, fd2, file2, skip2, len2)
	int fd1, fd2;
	char *file1, *file2;
	off_t skip1, len1, skip2, len2;
{
D 7
	register u_char ch, *p1, *p2;
	register off_t byte, length, line;
E 7
I 7
	u_char ch, *p1, *p2;
	off_t byte, length, line;
E 7
	int dfound;

	if (sflag && len1 != len2)
		exit(1);

D 2
	if (skip1 >= len1)
E 2
I 2
	if (skip1 > len1)
E 2
		eofmsg(file1);
	len1 -= skip1;
D 2
	if (skip2 >= len2)
E 2
I 2
	if (skip2 > len2)
E 2
		eofmsg(file2);
	len2 -= skip2;

	length = MIN(len1, len2);
I 5
	if (length > SIZE_T_MAX)
		return (c_special(fd1, file1, skip1, fd2, file2, skip2));

E 5
	if ((p1 = (u_char *)mmap(NULL,
D 3
	    length, PROT_READ, MAP_FILE, fd1, skip1)) == (u_char *)-1)
E 3
I 3
D 4
	    (int)length, PROT_READ, MAP_FILE, fd1, skip1)) == (u_char *)-1)
E 4
I 4
D 5
	    (size_t)length, PROT_READ, MAP_FILE, fd1, skip1)) == (u_char *)-1)
E 5
I 5
	    (size_t)length, PROT_READ, 0, fd1, skip1)) == (u_char *)-1)
E 5
E 4
E 3
D 7
		err("%s: %s", file1, strerror(errno));
E 7
I 7
		err(ERR_EXIT, "%s", file1);
E 7
	if ((p2 = (u_char *)mmap(NULL,
D 3
	    length, PROT_READ, MAP_FILE, fd2, skip2)) == (u_char *)-1)
E 3
I 3
D 4
	    (int)length, PROT_READ, MAP_FILE, fd2, skip2)) == (u_char *)-1)
E 4
I 4
D 5
	    (size_t)length, PROT_READ, MAP_FILE, fd2, skip2)) == (u_char *)-1)
E 5
I 5
	    (size_t)length, PROT_READ, 0, fd2, skip2)) == (u_char *)-1)
E 5
E 4
E 3
D 7
		err("%s: %s", file2, strerror(errno));
E 7
I 7
		err(ERR_EXIT, "%s", file2);
E 7

	dfound = 0;
	for (byte = line = 1; length--; ++p1, ++p2, ++byte) {
		if ((ch = *p1) != *p2)
			if (lflag) {
				dfound = 1;
D 3
				(void)printf("%6ld %3o %3o\n", byte, ch, *p2);
E 3
I 3
				(void)printf("%6qd %3o %3o\n", byte, ch, *p2);
E 3
			} else
				diffmsg(file1, file2, byte, line);
				/* NOTREACHED */
		if (ch == '\n')
			++line;
	}

	if (len1 != len2)
		eofmsg (len1 > len2 ? file2 : file1);
	if (dfound)
D 7
		exit(1);
E 7
I 7
		exit(DIFF_EXIT);
E 7
}
E 1
