h02393
s 00005/00004/00451
d D 8.3 95/05/30 20:57:08 dab 37 36
c code cleanup, change b*() calls to mem*() calls
e
s 00004/00002/00451
d D 8.2 93/12/15 11:35:56 dab 36 35
c Add support for new ENVIRON command.
c Latest Kerberos V code from MIT (includes new
c options '-f' and '-F' to control the forwarding
c of credentials.)  Various bugfixes to keep some
c C compilers happy.
e
s 00002/00002/00451
d D 8.1 93/06/06 16:32:47 bostic 35 34
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00452
d D 5.8 93/05/21 09:19:00 bostic 34 33
c settranscom has to return an int to be in the commands table
e
s 00010/00002/00443
d D 5.7 93/05/20 10:49:21 dab 33 31
c Mostly, this changes all the "#if defined(ENCRYPTION)"
c lines to "#ifdef ENCRYPTION".  This will allow unifdef
c to be used to strip out the encryption code for
c foreign exports.  This also fixes up the usage statement.
e
s 00010/00002/00443
d R 5.7 93/05/20 10:37:12 dab 32 31
c Mostly this changes "#if defined(ENCRYPTION)" to
c "#ifdef ENCRYPTION".  This will allow unifdef to be
e
s 00002/00002/00443
d D 5.6 93/05/11 10:02:10 bostic 31 30
c make tn3270 compile again
e
s 00006/00000/00439
d D 5.5 93/04/05 17:05:49 dab 30 29
c Fix gcc2 warnings.
c Fix the generation/parsing of the Environment option SEND suboption.
c Add code (#ifdef ENV_HACK) to help interoperation with Telnet servers
c that have the definitions for ENV_VAR and ENV_VALUE reversed.
e
s 00010/00002/00429
d D 5.4 92/12/18 14:06:42 dab 29 28
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Add Sun/SVR4 Streams support
c Allow for more ptys
c Environ suboption USERVAR support
c New Telnet Flowcontrol suboption support
c Server -k option to default to no kludge linemode
c Server -U option, allow only registered hosts to connect
e
s 00001/00000/00430
d D 5.3 91/03/22 13:09:18 dab 28 27
c Upgrade to the latest & greatest authentication/encryption
e
s 00081/00036/00349
d D 5.2 91/03/01 01:32:16 dab 27 26
c Telnet AUTHENTICATION option
c Telnet ENCRYPT option (test version)
c Function prototypes
e
s 00026/00006/00359
d D 5.1 90/09/14 10:41:59 borman 26 25
c Bump the sccs id to 5.1
e
s 00030/00017/00335
d D 1.25 90/06/28 12:57:23 borman 25 24
c Lots of bugfixes, add the ENVIRON and X-DISPLAY-LOC
c options, "-l user" to the command line, diagnostic flags.
e
s 00003/00000/00349
d D 1.24 90/06/20 16:30:30 kfall 24 23
c add kerberized flag
e
s 00002/00002/00347
d D 1.23 90/06/15 14:15:26 marc 23 22
c VFLUSHO -> VDISCARD
e
s 00001/00011/00348
d D 1.22 90/06/01 17:45:04 bostic 22 21
c new copyright notice
e
s 00036/00014/00323
d D 1.21 90/03/01 06:18:37 borman 21 20
c Several items:
c 1) Change from TC[GS]ETA* to TIOC[GS]ETA*
c 2) Use the cc_t typedef from terios.h
c 3) Add SLC_FORW support
c 4) Add TOS support
c 5) Fix the SLC_SUSP support.  The escape
c    character now uses one of the VEOL characters.
e
s 00105/00079/00232
d D 1.20 89/11/14 10:20:08 borman 20 19
c Latest & greatest version of telnet
e
s 00001/00000/00310
d D 1.19 89/09/02 15:47:58 minshall 19 18
c Add in "to apitrace"
e
s 00001/00000/00309
d D 1.18 89/09/01 15:47:38 borman 18 17
c  RFC 1091 term type support, STATUS support, BINARY changes
e
s 00156/00016/00153
d D 1.17 89/08/21 14:58:39 borman 17 16
c Add support for LINEMODE option
e
s 00006/00000/00163
d D 1.16 89/05/30 22:14:47 minshall 16 15
c Add two toggles: termdata, cursesdata.
e
s 00024/00002/00139
d D 1.15 89/03/21 22:30:42 minshall 15 14
c Keep track of each side's idea of what the state of each option is.
e
s 00002/00000/00139
d D 1.14 89/03/20 23:52:15 minshall 14 13
c Mods from DDP, et al, for LFLOW, TSPEED, and NAWS support.
e
s 00002/00001/00137
d D 1.13 88/11/29 22:09:30 minshall 13 12
c Try to fix SIGIO problem with Sun machines, h_errno with
c Sun machines, more debugging and options.
e
s 00003/00001/00135
d D 1.12 88/11/18 22:30:45 minshall 12 11
c Count SIGIO's (for debugging).  Separate out noasynch between
c tty and net.
e
s 00010/00005/00126
d D 1.11 88/06/29 20:15:16 bostic 11 10
c install approved copyright notice
e
s 00017/00001/00114
d D 1.10 88/06/27 22:19:20 minshall 10 9
c Fix up lint errors.
e
s 00007/00000/00108
d D 1.9 88/05/15 21:17:37 minshall 9 8
c For NOT43 systems, get correct definition for dosynch().
e
s 00065/00038/00043
d D 1.8 88/03/27 13:49:03 minshall 8 7
c Make it *compile* with -DTN3270.
e
s 00014/00000/00067
d D 1.7 88/03/08 10:30:46 bostic 7 6
c add Berkeley specific copyright
e
s 00000/00006/00067
d D 1.6 88/01/07 11:54:00 minshall 6 5
c Reduce extern's.
e
s 00000/00001/00073
d D 1.5 87/10/27 15:59:12 minshall 5 4
c Remove an unused extern.
e
s 00001/00000/00073
d D 1.4 87/10/23 15:15:35 minshall 4 3
c Try to move system dependent stuff to system dependent files.
e
s 00009/00007/00064
d D 1.3 87/10/10 14:27:11 minshall 3 2
c This is the first version to get near rings.  It compiles,
c but doesn't work.
e
s 00000/00002/00071
d D 1.2 87/09/25 16:06:40 minshall 2 1
c Cut down on number of extern's.
e
s 00073/00000/00000
d D 1.1 87/09/11 15:40:31 minshall 1 0
c date and time created 87/09/11 15:40:31 by minshall
e
u
U
t
T
I 7
/*
D 26
 * Copyright (c) 1988 Regents of the University of California.
E 26
I 26
D 35
 * Copyright (c) 1988, 1990 Regents of the University of California.
E 26
 * All rights reserved.
E 35
I 35
 * Copyright (c) 1988, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 35
 *
D 22
 * Redistribution and use in source and binary forms are permitted
D 11
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 11
I 11
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
E 22
I 22
 * %sccs.include.redist.c%
E 22
E 11
 *
 *	%W% (Berkeley) %G%
 */

