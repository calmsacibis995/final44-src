h34845
s 00005/00005/00022
d D 8.1 93/06/06 22:33:50 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00026
d D 5.4 90/06/01 18:36:39 bostic 5 4
c new copyright notice
e
s 00010/00005/00027
d D 5.3 88/06/29 21:51:21 bostic 4 3
c install approved copyright notice
e
s 00021/00009/00013
d D 5.2 88/01/09 18:12:56 bostic 3 2
c I was sated from moving and it dragged in too much.  added Berkeley header
e
s 00016/00001/00006
d D 5.1 85/05/31 09:41:49 dist 2 1
c Add copyright
e
s 00007/00000/00000
d D 4.1 80/10/08 18:55:05 bill 1 0
c date and time created 80/10/08 18:55:05 by bill
e
u
U
t
T
I 1
D 2
static char *sccsid ="%W% (Berkeley) %G%";
E 2
I 2
/*
D 3
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
D 6
 * Copyright (c) 1987 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1987, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 5
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 4
I 4
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
E 4
E 3
 */

#ifndef lint
D 6
char copyright[] =
D 3
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 3
I 3
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
E 3
 All rights reserved.\n";
E 6
I 6
static char copyright[] =
"%Z% Copyright (c) 1987, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 6
D 3
#endif not lint
E 3
I 3
#endif /* not lint */
E 3

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
#endif /* not lint */
E 3

E 2
main(argc, argv)
D 3
char **argv;
E 3
I 3
	int argc;
	char **argv;
E 3
{
D 3
	for (;;)
		printf("%s\n", argc>1? argv[1]: "y");
E 3
I 3
	if (argc > 1)
		for(;;)
			puts(argv[1]);
	else for (;;)
		puts("y");
E 3
}
E 1
