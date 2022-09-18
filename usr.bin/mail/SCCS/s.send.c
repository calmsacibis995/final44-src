h45088
s 00002/00002/00528
d D 8.1 93/06/06 15:08:41 bostic 49 48
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00009/00530
d D 5.25 92/12/17 12:04:36 bostic 48 47
c mail doesn't need to log who sends mail, does it?
e
s 00012/00000/00527
d D 5.24 92/06/26 12:03:25 bostic 47 46
c quad's broke it -- prototyped it rather than figure out the problem
e
s 00001/00001/00526
d D 5.23 91/02/09 23:01:55 edward 46 45
c for bostic: ANSI C change: remove -> rm
e
s 00007/00005/00520
d D 5.22 90/07/03 02:26:24 edward 45 44
c use of null pointer
e
s 00012/00012/00513
d D 5.21 90/06/25 00:01:31 edward 44 43
c remove call of _fwalk
e
s 00001/00011/00524
d D 5.20 90/06/01 17:00:18 bostic 43 42
c new copyright notice
e
s 00026/00002/00509
d D 5.19 90/01/15 00:21:42 edward 42 41
c fancy indentprefix processing
e
s 00003/00003/00508
d D 5.18 89/05/11 09:44:22 bostic 41 40
c file reorg, pathnames.h, paths.h
e
s 00003/00009/00508
d D 5.17 88/08/09 17:57:46 edward 40 39
c DEAD added, mbox changed to MBOX
e
s 00001/00001/00516
d D 5.16 88/07/12 17:40:56 edward 39 38
c use _exit not exit after fork
e
s 00001/00001/00516
d D 5.15 88/07/08 19:41:50 edward 38 37
c removed some functions in the C library
e
s 00058/00096/00459
d D 5.14 88/07/08 01:43:25 edward 37 36
c rationalized handling of child processes, cleaned up mail1 some more
e
s 00052/00032/00503
d D 5.13 88/07/07 09:34:43 edward 36 35
c merged even more functionality into send()
e
s 00012/00007/00523
d D 5.12 88/06/29 21:02:05 bostic 35 34
c install approved copyright notice
e
s 00072/00096/00458
d D 5.11 88/06/19 04:20:55 edward 34 33
c rationalized mail sending code: keep h_to, h_cc, h_bcc, h_smopts as lists
c not strings; h_seq deleted; now understands <...> addresses; and many more.
c should be much cleaner and somewhat faster.
e
s 00007/00015/00547
d D 5.10 88/06/18 14:54:16 edward 33 32
c removed support for -r, -h, and rmail
e
s 00007/00006/00555
d D 5.9 88/06/16 21:50:19 edward 32 31
c replaced intty and outtty by value("interactive"), ~ only in interactive mode
e
s 00001/00005/00560
d D 5.8 88/06/16 17:41:02 edward 31 30
c prehistoric (e.g., pre-sendmail) code removed
e
s 00013/00024/00552
d D 5.7 88/06/11 01:15:48 edward 30 29
c added -c -b -t flags, end echo with newline,
c from Tom Newcomb (newcomb@arpa)
e
s 00004/00003/00572
d D 5.6 88/06/09 22:24:28 edward 29 28
c new commands saveignore, saveretain, and savediscard
e
s 00011/00005/00564
d D 5.5 88/02/18 17:04:21 bostic 28 27
c written by Kurt Shoens; added Berkeley specific header
e
s 00038/00038/00531
d D 5.4 87/05/18 12:51:56 edward 27 26
c lint
e
s 00130/00151/00439
d D 5.3 87/05/18 12:28:39 edward 26 25
c major rework: made faster, cleaned up, obsolete code removed,
c the whole thing should be chucked and written from scratch
e
s 00001/00001/00589
d D 5.2 85/06/21 17:13:57 mckusick 25 24
c botched copyright
e
s 00007/00001/00583
d D 5.1 85/06/06 10:42:43 dist 24 23
c Add copyright
e
s 00001/00001/00583
d D 2.14 84/08/08 17:06:02 ralph 23 22
c fix stdio flushing, don't mess with stdio buffers
e
s 00003/00003/00581
d D 2.13 83/08/11 22:19:37 sam 22 21
c standardize sccs keyword lines
e
s 00001/00001/00583
d D 2.12 83/07/02 00:23:57 sam 21 20
c include fix
e
s 00003/00004/00581
d D 2.11 83/05/19 02:32:26 leres 20 18
c Ok to send a message with no subject and no body
e
s 00002/00004/00581
d R 2.11 83/03/17 19:32:30 leres 19 18
c Allow no body, no subject messages, why not?
e
s 00001/00001/00584
d D 2.10 83/02/09 15:25:00 sam 18 17
c from sun
e
s 00043/00022/00542
d D 2.9 83/01/22 15:11:50 leres 17 14
c Modified to only append to the POSTAGE file if it already exists. Modified
c fmt() to *really* limit lines to 72 characters. Added support for verbose
c command/option.
e
s 00043/00022/00542
d R 2.9 83/01/22 15:10:13 leres 16 14
c Modified to only append to the POSTAGE file if it already exists. Modified
c fmt() to *really* limit lines to 72 characters. Added support for verbose
e
s 00043/00022/00542
d R 2.9 83/01/22 15:04:54 leres 15 14
c Modified to append to the POSTAGE file only if it already exists.
c Modified fmt() to *really* limit lines to 72 characters and modified
e
s 00003/00003/00561
d D 2.8 82/12/26 21:16:29 eric 14 13
c change delivermail to sendmail throughout
e
s 00006/00003/00558
d D 2.7 82/11/17 23:11:50 bush 13 12
c Send fixed to supress continuation lines in ignored fields.
e
s 00004/00004/00557
d D 2.6 82/10/21 05:36:54 carl 12 11
c Changes to support long mail sizes (long m_size).
e
s 00005/00000/00556
d D 2.5 82/10/21 04:42:36 carl 11 10
c Wait3 becomes wait2 if pdp11 is defined, stays wait3 if vax is defined.
e
s 00011/00013/00545
d D 2.4 82/07/29 09:13:39 kurt 10 9
c Made recognition of Status: header field slightly more reliable. 
c 
e
s 00060/00011/00498
d D 2.3 82/07/28 23:20:42 kurt 9 8
c changed send() to take doignore argument and ignore header fields 
c that the user doesn't want to see; 
c changed statusput() to see if "status" should be ignored. 
c 
e
s 00002/00001/00507
d D 2.2 82/07/26 17:13:00 kurt 8 7
c added call on sigchild() after fork() to fix retrofit signals; 
c parameterized location of postage meter file 
c 
e
s 00000/00000/00508
d D 2.1 81/07/01 11:10:23 kurt 7 6
c Release to Heidi Stettner
e
s 00004/00002/00504
d D 1.6 81/05/18 15:53:11 kurt 6 5
c added option sendmail which lets you specify what program to use to
c actually send the mail
e
s 00004/00004/00502
d D 1.5 81/04/01 13:03:11 kurt 5 4
c changed calls on signal to sigset
e
s 00032/00002/00474
d D 1.4 81/03/13 12:44:54 kas 4 3
c fixed bug of putting Status:  line in wrong place for non
c Arpanetish messages
e
s 00001/00002/00475
d D 1.3 81/01/05 17:36:49 kas 3 2
c removed incriminating error message
e
s 00051/00006/00426
d D 1.2 80/10/17 00:36:21 kas 2 1
c send() now updates the status: field in the message image
c that it writes out.  Added routine statusput to print the Status: field
c in the appropriate format
e
s 00432/00000/00000
d D 1.1 80/10/08 09:51:16 kas 1 0
c date and time created 80/10/08 09:51:16 by kas
e
u
U
f b 
t
T
I 24
/*
D 49
 * Copyright (c) 1980 Regents of the University of California.
D 28
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 28
I 28
 * All rights reserved.
E 49
I 49
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 49
 *
D 43
 * Redistribution and use in source and binary forms are permitted
D 35
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 35
I 35
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
E 43
I 43
 * %sccs.include.redist.c%
E 43
E 35
E 28
 */

