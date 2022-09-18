h16456
s 00011/00002/00954
d D 8.4 95/04/29 10:34:29 vjs 71 70
c Andy Cherenson's hack to understand user@remote.host just like rcp
c Checked in for Vernon Schryver <vjs@calcite.rhyolite.com>.
e
s 00037/00004/00919
d D 8.3 94/08/31 05:44:04 pendry 70 69
c fix speed passing.
c ensure ICRNL is turned off, and ISTRIP (for eight bit mode).
e
s 00159/00151/00764
d D 8.2 94/08/23 10:13:00 pendry 69 68
c convert to POSIX code (signals, terminal manipulation, and string functions)
e
s 00005/00005/00910
d D 8.1 93/06/06 16:09:58 bostic 68 67
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00011/00903
d D 5.41 93/04/19 20:01:12 torek 67 66
c prettiness police; clean up SunOS ifdefs for SunOS 4
e
s 00006/00001/00908
d D 5.40 93/03/23 04:41:23 bostic 66 65
c fix stdarg/varargs includes
e
s 00000/00001/00909
d D 5.39 93/03/04 18:47:34 bostic 65 64
c stupid stdargs.h fix
e
s 00111/00060/00799
d D 5.38 93/03/04 18:31:49 bostic 64 63
c Craig Leres prototyping fixes, plus some of mine
e
s 00014/00006/00845
d D 5.37 93/02/26 16:32:55 mckusick 63 62
c narrow possible window for losing window size change
e
s 00008/00000/00843
d D 5.36 92/12/02 15:49:47 eric 62 61
c fully qualify host name on krb_realofhost call
e
s 00003/00005/00840
d D 5.35 92/06/20 10:29:26 bostic 61 60
c put K option in the usage statement
e
s 00001/00000/00844
d D 5.34 92/03/20 18:39:10 leres 60 58
c Allow later -e flag to override -E.
e
s 00000/00056/00788
d D 5.33.1.1 91/08/20 16:56:14 mckusick 59 58
c delete data-stream encryption for the foreign sites (Network, Release 2)
e
s 00015/00015/00829
d D 5.33 91/03/01 15:35:43 bostic 58 56
c ANSI (real bug fix!)
e
s 00000/00056/00788
d D 5.32.1.1 90/10/21 18:18:09 mckusick 57 56
c delete data-stream encryption for the foreign sites (4.3-Reno)
e
s 00015/00005/00829
d D 5.32 90/10/21 18:17:36 mckusick 56 55
c use ifdef's that unifdef understands
e
s 00014/00006/00820
d D 5.31 90/09/27 21:46:10 mckusick 55 54
c break out -x functionality into #ifdef CRYPT
e
s 00051/00024/00775
d D 5.30 90/08/23 10:26:38 bostic 54 53
c add -E for no escape character, allow octal for -e
e
s 00006/00001/00793
d D 5.29 90/06/27 21:20:38 karels 53 52
c set IP type of service
e
s 00003/00003/00791
d D 5.28 90/06/01 17:40:57 bostic 52 51
c put reasonable SCCS headers on
e
s 00001/00001/00793
d D 5.27 90/05/18 08:28:19 bostic 51 50
c FWRITE -> O_RDWR
e
s 00001/00001/00793
d D 5.26 90/05/15 20:00:35 bostic 50 49
c string.h is ANSI C include file
e
s 00001/00000/00793
d D 5.25 90/05/11 22:57:28 kfall 49 48
c include kerberosIV/des.h before kerberosIV/krb.h
e
s 00017/00010/00776
d D 5.24 90/04/10 10:07:35 bostic 48 47
c add -K flag to avoid Kerberos connection
e
s 00360/00383/00426
d D 5.23 90/04/09 12:50:47 bostic 47 46
c allow "rlogin flags host", reformat to KNF, minor rephrasing
e
s 00001/00001/00808
d D 5.22 90/04/03 12:06:09 bostic 46 45
c include files moved to kerberosIV, not /usr/include
e
s 00000/00000/00809
d D 5.21 89/08/30 17:52:37 kfall 45 44
c no change; but discovered an error in wait.h
e
s 00037/00034/00772
d D 5.20 89/08/22 17:34:41 kfall 44 43
c cleanup Kerberos stuff
e
s 00002/00000/00804
d D 5.19 89/02/10 01:18:33 kfall 43 42
c krb library uses euid's; handle appropriately
e
s 00001/00001/00803
d D 5.18 89/02/10 00:49:22 kfall 42 41
c get service name "eklogin" if encrypted
e
s 00006/00001/00798
d D 5.17 89/01/25 18:30:58 kfall 41 40
c fix klogin->login problem when Kerb. unavail, use new getrlm call
e
s 00001/00001/00798
d D 5.16 89/01/22 22:22:56 kfall 40 39
c fix up usage statement
e
s 00011/00000/00788
d D 5.15 89/01/07 02:36:10 kfall 39 38
c add -k argument for Kerberos realm
e
s 00057/00029/00731
d D 5.14 89/01/05 19:24:42 kfall 38 37
c add code for trying Kerb. 1st, then old style rlogin 
c (Uses "klogin" service from /etc/serices)
e
s 00105/00012/00655
d D 5.13 89/01/05 18:31:27 kfall 37 36
c add Kerberos ifdef's
e
s 00017/00007/00650
d D 5.12 88/09/19 12:58:59 bostic 36 34
c add Berkeley specific copyright
e
s 00002/00000/00657
d R 5.12 86/12/10 17:36:42 sam 35 34
c strip parity if we're not using eight-bit stuff
e
s 00129/00078/00528
d D 5.11 86/08/07 13:00:02 mckusick 34 32
c lint plus window size negotiation fixups from Torek
e
s 00130/00079/00527
d R 5.11 86/08/06 22:55:51 mckusick 33 32
c lint plus window size negotiation fixups from Torek
e
s 00046/00002/00560
d D 5.10 86/03/30 16:38:43 karels 32 30
c I'm tired of merging: add sun #ifdefs
e
s 00045/00001/00561
d R 5.10 86/03/30 16:24:04 karels 31 30
c I'm tired of merging; add sun #ifdefs
e
s 00001/00001/00561
d D 5.9 86/02/17 04:27:01 lepreau 30 29
c missing return value
e
s 00108/00038/00454
d D 5.8 85/11/08 09:46:48 karels 29 28
c don't flush input on oob unless it's really a flush; careful about
c restarting syscalls after return from oob(); misc cleanup
e
s 00005/00011/00487
d D 5.7 85/10/30 16:16:31 mckusick 28 27
c -w is obsolete
e
s 00005/00002/00493
d D 5.6 85/09/18 18:31:57 mckusick 27 25
c only send window size the first time it is noted in out of band data
e
s 00002/00001/00494
d R 5.6 85/09/17 23:06:04 mckusick 26 25
c only send window size the first time it is noted in out of band data
e
s 00000/00000/00495
d D 5.5 85/09/12 20:57:19 mckusick 25 22
i 24 23
c merge from Sun
e
s 00073/00052/00421
d D 5.3.1.2 85/09/12 20:55:55 mckusick 24 23
c update from Bill Nowicki at Sun
e
s 00000/00000/00473
d D 5.3.1.1 85/09/12 20:54:21 mckusick 23 21
c branch-place-holder
e
s 00003/00002/00471
d D 5.4 85/07/24 09:14:56 karels 22 21
c ioctl SPGRP -> fcntl F_SETOWN, and reverse sense of proc/pgrp
e
s 00051/00044/00422
d D 5.3 85/06/18 18:30:04 bloom 21 20
c fix handling of escape char and stopping differences (^Z/^Y)
e
s 00002/00001/00464
d D 5.2 85/06/08 13:09:40 bloom 20 19
c fix looping problem if receiving oob data and connection is lost
e
s 00014/00002/00451
d D 5.1 85/05/31 09:43:46 dist 19 18
c Add copyright
e
s 00015/00001/00438
d D 4.18 85/05/31 09:35:59 bloom 18 17
c add litout mode (-L)
e
s 00089/00031/00350
d D 4.17 85/03/17 23:33:20 sam 17 16
c propagate window size changes
e
s 00002/00001/00379
d D 4.16 84/12/03 00:05:49 lepreau 16 15
c cnvt setsockopt to new interface
e
s 00002/00002/00378
d D 4.15 83/07/02 00:55:21 sam 15 14
c include fixes
e
s 00045/00035/00335
d D 4.14 83/06/13 02:47:54 sam 14 13
c boy is this getting boring
e
s 00014/00014/00356
d D 4.13 83/06/10 23:34:44 sam 13 12
c new signals, no libjobs
e
s 00014/00010/00356
d D 4.12 83/04/30 18:53:41 sam 12 11
c from shannon to handle tabs properly and print neater 
c messages when closing connections; also ignore 0177 as a special 
c character -- guess early hope was to propagate break's, but they 
c should be mapped by the terminal handler into signals...
e
s 00043/00014/00323
d D 4.11 83/03/31 10:16:22 edward 11 10
c Fixed backgrounding bug.  Now uses new signals.
e
s 00003/00001/00334
d D 4.10 83/03/03 15:46:47 sam 10 9
c fix from ed wang for hanging on logout
e
s 00007/00007/00328
d D 4.9 83/02/09 17:05:22 sam 9 8
c from sun
e
s 00006/00003/00329
d D 4.8 83/01/18 19:27:51 sam 8 7
c put debugging back in
e
s 00050/00057/00282
d D 4.7 82/12/25 21:11:51 sam 7 6
c use new ioctls; add ^Y command; fix exiting bug
e
s 00000/00004/00339
d D 4.6 82/12/05 22:46:04 sam 6 5
c had broken interrupt flushing
e
s 00157/00454/00186
d D 4.5 82/11/27 16:21:58 sam 5 4
c major rework: 4.1c, netdb.h, eliminate crud, ...
e
s 00004/00002/00636
d D 4.4 82/11/15 01:22:51 sam 4 3
c null pointer problem with TERM
e
s 00002/00002/00636
d D 4.3 82/11/14 15:13:34 sam 3 2
c convert to 4.1c sys calls and directory layout
e
s 00003/00002/00635
d D 4.2 82/04/06 12:54:27 jkf 2 1
c remember settings of ECHO and CRMOD
e
s 00637/00000/00000
d D 4.1 82/04/02 10:28:57 wnj 1 0
c date and time created 82/04/02 10:28:57 by wnj
e
u
U
f b 
t
T
I 44
D 47

E 44
I 19
/*
I 44
 *	$Source: /a/staff/kfall/mit/rlogin/RCS/rlogin.c,v $
 *	$Header: /a/staff/kfall/mit/rlogin/RCS/rlogin.c,v 5.2 89/07/26 12:11:21 kfall Exp Locker: kfall $
 */

/*
E 44
D 36
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 36
I 36
 * Copyright (c) 1983 The Regents of the University of California.
E 47
I 47
D 53
/*-
E 53
I 53
/*
E 53
D 68
 * Copyright (c) 1983, 1990 The Regents of the University of California.
E 47
 * All rights reserved.
E 68
I 68
 * Copyright (c) 1983, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 68
 *
D 47
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
E 47
I 47
D 52
%sccs.include.redist.c%
E 52
I 52
 * %sccs.include.redist.c%
E 52
E 47
E 36
 */

E 19
I 1
#ifndef lint
D 15
static char sccsid[] = "%W% %E%";
E 15
I 15
D 19
static char sccsid[] = "%W% (Berkeley) %E%";
E 15
#endif
E 19
I 19
D 68
char copyright[] =
D 36
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 36
I 36
D 37
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 37
I 37
D 47
"@(#) Copyright (c) 1983 The Regents of the University of California.\n\
E 47
I 47
"%Z% Copyright (c) 1983, 1990 The Regents of the University of California.\n\
E 47
E 37
E 36
 All rights reserved.\n";
E 68
I 68
static char copyright[] =
"%Z% Copyright (c) 1983, 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 68
D 36
#endif not lint
E 36
I 36
#endif /* not lint */
E 36

#ifndef lint
D 37
static char sccsid[] = "%W% (Berkeley) %G%";
E 37
I 37
D 47
static char sccsid[] = "@(#)rlogin.c	5.12 (Berkeley) 9/19/88";
E 47
I 47
static char sccsid[] = "%W% (Berkeley) %G%";
E 47
E 37
D 36
#endif not lint
E 36
I 36
#endif /* not lint */
E 36
E 19

I 13
/*
I 47
D 64
 * $Source: mit/rlogin/RCS/rlogin.c,v $
D 52
 * $Header: mit/rlogin/RCS/rlogin.c,v 5.2 89/07/26 12:11:21 kfall Exp Locker: kfall $
E 52
I 52
 * $Header: mit/rlogin/RCS/rlogin.c,v 5.2 89/07/26 12:11:21 kfall
 *	Exp Locker: kfall $
E 52
 */

/*
E 64
E 47
 * rlogin - remote login
 */
E 13
D 5
#include <stdio.h>
#include <sgtty.h>
E 5
D 32
#include <sys/types.h>
E 32
I 32
#include <sys/param.h>
E 32
I 29
D 52
#include <sys/errno.h>
E 52
E 29
I 22
D 64
#include <sys/file.h>
E 64
E 22
#include <sys/socket.h>
I 47
D 64
#include <sys/signal.h>
E 64
E 47
I 34
#include <sys/time.h>
#include <sys/resource.h>
E 34
I 15
#include <sys/wait.h>
I 69
#include <sys/ioctl.h>
E 69
E 15
I 5

E 5
D 3
#include <net/in.h>
E 3
I 3
#include <netinet/in.h>
I 53
#include <netinet/in_systm.h>
#include <netinet/ip.h>
E 53
I 47
D 64
#include <netdb.h>
E 64
E 47
I 5

D 47
#include <stdio.h>
E 47
D 64
#include <sgtty.h>
I 47
#include <setjmp.h>
E 47
E 5
E 3
D 54
#include <errno.h>
E 54
I 47
#include <varargs.h>
E 64
I 54
#include <errno.h>
I 64
#include <fcntl.h>
#include <netdb.h>
E 64
E 54
E 47
#include <pwd.h>
I 64
#include <setjmp.h>
D 69
#include <sgtty.h>
E 69
I 69
#include <termios.h>
E 69
#include <signal.h>
D 66
#include <stdarg.h>
E 66
E 64
I 5
D 47
#include <signal.h>
I 29
#include <setjmp.h>
E 29
#include <netdb.h>
E 47
I 47
#include <stdio.h>
D 64
#include <unistd.h>
E 64
I 64
#include <stdlib.h>
E 64
D 50
#include <strings.h>
E 50
I 50
#include <string.h>
I 64
#include <unistd.h>
I 66

