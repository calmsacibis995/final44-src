h41922
s 00002/00002/00063
d D 8.1 93/06/04 12:03:12 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00060
d D 5.10 93/05/21 18:04:04 bostic 13 12
c use paths.h name
e
s 00002/00004/00061
d D 5.9 91/05/06 12:46:46 bostic 12 11
c don't use CIGNORE, just OR in TCSASOFT
e
s 00002/00001/00063
d D 5.8 91/02/23 19:49:45 donn 11 10
c Add include files to get prototype declarations, and fix bugs found.
e
s 00002/00002/00062
d D 5.7 90/06/17 17:47:58 bostic 10 9
c TCSADFLUSH -> TCSAFLUSH
e
s 00001/00011/00063
d D 5.6 90/06/01 14:10:58 bostic 9 8
c new copyright notice
e
s 00022/00016/00052
d D 5.5 90/02/15 16:46:28 marc 8 7
c ignore TSTP , termios
e
s 00002/00002/00066
d D 5.4 89/05/11 10:38:20 bostic 7 6
c increase buffer to 128
e
s 00054/00030/00014
d D 5.3 88/09/22 11:23:33 bostic 6 5
c from scratch; write to /dev/tty if possible, block interrupts
e
s 00002/00002/00042
d D 5.2 86/03/09 19:48:03 donn 5 4
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00040
d D 5.1 85/06/05 12:22:08 mckusick 4 3
c Add copyright
e
s 00003/00003/00038
d D 4.3 84/05/16 10:58:16 ralph 3 2
c inline expand gtty() and stty().
e
s 00002/00002/00039
d D 4.2 81/07/01 16:58:56 root 2 1
c allow for prompts with % and flush stderr
e
s 00041/00000/00000
d D 4.1 80/12/21 16:50:35 wnj 1 0
c date and time created 80/12/21 16:50:35 by wnj
e
u
U
t
T
I 6
/*
D 14
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
D 9
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 9
I 9
 * %sccs.include.redist.c%
E 9
 */

E 6
I 1
D 4
/* %W% (Berkeley) %G% */
E 4
I 4
D 5
#ifndef lint
E 5
I 5
#if defined(LIBC_SCCS) && !defined(lint)
E 5
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
D 6
#endif LIBC_SCCS and not lint
E 6
I 6
#endif /* LIBC_SCCS and not lint */
E 6
E 5

I 6
D 8
#include <sys/ioctl.h>
E 8
I 8
#include <sys/termios.h>
E 8
#include <sys/signal.h>
I 13

#include <paths.h>
#include <pwd.h>
E 13
E 6
E 4
#include <stdio.h>
I 11
#include <unistd.h>
E 11
I 8
D 13
#include <pwd.h>
E 13
E 8
D 6
#include <signal.h>
#include <sgtty.h>
E 6

char *
getpass(prompt)
D 6
char *prompt;
E 6
I 6
D 11
	char *prompt;
E 11
I 11
	const char *prompt;