E 24
I 1
D 22
#
E 22
I 22
D 28
#ifndef lint
D 25
static char sccsid[] = "%W% (Berkeley) %G%";
E 25
I 25
static char *sccsid = "%W% (Berkeley) %G%";
E 25
D 24
#endif
E 24
I 24
#endif not lint
E 28
I 28
D 35
#ifdef notdef
E 35
I 35
#ifndef lint
E 35
static char sccsid[] = "%W% (Berkeley) %G%";
D 35
#endif /* notdef */
E 35
I 35
#endif /* not lint */
E 35
E 28
E 24
E 22

#include "rcv.h"
I 47
#include "extern.h"
E 47
D 26
#ifdef VMUNIX
E 26
D 21
#include <wait.h>
E 21
I 21
D 37
#include <sys/wait.h>
E 21
D 26
#endif
I 4
#include <ctype.h>
E 26
I 17
#include <sys/stat.h>
E 37
E 17
E 4

/*
 * Mail -- a mail program
 *
 * Mail to others.
 */
D 22

static char *SccsId = "%W% %G%";
E 22

/*
 * Send message described by the passed pointer to the
D 36
 * passed output buffer.  Return -1 on error, but normally
D 2
 * the number of lines written.
E 2
I 2
 * the number of lines written.  Adjust the status: field
D 9
 * if need be.
E 9
I 9
D 29
 * if need be.  If doign is set, suppress ignored header fields.
E 29
I 29
 * if need be.  If doign is given, suppress ignored header fields.
E 36
I 36
 * passed output buffer.  Return -1 on error.
 * Adjust the status: field if need be.
 * If doign is given, suppress ignored header fields.
 * prefix is a string to prepend to each output line.
E 36
E 29
E 9
E 2
 */
I 47
int
E 47
D 10

E 10
D 9
send(mailp, obuf)
E 9
I 9
D 26
send(mailp, obuf, doign)
E 9
	struct message *mailp;
E 26
I 26
D 36
send(mp, obuf, doign)
E 36
I 36
send(mp, obuf, doign, prefix)
E 36
	register struct message *mp;
E 26
	FILE *obuf;
I 29
	struct ignoretab *doign;
I 36
	char *prefix;
