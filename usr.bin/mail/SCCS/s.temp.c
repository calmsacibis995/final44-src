h60065
s 00002/00002/00083
d D 8.1 93/06/06 15:08:47 bostic 24 23
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/00082
d D 5.17 92/06/26 12:03:27 bostic 23 22
c quad's broke it -- prototyped it rather than figure out the problem
e
s 00022/00005/00061
d D 5.16 92/03/11 16:46:39 bostic 22 21
c make mail understand TMPDIR
e
s 00000/00003/00066
d D 5.15 91/02/03 13:14:12 bostic 21 20
c ANSI C change: remove -> rm
c change temp file creation to use mkstemp, delete unused function/variable
e
s 00001/00011/00068
d D 5.14 90/06/01 17:00:33 bostic 20 19
c new copyright notice
e
s 00006/00006/00073
d D 5.13 89/08/21 17:34:32 bostic 19 18
c don't have double slashes, for emacs
e
s 00018/00012/00061
d D 5.12 89/05/11 09:44:25 bostic 18 17
c file reorg, pathnames.h, paths.h
e
s 00002/00005/00071
d D 5.11 88/08/17 14:23:41 edward 17 16
c don't need to keep the name of mailrc around
e
s 00001/00004/00075
d D 5.10 88/08/09 17:57:50 edward 16 15
c DEAD added, mbox changed to MBOX
e
s 00018/00016/00061
d D 5.9 88/07/07 06:55:16 edward 15 14
c removed some unnecessary global vars, dynamically allocate some others,
c added spreserve to fix the no sreset when sourcing kludge
e
s 00002/00003/00075
d D 5.8 88/07/06 20:44:28 edward 14 13
c removed global uid variable
e
s 00012/00007/00066
d D 5.7 88/06/29 21:02:09 bostic 13 12
c install approved copyright notice
e
s 00006/00008/00067
d D 5.6 88/06/29 19:04:12 edward 12 11
c use mktemp to make temp file names
e
s 00002/00006/00073
d D 5.5 88/06/17 15:05:08 edward 11 10
c cleaned up file handling code, now allows "mbox" variable
e
s 00011/00005/00068
d D 5.4 88/02/18 17:04:28 bostic 10 9
c written by Kurt Shoens; added Berkeley specific header
e
s 00011/00017/00062
d D 5.3 87/05/18 12:28:50 edward 9 8
c major rework: made faster, cleaned up, obsolete code removed,
c the whole thing should be chucked and written from scratch
e
s 00001/00001/00078
d D 5.2 85/06/21 17:14:23 mckusick 8 7
c botched copyright
e
s 00007/00001/00072
d D 5.1 85/06/06 10:44:31 dist 7 6
c Add copyright
e
s 00003/00003/00070
d D 2.3 83/08/11 22:20:16 sam 6 5
c standardize sccs keyword lines
e
s 00000/00001/00073
d D 2.2 82/06/24 23:54:07 kurt 5 4
c Removed the silly need to set mailname = mailspace since now 
c mailname is an array in its own right. 
c 
e
s 00000/00000/00074
d D 2.1 81/07/01 11:10:33 kurt 4 3
c Release to Heidi Stettner
e
s 00007/00004/00067
d D 1.3 80/10/31 09:18:09 kas 3 2
c Now if you Mail -u unknownUserName, we catch it immediately,
c give error and die
e
s 00001/00001/00070
d D 1.2 80/10/17 00:37:48 kas 2 1
c user name maximum size changed to PATHNAME from 8 in anticipation
c of larger user names in our system
e
s 00071/00000/00000
d D 1.1 80/10/08 09:51:29 kas 1 0
c date and time created 80/10/08 09:51:29 by kas
e
u
U
f b 
t
T
I 7
/*
D 24
 * Copyright (c) 1980 Regents of the University of California.
D 10
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
 * All rights reserved.
E 24
I 24
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 24
 *
D 20
 * Redistribution and use in source and binary forms are permitted
D 13
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 13
I 13
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
E 20
I 20
 * %sccs.include.redist.c%
E 20
E 13
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
D 13
#ifdef notdef
E 13
I 13
#ifndef lint
E 13
static char sccsid[] = "%W% (Berkeley) %G%";
D 13
#endif /* notdef */
E 13
I 13
#endif /* not lint */
E 13
E 10
E 7
E 6

