h43615
s 00001/00001/00384
d D 8.2 95/05/30 20:57:18 dab 28 27
c code cleanup, change b*() calls to mem*() calls
e
s 00002/00002/00383
d D 8.1 93/06/06 16:33:51 bostic 27 26
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00382
d D 5.5 93/05/21 09:19:01 bostic 26 25
c settranscom has to return an int to be in the commands table
e
s 00002/00001/00382
d D 5.4 93/05/11 10:02:12 bostic 25 24
c make tn3270 compile again
e
s 00001/00001/00382
d D 5.3 93/05/11 09:11:10 bostic 24 23
c mve telextrn.h into the sys_curses subdirectory
e
s 00019/00018/00364
d D 5.2 91/03/01 01:31:54 dab 23 22
c Telnet AUTHENTICATION option
c Telnet ENCRYPT option (test version)
c Function prototypes
e
s 00000/00000/00382
d D 5.1 90/09/14 10:42:08 borman 22 21
c Bump the sccs id to 5.1
e
s 00004/00004/00378
d D 1.21 90/06/28 12:57:28 borman 21 20
c Lots of bugfixes, add the ENVIRON and X-DISPLAY-LOC
c options, "-l user" to the command line, diagnostic flags.
e
s 00001/00011/00381
d D 1.20 90/06/01 17:46:45 bostic 20 19
c new copyright notice
e
s 00005/00005/00387
d D 1.19 89/08/21 14:59:01 borman 19 18
c Add support for LINEMODE option
e
s 00004/00000/00388
d D 1.18 89/05/30 22:14:49 minshall 18 17
c Add two toggles: termdata, cursesdata.
e
s 00002/00002/00386
d D 1.17 89/03/21 22:30:44 minshall 17 16
c Keep track of each side's idea of what the state of each option is.
e
s 00000/00079/00388
d D 1.16 88/11/30 22:27:57 minshall 16 15
c Flush out the last dregs in the terminal before quitting when
c the remote side quits (actually, there *may* be something left in the
c network input ring, so we don't actually guarantee to get everything).
e
s 00010/00001/00457
d D 1.15 88/11/18 22:30:10 minshall 15 14
c Count SIGIO's (for debugging).  Don't worry if there is just *one*
c byte in the TTY buffer.
e
s 00003/00000/00455
d D 1.14 88/11/04 17:57:03 minshall 14 13
c In SunOS 4.0, high order bits (sent from curses sometimes)
c can cause problems.
e
s 00011/00009/00444
d D 1.13 88/08/28 17:46:48 minshall 13 12
c Some linting of tn3270.
e
s 00010/00005/00443
d D 1.12 88/06/29 20:15:39 bostic 12 11
c install approved copyright notice
e
s 00000/00000/00448
d D 1.11 88/06/27 22:19:22 minshall 11 10
c Fix up lint errors.
e
s 00001/00001/00447
d D 1.10 88/05/15 20:49:22 minshall 10 9
c buffer is signed, but IAC is 0x255 (the twain shall never meet).
e
s 00002/00000/00446
d D 1.9 88/05/15 19:24:37 minshall 9 8
c Include "general.h" to get rid of ansi mem* functions.
e
s 00023/00017/00423
d D 1.8 88/05/15 12:47:15 minshall 8 7
c make it work for tn3270.
e
s 00111/00080/00329
d D 1.7 88/03/27 13:47:44 minshall 7 6
c Make *compiles* with -DTN3270 work.
e
s 00016/00000/00393
d D 1.6 88/03/08 10:31:20 bostic 6 5
c add Berkeley specific copyright
e
s 00002/00000/00391
d D 1.5 87/11/23 11:15:32 minshall 5 4
c Add in some changes from Dave Borman (borman@monet).
e
s 00027/00000/00364
d D 1.4 87/10/27 16:00:44 minshall 4 3
c Pick up some more tn3270-specific function.
e
s 00131/00000/00233
d D 1.3 87/10/23 15:15:43 minshall 3 2
c Try to move system dependent stuff to system dependent files.
e
s 00004/00010/00229
d D 1.2 87/09/25 16:06:51 minshall 2 1
c Cut down on number of extern's.
e
s 00239/00000/00000
d D 1.1 87/09/15 13:45:08 minshall 1 0
c date and time created 87/09/15 13:45:08 by minshall
e
u
U
t
T
I 6
/*
D 27
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 27
I 27
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 27
 *
D 20
 * Redistribution and use in source and binary forms are permitted
D 12
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 12
I 12
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
E 12
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 7
#include <sys/types.h>
#include <arpa/telnet.h>

I 9
#include "general.h"

E 9
#include "defines.h"
#include "ring.h"
#include "externs.h"
E 7
E 6
I 5
#include "fdset.h"

E 5
I 1
D 7
void
tn3270_init()
{
E 7
#if	defined(TN3270)
D 7
    Sent3270TerminalType = 0;
    Ifrontp = Ibackp = Ibuf;
    init_ctlr();		/* Initialize some things */
    init_keyboard();
    init_screen();
    init_system();
#endif	/* defined(TN3270) */
}
E 7

