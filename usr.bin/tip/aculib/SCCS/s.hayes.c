h34008
s 00002/00002/00277
d D 8.1 93/06/06 16:35:58 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00275
d D 5.4 91/03/02 10:26:42 bostic 5 4
c ANSI (real bug fix!)
e
s 00001/00011/00278
d D 5.3 90/06/01 17:46:19 bostic 4 3
c new copyright notice
e
s 00015/00004/00274
d D 5.2 88/09/13 17:03:52 bostic 3 2
c not derived from AT&T code; add Berkeley specific header
e
s 00008/00002/00270
d D 5.1 85/04/30 12:54:27 dist 2 1
c Add copyright
e
s 00272/00000/00000
d D 1.1 85/04/11 16:55:44 miriam 1 0
c date and time created 85/04/11 16:55:44 by miriam
e
u
U
t
T
I 2
/*
D 3
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
D 6
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 3
 */

E 2
I 1
#ifndef lint
D 2
static char sccsid[] = "@(#)%M%	%I% (Berkeley) %E% ";
#endif
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
#endif /* not lint */
E 3
E 2

/*
 * Routines for calling up on a Hayes Modem
 * (based on the old VenTel driver).
 * The modem is expected to be strapped for "echo".
 * Also, the switches enabling the DTR and CD lines
 * must be set correctly.
 * NOTICE:
 * The easy way to hang up a modem is always simply to
 * clear the DTR signal. However, if the +++ sequence
 * (which switches the modem back to local mode) is sent
 * before modem is hung up, removal of the DTR signal
 * has no effect (except that it prevents the modem from
 * recognizing commands).
 * (by Helge Skrivervik, Calma Company, Sunnyvale, CA. 1984) 
 */
/*
 * TODO:
 * It is probably not a good idea to switch the modem
 * state between 'verbose' and terse (status messages).
 * This should be kicked out and we should use verbose 
 * mode only. This would make it consistent with normal
 * interactive use thru the command 'tip dialer'.
 */
#include "tip.h"

#define	min(a,b)	((a < b) ? a : b)

D 5
static	int sigALRM();
E 5
I 5
static	void sigALRM();
E 5
static	int timeout = 0;
static	jmp_buf timeoutbuf;
static 	char gobble();
#define DUMBUFLEN	40
static char dumbuf[DUMBUFLEN];

#define	DIALING		1
#define IDLE		2
#define CONNECTED	3
#define	FAILED		4
static	int state = IDLE;

hay_dialer(num, acu)
	register char *num;
	char *acu;
{
	register char *cp;
	register int connected = 0;
	char dummy;
#ifdef ACULOG
	char line[80];
#endif
	if (hay_sync() == 0)		/* make sure we can talk to the modem */
		return(0);
	if (boolean(value(VERBOSE)))
		printf("\ndialing...");
	fflush(stdout);
	ioctl(FD, TIOCHPCL, 0);
	ioctl(FD, TIOCFLUSH, 0);	/* get rid of garbage */
	write(FD, "ATv0\r", 5);	/* tell modem to use short status codes */
	gobble("\r");
	gobble("\r");
	write(FD, "ATTD", 4);	/* send dial command */
	write(FD, num, strlen(num));
	state = DIALING;
	write(FD, "\r", 1);
	connected = 0;
	if (gobble("\r")) {
		if ((dummy = gobble("01234")) != '1')
			error_rep(dummy);
		else
			connected = 1;
	}
	if (connected)
		state = CONNECTED;
	else {
		state = FAILED;
		return (connected);	/* lets get out of here.. */
	}
	ioctl(FD, TIOCFLUSH, 0);
#ifdef ACULOG
	if (timeout) {
		sprintf(line, "%d second dial timeout",
			number(value(DIALTIMEOUT)));
		logent(value(HOST), num, "hayes", line);
	}
#endif
	if (timeout)
		hay_disconnect();	/* insurance */
	return (connected);
}


hay_disconnect()
{
	char c;
	int len, rlen;

	/* first hang up the modem*/
#ifdef DEBUG
	printf("\rdisconnecting modem....\n\r");
#endif
	ioctl(FD, TIOCCDTR, 0);
	sleep(1);
	ioctl(FD, TIOCSDTR, 0);
	goodbye();
}

