h30049
s 00001/00011/00047
d D 5.3 90/06/01 14:10:27 bostic 3 2
c new copyright notice
e
s 00001/00001/00057
d D 5.2 90/05/15 19:45:33 bostic 2 1
c string.h is ANSI C include file
e
s 00058/00000/00000
d D 5.1 90/03/13 17:51:35 mckusick 1 0
c date and time created 90/03/13 17:51:35 by mckusick
e
u
U
t
T
I 1
/*
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
D 3
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif LIBC_SCCS and not lint

D 2
#include <strings.h>
E 2
#include <sys/types.h>
#include <sys/stat.h>
I 2
#include <string.h>
E 2

char *objdir = "obj";

#define	UNKNOWN	0
#define	NODIR	1
#define	USEDIR	2

char *
genbuildname(name)
	char *name;
{
	static int dirlen, chkobjdir = UNKNOWN;
	struct stat stbuf;
	char *newname;

	if (chkobjdir == NODIR || index(name, '/') != (char *)0)
		return (name);
	if (chkobjdir == UNKNOWN &&
	    (stat(objdir, &stbuf) < 0 ||
	    (stbuf.st_mode & S_IFMT) != S_IFDIR)) {
		chkobjdir = NODIR;
		return (name);
	} else {
		chkobjdir = USEDIR;
		dirlen = strlen(objdir) + 2;
	}
	newname = (char *)malloc(dirlen + strlen(name));
	if (newname == (char *)0)
		return (name);
	strcpy(newname, objdir);
	strcat(newname, "/");
	strcat(newname, name);
	return (newname);
}
E 1
