h56943
s 00022/00000/00425
d D 8.2 95/04/20 09:59:06 dab 50 49
c Add support for "inc" command and "autoinc" variable.
c Recognize timestamps in From lines created by SysV/Solaris
c Recognize MAILRC env variable for .mailrc location
c Change tty handling from sgtty to termios
c Turn off EXTPROC when editing headers so that it works
c correctly with Linemode telnet.
e
s 00002/00002/00423
d D 8.1 93/06/06 15:07:07 bostic 49 48
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00022/00011/00403
d D 5.23 92/06/26 12:03:02 bostic 48 47
c quad's broke it -- prototyped it rather than figure out the problem
e
s 00002/00001/00412
d D 5.22 91/04/01 08:59:34 bostic 47 46
c ANSI
e
s 00010/00014/00403
d D 5.21 90/06/25 00:01:51 edward 46 45
c remove call of _fwalk
e
s 00009/00016/00408
d D 5.20 90/06/15 22:24:51 edward 45 44
c show-rcpt added
e
s 00001/00001/00423
d D 5.19 89/05/11 09:43:58 bostic 44 43
c file reorg, pathnames.h, paths.h
e
s 00001/00001/00423
d D 5.18 89/01/16 01:34:29 edward 43 42
c don't catch SIGCONT, catch the stop signals instead,
c cleaned up quitting of mail and signal catch in general,
c could use more work
e
s 00002/00002/00422
d D 5.17 88/12/23 03:02:10 edward 42 41
c added linesize argument to readline()
e
s 00006/00011/00418
d D 5.16 88/07/08 19:41:59 edward 41 40
c removed some functions in the C library
e
s 00001/00032/00428
d D 5.15 88/07/07 22:57:12 edward 40 39
c got rid of unused command "local" and some undocumented command names
e
s 00001/00001/00459
d D 5.14 88/07/07 09:34:51 edward 39 38
c merged even more functionality into send()
e
s 00001/00004/00459
d D 5.13 88/07/07 06:55:22 edward 38 37
c removed some unnecessary global vars, dynamically allocate some others,
c added spreserve to fix the no sreset when sourcing kludge
e
s 00006/00019/00457
d D 5.12 88/07/07 02:48:20 edward 37 36
c rationalized calling of editors and starting processes in general
e
s 00012/00007/00464
d D 5.11 88/06/29 21:01:21 bostic 36 35
c install approved copyright notice
e
s 00003/00003/00468
d D 5.10 88/06/29 19:03:47 edward 35 34
c popen to Popen, pclose to Pclose, never call a shell in popen
e
s 00001/00001/00470
d D 5.9 88/06/17 15:39:00 edward 34 33
c some general cleanup
e
s 00002/00001/00469
d D 5.8 88/06/16 21:50:39 edward 33 32
c replaced intty and outtty by value("interactive"), ~ only in interactive mode
e
s 00001/00001/00469
d D 5.7 88/06/16 19:23:08 edward 32 31
c let "crt" default to the screen height from TIOCGWINSZ
e
s 00001/00001/00469
d D 5.6 88/06/09 22:24:31 edward 31 30
c new commands saveignore, saveretain, and savediscard
e
s 00011/00005/00459
d D 5.5 88/02/18 17:03:26 bostic 30 29
c written by Kurt Shoens; added Berkeley specific header
e
s 00034/00082/00430
d D 5.4 87/05/18 12:28:35 edward 29 28
c major rework: made faster, cleaned up, obsolete code removed,
c the whole thing should be chucked and written from scratch
e
s 00007/00004/00505
d D 5.3 85/09/15 17:15:13 serge 28 27
c if PAGER variable is set, use it to page messages, instead of /usr/ucb/more
e
s 00001/00001/00508
d D 5.2 85/06/21 17:06:31 mckusick 27 26
c botched copyright
e
s 00007/00001/00502
d D 5.1 85/06/07 09:44:11 dist 26 25
c Add copyright
e
s 00036/00007/00467
d D 2.14 85/06/07 02:47:29 serge 25 24
c added "more" command
e
s 00001/00002/00473
d D 2.13 84/08/08 17:05:54 ralph 24 23
c fix stdio flushing, don't mess with stdio buffers
e
s 00004/00003/00471
d D 2.12 83/08/11 22:13:17 sam 23 22
c standardize sccs keyword lines
e
s 00001/00003/00473
d D 2.11 83/06/12 11:16:57 sam 22 21
c new signals
e
s 00030/00000/00446
d D 2.10 83/01/29 19:20:02 leres 21 19
c Added local()
e
s 00010/00000/00446
d R 2.10 83/01/29 18:55:30 leres 20 19
c Added local()
e
s 00001/00001/00445
d D 2.9 82/10/21 05:36:29 carl 19 18
c Changes to support long mail sizes (long m_size).
e
s 00024/00005/00422
d D 2.8 82/07/28 23:03:34 kurt 18 17
c changed type() to honor your ignored header fields; 
c added routine Type() to print messages with ignored fields. 
c 
e
s 00001/00000/00426
d D 2.7 82/07/26 17:05:30 kurt 17 16
c added call on sigchild() after a fork to fix up retrofit signals 
c 
e
s 00000/00000/00426
d D 2.6 82/03/15 09:43:52 kurt 16 14
i 15
c Included Eric's branch changes to remove vax and vmunix 
c dependencies. 
c 
e
s 00004/00001/00364
d D 2.2.1.1 82/03/15 09:32:55 kurt 15 11
c Eric Allman's fixes to remove VAX and VMUNIX dependencies
e
s 00003/00013/00420
d D 2.5 82/02/17 22:52:32 kurt 14 13
c changed the folders command to use execlp instead of 
c sh -c for speed.  changed to use getfold() to find folder name. 
c 
e
s 00039/00000/00394
d D 2.4 82/02/14 19:48:40 kurt 13 12
c added routine folders() for listing all folders in maildir. 
c 
e
s 00035/00006/00359
d D 2.3 81/12/10 12:53:53 kurt 12 11
c changed header command and scrolling command to determine 
c size of "page" of headers by looking at baud rate the user option 
c "screen" 
c 
e
s 00003/00003/00362
d D 2.2 81/09/19 16:51:26 kurt 11 10
c moved some interrupt sensitive code around, mainly to clear 
c pipef before pclose 
c 
e
s 00000/00000/00365
d D 2.1 81/07/01 11:07:59 kurt 10 9
c Release to Heidi Stettner
e
s 00004/00004/00361
d D 1.9 81/04/01 12:42:00 kurt 9 8
c changed calls to signal to sigset
e
s 00019/00000/00346
d D 1.8 81/03/20 15:22:38 kas 8 7
c changed header printing to show mboxed messages with M;
c added routine mboxit to mark a message as destined for mbox
e
s 00001/00001/00345
d D 1.7 81/03/13 12:40:46 kas 7 6
c moved signal call to fix broken pipe problem
e
s 00002/00002/00344
d D 1.6 81/02/06 09:34:20 kas 6 5
c New nameof takes two args
e
s 00007/00004/00339
d D 1.5 81/01/23 14:19:08 kas 5 4
c Changed headers command to be reluctant to change dot;
c Changed header printing to indicate current message with >
e
s 00004/00004/00339
d D 1.4 80/10/17 00:19:10 kas 4 3
c Changed the computation of the disposition character on
c header printing so that new messages are always flagged with N,
c and old but unread messages with U; other cases of MNEW/MREAD are
c no longer flagged
e
s 00004/00000/00339
d D 1.3 80/10/16 18:41:46 kas 3 2
c output of message headers now includes 'N' if the message is
c new (arrived since previous session) and 'U' is message is unread.
e
s 00052/00006/00287
d D 1.2 80/10/09 13:25:00 kas 2 1
c Made output of messages subject to filtering through
c ``more'' if the total output would be > value("crt")
e
s 00293/00000/00000
d D 1.1 80/10/08 09:49:17 kas 1 0
c date and time created 80/10/08 09:49:17 by kas
e
u
U
f b 
t
T
I 26
D 45
/*
 * Copyright (c) 1980 Regents of the University of California.
E 45
I 45
/*-
D 49
 * Copyright (c) 1980 The Regents of the University of California.
E 45
D 30
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 30
I 30
 * All rights reserved.
E 49
I 49
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 49
 *
D 45
 * Redistribution and use in source and binary forms are permitted
D 36
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 36
I 36
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
E 45
I 45
 * %sccs.include.redist.c%
E 45
E 36
E 30
 */

