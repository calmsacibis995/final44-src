h50527
s 00002/00001/00212
d D 8.2 95/02/16 11:37:50 dab 29 28
c Make sure that if we get a failure from TerminalWrite
c that we don't screw up our character count by adding -1 to it...
e
s 00002/00002/00211
d D 8.1 93/06/06 16:33:47 bostic 28 27
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00211
d D 5.5 93/05/20 10:49:28 dab 27 25
c Mostly, this changes all the "#if defined(ENCRYPTION)"
c lines to "#ifdef ENCRYPTION".  This will allow unifdef
c to be used to strip out the encryption code for
c foreign exports.  This also fixes up the usage statement.
e
s 00002/00002/00211
d R 5.5 93/05/20 10:37:19 dab 26 25
c Mostly this changes "#if defined(ENCRYPTION)" to
c "#ifdef ENCRYPTION".  This will allow unifdef to be
e
s 00002/00002/00211
d D 5.4 92/12/18 14:06:49 dab 25 24
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Add Sun/SVR4 Streams support
c Allow for more ptys
c Environ suboption USERVAR support
c New Telnet Flowcontrol suboption support
c Server -k option to default to no kludge linemode
c Server -U option, allow only registered hosts to connect
e
s 00001/00001/00212
d D 5.3 91/03/22 13:09:01 dab 24 23
c Upgrade to the latest & greatest authentication/encryption
e
s 00033/00008/00180
d D 5.2 91/03/01 01:32:09 dab 23 22
c Telnet AUTHENTICATION option
c Telnet ENCRYPT option (test version)
c Function prototypes
e
s 00006/00002/00182
d D 5.1 90/09/14 10:48:36 borman 22 21
c Latest batch of changes.  See the README file
c for a list of all the changes to telnet & telnetd.
e
s 00011/00011/00173
d D 1.21 90/06/28 12:57:10 borman 21 20
c Lots of bugfixes, add the ENVIRON and X-DISPLAY-LOC
c options, "-l user" to the command line, diagnostic flags.
e
s 00001/00001/00183
d D 1.20 90/06/15 14:15:36 marc 20 19
c VFLUSHO -> VDISCARD
e
s 00001/00011/00183
d D 1.19 90/06/01 17:46:36 bostic 19 18
c new copyright notice
e
s 00008/00000/00186
d D 1.18 90/03/01 06:18:35 borman 18 17
c Several items:
c 1) Change from TC[GS]ETA* to TIOC[GS]ETA*
c 2) Use the cc_t typedef from terios.h
c 3) Add SLC_FORW support
c 4) Add TOS support
c 5) Fix the SLC_SUSP support.  The escape
c    character now uses one of the VEOL characters.
e
s 00027/00008/00159
d D 1.17 89/11/14 10:20:07 borman 17 16
c Latest & greatest version of telnet
e
s 00050/00028/00117
d D 1.16 89/08/21 14:58:59 borman 16 15
c Add support for LINEMODE option
e
s 00005/00000/00140
d D 1.15 89/05/30 22:14:46 minshall 15 14
c Add two toggles: termdata, cursesdata.
e
s 00002/00002/00138
d D 1.14 89/03/21 22:30:41 minshall 14 13
c Keep track of each side's idea of what the state of each option is.
e
s 00010/00005/00130
d D 1.13 88/06/29 20:15:37 bostic 13 12
c install approved copyright notice
e
s 00008/00002/00127
d D 1.12 88/06/27 22:19:14 minshall 12 11
c Fix up lint errors.
e
s 00016/00000/00113
d D 1.11 88/03/08 10:31:18 bostic 11 10
c add Berkeley specific copyright
e
s 00004/00004/00109
d D 1.10 88/01/07 11:54:04 minshall 10 9
c Reduce extern's.
e
s 00015/00003/00098
d D 1.9 87/11/23 20:37:56 minshall 9 8
c Fixes from Dave Borman.
e
s 00000/00039/00101
d D 1.8 87/10/27 16:00:14 minshall 8 7
c Remove some unix specific things.
e
s 00003/00002/00137
d D 1.7 87/10/23 15:15:41 minshall 7 6
c Try to move system dependent stuff to system dependent files.
e
s 00003/00003/00136
d D 1.6 87/10/23 11:57:19 minshall 6 5
c Make the ring buffer a two-state buffer (supplier and consumer)
c rather than a three-state buffer (supplier, sender, and acker).
e
s 00001/00001/00138
d D 1.5 87/10/10 17:45:46 minshall 5 4
c sending is also acking.
e
s 00009/00008/00130
d D 1.4 87/10/10 14:27:20 minshall 4 3
c This is the first version to get near rings.  It compiles,
c but doesn't work.
e
s 00005/00004/00133
d D 1.3 87/09/25 16:06:49 minshall 3 2
c Cut down on number of extern's.
e
s 00000/00227/00137
d D 1.2 87/09/25 14:49:49 minshall 2 1
c Move a number of tn3270-items to tn3270.c
e
s 00364/00000/00000
d D 1.1 87/09/11 15:40:50 minshall 1 0
c date and time created 87/09/11 15:40:50 by minshall
e
u
U
t
T
I 11
/*
D 22
 * Copyright (c) 1988 Regents of the University of California.
E 22
I 22
D 28
 * Copyright (c) 1988, 1990 Regents of the University of California.
E 22
 * All rights reserved.
E 28
I 28
 * Copyright (c) 1988, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 28
 *
D 19
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
E 19
I 19
 * %sccs.include.redist.c%
E 19
E 13
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 11
I 1
#include <arpa/telnet.h>
I 4
#include <sys/types.h>
E 4

I 4
#include "ring.h"

E 4
#include "externs.h"
#include "types.h"

D 4
char	ttyobuf[2*BUFSIZ], *tfrontp, *tbackp;
E 4
I 4
D 7
Ring	ttyoring;
char	ttyobuf[2*BUFSIZ];
E 7
I 7
D 23
Ring	ttyoring, ttyiring;
char	ttyobuf[2*BUFSIZ], ttyibuf[BUFSIZ];
E 23
I 23
Ring		ttyoring, ttyiring;
unsigned char	ttyobuf[2*BUFSIZ], ttyibuf[BUFSIZ];
E 23
E 7
E 4

I 15
int termdata;			/* Debugging flag */