I 17
D 20
#ifdef	CRAY
#define	USE_TERMIO
E 20
I 20
#ifndef	BSD
# define BSD 43
E 20
#endif

I 29
/*
 * ucb stdio.h defines BSD as something wierd
 */
#if defined(sun) && defined(__svr4__)
#define BSD 43
#endif

E 29
I 20
D 36
#if (BSD > 43 || defined(SYSV_TERMIO)) && !defined(USE_TERMIO)
# define USE_TERMIO
E 36
I 36
#ifndef	USE_TERMIO
# if BSD > 43 || defined(SYSV_TERMIO)
#  define USE_TERMIO
# endif
E 36
#endif

E 20
E 17
E 7
I 1
#include <stdio.h>
#include <setjmp.h>
I 33
#if defined(CRAY) && !defined(NO_BSD_SETJMP)
#include <bsdsetjmp.h>
#endif
E 33
I 25
#ifndef	FILIO_H
E 25
I 17
#include <sys/ioctl.h>
I 25
#else
#include <sys/filio.h>
#endif
I 33
#ifdef CRAY
# include <errno.h>
#endif /* CRAY */
E 33
E 25
#ifdef	USE_TERMIO
D 20
#ifndef	VINTR
#include <sys/termio.h>
E 20
I 20
# ifndef	VINTR
#  ifdef SYSV_TERMIO
#   include <sys/termio.h>
#  else
#   include <sys/termios.h>
#   define termio termios
#  endif
# endif
I 21
D 25
#else
E 25
I 25
#endif
#if defined(NO_CC_T) || !defined(USE_TERMIO)
# if !defined(USE_TERMIO)
E 25
typedef char cc_t;
I 25
# else
typedef unsigned char cc_t;
# endif
E 25
E 21
E 20
#endif
D 20
#endif
E 20
E 17

