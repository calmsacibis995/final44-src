h36738
s 00032/00014/00233
d D 8.2 95/04/20 09:59:22 dab 27 26
c Add support for "inc" command and "autoinc" variable.
c Recognize timestamps in From lines created by SysV/Solaris
c Recognize MAILRC env variable for .mailrc location
c Change tty handling from sgtty to termios
c Turn off EXTPROC when editing headers so that it works
c correctly with Linemode telnet.
e
s 00002/00002/00245
d D 8.1 93/06/06 15:08:50 bostic 26 25
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/00242
d D 5.13 92/06/26 12:03:28 bostic 25 24
c quad's broke it -- prototyped it rather than figure out the problem
e
s 00004/00003/00238
d D 5.12 91/04/01 08:58:59 bostic 24 23
c ANSI
e
s 00001/00011/00240
d D 5.11 90/06/01 17:00:40 bostic 23 22
c new copyright notice
e
s 00006/00006/00245
d D 5.10 89/11/24 23:07:09 edward 22 21
c sig_t
e
s 00001/00001/00250
d D 5.9 89/05/19 18:22:42 bostic 21 20
c gtty and utime are in compatibility library now
e
s 00041/00014/00210
d D 5.8 89/04/22 15:27:41 edward 20 19
c no more SIGCONT
e
s 00012/00007/00212
d D 5.7 88/06/29 21:02:11 bostic 19 18
c install approved copyright notice
e
s 00009/00014/00210
d D 5.6 88/06/19 04:21:00 edward 18 17
c rationalized mail sending code: keep h_to, h_cc, h_bcc, h_smopts as lists
c not strings; h_seq deleted; now understands <...> addresses; and many more.
c should be much cleaner and somewhat faster.
e
s 00011/00005/00213
d D 5.5 88/02/18 17:04:29 bostic 17 16
c written by Kurt Shoens; added Berkeley specific header
e
s 00001/00002/00217
d D 5.4 88/01/02 22:37:10 bostic 16 15
c fix extern declarations for ANSI C
e
s 00014/00030/00205
d D 5.3 87/05/18 12:28:47 edward 15 14
c major rework: made faster, cleaned up, obsolete code removed,
c the whole thing should be chucked and written from scratch
e
s 00001/00001/00234
d D 5.2 85/06/21 17:14:31 mckusick 14 13
c botched copyright
e
s 00007/00001/00228
d D 5.1 85/06/06 10:44:53 dist 13 12
c Add copyright
e
s 00003/00003/00226
d D 2.7 83/08/11 22:20:20 sam 12 11
c standardize sccs keyword lines
e
s 00001/00000/00228
d D 2.6 83/07/26 17:55:41 sam 11 10
c stdio and tty's require clearerr to insure EOF is reset
e
s 00000/00001/00228
d D 2.5 83/06/12 11:17:07 sam 10 9
c new signals
e
s 00004/00003/00225
d D 2.4 83/02/09 15:25:21 sam 9 8
c from sun
e
s 00000/00000/00228
d D 2.3 82/03/15 09:44:39 kurt 8 6
i 7
c Included Eric's branch changes to remove vax and vmunix 
c dependencies. 
c 
e
s 00012/00002/00217
d D 2.1.1.1 82/03/15 09:34:16 kurt 7 5
c Eric Allman's fixes to remove VAX and VMUNIX dependencies
e
s 00000/00001/00218
d D 2.2 81/12/14 14:47:56 kurt 6 5
c removed redundant include of sgtty.h 
c 
e
s 00000/00000/00219
d D 2.1 81/07/01 11:10:37 kurt 5 4
c Release to Heidi Stettner
e
s 00051/00007/00168
d D 1.4 81/04/01 17:52:43 kurt 4 3
c changed to reprint prompt when resumed after ^Z
e
s 00003/00003/00172
d D 1.3 81/04/01 12:59:55 kurt 3 2
c changed calls on signal to sigset
e
s 00004/00001/00171
d D 1.2 81/03/02 19:46:54 kas 2 1
c more careful about clobbering the supposed newline at the end of the string
c when reading in a header line; careful to clear string initially when using
c the enhanced tty driver to avoid picking up a ghost from previous header
e
s 00172/00000/00000
d D 1.1 80/10/08 09:52:04 kas 1 0
c date and time created 80/10/08 09:52:04 by kas
e
u
U
f b 
t
T
I 13
/*
D 26
 * Copyright (c) 1980 Regents of the University of California.
D 17
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 17
I 17
 * All rights reserved.
E 26
I 26
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 26
 *
D 23
 * Redistribution and use in source and binary forms are permitted
D 19
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 19
I 19
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
E 23
I 23
 * %sccs.include.redist.c%
E 23
E 19
E 17
 */

