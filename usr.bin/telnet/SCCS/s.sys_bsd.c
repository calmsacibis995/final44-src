h44694
s 00010/00006/01184
d D 8.4 95/05/30 20:57:11 dab 39 38
c code cleanup, change b*() calls to mem*() calls
e
s 00058/00009/01132
d D 8.3 95/02/16 11:39:22 dab 38 37
c Recognize EIO as an end of file condition.
c Add code to deal with systems that have the terminal speeds
c defined as their actual values (it's simpler code).
e
s 00013/00013/01128
d D 8.2 93/12/15 11:35:59 dab 37 36
c Add support for new ENVIRON command.
c Latest Kerberos V code from MIT (includes new
c options '-f' and '-F' to control the forwarding
c of credentials.)  Various bugfixes to keep some
c C compilers happy.
e
s 00002/00002/01139
d D 8.1 93/06/06 16:33:22 bostic 36 35
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/01139
d D 5.5 93/05/20 10:49:30 dab 35 33
c Mostly, this changes all the "#if defined(ENCRYPTION)"
c lines to "#ifdef ENCRYPTION".  This will allow unifdef
c to be used to strip out the encryption code for
c foreign exports.  This also fixes up the usage statement.
e
s 00002/00000/01139
d R 5.5 93/05/20 10:37:22 dab 34 33
c Mostly this changes "#if defined(ENCRYPTION)" to
c "#ifdef ENCRYPTION".  This will allow unifdef to be
e
s 00006/00004/01133
d D 5.4 93/04/05 17:05:54 dab 33 32
c Fix gcc2 warnings.
c Fix the generation/parsing of the Environment option SEND suboption.
c Add code (#ifdef ENV_HACK) to help interoperation with Telnet servers
c that have the definitions for ENV_VAR and ENV_VALUE reversed.
e
s 00014/00002/01123
d D 5.3 92/12/18 14:06:51 dab 32 31
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Add Sun/SVR4 Streams support
c Allow for more ptys
c Environ suboption USERVAR support
c New Telnet Flowcontrol suboption support
c Server -k option to default to no kludge linemode
c Server -U option, allow only registered hosts to connect
e
s 00079/00071/01046
d D 5.2 91/03/01 01:31:56 dab 31 30
c Telnet AUTHENTICATION option
c Telnet ENCRYPT option (test version)
c Function prototypes
e
s 00177/00095/00940
d D 5.1 90/09/14 10:48:48 borman 30 29
c Latest batch of changes.  See the README file
c for a list of all the changes to telnet & telnetd.
e
s 00008/00000/01027
d D 1.28 90/07/28 11:04:13 trent 29 28
c disable VSTATUS (^T) on local tty
e
s 00108/00033/00919
d D 1.27 90/06/28 12:58:01 borman 28 27
c Lots of bugfixes, add the ENVIRON and X-DISPLAY-LOC
c options, "-l user" to the command line, diagnostic flags.
e
s 00001/00001/00951
d D 1.26 90/06/15 14:15:29 marc 27 26
c VFLUSHO -> VDISCARD
e
s 00001/00011/00951
d D 1.25 90/06/01 17:45:49 bostic 26 25
c new copyright notice
e
s 00055/00037/00907
d D 1.24 90/03/01 06:18:47 borman 25 24
c Several items:
c 1) Change from TC[GS]ETA* to TIOC[GS]ETA*
c 2) Use the cc_t typedef from terios.h
c 3) Add SLC_FORW support
c 4) Add TOS support
c 5) Fix the SLC_SUSP support.  The escape
c    character now uses one of the VEOL characters.
e
s 00035/00000/00909
d D 1.23 89/11/28 17:33:59 borman 24 22
c Add code for 4.2 based systems that don't do recv(MSG_OOB) properly.
e
s 00000/00000/00909
d R 1.23 89/11/28 17:31:18 borman 23 22
c Add code for 4.2 based systems that don't do MSG_OOB right.
e
s 00120/00060/00789
d D 1.22 89/11/14 10:20:18 borman 22 21
c Latest & greatest version of telnet
e
s 00021/00000/00828
d D 1.21 89/09/01 15:47:53 borman 21 20
c  RFC 1091 term type support, STATUS support, BINARY changes
e
s 00002/00002/00826
d D 1.20 89/08/28 09:57:38 borman 20 19
c Fix tags on #else #endif for ANSI C
e
s 00288/00124/00540
d D 1.19 89/08/21 14:58:45 borman 19 18
c Add support for LINEMODE option
e
s 00003/00000/00661
d D 1.18 89/05/30 22:14:51 minshall 18 17
c Add two toggles: termdata, cursesdata.
e
s 00050/00001/00611
d D 1.17 89/03/20 23:52:24 minshall 17 16
c Mods from DDP, et al, for LFLOW, TSPEED, and NAWS support.
e
s 00002/00004/00610
d D 1.16 88/11/29 22:09:32 minshall 16 15
c Try to fix SIGIO problem with Sun machines, h_errno with
c Sun machines, more debugging and options.
e
s 00003/00004/00611
d D 1.15 88/11/18 22:30:56 minshall 15 14
c Count SIGIO's (for debugging).  Separate out noasynch between
c tty and net.
e
s 00003/00007/00612
d D 1.14 88/08/28 17:46:50 minshall 14 13
c Some linting of tn3270.
e
s 00010/00005/00609
d D 1.13 88/06/29 20:15:27 bostic 13 12
c install approved copyright notice
e
s 00010/00006/00604
d D 1.12 88/06/27 22:19:34 minshall 12 11
c Fix up lint errors.
e
s 00000/00005/00610
d D 1.11 88/03/27 13:51:03 minshall 11 10
c Make it *compile* with -DTN3270.
e
s 00016/00000/00599
d D 1.10 88/03/08 10:30:59 bostic 10 9
c add Berkeley specific copyright
e
s 00016/00020/00583
d D 1.9 88/01/07 11:54:01 minshall 9 8
c Reduce extern's.
e
s 00001/00001/00602
d D 1.8 88/01/07 11:17:08 minshall 8 7
c Fix to not go into loop if tty disappears 
c (from Rick Adams <rick@seismo.css.gov>).
e
s 00003/00002/00600
d D 1.7 87/11/23 20:37:55 minshall 7 6
c Fixes from Dave Borman.
e
s 00002/00014/00600
d D 1.6 87/11/23 11:15:30 minshall 6 5
c Add in some changes from Dave Borman (borman@monet).
e
s 00051/00015/00563
d D 1.5 87/10/27 16:02:41 minshall 5 4
c Reformat somethings; get rid of "unix" comments and ifdefs;
c do some things which used to be done in tn (in command.c).
e
s 00267/00000/00311
d D 1.4 87/10/23 15:15:39 minshall 4 3
c Try to move system dependent stuff to system dependent files.
e
s 00003/00000/00308
d D 1.3 87/10/10 14:27:17 minshall 3 2
c This is the first version to get near rings.  It compiles,
c but doesn't work.
e
s 00007/00000/00301
d D 1.2 87/09/25 14:48:41 minshall 2 1
c Initialize term.*Char.
e
s 00301/00000/00000
d D 1.1 87/09/11 15:40:44 minshall 1 0
c date and time created 87/09/11 15:40:44 by minshall
e
u
U
t
T
I 1
/*
I 10
D 30
 * Copyright (c) 1988 Regents of the University of California.
E 30
I 30
D 36
 * Copyright (c) 1988, 1990 Regents of the University of California.
E 30
 * All rights reserved.
E 36
I 36
 * Copyright (c) 1988, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 36
 *
D 26
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
E 26
I 26
 * %sccs.include.redist.c%
E 26
E 13
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
E 10
 * The following routines try to encapsulate what is system dependent
 * (at least between 4.x and dos) which is used in telnet.c.
 */

D 22
#if	defined(unix)
E 22

I 16
#include <fcntl.h>
E 16
D 19
#include <sys/ioctl.h>
E 19
I 3
#include <sys/types.h>
E 3
#include <sys/time.h>
I 4
#include <sys/socket.h>
E 4
#include <signal.h>
I 4
#include <errno.h>
I 19
#include <arpa/telnet.h>
E 19
E 4
I 3

#include "ring.h"
E 3

I 6
#include "fdset.h"

E 6
#include "defines.h"
#include "externs.h"
#include "types.h"
D 6

I 4
#ifndef	FD_SETSIZE
/*
 * The following is defined just in case someone should want to run
 * this telnet on a 4.2 system.
 *
 */

#define	FD_SET(n, p)	((p)->fds_bits[0] |= (1<<(n)))
#define	FD_CLR(n, p)	((p)->fds_bits[0] &= ~(1<<(n)))
#define	FD_ISSET(n, p)	((p)->fds_bits[0] & (1<<(n)))
#define FD_ZERO(p)	((p)->fds_bits[0] = 0)

#endif
E 6

I 25
D 30
#if	defined(CRAY)
E 30
I 30
#if	defined(CRAY) || (defined(USE_TERMIO) && !defined(SYSV_TERMIO))
E 30
#define	SIG_FUNC_RET	void
#else
#define	SIG_FUNC_RET	int
#endif

I 33
#ifdef	SIGINFO
extern SIG_FUNC_RET ayt_status();
D 37
#endif	SIGINFO
E 37
I 37
#endif
E 37

