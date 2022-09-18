h13178
s 00005/00008/00725
d D 8.2 95/04/28 14:31:00 bostic 102 101
c add a '--' option before the user name, to avoid rlogin -l '-froot'
c use execle to pass the fabricated environment, quit whacking 'environ'
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00005/00005/00728
d D 8.1 93/06/04 18:59:10 bostic 101 100
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00732
d D 5.57 92/10/04 17:03:37 bostic 100 99
c don't write out the trailing NULL
e
s 00003/00004/00730
d D 5.56 92/07/01 20:04:46 bostic 99 98
c iruserok() calls __icheckhost which now calls gethostbyname which
c overwrites our hostname
e
s 00004/00011/00730
d D 5.55 92/06/29 14:37:41 bostic 98 97
c lint fix to signals
e
s 00094/00100/00647
d D 5.54 92/06/29 12:42:14 leres 97 95
c use iruserok, not ruserok, minor ANSI cleanups
e
s 00000/00053/00694
d D 5.53.1.1 91/08/20 17:10:59 mckusick 96 95
c delete data-stream encryption for the foreign sites (Network, Release 2)
e
s 00002/00002/00745
d D 5.53 91/04/20 10:42:45 karels 95 94
c it's really 666, not whatever the default is
e
s 00003/00013/00744
d D 5.52 91/04/12 14:22:59 bostic 94 93
c lost redist include line somewhere along the way
e
s 00027/00030/00730
d D 5.51 91/03/04 15:50:41 bostic 93 90
c ANSI
e
s 00031/00044/00716
d R 5.51 91/02/25 17:24:28 bostic 92 90
c ANSI fixes (one real bug!)
e
s 00000/00053/00707
d D 5.50.1.1 90/10/21 20:16:16 mckusick 91 90
c delete data-stream encryption for the foreign sites (4.3-Reno)
e
s 00012/00004/00748
d D 5.50 90/10/21 20:15:26 mckusick 90 89
c use ifdefs that unifdef understands
e
s 00011/00007/00741
d D 5.49 90/09/27 21:55:45 mckusick 89 88
c break out -x (encrypted sessions) with #ifdef CRYPT
e
s 00017/00056/00731
d D 5.48 90/06/27 22:57:43 marc 88 87
c use pty library
e
s 00008/00001/00779
d D 5.47 90/06/27 22:41:30 karels 87 86
c set IP type of service; minor kerberos touchups
e
s 00011/00003/00769
d D 5.46 90/06/21 14:31:19 kfall 86 85
c add ROOT login syslog message
e
s 00002/00002/00770
d D 5.45 90/06/19 15:59:25 bostic 85 84
c TCSADFLUSH -> TCSAFLUSH
e
s 00001/00000/00771
d D 5.44 90/06/07 10:36:35 bostic 84 83
c add FD_ZERO of ebits
e
s 00009/00014/00762
d D 5.43 90/05/21 15:06:22 bostic 83 82
c don't allow root login on unsecure terminal
e
s 00001/00001/00775
d D 5.42 90/05/15 19:47:45 bostic 82 81
c string.h is ANSI C include file
e
s 00001/00000/00775
d D 5.41 90/05/11 23:05:00 kfall 81 80
c now depends on kerberosIV/des.h
e
s 00054/00032/00721
d D 5.40 90/04/13 13:03:46 karels 80 78
c don't sleep(5) because of over-aggressive attempt to write;
c minor performance hacks with select; don't send \01 after null (fatal()
c after confirm, and don't drop the line feed
e
s 00001/00001/00646
d D 5.22.1.8 89/10/02 18:23:51 marc 79 76
c fix to network release version -- *don't* TIOCNOTTY
e
s 00061/00072/00692
d D 5.39 89/10/02 18:21:52 bostic 78 77
c checkpoint for bostic (by marc) -- making fixes to branch for network release
e
s 00021/00026/00743
d D 5.38 89/09/11 21:03:17 karels 77 75
c change local_domain to check only that last two components of domain match;
c add -a to check host addr vs. name always
e
s 00070/00012/00577
d D 5.22.1.7 89/09/11 21:02:09 karels 76 70
c change local_domain to check only that last two components of domain match;
c add -a to check host addr vs. name always
e
s 00041/00028/00728
d D 5.37 89/09/06 14:13:00 karels 75 74
c add -a to validate all incoming host addresses; redefine "local"
c domain to include any domains with two most-significant components in common
e
s 00035/00004/00721
d D 5.36 89/08/21 23:14:54 kfall 74 73
c remove POSIX_JOB_CONTROL #ifdefs (which were never defined--oops)
e
s 00009/00010/00716
d D 5.35 89/04/02 14:43:11 bostic 73 72
c add pathnames.h
e
s 00008/00025/00718
d D 5.34 89/02/09 22:50:17 kfall 72 71
c encrypted rlogin on different port; use nulls as 1st char
e
s 00000/00003/00743
d D 5.33 89/02/08 19:54:40 kfall 71 69
c don't need kntoln (remove)
e
s 00028/00047/00561
d D 5.22.1.6 89/02/07 16:23:06 karels 70 65
i 69 66
c on branch, sync with 5.32
e
s 00027/00000/00719
d D 5.32 89/02/07 16:08:25 karels 69 68
c log and ignore source-routing on incoming connections
e
s 00000/00000/00719
d D 5.31 89/01/27 17:35:18 kfall 68 67
c no change
e
s 00023/00019/00696
d D 5.30 89/01/26 18:27:16 kfall 67 66
c make work with Kerberos again
e
s 00020/00023/00695
d D 5.29 89/01/25 22:27:10 karels 66 64
c host address "names" are also ok
e
s 00006/00004/00555
d D 5.22.1.5 89/01/25 22:24:58 karels 65 62
c per kfall, nonlocal is ok
e
s 00022/00018/00696
d D 5.28 89/01/25 21:16:50 kfall 64 63
c host considered ok if not in local domain
e
s 00011/00013/00703
d D 5.27 89/01/25 20:51:06 karels 63 61
c more cleanup
e
s 00058/00009/00501
d D 5.22.1.4 89/01/25 20:47:36 karels 62 57
c sync with current (non-branch) version
e
s 00058/00056/00658
d D 5.26 89/01/25 20:30:39 karels 61 59
c clean up host address validation code
e
s 00057/00055/00659
d R 5.26 89/01/25 20:29:32 karels 60 59
c cleanup host address validation
e
s 00050/00008/00664
d D 5.25 89/01/25 17:25:15 kfall 59 58
c fix logging, etc.
e
s 00000/00000/00672
d D 5.24 89/01/24 16:37:19 kfall 58 56
c double check host name returned by gethostbyaddr, more logging
e
s 00002/00002/00508
d D 5.22.1.3 89/01/07 21:49:41 karels 57 55
c hmm, kevin says "login -p -f -h host username" loses (or wins!) with old login
e
s 00069/00031/00603
d D 5.23 89/01/07 03:08:24 kfall 56 53
c fix exec /bin/login line (order of args is important!), 
c use kuserok instead of ruserok for kerberos 
c add -k (kerberos) and -v (vacuous) flags
e
s 00004/00183/00506
d D 5.22.1.2 89/01/06 19:51:55 karels 55 54
c on branch, remove TERMIOS and KERBEROS #ifdefs for network release
e
s 00055/00000/00634
d D 5.22.1.1 89/01/06 19:49:05 karels 54 53
c start branch for network release, add #ifdefs for TERMIOS and OLD_LOGIN
e
s 00053/00077/00581
d D 5.22 89/01/06 19:45:29 karels 53 52
c finish cleanup/reformatting, remove nouser
e
s 00071/00075/00587
d D 5.21 89/01/06 17:19:25 karels 52 51
c hacks to make select more efficient, some reformatting
e
s 00000/00000/00662
d D 5.20 88/12/20 21:26:10 kfall 51 50
c handle entire 'rlogin protocol' in rlogind
e
s 00273/00012/00389
d D 5.19 88/12/20 21:23:21 kfall 50 49
c add Kerberos ifdefs, marc's posix job control stuff, and handle
e
s 00018/00001/00383
d D 5.18 88/12/08 09:24:31 bostic 49 48
c add -l flag to turn off rhosts
e
s 00017/00006/00367
d D 5.17 88/08/31 11:57:35 bostic 48 47
c rmut was probably AT&T; nothing else is, add Berkeley specific copyright
e
s 00010/00059/00363
d D 5.16 88/08/31 11:55:33 bostic 47 46
c use library version of rmut
e
s 00000/00002/00422
d D 5.15 88/05/23 19:41:27 bostic 46 45
c remove vhangup on exit
e
s 00033/00021/00391
d D 5.14 88/05/22 16:39:58 bostic 45 44
c fix security problem with pty's
e
s 00002/00001/00410
d D 5.13 87/09/09 16:09:32 karels 44 42
c don't accept connections from ports below 512
e
s 00002/00001/00410
d R 5.13 87/09/04 17:46:18 karels 43 42
c don't accept connections from ports below 512
e
s 00001/00000/00410
d D 5.12 87/03/10 16:53:38 mckusick 42 41
c eliminate race in cleanup (4.3BSD/etc/49 from Jeff Smith <aat@j.cc.purdue.edu>)
e
s 00009/00009/00401
d D 5.11 86/05/23 14:40:24 mckusick 41 40
c must be word aligned
e
s 00019/00004/00391
d D 5.10 86/01/07 19:29:32 karels 40 39
c use select on exceptional condition on pty to detect flush faster
e
s 00019/00032/00376
d D 5.9 85/11/08 08:32:50 karels 39 38
c only need to indicate window knowledge in oob messages
c until we get a response; close hole in message after control correctly;
c remove sun grot and other useless code
e
s 00000/00001/00408
d D 5.8 85/10/22 18:43:03 bloom 38 37
c be more social about killing attached processes (vhangup takes care of it)
c (from sun!guy)
e
s 00004/00001/00405
d D 5.7 85/09/17 23:13:07 mckusick 37 35
c take responsibility for reseting window size when first opening pty;
c send window size capability in every oob message in case first is lost
e
s 00004/00001/00405
d R 5.7 85/09/17 23:08:00 mckusick 36 35
c take responsibility for reseting window size when first opening pty;
c send window size capability in every oob message in case first is lost
e
s 00001/00001/00405
d D 5.6 85/09/17 19:17:08 eric 35 33
c facilities in syslog
e
s 00001/00000/00406
d R 5.6 85/09/16 20:26:19 mckusick 34 33
c add slight delay to help expidite setting of window size
e
s 00000/00003/00406
d D 5.5 85/09/12 20:48:38 mckusick 33 30
i 32 31
c merge of Suns changes
e
s 00039/00021/00363
d D 5.2.1.2 85/09/12 20:46:04 mckusick 32 31
c update from Sun
e
s 00000/00000/00384
d D 5.2.1.1 85/09/12 20:30:51 mckusick 31 28
c branch-place-holder
e
s 00007/00004/00381
d D 5.4 85/09/12 20:29:28 mckusick 30 29
c pass through internet number if gethostbyaddr() fails (check in for kjd)
e
s 00001/00000/00384
d D 5.3 85/08/08 13:55:47 bloom 29 28
c disconnect from terminal completely
e
s 00025/00013/00359
d D 5.2 85/06/19 11:14:40 bloom 28 27
c use one read of utmp and use O_APPEND for wtmp to avoid races
c 	(from ks@purdue-ecn)
e
s 00014/00002/00358
d D 5.1 85/05/28 15:20:13 dist 27 26
c Add copyright
e
s 00004/00004/00356
d D 4.25 85/03/24 12:47:22 sam 26 25
c correct comment now that I (believe) I understand ...
e
s 00006/00000/00354
d D 4.24 85/03/23 13:38:52 sam 25 24
c ignore SIGTTOU to avoid problems with csh changing prgrps (when 
c performing TIOCSWINSZ)
e
s 00146/00126/00208
d D 4.23 85/03/17 23:33:03 sam 24 23
c handle propagated window size changes
e
s 00003/00002/00331
d D 4.22 84/09/13 11:33:27 ralph 23 22
c use syslog for error messages
e
s 00002/00002/00331
d D 4.21 84/09/04 21:41:29 sam 22 21
c convert setsockopt calls to new interface
e
s 00020/00086/00313
d D 4.20 84/04/11 15:58:24 karels 21 19
c convert for use with inetd
e
s 00000/00000/00399
d R 4.20 84/04/11 15:37:28 karels 20 19
c convert for inetd
e
s 00025/00011/00374
d D 4.19 84/03/22 15:33:37 karels 19 18
c many cleanups; avoid looping if writes to socket WOULDBLOCK
e
s 00002/00002/00383
d D 4.18 83/07/01 03:19:32 sam 18 17
c add \r so readable
e
s 00001/00000/00384
d D 4.17 83/06/24 12:09:34 sam 17 16
c child inheriting original socket
e
s 00002/00002/00382
d D 4.16 83/06/12 01:40:49 sam 16 15
c new signals
e
s 00001/00001/00383
d D 4.15 83/06/02 17:41:53 sam 15 14
c socket.h
e
s 00002/00000/00382
d D 4.14 83/05/22 23:48:50 sam 14 13
c utmp changed
e
s 00002/00004/00380
d D 4.13 83/05/03 20:54:23 sam 13 12
c turn on keep alives
e
s 00024/00003/00360
d D 4.12 83/02/28 20:07:04 sam 12 11
c printing out illegal address is helpful in debugging
e
s 00003/00001/00360
d D 4.11 83/02/21 19:40:57 sam 11 10
c ignore SIGCHLD in child
e
s 00001/00001/00360
d D 4.10 83/01/22 16:11:09 sam 10 9
c oops
e
s 00024/00006/00337
d D 4.9 83/01/18 19:55:29 sam 9 8
c put back debugging and reap children so no zombies
e
s 00001/00002/00342
d D 4.8 83/01/07 20:36:11 sam 8 7
c no more SIOCDONE
e
s 00001/00000/00343
d D 4.7 82/12/29 15:57:33 sam 7 6
c put vhangup back in to clean pty
e
s 00003/00003/00340
d D 4.6 82/12/25 20:28:17 sam 6 5
c port numbers now byte swapped
e
s 00001/00001/00342
d D 4.5 82/11/15 18:32:53 sam 5 4
c add domain specification
e
s 00051/00020/00292
d D 4.4 82/11/15 01:23:21 sam 4 3
c fix fork failing and make diagnostics consistent
e
s 00022/00016/00290
d D 4.3 82/11/14 15:13:51 sam 3 2
c convert to 4.1c sys calls and directory layout
e
s 00027/00012/00279
d D 4.2 82/10/07 23:42:12 sam 2 1
c use new date base routines
e
s 00291/00000/00000
d D 4.1 82/04/02 10:28:59 wnj 1 0
c date and time created 82/04/02 10:28:59 by wnj
e
u
U
f b 
t
T
I 74
D 75

