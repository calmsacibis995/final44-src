h01824
s 00002/00002/00021
d D 8.1 93/06/04 19:07:27 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00000/00017
d D 5.3 91/03/01 01:35:10 dab 3 2
c Telnet AUTHENTICATION option
c Telnet ENCRYPT option (test version)
c Function prototypes
c Bug fixes and code cleanup
e
s 00001/00011/00016
d D 5.2 90/06/01 15:56:32 bostic 2 1
c new copyright notice
e
s 00027/00000/00000
d D 5.1 89/09/01 15:17:53 borman 1 0
c New telnetd, with LINEMODE support
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
D 2
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
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
 */


#include "defs.h"
#include "ext.h"

I 3
#ifdef	DIAGNOSTICS
#define	DIAG(a,b)	if (diagnostic & (a)) b
#else
#define	DIAG(a,b)
#endif

E 3
/* other external variables */
extern	char **environ;
extern	int errno;

E 1