#ifdef __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
E 66
E 64
E 50
E 47
I 17
D 24
#include <setjmp.h>
E 24
E 17
I 11
D 15
#include <wait.h>
E 15
E 11
E 5

I 37
D 47
#ifdef	KERBEROS
E 47
I 47
#ifdef KERBEROS
I 49
#include <kerberosIV/des.h>
E 49
E 47
D 44
#include <kerberos/krb.h>
E 44
I 44
D 46
#include <krb.h>
E 46
I 46
#include <kerberosIV/krb.h>
E 46
E 44
D 47
int		encrypt = 0;
D 44
char		krb_realm[REALM_SZ];
E 44
I 44
char		dst_realm_buf[REALM_SZ];
char		*dest_realm = NULL;
E 44
CREDENTIALS	cred;
Key_schedule	schedule;
I 38
int		use_kerberos = 1;
I 44
extern char	*krb_realmofhost();
E 44
E 38
#endif	/* KERBEROS */
E 47

I 64
#include "krb.h"

E 64
E 37
I 24
D 47
# ifndef TIOCPKT_WINDOW
# define TIOCPKT_WINDOW 0x80
# endif TIOCPKT_WINDOW
E 47
I 47
CREDENTIALS cred;
Key_schedule schedule;
D 58
int use_kerberos = 1, encrypt;
E 58
I 58
int use_kerberos = 1, doencrypt;
E 58
char dst_realm_buf[REALM_SZ], *dest_realm = NULL;
D 64
extern char *krb_realmofhost();
E 64
#endif
E 47

E 24
D 13
/*
D 5
 * rlogin - remote login; this is a hacked version of cu
E 5
I 5
 * rlogin - remote login
E 5
 */
E 13
D 34
char	*index(), *rindex(), *malloc(), *getenv();
E 34
I 34
D 47
/* concession to sun */
# ifndef SIGUSR1
# define SIGUSR1 30
# endif SIGUSR1
E 47
I 47
#ifndef TIOCPKT_WINDOW
#define	TIOCPKT_WINDOW	0x80
#endif
E 47

D 47
char	*index(), *rindex(), *malloc(), *getenv(), *strcat(), *strcpy();
E 34
struct	passwd *getpwuid();
D 5
struct	passwd *pwd;
char	*name, *pass;
E 5
I 5
char	*name;
E 5
int	rem;
char	cmdchar = '~';
D 8
int	rcmdoptions = 0;
E 8
int	eight;
I 18
int	litout;
E 18
char	*speeds[] =
    { "0", "50", "75", "110", "134", "150", "200", "300",
      "600", "1200", "1800", "2400", "4800", "9600", "19200", "38400" };
D 4
char	term[64];
E 4
I 4
D 5
char	term[64] = "dumb";
E 5
I 5
D 17
char	term[64] = "network";
E 17
I 17
char	term[256] = "network";
E 17
extern	int errno;
int	lostpeer();
I 17
D 24
int	nosigwin;
jmp_buf	winsizechanged;
E 24
I 24
int	dosigwinch = 0;
I 32
#ifndef sigmask
#define sigmask(m)	(1 << ((m)-1))
E 47
I 47
/* concession to Sun */
#ifndef SIGUSR1
#define	SIGUSR1	30
E 47
#endif
I 47

D 61
extern int errno;
E 61
int eight, litout, rem;
D 54
char cmdchar;
E 54
I 54

int noescape;
u_char escapechar = '~';

E 54
D 69
char *speeds[] = {
	"0", "50", "75", "110", "134", "150", "200", "300", "600", "1200",
	"1800", "2400", "4800", "9600", "19200", "38400"
};

E 69
E 47
D 64
#ifdef sun
E 64
I 64
D 67
#ifdef SUNOS4
E 67
I 67
#ifdef OLDSUN
E 67
E 64
D 34
struct	ttysize winsize;
E 34
struct winsize {
	unsigned short ws_row, ws_col;
	unsigned short ws_xpixel, ws_ypixel;
};
I 64
#else
#define	get_window_size(fd, wp)	ioctl(fd, TIOCGWINSZ, wp)
E 64
D 34
#else sun
E 32
D 28
int	nosigwin = 0;
E 28
E 24
struct	winsize winsize;
E 34
I 32
D 47
#endif sun
E 47
I 47
#endif
E 47
I 34
struct	winsize winsize;
E 34
E 32
D 24
int	sigwinch();
E 24
I 24
D 47
int	sigwinch(), oob();
E 47
E 24
E 17
E 5
E 4

I 34
D 47
/*
 * The following routine provides compatibility (such as it is)
 * between 4.2BSD Suns and others.  Suns have only a `ttysize',
 * so we convert it to a winsize.
 */
#ifdef sun
int
get_window_size(fd, wp)
	int fd;
	struct winsize *wp;
{
	struct ttysize ts;
	int error;
E 47
I 47
D 64
#ifndef sun
#define	get_window_size(fd, wp)	ioctl(fd, TIOCGWINSZ, wp)
E 64
I 64
void		catch_child __P((int));
void		copytochild __P((int));
D 69
__dead void	doit __P((long));
E 69
I 69
__dead void	doit __P((sigset_t *));
E 69
__dead void	done __P((int));
void		echo __P((char));
u_int		getescape __P((char *));
void		lostpeer __P((int));
void		mode __P((int));
void		msg __P((char *));
void		oob __P((int));
D 69
int		reader __P((int));
E 69
I 69
int		reader __P((sigset_t *));
E 69
void		sendwindow __P((void));
void		setsignal __P((int));
I 70
int		speed __P((int));
E 70
void		sigwinch __P((int));
void		stop __P((char));
__dead void	usage __P((void));
void		writer __P((void));
void		writeroob __P((int));

#ifdef	KERBEROS
void		warning __P((const char *, ...));
E 64
#endif
I 64
D 67
#ifdef SUNOS4
E 67
I 67
#ifdef OLDSUN
E 67
int		get_window_size __P((int, struct winsize *));
#endif
E 64
E 47

D 47
	if ((error = ioctl(0, TIOCGSIZE, &ts)) != 0)
		return (error);
	wp->ws_row = ts.ts_lines;
	wp->ws_col = ts.ts_cols;
	wp->ws_xpixel = 0;
	wp->ws_ypixel = 0;
	return (0);
}
#else sun
#define get_window_size(fd, wp)	ioctl(fd, TIOCGWINSZ, wp)
#endif sun
E 47
I 47
D 64
void exit();
E 47

E 64
I 64
int
E 64
E 34
I 5
D 6
#define	CTRL(c)	('c' & 037)

E 6
E 5
main(argc, argv)
	int argc;
D 64
	char **argv;
E 64
I 64
	char *argv[];
