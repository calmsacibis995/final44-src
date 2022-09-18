h18658
s 00002/00002/00056
d D 8.1 93/06/10 22:29:20 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00058/00000/00000
d D 7.1 92/12/13 03:50:13 akito 1 0
c date and time created 92/12/13 03:50:13 by akito
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * OMRON Corporation.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * getline -- simple getline function
 * 	by A.Fujita, Dec-11-1992
 */

int
getline(prompt, buff)
	char *prompt, *buff;
{
	register int c;
	register char *p = buff;

	printf("%s", prompt);

	for(;;) {
		c = cngetc() & 0x7F;

		switch (c) {
		case 0x0a:
		case 0x0d:
			cnputc('\r');
			cnputc('\n');
			*p = '\0';
			goto outloop;

		case 0x08:
		case 0x7f:
			if (p > buff) {
				cnputc(0x08);
				cnputc(' ');
				cnputc(0x08);
				p--;
			}
			break;

		default:
			*p++ = c;
			cnputc(c);
			break;
		}
	}

 outloop:
	return(strlen(buff));
}
E 1
