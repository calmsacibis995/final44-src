h52380
s 00002/00002/00264
d D 8.1 93/06/04 15:12:00 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00003/00264
d D 5.13 92/10/04 16:45:26 bostic 13 12
c litn
e
s 00010/00008/00257
d D 5.12 92/10/04 13:09:06 bostic 12 11
c lint
e
s 00004/00003/00261
d D 5.11 91/02/24 13:57:54 bostic 11 10
c Add include files to get prototype declarations, and fix bugs found.
e
s 00004/00001/00260
d D 5.10 90/12/04 20:16:12 bostic 10 9
c make a copy, mktime.3 modifies the tm struct
e
s 00022/00004/00239
d D 5.9 90/11/30 12:44:02 bostic 9 8
c add %s for number of seconds since the Epoch
e
s 00001/00011/00242
d D 5.8 90/06/01 14:46:17 bostic 8 7
c new copyright notice
e
s 00001/00000/00252
d D 5.7 90/05/17 12:05:42 bostic 7 6
c keep string.h and source in sync
e
s 00033/00015/00219
d D 5.6 89/04/09 21:58:49 bostic 6 5
c add Sun flags to correct deficiencies in X3J11 spec
e
s 00002/00002/00232
d D 5.5 89/04/09 21:41:33 bostic 5 4
c do it the way Sun did it, I think it's right for S5, too (sigh)
e
s 00001/00001/00232
d D 5.4 89/03/14 13:44:44 bostic 4 3
c if %x changes, %c has to too
e
s 00019/00009/00214
d D 5.3 89/03/14 13:39:49 bostic 3 2
c check before indirection, several format bug fixes, minor cleanups
e
s 00026/00004/00197
d D 5.2 89/03/12 13:03:52 bostic 2 1
c add System V/P1003.2 formats
e
s 00201/00000/00000
d D 5.1 89/03/08 16:04:05 bostic 1 0
c date and time created 89/03/08 16:04:05 by bostic
e
u
U
t
T
I 1
/*
D 14
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
D 8
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 8
I 8
 * %sccs.include.redist.c%
E 8
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
#include <sys/time.h>
#include <tzfile.h>
I 7
#include <string.h>
E 7

static char *afmt[] = {
	"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat",
};
static char *Afmt[] = {
	"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",
	"Saturday",
};
static char *bfmt[] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep",
	"Oct", "Nov", "Dec",
};
static char *Bfmt[] = {
	"January", "February", "March", "April", "May", "June", "July",
	"August", "September", "October", "November", "December",
};

static size_t gsize;
static char *pt;
I 11
D 12
static int _add(), _conv(), _secs();
E 12
I 12
static int _add __P((char *));
D 13
static int _conv __P((int, int, char));
E 13
I 13
static int _conv __P((int, int, int));
E 13
static int _secs __P((const struct tm *));
static size_t _fmt __P((const char *, const struct tm *));
E 12
E 11

size_t
strftime(s, maxsize, format, t)
	char *s;
D 11
	char *format;
E 11
	size_t maxsize;
D 11
	struct tm *t;
E 11
I 11
	const char *format;
	const struct tm *t;
E 11
{
D 11
	size_t _fmt();
E 11
I 11
D 12
	static size_t _fmt();
E 12
E 11

	pt = s;
	if ((gsize = maxsize) < 1)
		return(0);
	if (_fmt(format, t)) {
		*pt = '\0';
		return(maxsize - gsize);
	}
	return(0);
}

static size_t
_fmt(format, t)
D 12
	register char *format;
	struct tm *t;
E 12
I 12
	register const char *format;
	const struct tm *t;
E 12
{
D 3
	char *timezone();

E 3
	for (; *format; ++format) {
		if (*format == '%')
			switch(*++format) {
I 3
			case '\0':
				--format;
				break;
E 3
			case 'A':
D 3
				if (!_add(Afmt[t->tm_mon]))
E 3
I 3
				if (t->tm_wday < 0 || t->tm_wday > 6)
E 3
					return(0);
I 3
				if (!_add(Afmt[t->tm_wday]))
					return(0);
E 3
				continue;
			case 'a':
D 3
				if (!_add(afmt[t->tm_mon]))
E 3
I 3
				if (t->tm_wday < 0 || t->tm_wday > 6)
E 3
					return(0);
I 3
				if (!_add(afmt[t->tm_wday]))
					return(0);
E 3
				continue;
			case 'B':
I 3
				if (t->tm_mon < 0 || t->tm_mon > 11)
					return(0);
E 3
				if (!_add(Bfmt[t->tm_mon]))
					return(0);
				continue;
			case 'b':
I 2
			case 'h':
I 3
				if (t->tm_mon < 0 || t->tm_mon > 11)
					return(0);
E 3
E 2
				if (!_add(bfmt[t->tm_mon]))
					return(0);
				continue;
I 6
			case 'C':
				if (!_fmt("%a %b %e %H:%M:%S %Y", t))
					return(0);
				continue;
E 6
			case 'c':
D 4
				if (!_fmt("%x %X %Z %Y", t))
E 4
I 4
D 5
				if (!_fmt("%a %b %d %X %Z %Y", t))
E 5
I 5
				if (!_fmt("%m/%d/%y %H:%M:%S", t))
E 5
E 4
					return(0);
				continue;
I 6
D 9
			case 'e':
				if (!_conv(t->tm_mday, 2, ' '))
					return(0);
				continue;
E 9
E 6
I 2
			case 'D':
				if (!_fmt("%m/%d/%y", t))
					return(0);
				continue;
E 2
			case 'd':
D 6
				if (!_conv(t->tm_mday, 2))
E 6
I 6
				if (!_conv(t->tm_mday, 2, '0'))
E 6
					return(0);
				continue;
I 9
			case 'e':
				if (!_conv(t->tm_mday, 2, ' '))
					return(0);
				continue;
E 9
			case 'H':
D 6
				if (!_conv(t->tm_hour, 2))
E 6
I 6
				if (!_conv(t->tm_hour, 2, '0'))
E 6
					return(0);
				continue;
			case 'I':
D 3
				if (!_conv((t->tm_hour - 1) % 12 + 1, 2))
E 3
I 3
				if (!_conv(t->tm_hour % 12 ?
D 6
				    t->tm_hour % 12 : 12, 2))
E 6
I 6
				    t->tm_hour % 12 : 12, 2, '0'))
E 6
E 3
					return(0);
				continue;
			case 'j':
D 6
				if (!_conv(t->tm_yday + 1, 3))
E 6
I 6
				if (!_conv(t->tm_yday + 1, 3, '0'))
E 6
					return(0);
				continue;
I 6
			case 'k':
				if (!_conv(t->tm_hour, 2, ' '))
					return(0);
				continue;
			case 'l':
				if (!_conv(t->tm_hour % 12 ?
				    t->tm_hour % 12 : 12, 2, ' '))
					return(0);
				continue;
E 6
			case 'M':
D 6
				if (!_conv(t->tm_min, 2))
E 6
I 6
				if (!_conv(t->tm_min, 2, '0'))
E 6
					return(0);
				continue;
			case 'm':
D 6
				if (!_conv(t->tm_mon + 1, 2))
E 6
I 6
				if (!_conv(t->tm_mon + 1, 2, '0'))
E 6
					return(0);
				continue;
I 2
			case 'n':
				if (!_add("\n"))
					return(0);
				continue;
E 2
			case 'p':
D 3
				if (!_add(t->tm_hour >= 12 ? "AM" : "PM"))
E 3
I 3
				if (!_add(t->tm_hour >= 12 ? "PM" : "AM"))
E 3
					return(0);
				continue;
I 2
			case 'R':
				if (!_fmt("%H:%M", t))
					return(0);
				continue;
			case 'r':
				if (!_fmt("%I:%M:%S %p", t))
					return(0);
				continue;
E 2
			case 'S':
D 6
				if (!_conv(t->tm_sec, 2))
E 6
I 6
				if (!_conv(t->tm_sec, 2, '0'))
E 6
					return(0);
				continue;
I 9
			case 's':
				if (!_secs(t))
					return(0);
				continue;
E 9
I 2
			case 'T':
			case 'X':
				if (!_fmt("%H:%M:%S", t))
					return(0);
				continue;
			case 't':
				if (!_add("\t"))
					return(0);
				continue;
E 2
			case 'U':
				if (!_conv((t->tm_yday + 7 - t->tm_wday) / 7,
D 6
				    2))
E 6
I 6
				    2, '0'))
E 6
					return(0);
				continue;
			case 'W':
				if (!_conv((t->tm_yday + 7 -
D 3
				    (t->tm_wday ? t->tm_wday : 6)) / 7, 2))
E 3
I 3
				    (t->tm_wday ? (t->tm_wday - 1) : 6))
D 6
				    / 7, 2))
E 6
I 6
				    / 7, 2, '0'))
E 6
E 3
					return(0);
				continue;
			case 'w':
D 6
				if (!_conv(t->tm_wday, 1))
E 6
I 6
				if (!_conv(t->tm_wday, 1, '0'))
E 6
D 2
					return(0);
				continue;
			case 'X':
				if (!_fmt("%H:%M:%S", t))
E 2
					return(0);
				continue;
			case 'x':
D 3
				if (!_fmt("%a %b %d", t))
E 3
I 3
D 5
				if (!_fmt("%a %b %d %Y", t))
E 5
I 5
				if (!_fmt("%m/%d/%y", t))
E 5
E 3
					return(0);
				continue;
			case 'y':
				if (!_conv((t->tm_year + TM_YEAR_BASE)
D 6
				    % 100, 2))
E 6
I 6
				    % 100, 2, '0'))
E 6
					return(0);
				continue;
			case 'Y':
D 6
				if (!_conv(t->tm_year + TM_YEAR_BASE, 4))
E 6
I 6
				if (!_conv(t->tm_year + TM_YEAR_BASE, 4, '0'))
E 6
					return(0);
				continue;
			case 'Z':
D 3
				if (!_add(t->tm_zone))
E 3
I 3
				if (!t->tm_zone || !_add(t->tm_zone))
E 3
					return(0);
				continue;
			case '%':
			/*
			 * X311J/88-090 (4.12.3.5): if conversion char is
			 * undefined, behavior is undefined.  Print out the
D 6
			 * character itself as printf(3) also does.
E 6
I 6
			 * character itself as printf(3) does.
E 6
			 */
			default:
				break;
		}
		if (!gsize--)
			return(0);
		*pt++ = *format;
	}
	return(gsize);
