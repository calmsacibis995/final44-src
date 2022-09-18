h01509
s 00005/00005/00038
d D 8.1 93/06/06 16:39:26 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00042
d D 4.4 90/06/01 17:48:28 bostic 4 3
c new copyright notice
e
s 00001/00001/00052
d D 4.3 89/12/07 10:34:53 bostic 3 2
c exit >1 if an error occurs (POSIX 1003.2)
e
s 00045/00011/00008
d D 4.2 88/07/06 16:58:53 bostic 2 1
c add getopt; rewritten from the manual page;
c add Berkeley specific copyright
e
s 00019/00000/00000
d D 4.1 80/10/01 17:29:05 bill 1 0
c date and time created 80/10/01 17:29:05 by bill
e
u
U
t
T
I 1
D 2
static char *sccsid = "%W% (Berkeley) %G%";
E 2
/*
D 2
 * Type tty name
E 2
I 2
D 5
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 2
 */

D 2
char	*ttyname();
E 2
I 2
#ifndef lint
D 5
char copyright[] =
"%Z% Copyright (c) 1988 Regents of the University of California.\n\
 All rights reserved.\n";
E 5
I 5
static char copyright[] =
"%Z% Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 5
#endif /* not lint */
E 2

I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <stdio.h>

E 2
main(argc, argv)
D 2
char **argv;
E 2
I 2
	int argc;
	char **argv;
E 2
{
D 2
	register char *p;
E 2
I 2
	int ch, sflag;
	char *t, *ttyname();
E 2

D 2
	p = ttyname(0);
	if(argc==2 && !strcmp(argv[1], "-s"))
		;
	else
		printf("%s\n", (p? p: "not a tty"));
	exit(p? 0: 1);
E 2
I 2
	sflag = 0;
	while ((ch = getopt(argc, argv, "s")) != EOF)
		switch((char)ch) {
		case 's':
			sflag = 1;
			break;
		case '?':
		default:
			fputs("usage: tty [-s]\n", stderr);
D 3
			exit(1);
E 3
I 3
			exit(2);
E 3
		}

	t = ttyname(0);
	if (!sflag)
		puts(t ? t : "not a tty");
	exit(t ? 0 : 1);
E 2
}
E 1