I 27
#ifndef	NO_STRING_H
#include <string.h>
D 37
#endif
E 37
I 37
#else
E 37
#include <strings.h>
I 37
#endif
E 37

E 27
I 26
#ifndef	_POSIX_VDISABLE
# ifdef sun
#  include <sys/param.h>	/* pick up VDISABLE definition, mayby */
# endif
# ifdef VDISABLE
#  define _POSIX_VDISABLE VDISABLE
# else
D 27
#  define _POSIX_VDISABLE ((unsigned char)'\377')
E 27
I 27
#  define _POSIX_VDISABLE ((cc_t)'\377')
E 27
# endif
#endif

E 26
D 17
#define	SUBBUFSIZE	100
E 17
I 17
#define	SUBBUFSIZE	256
E 17

I 33
#ifndef CRAY
E 33
extern int errno;		/* outside this world */
I 33
#endif /* !CRAY */
E 33

I 8
D 27
extern char
    *strcat(),
    *strcpy();			/* outside this world */
E 27
I 27
#if	!defined(P)
# ifdef	__STDC__
#  define	P(x)	x
# else
#  define	P(x)	()
# endif
#endif
E 27

E 8
extern int
I 27
    autologin,		/* Autologin enabled */
I 28
    skiprc,		/* Don't process the ~/.telnetrc file */
E 28
    eight,		/* use eight bit mode (binary in and/or out */
E 27
D 2
	SYNCHing,		/* we are in TELNET SYNCH mode */
E 2
D 8
	flushout,		/* flush output */
	connected,		/* Are we connected to the other side? */
	globalmode,		/* Mode tty should be in */
	In3270,			/* Are we in 3270 mode? */
	telnetport,		/* Are we connected to the telnet port? */
	localchars,		/* we recognize interrupt/quit */
	donelclchars,		/* the user has set "localchars" */
	showoptions,
D 2
	flushline,
E 2
	net,
D 6
	tin,
	tout,
E 6
	crlf,		/* Should '\r' be mapped to <CR><LF> (or <CR><NUL>)? */
	autoflush,		/* flush output when interrupting? */
	autosynch,		/* send interrupt characters with SYNCH? */
I 4
	SYNCHing,		/* Is the stream in telnet SYNCH mode? */
E 4
	donebinarytoggle,	/* the user has put us in binary */
	dontlecho,		/* do we suppress local echoing right now? */
	crmod,
	netdata,		/* Print out network data flow */
	debug;			/* Debug level */
E 8
I 8
    flushout,		/* flush output */
    connected,		/* Are we connected to the other side? */
    globalmode,		/* Mode tty should be in */
D 37
    In3270,			/* Are we in 3270 mode? */
E 37
I 37
    In3270,		/* Are we in 3270 mode? */
E 37
    telnetport,		/* Are we connected to the telnet port? */
I 14
    localflow,		/* Flow control handled locally */
I 29
    restartany,		/* If flow control, restart output on any character */
E 29
E 14
    localchars,		/* we recognize interrupt/quit */
D 37
    donelclchars,		/* the user has set "localchars" */
E 37
I 37
    donelclchars,	/* the user has set "localchars" */
E 37
    showoptions,
D 13
    net,
E 13
I 13
    net,		/* Network file descriptor */
    tin,		/* Terminal input file descriptor */
E 13
    tout,		/* Terminal output file descriptor */
    crlf,		/* Should '\r' be mapped to <CR><LF> (or <CR><NUL>)? */
    autoflush,		/* flush output when interrupting? */
    autosynch,		/* send interrupt characters with SYNCH? */
    SYNCHing,		/* Is the stream in telnet SYNCH mode? */
    donebinarytoggle,	/* the user has put us in binary */
    dontlecho,		/* do we suppress local echoing right now? */
    crmod,
    netdata,		/* Print out network data flow */
I 24
D 27
#ifdef	KERBEROS
    kerberized,		/* Try to use Kerberos */
#endif
E 27
E 24
I 17
    prettydump,		/* Print "netdata" output in user readable format */
E 17
I 16
#if	defined(unix)
#if	defined(TN3270)
    cursesdata,		/* Print out curses data flow */
I 19
    apitrace,		/* Trace API transactions */
E 19
#endif	/* defined(TN3270) */
    termdata,		/* Print out terminal data flow */
#endif	/* defined(unix) */
E 16
D 37
    debug;			/* Debug level */
E 37
I 37
    debug;		/* Debug level */
E 37
E 8

