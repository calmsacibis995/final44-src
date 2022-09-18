h21083
s 00007/00007/00289
d D 8.3 95/05/30 20:57:09 dab 25 24
c code cleanup, change b*() calls to mem*() calls
e
s 00045/00002/00251
d D 8.2 93/12/15 11:35:57 dab 24 23
c Add support for new ENVIRON command.
c Latest Kerberos V code from MIT (includes new
c options '-f' and '-F' to control the forwarding
c of credentials.)  Various bugfixes to keep some
c C compilers happy.
e
s 00005/00005/00248
d D 8.1 93/06/06 16:33:03 bostic 23 22
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00010/00243
d D 5.6 93/05/20 10:49:30 dab 22 20
c Mostly, this changes all the "#if defined(ENCRYPTION)"
c lines to "#ifdef ENCRYPTION".  This will allow unifdef
c to be used to strip out the encryption code for
c foreign exports.  This also fixes up the usage statement.
e
s 00010/00010/00243
d R 5.6 93/05/20 10:37:21 dab 21 20
c Mostly this changes "#if defined(ENCRYPTION)" to
c "#ifdef ENCRYPTION".  This will allow unifdef to be
e
s 00008/00008/00245
d D 5.5 92/12/18 14:06:50 dab 20 19
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Add Sun/SVR4 Streams support
c Allow for more ptys
c Environ suboption USERVAR support
c New Telnet Flowcontrol suboption support
c Server -k option to default to no kludge linemode
c Server -U option, allow only registered hosts to connect
e
s 00005/00001/00248
d D 5.4 91/03/22 13:08:41 dab 19 18
c Upgrade to the latest & greatest authentication/encryption
e
s 00018/00001/00231
d D 5.3 91/03/01 02:59:14 dab 18 17
c Add -S option (type of service)
e
s 00087/00017/00145
d D 5.2 91/03/01 01:31:58 dab 17 16
c Telnet AUTHENTICATION option
c Telnet ENCRYPT option (test version)
c Function prototypes
e
s 00026/00012/00136
d D 5.1 90/09/14 10:48:52 borman 16 15
c Latest batch of changes.  See the README file
c for a list of all the changes to telnet & telnetd.
e
s 00104/00092/00044
d D 1.15 90/07/27 23:28:35 karels 15 14
c change USER-passing to happen only if -a or -l user specified
c (still not quite right, "open -l name" defines USER=name and exports);
c use current user id if different than login name; getopting and reformatting
c of main.c by bostic
e
s 00018/00001/00118
d D 1.14 90/06/28 12:58:26 borman 14 13
c Lots of bugfixes, add the ENVIRON and X-DISPLAY-LOC
c options, "-l user" to the command line, diagnostic flags.
e
s 00001/00011/00118
d D 1.13 90/06/01 17:45:22 bostic 13 12
c new copyright notice
e
s 00001/00001/00128
d D 1.12 89/11/14 10:20:24 borman 12 11
c Latest & greatest version of telnet
e
s 00006/00006/00123
d D 1.11 89/08/21 14:58:41 borman 11 10
c Add support for LINEMODE option
e
s 00006/00001/00123
d D 1.10 88/11/18 22:30:59 minshall 10 9
c Count SIGIO's (for debugging).  Separate out noasynch between
c tty and net.
e
s 00001/00001/00123
d D 1.9 88/09/26 13:26:07 mckusick 9 8
c process -t option argument properly for tn3270 (4.3BSD-tahoe/ucb/24)
e
s 00010/00005/00114
d D 1.8 88/06/29 20:15:20 bostic 8 7
c install approved copyright notice
e
s 00007/00003/00112
d D 1.7 88/06/27 22:19:39 minshall 7 6
c Fix up lint errors.
e
s 00002/00000/00113
d D 1.6 88/05/15 12:46:54 minshall 6 5
c Make tn3270 work.
e
s 00022/00000/00091
d D 1.5 88/03/08 10:30:51 bostic 5 4
c add Berkeley specific copyright
e
s 00002/00000/00089
d D 1.4 87/10/23 15:15:36 minshall 4 3
c Try to move system dependent stuff to system dependent files.
e
s 00004/00000/00085
d D 1.3 87/10/10 14:27:12 minshall 3 2
c This is the first version to get near rings.  It compiles,
c but doesn't work.
e
s 00000/00012/00085
d D 1.2 87/09/25 14:47:28 minshall 2 1
c The right things in the right place.
e
s 00097/00000/00000
d D 1.1 87/09/11 15:40:39 minshall 1 0
c date and time created 87/09/11 15:40:39 by minshall
e
u
U
t
T
I 5
/*
D 15
 * Copyright (c) 1988 Regents of the University of California.
E 15
I 15
D 23
 * Copyright (c) 1988, 1990 Regents of the University of California.
E 15
 * All rights reserved.
E 23
I 23
 * Copyright (c) 1988, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 23
 *
D 13
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 8
I 8
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
E 13
I 13
 * %sccs.include.redist.c%
E 13
E 8
 */