I 9
}

D 12
static
E 12
I 12
static int
E 12
_secs(t)
D 12
	struct tm *t;
E 12
I 12
	const struct tm *t;
E 12
{
	static char buf[15];
	register time_t s;
	register char *p;
I 10
	struct tm tmp;
E 10

D 10
	s = mktime(t);
E 10
I 10
	/* Make a copy, mktime(3) modifies the tm struct. */
	tmp = *t;
	s = mktime(&tmp);
E 10
	for (p = buf + sizeof(buf) - 2; s > 0 && p > buf; s /= 10)
		*p-- = s % 10 + '0';
	return(_add(++p));
E 9
}

D 12
static
E 12
I 12
static int
E 12
D 6
_conv(n, digits)
E 6
I 6
_conv(n, digits, pad)
E 6
D 13
	int n, digits;
I 6
	char pad;
E 13
I 13
	int n, digits, pad;
E 13
E 6
{
	static char buf[10];
	register char *p;

	for (p = buf + sizeof(buf) - 2; n > 0 && p > buf; n /= 10, --digits)
		*p-- = n % 10 + '0';
	while (p > buf && digits-- > 0)
D 6
		*p-- = '0';
E 6
I 6
		*p-- = pad;
E 6
	return(_add(++p));
}

D 12
static
E 12
I 12
static int
E 12
_add(str)
	register char *str;
{
	for (;; ++pt, --gsize) {
		if (!gsize)
			return(0);
		if (!(*pt = *str++))
			return(1);
	}
}
E 1
