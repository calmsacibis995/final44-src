h21776
s 00003/00013/00027
d D 5.2 93/05/29 11:15:17 bostic 2 1
c update copyright notices
e
s 00037/00000/00000
d D 5.1 89/05/16 08:51:22 bostic 1 0
c date and time created 89/05/16 08:51:22 by bostic
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1989 The Regents of the University of California.
E 2
I 2
/*-
 * Copyright (c) 1993 The Regents of the University of California.
E 2
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Bill Jolitz.
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

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/uio.h>
#include <sys/file.h>
#include <stdio.h>
#include <connect.h>

struct conversation {
	struct connectdomain co_cd;	/* where we are connecting to */
	char	co_methods[100];	/* how we go about making connection */
	char	co_optionsbuf[1024] ;	/* options requestor wants */
	int	co_constatus ;		/* current connection status */
	int	co_errfd ;		/* requestor's stderr if set */
	int	co_sock ;		/* requestor's socket if set */
	int	co_rqst ;		/* requestor's request if set */
	int	co_pid ;		/* connector pid if active */
};
E 1
