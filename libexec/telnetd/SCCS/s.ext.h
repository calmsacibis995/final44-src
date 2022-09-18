h35254
s 00002/00001/00212
d D 8.2 93/12/15 11:39:56 dab 12 11
c A bunch of bugfixes.
c Support for Solaris.
c new LOGIN_R option for systems that
c don't have "login -f".
c Support for the new ENVIRON option.
e
s 00002/00002/00211
d D 8.1 93/06/04 19:06:54 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00003/00208
d D 5.10 93/05/20 11:38:08 dab 10 9
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
s 00001/00000/00210
d D 5.9 93/04/05 16:48:27 dab 9 8
c Fix gcc2 warnings.
c Add ENV_HACK stuff to deal with telnet clients that
c have the wrong definitions for ENV_VAR and ENV_VALUE.
c Fix up the flow-control processing to work on systems
c that don't use Linemode in the server.
e
s 00019/00007/00191
d D 5.8 92/12/18 14:05:53 dab 8 7
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Add Sun/SVR4 Streams support
c Allow for more ptys
c Environ suboption USERVAR support
c New Telnet Flowcontrol suboption support
c Server -k option to default to no kludge linemode
c Server -U option, allow only registered hosts to connect
e
s 00108/00002/00090
d D 5.7 91/03/01 01:35:11 dab 7 6
c Telnet AUTHENTICATION option
c Telnet ENCRYPT option (test version)
c Function prototypes
c Bug fixes and code cleanup
e
s 00014/00004/00078
d D 5.6 90/06/28 13:06:01 borman 6 5
c Lots of bugfixes, add the ENVIRON and X-DISPLAY-LOC
c options, "-l user" to the command line, diagnostic flags.
e
s 00001/00011/00081
d D 5.5 90/06/01 15:55:34 bostic 5 4
c new copyright notice
e
s 00002/00002/00090
d D 5.4 90/02/28 15:35:48 borman 4 3
c Many fixes.  1) Use the cc_t typedef from termios.h
c 2) Fix for SYSV VEOF/VMIN overlap
c 3) Add two missing "break" statements
c 4) Add SLC_FORW[12] support
c 5) start of TOS support
c 6) Make sure things get initialized properly
c 7) Don't send Urgent mode data, since some clients go into infinate loops...
e
s 00005/00000/00087
d D 5.3 89/11/14 10:43:46 borman 3 2
c Bug fixes to the state machine
e
s 00002/00001/00085
d D 5.2 89/11/10 10:22:40 borman 2 1
c Fix bugs in state machine, add more TERMIOS support
e
s 00086/00000/00000
d D 5.1 89/09/01 15:17:48 borman 1 0
c New telnetd, with LINEMODE support
e
u
U
t
T
I 1
/*
D 11
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
D 5
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Telnet server variable declarations
 */
D 6
extern char	hisopts[256];
extern char	myopts[256];
extern char	hiswants[256];
extern char	mywants[256];
E 6
I 6
extern char	options[256];
E 6
D 2
extern char	resp[256];
E 2
I 2
extern char	do_dont_resp[256];
extern char	will_wont_resp[256];
E 2
extern int	linemode;	/* linemode on/off */
#ifdef	LINEMODE
extern int	uselinemode;	/* what linemode to use (on/off) */
extern int	editmode;	/* edit modes in use */
extern int	useeditmode;	/* edit modes to use */
extern int	alwayslinemode;	/* command line option */
# ifdef	KLUDGELINEMODE
extern int	lmodetype;	/* Client support for linemode */
# endif	/* KLUDGELINEMODE */
#endif	/* LINEMODE */
extern int	flowmode;	/* current flow control state */
I 8
extern int	restartany;	/* restart output on any character state */
E 8
I 6
#ifdef DIAGNOSTICS
extern int	diagnostic;	/* telnet diagnostic capabilities */
#endif /* DIAGNOSTICS */
#ifdef BFTPDAEMON
extern int	bftpd;		/* behave as bftp daemon */
#endif /* BFTPDAEMON */
I 7
#if	defined(SecurID)
extern int	require_SecurID;
#endif
D 8
#if	defined(AUTHENTICATE)
E 8
I 8
#if	defined(AUTHENTICATION)
E 8
extern int	auth_level;
#endif
E 7
E 6

extern slcfun	slctab[NSLC + 1];	/* slc mapping table */

char	*terminaltype;

/*
 * I/O data buffers, pointers, and counters.
 */
extern char	ptyobuf[BUFSIZ+NETSLOP], *pfrontp, *pbackp;

extern char	netibuf[BUFSIZ], *netip;

extern char	netobuf[BUFSIZ+NETSLOP], *nfrontp, *nbackp;
extern char	*neturg;		/* one past last bye of urgent data */

extern int	pcc, ncc;

I 3
D 4
#ifdef CRAY2
E 4
I 4
#if defined(CRAY2) && defined(UNICOS5)
E 4
extern int unpcc;  /* characters left unprocessed by CRAY-2 terminal routine */
extern char *unptyip;  /* pointer to remaining characters in buffer */
#endif

E 3
extern int	pty, net;
extern char	*line;
extern int	SYNCHing;		/* we are in TELNET SYNCH mode */

I 7
#ifndef	P
# ifdef	__STDC__
#  define P(x)	x
# else
#  define P(x)	()
# endif
#endif