D 7
#if	defined(TN3270)
E 7
I 7
#include "../ctlr/screen.h"
#include "../general/globals.h"
E 7

I 13
D 24
#include "../telextrn.h"
E 24
I 24
#include "../sys_curses/telextrn.h"
E 24
#include "../ctlr/externs.h"

E 13
I 7
#if	defined(unix)
I 15
int
	HaveInput,		/* There is input available to scan */
I 18
	cursesdata,		/* Do we dump curses data? */
E 18
	sigiocount;		/* Number of times we got a SIGIO */

E 15
char	tline[200];
char	*transcom = 0;	/* transparent mode command (default: none) */
#endif	/* defined(unix) */
E 7
I 3

D 7
static char	Ibuf[8*BUFSIZ], *Ifrontp, *Ibackp;
E 7
I 7
char	Ibuf[8*BUFSIZ], *Ifrontp, *Ibackp;
E 7

static char	sb_terminal[] = { IAC, SB,
			TELOPT_TTYPE, TELQUAL_IS,
			'I', 'B', 'M', '-', '3', '2', '7', '8', '-', '2',
			IAC, SE };
#define	SBTERMMODEL	13

static int
	Sent3270TerminalType;	/* Have we said we are a 3270? */

I 7
#endif	/* defined(TN3270) */
E 7

