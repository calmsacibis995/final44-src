h29661
s 00005/00005/00034
d D 8.1 93/06/06 16:03:07 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00007/00031
d D 5.3 91/04/16 15:56:34 bostic 6 5
c new copyright; att/bsd/shared
e
s 00001/00000/00037
d D 5.2 90/06/28 01:58:17 bostic 5 4
c exit 0 so make doesn't get unhappy
e
s 00015/00001/00022
d D 5.1 85/06/05 15:54:44 dist 4 3
c Add copyright
e
s 00001/00001/00022
d D 2.2 84/04/02 14:04:47 peter 3 2
c time.h moves to sys/time.h.
e
s 00000/00000/00023
d D 2.1 84/02/08 20:23:54 aoki 2 1
c synchronizing at version 2
e
s 00023/00000/00000
d D 1.1 82/08/13 15:32:45 peter 1 0
c date and time created 82/08/13 15:32:45 by peter
e
u
U
t
T
I 1
D 4
static	char *sccsid = "%W% (Berkeley) %E%";
E 4
I 4
D 6
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
/*-
D 7
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
E 6
 */

#ifndef lint
D 7
char copyright[] =
D 6
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 6
I 6
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
E 6
 All rights reserved.\n";
E 7
I 7
static char copyright[] =
"%Z% Copyright (c) 1980, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 7
D 6
#endif not lint
E 6
I 6
#endif /* not lint */
E 6

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif not lint
E 6
I 6
#endif /* not lint */
E 6
E 4

D 3
#include <time.h>
E 3
I 3
#include <sys/time.h>
E 3
#include <stdio.h>

extern char	version[];

main()
{
    long	time();
    long	clock;
    struct tm	*localtime();
    struct tm	*tmp;
    int		major;
    int		minor;

    time(&clock);
    tmp = localtime(&clock);
    sscanf(version, "%d.%d", &major, &minor);
    minor += 1;
    printf("char	version[] = \"%d.%d (%d/%d/%d)\";\n",
	    major, minor, tmp->tm_mon+1, tmp->tm_mday, tmp->tm_year);
I 5
    exit(0);
E 5
}
E 1
