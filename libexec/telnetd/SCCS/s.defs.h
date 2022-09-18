h27121
s 00002/00002/00268
d D 8.1 93/06/04 19:06:51 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00266
d D 5.12 93/05/20 11:38:01 dab 12 11
c Several fixes.  The big one is that all of the
c code that was "#if defined(ENCRYPTION)" is now changed
c to "#ifdef ENCRYPTION", so that all the encryption code
c can be stripped out using unifdef.
c Other fixes:
c 	Add support for HP-UX (untested...)
c 	Simplification of the ENV_HACK stuff
c 	Add in UNICOS 8.0 secure system changes
c 	Clean up the option processing
c 	Fix up the usage() statement
e
s 00003/00001/00263
d D 5.11 92/12/18 14:05:47 dab 11 10
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Add Sun/SVR4 Streams support
c Allow for more ptys
c Environ suboption USERVAR support
c New Telnet Flowcontrol suboption support
c Server -k option to default to no kludge linemode
c Server -U option, allow only registered hosts to connect
e
s 00012/00002/00252
d D 5.10 91/03/01 01:35:22 dab 10 9
c Telnet AUTHENTICATION option
c Telnet ENCRYPT option (test version)
c Function prototypes
c Bug fixes and code cleanup
e
s 00009/00000/00245
d D 5.9 90/09/14 11:26:29 borman 9 8
c Latest round of bug fixes.  See the README file
c in src/usr.bin/telnet/README for the details.
e
s 00120/00020/00125
d D 5.8 90/06/28 13:05:59 borman 8 7
c Lots of bugfixes, add the ENVIRON and X-DISPLAY-LOC
c options, "-l user" to the command line, diagnostic flags.
e
s 00002/00000/00143
d D 5.7 90/06/27 17:07:57 karels 7 6
c add IP type-of-service without gettos (at least for now)
e
s 00001/00011/00142
d D 5.6 90/06/01 15:55:29 bostic 6 5
c new copyright notice
e
s 00001/00001/00152
d D 5.5 90/05/15 19:47:33 bostic 5 4
c string.h is ANSI C include file
e
s 00011/00002/00142
d D 5.4 90/02/28 15:35:47 borman 4 3
c Many fixes.  1) Use the cc_t typedef from termios.h
c 2) Fix for SYSV VEOF/VMIN overlap
c 3) Add two missing "break" statements
c 4) Add SLC_FORW[12] support
c 5) start of TOS support
c 6) Make sure things get initialized properly
c 7) Don't send Urgent mode data, since some clients go into infinate loops...
e
s 00001/00002/00143
d D 5.3 89/11/10 10:22:38 borman 3 2
c Fix bugs in state machine, add more TERMIOS support
e
s 00001/00000/00144
d D 5.2 89/10/04 10:59:28 marc 2 1
c need ioctl.h for the pty ioctls
e
s 00144/00000/00000
d D 5.1 89/09/01 15:17:47 borman 1 0
c New telnetd, with LINEMODE support
e
u
U
t
T
I 1
/*
D 13
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
D 6
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
 * %sccs.include.redist.c%
E 6
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Telnet server defines
 */
#include <sys/types.h>
#include <sys/param.h>

#ifndef	BSD
# define	BSD 43
#endif

D 8
#if BSD > 43
#define	USE_TERMIO
E 8
I 8
#if	defined(CRAY) && !defined(LINEMODE)
# define SYSV_TERMIO
# define LINEMODE
# define KLUDGELINEMODE
D 10
# define NO_GETTYTAB
E 10
# define DIAGNOSTICS
I 10
# if defined(UNICOS50) && !defined(UNICOS5)
#  define UNICOS5
# endif
E 10
# if !defined(UNICOS5)
#  define BFTPDAEMON
#  define HAS_IP_TOS
# endif
#endif /* CRAY */
#if defined(UNICOS5) && !defined(NO_SETSID)
# define NO_SETSID
E 8
#endif

D 8
#ifdef	CRAY
# define	NEWINIT
# define	SYSV_TERMIO
# define	NO_GETTYTAB
# define	signal sigset
#endif	/* CRAY */
E 8
I 8
#if defined(PRINTOPTIONS) && defined(DIAGNOSTICS)
#define TELOPTS
#define TELCMDS
I 10
#define	SLC_NAMES
E 10
#endif
E 8

