h07887
s 00002/00002/00051
d D 8.1 93/06/11 16:01:00 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00053/00000/00000
d D 7.1 93/06/11 14:35:14 mckusick 1 0
c date and time created 93/06/11 14:35:14 by mckusick
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
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

gets(buf)
	char *buf;
{
	register int c;
	register char *lp;

	for (lp = buf;;)
		switch (c = getchar() & 0177) {
		case '\n':
		case '\r':
			*lp = '\0';
			return;
		case '\b':
		case '\177':
			if (lp > buf) {
				lp--;
				putchar('\b');
				putchar(' ');
				putchar('\b');
			}
			break;
		case '#':
			if (lp > buf)
				--lp;
			break;
		case 'r'&037: {
			register char *p;

			putchar('\n');
			for (p = buf; p < lp; ++p)
				putchar(*p);
			break;
		}
		case '@':
		case 'u'&037:
		case 'w'&037:
			lp = buf;
			putchar('\n');
			break;
		default:
			*lp++ = c;
		}
	/*NOTREACHED*/
}
E 1
