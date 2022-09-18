h14613
s 00002/00002/00220
d D 8.1 93/06/04 12:07:03 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00006/00220
d D 5.1 92/02/05 11:41:43 bostic 5 4
c don't pass chars to library functions; yank to 5.1
e
s 00009/00002/00217
d D 1.4 91/02/23 19:50:14 donn 4 3
c Add include files to get prototype declarations, and fix bugs found.
e
s 00005/00002/00214
d D 1.3 90/06/27 15:45:48 marc 3 2
c fix strunvis.  return SYNBAD instead of ERROR.
e
s 00032/00031/00184
d D 1.2 90/06/26 14:37:31 marc 2 1
c new implementation -- unvis replaces cdecode
e
s 00215/00000/00000
d D 1.1 90/05/15 10:52:08 marc 1 0
c date and time created 90/05/15 10:52:08 by marc
e
u
U
t
T
I 1
D 2

/*
E 2
I 2
/*-
E 2
D 6
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 2
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
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
#include <ctype.h>
#include <vis.h>

/*
 * decode driven by state machine
 */
#define	S_GROUND	0	/* haven't seen escape char */
#define	S_START		1	/* start decoding special sequence */
#define	S_META		2	/* metachar started (M) */
#define	S_META1		3	/* metachar more, regular char (-) */
#define	S_CTRL		4	/* control char started (^) */
#define	S_OCTAL2	5	/* octal digit 2 */
#define	S_OCTAL3	6	/* octal digit 3 */

I 2
#define	isoctal(c)	(((u_char)(c)) >= '0' && ((u_char)(c)) <= '7')

E 2
/*
 * unvis - decode characters previously encoded by vis
 */
I 4
int
D 5
#if __STDC__
unvis(char *cp, char c, int *astate, int flag)
#else
E 5
E 4
unvis(cp, c, astate, flag)
D 4
	u_char *cp, c;
E 4
I 4
D 5
	char *cp, c;
E 4
	int *astate, flag;
I 4
#endif
E 5
I 5
	char *cp;
	int c, *astate, flag;
