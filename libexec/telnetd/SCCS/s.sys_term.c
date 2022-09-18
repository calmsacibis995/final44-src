h31808
s 00118/00035/02137
d D 8.4 95/05/30 22:02:46 dab 27 26
c code cleanup, change b*() to mem*()
c Add setting up of LINEMODE environment variable.
e
s 00072/00009/02100
d D 8.3 95/02/16 11:58:48 dab 26 24
c Add code for machines that define baud rates directly
c rather than encoded (it's simpler).
c Put in a couple of Solaris bug fixes.
c Put in a sleep(1) before execing login, so that telnetd can
c finish initializing the tty, which can wipe out the login
c banner message if it gets written before telnetd is done.
c Also fix a bug where realloc() was not being called correctly.
e
s 00072/00009/02100
d R 8.3 95/02/16 11:45:41 dab 25 24
c Clean up how suboptions are put together to ensure that
c we always double any SE or IAC that is imbedded in the suboption.
e
s 00159/00024/01950
d D 8.2 93/12/15 11:39:59 dab 24 23
c A bunch of bugfixes.
c Support for Solaris.
c new LOGIN_R option for systems that
c don't have "login -f".
c Support for the new ENVIRON option.
e
s 00002/00002/01972
d D 8.1 93/06/04 19:07:14 bostic 23 22
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00128/00028/01846
d D 5.22 93/05/20 11:38:05 dab 22 21
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
s 00003/00003/01871
d D 5.21 93/04/12 18:18:09 torek 21 20
c ifdef sun does not imply SunOS: add gross hack to avoid bogus SunOS
c bug workaround.
e
s 00024/00024/01850
d D 5.20 93/04/05 16:48:25 dab 20 19
c Fix gcc2 warnings.
c Add ENV_HACK stuff to deal with telnet clients that
c have the wrong definitions for ENV_VAR and ENV_VALUE.
c Fix up the flow-control processing to work on systems
c that don't use Linemode in the server.
e
s 00002/00002/01872
d D 5.19 93/01/19 12:47:21 dab 19 18
c Fix up the code that deals with the
c flowcontrol option to properly deal with the
c RESTART_ANY and RESTART_XON suboptions.
e
s 00011/00001/01863
d D 5.18 93/01/18 15:19:39 dab 18 17
c Go back to using the global "pty" variable
c instead of the "ttyfd" variable that was put in for
c streams pty support on Suns.  (The ttyfd stuff is
c now just an ifdef.)  This change fixes a problem where
c telnetd was not coming up in linemode properly.
e
s 00220/00014/01644
d D 5.17 92/12/18 14:05:51 dab 17 16
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Add Sun/SVR4 Streams support
c Allow for more ptys
c Environ suboption USERVAR support
c New Telnet Flowcontrol suboption support
c Server -k option to default to no kludge linemode
c Server -U option, allow only registered hosts to connect
e
s 00017/00004/01641
d D 5.16 91/03/22 13:44:08 dab 16 15
c Fix for Cray UNICOS sessions
e
s 00002/00002/01643
d D 5.15 91/03/05 09:01:16 dab 15 14
c Another fix for initial terminal speed setting.
c If the client telnet didn't support the terminal speed
c option, we were setting the terminal speed to 0.  Not good.
e
s 00002/00002/01643
d D 5.14 91/03/01 14:51:04 dab 14 13
c In the initial terminal setup, cfset[io]speed() was
e
s 00361/00113/01284
d D 5.13 91/03/01 01:35:12 dab 13 12
c Telnet AUTHENTICATION option
c Telnet ENCRYPT option (test version)
c Function prototypes
c Bug fixes and code cleanup
e
s 00002/00002/01395
d D 5.12 91/02/26 11:50:35 bostic 12 11
c ANSI fixes (one real bug!)
e
s 00253/00124/01144
d D 5.11 90/09/14 11:26:37 borman 11 10
c Latest round of bug fixes.  See the README file
c in src/usr.bin/telnet/README for the details.
e
s 00001/00001/01267
d D 5.10 90/06/30 18:47:01 marc 10 9
c wait for output to drain when changing tty modes
e
s 00009/00011/01259
d D 5.9 90/06/28 22:38:05 marc 9 8
c pty library
e
s 00243/00036/01027
d D 5.8 90/06/28 13:06:18 borman 8 7
c Lots of bugfixes, add the ENVIRON and X-DISPLAY-LOC
c options, "-l user" to the command line, diagnostic flags.
e
s 00002/00002/01061
d D 5.7 90/06/15 14:04:45 marc 7 6
c VFLUSHO -> VDISCARD
e
s 00001/00011/01062
d D 5.6 90/06/01 15:56:15 bostic 6 5
c new copyright notice
e
s 00066/00037/01007
d D 5.5 90/02/28 15:35:56 borman 5 4
c Many fixes.  1) Use the cc_t typedef from termios.h
c 2) Fix for SYSV VEOF/VMIN overlap
c 3) Add two missing "break" statements
c 4) Add SLC_FORW[12] support
c 5) start of TOS support
c 6) Make sure things get initialized properly
c 7) Don't send Urgent mode data, since some clients go into infinate loops...
e
s 00004/00000/01040
d D 5.4 90/02/01 17:04:18 sklower 4 3
c Hope that TIOCSETA is close enough to TCSETA to work in telnetd . . .
e
s 00053/00028/00987
d D 5.3 89/11/10 10:22:44 borman 3 2
c Fix bugs in state machine, add more TERMIOS support
e
s 00001/00001/01014
d D 5.2 89/09/05 13:42:50 borman 2 1
c change "#ifdef BSD > 43" to "#if BSD > 43"
e
s 01015/00000/00000
d D 5.1 89/09/01 15:17:52 borman 1 0
c New telnetd, with LINEMODE support
e
u
U
t
T
I 1
/*
D 23
 * Copyright (c) 1989 Regents of the University of California.
 * All rights reserved.
E 23
I 23
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 23
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
 * %sccs.include.redist.c%
E 6
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include "telnetd.h"
#include "pathnames.h"

I 13
D 17
#if	defined(AUTHENTICATE)
E 17
I 17
#if	defined(AUTHENTICATION)
E 17
#include <libtelnet/auth.h>
#endif

I 22
#if defined(CRAY) || defined(__hpux)
# define PARENT_DOES_UTMP
#endif

E 22
E 13
#ifdef	NEWINIT
#include <initreq.h>
I 22
int	utmp_len = MAXHOSTNAMELEN;	/* sizeof(init_request.host) */
E 22
#else	/* NEWINIT*/
D 17
#include <utmp.h>
E 17
I 17
# ifdef	UTMPX
# include <utmpx.h>
I 24
struct	utmpx wtmp;
E 24
# else
# include <utmp.h>
D 24
# endif /* UTMPX */
E 24
E 17
struct	utmp wtmp;
I 24
# endif /* UTMPX */
E 24

I 17
int	utmp_len = sizeof(wtmp.ut_host);
E 17
D 22
# ifndef CRAY
E 22
I 22
# ifndef PARENT_DOES_UTMP
E 22
char	wtmpf[]	= "/usr/adm/wtmp";
char	utmpf[] = "/etc/utmp";
D 22
# else	/* CRAY */
E 22
I 22
# else /* PARENT_DOES_UTMP */
E 22
char	wtmpf[]	= "/etc/wtmp";
I 22
# endif /* PARENT_DOES_UTMP */

# ifdef CRAY
E 22
I 13
#include <tmpdir.h>
#include <sys/wait.h>
I 22
D 27
#  if defined(_SC_CRAY_SECURE_SYS) && !defined(SCM_SECURITY)
   /*
    * UNICOS 6.0/6.1 do not have SCM_SECURITY defined, so we can
    * use it to tell us to turn off all the socket security code,
    * since that is only used in UNICOS 7.0 and later.
    */
#   undef _SC_CRAY_SECURE_SYS
E 27
I 27
#  if (UNICOS_LVL == '7.0') || (UNICOS_LVL == '7.1')
#   define UNICOS7x
E 27
#  endif

E 22
I 17
D 27
#  if defined(_SC_CRAY_SECURE_SYS)
E 27
I 27
#  ifdef UNICOS7x
E 27
#include <sys/sysv.h>
#include <sys/secstat.h>
extern int secflag;
extern struct sysv sysv;
D 27
#  endif /* _SC_CRAY_SECURE_SYS */
E 27
I 27
#  endif /* UNICOS7x */
E 27
E 17
E 13
# endif	/* CRAY */
#endif	/* NEWINIT */

I 17
#ifdef	STREAMSPTY
#include <sac.h>
#include <sys/stropts.h>
#endif

E 17
#define SCPYN(a, b)	(void) strncpy(a, b, sizeof(a))
#define SCMPN(a, b)	strncmp(a, b, sizeof(a))

I 8
#ifdef	STREAMS
#include <sys/stream.h>
#endif
I 22
#ifdef __hpux
#include <sys/resource.h>
#include <sys/proc.h>
#endif
E 22
E 8
#include <sys/tty.h>
#ifdef	t_erase
#undef	t_erase
#undef	t_kill
#undef	t_intrc
#undef	t_quitc
#undef	t_startc
#undef	t_stopc
#undef	t_eofc
#undef	t_brkc
#undef	t_suspc
#undef	t_dsuspc
#undef	t_rprntc
#undef	t_flushc
#undef	t_werasc
#undef	t_lnextc
#endif

I 8
#if defined(UNICOS5) && defined(CRAY2) && !defined(EXTPROC)
# define EXTPROC 0400
#endif

E 8
#ifndef	USE_TERMIO
struct termbuf {
	struct sgttyb sg;
	struct tchars tc;
	struct ltchars ltc;
	int state;
	int lflags;
} termbuf, termbuf2;
I 11
# define	cfsetospeed(tp, val)	(tp)->sg.sg_ospeed = (val)
# define	cfsetispeed(tp, val)	(tp)->sg.sg_ispeed = (val)
I 13
# define	cfgetospeed(tp)		(tp)->sg.sg_ospeed
# define	cfgetispeed(tp)		(tp)->sg.sg_ispeed
E 13
E 11
#else	/* USE_TERMIO */
D 8
# ifndef EXTPROC
# define EXTPROC 0400
# endif
E 8
# ifdef	SYSV_TERMIO
#	define termios termio
# endif
I 4
D 11
# ifndef TCSETA
E 11
I 11
# ifndef	TCSANOW
E 11
D 8
# define TCSETA TIOCSETA
# define TCGETA TIOCGETA
E 8
I 8
#  ifdef TCSETS
D 11
#   define TCSETA TCSETS
#   define TCGETA TCGETS
E 11
I 11
#   define	TCSANOW		TCSETS
#   define	TCSADRAIN	TCSETSW
D 13
#   define	tcgetattr(f, t)	iotcl(f, TCGETS, t)
E 13
I 13
#   define	tcgetattr(f, t)	ioctl(f, TCGETS, (char *)t)
E 13
E 11
#  else
D 10
#   define TCSETA TIOCSETA
E 10
I 10
D 11
#   define TCSETA TIOCSETAW
E 10
#   define TCGETA TIOCGETA
E 11
I 11
#   ifdef TCSETA
#    define	TCSANOW		TCSETA
#    define	TCSADRAIN	TCSETAW
D 13
#    define	tcgetattr(f, t)	ioctl(f, TCGETA, t)
E 13
I 13
#    define	tcgetattr(f, t)	ioctl(f, TCGETA, (char *)t)
E 13
#   else
#    define	TCSANOW		TIOCSETA
#    define	TCSADRAIN	TIOCSETAW
D 13
#    define	tcgetattr(f, t)	iotcl(f, TIOCGETA, t)
E 13
I 13
#    define	tcgetattr(f, t)	ioctl(f, TIOCGETA, (char *)t)
E 13
#   endif
E 11
#  endif
E 8
D 11
# endif /* 4.4BSD */
E 11
I 11
#  define	tcsetattr(f, a, t)	ioctl(f, a, t)
#  define	cfsetospeed(tp, val)	(tp)->c_cflag &= ~CBAUD; \
					(tp)->c_cflag |= (val)
I 13
#  define	cfgetospeed(tp)		((tp)->c_cflag & CBAUD)
E 13
#  ifdef CIBAUD
#   define	cfsetispeed(tp, val)	(tp)->c_cflag &= ~CIBAUD; \
					(tp)->c_cflag |= ((val)<<IBSHIFT)
I 13
#   define	cfgetispeed(tp)		(((tp)->c_cflag & CIBAUD)>>IBSHIFT)
E 13
#  else
#   define	cfsetispeed(tp, val)	(tp)->c_cflag &= ~CBAUD; \
					(tp)->c_cflag |= (val)
