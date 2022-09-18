h43000
s 00012/00011/00745
d D 8.2 94/04/06 11:29:25 pendry 77 76
c prettiness police
e
s 00005/00005/00751
d D 8.1 93/06/04 19:06:06 bostic 76 75
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00754
d D 5.42 92/10/17 15:17:20 bostic 75 74
c snprintf returns printed length, not actual length
e
s 00001/00001/00755
d D 5.41 92/10/04 17:02:52 bostic 74 73
c don't write the trailing NULL out
e
s 00007/00005/00749
d D 5.40 92/07/28 18:23:27 bostic 73 72
c fileno fixes from Craig Leres
e
s 00105/00064/00649
d D 5.39 92/07/15 11:56:24 andrew 72 70
c add -L option to log successful accesses
e
s 00000/00131/00582
d D 5.38.1.1 91/08/20 17:32:00 mckusick 71 70
c delete data-stream encryption for the foreign sites (Network, Release 2)
e
s 00003/00001/00710
d D 5.38 91/03/02 10:12:14 bostic 70 69
c I messed up the default path stuff
e
s 00036/00034/00675
d D 5.37 91/02/25 17:33:44 bostic 69 67
c ANSI fixes (one real bug!)
e
s 00000/00130/00579
d D 5.36.1.1 90/10/21 20:26:10 mckusick 68 67
c delete data-stream encryption for the foreign sites (4.3-Reno)
e
s 00027/00009/00682
d D 5.36 90/10/21 20:25:18 mckusick 67 66
c use ifdef's that unifdef can understand
e
s 00016/00012/00675
d D 5.35 90/09/27 22:14:16 mckusick 66 65
c break out -x (encrypted sessions) with #ifdef CRYPT
e
s 00003/00002/00684
d D 5.34 90/06/29 18:55:36 karels 65 64
c don't log (null) hostname; can't fprintf to stderr, need to use error()
e
s 00006/00007/00680
d D 5.33 90/06/18 17:43:39 bostic 64 63
c port should be a u_short (no negative port numbers); minor whitespace
c changes.  from Chris Torek
e
s 00002/00006/00685
d D 5.32 90/06/18 16:42:51 bostic 63 62
c options were reversed, make sure it doesn't happen again
e
s 00001/00011/00690
d D 5.31 90/06/01 15:54:53 bostic 62 61
c new copyright notice
e
s 00001/00000/00700
d D 5.30 90/05/11 23:05:39 kfall 61 60
c now depends on kerberosIV/des.h
e
s 00001/00001/00699
d D 5.29 90/04/03 10:37:33 bostic 60 59
c include from kerberosIV, not /usr/include
e
s 00040/00029/00660
d D 5.28 90/03/28 09:04:41 karels 59 58
c if host address doesn't match name, attempt to login using number;
c if that fails, error message reports mismatch; cleanups
e
s 00005/00005/00684
d D 5.27 89/12/29 08:42:10 bostic 58 56
c rshd can dump core; bug report 4.3BSD-tahoe/libexec/0
e
s 00083/00028/00381
d D 5.17.1.3 89/09/11 21:47:17 karels 57 49
c sync with 5.26
e
s 00076/00063/00613
d D 5.26 89/09/11 21:46:43 karels 56 55
c restore keywords (again!); change local_domain to compare last two
c components of domain only; add -a; various cleanups; bug fix for encrypted rsh;
c not working, possibly because of last delta or library changes
e
s 00167/00025/00509
d D 5.25 89/09/08 10:13:23 kfall 55 54
c checked in by karels for kfall
e
s 00013/00003/00521
d D 5.24 89/07/24 12:29:17 kfall 54 53
c fix syslog: use AUTH for root shells; use AUTH_DAT for Kerberos
e
s 00028/00017/00496
d D 5.23 89/05/18 15:42:17 kfall 53 52
c don't require reserved ports for kerberos, -e now -x, move endpwent()
e
s 00003/00001/00510
d D 5.22 89/05/09 13:40:45 bostic 52 51
c add setlogname; add pathnames.h
e
s 00005/00004/00506
d D 5.21 89/04/02 14:49:57 bostic 51 50
c add pathnames.h
e
s 00019/00034/00491
d D 5.20 89/02/08 22:09:44 kfall 50 46
c add -e (encrypt) flag, openlog says "rshd", add usage() routine
e
s 00032/00008/00377
d D 5.17.1.2 89/02/07 15:38:05 karels 49 44
c on branch, sync with 5.19
e
s 00007/00123/00402
d R 5.20 89/02/07 15:28:24 karels 48 46
c on branch, sync with 5.19
e
s 00000/00001/00410
d R 5.17.1.2 89/02/07 15:11:34 karels 47 44
i 46
c on branch, sync with 5.19
e
s 00033/00009/00492
d D 5.19 89/02/07 15:04:42 karels 46 45
c purge first arg to doit (assume 0 and save the work),
c log and ignore source-routing on incoming connections
e
s 00002/00001/00499
d D 5.18 89/01/27 17:36:50 kfall 45 41
c close pv[1], don't close f (stderr was being lost)
e
s 00007/00122/00378
d D 5.17.1.1 89/01/25 19:35:14 karels 44 41
c branch for network release (no Kerberos), one more time...
e
s 00007/00122/00378
d R 5.18 89/01/25 19:32:58 karels 43 41
c branch for net release (no Kerberos)
e
s 00008/00123/00377
d R 5.17.1.1 89/01/25 19:32:15 karels 42 41
c branch for net release (no Kerberos)
e
s 00080/00056/00420
d D 5.17 89/01/25 19:31:45 karels 41 39
c cleanups
e
s 00079/00055/00421
d R 5.17 89/01/25 19:30:50 karels 40 39
c cleanups
e
s 00005/00002/00471
d D 5.16 89/01/24 18:13:28 kfall 39 38
c fix some syntax errors (for when KERBEROS is defined)
e
s 00177/00012/00296
d D 5.15 89/01/24 18:02:40 kfall 38 37
c double check hostname from gethostbyaddr, add kerberos ifdefs
e
s 00008/00003/00300
d D 5.14 89/01/23 11:50:44 bostic 37 36
c add -n flag to turn off keepalives
e
s 00017/00001/00286
d D 5.13 88/12/08 09:21:11 bostic 36 35
c add -l flag to turn off rhosts
e
s 00024/00012/00263
d D 5.12 88/09/12 22:27:29 bostic 35 34
c long/int fixes from 2.10BSD; add Berkeley specific copyright
e
s 00001/00001/00274
d D 5.11 88/04/18 15:06:59 bostic 34 33
c allow root to log in, even if nologin around
e
s 00009/00004/00266
d D 5.10 87/09/04 17:46:21 karels 33 32
c don't accept connections from ports below 512
e
s 00005/00000/00265
d D 5.9 87/05/04 12:03:26 bostic 32 31
c handle presence of /etc/nologin 
e
s 00001/00001/00264
d D 5.8 86/12/09 11:30:11 mckusick 31 30
c Rshd sets nonblocking mode on wrong file descriptor
c (from 4.3BSD/etc/31, serge)
e
s 00018/00019/00247
d D 5.7 86/05/09 03:00:13 lepreau 30 29
c lint
e
s 00007/00010/00259
d D 5.6 86/01/29 14:02:25 karels 29 28
c connection failure on second port unimportant (he gave up);
c don't need to build hostent structures
e
s 00003/00002/00266
d D 5.5 86/01/03 16:27:32 mckusick 28 27
c error needs to take additional arguments (jason@opal)
e
s 00008/00002/00260
d D 5.4 85/09/18 10:12:58 bloom 27 26
c don't exit on gethostbyaddr() failure, pass through address
e
s 00001/00007/00261
d D 5.3 85/09/17 19:12:58 eric 26 25
c facilities in syslog
e
s 00002/00001/00266
d D 5.2 85/08/28 10:02:29 bloom 25 24
c allow null passwd (from serge@arpa)
e
s 00014/00002/00253
d D 5.1 85/05/28 15:32:11 dist 24 23
c Add copyright
e
s 00016/00011/00239
d D 4.21 84/09/13 11:33:19 ralph 23 22
c use syslog for error messages
e
s 00005/00003/00245
d D 4.20 84/09/04 21:41:37 sam 22 21
c convert setsockopt calls to new interface
e
s 00001/00001/00247
d D 4.19 84/05/25 11:54:27 layer 21 20
c fixed exclusion from group 0 (from jrs@purue.arpa)
e
s 00025/00088/00223
d D 4.18 84/04/11 15:58:43 karels 20 18
c convert for use with inetd
e
s 00000/00000/00311
d R 4.18 84/04/11 15:37:33 karels 19 18
c convert for inetd
e
s 00002/00002/00309
d D 4.17 83/07/02 00:19:13 sam 18 17
c include fixes
e
s 00006/00003/00305
d D 4.16 83/06/12 01:46:35 sam 17 16
c new signals and linger no longer default
e
s 00000/00002/00308
d D 4.15 83/05/03 20:54:31 sam 16 15
c turn on keep alives
e
s 00005/00006/00305
d D 4.14 83/02/23 14:00:39 sam 15 13
c plug security hole with root; setgid comes before setuid; 
c parameter passing problem to shutdown
e
s 00004/00003/00308
d R 4.14 83/02/23 13:58:19 sam 14 13
c fix security hole with root; setgid must precede setuid, etc.
e
s 00001/00000/00310
d D 4.13 83/02/21 19:41:37 sam 13 12
c ignore SIGCHLD in child
e
s 00002/00009/00308
d D 4.12 83/02/10 21:30:22 sam 12 11
c remove backoff; DEBUG change before was wrong
e
s 00031/00013/00286
d D 4.11 83/01/22 22:17:48 sam 11 10
c do backoff on connect failure (probably not needed); also 
c postpone dups to allow diagnostics when running in debugging mode
e
s 00001/00001/00298
d D 4.10 83/01/22 16:11:42 sam 10 9
c SIGCHLD reset on each occurance
e
s 00012/00004/00287
d D 4.9 83/01/18 19:41:29 sam 9 8
c reap zombies instead of leaving one always outstanding
e
s 00014/00004/00277
d D 4.8 83/01/13 21:39:51 sam 8 7
c add debugging back in; fix FIN_WAIT_2 problem
e
s 00001/00002/00280
d D 4.7 83/01/07 20:38:00 sam 7 6
c no more SIOCDONE
e
s 00002/00002/00280
d D 4.6 82/12/25 21:18:39 sam 6 5
c port numbers now byte swapped
e
s 00001/00001/00281
d D 4.5 82/11/15 18:33:23 sam 5 4
c add domain specification
e
s 00001/00001/00281
d D 4.4 82/11/15 01:23:55 sam 4 3
c using wrong port for fd 2
e
s 00032/00023/00250
d D 4.3 82/11/14 15:15:12 sam 3 2
c convert to 4.1c sys calls and directory layout
e
s 00027/00016/00246
d D 4.2 82/10/07 23:42:18 sam 2 1
c use new date base routines
e
s 00262/00000/00000
d D 4.1 82/04/02 10:29:04 wnj 1 0
c date and time created 82/04/02 10:29:04 by wnj
e
u
U
f b 
t
T
I 24
D 69
/*
D 35
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 35
I 35
D 41
 * Copyright (c) 1983 The Regents of the University of California.
E 41
I 41
D 55
D 57
 * Copyright (c) 1983, 1988 The Regents of the University of California.
E 57
I 57
 * Copyright (c) 1983, 1988, 1989 The Regents of the University of California.
E 57
E 55
I 55
D 56
 *	$Source: /mit/kerberos/ucb/mit/rshd/RCS/rshd.c,v $
 *	$Header: /mit/kerberos/ucb/mit/rshd/RCS/rshd.c,v 5.2 89/07/31 19:30:04 kfall Exp $
 */