E 75
E 74
I 27
D 94
/*
E 94
I 94
/*-
E 94
I 74
D 75
 *	$Source: /mit/kerberos/ucb/mit/rlogind/RCS/rlogind.c,v $
 *	$Header: rlogind.c,v 5.0 89/06/26 18:31:01 kfall Locked $
 */

/*
E 75
E 74
D 48
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 48
I 48
D 52
 * Copyright (c) 1983 The Regents of the University of California.
E 52
I 52
D 77
 * Copyright (c) 1983, 1988 The Regents of the University of California.
E 77
I 77
D 101
 * Copyright (c) 1983, 1988, 1989 The Regents of the University of California.
E 77
E 52
 * All rights reserved.
E 101
I 101
 * Copyright (c) 1983, 1988, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 101
 *
D 94
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
E 94
I 94
 * %sccs.include.redist.c%
E 94
E 48
 */

E 27
I 1
#ifndef lint
D 21
static char sccsid[] = "%W% %E%";
E 21
I 21
D 27
static	char sccsid[] = "%W% (Berkeley) %G%";
E 21
#endif
E 27
I 27
D 101
char copyright[] =
D 48
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 48
I 48
D 52
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 52
I 52
D 77
"@(#) Copyright (c) 1983, 1988 The Regents of the University of California.\n\
E 77
I 77
D 94
"@(#) Copyright (c) 1983, 1988, 1989 The Regents of the University of California.\n\
E 94
I 94
"%Z% Copyright (c) 1983, 1988, 1989 The Regents of the University of California.\n\
E 94
E 77
E 52
E 48
 All rights reserved.\n";
E 101
I 101
static char copyright[] =
"%Z% Copyright (c) 1983, 1988, 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 101
D 48
#endif not lint
E 48
I 48
#endif /* not lint */
E 48

#ifndef lint
D 59
static char sccsid[] = "%W% (Berkeley) %G%";
E 59
I 59
D 61
static char sccsid[] = "@(#)rlogind.c	5.23 (Berkeley) 1/7/89";
E 61
I 61
D 74
static char sccsid[] = "%W% (Berkeley) %G%";
E 74
I 74
D 75
static char sccsid[] = "@(#)rlogind.c	5.35 (Berkeley) 4/2/89";
E 75
I 75
static char sccsid[] = "%W% (Berkeley) %G%";
E 75
E 74
E 61
E 59
D 48
#endif not lint
E 48
I 48
#endif /* not lint */
E 48
E 27

I 75
D 98
#ifdef KERBEROS
/* From:
 *	$Source: /mit/kerberos/ucb/mit/rlogind/RCS/rlogind.c,v $
 *	$Header: rlogind.c,v 5.0 89/06/26 18:31:01 kfall Locked $
 */
D 78

E 78
#endif
I 78

E 98
E 78
E 75
I 21
/*
 * remote login server:
I 50
 *	\0
E 50
 *	remuser\0
 *	locuser\0
D 24
 *	terminal type\0
E 24
I 24
D 50
 *	terminal info\0
E 24
 *	data
E 50
I 50
 *	terminal_type/speed\0
D 53
 *	data (not used currently)
E 53
I 53
 *	data
I 54
 *
 * Automatic login protocol is done here, using login -f upon success,
 * unless OLD_LOGIN is defined (then done in login, ala 4.2/4.3BSD).
E 54
E 53
E 50
 */

I 80
#define	FD_SETSIZE	16		/* don't need many bits for select */
E 80
E 21
D 73
#include <stdio.h>
D 62
#include <sys/types.h>
E 73
I 73
#include <sys/param.h>
E 73
E 62
I 62
#include <sys/param.h>
E 62
#include <sys/stat.h>
D 93
#include <sys/socket.h>
I 18
#include <sys/wait.h>
I 24
#include <sys/file.h>
I 76
#include <sys/ioctl.h>
#if BSD > 43
#include <sys/termios.h>
#endif
E 76
I 59
D 73
#include <sys/param.h>
E 73
I 73
#include <sys/signal.h>
E 93
#include <sys/ioctl.h>
D 93
#include <sys/termios.h>
E 93
I 93
#include <signal.h>
#include <termios.h>
E 93
E 73
E 59
E 24
E 18
D 3
#include <net/in.h>
E 3
I 3

I 93
#include <sys/socket.h>
E 93
#include <netinet/in.h>
I 87
#include <netinet/in_systm.h>
#include <netinet/ip.h>
I 93
#include <arpa/inet.h>
#include <netdb.h>
E 93
E 87

E 3
D 93
#include <errno.h>
E 93
#include <pwd.h>
D 18
#include <wait.h>
E 18
D 73
#include <signal.h>
I 54
D 55
#ifndef TERMIOS
E 55
D 76
#include <sgtty.h>
E 76
D 55
#else /* TERMIOS */
E 54
D 50
#include <sgtty.h>
E 50
I 50
#include <sys/ioctl.h>
#include <sys/termios.h>
I 54
#endif /* TERMIOS */
E 55
E 54
E 50
#include <stdio.h>
E 73
I 2
D 93
#include <netdb.h>
E 93
I 23
#include <syslog.h>
I 24
D 82
#include <strings.h>
E 82
I 82
D 93
#include <string.h>
E 93
I 93
#include <errno.h>
E 93
E 82
I 73
#include <stdio.h>
I 78
#include <unistd.h>
I 93
#include <stdlib.h>
#include <string.h>
E 93
E 78
#include "pathnames.h"
E 73
I 50
D 53
#include <utmp.h>
E 53
E 50
E 24
E 23
E 2

I 53
#ifndef TIOCPKT_WINDOW
#define TIOCPKT_WINDOW 0x80
#endif

E 53
I 50
D 55
#ifdef	KERBEROS
I 81
#include <kerberosIV/des.h>
E 81
D 59
#include <sys/param.h>
E 59
D 74
#include <kerberos/krb.h>
E 74
I 74
D 80
#include <krb.h>
E 80
I 80
#include <kerberosIV/krb.h>
E 80
E 74
#define	SECURE_MESSAGE "This rlogin session is using DES encryption for all transmissions.\r\n"

AUTH_DAT	*kdata;
KTEXT		ticket;
u_char		auth_buf[sizeof(AUTH_DAT)];
u_char		tick_buf[sizeof(KTEXT_ST)];
Key_schedule	schedule;
D 53
int		encrypt = 0, retval;
E 53
I 53
D 56
int		encrypt, retval;
E 56
I 56
D 67
int		encrypt, retval, use_kerberos = 0, vacuous = 0;
E 67
I 67
D 93
int		encrypt = 0, retval, use_kerberos = 0, vacuous = 0;
E 93
I 93
int		doencrypt, retval, use_kerberos, vacuous;
E 93
E 67
E 56
E 53
D 83
int		do_krb_login();
E 83

I 74
D 75
#if	BSD > 43
E 74
D 72
#define		OLD_RCMD		0x00
D 56
#define		KERB_RCMD		0x01
#define		KERB_RCMD_MUTUAL	0x02
E 56
I 56
#define		KERB_RCMD		0x00
#define		KERB_RCMD_MUTUAL	0x03

#define		ARGSTR			"lnkv"
E 72
I 72
#define		ARGSTR			"lnkvx"
E 75
I 75
#define		ARGSTR			"alnkvx"
E 75
E 72
#else
I 74
D 75
#define		ARGSTR			"nkvx"
#endif
#else
#if	BSD > 43
E 74
#define		ARGSTR			"ln"
I 74
#else
#define		ARGSTR			"n"
#endif
E 75
I 75
#define		ARGSTR			"aln"
E 75
E 74
E 56
#endif	/* KERBEROS */

E 55
D 53
char	*envinit[2];
D 52
struct	utmp	utmp;
#define	NMAX	sizeof(utmp.ut_name)
char		lusername[NMAX+1], rusername[NMAX+1];
static char	term[64] = "TERM=";
#define	ENVSIZE	(strlen("TERM="))
struct	passwd	nouser = {"", "nope", -1, -1, -1, "", "", "", "" };
E 52
I 52
struct	utmp utmp;
#define	NMAX sizeof(utmp.ut_name)
E 53
I 53
char	*env[2];
#define	NMAX 30
E 53
char	lusername[NMAX+1], rusername[NMAX+1];
static	char term[64] = "TERM=";
#define	ENVSIZE	(sizeof("TERM=")-1)	/* skip null for concatenation */
int	keepalive = 1;
I 76
int	check_all = 0;
E 76
I 75
int	check_all = 0;
E 75
E 52

D 83
#define	SUPERUSER(pwd)	((pwd)->pw_uid == 0)

E 83
E 50
I 32
D 52
# ifndef TIOCPKT_WINDOW
# define TIOCPKT_WINDOW 0x80
# endif TIOCPKT_WINDOW
E 52
I 52
D 53
#ifndef TIOCPKT_WINDOW
#define TIOCPKT_WINDOW 0x80
#endif
E 52

E 53
E 32
D 45
extern	errno;
E 45
I 45
D 93
extern	int errno;
E 45
I 9
int	reapchild();
E 9
D 50
struct	passwd *getpwnam();
E 50
I 50
struct	passwd *getpwnam(), *pwd;
E 50
D 2
char	*crypt(), *rindex(), *index(), *malloc(), *raddr();
E 2
I 2
D 12
char	*crypt(), *rindex(), *index(), *malloc();
E 12
I 12
D 24
char	*crypt(), *rindex(), *index(), *malloc(), *ntoa();
E 24
I 24
D 32
char	*crypt(), *malloc();
E 32
I 32
char	*malloc();
E 93
I 93
struct	passwd *pwd;
E 93
E 32
E 24
E 12
E 2
D 9
int	options = SO_ACCEPTCONN|SO_KEEPALIVE;
E 9
D 2
struct	sockaddr_in sin = { AF_INET, IPPORT_LOGINSERVER };
E 2
I 2
D 21
struct	sockaddr_in sin = { AF_INET };
E 2
/*
 * remote login server:
 *	remuser\0
 *	locuser\0
 *	terminal type\0
 *	data
 */
E 21
I 21

I 97
void	doit __P((int, struct sockaddr_in *));
int	control __P((int, char *, int));
void	protocol __P((int, int));
D 98
void	cleanup __P((void));
E 98
I 98
void	cleanup __P((int));
E 98
void	fatal __P((int, char *, int));
int	do_rlogin __P((struct sockaddr_in *));
void	getstr __P((char *, int, char *));
void	setup_term __P((int));
int	do_krb_login __P((struct sockaddr_in *));
void	usage __P((void));
int	local_domain __P((char *));
char	*topdomain __P((char *));

int
E 97
I 45
D 52
/*ARGSUSED*/
E 52
E 45
E 21
main(argc, argv)
	int argc;
D 97
	char **argv;
E 97
I 97
	char *argv[];