D 8
#ifdef	SYSV_TERMIO
E 8
I 8
#if	defined(SYSV_TERMIO) && !defined(USE_TERMIO)
E 8
# define	USE_TERMIO
#endif

#include <sys/socket.h>
#ifndef	CRAY
#include <sys/wait.h>
#endif	/* CRAY */
I 10
#include <fcntl.h>
E 10
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/time.h>
I 8
#ifndef	FILIO_H
E 8
I 3
#include <sys/ioctl.h>
I 8
#else
#include <sys/filio.h>
#endif
E 8
E 3

#include <netinet/in.h>
I 7
D 8
#include <netinet/in_systm.h>
#include <netinet/ip.h>
E 8
E 7

#include <arpa/telnet.h>

#include <stdio.h>
I 10
#ifdef	__STDC__
#include <stdlib.h>
#endif
E 10
#include <signal.h>
#include <errno.h>
#include <netdb.h>
#include <syslog.h>
I 4
#ifndef	LOG_DAEMON
#define	LOG_DAEMON	0
#endif
#ifndef	LOG_ODELAY
#define	LOG_ODELAY	0
#endif
E 4
#include <ctype.h>
I 8
#ifndef NO_STRING_H
E 8
D 5
#include <strings.h>
E 5
I 5
#include <string.h>
I 8
#else
#include <strings.h>
#endif
E 8
E 5

#ifndef	USE_TERMIO
#include <sgtty.h>
I 4
D 8
typedef unsigned char cc_t;
E 8
E 4
#else
# ifdef	SYSV_TERMIO
# include <termio.h>
# else
I 2
D 3
# include <sys/ioctl.h>
E 3
E 2
# include <termios.h>
# endif
#endif
I 8
#if !defined(USE_TERMIO) || defined(NO_CC_T)
typedef unsigned char cc_t;
#endif
E 8

I 10
#ifdef	__STDC__
#include <unistd.h>
#endif

E 10
I 9
#ifndef _POSIX_VDISABLE
# ifdef VDISABLE
#  define _POSIX_VDISABLE VDISABLE
# else
#  define _POSIX_VDISABLE ((unsigned char)'\377')
# endif
#endif


E 9
#ifdef	CRAY
D 10
#include <sys/fcntl.h>
E 10
D 3
#include <sys/ioctl.h>
E 3
# ifdef	CRAY1
# include <sys/pty.h>
#  ifndef FD_ZERO
# include <sys/select.h>
#  endif /* FD_ZERO */
# endif	/* CRAY1 */

#include <memory.h>
#endif	/* CRAY */

I 12
#ifdef __hpux
#include <sys/ptyio.h>
#endif

E 12
D 8
#if	defined(TCSIG) || defined(TIOCPKT_IOCTL)
# define	LINEMODE
# define	KLUDGELINEMODE
E 8
I 8
#if	!defined(TIOCSCTTY) && defined(TCSETCTTY)
# define	TIOCSCTTY TCSETCTTY
E 8
#endif

#ifndef	FD_SET
I 4
#ifndef	HAVE_fd_set
E 4
typedef struct fd_set { int fds_bits[1]; } fd_set;
I 4
#endif
E 4

#define	FD_SET(n, p)	((p)->fds_bits[0] |= (1<<(n)))
#define	FD_CLR(n, p)	((p)->fds_bits[0] &= ~(1<<(n)))
#define	FD_ISSET(n, p)	((p)->fds_bits[0] & (1<<(n)))
#define FD_ZERO(p)	((p)->fds_bits[0] = 0)
#endif	/* FD_SET */

D 8
#define	OPT_NO			0		/* won't do this option */
#define	OPT_YES			1		/* will do this option */
#define	OPT_YES_BUT_ALWAYS_LOOK	2
#define	OPT_NO_BUT_ALWAYS_LOOK	3

E 8
/*
 * I/O data buffers defines
 */
#define	NETSLOP	64
#ifdef CRAY
#undef BUFSIZ
#define BUFSIZ  2048
#endif

