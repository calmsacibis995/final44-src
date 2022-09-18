h18269
s 00002/00002/00158
d D 8.1 93/07/19 10:46:11 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00004/00154
d D 5.7 93/07/19 10:45:20 bostic 8 6
c src not being incremented, and string not null-terminated
c from Chris Demetriou
e
s 00002/00002/00156
d R 8.1 93/06/04 12:07:27 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00007/00154
d D 5.6 92/02/05 11:41:32 bostic 6 5
c don't check isascii(), check against UCHAR_MAX (see ANSI C, 4.3)
c don't pass chars to library functions
e
s 00004/00004/00157
d D 5.5 92/02/04 15:28:31 bostic 5 4
c strvis couldn't handle empty strings; from Christos for csh(1)
e
s 00018/00004/00143
d D 5.4 91/02/23 19:50:18 donn 4 3
c Add include files to get prototype declarations, and fix bugs found.
e
s 00039/00171/00108
d D 5.3 90/06/26 14:36:18 marc 3 2
c new implementation -- vis replaces cencode
e
s 00113/00092/00166
d D 5.2 90/05/11 18:24:54 marc 2 1
c (first half of) new version.  name changes to vis() and unvis()
e
s 00258/00000/00000
d D 5.1 89/10/13 16:00:08 marc 1 0
c date and time created 89/10/13 16:00:08 by marc
e
u
U
t
T
I 1
D 3
/*
E 3
I 3
/*-
E 3
D 9
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 3
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
I 6
#include <limits.h>
E 6
#include <ctype.h>
D 3
#include <cencode.h>
E 3
I 3
#include <vis.h>
E 3

D 2
#define	iswhite(c)	((c)==' '||(c)=='\t'||(c)=='\n')
E 2
#define	isoctal(c)	(((u_char)(c)) >= '0' && ((u_char)(c)) <= '7')

/*
D 2
 * cencode
E 2
I 2
 * vis - visually encode characters
E 2
 */
D 2

/*VARARGS2*/
E 2
char *
I 4
D 6
#if __STDC__
vis(register char *dst, register char c, register int flag, char nextc)
#else
E 6
E 4
D 2
cencode(sc, flags, rachar)
	char sc, rachar;
E 2
I 2
vis(dst, c, flag, nextc)
D 6
	register char *dst, c;
	char nextc;
E 6
I 6
	register char *dst;
	int c, nextc;
E 6
	register int flag;
