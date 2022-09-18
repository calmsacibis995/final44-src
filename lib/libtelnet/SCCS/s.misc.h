h50564
s 00002/00002/00014
d D 8.1 93/06/04 17:37:09 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00016/00000/00000
d D 5.1 91/02/28 22:01:33 dab 1 0
c date and time created 91/02/28 22:01:33 by dab
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

extern char *UserNameRequested;
extern char *LocalHostName;
extern char *RemoteHostName;
extern int ConnectedCount;
extern int ReservedPort;

#include "misc-proto.h"
E 1
