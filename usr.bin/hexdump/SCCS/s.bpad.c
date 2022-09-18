h23606
s 00011/00098/00055
d D 5.2 89/08/29 22:18:16 bostic 2 1
c trimming trailing blanks is too hard; the last revision handles most of the
c cases -- the one I quit on is where you have:
c 	"%06.6_ao "  12/1 "%3o "
c 	"\t\t" "%_p"
c 	"\n"
c You'd have to read-ahead and figure out what's going to be printed from
c future format strings to know if the current line should be blank padded.
e
s 00153/00000/00000
d D 5.1 89/08/29 18:36:13 bostic 1 0
c date and time created 89/08/29 18:36:13 by bostic
e
u
U
t
T
I 1
/*
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
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
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <stdio.h>
#include <ctype.h>
#include "hexdump.h"

D 2
bpad(fu, pr, bp)
E 2
I 2
bpad(fu, pr)
E 2
	FU *fu;
	PR *pr;
D 2
	u_char *bp;
E 2
{
D 2
	static char *spec1 = "-0+ #";
	static char *spec2 = ".0123456789";
	enum { NONE, ZEROPAD, NOTSET } fw;
E 2
	register char *p1, *p2;
D 2
	FU *s_fu;
	PR *cur_pr, *s_pr, *txt_pr;
	int newlinecnt;
	char *txt_p1;
E 2

	/*
	 * the format string has no more data to print out.  Go through
	 * the rest of the format string, and, for all non-%s conversions,
	 * replace with %s and remove any conversion flags that don't
	 * apply to %s.  This should replace any output with an equivalent
D 2
	 * number of spaces.  At the same time, keep track of any text
	 * that must be printed, i.e. constant text from the user.  Use
	 * this to trim any trailing spaces and tabs, possibly interspersed
	 * by newlines, leaving only the newlines.
E 2
I 2
	 * number of spaces.
E 2
	 */
D 2
	s_fu = fu;
	cur_pr = pr;
	s_pr = pr = pr->nextpr;
	txt_pr = NULL;
	newlinecnt = 0;
E 2
	for (;;) {
		if (fu->flags&F_IGNORE)
			continue;
		for (; pr; pr = pr->nextpr) {
D 2
			if (pr->flags != F_TEXT)
				*pr->cchar = 's';
E 2
I 2
			if (pr->flags == F_TEXT)
				continue;
			pr->flags = F_BPAD;
			*pr->cchar = 's';
			/* remove conversion flags %s can't handle. */
E 2
			for (p1 = p2 = pr->fmt; *p1; *p2++ = *p1++)
D 2
				switch (*p1) {
				/* remove conversion flags %s can't handle. */
				case '%':
E 2
I 2
				if (*p1 == '%') {
					static char *spec1 = "-0+ #";
					static char *spec2 = ".0123456789";

E 2
					*p2++ = *p1;
					while (index(spec1, *++p1))
						if (*p1 == '-')
							*p2++ = '-';
					while (index(spec2, *p2++ = *p1++));
D 2
					break;
				/* ignore spaces and tabs */
				case ' ': case '\t':
					break;
				/* count newlines */
				case '\n':
					++newlinecnt;
					break;
				/*
				 * anything else has to be printed; keep track
				 * of it, and reset newline counter.
				 */
				default:
					txt_pr = pr;
					txt_p1 = p1 + 1;
					newlinecnt = 0;
					break;
E 2
				}
			*p2 = '\0';
		}
		if (!(fu = fu->nextfu))
			break;
		pr = fu->nextpr;
	}
D 2
	if (txt_pr) {
		/*
		 * if anything else has to be printed, print out the current
		 * item then the rest of the formats up to the one which has
		 * to be displayed.
		 */
		print(cur_pr, bp);
		*txt_p1 = '\0';
		for (fu = s_fu, pr = s_pr;;) {
			if (fu->flags&F_IGNORE)
				continue;
			for (; pr; pr = pr->nextpr) {
				(void)printf(pr->fmt, "");
				if (pr == txt_pr)
					goto done;
			}
			if (!(fu = fu->nextfu))
				break;
			pr = fu->nextpr;
		}
	} else {
		/*
		 * nothing else has to be printed -- serious special case.
		 * If current item is left justified and zero-pad flag not
		 * set, printf will space pad it.
		 */
		for (p1 = p2 = cur_pr->fmt; *p1; *p2++ = *p1++)
			if (*p1 == '%') {
				*p2++ = *p1++;
				for (fw = NOTSET; *p1; ++p1) {
					while (index(spec1 + 2, *p1))
						*p2++ = *p1++;
					if (*p1 == '-') {
						if (fw == NOTSET)
							fw = NONE;
						else if (fw == ZEROPAD)
							*p2++ = '-';
						continue;
					}
					if (*p1 == '0') {
						if (fw == NONE)
							*p2++ = '-';
						fw = ZEROPAD;
						*p2++ = '0';
						continue;
					}
					break;
				}
				if (fw == NONE)
					while (isdigit(*++p1));
				while (index(spec2, *p1))
					*p2++ = *p1++;
			}
		*p2 = '\0';
	}
	/* print out any trailing newlines */
done:	while(newlinecnt--)
		(void)printf("\n");
E 2
}
E 1
