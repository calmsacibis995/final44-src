h43870
s 00002/00002/00223
d D 8.1 93/06/06 16:36:13 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00006/00218
d D 5.4 91/03/02 10:26:46 bostic 11 10
c ANSI (real bug fix!)
e
s 00001/00011/00223
d D 5.3 90/06/01 17:46:46 bostic 10 9
c new copyright notice
e
s 00015/00004/00219
d D 5.2 88/09/13 17:03:57 bostic 9 8
c not derived from AT&T code; add Berkeley specific header
e
s 00007/00001/00216
d D 5.1 85/04/30 12:52:17 dist 8 7
c Add copyright
e
s 00019/00006/00198
d D 1.7 85/04/11 17:00:38 miriam 7 6
c Replace sleep calls for 'wake up'.
e
s 00031/00008/00173
d D 1.6 83/10/09 22:53:54 sam 6 5
c parse response string from dialer
e
s 00000/00002/00181
d D 1.5 83/06/25 02:10:25 sam 5 4
c remove #if's, now in a library
e
s 00037/00032/00146
d D 1.4 83/06/25 01:15:31 sam 4 3
c so much...clean up after ralph's merge of wendel and mo code;
c purge VMUNIX include since changes for signals make it no longer portable 
c to systems other than 4.2; fix ventel for no echo strapping; do setjmps 
c instead of assuming interrupted system calls; purge lcmd, if people use 
e
s 00002/00002/00176
d D 1.3 83/06/15 13:53:46 ralph 3 2
c changes for local info, parity, vadic auto dialers
e
s 00008/00004/00170
d D 1.2 82/07/29 15:20:16 shannon 2 1
c 68000 fixes and other random fixes
e
s 00174/00000/00000
d D 1.1 82/04/19 18:01:28 shannon 1 0
c date and time created 82/04/19 18:01:28 by shannon
e
u
U
t
T
I 8
/*
D 9
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 9
I 9
D 12
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
D 10
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
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 9
 */

E 8
I 1
D 4
/*	%M%	%I%	%E%	*/
E 4
I 4
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 8
#endif
E 8
I 8
D 9
#endif not lint
E 9
I 9
#endif /* not lint */
E 9
E 8
E 4

D 5
#if VENTEL
E 5
/*
 * Routines for calling up on a Ventel Modem
I 4
D 7
 * The Ventel is expected to be strapped for "no echo".
E 7
I 7
 * The Ventel is expected to be strapped for local echo (just like uucp)
E 7
E 4
 */
#include "tip.h"
D 4
#include <setjmp.h>
#include <errno.h>
E 4

#define	MAXRETRY	5
D 4
#define	DISCONNECT	"\03"		/* ^C */
E 4

I 3
D 4
static char *sccsid = "%W% %G%";
E 3
static int sigALRM();
static int timeout = 0;
E 4
I 4
D 11
static	int sigALRM();
E 11
I 11
static	void sigALRM();
E 11
static	int timeout = 0;
static	jmp_buf timeoutbuf;
E 4

I 7
/*
 * some sleep calls have been replaced by this macro
 * because some ventel modems require two <cr>s in less than
 * a second in order to 'wake up'... yes, it is dirty...
 */
#define delay(num,denom) busyloop(CPUSPEED*num/denom)
#define CPUSPEED 1000000	/* VAX 780 is 1MIPS */
#define	DELAY(n)	{ register long N = (n); while (--N > 0); }
busyloop(n) { DELAY(n); }

E 7
ven_dialer(num, acu)
	register char *num;
	char *acu;
{
	register char *cp;
	register int connected = 0;
I 2
D 3
	char c;
E 3
E 2
D 6
#ifdef ACULOG
	char line[80];
#endif
E 6
I 6
	char *msg, *index(), line[80];
I 11
	static int gobble(), vensync();
	static void echo();
E 11

E 6
	/*
	 * Get in synch with a couple of carriage returns
	 */
	if (!vensync(FD)) {
		printf("can't synchronize with ventel\n");
#ifdef ACULOG
		logent(value(HOST), num, "ventel", "can't synch up");
#endif
		return (0);
	}
I 2
	if (boolean(value(VERBOSE)))
		printf("\ndialing...");
	fflush(stdout);
E 2
	ioctl(FD, TIOCHPCL, 0);
D 2
	echo("k$\n$D$I$A$L$:$ <");
E 2
I 2
D 4
	echo("k$\r$\n$D$I$A$L$:$ <");
E 4
I 4
	echo("#k$\r$\n$D$I$A$L$:$ ");
E 4
E 2
	for (cp = num; *cp; cp++) {
D 7
		sleep(1);
E 7
I 7
		delay(1, 10);
E 7
		write(FD, cp, 1);
D 2
		read(FD, cp, 1);
E 2
I 2
D 3
		read(FD, &c, 1);
E 3
I 3
D 4
		read(FD, cp, 1);
E 4
E 3
E 2
	}
D 4
	echo(">\r$\n");
E 4
I 4
D 7
	echo("\r$\n");
E 7
I 7
	delay(1, 10);
	write(FD, "\r", 1);
	gobble('\n', line);
E 7
E 4
D 6
	if (gobble('\n'))
		connected = gobble('!');
E 6
I 6
	if (gobble('\n', line))
		connected = gobble('!', line);
E 6
	ioctl(FD, TIOCFLUSH);
#ifdef ACULOG
	if (timeout) {
		sprintf(line, "%d second dial timeout",
			number(value(DIALTIMEOUT)));
		logent(value(HOST), num, "ventel", line);
	}
#endif
	if (timeout)
		ven_disconnect();	/* insurance */
I 6
	if (connected || timeout || !boolean(value(VERBOSE)))
		return (connected);
	/* call failed, parse response for user */
	cp = index(line, '\r');
	if (cp)
		*cp = '\0';
	for (cp = line; cp = index(cp, ' '); cp++)
		if (cp[1] == ' ')
			break;
	if (cp) {
		while (*cp == ' ')
			cp++;
		msg = cp;
		while (*cp) {
			if (isupper(*cp))
				*cp = tolower(*cp);
			cp++;
		}
		printf("%s...", msg);
	}
E 6
	return (connected);
}

