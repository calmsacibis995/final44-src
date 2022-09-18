h46124
s 00001/00001/00033
d D 8.3 94/04/02 10:06:37 pendry 4 3
c add 1994 copyright
e
s 00000/00003/00034
d D 8.2 94/04/02 07:56:55 pendry 3 2
c prettyness police
e
s 00002/00002/00035
d D 8.1 93/06/06 14:27:30 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00037/00000/00000
d D 5.1 91/02/12 22:36:28 bostic 1 0
c rework the password subsystem
c date and time created 91/02/12 22:36:28 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
D 4
 * Copyright (c) 1990, 1993
E 4
I 4
 * Copyright (c) 1990, 1993, 1994
E 4
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <stddef.h>
#include "chpass.h"

char e1[] = ": ";
char e2[] = ":,";

D 3
int p_change(), p_class(), p_expire(), p_gecos(), p_gid(), p_hdir();
int p_login(), p_passwd(), p_shell(), p_uid();

E 3
ENTRY list[] = {
	{ "login",		p_login,  1,   5, e1,   },
	{ "password",		p_passwd, 1,   8, e1,   },
	{ "uid",		p_uid,    1,   3, e1,   },
	{ "gid",		p_gid,    1,   3, e1,   },
	{ "class",		p_class,  1,   5, e1,   },
	{ "change",		p_change, 1,   6, NULL, },
	{ "expire",		p_expire, 1,   6, NULL, },
	{ "full name",		p_gecos,  0,   9, e2,   },
	{ "office phone",	p_gecos,  0,  12, e2,   },
	{ "home phone",		p_gecos,  0,  10, e2,   },
	{ "location",		p_gecos,  0,   8, e2,   },
	{ "home directory",	p_hdir,   1,  14, e1,   },
	{ "shell",		p_shell,  0,   5, e1,   },
	{ NULL, 0, },
};
E 1
