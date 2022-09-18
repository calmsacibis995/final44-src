h07348
s 00002/00002/00014
d D 8.1 93/06/06 15:08:21 bostic 27 26
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00016
d D 5.16 92/12/17 12:05:05 bostic 26 25
c mail doesn't need to log who sends mail, does it?
e
s 00000/00000/00017
d D 5.15 92/06/26 12:03:22 bostic 25 24
c quad's broke it -- prototyped it rather than figure out the problem
e
s 00003/00003/00014
d D 5.14 91/06/19 15:07:58 bostic 24 23
c rename Mail.{rc,tildehelp,help} -> mail.{rc,tildehelp,help}
c move mail.rc from /usr/share/misc to /etc
e
s 00000/00001/00017
d D 5.13 90/06/24 23:35:42 bostic 23 22
c move _PATH_MAILDIR into <paths.h>
e
s 00001/00011/00017
d D 5.12 90/06/01 16:59:46 bostic 22 21
c new copyright notice
e
s 00002/00002/00026
d D 5.11 89/07/28 12:44:22 karels 21 20
c /var/spool/mail -> /var/mail
e
s 00000/00001/00028
d D 5.10 89/06/04 10:00:09 bostic 20 19
c sendmail -> paths.h
e
s 00001/00001/00028
d D 5.9 89/05/19 18:49:03 bostic 19 18
c sendmail moved
e
s 00001/00001/00028
d D 5.8 89/05/19 18:12:54 bostic 18 17
c /usr/adm -> /var/log
e
s 00010/00020/00019
d D 5.7 89/05/11 09:44:18 bostic 17 16
c file reorg, pathnames.h, paths.h
e
s 00010/00005/00029
d D 5.6 88/06/29 21:02:14 bostic 16 15
c install approved copyright notice
e
s 00001/00011/00033
d D 5.5 88/06/16 17:41:07 edward 15 14
c prehistoric (e.g., pre-sendmail) code removed
e
s 00008/00002/00036
d D 5.4 88/02/18 17:04:32 bostic 14 13
c written by Kurt Shoens; added Berkeley specific header
e
s 00000/00005/00038
d D 5.3 87/05/18 12:28:34 edward 13 12
c major rework: made faster, cleaned up, obsolete code removed,
c the whole thing should be chucked and written from scratch
e
s 00001/00001/00042
d D 5.2 85/09/19 00:32:51 lepreau 12 11
c Mail.help.~ renamed to avoid deletion by find's for CCA emacs chkpoint files.
e
s 00007/00001/00036
d D 5.1 85/06/06 10:48:51 dist 11 10
c Add copyright
e
s 00002/00004/00035
d D 2.6 83/08/11 22:20:32 sam 10 9
c standardize sccs keyword lines
e
s 00001/00001/00038
d D 2.5 83/01/29 19:51:25 leres 9 7
c Changed location of postage file
e
s 00000/00000/00039
d R 2.5 83/01/29 19:49:40 leres 8 7
c Changed location of the POSTAGE file.
e
s 00001/00001/00038
d D 2.4 82/12/26 21:16:23 eric 7 6
c change delivermail to sendmail throughout
e
s 00007/00001/00032
d D 2.3 82/09/02 12:36:36 mckusick 6 5
c added #define of GETHOST for systems that have gethostname();
c changed determination of local machine id to EMPTYID ifdef GETHOST
e
s 00006/00000/00027
d D 2.2 82/07/26 17:13:52 kurt 5 4
c Parameterized location of postage meter file as POSTAGE; 
c added include on sigretro.h if we're not a VMUNIX site. 
c 
e
s 00000/00000/00027
d D 2.1 81/07/01 11:11:35 kurt 4 3
c Release to Heidi Stettner
e
s 00001/00001/00026
d D 1.3 81/04/01 10:55:54 kurt 3 2
c changed local machine to ingvax.
e
s 00001/00000/00026
d D 1.2 80/10/10 12:01:15 kas 2 1
c Added define constant MORE == path of the more program
e
s 00026/00000/00000
d D 1.1 80/10/08 09:53:57 kas 1 0
c date and time created 80/10/08 09:53:57 by kas
e
u
U
f b 
t
T
I 10
D 11
/*	%M%	%I%	%E%	*/
E 11
I 11
/*
D 21
 * Copyright (c) 1980 Regents of the University of California.
E 21
I 21
D 27
 * Copyright (c) 1989 Regents of the University of California.
E 21
D 14
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 14
I 14
 * All rights reserved.
E 27
I 27
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 27
 *
D 22
 * Redistribution and use in source and binary forms are permitted
D 16
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 16
I 16
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
D 17
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 17
I 17
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 22
I 22
 * %sccs.include.redist.c%
E 22
E 17
E 16
E 14
 *
 *	%W% (Berkeley) %G%
 */