I 20
D 21
extern unsigned char
E 21
I 21
D 25
extern cc_t
E 21
    echoc,		/* Toggle local echoing */
D 21
    escape,		/* Escape to command mode */
E 21
I 21
    escape;		/* Escape to command mode */
E 25
I 25
extern cc_t escape;	/* Escape to command mode */
I 27
extern cc_t rlogin;	/* Rlogin mode escape character */
E 27
#ifdef	KLUDGELINEMODE
extern cc_t echoc;	/* Toggle local echoing */
#endif
E 25

D 25
extern unsigned char
E 25
I 25
extern char
E 25
E 21
    *prompt;		/* Prompt for command. */

E 20
extern char
D 8
	echoc,			/* Toggle local echoing */
	escape,			/* Escape to command mode */
	doopt[],
	dont[],
	will[],
	wont[],
	hisopts[],
	myopts[],
D 6
	subbuffer[SUBBUFSIZE],
E 6
	*hostname,		/* Who are we connected to? */
D 3
	*prompt,		/* Prompt for command. */
	*nfrontp,
	*nbackp,
	netobuf[2*BUFSIZ],
	ttyobuf[2*BUFSIZ],
	*tfrontp,
	*tbackp;
E 3
I 3
	*prompt;		/* Prompt for command. */
E 8
I 8
D 20
    echoc,			/* Toggle local echoing */
    escape,			/* Escape to command mode */
E 20
    doopt[],
    dont[],
    will[],
    wont[],
D 15
    hisopts[],
    myopts[],
E 15
I 15
    options[],		/* All the little options */
E 15
D 20
    *hostname,		/* Who are we connected to? */
    *prompt;		/* Prompt for command. */
E 20
I 20
    *hostname;		/* Who are we connected to? */
I 27
D 29
#if	defined(ENCRYPT)
E 29
I 29
D 33
#if	defined(ENCRYPTION)
E 33
I 33
#ifdef	ENCRYPTION
E 33
E 29
extern void (*encrypt_output) P((unsigned char *, int));
extern int (*decrypt_input) P((int));
D 33
#endif
E 33
I 33
#endif	/* ENCRYPTION */
E 33
E 27
E 20
I 15

/*
 * We keep track of each side of the option negotiation.
 */

D 17
#define	OPT_HE_SAID_DO		0x01
#define	OPT_HE_SAID_WILL	0x02
#define	OPT_I_SAID_DO		0x04
#define	OPT_I_SAID_WILL		0x08
E 17
I 17
#define	MY_STATE_WILL		0x01
#define	MY_WANT_STATE_WILL	0x02
#define	MY_STATE_DO		0x04
#define	MY_WANT_STATE_DO	0x08
E 17

/*
D 17
 * Macros to check out what has been said.
E 17
I 17
 * Macros to check the current state of things
E 17
 */

D 17
#define	did_he_say_do(opt)	(options[opt]&OPT_HE_SAID_DO)
#define	did_he_say_will(opt)	(options[opt]&OPT_HE_SAID_WILL)
#define	did_I_say_do(opt)	(options[opt]&OPT_I_SAID_DO)
#define	did_I_say_will(opt)	(options[opt]&OPT_I_SAID_WILL)
E 17
I 17
#define	my_state_is_do(opt)		(options[opt]&MY_STATE_DO)
#define	my_state_is_will(opt)		(options[opt]&MY_STATE_WILL)
#define my_want_state_is_do(opt)	(options[opt]&MY_WANT_STATE_DO)
#define my_want_state_is_will(opt)	(options[opt]&MY_WANT_STATE_WILL)
E 17

D 17
#define	should_he(opt) \
	    (did_he_say_will(opt) && did_I_say_do(opt))
#define	should_I(opt) \
	    (did_I_say_will(opt) && did_he_say_do(opt))
E 17
I 17
#define	my_state_is_dont(opt)		(!my_state_is_do(opt))
#define	my_state_is_wont(opt)		(!my_state_is_will(opt))
#define my_want_state_is_dont(opt)	(!my_want_state_is_do(opt))
#define my_want_state_is_wont(opt)	(!my_want_state_is_will(opt))
E 17
E 15
E 8
E 3

I 17
#define	set_my_state_do(opt)		{options[opt] |= MY_STATE_DO;}
#define	set_my_state_will(opt)		{options[opt] |= MY_STATE_WILL;}
#define	set_my_want_state_do(opt)	{options[opt] |= MY_WANT_STATE_DO;}
#define	set_my_want_state_will(opt)	{options[opt] |= MY_WANT_STATE_WILL;}