E 11
E 6
{
D 8
	struct sgttyb ttyb;
E 8
I 8
	struct termios term;
E 8
D 6
	int flags;
E 6
I 6
	register int ch;
E 6
	register char *p;
D 6
	register c;
	FILE *fi;
	static char pbuf[9];
	int (*signal())();
	int (*sig)();
E 6
I 6
	FILE *fp, *outfp;
	long omask;
D 8
	int svflagval;
D 7
#define	PASSWD_LEN	8
E 7
I 7
#define	PASSWD_LEN	128
E 7
	static char buf[PASSWD_LEN + 1];
E 8
I 8
	int echo;
	static char buf[_PASSWORD_LEN + 1];
E 8
E 6

D 6
	if ((fi = fdopen(open("/dev/tty", 2), "r")) == NULL)
		fi = stdin;
	else
		setbuf(fi, (char *)NULL);
	sig = signal(SIGINT, SIG_IGN);
D 3
	gtty(fileno(fi), &ttyb);
E 3
I 3
	ioctl(fileno(fi), TIOCGETP, &ttyb);
E 3
	flags = ttyb.sg_flags;
	ttyb.sg_flags &= ~ECHO;
D 3
	stty(fileno(fi), &ttyb);
E 3
I 3
	ioctl(fileno(fi), TIOCSETP, &ttyb);
E 3
D 2
	fprintf(stderr, prompt);
E 2
I 2
	fprintf(stderr, "%s", prompt); fflush(stderr);
E 2
	for (p=pbuf; (c = getc(fi))!='\n' && c!=EOF;) {
		if (p < &pbuf[8])
			*p++ = c;
E 6
I 6
	/*
	 * read and write to /dev/tty if possible; else read from
	 * stdin and write to stderr.
	 */
D 13
	if ((outfp = fp = fopen("/dev/tty", "w+")) == NULL) {
E 13
I 13
	if ((outfp = fp = fopen(_PATH_TTY, "w+")) == NULL) {
E 13
		outfp = stderr;
		fp = stdin;
E 6
	}
I 6
D 8

	(void)ioctl(fileno(fp), TIOCGETP, &ttyb);
	svflagval = ttyb.sg_flags;
	ttyb.sg_flags &= ~ECHO;
	omask = sigblock(sigmask(SIGINT));
	(void)ioctl(fileno(fp), TIOCSETP, &ttyb);

E 8
I 8
	/*
	 * note - blocking signals isn't necessarily the
	 * right thing, but we leave it for now.
	 */
	omask = sigblock(sigmask(SIGINT)|sigmask(SIGTSTP));
	(void)tcgetattr(fileno(fp), &term);
	if (echo = (term.c_lflag & ECHO)) {
		term.c_lflag &= ~ECHO;
D 12
		term.c_cflag |= CIGNORE;
D 10
		(void)tcsetattr(fileno(fp), TCSADFLUSH, &term);
E 10
I 10
		(void)tcsetattr(fileno(fp), TCSAFLUSH, &term);
E 12
I 12
		(void)tcsetattr(fileno(fp), TCSAFLUSH|TCSASOFT, &term);
E 12
E 10
	}
E 8
D 7
	fputs(prompt, outfp);
E 7
I 7
	(void)fputs(prompt, outfp);
E 7
	rewind(outfp);			/* implied flush */
	for (p = buf; (ch = getc(fp)) != EOF && ch != '\n';)
D 8
		if (p < buf + PASSWD_LEN)
E 8
I 8
		if (p < buf + _PASSWORD_LEN)
E 8
			*p++ = ch;
E 6
	*p = '\0';
D 2
	fprintf(stderr, "\n");
E 2
I 2
D 6
	fprintf(stderr, "\n"); fflush(stderr);
E 2
	ttyb.sg_flags = flags;
D 3
	stty(fileno(fi), &ttyb);
E 3
I 3
	ioctl(fileno(fi), TIOCSETP, &ttyb);
E 3
	signal(SIGINT, sig);
	if (fi != stdin)
		fclose(fi);
	return(pbuf);
E 6
I 6
	(void)write(fileno(outfp), "\n", 1);
D 8

	ttyb.sg_flags = svflagval;
	(void)ioctl(fileno(fp), TIOCSETP, &ttyb);
E 8
I 8
	if (echo) {
		term.c_lflag |= ECHO;
D 12
		term.c_cflag |= CIGNORE;
D 10
		tcsetattr(fileno(fp), TCSADFLUSH, &term);
E 10
I 10
		tcsetattr(fileno(fp), TCSAFLUSH, &term);
E 12
I 12
D 13
		tcsetattr(fileno(fp), TCSAFLUSH|TCSASOFT, &term);
E 13
I 13
		(void)tcsetattr(fileno(fp), TCSAFLUSH|TCSASOFT, &term);
E 13
E 12
E 10
	}
E 8
	(void)sigsetmask(omask);
	if (fp != stdin)
		(void)fclose(fp);
	return(buf);
E 6
}
E 1
