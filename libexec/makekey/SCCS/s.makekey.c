h21509
s 00005/00005/00051
d D 8.1 93/06/04 18:56:40 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00011/00048
d D 5.4 93/05/17 11:18:27 bostic 5 4
c use err(3), prototypes
e
s 00008/00006/00051
d D 5.3 91/02/25 17:07:39 bostic 4 3
c ANSI fixes
e
s 00042/00021/00014
d D 5.2 91/01/19 18:54:47 bostic 3 2
c from scratch; add Berkeley specific copyright notice
e
s 00016/00001/00019
d D 5.1 85/06/06 09:54:26 dist 2 1
c Add copyright
e
s 00020/00000/00000
d D 4.1 80/10/01 17:27:24 bill 1 0
c date and time created 80/10/01 17:27:24 by bill
e
u
U
t
T
I 1
D 2
static char *sccsid = "%W% (Berkeley) %G%";
E 2
I 2
D 3
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
E 3
 */

#ifndef lint
D 6
char copyright[] =
D 3
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 3
I 3
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
E 3
 All rights reserved.\n";
E 6
I 6
static char copyright[] =
"%Z% Copyright (c) 1990, 1993\n\
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

I 5
#include <sys/types.h>

#include <err.h>
E 5
E 2
D 3
/*
 * You send it 10 bytes.
 * It sends you 13 bytes.
 * The transformation is expensive to perform
 * (a significant part of a second).
 */
E 3
I 3
D 4
#include <sys/errno.h>
E 4
I 4
#include <errno.h>
D 5
#include <unistd.h>
E 5
#include <stdio.h>
E 4
#include <stdlib.h>
#include <string.h>
I 5
#include <unistd.h>
E 5
D 4
#include <stdio.h>
#include <unistd.h>
E 4
E 3

I 4
D 5
static void error(), get();
E 5
I 5
static void get __P((char *, int));
E 5

I 5
int
E 5
E 4
D 3
char	*crypt();

E 3
main()
{
D 3
	char key[8];
	char salt[2];
E 3
I 3
	int len;
D 4
	char *r, key[9], salt[3], *crypt();
E 4
I 4
	char *r, key[9], salt[3];
E 4
E 3
	
D 3
	read(0, key, 8);
	read(0, salt, 2);
	write(1, crypt(key, salt), 13);
	return(0);
E 3
I 3
	get(key, sizeof(key) - 1);
	get(salt, sizeof(salt) - 1);
	len = strlen(r = crypt(key, salt));
	if (write(STDOUT_FILENO, r, len) != len)
D 5
		error();
E 5
I 5
		err(1, "stdout");
E 5
	exit(0);
}

D 4
static
E 4
I 4
static void
E 4
get(bp, len)
	char *bp;
	register int len;
{
	register int nr;

	bp[len] = '\0';
	if ((nr = read(STDIN_FILENO, bp, len)) == len)
		return;
	if (nr >= 0)
		errno = EFTYPE;
D 5
	error();
}

D 4
static
E 4
I 4
static void
E 4
error()
{
	(void)fprintf(stderr, "makekey: %s\n", strerror(errno));
	exit(1);
E 5
I 5
	err(1, "stdin");
E 5
E 3
}
E 1