I 16
#ifdef	USE_TERMIO
E 16
E 15
D 17
char
D 16
    termEofChar,
    termEraseChar,
E 16
    termFlushChar,
D 16
    termIntChar,
    termKillChar,
I 12
#if	defined(MSDOS)
E 16
E 12
    termLiteralNextChar,
I 12
D 16
#endif	/* defined(MSDOS) */
E 12
    termQuitChar;
E 16
I 16
    termSuspChar,
    termWerasChar,
    termRprntChar,
    termStartChar,
    termStopChar;
E 17
I 17
D 20
# ifndef VFLUSHO
E 20
I 20
D 21
# ifndef VDISCARD
E 20
char termFlushChar;
E 21
I 21
D 22
# ifndef VFLUSHO
E 22
I 22
# ifndef VDISCARD
E 22
cc_t termFlushChar;
E 21
# endif
# ifndef VLNEXT
D 21
char termLiteralNextChar;
E 21
I 21
cc_t termLiteralNextChar;
E 21
# endif
# ifndef VSUSP
D 21
char termSuspChar;
E 21
I 21
cc_t termSuspChar;
E 21
# endif
# ifndef VWERASE
D 21
char termWerasChar;
E 21
I 21
cc_t termWerasChar;
E 21
# endif
# ifndef VREPRINT
D 21
char termRprntChar;
E 21
I 21
cc_t termRprntChar;
E 21
# endif
# ifndef VSTART
D 21
char termStartChar;
E 21
I 21
cc_t termStartChar;
E 21
# endif
# ifndef VSTOP
D 21
char termStopChar;
E 21
I 21
cc_t termStopChar;
E 21
# endif
I 18
# ifndef VEOL
D 21
char termForw1Char;
E 21
I 21
cc_t termForw1Char;
E 21
# endif
# ifndef VEOL2
D 21
char termForw2Char;
E 21
I 21
cc_t termForw2Char;
E 21
# endif
I 22
# ifndef VSTATUS
cc_t termAytChar;
# endif
E 22
#else
D 21
char termForw2Char;
E 21
I 21
cc_t termForw2Char;
I 22
cc_t termAytChar;
E 22
E 21
E 18
E 17
#endif
E 16

/*
 * initialize the terminal data structures.
 */

I 23
    void
