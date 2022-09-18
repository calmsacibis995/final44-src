h39568
s 00002/00000/00566
d D 8.4 94/04/02 10:34:15 pendry 131 130
c don't allow kerberos root login if the root instance is missing
e
s 00038/00035/00528
d D 8.3 94/04/02 08:38:45 pendry 130 129
c prettyness police
e
s 00003/00003/00560
d D 8.2 94/02/24 06:17:27 bostic 129 128
c update the copyright notice
e
s 00005/00005/00558
d D 8.1 93/06/09 22:44:10 bostic 128 127
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00559
d D 5.79 93/06/01 23:24:29 mckusick 127 126
c update login copyright string
e
s 00012/00007/00550
d D 5.78 92/06/29 12:52:24 bostic 126 125
c ANSI C cleanups
e
s 00067/00051/00487
d D 5.77 92/04/26 17:52:42 bostic 125 124
c the prettiness police welcome login to ANSI; no real changes
e
s 00006/00015/00532
d D 5.76 92/04/26 17:33:33 bostic 124 123
c rootlogin should be set early in the loop
e
s 00002/00000/00545
d D 5.75 91/11/19 22:50:38 marc 123 122
c reset rootlogin=0 so successive attempts to login with valid name succeed
e
s 00001/00001/00544
d D 5.74 91/07/31 17:09:53 bostic 122 121
c wrong expire value for password; bug report 4.3BSD-reno/usr.bin/22
e
s 00005/00005/00540
d D 5.73 91/06/29 13:23:29 bostic 121 120
c document -h option, exit 1 if exec fails, minor cleanups
e
s 00001/00000/00544
d D 5.72 91/06/28 11:51:09 bostic 120 119
c set LOGNAME for POSIX.2
e
s 00001/00001/00543
d D 5.71 91/06/27 15:05:04 bostic 119 118
c correct error message for -h option by unprivileged user
e
s 00058/00047/00486
d D 5.70 91/06/02 17:38:42 karels 118 116
c various cleanups: allow any instance to be attempted; no syslog
c if there is no Kerberos realm; fix up error msgs; allow user.root login
c via Kerberos on any tty
e
s 00046/00032/00501
d R 5.70 91/06/01 15:13:07 karels 117 116
c various cleanups: allow any instance to be attempted; no syslog
c if there is no Kerberos realm; fix up error msgs; allow user.root login
c via Kerberos on any tty
e
s 00000/00001/00533
d D 5.69 91/05/10 12:51:23 marc 116 115
c don't set tty mode - should already be done (and too late if not)
e
s 00034/00010/00500
d D 5.68 91/03/29 17:57:20 kfall 115 114
c update to use "person.root" login for kerberos
e
s 00006/00003/00504
d D 5.67 91/03/15 12:20:21 karels 114 113
c try to satisfy General Counsel
e
s 00002/00001/00505
d D 5.66 91/03/01 14:56:31 bostic 113 112
c ANSI
e
s 00000/00001/00506
d D 5.65 91/02/05 11:15:04 karels 112 111
c don't need sgtty.h now
e
s 00011/00004/00496
d D 5.64 90/10/29 16:10:51 bostic 111 109
c change so that user entered info gets put in secure logfile
e
s 00020/00013/00487
d R 5.64 90/09/30 17:35:23 bostic 110 109
c change so that user entered info gets put in secure logfile
e
s 00000/00004/00500
d D 5.63 90/06/29 14:08:56 marc 109 108
c tty is already prep'd - remove unnecessary code
e
s 00003/00028/00501
d D 5.62 90/06/29 00:13:30 marc 108 107
c rip out tty initializations (done elsewhere)
e
s 00003/00001/00526
d D 5.61 90/06/27 22:51:18 karels 107 106
c don't do duplicate ROOT login logs from rlogind w/ kerberos
c (and rlogind knows more)
e
s 00007/00017/00520
d D 5.60 90/06/24 18:15:45 bostic 106 105
c make -f work for root, simplify the code
e
s 00004/00004/00533
d D 5.59 90/06/24 16:52:52 bostic 105 104
c don't show nologin stuff until have a valid password
e
s 00006/00017/00531
d D 5.58 90/06/24 16:25:22 bostic 104 103
c replace localtime/printf combinations with calls to ctime
e
s 00019/00018/00529
d D 5.57 90/06/24 16:19:33 bostic 103 102
c make unknown login name parallel real login so looks the same
e
s 00043/00187/00504
d D 5.56 90/06/24 15:48:48 bostic 102 101
c move Kerberos code into klogin.c; CFLUSH -> CDISCARD; errno.h declares
c errno; clean up local variables; fix for POSIX signals; don't indirect
c through NULL pwd pointer; minor lint stuff; getstr() function never used;
c truncate login name to UT_NAMESIZE if taken from command line
e
s 00002/00002/00689
d D 5.55 90/05/31 14:17:35 bostic 101 100
c move openlog before syslog call
e
s 00001/00001/00690
d D 5.54 90/05/15 20:02:01 bostic 100 99
c string.h is ANSI C include file
e
s 00001/00000/00690
d D 5.53 90/05/11 22:46:48 kfall 99 98
c now includes kerberosIV/des.h
e
s 00000/00020/00690
d D 5.52 90/05/06 14:05:36 mckusick 98 97
c no more interaction with quotas
e
s 00001/00001/00709
d D 5.51 90/04/03 10:34:24 bostic 97 96
c include from kerberosIV directory
e
s 00002/00002/00708
d D 5.50 90/03/14 15:14:56 bostic 96 95
c envinit must be initialized to NULL
e
s 00002/00002/00708
d D 5.49 90/02/02 21:40:39 sklower 95 94
c change setlogname --> setlogin
e
s 00035/00034/00675
d D 5.48 89/10/12 17:30:57 kfall 94 93
c added some root terminal protection
e
s 00022/00019/00687
d D 5.47 89/08/24 16:39:25 kfall 93 92
c unlink ticket file before initializing new one; fix libkrb.a to
c clean up the setreuid stuff. [now we chown the ticket file]
e
s 00006/00000/00700
d D 5.46 89/08/23 20:33:56 kfall 92 91
c fix ticket file ownership (look at this again later)
e
s 00000/00004/00700
d D 5.45 89/08/22 16:29:20 kfall 91 90
c remove BSD ifdefs
e
s 00065/00015/00639
d D 5.44 89/08/22 16:23:54 kfall 90 89
c numerous Kerberos, syslog changes; signal() is now type sig_t
e
s 00001/00006/00653
d D 5.43 89/08/14 18:16:35 bostic 89 88
c new tty driver
e
s 00008/00005/00651
d D 5.42 89/06/02 09:02:24 bostic 88 87
c use tzfile.h #defines; tests for expiration were reversed
e
s 00069/00010/00587
d D 5.41 89/05/17 17:21:37 kfall 87 86
c add protection against masquerading Kerberos server
e
s 00012/00005/00585
d D 5.40 89/05/09 13:33:07 bostic 86 85
c file system reorg; paths.h; add setlogname, clean up getpwent()
e
s 00001/00001/00589
d D 5.39 89/04/02 11:59:35 bostic 85 84
c rest of pathnames
e
s 00036/00033/00554
d D 5.38 89/03/17 15:51:01 bostic 84 82
c don't let user force core dump; KNF some Kerberos stuff; 
c make date printf's work for 2000's, minor cleanups
e
s 00091/00004/00550
d D 5.32.1.3 89/03/17 12:46:00 bostic 83 79
c add in -r flag for shadow password package
e
s 00005/00004/00582
d D 5.37 89/03/14 08:40:25 bostic 82 81
c for marc; hushlogin for password expiration and Kerberos messages
e
s 00001/00001/00585
d D 5.36 89/03/05 21:34:48 bostic 81 80
c forgot one
e
s 00007/00013/00579
d D 5.35 89/03/05 21:33:44 bostic 80 78
c add pathnames.h
e
s 00032/00001/00522
d D 5.32.1.2 89/02/23 18:04:01 bostic 79 76
c add shadow passwords to branch for distribution
e
s 00033/00002/00559
d D 5.34 89/02/23 17:56:34 bostic 78 77
c add password/change account/expiration timeouts
e
s 00012/00007/00549
d D 5.33 89/02/07 21:59:25 kfall 77 75
c use new krb library, correct ownership of ticket file, 
c people w/valid Kerb. passwords but not in pw file get "login incorrect"
e
s 00000/00033/00523
d D 5.32.1.1 89/01/28 17:08:18 karels 76 75
c branch without Kerberos (network release)
e
s 00001/00001/00555
d D 5.32 89/01/28 16:51:34 karels 75 74
c restore SCCS keywords (grrr)
e
s 00044/00051/00512
d D 5.31 89/01/28 16:50:12 karels 74 73
c not so noisy: don't log failures if same login name succeeds,
c don't use LOG_ERR for user actions, don't log single mistyped user name
c if another name is then tried; undo some grot; use KNF!
e
s 00041/00005/00522
d D 5.30 89/01/24 13:04:36 kfall 73 72
c add Kerberos ifdefs and bzero password ASAP
e
s 00008/00001/00519
d D 5.29 89/01/20 11:42:40 bostic 72 71
c null pointer dereference
e
s 00001/00001/00519
d D 5.28 89/01/15 15:23:52 bostic 71 70
c do case insensitive comparison on domain name
e
s 00064/00033/00456
d D 5.27 89/01/15 14:01:50 bostic 70 69
c always log errors, even if EOF read or eventually successful
c log if multiple user names tried; do backoff after 3 attempts made
e
s 00007/00092/00482
d D 5.26 89/01/06 20:15:32 karels 69 68
c remove -r (moved into rlogind)
e
s 00099/00086/00475
d D 5.25 89/01/06 14:00:16 bostic 68 67
c Mike's cleanups; add Berkeley specific copyright, minor rearranging
e
s 00355/00368/00206
d D 5.24 88/12/21 17:57:35 bostic 67 66
c major rework/cleanup; remove any vestige of AT&T code
e
s 00001/00001/00573
d D 5.23 88/09/22 16:57:59 bostic 66 65
c fopen returns pointer, not integer; fix for ANSI C
e
s 00002/00011/00572
d D 5.22 88/09/19 20:15:42 bostic 65 64
c use libutil version of login
e
s 00001/00001/00582
d D 5.21 88/09/17 09:54:50 bostic 64 63
c i unused
e
s 00009/00001/00574
d D 5.20 87/10/01 14:00:41 bostic 63 61
c '-' may not start login name; bug report 4.3BSD/bin/85
e
s 00007/00001/00574
d R 5.20 87/10/01 13:38:36 bostic 62 61
c '-' may not start login name; bug report 4.3BSD/bin/85
e
s 00047/00019/00528
d D 5.19 87/06/27 17:14:17 karels 61 60
c add -f for datakit and others
e
s 00001/00001/00546
d D 5.18 87/06/16 14:03:11 bostic 60 59
c timeout to 5 minutes
e
s 00009/00057/00538
d D 5.17 87/03/11 12:00:22 bostic 59 58
c setenv moved to C library
e
s 00008/00000/00587
d D 5.16 86/11/10 21:48:46 karels 58 57
c shorten hostname if local
e
s 00005/00005/00582
d D 5.15 86/04/12 15:50:48 karels 57 55
c write => tty
e
s 00004/00004/00583
d R 5.15 86/04/12 15:48:36 karels 56 55
c write => tty
e
s 00007/00006/00580
d D 5.14 86/03/13 21:16:02 mckusick 55 54
c if lookup of group "write" fails, use user's /etc/passwd entry as before
e
s 00020/00002/00566
d D 5.13 86/03/13 19:23:05 mckusick 54 53
c setgid to group "write" so that terminals need not be world writable
e
s 00002/00000/00566
d D 5.12 86/03/05 18:07:38 karels 53 52
c if resetting special chars, let's do them all
e
s 00000/00034/00566
d D 5.11 86/01/09 14:54:45 mckusick 52 51
c delete trash for distribution
e
s 00001/00001/00599
d D 5.10 85/11/08 16:49:57 bloom 51 50
c check for null string as well as null pointer
e
s 00022/00005/00578
d D 5.9 85/10/18 15:12:41 mckusick 50 49
c give "from host" information for network login failures
e
s 00003/00002/00580
d D 5.8 85/10/10 17:54:10 bloom 49 47
c ask for login name second time around on rlogin
e
s 00001/00001/00581
d R 5.8 85/09/24 12:03:19 bloom 48 47
c ask for login name after first time around on remote login
e
s 00008/00006/00574
d D 5.7 85/09/19 18:41:52 karels 47 46
c don't clobber term, path if -p (but always set user, home and shell)
e
s 00002/00004/00578
d D 5.6 85/09/17 22:52:29 mckusick 46 45
c overloading of rflag causes trouble for window sizes
e
s 00004/00004/00578
d D 5.5 85/09/17 19:14:25 eric 45 44
c facilities in syslog
e
s 00036/00024/00546
d D 5.4 85/09/17 19:02:27 mckusick 44 43
c do not set window size from rlogin as rlogind promises to handle it;
c missed one file descriptor (from serge);
c passing through window size with speed is isolated as TRASH
e
s 00026/00067/00544
d D 5.3 85/09/12 16:17:40 bloom 43 42
c allow -p and a network arg, use ruserok instead of builtin, break rflag into
c two pieces
e
s 00001/00001/00610
d D 5.2 85/05/24 15:53:48 mckusick 42 41
c ignore ``quotas not compiled in'' error message from quota
e
s 00014/00002/00597
d D 5.1 85/04/30 14:57:06 dist 41 40
c Add copyright
e
s 00001/00001/00598
d D 4.37 85/04/02 08:18:45 karels 40 39
c off by one
e
s 00131/00036/00468
d D 4.36 85/04/01 21:25:00 sam 39 38
c allow getty to propagate environment; setup window sizes both locally 
c and for remote logins; hack -h flag to allow telnetd to set window sizes 
c instead of login; miscellaneous cleanups; NOTE change to rlogin protocol 
c encourages passing window size from remote machine
e
s 00006/00008/00498
d D 4.35 85/01/08 20:23:07 serge 38 36
c specify if mail in the mbox is new
e
s 00001/00000/00506
d R 4.35 84/12/17 13:30:04 ralph 37 36
c set umask here until switchover (get it from init).
e
s 00046/00089/00460
d D 4.34 84/05/07 11:42:51 root 36 35
c uses new getttyent(3) routines.
e
s 00004/00002/00545
d D 4.33 83/09/02 14:07:23 edward 35 32
c in getloginname, use lusername to getpw so it can be null terminated.
e
s 00007/00005/00542
d R 4.33 83/09/02 13:42:37 edward 34 32
c use lusername[] as buffer in getloginname()
c so we can null terminate it for getpwnam.
e
s 00002/00043/00504
d R 4.33 83/07/06 00:32:39 sam 33 32
c no more ttytype
e
s 00004/00003/00543
d D 4.32 83/06/30 14:36:40 sam 32 31
c fix logerr
e
s 00007/00004/00539
d D 4.31 83/06/30 12:58:39 sam 31 30
c pwd was undefined when user was unknown for remote login
e
s 00010/00008/00533
d D 4.30 83/06/13 02:43:44 sam 30 29
c way back yonder...
e
s 00001/00001/00540
d D 4.29 83/06/10 23:13:51 sam 29 28
c needs NMOUNT for quotas
e
s 00000/00001/00541
d D 4.28 83/05/28 16:29:15 sam 28 27
c no more need for #define ne QUOTA
e
s 00002/00003/00540
d D 4.27 83/05/24 16:03:06 sam 27 26
c no more hostname stuff
e
s 00008/00000/00535
d D 4.26 83/05/23 01:02:37 sam 26 25
c logging on define LOGERR now
e
s 00223/00156/00312
d D 4.25 83/05/23 00:04:36 sam 25 24
c major changes; make mainline login loop understandable; factor 
c out remote login protocol into separate routines; replace nice calls with 
c setpriority calls; add -h option so telnetd and friends can supply host name 
c for stuffing into the utmp file
e
s 00021/00001/00447
d D 4.24 83/05/22 19:23:42 sam 24 23
c stuff for quotas
e
s 00004/00009/00444
d D 4.23 83/05/19 02:21:53 leres 23 22
c /etc/securetty is checked, even when root logins across the net.
e
s 00001/00004/00452
d D 4.22 83/04/18 23:31:31 leres 22 21
c Removed "No such user" message to prevent probing from remote machines.
e
s 00036/00016/00420
d D 4.21 83/03/31 14:01:50 leres 21 20
c Tightened security in login. The .rhosts file must now be owned
c by either the user or root and may not be a symbolic link.
e
s 00011/00024/00425
d D 4.20 82/12/21 15:44:33 sam 20 19
c use new ioctl's; fix tty mode typo; handle > 8 remote login names
e
s 00001/00001/00448
d D 4.19 82/11/14 16:32:41 sam 19 18
c convert to 4.1c sys calls and directory layout
e
s 00001/00000/00448
d D 4.18 82/06/27 10:27:10 root 18 17
c chmod the tty to repair previous biff/mesg
e
s 00004/00001/00444
d D 4.17 82/05/19 22:09:26 mckusick 17 16
c fix group initialization for eight character login names
e
s 00006/00006/00439
d D 4.16 82/04/03 19:32:42 wnj 16 15
c root only from /.rhosts
e
s 00039/00056/00406
d D 4.15 82/03/27 22:16:33 wnj 15 14
c many changes relating to remote login; but fix with updating lastlog
e
s 00094/00053/00368
d D 4.14 82/03/15 04:04:39 root 14 13
c machine independent
e
s 00003/00003/00418
d D 4.13 82/02/28 23:45:47 wnj 13 12
c groups stuff
e
s 00071/00015/00350
d D 4.12 82/02/28 21:26:31 wnj 12 11
c add login -r
e
s 00001/00000/00364
d D 4.11 81/07/05 21:48:25 root 11 10
c ignore SIGTSTP before exec() so /bin/sh's wont die on ^Z under ttynew
e
s 00181/00094/00183
d D 4.10 81/02/28 22:58:37 wnj 10 9
c new shutdown style
e
s 00007/00001/00270
d D 4.9 81/01/11 15:35:18 wnj 9 8
c umask defaults to 2 for csr group members
e
s 00003/00003/00268
d D 4.8 81/01/10 17:09:59 root 8 7
c I changed the directory you log into if your own directory is not there to
c the root directory -- presotto
e
s 00004/00000/00267
d D 4.7 80/12/10 20:01:30 bill 7 6
c If login directory not available, log in with pwd->pw_dir=="/tmp"
e
s 00003/00000/00264
d D 4.6 80/11/11 10:10:08 bill 6 5
c #ifdef ERNIE around root login restrictions
e
s 00002/00002/00262
d D 4.5 80/10/22 10:23:17 mark 5 4
c fixed non-vax bug where lseek was being passed an int for lastlog.
e
s 00009/00001/00255
d D 4.4 80/10/19 10:45:53 bill 4 3
c restore lost code
e
s 00001/00002/00255
d D 4.3 80/10/19 02:05:01 bill 3 2
c remove local chars
e
s 00021/00010/00236
d D 4.2 80/10/10 00:50:08 bill 2 1
c reset all chars; line discipline=NTTY for csh users
e
s 00246/00000/00000
d D 4.1 80/10/01 17:27:21 bill 1 0
c date and time created 80/10/01 17:27:21 by bill
e
u
U
f b 
t
T
I 41
D 102
/*
E 102
I 102
/*-
E 102
D 61
 * Copyright (c) 1980 Regents of the University of California.
E 61
I 61
D 67
 * Copyright (c) 1980,1987 Regents of the University of California.
E 67
I 67
D 68
 * Copyright (c) 1980, 1987 Regents of the University of California.
E 67
E 61
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 68
I 68
D 114
 * Copyright (c) 1980, 1987, 1988 The Regents of the University of California.
 * All rights reserved.
E 114
I 114
D 128
 * Copyright (c) 1980, 1987, 1988, 1991 The Regents of the University
 * of California.  All rights reserved.
E 128
I 128
D 129
 * Copyright (c) 1980, 1987, 1988, 1991, 1993
E 129
I 129
 * Copyright (c) 1980, 1987, 1988, 1991, 1993, 1994
E 129
 *	The Regents of the University of California.  All rights reserved.
E 128
E 114
 *
D 102
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
E 102
I 102
 * %sccs.include.redist.c%
E 102
E 68
 */

