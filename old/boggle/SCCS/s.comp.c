h18626
s 00005/00005/00034
d D 8.1 93/05/31 16:20:28 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00037
d D 5.3 93/02/03 16:12:49 torek 5 4
c must provide an exit status
e
s 00008/00007/00030
d D 5.2 91/04/08 17:26:17 bostic 4 2
c new copyright; att/bsd/shared
e
s 00008/00007/00030
d R 5.2 91/04/08 17:25:06 bostic 3 2
c new copyright; att/bsd/shared
e
s 00014/00002/00023
d D 5.1 85/05/30 19:41:09 mckusick 2 1
c Add copyright
e
s 00025/00000/00000
d D 4.1 82/12/24 13:07:52 sam 1 0
c date and time created 82/12/24 13:07:52 by sam
e
u
U
t
T
I 2
D 4
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
/*-
D 6
 * Copyright (c) 1982 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1982, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.proprietary.c%
E 4
 */

E 2
I 1
#ifndef lint
D 2
static char sccsid[] = "%W% %G%";
#endif
E 2
I 2
D 6
char copyright[] =
D 4
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 4
I 4
"%Z% Copyright (c) 1982 The Regents of the University of California.\n\
E 4
 All rights reserved.\n";
E 6
I 6
static char copyright[] =
"%Z% Copyright (c) 1982, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 6
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4
E 2

#include <stdio.h>
#define MAX ' '

char new[MAX], old[MAX];

D 5
main ()
E 5
I 5
main()
E 5
{
	register int i, j;
	old[0] = '\0';
	while (fgets(&new[0], MAX, stdin) != NULL) {
		for (i=0; i<MAX && old[i]==new[i]; i++);
		if (i >= MAX) {
			fprintf(stderr, "long word\n");
			exit(1);
		}
		putc(i, stdout);
		for (j=0; (old[j]=new[j]) != '\n'; j++);
		old[j] = '\0';
		fputs(&old[i], stdout);
	}
I 5
	exit(0);
E 5
}
E 1