I 22
D 23
#include <errno.h>
E 23
E 22
#include "rcv.h"
I 23
#include <errno.h>
#include "extern.h"
E 23

/*
 * Mail -- a mail program
 *
 * Give names to all the temporary files that we will need.
 */
D 6

static char *SccsId = "%W% %G%";
E 6

D 18
char	tempMail[14];
char	tempQuit[14];
char	tempEdit[14];
char	tempSet[14];
char	tempResid[14];
char	tempMesg[14];
E 18
I 18
char	tempMail[24];
char	tempQuit[24];
char	tempEdit[24];
D 21
char	tempSet[24];
E 21
char	tempResid[24];
char	tempMesg[24];
I 22
char	*tmpdir;
E 22
E 18

I 23
void
E 23
tinit()
{
D 9
	register char *cp, *cp2;
E 9
I 9
	register char *cp;
I 22
	int len;
E 22
E 9
D 2
	char uname[9];
E 2
I 2
D 15
	char uname[PATHSIZE];
E 2
D 9
	register int err = 0;
E 9
D 12
	register int pid;
E 12
I 9
D 14
	uid_t getuid();
E 14
I 14
	int uid;
E 15
I 15
D 17
	char buf[PATHSIZE];
E 17
E 15
E 14
E 9

D 12
	pid = getpid();
	sprintf(tempMail, "/tmp/Rs%05d", pid);
	sprintf(tempResid, "/tmp/Rq%05d", pid);
	sprintf(tempQuit, "/tmp/Rm%05d", pid);
	sprintf(tempEdit, "/tmp/Re%05d", pid);
	sprintf(tempSet, "/tmp/Rx%05d", pid);
	sprintf(tempMesg, "/tmp/Rx%05d", pid);
E 12
I 12
D 18
	mktemp(strcpy(tempMail, "/tmp/RsXXXXXX"));
	mktemp(strcpy(tempResid, "/tmp/RqXXXXXX"));
	mktemp(strcpy(tempQuit, "/tmp/RmXXXXXX"));
	mktemp(strcpy(tempEdit, "/tmp/ReXXXXXX"));
	mktemp(strcpy(tempSet, "/tmp/RxXXXXXX"));
	mktemp(strcpy(tempMesg, "/tmp/RxXXXXXX"));
E 18
I 18
D 22
	strcpy(tempMail, _PATH_TMP);
E 22
I 22
	if ((tmpdir = getenv("TMPDIR")) == NULL)
		tmpdir = _PATH_TMP;
	else {
		len = strlen(tmpdir);
		if ((cp = malloc(len + 2)) == NULL) {
			(void)fprintf(stderr, "mail: %s\n", strerror(errno));
			exit (1);
		}
		(void)strcpy(cp, tmpdir);
		cp[len] = '/';
		cp[len + 1] = '\0';
		tmpdir = cp;
	}
			
	strcpy(tempMail, tmpdir);
E 22
D 19
	mktemp(strcat(tempMail, "/RsXXXXXX"));
E 19
I 19
	mktemp(strcat(tempMail, "RsXXXXXX"));
E 19
D 22
	strcpy(tempResid, _PATH_TMP);
E 22
I 22
	strcpy(tempResid, tmpdir);
E 22
D 19
	mktemp(strcat(tempResid, "/RqXXXXXX"));
E 19
I 19
	mktemp(strcat(tempResid, "RqXXXXXX"));
E 19
D 22
	strcpy(tempQuit, _PATH_TMP);
E 22
I 22
	strcpy(tempQuit, tmpdir);
E 22
D 19
	mktemp(strcat(tempQuit, "/RmXXXXXX"));
E 19
I 19
	mktemp(strcat(tempQuit, "RmXXXXXX"));
E 19
D 22
	strcpy(tempEdit, _PATH_TMP);
E 22
I 22
	strcpy(tempEdit, tmpdir);
E 22
D 19
	mktemp(strcat(tempEdit, "/ReXXXXXX"));
E 19
I 19
	mktemp(strcat(tempEdit, "ReXXXXXX"));
E 19
D 21
	strcpy(tempSet, _PATH_TMP);
D 19
	mktemp(strcat(tempSet, "/RxXXXXXX"));
E 19
I 19
	mktemp(strcat(tempSet, "RxXXXXXX"));
E 21
E 19
D 22
	strcpy(tempMesg, _PATH_TMP);
E 22
I 22
	strcpy(tempMesg, tmpdir);
E 22
D 19
	mktemp(strcat(tempMesg, "/RxXXXXXX"));
E 19
I 19
	mktemp(strcat(tempMesg, "RxXXXXXX"));
E 19
E 18
E 12

D 15
	if (strlen(myname) != 0) {
		uid = getuserid(myname);
D 3
		if (uid == -1)
			goto youlose;
E 3
I 3
		if (uid == -1) {
E 15
I 15
	/*
	 * It's okay to call savestr in here because main will
	 * do a spreserve() after us.
	 */
	if (myname != NOSTR) {
		if (getuserid(myname) < 0) {
E 15
			printf("\"%s\" is not a user of this system\n",
			    myname);
			exit(1);
		}
E 3
D 14
	}
	else {
E 14
I 14
	} else {
E 14
D 9
		uid = getuid() & UIDMASK;
E 9
I 9
D 15
		uid = getuid();
E 9
		if (username(uid, uname) < 0) {
D 9
			copy("ubluit", myname);
D 3
youlose:
E 3
			err++;
E 9
I 9
			strcpy(myname, "ubluit");
E 15
I 15
		if ((cp = username()) == NOSTR) {
			myname = "ubluit";
E 15
E 9
			if (rcvmode) {
				printf("Who are you!?\n");
				exit(1);
			}
D 9
		}
D 3
		copy(uname, myname);
E 3
I 3
		else
			copy(uname, myname);
E 9
I 9
		} else
D 15
			strcpy(myname, uname);
E 15
I 15
			myname = savestr(cp);
E 15
E 9
E 3
	}
D 5
	mailname = mailspace;
E 5
D 9
	cp = value("HOME");
	if (cp == NOSTR)
E 9
I 9
D 17
	if ((cp = value("HOME")) == NOSTR)
E 17
I 17
	if ((cp = getenv("HOME")) == NOSTR)
E 17
E 9
		cp = ".";
D 9
	copy(cp, homedir);
E 9
I 9
D 15
	strcpy(homedir, cp);
E 9
D 11
	findmail();
D 9
	cp = copy(homedir, mbox);
	copy("/mbox", cp);
	cp = copy(homedir, mailrc);
	copy("/.mailrc", cp);
	cp = copy(homedir, deadletter);
	copy("/dead.letter", cp);
E 9
I 9
	strcpy(copy(homedir, mbox), "/mbox");
E 11
	strcpy(copy(homedir, mailrc), "/.mailrc");
	strcpy(copy(homedir, deadletter), "/dead.letter");
E 9
	if (debug) {
D 11
		printf("uid = %d, user = %s, mailname = %s\n",
		    uid, myname, mailname);
		printf("deadletter = %s, mailrc = %s, mbox = %s\n",
		    deadletter, mailrc, mbox);
E 11
I 11
		printf("uid = %d, user = %s\n", uid, myname);
		printf("deadletter = %s, mailrc = %s\n", deadletter, mailrc);
E 11
	}
E 15
I 15
	homedir = savestr(cp);
D 17
	sprintf(buf, "%s/.mailrc", homedir);
	mailrc = savestr(buf);
E 17
D 16
	sprintf(buf, "%s/dead.letter", homedir);
	deadletter = savestr(buf);
E 16
	if (debug)
D 16
		printf("user = %s, deadletter = %s, mailrc = %s\n",
			myname, deadletter, mailrc);
E 16
I 16
D 17
		printf("user = %s, mailrc = %s\n", myname, mailrc);
E 17
I 17
		printf("user = %s, homedir = %s\n", myname, homedir);
E 17
E 16
E 15
}
E 1