E 33
E 25
E 4
int
I 4
	tout,			/* Output file descriptor */
	tin,			/* Input file descriptor */
D 15
	net,
E 4
	HaveInput;		/* There is input available to scan */
E 15
I 15
	net;
E 15

D 11
#if	defined(TN3270)
static char	tline[200];
char	*transcom = 0;	/* transparent mode command (default: none) */
#endif	/* defined(TN3270) */

E 11
D 19
static struct	tchars otc = { 0 }, ntc = { 0 };
static struct	ltchars oltc = { 0 }, nltc = { 0 };
static struct	sgttyb ottyb = { 0 }, nttyb = { 0 };
E 19
I 19
#ifndef	USE_TERMIO
struct	tchars otc = { 0 }, ntc = { 0 };
struct	ltchars oltc = { 0 }, nltc = { 0 };
struct	sgttyb ottyb = { 0 }, nttyb = { 0 };
I 21
int	olmode = 0;
I 30
# define cfgetispeed(ptr)	(ptr)->sg_ispeed
# define cfgetospeed(ptr)	(ptr)->sg_ospeed
# define old_tc ottyb
E 30
E 21
E 19

I 19
D 22
#define	ISPEED	ottyb.sg_ispeed
#define	OSPEED	ottyb.sg_ospeed
E 22
#else	/* USE_TERMIO */
struct	termio old_tc = { 0 };
extern struct termio new_tc;

I 25
D 30
#ifndef	TCGETA
D 28
#define	TCGETA	TIOCGETA
#define	TCSETA	TIOCSETA
#define	TCSETAW	TIOCSETAW
E 28
I 28
# ifdef TCGETS
#  define	TCGETA	TCGETS
#  define	TCSETA	TCSETS
#  define	TCSETAW	TCSETSW
# else
#  define	TCGETA	TIOCGETA
#  define	TCSETA	TIOCSETA
#  define	TCSETAW	TIOCSETAW
# endif
E 28
#endif	/* TCGETA */
E 30
I 30
# ifndef	TCSANOW
#  ifdef TCSETS
#   define	TCSANOW		TCSETS
#   define	TCSADRAIN	TCSETSW
D 31
#   define	tcgetattr(f, t) ioctl(f, TCGETS, t)
E 31
I 31
#   define	tcgetattr(f, t) ioctl(f, TCGETS, (char *)t)
E 31
#  else
#   ifdef TCSETA
#    define	TCSANOW		TCSETA
#    define	TCSADRAIN	TCSETAW
D 31
#    define	tcgetattr(f, t) ioctl(f, TCGETA, t)
E 31
I 31
#    define	tcgetattr(f, t) ioctl(f, TCGETA, (char *)t)
E 31
#   else
#    define	TCSANOW		TIOCSETA
#    define	TCSADRAIN	TIOCSETAW
D 31
#    define	tcgetattr(f, t) ioctl(f, TIOCGETA, t)
E 31
I 31
#    define	tcgetattr(f, t) ioctl(f, TIOCGETA, (char *)t)
E 31
#   endif
#  endif
D 31
#  define	tcsetattr(f, a, t) ioctl(f, a, t)
E 31
I 31
#  define	tcsetattr(f, a, t) ioctl(f, a, (char *)t)
E 31
#  define	cfgetospeed(ptr)	((ptr)->c_cflag&CBAUD)
#  ifdef CIBAUD
#   define	cfgetispeed(ptr)	(((ptr)->c_cflag&CIBAUD) >> IBSHIFT)
#  else
#   define	cfgetispeed(ptr)	cfgetospeed(ptr)
#  endif
# endif /* TCSANOW */
I 32
# ifdef	sysV88
# define TIOCFLUSH TC_PX_DRAIN
# endif
E 32
E 30
E 25
D 22
#define	ISPEED	(old_tc.c_cflag&CBAUD)
#define	OSPEED	ISPEED
E 22
#endif	/* USE_TERMIO */

E 19
I 4
static fd_set ibits, obits, xbits;
E 4

I 4

I 31
    void
E 31
init_sys()
{
    tout = fileno(stdout);
    tin = fileno(stdin);
    FD_ZERO(&ibits);
    FD_ZERO(&obits);
    FD_ZERO(&xbits);

    errno = 0;
}


I 31
    int
E 31
E 4
D 9
TerminalWrite(fd, buf, n)
int	fd;
E 9
I 9
TerminalWrite(buf, n)
E 9
D 31
char	*buf;
int	n;
E 31
I 31
    char *buf;
    int  n;
E 31
{
D 9
    return write(fd, buf, n);
E 9
I 9
    return write(tout, buf, n);
E 9
}

I 31
    int
E 31
D 9
TerminalRead(fd, buf, n)
int	fd;
E 9
I 9
TerminalRead(buf, n)
E 9
D 31
char	*buf;
int	n;
E 31
I 31
    char *buf;
    int  n;
E 31
{
D 9
    return read(fd, buf, n);
E 9
I 9
    return read(tin, buf, n);
E 9
}

/*
 *
 */

D 31
int
E 31
I 31
    int
E 31
D 5
TerminalAutoFlush()					/* unix */
E 5
I 5
TerminalAutoFlush()
E 5
{
#if	defined(LNOFLSH)
    int flush;

    ioctl(0, TIOCLGET, (char *)&flush);
    return !(flush&LNOFLSH);	/* if LNOFLSH, no autoflush */
#else	/* LNOFLSH */
    return 1;
#endif	/* LNOFLSH */
}

I 19
#ifdef	KLUDGELINEMODE
extern int kludgelinemode;
#endif
E 19
/*
 * TerminalSpecialChars()
 *
 * Look at an input character to see if it is a special character
 * and decide what to do.
 *
 * Output:
 *
 *	0	Don't add this character.
 *	1	Do add this character
 */

I 33
extern void xmitAO(), xmitEL(), xmitEC(), intp(), sendbrk();

E 33
D 31
int
E 31
I 31
    int
E 31
D 5
TerminalSpecialChars(c)			/* unix */
E 5
I 5
TerminalSpecialChars(c)
E 5
D 31
int	c;
E 31
I 31
    int	c;