extern void
	_termstat P((void)),
	add_slc P((int, int, int)),
	check_slc P((void)),
	change_slc P((int, int, int)),
	cleanup P((int)),
	clientstat P((int, int, int)),
	copy_termbuf P((char *, int)),
	deferslc P((void)),
	defer_terminit P((void)),
	do_opt_slc P((unsigned char *, int)),
	doeof P((void)),
	dooption P((int)),
	dontoption P((int)),
	edithost P((char *, char *)),
	fatal P((int, char *)),
	fatalperror P((int, char *)),
	get_slc_defaults P((void)),
	init_env P((void)),
	init_termbuf P((void)),
	interrupt P((void)),
	localstat P((void)),
I 9
	flowstat P((void)),
E 9
	netclear P((void)),
	netflush P((void)),
E 7
I 6
#ifdef DIAGNOSTICS
D 7
extern void printoption();
extern void printdata();
E 7
I 7
	printoption P((char *, int)),
	printdata P((char *, char *, int)),
	printsub P((int, unsigned char *, int)),
E 7
#endif
I 7
	ptyflush P((void)),
	putchr P((int)),
	putf P((char *, char *)),
	recv_ayt P((void)),
	send_do P((int, int)),
	send_dont P((int, int)),
	send_slc P((void)),
	send_status P((void)),
	send_will P((int, int)),
	send_wont P((int, int)),
	sendbrk P((void)),
	sendsusp P((void)),
	set_termbuf P((void)),
	start_login P((char *, int, char *)),
	start_slc P((int)),
D 8
#if	defined(AUTHENTICATE)
E 8
I 8
#if	defined(AUTHENTICATION)
E 8
	start_slave P((char *)),
#else
	start_slave P((char *, int, char *)),
#endif
	suboption P((void)),
	telrcv P((void)),
	ttloop P((void)),
	tty_binaryin P((int)),
	tty_binaryout P((int));

extern int
	end_slc P((unsigned char **)),
	getnpty P((void)),
D 10
	getpty P((void)),
E 10
I 10
#ifndef convex
	getpty P((int *)),
D 12
#endif convex
E 12
I 12
#endif
E 12
E 10
	login_tty P((int)),
	spcset P((int, cc_t *, cc_t **)),
	stilloob P((int)),
	terminit P((void)),
	termstat P((void)),
	tty_flowmode P((void)),
I 8
	tty_restartany P((void)),
E 8
	tty_isbinaryin P((void)),
	tty_isbinaryout P((void)),
	tty_iscrnl P((void)),
	tty_isecho P((void)),
	tty_isediting P((void)),
	tty_islitecho P((void)),
	tty_isnewmap P((void)),
	tty_israw P((void)),
	tty_issofttab P((void)),
	tty_istrapsig P((void)),
	tty_linemode P((void));

extern void
	tty_rspeed P((int)),
	tty_setecho P((int)),
	tty_setedit P((int)),
	tty_setlinemode P((int)),
	tty_setlitecho P((int)),
	tty_setsig P((int)),
	tty_setsofttab P((int)),
	tty_tspeed P((int)),
	willoption P((int)),
	wontoption P((int)),
	writenet P((unsigned char *, int));

D 8
#if	defined(ENCRYPT)
E 8
I 8
D 10
#if	defined(ENCRYPTION)
E 10
I 10
#ifdef	ENCRYPTION
E 10
E 8
extern void	(*encrypt_output) P((unsigned char *, int));
extern int	(*decrypt_input) P((int));
extern char	*nclearto;
D 10
#endif
E 10
I 10
#endif	/* ENCRYPTION */
E 10

E 7

E 6
/*
 * The following are some clocks used to decide how to interpret
 * the relationship between various variables.
 */

extern struct {
    int
	system,			/* what the current time is */
	echotoggle,		/* last time user entered echo character */
	modenegotiated,		/* last time operating mode negotiated */
	didnetreceive,		/* last time we read data from network */
	ttypesubopt,		/* ttype subopt is received */
	tspeedsubopt,		/* tspeed subopt is received */
I 6
	environsubopt,		/* environ subopt is received */
I 12
	oenvironsubopt,		/* old environ subopt is received */
E 12
	xdisplocsubopt,		/* xdisploc subopt is received */
E 6
	baseline,		/* time started to do timed action */
	gotDM;			/* when did we last see a data mark */
} clocks;


D 4
#ifdef CRAY2
E 4
I 4
#if	defined(CRAY2) && defined(UNICOS5)
E 4
extern int	needtermstat;
#endif

D 8
#ifndef	CRAY
#define DEFAULT_IM	"\r\n\r\n4.3 BSD UNIX (%h) (%t)\r\n\r\r\n\r"
#else
#define DEFAULT_IM	"\r\n\r\nCray UNICOS (%h) (%t)\r\n\r\r\n\r"
E 8
I 8
#ifndef	DEFAULT_IM
# ifdef CRAY
#  define DEFAULT_IM	"\r\n\r\nCray UNICOS (%h) (%t)\r\n\r\r\n\r"
# else
#  ifdef sun
#   define DEFAULT_IM	"\r\n\r\nSunOS UNIX (%h) (%t)\r\n\r\r\n\r"
#  else
#   ifdef ultrix
#    define DEFAULT_IM	"\r\n\r\nULTRIX (%h) (%t)\r\n\r\r\n\r"
#   else
#    define DEFAULT_IM	"\r\n\r\n4.4 BSD UNIX (%h) (%t)\r\n\r\r\n\r"
#   endif
#  endif
# endif
E 8
#endif
E 1