I 4
D 6
#endif
E 6
E 4
E 2
{
D 2
	static char buff[5];
	register char *s = buff;
	register u_char c = sc;

	if (isgraph(c) || (!(flags&CENC_WHITE) && iswhite(c))) {
		if (c == '\\')
			*s++ = '\\';
		*s++ = c;
		goto done;
E 2
I 2
D 6
	if (isascii(c) && isgraph(c) ||
E 6
I 6
	if ((u_int)c <= UCHAR_MAX && isgraph(c) ||
E 6
D 3
	   ((flag & VIS_WHITE) == 0 && 
		(c == ' ' || c == '\n' || (flag & VIS_TAB) == 0 && c == '\t')) ||
E 3
I 3
	   ((flag & VIS_SP) == 0 && c == ' ') ||
	   ((flag & VIS_TAB) == 0 && c == '\t') ||
	   ((flag & VIS_NL) == 0 && c == '\n') ||
E 3
	   ((flag & VIS_SAFE) && (c == '\b' || c == '\007' || c == '\r'))) {
		*dst++ = c;
		if (c == '\\' && (flag & VIS_NOSLASH) == 0)
			*dst++ = '\\';
		*dst = '\0';
		return (dst);
E 2
	}
D 2
	*s++ = '\\';
	if (flags&CENC_CSTYLE) {
E 2
I 2

D 3
	if ((flag & VIS_NOSLASH) == 0)
		*dst++ = '\\';
E 3
	if (flag & VIS_CSTYLE) {
E 2
		switch(c) {
		case '\n':
I 3
			*dst++ = '\\';
E 3
D 2
			*s++ = 'n';
E 2
I 2
			*dst++ = 'n';
E 2
			goto done;
		case '\r':
I 3
			*dst++ = '\\';
E 3
D 2
			*s++ = 'r';
E 2
I 2
			*dst++ = 'r';
E 2
			goto done;
		case '\b':
I 3
			*dst++ = '\\';
E 3
D 2
			*s++ = 'b';
E 2
I 2
			*dst++ = 'b';
E 2
			goto done;
D 2
		case '\007':
			*s++ = 'a';
E 2
I 2
D 4
		case '\007':	/* waiting for ansi compiler */
E 4
I 4
#if __STDC__
		case '\a':
#else
		case '\007':
#endif
E 4
I 3
			*dst++ = '\\';
E 3
			*dst++ = 'a';
E 2
			goto done;
		case '\v':
I 3
			*dst++ = '\\';
E 3
D 2
			*s++ = 'v';
E 2
I 2
			*dst++ = 'v';
E 2
			goto done;
		case '\t':
I 3
			*dst++ = '\\';
E 3
D 2
			*s++ = 't';
E 2
I 2
			*dst++ = 't';
E 2
			goto done;
		case '\f':
I 3
			*dst++ = '\\';
E 3
D 2
			*s++ = 'f';
E 2
I 2
			*dst++ = 'f';
E 2
			goto done;
		case ' ':
I 3
			*dst++ = '\\';
E 3
D 2
			*s++ = 's';
E 2
I 2
			*dst++ = 's';
E 2
			goto done;
		case '\0':
I 3
			*dst++ = '\\';
E 3
D 2
			*s++ = '0';
			if (!(flags&CENC_RACHAR) || isoctal(rachar)) {
				*s++ = '0';
				*s++ = '0';
E 2
I 2
			*dst++ = '0';
D 3
			if ((flag & VIS_NEXTC) == 0 || isoctal(nextc)) {
E 3
I 3
			if (isoctal(nextc)) {
E 3
				*dst++ = '0';
				*dst++ = '0';
E 2
			}
			goto done;
		}
	}
D 2
	if ((flags&CENC_GRAPH) && (c&0177) != ' ') {
		if (c & 0200) {
			c &= 0177;
			*s++ = 'M';
		}
		if (iscntrl(c)) {
			*s++ = '^';
			if (c == 0177)
				*s++ = '?';
			else
				*s++ = c + '@';
		} else {
			*s++ = '-';
			*s++ = c;
		}
E 2
I 2
	if (((c & 0177) == ' ') || (flag & VIS_OCTAL)) {	
I 3
		*dst++ = '\\';
E 3
		*dst++ = ((u_char)c >> 6 & 07) + '0';
		*dst++ = ((u_char)c >> 3 & 07) + '0';
		*dst++ = ((u_char)c & 07) + '0';
E 2
		goto done;
	}
I 3
	if ((flag & VIS_NOSLASH) == 0)
		*dst++ = '\\';
E 3
D 2
	if (flags&CENC_OCTAL) {
		if (flags&CENC_RACHAR && !isoctal(rachar))
			(void)sprintf(s, "%o", (int)c);
E 2
I 2
	if (c & 0200) {
		c &= 0177;
		*dst++ = 'M';
	}
	if (iscntrl(c)) {
		*dst++ = '^';
		if (c == 0177)
			*dst++ = '?';
E 2
		else
D 2
			(void)sprintf(s, "%03o", (int)c);
		while (*s++)
			;
		goto done;
E 2
I 2
			*dst++ = c + '@';
	} else {
		*dst++ = '-';
		*dst++ = c;
E 2
	}
D 2
	/*
	 * Couldn't encode.
	 */
	s--;
	*s = c;
E 2
done:
D 2
	*s = '\0';
	return(buff);
E 2
I 2
	*dst = '\0';
	return (dst);
E 2
}

I 2
D 3

E 3
E 2
/*
D 3
 * decode driven by state machine
 */
#define	S_NORMAL	1	/* haven't seen escape char */
#define	S_START		2	/* start decoding special sequence */
#define	S_META		3	/* metachar started (M) */
#define	S_META1		4	/* metachar more, regular char (-) */
#define	S_CTRL		5	/* control char started (^) */
#define	S_OCTAL		6	/* octal number */

/*
E 3
I 3
 * strvis, strvisx - visually encode characters from src into dst
 *	
 *	Dst must be 4 times the size of src to account for possible
 *	expansion.  The length of dst, not including the trailing NULL,
 *	is returned. 
E 3
 *
I 3
 *	Strvisx encodes exactly len bytes from src into dst.
 *	This is useful for encoding a block of data.
E 3
 */
I 4
int
E 4
D 2
cdecode(c, cp, flags)
E 2
I 2
D 3
cunvis(c, cp, flags)
E 2
	char c;
	char *cp;
E 3
I 3
strvis(dst, src, flag)
D 4
	register char *dst, *src;
E 4
I 4
	register char *dst;
	register const char *src;
	int flag;
E 4
E 3
{
D 3
	static int state = S_NORMAL;
D 2
	u_char buildchar;
	int octal;
E 2
I 2
	static u_char buildchar;
	static int octal;
E 3
I 3
	register char c;
D 5
	char *start = dst;
E 5
I 5
	char *start;
E 5
E 3
E 2

D 2
	if (flags&CDEC_END) {
E 2
I 2
D 3
	if (flags&UNVIS_END) {
E 2
		int ostate = state;
		state = S_NORMAL;
		if (ostate == S_OCTAL) {
			*cp = buildchar;
D 2
			return(CDEC_OK);
E 2
I 2
			return(UNVIS_OK);
E 2
		} else if (ostate == S_META1) {
			/* slightly forgiving, if not wrong */
			*cp = ' ' | 0200;
D 2
			return(CDEC_OK);
E 2
I 2
			return(UNVIS_OK);
E 2
		} else
D 2
			return(ostate == S_NORMAL ? CDEC_NOCHAR : CDEC_SYNBAD);
E 2
I 2
			return(ostate == S_NORMAL ? UNVIS_NOCHAR : CDEC_SYNBAD);
E 2
	}
E 3
I 3
D 5
	for (;c = *src; src++)
		dst = vis(dst, c, flag, *(src+1));
E 3

E 5
I 5
	for (start = dst; c = *src;)
		dst = vis(dst, c, flag, *++src);
	*dst = '\0';
E 5
D 3
	switch (state) {
	case S_NORMAL:
		buildchar = 0;
		if (c == '\\') {
			state = S_START;
D 2
			return(CDEC_NEEDMORE);
		} else if (flags&CDEC_HAT && c == '^') {
E 2
I 2
			return(UNVIS_NEEDMORE);
		} else if (flags&UNVIS_HAT && c == '^') {
E 2
			state = S_CTRL;
D 2
			return(CDEC_NEEDMORE);
E 2
I 2
			return(UNVIS_NEEDMORE);
E 2
		} else {
			*cp = c;
D 2
			return(CDEC_OK);
E 2
I 2
			return(UNVIS_OK);
E 2
		}
		break;
	case S_START:
		state = S_NORMAL;
		if (c == '\\') {
			*cp = c;
D 2
			return(CDEC_OK);
E 2
I 2
			return(UNVIS_OK);
E 2
		}
		if (isoctal(c)) {
			buildchar = (c-'0');
			octal = 1;
			state = S_OCTAL;
D 2
			return(CDEC_NEEDMORE);
E 2
I 2
			return(UNVIS_NEEDMORE);
E 2
		} 
		switch(c) {
		case 'M':
			buildchar |= 0200;
			state = S_META;
D 2
			return(CDEC_NEEDMORE);
E 2
I 2
			return(UNVIS_NEEDMORE);
E 2
		case '^':
			state = S_CTRL;
D 2
			return(CDEC_NEEDMORE);
E 2
I 2
			return(UNVIS_NEEDMORE);
E 2
		case 'n':
			*cp = '\n';
D 2
			return(CDEC_OK);
E 2
I 2
			return(UNVIS_OK);
E 2
		case 'r':
			*cp = '\r';
D 2
			return(CDEC_OK);
E 2
I 2
			return(UNVIS_OK);
E 2
		case 'b':
			*cp = '\b';
D 2
			return(CDEC_OK);
E 2
I 2
			return(UNVIS_OK);
E 2
		case 'a':
			*cp = '\007';
D 2
			return(CDEC_OK);
E 2
I 2
			return(UNVIS_OK);
E 2
		case 'v':
			*cp = '\v';
D 2
			return(CDEC_OK);
E 2
I 2
			return(UNVIS_OK);
E 2
		case 't':
			*cp = '\t';
D 2
			return(CDEC_OK);
E 2
I 2
			return(UNVIS_OK);
E 2
		case 'f':
			*cp = '\f';
D 2
			return(CDEC_OK);
E 2
I 2
			return(UNVIS_OK);
E 2
		case 's':			/* does anyone use this ? */
			*cp = ' ';
D 2
			return(CDEC_OK);
E 2
I 2
			return(UNVIS_OK);
E 2
		case 'E':
			*cp = '\033';
D 2
			return(CDEC_OK);
E 2
I 2
			return(UNVIS_OK);
E 2
		case '\n':
D 2
			return(CDEC_NOCHAR);	/* hidden newline */
E 2
I 2
			return(UNVIS_NOCHAR);	/* hidden newline */
E 2
		}
		state = S_NORMAL;
D 2
		return(CDEC_SYNBAD);
E 2
I 2
		return(UNVIS_SYNBAD);
E 2
	case S_META:
		if (c == '-')
			state = S_META1;
		else if (c == '^')
			state = S_CTRL;
		else {
			state = S_NORMAL;
D 2
			return(CDEC_SYNBAD);
E 2
I 2
			return(UNVIS_SYNBAD);
E 2
		}
D 2
		return(CDEC_NEEDMORE);
E 2
I 2
		return(UNVIS_NEEDMORE);
E 2
	case S_META1:
		state = S_NORMAL;
		*cp = c | buildchar;
D 2
		return(CDEC_OK);
E 2
I 2
		return(UNVIS_OK);
E 2
	case S_CTRL:
		if (c == '?')
			buildchar |= 0177;
		else
			buildchar |= c&037;
		state = S_NORMAL;
		*cp = buildchar;
D 2
		return(CDEC_OK);
E 2
I 2
		return(UNVIS_OK);
E 2
	case S_OCTAL:
		if (isoctal(c)) {
			buildchar = (buildchar<<3) + (c-'0');
			if (++octal == 3) {
				state = S_NORMAL;
				*cp = buildchar;
D 2
				return(CDEC_OK);
E 2
I 2
				return(UNVIS_OK);
E 2
			} else
D 2
				return(CDEC_NEEDMORE);
E 2
I 2
				return(UNVIS_NEEDMORE);
E 2
		} else {
			state = S_NORMAL;
			*cp = buildchar;
D 2
			return(CDEC_OKPUSH);
E 2
I 2
			return(UNVIS_OKPUSH);
E 2
		}
	}
E 3
I 3
	return (dst - start);
E 3
I 2
}

I 4
int
E 4
D 3
/*
 * strvis - visually encode characters from src into dst
 *
 *	If len >= 0, encodes exactly len chars from src (including NULL's).
 *	Otherwise, stops before first NULL in src.  In all cases, dst is 
 *	NULL terminated.
 *
 *	Dst must be 4 times the size of src to account for possible
 *	expansion.  The length of dst, not including the trailing NULL,
 *	is returned.
 */
strvis(dst, src, len, flag)
E 3
I 3
strvisx(dst, src, len, flag)
E 3
D 4
	register char *dst, *src;
	register int len;
E 4
I 4
	register char *dst;
	register const char *src;
	register size_t len;
	int flag;
E 4
{
D 8
	char *start = dst;
E 8
I 8
	int c;
	char *start;
E 8

D 3
	for (;;) {
		if (len > 0) { 
			if (len-- == 0)
				break;
		} else if (!*src)
			break;
		dst = vis(dst, *src, flag | VIS_NEXTC, *(src+1));
		src++;
E 3
I 3
D 8
	while (len > 1) {
		dst = vis(dst, *src, flag, *(src+1));
		len--;
E 8
I 8
	for (start = dst; len > 1; len--) {
		c = *src;
		dst = vis(dst, c, flag, *++src);
E 8
E 3
	}
I 3
	if (len)
		dst = vis(dst, *src, flag, '\0');
I 8
	*dst = '\0';
E 8
E 3

	return (dst - start);
E 2
}
E 1
