h15649
s 00002/00002/00010
d D 8.1 93/06/01 23:15:02 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00011
d D 5.2 92/07/16 13:27:19 bostic 4 3
c move the update file into /etc/kerberosIV
e
s 00000/00000/00012
d D 5.1 91/02/25 15:46:09 bostic 3 2
c ANSI fixes, yank to rev 5.1, fix the copyright notices
e
s 00010/00002/00002
d D 1.2 90/06/22 18:55:37 kfall 2 1
c filesystem reorg
e
s 00004/00000/00000
d D 1.1 89/08/21 18:02:28 kfall 1 0
c date and time created 89/08/21 18:02:28 by kfall
e
u
U
t
T
I 2
/*-
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 2
I 1

D 2
#define	SERVER_KEYDIR	"/kerberos/register_keys"
E 2
I 2
#define	SERVER_KEYDIR	"/etc/kerberosIV/register_keys"
E 2
D 4
#define	CLIENT_KEYFILE	"/.update.key"
E 4
I 4
#define	CLIENT_KEYFILE	"/etc/kerberosIV/.update.key"
E 4
D 2
#define	_PATH_KPASSWD	"/usr/local/kpasswd"
E 2
I 2
#define	_PATH_KPASSWD	"/usr/bin/passwd"
E 2
E 1
