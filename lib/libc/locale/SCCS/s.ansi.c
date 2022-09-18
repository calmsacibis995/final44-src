h49001
s 00002/00002/00120
d D 8.1 93/06/27 19:22:32 bostic 4 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00120
d R 8.1 93/06/04 12:42:49 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00121
d D 5.2 93/05/27 13:17:18 bostic 2 1
c initialize cnt
e
s 00122/00000/00000
d D 5.1 93/05/26 20:28:30 bostic 1 0
c rune support from Paul Borman
c date and time created 93/05/26 20:28:30 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Paul Borman at Krystal Technologies.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <stdlib.h>
#include <limits.h>
#include <stddef.h>
#include <rune.h>

int
mblen(s, n)
	const char *s;
	size_t n;
{
	char const *e;

	if (s == 0 || *s == 0)
		return (0);	/* No support for state dependent encodings. */

	if (sgetrune(s, (int)n, &e) == _INVALID_RUNE)
		return (s - e);
	return (e - s);
}

int
mbtowc(pwc, s, n)
	wchar_t *pwc;
	const char *s;
	size_t n;
{
	char const *e;
	rune_t r;

	if (s == 0 || *s == 0)
		return (0);	/* No support for state dependent encodings. */

	if ((r = sgetrune(s, (int)n, &e)) == _INVALID_RUNE)
		return (s - e);
	if (pwc)
		*pwc = r;
	return (e - s);
}

int
wctomb(s, wchar)
	char *s;
	wchar_t wchar;
{
	char *e;

	if (s == 0)
		return (0);	/* No support for state dependent encodings. */

	if (wchar == 0) {
		*s = 0;
		return (1);
	}

	sputrune(wchar, s, MB_CUR_MAX, &e);
	return (e ? e - s : -1);
}

size_t
mbstowcs(pwcs, s, n)
	wchar_t *pwcs;
	const char *s;
	size_t n;
{
	char const *e;
	int cnt = 0;

	if (!pwcs || !s)
		return (-1);

	while (n-- > 0) {
		*pwcs = sgetrune(s, MB_LEN_MAX, &e);
		if (*pwcs == _INVALID_RUNE)
			return (-1);
		if (*pwcs++ == 0)
			break;
		s = e;
		++cnt;
	}
	return (cnt);
}

size_t
wcstombs(s, pwcs, n)
	char *s;
	const wchar_t *pwcs;
	size_t n;
{
	char *e;
D 2
	int cnt;
E 2
I 2
	int cnt = 0;
E 2

	if (!pwcs || !s)
		return (-1);

	while (n > 0) {
		if (*pwcs == 0) {
			*s = 0;
			break;
		}
		if (!sputrune(*pwcs++, s, (int)n, &e))
			return (-1);		/* encoding error */
		if (!e)			/* too long */
			return (cnt);
		cnt += e - s;
		s = e;
	}
	return (cnt);
}
E 1