I 4
D 7
#if	defined(unix)
static
settranscom(argc, argv)
	int argc;
	char *argv[];
{
	int i, len = 0;
	char *strcpy(), *strcat();
E 7

D 7
	if (argc == 1 && transcom) {
	   transcom = 0;
	}
	if (argc == 1) {
	   return;
	}
	for (i = 1; i < argc; ++i) {
	    len += 1 + strlen(argv[1]);
	}
	transcom = tline;
	(void) strcpy(transcom, argv[1]);
	for (i = 2; i < argc; ++i) {
	    (void) strcat(transcom, " ");
	    (void) strcat(transcom, argv[i]);
	}
E 7
I 7
D 23
void
E 23
I 23
    void
E 23
D 8
tn3270_init()
E 8
I 8
init_3270()
E 8
{
#if	defined(TN3270)
I 15
#if	defined(unix)
    HaveInput = 0;
    sigiocount = 0;
#endif	/* defined(unix) */
E 15
    Sent3270TerminalType = 0;
    Ifrontp = Ibackp = Ibuf;
    init_ctlr();		/* Initialize some things */
    init_keyboard();
    init_screen();
    init_system();
#endif	/* defined(TN3270) */
E 7
}
D 7
#endif	/* defined(unix) */
E 7

I 7

#if	defined(TN3270)

E 7
E 4
E 3
/*
 * DataToNetwork - queue up some data to go to network.  If "done" is set,
 * then when last byte is queued, we add on an IAC EOR sequence (so,
 * don't call us with "done" until you want that done...)
 *
 * We actually do send all the data to the network buffer, since our
 * only client needs for us to do that.
 */

D 23
int
E 23
I 23
    int
E 23
DataToNetwork(buffer, count, done)
D 23
register char	*buffer;	/* where the data is */
register int	count;		/* how much to send */
int		done;		/* is this the last of a logical block */
E 23
I 23
    register char *buffer;	/* where the data is */
    register int  count;	/* how much to send */
    int		  done;		/* is this the last of a logical block */
E 23
{
D 7
    register int c;
E 7
I 7
    register int loop, c;
E 7
    int origCount;
D 7
    fd_set o;
E 7

    origCount = count;
D 7
    FD_ZERO(&o);
E 7

    while (count) {
I 8
	/* If not enough room for EORs, IACs, etc., wait */
E 8
D 7
	if ((netobuf+sizeof netobuf - nfrontp) < 6) {
E 7
I 7
	if (NETROOM() < 6) {
	    fd_set o;

	    FD_ZERO(&o);
E 7
	    netflush();
D 7
	    while ((netobuf+sizeof netobuf - nfrontp) < 6) {
E 7
I 7
	    while (NETROOM() < 6) {
E 7
		FD_SET(net, &o);
		(void) select(net+1, (fd_set *) 0, &o, (fd_set *) 0,
						(struct timeval *) 0);
		netflush();
	    }
	}
D 7
	c = *buffer++;
	count--;
	if (c == IAC) {
	    *nfrontp++ = IAC;
	    *nfrontp++ = IAC;
	} else {
	    *nfrontp++ = c;
E 7
I 7
D 8
	c = loop = ring_empty_consecutive(&netoring);
E 8
I 8
	c = ring_empty_count(&netoring);
	if (c > count) {
	    c = count;
	}
	loop = c;
E 8
	while (loop) {
D 10
	    if (*buffer == IAC) {
E 10
I 10
	    if (((unsigned char)*buffer) == IAC) {
E 10
		break;
	    }
	    buffer++;
	    loop--;
E 7
	}
I 7
	if ((c = c-loop)) {
	    ring_supply_data(&netoring, buffer-c, c);
	    count -= c;
	}
	if (loop) {
	    NET2ADD(IAC, IAC);
	    count--;
I 8
	    buffer++;
E 8
	}
E 7
    }

D 7
    if (done && !count) {
	*nfrontp++ = IAC;
	*nfrontp++ = EOR;
E 7
I 7
    if (done) {
D 8
	NET2ADD(IAC, IAC);
E 8
I 8
	NET2ADD(IAC, EOR);
E 8
E 7
	netflush();		/* try to move along as quickly as ... */
    }
    return(origCount - count);
}


#if	defined(unix)
D 7
static void
E 7
I 7
D 23
void
E 23
I 23
    void
E 23
E 7
D 25
inputAvailable()
E 25
I 25
inputAvailable(signo)
	int signo;
E 25
{
    HaveInput = 1;
I 15
    sigiocount++;
E 15
}
#endif	/* defined(unix) */

D 23
void
E 23
I 23
    void
E 23
outputPurge()
{
D 2
    int tmp = flushout;

    flushout = 1;

    ttyflush();

    flushout = tmp;
E 2
I 2
D 21
    ttyflush(1);
E 21
I 21
    (void) ttyflush(1);
E 21
E 2
}


/*
 * The following routines are places where the various tn3270
 * routines make calls into telnet.c.
 */

D 7
/* TtyChars() - returns the number of characters in the TTY buffer */
TtyChars()
{
    return(tfrontp-tbackp);
}

E 7
D 8
/* DataToTerminal - queue up some data to go to terminal. */
E 8
I 8
/*
 * DataToTerminal - queue up some data to go to terminal.
 *
 * Note: there are people who call us and depend on our processing
 * *all* the data at one time (thus the select).
 */
E 8

D 23
int
E 23
I 23
    int
E 23
DataToTerminal(buffer, count)
D 23
register char	*buffer;		/* where the data is */
register int	count;			/* how much to send */
E 23
I 23
    register char	*buffer;		/* where the data is */
    register int	count;			/* how much to send */
E 23
{
I 7
D 13
    register int loop, c;
E 13
I 13
    register int c;
E 13
E 7
    int origCount;
D 7
#if	defined(unix)
    fd_set	o;
E 7

D 7
    FD_ZERO(&o);
#endif	/* defined(unix) */
E 7
    origCount = count;

    while (count) {
D 7
	if (tfrontp >= ttyobuf+sizeof ttyobuf) {
D 2
	    ttyflush();
E 2
I 2
	    ttyflush(0);
E 2
	    while (tfrontp >= ttyobuf+sizeof ttyobuf) {
E 7
I 7
	if (TTYROOM() == 0) {
E 7
#if	defined(unix)
I 7
	    fd_set o;

	    FD_ZERO(&o);
#endif	/* defined(unix) */
D 13
	    ttyflush();
E 13
I 13
D 21
	    ttyflush(0);
E 21
I 21
	    (void) ttyflush(0);
E 21
E 13
	    while (TTYROOM() == 0) {
#if	defined(unix)
E 7
		FD_SET(tout, &o);
		(void) select(tout+1, (fd_set *) 0, &o, (fd_set *) 0,
						(struct timeval *) 0);
#endif	/* defined(unix) */
D 2
		ttyflush();
E 2
I 2
D 7
		ttyflush(0);
E 7
I 7
D 13
		ttyflush();
E 13
I 13
D 21
		ttyflush(0);
E 21
I 21
		(void) ttyflush(0);
E 21
E 13
E 7
E 2
	    }
	}
D 7
	*tfrontp++ = *buffer++;
	count--;
E 7
I 7
D 8
	c = loop = ring_empty_consecutive(&ttyoring);
	while (loop) {
	    if (*buffer == IAC) {
		break;
	    }
	    buffer++;
	    loop--;
E 8
I 8
	c = TTYROOM();
	if (c > count) {
	    c = count;
E 8
	}
D 8
	if ((c = c-loop)) {
	    ring_supply_data(&ttyoring, buffer-c, c);
	    count -= c;
	}
E 8
I 8
	ring_supply_data(&ttyoring, buffer, c);
	count -= c;
	buffer += c;
E 8
E 7
    }
D 8
    return(origCount - count);
E 8
I 8
    return(origCount);
E 8
}
D 16

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

D 7
    if (tfrontp == tbackp) {
E 7
I 7
D 8
    if (TTYBYTES()) {
E 8
I 8
    if (TTYBYTES() == 0) {
E 8
E 7
#if	defined(unix)
	FD_SET(tout, &o);
D 13
	(void) select(tout+1, (int *) 0, &o, (int *) 0,
E 13
I 13
	(void) select(tout+1, (fd_set *) 0, &o, (fd_set *) 0,
E 13
			(struct timeval *) 0);	/* wait for TTLOWAT */
#endif	/* defined(unix) */
    } else {
D 7
	while (tfrontp != tbackp) {
E 7
I 7
	while (TTYBYTES()) {
E 7
D 2
	    ttyflush();
E 2
I 2
	    ttyflush(0);
E 2
#if	defined(unix)
	    FD_SET(tout, &o);
D 13
	    (void) select(tout+1, (int *) 0, &o, (int *) 0,
E 13
I 13
	    (void) select(tout+1, (fd_set *) 0, &o, (fd_set *) 0,
E 13
				(struct timeval *) 0);	/* wait for TTLOWAT */
#endif	/* defined(unix) */
	}
    }
}
E 16


/*
 * Push3270 - Try to send data along the 3270 output (to screen) direction.
 */

D 7
static int
E 7
I 7
D 23
int
E 23
I 23
    int
E 23
E 7
Push3270()
{
D 7
    int save = scc;
E 7
I 7
    int save = ring_full_count(&netiring);
E 7

D 7
    if (scc) {
	if (Ifrontp+scc > Ibuf+sizeof Ibuf) {
E 7
I 7
    if (save) {
	if (Ifrontp+save > Ibuf+sizeof Ibuf) {
E 7
	    if (Ibackp != Ibuf) {
D 28
		memcpy(Ibuf, Ibackp, Ifrontp-Ibackp);
E 28
I 28
		memmove(Ibuf, Ibackp, Ifrontp-Ibackp);
E 28
		Ifrontp -= (Ibackp-Ibuf);
		Ibackp = Ibuf;
	    }
	}
D 7
	if (Ifrontp+scc < Ibuf+sizeof Ibuf) {
E 7
I 7
	if (Ifrontp+save < Ibuf+sizeof Ibuf) {
E 7
D 21
	    telrcv();
E 21
I 21
	    (void)telrcv();
E 21
	}
    }
D 7
    return save != scc;
E 7
I 7
    return save != ring_full_count(&netiring);
E 7
}


/*
 * Finish3270 - get the last dregs of 3270 data out to the terminal
 *		before quitting.
 */

D 7
static void
E 7
I 7
D 23
void
E 23
I 23
    void
E 23
E 7
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

D 23
void
E 23
I 23
    void
E 23
StringToTerminal(s)
D 23
char *s;
E 23
I 23
    char *s;
E 23
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

D 23
void
E 23
I 23
    void
E 23
_putchar(c)
D 23
char c;
E 23
I 23
    char c;
E 23
{
I 14
#if	defined(sun)		/* SunOS 4.0 bug */
    c &= 0x7f;
#endif	/* defined(sun) */
I 18
    if (cursesdata) {
	Dump('>', &c, 1);
    }
E 18
E 14
D 7
    if (tfrontp >= ttyobuf+sizeof ttyobuf) {
E 7
I 7
D 15
    if (TTYBYTES()) {
E 15
I 15
    if (!TTYROOM()) {
E 15
E 7
	(void) DataToTerminal(&c, 1);
    } else {
D 7
	*tfrontp++ = c;		/* optimize if possible. */
E 7
I 7
	TTYADD(c);
E 7
    }
}
#endif	/* ((!defined(NOT43)) || defined(PUTCHAR)) */
D 16

I 3
void
SetForExit()
{
    setconnmode();
    if (In3270) {
	Finish3270();
    }
    setcommandmode();
    fflush(stdout);
    fflush(stderr);
    if (In3270) {
	StopScreen(1);
    }
    setconnmode();
    setcommandmode();
}

void
Exit(returnCode)
int returnCode;
{
    SetForExit();
    exit(returnCode);
}

void
ExitString(string, returnCode)
char *string;
int returnCode;
{
    SetForExit();
    fwrite(string, 1, strlen(string), stderr);
    exit(returnCode);
}

I 13
#if defined(MSDOS)
E 13
void
ExitPerror(string, returnCode)
char *string;
int returnCode;
{
    SetForExit();
    perror(string);
    exit(returnCode);
}
I 13
#endif /* defined(MSDOS) */
E 16
E 13

D 23
void
E 23
I 23
    void
E 23
SetIn3270()
{
D 17
    if (Sent3270TerminalType && myopts[TELOPT_BINARY]
			    && hisopts[TELOPT_BINARY] && !donebinarytoggle) {
E 17
I 17
D 19
    if (Sent3270TerminalType && should_I(TELOPT_BINARY)
			    && should_he(TELOPT_BINARY) && !donebinarytoggle) {
E 19
I 19
    if (Sent3270TerminalType && my_want_state_is_will(TELOPT_BINARY)
		&& my_want_state_is_do(TELOPT_BINARY) && !donebinarytoggle) {
E 19
E 17
	if (!In3270) {
	    In3270 = 1;
	    Init3270();		/* Initialize 3270 functions */
	    /* initialize terminal key mapping */
	    InitTerminal();	/* Start terminal going */
D 19
	    setconnmode();
E 19
I 19
	    setconnmode(0);
E 19
	}
    } else {
	if (In3270) {
	    StopScreen(1);
	    In3270 = 0;
	    Stop3270();		/* Tell 3270 we aren't here anymore */
D 19
	    setconnmode();
E 19
I 19
	    setconnmode(0);
E 19
	}
    }
}

/*
 * tn3270_ttype()
 *
 *	Send a response to a terminal type negotiation.
 *
 *	Return '0' if no more responses to send; '1' if a response sent.
 */

D 23
int
E 23
I 23
    int
E 23
tn3270_ttype()
{
    /*
     * Try to send a 3270 type terminal name.  Decide which one based
     * on the format of our screen, and (in the future) color
     * capaiblities.
     */
    InitTerminal();		/* Sets MaxNumberColumns, MaxNumberLines */
    if ((MaxNumberLines >= 24) && (MaxNumberColumns >= 80)) {
	Sent3270TerminalType = 1;
	if ((MaxNumberLines >= 27) && (MaxNumberColumns >= 132)) {
	    MaxNumberLines = 27;
	    MaxNumberColumns = 132;
	    sb_terminal[SBTERMMODEL] = '5';
	} else if (MaxNumberLines >= 43) {
	    MaxNumberLines = 43;
	    MaxNumberColumns = 80;
	    sb_terminal[SBTERMMODEL] = '4';
	} else if (MaxNumberLines >= 32) {
	    MaxNumberLines = 32;
	    MaxNumberColumns = 80;
	    sb_terminal[SBTERMMODEL] = '3';
	} else {
	    MaxNumberLines = 24;
	    MaxNumberColumns = 80;
	    sb_terminal[SBTERMMODEL] = '2';
	}
	NumberLines = 24;		/* before we start out... */
	NumberColumns = 80;
	ScreenSize = NumberLines*NumberColumns;
	if ((MaxNumberLines*MaxNumberColumns) > MAXSCREENSIZE) {
	    ExitString("Programming error:  MAXSCREENSIZE too small.\n",
								1);
	    /*NOTREACHED*/
	}
D 19
	printsub(">", sb_terminal+2, sizeof sb_terminal-2);
E 19
I 19
	printsub('>', sb_terminal+2, sizeof sb_terminal-2);
E 19
	ring_supply_data(&netoring, sb_terminal, sizeof sb_terminal);
	return 1;
    } else {
	return 0;
    }
}
I 7

#if	defined(unix)
I 23
D 26
	void
E 26
I 26
	int
E 26
E 23
settranscom(argc, argv)
	int argc;
	char *argv[];
{
D 13
	int i, len = 0;
E 13
I 13
	int i;
E 13

	if (argc == 1 && transcom) {
	   transcom = 0;
	}
	if (argc == 1) {
D 26
	   return;
E 26
I 26
	   return 1;
E 26
D 13
	}
	for (i = 1; i < argc; ++i) {
	    len += 1 + strlen(argv[1]);
E 13
	}
	transcom = tline;
	(void) strcpy(transcom, argv[1]);
	for (i = 2; i < argc; ++i) {
	    (void) strcat(transcom, " ");
	    (void) strcat(transcom, argv[i]);
	}
I 26
	return 1;
E 26
}
#endif	/* defined(unix) */

E 7
E 3
#endif	/* defined(TN3270) */
E 1
