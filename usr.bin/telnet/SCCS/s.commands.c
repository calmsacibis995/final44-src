h60275
s 00041/00041/02878
d D 8.4 95/05/30 20:57:04 dab 51 50
c code cleanup, change b*() calls to mem*() calls
e
s 00016/00004/02903
d D 8.3 95/02/16 11:36:55 dab 50 49
c Fix auth & encrypt commands to require a second argument.
c Fix the "open" command to require that "open help" or "open ?" be
c used to get help info, previously "open h", "open he" and "open hel"
c would give help info, meaning if you had a machine named "h", "he"
c or "hel" you couldn't connect to it.  Now you just can't connect to
c a machine named "help".
e
s 00021/00017/02886
d D 8.2 93/12/15 11:35:53 dab 49 48
c Add support for new ENVIRON command.
c Latest Kerberos V code from MIT (includes new
c options '-f' and '-F' to control the forwarding
c of credentials.)  Various bugfixes to keep some
c C compilers happy.
e
s 00002/00002/02901
d D 8.1 93/06/06 16:32:24 bostic 48 47
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/02902
d D 5.13 93/06/01 11:49:30 dab 47 46
c Fix the hton() declaration to be an ANSI type
c declaration, so that it matches what is in machine/endian.h
e
s 00016/00016/02887
d D 5.12 93/05/20 10:49:34 dab 46 44
c Mostly, this changes all the "#if defined(ENCRYPTION)"
c lines to "#ifdef ENCRYPTION".  This will allow unifdef
c to be used to strip out the encryption code for
c foreign exports.  This also fixes up the usage statement.
e
s 00016/00016/02887
d R 5.12 93/05/20 10:37:24 dab 45 44
c Mostly this changes "#if defined(ENCRYPTION)" to
c "#ifdef ENCRYPTION".  This will allow unifdef to be
e
s 00004/00000/02899
d D 5.11 93/05/11 10:02:13 bostic 44 43
c make tn3270 compile again
e
s 00048/00005/02851
d D 5.10 93/04/05 17:05:56 dab 43 42
c Fix gcc2 warnings.
c Fix the generation/parsing of the Environment option SEND suboption.
c Add code (#ifdef ENV_HACK) to help interoperation with Telnet servers
c that have the definitions for ENV_VAR and ENV_VALUE reversed.
e
s 00001/00001/02855
d D 5.9 93/02/04 13:26:53 dab 42 41
c Fix message for "skiprc" so that the message
c that gets printed when it is changed is correct. (It
c used to print the exact opposite of what was really
c being done...)
e
s 00094/00033/02762
d D 5.8 92/12/18 14:06:54 dab 41 40
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Add Sun/SVR4 Streams support
c Allow for more ptys
c Environ suboption USERVAR support
c New Telnet Flowcontrol suboption support
c Server -k option to default to no kludge linemode
c Server -U option, allow only registered hosts to connect
e
s 00002/00003/02793
d D 5.7 92/11/16 23:07:59 torek 40 38
c rm bogus variable to fix "send" command (jonathan@CS.Stanford.EDU)
e
s 00001/00002/02794
d R 5.7 92/11/16 23:04:08 torek 39 38
c rm bogus variable to fix "send" command (jonathan@CS.Stanford.EDU)
e
s 00010/00010/02786
d D 5.6 92/10/24 15:14:22 ralph 38 37
c fix gcc2 warnings for extern & later declared static.
e
s 00062/00017/02734
d D 5.5 91/03/22 13:09:04 dab 37 36
c Upgrade to the latest & greatest authentication/encryption
e
s 00011/00003/02740
d D 5.4 91/03/01 02:59:05 dab 36 35
c Add -S option (type of service)
e
s 00668/00566/02075
d D 5.3 91/03/01 01:32:11 dab 35 34
c Telnet AUTHENTICATION option
c Telnet ENCRYPT option (test version)
c Function prototypes
e
s 00004/00004/02637
d D 5.2 90/09/19 16:56:48 william 34 33
c changed conditional inclusion of machine/endian to instead use param.h
c so i386 (among others) can use source route feature
e
s 00074/00028/02567
d D 5.1 90/09/14 10:48:54 borman 33 32
c Latest batch of changes.  See the README file
c for a list of all the changes to telnet & telnetd.
e
s 00001/00001/02594
d D 1.32 90/07/28 00:08:53 karels 32 31
c always mark for export when defining environ variables
e
s 00020/00001/02575
d D 1.31 90/07/27 23:28:38 karels 31 30
c change USER-passing to happen only if -a or -l user specified
c (still not quite right, "open -l name" defines USER=name and exports);
c use current user id if different than login name; getopting and reformatting
c of main.c by bostic
e
s 00464/00081/02112
d D 1.30 90/06/28 12:58:29 borman 30 29
c Lots of bugfixes, add the ENVIRON and X-DISPLAY-LOC
c options, "-l user" to the command line, diagnostic flags.
e
s 00016/00040/02177
d D 1.29 90/06/27 19:02:32 karels 29 28
c add IP type-of-service without gettos (at least for now)
e
s 00008/00001/02209
d D 1.28 90/06/20 16:29:43 kfall 28 27
c small change towards Kerberized telnet
e
s 00001/00011/02209
d D 1.27 90/06/01 17:44:36 bostic 27 26
c new copyright notice
e
s 00001/00001/02219
d D 1.26 90/05/18 17:47:20 bostic 26 25
c add hp300 define
e
s 00009/00005/02211
d D 1.25 90/03/01 07:57:35 borman 25 24
c Change how TOS code gets included
e
s 00037/00006/02179
d D 1.24 90/03/01 06:18:51 borman 24 23
c Several items:
c 1) Change from TC[GS]ETA* to TIOC[GS]ETA*
c 2) Use the cc_t typedef from terios.h
c 3) Add SLC_FORW support
c 4) Add TOS support
c 5) Fix the SLC_SUSP support.  The escape
c    character now uses one of the VEOL characters.
e
s 00015/00026/02170
d D 1.23 89/11/14 10:20:26 borman 23 22
c Latest & greatest version of telnet
e
s 00005/00000/02191
d D 1.22 89/09/02 15:48:00 minshall 22 21
c Add in "to apitrace"
e
s 00091/00013/02100
d D 1.21 89/09/01 15:47:59 borman 21 20
c  RFC 1091 term type support, STATUS support, BINARY changes
e
s 00009/00009/02104
d D 1.20 89/08/28 09:57:32 borman 20 19
c Fix tags on #else #endif for ANSI C
e
s 00900/00202/01213
d D 1.19 89/08/21 14:58:30 borman 19 18
c Add support for LINEMODE option
e
s 00016/00000/01399
d D 1.18 89/05/30 22:14:53 minshall 18 17
c Add two toggles: termdata, cursesdata.
e
s 00014/00025/01385
d D 1.17 89/03/21 22:30:54 minshall 17 16
c Keep track of each side's idea of what the state of each option is.
e
s 00023/00013/01387
d D 1.16 89/03/20 23:52:26 minshall 16 15
c Mods from DDP, et al, for LFLOW, TSPEED, and NAWS support.
e
s 00001/00001/01399
d D 1.15 89/02/06 19:05:37 minshall 15 14
c Make Gould compiler happy.
e
s 00109/00001/01291
d D 1.14 88/11/29 22:09:35 minshall 14 13
c Try to fix SIGIO problem with Sun machines, h_errno with
c Sun machines, more debugging and options.
e
s 00005/00001/01287
d D 1.13 88/11/18 22:31:01 minshall 13 12
c Count SIGIO's (for debugging).  Separate out noasynch between
c tty and net.
e
s 00033/00004/01255
d D 1.12 88/10/30 13:16:05 minshall 12 11
c 1.  Fix "ambiguous" versus "unknown" commands; 2.  Don't tell
c about "toggle" results twice; 3.  Add herror() support for older Berkeley
c systems.
e
s 00001/00001/01258
d D 1.11 88/10/11 13:48:36 bostic 11 10
c use herror
e
s 00003/00003/01256
d D 1.10 88/09/14 23:44:20 minshall 10 9
c Fix bug which kept us from quitting (because bye()'s
c argc was too high).
e
s 00001/00000/01258
d D 1.9 88/08/28 17:46:52 minshall 9 8
c Some linting of tn3270.
e
s 00018/00009/01240
d D 1.8 88/08/01 22:02:36 minshall 8 7
c Fix to allow us to run on a Sun4.
e
s 00010/00005/01239
d D 1.7 88/06/29 20:15:11 bostic 7 6
c install approved copyright notice
e
s 00019/00013/01225
d D 1.6 88/06/27 22:19:40 minshall 6 5
c Fix up lint errors.
e
s 00002/00000/01236
d D 1.5 88/05/15 19:24:33 minshall 5 4
c Include "general.h" to get rid of ansi mem* functions.
e
s 00016/00000/01220
d D 1.4 88/03/08 10:30:42 bostic 4 3
c add Berkeley specific copyright
e
s 00000/00036/01220
d D 1.3 87/10/27 15:59:40 minshall 3 2
c Move tn3270 and unix specific things to Unix places.
e
s 00003/00001/01253
d D 1.2 87/10/10 14:27:13 minshall 2 1
c This is the first version to get near rings.  It compiles,
c but doesn't work.
e
s 01254/00000/00000
d D 1.1 87/09/11 15:40:36 minshall 1 0
c date and time created 87/09/11 15:40:36 by minshall
e
u
U
t
T
I 4
/*
D 33
 * Copyright (c) 1988 Regents of the University of California.
E 33
I 33
D 48
 * Copyright (c) 1988, 1990 Regents of the University of California.
E 33
 * All rights reserved.
E 48
I 48
 * Copyright (c) 1988, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 48
 *
D 27
 * Redistribution and use in source and binary forms are permitted
D 7
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 7
I 7
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
E 27
I 27
 * %sccs.include.redist.c%
E 27
E 7
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 4
I 1
D 29
#include <sys/types.h>
E 29
I 29
D 30
#include <sys/param.h>
E 30
I 30
D 34
#include <sys/types.h>
E 34
E 30
E 29
I 14
#if	defined(unix)
I 34
#include <sys/param.h>
I 35
D 41
#ifdef	CRAY
E 41
I 41
#if	defined(CRAY) || defined(sysV88)
E 41
#include <sys/types.h>
#endif
E 35
E 34
#include <sys/file.h>
I 34
#else
#include <sys/types.h>
E 34
#endif	/* defined(unix) */
I 34
D 35

E 35
E 34
E 14
#include <sys/socket.h>
#include <netinet/in.h>
I 29
D 30
#include <netinet/in_systm.h>
#include <netinet/ip.h>
E 30
E 29
I 19
#ifdef	CRAY
D 35
#include <sys/fcntl.h>
E 35
I 35
#include <fcntl.h>
E 35
D 20
#endif	CRAY
E 20
I 20
#endif	/* CRAY */
E 20
E 19

#include <signal.h>
#include <netdb.h>
#include <ctype.h>
I 31
#include <pwd.h>
E 31
I 8
#include <varargs.h>
I 35
#include <errno.h>
E 35
E 8

#include <arpa/telnet.h>

I 5
#include "general.h"

E 5
I 2
#include "ring.h"

E 2
#include "externs.h"
#include "defines.h"
#include "types.h"

I 30
D 35
#ifdef	SRCRT
# ifndef CRAY
# include <netinet/in_systm.h>
D 34
#  if (defined(vax) || defined(tahoe) || defined(hp300)) && !defined(ultrix)
#  include <machine/endian.h>
#  endif /* vax */
E 34
# endif /* CRAY */
E 35
I 35
D 41
#ifndef CRAY
E 41
I 41
#if !defined(CRAY) && !defined(sysV88)
E 41
#include <netinet/in_systm.h>
# if (defined(vax) || defined(tahoe) || defined(hp300)) && !defined(ultrix)
# include <machine/endian.h>
# endif /* vax */
D 41
#endif /* CRAY */
E 41
I 41
#endif /* !defined(CRAY) && !defined(sysV88) */
E 41
E 35
#include <netinet/ip.h>
D 35
#endif /* SRCRT */
E 35
E 30
I 19
D 29
#ifdef	SRCRT
D 20
#if	!defined(CRAY)
#include <netinet/in_systm.h>
#if	!defined(sun)
#include <machine/endian.h>
#endif
#endif
E 20
I 20
# ifndef CRAY
# include <netinet/in_systm.h>
D 23
#  ifndef sun
E 23
I 23
D 26
#  if defined(vax) || defined(tahoe)
E 26
I 26
#  if defined(vax) || defined(tahoe) || defined(hp300)
E 26
E 23
#  include <machine/endian.h>
D 23
#  endif /* sun */
E 23
I 23
#  endif /* vax */
E 23
# endif /* CRAY */
E 20
#include <netinet/ip.h>
D 20
#endif
E 20
I 20
#endif /* SRCRT */
E 29
E 20

I 25
D 35
#if defined(CRAY) && defined(IP_TOS) && !defined(HAS_IP_TOS)
D 29
# define HAS_IP_TOS
E 29
I 29
D 30
# define HAS_IP_TOS		/* have gettos() lookup */
E 30
I 30
# define HAS_IP_TOS
E 30
E 29
#endif
E 35
E 25

I 35
D 51
#ifndef       MAXHOSTNAMELEN
#define       MAXHOSTNAMELEN 64
#endif        MAXHOSTNAMELEN
E 51
I 51
#ifndef	MAXHOSTNAMELEN
#define	MAXHOSTNAMELEN 64
#endif	MAXHOSTNAMELEN
E 51
E 35
I 25

I 36
#if	defined(IPPROTO_IP) && defined(IP_TOS)
int tos = -1;
#endif	/* defined(IPPROTO_IP) && defined(IP_TOS) */

E 36
E 25
E 19
char	*hostname;
I 35
static char _hostname[MAXHOSTNAMELEN];

E 35
I 19
extern char *getenv();
E 19

D 12
#define Ambiguous(s)	((char *)s == ambiguous)
E 12
I 12
D 35
#define Ambiguous(s)	((char **)s == &ambiguous)
E 12
static char *ambiguous;		/* special return value for command routines */
E 35
I 35
extern int isprefix();
extern char **genget();
extern int Ambiguous();

E 35
I 30
static call();
E 30

typedef struct {
	char	*name;		/* command name */
D 19
	char	*help;		/* help string */
E 19
I 19
	char	*help;		/* help string (NULL for no help) */
E 19
	int	(*handler)();	/* routine which executes command */
D 19
	int	dohelp;		/* Should we give general help information? */
E 19
	int	needconnect;	/* Do we need to be connected to execute? */
} Command;

D 19
static char line[200];
E 19
I 19
static char line[256];
static char saveline[256];
E 19
static int margc;
static char *margv[20];

D 35
/*
 * Various utility routines.
 */

I 12
#if	!defined(BSD) || (BSD <= 43)

char	*h_errlist[] = {
	"Error 0",
	"Unknown host",				/* 1 HOST_NOT_FOUND */
	"Host name lookup failure",		/* 2 TRY_AGAIN */
	"Unknown server error",			/* 3 NO_RECOVERY */
	"No address associated with name",	/* 4 NO_ADDRESS */
};
int	h_nerr = { sizeof(h_errlist)/sizeof(h_errlist[0]) };

D 14
extern int	h_errno;
E 14
I 14
int h_errno;		/* In some version of SunOS this is necessary */
E 14

/*
 * herror --
 *	print the error indicated by the h_errno value.
 */
herror(s)
	char *s;
{
	if (s && *s) {
		fprintf(stderr, "%s: ", s);
	}
	if ((h_errno < 0) || (h_errno >= h_nerr)) {
		fprintf(stderr, "Unknown error\n");
I 14
	} else if (h_errno == 0) {
#if	defined(sun)
		fprintf(stderr, "Host unknown\n");
#endif	/* defined(sun) */
E 14
	} else {
		fprintf(stderr, "%s\n", h_errlist[h_errno]);
	}
}
#endif	/* !define(BSD) || (BSD <= 43) */

E 12
static void
E 35
I 35
    static void
