h06312
s 00002/00002/00038
d D 8.1 93/06/06 14:09:41 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00009/00028
d D 5.1 93/05/11 11:49:37 bostic 8 7
c new version from Vernon Schryver (vjs@sgi.com); see ../timed/CHANGES for details
e
s 00001/00011/00036
d D 2.4 90/06/01 19:03:32 bostic 7 6
c new copyright notice
e
s 00011/00006/00036
d D 2.3 88/06/18 14:08:31 bostic 6 5
c install approved copyright notice
e
s 00010/00004/00032
d D 2.2 87/12/23 14:30:24 bostic 5 4
c append Berkeley header; NASA wants a copy
e
s 00000/00000/00036
d D 2.1 85/12/10 13:07:51 bloom 4 3
c Multi network support
e
s 00002/00002/00034
d D 1.3 85/10/23 20:33:28 gusella 3 2
c value of constants MSGS and TRIALS changed
e
s 00004/00001/00032
d D 1.2 85/09/18 10:16:53 bloom 2 1
c add constants, change include to param.h instead of types.h
e
s 00033/00000/00000
d D 1.1 85/06/22 22:08:03 gusella 1 0
c date and time created 85/06/22 22:08:03 by gusella
e
u
U
t
T
I 1
D 8
/*
 * Copyright (c) 1983 Regents of the University of California.
E 8
I 8
/*-
D 9
 * Copyright (c) 1985, 1993 The Regents of the University of California.
E 8
D 5
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 7
 * Redistribution and use in source and binary forms are permitted
D 6
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 6
I 6
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 6
 *
D 6
 *	%W% (Berkeleyb %G%
E 6
I 6
 *	%W% (Berkeley) %G%
E 6
E 5
 */
D 5

/*	%W%	(Berkeley)	%G%	*/
E 5

D 2
#include <sys/types.h>
E 2
I 2
#include <sys/param.h>
E 2
D 8
#include <stdio.h>
E 8
#include <sys/time.h>
D 8
#include <errno.h>
E 8
I 8
#ifdef sgi
#include <sys/uio.h>
#endif
E 8
#include <sys/socket.h>
#include <netinet/in.h>
D 8
#include <netdb.h>
E 8
#include <arpa/inet.h>

I 8
#include <errno.h>
#include <netdb.h>
#include <stdio.h>

E 8
extern int errno;
I 2

#define ON		1
#define OFF		0
E 2

D 3
#define MSGS 		4
#define TRIALS		8
E 3
I 3
D 8
#define MSGS 		6
#define TRIALS		5
E 3

E 8
#define GOOD		1
#define UNREACHABLE	2
#define NONSTDTIME	3
#define HOSTDOWN 	0x7fffffff

struct	cmd {
	char	*c_name;		/* command name */
	char	*c_help;		/* help message */
D 8
	int	(*c_handler)();		/* routine to do the work */
E 8
I 8
	void	(*c_handler)();		/* routine to do the work */
E 8
	int	c_priv;			/* privileged command */
};
I 8

#include "extern.h"
E 8
E 1