E 13
I 1
D 12
#
E 12
I 12
D 17
#ifndef lint
D 14
static char sccsid[] = "%W% (Berkeley) %G%";
E 14
I 14
static char *sccsid = "%W% (Berkeley) %G%";
E 14
D 13
#endif
E 13
I 13
#endif not lint
E 17
I 17
D 19
#ifdef notdef
E 19
I 19
#ifndef lint
E 19
static char sccsid[] = "%W% (Berkeley) %G%";
D 19
#endif /* notdef */
E 19
I 19
#endif /* not lint */
E 19
E 17
E 13
E 12

/*
 * Mail -- a mail program
 *
 * Generally useful tty stuff.
 */

#include "rcv.h"
I 25
#include "extern.h"
E 25
D 6
#include <sgtty.h>
E 6
D 12

static char *SccsId = "%W% %G%";
E 12

static	int	c_erase;		/* Current erase char */
static	int	c_kill;			/* Current kill char */
I 4
D 20
static	int	hadcont;		/* Saw continue signal */
E 20
static	jmp_buf	rewrite;		/* Place to go when continued */
I 20
static	jmp_buf	intjmp;			/* Place to go when interrupted */
E 20
E 4
#ifndef TIOCSTI
static	int	ttyset;			/* We must now do erase/kill */
#endif

/*
 * Read all relevant header fields.
 */

I 25
int
E 25
grabh(hp, gflags)
	struct header *hp;
I 25
	int gflags;