#define	NIACCUM(c)	{   *netip++ = c; \
			    ncc++; \
			}

/* clock manipulations */
#define	settimer(x)	(clocks.x = ++clocks.system)
#define	sequenceIs(x,y)	(clocks.x < clocks.y)

/*
 * Linemode support states, in decreasing order of importance
 */
D 11
#define REAL_LINEMODE	0x02
E 11
I 11
#define REAL_LINEMODE	0x04
#define KLUDGE_OK	0x03
#define	NO_AUTOKLUDGE	0x02
E 11
#define KLUDGE_LINEMODE	0x01
#define NO_LINEMODE	0x00

/*
 * Structures of information for each special character function.
 */
typedef struct {
	unsigned char	flag;		/* the flags for this function */
D 4
	unsigned char	val;		/* the value of the special character */
E 4
I 4
	cc_t		val;		/* the value of the special character */
E 4
} slcent, *Slcent;

typedef struct {
	slcent		defset;		/* the default settings */
	slcent		current;	/* the current settings */
D 4
	unsigned char	*sptr;		/* a pointer to the char in */
E 4
I 4
	cc_t		*sptr;		/* a pointer to the char in */
E 4
					/* system data structures */
} slcfun, *Slcfun;
I 8

#ifdef DIAGNOSTICS
/*
 * Diagnostics capabilities
 */
#define	TD_REPORT	0x01	/* Report operations to client */
#define TD_EXERCISE	0x02	/* Exercise client's implementation */
#define TD_NETDATA	0x04	/* Display received data stream */
#define TD_PTYDATA	0x08	/* Display data passed to pty */
#define	TD_OPTIONS	0x10	/* Report just telnet options */
#endif /* DIAGNOSTICS */

/*
 * We keep track of each side of the option negotiation.
 */

#define	MY_STATE_WILL		0x01
#define	MY_WANT_STATE_WILL	0x02
#define	MY_STATE_DO		0x04
#define	MY_WANT_STATE_DO	0x08

/*
 * Macros to check the current state of things
 */

#define	my_state_is_do(opt)		(options[opt]&MY_STATE_DO)
#define	my_state_is_will(opt)		(options[opt]&MY_STATE_WILL)
#define my_want_state_is_do(opt)	(options[opt]&MY_WANT_STATE_DO)
#define my_want_state_is_will(opt)	(options[opt]&MY_WANT_STATE_WILL)

#define	my_state_is_dont(opt)		(!my_state_is_do(opt))
#define	my_state_is_wont(opt)		(!my_state_is_will(opt))
#define my_want_state_is_dont(opt)	(!my_want_state_is_do(opt))
#define my_want_state_is_wont(opt)	(!my_want_state_is_will(opt))

#define	set_my_state_do(opt)		(options[opt] |= MY_STATE_DO)
#define	set_my_state_will(opt)		(options[opt] |= MY_STATE_WILL)
#define	set_my_want_state_do(opt)	(options[opt] |= MY_WANT_STATE_DO)
#define	set_my_want_state_will(opt)	(options[opt] |= MY_WANT_STATE_WILL)

#define	set_my_state_dont(opt)		(options[opt] &= ~MY_STATE_DO)
#define	set_my_state_wont(opt)		(options[opt] &= ~MY_STATE_WILL)
#define	set_my_want_state_dont(opt)	(options[opt] &= ~MY_WANT_STATE_DO)
#define	set_my_want_state_wont(opt)	(options[opt] &= ~MY_WANT_STATE_WILL)

/*
 * Tricky code here.  What we want to know is if the MY_STATE_WILL
 * and MY_WANT_STATE_WILL bits have the same value.  Since the two
 * bits are adjacent, a little arithmatic will show that by adding
 * in the lower bit, the upper bit will be set if the two bits were
 * different, and clear if they were the same.
 */
#define my_will_wont_is_changing(opt) \
			((options[opt]+MY_STATE_WILL) & MY_WANT_STATE_WILL)

#define my_do_dont_is_changing(opt) \
			((options[opt]+MY_STATE_DO) & MY_WANT_STATE_DO)

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

#define his_will_wont_is_changing	my_do_dont_is_changing
#define his_do_dont_is_changing		my_will_wont_is_changing
E 8
E 1