E 41
I 24
#ifndef lint
E 24
I 1
D 2
static char *sccsid = "%W% (Berkeley) %G%";
E 2
I 2
D 10
static	char *sccsid = "%W% (Berkeley) %G%";
E 10
I 10
D 12
static	char *sccsid = "%W% (Berkeley) %E%";
E 12
I 12
D 14
static	char *sccsid = "%W% (Berkeley) %I%";
E 14
I 14
D 25
static	char *sccsid = "%W% %E%";
E 25
I 25
D 41
static	char *sccsid = "%W% (Berkeley) %E%";
E 25
I 24
#endif
E 41
I 41
D 128
char copyright[] =
D 68
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 68
I 68
D 73
"%Z% Copyright (c) 1980, 1987, 1988 The Regents of the University of California.\n\
E 73
I 73
D 102
"@(#) Copyright (c) 1980, 1987, 1988 The Regents of the University of California.\n\
E 102
I 102
D 114
"%Z% Copyright (c) 1980, 1987, 1988 The Regents of the University of California.\n\
E 114
I 114
"%Z% Copyright (c) 1980, 1987, 1988, 1991 The Regents of the University of California.\n\
E 114
E 102
E 73
E 68
 All rights reserved.\n";
E 128
I 128
static char copyright[] =
D 129
"%Z% Copyright (c) 1980, 1987, 1988, 1991, 1993\n\
E 129
I 129
"%Z% Copyright (c) 1980, 1987, 1988, 1991, 1993, 1994\n\
E 129
	The Regents of the University of California.  All rights reserved.\n";
E 128
D 68
#endif not lint
E 68
I 68
#endif /* not lint */
E 68

#ifndef lint
D 73
static char sccsid[] = "%W% (Berkeley) %G%";
E 73
I 73
D 75
static char sccsid[] = "@(#)login.c	5.29 (Berkeley) 1/20/89";
E 75
I 75
static char sccsid[] = "%W% (Berkeley) %G%";
E 75
E 73
D 68
#endif not lint
E 68
I 68
#endif /* not lint */
E 68
E 41

E 24
E 14
E 12
E 10
E 2
/*
 * login [ name ]
I 83
 * login -r hostname	(for rlogind)
E 83
I 12
D 25
 * login -r
E 25
I 25
D 61
 * login -r hostname (for rlogind)
 * login -h hostname (for telnetd, etc.)
E 61
I 61
D 69
 * login -r hostname	(for rlogind)
E 69
 * login -h hostname	(for telnetd, etc.)
 * login -f name	(for pre-authenticated login: datakit, xterm, etc.)
E 61
E 25
I 14
D 15
 * login -r [ rhost ]
E 15
E 14
E 12
 */

D 29
#include <sys/types.h>
E 29
I 29
#include <sys/param.h>
E 29
I 25
D 28
#define	QUOTA
E 28
D 86
#include <sys/quota.h>
E 86
I 86
D 98
#include <ufs/quota.h>
E 98
E 86
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>
I 36
#include <sys/file.h>
I 67
D 68
#include <sys/termios.h>
E 68
D 94
#include <sys/ioctl.h>
E 94
I 94
D 112
#include <sgtty.h>
E 112
E 94
E 67
E 36

E 25
D 67
#include <sgtty.h>
E 67
D 125
#include <utmp.h>
E 125
D 130
#include <signal.h>
D 67
#include <pwd.h>
#include <stdio.h>
E 67
D 25
#include <sys/stat.h>
E 25
D 86
#include <lastlog.h>
E 86
I 24
D 25
#define	QUOTA
#include <sys/quota.h>
E 25
D 125
#include <errno.h>
E 125
I 36
#include <ttyent.h>
#include <syslog.h>
I 125
#include <setjmp.h>
#include <tzfile.h>
#include <utmp.h>
E 130
I 130
#include <err.h>
E 130
#include <errno.h>
E 125
I 54
#include <grp.h>
I 67
#include <pwd.h>
I 68
D 125
#include <setjmp.h>
E 125
I 125
D 130
#include <unistd.h>
E 130
I 130
#include <setjmp.h>
#include <signal.h>
E 130
E 125
E 68
#include <stdio.h>
I 125
#include <stdlib.h>
E 125
D 100
#include <strings.h>
E 100
I 100
#include <string.h>
I 130
#include <syslog.h>
#include <ttyent.h>
#include <tzfile.h>
#include <unistd.h>
#include <utmp.h>

E 130
E 100
I 84
D 125
#include <tzfile.h>
E 125
E 84
I 80
#include "pathnames.h"
E 80
E 67
E 54
E 36
E 24
I 6
D 14
#include <whoami.h>
E 6
D 10
#define SCPYN(a, b)	strncpy(a, b, sizeof(a))
E 10
I 10
#ifdef	UNAME
#include <sys/utsname.h>
#endif
E 14
E 10

I 125
void	 badlogin __P((char *));
void	 checknologin __P((void));
void	 dolastlog __P((int));
void	 getloginname __P((void));
void	 motd __P((void));
int	 rootterm __P((char *));
void	 sigint __P((int));
void	 sleepexit __P((int));
char	*stypeof __P((char *));
void	 timedout __P((int));
I 126
#ifdef KERBEROS
int	 klogin __P((struct passwd *, char *, char *, char *));
#endif
E 126

I 130
extern void login __P((struct utmp *));

E 130
E 125
I 73
D 76
D 102
#ifdef	KERBEROS
I 99
#include <kerberosIV/des.h>
E 99
D 90
#include <kerberos/krb.h>
#include <sys/termios.h>
E 90
I 90
D 97
#include <krb.h>
E 97
I 97
#include <kerberosIV/krb.h>
E 97
D 94
#include <sgtty.h>
E 94
E 90
D 77
char	inst[INST_SZ];
E 77
D 87
char	realm[REALM_SZ];
int	kerror = KSUCCESS, notickets = 1;
E 87
I 87
#include <netdb.h>
char		realm[REALM_SZ];
int		kerror = KSUCCESS, notickets = 1;
KTEXT_ST	ticket;
AUTH_DAT	authdata;
char		savehost[MAXHOSTNAMELEN];
I 90
char		tkfile[MAXPATHLEN];
E 90
unsigned long	faddr;
struct	hostent	*hp;
#define	PRINCIPAL_NAME	pwd->pw_name
#define	PRINCIPAL_INST	""
#define	INITIAL_TICKET	"krbtgt"
#define	VERIFY_SERVICE	"rcmd"
E 87
D 77
#define	LIFE		96	/* ticket lifetime in 5-min units */
E 77
#endif

E 102
E 76
E 73
I 54
D 55
#define WRITENAME       "write"         /* name of group to own ttys */
#define WRITEGID        write_gid()     /* gid that owns all ttys */
E 55
I 55
D 57
#define WRITENAME	"write"		/* name of group to own ttys */
#define WRITEGID(gid)	write_gid(gid)	/* gid that owns all ttys */
E 57
I 57
D 67
#define TTYGRPNAME	"tty"		/* name of group to own ttys */
#define TTYGID(gid)	tty_gid(gid)	/* gid that owns all ttys */
E 67
I 67
#define	TTYGRPNAME	"tty"		/* name of group to own ttys */
E 67
E 57
E 55

E 54
I 36
D 67
#define	SCMPN(a, b)	strncmp(a, b, sizeof(a))
E 36
I 10
#define	SCPYN(a, b)	strncpy(a, b, sizeof(a))
E 67
I 67
D 80
#define	MOTDFILE	"/etc/motd"
#define	MAILDIR		"/usr/spool/mail"
#define	NOLOGIN		"/etc/nologin"
#define	HUSHLOGIN	".hushlogin"
#define	LASTLOG		"/usr/adm/lastlog"
#define	BSHELL		"/bin/sh"
E 67

E 80
E 10
D 14
#define NMAX sizeof(utmp.ut_name)
#define LMAX sizeof(utmp.ut_line)
E 14
I 14
D 67
#define NMAX	sizeof(utmp.ut_name)
I 50
#define HMAX	sizeof(utmp.ut_host)
E 50
D 25
#define LMAX	sizeof(utmp.ut_line)
E 25
E 14

D 10
char	user[20];
E 10
I 10
#define	FALSE	0
#define	TRUE	-1

char	nolog[] =	"/etc/nologin";
char	qlog[]  =	".hushlogin";
D 36
char	securetty[] =	"/etc/securetty";
E 36
E 10
char	maildir[30] =	"/usr/spool/mail/";
char	lastlog[] =	"/usr/adm/lastlog";
D 20
struct	passwd nouser = {"", "nope"};
E 20
I 20
struct	passwd nouser = {"", "nope", -1, -1, -1, "", "", "", "" };
E 20
struct	sgttyb ttyb;
struct	utmp utmp;
char	minusnam[16] = "-";
I 39
D 59
char	*envinit[] = { 0 };		/* now set by setenv calls */
E 59
I 59
char	*envinit[1];			/* now set by setenv calls */
E 67
E 59
E 39
I 25
/*
D 67
 * This bounds the time given to login.  We initialize it here
 * so it can be patched on machines where it's too small.
E 67
I 67
 * This bounds the time given to login.  Not a define so it can
 * be patched on machines where it's too small.
E 67
 */
D 60
int	timeout = 60;
E 60
I 60
D 130
int	timeout = 300;
E 130
I 130
u_int	timeout = 300;
E 130
I 118
D 125
int	rootlogin;
E 125
I 125

E 125
E 118
I 102
#ifdef KERBEROS
int	notickets = 1;
I 115
D 118
int	rootlogin = 0;
#define	ROOTLOGIN	(rootlogin || (pwd && pwd->pw_uid == 0))
#else
#define	ROOTLOGIN	(pwd && pwd->pw_uid == 0)
E 118
I 118
char	*instance;
char	*krbtkfile_env;
int	authok;
E 118
E 115
#endif
E 102
E 60
E 25
I 12

E 12
D 39
char	homedir[64] = "HOME=";
char	shell[64] = "SHELL=";
char	term[64] = "TERM=";
D 10
char	*envinit[] = {homedir, shell, "PATH=:/usr/ucb:/bin:/usr/bin", term, user,0};
E 10
I 10
char	user[20] = "USER=";
E 39
I 39
D 67
char	term[64];
E 67
I 67
D 68
struct passwd nouser = {"", "NOLOGIN", -1, -1, -1, "", "", "", "" };
struct sgttyb ttyb;
E 68
D 74
struct passwd *pwd;
D 70
char term[64], *hostname, *username;
E 70
I 70
int repeatcnt;
char term[64], *hostname, *username, *tty;
E 74
I 74
struct	passwd *pwd;
int	failures;
D 96
char	term[64], *hostname, *username, *tty;
E 96
I 96
char	term[64], *envinit[1], *hostname, *username, *tty;
E 96
E 74
E 70
E 67
E 39
D 12
char	*envinit[] = {homedir, shell, "PATH=:/usr/ucb:/bin:/usr/bin", term, user, 0};
E 10
struct	passwd *pwd;
E 12
I 12
D 25
char	*speeds[] =
    { "0", "50", "75", "110", "134", "150", "200", "300",
      "600", "1200", "1800", "2400", "4800", "9600", "19200", "38400" };
#define	NSPEEDS	(sizeof (speeds) / sizeof (speeds[0]))
E 25
E 12

I 125
int
E 125
I 68
D 74
struct sgttyb sgttyb;
E 68
I 12
D 39
char	*envinit[] =
D 25
    {homedir, shell, "PATH=:/usr/ucb:/bin:/usr/bin", term, user, 0};
E 25
I 25
    { homedir, shell, "PATH=:/usr/ucb:/bin:/usr/bin", term, user, 0 };
E 25

E 39
D 67
struct	passwd *pwd;
E 12
D 36
struct	passwd *getpwnam();
E 36
D 12
char	*strcat();
E 12
I 12
D 39
char	*strcat(), *rindex(), *index();
E 39
I 39
D 59
char	*strcat(), *rindex(), *index(), *malloc(), *realloc();
E 59
I 59
char	*strcat(), *rindex(), *index();
E 59
E 39
E 12
D 36
int	setpwent();
E 36
I 25
int	timedout();
E 25
char	*ttyname();
char	*crypt();
char	*getpass();
D 23
char	*rindex();
E 23
char	*stypeof();
D 59
extern	char **environ;
E 59
I 24
extern	int errno;
E 24