E 5
E 4
{

	if (flag & UNVIS_END) {
		if (*astate == S_OCTAL2 || *astate == S_OCTAL3) {
			*astate = S_GROUND;
			return (UNVIS_VALID);
		} 
		return (*astate == S_GROUND ? UNVIS_NOCHAR : UNVIS_SYNBAD);
	}

	switch (*astate) {

	case S_GROUND:
		*cp = 0;
		if (c == '\\') {
			*astate = S_START;
			return (0);
		} 
		*cp = c;
		return (UNVIS_VALID);

	case S_START:
		switch(c) {
		case '\\':
			*cp = c;
			*astate = S_GROUND;
			return (UNVIS_VALID);
		case '0': case '1': case '2': case '3':
		case '4': case '5': case '6': case '7':
			*cp = (c - '0');
			*astate = S_OCTAL2;
			return (0);
		case 'M':
			*cp = 0200;
			*astate = S_META;
			return (0);
		case '^':
			*astate = S_CTRL;
			return (0);
		case 'n':
			*cp = '\n';
			*astate = S_GROUND;
			return (UNVIS_VALID);
		case 'r':
			*cp = '\r';
			*astate = S_GROUND;
			return (UNVIS_VALID);
		case 'b':
			*cp = '\b';
			*astate = S_GROUND;
			return (UNVIS_VALID);
		case 'a':
			*cp = '\007';
			*astate = S_GROUND;
			return (UNVIS_VALID);
		case 'v':
			*cp = '\v';
			*astate = S_GROUND;
			return (UNVIS_VALID);
		case 't':
			*cp = '\t';
			*astate = S_GROUND;
			return (UNVIS_VALID);
		case 'f':
			*cp = '\f';
			*astate = S_GROUND;
			return (UNVIS_VALID);
		case 's':
			*cp = ' ';
			*astate = S_GROUND;
			return (UNVIS_VALID);
		case 'E':
			*cp = '\033';
			*astate = S_GROUND;
			return (UNVIS_VALID);
		case '\n':
			/*
			 * hidden newline
			 */
			*astate = S_GROUND;
			return (UNVIS_NOCHAR);
I 2
		case '$':
			/*
			 * hidden marker
			 */
			*astate = S_GROUND;
			return (UNVIS_NOCHAR);
E 2
		}
		*astate = S_GROUND;
		return (UNVIS_SYNBAD);
		 
	case S_META:
		if (c == '-')
			*astate = S_META1;
		else if (c == '^')
			*astate = S_CTRL;
		else {
			*astate = S_GROUND;
			return (UNVIS_SYNBAD);
		}
		return (0);
		 
	case S_META1:
		*astate = S_GROUND;
		*cp |= c;
		return (UNVIS_VALID);
		 
	case S_CTRL:
		if (c == '?')
			*cp |= 0177;
		else
			*cp |= c & 037;
		*astate = S_GROUND;
		return (UNVIS_VALID);

	case S_OCTAL2:	/* second possible octal digit */
		if (isoctal(c)) {
			/* 
			 * yes - and maybe a third 
			 */
			*cp = (*cp << 3) + (c - '0');
			*astate = S_OCTAL3;	
			return (0);
		} 
		/* 
		 * no - done with current sequence, push back passed char 
		 */
		*astate = S_GROUND;
		return (UNVIS_VALIDPUSH);

	case S_OCTAL3:	/* third possible octal digit */
		*astate = S_GROUND;
		if (isoctal(c)) {
			*cp = (*cp << 3) + (c - '0');
			return (UNVIS_VALID);
		}
		/*
		 * we were done, push back passed char
		 */
		return (UNVIS_VALIDPUSH);
			
	default:	
		/* 
		 * decoder in unknown state - (probably uninitialized) 
		 */
D 3
		return (UNVIS_ERROR);
E 3
I 3
		*astate = S_GROUND;
		return (UNVIS_SYNBAD);
E 3
	}
}

/*
D 2
 * strvis - visually encode characters from src into dst
E 2
I 2
 * strunvis - decode src into dst 
E 2
 *
D 2
 *	If len >= 0, encodes exactly len chars from src (including NULL's).
 *	Otherwise, stops before first NULL in src.  In all cases, dst is 
 *	NULL terminated.
 *
 *	Dst must be 4 times the size of src to account for possible
 *	expansion.  The length of dst, not including the trailing NULL,
 *	is returned.
E 2
I 2
 *	Number of chars decoded into dst is returned, -1 on error.
 *	Dst is null terminated.
E 2
 */
D 2
strvis(dst, src, len, flag)
E 2
I 2

I 4
int
E 4
strunvis(dst, src)
E 2
D 4
	register char *dst, *src;
E 4
I 4
	register char *dst;
	register const char *src;
E 4
D 2
	register int len;
E 2
{
I 2
	register char c;
E 2
	char *start = dst;
I 2
D 3
	int state;
E 3
I 3
	int state = 0;
E 3
E 2

D 2
	for (;;) {
		if (len > 0) { 
			if (len-- == 0)
				break;
		} else if (!*src)
E 2
I 2
	while (c = *src++) {
	again:
		switch (unvis(dst, c, &state, 0)) {
		case UNVIS_VALID:
			dst++;
E 2
			break;
D 2
		dst = vis(dst, *src, flag, *(src+1));
		src++;
E 2
I 2
		case UNVIS_VALIDPUSH:
			dst++;
			goto again;
		case 0:
		case UNVIS_NOCHAR:
			break;
		default:
			return (-1);
		}
E 2
	}
I 3
	if (unvis(dst, c, &state, UNVIS_END) == UNVIS_VALID)
		dst++;
E 3
D 2

E 2
I 2
	*dst = '\0';
E 2
	return (dst - start);
}
E 1