hay_abort()
{

	char c;

	write(FD, "\r", 1);	/* send anything to abort the call */
	hay_disconnect();
}

D 5
static int
E 5
I 5
static void
E 5
sigALRM()
{

	printf("\07timeout waiting for reply\n\r");
	timeout = 1;
	longjmp(timeoutbuf, 1);
}

static char
gobble(match)
	register char *match;
{
	char c;
D 5
	int (*f)();
E 5
I 5
	sig_t f;
E 5
	int i, status = 0;

D 5
	signal(SIGALRM, sigALRM);
E 5
I 5
	f = signal(SIGALRM, sigALRM);
E 5
	timeout = 0;
#ifdef DEBUG
	printf("\ngobble: waiting for %s\n", match);
#endif
	do {
		if (setjmp(timeoutbuf)) {
			signal(SIGALRM, f);
			return (0);
		}
		alarm(number(value(DIALTIMEOUT)));
		read(FD, &c, 1);
		alarm(0);
		c &= 0177;
#ifdef DEBUG
		printf("%c 0x%x ", c, c);
#endif
		for (i = 0; i < strlen(match); i++)
			if (c == match[i])
				status = c;
	} while (status == 0);
	signal(SIGALRM, SIG_DFL);
#ifdef DEBUG
	printf("\n");
#endif
	return (status);
}

error_rep(c)
	register char c;
{
	printf("\n\r");
	switch (c) {

	case '0':
		printf("OK");
		break;

	case '1':
		printf("CONNECT");
		break;
	
	case '2':
		printf("RING");
		break;
	
	case '3':
		printf("NO CARRIER");
		break;
	
	case '4':
		printf("ERROR in input");
		break;
	
	case '5':
		printf("CONNECT 1200");
		break;
	
	default:
		printf("Unknown Modem error: %c (0x%x)", c, c);
	}
	printf("\n\r");
	return;
}

/*
 * set modem back to normal verbose status codes.
 */
goodbye()
{
	int len, rlen;
	char c;

	ioctl(FD, TIOCFLUSH, &len);	/* get rid of trash */
	if (hay_sync()) {
		sleep(1);
#ifndef DEBUG
		ioctl(FD, TIOCFLUSH, 0);
#endif
		write(FD, "ATH0\r", 5);		/* insurance */
#ifndef DEBUG
		c = gobble("03");
		if (c != '0' && c != '3') {
			printf("cannot hang up modem\n\r");
			printf("please use 'tip dialer' to make sure the line is hung up\n\r");
		}
#endif
		sleep(1);
		ioctl(FD, FIONREAD, &len);
#ifdef DEBUG
		printf("goodbye1: len=%d -- ", len);
		rlen = read(FD, dumbuf, min(len, DUMBUFLEN));
		dumbuf[rlen] = '\0';
		printf("read (%d): %s\r\n", rlen, dumbuf);
#endif
		write(FD, "ATv1\r", 5);
		sleep(1);
#ifdef DEBUG
		ioctl(FD, FIONREAD, &len);
		printf("goodbye2: len=%d -- ", len);
		rlen = read(FD, dumbuf, min(len, DUMBUFLEN));
		dumbuf[rlen] = '\0';
		printf("read (%d): %s\r\n", rlen, dumbuf);
#endif
	}
	ioctl(FD, TIOCFLUSH, 0);	/* clear the input buffer */
	ioctl(FD, TIOCCDTR, 0);		/* clear DTR (insurance) */
	close(FD);
}

#define MAXRETRY	5

hay_sync()
{
	int len, retry = 0;

	while (retry++ <= MAXRETRY) {
		write(FD, "AT\r", 3);
		sleep(1);
		ioctl(FD, FIONREAD, &len);
		if (len) {
			len = read(FD, dumbuf, min(len, DUMBUFLEN));
			if (index(dumbuf, '0') || 
		   	(index(dumbuf, 'O') && index(dumbuf, 'K')))
				return(1);
#ifdef DEBUG
			dumbuf[len] = '\0';
			printf("hay_sync: (\"%s\") %d\n\r", dumbuf, retry);
#endif
		}
		ioctl(FD, TIOCCDTR, 0);
		ioctl(FD, TIOCSDTR, 0);
	}
	printf("Cannot synchronize with hayes...\n\r");
	return(0);
}
E 1