I 2
D 20
#define	CTRL(c)	('c'&037)
#define	CERASE	'#'
#define	CEOT	CTRL(d)
#define	CKILL	'@'
#define	CQUIT	034		/* FS, cntl shift L */
#define	CINTR	0177		/* DEL */
#define	CSTOP	CTRL(s)
#define	CSTART	CTRL(q)
#define	CBRK	0377
struct	tchars tc = {
	CINTR, CQUIT, CSTART, CSTOP, CEOT, CBRK
E 20
I 20
D 30
struct	ttychars tc = {
	CERASE,	CKILL,	CINTR,	CQUIT,	CSTART,
	CSTOP,	CEOF,	CBRK,	CSUSP,	CDSUSP,
	CRPRNT,	CFLUSH,	CWERASE,CLNEXT
E 30
I 30
struct	tchars tc = {
E 67
I 67
struct tchars tc = {
E 74
I 74
D 108
struct	sgttyb sgttyb;
struct	tchars tc = {
E 74
E 67
	CINTR, CQUIT, CSTART, CSTOP, CEOT, CBRK
E 30
E 20
};
I 30
D 67
struct	ltchars ltc = {
E 67
I 67
D 74
struct ltchars ltc = {
E 74
I 74
struct	ltchars ltc = {
E 74
E 67
D 102
	CSUSP, CDSUSP, CRPRNT, CFLUSH, CWERASE, CLNEXT
E 102
I 102
	CSUSP, CDSUSP, CRPRNT, CDISCARD, CWERASE, CLNEXT
E 102
};
E 30
I 10
D 14
#ifdef	TIOCLSET
E 14
E 10
D 20
struct	ltchars ltc = {
D 3
	CTRL(z), CTRL(y), CTRL(r), CTRL(o), CTRL(w), CTRL(v), CTRL(h), CTRL(u),
	CTRL(c)
E 3
I 3
	CTRL(z), CTRL(y), CTRL(r), CTRL(o), CTRL(w), CTRL(v)
E 3
};
E 20
I 10
D 14
#endif
E 14
E 10

E 108
I 79
char *months[] =
	{ "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug",
	  "Sep", "Oct", "Nov", "Dec" };

E 79
I 78
D 104
char *months[] =
	{ "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug",
	  "Sep", "Oct", "Nov", "Dec" };

E 104
E 78
I 39
D 67
struct winsize win = { 0, 0, 0, 0 };

E 39
I 12
int	rflag;
I 43
int	usererr = -1;
E 43
D 14
char	rusername[NMAX+1];
E 14
I 14
char	rusername[NMAX+1], lusername[NMAX+1];
E 14
char	rpassword[NMAX+1];
I 17
char	name[NMAX+1];
I 58
char	me[MAXHOSTNAMELEN];
E 58
E 17
I 14
char	*rhost;
E 14

E 67
E 12
E 2
main(argc, argv)
D 25
char **argv;
E 25
I 25
D 67
	char *argv[];
E 67
I 67
	int argc;
D 125
	char **argv;
E 125
I 125
	char *argv[];
E 125
E 67
E 25
{
I 59
D 67
	extern	char **environ;
E 59
	register char *namep;
D 25
	int t, f, c;
I 10
	int invalid;
	int quietlog;
	int i;
E 25
I 25
D 36
	int t, f, c, i;
E 36
I 36
D 39
	int t, f, c;
E 39
I 39
D 61
	int pflag = 0, hflag = 0, t, f, c;
E 61
I 61
	int pflag = 0, hflag = 0, fflag = 0, t, f, c;
E 61
E 39
E 36
	int invalid, quietlog;
E 25
	FILE *nlfd;
E 10
D 36
	char *ttyn;
E 36
I 36
	char *ttyn, *tty;
E 36
D 10
	int ldisc = 0;
E 10
I 10
D 12
	int	ldisc = 0;
E 12
I 12
D 13
	int ldisc = 0;
	int zero = 0;
E 13
I 13
D 14
	int	ldisc = 0;
E 13
E 12
#ifdef	UNAME
	struct utsname uts;
#endif
E 14
I 14
D 39
	int ldisc = 0, zero = 0;
E 39
I 39
D 64
	int ldisc = 0, zero = 0, i;
E 64
I 64
	int ldisc = 0, zero = 0;
E 64
D 59
	char **envnew;
E 59
I 58
	char *p, *domain, *index();
E 67
I 67
D 102
	extern int errno, optind;
E 102
I 102
D 125
	extern int optind;
E 102
	extern char *optarg, **environ;
I 79
	struct timeval tp;
	struct tm *ttp;
E 79
I 78
	struct timeval tp;
D 104
	struct tm *ttp;
E 104
E 78
	struct group *gr;
E 125
I 125
	extern char **environ;
E 125
D 130
	register int ch;
D 73
	register char *p;
E 73
I 73
D 74
	register char *p, *pp;
E 74
I 74
	register char *p;
E 130
E 74
E 73
D 69
	int fflag, hflag, pflag, rflag, cnt;
E 69
I 69
D 70
	int fflag, hflag, pflag, cnt;
E 70
I 70
D 83
D 94
	int ask, fflag, hflag, pflag, cnt;
E 94
I 94
D 125
	int ask, fflag, hflag, pflag, cnt, uid;
E 94
E 83
I 83
	int ask, fflag, hflag, pflag, rflag, cnt;
E 83
E 70
E 69
D 102
	int quietlog, passwd_req, ioctlval, timedout();
D 68
	char *domain, *envinit[1], *ttyn, *tty;
E 68
I 68
D 70
	char *domain, *salt, *envinit[1], *ttyn, *tty;
E 70
I 70
D 74
	char *domain, *salt, *envinit[1], *ttyn;
E 74
I 74
D 96
	char *domain, *salt, *envinit[1], *ttyn, *pp;
E 96
I 96
	char *domain, *salt, *ttyn, *pp;
E 102
I 102
D 106
	int quietlog, passwd_req, ioctlval, rval;
E 106
I 106
D 108
	int quietlog, ioctlval, rval;
E 108
I 108
	int quietlog, rval;
E 125
I 125
	struct group *gr;
	struct stat st;
	struct timeval tp;
	struct utmp utmp;
D 130
	int ask, cnt, fflag, hflag, pflag, quietlog, rootlogin, rval, uid;
E 125
E 108
E 106
	char *domain, *salt, *ttyn;
E 130
I 130
	int ask, ch, cnt, fflag, hflag, pflag, quietlog, rootlogin, rval;
	uid_t uid;
	char *domain, *p, *salt, *ttyn;
E 130
E 102
E 96
E 74
E 70
E 68
D 86
	char tbuf[MAXPATHLEN + 2];
E 86
I 86
	char tbuf[MAXPATHLEN + 2], tname[sizeof(_PATH_TTY) + 10];
I 87
	char localhost[MAXHOSTNAMELEN];
E 87
E 86
D 78
D 79
	char *ttyname(), *stypeof(), *crypt(), *getpass();
E 79
I 79
	char *ctime(), *ttyname(), *stypeof(), *crypt(), *getpass();
E 79
E 78
I 78
D 125
	char *ctime(), *ttyname(), *stypeof(), *crypt(), *getpass();
E 78
	time_t time();
	off_t lseek();
I 102
	void timedout();
E 125
E 102
E 67
E 58
E 39
D 25
	FILE *hostf; int first = 1;
E 25
E 14
E 10

D 25
	alarm(60);
E 25
I 25
D 67
	signal(SIGALRM, timedout);
	alarm(timeout);
E 25
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
D 25
	nice(-100);
	nice(20);
	nice(0);
E 25
I 25
	setpriority(PRIO_PROCESS, 0, 0);
E 25
I 24
	quota(Q_SETUID, 0, 0, 0);
E 67
I 67
	(void)signal(SIGALRM, timedout);
D 130
	(void)alarm((u_int)timeout);
E 130
I 130
	(void)alarm(timeout);
E 130
	(void)signal(SIGQUIT, SIG_IGN);
	(void)signal(SIGINT, SIG_IGN);
	(void)setpriority(PRIO_PROCESS, 0, 0);
D 98
	(void)quota(Q_SETUID, 0, 0, 0);
E 98

I 101
	openlog("login", LOG_ODELAY, LOG_AUTH);

E 101
E 67
E 24
I 12
D 15
	if (argc > 0 && !strcmp(argv[1], "-r")) {
E 15
I 15
D 25
	if (argc > 1 && !strcmp(argv[1], "-r")) {
E 15
		rflag++;
D 14
		getstr(rusername, sizeof (rusername), "Username");
		getstr(rpassword, sizeof (rpassword), "Password");
E 14
I 14
D 15
		if (argc > 1)
			rhost = argv[2];
E 15
I 15
		rhost = argv[2];
E 15
		argc = 1;
D 15
		if (rhost) {
			getstr(rusername, sizeof (rusername), "remuser");
			getstr(lusername, sizeof (lusername), "locuser");
		} else {
			getstr(lusername, sizeof (lusername), "Username");
			getstr(rpassword, sizeof (rpassword), "Password");
		}
E 15
I 15
		getstr(rusername, sizeof (rusername), "remuser");
		getstr(lusername, sizeof (lusername), "locuser");
E 15
E 14
		getstr(term+5, sizeof(term)-5, "Terminal type");
I 14
D 15
		if (rhost == 0)
			goto normal;
		if (getuid()) {
			rflag = 0;
			goto normal;
		}
E 15
I 15
		if (getuid())
			goto abnormal;
E 15
		setpwent();
		pwd = getpwnam(lusername);
I 15
		endpwent();
E 15
D 22
		if (pwd == NULL) {
D 15
			fprintf(stderr, "Login incorrect.\n");
			exit(1);
E 15
I 15
			if (strcmp(rusername, lusername))
				printf("%s: No such user\r\n", lusername);
E 22
I 22
		if (pwd == NULL)
E 22
			goto abnormal;
E 15
D 22
		}
E 22
D 15
		endpwent();
E 15
D 16
		hostf = fopen("/etc/hosts.equiv", "r");
E 16
I 16
		hostf = pwd->pw_uid ? fopen("/etc/hosts.equiv", "r") : 0;
E 16
	again:
		if (hostf) {
D 21
		  char ahost[32];
		  while (fgets(ahost, sizeof (ahost), hostf)) {
			char *user;
			if (index(ahost, '\n'))
				*index(ahost, '\n') = 0;
			user = index(ahost, ' ');
			if (user)
				*user++ = 0;
			if (!strcmp(rhost, ahost) &&
D 15
			    !strcmp(rusername, user ? user : lusername))
E 15
I 15
			    !strcmp(rusername, user ? user : lusername)) {
				fclose(hostf);
E 15
				goto normal;
E 21
I 21
			char ahost[32];

		        while (fgets(ahost, sizeof (ahost), hostf)) {
				char *user;

D 23
				if (index(ahost, '\n'))
					*index(ahost, '\n') = 0;
				user = index(ahost, ' ');
				if (user)
					*user++ = 0;
E 23
I 23
				if ((user = index(ahost, '\n')) != 0)
					*user++ = '\0';
				if ((user = index(ahost, ' ')) != 0)
					*user++ = '\0';
E 23
				if (!strcmp(rhost, ahost) &&
				    !strcmp(rusername, user ?
				    user : lusername)) {
					fclose(hostf);
					goto normal;
				}
E 21
I 15
			}
E 15
D 21
		  }
		  fclose(hostf);
E 21
I 21
			fclose(hostf);
E 25
I 25
	/*
I 39
	 * -p is used by getty to tell login not to destroy the environment
I 83
	 * -r is used by rlogind to cause the autologin protocol;
E 83
E 39
D 69
	 * -r is used by rlogind to cause the autologin protocol;
E 69
I 61
D 126
 	 * -f is used to skip a second login authentication 
E 126
I 126
	 * -f is used to skip a second login authentication
E 126
E 61
D 69
	 * -h is used by other servers to pass the name of the
	 * remote host to login so that it may be placed in utmp and wtmp
E 69
I 69
	 * -h is used by other servers to pass the name of the remote
	 *    host to login so that it may be placed in utmp and wtmp
E 69
	 */
I 58
D 67
	(void) gethostname(me, sizeof(me));
	domain = index(me, '.');
E 58
D 43
	if (argc > 1) {
E 43
I 43
	while (argc > 1) {
E 43
		if (strcmp(argv[1], "-r") == 0) {
D 43
			rflag = doremotelogin(argv[2]);
E 43
I 43
D 61
			if (rflag || hflag) {
				printf("Only one of -r and -h allowed\n");
E 61
I 61
			if (rflag || hflag || fflag) {
				printf("Other options not allowed with -r\n");
E 67
I 67
D 87
	(void)gethostname(tbuf, sizeof(tbuf));
	domain = index(tbuf, '.');
E 87
I 87
	domain = NULL;
	if (gethostname(localhost, sizeof(localhost)) < 0)
		syslog(LOG_ERR, "couldn't get local hostname: %m");
	else
D 130
		domain = index(localhost, '.');
E 130
I 130
		domain = strchr(localhost, '.');
E 130
E 87
D 101

I 94
	openlog("login", LOG_ODELAY, LOG_AUTH);
E 101

E 94
D 69
	fflag = hflag = pflag = rflag = 0;
E 69
I 69
D 83
	fflag = hflag = pflag = 0;
E 83
I 83
	fflag = hflag = pflag = rflag = 0;
E 83
E 69
D 106
	passwd_req = 1;
E 106
I 94
	uid = getuid();
E 94
D 68
	while ((ch = getopt(argc, argv, "f:h:pr:")) != EOF)
		switch(ch) {
E 68
I 68
D 69
	while ((ch = getopt(argc, argv, "fh:pr:")) != EOF)
E 69
I 69
D 83
	while ((ch = getopt(argc, argv, "fh:p")) != EOF)
E 83
I 83
	while ((ch = getopt(argc, argv, "fh:pr:")) != EOF)
E 83
E 69
		switch (ch) {
E 68
		case 'f':
I 83
			if (rflag) {
				fprintf(stderr,
				    "login: only one of -r and -f allowed.\n");
				exit(1);
			}
E 83
D 69
			if (rflag) {
				fprintf(stderr,
				    "login: only one of -r and -f allowed.\n");
E 67
E 61
				exit(1);
			}
E 69
I 63
D 67
			if (argv[2] == 0)
E 67
I 67
			fflag = 1;
D 68
			username = optarg;
E 68
			break;
		case 'h':
D 94
			if (getuid()) {
E 94
I 94
D 130
			if (uid) {
E 94
D 84
				fprintf(stderr,
E 84
I 84
				(void)fprintf(stderr,
E 84
D 119
				    "login: -h for super-user only.\n");
E 119
I 119
				    "login: -h option: %s\n", strerror(EPERM));
E 119
E 67
				exit(1);
E 63
D 67
			rflag = 1;
			usererr = doremotelogin(argv[2]);
I 58
			if ((p = index(argv[2], '.')) && strcmp(p, domain) == 0)
				*p = 0;
E 58
E 43
			SCPYN(utmp.ut_host, argv[2]);
D 43
			argc = 0;
E 43
I 43
			argc -= 2;
			argv += 2;
			continue;
E 43
E 25
E 21
		}
D 25
		if (first == 1) {
I 21
			char *rhosts = ".rhosts";
			struct stat sbuf;

E 21
			first = 0;
			if (chdir(pwd->pw_dir) < 0)
				goto again;
D 21
			hostf = fopen(".rhosts", "r");
			goto again;
E 21
I 21
			if (lstat(rhosts, &sbuf) < 0)
				goto again;
			if ((sbuf.st_mode & S_IFMT) == S_IFLNK) {
				printf("login: .rhosts is a soft link.\r\n");
D 23
			        fclose(hostf);
E 23
				goto abnormal;
			}
			hostf = fopen(rhosts, "r");
			fstat(fileno(hostf), &sbuf);
			if ((int) sbuf.st_uid != pwd->pw_uid &&
			    (int) sbuf.st_uid != 0) {
				printf("login: Bad .rhosts ownership.\r\n");
			        fclose(hostf);
				goto abnormal;
			}
		goto again;
E 25
I 25
D 61
		if (strcmp(argv[1], "-h") == 0 && getuid() == 0) {
I 43
			if (rflag || hflag) {
				printf("Only one of -r and -h allowed\n");
E 61
I 61
		if (strcmp(argv[1], "-h") == 0) {
			if (getuid() == 0) {
				if (rflag || hflag) {
				    printf("Only one of -r and -h allowed\n");
				    exit(1);
				}
				hflag = 1;
				if ((p = index(argv[2], '.')) &&
				    strcmp(p, domain) == 0)
					*p = 0;
				SCPYN(utmp.ut_host, argv[2]);
E 67
			}
E 130
I 130
			if (uid)
				errx(1, "-h option: %s", strerror(EPERM));
E 130
I 83
			if (rflag) {
				fprintf(stderr,
				    "login: only one of -r and -h allowed.\n");
				exit(1);
			}
E 83
D 67
			argc -= 2;
			argv += 2;
			continue;
		}
		if (strcmp(argv[1], "-f") == 0 && argc > 2) {
E 67
D 69
			if (rflag) {
D 67
				printf("Only one of -r and -f allowed\n");
E 67
I 67
				fprintf(stderr,
				    "login: only one of -r and -h allowed.\n");
E 67
E 61
				exit(1);
			}
E 69
E 43
I 39
D 61
			hflag = 1;
I 58
			if ((p = index(argv[2], '.')) && strcmp(p, domain) == 0)
				*p = 0;
E 58
E 39
			SCPYN(utmp.ut_host, argv[2]);
E 61
I 61
D 67
			fflag = 1;
			SCPYN(utmp.ut_name, argv[2]);
E 61
D 43
			argc = 0;
E 43
I 43
			argc -= 2;
			argv += 2;
			continue;
E 43
E 25
E 21
		}
I 39
		if (strcmp(argv[1], "-p") == 0) {
			argc--;
			argv++;
E 67
I 67
			hflag = 1;
D 130
			if (domain && (p = index(optarg, '.')) &&
E 130
I 130
			if (domain && (p = strchr(optarg, '.')) &&
E 130
D 71
			    strcmp(p, domain) == 0)
E 71
I 71
			    strcasecmp(p, domain) == 0)
E 71
				*p = 0;
			hostname = optarg;
			break;
		case 'p':
E 67
			pflag = 1;
I 43
D 67
			continue;
E 67
I 67
			break;
I 83
		case 'r':
			if (hflag || fflag) {
				fprintf(stderr,
				    "login: -f and -h not allowed with -r.\n");
				exit(1);
			}
			if (getuid()) {
				fprintf(stderr,
				    "login: -r for super-user only.\n");
				exit(1);
			}
			/* "-r hostname" must be last args */
			if (optind != argc) {
				fprintf(stderr, "Syntax error.\n");
				exit(1);
			}
			rflag = 1;
			passwd_req = (doremotelogin(optarg) == -1);
			if (domain && (p = index(optarg, '.')) &&
			    !strcmp(p, domain))
				*p = '\0';
			hostname = optarg;
			break;
E 83
D 69
		case 'r':
			if (hflag || fflag) {
				fprintf(stderr,
				    "login: -f and -h not allowed with -r.\n");
				exit(1);
			}
I 68
			if (getuid()) {
				fprintf(stderr,
				    "login: -r for super-user only.\n");
				exit(1);
			}
			/* "-r hostname" must be last args */
			if (optind != argc) {
				fprintf(stderr, "Syntax error.\n");
				exit(1);
			}
E 68
			rflag = 1;
D 68
			passwd_req = doremotelogin(optarg);
E 68
I 68
			passwd_req = (doremotelogin(optarg) == -1);
E 68
			if (domain && (p = index(optarg, '.')) &&
			    !strcmp(p, domain))
				*p = '\0';
			hostname = optarg;
			break;
E 69
		case '?':
		default:
I 90
D 94
			syslog(LOG_ERR, "invalid flag");
E 94
I 94
			if (!uid)
				syslog(LOG_ERR, "invalid flag %c", ch);
E 94
E 90
D 68
			fprintf(stderr, "usage: login [-p] [username]\n");
E 68
I 68
D 84
			fprintf(stderr, "usage: login [-fp] [username]\n");
E 84
I 84
			(void)fprintf(stderr,
D 121
			    "usage: login [-fp] [username]\n");
E 121
I 121
			    "usage: login [-fp] [-h hostname] [username]\n");
E 121
E 84
E 68
			exit(1);
E 67
E 43
		}
I 43
D 67
		break;
E 43
E 39
I 15
D 25
abnormal:
E 15
		rhost = 0;
		rflag = -1;
E 25
E 14
	}
E 12
I 10
D 14
#ifdef	TIOCLSET
E 10
I 2
D 4
	ioctl(0, TIOCSETD, &ldisc);
E 4
E 2
D 12
	ioctl(0, TIOCLSET, 0);
E 12
I 12
D 13
	ioctl(0, TIOCLSET, &zero);
E 13
I 13
	ioctl(0, TIOCLSET, 0);
E 13
E 12
I 10
#endif
E 14
I 14
D 25
normal:
E 25
D 20
	ioctl(0, TIOCLSET, &zero);
E 20
I 20
D 30
	ioctl(0, TIOCLSET, &zero);	/* XXX */
E 30
I 30
	ioctl(0, TIOCLSET, &zero);
E 30
E 20
E 14
E 10
I 4
	ioctl(0, TIOCNXCL, 0);
I 15
	ioctl(0, FIONBIO, &zero);
	ioctl(0, FIOASYNC, &zero);
E 15
E 4
D 2
	ioctl(0, TIOCNXCL, 0);
E 2
D 20
	gtty(0, &ttyb);
E 20
I 20
D 30
	ioctl(0, TIOCGETP, &ttyb);	/* XXX */
E 30
I 30
	ioctl(0, TIOCGETP, &ttyb);
E 67
I 67
	argc -= optind;
	argv += optind;
I 125

E 125
D 70
	if (*argv)
E 70
I 70
	if (*argv) {
D 74
		ask = 0;
E 74
E 70
		username = *argv;
I 102
D 118
		if (strlen(username) > UT_NAMESIZE)
			username[UT_NAMESIZE] = '\0';
E 118
E 102
I 70
D 74
	}
	else
E 74
I 74
		ask = 0;
	} else
E 74
		ask = 1;
I 83
	if (rflag)
		ask = 0;
E 83
E 70

D 108
	ioctlval = 0;
	(void)ioctl(0, TIOCLSET, &ioctlval);
	(void)ioctl(0, TIOCNXCL, 0);
D 68
	(void)ioctl(0, FIONBIO, &ioctlval);
	(void)ioctl(0, FIOASYNC, &ioctlval);
	(void)ioctl(0, TIOCGETP, &ttyb);
E 68
I 68
	(void)fcntl(0, F_SETFL, ioctlval);
	(void)ioctl(0, TIOCGETP, &sgttyb);
I 83

	/*
	 * If talking to an rlogin process, propagate the terminal type and
	 * baud rate across the network.
	 */
	if (rflag)
		doremoteterm(&sgttyb);
E 83
E 68
D 69

E 67
E 30
E 20
I 12
D 25
	if (rflag) {
		char *cp = index(term, '/');
		if (cp) {
			int i;
			*cp++ = 0;
			for (i = 0; i < NSPEEDS; i++)
				if (!strcmp(speeds[i], cp)) {
					ttyb.sg_ispeed = ttyb.sg_ospeed = i;
					break;
				}
		}
		ttyb.sg_flags = ECHO|CRMOD|ANYP|XTABS;
	}
E 25
I 25
	/*
D 67
	 * If talking to an rlogin process,
	 * propagate the terminal type and
E 67
I 67
	 * If talking to an rlogin process, propagate the terminal type and
E 67
	 * baud rate across the network.
	 */
	if (rflag)
D 67
		doremoteterm(term, &ttyb);
E 67
I 67
D 68
		doremoteterm(&ttyb);
E 67
I 53
	ttyb.sg_erase = CERASE;
	ttyb.sg_kill = CKILL;
E 68
I 68
		doremoteterm(&sgttyb);
E 69
	sgttyb.sg_erase = CERASE;
	sgttyb.sg_kill = CKILL;
E 68
E 53
E 25
I 14
D 15
	if (rflag == -1)
		rflag = 0;
E 15
E 14
E 12
D 10
	ttyb.sg_erase = '#';
	ttyb.sg_kill = '@';
E 10
I 10
D 20
	ttyb.sg_erase = CERASE;
	ttyb.sg_kill = CKILL;
E 10
	stty(0, &ttyb);
I 2
	ioctl(0, TIOCSETC, &tc);
I 10
D 14
#ifdef	TIOCLSET
E 14
E 10
	ioctl(0, TIOCSLTC, &ltc);
E 20
I 20
D 30
	ioctl(0, TIOCSETP, &ttyb);	/* XXX */
	ioctl(0, TIOCCSET, &tc);
E 30
I 30
D 67
	ioctl(0, TIOCSLTC, &ltc);
	ioctl(0, TIOCSETC, &tc);
	ioctl(0, TIOCSETP, &ttyb);
E 30
E 20
I 10
D 14
#endif
E 14
E 10
E 2
D 25
	for (t=3; t<20; t++)
E 25
I 25
D 44
	for (t = getdtablesize(); t > 3; t--)
E 44
I 44
	for (t = getdtablesize(); t > 2; t--)
E 44
E 25
		close(t);
E 67
I 67
	(void)ioctl(0, TIOCSLTC, &ltc);
	(void)ioctl(0, TIOCSETC, &tc);
D 68
	(void)ioctl(0, TIOCSETP, &ttyb);
E 68
I 68
	(void)ioctl(0, TIOCSETP, &sgttyb);
E 108
I 108
D 109
	(void) ioctl(0, TIOCNXCL, 0);
	(void) fcntl(0, F_SETFL, 0);
E 108
E 68

E 109
	for (cnt = getdtablesize(); cnt > 2; cnt--)
D 125
		close(cnt);
E 125
I 125
		(void)close(cnt);
E 125

E 67
D 125
	ttyn = ttyname(0);
E 125
I 125
	ttyn = ttyname(STDIN_FILENO);
E 125
D 10
	if (ttyn==0)
E 10
I 10
D 36
	if (ttyn==(char *)0)
E 36
I 36
D 51
	if (ttyn == (char *)0)
E 51
I 51
D 67
	if (ttyn == (char *)0 || *ttyn == '\0')
E 67
I 67
D 86
	if (ttyn == NULL || *ttyn == '\0')
E 67
E 51
E 36
E 10
		ttyn = "/dev/tty??";
E 86
I 86
	if (ttyn == NULL || *ttyn == '\0') {
D 125
		(void)sprintf(tname, "%s??", _PATH_TTY);
E 125
I 125
		(void)snprintf(tname, sizeof(tname), "%s??", _PATH_TTY);
E 125
		ttyn = tname;
	}
E 86
I 36
D 67
	tty = rindex(ttyn, '/');
	if (tty == NULL)
		tty = ttyn;
E 67
I 67
D 130
	if (tty = rindex(ttyn, '/'))
E 130
I 130
	if (tty = strrchr(ttyn, '/'))
E 130
		++tty;
E 67
	else
D 67
		tty++;
E 67
I 67
		tty = ttyn;

E 67
D 39
	openlog("login", 0, 0);
E 39
I 39
D 45
	openlog("login", LOG_ODELAY, 0);
E 45
I 45
D 94
	openlog("login", LOG_ODELAY, LOG_AUTH);
E 45
E 39
D 67
	t = 0;
I 49
	invalid = FALSE;
E 49
E 36
D 12

E 12
D 10
    loop:
I 4
	ldisc = 0;
	ioctl(0, TIOCSETD, &ldisc);
E 4
D 2
	ldisc = 0;
	ioctl(0, TIOCSETD, &ldisc);
E 2
	SCPYN(utmp.ut_name, "");
	if (argc>1) {
		SCPYN(utmp.ut_name, argv[1]);
		argc = 0;
	}
	while (utmp.ut_name[0] == '\0') {
		namep = utmp.ut_name;
		printf("login: ");
		while ((c = getchar()) != '\n') {
			if(c == ' ')
				c = '_';
			if (c == EOF)
				exit(0);
			if (namep < utmp.ut_name+NMAX)
				*namep++ = c;
		}
	}
	setpwent();
	if ((pwd = getpwnam(utmp.ut_name)) == NULL)
		pwd = &nouser;
	endpwent();
I 4
	if (!strcmp(pwd->pw_shell, "/bin/csh")) {
		ldisc = NTTYDISC;
E 10
I 10
	do {
		ldisc = 0;
E 10
		ioctl(0, TIOCSETD, &ldisc);
D 10
	}
E 4
D 2
	if (!strcmp(pwd->pw_shell, "/bin/csh")) {
		ldisc = NTTYDISC;
		ioctl(0, TIOCSETD, &ldisc);
	}
E 2
	if (*pwd->pw_passwd != '\0') {
I 4
		nice(-4);
E 4
D 2
		nice(-4);
E 2
		namep = crypt(getpass("Password:"),pwd->pw_passwd);
I 4
		nice(4);
E 4
D 2
		nice(4);
E 2
		if (strcmp(namep, pwd->pw_passwd)) {
bad:
E 10
I 10
D 49
		invalid = FALSE;
E 49
D 61
		SCPYN(utmp.ut_name, "");
E 61
I 61
		if (fflag == 0)
			SCPYN(utmp.ut_name, "");
E 61
D 25
		if (argc>1) {
E 25
I 25
		/*
		 * Name specified, take it.
		 */
		if (argc > 1) {
E 25
			SCPYN(utmp.ut_name, argv[1]);
			argc = 0;
E 67
I 67

E 94
D 70
	for (cnt = 0;; username = NULL) {
E 70
I 70
	for (cnt = 0;; ask = 1) {
E 70
D 89
		ioctlval = 0;
E 89
I 89
D 108
		ioctlval = TTYDISC;
E 89
		(void)ioctl(0, TIOCSETD, &ioctlval);

E 108
D 68
		if (!username)
E 68
I 68
D 70
		if (username == NULL) {
E 70
I 70
		if (ask) {
E 70
			fflag = 0;
E 68
			getloginname();
D 68
		if ((pwd = getpwnam(username)) == NULL)
			pwd = &nouser;
E 68
I 68
		}
I 124
		rootlogin = 0;
E 124
I 118
#ifdef	KERBEROS
D 130
		if ((instance = index(username, '.')) != NULL) {
E 130
I 130
		if ((instance = strchr(username, '.')) != NULL) {
E 130
			if (strncmp(instance, ".root", 5) == 0)
D 124
				rootlogin++;
E 124
I 124
				rootlogin = 1;
E 124
			*instance++ = '\0';
D 124
		} else {
			rootlogin = 0;
E 124
I 124
		} else
E 124
			instance = "";
D 124
		}
E 124
#endif
		if (strlen(username) > UT_NAMESIZE)
			username[UT_NAMESIZE] = '\0';

E 118
I 70
D 74
		/* note if trying multiple login's */
		if (repeatcnt) {
			if (strcmp(tbuf, username)) {
E 74
I 74
		/*
D 94
		 * Note if trying multiple user names;
		 * log failures for previous user name,
		 * but don't bother logging one failure
E 94
I 94
		 * Note if trying multiple user names; log failures for
		 * previous user name, but don't bother logging one failure
E 94
		 * for nonexistent name (mistyped username).
		 */
		if (failures && strcmp(tbuf, username)) {
			if (failures > (pwd ? 0 : 1))
E 74
				badlogin(tbuf);
D 74
				repeatcnt = 1;
				(void)strcpy(tbuf, username);
			}
			else
				++repeatcnt;
E 74
I 74
			failures = 0;
E 74
		}
D 74
		else {
			repeatcnt = 1;
			(void)strcpy(tbuf, username);
		}
E 74
I 74
		(void)strcpy(tbuf, username);
I 103

E 103
E 74
E 70
		if (pwd = getpwnam(username))
			salt = pwd->pw_passwd;
D 102
		else
			salt = "xx";
E 102
I 102
D 103
		else {
			/* take up the right amount of time */
			(void)crypt(getpass("Password:"), "xx");
			goto faked;
		}
E 103
I 103
		else
			salt = "xx";
E 103
E 102
E 68

D 105
		/* if user not super-user, check for disabled logins */
D 68
		if (pwd->pw_uid)
E 68
I 68
D 102
		if (pwd == NULL || pwd->pw_uid)
E 102
I 102
D 103
		if (pwd->pw_uid)
E 103
I 103
		if (!pwd || pwd->pw_uid)
E 103
E 102
E 68
			checknologin();

E 105
D 68
		if (!strcmp(pwd->pw_shell, "/bin/csh")) {
			ioctlval = NTTYDISC;
			(void)ioctl(0, TIOCSETD, &ioctlval);
E 67
		}
I 67

E 68
E 67
I 25
		/*
D 67
		 * If remote login take given name,
		 * otherwise prompt user for something.
E 67
I 67
D 68
		 * disallow automatic login to root, or if not root
		 * and the uid's differ
E 68
I 68
D 106
		 * Disallow automatic login to root; if not invoked by
		 * root, disallow if the uid's differ.
E 106
I 106
		 * if we have a valid account name, and it doesn't have a
		 * password, or the -f option was specified and the caller
		 * is root or the caller isn't changing their uid, don't
		 * authenticate.
E 106
E 68
E 67
		 */
E 25
I 12
D 15
		if (rflag)
E 15
I 15
D 46
		if (rflag) {
E 46
I 46
D 49
		if (rflag)
E 49
I 49
D 67
		if (rflag && !invalid)
E 49
E 46
E 15
D 14
			strcpy(utmp.ut_name, rusername);
E 14
I 14
D 20
			strcpy(utmp.ut_name, lusername);
E 20
I 20
			SCPYN(utmp.ut_name, lusername);
I 25
D 43
			/* autologin failed, prompt for passwd */
E 25
E 20
E 14
D 15
		else
E 15
I 15
			if (rflag == -1)
E 43
I 43
D 46
			if (usererr == -1)
E 43
				rflag = 0;
D 25
		} else
E 15
E 12
D 14
		while (utmp.ut_name[0] == '\0') {
			namep = utmp.ut_name;
D 12
#ifdef	UNAME
			if (uname(&uts) != -1)
				printf("%s login: ", uts.nodename);
			else
#endif
				printf("login: ");
E 12
I 12
			printf("%s login: ", sysname);
E 12
			while ((c = getchar()) != '\n') {
				if (c == ' ')
					c = '_';
				if (c == EOF)
					exit(0);
				if (namep < utmp.ut_name+NMAX)
					*namep++ = c;
E 14
I 14
			while (utmp.ut_name[0] == '\0') {
				namep = utmp.ut_name;
				{ char hostname[32];
				  gethostname(hostname, sizeof (hostname));
				  printf("%s login: ", hostname); }
				while ((c = getchar()) != '\n') {
					if (c == ' ')
						c = '_';
					if (c == EOF)
						exit(0);
					if (namep < utmp.ut_name+NMAX)
						*namep++ = c;
				}
E 14
			}
I 14
		if (rhost == 0) {
			setpwent();
			if ((pwd = getpwnam(utmp.ut_name)) == NULL)
				pwd = &nouser;
			endpwent();
E 25
I 25
D 31
		} else {
E 31
I 31
		} else
E 46
I 46
D 63
		else
E 63
I 63
		else {
E 63
E 46
E 31
			getloginname(&utmp);
I 63
			if (utmp.ut_name[0] == '-') {
				puts("login names may not start with '-'.");
				invalid = TRUE;
				continue;
			}
		}
E 63
I 49
		invalid = FALSE;
E 49
E 25
E 14
D 31
		}
E 31
D 14
		setpwent();
		if ((pwd = getpwnam(utmp.ut_name)) == NULL)
			pwd = &nouser;
		endpwent();
E 14
		if (!strcmp(pwd->pw_shell, "/bin/csh")) {
			ldisc = NTTYDISC;
			ioctl(0, TIOCSETD, &ldisc);
		}
E 67
I 61
D 68
		if (fflag) {
E 68
I 68
D 102
		if (fflag && pwd) {
E 102
I 102
D 103
		if (fflag) {
E 103
I 103
D 106
		if (pwd && fflag) {
E 103
E 102
E 68
D 94
			int uid = getuid();

E 94
D 67
			if (uid != 0 && uid != pwd->pw_uid)
				fflag = 0;
			/*
			 * Disallow automatic login for root.
			 */
			if (pwd->pw_uid == 0)
				fflag = 0;
E 67
I 67
D 68
			passwd_req = !pwd->pw_uid || uid && uid != pwd->pw_uid;
E 68
I 68
D 90
			passwd_req = pwd->pw_uid == 0 ||
E 90
I 90
			passwd_req =
#ifndef	KERBEROS
			     pwd->pw_uid == 0 ||
#endif
E 90
			    (uid && uid != pwd->pw_uid);
E 68
E 67
		}
E 61
D 14
		if (*pwd->pw_passwd != '\0') {
I 12
			char *pp;
E 12
			nice(-4);
D 12
			namep = crypt(getpass("Password:"),pwd->pw_passwd);
E 12
I 12
			if (rflag == 0)
				pp = getpass("Password:");
			else
				pp = rpassword;
			namep = crypt(pp,pwd->pw_passwd);
E 12
			nice(4);
			if (strcmp(namep, pwd->pw_passwd))
				invalid = TRUE;
E 14
I 14
D 25
		if (rhost == 0) {
			if (*pwd->pw_passwd != '\0') {
				char *pp;
				nice(-4);
				if (rflag == 0)
					pp = getpass("Password:");
				else
					pp = rpassword;
				namep = crypt(pp,pwd->pw_passwd);
				nice(4);
				if (strcmp(namep, pwd->pw_passwd))
					invalid = TRUE;
			}
E 25
I 25
D 67
		/*
		 * If no remote login authentication and
		 * a password exists for this user, prompt
		 * for one and verify it.
		 */
D 43
		if (!rflag && *pwd->pw_passwd != '\0') {
E 43
I 43
D 61
		if (usererr == -1 && *pwd->pw_passwd != '\0') {
E 61
I 61
		if (usererr == -1 && fflag == 0 && *pwd->pw_passwd != '\0') {
E 61
E 43
			char *pp;
E 67

D 67
			setpriority(PRIO_PROCESS, 0, -4);
			pp = getpass("Password:");
			namep = crypt(pp, pwd->pw_passwd);
			setpriority(PRIO_PROCESS, 0, 0);
			if (strcmp(namep, pwd->pw_passwd))
				invalid = TRUE;
E 25
E 14
		}
E 67
I 25
		/*
D 67
		 * If user not super-user, check for logins disabled.
E 67
I 67
D 69
		 * If no remote login authentication and a password exists
E 69
I 69
		 * If no pre-authentication and a password exists
E 69
		 * for this user, prompt for one and verify it.
E 67
		 */
E 25
D 66
		if (pwd->pw_uid != 0 && (nlfd = fopen(nolog, "r")) > 0) {
E 66
I 66
D 67
		if (pwd->pw_uid != 0 && (nlfd = fopen(nolog, "r"))) {
E 66
D 25
			/* logins are disabled except for root */
E 25
			while ((c = getc(nlfd)) != EOF)
				putchar(c);
			fflush(stdout);
			sleep(5);
			exit(0);
		}
I 25
		/*
		 * If valid so far and root is logging in,
		 * see if root logins on this terminal are permitted.
		 */
E 25
D 36
		if (!invalid && pwd->pw_uid == 0 &&
		    !rootterm(ttyn+sizeof("/dev/")-1)) {
D 15
			FILE *console = fopen("/dev/console", "w");
			if (console != NULL) {
				fprintf(console, "\r\nROOT LOGIN REFUSED %s\r\n"
				    , ttyn+sizeof("/dev/")-1
				);
				fclose(console);
			}
E 15
I 15
			logerr("ROOT LOGIN REFUSED %s",
			    ttyn+sizeof("/dev/")-1);
E 36
I 36
		if (!invalid && pwd->pw_uid == 0 && !rootterm(tty)) {
D 39
			syslog(LOG_INFO, "ROOT LOGIN REFUSED %s", tty);
E 39
I 39
D 45
			syslog(LOG_SECURITY, "ROOT LOGIN REFUSED %s", tty);
E 45
I 45
D 50
			syslog(LOG_CRIT, "ROOT LOGIN REFUSED %s", tty);
E 50
I 50
			if (utmp.ut_host[0])
				syslog(LOG_CRIT,
				    "ROOT LOGIN REFUSED ON %s FROM %.*s",
				    tty, HMAX, utmp.ut_host);
E 67
I 67
D 68
		if (!passwd_req || !*pwd->pw_passwd)
E 68
I 68
D 73
		if (!passwd_req || pwd && !*pwd->pw_passwd)
E 73
I 73
D 102
		if (!passwd_req || (pwd && !*pwd->pw_passwd))
E 102
I 102
D 103
		if (!passwd_req || !*pwd->pw_passwd)
E 103
I 103
		if (pwd && (!passwd_req || !*pwd->pw_passwd))
E 106
I 106
		if (pwd && (*pwd->pw_passwd == '\0' ||
		    fflag && (uid == 0 || uid == pwd->pw_uid)))
E 106
E 103
E 102
E 73
E 68
			break;
I 107
		fflag = 0;
I 118
		if (pwd && pwd->pw_uid == 0)
			rootlogin = 1;
I 123
D 124
		else
			rootlogin = 0;
E 124
E 123
E 118
E 107

I 118
		(void)setpriority(PRIO_PROCESS, 0, -4);

		p = getpass("Password:");

		if (pwd) {
#ifdef KERBEROS
			rval = klogin(pwd, instance, localhost, p);
I 131
			if (rval != 0 && rootlogin && pwd->pw_uid != 0)
				rootlogin = 0;
E 131
			if (rval == 0)
				authok = 1;
D 124
			else if (rval == 1) {
				if (pwd->pw_uid != 0)
					rootlogin = 0;
E 124
I 124
			else if (rval == 1)
E 124
				rval = strcmp(crypt(p, salt), pwd->pw_passwd);
D 124
			}
E 124
#else
			rval = strcmp(crypt(p, salt), pwd->pw_passwd);
#endif
		}
D 130
		bzero(p, strlen(p));
E 130
I 130
		memset(p, 0, strlen(p));
E 130

		(void)setpriority(PRIO_PROCESS, 0, 0);

E 118
I 94
		/*
D 118
		 * If trying to log in as root, but with insecure terminal,
		 * refuse the login attempt.
E 118
I 118
		 * If trying to log in as root without Kerberos,
		 * but with insecure terminal, refuse the login attempt.
E 118
		 */
D 103
		if (pwd->pw_uid == 0 && !rootterm(tty)) {
E 103
I 103
D 115
		if (pwd && pwd->pw_uid == 0 && !rootterm(tty)) {
E 115
I 115
D 118
		if (ROOTLOGIN && !rootterm(tty)) {
E 118
I 118
#ifdef KERBEROS
		if (authok == 0)
#endif
		if (pwd && rootlogin && !rootterm(tty)) {
E 118
E 115
E 103
			(void)fprintf(stderr,
			    "%s login refused on this terminal.\n",
			    pwd->pw_name);
			if (hostname)
				syslog(LOG_NOTICE,
				    "LOGIN %s REFUSED FROM %s ON TTY %s",
				    pwd->pw_name, hostname, tty);
			else
				syslog(LOG_NOTICE,
				    "LOGIN %s REFUSED ON TTY %s",
				     pwd->pw_name, tty);
			continue;
		}

E 94
D 102
		setpriority(PRIO_PROCESS, 0, -4);
D 68
		p = getpass("Password:");
		p = crypt(p, pwd->pw_passwd);
E 68
I 68
D 73
		p = crypt(getpass("Password:"), salt);
E 73
I 73
		pp = getpass("Password:");
		p = crypt(pp, salt);
E 73
E 68
		setpriority(PRIO_PROCESS, 0, 0);
E 102
I 102
D 118
		(void)setpriority(PRIO_PROCESS, 0, -4);
I 103

E 103
		p = getpass("Password:");
E 102
I 73

I 103
		if (pwd) {
E 103
D 76
D 102
#ifdef	KERBEROS

		/*
I 77
D 93
		 * If not present in pw file, act as we normally would.
E 93
I 93
		 * If not present in pw file, act as old login would.
E 93
E 77
		 * If we aren't Kerberos-authenticated, try the normal
		 * pw file for a password.  If that's ok, log the user
		 * in without issueing any tickets.
		 */

D 74
		if(!get_krbrlm(realm,1)) {
E 74
I 74
D 77
		if (!get_krbrlm(realm,1)) {
E 74
			/* get TGT for local realm */
			kerror = get_in_tkt(pwd->pw_name, inst, realm,
				"krbtgt", realm, LIFE, pp);
D 74
			if(kerror == KSUCCESS) {
E 74
I 74
			if (kerror == KSUCCESS) {
E 77
I 77
D 87
		if (pwd && !krb_get_lrealm(realm,1)) {
E 87
I 87
		if (pwd && (krb_get_lrealm(realm,1) == KSUCCESS)) {
I 90

E 90
E 87
D 84
			/* get TGT for local realm
			 * be careful about uid's here for ticket
			 * file ownership
E 84
I 84
			/*
D 90
			 * get TGT for local realm; be careful about uid's
			 * here for ticket file ownership
E 90
I 90
			 * get TGT for local realm
D 94
			 *	convention: store tickets in file
D 93
			 *	associated with tty name
E 93
I 93
			 *	associated with tty name, which should
			 *	be available
E 94
I 94
			 * convention: store tickets in file associated
			 * with tty name, which should be available
E 94
E 93
E 90
E 84
			 */
D 84
			(void) setreuid(geteuid(),pwd->pw_uid);
			kerror = krb_get_pw_in_tkt(
				pwd->pw_name, "", realm,
E 84
I 84
D 90
			(void)setreuid(geteuid(),pwd->pw_uid);
D 87
			kerror = krb_get_pw_in_tkt(pwd->pw_name, "", realm,
E 84
				"krbtgt", realm, DEFAULT_TKT_LIFE, pp);
E 87
I 87
			kerror = krb_get_pw_in_tkt(
				PRINCIPAL_NAME, PRINCIPAL_INST, realm,
				INITIAL_TICKET, realm, DEFAULT_TKT_LIFE, pp);
E 87
D 84
			(void) setuid(0);
E 84
I 84
			(void)setuid(0);
E 90
I 90
D 94

E 94
			(void)sprintf(tkfile, "%s_%s", TKT_ROOT, tty);
			kerror = INTK_ERR;
			if (setenv("KRBTKFILE", tkfile, 1) < 0)
				syslog(LOG_ERR, "couldn't set tkfile environ");
			else {
I 92
D 93
				setreuid(pwd->pw_uid, 0);
E 93
I 93
				(void) unlink(tkfile);
E 93
E 92
				kerror = krb_get_pw_in_tkt(
D 93
					PRINCIPAL_NAME, PRINCIPAL_INST, realm,
					INITIAL_TICKET, realm, DEFAULT_TKT_LIFE,
E 93
I 93
					PRINCIPAL_NAME,	/* user */
					PRINCIPAL_INST,	/* (null) */
					realm,
					INITIAL_TICKET, realm,
					DEFAULT_TKT_LIFE,
E 93
					pp);
I 92
D 93
				setuid(0);
E 92
				if ((kerror == KSUCCESS) &&
				    (chown(tkfile, pwd->pw_uid) < 0)) {
					syslog(LOG_ERR,
						"couldn't chown tkfile: %m");
					kerror = INTK_ERR;
I 92
				} else if (kerror != KSUCCESS) {
					syslog(LOG_ERR,
						"problem getting intkt: %s\n",
						krb_err_txt[kerror]);
E 92
				}
E 93
I 93
D 94

				if (chown(tkfile, pwd->pw_uid, pwd->pw_gid) < 0)
					syslog(LOG_ERR, "chown tkfile: %m");
E 94
E 93
			}
E 90
I 87
			/*
			 * If we got a TGT, get a local "rcmd" ticket and
			 * check it so as to ensure that we are not
			 * talking to a bogus Kerberos server
I 90
			 *
			 * There are 2 cases where we still allow a login:
			 *	1> the VERIFY_SERVICE doesn't exist in the KDC
			 *	2> local host has no srvtab, as (hopefully)
			 *	   indicated by a return value of RD_AP_UNDEC
			 *	   from krb_rd_req()
E 90
			 */
E 87
E 84
			if (kerror == INTK_OK) {
I 94
				if (chown(tkfile, pwd->pw_uid, pwd->pw_gid) < 0)
					syslog(LOG_ERR, "chown tkfile: %m");
E 94
E 77
E 74
D 87
				bzero(pp, strlen(pp));
				notickets = 0;	/* user got ticket */
				break;
E 87
I 87
				(void) strncpy(savehost,
					krb_get_phost(localhost),
					sizeof(savehost));
				savehost[sizeof(savehost)-1] = NULL;
				kerror = krb_mk_req(&ticket, VERIFY_SERVICE,
					savehost, realm, 33);
I 90
				/*
D 93
				 * if the "VERIFY_SERVICE" doesn't exist in the
				 * KDC for this host, still allow login,
E 93
I 93
				 * if the "VERIFY_SERVICE" doesn't exist in
				 * the KDC for this host, still allow login,
E 93
				 * but log the error condition
				 */
E 90
				if (kerror == KDC_PR_UNKNOWN) {
D 90
					syslog(LOG_WARNING,
E 90
I 90
					syslog(LOG_NOTICE,
E 90
					    "Warning: TGT not verified (%s)",
						krb_err_txt[kerror]);
					bzero(pp, strlen(pp));
					notickets = 0;
					break;		/* ok */
				} else if (kerror != KSUCCESS) {
					printf("Unable to use TGT: (%s)\n",
						krb_err_txt[kerror]);
D 90
					syslog(LOG_WARNING,
E 90
I 90
					syslog(LOG_NOTICE,
E 90
					    "Unable to use TGT: (%s)",
						krb_err_txt[kerror]);
					dest_tkt();
					/* fall thru: no login */
				} else {
					if (!(hp = gethostbyname(localhost))) {
D 93
						syslog(LOG_ERR, "couldn't get local host address");
E 93
I 93
						syslog(LOG_ERR,
						    "couldn't get local host address");
E 93
					} else {
					    bcopy((char *) hp->h_addr,
						(char *) &faddr, sizeof(faddr));
					    if ((kerror = krb_rd_req(&ticket,
						VERIFY_SERVICE, savehost, faddr,
						&authdata, "")) != KSUCCESS) {
D 90
						    printf("Unable to verify rcmd ticket: (%s)\n",
E 90
I 90

						if (kerror = RD_AP_UNDEC) {
							syslog(LOG_NOTICE,
							  "krb_rd_req: (%s)\n",
							  krb_err_txt[kerror]);
							bzero(pp, strlen(pp));
							notickets = 0;
							break;	/* ok */
						} else {
						    printf("Unable to verify %s ticket: (%s)\n",
							VERIFY_SERVICE,
E 90
							krb_err_txt[kerror]);
D 90
						syslog(LOG_WARNING, "couldn't verify rcmd ticket: %s",
E 90
I 90
						    syslog(LOG_NOTICE,
						    "couldn't verify %s ticket: %s",
							VERIFY_SERVICE,
E 90
							krb_err_txt[kerror]);
I 90
						}
						/* fall thru: no login */
E 90
					    } else {
						bzero(pp, strlen(pp));
						notickets = 0;	/* got ticket */
						break;		/* ok */
					    }
					}
				}

I 93
			} else {
				(void) unlink(tkfile);
D 94
				if (kerror != INTK_BADPW)
E 94
I 94
				if ((kerror != INTK_BADPW) &&
				    kerror != KDC_PR_UNKNOWN)
E 94
					syslog(LOG_ERR,
						"Kerberos intkt error: %s",
						krb_err_txt[kerror]);
E 93
E 87
			}
		}
I 90

E 102
I 102
#ifdef KERBEROS
D 103
		rval = klogin(pwd, localhost, p);
		if (rval == 1)
			rval = strcmp(crypt(p, salt), pwd->pw_passwd);
E 103
I 103
			rval = klogin(pwd, localhost, p);
			if (rval == 1)
				rval = strcmp(crypt(p, salt), pwd->pw_passwd);
E 103
#else
D 103
		rval = strcmp(crypt(p, salt), pwd->pw_passwd);
E 103
I 103
			rval = strcmp(crypt(p, salt), pwd->pw_passwd);
E 103
E 102
E 90
#endif
I 103
		}
E 103
E 76
D 102
		(void) bzero(pp, strlen(pp));
E 73
D 68
		if (!strcmp(p, pwd->pw_passwd))
E 68
I 68
		if (pwd && !strcmp(p, pwd->pw_passwd))
E 102
I 102
		bzero(p, strlen(p));
D 103
		if (!rval)
E 103
I 103

		(void)setpriority(PRIO_PROCESS, 0, 0);

E 118
		if (pwd && !rval)
E 103
E 102
E 68
			break;

D 84
		printf("Login incorrect\n");
E 84
I 84
D 102
		(void)printf("Login incorrect\n");
E 102
I 102
D 103
faked:		(void)printf("Login incorrect\n");
E 103
I 103
		(void)printf("Login incorrect\n");
E 103
E 102
E 84
I 74
		failures++;
E 74
D 70
		if (++cnt >= 5) {
			if (hostname)
			    syslog(LOG_ERR,
				"REPEATED LOGIN FAILURES ON %s FROM %.*s, %.*s",
				tty, UT_HOSTSIZE, hostname, UT_NAMESIZE,
				username);
E 67
			else
D 67
				syslog(LOG_CRIT,
				    "ROOT LOGIN REFUSED ON %s", tty);
E 50
E 45
E 39
E 36
E 15
			invalid = TRUE;
E 67
I 67
			    syslog(LOG_ERR,
				"REPEATED LOGIN FAILURES ON %s, %.*s",
				tty, UT_NAMESIZE, username);
			(void)ioctl(0, TIOCHPCL, (struct sgttyb *)NULL);
			sleepexit(1);
E 70
I 70
		/* we allow 10 tries, but after 3 we start backing off */
		if (++cnt > 3) {
			if (cnt >= 10) {
				badlogin(username);
D 109
				(void)ioctl(0, TIOCHPCL, (struct sgttyb *)NULL);
E 109
				sleepexit(1);
			}
			sleep((u_int)((cnt - 3) * 5));
E 70
E 67
		}
D 67
		if (invalid) {
E 10
			printf("Login incorrect\n");
D 10
			if (ttyn[LMAX] == 'd') {
E 10
I 10
D 15
			if (ttyn[sizeof("/dev/tty")-1] == 'd') {
E 10
				FILE *console = fopen("/dev/console", "w");
				if (console != NULL) {
D 10
					fprintf(console, "\r\nBADDIALUP %s %s\r\n", ttyn+5, utmp.ut_name);
E 10
I 10
					fprintf(console, "\r\nBADDIALUP %s %s\r\n"
					    , ttyn+sizeof("/dev/")-1
					    , utmp.ut_name);
E 10
					fclose(console);
				}
			}
E 15
I 15
D 36
			if (ttyn[sizeof("/dev/tty")-1] == 'd')
D 32
				logerr("BADDIALUP %s %s\n",
E 32
I 32
				logerr("BADDIALUP %s %s",
E 32
				    ttyn+sizeof("/dev/")-1, utmp.ut_name);
E 36
I 36
			if (++t >= 5) {
D 39
				syslog(LOG_INFO,
E 39
I 39
D 45
				syslog(LOG_SECURITY,
E 45
I 45
D 50
				syslog(LOG_CRIT,
E 45
E 39
				    "REPEATED LOGIN FAILURES %s, %s",
					tty, utmp.ut_name);
E 50
I 50
				if (utmp.ut_host[0])
D 61
					syslog(LOG_CRIT,
					    "REPEATED LOGIN FAILURES ON %s FROM %.*s, %.*s",
E 61
I 61
					syslog(LOG_ERR,
			    "REPEATED LOGIN FAILURES ON %s FROM %.*s, %.*s",
E 61
					    tty, HMAX, utmp.ut_host,
					    NMAX, utmp.ut_name);
				else
D 61
					syslog(LOG_CRIT,
					    "REPEATED LOGIN FAILURES ON %s, %.*s",
E 61
I 61
					syslog(LOG_ERR,
				    "REPEATED LOGIN FAILURES ON %s, %.*s",
E 61
						tty, NMAX, utmp.ut_name);
E 50
				ioctl(0, TIOCHPCL, (struct sgttyb *) 0);
D 39
				close(0);
				close(1);
				close(2);
E 39
I 39
				close(0), close(1), close(2);
E 39
				sleep(10);
				exit(1);
			}
E 36
E 15
D 10
			goto loop;
E 10
		}
D 10
	}
	sprintf(user, "USER=%.*s", NMAX, pwd->pw_name);
I 6
#ifdef ERNIE
E 6
	if (pwd->pw_uid == 0 && ttyn[5] != 'c')
		goto bad;
I 6
#endif
E 6
	if (ttyn[LMAX] == 'd') {
		FILE *console = fopen("/dev/console", "w");
		if (console != NULL) {
			fprintf(console, "\r\nDIALUP %s %s\r\n", ttyn+5, pwd->pw_name);
			fclose(console);
E 10
I 10
		if (*pwd->pw_shell == '\0')
			pwd->pw_shell = "/bin/sh";
D 36
		i = strlen(pwd->pw_shell);
E 36
		if (chdir(pwd->pw_dir) < 0 && !invalid ) {
			if (chdir("/") < 0) {
				printf("No directory!\n");
				invalid = TRUE;
			} else {
D 25
				printf("No directory!  Logging in with home=/\n");
E 25
I 25
				printf("No directory! %s\n",
				   "Logging in with home=/");
E 25
				pwd->pw_dir = "/";
			}
E 10
		}
I 25
		/*
		 * Remote login invalid must have been because
		 * of a restriction of some sort, no extra chances.
		 */
E 25
I 12
D 43
		if (rflag && invalid)
E 43
I 43
		if (!usererr && invalid)
E 43
			exit(1);
E 12
D 10
	}
	if((f = open(lastlog, 2)) >= 0) {
		struct lastlog ll;
E 10
I 10
	} while (invalid);
I 25
/* committed to login turn off timeout */
	alarm(0);
E 67
I 67
	}
E 67
E 25
E 10

I 12
D 24

E 24
I 24
D 42
	if (quota(Q_SETUID, pwd->pw_uid, 0, 0) < 0) {
E 42
I 42
D 67
	if (quota(Q_SETUID, pwd->pw_uid, 0, 0) < 0 && errno != EINVAL) {
E 42
		if (errno == EUSERS)
			printf("%s.\n%s.\n",
			   "Too many users logged on already",
			   "Try again later");
		else if (errno == EPROCLIM)
			printf("You have too many processes running.\n");
E 67
I 67
	/* committed to login -- turn off timeout */
	(void)alarm((u_int)0);
D 103

I 102
	/* reset priority */
	(void)setpriority(PRIO_PROCESS, 0, 0);
E 103

E 102
I 86
D 118
	/* paranoia... */
E 118
	endpwent();
I 105

	/* if user not super-user, check for disabled logins */
D 115
	if (pwd->pw_uid)
E 115
I 115
D 118
	if (!(ROOTLOGIN))
E 118
I 118
D 121
	if (!(rootlogin))
E 121
I 121
	if (!rootlogin)
E 121
E 118
E 115
		checknologin();
E 105
D 94

E 86
I 70
D 74
	/* log any mistakes -- don't count last one */
	--repeatcnt;
	badlogin(username);

E 74
E 70
	/*
	 * If valid so far and root is logging in, see if root logins on
	 * this terminal are permitted.
	 */
D 68
	if (!pwd->pw_uid && !rootterm(tty)) {
E 68
I 68
D 70
	if (pwd->pw_uid == 0 && !rootterm(tty)) {
E 70
I 70
D 74
	if (pwd->pw_uid == 0 && !rootterm()) {
E 74
I 74
	if (pwd->pw_uid == 0 && !rootterm(tty)) {
E 74
E 70
E 68
		if (hostname)
D 68
			syslog(LOG_CRIT, "ROOT LOGIN REFUSED ON %s FROM %.*s",
E 68
I 68
D 70
			syslog(LOG_ERR, "ROOT LOGIN REFUSED ON %s FROM %.*s",
E 68
			    tty, UT_HOSTSIZE, hostname);
E 70
I 70
D 74
			syslog(LOG_ERR, "ROOT LOGIN REFUSED ON %s FROM %s",
			    tty, hostname);
E 74
I 74
			syslog(LOG_NOTICE, "ROOT LOGIN REFUSED FROM %s",
			    hostname);
E 74
E 70
E 67
		else
D 38
			perror("setuid");
E 38
I 38
D 67
			perror("quota (Q_SETUID)");
E 38
		sleep(5);
		exit(0);
E 67
I 67
D 68
			syslog(LOG_CRIT, "ROOT LOGIN REFUSED ON %s", tty);
E 68
I 68
D 74
			syslog(LOG_ERR, "ROOT LOGIN REFUSED ON %s", tty);
E 74
I 74
			syslog(LOG_NOTICE, "ROOT LOGIN REFUSED ON %s", tty);
E 74
E 68
D 84
		printf("Login incorrect\n");
E 84
I 84
		(void)printf("Login incorrect\n");
E 84
		sleepexit(1);
E 67
	}
E 94
E 24
E 12
D 5
		lseek(f, pwd->pw_uid * sizeof (struct lastlog), 0);
E 5
I 5
D 10
		lseek(f, (long) pwd->pw_uid * sizeof (struct lastlog), 0);
E 5
		if (read(f, (char *) &ll, sizeof ll) == sizeof ll && ll.ll_time != 0) {
			register char *ep = (char *) ctime(&ll.ll_time);
			printf("Last login: ");
			ep[24 - 5] = 0;
			printf("%s on %.*s\n", ep, LMAX, ll.ll_line);
		}
D 5
		lseek(f, pwd->pw_uid * sizeof (struct lastlog), 0);
E 5
I 5
		lseek(f, (long) pwd->pw_uid * sizeof (struct lastlog), 0);
E 5
		time(&ll.ll_time);
		strcpyn(ll.ll_line, ttyn+5, LMAX);
		write(f, (char *) &ll, sizeof ll);
		close(f);
	}
	if(chdir(pwd->pw_dir) < 0) {
I 7
D 8
	    printf("Logging with home=/tmp\n");
	    pwd->pw_dir = "/tmp";
	    if(chdir("/tmp") < 0) {
E 8
I 8
	    printf("Logging with home=/\n");
	    pwd->pw_dir = "/";
	    if(chdir("/") < 0) {
E 8
E 7
		printf("No directory\n");
		goto loop;
I 7
	    }
E 7
	}
E 10
D 67
	time(&utmp.ut_time);
D 65
	t = ttyslot();
D 25
	if (t>0 && (f = open("/etc/utmp", 1)) >= 0) {
E 25
I 25
D 36
	if (t > 0 && (f = open("/etc/utmp", 1)) >= 0) {
E 36
I 36
	if (t > 0 && (f = open("/etc/utmp", O_WRONLY)) >= 0) {
E 36
E 25
		lseek(f, (long)(t*sizeof(utmp)), 0);
D 36
		SCPYN(utmp.ut_line, rindex(ttyn, '/')+1);
E 36
I 36
		SCPYN(utmp.ut_line, tty);
E 36
		write(f, (char *)&utmp, sizeof(utmp));
		close(f);
	}
D 25
	if (t>0 && (f = open("/usr/adm/wtmp", 1)) >= 0) {
E 25
I 25
D 36
	if (t > 0 && (f = open("/usr/adm/wtmp", 1)) >= 0) {
E 25
		lseek(f, 0L, 2);
E 36
I 36
	if ((f = open("/usr/adm/wtmp", O_WRONLY|O_APPEND)) >= 0) {
E 36
		write(f, (char *)&utmp, sizeof(utmp));
		close(f);
	}
E 65
I 65
	SCPYN(utmp.ut_line, tty);
	login(&utmp);
E 65
I 10
D 15
	quietlog = FALSE;
E 15
I 15
D 25
	quietlog = 0;
E 15
	if (access(qlog, 0) == 0)
D 15
		quietlog = TRUE;
	if ( !quietlog && (f = open(lastlog, 2)) >= 0 ) {
E 15
I 15
		quietlog = 1;
E 25
I 25
D 36
	quietlog = access(qlog, 0) == 0;
E 25
	if ((f = open(lastlog, 2)) >= 0) {
E 36
I 36
	quietlog = access(qlog, F_OK) == 0;
	if ((f = open(lastlog, O_RDWR)) >= 0) {
E 36
E 15
		struct lastlog ll;
E 67

D 67
		lseek(f, (long)pwd->pw_uid * sizeof (struct lastlog), 0);
		if (read(f, (char *) &ll, sizeof ll) == sizeof ll &&
D 25
		    ll.ll_time != 0) {
I 15
			if (quietlog == 0)
E 15
			printf("Last login: %.*s on %.*s\n"
			    , 24-5
			    , (char *) ctime(&ll.ll_time)
			    , sizeof(ll.ll_line)
			    , ll.ll_line
			);
E 25
I 25
		    ll.ll_time != 0 && !quietlog) {
			printf("Last login: %.*s ",
			    24-5, (char *)ctime(&ll.ll_time));
			if (*ll.ll_host != '\0')
				printf("from %.*s\n",
				    sizeof (ll.ll_host), ll.ll_host);
			else
				printf("on %.*s\n",
				    sizeof (ll.ll_line), ll.ll_line);
E 67
I 67
D 68
	if (*pwd->pw_shell == '\0')
		pwd->pw_shell = BSHELL;

	if (chdir(pwd->pw_dir) < 0) {
		printf("No directory %s!\n", pwd->pw_dir);
		if (chdir("/"))
			exit(0);
		pwd->pw_dir = "/";
		printf("Logging in with home = \"/\".\n");
	}

E 68
D 98
	if (quota(Q_SETUID, pwd->pw_uid, 0, 0) < 0 && errno != EINVAL) {
		switch(errno) {
		case EUSERS:
D 84
			fprintf(stderr,
E 84
I 84
			(void)fprintf(stderr,
E 84
		"Too many users logged on already.\nTry again later.\n");
			break;
		case EPROCLIM:
D 84
			fprintf(stderr,
E 84
I 84
			(void)fprintf(stderr,
E 84
			    "You have too many processes running.\n");
			break;
		default:
			perror("quota (Q_SETUID)");
E 67
E 25
		}
D 67
		lseek(f, (long)pwd->pw_uid * sizeof (struct lastlog), 0);
		time(&ll.ll_time);
D 36
		SCPYN(ll.ll_line, rindex(ttyn, '/')+1);
E 36
I 36
		SCPYN(ll.ll_line, tty);
E 36
I 25
		SCPYN(ll.ll_host, utmp.ut_host);
E 25
		write(f, (char *) &ll, sizeof ll);
		close(f);
E 67
I 67
		sleepexit(0);
E 67
	}
E 10
D 54
	chown(ttyn, pwd->pw_uid, pwd->pw_gid);
E 54
I 54
D 55
	chown(ttyn, pwd->pw_uid, WRITEGID);
E 55
I 55
D 57
	chown(ttyn, pwd->pw_uid, WRITEGID(pwd->pw_gid));
E 57
I 57
D 67
	chown(ttyn, pwd->pw_uid, TTYGID(pwd->pw_gid));
E 57
E 55
E 54
I 39
D 44
	if (!hflag)					/* XXX */
E 44
I 44
	if (!hflag && !rflag)					/* XXX */
E 44
		ioctl(0, TIOCSWINSZ, &win);
E 39
I 18
D 20
	chmod(ttyn, 622);
E 20
I 20
D 54
	chmod(ttyn, 0622);
E 54
I 54
	chmod(ttyn, 0620);
E 54
E 20
E 18
	setgid(pwd->pw_gid);
I 13
D 17
	inigrp(utmp.ut_name, pwd->pw_gid);
E 17
I 17
	strncpy(name, utmp.ut_name, NMAX);
	name[NMAX] = '\0';
D 19
	inigrp(name, pwd->pw_gid);
E 19
I 19
	initgroups(name, pwd->pw_gid);
E 67
I 67

E 98
I 68
	if (chdir(pwd->pw_dir) < 0) {
D 84
		printf("No directory %s!\n", pwd->pw_dir);
E 84
I 84
D 121
		(void)printf("No directory %s!\n", pwd->pw_dir);
E 121
I 121
		(void)printf("No home directory %s!\n", pwd->pw_dir);
E 121
E 84
		if (chdir("/"))
			exit(0);
		pwd->pw_dir = "/";
D 84
		printf("Logging in with home = \"/\".\n");
E 84
I 84
		(void)printf("Logging in with home = \"/\".\n");
E 84
	}
I 73
D 76

I 82
	quietlog = access(_PATH_HUSHLOGIN, F_OK) == 0;

E 82
D 78
#ifdef	KERBEROS
E 78
I 78
D 102
#ifdef KERBEROS
E 78
D 74
	if(notickets)
E 74
I 74
D 82
	if (notickets)
E 82
I 82
	if (notickets && !quietlog)
E 82
E 74
D 84
		printf("Warning: no Kerberos tickets issued\n");
E 84
I 84
		(void)printf("Warning: no Kerberos tickets issued\n");
E 84
#endif
E 76
E 73

E 102
I 90
D 91
#if BSD > 43
E 91
E 90
I 79
#define	TWOWEEKS	(14*24*60*60)
	if (pwd->pw_change || pwd->pw_expire)
		(void)gettimeofday(&tp, (struct timezone *)NULL);
	if (pwd->pw_change)
		if (tp.tv_sec >= pwd->pw_change) {
			printf("Sorry -- your password has expired.\n");
			sleepexit(1);
		}
		else if (tp.tv_sec - pwd->pw_change < TWOWEEKS) {
			ttp = localtime(&pwd->pw_change);
			printf("Warning: your password expires on %s %d, 19%d\n",
			    months[ttp->tm_mon], ttp->tm_mday, ttp->tm_year);
		}
	if (pwd->pw_expire)
		if (tp.tv_sec >= pwd->pw_expire) {
			printf("Sorry -- your account has expired.\n");
			sleepexit(1);
		}
		else if (tp.tv_sec - pwd->pw_expire < TWOWEEKS) {
			ttp = localtime(&pwd->pw_expire);
			printf("Warning: your account expires on %s %d, 19%d\n",
			    months[ttp->tm_mon], ttp->tm_mday, ttp->tm_year);
		}

E 79
I 78
D 88
#define	TWOWEEKS	(14*24*60*60)
E 88
	if (pwd->pw_change || pwd->pw_expire)
		(void)gettimeofday(&tp, (struct timezone *)NULL);
	if (pwd->pw_change)
		if (tp.tv_sec >= pwd->pw_change) {
D 84
			printf("Sorry -- your password has expired.\n");
E 84
I 84
			(void)printf("Sorry -- your password has expired.\n");
E 84
			sleepexit(1);
D 118
		}
D 82
		else if (tp.tv_sec - pwd->pw_change < TWOWEEKS) {
E 82
I 82
D 88
		else if (tp.tv_sec - pwd->pw_change < TWOWEEKS && !quietlog) {
E 88
I 88
		else if (pwd->pw_change - tp.tv_sec <
E 118
I 118
		} else if (pwd->pw_change - tp.tv_sec <
E 118
D 104
		    2 * DAYSPERWEEK * SECSPERDAY && !quietlog) {
E 88
E 82
			ttp = localtime(&pwd->pw_change);
D 84
			printf("Warning: your password expires on %s %d, 19%d\n",
			    months[ttp->tm_mon], ttp->tm_mday, ttp->tm_year);
E 84
I 84
			(void)printf("Warning: your password expires on %s %d, %d\n",
D 88
			    months[ttp->tm_mon], ttp->tm_mday, TM_YEAR_BASE + ttp->tm_year);
E 88
I 88
			    months[ttp->tm_mon], ttp->tm_mday,
			    TM_YEAR_BASE + ttp->tm_year);
E 88
E 84
		}
E 104
I 104
		    2 * DAYSPERWEEK * SECSPERDAY && !quietlog)
			(void)printf("Warning: your password expires on %s",
D 122
			    ctime(&pwd->pw_expire));
E 122
I 122
			    ctime(&pwd->pw_change));
E 122
E 104
	if (pwd->pw_expire)
		if (tp.tv_sec >= pwd->pw_expire) {
D 84
			printf("Sorry -- your account has expired.\n");
E 84
I 84
			(void)printf("Sorry -- your account has expired.\n");
E 84
			sleepexit(1);
D 118
		}
D 82
		else if (tp.tv_sec - pwd->pw_expire < TWOWEEKS) {
E 82
I 82
D 88
		else if (tp.tv_sec - pwd->pw_expire < TWOWEEKS && !quietlog) {
E 88
I 88
		else if (pwd->pw_expire - tp.tv_sec <
E 118
I 118
		} else if (pwd->pw_expire - tp.tv_sec <
E 118
D 104
		    2 * DAYSPERWEEK * SECSPERDAY && !quietlog) {
E 88
E 82
			ttp = localtime(&pwd->pw_expire);
D 84
			printf("Warning: your account expires on %s %d, 19%d\n",
			    months[ttp->tm_mon], ttp->tm_mday, ttp->tm_year);
E 84
I 84
			(void)printf("Warning: your account expires on %s %d, %d\n",
D 88
			    months[ttp->tm_mon], ttp->tm_mday, TM_YEAR_BASE + ttp->tm_year);
E 88
I 88
			    months[ttp->tm_mon], ttp->tm_mday,
			    TM_YEAR_BASE + ttp->tm_year);
E 88
E 84
		}
E 104
I 104
		    2 * DAYSPERWEEK * SECSPERDAY && !quietlog)
			(void)printf("Warning: your account expires on %s",
			    ctime(&pwd->pw_expire));
E 104
I 90
D 91
#endif
E 91
E 90

E 78
D 125
	/* nothing else left to fail -- really log in */
E 68
	{
		struct utmp utmp;
E 125
I 125
	/* Nothing else left to fail -- really log in. */
D 130
	bzero((void *)&utmp, sizeof(utmp));
E 130
I 130
	memset((void *)&utmp, 0, sizeof(utmp));
E 130
	(void)time(&utmp.ut_time);
D 126
	strncpy(utmp.ut_name, username, sizeof(utmp.ut_name));
E 126
I 126
	(void)strncpy(utmp.ut_name, username, sizeof(utmp.ut_name));
E 126
	if (hostname)
		(void)strncpy(utmp.ut_host, hostname, sizeof(utmp.ut_host));
	(void)strncpy(utmp.ut_line, tty, sizeof(utmp.ut_line));
	login(&utmp);
E 125

I 74
D 102
		bzero((char *)&utmp, sizeof(utmp));
E 102
I 102
D 125
		bzero((void *)&utmp, sizeof(utmp));
E 102
E 74
		(void)time(&utmp.ut_time);
		strncpy(utmp.ut_name, username, sizeof(utmp.ut_name));
D 72
		strncpy(utmp.ut_host, hostname, sizeof(utmp.ut_host));
E 72
I 72
		if (hostname)
			strncpy(utmp.ut_host, hostname, sizeof(utmp.ut_host));
D 74
		else
			bzero(utmp.ut_host, sizeof(utmp.ut_host));
E 74
E 72
		strncpy(utmp.ut_line, tty, sizeof(utmp.ut_line));
		login(&utmp);
	}

E 125
D 80
	quietlog = access(HUSHLOGIN, F_OK) == 0;
E 80
I 80
D 82
	quietlog = access(_PATH_HUSHLOGIN, F_OK) == 0;
E 82
E 80
D 70
	dolastlog(quietlog, tty);
E 70
I 70
	dolastlog(quietlog);
E 70
D 108

D 69
	if (!hflag && !rflag) {					/* XXX */
E 69
I 69
D 83
	if (!hflag) {					/* XXX */
E 83
I 83
	if (!hflag && !rflag) {					/* XXX */
E 83
E 69
		static struct winsize win = { 0, 0, 0, 0 };

		(void)ioctl(0, TIOCSWINSZ, &win);
	}
E 108

	(void)chown(ttyn, pwd->pw_uid,
	    (gr = getgrnam(TTYGRPNAME)) ? gr->gr_gid : pwd->pw_gid);
D 116
	(void)chmod(ttyn, 0620);
E 116
	(void)setgid(pwd->pw_gid);

	initgroups(username, pwd->pw_gid);
D 98

E 67
I 24
	quota(Q_DOWARN, pwd->pw_uid, (dev_t)-1, 0);
E 98
E 24
E 19
E 17
E 13
D 67
	setuid(pwd->pw_uid);
E 67
I 67
D 84
	(void)setuid(pwd->pw_uid);
E 84
E 67
I 59

I 68
	if (*pwd->pw_shell == '\0')
D 80
		pwd->pw_shell = BSHELL;
E 80
I 80
		pwd->pw_shell = _PATH_BSHELL;
E 80
D 89
	/* turn on new line discipline for the csh */
D 81
	else if (!strcmp(pwd->pw_shell, "/bin/csh")) {
E 81
I 81
	else if (!strcmp(pwd->pw_shell, _PATH_CSHELL)) {
E 81
		ioctlval = NTTYDISC;
		(void)ioctl(0, TIOCSETD, &ioctlval);
	}
E 89

E 68
E 59
D 10
	if (*pwd->pw_shell == '\0')
		pwd->pw_shell = "/bin/sh";
E 10
D 39
	environ = envinit;
	strncat(homedir, pwd->pw_dir, sizeof(homedir)-6);
	strncat(shell, pwd->pw_shell, sizeof(shell)-7);
D 12
	strncat(term, stypeof(ttyn), sizeof(term)-6);
E 12
I 12
D 15
	if (rflag == 0)
E 15
I 15
D 38
	if (term[strlen("TERM=")] == 0)
E 38
I 38
	if (term[sizeof("TERM=")-1] == 0)
E 38
E 15
D 36
		strncat(term, stypeof(ttyn), sizeof(term)-6);
E 36
I 36
		strncat(term, stypeof(tty), sizeof(term)-6);
E 36
E 12
I 10
	strncat(user, pwd->pw_name, sizeof(user)-6);
E 39
I 39
D 67
	/* destroy environment unless user has asked to preserve it */
E 67
I 67
D 125
	/* destroy environment unless user has requested preservation */
E 125
I 125
	/* Destroy environment unless user has requested its preservation. */
E 125
E 67
	if (!pflag)
		environ = envinit;
D 59

	/* set up environment, this time without destruction */
	/* copy the environment before setenving */
	i = 0;
	while (environ[i] != NULL)
		i++;
	envnew = (char **) malloc(sizeof (char *) * (i + 1));
	for (; i >= 0; i--)
		envnew[i] = environ[i];
	environ = envnew;

D 47
	setenv("HOME=", pwd->pw_dir);
	setenv("SHELL=", pwd->pw_shell);
E 47
I 47
	setenv("HOME=", pwd->pw_dir, 1);
	setenv("SHELL=", pwd->pw_shell, 1);
E 59
I 59
D 68
	setenv("HOME", pwd->pw_dir, 1);
	setenv("SHELL", pwd->pw_shell, 1);
E 68
I 68
	(void)setenv("HOME", pwd->pw_dir, 1);
	(void)setenv("SHELL", pwd->pw_shell, 1);
E 68
E 59
E 47
	if (term[0] == '\0')
D 70
		strncpy(term, stypeof(tty), sizeof(term));
E 70
I 70
D 74
		strncpy(term, stypeof(), sizeof(term));
E 74
I 74
D 126
		strncpy(term, stypeof(tty), sizeof(term));
E 126
I 126
		(void)strncpy(term, stypeof(tty), sizeof(term));
E 126
E 74
E 70
D 47
	setenv("TERM=", term);
	setenv("USER=", pwd->pw_name);
	setenv("PATH=", ":/usr/ucb:/bin:/usr/bin");
E 47
I 47
D 59
	setenv("TERM=", term, 0);
	setenv("USER=", pwd->pw_name, 1);
	setenv("PATH=", ":/usr/ucb:/bin:/usr/bin", 0);
E 59
I 59
D 68
	setenv("TERM", term, 0);
	setenv("USER", pwd->pw_name, 1);
	setenv("PATH", ":/usr/ucb:/bin:/usr/bin", 0);
E 68
I 68
	(void)setenv("TERM", term, 0);
I 120
	(void)setenv("LOGNAME", pwd->pw_name, 1);
E 120
	(void)setenv("USER", pwd->pw_name, 1);
D 85
	(void)setenv("PATH", "/usr/ucb:/bin:/usr/bin:", 0);
E 85
I 85
	(void)setenv("PATH", _PATH_DEFPATH, 0);
I 118
#ifdef KERBEROS
	if (krbtkfile_env)
		(void)setenv("KRBTKFILE", krbtkfile_env, 1);
#endif
E 118
E 85
E 68
E 59
E 47

E 39
E 10
D 67
	if ((namep = rindex(pwd->pw_shell, '/')) == NULL)
		namep = pwd->pw_shell;
	else
		namep++;
	strcat(minusnam, namep);
E 67
D 25
	alarm(0);
E 25
D 9
	umask(022);
E 9
I 9
D 14
#ifdef ARPAVAX
D 10
	if (pwd->pw_gid == 31)
E 10
I 10
	if (pwd->pw_gid == 27)			/* UGLY ! */
E 10
		umask(2);
	else
D 10
#else
		umask(022);
E 10
#endif
E 9
D 10
	showmotd();
	strcat(maildir, pwd->pw_name);
	if(access(maildir,4)==0) {
		struct stat statb;
		stat(maildir, &statb);
		if (statb.st_size)
			printf("You have mail.\n");
E 10
I 10
		umask(022);
E 14
I 14
D 36
	umask(022);
E 14
D 15
	if (ttyn[sizeof("/dev/tty")-1] == 'd') {
		FILE *console = fopen("/dev/console", "w");
		if (console != NULL) {
			fprintf(console, "\r\nDIALUP %s %s\r\n"
			    , ttyn+sizeof("/dev/")-1
			    , pwd->pw_name
			);
			fclose(console);
		}
E 10
	}
I 10
	if ( !quietlog ) {
E 15
I 15
	if (ttyn[sizeof("/dev/tty")-1] == 'd')
D 32
		logerr("DIALUP %s %s\n", ttyn+sizeof("/dev/")-1, pwd->pw_name);
E 32
I 32
		logerr("DIALUP %s %s",
		    ttyn+sizeof("/dev/")-1, pwd->pw_name);
E 36
I 36
	if (tty[sizeof("tty")-1] == 'd')
D 39
		syslog(LOG_INFO, "DIALUP %s %s", tty, pwd->pw_name);
E 39
I 39
		syslog(LOG_INFO, "DIALUP %s, %s", tty, pwd->pw_name);
D 107
	if (pwd->pw_uid == 0)
E 107
I 107
D 125
	/* if fflag is on, assume caller/authenticator has logged root login */
E 125
I 125

	/* If fflag is on, assume caller/authenticator has logged root login. */
E 125
D 115
	if (pwd->pw_uid == 0 && fflag == 0)
E 115
I 115
D 118
	if (ROOTLOGIN && fflag == 0)
E 118
I 118
	if (rootlogin && fflag == 0)
E 118
E 115
E 107
D 45
		syslog(LOG_SECURITY, "ROOT LOGIN %s", tty);
E 45
I 45
D 50
		syslog(LOG_NOTICE, "ROOT LOGIN %s", tty);
E 50
I 50
D 67
		if (utmp.ut_host[0])
E 67
I 67
		if (hostname)
E 67
D 70
			syslog(LOG_NOTICE, "ROOT LOGIN %s FROM %.*s",
D 67
			    tty, HMAX, utmp.ut_host);
E 67
I 67
			    tty, UT_HOSTSIZE, hostname);
E 70
I 70
D 74
			syslog(LOG_NOTICE, "ROOT LOGIN %s FROM %s",
E 74
I 74
D 115
			syslog(LOG_NOTICE, "ROOT LOGIN ON %s FROM %s",
E 74
			    tty, hostname);
E 115
I 115
			syslog(LOG_NOTICE, "ROOT LOGIN (%s) ON %s FROM %s",
			    username, tty, hostname);
E 115
E 70
E 67
		else
D 74
			syslog(LOG_NOTICE, "ROOT LOGIN %s", tty);
E 74
I 74
D 115
			syslog(LOG_NOTICE, "ROOT LOGIN ON %s", tty);
E 115
I 115
			syslog(LOG_NOTICE, "ROOT LOGIN (%s) ON %s", username, tty);
E 115
E 74
I 67

I 102
#ifdef KERBEROS
	if (!quietlog && notickets == 1)
		(void)printf("Warning: no Kerberos tickets issued.\n");
#endif

E 102
E 67
E 50
E 45
E 39
E 36
E 32
	if (!quietlog) {
I 38
D 125
		struct stat st;
I 39

I 114
		printf(
E 125
I 125
D 127
		(void)printf(
E 125
"Copyright (c) 1980,1983,1986,1988,1990,1991 The Regents of the University\n%s",
"of California.  All rights reserved.\n\n");
E 127
I 127
		(void)printf("%s\n\t%s  %s\n\n",
D 129
		    "Copyright (c) 1980, 1983, 1986, 1988, 1990, 1991, 1993",
E 129
I 129
	    "Copyright (c) 1980, 1983, 1986, 1988, 1990, 1991, 1993, 1994",
E 129
		    "The Regents of the University of California. ",
		    "All rights reserved.");
E 127
E 114
E 39
E 38
E 15
D 67
		showmotd();
		strcat(maildir, pwd->pw_name);
D 36
		if (access(maildir,4)==0) {
E 36
I 36
D 38
		if (access(maildir, R_OK) == 0) {
E 36
			struct stat statb;
			stat(maildir, &statb);
			if (statb.st_size)
				printf("You have mail.\n");
		}
E 38
I 38
		if (stat(maildir, &st) == 0 && st.st_size != 0)
E 67
I 67
		motd();
D 80
		(void)sprintf(tbuf, "%s/%s", MAILDIR, pwd->pw_name);
E 80
I 80
D 125
		(void)sprintf(tbuf, "%s/%s", _PATH_MAILDIR, pwd->pw_name);
E 125
I 125
		(void)snprintf(tbuf,
		    sizeof(tbuf), "%s/%s", _PATH_MAILDIR, pwd->pw_name);
E 125
E 80
		if (stat(tbuf, &st) == 0 && st.st_size != 0)
E 67
D 84
			printf("You have %smail.\n",
E 84
I 84
			(void)printf("You have %smail.\n",
E 84
D 39
				(st.st_mtime > st.st_atime) ? "new" : "");
E 39
I 39
D 67
				(st.st_mtime > st.st_atime) ? "new " : "");
E 67
I 67
			    (st.st_mtime > st.st_atime) ? "new " : "");
E 67
E 39
E 38
	}
D 25
	
E 25
I 25
D 67
	signal(SIGALRM, SIG_DFL);
E 25
E 10
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
I 11
	signal(SIGTSTP, SIG_IGN);
E 11
	execlp(pwd->pw_shell, minusnam, 0);
E 67
I 67

	(void)signal(SIGALRM, SIG_DFL);
	(void)signal(SIGQUIT, SIG_DFL);
	(void)signal(SIGINT, SIG_DFL);
	(void)signal(SIGTSTP, SIG_IGN);

	tbuf[0] = '-';
D 125
	strcpy(tbuf + 1, (p = rindex(pwd->pw_shell, '/')) ?
E 125
I 125
D 130
	(void)strcpy(tbuf + 1, (p = rindex(pwd->pw_shell, '/')) ?
E 130
I 130
	(void)strcpy(tbuf + 1, (p = strrchr(pwd->pw_shell, '/')) ?
E 130
E 125
	    p + 1 : pwd->pw_shell);
I 86

I 90
D 91
#if	BSD > 43
E 91
E 90
D 95
	if (setlogname(pwd->pw_name, strlen(pwd->pw_name)) < 0)
		syslog(LOG_ERR, "setlogname() failure: %m");
E 95
I 95
	if (setlogin(pwd->pw_name) < 0)
		syslog(LOG_ERR, "setlogin() failure: %m");
E 95
I 90
D 91
#endif
E 91
E 90
E 86
I 84

D 124
	/* discard permissions last so can't get killed and drop core */
E 124
I 124
	/* Discard permissions last so can't get killed and drop core. */
E 124
D 115
	(void)setuid(pwd->pw_uid);
E 115
I 115
D 118
	if (ROOTLOGIN)
E 118
I 118
	if (rootlogin)
E 118
		(void) setuid(0);
	else
D 118
		(void)setuid(pwd->pw_uid);
E 118
I 118
		(void) setuid(pwd->pw_uid);
E 118
E 115

E 84
	execlp(pwd->pw_shell, tbuf, 0);
I 68
D 84
	fprintf(stderr, "login: no shell: ");
E 68
E 67
I 10
	perror(pwd->pw_shell);
E 84
I 84
D 121
	(void)fprintf(stderr, "login: no shell: %s.\n", strerror(errno));
E 84
E 10
D 67
	printf("No shell\n");
E 67
I 67
D 68
	fprintf(stderr, "login: no shell\n");
E 68
E 67
	exit(0);
E 121
I 121
D 130
	(void)fprintf(stderr, "%s: %s\n", pwd->pw_shell, strerror(errno));
	exit(1);
E 130
I 130
	err(1, "%s", pwd->pw_shell);
E 130
E 121
}

I 115
#ifdef	KERBEROS
D 125
#define	NBUFSIZ		(UT_NAMESIZE + 1 + 5) /* .root suffix */
E 125
I 125
#define	NBUFSIZ		(UT_NAMESIZE + 1 + 5)	/* .root suffix */
E 125
#else
#define	NBUFSIZ		(UT_NAMESIZE + 1)
#endif

I 125
void
E 125
E 115
I 25
D 67
getloginname(up)
	register struct utmp *up;
E 67
I 67
getloginname()
E 67
{
D 67
	register char *namep;
D 27
	char hostname[32], c;
E 27
I 27
	char c;
E 67
I 67
D 130
	register int ch;
D 115
	register char *p;
	static char nbuf[UT_NAMESIZE + 1];
E 115
I 115
D 118
	register char *p, *instance;
E 118
I 118
	register char *p;
E 130
I 130
	int ch;
	char *p;
E 130
E 118
	static char nbuf[NBUFSIZ];
E 115
E 67
E 27

D 27
	gethostname(hostname, sizeof (hostname));
E 27
D 67
	while (up->ut_name[0] == '\0') {
D 35
		namep = utmp.ut_name;
E 35
I 35
		namep = up->ut_name;
E 67
I 67
	for (;;) {
D 68
		p = nbuf;
E 68
E 67
E 35
D 27
		printf("%s login: ", hostname);
E 27
I 27
D 84
		printf("login: ");
E 84
I 84
		(void)printf("login: ");
E 84
E 27
D 67
		while ((c = getchar()) != '\n') {
			if (c == ' ')
				c = '_';
			if (c == EOF)
E 67
I 67
D 68
		while ((ch = getchar()) != '\n') {
			if (ch == ' ')
				ch = '_';
E 68
I 68
		for (p = nbuf; (ch = getchar()) != '\n'; ) {
E 68
D 70
			if (ch == EOF)
E 70
I 70
			if (ch == EOF) {
				badlogin(username);
E 70
E 67
				exit(0);
I 70
			}
E 70
D 67
			if (namep < up->ut_name+NMAX)
				*namep++ = c;
E 67
I 67
D 68
			if (p < nbuf+UT_NAMESIZE)
E 68
I 68
D 115
			if (p < nbuf + UT_NAMESIZE)
E 115
I 115
			if (p < nbuf + (NBUFSIZ - 1))
E 115
E 68
				*p++ = ch;
E 67
		}
I 67
		if (p > nbuf)
			if (nbuf[0] == '-')
D 84
				fprintf(stderr,
E 84
I 84
				(void)fprintf(stderr,
E 84
				    "login names may not start with '-'.\n");
			else {
				*p = '\0';
				username = nbuf;
D 68
				return;
E 68
I 68
				break;
E 68
			}
E 67
	}
I 115
D 118
#ifdef	KERBEROS
	if ((instance = index(nbuf, '.')) != NULL) {
		if (strncmp(instance, ".root", 5) == 0) {
			rootlogin++;
		}
		*instance = '\0';
		if ((instance - nbuf) > UT_NAMESIZE)
			nbuf[UT_NAMESIZE] = '\0';
	} else
		rootlogin = 0;
#endif
E 118
E 115
I 35
D 67
	strncpy(lusername, up->ut_name, NMAX);
	lusername[NMAX] = 0;
E 35
D 36
	setpwent();
E 36
D 35
	if ((pwd = getpwnam(utmp.ut_name)) == NULL)
E 35
I 35
	if ((pwd = getpwnam(lusername)) == NULL)
E 35
		pwd = &nouser;
E 67
I 67
D 68
	/* NOTREACHED */
E 68
E 67
D 36
	endpwent();
E 36
}

I 102
D 125
void
E 102
timedout()
{
D 67

	printf("Login timed out after %d seconds\n", timeout);
E 67
I 67
D 84
	fprintf(stderr, "Login timed out after %d seconds\n", timeout);
E 84
I 84
	(void)fprintf(stderr, "Login timed out after %d seconds\n", timeout);
E 84
E 67
	exit(0);
}

E 125
I 125
int
E 125
E 25
D 67
int	stopmotd;
catch()
E 67
I 67
D 70
rootterm(tty)
	char *tty;
E 70
I 70
D 74
rootterm()
E 74
I 74
rootterm(ttyn)
	char *ttyn;
E 74
E 70
E 67
{
I 67
	struct ttyent *t;
E 67
I 16

E 16
D 67
	signal(SIGINT, SIG_IGN);
	stopmotd++;
E 67
I 67
D 74
	return((t = getttynam(tty)) && t->ty_status&TTY_SECURE);
E 74
I 74
D 125
	return((t = getttynam(ttyn)) && t->ty_status&TTY_SECURE);
E 125
I 125
D 130
	return((t = getttynam(ttyn)) && t->ty_status & TTY_SECURE);
E 130
I 130
	return ((t = getttynam(ttyn)) && t->ty_status & TTY_SECURE);
E 130
E 125
E 74
E 67
}

I 10
D 16
/*
 * return true if OK for root to login on this terminal
 */
E 16
D 67
rootterm(tty)
D 16
	char	*tty;
E 16
I 16
	char *tty;
E 67
I 67
D 68
int motdinterrupt;
E 68
I 68
jmp_buf motdinterrupt;

I 125
void
E 125
E 68
motd()
E 67
E 16
{
D 36
	register FILE *fd;
D 16
	char	buf[100];
E 16
I 16
	char buf[100];
E 36
I 36
D 67
	register struct ttyent *t;
E 67
I 67
D 68
	register int ch;
	FILE *fp;
E 68
I 68
D 130
	register int fd, nchars;
E 130
I 130
	int fd, nchars;
E 130
E 68
D 90
	int (*oldint)(), sigint();
E 90
I 90
	sig_t oldint;
D 113
	int sigint();
E 113
I 113
D 125
	void sigint();
E 125
E 113
E 90
I 68
	char tbuf[8192];
E 68
E 67
E 36
E 16

I 16
D 23
	if (rflag)
		return(1);
E 23
E 16
D 36
	if ((fd = fopen(securetty, "r")) == NULL)
		return(1);
	while (fgets(buf, sizeof buf, fd) != NULL) {
		buf[strlen(buf)-1] = '\0';
		if (strcmp(tty, buf) == 0) {
			fclose(fd);
			return(1);
		}
E 36
I 36
D 67
	if ((t = getttynam(tty)) != NULL) {
		if (t->ty_status & TTY_SECURE)
			return (1);
E 67
I 67
D 68
	if ((fp = fopen(MOTDFILE, "r")) == NULL)
E 68
I 68
D 80
	if ((fd = open(MOTDFILE, O_RDONLY, 0)) < 0)
E 80
I 80
	if ((fd = open(_PATH_MOTDFILE, O_RDONLY, 0)) < 0)
E 80
E 68
		return;
	oldint = signal(SIGINT, sigint);
D 68
	while ((ch = getc(fp)) != EOF && !motdinterrupt)
		(void)putchar(ch);
E 68
I 68
	if (setjmp(motdinterrupt) == 0)
		while ((nchars = read(fd, tbuf, sizeof(tbuf))) > 0)
			(void)write(fileno(stdout), tbuf, nchars);
E 68
	(void)signal(SIGINT, oldint);
D 68
	if (motdinterrupt)
		fpurge(fp);
	(void)fclose(fp);
E 68
I 68
	(void)close(fd);
E 68
}

I 125
/* ARGSUSED */
E 125
I 113
void
E 113
D 125
sigint()
E 125
I 125
sigint(signo)
	int signo;
E 125
{
I 130

E 130
D 68
	motdinterrupt = 1;
E 68
I 68
	longjmp(motdinterrupt, 1);
E 68
}

I 125
/* ARGSUSED */
void
timedout(signo)
	int signo;
{
I 130

E 130
	(void)fprintf(stderr, "Login timed out after %d seconds\n", timeout);
	exit(0);
}

void
E 125
checknologin()
{
D 130
	register int fd, nchars;
E 130
I 130
	int fd, nchars;
E 130
D 68
	char tbuf[1024];
E 68
I 68
	char tbuf[8192];
E 68

D 80
	if ((fd = open(NOLOGIN, O_RDONLY, 0)) >= 0) {
E 80
I 80
	if ((fd = open(_PATH_NOLOGIN, O_RDONLY, 0)) >= 0) {
E 80
		while ((nchars = read(fd, tbuf, sizeof(tbuf))) > 0)
			(void)write(fileno(stdout), tbuf, nchars);
		sleepexit(0);
E 67
E 36
	}
D 36
	fclose(fd);
	return(0);
E 36
I 36
D 67
	return (0);
E 67
E 36
}

I 125
void
E 125
E 10
D 67
showmotd()
E 67
I 67
D 70
dolastlog(quiet, tty)
E 70
I 70
dolastlog(quiet)
E 70
	int quiet;
D 70
	char *tty;
E 70
E 67
{
D 67
	FILE *mf;
	register c;
E 67
I 67
	struct lastlog ll;
	int fd;
I 79
	char *ctime();
E 79
I 78
D 125
	char *ctime();
E 125
E 78
E 67

D 67
	signal(SIGINT, catch);
D 10
	if((mf = fopen("/etc/motd","r")) != NULL) {
		while((c = getc(mf)) != EOF && stopmotd == 0)
E 10
I 10
D 36
	if ((mf = fopen("/etc/motd","r")) != NULL) {
E 36
I 36
	if ((mf = fopen("/etc/motd", "r")) != NULL) {
E 36
		while ((c = getc(mf)) != EOF && stopmotd == 0)
E 10
			putchar(c);
		fclose(mf);
E 67
I 67
D 80
	if ((fd = open(LASTLOG, O_RDWR, 0)) >= 0) {
E 80
I 80
	if ((fd = open(_PATH_LASTLOG, O_RDWR, 0)) >= 0) {
E 80
D 68
		(void)lseek(fd, (long)pwd->pw_uid * sizeof(ll), L_SET);
E 68
I 68
		(void)lseek(fd, (off_t)pwd->pw_uid * sizeof(ll), L_SET);
E 68
		if (!quiet) {
			if (read(fd, (char *)&ll, sizeof(ll)) == sizeof(ll) &&
			    ll.ll_time != 0) {
D 84
				printf("Last login: %.*s ",
E 84
I 84
				(void)printf("Last login: %.*s ",
E 84
				    24-5, (char *)ctime(&ll.ll_time));
				if (*ll.ll_host != '\0')
D 84
					printf("from %.*s\n",
E 84
I 84
					(void)printf("from %.*s\n",
E 84
D 126
					    sizeof(ll.ll_host), ll.ll_host);
E 126
I 126
					    (int)sizeof(ll.ll_host),
					    ll.ll_host);
E 126
				else
D 84
					printf("on %.*s\n",
E 84
I 84
					(void)printf("on %.*s\n",
E 84
D 126
					    sizeof(ll.ll_line), ll.ll_line);
E 126
I 126
					    (int)sizeof(ll.ll_line),
					    ll.ll_line);
E 126
			}
D 68
			(void)lseek(fd, (long)pwd->pw_uid * sizeof(ll), L_SET);
E 68
I 68
			(void)lseek(fd, (off_t)pwd->pw_uid * sizeof(ll), L_SET);
E 68
		}
I 74
D 102
		bzero((char *)&ll, sizeof(ll));
E 102
I 102
D 130
		bzero((void *)&ll, sizeof(ll));
E 130
I 130
		memset((void *)&ll, 0, sizeof(ll));
E 130
E 102
E 74
		(void)time(&ll.ll_time);
D 126
		strncpy(ll.ll_line, tty, sizeof(ll.ll_line));
E 126
I 126
		(void)strncpy(ll.ll_line, tty, sizeof(ll.ll_line));
E 126
I 72
		if (hostname)
D 126
			strncpy(ll.ll_host, hostname, sizeof(ll.ll_host));
E 126
I 126
			(void)strncpy(ll.ll_host, hostname, sizeof(ll.ll_host));
E 126
D 74
		else
			bzero(ll.ll_host, sizeof(ll.ll_host));
E 72
		strncpy(ll.ll_host, hostname, sizeof(ll.ll_host));
E 74
		(void)write(fd, (char *)&ll, sizeof(ll));
		(void)close(fd);
E 67
	}
D 67
	signal(SIGINT, SIG_IGN);
E 67
}

I 125
void
E 125
I 70
badlogin(name)
	char *name;
{
I 130

E 130
D 74
	if (!repeatcnt)
E 74
I 74
	if (failures == 0)
E 74
		return;
D 111
	if (hostname)
D 74
		syslog(LOG_ERR, "%d LOGIN FAILURE%s ON %s FROM %s, %s",
		    repeatcnt, repeatcnt > 1 ? "S" : "", tty, hostname, name);
E 74
I 74
		syslog(LOG_NOTICE, "%d LOGIN FAILURE%s FROM %s, %s",
E 111
I 111
	if (hostname) {
		syslog(LOG_NOTICE, "%d LOGIN FAILURE%s FROM %s",
		    failures, failures > 1 ? "S" : "", hostname);
		syslog(LOG_AUTHPRIV|LOG_NOTICE,
		    "%d LOGIN FAILURE%s FROM %s, %s",
E 111
		    failures, failures > 1 ? "S" : "", hostname, name);
E 74
D 111
	else
D 74
		syslog(LOG_ERR, "%d LOGIN FAILURE%s ON %s, %s",
		    repeatcnt, repeatcnt > 1 ? "S" : "", tty, name);
E 74
I 74
		syslog(LOG_NOTICE, "%d LOGIN FAILURE%s ON %s, %s",
E 111
I 111
	} else {
		syslog(LOG_NOTICE, "%d LOGIN FAILURE%s ON %s",
		    failures, failures > 1 ? "S" : "", tty);
		syslog(LOG_AUTHPRIV|LOG_NOTICE,
		    "%d LOGIN FAILURE%s ON %s, %s",
E 111
		    failures, failures > 1 ? "S" : "", tty, name);
I 111
	}
E 111
E 74
}

E 70
I 10
#undef	UNKNOWN
E 10
D 67
#define UNKNOWN "su"
E 67
I 67
#define	UNKNOWN	"su"
E 67

char *
D 70
stypeof(ttyid)
D 25
char	*ttyid;
E 25
I 25
	char *ttyid;
E 70
I 70
D 74
stypeof()
E 74
I 74
stypeof(ttyid)
	char *ttyid;
E 74
E 70
E 25
{
D 25
	static char	typebuf[16];
	char		buf[50];
	register FILE	*f;
	register char	*p, *t, *q;
E 25
I 25
D 36
	static char typebuf[16];
	char buf[50];
	register FILE *f;
	register char *p, *t, *q;
E 36
I 36
D 67
	register struct ttyent *t;
E 67
I 67
	struct ttyent *t;
E 67
E 36
E 25

D 36
	if (ttyid == NULL)
E 36
I 36
D 67
	if (ttyid == NULL || (t = getttynam(ttyid)) == NULL)
E 36
		return (UNKNOWN);
D 36
	f = fopen("/etc/ttytype", "r");
	if (f == NULL)
		return (UNKNOWN);
	/* split off end of name */
	for (p = q = ttyid; *p != 0; p++)
		if (*p == '/')
			q = p + 1;

	/* scan the file */
D 25
	while (fgets(buf, sizeof buf, f) != NULL)
	{
D 10
		for (t=buf; *t!=' '; t++)
E 10
I 10
		for (t=buf; *t!=' ' && *t != '\t'; t++)
E 25
I 25
	while (fgets(buf, sizeof buf, f) != NULL) {
		for (t = buf; *t != ' ' && *t != '\t'; t++)
E 25
E 10
			;
		*t++ = 0;
I 10
		while (*t == ' ' || *t == '\t')
			t++;
E 10
D 25
		for (p=t; *p>' '; p++)
E 25
I 25
		for (p = t; *p > ' '; p++)
E 25
			;
		*p = 0;
D 25
		if (strcmp(q,t)==0) {
E 25
I 25
		if (strcmp(q,t) == 0) {
E 25
			strcpy(typebuf, buf);
			fclose(f);
			return (typebuf);
		}
	}
	fclose (f);
	return (UNKNOWN);
E 36
I 36
	return (t->ty_type);
E 67
I 67
D 70
	return(ttyid && (t = getttynam(ttyid)) ? t->ty_type : UNKNOWN);
E 70
I 70
D 74
	return(tty && (t = getttynam(tty)) ? t->ty_type : UNKNOWN);
E 74
I 74
D 130
	return(ttyid && (t = getttynam(ttyid)) ? t->ty_type : UNKNOWN);
E 130
I 130
	return (ttyid && (t = getttynam(ttyid)) ? t->ty_type : UNKNOWN);
E 130
E 74
E 70
E 67
E 36
I 12
D 102
}

I 25
D 69
doremotelogin(host)
	char *host;
{
D 43
	FILE *hostf;
	int first = 1;

E 43
D 67
	getstr(rusername, sizeof (rusername), "remuser");
	getstr(lusername, sizeof (lusername), "locuser");
E 67
I 67
	static char lusername[UT_NAMESIZE+1];
	char rusername[UT_NAMESIZE+1];

	getstr(rusername, sizeof(rusername), "remuser");
	getstr(lusername, sizeof(lusername), "locuser");
E 67
D 39
	getstr(term+5, sizeof(term)-5, "Terminal type");
E 39
I 39
	getstr(term, sizeof(term), "Terminal type");
I 67
	username = lusername;
E 67
E 39
D 31
	if (getuid())
E 31
I 31
D 68
	if (getuid()) {
		pwd = &nouser;
E 31
D 43
		goto bad;
E 43
I 43
		return(-1);
E 43
I 31
	}
E 68
E 31
D 36
	setpwent();
E 36
D 67
	pwd = getpwnam(lusername);
E 67
I 67
	pwd = getpwnam(username);
E 67
D 36
	endpwent();
E 36
D 31
	if (pwd == NULL)
E 31
I 31
D 68
	if (pwd == NULL) {
		pwd = &nouser;
E 68
I 68
	if (pwd == NULL)
E 68
E 31
D 43
		goto bad;
E 43
I 43
		return(-1);
E 43
I 31
D 68
	}
E 68
E 31
D 43
	hostf = pwd->pw_uid ? fopen("/etc/hosts.equiv", "r") : 0;
again:
	if (hostf) {
		char ahost[32];

		while (fgets(ahost, sizeof (ahost), hostf)) {
I 39
			register char *p;
E 39
			char *user;

D 39
			if ((user = index(ahost, '\n')) != 0)
				*user++ = '\0';
			if ((user = index(ahost, ' ')) != 0)
				*user++ = '\0';
E 39
I 39
			p = ahost;
			while (*p != '\n' && *p != ' ' && *p != '\t' && *p != '\0')
				p++;
			if (*p == ' ' || *p == '\t') {
				*p++ = '\0';
				while (*p == ' ' || *p == '\t')
					p++;
				user = p;
				while (*p != '\n' && *p != ' ' && *p != '\t' && *p != '\0')
					p++;
			} else
				user = p;
			*p = '\0';
E 39
			if (!strcmp(host, ahost) &&
D 39
			    !strcmp(rusername, user ? user : lusername)) {
E 39
I 39
			    !strcmp(rusername, *user ? user : lusername)) {
E 39
				fclose(hostf);
				return (1);
			}
		}
		fclose(hostf);
	}
	if (first == 1) {
		char *rhosts = ".rhosts";
		struct stat sbuf;

		first = 0;
		if (chdir(pwd->pw_dir) < 0)
			goto again;
		if (lstat(rhosts, &sbuf) < 0)
			goto again;
		if ((sbuf.st_mode & S_IFMT) == S_IFLNK) {
			printf("login: .rhosts is a soft link.\r\n");
			goto bad;
		}
		hostf = fopen(rhosts, "r");
		fstat(fileno(hostf), &sbuf);
		if (sbuf.st_uid && sbuf.st_uid != pwd->pw_uid) {
			printf("login: Bad .rhosts ownership.\r\n");
			fclose(hostf);
			goto bad;
		}
		goto again;
	}
bad:
	return (-1);
E 43
I 43
D 67
	return(ruserok(host, (pwd->pw_uid == 0), rusername, lusername));
E 67
I 67
	return(ruserok(host, (pwd->pw_uid == 0), rusername, username));
E 67
E 43
}

E 69
E 25
getstr(buf, cnt, err)
D 67
	char *buf;
E 67
I 67
	char *buf, *err;
E 67
	int cnt;
D 67
	char *err;
E 67
{
D 67
	char c;
E 67
I 67
	char ch;
E 67

	do {
D 67
		if (read(0, &c, 1) != 1)
E 67
I 67
		if (read(0, &ch, sizeof(ch)) != sizeof(ch))
E 67
			exit(1);
		if (--cnt < 0) {
D 67
			printf("%s too long\r\n", err);
			exit(1);
E 67
I 67
D 84
			fprintf(stderr, "%s too long\r\n", err);
E 84
I 84
			(void)fprintf(stderr, "%s too long\r\n", err);
E 84
			sleepexit(1);
E 67
		}
D 67
		*buf++ = c;
	} while (c != 0);
E 67
I 67
		*buf++ = ch;
	} while (ch);
E 102
E 67
I 25
D 69
}

D 67
char	*speeds[] =
    { "0", "50", "75", "110", "134", "150", "200", "300",
      "600", "1200", "1800", "2400", "4800", "9600", "19200", "38400" };
#define	NSPEEDS	(sizeof (speeds) / sizeof (speeds[0]))
E 67
I 67
char *speeds[] = {
	"0", "50", "75", "110", "134", "150", "200", "300", "600",
	"1200", "1800", "2400", "4800", "9600", "19200", "38400",
};
#define	NSPEEDS	(sizeof(speeds) / sizeof(speeds[0]))
E 67

D 67
doremoteterm(term, tp)
	char *term;
E 67
I 67
doremoteterm(tp)
E 67
	struct sgttyb *tp;
{
D 39
	char *cp = index(term, '/');
	register int i;
E 39
I 39
	register char *cp = index(term, '/'), **cpp;
	char *speed;
D 44
	struct winsize ws;
E 44
E 39

	if (cp) {
D 39
		*cp++ = 0;
		for (i = 0; i < NSPEEDS; i++)
			if (!strcmp(speeds[i], cp)) {
				tp->sg_ispeed = tp->sg_ospeed = i;
E 39
I 39
		*cp++ = '\0';
		speed = cp;
		cp = index(speed, '/');
		if (cp)
			*cp++ = '\0';
		for (cpp = speeds; cpp < &speeds[NSPEEDS]; cpp++)
			if (strcmp(*cpp, speed) == 0) {
				tp->sg_ispeed = tp->sg_ospeed = cpp-speeds;
E 39
				break;
			}
I 39
D 44
		ws.ws_row = ws.ws_col = -1;
		ws.ws_xpixel = ws.ws_ypixel = -1;
		if (cp) {
D 40
			ws.ws_row = atoi(++cp);
E 40
I 40
			ws.ws_row = atoi(cp);
E 40
			cp = index(cp, ',');
			if (cp == 0)
				goto done;
			ws.ws_col = atoi(++cp);
			cp = index(cp, ',');
			if (cp == 0)
				goto done;
			ws.ws_xpixel = atoi(++cp);
			cp = index(cp, ',');
			if (cp == 0)
				goto done;
			ws.ws_ypixel = atoi(++cp);
		}
done:
		if (ws.ws_row != -1 && ws.ws_col != -1 &&
		    ws.ws_xpixel != -1 && ws.ws_ypixel != -1)
			win = ws;
E 44
I 44
D 52
		compatsiz(cp);
E 52
E 44
E 39
	}
	tp->sg_flags = ECHO|CRMOD|ANYP|XTABS;
E 69
I 39
D 59
}
I 44
D 52

/* BEGIN TRASH
 *
 * This is here only long enough to get us by to the revised rlogin
 */
compatsiz(cp)
	char *cp;
{
	struct winsize ws;

	ws.ws_row = ws.ws_col = -1;
	ws.ws_xpixel = ws.ws_ypixel = -1;
	if (cp) {
		ws.ws_row = atoi(cp);
		cp = index(cp, ',');
		if (cp == 0)
			goto done;
		ws.ws_col = atoi(++cp);
		cp = index(cp, ',');
		if (cp == 0)
			goto done;
		ws.ws_xpixel = atoi(++cp);
		cp = index(cp, ',');
		if (cp == 0)
			goto done;
		ws.ws_ypixel = atoi(++cp);
	}
done:
	if (ws.ws_row != -1 && ws.ws_col != -1 &&
	    ws.ws_xpixel != -1 && ws.ws_ypixel != -1)
		ioctl(0, TIOCSWINSZ, &ws);
}
/* END TRASH */
E 52
E 44

/*
 * Set the value of var to be arg in the Unix 4.2 BSD environment env.
 * Var should end with '='.
 * (bindings are of the form "var=value")
 * This procedure assumes the memory for the first level of environ
 * was allocated using malloc.
 */
D 47
setenv(var, value)
E 47
I 47
setenv(var, value, clobber)
E 47
	char *var, *value;
{
	extern char **environ;
	int index = 0;
	int varlen = strlen(var);
	int vallen = strlen(value);

	for (index = 0; environ[index] != NULL; index++) {
		if (strncmp(environ[index], var, varlen) == 0) {
			/* found it */
I 47
			if (!clobber)
				return;
E 47
			environ[index] = malloc(varlen + vallen + 1);
			strcpy(environ[index], var);
			strcat(environ[index], value);
			return;
		}
	}
	environ = (char **) realloc(environ, sizeof (char *) * (index + 2));
	if (environ == NULL) {
		fprintf(stderr, "login: malloc out of memory\n");
		exit(1);
	}
	environ[index] = malloc(varlen + vallen + 1);
	strcpy(environ[index], var);
	strcat(environ[index], value);
	environ[++index] = NULL;
E 59
I 54
}

I 125
void
E 125
D 55
write_gid()
E 55
I 55
D 57
write_gid(default_gid)
E 57
I 57
D 67
tty_gid(default_gid)
E 57
	int default_gid;
E 67
I 67
sleepexit(eval)
	int eval;
E 67
E 55
{
D 67
	struct group *getgrnam(), *gr;
D 55
	int gid = 0;
E 55
I 55
	int gid = default_gid;
E 55

D 57
	gr = getgrnam(WRITENAME);
E 57
I 57
	gr = getgrnam(TTYGRPNAME);
E 57
	if (gr != (struct group *) 0)
		gid = gr->gr_gid;

	endgrent();

D 55
	return gid;
E 55
I 55
	return (gid);
E 67
I 67
D 125
	sleep((u_int)5);
E 125
I 125
D 130
	(void)sleep((u_int)5);
E 130
I 130

	(void)sleep(5);
E 130
E 125
	exit(eval);
I 83
}

doremotelogin(host)
	char *host;
{
	static char lusername[UT_NAMESIZE+1];
	char rusername[UT_NAMESIZE+1];

	getstr(rusername, sizeof(rusername), "remuser");
	getstr(lusername, sizeof(lusername), "locuser");
	getstr(term, sizeof(term), "Terminal type");
	username = lusername;
	pwd = getpwnam(username);
	if (pwd == NULL)
		return(-1);
	return(ruserok(host, (pwd->pw_uid == 0), rusername, username));
}

char *speeds[] = {
	"0", "50", "75", "110", "134", "150", "200", "300", "600",
	"1200", "1800", "2400", "4800", "9600", "19200", "38400",
};
#define	NSPEEDS	(sizeof(speeds) / sizeof(speeds[0]))

doremoteterm(tp)
	struct sgttyb *tp;
{
	register char *cp = index(term, '/'), **cpp;
	char *speed;

	if (cp) {
		*cp++ = '\0';
		speed = cp;
		cp = index(speed, '/');
		if (cp)
			*cp++ = '\0';
		for (cpp = speeds; cpp < &speeds[NSPEEDS]; cpp++)
			if (strcmp(*cpp, speed) == 0) {
				tp->sg_ispeed = tp->sg_ospeed = cpp-speeds;
				break;
			}
	}
	tp->sg_flags = ECHO|CRMOD|ANYP|XTABS;
E 83
E 67
E 55
E 54
E 39
E 25
I 15
D 36
}

logerr(fmt, a1, a2, a3)
	char *fmt, *a1, *a2, *a3;
{
I 26
#ifdef LOGERR
	FILE *cons = fopen("/dev/console", "w");
E 26

I 26
	if (cons != NULL) {
		fprintf(cons, fmt, a1, a2, a3);
D 32
		fputc('\r', cons);
E 32
I 32
		fprintf(cons, "\n\r");
E 32
		fclose(cons);
	}
#endif
E 36
E 26
E 15
E 12
}
E 1
