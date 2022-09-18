h59311
s 00005/00005/00081
d D 8.1 93/06/04 17:33:05 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00014/00082
d D 5.4 91/04/12 14:14:00 bostic 5 4
c new copyright; att/bsd/shared
e
s 00013/00016/00083
d D 5.3 89/02/28 12:39:59 jak 4 3
c fixed order of tgoto args, zapped reliance on former isprint bug
e
s 00021/00004/00078
d D 5.2 89/01/03 21:17:53 bostic 3 2
c written by Bill Joy; add Berkeley specific copyright
e
s 00007/00001/00075
d D 5.1 85/06/05 11:29:49 dist 2 1
c Add copyright
e
s 00076/00000/00000
d D 4.1 83/06/27 13:57:01 sam 1 0
c date and time created 83/06/27 13:57:01 by sam
e
u
U
t
T
I 2
D 5
/*
D 3
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
 * Copyright (c) 1980 The Regents of the University of California.
E 5
I 5
/*-
D 6
 * Copyright (c) 1983 The Regents of the University of California.
E 5
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1983, 1993
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
I 3
D 6
char copyright[] =
D 5
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
E 5
I 5
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 5
 All rights reserved.\n";
E 6
I 6
static char copyright[] =
"%Z% Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 6
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
 * tc3 [term]
D 4
 * Dummy program to test out termlib.
 * Input two numbers and it prints out the tgoto string generated.
E 4
I 4
 * Dummy program to test out termlib.  Input two numbers (row and col)
 * and it prints out the tgoto string generated.
E 4
 */
#include <stdio.h>
char buf[1024];
char *getenv(), *tgetstr();
char *rdchar();
char *tgoto();
char *CM;
char cmbuff[30];
char *x;
char *UP;
char *tgout;

main(argc, argv) char **argv; {
	char *p;
	int rc;
	int row, col;

	if (argc < 2)
		p = getenv("TERM");
	else
		p = argv[1];
	rc = tgetent(buf,p);
	x = cmbuff;
	UP = tgetstr("up", &x);
	printf("UP = %x = ", UP); pr(UP); printf("\n");
	if (UP && *UP==0)
		UP = 0;
	CM = tgetstr("cm", &x);
	printf("CM = "); pr(CM); printf("\n");
	for (;;) {
		if (scanf("%d %d", &row, &col) < 2)
			exit(0);
D 4
		tgout = tgoto(CM, row, col);
E 4
I 4
		tgout = tgoto(CM, col, row);
E 4
		pr(tgout);
		printf("\n");
	}
}

pr(p)
register char *p;
{
	for (; *p; p++)
		printf("%s", rdchar(*p));
}

/*
D 4
 * rdchar: returns a readable representation of an ASCII char, using ^ notation.
E 4
I 4
 * rdchar() returns a readable representation of an ASCII character
 * using ^ for control, ' for meta.
E 4
 */
#include <ctype.h>
char *rdchar(c)
char c;
{
	static char ret[4];
D 4
	register char *p;
E 4
I 4
	register char *p = ret;
E 4

D 4
	/*
	 * Due to a bug in isprint, this prints spaces as ^`, but this is OK
	 * because we want something to show up on the screen.
	 */
	ret[0] = ((c&0377) > 0177) ? '\'' : ' ';
E 4
I 4
	if ((c&0377) > 0177)
		*p++ = '\'';
E 4
	c &= 0177;
D 4
	ret[1] = isprint(c) ? ' ' : '^';
	ret[2] = isprint(c) ?  c  : c^0100;
	ret[3] = 0;
	for (p=ret; *p==' '; p++)
		;
	return (p);
E 4
I 4
	if (!isprint(c))
		*p++ = '^';
	*p++ = (isprint(c) ?  c  : c^0100);
	*p = 0;
	return (ret);
E 4
}
E 1