#ifndef lint
D 23
char copyright[] =
D 15
"%Z% Copyright (c) 1988 Regents of the University of California.\n\
E 15
I 15
"%Z% Copyright (c) 1988, 1990 Regents of the University of California.\n\
E 15
 All rights reserved.\n";
E 23
I 23
static char copyright[] =
"%Z% Copyright (c) 1988, 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 23
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 5
I 3
#include <sys/types.h>
I 16
D 17
#if	defined(unix)
#include <strings.h>
#else	/* defined(unix) */
E 16
I 15
#include <string.h>
I 16
#endif	/* defined(unix) */
E 17
E 16
E 15

#include "ring.h"
D 15

E 15
E 3
I 1
#include "externs.h"
#include "defines.h"

I 24
/* These values need to be the same as defined in libtelnet/kerberos5.c */
/* Either define them in both places, or put in some common header file. */
D 25
#define OPTS_FORWARD_CREDS           0x00000002
#define OPTS_FORWARDABLE_CREDS       0x00000001
E 25
I 25
#define OPTS_FORWARD_CREDS	0x00000002
#define OPTS_FORWARDABLE_CREDS	0x00000001
E 25

#if 0
#define FORWARD
#endif

E 24
/*
 * Initialize variables.
 */
D 15

E 15
D 17
void
E 17
I 17
    void
E 17
tninit()
{
D 2
#if	defined(TN3270)
    Sent3270TerminalType = 0;
    Ifrontp = Ibackp = Ibuf;
#endif	/* defined(TN3270) */

E 2
D 15
    init_terminal();

    init_network();
    
    init_telnet();
I 4

    init_sys();
I 6

    init_3270();
E 15
I 15
D 16
	init_terminal();
	init_network();
	init_telnet();
	init_sys();
	init_3270();
E 16
I 16
    init_terminal();

    init_network();
D 25
    
E 25
I 25

E 25
    init_telnet();

    init_sys();

#if defined(TN3270)
    init_3270();
#endif
E 16
E 15
E 6
E 4
D 2

#if	defined(TN3270)
    init_ctlr();		/* Initialize some things */
    init_keyboard();
    init_screen();
    init_system();
#endif	/* defined(TN3270) */
E 2
}

I 15
D 17
int	autologin;
E 17
I 17
	void
usage()
{
	fprintf(stderr, "Usage: %s %s%s%s%s\n",
	    prompt,
D 20
#ifdef	AUTHENTICATE
E 20
I 20
#ifdef	AUTHENTICATION
E 20
D 22
	    " [-8] [-E] [-K] [-L] [-X atype] [-a] [-d] [-e char] [-k realm]",
	    "\n\t[-l user] [-n tracefile] ",
E 22
I 22
	    "[-8] [-E] [-K] [-L] [-S tos] [-X atype] [-a] [-c] [-d] [-e char]",
D 24
	    "\n\t[-k realm] [-l user] [-n tracefile] ",
E 24
I 24
	    "\n\t[-k realm] [-l user] [-f/-F] [-n tracefile] ",
E 24
E 22
#else
D 22
	    " [-8] [-E] [-L] [-a] [-d] [-e char] [-l user] [-n tracefile]",
	    "\n\t",
E 22
I 22
	    "[-8] [-E] [-L] [-S tos] [-a] [-c] [-d] [-e char] [-l user]",
	    "\n\t[-n tracefile]",
E 22
#endif
#if defined(TN3270) && defined(unix)
D 20
# ifdef AUTHENTICATE
E 20
I 20
# ifdef AUTHENTICATION
E 20
D 22
	    "[-noasynch] [-noasynctty] [-noasyncnet]\n\t[-r] [-t transcom] ",
E 22
I 22
	    "[-noasynch] [-noasynctty]\n\t[-noasyncnet] [-r] [-t transcom] ",
E 22
# else
D 22
	    "[-noasynch] [-noasynctty] [-noasyncnet] [-r] [-t transcom]\n\t",
E 22
I 22
	    "[-noasynch] [-noasynctty] [-noasyncnet] [-r]\n\t[-t transcom]",
E 22
# endif
#else
	    "[-r] ",
#endif
D 20
#ifdef	ENCRYPT
E 20
I 20
#ifdef	ENCRYPTION
E 20
	    "[-x] [host-name [port]]"
D 22
#else
E 22
I 22
#else	/* ENCRYPTION */
E 22
	    "[host-name [port]]"
D 22
#endif
E 22
I 22
#endif	/* ENCRYPTION */
E 22
	);
	exit(1);
}
E 17
E 15

