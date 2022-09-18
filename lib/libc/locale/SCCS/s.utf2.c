h06104
s 00002/00002/00120
d D 8.1 93/06/04 12:43:36 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00122/00000/00000
d D 5.1 93/05/26 20:28:35 bostic 1 0
c rune support from Paul Borman
c date and time created 93/05/26 20:28:35 by bostic
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

#include <errno.h>
#include <rune.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

rune_t	_UTF2_sgetrune __P((const char *, size_t, char const **));
int	_UTF2_sputrune __P((rune_t, char *, size_t, char **));

static _utf_count[16] = {
	1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 2, 2, 3, 0,
};

int
_UTF2_init(rl)
	_RuneLocale *rl;
{
	rl->sgetrune = _UTF2_sgetrune;
	rl->sputrune = _UTF2_sputrune;
	_CurrentRuneLocale = rl;
	__mb_cur_max = 3;
	return (0);
}

rune_t
_UTF2_sgetrune(string, n, result)
	const char *string;
	size_t n;
	char const **result;
{
	int c;

	if (n < 1 || (c = _utf_count[(*string >> 4) & 0xf]) > n) {
		if (result)
			*result = string;
		return (_INVALID_RUNE);
	}
	switch (c) {
	case 1:
		if (result)
			*result = string + 1;
		return (*string & 0xff);
	case 2:
		if ((string[1] & 0xC0) != 0x80)
			goto encoding_error;
		if (result)
			*result = string + 2;
		return (((string[0] & 0x1F) << 6) | (string[1] & 0x3F));
	case 3:
		if ((string[1] & 0xC0) != 0x80 || (string[2] & 0xC0) != 0x80)
			goto encoding_error;
		if (result)
			*result = string + 3;
		return (((string[0] & 0x1F) << 12) | ((string[1] & 0x3F) << 6)
		    | (string[2] & 0x3F));
	default:
encoding_error:	if (result)
			*result = string + 1;
		return (_INVALID_RUNE);
	}
}

int
_UTF2_sputrune(c, string, n, result)
	rune_t c;
	char *string, **result;
	size_t n;
{
	if (c & 0xF800) {
		if (n >= 3) {
			if (string) {
				string[0] = 0xE0 | ((c >> 12) & 0x0F);
				string[1] = 0x80 | ((c >> 6) & 0x3F);
				string[2] = 0x80 | ((c) & 0x3F);
			}
			if (result)
				*result = string + 3;
		} else
			if (result)
				*result = NULL;

		return (3);
	} else
		if (c & 0x0780) {
			if (n >= 2) {
				if (string) {
					string[0] = 0xC0 | ((c >> 6) & 0x1F);
					string[1] = 0x80 | ((c) & 0x3F);
				}
				if (result)
					*result = string + 2;
			} else
				if (result)
					*result = NULL;
			return (2);
		} else {
			if (n >= 1) {
				if (string)
					string[0] = c;
				if (result)
					*result = string + 1;
			} else
				if (result)
					*result = NULL;
			return (1);
		}
}
E 1
