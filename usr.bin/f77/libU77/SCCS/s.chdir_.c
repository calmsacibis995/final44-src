h50959
s 00008/00005/00033
d D 5.2 91/04/12 15:32:47 bostic 5 4
c new copyright; att/bsd/shared
e
s 00007/00001/00031
d D 5.1 85/06/07 23:11:25 kre 4 3
c Add copyright
e
s 00005/00001/00027
d D 1.3 83/04/30 16:44:27 dlw 3 2
c changed to MAXPATHLEN. DLW
e
s 00002/00002/00026
d D 1.2 81/02/19 10:56:33 dlw 2 1
c added name len check. DLW
e
s 00028/00000/00000
d D 1.1 81/02/11 22:15:30 dlw 1 0
c date and time created 81/02/11 22:15:30 by dlw
e
u
U
t
T
I 1
D 5
/*
D 4
char id_chdir[] = "%W%";
E 4
I 4
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 5
E 4
 *
I 4
D 5
 *	%W%	%G%
E 5
I 5
 * %sccs.include.proprietary.c%
E 5
 */
I 5

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

/*
E 4
 * change default directory
 *
 * calling sequence:
 *	integer chdir
 *	ierror = chdir(dirname)
 * where:
 *	ierror will receive a returned status (0 == OK)
 *	dirname is the directory name
 */

#include "../libI77/f_errno.h"
I 3
#include <sys/param.h>
#ifndef	MAXPATHLEN
#define MAXPATHLEN	128
#endif
E 3

long chdir_(dname, dnamlen)
char *dname;
long dnamlen;
{
D 3
	char buf[128];
E 3
I 3
	char buf[MAXPATHLEN];
E 3

D 2
	g_char(dname, dnamlen, buf);
	if (buf[0] == '\0')
E 2
I 2
	if (dnamlen >= sizeof buf)
E 2
		return((long)(errno=F_ERARG));
I 2
	g_char(dname, dnamlen, buf);
E 2
	if (chdir(buf) != 0)
		return((long)errno);
	return(0L);
}
E 1