#define	set_my_state_dont(opt)		{options[opt] &= ~MY_STATE_DO;}
#define	set_my_state_wont(opt)		{options[opt] &= ~MY_STATE_WILL;}
#define	set_my_want_state_dont(opt)	{options[opt] &= ~MY_WANT_STATE_DO;}
#define	set_my_want_state_wont(opt)	{options[opt] &= ~MY_WANT_STATE_WILL;}

/*
 * Make everything symetrical
 */

#define	HIS_STATE_WILL			MY_STATE_DO
#define	HIS_WANT_STATE_WILL		MY_WANT_STATE_DO
#define HIS_STATE_DO			MY_STATE_WILL
#define HIS_WANT_STATE_DO		MY_WANT_STATE_WILL

#define	his_state_is_do			my_state_is_will
#define	his_state_is_will		my_state_is_do
#define his_want_state_is_do		my_want_state_is_will
#define his_want_state_is_will		my_want_state_is_do

#define	his_state_is_dont		my_state_is_wont
#define	his_state_is_wont		my_state_is_dont
#define his_want_state_is_dont		my_want_state_is_wont
#define his_want_state_is_wont		my_want_state_is_dont

#define	set_his_state_do		set_my_state_will
#define	set_his_state_will		set_my_state_do
#define	set_his_want_state_do		set_my_want_state_will
#define	set_his_want_state_will		set_my_want_state_do

#define	set_his_state_dont		set_my_state_wont
#define	set_his_state_wont		set_my_state_dont
#define	set_his_want_state_dont		set_my_want_state_wont
#define	set_his_want_state_wont		set_my_want_state_dont


E 17
extern FILE
D 8
	*NetTrace;		/* Where debugging output goes */
E 8
I 8
    *NetTrace;		/* Where debugging output goes */
I 17
D 20
extern char
E 20
I 20
extern unsigned char
E 20
    NetTraceFile[];	/* Name of file where debugging output goes */
extern void
D 27
    SetNetTrace();	/* Function to change where debugging goes */
E 27
I 27
    SetNetTrace P((char *));	/* Function to change where debugging goes */
E 27
E 17
E 8

extern jmp_buf
D 8
	peerdied,
	toplevel;		/* For error conditions. */
E 8
I 8
    peerdied,
    toplevel;		/* For error conditions. */
E 8

extern void
I 10
D 27
    command(),
E 10
I 9
#if	!defined(NOT43)
E 9
D 6
	intr(),
	intr2(),
	deadpeer(),
E 6
D 8
	dosynch(),
D 5
	doflush(),
E 5
	setconnmode(),
	setcommandmode();
E 8
I 8
    dosynch(),
I 9
#endif	/* !defined(NOT43) */
I 18
    get_status(),
E 18
I 10
    Dump(),
    init_3270(),
    printoption(),
    printsub(),
I 14
    sendnaws(),
E 14
E 10
E 9
    setconnmode(),
D 10
    setcommandmode();
E 10
I 10
    setcommandmode(),
    setneturg(),
    sys_telnet_init(),
    telnet(),
    TerminalFlushOutput(),
    TerminalNewMode(),
    TerminalRestoreState(),
    TerminalSaveState(),
    tninit(),
    upcase(),
    willoption(),
    wontoption();
E 27
I 27
    command P((int, char *, int)),
    Dump P((int, unsigned char *, int)),
    init_3270 P((void)),
    printoption P((char *, int, int)),
    printsub P((int, unsigned char *, int)),
    sendnaws P((void)),
    setconnmode P((int)),
    setcommandmode P((void)),
    setneturg P((void)),
    sys_telnet_init P((void)),
    telnet P((char *)),
    tel_enter_binary P((int)),
    TerminalFlushOutput P((void)),
    TerminalNewMode P((int)),
    TerminalRestoreState P((void)),
    TerminalSaveState P((void)),
    tninit P((void)),
    upcase P((char *)),
    willoption P((int)),
    wontoption P((int));
E 27
E 10
I 9

D 27
#if	defined(NOT43)
E 27
I 27
extern void
I 30
    send_do P((int, int)),
    send_dont P((int, int)),
    send_will P((int, int)),
    send_wont P((int, int));

extern void
E 30
    lm_will P((unsigned char *, int)),
    lm_wont P((unsigned char *, int)),
    lm_do P((unsigned char *, int)),
    lm_dont P((unsigned char *, int)),
    lm_mode P((unsigned char *, int, int));

