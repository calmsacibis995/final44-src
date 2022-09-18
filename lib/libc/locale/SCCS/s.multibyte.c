h24870
s 00079/00000/00000
d D 5.1 91/02/18 10:27:33 donn 1 0
c date and time created 91/02/18 10:27:33 by donn
e
u
U
t
T
I 1
/*
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <stdlib.h>

/*
 * Stub multibyte character functions.
 * These ignore the current fixed ("C") locale and
 * always indicate that no multibyte characters are supported.
 */

int
mblen(s, n)
	const char *s;
	size_t n;
{
	if (s && n && *s)
		return -1;
	return 0;
}

/*ARGSUSED*/
int
mbtowc(pwc, s, n)
	wchar_t *pwc;
	const char *s;
	size_t n;
{
	if (s && n && *s)
		return -1;
	return 0;
}

/*ARGSUSED*/
int
#ifdef __STDC__
wctomb(char *s, wchar_t wchar)
#else
wctomb(s, wchar)
	char *s;
	wchar_t wchar;
#endif
{
	if (s)
		return -1;
	return 0;
}

/*ARGSUSED*/
size_t
mbstowcs(pwcs, s, n)
	wchar_t *pwcs;
	const char *s;
	size_t n;
{
	if (s && n && *s)
		return -1;
	return 0;
}

/*ARGSUSED*/
size_t
wcstombs(s, pwcs, n)
	char *s;
	const wchar_t *pwcs;
	size_t n;
{
	if (pwcs && n && *pwcs)
		return -1;
	return 0;
}
E 1
