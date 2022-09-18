h41014
s 00005/00005/00059
d D 8.1 93/06/04 17:33:00 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00014/00060
d D 5.3 91/04/12 14:14:00 bostic 4 3
c new copyright; att/bsd/shared
e
s 00021/00004/00053
d D 5.2 89/01/03 21:17:52 bostic 3 2
c written by Bill Joy; add Berkeley specific copyright
e
s 00007/00001/00050
d D 5.1 85/06/05 11:29:28 dist 2 1
c Add copyright
e
s 00051/00000/00000
d D 4.1 83/06/27 13:57:00 sam 1 0
c date and time created 83/06/27 13:57:00 by sam
e
u
U
t
T
I 2
D 4
/*
D 3
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
 * Copyright (c) 1980 The Regents of the University of California.
E 4
I 4
/*-
D 5
 * Copyright (c) 1983 The Regents of the University of California.
E 4
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1983, 1993
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 3
 */

E 2
I 1
#ifndef lint
I 3
D 5
char copyright[] =
D 4
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
E 4
I 4
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 4
 All rights reserved.\n";
E 5
I 5
static char copyright[] =
"%Z% Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 5
#endif /* not lint */

#ifndef lint
E 3
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

/*
 * tc2 [term]
 * Dummy program to test out termlib.
 * Commands are "tcc\n" where t is type (s for string, f for flag,
 * or n for number) and cc is the name of the capability.
 */
#include <stdio.h>
char buf[1024];
char *getenv(), *tgetstr();

main(argc, argv) char **argv; {
	char *p, *q;
	int rc;
	char b[3], c;
	char area[200];

	if (argc < 2)
		p = getenv("TERM");
	else
		p = argv[1];
	rc = tgetent(buf,p);
	for (;;) {
		c = getchar();
		if (c < 0)
			exit(0);
		b[0] = getchar();
		if (b[0] < ' ')
			exit(0);
		b[1] = getchar();
		b[2] = 0;
		getchar();
		switch(c) {
			case 'f':
				printf("%s: %d\n",b,tgetflag(b));
				break;
			case 'n':
				printf("%s: %d\n",b,tgetnum(b));
				break;
			case 's':
				q = area;
				printf("%s: %s\n",b,tgetstr(b,&q));
				break;
			default:
				exit(0);
		}
	}
}
E 1