E 23
init_terminal()
{
D 4
    tfrontp = tbackp = ttyobuf;
E 4
I 4
D 12
    ring_init(&ttyoring, ttyobuf, sizeof ttyobuf);
I 7
    ring_init(&ttyiring, ttyibuf, sizeof ttyibuf);
E 12
I 12
    if (ring_init(&ttyoring, ttyobuf, sizeof ttyobuf) != 1) {
	exit(1);
    }
    if (ring_init(&ttyiring, ttyibuf, sizeof ttyibuf) != 1) {
	exit(1);
    }
E 12
E 7
E 4
    autoflush = TerminalAutoFlush();
}


/*
 *		Send as much data as possible to the terminal.
 *
D 16
 *		The return value indicates whether we did any
 *	useful work.
E 16
I 16
 *		Return value:
 *			-1: No useful work done, data waiting to go out.
 *			 0: No data was waiting, so nothing was done.
 *			 1: All waiting data was written out.
 *			 n: All data - n was written out.
E 16
 */


D 23
int
E 23
I 23
    int
E 23
D 3
ttyflush()
E 3
I 3
ttyflush(drop)
D 23
int drop;
E 23
I 23
    int drop;
E 23
E 3
{
D 9
    int n;
E 9
I 9
    register int n, n0, n1;
E 9

D 4
    if ((n = tfrontp - tbackp) > 0) {
E 4
I 4
D 6
    if ((n = ring_unsent_consecutive(&ttyoring)) > 0) {
E 6
I 6
D 9
    if ((n = ring_full_consecutive(&ttyoring)) > 0) {
E 9
I 9
    n0 = ring_full_count(&ttyoring);
    if ((n1 = n = ring_full_consecutive(&ttyoring)) > 0) {
E 9
E 6
E 4
D 3
	if (!(SYNCHing||flushout)) {
	    n = TerminalWrite(tout, tbackp, n);
	} else {
E 3
I 3
	if (drop) {
E 3
	    TerminalFlushOutput();
	    /* we leave 'n' alone! */
I 3
	} else {
D 4
	    n = TerminalWrite(tout, tbackp, n);
E 4
I 4
D 6
	    n = TerminalWrite(tout, ttyoring.send, n);
E 6
I 6
D 10
	    n = TerminalWrite(tout, ttyoring.consume, n);
E 10
I 10
	    n = TerminalWrite(ttyoring.consume, n);
E 10
E 6
E 4
E 3
	}
    }
D 9
    if (n >= 0) {
E 9
I 9
    if (n > 0) {
I 15
	if (termdata && n) {
	    Dump('>', ttyoring.consume, n);
	}
E 15
	/*
	 * If we wrote everything, and the full count is
	 * larger than what we wrote, then write the
	 * rest of the buffer.
	 */
	if (n1 == n && n0 > n) {
		n1 = n0 - n;
		if (!drop)
D 10
			n1 = TerminalWrite(tout, ttyoring.bottom, n1);
E 10
I 10
			n1 = TerminalWrite(ttyoring.bottom, n1);
E 10
D 29
		n += n1;
E 29
I 29
		if (n1 > 0)
			n += n1;
E 29
	}
E 9
D 4
	tbackp += n;
	if (tbackp == tfrontp) {
	    tbackp = tfrontp = ttyobuf;
	}
E 4
I 4
D 5
	ring_sent(&ttyoring, n);
E 5
I 5
D 6
	ring_sent_acked(&ttyoring, n);
E 6
I 6
	ring_consumed(&ttyoring, n);
E 6
E 5
E 4
    }
D 16
    return n > 0;
E 16
I 16
    if (n < 0)
	return -1;
    if (n == n0) {
	if (n0)
	    return -1;
	return 0;
    }
    return n0 - n + 1;
E 16
}

D 2
#if	defined(TN3270)

#if	defined(unix)
static void
inputAvailable()
{
    HaveInput = 1;
}
#endif	/* defined(unix) */

void
outputPurge()
{
    int tmp = flushout;

    flushout = 1;

    ttyflush();

    flushout = tmp;
}

#endif	/* defined(TN3270) */
E 2

D 8
#if	defined(unix)
/*
 * Various signal handling routines.
 */

void
deadpeer()
{
	setcommandmode();
	longjmp(peerdied, -1);
}

void
intr()
{
    if (localchars) {
	intp();
	return;
    }
    setcommandmode();
    longjmp(toplevel, -1);
}

void
intr2()
{
    if (localchars) {
	sendbrk();
	return;
    }
}

void
doescape()
{
    command(0);
}
#endif	/* defined(unix) */

E 8
/*
 * These routines decides on what the mode should be (based on the values
 * of various global variables).
 */


D 23
int
E 23
I 23
    int
E 23
getconnmode()
{
D 16
    static char newmode[16] =
			{ 4, 5, 3, 3, 2, 2, 1, 1, 6, 6, 6, 6, 6, 6, 6, 6 };
    int modeindex = 0;
E 16
I 16
    extern int linemode;
    int mode = 0;
#ifdef	KLUDGELINEMODE
    extern int kludgelinemode;
#endif
E 16

D 16
    if (dontlecho && (clocks.echotoggle > clocks.modenegotiated)) {
	modeindex += 1;
E 16
I 16
    if (In3270)
	return(MODE_FLOW);

    if (my_want_state_is_dont(TELOPT_ECHO))
	mode |= MODE_ECHO;

    if (localflow)
	mode |= MODE_FLOW;
I 17

    if (my_want_state_is_will(TELOPT_BINARY))
	mode |= MODE_INBIN;

    if (his_want_state_is_will(TELOPT_BINARY))
	mode |= MODE_OUTBIN;
E 17

#ifdef	KLUDGELINEMODE
    if (kludgelinemode) {
	if (my_want_state_is_dont(TELOPT_SGA)) {
	    mode |= (MODE_TRAPSIG|MODE_EDIT);
	    if (dontlecho && (clocks.echotoggle > clocks.modenegotiated)) {
		mode &= ~MODE_ECHO;
	    }
	}
	return(mode);
E 16
    }
D 14
    if (hisopts[TELOPT_ECHO]) {
E 14
I 14
D 16
    if (should_he(TELOPT_ECHO)) {
E 14
	modeindex += 2;
    }
D 14
    if (hisopts[TELOPT_SGA]) {
E 14
I 14
    if (should_he(TELOPT_SGA)) {
E 14
	modeindex += 4;
    }
    if (In3270) {
	modeindex += 8;
    }
    return newmode[modeindex];
E 16
I 16
#endif
    if (my_want_state_is_will(TELOPT_LINEMODE))
	mode |= linemode;
    return(mode);
E 16
}

D 23
void
E 23
I 23
    void
E 23
D 16
setconnmode()
E 16
I 16
setconnmode(force)
I 23
    int force;
E 23
E 16
{
D 10
    TerminalNewMode(tin, tout, getconnmode());
E 10
I 10
D 16
    TerminalNewMode(getconnmode());
E 16
I 16
D 23
    TerminalNewMode(getconnmode()|(force?MODE_FORCE:0));
E 23
I 23
D 25
#ifdef	ENCRYPT
E 25
I 25
#ifdef	ENCRYPTION
E 25
    static int enc_passwd = 0;
D 27
#endif
E 27
I 27
#endif	/* ENCRYPTION */
E 27
    register int newmode;

    newmode = getconnmode()|(force?MODE_FORCE:0);

    TerminalNewMode(newmode);

D 25
#ifdef  ENCRYPT
E 25
I 25
#ifdef  ENCRYPTION
E 25
    if ((newmode & (MODE_ECHO|MODE_EDIT)) == MODE_EDIT) {
	if (my_want_state_is_will(TELOPT_ENCRYPT)
				&& (enc_passwd == 0) && !encrypt_output) {
D 24
	    encrypt_request_start();
E 24
I 24
	    encrypt_request_start(0, 0);
E 24
	    enc_passwd = 1;
	}
    } else {
	if (enc_passwd) {
	    encrypt_request_end();
	    enc_passwd = 0;
	}
    }
D 27
#endif
E 27
I 27
#endif	/* ENCRYPTION */
E 27

E 23
E 16
E 10
}


D 23
void
E 23
I 23
    void
E 23
setcommandmode()
{
D 10
    TerminalNewMode(tin, tout, 0);
E 10
I 10
D 16
    TerminalNewMode(0);
E 16
I 16
    TerminalNewMode(-1);
E 16
E 10
}
D 2

#if	defined(TN3270)

/*
 * The following routines are places where the various tn3270
 * routines make calls into telnet.c.
 */

/* TtyChars() - returns the number of characters in the TTY buffer */
TtyChars()
{
    return(tfrontp-tbackp);
}

/*
 * DataToNetwork - queue up some data to go to network.  If "done" is set,
 * then when last byte is queued, we add on an IAC EOR sequence (so,
 * don't call us with "done" until you want that done...)
 *
 * We actually do send all the data to the network buffer, since our
 * only client needs for us to do that.
 */

int
DataToNetwork(buffer, count, done)
register char	*buffer;	/* where the data is */
register int	count;		/* how much to send */
int		done;		/* is this the last of a logical block */
{
    register int c;
    int origCount;
    fd_set o;

    origCount = count;
    FD_ZERO(&o);

    while (count) {
	if ((netobuf+sizeof netobuf - nfrontp) < 6) {
	    netflush();
	    while ((netobuf+sizeof netobuf - nfrontp) < 6) {
		FD_SET(net, &o);
		(void) select(net+1, (fd_set *) 0, &o, (fd_set *) 0,
						(struct timeval *) 0);
		netflush();
	    }
	}
	c = *buffer++;
	count--;
	if (c == IAC) {
	    *nfrontp++ = IAC;
	    *nfrontp++ = IAC;
	} else {
	    *nfrontp++ = c;
	}
    }

    if (done && !count) {
	*nfrontp++ = IAC;
	*nfrontp++ = EOR;
	netflush();		/* try to move along as quickly as ... */
    }
    return(origCount - count);
}

/* DataToTerminal - queue up some data to go to terminal. */

int
DataToTerminal(buffer, count)
register char	*buffer;		/* where the data is */
register int	count;			/* how much to send */
{
    int origCount;
#if	defined(unix)
    fd_set	o;

    FD_ZERO(&o);
#endif	/* defined(unix) */
    origCount = count;

    while (count) {
	if (tfrontp >= ttyobuf+sizeof ttyobuf) {
	    ttyflush();
	    while (tfrontp >= ttyobuf+sizeof ttyobuf) {
#if	defined(unix)
		FD_SET(tout, &o);
		(void) select(tout+1, (fd_set *) 0, &o, (fd_set *) 0,
						(struct timeval *) 0);
#endif	/* defined(unix) */
		ttyflush();
	    }
	}
	*tfrontp++ = *buffer++;
	count--;
    }
    return(origCount - count);
}

/* EmptyTerminal - called to make sure that the terminal buffer is empty.
 *			Note that we consider the buffer to run all the
 *			way to the kernel (thus the select).
 */

void
EmptyTerminal()
{
#if	defined(unix)
    fd_set	o;

    FD_ZERO(&o);
#endif	/* defined(unix) */

    if (tfrontp == tbackp) {
#if	defined(unix)
	FD_SET(tout, &o);
	(void) select(tout+1, (int *) 0, &o, (int *) 0,
			(struct timeval *) 0);	/* wait for TTLOWAT */
#endif	/* defined(unix) */
    } else {
	while (tfrontp != tbackp) {
	    ttyflush();
#if	defined(unix)
	    FD_SET(tout, &o);
	    (void) select(tout+1, (int *) 0, &o, (int *) 0,
				(struct timeval *) 0);	/* wait for TTLOWAT */
#endif	/* defined(unix) */
	}
    }
}


/*
 * Push3270 - Try to send data along the 3270 output (to screen) direction.
 */

static int
Push3270()
{
    int save = scc;

    if (scc) {
	if (Ifrontp+scc > Ibuf+sizeof Ibuf) {
	    if (Ibackp != Ibuf) {
		memcpy(Ibuf, Ibackp, Ifrontp-Ibackp);
		Ifrontp -= (Ibackp-Ibuf);
		Ibackp = Ibuf;
	    }
	}
	if (Ifrontp+scc < Ibuf+sizeof Ibuf) {
	    telrcv();
	}
    }
    return save != scc;
}


/*
 * Finish3270 - get the last dregs of 3270 data out to the terminal
 *		before quitting.
 */

static void
Finish3270()
{
    while (Push3270() || !DoTerminalOutput()) {
#if	defined(unix)
	HaveInput = 0;
#endif	/* defined(unix) */
	;
    }
}


/* StringToTerminal - output a null terminated string to the terminal */

void
StringToTerminal(s)
char *s;
{
    int count;

    count = strlen(s);
    if (count) {
	(void) DataToTerminal(s, count);	/* we know it always goes... */
    }
}


#if	((!defined(NOT43)) || defined(PUTCHAR))
/* _putchar - output a single character to the terminal.  This name is so that
 *	curses(3x) can call us to send out data.
 */

void
_putchar(c)
char c;
{
    if (tfrontp >= ttyobuf+sizeof ttyobuf) {
	(void) DataToTerminal(&c, 1);
    } else {
	*tfrontp++ = c;		/* optimize if possible. */
    }
}
#endif	/* ((!defined(NOT43)) || defined(PUTCHAR)) */
#endif	/* defined(TN3270) */
E 2
E 1
