h43982
s 00002/00002/00066
d D 8.1 93/06/04 17:37:03 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00066
d D 5.4 93/05/20 10:51:39 dab 4 3
c Fix all the "#if defined(ENCRYPTION)" lines to just
c be "#ifdef ENCRYPTION", so that unifdef can be used to strip
c out all the encryption code.
e
s 00000/00019/00068
d D 5.3 93/01/20 13:23:13 bostic 3 2
c delete extra Berkeley copyright notice
e
s 00002/00002/00085
d D 5.2 92/12/18 14:11:16 dab 2 1
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Latest version of Kerberos V stuff
c Bug fixes
e
s 00087/00000/00000
d D 5.1 91/02/28 22:01:33 dab 1 0
c date and time created 91/02/28 22:01:33 by dab
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 3
/*
 * Copyright (c) 1988, 1990 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

E 3
#include "misc.h"

char *RemoteHostName;
char *LocalHostName;
char *UserNameRequested = 0;
int ConnectedCount = 0;

	void
auth_encrypt_init(local, remote, name, server)
	char *local;
	char *remote;
	char *name;
	int server;
{
	RemoteHostName = remote;
	LocalHostName = local;
D 2
#if	defined(AUTHENTICATE)
E 2
I 2
#if	defined(AUTHENTICATION)
E 2
	auth_init(name, server);
#endif
D 2
#if	defined(ENCRYPT)
E 2
I 2
D 4
#if	defined(ENCRYPTION)
E 4
I 4
#ifdef	ENCRYPTION
E 4
E 2
	encrypt_init(name, server);
D 4
#endif
E 4
I 4
#endif	/* ENCRYPTION */
E 4
	if (UserNameRequested) {
		free(UserNameRequested);
		UserNameRequested = 0;
	}
}

	void
auth_encrypt_user(name)
	char *name;
{
	extern char *strdup();

	if (UserNameRequested)
		free(UserNameRequested);
	UserNameRequested = name ? strdup(name) : 0;
}

	void
auth_encrypt_connect(cnt)
	int cnt;
{
}

	void
printd(data, cnt)
	unsigned char *data;
	int cnt;
{
	if (cnt > 16)
		cnt = 16;
	while (cnt-- > 0) {
		printf(" %02x", *data);
		++data;
	}
}
E 1
