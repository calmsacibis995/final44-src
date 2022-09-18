h03875
s 00001/00001/00703
d D 8.2 95/04/20 09:59:07 dab 58 57
c Add support for "inc" command and "autoinc" variable.
c Recognize timestamps in From lines created by SysV/Solaris
c Recognize MAILRC env variable for .mailrc location
c Change tty handling from sgtty to termios
c Turn off EXTPROC when editing headers so that it works
c correctly with Linemode telnet.
e
s 00002/00002/00702
d D 8.1 93/06/06 15:07:15 bostic 57 56
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00701
d D 5.26 93/01/22 17:14:34 bostic 56 55
c cfree -> cfree
e
s 00032/00015/00672
d D 5.25 92/06/26 12:03:04 bostic 55 54
c quad's broke it -- prototyped it rather than figure out the problem
e
s 00002/00002/00685
d D 5.24 90/06/25 00:01:38 edward 54 53
c remove call of _fwalk
e
s 00001/00011/00686
d D 5.23 90/06/01 16:57:35 bostic 53 52
c new copyright notice
e
s 00002/00002/00695
d D 5.22 89/11/24 23:07:11 edward 52 51
c sig_t
e
s 00004/00004/00693
d D 5.21 89/05/11 09:44:00 bostic 51 50
c file reorg, pathnames.h, paths.h
e
s 00000/00004/00697
d D 5.20 89/04/22 15:27:43 edward 50 49
c no more SIGCONT
e
s 00001/00005/00700
d D 5.19 89/02/13 23:51:53 edward 49 48
c more accurate error message when editing system mailbox
e
s 00007/00011/00698
d D 5.18 89/01/16 01:34:21 edward 48 47
c don't catch SIGCONT, catch the stop signals instead,
c cleaned up quitting of mail and signal catch in general,
c could use more work
e
s 00002/00000/00707
d D 5.17 88/07/19 18:34:30 edward 47 46
c replying to a message implies reading it
e
s 00007/00007/00700
d D 5.16 88/07/08 19:41:53 edward 46 45
c removed some functions in the C library
e
s 00006/00009/00701
d D 5.15 88/07/07 04:51:36 edward 45 44
c fixed up some command argument types
e
s 00019/00055/00691
d D 5.14 88/07/07 02:48:14 edward 44 43
c rationalized calling of editors and starting processes in general
e
s 00012/00007/00734
d D 5.13 88/06/29 21:01:26 bostic 43 42
c install approved copyright notice
e
s 00001/00001/00740
d D 5.12 88/06/19 19:59:15 edward 42 41
c reedit bug fix
e
s 00058/00097/00683
d D 5.11 88/06/19 04:21:01 edward 41 40
c rationalized mail sending code: keep h_to, h_cc, h_bcc, h_smopts as lists
c not strings; h_seq deleted; now understands <...> addresses; and many more.
c should be much cleaner and somewhat faster.
e
s 00000/00002/00780
d D 5.10 88/06/18 14:54:24 edward 40 39
c removed support for -r, -h, and rmail
e
s 00001/00001/00781
d D 5.9 88/06/17 15:38:52 edward 39 38
c some general cleanup
e
s 00007/00092/00775
d D 5.8 88/06/17 15:05:09 edward 38 37
c cleaned up file handling code, now allows "mbox" variable
e
s 00000/00002/00867
d D 5.7 88/06/16 17:41:11 edward 37 36
c prehistoric (e.g., pre-sendmail) code removed
e
s 00009/00002/00860
d D 5.6 88/06/11 01:15:51 edward 36 35
c added -c -b -t flags, end echo with newline,
c from Tom Newcomb (newcomb@arpa)
e
s 00011/00005/00851
d D 5.5 88/02/18 17:03:32 bostic 35 34
c written by Kurt Shoens; added Berkeley specific header
e
s 00038/00033/00818
d D 5.4 87/05/18 12:28:20 edward 34 33
c major rework: made faster, cleaned up, obsolete code removed,
c the whole thing should be chucked and written from scratch
e
s 00040/00006/00811
d D 5.3 85/09/15 17:12:31 serge 33 32
c added unread/Unread command (marks messages as not read)
c if Replyall is set, reverse sense of "reply" and "Reply"
c always print headers of first few messages when editing a different file
e
s 00001/00001/00816
d D 5.2 85/06/21 17:07:33 mckusick 32 31
c botched copyright
e
s 00007/00001/00810
d D 5.1 85/06/06 10:23:32 dist 31 30
c Add copyright
e
s 00003/00003/00808
d D 2.14 83/08/11 22:13:41 sam 30 29
c standardize sccs keyword lines
e
s 00009/00009/00802
d D 2.13 83/06/28 18:09:23 leres 29 27
c Added a few calls to skin() to remove comments when replying. Took out
c flag to use commas when constructing the address list since it isn't needed
c if comments aren't present.
e
s 00008/00008/00803
d R 2.13 83/06/28 17:57:37 leres 28 27
c Added a few calls to skin() to remove comments when replying. Took out
c flag to use commas when construting the address list since it isn't needed
c if comments aren't present.
e
s 00002/00002/00809
d D 2.12 83/06/28 17:33:58 leres 27 26
c Modified to seperate addresses with commas so that commented addresses
c work correctly.
e
s 00016/00005/00795
d D 2.11 83/06/05 18:20:23 leres 26 23
c Modified to use the "From:" line (if one exists) when replying rather
c than the "From" line (i.e. the first line in the message).
e
s 00015/00007/00793
d R 2.11 83/01/29 19:00:50 leres 25 23
c Broke alternates() into two routines so that part of it (the routine
c makelist()) could be used for the local command
e
s 00015/00007/00793
d R 2.11 83/01/29 18:58:40 leres 24 23
c Broke alternates() up into two routines so that the list
e
s 00008/00008/00792
d D 2.10 83/01/22 15:48:27 leres 23 22
c Modified to use perror() to report failure to open the HELPFILE. Changed
c calls to delname() to include function to compare strings with. Removed
c declaration of netmap() (since it's already in def.h)
e
s 00001/00001/00799
d D 2.9 82/10/21 05:38:46 carl 22 21
c Changes to support long mail sizes (long m_size).
c Call to msize(x) replaced by the inline expansion x->m_size.
e
s 00003/00001/00797
d D 2.8 82/07/28 15:32:33 kurt 21 20
c changed file() to report its own error message when setfile returns an error 
c 
e
s 00002/00000/00796
d D 2.7 82/07/26 17:06:33 kurt 20 19
c added calls on sigchild() after forks to fix up retrofit signals 
c 
e
s 00011/00003/00785
d D 2.6 82/02/20 20:07:59 kurt 19 18
c changed file() to call setfile() with proper arg for isedit; 
c changed getfilename() to return through a reference parameter whether 
c the named passed it is for system mailbox to facilitate above fix. 
c 
e
s 00003/00001/00785
d D 2.5 82/02/13 14:44:40 kurt 18 17
c changed the file command to print the "new file info" 
c when a new file is successfully selected. 
c 
e
s 00002/00000/00784
d D 2.4 81/10/26 20:09:41 kurt 17 16
c changed rexit() to leave an empty file for -T. 
c 
e
s 00003/00000/00781
d D 2.3 81/10/26 12:11:02 kurt 16 15
c fixed alternate name implementation to do CC names, too. 
c 
e
s 00038/00001/00743
d D 2.2 81/09/16 14:31:34 kurt 15 14
c changed respond() to delname all alternate names specified by user; 
c added code for "alternates" command to specify alternate names 
c 
e
s 00000/00000/00744
d D 2.1 81/07/01 11:08:11 kurt 14 13
c Release to Heidi Stettner
e
s 00006/00006/00738
d D 1.13 81/04/01 12:42:40 kurt 13 12
c changed calls to signal to sigset/sigsys
e
s 00001/00000/00743
d D 1.12 81/03/20 15:25:35 kas 12 11
c preserving clears mbox bit
e
s 00001/00001/00742
d D 1.11 81/03/17 16:42:28 kas 11 10
c changed echo command to put all output on one line
e
s 00003/00003/00740
d D 1.10 81/03/11 15:54:20 kas 10 9
c fixed calls on nameof to obey new convention of "reply type"
e
s 00026/00013/00717
d D 1.9 81/02/06 09:35:41 kas 9 8
c Changed reply to send only to reply-to field if such given
e
s 00028/00004/00702
d D 1.8 81/01/26 10:30:38 kas 8 7
c changed reply code to change replied subject to Re: &
e
s 00001/00006/00705
d D 1.7 81/01/13 23:33:32 kas 7 6
c the file command now calls newfileinfo() to print information
c about the current message file
e
s 00010/00005/00701
d D 1.6 80/10/25 21:29:21 kas 6 5
c getfilename() is careful not to clobber mailname, since quit()
c needs it intact
e
s 00084/00002/00622
d D 1.5 80/10/18 18:10:52 kas 5 4
c fixed # in file() command -- prevfile is now set up right
c added conditional command implementations ifcmd(), elsecmd(), endifcmd()
e
s 00038/00002/00586
d D 1.4 80/10/17 00:26:02 kas 4 3
c added meta character expansion to the file command, implementing
c # wrong
e
s 00047/00007/00541
d D 1.3 80/10/09 13:27:15 kas 3 2
c Added optional argument to "file" command which allows
c one to switch mail files during execution.
e
s 00059/00002/00489
d D 1.2 80/10/08 18:48:47 kas 2 1
c Made shell escapes expand !'s to previous command
e
s 00491/00000/00000
d D 1.1 80/10/08 09:49:26 kas 1 0
c date and time created 80/10/08 09:49:26 by kas
e
u
U
f b 
t
T
I 31
/*
D 57
 * Copyright (c) 1980 Regents of the University of California.
D 35
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 35
I 35
 * All rights reserved.
E 57
I 57
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 57
 *
D 53
 * Redistribution and use in source and binary forms are permitted
D 43
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 43
I 43
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
E 53
I 53
 * %sccs.include.redist.c%
E 53
E 43
E 35
 */

E 31
I 1
D 30
#
E 30
I 30
D 35
#ifndef lint
D 32
static char sccsid[] = "%W% (Berkeley) %G%";
E 32
I 32
static char *sccsid = "%W% (Berkeley) %G%";
E 32
D 31
#endif
E 31
I 31
#endif not lint
E 35
I 35
D 43
#ifdef notdef
E 43
I 43
#ifndef lint
E 43
static char sccsid[] = "%W% (Berkeley) %G%";
D 43
#endif /* notdef */
E 43
I 43
#endif /* not lint */
E 43
E 35
E 31
E 30

#include "rcv.h"
I 55
#include "extern.h"
E 55
D 44
#include <sys/stat.h>
I 34
#include <sys/wait.h>
E 44
E 34

/*
 * Mail -- a mail program
 *
 * Still more user commands.
 */
D 30

static char *SccsId = "%W% %G%";
E 30

/*
 * Process a shell escape by saving signals, ignoring signals,
 * and forking a sh -c
 */
I 55
int
E 55
D 44

E 44
shell(str)
	char *str;
{
D 34
	int (*sig[2])(), stat[1];
E 34
I 34
D 44
	int (*sigint)(), (*sigquit)();
	union wait stat;
E 34
	register int t;
	char *Shell;
E 44
I 44
D 52
	int (*sigint)() = signal(SIGINT, SIG_IGN);
E 52
I 52
	sig_t sigint = signal(SIGINT, SIG_IGN);
E 52
D 50
	int (*sigcont)() = signal(SIGCONT, SIG_DFL);
E 50
	char *shell;
E 44
I 2
	char cmd[BUFSIZ];
E 2

I 2
D 44
	strcpy(cmd, str);
E 44
I 44
	(void) strcpy(cmd, str);
E 44
	if (bangexp(cmd) < 0)
D 48
		return(-1);
E 48
I 48
		return 1;
E 48
E 2
D 44
	if ((Shell = value("SHELL")) == NOSTR)
		Shell = SHELL;
D 34
	for (t = 2; t < 4; t++)
D 13
		sig[t-2] = signal(t, SIG_IGN);
E 13
I 13
		sig[t-2] = sigset(t, SIG_IGN);
E 34
I 34
	sigint = signal(SIGINT, SIG_IGN);
	sigquit = signal(SIGQUIT, SIG_IGN);
E 34
E 13
	t = vfork();
	if (t == 0) {
I 20
D 34
		sigchild();
E 20
		for (t = 2; t < 4; t++)
			if (sig[t-2] != SIG_IGN)
D 13
				signal(t, SIG_DFL);
E 13
I 13
				sigsys(t, SIG_DFL);
E 34
I 34
		if (sigint != SIG_IGN)
			signal(SIGINT, SIG_DFL);
		if (sigquit != SIG_IGN)
			signal(SIGQUIT, SIG_DFL);
E 34
E 13
D 2
		execl(Shell, Shell, "-c", str, 0);
E 2
I 2
D 33
		execl(Shell, Shell, "-c", cmd, 0);
E 33
I 33
		execl(Shell, Shell, "-c", cmd, (char *)0);
E 33
E 2
		perror(Shell);
		_exit(1);
	}
D 34
	while (wait(stat) != t)
E 34
I 34
	while (wait(&stat) != t)
E 34
		;
	if (t == -1)
		perror("fork");
D 34
	for (t = 2; t < 4; t++)
D 13
		signal(t, sig[t-2]);
E 13
I 13
		sigset(t, sig[t-2]);
E 34
I 34
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
E 44
I 44
	if ((shell = value("SHELL")) == NOSTR)
D 51
		shell = SHELL;
E 51
I 51
		shell = _PATH_CSHELL;
E 51
	(void) run_command(shell, 0, -1, -1, "-c", cmd, NOSTR);
	(void) signal(SIGINT, sigint);
D 50
	(void) signal(SIGCONT, sigcont);
E 50
E 44
E 34
E 13
	printf("!\n");
D 44
	return(0);
E 44
I 44
	return 0;
E 44
}

/*
 * Fork an interactive shell.
 */
D 44

E 44
I 34
/*ARGSUSED*/
I 55
int
E 55
E 34
dosh(str)
	char *str;
{
D 34
	int (*sig[2])(), stat[1];
E 34
I 34
D 44
	int (*sigint)(), (*sigquit)();
	union wait stat;
E 34
	register int t;
	char *Shell;
E 44
I 44
D 52
	int (*sigint)() = signal(SIGINT, SIG_IGN);
E 52
I 52
	sig_t sigint = signal(SIGINT, SIG_IGN);
E 52
D 50
	int (*sigcont)() = signal(SIGCONT, SIG_DFL);
E 50
	char *shell;
E 44
I 34

E 34
D 2

E 2
D 44
	if ((Shell = value("SHELL")) == NOSTR)
		Shell = SHELL;
D 34
	for (t = 2; t < 4; t++)
D 13
		sig[t-2] = signal(t, SIG_IGN);
E 13
I 13
		sig[t-2] = sigset(t, SIG_IGN);
E 34
I 34
	sigint = signal(SIGINT, SIG_IGN);
	sigquit = signal(SIGQUIT, SIG_IGN);
E 34
E 13
	t = vfork();
	if (t == 0) {
I 20
D 34
		sigchild();
E 20
		for (t = 2; t < 4; t++)
			if (sig[t-2] != SIG_IGN)
D 13
				signal(t, SIG_DFL);
E 13
I 13
				sigsys(t, SIG_DFL);
E 34
I 34
		if (sigint != SIG_IGN)
			signal(SIGINT, SIG_DFL);
		if (sigquit != SIG_IGN)
			signal(SIGQUIT, SIG_DFL);
E 34
E 13
D 33
		execl(Shell, Shell, 0);
E 33
I 33
		execl(Shell, Shell, (char *)0);
E 33
		perror(Shell);
		_exit(1);
	}
D 34
	while (wait(stat) != t)
E 34
I 34
	while (wait(&stat) != t)
E 34
		;
	if (t == -1)
		perror("fork");
D 34
	for (t = 2; t < 4; t++)
D 13
		signal(t, sig[t-2]);
E 13
I 13
		sigsys(t, sig[t-2]);
E 34
I 34
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
E 44
I 44
	if ((shell = value("SHELL")) == NOSTR)
D 51
		shell = SHELL;
E 51
I 51
		shell = _PATH_CSHELL;
E 51
D 55
	(void) run_command(shell, 0, -1, -1, NOSTR);
E 55
I 55
	(void) run_command(shell, 0, -1, -1, NOSTR, NOSTR, NOSTR);
E 55
	(void) signal(SIGINT, sigint);
D 50
	(void) signal(SIGCONT, sigcont);
E 50
E 44
E 34
E 13
	putchar('\n');
I 2
D 44
	return(0);
E 44
I 44
	return 0;
E 44
}

/*
 * Expand the shell escape by expanding unescaped !'s into the
 * last issued command where possible.
 */

char	lastbang[128];

I 55
int
E 55
bangexp(str)
	char *str;
{
	char bangbuf[BUFSIZ];
	register char *cp, *cp2;
	register int n;
	int changed = 0;

	cp = str;
	cp2 = bangbuf;
	n = BUFSIZ;
	while (*cp) {
		if (*cp == '!') {
			if (n < strlen(lastbang)) {
overf:
				printf("Command buffer overflow\n");
				return(-1);
			}
			changed++;
			strcpy(cp2, lastbang);
			cp2 += strlen(lastbang);
			n -= strlen(lastbang);
			cp++;
			continue;
		}
		if (*cp == '\\' && cp[1] == '!') {
			if (--n <= 1)
				goto overf;
			*cp2++ = '!';
			cp += 2;
			changed++;
		}
		if (--n <= 1)
			goto overf;
		*cp2++ = *cp++;
	}
	*cp2 = 0;
	if (changed) {
		printf("!%s\n", bangbuf);
		fflush(stdout);
	}
	strcpy(str, bangbuf);
	strncpy(lastbang, bangbuf, 128);
	lastbang[127] = 0;
E 2
	return(0);
}

/*
 * Print out a nice help message from some file or another.
 */

I 55
int
E 55
help()
{
	register c;
	register FILE *f;

D 51
	if ((f = fopen(HELPFILE, "r")) == NULL) {
D 23
		printf("No help just now.\n");
E 23
I 23
		perror(HELPFILE);
E 51
I 51
D 54
	if ((f = fopen(_PATH_HELP, "r")) == NULL) {
E 54
I 54
	if ((f = Fopen(_PATH_HELP, "r")) == NULL) {
E 54
		perror(_PATH_HELP);
E 51
E 23
		return(1);
	}
	while ((c = getc(f)) != EOF)
		putchar(c);
D 54
	fclose(f);
E 54
I 54
	Fclose(f);
E 54
	return(0);
}

/*
 * Change user's working directory.
 */
I 55
int
E 55
D 45

schdir(str)
	char *str;
E 45
I 45
schdir(arglist)
	char **arglist;
E 45
{
D 45
	register char *cp;
E 45
I 45
	char *cp;
E 45

D 45
	for (cp = str; *cp == ' '; cp++)
		;
	if (*cp == '\0')
E 45
I 45
	if (*arglist == NOSTR)
E 45
		cp = homedir;
	else
D 45
		if ((cp = expand(cp)) == NOSTR)
E 45
I 45
		if ((cp = expand(*arglist)) == NOSTR)
E 45
			return(1);
	if (chdir(cp) < 0) {
		perror(cp);
		return(1);
	}
D 45
	return(0);
E 45
I 45
	return 0;
E 45
}

I 55
int
E 55
I 33
respond(msgvec)
	int *msgvec;
{
	if (value("Replyall") == NOSTR)
		return (_respond(msgvec));
	else
		return (_Respond(msgvec));
}

E 33
/*
 * Reply to a list of messages.  Extract each name from the
 * message header and send them off to mail1()
 */
I 55
int
E 55
D 41

E 41
D 33
respond(msgvec)
E 33
I 33
_respond(msgvec)
E 33
	int *msgvec;
{
	struct message *mp;
D 9
	char *cp, buf[2 * LINESIZE], *rcv;
E 9
I 9
D 15
	char *cp, buf[2 * LINESIZE], *rcv, *replyto;
E 15
I 15
D 23
	char *cp, buf[2 * LINESIZE], *rcv, *replyto, **ap;
E 23
I 23
D 34
	char *cp, *cp2, *cp3, *rcv, *replyto;
E 34
I 34
	char *cp, *rcv, *replyto;
E 34
D 41
	char buf[2 * LINESIZE], **ap;
E 41
I 41
	char **ap;
E 41
E 23
E 15
E 9
	struct name *np;
	struct header head;
D 23
	char *netmap();
E 23

	if (msgvec[1] != 0) {
		printf("Sorry, can't reply to multiple messages at once\n");
		return(1);
	}
	mp = &message[msgvec[0] - 1];
I 47
	touch(mp);
E 47
	dot = mp;
D 8
	rcv = nameof(mp);
E 8
I 8
D 26
	rcv = nameof(mp, 1);
E 26
I 26
D 41
	rcv = NOSTR;
D 29
	cp = nameof(mp, 1);
E 29
I 29
	cp = skin(nameof(mp, 1));
E 29
	if (cp != NOSTR)
	    rcv = cp;
D 29
	cp = hfield("from", mp);
E 29
I 29
	cp = skin(hfield("from", mp));
E 29
	if (cp != NOSTR)
	    rcv = cp;
E 26
I 9
D 10
	replyto = hfield("reply-to", mp);
E 10
I 10
	replyto = skin(hfield("reply-to", mp));
E 10
E 9
E 8
	strcpy(buf, "");
D 9
	cp = hfield("to", mp);
	if (cp != NOSTR)
		strcpy(buf, cp);
E 9
I 9
	if (replyto != NOSTR)
		strcpy(buf, replyto);
	else {
D 29
		cp = hfield("to", mp);
E 29
I 29
		cp = skin(hfield("to", mp));
E 29
		if (cp != NOSTR)
			strcpy(buf, cp);
	}
E 9
	np = elide(extract(buf, GTO));
E 41
I 41
	if ((rcv = skin(hfield("from", mp))) == NOSTR)
		rcv = skin(nameof(mp, 1));
	if ((replyto = skin(hfield("reply-to", mp))) != NOSTR)
		np = extract(replyto, GTO);
	else if ((cp = skin(hfield("to", mp))) != NOSTR)
		np = extract(cp, GTO);
	else
		np = NIL;
	np = elide(np);
E 41
D 34
	/* rcv = rename(rcv); */
E 34
D 37
	mapf(np, rcv);
E 37
I 15
	/*
	 * Delete my name from the reply list,
	 * and with it, all my alternate names.
	 */
E 15
D 23
	np = delname(np, myname);
I 15
	if (altnames != 0)
E 23
I 23
D 46
	np = delname(np, myname, icequal);
E 46
I 46
	np = delname(np, myname);
E 46
	if (altnames)
E 23
		for (ap = altnames; *ap; ap++)
D 23
			np = delname(np, *ap);
E 23
I 23
D 46
			np = delname(np, *ap, icequal);
E 46
I 46
			np = delname(np, *ap);
E 46
E 23
E 15
D 41
	head.h_seq = 1;
D 27
	cp = detract(np, 0);
E 27
I 27
D 29
	cp = detract(np, GCOMMA);		/* do it with commas */
E 29
I 29
	cp = detract(np, 0);
E 29
E 27
D 9
	if (cp != NOSTR) {
E 9
I 9
	if (cp != NOSTR && replyto == NOSTR) {
E 9
		strcpy(buf, cp);
D 27
		strcat(buf, " ");
E 27
I 27
D 29
		strcat(buf, ", ");
E 29
I 29
		strcat(buf, " ");
E 29
E 27
		strcat(buf, rcv);
	}
D 9
	else
		strcpy(buf, rcv);
E 9
I 9
	else {
		if (cp == NOSTR && replyto != NOSTR)
E 41
I 41
	if (np != NIL && replyto == NOSTR)
		np = cat(np, extract(rcv, GTO));
	else if (np == NIL) {
		if (replyto != NOSTR)
E 41
			printf("Empty reply-to field -- replying to author\n");
D 41
		if (cp == NOSTR)
			strcpy(buf, rcv);
		else
			strcpy(buf, cp);
E 41
I 41
		np = extract(rcv, GTO);
E 41
	}
E 9
D 41
	head.h_to = buf;
	head.h_subject = hfield("subject", mp);
	if (head.h_subject == NOSTR)
E 41
I 41
	head.h_to = np;
	if ((head.h_subject = hfield("subject", mp)) == NOSTR)
E 41
		head.h_subject = hfield("subj", mp);
I 8
	head.h_subject = reedit(head.h_subject);
E 8
D 41
	head.h_cc = NOSTR;
D 9
	cp = hfield("cc", mp);
	if (cp != NOSTR) {
		np = elide(extract(cp, GCC));
		mapf(np, rcv);
		np = delname(np, myname);
		head.h_cc = detract(np, 0);
E 9
I 9
	if (replyto == NOSTR) {
D 34
		cp = hfield("cc", mp);
E 34
I 34
		cp = skin(hfield("cc", mp));
E 34
		if (cp != NOSTR) {
			np = elide(extract(cp, GCC));
D 37
			mapf(np, rcv);
E 37
D 23
			np = delname(np, myname);
E 23
I 23
			np = delname(np, myname, icequal);
E 23
I 16
			if (altnames != 0)
				for (ap = altnames; *ap; ap++)
D 23
					np = delname(np, *ap);
E 23
I 23
					np = delname(np, *ap, icequal);
E 23
E 16
			head.h_cc = detract(np, 0);
		}
E 9
	}
	head.h_bcc = NOSTR;
I 36
	head.h_smopts = NOSTR;
E 36
	mail1(&head);
E 41
I 41
	if (replyto == NOSTR && (cp = skin(hfield("cc", mp))) != NOSTR) {
		np = elide(extract(cp, GCC));
D 46
		np = delname(np, myname, icequal);
E 46
I 46
		np = delname(np, myname);
E 46
		if (altnames != 0)
			for (ap = altnames; *ap; ap++)
D 46
				np = delname(np, *ap, icequal);
E 46
I 46
				np = delname(np, *ap);
E 46
		head.h_cc = np;
	} else
		head.h_cc = NIL;
	head.h_bcc = NIL;
	head.h_smopts = NIL;
	mail1(&head, 1);
E 41
	return(0);
}

/*
I 8
 * Modify the subject we are replying to to begin with Re: if
 * it does not already.
 */
D 41

E 41
char *
reedit(subj)
D 41
	char *subj;
E 41
I 41
	register char *subj;
E 41
{
D 41
	char sbuf[10];
	register char *newsubj;
E 41
I 41
	char *newsubj;
E 41

	if (subj == NOSTR)
D 41
		return(NOSTR);
	strncpy(sbuf, subj, 3);
	sbuf[3] = 0;
	if (icequal(sbuf, "re:"))
		return(subj);
	newsubj = salloc(strlen(subj) + 6);
D 34
	sprintf(newsubj, "Re:  %s", subj);
E 34
I 34
	sprintf(newsubj, "Re: %s", subj);
E 34
	return(newsubj);
E 41
I 41
		return NOSTR;
	if ((subj[0] == 'r' || subj[0] == 'R') &&
	    (subj[1] == 'e' || subj[1] == 'E') &&
	    subj[2] == ':')
		return subj;
	newsubj = salloc(strlen(subj) + 5);
	strcpy(newsubj, "Re: ");
D 42
	strcpy(subj, newsubj + 4);
E 42
I 42
	strcpy(newsubj + 4, subj);
E 42
	return newsubj;
E 41
}

/*
E 8
 * Preserve the named messages, so that they will be sent
 * back to the system mailbox.
 */
D 55

E 55
I 55
int
E 55
preserve(msgvec)
	int *msgvec;
{
	register struct message *mp;
	register int *ip, mesg;

	if (edit) {
		printf("Cannot \"preserve\" in edit mode\n");
		return(1);
	}
	for (ip = msgvec; *ip != NULL; ip++) {
		mesg = *ip;
		mp = &message[mesg-1];
		mp->m_flag |= MPRESERVE;
I 12
		mp->m_flag &= ~MBOX;
E 12
		dot = mp;
	}
	return(0);
}

/*
I 33
 * Mark all given messages as unread.
 */
I 55
int
E 55
unread(msgvec)
	int	msgvec[];
{
	register int *ip;

	for (ip = msgvec; *ip != NULL; ip++) {
		dot = &message[*ip-1];
		dot->m_flag &= ~(MREAD|MTOUCH);
		dot->m_flag |= MSTATUS;
	}
	return(0);
}

/*
E 33
 * Print the size of each message.
 */
D 55

E 55
I 55
int
E 55
messize(msgvec)
	int *msgvec;
{
	register struct message *mp;
	register int *ip, mesg;

	for (ip = msgvec; *ip != NULL; ip++) {
		mesg = *ip;
		mp = &message[mesg-1];
D 22
		printf("%d: %d\n", mesg, msize(mp));
E 22
I 22
D 33
		printf("%d: %ld\n", mesg, mp->m_size);
E 33
I 33
		printf("%d: %d/%ld\n", mesg, mp->m_lines, mp->m_size);
E 33
E 22
	}
	return(0);
}

/*
 * Quit quickly.  If we are sourcing, just pop the input level
 * by returning an error.
 */
D 55

E 55
I 55
int
E 55
rexit(e)
I 55
	int e;
E 55
{
	if (sourcing)
		return(1);
I 17
D 40
	if (Tflag != NOSTR)
		close(creat(Tflag, 0600));
E 40
E 17
	exit(e);
I 34
	/*NOTREACHED*/
E 34
}

/*
 * Set or display a variable value.  Syntax is similar to that
 * of csh.
 */
D 55

E 55
I 55
int
E 55
set(arglist)
	char **arglist;
{
	register struct var *vp;
	register char *cp, *cp2;
	char varbuf[BUFSIZ], **ap, **p;
	int errs, h, s;

D 46
	if (argcount(arglist) == 0) {
E 46
I 46
	if (*arglist == NOSTR) {
E 46
		for (h = 0, s = 1; h < HSHSIZE; h++)
			for (vp = variables[h]; vp != NOVAR; vp = vp->v_link)
				s++;
		ap = (char **) salloc(s * sizeof *ap);
		for (h = 0, p = ap; h < HSHSIZE; h++)
			for (vp = variables[h]; vp != NOVAR; vp = vp->v_link)
				*p++ = vp->v_name;
		*p = NOSTR;
		sort(ap);
		for (p = ap; *p != NOSTR; p++)
			printf("%s\t%s\n", *p, value(*p));
		return(0);
	}
	errs = 0;
	for (ap = arglist; *ap != NOSTR; ap++) {
		cp = *ap;
		cp2 = varbuf;
		while (*cp != '=' && *cp != '\0')
			*cp2++ = *cp++;
		*cp2 = '\0';
		if (*cp == '\0')
			cp = "";
		else
			cp++;
		if (equal(varbuf, "")) {
			printf("Non-null variable name required\n");
			errs++;
			continue;
		}
		assign(varbuf, cp);
	}
	return(errs);
}

/*
 * Unset a bunch of variable values.
 */
D 55

E 55
I 55
int
E 55
unset(arglist)
	char **arglist;
{
	register struct var *vp, *vp2;
D 34
	register char *cp;
E 34
	int errs, h;
	char **ap;

	errs = 0;
	for (ap = arglist; *ap != NOSTR; ap++) {
		if ((vp2 = lookup(*ap)) == NOVAR) {
			if (!sourcing) {
				printf("\"%s\": undefined variable\n", *ap);
				errs++;
			}
			continue;
		}
		h = hash(*ap);
		if (vp2 == variables[h]) {
			variables[h] = variables[h]->v_link;
			vfree(vp2->v_name);
			vfree(vp2->v_value);
D 34
			cfree(vp2);
E 34
I 34
D 56
			cfree((char *)vp2);
E 56
I 56
			free((char *)vp2);
E 56
E 34
			continue;
		}
		for (vp = variables[h]; vp->v_link != vp2; vp = vp->v_link)
			;
		vp->v_link = vp2->v_link;
		vfree(vp2->v_name);
		vfree(vp2->v_value);
D 34
		cfree(vp2);
E 34
I 34
D 56
		cfree((char *) vp2);
E 56
I 56
		free((char *) vp2);
E 56
E 34
	}
	return(errs);
}

/*
 * Put add users to a group.
 */
D 55

E 55
I 55
int
E 55
group(argv)
	char **argv;
{
	register struct grouphead *gh;
	register struct group *gp;
	register int h;
	int s;
	char **ap, *gname, **p;

D 46
	if (argcount(argv) == 0) {
E 46
I 46
	if (*argv == NOSTR) {
E 46
		for (h = 0, s = 1; h < HSHSIZE; h++)
			for (gh = groups[h]; gh != NOGRP; gh = gh->g_link)
				s++;
		ap = (char **) salloc(s * sizeof *ap);
		for (h = 0, p = ap; h < HSHSIZE; h++)
			for (gh = groups[h]; gh != NOGRP; gh = gh->g_link)
				*p++ = gh->g_name;
		*p = NOSTR;
		sort(ap);
		for (p = ap; *p != NOSTR; p++)
			printgroup(*p);
		return(0);
	}
D 46
	if (argcount(argv) == 1) {
E 46
I 46
	if (argv[1] == NOSTR) {
E 46
		printgroup(*argv);
		return(0);
	}
	gname = *argv;
	h = hash(gname);
	if ((gh = findgroup(gname)) == NOGRP) {
		gh = (struct grouphead *) calloc(sizeof *gh, 1);
		gh->g_name = vcopy(gname);
		gh->g_list = NOGE;
		gh->g_link = groups[h];
		groups[h] = gh;
	}

	/*
	 * Insert names from the command list into the group.
	 * Who cares if there are duplicates?  They get tossed
	 * later anyway.
	 */

	for (ap = argv+1; *ap != NOSTR; ap++) {
		gp = (struct group *) calloc(sizeof *gp, 1);
		gp->ge_name = vcopy(*ap);
		gp->ge_link = gh->g_list;
		gh->g_list = gp;
	}
	return(0);
}

/*
 * Sort the passed string vecotor into ascending dictionary
 * order.
 */
D 55

E 55
I 55
void
E 55
sort(list)
	char **list;
{
	register char **ap;
	int diction();

	for (ap = list; *ap != NOSTR; ap++)
		;
	if (ap-list < 2)
		return;
D 34
	qsort(list, ap-list, sizeof *list, diction);
E 34
I 34
D 55
	qsort((char *)list, ap-list, sizeof *list, diction);
E 55
I 55
	qsort(list, ap-list, sizeof(*list), diction);
E 55
E 34
}

/*
 * Do a dictionary order comparison of the arguments from
 * qsort.
 */
D 55

E 55
I 55
int
E 55
diction(a, b)
D 55
	register char **a, **b;
E 55
I 55
	const void *a, *b;
E 55
{
D 55
	return(strcmp(*a, *b));
E 55
I 55
	return(strcmp(*(char **)a, *(char **)b));
E 55
}

/*
 * The do nothing command for comments.
 */

I 34
/*ARGSUSED*/
I 55
int
E 55
E 34
null(e)
I 55
	int e;
E 55
{
D 34
	return(0);
E 34
I 34
	return 0;
E 34
}

/*
D 3
 * Print out the current edit file, if we are editting.
E 3
I 3
D 48
 * Print out the current edit file, if we are editing.
E 3
 * Otherwise, print the name of the person who's mail
 * we are reading.
E 48
I 48
 * Change to another file.  With no argument, print information about
 * the current file.
E 48
 */
I 55
int
E 55
D 48

E 48
D 3
file(e)
E 3
I 3
file(argv)
D 38
	char **argv;
E 38
I 38
	register char **argv;
E 38
E 3
{
D 48
	register char *cp;
E 48
I 48
D 49
	char *cp;
E 49
E 48
I 3
D 34
	char fname[BUFSIZ];
E 34
I 19
D 38
	int edit;
E 38
E 19
E 3

D 3
	if (edit)
		printf("Reading \"%s\"\n", editfile);
	else
		printf("Reading %s's mail\n", rindex(mailname, '/') + 1);
	return(0);
E 3
I 3
	if (argv[0] == NOSTR) {
D 7
		if (edit)
			printf("Reading \"%s\"", editfile);
		else
			printf("Reading %s's mail",
			    rindex(mailname, '/') + 1);
		printf("; %d message(s)\n", msgCount);
E 7
I 7
D 58
		newfileinfo();
E 58
I 58
		newfileinfo(0);
E 58
E 7
D 38
		return(0);
E 38
I 38
		return 0;
E 38
	}
D 38

	/*
	 * Acker's!  Must switch to the new file.
	 * We use a funny interpretation --
	 *	# -- gets the previous file
	 *	% -- gets the invoker's post office box
	 *	%user -- gets someone else's post office box
I 4
	 *	& -- gets invoker's mbox file
E 4
	 *	string -- reads the given file
	 */

D 19
	cp = getfilename(argv[0]);
E 19
I 19
	cp = getfilename(argv[0], &edit);
E 19
	if (cp == NOSTR)
		return(-1);
D 18
	return(setfile(cp, 1));
E 18
I 18
D 19
	if (setfile(cp, 1))
E 19
I 19
D 21
	if (setfile(cp, edit))
E 21
I 21
	if (setfile(cp, edit)) {
E 38
I 38
D 49
	if ((cp = expand(*argv)) == NOSTR)
D 48
		return -1;
E 48
I 48
		return 1;
E 48
	strcpy(prevfile, mailname);
D 48
	if (setfile(cp, **argv != '%')) {
E 38
		perror(cp);
E 21
E 19
D 38
		return(-1);
E 38
I 38
		return -1;
E 38
I 21
	}
E 48
I 48
	if (setfile(cp, **argv != '%') < 0)
E 49
I 49
	if (setfile(*argv) < 0)
E 49
		return 1;
E 48
E 21
D 33
	newfileinfo();
E 33
I 33
D 39
	announce(0);
E 39
I 39
	announce();
E 39
I 34
	return 0;
E 34
E 33
E 18
D 38
}

/*
 * Evaluate the string given as a new mailbox name.
 * Ultimately, we want this to support a number of meta characters.
 * Possibly:
 *	% -- for my system mail box
 *	%user -- for user's system mail box
 *	# -- for previous file
I 4
 *	& -- get's invoker's mbox file
E 4
 *	file name -- for any other file
 */

I 4
D 5
char	prevfile[BUFSIZ];
E 5
I 5
char	prevfile[PATHSIZE];
E 5

E 4
char *
D 19
getfilename(name)
E 19
I 19
getfilename(name, aedit)
E 19
	char *name;
I 19
	int *aedit;
E 19
{
	register char *cp;
I 4
	char savename[BUFSIZ];
I 6
	char oldmailname[BUFSIZ];
E 6
E 4

I 19
	/*
	 * Assume we will be in "edit file" mode, until
	 * proven wrong.
	 */
	*aedit = 1;
E 19
D 4
	cp = expand(name);
	return(cp);
E 4
I 4
	switch (*name) {
	case '%':
I 19
		*aedit = 0;
E 19
I 5
		strcpy(prevfile, mailname);
E 5
		if (name[1] != 0) {
			strcpy(savename, myname);
I 6
			strcpy(oldmailname, mailname);
E 6
			strncpy(myname, name+1, PATHSIZE-1);
			myname[PATHSIZE-1] = 0;
			findmail();
D 6
			cp = mailname;
E 6
I 6
			cp = savestr(mailname);
E 6
			strcpy(myname, savename);
I 6
			strcpy(mailname, oldmailname);
E 6
			return(cp);
		}
I 6
		strcpy(oldmailname, mailname);
E 6
		findmail();
D 6
		return(mailname);
E 6
I 6
		cp = savestr(mailname);
		strcpy(mailname, oldmailname);
		return(cp);
E 6

	case '#':
		if (name[1] != 0)
			goto regular;
		if (prevfile[0] == 0) {
			printf("No previous file\n");
			return(NOSTR);
		}
D 5
		return(prevfile);
E 5
I 5
D 6
		strcpy(savename, prevfile);
E 6
I 6
		cp = savestr(prevfile);
E 6
		strcpy(prevfile, mailname);
D 6
		strcpy(mailname, savename);
		return(mailname);
E 6
I 6
		return(cp);
E 6
E 5

	case '&':
I 5
		strcpy(prevfile, mailname);
E 5
		if (name[1] == 0)
			return(mbox);
		/* Fall into . . . */

	default:
regular:
I 5
		strcpy(prevfile, mailname);
E 5
		cp = expand(name);
		return(cp);
	}
E 38
E 4
E 3
}

/*
 * Expand file names like echo
 */
I 55
int
E 55
D 41

E 41
echo(argv)
	char **argv;
{
	register char **ap;
	register char *cp;

	for (ap = argv; *ap != NOSTR; ap++) {
		cp = *ap;
D 36
		if ((cp = expand(cp)) != NOSTR)
D 11
			printf("%s\n", cp);
E 11
I 11
			printf("%s ", cp);
E 36
I 36
		if ((cp = expand(cp)) != NOSTR) {
			if (ap != argv)
				putchar(' ');
			printf("%s", cp);
		}
E 36
E 11
	}
I 36
	putchar('\n');
D 41

E 36
	return(0);
E 41
I 41
	return 0;
E 41
}

I 55
int
E 55
I 33
Respond(msgvec)
	int *msgvec;
{
	if (value("Replyall") == NOSTR)
		return (_Respond(msgvec));
	else
		return (_respond(msgvec));
}

E 33
/*
 * Reply to a series of messages by simply mailing to the senders
 * and not messing around with the To: and Cc: lists as in normal
 * reply.
 */
I 55
int
E 55
D 41

E 41
D 33
Respond(msgvec)
E 33
I 33
_Respond(msgvec)
E 33
	int msgvec[];
{
	struct header head;
	struct message *mp;
D 26
	register int s, *ap;
	register char *cp, *subject;
E 26
I 26
D 34
	register int i, s, *ap;
E 34
I 34
D 41
	register int s, *ap;
E 34
	register char *cp, *cp2, *subject;
E 41
I 41
	register int *ap;
	register char *cp;
E 41
E 26

D 41
	for (s = 0, ap = msgvec; *ap != 0; ap++) {
E 41
I 41
	head.h_to = NIL;
	for (ap = msgvec; *ap != 0; ap++) {
E 41
		mp = &message[*ap - 1];
I 47
		touch(mp);
E 47
		dot = mp;
D 8
		s += strlen(nameof(mp)) + 1;
E 8
I 8
D 10
		s += strlen(nameof(mp, 1)) + 1;
E 10
I 10
D 26
		s += strlen(nameof(mp, 2)) + 1;
E 26
I 26
D 29
		if ((cp = hfield("from", mp)) != NOSTR)
E 29
I 29
D 41
		if ((cp = skin(hfield("from", mp))) != NOSTR)
E 29
		    s+= strlen(cp) + 1;
		else
D 29
		    s += strlen(nameof(mp, 2)) + 1;
E 29
I 29
		    s += strlen(skin(nameof(mp, 2))) + 1;
E 41
I 41
		if ((cp = skin(hfield("from", mp))) == NOSTR)
			cp = skin(nameof(mp, 2));
		head.h_to = cat(head.h_to, extract(cp, GTO));
E 41
E 29
E 26
E 10
E 8
	}
D 41
	if (s == 0)
		return(0);
	cp = salloc(s + 2);
	head.h_to = cp;
	for (ap = msgvec; *ap != 0; ap++) {
		mp = &message[*ap - 1];
D 8
		cp = copy(nameof(mp), cp);
E 8
I 8
D 10
		cp = copy(nameof(mp, 1), cp);
E 10
I 10
D 26
		cp = copy(nameof(mp, 2), cp);
E 26
I 26
D 29
		if ((cp2 = hfield("from", mp)) == NOSTR)
		    cp2 = nameof(mp, 2);
E 29
I 29
		if ((cp2 = skin(hfield("from", mp))) == NOSTR)
		    cp2 = skin(nameof(mp, 2));
E 29
		cp = copy(cp2, cp);
E 26
E 10
E 8
		*cp++ = ' ';
	}
	*--cp = 0;
E 41
I 41
	if (head.h_to == NIL)
		return 0;
E 41
	mp = &message[msgvec[0] - 1];
D 41
	subject = hfield("subject", mp);
	head.h_seq = 0;
	if (subject == NOSTR)
		subject = hfield("subj", mp);
D 8
	head.h_subject = subject;
E 8
I 8
	head.h_subject = reedit(subject);
E 8
	if (subject != NOSTR)
		head.h_seq++;
	head.h_cc = NOSTR;
	head.h_bcc = NOSTR;
I 36
	head.h_smopts = NOSTR;
E 36
	mail1(&head);
I 5
	return(0);
E 41
I 41
	if ((head.h_subject = hfield("subject", mp)) == NOSTR)
		head.h_subject = hfield("subj", mp);
	head.h_subject = reedit(head.h_subject);
	head.h_cc = NIL;
	head.h_bcc = NIL;
	head.h_smopts = NIL;
	mail1(&head, 1);
	return 0;
E 41
}

/*
 * Conditional commands.  These allow one to parameterize one's
 * .mailrc and do some things if sending, others if receiving.
 */
D 55

E 55
I 55
int
E 55
ifcmd(argv)
	char **argv;
{
	register char *cp;

	if (cond != CANY) {
		printf("Illegal nested \"if\"\n");
		return(1);
	}
	cond = CANY;
	cp = argv[0];
	switch (*cp) {
	case 'r': case 'R':
		cond = CRCV;
		break;

	case 's': case 'S':
		cond = CSEND;
		break;

	default:
		printf("Unrecognized if-keyword: \"%s\"\n", cp);
		return(1);
	}
	return(0);
}

/*
 * Implement 'else'.  This is pretty simple -- we just
 * flip over the conditional flag.
 */
D 55

E 55
I 55
int
E 55
elsecmd()
{

	switch (cond) {
	case CANY:
		printf("\"Else\" without matching \"if\"\n");
		return(1);

	case CSEND:
		cond = CRCV;
		break;

	case CRCV:
		cond = CSEND;
		break;

	default:
		printf("Mail's idea of conditions is screwed up\n");
		cond = CANY;
		break;
	}
	return(0);
}

/*
 * End of if statement.  Just set cond back to anything.
 */
D 55

E 55
I 55
int
E 55
endifcmd()
{

	if (cond == CANY) {
		printf("\"Endif\" without matching \"if\"\n");
		return(1);
	}
	cond = CANY;
I 15
	return(0);
}

/*
 * Set the list of alternate names.
 */
I 55
int
E 55
alternates(namelist)
	char **namelist;
{
	register int c;
	register char **ap, **ap2, *cp;

	c = argcount(namelist) + 1;
	if (c == 1) {
		if (altnames == 0)
			return(0);
		for (ap = altnames; *ap; ap++)
			printf("%s ", *ap);
		printf("\n");
		return(0);
	}
	if (altnames != 0)
D 56
		cfree((char *) altnames);
E 56
I 56
		free((char *) altnames);
E 56
D 34
	altnames = (char **) calloc(c, sizeof (char *));
E 34
I 34
	altnames = (char **) calloc((unsigned) c, sizeof (char *));
E 34
	for (ap = namelist, ap2 = altnames; *ap; ap++, ap2++) {
D 34
		cp = (char *) calloc(strlen(*ap) + 1, sizeof (char));
E 34
I 34
		cp = (char *) calloc((unsigned) strlen(*ap) + 1, sizeof (char));
E 34
		strcpy(cp, *ap);
		*ap2 = cp;
	}
	*ap2 = 0;
E 15
E 5
	return(0);
}
E 1