E 36
E 29
{
D 26
	register struct message *mp;
	register int t;
D 12
	unsigned int c;
E 12
I 12
	long c;
E 12
	FILE *ibuf;
D 2
	int lc;
E 2
I 2
D 9
	char line[LINESIZE];
D 4
	int lc, ishead;
E 4
I 4
	int lc, ishead, infld, fline;
E 9
I 9
	char line[LINESIZE], field[BUFSIZ];
	int lc, ishead, infld, fline, dostat;
	char *cp, *cp2;
E 26
I 26
	long count;
	register FILE *ibuf;
	char line[LINESIZE];
D 36
	int lc, ishead, infld, ignoring, dostat;
E 36
I 36
	int ishead, infld, ignoring, dostat, firstline;
E 36
	register char *cp, *cp2;
	register int c;
	int length;
I 42
	int prefixlen;
E 42
E 26
E 9
E 4
E 2

I 42
	/*
	 * Compute the prefix string, without trailing whitespace
	 */
D 45
	cp2 = 0;
	for (cp = prefix; *cp; cp++)
		if (*cp != ' ' && *cp != '\t')
			cp2 = cp;
	prefixlen = cp2 == 0 ? 0 : cp2 - prefix + 1;
E 45
I 45
	if (prefix != NOSTR) {
		cp2 = 0;
		for (cp = prefix; *cp; cp++)
			if (*cp != ' ' && *cp != '\t')
				cp2 = cp;
		prefixlen = cp2 == 0 ? 0 : cp2 - prefix + 1;
	}
E 45
E 42
D 26
	mp = mailp;
E 26
	ibuf = setinput(mp);
D 12
	c = msize(mp);
E 12
I 12
D 26
	c = mp->m_size;
E 26
I 26
	count = mp->m_size;
E 26
E 12
I 2
D 9
	ishead = (mailp->m_flag & MSTATUS) != 0;
E 9
I 9
	ishead = 1;
D 26
	dostat = 1;
E 26
I 26
D 29
	dostat = !doign || !isign("status");
E 29
I 29
	dostat = doign == 0 || !isign("status", doign);
E 29
E 26
E 9
I 4
	infld = 0;
D 26
	fline = 1;
E 26
E 4
E 2
D 36
	lc = 0;
E 36
I 36
	firstline = 1;
E 36
D 2
	while (c-- > 0) {
		putc(t = getc(ibuf), obuf);
		if (t == '\n')
			lc++;
E 2
I 2
D 12
	while (c > 0) {
E 12
I 12
D 26
	while (c > 0L) {
E 12
		fgets(line, LINESIZE, ibuf);
D 12
		c -= strlen(line);
E 12
I 12
		c -= (long) strlen(line);
E 12
		lc++;
		if (ishead) {
E 26
I 26
	/*
	 * Process headers first
	 */
	while (count > 0 && ishead) {
		if (fgets(line, LINESIZE, ibuf) == NULL)
			break;
		count -= length = strlen(line);
D 36
		if (lc == 0) {
E 36
I 36
		if (firstline) {
E 36
E 26
I 9
			/* 
			 * First line is the From line, so no headers
			 * there to worry about
			 */
E 9
I 4
D 26
			if (fline) {
				fline = 0;
				goto writeit;
			}
E 26
I 26
D 36
			ignoring = 0;
E 36
I 36
			firstline = 0;
			ignoring = doign == ignoreall;
E 36
		} else if (line[0] == '\n') {
E 26
I 9
			/*
			 * If line is blank, we've reached end of
			 * headers, so force out status: field
			 * and note that we are no longer in header
			 * fields
			 */
E 9
E 4
D 26
			if (line[0] == '\n') {
D 9
				statusput(mailp, obuf);
E 9
I 9
				if (dostat) {
					statusput(mailp, obuf, doign);
					dostat = 0;
				}
E 9
				ishead = 0;
				goto writeit;
E 26
I 26
			if (dostat) {
D 36
				statusput(mp, obuf);
E 36
I 36
				statusput(mp, obuf, prefix);
E 36
				dostat = 0;
E 26
			}
I 26
			ishead = 0;
D 36
			ignoring = 0;
E 36
I 36
			ignoring = doign == ignoreall;
E 36
		} else if (infld && (line[0] == ' ' || line[0] == '\t')) {
E 26
I 9
			/*
D 13
			 * If this line is a continuation
			 * of a previous header field, just echo it.
E 13
I 13
			 * If this line is a continuation (via space or tab)
			 * of a previous header field, just echo it
			 * (unless the field should be ignored).
I 26
			 * In other words, nothing to do.
E 26
E 13
			 */
E 9
D 4
			if (index(line, ':') == 0)
E 4
I 4
D 13
			if (isspace(line[0]) && infld)
E 13
I 13
D 26
			if (infld && (isspace(line[0]) || line[0] == '\t')) {
				if (doign && isign(field)) continue;
E 13
E 4
				goto writeit;
I 13
			}
E 13
I 4
			infld = 0;
E 26
I 26
		} else {
E 26
I 9
			/*
D 26
			 * If we are no longer looking at real
			 * header lines, force out status:
			 * This happens in uucp style mail where
			 * there are no headers at all.
E 26
I 26
			 * Pick up the header field if we have one.
E 26
			 */
E 9
D 26
			if (!headerp(line)) {
E 26
I 26
			for (cp = line; (c = *cp++) && c != ':' && !isspace(c);)
				;
			cp2 = --cp;
			while (isspace(*cp++))
				;
			if (cp[-1] != ':') {
				/*
				 * Not a header line, force out status:
				 * This happens in uucp style mail where
				 * there are no headers at all.
				 */
E 26
D 9
				statusput(mailp, obuf);
E 9
I 9
				if (dostat) {
D 26
					statusput(mailp, obuf, doign);
E 26
I 26
D 36
					statusput(mp, obuf);
E 36
I 36
					statusput(mp, obuf, prefix);
E 36
E 26
					dostat = 0;
				}
E 9
D 26
				putc('\n', obuf);
E 26
I 26
D 27
				putc('\n', obuf);	/* add blank line */
E 27
I 27
D 36
				(void) putc('\n', obuf); /* add blank line */
E 27
				lc++;
E 36
I 36
				if (doign != ignoreall)
					/* add blank line */
					(void) putc('\n', obuf);
E 36
E 26
				ishead = 0;
D 26
				goto writeit;
			}
			infld++;
I 9
			/*
D 10
			 * We are looking at a header line.
			 * See if it is the status: field,
			 * and if it is, print the real status: field
			 */
E 9
E 4
			if (icisname(line, "status", 6)) {
D 9
				statusput(mailp, obuf);
				ishead = 0;
E 9
I 9
				if (dostat) {
					statusput(mailp, obuf, doign);
					dostat = 0;
				}
E 9
				continue;
			}
I 9
			/*
E 10
			 * Pick up the header field.
			 * If it is an ignored field and
			 * we care about such things, skip it.
			 */
			cp = line;
			cp2 = field;
			while (*cp && *cp != ':' && !isspace(*cp))
				*cp2++ = *cp++;
			*cp2 = 0;
			if (doign && isign(field))
				continue;
I 10
			/*
			 * If the field is "status," go compute and print the
			 * real Status: field
			 */
			if (icequal(field, "status")) {
				if (dostat) {
					statusput(mailp, obuf, doign);
					dostat = 0;
E 26
I 26
				ignoring = 0;
			} else {
				/*
				 * If it is an ignored field and
				 * we care about such things, skip it.
				 */
				*cp2 = 0;	/* temporarily null terminate */
D 29
				if (doign && isign(line))
E 29
I 29
				if (doign && isign(line, doign))
E 29
					ignoring = 1;
				else if ((line[0] == 's' || line[0] == 'S') &&
D 38
					 icequal(line, "status")) {
E 38
I 38
					 strcasecmp(line, "status") == 0) {
E 38
					/*
					 * If the field is "status," go compute
					 * and print the real Status: field
					 */
					if (dostat) {
D 36
						statusput(mp, obuf);
E 36
I 36
						statusput(mp, obuf, prefix);
E 36
						dostat = 0;
					}
					ignoring = 1;
				} else {
					ignoring = 0;
					*cp2 = c;	/* restore */
E 26
				}
D 26
				continue;
E 26
I 26
				infld = 1;
E 26
			}
E 10
E 9
		}
D 26
writeit:
		fputs(line, obuf);
E 2
		if (ferror(obuf))
			return(-1);
E 26
I 26
		if (!ignoring) {
I 36
D 42
			if (prefix != NOSTR && length > 1)
				fputs(prefix, obuf);
E 42
I 42
			/*
			 * Strip trailing whitespace from prefix
			 * if line is blank.
			 */
			if (prefix != NOSTR)
				if (length > 1)
					fputs(prefix, obuf);
				else
					(void) fwrite(prefix, sizeof *prefix,
							prefixlen, obuf);
E 42
E 36
D 27
			fwrite(line, sizeof *line, length, obuf);
E 27
I 27
			(void) fwrite(line, sizeof *line, length, obuf);
E 27
			if (ferror(obuf))
				return -1;
D 36
			lc++;
E 36
		}
E 26
	}
I 2
D 26
	if (ferror(obuf))
		return(-1);
	if (ishead && (mailp->m_flag & MSTATUS))
E 26
I 26
	/*
	 * Copy out message body
	 */
D 36
	while (count > 0) {
		cp = line;
		c = count < LINESIZE ? count : LINESIZE;
		if ((c = fread(cp, sizeof *cp, c, ibuf)) <= 0)
			break;
		if (fwrite(cp, sizeof *cp, c, obuf) != c)
E 36
I 36
	if (doign == ignoreall)
		count--;		/* skip final blank line */
	if (prefix != NOSTR)
		while (count > 0) {
			if (fgets(line, LINESIZE, ibuf) == NULL) {
				c = 0;
				break;
			}
			count -= c = strlen(line);
I 42
			/*
			 * Strip trailing whitespace from prefix
			 * if line is blank.
			 */
E 42
			if (c > 1)
				fputs(prefix, obuf);
I 42
			else
				(void) fwrite(prefix, sizeof *prefix,
						prefixlen, obuf);
E 42
			(void) fwrite(line, sizeof *line, c, obuf);
			if (ferror(obuf))
				return -1;
		}
	else
		while (count > 0) {
			c = count < LINESIZE ? count : LINESIZE;
			if ((c = fread(line, sizeof *line, c, ibuf)) <= 0)
				break;
			count -= c;
			if (fwrite(line, sizeof *line, c, obuf) != c)
				return -1;
		}
	if (doign == ignoreall && c > 0 && line[c - 1] != '\n')
		/* no final blank line */
		if ((c = getc(ibuf)) != EOF && putc(c, obuf) == EOF)
E 36
			return -1;
D 36
		count -= c;
		while (--c >= 0)
			if (*cp++ == '\n')
				lc++;
	}
	if (ishead && (mp->m_flag & MSTATUS))
E 26
		printf("failed to fix up status field\n");
E 2
D 26
	return(lc);
E 26
I 26
	return (lc);
E 36
I 36
	return 0;
E 36
E 26
I 4
}

/*
D 26
 * Test if the passed line is a header line, RFC 733 style.
 */
headerp(line)
	register char *line;
{
	register char *cp = line;

	while (*cp && !isspace(*cp) && *cp != ':')
		cp++;
	while (*cp && isspace(*cp))
		cp++;
	return(*cp == ':');
E 4
}
I 2

/*
E 26
 * Output a reasonable looking status field.
I 9
D 36
 * But if "status" is ignored and doign, forget it.
E 36
E 9
 */
I 47
void
E 47
D 9

statusput(mp, obuf)
E 9
I 9
D 26
statusput(mp, obuf, doign)
E 26
I 26
D 36
statusput(mp, obuf)
E 36
I 36
statusput(mp, obuf, prefix)
E 36
E 26
E 9
	register struct message *mp;
D 26
	register FILE *obuf;
E 26
I 26
	FILE *obuf;
I 36
	char *prefix;
E 36
E 26
{
	char statout[3];
I 26
	register char *cp = statout;
E 26

I 9
D 26
	if (doign && isign("status"))
		return;
E 9
	if ((mp->m_flag & (MNEW|MREAD)) == MNEW)
		return;
E 26
	if (mp->m_flag & MREAD)
D 26
		strcpy(statout, "R");
	else
		strcpy(statout, "");
E 26
I 26
		*cp++ = 'R';
E 26
	if ((mp->m_flag & MNEW) == 0)
D 26
		strcat(statout, "O");
	fprintf(obuf, "Status: %s\n", statout);
E 26
I 26
		*cp++ = 'O';
	*cp = 0;
	if (statout[0])
D 36
		fprintf(obuf, "Status: %s\n", statout);
E 36
I 36
		fprintf(obuf, "%sStatus: %s\n",
			prefix == NOSTR ? "" : prefix, statout);
E 36
E 26
}

E 2
D 26

E 26
/*
 * Interface between the argument list and the mail1 routine
 * which does all the dirty work.
 */
I 47
int
E 47
D 37

E 37
D 30
mail(people)
	char **people;
E 30
I 30
D 34
mail(to, cc, bcc, smopts)
E 34
I 34
mail(to, cc, bcc, smopts, subject)
E 34
	struct name *to, *cc, *bcc, *smopts;
I 34
	char *subject;
E 34
E 30
{
D 30
	register char *cp2;
	register int s;
	char *buf, **ap;
E 30
	struct header head;

D 26
	for (s = 0, ap = people; *ap != (char *) -1; ap++)
E 26
I 26
D 30
	for (s = 0, ap = people; *ap != 0; ap++)
E 26
		s += strlen(*ap) + 1;
	buf = salloc(s+1);
	cp2 = buf;
D 26
	for (ap = people; *ap != (char *) -1; ap++) {
E 26
I 26
	for (ap = people; *ap != 0; ap++) {
E 26
		cp2 = copy(*ap, cp2);
		*cp2++ = ' ';
	}
	if (cp2 != buf)
		cp2--;
	*cp2 = '\0';
	head.h_to = buf;
E 30
I 30
D 34
	head.h_to = detract(to, 0);
E 30
	head.h_subject = NOSTR;
D 30
	head.h_cc = NOSTR;
	head.h_bcc = NOSTR;
E 30
I 30
	head.h_cc = detract(cc, 0);
	head.h_bcc = detract(bcc, 0);
	head.h_smopts = detract(smopts, 0);
E 30
	head.h_seq = 0;
D 27
	mail1(&head);
E 27
I 27
	(void) mail1(&head);
E 34
I 34
	head.h_to = to;
	head.h_subject = subject;
	head.h_cc = cc;
	head.h_bcc = bcc;
	head.h_smopts = smopts;
D 37
	(void) mail1(&head, 0);
E 37
I 37
	mail1(&head, 0);
E 37
E 34
E 27
	return(0);
}


/*
 * Send mail to a bunch of user names.  The interface is through
 * the mail routine below.
 */
I 47
int
E 47
D 37

E 37
sendmail(str)
	char *str;
{
D 26
	register char **ap;
	char *bufp;
	register int t;
E 26
	struct header head;

D 34
	if (blankline(str))
		head.h_to = NOSTR;
	else
		head.h_to = str;
E 34
I 34
	head.h_to = extract(str, GTO);
E 34
	head.h_subject = NOSTR;
D 34
	head.h_cc = NOSTR;
	head.h_bcc = NOSTR;
I 30
	head.h_smopts = NOSTR;
E 30
	head.h_seq = 0;
D 27
	mail1(&head);
E 27
I 27
	(void) mail1(&head);
E 34
I 34
	head.h_cc = NIL;
	head.h_bcc = NIL;
	head.h_smopts = NIL;
D 37
	(void) mail1(&head, 0);
E 37
I 37
	mail1(&head, 0);
E 37
E 34
E 27
	return(0);
}

/*
 * Mail a message on standard input to the people indicated
 * in the passed header.  (Internal interface).
 */
I 47
void
E 47
D 37

E 37
D 34
mail1(hp)
E 34
I 34
mail1(hp, printheaders)
E 34
	struct header *hp;
I 47
	int printheaders;
E 47
{
D 37
	register char *cp;
D 26
	int pid, i, s, p, gotcha;
E 26
I 26
	int pid, i, p, gotcha;
	union wait s;
E 26
D 6
	char **namelist;
E 6
I 6
	char **namelist, *deliver;
E 6
	struct name *to, *np;
I 17
	struct stat sbuf;
E 17
	FILE *mtf, *postage;
D 33
	int remote = rflag != NOSTR || rmail;
E 33
	char **t;
E 37
I 37
	char *cp;
	int pid;
	char **namelist;
	struct name *to;
	FILE *mtf;
E 37

	/*
	 * Collect user's mail from standard input.
	 * Get the result as mtf.
	 */
D 37

	pid = -1;
E 37
I 30
D 34
	if (hp->h_subject == NOSTR)
		hp->h_subject = sflag;
E 30
	if ((mtf = collect(hp)) == NULL)
E 34
I 34
	if ((mtf = collect(hp, printheaders)) == NULL)
E 34
D 37
		return(-1);
E 37
I 37
		return;
E 37
D 34
	hp->h_seq = 1;
E 34
D 30
	if (hp->h_subject == NOSTR)
		hp->h_subject = sflag;
E 30
D 20
	if (fsize(mtf) == 0 && hp->h_subject == NOSTR) {
		printf("No message !?!\n");
		goto out;
	}
E 20
D 32
	if (intty && value("askcc") != NOSTR)
		grabh(hp, GCC);
	else if (intty) {
		printf("EOT\n");
D 23
		flush();
E 23
I 23
D 27
		fflush(stdout);
E 27
I 27
		(void) fflush(stdout);
E 27
E 23
	}
E 32
I 32
	if (value("interactive") != NOSTR)
		if (value("askcc") != NOSTR)
			grabh(hp, GCC);
		else {
			printf("EOT\n");
			(void) fflush(stdout);
		}
I 37
	if (fsize(mtf) == 0)
		if (hp->h_subject == NOSTR)
			printf("No message, no subject; hope that's ok\n");
		else
			printf("Null message body; hope that's ok\n");
E 37
E 32
D 34

E 34
	/*
	 * Now, take the user names from the combined
	 * to and cc lists and do all the alias
	 * processing.
	 */
D 34

E 34
	senderr = 0;
D 34
	to = usermap(cat(extract(hp->h_bcc, GBCC),
D 30
	    cat(extract(hp->h_to, GTO), extract(hp->h_cc, GCC))));
E 30
I 30
		cat(extract(hp->h_to, GTO), extract(hp->h_cc, GCC))));
E 34
I 34
	to = usermap(cat(hp->h_bcc, cat(hp->h_to, hp->h_cc)));
E 34
E 30
	if (to == NIL) {
		printf("No recipients specified\n");
D 37
		goto topdog;
E 37
I 37
		senderr++;
E 37
	}
D 34

E 34
	/*
	 * Look through the recipient list for names with /'s
	 * in them which we write to as files directly.
	 */
D 34

E 34
	to = outof(to, mtf, hp);
D 37
	rewind(mtf);
E 37
D 31
	to = verify(to);
E 31
D 33
	if (senderr && !remote) {
E 33
I 33
D 40
	if (senderr) {
E 33
D 37
topdog:
E 37
D 33

E 33
		if (fsize(mtf) != 0) {
D 27
			remove(deadletter);
			exwrite(deadletter, mtf, 1);
E 27
I 27
			(void) remove(deadletter);
			(void) exwrite(deadletter, mtf, 1);
E 27
			rewind(mtf);
		}
	}
E 40
I 40
	if (senderr)
		savedeadletter(mtf);
E 40
D 37
	for (gotcha = 0, np = to; np != NIL; np = np->n_flink)
		if ((np->n_type & GDEL) == 0) {
			gotcha++;
			break;
		}
	if (!gotcha)
		goto out;
E 37
	to = elide(to);
D 33
	mechk(to);
E 33
D 34
	if (count(to) > 1)
		hp->h_seq++;
D 33
	if (hp->h_seq > 0 && !remote) {
E 33
I 33
	if (hp->h_seq > 0) {
E 33
		fixhead(hp, to);
		if (fsize(mtf) == 0)
I 20
		    if (hp->h_subject == NOSTR)
E 34
I 34
D 37
	if (fsize(mtf) == 0)
		if (hp->h_subject == NOSTR)
E 34
			printf("No message, no subject; hope that's ok\n");
D 34
		    else
E 34
I 34
		else
E 34
E 20
			printf("Null message body; hope that's ok\n");
I 34
	if (count(to) > 0 || hp->h_subject != NOSTR) {
		/* don't do this unless we have to */
		fixhead(hp, to);
E 34
		if ((mtf = infix(hp, mtf)) == NULL) {
			fprintf(stderr, ". . . message lost, sorry.\n");
			return(-1);
		}
E 37
I 37
	if (count(to) == 0)
		goto out;
	fixhead(hp, to);
	if ((mtf = infix(hp, mtf)) == NULL) {
		fprintf(stderr, ". . . message lost, sorry.\n");
		return;
E 37
	}
D 30
	namelist = unpack(to);
E 30
I 30
D 34
	namelist = unpack(cat(extract(hp->h_smopts, 0), to));
E 34
I 34
	namelist = unpack(cat(hp->h_smopts, to));
E 34
E 30
	if (debug) {
I 37
		char **t;

E 37
D 34
		printf("Recipients of message:\n");
E 34
I 34
		printf("Sendmail arguments:");
E 34
		for (t = namelist; *t != NOSTR; t++)
			printf(" \"%s\"", *t);
		printf("\n");
D 27
		fflush(stdout);
E 27
I 27
D 37
		(void) fflush(stdout);
E 27
D 26
		return;
E 26
I 26
		return 0;
E 37
I 37
		goto out;
E 37
E 26
	}
	if ((cp = value("record")) != NOSTR)
D 26
		savemail(expand(cp), hp, mtf);
E 26
I 26
D 27
		savemail(expand(cp), mtf);
E 27
I 27
		(void) savemail(expand(cp), mtf);
E 27
E 26
D 34

E 34
	/*
D 37
	 * Wait, to absorb a potential zombie, then
	 * fork, set up the temporary mail file as standard
	 * input for "mail" and exec with the user list we generated
	 * far above. Return the process id to caller in case he
	 * wants to await the completion of mail.
E 37
I 37
	 * Fork, set up the temporary mail file as standard
	 * input for "mail", and exec with the user list we generated
	 * far above.
E 37
	 */
D 34

E 34
D 26
#ifdef VMUNIX
I 11
#ifdef	pdp11
	while (wait2(&s, WNOHANG) > 0)
#endif
D 18
#ifdef	vax
E 18
I 18
#if defined(vax) || defined(sun)
E 18
E 11
	while (wait3(&s, WNOHANG, 0) > 0)
I 11
#endif
E 26
I 26
D 37
	while (wait3(&s, WNOHANG, (struct timeval *) 0) > 0)
E 26
E 11
		;
D 26
#else
	wait(&s);
#endif
E 26
	rewind(mtf);
E 37
	pid = fork();
	if (pid == -1) {
		perror("fork");
D 27
		remove(deadletter);
		exwrite(deadletter, mtf, 1);
E 27
I 27
D 40
		(void) remove(deadletter);
		(void) exwrite(deadletter, mtf, 1);
E 40
I 40
		savedeadletter(mtf);
E 40
E 27
		goto out;
	}
	if (pid == 0) {
I 8
D 26
		sigchild();
E 26
E 8
D 37
#ifdef SIGTSTP
D 33
		if (remote == 0) {
D 5
			signal(SIGTSTP, SIG_IGN);
			signal(SIGTTIN, SIG_IGN);
			signal(SIGTTOU, SIG_IGN);
E 5
I 5
D 26
			sigset(SIGTSTP, SIG_IGN);
			sigset(SIGTTIN, SIG_IGN);
			sigset(SIGTTOU, SIG_IGN);
E 26
I 26
D 27
			signal(SIGTSTP, SIG_IGN);
			signal(SIGTTIN, SIG_IGN);
			signal(SIGTTOU, SIG_IGN);
E 27
I 27
			(void) signal(SIGTSTP, SIG_IGN);
			(void) signal(SIGTTIN, SIG_IGN);
			(void) signal(SIGTTOU, SIG_IGN);
E 27
E 26
E 5
		}
E 33
I 33
		(void) signal(SIGTSTP, SIG_IGN);
		(void) signal(SIGTTIN, SIG_IGN);
		(void) signal(SIGTTOU, SIG_IGN);
E 33
#endif
D 26
		for (i = SIGHUP; i <= SIGQUIT; i++)
D 5
			signal(i, SIG_IGN);
E 5
I 5
			sigset(i, SIG_IGN);
E 26
I 26
D 27
		signal(SIGHUP, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
E 27
I 27
		(void) signal(SIGHUP, SIG_IGN);
		(void) signal(SIGINT, SIG_IGN);
		(void) signal(SIGQUIT, SIG_IGN);
E 27
E 26
E 5
D 8
		if ((postage = fopen("/crp/kurt/postage", "a")) != NULL) {
E 8
I 8
D 17
		if ((postage = fopen(POSTAGE, "a")) != NULL) {
E 8
			fprintf(postage, "%s %d %d\n", myname,
			    count(to), fsize(mtf));
			fclose(postage);
		}
E 17
I 17
		if (!stat(POSTAGE, &sbuf))
E 37
I 37
D 41
		if (access(POSTAGE, 0) == 0) {
E 41
I 41
D 48
		if (access(_PATH_MAIL_LOG, 0) == 0) {
E 41
			FILE *postage;

E 37
D 41
			if ((postage = fopen(POSTAGE, "a")) != NULL) {
E 41
I 41
D 44
			if ((postage = fopen(_PATH_MAIL_LOG, "a")) != NULL) {
E 44
I 44
			if ((postage = Fopen(_PATH_MAIL_LOG, "a")) != NULL) {
E 44
E 41
D 27
				fprintf(postage, "%s %d %d\n", myname,
E 27
I 27
				fprintf(postage, "%s %d %ld\n", myname,
E 27
				    count(to), fsize(mtf));
D 27
				fclose(postage);
E 27
I 27
D 44
				(void) fclose(postage);
E 44
I 44
				(void) Fclose(postage);
E 44
E 27
			}
E 17
D 26
		s = fileno(mtf);
		for (i = 3; i < 15; i++)
			if (i != s)
				close(i);
E 26
D 27
		close(0);
D 26
		dup(s);
		close(s);
#ifdef CC
		submit(getpid());
#endif CC
E 26
I 26
		dup(fileno(mtf));
E 27
I 27
D 37
		(void) close(0);
		(void) dup(fileno(mtf));
E 27
		for (i = getdtablesize(); --i > 2;)
D 27
			close(i);
E 27
I 27
			(void) close(i);
E 27
E 26
D 14
#ifdef DELIVERMAIL
E 14
I 14
D 31
#ifdef SENDMAIL
E 31
E 14
D 6
		execv(DELIVERMAIL, namelist);
E 6
I 6
		if ((deliver = value("sendmail")) == NOSTR)
D 14
			deliver = DELIVERMAIL;
E 14
I 14
			deliver = SENDMAIL;
E 14
		execv(deliver, namelist);
E 6
D 14
#endif DELIVERMAIL
E 14
I 14
D 31
#endif SENDMAIL
E 14
		execv(MAIL, namelist);
		perror(MAIL);
E 31
I 31
		perror(deliver);
E 37
I 37
		}
E 48
		prepare_child(sigmask(SIGHUP)|sigmask(SIGINT)|sigmask(SIGQUIT)|
			sigmask(SIGTSTP)|sigmask(SIGTTIN)|sigmask(SIGTTOU),
			fileno(mtf), -1);
		if ((cp = value("sendmail")) != NOSTR)
			cp = expand(cp);
		else
D 41
			cp = SENDMAIL;
E 41
I 41
			cp = _PATH_SENDMAIL;
E 41
		execv(cp, namelist);
		perror(cp);
E 37
E 31
D 39
		exit(1);
E 39
I 39
		_exit(1);
E 39
	}
I 37
	if (value("verbose") != NOSTR)
		(void) wait_child(pid);
	else
		free_child(pid);
E 37
D 34

E 34
out:
D 17
	if (remote) {
E 17
I 17
D 33
	if (remote || (value("verbose") != NOSTR)) {
E 33
I 33
D 37
	if (value("verbose") != NOSTR) {
E 33
E 17
		while ((p = wait(&s)) != pid && p != -1)
			;
D 26
		if (s != 0)
E 26
I 26
		if (s.w_status != 0)
E 26
			senderr++;
		pid = 0;
	}
E 37
D 27
	fclose(mtf);
E 27
I 27
D 44
	(void) fclose(mtf);
E 44
I 44
	(void) Fclose(mtf);
E 44
E 27
D 34
	return(pid);
E 34
I 34
D 37
	return pid;
E 37
E 34
}

/*
 * Fix the header by glopping all of the expanded names from
 * the distribution list into the appropriate fields.
D 34
 * If there are any ARPA net recipients in the message,
 * we must insert commas, alas.
E 34
 */
I 47
void
E 47
D 34

E 34
fixhead(hp, tolist)
	struct header *hp;
	struct name *tolist;
{
D 26
	register struct name *nlist;
E 26
D 34
	register int f;
E 34
	register struct name *np;

D 34
	for (f = 0, np = tolist; np != NIL; np = np->n_flink)
		if (any('@', np->n_name)) {
			f |= GCOMMA;
			break;
		}

	if (debug && f & GCOMMA)
		fprintf(stderr, "Should be inserting commas in recip lists\n");
	hp->h_to = detract(tolist, GTO|f);
	hp->h_cc = detract(tolist, GCC|f);
I 30
	hp->h_bcc = detract(tolist, GBCC|f);
E 34
I 34
	hp->h_to = NIL;
	hp->h_cc = NIL;
	hp->h_bcc = NIL;
	for (np = tolist; np != NIL; np = np->n_flink)
		if ((np->n_type & GMASK) == GTO)
			hp->h_to =
				cat(hp->h_to, nalloc(np->n_name, np->n_type));
		else if ((np->n_type & GMASK) == GCC)
			hp->h_cc =
				cat(hp->h_cc, nalloc(np->n_name, np->n_type));
		else if ((np->n_type & GMASK) == GBCC)
			hp->h_bcc =
				cat(hp->h_bcc, nalloc(np->n_name, np->n_type));
E 34
E 30
}

/*
 * Prepend a header in front of the collected stuff
 * and return the new file.
 */
D 37

E 37
FILE *
infix(hp, fi)
	struct header *hp;
	FILE *fi;
{
	extern char tempMail[];
	register FILE *nfo, *nfi;
	register int c;

I 3
D 37
	rewind(fi);
E 37
E 3
D 44
	if ((nfo = fopen(tempMail, "w")) == NULL) {
E 44
I 44
	if ((nfo = Fopen(tempMail, "w")) == NULL) {
E 44
		perror(tempMail);
		return(fi);
	}
D 44
	if ((nfi = fopen(tempMail, "r")) == NULL) {
E 44
I 44
	if ((nfi = Fopen(tempMail, "r")) == NULL) {
E 44
		perror(tempMail);
D 27
		fclose(nfo);
E 27
I 27
D 44
		(void) fclose(nfo);
E 44
I 44
		(void) Fclose(nfo);
E 44
E 27
		return(fi);
	}
D 27
	remove(tempMail);
	puthead(hp, nfo, GTO|GSUBJECT|GCC|GNL);
E 27
I 27
D 46
	(void) remove(tempMail);
E 46
I 46
	(void) rm(tempMail);
E 46
D 30
	(void) puthead(hp, nfo, GTO|GSUBJECT|GCC|GNL);
E 30
I 30
D 34
	(void) puthead(hp, nfo, GTO|GSUBJECT|GCC|GBCC|GNL);
E 34
I 34
	(void) puthead(hp, nfo, GTO|GSUBJECT|GCC|GBCC|GNL|GCOMMA);
E 34
E 30
E 27
D 3
	rewind(fi);
E 3
	c = getc(fi);
	while (c != EOF) {
D 27
		putc(c, nfo);
E 27
I 27
		(void) putc(c, nfo);
E 27
		c = getc(fi);
	}
	if (ferror(fi)) {
		perror("read");
I 37
		rewind(fi);
E 37
D 3
		fprintf(stderr, "Please notify Kurt Shoens\n");
E 3
		return(fi);
	}
D 27
	fflush(nfo);
E 27
I 27
	(void) fflush(nfo);
E 27
	if (ferror(nfo)) {
		perror(tempMail);
D 27
		fclose(nfo);
		fclose(nfi);
E 27
I 27
D 44
		(void) fclose(nfo);
		(void) fclose(nfi);
E 44
I 44
		(void) Fclose(nfo);
		(void) Fclose(nfi);
E 44
I 37
		rewind(fi);
E 37
E 27
		return(fi);
	}
D 27
	fclose(nfo);
	fclose(fi);
E 27
I 27
D 44
	(void) fclose(nfo);
	(void) fclose(fi);
E 44
I 44
	(void) Fclose(nfo);
	(void) Fclose(fi);
E 44
E 27
	rewind(nfi);
	return(nfi);
}

/*
 * Dump the to, subject, cc header on the
 * passed file buffer.
 */
I 47
int
E 47
D 34

E 34
puthead(hp, fo, w)
	struct header *hp;
	FILE *fo;
I 47
	int w;
E 47
{
	register int gotcha;

	gotcha = 0;
D 34
	if (hp->h_to != NOSTR && w & GTO)
D 17
		fprintf(fo, "To: "), fmt(hp->h_to, fo), gotcha++;
E 17
I 17
		fmt("To: ", hp->h_to, fo), gotcha++;
E 34
I 34
	if (hp->h_to != NIL && w & GTO)
D 37
		fmt("To: ", hp->h_to, fo, w&GCOMMA), gotcha++;
E 37
I 37
		fmt("To:", hp->h_to, fo, w&GCOMMA), gotcha++;
E 37
E 34
E 17
	if (hp->h_subject != NOSTR && w & GSUBJECT)
		fprintf(fo, "Subject: %s\n", hp->h_subject), gotcha++;
D 34
	if (hp->h_cc != NOSTR && w & GCC)
D 17
		fprintf(fo, "Cc: "), fmt(hp->h_cc, fo), gotcha++;
E 17
I 17
		fmt("Cc: ", hp->h_cc, fo), gotcha++;
E 17
	if (hp->h_bcc != NOSTR && w & GBCC)
D 17
		fprintf(fo, "Bcc: "), fmt(hp->h_bcc, fo), gotcha++;
E 17
I 17
		fmt("Bcc: ", hp->h_bcc, fo), gotcha++;
E 34
I 34
	if (hp->h_cc != NIL && w & GCC)
D 37
		fmt("Cc: ", hp->h_cc, fo, w&GCOMMA), gotcha++;
E 37
I 37
		fmt("Cc:", hp->h_cc, fo, w&GCOMMA), gotcha++;
E 37
	if (hp->h_bcc != NIL && w & GBCC)
D 37
		fmt("Bcc: ", hp->h_bcc, fo, w&GCOMMA), gotcha++;
E 37
I 37
		fmt("Bcc:", hp->h_bcc, fo, w&GCOMMA), gotcha++;
E 37
E 34
E 17
	if (gotcha && w & GNL)
D 27
		putc('\n', fo);
E 27
I 27
		(void) putc('\n', fo);
E 27
	return(0);
}

/*
D 37
 * Format the given text to not exceed 72 characters.
E 37
I 37
 * Format the given header line to not exceed 72 characters.
E 37
 */
I 47
void
E 47
D 34

D 17
fmt(str, fo)
	register char *str;
E 17
I 17
fmt(str, txt, fo)
	register char *str, *txt;
E 17
	register FILE *fo;
E 34
I 34
fmt(str, np, fo, comma)
	char *str;
	register struct name *np;
	FILE *fo;
	int comma;
E 34
{
D 34
	register int col;
D 17
	register char *cp;
E 17
I 17
	register char *bg, *bl, *pt, ch;
E 34
I 34
	register col, len;
E 34
E 17

I 34
	comma = comma ? 1 : 0;
E 34
D 17
	cp = str;
	col = 0;
	while (*cp) {
		if (*cp == ' ' && col > 65) {
			fprintf(fo, "\n    ");
E 17
I 17
	col = strlen(str);
	if (col)
D 34
		fprintf(fo, "%s", str);
	pt = bg = txt;
	bl = 0;
	while (*bg) {
		pt++;
D 26
		if (++col >72) {
E 26
I 26
		if (++col > 72) {
E 26
			if (!bl) {
				bl = bg;
				while (*bl && !isspace(*bl))
					bl++;
			}
			if (!*bl)
				goto finish;
			ch = *bl;
			*bl = '\0';
			fprintf(fo, "%s\n    ", bg);
E 34
I 34
		fputs(str, fo);
D 37
	len = strlen(np->n_name);
	for (;;) {
		fputs(np->n_name, fo);
		col += len;
		if (comma) {
			putc(',', fo);
			col++;
		}
		if ((np = np->n_flink) == NIL)
			break;
E 37
I 37
	for (; np != NIL; np = np->n_flink) {
E 37
		if (np->n_flink == NIL)
			comma = 0;
		len = strlen(np->n_name);
D 37
		if (col + len + comma > 72) {
E 37
I 37
		col++;		/* for the space */
		if (col + len + comma > 72 && col > 4) {
E 37
			fputs("\n    ", fo);
E 34
E 17
			col = 4;
D 17
			cp++;
			continue;
E 17
I 17
D 34
			*bl = ch;
			pt = bg = ++bl;
			bl = 0;
E 34
I 34
D 37
		} else {
E 37
I 37
		} else
E 37
			putc(' ', fo);
D 37
			col++;
E 34
E 17
		}
E 37
I 37
		fputs(np->n_name, fo);
		if (comma)
			putc(',', fo);
		col += len + comma;
E 37
D 17
		putc(*cp++, fo);
		col++;
E 17
I 17
D 34
		if (!*pt) {
finish:
			fprintf(fo, "%s\n", bg);
			return;
		}
		if (isspace(*pt))
			bl = pt;
E 34
E 17
	}
I 34
	putc('\n', fo);
E 34
D 17
	putc('\n', fo);
E 17
}

/*
 * Save the outgoing mail on the passed file.
 */

D 26
savemail(name, hp, fi)
E 26
I 26
/*ARGSUSED*/
I 47
int
E 47
savemail(name, fi)
E 26
	char name[];
D 26
	struct header *hp;
	FILE *fi;
E 26
I 26
	register FILE *fi;
E 26
{
	register FILE *fo;
D 26
	register int c;
	long now;
E 26
I 26
	char buf[BUFSIZ];
	register i;
	time_t now, time();
E 26
D 33
	char *n;
E 33
I 26
	char *ctime();
E 26

D 44
	if ((fo = fopen(name, "a")) == NULL) {
E 44
I 44
	if ((fo = Fopen(name, "a")) == NULL) {
E 44
		perror(name);
D 26
		return(-1);
E 26
I 26
		return (-1);
E 26
	}
D 27
	time(&now);
E 27
I 27
	(void) time(&now);
E 27
D 26
	n = rflag;
	if (n == NOSTR)
E 26
I 26
D 33
	if ((n = rflag) == NOSTR)
E 26
		n = myname;
	fprintf(fo, "From %s %s", n, ctime(&now));
E 33
I 33
	fprintf(fo, "From %s %s", myname, ctime(&now));
E 33
D 37
	rewind(fi);
E 37
D 26
	for (c = getc(fi); c != EOF; c = getc(fi))
		putc(c, fo);
	fprintf(fo, "\n");
E 26
I 26
	while ((i = fread(buf, 1, sizeof buf, fi)) > 0)
D 27
		fwrite(buf, 1, i, fo);
	putc('\n', fo);
E 26
	fflush(fo);
E 27
I 27
		(void) fwrite(buf, 1, i, fo);
	(void) putc('\n', fo);
	(void) fflush(fo);
E 27
	if (ferror(fo))
		perror(name);
D 27
	fclose(fo);
E 27
I 27
D 44
	(void) fclose(fo);
E 44
I 44
	(void) Fclose(fo);
E 44
I 37
	rewind(fi);
E 37
E 27
D 26
	return(0);
E 26
I 26
	return (0);
E 26
}
E 1
