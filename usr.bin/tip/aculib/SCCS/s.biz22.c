h33402
s 00002/00002/00159
d D 8.1 93/06/06 16:35:41 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00160
d D 5.5 91/03/02 10:26:36 bostic 9 8
c ANSI (real bug fix!)
e
s 00001/00011/00159
d D 5.4 90/06/01 17:45:43 bostic 8 7
c new copyright notice
e
s 00004/00004/00166
d D 5.3 89/10/03 15:17:32 bostic 7 6
c POSIX signals
e
s 00015/00004/00155
d D 5.2 88/09/13 17:03:44 bostic 6 5
c not derived from AT&T code; add Berkeley specific header
e
s 00007/00001/00152
d D 5.1 85/06/06 09:49:19 dist 5 4
c Add copyright
e
s 00000/00002/00153
d D 4.4 83/06/25 02:09:36 sam 4 3
c remove #if's, now in a library
e
s 00033/00020/00122
d D 4.3 83/06/25 01:13:09 sam 3 2
c so much...clean up after ralph's merge of wendel and mo code;
c purge VMUNIX include since changes for signals make it no longer portable 
c to systems other than 4.2; fix ventel for no echo strapping; do setjmps 
c instead of assuming interrupted system calls; purge lcmd, if people use 
e
s 00002/00000/00140
d D 4.2 83/06/15 13:51:32 ralph 2 1
c changes for local info, parity, vadic auto dialers
e
s 00140/00000/00000
d D 4.1 81/11/29 22:48:08 sam 1 0
c date and time created 81/11/29 22:48:08 by sam
e
u
U
t
T
I 5
/*
D 6
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
D 10
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 8
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 6
 */

E 5
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif
E 5
I 5
D 6
#endif not lint
E 6
I 6
#endif /* not lint */
E 6
E 5

E 3
#include "tip.h"

D 4
#if BIZ1022
E 4
D 3
#define DISCONNECT	"\20\04"	/* disconnection string */
E 3
I 3
#define DISCONNECT_CMD	"\20\04"	/* disconnection string */
E 3

I 2
D 3
static char *sccsid = "%W% %G%";
E 2
static int sigALRM();
static int timeout = 0;
E 3
I 3
D 7
static	int sigALRM();
E 7
I 7
static	void sigALRM();
E 7
static	int timeout = 0;
static	jmp_buf timeoutbuf;
E 3

/*
 * Dial up on a BIZCOMP Model 1022 with either
 * 	tone dialing (mod = "V")
 *	pulse dialing (mod = "W")
 */
static int
biz_dialer(num, mod)
	char *num, *mod;
{
	register int connected = 0;
	char cbuf[40];
I 9
	static int cmd(), detect();
E 9

	if (boolean(value(VERBOSE)))
		printf("\nstarting call...");
	/*
	 * Disable auto-answer and configure for tone/pulse
	 *  dialing
	 */
	if (cmd("\02K\r")) {
		printf("can't initialize bizcomp...");
		return (0);
	}
	strcpy(cbuf, "\02.\r");
	cbuf[1] = *mod;
	if (cmd(cbuf)) {
		printf("can't set dialing mode...");
		return (0);
	}
	strcpy(cbuf, "\02D");
	strcat(cbuf, num);
	strcat(cbuf, "\r");
	write(FD, cbuf, strlen(cbuf));
	if (!detect("7\r")) {
		printf("can't get dial tone...");
		return (0);
	}
	if (boolean(value(VERBOSE)))
		printf("ringing...");
	/*
	 * The reply from the BIZCOMP should be:
	 *	2 \r or 7 \r	failure
	 *	1 \r		success
	 */
	connected = detect("1\r");
#ifdef ACULOG
	if (timeout) {
		char line[80];

		sprintf(line, "%d second dial timeout",
			number(value(DIALTIMEOUT)));
		logent(value(HOST), num, "biz1022", line);
	}
#endif
	if (timeout)
		biz22_disconnect();	/* insurance */
	return (connected);
}

biz22w_dialer(num, acu)
	char *num, *acu;
{
I 3

E 3
	return (biz_dialer(num, "W"));
}

biz22f_dialer(num, acu)
	char *num, *acu;
{
I 3

E 3
	return (biz_dialer(num, "V"));
}

biz22_disconnect()
{
D 3
	write(FD, DISCONNECT, 4);
E 3
I 3
	int rw = 2;

	write(FD, DISCONNECT_CMD, 4);
E 3
	sleep(2);
D 3
	ioctl(FD, TIOCFLUSH);
E 3
I 3
	ioctl(FD, TIOCFLUSH, &rw);
E 3
}

biz22_abort()
{
I 3

E 3
	write(FD, "\02", 1);
D 3
	timeout = 1;
E 3
}

D 7
static int
E 7
I 7
static void
E 7
sigALRM()
{
D 3
	signal(SIGALRM, SIG_IGN);
	printf("\07timeout waiting for reply\n");
E 3
I 3

E 3
	timeout = 1;
I 3
	longjmp(timeoutbuf, 1);
E 3
}

static int
cmd(s)
	register char *s;
{
I 7
	sig_t f;
E 7
	char c;
I 3
D 7
	int (*f)();
E 7
E 3

	write(FD, s, strlen(s));
D 3
	timeout = 0;
	signal(SIGALRM, biz22_abort);
E 3
I 3
	f = signal(SIGALRM, sigALRM);
	if (setjmp(timeoutbuf)) {
		biz22_abort();
		signal(SIGALRM, f);
		return (1);
	}
E 3
	alarm(number(value(DIALTIMEOUT)));
	read(FD, &c, 1);
	alarm(0);
D 3
	signal(SIGALRM, SIG_DFL);
	if (timeout)
		return (1);
E 3
I 3
	signal(SIGALRM, f);
E 3
	c &= 0177;
	return (c != '\r');
}

static int
detect(s)
	register char *s;
{
I 7
	sig_t f;
E 7
	char c;
I 3
D 7
	int (*f)();
E 7
E 3

D 3
	signal(SIGALRM, biz22_abort);
E 3
I 3
	f = signal(SIGALRM, sigALRM);
E 3
	timeout = 0;
	while (*s) {
I 3
		if (setjmp(timeoutbuf)) {
			biz22_abort();
			break;
		}
E 3
		alarm(number(value(DIALTIMEOUT)));
		read(FD, &c, 1);
		alarm(0);
D 3
		if (timeout)
			return (0);
E 3
		c &= 0177;
		if (c != *s++)
			return (0);
	}
D 3
	signal(SIGALRM, SIG_DFL);
	return (1);
E 3
I 3
	signal(SIGALRM, f);
	return (timeout == 0);
E 3
}
I 2
D 4
#endif
E 4
E 2
E 1