E 25
{
D 27
	struct sgttyb ttybuf;
E 27
I 27
	struct termios ttybuf;
E 27
I 20
D 22
	int (*saveint)();
E 22
I 22
	sig_t saveint;
E 22
E 20
I 4
D 15
	int ttycont(), signull();
E 15
I 15
D 16
	int ttycont();
E 16
E 15
E 4
#ifndef TIOCSTI
D 15
	int (*savesigs[2])();
E 15
I 15
D 20
	int (*saveint)(), (*savequit)();
E 20
I 20
D 22
	int (*savequit)();
E 22
I 22
	sig_t savequit;
I 27
#else
	int extproc, flag;
E 27
E 22
E 20
E 15
#endif
I 4
D 20
	int (*savecont)();
E 20
I 20
D 22
	int (*savetstp)();
	int (*savettou)();
	int (*savettin)();
E 22
I 22
	sig_t savetstp;
	sig_t savettou;
	sig_t savettin;
E 22
E 20
E 4
D 15
	register int s;
E 15
	int errs;
I 20
D 24
	int ttyint();
E 24
I 24
	void ttyint();
E 24
E 20

I 7
D 15
# ifdef VMUNIX
E 7
I 4
	savecont = sigset(SIGCONT, signull);
I 7
# endif VMUNIX
E 15
I 15
D 20
	savecont = signal(SIGCONT, SIG_DFL);
E 20
I 20
	savetstp = signal(SIGTSTP, SIG_DFL);
	savettou = signal(SIGTTOU, SIG_DFL);
	savettin = signal(SIGTTIN, SIG_DFL);
E 20
E 15
E 7
E 4
	errs = 0;
#ifndef TIOCSTI
	ttyset = 0;
#endif
D 21
	if (gtty(fileno(stdin), &ttybuf) < 0) {
E 21
I 21
D 27
	if (ioctl(fileno(stdin), TIOCGETP, &ttybuf) < 0) {
E 21
		perror("gtty");
E 27
I 27
	if (ioctl(fileno(stdin), TIOCGETA, &ttybuf) < 0) {
		perror("TIOCGETA");
E 27
		return(-1);
	}
D 27
	c_erase = ttybuf.sg_erase;
	c_kill = ttybuf.sg_kill;
E 27
I 27
	c_erase = ttybuf.c_cc[VERASE];
	c_kill = ttybuf.c_cc[VKILL];
E 27
#ifndef TIOCSTI
D 27
	ttybuf.sg_erase = 0;
	ttybuf.sg_kill = 0;
E 27
I 27
	ttybuf.c_cc[VERASE] = 0;
	ttybuf.c_cc[VKILL] = 0;
E 27
D 15
	for (s = SIGINT; s <= SIGQUIT; s++)
D 3
		if ((savesigs[s-SIGINT] = signal(s, SIG_IGN)) == SIG_DFL)
			signal(s, SIG_DFL);
E 3
I 3
		if ((savesigs[s-SIGINT] = sigset(s, SIG_IGN)) == SIG_DFL)
			sigset(s, SIG_DFL);
E 15
I 15
	if ((saveint = signal(SIGINT, SIG_IGN)) == SIG_DFL)
		signal(SIGINT, SIG_DFL);
	if ((savequit = signal(SIGQUIT, SIG_IGN)) == SIG_DFL)
		signal(SIGQUIT, SIG_DFL);
I 20
#else
I 27
# ifdef	TIOCEXT
	extproc = ((ttybuf.c_lflag & EXTPROC) ? 1 : 0);
	if (extproc) {
		flag = 0;
		if (ioctl(fileno(stdin), TIOCEXT, &flag) < 0)
			perror("TIOCEXT: off");
	}
# endif /* TIOCEXT */
E 27
	if (setjmp(intjmp))
		goto out;
	saveint = signal(SIGINT, ttyint);
E 20
E 15
E 3
#endif
	if (gflags & GTO) {
#ifndef TIOCSTI
D 18
		if (!ttyset && hp->h_to != NOSTR)
E 18
I 18
		if (!ttyset && hp->h_to != NIL)
E 18
D 27
			ttyset++, stty(fileno(stdin), &ttybuf);
E 27
I 27
			ttyset++, tcsetattr(fileno(stdin), &ttybuf);
E 27
#endif
D 18
		hp->h_to = readtty("To: ", hp->h_to);
		if (hp->h_to != NOSTR)
			hp->h_seq++;
E 18
I 18
		hp->h_to =
			extract(readtty("To: ", detract(hp->h_to, 0)), GTO);
E 18
	}
	if (gflags & GSUBJECT) {
#ifndef TIOCSTI
		if (!ttyset && hp->h_subject != NOSTR)
D 27
			ttyset++, stty(fileno(stdin), &ttybuf);
E 27
I 27
			ttyset++, tcsetattr(fileno(stdin), &ttybuf);
E 27
#endif
		hp->h_subject = readtty("Subject: ", hp->h_subject);
D 18
		if (hp->h_subject != NOSTR)
			hp->h_seq++;
E 18
	}
	if (gflags & GCC) {
#ifndef TIOCSTI
D 18
		if (!ttyset && hp->h_cc != NOSTR)
E 18
I 18
		if (!ttyset && hp->h_cc != NIL)
E 18
D 27
			ttyset++, stty(fileno(stdin), &ttybuf);
E 27
I 27
			ttyset++, tcsetattr(fileno(stdin), &ttybuf);
E 27
#endif
D 18
		hp->h_cc = readtty("Cc: ", hp->h_cc);
		if (hp->h_cc != NOSTR)
			hp->h_seq++;
E 18
I 18
		hp->h_cc =
			extract(readtty("Cc: ", detract(hp->h_cc, 0)), GCC);
E 18
	}
	if (gflags & GBCC) {
#ifndef TIOCSTI
D 18
		if (!ttyset && hp->h_bcc != NOSTR)
E 18
I 18
		if (!ttyset && hp->h_bcc != NIL)
E 18
D 27
			ttyset++, stty(fileno(stdin), &ttybuf);
E 27
I 27
			ttyset++, tcsetattr(fileno(stdin), &ttybuf);
E 27
#endif
D 18
		hp->h_bcc = readtty("Bcc: ", hp->h_bcc);
		if (hp->h_bcc != NOSTR)
			hp->h_seq++;
E 18
I 18
		hp->h_bcc =
			extract(readtty("Bcc: ", detract(hp->h_bcc, 0)), GBCC);
E 18
	}
I 7
D 15
# ifdef VMUNIX
E 7
I 4
	sigset(SIGCONT, savecont);
I 7
# endif VMUNIX
E 15
I 15
D 20
	signal(SIGCONT, savecont);
E 20
I 20
out:
	signal(SIGTSTP, savetstp);
	signal(SIGTTOU, savettou);
	signal(SIGTTIN, savettin);
E 20
E 15
E 7
E 4
#ifndef TIOCSTI
D 27
	ttybuf.sg_erase = c_erase;
	ttybuf.sg_kill = c_kill;
E 27
I 27
	ttybuf.c_cc[VERASE] = c_erase;
	ttybuf.c_cc[VKILL] = c_kill;
E 27
	if (ttyset)
D 27
		stty(fileno(stdin), &ttybuf);
E 27
I 27
		tcsetattr(fileno(stdin), &ttybuf);
E 27
D 15
	for (s = SIGINT; s <= SIGQUIT; s++)
D 3
		signal(s, savesigs[s-SIGINT]);
E 3
I 3
		sigset(s, savesigs[s-SIGINT]);
E 15
I 15
D 20
	signal(SIGINT, saveint);
E 20
	signal(SIGQUIT, savequit);
I 27
#else
# ifdef	TIOCEXT
	if (extproc) {
		flag = 1;
		if (ioctl(fileno(stdin), TIOCEXT, &flag) < 0)
			perror("TIOCEXT: on");
	}
# endif /* TIOCEXT */
E 27
E 15
E 3
#endif
I 20
	signal(SIGINT, saveint);
E 20
	return(errs);
}

/*
 * Read up a header from standard input.
 * The source string has the preliminary contents to
 * be read.
 *
 */

char *
readtty(pr, src)
	char pr[], src[];
{
D 9
	char canonb[BUFSIZ];
D 4
	int c, ch;
E 4
I 4
	int c, ch, signull();
E 9
I 9
	char ch, canonb[BUFSIZ];
D 15
	int c, signull();
E 15
I 15
	int c;
E 15
E 9
E 4
	register char *cp, *cp2;
I 16
D 20
	int ttycont();
E 20
I 20
D 24
	int ttystop();
E 24
I 24
	void ttystop();
E 24
E 20
E 16

D 4
	fputs(pr, stdout); fflush(stdout);
E 4
I 4
	fputs(pr, stdout);
	fflush(stdout);
E 4
	if (src != NOSTR && strlen(src) > BUFSIZ - 2) {
		printf("too long to edit\n");
		return(src);
	}
#ifndef TIOCSTI
	if (src != NOSTR)
		cp = copy(src, canonb);
	else
		cp = copy("", canonb);
	fputs(canonb, stdout);
	fflush(stdout);
#else
D 4
	for (cp = src; c = *cp; cp++) {
E 4
I 4
	cp = src == NOSTR ? "" : src;
	while (c = *cp++) {
E 4
		if (c == c_erase || c == c_kill) {
			ch = '\\';
			ioctl(0, TIOCSTI, &ch);
		}
D 9
		ioctl(0, TIOCSTI, &c);
E 9
I 9
		ch = c;
		ioctl(0, TIOCSTI, &ch);
E 9
	}
	cp = canonb;
I 2
	*cp = 0;
E 2
#endif
D 4
	cp2 = fgets(cp, BUFSIZ - (cp - canonb), stdin);
D 2
	canonb[strlen(canonb) - 1] = '\0';
E 2
I 2
	cp = index(canonb, '\n');
	if (cp != NOSTR)
		*cp = 0;
E 4
I 4
	cp2 = cp;
	while (cp2 < canonb + BUFSIZ)
		*cp2++ = 0;
	cp2 = cp;
	if (setjmp(rewrite))
		goto redo;
I 7
D 15
# ifdef VMUNIX
E 7
	sigset(SIGCONT, ttycont);
I 7
# endif VMUNIX
E 15
I 15
D 20
	signal(SIGCONT, ttycont);
E 20
I 20
	signal(SIGTSTP, ttystop);
	signal(SIGTTOU, ttystop);
	signal(SIGTTIN, ttystop);
E 20
E 15
I 11
	clearerr(stdin);
E 11
E 7
	while (cp2 < canonb + BUFSIZ) {
		c = getc(stdin);
		if (c == EOF || c == '\n')
			break;
		*cp2++ = c;
	}
	*cp2 = 0;
I 7
D 15
# ifdef VMUNIX
E 7
	sigset(SIGCONT, signull);
I 7
# endif VMUNIX
E 15
I 15
D 20
	signal(SIGCONT, SIG_DFL);
E 15
E 7
	if (c == EOF && ferror(stdin) && hadcont) {
E 20
I 20
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	if (c == EOF && ferror(stdin)) {
E 20
redo:
D 20
		hadcont = 0;
E 20
		cp = strlen(canonb) > 0 ? canonb : NOSTR;
		clearerr(stdin);
		return(readtty(pr, cp));
	}
E 4
E 2
#ifndef TIOCSTI
D 7
	if (cp2 == NOSTR || *cp2 == '\0')
E 7
I 7
	if (cp == NOSTR || *cp == '\0')
E 7
		return(src);
D 7
	cp = cp2;
E 7
I 7
	cp2 = cp;
E 7
	if (!ttyset)
		return(strlen(canonb) > 0 ? savestr(canonb) : NOSTR);
	while (*cp != '\0') {
		c = *cp++;
		if (c == c_erase) {
			if (cp2 == canonb)
				continue;
			if (cp2[-1] == '\\') {
				cp2[-1] = c;
				continue;
			}
			cp2--;
			continue;
		}
		if (c == c_kill) {
			if (cp2 == canonb)
				continue;
			if (cp2[-1] == '\\') {
				cp2[-1] = c;
				continue;
			}
			cp2 = canonb;
			continue;
		}
		*cp2++ = c;
	}
	*cp2 = '\0';
#endif
	if (equal("", canonb))
		return(NOSTR);
	return(savestr(canonb));
}
I 4

I 7
D 15
# ifdef VMUNIX
E 15
E 7
/*
 * Receipt continuation.
 */
I 24
void
E 24
I 15
D 20
/*ARGSUSED*/
E 15
ttycont(s)
E 20
I 20
ttystop(s)
I 25
	int s;
E 25
E 20
{
D 16

E 16
D 20
	hadcont++;
E 20
I 20
D 22
	int (*old_action)() = signal(s, SIG_DFL);
E 22
I 22
	sig_t old_action = signal(s, SIG_DFL);
E 22

	sigsetmask(sigblock(0) & ~sigmask(s));
	kill(0, s);
	sigblock(sigmask(s));
	signal(s, old_action);
E 20
D 10
	sigrelse(SIGCONT);
E 10
	longjmp(rewrite, 1);
I 20
}

/*ARGSUSED*/
I 24
void
E 24
ttyint(s)
I 25
	int s;
E 25
{
D 24

E 24
	longjmp(intjmp, 1);
E 20
}
I 7
D 15
# endif VMUNIX
E 7

/*
 * Null routine to satisfy
 * silly system bug that denies us holding SIGCONT
 */
signull(s)
{}
E 15
E 4
E 1