/*
 * Copyright (c) 1988, 1989 The Regents of the University of California.
E 56
I 56
 * Copyright (c) 1983, 1988, 1989 The Regents of the University of California.
E 69
I 69
/*-
D 72
 * Copyright (c) 1988, 1989 The Regents of the University of California.
E 72
I 72
D 76
 * Copyright (c) 1988, 1989, 1992 The Regents of the University of California.
E 72
E 69
E 56
E 55
E 41
 * All rights reserved.
E 76
I 76
D 77
 * Copyright (c) 1988, 1989, 1992, 1993
E 77
I 77
 * Copyright (c) 1988, 1989, 1992, 1993, 1994
E 77
 *	The Regents of the University of California.  All rights reserved.
E 76
 *
D 62
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
E 62
I 62
 * %sccs.include.redist.c%
E 62
E 35
 */

E 24
I 1
#ifndef lint
D 18
static char sccsid[] = "%W% %E%";
E 18
I 18
D 20
static char sccsid[] = "%W% (Berkeley) %E%";
E 20
I 20
D 24
static	char sccsid[] = "%W% (Berkeley) %G%";
E 20
E 18
#endif
E 24
I 24
D 76
char copyright[] =
D 35
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 35
I 35
D 38
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 38
I 38
D 41
"@(#) Copyright (c) 1983 The Regents of the University of California.\n\
E 41
I 41
D 56
D 57
"@(#) Copyright (c) 1983, 1988 The Regents of the University of California.\n\
E 57
I 57
"@(#) Copyright (c) 1983, 1988, 1989 The Regents of the University of California.\n\
E 57
E 56
I 56
D 69
"@(#) Copyright (c) 1983, 1988, 1089 The Regents of the University of California.\n\
E 69
I 69
D 72
"%Z% Copyright (c) 1988, 1989 The Regents of the University of California.\n\
E 72
I 72
"%Z% Copyright (c) 1988, 1989, 1992 The Regents of the University of California.\n\
E 72
E 69
E 56
E 41
E 38
E 35
 All rights reserved.\n";
E 76
I 76
static char copyright[] =
D 77
"%Z% Copyright (c) 1988, 1989, 1992, 1993\n\
E 77
I 77
"%Z% Copyright (c) 1988, 1989, 1992, 1993, 1994\n\
E 77
	The Regents of the University of California.  All rights reserved.\n";
E 76
D 35
#endif not lint
E 35
I 35
#endif /* not lint */
E 35

#ifndef lint
D 38
static char sccsid[] = "%W% (Berkeley) %G%";
E 38
I 38
D 41
static char sccsid[] = "@(#)rshd.c	5.14 (Berkeley) 1/23/89";
E 41
I 41
D 55
static char sccsid[] = "%W% (Berkeley) %G%";
E 55
I 55
D 56
static char sccsid[] = "@(#)rshd.c	5.23 (Berkeley) 5/18/89";
E 56
I 56
static char sccsid[] = "%W% (Berkeley) %G%";
E 56
E 55
E 41
E 38
D 35
#endif not lint
E 35
I 35
#endif /* not lint */
E 35
E 24

I 56
D 69
/* From:
E 69
I 69
/*
D 72
 * From:
E 69
 *	$Source: /mit/kerberos/ucb/mit/rshd/RCS/rshd.c,v $
D 69
 *	$Header: /mit/kerberos/ucb/mit/rshd/RCS/rshd.c,v 5.2 89/07/31 19:30:04 kfall Exp $
E 69
I 69
 *	$Header: /mit/kerberos/ucb/mit/rshd/RCS/rshd.c,v 
 *		5.2 89/07/31 19:30:04 kfall Exp $
E 69
 */

D 69

E 69
E 56
I 20
/*
E 72
 * remote shell server:
I 38
D 41
 *	\0
E 41
I 41
 *	[port]\0
E 41
E 38
 *	remuser\0
 *	locuser\0
 *	command\0
 *	data
 */
E 20
D 3
#include <stdio.h>
E 3
D 41
#include <sys/ioctl.h>
E 41
#include <sys/param.h>
I 41
#include <sys/ioctl.h>
E 41
D 69
#include <sys/socket.h>
I 32
#include <sys/file.h>
I 57
#include <sys/signal.h>
E 57
I 51
#include <sys/signal.h>
E 69
E 51
E 32
I 18
D 30
#include <sys/wait.h>
E 30
I 30
#include <sys/time.h>
I 69
D 72
#include <fcntl.h>
#include <signal.h>
E 69
E 30
E 18
D 3
#include <net/in.h>
E 3
I 3

E 72
I 69
#include <sys/socket.h>
I 72

E 72
E 69
#include <netinet/in.h>
D 69

E 69
I 27
#include <arpa/inet.h>
I 69
#include <netdb.h>
E 69

I 77
#include <errno.h>
E 77
I 72
#include <fcntl.h>
D 77
#include <signal.h>
E 77
I 77
#include <paths.h>
E 77
E 72
E 27
D 69
#include <stdio.h>
E 3
#include <errno.h>
E 69
#include <pwd.h>
D 18
#include <wait.h>
E 18
D 51
D 57
#include <signal.h>
E 57
E 51
I 2
D 69
#include <netdb.h>
E 69
I 23
D 77
#include <syslog.h>
I 57
#include "pathnames.h"
E 57
I 51
D 69
#include "pathnames.h"
E 69
I 69
#include <unistd.h>
#include <errno.h>
E 77
I 77
#include <signal.h>
E 77
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
D 77
#include <paths.h>
E 77
I 77
#include <syslog.h>
#include <unistd.h>
E 77
E 69
E 51
E 23
E 2

D 69
int	errno;
E 69
I 37
int	keepalive = 1;
I 57
int	check_all = 0;
E 57
I 56
D 72
int	check_all = 0;
E 56
E 37
I 9
D 20
int	reapchild();
E 9
D 2
struct	sockaddr_in sin = { AF_INET, IPPORT_CMDSERVER };
E 2
I 2
struct	sockaddr_in sin = { AF_INET };
E 20
E 2
D 23
struct	passwd *getpwnam();
D 2
char	*index(), *rindex(), *raddr(), *sprintf();
E 2
I 2
char	*index(), *rindex(), *sprintf();
E 23
I 23
D 30
char	*index(), *rindex();
E 23
E 2
D 8
int	options = SO_ACCEPTCONN|SO_KEEPALIVE;
E 8
I 8
D 20
int	options;
E 20
E 8
/* VARARGS 1 */
E 30
I 30
char	*index(), *rindex(), *strncat();
/*VARARGS1*/
E 30
int	error();
E 72
I 72
int	check_all;
int	log_success;		/* If TRUE, log all successful accesses */
E 72
I 57
int	sent_null;
E 57
I 56
int	sent_null;
E 56
D 20
/*
D 17
 * remote execute server:
E 17
I 17
 * remote shell server:
E 17
 *	remuser\0
 *	locuser\0
 *	command\0
 *	data
 */
E 20
I 20

I 72
void	 doit __P((struct sockaddr_in *));
void	 error __P((const char *, ...));
void	 getstr __P((char *, int, char *));
int	 local_domain __P((char *));
char	*topdomain __P((char *));
void	 usage __P((void));

E 72
I 38
D 44
#ifdef	KERBEROS
I 61
#include <kerberosIV/des.h>
E 61
D 55
#include <kerberos/krb.h>
E 55
I 55
D 60
#include <krb.h>
E 60
I 60
#include <kerberosIV/krb.h>
E 60
E 55
#define	VERSION_SIZE	9
D 50
#define	OPTIONS		"lnkv"
E 50
I 50
D 55
#define	OPTIONS		"lnkve"
E 55
I 55
#define SECURE_MESSAGE  "This rsh session is using DES encryption for all transmissions.\r\n"
D 56
#if	BSD > 43
#define	OPTIONS		"lnkvx"
#else
#define	OPTIONS		"nkvx"
#endif
E 56
I 56
D 63
#define	OPTIONS		"alnkvx"
E 63
I 63
D 72
#define	OPTIONS		"alknvx"
E 72
I 72
#define	OPTIONS		"alnkvxL"
E 72
E 63
E 56
E 55
E 50
D 59
char	*strsave();
E 59
char	authbuf[sizeof(AUTH_DAT)];
char	tickbuf[sizeof(KTEXT_ST)];
D 39
int	use_kerberos = 0;
E 39
I 39
D 69
int	use_kerberos = 0, vacuous = 0;
E 39
D 50

#define	OLD_RCMD		0x00
#define	KERB_RCMD		0x00
#define	KERB_RCMD_MUTUAL	0x03

E 50
int	encrypt = 0;
E 69
I 69
int	doencrypt, use_kerberos, vacuous;
E 69
I 55
Key_schedule	schedule;
E 55
#else
I 55
D 56
#if	BSD > 43
E 55
#define	OPTIONS	"ln"
I 55
#else
#define	OPTIONS	"n"
E 56
I 56
D 72
#define	OPTIONS	"aln"
E 72
I 72
#define	OPTIONS	"alnL"
E 72
E 56
E 55
#endif
I 55
D 56
#endif
E 56
E 55

