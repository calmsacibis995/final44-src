h31140
s 00002/00002/00179
d D 8.1 93/06/04 17:32:29 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00180
d D 5.4 90/06/01 15:47:21 bostic 5 4
c new copyright notice
e
s 00002/00002/00189
d D 5.3 89/05/06 16:02:50 bostic 4 3
c fix for ANSI C; bug report 4.3BSD/usr.lib/110
e
s 00015/00004/00176
d D 5.2 89/01/03 21:17:56 bostic 3 2
c written by Bill Joy; add Berkeley specific copyright
e
s 00007/00002/00173
d D 5.1 85/06/05 11:31:20 dist 2 1
c Add copyright
e
s 00175/00000/00000
d D 4.1 83/06/27 13:57:05 sam 1 0
c date and time created 83/06/27 13:57:05 by sam
e
u
U
t
T
I 2
/*
D 3
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
D 6
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 5
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 3
 */

E 2
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif
E 2
I 2
D 3
#endif not lint
E 3
I 3
#endif /* not lint */
E 3
E 2

D 2
/* Copyright (c) 1979 Regents of the University of California */
E 2
D 4
#define	CTRL(c)	('c' & 037)
E 4
I 4
#define	CTRL(c)	((c) & 037)
E 4

#define MAXRETURNSIZE 64

char	*UP;
char	*BC;

/*
 * Routine to perform cursor addressing.
 * CM is a string containing printf type escapes to allow
 * cursor addressing.  We start out ready to print the destination
 * line, and switch each time we print row or column.
 * The following escapes are defined for substituting row/column:
 *
 *	%d	as in printf
 *	%2	like %2d
 *	%3	like %3d
 *	%.	gives %c hacking special case characters
 *	%+x	like %c but adding x first
 *
 *	The codes below affect the state but don't use up a value.
 *
 *	%>xy	if value > x add y
 *	%r	reverses row/column
 *	%i	increments row/column (for one origin indexing)
 *	%%	gives %
 *	%B	BCD (2 decimal digits encoded in one byte)
 *	%D	Delta Data (backwards bcd)
 *
 * all other characters are ``self-inserting''.
 */
char *
tgoto(CM, destcol, destline)
	char *CM;
	int destcol, destline;
{
	static char result[MAXRETURNSIZE];
	static char added[10];
	char *cp = CM;
	register char *dp = result;
	register int c;
	int oncol = 0;
	register int which = destline;

	if (cp == 0) {
toohard:
		/*
		 * ``We don't do that under BOZO's big top''
		 */
		return ("OOPS");
	}
	added[0] = 0;
	while (c = *cp++) {
		if (c != '%') {
			*dp++ = c;
			continue;
		}
		switch (c = *cp++) {

#ifdef CM_N
		case 'n':
			destcol ^= 0140;
			destline ^= 0140;
			goto setwhich;
#endif

		case 'd':
			if (which < 10)
				goto one;
			if (which < 100)
				goto two;
			/* fall into... */

		case '3':
			*dp++ = (which / 100) | '0';
			which %= 100;
			/* fall into... */

		case '2':
two:	
			*dp++ = which / 10 | '0';
one:
			*dp++ = which % 10 | '0';
swap:
			oncol = 1 - oncol;
setwhich:
			which = oncol ? destcol : destline;
			continue;

#ifdef CM_GT
		case '>':
			if (which > *cp++)
				which += *cp++;
			else
				cp++;
			continue;
#endif

		case '+':
			which += *cp++;
			/* fall into... */

		case '.':
casedot:
			/*
			 * This code is worth scratching your head at for a
			 * while.  The idea is that various weird things can
			 * happen to nulls, EOT's, tabs, and newlines by the
			 * tty driver, arpanet, and so on, so we don't send
			 * them if we can help it.
			 *
			 * Tab is taken out to get Ann Arbors to work, otherwise
			 * when they go to column 9 we increment which is wrong
			 * because bcd isn't continuous.  We should take out
			 * the rest too, or run the thing through more than
			 * once until it doesn't make any of these, but that
			 * would make termlib (and hence pdp-11 ex) bigger,
			 * and also somewhat slower.  This requires all
			 * programs which use termlib to stty tabs so they
			 * don't get expanded.  They should do this anyway
			 * because some terminals use ^I for other things,
			 * like nondestructive space.
			 */
D 4
			if (which == 0 || which == CTRL(d) || /* which == '\t' || */ which == '\n') {
E 4
I 4
			if (which == 0 || which == CTRL('d') || /* which == '\t' || */ which == '\n') {
E 4
				if (oncol || UP) /* Assumption: backspace works */
					/*
					 * Loop needed because newline happens
					 * to be the successor of tab.
					 */
					do {
						strcat(added, oncol ? (BC ? BC : "\b") : UP);
						which++;
					} while (which == '\n');
			}
			*dp++ = which;
			goto swap;

		case 'r':
			oncol = 1;
			goto setwhich;

		case 'i':
			destcol++;
			destline++;
			which++;
			continue;

		case '%':
			*dp++ = c;
			continue;

#ifdef CM_B
		case 'B':
			which = (which/10 << 4) + which%10;
			continue;
#endif

#ifdef CM_D
		case 'D':
			which = which - 2 * (which%16);
			continue;
#endif

		default:
			goto toohard;
		}
	}
	strcpy(dp, added);
	return (result);
}
E 1