E 64
{
D 5
	int pid;
	char *host, *cp, **ap, buf[BUFSIZ];
	register int cc;
E 5
I 5
D 47
	char *host, *cp;
E 5
	struct sgttyb ttyb;
	struct passwd *pwd;
E 47
I 47
D 69
	extern char *optarg;
	extern int optind;
E 69
	struct passwd *pw;
E 47
I 5
	struct servent *sp;
I 62
D 64
	struct hostent *hp;
E 64
E 62
D 8
	int uid;
E 8
I 8
D 24
	int uid, options = 0;
E 24
I 24
D 47
	int uid, options = 0, oldmask;
E 24
I 16
	int on = 1;
E 47
I 47
D 69
	struct sgttyb ttyb;
	long omask;
	int argoff, ch, dflag, one, uid;
E 69
I 69
	sigset_t smask;
	uid_t uid;
	int argoff, ch, dflag, one;
E 69
	char *host, *p, *user, term[1024];
I 69
	struct sigaction sa;
E 69
D 63
	void lostpeer();
E 63
I 63
D 64
	void lostpeer(), copytochild(), writeroob();
E 63
I 54
	u_char getescape();
E 54
	char *getenv();
E 64
E 47
E 16
E 8
E 5

D 47
	host = rindex(argv[0], '/');
	if (host)
		host++;
E 47
I 47
	argoff = dflag = 0;
	one = 1;
	host = user = NULL;
D 54
	cmdchar = '~';
E 54

D 69
	if (p = rindex(argv[0], '/'))
E 69
I 69
	if (p = strrchr(argv[0], '/'))
E 69
		++p;
E 47
	else
D 47
		host = argv[0];
	argv++, --argc;
	if (!strcmp(host, "rlogin"))
		host = *argv++, --argc;
another:
D 9
	if (!strcmp(*argv, "-d")) {
E 9
I 9
	if (argc > 0 && !strcmp(*argv, "-d")) {
E 9
		argv++, argc--;
D 8
		rcmdoptions |= SO_DEBUG;
E 8
I 8
		options |= SO_DEBUG;
E 8
		goto another;
	}
D 9
	if (!strcmp(*argv, "-l")) {
E 9
I 9
	if (argc > 0 && !strcmp(*argv, "-l")) {
E 9
		argv++, argc--;
		if (argc == 0)
			goto usage;
		name = *argv++; argc--;
		goto another;
	}
D 9
	if (!strncmp(*argv, "-e", 2)) {
E 9
I 9
	if (argc > 0 && !strncmp(*argv, "-e", 2)) {
E 9
		cmdchar = argv[0][2];
		argv++, argc--;
		goto another;
	}
D 9
	if (!strcmp(*argv, "-8")) {
E 9
I 9
	if (argc > 0 && !strcmp(*argv, "-8")) {
E 9
		eight = 1;
		argv++, argc--;
		goto another;
	}
I 18
	if (argc > 0 && !strcmp(*argv, "-L")) {
		litout = 1;
		argv++, argc--;
		goto another;
	}
E 47
I 47
		p = argv[0];
E 47
I 37

D 47
#ifdef	KERBEROS
	if (argc > 0 && !strcmp(*argv, "-x")) {
		encrypt = 1;
		des_set_key(cred.session, schedule);
		argv++, argc--;
		goto another;
E 47
I 47
D 69
	if (strcmp(p, "rlogin"))
E 69
I 69
	if (strcmp(p, "rlogin") != 0)
E 69
		host = p;

	/* handle "rlogin host flags" */
	if (!host && argc > 2 && argv[1][0] != '-') {
		host = argv[1];
		argoff = 1;
E 47
	}
I 39
D 47
	if (argc > 0 && !strcmp(*argv, "-k")) {
		argv++, argc--;
		if(argc <= 0 || (**argv == '-')) {
			fprintf(stderr, "-k option requires an argument\n");
			exit(1);
E 47
I 47

#ifdef KERBEROS
D 48
#define	OPTIONS	"8Lde:k:l:x"
E 48
I 48
D 54
#define	OPTIONS	"8KLde:k:l:x"
E 54
I 54
#define	OPTIONS	"8EKLde:k:l:x"
E 54
E 48
#else
D 48
#define	OPTIONS	"8Lde:l:"
E 48
I 48
D 54
#define	OPTIONS	"8KLde:l:"
E 54
I 54
#define	OPTIONS	"8EKLde:l:"
E 54
E 48
#endif
	while ((ch = getopt(argc - argoff, argv + argoff, OPTIONS)) != EOF)
		switch(ch) {
		case '8':
			eight = 1;
			break;
I 54
		case 'E':
			noescape = 1;
			break;
E 54
I 48
		case 'K':
#ifdef KERBEROS
			use_kerberos = 0;
#endif
			break;
E 48
		case 'L':
			litout = 1;
			break;
		case 'd':
			dflag = 1;
			break;
		case 'e':
I 60
			noescape = 0;
E 60
D 54
			cmdchar = optarg[0];
E 54
I 54
			escapechar = getescape(optarg);
E 54
			break;
#ifdef KERBEROS
		case 'k':
			dest_realm = dst_realm_buf;
			(void)strncpy(dest_realm, optarg, REALM_SZ);
			break;
#endif
		case 'l':
			user = optarg;
			break;
D 55
#ifdef KERBEROS
E 55
I 55
D 56
#if defined(KERBEROS) && defined(CRYPT)
E 56
I 56
D 57
D 59
#ifdef CRYPT
#ifdef KERBEROS
E 56
E 55
		case 'x':
D 58
			encrypt = 1;
E 58
I 58
			doencrypt = 1;
E 58
			des_set_key(cred.session, schedule);
			break;
#endif
I 56
#endif
E 59
E 57
E 56
		case '?':
		default:
			usage();
E 47
		}
D 44
		strncpy(krb_realm, *argv, REALM_SZ);
E 44
I 44
D 47
		dest_realm = dst_realm_buf;
		strncpy(dest_realm, *argv, REALM_SZ);
E 44
		argv++, argc--;
		goto another;
	}
E 47
I 47
	optind += argoff;
	argc -= optind;
	argv += optind;
E 47

E 39
D 47
#endif	/* KERBEROS */
E 47
I 47
	/* if haven't gotten a host yet, do so */
	if (!host && !(host = *argv++))
		usage();
E 47

E 37
E 18
I 17
D 28
	if (argc > 0 && !strcmp(*argv, "-w")) {
		nosigwin++;
		argv++, argc--;
		goto another;
	}
E 28
E 17
D 47
	if (host == 0)
		goto usage;
	if (argc > 0)
		goto usage;
D 44
	pwd = getpwuid(getuid());
E 44
I 44
	uid = getuid();
	pwd = getpwuid(uid);
E 44
	if (pwd == 0) {
		fprintf(stderr, "Who are you?\n");
E 47
I 47
	if (*argv)
		usage();

D 69
	if (!(pw = getpwuid(uid = getuid()))) {
		(void)fprintf(stderr, "rlogin: unknown user id.\n");
E 47
		exit(1);
	}
E 69
I 69
	if (!(pw = getpwuid(uid = getuid())))
		errx(1, "unknown user id.");
D 71

E 71
I 71
	/* Accept user1@host format, though "-l user2" overrides user1 */
	p = strchr(host, '@');
	if (p) {
		*p = '\0';
		if (!user && p > host)
			user = host;
		host = p + 1;
		if (*host == '\0')
			usage();
	}
E 71
E 69
I 38
D 47
#ifdef	KERBEROS
E 47
I 47
	if (!user)
		user = pw->pw_name;

I 48
	sp = NULL;
E 48
#ifdef KERBEROS
E 47
D 42
	sp = getservbyname("klogin", "tcp");
E 42
I 42
D 48
	sp = getservbyname((encrypt ? "eklogin" : "klogin"), "tcp");
E 42
	if(sp == NULL) {
		use_kerberos = 0;
D 47
		old_warning("klogin service unknown");
E 47
I 47
		warning("can't get entry for %s/tcp service",
		    encrypt ? "eklogin" : "klogin");
E 47
		sp = getservbyname("login", "tcp");
E 48
I 48
	if (use_kerberos) {
D 58
		sp = getservbyname((encrypt ? "eklogin" : "klogin"), "tcp");
E 58
I 58
		sp = getservbyname((doencrypt ? "eklogin" : "klogin"), "tcp");
E 58
		if (sp == NULL) {
			use_kerberos = 0;
			warning("can't get entry for %s/tcp service",
D 58
			    encrypt ? "eklogin" : "klogin");
E 58
I 58
			    doencrypt ? "eklogin" : "klogin");
E 58
		}
E 48
	}
D 48
#else
E 38
D 5
	cc = 0;
E 5
I 5
	sp = getservbyname("login", "tcp");
E 48
I 38
#endif
I 48
	if (sp == NULL)
		sp = getservbyname("login", "tcp");
E 48
E 38
D 47
	if (sp == 0) {
		fprintf(stderr, "rlogin: login/tcp: unknown service\n");
		exit(2);
E 47
I 47
D 69
	if (sp == NULL) {
		(void)fprintf(stderr, "rlogin: login/tcp: unknown service.\n");
		exit(1);
E 47
	}
E 69
I 69
	if (sp == NULL)
		errx(1, "login/tcp: unknown service.");
E 69
E 5
D 4
	strcpy(term, getenv("TERM"));
E 4
I 4
D 47
	cp = getenv("TERM");
	if (cp)
D 34
		strcpy(term, cp);
E 34
I 34
		(void) strcpy(term, cp);
E 47
I 47

D 69
	(void)strcpy(term, (p = getenv("TERM")) ? p : "network");
E 47
E 34
E 4
D 7
	if (gtty(0, &ttyb)==0) {
E 7
I 7
D 17
	if (ioctl(0, TIOCGETP, &ttyb)==0) {
E 17
I 17
	if (ioctl(0, TIOCGETP, &ttyb) == 0) {
E 17
E 7
D 34
		strcat(term, "/");
		strcat(term, speeds[ttyb.sg_ospeed]);
E 34
I 34
D 47
		(void) strcat(term, "/");
		(void) strcat(term, speeds[ttyb.sg_ospeed]);
E 47
I 47
		(void)strcat(term, "/");
D 64
		(void)strcat(term, speeds[ttyb.sg_ospeed]);
E 64
I 64
		(void)strcat(term, speeds[(int)ttyb.sg_ospeed]);
E 64
E 47
E 34
	}
E 69
I 69
	(void)snprintf(term, sizeof(term), "%s/%d",
			((p = getenv("TERM")) ? p : "network"),
D 70
			cfgetispeed(0));
E 70
I 70
			speed(0));
E 70
E 69
I 32
D 34
#ifdef sun
	(void) ioctl(0, TIOCGSIZE, &winsize);
#else sun
E 32
I 17
D 24
	if (!nosigwin && ioctl(0, TIOCGWINSZ, &winsize) == 0) {
		cp = index(term, '\0');
		sprintf(cp, "/%u,%u,%u,%u", winsize.ws_row, winsize.ws_col,
		    winsize.ws_xpixel, winsize.ws_ypixel);
	}
E 24
I 24
	(void) ioctl(0, TIOCGWINSZ, &winsize);
I 32
#endif sun
E 32
E 24
E 17
D 5
        rem = rcmd(&host, IPPORT_LOGINSERVER, pwd->pw_name,
E 5
I 5
D 11
	signal(SIGPIPE, lostpeer);
E 11
I 11
D 13
	sigset(SIGPIPE, lostpeer);
E 13
I 13
	signal(SIGPIPE, lostpeer);
I 24
	signal(SIGURG, oob);
	oldmask = sigblock(sigmask(SIGURG));
E 34
I 34
D 47
	(void) get_window_size(0, &winsize);
	(void) signal(SIGPIPE, lostpeer);
E 47
I 47

	(void)get_window_size(0, &winsize);

D 69
	(void)signal(SIGPIPE, lostpeer);
E 69
I 69
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = lostpeer;
	(void)sigaction(SIGPIPE, &sa, (struct sigaction *) 0);
E 69
E 47
	/* will use SIGUSR1 for window size hack, so hold it off */
D 47
	oldmask = sigblock(sigmask(SIGURG) | sigmask(SIGUSR1));
E 47
I 47
D 69
	omask = sigblock(sigmask(SIGURG) | sigmask(SIGUSR1));
E 69
I 69
	sigemptyset(&smask);
	sigaddset(&smask, SIGURG);
	sigaddset(&smask, SIGUSR1);
	(void)sigprocmask(SIG_SETMASK, &smask, &smask);
E 69
I 63
	/*
	 * We set SIGURG and SIGUSR1 below so that an
	 * incoming signal will be held pending rather than being
	 * discarded. Note that these routines will be ready to get
	 * a signal by the time that they are unblocked below.
	 */
D 69
	(void)signal(SIGURG, copytochild);
	(void)signal(SIGUSR1, writeroob);
E 69
I 69
	sa.sa_handler = copytochild;
	(void)sigaction(SIGURG, &sa, (struct sigaction *) 0);
	sa.sa_handler = writeroob;
	(void)sigaction(SIGUSR1, &sa, (struct sigaction *) 0);
E 69
E 63
E 47
I 37

D 47
#ifdef	KERBEROS
E 47
I 47
#ifdef KERBEROS
E 47
D 38
	rem = KSUCCESS;
	if(krb_realm[0] == '\0') {
		rem = get_krbrlm(krb_realm, 1);
	}
	if(rem == KSUCCESS) {
		if(encrypt) {
			rem = krcmd_mutual(
				&host, sp->s_port,
				name ? name : pwd->pw_name, term,
				0, krb_realm,
				&cred, schedule
			);
E 38
I 38
try_connect:
D 47
	if(use_kerberos) {
E 47
I 47
	if (use_kerberos) {
I 62
D 64
		/* fully qualify hostname (needed for krb_realmofhost) */
E 64
I 64
		struct hostent *hp;

		/* Fully qualify hostname (needed for krb_realmofhost). */
E 64
		hp = gethostbyname(host);
D 69
		if (hp != NULL && !(host = strdup(hp->h_name))) {
D 64
			(void)fprintf(stderr, "rlogin: %s.\n", strerror(ENOMEM));
E 64
I 64
			(void)fprintf(stderr, "rlogin: %s\n",
			    strerror(ENOMEM));
E 64
			exit(1);
		}
E 69
I 69
		if (hp != NULL && !(host = strdup(hp->h_name)))
			errx(1, "%s", strerror(ENOMEM));
E 69

E 62
E 47
		rem = KSUCCESS;
I 47
		errno = 0;
E 47
D 44
		if(krb_realm[0] == '\0') {
D 41
			rem = get_krbrlm(krb_realm, 1);
E 41
I 41
			rem = krb_get_lrealm(krb_realm, 1);
E 41
		}
		if(rem == KSUCCESS) {
I 43
			setreuid(0,getuid());
E 43
			if(encrypt) {
				rem = krcmd_mutual(
					&host, sp->s_port,
					name ? name : pwd->pw_name, term,
					0, krb_realm,
					&cred, schedule
				);
			} else {
				rem = krcmd(
			    		&host, sp->s_port,
					name ? name : pwd->pw_name, term,
					0, krb_realm
				);
			}
I 43
			setuid(geteuid());
E 44
I 44
		if (dest_realm == NULL)
			dest_realm = krb_realmofhost(host);

I 55
D 57
D 59
#ifdef CRYPT
E 55
D 47
		errno = 0;
		if(encrypt) {
			rem = krcmd_mutual(
				&host, sp->s_port,
				name ? name : pwd->pw_name, term,
				0, dest_realm,
				&cred, schedule
			);
E 44
E 43
E 38
		} else {
D 38
			rem = krcmd(
			    	&host, sp->s_port,
			    	name ? name : pwd->pw_name, term,
			    	0, krb_realm
E 38
I 38
D 44
			fprintf(
				stderr,
				"rlogin: Kerberos error getting local realm %s\n",
				krb_err_txt[rem]
E 44
I 44
			rem = krcmd(
				&host, sp->s_port,
				name ? name : pwd->pw_name, term,
				0, dest_realm
E 44
E 38
			);
I 38
D 44
			exit(1);
E 44
E 38
		}
E 47
I 47
D 58
		if (encrypt)
E 58
I 58
		if (doencrypt)
E 58
			rem = krcmd_mutual(&host, sp->s_port, user, term, 0,
			    dest_realm, &cred, schedule);
		else
I 55
#endif /* CRYPT */
E 59
E 57
E 55
			rem = krcmd(&host, sp->s_port, user, term, 0,
			    dest_realm);
E 47
I 38
D 44
		if((rem < 0) && errno == ECONNREFUSED) {
E 44
I 44
		if (rem < 0) {
E 44
			use_kerberos = 0;
I 41
			sp = getservbyname("login", "tcp");
D 47
			if(sp == NULL) {
D 44
				fprintf(stderr, "unknown service login/tcp\n");
E 44
I 44
				fprintf(stderr,
					"unknown service login/tcp\n");
E 47
I 47
D 69
			if (sp == NULL) {
				(void)fprintf(stderr,
				    "rlogin: unknown service login/tcp.\n");
E 47
E 44
				exit(1);
			}
E 69
I 69
			if (sp == NULL)
				errx(1, "unknown service login/tcp.");
E 69
E 41
D 44
			old_warning("remote host doesn't support Kerberos");
E 44
I 44
			if (errno == ECONNREFUSED)
D 47
				old_warning("remote host doesn't support Kerberos");
E 47
I 47
				warning("remote host doesn't support Kerberos");
E 47
			if (errno == ENOENT)
D 47
				old_warning("Can't provide Kerberos auth data");
E 47
I 47
				warning("can't provide Kerberos auth data");
E 47
E 44
			goto try_connect;
		}
E 38
	} else {
I 55
D 57
D 59
#ifdef CRYPT
E 55
D 38
		fprintf(
			stderr,
			"rlogin: Kerberos error getting local realm %s\n",
			krb_err_txt[rem]
		);
		exit(1);
E 38
I 38
D 47
		if(encrypt) {
D 44
			fprintf(stderr, "The -x flag requires Kerberos authencation\n");
E 44
I 44
			fprintf(stderr, "The -x flag requires Kerberos authentication\n");
E 47
I 47
D 58
		if (encrypt) {
E 58
I 58
D 69
		if (doencrypt) {
E 58
			(void)fprintf(stderr,
			    "rlogin: the -x flag requires Kerberos authentication.\n");
E 47
E 44
			exit(1);
		}
E 69
I 69
		if (doencrypt)
			errx(1, "the -x flag requires Kerberos authentication.");
E 69
I 55
#endif /* CRYPT */
E 59
E 57
E 55
D 47
        	rem = rcmd(&host, sp->s_port, pwd->pw_name,
	    		name ? name : pwd->pw_name, term, 0);
E 47
I 47
		rem = rcmd(&host, sp->s_port, pw->pw_name, user, term, 0);
E 47
E 38
	}
I 38
#else
D 47
       	rem = rcmd(&host, sp->s_port, pwd->pw_name,
    		name ? name : pwd->pw_name, term, 0);
E 47
I 47
	rem = rcmd(&host, sp->s_port, pw->pw_name, user, term, 0);
E 47
D 55
#endif
E 55
I 55
#endif /* KERBEROS */
E 55
E 38

D 38
#else	/* !KERBEROS */

E 37
E 34
E 24
E 13
E 11
        rem = rcmd(&host, sp->s_port, pwd->pw_name,
E 5
	    name ? name : pwd->pw_name, term, 0);
D 37
        if (rem < 0)
                exit(1);
E 37
I 37

#endif	/* KERBEROS */

E 38
D 47
	if(rem < 0) 
E 47
I 47
	if (rem < 0)
E 47
		exit(1);

E 37
I 8
D 47
	if (options & SO_DEBUG &&
D 16
	    setsockopt(rem, SOL_SOCKET, SO_DEBUG, 0, 0) < 0)
E 16
I 16
	    setsockopt(rem, SOL_SOCKET, SO_DEBUG, &on, sizeof (on)) < 0)
E 16
		perror("rlogin: setsockopt (SO_DEBUG)");
E 8
D 5
	setuid(getuid());
	cumain();
	exit(0);
E 5
I 5
D 44
	uid = getuid();
E 44
	if (setuid(uid) < 0) {
		perror("rlogin: setuid");
		exit(1);
	}
D 24
	doit();
E 24
I 24
	doit(oldmask);
E 47
I 47
	if (dflag &&
	    setsockopt(rem, SOL_SOCKET, SO_DEBUG, &one, sizeof(one)) < 0)
D 69
		(void)fprintf(stderr, "rlogin: setsockopt: %s.\n",
		    strerror(errno));
E 69
I 69
		warn("setsockopt DEBUG (ignored)");
E 69
I 53
	one = IPTOS_LOWDELAY;
	if (setsockopt(rem, IPPROTO_IP, IP_TOS, (char *)&one, sizeof(int)) < 0)
D 69
		perror("rlogin: setsockopt TOS (ignored)");
E 69
I 69
		warn("setsockopt TOS (ignored)");
E 69
E 53

	(void)setuid(uid);
D 69
	doit(omask);
E 69
I 69
	doit(&smask);
E 69
E 47
E 24
	/*NOTREACHED*/
E 5
D 47
usage:
	fprintf(stderr,
I 37
#ifdef	KERBEROS
D 40
	    "usage: rlogin host [ -ex ] [ -l username ] [ -8 ] [ -L ] [ -x ]\n");
E 40
I 40
	    "usage: rlogin host [ -ex ] [ -l username ] [ -k realm ] [ -8 ] [ -L ] [ -x ]\n");
E 40
#else
E 37
D 12
	    "usage: rlogin host [ -ex ] [ -l username ]\n");
E 12
I 12
D 18
	    "usage: rlogin host [ -ex ] [ -l username ] [ -8 ]\n");
E 18
I 18
D 28
	    "usage: rlogin host [ -ex ] [ -l username ] [ -8 ] [ -L ] [ -w ]\n");
E 28
I 28
	    "usage: rlogin host [ -ex ] [ -l username ] [ -8 ] [ -L ]\n");
I 37
#endif
E 37
E 28
E 18
E 12
	exit(1);
E 47
}

I 70
#if BSD >= 198810
int
speed(fd)
	int fd;
{
	struct termios tt;

	(void)tcgetattr(fd, &tt);

	return ((int) cfgetispeed(&tt));
}
#else
int    speeds[] = {	/* for older systems, B0 .. EXTB */
	0, 50, 75, 110,
	134, 150, 200, 300,
	600, 1200, 1800, 2400,
	4800, 9600, 19200, 38400
};

int
speed(fd)
	int fd;
{
	struct termios tt;

	(void)tcgetattr(fd, &tt);

	return (speeds[(int)cfgetispeed(&tt)]);
}
#endif

E 70
D 5
#include <ctype.h>
#include <signal.h>

E 5
D 47
#define CRLF "\r\n"
E 47
I 47
D 69
int child, defflags, deflflags, tabflag;
char deferase, defkill;
struct tchars deftc;
struct ltchars defltc;
struct tchars notc = { -1, -1, -1, -1, -1, -1 };
struct ltchars noltc = { -1, -1, -1, -1, -1, -1 };
E 69
I 69
pid_t child;
struct termios deftt;
struct termios nott;
E 69
E 47
D 5
#define wrc(ds) write(ds,&c,1)
E 5

I 64
void
E 64
D 5
char	tkill, terase;	/* current input kill & erase */
int	efk;		/* process of id of listener  */
char	c, oc;
int	pipes[] = {-1,-1};
int	intr, sig2();
int	parent;

int	nhup;
E 5
I 5
D 47
int	child;
E 5
D 11
int	done();
E 11
I 11
int	catchild();
I 24
D 34
int	writeroob();
E 34
I 34
int	copytochild(), writeroob();
E 34
E 24
E 11

D 5
struct tchars deftchars;
struct tchars notchars = { 0377, 0377, 'q'&037, 's'&037, 0377, 0377 };
struct ltchars defltchars;
struct ltchars noltchars = { 0377, 0377, 0377, 0377, 0377, 0377 };
D 2
char defkill, deferase;
E 2
I 2
char defkill, deferase, defflags;
E 5
I 5
D 7
char	tkill, terase;	/* current input kill & erase */
char	defkill, deferase, defflags;
E 7
I 7
D 14
int	defflags;
I 12
int	tabflag;
E 12
struct	ttychars deftc;
struct	ttychars notc = {
	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1
};
E 14
I 14
int	defflags, tabflag;
I 18
int	deflflags;
E 18
char	deferase, defkill;
struct	tchars deftc;
struct	ltchars defltc;
struct	tchars notc =	{ -1, -1, -1, -1, -1, -1 };
struct	ltchars noltc =	{ -1, -1, -1, -1, -1, -1 };
E 14
E 7
E 5
E 2

D 5
cumain()
E 5
I 5
D 7
struct	tchars deftchars;
struct	tchars notchars = { -1, -1, CTRL(q), CTRL(s), -1, -1 };
struct	ltchars defltchars;
struct	ltchars noltchars = { -1, -1, -1, -1, -1, -1 };

E 7
D 24
doit()
E 24
I 24
doit(oldmask)
E 47
I 47
D 69
doit(omask)
	long omask;
E 69
I 69
doit(smask)
	sigset_t *smask;
E 69
E 47
E 24
E 5
{
D 5
	int fk;
	int speed;
	char *telno;
E 5
D 7
	struct sgttyb stbuf;
E 7
D 47
	int exit();
E 47
I 14
D 69
	struct sgttyb sb;
E 69
I 69
	int i;
	struct sigaction sa;
E 69
I 47
D 63
	void catch_child(), copytochild(), exit(), writeroob();
E 63
I 63
D 64
	void catch_child(), exit();
E 64
E 63
E 47
E 14

D 5
	gtty(0, &stbuf);
E 5
I 5
D 7
	ioctl(0, TIOCGETP, (char *)&stbuf);
E 5
	defkill = stbuf.sg_kill;
	deferase = stbuf.sg_erase;
I 2
	defflags = stbuf.sg_flags & (ECHO | CRMOD);
E 2
D 5
	ioctl(0, TIOCGETC, &deftchars);
	ioctl(0, TIOCGLTC, &defltchars);
E 5
I 5
	ioctl(0, TIOCGETC, (char *)&deftchars);
	ioctl(0, TIOCGLTC, (char *)&defltchars);
E 7
I 7
D 14
	ioctl(0, TIOCGET, (char *)&defflags);
E 14
I 14
D 34
	ioctl(0, TIOCGETP, (char *)&sb);
E 34
I 34
D 47
	(void) ioctl(0, TIOCGETP, (char *)&sb);
E 47
I 47
D 69
	(void)ioctl(0, TIOCGETP, (char *)&sb);
E 47
E 34
	defflags = sb.sg_flags;
E 14
I 12
	tabflag = defflags & TBDELAY;
E 12
	defflags &= ECHO | CRMOD;
D 14
	ioctl(0, TIOCCGET, (char *)&deftc);
	notc.tc_startc = deftc.tc_startc;
	notc.tc_stopc = deftc.tc_stopc;
E 14
I 14
	deferase = sb.sg_erase;
	defkill = sb.sg_kill;
I 18
D 34
	ioctl(0, TIOCLGET, (char *)&deflflags);
E 18
	ioctl(0, TIOCGETC, (char *)&deftc);
E 34
I 34
D 47
	(void) ioctl(0, TIOCLGET, (char *)&deflflags);
	(void) ioctl(0, TIOCGETC, (char *)&deftc);
E 47
I 47
D 64
	(void)ioctl(0, TIOCLGET, (char *)&deflflags);
	(void)ioctl(0, TIOCGETC, (char *)&deftc);
E 64
I 64
	(void)ioctl(0, TIOCLGET, &deflflags);
	(void)ioctl(0, TIOCGETC, &deftc);
E 64
E 47
E 34
	notc.t_startc = deftc.t_startc;
	notc.t_stopc = deftc.t_stopc;
D 34
	ioctl(0, TIOCGLTC, (char *)&defltc);
E 14
E 7
E 5
D 11
	signal(SIGINT, exit);
	signal(SIGHUP, exit);
	signal(SIGQUIT, exit);
E 11
I 11
D 13
	sigset(SIGINT, exit);
	sigset(SIGHUP, exit);
	sigset(SIGQUIT, exit);
E 13
I 13
D 24
	signal(SIGINT, exit);
E 24
I 24
	signal(SIGINT, SIG_IGN);
E 24
	signal(SIGHUP, exit);
	signal(SIGQUIT, exit);
E 34
I 34
D 47
	(void) ioctl(0, TIOCGLTC, (char *)&defltc);
	(void) signal(SIGINT, SIG_IGN);
E 47
I 47
D 64
	(void)ioctl(0, TIOCGLTC, (char *)&defltc);
E 64
I 64
	(void)ioctl(0, TIOCGLTC, &defltc);
E 64
	(void)signal(SIGINT, SIG_IGN);
E 69
I 69
	for (i = 0; i < NCCS; i++)
		nott.c_cc[i] = _POSIX_VDISABLE;
	tcgetattr(0, &deftt);
	nott.c_cc[VSTART] = deftt.c_cc[VSTART];
	nott.c_cc[VSTOP] = deftt.c_cc[VSTOP];
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;
	(void)sigaction(SIGINT, &sa, (struct sigaction *) 0);
E 69
E 47
D 64
	setsignal(SIGHUP, exit);
	setsignal(SIGQUIT, exit);
E 64
I 64
	setsignal(SIGHUP);
	setsignal(SIGQUIT);
E 64
E 34
E 13
E 11
D 5
	pipe(pipes);
	parent = getpid();
	fk = fork();
	nhup = (int)signal(SIGINT, SIG_IGN);
	if (fk == 0) {
		rd();
		sleep(1);
E 5
I 5
	child = fork();
	if (child == -1) {
D 47
		perror("rlogin: fork");
E 47
I 47
D 69
		(void)fprintf(stderr, "rlogin: fork: %s.\n", strerror(errno));
E 69
I 69
		warn("fork");
E 69
E 47
D 29
		done();
E 29
I 29
		done(1);
E 29
	}
D 11
	signal(SIGINT, SIG_IGN);
E 11
I 11
D 13
	sigignore(SIGINT);
E 13
I 13
D 24
	signal(SIGINT, SIG_IGN);
E 13
	mode(1);
E 24
E 11
	if (child == 0) {
I 24
		mode(1);
D 34
		sigsetmask(oldmask);
E 24
D 7
		signal(SIGPIPE, SIG_IGN);
E 7
D 29
		reader();
E 29
I 29
		if (reader() == 0) {
E 34
I 34
D 47
		if (reader(oldmask) == 0) {
E 34
			prf("Connection closed.");
E 47
I 47
D 69
		if (reader(omask) == 0) {
E 69
I 69
		if (reader(smask) == 0) {
E 69
			msg("connection closed.");
E 47
			exit(0);
		}
E 29
E 5
D 12
		prf("\007Lost connection.");
E 12
I 12
		sleep(1);
D 47
		prf("\007Connection closed.");
E 12
		exit(3);
E 47
I 47
		msg("\007connection closed.");
		exit(1);
E 47
	}
I 24
D 34
	signal(SIGURG, writeroob);
	sigsetmask(oldmask);
E 24
D 11
	signal(SIGCHLD, done);
	mode(1);
E 11
I 11
D 13
	sigset(SIGCHLD, catchild);
E 13
I 13
	signal(SIGCHLD, catchild);
E 34
I 34

	/*
D 47
	 * We may still own the socket, and may have a pending SIGURG
	 * (or might receive one soon) that we really want to send to
	 * the reader.  Set a trap that simply copies such signals to
	 * the child.
E 47
I 47
	 * We may still own the socket, and may have a pending SIGURG (or might
D 63
	 * receive one soon) that we really want to send to the reader.  Set a
	 * trap that simply copies such signals to the child.
E 63
I 63
	 * receive one soon) that we really want to send to the reader.  When
	 * one of these comes in, the trap copytochild simply copies such
	 * signals to the child. We can now unblock SIGURG and SIGUSR1
	 * that were set above.
E 63
E 47
	 */
D 47
	(void) signal(SIGURG, copytochild);
	(void) signal(SIGUSR1, writeroob);
	(void) sigsetmask(oldmask);
	(void) signal(SIGCHLD, catchild);
E 47
I 47
D 63
	(void)signal(SIGURG, copytochild);
	(void)signal(SIGUSR1, writeroob);
E 63
D 69
	(void)sigsetmask(omask);
	(void)signal(SIGCHLD, catch_child);
E 69
I 69
	(void)sigprocmask(SIG_SETMASK, smask, (sigset_t *) 0);
	sa.sa_handler = catch_child;
	(void)sigaction(SIGCHLD, &sa, (struct sigaction *) 0);
E 69
E 47
E 34
I 17
D 28
	if (!nosigwin)
		signal(SIGWINCH, sigwinch);
E 28
E 17
E 13
E 11
D 5
	efk = fk;
	wr();
	if (fk != -1) kill(fk, SIGKILL);
E 5
I 5
	writer();
E 5
D 12
	prf("Disconnected.");
E 12
I 12
D 47
	prf("Closed connection.");
E 47
I 47
	msg("closed connection.");
E 47
E 12
D 29
	done();
E 29
I 29
	done(0);
E 29
}

I 34
D 47
/*
 * Trap a signal, unless it is being ignored.
 */
E 47
I 47
/* trap a signal, unless it is being ignored. */
E 47
D 64
setsignal(sig, act)
E 64
I 64
void
setsignal(sig)
E 64
D 47
	int sig, (*act)();
E 47
I 47
	int sig;
D 64
	void (*act)();
E 64
E 47
{
D 69
	int omask = sigblock(sigmask(sig));
E 69
I 69
	struct sigaction sa;
	sigset_t sigs;
E 69

D 64
	if (signal(sig, act) == SIG_IGN)
E 64
I 64
D 69
	if (signal(sig, exit) == SIG_IGN)
E 64
D 47
		(void) signal(sig, SIG_IGN);
	(void) sigsetmask(omask);
E 47
I 47
		(void)signal(sig, SIG_IGN);
	(void)sigsetmask(omask);
E 69
I 69
	sigemptyset(&sigs);
	sigaddset(&sigs, sig);
	sigprocmask(SIG_BLOCK, &sigs, &sigs);

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = exit;
	sa.sa_flags = SA_RESTART;
	(void)sigaction(sig, &sa, &sa);
	if (sa.sa_handler == SIG_IGN)
		(void)sigaction(sig, &sa, (struct sigaction *) 0);

	(void)sigprocmask(SIG_SETMASK, &sigs, (sigset_t *) 0);
E 69
E 47
}

I 64
__dead void
E 64
E 34
D 29
done()
E 29
I 29
done(status)
	int status;
E 29
{
I 34
D 58
	int w;
E 58
I 58
D 69
	int w, wstatus;
E 69
I 69
	pid_t w;
	int wstatus;
	struct sigaction sa;
E 69
E 58
E 34

	mode(0);
D 5
	wait((int *)NULL);
E 5
I 5
D 34
	if (child > 0 && kill(child, SIGKILL) >= 0)
		wait((int *)0);
E 34
I 34
	if (child > 0) {
D 47
		/* make sure catchild does not snap it up */
		(void) signal(SIGCHLD, SIG_DFL);
E 47
I 47
		/* make sure catch_child does not snap it up */
D 69
		(void)signal(SIGCHLD, SIG_DFL);
E 69
I 69
		sigemptyset(&sa.sa_mask);
		sa.sa_handler = SIG_DFL;
		sa.sa_flags = 0;
		(void)sigaction(SIGCHLD, &sa, (struct sigaction *) 0);
E 69
E 47
		if (kill(child, SIGKILL) >= 0)
D 47
			while ((w = wait((union wait *)0)) > 0 && w != child)
				/*void*/;
E 47
I 47
D 58
			while ((w = wait((union wait *)0)) > 0 && w != child);
E 58
I 58
D 69
			while ((w = wait(&wstatus)) > 0 && w != child);
E 69
I 69
			while ((w = wait(&wstatus)) > 0 && w != child)
				continue;
E 69
E 58
E 47
	}
E 34
E 5
D 29
	exit(0);
E 29
I 29
	exit(status);
E 29
}

I 24
D 47
/*
I 34
 * Copy SIGURGs to the child process.
 */
copytochild()
{
E 47
I 47
int dosigwinch;
I 58
D 64
void sigwinch();
E 64
E 58
E 47

D 47
	(void) kill(child, SIGURG);
}

E 47
/*
E 34
 * This is called when the reader process gets the out-of-band (urgent)
 * request to turn on the window-changing protocol.
 */
I 47
void
E 47
D 64
writeroob()
E 64
I 64
writeroob(signo)
	int signo;
E 64
{
I 69
	struct sigaction sa;

E 69
I 47
D 58
	void sigwinch();
E 47

E 58
I 27
D 28
	if (dosigwinch == 0)
E 28
I 28
	if (dosigwinch == 0) {
E 28
		sendwindow();
I 28
D 34
		signal(SIGWINCH, sigwinch);
E 34
I 34
D 47
		(void) signal(SIGWINCH, sigwinch);
E 47
I 47
D 69
		(void)signal(SIGWINCH, sigwinch);
E 69
I 69
		sigemptyset(&sa.sa_mask);
		sa.sa_handler = sigwinch;
		sa.sa_flags = SA_RESTART;
		(void)sigaction(SIGWINCH, &sa, (struct sigaction *) 0);
E 69
E 47
E 34
	}
E 28
E 27
	dosigwinch = 1;
D 27
	sendwindow();
E 27
}

E 24
I 11
D 47
catchild()
E 47
I 47
void
D 64
catch_child()
E 64
I 64
catch_child(signo)
	int signo;
E 64
E 47
{
D 69
	union wait status;
	int pid;
E 69
I 69
	int status;
	pid_t pid;
E 69

D 47
again:
D 34
	pid = wait3(&status, WNOHANG|WUNTRACED, 0);
E 34
I 34
	pid = wait3(&status, WNOHANG|WUNTRACED, (struct rusage *)0);
E 34
	if (pid == 0)
		return;
	/*
	 * if the child (reader) dies, just quit
	 */
	if (pid < 0 || pid == child && !WIFSTOPPED(status))
D 29
		done();
E 29
I 29
D 34
		done(status.w_termsig | status.w_retcode);
E 34
I 34
		done((int)(status.w_termsig | status.w_retcode));
E 34
E 29
	goto again;
E 47
I 47
	for (;;) {
D 58
		pid = wait3(&status, WNOHANG|WUNTRACED, (struct rusage *)0);
E 58
I 58
D 61
		pid = wait3((int *)&status,
		    WNOHANG|WUNTRACED, (struct rusage *)0);
E 61
I 61
D 69
		pid = wait3((int *)&status, WNOHANG|WUNTRACED, NULL);
E 69
I 69
		pid = waitpid(-1, &status, WNOHANG|WUNTRACED);
E 69
E 61
E 58
		if (pid == 0)
			return;
		/* if the child (reader) dies, just quit */
D 64
		if (pid < 0 || pid == child && !WIFSTOPPED(status))
E 64
I 64
		if (pid < 0 || (pid == child && !WIFSTOPPED(status)))
E 64
D 69
			done((int)(status.w_termsig | status.w_retcode));
E 69
I 69
			done(WEXITSTATUS(status) | WTERMSIG(status));
E 69
	}
	/* NOTREACHED */
E 47
}

E 11
/*
D 5
 *	wr: write to remote: 0 -> line.
 *	~.	terminate
 *	~<file	send file
 *	~!	local login-style shell
 *	~!cmd	execute cmd locally
 *	~$proc	execute proc locally, send output to line
 *	~%cmd	execute builtin cmd (put and take)
 *	~^Z	suspend cu process.
E 5
I 5
 * writer: write to remote: 0 -> line.
D 54
 * ~.	terminate
 * ~^Z	suspend rlogin process.
I 8
 * ~^Y  suspend rlogin process, but leave reader alone.
E 54
I 54
 * ~.				terminate
 * ~^Z				suspend rlogin process.
 * ~<delayed-suspend char>	suspend rlogin process, but leave reader alone.
E 54
E 8
E 5
 */
I 64
void
E 64
D 5

wr()
E 5
I 5
writer()
E 5
{
D 5
	int ds,fk,lcl,x;
	char *p,b[600];
	for (;;) {
		p=b;
		while (rdc(0) == 1) {
			if (p == b) lcl=(c == cmdchar);
			if (p == b+1 && b[0] == cmdchar) lcl=(c!=cmdchar);
			if (!lcl) {
				c = oc;
				if (wrc(rem) == 0) {
					prf("line gone"); return;
				}
				if (eight == 0)
					c &= 0177;
			}
			if (lcl) {
				if (c == 0177) c=tkill;
				if (c == '\r' || c == '\n') goto A;
				wrc(0);
			}
			*p++=c;
			if (c == terase) {
				p=p-2; 
				if (p<b) p=b;
			}
			if (c == tkill || c == 0177 || c == '\4' || c == '\r' || c == '\n') p=b;
		}
		return;
A: 
		echo("");
		*p=0;
		switch (b[1]) {
		case '.':
		case '\004':
			return;
		case '!':
		case '$':
			fk = fork();
			signal(SIGCHLD, SIG_DFL);
			if (fk == 0) {
				char *shell = getenv("SHELL");
				if (shell == 0) shell = "/bin/sh";
				close(1);
				dup(b[1] == '$'? rem:2);
				close(rem);
				mode(0);
				if (!nhup) signal(SIGINT, SIG_DFL);
				if (b[2] == 0) execl(shell,shell,0);
				/* if (b[2] == 0) execl(shell,"-",0); */
				else execl(shell,"sh","-c",b+2,0);
				prf("Can't execute shell");
				exit(~0);
			}
			if (fk!=(-1)) {
				while (wait(&x)!=fk);
			}
			signal(SIGCHLD, done);
			mode(1);
			if (b[1] == '!') echo("!");
			break;
		case '<':
			if (b[2] == 0) break;
			if ((ds=open(b+2,0))<0) {
				prf("Can't divert %s",b+1); 
				break;
			}
			intr=x=0;
			mode(2);
			if (!nhup) signal(SIGINT, sig2);
			while (!intr && rdc(ds) == 1) {
				if (wrc(rem) == 0) {
					x=1; 
					break;
				}
			}
			signal(SIGINT, SIG_IGN);
			close(ds);
			mode(1);
			if (x) return;
			break;
		case '>':
		case ':':
			{
			register char *q;
E 5
I 5
D 17
	char b[600], c;
	register char *p;
E 17
I 17
D 21
	char obuf[600], c;
	register char *op;
E 21
I 21
D 54
	char c;
E 54
E 21
E 17
I 11
D 47
	register n;
I 21
	register bol = 1;               /* beginning of line */
	register local = 0;
E 47
I 47
	register int bol, local, n;
I 54
	char c;
E 54
E 47
E 21
E 11
E 5

I 47
	bol = 1;			/* beginning of line */
	local = 0;
E 47
I 17
D 24
	/*
	 * Handle SIGWINCH's with in-band signaling of new
	 * window size.  It seems reasonable that we flush
	 * pending input and not force out of band signal
	 * as this most likely will occur from an input device
	 * other than the keyboard (e.g. a mouse).
	 *
	 * The hack of using 0377 to signal an in-band signal
	 * is pretty bad, but otherwise we'd be forced to
	 * either get complicated (use MSG_OOB) or go to a
	 * serious (telnet-style) protocol.
	 */
	if (setjmp(winsizechanged)) {
I 21
		char obuf[4 + sizeof (struct winsize)];
E 21
		struct winsize *wp = (struct winsize *)(obuf+4);

		obuf[0] = 0377;			/* XXX */
		obuf[1] = 0377;			/* XXX */
		obuf[2] = 's';			/* XXX */
		obuf[3] = 's';			/* XXX */
		wp->ws_row = htons(winsize.ws_row);
		wp->ws_col = htons(winsize.ws_col);
		wp->ws_xpixel = htons(winsize.ws_xpixel);
		wp->ws_ypixel = htons(winsize.ws_ypixel);
		(void) write(rem, obuf, 4+sizeof (*wp));
	}
E 17
D 5
			q = b+1;
			if(*q=='>') q++;
			write(pipes[1],q,strlen(q)+1);
			if (efk != -1) kill(efk,SIGEMT);
E 5
I 5
D 21
top:
D 17
	p = b;
E 17
I 17
	op = obuf;
E 17
D 11
	while (read(0, &c, 1) > 0) {
E 11
I 11
	for (;;) {
E 11
		int local;
E 21

E 24
I 21
	for (;;) {
E 21
I 11
D 47
		n = read(0, &c, 1);
E 47
I 47
		n = read(STDIN_FILENO, &c, 1);
E 47
D 17
		if (n == 0)
			break;
		if (n < 0)
			if (errno == EINTR)
E 17
I 17
		if (n <= 0) {
			if (n < 0 && errno == EINTR)
E 17
				continue;
D 17
			else
				break;

E 11
		if (eight == 0)
E 17
I 17
			break;
		}
D 24
		if (!eight)
E 17
			c &= 0177;
E 24
		/*
D 47
		 * If we're at the beginning of the line
		 * and recognize a command character, then
		 * we echo locally.  Otherwise, characters
		 * are echo'd remotely.  If the command
		 * character is doubled, this acts as a 
		 * force and local echo is suppressed.
E 47
I 47
		 * If we're at the beginning of the line and recognize a
		 * command character, then we echo locally.  Otherwise,
		 * characters are echo'd remotely.  If the command character
		 * is doubled, this acts as a force and local echo is
		 * suppressed.
E 47
		 */
D 17
		if (p == b)
E 17
I 17
D 21
		if (op == obuf)
E 17
			local = (c == cmdchar);
D 17
		if (p == b + 1 && *b == cmdchar)
E 17
I 17
		if (op == obuf + 1 && *obuf == cmdchar)
E 17
			local = (c != cmdchar);
		if (!local) {
			if (write(rem, &c, 1) == 0) {
				prf("line gone");
				return;
E 21
I 21
		if (bol) {
			bol = 0;
D 54
			if (c == cmdchar) {
				bol = 0;
E 54
I 54
			if (!noescape && c == escapechar) {
E 54
				local = 1;
				continue;
E 21
E 5
			}
D 5
			break;
#ifdef SIGTSTP
#define CTRLZ	26
		case CTRLZ:
			mode(0);
			signal(SIGCHLD, SIG_IGN);
			kill(0, SIGTSTP);
			signal(SIGCHLD, done);
			mode(1);
			break;
#endif
		case '%':
			dopercen(&b[2]);
			break;
		default:
			prf("Use `%c%c' to start line with `%c'", cmdchar, cmdchar, cmdchar);
		}
		continue;
	}
}
E 5
I 5
D 17
			if (eight == 0)
E 17
I 17
D 21
			if (!eight)
E 17
				c &= 0177;
		} else {
D 12
			if (c == 0177)
D 7
				c = tkill;
E 7
I 7
				c = deftc.tc_kill;
E 12
E 7
			if (c == '\r' || c == '\n') {
D 7
				switch (b[1]) {
E 7
I 7
D 17
				char cmdc = b[1];
E 17
I 17
				char cmdc = obuf[1];
E 17
E 7
E 5

D 5
dopercen(line)
register char *line;
{
	char *args[10];
	register narg, f;
	int rcount;
	for (narg = 0; narg < 10;) {
		while(*line == ' ' || *line == '\t')
			line++;
		if (*line == '\0')
			break;
		args[narg++] = line;
		while(*line != '\0' && *line != ' ' && *line != '\t')
			line++;
		if (*line == '\0')
			break;
		*line++ = '\0';
	}
	if (equal(args[0], "take")) {
		if (narg < 2) {
			prf("usage: %c%%take from [to]", cmdchar);
			return;
		}
		if (narg < 3)
			args[2] = args[1];
		write(pipes[1], ">/dev/null",sizeof(">/dev/null"));
		if (efk != -1) kill(efk,SIGEMT);
		sleep(5);
		wrln("echo '%c>:", cmdchar);
		wrln(args[2]);
		wrln("'; tee /dev/null <");
		wrln(args[1]);
		wrln(";echo '%c>'\n", cmdchar);
		return;
	} else if (equal(args[0], "put")) {
		prf("%c%%put doesn't work yet (use rsh)", cmdchar);
		return;
/*
		if (narg < 2) {
			prf("usage: %c%%put from [to]", cmdchar);
			return;
		}
		if (narg < 3)
			args[2] = args[1];
		if ((f = open(args[1], 0)) < 0) {
			prf("cannot open: %s", args[1]);
			return;
		}
		wrln("stty -echo;cat >");
		wrln(args[2]);
		wrln(";stty echo\n");
		sleep(5);
		intr = 0;
		if (!nhup)
			signal(SIGINT, sig2);
		mode(2);
		rcount = 0;
		while(!intr && rdc(f) == 1) {
			rcount++;
			if (c == tkill || c == terase)
				wrln("\\");
			if (wrc(rem) != 1) {
				sleep(2);
				if (wrc(rem) != 1) {
					prf("character missed");
					intr = 1;
					break;
E 5
I 5
D 7
				case '.':
				case CTRL(d):
E 7
I 7
D 14
				if (cmdc == '.' || cmdc == deftc.tc_eofc) {
E 14
I 14
				if (cmdc == '.' || cmdc == deftc.t_eofc) {
E 14
E 7
					write(0, CRLF, sizeof(CRLF));
					return;
D 7

				case CTRL(z):
E 7
I 7
				}
D 14
				if (cmdc == deftc.tc_suspc ||
				    cmdc == deftc.tc_dsuspc) {
E 14
I 14
				if (cmdc == defltc.t_suspc ||
				    cmdc == defltc.t_dsuspc) {
E 14
E 7
D 17
					write(0, CRLF, sizeof(CRLF));
					mode(0);
D 11
					signal(SIGCHLD, SIG_IGN);
E 11
I 11
D 13
					sigignore(SIGCHLD);
E 13
I 13
					signal(SIGCHLD, SIG_IGN);
E 13
E 11
D 7
					kill(0, SIGTSTP);
E 7
I 7
D 14
					kill(cmdc == deftc.tc_suspc ?
E 14
I 14
					kill(cmdc == defltc.t_suspc ?
E 14
					  0 : getpid(), SIGTSTP);
E 7
D 11
					signal(SIGCHLD, done);
E 11
I 11
D 13
					sigrelse(SIGCHLD);
E 13
I 13
					signal(SIGCHLD, catchild);
E 13
E 11
					mode(1);
E 17
I 17
					stop(cmdc);
E 17
					goto top;
E 5
				}
I 5
D 17
				*p++ = c;
				write(rem, b, p - b);
E 17
I 17
				*op++ = c;
				write(rem, obuf, op - obuf);
E 17
				goto top;
E 21
I 21
		} else if (local) {
			local = 0;
D 69
			if (c == '.' || c == deftc.t_eofc) {
E 69
I 69
			if (c == '.' || c == deftt.c_cc[VEOF]) {
E 69
				echo(c);
				break;
E 21
E 5
			}
I 5
D 21
			write(1, &c, 1);
E 21
I 21
D 69
			if (c == defltc.t_suspc || c == defltc.t_dsuspc) {
E 69
I 69
			if (c == deftt.c_cc[VSUSP] || c == deftt.c_cc[VDSUSP]) {
E 69
				bol = 1;
				echo(c);
				stop(c);
				continue;
			}
D 37
			if (c != cmdchar)
D 34
				write(rem, &cmdchar, 1);
E 34
I 34
				(void) write(rem, &cmdchar, 1);
E 37
I 37
D 54
			if (c != cmdchar) {
E 54
I 54
			if (c != escapechar)
E 54
D 47
#ifdef	KERBEROS
				if(encrypt) {
					(void) des_write(
						rem,
						&cmdchar,
						1
					);
E 47
I 47
D 55
#ifdef KERBEROS
E 55
I 55
D 56
#if defined(KERBEROS) && defined(CRYPT)
E 56
I 56
D 57
D 59
#ifdef CRYPT
#ifdef KERBEROS
E 56
E 55
D 54
				if (encrypt) {
					(void)des_write(rem, &cmdchar, 1);
E 47
				} else
E 54
I 54
D 58
				if (encrypt)
E 58
I 58
				if (doencrypt)
E 58
D 64
					(void)des_write(rem, &escapechar, 1);
E 64
I 64
					(void)des_write(rem,
					    (char *)&escapechar, 1);
E 64
				else
E 54
#endif
I 56
#endif
E 59
E 57
E 56
D 47
					(void) write(
						rem,
						&cmdchar,
						1
					);
E 47
I 47
D 54
					(void)write(rem, &cmdchar, 1);
E 47
			}
E 54
I 54
					(void)write(rem, &escapechar, 1);
E 54
E 37
E 34
E 21
E 5
		}
D 5
		signal(SIGINT, SIG_IGN);
		close(f);
		if (intr) {
			wrln("\n");
			prf("stopped after %d bytes", rcount);
E 5
I 5
D 17
		*p++ = c;
E 17
I 17
D 21
		*op++ = c;
E 17
D 7
		if (c == terase) {
E 7
I 7
D 14
		if (c == deftc.tc_erase) {
E 14
I 14
		if (c == deferase) {
E 14
E 7
D 17
			p -= 2; 
			if (p < b)
E 17
I 17
			op -= 2; 
			if (op < obuf)
E 17
				goto top;
E 21
I 21
D 37
		if (write(rem, &c, 1) == 0) {
			prf("line gone");
			break;
E 21
E 5
		}
E 37
I 37

D 47
#ifdef	KERBEROS
		if(encrypt) {
E 47
I 47
D 55
#ifdef KERBEROS
E 55
I 55
D 56
#if defined(KERBEROS) && defined(CRYPT)
E 56
I 56
D 57
D 59
#ifdef CRYPT
#ifdef KERBEROS
E 56
E 55
D 58
		if (encrypt) {
E 58
I 58
		if (doencrypt) {
E 58
E 47
			if (des_write(rem, &c, 1) == 0) {
D 47
				prf("line gone");
E 47
I 47
				msg("line gone");
E 47
				break;
			}
		} else
#endif
I 56
#endif
E 59
E 57
E 56
			if (write(rem, &c, 1) == 0) {
D 47
				prf("line gone");
E 47
I 47
				msg("line gone");
E 47
				break;
			}
E 37
D 5
		wrln("\004");
		sleep(5);
		mode(1);
		return;
*/
E 5
I 5
D 7
		if (c == tkill || c == 0177 || c == CTRL(d) ||
E 7
I 7
D 12
		if (c == deftc.tc_kill || c == 0177 || c == deftc.tc_eofc ||
E 12
I 12
D 14
		if (c == deftc.tc_kill || c == deftc.tc_eofc ||
E 14
I 14
D 21
		if (c == defkill || c == deftc.t_eofc ||
E 14
E 12
E 7
		    c == '\r' || c == '\n')
			goto top;
I 11
D 17
		if (p >= &b[sizeof b])
			p--;
E 17
I 17
		if (op >= &obuf[sizeof (obuf)])
			op--;
E 21
I 21
D 69
		bol = c == defkill || c == deftc.t_eofc ||
I 29
		    c == deftc.t_intrc || c == defltc.t_suspc ||
E 69
I 69
		bol = c == deftt.c_cc[VKILL] || c == deftt.c_cc[VEOF] ||
		    c == deftt.c_cc[VINTR] || c == deftt.c_cc[VSUSP] ||
E 69
E 29
		    c == '\r' || c == '\n';
E 21
	}
}

I 64
void
#if __STDC__
echo(register char c)
#else
E 64
I 21
echo(c)
D 64
register char c;
E 64
I 64
	register char c;
#endif
E 64
{
I 47
	register char *p;
E 47
	char buf[8];
D 47
	register char *p = buf;
E 47

I 47
	p = buf;
E 47
	c &= 0177;
D 54
	*p++ = cmdchar;
E 54
I 54
	*p++ = escapechar;
E 54
	if (c < ' ') {
		*p++ = '^';
		*p++ = c + '@';
	} else if (c == 0177) {
		*p++ = '^';
		*p++ = '?';
	} else
		*p++ = c;
	*p++ = '\r';
	*p++ = '\n';
D 34
	write(1, buf, p - buf);
E 34
I 34
D 47
	(void) write(1, buf, p - buf);
E 47
I 47
D 54
	(void)write(1, buf, p - buf);
E 54
I 54
	(void)write(STDOUT_FILENO, buf, p - buf);
E 54
E 47
E 34
}

I 64
void
#if __STDC__
stop(char cmdc)
#else
E 64
E 21
stop(cmdc)
	char cmdc;
I 64
#endif
E 64
{
I 69
	struct sigaction sa;

E 69
D 24
	struct winsize ws;

E 24
D 21
	write(0, CRLF, sizeof(CRLF));
E 21
	mode(0);
D 34
	signal(SIGCHLD, SIG_IGN);
	kill(cmdc == defltc.t_suspc ? 0 : getpid(), SIGTSTP);
	signal(SIGCHLD, catchild);
E 34
I 34
D 47
	(void) signal(SIGCHLD, SIG_IGN);
	(void) kill(cmdc == defltc.t_suspc ? 0 : getpid(), SIGTSTP);
	(void) signal(SIGCHLD, catchild);
E 47
I 47
D 69
	(void)signal(SIGCHLD, SIG_IGN);
	(void)kill(cmdc == defltc.t_suspc ? 0 : getpid(), SIGTSTP);
	(void)signal(SIGCHLD, catch_child);
E 69
I 69
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = SA_RESTART;
	(void)sigaction(SIGCHLD, &sa, (struct sigaction *) 0);
	(void)kill(cmdc == deftt.c_cc[VSUSP] ? 0 : getpid(), SIGTSTP);
	sa.sa_handler = catch_child;
	(void)sigaction(SIGCHLD, &sa, (struct sigaction *) 0);
E 69
E 47
E 34
	mode(1);
D 64
	sigwinch();			/* check for size changes */
E 64
I 64
	sigwinch(0);			/* check for size changes */
E 64
}

I 47
void
E 47
I 32
D 34
#ifdef sun
E 34
E 32
D 64
sigwinch()
E 64
I 64
sigwinch(signo)
	int signo;
E 64
{
I 32
D 34
	struct ttysize ws;

	if (dosigwinch && ioctl(0, TIOCGSIZE, &ws) == 0 &&
	    bcmp(&ws, &winsize, sizeof (ws))) {
		winsize = ws;
		sendwindow();
	}
}

#else sun
sigwinch()
{
E 34
E 32
	struct winsize ws;

D 24
	if (!nosigwin && ioctl(0, TIOCGWINSZ, &ws) == 0 &&
E 24
I 24
D 28
	if (dosigwinch && !nosigwin && ioctl(0, TIOCGWINSZ, &ws) == 0 &&
E 28
I 28
D 34
	if (dosigwinch && ioctl(0, TIOCGWINSZ, &ws) == 0 &&
E 34
I 34
	if (dosigwinch && get_window_size(0, &ws) == 0 &&
E 34
E 28
E 24
D 47
	    bcmp(&ws, &winsize, sizeof (ws))) {
E 47
I 47
D 69
	    bcmp(&ws, &winsize, sizeof(ws))) {
E 69
I 69
	    memcmp(&ws, &winsize, sizeof(ws))) {
E 69
E 47
		winsize = ws;
D 24
		longjmp(winsizechanged, 1);
E 24
I 24
		sendwindow();
E 24
E 17
E 11
E 5
	}
D 5
	prf("%c%%%s unknown\n", cmdchar, args[0]);
E 5
}
I 32
D 34
#endif
E 34
E 32

I 24
/*
 * Send the window size to the server via the magic escape
 */
I 64
void
E 64
sendwindow()
{
I 47
	struct winsize *wp;
E 47
	char obuf[4 + sizeof (struct winsize)];
D 47
	struct winsize *wp = (struct winsize *)(obuf+4);
E 47

I 47
	wp = (struct winsize *)(obuf+4);
E 47
	obuf[0] = 0377;
	obuf[1] = 0377;
	obuf[2] = 's';
	obuf[3] = 's';
I 32
D 34
#ifdef sun
	wp->ws_row = htons(winsize.ts_lines);
	wp->ws_col = htons(winsize.ts_cols);
	wp->ws_xpixel = 0;
	wp->ws_ypixel = 0;
#else sun
E 34
E 32
	wp->ws_row = htons(winsize.ws_row);
	wp->ws_col = htons(winsize.ws_col);
	wp->ws_xpixel = htons(winsize.ws_xpixel);
	wp->ws_ypixel = htons(winsize.ws_ypixel);
I 32
D 34
#endif sun
E 34
E 32
D 37
	(void) write(rem, obuf, sizeof(obuf));
E 37
I 37

D 47
#ifdef	KERBEROS
E 47
I 47
D 55
#ifdef KERBEROS
E 55
I 55
D 56
#if defined(KERBEROS) && defined(CRYPT)
E 56
I 56
D 57
D 59
#ifdef CRYPT
#ifdef KERBEROS
E 56
E 55
E 47
D 58
	if(encrypt)
E 58
I 58
	if(doencrypt)
E 58
D 47
		(void) des_write(rem, obuf, sizeof(obuf));
E 47
I 47
		(void)des_write(rem, obuf, sizeof(obuf));
E 47
	else
#endif
I 56
#endif
E 59
E 57
E 56
D 47
		(void) write(rem, obuf, sizeof(obuf));
E 47
I 47
		(void)write(rem, obuf, sizeof(obuf));
E 47
E 37
}

I 29
/*
 * reader: read from remote: line -> 1
 */
#define	READING	1
#define	WRITING	2

D 47
char	rcvbuf[8 * 1024];
int	rcvcnt;
int	rcvstate;
I 32
int	ppid;
E 32
jmp_buf	rcvtop;
E 47
I 47
jmp_buf rcvtop;
D 69
int ppid, rcvcnt, rcvstate;
E 69
I 69
pid_t ppid;
int rcvcnt, rcvstate;
E 69
char rcvbuf[8 * 1024];
E 47

I 47
void
E 47
E 29
E 24
D 5
equal(s1, s2)
register char *s1, *s2;
{
	while (*s1++ == *s2)
		if (*s2++ == '\0')
			return(1);
	return(0);
}

wrln(s, p1, p2, p3)
register char *s;
int p1, p2, p3;
{
	char wbuf[256];

	sprintf(wbuf, s, p1, p2, p3);
	s = wbuf;
	while (*s)
		write(rem, s++, 1);
}
int ds,slnt;
int justrung;

/*
 *	rd: read from remote: line -> 1
 *	catch:
 *	~>[>][:][file]
 *	stuff from file...
 *	~>	(ends diversion)
 */

int ds,slnt,taking;
int justrung;
readmsg(){
	static char dobuff[128], morejunk[256];
	int n;
	justrung = 1;
	signal(SIGEMT,readmsg);
	n = read(pipes[0],morejunk,256);
	dodiver(morejunk);
}

dodiver(msg)
char *msg;
{
	register char *cp = msg; 

	if (*cp=='>') cp++;
	if (*cp==':') {
		cp++;
		if(*cp==0) {
			slnt ^= 1;
			return;
		} else  {
			slnt = 1;
		}
	}
	if (ds >= 0) close(ds);
	if (*cp==0) {
		slnt = 0;
		ds = -1;
		return;
	}
	if (*msg!='>' || (ds=open(cp,1))<0) ds=creat(cp,0644);
	lseek(ds, (long)0, 2);
	if(ds < 0) prf("Creat failed:"), prf(cp);
	if (ds<0) prf("Can't divert %s",cp+1);
}


/*
 *	rd: read from remote: line -> 1
 *	catch: diversion caught by interrupt routine
 */

#define ORDIN 0
#define SAWCR 1
#define EOL   2
#define SAWTL 3
#define DIVER 4

E 5
D 64
oob()
E 64
I 64
oob(signo)
	int signo;
E 64
{
D 5
	int mark, cc, out = 1+1;
	char waste[512];
E 5
I 5
D 9
	int out = 1+1;
E 9
I 9
D 29
	int out = 1+1, atmark;
E 29
I 29
D 47
	int out = FWRITE, atmark, n;
	int rcvd = 0;
E 29
E 9
	char waste[BUFSIZ], mark;
E 47
I 24
D 69
	struct sgttyb sb;
E 69
I 69
	struct termios tt;
E 69
I 47
	int atmark, n, out, rcvd;
	char waste[BUFSIZ], mark;
E 47
I 27
D 29
	static int didnotify = 0;
E 29
E 27
E 24
E 5

I 47
D 51
	out = FWRITE;
E 51
I 51
	out = O_RDWR;
E 51
	rcvd = 0;
E 47
D 11
	signal(SIGURG, oob);
E 11
D 5
	ioctl(1, TIOCFLUSH, &out);
E 5
I 5
D 29
	ioctl(1, TIOCFLUSH, (char *)&out);
E 5
	for (;;) {
I 24
		int rv;
E 24
D 9
		if (ioctl(rem, SIOCATMARK, &mark) < 0) {
E 9
I 9
		if (ioctl(rem, SIOCATMARK, &atmark) < 0) {
E 9
			perror("ioctl");
			break;
		}
D 9
		if (mark)
E 9
I 9
		if (atmark)
E 9
			break;
D 5
		cc = read(rem, waste, 512);
E 5
I 5
D 20
		(void) read(rem, waste, sizeof (waste));
E 20
I 20
D 24
		if (read(rem, waste, sizeof (waste)) <= 0)
E 24
I 24
		rv = read(rem, waste, sizeof (waste));
		if (rv <= 0)
E 24
			break;
E 29
I 29
D 67
	while (recv(rem, &mark, 1, MSG_OOB) < 0)
E 67
I 67
	while (recv(rem, &mark, 1, MSG_OOB) < 0) {
E 67
		switch (errno) {
D 47
		
E 47
		case EWOULDBLOCK:
			/*
D 47
			 * Urgent data not here yet.
			 * It may not be possible to send it yet
			 * if we are blocked for output
			 * and our input buffer is full.
E 47
I 47
			 * Urgent data not here yet.  It may not be possible
			 * to send it yet if we are blocked for output and
			 * our input buffer is full.
E 47
			 */
			if (rcvcnt < sizeof(rcvbuf)) {
				n = read(rem, rcvbuf + rcvcnt,
D 47
					sizeof(rcvbuf) - rcvcnt);
E 47
I 47
				    sizeof(rcvbuf) - rcvcnt);
E 47
				if (n <= 0)
					return;
				rcvd += n;
			} else {
				n = read(rem, waste, sizeof(waste));
				if (n <= 0)
					return;
			}
			continue;
D 47
				
E 47
		default:
			return;
I 67
		}
E 67
E 29
E 20
E 5
	}
D 3
	ioctl(rem, SIOCRCVOOB, &mark);
E 3
I 3
D 13
	recv(rem, &mark, 1, SOF_OOB);
E 13
I 13
D 29
	recv(rem, &mark, 1, MSG_OOB);
I 24
D 27
	if (mark & TIOCPKT_WINDOW) {
E 27
I 27
	if (didnotify == 0 && (mark & TIOCPKT_WINDOW)) {
E 29
I 29
	if (mark & TIOCPKT_WINDOW) {
E 29
E 27
D 47
		/*
		 * Let server know about window size changes
		 */
D 32
		kill(getppid(), SIGURG);
E 32
I 32
D 34
		kill(ppid, SIGURG);
E 34
I 34
		(void) kill(ppid, SIGUSR1);
E 47
I 47
		/* Let server know about window size changes */
		(void)kill(ppid, SIGUSR1);
E 47
E 34
E 32
I 27
D 29
		didnotify = 1;
E 29
E 27
	}
D 29
	if (eight)
		return;
E 24
E 13
E 3
	if (mark & TIOCPKT_NOSTOP) {
E 29
I 29
	if (!eight && (mark & TIOCPKT_NOSTOP)) {
E 29
I 24
D 34
		ioctl(0, TIOCGETP, (char *)&sb);
E 34
I 34
D 47
		(void) ioctl(0, TIOCGETP, (char *)&sb);
E 47
I 47
D 69
		(void)ioctl(0, TIOCGETP, (char *)&sb);
E 47
E 34
		sb.sg_flags &= ~CBREAK;
		sb.sg_flags |= RAW;
D 34
		ioctl(0, TIOCSETN, (char *)&sb);
E 34
I 34
D 47
		(void) ioctl(0, TIOCSETN, (char *)&sb);
E 47
I 47
		(void)ioctl(0, TIOCSETN, (char *)&sb);
E 47
E 34
E 24
D 5
		notchars.t_stopc = 0377;
		notchars.t_startc = 0377;
		ioctl(0, TIOCSETC, &notchars);
E 5
I 5
D 7
		notchars.t_stopc = -1;
		notchars.t_startc = -1;
		ioctl(0, TIOCSETC, (char *)&notchars);
E 7
I 7
D 14
		notc.tc_stopc = -1;
		notc.tc_startc = -1;
		ioctl(0, TIOCCSET, (char *)&notc);
E 14
I 14
		notc.t_stopc = -1;
		notc.t_startc = -1;
D 34
		ioctl(0, TIOCSETC, (char *)&notc);
E 34
I 34
D 47
		(void) ioctl(0, TIOCSETC, (char *)&notc);
E 47
I 47
		(void)ioctl(0, TIOCSETC, (char *)&notc);
E 69
I 69
		tcgetattr(0, &tt);
D 70
		tt.c_iflag &= ~(IXON|IXOFF);
E 70
I 70
		tt.c_iflag &= ~(IXON | IXOFF);
E 70
		tt.c_cc[VSTOP] = _POSIX_VDISABLE;
		tt.c_cc[VSTART] = _POSIX_VDISABLE;
		tcsetattr(0, TCSANOW, &tt);
E 69
E 47
E 34
E 14
E 7
E 5
	}
D 29
	if (mark & TIOCPKT_DOSTOP) {
E 29
I 29
	if (!eight && (mark & TIOCPKT_DOSTOP)) {
E 29
I 24
D 34
		ioctl(0, TIOCGETP, (char *)&sb);
E 34
I 34
D 47
		(void) ioctl(0, TIOCGETP, (char *)&sb);
E 47
I 47
D 69
		(void)ioctl(0, TIOCGETP, (char *)&sb);
E 47
E 34
		sb.sg_flags &= ~RAW;
		sb.sg_flags |= CBREAK;
D 34
		ioctl(0, TIOCSETN, (char *)&sb);
E 34
I 34
D 47
		(void) ioctl(0, TIOCSETN, (char *)&sb);
E 47
I 47
		(void)ioctl(0, TIOCSETN, (char *)&sb);
E 47
E 34
E 24
D 5
		notchars.t_stopc = 's'&037;
		notchars.t_startc = 'q'&037;
		ioctl(0, TIOCSETC, &notchars);
E 5
I 5
D 7
		notchars.t_stopc = CTRL(s);
		notchars.t_startc = CTRL(q);
		ioctl(0, TIOCSETC, (char *)&notchars);
E 7
I 7
D 14
		notc.tc_stopc = deftc.tc_stopc;
		notc.tc_startc = deftc.tc_startc;
		ioctl(0, TIOCCSET, (char *)&notc);
E 14
I 14
		notc.t_stopc = deftc.t_stopc;
		notc.t_startc = deftc.t_startc;
D 34
		ioctl(0, TIOCSETC, (char *)&notc);
E 34
I 34
D 47
		(void) ioctl(0, TIOCSETC, (char *)&notc);
E 47
I 47
		(void)ioctl(0, TIOCSETC, (char *)&notc);
E 69
I 69
		tcgetattr(0, &tt);
		tt.c_iflag |= (IXON|IXOFF);
		tt.c_cc[VSTOP] = deftt.c_cc[VSTOP];
		tt.c_cc[VSTART] = deftt.c_cc[VSTART];
		tcsetattr(0, TCSANOW, &tt);
E 69
E 47
E 34
E 14
E 7
E 5
	}
I 29
	if (mark & TIOCPKT_FLUSHWRITE) {
D 34
		ioctl(1, TIOCFLUSH, (char *)&out);
E 34
I 34
D 47
		(void) ioctl(1, TIOCFLUSH, (char *)&out);
E 47
I 47
		(void)ioctl(1, TIOCFLUSH, (char *)&out);
E 47
E 34
		for (;;) {
			if (ioctl(rem, SIOCATMARK, &atmark) < 0) {
D 47
				perror("ioctl");
E 47
I 47
D 69
				(void)fprintf(stderr, "rlogin: ioctl: %s.\n",
				    strerror(errno));
E 69
I 69
				warn("ioctl SIOCATMARK (ignored)");
E 69
E 47
				break;
			}
			if (atmark)
				break;
			n = read(rem, waste, sizeof (waste));
			if (n <= 0)
				break;
		}
		/*
D 47
		 * Don't want any pending data to be output,
		 * so clear the recv buffer.
		 * If we were hanging on a write when interrupted,
		 * don't want it to restart.  If we were reading,
		 * restart anyway.
E 47
I 47
		 * Don't want any pending data to be output, so clear the recv
		 * buffer.  If we were hanging on a write when interrupted,
		 * don't want it to restart.  If we were reading, restart
		 * anyway.
E 47
		 */
		rcvcnt = 0;
		longjmp(rcvtop, 1);
	}
I 34

E 34
D 47
	/*
I 34
	 * oob does not do FLUSHREAD (alas!)
	 */
E 47
I 47
	/* oob does not do FLUSHREAD (alas!) */
E 47

	/*
E 34
D 47
	 * If we filled the receive buffer while a read was pending,
	 * longjmp to the top to restart appropriately.  Don't abort
	 * a pending write, however, or we won't know how much was written.
E 47
I 47
	 * If we filled the receive buffer while a read was pending, longjmp
	 * to the top to restart appropriately.  Don't abort a pending write,
	 * however, or we won't know how much was written.
E 47
	 */
	if (rcvd && rcvstate == READING)
		longjmp(rcvtop, 1);
E 29
}

D 5
rd()
E 5
I 5
D 47
/*
 * reader: read from remote: line -> 1
 */
D 34
reader()
E 34
I 34
reader(oldmask)
	int oldmask;
E 47
I 47
/* reader: read from remote: line -> 1 */
I 64
int
E 64
D 69
reader(omask)
	int omask;
E 69
I 69
reader(smask)
	sigset_t *smask;
E 69
E 47
E 34
E 5
{
I 67
D 69
	int pid, n, remaining;
E 69
I 69
	pid_t pid;
	int n, remaining;
E 69
	char *bufp;
I 69
	struct sigaction sa;
E 69
E 67
I 47
D 64
	void oob();
E 64

E 47
I 32
D 67
#if !defined(BSD) || BSD < 43
	int pid = -getpid();
E 67
I 67
#if BSD >= 43 || defined(SUNOS4)
	pid = getpid();		/* modern systems use positives for pid */
E 67
#else
E 32
D 5
	extern int ds,slnt;
	char rb[600], lb[600], *rlim, *llim, c;
	register char *p,*q;
	int cnt, state = 0, mustecho, oldslnt, readmsg();
E 5
I 5
D 29
	char rb[BUFSIZ];
	register int cnt;
E 29
I 29
D 67
	int pid = getpid();
E 67
I 67
	pid = -getpid();	/* old broken systems use negatives */
E 67
I 32
#endif
E 32
D 67
	int n, remaining;
	char *bufp = rcvbuf;
E 29
E 5

E 67
D 5
	signal(SIGEMT,readmsg);  /* set up child for catching diversion msgs
				    from parent */
	signal(SIGURG,oob);
E 5
I 5
D 11
	signal(SIGURG, oob);
E 11
I 11
D 13
	sigset(SIGURG, oob);
E 13
I 13
D 24
	signal(SIGURG, oob);
E 24
I 21
D 34
	signal(SIGTTOU, SIG_IGN);
E 21
E 13
E 11
D 6
#ifdef notdef
E 6
E 5
D 22
	{ int pid = -getpid();
D 5
	  ioctl(rem, SIOCSPGRP, &pid); }
	ds=(-1);
	p = lb; llim = lb+600;
agin:
E 5
I 5
	  ioctl(rem, SIOCSPGRP, (char *)&pid); }
E 22
I 22
D 29
	{ int pid = getpid();
	  fcntl(rem, F_SETOWN, pid); }
E 29
I 29
	fcntl(rem, F_SETOWN, pid);
E 34
I 34
D 47
	(void) signal(SIGTTOU, SIG_IGN);
	(void) signal(SIGURG, oob);
E 47
I 47
D 69
	(void)signal(SIGTTOU, SIG_IGN);
	(void)signal(SIGURG, oob);
E 69
I 69
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;
	(void)sigaction(SIGTTOU, &sa, (struct sigaction *) 0);
	sa.sa_handler = oob;
	(void)sigaction(SIGURG, &sa, (struct sigaction *) 0);
E 69
E 47
E 34
I 32
	ppid = getppid();
I 34
D 47
	(void) fcntl(rem, F_SETOWN, pid);
E 34
E 32
	(void) setjmp(rcvtop);
I 34
	(void) sigsetmask(oldmask);
E 47
I 47
	(void)fcntl(rem, F_SETOWN, pid);
	(void)setjmp(rcvtop);
D 69
	(void)sigsetmask(omask);
E 69
I 69
	(void)sigprocmask(SIG_SETMASK, smask, (sigset_t *) 0);
E 69
I 67
	bufp = rcvbuf;
E 67
E 47
E 34
E 29
E 22
D 6
#endif
E 6
E 5
	for (;;) {
D 5
		extern errno;
		errno = 0;
		cnt = read(rem,rb,600);
E 5
I 5
D 29
		cnt = read(rem, rb, sizeof (rb));
E 5
D 10
		if (cnt <= 0) {
E 10
I 10
		if (cnt == 0)
			break;
		if (cnt < 0) {
E 29
I 29
		while ((remaining = rcvcnt - (bufp - rcvbuf)) > 0) {
			rcvstate = WRITING;
D 54
			n = write(1, bufp, remaining);
E 54
I 54
			n = write(STDOUT_FILENO, bufp, remaining);
E 54
			if (n < 0) {
				if (errno != EINTR)
D 30
					return;
E 30
I 30
D 47
					return (-1);
E 47
I 47
D 64
					return(-1);
E 64
I 64
					return (-1);
E 64
E 47
E 30
				continue;
			}
			bufp += n;
		}
		bufp = rcvbuf;
		rcvcnt = 0;
		rcvstate = READING;
D 37
		rcvcnt = read(rem, rcvbuf, sizeof (rcvbuf));
E 37
I 37

D 47
#ifdef	KERBEROS
		if(encrypt)
E 47
I 47
D 55
#ifdef KERBEROS
E 55
I 55
D 56
#if defined(KERBEROS) && defined(CRYPT)
E 56
I 56
D 57
D 59
#ifdef CRYPT
#ifdef KERBEROS
E 56
E 55
D 58
		if (encrypt)
E 58
I 58
		if (doencrypt)
E 58
E 47
			rcvcnt = des_read(rem, rcvbuf, sizeof(rcvbuf));
		else
I 56
#endif
E 56
#endif
E 59
E 57
			rcvcnt = read(rem, rcvbuf, sizeof (rcvbuf));
E 37
		if (rcvcnt == 0)
			return (0);
		if (rcvcnt < 0) {
E 29
E 10
D 5
			if (errno == EINTR) {
				errno = 0;
E 5
I 5
			if (errno == EINTR)
E 5
				continue;
I 32
D 47
			perror("read");
E 32
D 5
			}
E 5
D 29
			break;
E 29
I 29
			return (-1);
E 47
I 47
D 69
			(void)fprintf(stderr, "rlogin: read: %s.\n",
			    strerror(errno));
E 69
I 69
			warn("read");
E 69
D 64
			return(-1);
E 64
I 64
			return (-1);
E 64
E 47
E 29
		}
D 5
		if(!slnt) write(1,rb,cnt);
		if(ds < 0) continue;
		oldslnt = slnt;
		for( q=rb, rlim = rb + cnt - 1; q <= rlim; ) {
			if (eight == 0)
			c &= 0177;
			if(p < llim) *p++ = c;
			switch(state) {
			case ORDIN:
				if(c=='\r') state = SAWCR;
				break;
			case SAWCR:
				if(c=='\n') {
					state = EOL;
					p--;
					p[-1] = '\n';
				} else state = ORDIN;
				break;
			case EOL:
				state = (c==cmdchar ? SAWTL : 
					 (c=='\r' ? SAWCR : ORDIN));
				break;
			case SAWTL:
				state = (c=='>' ? DIVER : 
					 (c=='\r' ? SAWCR : ORDIN));
				break;
			case DIVER:
				if(c=='\r') {
					p--;
				} else if (c=='\n') {
					state = ORDIN;
					p[-1] = 0;
					dodiver(lb+2);
					c = 0; p = lb;
				}
			}
			if(slnt==0 && oldslnt) {
				if(c=='\n') {
					write(rem,lb,p-lb-1);
					write(rem,CRLF,sizeof(CRLF));
				} else if(q==rlim) {
					write(rem,lb,p-lb);
					c = '\n';  /*force flush to file*/
				}
			}
			if(c=='\n') {
				if(ds >= 0)
					write(ds,lb,p-lb);
				p = lb;
			}
		}
E 5
I 5
D 29
		write(1, rb, cnt);
E 29
E 5
	}
D 5
	if(justrung) {
		justrung = 0;
		goto agin;
	}
E 5
}

I 64
void
E 64
D 5
struct {char lobyte; char hibyte;};
E 5
mode(f)
I 64
	int f;
E 64
{
D 7
	struct sgttyb stbuf;
E 7
I 7
D 14
	struct ttychars *tc;
	int flags;
E 14
I 14
D 47
	struct tchars *tc;
E 47
D 69
	struct ltchars *ltc;
	struct sgttyb sb;
I 18
D 47
	int	lflags;
E 47
I 47
	struct tchars *tc;
	int lflags;
E 69
I 69
	struct termios tt;
E 69
E 47
E 18
E 14
E 7
D 5
	ioctl(0, TIOCGETP, &stbuf);
E 5
I 5

D 7
	ioctl(0, TIOCGETP, (char *)&stbuf);
E 5
	if (f == 0) {
		stbuf.sg_flags &= ~CBREAK;
D 2
		stbuf.sg_flags |= ECHO|CRMOD;
E 2
I 2
		stbuf.sg_flags |= defflags;
E 2
D 5
		ioctl(0, TIOCSETC, &deftchars);
		ioctl(0, TIOCSLTC, &defltchars);
E 5
I 5
		ioctl(0, TIOCSETC, (char *)&deftchars);
		ioctl(0, TIOCSLTC, (char *)&defltchars);
E 5
		stbuf.sg_kill = defkill;
		stbuf.sg_erase = deferase;
E 7
I 7
D 14
	ioctl(0, TIOCGET, (char *)&flags);
E 14
I 14
D 34
	ioctl(0, TIOCGETP, (char *)&sb);
I 18
	ioctl(0, TIOCLGET, (char *)&lflags);
E 34
I 34
D 47
	(void) ioctl(0, TIOCGETP, (char *)&sb);
	(void) ioctl(0, TIOCLGET, (char *)&lflags);
E 34
E 18
E 14
	switch (f) {

E 47
I 47
D 69
	(void)ioctl(0, TIOCGETP, (char *)&sb);
	(void)ioctl(0, TIOCLGET, (char *)&lflags);
	switch(f) {
E 69
I 69
	switch (f) {
E 69
E 47
	case 0:
D 12
		flags &= ~CBREAK;
		flags |= defflags;
E 12
I 12
D 14
		flags &= ~(CBREAK|RAW|TBDELAY);
		flags |= defflags|tabflag;
E 14
I 14
D 69
		sb.sg_flags &= ~(CBREAK|RAW|TBDELAY);
		sb.sg_flags |= defflags|tabflag;
E 14
E 12
		tc = &deftc;
I 14
		ltc = &defltc;
		sb.sg_kill = defkill;
		sb.sg_erase = deferase;
I 18
		lflags = deflflags;
E 69
I 69
		tcsetattr(0, TCSADRAIN, &deftt);
E 69
E 18
E 14
		break;
D 47

E 47
	case 1:
D 12
		flags |= CBREAK;
E 12
I 12
D 14
		flags |= (eight ? RAW : CBREAK);
E 12
		flags &= ~defflags;
E 14
I 14
D 69
		sb.sg_flags |= (eight ? RAW : CBREAK);
		sb.sg_flags &= ~defflags;
E 14
I 12
		/* preserve tab delays, but turn off XTABS */
D 14
		if ((flags & TBDELAY) == XTABS)
			flags &= ~TBDELAY;
E 14
I 14
		if ((sb.sg_flags & TBDELAY) == XTABS)
			sb.sg_flags &= ~TBDELAY;
E 14
E 12
		tc = &notc;
I 14
		ltc = &noltc;
		sb.sg_kill = sb.sg_erase = -1;
I 18
		if (litout)
			lflags |= LLITOUT;
E 69
I 69
		tt = deftt;
D 70
		tt.c_oflag &= ~OPOST;
E 70
I 70
		tt.c_oflag &= ~(OPOST);
E 70
		tt.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
I 70
		tt.c_iflag &= ~(ICRNL);
E 70
		tt.c_cc[VMIN] = 1;
		tt.c_cc[VTIME] = 0;
		if (eight) {
D 70
			tt.c_iflag &= ~(IXON | IXOFF);
E 70
I 70
			tt.c_iflag &= ~(IXON | IXOFF | ISTRIP);
E 70
			tt.c_cc[VSTOP] = _POSIX_VDISABLE;
			tt.c_cc[VSTART] = _POSIX_VDISABLE;
		}
		/*if (litout)
			lflags |= LLITOUT;*/
		tcsetattr(0, TCSADRAIN, &tt);
E 69
E 18
E 14
		break;
I 69

E 69
D 47

E 47
	default:
		return;
E 7
	}
D 7
	if (f == 1) {
		stbuf.sg_flags |= CBREAK;
		stbuf.sg_flags &= ~(ECHO|CRMOD);
D 5
		ioctl(0, TIOCSETC, &notchars);
		ioctl(0, TIOCSLTC, &noltchars);
		stbuf.sg_kill = 0377;
		stbuf.sg_erase = 0377;
E 5
I 5
		ioctl(0, TIOCSETC, (char *)&notchars);
		ioctl(0, TIOCSLTC, (char *)&noltchars);
		stbuf.sg_kill = -1;
		stbuf.sg_erase = -1;
E 5
	}
	if (f == 2) {
		stbuf.sg_flags &= ~CBREAK;
		stbuf.sg_flags &= ~(ECHO|CRMOD);
D 5
		ioctl(0, TIOCSETC, &deftchars);
		ioctl(0, TIOCSLTC, &defltchars);
		stbuf.sg_kill = 0377;
		stbuf.sg_erase = 0377;
E 5
I 5
		ioctl(0, TIOCSETC, (char *)&deftchars);
		ioctl(0, TIOCSLTC, (char *)&defltchars);
		stbuf.sg_kill = -1;
		stbuf.sg_erase = -1;
E 5
	}
D 5
	ioctl(0, TIOCSETN, &stbuf);
E 5
I 5
	ioctl(0, TIOCSETN, (char *)&stbuf);
E 7
I 7
D 14
	ioctl(0, TIOCSET, (char *)&flags);
	ioctl(0, TIOCCSET, (char *)tc);
E 14
I 14
D 34
	ioctl(0, TIOCSLTC, (char *)ltc);
	ioctl(0, TIOCSETC, (char *)tc);
	ioctl(0, TIOCSETN, (char *)&sb);
I 18
	ioctl(0, TIOCLSET, (char *)&lflags);
E 34
I 34
D 47
	(void) ioctl(0, TIOCSLTC, (char *)ltc);
	(void) ioctl(0, TIOCSETC, (char *)tc);
	(void) ioctl(0, TIOCSETN, (char *)&sb);
	(void) ioctl(0, TIOCLSET, (char *)&lflags);
E 47
I 47
D 69
	(void)ioctl(0, TIOCSLTC, (char *)ltc);
	(void)ioctl(0, TIOCSETC, (char *)tc);
	(void)ioctl(0, TIOCSETN, (char *)&sb);
	(void)ioctl(0, TIOCLSET, (char *)&lflags);
E 69
E 47
E 34
E 18
E 14
E 7
E 5
}

D 5
echo(s)
char *s;
{
	char *p;
	for (p=s;*p;p++);
	if (p>s) write(0,s,p-s);
	write(0,CRLF, sizeof(CRLF));
}

E 5
I 5
D 47
/*VARARGS*/
E 5
D 24
prf(f, a1, a2, a3)
E 24
I 24
prf(f, a1, a2, a3, a4, a5)
E 24
D 5
char *f;
E 5
I 5
	char *f;
E 47
I 47
void
D 64
lostpeer()
E 64
I 64
lostpeer(signo)
	int signo;
E 64
E 47
E 5
{
I 47
D 69
	(void)signal(SIGPIPE, SIG_IGN);
E 69
I 69
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;
	(void)sigaction(SIGPIPE, &sa, (struct sigaction *) 0);
E 69
	msg("\007connection closed.");
	done(1);
}
E 47
I 34

E 34
D 24
	fprintf(stderr, f, a1, a2, a3);
E 24
I 24
D 47
	fprintf(stderr, f, a1, a2, a3, a4, a5);
E 24
	fprintf(stderr, CRLF);
E 47
I 47
/* copy SIGURGs to the child process. */
void
D 64
copytochild()
E 64
I 64
copytochild(signo)
	int signo;
E 64
{
I 69

E 69
	(void)kill(child, SIGURG);
E 47
}

I 64
void
E 64
D 5
exists(devname)
char *devname;
E 5
I 5
D 47
lostpeer()
E 47
I 47
msg(str)
	char *str;
E 47
E 5
{
I 69

E 69
I 47
	(void)fprintf(stderr, "rlogin: %s\r\n", str);
}
E 47
D 5
	if (access(devname, 0)==0)
		return(1);
	prf("%s does not exist", devname);
	return(0);
}

rdc(ds)
{

	ds=read(ds,&c,1); 
	oc = c;
	if (eight == 0)
		c &= 0177;
	return (ds);
}

sig2()
{
	signal(SIGINT, SIG_IGN); 
	intr = 1;
E 5
I 5
D 11
	signal(SIGPIPE, SIG_IGN);
E 11
I 11
D 13
	sigignore(SIGPIPE);
E 13
I 13
D 34
	signal(SIGPIPE, SIG_IGN);
E 34
I 34

D 47
	(void) signal(SIGPIPE, SIG_IGN);
E 34
E 13
E 11
D 12
	prf("\007Lost connection");
E 12
I 12
	prf("\007Connection closed.");
E 12
D 29
	done();
E 29
I 29
	done(1);
E 47
I 47
#ifdef KERBEROS
/* VARARGS */
D 64
warning(va_alist)
va_dcl
E 64
I 64
void
#if __STDC__
warning(const char *fmt, ...)
#else
warning(fmt, va_alist)
	char *fmt;
	va_dcl
#endif
E 64
{
	va_list ap;
D 64
	char *fmt;
E 64

	(void)fprintf(stderr, "rlogin: warning, using standard rlogin: ");
I 64
#ifdef __STDC__
	va_start(ap, fmt);
#else
E 64
	va_start(ap);
I 64
#endif
E 64
D 65
	fmt = va_arg(ap, char *);
E 65
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, ".\n");
E 47
I 38
}
I 47
#endif
E 47

I 64
__dead void
E 64
D 47
old_warning(str)
	char	*str;
E 47
I 47
usage()
E 47
{
D 47
	prf("Warning: %s, using standard rlogin", str);
E 47
I 47
	(void)fprintf(stderr,
D 71
	    "usage: rlogin [ -%s]%s[-e char] [ -l username ] host\n",
E 71
I 71
	    "usage: rlogin [ -%s]%s[-e char] [ -l username ] [username@]host\n",
E 71
#ifdef KERBEROS
I 55
D 57
D 59
#ifdef CRYPT
E 55
D 54
	    "8Lx", " [-k realm] ");
E 54
I 54
D 61
	    "8ELx", " [-k realm] ");
E 61
I 61
	    "8EKLx", " [-k realm] ");
E 61
I 55
#else
E 59
E 57
D 61
	    "8EL", " [-k realm] ");
E 61
I 61
	    "8EKL", " [-k realm] ");
E 61
D 57
D 59
#endif
E 59
E 57
E 55
E 54
#else
D 54
	    "8L", " ");
E 54
I 54
	    "8EL", " ");
E 54
#endif
	exit(1);
E 47
E 38
E 29
E 5
}
I 47

/*
D 67
 * The following routine provides compatibility (such as it is) between 4.2BSD
E 67
I 67
 * The following routine provides compatibility (such as it is) between older
E 67
 * Suns and others.  Suns have only a `ttysize', so we convert it to a winsize.
 */
D 64
#ifdef sun
E 64
I 64
D 67
#ifdef SUNOS4
E 67
I 67
#ifdef OLDSUN
E 67
int
E 64
D 54
int
E 54
get_window_size(fd, wp)
	int fd;
	struct winsize *wp;
{
	struct ttysize ts;
	int error;

	if ((error = ioctl(0, TIOCGSIZE, &ts)) != 0)
D 64
		return(error);
E 64
I 64
		return (error);
E 64
	wp->ws_row = ts.ts_lines;
	wp->ws_col = ts.ts_cols;
	wp->ws_xpixel = 0;
	wp->ws_ypixel = 0;
D 64
	return(0);
E 64
I 64
	return (0);
E 64
}
#endif
I 54

D 64
u_char
E 64
I 64
u_int
E 64
getescape(p)
	register char *p;
{
	long val;
	int len;

	if ((len = strlen(p)) == 1)	/* use any single char, including '\' */
D 64
		return((u_char)*p);
E 64
I 64
		return ((u_int)*p);
E 64
					/* otherwise, \nnn */
	if (*p == '\\' && len >= 2 && len <= 4) {
D 64
		val = strtol(++p, (char **)NULL, 8);
E 64
I 64
		val = strtol(++p, NULL, 8);
E 64
		for (;;) {
			if (!*++p)
D 64
				return((u_char)val);
E 64
I 64
				return ((u_int)val);
E 64
			if (*p < '0' || *p > '8')
				break;
		}
	}
	msg("illegal option value -- e");
	usage();
	/* NOTREACHED */
}
E 54
E 47
I 32
D 36

E 36
E 32
E 1