E 31
{
D 5
    void doflush(), intp(), sendbrk();
E 5
I 5
D 33
    void xmitAO(), xmitEL(), xmitEC(), intp(), sendbrk();
E 5

E 33
D 19
    if (c == ntc.t_intrc) {
E 19
I 19
    if (c == termIntChar) {
E 19
	intp();
	return 0;
D 19
    } else if (c == ntc.t_quitc) {
	sendbrk();
E 19
I 19
    } else if (c == termQuitChar) {
#ifdef	KLUDGELINEMODE
	if (kludgelinemode)
	    sendbrk();
	else
#endif
	    sendabort();
E 19
	return 0;
D 19
    } else if (c == nltc.t_flushc) {
E 19
I 19
    } else if (c == termEofChar) {
	if (my_want_state_is_will(TELOPT_LINEMODE)) {
	    sendeof();
	    return 0;
	}
	return 1;
    } else if (c == termSuspChar) {
	sendsusp();
	return(0);
    } else if (c == termFlushChar) {
E 19
	xmitAO();		/* Transmit Abort Output */
	return 0;
    } else if (!MODE_LOCAL_CHARS(globalmode)) {
D 19
	if (c == nttyb.sg_kill) {
E 19
I 19
	if (c == termKillChar) {
E 19
	    xmitEL();
	    return 0;
D 19
	} else if (c == nttyb.sg_erase) {
E 19
I 19
	} else if (c == termEraseChar) {
E 19
	    xmitEC();		/* Transmit Erase Character */
	    return 0;
	}
    }
    return 1;
}


/*
 * Flush output to the terminal
 */
D 39
 
E 39
I 39

E 39
D 31
void
E 31
I 31
    void
E 31
D 5
TerminalFlushOutput()				/* unix */
E 5
I 5
TerminalFlushOutput()
E 5
{
I 19
D 22
#ifndef	USE_TERMIO
E 22
I 22
#ifdef	TIOCFLUSH
E 22
E 19
    (void) ioctl(fileno(stdout), TIOCFLUSH, (char *) 0);
I 19
#else
    (void) ioctl(fileno(stdout), TCFLSH, (char *) 0);
#endif
E 19
}

D 31
void
E 31
I 31
    void
E 31
D 5
TerminalSaveState()				/* unix */
E 5
I 5
TerminalSaveState()
E 5
{
I 19
#ifndef	USE_TERMIO
E 19
    ioctl(0, TIOCGETP, (char *)&ottyb);
    ioctl(0, TIOCGETC, (char *)&otc);
    ioctl(0, TIOCGLTC, (char *)&oltc);
I 21
    ioctl(0, TIOCLGET, (char *)&olmode);
E 21

    ntc = otc;
    nltc = oltc;
    nttyb = ottyb;
I 2

D 19
    termEofChar = ntc.t_eofc;
    termEraseChar = nttyb.sg_erase;
    termFlushChar = nltc.t_flushc;
    termIntChar = ntc.t_intrc;
    termKillChar = nttyb.sg_kill;
    termQuitChar = ntc.t_quitc;
E 19
I 19
#else	/* USE_TERMIO */
D 30
    ioctl(0, TCGETA, &old_tc);
E 30
I 30
    tcgetattr(0, &old_tc);
E 30

    new_tc = old_tc;

I 30
#ifndef	VDISCARD
E 30
D 28
    termFlushChar = 'O'&0x37;
    termWerasChar = 'W'&0x37;
    termRprntChar = 'R'&0x37;
    termLiteralNextChar = 'V'&0x37;
    termStartChar = 'Q'&0x37;
    termStopChar = 'S'&0x37;
E 28
I 28
    termFlushChar = CONTROL('O');
I 30
#endif
#ifndef	VWERASE
E 30
    termWerasChar = CONTROL('W');
I 30
#endif
#ifndef	VREPRINT
E 30
    termRprntChar = CONTROL('R');
I 30
#endif
#ifndef	VLNEXT
E 30
    termLiteralNextChar = CONTROL('V');
I 30
#endif
#ifndef	VSTART
E 30
    termStartChar = CONTROL('Q');
I 30
#endif
#ifndef	VSTOP
E 30
    termStopChar = CONTROL('S');
I 30
#endif
#ifndef	VSTATUS
    termAytChar = CONTROL('T');
#endif
E 30
E 28
#endif	/* USE_TERMIO */
E 19
E 2
}

I 22
D 25
unsigned
E 22
I 19
char *
E 25
I 25
D 31
cc_t *
E 31
I 31
    cc_t *
E 31
E 25
tcval(func)
D 31
register int func;
E 31
I 31
    register int func;
E 31
{
    switch(func) {
D 22
    case SLC_IP:	return(&termIntChar);
    case SLC_ABORT:	return(&termQuitChar);
    case SLC_EOF:	return(&termEofChar);
    case SLC_EC:	return(&termEraseChar);
    case SLC_EL:	return(&termKillChar);
    case SLC_XON:	return(&termStartChar);
    case SLC_XOFF:	return(&termStopChar);
#ifndef	CRAY
    case SLC_AO:	return(&termFlushChar);
    case SLC_SUSP:	return(&termSuspChar);
    case SLC_EW:	return(&termWerasChar);
    case SLC_RP:	return(&termRprntChar);
    case SLC_LNEXT:	return(&termLiteralNextChar);
D 20
#endif	CRAY
E 20
I 20
#endif	/* CRAY */
E 22
I 22
D 25
    case SLC_IP:	return((unsigned char *)&termIntChar);
    case SLC_ABORT:	return((unsigned char *)&termQuitChar);
    case SLC_EOF:	return((unsigned char *)&termEofChar);
    case SLC_EC:	return((unsigned char *)&termEraseChar);
    case SLC_EL:	return((unsigned char *)&termKillChar);
    case SLC_XON:	return((unsigned char *)&termStartChar);
    case SLC_XOFF:	return((unsigned char *)&termStopChar);
E 25
I 25
    case SLC_IP:	return(&termIntChar);
    case SLC_ABORT:	return(&termQuitChar);
    case SLC_EOF:	return(&termEofChar);
    case SLC_EC:	return(&termEraseChar);
    case SLC_EL:	return(&termKillChar);
    case SLC_XON:	return(&termStartChar);
    case SLC_XOFF:	return(&termStopChar);
I 28
    case SLC_FORW1:	return(&termForw1Char);
E 28
E 25
D 30
#ifndef	SYSV_TERMIO
E 30
I 30
#ifdef	USE_TERMIO
    case SLC_FORW2:	return(&termForw2Char);
# ifdef	VDISCARD
E 30
D 25
    case SLC_AO:	return((unsigned char *)&termFlushChar);
    case SLC_SUSP:	return((unsigned char *)&termSuspChar);
    case SLC_EW:	return((unsigned char *)&termWerasChar);
    case SLC_RP:	return((unsigned char *)&termRprntChar);
    case SLC_LNEXT:	return((unsigned char *)&termLiteralNextChar);
E 25
I 25
    case SLC_AO:	return(&termFlushChar);
I 30
# endif
# ifdef	VSUSP
E 30
    case SLC_SUSP:	return(&termSuspChar);
I 30
# endif
# ifdef	VWERASE
E 30
    case SLC_EW:	return(&termWerasChar);
I 30
# endif
# ifdef	VREPRINT
E 30
    case SLC_RP:	return(&termRprntChar);
I 30
# endif
# ifdef	VLNEXT
E 30
    case SLC_LNEXT:	return(&termLiteralNextChar);
E 25
D 30
#endif	/* SYSV_TERMIO */
I 28
#ifdef	USE_TERMIO
    case SLC_FORW2:	return(&termForw2Char);
E 30
I 30
# endif
# ifdef	VSTATUS
    case SLC_AYT:	return(&termAytChar);
# endif
E 30
#endif
E 28
E 22
E 20

    case SLC_SYNCH:
    case SLC_BRK:
D 30
    case SLC_AYT:
E 30
    case SLC_EOR:
D 28
    case SLC_FORW1:
    case SLC_FORW2:
E 28
    default:
D 22
	return((char *)0);
E 22
I 22
D 25
	return((unsigned char *)0);
E 25
I 25
	return((cc_t *)0);
E 25
E 22
    }
}

E 19
D 31
void
E 31
I 31
    void
E 31
I 19
TerminalDefaultChars()
{
#ifndef	USE_TERMIO
    ntc = otc;
    nltc = oltc;
    nttyb.sg_kill = ottyb.sg_kill;
    nttyb.sg_erase = ottyb.sg_erase;
#else	/* USE_TERMIO */
D 39
    memcpy(new_tc.c_cc, old_tc.c_cc, sizeof(old_tc.c_cc));
E 39
I 39
    memmove(new_tc.c_cc, old_tc.c_cc, sizeof(old_tc.c_cc));
E 39
I 22
D 27
# ifndef	VFLUSHO
E 27
I 27
D 28
# ifndef	VDISCARD
E 27
E 22
    termFlushChar = 'O'&0x37;
E 28
I 28
D 30
# ifndef	VFLUSHO
E 30
I 30
# ifndef	VDISCARD
E 30
    termFlushChar = CONTROL('O');
E 28
I 22
# endif
# ifndef	VWERASE
E 22
D 28
    termWerasChar = 'W'&0x37;
E 28
I 28
    termWerasChar = CONTROL('W');
E 28
I 22
# endif
# ifndef	VREPRINT
E 22
D 28
    termRprntChar = 'R'&0x37;
E 28
I 28
    termRprntChar = CONTROL('R');
E 28
I 22
# endif
# ifndef	VLNEXT
E 22
D 28
    termLiteralNextChar = 'V'&0x37;
E 28
I 28
    termLiteralNextChar = CONTROL('V');
E 28
I 22
# endif
# ifndef	VSTART
E 22
D 28
    termStartChar = 'Q'&0x37;
E 28
I 28
    termStartChar = CONTROL('Q');
E 28
I 22
# endif
# ifndef	VSTOP
E 22
D 28
    termStopChar = 'S'&0x37;
E 28
I 28
    termStopChar = CONTROL('S');
E 28
I 22
# endif
I 30
# ifndef	VSTATUS
    termAytChar = CONTROL('T');
# endif
E 30
E 22
#endif	/* USE_TERMIO */
}

I 28
#ifdef notdef
E 28
void
E 19
D 5
TerminalRestoreState()				/* unix */
E 5
I 5
TerminalRestoreState()
E 5
{
}
I 28
#endif
E 28

/*
 * TerminalNewMode - set up terminal to a specific mode.
I 19
 *	MODE_ECHO: do local terminal echo
 *	MODE_FLOW: do local flow control
 *	MODE_TRAPSIG: do local mapping to TELNET IAC sequences
 *	MODE_EDIT: do local line editing
 *
 *	Command mode:
 *		MODE_ECHO|MODE_EDIT|MODE_FLOW|MODE_TRAPSIG
 *		local echo
 *		local editing
 *		local xon/xoff
 *		local signal mapping
 *
 *	Linemode:
 *		local/no editing
 *	Both Linemode and Single Character mode:
 *		local/remote echo
 *		local/no xon/xoff
 *		local/no signal mapping
E 19
 */


D 31
void
E 31
I 31
    void
E 31
D 5
TerminalNewMode(fd_in, fd_out, f)			/* unix */
E 5
I 5
D 9
TerminalNewMode(fd_in, fd_out, f)
E 5
int	fd_in, fd_out;		/* File descriptor */
E 9
I 9
TerminalNewMode(f)
E 9
D 31
register int f;
E 31
I 31
    register int f;
E 31
{
    static int prevmode = 0;
D 19
    struct tchars *tc;
    struct tchars tc3;
    struct ltchars *ltc;
E 19
I 19
#ifndef	USE_TERMIO
    struct tchars tc;
    struct ltchars ltc;
E 19
    struct sgttyb sb;
I 21
    int lmode;
E 21
I 19
#else	/* USE_TERMIO */
    struct termio tmp_tc;
#endif	/* USE_TERMIO */
E 19
    int onoff;
    int old;
I 31
    cc_t esc;
E 31
D 19
    struct	tchars notc2;
    struct	ltchars noltc2;
    static struct	tchars notc =	{ -1, -1, -1, -1, -1, -1 };
    static struct	ltchars noltc =	{ -1, -1, -1, -1, -1, -1 };
E 19

D 19
    globalmode = f;
E 19
I 19
    globalmode = f&~MODE_FORCE;
E 19
    if (prevmode == f)
	return;
I 19

    /*
     * Write any outstanding data before switching modes
     * ttyflush() returns 0 only when there is no more data
     * left to write out, it returns -1 if it couldn't do
     * anything at all, otherwise it returns 1 + the number
     * of characters left to write.
I 30
#ifndef	USE_TERMIO
     * We would really like ask the kernel to wait for the output
     * to drain, like we can do with the TCSADRAIN, but we don't have
     * that option.  The only ioctl that waits for the output to
     * drain, TIOCSETP, also flushes the input queue, which is NOT
     * what we want (TIOCSETP is like TCSADFLUSH).
#endif
E 30
     */
    old = ttyflush(SYNCHing|flushout);
    if (old < 0 || old > 1) {
D 30
#ifndef	USE_TERMIO
	ioctl(tin, TIOCGETP, (char *)&sb);
#else	/* USE_TERMIO */
	ioctl(tin, TCGETA, (char *)&tmp_tc);
E 30
I 30
#ifdef	USE_TERMIO
D 31
	tcgetattr(tin, (char *)&tmp_tc);
E 31
I 31
	tcgetattr(tin, &tmp_tc);
E 31
E 30
#endif	/* USE_TERMIO */
	do {
	    /*
	     * Wait for data to drain, then flush again.
	     */
D 30
#ifndef	USE_TERMIO
	    ioctl(tin, TIOCSETP, (char *)&sb);
#else	/* USE_TERMIO */
	    ioctl(tin, TCSETAW, (char *)&tmp_tc);
E 30
I 30
#ifdef	USE_TERMIO
D 31
	    tcsetattr(tin, TCSADRAIN, (char *)&tmp_tc);
E 31
I 31
	    tcsetattr(tin, TCSADRAIN, &tmp_tc);
E 31
E 30
#endif	/* USE_TERMIO */
	    old = ttyflush(SYNCHing|flushout);
	} while (old < 0 || old > 1);
    }

E 19
    old = prevmode;
D 19
    prevmode = f;
E 19
I 19
    prevmode = f&~MODE_FORCE;
#ifndef	USE_TERMIO
E 19
    sb = nttyb;
I 19
    tc = ntc;
    ltc = nltc;
I 21
    lmode = olmode;
E 21
#else
    tmp_tc = new_tc;
#endif
E 19

D 19
    switch (f) {
E 19
I 19
    if (f&MODE_ECHO) {
#ifndef	USE_TERMIO
	sb.sg_flags |= ECHO;
#else
	tmp_tc.c_lflag |= ECHO;
	tmp_tc.c_oflag |= ONLCR;
I 22
D 31
# ifdef notdef
E 22
	tmp_tc.c_iflag |= ICRNL;
I 22
# endif
E 31
I 31
	if (crlf)
		tmp_tc.c_iflag |= ICRNL;
E 31
E 22
#endif
    } else {
#ifndef	USE_TERMIO
	sb.sg_flags &= ~ECHO;
#else
	tmp_tc.c_lflag &= ~ECHO;
	tmp_tc.c_oflag &= ~ONLCR;
I 22
# ifdef notdef
E 22
D 31
	tmp_tc.c_iflag &= ~ICRNL;
E 31
I 31
	if (crlf)
		tmp_tc.c_iflag &= ~ICRNL;
E 31
I 22
# endif
E 22
#endif
    }
E 19

D 19
    case 0:
	onoff = 0;
	tc = &otc;
	ltc = &oltc;
	break;
E 19
I 19
    if ((f&MODE_FLOW) == 0) {
#ifndef	USE_TERMIO
D 30
	tc.t_startc = -1;
	tc.t_stopc = -1;
E 30
I 30
	tc.t_startc = _POSIX_VDISABLE;
	tc.t_stopc = _POSIX_VDISABLE;
E 30
#else
D 32
	tmp_tc.c_iflag &= ~(IXANY|IXOFF|IXON);
E 32
I 32
	tmp_tc.c_iflag &= ~(IXOFF|IXON);	/* Leave the IXANY bit alone */
E 32
    } else {
D 32
	tmp_tc.c_iflag |= IXANY|IXOFF|IXON;
E 32
I 32
	if (restartany < 0) {
		tmp_tc.c_iflag |= IXOFF|IXON;	/* Leave the IXANY bit alone */
	} else if (restartany > 0) {
		tmp_tc.c_iflag |= IXOFF|IXON|IXANY;
	} else {
		tmp_tc.c_iflag |= IXOFF|IXON;
		tmp_tc.c_iflag &= ~IXANY;
	}
E 32
#endif
    }
E 19

D 19
    case 1:		/* remote character processing, remote echo */
    case 2:		/* remote character processing, local echo */
    case 6:		/* 3270 mode - like 1, but with xon/xoff local */
		    /* (might be nice to have "6" in telnet also...) */
	    sb.sg_flags |= CBREAK;
	    if ((f == 1) || (f == 6)) {
		sb.sg_flags &= ~(ECHO|CRMOD);
	    } else {
		sb.sg_flags |= ECHO|CRMOD;
	    }
	    sb.sg_erase = sb.sg_kill = -1;
D 17
	    if (f == 6) {
E 17
I 17
	    if (localflow || (f == 6)) {
E 17
		tc = &tc3;
		tc3 = notc;
		    /* get XON, XOFF characters */
		tc3.t_startc = otc.t_startc;
		tc3.t_stopc = otc.t_stopc;
	    } else {
		/*
		 * If user hasn't specified one way or the other,
		 * then default to not trapping signals.
		 */
		if (!donelclchars) {
		    localchars = 0;
		}
		if (localchars) {
		    notc2 = notc;
		    notc2.t_intrc = ntc.t_intrc;
		    notc2.t_quitc = ntc.t_quitc;
		    tc = &notc2;
		} else {
		    tc = &notc;
		}
	    }
	    ltc = &noltc;
	    onoff = 1;
	    break;
    case 3:		/* local character processing, remote echo */
    case 4:		/* local character processing, local echo */
    case 5:		/* local character processing, no echo */
	    sb.sg_flags &= ~CBREAK;
E 19
I 19
    if ((f&MODE_TRAPSIG) == 0) {
#ifndef	USE_TERMIO
D 30
	tc.t_intrc = -1;
	tc.t_quitc = -1;
	tc.t_eofc = -1;
	ltc.t_suspc = -1;
	ltc.t_dsuspc = -1;
E 30
I 30
	tc.t_intrc = _POSIX_VDISABLE;
	tc.t_quitc = _POSIX_VDISABLE;
	tc.t_eofc = _POSIX_VDISABLE;
	ltc.t_suspc = _POSIX_VDISABLE;
	ltc.t_dsuspc = _POSIX_VDISABLE;
E 30
#else
	tmp_tc.c_lflag &= ~ISIG;
#endif
	localchars = 0;
    } else {
#ifdef	USE_TERMIO
	tmp_tc.c_lflag |= ISIG;
#endif
	localchars = 1;
    }

    if (f&MODE_EDIT) {
#ifndef	USE_TERMIO
	sb.sg_flags &= ~CBREAK;
	sb.sg_flags |= CRMOD;
#else
	tmp_tc.c_lflag |= ICANON;
#endif
    } else {
#ifndef	USE_TERMIO
	sb.sg_flags |= CBREAK;
	if (f&MODE_ECHO)
E 19
	    sb.sg_flags |= CRMOD;
D 19
	    if (f == 4)
		sb.sg_flags |= ECHO;
	    else
		sb.sg_flags &= ~ECHO;
	    notc2 = ntc;
	    tc = &notc2;
	    noltc2 = oltc;
	    ltc = &noltc2;
	    /*
	     * If user hasn't specified one way or the other,
	     * then default to trapping signals.
	     */
	    if (!donelclchars) {
		localchars = 1;
	    }
	    if (localchars) {
		notc2.t_brkc = nltc.t_flushc;
		noltc2.t_flushc = -1;
	    } else {
		notc2.t_intrc = notc2.t_quitc = -1;
	    }
	    noltc2.t_suspc = escape;
	    noltc2.t_dsuspc = -1;
	    onoff = 1;
	    break;
E 19
I 19
	else
	    sb.sg_flags &= ~CRMOD;
#else
	tmp_tc.c_lflag &= ~ICANON;
	tmp_tc.c_iflag &= ~ICRNL;
	tmp_tc.c_cc[VMIN] = 1;
	tmp_tc.c_cc[VTIME] = 0;
#endif
    }
E 19

I 28
    if ((f&(MODE_EDIT|MODE_TRAPSIG)) == 0) {
#ifndef	USE_TERMIO
D 30
	ltc.t_lnextc = -1;
E 30
I 30
	ltc.t_lnextc = _POSIX_VDISABLE;
E 30
#else
# ifdef VLNEXT
D 30
	tmp_tc.c_cc[VLNEXT] = (cc_t)(-1);
E 30
I 30
	tmp_tc.c_cc[VLNEXT] = (cc_t)(_POSIX_VDISABLE);
E 30
# endif
#endif
    }

    if (f&MODE_SOFT_TAB) {
#ifndef USE_TERMIO
	sb.sg_flags |= XTABS;
#else
# ifdef	OXTABS
	tmp_tc.c_oflag |= OXTABS;
# endif
# ifdef	TABDLY
	tmp_tc.c_oflag &= ~TABDLY;
	tmp_tc.c_oflag |= TAB3;
# endif
#endif
    } else {
#ifndef USE_TERMIO
	sb.sg_flags &= ~XTABS;
#else
# ifdef	OXTABS
	tmp_tc.c_oflag &= ~OXTABS;
# endif
# ifdef	TABDLY
	tmp_tc.c_oflag &= ~TABDLY;
# endif
#endif
    }

    if (f&MODE_LIT_ECHO) {
#ifndef USE_TERMIO
D 31
	sb.sg_flags &= ~CTLECH;
E 31
I 31
	lmode &= ~LCTLECH;
E 31
#else
# ifdef	ECHOCTL
	tmp_tc.c_lflag &= ~ECHOCTL;
# endif
#endif
    } else {
#ifndef USE_TERMIO
D 31
	sb.sg_flags |= CTLECH;
E 31
I 31
	lmode |= LCTLECH;
E 31
#else
# ifdef	ECHOCTL
	tmp_tc.c_lflag |= ECHOCTL;
# endif
#endif
    }

E 28
D 19
    default:
	    return;
E 19
I 19
    if (f == -1) {
	onoff = 0;
    } else {
I 21
#ifndef	USE_TERMIO
D 22
	if (his_want_state_is_will(TELOPT_BINARY))
E 22
I 22
	if (f & MODE_OUTBIN)
E 22
		lmode |= LLITOUT;
	else
		lmode &= ~LLITOUT;
D 22
	if (my_want_state_is_will(TELOPT_BINARY))
E 22
I 22

	if (f & MODE_INBIN)
E 22
		lmode |= LPASS8;
	else
		lmode &= ~LPASS8;
#else
D 22
	if (my_want_state_is_will(TELOPT_BINARY))
		tmp.tc.c_lflag &= ~ISTRIP;
E 22
I 22
D 30
	if (f & MODE_OUTBIN)
		tmp_tc.c_lflag &= ~ISTRIP;
E 30
I 30
	if (f & MODE_INBIN)
		tmp_tc.c_iflag &= ~ISTRIP;
E 30
E 22
	else
D 22
		tmp.tc.c_lflag |= ISTRIP;
E 22
I 22
D 30
		tmp_tc.c_lflag |= ISTRIP;
	if (f & MODE_INBIN) {
E 30
I 30
		tmp_tc.c_iflag |= ISTRIP;
	if (f & MODE_OUTBIN) {
E 30
		tmp_tc.c_cflag &= ~(CSIZE|PARENB);
		tmp_tc.c_cflag |= CS8;
D 30
		tmp_tc.c_cflag &= ~OPOST;
E 30
I 30
		tmp_tc.c_oflag &= ~OPOST;
E 30
	} else {
D 30
		tmp_tc.c_cflag &= ~CSIZE;
		tmp_tc.c_cflag |= CS7|PARENB;
		tmp_tc.c_cflag |= OPOST;
E 30
I 30
		tmp_tc.c_cflag &= ~(CSIZE|PARENB);
		tmp_tc.c_cflag |= old_tc.c_cflag & (CSIZE|PARENB);
		tmp_tc.c_oflag |= OPOST;
E 30
	}
E 22
#endif
E 21
	onoff = 1;
E 19
    }
D 9
    ioctl(fd_in, TIOCSLTC, (char *)ltc);
    ioctl(fd_in, TIOCSETC, (char *)tc);
    ioctl(fd_in, TIOCSETP, (char *)&sb);
E 9
I 9
D 19
    ioctl(tin, TIOCSLTC, (char *)ltc);
    ioctl(tin, TIOCSETC, (char *)tc);
    ioctl(tin, TIOCSETP, (char *)&sb);
E 19
I 19

D 22
#ifndef	USE_TERMIO
E 22
    if (f != -1) {
I 22
#ifdef	SIGTSTP
E 22
D 25
	if (f&MODE_EDIT) {
	    void doescape();
E 25
I 25
D 28
	void susp();
E 28
I 28
D 30
	static void susp();
E 30
I 30
D 37
	static SIG_FUNC_RET susp();
E 37
I 37
	SIG_FUNC_RET susp();
E 37
#endif	/* SIGTSTP */
#ifdef	SIGINFO
D 37
	static SIG_FUNC_RET ayt();
#endif	SIGINFO
E 37
I 37
	SIG_FUNC_RET ayt();
#endif
E 37
E 30
E 28
E 25

I 22
D 25
# ifndef USE_TERMIO
E 22
	    ltc.t_suspc = escape;
I 22
# else
	    tmp_tc.c_cc[VSUSP] = escape;
# endif
E 22
	    (void) signal(SIGTSTP, (int (*)())doescape);
	} else if (old&MODE_EDIT) {
	    (void) signal(SIGTSTP, SIG_DFL);
	    sigsetmask(sigblock(0) & ~(1<<(SIGTSTP-1)));
	}
E 25
I 25
D 30
	(void) signal(SIGTSTP, (SIG_FUNC_RET (*)())susp);
E 30
I 30
#ifdef	SIGTSTP
	(void) signal(SIGTSTP, susp);
E 30
E 25
I 21
D 22
	ioctl(tin, TIOCLSET, (char *)&lmode);
E 21
	ioctl(tin, TIOCSLTC, (char *)&ltc);
	ioctl(tin, TIOCSETC, (char *)&tc);
	ioctl(tin, TIOCSETP, (char *)&sb);
E 22
I 22
#endif	/* SIGTSTP */
I 30
#ifdef	SIGINFO
	(void) signal(SIGINFO, ayt);
D 37
#endif	SIGINFO
E 37
I 37
#endif
E 37
#if	defined(USE_TERMIO) && defined(NOKERNINFO)
	tmp_tc.c_lflag |= NOKERNINFO;
#endif
E 30
I 28
	/*
	 * We don't want to process ^Y here.  It's just another
	 * character that we'll pass on to the back end.  It has
	 * to process it because it will be processed when the
	 * user attempts to read it, not when we send it.
	 */
#ifndef	USE_TERMIO
D 30
	ltc.t_dsuspc = -1;
E 30
I 30
	ltc.t_dsuspc = _POSIX_VDISABLE;
E 30
#else
# ifdef	VDSUSP
D 30
	tmp_tc.c_cc[VDSUSP] = (cc_t)(-1);
E 30
I 30
	tmp_tc.c_cc[VDSUSP] = (cc_t)(_POSIX_VDISABLE);
E 30
# endif
#endif
I 29
D 30
#ifdef USE_TERMIO
/*
 * Disable VSTATUS (^T)
 */
# ifdef VSTATUS
	tmp_tc.c_cc[VSTATUS] = (cc_t)(-1);
# endif
#endif
E 30
E 29
E 28
I 25
#ifdef	USE_TERMIO
D 28
#ifdef	VEOL2
E 28
	/*
	 * If the VEOL character is already set, then use VEOL2,
	 * otherwise use VEOL.
	 */
D 28
	if (tmp_tc.c_cc[VEOL] != (cc_t)(-1))
		tmp_tc.c_cc[VEOL2] = escape;
	else
#endif
E 28
I 28
D 30
	if (tmp_tc.c_cc[VEOL] == (cc_t)(-1))
E 28
		tmp_tc.c_cc[VEOL] = escape;
E 30
I 30
D 31
	if ((tmp_tc.c_cc[VEOL] != escape)
E 31
I 31
	esc = (rlogin != _POSIX_VDISABLE) ? rlogin : escape;
	if ((tmp_tc.c_cc[VEOL] != esc)
E 31
E 30
I 28
# ifdef	VEOL2
D 30
	else if (tmp_tc.c_cc[VEOL2] == (cc_t)(-1))
		tmp_tc.c_cc[VEOL2] = escape;
E 30
I 30
D 31
	    && (tmp_tc.c_cc[VEOL2] != escape)
E 31
I 31
	    && (tmp_tc.c_cc[VEOL2] != esc)
E 31
E 30
# endif
I 30
D 31
	   ) {
E 31
I 31
	    ) {
E 31
		if (tmp_tc.c_cc[VEOL] == (cc_t)(_POSIX_VDISABLE))
D 31
			tmp_tc.c_cc[VEOL] = escape;
E 31
I 31
		    tmp_tc.c_cc[VEOL] = esc;
E 31
# ifdef	VEOL2
		else if (tmp_tc.c_cc[VEOL2] == (cc_t)(_POSIX_VDISABLE))
D 31
			tmp_tc.c_cc[VEOL2] = escape;
E 31
I 31
		    tmp_tc.c_cc[VEOL2] = esc;
E 31
# endif
	}
E 30
E 28
#else
D 28
	tc.t_brkc = escape;
E 28
I 28
D 30
	if (tc.t_brkc == (cc_t)(-1))
E 30
I 30
	if (tc.t_brkc == (cc_t)(_POSIX_VDISABLE))
E 30
D 31
		tc.t_brkc = escape;
E 31
I 31
		tc.t_brkc = esc;
E 31
E 28
#endif
E 25
E 22
    } else {
I 30
#ifdef	SIGINFO
I 35
	SIG_FUNC_RET ayt_status();

E 35
D 33
	SIG_FUNC_RET ayt_status();

E 33
	(void) signal(SIGINFO, ayt_status);
D 37
#endif	SIGINFO
E 37
I 37
#endif
E 37
E 30
I 22
#ifdef	SIGTSTP
E 22
	(void) signal(SIGTSTP, SIG_DFL);
I 39
# ifndef SOLARIS
E 39
D 28
	sigsetmask(sigblock(0) & ~(1<<(SIGTSTP-1)));
E 28
I 28
	(void) sigsetmask(sigblock(0) & ~(1<<(SIGTSTP-1)));
I 39
# else	SOLARIS
	(void) sigrelse(SIGTSTP);
# endif	SOLARIS
E 39
E 28
I 21
D 22
	ioctl(tin, TIOCLSET, (char *)&lmode);
E 21
	ioctl(tin, TIOCSLTC, (char *)&oltc);
	ioctl(tin, TIOCSETC, (char *)&otc);
	ioctl(tin, TIOCSETP, (char *)&ottyb);
E 22
I 22
#endif	/* SIGTSTP */
#ifndef USE_TERMIO
	ltc = oltc;
	tc = otc;
	sb = ottyb;
I 28
	lmode = olmode;
#else
	tmp_tc = old_tc;
E 28
#endif
E 22
    }
I 22
#ifndef USE_TERMIO
    ioctl(tin, TIOCLSET, (char *)&lmode);
    ioctl(tin, TIOCSLTC, (char *)&ltc);
    ioctl(tin, TIOCSETC, (char *)&tc);
D 30
    ioctl(tin, TIOCSETP, (char *)&sb);
E 30
I 30
    ioctl(tin, TIOCSETN, (char *)&sb);
E 30
#else
D 30
    if (ioctl(tin, TCSETAW, &tmp_tc) < 0)
	ioctl(tin, TCSETA, &tmp_tc);
E 30
I 30
    if (tcsetattr(tin, TCSADRAIN, &tmp_tc) < 0)
	tcsetattr(tin, TCSANOW, &tmp_tc);
E 30
#endif

E 22
E 19
E 9
#if	(!defined(TN3270)) || ((!defined(NOT43)) || defined(PUTCHAR))
I 32
# if	!defined(sysV88)
E 32
D 9
    ioctl(fd_in, FIONBIO, (char *)&onoff);
    ioctl(fd_out, FIONBIO, (char *)&onoff);
E 9
I 9
    ioctl(tin, FIONBIO, (char *)&onoff);
    ioctl(tout, FIONBIO, (char *)&onoff);
I 32
# endif
E 32
E 9
#endif	/* (!defined(TN3270)) || ((!defined(NOT43)) || defined(PUTCHAR)) */
#if	defined(TN3270)
D 15
    if (noasynch == 0) {
E 15
I 15
    if (noasynchtty == 0) {
E 15
D 9
	ioctl(fd_in, FIOASYNC, (char *)&onoff);
E 9
I 9
	ioctl(tin, FIOASYNC, (char *)&onoff);
E 9
    }
#endif	/* defined(TN3270) */
I 31

E 31
D 19

    if (MODE_LINE(f)) {
	void doescape();

D 12
	signal(SIGTSTP, doescape);
E 12
I 12
	(void) signal(SIGTSTP, (int (*)())doescape);
E 12
    } else if (MODE_LINE(old)) {
D 12
	signal(SIGTSTP, SIG_DFL);
E 12
I 12
	(void) signal(SIGTSTP, SIG_DFL);
E 12
	sigsetmask(sigblock(0) & ~(1<<(SIGTSTP-1)));
    }
E 19
I 19
D 22
#else	/* USE_TERMIO */
    if (ioctl(tin, TCSETAW, &tmp_tc) < 0)
	ioctl(tin, TCSETA, &tmp_tc);
#endif	/* USE_TERMIO */
E 22
E 19
}

I 38
/*
 * Try to guess whether speeds are "encoded" (4.2BSD) or just numeric (4.4BSD).
 */
#if B4800 != 4800
#define	DECODE_BAUD
#endif

#ifdef	DECODE_BAUD
#ifndef	B7200
#define B7200   B4800
#endif

#ifndef	B14400
#define B14400  B9600
#endif

E 38
I 22
#ifndef	B19200
D 38
# define B19200 B9600
E 38
I 38
# define B19200 B14400
E 38
#endif

D 38
#ifndef	B38400
# define B38400 B19200
E 38
I 38
#ifndef	B28800
#define B28800  B19200
E 38
#endif

I 38
#ifndef	B38400
# define B38400 B28800
#endif

D 39
#ifndef B57600 
E 39
I 39
#ifndef B57600
E 39
#define B57600  B38400
#endif

D 39
#ifndef B76800 
E 39
I 39
#ifndef B76800
E 39
#define B76800  B57600
#endif

#ifndef B115200
#define B115200 B76800
#endif

#ifndef B230400
#define B230400 B115200
#endif


E 38
/*
 * This code assumes that the values B0, B50, B75...
 * are in ascending order.  They do not have to be
 * contiguous.
 */
struct termspeeds {
	long speed;
	long value;
} termspeeds[] = {
D 38
	{ 0,     B0 },     { 50,    B50 },   { 75,    B75 },
	{ 110,   B110 },   { 134,   B134 },  { 150,   B150 },
	{ 200,   B200 },   { 300,   B300 },  { 600,   B600 },
	{ 1200,  B1200 },  { 1800,  B1800 }, { 2400,  B2400 },
	{ 4800,  B4800 },  { 9600,  B9600 }, { 19200, B19200 },
	{ 38400, B38400 }, { -1,    B38400 }
E 38
I 38
	{ 0,      B0 },      { 50,    B50 },    { 75,     B75 },
	{ 110,    B110 },    { 134,   B134 },   { 150,    B150 },
	{ 200,    B200 },    { 300,   B300 },   { 600,    B600 },
	{ 1200,   B1200 },   { 1800,  B1800 },  { 2400,   B2400 },
	{ 4800,   B4800 },   { 7200,  B7200 },  { 9600,   B9600 },
	{ 14400,  B14400 },  { 19200, B19200 }, { 28800,  B28800 },
	{ 38400,  B38400 },  { 57600, B57600 }, { 115200, B115200 },
	{ 230400, B230400 }, { -1,    B230400 }
E 38
};
I 38
#endif	/* DECODE_BAUD */
E 38

D 30
#ifndef	USE_TERMIO
# define	ISPEED	ottyb.sg_ispeed
# define	OSPEED	ottyb.sg_ospeed
#else
D 28
# ifdef	SYSV_TERMIO
E 28
I 28
# ifdef	CBAUD
E 28
#  define	ISPEED	(old_tc.c_cflag&CBAUD)
#  define	OSPEED	ISPEED
# else
#  define	ISPEED	old_tc.c_ispeed
#  define OSPEED	old_tc.c_ospeed
# endif
#endif

E 30
E 22
I 17
D 31
void
E 31
I 31
    void
E 31
TerminalSpeeds(ispeed, ospeed)
D 31
long *ispeed;
long *ospeed;
E 31
I 31
    long *ispeed;
    long *ospeed;
E 31
{
I 38
#ifdef	DECODE_BAUD
E 38
D 22
    /*
     * The order here is important.  The index of each speed needs to
     * correspond with the sgtty structure value for that speed.
     *
     * Additionally, the search algorithm assumes the table is in
     * ascending sequence.
     */
    static int ttyspeeds[] = {
	    0, 50, 75, 110, 134, 150, 200, 300,
	    600, 1200, 1800, 2400, 4800, 9600, 19200, 38400 };
#define NUMSPEEDS sizeof ttyspeeds/sizeof ttyspeeds[0]
E 22
I 22
    register struct termspeeds *tp;
I 38
#endif	/* DECODE_BAUD */
E 38
I 30
    register long in, out;
E 30
E 22
E 17

I 30
D 31
    in = cfgetispeed(&old_tc);
E 31
    out = cfgetospeed(&old_tc);
I 31
    in = cfgetispeed(&old_tc);
    if (in == 0)
	in = out;
E 31

I 38
#ifdef	DECODE_BAUD
E 38
E 30
I 17
D 19
    if ((ottyb.sg_ospeed < 0) || (ottyb.sg_ospeed > NUMSPEEDS) ||
	(ottyb.sg_ispeed < 0) || (ottyb.sg_ispeed > NUMSPEEDS)) {
E 19
I 19
D 22
    if ((OSPEED < 0) || (OSPEED > NUMSPEEDS) ||
	(ISPEED < 0) || (ISPEED > NUMSPEEDS)) {
E 19
	ExitString("Invalid terminal speed.");
	/*NOTREACHED*/
    } else {
D 19
	*ispeed = ttyspeeds[ottyb.sg_ispeed];
	*ospeed = ttyspeeds[ottyb.sg_ospeed];
E 19
I 19
	*ispeed = ttyspeeds[ISPEED];
	*ospeed = ttyspeeds[OSPEED];
E 19
    }
E 22
I 22
    tp = termspeeds;
D 30
    while ((tp->speed != -1) && (tp->value < ISPEED))
E 30
I 30
    while ((tp->speed != -1) && (tp->value < in))
E 30
	tp++;
    *ispeed = tp->speed;

    tp = termspeeds;
D 30
    while ((tp->speed != -1) && (tp->value < OSPEED))
E 30
I 30
    while ((tp->speed != -1) && (tp->value < out))
E 30
	tp++;
    *ospeed = tp->speed;
I 38
#else	/* DECODE_BAUD */
	*ispeed = in;
	*ospeed = out;
#endif	/* DECODE_BAUD */
E 38
E 22
}

E 17
D 31
int
E 31
I 31
    int
E 31
I 17
TerminalWindowSize(rows, cols)
D 31
long *rows, *cols;
E 31
I 31
    long *rows, *cols;
E 31
{
I 19
#ifdef	TIOCGWINSZ
E 19
    struct winsize ws;

D 19
    if (ioctl(fileno(stdin), TIOCGWINSZ, (char *)&ws) < 0) {
	return 0;
E 19
I 19
    if (ioctl(fileno(stdin), TIOCGWINSZ, (char *)&ws) >= 0) {
	*rows = ws.ws_row;
	*cols = ws.ws_col;
	return 1;
E 19
    }
D 19
    *rows = ws.ws_row;
    *cols = ws.ws_col;
    return 1;
E 19
I 19
D 20
#endif	TIOCGWINSZ
E 20
I 20
#endif	/* TIOCGWINSZ */
E 20
    return 0;
E 19
}

D 31
int
E 31
I 31
    int
E 31
E 17
D 14
NetClose(net)
int	net;
E 14
I 14
NetClose(fd)
D 31
int	fd;
E 31
I 31
    int	fd;
E 31
E 14
{
D 14
    return close(net);
E 14
I 14
    return close(fd);
E 14
}


D 31
void
E 31
I 31
    void
E 31
D 5
NetNonblockingIO(fd, onoff)				/* unix */
E 5
I 5
NetNonblockingIO(fd, onoff)
E 5
D 31
int
	fd,
	onoff;
E 31
I 31
    int fd;
    int onoff;
E 31
{
    ioctl(fd, FIONBIO, (char *)&onoff);
}

I 12
#if	defined(TN3270)
E 12
D 31
void
E 31
I 31
    void
E 31
D 5
NetSigIO(fd, onoff)				/* unix */
E 5
I 5
NetSigIO(fd, onoff)
E 5
D 31
int
	fd,
	onoff;
E 31
I 31
    int fd;
    int onoff;
E 31
{
    ioctl(fd, FIOASYNC, (char *)&onoff);	/* hear about input */
}

D 31
void
E 31
I 31
    void
E 31
D 5
NetSetPgrp(fd)				/* unix */
E 5
I 5
NetSetPgrp(fd)
E 5
D 31
int fd;
E 31
I 31
    int fd;
E 31
{
    int myPid;

    myPid = getpid();
D 16
#if	defined(NOT43)
    myPid = -myPid;
#endif	/* defined(NOT43) */
    ioctl(fd, SIOCSPGRP, (char *)&myPid);	/* set my pid */
E 16
I 16
    fcntl(fd, F_SETOWN, myPid);
E 16
}
I 12
#endif	/*defined(TN3270)*/
E 12
I 5

/*
 * Various signal handling routines.
 */
E 5

I 5
D 9
void
E 9
I 9
D 30
static void
E 9
deadpeer()
E 30
I 30
D 31
/* ARGSUSED */
static SIG_FUNC_RET
E 31
I 31
    /* ARGSUSED */
D 37
    static SIG_FUNC_RET
E 37
I 37
    SIG_FUNC_RET
E 37
E 31
deadpeer(sig)
D 31
int sig;
E 31
I 31
    int sig;
E 31
E 30
{
	setcommandmode();
	longjmp(peerdied, -1);
}
E 5

I 4
D 9
void
E 9
I 9
D 30
static void
E 9
I 5
intr()
E 30
I 30
D 31
/* ARGSUSED */
static SIG_FUNC_RET
E 31
I 31
    /* ARGSUSED */
D 37
    static SIG_FUNC_RET
E 37
I 37
    SIG_FUNC_RET
E 37
E 31
intr(sig)
D 31
int sig;
E 31
I 31
    int sig;
E 31
E 30
{
    if (localchars) {
	intp();
	return;
    }
    setcommandmode();
    longjmp(toplevel, -1);
}

D 9
void
E 9
I 9
D 30
static void
E 9
intr2()
E 30
I 30
D 31
/* ARGSUSED */
static SIG_FUNC_RET
E 31
I 31
    /* ARGSUSED */
D 37
    static SIG_FUNC_RET
E 37
I 37
    SIG_FUNC_RET
E 37
E 31
intr2(sig)
D 31
int sig;
E 31
I 31
    int sig;
E 31
E 30
{
    if (localchars) {
D 19
	sendbrk();
E 19
I 19
#ifdef	KLUDGELINEMODE
	if (kludgelinemode)
	    sendbrk();
	else
#endif
	    sendabort();
E 19
	return;
    }
}

D 9
void
E 9
I 9
D 30
static void
I 25
susp()
E 30
I 30
#ifdef	SIGTSTP
D 31
/* ARGSUSED */
static SIG_FUNC_RET
E 31
I 31
    /* ARGSUSED */
D 37
    static SIG_FUNC_RET
E 37
I 37
    SIG_FUNC_RET
E 37
E 31
susp(sig)
D 31
int sig;
E 31
I 31
    int sig;
E 31
E 30
{
I 31
    if ((rlogin != _POSIX_VDISABLE) && rlogin_susp())
	return;
E 31
    if (localchars)
	sendsusp();
}
I 30
#endif
E 30

D 30
static void
E 25
I 17
sendwin()
E 30
I 30
#ifdef	SIGWINCH
D 31
/* ARGSUSED */
static SIG_FUNC_RET
E 31
I 31
    /* ARGSUSED */
D 37
    static SIG_FUNC_RET
E 37
I 37
    SIG_FUNC_RET
E 37
E 31
sendwin(sig)
D 31
int sig;
E 31
I 31
    int sig;
E 31
E 30
{
    if (connected) {
	sendnaws();
    }
}
I 30
#endif
E 30

I 30
#ifdef	SIGINFO
D 31
/* ARGSUSED */
static SIG_FUNC_RET
E 31
I 31
    /* ARGSUSED */
D 37
    static SIG_FUNC_RET
E 37
I 37
    SIG_FUNC_RET
E 37
E 31
ayt(sig)
D 31
int sig;
E 31
I 31
    int sig;
E 31
{
    if (connected)
	sendayt();
    else
	ayt_status();
}
#endif

E 30
D 28
static void
E 17
E 9
doescape()
{
D 19
    command(0);
E 19
I 19
    command(0, 0, 0);
E 19
}
E 28

D 31
void
E 31
I 31
    void
E 31
E 5
sys_telnet_init()
{
I 19
D 22
#ifndef	CRAY
E 22
I 22
D 25
#ifndef	VOID_SIGNAL
E 22
E 19
D 5
#if	defined(TN3270) && defined(unix)
E 5
I 5
D 14
#if	defined(TN3270)
E 5
    int myPid;
#endif	/* defined(TN3270) */

E 14
I 5
D 12
    signal(SIGINT, intr);
    signal(SIGQUIT, intr2);
    signal(SIGPIPE, deadpeer);
E 12
I 12
    (void) signal(SIGINT, (int (*)())intr);
    (void) signal(SIGQUIT, (int (*)())intr2);
    (void) signal(SIGPIPE, (int (*)())deadpeer);
I 19
#else
    (void) signal(SIGINT, (void (*)())intr);
    (void) signal(SIGQUIT, (void (*)())intr2);
    (void) signal(SIGPIPE, (void (*)())deadpeer);
#endif
E 25
I 25
D 30
    (void) signal(SIGINT, (SIG_FUNC_RET (*)())intr);
    (void) signal(SIGQUIT, (SIG_FUNC_RET (*)())intr2);
    (void) signal(SIGPIPE, (SIG_FUNC_RET (*)())deadpeer);
E 30
I 30
    (void) signal(SIGINT, intr);
    (void) signal(SIGQUIT, intr2);
    (void) signal(SIGPIPE, deadpeer);
E 30
E 25
#ifdef	SIGWINCH
E 19
I 17
D 25
    (void) signal(SIGWINCH, (int (*)())sendwin);
E 25
I 25
D 30
    (void) signal(SIGWINCH, (SIG_FUNC_RET (*)())sendwin);
E 30
I 30
    (void) signal(SIGWINCH, sendwin);
E 30
#endif
#ifdef	SIGTSTP
D 30
    (void) signal(SIGTSTP, (SIG_FUNC_RET (*)())susp);
E 30
I 30
    (void) signal(SIGTSTP, susp);
#endif
#ifdef	SIGINFO
    (void) signal(SIGINFO, ayt);
E 30
E 25
I 19
#endif
E 19
E 17
E 12

E 5
D 19
    setconnmode();
E 19
I 19
    setconnmode(0);
E 19

    NetNonblockingIO(net, 1);

#if	defined(TN3270)
D 15
    if (noasynch == 0) {			/* DBX can't handle! */
E 15
I 15
    if (noasynchnet == 0) {			/* DBX can't handle! */
E 15
	NetSigIO(net, 1);
	NetSetPgrp(net);
    }
#endif	/* defined(TN3270) */

#if	defined(SO_OOBINLINE)
D 12
    SetSockOpt(net, SOL_SOCKET, SO_OOBINLINE, 1);
E 12
I 12
    if (SetSockOpt(net, SOL_SOCKET, SO_OOBINLINE, 1) == -1) {
	perror("SetSockOpt");
    }
E 12
#endif	/* defined(SO_OOBINLINE) */
}

/*
 * Process rings -
 *
 *	This routine tries to fill up/empty our various rings.
 *
 *	The parameter specifies whether this is a poll operation,
 *	or a block-until-something-happens operation.
 *
 *	The return value is 1 if something happened, 0 if not.
 */

D 31
int
E 31
I 31
    int
E 31
process_rings(netin, netout, netex, ttyin, ttyout, poll)
D 31
int poll;		/* If 0, then block until something to do */
E 31
I 31
    int poll;		/* If 0, then block until something to do */
E 31
{
    register int c;
		/* One wants to be a bit careful about setting returnValue
		 * to one, since a one implies we did some useful work,
		 * and therefore probably won't be called to block next
		 * time (TN3270 mode only).
		 */
    int returnValue = 0;
    static struct timeval TimeValue = { 0 };

    if (netout) {
	FD_SET(net, &obits);
D 39
    } 
E 39
I 39
    }
E 39
    if (ttyout) {
	FD_SET(tout, &obits);
    }
#if	defined(TN3270)
    if (ttyin) {
	FD_SET(tin, &ibits);
    }
#else	/* defined(TN3270) */
    if (ttyin) {
	FD_SET(tin, &ibits);
    }
#endif	/* defined(TN3270) */
#if	defined(TN3270)
    if (netin) {
	FD_SET(net, &ibits);
    }
#   else /* !defined(TN3270) */
    if (netin) {
	FD_SET(net, &ibits);
    }
#   endif /* !defined(TN3270) */
    if (netex) {
	FD_SET(net, &xbits);
    }
    if ((c = select(16, &ibits, &obits, &xbits,
			(poll == 0)? (struct timeval *)0 : &TimeValue)) < 0) {
	if (c == -1) {
		    /*
		     * we can get EINTR if we are in line mode,
		     * and the user does an escape (TSTP), or
		     * some other signal generator.
		     */
	    if (errno == EINTR) {
		return 0;
	    }
#	    if defined(TN3270)
		    /*
		     * we can get EBADF if we were in transparent
		     * mode, and the transcom process died.
		    */
	    if (errno == EBADF) {
			/*
			 * zero the bits (even though kernel does it)
			 * to make sure we are selecting on the right
			 * ones.
			*/
		FD_ZERO(&ibits);
		FD_ZERO(&obits);
		FD_ZERO(&xbits);
		return 0;
	    }
#	    endif /* defined(TN3270) */
		    /* I don't like this, does it ever happen? */
	    printf("sleep(5) from telnet, after select\r\n");
D 5
#if	defined(unix)
E 5
	    sleep(5);
D 5
#endif	/* defined(unix) */
E 5
	}
	return 0;
    }

    /*
     * Any urgent data?
     */
    if (FD_ISSET(net, &xbits)) {
	FD_CLR(net, &xbits);
	SYNCHing = 1;
D 28
	ttyflush(1);	/* flush already enqueued data */
E 28
I 28
	(void) ttyflush(1);	/* flush already enqueued data */
E 28
    }

    /*
     * Something to read from the network...
     */
    if (FD_ISSET(net, &ibits)) {
	int canread;

	FD_CLR(net, &ibits);
	canread = ring_empty_consecutive(&netiring);
#if	!defined(SO_OOBINLINE)
	    /*
	     * In 4.2 (and some early 4.3) systems, the
	     * OOB indication and data handling in the kernel
	     * is such that if two separate TCP Urgent requests
	     * come in, one byte of TCP data will be overlaid.
	     * This is fatal for Telnet, but we try to live
	     * with it.
	     *
	     * In addition, in 4.2 (and...), a special protocol
	     * is needed to pick up the TCP Urgent data in
	     * the correct sequence.
	     *
	     * What we do is:  if we think we are in urgent
	     * mode, we look to see if we are "at the mark".
	     * If we are, we do an OOB receive.  If we run
	     * this twice, we will do the OOB receive twice,
	     * but the second will fail, since the second
	     * time we were "at the mark", but there wasn't
	     * any data there (the kernel doesn't reset
	     * "at the mark" until we do a normal read).
	     * Once we've read the OOB data, we go ahead
	     * and do normal reads.
	     *
	     * There is also another problem, which is that
	     * since the OOB byte we read doesn't put us
	     * out of OOB state, and since that byte is most
	     * likely the TELNET DM (data mark), we would
	     * stay in the TELNET SYNCH (SYNCHing) state.
	     * So, clocks to the rescue.  If we've "just"
	     * received a DM, then we test for the
	     * presence of OOB data when the receive OOB
	     * fails (and AFTER we did the normal mode read
	     * to clear "at the mark").
	     */
	if (SYNCHing) {
	    int atmark;
I 24
	    static int bogus_oob = 0, first = 1;
E 24

	    ioctl(net, SIOCATMARK, (char *)&atmark);
	    if (atmark) {
		c = recv(net, netiring.supply, canread, MSG_OOB);
		if ((c == -1) && (errno == EINVAL)) {
		    c = recv(net, netiring.supply, canread, 0);
		    if (clocks.didnetreceive < clocks.gotDM) {
			SYNCHing = stilloob(net);
		    }
I 24
		} else if (first && c > 0) {
		    /*
		     * Bogosity check.  Systems based on 4.2BSD
		     * do not return an error if you do a second
		     * recv(MSG_OOB).  So, we do one.  If it
		     * succeeds and returns exactly the same
		     * data, then assume that we are running
		     * on a broken system and set the bogus_oob
		     * flag.  (If the data was different, then
		     * we probably got some valid new data, so
		     * increment the count...)
		     */
		    int i;
		    i = recv(net, netiring.supply + c, canread - c, MSG_OOB);
		    if (i == c &&
D 39
			  bcmp(netiring.supply, netiring.supply + c, i) == 0) {
E 39
I 39
			 memcmp(netiring.supply, netiring.supply + c, i) == 0) {
E 39
			bogus_oob = 1;
			first = 0;
		    } else if (i < 0) {
			bogus_oob = 0;
			first = 0;
		    } else
			c += i;
		}
		if (bogus_oob && c > 0) {
		    int i;
		    /*
		     * Bogosity.  We have to do the read
		     * to clear the atmark to get out of
		     * an infinate loop.
		     */
		    i = read(net, netiring.supply + c, canread - c);
		    if (i > 0)
			c += i;
E 24
		}
	    } else {
		c = recv(net, netiring.supply, canread, 0);
	    }
	} else {
	    c = recv(net, netiring.supply, canread, 0);
	}
	settimer(didnetreceive);
#else	/* !defined(SO_OOBINLINE) */
D 37
	c = recv(net, netiring.supply, canread, 0);
E 37
I 37
	c = recv(net, (char *)netiring.supply, canread, 0);
E 37
#endif	/* !defined(SO_OOBINLINE) */
	if (c < 0 && errno == EWOULDBLOCK) {
	    c = 0;
	} else if (c <= 0) {
	    return -1;
	}
	if (netdata) {
	    Dump('<', netiring.supply, c);
	}
D 7
	ring_supplied(&netiring, c);
E 7
I 7
	if (c)
	    ring_supplied(&netiring, c);
E 7
	returnValue = 1;
    }

    /*
     * Something to read from the tty...
     */
    if (FD_ISSET(tin, &ibits)) {
	FD_CLR(tin, &ibits);
D 9
	c = TerminalRead(tin, ttyiring.supply,
			ring_empty_consecutive(&ttyiring));
E 9
I 9
	c = TerminalRead(ttyiring.supply, ring_empty_consecutive(&ttyiring));
I 38
	if (c < 0 && errno == EIO)
	    c = 0;
E 38
E 9
	if (c < 0 && errno == EWOULDBLOCK) {
	    c = 0;
	} else {
D 5
#if	defined(unix)
E 5
	    /* EOF detection for line mode!!!! */
D 8
	    if (c == 0 && MODE_LOCAL_CHARS(globalmode)) {
E 8
I 8
	    if ((c == 0) && MODE_LOCAL_CHARS(globalmode) && isatty(tin)) {
E 8
			/* must be an EOF... */
		*ttyiring.supply = termEofChar;
		c = 1;
	    }
D 5
#endif	/* defined(unix) */
E 5
	    if (c <= 0) {
		return -1;
	    }
I 18
	    if (termdata) {
		Dump('<', ttyiring.supply, c);
	    }
E 18
I 7
	    ring_supplied(&ttyiring, c);
E 7
	}
D 7
	ring_supplied(&ttyiring, c);
E 7
	returnValue = 1;		/* did something useful */
    }

    if (FD_ISSET(net, &obits)) {
	FD_CLR(net, &obits);
	returnValue |= netflush();
    }
    if (FD_ISSET(tout, &obits)) {
	FD_CLR(tout, &obits);
D 19
	returnValue |= ttyflush(SYNCHing|flushout);
E 19
I 19
	returnValue |= (ttyflush(SYNCHing|flushout) > 0);
E 19
    }

    return returnValue;
}
E 4
D 22
#endif	/* defined(unix) */
E 22
E 1