E 97
{
I 49
D 74
	extern int opterr, optind, _check_rhosts_file;
E 74
I 74
D 97
	extern int opterr, optind;
D 75
#if	BSD > 43
E 75
	extern int _check_rhosts_file;
D 75
#endif
E 75
E 74
	int ch;
E 49
D 9
	union wait status;
	int f, debug = 0;
E 9
I 9
D 13
	int f, options = SO_KEEPALIVE;
E 13
I 13
D 21
	int f, options = 0;
E 21
I 21
D 22
	int options = 0, fromlen;
E 22
I 22
D 45
	int on = 1, options = 0, fromlen;
E 45
I 45
	int on = 1, fromlen;
E 97
I 97
	extern int __check_rhosts_file;
E 97
E 45
E 22
E 21
E 13
E 9
	struct sockaddr_in from;
I 97
	int ch, fromlen, on;
E 97
I 2
D 21
	struct servent *sp;
E 21
E 2

I 35
D 59
D 62
	openlog("rlogind", LOG_PID | LOG_AUTH, LOG_AUTH);
E 62
I 62
	openlog("rlogind", LOG_PID | LOG_CONS, LOG_AUTH);
E 62
E 59
I 59
	openlog("rlogind", LOG_PID | LOG_CONS, LOG_AUTH);
E 59
I 49

	opterr = 0;
D 52
	while ((ch = getopt(argc, argv, "l")) != EOF)
		switch((char)ch) {
E 52
I 52
D 56
D 76
	while ((ch = getopt(argc, argv, "ln")) != EOF)
E 76
I 76
	while ((ch = getopt(argc, argv, "aln")) != EOF)
E 76
E 56
I 56
	while ((ch = getopt(argc, argv, ARGSTR)) != EOF)
E 56
		switch (ch) {
I 76
		case 'a':
			check_all = 1;
			break;
E 76
I 74
D 75
#if	BSD > 43
E 75
I 75
		case 'a':
			check_all = 1;
			break;
E 75
E 74
E 52
		case 'l':
D 97
			_check_rhosts_file = 0;
E 97
I 97
			__check_rhosts_file = 0;
E 97
			break;
I 74
D 75
#endif
E 75
E 74
I 52
		case 'n':
			keepalive = 0;
			break;
I 56
#ifdef KERBEROS
		case 'k':
			use_kerberos = 1;
			break;
		case 'v':
			vacuous = 1;
			break;
I 89
D 91
D 96
#ifdef CRYPT
E 89
I 72
		case 'x':
D 93
			encrypt = 1;
E 93
I 93
			doencrypt = 1;
E 93
			break;
E 96
E 91
E 72
#endif
I 89
D 91
D 96
#endif
E 96
E 91
E 89
E 56
E 52
		case '?':
		default:
D 52
			syslog(LOG_ERR, "usage: rlogind [-l]");
E 52
I 52
D 56
D 76
			syslog(LOG_ERR, "usage: rlogind [-l] [-n]");
E 76
I 76
			syslog(LOG_ERR, "usage: rlogind [-a] [-l] [-n]");
E 76
E 56
I 56
			usage();
E 56
E 52
			break;
		}
	argc -= optind;
	argv += optind;

I 56
#ifdef	KERBEROS
D 61
	if(use_kerberos && vacuous) {
E 61
I 61
	if (use_kerberos && vacuous) {
E 61
D 63
		fprintf(stderr, "%s: only one of -k and -v allowed\n", argv[0]);
E 63
		usage();
D 63
		exit(1);
E 63
I 63
D 77
		fatal("only one of -k and -v allowed\n");
E 77
I 77
D 78
		fatal("only one of -k and -v allowed");
E 78
I 78
		fatal(STDERR_FILENO, "only one of -k and -v allowed", 0);
E 78
E 77
E 63
	}
#endif
E 56
E 49
E 35
I 2
D 21
	sp = getservbyname("login", "tcp");
	if (sp == 0) {
		fprintf(stderr, "rlogind: tcp/rlogin: unknown service\n");
		exit(1);
E 21
I 21
	fromlen = sizeof (from);
D 93
	if (getpeername(0, &from, &fromlen) < 0) {
E 93
I 93
	if (getpeername(0, (struct sockaddr *)&from, &fromlen) < 0) {
E 93
D 59
D 62
		fprintf(stderr, "%s: ", argv[0]);
		perror("getpeername");
E 59
I 59
D 63
		syslog(LOG_ERR,"Couldn't get peer name of remote host: %m");
E 59
D 49
		_exit(1);
E 49
I 49
		exit(1);
E 63
I 63
		syslog(LOG_ERR,"Can't get peer name of remote host: %m");
D 78
		fatalperror("Can't get peer name of remote host");
E 78
I 78
		fatal(STDERR_FILENO, "Can't get peer name of remote host", 1);
E 78
E 63
E 62
I 62
		syslog(LOG_ERR, "Couldn't get peer name of remote host: %m");
D 76
		fatalperror("Can't get peer name of host");
E 76
I 76
		fatalperror("Can't get peer name of remote host");
E 76
E 62
E 49
E 21
	}
I 97
	on = 1;
E 97
E 2
D 21
#ifndef DEBUG
	if (fork())
		exit(0);
	for (f = 0; f < 10; f++)
		(void) close(f);
	(void) open("/", 0);
	(void) dup2(0, 1);
	(void) dup2(0, 2);
	{ int tt = open("/dev/tty", 2);
	  if (tt > 0) {
		ioctl(tt, TIOCNOTTY, 0);
		close(tt);
	  }
E 21
I 21
D 22
	if (setsockopt(0, SOL_SOCKET, SO_KEEPALIVE, 0, 0) < 0) {
E 22
I 22
D 52
	if (setsockopt(0, SOL_SOCKET, SO_KEEPALIVE, &on, sizeof (on)) < 0) {
E 52
I 52
	if (keepalive &&
	    setsockopt(0, SOL_SOCKET, SO_KEEPALIVE, &on, sizeof (on)) < 0)
E 52
E 22
D 23
		fprintf(stderr, "%s: ", argv[0]);
		perror("setsockopt (SO_KEEPALIVE)");
E 23
I 23
D 35
		openlog(argv[0], LOG_PID, 0);
E 35
		syslog(LOG_WARNING, "setsockopt (SO_KEEPALIVE): %m");
I 87
	on = IPTOS_LOWDELAY;
	if (setsockopt(0, IPPROTO_IP, IP_TOS, (char *)&on, sizeof(int)) < 0)
		syslog(LOG_WARNING, "setsockopt (IP_TOS): %m");
E 87
E 23
E 21
D 52
	}
E 52
D 21
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
		options |= SO_DEBUG, argv++, argc--;
	if (argc > 0) {
E 3
I 3
	if (argc > 0 && !strcmp(argv[0], "-d")) {
I 9
		options |= SO_DEBUG;
		argc--, argv++;
	}
	if (argc > 0) {
E 9
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
		argv++, argc--;
	}
I 3
D 5
	f = socket(0, SOCK_STREAM, 0, 0);
E 5
I 5
	f = socket(AF_INET, SOCK_STREAM, 0, 0);
E 5
	if (f < 0) {
		perror("rlogind: socket");
		exit(1);
	}
I 9
	if (options & SO_DEBUG)
		if (setsockopt(f, SOL_SOCKET, SO_DEBUG, 0, 0) < 0)
			perror("rlogind: setsockopt (SO_DEBUG)");
D 13
#ifdef notdef
E 13
	if (setsockopt(f, SOL_SOCKET, SO_KEEPALIVE, 0, 0) < 0)
D 13
		perror("rlogind: setsocktopt (SO_KEEPALIVE)");
#endif
E 13
I 13
		perror("rlogind: setsockopt (SO_KEEPALIVE)");
E 13
E 9
	if (bind(f, &sin, sizeof (sin), 0) < 0) {
		perror("rlogind: bind");
		exit(1);
	}
I 9
D 10
	signal(SIGCHLD, reapchild);
E 10
I 10
D 16
	sigset(SIGCHLD, reapchild);
E 16
I 16
	signal(SIGCHLD, reapchild);
E 16
E 10
E 9
	listen(f, 10);
E 3
E 2
	for (;;) {
D 3
		f = socket(SOCK_STREAM, 0, &sin, options);
		if (f < 0) {
			perror("socket");
			sleep(5);
			continue;
		}
		if (accept(f, &from) < 0) {
E 3
I 3
		int s, len = sizeof (from);

		s = accept(f, &from, &len, 0);
		if (s < 0) {
I 9
			if (errno == EINTR)
				continue;
E 9
E 3
D 4
			perror("accept");
E 4
I 4
			perror("rlogind: accept");
E 4
D 3
			close(f);
E 3
D 9
			sleep(1);
E 9
			continue;
		}
D 11
		if (fork() == 0)
E 11
I 11
		if (fork() == 0) {
			signal(SIGCHLD, SIG_IGN);
I 17
			close(f);
E 17
E 11
D 3
			doit(f, &from);
		close(f);
E 3
I 3
			doit(s, &from);
I 11
		}
E 11
		close(s);
E 3
D 9
		while (wait3(status, WNOHANG, 0) > 0)
			continue;
E 9
	}
I 9
}

reapchild()
{
	union wait status;

	while (wait3(&status, WNOHANG, 0) > 0)
		;
E 21
I 21
	doit(0, &from);
E 21
E 9
}

D 24
char	locuser[32], remuser[32];
char	buf[BUFSIZ];
E 24
int	child;
D 93
int	cleanup();
E 93
I 93
D 98
void	cleanup();
E 98
E 93
int	netf;
D 45
extern	errno;
E 45
D 88
char	*line;
E 88
I 88
char	line[MAXPATHLEN];
E 88
I 80
int	confirmed;
E 80
I 30
D 97
extern	char	*inet_ntoa();
E 97
E 30

I 37
struct winsize win = { 0, 0, 0, 0 };
E 37
I 32

I 37

I 97
void
E 97
E 37
E 32
doit(f, fromp)
	int f;
	struct sockaddr_in *fromp;
{
D 2
	char c, *rhost;
E 2
I 2
D 24
	char c;
E 2
D 4
	int i, p, cc, t;
E 4
I 4
	int i, p, cc, t, pid;
E 4
	int stop = TIOCPKT_DOSTOP;
E 24
I 24
D 88
	int i, p, t, pid, on = 1;
E 88
I 88
D 97
	int i, master, pid, on = 1;
E 88
I 54
#ifndef OLD_LOGIN
E 54
I 50
D 53
	int	authenticated = 0;
E 53
I 53
D 61
D 62
	int authenticated = 0;
E 62
I 62
	int authenticated = 0, hostok = 0;
	char remotehost[2 * MAXHOSTNAMELEN + 1];
E 62
E 61
I 61
	int authenticated = 0, hostok = 0;
E 97
I 97
	int master, pid, on = 1;
	int authenticated = 0;
E 97
E 61
I 54
#endif
E 54
E 53
E 50
E 24
I 2
	register struct hostent *hp;
I 97
D 99
	register char *hostname;
E 97
I 59
D 61
	char	remotehost[MAXHOSTNAMELEN];
	char	localhost[MAXHOSTNAMELEN];
E 61
I 61
	char remotehost[2 * MAXHOSTNAMELEN + 1];
E 99
I 99
	char hostname[2 * MAXHOSTNAMELEN + 1];
E 99
E 61
E 59
I 30
D 97
	struct hostent hostent;
E 97
I 59
D 61
	char	*raddr;
E 61
E 59
E 30
I 24
	char c;
E 24
E 2

	alarm(60);
	read(f, &c, 1);
I 50
D 55

D 72
#ifdef	KERBEROS
	/*
D 67
	 * XXX 1st char tells us which client we're talking to
E 67
I 67
	 * XXX: 1st char tells us which client we're talking to
E 67
	 */
D 52
	switch(c) {
E 52
I 52
	switch (c) {
E 52

D 52
	case	KERB_RCMD:
E 52
I 52
D 56
	case KERB_RCMD:
E 56
I 56
D 67
	case OLD_RCMD:		/* OLD_RCMD is same as KERB_RCMD */
E 67
I 67
	case OLD_RCMD:		/* NB: OLD_RCMD == KERB_RCMD */
E 67
D 61
		if(vacuous)
E 61
I 61
		if (vacuous)
E 61
			fatal(f, "Remote host requires Kerberos authentication");
E 56
E 52
		break;

D 52
	case	KERB_RCMD_MUTUAL:
E 52
I 52
	case KERB_RCMD_MUTUAL:
E 52
		encrypt = 1;
		break;

D 56

D 52
	case	OLD_RCMD:
E 52
I 52
	case OLD_RCMD:
E 56
E 52
	default:
D 56
		fatal(f, "Remote host requires Kerberos authentication");
E 56
I 56
		fatal(f, "Remote protocol error");
E 56
	}
#else
E 55
E 50
	if (c != 0)
E 72
I 72
D 80
	if(c != 0)
E 80
I 80
	if (c != 0)
E 80
E 72
		exit(1);
I 72
#ifdef	KERBEROS
D 77
	if(vacuous)
E 77
I 77
	if (vacuous)
E 77
D 78
		fatal(f, "Remote host requires Kerberos authentication");
E 78
I 78
		fatal(f, "Remote host requires Kerberos authentication", 0);
E 78
E 72
I 50
D 55
#endif
E 55

D 52

E 52
E 50
	alarm(0);
D 2
#if vax
E 2
D 6
	fromp->sin_port = htons(fromp->sin_port);
E 6
I 6
D 19
	fromp->sin_port = htons((u_short)fromp->sin_port);
E 19
I 19
	fromp->sin_port = ntohs((u_short)fromp->sin_port);
E 19
E 6
D 2
#endif
	rhost = raddr(fromp->sin_addr.s_addr);
E 2
I 2
D 93
	hp = gethostbyaddr(&fromp->sin_addr, sizeof (struct in_addr),
E 93
I 93
	hp = gethostbyaddr((char *)&fromp->sin_addr, sizeof(struct in_addr),
E 93
D 97
		fromp->sin_family);
I 4
D 12
	if (hp == 0)
		fatal(f, "Host name for your address unknown");
E 12
I 12
	if (hp == 0) {
D 19
		char buf[BUFSIZ], *cp = (char *)&fromp->sin_addr;
E 19
I 19
D 30
		char buf[BUFSIZ];
E 19
D 32

		fatal(f, sprintf(buf, "Host name for your address (%s) unknown",
D 24
			ntoa(fromp->sin_addr)));
E 24
I 24
			inet_ntoa(fromp->sin_addr)));
E 32
I 32
D 33
		(void) sprintf(buf, "Host name for your address (%s) unknown",
			inet_ntoa(fromp->sin_addr));
		fatal(f, buf);
E 33
E 32
E 30
I 30
		/*
		 * Only the name is used below.
		 */
		hp = &hostent;
		hp->h_name = inet_ntoa(fromp->sin_addr);
I 70
#ifndef OLD_LOGIN
E 70
I 65
		hostok++;
I 70
#endif
E 70
	}
E 65
I 62
#ifndef OLD_LOGIN
D 65
	} else if (local_domain(hp->h_name)) {
E 65
I 65
D 76
	else if (local_domain(hp->h_name)) {
E 76
I 76
	else if (check_all || local_domain(hp->h_name)) {
E 76
E 65
		/*
		 * If name returned by gethostbyaddr is in our domain,
		 * attempt to verify that we haven't been fooled by someone
		 * in a remote net; look up the name and check that this
		 * address corresponds to the name.
		 */
		strncpy(remotehost, hp->h_name, sizeof(remotehost) - 1);
		remotehost[sizeof(remotehost) - 1] = 0;
		hp = gethostbyname(remotehost);
		if (hp)
I 76
#ifdef h_addr	/* 4.2 hack */
E 76
D 65
		    for (; hp->h_addr_list[0]; hp->h_addr_list++) {
E 65
I 65
		    for (; hp->h_addr_list[0]; hp->h_addr_list++)
E 65
			if (!bcmp(hp->h_addr_list[0], (caddr_t)&fromp->sin_addr,
			    sizeof(fromp->sin_addr))) {
				hostok++;
				break;
			}
I 76
#else
			if (!bcmp(hp->h_addr, (caddr_t)&fromp->sin_addr,
			    sizeof(fromp->sin_addr)))
				hostok++;
#endif
E 76
D 65
		}
E 65
I 65
	} else
		hostok++;
E 65
D 76
#endif
E 76
I 76
#endif /* OLD_LOGIN */
E 76
E 62
I 59
D 61
	} else {
		(void) gethostname(localhost, sizeof(localhost));
		if(same_domain(hp->h_name, localhost)) {
			bcopy(hp->h_name, remotehost, sizeof(remotehost));
			hp = gethostbyname(remotehost);
			authenticated = -10;	/* !authenticated */
			if(hp == NULL) {
				syslog(LOG_NOTICE, "Couldn't get entry for remote host %s\n",
					remotehost);
			} else {
			    for(;;) {
				if(!(raddr = hp->h_addr_list[0]))
					break;

				if(!bcmp(raddr, (caddr_t) &fromp->sin_addr,
				    sizeof(struct in_addr))) {
					authenticated = 0;
					break;
				}
				hp->h_addr_list++;
    			    }
			    if(authenticated < 0) {
				syslog(LOG_NOTICE,"Host address not listed for name %s",
					remotehost);
			    }
E 61
I 61
D 64
	} else if (local_domain(hp->h_name)) {
		/*
		 * If name returned by gethostbyaddr is in our domain,
		 * attempt to verify that we haven't been fooled by someone
		 * in a remote net; look up the name and check that this
		 * address corresponds to the name.
		 */
		strncpy(remotehost, hp->h_name, sizeof(remotehost) - 1);
		remotehost[sizeof(remotehost) - 1] = 0;
		hp = gethostbyname(remotehost);
		if (hp)
		    for (; hp->h_addr_list[0]; hp->h_addr_list++) {
			if (!bcmp(hp->h_addr_list[0], (caddr_t)&fromp->sin_addr,
			    sizeof(fromp->sin_addr))) {
				hostok++;
				break;
E 61
			}
		}
E 64
I 64
D 66
	} else {
		if (local_domain(hp->h_name)) {
		    /*
		     * If name returned by gethostbyaddr is in our domain,
		     * attempt to verify that we haven't been fooled by someone
		     * in a remote net; look up the name and check that this
		     * address corresponds to the name.
		     */
		    strncpy(remotehost, hp->h_name, sizeof(remotehost) - 1);
		    remotehost[sizeof(remotehost) - 1] = 0;
		    hp = gethostbyname(remotehost);
		    if (hp)
		        for (; hp->h_addr_list[0]; hp->h_addr_list++) {
			    if (!bcmp(hp->h_addr_list[0],
				(caddr_t)&fromp->sin_addr,
			        sizeof(fromp->sin_addr))) {
				    hostok++;
				    break;
			    }
		        }
		} else
			hostok++;
E 64
E 59
E 30
E 24
D 65
	}
E 66
I 66
D 70
		hostok++;
D 75
	} else if (local_domain(hp->h_name)) {
E 75
I 75
	} else if (check_all || local_domain(hp->h_name)) {
E 75
		/*
		 * If name returned by gethostbyaddr is in our domain,
		 * attempt to verify that we haven't been fooled by someone
		 * in a remote net; look up the name and check that this
		 * address corresponds to the name.
		 */
		strncpy(remotehost, hp->h_name, sizeof(remotehost) - 1);
		remotehost[sizeof(remotehost) - 1] = 0;
		hp = gethostbyname(remotehost);
		if (hp)
		    for (; hp->h_addr_list[0]; hp->h_addr_list++)
			if (!bcmp(hp->h_addr_list[0], (caddr_t)&fromp->sin_addr,
			    sizeof(fromp->sin_addr))) {
				hostok++;
				break;
			}
	} else
		hostok++;
E 97
I 97
	    fromp->sin_family);
	if (hp)
D 99
		hostname = hp->h_name;
E 99
I 99
		(void)strcpy(hostname, hp->h_name);
E 99
	else
D 99
		hostname = strcpy(remotehost, inet_ntoa(fromp->sin_addr));
E 99
I 99
		(void)strcpy(hostname, inet_ntoa(fromp->sin_addr));
E 99
E 97
E 70
E 66
E 65
I 50

D 55
#ifdef	KERBEROS
D 56
	retval = do_krb_login(hp->h_name, fromp, encrypt);
	write(f, &c, 1);
D 52
	if(retval == 0) {
E 52
I 52
	if (retval == 0)
E 52
		authenticated++;
D 52
	} else {
		if(retval > 0)
E 52
I 52
	else
		if (retval > 0)
E 52
			fatal(f, krb_err_txt[retval]);
D 52
	}
E 52
#else
E 55
E 50
E 12
E 4
E 2
	if (fromp->sin_family != AF_INET ||
D 19
	    fromp->sin_port >= IPPORT_RESERVED ||
D 2
	    rhost == 0) {
E 2
I 2
D 4
	    hp == 0) {
E 2
		write(f, "\01Permission denied.\n", 20);
		exit(1);
	}
E 4
I 4
	    hp == 0)
E 19
I 19
D 44
	    fromp->sin_port >= IPPORT_RESERVED)
E 44
I 44
	    fromp->sin_port >= IPPORT_RESERVED ||
D 62
	    fromp->sin_port < IPPORT_RESERVED/2)
E 62
I 62
	    fromp->sin_port < IPPORT_RESERVED/2) {
		syslog(LOG_NOTICE, "Connection from %s on illegal port",
			inet_ntoa(fromp->sin_addr));
E 62
E 44
E 19
		fatal(f, "Permission denied");
I 62
	}
I 70
#ifdef IP_OPTIONS
      {
	u_char optbuf[BUFSIZ/3], *cp;
	char lbuf[BUFSIZ], *lp;
	int optsize = sizeof(optbuf), ipproto;
	struct protoent *ip;

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
E 70
E 62
E 4
	write(f, "", 1);
E 56
I 56
D 61
	if(use_kerberos) {
E 61
I 61
	if (use_kerberos) {
I 83
D 97
		if (!hostok)
D 87
			fatal(f, "krlogind: Host address mismatch.", 0);
E 87
I 87
			fatal(f, "rlogind: Host address mismatch.", 0);
E 87
E 83
E 61
D 93
		retval = do_krb_login(hp->h_name, fromp, encrypt);
E 93
I 93
		retval = do_krb_login(hp->h_name, fromp);
E 97
I 97
		retval = do_krb_login(fromp);
E 97
E 93
D 80
		write(f, &c, 1);
E 80
D 61
		if (retval == 0) {
E 61
I 61
D 67
		if (retval == 0)
E 67
I 67
D 83
		if (retval == 0 && hostok)
E 83
I 83
		if (retval == 0)
E 83
E 67
E 61
			authenticated++;
D 61
		} else {
			if (retval > 0)
				fatal(f, krb_err_txt[retval]);
		}
E 61
I 61
		else if (retval > 0)
D 78
			fatal(f, krb_err_txt[retval]);
E 78
I 78
			fatal(f, krb_err_txt[retval], 0);
E 78
I 67
D 80
		else if(!hostok)
E 80
I 80
D 83
		else if (!hostok)
E 80
D 77
			fatal(f, "krlogind: Host address mismatch.\r\n");
E 77
I 77
D 78
			fatal(f, "krlogind: Host address mismatch.");
E 78
I 78
			fatal(f, "krlogind: Host address mismatch.", 0);
E 83
I 80
		write(f, &c, 1);
		confirmed = 1;		/* we sent the null! */
E 80
E 78
E 77
E 67
E 61
	} else
E 56
I 53
D 55
#endif
E 55
I 54
#ifndef OLD_LOGIN
E 54
E 53
I 50
D 52
	if(do_rlogin(hp->h_name) == 0)
E 52
I 52
D 56
D 62
	if (do_rlogin(hp->h_name) == 0)
E 52
		authenticated++;
E 62
I 62
	if (do_rlogin(hp->h_name) == 0) {
		if (hostok)
		    authenticated++;
		else
		    write(f, "rlogind: Host address mismatch.\r\n",
		     sizeof("rlogind: Host address mismatch.\r\n") - 1);
	}
E 62
E 56
I 56
D 61
		if (fromp->sin_family != AF_INET ||
	    	    fromp->sin_port >= IPPORT_RESERVED ||
D 59
	    	    fromp->sin_port < IPPORT_RESERVED/2)
E 59
I 59
	    	    fromp->sin_port < IPPORT_RESERVED/2) {
			syslog(LOG_NOTICE, "Connection from %s on illegal port",
				inet_ntoa(fromp->sin_addr));
E 59
			fatal(f, "Permission denied");
D 59
		else {
E 59
I 59
		} else {
E 59
			write(f, "", 1);
E 61
I 61
D 67
	if (fromp->sin_family != AF_INET ||
	    fromp->sin_port >= IPPORT_RESERVED ||
	    fromp->sin_port < IPPORT_RESERVED/2) {
		syslog(LOG_NOTICE, "Connection from %s on illegal port",
			inet_ntoa(fromp->sin_addr));
		fatal(f, "Permission denied");
D 63
	} else {
		write(f, "", 1);
E 63
I 63
	}
	write(f, "", 1);
E 63
E 61
E 56
I 54
#endif
E 54
D 53
#endif
E 53

I 56
D 61
			if (do_rlogin(hp->h_name) == 0)
				authenticated++;
E 61
I 61
D 63
		if (do_rlogin(hp->h_name) == 0) {
			if (hostok)
			    authenticated++;
			else
			    write(f, "rlogind: Host address mismatch.\r\n",
			     sizeof("rlogind: Host address mismatch.\r\n") - 1);
E 61
		}
E 63
I 63
	if (do_rlogin(hp->h_name) == 0) {
		if (hostok)
			authenticated++;
		else
			write(f, "rlogind: Host address mismatch.\r\n",
			    sizeof("rlogind: Host address mismatch.\r\n") - 1);
E 67
I 67
	{
D 97
	    if (fromp->sin_family != AF_INET ||
	        fromp->sin_port >= IPPORT_RESERVED ||
	        fromp->sin_port < IPPORT_RESERVED/2) {
		    syslog(LOG_NOTICE, "Connection from %s on illegal port",
			    inet_ntoa(fromp->sin_addr));
D 78
		    fatal(f, "Permission denied");
E 78
I 78
		    fatal(f, "Permission denied", 0);
E 78
	    }
E 97
I 97
		if (fromp->sin_family != AF_INET ||
		    fromp->sin_port >= IPPORT_RESERVED ||
		    fromp->sin_port < IPPORT_RESERVED/2) {
			syslog(LOG_NOTICE, "Connection from %s on illegal port",
				inet_ntoa(fromp->sin_addr));
			fatal(f, "Permission denied", 0);
		}
E 97
I 69
D 70
#ifdef IP_OPTIONS
D 97
	    {
	    u_char optbuf[BUFSIZ/3], *cp;
	    char lbuf[BUFSIZ], *lp;
	    int optsize = sizeof(optbuf), ipproto;
	    struct protoent *ip;
E 97
I 97
		{
		u_char optbuf[BUFSIZ/3], *cp;
		char lbuf[BUFSIZ], *lp;
		int optsize = sizeof(optbuf), ipproto;
		struct protoent *ip;
E 97

D 97
	    if ((ip = getprotobyname("ip")) != NULL)
		    ipproto = ip->p_proto;
	    else
		    ipproto = IPPROTO_IP;
	    if (getsockopt(0, ipproto, IP_OPTIONS, (char *)optbuf,
		&optsize) == 0 && optsize != 0) {
		    lp = lbuf;
		    for (cp = optbuf; optsize > 0; cp++, optsize--, lp += 3)
			    sprintf(lp, " %2.2x", *cp);
		    syslog(LOG_NOTICE,
			"Connection received using IP options (ignored):%s",
			lbuf);
		    if (setsockopt(0, ipproto, IP_OPTIONS,
D 93
			(char *)NULL, &optsize) != 0) {
E 93
I 93
			(char *)NULL, optsize) != 0) {
E 93
			    syslog(LOG_ERR, "setsockopt IP_OPTIONS NULL: %m");
			    exit(1);
		    }
	        }
	    }
E 97
I 97
		if ((ip = getprotobyname("ip")) != NULL)
			ipproto = ip->p_proto;
		else
			ipproto = IPPROTO_IP;
		if (getsockopt(0, ipproto, IP_OPTIONS, (char *)optbuf,
		    &optsize) == 0 && optsize != 0) {
			lp = lbuf;
			for (cp = optbuf; optsize > 0; cp++, optsize--, lp += 3)
				sprintf(lp, " %2.2x", *cp);
			syslog(LOG_NOTICE,
			    "Connection received using IP options (ignored):%s",
			    lbuf);
			if (setsockopt(0, ipproto, IP_OPTIONS,
			    (char *)NULL, optsize) != 0) {
				syslog(LOG_ERR,
				    "setsockopt IP_OPTIONS NULL: %m");
				exit(1);
			}
		}
		}
E 97
#endif
E 70
E 69
D 80
	    write(f, "", 1);
    
	    if (do_rlogin(hp->h_name) == 0) {
		    if (hostok)
			    authenticated++;
		    else
			    write(f, "rlogind: Host address mismatch.\r\n",
			     sizeof("rlogind: Host address mismatch.\r\n") - 1);
	    }
E 80
I 80
D 97
	    if (do_rlogin(hp->h_name) == 0 && hostok)
		    authenticated++;
E 97
I 97
		if (do_rlogin(fromp) == 0)
			authenticated++;
E 97
E 80
E 67
E 63
I 61
	}
E 61
D 88

E 56
E 50
	for (c = 'p'; c <= 's'; c++) {
		struct stat stb;
		line = "/dev/ptyXX";
		line[strlen("/dev/pty")] = c;
		line[strlen("/dev/ptyp")] = '0';
		if (stat(line, &stb) < 0)
			break;
		for (i = 0; i < 16; i++) {
D 45
			line[strlen("/dev/ptyp")] = "0123456789abcdef"[i];
			p = open(line, 2);
E 45
I 45
			line[sizeof("/dev/ptyp") - 1] = "0123456789abcdef"[i];
			p = open(line, O_RDWR);
E 45
			if (p > 0)
				goto gotpty;
		}
	}
D 4
	dup2(f, 1);
	printf("All network ports in use.\r\n");
	exit(1);
E 4
I 4
D 32
	fatal(f, "All network ports in use");
E 32
I 32
D 78
	fatal(f, "Out of ptys");
E 78
I 78
	fatal(f, "Out of ptys", 0);
E 78
E 32
	/*NOTREACHED*/
E 4
gotpty:
I 37
	(void) ioctl(p, TIOCSWINSZ, &win);
E 37
D 19
	dup2(f, 0);
E 19
I 19
	netf = f;
E 19
D 78
	line[strlen("/dev/")] = 't';
E 78
I 78
	line[sizeof(_PATH_DEV) - 1] = 't';
E 78
I 45
	t = open(line, O_RDWR);
	if (t < 0)
D 78
		fatalperror(f, line);
E 78
I 78
		fatal(f, line, 1);
E 78
	if (fchmod(t, 0))
D 78
		fatalperror(f, line);
E 78
I 78
		fatal(f, line, 1);
E 78
	(void)signal(SIGHUP, SIG_IGN);
D 86
	vhangup();
E 86
I 86
#ifdef	notdef
vhangup();
#endif
E 86
	(void)signal(SIGHUP, SIG_DFL);
	t = open(line, O_RDWR);
	if (t < 0)
D 78
		fatalperror(f, line);
E 78
I 78
		fatal(f, line, 1);
E 78
D 50
	{
		struct sgttyb b;

		(void)ioctl(t, TIOCGETP, &b);
		b.sg_flags = RAW|ANYP;
		(void)ioctl(t, TIOCSETP, &b);
	}
E 50
I 50
	setup_term(t);
E 88
I 80
	if (confirmed == 0) {
		write(f, "", 1);
		confirmed = 1;		/* we sent the null! */
	}
#ifdef	KERBEROS
I 89
D 91
D 96
#ifdef	CRYPT
E 89
D 93
	if (encrypt)
E 93
I 93
	if (doencrypt)
E 93
D 100
		(void) des_write(f, SECURE_MESSAGE, sizeof(SECURE_MESSAGE));
E 100
I 100
		(void) des_write(f, SECURE_MESSAGE, sizeof(SECURE_MESSAGE) - 1);
E 100
E 80
E 50
E 45
D 76
D 77
#ifdef DEBUG
E 76
I 76
D 79
#ifndef DEBUG
E 79
I 79
#ifdef DEBUG
E 79
E 76
D 45
	{ int tt = open("/dev/tty", 2);
	  if (tt > 0) {
		ioctl(tt, TIOCNOTTY, 0);
		close(tt);
	  }
E 45
I 45
	{
		int tt = open("/dev/tty", O_RDWR);
		if (tt > 0) {
			(void)ioctl(tt, TIOCNOTTY, 0);
			(void)close(tt);
		}
E 45
	}
#endif
E 77
I 77
D 89

E 89
I 89
#endif
E 96
E 91
E 89
I 80
D 97
	if (use_kerberos == 0)
E 97
#endif
D 97
	   if (!authenticated && !hostok)
		write(f, "rlogind: Host address mismatch.\r\n",
		    sizeof("rlogind: Host address mismatch.\r\n") - 1);

E 97
E 80
E 77
D 45
	t = open(line, 2);
D 4
	if (t < 0) {
		dup2(f, 2);
		perror(line);
		exit(1);
	}
E 4
I 4
	if (t < 0)
		fatalperror(f, line, errno);
E 4
	{ struct sgttyb b;
	  gtty(t, &b); b.sg_flags = RAW|ANYP; stty(t, &b);
	}
E 45
D 4
	if (fork()) {
E 4
I 4
D 88
	pid = fork();
	if (pid < 0)
D 45
		fatalperror(f, "", errno);
E 45
I 45
D 78
		fatalperror(f, "");
E 78
I 78
		fatal(f, "", 1);
E 78
E 45
D 24
	if (pid) {
E 4
		char pibuf[1024], fibuf[1024], *pbp, *fbp;
D 19
		int pcc = 0, fcc = 0, on = 1;
E 19
I 19
		register pcc = 0, fcc = 0;
		int on = 1;
E 19
/* FILE *console = fopen("/dev/console", "w");  */
/* setbuf(console, 0); */

/* fprintf(console, "f %d p %d\r\n", f, p); */
E 24
I 24
	if (pid == 0) {
I 76
#if BSD > 43
		if (setsid() < 0)
			fatalperror(f, "setsid");
		if (ioctl(t, TIOCSCTTY, 0) < 0)
			fatalperror(f, "ioctl(sctty)");
#endif
E 76
I 54
D 55
#ifdef TERMIOS
E 54
I 50
D 52
		if(setsid() < 0)
E 52
I 52
		if (setsid() < 0)
E 52
D 78
			fatalperror(f, "setsid");
E 78
I 78
			fatal(f, "setsid", 1);
E 78
D 52
		if(ioctl(t, TIOCSCTTY, 0) < 0)
E 52
I 52
		if (ioctl(t, TIOCSCTTY, 0) < 0)
E 52
D 78
			fatalperror(f, "ioctl(sctty)");
I 54
#endif /* TERMIOS */
E 55
E 54
E 50
		close(f), close(p);
		dup2(t, 0), dup2(t, 1), dup2(t, 2);
E 24
I 19
		close(t);
E 78
I 78
			fatal(f, "ioctl(sctty)", 1);
		(void)close(f);
		(void)close(p);
		dup2(t, STDIN_FILENO);
		dup2(t, STDOUT_FILENO);
		dup2(t, STDERR_FILENO);
		(void)close(t);
E 88
I 88
	netf = f;
E 88
E 78
I 74

I 88
	pid = forkpty(&master, line, NULL, &win);
	if (pid < 0) {
		if (errno == ENOENT)
			fatal(f, "Out of ptys", 0);
		else
			fatal(f, "Forkpty", 1);
	}
	if (pid == 0) {
D 97
		if (f > 2)	/* f should always be 0, but... */ 
E 97
I 97
		if (f > 2)	/* f should always be 0, but... */
E 97
			(void) close(f);
		setup_term(0);
E 88
E 74
I 54
#ifdef OLD_LOGIN
		execl("/bin/login", "login", "-r", hp->h_name, 0);
#else /* OLD_LOGIN */
E 54
E 19
D 24
		ioctl(f, FIONBIO, &on);
		ioctl(p, FIONBIO, &on);
		ioctl(p, TIOCPKT, &on);
		signal(SIGTSTP, SIG_IGN);
D 16
		sigset(SIGCHLD, cleanup);
E 16
I 16
		signal(SIGCHLD, cleanup);
E 16
		for (;;) {
			int ibits = 0, obits = 0;
E 24
I 24
D 50
		execl("/bin/login", "login", "-r", hp->h_name, 0);
E 50
I 50
D 52
		if(authenticated)
			execl("/bin/login", "login",
				"-h", hp->h_name,
				"-f", pwd->pw_name,
				"-p", 0
			);
E 52
I 52
D 59
		if (authenticated)
E 59
I 59
D 61
		if (authenticated > 0)
E 61
I 61
D 86
		if (authenticated)
E 86
I 86
		if (authenticated) {
I 87
#ifdef	KERBEROS
E 87
			if (use_kerberos && (pwd->pw_uid == 0))
				syslog(LOG_INFO|LOG_AUTH,
				    "ROOT Kerberos login from %s.%s@%s on %s\n",
				    kdata->pname, kdata->pinst, kdata->prealm,
D 97
				    hp->h_name);
E 97
I 97
				    hostname);
E 97
I 87
#endif
E 87

E 86
E 61
E 59
D 56
D 57
			execl("/bin/login", "login", "-p", "-f",
D 53
			    "-h", hp->h_name, pwd->pw_name, 0);
E 53
I 53
			    "-h", hp->h_name, lusername, 0);
E 57
I 57
			execl("/bin/login", "login", "-p", "-h", hp->h_name,
			    "-f", lusername, 0);
E 57
E 56
I 56
D 73
			execl("/bin/login", "login", "-p",
E 73
I 73
D 102
			execl(_PATH_LOGIN, "login", "-p",
E 73
D 97
			    "-h", hp->h_name, "-f", lusername, 0);
E 97
I 97
			    "-h", hostname, "-f", lusername, (char *)NULL);
E 102
I 102
			execle(_PATH_LOGIN, "login", "-p",
			    "-h", hostname, "-f", "--", lusername, NULL, env);
E 102
E 97
E 56
E 53
E 52
D 86
		else
E 86
I 86
		} else
E 86
D 52
			execl("/bin/login", "login",
				"-h", hp->h_name,
				"-p", pwd->pw_name,
				0
			);
E 52
I 52
D 56
			execl("/bin/login", "login", "-p", "-h", hp->h_name,
D 53
			    pwd->pw_name, 0);
E 53
I 53
			    lusername, 0);
E 56
I 56
D 73
			execl("/bin/login", "login", "-p",
E 73
I 73
D 102
			execl(_PATH_LOGIN, "login", "-p",
E 73
D 97
			    "-h", hp->h_name, lusername, 0);
E 97
I 97
			    "-h", hostname, lusername, (char *)NULL);
E 102
I 102
			execle(_PATH_LOGIN, "login", "-p",
			    "-h", hostname, "--", lusername, NULL, env);
E 102
E 97
E 56
I 54
#endif /* OLD_LOGIN */
E 54
E 53
E 52
E 50
D 45
		fatalperror(2, "/bin/login", errno);
E 45
I 45
D 73
		fatalperror(2, "/bin/login");
E 73
I 73
D 78
		fatalperror(2, _PATH_LOGIN);
E 78
I 78
		fatal(STDERR_FILENO, _PATH_LOGIN, 1);
E 78
E 73
E 45
		/*NOTREACHED*/
	}
D 88
	close(t);
I 50

E 88
D 55
D 89
#ifdef	KERBEROS
E 89
I 89
D 90
#if defined(KERBEROS) && defined(CRYPT)
E 90
I 90
D 91
D 96
#ifdef	CRYPT
#ifdef	KERBEROS
E 90
E 89
	/*
	 * If encrypted, don't turn on NBIO or the des read/write
	 * routines will croak.
	 */

D 52
	if(encrypt)
E 52
I 52
D 80
	if (encrypt)
E 52
		(void) des_write(f, SECURE_MESSAGE, sizeof(SECURE_MESSAGE));
	else
E 80
I 80
D 93
	if (!encrypt)
E 93
I 93
	if (!doencrypt)
E 93
E 80
D 52
		ioctl(f, FIONBIO, &on);
#else
E 50
	ioctl(f, FIONBIO, &on);
E 52
I 50
#endif
I 90
#endif
E 96
E 91
E 90
I 52
		ioctl(f, FIONBIO, &on);
E 55
I 55
	ioctl(f, FIONBIO, &on);
E 55
E 52
D 53

E 53
E 50
D 88
	ioctl(p, FIONBIO, &on);
	ioctl(p, TIOCPKT, &on);
E 88
I 88
	ioctl(master, FIONBIO, &on);
	ioctl(master, TIOCPKT, &on);
E 88
D 80
	signal(SIGTSTP, SIG_IGN);
E 80
	signal(SIGCHLD, cleanup);
I 29
D 80
	setpgrp(0, 0);
E 80
E 29
D 88
	protocol(f, p);
E 88
I 88
	protocol(f, master);
E 88
I 42
	signal(SIGCHLD, SIG_IGN);
E 42
D 98
	cleanup();
E 98
I 98
	cleanup(0);
E 98
}
E 24
D 4
			if (fcc) obits |= (1<<p); else ibits |= (1<<f);
E 4
I 4

D 24
			if (fcc)
				obits |= (1<<p);
E 24
I 24
char	magic[2] = { 0377, 0377 };
I 39
char	oobdata[] = {TIOCPKT_WINDOW};
E 39

/*
 * Handle a "control" request (signaled by magic being present)
 * in the data stream.  For now, we are only willing to handle
 * window size changes.
 */
I 97
int
E 97
control(pty, cp, n)
	int pty;
	char *cp;
	int n;
{
D 41
	struct winsize *wp;
E 41
I 41
	struct winsize w;
E 41

D 41
	if (n < 4+sizeof (*wp) || cp[2] != 's' || cp[3] != 's')
E 41
I 41
	if (n < 4+sizeof (w) || cp[2] != 's' || cp[3] != 's')
E 41
		return (0);
I 39
	oobdata[0] &= ~TIOCPKT_WINDOW;	/* we know he heard */
E 39
D 41
	wp = (struct winsize *)(cp+4);
	wp->ws_row = ntohs(wp->ws_row);
	wp->ws_col = ntohs(wp->ws_col);
	wp->ws_xpixel = ntohs(wp->ws_xpixel);
	wp->ws_ypixel = ntohs(wp->ws_ypixel);
	(void)ioctl(pty, TIOCSWINSZ, wp);
	return (4+sizeof (*wp));
E 41
I 41
D 102
	bcopy(cp+4, (char *)&w, sizeof(w));
E 102
I 102
	memmove(&w, cp+4, sizeof(w));
E 102
	w.ws_row = ntohs(w.ws_row);
	w.ws_col = ntohs(w.ws_col);
	w.ws_xpixel = ntohs(w.ws_xpixel);
	w.ws_ypixel = ntohs(w.ws_ypixel);
	(void)ioctl(pty, TIOCSWINSZ, &w);
	return (4+sizeof (w));
E 41
}

/*
 * rlogin "protocol" machine.
 */
I 97
void
E 97
protocol(f, p)
D 78
	int f, p;
E 78
I 78
	register int f, p;
E 78
{
D 80
	char pibuf[1024], fibuf[1024], *pbp, *fbp;
E 80
I 80
	char pibuf[1024+1], fibuf[1024], *pbp, *fbp;
E 80
	register pcc = 0, fcc = 0;
D 32
	int cc, stop = TIOCPKT_DOSTOP;
E 32
I 32
D 39
	int cc, stop = TIOCPKT_DOSTOP, wsize;
	static char oob[] = {TIOCPKT_WINDOW};
E 39
I 39
D 52
	int cc;
E 52
I 52
D 78
	int cc, nfd, pmask, fmask;
E 78
I 78
	int cc, nfd, n;
E 78
E 52
I 40
	char cntl;
E 40
E 39
E 32

I 25
	/*
D 26
	 * This is a hack for the TIOCSWINSZ calls
	 * (csh pgrp manipulation appears to cause
	 * trouble).
E 26
I 26
	 * Must ignore SIGTTOU, otherwise we'll stop
	 * when we try and set slave pty's window shape
D 39
	 * (our pgrp is that of the master pty).
E 39
I 39
	 * (our controlling tty is the master pty).
E 39
E 26
	 */
D 26
	(void) signal(SIGTTOU, SIG_IGN);		/* XXX */
E 26
I 26
	(void) signal(SIGTTOU, SIG_IGN);
I 32
D 39
	send(f, oob, 1, MSG_OOB);	/* indicate new rlogin */
E 39
I 39
	send(f, oobdata, 1, MSG_OOB);	/* indicate new rlogin */
I 52
	if (f > p)
		nfd = f + 1;
	else
		nfd = p + 1;
I 80
	if (nfd > FD_SETSIZE) {
		syslog(LOG_ERR, "select mask too small, increase FD_SETSIZE");
		fatal(f, "internal error (select mask too small)", 0);
	}
E 80
D 78
	fmask = 1 << f;
	pmask = 1 << p;
E 78
E 52
E 39
E 32
E 26
E 25
	for (;;) {
D 40
		int ibits = 0, obits = 0;
E 40
I 40
D 78
		int ibits, obits, ebits;
E 78
I 78
D 80
		fd_set ibits, obits, ebits;
E 80
I 80
		fd_set ibits, obits, ebits, *omask;
E 80
E 78
E 40

I 84
		FD_ZERO(&ebits);
E 84
I 40
D 78
		ibits = 0;
		obits = 0;
E 78
I 78
		FD_ZERO(&ibits);
		FD_ZERO(&obits);
E 78
E 40
D 80
		if (fcc)
E 80
I 80
		omask = (fd_set *)NULL;
		if (fcc) {
E 80
D 52
			obits |= (1<<p);
E 52
I 52
D 78
			obits |= pmask;
E 78
I 78
			FD_SET(p, &obits);
E 78
E 52
D 80
		else
E 80
I 80
			omask = &obits;
		} else
E 80
D 52
			ibits |= (1<<f);
E 52
I 52
D 78
			ibits |= fmask;
E 78
I 78
			FD_SET(f, &ibits);
E 78
E 52
		if (pcc >= 0)
D 80
			if (pcc)
E 80
I 80
			if (pcc) {
E 80
D 52
				obits |= (1<<f);
E 52
I 52
D 78
				obits |= fmask;
E 78
I 78
				FD_SET(f, &obits);
E 78
E 52
E 24
D 80
			else
E 80
I 80
				omask = &obits;
			} else
E 80
D 24
				ibits |= (1<<f);
E 4
			if (pcc >= 0)
D 4
			if (pcc) obits |= (1<<f); else ibits |= (1<<p);
			if (fcc < 0 && pcc < 0) break;
E 4
I 4
				if (pcc)
					obits |= (1<<f);
				else
					ibits |= (1<<p);
D 19
			if (fcc < 0 && pcc < 0)
				break;
E 19
E 4
/* fprintf(console, "ibits from %d obits from %d\r\n", ibits, obits); */
D 3
			select(32, &ibits, &obits, 10000000);
E 3
I 3
D 19
			select(16, &ibits, &obits, 0, 0, 0);
E 19
I 19
			if (select(16, &ibits, &obits, 0, 0) < 0) {
				if (errno == EINTR)
					continue;
				fatalperror(f, "select", errno);
			}
E 19
E 3
/* fprintf(console, "ibits %d obits %d\r\n", ibits, obits); */
			if (ibits == 0 && obits == 0) {
I 19
				/* shouldn't happen... */
E 19
				sleep(5);
E 24
I 24
D 52
				ibits |= (1<<p);
D 40
		if (select(16, &ibits, &obits, 0, 0) < 0) {
E 40
I 40
		ebits = (1<<p);
		if (select(16, &ibits, &obits, &ebits, 0) < 0) {
E 52
I 52
D 78
				ibits |= pmask;
		ebits = pmask;
		if (select(nfd, &ibits, obits ? &obits : (int *)NULL,
		    &ebits, 0) < 0) {
E 78
I 78
				FD_SET(p, &ibits);
		FD_SET(p, &ebits);
D 80
		if ((n = select(nfd, &ibits, &obits, &ebits, 0)) < 0) {
E 80
I 80
		if ((n = select(nfd, &ibits, omask, &ebits, 0)) < 0) {
E 80
E 78
E 52
E 40
			if (errno == EINTR)
E 24
				continue;
D 24
			}
			if (ibits & (1<<f)) {
				fcc = read(f, fibuf, sizeof (fibuf));
/* fprintf(console, "%d from f\r\n", fcc); */
				if (fcc < 0 && errno == EWOULDBLOCK)
					fcc = 0;
				else {
					if (fcc <= 0)
						break;
					fbp = fibuf;
				}
			}
			if (ibits & (1<<p)) {
				pcc = read(p, pibuf, sizeof (pibuf));
/* fprintf(console, "%d from p, buf[0] %x, errno %d\r\n", pcc, buf[0], errno); */
				pbp = pibuf;
				if (pcc < 0 && errno == EWOULDBLOCK)
					pcc = 0;
				else if (pcc <= 0)
E 24
I 24
D 45
			fatalperror(f, "select", errno);
E 45
I 45
D 78
			fatalperror(f, "select");
E 78
I 78
			fatal(f, "select", 1);
E 78
E 45
		}
D 40
		if (ibits == 0 && obits == 0) {
E 40
I 40
D 78
		if (ibits == 0 && obits == 0 && ebits == 0) {
E 78
I 78
		if (n == 0) {
E 78
E 40
			/* shouldn't happen... */
			sleep(5);
			continue;
		}
I 40
#define	pkcontrol(c)	((c)&(TIOCPKT_FLUSHWRITE|TIOCPKT_NOSTOP|TIOCPKT_DOSTOP))
D 52
		if (ebits & (1<<p)) {
E 52
I 52
D 78
		if (ebits & pmask) {
E 78
I 78
		if (FD_ISSET(p, &ebits)) {
E 78
E 52
			cc = read(p, &cntl, 1);
			if (cc == 1 && pkcontrol(cntl)) {
				cntl |= oobdata[0];
				send(f, &cntl, 1, MSG_OOB);
				if (cntl & TIOCPKT_FLUSHWRITE) {
					pcc = 0;
D 52
					ibits &= ~(1<<p);
E 52
I 52
D 78
					ibits &= ~pmask;
E 78
I 78
					FD_CLR(p, &ibits);
E 78
E 52
				}
			}
		}
E 40
D 52
		if (ibits & (1<<f)) {
E 52
I 52
D 78
		if (ibits & fmask) {
E 52
I 50
D 55
#ifdef	KERBEROS
E 78
I 78
		if (FD_ISSET(f, &ibits)) {
D 89
#ifdef KERBEROS
E 89
I 89
D 90
#if defined(KERBEROS) && defined(CRYPT)
E 90
I 90
D 91
D 96
#ifdef	CRYPT
#ifdef	KERBEROS
E 90
E 89
E 78
D 52
			if(encrypt) {
E 52
I 52
D 93
			if (encrypt)
E 93
I 93
			if (doencrypt)
E 93
E 52
				fcc = des_read(f, fibuf, sizeof(fibuf));
D 52
			} else {
				fcc = read(f, fibuf, sizeof(fibuf));
			}
#else
E 50
			fcc = read(f, fibuf, sizeof (fibuf));
E 52
I 52
			else
E 52
I 50
#endif
I 90
#endif
E 96
E 91
E 90
I 52
				fcc = read(f, fibuf, sizeof(fibuf));
E 55
I 55
			fcc = read(f, fibuf, sizeof(fibuf));
E 55
E 52
E 50
			if (fcc < 0 && errno == EWOULDBLOCK)
				fcc = 0;
			else {
				register char *cp;
				int left, n;

				if (fcc <= 0)
E 24
D 19
					pcc = -1;
E 19
I 19
					break;
E 19
D 24
				else if (pibuf[0] == 0)
					pbp++, pcc--;
				else {
					if (pibuf[0]&(TIOCPKT_FLUSHWRITE|
						      TIOCPKT_NOSTOP|
						      TIOCPKT_DOSTOP)) {
I 19
					/* The following 3 lines do nothing. */
E 19
						int nstop = pibuf[0] &
						    (TIOCPKT_NOSTOP|
						     TIOCPKT_DOSTOP);
						if (nstop)
							stop = nstop;
						pibuf[0] |= nstop;
D 3
						ioctl(f,SIOCSENDOOB,&pibuf[0]);
E 3
I 3
D 15
						send(f,&pibuf[0],1,SOF_OOB);
E 15
I 15
						send(f,&pibuf[0],1,MSG_OOB);
E 24
I 24
				fbp = fibuf;
I 32

E 32
			top:
D 39
				for (cp = fibuf; cp < fibuf+fcc; cp++)
E 39
I 39
				for (cp = fibuf; cp < fibuf+fcc-1; cp++)
E 39
					if (cp[0] == magic[0] &&
					    cp[1] == magic[1]) {
						left = fcc - (cp-fibuf);
						n = control(p, cp, left);
						if (n) {
							left -= n;
							if (left > 0)
D 39
								bcopy(cp, cp+n, left);
E 39
I 39
								bcopy(cp+n, cp, left);
E 39
							fcc -= n;
							goto top; /* n^2 */
D 32
						}
E 24
E 15
E 3
					}
E 32
I 32
D 39
						} /* if (n) */
					} /* for (cp = ) */
				} /* else */
		} /* if (ibits & (1<<f)) */
E 39
I 39
						}
					}
I 52
D 78
				obits |= pmask;		/* try write */
E 78
I 78
				FD_SET(p, &obits);		/* try write */
E 78
E 52
			}
		}
E 39

D 52
		if ((obits & (1<<p)) && fcc > 0) {
E 52
I 52
D 78
		if ((obits & pmask) && fcc > 0) {
E 78
I 78
		if (FD_ISSET(p, &obits) && fcc > 0) {
E 78
E 52
D 39
			wsize = fcc;
			do {
				cc = write(p, fbp, wsize);
				wsize /= 2;
			} while (cc<0 && errno==EWOULDBLOCK && wsize);
E 39
I 39
			cc = write(p, fbp, fcc);
E 39
			if (cc > 0) {
				fcc -= cc;
				fbp += cc;
E 32
D 24
					pcc = 0;
				}
E 24
			}
D 24
			if ((obits & (1<<f)) && pcc > 0) {
				cc = write(f, pbp, pcc);
I 19
				if (cc < 0 && errno == EWOULDBLOCK) {
					/* also shouldn't happen */
					sleep(5);
					continue;
E 24
I 24
		}
I 32

E 32
D 52
		if (ibits & (1<<p)) {
E 52
I 52
D 78
		if (ibits & pmask) {
E 78
I 78
		if (FD_ISSET(p, &ibits)) {
E 78
E 52
			pcc = read(p, pibuf, sizeof (pibuf));
			pbp = pibuf;
			if (pcc < 0 && errno == EWOULDBLOCK)
				pcc = 0;
			else if (pcc <= 0)
				break;
D 52
			else if (pibuf[0] == 0)
E 52
I 52
			else if (pibuf[0] == 0) {
E 52
				pbp++, pcc--;
D 52
			else {
E 52
I 52
D 55
D 78
#ifdef	KERBEROS
E 78
I 78
D 89
#ifdef KERBEROS
E 89
I 89
D 90
#if defined(KERBEROS) && defined(CRYPT)
E 90
I 90
D 91
D 96
#ifdef	CRYPT
#ifdef	KERBEROS
E 90
E 89
E 78
D 93
				if (!encrypt)
E 93
I 93
				if (!doencrypt)
E 93
#endif
I 90
#endif
E 96
E 91
E 90
D 78
					obits |= fmask;	/* try a write */
E 78
I 78
					FD_SET(f, &obits);	/* try write */
E 78
E 55
I 55
				obits |= fmask;	/* try a write */
E 55
			} else {
E 52
D 40
#define	pkcontrol(c)	((c)&(TIOCPKT_FLUSHWRITE|TIOCPKT_NOSTOP|TIOCPKT_DOSTOP))
E 40
I 32
D 39
				int out = FREAD;

E 39
E 32
				if (pkcontrol(pibuf[0])) {
D 39
				/* The following 3 lines do nothing. */
					int nstop = pibuf[0] &
					    (TIOCPKT_NOSTOP|TIOCPKT_DOSTOP);

					if (nstop)
						stop = nstop;
D 37
					pibuf[0] |= nstop;
E 37
I 37
					pibuf[0] |= nstop | oob[0];
E 39
I 39
					pibuf[0] |= oobdata[0];
E 39
E 37
					send(f, &pibuf[0], 1, MSG_OOB);
I 32
D 39
					if (pibuf[0] & TIOCPKT_FLUSHWRITE)
					  ioctl(p, TIOCFLUSH, (char *)&out);

E 39
E 32
E 24
				}
E 19
D 24
/* fprintf(console, "%d of %d to f\r\n", cc, pcc); */
				if (cc > 0) {
					pcc -= cc;
					pbp += cc;
				}
E 24
I 24
				pcc = 0;
E 24
			}
D 24
			if ((obits & (1<<p)) && fcc > 0) {
				cc = write(p, fbp, fcc);
/* fprintf(console, "%d of %d to p\r\n", cc, fcc); */
				if (cc > 0) {
					fcc -= cc;
					fbp += cc;
				}
E 24
I 24
		}
D 52
		if ((obits & (1<<f)) && pcc > 0) {
E 52
I 52
D 78
		if ((obits & fmask) && pcc > 0) {
E 52
I 50
D 55
#ifdef	KERBEROS
E 78
I 78
		if ((FD_ISSET(f, &obits)) && pcc > 0) {
D 89
#ifdef KERBEROS
E 89
I 89
D 90
#if defined(KERBEROS) && defined(CRYPT)
E 90
I 90
D 91
D 96
#ifdef	CRYPT
#ifdef	KERBEROS
E 90
E 89
E 78
D 52
			if(encrypt) {
E 52
I 52
D 93
			if (encrypt)
E 93
I 93
			if (doencrypt)
E 93
E 52
				cc = des_write(f, pbp, pcc);
D 52
			} else {
				cc = write(f, pbp, pcc);
			}
#else
E 50
D 32
			cc = write(f, pbp, pcc);
			if (cc < 0 && errno == EWOULDBLOCK) {
				/* also shouldn't happen */
				sleep(5);
				continue;
E 24
			}
E 32
I 32
D 39
			wsize = pcc;
			do {
				cc = write(f, pbp, wsize);
				wsize /= 2;
			} while (cc<0 && errno==EWOULDBLOCK && wsize);
E 39
I 39
			cc = write(f, pbp, pcc);
E 52
I 52
			else
I 90
#endif
E 90
E 52
I 50
#endif
E 96
E 91
I 52
				cc = write(f, pbp, pcc);
E 55
I 55
			cc = write(f, pbp, pcc);
E 55
E 52
E 50
			if (cc < 0 && errno == EWOULDBLOCK) {
D 80
				/* also shouldn't happen */
				sleep(5);
E 80
I 80
				/*
				 * This happens when we try write after read
				 * from p, but some old kernels balk at large
				 * writes even when select returns true.
				 */
				if (!FD_ISSET(p, &ibits))
					sleep(5);
E 80
				continue;
			}
E 39
E 32
I 24
			if (cc > 0) {
				pcc -= cc;
				pbp += cc;
D 32
			}
E 24
		}
D 24
		cleanup();
E 24
I 24
		if ((obits & (1<<p)) && fcc > 0) {
			cc = write(p, fbp, fcc);
			if (cc > 0) {
				fcc -= cc;
				fbp += cc;
E 32
			}
		}
E 24
	}
D 24
	close(f);
	close(p);
	dup2(t, 0);
	dup2(t, 1);
	dup2(t, 2);
	close(t);
D 2
	execl("/bin/login", "login", "-r", rhost, 0);
E 2
I 2
	execl("/bin/login", "login", "-r", hp->h_name, 0);
E 2
D 4
	perror("/bin/login");
	exit(1);
E 4
I 4
	fatalperror(2, "/bin/login", errno);
	/*NOTREACHED*/
E 24
E 4
}

I 93
void
E 93
D 98
cleanup()
E 98
I 98
cleanup(signo)
	int signo;
E 98
{
D 8
	int how = 2;
E 8
D 46

E 46
D 47
	rmut();
E 47
I 47
	char *p;

D 78
	p = line + sizeof("/dev/") - 1;
E 78
I 78
	p = line + sizeof(_PATH_DEV) - 1;
E 78
	if (logout(p))
		logwtmp(p, "", "");
D 93
	(void)chmod(line, 0666);
E 93
I 93
D 95
	(void)chmod(line, DEFFILEMODE);
E 95
I 95
	(void)chmod(line, 0666);
E 95
E 93
	(void)chown(line, 0, 0);
	*p = 'p';
D 93
	(void)chmod(line, 0666);
E 93
I 93
D 95
	(void)chmod(line, DEFFILEMODE);
E 95
I 95
	(void)chmod(line, 0666);
E 95
E 93
	(void)chown(line, 0, 0);
E 47
I 7
D 46
	vhangup();		/* XXX */
E 46
E 7
D 8
	ioctl(netf, SIOCDONE, &how);
E 8
I 8
	shutdown(netf, 2);
E 8
D 38
	kill(0, SIGKILL);
E 38
	exit(1);
I 4
}

I 97
void
E 97
D 78
fatal(f, msg)
	int f;
E 78
I 78
fatal(f, msg, syserr)
D 97
	int f, syserr;
E 97
I 97
	int f;
E 97
E 78
	char *msg;
I 97
	int syserr;
E 97
{
I 78
	int len;
E 78
D 80
	char buf[BUFSIZ];
E 80
I 80
	char buf[BUFSIZ], *bp = buf;
E 80

D 80
	buf[0] = '\01';		/* error indicator */
E 80
I 80
	/*
	 * Prepend binary one to message if we haven't sent
	 * the magic null as confirmation.
	 */
	if (!confirmed)
		*bp++ = '\01';		/* error indicator */
E 80
D 18
	(void) sprintf(buf + 1, "rlogind: %s.\n", msg);
E 18
I 18
D 78
	(void) sprintf(buf + 1, "rlogind: %s.\r\n", msg);
E 18
	(void) write(f, buf, strlen(buf));
E 78
I 78
	if (syserr)
D 80
		len = sprintf(buf + 1, "rlogind: %s: %s.\r\n",
E 80
I 80
		len = sprintf(bp, "rlogind: %s: %s.\r\n",
E 80
		    msg, strerror(errno));
	else
D 80
		len = sprintf(buf + 1, "rlogind: %s.\r\n", msg);
	(void) write(f, buf, len);
E 80
I 80
		len = sprintf(bp, "rlogind: %s.\r\n", msg);
	(void) write(f, buf, bp + len - buf);
E 80
E 78
	exit(1);
}

D 45
fatalperror(f, msg, errno)
E 45
I 45
D 78
fatalperror(f, msg)
E 45
	int f;
	char *msg;
D 45
	int errno;
E 45
{
	char buf[BUFSIZ];
I 19
	extern int sys_nerr;
E 19
	extern char *sys_errlist[];

D 19
	(void) sprintf(buf, "%s: %s", msg, sys_errlist[errno]);
E 19
I 19
D 24
	if ((unsigned) errno < sys_nerr)
E 24
I 24
	if ((unsigned)errno < sys_nerr)
E 24
		(void) sprintf(buf, "%s: %s", msg, sys_errlist[errno]);
	else
		(void) sprintf(buf, "%s: Error %d", msg, errno);
E 19
	fatal(f, buf);
E 4
D 47
}

#include <utmp.h>

struct	utmp wtmp;
char	wtmpf[]	= "/usr/adm/wtmp";
D 28
char	utmp[] = "/etc/utmp";
E 28
I 28
char	utmpf[] = "/etc/utmp";
E 28
#define SCPYN(a, b)	strncpy(a, b, sizeof(a))
#define SCMPN(a, b)	strncmp(a, b, sizeof(a))

rmut()
{
	register f;
	int found = 0;
I 28
	struct utmp *u, *utmp;
	int nutmp;
	struct stat statbf;
E 28

D 24
	f = open(utmp, 2);
E 24
I 24
D 28
	f = open(utmp, O_RDWR);
E 28
I 28
	f = open(utmpf, O_RDWR);
E 28
E 24
	if (f >= 0) {
D 28
		while(read(f, (char *)&wtmp, sizeof(wtmp)) == sizeof(wtmp)) {
			if (SCMPN(wtmp.ut_line, line+5) || wtmp.ut_name[0]==0)
				continue;
D 24
			lseek(f, -(long)sizeof(wtmp), 1);
E 24
I 24
			lseek(f, -(long)sizeof(wtmp), L_INCR);
E 24
			SCPYN(wtmp.ut_name, "");
I 14
			SCPYN(wtmp.ut_host, "");
E 14
			time(&wtmp.ut_time);
			write(f, (char *)&wtmp, sizeof(wtmp));
			found++;
E 28
I 28
		fstat(f, &statbf);
		utmp = (struct utmp *)malloc(statbf.st_size);
		if (!utmp)
			syslog(LOG_ERR, "utmp malloc failed");
		if (statbf.st_size && utmp) {
			nutmp = read(f, utmp, statbf.st_size);
			nutmp /= sizeof(struct utmp);
		
			for (u = utmp ; u < &utmp[nutmp] ; u++) {
				if (SCMPN(u->ut_line, line+5) ||
				    u->ut_name[0]==0)
					continue;
				lseek(f, ((long)u)-((long)utmp), L_SET);
				SCPYN(u->ut_name, "");
				SCPYN(u->ut_host, "");
				time(&u->ut_time);
				write(f, (char *)u, sizeof(wtmp));
				found++;
			}
E 28
		}
		close(f);
	}
	if (found) {
D 24
		f = open(wtmpf, 1);
E 24
I 24
D 28
		f = open(wtmpf, O_WRONLY);
E 28
I 28
		f = open(wtmpf, O_WRONLY|O_APPEND);
E 28
E 24
		if (f >= 0) {
			SCPYN(wtmp.ut_line, line+5);
			SCPYN(wtmp.ut_name, "");
I 14
			SCPYN(wtmp.ut_host, "");
E 14
			time(&wtmp.ut_time);
D 24
			lseek(f, (long)0, 2);
E 24
I 24
D 28
			lseek(f, (long)0, L_XTND);
E 28
E 24
			write(f, (char *)&wtmp, sizeof(wtmp));
			close(f);
		}
	}
	chmod(line, 0666);
	chown(line, 0, 0);
	line[strlen("/dev/")] = 'p';
	chmod(line, 0666);
	chown(line, 0, 0);
E 47
I 12
D 24
}

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

	p = (char *)&in;
#define	UC(b)	(((int)b)&0xff)
	sprintf(b, "%d.%d.%d.%d", UC(p[0]), UC(p[1]), UC(p[2]), UC(p[3]));
	return (b);
E 24
E 12
}
I 50

E 78
I 54
#ifndef OLD_LOGIN
E 54
D 53

int
E 53
D 97
do_rlogin(host)
D 53
	char	*host;
E 53
I 53
	char *host;
E 97
I 97
int
do_rlogin(dest)
	struct sockaddr_in *dest;
E 97
E 53
{
D 53
	getstr(rusername, sizeof(rusername), "remuser");
	getstr(lusername, sizeof(lusername), "locuser");
	getstr(term+ENVSIZE, sizeof(term)-ENVSIZE, "Terminal type");
E 53
D 78

E 78
D 53
	if(getuid()) {
		pwd = &nouser;
E 53
I 53
	getstr(rusername, sizeof(rusername), "remuser too long");
	getstr(lusername, sizeof(lusername), "locuser too long");
	getstr(term+ENVSIZE, sizeof(term)-ENVSIZE, "Terminal type too long");

D 83
	if (getuid())
E 53
		return(-1);
E 83
D 53
	}
E 53
	pwd = getpwnam(lusername);
D 53
	if(pwd == NULL) {
		pwd = &nouser;
		pwd->pw_name = lusername;	/* pass on to login */
E 53
I 53
	if (pwd == NULL)
E 53
D 97
		return(-1);
E 97
I 97
		return (-1);
E 97
D 53
	}
E 53
D 83
	return(ruserok(host, SUPERUSER(pwd), rusername, lusername));
E 83
I 83
	if (pwd->pw_uid == 0)
D 97
		return(-1);
	return(ruserok(host, 0, rusername, lusername));
E 97
I 97
		return (-1);
	/* XXX why don't we syslog() failure? */
	return (iruserok(dest->sin_addr.s_addr, 0, rusername, lusername));
E 97
E 83
}

D 97

E 97
I 97
void
E 97
D 53
getstr(buf, cnt, err)
	char	*buf;
	int	cnt;
	char	*err;
E 53
I 53
getstr(buf, cnt, errmsg)
	char *buf;
	int cnt;
	char *errmsg;
E 53
{
D 53
	char	c;
E 53
I 53
	char c;

E 53
	do {
D 53
		if(read(0, &c, 1) != 1)
E 53
I 53
		if (read(0, &c, 1) != 1)
E 53
			exit(1);
D 53
		if(--cnt < 0) {
			printf("%s too long\r\n", err);
			exit(1);
		}
E 53
I 53
		if (--cnt < 0)
D 78
			fatal(1, errmsg);
E 78
I 78
			fatal(STDOUT_FILENO, errmsg, 0);
E 78
E 53
		*buf++ = c;
D 53
	} while(c != 0);
E 53
I 53
	} while (c != 0);
E 53
}

D 53
extern	char	**environ;
E 53
I 53
D 102
extern	char **environ;
E 53

E 102
I 97
void
E 97
I 54
D 55
#ifdef TERMIOS
E 54
setup_term(fd)
D 53
	int	fd;
E 53
I 53
	int fd;
E 53
{
D 53
	struct	termios	tt;
	struct	sgttyb	tp;
	register char	*cp = index(term+ENVSIZE, '/'), **cpp;
	char		*speed;
E 53
I 53
D 74
	struct termios tt;
E 74
	register char *cp = index(term+ENVSIZE, '/');
	char *speed;
E 53
D 77

E 77
I 74
	struct termios tt;
I 77

#ifndef notyet
E 77
E 74
	tcgetattr(fd, &tt);
D 53
	if(cp) {
E 53
I 53
	if (cp) {
E 53
		*cp++ = '\0';
		speed = cp;
		cp = index(speed, '/');
D 53
		if(cp)
E 53
I 53
		if (cp)
E 53
			*cp++ = '\0';
		cfsetspeed(&tt, atoi(speed));
	}
I 74

D 77

E 74
	tt.c_iflag = BRKINT|ICRNL|IXON|ISTRIP|IEXTEN|IMAXBEL;
	tt.c_oflag = OPOST|ONLCR|OXTABS;
	tt.c_lflag = ISIG|ICANON|ECHO;
E 77
I 77
	tt.c_iflag = TTYDEF_IFLAG;
	tt.c_oflag = TTYDEF_OFLAG;
	tt.c_lflag = TTYDEF_LFLAG;
E 77
D 85
	tcsetattr(fd, TCSADFLUSH, &tt);
E 85
I 85
	tcsetattr(fd, TCSAFLUSH, &tt);
E 85
I 74
D 77
#ifdef	notdef
	{
		struct	sgttyb	b;
		(void) ioctl(fd, TIOCGETP, &b);
		b.sg_flags = ECHO|CRMOD|ANYP;
		b.sg_ispeed = b.sg_ospeed = atoi(speed);
		(void) ioctl(fd, TIOCSETP, &b);
E 77
I 77
#else
	if (cp) {
		*cp++ = '\0';
		speed = cp;
		cp = index(speed, '/');
		if (cp)
			*cp++ = '\0';
		tcgetattr(fd, &tt);
		cfsetspeed(&tt, atoi(speed));
D 85
		tcsetattr(fd, TCSADFLUSH, &tt);
E 85
I 85
		tcsetattr(fd, TCSAFLUSH, &tt);
E 85
E 77
	}
#endif
E 74

D 53
	envinit[0] = term;
	envinit[1] = 0;
	environ = envinit;
E 53
I 53
	env[0] = term;
	env[1] = 0;
D 102
	environ = env;
E 102
E 53
}
I 54
#else /* TERMIOS */
E 55
char *speeds[] = {
	"0", "50", "75", "110", "134", "150", "200", "300", "600",
	"1200", "1800", "2400", "4800", "9600", "19200", "38400",
};
#define	NSPEEDS	(sizeof(speeds) / sizeof(speeds[0]))

setup_term(fd)
	int fd;
{
	register char *cp = index(term, '/'), **cpp;
D 76
	struct sgttyb sgttyb;
E 76
	char *speed;
I 76
#if BSD > 43
	struct termios tt;
E 76

I 76
	tcgetattr(fd, &tt);
	if (cp) {
		*cp++ = '\0';
		speed = cp;
		cp = index(speed, '/');
		if (cp)
			*cp++ = '\0';
		cfsetspeed(&tt, atoi(speed));
	}

	tt.c_iflag = TTYDEF_IFLAG;
	tt.c_oflag = TTYDEF_OFLAG;
	tt.c_lflag = TTYDEF_LFLAG;
	tcsetattr(fd, TCSADFLUSH, &tt);
#else
	struct sgttyb sgttyb;

E 76
	(void)ioctl(fd, TIOCGETP, &sgttyb);
	if (cp) {
		*cp++ = '\0';
		speed = cp;
		cp = index(speed, '/');
		if (cp)
			*cp++ = '\0';
		for (cpp = speeds; cpp < &speeds[NSPEEDS]; cpp++)
		    if (strcmp(*cpp, speed) == 0) {
			sgttyb.sg_ispeed = sgttyb.sg_ospeed = cpp - speeds;
			break;
		    }
	}
	sgttyb.sg_flags = ECHO|CRMOD|ANYP|XTABS;
	(void)ioctl(fd, TIOCSETP, &sgttyb);
I 76
#endif
E 76

	env[0] = term;
	env[1] = 0;
	environ = env;
I 62
}

/*
 * Check whether host h is in our local domain,
D 76
 * as determined by the part of the name following
 * the first '.' in its name and in ours.
E 76
I 76
 * defined as sharing the last two components of the domain part,
 * or the entire domain part if the local domain has only one component.
E 76
 * If either name is unqualified (contains no '.'),
 * assume that the host is local, as it will be
 * interpreted as such.
 */
local_domain(h)
	char *h;
{
	char localhost[MAXHOSTNAMELEN];
D 76
	char *p1, *p2 = index(h, '.');
E 76
I 76
	char *p1, *p2, *topdomain();
E 76

I 76
	localhost[0] = 0;
E 76
	(void) gethostname(localhost, sizeof(localhost));
D 76
	p1 = index(localhost, '.');
E 76
I 76
	p1 = topdomain(localhost);
	p2 = topdomain(h);
E 76
	if (p1 == NULL || p2 == NULL || !strcasecmp(p1, p2))
		return(1);
	return(0);
I 76
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
E 76
E 62
}
D 55
#endif /* TERMIOS */
E 55
#endif /* OLD_LOGIN */
E 54
D 55

#ifdef	KERBEROS
#define	VERSION_SIZE	9

/*
 * Do the remote kerberos login to the named host with the
 * given inet address
 *
 * Return 0 on valid authorization
 * Return -1 on valid authentication, no authorization
 * Return >0 for error conditions
 */
D 53

int
E 53
D 93
do_krb_login(host, dest, encrypt)
E 93
I 93
D 97
do_krb_login(host, dest)
E 93
D 53
	char			*host;
	struct	sockaddr_in	*dest;
	int			encrypt;
E 53
I 53
	char *host;
E 97
I 97
int
do_krb_login(dest)
E 97
	struct sockaddr_in *dest;
D 93
	int encrypt;
E 93
E 53
{
D 53
	int	rc;
	char	instance[INST_SZ], version[VERSION_SIZE];
	long	authopts = 0L;	/* !mutual */
	struct	sockaddr_in	faddr;
E 53
I 53
	int rc;
	char instance[INST_SZ], version[VERSION_SIZE];
	long authopts = 0L;	/* !mutual */
	struct sockaddr_in faddr;
E 53

D 53
	if(getuid()) {
		pwd = &nouser;
E 53
I 53
D 83
	if (getuid())
E 53
		return(KFAILURE);
D 53
	}
E 53

E 83
	kdata = (AUTH_DAT *) auth_buf;
	ticket = (KTEXT) tick_buf;
D 83
	strcpy(instance, "*");
E 83

I 83
	instance[0] = '*';
	instance[1] = '\0';

I 89
D 91
D 96
#ifdef	CRYPT
E 89
E 83
D 53
	if(encrypt) {
E 53
I 53
D 93
	if (encrypt) {
E 93
I 93
	if (doencrypt) {
E 93
E 53
		rc = sizeof(faddr);
D 53
		if(getsockname(0, &faddr, &rc)) {
			pwd = &nouser;
E 53
I 53
D 93
		if (getsockname(0, &faddr, &rc))
E 93
I 93
		if (getsockname(0, (struct sockaddr *)&faddr, &rc))
E 93
E 53
D 97
			return(-1);
E 97
I 97
			return (-1);
E 97
D 53
		}
E 53
		authopts = KOPT_DO_MUTUAL;
		rc = krb_recvauth(
			authopts, 0,
			ticket, "rcmd",
			instance, dest, &faddr,
D 52
			kdata, "", schedule, version
		 );
E 52
I 52
			kdata, "", schedule, version);
E 52
		 des_set_key(kdata->session, schedule);

D 89
	} else {
E 89
I 89
	} else
#endif
E 96
E 91
E 89
		rc = krb_recvauth(
			authopts, 0,
			ticket, "rcmd",
			instance, dest, (struct sockaddr_in *) 0,
D 52
			kdata, "", (bit_64 *) 0, version
		 );
E 52
I 52
			kdata, "", (bit_64 *) 0, version);
E 52
D 89
	}
E 89

D 53
	if(rc != KSUCCESS) {
		pwd = &nouser;
E 53
I 53
	if (rc != KSUCCESS)
E 53
D 97
		return(rc);
E 97
I 97
		return (rc);
E 97
D 53
	}
E 53

D 53
	if((rc = krb_kntoln(kdata, rusername)) != KSUCCESS) {
		pwd = &nouser;
E 53
I 53
D 71
	if ((rc = krb_kntoln(kdata, rusername)) != KSUCCESS)
E 53
		return(rc);
D 53
	}
E 53

E 71
	getstr(lusername, sizeof(lusername), "locuser");
	/* get the "cmd" in the rcmd protocol */
	getstr(term+ENVSIZE, sizeof(term)-ENVSIZE, "Terminal type");

	pwd = getpwnam(lusername);
D 53
	if(pwd == NULL) {
		pwd = &nouser;
		pwd->pw_name = lusername;
E 53
I 53
	if (pwd == NULL)
E 53
D 97
		return(-1);
E 97
I 97
		return (-1);
E 97
D 53
	}
E 53

D 56
	/* XXX need to use something other than ruserok */
	/* returns -1 for invalid authentication */
	return(ruserok(host, SUPERUSER(pwd), rusername, lusername));
E 56
I 56
	/* returns nonzero for no access */
D 83
	/* return(ruserok(host, SUPERUSER(pwd), rusername, lusername)); */
E 83
D 61
	if(kuserok(kdata,lusername) != 0)
E 61
I 61
D 97
	if (kuserok(kdata,lusername) != 0)
E 61
		return(-1);
E 97
I 97
	if (kuserok(kdata, lusername) != 0)
		return (-1);
E 97
	
D 97
	return(0);
E 97
I 97
	return (0);
E 97

E 56
}
I 56
D 78

E 78
E 56
D 53
#endif
E 53
I 53
#endif /* KERBEROS */
I 56

I 97
void
E 97
usage()
{
D 78
#ifdef	KERBEROS
D 75
	syslog(LOG_ERR, "usage: rlogind [-k | -v] [-l] [-n]");
E 75
I 75
	syslog(LOG_ERR, "usage: rlogind [-k | -v] [-a] [-l] [-n]");
E 78
I 78
#ifdef KERBEROS
	syslog(LOG_ERR, "usage: rlogind [-aln] [-k | -v]");
E 78
E 75
#else
D 75
	syslog(LOG_ERR, "usage: rlogind [-l] [-n]");
E 75
I 75
D 78
	syslog(LOG_ERR, "usage: rlogind [-a] [-l] [-n]");
E 78
I 78
	syslog(LOG_ERR, "usage: rlogind [-aln]");
E 78
E 75
#endif
I 59
}

D 61
int
same_domain(h1, h2)
	char	*h1, *h2;
E 61
I 61
/*
 * Check whether host h is in our local domain,
D 75
 * as determined by the part of the name following
 * the first '.' in its name and in ours.
E 75
I 75
 * defined as sharing the last two components of the domain part,
 * or the entire domain part if the local domain has only one component.
E 75
 * If either name is unqualified (contains no '.'),
 * assume that the host is local, as it will be
 * interpreted as such.
 */
I 97
int
E 97
local_domain(h)
	char *h;
E 61
{
D 61
	register char *p1 = index(h1, '.');
	register char *p2 = index(h2, '.');
	if(!strcasecmp(p1, p2))
E 61
I 61
	char localhost[MAXHOSTNAMELEN];
D 75
	char *p1, *p2 = index(h, '.');
E 75
I 75
D 97
	char *p1, *p2, *topdomain();
E 97
I 97
	char *p1, *p2;
E 97
E 75

I 75
	localhost[0] = 0;
E 75
	(void) gethostname(localhost, sizeof(localhost));
D 75
	p1 = index(localhost, '.');
E 75
I 75
	p1 = topdomain(localhost);
	p2 = topdomain(h);
E 75
	if (p1 == NULL || p2 == NULL || !strcasecmp(p1, p2))
E 61
D 97
		return(1);
	return(0);
E 97
I 97
		return (1);
	return (0);
E 97
I 75
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
E 75
E 59
}
E 56
E 55
E 53
E 50
E 1