E 26
I 1
D 23
#
E 23
I 23
D 30
#ifndef lint
D 27
static char sccsid[] = "%W% (Berkeley) %G%";
E 27
I 27
static char *sccsid = "%W% (Berkeley) %G%";
E 27
D 26
#endif
E 26
I 26
#endif not lint
E 30
I 30
D 36
#ifdef notdef
E 36
I 36
#ifndef lint
E 36
static char sccsid[] = "%W% (Berkeley) %G%";
D 36
#endif /* notdef */
E 36
I 36
#endif /* not lint */
E 36
E 30
E 26

E 23
#include "rcv.h"
I 48
#include "extern.h"
E 48
D 37
#include <sys/stat.h>
I 29
#include <sys/wait.h>
E 37
E 29

/*
 * Mail -- a mail program
 *
 * User commands.
 */
D 23

static char *SccsId = "%W% %G%";
E 23

/*
 * Print the current active headings.
I 5
 * Don't change dot if invoker didn't give an argument.
E 5
 */

static int screen;

I 48
int
E 48
headers(msgvec)
	int *msgvec;
{
	register int n, mesg, flag;
	register struct message *mp;
I 12
	int size;
E 12

I 12
	size = screensize();
E 12
	n = msgvec[0];
	if (n != 0)
D 12
		screen = (n-1)/SCREEN;
E 12
I 12
		screen = (n-1)/size;
E 12
	if (screen < 0)
		screen = 0;
D 12
	mp = &message[screen * SCREEN];
E 12
I 12
	mp = &message[screen * size];
E 12
	if (mp >= &message[msgCount])
D 12
		mp = &message[msgCount - SCREEN];
E 12
I 12
		mp = &message[msgCount - size];
E 12
	if (mp < &message[0])
		mp = &message[0];
	flag = 0;
	mesg = mp - &message[0];
D 5
	dot = mp;
E 5
I 5
	if (dot != &message[n-1])
		dot = mp;
E 5
	for (; mp < &message[msgCount]; mp++) {
		mesg++;
		if (mp->m_flag & MDELETED)
			continue;
D 12
		if (flag++ >= SCREEN)
E 12
I 12
		if (flag++ >= size)
E 12
			break;
		printhead(mesg);
D 38
		sreset();
E 38
	}
	if (flag == 0) {
		printf("No more mail.\n");
		return(1);
	}
	return(0);
}