extern void
    slc_init P((void)),
    slcstate P((void)),
    slc_mode_export P((void)),
    slc_mode_import P((int)),
    slc_import P((int)),
    slc_export P((void)),
    slc P((unsigned char *, int)),
    slc_check P((void)),
    slc_start_reply P((void)),
    slc_add_reply P((int, int, int)),
    slc_end_reply P((void));
E 27
extern int
D 27
    dosynch();
#endif	/* defined(NOT43) */
E 27
I 27
    slc_update P((void));
E 27
E 9
E 8

I 27
extern void
    env_opt P((unsigned char *, int)),
    env_opt_start P((void)),
    env_opt_start_info P((void)),
    env_opt_add P((unsigned char *)),
    env_opt_end P((int));

extern unsigned char
D 29
    *env_default P((int)),
E 29
I 29
    *env_default P((int, int)),
E 29
    *env_getvalue P((unsigned char *));

extern int
    get_status P((void)),
    dosynch P((void));

extern cc_t
    *tcval P((int));

E 27
I 17
D 20
#if	!defined(MSDOS)
# ifndef	USE_TERMIO
E 20
I 20
#ifndef	USE_TERMIO
E 20

extern struct	tchars ntc;
extern struct	ltchars nltc;
extern struct	sgttyb nttyb;

D 20
#  define termEofChar		ntc.t_eofc
#  define termEraseChar		nttyb.sg_erase
#  define termFlushChar		nltc.t_flushc
#  define termIntChar		ntc.t_intrc
#  define termKillChar		nttyb.sg_kill
#  define termLiteralNextChar	nltc.t_lnextc
#  define termQuitChar		ntc.t_quitc
#  define termSuspChar		nltc.t_suspc
#  define termRprntChar		nltc.t_rprntc
#  define termWerasChar		nltc.t_werasc
#  define termStartChar		ntc.t_startc
#  define termStopChar		ntc.t_stopc
E 20
I 20
# define termEofChar		ntc.t_eofc
# define termEraseChar		nttyb.sg_erase
# define termFlushChar		nltc.t_flushc
# define termIntChar		ntc.t_intrc
# define termKillChar		nttyb.sg_kill
# define termLiteralNextChar	nltc.t_lnextc
# define termQuitChar		ntc.t_quitc
# define termSuspChar		nltc.t_suspc
# define termRprntChar		nltc.t_rprntc
# define termWerasChar		nltc.t_werasc
# define termStartChar		ntc.t_startc
# define termStopChar		ntc.t_stopc
I 21
# define termForw1Char		ntc.t_brkc
D 25
extern char termForw2Char;
E 25
I 25
extern cc_t termForw2Char;
I 26
extern cc_t termAytChar;
E 26
E 25
E 21
E 20

D 20
#  define termEofCharp		&ntc.t_eofc
#  define termEraseCharp	&nttyb.sg_erase
#  define termFlushCharp	&nltc.t_flushc
#  define termIntCharp		&ntc.t_intrc
#  define termKillCharp		&nttyb.sg_kill
#  define termLiteralNextCharp	&nltc.t_lnextc
#  define termQuitCharp		&ntc.t_quitc
#  define termSuspCharp		&nltc.t_suspc
#  define termRprntCharp	&nltc.t_rprntc
#  define termWerasCharp	&nltc.t_werasc
#  define termStartCharp	&ntc.t_startc
#  define termStopCharp		&ntc.t_stopc
E 20
I 20
D 21
# define termEofCharp		(unsigned char *)&ntc.t_eofc
# define termEraseCharp		(unsigned char *)&nttyb.sg_erase
# define termFlushCharp		(unsigned char *)&nltc.t_flushc
# define termIntCharp		(unsigned char *)&ntc.t_intrc
# define termKillCharp		(unsigned char *)&nttyb.sg_kill
# define termLiteralNextCharp	(unsigned char *)&nltc.t_lnextc
# define termQuitCharp		(unsigned char *)&ntc.t_quitc
# define termSuspCharp		(unsigned char *)&nltc.t_suspc
# define termRprntCharp		(unsigned char *)&nltc.t_rprntc
# define termWerasCharp		(unsigned char *)&nltc.t_werasc
# define termStartCharp		(unsigned char *)&ntc.t_startc
# define termStopCharp		(unsigned char *)&ntc.t_stopc
E 21
I 21
# define termEofCharp		(cc_t *)&ntc.t_eofc
# define termEraseCharp		(cc_t *)&nttyb.sg_erase
# define termFlushCharp		(cc_t *)&nltc.t_flushc
# define termIntCharp		(cc_t *)&ntc.t_intrc
# define termKillCharp		(cc_t *)&nttyb.sg_kill
# define termLiteralNextCharp	(cc_t *)&nltc.t_lnextc
# define termQuitCharp		(cc_t *)&ntc.t_quitc
# define termSuspCharp		(cc_t *)&nltc.t_suspc
# define termRprntCharp		(cc_t *)&nltc.t_rprntc
# define termWerasCharp		(cc_t *)&nltc.t_werasc
# define termStartCharp		(cc_t *)&ntc.t_startc
# define termStopCharp		(cc_t *)&ntc.t_stopc
# define termForw1Charp		(cc_t *)&ntc.t_brkc
# define termForw2Charp		(cc_t *)&termForw2Char
I 26
# define termAytCharp		(cc_t *)&termAytChar
E 26
E 21
E 20

