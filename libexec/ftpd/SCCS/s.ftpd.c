h64121
s 00001/00001/01627
d D 8.5 95/04/28 09:31:42 bostic 88 87
c the checkuser() function compared p against name, but p points to
c the end of the line, not the beginning.
c From: "J.T. Conklin" <jtc@NetBSD.ORG>
e
s 00004/00002/01624
d D 8.4 94/04/16 15:47:08 bostic 87 86
c "bare linefeed's code should match 226
c See RFC959 starting around the bottom of page 35.
c From: sms@WLV.IIPO.GTEGSC.COM (Steven M. Schultz)
e
s 00002/00001/01624
d D 8.3 94/04/06 11:04:21 pendry 86 85
c fix globbing - need NOCHECK flag
e
s 00124/00114/01501
d D 8.2 94/04/04 12:36:00 pendry 85 84
c eliminate local version of glob (cf ftp)
c clean up yacc grammar.  prettiness police.
e
s 00005/00005/01610
d D 8.1 93/06/04 18:48:33 bostic 84 83
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/01609
d D 5.44 93/05/17 10:10:04 bostic 83 82
c index, rindex -> strchr, strrchr
e
s 00000/00002/01615
d D 5.43 92/10/01 22:17:13 bostic 82 81
c fix prototypes for gcc 2.2.2
e
s 00261/00087/01356
d D 5.42 92/07/15 11:54:18 andrew 81 80
c new features:  extend logging to show i/o operations,
c display pre- and post-login messages; add prototyping, misc. bug fixes
e
s 00008/00012/01435
d D 5.41 92/03/18 15:11:22 bostic 80 79
c Don't log user passwords when debug is turned on with -d.
c Set "home" to "/" when logging in as a guest.
c Don't syslog() trailing CR-LF when using -d.
c Don't timestamp connect message, syslog() already does that.
c Don't timestamp timeout message, syslog() already does that.
c Minor whitespace cleanups.
c from Craig Leres (leres@ee.lbl.gov)
e
s 00002/00002/01445
d D 5.40 91/07/02 17:35:43 karels 79 78
c hack to avoid kernel problem
e
s 00014/00012/01433
d D 5.39 91/02/25 16:46:20 bostic 78 77
c ANSI fixes, struct direct -> struct dirent, rename glob() -> ftpglob()
e
s 00005/00001/01440
d D 5.38 90/08/07 13:47:08 karels 77 76
c use LOG_NDELAY, move openlog before all syslog's
e
s 00022/00005/01419
d D 5.37 90/06/27 18:04:39 karels 76 75
c set IP type-of-service
e
s 00001/00011/01423
d D 5.36 90/06/01 15:52:30 bostic 75 74
c new copyright notice
e
s 00002/00008/01432
d D 5.35 90/05/28 12:39:47 bostic 74 73
c sys_errlist -> strerror(3)
e
s 00019/00019/01421
d D 5.34 90/05/24 21:12:26 bostic 73 72
c handle comments in ftpusers correctly
e
s 00001/00001/01439
d D 5.33 90/05/15 19:49:52 bostic 72 71
c string.h is ANSI C include file
e
s 00024/00021/01416
d D 5.32 90/02/20 21:26:41 mckusick 71 70
c have to put back the checkuser subroutine
e
s 00005/00003/01432
d D 5.31 90/02/19 11:10:29 mckusick 70 69
c check /etc/ftpusers for denial of access to anonymous (4.3BSD-tahoe/libexec/1)
e
s 00006/00003/01429
d D 5.30 89/05/28 20:44:24 rick 69 68
c in new code for NLST, forgot to send \r\n in ASCII mode instead
c of just \n
e
s 00012/00005/01420
d D 5.29 89/05/26 13:11:49 rick 68 67
c add some missing fclose() in error cases; check for bare \n
c received in ASCII mode and print warning; correct test in status() code
c so ip address is printed as well as hostname
e
s 00023/00015/01402
d D 5.28 89/04/20 10:31:10 karels 67 65
c retry data connection (SO_REUSEADDR isn't enough); show directories
c in NLST unless globbing (a botch, but too incompatible otherwise); bostic's
c pathname changes
e
s 00000/00050/01367
d D 5.27.1.1 89/03/02 09:38:38 karels 66 65
c remove restart for network release
e
s 00302/00098/01115
d D 5.27 89/02/28 12:10:01 karels 65 64
c lots of changes, mostly from Rick Adams: implement restart, stat,
c site (from Dave Borman), size, mdtm; pointer fixes for cray; more cleanups;
c proctitle stuff
e
s 00276/00102/00937
d D 5.26 89/01/25 14:43:46 rick 64 63
c add support for REST (restart at arbitrary byte position) SYST (system
c type); fix chroot bug; add setproctitle (#ifdef'd); clean up 400/500
c return codes; make NLST/LIST RFC conformant
e
s 00004/00003/01035
d D 5.25 89/01/16 12:03:11 bostic 63 62
c don't print 0 bytes for ls commands
e
s 00024/00009/01014
d D 5.24 89/01/15 15:15:41 bostic 62 61
c add SYST (sys type), REST (restart); null deref; from Rick Adams
e
s 00011/00002/01012
d D 5.23 89/01/15 14:09:30 bostic 61 60
c syslog logins, both successful(??) and unsuccessful
e
s 00052/00058/00962
d D 5.22 88/12/19 16:35:02 bostic 60 59
c if no home directory, log into '/'; delete old #ifdef/notdef and
c commented out stuff; allocate block for binary transfer, based on st_blksize;
c redo reply/lreply as taking multiple arguments -- this should be ripped out
c at some point and made to use varargs/vsyslog.
e
s 00011/00016/01009
d D 5.21 88/12/16 17:10:03 bostic 59 58
c use varargs; lreply only used once, so just handle that one case
e
s 00228/00181/00797
d D 5.20 88/12/07 11:35:44 karels 58 57
c fix user/pass to reset all on failure (*don't* leave failed anonymous
c login as root!), limit login attempts, sleep after failures to slow down
c guessing, correct telnet option processing, various cleanups
e
s 00020/00022/00958
d D 5.19 88/11/30 20:25:38 bostic 57 56
c Rick Adams for Bill Scherlis, the night that MilNet died
e
s 00004/00004/00976
d D 5.18 88/11/18 12:11:54 karels 56 55
c make mode more prominent
e
s 00011/00017/00969
d D 5.17 88/11/01 10:52:06 bostic 55 54
c cleanup logwtmp stuff, stupid mistakes
e
s 00067/00037/00919
d D 5.16 88/10/30 14:07:41 bostic 54 53
c security problem with user; bug report 4.3BSD/ucb/251
e
s 00004/00006/00952
d D 5.15 88/09/22 18:37:42 bostic 53 52
c print ascii/binary mode for connection, not address and port #
e
s 00002/00002/00956
d D 5.14 88/09/22 17:07:37 bostic 52 51
c fix for ANSI C; cast return of signal before compare with int
e
s 00005/00147/00953
d D 5.13 88/09/22 15:02:27 bostic 51 50
c break out logwtmp and popen into separate modules
e
s 00010/00005/01090
d D 5.12 88/06/18 13:46:50 bostic 50 49
c install approved copyright notice
e
s 00011/00005/01084
d D 5.11 88/03/14 17:27:50 bostic 49 48
c add Berkeley specific header
e
s 00006/00008/01083
d D 5.10 87/09/04 17:56:29 mckusick 48 47
c fix bogus use of varags (4.3BSD/etc/90)
e
s 00001/00000/01090
d D 5.9 87/04/23 11:39:21 csvsj 47 46
c freoprn stderr to /dev/null to prevent ls() 'file not found' messages
e
s 00002/00001/01088
d D 5.8 86/11/18 20:44:27 bostic 46 45
c FTPD refuses to let /bin/sh users log in; bug report 4.3BSD/etc/19
e
s 00016/00003/01073
d D 5.7 86/05/28 15:24:17 mckusick 45 44
c also require user to have a standard shell
e
s 00022/00043/01054
d D 5.6 86/05/06 21:23:16 minshall 44 43
c Use SO_OOBINLINE for TCP urgent data. 
c Don't send 150 response unless data connection successful for data transfers. 
c Correctly filter \r\r\n during ascii receives. (all from Steve Jacobson)
e
s 00021/00037/01076
d D 5.5 86/04/16 17:37:20 mckusick 43 41
c standardize the reply codes (from mcvax!dpk@seismo.CSS.GOV)
e
s 00001/00001/01112
d R 5.5 86/04/03 13:38:28 mckusick 42 41
c command code 200 does not exist, should be code 250 (from torek)
e
s 00077/00079/01036
d D 5.4 86/03/07 12:01:22 minshall 41 40
c Clean up for lint; add syslog.
e
s 00017/00032/01098
d D 5.3 86/02/18 13:54:40 sam 40 39
c cleanup oob code; recv takes char *, SIOCATMARK takes int; geez!!!!
e
s 00282/00032/00848
d D 5.2 86/02/03 14:32:16 minshall 39 38
c Steve Jacobson's changes (from <csvsj@ucbopal>).
e
s 00014/00002/00866
d D 5.1 85/06/06 11:09:28 dist 38 37
c Add copyright
e
s 00010/00005/00858
d D 4.35 85/06/04 21:46:37 sam 37 36
c force glob failure to result in original string being used (from 
c bug report -- sorry whoever you are)
e
s 00001/00001/00862
d D 4.34 85/02/24 11:57:04 bloom 36 35
c fix printf format
e
s 00011/00011/00852
d D 4.33 84/12/23 16:43:04 sam 35 34
c always exit in dologout; from brl
e
s 00002/00002/00861
d D 4.32 84/09/04 21:43:01 sam 34 33
c convert setsockopt call to new interface
e
s 00014/00011/00849
d D 4.31 84/07/25 02:41:08 lepreau 33 32
c fix wtmp logging: no anonymous logout record; null hostname.
c disallow null passwords yet again.
e
s 00037/00082/00823
d D 4.30 84/04/11 14:55:28 karels 32 31
c convert for inetd
e
s 00015/00006/00890
d D 4.29 84/02/10 15:27:09 ralph 31 30
c log anonymous logins in wtmp properly.
e
s 00001/00001/00895
d D 4.28 83/09/22 22:23:15 sam 30 29
c disallow null passwords (geez I fixed this long ago, where'd it go?)
e
s 00001/00001/00895
d D 4.27 83/08/23 11:34:56 karels 29 28
c if !logged_in, going to loop indefinitely
e
s 00002/00001/00894
d D 4.26 83/08/09 20:11:51 sam 28 27
c if data is buffered when a SIGPIPE arrives, can loop on signals
e
s 00003/00001/00892
d D 4.25 83/07/24 13:19:08 sam 27 26
c don't reply when connection breaks, noone to send to
e
s 00001/00001/00892
d D 4.24 83/07/01 23:57:27 sam 26 25
c include fix
e
s 00070/00038/00823
d D 4.23 83/06/22 14:33:20 sam 25 24
c do wtmp logging and cleanup some stuff
e
s 00021/00015/00840
d D 4.22 83/06/19 23:06:40 root 24 23
c fix glob one more time (can't fix all since glob done in ftpcmd.y)
e
s 00007/00011/00848
d D 4.21 83/06/15 15:19:58 sam 23 22
c fix for multi-homing problem; glob done wrong
e
s 00015/00004/00844
d D 4.20 83/06/12 02:45:04 sam 22 21
c new signals == no libjobs
e
s 00019/00004/00829
d D 4.19 83/03/29 11:25:05 sam 21 20
c from jsq@utexas-11 (mls, mdir and random cleanups after me)
e
s 00039/00044/00794
d D 4.18 83/03/23 10:27:12 sam 20 19
c merge of changes from jsq@utexas-11
e
s 00001/00001/00837
d D 4.17 83/02/28 23:44:26 sam 19 18
c formatting
e
s 00023/00020/00815
d D 4.16 83/02/21 19:38:28 sam 18 17
c fixes from texas
e
s 00122/00000/00713
d D 4.15 83/02/02 16:25:13 sam 17 16
c 2 holes: disallow |'s in ls and dir; 2nd, provide forbidden user list
e
s 00003/00006/00710
d D 4.14 83/01/24 02:11:07 sam 16 15
c pretty dumb stuff -- better to use fileno directly
e
s 00014/00023/00702
d D 4.13 83/01/23 13:34:13 sam 15 14
c hack for address binding + rearrange replys for sanity
e
s 00001/00001/00724
d D 4.12 83/01/22 16:12:48 sam 14 13
c SIGCHLD reset on each occurance
e
s 00001/00007/00724
d D 4.11 83/01/21 22:05:51 sam 13 12
c follow spec dummy
e
s 00001/00000/00730
d D 4.10 83/01/19 12:41:44 sam 12 11
c forgot errno.h, who wrote this code anyway?
e
s 00011/00012/00719
d D 4.9 83/01/19 12:32:15 sam 11 10
c rearrange stuff so printfs look right
e
s 00019/00004/00712
d D 4.8 83/01/18 20:24:54 sam 10 8
c put back debugging and reap children so no zombies
e
s 00016/00003/00713
d R 4.8 83/01/18 20:22:52 sam 9 8
c put back debugging and reap child so no zombies
e
s 00001/00001/00715
d D 4.7 83/01/16 13:16:29 sam 8 7
c oops
e
s 00013/00002/00703
d D 4.6 83/01/16 12:32:48 sam 7 5
c use default port on data transfers when no PORT is specified
e
s 00012/00001/00704
d R 4.6 83/01/16 12:29:28 sam 6 5
c insure default address used even if some transfers supply PORT
e
s 00009/00003/00696
d D 4.5 83/01/16 11:53:17 sam 5 4
c disallow remote command execution, lest someone become root 
c through it by executing a setuid program while using the server
e
s 00002/00002/00697
d D 4.4 83/01/15 21:29:52 sam 4 3
c screwed up reseting effective uid after acquiring socket
e
s 00001/00001/00698
d D 4.3 83/01/15 17:02:40 sam 3 2
c leave stderr open only when debugging
e
s 00069/00026/00630
d D 4.2 83/01/15 17:00:29 sam 2 1
c handle globbing problems; make sure new files are owned 
c by the user; fix problem with rename; lots more (check delta)
e
s 00656/00000/00000
d D 4.1 83/01/13 23:57:01 sam 1 0
c date and time created 83/01/13 23:57:01 by sam
e
u
U
f b 
t
T
I 38
/*
D 39
 * Copyright (c) 1983 Regents of the University of California.
E 39
I 39
D 58
 * Copyright (c) 1985 Regents of the University of California.
E 58
I 58
D 76
 * Copyright (c) 1985, 1988 Regents of the University of California.
E 76
I 76
D 81
 * Copyright (c) 1985, 1988, 1990 Regents of the University of California.
E 81
I 81
D 84
 * Copyright (c) 1985, 1988, 1990, 1992 Regents of the University of California.
E 81
E 76
E 58
E 39
D 49
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 49
I 49
 * All rights reserved.
E 84
I 84
D 85
 * Copyright (c) 1985, 1988, 1990, 1992, 1993
E 85
I 85
 * Copyright (c) 1985, 1988, 1990, 1992, 1993, 1994
E 85
 *	The Regents of the University of California.  All rights reserved.
E 84
 *
D 75
 * Redistribution and use in source and binary forms are permitted
D 50
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 50
I 50
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
D 65
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 65
I 65
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 75
I 75
 * %sccs.include.redist.c%
E 75
E 65
E 50
E 49
 */

E 38
I 1
#ifndef lint
D 11
static char sccsid[] = "%W% (Berkeley) %E%";
E 11
I 11
D 32
static char sccsid[] = "%W% (Berkeley) %G%";
E 32
I 32
D 38
static	char sccsid[] = "%W% (Berkeley) %G%";
E 32
E 11
#endif
E 38
I 38
D 84
char copyright[] =
D 39
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 39
I 39
D 49
"@(#) Copyright (c) 1985 Regents of the University of California.\n\
E 49
I 49
D 58
"%Z% Copyright (c) 1985 Regents of the University of California.\n\
E 58
I 58
D 64
"%Z% Copyright (c) 1985, 1988 Regents of the University of California.\n\
E 64
I 64
D 76
"@(#) Copyright (c) 1985, 1988 Regents of the University of California.\n\
E 76
I 76
D 81
"@(#) Copyright (c) 1985, 1988, 1990 Regents of the University of California.\n\
E 81
I 81
"@(#) Copyright (c) 1985, 1988, 1990, 1992 Regents of the University of California.\n\
E 81
E 76
E 64
E 58
E 49
E 39
 All rights reserved.\n";
E 84
I 84
static char copyright[] =
D 85
"%Z% Copyright (c) 1985, 1988, 1990, 1992, 1993\n\
E 85
I 85
"%Z% Copyright (c) 1985, 1988, 1990, 1992, 1993, 1994\n\
E 85
	The Regents of the University of California.  All rights reserved.\n";
E 84
D 49
#endif not lint
E 49
I 49
#endif /* not lint */
E 49

#ifndef lint
D 64
static char sccsid[] = "%W% (Berkeley) %G%";
E 64
I 64
D 76
static char sccsid[] = "%W%	(Berkeley) %G%";
E 76
I 76
static char sccsid[] = "%W% (Berkeley) %G%";
E 76
E 64
D 49
#endif not lint
E 49
I 49
#endif /* not lint */
E 49
E 38

/*
 * FTP server.
 */
D 2
#include <sys/types.h>
E 2
I 2
#include <sys/param.h>
E 2
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
I 25
D 78
#include <sys/file.h>
E 78
I 26
#include <sys/wait.h>
I 64
D 78
#include <sys/dir.h>
E 78
E 64
E 26
E 25

#include <netinet/in.h>
I 76
#include <netinet/in_systm.h>
#include <netinet/ip.h>
E 76

I 65
#define	FTP_NAMES
E 65
I 22
#include <arpa/ftp.h>
I 24
#include <arpa/inet.h>
I 39
#include <arpa/telnet.h>
E 39
E 24

I 65
D 78
#include <ctype.h>
E 65
E 22
#include <stdio.h>
E 78
D 85
#include <signal.h>
E 85
I 85
#include <ctype.h>
E 85
I 78
#include <dirent.h>
I 85
#include <err.h>
#include <errno.h>
E 85
#include <fcntl.h>
D 85
#include <time.h>
E 85
I 85
#include <glob.h>
#include <limits.h>
#include <netdb.h>
E 85
E 78
D 26
#include <wait.h>
E 26
#include <pwd.h>
#include <setjmp.h>
D 85
#include <netdb.h>
I 12
#include <errno.h>
I 39
D 72
#include <strings.h>
E 72
I 72
D 78
#include <string.h>
E 78
E 72
I 41
#include <syslog.h>
I 59
D 81
#include <varargs.h>
E 81
I 78
#include <unistd.h>
E 85
I 85
#include <signal.h>
E 85
#include <stdio.h>
D 85
#include <ctype.h>
E 85
#include <stdlib.h>
#include <string.h>
I 85
#include <syslog.h>
#include <time.h>
#include <unistd.h>

E 85
E 78
I 67
#include "pathnames.h"
I 81
#include "extern.h"
E 81
E 67
E 59
E 41
E 39
E 12

D 22
#include "ftp.h"

E 22
I 17
D 81
/*
 * File containing login names
 * NOT to be used on this machine.
 * Commonly used to disallow uucp.
 */
D 67
#define	FTPUSERS	"/etc/ftpusers"

E 67
E 17
extern	int errno;
D 74
extern	char *sys_errlist[];
I 58
extern	int sys_nerr;
E 74
E 58
extern	char *crypt();
extern	char version[];
E 81
I 81
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

I 85
static char version[] = "Version 6.00";

E 85
extern	off_t restart_point;
E 81
D 85
extern	char *home;		/* pointer to home directory for glob */
E 85
D 39
extern	FILE *popen(), *fopen();
E 39
I 39
D 57
extern	FILE *popen(), *fopen(), *freopen();
E 57
I 57
D 81
extern	FILE *ftpd_popen(), *fopen(), *freopen();
E 57
E 39
D 41
extern	int pclose(), fclose();
E 41
I 41
D 58
extern	int  pclose(), fclose();
E 58
I 58
extern	int  ftpd_pclose(), fclose();
E 58
E 41
I 39
extern	char *getline();
E 81
extern	char cbuf[];
I 62
D 66
D 81
extern	off_t restart_point;
E 81
I 81
D 85
extern	char version[];
E 85
E 81
E 66
E 62
E 39

struct	sockaddr_in ctrl_addr;
struct	sockaddr_in data_source;
struct	sockaddr_in data_dest;
struct	sockaddr_in his_addr;
I 65
struct	sockaddr_in pasv_addr;
E 65

D 41
struct	hostent *hp;

E 41
int	data;
D 39
jmp_buf	errcatch;
E 39
I 39
jmp_buf	errcatch, urgcatch;
E 39
int	logged_in;
struct	passwd *pw;
int	debug;
I 20
D 41
int	timeout;
E 41
I 41
int	timeout = 900;    /* timeout after 15 minutes of inactivity */
I 65
int	maxtimeout = 7200;/* don't allow idle time to be set beyond 2 hours */
E 65
E 41
E 20
D 21
int	logging = 1;
E 21
I 21
int	logging;
E 21
int	guest;
I 31
D 55
int	wtmp;
E 55
E 31
int	type;
int	form;
int	stru;			/* avoid C keyword */
int	mode;
I 7
int	usedefault = 1;		/* for data transfers */
I 39
D 58
int	pdata;			/* for passive mode */
int	unique;
E 58
I 58
int	pdata = -1;		/* for passive mode */
E 58
D 85
int	transflag;
E 85
I 85
sig_atomic_t transflag;
E 85
I 65
off_t	file_size;
off_t	byte_count;
#if !defined(CMASK) || CMASK == 0
#undef CMASK
#define CMASK 027
#endif
int	defumask = CMASK;		/* default umask value */
E 65
char	tmpline[7];
E 39
E 7
D 57
char	hostname[32];
D 25
char	*remotehost;
E 25
I 25
char	remotehost[32];
E 57
I 57
char	hostname[MAXHOSTNAMELEN];
char	remotehost[MAXHOSTNAMELEN];
E 57
E 25
I 7
D 32
struct	servent *sp;
E 32
E 7

I 20
/*
 * Timeout intervals for retrying connections
 * to hosts that don't accept PORT cmds.  This
 * is a kludge, but given the problems with TCP...
 */
#define	SWAITMAX	90	/* wait at most 90 seconds */
#define	SWAITINT	5	/* interval between retries */

int	swaitmax = SWAITMAX;
int	swaitint = SWAITINT;

E 20
D 78
int	lostconn();
I 10
D 41
int	reapchild();
E 41
I 39
int	myoob();
E 78
I 78
D 81
void	lostconn(), myoob();
E 78
E 39
E 10
FILE	*getdatasock(), *dataconn();
D 25
char	*ntoa();
E 25

E 81
D 64
main(argc, argv)
E 64
I 64
#ifdef SETPROCTITLE
char	**Argv = NULL;		/* pointer to argument vector */
char	*LastArgv = NULL;	/* end of argv */
I 65
D 85
char	proctitle[BUFSIZ];	/* initial part of title */
E 85
I 85
char	proctitle[LINE_MAX];	/* initial part of title */
E 85
E 65
#endif /* SETPROCTITLE */

I 81
D 85
#define MAXLINE         256

E 85
#define LOGCMD(cmd, file) \
	if (logging > 1) \
	    syslog(LOG_INFO,"%s %s%s", cmd, \
		*(file) == '/' ? "" : curdir(), file);
#define LOGCMD2(cmd, file1, file2) \
	 if (logging > 1) \
	    syslog(LOG_INFO,"%s %s%s %s%s", cmd, \
		*(file1) == '/' ? "" : curdir(), file1, \
		*(file2) == '/' ? "" : curdir(), file2);
#define LOGBYTES(cmd, file, cnt) \
	if (logging > 1) { \
		if (cnt == (off_t)-1) \
		    syslog(LOG_INFO,"%s %s%s", cmd, \
			*(file) == '/' ? "" : curdir(), file); \
		else \
		    syslog(LOG_INFO, "%s %s%s = %qd bytes", \
			cmd, (*(file) == '/') ? "" : curdir(), file, cnt); \
	}

static void	 ack __P((char *));
static void	 myoob __P((int));
static int	 checkuser __P((char *));
static FILE	*dataconn __P((char *, off_t, char *));
static void	 dolog __P((struct sockaddr_in *));
static char	*curdir __P((void));
static void	 end_login __P((void));
static FILE	*getdatasock __P((char *));
static char	*gunique __P((char *));
static void	 lostconn __P((int));
D 82
static void	 pass __P((char *));
E 82
static int	 receive_data __P((FILE *, FILE *));
static void	 send_data __P((FILE *, FILE *, off_t));
static struct passwd *
		 sgetpwnam __P((char *));
static char	*sgetsave __P((char *));
D 82
static void	 user __P((char *));
E 82

static char *
curdir()
{
	static char path[MAXPATHLEN+1+1];	/* path + '/' + '\0' */

	if (getcwd(path, sizeof(path)-2) == NULL)
		return ("");
	if (path[1] != '\0')		/* special case for root dir. */
		strcat(path, "/");
	/* For guest account, skip / since it's chrooted */
	return (guest ? path+1 : path);
}

int
E 81
main(argc, argv, envp)
E 64
	int argc;
	char *argv[];
I 64
	char **envp;
E 64
{
D 32
	int ctrl, s, options = 0;
E 32
I 32
D 41
	int options = 0, addrlen;
E 41
I 41
D 44
	int addrlen;
E 44
I 44
D 76
	int addrlen, on = 1;
E 76
I 76
D 85
	int addrlen, on = 1, tos;
E 76
E 44
E 41
I 39
D 58
	long pgid;
E 58
E 39
E 32
D 7
	struct servent *sp;
E 7
D 10
	union wait status;
E 10
D 81
	char *cp;
E 81
I 81
	char *cp, line[MAXLINE];
E 85
I 85
	int addrlen, ch, on = 1, tos;
	char *cp, line[LINE_MAX];
E 85
	FILE *fd;
E 81

I 77
	/*
	 * LOG_NDELAY sets up the logging connection immediately,
	 * necessary for anonymous ftp's that chroot and can't do it later.
	 */
D 81
	openlog("ftpd", LOG_PID | LOG_NDELAY, LOG_DAEMON);
E 81
I 81
	openlog("ftpd", LOG_PID | LOG_NDELAY, LOG_FTP);
E 81
E 77
D 32
	sp = getservbyname("ftp", "tcp");
	if (sp == 0) {
D 18
		fprintf(stderr, "ftpd: fpt/tcp: unknown service\n");
E 18
I 18
		fprintf(stderr, "ftpd: ftp/tcp: unknown service\n");
E 32
I 32
D 85
	addrlen = sizeof (his_addr);
E 85
I 85
	addrlen = sizeof(his_addr);
E 85
D 58
	if (getpeername(0, &his_addr, &addrlen) < 0) {
E 58
I 58
	if (getpeername(0, (struct sockaddr *)&his_addr, &addrlen) < 0) {
E 58
D 41
		fprintf(stderr, "%s: ", argv[0]);
		perror("getpeername");
E 41
I 41
		syslog(LOG_ERR, "getpeername (%s): %m",argv[0]);
E 41
E 32
E 18
		exit(1);
	}
D 32
	ctrl_addr.sin_port = sp->s_port;
	data_source.sin_port = htons(ntohs(sp->s_port) - 1);
	signal(SIGPIPE, lostconn);
E 32
I 32
D 85
	addrlen = sizeof (ctrl_addr);
E 85
I 85
	addrlen = sizeof(ctrl_addr);
E 85
D 41
	if (getsockname(0, &ctrl_addr, &addrlen) < 0) {
		fprintf(stderr, "%s: ", argv[0]);
		perror("getsockname");
E 41
I 41
D 58
	if (getsockname(0, (char *) &ctrl_addr, &addrlen) < 0) {
E 58
I 58
	if (getsockname(0, (struct sockaddr *)&ctrl_addr, &addrlen) < 0) {
E 58
		syslog(LOG_ERR, "getsockname (%s): %m",argv[0]);
E 41
		exit(1);
	}
I 76
#ifdef IP_TOS
	tos = IPTOS_LOWDELAY;
	if (setsockopt(0, IPPROTO_IP, IP_TOS, (char *)&tos, sizeof(int)) < 0)
		syslog(LOG_WARNING, "setsockopt (IP_TOS): %m");
#endif
E 76
	data_source.sin_port = htons(ntohs(ctrl_addr.sin_port) - 1);
E 32
	debug = 0;
I 41
D 77
	openlog("ftpd", LOG_PID, LOG_DAEMON);
E 77
I 64
#ifdef SETPROCTITLE
	/*
	 *  Save start and extent of argv for setproctitle.
	 */
	Argv = argv;
	while (*envp)
		envp++;
	LastArgv = envp[-1] + strlen(envp[-1]);
#endif /* SETPROCTITLE */

E 64
E 41
D 85
	argc--, argv++;
	while (argc > 0 && *argv[0] == '-') {
		for (cp = &argv[0][1]; *cp; cp++) switch (*cp) {

I 20
		case 'v':
			debug = 1;
			break;

E 85
I 85
	while ((ch = getopt(argc, argv, "dlt:T:u:v")) != EOF) {
		switch (ch) {
E 85
E 20
		case 'd':
			debug = 1;
D 41
			options |= SO_DEBUG;
E 41
			break;

I 21
		case 'l':
D 81
			logging = 1;
E 81
I 81
			logging++;	/* > 1 == extra logging */
E 81
I 39
D 41
			(void) freopen("/tmp/ftplog", "a", stderr);
E 41
E 39
			break;

E 21
I 20
		case 't':
D 85
			timeout = atoi(++cp);
E 85
I 85
			timeout = atoi(optarg);
E 85
I 65
			if (maxtimeout < timeout)
				maxtimeout = timeout;
E 65
D 85
			goto nextopt;
E 85
I 85
			break;
E 85
D 60
			break;
E 60

I 65
		case 'T':
D 85
			maxtimeout = atoi(++cp);
E 85
I 85
			maxtimeout = atoi(optarg);
E 85
			if (timeout > maxtimeout)
				timeout = maxtimeout;
D 85
			goto nextopt;
E 85
I 85
			break;
E 85

		case 'u':
		    {
D 85
			int val = 0;
E 85
I 85
			long val = 0;
E 85

D 85
			while (*++cp && *cp >= '0' && *cp <= '9')
				val = val*8 + *cp - '0';
			if (*cp)
				fprintf(stderr, "ftpd: Bad value for -u\n");
E 85
I 85
			val = strtol(optarg, &optarg, 8);
			if (*optarg != '\0' || val < 0)
				warnx("bad value for -u");
E 85
			else
				defumask = val;
D 85
			goto nextopt;
E 85
I 85
			break;
E 85
		    }

I 85
		case 'v':
			debug = 1;
			break;

E 85
E 65
E 20
		default:
D 20
			fprintf(stderr, "Unknown flag -%c ignored.\n", cp);
E 20
I 20
D 32
			fprintf(stderr, "Unknown flag -%c ignored.\n", *cp);
E 32
I 32
D 85
			fprintf(stderr, "ftpd: Unknown flag -%c ignored.\n",
			     *cp);
E 85
I 85
			warnx("unknown flag -%c ignored", optopt);
E 85
E 32
E 20
			break;
		}
I 20
D 85
nextopt:
E 20
		argc--, argv++;
E 85
	}
I 47
D 67
	(void) freopen("/dev/null", "w", stderr);
E 67
I 67
	(void) freopen(_PATH_DEVNULL, "w", stderr);
E 67
E 47
D 32
#ifndef DEBUG
	if (fork())
		exit(0);
	for (s = 0; s < 10; s++)
I 20
		if (!logging || (s != 2))
			(void) close(s);
E 20
D 3
		if (s != 2)		/* don't screw stderr */
E 3
I 3
D 5
		if (s != 2 && debug)		/* don't screw stderr */
E 3
			(void) close(s);
E 5
I 5
D 21
		(void) close(s);
E 21
E 5
D 18
	(void) open("/dev/null", 0);
E 18
I 18
D 25
	(void) open("/", 0);
E 25
I 25
	(void) open("/", O_RDONLY);
E 25
E 18
	(void) dup2(0, 1);
I 18
D 20
	(void) dup2(0, 2);
E 20
I 20
	if (!logging)
		(void) dup2(0, 2);
E 20
E 18
D 25
	{ int tt = open("/dev/tty", 2);
E 25
I 25
	{ int tt = open("/dev/tty", O_RDWR);
E 25
	  if (tt > 0) {
		ioctl(tt, TIOCNOTTY, 0);
		close(tt);
	  }
	}
#endif
D 2
	while ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
E 2
I 2
D 25
	while ((s = socket(AF_INET, SOCK_STREAM, 0, 0)) < 0) {
E 25
I 25
	while ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
E 25
E 2
		perror("ftpd: socket");
		sleep(5);
	}
I 10
	if (options & SO_DEBUG)
		if (setsockopt(s, SOL_SOCKET, SO_DEBUG, 0, 0) < 0)
			perror("ftpd: setsockopt (SO_DEBUG)");
D 25
#ifdef notdef
E 25
	if (setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, 0, 0) < 0)
		perror("ftpd: setsockopt (SO_KEEPALIVE)");
D 25
#endif
E 25
E 10
	while (bind(s, &ctrl_addr, sizeof (ctrl_addr), 0) < 0) {
		perror("ftpd: bind");
		sleep(5);
	}
I 10
D 14
	signal(SIGCHLD, reapchild);
E 14
I 14
D 22
	sigset(SIGCHLD, reapchild);
E 22
I 22
	signal(SIGCHLD, reapchild);
E 22
E 14
E 10
I 2
	listen(s, 10);
E 2
	for (;;) {
		int hisaddrlen = sizeof (his_addr);

		ctrl = accept(s, &his_addr, &hisaddrlen, 0);
		if (ctrl < 0) {
I 10
			if (errno == EINTR)
				continue;
E 10
			perror("ftpd: accept");
D 10
			sleep(5);
E 10
			continue;
		}
D 7
		data_dest = his_addr;
E 7
		if (fork() == 0) {
I 18
			signal (SIGCHLD, SIG_IGN);
E 18
D 25
			if (logging)
				dolog(&his_addr);
E 25
I 25
			dolog(&his_addr);
E 25
			close(s);
			dup2(ctrl, 0), close(ctrl), dup2(0, 1);
			/* do telnet option negotiation here */
I 2
			/*
			 * Set up default state
			 */
E 2
			logged_in = 0;
			data = -1;
I 2
			type = TYPE_A;
			form = FORM_N;
			stru = STRU_F;
			mode = MODE_S;
I 23
			(void) getsockname(0, &ctrl_addr, sizeof (ctrl_addr));
E 23
E 2
			gethostname(hostname, sizeof (hostname));
			reply(220, "%s FTP server (%s) ready.",
				hostname, version);
I 22
D 23
			/*
			 * Anchor data source address to that
			 * of the control port so hosts with
			 * multiple address won't have data
			 * connections bound to an address different
			 * than the control port.
			 */
			if (getsockname(0, &ctrl_addr, sizeof (ctrl_addr)) >= 0)
				data_source.sin_addr = ctrl_addr.sin_addr;
E 23
E 22
			for (;;) {
				setjmp(errcatch);
				yyparse();
			}
		}
		close(ctrl);
E 32
I 32
D 41
	signal(SIGPIPE, lostconn);
	signal(SIGCHLD, SIG_IGN);
E 41
I 41
	(void) signal(SIGPIPE, lostconn);
	(void) signal(SIGCHLD, SIG_IGN);
E 41
I 39
D 52
	if (signal(SIGURG, myoob) < 0) {
E 52
I 52
	if ((int)signal(SIGURG, myoob) < 0)
E 52
D 41
		perror("signal");
E 41
I 41
		syslog(LOG_ERR, "signal: %m");
E 41
D 52
	}
E 52
I 52

E 52
I 44
D 68
	/* handle urgent data inline */
I 57
	/* Sequent defines this, but it doesn't work */
E 68
I 68
	/* Try to handle urgent data inline */
E 68
E 57
#ifdef SO_OOBINLINE
D 57
	if (setsockopt(0, SOL_SOCKET, SO_OOBINLINE, (char *)&on, sizeof(on)) < 0) {
E 57
I 57
	if (setsockopt(0, SOL_SOCKET, SO_OOBINLINE, (char *)&on, sizeof(on)) < 0)
E 57
		syslog(LOG_ERR, "setsockopt: %m");
D 57
	}
#endif SO_OOBINLINE
E 57
I 57
#endif
I 68

E 68
I 65
#ifdef	F_SETOWN
E 65
E 57
E 44
D 58
	pgid = getpid();
D 41
	if (ioctl(fileno(stdin), SIOCSPGRP, (char *) &pgid) < 0) {
		perror("ioctl");
E 41
I 41
D 44
	if (ioctl(fileno(stdin), (int) SIOCSPGRP, (char *) &pgid) < 0) {
E 44
I 44
	if (ioctl(fileno(stdin), SIOCSPGRP, (char *) &pgid) < 0) {
E 44
		syslog(LOG_ERR, "ioctl: %m");
E 41
	}
E 58
I 58
	if (fcntl(fileno(stdin), F_SETOWN, getpid()) == -1)
		syslog(LOG_ERR, "fcntl F_SETOWN: %m");
I 65
#endif
E 65
E 58
E 39
I 33
	dolog(&his_addr);
E 33
D 65
	/* do telnet option negotiation here */
E 65
	/*
	 * Set up default state
	 */
D 55
	logged_in = 0;
E 55
	data = -1;
	type = TYPE_A;
	form = FORM_N;
	stru = STRU_F;
	mode = MODE_S;
I 39
	tmpline[0] = '\0';
I 81

	/* If logins are disabled, print out the message. */
	if ((fd = fopen(_PATH_NOLOGIN,"r")) != NULL) {
D 85
		while (fgets(line, sizeof (line), fd) != NULL) {
E 85
I 85
		while (fgets(line, sizeof(line), fd) != NULL) {
E 85
D 83
			if ((cp = index(line, '\n')) != NULL)
E 83
I 83
			if ((cp = strchr(line, '\n')) != NULL)
E 83
				*cp = '\0';
			lreply(530, "%s", line);
		}
		(void) fflush(stdout);
		(void) fclose(fd);
		reply(530, "System not available.");
		exit(0);
	}
	if ((fd = fopen(_PATH_FTPWELCOME, "r")) != NULL) {
D 85
		while (fgets(line, sizeof (line), fd) != NULL) {
E 85
I 85
		while (fgets(line, sizeof(line), fd) != NULL) {
E 85
D 83
			if ((cp = index(line, '\n')) != NULL)
E 83
I 83
			if ((cp = strchr(line, '\n')) != NULL)
E 83
				*cp = '\0';
			lreply(220, "%s", line);
		}
		(void) fflush(stdout);
		(void) fclose(fd);
		/* reply(220,) must follow */
	}
E 81
E 39
D 41
	gethostname(hostname, sizeof (hostname));
E 41
I 41
D 85
	(void) gethostname(hostname, sizeof (hostname));
E 85
I 85
	(void) gethostname(hostname, sizeof(hostname));
E 85
E 41
D 57
	reply(220, "%s FTP server (%s) ready.",
		hostname, version);
E 57
I 57
	reply(220, "%s FTP server (%s) ready.", hostname, version);
E 57
D 58
	for (;;) {
D 41
		setjmp(errcatch);
		yyparse();
E 41
I 41
		(void) setjmp(errcatch);
E 58
I 58
	(void) setjmp(errcatch);
	for (;;)
E 58
		(void) yyparse();
I 64
	/* NOTREACHED */
E 64
E 41
E 32
D 10
		while (wait3(status, WNOHANG, 0) > 0)
			continue;
E 10
D 58
	}
E 58
I 10
}
D 41

E 41
I 41
D 43
/*
E 41
reapchild()
{
	union wait status;
E 43

I 78
D 81
void
E 78
D 43
	while (wait3(&status, WNOHANG, 0) > 0)
		;
E 10
}
I 41
*/
E 41

E 43
lostconn()
E 81
I 81
static void
lostconn(signo)
	int signo;
E 81
{
I 85

E 85
D 78

E 78
D 27
	fatal("Connection closed.");
E 27
I 27
	if (debug)
D 41
		fprintf(stderr, "Lost connection.\n");
E 41
I 41
		syslog(LOG_DEBUG, "lost connection");
E 41
	dologout(-1);
E 27
}

I 51
static char ttyline[20];

I 54
/*
 * Helper function for sgetpwnam().
 */
D 81
char *
E 81
I 81
static char *
E 81
sgetsave(s)
	char *s;
{
D 58
#ifdef notdef
	char *new = strdup(s);
#else
E 58
D 78
	char *malloc();
E 78
	char *new = malloc((unsigned) strlen(s) + 1);
D 58
#endif
E 58
D 65
	
E 65
I 65

E 65
	if (new == NULL) {
D 57
		reply(553, "Local resource failure");
E 57
I 57
D 64
		reply(553, "Local resource failure: malloc");
E 64
I 64
		perror_reply(421, "Local resource failure: malloc");
E 64
E 57
		dologout(1);
I 64
		/* NOTREACHED */
E 64
	}
D 58
#ifndef notdef
E 58
	(void) strcpy(new, s);
D 58
#endif
E 58
	return (new);
}

/*
 * Save the result of a getpwnam.  Used for USER command, since
 * the data returned must not be clobbered by any other command
 * (e.g., globbing).
 */
D 81
struct passwd *
E 81
I 81
static struct passwd *
E 81
sgetpwnam(name)
	char *name;
{
	static struct passwd save;
D 85
	register struct passwd *p;
	char *sgetsave();
E 85
I 85
	struct passwd *p;
E 85

	if ((p = getpwnam(name)) == NULL)
		return (p);
	if (save.pw_name) {
		free(save.pw_name);
		free(save.pw_passwd);
D 65
		free(save.pw_comment);
E 65
		free(save.pw_gecos);
		free(save.pw_dir);
		free(save.pw_shell);
	}
	save = *p;
	save.pw_name = sgetsave(p->pw_name);
	save.pw_passwd = sgetsave(p->pw_passwd);
D 65
	save.pw_comment = sgetsave(p->pw_comment);
E 65
	save.pw_gecos = sgetsave(p->pw_gecos);
	save.pw_dir = sgetsave(p->pw_dir);
	save.pw_shell = sgetsave(p->pw_shell);
	return (&save);
}

I 58
D 81
int login_attempts;		/* number of failed login attempts */
int askpasswd;			/* had user command, ask for passwd */
E 81
I 81
static int login_attempts;	/* number of failed login attempts */
static int askpasswd;		/* had user command, ask for passwd */
static char curname[10];	/* current USER name */
E 81

/*
 * USER command.
D 73
 * Sets global passwd pointer pw if named account exists
 * and is acceptable; sets askpasswd if a PASS command is
 * expected. If logged in previously, need to reset state.
D 70
 * If name is "ftp" or "anonymous" and ftp account exists,
 * set guest and pw, then just return.
E 70
I 70
 * If name is "ftp" or "anonymous", the name is not in /etc/ftpusers,
 * and ftp account exists, set guest and pw, then just return.
E 70
 * If account doesn't exist, ask for passwd anyway.
 * Otherwise, check user requesting login privileges.
 * Disallow anyone who does not have a standard
D 67
 * shell returned by getusershell() (/etc/shells).
 * Disallow anyone mentioned in the file FTPUSERS
E 67
I 67
 * shell as returned by getusershell().
 * Disallow anyone mentioned in the file _PATH_FTPUSERS
E 67
 * to allow people such as root and uucp to be avoided.
E 73
I 73
 * Sets global passwd pointer pw if named account exists and is acceptable;
 * sets askpasswd if a PASS command is expected.  If logged in previously,
 * need to reset state.  If name is "ftp" or "anonymous", the name is not in
 * _PATH_FTPUSERS, and ftp account exists, set guest and pw, then just return.
 * If account doesn't exist, ask for passwd anyway.  Otherwise, check user
 * requesting login privileges.  Disallow anyone who does not have a standard
 * shell as returned by getusershell().  Disallow anyone mentioned in the file
 * _PATH_FTPUSERS to allow people such as root and uucp to be avoided.
E 73
 */
I 81
void
E 81
user(name)
	char *name;
{
D 85
	register char *cp;
D 71
	FILE *fd;
E 71
	char *shell;
E 85
I 85
	char *cp, *shell;
E 85
D 62
	char line[BUFSIZ], *index(), *getusershell();
E 62
I 62
D 71
	char line[BUFSIZ], *getusershell();
E 71
I 71
D 81
	char *getusershell();
E 81
E 71
E 62

	if (logged_in) {
		if (guest) {
			reply(530, "Can't change user from guest login.");
			return;
		}
		end_login();
	}

	guest = 0;
	if (strcmp(name, "ftp") == 0 || strcmp(name, "anonymous") == 0) {
D 70
		if ((pw = sgetpwnam("ftp")) != NULL) {
E 70
I 70
D 71
		if (!checkuser("ftp") || !checkuser("anonymous"))
E 71
I 71
		if (checkuser("ftp") || checkuser("anonymous"))
E 71
			reply(530, "User %s access denied.", name);
		else if ((pw = sgetpwnam("ftp")) != NULL) {
E 70
			guest = 1;
			askpasswd = 1;
D 81
			reply(331, "Guest login ok, send ident as password.");
E 81
I 81
			reply(331,
			    "Guest login ok, type your name as password.");
E 81
D 62
		} else
E 62
I 62
D 65
		}
		else
E 65
I 65
		} else
E 65
E 62
			reply(530, "User %s unknown.", name);
I 81
		if (!askpasswd && logging)
			syslog(LOG_NOTICE,
			    "ANONYMOUS FTP LOGIN REFUSED FROM %s", remotehost);
E 81
		return;
	}
	if (pw = sgetpwnam(name)) {
		if ((shell = pw->pw_shell) == NULL || *shell == 0)
D 67
			shell = "/bin/sh";
E 67
I 67
			shell = _PATH_BSHELL;
E 67
		while ((cp = getusershell()) != NULL)
			if (strcmp(cp, shell) == 0)
				break;
		endusershell();
I 81

E 81
D 71
		if (cp == NULL) {
E 71
I 71
		if (cp == NULL || checkuser(name)) {
E 71
			reply(530, "User %s access denied.", name);
I 61
D 65
			syslog(LOG_ERR, "FTP LOGIN REFUSED FROM %s, %s",
			    remotehost, name);
E 65
I 65
			if (logging)
				syslog(LOG_NOTICE,
				    "FTP LOGIN REFUSED FROM %s, %s",
				    remotehost, name);
E 65
E 61
			pw = (struct passwd *) NULL;
			return;
		}
D 67
		if ((fd = fopen(FTPUSERS, "r")) != NULL) {
E 67
I 67
D 71
		if ((fd = fopen(_PATH_FTPUSERS, "r")) != NULL) {
E 67
		    while (fgets(line, sizeof (line), fd) != NULL) {
			if ((cp = index(line, '\n')) != NULL)
				*cp = '\0';
			if (strcmp(line, name) == 0) {
				reply(530, "User %s access denied.", name);
I 61
D 65
				syslog(LOG_ERR, "FTP LOGIN REFUSED FROM %s, %s",
				    remotehost, name);
E 65
I 65
				if (logging)
					syslog(LOG_NOTICE,
					    "FTP LOGIN REFUSED FROM %s, %s",
					    remotehost, name);
E 65
E 61
				pw = (struct passwd *) NULL;
I 68
				(void) fclose(fd);
E 68
				return;
			}
		    }
I 68
		    (void) fclose(fd);
E 68
		}
E 71
D 68
		(void) fclose(fd);
E 68
	}
I 81
	if (logging)
		strncpy(curname, name, sizeof(curname)-1);
E 81
	reply(331, "Password required for %s.", name);
	askpasswd = 1;
	/*
	 * Delay before reading passwd after first failed
	 * attempt to slow down passwd-guessing programs.
	 */
	if (login_attempts)
		sleep((unsigned) login_attempts);
I 71
}

/*
 * Check if a user is in the file _PATH_FTPUSERS
 */
I 81
static int
E 81
checkuser(name)
	char *name;
{
D 73
	FILE *fd;
	char line[BUFSIZ], *cp;
E 73
I 73
D 85
	register FILE *fd;
	register char *p;
	char line[BUFSIZ];
E 85
I 85
	FILE *fd;
E 85
I 81
	int found = 0;
I 85
	char *p, line[BUFSIZ];
E 85
E 81
E 73

	if ((fd = fopen(_PATH_FTPUSERS, "r")) != NULL) {
D 73
		while (fgets(line, sizeof (line), fd) != NULL) {
			if ((cp = index(line, '\n')) != NULL)
				*cp = '\0';
			if (strcmp(line, name) == 0)
				return (1);
		}
E 73
I 73
		while (fgets(line, sizeof(line), fd) != NULL)
D 83
			if ((p = index(line, '\n')) != NULL) {
E 83
I 83
			if ((p = strchr(line, '\n')) != NULL) {
E 83
				*p = '\0';
				if (line[0] == '#')
					continue;
D 81
				if (strcmp(line, name) == 0)
					return (1);
E 81
I 81
D 88
				if (strcmp(p, name) == 0) {
E 88
I 88
				if (strcmp(line, name) == 0) {
E 88
					found = 1;
					break;
				}
E 81
			}
E 73
		(void) fclose(fd);
	}
D 81
	return (0);
E 81
I 81
	return (found);
E 81
E 71
}

/*
 * Terminate login as previous user, if any, resetting state;
 * used when USER command is given or login fails.
 */
I 81
static void
E 81
end_login()
{

	(void) seteuid((uid_t)0);
	if (logged_in)
		logwtmp(ttyline, "", "");
	pw = NULL;
	logged_in = 0;
	guest = 0;
}

I 81
void
E 81
E 58
E 54
E 51
pass(passwd)
	char *passwd;
{
D 2
	char *xpasswd;
E 2
I 2
D 54
	char *xpasswd, *savestr();
	static struct passwd save;
E 54
I 54
D 58
	char *xpasswd;
E 58
I 58
D 85
	char *xpasswd, *salt;
E 85
I 85
	char *salt, *xpasswd;
E 85
I 81
	FILE *fd;
E 81
E 58
E 54
E 2

D 58
	if (logged_in || pw == NULL) {
E 58
I 58
	if (logged_in || askpasswd == 0) {
E 58
		reply(503, "Login with USER first.");
		return;
	}
I 58
	askpasswd = 0;
E 58
	if (!guest) {		/* "ftp" is only account allowed no password */
D 58
		xpasswd = crypt(passwd, pw->pw_passwd);
E 58
I 58
		if (pw == NULL)
			salt = "xx";
		else
			salt = pw->pw_passwd;
		xpasswd = crypt(passwd, salt);
E 58
D 30
		if (strcmp(xpasswd, pw->pw_passwd) != 0) {
E 30
I 30
D 32
		if (*pw->pw_passwd == '\0' || strcmp(xpasswd, pw->pw_passwd)) {
E 32
I 32
D 33
		if (strcmp(xpasswd, pw->pw_passwd) != 0) {
E 33
I 33
		/* The strcmp does not catch null passwords! */
D 58
		if (*pw->pw_passwd == '\0' || strcmp(xpasswd, pw->pw_passwd)) {
E 58
I 58
		if (pw == NULL || *pw->pw_passwd == '\0' ||
		    strcmp(xpasswd, pw->pw_passwd)) {
E 58
E 33
E 32
E 30
			reply(530, "Login incorrect.");
I 81
			if (logging)
				syslog(LOG_NOTICE,
				    "FTP LOGIN FAILED FROM %s, %s",
				    remotehost, curname);
E 81
			pw = NULL;
I 58
			if (login_attempts++ >= 5) {
D 65
				syslog(LOG_ERR,
E 65
I 65
				syslog(LOG_NOTICE,
E 65
				    "repeated login failures from %s",
				    remotehost);
				exit(0);
			}
E 58
			return;
		}
	}
D 2
	home = pw->pw_dir;		/* home dir for globbing */
	setreuid(-1, pw->pw_uid);
	setregid(-1, pw->pw_gid);
E 2
I 2
D 58
	setegid(pw->pw_gid);
E 2
	initgroups(pw->pw_name, pw->pw_gid);
E 58
I 58
	login_attempts = 0;		/* this time successful */
D 81
	(void) setegid((gid_t)pw->pw_gid);
E 81
I 81
	if (setegid((gid_t)pw->pw_gid) < 0) {
		reply(550, "Can't set gid.");
		return;
	}
E 81
	(void) initgroups(pw->pw_name, pw->pw_gid);
E 58
D 60
	if (chdir(pw->pw_dir)) {
D 36
		reply(550, "User %s: can't change directory to $s.",
E 36
I 36
D 43
		reply(550, "User %s: can't change directory to %s.",
E 43
I 43
		reply(530, "User %s: can't change directory to %s.",
E 43
E 36
			pw->pw_name, pw->pw_dir);
D 2
		pw = NULL;
		return;
E 2
I 2
		goto bad;
E 2
	}
E 60
I 31

D 33
	if (guest)			/* grab wtmp before chroot */
		wtmp = open("/usr/adm/wtmp", O_WRONLY|O_APPEND);
E 33
I 33
D 55
	/* grab wtmp before chroot */
	wtmp = open("/usr/adm/wtmp", O_WRONLY|O_APPEND);
E 33
D 32

E 32
E 31
D 2
	if (guest && chroot(pw->pw_dir) < 0){
E 2
I 2
	if (guest && chroot(pw->pw_dir) < 0) {
E 2
		reply(550, "Can't set guest privileges.");
I 33
		if (wtmp >= 0) {
			(void) close(wtmp);
			wtmp = -1;
		}
E 33
D 2
		pw = NULL;
		return;
E 2
I 2
		goto bad;
E 2
	}
	if (!guest)
		reply(230, "User %s logged in.", pw->pw_name);
	else
		reply(230, "Guest login ok, access restrictions apply.");
	logged_in = 1;
E 55
I 55
	/* open wtmp before chroot */
E 55
I 25
D 51
	dologin(pw);
E 51
I 51
	(void)sprintf(ttyline, "ftp%d", getpid());
	logwtmp(ttyline, pw->pw_name, remotehost);
I 55
	logged_in = 1;

D 58
	if (guest) {
		if (chroot(pw->pw_dir) < 0) {
			reply(550, "Can't set guest privileges.");
			goto bad;
		}
E 58
I 58
D 60
	if (guest && chroot(pw->pw_dir) < 0) {
		reply(550, "Can't set guest privileges.");
		goto bad;
E 60
I 60
	if (guest) {
D 64
		if (chroot(pw->pw_dir) < 0) {
E 64
I 64
		/*
D 65
		 * We MUST do a chdir() after the chroot. Otherwise "."
		 * will be accessible outside the root!
E 65
I 65
		 * We MUST do a chdir() after the chroot. Otherwise
		 * the old current directory will be accessible as "."
		 * outside the new root!
E 65
		 */
		if (chroot(pw->pw_dir) < 0 || chdir("/") < 0) {
E 64
			reply(550, "Can't set guest privileges.");
			goto bad;
		}
E 60
D 65
	}
I 60
D 64
	else if (chdir(pw->pw_dir))
		if (chdir("/")) {
E 64
I 64
	else if (chdir(pw->pw_dir) < 0) {
E 65
I 65
	} else if (chdir(pw->pw_dir) < 0) {
E 65
		if (chdir("/") < 0) {
E 64
			reply(530, "User %s: can't change directory to %s.",
			    pw->pw_name, pw->pw_dir);
			goto bad;
D 65
		}
		else
E 65
I 65
		} else
E 65
			lreply(230, "No directory! Logging in with home=/");
I 64
	}
E 64
E 60
	if (seteuid((uid_t)pw->pw_uid) < 0) {
		reply(550, "Can't set uid.");
		goto bad;
	}
I 81
	/*
	 * Display a login message, if it exists.
	 * N.B. reply(230,) must follow the message.
	 */
	if ((fd = fopen(_PATH_FTPLOGINMESG, "r")) != NULL) {
D 85
		char *cp, line[MAXLINE];
E 85
I 85
		char *cp, line[LINE_MAX];
E 85

D 85
		while (fgets(line, sizeof (line), fd) != NULL) {
E 85
I 85
		while (fgets(line, sizeof(line), fd) != NULL) {
E 85
D 83
			if ((cp = index(line, '\n')) != NULL)
E 83
I 83
			if ((cp = strchr(line, '\n')) != NULL)
E 83
				*cp = '\0';
			lreply(230, "%s", line);
		}
		(void) fflush(stdout);
		(void) fclose(fd);
	}
E 81
D 61
	if (guest)
E 61
I 61
	if (guest) {
E 61
E 58
		reply(230, "Guest login ok, access restrictions apply.");
D 58
	} else
E 58
I 58
D 61
	else
E 61
I 61
D 65
		syslog(LOG_INFO, "ANONYMOUS FTP LOGIN FROM %s, %s",
		    remotehost, passwd);
D 62
	} else {
E 62
I 62
	}
	else {
E 65
I 65
#ifdef SETPROCTITLE
D 85
		sprintf(proctitle, "%s: anonymous/%.*s", remotehost,
E 85
I 85
		snprintf(proctitle, sizeof(proctitle),
		    "%s: anonymous/%.*s", remotehost,
E 85
		    sizeof(proctitle) - sizeof(remotehost) -
		    sizeof(": anonymous/"), passwd);
		setproctitle(proctitle);
#endif /* SETPROCTITLE */
		if (logging)
			syslog(LOG_INFO, "ANONYMOUS FTP LOGIN FROM %s, %s",
			    remotehost, passwd);
I 80
D 85
		home = "/";		/* guest home dir for globbing */
E 85
E 80
	} else {
E 65
E 62
E 61
E 58
		reply(230, "User %s logged in.", pw->pw_name);
I 61
D 65
		syslog(LOG_INFO, "FTP LOGIN FROM %s, %s",
		    remotehost, pw->pw_name);
E 65
I 65
#ifdef SETPROCTITLE
D 85
		sprintf(proctitle, "%s: %s", remotehost, pw->pw_name);
E 85
I 85
		snprintf(proctitle, sizeof(proctitle),
		    "%s: %s", remotehost, pw->pw_name);
E 85
		setproctitle(proctitle);
#endif /* SETPROCTITLE */
		if (logging)
D 81
			syslog(LOG_INFO, "FTP LOGIN FROM %s, %s",
E 81
I 81
			syslog(LOG_INFO, "FTP LOGIN FROM %s as %s",
E 81
			    remotehost, pw->pw_name);
I 80
D 85
		home = pw->pw_dir;	/* home dir for globbing */
E 85
E 80
E 65
	}
E 61
E 55
E 51
E 25
I 2
D 58
	seteuid(pw->pw_uid);
E 58
D 54
	/*
	 * Save everything so globbing doesn't
	 * clobber the fields.
	 */
	save = *pw;
	save.pw_name = savestr(pw->pw_name);
	save.pw_passwd = savestr(pw->pw_passwd);
	save.pw_comment = savestr(pw->pw_comment);
D 41
	save.pw_gecos = savestr(pw->pw_gecos, &save.pw_gecos);
E 41
I 41
	save.pw_gecos = savestr(pw->pw_gecos);
E 41
	save.pw_dir = savestr(pw->pw_dir);
	save.pw_shell = savestr(pw->pw_shell);
	pw = &save;
E 54
D 80
	home = pw->pw_dir;		/* home dir for globbing */
E 80
I 65
	(void) umask(defumask);
E 65
	return;
bad:
D 58
	seteuid(0);
	pw = NULL;
E 58
I 58
	/* Forget all about it... */
	end_login();
E 58
E 2
}

I 81
void
E 81
I 2
D 54
char *
savestr(s)
	char *s;
{
	char *malloc();
D 41
	char *new = malloc(strlen(s) + 1);
E 41
I 41
	char *new = malloc((unsigned) strlen(s) + 1);
E 41
	
	if (new != NULL)
D 41
		strcpy(new, s);
E 41
I 41
		(void) strcpy(new, s);
E 41
D 19
	return(new);
E 19
I 19
	return (new);
E 19
}

E 54
E 2
retrieve(cmd, name)
	char *cmd, *name;
{
	FILE *fin, *dout;
	struct stat st;
D 39
	int (*closefunc)();
E 39
I 39
D 64
	int (*closefunc)(), tmp;
E 64
I 64
D 85
	int (*closefunc)();
E 85
I 85
	int (*closefunc) __P((FILE *));
E 85
E 64
E 39

D 60
	if (cmd == 0) {
I 5
#ifdef notdef
		/* no remote command execution -- it's a security hole */
E 5
D 20
		if (*name == '!')
E 20
I 20
		if (*name == '|')
E 20
D 57
			fin = popen(name + 1, "r"), closefunc = pclose;
E 57
I 57
D 58
			fin = ftpd_popen(name + 1, "r"), closefunc = pclose;
E 58
I 58
			fin = ftpd_popen(name + 1, "r"),
			    closefunc = ftpd_pclose;
E 58
E 57
		else
I 5
#endif
E 5
			fin = fopen(name, "r"), closefunc = fclose;
	} else {
E 60
I 60
D 63
	if (cmd == 0)
E 63
I 63
	if (cmd == 0) {
E 63
		fin = fopen(name, "r"), closefunc = fclose;
D 63
	else {
E 63
I 63
		st.st_size = 0;
	} else {
E 63
E 60
		char line[BUFSIZ];

D 11
		sprintf(line, cmd, name);
E 11
I 11
D 41
		sprintf(line, cmd, name), name = line;
E 41
I 41
		(void) sprintf(line, cmd, name), name = line;
E 41
E 11
D 57
		fin = popen(line, "r"), closefunc = pclose;
E 57
I 57
D 58
		fin = ftpd_popen(line, "r"), closefunc = pclose;
E 58
I 58
		fin = ftpd_popen(line, "r"), closefunc = ftpd_pclose;
I 63
		st.st_size = -1;
I 65
		st.st_blksize = BUFSIZ;
E 65
E 63
E 58
E 57
	}
	if (fin == NULL) {
D 23
		reply(550, "%s: %s.", name, sys_errlist[errno]);
E 23
I 23
D 81
		if (errno != 0)
E 81
I 81
		if (errno != 0) {
E 81
D 58
			reply(550, "%s: %s.", name, sys_errlist[errno]);
E 58
I 58
			perror_reply(550, name);
I 81
			if (cmd == 0) {
				LOGCMD("get", name);
			}
		}
E 81
E 58
E 23
		return;
	}
I 81
	byte_count = -1;
E 81
D 63
	st.st_size = 0;
E 63
D 85
	if (cmd == 0 &&
D 65
	    (stat(name, &st) < 0 || (st.st_mode&S_IFMT) != S_IFREG)) {
E 65
I 65
	    (fstat(fileno(fin), &st) < 0 || (st.st_mode&S_IFMT) != S_IFREG)) {
E 85
I 85
	if (cmd == 0 && (fstat(fileno(fin), &st) < 0 || !S_ISREG(st.st_mode))) {
E 85
E 65
		reply(550, "%s: not a plain file.", name);
		goto done;
	}
I 62
D 64
	if (restart_point)
E 64
I 64
D 66
	if (restart_point) {
E 64
		if (type == TYPE_A) {
D 64
			if (fseek(fin, restart_point, L_SET) < 0)
E 64
I 64
D 65
			if (fseek(fin, restart_point, L_SET) < 0) {
E 64
				perror_reply(550, name);
I 64
				goto done;
			}
E 64
		}
D 64
		else if (lseek(fileno(fin), restart_point, L_SET) < 0)
E 64
I 64
		else if (lseek(fileno(fin), restart_point, L_SET) < 0) {
E 65
I 65
D 85
			register int i, n, c;
E 85
I 85
			off_t i, n;
			int c;
E 85

			n = restart_point;
			i = 0;
			while (i++ < n) {
				if ((c=getc(fin)) == EOF) {
					perror_reply(550, name);
					goto done;
				}
				if (c == '\n')
					i++;
D 80
			}	
E 80
I 80
			}
E 80
		} else if (lseek(fileno(fin), restart_point, L_SET) < 0) {
E 65
E 64
			perror_reply(550, name);
I 64
			goto done;
		}
	}
E 66
E 64
E 62
	dout = dataconn(name, st.st_size, "w");
	if (dout == NULL)
		goto done;
D 2
	if (!send_data(fin, dout) || ferror(dout))
E 2
I 2
D 39
	if (send_data(fin, dout) || ferror(dout))
E 39
I 39
D 60
	if ((tmp = send_data(fin, dout)) > 0 || ferror(dout) > 0) {
E 60
I 60
D 64
	if ((tmp = send_data(fin, dout, st.st_blksize)) > 0 ||
D 62
	    ferror(dout) > 0) {
E 62
I 62
	    ferror(dout) > 0)
E 62
E 60
E 39
E 2
D 58
		reply(550, "%s: %s.", name, sys_errlist[errno]);
E 58
I 58
		perror_reply(550, name);
E 58
D 39
	else
E 39
I 39
D 62
	}
	else if (tmp == 0) {
E 62
I 62
	else if (tmp == 0)
E 62
E 39
		reply(226, "Transfer complete.");
E 64
I 64
	send_data(fin, dout, st.st_blksize);
E 64
D 2
	if (mode == MODE_S)
		/* indicate EOF by closing connection */
		fclose(dout), data = -1;
E 2
I 2
D 39
	fclose(dout), data = -1;
E 39
I 39
D 62
	}
E 62
D 41
	fclose(dout);
E 41
I 41
	(void) fclose(dout);
E 41
	data = -1;
	pdata = -1;
E 39
E 2
done:
I 81
	if (cmd == 0)
		LOGBYTES("get", name, byte_count);
E 81
	(*closefunc)(fin);
}

I 81
void
E 81
D 58
store(name, mode)
E 58
I 58
store(name, mode, unique)
E 58
	char *name, *mode;
I 58
	int unique;
E 58
{
	FILE *fout, *din;
I 60
	struct stat st;
E 60
D 2
	int (*closefunc)();
E 2
I 2
D 39
	int (*closefunc)(), dochown = 0;
E 39
I 39
D 58
	int (*closefunc)(), dochown = 0, tmp;
	char *gunique(), *local;
E 58
I 58
D 64
	int (*closefunc)(), tmp;
E 64
I 64
D 85
	int (*closefunc)();
E 85
I 85
	int (*closefunc) __P((FILE *));
E 85
E 64
D 81
	char *gunique();
E 81
E 58
E 39
E 2

I 5
D 60
#ifdef notdef
	/* no remote command execution -- it's a security hole */
E 5
D 20
	if (name[0] == '!')
E 20
I 20
	if (name[0] == '|')
E 20
D 57
		fout = popen(&name[1], "w"), closefunc = pclose;
E 57
I 57
D 58
		fout = ftpd_popen(&name[1], "w"), closefunc = pclose;
E 58
I 58
		fout = ftpd_popen(&name[1], "w"), closefunc = ftpd_pclose;
E 58
E 57
D 2
	else
E 2
I 2
D 5
	else {
E 5
I 5
	else
#endif
	{
E 5
		struct stat st;
E 60
I 60
	if (unique && stat(name, &st) == 0 &&
D 81
	    (name = gunique(name)) == NULL)
E 81
I 81
	    (name = gunique(name)) == NULL) {
		LOGCMD(*mode == 'w' ? "put" : "append", name);
E 81
		return;
I 81
	}
E 81
E 60

D 39
		if (stat(name, &st) < 0)
E 39
I 39
D 58
		local = name;
		if (stat(name, &st) < 0) {
E 39
			dochown++;
E 2
D 39
		fout = fopen(name, mode), closefunc = fclose;
E 39
I 39
		}
		else if (unique) {
			if ((local = gunique(name)) == NULL) {
				return;
			}
			dochown++;
		}
		fout = fopen(local, mode), closefunc = fclose;
E 58
I 58
D 60
		if (unique && stat(name, &st) == 0 &&
		    (name = gunique(name)) == NULL)
			return;
		fout = fopen(name, mode), closefunc = fclose;
E 58
E 39
I 2
	}
E 60
I 60
D 64
	fout = fopen(name, mode), closefunc = fclose;
E 64
I 64
D 66
	if (restart_point)
D 85
		mode = "r+w";
E 85
I 85
		mode = "r+";
E 85
E 66
	fout = fopen(name, mode);
	closefunc = fclose;
E 64
E 60
E 2
	if (fout == NULL) {
D 39
		reply(550, "%s: %s.", name, sys_errlist[errno]);
E 39
I 39
D 43
		reply(550, "%s: %s.", local, sys_errlist[errno]);
E 43
I 43
D 58
		reply(553, "%s: %s.", local, sys_errlist[errno]);
E 58
I 58
		perror_reply(553, name);
I 81
		LOGCMD(*mode == 'w' ? "put" : "append", name);
E 81
E 58
E 43
E 39
		return;
D 66
	}
I 81
	byte_count = -1;
E 81
I 62
D 64
	if (restart_point)
E 64
I 64
	if (restart_point) {
E 64
		if (type == TYPE_A) {
D 64
			if (fseek(fout, restart_point, L_SET) < 0)
E 64
I 64
D 65
			if (fseek(fout, restart_point, L_SET) < 0) {
E 65
I 65
D 85
			register int i, n, c;
E 85
I 85
			off_t i, n;
			int c;
E 85

			n = restart_point;
			i = 0;
			while (i++ < n) {
				if ((c=getc(fout)) == EOF) {
					perror_reply(550, name);
					goto done;
				}
				if (c == '\n')
					i++;
D 80
			}	
E 80
I 80
			}
E 80
			/*
			 * We must do this seek to "current" position
			 * because we are changing from reading to
			 * writing.
			 */
			if (fseek(fout, 0L, L_INCR) < 0) {
E 65
E 64
				perror_reply(550, name);
I 64
				goto done;
			}
E 64
D 65
		}
D 64
		else if (lseek(fileno(fout), restart_point, L_SET) < 0)
E 64
I 64
		else if (lseek(fileno(fout), restart_point, L_SET) < 0) {
E 65
I 65
		} else if (lseek(fileno(fout), restart_point, L_SET) < 0) {
E 65
E 64
			perror_reply(550, name);
I 64
			goto done;
		}
E 66
	}
E 64
E 62
D 20
	din = dataconn(name, -1, "r");
E 20
I 20
D 39
	din = dataconn(name, (off_t)-1, "r");
E 39
I 39
D 58
	din = dataconn(local, (off_t)-1, "r");
E 58
I 58
	din = dataconn(name, (off_t)-1, "r");
E 58
E 39
E 20
	if (din == NULL)
		goto done;
D 2
	if (!receive_data(din, fout) || ferror(fout))
E 2
I 2
D 39
	if (receive_data(din, fout) || ferror(fout))
E 2
		reply(550, "%s: %s.", name, sys_errlist[errno]);
	else
E 39
I 39
D 58
	if ((tmp = receive_data(din, fout)) > 0 || ferror(fout) > 0) {
D 43
		reply(550, "%s: %s.", local, sys_errlist[errno]);
E 43
I 43
		reply(552, "%s: %s.", local, sys_errlist[errno]);
E 58
I 58
D 64
	if ((tmp = receive_data(din, fout)) > 0)
		perror_reply(552, name);
	else if (tmp == 0) {
		if (ferror(fout) > 0)
			perror_reply(552, name);
		else if (unique)
E 64
I 64
	if (receive_data(din, fout) == 0) {
		if (unique)
E 64
			reply(226, "Transfer complete (unique file name:%s).",
D 64
			    name);
E 64
I 64
D 65
				name);
E 65
I 65
			    name);
E 65
E 64
		else
			reply(226, "Transfer complete.");
E 58
E 43
	}
D 58
	else if (tmp == 0 && !unique) {
E 39
		reply(226, "Transfer complete.");
D 39
	fclose(din), data = -1;
E 39
I 39
	}
	else if (tmp == 0 && unique) {
		reply(226, "Transfer complete (unique file name:%s).", local);
	}
E 58
D 41
	fclose(din);
E 41
I 41
	(void) fclose(din);
E 41
	data = -1;
	pdata = -1;
E 39
done:
I 81
	LOGBYTES(*mode == 'w' ? "put" : "append", name, byte_count);
E 81
I 2
D 58
	if (dochown)
D 39
		(void) chown(name, pw->pw_uid, -1);
E 39
I 39
D 57
		(void) chown(local, pw->pw_uid, -1);
E 57
I 57
		(void) fchown(fileno(fout), pw->pw_uid, -1);
E 58
E 57
E 39
E 2
	(*closefunc)(fout);
}

D 81
FILE *
E 81
I 81
static FILE *
E 81
getdatasock(mode)
	char *mode;
{
D 15
	int retrytime, s;
E 15
I 15
D 22
	int s;
E 22
I 22
D 25
	int s, linger;
E 25
I 25
D 34
	int s;
E 34
I 34
D 67
	int s, on = 1;
E 67
I 67
D 85
	int s, on = 1, tries;
I 81
	int t;
E 85
I 85
	int on = 1, s, t, tries;
E 85
E 81
E 67
E 34
E 25
E 22
E 15

	if (data >= 0)
		return (fdopen(data, mode));
I 79
	(void) seteuid((uid_t)0);
E 79
D 15
	retrytime = 1;
	while ((s = socket(AF_INET, SOCK_STREAM, 0, 0)) < 0) {
		if (retrytime < 5) {
			sleep(retrytime);
			retrytime <<= 1;
			continue;
		}
E 15
I 15
D 25
	s = socket(AF_INET, SOCK_STREAM, 0, 0);
E 25
I 25
	s = socket(AF_INET, SOCK_STREAM, 0);
E 25
	if (s < 0)
E 15
D 79
		return (NULL);
D 15
	}
	retrytime = 1;
E 15
D 58
	seteuid(0);
E 58
I 58
	(void) seteuid((uid_t)0);
E 79
I 79
		goto bad;
E 79
E 58
D 15
	while (bind(s, &data_source, sizeof (data_source), 0) < 0) {
		if (retrytime < 5) {
			sleep(retrytime);
			retrytime <<= 1;
			continue;
		}
D 4
		seteuid(0);
E 4
I 4
		seteuid(pw->pw_uid);
E 4
		close(s);
		return (NULL);
	}
E 15
I 15
D 34
	if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, 0, 0) < 0)
E 34
I 34
D 41
	if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof (on)) < 0)
E 41
I 41
D 67
	if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof (on)) < 0)
E 67
I 67
	if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR,
D 85
	    (char *) &on, sizeof (on)) < 0)
E 85
I 85
	    (char *) &on, sizeof(on)) < 0)
E 85
E 67
E 41
E 34
		goto bad;
I 23
	/* anchor socket to avoid multi-homing problems */
	data_source.sin_family = AF_INET;
	data_source.sin_addr = ctrl_addr.sin_addr;
E 23
D 41
	if (bind(s, &data_source, sizeof (data_source), 0) < 0)
E 41
I 41
D 58
	if (bind(s, &data_source, sizeof (data_source)) < 0)
E 58
I 58
D 67
	if (bind(s, (struct sockaddr *)&data_source, sizeof (data_source)) < 0)
E 58
E 41
		goto bad;
E 67
I 67
	for (tries = 1; ; tries++) {
		if (bind(s, (struct sockaddr *)&data_source,
D 85
		    sizeof (data_source)) >= 0)
E 85
I 85
		    sizeof(data_source)) >= 0)
E 85
			break;
		if (errno != EADDRINUSE || tries > 10)
			goto bad;
		sleep(tries);
	}
E 67
I 22
D 25
	linger = 60;			/* value ignored by system */
	(void) setsockopt(s, SOL_SOCKET, SO_LINGER, &linger, sizeof (linger));
E 25
E 22
E 15
D 4
	seteuid(0);
E 4
I 4
D 58
	seteuid(pw->pw_uid);
E 58
I 58
	(void) seteuid((uid_t)pw->pw_uid);
I 76
#ifdef IP_TOS
	on = IPTOS_THROUGHPUT;
	if (setsockopt(s, IPPROTO_IP, IP_TOS, (char *)&on, sizeof(int)) < 0)
		syslog(LOG_WARNING, "setsockopt (IP_TOS): %m");
#endif
E 76
E 58
E 4
	return (fdopen(s, mode));
I 15
bad:
I 81
	/* Return the real value of errno (close may change it) */
	t = errno;
E 81
D 58
	seteuid(pw->pw_uid);
E 58
I 58
	(void) seteuid((uid_t)pw->pw_uid);
E 58
D 41
	close(s);
E 41
I 41
	(void) close(s);
I 81
	errno = t;
E 81
E 41
	return (NULL);
E 15
}

D 81
FILE *
E 81
I 81
static FILE *
E 81
dataconn(name, size, mode)
	char *name;
D 20
	int size;
E 20
I 20
	off_t size;
E 20
	char *mode;
{
	char sizebuf[32];
	FILE *file;
I 20
D 76
	int retry = 0;
E 76
I 76
	int retry = 0, tos;
E 76
E 20

I 65
	file_size = size;
	byte_count = 0;
E 65
D 58
	if (size >= 0)
E 58
I 58
	if (size != (off_t) -1)
E 58
D 20
		sprintf(sizebuf, " (%d bytes)", size);
E 20
I 20
D 41
		sprintf (sizebuf, " (%ld bytes)", size);
E 41
I 41
D 81
		(void) sprintf (sizebuf, " (%ld bytes)", size);
E 81
I 81
D 85
		(void) sprintf (sizebuf, " (%qd bytes)", size);
E 85
I 85
		(void) sprintf(sizebuf, " (%qd bytes)", size);
E 85
E 81
E 41
E 20
	else
		(void) strcpy(sizebuf, "");
I 39
D 58
	if (pdata > 0) {
E 58
I 58
	if (pdata >= 0) {
E 58
		struct sockaddr_in from;
		int s, fromlen = sizeof(from);

D 41
		s = accept(pdata, &from, &fromlen, 0);
E 41
I 41
D 58
		s = accept(pdata, &from, &fromlen);
E 58
I 58
		s = accept(pdata, (struct sockaddr *)&from, &fromlen);
E 58
E 41
		if (s < 0) {
			reply(425, "Can't open data connection.");
			(void) close(pdata);
			pdata = -1;
D 85
			return(NULL);
E 85
I 85
			return (NULL);
E 85
		}
		(void) close(pdata);
		pdata = s;
I 76
#ifdef IP_TOS
		tos = IPTOS_LOWDELAY;
		(void) setsockopt(s, IPPROTO_IP, IP_TOS, (char *)&tos,
		    sizeof(int));
#endif
E 76
D 53
		reply(150, "Openning data connection for %s (%s,%d)%s.",
D 41
		     name, inet_ntoa(from.sin_addr.s_addr),
E 41
I 41
		     name, inet_ntoa(from.sin_addr),
E 41
		     ntohs(from.sin_port), sizebuf);
E 53
I 53
D 56
		reply(150, "Opening data connection for %s (%s mode)%s.",
		     name, type == TYPE_A ? "ascii" : "binary", sizebuf);
E 56
I 56
D 81
		reply(150, "Opening %s mode data connection for %s%s.",
E 81
I 81
		reply(150, "Opening %s mode data connection for '%s'%s.",
E 81
		     type == TYPE_A ? "ASCII" : "BINARY", name, sizebuf);
E 56
E 53
D 85
		return(fdopen(pdata, mode));
E 85
I 85
		return (fdopen(pdata, mode));
E 85
	}
E 39
	if (data >= 0) {
D 81
		reply(125, "Using existing data connection for %s%s.",
E 81
I 81
		reply(125, "Using existing data connection for '%s'%s.",
E 81
		    name, sizebuf);
I 7
		usedefault = 1;
E 7
		return (fdopen(data, mode));
	}
I 11
D 13
	/*
	 * If no PORT command was specified,
	 * use the default address.
	 */
	if (usedefault) {
E 13
I 13
	if (usedefault)
E 13
		data_dest = his_addr;
D 13
		data_dest.sin_port = htons(ntohs(sp->s_port) - 1);
	}
E 13
	usedefault = 1;
E 11
D 15
	reply(150, "Opening data connection for %s (%s,%d)%s.",
	    name, ntoa(data_dest.sin_addr.s_addr),
	    ntohs(data_dest.sin_port), sizebuf);
E 15
	file = getdatasock(mode);
	if (file == NULL) {
		reply(425, "Can't create data socket (%s,%d): %s.",
D 25
		    ntoa(data_source.sin_addr),
E 25
I 25
		    inet_ntoa(data_source.sin_addr),
E 25
D 74
		    ntohs(data_source.sin_port),
D 58
		    sys_errlist[errno]);
E 58
I 58
		    errno < sys_nerr ? sys_errlist[errno] : "unknown error");
E 74
I 74
		    ntohs(data_source.sin_port), strerror(errno));
E 74
E 58
I 7
D 11
		usedefault = 1;
E 11
E 7
		return (NULL);
	}
I 15
D 44
	reply(150, "Opening data connection for %s (%s,%d)%s.",
D 25
	    name, ntoa(data_dest.sin_addr.s_addr),
E 25
I 25
D 41
	    name, inet_ntoa(data_dest.sin_addr.s_addr),
E 41
I 41
	    name, inet_ntoa(data_dest.sin_addr),
E 41
E 25
	    ntohs(data_dest.sin_port), sizebuf);
E 44
E 15
	data = fileno(file);
I 7
D 11
	/*
	 * If no PORT command was specified,
	 * use the default address.
	 */
	if (usedefault) {
		data_dest = his_addr;
		data_dest.sin_port = htons(ntohs(sp->s_port) - 1);
	}
D 8
	usedefault = 0;
E 8
I 8
	usedefault = 1;
E 11
E 8
E 7
D 20
	if (connect(data, &data_dest, sizeof (data_dest), 0) < 0) {
E 20
I 20
D 39
	while (connect(data, &data_dest, sizeof (data_dest), 0) < 0) {
E 39
I 39
D 58
	while (connect(data, &data_dest, sizeof (data_dest)) < 0) {
E 58
I 58
	while (connect(data, (struct sockaddr *)&data_dest,
D 85
	    sizeof (data_dest)) < 0) {
E 85
I 85
	    sizeof(data_dest)) < 0) {
E 85
E 58
E 39
		if (errno == EADDRINUSE && retry < swaitmax) {
D 41
			sleep(swaitint);
E 41
I 41
			sleep((unsigned) swaitint);
E 41
			retry += swaitint;
			continue;
		}
E 20
D 58
		reply(425, "Can't build data connection: %s.",
		    sys_errlist[errno]);
E 58
I 58
		perror_reply(425, "Can't build data connection");
E 58
		(void) fclose(file);
		data = -1;
		return (NULL);
	}
I 44
D 53
	reply(150, "Opening data connection for %s (%s,%d)%s.",
	    name, inet_ntoa(data_dest.sin_addr),
	    ntohs(data_dest.sin_port), sizebuf);
E 53
I 53
D 56
	reply(150, "Opening data connection for %s (%s mode)%s.",
	    name, type == TYPE_A ? "ascii" : "binary", sizebuf);
E 56
I 56
D 81
	reply(150, "Opening %s mode data connection for %s%s.",
E 81
I 81
	reply(150, "Opening %s mode data connection for '%s'%s.",
E 81
	     type == TYPE_A ? "ASCII" : "BINARY", name, sizebuf);
E 56
E 53
E 44
	return (file);
}

/*
D 81
 * Tranfer the contents of "instr" to
 * "outstr" peer using the appropriate
D 65
 * encapulation of the date subject
E 65
I 65
 * encapsulation of the data subject
E 65
 * to Mode, Structure, and Type.
E 81
I 81
 * Tranfer the contents of "instr" to "outstr" peer using the appropriate
 * encapsulation of the data subject * to Mode, Structure, and Type.
E 81
 *
 * NB: Form isn't handled.
 */
I 81
static void
E 81
D 60
send_data(instr, outstr)
E 60
I 60
send_data(instr, outstr, blksize)
E 60
	FILE *instr, *outstr;
I 60
	off_t blksize;
E 60
{
D 60
	register int c;
	int netfd, filefd, cnt;
	char buf[BUFSIZ];
E 60
I 60
D 85
	register int c, cnt;
	register char *buf;
	int netfd, filefd;
E 85
I 85
	int c, cnt, filefd, netfd;
	char *buf;
E 85
E 60

I 39
	transflag++;
	if (setjmp(urgcatch)) {
		transflag = 0;
D 64
		return(-1);
E 64
I 64
		return;
E 64
	}
E 39
	switch (type) {

	case TYPE_A:
		while ((c = getc(instr)) != EOF) {
I 65
			byte_count++;
E 65
D 18
			if (c == '\n')
E 18
I 18
			if (c == '\n') {
D 39
				if (ferror (outstr))
E 39
I 39
D 64
				if (ferror (outstr)) {
					transflag = 0;
E 39
					return (1);
I 39
				}
E 64
I 64
D 65
				if (ferror (outstr)) 
E 65
I 65
				if (ferror(outstr))
E 65
					goto data_err;
E 64
E 39
E 18
D 44
				putc('\r', outstr);
E 44
I 44
				(void) putc('\r', outstr);
E 44
D 18
			if (putc(c, outstr) == EOF)
				return (1);
E 18
I 18
			}
D 44
			putc(c, outstr);
E 44
I 44
			(void) putc(c, outstr);
E 44
D 39
			if (c == '\r')
				putc ('\0', outstr);
E 39
I 39
D 60
		/*	if (c == '\r')			*/
		/*		putc ('\0', outstr);	*/
E 60
E 39
E 18
		}
I 18
D 39
		if (ferror (instr) || ferror (outstr))
E 39
I 39
D 65
		transflag = 0;
E 65
D 64
		if (ferror (instr) || ferror (outstr)) {
E 39
			return (1);
I 39
		}
E 39
E 18
		return (0);
E 64
I 64
		fflush(outstr);
D 65
		if (ferror (instr) || ferror (outstr)) 
E 65
I 65
		transflag = 0;
		if (ferror(instr))
			goto file_err;
		if (ferror(outstr))
E 65
			goto data_err;
		reply(226, "Transfer complete.");
		return;
E 64
D 60
		
E 60
I 60

E 60
	case TYPE_I:
	case TYPE_L:
I 60
		if ((buf = malloc((u_int)blksize)) == NULL) {
			transflag = 0;
D 64
			return (1);
E 64
I 64
D 65
			perror_reply(421, "Local resource failure: malloc");
			dologout(1);
			/* NOTREACHED */
E 65
I 65
			perror_reply(451, "Local resource failure: malloc");
			return;
E 65
E 64
		}
E 60
		netfd = fileno(outstr);
		filefd = fileno(instr);
D 60

D 2
		while ((cnt = read(filefd, buf, sizeof buf)) > 0)
E 2
I 2
D 39
		while ((cnt = read(filefd, buf, sizeof (buf))) > 0)
E 2
			if (write(netfd, buf, cnt) < 0)
E 39
I 39
		while ((cnt = read(filefd, buf, sizeof (buf))) > 0) {
			if (write(netfd, buf, cnt) < 0) {
				transflag = 0;
E 39
				return (1);
I 39
			}
		}
E 60
I 60
D 65
		while ((cnt = read(filefd, buf, sizeof(buf))) > 0 &&
E 65
I 65
		while ((cnt = read(filefd, buf, (u_int)blksize)) > 0 &&
E 65
D 64
		    write(netfd, buf, cnt) == cnt);
E 64
I 64
		    write(netfd, buf, cnt) == cnt)
D 65
			/* LOOP */;
E 65
I 65
			byte_count += cnt;
E 65
E 64
E 60
		transflag = 0;
E 39
D 60
		return (cnt < 0);
E 60
I 60
		(void)free(buf);
D 64
		return (cnt != 0);
E 64
I 64
D 65
		if (cnt != 0)
E 65
I 65
		if (cnt != 0) {
			if (cnt < 0)
				goto file_err;
E 65
			goto data_err;
I 65
		}
E 65
		reply(226, "Transfer complete.");
		return;
	default:
		transflag = 0;
		reply(550, "Unimplemented TYPE %d in send_data", type);
		return;
E 64
E 60
	}
D 43
	reply(504,"Unimplemented TYPE %d in send_data", type);
E 43
I 43
D 64
	reply(550, "Unimplemented TYPE %d in send_data", type);
E 64
I 64

data_err:
E 64
E 43
I 39
	transflag = 0;
E 39
D 43
	return (1);
E 43
I 43
D 64
	return (-1);
E 64
I 64
D 65
	perror_reply(421, "Data connection");
	dologout(1);
	/* NOTREACHED */
E 65
I 65
	perror_reply(426, "Data connection");
	return;

file_err:
	transflag = 0;
	perror_reply(551, "Error on input file");
E 65
E 64
E 43
}

/*
D 81
 * Transfer data from peer to
 * "outstr" using the appropriate
 * encapulation of the data subject
 * to Mode, Structure, and Type.
E 81
I 81
 * Transfer data from peer to "outstr" using the appropriate encapulation of
 * the data subject to Mode, Structure, and Type.
E 81
 *
 * N.B.: Form isn't handled.
 */
I 81
static int
E 81
receive_data(instr, outstr)
	FILE *instr, *outstr;
{
D 85
	register int c;
E 85
I 85
	int c;
E 85
D 16
	int cr, escape, eof;
	int netfd, filefd, cnt;
E 16
I 16
D 18
	int cr, escape, eof, cnt;
E 18
I 18
D 68
	int cnt;
E 68
I 68
	int cnt, bare_lfs = 0;
E 68
E 18
E 16
	char buf[BUFSIZ];

D 65

E 65
I 39
	transflag++;
	if (setjmp(urgcatch)) {
		transflag = 0;
D 65
		return(-1);
E 65
I 65
		return (-1);
E 65
	}
E 39
	switch (type) {

	case TYPE_I:
	case TYPE_L:
D 16
		netfd = fileno(instr);
		netfd = fileno(outstr);
		while ((cnt = read(netfd, buf, sizeof buf)) > 0)
			if (write(filefd, buf, cnt) < 0)
E 16
I 16
D 39
		while ((cnt = read(fileno(instr), buf, sizeof buf)) > 0)
			if (write(fileno(outstr), buf, cnt) < 0)
E 39
I 39
D 85
		while ((cnt = read(fileno(instr), buf, sizeof buf)) > 0) {
E 85
I 85
		while ((cnt = read(fileno(instr), buf, sizeof(buf))) > 0) {
E 85
D 64
			if (write(fileno(outstr), buf, cnt) < 0) {
				transflag = 0;
E 39
E 16
				return (1);
I 39
			}
E 64
I 64
			if (write(fileno(outstr), buf, cnt) != cnt)
D 65
				goto data_err;
E 65
I 65
				goto file_err;
			byte_count += cnt;
E 65
E 64
		}
I 64
D 65
		if (cnt < 0) 
E 65
I 65
		if (cnt < 0)
E 65
			goto data_err;
E 64
		transflag = 0;
E 39
D 64
		return (cnt < 0);
E 64
I 64
D 65
		return 0;
E 65
I 65
		return (0);
E 65
E 64

	case TYPE_E:
D 43
		reply(504, "TYPE E not implemented.");
E 43
I 43
		reply(553, "TYPE E not implemented.");
E 43
I 39
		transflag = 0;
E 39
D 43
		return (1);
E 43
I 43
		return (-1);
E 43

	case TYPE_A:
D 18
		cr = 0;
E 18
		while ((c = getc(instr)) != EOF) {
I 65
			byte_count++;
I 68
			if (c == '\n')
				bare_lfs++;
E 68
E 65
D 18
			if (cr) {
				if (c != '\r' && c != '\n')
					putc('\r', outstr);
				putc(c, outstr);
				cr = c == '\r';
				continue;
			}
E 18
D 44
			if (c == '\r') {
E 44
I 44
			while (c == '\r') {
E 44
D 18
				cr = 1;
				continue;
E 18
I 18
D 39
				if (ferror (outstr))
E 39
I 39
D 64
				if (ferror (outstr)) {
					transflag = 0;
E 39
					return (1);
I 39
				}
E 64
I 64
D 65
				if (ferror (outstr))
E 65
I 65
				if (ferror(outstr))
E 65
					goto data_err;
E 64
E 39
D 65
				if ((c = getc(instr)) != '\n')
E 65
I 65
				if ((c = getc(instr)) != '\n') {
E 65
D 44
					putc ('\r', outstr);
E 44
I 44
					(void) putc ('\r', outstr);
I 65
					if (c == '\0' || c == EOF)
						goto contin2;
				}
E 65
E 44
D 39
				if (c == '\0')
					continue;
E 39
I 39
D 64
			/*	if (c == '\0')			*/
			/*		continue;		*/
E 64
E 39
E 18
			}
D 18
			putc(c, outstr);
E 18
I 18
D 44
			putc (c, outstr);
E 44
I 44
D 65
			(void) putc (c, outstr);
E 65
I 65
			(void) putc(c, outstr);
	contin2:	;
E 65
E 44
E 18
		}
I 39
D 64
		transflag = 0;
E 64
I 64
		fflush(outstr);
E 64
E 39
D 18
		if (cr)
			putc('\r', outstr);
E 18
I 18
D 65
		if (ferror (instr) || ferror (outstr))
E 65
I 65
		if (ferror(instr))
E 65
D 64
			return (1);
E 64
I 64
			goto data_err;
I 65
		if (ferror(outstr))
			goto file_err;
E 65
		transflag = 0;
I 68
		if (bare_lfs) {
D 87
			lreply(230, "WARNING! %d bare linefeeds received in ASCII mode", bare_lfs);
			printf("   File may not have transferred correctly.\r\n");
E 87
I 87
			lreply(226,
		"WARNING! %d bare linefeeds received in ASCII mode",
			    bare_lfs);
		(void)printf("   File may not have transferred correctly.\r\n");
E 87
		}
E 68
E 64
E 18
		return (0);
I 64
	default:
		reply(550, "Unimplemented TYPE %d in receive_data", type);
		transflag = 0;
D 65
		return 1;
E 65
I 65
		return (-1);
E 65
E 64
	}
I 64

data_err:
E 64
I 39
	transflag = 0;
E 39
D 64
	fatal("Unknown type in receive_data.");
	/*NOTREACHED*/
E 64
I 64
D 65
	perror_reply(421, "Data Connection");
	dologout(1);
	/* NOTREACHED */
E 65
I 65
	perror_reply(426, "Data Connection");
	return (-1);

file_err:
	transflag = 0;
	perror_reply(452, "Error writing file");
	return (-1);
E 65
E 64
}

I 81
void
E 81
I 65
statfilecmd(filename)
	char *filename;
{
D 85
	char line[BUFSIZ];
E 85
	FILE *fin;
	int c;
I 85
	char line[LINE_MAX];
E 85

D 81
	(void) sprintf(line, "/bin/ls -lgA %s", filename);
E 81
I 81
	(void)snprintf(line, sizeof(line), "/bin/ls -lgA %s", filename);
E 81
	fin = ftpd_popen(line, "r");
	lreply(211, "status of %s:", filename);
	while ((c = getc(fin)) != EOF) {
		if (c == '\n') {
			if (ferror(stdout)){
				perror_reply(421, "control connection");
				(void) ftpd_pclose(fin);
				dologout(1);
				/* NOTREACHED */
			}
			if (ferror(fin)) {
				perror_reply(551, filename);
				(void) ftpd_pclose(fin);
				return;
			}
			(void) putc('\r', stdout);
		}
		(void) putc(c, stdout);
	}
	(void) ftpd_pclose(fin);
	reply(211, "End of Status");
}

I 81
void
E 81
statcmd()
{
	struct sockaddr_in *sin;
	u_char *a, *p;

	lreply(211, "%s FTP server status:", hostname, version);
	printf("     %s\r\n", version);
	printf("     Connected to %s", remotehost);
D 68
	if (isdigit(remotehost[0]))
E 68
I 68
	if (!isdigit(remotehost[0]))
E 68
		printf(" (%s)", inet_ntoa(his_addr.sin_addr));
	printf("\r\n");
	if (logged_in) {
		if (guest)
			printf("     Logged in anonymously\r\n");
		else
			printf("     Logged in as %s\r\n", pw->pw_name);
	} else if (askpasswd)
		printf("     Waiting for password\r\n");
	else
		printf("     Waiting for user name\r\n");
	printf("     TYPE: %s", typenames[type]);
	if (type == TYPE_A || type == TYPE_E)
		printf(", FORM: %s", formnames[form]);
	if (type == TYPE_L)
#if NBBY == 8
		printf(" %d", NBBY);
#else
		printf(" %d", bytesize);	/* need definition! */
#endif
	printf("; STRUcture: %s; transfer MODE: %s\r\n",
	    strunames[stru], modenames[mode]);
	if (data != -1)
		printf("     Data connection open\r\n");
	else if (pdata != -1) {
		printf("     in Passive mode");
		sin = &pasv_addr;
		goto printaddr;
	} else if (usedefault == 0) {
		printf("     PORT");
		sin = &data_dest;
printaddr:
		a = (u_char *) &sin->sin_addr;
		p = (u_char *) &sin->sin_port;
#define UC(b) (((int) b) & 0xff)
		printf(" (%d,%d,%d,%d,%d,%d)\r\n", UC(a[0]),
			UC(a[1]), UC(a[2]), UC(a[3]), UC(p[0]), UC(p[1]));
#undef UC
	} else
		printf("     No data connection\r\n");
	reply(211, "End of status");
}

I 81
void
E 81
E 65
fatal(s)
	char *s;
{
I 85

E 85
	reply(451, "Error in server: %s\n", s);
	reply(221, "Closing connection due to server error.");
D 25
	exit(0);
E 25
I 25
	dologout(0);
I 64
	/* NOTREACHED */
E 64
E 25
}

I 58
D 59
/* VARARGS2 */
E 58
I 41
D 48
/*VARARGS2*/
E 41
reply(n, s, args)
E 48
I 48
reply(n, s, p0, p1, p2, p3, p4)
E 59
I 59
D 60
reply(n, s, argp)
E 60
I 60
D 81
/* VARARGS2 */
reply(n, fmt, p0, p1, p2, p3, p4, p5)
E 81
I 81
void
#if __STDC__
reply(int n, const char *fmt, ...)
#else
reply(n, fmt, va_alist)
E 81
E 60
E 59
E 48
	int n;
D 60
	char *s;
I 59
	va_list argp;
E 60
I 60
	char *fmt;
I 81
        va_dcl
#endif
E 81
E 60
E 59
{
D 59

E 59
D 81
	printf("%d ", n);
D 48
	_doprnt(s, &args, stdout);
E 48
I 48
D 59
	printf(s, p0, p1, p2, p3, p4);
E 59
I 59
D 60
	printf(s, argp);
E 60
I 60
	printf(fmt, p0, p1, p2, p3, p4, p5);
E 60
E 59
E 48
	printf("\r\n");
E 81
I 81
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)printf("%d ", n);
	(void)vprintf(fmt, ap);
	(void)printf("\r\n");
E 81
D 41
	fflush(stdout);
E 41
I 41
D 59
	(void) fflush(stdout);
E 59
I 59
	(void)fflush(stdout);
E 59
E 41
	if (debug) {
D 41
		fprintf(stderr, "<--- %d ", n);
		_doprnt(s, &args, stderr);
		fprintf(stderr, "\n");
		fflush(stderr);
E 41
I 41
		syslog(LOG_DEBUG, "<--- %d ", n);
D 48
		syslog(LOG_DEBUG, s, &args);
E 48
I 48
D 59
		syslog(LOG_DEBUG, s, p0, p1, p2, p3, p4);
E 59
I 59
D 60
		syslog(LOG_DEBUG, s, argp);
E 60
I 60
D 81
		syslog(LOG_DEBUG, fmt, p0, p1, p2, p3, p4, p5);
E 81
I 81
		vsyslog(LOG_DEBUG, fmt, ap);
	}
E 81
E 60
E 59
E 48
E 41
D 64
	}
E 64
}
I 64
D 81
}
E 81
E 64

I 58
D 59
/* VARARGS2 */
E 58
I 41
D 48
/*VARARGS2*/
E 41
lreply(n, s, args)
E 48
I 48
lreply(n, s, p0, p1, p2, p3, p4)
E 59
I 59
D 60
lreply(n, s)
E 60
I 60
D 81
/* VARARGS2 */
lreply(n, fmt, p0, p1, p2, p3, p4, p5)
E 81
I 81
void
#if __STDC__
lreply(int n, const char *fmt, ...)
#else
lreply(n, fmt, va_alist)
E 81
E 60
E 59
E 48
	int n;
D 60
	char *s;
E 60
I 60
	char *fmt;
I 81
        va_dcl
#endif
E 81
E 60
{
D 59
	printf("%d-", n);
D 48
	_doprnt(s, &args, stdout);
E 48
I 48
	printf(s, p0, p1, p2, p3, p4);
E 48
	printf("\r\n");
D 41
	fflush(stdout);
E 41
I 41
	(void) fflush(stdout);
E 41
	if (debug) {
D 41
		fprintf(stderr, "<--- %d-", n);
		_doprnt(s, &args, stderr);
		fprintf(stderr, "\n");
E 41
I 41
		syslog(LOG_DEBUG, "<--- %d- ", n);
D 48
		syslog(LOG_DEBUG, s, &args);
E 48
I 48
		syslog(LOG_DEBUG, s, p0, p1, p2, p3, p4);
E 48
E 41
	}
E 59
I 59
D 60
	printf("%d- %s\r\n", n, s);
E 60
I 60
D 81
	printf("%d- ", n);
	printf(fmt, p0, p1, p2, p3, p4, p5);
	printf("\r\n");
E 81
I 81
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)printf("%d- ", n);
	(void)vprintf(fmt, ap);
	(void)printf("\r\n");
E 81
E 60
	(void)fflush(stdout);
D 60
	if (debug)
		syslog(LOG_DEBUG, "<--- %d- %s", n, s);
E 60
I 60
	if (debug) {
		syslog(LOG_DEBUG, "<--- %d- ", n);
D 81
		syslog(LOG_DEBUG, fmt, p0, p1, p2, p3, p4, p5);
E 81
I 81
		vsyslog(LOG_DEBUG, fmt, ap);
E 81
	}
E 60
E 59
}

I 81
static void
E 81
I 41
D 43
/*  NOT CALLED ANYWHERE
E 41
replystr(s)
	char *s;
{
	printf("%s\r\n", s);
D 41
	fflush(stdout);
E 41
I 41
	(void) fflush(stdout);
E 41
	if (debug)
		fprintf(stderr, "<--- %s\n", s);
}
I 41
*/
E 41

E 43
ack(s)
	char *s;
{
I 85

E 85
D 39
	reply(200, "%s command okay.", s);
E 39
I 39
D 43
	reply(200, "%s command successful.", s);
E 43
I 43
	reply(250, "%s command successful.", s);
E 43
E 39
}

I 81
void
E 81
nack(s)
	char *s;
{
I 85

E 85
	reply(502, "%s command not implemented.", s);
}

I 58
/* ARGSUSED */
I 81
D 85
char *
E 85
I 85
void
E 85
E 81
E 58
D 41
yyerror()
E 41
I 41
yyerror(s)
	char *s;
E 41
{
D 39
	reply(500, "Command not understood.");
E 39
I 39
	char *cp;

D 62
	cp = index(cbuf,'\n');
	*cp = '\0';
E 62
I 62
D 83
	if (cp = index(cbuf,'\n'))
E 83
I 83
	if (cp = strchr(cbuf,'\n'))
E 83
		*cp = '\0';
E 62
D 65
	reply(500, "'%s': command not understood.",cbuf);
E 65
I 65
	reply(500, "'%s': command not understood.", cbuf);
E 65
E 39
}

I 81
void
E 81
delete(name)
	char *name;
{
	struct stat st;

I 81
	LOGCMD("delete", name);
E 81
	if (stat(name, &st) < 0) {
D 58
		reply(550, "%s: %s.", name, sys_errlist[errno]);
E 58
I 58
		perror_reply(550, name);
E 58
		return;
	}
	if ((st.st_mode&S_IFMT) == S_IFDIR) {
		if (rmdir(name) < 0) {
D 58
			reply(550, "%s: %s.", name, sys_errlist[errno]);
E 58
I 58
			perror_reply(550, name);
E 58
			return;
		}
		goto done;
	}
	if (unlink(name) < 0) {
D 58
		reply(550, "%s: %s.", name, sys_errlist[errno]);
E 58
I 58
		perror_reply(550, name);
E 58
		return;
	}
done:
	ack("DELE");
}

I 81
void
E 81
cwd(path)
	char *path;
{
I 85

E 85
D 64

	if (chdir(path) < 0) {
E 64
I 64
	if (chdir(path) < 0)
E 64
D 58
		reply(550, "%s: %s.", path, sys_errlist[errno]);
E 58
I 58
		perror_reply(550, path);
E 58
D 64
		return;
	}
	ack("CWD");
E 64
I 64
	else
		ack("CWD");
E 64
}

I 81
void
E 81
D 2
do_mkdir(name)
E 2
I 2
makedir(name)
E 2
	char *name;
{
I 85

E 85
I 81
	LOGCMD("mkdir", name);
E 81
I 2
D 57
	struct stat st;
	int dochown = stat(name, &st) < 0;
E 2
	
	if (mkdir(name, 0777) < 0) {
E 57
I 57
D 58
	uid_t	oldeuid;

	oldeuid = geteuid();
	seteuid(pw->pw_uid);
E 58
	if (mkdir(name, 0777) < 0)
E 57
D 58
		reply(550, "%s: %s.", name, sys_errlist[errno]);
E 58
I 58
		perror_reply(550, name);
E 58
D 57
		return;
	}
I 2
	if (dochown)
		(void) chown(name, pw->pw_uid, -1);
E 2
D 43
	ack("MKDIR");
E 43
I 43
	reply(257, "MKD command successful.");
E 57
I 57
	else
		reply(257, "MKD command successful.");
D 58
	seteuid(oldeuid);
E 58
E 57
E 43
}

I 81
void
E 81
D 2
do_rmdir(name)
E 2
I 2
removedir(name)
E 2
	char *name;
{
I 85

E 85
I 81
	LOGCMD("rmdir", name);
E 81
D 64

	if (rmdir(name) < 0) {
E 64
I 64
	if (rmdir(name) < 0)
E 64
D 58
		reply(550, "%s: %s.", name, sys_errlist[errno]);
E 58
I 58
		perror_reply(550, name);
E 58
D 64
		return;
	}
D 43
	ack("RMDIR");
E 43
I 43
	ack("RMD");
E 64
I 64
	else
		ack("RMD");
E 64
E 43
}

I 81
void
E 81
D 2
do_pwd()
E 2
I 2
pwd()
E 2
{
D 2
	char path[1024];
E 2
I 2
	char path[MAXPATHLEN + 1];
I 58
D 81
	extern char *getwd();
E 81
E 58
E 2
D 20
	char *p;
E 20

D 58
	if (getwd(path) == NULL) {
E 58
I 58
D 64
	if (getwd(path) == (char *)NULL) {
E 64
I 64
	if (getwd(path) == (char *)NULL)
E 64
E 58
D 43
		reply(451, "%s.", path);
E 43
I 43
		reply(550, "%s.", path);
E 43
D 64
		return;
	}
D 43
	reply(251, "\"%s\" is current directory.", path);
E 43
I 43
	reply(257, "\"%s\" is current directory.", path);
E 64
I 64
	else
		reply(257, "\"%s\" is current directory.", path);
E 64
E 43
}

char *
renamefrom(name)
	char *name;
{
	struct stat st;

	if (stat(name, &st) < 0) {
D 58
		reply(550, "%s: %s.", name, sys_errlist[errno]);
E 58
I 58
		perror_reply(550, name);
E 58
		return ((char *)0);
	}
D 2
	ack("RNFR");
E 2
I 2
	reply(350, "File exists, ready for destination name");
E 2
	return (name);
}

I 81
void
E 81
renamecmd(from, to)
	char *from, *to;
{
I 85

E 85
I 81
	LOGCMD2("rename", from, to);
E 81
D 64

	if (rename(from, to) < 0) {
E 64
I 64
	if (rename(from, to) < 0)
E 64
D 58
		reply(550, "rename: %s.", sys_errlist[errno]);
E 58
I 58
		perror_reply(550, "rename");
E 58
D 64
		return;
	}
	ack("RNTO");
E 64
I 64
	else
		ack("RNTO");
E 64
D 20
}

int guest;
/*
 * Test pathname for guest-user safety.
 */
inappropriate_request(name)
	char *name;
{
	int bogus = 0, depth = 0, length = strlen(name);
	char *p, *s;

	if (!guest)
		return (0);
	if (name[0] == '/' || name[0] == '|')
		bogus = 1;
	for (p = name; p < name+length;) {
		s = p;				/* start of token */
		while ( *p && *p!= '/')
			p++;
		*p = 0;
		if (strcmp(s, "..") == 0)
			depth -= 1;		/* backing up */
		else if (strcmp(s, ".") == 0)
			depth += 0;		/* no change */
		else
			depth += 1;		/* descending */
		if (depth < 0) {
			bogus = 1;
			break;
		}
	}
	if (bogus)
		reply(553, "%s: pathname disallowed guest users", name);
	return (bogus);
E 20
}

I 81
static void
E 81
D 25
/*
 * Convert network-format internet address
 * to base 256 d.d.d.d representation.
 */
char *
ntoa(in)
	struct in_addr in;
{
	static char b[18];
	register char *p;

D 18
	in.s_addr = ntohl(in.s_addr);
E 18
	p = (char *)&in;
#define	UC(b)	(((int)b)&0xff)
	sprintf(b, "%d.%d.%d.%d", UC(p[0]), UC(p[1]), UC(p[2]), UC(p[3]));
	return (b);
}

E 25
dolog(sin)
	struct sockaddr_in *sin;
{
D 58
	struct hostent *hp = gethostbyaddr(&sin->sin_addr,
E 58
I 58
	struct hostent *hp = gethostbyaddr((char *)&sin->sin_addr,
E 58
D 85
		sizeof (struct in_addr), AF_INET);
E 85
I 85
		sizeof(struct in_addr), AF_INET);
E 85
D 25
	char *remotehost;
E 25
D 58
	time_t t;
E 58
I 58
D 80
	time_t t, time();
E 58
I 41
	extern char *ctime();
E 80
E 41

D 25
	if (hp)
		remotehost = hp->h_name;
	else
D 23
		remotehost = "UNKNOWNHOST";
E 23
I 23
		remotehost = inet_ntoa(sin->sin_addr);
E 25
I 25
D 58
	if (hp) {
E 58
I 58
	if (hp)
E 58
D 41
		strncpy(remotehost, hp->h_name, sizeof (remotehost));
E 41
I 41
D 85
		(void) strncpy(remotehost, hp->h_name, sizeof (remotehost));
E 85
I 85
		(void) strncpy(remotehost, hp->h_name, sizeof(remotehost));
E 85
E 41
D 58
		endhostent();
	} else
E 58
I 58
	else
E 58
D 41
		strncpy(remotehost, inet_ntoa(sin->sin_addr),
E 41
I 41
		(void) strncpy(remotehost, inet_ntoa(sin->sin_addr),
E 41
D 85
		    sizeof (remotehost));
E 85
I 85
		    sizeof(remotehost));
E 85
D 65
	if (!logging)
		return;
E 25
E 23
D 41
	t = time(0);
D 2
	fprintf(stderr,"FTP %d: connection from %s at %s",
		getpid(), remotehost, ctime(&t));
E 2
I 2
D 21
	fprintf(stderr,"FTP: connection from %s at %s", remotehost, ctime(&t));
E 21
I 21
	fprintf(stderr,"FTPD: connection from %s at %s", remotehost, ctime(&t));
E 21
E 2
	fflush(stderr);
E 41
I 41
	t = time((time_t *) 0);
D 58
	syslog(LOG_INFO,"FTPD: connection from %s at %s", remotehost, ctime(&t));
E 58
I 58
	syslog(LOG_INFO, "connection from %s at %s",
	    remotehost, ctime(&t));
E 65
I 64
#ifdef SETPROCTITLE
D 65
	setproctitle("%s: connected", remotehost);
E 65
I 65
D 85
	sprintf(proctitle, "%s: connected", remotehost);
E 85
I 85
	snprintf(proctitle, sizeof(proctitle), "%s: connected", remotehost);
E 85
	setproctitle(proctitle);
E 65
#endif /* SETPROCTITLE */
I 65

D 80
	if (logging) {
		t = time((time_t *) 0);
		syslog(LOG_INFO, "connection from %s at %s",
		    remotehost, ctime(&t));
	}
E 80
I 80
	if (logging)
		syslog(LOG_INFO, "connection from %s", remotehost);
E 80
E 65
E 64
E 58
E 41
I 25
}

D 51
#include <utmp.h>

D 41
#define	SCPYN(a, b)	strncpy(a, b, sizeof (a))
E 41
I 41
#define	SCPYN(a, b)	(void) strncpy(a, b, sizeof (a))
E 41
struct	utmp utmp;

E 51
/*
D 51
 * Record login in wtmp file.
 */
dologin(pw)
	struct passwd *pw;
{
D 31
	int wtmp;
E 31
	char line[32];

D 31
	wtmp = open("/usr/adm/wtmp", O_WRONLY|O_APPEND);
E 31
I 31
D 33
	if (guest && (wtmp >= 0))
		lseek(wtmp, 0, L_XTND);
	else
		wtmp = open("/usr/adm/wtmp", O_WRONLY|O_APPEND);
E 33
E 31
	if (wtmp >= 0) {
		/* hack, but must be unique and no tty line */
D 41
		sprintf(line, "ftp%d", getpid());
E 41
I 41
		(void) sprintf(line, "ftp%d", getpid());
E 41
		SCPYN(utmp.ut_line, line);
		SCPYN(utmp.ut_name, pw->pw_name);
		SCPYN(utmp.ut_host, remotehost);
D 41
		utmp.ut_time = time(0);
E 41
I 41
		utmp.ut_time = (long) time((time_t *) 0);
E 41
		(void) write(wtmp, (char *)&utmp, sizeof (utmp));
D 31
		(void) close(wtmp);
E 31
I 31
D 32
		if (!guest)
			(void) close(wtmp);
E 32
I 32
D 33
		(void) close(wtmp);
E 33
I 33
		if (!guest) {		/* anon must hang on */
			(void) close(wtmp);
			wtmp = -1;
		}
E 33
E 32
E 31
	}
}

/*
E 51
 * Record logout in wtmp file
 * and exit with supplied status.
 */
I 81
void
E 81
dologout(status)
	int status;
{
I 85

E 85
I 32
D 51

E 51
E 32
D 31
	int wtmp;

E 31
D 35
	if (!logged_in)
D 29
		return;
E 29
I 29
D 32
		_exit(status);
E 32
I 32
		return;
E 32
E 29
	seteuid(0);
D 31
	wtmp = open("/usr/adm/wtmp", O_WRONLY|O_APPEND);
E 31
I 31
D 33
	if (guest && (wtmp >= 0))
		lseek(wtmp, 0, L_XTND);
	else
E 33
I 33
	if (wtmp < 0)
E 33
		wtmp = open("/usr/adm/wtmp", O_WRONLY|O_APPEND);
E 31
	if (wtmp >= 0) {
		SCPYN(utmp.ut_name, "");
		SCPYN(utmp.ut_host, "");
		utmp.ut_time = time(0);
		(void) write(wtmp, (char *)&utmp, sizeof (utmp));
		(void) close(wtmp);
E 35
I 35
	if (logged_in) {
D 58
		(void) seteuid(0);
E 58
I 58
		(void) seteuid((uid_t)0);
E 58
D 51
		if (wtmp < 0)
			wtmp = open("/usr/adm/wtmp", O_WRONLY|O_APPEND);
		if (wtmp >= 0) {
			SCPYN(utmp.ut_name, "");
			SCPYN(utmp.ut_host, "");
D 41
			utmp.ut_time = time(0);
E 41
I 41
			utmp.ut_time = (long) time((time_t *) 0);
E 41
			(void) write(wtmp, (char *)&utmp, sizeof (utmp));
			(void) close(wtmp);
		}
E 51
I 51
		logwtmp(ttyline, "", "");
E 51
E 35
	}
D 28
	exit(status);
E 28
I 28
	/* beware of flushing buffers after a SIGPIPE */
	_exit(status);
E 28
E 25
I 17
D 51
}

/*
 * Special version of popen which avoids
 * call to shell.  This insures noone may 
 * create a pipe to a hidden program as a side
 * effect of a list or dir command.
 */
#define	tst(a,b)	(*mode == 'r'? (b) : (a))
#define	RDR	0
#define	WTR	1
static	int popen_pid[5];

static char *
nextarg(cpp)
	char *cpp;
{
	register char *cp = cpp;

	if (cp == 0)
		return (cp);
	while (*cp && *cp != ' ' && *cp != '\t')
		cp++;
	if (*cp == ' ' || *cp == '\t') {
		*cp++ = '\0';
		while (*cp == ' ' || *cp == '\t')
			cp++;
	}
	if (cp == cpp)
		return ((char *)0);
	return (cp);
}

FILE *
popen(cmd, mode)
	char *cmd, *mode;
{
D 24
	int p[2], ac;
E 24
I 24
	int p[2], ac, gac;
E 24
	register myside, hisside, pid;
D 21
	char *av[10];
E 21
I 21
D 24
	char *av[512];
	char **pop, **popargs = NULL;
	extern char **glob();
E 24
I 24
	char *av[20], *gav[512];
E 24
E 21
	register char *cp;

	if (pipe(p) < 0)
		return (NULL);
	cp = cmd, ac = 0;
I 24
	/* break up string into pieces */
E 24
	do {
		av[ac++] = cp;
		cp = nextarg(cp);
D 24
	} while (cp && *cp);
E 24
I 24
	} while (cp && *cp && ac < 20);
E 24
	av[ac] = (char *)0;
I 21
D 24
	if (ac > 1) {
		popargs = glob(&av[1]);
		if (popargs == NULL)
			return (NULL);
		for (ac = 1, pop = popargs; *pop;) 
			av[ac++] = *pop++;
E 24
I 24
	gav[0] = av[0];
	/* glob each piece */
	for (gac = ac = 1; av[ac] != NULL; ac++) {
		char **pop;
D 37
		extern char **glob();
E 37
I 37
		extern char **glob(), **copyblk();
E 37

		pop = glob(av[ac]);
D 37
		if (pop) {
			av[ac] = (char *)pop;		/* save to free later */
			while (*pop && gac < 512)
				gav[gac++] = *pop++;
E 37
I 37
		if (pop == (char **)NULL) {	/* globbing failed */
			char *vv[2];

			vv[0] = av[ac];
			vv[1] = 0;
			pop = copyblk(vv);
E 37
		}
I 37
		av[ac] = (char *)pop;		/* save to free later */
		while (*pop && gac < 512)
			gav[gac++] = *pop++;
E 37
E 24
	}
D 24
	av[ac] = (char *)0;
E 24
I 24
	gav[gac] = (char *)0;
E 24
E 21
	myside = tst(p[WTR], p[RDR]);
	hisside = tst(p[RDR], p[WTR]);
	if ((pid = fork()) == 0) {
		/* myside and hisside reverse roles in child */
D 41
		close(myside);
		dup2(hisside, tst(0, 1));
		close(hisside);
E 41
I 41
		(void) close(myside);
		(void) dup2(hisside, tst(0, 1));
		(void) close(hisside);
E 41
D 24
		execv(av[0], av);
E 24
I 24
		execv(gav[0], gav);
E 24
		_exit(1);
	}
I 21
D 24
	if (popargs != NULL)
		blkfree(popargs);
E 24
I 24
	for (ac = 1; av[ac] != NULL; ac++)
		blkfree((char **)av[ac]);
E 24
E 21
	if (pid == -1)
		return (NULL);
	popen_pid[myside] = pid;
D 41
	close(hisside);
E 41
I 41
	(void) close(hisside);
E 41
	return (fdopen(myside, mode));
}

pclose(ptr)
	FILE *ptr;
{
	register f, r, (*hstat)(), (*istat)(), (*qstat)();
	int status;

	f = fileno(ptr);
D 41
	fclose(ptr);
E 41
I 41
	(void) fclose(ptr);
E 41
	istat = signal(SIGINT, SIG_IGN);
	qstat = signal(SIGQUIT, SIG_IGN);
	hstat = signal(SIGHUP, SIG_IGN);
	while ((r = wait(&status)) != popen_pid[f] && r != -1)
		;
	if (r == -1)
		status = -1;
D 41
	signal(SIGINT, istat);
	signal(SIGQUIT, qstat);
	signal(SIGHUP, hstat);
E 41
I 41
	(void) signal(SIGINT, istat);
	(void) signal(SIGQUIT, qstat);
	(void) signal(SIGHUP, hstat);
E 41
	return (status);
E 51
}

I 78
D 81
void
E 78
D 58
/*
 * Check user requesting login priviledges.
I 45
 * Disallow anyone who does not have a standard
 * shell returned by getusershell() (/etc/shells).
E 45
 * Disallow anyone mentioned in the file FTPUSERS
 * to allow people such as uucp to be avoided.
 */
checkuser(name)
	register char *name;
{
D 45
	char line[BUFSIZ], *index();
E 45
I 45
	register char *cp;
D 54
	char line[BUFSIZ], *index(), *getusershell();
E 54
E 45
	FILE *fd;
I 45
D 54
	struct passwd *pw;
E 54
I 54
	struct passwd *p;
	char *shell;
E 54
E 45
	int found = 0;
I 54
	char line[BUFSIZ], *index(), *getusershell();
E 54

I 45
D 54
	pw = getpwnam(name);
	if (pw == NULL)
E 54
I 54
	if ((p = getpwnam(name)) == NULL)
E 54
		return (0);
I 46
D 54
	if (pw ->pw_shell == NULL || pw->pw_shell[0] == NULL)
		pw->pw_shell = "/bin/sh";
E 54
I 54
	if ((shell = p->pw_shell) == NULL || *shell == 0)
		shell = "/bin/sh";
E 54
E 46
	while ((cp = getusershell()) != NULL)
D 54
		if (strcmp(cp, pw->pw_shell) == 0)
E 54
I 54
		if (strcmp(cp, shell) == 0)
E 54
			break;
D 46
	endpwent();
E 46
	endusershell();
	if (cp == NULL)
		return (0);
E 45
D 54
	fd = fopen(FTPUSERS, "r");
	if (fd == NULL)
E 54
I 54
	if ((fd = fopen(FTPUSERS, "r")) == NULL)
E 54
		return (1);
	while (fgets(line, sizeof (line), fd) != NULL) {
D 45
		register char *cp = index(line, '\n');

E 45
I 45
D 54
		cp = index(line, '\n');
E 45
		if (cp)
E 54
I 54
		if ((cp = index(line, '\n')) != NULL)
E 54
			*cp = '\0';
		if (strcmp(line, name) == 0) {
			found++;
			break;
		}
	}
D 41
	fclose(fd);
E 41
I 41
	(void) fclose(fd);
E 41
	return (!found);
I 39
}

E 58
myoob()
E 81
I 81
static void
myoob(signo)
	int signo;
E 81
{
D 40
	char mark, *cp;
	int aflag = 0, count = 0, iacflag = 0, c;
E 40
I 40
D 41
	int aflag = 0, count = 0, iacflag = 0, atmark;
E 41
I 41
D 44
	int aflag = 0, atmark;
E 41
	char c, *cp;
E 44
I 44
	char *cp;
E 44
E 40

I 44
	/* only process if transfer occurring */
E 44
D 58
	if (!transflag) {
E 58
I 58
	if (!transflag)
E 58
D 44
		for (;;) {
D 40
			if (ioctl(fileno(stdin), SIOCATMARK, &mark) < 0) {
E 40
I 40
D 41
			if (ioctl(fileno(stdin), SIOCATMARK, &atmark) < 0) {
E 40
				perror("ioctl");
E 41
I 41
			if (ioctl(fileno(stdin), (int) SIOCATMARK, (char *) &atmark) < 0) {
				syslog(LOG_ERR, "ioctl: %m");
E 41
				break;
			}
D 40
			if (mark) {
E 40
I 40
			if (atmark)
E 40
				break;
D 40
			}
			read(fileno(stdin), &mark, 1);
			c = 0377 & mark;
E 40
I 40
D 41
			read(fileno(stdin), &c, 1);
E 41
I 41
			(void) read(fileno(stdin), &c, 1);
E 41
E 40
		}
D 40
		recv(fileno(stdin), &mark, 1, MSG_OOB);
		c = 0377 & mark;
		read(fileno(stdin), &mark, 1);
E 40
I 40
D 41
		recv(fileno(stdin), &c, 1, MSG_OOB);
		read(fileno(stdin), &c, 1);
E 41
I 41
		(void) recv(fileno(stdin), &c, 1, MSG_OOB);
		(void) read(fileno(stdin), &c, 1);
E 44
E 41
E 40
		return;
D 58
	}
E 58
D 44
	for (;;) {
D 40
		if (ioctl(fileno(stdin), SIOCATMARK, &mark) < 0) {
E 40
I 40
D 41
		if (ioctl(fileno(stdin), SIOCATMARK, &atmark) < 0) {
E 40
			perror("ioctl");
E 41
I 41
		if (ioctl(fileno(stdin), (int) SIOCATMARK, (char *) &atmark) < 0) {
			syslog(LOG_ERR, "ioctl: %m");
E 41
			break;
		}
D 40
		if (mark) {
E 40
I 40
		if (atmark)
E 40
			break;
D 40
		}
		read(fileno(stdin), &mark, 1);
		c = 0377 & mark;
		if (c == IAC) {
E 40
I 40
D 41
		read(fileno(stdin), &c, 1);
E 41
I 41
		(void) read(fileno(stdin), &c, 1);
E 41
		if (c == IAC || c == IP)
E 40
			aflag++;
D 40
		}
		else if (c == IP) {
			aflag++;
		}
E 40
	}
D 40
	recv(fileno(stdin), &mark, 1, MSG_OOB);
	c = 0377 & mark;
	if (c == IAC) {
E 40
I 40
D 41
	recv(fileno(stdin), &c, 1, MSG_OOB);
E 41
I 41
	(void) recv(fileno(stdin), &c, 1, MSG_OOB);
E 41
	if (c == IAC)
E 40
		aflag++;
D 40
	}
	read(fileno(stdin), &mark, 1);
	c = 0377 & mark;
	if (c == DM) {
E 40
I 40
D 41
	read(fileno(stdin), &c, 1);
E 41
I 41
	(void) read(fileno(stdin), &c, 1);
E 41
	if (c == DM)
E 40
		aflag++;
D 40
	}
	if (aflag != 4) {
E 40
I 40
	if (aflag != 4)
E 40
		return;
E 44
D 40
	}
E 40
	cp = tmpline;
D 44
	(void) getline(cp, 7, stdin);
E 44
I 44
	if (getline(cp, 7, stdin) == NULL) {
D 58
		reply(221, "You could at least say goodby.");
E 58
I 58
		reply(221, "You could at least say goodbye.");
E 58
		dologout(0);
	}
E 44
	upper(cp);
D 40
	if (strcmp(cp, "ABOR\r\n")) {
E 40
I 40
D 65
	if (strcmp(cp, "ABOR\r\n"))
E 40
		return;
D 40
	}
E 40
	tmpline[0] = '\0';
	reply(426,"Transfer aborted. Data connection closed.");
	reply(226,"Abort successful");
	longjmp(urgcatch, 1);
E 65
I 65
	if (strcmp(cp, "ABOR\r\n") == 0) {
		tmpline[0] = '\0';
		reply(426, "Transfer aborted. Data connection closed.");
		reply(226, "Abort successful");
		longjmp(urgcatch, 1);
	}
	if (strcmp(cp, "STAT\r\n") == 0) {
		if (file_size != (off_t) -1)
D 81
			reply(213, "Status: %lu of %lu bytes transferred",
E 81
I 81
			reply(213, "Status: %qd of %qd bytes transferred",
E 81
			    byte_count, file_size);
		else
D 81
			reply(213, "Status: %lu bytes transferred", byte_count);
E 81
I 81
			reply(213, "Status: %qd bytes transferred", byte_count);
E 81
	}
E 65
}

I 43
/*
D 64
 * Note: The 530 reply codes could be 4xx codes, except nothing is
 * given in the state tables except 421 which implies an exit.  (RFC959)
E 64
I 64
 * Note: a response of 425 is not mentioned as a possible response to
D 80
 * 	the PASV command in RFC959. However, it has been blessed as
 * 	a legitimate response by Jon Postel in a telephone conversation
E 80
I 80
 *	the PASV command in RFC959. However, it has been blessed as
 *	a legitimate response by Jon Postel in a telephone conversation
E 80
 *	with Rick Adams on 25 Jan 89.
E 64
 */
I 81
void
E 81
E 43
passive()
{
	int len;
D 65
	struct sockaddr_in tmp;
E 65
D 85
	register char *p, *a;
E 85
I 85
	char *p, *a;
E 85

	pdata = socket(AF_INET, SOCK_STREAM, 0);
	if (pdata < 0) {
D 43
		reply(451, "Can't open passive connection");
E 43
I 43
D 64
		reply(530, "Can't open passive connection");
E 64
I 64
		perror_reply(425, "Can't open passive connection");
E 64
E 43
		return;
	}
D 65
	tmp = ctrl_addr;
	tmp.sin_port = 0;
E 65
I 65
	pasv_addr = ctrl_addr;
	pasv_addr.sin_port = 0;
E 65
D 58
	seteuid(0);
E 58
I 58
	(void) seteuid((uid_t)0);
E 58
D 41
	if (bind(pdata, (char *) &tmp, sizeof(tmp), 0) < 0) {
E 41
I 41
D 65
	if (bind(pdata, (struct sockaddr *) &tmp, sizeof(tmp)) < 0) {
E 65
I 65
	if (bind(pdata, (struct sockaddr *)&pasv_addr, sizeof(pasv_addr)) < 0) {
E 65
E 41
D 58
		seteuid(pw->pw_uid);
E 58
I 58
		(void) seteuid((uid_t)pw->pw_uid);
E 58
D 64
		(void) close(pdata);
		pdata = -1;
D 43
		reply(451, "Can't open passive connection");
E 43
I 43
		reply(530, "Can't open passive connection");
E 43
		return;
E 64
I 64
		goto pasv_error;
E 64
	}
D 58
	seteuid(pw->pw_uid);
E 58
I 58
	(void) seteuid((uid_t)pw->pw_uid);
E 58
D 65
	len = sizeof(tmp);
D 58
	if (getsockname(pdata, (char *) &tmp, &len) < 0) {
E 58
I 58
D 64
	if (getsockname(pdata, (struct sockaddr *) &tmp, &len) < 0) {
E 58
		(void) close(pdata);
		pdata = -1;
D 43
		reply(451, "Can't open passive connection");
E 43
I 43
		reply(530, "Can't open passive connection");
E 43
		return;
	}
	if (listen(pdata, 1) < 0) {
		(void) close(pdata);
		pdata = -1;
D 43
		reply(451, "Can't open passive connection");
E 43
I 43
		reply(530, "Can't open passive connection");
E 43
		return;
	}
E 64
I 64
	if (getsockname(pdata, (struct sockaddr *) &tmp, &len) < 0)
E 65
I 65
	len = sizeof(pasv_addr);
	if (getsockname(pdata, (struct sockaddr *) &pasv_addr, &len) < 0)
E 65
		goto pasv_error;
	if (listen(pdata, 1) < 0)
		goto pasv_error;
E 64
D 65
	a = (char *) &tmp.sin_addr;
	p = (char *) &tmp.sin_port;
E 65
I 65
	a = (char *) &pasv_addr.sin_addr;
	p = (char *) &pasv_addr.sin_port;
E 65

#define UC(b) (((int) b) & 0xff)

	reply(227, "Entering Passive Mode (%d,%d,%d,%d,%d,%d)", UC(a[0]),
		UC(a[1]), UC(a[2]), UC(a[3]), UC(p[0]), UC(p[1]));
I 64
	return;

pasv_error:
	(void) close(pdata);
	pdata = -1;
	perror_reply(425, "Can't open passive connection");
	return;
E 64
}

I 58
/*
 * Generate unique name for file with basename "local".
 * The file named "local" is already known to exist.
 * Generates failure reply on error.
 */
E 58
D 81
char *
E 81
I 81
static char *
E 81
gunique(local)
	char *local;
{
	static char new[MAXPATHLEN];
I 58
	struct stat st;
E 58
D 81
	char *cp = rindex(local, '/');
D 64
	int d, count=0;
E 64
I 64
D 65
	int count=0;
E 65
I 65
	int count = 0;
E 81
I 81
	int count;
	char *cp;
E 81
E 65
E 64
D 58
	char ext = '1';
E 58

I 81
D 83
	cp = rindex(local, '/');
E 83
I 83
	cp = strrchr(local, '/');
E 83
E 81
D 58
	if (cp) {
E 58
I 58
	if (cp)
E 58
		*cp = '\0';
D 58
	}
	d = access(cp ? local : ".", 2);
	if (cp) {
E 58
I 58
D 64
	d = stat(cp ? local : ".", &st);
	if (cp)
E 58
		*cp = '/';
D 58
	}
E 58
	if (d < 0) {
E 64
I 64
	if (stat(cp ? local : ".", &st) < 0) {
E 64
D 41
		perror(local);
E 41
I 41
D 58
		syslog(LOG_ERR, "%s: %m", local);
E 58
I 58
D 65
		perror_reply(553, local);
E 65
I 65
		perror_reply(553, cp ? local : ".");
E 65
E 58
E 41
D 85
		return((char *) 0);
E 85
I 85
		return ((char *) 0);
E 85
	}
I 64
	if (cp)
		*cp = '/';
E 64
	(void) strcpy(new, local);
	cp = new + strlen(new);
	*cp++ = '.';
D 58
	while (!d) {
		if (++count == 100) {
D 43
			reply(451, "Unique file name not cannot be created.");
E 43
I 43
			reply(452, "Unique file name not cannot be created.");
E 43
			return((char *) 0);
		}
		*cp++ = ext;
		*cp = '\0';
		if (ext == '9') {
			ext = '0';
		}
		else {
			ext++;
		}
		if ((d = access(new, 0)) < 0) {
			break;
		}
		if (ext != '0') {
			cp--;
		}
		else if (*(cp - 2) == '.') {
			*(cp - 1) = '1';
		}
		else {
			*(cp - 2) = *(cp - 2) + 1;
			cp--;
		}
E 58
I 58
	for (count = 1; count < 100; count++) {
D 81
		(void) sprintf(cp, "%d", count);
E 81
I 81
		(void)sprintf(cp, "%d", count);
E 81
		if (stat(new, &st) < 0)
D 85
			return(new);
E 85
I 85
			return (new);
E 85
E 58
	}
D 58
	return(new);
E 58
I 58
	reply(452, "Unique file name cannot be created.");
D 81
	return((char *) 0);
E 81
I 81
D 85
	return(NULL);
E 85
I 85
	return (NULL);
E 85
E 81
}

/*
 * Format and send reply containing system error number.
 */
I 81
void
E 81
perror_reply(code, string)
	int code;
	char *string;
{
I 85

E 85
D 64

E 64
D 74
	if (errno < sys_nerr)
		reply(code, "%s: %s.", string, sys_errlist[errno]);
	else
		reply(code, "%s: unknown error %d.", string, errno);
E 74
I 74
	reply(code, "%s: %s.", string, strerror(errno));
E 74
E 58
E 39
E 17
}
I 64

static char *onefile[] = {
	"",
	0
};

I 81
void
E 81
D 85
send_file_list(whichfiles)
	char *whichfiles;
E 85
I 85
send_file_list(whichf)
	char *whichf;
E 85
{
	struct stat st;
	DIR *dirp = NULL;
D 78
	struct direct *dir;
E 78
I 78
	struct dirent *dir;
E 78
	FILE *dout = NULL;
D 85
	register char **dirlist, *dirname;
E 85
I 85
	char **dirlist, *dirname;
E 85
I 67
	int simple = 0;
I 85
	int freeglob = 0;
	glob_t gl;
E 85
E 67
D 81
	char *strpbrk();
E 81

D 85
	if (strpbrk(whichfiles, "~{[*?") != NULL) {
D 78
		extern char **glob(), *globerr;
E 78
I 78
D 81
		extern char **ftpglob(), *globerr;
E 81
I 81
		extern char *globerr;
E 85
I 85
	if (strpbrk(whichf, "~{[*?") != NULL) {
I 86
		int flags = GLOB_BRACE|GLOB_NOCHECK|GLOB_QUOTE|GLOB_TILDE;
E 86
E 85
E 81
E 78
I 65

E 65
D 85
		globerr = NULL;
D 78
		dirlist = glob(whichfiles);
E 78
I 78
		dirlist = ftpglob(whichfiles);
E 78
		if (globerr != NULL) {
			reply(550, globerr);
			return;
		} else if (dirlist == NULL) {
E 85
I 85
		memset(&gl, 0, sizeof(gl));
		freeglob = 1;
D 86
		if (glob(whichf, GLOB_BRACE|GLOB_QUOTE|GLOB_TILDE, 0, &gl)) {
E 86
I 86
		if (glob(whichf, flags, 0, &gl)) {
E 86
			reply(550, "not found");
			goto out;
		} else if (gl.gl_pathc == 0) {
E 85
			errno = ENOENT;
D 85
			perror_reply(550, whichfiles);
			return;
E 85
I 85
			perror_reply(550, whichf);
			goto out;
E 85
		}
I 85
		dirlist = gl.gl_pathv;
E 85
	} else {
D 85
		onefile[0] = whichfiles;
E 85
I 85
		onefile[0] = whichf;
E 85
		dirlist = onefile;
I 67
		simple = 1;
E 67
	}
D 65
	
E 65
I 65

	if (setjmp(urgcatch)) {
		transflag = 0;
D 85
		return;
E 85
I 85
		goto out;
E 85
	}
E 65
	while (dirname = *dirlist++) {
		if (stat(dirname, &st) < 0) {
I 65
			/*
			 * If user typed "ls -l", etc, and the client
			 * used NLST, do what the user meant.
			 */
			if (dirname[0] == '-' && *dirlist == NULL &&
			    transflag == 0) {
				retrieve("/bin/ls %s", dirname);
D 85
				return;
E 85
I 85
				goto out;
E 85
			}
E 65
D 85
			perror_reply(550, whichfiles);
E 85
I 85
			perror_reply(550, whichf);
E 85
			if (dout != NULL) {
				(void) fclose(dout);
I 65
				transflag = 0;
E 65
				data = -1;
				pdata = -1;
			}
D 85
			return;
E 85
I 85
			goto out;
E 85
		}
D 65
			
E 65
I 65

E 65
D 85
		if ((st.st_mode&S_IFMT) == S_IFREG) {
E 85
I 85
		if (S_ISREG(st.st_mode)) {
E 85
			if (dout == NULL) {
D 67
				dout = dataconn(whichfiles, (off_t)-1, "w");
E 67
I 67
				dout = dataconn("file list", (off_t)-1, "w");
E 67
				if (dout == NULL)
D 85
					return;
E 85
I 85
					goto out;
E 85
I 65
				transflag++;
E 65
			}
D 69
			fprintf(dout, "%s\n", dirname);
E 69
I 69
			fprintf(dout, "%s%s\n", dirname,
				type == TYPE_A ? "\r" : "");
E 69
I 65
			byte_count += strlen(dirname) + 1;
E 65
			continue;
D 65
		} else if ((st.st_mode&S_IFMT) != S_IFDIR) 
E 65
I 65
D 85
		} else if ((st.st_mode&S_IFMT) != S_IFDIR)
E 85
I 85
		} else if (!S_ISDIR(st.st_mode))
E 85
E 65
			continue;

		if ((dirp = opendir(dirname)) == NULL)
			continue;

		while ((dir = readdir(dirp)) != NULL) {
D 65
			char nbuf[BUFSIZ];
E 65
I 65
			char nbuf[MAXPATHLEN];
E 65

			if (dir->d_name[0] == '.' && dir->d_namlen == 1)
				continue;
D 65
			if (dir->d_name[0] == '.' && dir->d_name[1] == '.'
			    && dir->d_namlen == 2)
E 65
I 65
			if (dir->d_name[0] == '.' && dir->d_name[1] == '.' &&
			    dir->d_namlen == 2)
E 65
				continue;

D 65
			sprintf(nbuf, "%s/%s", dirname, dir->d_name); 
			
E 65
I 65
			sprintf(nbuf, "%s/%s", dirname, dir->d_name);

E 65
			/*
D 65
			 * we have to do a stat to insure it's
			 * not a directory
E 65
I 65
			 * We have to do a stat to insure it's
			 * not a directory or special file.
E 65
			 */
D 67
			if (stat(nbuf, &st) == 0 &&
			    (st.st_mode&S_IFMT) == S_IFREG) {
E 67
I 67
			if (simple || (stat(nbuf, &st) == 0 &&
D 85
			    (st.st_mode&S_IFMT) == S_IFREG)) {
E 85
I 85
			    S_ISREG(st.st_mode))) {
E 85
E 67
				if (dout == NULL) {
D 67
					dout = dataconn(whichfiles, (off_t)-1,
E 67
I 67
					dout = dataconn("file list", (off_t)-1,
E 67
						"w");
					if (dout == NULL)
D 85
						return;
E 85
I 85
						goto out;
E 85
I 65
					transflag++;
E 65
				}
				if (nbuf[0] == '.' && nbuf[1] == '/')
D 69
					fprintf(dout, "%s\n", &nbuf[2]);
E 69
I 69
					fprintf(dout, "%s%s\n", &nbuf[2],
						type == TYPE_A ? "\r" : "");
E 69
				else
D 69
					fprintf(dout, "%s\n", nbuf);
E 69
I 69
					fprintf(dout, "%s%s\n", nbuf,
						type == TYPE_A ? "\r" : "");
E 69
I 65
				byte_count += strlen(nbuf) + 1;
E 65
			}
		}
		(void) closedir(dirp);
	}

D 65
	if (dout != NULL && ferror(dout) != 0)
		perror_reply(550, whichfiles);
	else 
E 65
I 65
	if (dout == NULL)
		reply(550, "No files found.");
	else if (ferror(dout) != 0)
		perror_reply(550, "Data connection");
	else
E 65
		reply(226, "Transfer complete.");

D 65
	if (dout != NULL) 
E 65
I 65
	transflag = 0;
	if (dout != NULL)
E 65
		(void) fclose(dout);
	data = -1;
	pdata = -1;
I 85
out:
	if (freeglob) {
		freeglob = 0;
		globfree(&gl);
	}
E 85
}

#ifdef SETPROCTITLE
/*
D 81
 * clobber argv so ps will show what we're doing.
 * (stolen from sendmail)
 * warning, since this is usually started from inetd.conf, it
 * often doesn't have much of an environment or arglist to overwrite.
E 81
I 81
 * Clobber argv so ps will show what we're doing.  (Stolen from sendmail.)
 * Warning, since this is usually started from inetd.conf, it often doesn't
 * have much of an environment or arglist to overwrite.
E 81
 */
D 81

/*VARARGS1*/
setproctitle(fmt, a, b, c)
char *fmt;
E 81
I 81
void
#if __STDC__
setproctitle(const char *fmt, ...)
#else
setproctitle(fmt, va_alist)
	char *fmt;
        va_dcl
#endif
E 81
{
D 85
	register char *p, *bp, ch;
	register int i;
E 85
I 85
	int i;
E 85
I 81
	va_list ap;
E 81
D 85
	char buf[BUFSIZ];
E 85
I 85
	char *p, *bp, ch;
	char buf[LINE_MAX];

E 85
D 81

	(void) sprintf(buf, fmt, a, b, c);
E 81
I 81
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)vsnprintf(buf, sizeof(buf), fmt, ap);
E 81

	/* make ps print our process name */
	p = Argv[0];
	*p++ = '-';

	i = strlen(buf);
	if (i > LastArgv - p - 2) {
		i = LastArgv - p - 2;
		buf[i] = '\0';
	}
	bp = buf;
	while (ch = *bp++)
		if (ch != '\n' && ch != '\r')
			*p++ = ch;
	while (p < LastArgv)
		*p++ = ' ';
}
#endif /* SETPROCTITLE */
E 64
E 1