/*
I 21
D 40
 * Set the list of alternate names for out host.
 */
local(namelist)
	char **namelist;
{
	register int c;
	register char **ap, **ap2, *cp;

	c = argcount(namelist) + 1;
	if (c == 1) {
		if (localnames == 0)
			return(0);
		for (ap = localnames; *ap; ap++)
			printf("%s ", *ap);
		printf("\n");
		return(0);
	}
	if (localnames != 0)
		cfree((char *) localnames);
D 29
	localnames = (char **) calloc(c, sizeof (char *));
E 29
I 29
	localnames = (char **) calloc((unsigned) c, sizeof (char *));
E 29
	for (ap = namelist, ap2 = localnames; *ap; ap++, ap2++) {
D 29
		cp = (char *) calloc(strlen(*ap) + 1, sizeof (char));
E 29
I 29
		cp = (char *) calloc((unsigned) strlen(*ap) + 1, sizeof (char));
E 29
		strcpy(cp, *ap);
		*ap2 = cp;
	}
	*ap2 = 0;
	return(0);
}

/*
E 21
 * Scroll to the next/previous screen
E 40
I 40
 * Scroll to the next/previous screen
E 40
 */
I 48
int
E 48
D 40

E 40
scroll(arg)
	char arg[];
{
D 12
	register int s;
E 12
I 12
	register int s, size;
E 12
	int cur[1];

	cur[0] = 0;
I 12
	size = screensize();
E 12
	s = screen;
	switch (*arg) {
	case 0:
	case '+':
		s++;
D 12
		if (s*SCREEN > msgCount) {
E 12
I 12
		if (s * size > msgCount) {
E 12
			printf("On last screenful of messages\n");
			return(0);
		}
		screen = s;
		break;

	case '-':
		if (--s < 0) {
			printf("On first screenful of messages\n");
			return(0);
		}
		screen = s;
		break;

	default:
		printf("Unrecognized scrolling command \"%s\"\n", arg);
		return(1);
	}
	return(headers(cur));
}

I 12
/*
D 29
 * Compute what the screen size should be.
 * We use the following algorithm:
 *	If user specifies with screen option, use that.
 *	If baud rate < 1200, use  5
 *	If baud rate = 1200, use 10
 *	If baud rate > 1200, use 20
E 29
I 29
 * Compute screen size.
E 29
 */
I 48
int
E 48
screensize()
{
D 29
	register char *cp;
	register int s;
I 25
#ifdef	TIOCGWINSZ
	struct winsize ws;
#endif
E 29
I 29
	int s;
	char *cp;
E 29
E 25

D 29
	if ((cp = value("screen")) != NOSTR) {
		s = atoi(cp);
		if (s > 0)
			return(s);
	}
	if (baud < B1200)
		s = 5;
	else if (baud == B1200)
		s = 10;
I 25
#ifdef	TIOCGWINSZ
	else if (ioctl(fileno(stdout), TIOCGWINSZ, &ws) == 0 && ws.ws_row != 0)
		s = ws.ws_row - 4;
#endif
E 25
	else
		s = 20;
	return(s);
E 29
I 29
	if ((cp = value("screen")) != NOSTR && (s = atoi(cp)) > 0)
		return s;
	return screenheight - 4;
E 29
}
E 12

/*
 * Print out the headlines for each message
 * in the passed message list.
 */
D 48

E 48
I 48
int
E 48
from(msgvec)
	int *msgvec;
{
	register int *ip;

D 38
	for (ip = msgvec; *ip != NULL; ip++) {
E 38
I 38
	for (ip = msgvec; *ip != NULL; ip++)
E 38
		printhead(*ip);
D 38
		sreset();
	}
E 38
	if (--ip >= msgvec)
		dot = &message[*ip - 1];
	return(0);
}

/*
 * Print out the header of a specific message.
 * This is a slight improvement to the standard one.
 */
D 48

E 48
I 48
void
E 48
printhead(mesg)
I 48
	int mesg;
E 48
{
	struct message *mp;
D 29
	FILE *ibuf;
E 29
D 5
	char headline[LINESIZE], wcount[10], *subjline, dispc;
E 5
I 5
D 28
	char headline[LINESIZE], wcount[10], *subjline, dispc, curind;
E 28
I 28
	char headline[LINESIZE], wcount[LINESIZE], *subjline, dispc, curind;
E 28
E 5
	char pbuf[BUFSIZ];
D 29
	int s;
E 29
	struct headline hl;
D 29
	register char *cp;
E 29
I 29
	int subjlen;
I 45
	char *name;
E 45
E 29

	mp = &message[mesg-1];
D 29
	ibuf = setinput(mp);
	readline(ibuf, headline);
	subjline = hfield("subject", mp);
	if (subjline == NOSTR)
E 29
I 29
D 42
	readline(setinput(mp), headline);
E 42
I 42
	(void) readline(setinput(mp), headline, LINESIZE);
E 42
	if ((subjline = hfield("subject", mp)) == NOSTR)
E 29
		subjline = hfield("subj", mp);
D 29

E 29
	/*
	 * Bletch!
	 */
D 29

	if (subjline != NOSTR && strlen(subjline) > 28)
		subjline[29] = '\0';
E 29
I 5
	curind = dot == mp ? '>' : ' ';
E 5
	dispc = ' ';
	if (mp->m_flag & MSAVED)
		dispc = '*';
	if (mp->m_flag & MPRESERVE)
		dispc = 'P';
I 3
D 4
	if ((mp->m_flag & MREAD) == 0)
		dispc = 'U';
	if (mp->m_flag & MNEW)
E 4
I 4
	if ((mp->m_flag & (MREAD|MNEW)) == MNEW)
E 4
		dispc = 'N';
I 4
	if ((mp->m_flag & (MREAD|MNEW)) == 0)
		dispc = 'U';
I 8
	if (mp->m_flag & MBOX)
		dispc = 'M';
E 8
E 4
E 3
	parse(headline, &hl, pbuf);
D 19
	sprintf(wcount, " %d/%d", mp->m_lines, mp->m_size);
E 19
I 19
D 29
	sprintf(wcount, " %d/%ld", mp->m_lines, mp->m_size);
E 19
	s = strlen(wcount);
	cp = wcount + s;
	while (s < 7)
		s++, *cp++ = ' ';
	*cp = '\0';
	if (subjline != NOSTR)
D 5
		printf("%c%3d %-8s %16.16s %s \"%s\"\n", dispc, mesg,
E 5
I 5
		printf("%c%c%3d %-8s %16.16s %s \"%s\"\n", curind, dispc, mesg,
E 5
D 6
		    nameof(mp), hl.l_date, wcount, subjline);
E 6
I 6
		    nameof(mp, 0), hl.l_date, wcount, subjline);
E 29
I 29
D 45
	sprintf(wcount, "%3d/%-4ld", mp->m_lines, mp->m_size);
E 45
I 45
	sprintf(wcount, "%3d/%-5ld", mp->m_lines, mp->m_size);
E 45
	subjlen = screenwidth - 50 - strlen(wcount);
I 45
	name = value("show-rcpt") != NOSTR ?
		skin(hfield("to", mp)) : nameof(mp, 0);
E 45
	if (subjline == NOSTR || subjlen < 0)		/* pretty pathetic */
		printf("%c%c%3d %-20.20s  %16.16s %s\n",
D 45
			curind, dispc, mesg, nameof(mp, 0), hl.l_date, wcount);
E 45
I 45
			curind, dispc, mesg, name, hl.l_date, wcount);
E 45
E 29
E 6
	else
D 5
		printf("%c%3d %-8s %16.16s %s\n", dispc, mesg,
E 5
I 5
D 29
		printf("%c%c%3d %-8s %16.16s %s\n", curind, dispc, mesg,
E 5
D 6
		    nameof(mp), hl.l_date, wcount);
E 6
I 6
		    nameof(mp, 0), hl.l_date, wcount);
E 29
I 29
		printf("%c%c%3d %-20.20s  %16.16s %s \"%.*s\"\n",
D 45
			curind, dispc, mesg, nameof(mp, 0), hl.l_date, wcount,
E 45
I 45
			curind, dispc, mesg, name, hl.l_date, wcount,
E 45
			subjlen, subjline);
E 29
E 6
}