# else

extern struct	termio new_tc;

D 20
#  define termEofChar		new_tc.c_cc[VEOF]
#  define termEraseChar		new_tc.c_cc[VERASE]
#  define termIntChar		new_tc.c_cc[VINTR]
#  define termKillChar		new_tc.c_cc[VKILL]
#  define termQuitChar		new_tc.c_cc[VQUIT]
E 20
I 20
# define termEofChar		new_tc.c_cc[VEOF]
# define termEraseChar		new_tc.c_cc[VERASE]
# define termIntChar		new_tc.c_cc[VINTR]
# define termKillChar		new_tc.c_cc[VKILL]
# define termQuitChar		new_tc.c_cc[VQUIT]
E 20

E 17
D 20
extern char
I 17
    termSuspChar,
    termFlushChar,
    termWerasChar,
    termRprntChar,
    termLiteralNextChar,
    termStartChar,
    termStopChar;
E 20
I 20
# ifndef	VSUSP
D 25
extern char termSuspChar;
E 25
I 25
extern cc_t termSuspChar;
E 25
# else
#  define termSuspChar		new_tc.c_cc[VSUSP]
# endif
D 23
# ifndef	VFLUSHO
E 23
I 23
D 25
# ifndef	VDISCARD
E 23
extern char termFlushChar;
E 25
I 25
D 26
# if	!defined(VFLUSHO) && defined(VDISCARD)
#  define VFLUSHO VDISCARD
E 26
I 26
# if	defined(VFLUSHO) && !defined(VDISCARD)
#  define VDISCARD VFLUSHO
E 26
# endif
D 26
# ifndef	VFLUSHO
E 26
I 26
# ifndef	VDISCARD
E 26
extern cc_t termFlushChar;
E 25
# else
D 23
#  define termFlushChar		new_tc.c_cc[VFLUSHO]
E 23
I 23
D 25
#  define termFlushChar		new_tc.c_cc[VDISCARD]
E 25
I 25
D 26
#  define termFlushChar		new_tc.c_cc[VFLUSHO]
E 26
I 26
#  define termFlushChar		new_tc.c_cc[VDISCARD]
E 26
E 25
E 23
# endif
# ifndef VWERASE
D 25
extern char termWerasChar;
E 25
I 25
extern cc_t termWerasChar;
E 25
# else
#  define termWerasChar		new_tc.c_cc[VWERASE]
# endif
# ifndef	VREPRINT
D 25
extern char termRprntChar;
E 25
I 25
extern cc_t termRprntChar;
E 25
# else
#  define termRprntChar		new_tc.c_cc[VREPRINT]
# endif
# ifndef	VLNEXT
D 25
extern char termLiteralNextChar;
E 25
I 25
extern cc_t termLiteralNextChar;
E 25
# else
#  define termLiteralNextChar	new_tc.c_cc[VLNEXT]
# endif
# ifndef	VSTART
D 25
extern char termStartChar;
E 25
I 25
extern cc_t termStartChar;
E 25
# else
#  define termStartChar		new_tc.c_cc[VSTART]
# endif
# ifndef	VSTOP
D 25
extern char termStopChar;
E 25
I 25
extern cc_t termStopChar;
E 25
# else
#  define termStopChar		new_tc.c_cc[VSTOP]
# endif
I 21
# ifndef	VEOL
D 25
extern char termForw1Char;
E 25
I 25
extern cc_t termForw1Char;
E 25
# else
#  define termForw1Char		new_tc.c_cc[VEOL]
# endif
# ifndef	VEOL2
D 25
extern char termForw2Char;
E 25
I 25
extern cc_t termForw2Char;
E 25
# else
#  define termForw2Char		new_tc.c_cc[VEOL]
# endif
I 26
# ifndef	VSTATUS
extern cc_t termAytChar;
#else
#  define termAytChar		new_tc.c_cc[VSTATUS]
#endif
E 26
E 21
E 20