/*
 * main.  Parse arguments, invoke the protocol or command parser.
 */
I 16


E 16
D 15


D 7
void
E 7
I 7
int
E 15
E 7
main(argc, argv)
	int argc;
	char *argv[];
{
I 14
D 15
    char *user = 0;
E 15
I 15
	extern char *optarg;
	extern int optind;
	int ch;
D 16
	char *user;
E 16
I 16
	char *user, *strrchr();
I 24
#ifdef	FORWARD
	extern int forward_flags;
#endif	/* FORWARD */
E 24
E 16
E 15

E 14
D 15
    tninit();		/* Clear out things */
I 11
#ifdef	CRAY
    _setlist_init();	/* Work around compiler bug */
E 15
I 15
	tninit();		/* Clear out things */
D 16
#ifdef CRAY
E 16
I 16
#if	defined(CRAY) && !defined(__STDC__)
E 16
	_setlist_init();	/* Work around compiler bug */
E 15
#endif
I 16

E 16
I 15
	TerminalSaveState();
E 15
E 11

D 15
    TerminalSaveState();
E 15
I 15
D 16
	if (prompt = rindex(argv[0], '/'))
E 16
I 16
	if (prompt = strrchr(argv[0], '/'))
E 16
		++prompt;
	else
		prompt = argv[0];
E 15

D 12
    prompt = argv[0];
E 12
I 12
D 14
    prompt = (unsigned char *)argv[0];
E 14
I 14
D 15
    prompt = argv[0];
E 14
E 12
    while ((argc > 1) && (argv[1][0] == '-')) {
	if (!strcmp(argv[1], "-d")) {
	    debug = 1;
	} else if (!strcmp(argv[1], "-n")) {
	    if ((argc > 1) && (argv[2][0] != '-')) {	/* get file name */
D 11
		NetTrace = fopen(argv[2], "w");
E 11
I 11
		SetNetTrace(argv[2]);
E 11
		argv++;
		argc--;
D 11
		if (NetTrace == NULL) {
		    NetTrace = stdout;
		}
E 11
	    }
I 14
	} else if (!strcmp(argv[1], "-l")) {
	    if ((argc > 1) && (argv[2][0] != '-')) {	/* get user name */
		user = argv[2];
		argv++;
		argc--;
	    }
	} else if (!strncmp(argv[1], "-e", 2)) {
		set_escape_char(&argv[1][2]);
E 14
	} else {
#if	defined(TN3270) && defined(unix)
	    if (!strcmp(argv[1], "-t")) {
		if ((argc > 1) && (argv[2][0] != '-')) { /* get file name */
		    transcom = tline;
D 9
		    (void) strcpy(transcom, argv[1]);
E 9
I 9
		    (void) strcpy(transcom, argv[2]);
E 9
		    argv++;
		    argc--;
		}
	    } else if (!strcmp(argv[1], "-noasynch")) {
D 10
		noasynch = 1;
E 10
I 10
		noasynchtty = 1;
		noasynchnet = 1;
	    } else if (!strcmp(argv[1], "-noasynchtty")) {
		noasynchtty = 1;
	    } else if (!strcmp(argv[1], "-noasynchnet")) {
		noasynchnet = 1;
E 10
	    } else
E 15
I 15
	user = NULL;
D 17
	autologin = 0;
D 16
	while ((ch = getopt(argc, argv, "ade:l:n:")) != EOF)
E 16
I 16
	while ((ch = getopt(argc, argv, "ade:l:n:")) != EOF) {
E 17
I 17

	rlogin = (strncmp(prompt, "rlog", 4) == 0) ? '~' : _POSIX_VDISABLE;
	autologin = -1;

D 18
	while ((ch = getopt(argc, argv, "8EKLX:ade:k:l:n:rt:x")) != EOF) {
E 18
I 18
D 20
	while ((ch = getopt(argc, argv, "8EKLS:X:ade:k:l:n:rt:x")) != EOF) {
E 20
I 20
D 24
	while ((ch = getopt(argc, argv, "8EKLS:X:acde:k:l:n:rt:x")) != EOF) {
E 24
I 24
	while ((ch = getopt(argc, argv, "8EKLS:X:acde:fFk:l:n:rt:x")) != EOF) {
E 24
E 20
E 18
E 17
E 16
		switch(ch) {
I 17
		case '8':
			eight = 3;	/* binary output and input */
			break;
		case 'E':
			rlogin = escape = _POSIX_VDISABLE;
			break;
		case 'K':
D 20
#ifdef	AUTHENTICATE
E 20
I 20
#ifdef	AUTHENTICATION
E 20
			autologin = 0;
#endif
			break;
		case 'L':
			eight |= 2;	/* binary output only */
I 18
			break;
		case 'S':
		    {
#ifdef	HAS_GETTOS
			extern int tos;

			if ((tos = parsetos(optarg, "tcp")) < 0)
				fprintf(stderr, "%s%s%s%s\n",
					prompt, ": Bad TOS argument '",
					optarg,
					"; will try to use default TOS");
#else
			fprintf(stderr,
			   "%s: Warning: -S ignored, no parsetos() support.\n",
								prompt);
#endif
		    }
E 18
			break;
		case 'X':
D 20
#ifdef	AUTHENTICATE
E 20
I 20
#ifdef	AUTHENTICATION
E 20
			auth_disable_name(optarg);
#endif
			break;
E 17
		case 'a':
			autologin = 1;
			break;
I 19
		case 'c':
			skiprc = 1;
			break;
E 19
		case 'd':
			debug = 1;
			break;
		case 'e':
			set_escape_char(optarg);
I 24
			break;
		case 'f':
#if defined(AUTHENTICATION) && defined(KRB5) && defined(FORWARD)
			if (forward_flags & OPTS_FORWARD_CREDS) {
D 25
			    fprintf(stderr, 
E 25
I 25
			    fprintf(stderr,
E 25
				    "%s: Only one of -f and -F allowed.\n",
				    prompt);
			    usage();
			}
			forward_flags |= OPTS_FORWARD_CREDS;
#else
			fprintf(stderr,
D 25
			 "%s: Warning: -f ignored, no Kerberos V5 support.\n", 
E 25
I 25
			 "%s: Warning: -f ignored, no Kerberos V5 support.\n",
E 25
				prompt);
#endif
			break;
		case 'F':
#if defined(AUTHENTICATION) && defined(KRB5) && defined(FORWARD)
			if (forward_flags & OPTS_FORWARD_CREDS) {
D 25
			    fprintf(stderr, 
E 25
I 25
			    fprintf(stderr,
E 25
				    "%s: Only one of -f and -F allowed.\n",
				    prompt);
			    usage();
			}
			forward_flags |= OPTS_FORWARD_CREDS;
			forward_flags |= OPTS_FORWARDABLE_CREDS;
#else
			fprintf(stderr,
D 25
			 "%s: Warning: -F ignored, no Kerberos V5 support.\n", 
E 25
I 25
			 "%s: Warning: -F ignored, no Kerberos V5 support.\n",
E 25
				prompt);
#endif
E 24
			break;
I 17
		case 'k':
D 20
#if defined(AUTHENTICATE) && defined(KRB4)
E 20
I 20
#if defined(AUTHENTICATION) && defined(KRB4)
E 20
		    {
			extern char *dest_realm, dst_realm_buf[], dst_realm_sz;
			dest_realm = dst_realm_buf;
			(void)strncpy(dest_realm, optarg, dst_realm_sz);
		    }
#else
			fprintf(stderr,
			   "%s: Warning: -k ignored, no Kerberos V4 support.\n",
								prompt);
#endif
			break;
E 17
		case 'l':
			autologin = 1;
			user = optarg;
			break;
		case 'n':
#if defined(TN3270) && defined(unix)
			/* distinguish between "-n oasynch" and "-noasynch" */
			if (argv[optind - 1][0] == '-' && argv[optind - 1][1]
			    == 'n' && argv[optind - 1][2] == 'o') {
				if (!strcmp(optarg, "oasynch")) {
					noasynchtty = 1;
					noasynchnet = 1;
				} else if (!strcmp(optarg, "oasynchtty"))
					noasynchtty = 1;
D 16
				} else if (!strcmp(optarg, "oasynchnet"))
E 16
I 16
				else if (!strcmp(optarg, "oasynchnet"))
E 16
					noasynchnet = 1;
D 16
				}
E 16
			} else
E 15
#endif	/* defined(TN3270) && defined(unix) */
D 15
	    if (argv[1][1] != '\0') {
		fprintf(stderr, "Unknown option *%s*.\n", argv[1]);
	    }
E 15
I 15
				SetNetTrace(optarg);
			break;
D 17
#if defined(TN3270) && defined(unix)
E 17
I 17
		case 'r':
			rlogin = '~';
			break;
E 17
		case 't':
I 17
#if defined(TN3270) && defined(unix)
E 17
			transcom = tline;
			(void)strcpy(transcom, optarg);
I 17
#else
			fprintf(stderr,
			   "%s: Warning: -t ignored, no TN3270 support.\n",
								prompt);
#endif
E 17
			break;
I 17
		case 'x':
D 20
#ifdef	ENCRYPT
E 20
I 20
#ifdef	ENCRYPTION
E 20
D 19
			encrypt_auto();
E 19
I 19
			encrypt_auto(1);
			decrypt_auto(1);
E 19
D 22
#else
E 22
I 22
#else	/* ENCRYPTION */
E 22
			fprintf(stderr,
			    "%s: Warning: -x ignored, no ENCRYPT support.\n",
								prompt);
E 17
D 22
#endif
E 22
I 22
#endif	/* ENCRYPTION */
E 22
I 17
			break;
E 17
		case '?':
		default:
			usage();
			/* NOTREACHED */
		}
I 16
	}
I 17
	if (autologin == -1)
		autologin = (rlogin == _POSIX_VDISABLE) ? 0 : 1;

E 17
E 16
	argc -= optind;
	argv += optind;

	if (argc) {
		char *args[7], **argp = args;

		if (argc > 2)
			usage();
		*argp++ = prompt;
		if (user) {
			*argp++ = "-l";
			*argp++ = user;
		}
		*argp++ = argv[0];		/* host */
		if (argc > 1)
			*argp++ = argv[1];	/* port */
		*argp = 0;

		if (setjmp(toplevel) != 0)
			Exit(0);
		if (tn(argp - args, args) == 1)
			return (0);
		else
			return (1);
E 15
	}
D 15
	argc--;
	argv++;
    }
    if (argc != 1) {
	if (setjmp(toplevel) != 0)
	    Exit(0);
I 14
	if (user) {
	    argc += 2;
	    argv -= 2;
	    argv[0] = argv[2];
	    argv[1] = "-l";
	    argv[2] = user;
	}
E 14
D 7
	tn(argc, argv);
E 7
I 7
	if (tn(argc, argv) == 1) {
	    return 0;
	} else {
	    return 1;
	}
E 7
    }
D 7
    setjmp(toplevel);
E 7
I 7
    (void) setjmp(toplevel);
E 7
    for (;;) {
#if	!defined(TN3270)
D 11
	command(1);
E 11
I 11
	command(1, 0, 0);
E 11
#else	/* !defined(TN3270) */
	if (!shell_active) {
D 11
	    command(1);
E 11
I 11
	    command(1, 0, 0);
E 11
	} else {
#if	defined(TN3270)
	    shell_continue();
#endif	/* defined(TN3270) */
	}
#endif	/* !defined(TN3270) */
    }
E 15
I 15
	(void)setjmp(toplevel);
D 16
	for (;;)
E 16
I 16
	for (;;) {
E 16
#ifdef TN3270
		if (shell_active)
			shell_continue();
		else
#endif
			command(1, 0, 0);
I 16
	}
E 16
D 17
}

usage()
{
	fprintf(stderr, "usage: %s [-a] [ [-l user] host-name [port] ]\n",
	    prompt);
	exit(1);
E 17
E 15
}
E 1
