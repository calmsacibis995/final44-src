h19272
s 00002/00002/00033
d D 8.1 93/06/05 11:04:02 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00035
d D 5.1 92/07/13 15:47:30 pendry 3 2
c move to rev 5
e
s 00001/00000/00034
d D 1.2 92/07/12 09:03:51 pendry 2 1
c checkpoint
e
s 00034/00000/00000
d D 1.1 92/07/09 14:47:42 pendry 1 0
c date and time created 92/07/09 14:47:42 by pendry
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 * All rights reserved.
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * $Id: pt_exec.c,v 1.1 1992/05/25 21:43:09 jsp Exp jsp $
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
I 2
#include <sys/param.h>
E 2
#include <sys/syslog.h>

#include "portald.h"

int portal_exec(pcr, key, v, so, fdp)
struct portal_cred *pcr;
char *key;
char **v;
int so;
int *fdp;
{
	return (ENOEXEC);
}

E 1