D 26
# ifndef CRAY
E 26
I 26
# if !defined(CRAY) || defined(__STDC__)
E 26
D 20
#  define termEofCharp		&new_tc.c_cc[VEOF]
#  define termEraseCharp	&new_tc.c_cc[VERASE]
#  define termIntCharp		&new_tc.c_cc[VINTR]
#  define termKillCharp		&new_tc.c_cc[VKILL]
#  define termQuitCharp		&new_tc.c_cc[VQUIT]
E 20
I 20
#  define termEofCharp		&termEofChar
#  define termEraseCharp	&termEraseChar
#  define termIntCharp		&termIntChar
#  define termKillCharp		&termKillChar
#  define termQuitCharp		&termQuitChar
#  define termSuspCharp		&termSuspChar
#  define termFlushCharp	&termFlushChar
#  define termWerasCharp	&termWerasChar
#  define termRprntCharp	&termRprntChar
#  define termLiteralNextCharp	&termLiteralNextChar
#  define termStartCharp	&termStartChar
#  define termStopCharp		&termStopChar
I 21
#  define termForw1Charp	&termForw1Char
#  define termForw2Charp	&termForw2Char
I 26
#  define termAytCharp		&termAytChar
E 26
E 21
E 20
# else
	/* Work around a compiler bug */
#  define termEofCharp		0
#  define termEraseCharp	0
#  define termIntCharp		0
#  define termKillCharp		0
#  define termQuitCharp		0
I 20
#  define termSuspCharp		0
#  define termFlushCharp	0
#  define termWerasCharp	0
#  define termRprntCharp	0
#  define termLiteralNextCharp	0
#  define termStartCharp	0
#  define termStopCharp		0
I 21
#  define termForw1Charp	0
#  define termForw2Charp	0
I 26
#  define termAytCharp		0
E 26
E 21
E 20
# endif
D 20
#  define termSuspCharp		&termSuspChar
#  define termFlushCharp	&termFlushChar
#  define termWerasCharp	&termWerasChar
#  define termRprntCharp	&termRprntChar
#  define termLiteralNextCharp	&termLiteralNextChar
#  define termStartCharp	&termStartChar
#  define termStopCharp		&termStopChar
# endif

#else	/* MSDOS */

extern char
E 17
    termEofChar,
    termEraseChar,
D 17
    termFlushChar,
E 17
    termIntChar,
    termKillChar,
I 17
    termQuitChar,
    termSuspChar,
    termFlushChar,
    termWerasChar,
    termRprntChar,
E 17
    termLiteralNextChar,
D 17
    termQuitChar;
E 17
I 17
    termStartChar,
    termStopChar;

E 20
#endif

E 17
I 3

/* Ring buffer structures which are shared */

extern Ring
D 8
	netoring,
	netiring,
	ttyoring,
	ttyiring;
E 8
I 8
    netoring,
    netiring,
    ttyoring,
    ttyiring;

/* Tn3270 section */
#if	defined(TN3270)

extern int
    HaveInput,		/* Whether an asynchronous I/O indication came in */
D 12
    noasynch,		/* Don't do signals on I/O (SIGURG, SIGIO) */
E 12
I 12
    noasynchtty,	/* Don't do signals on I/O (SIGURG, SIGIO) */
    noasynchnet,	/* Don't do signals on I/O (SIGURG, SIGIO) */
    sigiocount,		/* Count of SIGIO receptions */
E 12
    shell_active;	/* Subshell is active */

extern char
    *Ibackp,		/* Oldest byte of 3270 data */
    Ibuf[],		/* 3270 buffer */
    *Ifrontp,		/* Where next 3270 byte goes */
    tline[],
    *transcom;		/* Transparent command */

D 31
extern int
E 31
I 31
D 34
extern void
E 34
I 34
extern int
E 34
E 31
D 27
    settranscom();
E 27
I 27
    settranscom P((int, char**));
E 27

extern void
D 27
    inputAvailable();
E 27
I 27
D 31
    inputAvailable P((void));
E 31
I 31
    inputAvailable P((int));
E 31
E 27
#endif	/* defined(TN3270) */
E 8
E 3
E 1