I 13
#   define	cfgetispeed(tp)		((tp)->c_cflag & CBAUD)
E 13
#  endif
# endif /* TCSANOW */
E 11
E 4
struct termios termbuf, termbuf2;	/* pty control structure */
I 18
# ifdef  STREAMSPTY
E 18
I 17
int ttyfd = -1;
I 18
# endif
E 18
E 17
#endif	/* USE_TERMIO */

/*
 * init_termbuf()
 * copy_termbuf(cp)
 * set_termbuf()
 *
 * These three routines are used to get and set the "termbuf" structure
 * to and from the kernel.  init_termbuf() gets the current settings.
 * copy_termbuf() hands in a new "termbuf" to write to the kernel, and
 * set_termbuf() writes the structure into the kernel.
 */

I 13
	void
E 13
init_termbuf()
{
#ifndef	USE_TERMIO
	(void) ioctl(pty, TIOCGETP, (char *)&termbuf.sg);
	(void) ioctl(pty, TIOCGETC, (char *)&termbuf.tc);
	(void) ioctl(pty, TIOCGLTC, (char *)&termbuf.ltc);
# ifdef	TIOCGSTATE
	(void) ioctl(pty, TIOCGSTATE, (char *)&termbuf.state);
# endif
#else
I 18
# ifdef  STREAMSPTY
E 18
D 11
	(void) ioctl(pty, TCGETA, (char *)&termbuf);
E 11
I 11
D 12
	(void) tcgetattr(pty, (char *)&termbuf);
E 12
I 12
D 17
	(void) tcgetattr(pty, &termbuf);
E 17
I 17
	(void) tcgetattr(ttyfd, &termbuf);
I 18
# else
	(void) tcgetattr(pty, &termbuf);
# endif
E 18
E 17
E 12
E 11
#endif
	termbuf2 = termbuf;
}

#if	defined(LINEMODE) && defined(TIOCPKT_IOCTL)
I 13
	void
E 13
copy_termbuf(cp, len)
D 13
char *cp;
int len;
E 13
I 13
	char *cp;
	int len;
E 13
{
	if (len > sizeof(termbuf))
		len = sizeof(termbuf);
D 27
	bcopy(cp, (char *)&termbuf, len);
E 27
I 27
	memmove((char *)&termbuf, cp, len);
E 27
	termbuf2 = termbuf;
}
#endif	/* defined(LINEMODE) && defined(TIOCPKT_IOCTL) */

I 13
	void