/*
 * Print out the value of dot.
 */
D 48

E 48
I 48
int
E 48
pdot()
{
	printf("%d\n", dot - &message[0] + 1);
	return(0);
}

/*
 * Print out all the possible commands.
 */
D 48

E 48
I 48
int
E 48
pcmdlist()
{
	register struct cmd *cp;
	register int cc;
	extern struct cmd cmdtab[];

	printf("Commands are:\n");
	for (cc = 0, cp = cmdtab; cp->c_name != NULL; cp++) {
		cc += strlen(cp->c_name) + 2;
		if (cc > 72) {
			printf("\n");
			cc = strlen(cp->c_name) + 2;
		}
		if ((cp+1)->c_name != NOSTR)
			printf("%s, ", cp->c_name);
		else
			printf("%s\n", cp->c_name);
	}
	return(0);
}

/*
I 25
 * Paginate messages, honor ignored fields.
 */
I 48
int
E 48
more(msgvec)
	int *msgvec;
{
	return (type1(msgvec, 1, 1));
}

/*
 * Paginate messages, even printing ignored fields.
 */
I 48
int
E 48
More(msgvec)
	int *msgvec;
{

	return (type1(msgvec, 0, 1));
}

/*
E 25
D 18
 * Type out the messages requested.
E 18
I 18
 * Type out messages, honor ignored fields.
E 18
 */