E 11

E 10
I 1
D 17
/*
 * Declarations and constants specific to an installation.
 *
 * Vax/Unix version 7.
D 10
 */
 
/*
 * Sccs Id = "%W% %G%";
E 10
 */
E 17
I 17
#include <paths.h>
E 17

D 3
#define	LOCAL		'v'		/* Local machine id */
E 3
I 3
D 6
#define	LOCAL		'j'		/* Local machine id */
E 6
I 6
D 15
#define	GETHOST				/* System has gethostname syscall */
#ifdef	GETHOST
#define	LOCAL		EMPTYID		/* Dynamically determined local host */
#else
#define	LOCAL		'j'		/* Local host id */
#endif	GETHOST

E 6
E 3
#define	MAIL		"/bin/mail"	/* Name of mail sender */
E 15
D 7
#define DELIVERMAIL	"/etc/delivermail"
E 7
I 7
D 17
#define SENDMAIL	"/usr/lib/sendmail"
E 7
					/* Name of classy mail deliverer */
#define	EDITOR		"/usr/ucb/ex"	/* Name of text editor */
#define	VISUAL		"/usr/ucb/vi"	/* Name of display editor */
#define	SHELL		"/bin/csh"	/* Standard shell */
I 2
#define	MORE		"/usr/ucb/more"	/* Standard output pager */
E 2
#define	HELPFILE	"/usr/lib/Mail.help"
					/* Name of casual help file */
D 12
#define	THELPFILE	"/usr/lib/Mail.help.~"
E 12
I 12
#define	THELPFILE	"/usr/lib/Mail.tildehelp"
I 15
					/* Name of casual tilde help */
E 15
E 12
I 5
D 9
#define	POSTAGE		"/arch/kurt/postage"
E 9
I 9
#define	POSTAGE		"/usr/adm/maillog"
E 9
					/* Where to audit mail sending */
E 5
D 15
					/* Name of casual tilde help */
E 15
D 13
#define	UIDMASK		0177777		/* Significant uid bits */
E 13
#define	MASTER		"/usr/lib/Mail.rc"
#define	APPEND				/* New mail goes to end of mailbox */
E 17
I 17
#define	_PATH_EX	"/usr/bin/ex"
D 24
#define	_PATH_HELP	"/usr/share/misc/Mail.help"
#define	_PATH_TILDE	"/usr/share/misc/Mail.tildehelp"
E 24
I 24
#define	_PATH_HELP	"/usr/share/misc/mail.help"
#define	_PATH_TILDE	"/usr/share/misc/mail.tildehelp"
E 24
D 18
#define	_PATH_MAIL_LOG	"/usr/adm/maillog"
E 18
I 18
D 26
#define	_PATH_MAIL_LOG	"/var/log/maillog"
E 26
E 18
D 24
#define	_PATH_MASTER_RC	"/usr/share/misc/Mail.rc"
E 24
I 24
#define	_PATH_MASTER_RC	"/etc/mail.rc"
E 24
D 21
#define	_PATH_MBOX	"/var/spool/mail/"
E 21
I 21
D 23
#define	_PATH_MBOX	"/var/mail/"
E 23
E 21
#define	_PATH_MORE	"/usr/bin/more"
D 19
#define	_PATH_SENDMAIL	"/usr/libexec/sendmail"
E 19
I 19
D 20
#define	_PATH_SENDMAIL	"/usr/sbin/sendmail"
E 20
E 19
E 17
D 15
#define CANLOCK				/* Locking protocol actually works */
#define	UTIME				/* System implements utime(2) */
E 15
I 5
D 13

#ifndef VMUNIX
#include "sigretro.h"			/* Retrofit signal defs */
#endif VMUNIX
E 13
E 5
E 1