E 13
set_termbuf()
{
	/*
	 * Only make the necessary changes.
	 */
#ifndef	USE_TERMIO
D 27
	if (bcmp((char *)&termbuf.sg, (char *)&termbuf2.sg, sizeof(termbuf.sg)))
E 27
I 27
	if (memcmp((char *)&termbuf.sg, (char *)&termbuf2.sg,
							sizeof(termbuf.sg)))
E 27
D 11
		(void) ioctl(pty, TIOCSETP, (char *)&termbuf.sg);
E 11
I 11
		(void) ioctl(pty, TIOCSETN, (char *)&termbuf.sg);
E 11
D 27
	if (bcmp((char *)&termbuf.tc, (char *)&termbuf2.tc, sizeof(termbuf.tc)))
E 27
I 27
	if (memcmp((char *)&termbuf.tc, (char *)&termbuf2.tc,
							sizeof(termbuf.tc)))
E 27
		(void) ioctl(pty, TIOCSETC, (char *)&termbuf.tc);
D 27
	if (bcmp((char *)&termbuf.ltc, (char *)&termbuf2.ltc,
E 27
I 27
	if (memcmp((char *)&termbuf.ltc, (char *)&termbuf2.ltc,
E 27
							sizeof(termbuf.ltc)))
		(void) ioctl(pty, TIOCSLTC, (char *)&termbuf.ltc);
	if (termbuf.lflags != termbuf2.lflags)
		(void) ioctl(pty, TIOCLSET, (char *)&termbuf.lflags);
#else	/* USE_TERMIO */
D 27
	if (bcmp((char *)&termbuf, (char *)&termbuf2, sizeof(termbuf)))
E 27
I 27
	if (memcmp((char *)&termbuf, (char *)&termbuf2, sizeof(termbuf)))
E 27
I 18
# ifdef  STREAMSPTY
E 18
D 11
		(void) ioctl(pty, TCSETA, (char *)&termbuf);
E 11
I 11
D 12
		(void) tcsetattr(pty, TCSADRAIN, (char *)&termbuf);
E 12
I 12
D 13
		(void) tcsetattr(pty, TCSADRAIN, &termbuf);
E 13
I 13
D 17
		(void) tcsetattr(pty, TCSANOW, &termbuf);
E 13
E 12
E 11
D 5
# ifdef	CRAY2
E 5
I 5
# if	defined(CRAY2) && defined(UNCIOS5)
E 17
I 17
		(void) tcsetattr(ttyfd, TCSANOW, &termbuf);
I 18
# else
		(void) tcsetattr(pty, TCSANOW, &termbuf);
# endif
E 18
# if	defined(CRAY2) && defined(UNICOS5)
E 17
E 5
	needtermstat = 1;
# endif
#endif	/* USE_TERMIO */
}


/*
 * spcset(func, valp, valpp)
 *
 * This function takes various special characters (func), and
 * sets *valp to the current value of that character, and
 * *valpp to point to where in the "termbuf" structure that
 * value is kept.
 *
 * It returns the SLC_ level of support for this function.
 */

#ifndef	USE_TERMIO
I 13
	int
E 13
spcset(func, valp, valpp)
D 13
int func;
D 5
unsigned char *valp;
unsigned char **valpp;
E 5
I 5
cc_t *valp;
cc_t **valpp;
E 13
I 13
	int func;
	cc_t *valp;
	cc_t **valpp;
E 13
E 5
{
	switch(func) {
	case SLC_EOF:
		*valp = termbuf.tc.t_eofc;
D 5
		*valpp = (unsigned char *)&termbuf.tc.t_eofc;
E 5
I 5
		*valpp = (cc_t *)&termbuf.tc.t_eofc;
E 5
		return(SLC_VARIABLE);
	case SLC_EC:
		*valp = termbuf.sg.sg_erase;
D 5
		*valpp = (unsigned char *)&termbuf.sg.sg_erase;
E 5
I 5
		*valpp = (cc_t *)&termbuf.sg.sg_erase;
E 5
		return(SLC_VARIABLE);
	case SLC_EL:
		*valp = termbuf.sg.sg_kill;
D 5
		*valpp = (unsigned char *)&termbuf.sg.sg_kill;
E 5
I 5
		*valpp = (cc_t *)&termbuf.sg.sg_kill;
E 5
		return(SLC_VARIABLE);
	case SLC_IP:
		*valp = termbuf.tc.t_intrc;
D 5
		*valpp = (unsigned char *)&termbuf.tc.t_intrc;
E 5
I 5
		*valpp = (cc_t *)&termbuf.tc.t_intrc;
E 5
		return(SLC_VARIABLE|SLC_FLUSHIN|SLC_FLUSHOUT);
	case SLC_ABORT:
		*valp = termbuf.tc.t_quitc;
D 5
		*valpp = (unsigned char *)&termbuf.tc.t_quitc;
E 5
I 5
		*valpp = (cc_t *)&termbuf.tc.t_quitc;
E 5
		return(SLC_VARIABLE|SLC_FLUSHIN|SLC_FLUSHOUT);
	case SLC_XON:
		*valp = termbuf.tc.t_startc;
D 5
		*valpp = (unsigned char *)&termbuf.tc.t_startc;
E 5
I 5
		*valpp = (cc_t *)&termbuf.tc.t_startc;
E 5
		return(SLC_VARIABLE);
	case SLC_XOFF:
		*valp = termbuf.tc.t_stopc;
D 5
		*valpp = (unsigned char *)&termbuf.tc.t_stopc;
E 5
I 5
		*valpp = (cc_t *)&termbuf.tc.t_stopc;
E 5
		return(SLC_VARIABLE);
	case SLC_AO:
		*valp = termbuf.ltc.t_flushc;
D 5
		*valpp = (unsigned char *)&termbuf.ltc.t_flushc;
E 5
I 5
		*valpp = (cc_t *)&termbuf.ltc.t_flushc;
E 5
		return(SLC_VARIABLE);
	case SLC_SUSP:
		*valp = termbuf.ltc.t_suspc;
D 5
		*valpp = (unsigned char *)&termbuf.ltc.t_suspc;
E 5
I 5
		*valpp = (cc_t *)&termbuf.ltc.t_suspc;
E 5
		return(SLC_VARIABLE);
	case SLC_EW:
		*valp = termbuf.ltc.t_werasc;
D 5
		*valpp = (unsigned char *)&termbuf.ltc.t_werasc;
E 5
I 5
		*valpp = (cc_t *)&termbuf.ltc.t_werasc;
E 5
		return(SLC_VARIABLE);
	case SLC_RP:
		*valp = termbuf.ltc.t_rprntc;
D 5
		*valpp = (unsigned char *)&termbuf.ltc.t_rprntc;
E 5
I 5
		*valpp = (cc_t *)&termbuf.ltc.t_rprntc;
E 5
		return(SLC_VARIABLE);
	case SLC_LNEXT:
		*valp = termbuf.ltc.t_lnextc;
D 5
		*valpp = (unsigned char *)&termbuf.ltc.t_lnextc;
E 5
I 5
		*valpp = (cc_t *)&termbuf.ltc.t_lnextc;
E 5
		return(SLC_VARIABLE);
I 5
	case SLC_FORW1:
		*valp = termbuf.tc.t_brkc;
		*valpp = (cc_t *)&termbuf.ltc.t_lnextc;
		return(SLC_VARIABLE);
E 5
	case SLC_BRK:
	case SLC_SYNCH:
	case SLC_AYT:
	case SLC_EOR:
D 5
		*valp = 0;
		*valpp = 0;
E 5
I 5
		*valp = (cc_t)0;
		*valpp = (cc_t *)0;
E 5
		return(SLC_DEFAULT);
	default:
D 5
		*valp = 0;
		*valpp = 0;
E 5
I 5
		*valp = (cc_t)0;
		*valpp = (cc_t *)0;
E 5
		return(SLC_NOSUPPORT);
	}
}

#else	/* USE_TERMIO */

I 13
	int
E 13
spcset(func, valp, valpp)
D 13
int func;
D 5
unsigned char *valp;
unsigned char **valpp;
E 5
I 5
cc_t *valp;
cc_t **valpp;
E 13
I 13
	int func;
	cc_t *valp;
	cc_t **valpp;
E 13
E 5
{
I 3

#define	setval(a, b)	*valp = termbuf.c_cc[a]; \
			*valpp = &termbuf.c_cc[a]; \
			return(b);
D 5
#define	defval(a)	*valp = (a); *valpp = 0; return(SLC_DEFAULT);
E 5
I 5
#define	defval(a) *valp = ((cc_t)a); *valpp = (cc_t *)0; return(SLC_DEFAULT);
E 5

E 3
	switch(func) {
	case SLC_EOF:
D 3
		*valp = termbuf.c_cc[VEOF];
		*valpp = &termbuf.c_cc[VEOF];
		return(SLC_VARIABLE);
E 3
I 3
		setval(VEOF, SLC_VARIABLE);
E 3
	case SLC_EC:
D 3
		*valp = termbuf.c_cc[VERASE];
		*valpp = &termbuf.c_cc[VERASE];
		return(SLC_VARIABLE);
E 3
I 3
		setval(VERASE, SLC_VARIABLE);
E 3
	case SLC_EL:
D 3
		*valp = termbuf.c_cc[VKILL];
		*valpp = &termbuf.c_cc[VKILL];
		return(SLC_VARIABLE);
E 3
I 3
		setval(VKILL, SLC_VARIABLE);
E 3
	case SLC_IP:
D 3
		*valp = termbuf.c_cc[VINTR];
		*valpp = &termbuf.c_cc[VINTR];
		return(SLC_VARIABLE|SLC_FLUSHIN|SLC_FLUSHOUT);
E 3
I 3
		setval(VINTR, SLC_VARIABLE|SLC_FLUSHIN|SLC_FLUSHOUT);
E 3
	case SLC_ABORT:
D 3
		*valp = termbuf.c_cc[VQUIT];
		*valpp = &termbuf.c_cc[VQUIT];
		return(SLC_VARIABLE|SLC_FLUSHIN|SLC_FLUSHOUT);
E 3
I 3
		setval(VQUIT, SLC_VARIABLE|SLC_FLUSHIN|SLC_FLUSHOUT);
E 3
	case SLC_XON:
D 3
		*valp = 0x13;
		*valpp = 0;
		return(SLC_DEFAULT);
E 3
I 3
#ifdef	VSTART
		setval(VSTART, SLC_VARIABLE);
#else
		defval(0x13);
#endif
E 3
	case SLC_XOFF:
D 3
		*valp = 0x11;
		*valpp = 0;
		return(SLC_DEFAULT);
E 3
I 3
#ifdef	VSTOP
		setval(VSTOP, SLC_VARIABLE);
#else
		defval(0x11);
#endif
E 3
	case SLC_EW:
I 3
#ifdef	VWERASE
		setval(VWERASE, SLC_VARIABLE);
#else
		defval(0);
#endif
E 3
	case SLC_RP:
I 3
#ifdef	VREPRINT
		setval(VREPRINT, SLC_VARIABLE);
#else
		defval(0);
#endif
E 3
	case SLC_LNEXT:
I 3
#ifdef	VLNEXT
		setval(VLNEXT, SLC_VARIABLE);
#else
		defval(0);
#endif
	case SLC_AO:
D 7
#ifdef	VFLUSHO
		setval(VFLUSHO, SLC_VARIABLE|SLC_FLUSHOUT);
E 7
I 7
D 8
#ifdef	VDISCARD
		setval(VDISCARD, SLC_VARIABLE|SLC_FLUSHOUT);
E 8
I 8
D 11
#ifdef	VFLUSHO
		setval(VFLUSHO, SLC_VARIABLE|SLC_FLUSHOUT);
E 11
I 11
#if	!defined(VDISCARD) && defined(VFLUSHO)
# define VDISCARD VFLUSHO
#endif
#ifdef	VDISCARD
		setval(VDISCARD, SLC_VARIABLE|SLC_FLUSHOUT);
E 11
E 8
E 7
#else
		defval(0);
#endif
	case SLC_SUSP:
#ifdef	VSUSP
		setval(VSUSP, SLC_VARIABLE|SLC_FLUSHIN);
#else
		defval(0);
#endif
I 5
#ifdef	VEOL
	case SLC_FORW1:
		setval(VEOL, SLC_VARIABLE);
#endif
#ifdef	VEOL2
	case SLC_FORW2:
		setval(VEOL2, SLC_VARIABLE);
#endif
I 11
	case SLC_AYT:
#ifdef	VSTATUS
		setval(VSTATUS, SLC_VARIABLE);
#else
		defval(0);
#endif
E 11
E 5

E 3
	case SLC_BRK:
	case SLC_SYNCH:
D 11
	case SLC_AYT:
E 11
	case SLC_EOR:
D 3
		*valp = 0;
		*valpp = 0;
		return(SLC_DEFAULT);
	case SLC_AO:
	case SLC_SUSP:
E 3
I 3
		defval(0);

E 3
	default:
		*valp = 0;
		*valpp = 0;
		return(SLC_NOSUPPORT);
	}
}
#endif	/* USE_TERMIO */

I 5
#ifdef CRAY
E 5
/*
I 5
 * getnpty()
 *
 * Return the number of pty's configured into the system.
 */
I 13
	int
E 13
getnpty()
{
#ifdef _SC_CRAY_NPTY
D 13
	return sysconf(_SC_CRAY_NPTY);
#else
	return 128;
E 13
I 13
	int numptys;

	if ((numptys = sysconf(_SC_CRAY_NPTY)) != -1)
		return numptys;
	else
E 13
#endif /* _SC_CRAY_NPTY */
I 13
		return 128;
E 13
}
#endif /* CRAY */

I 11
#ifndef	convex
E 11
/*
E 5
 * getpty()
 *
 * Allocate a pty.  As a side effect, the external character
 * array "line" contains the name of the slave side.
 *
 * Returns the file descriptor of the opened pty.
 */
I 11
#ifndef	__GNUC__
E 11
char *line = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
I 11
#else
static char Xline[] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
char *line = Xline;
#endif
#ifdef	CRAY
char *myline = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
#endif	/* CRAY */
E 11

I 13
	int
E 13
D 22
getpty()
E 22
I 22
getpty(ptynum)
int *ptynum;
E 22
{
	register int p;
I 17
#ifdef	STREAMSPTY
	int t;
	char *ptsname();

	p = open("/dev/ptmx", 2);
	if (p > 0) {
		grantpt(p);
		unlockpt(p);
		strcpy(line, ptsname(p));
		return(p);
	}

#else	/* ! STREAMSPTY */
E 17
#ifndef CRAY
D 17
	register char c, *p1, *p2;
E 17
I 17
	register char *cp, *p1, *p2;
E 17
	register int i;
I 17
D 21
#if defined(sun) && defined(TIOCGPGRP)
E 21
I 21
#if defined(sun) && defined(TIOCGPGRP) && BSD < 199207
E 21
	int dummy;
#endif
E 17

I 22
#ifndef	__hpux
E 22
	(void) sprintf(line, "/dev/ptyXX");
	p1 = &line[8];
	p2 = &line[9];
I 22
#else
	(void) sprintf(line, "/dev/ptym/ptyXX");
	p1 = &line[13];
	p2 = &line[14];
#endif
E 22

D 17
	for (c = 'p'; c <= 's'; c++) {
E 17
I 17
	for (cp = "pqrstuvwxyzPQRST"; *cp; cp++) {
E 17
		struct stat stb;

D 17
		*p1 = c;
E 17
I 17
		*p1 = *cp;
E 17
		*p2 = '0';
I 17
		/*
		 * This stat() check is just to keep us from
		 * looping through all 256 combinations if there
		 * aren't that many ptys available.
		 */
E 17
		if (stat(line, &stb) < 0)
			break;
		for (i = 0; i < 16; i++) {
			*p2 = "0123456789abcdef"[i];
			p = open(line, 2);
			if (p > 0) {
I 22
#ifndef	__hpux
E 22
				line[5] = 't';
I 22
#else
				for (p1 = &line[8]; *p1; p1++)
					*p1 = *(p1+1);
				line[9] = 't';
#endif
E 22
D 17
				return(p);
E 17
I 17
				chown(line, 0, 0);
				chmod(line, 0600);
D 21
#if defined(sun) && defined(TIOCGPGRP)
E 21
I 21
#if defined(sun) && defined(TIOCGPGRP) && BSD < 199207
E 21
				if (ioctl(p, TIOCGPGRP, &dummy) == 0
				    || errno != EIO) {
					chmod(line, 0666);
					close(p);
					line[5] = 'p';
				} else
D 21
#endif /* defined(sun) && defined(TIOCGPGRP) */
E 21
I 21
#endif /* defined(sun) && defined(TIOCGPGRP) && BSD < 199207 */
E 21
					return(p);
E 17
			}
		}
	}
#else	/* CRAY */
D 22
	register int npty;
E 22
	extern lowpty, highpty;
I 11
	struct stat sb;
E 11

D 22
	for (npty = lowpty; npty <= highpty; npty++) {
D 11
		(void) sprintf(line, "/dev/pty/%03d", npty);
		p = open(line, 2);
E 11
I 11
		(void) sprintf(myline, "/dev/pty/%03d", npty);
E 22
I 22
	for (*ptynum = lowpty; *ptynum <= highpty; (*ptynum)++) {
		(void) sprintf(myline, "/dev/pty/%03d", *ptynum);
E 22
		p = open(myline, 2);
E 11
		if (p < 0)
			continue;
D 22
		(void) sprintf(line, "/dev/ttyp%03d", npty);
E 22
I 22
		(void) sprintf(line, "/dev/ttyp%03d", *ptynum);
E 22
I 11
		/*
		 * Here are some shenanigans to make sure that there
		 * are no listeners lurking on the line.
		 */
		if(stat(line, &sb) < 0) {
			(void) close(p);
			continue;
		}
		if(sb.st_uid || sb.st_gid || sb.st_mode != 0600) {
			chown(line, 0, 0);
			chmod(line, 0600);
			(void)close(p);
			p = open(myline, 2);
			if (p < 0)
				continue;
		}
		/*
		 * Now it should be safe...check for accessability.
		 */
E 11
		if (access(line, 6) == 0)
			return(p);
		else {
			/* no tty side to pty so skip it */
			(void) close(p);
		}
	}
#endif	/* CRAY */
I 17
#endif	/* STREAMSPTY */
E 17
	return(-1);
}
I 11
#endif	/* convex */
E 11

#ifdef	LINEMODE
/*
 * tty_flowmode()	Find out if flow control is enabled or disabled.
 * tty_linemode()	Find out if linemode (external processing) is enabled.
 * tty_setlinemod(on)	Turn on/off linemode.
 * tty_isecho()		Find out if echoing is turned on.
 * tty_setecho(on)	Enable/disable character echoing.
 * tty_israw()		Find out if terminal is in RAW mode.
 * tty_binaryin(on)	Turn on/off BINARY on input.
 * tty_binaryout(on)	Turn on/off BINARY on output.
 * tty_isediting()	Find out if line editing is enabled.
 * tty_istrapsig()	Find out if signal trapping is enabled.
 * tty_setedit(on)	Turn on/off line editing.
 * tty_setsig(on)	Turn on/off signal trapping.
I 8
 * tty_issofttab()	Find out if tab expansion is enabled.
 * tty_setsofttab(on)	Turn on/off soft tab expansion.
 * tty_islitecho()	Find out if typed control chars are echoed literally
 * tty_setlitecho()	Turn on/off literal echo of control chars
E 8
 * tty_tspeed(val)	Set transmit speed to val.
 * tty_rspeed(val)	Set receive speed to val.
 */

I 13
D 20
	int
E 13
tty_flowmode()
{
#ifndef USE_TERMIO
D 13
	return((termbuf.tc.t_startc) > 0 && (termbuf.tc.t_stopc) > 0);
E 13
I 13
	return(((termbuf.tc.t_startc) > 0 && (termbuf.tc.t_stopc) > 0) ? 1 : 0);
E 13
#else
D 19
	return(termbuf.c_iflag & IXON ? 1 : 0);
E 19
I 19
	return((termbuf.c_iflag & IXON) ? 1 : 0);
E 19
#endif
}

I 17
	int
tty_restartany()
{
#ifndef USE_TERMIO
# ifdef	DECCTQ
	return((termbuf.lflags & DECCTQ) ? 0 : 1);
# else
	return(-1);
# endif
#else
D 19
	return(termbuf.c_iflag & IXANY ? 1 : 0);
E 19
I 19
	return((termbuf.c_iflag & IXANY) ? 1 : 0);
E 19
#endif
}

E 20
E 17
I 11
#ifdef convex
static int linestate;
#endif

I 13
	int
E 13
E 11
tty_linemode()
{
I 11
#ifndef convex
E 11
#ifndef	USE_TERMIO
	return(termbuf.state & TS_EXTPROC);
#else
	return(termbuf.c_lflag & EXTPROC);
#endif
I 11
#else
	return(linestate);
#endif
E 11
}

I 13
	void
E 13
tty_setlinemode(on)
D 13
int on;
E 13
I 13
	int on;
E 13
{
#ifdef	TIOCEXT
I 11
# ifndef convex
	set_termbuf();
# else
	linestate = on;
# endif
E 11
	(void) ioctl(pty, TIOCEXT, (char *)&on);
I 11
# ifndef convex
	init_termbuf();
# endif
E 11
#else	/* !TIOCEXT */
D 11
#ifdef	EXTPROC
E 11
I 11
# ifdef	EXTPROC
E 11
	if (on)
		termbuf.c_lflag |= EXTPROC;
	else
		termbuf.c_lflag &= ~EXTPROC;
D 11
#endif
	set_termbuf();
E 11
I 11
# endif
E 11
#endif	/* TIOCEXT */
}
I 24
#endif	/* LINEMODE */
E 24

I 13
	int
E 13
tty_isecho()
{
#ifndef USE_TERMIO
	return (termbuf.sg.sg_flags & ECHO);
#else
	return (termbuf.c_lflag & ECHO);
#endif
}
D 24
#endif	/* LINEMODE */
E 24
I 20

	int
tty_flowmode()
{
#ifndef USE_TERMIO
	return(((termbuf.tc.t_startc) > 0 && (termbuf.tc.t_stopc) > 0) ? 1 : 0);
#else
	return((termbuf.c_iflag & IXON) ? 1 : 0);
#endif
}

	int
tty_restartany()
{
#ifndef USE_TERMIO
# ifdef	DECCTQ
	return((termbuf.lflags & DECCTQ) ? 0 : 1);
# else
	return(-1);
# endif
#else
	return((termbuf.c_iflag & IXANY) ? 1 : 0);
#endif
}
E 20

I 13
	void
E 13
tty_setecho(on)
I 13
	int on;
E 13
{
#ifndef	USE_TERMIO
	if (on)
		termbuf.sg.sg_flags |= ECHO|CRMOD;
	else
		termbuf.sg.sg_flags &= ~(ECHO|CRMOD);
#else
	if (on)
		termbuf.c_lflag |= ECHO;
	else
		termbuf.c_lflag &= ~ECHO;
#endif
}

D 24
#if	defined(LINEMODE) && defined(KLUDGELINEMODE)
E 24
I 13
	int
E 13
tty_israw()
{
#ifndef USE_TERMIO
	return(termbuf.sg.sg_flags & RAW);
#else
	return(!(termbuf.c_lflag & ICANON));
#endif
}
D 24
#endif	/* defined(LINEMODE) && defined(KLUDGELINEMODE) */
E 24

I 24
#if	defined (AUTHENTICATION) && defined(NO_LOGIN_F) && defined(LOGIN_R)
	int
tty_setraw(on)
{
#  ifndef USE_TERMIO
	if (on)
		termbuf.sg.sg_flags |= RAW;
	else
		termbuf.sg.sg_flags &= ~RAW;
#  else
	if (on)
		termbuf.c_lflag &= ~ICANON;
	else
		termbuf.c_lflag |= ICANON;
#  endif
}
#endif

E 24
I 13
	void
E 13
tty_binaryin(on)
I 13
	int on;
E 13
{
#ifndef	USE_TERMIO
	if (on)
		termbuf.lflags |= LPASS8;
	else
		termbuf.lflags &= ~LPASS8;
#else
	if (on) {
D 13
		termbuf.c_lflag &= ~ISTRIP;
E 13
I 13
		termbuf.c_iflag &= ~ISTRIP;
E 13
	} else {
D 13
		termbuf.c_lflag |= ISTRIP;
E 13
I 13
		termbuf.c_iflag |= ISTRIP;
E 13
	}
#endif
}

I 13
	void
E 13
tty_binaryout(on)
I 13
	int on;
E 13
{
#ifndef	USE_TERMIO
	if (on)
		termbuf.lflags |= LLITOUT;
	else
		termbuf.lflags &= ~LLITOUT;
#else
	if (on) {
		termbuf.c_cflag &= ~(CSIZE|PARENB);
		termbuf.c_cflag |= CS8;
		termbuf.c_oflag &= ~OPOST;
	} else {
		termbuf.c_cflag &= ~CSIZE;
		termbuf.c_cflag |= CS7|PARENB;
		termbuf.c_oflag |= OPOST;
	}
#endif
}

I 13
	int
E 13
tty_isbinaryin()
{
#ifndef	USE_TERMIO
	return(termbuf.lflags & LPASS8);
#else
D 3
	return(!(termbuf.c_lflag & ISTRIP));
E 3
I 3
	return(!(termbuf.c_iflag & ISTRIP));
E 3
#endif
}

I 13
	int
E 13
tty_isbinaryout()
{
#ifndef	USE_TERMIO
	return(termbuf.lflags & LLITOUT);
#else
D 3
	return(mywants[TELOPT_BINARY] == OPT_YES);
E 3
I 3
	return(!(termbuf.c_oflag&OPOST));
E 3
#endif
}

#ifdef	LINEMODE
I 13
	int
E 13
tty_isediting()
{
#ifndef USE_TERMIO
	return(!(termbuf.sg.sg_flags & (CBREAK|RAW)));
#else
	return(termbuf.c_lflag & ICANON);
#endif
}

I 13
	int
E 13
tty_istrapsig()
{
#ifndef USE_TERMIO
	return(!(termbuf.sg.sg_flags&RAW));
#else
	return(termbuf.c_lflag & ISIG);
#endif
}

I 13
	void
E 13
tty_setedit(on)
D 13
int on;
E 13
I 13
	int on;
E 13
{
#ifndef USE_TERMIO
	if (on)
		termbuf.sg.sg_flags &= ~CBREAK;
	else
		termbuf.sg.sg_flags |= CBREAK;
#else
	if (on)
		termbuf.c_lflag |= ICANON;
	else
		termbuf.c_lflag &= ~ICANON;
#endif
}

I 13
	void
E 13
tty_setsig(on)
D 13
int on;
E 13
I 13
	int on;
E 13
{
#ifndef	USE_TERMIO
	if (on)
		;
#else
	if (on)
		termbuf.c_lflag |= ISIG;
	else
		termbuf.c_lflag &= ~ISIG;
#endif
}
#endif	/* LINEMODE */

I 13
	int
E 13
I 8
tty_issofttab()
{
#ifndef	USE_TERMIO
	return (termbuf.sg.sg_flags & XTABS);
#else
# ifdef	OXTABS
	return (termbuf.c_oflag & OXTABS);
# endif
# ifdef	TABDLY
	return ((termbuf.c_oflag & TABDLY) == TAB3);
# endif
#endif
}

I 13
	void
E 13
tty_setsofttab(on)
D 13
int on;
E 13
I 13
	int on;
E 13
{
#ifndef	USE_TERMIO
	if (on)
		termbuf.sg.sg_flags |= XTABS;
	else
		termbuf.sg.sg_flags &= ~XTABS;
#else
	if (on) {
# ifdef	OXTABS
		termbuf.c_oflag |= OXTABS;
# endif
# ifdef	TABDLY
		termbuf.c_oflag &= ~TABDLY;
		termbuf.c_oflag |= TAB3;
# endif
	} else {
# ifdef	OXTABS
		termbuf.c_oflag &= ~OXTABS;
# endif
# ifdef	TABDLY
		termbuf.c_oflag &= ~TABDLY;
		termbuf.c_oflag |= TAB0;
# endif
	}
#endif
}

I 13
	int
E 13
tty_islitecho()
{
#ifndef	USE_TERMIO
D 13
	return (!(termbuf.sg.sg_flags & CTLECH));
E 13
I 13
	return (!(termbuf.lflags & LCTLECH));
E 13
#else
# ifdef	ECHOCTL
	return (!(termbuf.c_lflag & ECHOCTL));
# endif
# ifdef	TCTLECH
	return (!(termbuf.c_lflag & TCTLECH));
# endif
# if	!defined(ECHOCTL) && !defined(TCTLECH)
	return (0);	/* assumes ctl chars are echoed '^x' */
# endif
#endif
}

I 13
	void
E 13
tty_setlitecho(on)
D 13
int on;
E 13
I 13
	int on;
E 13
{
#ifndef	USE_TERMIO
	if (on)
D 13
		termbuf.sg.sg_flags &= ~CTLECH;
E 13
I 13
		termbuf.lflags &= ~LCTLECH;
E 13
	else
D 13
		termbuf.sg.sg_flags |= CTLECH;
E 13
I 13
		termbuf.lflags |= LCTLECH;
E 13
#else
# ifdef	ECHOCTL
	if (on)
		termbuf.c_lflag &= ~ECHOCTL;
	else
		termbuf.c_lflag |= ECHOCTL;
# endif
# ifdef	TCTLECH
	if (on)
		termbuf.c_lflag &= ~TCTLECH;
	else
		termbuf.c_lflag |= TCTLECH;
# endif
#endif
}

I 13
	int
tty_iscrnl()
{
#ifndef	USE_TERMIO
	return (termbuf.sg.sg_flags & CRMOD);
#else
	return (termbuf.c_iflag & ICRNL);
#endif
}

E 13
E 8
/*
I 26
 * Try to guess whether speeds are "encoded" (4.2BSD) or just numeric (4.4BSD).
 */
#if B4800 != 4800
#define	DECODE_BAUD
#endif

#ifdef	DECODE_BAUD

/*
E 26
 * A table of available terminal speeds
 */
struct termspeeds {
	int	speed;
	int	value;
} termspeeds[] = {
D 26
	{ 0,     B0 },    { 50,    B50 },   { 75,    B75 },
	{ 110,   B110 },  { 134,   B134 },  { 150,   B150 },
	{ 200,   B200 },  { 300,   B300 },  { 600,   B600 },
	{ 1200,  B1200 }, { 1800,  B1800 }, { 2400,  B2400 },
	{ 4800,  B4800 }, { 9600,  B9600 }, { 19200, B9600 },
	{ 38400, B9600 }, { -1,    B9600 }
E 26
I 26
	{ 0,      B0 },      { 50,    B50 },    { 75,     B75 },
	{ 110,    B110 },    { 134,   B134 },   { 150,    B150 },
	{ 200,    B200 },    { 300,   B300 },   { 600,    B600 },
	{ 1200,   B1200 },   { 1800,  B1800 },  { 2400,   B2400 },
D 27
	{ 4800,   B4800 },  
E 27
I 27
	{ 4800,   B4800 },
E 27
#ifdef	B7200
D 27
	{ 7200,  B7200 }, 
E 27
I 27
	{ 7200,  B7200 },
E 27
#endif
	{ 9600,   B9600 },
#ifdef	B14400
	{ 14400,  B14400 },
#endif
#ifdef	B19200
	{ 19200,  B19200 },
#endif
#ifdef	B28800
	{ 28800,  B28800 },
#endif
#ifdef	B38400
	{ 38400,  B38400 },
#endif
#ifdef	B57600
	{ 57600,  B57600 },
#endif
#ifdef	B115200
	{ 115200, B115200 },
#endif
#ifdef	B230400
	{ 230400, B230400 },
#endif
	{ -1,     0 }
E 26
};
I 26
#endif	/* DECODE_BUAD */
E 26

I 13
	void
E 13
tty_tspeed(val)
I 13
	int val;
E 13
{
I 26
#ifdef	DECODE_BAUD
E 26
	register struct termspeeds *tp;

	for (tp = termspeeds; (tp->speed != -1) && (val > tp->speed); tp++)
		;
I 26
	if (tp->speed == -1)	/* back up to last valid value */
		--tp;
E 26
D 11
#ifndef	USE_TERMIO
	termbuf.sg.sg_ospeed = tp->value;
#else
D 8
# ifdef	SYSV_TERMIO
E 8
I 8
# ifdef	CBAUD
E 8
	termbuf.c_cflag &= ~CBAUD;
	termbuf.c_cflag |= tp->value;
# else
	termbuf.c_ospeed = tp->value;
# endif
#endif
E 11
I 11
	cfsetospeed(&termbuf, tp->value);
I 26
#else	/* DECODE_BUAD */
	cfsetospeed(&termbuf, val);
#endif	/* DECODE_BUAD */
E 26
E 11
}

I 13
	void
E 13
tty_rspeed(val)
I 13
	int val;
E 13
{
I 26
#ifdef	DECODE_BAUD
E 26
	register struct termspeeds *tp;

	for (tp = termspeeds; (tp->speed != -1) && (val > tp->speed); tp++)
		;
I 26
	if (tp->speed == -1)	/* back up to last valid value */
		--tp;
E 26
D 11
#ifndef	USE_TERMIO
	termbuf.sg.sg_ispeed = tp->value;
#else
D 8
# ifdef	SYSV_TERMIO
E 8
I 8
# ifdef	CBAUD
E 8
	termbuf.c_cflag &= ~CBAUD;
	termbuf.c_cflag |= tp->value;
# else
	termbuf.c_ispeed = tp->value;
# endif
#endif
E 11
I 11
	cfsetispeed(&termbuf, tp->value);
I 26
#else	/* DECODE_BAUD */
	cfsetispeed(&termbuf, val);
#endif	/* DECODE_BAUD */
E 26
E 11
}

D 5
#ifdef	CRAY2
E 5
I 5
#if	defined(CRAY2) && defined(UNICOS5)
I 13
	int
E 13
E 5
tty_isnewmap()
{
	return((termbuf.c_oflag & OPOST) && (termbuf.c_oflag & ONLCR) &&
			!(termbuf.c_oflag & ONLRET));
}
#endif

D 22
#ifdef	CRAY
E 22
I 22
#ifdef PARENT_DOES_UTMP
E 22
# ifndef NEWINIT
extern	struct utmp wtmp;
extern char wtmpf[];
# else	/* NEWINIT */
int	gotalarm;
D 5
nologinproc()
E 5
I 5
D 13
/* ARGSUSED */
void
E 13
I 13

	/* ARGSUSED */
	void
E 13
nologinproc(sig)
D 13
int sig;
E 13
I 13
	int sig;
E 13
E 5
{
	gotalarm++;
}
# endif	/* NEWINIT */
D 22
#endif /* CRAY */
E 22
I 22
#endif /* PARENT_DOES_UTMP */
E 22

I 13
#ifndef	NEWINIT
D 22
# ifdef	CRAY
E 22
I 22
# ifdef PARENT_DOES_UTMP
E 22
extern void utmp_sig_init P((void));
extern void utmp_sig_reset P((void));
extern void utmp_sig_wait P((void));
extern void utmp_sig_notify P((int));
D 22
# endif
E 22
I 22
# endif /* PARENT_DOES_UTMP */
E 22
#endif

E 13
/*
 * getptyslave()
 *
 * Open the slave side of the pty, and do any initialization
 * that is necessary.  The return value is a file descriptor
 * for the slave side.
 */
I 13
	int
E 13
getptyslave()
{
	register int t = -1;

D 11
#ifndef	CRAY
E 11
I 11
#if	!defined(CRAY) || !defined(NEWINIT)
# ifdef	LINEMODE
I 13
	int waslm;
# endif
# ifdef	TIOCGWINSZ
	struct winsize ws;
	extern int def_row, def_col;
# endif
	extern int def_tspeed, def_rspeed;
E 13
E 11
	/*
D 11
	 * Disassociate self from control terminal and open ttyp side.
	 * Set important flags on ttyp and ptyp.
E 11
I 11
	 * Opening the slave side may cause initilization of the
D 13
	 * kernel tty structure.  We need remember whether or not
	 * linemode was turned on, so that we can re-set it if we
	 * need to.
E 13
I 13
	 * kernel tty structure.  We need remember the state of
	 * 	if linemode was turned on
	 *	terminal window size
	 *	terminal speed
	 * so that we can re-set them if we need to.
E 13
E 11
	 */
I 11
D 13
	int waslm = tty_linemode();
E 13
I 13
# ifdef	LINEMODE
	waslm = tty_linemode();
E 13
# endif


	/*
	 * Make sure that we don't have a controlling tty, and
	 * that we are the session (process group) leader.
	 */
# ifdef	TIOCNOTTY
E 11
	t = open(_PATH_TTY, O_RDWR);
	if (t >= 0) {
		(void) ioctl(t, TIOCNOTTY, (char *)0);
		(void) close(t);
	}
I 11
# endif
E 11

D 11
	t = open(line, O_RDWR);
E 11
I 11

D 22
# ifdef	CRAY
E 22
I 22
# ifdef PARENT_DOES_UTMP
E 22
	/*
	 * Wait for our parent to get the utmp stuff to get done.
	 */
	utmp_sig_wait();
# endif

	t = cleanopen(line);
E 11
	if (t < 0)
		fatalperror(net, line);
D 11
	if (fchmod(t, 0))
		fatalperror(net, line);
I 8
#if BSD <= 43
E 8
	(void) signal(SIGHUP, SIG_IGN);
	vhangup();
	(void) signal(SIGHUP, SIG_DFL);
	t = open(line, O_RDWR);
	if (t < 0)
		fatalperror(net, line);
I 8
#endif
E 11
E 8

I 18
#ifdef  STREAMSPTY
E 18
I 17
#ifdef	USE_TERMIO
	ttyfd = t;
#endif
D 18
#ifdef  STREAMSPTY
E 18
D 27
	if (ioctl(t, I_PUSH, "ptem") < 0) 
E 27
I 27
	if (ioctl(t, I_PUSH, "ptem") < 0)
E 27
		fatal(net, "I_PUSH ptem");
	if (ioctl(t, I_PUSH, "ldterm") < 0)
		fatal(net, "I_PUSH ldterm");
	if (ioctl(t, I_PUSH, "ttcompat") < 0)
		fatal(net, "I_PUSH ttcompat");
	if (ioctl(pty, I_PUSH, "pckt") < 0)
		fatal(net, "I_PUSH pckt");
#endif

E 17
I 11
	/*
	 * set up the tty modes as we like them to be.
	 */
E 11
	init_termbuf();
D 11
#ifndef	USE_TERMIO
E 11
I 11
D 13
# ifdef	LINEMODE
	if (waslm)
		tty_setlinemode();
# endif	LINEMODE
E 13
I 13
# ifdef	TIOCGWINSZ
	if (def_row || def_col) {
D 27
		bzero((char *)&ws, sizeof(ws));
E 27
I 27
		memset((char *)&ws, 0, sizeof(ws));
E 27
		ws.ws_col = def_col;
		ws.ws_row = def_row;
		(void)ioctl(t, TIOCSWINSZ, (char *)&ws);
	}
# endif
E 13

	/*
	 * Settings for sgtty based systems
	 */
# ifndef	USE_TERMIO
E 11
D 5
	termbuf.sg.sg_flags |= CRMOD|ANYP|ECHO;
E 5
I 5
	termbuf.sg.sg_flags |= CRMOD|ANYP|ECHO|XTABS;
E 5
D 13
	termbuf.sg.sg_ospeed = termbuf.sg.sg_ispeed = B9600;
E 13
D 11
#else
E 11
I 11
# endif	/* USE_TERMIO */

	/*
D 22
	 * Settings for UNICOS
E 22
I 22
	 * Settings for UNICOS (and HPUX)
E 22
	 */
D 22
# ifdef	CRAY
E 22
I 22
# if defined(CRAY) || defined(__hpux)
E 22
	termbuf.c_oflag = OPOST|ONLCR|TAB3;
	termbuf.c_iflag = IGNPAR|ISTRIP|ICRNL|IXON;
	termbuf.c_lflag = ISIG|ICANON|ECHO|ECHOE|ECHOK;
	termbuf.c_cflag = EXTB|HUPCL|CS8;
# endif

	/*
	 * Settings for all other termios/termio based
	 * systems, other than 4.4BSD.  In 4.4BSD the
	 * kernel does the initial terminal setup.
	 */
D 22
# if defined(USE_TERMIO) && !defined(CRAY) && (BSD <= 43)
E 22
I 22
# if defined(USE_TERMIO) && !(defined(CRAY) || defined(__hpux)) && (BSD <= 43)
E 22
#  ifndef	OXTABS
#   define OXTABS	0
#  endif
E 11
	termbuf.c_lflag |= ECHO;
I 8
D 11
#ifndef	OXTABS
#define OXTABS	0
#endif
E 11
E 8
	termbuf.c_oflag |= ONLCR|OXTABS;
	termbuf.c_iflag |= ICRNL;
	termbuf.c_iflag &= ~IXOFF;
D 8
# ifdef	SYSV_TERMIO
	termbuf.sg.sg_ospeed = termbuf.sg.sg_ispeed = B9600;
# else SYSV_TERMIO
E 8
I 8
D 11
# ifdef	CBAUD
	termbuf.c_cflag &= ~CBAUD;
	termbuf.c_cflag |= B9600;
# else	/* CBAUD */
E 8
	termbuf.c_ospeed = termbuf.c_ispeed = B9600;
D 8
# endif
E 8
I 8
# endif	/* CBAUD */
E 8
#endif
E 11
I 11
D 13
	cfsetospeed(&termbuf, B9600);
	cfsetispeed(&termbuf, B9600);
E 13
# endif /* defined(USE_TERMIO) && !defined(CRAY) && (BSD <= 43) */
I 13
D 14
	cfsetospeed(&termbuf, (def_tspeed == -1) ? B9600 : def_tspeed);
	cfsetispeed(&termbuf, (def_rspeed == -1) ? B9600 : def_rspeed);
E 14
I 14
D 15
	tty_rspeed(def_rspeed);
	tty_tspeed(def_tspeed);
E 15
I 15
	tty_rspeed((def_rspeed > 0) ? def_rspeed : 9600);
	tty_tspeed((def_tspeed > 0) ? def_tspeed : 9600);
E 15
E 14
# ifdef	LINEMODE
	if (waslm)
		tty_setlinemode(1);
# endif	/* LINEMODE */
E 13

	/*
	 * Set the tty modes, and make this our controlling tty.
	 */
E 11
	set_termbuf();
D 11
#else	/* CRAY */
E 11
I 11
	if (login_tty(t) == -1)
		fatalperror(net, "login_tty");
#endif	/* !defined(CRAY) || !defined(NEWINIT) */
	if (net > 2)
		(void) close(net);
D 24
	if (pty > 2)
E 24
I 24
#if	defined(AUTHENTICATION) && defined(NO_LOGIN_F) && defined(LOGIN_R)
	/*
	 * Leave the pty open so that we can write out the rlogin
	 * protocol for /bin/login, if the authentication works.
	 */
#else
	if (pty > 2) {
E 24
		(void) close(pty);
I 24
		pty = -1;
	}
#endif
E 24
}

#if	!defined(CRAY) || !defined(NEWINIT)
#ifndef	O_NOCTTY
#define	O_NOCTTY	0
#endif
/*
 * Open the specified slave side of the pty,
 * making sure that we have a clean tty.
 */
I 13
	int
E 13
cleanopen(line)
D 13
char *line;
E 13
I 13
	char *line;
E 13
{
	register int t;
I 17
D 27
#if	defined(_SC_CRAY_SECURE_SYS)
E 27
I 27
#ifdef	UNICOS7x
E 27
	struct secstat secbuf;
D 27
#endif	/* _SC_CRAY_SECURE_SYS */
E 27
I 27
#endif	/* UNICOS7x */
E 27
E 17

I 17
#ifndef STREAMSPTY
E 17
	/*
	 * Make sure that other people can't open the
	 * slave side of the connection.
	 */
E 11
	(void) chown(line, 0, 0);
	(void) chmod(line, 0600);
I 17
#endif
E 17
D 11
#endif	/* CRAY */
E 11
I 11

# if !defined(CRAY) && (BSD > 43)
	(void) revoke(line);
# endif
I 17
D 27
#if	defined(_SC_CRAY_SECURE_SYS)
E 27
I 27
#ifdef	UNICOS7x
E 27
	if (secflag) {
		if (secstat(line, &secbuf) < 0)
			return(-1);
		if (setulvl(secbuf.st_slevel) < 0)
			return(-1);
		if (setucmp(secbuf.st_compart) < 0)
			return(-1);
	}
D 27
#endif	/* _SC_CRAY_SECURE_SYS */
E 27
I 27
#endif	/* UNICOS7x */
E 27

E 17
	t = open(line, O_RDWR|O_NOCTTY);
I 17

D 27
#if	defined(_SC_CRAY_SECURE_SYS)
E 27
I 27
#ifdef	UNICOS7x
E 27
	if (secflag) {
		if (setulvl(sysv.sy_minlvl) < 0)
			return(-1);
		if (setucmp(0) < 0)
			return(-1);
	}
D 27
#endif	/* _SC_CRAY_SECURE_SYS */
E 27
I 27
#endif	/* UNICOS7x */
E 27

E 17
	if (t < 0)
		return(-1);

	/*
	 * Hangup anybody else using this ttyp, then reopen it for
	 * ourselves.
	 */
D 17
# if !defined(CRAY) && (BSD <= 43)
E 17
I 17
D 22
# if !defined(CRAY) && (BSD <= 43) && !defined(STREAMSPTY)
E 22
I 22
# if !(defined(CRAY) || defined(__hpux)) && (BSD <= 43) && !defined(STREAMSPTY)
E 22
E 17
	(void) signal(SIGHUP, SIG_IGN);
	vhangup();
	(void) signal(SIGHUP, SIG_DFL);
	t = open(line, O_RDWR|O_NOCTTY);
	if (t < 0)
		return(-1);
# endif
# if	defined(CRAY) && defined(TCVHUP)
	{
		register int i;
		(void) signal(SIGHUP, SIG_IGN);
		(void) ioctl(t, TCVHUP, (char *)0);
		(void) signal(SIGHUP, SIG_DFL);
D 27
		setpgrp();
E 27
I 17

D 27
#if		defined(_SC_CRAY_SECURE_SYS)
E 27
I 27
#ifdef	UNICOS7x
E 27
		if (secflag) {
			if (secstat(line, &secbuf) < 0)
				return(-1);
			if (setulvl(secbuf.st_slevel) < 0)
				return(-1);
			if (setucmp(secbuf.st_compart) < 0)
				return(-1);
		}
D 27
#endif		/* _SC_CRAY_SECURE_SYS */
E 27
I 27
#endif	/* UNICOS7x */
E 27

E 17
		i = open(line, O_RDWR);
I 17

D 27
#if		defined(_SC_CRAY_SECURE_SYS)
E 27
I 27
#ifdef	UNICOS7x
E 27
		if (secflag) {
			if (setulvl(sysv.sy_minlvl) < 0)
				return(-1);
			if (setucmp(0) < 0)
				return(-1);
		}
D 27
#endif		/* _SC_CRAY_SECURE_SYS */
E 27
I 27
#endif	/* UNICOS7x */
E 27

E 17
		if (i < 0)
D 13
			return(-1)
E 13
I 13
			return(-1);
E 13
		(void) close(t);
		t = i;
	}
# endif	/* defined(CRAY) && defined(TCVHUP) */
E 11
	return(t);
}
I 11
#endif	/* !defined(CRAY) || !defined(NEWINIT) */
E 11

I 11
#if BSD <= 43
I 24

E 24
I 13
	int
E 13
login_tty(t)
D 13
int t;
E 13
I 13
	int t;
E 13
{
D 13
# ifndef NO_SETSID
E 13
D 24
	if (setsid() < 0)
		fatalperror(net, "setsid()");
E 24
I 24
	if (setsid() < 0) {
#ifdef ultrix
		/*
		 * The setsid() may have failed because we
		 * already have a pgrp == pid.  Zero out
		 * our pgrp and try again...
		 */
		if ((setpgrp(0, 0) < 0) || (setsid() < 0))
#endif
			fatalperror(net, "setsid()");
	}
E 24
D 13
# else
#  ifndef convex
	if (setpgrp(0,0) < 0)
		fatalperror(net, "setpgrp()");
#  endif
# endif
E 13
# ifdef	TIOCSCTTY
	if (ioctl(t, TIOCSCTTY, (char *)0) < 0)
		fatalperror(net, "ioctl(sctty)");
I 16
D 17
#  if defined(CRAY) && defined(SESS_CTTY)	/* SESS_CTTY is in param.h */
E 17
I 17
#  if defined(CRAY)
E 17
	/*
	 * Close the hard fd to /dev/ttypXXX, and re-open through
	 * the indirect /dev/tty interface.
	 */
	close(t);
	if ((t = open("/dev/tty", O_RDWR)) < 0)
		fatalperror(net, "open(/dev/tty)");
#  endif
E 16
# else
I 24
	/*
	 * We get our controlling tty assigned as a side-effect
	 * of opening up a tty device.  But on BSD based systems,
	 * this only happens if our process group is zero.  The
	 * setsid() call above may have set our pgrp, so clear
	 * it out before opening the tty...
	 */
I 27
#  ifndef SOLARIS
E 27
	(void) setpgrp(0, 0);
I 27
#  else
	(void) setpgrp();
#  endif
E 27
E 24
	close(open(line, O_RDWR));
# endif
D 16
	(void) dup2(t, 0);
	(void) dup2(t, 1);
	(void) dup2(t, 2);
	close(t);
E 16
I 16
	if (t != 0)
		(void) dup2(t, 0);
	if (t != 1)
		(void) dup2(t, 1);
	if (t != 2)
		(void) dup2(t, 2);
	if (t > 2)
		close(t);
E 16
I 13
	return(0);
E 13
}
#endif	/* BSD <= 43 */

E 11
#ifdef	NEWINIT
char *gen_id = "fe";
#endif

/*
D 11
 * startslave(t, host)
E 11
I 11
 * startslave(host)
E 11
 *
D 11
 * Given a file descriptor (t) for a tty, and a hostname, do whatever
E 11
I 11
 * Given a hostname, do whatever
E 11
 * is necessary to startup the login process on the slave side of the pty.
 */

/* ARGSUSED */
D 11
startslave(t, host)
int t;
E 11
I 11
D 13
startslave(host)
E 11
char *host;
E 13
I 13
	void
startslave(host, autologin, autoname)
	char *host;
	int autologin;
	char *autoname;
E 13
{
	register int i;
	long time();
I 13
	char name[256];
#ifdef	NEWINIT
	extern char *ptyip;
	struct init_request request;
	void nologinproc();
	register int n;
#endif	/* NEWINIT */
E 13

I 13
D 17
#if	defined(AUTHENTICATE)
E 17
I 17
#if	defined(AUTHENTICATION)
E 17
	if (!autoname || !autoname[0])
		autologin = 0;

	if (autologin < auth_level) {
		fatal(net, "Authorization failed");
		exit(1);
	}
#endif

E 13
#ifndef	NEWINIT
D 22
# ifdef	CRAY
E 22
I 22
# ifdef	PARENT_DOES_UTMP
E 22
	utmp_sig_init();
D 22
# endif	/* CRAY */
E 22
I 22
# endif	/* PARENT_DOES_UTMP */
E 22

	if ((i = fork()) < 0)
		fatalperror(net, "fork");
	if (i) {
D 22
# ifdef	CRAY
E 22
I 22
# ifdef PARENT_DOES_UTMP
E 22
		/*
		 * Cray parent will create utmp entry for child and send
		 * signal to child to tell when done.  Child waits for signal
		 * before doing anything important.
		 */
		register int pid = i;
I 13
		void sigjob P((int));
E 13

		setpgrp();
D 8
		(void) signal(SIGUSR1, func);	/* reset handler to default */
E 8
I 8
		utmp_sig_reset();		/* reset handler to default */
E 8
		/*
		 * Create utmp entry for child
		 */
		(void) time(&wtmp.ut_time);
		wtmp.ut_type = LOGIN_PROCESS;
		wtmp.ut_pid = pid;
		SCPYN(wtmp.ut_user, "LOGIN");
		SCPYN(wtmp.ut_host, host);
		SCPYN(wtmp.ut_line, line + sizeof("/dev/") - 1);
I 22
#ifndef	__hpux
E 22
		SCPYN(wtmp.ut_id, wtmp.ut_line+3);
I 22
#else
		SCPYN(wtmp.ut_id, wtmp.ut_line+7);
#endif
E 22
		pututline(&wtmp);
		endutent();
		if ((i = open(wtmpf, O_WRONLY|O_APPEND)) >= 0) {
			(void) write(i, (char *)&wtmp, sizeof(struct utmp));
			(void) close(i);
		}
I 22
#ifdef	CRAY
E 22
I 13
		(void) signal(WJSIGNAL, sigjob);
I 22
#endif
E 22
E 13
		utmp_sig_notify(pid);
D 22
# endif	/* CRAY */
E 22
I 22
# endif	/* PARENT_DOES_UTMP */
E 22
D 11
		(void) close(t);
E 11
	} else {
D 11
		start_login(t, host);
E 11
I 11
D 24
		getptyslave();
E 24
I 24
		getptyslave(autologin);
E 24
D 13
		start_login(host);
E 13
I 13
		start_login(host, autologin, autoname);
E 13
E 11
		/*NOTREACHED*/
	}
#else	/* NEWINIT */

D 13
	extern char *ptyip;
	struct init_request request;
D 5
	int nologinproc();
E 5
I 5
	void nologinproc();
E 5
	register int n;

E 13
	/*
	 * Init will start up login process if we ask nicely.  We only wait
	 * for it to start up and begin normal telnet operation.
	 */
	if ((i = open(INIT_FIFO, O_WRONLY)) < 0) {
		char tbuf[128];
		(void) sprintf(tbuf, "Can't open %s\n", INIT_FIFO);
		fatalperror(net, tbuf);
	}
	memset((char *)&request, 0, sizeof(request));
	request.magic = INIT_MAGIC;
	SCPYN(request.gen_id, gen_id);
	SCPYN(request.tty_id, &line[8]);
	SCPYN(request.host, host);
D 8
	SCPYN(request.term_type, &terminaltype[5]);
I 5
#if	defined(UNICOS5)
E 8
I 8
D 13
	SCPYN(request.term_type, terminaltype);
E 13
I 13
	SCPYN(request.term_type, terminaltype ? terminaltype : "network");
E 13
#if	!defined(UNICOS5)
E 8
	request.signal = SIGCLD;
	request.pid = getpid();
#endif
I 8
#ifdef BFTPDAEMON
	/*
	 * Are we working as the bftp daemon?
	 */
	if (bftpd) {
		SCPYN(request.exec_name, BFTPPATH);
	}
#endif /* BFTPDAEMON */
E 8
E 5
	if (write(i, (char *)&request, sizeof(request)) < 0) {
		char tbuf[128];
		(void) sprintf(tbuf, "Can't write to %s\n", INIT_FIFO);
		fatalperror(net, tbuf);
	}
	(void) close(i);
	(void) signal(SIGALRM, nologinproc);
	for (i = 0; ; i++) {
I 5
		char tbuf[128];
E 5
		alarm(15);
		n = read(pty, ptyip, BUFSIZ);
		if (i == 3 || n >= 0 || !gotalarm)
			break;
		gotalarm = 0;
D 5
		(void) write(net, "telnetd: waiting for /etc/init to start login process.\r\n", 56);
E 5
I 5
		sprintf(tbuf, "telnetd: waiting for /etc/init to start login process on %s\r\n", line);
		(void) write(net, tbuf, strlen(tbuf));
E 5
	}
	if (n < 0 && gotalarm)
		fatal(net, "/etc/init didn't start login process");
	pcc += n;
	alarm(0);
	(void) signal(SIGALRM, SIG_DFL);

D 5
	/*
	 * Set tab expansion the way we like, in case init did something
	 * different.
	 */
	init_termbuf();
	termbuf.c_oflag &= ~TABDLY;
	termbuf.c_oflag |= TAB0;
	set_termbuf();
E 5
	return;
#endif	/* NEWINIT */
}

D 8
#ifndef	NEWINIT
E 8
char	*envinit[3];
I 8
extern char **environ;
E 8

I 13
	void
E 13
I 8
init_env()
{
	extern char *getenv();
	char **envp;

	envp = envinit;
	if (*envp = getenv("TZ"))
		*envp++ -= 3;
D 22
#ifdef	CRAY
E 22
I 22
#if	defined(CRAY) || defined(__hpux)
E 22
	else
		*envp++ = "TZ=GMT0";
#endif
	*envp = 0;
	environ = envinit;
}

D 13
#ifdef	CRAY
E 8
/*
I 8
 * These are environment variable that we
 * don't put on the argument line.
 */
char *invalid[] = {
	"USER=",	/* Set up by login */
	"HOME=",	/* Set up by login */
	"LOGNAME=",	/* Set up by login */
	"TMPDIR=",	/* Set up by login */
	"SHELL=",	/* Set up by login */
	"PATH=",	/* Set up by login */
	"MAIL=",	/* Set up by login */
	"TZ=",		/* Login gets it from the environment */
	"TERM=",	/* Login gets it from the environment */
	0
};
#endif

E 13
#ifndef	NEWINIT

/*
E 8
D 11
 * start_login(t, host)
E 11
I 11
 * start_login(host)
E 11
 *
 * Assuming that we are now running as a child processes, this
 * function will turn us into the login process.
 */

D 11
start_login(t, host)
int t;
E 11
I 11
D 13
start_login(host)
E 11
char *host;
E 13
I 13
	void
start_login(host, autologin, name)
	char *host;
	int autologin;
	char *name;
E 13
{
D 8
	extern char *getenv();
	char **envp;

E 8
I 8
	register char *cp;
	register char **argv;
	char **addarg();
I 24
	extern char *getenv();
E 24
I 17
#ifdef	UTMPX
	register int pid = getpid();
	struct utmpx utmpx;
#endif
D 24
#ifdef __svr4__
E 24
I 24
#ifdef SOLARIS
E 24
	char *term;
	char termbuf[64];
#endif
E 17
E 8
D 13
#ifdef	CRAY
I 8
	register char **cpp, **cpp2;
E 8
D 11
	utmp_sig_wait();
# ifndef TCVHUP
	setpgrp();
# endif
	t = open(line, 2);	/* open ttyp */
	if (t < 0)
		fatalperror(net, line);
# ifdef	TCVHUP
	/*
	 * Hangup anybody else using this ttyp, then reopen it for
	 * ourselves.
	 */
	(void) chown(line, 0, 0);
	(void) chmod(line, 0600);
	(void) signal(SIGHUP, SIG_IGN);
	(void) ioctl(t, TCVHUP, (char *)0);
	(void) signal(SIGHUP, SIG_DFL);
	setpgrp();
	i = open(line, 2);
	if (i < 0)
		fatalperror(net, line);
	(void) close(t);
	t = i;
# endif	/* TCVHUP */
	/*
	 * set ttyp modes as we like them to be
	 */
	init_termbuf();
D 5
	termbuf.c_oflag = OPOST|ONLCR;
E 5
I 5
	termbuf.c_oflag = OPOST|ONLCR|TAB3;
E 5
	termbuf.c_iflag = IGNPAR|ISTRIP|ICRNL|IXON;
	termbuf.c_lflag = ISIG|ICANON|ECHO|ECHOE|ECHOK;
	termbuf.c_cflag = EXTB|HUPCL|CS8;
	set_termbuf();
E 11
#endif	/* CRAY */
E 13

I 17
#ifdef	UTMPX
E 17
	/*
I 17
	 * Create utmp entry for child
	 */

D 27
	bzero(&utmpx, sizeof(utmpx));
E 27
I 27
	memset(&utmpx, 0, sizeof(utmpx));
E 27
	SCPYN(utmpx.ut_user, ".telnet");
	SCPYN(utmpx.ut_line, line + sizeof("/dev/") - 1);
	utmpx.ut_pid = pid;
	utmpx.ut_id[0] = 't';
	utmpx.ut_id[1] = 'n';
	utmpx.ut_id[2] = SC_WILDC;
	utmpx.ut_id[3] = SC_WILDC;
	utmpx.ut_type = LOGIN_PROCESS;
	(void) time(&utmpx.ut_tv.tv_sec);
D 26
	if (makeutx(&utmpx) == NULL)
		fatal(net, "makeutx failed");
E 26
I 26
	if (pututxline(&utmpx) == NULL)
		fatal(net, "pututxline failed");
E 26
#endif

	/*
E 17
D 11
	 * set up standard paths before forking to login
	 */
D 2
#ifdef	BSD >43
E 2
I 2
D 8
#if	BSD >43
E 8
I 8
D 9
#ifndef	NO_SETSID
E 8
E 2
	if (setsid() < 0)
		fatalperror(net, "setsid");
I 8
#endif

#ifdef	TIOCSCTTY
E 8
	if (ioctl(t, TIOCSCTTY, (char *)0) < 0)
		fatalperror(net, "ioctl(sctty)");
#endif
	(void) close(net);
	(void) close(pty);
E 9
I 9
#if BSD > 43
	if (login_tty(t) == -1)
		fatalperror(net, "login_tty");
#else
E 9
	(void) dup2(t, 0);
	(void) dup2(t, 1);
	(void) dup2(t, 2);
	(void) close(t);
I 9
#endif
	if (net > 2)
		(void) close(net);
	if (pty > 2)
		(void) close(pty);
E 9
D 8
	envp = envinit;
	*envp++ = terminaltype;
	if (*envp = getenv("TZ"))
		*envp++ -= 3;
#ifdef	CRAY
	else
		*envp++ = "TZ=GMT0";
#endif
	*envp = 0;
	environ = envinit;
E 8
	/*
E 11
	 * -h : pass on name of host.
	 *		WARNING:  -h is accepted by login if and only if
	 *			getuid() == 0.
	 * -p : don't clobber the environment (so terminal type stays set).
I 13
	 *
	 * -f : force this login, he has already been authenticated
E 13
	 */
D 8
	execl(_PATH_LOGIN, "login", "-h", host,
#ifndef CRAY
					terminaltype ? "-p" : 0,
E 8
I 8
	argv = addarg(0, "login");
I 24

E 24
I 22
#if	!defined(NO_LOGIN_H)
E 22
D 24
	argv = addarg(argv, "-h");
	argv = addarg(argv, host);
I 22
#endif
E 22
I 17
#ifdef	__svr4__
E 24
I 24

# if	defined (AUTHENTICATION) && defined(NO_LOGIN_F) && defined(LOGIN_R)
E 24
	/*
D 24
	 * SVR4 version of -h takes TERM= as second arg, or -
E 24
I 24
	 * Don't add the "-h host" option if we are going
	 * to be adding the "-r host" option down below...
E 24
	 */
D 24
	term = getenv("TERM");
	if (term == NULL || term[0] == 0) {
		term = "-";
	} else {
		strcpy(termbuf, "TERM=");
		strncat(termbuf, term, sizeof(termbuf) - 6);
		term = termbuf;
E 24
I 24
	if ((auth_level < 0) || (autologin != AUTH_VALID))
# endif
	{
		argv = addarg(argv, "-h");
		argv = addarg(argv, host);
#ifdef	SOLARIS
		/*
		 * SVR4 version of -h takes TERM= as second arg, or -
		 */
		term = getenv("TERM");
		if (term == NULL || term[0] == 0) {
			term = "-";
		} else {
			strcpy(termbuf, "TERM=");
			strncat(termbuf, term, sizeof(termbuf) - 6);
			term = termbuf;
		}
		argv = addarg(argv, term);
#endif
E 24
	}
D 24
	argv = addarg(argv, term);
E 24
#endif
E 17
D 13
#if	!defined(CRAY) && !defined(NO_LOGIN_P)
E 13
I 13
#if	!defined(NO_LOGIN_P)
E 13
	argv = addarg(argv, "-p");
E 8
#endif
I 27
#ifdef	LINEMODE
	/*
	 * Set the environment variable "LINEMODE" to either
	 * "real" or "kludge" if we are operating in either
	 * real or kludge linemode.
	 */
	if (lmodetype == REAL_LINEMODE)
		setenv("LINEMODE", "real", 1);
# ifdef KLUDGELINEMODE
	else if (lmodetype == KLUDGE_LINEMODE || lmodetype == KLUDGE_OK)
		setenv("LINEMODE", "kludge", 1);
# endif
#endif
E 27
D 8
								0);
E 8
I 8
#ifdef	BFTPDAEMON
	/*
	 * Are we working as the bftp daemon?  If so, then ask login
	 * to start bftp instead of shell.
	 */
	if (bftpd) {
		argv = addarg(argv, "-e");
		argv = addarg(argv, BFTPPATH);
D 27
	} else 
E 27
I 27
	} else
E 27
#endif
I 13
#if	defined (SecurID)
	/*
	 * don't worry about the -f that might get sent.
	 * A -s is supposed to override it anyhow.
	 */
	if (require_SecurID)
		argv = addarg(argv, "-s");
#endif
D 17
#if	defined (AUTHENTICATE)
E 17
I 17
#if	defined (AUTHENTICATION)
E 17
	if (auth_level >= 0 && autologin == AUTH_VALID) {
# if	!defined(NO_LOGIN_F)
		argv = addarg(argv, "-f");
I 24
		argv = addarg(argv, name);
# else
#  if defined(LOGIN_R)
		/*
		 * We don't have support for "login -f", but we
		 * can fool /bin/login into thinking that we are
		 * rlogind, and allow us to log in without a
		 * password.  The rlogin protocol expects
		 *	local-user\0remote-user\0term/speed\0
		 */

		if (pty > 2) {
			register char *cp;
			char speed[128];
			int isecho, israw, xpty, len;
			extern int def_rspeed;
#  ifndef LOGIN_HOST
			/*
			 * Tell login that we are coming from "localhost".
			 * If we passed in the real host name, then the
			 * user would have to allow .rhost access from
			 * every machine that they want authenticated
			 * access to work from, which sort of defeats
			 * the purpose of an authenticated login...
			 * So, we tell login that the session is coming
			 * from "localhost", and the user will only have
			 * to have "localhost" in their .rhost file.
			 */
#			define LOGIN_HOST "localhost"
#  endif
			argv = addarg(argv, "-r");
			argv = addarg(argv, LOGIN_HOST);

			xpty = pty;
# ifndef  STREAMSPTY
			pty = 0;
# else
			ttyfd = 0;
E 24
# endif
I 24
			init_termbuf();
			isecho = tty_isecho();
			israw = tty_israw();
			if (isecho || !israw) {
				tty_setecho(0);		/* Turn off echo */
				tty_setraw(1);		/* Turn on raw */
				set_termbuf();
			}
			len = strlen(name)+1;
			write(xpty, name, len);
			write(xpty, name, len);
			sprintf(speed, "%s/%d", (cp = getenv("TERM")) ? cp : "",
				(def_rspeed > 0) ? def_rspeed : 9600);
			len = strlen(speed)+1;
			write(xpty, speed, len);

			if (isecho || !israw) {
				init_termbuf();
				tty_setecho(isecho);
				tty_setraw(israw);
				set_termbuf();
				if (!israw) {
					/*
					 * Write a newline to ensure
					 * that login will be able to
					 * read the line...
					 */
					write(xpty, "\n", 1);
				}
			}
			pty = xpty;
		}
#  else
E 24
		argv = addarg(argv, name);
I 24
#  endif
# endif
E 24
	} else
#endif
E 13
	if (getenv("USER")) {
		argv = addarg(argv, getenv("USER"));
D 13
	}
#ifdef	CRAY
	for (cpp = environ; *cpp; cpp++) {
		for (cpp2 = invalid; *cpp2; cpp2++)
			if (strncmp(*cpp2, *cpp, strlen(*cpp2)) == 0)
				break;
		if (*cpp2)
			continue;
		argv = addarg(argv, *cpp);
	}
E 13
I 13
D 22
#if	defined(CRAY) && defined(NO_LOGIN_P)
E 22
I 22
D 24
#if	(defined(CRAY) || defined(__hpux)) && defined(NO_LOGIN_P)
E 24
I 24
#if	defined(LOGIN_ARGS) && defined(NO_LOGIN_P)
E 24
E 22
		{
			register char **cpp;
			for (cpp = environ; *cpp; cpp++)
				argv = addarg(argv, *cpp);
		}
E 13
#endif
I 17
		/*
		 * Assume that login will set the USER variable
		 * correctly.  For SysV systems, this means that
		 * USER will no longer be set, just LOGNAME by
		 * login.  (The problem is that if the auto-login
		 * fails, and the user then specifies a different
		 * account name, he can get logged in with both
		 * LOGNAME and USER in his environment, but the
		 * USER value will be wrong.
		 */
		unsetenv("USER");
E 17
D 13

E 13
I 13
	}
I 26
#ifdef	SOLARIS
	else {
		char **p;
D 27
 
E 27
I 27

E 27
		argv = addarg(argv, "");	/* no login name */
		for (p = environ; *p; p++) {
			argv = addarg(argv, *p);
		}
	}
#endif	/* SOLARIS */
E 26
I 24
#if	defined(AUTHENTICATION) && defined(NO_LOGIN_F) && defined(LOGIN_R)
	if (pty > 2)
		close(pty);
#endif
E 24
	closelog();
I 26
	/*
	 * This sleep(1) is in here so that telnetd can
	 * finish up with the tty.  There's a race condition
	 * the login banner message gets lost...
	 */
	sleep(1);
E 26
E 13
	execv(_PATH_LOGIN, argv);

E 8
	syslog(LOG_ERR, "%s: %m\n", _PATH_LOGIN);
	fatalperror(net, _PATH_LOGIN);
	/*NOTREACHED*/
}
I 8

D 13
char **
E 13
I 13
	char **
E 13
addarg(argv, val)
D 13
register char **argv;
register char *val;
E 13
I 13
	register char **argv;
	register char *val;
E 13
{
	register char **cpp;
D 13
	char *malloc();
E 13

	if (argv == NULL) {
		/*
		 * 10 entries, a leading length, and a null
		 */
		argv = (char **)malloc(sizeof(*argv) * 12);
		if (argv == NULL)
			return(NULL);
		*argv++ = (char *)10;
		*argv = (char *)0;
	}
	for (cpp = argv; *cpp; cpp++)
		;
	if (cpp == &argv[(int)argv[-1]]) {
		--argv;
		*argv = (char *)((int)(*argv) + 10);
D 26
		argv = (char **)realloc(argv, (int)(*argv) + 2);
E 26
I 26
		argv = (char **)realloc(argv, sizeof(*argv)*((int)(*argv) + 2));
E 26
		if (argv == NULL)
			return(NULL);
		argv++;
		cpp = &argv[(int)argv[-1] - 10];
	}
	*cpp++ = val;
	*cpp = 0;
	return(argv);
}
E 8
D 13
#endif	NEWINIT
E 13
I 13
#endif	/* NEWINIT */
E 13

/*
 * cleanup()
 *
 * This is the routine to call when we are all through, to
 * clean up anything that needs to be cleaned up.
 */
I 11
D 13
void
E 11
cleanup()
E 13
I 13
	/* ARGSUSED */
	void
cleanup(sig)
	int sig;
E 13
{
D 13

E 13
D 22
#ifndef	CRAY
E 22
I 22
#ifndef	PARENT_DOES_UTMP
E 22
D 11
# if BSD > 43
E 11
I 11
# if (BSD > 43) || defined(convex)
E 11
	char *p;

	p = line + sizeof("/dev/") - 1;
	if (logout(p))
		logwtmp(p, "", "");
	(void)chmod(line, 0666);
	(void)chown(line, 0, 0);
	*p = 'p';
	(void)chmod(line, 0666);
	(void)chown(line, 0, 0);
I 13
	(void) shutdown(net, 2);
	exit(1);
E 13
# else
I 13
	void rmut();

E 13
	rmut();
	vhangup();	/* XXX */
D 13
# endif
E 13
	(void) shutdown(net, 2);
I 13
	exit(1);
# endif
E 13
D 22
#else	/* CRAY */
E 22
I 22
#else	/* PARENT_DOES_UTMP */
E 22
D 13
# ifndef NEWINIT
	rmut(line);
E 13
I 13
# ifdef	NEWINIT
E 13
	(void) shutdown(net, 2);
D 13
	kill(0, SIGHUP);
E 13
I 13
	exit(1);
E 13
# else	/* NEWINIT */
I 22
#  ifdef CRAY
E 22
I 13
	static int incleanup = 0;
	register int t;
I 27
	int child_status; /* status of child process as returned by waitpid */
	int flags = WNOHANG|WUNTRACED;
E 27

	/*
	 * 1: Pick up the zombie, if we are being called
	 *    as the signal handler.
	 * 2: If we are a nested cleanup(), return.
	 * 3: Try to clean up TMPDIR.
	 * 4: Fill in utmp with shutdown of process.
	 * 5: Close down the network and pty connections.
	 * 6: Finish up the TMPDIR cleanup, if needed.
	 */
D 27
	if (sig == SIGCHLD)
		while (waitpid(-1, 0, WNOHANG) > 0)
E 27
I 27
	if (sig == SIGCHLD) {
		while (waitpid(-1, &child_status, flags) > 0)
E 27
			;	/* VOID */
I 27
		/* Check if the child process was stopped
		 * rather than exited.  We want cleanup only if
		 * the child has died.
		 */
		if (WIFSTOPPED(child_status)) {
			return;
		}
	}
E 27
	t = sigblock(sigmask(SIGCHLD));
	if (incleanup) {
		sigsetmask(t);
		return;
	}
	incleanup = 1;
	sigsetmask(t);
I 27
#ifdef	UNICOS7x
E 27
I 22
	if (secflag) {
		/*
		 *	We need to set ourselves back to a null
		 *	label to clean up.
		 */
E 22

I 22
		setulvl(sysv.sy_minlvl);
		setucmp((long)0);
	}
I 27
#endif	/* UNICOS7x */
E 27

E 22
	t = cleantmp(&wtmp);
	setutent();	/* just to make sure */
I 22
#  endif /* CRAY */
E 22
	rmut(line);
	close(pty);
E 13
	(void) shutdown(net, 2);
I 22
#  ifdef CRAY
E 22
I 13
	if (t == 0)
		cleantmp(&wtmp);
I 22
#  endif /* CRAY */
E 22
	exit(1);
E 13
D 5
	sleep(5);
E 5
I 5
D 8
	sleep(2);
E 8
E 5
# endif	/* NEWINT */
D 22
#endif	/* CRAY */
E 22
I 22
#endif	/* PARENT_DOES_UTMP */
E 22
D 13
	exit(1);
E 13
}

D 22
#if	defined(CRAY) && !defined(NEWINIT)
E 22
I 22
#if defined(PARENT_DOES_UTMP) && !defined(NEWINIT)
E 22
/*
 * _utmp_sig_rcv
 * utmp_sig_init
 * utmp_sig_wait
 *	These three functions are used to coordinate the handling of
 *	the utmp file between the server and the soon-to-be-login shell.
 *	The server actually creates the utmp structure, the child calls
 *	utmp_sig_wait(), until the server calls utmp_sig_notify() and
 *	signals the future-login shell to proceed.
 */
static int caught=0;		/* NZ when signal intercepted */
static void (*func)();		/* address of previous handler */

D 13
void
E 13
I 13
	void
E 13
_utmp_sig_rcv(sig)
D 13
int sig;
E 13
I 13
	int sig;
E 13
{
	caught = 1;
	(void) signal(SIGUSR1, func);
}

I 13
	void
E 13
utmp_sig_init()
{
	/*
	 * register signal handler for UTMP creation
	 */
	if ((int)(func = signal(SIGUSR1, _utmp_sig_rcv)) == -1)
		fatalperror(net, "telnetd/signal");
I 8
}

I 13
	void
E 13
utmp_sig_reset()
{
	(void) signal(SIGUSR1, func);	/* reset handler to default */
E 8
}

I 22
# ifdef __hpux
# define sigoff() /* do nothing */
# define sigon() /* do nothing */
# endif

E 22
I 13
	void
E 13
utmp_sig_wait()
{
	/*
	 * Wait for parent to write our utmp entry.
	 */
	sigoff();
	while (caught == 0) {
		pause();	/* wait until we get a signal (sigon) */
		sigoff();	/* turn off signals while we check caught */
	}
	sigon();		/* turn on signals again */
}

I 13
	void
E 13
utmp_sig_notify(pid)
{
	kill(pid, SIGUSR1);
}
I 13

I 22
# ifdef CRAY
E 22
static int gotsigjob = 0;

	/*ARGSUSED*/
	void
sigjob(sig)
	int sig;
{
	register int jid;
	register struct jobtemp *jp;

	while ((jid = waitjob(NULL)) != -1) {
		if (jid == 0) {
			return;
		}
		gotsigjob++;
		jobend(jid, NULL, NULL);
	}
}

/*
I 27
 *	jid_getutid:
 *		called by jobend() before calling cleantmp()
 *		to find the correct $TMPDIR to cleanup.
 */

	struct utmp *
jid_getutid(jid)
	int jid;
{
	struct utmp *cur = NULL;

	setutent();	/* just to make sure */
	while (cur = getutent()) {
		if ( (cur->ut_type != NULL) && (jid == cur->ut_jid) ) {
			return(cur);
		}
	}

	return(0);
}

/*
E 27
 * Clean up the TMPDIR that login created.
 * The first time this is called we pick up the info
 * from the utmp.  If the job has already gone away,
 * then we'll clean up and be done.  If not, then
 * when this is called the second time it will wait
 * for the signal that the job is done.
 */
	int
cleantmp(wtp)
	register struct utmp *wtp;
{
	struct utmp *utp;
	static int first = 1;
	register int mask, omask, ret;
D 24
	extern struct utmp *getutid P((struct utmp *));
E 24
I 24
	extern struct utmp *getutid P((const struct utmp *_Id));
E 24

I 24

E 24
	mask = sigmask(WJSIGNAL);

	if (first == 0) {
		omask = sigblock(mask);
		while (gotsigjob == 0)
			sigpause(omask);
		return(1);
	}
	first = 0;
	setutent();	/* just to make sure */

	utp = getutid(wtp);
	if (utp == 0) {
		syslog(LOG_ERR, "Can't get /etc/utmp entry to clean TMPDIR");
		return(-1);
	}
	/*
	 * Nothing to clean up if the user shell was never started.
	 */
	if (utp->ut_type != USER_PROCESS || utp->ut_jid == 0)
		return(1);

	/*
	 * Block the WJSIGNAL while we are in jobend().
	 */
	omask = sigblock(mask);
	ret = jobend(utp->ut_jid, utp->ut_tpath, utp->ut_user);
	sigsetmask(omask);
	return(ret);
}

	int
jobend(jid, path, user)
	register int jid;
	register char *path;
	register char *user;
{
	static int saved_jid = 0;
I 27
	static int pty_saved_jid = 0;
E 27
	static char saved_path[sizeof(wtmp.ut_tpath)+1];
	static char saved_user[sizeof(wtmp.ut_user)+1];

I 27
	/*
	 * this little piece of code comes into play
	 * only when ptyreconnect is used to reconnect
	 * to an previous session.
	 *
	 * this is the only time when the
	 * "saved_jid != jid" code is executed.
	 */

	if ( saved_jid && saved_jid != jid ) {
		if (!path) {	/* called from signal handler */
			pty_saved_jid = jid;
		} else {
			pty_saved_jid = saved_jid;
		}
	}

E 27
	if (path) {
		strncpy(saved_path, path, sizeof(wtmp.ut_tpath));
		strncpy(saved_user, user, sizeof(wtmp.ut_user));
		saved_path[sizeof(saved_path)] = '\0';
		saved_user[sizeof(saved_user)] = '\0';
	}
	if (saved_jid == 0) {
		saved_jid = jid;
		return(0);
	}
I 27

	/* if the jid has changed, get the correct entry from the utmp file */

	if ( saved_jid != jid ) {
		struct utmp *utp = NULL;
		struct utmp *jid_getutid();

		utp = jid_getutid(pty_saved_jid);

		if (utp == 0) {
			syslog(LOG_ERR, "Can't get /etc/utmp entry to clean TMPDIR");
			return(-1);
		}

		cleantmpdir(jid, utp->ut_tpath, utp->ut_user);
		return(1);
	}

E 27
	cleantmpdir(jid, saved_path, saved_user);
	return(1);
}

/*
 * Fork a child process to clean up the TMPDIR
 */
cleantmpdir(jid, tpath, user)
	register int jid;
	register char *tpath;
	register char *user;
{
	switch(fork()) {
	case -1:
		syslog(LOG_ERR, "TMPDIR cleanup(%s): fork() failed: %m\n",
							tpath);
		break;
	case 0:
		execl(CLEANTMPCMD, CLEANTMPCMD, user, tpath, 0);
		syslog(LOG_ERR, "TMPDIR cleanup(%s): execl(%s) failed: %m\n",
							tpath, CLEANTMPCMD);
		exit(1);
	default:
		/*
		 * Forget about child.  We will exit, and
		 * /etc/init will pick it up.
		 */
		break;
	}
}
E 13
D 22
#endif	/* defined(CRAY) && !defined(NEWINIT) */
E 22
I 22
# endif /* CRAY */
#endif	/* defined(PARENT_DOES_UTMP) && !defined(NEWINIT) */
E 22

/*
 * rmut()
 *
 * This is the function called by cleanup() to
 * remove the utmp entry for this person.
 */

D 17
#if	!defined(CRAY) && BSD <= 43
E 17
I 17
#ifdef	UTMPX
I 24
	void
E 24
rmut()
{
	register f;
	int found = 0;
	struct utmp *u, *utmp;
	int nutmp;
	struct stat statbf;

	struct utmpx *utxp, utmpx;

	/*
	 * This updates the utmpx and utmp entries and make a wtmp/x entry
	 */

	SCPYN(utmpx.ut_line, line + sizeof("/dev/") - 1);
	utxp = getutxline(&utmpx);
	if (utxp) {
		utxp->ut_type = DEAD_PROCESS;
		utxp->ut_exit.e_termination = 0;
		utxp->ut_exit.e_exit = 0;
		(void) time(&utmpx.ut_tv.tv_sec);
		utmpx.ut_tv.tv_usec = 0;
		modutx(utxp);
	}
	endutxent();
}  /* end of rmut */
#endif

D 22
#if	!defined(UTMPX) && !defined(CRAY) && BSD <= 43
E 22
I 22
#if	!defined(UTMPX) && !(defined(CRAY) || defined(__hpux)) && BSD <= 43
E 22
E 17
I 13
	void
E 13
rmut()
{
	register f;
	int found = 0;
	struct utmp *u, *utmp;
	int nutmp;
	struct stat statbf;
D 13
	char *malloc();
	long time();
	off_t lseek();
E 13

	f = open(utmpf, O_RDWR);
	if (f >= 0) {
		(void) fstat(f, &statbf);
		utmp = (struct utmp *)malloc((unsigned)statbf.st_size);
		if (!utmp)
			syslog(LOG_ERR, "utmp malloc failed");
		if (statbf.st_size && utmp) {
			nutmp = read(f, (char *)utmp, (int)statbf.st_size);
			nutmp /= sizeof(struct utmp);
D 27
		
E 27
I 27

E 27
			for (u = utmp ; u < &utmp[nutmp] ; u++) {
				if (SCMPN(u->ut_line, line+5) ||
				    u->ut_name[0]==0)
					continue;
				(void) lseek(f, ((long)u)-((long)utmp), L_SET);
				SCPYN(u->ut_name, "");
				SCPYN(u->ut_host, "");
				(void) time(&u->ut_time);
				(void) write(f, (char *)u, sizeof(wtmp));
				found++;
			}
		}
		(void) close(f);
	}
	if (found) {
		f = open(wtmpf, O_WRONLY|O_APPEND);
		if (f >= 0) {
			SCPYN(wtmp.ut_line, line+5);
			SCPYN(wtmp.ut_name, "");
			SCPYN(wtmp.ut_host, "");
			(void) time(&wtmp.ut_time);
			(void) write(f, (char *)&wtmp, sizeof(wtmp));
			(void) close(f);
		}
	}
	(void) chmod(line, 0666);
	(void) chown(line, 0, 0);
	line[strlen("/dev/")] = 'p';
	(void) chmod(line, 0666);
	(void) chown(line, 0, 0);
}  /* end of rmut */
#endif	/* CRAY */
I 22

#ifdef __hpux
rmut (line)
char *line;
{
	struct utmp utmp;
	struct utmp *utptr;
	int fd;			/* for /etc/wtmp */

	utmp.ut_type = USER_PROCESS;
	(void) strncpy(utmp.ut_id, line+12, sizeof(utmp.ut_id));
	(void) setutent();
	utptr = getutid(&utmp);
	/* write it out only if it exists */
	if (utptr) {
		utptr->ut_type = DEAD_PROCESS;
		utptr->ut_time = time((long *) 0);
		(void) pututline(utptr);
		/* set wtmp entry if wtmp file exists */
		if ((fd = open(wtmpf, O_WRONLY | O_APPEND)) >= 0) {
			(void) write(fd, utptr, sizeof(utmp));
			(void) close(fd);
		}
	}
	(void) endutent();

	(void) chmod(line, 0666);
	(void) chown(line, 0, 0);
	line[14] = line[13];
	line[13] = line[12];
	line[8] = 'm';
	line[9] = '/';
	line[10] = 'p';
	line[11] = 't';
	line[12] = 'y';
	(void) chmod(line, 0666);
	(void) chown(line, 0, 0);
}
#endif
E 22
E 1
