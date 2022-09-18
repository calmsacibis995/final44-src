h60375
s 00005/00005/00051
d D 8.1 93/06/05 11:01:14 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00055
d D 4.4 90/06/01 16:17:51 bostic 4 3
c new copyright notice
e
s 00052/00036/00014
d D 4.3 89/03/11 15:41:05 bostic 3 2
c new version from Kevin Fall
e
s 00011/00004/00039
d D 4.2 85/08/28 18:45:52 mckusick 2 1
c give more complete error messages
e
s 00043/00000/00000
d D 4.1 80/10/01 17:27:29 bill 1 0
c date and time created 80/10/01 17:27:29 by bill
e
u
U
t
T
I 3
/*
D 5
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Kevin Fall.
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
 */

E 3
I 2
#ifndef lint
E 2
I 1
D 3
static char *sccsid = "%W% (Berkeley) %G%";
I 2
#endif not lint
E 3
I 3
D 5
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 5
I 5
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 5
#endif /* not lint */
E 3

I 3
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/stat.h>
E 3
#include <stdio.h>

E 2
main(argc, argv)
D 2
int argc;
char **argv;
E 2
I 2
	int argc;
	char **argv;
E 2
{
D 3
	int m, a, b;
E 3
I 3
	extern int errno;
	u_short mode;
	char *strerror();
E 3

D 3
	if(argc != 5) {
		printf("arg count\n");
		goto usage;
E 3
I 3
	if (argc != 5) {
		(void)fprintf(stderr,
		    "usage: mknod name [b | c] major minor\n");
		exit(1);
E 3
	}
D 3
	if(*argv[2] == 'b')
		m = 060666; else
	if(*argv[2] == 'c')
		m = 020666; else
		goto usage;
	a = number(argv[3]);
	if(a < 0)
		goto usage;
	b = number(argv[4]);
	if(b < 0)
		goto usage;
D 2
	if(mknod(argv[1], m, (a<<8)|b) < 0)
		perror("mknod");
E 2
I 2
	if(mknod(argv[1], m, (a<<8)|b) < 0) {
		fprintf(stderr, "mknod: ");
		perror(argv[1]);
E 3
I 3

	mode = 0666;
	if (argv[2][0] == 'c')
		mode |= S_IFCHR;
	else if (argv[2][0] == 'b')
		mode |= S_IFBLK;
	else {
		(void)fprintf(stderr,
		    "mknod: node must be type 'b' or 'c'.\n");
		exit(1);
E 3
	}
E 2
D 3
	exit(0);
E 3

D 3
usage:
	printf("usage: mknod name b/c major minor\n");
}

number(s)
char *s;
{
	int n, c;

	n = 0;
	while(c = *s++) {
		if(c<'0' || c>'9')
			return(-1);
		n = n*10 + c-'0';
E 3
I 3
	if (mknod(argv[1], mode, makedev(atoi(argv[3]), atoi(argv[4]))) < 0) {
		(void)fprintf(stderr,
		    "mknod: %s: %s\n", argv[1], strerror(errno));
		exit(1);
E 3
	}
D 3
	return(n);
E 3
I 3
	exit(0);
E 3
}
E 1