E 35
makeargv()
{
D 30
    register char *cp;
E 30
I 30
    register char *cp, *cp2, c;
E 30
    register char **argp = margv;

    margc = 0;
    cp = line;
    if (*cp == '!') {		/* Special case shell escape */
I 19
	strcpy(saveline, line);	/* save for shell command */
E 19
	*argp++ = "!";		/* No room in string to get this */
	margc++;
	cp++;
    }
D 30
    while (*cp) {
	while (isspace(*cp))
	    cp++;
	if (*cp == '\0')
E 30
I 30
    while (c = *cp) {
	register int inquote = 0;
	while (isspace(c))
	    c = *++cp;
	if (c == '\0')
E 30
	    break;
	*argp++ = cp;
	margc += 1;
D 30
	while (*cp != '\0' && !isspace(*cp))
	    cp++;
	if (*cp == '\0')
E 30
I 30
	for (cp2 = cp; c != '\0'; c = *++cp) {
	    if (inquote) {
		if (c == inquote) {
		    inquote = 0;
		    continue;
		}
	    } else {
		if (c == '\\') {
		    if ((c = *++cp) == '\0')
			break;
		} else if (c == '"') {
		    inquote = '"';
		    continue;
		} else if (c == '\'') {
		    inquote = '\'';
		    continue;
		} else if (isspace(c))
		    break;
	    }
	    *cp2++ = c;
	}
	*cp2 = '\0';
	if (c == '\0')
E 30
	    break;
D 30
	*cp++ = '\0';
E 30
I 30
	cp++;
E 30
    }
    *argp++ = 0;
}

D 35

static char **
genget(name, table, next)
char	*name;		/* name to match */
char	**table;		/* name entry in table */
char	**(*next)();	/* routine to return next entry in table */
{
	register char *p, *q;
	register char **c, **found;
	register int nmatches, longest;

	if (name == 0) {
	    return 0;
	}
	longest = 0;
	nmatches = 0;
	found = 0;
	for (c = table; (p = *c) != 0; c = (*next)(c)) {
		for (q = name;
		    (*q == *p) || (isupper(*q) && tolower(*q) == *p); p++, q++)
			if (*q == 0)		/* exact match? */
				return (c);
		if (!*q) {			/* the name was a prefix */
			if (q - name > longest) {
				longest = q - name;
				nmatches = 1;
				found = c;
			} else if (q - name == longest)
				nmatches++;
		}
	}
	if (nmatches > 1)
D 12
		return (char **)ambiguous;
E 12
I 12
		return &ambiguous;
E 12
	return (found);
}

E 35
/*
 * Make a character string into a number.
 *
 * Todo:  1.  Could take random integers (12, 0x12, 012, 0b1).
 */

D 35
static
E 35
I 35
	static
E 35
special(s)
D 35
register char *s;
E 35
I 35
	register char *s;
E 35
{
	register char c;
	char b;

	switch (*s) {
	case '^':
		b = *++s;
		if (b == '?') {
		    c = b | 0x40;		/* DEL */
		} else {
		    c = b & 0x1f;
		}
		break;
	default:
		c = *s;
		break;
	}
	return c;
}

/*
 * Construct a control character sequence
 * for a special character.
 */
D 35
static char *
E 35
I 35
	static char *
E 35
control(c)
D 24
	register int c;
E 24
I 24
	register cc_t c;
E 24
{
D 30
	static char buf[3];
E 30
I 30
	static char buf[5];
I 35
	/*
	 * The only way I could get the Sun 3.5 compiler
	 * to shut up about
	 *	if ((unsigned int)c >= 0x80)
	 * was to assign "c" to an unsigned int variable...
	 * Arggg....
	 */
	register unsigned int uic = (unsigned int)c;
E 35
E 30

D 35
	if (c == 0x7f)
E 35
I 35
	if (uic == 0x7f)
E 35
		return ("^?");
D 24
	if (c == '\377') {
E 24
I 24
D 33
	if (c == (cc_t)-1) {
E 33
I 33
	if (c == (cc_t)_POSIX_VDISABLE) {
E 33
E 24
		return "off";
	}
D 30
	if (c >= 0x20) {
E 30
I 30
D 33
	if (c >= 0x80) {
E 33
I 33
D 35
	if ((unsigned int)c >= 0x80) {
E 35
I 35
	if (uic >= 0x80) {
E 35
E 33
		buf[0] = '\\';
		buf[1] = ((c>>6)&07) + '0';
		buf[2] = ((c>>3)&07) + '0';
		buf[3] = (c&07) + '0';
		buf[4] = 0;
D 33
	} else if (c >= 0x20) {
E 33
I 33
D 35
	} else if ((unsigned int)c >= 0x20) {
E 35
I 35
	} else if (uic >= 0x20) {
E 35
E 33
E 30
		buf[0] = c;
		buf[1] = 0;
	} else {
		buf[0] = '^';
		buf[1] = '@'+c;
		buf[2] = 0;
	}
	return (buf);
}



/*
 *	The following are data structures and routines for
 *	the "send" command.
 *
 */
D 51
 
E 51
I 51

E 51
struct sendlist {
    char	*name;		/* How user refers to it (case independent) */
D 19
    int		what;		/* Character to be sent (<0 ==> special) */
E 19
    char	*help;		/* Help information (0 ==> no help) */
D 35
#if	defined(NOT43)
E 35
I 35
    int		needconnect;	/* Need to be connected */
    int		narg;		/* Number of arguments */
E 35
D 19
    int		(*routine)();	/* Routine to perform (for special ops) */
E 19
I 19
    int		(*handler)();	/* Routine to perform (for special ops) */
E 19
D 35
#else	/* defined(NOT43) */
D 19
    void	(*routine)();	/* Routine to perform (for special ops) */
E 19
I 19
    void	(*handler)();	/* Routine to perform (for special ops) */
E 19
#endif	/* defined(NOT43) */
E 35
I 35
    int		nbyte;		/* Number of bytes to send this command */
E 35
I 19
    int		what;		/* Character to be sent (<0 ==> special) */
E 19
};

D 35
#define	SENDQUESTION	-1
#define	SENDESCAPE	-3
E 35

I 35
D 38
extern int
E 38
I 38
static int
E 38
	send_esc P((void)),
	send_help P((void)),
	send_docmd P((char *)),
	send_dontcmd P((char *)),
	send_willcmd P((char *)),
	send_wontcmd P((char *));

E 35
static struct sendlist Sendlist[] = {
D 19
    { "ao", AO, "Send Telnet Abort output" },
    { "ayt", AYT, "Send Telnet 'Are You There'" },
    { "brk", BREAK, "Send Telnet Break" },
    { "ec", EC, "Send Telnet Erase Character" },
    { "el", EL, "Send Telnet Erase Line" },
    { "escape", SENDESCAPE, "Send current escape character" },
    { "ga", GA, "Send Telnet 'Go Ahead' sequence" },
    { "ip", IP, "Send Telnet Interrupt Process" },
    { "nop", NOP, "Send Telnet 'No operation'" },
    { "synch", SYNCH, "Perform Telnet 'Synch operation'", dosynch },
    { "?", SENDQUESTION, "Display send options" },
E 19
I 19
D 35
    { "ao",	"Send Telnet Abort output",		0,	AO },
    { "ayt",	"Send Telnet 'Are You There'",		0,	AYT },
    { "brk",	"Send Telnet Break",			0,	BREAK },
    { "ec",	"Send Telnet Erase Character",		0,	EC },
    { "el",	"Send Telnet Erase Line",		0,	EL },
    { "escape",	"Send current escape character",	0,	SENDESCAPE },
    { "ga",	"Send Telnet 'Go Ahead' sequence",	0,	GA },
    { "ip",	"Send Telnet Interrupt Process",	0,	IP },
    { "nop",	"Send Telnet 'No operation'",		0,	NOP },
    { "eor",	"Send Telnet 'End of Record'",		0,	EOR },
    { "abort",	"Send Telnet 'Abort Process'",		0,	ABORT },
    { "susp",	"Send Telnet 'Suspend Process'",	0,	SUSP },
    { "eof",	"Send Telnet End of File Character",	0,	xEOF },
    { "synch",	"Perform Telnet 'Synch operation'",	dosynch, SYNCH },
I 21
    { "getstatus", "Send request for STATUS",		get_status, 0 },
E 21
    { "?",	"Display send options",			0,	SENDQUESTION },
E 35
I 35
    { "ao",	"Send Telnet Abort output",		1, 0, 0, 2, AO },
    { "ayt",	"Send Telnet 'Are You There'",		1, 0, 0, 2, AYT },
    { "brk",	"Send Telnet Break",			1, 0, 0, 2, BREAK },
    { "break",	0,					1, 0, 0, 2, BREAK },
    { "ec",	"Send Telnet Erase Character",		1, 0, 0, 2, EC },
    { "el",	"Send Telnet Erase Line",		1, 0, 0, 2, EL },
    { "escape",	"Send current escape character",	1, 0, send_esc, 1, 0 },
    { "ga",	"Send Telnet 'Go Ahead' sequence",	1, 0, 0, 2, GA },
    { "ip",	"Send Telnet Interrupt Process",	1, 0, 0, 2, IP },
    { "intp",	0,					1, 0, 0, 2, IP },
    { "interrupt", 0,					1, 0, 0, 2, IP },
    { "intr",	0,					1, 0, 0, 2, IP },
    { "nop",	"Send Telnet 'No operation'",		1, 0, 0, 2, NOP },
    { "eor",	"Send Telnet 'End of Record'",		1, 0, 0, 2, EOR },
    { "abort",	"Send Telnet 'Abort Process'",		1, 0, 0, 2, ABORT },
    { "susp",	"Send Telnet 'Suspend Process'",	1, 0, 0, 2, SUSP },
    { "eof",	"Send Telnet End of File Character",	1, 0, 0, 2, xEOF },
    { "synch",	"Perform Telnet 'Synch operation'",	1, 0, dosynch, 2, 0 },
    { "getstatus", "Send request for STATUS",		1, 0, get_status, 6, 0 },
    { "?",	"Display send options",			0, 0, send_help, 0, 0 },
    { "help",	0,					0, 0, send_help, 0, 0 },
    { "do",	0,					0, 1, send_docmd, 3, 0 },
    { "dont",	0,					0, 1, send_dontcmd, 3, 0 },
    { "will",	0,					0, 1, send_willcmd, 3, 0 },
    { "wont",	0,					0, 1, send_wontcmd, 3, 0 },
E 35
E 19
    { 0 }
};

D 35
static struct sendlist Sendlist2[] = {		/* some synonyms */
D 19
	{ "break", BREAK, 0 },
E 19
I 19
    { "break",		0, 0, BREAK },
E 35
I 35
#define	GETSEND(name) ((struct sendlist *) genget(name, (char **) Sendlist, \
				sizeof(struct sendlist)))
E 35
E 19

D 19
	{ "intp", IP, 0 },
	{ "interrupt", IP, 0 },
	{ "intr", IP, 0 },
E 19
I 19
D 35
    { "intp",		0, 0, IP },
    { "interrupt",	0, 0, IP },
    { "intr",		0, 0, IP },
E 19

D 19
	{ "help", SENDQUESTION, 0 },
E 19
I 19
    { "help",		0, 0, SENDQUESTION },
E 19

D 19
	{ 0 }
E 19
I 19
    { 0 }
E 19
};

static char **
getnextsend(name)
char *name;
{
    struct sendlist *c = (struct sendlist *) name;

    return (char **) (c+1);
}

static struct sendlist *
getsend(name)
char *name;
{
    struct sendlist *sl;

    if ((sl = (struct sendlist *)
			genget(name, (char **) Sendlist, getnextsend)) != 0) {
	return sl;
    } else {
	return (struct sendlist *)
				genget(name, (char **) Sendlist2, getnextsend);
    }
}

static
E 35
I 35
    static int
E 35
sendcmd(argc, argv)
D 35
int	argc;
char	**argv;
E 35
I 35
    int  argc;
    char **argv;
E 35
{
D 40
    int what;		/* what we are sending this time */
E 40
    int count;		/* how many bytes we are going to need to send */
    int i;
    int question = 0;	/* was at least one argument a question */
    struct sendlist *s;	/* pointer to current command */
I 35
    int success = 0;
    int needconnect = 0;
E 35

    if (argc < 2) {
	printf("need at least one argument for 'send' command\n");
	printf("'send ?' for help\n");
	return 0;
    }
    /*
     * First, validate all the send arguments.
     * In addition, we see how much space we are going to need, and
     * whether or not we will be doing a "SYNCH" operation (which
     * flushes the network queue).
     */
    count = 0;
    for (i = 1; i < argc; i++) {
D 35
	s = getsend(argv[i]);
E 35
I 35
	s = GETSEND(argv[i]);
E 35
	if (s == 0) {
	    printf("Unknown send argument '%s'\n'send ?' for help.\n",
			argv[i]);
	    return 0;
	} else if (Ambiguous(s)) {
	    printf("Ambiguous send argument '%s'\n'send ?' for help.\n",
			argv[i]);
	    return 0;
	}
D 35
	switch (s->what) {
	case SENDQUESTION:
I 19
	    question = 1;
E 19
	    break;
	case SENDESCAPE:
	    count += 1;
	    break;
	case SYNCH:
	    count += 2;
	    break;
	default:
	    count += 2;
	    break;
E 35
I 35
	if (i + s->narg >= argc) {
	    fprintf(stderr,
	    "Need %d argument%s to 'send %s' command.  'send %s ?' for help.\n",
		s->narg, s->narg == 1 ? "" : "s", s->name, s->name);
	    return 0;
E 35
	}
I 35
	count += s->nbyte;
	if (s->handler == send_help) {
	    send_help();
	    return 0;
	}

	i += s->narg;
	needconnect += s->needconnect;
E 35
    }
I 19
D 35
    if (!connected) {
	if (count)
	    printf("?Need to be connected first.\n");
	if (question) {
	    for (s = Sendlist; s->name; s++)
		if (s->help)
		    printf("%-15s %s\n", s->name, s->help);
	} else
	    printf("'send ?' for help\n");
	return !question;
E 35
I 35
    if (!connected && needconnect) {
	printf("?Need to be connected first.\n");
	printf("'send ?' for help\n");
	return 0;
E 35
    }
E 19
    /* Now, do we have enough room? */
    if (NETROOM() < count) {
	printf("There is not enough room in the buffer TO the network\n");
	printf("to process your request.  Nothing will be done.\n");
	printf("('send synch' will throw away most data in the network\n");
	printf("buffer, if this might help.)\n");
	return 0;
    }
    /* OK, they are all OK, now go through again and actually send */
I 35
    count = 0;
E 35
    for (i = 1; i < argc; i++) {
D 35
	if ((s = getsend(argv[i])) == 0) {
E 35
I 35
	if ((s = GETSEND(argv[i])) == 0) {
E 35
	    fprintf(stderr, "Telnet 'send' error - argument disappeared!\n");
D 30
	    quit();
E 30
I 30
	    (void) quit();
E 30
	    /*NOTREACHED*/
	}
D 19
	if (s->routine) {
	    (*s->routine)(s);
E 19
I 19
	if (s->handler) {
D 35
	    (*s->handler)(s);
E 35
I 35
	    count++;
	    success += (*s->handler)((s->narg > 0) ? argv[i+1] : 0,
				  (s->narg > 1) ? argv[i+2] : 0);
	    i += s->narg;
E 35
E 19
	} else {
D 35
	    switch (what = s->what) {
	    case SYNCH:
		dosynch();
		break;
	    case SENDQUESTION:
		for (s = Sendlist; s->name; s++) {
D 19
		    if (s->help) {
			printf(s->name);
			if (s->help) {
			    printf("\t%s", s->help);
			}
			printf("\n");
		    }
E 19
I 19
		    if (s->help)
			printf("%-15s %s\n", s->name, s->help);
E 19
		}
		question = 1;
		break;
	    case SENDESCAPE:
		NETADD(escape);
		break;
	    default:
		NET2ADD(IAC, what);
I 33
		printoption("SENT", "IAC", what);
E 33
		break;
E 35
I 35
D 40
	    NET2ADD(IAC, what);
	    printoption("SENT", IAC, what);
E 40
I 40
	    NET2ADD(IAC, s->what);
	    printoption("SENT", IAC, s->what);
E 40
	}
    }
    return (count == success);
}

    static int
send_esc()
{
    NETADD(escape);
    return 1;
}

    static int
send_docmd(name)
    char *name;
{
D 43
    void send_do();
E 43
    return(send_tncmd(send_do, "do", name));
}

    static int
send_dontcmd(name)
    char *name;
{
D 43
    void send_dont();
E 43
    return(send_tncmd(send_dont, "dont", name));
}
    static int
send_willcmd(name)
    char *name;
{
D 43
    void send_will();
E 43
    return(send_tncmd(send_will, "will", name));
}
    static int
send_wontcmd(name)
    char *name;
{
D 43
    void send_wont();
E 43
    return(send_tncmd(send_wont, "wont", name));
}

    int
send_tncmd(func, cmd, name)
    void	(*func)();
    char	*cmd, *name;
{
    char **cpp;
    extern char *telopts[];
I 41
    register int val = 0;
E 41

    if (isprefix(name, "help") || isprefix(name, "?")) {
	register int col, len;

D 41
	printf("Usage: send %s <option>\n", cmd);
E 41
I 41
	printf("Usage: send %s <value|option>\n", cmd);
	printf("\"value\" must be from 0 to 255\n");
E 41
	printf("Valid options are:\n\t");

	col = 8;
	for (cpp = telopts; *cpp; cpp++) {
D 41
	    len = strlen(*cpp) + 1;
E 41
I 41
	    len = strlen(*cpp) + 3;
E 41
	    if (col + len > 65) {
		printf("\n\t");
		col = 8;
E 35
	    }
I 35
D 41
	    printf(" %s", *cpp);
E 41
I 41
	    printf(" \"%s\"", *cpp);
E 41
	    col += len;
E 35
	}
I 35
	printf("\n");
	return 0;
E 35
    }
D 35
    return !question;
E 35
I 35
    cpp = (char **)genget(name, telopts, sizeof(char *));
    if (Ambiguous(cpp)) {
	fprintf(stderr,"'%s': ambiguous argument ('send %s ?' for help).\n",
					name, cmd);
	return 0;
    }
D 41
    if (cpp == 0) {
	fprintf(stderr, "'%s': unknown argument ('send %s ?' for help).\n",
E 41
I 41
    if (cpp) {
	val = cpp - telopts;
    } else {
	register char *cp = name;

	while (*cp >= '0' && *cp <= '9') {
	    val *= 10;
	    val += *cp - '0';
	    cp++;
	}
	if (*cp != 0) {
	    fprintf(stderr, "'%s': unknown argument ('send %s ?' for help).\n",
E 41
					name, cmd);
D 41
	return 0;
E 41
I 41
	    return 0;
	} else if (val < 0 || val > 255) {
	    fprintf(stderr, "'%s': bad value ('send %s ?' for help).\n",
					name, cmd);
	    return 0;
	}
E 41
    }
    if (!connected) {
	printf("?Need to be connected first.\n");
	return 0;
    }
D 41
    (*func)(cpp - telopts, 1);
E 41
I 41
    (*func)(val, 1);
E 41
    return 1;
E 35
}
I 35

    static int
send_help()
{
    struct sendlist *s;	/* pointer to current command */
    for (s = Sendlist; s->name; s++) {
	if (s->help)
	    printf("%-15s %s\n", s->name, s->help);
    }
    return(0);
}
E 35

/*
 * The following are the routines and data structures referred
 * to by the arguments to the "toggle" command.
 */

D 35
static
E 35
I 35
    static int
E 35
lclchars()
{
    donelclchars = 1;
    return 1;
}

D 35
static
E 35
I 35
    static int
E 35
togdebug()
{
#ifndef	NOT43
    if (net > 0 &&
	(SetSockOpt(net, SOL_SOCKET, SO_DEBUG, debug)) < 0) {
	    perror("setsockopt (SO_DEBUG)");
    }
#else	/* NOT43 */
    if (debug) {
	if (net > 0 && SetSockOpt(net, SOL_SOCKET, SO_DEBUG, 0, 0) < 0)
	    perror("setsockopt (SO_DEBUG)");
    } else
	printf("Cannot turn off socket debugging\n");
#endif	/* NOT43 */
    return 1;
}


D 35
static int
E 35
I 35
    static int
E 35
togcrlf()
{
    if (crlf) {
	printf("Will send carriage returns as telnet <CR><LF>.\n");
    } else {
	printf("Will send carriage returns as telnet <CR><NUL>.\n");
    }
    return 1;
}

I 21
int binmode;
E 21

D 35
static int
E 35
I 35
    static int
E 35
D 19
togbinary()
E 19
I 19
togbinary(val)
D 35
int val;
E 35
I 35
    int val;
E 35
E 19
{
    donebinarytoggle = 1;

D 17
    if (myopts[TELOPT_BINARY] == 0) {	/* Go into binary mode */
	NET2ADD(IAC, DO);
	NETADD(TELOPT_BINARY);
	printoption("<SENT", doopt, TELOPT_BINARY, 0);
	NET2ADD(IAC, WILL);
	NETADD(TELOPT_BINARY);
	printoption("<SENT", doopt, TELOPT_BINARY, 0);
	hisopts[TELOPT_BINARY] = myopts[TELOPT_BINARY] = 1;
	printf("Negotiating binary mode with remote host.\n");
    } else {				/* Turn off binary mode */
	NET2ADD(IAC, DONT);
	NETADD(TELOPT_BINARY);
	printoption("<SENT", dont, TELOPT_BINARY, 0);
	NET2ADD(IAC, DONT);
	NETADD(TELOPT_BINARY);
	printoption("<SENT", dont, TELOPT_BINARY, 0);
	hisopts[TELOPT_BINARY] = myopts[TELOPT_BINARY] = 0;
E 17
I 17
D 19
    if (did_he_say_will(TELOPT_BINARY) || did_I_say_will(TELOPT_BINARY)) {
	/* leave binary mode */
E 17
	printf("Negotiating network ascii mode with remote host.\n");
I 17
	tel_leave_binary();
E 19
I 19
D 21
    if (my_want_state_is_will(TELOPT_BINARY) ||
	my_want_state_is_do(TELOPT_BINARY)) {
	if (val == 1)
E 21
I 21
    if (val >= 0) {
	binmode = val;
    } else {
	if (my_want_state_is_will(TELOPT_BINARY) &&
				my_want_state_is_do(TELOPT_BINARY)) {
	    binmode = 1;
	} else if (my_want_state_is_wont(TELOPT_BINARY) &&
				my_want_state_is_dont(TELOPT_BINARY)) {
	    binmode = 0;
	}
	val = binmode ? 0 : 1;
    }

    if (val == 1) {
	if (my_want_state_is_will(TELOPT_BINARY) &&
					my_want_state_is_do(TELOPT_BINARY)) {
E 21
	    printf("Already operating in binary mode with remote host.\n");
D 21
	else {
	    /* leave binary mode */
	    printf("Negotiating network ascii mode with remote host.\n");
	    tel_leave_binary();
E 21
I 21
	} else {
	    printf("Negotiating binary mode with remote host.\n");
	    tel_enter_binary(3);
E 21
	}
E 19
D 21
    } else {				/* Turn off binary mode */
D 19
	printf("Negotiating binary mode with remote host.\n");
	tel_enter_binary();
E 19
I 19
	if (val == 0)
E 21
I 21
    } else {
	if (my_want_state_is_wont(TELOPT_BINARY) &&
					my_want_state_is_dont(TELOPT_BINARY)) {
E 21
	    printf("Already in network ascii mode with remote host.\n");
D 21
	else {
	    printf("Negotiating binary mode with remote host.\n");
	    tel_enter_binary();
E 21
I 21
	} else {
	    printf("Negotiating network ascii mode with remote host.\n");
	    tel_leave_binary(3);
E 21
	}
E 19
E 17
    }
    return 1;
}

I 21
D 35
static int
E 35
I 35
    static int
E 35
togrbinary(val)
D 35
int val;
E 35
I 35
    int val;
E 35
{
    donebinarytoggle = 1;
E 21

I 21
    if (val == -1)
	val = my_want_state_is_do(TELOPT_BINARY) ? 0 : 1;
E 21

I 21
    if (val == 1) {
	if (my_want_state_is_do(TELOPT_BINARY)) {
	    printf("Already receiving in binary mode.\n");
	} else {
	    printf("Negotiating binary mode on input.\n");
	    tel_enter_binary(1);
	}
    } else {
	if (my_want_state_is_dont(TELOPT_BINARY)) {
	    printf("Already receiving in network ascii mode.\n");
	} else {
	    printf("Negotiating network ascii mode on input.\n");
	    tel_leave_binary(1);
	}
    }
    return 1;
}

D 35
static int
E 35
I 35
    static int
E 35
togxbinary(val)
D 35
int val;
E 35
I 35
    int val;
E 35
{
    donebinarytoggle = 1;

    if (val == -1)
	val = my_want_state_is_will(TELOPT_BINARY) ? 0 : 1;

    if (val == 1) {
	if (my_want_state_is_will(TELOPT_BINARY)) {
	    printf("Already transmitting in binary mode.\n");
	} else {
	    printf("Negotiating binary mode on output.\n");
	    tel_enter_binary(2);
	}
    } else {
	if (my_want_state_is_wont(TELOPT_BINARY)) {
	    printf("Already transmitting in network ascii mode.\n");
	} else {
	    printf("Negotiating network ascii mode on output.\n");
	    tel_leave_binary(2);
	}
    }
    return 1;
}


E 21
D 35
extern int togglehelp();
I 19
extern int slc_check();
E 35
I 35
D 38
extern int togglehelp P((void));
E 38
I 38
static int togglehelp P((void));
E 38
I 37
D 41
#if	defined(AUTHENTICATE)
E 41
I 41
#if	defined(AUTHENTICATION)
E 41
extern int auth_togdebug P((int));
#endif
D 41
#if	defined(ENCRYPT)
E 41
I 41
D 46
#if	defined(ENCRYPTION)
E 46
I 46
#ifdef	ENCRYPTION
E 46
E 41
extern int EncryptAutoEnc P((int));
extern int EncryptAutoDec P((int));
extern int EncryptDebug P((int));
extern int EncryptVerbose P((int));
D 46
#endif
E 46
I 46
#endif	/* ENCRYPTION */
E 46
E 37
E 35
E 19

struct togglelist {
    char	*name;		/* name of toggle */
    char	*help;		/* help message */
    int		(*handler)();	/* routine to do actual setting */
D 19
    int		dohelp;		/* should we display help information */
E 19
    int		*variable;
    char	*actionexplanation;
};

static struct togglelist Togglelist[] = {
    { "autoflush",
D 19
	"toggle flushing of output when sending interrupt characters",
E 19
I 19
	"flushing of output when sending interrupt characters",
E 19
	    0,
D 19
		1,
		    &autoflush,
			"flush output when sending interrupt characters" },
E 19
I 19
		&autoflush,
		    "flush output when sending interrupt characters" },
E 19
    { "autosynch",
D 19
	"toggle automatic sending of interrupt characters in urgent mode",
E 19
I 19
	"automatic sending of interrupt characters in urgent mode",
E 19
	    0,
D 19
		1,
		    &autosynch,
			"send interrupt characters in urgent mode" },
E 19
I 19
		&autosynch,
		    "send interrupt characters in urgent mode" },
I 37
D 41
#if	defined(AUTHENTICATE)
E 41
I 41
#if	defined(AUTHENTICATION)
E 41
    { "autologin",
	"automatic sending of login and/or authentication info",
	    0,
		&autologin,
		    "send login name and/or authentication information" },
    { "authdebug",
	"Toggle authentication debugging",
	    auth_togdebug,
		0,
		     "print authentication debugging information" },
#endif
D 41
#if	defined(ENCRYPT)
E 41
I 41
D 46
#if	defined(ENCRYPTION)
E 46
I 46
#ifdef	ENCRYPTION
E 46
E 41
    { "autoencrypt",
	"automatic encryption of data stream",
	    EncryptAutoEnc,
		0,
		    "automatically encrypt output" },
    { "autodecrypt",
	"automatic decryption of data stream",
	    EncryptAutoDec,
		0,
		    "automatically decrypt input" },
    { "verbose_encrypt",
	"Toggle verbose encryption output",
	    EncryptVerbose,
		0,
		    "print verbose encryption output" },
    { "encdebug",
	"Toggle encryption debugging",
	    EncryptDebug,
		0,
		    "print encryption debugging information" },
D 46
#endif
E 46
I 46
#endif	/* ENCRYPTION */
E 46
    { "skiprc",
	"don't read ~/.telnetrc file",
	    0,
		&skiprc,
D 42
		    "read ~/.telnetrc file" },
E 42
I 42
		    "skip reading of ~/.telnetrc file" },
E 42
E 37
E 19
    { "binary",
D 19
	"toggle sending and receiving of binary data",
E 19
I 19
	"sending and receiving of binary data",
E 19
	    togbinary,
D 19
		1,
		    0,
			0 },
E 19
I 19
		0,
		    0 },
I 21
    { "inbinary",
	"receiving of binary data",
	    togrbinary,
		0,
		    0 },
    { "outbinary",
	"sending of binary data",
	    togxbinary,
		0,
		    0 },
E 21
E 19
    { "crlf",
D 19
	"toggle sending carriage returns as telnet <CR><LF>",
E 19
I 19
	"sending carriage returns as telnet <CR><LF>",
E 19
	    togcrlf,
D 19
		1,
		    &crlf,
			0 },
E 19
I 19
		&crlf,
		    0 },
E 19
    { "crmod",
D 19
	"toggle mapping of received carriage returns",
E 19
I 19
	"mapping of received carriage returns",
E 19
	    0,
D 19
		1,
		    &crmod,
			"map carriage return on output" },
E 19
I 19
		&crmod,
		    "map carriage return on output" },
E 19
    { "localchars",
D 19
	"toggle local recognition of certain control characters",
E 19
I 19
	"local recognition of certain control characters",
E 19
	    lclchars,
D 19
		1,
		    &localchars,
			"recognize certain control characters" },
    { " ", "", 0, 1 },		/* empty line */
E 19
I 19
		&localchars,
		    "recognize certain control characters" },
I 28
D 35
#ifdef	KERBEROS
    { "kerberos",
	"toggle use of Kerberos authentication",
	    0,
		&kerberized,
		    "use Kerberos authentication" },
#endif
E 35
E 28
    { " ", "", 0 },		/* empty line */
E 19
I 18
#if	defined(unix) && defined(TN3270)
I 22
    { "apitrace",
	"(debugging) toggle tracing of API transactions",
	    0,
		&apitrace,
		    "trace API transactions" },
E 22
    { "cursesdata",
	"(debugging) toggle printing of hexadecimal curses data",
	    0,
D 19
		1,
		    &cursesdata,
			"print hexadecimal representation of curses data" },
E 19
I 19
		&cursesdata,
		    "print hexadecimal representation of curses data" },
E 19
#endif	/* defined(unix) && defined(TN3270) */
E 18
    { "debug",
D 19
	"(debugging) toggle debugging",
E 19
I 19
	"debugging",
E 19
	    togdebug,
D 19
		1,
		    &debug,
			"turn on socket level debugging" },
E 19
I 19
		&debug,
		    "turn on socket level debugging" },
E 19
    { "netdata",
D 19
	"(debugging) toggle printing of hexadecimal network data",
E 19
I 19
	"printing of hexadecimal network data (debugging)",
E 19
	    0,
D 19
		1,
		    &netdata,
			"print hexadecimal representation of network traffic" },
E 19
I 19
		&netdata,
		    "print hexadecimal representation of network traffic" },
    { "prettydump",
	"output of \"netdata\" to user readable format (debugging)",
	    0,
		&prettydump,
		    "print user readable output for \"netdata\"" },
E 19
    { "options",
D 19
	"(debugging) toggle viewing of options processing",
E 19
I 19
	"viewing of options processing (debugging)",
E 19
	    0,
D 19
		1,
		    &showoptions,
			"show option processing" },
E 19
I 19
		&showoptions,
		    "show option processing" },
E 19
I 18
#if	defined(unix)
    { "termdata",
	"(debugging) toggle printing of hexadecimal terminal data",
	    0,
D 19
		1,
		    &termdata,
			"print hexadecimal representation of terminal traffic" },
E 19
I 19
		&termdata,
		    "print hexadecimal representation of terminal traffic" },
E 19
#endif	/* defined(unix) */
E 18
D 19
    { " ", "", 0, 1 },		/* empty line */
E 19
    { "?",
D 19
	"display help information",
	    togglehelp,
		1 },
E 19
I 19
	0,
	    togglehelp },
E 19
    { "help",
D 19
	"display help information",
	    togglehelp,
		0 },
E 19
I 19
	0,
	    togglehelp },
E 19
    { 0 }
};

D 35
static
E 35
I 35
    static int
E 35
togglehelp()
{
    struct togglelist *c;

    for (c = Togglelist; c->name; c++) {
D 19
	if (c->dohelp) {
	    printf("%s\t%s\n", c->name, c->help);
E 19
I 19
	if (c->help) {
	    if (*c->help)
		printf("%-15s toggle %s\n", c->name, c->help);
	    else
		printf("\n");
E 19
	}
    }
I 19
    printf("\n");
    printf("%-15s %s\n", "?", "display help information");
E 19
    return 0;
}

I 19
D 35
static
E 35
I 35
    static void
E 35
settogglehelp(set)
D 35
int set;
E 35
I 35
    int set;
E 35
{
    struct togglelist *c;

    for (c = Togglelist; c->name; c++) {
	if (c->help) {
	    if (*c->help)
		printf("%-15s %s %s\n", c->name, set ? "enable" : "disable",
						c->help);
	    else
		printf("\n");
	}
    }
}

E 19
D 35
static char **
getnexttoggle(name)
char *name;
{
    struct togglelist *c = (struct togglelist *) name;
E 35
I 35
#define	GETTOGGLE(name) (struct togglelist *) \
		genget(name, (char **) Togglelist, sizeof(struct togglelist))
E 35

D 35
    return (char **) (c+1);
}

static struct togglelist *
gettoggle(name)
char *name;
{
    return (struct togglelist *)
			genget(name, (char **) Togglelist, getnexttoggle);
}

static
E 35
I 35
    static int
E 35
toggle(argc, argv)
D 35
int	argc;
char	*argv[];
E 35
I 35
    int  argc;
    char *argv[];
E 35
{
    int retval = 1;
    char *name;
    struct togglelist *c;

    if (argc < 2) {
	fprintf(stderr,
	    "Need an argument to 'toggle' command.  'toggle ?' for help.\n");
	return 0;
    }
    argc--;
    argv++;
    while (argc--) {
	name = *argv++;
D 35
	c = gettoggle(name);
E 35
I 35
	c = GETTOGGLE(name);
E 35
	if (Ambiguous(c)) {
	    fprintf(stderr, "'%s': ambiguous argument ('toggle ?' for help).\n",
					name);
	    return 0;
	} else if (c == 0) {
	    fprintf(stderr, "'%s': unknown argument ('toggle ?' for help).\n",
					name);
	    return 0;
	} else {
	    if (c->variable) {
		*c->variable = !*c->variable;		/* invert it */
		if (c->actionexplanation) {
		    printf("%s %s.\n", *c->variable? "Will" : "Won't",
							c->actionexplanation);
		}
D 12
		printf("%s %s.\n", *c->variable? "Will" : "Won't",
							c->actionexplanation);
E 12
	    }
	    if (c->handler) {
D 19
		retval &= (*c->handler)(c);
E 19
I 19
		retval &= (*c->handler)(-1);
E 19
	    }
	}
    }
    return retval;
}

/*
 * The following perform the "set" command.
 */

I 19
#ifdef	USE_TERMIO
struct termio new_tc = { 0 };
#endif

E 19
struct setlist {
    char *name;				/* name */
    char *help;				/* help information */
I 19
    void (*handler)();
E 19
D 23
    char *charp;			/* where it is located at */
E 23
I 23
D 24
    unsigned char *charp;			/* where it is located at */
E 24
I 24
    cc_t *charp;			/* where it is located at */
E 24
E 23
};

static struct setlist Setlist[] = {
I 30
#ifdef	KLUDGELINEMODE
E 30
D 19
    { "echo", 	"character to toggle local echoing on/off", &echoc },
    { "escape",	"character to escape back to telnet command mode", &escape },
E 19
I 19
    { "echo", 	"character to toggle local echoing on/off", 0, &echoc },
I 30
#endif
E 30
    { "escape",	"character to escape back to telnet command mode", 0, &escape },
I 35
    { "rlogin", "rlogin escape character", 0, &rlogin },
E 35
D 24
    { "tracefile", "file to write trace intormation to", SetNetTrace, NetTraceFile},
E 24
I 24
D 33
    { "tracefile", "file to write trace intormation to", SetNetTrace, (cc_t *)NetTraceFile},
E 33
I 33
    { "tracefile", "file to write trace information to", SetNetTrace, (cc_t *)NetTraceFile},
E 33
E 24
E 19
    { " ", "" },
D 19
    { " ", "The following need 'localchars' to be toggled true", 0 },
    { "erase",	"character to cause an Erase Character", &termEraseChar },
    { "flushoutput", "character to cause an Abort Oubput", &termFlushChar },
    { "interrupt", "character to cause an Interrupt Process", &termIntChar },
    { "kill",	"character to cause an Erase Line", &termKillChar },
    { "quit",	"character to cause a Break", &termQuitChar },
    { "eof",	"character to cause an EOF ", &termEofChar },
E 19
I 19
    { " ", "The following need 'localchars' to be toggled true", 0, 0 },
D 23
#ifndef	CRAY
E 23
D 33
    { "flushoutput", "character to cause an Abort Oubput", 0, termFlushCharp },
E 33
I 33
    { "flushoutput", "character to cause an Abort Output", 0, termFlushCharp },
E 33
D 23
#endif
E 23
    { "interrupt", "character to cause an Interrupt Process", 0, termIntCharp },
    { "quit",	"character to cause an Abort process", 0, termQuitCharp },
    { "eof",	"character to cause an EOF ", 0, termEofCharp },
    { " ", "" },
    { " ", "The following are for local editing in linemode", 0, 0 },
    { "erase",	"character to use to erase a character", 0, termEraseCharp },
    { "kill",	"character to use to erase a line", 0, termKillCharp },
D 23
#ifndef	CRAY
E 23
    { "lnext",	"character to use for literal next", 0, termLiteralNextCharp },
D 30
    { "susp",	"character to cuase a Suspend Process", 0, termSuspCharp },
E 30
I 30
    { "susp",	"character to cause a Suspend Process", 0, termSuspCharp },
E 30
    { "reprint", "character to use for line reprint", 0, termRprntCharp },
    { "worderase", "character to use to erase a word", 0, termWerasCharp },
    { "start",	"character to use for XON", 0, termStartCharp },
D 30
    { "stop",	"character to sue for XOFF", 0, termStopCharp },
E 30
I 30
    { "stop",	"character to use for XOFF", 0, termStopCharp },
    { "forw1",	"alternate end of line character", 0, termForw1Charp },
    { "forw2",	"alternate end of line character", 0, termForw2Charp },
I 33
    { "ayt",	"alternate AYT character", 0, termAytCharp },
E 33
E 30
D 23
#endif
E 23
E 19
    { 0 }
};

I 19
D 33
#ifdef	CRAY
/* Work around compiler bug */
E 33
I 33
#if	defined(CRAY) && !defined(__STDC__)
/* Work around compiler bug in pcc 4.1.5 */
I 35
    void
E 35
E 33
_setlist_init()
{
I 23
D 30
	Setlist[5].charp = &termFlushChar;
E 23
	Setlist[6].charp = &termIntChar;
	Setlist[7].charp = &termQuitChar;
	Setlist[8].charp = &termEofChar;
	Setlist[11].charp = &termEraseChar;
	Setlist[12].charp = &termKillChar;
I 23
	Setlist[13].charp = &termLiteralNextChar;
	Setlist[14].charp = &termSuspChar;
	Setlist[15].charp = &termRprntChar;
	Setlist[16].charp = &termWerasChar;
	Setlist[17].charp = &termStartChar;
	Setlist[18].charp = &termStopChar;
E 30
I 30
#ifndef	KLUDGELINEMODE
D 35
#define	N 4
#else
E 35
#define	N 5
I 35
#else
#define	N 6
E 35
#endif
	Setlist[N+0].charp = &termFlushChar;
	Setlist[N+1].charp = &termIntChar;
	Setlist[N+2].charp = &termQuitChar;
	Setlist[N+3].charp = &termEofChar;
	Setlist[N+6].charp = &termEraseChar;
	Setlist[N+7].charp = &termKillChar;
	Setlist[N+8].charp = &termLiteralNextChar;
	Setlist[N+9].charp = &termSuspChar;
	Setlist[N+10].charp = &termRprntChar;
	Setlist[N+11].charp = &termWerasChar;
	Setlist[N+12].charp = &termStartChar;
	Setlist[N+13].charp = &termStopChar;
	Setlist[N+14].charp = &termForw1Char;
	Setlist[N+15].charp = &termForw2Char;
I 33
	Setlist[N+16].charp = &termAytChar;
E 33
#undef	N
E 30
E 23
}
D 20
#endif	CRAY
E 20
I 20
D 33
#endif	/* CRAY */
E 33
I 33
#endif	/* defined(CRAY) && !defined(__STDC__) */
E 33
E 20

E 19
D 35
static char **
getnextset(name)
char *name;
{
    struct setlist *c = (struct setlist *)name;

    return (char **) (c+1);
}

static struct setlist *
E 35
I 35
    static struct setlist *
E 35
getset(name)
D 35
char *name;
E 35
I 35
    char *name;
E 35
{
D 35
    return (struct setlist *) genget(name, (char **) Setlist, getnextset);
E 35
I 35
    return (struct setlist *)
		genget(name, (char **) Setlist, sizeof(struct setlist));
E 35
}

I 35
    void
E 35
I 30
set_escape_char(s)
D 35
char *s;
E 35
I 35
    char *s;
E 35
{
D 33
	escape = (s && *s) ? special(s) : -1;
E 33
I 33
D 35
	escape = (s && *s) ? special(s) : _POSIX_VDISABLE;
E 33
	printf("escape character is '%s'.\n", control(escape));
E 35
I 35
	if (rlogin != _POSIX_VDISABLE) {
		rlogin = (s && *s) ? special(s) : _POSIX_VDISABLE;
		printf("Telnet rlogin escape character is '%s'.\n",
					control(rlogin));
	} else {
		escape = (s && *s) ? special(s) : _POSIX_VDISABLE;
		printf("Telnet escape character is '%s'.\n", control(escape));
	}
E 35
}

E 30
D 35
static
E 35
I 35
    static int
E 35
setcmd(argc, argv)
D 35
int	argc;
char	*argv[];
E 35
I 35
    int  argc;
    char *argv[];
E 35
{
    int value;
    struct setlist *ct;
I 19
    struct togglelist *c;
E 19

D 19
    /* XXX back we go... sigh */
    if (argc != 3) {
	if ((argc == 2) &&
		    ((!strcmp(argv[1], "?")) || (!strcmp(argv[1], "help")))) {
	    for (ct = Setlist; ct->name; ct++) {
		printf("%s\t%s\n", ct->name, ct->help);
	    }
	    printf("?\tdisplay help information\n");
	} else {
	    printf("Format is 'set Name Value'\n'set ?' for help.\n");
	}
E 19
I 19
    if (argc < 2 || argc > 3) {
	printf("Format is 'set Name Value'\n'set ?' for help.\n");
E 19
	return 0;
    }
I 19
D 35
    if ((argc == 2) &&
		((!strcmp(argv[1], "?")) || (!strcmp(argv[1], "help")))) {
E 35
I 35
    if ((argc == 2) && (isprefix(argv[1], "?") || isprefix(argv[1], "help"))) {
E 35
	for (ct = Setlist; ct->name; ct++)
	    printf("%-15s %s\n", ct->name, ct->help);
	printf("\n");
	settogglehelp(1);
	printf("%-15s %s\n", "?", "display help information");
	return 0;
    }
E 19

    ct = getset(argv[1]);
    if (ct == 0) {
D 19
	fprintf(stderr, "'%s': unknown argument ('set ?' for help).\n",
E 19
I 19
D 35
	c = gettoggle(argv[1]);
E 35
I 35
	c = GETTOGGLE(argv[1]);
E 35
	if (c == 0) {
	    fprintf(stderr, "'%s': unknown argument ('set ?' for help).\n",
E 19
			argv[1]);
I 19
	    return 0;
	} else if (Ambiguous(c)) {
	    fprintf(stderr, "'%s': ambiguous argument ('set ?' for help).\n",
			argv[1]);
	    return 0;
	}
	if (c->variable) {
	    if ((argc == 2) || (strcmp("on", argv[2]) == 0))
		*c->variable = 1;
	    else if (strcmp("off", argv[2]) == 0)
		*c->variable = 0;
	    else {
		printf("Format is 'set togglename [on|off]'\n'set ?' for help.\n");
		return 0;
	    }
	    if (c->actionexplanation) {
		printf("%s %s.\n", *c->variable? "Will" : "Won't",
							c->actionexplanation);
	    }
	}
	if (c->handler)
	    (*c->handler)(1);
    } else if (argc != 3) {
	printf("Format is 'set Name Value'\n'set ?' for help.\n");
E 19
	return 0;
    } else if (Ambiguous(ct)) {
	fprintf(stderr, "'%s': ambiguous argument ('set ?' for help).\n",
			argv[1]);
	return 0;
I 19
    } else if (ct->handler) {
	(*ct->handler)(argv[2]);
D 24
	printf("%s set to \"%s\".\n", ct->name, ct->charp);
E 24
I 24
D 30
	printf("%s set to \"%s\".\n", ct->name, (unsigned char *)ct->charp);
E 30
I 30
	printf("%s set to \"%s\".\n", ct->name, (char *)ct->charp);
E 30
E 24
E 19
    } else {
	if (strcmp("off", argv[2])) {
	    value = special(argv[2]);
	} else {
D 33
	    value = -1;
E 33
I 33
	    value = _POSIX_VDISABLE;
E 33
	}
D 24
	*(ct->charp) = value;
E 24
I 24
	*(ct->charp) = (cc_t)value;
E 24
	printf("%s character is '%s'.\n", ct->name, control(*(ct->charp)));
    }
I 19
    slc_check();
E 19
    return 1;
}
I 19

D 35
static
E 35
I 35
    static int
E 35
unsetcmd(argc, argv)
D 35
int	argc;
char	*argv[];
E 35
I 35
    int  argc;
    char *argv[];
E 35
{
D 30
    int value;
E 30
    struct setlist *ct;
    struct togglelist *c;
    register char *name;

    if (argc < 2) {
	fprintf(stderr,
	    "Need an argument to 'unset' command.  'unset ?' for help.\n");
	return 0;
    }
D 35
    if ((!strcmp(argv[1], "?")) || (!strcmp(argv[1], "help"))) {
E 35
I 35
    if (isprefix(argv[1], "?") || isprefix(argv[1], "help")) {
E 35
	for (ct = Setlist; ct->name; ct++)
	    printf("%-15s %s\n", ct->name, ct->help);
	printf("\n");
	settogglehelp(0);
	printf("%-15s %s\n", "?", "display help information");
	return 0;
    }

    argc--;
    argv++;
    while (argc--) {
	name = *argv++;
	ct = getset(name);
	if (ct == 0) {
D 35
	    c = gettoggle(name);
E 35
I 35
	    c = GETTOGGLE(name);
E 35
	    if (c == 0) {
		fprintf(stderr, "'%s': unknown argument ('unset ?' for help).\n",
			name);
		return 0;
	    } else if (Ambiguous(c)) {
		fprintf(stderr, "'%s': ambiguous argument ('unset ?' for help).\n",
			name);
		return 0;
	    }
	    if (c->variable) {
		*c->variable = 0;
		if (c->actionexplanation) {
		    printf("%s %s.\n", *c->variable? "Will" : "Won't",
							c->actionexplanation);
		}
	    }
	    if (c->handler)
		(*c->handler)(0);
	} else if (Ambiguous(ct)) {
	    fprintf(stderr, "'%s': ambiguous argument ('unset ?' for help).\n",
			name);
	    return 0;
	} else if (ct->handler) {
	    (*ct->handler)(0);
D 30
	    printf("%s reset to \"%s\".\n", ct->name, ct->charp);
E 30
I 30
	    printf("%s reset to \"%s\".\n", ct->name, (char *)ct->charp);
E 30
	} else {
D 30
	    value = -1;
E 30
D 33
	    *(ct->charp) = -1;
E 33
I 33
	    *(ct->charp) = _POSIX_VDISABLE;
E 33
	    printf("%s character is '%s'.\n", ct->name, control(*(ct->charp)));
	}
    }
    return 1;
}
E 19

/*
 * The following are the data structures and routines for the
 * 'mode' command.
 */
I 19
#ifdef	KLUDGELINEMODE
extern int kludgelinemode;
I 30

I 35
    static int
E 35
dokludgemode()
{
    kludgelinemode = 1;
    send_wont(TELOPT_LINEMODE, 1);
    send_dont(TELOPT_SGA, 1);
    send_dont(TELOPT_ECHO, 1);
}
E 30
#endif
E 19

D 35
static
E 35
I 35
    static int
E 35
dolinemode()
{
D 17
    if (hisopts[TELOPT_SGA]) {
	wontoption(TELOPT_SGA, 0);
E 17
I 17
D 19
    if (did_I_say_do(TELOPT_SGA)) {
	send_dont(TELOPT_SGA);
E 17
    }
D 17
    if (hisopts[TELOPT_ECHO]) {
	wontoption(TELOPT_ECHO, 0);
E 17
I 17
    if (did_I_say_do(TELOPT_ECHO)) {
	send_dont(TELOPT_ECHO);
E 17
    }
E 19
I 19
#ifdef	KLUDGELINEMODE
    if (kludgelinemode)
	send_dont(TELOPT_SGA, 1);
#endif
    send_will(TELOPT_LINEMODE, 1);
    send_dont(TELOPT_ECHO, 1);
E 19
    return 1;
}

D 35
static
E 35
I 35
    static int
E 35
docharmode()
{
D 17
    if (!hisopts[TELOPT_SGA]) {
	willoption(TELOPT_SGA, 0);
E 17
I 17
D 19
    if (!did_I_say_do(TELOPT_SGA)) {
	send_do(TELOPT_SGA);
E 19
I 19
#ifdef	KLUDGELINEMODE
    if (kludgelinemode)
	send_do(TELOPT_SGA, 1);
    else
#endif
    send_wont(TELOPT_LINEMODE, 1);
    send_do(TELOPT_ECHO, 1);
    return 1;
}

D 35
setmode(bit)
{
    return dolmmode(bit, 1);
}

clearmode(bit)
{
    return dolmmode(bit, 0);
}

E 35
I 35
    static int
E 35
dolmmode(bit, on)
D 35
int bit, on;
E 35
I 35
    int bit, on;
E 35
{
D 35
    char c;
E 35
I 35
    unsigned char c;
E 35
    extern int linemode;

    if (my_want_state_is_wont(TELOPT_LINEMODE)) {
	printf("?Need to have LINEMODE option enabled first.\n");
	printf("'mode ?' for help.\n");
	return 0;
E 19
E 17
    }
D 17
    if (!hisopts[TELOPT_ECHO]) {
	willoption(TELOPT_ECHO, 0);
E 17
I 17
D 19
    if (!did_I_say_do(TELOPT_ECHO)) {
	send_do(TELOPT_ECHO);
E 17
    }
E 19
I 19

    if (on)
	c = (linemode | bit);
    else
	c = (linemode & ~bit);
    lm_mode(&c, 1, 1);
E 19
    return 1;
}

I 35
    int
setmode(bit)
{
    return dolmmode(bit, 1);
}

    int
clearmode(bit)
{
    return dolmmode(bit, 0);
}

E 35
D 19
static Command Mode_commands[] = {
    { "character",	"character-at-a-time mode",	docharmode, 1, 1 },
    { "line",		"line-by-line mode",		dolinemode, 1, 1 },
E 19
I 19
struct modelist {
	char	*name;		/* command name */
	char	*help;		/* help string */
	int	(*handler)();	/* routine which executes command */
	int	needconnect;	/* Do we need to be connected to execute? */
	int	arg1;
};

extern int modehelp();

static struct modelist ModeList[] = {
    { "character", "Disable LINEMODE option",	docharmode, 1 },
D 23
#ifdef	KLUDEGLINEMODE
    { "",	"(or disable obsolete line-by-line mode)", 0 };
E 23
I 23
#ifdef	KLUDGELINEMODE
    { "",	"(or disable obsolete line-by-line mode)", 0 },
E 23
#endif
    { "line",	"Enable LINEMODE option",	dolinemode, 1 },
D 23
#ifdef	KLUDEGLINEMODE
    { "",	"(or enable obsolete line-by-line mode)", 0 };
E 23
I 23
#ifdef	KLUDGELINEMODE
    { "",	"(or enable obsolete line-by-line mode)", 0 },
E 23
#endif
    { "", "", 0 },
    { "",	"These require the LINEMODE option to be enabled", 0 },
    { "isig",	"Enable signal trapping",	setmode, 1, MODE_TRAPSIG },
    { "+isig",	0,				setmode, 1, MODE_TRAPSIG },
    { "-isig",	"Disable signal trapping",	clearmode, 1, MODE_TRAPSIG },
    { "edit",	"Enable character editing",	setmode, 1, MODE_EDIT },
    { "+edit",	0,				setmode, 1, MODE_EDIT },
    { "-edit",	"Disable character editing",	clearmode, 1, MODE_EDIT },
I 30
    { "softtabs", "Enable tab expansion",	setmode, 1, MODE_SOFT_TAB },
    { "+softtabs", 0,				setmode, 1, MODE_SOFT_TAB },
    { "-softtabs", "Disable character editing",	clearmode, 1, MODE_SOFT_TAB },
    { "litecho", "Enable literal character echo", setmode, 1, MODE_LIT_ECHO },
    { "+litecho", 0,				setmode, 1, MODE_LIT_ECHO },
    { "-litecho", "Disable literal character echo", clearmode, 1, MODE_LIT_ECHO },
E 30
    { "help",	0,				modehelp, 0 },
I 30
#ifdef	KLUDGELINEMODE
    { "kludgeline", 0,				dokludgemode, 1 },
#endif
    { "", "", 0 },
E 30
    { "?",	"Print help information",	modehelp, 0 },
E 19
    { 0 },
};

D 35
static char **
getnextmode(name)
char *name;
{
D 19
    Command *c = (Command *) name;

    return (char **) (c+1);
E 19
I 19
    return (char **) (((struct modelist *)name)+1);
E 19
}
E 35

D 19
static Command *
E 19
I 19
D 35
static struct modelist *
E 19
getmodecmd(name)
char *name;
{
D 19
    return (Command *) genget(name, (char **) Mode_commands, getnextmode);
E 19
I 19
    return (struct modelist *) genget(name, (char **) ModeList, getnextmode);
E 19
}

E 35
I 35
    int
E 35
I 19
modehelp()
{
    struct modelist *mt;

    printf("format is:  'mode Mode', where 'Mode' is one of:\n\n");
    for (mt = ModeList; mt->name; mt++) {
	if (mt->help) {
	    if (*mt->help)
		printf("%-15s %s\n", mt->name, mt->help);
	    else
		printf("\n");
	}
    }
    return 0;
}

E 19
D 35
static
E 35
I 35
#define	GETMODECMD(name) (struct modelist *) \
		genget(name, (char **) ModeList, sizeof(struct modelist))

    static int
E 35
modecmd(argc, argv)
D 35
int	argc;
char	*argv[];
E 35
I 35
    int  argc;
    char *argv[];
E 35
{
D 19
    Command *mt;
E 19
I 19
    struct modelist *mt;
E 19

D 19
    if ((argc != 2) || !strcmp(argv[1], "?") || !strcmp(argv[1], "help")) {
	printf("format is:  'mode Mode', where 'Mode' is one of:\n\n");
	for (mt = Mode_commands; mt->name; mt++) {
	    printf("%s\t%s\n", mt->name, mt->help);
	}
	return 0;
    }
    mt = getmodecmd(argv[1]);
    if (mt == 0) {
E 19
I 19
    if (argc != 2) {
	printf("'mode' command requires an argument\n");
	printf("'mode ?' for help.\n");
D 35
    } else if ((mt = getmodecmd(argv[1])) == 0) {
E 35
I 35
    } else if ((mt = GETMODECMD(argv[1])) == 0) {
E 35
E 19
	fprintf(stderr, "Unknown mode '%s' ('mode ?' for help).\n", argv[1]);
D 19
	return 0;
E 19
    } else if (Ambiguous(mt)) {
	fprintf(stderr, "Ambiguous mode '%s' ('mode ?' for help).\n", argv[1]);
D 19
	return 0;
    } else {
	(*mt->handler)();
E 19
I 19
    } else if (mt->needconnect && !connected) {
	printf("?Need to be connected first.\n");
	printf("'mode ?' for help.\n");
    } else if (mt->handler) {
	return (*mt->handler)(mt->arg1);
E 19
    }
D 19
    return 1;
E 19
I 19
    return 0;
E 19
}

/*
 * The following data structures and routines implement the
 * "display" command.
 */

D 35
static
E 35
I 35
    static int
E 35
display(argc, argv)
D 35
int	argc;
char	*argv[];
E 35
I 35
    int  argc;
    char *argv[];
E 35
{
I 35
    struct togglelist *tl;
    struct setlist *sl;

E 35
#define	dotog(tl)	if (tl->variable && tl->actionexplanation) { \
			    if (*tl->variable) { \
				printf("will"); \
			    } else { \
				printf("won't"); \
			    } \
			    printf(" %s.\n", tl->actionexplanation); \
			}

#define	doset(sl)   if (sl->name && *sl->name != ' ') { \
D 19
			printf("[%s]\t%s.\n", control(*sl->charp), sl->name); \
E 19
I 19
			if (sl->handler == 0) \
			    printf("%-15s [%s]\n", sl->name, control(*sl->charp)); \
			else \
D 30
			    printf("%-15s \"%s\"\n", sl->name, sl->charp); \
E 30
I 30
			    printf("%-15s \"%s\"\n", sl->name, (char *)sl->charp); \
E 30
E 19
		    }

D 35
    struct togglelist *tl;
    struct setlist *sl;

E 35
    if (argc == 1) {
	for (tl = Togglelist; tl->name; tl++) {
	    dotog(tl);
	}
	printf("\n");
	for (sl = Setlist; sl->name; sl++) {
	    doset(sl);
	}
    } else {
	int i;

	for (i = 1; i < argc; i++) {
	    sl = getset(argv[i]);
D 35
	    tl = gettoggle(argv[i]);
E 35
I 35
	    tl = GETTOGGLE(argv[i]);
E 35
	    if (Ambiguous(sl) || Ambiguous(tl)) {
		printf("?Ambiguous argument '%s'.\n", argv[i]);
		return 0;
	    } else if (!sl && !tl) {
		printf("?Unknown argument '%s'.\n", argv[i]);
		return 0;
	    } else {
		if (tl) {
		    dotog(tl);
		}
		if (sl) {
		    doset(sl);
		}
	    }
	}
    }
I 19
/*@*/optionstatus();
I 35
D 41
#if	defined(ENCRYPT)
E 41
I 41
D 46
#if	defined(ENCRYPTION)
E 46
I 46
#ifdef	ENCRYPTION
E 46
E 41
    EncryptStatus();
D 46
#endif
E 46
I 46
#endif	/* ENCRYPTION */
E 46
E 35
E 19
    return 1;
#undef	doset
#undef	dotog
}

/*
 * The following are the data structures, and many of the routines,
 * relating to command processing.
 */

/*
 * Set the escape character.
 */
D 35
static
E 35
I 35
	static int
E 35
setescape(argc, argv)
	int argc;
	char *argv[];
{
	register char *arg;
	char buf[50];

	printf(
	    "Deprecated usage - please use 'set escape%s%s' in the future.\n",
				(argc > 2)? " ":"", (argc > 2)? argv[1]: "");
	if (argc > 2)
		arg = argv[1];
	else {
		printf("new escape character: ");
D 6
		gets(buf);
E 6
I 6
D 35
		(void) gets(buf);
E 35
I 35
		(void) fgets(buf, sizeof(buf), stdin);
E 35
E 6
		arg = buf;
	}
	if (arg[0] != '\0')
		escape = arg[0];
	if (!In3270) {
		printf("Escape character is '%s'.\n", control(escape));
	}
D 6
	fflush(stdout);
E 6
I 6
	(void) fflush(stdout);
E 6
	return 1;
}

D 35
/*VARARGS*/
static
E 35
I 35
    /*VARARGS*/
    static int
E 35
togcrmod()
{
    crmod = !crmod;
    printf("Deprecated usage - please use 'toggle crmod' in the future.\n");
    printf("%s map carriage return on output.\n", crmod ? "Will" : "Won't");
D 6
    fflush(stdout);
E 6
I 6
    (void) fflush(stdout);
E 6
    return 1;
}

D 35
/*VARARGS*/
E 35
I 35
    /*VARARGS*/
    int
E 35
suspend()
{
I 19
#ifdef	SIGTSTP
E 19
D 16
	setcommandmode();
E 16
I 16
    setcommandmode();
E 16
D 19
#if	defined(unix)
E 19
I 16
    {
D 30
	long oldrows, oldcols, newrows, newcols;
E 30
I 30
	long oldrows, oldcols, newrows, newcols, err;
E 30

D 30
	TerminalWindowSize(&oldrows, &oldcols);
E 30
I 30
D 41
	err = TerminalWindowSize(&oldrows, &oldcols);
E 41
I 41
	err = (TerminalWindowSize(&oldrows, &oldcols) == 0) ? 1 : 0;
E 41
E 30
E 16
D 6
	kill(0, SIGTSTP);
E 6
I 6
	(void) kill(0, SIGTSTP);
I 16
D 30
	TerminalWindowSize(&newrows, &newcols);
	if ((oldrows != newrows) || (oldcols != newcols)) {
	    if (connected) {
E 30
I 30
D 41
	err += TerminalWindowSize(&newrows, &newcols);
	if (connected && !err &&
	    ((oldrows != newrows) || (oldcols != newcols))) {
E 41
I 41
	/*
	 * If we didn't get the window size before the SUSPEND, but we
D 51
	 * can get them now (???), then send the NAWS to make sure that
E 51
I 51
	 * can get them now (?), then send the NAWS to make sure that
E 51
	 * we are set up for the right window size.
	 */
	if (TerminalWindowSize(&newrows, &newcols) && connected &&
	    (err || ((oldrows != newrows) || (oldcols != newcols)))) {
E 41
E 30
		sendnaws();
D 30
	    }
E 30
	}
    }
E 16
E 6
D 19
#endif	/* defined(unix) */
E 19
D 16
	/* reget parameters in case they were changed */
	TerminalSaveState();
	setconnmode();
	return 1;
E 16
I 16
    /* reget parameters in case they were changed */
    TerminalSaveState();
D 19
    setconnmode();
E 19
I 19
    setconnmode(0);
#else
    printf("Suspend is not supported.  Try the '!' command instead\n");
#endif
E 19
    return 1;
E 16
}

I 19
#if	!defined(TN3270)
I 30
D 35
/*ARGSUSED*/
E 35
I 35
    /*ARGSUSED*/
    int
E 35
E 30
D 23
#ifdef	CRAY
#define	vfork	fork
#endif
E 23
shell(argc, argv)
D 35
int argc;
char *argv[];
E 35
I 35
    int argc;
    char *argv[];
E 35
{
I 41
    long oldrows, oldcols, newrows, newcols, err;

E 41
D 35
    extern char *rindex();
D 30
    char cmdbuf[256];
E 30

E 35
    setcommandmode();
I 41

    err = (TerminalWindowSize(&oldrows, &oldcols) == 0) ? 1 : 0;
E 41
    switch(vfork()) {
    case -1:
	perror("Fork failed\n");
	break;

    case 0:
	{
	    /*
	     * Fire up the shell in the child.
	     */
D 35
	    register char *shell, *shellname;
E 35
I 35
	    register char *shellp, *shellname;
D 51
	    extern char *rindex();
E 51
I 51
	    extern char *strrchr();
E 51
E 35

D 35
	    shell = getenv("SHELL");
	    if (shell == NULL)
		shell = "/bin/sh";
	    if ((shellname = rindex(shell, '/')) == 0)
		shellname = shell;
E 35
I 35
	    shellp = getenv("SHELL");
	    if (shellp == NULL)
		shellp = "/bin/sh";
D 51
	    if ((shellname = rindex(shellp, '/')) == 0)
E 51
I 51
	    if ((shellname = strrchr(shellp, '/')) == 0)
E 51
		shellname = shellp;
E 35
	    else
		shellname++;
	    if (argc > 1)
D 35
		execl(shell, shellname, "-c", &saveline[1], 0);
E 35
I 35
		execl(shellp, shellname, "-c", &saveline[1], 0);
E 35
	    else
D 35
		execl(shell, shellname, 0);
E 35
I 35
		execl(shellp, shellname, 0);
E 35
	    perror("Execl");
	    _exit(1);
	}
    default:
D 30
	    wait((int *)0);	/* Wait for the shell to complete */
E 30
I 30
	    (void)wait((int *)0);	/* Wait for the shell to complete */
I 41

	    if (TerminalWindowSize(&newrows, &newcols) && connected &&
		(err || ((oldrows != newrows) || (oldcols != newcols)))) {
		    sendnaws();
	    }
	    break;
E 41
E 30
    }
I 35
    return 1;
E 35
}
I 44
#else	/* !defined(TN3270) */
extern int shell();
E 44
#endif	/* !defined(TN3270) */

E 19
D 35
/*VARARGS*/
static
E 35
I 35
    /*VARARGS*/
    static
E 35
bye(argc, argv)
D 35
int	argc;		/* Number of arguments */
char	*argv[];	/* arguments */
E 35
I 35
    int  argc;		/* Number of arguments */
    char *argv[];	/* arguments */
E 35
{
I 35
    extern int resettermname;

E 35
    if (connected) {
D 6
	shutdown(net, 2);
E 6
I 6
	(void) shutdown(net, 2);
E 6
	printf("Connection closed.\n");
D 6
	NetClose(net);
E 6
I 6
	(void) NetClose(net);
E 6
	connected = 0;
I 35
	resettermname = 1;
D 41
#if	defined(AUTHENTICATE) || defined(ENCRYPT)
E 41
I 41
#if	defined(AUTHENTICATION) || defined(ENCRYPTION)
E 41
	auth_encrypt_connect(connected);
D 46
#endif
E 46
I 46
#endif	/* defined(AUTHENTICATION) || defined(ENCRYPTION) */
E 46
E 35
	/* reset options */
	tninit();
#if	defined(TN3270)
	SetIn3270();		/* Get out of 3270 mode */
#endif	/* defined(TN3270) */
    }
    if ((argc != 2) || (strcmp(argv[1], "fromquit") != 0)) {
	longjmp(toplevel, 1);
	/* NOTREACHED */
    }
    return 1;			/* Keep lint, etc., happy */
}

/*VARARGS*/
quit()
{
	(void) call(bye, "bye", "fromquit", 0);
	Exit(0);
D 6
	/*NOTREACHED*/
E 6
D 30
	return 1;			/* just to keep lint happy */
E 30
I 30
	/*NOTREACHED*/
E 30
}
I 35

/*VARARGS*/
	int
logout()
{
	send_do(TELOPT_LOGOUT, 1);
	(void) netflush();
	return 1;
}

E 35
I 19

/*
 * The SLC command.
 */
E 19

I 19
struct slclist {
	char	*name;
	char	*help;
D 35
	int	(*handler)();
E 35
I 35
	void	(*handler)();
E 35
	int	arg;
};

D 35
extern int slc_help();
extern int slc_mode_export(), slc_mode_import(), slcstate();
E 35
I 35
D 38
extern void slc_help();
E 38
I 38
static void slc_help();
E 38
E 35

struct slclist SlcList[] = {
    { "export",	"Use local special character definitions",
						slc_mode_export,	0 },
    { "import",	"Use remote special character definitions",
						slc_mode_import,	1 },
    { "check",	"Verify remote special character definitions",
						slc_mode_import,	0 },
    { "help",	0,				slc_help,		0 },
    { "?",	"Print help information",	slc_help,		0 },
    { 0 },
};

D 35
static
E 35
I 35
    static void
E 35
slc_help()
{
    struct slclist *c;

    for (c = SlcList; c->name; c++) {
	if (c->help) {
	    if (*c->help)
		printf("%-15s %s\n", c->name, c->help);
	    else
		printf("\n");
	}
    }
}

D 35
static char **
getnextslc(name)
char *name;
{
    return (char **)(((struct slclist *)name)+1);
}

static struct slclist *
E 35
I 35
    static struct slclist *
E 35
getslc(name)
D 35
char *name;
E 35
I 35
    char *name;
E 35
{
D 35
    return (struct slclist *)genget(name, (char **) SlcList, getnextslc);
E 35
I 35
    return (struct slclist *)
		genget(name, (char **) SlcList, sizeof(struct slclist));
E 35
}

D 35
static
E 35
I 35
    static
E 35
slccmd(argc, argv)
D 35
int	argc;
char	*argv[];
E 35
I 35
    int  argc;
    char *argv[];
E 35
{
    struct slclist *c;

    if (argc != 2) {
	fprintf(stderr,
	    "Need an argument to 'slc' command.  'slc ?' for help.\n");
	return 0;
    }
    c = getslc(argv[1]);
    if (c == 0) {
D 51
        fprintf(stderr, "'%s': unknown argument ('slc ?' for help).\n",
E 51
I 51
	fprintf(stderr, "'%s': unknown argument ('slc ?' for help).\n",
E 51
    				argv[1]);
D 51
        return 0;
E 51
I 51
	return 0;
E 51
    }
    if (Ambiguous(c)) {
D 51
        fprintf(stderr, "'%s': ambiguous argument ('slc ?' for help).\n",
E 51
I 51
	fprintf(stderr, "'%s': ambiguous argument ('slc ?' for help).\n",
E 51
    				argv[1]);
D 51
        return 0;
E 51
I 51
	return 0;
E 51
    }
    (*c->handler)(c->arg);
    slcstate();
    return 1;
}
I 30

/*
 * The ENVIRON command.
 */
E 30

I 30
struct envlist {
	char	*name;
	char	*help;
D 35
	int	(*handler)();
E 35
I 35
	void	(*handler)();
E 35
	int	narg;
};

D 35
extern struct env_lst *env_define();
extern int env_undefine();
extern int env_export(), env_unexport();
D 33
extern int env_list(), env_help();
E 33
I 33
extern int env_send(), env_list(), env_help();
E 35
I 35
extern struct env_lst *
	env_define P((unsigned char *, unsigned char *));
extern void
	env_undefine P((unsigned char *)),
	env_export P((unsigned char *)),
	env_unexport P((unsigned char *)),
	env_send P((unsigned char *)),
I 43
D 49
#ifdef	ENV_HACK
E 49
I 49
#if defined(OLD_ENVIRON) && defined(ENV_HACK)
E 49
	env_varval P((unsigned char *)),
#endif
E 43
D 38
	env_list P((void)),
E 38
I 38
	env_list P((void));
static void
E 38
	env_help P((void));
E 35
E 33

struct envlist EnvList[] = {
    { "define",	"Define an environment variable",
D 35
						(int (*)())env_define,	2 },
E 35
I 35
						(void (*)())env_define,	2 },
E 35
    { "undefine", "Undefine an environment variable",
						env_undefine,	1 },
    { "export",	"Mark an environment variable for automatic export",
						env_export,	1 },
D 35
    { "unexport", "Dont mark an environment variable for automatic export",
E 35
I 35
    { "unexport", "Don't mark an environment variable for automatic export",
E 35
						env_unexport,	1 },
I 33
    { "send",	"Send an environment variable", env_send,	1 },
E 33
    { "list",	"List the current environment variables",
						env_list,	0 },
I 43
D 49
#ifdef	ENV_HACK
E 49
I 49
#if defined(OLD_ENVIRON) && defined(ENV_HACK)
E 49
    { "varval", "Reverse VAR and VALUE (auto, right, wrong, status)",
						env_varval,    1 },
#endif
E 43
    { "help",	0,				env_help,		0 },
    { "?",	"Print help information",	env_help,		0 },
    { 0 },
};

D 35
static
E 35
I 35
    static void
E 35
env_help()
{
    struct envlist *c;

    for (c = EnvList; c->name; c++) {
	if (c->help) {
	    if (*c->help)
		printf("%-15s %s\n", c->name, c->help);
	    else
		printf("\n");
	}
    }
}

D 35
static char **
getnextenv(name)
char *name;
{
    return (char **)(((struct envlist *)name)+1);
}

static struct envlist *
E 35
I 35
    static struct envlist *
E 35
getenvcmd(name)
D 35
char *name;
E 35
I 35
    char *name;
E 35
{
D 35
    return (struct envlist *)genget(name, (char **) EnvList, getnextenv);
E 35
I 35
    return (struct envlist *)
		genget(name, (char **) EnvList, sizeof(struct envlist));
E 35
}

env_cmd(argc, argv)
D 35
int	argc;
char	*argv[];
E 35
I 35
    int  argc;
    char *argv[];
E 35
{
    struct envlist *c;

    if (argc < 2) {
	fprintf(stderr,
	    "Need an argument to 'environ' command.  'environ ?' for help.\n");
	return 0;
    }
    c = getenvcmd(argv[1]);
    if (c == 0) {
D 51
        fprintf(stderr, "'%s': unknown argument ('environ ?' for help).\n",
E 51
I 51
	fprintf(stderr, "'%s': unknown argument ('environ ?' for help).\n",
E 51
    				argv[1]);
D 51
        return 0;
E 51
I 51
	return 0;
E 51
    }
    if (Ambiguous(c)) {
D 51
        fprintf(stderr, "'%s': ambiguous argument ('environ ?' for help).\n",
E 51
I 51
	fprintf(stderr, "'%s': ambiguous argument ('environ ?' for help).\n",
E 51
    				argv[1]);
D 51
        return 0;
E 51
I 51
	return 0;
E 51
    }
    if (c->narg + 2 != argc) {
	fprintf(stderr,
	    "Need %s%d argument%s to 'environ %s' command.  'environ ?' for help.\n",
		c->narg < argc + 2 ? "only " : "",
		c->narg, c->narg == 1 ? "" : "s", c->name);
	return 0;
    }
D 35
    (void)(*c->handler)(argv[2], argv[3]);
E 35
I 35
    (*c->handler)(argv[2], argv[3]);
E 35
    return 1;
}

struct env_lst {
	struct env_lst *next;	/* pointer to next structure */
D 41
	struct env_lst *prev;	/* pointer to next structure */
E 41
I 41
	struct env_lst *prev;	/* pointer to previous structure */
E 41
D 35
	char *var;		/* pointer to variable name */
	char *value;		/* pointer to varialbe value */
E 35
I 35
	unsigned char *var;	/* pointer to variable name */
D 41
	unsigned char *value;	/* pointer to varialbe value */
E 41
I 41
	unsigned char *value;	/* pointer to variable value */
E 41
E 35
	int export;		/* 1 -> export with default list of variables */
I 41
	int welldefined;	/* A well defined variable */
E 41
};

struct env_lst envlisthead;

D 35
struct env_lst *
E 35
I 35
	struct env_lst *
E 35
env_find(var)
I 33
D 35
char *var;
E 35
I 35
	unsigned char *var;
E 35
E 33
{
	register struct env_lst *ep;

	for (ep = envlisthead.next; ep; ep = ep->next) {
D 35
		if (strcmp(ep->var, var) == 0)
E 35
I 35
		if (strcmp((char *)ep->var, (char *)var) == 0)
E 35
			return(ep);
	}
	return(NULL);
}

I 35
	void
E 35
env_init()
{
D 35
	extern char **environ, *index();
E 35
I 35
	extern char **environ;
E 35
	register char **epp, *cp;
	register struct env_lst *ep;
I 35
D 51
	extern char *index();
E 51
I 51
	extern char *strchr();
E 51
E 35

	for (epp = environ; *epp; epp++) {
D 51
		if (cp = index(*epp, '=')) {
E 51
I 51
		if (cp = strchr(*epp, '=')) {
E 51
			*cp = '\0';
D 35
			ep = env_define(*epp, cp+1);
E 35
I 35
			ep = env_define((unsigned char *)*epp,
					(unsigned char *)cp+1);
E 35
			ep->export = 0;
			*cp = '=';
		}
	}
	/*
	 * Special case for DISPLAY variable.  If it is ":0.0" or
	 * "unix:0.0", we have to get rid of "unix" and insert our
	 * hostname.
	 */
D 35
	if ((ep = env_find("DISPLAY")) &&
	    ((*ep->value == ':') || (strncmp(ep->value, "unix:", 5) == 0))) {
E 35
I 35
	if ((ep = env_find("DISPLAY"))
	    && ((*ep->value == ':')
D 51
	        || (strncmp((char *)ep->value, "unix:", 5) == 0))) {
E 51
I 51
		|| (strncmp((char *)ep->value, "unix:", 5) == 0))) {
E 51
E 35
		char hbuf[256+1];
D 35
		char *cp2 = index(ep->value, ':');
E 35
I 35
D 51
		char *cp2 = index((char *)ep->value, ':');
E 51
I 51
		char *cp2 = strchr((char *)ep->value, ':');
E 51
E 35

		gethostname(hbuf, 256);
		hbuf[256] = '\0';
		cp = (char *)malloc(strlen(hbuf) + strlen(cp2) + 1);
D 35
		sprintf(cp, "%s%s", hbuf, cp2);
E 35
I 35
		sprintf((char *)cp, "%s%s", hbuf, cp2);
E 35
		free(ep->value);
D 35
		ep->value = cp;
E 35
I 35
		ep->value = (unsigned char *)cp;
E 35
	}
I 31
D 33
#ifdef notdef
E 33
E 31
	/*
	 * If USER is not defined, but LOGNAME is, then add
D 33
	 * USER with the value from LOGNAME.
E 33
I 33
	 * USER with the value from LOGNAME.  By default, we
	 * don't export the USER variable.
E 33
	 */
D 33
	if ((env_find("USER") == NULL) && (ep = env_find("LOGNAME")))
E 33
I 33
	if ((env_find("USER") == NULL) && (ep = env_find("LOGNAME"))) {
E 33
D 35
		env_define("USER", ep->value);
D 33
	env_export("USER");
I 31
#endif
E 33
I 33
		env_unexport("USER");
E 35
I 35
		env_define((unsigned char *)"USER", ep->value);
		env_unexport((unsigned char *)"USER");
E 35
	}
E 33
E 31
D 35
	env_export("DISPLAY");
	env_export("PRINTER");
E 35
I 35
	env_export((unsigned char *)"DISPLAY");
	env_export((unsigned char *)"PRINTER");
E 35
}

D 35
struct env_lst *
E 35
I 35
	struct env_lst *
E 35
env_define(var, value)
D 35
char *var, *value;
E 35
I 35
	unsigned char *var, *value;
E 35
{
	register struct env_lst *ep;
D 33
	extern char *savestr();
E 33
I 33
D 35
	extern char *strdup();
E 35
E 33

	if (ep = env_find(var)) {
		if (ep->var)
			free(ep->var);
		if (ep->value)
			free(ep->value);
	} else {
		ep = (struct env_lst *)malloc(sizeof(struct env_lst));
D 32
		ep->export = 1;
E 32
		ep->next = envlisthead.next;
		envlisthead.next = ep;
		ep->prev = &envlisthead;
		if (ep->next)
			ep->next->prev = ep;
	}
I 41
	ep->welldefined = opt_welldefined(var);
E 41
I 32
	ep->export = 1;
E 32
D 33
	ep->var = savestr(var);
	ep->value = savestr(value);
E 33
I 33
D 35
	ep->var = strdup(var);
	ep->value = strdup(value);
E 35
I 35
	ep->var = (unsigned char *)strdup((char *)var);
	ep->value = (unsigned char *)strdup((char *)value);
E 35
E 33
	return(ep);
}

I 35
	void
E 35
env_undefine(var)
D 35
char *var;
E 35
I 35
	unsigned char *var;
E 35
{
	register struct env_lst *ep;

	if (ep = env_find(var)) {
		ep->prev->next = ep->next;
D 33
		ep->next->prev = ep->prev;
E 33
I 33
		if (ep->next)
			ep->next->prev = ep->prev;
E 33
		if (ep->var)
			free(ep->var);
		if (ep->value)
			free(ep->value);
		free(ep);
	}
}

I 35
	void
E 35
env_export(var)
D 35
char *var;
E 35
I 35
	unsigned char *var;
E 35
{
	register struct env_lst *ep;

	if (ep = env_find(var))
		ep->export = 1;
}

I 35
	void
E 35
env_unexport(var)
D 35
char *var;
E 35
I 35
	unsigned char *var;
E 35
{
	register struct env_lst *ep;

	if (ep = env_find(var))
		ep->export = 0;
}

I 35
	void
E 35
I 33
env_send(var)
D 35
char *var;
E 35
I 35
	unsigned char *var;
E 35
{
	register struct env_lst *ep;

D 49
        if (my_state_is_wont(TELOPT_ENVIRON)) {
E 49
I 49
D 51
        if (my_state_is_wont(TELOPT_NEW_ENVIRON)
E 51
I 51
	if (my_state_is_wont(TELOPT_NEW_ENVIRON)
E 51
#ifdef	OLD_ENVIRON
	    && my_state_is_wont(TELOPT_OLD_ENVIRON)
#endif
		) {
E 49
		fprintf(stderr,
		    "Cannot send '%s': Telnet ENVIRON option not enabled\n",
									var);
		return;
	}
	ep = env_find(var);
	if (ep == 0) {
		fprintf(stderr, "Cannot send '%s': variable not defined\n",
									var);
		return;
	}
	env_opt_start_info();
	env_opt_add(ep->var);
	env_opt_end(0);
}

I 35
	void
E 35
E 33
env_list()
{
	register struct env_lst *ep;

	for (ep = envlisthead.next; ep; ep = ep->next) {
		printf("%c %-20s %s\n", ep->export ? '*' : ' ',
					ep->var, ep->value);
	}
}

D 35
char *
E 35
I 35
	unsigned char *
E 35
D 41
env_default(init)
E 41
I 41
env_default(init, welldefined)
E 41
I 35
	int init;
E 35
{
	static struct env_lst *nep = NULL;

	if (init) {
		nep = &envlisthead;
		return;
	}
	if (nep) {
		while (nep = nep->next) {
D 41
			if (nep->export)
E 41
I 41
			if (nep->export && (nep->welldefined == welldefined))
E 41
				return(nep->var);
		}
	}
	return(NULL);
}

D 35
char *
E 35
I 35
	unsigned char *
E 35
env_getvalue(var)
D 35
char *var;
E 35
I 35
	unsigned char *var;
E 35
{
	register struct env_lst *ep;

	if (ep = env_find(var))
		return(ep->value);
	return(NULL);
}

I 43
D 49
#ifdef	ENV_HACK
E 49
I 49
#if defined(OLD_ENVIRON) && defined(ENV_HACK)
E 49
	void
env_varval(what)
	unsigned char *what;
{
D 49
	extern int env_var, env_value, env_auto;
	int len = strlen(what);
E 49
I 49
	extern int old_env_var, old_env_value, env_auto;
	int len = strlen((char *)what);
E 49

	if (len == 0)
		goto unknown;

D 49
	if (strncasecmp(what, "status", len) == 0) {
E 49
I 49
	if (strncasecmp((char *)what, "status", len) == 0) {
E 49
		if (env_auto)
			printf("%s%s", "VAR and VALUE are/will be ",
					"determined automatically\n");
D 49
		if (env_var == ENV_VAR)
E 49
I 49
		if (old_env_var == OLD_ENV_VAR)
E 49
			printf("VAR and VALUE set to correct definitions\n");
		else
			printf("VAR and VALUE definitions are reversed\n");
D 49
	} else if (strncasecmp(what, "auto", len) == 0) {
E 49
I 49
	} else if (strncasecmp((char *)what, "auto", len) == 0) {
E 49
		env_auto = 1;
D 49
		env_var = ENV_VALUE;
		env_value = ENV_VAR;
	} else if (strncasecmp(what, "right", len) == 0) {
E 49
I 49
		old_env_var = OLD_ENV_VALUE;
		old_env_value = OLD_ENV_VAR;
	} else if (strncasecmp((char *)what, "right", len) == 0) {
E 49
		env_auto = 0;
D 49
		env_var = ENV_VAR;
		env_value = ENV_VALUE;
	} else if (strncasecmp(what, "wrong", len) == 0) {
E 49
I 49
		old_env_var = OLD_ENV_VAR;
		old_env_value = OLD_ENV_VALUE;
	} else if (strncasecmp((char *)what, "wrong", len) == 0) {
E 49
		env_auto = 0;
D 49
		env_var = ENV_VALUE;
		env_value = ENV_VAR;
E 49
I 49
		old_env_var = OLD_ENV_VALUE;
		old_env_value = OLD_ENV_VAR;
E 49
	} else {
unknown:
		printf("Unknown \"varval\" command. (\"auto\", \"right\", \"wrong\", \"status\")\n");
	}
}
#endif

E 43
I 33
D 35
#ifdef	NO_STRDUP
E 33
char *
D 33
savestr(s)
E 33
I 33
strdup(s)
E 33
register char *s;
E 35
I 35
D 41
#if	defined(AUTHENTICATE)
E 41
I 41
#if	defined(AUTHENTICATION)
E 41
/*
 * The AUTHENTICATE command.
 */

struct authlist {
	char	*name;
	char	*help;
	int	(*handler)();
	int	narg;
};

extern int
D 50
	auth_enable P((int)),
	auth_disable P((int)),
E 50
I 50
	auth_enable P((char *)),
	auth_disable P((char *)),
E 50
D 38
	auth_status P((void)),
E 38
I 38
	auth_status P((void));
static int
E 38
D 37
	auth_togdebug P((void)),
E 37
	auth_help P((void));

struct authlist AuthList[] = {
    { "status",	"Display current status of authentication information",
						auth_status,	0 },
D 37
    { "debug",	"Toggle authentication debugging",
						auth_togdebug,	0 },
E 37
    { "disable", "Disable an authentication type ('auth disable ?' for more)",
						auth_disable,	1 },
    { "enable", "Enable an authentication type ('auth enable ?' for more)",
						auth_enable,	1 },
    { "help",	0,				auth_help,		0 },
    { "?",	"Print help information",	auth_help,		0 },
    { 0 },
};

    static int
auth_help()
E 35
{
D 35
	register char *ret;
	if (ret = (char *)malloc(strlen(s)+1))
		strcpy(ret, s);
	return(ret);
E 35
I 35
    struct authlist *c;

    for (c = AuthList; c->name; c++) {
	if (c->help) {
	    if (*c->help)
		printf("%-15s %s\n", c->name, c->help);
	    else
		printf("\n");
	}
    }
    return 0;
E 35
}
I 35

auth_cmd(argc, argv)
    int  argc;
    char *argv[];
{
    struct authlist *c;

I 50
    if (argc < 2) {
	fprintf(stderr,
	    "Need an argument to 'auth' command.  'auth ?' for help.\n");
	return 0;
    }

E 50
    c = (struct authlist *)
		genget(argv[1], (char **) AuthList, sizeof(struct authlist));
    if (c == 0) {
D 51
        fprintf(stderr, "'%s': unknown argument ('auth ?' for help).\n",
E 51
I 51
	fprintf(stderr, "'%s': unknown argument ('auth ?' for help).\n",
E 51
    				argv[1]);
D 51
        return 0;
E 51
I 51
	return 0;
E 51
    }
    if (Ambiguous(c)) {
D 51
        fprintf(stderr, "'%s': ambiguous argument ('auth ?' for help).\n",
E 51
I 51
	fprintf(stderr, "'%s': ambiguous argument ('auth ?' for help).\n",
E 51
    				argv[1]);
D 51
        return 0;
E 51
I 51
	return 0;
E 51
    }
    if (c->narg + 2 != argc) {
	fprintf(stderr,
	    "Need %s%d argument%s to 'auth %s' command.  'auth ?' for help.\n",
		c->narg < argc + 2 ? "only " : "",
		c->narg, c->narg == 1 ? "" : "s", c->name);
	return 0;
    }
    return((*c->handler)(argv[2], argv[3]));
}
E 35
I 33
#endif
E 33

E 30
E 19
I 14
D 35
#if	defined(unix)
I 30
#ifdef notdef
E 35
I 35
D 41
#if	defined(ENCRYPT)
E 41
I 41
D 46
#if	defined(ENCRYPTION)
E 46
I 46
#ifdef	ENCRYPTION
E 46
E 41
E 35
E 30
E 14
/*
I 14
D 35
 * Some information about our file descriptors.
E 35
I 35
 * The ENCRYPT command.
E 35
 */

D 35
char *
decodeflags(mask)
int mask;
E 35
I 35
struct encryptlist {
	char	*name;
	char	*help;
	int	(*handler)();
	int	needconnect;
	int	minarg;
	int	maxarg;
};

extern int
	EncryptEnable P((char *, char *)),
I 37
	EncryptDisable P((char *, char *)),
E 37
	EncryptType P((char *, char *)),
	EncryptStart P((char *)),
	EncryptStartInput P((void)),
	EncryptStartOutput P((void)),
	EncryptStop P((char *)),
	EncryptStopInput P((void)),
	EncryptStopOutput P((void)),
D 37
	EncryptTogAuto P((void)),
	EncryptTogDebug P((void)),
	EncryptTogVerbose P((void)),
E 37
D 38
	EncryptStatus P((void)),
E 38
I 38
	EncryptStatus P((void));
static int
E 38
	EncryptHelp P((void));

struct encryptlist EncryptList[] = {
    { "enable", "Enable encryption. ('encrypt enable ?' for more)",
						EncryptEnable, 1, 1, 2 },
I 37
    { "disable", "Disable encryption. ('encrypt enable ?' for more)",
						EncryptDisable, 0, 1, 2 },
E 37
D 50
    { "type", "Set encryptiong type. ('encrypt type ?' for more)",
E 50
I 50
    { "type", "Set encryption type. ('encrypt type ?' for more)",
E 50
						EncryptType, 0, 1, 1 },
    { "start", "Start encryption. ('encrypt start ?' for more)",
						EncryptStart, 1, 0, 1 },
    { "stop", "Stop encryption. ('encrypt stop ?' for more)",
						EncryptStop, 1, 0, 1 },
    { "input", "Start encrypting the input stream",
						EncryptStartInput, 1, 0, 0 },
    { "-input", "Stop encrypting the input stream",
						EncryptStopInput, 1, 0, 0 },
    { "output", "Start encrypting the output stream",
						EncryptStartOutput, 1, 0, 0 },
    { "-output", "Stop encrypting the output stream",
						EncryptStopOutput, 1, 0, 0 },

    { "status",	"Display current status of authentication information",
						EncryptStatus,	0, 0, 0 },
D 37
    { "auto", "Toggle automatic enabling of encryption",
						EncryptTogAuto, 0, 0, 0 },
    { "verbose", "Toggle verbose encryption output",
						EncryptTogVerbose, 0, 0, 0 },
    { "debug",	"Toggle encryption debugging",
						EncryptTogDebug, 0, 0, 0 },
E 37
    { "help",	0,				EncryptHelp,	0, 0, 0 },
    { "?",	"Print help information",	EncryptHelp,	0, 0, 0 },
    { 0 },
};

    static int
EncryptHelp()
E 35
{
D 35
    static char buffer[100];
#define do(m,s) \
	if (mask&(m)) { \
	    strcat(buffer, (s)); \
E 35
I 35
    struct encryptlist *c;

    for (c = EncryptList; c->name; c++) {
	if (c->help) {
	    if (*c->help)
		printf("%-15s %s\n", c->name, c->help);
	    else
		printf("\n");
E 35
	}
I 35
    }
    return 0;
}
E 35

D 35
    buffer[0] = 0;			/* Terminate it */
E 35
I 35
encrypt_cmd(argc, argv)
    int  argc;
    char *argv[];
{
    struct encryptlist *c;
E 35

I 50
    if (argc < 2) {
	fprintf(stderr,
	    "Need an argument to 'encrypt' command.  'encrypt ?' for help.\n");
	return 0;
    }

E 50
D 35
#ifdef FREAD
    do(FREAD, " FREAD");
E 35
I 35
    c = (struct encryptlist *)
		genget(argv[1], (char **) EncryptList, sizeof(struct encryptlist));
    if (c == 0) {
D 51
        fprintf(stderr, "'%s': unknown argument ('encrypt ?' for help).\n",
E 51
I 51
	fprintf(stderr, "'%s': unknown argument ('encrypt ?' for help).\n",
E 51
    				argv[1]);
D 51
        return 0;
E 51
I 51
	return 0;
E 51
    }
    if (Ambiguous(c)) {
D 51
        fprintf(stderr, "'%s': ambiguous argument ('encrypt ?' for help).\n",
E 51
I 51
	fprintf(stderr, "'%s': ambiguous argument ('encrypt ?' for help).\n",
E 51
    				argv[1]);
D 51
        return 0;
E 51
I 51
	return 0;
E 51
    }
    argc -= 2;
    if (argc < c->minarg || argc > c->maxarg) {
	if (c->minarg == c->maxarg) {
	    fprintf(stderr, "Need %s%d argument%s ",
		c->minarg < argc ? "only " : "", c->minarg,
		c->minarg == 1 ? "" : "s");
	} else {
	    fprintf(stderr, "Need %s%d-%d arguments ",
		c->maxarg < argc ? "only " : "", c->minarg, c->maxarg);
	}
	fprintf(stderr, "to 'encrypt %s' command.  'encrypt ?' for help.\n",
		c->name);
	return 0;
    }
    if (c->needconnect && !connected) {
	if (!(argc && (isprefix(argv[2], "help") || isprefix(argv[2], "?")))) {
	    printf("?Need to be connected first.\n");
	    return 0;
	}
    }
    return ((*c->handler)(argc > 0 ? argv[2] : 0,
			argc > 1 ? argv[3] : 0,
			argc > 2 ? argv[4] : 0));
}
E 35
D 46
#endif
E 46
I 46
#endif	/* ENCRYPTION */
E 46
D 35
#ifdef FWRITE
    do(FWRITE, " FWRITE");
#endif
#ifdef F_DUPFP
    do(F_DUPFD, " F_DUPFD");
#endif
#ifdef FNDELAY
    do(FNDELAY, " FNDELAY");
#endif
#ifdef FAPPEND
    do(FAPPEND, " FAPPEND");
#endif
#ifdef FMARK
    do(FMARK, " FMARK");
#endif
#ifdef FDEFER
    do(FDEFER, " FDEFER");
#endif
#ifdef FASYNC
    do(FASYNC, " FASYNC");
#endif
#ifdef FSHLOCK
    do(FSHLOCK, " FSHLOCK");
#endif
#ifdef FEXLOCK
    do(FEXLOCK, " FEXLOCK");
#endif
#ifdef FCREAT
    do(FCREAT, " FCREAT");
#endif
#ifdef FTRUNC
    do(FTRUNC, " FTRUNC");
#endif
#ifdef FEXCL
    do(FEXCL, " FEXCL");
#endif
E 35

D 35
    return buffer;
}
#undef do
I 30
#endif	/* notdef */
E 30

I 30
#if defined(TN3270)
E 30
static void
E 35
I 35
#if	defined(unix) && defined(TN3270)
    static void
E 35
filestuff(fd)
D 35
int fd;
E 35
I 35
    int fd;
E 35
{
    int res;

D 19
    setconnmode();
E 19
I 19
#ifdef	F_GETOWN
    setconnmode(0);
E 19
    res = fcntl(fd, F_GETOWN, 0);
    setcommandmode();

    if (res == -1) {
	perror("fcntl");
	return;
    }
    printf("\tOwner is %d.\n", res);
I 19
#endif
E 19

D 19
    setconnmode();
E 19
I 19
    setconnmode(0);
E 19
    res = fcntl(fd, F_GETFL, 0);
    setcommandmode();

    if (res == -1) {
	perror("fcntl");
	return;
    }
I 44
#ifdef notdef
E 44
    printf("\tFlags are 0x%x: %s\n", res, decodeflags(res));
I 44
#endif
E 44
}
I 30
D 35
#endif /* defined(TN3270) */
E 35
I 35
#endif /* defined(unix) && defined(TN3270) */
E 35
E 30

D 35

#endif	/* defined(unix) */

E 35
/*
E 14
 * Print status about the connection.
 */
I 6
D 35
/*ARGSUSED*/
E 6
static
E 35
I 35
    /*ARGSUSED*/
    static
E 35
status(argc, argv)
D 35
int	argc;
char	*argv[];
E 35
I 35
    int	 argc;
    char *argv[];
E 35
{
    if (connected) {
	printf("Connected to %s.\n", hostname);
D 13
	if (argc < 2) {
E 13
I 13
	if ((argc < 2) || strcmp(argv[1], "notmuch")) {
E 13
D 19
	    printf("Operating in %s.\n",
				modelist[getconnmode()].modedescriptions);
	    if (localchars) {
		printf("Catching signals locally.\n");
E 19
I 19
	    int mode = getconnmode();

	    if (my_want_state_is_will(TELOPT_LINEMODE)) {
		printf("Operating with LINEMODE option\n");
		printf("%s line editing\n", (mode&MODE_EDIT) ? "Local" : "No");
		printf("%s catching of signals\n",
					(mode&MODE_TRAPSIG) ? "Local" : "No");
		slcstate();
#ifdef	KLUDGELINEMODE
D 23
	    } else if (kludgelinemode && my_want_state_is_wont(TELOPT_SGA)) {
E 23
I 23
	    } else if (kludgelinemode && my_want_state_is_dont(TELOPT_SGA)) {
E 23
		printf("Operating in obsolete linemode\n");
#endif
	    } else {
		printf("Operating in single character mode\n");
		if (localchars)
		    printf("Catching signals locally\n");
E 19
	    }
I 19
	    printf("%s character echo\n", (mode&MODE_ECHO) ? "Local" : "Remote");
	    if (my_want_state_is_will(TELOPT_LFLOW))
		printf("%s flow control\n", (mode&MODE_FLOW) ? "Local" : "No");
I 35
D 41
#if	defined(ENCRYPT)
E 41
I 41
D 46
#if	defined(ENCRYPTION)
E 46
I 46
#ifdef	ENCRYPTION
E 46
E 41
	    encrypt_display();
D 46
#endif
E 46
I 46
#endif	/* ENCRYPTION */
E 46
E 35
E 19
	}
    } else {
	printf("No connection.\n");
    }
#   if !defined(TN3270)
    printf("Escape character is '%s'.\n", control(escape));
D 6
    fflush(stdout);
E 6
I 6
    (void) fflush(stdout);
E 6
#   else /* !defined(TN3270) */
    if ((!In3270) && ((argc < 2) || strcmp(argv[1], "notmuch"))) {
	printf("Escape character is '%s'.\n", control(escape));
    }
#   if defined(unix)
I 13
    if ((argc >= 2) && !strcmp(argv[1], "everything")) {
	printf("SIGIO received %d time%s.\n",
				sigiocount, (sigiocount == 1)? "":"s");
I 14
	if (In3270) {
	    printf("Process ID %d, process group %d.\n",
					    getpid(), getpgrp(getpid()));
	    printf("Terminal input:\n");
	    filestuff(tin);
	    printf("Terminal output:\n");
	    filestuff(tout);
	    printf("Network socket:\n");
	    filestuff(net);
	}
E 14
    }
E 13
    if (In3270 && transcom) {
       printf("Transparent mode command is '%s'.\n", transcom);
    }
#   endif /* defined(unix) */
D 6
    fflush(stdout);
E 6
I 6
    (void) fflush(stdout);
E 6
    if (In3270) {
	return 0;
    }
#   endif /* defined(TN3270) */
    return 1;
}

I 33
#ifdef	SIGINFO
/*
 * Function that gets called when SIGINFO is received.
 */
ayt_status()
{
    (void) call(status, "status", "notmuch", 0);
}
#endif
E 33
D 3
#if	defined(TN3270) && defined(unix)
static
settranscom(argc, argv)
	int argc;
	char *argv[];
{
	int i, len = 0;
	char *strcpy(), *strcat();
E 3

I 43
unsigned long inet_addr();

E 43
I 30
D 35
#if	defined(NEED_GETTOS)
struct tosent {
	char	*t_name;	/* name */
	char	**t_aliases;	/* alias list */
	char	*t_proto;	/* protocol */
	int	t_tos;		/* Type Of Service bits */
};

struct tosent *
gettosbyname(name, proto)
char *name, *proto;
{
	static struct tosent te;
	static char *aliasp = 0;

	te.t_name = name;
	te.t_aliases = &aliasp;
	te.t_proto = proto;
	te.t_tos = 020; /* Low Delay bit */
	return(&te);
}
#endif

I 31
extern	int autologin;

E 31
E 30
I 24
D 25
#if	defined(IP_TOS) && defined(NEED_GETTOS)
E 25
I 25
D 29
#if	defined(NEED_GETTOS)
E 25
struct tosent {
	char	*t_name;	/* name */
	char	**t_aliases;	/* alias list */
	char	*t_proto;	/* protocol */
	int	t_tos;		/* Type Of Service bits */
};
E 24
D 3
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
}
#endif	/* defined(TN3270) && defined(unix) */
E 3

I 24
struct tosent *
gettosbyname(name, proto)
char *name, *proto;
{
	static struct tosent te;
	static char *aliasp = 0;

	te.t_name = name;
	te.t_aliases = &aliasp;
	te.t_proto = proto;
	te.t_tos = 020; /* Low Delay bit */
	return(&te);
}
#endif

E 29
E 24
D 3


E 3
int
E 35
I 35
    int
E 35
tn(argc, argv)
D 35
	int argc;
	char *argv[];
E 35
I 35
    int argc;
    char *argv[];
E 35
{
    register struct hostent *host = 0;
    struct sockaddr_in sin;
    struct servent *sp = 0;
D 35
    static char	hnamebuf[32];
E 35
I 6
D 19
    unsigned long inet_addr();
E 19
I 19
D 43
    unsigned long temp, inet_addr();
E 43
I 43
    unsigned long temp;
E 43
E 19
I 16
    extern char *inet_ntoa();
I 29
D 30
    int tos;
E 30
E 29
I 19
D 35
#if	defined(SRCRT) && defined(IPPROTO_IP)
E 35
I 35
#if	defined(IP_OPTIONS) && defined(IPPROTO_IP)
E 35
    char *srp = 0, *strrchr();
    unsigned long sourceroute(), srlen;
#endif
I 24
D 25
#ifdef IP_TOS
E 25
I 25
D 29
#if defined(HAS_IP_TOS) || defined(NEED_GETTOS)
E 29
I 29
D 30
#if defined(HAS_IP_TOS)
E 30
I 30
D 35
#if defined(HAS_IP_TOS) || defined(NEED_GETTOS)
E 30
E 29
E 25
    struct tosent *tp;
D 25
#endif /* IP_TOS */
E 25
I 25
D 29
#endif /* defined(HAS_IP_TOS) || defined(NEED_GETTOS) */
E 29
I 29
D 30
#endif /* defined(HAS_IP_TOS) */
E 30
I 30
#endif /* defined(HAS_IP_TOS) || defined(NEED_GETTOS) */
E 35
    char *cmd, *hostp = 0, *portp = 0, *user = 0;
E 30
E 29
E 25
E 24
E 19
E 16
E 6

I 33
    /* clear the socket address prior to use */
D 51
    bzero((char *)&sin, sizeof(sin));
E 51
I 51
    memset((char *)&sin, 0, sizeof(sin));
E 51
E 33

D 23
#if defined(MSDOS)
    char *cp;
#endif	/* defined(MSDOS) */

E 23
    if (connected) {
	printf("?Already connected to %s\n", hostname);
I 35
	setuid(getuid());
E 35
	return 0;
    }
    if (argc < 2) {
D 35
	(void) strcpy(line, "Connect ");
E 35
I 35
	(void) strcpy(line, "open ");
E 35
	printf("(to) ");
D 6
	gets(&line[strlen(line)]);
E 6
I 6
D 35
	(void) gets(&line[strlen(line)]);
E 35
I 35
	(void) fgets(&line[strlen(line)], sizeof(line) - strlen(line), stdin);
E 35
E 6
	makeargv();
	argc = margc;
	argv = margv;
    }
D 30
    if ((argc < 2) || (argc > 3)) {
	printf("usage: %s host-name [port]\n", argv[0]);
E 30
I 30
    cmd = *argv;
    --argc; ++argv;
    while (argc) {
I 35
D 50
	if (isprefix(*argv, "help") || isprefix(*argv, "?"))
E 50
I 50
	if (strcmp(*argv, "help") == 0 || isprefix(*argv, "?"))
E 50
	    goto usage;
E 35
	if (strcmp(*argv, "-l") == 0) {
	    --argc; ++argv;
	    if (argc == 0)
		goto usage;
	    user = *argv++;
	    --argc;
	    continue;
	}
I 33
	if (strcmp(*argv, "-a") == 0) {
	    --argc; ++argv;
	    autologin = 1;
	    continue;
	}
E 33
	if (hostp == 0) {
	    hostp = *argv++;
	    --argc;
	    continue;
	}
	if (portp == 0) {
	    portp = *argv++;
	    --argc;
	    continue;
	}
    usage:
D 33
	printf("usage: %s [-l user] host-name [port]\n", cmd);
E 33
I 33
	printf("usage: %s [-l user] [-a] host-name [port]\n", cmd);
I 35
	setuid(getuid());
E 35
E 33
E 30
	return 0;
    }
D 23
#if	defined(MSDOS)
    for (cp = argv[1]; *cp; cp++) {
	if (isupper(*cp)) {
	    *cp = tolower(*cp);
	}
    }
#endif	/* defined(MSDOS) */
E 23
D 19
    sin.sin_addr.s_addr = inet_addr(argv[1]);
D 15
    if (sin.sin_addr.s_addr != -1) {
E 15
I 15
    if (sin.sin_addr.s_addr != (unsigned long) -1) {
E 15
	sin.sin_family = AF_INET;
	(void) strcpy(hnamebuf, argv[1]);
	hostname = hnamebuf;
E 19
I 19
D 35
#if	defined(SRCRT) && defined(IPPROTO_IP)
E 35
I 35
    if (hostp == 0)
	goto usage;

#if	defined(IP_OPTIONS) && defined(IPPROTO_IP)
E 35
D 30
    if (argv[1][0] == '@' || argv[1][0] == '!') {
	if ((hostname = strrchr(argv[1], ':')) == NULL)
	    hostname = strrchr(argv[1], '@');
E 30
I 30
    if (hostp[0] == '@' || hostp[0] == '!') {
	if ((hostname = strrchr(hostp, ':')) == NULL)
	    hostname = strrchr(hostp, '@');
E 30
	hostname++;
	srp = 0;
D 30
	temp = sourceroute(argv[1], &srp, &srlen);
E 30
I 30
	temp = sourceroute(hostp, &srp, &srlen);
E 30
	if (temp == 0) {
	    herror(srp);
I 35
	    setuid(getuid());
E 35
	    return 0;
	} else if (temp == -1) {
D 30
	    printf("Bad source route option: %s\n", argv[1]);
E 30
I 30
	    printf("Bad source route option: %s\n", hostp);
I 35
	    setuid(getuid());
E 35
E 30
	    return 0;
	} else {
	    sin.sin_addr.s_addr = temp;
	    sin.sin_family = AF_INET;
	}
E 19
    } else {
D 19
	host = gethostbyname(argv[1]);
	if (host) {
	    sin.sin_family = host->h_addrtype;
E 19
I 19
#endif
D 30
	temp = inet_addr(argv[1]);
E 30
I 30
	temp = inet_addr(hostp);
E 30
	if (temp != (unsigned long) -1) {
	    sin.sin_addr.s_addr = temp;
	    sin.sin_family = AF_INET;
D 30
	    (void) strcpy(hnamebuf, argv[1]);
E 30
I 30
D 35
	    (void) strcpy(hnamebuf, hostp);
E 30
	    hostname = hnamebuf;
E 35
I 35
	    (void) strcpy(_hostname, hostp);
	    hostname = _hostname;
E 35
	} else {
D 30
	    host = gethostbyname(argv[1]);
E 30
I 30
	    host = gethostbyname(hostp);
E 30
	    if (host) {
		sin.sin_family = host->h_addrtype;
E 19
#if	defined(h_addr)		/* In 4.3, this is a #define */
D 19
	    memcpy((caddr_t)&sin.sin_addr,
E 19
I 19
D 51
		memcpy((caddr_t)&sin.sin_addr,
E 51
I 51
		memmove((caddr_t)&sin.sin_addr,
E 51
E 19
				host->h_addr_list[0], host->h_length);
#else	/* defined(h_addr) */
D 19
	    memcpy((caddr_t)&sin.sin_addr, host->h_addr, host->h_length);
E 19
I 19
D 51
		memcpy((caddr_t)&sin.sin_addr, host->h_addr, host->h_length);
E 51
I 51
		memmove((caddr_t)&sin.sin_addr, host->h_addr, host->h_length);
E 51
E 19
#endif	/* defined(h_addr) */
D 19
	    hostname = host->h_name;
	} else {
D 11
	    printf("%s: unknown host\n", argv[1]);
E 11
I 11
	    herror(argv[1]);
E 11
	    return 0;
E 19
I 19
D 35
		hostname = host->h_name;
E 35
I 35
		strncpy(_hostname, host->h_name, sizeof(_hostname));
		_hostname[sizeof(_hostname)-1] = '\0';
		hostname = _hostname;
E 35
	    } else {
D 30
		herror(argv[1]);
E 30
I 30
		herror(hostp);
I 35
D 51
	        setuid(getuid());
E 51
I 51
		setuid(getuid());
E 51
E 35
E 30
		return 0;
	    }
E 19
	}
I 19
D 35
#if	defined(SRCRT) && defined(IPPROTO_IP)
E 35
I 35
#if	defined(IP_OPTIONS) && defined(IPPROTO_IP)
E 35
E 19
    }
I 19
#endif
E 19
D 30
    if (argc == 3) {
I 19
	int tmp;

	if (*argv[2] == '-') {
	    argv[2]++;
E 30
I 30
    if (portp) {
	if (*portp == '-') {
	    portp++;
E 30
	    telnetport = 1;
	} else
	    telnetport = 0;
E 19
D 30
	sin.sin_port = atoi(argv[2]);
E 30
I 30
	sin.sin_port = atoi(portp);
E 30
	if (sin.sin_port == 0) {
D 30
	    sp = getservbyname(argv[2], "tcp");
E 30
I 30
	    sp = getservbyname(portp, "tcp");
E 30
	    if (sp)
		sin.sin_port = sp->s_port;
	    else {
D 30
		printf("%s: bad port number\n", argv[2]);
E 30
I 30
		printf("%s: bad port number\n", portp);
I 35
D 51
	        setuid(getuid());
E 51
I 51
		setuid(getuid());
E 51
E 35
E 30
		return 0;
	    }
	} else {
I 41
#if	!defined(htons)
D 47
	    u_short htons();
E 47
I 47
	    u_short htons P((unsigned short));
E 47
#endif	/* !defined(htons) */
E 41
I 6
D 38
#if	!defined(htons)
	    u_short htons();
#endif	/* !defined(htons) */
E 38
D 16

E 6
	    sin.sin_port = atoi(argv[2]);
E 16
	    sin.sin_port = htons(sin.sin_port);
	}
D 19
	telnetport = 0;
E 19
    } else {
	if (sp == 0) {
	    sp = getservbyname("telnet", "tcp");
	    if (sp == 0) {
D 6
		fprintf(stderr, "telnet: tcp/telnet: unknown service\n",1);
E 6
I 6
		fprintf(stderr, "telnet: tcp/telnet: unknown service\n");
I 35
D 51
	        setuid(getuid());
E 51
I 51
		setuid(getuid());
E 51
E 35
E 6
		return 0;
	    }
	    sin.sin_port = sp->s_port;
	}
	telnetport = 1;
    }
D 3
#if	defined(unix)
    signal(SIGINT, intr);
    signal(SIGQUIT, intr2);
    signal(SIGPIPE, deadpeer);
#endif	/* defined(unix) */
E 3
D 16
    printf("Trying...\n");
E 16
I 16
    printf("Trying %s...\n", inet_ntoa(sin.sin_addr));
E 16
    do {
	net = socket(AF_INET, SOCK_STREAM, 0);
I 35
	setuid(getuid());
E 35
	if (net < 0) {
	    perror("telnet: socket");
	    return 0;
	}
I 19
D 35
#if	defined(SRCRT) && defined(IPPROTO_IP)
E 35
I 35
#if	defined(IP_OPTIONS) && defined(IPPROTO_IP)
E 35
	if (srp && setsockopt(net, IPPROTO_IP, IP_OPTIONS, (char *)srp, srlen) < 0)
		perror("setsockopt (IP_OPTIONS)");
#endif
I 24
D 25
#ifdef IP_TOS
E 25
I 25
D 29
#if	defined(HAS_IP_TOS) || defined(NEED_GETTOS)
E 25
	if ((tp = gettosbyname("telnet", "tcp")) &&
	    (setsockopt(net, IPPROTO_IP, IP_TOS, &tp->t_tos, sizeof(int)) < 0))
E 29
I 29
D 30
#ifdef	IP_TOS
#ifdef	HAS_IP_TOS
	if (tp = gettosbyname("telnet", "tcp"))
		tos = tp->t_tos;
	else
#endif
	tos = IPTOS_LOWDELAY;
	if (setsockopt(net, IPPROTO_IP, IP_TOS, (char *)&tos, sizeof(int)) < 0)
E 30
I 30
D 35
#if	defined(HAS_IP_TOS) || defined(NEED_GETTOS)
	if ((tp = gettosbyname("telnet", "tcp")) &&
	    (setsockopt(net, IPPROTO_IP, IP_TOS, &tp->t_tos, sizeof(int)) < 0))
E 30
E 29
		perror("telnet: setsockopt TOS (ignored)");
I 25
D 29
#endif	/* defined(HAS_IP_TOS) || defined(NEED_GETTOS) */
E 29
I 29
D 30
#endif	/* IP_TOS */
E 30
I 30
#endif	/* defined(HAS_IP_TOS) || defined(NEED_GETTOS) */
E 35
I 35
#if	defined(IPPROTO_IP) && defined(IP_TOS)
	{
D 36
	    int tos = 020; /* Low Delay bit */
E 36
# if	defined(HAS_GETTOS)
	    struct tosent *tp;
D 36
	    if (tp = gettosbyname("telnet", "tcp"))
E 36
I 36
	    if (tos < 0 && (tp = gettosbyname("telnet", "tcp")))
E 36
		tos = tp->t_tos;
# endif
D 36
	    (void)setsockopt(net, IPPROTO_IP, IP_TOS, &tos, sizeof(int));
E 36
I 36
	    if (tos < 0)
		tos = 020;	/* Low Delay bit */
	    if (tos
D 41
		&& (setsockopt(net, IPPROTO_IP, IP_TOS, &tos, sizeof(int)) < 0)
E 41
I 41
		&& (setsockopt(net, IPPROTO_IP, IP_TOS,
		    (char *)&tos, sizeof(int)) < 0)
E 41
		&& (errno != ENOPROTOOPT))
		    perror("telnet: setsockopt (IP_TOS) (ignored)");
E 36
	}
#endif	/* defined(IPPROTO_IP) && defined(IP_TOS) */
E 35
E 30
E 29
E 25

D 25
#endif /* IP_TOS */
E 25
E 24
E 19
	if (debug && SetSockOpt(net, SOL_SOCKET, SO_DEBUG, 1) < 0) {
		perror("setsockopt (SO_DEBUG)");
	}

	if (connect(net, (struct sockaddr *)&sin, sizeof (sin)) < 0) {
#if	defined(h_addr)		/* In 4.3, this is a #define */
	    if (host && host->h_addr_list[1]) {
		int oerrno = errno;
I 6
D 16
		extern char *inet_ntoa();
E 16
E 6

		fprintf(stderr, "telnet: connect to address %s: ",
						inet_ntoa(sin.sin_addr));
		errno = oerrno;
		perror((char *)0);
		host->h_addr_list++;
D 51
		memcpy((caddr_t)&sin.sin_addr, 
E 51
I 51
		memmove((caddr_t)&sin.sin_addr,
E 51
			host->h_addr_list[0], host->h_length);
D 16
		fprintf(stderr, "Trying %s...\n",
			inet_ntoa(sin.sin_addr));
E 16
		(void) NetClose(net);
		continue;
	    }
#endif	/* defined(h_addr) */
	    perror("telnet: Unable to connect to remote host");
D 3
#if defined(unix)
	    signal(SIGINT, SIG_DFL);
	    signal(SIGQUIT, SIG_DFL);
#endif	/* defined(unix) */
E 3
	    return 0;
D 16
	    }
E 16
I 16
	}
E 16
	connected++;
I 35
D 41
#if	defined(AUTHENTICATE) || defined(ENCRYPT)
E 41
I 41
#if	defined(AUTHENTICATION) || defined(ENCRYPTION)
E 41
	auth_encrypt_connect(connected);
D 46
#endif
E 46
I 46
#endif	/* defined(AUTHENTICATION) || defined(ENCRYPTION) */
E 46
E 35
    } while (connected == 0);
I 19
D 30
    cmdrc(argv[1], hostname);
E 30
I 30
    cmdrc(hostp, hostname);
D 31
    if (user)
E 31
I 31
    if (autologin && user == NULL) {
	struct passwd *pw;
D 33
	uid_t uid = getuid();
E 33

D 33
	user = getlogin();
E 33
I 33
	user = getenv("USER");
E 33
	if (user == NULL ||
D 33
	    (pw = getpwnam(user)) && pw->pw_uid != uid)
		if (pw = getpwuid(uid))
E 33
I 33
	    (pw = getpwnam(user)) && pw->pw_uid != getuid()) {
		if (pw = getpwuid(getuid()))
E 33
			user = pw->pw_name;
		else
			user = NULL;
I 33
	}
E 33
    }
    if (user) {
E 31
D 35
	env_define("USER", user);
I 31
	env_export("USER");
E 35
I 35
	env_define((unsigned char *)"USER", (unsigned char *)user);
	env_export((unsigned char *)"USER");
E 35
    }
E 31
E 30
E 19
D 6
    call(status, "status", "notmuch", 0);
E 6
I 6
    (void) call(status, "status", "notmuch", 0);
E 6
    if (setjmp(peerdied) == 0)
D 35
	telnet();
E 35
I 35
	telnet(user);
E 35
D 6
    NetClose(net);
E 6
I 6
    (void) NetClose(net);
E 6
D 2
    ExitString(stderr, "Connection closed by foreign host.\n",1);
E 2
I 2
    ExitString("Connection closed by foreign host.\n",1);
E 2
    /*NOTREACHED*/
}

D 35

E 35
#define HELPINDENT (sizeof ("connect"))

static char
	openhelp[] =	"connect to a site",
	closehelp[] =	"close current connection",
I 35
	logouthelp[] =	"forcibly logout remote user and close the connection",
E 35
	quithelp[] =	"exit telnet",
	statushelp[] =	"print status information",
	helphelp[] =	"print help information",
	sendhelp[] =	"transmit special characters ('send ?' for more)",
	sethelp[] = 	"set operating parameters ('set ?' for more)",
I 19
	unsethelp[] = 	"unset operating parameters ('unset ?' for more)",
E 19
	togglestring[] ="toggle operating parameters ('toggle ?' for more)",
I 19
	slchelp[] =	"change state of special charaters ('slc ?' for more)",
E 19
	displayhelp[] =	"display operating parameters",
#if	defined(TN3270) && defined(unix)
	transcomhelp[] = "specify Unix command for transparent mode pipe",
#endif	/* defined(TN3270) && defined(unix) */
I 35
D 41
#if	defined(AUTHENTICATE)
E 41
I 41
#if	defined(AUTHENTICATION)
E 41
	authhelp[] =	"turn on (off) authentication ('auth ?' for more)",
#endif
D 41
#if	defined(ENCRYPT)
E 41
I 41
D 46
#if	defined(ENCRYPTION)
E 46
I 46
#ifdef	ENCRYPTION
E 46
E 41
	encrypthelp[] =	"turn on (off) encryption ('encrypt ?' for more)",
D 46
#endif
E 46
I 46
#endif	/* ENCRYPTION */
E 46
E 35
#if	defined(unix)
	zhelp[] =	"suspend telnet",
D 28
#endif	/* defined(unix */
E 28
I 28
#endif	/* defined(unix) */
E 28
D 19
#if	defined(TN3270)
E 19
	shellhelp[] =	"invoke a subshell",
D 19
#endif	/* defined(TN3270) */
	modehelp[] = "try to enter line-by-line or character-at-a-time mode";
E 19
I 19
D 30
	modestring[] = "try to enter line-by-line or character-at-a-time mode";
E 30
I 30
	envhelp[] =	"change environment variables ('environ ?' for more)",
	modestring[] = "try to enter line or character mode ('mode ?' for more)";
E 30
E 19

D 35
extern int	help(), shell();
E 35
I 35
D 38
extern int	help();
E 38
I 38
static int	help();
E 38
E 35

static Command cmdtab[] = {
D 19
	{ "close",	closehelp,	bye,		1, 1 },
	{ "display",	displayhelp,	display,	1, 0 },
	{ "mode",	modehelp,	modecmd,	1, 1 },
	{ "open",	openhelp,	tn,		1, 0 },
	{ "quit",	quithelp,	quit,		1, 0 },
	{ "send",	sendhelp,	sendcmd,	1, 1 },
	{ "set",	sethelp,	setcmd,		1, 0 },
	{ "status",	statushelp,	status,		1, 0 },
	{ "toggle",	togglestring,	toggle,		1, 0 },
E 19
I 19
	{ "close",	closehelp,	bye,		1 },
I 35
	{ "logout",	logouthelp,	logout,		1 },
E 35
	{ "display",	displayhelp,	display,	0 },
	{ "mode",	modestring,	modecmd,	0 },
	{ "open",	openhelp,	tn,		0 },
	{ "quit",	quithelp,	quit,		0 },
	{ "send",	sendhelp,	sendcmd,	0 },
	{ "set",	sethelp,	setcmd,		0 },
	{ "unset",	unsethelp,	unsetcmd,	0 },
	{ "status",	statushelp,	status,		0 },
	{ "toggle",	togglestring,	toggle,		0 },
	{ "slc",	slchelp,	slccmd,		0 },
E 19
#if	defined(TN3270) && defined(unix)
D 19
	{ "transcom",	transcomhelp,	settranscom,	1, 0 },
E 19
I 19
	{ "transcom",	transcomhelp,	settranscom,	0 },
E 19
#endif	/* defined(TN3270) && defined(unix) */
I 35
D 41
#if	defined(AUTHENTICATE)
E 41
I 41
#if	defined(AUTHENTICATION)
E 41
	{ "auth",	authhelp,	auth_cmd,	0 },
#endif
D 41
#if	defined(ENCRYPT)
E 41
I 41
D 46
#if	defined(ENCRYPTION)
E 46
I 46
#ifdef	ENCRYPTION
E 46
E 41
	{ "encrypt",	encrypthelp,	encrypt_cmd,	0 },
D 46
#endif
E 46
I 46
#endif	/* ENCRYPTION */
E 46
E 35
#if	defined(unix)
D 19
	{ "z",		zhelp,		suspend,	1, 0 },
E 19
I 19
	{ "z",		zhelp,		suspend,	0 },
E 19
#endif	/* defined(unix) */
#if	defined(TN3270)
D 19
	{ "!",		shellhelp,	shell,		1, 1 },
#endif	/* defined(TN3270) */
	{ "?",		helphelp,	help,		1, 0 },
E 19
I 19
	{ "!",		shellhelp,	shell,		1 },
#else
	{ "!",		shellhelp,	shell,		0 },
#endif
I 30
	{ "environ",	envhelp,	env_cmd,	0 },
E 30
	{ "?",		helphelp,	help,		0 },
E 19
	0
};

static char	crmodhelp[] =	"deprecated command -- use 'toggle crmod' instead";
static char	escapehelp[] =	"deprecated command -- use 'set escape' instead";

static Command cmdtab2[] = {
D 19
	{ "help",	helphelp,	help,		0, 0 },
	{ "escape",	escapehelp,	setescape,	1, 0 },
	{ "crmod",	crmodhelp,	togcrmod,	1, 0 },
E 19
I 19
	{ "help",	0,		help,		0 },
	{ "escape",	escapehelp,	setescape,	0 },
	{ "crmod",	crmodhelp,	togcrmod,	0 },
E 19
	0
};

I 8

E 8
/*
 * Call routine with argc, argv set from args (terminated by 0).
D 8
 * VARARGS2
E 8
 */
I 8

I 9
D 35
/*VARARGS1*/
E 9
E 8
static
E 35
I 35
    /*VARARGS1*/
    static
E 35
D 8
call(routine, args)
	int (*routine)();
	char *args;
E 8
I 8
call(va_alist)
D 35
va_dcl
E 35
I 35
    va_dcl
E 35
E 8
{
D 8
	register char **argp;
	register int argc;
E 8
I 8
    va_list ap;
    typedef int (*intrtn_t)();
    intrtn_t routine;
    char *args[100];
E 8
D 10

E 10
D 8
	for (argc = 0, argp = &args; *argp++ != 0; argc++)
		;
	return (*routine)(argc, &args);
E 8
I 8
    int argno = 0;

    va_start(ap);
    routine = (va_arg(ap, intrtn_t));
D 10
    while (args[argno++] = va_arg(ap, char *))
E 10
I 10
    while ((args[argno++] = va_arg(ap, char *)) != 0) {
E 10
	;
I 10
    }
E 10
    va_end(ap);
D 10
    return (*routine)(argno, args);
E 10
I 10
    return (*routine)(argno-1, args);
E 10
E 8
}
I 8

E 8

D 35
static char **
getnextcmd(name)
char *name;
{
    Command *c = (Command *) name;

    return (char **) (c+1);
}

static Command *
E 35
I 35
    static Command *
E 35
getcmd(name)
D 35
char *name;
E 35
I 35
    char *name;
E 35
{
    Command *cm;

D 35
    if ((cm = (Command *) genget(name, (char **) cmdtab, getnextcmd)) != 0) {
E 35
I 35
    if (cm = (Command *) genget(name, (char **) cmdtab, sizeof(Command)))
E 35
	return cm;
D 35
    } else {
	return (Command *) genget(name, (char **) cmdtab2, getnextcmd);
    }
E 35
I 35
    return (Command *) genget(name, (char **) cmdtab2, sizeof(Command));
E 35
}

D 35
void
E 35
I 35
    void
E 35
D 19
command(top)
E 19
I 19
command(top, tbuf, cnt)
E 19
D 35
	int top;
I 19
	char *tbuf;
	int cnt;
E 35
I 35
    int top;
    char *tbuf;
    int cnt;
E 35
E 19
{
    register Command *c;

    setcommandmode();
    if (!top) {
	putchar('\n');
D 16
    } else {
E 16
#if	defined(unix)
I 16
    } else {
E 16
D 30
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
E 30
I 30
	(void) signal(SIGINT, SIG_DFL);
	(void) signal(SIGQUIT, SIG_DFL);
E 30
#endif	/* defined(unix) */
    }
    for (;;) {
D 35
	printf("%s> ", prompt);
E 35
I 35
	if (rlogin == _POSIX_VDISABLE)
		printf("%s> ", prompt);
E 35
D 19
	if (gets(line) == NULL) {
	    if (feof(stdin) || ferror(stdin))
		quit();
	    break;
E 19
I 19
	if (tbuf) {
	    register char *cp;
	    cp = line;
	    while (cnt > 0 && (*cp++ = *tbuf++) != '\n')
		cnt--;
	    tbuf = 0;
	    if (cp == line || *--cp != '\n' || cp == line)
		goto getline;
	    *cp = '\0';
D 35
	    printf("%s\n", line);
E 35
I 35
	    if (rlogin == _POSIX_VDISABLE)
D 51
	        printf("%s\n", line);
E 51
I 51
		printf("%s\n", line);
E 51
E 35
	} else {
	getline:
D 35
	    if (gets(line) == NULL) {
E 35
I 35
	    if (rlogin != _POSIX_VDISABLE)
		printf("%s> ", prompt);
	    if (fgets(line, sizeof(line), stdin) == NULL) {
E 35
D 30
		if (feof(stdin) || ferror(stdin))
		    quit();
E 30
I 30
		if (feof(stdin) || ferror(stdin)) {
		    (void) quit();
		    /*NOTREACHED*/
		}
E 30
		break;
	    }
E 19
	}
	if (line[0] == 0)
	    break;
	makeargv();
I 16
	if (margv[0] == 0) {
	    break;
	}
E 16
	c = getcmd(margv[0]);
	if (Ambiguous(c)) {
	    printf("?Ambiguous command\n");
	    continue;
	}
	if (c == 0) {
	    printf("?Invalid command\n");
	    continue;
	}
	if (c->needconnect && !connected) {
	    printf("?Need to be connected first.\n");
	    continue;
	}
	if ((*c->handler)(margc, margv)) {
	    break;
	}
    }
    if (!top) {
	if (!connected) {
	    longjmp(toplevel, 1);
	    /*NOTREACHED*/
	}
#if	defined(TN3270)
	if (shell_active == 0) {
D 19
	    setconnmode();
E 19
I 19
	    setconnmode(0);
E 19
	}
#else	/* defined(TN3270) */
D 19
	setconnmode();
E 19
I 19
	setconnmode(0);
E 19
#endif	/* defined(TN3270) */
    }
}

/*
 * Help command.
 */
D 35
static
E 35
I 35
	static
E 35
help(argc, argv)
	int argc;
	char *argv[];
{
	register Command *c;

	if (argc == 1) {
		printf("Commands may be abbreviated.  Commands are:\n\n");
		for (c = cmdtab; c->name; c++)
D 19
			if (c->dohelp) {
E 19
I 19
			if (c->help) {
E 19
				printf("%-*s\t%s\n", HELPINDENT, c->name,
								    c->help);
			}
		return 0;
	}
	while (--argc > 0) {
		register char *arg;
		arg = *++argv;
		c = getcmd(arg);
		if (Ambiguous(c))
			printf("?Ambiguous help command %s\n", arg);
		else if (c == (Command *)0)
			printf("?Invalid help command %s\n", arg);
		else
			printf("%s\n", c->help);
	}
	return 0;
}
I 19

static char *rcname = 0;
static char rcbuf[128];

cmdrc(m1, m2)
	char *m1, *m2;
{
    register Command *c;
    FILE *rcfile;
    int gotmachine = 0;
    int l1 = strlen(m1);
    int l2 = strlen(m2);
    char m1save[64];

I 37
    if (skiprc)
	return;

E 37
    strcpy(m1save, m1);
    m1 = m1save;

    if (rcname == 0) {
	rcname = getenv("HOME");
	if (rcname)
	    strcpy(rcbuf, rcname);
	else
	    rcbuf[0] = '\0';
	strcat(rcbuf, "/.telnetrc");
	rcname = rcbuf;
    }

    if ((rcfile = fopen(rcname, "r")) == 0) {
	return;
    }

    for (;;) {
	if (fgets(line, sizeof(line), rcfile) == NULL)
	    break;
	if (line[0] == 0)
	    break;
	if (line[0] == '#')
	    continue;
I 37
	if (gotmachine) {
	    if (!isspace(line[0]))
		gotmachine = 0;
	}
E 37
	if (gotmachine == 0) {
	    if (isspace(line[0]))
		continue;
	    if (strncasecmp(line, m1, l1) == 0)
		strncpy(line, &line[l1], sizeof(line) - l1);
	    else if (strncasecmp(line, m2, l2) == 0)
		strncpy(line, &line[l2], sizeof(line) - l2);
I 37
	    else if (strncasecmp(line, "DEFAULT", 7) == 0)
		strncpy(line, &line[7], sizeof(line) - 7);
E 37
	    else
		continue;
D 37
	    gotmachine = 1;
	} else {
	    if (!isspace(line[0])) {
		gotmachine = 0;
E 37
I 37
	    if (line[0] != ' ' && line[0] != '\t' && line[0] != '\n')
E 37
		continue;
D 37
	    }
E 37
I 37
	    gotmachine = 1;
E 37
	}
	makeargv();
	if (margv[0] == 0)
	    continue;
	c = getcmd(margv[0]);
	if (Ambiguous(c)) {
	    printf("?Ambiguous command: %s\n", margv[0]);
	    continue;
	}
	if (c == 0) {
	    printf("?Invalid command: %s\n", margv[0]);
	    continue;
	}
	/*
	 * This should never happen...
	 */
	if (c->needconnect && !connected) {
	    printf("?Need to be connected first for %s.\n", margv[0]);
	    continue;
	}
	(*c->handler)(margc, margv);
    }
    fclose(rcfile);
}

D 35
#if	defined(SRCRT) && defined(IPPROTO_IP)
E 35
I 35
#if	defined(IP_OPTIONS) && defined(IPPROTO_IP)
E 35

/*
 * Source route is handed in as
 *	[!]@hop1@hop2...[@|:]dst
 * If the leading ! is present, it is a
 * strict source route, otherwise it is
 * assmed to be a loose source route.
 *
 * We fill in the source route option as
 *	hop1,hop2,hop3...dest
 * and return a pointer to hop1, which will
 * be the address to connect() to.
 *
 * Arguments:
 *	arg:	pointer to route list to decipher
 *
 *	cpp: 	If *cpp is not equal to NULL, this is a
 *		pointer to a pointer to a character array
 *		that should be filled in with the option.
 *
 *	lenp:	pointer to an integer that contains the
 *		length of *cpp if *cpp != NULL.
 *
 * Return values:
 *
 *	Returns the address of the host to connect to.  If the
 *	return value is -1, there was a syntax error in the
 *	option, either unknown characters, or too many hosts.
 *	If the return value is 0, one of the hostnames in the
 *	path is unknown, and *cpp is set to point to the bad
 *	hostname.
 *
 *	*cpp:	If *cpp was equal to NULL, it will be filled
 *		in with a pointer to our static area that has
 *		the option filled in.  This will be 32bit aligned.
D 51
 * 
E 51
I 51
 *
E 51
 *	*lenp:	This will be filled in with how long the option
 *		pointed to by *cpp is.
D 51
 *	
E 51
I 51
 *
E 51
 */
D 35
unsigned long
E 35
I 35
	unsigned long
E 35
sourceroute(arg, cpp, lenp)
D 35
char	*arg;
char	**cpp;
int	*lenp;
E 35
I 35
	char	*arg;
	char	**cpp;
	int	*lenp;
E 35
{
	static char lsr[44];
I 41
#ifdef	sysV88
	static IOPTN ipopt;
#endif
E 41
D 35
	char *cp, *cp2, *lsrp, *lsrep, *index();
E 35
I 35
	char *cp, *cp2, *lsrp, *lsrep;
E 35
	register int tmp;
	struct in_addr sin_addr;
	register struct hostent *host = 0;
	register char c;

	/*
	 * Verify the arguments, and make sure we have
	 * at least 7 bytes for the option.
	 */
	if (cpp == NULL || lenp == NULL)
		return((unsigned long)-1);
	if (*cpp != NULL && *lenp < 7)
		return((unsigned long)-1);
	/*
	 * Decide whether we have a buffer passed to us,
	 * or if we need to use our own static buffer.
	 */
	if (*cpp) {
		lsrp = *cpp;
		lsrep = lsrp + *lenp;
	} else {
		*cpp = lsrp = lsr;
		lsrep = lsrp + 44;
	}

	cp = arg;

	/*
	 * Next, decide whether we have a loose source
	 * route or a strict source route, and fill in
	 * the begining of the option.
	 */
I 41
#ifndef	sysV88
E 41
	if (*cp == '!') {
		cp++;
		*lsrp++ = IPOPT_SSRR;
	} else
		*lsrp++ = IPOPT_LSRR;
I 41
#else
	if (*cp == '!') {
		cp++;
		ipopt.io_type = IPOPT_SSRR;
	} else
		ipopt.io_type = IPOPT_LSRR;
#endif
E 41

	if (*cp != '@')
		return((unsigned long)-1);

I 41
#ifndef	sysV88
E 41
	lsrp++;		/* skip over length, we'll fill it in later */
	*lsrp++ = 4;
I 41
#endif
E 41

	cp++;

	sin_addr.s_addr = 0;

	for (c = 0;;) {
		if (c == ':')
			cp2 = 0;
		else for (cp2 = cp; c = *cp2; cp2++) {
			if (c == ',') {
				*cp2++ = '\0';
				if (*cp2 == '@')
					cp2++;
			} else if (c == '@') {
				*cp2++ = '\0';
			} else if (c == ':') {
				*cp2++ = '\0';
			} else
				continue;
			break;
		}
		if (!c)
			cp2 = 0;

		if ((tmp = inet_addr(cp)) != -1) {
			sin_addr.s_addr = tmp;
		} else if (host = gethostbyname(cp)) {
#if	defined(h_addr)
D 51
			memcpy((caddr_t)&sin_addr,
E 51
I 51
			memmove((caddr_t)&sin_addr,
E 51
				host->h_addr_list[0], host->h_length);
#else
D 51
			memcpy((caddr_t)&sin_addr, host->h_addr, host->h_length);
E 51
I 51
			memmove((caddr_t)&sin_addr, host->h_addr, host->h_length);
E 51
#endif
		} else {
			*cpp = cp;
			return(0);
		}
D 51
		memcpy(lsrp, (char *)&sin_addr, 4);
E 51
I 51
		memmove(lsrp, (char *)&sin_addr, 4);
E 51
		lsrp += 4;
		if (cp2)
			cp = cp2;
		else
			break;
		/*
		 * Check to make sure there is space for next address
		 */
		if (lsrp + 4 > lsrep)
			return((unsigned long)-1);
	}
I 41
#ifndef	sysV88
E 41
	if ((*(*cpp+IPOPT_OLEN) = lsrp - *cpp) <= 7) {
		*cpp = 0;
		*lenp = 0;
		return((unsigned long)-1);
	}
	*lsrp++ = IPOPT_NOP; /* 32 bit word align it */
	*lenp = lsrp - *cpp;
I 41
#else
	ipopt.io_len = lsrp - *cpp;
	if (ipopt.io_len <= 5) {		/* Is 3 better ? */
		*cpp = 0;
		*lenp = 0;
		return((unsigned long)-1);
	}
	*lenp = sizeof(ipopt);
	*cpp = (char *) &ipopt;
#endif
E 41
	return(sin_addr.s_addr);
D 35
}
#endif

D 21
#if	defined(sun)
E 21
I 21
#if	defined(NOSTRNCASECMP)
E 21
strncasecmp(p1, p2, len)
register char *p1, *p2;
int len;
{
    while (len--) {
	if (tolower(*p1) != tolower(*p2))
	   return(tolower(*p1) - tolower(*p2));
	if (*p1 == '\0')
	    return(0);
	p1++, p2++;
    }
    return(0);
E 35
}
#endif
E 19
E 1
