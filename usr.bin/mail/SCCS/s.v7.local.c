h02440
s 00002/00002/00055
d D 8.1 93/06/06 15:08:54 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00001/00052
d D 5.13 92/06/26 12:03:28 bostic 19 18
c quad's broke it -- prototyped it rather than figure out the problem
e
s 00001/00001/00052
d D 5.12 91/02/03 13:14:08 bostic 18 17
c ANSI C change: remove -> rm
c change temp file creation to use mkstemp, delete unused function/variable
e
s 00002/00004/00051
d D 5.11 90/06/24 23:54:34 bostic 17 16
c the old _PATH_MAILDIR path had a trailing slash; fix it
e
s 00001/00001/00054
d D 5.10 90/06/24 23:35:40 bostic 16 15
c move _PATH_MAILDIR into <paths.h>
e
s 00001/00011/00054
d D 5.9 90/06/01 17:00:47 bostic 15 14
c new copyright notice
e
s 00001/00001/00064
d D 5.8 89/05/11 09:44:26 bostic 14 13
c file reorg, pathnames.h, paths.h
e
s 00010/00020/00055
d D 5.7 88/07/07 06:55:06 edward 13 12
c removed some unnecessary global vars, dynamically allocate some others,
c added spreserve to fix the no sreset when sourcing kludge
e
s 00012/00007/00063
d D 5.6 88/06/29 21:02:12 bostic 12 11
c install approved copyright notice
e
s 00007/00008/00063
d D 5.5 88/06/17 15:05:01 edward 11 10
c cleaned up file handling code, now allows "mbox" variable
e
s 00011/00005/00060
d D 5.4 88/02/18 17:04:31 bostic 10 9
c written by Kurt Shoens; added Berkeley specific header
e
s 00001/00003/00064
d D 5.3 87/05/18 12:28:52 edward 9 8
c major rework: made faster, cleaned up, obsolete code removed,
c the whole thing should be chucked and written from scratch
e
s 00001/00001/00066
d D 5.2 85/06/21 17:14:43 mckusick 8 7
c botched copyright
e
s 00007/00001/00060
d D 5.1 85/06/06 10:45:21 dist 7 6
c Add copyright
e
s 00003/00003/00058
d D 2.3 83/08/11 22:20:27 sam 6 5
c standardize sccs keyword lines
e
s 00004/00002/00057
d D 2.2 82/07/28 15:37:22 kurt 5 4
c changed demail to truncate mailbox if unlinking fails 
c 
e
s 00000/00000/00059
d D 2.1 81/07/01 11:10:49 kurt 4 3
c Release to Heidi Stettner
e
s 00004/00001/00055
d D 1.3 81/01/05 17:37:27 kas 3 2
c now honors a flag "keep" to avoid removing your mailbox
e
s 00001/00001/00055
d D 1.2 80/10/17 00:39:12 kas 2 1
c max user name size changed to PATHSIZE
e
s 00056/00000/00000
d D 1.1 80/10/08 09:52:17 kas 1 0
c date and time created 80/10/08 09:52:17 by kas
e
u
U
f b 
t
T
I 7
/*
D 20
 * Copyright (c) 1980 Regents of the University of California.
D 10
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
D 15
 * Redistribution and use in source and binary forms are permitted
D 12
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 12
I 12
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
E 15
I 15
 * %sccs.include.redist.c%
E 15
E 12
E 10
 */

E 7
I 1
D 6
#
E 6
I 6
D 10
#ifndef lint
D 8
static char sccsid[] = "%W% (Berkeley) %G%";
E 8
I 8
static char *sccsid = "%W% (Berkeley) %G%";
E 8
D 7
#endif
E 7
I 7
#endif not lint
E 10
I 10
D 12
#ifdef notdef
E 12
I 12
#ifndef lint
E 12
static char sccsid[] = "%W% (Berkeley) %G%";
D 12
#endif /* notdef */
E 12
I 12
#endif /* not lint */
E 12
E 10
E 7
E 6

/*
 * Mail -- a mail program
 *
 * Version 7
 *
 * Local routines that are installation dependent.
 */

#include "rcv.h"
I 19
#include <fcntl.h>
#include "extern.h"
E 19
D 6

static char *SccsId = "%W% %G%";
E 6

/*
 * Locate the user's mailbox file (ie, the place where new, unread
D 11
 * mail is queued).  In Version 7, it is in /usr/spool/mail/name.
E 11
I 11
 * mail is queued).
E 11
 */
I 19
void
E 19
D 11

findmail()
E 11
I 11
D 13
char *
findmail(user)
E 13
I 13
findmail(user, buf)
E 13
D 17
	char *user;
I 13
	char *buf;
E 17
I 17
	char *user, *buf;
E 17
E 13
E 11
{
I 11
D 13
	static char buf[PATHSIZE];
E 13
E 11
D 9
	register char *cp;
E 9
D 17

D 9
	cp = copy("/usr/spool/mail/", mailname);
	copy(myname, cp);
E 9
I 9
D 11
	strcpy(copy("/usr/spool/mail/", mailname), myname);
E 9
	if (isdir(mailname)) {
		stradd(mailname, '/');
		strcat(mailname, myname);
	}
E 11
I 11
D 14
	strcpy(copy("/usr/spool/mail/", buf), user);
E 14
I 14
D 16
	strcpy(copy(_PATH_MBOX, buf), user);
E 16
I 16
	strcpy(copy(_PATH_MAILDIR, buf), user);
E 17
I 17
	(void)sprintf(buf, "%s/%s", _PATH_MAILDIR, user);
E 17
E 16
E 14
D 13
	return buf;
E 13
E 11
}

/*
 * Get rid of the queued mail.
 */
I 19
void
E 19
D 13

E 13
demail()
{

D 3
	remove(mailname);
E 3
I 3
D 13
	if (value("keep") != NOSTR)
		close(creat(mailname, 0666));
D 5
	else
		remove(mailname);
E 5
I 5
	else {
		if (remove(mailname) < 0)
			close(creat(mailname, 0666));
	}
E 13
I 13
D 18
	if (value("keep") != NOSTR || remove(mailname) < 0)
E 18
I 18
	if (value("keep") != NOSTR || rm(mailname) < 0)
E 18
		close(creat(mailname, 0600));
E 13
E 5
E 3
}

/*
 * Discover user login name.
 */
D 13

username(uid, namebuf)
	char namebuf[];
E 13
I 13
D 19
char*
E 19
I 19
char *
E 19
username()
E 13
{
D 13
	register char *np;
E 13
I 13
	char *np;
E 13

D 13
	if (uid == getuid() && (np = getenv("USER")) != NOSTR) {
D 2
		strncpy(namebuf, np, 9);
E 2
I 2
		strncpy(namebuf, np, PATHSIZE);
E 2
		return(0);
	}
	return(getname(uid, namebuf));
E 13
I 13
	if ((np = getenv("USER")) != NOSTR)
		return np;
	return getname(getuid());
E 13
}
E 1