I 48
int
E 48
I 18
type(msgvec)
	int *msgvec;
{
E 18

I 18
D 25
	return(type1(msgvec, 1));
E 25
I 25
	return(type1(msgvec, 1, 0));
E 25
}

/*
 * Type out messages, even printing ignored fields.
 */
I 48
int
E 48
Type(msgvec)
	int *msgvec;
{

D 25
	return(type1(msgvec, 0));
E 25
I 25
	return(type1(msgvec, 0, 0));
E 25
}

/*
 * Type out the messages requested.
 */
E 18
I 2
jmp_buf	pipestop;
D 48

E 48
I 48
int
E 48
E 2
D 18
type(msgvec)
E 18
I 18
D 25
type1(msgvec, doign)
E 25
I 25
type1(msgvec, doign, page)
E 25
E 18
	int *msgvec;
I 48
	int doign, page;
E 48
{
	register *ip;
	register struct message *mp;
D 41
	register int mesg;
E 41
D 2
	int c;
	FILE *ibuf;
E 2
I 2
	register char *cp;
D 29
	int c, nlines;
E 29
I 29
	int nlines;
E 29
D 47
	int brokpipe();
E 47
D 29
	FILE *ibuf, *obuf;
E 29
I 29
	FILE *obuf;
I 47
D 48
	void brokpipe();
E 48
E 47
E 29
E 2

I 2
	obuf = stdout;
D 46
	if (setjmp(pipestop)) {
		if (obuf != stdout) {
D 11
			pclose(obuf);
E 11
			pipef = NULL;
I 11
D 35
			pclose(obuf);
E 35
I 35
			Pclose(obuf);
E 35
E 11
		}
D 9
		signal(SIGPIPE, SIG_DFL);
E 9
I 9
D 29
		sigset(SIGPIPE, SIG_DFL);
E 29
I 29
		signal(SIGPIPE, SIG_DFL);
E 29
E 9
		return(0);
	}
E 46
I 46
	if (setjmp(pipestop))
		goto close_pipe;
E 46
D 25
	if (intty && outtty && (cp = value("crt")) != NOSTR) {
		for (ip = msgvec, nlines = 0; *ip && ip-msgvec < msgCount; ip++)
			nlines += message[*ip - 1].m_lines;
		if (nlines > atoi(cp)) {
E 25
I 25
D 33
	if (intty && outtty && (page || (cp = value("crt")) != NOSTR)) {
E 33
I 33
	if (value("interactive") != NOSTR &&
	    (page || (cp = value("crt")) != NOSTR)) {
E 33
I 28
		nlines = 0;
E 28
		if (!page) {
D 28
			nlines = 0;
E 28
			for (ip = msgvec; *ip && ip-msgvec < msgCount; ip++)
				nlines += message[*ip - 1].m_lines;
		}
D 32
		if (page || nlines > atoi(cp)) {
E 32
I 32
		if (page || nlines > (*cp ? atoi(cp) : realscreenheight)) {
E 32
E 25
D 28
			obuf = popen(MORE, "w");
E 28
I 28
			cp = value("PAGER");
			if (cp == NULL || *cp == '\0')
D 44
				cp = MORE;
E 44
I 44
				cp = _PATH_MORE;
E 44
D 35
			obuf = popen(cp, "w");
E 35
I 35
			obuf = Popen(cp, "w");
E 35
E 28
			if (obuf == NULL) {
D 28
				perror(MORE);
E 28
I 28
				perror(cp);
E 28
				obuf = stdout;
D 29
			}
			else {
E 29
I 29
D 46
			} else {
E 29
				pipef = obuf;
E 46
I 46
			} else
E 46
D 9
				signal(SIGPIPE, brokpipe);
E 9
I 9
D 29
				sigset(SIGPIPE, brokpipe);
E 29
I 29
				signal(SIGPIPE, brokpipe);
E 29
E 9
D 46
			}
E 46
		}
	}
E 2
D 29
	for (ip = msgvec; *ip && ip-msgvec < msgCount; ip++) {
E 29
I 29
	for (ip = msgvec; *ip && ip - msgvec < msgCount; ip++) {
E 29
D 41
		mesg = *ip;
		touch(mesg);
		mp = &message[mesg-1];
E 41
I 41
		mp = &message[*ip - 1];
		touch(mp);
E 41
		dot = mp;
D 2
		print(mp);
E 2
I 2
D 18
		print(mp, obuf);
E 18
I 18
D 29
		print(mp, obuf, doign);
E 29
I 29
		if (value("quiet") == NOSTR)
D 41
			fprintf(obuf, "Message %d:\n", mesg);
E 41
I 41
			fprintf(obuf, "Message %d:\n", *ip);
E 41
D 31
		send(mp, obuf, doign);
E 31
I 31
D 39
		send(mp, obuf, doign ? ignore : 0);
E 39
I 39
		(void) send(mp, obuf, doign ? ignore : 0, NOSTR);
E 39
E 31
E 29
E 18
E 2
	}
I 46
close_pipe:
E 46
I 2
D 7
	signal(SIGPIPE, SIG_DFL);
E 7
	if (obuf != stdout) {
D 11
		pclose(obuf);
E 11
D 46
		pipef = NULL;
E 46
I 46
		/*
		 * Ignore SIGPIPE so it can't cause a duplicate close.
		 */
		signal(SIGPIPE, SIG_IGN);
E 46
I 11
D 35
		pclose(obuf);
E 35
I 35
		Pclose(obuf);
I 46
		signal(SIGPIPE, SIG_DFL);
E 46
E 35
E 11
	}
I 7
D 9
	signal(SIGPIPE, SIG_DFL);
E 9
I 9
D 29
	sigset(SIGPIPE, SIG_DFL);
E 29
I 29
D 46
	signal(SIGPIPE, SIG_DFL);
E 46
E 29
E 9
E 7
E 2
	return(0);
}

/*
I 2
 * Respond to a broken pipe signal --
D 46
 * probably caused by using quitting more.
E 46
I 46
 * probably caused by quitting more.
E 46
 */
D 48

E 48
I 47
void
E 47
D 48
brokpipe()
E 48
I 48
brokpipe(signo)
	int signo;
E 48
{
D 15

E 15
I 15
D 22
# ifdef VMUNIX
E 15
D 9
	signal(SIGPIPE, SIG_IGN);
E 9
D 11
	longjmp(pipestop, 1);
E 11
I 9
	sigrelse(SIGPIPE);
I 15
# else
E 22
I 22
D 29
# ifndef VMUNIX
E 22
	signal(SIGPIPE, brokpipe);
# endif
E 29
E 15
I 11
	longjmp(pipestop, 1);
E 11
E 9
}

/*
E 2
D 29
 * Print the indicated message on standard output.
 */

D 2
print(mp)
E 2
I 2
D 18
print(mp, obuf)
E 18
I 18
print(mp, obuf, doign)
E 18
E 2
	register struct message *mp;
I 2
	FILE *obuf;
E 2
{

	if (value("quiet") == NOSTR)
D 2
		printf("Message %2d:\n", mp - &message[0] + 1);
E 2
I 2
		fprintf(obuf, "Message %2d:\n", mp - &message[0] + 1);
E 2
	touch(mp - &message[0] + 1);
D 2
	send(mp, stdout);
E 2
I 2
D 18
	send(mp, obuf);
E 18
I 18
	send(mp, obuf, doign);
E 18
E 2
}

/*
E 29
 * Print the top so many lines of each desired message.
 * The number of lines is taken from the variable "toplines"
 * and defaults to 5.
 */
D 48

E 48
I 48
int
E 48
top(msgvec)
	int *msgvec;
{
	register int *ip;
	register struct message *mp;
D 41
	register int mesg;
E 41
	int c, topl, lines, lineb;
	char *valtop, linebuf[LINESIZE];
	FILE *ibuf;

	topl = 5;
	valtop = value("toplines");
	if (valtop != NOSTR) {
		topl = atoi(valtop);
		if (topl < 0 || topl > 10000)
			topl = 5;
	}
	lineb = 1;
	for (ip = msgvec; *ip && ip-msgvec < msgCount; ip++) {
D 41
		mesg = *ip;
		touch(mesg);
		mp = &message[mesg-1];
E 41
I 41
		mp = &message[*ip - 1];
		touch(mp);
E 41
		dot = mp;
		if (value("quiet") == NOSTR)
D 34
			printf("Message %2d:\n", mesg);
E 34
I 34
D 41
			printf("Message %d:\n", mesg);
E 41
I 41
			printf("Message %d:\n", *ip);
E 41
E 34
		ibuf = setinput(mp);
		c = mp->m_lines;
		if (!lineb)
			printf("\n");
		for (lines = 0; lines < c && lines <= topl; lines++) {
D 29
			if (readline(ibuf, linebuf) <= 0)
E 29
I 29
D 42
			if (readline(ibuf, linebuf) < 0)
E 42
I 42
			if (readline(ibuf, linebuf, LINESIZE) < 0)
E 42
E 29
				break;
			puts(linebuf);
			lineb = blankline(linebuf);
		}
	}
	return(0);
}

/*
 * Touch all the given messages so that they will
 * get mboxed.
 */
I 48
int
E 48
D 41

E 41
stouch(msgvec)
	int msgvec[];
{
	register int *ip;

	for (ip = msgvec; *ip != 0; ip++) {
D 4
		touch(*ip);
E 4
		dot = &message[*ip-1];
I 4
		dot->m_flag |= MTOUCH;
I 8
		dot->m_flag &= ~MPRESERVE;
	}
	return(0);
}

/*
 * Make sure all passed messages get mboxed.
 */
D 48

E 48
I 48
int
E 48
mboxit(msgvec)
	int msgvec[];
{
	register int *ip;

	for (ip = msgvec; *ip != 0; ip++) {
		dot = &message[*ip-1];
		dot->m_flag |= MTOUCH|MBOX;
E 8
E 4
		dot->m_flag &= ~MPRESERVE;
	}
	return(0);
}
I 13

/*
 * List the folders the user currently has.
 */
I 48
int
E 48
folders()
{
D 14
	char *maildir, *shell;
E 14
D 29
	char dirname[BUFSIZ], cmd[BUFSIZ];
	int pid, s, e;
E 29
I 29
	char dirname[BUFSIZ];
D 37
	int pid, e;
	union wait s;
E 37
I 37
	char *cmd;
E 37
E 29

D 14
	if ((maildir = value("maildir")) == NOSTR) {
		printf("No value set for \"maildir\"\n");
E 14
I 14
	if (getfold(dirname) < 0) {
		printf("No value set for \"folder\"\n");
E 14
D 37
		return(-1);
E 37
I 37
D 43
		return -1;
E 43
I 43
		return 1;
E 43
E 37
	}
D 14
	if (*maildir != '/')
		sprintf(dirname, "%s/%s", homedir, maildir);
	else
		strcpy(dirname, maildir);
	sprintf(cmd, "ls %s", dirname);
	shell = value("SHELL");
	if (shell == 0)
		shell = SHELL;
E 14
D 37
	switch ((pid = fork())) {
	case 0:
I 17
D 29
		sigchild();
E 29
E 17
D 14
		execl(shell, "sh", "-c", cmd, 0);
E 14
I 14
		execlp("ls", "ls", dirname, 0);
E 14
D 24
		clrbuf(stdout);
D 14
		perror(shell);
E 14
		exit(1);
E 24
I 24
		_exit(1);
E 24

	case -1:
		perror("fork");
		return(-1);

	default:
		while ((e = wait(&s)) != -1 && e != pid)
			;
	}
	return(0);
E 37
I 37
	if ((cmd = value("LISTER")) == NOSTR)
		cmd = "ls";
D 48
	(void) run_command(cmd, 0, -1, -1, dirname, NOSTR);
E 48
I 48
	(void) run_command(cmd, 0, -1, -1, dirname, NOSTR, NOSTR);
E 48
	return 0;
E 37
}
I 50

/*
 * Update the mail file with any new messages that have
 * come in since we started reading mail.
 */
inc()
{
	int nmsg, mdot;

	nmsg = incfile();

	if (nmsg == 0) {
		printf("No new mail.\n");
	} else if (nmsg > 0) {
		mdot = newfileinfo(msgCount - nmsg);
		dot = &message[mdot - 1];
	} else {
		printf("\"inc\" command failed...\n");
	}

	return 0;
}
E 50
E 13
E 1
