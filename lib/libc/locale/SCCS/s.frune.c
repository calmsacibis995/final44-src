h56063
s 00002/00002/00075
d D 8.1 93/06/04 12:43:01 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00077/00000/00000
d D 5.1 93/05/26 20:28:31 bostic 1 0
c rune support from Paul Borman
c date and time created 93/05/26 20:28:31 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Paul Borman at Krystal Technologies.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <limits.h>
#include <rune.h>
#include <stddef.h>
#include <stdio.h>

long
fgetrune(fp)
	FILE *fp;
{
	rune_t  r;
	int c, len;
	char buf[MB_LEN_MAX];
	char const *result;

	len = 0;
	do {
		if ((c = getc(fp)) == EOF) {
			if (len)
				break;
			return (EOF);
		}
		buf[len++] = c;

		if ((r = sgetrune(buf, len, &result)) != _INVALID_RUNE)
			return (r);
	} while (result == buf && len < MB_LEN_MAX);

	while (--len > 0)
		ungetc(buf[len], fp);
	return (_INVALID_RUNE);
}

int
fungetrune(r, fp)
	rune_t r;
	FILE* fp;
{
	int len;
	char buf[MB_LEN_MAX];

	len = sputrune(r, buf, MB_LEN_MAX, 0);
	while (len-- > 0)
		if (ungetc(buf[len], fp) == EOF)
			return (EOF);
	return (0);
}

int
fputrune(r, fp)
	rune_t r;
	FILE *fp;
{
	int i, len;
	char buf[MB_LEN_MAX];

	len = sputrune(r, buf, MB_LEN_MAX, 0);

	for (i = 0; i < len; ++i)
		if (putc(buf[i], fp) == EOF)
			return (EOF);

	return (0);
}
E 1