E 44
E 38
I 30
D 72
/*ARGSUSED*/
E 72
I 72
int
E 72
E 30
E 20
main(argc, argv)
	int argc;
D 72
	char **argv;
E 72
I 72
	char *argv[];
E 72
{
I 36
D 55
D 57
	extern int opterr, optind, _check_rhosts_file;
E 57
I 57
	extern int opterr, optind;
	extern int _check_rhosts_file;
E 57
E 55
I 55
D 64
	
E 64
D 72
	extern int opterr, optind;
D 56
#if	BSD > 43
E 56
	extern int _check_rhosts_file;
E 72
I 72
	extern int __check_rhosts_file;
E 72
D 56
#endif
E 56
E 55
E 36
D 9
	union wait status;
E 9
D 17
	int f;
E 17
I 17
D 20
	int f, linger;
E 20
I 20
D 22
	int linger, fromlen;
E 22
I 22
	struct linger linger;
D 36
	int on = 1, fromlen;
E 36
I 36
	int ch, on = 1, fromlen;
E 36
E 22
E 20
E 17
	struct sockaddr_in from;
I 2
D 20
	struct servent *sp;
E 20
E 2

I 26
D 50
D 57
	openlog("rsh", LOG_PID | LOG_ODELAY, LOG_DAEMON);
E 57
I 57
	openlog("rshd", LOG_PID | LOG_ODELAY, LOG_DAEMON);
E 57
E 50
I 50
	openlog("rshd", LOG_PID | LOG_ODELAY, LOG_DAEMON);
E 50
I 36

	opterr = 0;
D 37
	while ((ch = getopt(argc, argv, "l")) != EOF)
E 37
I 37
D 38
	while ((ch = getopt(argc, argv, "ln")) != EOF)
E 38
I 38
D 44
	while ((ch = getopt(argc, argv, OPTIONS)) != EOF)
E 44
I 44
D 57
	while ((ch = getopt(argc, argv, "ln")) != EOF)
E 44
E 38
E 37
D 56
		switch((char)ch) {
E 57
I 57
	while ((ch = getopt(argc, argv, "aln")) != EOF)
		switch (ch) {
		case 'a':
			check_all = 1;
			break;
E 57
I 55
#if	BSD > 43
E 56
I 56
		switch (ch) {
		case 'a':
			check_all = 1;
			break;
E 56
E 55
		case 'l':
D 72
			_check_rhosts_file = 0;
E 72
I 72
			__check_rhosts_file = 0;
E 72
			break;
I 55
D 56
#endif
E 56
E 55
I 37
		case 'n':
			keepalive = 0;
			break;
I 38
D 44
#ifdef	KERBEROS
		case 'k':
			use_kerberos = 1;
			break;

		case 'v':
			vacuous = 1;
			break;
I 50

I 66
D 68
D 71
#ifdef CRYPT
E 66
D 53
		case 'e':
E 53
I 53
		case 'x':
E 53
D 69
			encrypt = 1;
E 69
I 69
			doencrypt = 1;
E 69
I 53
D 55
			{
				syslog(LOG_ERR,
					"-x option to rshd unimplemented");
				exit(1);
			}
E 55
E 53
			break;
E 71
E 68
E 50
#endif
I 66
D 68
D 71
#endif
I 72
		case 'L':
			log_success = 1;
			break;
E 72
E 71
E 68
E 66
E 44
E 38
E 37
		case '?':
		default:
D 50
D 57
			syslog(LOG_ERR, "usage: rshd [-l]");
E 57
I 57
			syslog(LOG_ERR, "usage: rshd [-aln]");
E 57
E 50
I 50
			usage();
E 50
D 59
			break;
E 59
I 59
D 77
			exit(2);
E 77
I 77
			break;
E 77
E 59
		}
I 38

E 38
	argc -= optind;
	argv += optind;

I 38
D 44
#ifdef	KERBEROS
D 41
	if(use_kerberos && vacuous) {
E 41
I 41
	if (use_kerberos && vacuous) {
E 41
		syslog(LOG_ERR, "only one of -k and -v allowed");
D 59
		exit(1);
E 59
I 59
		exit(2);
E 59
	}
I 66
D 68
D 71
#ifdef CRYPT
E 66
I 55
D 69
	if (encrypt && !use_kerberos) {
E 69
I 69
	if (doencrypt && !use_kerberos) {
E 69
D 59
			syslog(LOG_ERR, "-k is required for -x");
					exit(1);
E 59
I 59
		syslog(LOG_ERR, "-k is required for -x");
		exit(2);
E 59
	}
E 71
E 68
E 55
#endif
I 66
D 68
D 71
#endif
E 71
E 68
E 66
E 44
D 57

E 57
E 38
E 36
E 26
I 2
D 20
	sp = getservbyname("shell", "tcp");
	if (sp == 0) {
		fprintf(stderr, "rshd: tcp/shell: unknown service\n");
		exit(1);
E 20
I 20
	fromlen = sizeof (from);
D 69
	if (getpeername(0, &from, &fromlen) < 0) {
E 69
I 69
	if (getpeername(0, (struct sockaddr *)&from, &fromlen) < 0) {
E 69
D 56
D 57
		fprintf(stderr, "%s: ", argv[0]);
		perror("getpeername");
E 57
I 57
		syslog(LOG_ERR, "getpeername: %m");
E 57
E 56
I 56
		syslog(LOG_ERR, "getpeername: %m");
E 56
		_exit(1);
E 20
	}
E 2
D 20
#ifndef DEBUG
	if (fork())
		exit(0);
	for (f = 0; f < 10; f++)
		(void) close(f);
	(void) open("/", 0);
	(void) dup2(0, 1);
	(void) dup2(0, 2);
	{ int t = open("/dev/tty", 2);
	  if (t >= 0) {
		ioctl(t, TIOCNOTTY, (char *)0);
		(void) close(t);
	  }
E 20
I 20
D 22
	if (setsockopt(0, SOL_SOCKET, SO_KEEPALIVE, 0, 0) < 0) {
E 22
I 22
D 30
	if (setsockopt(0, SOL_SOCKET, SO_KEEPALIVE, &on, sizeof (on)) < 0) {
E 30
I 30
D 37
	if (setsockopt(0, SOL_SOCKET, SO_KEEPALIVE, (char *)&on,
	    sizeof (on)) < 0)
E 37
I 37
	if (keepalive &&
	    setsockopt(0, SOL_SOCKET, SO_KEEPALIVE, (char *)&on,
	    sizeof(on)) < 0)
E 37
E 30
E 22
D 23
		fprintf(stderr, "%s: ", argv[0]);
		perror("setsockopt (SO_KEEPALIVE)");
E 23
I 23
D 26
		openlog(argv[0], LOG_PID, 0);
E 26
		syslog(LOG_WARNING, "setsockopt (SO_KEEPALIVE): %m");
E 23
E 20
D 30
	}
E 30
D 20
#endif
D 2
#if vax
	sin.sin_port = htons(sin.sin_port);
#endif
E 2
I 2
D 6
	sin.sin_port = htons(sp->s_port);
E 6
I 6
	sin.sin_port = sp->s_port;
E 6
E 2
	argc--, argv++;
D 3
	if (argc > 0 && !strcmp(argv[0], "-d"))
D 2
		options |= SO_DEBUG;
E 2
I 2
		options |= SO_DEBUG, argc--, argv++;
	if (argc > 0) {
E 3
I 3
	if (argc > 0 && !strcmp(argv[0], "-d")) {
I 8
		options |= SO_DEBUG;
		argc--, argv++;
	}
	if (argc > 0) {
E 8
E 3
		int port = atoi(argv[0]);

		if (port < 0) {
			fprintf(stderr, "%s: bad port #\n", argv[0]);
			exit(1);
		}
D 6
		sin.sin_port = htons(port);
E 6
I 6
		sin.sin_port = htons((u_short)port);
E 6
		argc--, argv++;
	}
I 3
D 5
	f = socket(0, SOCK_STREAM, 0, 0);
E 5
I 5
	f = socket(AF_INET, SOCK_STREAM, 0, 0);
E 5
	if (f < 0) {
		perror("rshd: socket");
		exit(1);
	}
I 8
	if (options & SO_DEBUG && setsockopt(f, SOL_SOCKET, SO_DEBUG, 0, 0) < 0)
		perror("rshd: setsockopt (SO_DEBUG)");
D 16
#ifdef notdef
E 16
	if (setsockopt(f, SOL_SOCKET, SO_KEEPALIVE, 0, 0) < 0)
		perror("rshd: setsockopt (SO_KEEPALIVE)");
E 20
I 17
D 22
	linger = 60;			/* XXX */
E 22
I 22
	linger.l_onoff = 1;
	linger.l_linger = 60;			/* XXX */
E 22
D 20
	if (setsockopt(f, SOL_SOCKET, SO_LINGER, &linger, 0) < 0)
		perror("rshd: setsockopt (SO_LINGER)");
E 17
D 16
#endif
E 16
E 8
	if (bind(f, (caddr_t)&sin, sizeof (sin), 0) < 0) {
		perror("rshd: bind");
		exit(1);
E 20
I 20
D 30
	if (setsockopt(0, SOL_SOCKET, SO_LINGER, &linger, sizeof (linger)) < 0) {
E 30
I 30
	if (setsockopt(0, SOL_SOCKET, SO_LINGER, (char *)&linger,
	    sizeof (linger)) < 0)
E 30
D 23
		fprintf(stderr, "%s: ", argv[0]);
		perror("setsockopt (SO_LINGER)");
E 23
I 23
D 26
		openlog(argv[0], LOG_PID, 0);
E 26
		syslog(LOG_WARNING, "setsockopt (SO_LINGER): %m");
E 23
E 20
D 30
	}
E 30
I 9
D 10
	signal(SIGCHLD, reapchild);
E 10
I 10
D 17
	sigset(SIGCHLD, reapchild);
E 17
I 17
D 20
	signal(SIGCHLD, reapchild);
E 17
E 10
E 9
	listen(f, 10);
E 3
E 2
	for (;;) {
D 3
		errno = 0;
		f = socket(SOCK_STREAM, 0, &sin, options);
		if (f < 0) {
			perror("socket");
			sleep(5);
			continue;
		}
		if (accept(f, &from) < 0) {
E 3
I 3
		int g, len = sizeof (from);

		g = accept(f, &from, &len, 0);
		if (g < 0) {
I 9
			if (errno == EINTR)
				continue;
E 9
E 3
D 8
			perror("accept");
E 8
I 8
			perror("rshd: accept");
E 8
D 3
			(void) close(f);
E 3
D 9
			sleep(1);
E 9
			continue;
		}
D 3
		if (fork() == 0)
			doit(f, &from);
		(void) close(f);
		while(wait3(status, WNOHANG, 0) > 0)
E 3
I 3
		if (fork() == 0) {
D 15
			close(f);
E 15
I 13
			signal(SIGCHLD, SIG_IGN);
I 15
			close(f);
E 15
E 13
			doit(g, &from);
		}
		close(g);
D 9
		while (wait3(status, WNOHANG, 0) > 0)
E 3
			continue;
E 9
	}
E 20
I 20
D 41
	doit(dup(0), &from);
E 41
I 41
D 46
D 49
	doit(0, &from);
E 49
I 49
	doit(&from);
E 49
E 46
I 46
	doit(&from);
I 72
	/* NOTREACHED */
E 72
E 46
E 41
E 20
I 9
}

D 20
reapchild()
{
	union wait status;

	while (wait3(&status, WNOHANG, 0) > 0)
		;
E 9
}

E 20
char	username[20] = "USER=";
char	homedir[64] = "HOME=";
char	shell[64] = "SHELL=";
I 70
char	path[100] = "PATH=";
E 70
char	*envinit[] =
D 41
	    {homedir, shell, "PATH=:/usr/ucb:/bin:/usr/bin", username, 0};
E 41
I 41
D 51
D 57
	    {homedir, shell, "PATH=/usr/ucb:/bin:/usr/bin:", username, 0};
E 57
I 57
	    {homedir, shell, _PATH_DEFPATH, username, 0};
E 57
E 51
I 51
D 70
	    {homedir, shell, _PATH_DEFPATH, username, 0};
E 70
I 70
	    {homedir, shell, path, username, 0};
E 70
E 51
E 41
char	**environ;

I 72
void
E 72
D 46
D 49
doit(f, fromp)
	int f;
E 49
I 49
doit(fromp)
E 49
E 46
I 46
doit(fromp)
E 46
	struct sockaddr_in *fromp;
{
D 72
	char cmdbuf[NCARGS+1], *cp;
	char locuser[16], remuser[16];
	struct passwd *pwd;
D 2
	char *rhost;
E 2
D 11
	int s;
E 11
I 11
D 30
	int s, backoff;
E 30
I 30
	int s;
E 72
I 72
	extern char *__rcmd_errstr;	/* syslog hook from libc/net/rcmd.c. */
E 72
E 30
E 11
I 2
	struct hostent *hp;
I 27
D 29
	struct hostent hostent;
E 29
I 29
D 59
	char *hostname;
E 59
I 59
D 72
	char *hostname, *errorstr = NULL, *errorhost;
E 72
I 72
	struct passwd *pwd;
E 72
E 59
E 29
E 27
E 2
D 64
	short port;
E 64
I 64
	u_short port;
E 64
D 35
	int pv[2], pid, ready, readfrom, cc;
E 35
I 35
D 72
	int pv[2], pid, cc;
D 41
	long ready, readfrom;
E 41
I 41
	int nfd;
E 72
	fd_set ready, readfrom;
E 41
E 35
D 72
	char buf[BUFSIZ], sig;
E 72
I 72
	int cc, nfd, pv[2], pid, s;
E 72
	int one = 1;
I 72
	char *hostname, *errorstr, *errorhost;
	char *cp, sig, buf[BUFSIZ];
	char cmdbuf[NCARGS+1], locuser[16], remuser[16];
E 72
I 38
D 41
	char	localhost[MAXHOSTNAMELEN], remotehost[MAXHOSTNAMELEN];
	char	*raddr;
E 41
I 41
	char remotehost[2 * MAXHOSTNAMELEN + 1];
E 41
E 38

I 38
D 44
#ifdef	KERBEROS
	AUTH_DAT	*kdata = (AUTH_DAT *) NULL;
	KTEXT		ticket = (KTEXT) NULL;
	char		instance[INST_SZ], version[VERSION_SIZE];
D 59
	char		*h_name;
E 59
D 39
	struct		sockaddr_in	fromaddr = *fromp;
E 39
I 39
	struct		sockaddr_in	fromaddr;
E 39
	int		rc;
	long		authopts;
I 55
	int		pv1[2], pv2[2];
	fd_set		wready, writeto;
E 55
I 39

	fromaddr = *fromp;
E 39
#endif

E 44
E 38
	(void) signal(SIGINT, SIG_DFL);
	(void) signal(SIGQUIT, SIG_DFL);
	(void) signal(SIGTERM, SIG_DFL);
D 8
#ifdef DEBUG
E 8
I 8
D 12
#ifndef DEBUG
E 12
I 12
#ifdef DEBUG
E 12
E 8
D 52
D 57
	{ int t = open("/dev/tty", 2);
E 57
I 57
	{ int t = open(_PATH_TTY, 2);
E 57
E 52
I 52
	{ int t = open(_PATH_TTY, 2);
E 52
	  if (t >= 0) {
		ioctl(t, TIOCNOTTY, (char *)0);
		(void) close(t);
	  }
	}
#endif
D 11
	dup2(f, 0);
	dup2(f, 1);
	dup2(f, 2);
E 11
D 2
#if vax
E 2
	fromp->sin_port = ntohs((u_short)fromp->sin_port);
D 2
#endif
E 2
D 33
	if (fromp->sin_family != AF_INET ||
D 11
	    fromp->sin_port >= IPPORT_RESERVED)
E 11
I 11
	    fromp->sin_port >= IPPORT_RESERVED) {
E 33
I 33
	if (fromp->sin_family != AF_INET) {
E 33
D 23
		fprintf(stderr, "rshd: malformed from address\n");
E 23
I 23
D 26
		openlog("rshd", LOG_PID, 0);
E 26
D 59
		syslog(LOG_ERR, "malformed from address\n");
E 59
I 59
		syslog(LOG_ERR, "malformed \"from\" address (af %d)\n",
		    fromp->sin_family);
E 59
E 23
E 11
		exit(1);
I 11
	}
I 49
#ifdef IP_OPTIONS
      {
	u_char optbuf[BUFSIZ/3], *cp;
	char lbuf[BUFSIZ], *lp;
	int optsize = sizeof(optbuf), ipproto;
	struct protoent *ip;
E 49
I 46
#ifdef IP_OPTIONS
      {
	u_char optbuf[BUFSIZ/3], *cp;
	char lbuf[BUFSIZ], *lp;
	int optsize = sizeof(optbuf), ipproto;
	struct protoent *ip;
E 46
I 38

I 49
	if ((ip = getprotobyname("ip")) != NULL)
		ipproto = ip->p_proto;
	else
		ipproto = IPPROTO_IP;
	if (getsockopt(0, ipproto, IP_OPTIONS, (char *)optbuf, &optsize) == 0 &&
	    optsize != 0) {
		lp = lbuf;
		for (cp = optbuf; optsize > 0; cp++, optsize--, lp += 3)
			sprintf(lp, " %2.2x", *cp);
		syslog(LOG_NOTICE,
		    "Connection received using IP options (ignored):%s", lbuf);
		if (setsockopt(0, ipproto, IP_OPTIONS,
		    (char *)NULL, &optsize) != 0) {
			syslog(LOG_ERR, "setsockopt IP_OPTIONS NULL: %m");
			exit(1);
		}
	}
      }
#endif

E 49
I 46
	if ((ip = getprotobyname("ip")) != NULL)
		ipproto = ip->p_proto;
	else
		ipproto = IPPROTO_IP;
D 58
	if (getsockopt(0, ipproto, IP_OPTIONS, (char *)optbuf, &optsize) == 0 &&
E 58
I 58
	if (!getsockopt(0, ipproto, IP_OPTIONS, (char *)optbuf, &optsize) &&
E 58
	    optsize != 0) {
		lp = lbuf;
		for (cp = optbuf; optsize > 0; cp++, optsize--, lp += 3)
			sprintf(lp, " %2.2x", *cp);
		syslog(LOG_NOTICE,
D 59
		    "Connection received using IP options (ignored):%s", lbuf);
E 59
I 59
		    "Connection received from %s using IP options (ignored):%s",
		    inet_ntoa(fromp->sin_addr), lbuf);
E 59
		if (setsockopt(0, ipproto, IP_OPTIONS,
D 69
		    (char *)NULL, &optsize) != 0) {
E 69
I 69
		    (char *)NULL, optsize) != 0) {
E 69
			syslog(LOG_ERR, "setsockopt IP_OPTIONS NULL: %m");
			exit(1);
		}
	}
      }
#endif

E 46
D 44
D 53
#ifndef	KERBEROS
E 44
E 38
I 33
	if (fromp->sin_port >= IPPORT_RESERVED ||
	    fromp->sin_port < IPPORT_RESERVED/2) {
D 38
		syslog(LOG_NOTICE, "connection from bad port\n");
E 38
I 38
		syslog(LOG_NOTICE, "Connection from %s on illegal port",
			inet_ntoa(fromp->sin_addr));
E 38
		exit(1);
	}
E 53
I 53
#ifdef	KERBEROS
	if (!use_kerberos)
E 53
I 38
D 44
#endif
I 53
		if (fromp->sin_port >= IPPORT_RESERVED ||
D 64
	    		fromp->sin_port < IPPORT_RESERVED/2) {
E 64
I 64
		    fromp->sin_port < IPPORT_RESERVED/2) {
E 64
D 55
			syslog(LOG_NOTICE,
E 55
I 55
			syslog(LOG_NOTICE|LOG_AUTH,
E 55
D 59
				"Connection from %s on illegal port",
				inet_ntoa(fromp->sin_addr));
E 59
I 59
D 72
			    "Connection from %s on illegal port",
			    inet_ntoa(fromp->sin_addr));
E 72
I 72
			    "Connection from %s on illegal port %u",
			    inet_ntoa(fromp->sin_addr),
			    fromp->sin_port);
E 72
E 59
			exit(1);
		}
E 53
E 44

E 38
E 33
E 11
	(void) alarm(60);
	port = 0;
	for (;;) {
		char c;
D 11
		if (read(f, &c, 1) != 1)
E 11
I 11
D 33
		if (read(f, &c, 1) != 1) {
D 15
			int how = 1+1;

E 15
D 23
			perror("rshd: read");
E 23
I 23
D 26
			openlog("rshd", LOG_PID, 0);
E 26
			syslog(LOG_ERR, "read: %m");
E 33
I 33
D 46
D 49
		if ((cc = read(f, &c, 1)) != 1) {
E 49
I 49
		if ((cc = read(0, &c, 1)) != 1) {
E 49
E 46
I 46
D 73
		if ((cc = read(0, &c, 1)) != 1) {
E 73
I 73
		if ((cc = read(STDIN_FILENO, &c, 1)) != 1) {
E 73
E 46
			if (cc < 0)
				syslog(LOG_NOTICE, "read: %m");
E 33
E 23
D 15
			shutdown(f, &how);
E 15
I 15
D 46
D 49
			shutdown(f, 1+1);
E 49
I 49
			shutdown(0, 1+1);
E 49
E 46
I 46
			shutdown(0, 1+1);
E 46
E 15
E 11
			exit(1);
I 11
		}
I 38
D 44
D 50
#ifdef	KERBEROS
D 41
		if(c == OLD_RCMD || c == KERB_RCMD)
E 41
I 41
		if (c == OLD_RCMD || c == KERB_RCMD)
E 50
I 50
D 56
		if(c== 0)
E 56
I 56
		if (c== 0)
E 56
E 50
E 41
			break;
D 50

D 41
		if(c == KERB_RCMD_MUTUAL) {
E 41
I 41
		if (c == KERB_RCMD_MUTUAL) {
E 41
			encrypt = 1;
			break;
		}
#else
E 44
E 38
E 11
		if (c == 0)
			break;
I 38
D 44
#endif
E 50
E 44
E 38
		port = port * 10 + c - '0';
	}
I 38

E 38
	(void) alarm(0);
	if (port != 0) {
D 3
		s = rresvport(0);
E 3
I 3
D 11
		int lport = IPPORT_RESERVED - 1;
E 11
I 11
D 30
		int lport = IPPORT_RESERVED - 1, retryshift;
E 30
I 30
		int lport = IPPORT_RESERVED - 1;
E 30
E 11
D 8
		s = rresvport(0, &lport);
E 8
I 8
		s = rresvport(&lport);
E 8
E 3
D 11
		if (s < 0)
E 11
I 11
		if (s < 0) {
D 23
			perror("rshd: can't get stderr port");
E 23
I 23
D 26
			openlog("rshd", LOG_PID, 0);
E 26
			syslog(LOG_ERR, "can't get stderr port: %m");
E 23
E 11
			exit(1);
D 11
		if (port >= IPPORT_RESERVED)
			goto protofail;
		(void) alarm(60);
E 11
I 11
		}
I 38
D 44
D 53
#ifndef	KERBEROS
E 44
E 38
		if (port >= IPPORT_RESERVED) {
D 23
			fprintf(stderr, "rshd: 2nd port not reserved\n");
E 23
I 23
D 26
			openlog("rshd", LOG_PID, 0);
E 26
			syslog(LOG_ERR, "2nd port not reserved\n");
E 23
			exit(1);
		}
E 53
I 53
#ifdef	KERBEROS
		if (!use_kerberos)
E 53
I 38
D 44
#endif
I 53
			if (port >= IPPORT_RESERVED) {
				syslog(LOG_ERR, "2nd port not reserved\n");
				exit(1);
			}
E 53
E 44
E 38
E 11
D 2
		fromp->sin_port = port;
#if vax
		fromp->sin_port = ntohs(fromp->sin_port);
#endif
E 2
I 2
D 3
		fromp->sin_port = ntohs(port);
E 2
		if (connect(s, fromp) < 0)
E 3
I 3
D 4
		fromp->sin_port = htons((u_short)fromp->sin_port);
E 4
I 4
D 64
		fromp->sin_port = htons((u_short)port);
E 64
I 64
		fromp->sin_port = htons(port);
E 64
E 4
D 11
		if (connect(s, fromp, sizeof (*fromp), 0) < 0)
E 11
I 11
D 12
		for (backoff = 1; backoff != 0; backoff <<= 1) {
			(void) alarm(60);
			if (connect(s, fromp, sizeof (*fromp), 0) >= 0)
				break;
			(void) alarm(0);
			sleep(backoff);
		}
		if (backoff == 0) {
E 12
I 12
D 30
		if (connect(s, fromp, sizeof (*fromp), 0) < 0) {
E 30
I 30
D 69
		if (connect(s, fromp, sizeof (*fromp)) < 0) {
E 69
I 69
		if (connect(s, (struct sockaddr *)fromp, sizeof (*fromp)) < 0) {
E 69
E 30
E 12
D 23
			perror("rshd: connect");
E 23
I 23
D 26
			openlog("rshd", LOG_PID, 0);
E 26
D 29
			syslog(LOG_ERR, "connect: %m");
E 29
I 29
D 72
			syslog(LOG_INFO, "connect second port: %m");
E 72
I 72
			syslog(LOG_INFO, "connect second port %d: %m", port);
E 72
E 29
E 23
E 11
E 3
			exit(1);
D 11
		(void) alarm(0);
E 11
I 11
		}
E 11
	}
I 38

D 44
#ifdef	KERBEROS
D 41
	if(vacuous) {
E 41
I 41
	if (vacuous) {
E 41
		error("rshd: remote host requires Kerberos authentication\n");
		exit(1);
	}
#endif

E 44
I 41
#ifdef notdef
D 46
D 49
	/* from inetd, f is already on 0, 1, 2 */
E 49
I 49
	/* from inetd, socket is already on 0, 1, 2 */
E 49
E 46
I 46
	/* from inetd, socket is already on 0, 1, 2 */
E 46
E 41
E 38
I 11
	dup2(f, 0);
	dup2(f, 1);
	dup2(f, 2);
I 41
#endif
I 72
	errorstr = NULL;
E 72
E 41
E 11
D 2
	rhost = raddr(fromp->sin_addr.s_addr);
	if (rhost == 0) {
E 2
I 2
D 30
	hp = gethostbyaddr(&fromp->sin_addr, sizeof (struct in_addr),
E 30
I 30
	hp = gethostbyaddr((char *)&fromp->sin_addr, sizeof (struct in_addr),
E 30
		fromp->sin_family);
D 29
	if (hp == 0) {
E 2
D 27
		error("Host name for your address unknown\n");
		exit(1);
E 27
I 27
		/*
		 * Only the name is used below
		 */
		hp = &hostent;
		hp->h_name = inet_ntoa(fromp->sin_addr);
E 27
	}
E 29
I 29
D 38
	if (hp)
E 38
I 38
	if (hp) {
D 41
		(void) gethostname(localhost, sizeof(localhost));
		if(same_domain(hp->h_name, localhost)) {
			bcopy(hp->h_name, remotehost, sizeof(remotehost));
E 41
I 41
		/*
		 * If name returned by gethostbyaddr is in our domain,
		 * attempt to verify that we haven't been fooled by someone
		 * in a remote net; look up the name and check that this
		 * address corresponds to the name.
		 */
I 65
		hostname = hp->h_name;
E 65
D 56
D 57
		if (local_domain(hp->h_name)) {
E 57
I 57
		if (check_all || local_domain(hp->h_name)) {
E 57
E 56
I 56
D 59
		if (check_all || (!use_kerberos && local_domain(hp->h_name))) {
E 59
I 59
#ifdef	KERBEROS
		if (!use_kerberos)
#endif
		if (check_all || local_domain(hp->h_name)) {
E 59
E 56
			strncpy(remotehost, hp->h_name, sizeof(remotehost) - 1);
			remotehost[sizeof(remotehost) - 1] = 0;
I 59
			errorhost = remotehost;
E 59
E 41
			hp = gethostbyname(remotehost);
D 41
			if(hp == NULL) {
				syslog(LOG_NOTICE, "Couldn't get host entry for %s",
					remotehost);
				error("Couldn't get host entry for your host");
E 41
I 41
			if (hp == NULL) {
				syslog(LOG_INFO,
				    "Couldn't look up address for %s",
				    remotehost);
D 56
D 57
				error("Couldn't look up address for your host");
E 57
I 57
				error("Couldn't look up address for your host\n");
E 57
E 56
I 56
D 59
				error("Couldn't look up address for your host\n");
E 56
E 41
				exit(1);
E 59
I 59
D 64
				errorstr = 
E 64
I 64
				errorstr =
E 64
				"Couldn't look up address for your host (%s)\n";
				hostname = inet_ntoa(fromp->sin_addr);
E 59
D 41
			} else {
			    for(;;) {
				if(!(raddr = hp->h_addr_list[0])) {
					syslog(LOG_NOTICE, "Host addr not listed for host %s",
						hp->h_name);
E 41
I 41
D 57
			} else for (; ; hp->h_addr_list++) {
E 57
I 57
			}
#ifdef h_addr	/* 4.2 hack */
			for (; ; hp->h_addr_list++) {
E 57
D 58
				if (!bcmp(hp->h_addr_list[0],
				    (caddr_t)&fromp->sin_addr,
				    sizeof(fromp->sin_addr)))
					break;
E 58
				if (hp->h_addr_list[0] == NULL) {
					syslog(LOG_NOTICE,
					  "Host addr %s not listed for host %s",
					    inet_ntoa(fromp->sin_addr),
					    hp->h_name);
E 41
D 56
D 57
					error("Host address mismatch");
E 57
I 57
					error("Host address mismatch\n");
E 57
E 56
I 56
D 59
					error("Host address mismatch\n");
E 56
					exit(1);
E 59
I 59
					errorstr =
					    "Host address mismatch for %s\n";
					hostname = inet_ntoa(fromp->sin_addr);
					break;
E 59
				}
I 58
				if (!bcmp(hp->h_addr_list[0],
				    (caddr_t)&fromp->sin_addr,
D 59
				    sizeof(fromp->sin_addr)))
E 59
I 59
				    sizeof(fromp->sin_addr))) {
					hostname = hp->h_name;
E 59
					break;
I 59
				}
E 59
E 58
D 41
				if(!bcmp(raddr, (caddr_t)&fromp->sin_addr,
					sizeof(struct in_addr))) {
						break;
				}
				hp->h_addr_list++;
			    }
E 41
			}
I 57
#else
			if (bcmp(hp->h_addr, (caddr_t)&fromp->sin_addr,
			    sizeof(fromp->sin_addr))) {
				syslog(LOG_NOTICE,
				  "Host addr %s not listed for host %s",
				    inet_ntoa(fromp->sin_addr),
				    hp->h_name);
				error("Host address mismatch\n");
				exit(1);
			}
#endif
E 57
		}
E 38
D 59
		hostname = hp->h_name;
E 59
D 38
	else
E 38
I 38
D 41
	} else {
E 41
I 41
	} else
E 41
E 38
D 59
		hostname = inet_ntoa(fromp->sin_addr);
E 59
I 59
		errorhost = hostname = inet_ntoa(fromp->sin_addr);
E 59
E 29
D 38
	getstr(remuser, sizeof(remuser), "remuser");
E 38
I 38
D 41
	}
E 41

D 44
#ifdef	KERBEROS
D 41
	if(use_kerberos) {
E 41
I 41
	if (use_kerberos) {
E 41
D 59
		h_name = strsave(hp->h_name);
E 59
		kdata = (AUTH_DAT *) authbuf;
		ticket = (KTEXT) tickbuf;
		authopts = 0L;
		strcpy(instance, "*");
		version[VERSION_SIZE - 1] = '\0';
I 66
D 68
D 71
#ifdef CRYPT
E 66
D 41
		if(rc = krb_recvauth(
			authopts, f, ticket, "rcmd",
E 41
I 41
D 46
		if (rc = krb_recvauth(authopts, f, ticket, "rcmd",
E 46
I 46
D 55
		if (rc = krb_recvauth(authopts, 0, ticket, "rcmd",
E 46
E 41
			instance, &fromaddr,
			(struct sockaddr_in *) 0,
D 41
			kdata, "", (bit_64 *) 0, version)
		) {
E 41
I 41
			kdata, "", (bit_64 *) 0, version)) {
E 55
I 55
D 69
		if (encrypt) {
E 69
I 69
		if (doencrypt) {
E 69
D 59
			struct sockaddr_in	local_addr;
E 59
I 59
			struct sockaddr_in local_addr;
E 59
			rc = sizeof(local_addr);
D 69
			if (getsockname(0, &local_addr, &rc) < 0) {
E 69
I 69
			if (getsockname(0, (struct sockaddr *)&local_addr,
			    &rc) < 0) {
E 69
D 56
				perror("getsockname");
E 56
I 56
				syslog(LOG_ERR, "getsockname: %m");
I 65
				error("rlogind: getsockname: %m");
E 65
E 56
				exit(1);
			}
			authopts = KOPT_DO_MUTUAL;
			rc = krb_recvauth(authopts, 0, ticket,
				"rcmd", instance, &fromaddr,
				&local_addr, kdata, "", schedule,
				version);
			des_set_key(kdata->session, schedule);
D 66
		} else {
E 66
I 66
		} else
#endif
E 71
E 68
E 66
			rc = krb_recvauth(authopts, 0, ticket, "rcmd",
				instance, &fromaddr,
				(struct sockaddr_in *) 0,
				kdata, "", (bit_64 *) 0, version);
D 66
		}
E 66
		if (rc != KSUCCESS) {
E 55
E 41
D 65
			fprintf(stderr,
				"Kerberos authentication failure: %s\r\n",
E 65
I 65
			error("Kerberos authentication failure: %s\n",
E 65
				  krb_err_txt[rc]);
			exit(1);
		}
D 59
		free(h_name);
		h_name = NULL;
E 59
	} else
#endif
		getstr(remuser, sizeof(remuser), "remuser");

E 44
I 44
	getstr(remuser, sizeof(remuser), "remuser");
E 44
E 38
	getstr(locuser, sizeof(locuser), "locuser");
	getstr(cmdbuf, sizeof(cmdbuf), "command");
	setpwent();
	pwd = getpwnam(locuser);
	if (pwd == NULL) {
I 72
		syslog(LOG_INFO|LOG_AUTH,
		    "%s@%s as %s: unknown login. cmd='%.80s'",
		    remuser, hostname, locuser, cmdbuf);
E 72
D 59
		error("Login incorrect.\n");
		exit(1);
E 59
I 59
		if (errorstr == NULL)
			errorstr = "Login incorrect.\n";
		goto fail;
E 59
	}
D 53
D 57
	endpwent();
E 57
E 53
	if (chdir(pwd->pw_dir) < 0) {
I 20
D 30
		chdir("/");
E 30
I 30
		(void) chdir("/");
E 30
#ifdef notdef
I 72
		syslog(LOG_INFO|LOG_AUTH,
		    "%s@%s as %s: no home directory. cmd='%.80s'",
		    remuser, hostname, locuser, cmdbuf);
E 72
E 20
		error("No remote directory.\n");
		exit(1);
I 20
#endif
E 20
	}
D 2
	if (ruserok(rhost, remuser, locuser) < 0) {
E 2
I 2
D 15
	if (ruserok(hp->h_name, remuser, locuser) < 0) {
E 15
I 15
D 25
	if (ruserok(hp->h_name, pwd->pw_uid == 0, remuser, locuser) < 0) {
E 25
I 25
D 38
	if (pwd->pw_passwd != 0 && *pwd->pw_passwd != '\0' &&
D 29
	    ruserok(hp->h_name, pwd->pw_uid == 0, remuser, locuser) < 0) {
E 29
I 29
	    ruserok(hostname, pwd->pw_uid == 0, remuser, locuser) < 0) {
E 29
E 25
E 15
E 2
		error("Permission denied.\n");
I 32
		exit(1);
	}
E 38
I 38

D 44
#ifdef	KERBEROS
D 41
	if(use_kerberos) {
E 41
I 41
	if (use_kerberos) {
E 41
		if (pwd->pw_passwd != 0 && *pwd->pw_passwd != '\0') {
D 41
			if(krb_kntoln(kdata, remuser) != KSUCCESS) {
E 41
I 41
D 50
			if (krb_kntoln(kdata, remuser) != KSUCCESS) {
E 41
				error("Permission denied.\n");
				exit(1);
			}
E 50
D 41
			if(kuserok(kdata, locuser) != 0) {
E 41
I 41
			if (kuserok(kdata, locuser) != 0) {
E 41
D 50
				syslog(LOG_NOTICE, "Kerberos rlogin denied to %s.%s@%s",
E 50
I 50
D 55
				syslog(LOG_NOTICE, "Kerberos rsh denied to %s.%s@%s",
E 55
I 55
D 59
				syslog(LOG_NOTICE|LOG_AUTH, "Kerberos rsh denied to %s.%s@%s",
E 55
E 50
					kdata->pname, kdata->pinst, kdata->prealm);
E 59
I 59
D 72
				syslog(LOG_NOTICE|LOG_AUTH,
E 72
I 72
				syslog(LOG_INFO|LOG_AUTH,
E 72
				    "Kerberos rsh denied to %s.%s@%s",
				    kdata->pname, kdata->pinst, kdata->prealm);
E 59
				error("Permission denied.\n");
				exit(1);
			}
I 39
		}
E 39
	} else
#endif
E 44
I 44
	if (pwd->pw_passwd != 0 && *pwd->pw_passwd != '\0' &&
	    ruserok(hostname, pwd->pw_uid == 0, remuser, locuser) < 0) {
		error("Permission denied.\n");
		exit(1);
	}
E 44

D 44
D 53
		if (pwd->pw_passwd != 0 && *pwd->pw_passwd != '\0' &&
E 53
I 53
D 59
 		if (pwd->pw_passwd != 0 && *pwd->pw_passwd != '\0' &&
E 59
I 59
D 64
 		if (errorstr ||
E 64
I 64
		if (errorstr ||
E 64
		    pwd->pw_passwd != 0 && *pwd->pw_passwd != '\0' &&
E 59
E 53
D 72
		    ruserok(hostname, pwd->pw_uid == 0, remuser, locuser) < 0) {
E 72
I 72
		    iruserok(fromp->sin_addr.s_addr, pwd->pw_uid == 0,
		    remuser, locuser) < 0) {
			if (__rcmd_errstr)
				syslog(LOG_INFO|LOG_AUTH,
			    "%s@%s as %s: permission denied (%s). cmd='%.80s'",
				    remuser, hostname, locuser, __rcmd_errstr,
				    cmdbuf);
			else
				syslog(LOG_INFO|LOG_AUTH,
			    "%s@%s as %s: permission denied. cmd='%.80s'",
				    remuser, hostname, locuser, cmdbuf);
E 72
D 59
			error("Permission denied.\n");
E 59
I 59
fail:
			if (errorstr == NULL)
				errorstr = "Permission denied.\n";
			error(errorstr, errorhost);
E 59
			exit(1);
		}

E 44
E 38
D 34
	if (!access("/etc/nologin", F_OK)) {
E 34
I 34
D 51
D 57
	if (pwd->pw_uid && !access("/etc/nologin", F_OK)) {
E 57
I 57
	if (pwd->pw_uid && !access(_PATH_NOLOGIN, F_OK)) {
E 57
E 51
I 51
	if (pwd->pw_uid && !access(_PATH_NOLOGIN, F_OK)) {
E 51
E 34
		error("Logins currently disabled.\n");
E 32
		exit(1);
	}
I 57

E 57
I 38
D 44
D 50
#ifdef	KERBEROS
D 41
	if(encrypt) {
E 41
I 41
	if (encrypt) {
E 41
		char c = KERB_RCMD_MUTUAL;
		(void) write(2, &c, 1);
	} else {
		char c = KERB_RCMD;
		(void) write(2, &c, 1);
	}
#else
E 50
I 50

E 50
E 44
E 38
D 73
	(void) write(2, "\0", 1);
E 73
I 73
	(void) write(STDERR_FILENO, "\0", 1);
E 73
I 57
	sent_null = 1;
E 57
I 56
	sent_null = 1;
E 56
I 38
D 44
D 50
#endif
E 50
E 44

E 38
	if (port) {
		if (pipe(pv) < 0) {
			error("Can't make pipe.\n");
			exit(1);
		}
I 55
D 66
#ifdef	KERBEROS
E 66
I 66
D 67
#if defined(KERBEROS) && defined(CRYPT)
E 67
I 67
D 68
D 71
#ifdef CRYPT
#ifdef KERBEROS
E 67
E 66
D 69
		if (encrypt) {
E 69
I 69
		if (doencrypt) {
E 69
			if (pipe(pv1) < 0) {
				error("Can't make 2nd pipe.\n");
				exit(1);
			}
			if (pipe(pv2) < 0) {
				error("Can't make 3rd pipe.\n");
				exit(1);
			}
		}
#endif
I 67
#endif
E 71
E 68
E 67
E 55
		pid = fork();
		if (pid == -1)  {
D 56
D 57
			error("Try again.\n");
E 57
I 57
			error("Can't fork; try again.\n");
E 57
E 56
I 56
			error("Can't fork; try again.\n");
E 56
			exit(1);
		}
I 41
D 56
		if (pv[0] > s)
			nfd = pv[0];
		else
			nfd = s;
		nfd++;
E 56
E 41
		if (pid) {
D 55
			(void) close(0); (void) close(1); (void) close(2);
D 46
D 49
			(void) close(f); (void) close(pv[1]);
E 49
I 49
			(void) close(pv[1]);
E 49
E 46
I 46
			(void) close(pv[1]);
E 55
I 55
D 66
#ifdef	KERBEROS
E 66
I 66
D 67
#if defined(KERBEROS) && defined(CRYPT)
E 67
I 67
D 68
D 71
#ifdef CRYPT
#ifdef KERBEROS
E 67
E 66
D 69
			if (encrypt) {
E 69
I 69
			if (doencrypt) {
E 69
				static char msg[] = SECURE_MESSAGE;
D 56
				(void) close(pv[1]); (void) close(pv1[1]);
				(void) close(pv2[1]); (void) close(2);
E 56
I 56
				(void) close(pv1[1]);
				(void) close(pv2[1]);
E 56
D 74
				des_write(s, msg, sizeof(msg));
E 74
I 74
				des_write(s, msg, sizeof(msg) - 1);
E 74

			} else
#endif
I 67
#endif
E 71
E 68
E 67
			{
D 72
				(void) close(0); (void) close(1);
E 72
I 72
				(void) close(0);
				(void) close(1);
E 72
D 56
				(void) close(2); (void) close(pv[1]);
E 56
			}
I 56
D 72
			(void) close(2); (void) close(pv[1]);
E 72
I 72
			(void) close(2);
			(void) close(pv[1]);
E 72
E 56

E 55
E 46
D 35
			readfrom = (1<<s) | (1<<pv[0]);
E 35
I 35
D 41
			readfrom = (1L<<s) | (1L<<pv[0]);
E 41
I 41
			FD_ZERO(&readfrom);
			FD_SET(s, &readfrom);
			FD_SET(pv[0], &readfrom);
I 56
			if (pv[0] > s)
				nfd = pv[0];
			else
				nfd = s;
E 56
E 41
E 35
D 31
			ioctl(pv[1], FIONBIO, (char *)&one);
E 31
I 31
D 55
			ioctl(pv[0], FIONBIO, (char *)&one);
E 55
I 55
D 66
#ifdef	KERBEROS
E 66
I 66
D 67
#if defined(KERBEROS) && defined(CRYPT)
E 67
I 67
D 68
D 71
#ifdef CRYPT
#ifdef KERBEROS
E 67
E 66
D 69
			if (encrypt) {
E 69
I 69
			if (doencrypt) {
E 69
				FD_ZERO(&writeto);
				FD_SET(pv2[0], &writeto);
				FD_SET(pv1[0], &readfrom);

				nfd = MAX(nfd, pv2[0]);
				nfd = MAX(nfd, pv1[0]);
			} else
#endif
I 67
#endif
E 71
E 68
E 67
				ioctl(pv[0], FIONBIO, (char *)&one);

E 55
E 31
			/* should set s nbio! */
I 56
			nfd++;
E 56
			do {
				ready = readfrom;
D 3
				(void) select(32, &ready, 0, 1000000);
E 3
I 3
D 30
				if (select(16, &ready, 0, 0, 0) < 0)
E 30
I 30
D 41
				if (select(16, &ready, (fd_set *)0,
E 41
I 41
D 55
				if (select(nfd, &ready, (fd_set *)0,
E 41
				    (fd_set *)0, (struct timeval *)0) < 0)
E 30
					break;
E 55
I 55
D 66
#ifdef	KERBEROS
E 66
I 66
D 67
#if defined(KERBEROS) && defined(CRYPT)
E 67
I 67
D 68
D 71
#ifdef CRYPT
#ifdef KERBEROS
E 67
E 66
D 69
				if (encrypt) {
E 69
I 69
				if (doencrypt) {
E 69
					wready = writeto;
					if (select(nfd, &ready,
					    &wready, (fd_set *) 0,
					    (struct timeval *) 0) < 0)
						break;
				} else
#endif
I 67
#endif
E 71
E 68
E 67
					if (select(nfd, &ready, (fd_set *)0,
D 64
				          (fd_set *)0, (struct timeval *)0) < 0)
E 64
I 64
					  (fd_set *)0, (struct timeval *)0) < 0)
E 64
						break;
E 55
E 3
D 35
				if (ready & (1<<s)) {
E 35
I 35
D 41
				if (ready & (1L<<s)) {
E 41
I 41
				if (FD_ISSET(s, &ready)) {
E 41
E 35
D 55
					if (read(s, &sig, 1) <= 0)
E 55
I 55
					int	ret;
D 66
#ifdef	KERBEROS
E 66
I 66
D 67
#if defined(KERBEROS) && defined(CRYPT)
E 67
I 67
D 68
D 71
#ifdef CRYPT
#ifdef KERBEROS
E 67
E 66
D 69
					if (encrypt)
E 69
I 69
					if (doencrypt)
E 69
						ret = des_read(s, &sig, 1);
					else
#endif
I 67
#endif
E 71
E 68
E 67
						ret = read(s, &sig, 1);
					if (ret <= 0)
E 55
D 35
						readfrom &= ~(1<<s);
E 35
I 35
D 41
						readfrom &= ~(1L<<s);
E 41
I 41
						FD_CLR(s, &readfrom);
E 41
E 35
					else
						killpg(pid, sig);
				}
D 35
				if (ready & (1<<pv[0])) {
E 35
I 35
D 41
				if (ready & (1L<<pv[0])) {
E 41
I 41
				if (FD_ISSET(pv[0], &ready)) {
E 41
E 35
I 15
					errno = 0;
E 15
D 55
					cc = read(pv[0], buf, sizeof (buf));
E 55
I 55
					cc = read(pv[0], buf, sizeof(buf));
E 55
					if (cc <= 0) {
D 7
						int done = 1+1;
						ioctl(s, SIOCDONE, (char *)&done);
E 7
I 7
						shutdown(s, 1+1);
E 7
D 35
						readfrom &= ~(1<<pv[0]);
E 35
I 35
D 41
						readfrom &= ~(1L<<pv[0]);
E 41
I 41
						FD_CLR(pv[0], &readfrom);
I 55
					} else {
D 66
#ifdef	KERBEROS
E 66
I 66
D 67
#if defined(KERBEROS) && defined(CRYPT)
E 67
I 67
D 68
D 71
#ifdef CRYPT
#ifdef KERBEROS
E 67
E 66
D 69
						if (encrypt)
E 69
I 69
						if (doencrypt)
E 71
E 69
E 68
							(void)
D 68
D 71
							  des_write(s, buf, cc);
						else
#endif
I 67
#endif
E 67
							(void)
E 71
E 68
							  write(s, buf, cc);
					}
				}
D 66
#ifdef	KERBEROS

E 66
I 66
D 67
#if defined(KERBEROS) && defined(CRYPT)
E 67
I 67
D 68
D 71
#ifdef CRYPT
#ifdef KERBEROS
E 67
E 66
D 69
				if (encrypt && FD_ISSET(pv1[0], &ready)) {
E 69
I 69
				if (doencrypt && FD_ISSET(pv1[0], &ready)) {
E 69
					errno = 0;
					cc = read(pv1[0], buf, sizeof(buf));
					if (cc <= 0) {
						shutdown(pv1[0], 1+1);
						FD_CLR(pv1[0], &readfrom);
E 55
E 41
E 35
					} else
D 55
						(void) write(s, buf, cc);
E 55
I 55
D 73
						(void) des_write(1, buf, cc);
E 73
I 73
						(void) des_write(STDOUT_FILENO,
						    buf, cc);
E 73
E 55
				}
E 71
E 68
I 55

D 68
D 69
				if (encrypt && FD_ISSET(pv2[0], &wready)) {
E 69
I 69
D 71
				if (doencrypt && FD_ISSET(pv2[0], &wready)) {
E 69
					errno = 0;
D 73
					cc = des_read(0, buf, sizeof(buf));
E 73
I 73
					cc = des_read(STDIN_FILENO,
					    buf, sizeof(buf));
E 73
					if (cc <= 0) {
						shutdown(pv2[0], 1+1);
						FD_CLR(pv2[0], &writeto);
					} else
						(void) write(pv2[0], buf, cc);
				}
#endif
I 67
#endif
E 67

E 71
E 68
E 55
D 41
			} while (readfrom);
E 41
I 41
			} while (FD_ISSET(s, &readfrom) ||
I 55
D 66
#ifdef	KERBEROS
E 66
I 66
D 67
#if defined(KERBEROS) && defined(CRYPT)
E 67
I 67
D 68
D 71
#ifdef CRYPT
#ifdef KERBEROS
E 67
E 66
D 69
			    (encrypt && FD_ISSET(pv1[0], &readfrom)) ||
E 69
I 69
			    (doencrypt && FD_ISSET(pv1[0], &readfrom)) ||
E 69
#endif
I 67
#endif
E 71
E 68
E 67
E 55
			    FD_ISSET(pv[0], &readfrom));
E 41
			exit(0);
		}
		setpgrp(0, getpid());
D 72
		(void) close(s); (void) close(pv[0]);
E 72
I 72
		(void) close(s);
		(void) close(pv[0]);
E 72
I 55
D 66
#ifdef	KERBEROS
E 66
I 66
D 67
#if defined(KERBEROS) && defined(CRYPT)
E 67
I 67
D 68
D 71
#ifdef CRYPT
#ifdef KERBEROS
E 67
E 66
D 69
		if (encrypt) {
E 69
I 69
		if (doencrypt) {
E 69
			close(pv1[0]); close(pv2[0]);
			dup2(pv1[1], 1);
			dup2(pv2[1], 0);
			close(pv1[1]);
			close(pv2[1]);
		}
I 67
#endif
E 67
#endif
E 71
E 68
E 55
		dup2(pv[1], 2);
I 57
		close(pv[1]);
E 57
I 45
		close(pv[1]);
E 45
	}
	if (*pwd->pw_shell == '\0')
D 51
D 57
		pwd->pw_shell = "/bin/sh";
E 57
I 57
		pwd->pw_shell = _PATH_BSHELL;
#if	BSD > 43
	if (setlogin(pwd->pw_name) < 0)
		syslog(LOG_ERR, "setlogin() failed: %m");
#endif
E 57
E 51
I 51
		pwd->pw_shell = _PATH_BSHELL;
E 51
D 45
D 49
	(void) close(f);
E 49
E 45
I 45
D 46
	/* (void) close(f); */
E 46
E 45
D 3
	inigrp(pwd->pw_name, pwd->pw_gid);
E 3
I 3
D 21
	initgroups(pwd->pw_name, pwd->pw_gid);
E 21
E 3
D 15
	(void) setuid(pwd->pw_uid);
E 15
D 30
	(void) setgid(pwd->pw_gid);
E 30
I 30
D 56
	(void) setgid((gid_t)pwd->pw_gid);
E 30
I 21
	initgroups(pwd->pw_name, pwd->pw_gid);
E 56
I 55
#if	BSD > 43
E 55
I 52
D 56
	if (setlogname(pwd->pw_name, strlen(pwd->pw_name)) < 0)
		syslog(LOG_NOTICE, "setlogname() failed: %m");
E 56
I 56
	if (setlogin(pwd->pw_name) < 0)
		syslog(LOG_ERR, "setlogin() failed: %m");
E 56
I 55
#endif
I 56
	(void) setgid((gid_t)pwd->pw_gid);
	initgroups(pwd->pw_name, pwd->pw_gid);
E 56
E 55
E 52
E 21
I 15
D 30
	(void) setuid(pwd->pw_uid);
E 30
I 30
	(void) setuid((uid_t)pwd->pw_uid);
E 30
E 15
	environ = envinit;
	strncat(homedir, pwd->pw_dir, sizeof(homedir)-6);
I 70
	strcat(path, _PATH_DEFPATH);
E 70
	strncat(shell, pwd->pw_shell, sizeof(shell)-7);
	strncat(username, pwd->pw_name, sizeof(username)-6);
D 77
	cp = rindex(pwd->pw_shell, '/');
E 77
I 77
	cp = strrchr(pwd->pw_shell, '/');
E 77
	if (cp)
		cp++;
	else
		cp = pwd->pw_shell;
I 57
	endpwent();
	if (pwd->pw_uid == 0)
		syslog(LOG_INFO|LOG_AUTH, "ROOT shell from %s@%s, comm: %s\n",
		    remuser, hostname, cmdbuf);
E 57
I 53
	endpwent();
D 54
	if (!pwd->pw_uid)
		syslog(LOG_NOTICE, "ROOT shell from %s@%s, comm: %s\n",
			remuser, hostname, cmdbuf);
E 54
I 54
D 56
	if (!pwd->pw_uid) {
E 56
I 56
D 72
	if (pwd->pw_uid == 0) {
E 72
I 72
	if (log_success || pwd->pw_uid == 0) {
E 72
E 56
#ifdef	KERBEROS
		if (use_kerberos)
D 56
			syslog(LOG_NOTICE|LOG_AUTH,
E 56
I 56
D 72
			syslog(LOG_INFO|LOG_AUTH,
E 56
				"ROOT Kerberos shell from %s.%s@%s on %s, comm: %s\n",
				kdata->pname, kdata->pinst, kdata->prealm,
				hostname, cmdbuf);
E 72
I 72
		    syslog(LOG_INFO|LOG_AUTH,
			"Kerberos shell from %s.%s@%s on %s as %s, cmd='%.80s'",
			kdata->pname, kdata->pinst, kdata->prealm,
			hostname, locuser, cmdbuf);
E 72
		else
#endif
D 56
			syslog(LOG_NOTICE|LOG_AUTH,
E 56
I 56
D 72
			syslog(LOG_INFO|LOG_AUTH,
E 56
				"ROOT shell from %s@%s, comm: %s\n",
				remuser, hostname, cmdbuf);
E 72
I 72
		    syslog(LOG_INFO|LOG_AUTH, "%s@%s as %s: cmd='%.80s'",
			remuser, hostname, locuser, cmdbuf);
E 72
	}
E 54
E 53
	execl(pwd->pw_shell, cp, "-c", cmdbuf, 0);
	perror(pwd->pw_shell);
	exit(1);
D 30
protofail:
	error("rsh: protocol failure detected by remote\n");
	exit(1);
E 30
}

I 57
/*
 * Report error to client.
 * Note: can't be used until second socket has connected
 * to client, or older clients will hang waiting
 * for that connection first.
 */
E 57
I 56
/*
D 72
 * Report error to client.
 * Note: can't be used until second socket has connected
 * to client, or older clients will hang waiting
 * for that connection first.
E 72
I 72
 * Report error to client.  Note: can't be used until second socket has
 * connected to client, or older clients will hang waiting for that
 * connection first.
E 72
 */
E 56
D 30
/* VARARGS 1 */
E 30
I 30
D 72
/*VARARGS1*/
E 30
D 28
error(fmt)
E 28
I 28
error(fmt, a1, a2, a3)
E 72
I 72
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
error(const char *fmt, ...)
#else
error(fmt, va_alist)
E 72
E 28
	char *fmt;
I 28
D 72
	int a1, a2, a3;
E 72
I 72
        va_dcl
#endif
E 72
E 28
{
D 56
D 57
	char buf[BUFSIZ];
E 57
I 57
	char buf[BUFSIZ], *bp = buf;
E 57
E 56
I 56
D 72
	char buf[BUFSIZ], *bp = buf;
E 56

D 56
D 57
	buf[0] = 1;
D 28
	(void) sprintf(buf+1, fmt);
E 28
I 28
	(void) sprintf(buf+1, fmt, a1, a2, a3);
E 57
I 57
	if (sent_null == 0)
		*bp++ = 1;
	(void) sprintf(bp, fmt, a1, a2, a3);
E 57
E 56
I 56
	if (sent_null == 0)
E 72
I 72
	va_list ap;
	int len;
	char *bp, buf[BUFSIZ];
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	bp = buf;
	if (sent_null == 0) {
E 72
		*bp++ = 1;
D 72
	(void) sprintf(bp, fmt, a1, a2, a3);
E 56
E 28
	(void) write(2, buf, strlen(buf));
E 72
I 72
		len = 1;
	} else
		len = 0;
D 75
	len += vsnprintf(bp, sizeof(buf) - 1, fmt, ap);
	(void)write(STDERR_FILENO, buf, len);
E 75
I 75
	(void)vsnprintf(bp, sizeof(buf) - 1, fmt, ap);
	(void)write(STDERR_FILENO, buf, len + strlen(bp));
E 75
E 72
}

I 72
void
E 72
getstr(buf, cnt, err)
D 72
	char *buf;
E 72
I 72
	char *buf, *err;
E 72
	int cnt;
D 72
	char *err;
E 72
{
	char c;

	do {
D 73
		if (read(0, &c, 1) != 1)
E 73
I 73
		if (read(STDIN_FILENO, &c, 1) != 1)
E 73
			exit(1);
		*buf++ = c;
		if (--cnt == 0) {
			error("%s too long\n", err);
			exit(1);
		}
	} while (c != 0);
I 38
}

D 41
int
same_domain(h1, h2)
	register char	*h1, *h2;
E 41
I 41
/*
 * Check whether host h is in our local domain,
D 56
D 57
 * as determined by the part of the name following
 * the first '.' in its name and in ours.
E 57
I 57
 * defined as sharing the last two components of the domain part,
 * or the entire domain part if the local domain has only one component.
E 57
E 56
I 56
 * defined as sharing the last two components of the domain part,
 * or the entire domain part if the local domain has only one component.
E 56
 * If either name is unqualified (contains no '.'),
 * assume that the host is local, as it will be
 * interpreted as such.
 */
I 72
int
E 72
local_domain(h)
	char *h;
E 41
{
D 41
	register char *p1 = index(h1, '.');
	register char *p2 = index(h2, '.');
	if(!strcasecmp(p1, p2))
E 41
I 41
	char localhost[MAXHOSTNAMELEN];
D 56
D 57
	char *p1, *p2 = index(h, '.');
E 57
I 57
	char *p1, *p2, *topdomain();
E 57
E 56
I 56
D 72
	char *p1, *p2, *topdomain();
E 72
I 72
	char *p1, *p2;
E 72
E 56

I 57
	localhost[0] = 0;
E 57
I 56
	localhost[0] = 0;
E 56
	(void) gethostname(localhost, sizeof(localhost));
D 56
D 57
	p1 = index(localhost, '.');
E 57
I 57
	p1 = topdomain(localhost);
	p2 = topdomain(h);
E 57
E 56
I 56
	p1 = topdomain(localhost);
	p2 = topdomain(h);
E 56
	if (p1 == NULL || p2 == NULL || !strcasecmp(p1, p2))
E 41
D 72
		return(1);
	return(0);
E 72
I 72
		return (1);
	return (0);
E 72
I 57
}

char *
topdomain(h)
	char *h;
{
	register char *p;
	char *maybe = NULL;
	int dots = 0;

	for (p = h + strlen(h); p >= h; p--) {
		if (*p == '.') {
			if (++dots == 2)
				return (p);
			maybe = p;
		}
	}
	return (maybe);
E 57
I 50
}

I 56
char *
topdomain(h)
	char *h;
{
D 77
	register char *p;
	char *maybe = NULL;
E 77
I 77
	char *p, *maybe = NULL;
E 77
	int dots = 0;

	for (p = h + strlen(h); p >= h; p--) {
		if (*p == '.') {
			if (++dots == 2)
				return (p);
			maybe = p;
		}
	}
	return (maybe);
}

I 72
void
E 72
E 56
usage()
{
I 77

E 77
D 63
#ifdef	KERBEROS
I 55
D 56
#if	BSD > 43
E 55
D 53
	syslog(LOG_ERR, "usage: rshd [-l] [-n]");
E 53
I 53
	syslog(LOG_ERR, "usage: rshd [-ln]");
E 56
I 56
	syslog(LOG_ERR, "usage: rshd [-aln]");
E 56
E 53
#else
I 55
D 56
	syslog(LOG_ERR, "usage: rshd [-n]");
#endif
#else
#if	BSD > 43
E 55
D 53
	syslog(LOG_ERR, "usage: rshd [-l] [-n] [-k] [-v] [-e]");
E 53
I 53
	syslog(LOG_ERR, "usage: rshd [-lknvx]");
I 55
#else
	syslog(LOG_ERR, "usage: rshd [-knvx]");
#endif
E 56
I 56
	syslog(LOG_ERR, "usage: rshd [-alknvx]");
E 56
E 55
E 53
#endif
E 63
I 63
	syslog(LOG_ERR, "usage: rshd [-%s]", OPTIONS);
I 77
	exit(2);
E 77
E 63
E 50
E 38
}
E 1