ven_disconnect()
{
I 4

E 4
	close(FD);
}

ven_abort()
{
I 4

E 4
	write(FD, "\03", 1);
	close(FD);
}

D 11
static int
E 11
I 11
static void
E 11
echo(s)
	register char *s;
{
	char c;

	while (c = *s++) switch (c) {

	case '$':
		read(FD, &c, 1);
		s++;
		break;

	case '#':
		c = *s++;
		write(FD, &c, 1);
		break;

	default:
		write(FD, &c, 1);
		read(FD, &c, 1);
	}
}

D 11
static int
E 11
I 11
static void
E 11
sigALRM()
{
D 4
	signal(SIGALRM, SIG_IGN);
E 4
I 4
D 11

E 11
E 4
	printf("\07timeout waiting for reply\n");
	timeout = 1;
I 4
	longjmp(timeoutbuf, 1);
E 4
}

static int
D 4
gobble(s)
	register char s;
E 4
I 4
D 6
gobble(match)
E 6
I 6
gobble(match, response)
E 6
	register char match;
I 6
	char response[];
E 6
E 4
{
I 6
	register char *cp = response;
I 11
	sig_t f;
E 11
E 6
	char c;
I 4
D 11
	int (*f)();
E 11
E 4

D 11
	signal(SIGALRM, sigALRM);
E 11
I 11
	f = signal(SIGALRM, sigALRM);
E 11
	timeout = 0;
	do {
I 4
		if (setjmp(timeoutbuf)) {
			signal(SIGALRM, f);
I 6
			*cp = '\0';
E 6
			return (0);
		}
E 4
		alarm(number(value(DIALTIMEOUT)));
D 6
		read(FD, &c, 1);
E 6
I 6
		read(FD, cp, 1);
E 6
D 4
		c &= 0177;
E 4
I 2
		alarm(0);
I 4
D 6
		c &= 0177;
E 6
I 6
		c = (*cp++ &= 0177);
E 6
E 4
E 2
#ifdef notdef
		if (boolean(value(VERBOSE)))
D 2
#endif
E 2
			putchar(c);
D 2
		alarm(0);
E 2
I 2
#endif
E 2
D 4
		if (timeout)
			return (0);
	} while (c != '\n' && c != s);
E 4
I 4
	} while (c != '\n' && c != match);
E 4
	signal(SIGALRM, SIG_DFL);
I 6
	*cp = '\0';
E 6
D 4
	return (c == s);
E 4
I 4
	return (c == match);
E 4
}

#define min(a,b)	((a)>(b)?(b):(a))
/*
 * This convoluted piece of code attempts to get
D 4
 * the ventel in sync.  If you don't have the capacity or nread
 * call there are gory ways to simulate this.
E 4
I 4
 * the ventel in sync.  If you don't have FIONREAD
 * there are gory ways to simulate this.
E 4
 */
static int
vensync(fd)
{
D 4
	long nread;
	register int already = 0, nbytes;
E 4
I 4
	int already = 0, nread;
E 4
	char buf[60];

	/*
	 * Toggle DTR to force anyone off that might have left
	 * the modem connected, and insure a consistent state
	 * to start from.
	 *
	 * If you don't have the ioctl calls to diddle directly
	 * with DTR, you can always try setting the baud rate to 0.
	 */
	ioctl(FD, TIOCCDTR, 0);
D 7
	sleep(2);
E 7
I 7
	sleep(1);
E 7
	ioctl(FD, TIOCSDTR, 0);
	while (already < MAXRETRY) {
		/*
		 * After reseting the modem, send it two \r's to
		 * autobaud on. Make sure to delay between them
		 * so the modem can frame the incoming characters.
		 */
		write(fd, "\r", 1);
D 7
		sleep(1);
E 7
I 7
		delay(1,10);
E 7
		write(fd, "\r", 1);
D 7
		sleep(3);
E 7
I 7
		sleep(2);
E 7
D 4
		if (ioctl(fd, FIONREAD, (caddr_t)&nread) >= 0) {
			nbytes = nread;
			while (nbytes > 0) {
				read(fd, buf, min(nbytes, 60));
				if ((buf[nbytes-1]&0177) == '$')
					return (1);
				nbytes -= min(nbytes, 60);
			}
			sleep(1);
			already++;
E 4
I 4
		if (ioctl(fd, FIONREAD, (caddr_t)&nread) < 0) {
			perror("tip: ioctl");
			continue;
E 4
		}
I 4
		while (nread > 0) {
			read(fd, buf, min(nread, 60));
			if ((buf[nread - 1] & 0177) == '$')
				return (1);
			nread -= min(nread, 60);
		}
		sleep(1);
		already++;
E 4
	}
	return (0);
}
I 7

E 7
D 5
#endif
E 5
E 1
