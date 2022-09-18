h03180
s 00002/00002/00476
d D 8.4 94/04/02 10:01:23 pendry 97 96
c add 1994 copyright
e
s 00022/00016/00456
d D 8.3 94/04/02 09:59:57 pendry 96 94
c prettyness police
e
s 00022/00016/00456
d R 8.3 94/04/02 09:58:35 pendry 95 94
c prettyness police
e
s 00002/00002/00470
d D 8.2 93/09/23 19:08:48 bostic 94 93
c changes for 4.4BSD-Lite requested by USL
e
s 00005/00005/00467
d D 8.1 93/05/31 15:05:55 bostic 93 92
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00028/00055/00444
d D 5.51 93/04/29 13:18:12 bostic 92 91
c use err/warn from C library; lots of minor cleanup, lint
e
s 00001/00002/00498
d D 5.50 93/04/28 14:17:41 bostic 91 90
c delete trs from -v format, it's not available in the new VM
e
s 00005/00005/00495
d D 5.49 93/03/31 16:04:31 mckusick 90 89
c convert kinfo to sysctl
e
s 00000/00001/00500
d D 5.48 92/07/02 21:35:12 torek 89 88
c err must not be static, it is used in keyword.c and print.c
e
s 00039/00038/00462
d D 5.47 92/06/05 18:56:55 bostic 88 87
c ANSI prototypes (two real bugs)
e
s 00005/00003/00495
d D 5.46 92/05/12 15:44:50 marc 87 86
c -w weirdness fixed
e
s 00070/00044/00428
d D 5.45 92/04/03 14:55:42 mckusick 86 85
c update from Steve McCanne for Sun compatible kvm
e
s 00007/00000/00465
d D 5.44 92/01/27 12:24:18 bostic 85 84
c don't let users create their own symbol table for the running kernel
e
s 00003/00002/00462
d D 5.43 91/07/01 17:54:25 marc 84 83
c don't alloacte user structure if it can't be had
e
s 00005/00000/00459
d D 5.42 91/06/03 17:26:25 bostic 83 81
c the format string gets modified by parsefmt -- don't use it twice
e
s 00008/00008/00451
d R 5.42 91/06/03 17:19:23 bostic 82 81
c formats can be text space, have to copy them anyway
c vtail doesn't need to be global
e
s 00035/00036/00424
d D 5.41 91/06/03 16:55:41 bostic 81 80
c fix err routine, make everyone use it; minor ANSI cleanups
e
s 00024/00009/00436
d D 5.40 91/04/23 19:08:38 bostic 80 79
c add -M, -N, -W for consistency with other stat programs
e
s 00002/00002/00443
d D 5.39 91/04/08 14:49:14 bostic 79 78
c keywords got lost somewhere
e
s 00010/00008/00435
d D 5.38 91/03/27 15:49:38 marc 78 77
c its \not/ an error to specify a keyword twice
e
s 00015/00000/00428
d D 5.37 91/03/27 15:04:09 karels 77 76
c new vm
e
s 00015/00015/00413
d D 5.36 91/02/25 08:33:13 bostic 76 75
c strings may no longer be writable (thanks, ANSI!)
e
s 00001/00001/00427
d D 5.35 91/02/12 16:08:04 bostic 75 74
c forgot to remove 's' from getopt call
e
s 00002/00007/00426
d D 5.34 91/02/12 16:05:59 bostic 74 73
c delete "rusage" alias; delete -s option; change "trs" to "trss"
c two bugs: sortby needed to be initalized, typo in an error message
e
s 00001/00001/00432
d D 5.33 91/02/08 18:02:03 bostic 73 72
c drop "tt" keyword from -v output so fits on 80 column screen
e
s 00007/00007/00426
d D 5.32 91/02/08 17:50:58 bostic 72 71
c don't use aliases in descriptions, make -O same order as default
e
s 00150/00941/00283
d D 5.31 91/02/08 11:16:57 bostic 71 70
c Put print/keyword routines into separate modules; delete attime.c, use
c strftime(3) instead; put combination keywords into main keyword list,
c sort, delete aliases, and use bsearch(3); don't fail if nlist fails or
c devices aren't found.  Whack the manual page for consistency, correctness.
e
s 00003/00009/01221
d D 5.30 91/02/07 10:44:53 marc 70 69
c remove umask
e
s 00203/00243/01027
d D 5.29 90/08/30 11:54:58 marc 69 68
c fixes from chris
e
s 00000/00002/01270
d D 5.28 90/06/26 10:54:51 marc 68 67
c fix botch
e
s 00026/00028/01243
d D 5.27 90/06/26 10:49:55 marc 67 66
c new copyright, remove cursig, "s" state means session leader,
c EPROC_CTTY set in eproc if ctty vnode active, other minor fixups
e
s 00003/00002/01269
d D 5.26 90/06/06 10:03:12 bostic 66 65
c HP300 fixes from Mike Hibler
e
s 00024/00007/01247
d D 5.25 90/05/04 15:31:59 marc 65 64
c display cputime to two decimal places; provide dummy -g flag
e
s 00002/00001/01252
d D 5.24 90/04/20 12:50:05 marc 64 63
c kinfo now returns tty even for procs w/no ctty -- have to check
c SCTTY flag w/o -x option
e
s 00003/00003/01250
d D 5.23 90/04/18 13:31:30 marc 63 62
c use value S_IFCHR or S_IFBLK for specifying type of device
e
s 00044/00041/01209
d D 5.22 90/04/18 13:29:42 marc 62 61
c alter some names, remove flags on-l, add more symbolic flags for STAT
e
s 00990/01563/00260
d D 5.21 90/04/02 18:24:23 marc 61 60
c new version
e
s 00090/00022/01733
d D 5.20 90/03/01 17:36:57 marc 60 59
c checkpoint before trashing this version
e
s 00072/00052/01683
d D 5.19 89/11/20 23:46:30 mckusick 59 58
c get rid of unused nlist name; inode => vnode; reorder nlist entries
e
s 00011/00004/01724
d D 5.18 89/05/29 14:54:25 mckusick 58 57
c eliminate floating point from the kernel (from forys@cs.utah.edu)
e
s 00020/00016/01708
d D 5.17 89/05/29 14:24:25 bostic 57 56
c file reorg, pathnames.h paths.h
e
s 00002/00002/01722
d D 5.16 89/05/29 14:20:20 marc 56 55
c minor fix in output format
e
s 00006/00006/01718
d D 5.15 88/04/13 22:33:32 karels 55 54
c try again (better format for times >99:59)
e
s 00011/00010/01713
d D 5.14 88/03/10 19:16:05 karels 54 52
c sigh, I give up making this fit on a line (need to squish flags)
e
s 00004/00004/01719
d R 5.14 88/03/10 17:31:10 karels 53 52
c "pagedaemon" is too long now
e
s 00003/00002/01720
d D 5.13 88/03/10 17:23:50 karels 52 50
c oops, don't keep state from previous process
e
s 00001/00000/01722
d R 5.13 88/03/10 17:17:45 karels 51 50
c oops, don't keep the last proc's state
e
s 00035/00030/01687
d D 5.12 88/03/10 17:02:41 karels 50 49
c leave spaces between fields, enough space for large processes
e
s 00002/00002/01715
d D 5.11 87/10/22 09:54:49 bostic 49 48
c ANSI C; sprintf now returns an int.
e
s 00003/00003/01714
d D 5.10 87/03/28 17:49:05 karels 48 47
c make -k work on tahoe
e
s 00001/00001/01716
d D 5.9 86/05/08 12:48:28 karels 47 46
c rename nch => namecache (hopefully never used!)
e
s 00005/00005/01712
d D 5.8 86/04/26 07:29:23 lepreau 46 45
c give LIM field 1 more space
e
s 00000/00000/01717
d D 5.7 86/04/20 12:46:51 mckusick 45 43
i 44
c merge of 5.4.1.1
e
s 00039/00004/01678
d D 5.4.1.1 86/04/20 12:44:39 mckusick 44 41
c move verification to front of database to prevent looping 
c (from Peter Ford via lepreau@utah-cs.arpa)
e
s 00001/00001/01681
d D 5.6 86/02/07 10:40:42 bloom 43 42
c use stdout instead of stdin for sizing window
e
s 00002/00002/01680
d D 5.5 86/01/10 03:50:27 lepreau 42 41
c make specifying just proc 0 work
e
s 00031/00086/01651
d D 5.4 85/09/07 19:48:26 bloom 41 39
c use ls style uid/name hash (from serge@arpa), delete purdue RCS log
e
s 00031/00086/01651
d R 5.4 85/09/07 18:53:59 bloom 40 39
c use ls style name hashing, remove purdue rcs logs
e
s 00408/00032/01329
d D 5.3 85/08/28 18:04:31 mckusick 39 38
c symbolic wchan's (from Charles LaBrec; crl@newton.purdue.edu)
e
s 00055/00018/01306
d D 5.2 85/07/31 19:28:21 mckusick 38 37
c dynamic allocation of tty slots; save tty hash structure (from ks@purdue)
e
s 00014/00002/01310
d D 5.1 85/06/06 10:53:43 dist 37 36
c Add copyright
e
s 00013/00012/01299
d D 4.32 85/06/05 14:32:13 karels 36 35
c sundry fixes
e
s 00010/00004/01301
d D 4.31 85/02/25 09:23:33 karels 35 34
c minor cleanups: get disk names right, avoid pty masters
e
s 00013/00002/01292
d D 4.30 85/02/23 14:48:06 bloom 34 31
c get screen width ioctl added and hold passwd file open
e
s 00013/00002/01292
d R 4.30 85/02/20 08:55:01 bloom 33 31
c get screen width ioctl added and hold passwd file open
e
s 00001/00000/01294
d R 4.30 85/01/03 11:30:55 bloom 32 31
c tty.h requires ioctl.h
e
s 00003/00003/01291
d D 4.29 84/11/15 16:26:27 sam 31 30
c check in for bloom; update device lookup routine to skip current 
c block devices (had been checking only for oldies)
e
s 00002/00002/01292
d D 4.28 84/07/25 15:54:16 bloom 30 29
c add another digit to wchan, too many processes wait on higher addresses
e
s 00192/00086/01102
d D 4.27 84/03/21 14:56:45 ralph 29 28
c add -U flag to save static info & reduce startup time.
e
s 00001/00001/01187
d D 4.26 83/09/25 13:00:21 sam 28 27
c sbrk returns -1, not 0, on failure; from lepreau@utah-cs
e
s 00001/00001/01187
d D 4.25 83/09/22 11:45:37 ralph 27 26
c memory sizes are now computed correctly
e
s 00010/00003/01178
d D 4.24 83/05/22 17:29:45 sam 26 25
c size of proc structure changed for quotas
e
s 00068/00026/01113
d D 4.23 83/05/06 21:00:19 leres 25 24
c Fix from dlw@Jade, use a hash table so that uid's bigger than 2048 work.
e
s 00006/00000/01133
d D 4.22 83/04/13 15:54:15 leres 24 23
c Modified so that "ps t" means processes at my tty.
e
s 00054/00175/01079
d D 4.21 83/02/09 14:00:22 sam 23 22
c stuff from sun and delete ss trash
e
s 00001/00001/01253
d D 4.20 82/12/24 12:40:06 sam 22 21
c pte.h moved
e
s 00005/00009/01249
d D 4.19 82/11/14 16:33:35 sam 21 20
c convert to 4.1c sys calls and directory layout
e
s 00034/00025/01224
d D 4.18 82/06/26 01:07:10 wnj 20 19
c -k works now
e
s 00072/00081/01177
d D 4.17 82/05/07 17:46:29 mckusick 19 18
c update to new fs
e
s 00020/00009/01238
d D 4.16 82/03/01 00:11:36 wnj 18 17
c merge in -k fixes with rand stuff
e
s 00001/00001/01246
d D 4.15 81/09/08 08:30:02 mark 17 16
c fixed SCCS id to use %G%, not %E%
e
s 00152/00019/01095
d D 4.14 81/09/03 12:23:19 mark 16 15
c ss command from Rand merged in (again!)
e
s 00001/00001/01113
d D 4.13 81/07/08 16:32:54 root 15 14
c restore sccs line
e
s 00006/00003/01108
d D 4.12 81/07/08 16:32:04 root 14 11
c fix bug which caused some ttys to appear to be ``mt''
e
s 00004/00001/01243
d R 4.13 81/07/02 15:31:01 bugs 13 12
c fix to ps on tty12 printing tty as ``mt''
e
s 00152/00019/01092
d R 4.12 81/05/22 00:08:14 mark 12 11
c added in Rand ss stuff
e
s 00002/00000/01109
d D 4.11 81/05/12 23:03:56 toy 11 10
c Recognize net process (3)
e
s 00002/00002/01107
d D 4.10 81/04/26 23:38:41 wnj 10 9
c lim prints as XX; print S for sequential
e
s 00014/00005/01095
d D 4.9 81/04/21 02:06:01 root 9 8
c limit memsize stuff
e
s 00037/00015/01063
d D 4.8 81/02/28 22:55:52 wnj 8 7
c changed for new system style
e
s 00008/00001/01070
d D 4.7 80/10/21 01:23:27 bill 7 6
c pad for hardware botch end-run
e
s 00001/00001/01070
d D 4.6 80/10/20 14:04:38 bill 6 5
c fixed bug where used text even though 0
e
s 00006/00001/01065
d D 4.5 80/10/19 01:59:53 bill 5 4
c S option
e
s 00085/00044/00981
d D 4.4 80/10/12 23:30:04 bill 4 3
c %cpu %mem stuff 
e
s 00037/00014/00988
d D 4.3 80/10/11 18:32:38 bill 3 2
c ps au fixes
e
s 00095/00058/00907
d D 4.2 80/10/11 14:44:22 bill 2 1
c misc bug fixes
e
s 00965/00000/00000
d D 4.1 80/10/01 17:27:49 bill 1 0
c date and time created 80/10/01 17:27:49 by bill
e
u
U
f b 
t
T
I 37
D 67
/*
D 61
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 61
I 61
 * Copyright (c) 1989 The Regents of the University of California.
E 67
I 67
/*-
D 93
 * Copyright (c) 1990 The Regents of the University of California.
E 67
 * All rights reserved.
E 93
I 93
D 97
 * Copyright (c) 1990, 1993
E 97
I 97
 * Copyright (c) 1990, 1993, 1994
E 97
 *	The Regents of the University of California.  All rights reserved.
E 93
 *
D 67
 * Redistribution and use in source and binary forms is permitted
 * provided that all copyright information, including this notice,
 * is retained in all such forms, and that any documentation,
 * advertising or other materials related to such distribution and
 * use acknowledge that the software was
 * developed by the University of California, Berkeley.  The name
 * of the University may not be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 67
I 67
 * %sccs.include.redist.c%
E 67
E 61
 */

E 37
I 19
#ifndef lint
E 19
I 3
D 14
static	char *sccsid = "%W% (Berkeley) %G%";
E 14
I 14
D 15
static	char *sccsid = "@(#)ps.c	4.10+ (Berkeley) 7/2/81";
E 15
I 15
D 17
static	char *sccsid = "%W% (Berkeley) %E%";
E 17
I 17
D 37
static	char *sccsid = "%W% (Berkeley) %G%";
I 19
#endif
E 37
I 37
D 93
char copyright[] =
D 61
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 61
I 61
D 67
"@(#) Copyright (c) 1989 The Regents of the University of California.\n\
E 67
I 67
D 78
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
E 78
I 78
D 79
"@(#) Copyright (c) 1990 The Regents of the University of California.\n\
E 79
I 79
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
E 79
E 78
E 67
E 61
 All rights reserved.\n";
E 93
I 93
static char copyright[] =
D 97
"%Z% Copyright (c) 1990, 1993\n\
E 97
I 97
"%Z% Copyright (c) 1990, 1993, 1994\n\
E 97
	The Regents of the University of California.  All rights reserved.\n";
E 93
D 61
#endif not lint
E 61
I 61
#endif /* not lint */
E 61

#ifndef lint
D 61
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 37

E 61
I 61
D 67
static char sccsid[] = "@(#)ps.c	1.8 (Berkeley) 2/16/90";
E 67
I 67
D 78
static char sccsid[] = "%W% (Berkeley) %G%";
E 78
I 78
D 79
static char sccsid[] = "@(#)ps.c	5.37 (Berkeley) 3/27/91";
E 79
I 79
static char sccsid[] = "%W% (Berkeley) %G%";
E 79
E 78
E 67
#endif /* not lint */
I 67

D 71
#include <machine/pte.h>

E 71
E 67
E 61
E 19
E 17
E 15
E 14
E 3
I 1
D 2
static char *sccsid = "%W% (Berkeley) %G%";
E 2
D 41
/*
D 19
 * ps; VAX 4BSD version
E 19
I 19
 * ps
I 39
 *
 * $Log:	ps.c,v $
 * Revision 5.2.1.4  85/08/25  22:25:43  crl
 * 'n' flag now also causes usernames to be printed as uid's.
 * 
 * Revision 5.2.1.3  85/08/10  01:33:18  crl
 * Implemented the wait channel stop list in addchan() and the index table
 * 	in getchan()
 * 
 * Revision 5.2.1.2  85/08/05  23:40:34  crl
 * Cut down # of calls to realloc by allocating in bigger chunks in
 * 	addchan().
 * If terminal width > WTSIZ, use a wider field for wchan.
 * 
E 39
E 19
 */
E 41
D 23

E 23
D 57
#include <stdio.h>
#include <ctype.h>
D 39
#include <nlist.h>
E 39
I 39
#include <a.out.h>
E 39
#include <pwd.h>
E 57
#include <sys/param.h>
I 86
D 92
#include <sys/file.h>
E 92
E 86
I 58
D 67
#include <sys/types.h>
E 67
E 58
I 34
D 71
#include <sys/ioctl.h>
E 34
#include <sys/tty.h>
E 71
D 19
#include <sys/dir.h>
E 19
I 19
D 26
#include <dir.h>
E 26
I 26
D 60
#include <sys/dir.h>
E 60
E 26
E 19
#include <sys/user.h>
I 71
#include <sys/time.h>
#include <sys/resource.h>
E 71
#include <sys/proc.h>
I 60
D 61
#include <dirent.h>
E 61
E 60
D 22
#include <sys/pte.h>
E 22
I 22
D 57
#include <machine/pte.h>
E 57
E 22
D 71
#include <sys/vm.h>
#include <sys/text.h>
E 71
#include <sys/stat.h>
I 23
D 71
#include <sys/mbuf.h>
I 57
D 67
#include <machine/pte.h>
E 67
D 61
#include <a.out.h>
E 61
I 61
#include <nlist.h>
E 61
#include <pwd.h>
E 57
E 23
I 3
#include <math.h>
E 71
I 71
#include <sys/ioctl.h>
D 90
#include <sys/kinfo.h>
E 90
I 90
#include <sys/sysctl.h>
E 90
I 80
D 92
#include <nlist.h>
E 80
#include <kvm.h>
E 92
I 92

#include <ctype.h>
#include <err.h>
E 92
E 71
I 29
#include <errno.h>
I 69
D 71
#include <stddef.h>
E 71
I 71
D 92
#include <unistd.h>
E 92
I 92
#include <fcntl.h>
#include <kvm.h>
#include <nlist.h>
#include <paths.h>
E 92
D 81
#include <stdarg.h>
E 81
E 71
E 69
I 57
#include <stdio.h>
I 69
#include <stdlib.h>
#include <string.h>
E 69
D 71
#include <ctype.h>
I 69
#include <varargs.h>
E 69
D 61
#include "pathnames.h"
E 61
I 61
#include <kvm.h>
I 69
#include "pathnames.h"
E 71
I 71
D 92
#include <paths.h>
I 88
#include <ctype.h>
E 92
I 92
#include <unistd.h>

E 92
E 88
#include "ps.h"
E 71
E 69
E 61
E 57
E 29
I 9
D 23
#include <sys/vlimit.h>
E 23
E 9
E 3

I 77
D 94
#ifdef SPPWAIT
E 94
I 94
#ifdef P_PPWAIT
E 94
#define NEWVM
#endif

E 77
D 39
struct nlist nl[] = {
	{ "_proc" },
E 39
I 39
D 61
char *nl_names[] = {
E 61
I 61
D 71
struct usave {
	struct	proc *u_procp;
	struct	timeval u_start;
	struct	rusage u_ru;
	struct	rusage u_cru;
D 70
	short	u_cmask;
E 70
	char	u_acflag;
};
E 71
I 71
KINFO *kinfo;
D 78
VAR *vhead, *vtail;
E 78
I 78
struct varent *vhead, *vtail;
E 78
E 71
E 61
D 59
	"_proc",
E 39
#define	X_PROC		0
D 39
	{ "_Usrptmap" },
E 39
I 39
	"_Usrptmap",
E 39
D 29
#define	X_USRPTMA	1
E 29
I 29
#define	X_USRPTMAP	1
E 29
D 39
	{ "_usrpt" },
E 39
I 39
	"_usrpt",
E 39
#define	X_USRPT		2
D 39
	{ "_text" },
E 39
I 39
	"_text",
E 39
#define	X_TEXT		3
D 39
	{ "_nswap" },
E 39
I 39
	"_nswap",
E 39
#define	X_NSWAP		4
I 2
D 39
	{ "_maxslp" },
E 39
I 39
	"_maxslp",
E 39
#define	X_MAXSLP	5
I 3
D 39
	{ "_ccpu" },
E 39
I 39
	"_ccpu",
E 39
#define	X_CCPU		6
I 4
D 39
	{ "_ecmx" },
E 39
I 39
	"_ecmx",
E 39
#define	X_ECMX		7
I 8
D 39
	{ "_nproc" },
E 39
I 39
	"_nproc",
E 39
#define	X_NPROC		8
D 39
	{ "_ntext" },
E 39
I 39
	"_ntext",
E 39
#define	X_NTEXT		9
I 26
D 39
	{ "_dmmin" },
E 39
I 39
	"_dmmin",
E 39
#define	X_DMMIN		10
D 39
	{ "_dmmax" },
E 39
I 39
	"_dmmax",
E 39
#define	X_DMMAX		11
I 29
D 39
	{ "_Sysmap" },
E 39
I 39
	"_Sysmap",
E 39
#define	X_SYSMAP	12
D 39
	{ "_Syssize" },
E 39
I 39
	"_Syssize",
E 39
#define	X_SYSSIZE	13
E 29
E 26
D 21
	{ "_hz" },
#define	X_HZ		10
E 21
E 8
E 4
E 3
E 2
D 23
	{ 0 },
E 23
I 23
D 39
	{ "" },
E 39
I 39
	"_inode",
#define X_INODE		14
E 59
I 59

D 71
/*
D 61
 * The following are used for symbolic wchan's
E 61
I 61
 * to compute offset in common structures
E 61
 */
D 61
	"_vnode",
#define X_VNODE		0
E 59
	"_file",
D 59
#define X_FILE		15
E 59
I 59
#define X_FILE		1
E 59
	"_cfree",
D 59
#define X_CFREE		16
E 59
I 59
#define X_CFREE		2
E 59
	"_callout",
D 59
#define X_CALLOUT	17
E 59
I 59
#define X_CALLOUT	3
E 59
	"_swapmap",
D 59
#define X_SWAPMAP	18
E 59
I 59
#define X_SWAPMAP	4
E 59
	"_argmap",
D 59
#define X_ARGMAP	19
E 59
I 59
#define X_ARGMAP	5
E 59
	"_kernelmap",
D 59
#define X_KERNELMAP	20
E 59
I 59
#define X_KERNELMAP	6
E 59
	"_mbmap",
D 59
#define X_MBMAP		21
E 59
I 59
#define X_MBMAP		7
E 59
D 47
	"_nch",
E 47
I 47
	"_namecache",
E 47
D 59
#define X_NCH		22
E 59
I 59
#define X_NCH		8
E 59
	"_quota",
D 59
#define X_QUOTA		23
E 59
I 59
#define X_QUOTA		9
E 59
	"_dquot",
D 59
#define X_DQUOT		24
E 59
I 59
#define X_DQUOT		10
E 59
	"_swbuf",
D 59
#define X_SWBUF		25
E 59
I 59
#define X_SWBUF		11
E 59
	"_buf",
D 59
#define X_BUF		26
E 59
I 59
#define X_BUF		12
E 59
	"_cmap",
D 59
#define X_CMAP		27
E 59
I 59
#define X_CMAP		13
E 59
	"_buffers",
D 59
#define X_BUFFERS	28
E 59
I 59
#define X_BUFFERS	14
E 61
I 61
D 69
#define	POFF(x)		((int)&((struct proc *)0)->x)
#define	EOFF(x)		((int)&((struct eproc *)0)->x)
#define	UOFF(x)		((int)&((struct usave *)0)->x)
#define	ROFF(x)		((int)&((struct rusage *)0)->x)
E 69
I 69
#define	POFF(x)		offsetof(struct proc, x)
#define	EOFF(x)		offsetof(struct eproc, x)
#define	UOFF(x)		offsetof(struct usave, x)
#define	ROFF(x)		offsetof(struct rusage, x)
E 71
I 71
int	eval;			/* exit value */
int	rawcpu;			/* -C */
int	sumrusage;		/* -S */
int	termwidth;		/* width of screen (0 == infinity) */
int	totwidth;		/* calculated width of requested variables */
E 71
E 69
E 61

D 61
/*
 * These are used for interpreting raw memory (-k)
 */
	"_Sysmap",
#define	X_SYSMAP	15
	"_Syssize",
#define	X_SYSSIZE	16
E 61
I 61
D 71
enum type	{ CHAR, UCHAR, SHORT, USHORT, LONG, ULONG, KPTR };
E 71
I 71
D 86
static int needuser, needcomm;
E 86
I 86
static int needuser, needcomm, needenv;
E 86
E 71
E 61

D 61
/*
 * These should be obtained from getdynamicsysinfo()
 */
	"_ecmx",
#define	X_ECMX		17
	"_ccpu",
#define	X_CCPU		18
E 59
I 58
	"_fscale",
D 59
#define X_FSCALE	29
E 59
I 59
#define X_FSCALE	19
E 61
I 61
D 71
#define	UIDFMT	"u"
#define UIDLEN	5
#define PIDFMT	"d"
#define PIDLEN	5
#define	USERLEN	8
E 71
I 71
D 74
enum sort { SORTMEM, SORTCPU } sortby;
E 74
I 74
enum sort { DEFAULT, SORTMEM, SORTCPU } sortby = DEFAULT;
E 74
E 71
E 61

D 61
/*
 * Here to end should be replaced by getproc info()
 */
E 61
I 61
D 71
int needuser, needcomm, neednlist;
E 61

D 61
/* This is used to find the prog args and user area */
	"_Usrptmap",
#define	X_USRPTMAP	20
	"_usrpt",
#define	X_USRPT		21
E 61
I 61
D 69
int 	command(), ucomm(), logname(), pvar(), evar(), uvar(), rvar(), uname(), 
E 69
I 69
int 	command(), ucomm(), logname(), pvar(), evar(), uvar(), rvar(), uname(),
E 69
	runame(), state(), pri(), tdev(), tname(), longtname(), started(),
D 69
	lstarted(), wchan(), vsize(), rssize(), p_rssize(), cputime(), 
E 69
I 69
	lstarted(), wchan(), vsize(), rssize(), p_rssize(), cputime(),
E 69
	pmem(), pcpu(), pagein(), maxrss(), tsize(), trss();
	/**
	utime(), stime(), ixrss(), idrss(), isrss();
	**/
E 61

E 71
D 61
/* This is used to extract the process table */
	"_nproc",
#define	X_NPROC		22
	"_proc",
#define	X_PROC		23
E 61
I 61
D 69
struct	usave *saveuser();
char	*saveargs();
E 69
I 69
D 88
uid_t	getuid();
char	*ttyname();
E 88
I 88
D 89
static void	 err __P((const char *, ...));
E 89
static char	*fmt __P((char **(*)(kvm_t *, const struct kinfo_proc *, int),
		    KINFO *, char *, int));
static char	*kludge_oldps_options __P((char *));
static int	 pscomp __P((const void *, const void *));
static void	 saveuser __P((KINFO *));
static void	 scanvars __P((void));
static void	 usage __P((void));
E 88
E 69
E 61

D 61
/* These are used to extract the text table */
	"_ntext",
#define	X_NTEXT		24
	"_text",
#define	X_TEXT		25
E 61
I 61
D 71
struct var {
D 69
	char	*name[8];	/* name(s) of variable */
E 69
I 69
	char	*name[4];	/* name(s) of variable */
E 69
	char	*header;	/* default header */
	int	flag;
#define	USER	0x01	/* requires user structure */
D 62
#define	TEXT	0x02	/* requires text table */
#define	LJUST	0x04	/* right adjust on output */
#define	COMM	0x08	/* requires exec arguments and environment (XXX) */
#define	NLIST	0x10	/* requires nlist to get extra variables */
E 62
I 62
D 69
#define	LJUST	0x02	/* right adjust on output */
E 69
I 69
#define	LJUST	0x02	/* left adjust on output (trailing blanks) */
E 69
#define	COMM	0x04	/* requires exec arguments and environment (XXX) */
#define	NLIST	0x08	/* requires nlist to get extra variables */
E 62
	int	(*oproc)();	/* output routine */
	short	width;		/* printing width */
	/*
	 * The following (optional) elements are hooks for passing information
	 * to the generic output routines: pvar, evar, uvar (those which print
	 * simple elements from well known structures: proc, eproc, usave)
	 */
	int	off;		/* offset in structure */
	enum	type type;	/* type of element */
	char	*fmt;		/* printf format */
	/*
	 * glue to link selected fields together
	 */
	struct	var *next;
}  var[] = {
D 69
	{{"command", "comm", "args"}, "COMMAND", USER|LJUST|COMM, 
		command, 16}, 
E 69
I 69
	{{"command", "comm", "args"}, "COMMAND", USER|LJUST|COMM,
		command, 16},
E 69
	{{"ucomm"}, "COMMAND",	LJUST, ucomm, MAXCOMLEN},
	{{"logname"}, "LOGNAME", LJUST, logname, MAXLOGNAME},
D 62
	{{"flag"}, "F", 0, pvar, 7, POFF(p_flag), LONG, "x"},
E 62
I 62
	{{"flag", "f"}, "F", 0, pvar, 7, POFF(p_flag), LONG, "x"},
E 62
	{{"uid"}, "UID", 0, pvar, UIDLEN, POFF(p_uid),USHORT, UIDFMT},
	{{"ruid"}, "RUID", 0, pvar, UIDLEN, POFF(p_ruid), USHORT, UIDFMT},
	{{"svuid"}, "SVUID", 0, pvar, UIDLEN, POFF(p_svuid), USHORT, UIDFMT},
	{{"rgid"}, "RGID", 0, pvar, UIDLEN, POFF(p_rgid), USHORT, UIDFMT},
	{{"svgid"}, "SVGID", 0, pvar, UIDLEN, POFF(p_svgid), USHORT, UIDFMT},
	{{"pid"}, "PID", 0, pvar, PIDLEN, POFF(p_pid),SHORT, PIDFMT},
	{{"ppid"}, "PPID", 0, pvar, PIDLEN, POFF(p_ppid), SHORT, PIDFMT},
	{{"cp", "cpu"}, "CP", 0, pvar, 3, POFF(p_cpu), UCHAR, "d"},
	{{"xstat"}, "XSTAT", 0, pvar, 4, POFF(p_xstat), USHORT, "x"},
	{{"poip"}, "POIP", 0, pvar, 4, POFF(p_poip), SHORT, "d"},
	{{"nwchan"}, "WCHAN", 0, pvar, 6, POFF(p_wchan), KPTR, "x"},
	{{"wchan"}, "WCHAN", LJUST, wchan, 6},
	{{"rlink"}, "RLINK", 0, pvar, 8, POFF(p_rlink), KPTR, "x"},
	{{"ktrace", "traceflag"}, "KTRACE",
		0, pvar, 8, POFF(p_traceflag), LONG, "x"},
	{{"ktracep", "tracep"}, "KTRACEP",
		0, pvar, 8, POFF(p_tracep), LONG, "x"},
D 67
	{{"cursig"}, "CURSIG",
		0, pvar, 2, POFF(p_cursig), CHAR, "d"},
E 67
	{{"sig", "pending"}, "PENDING",
		0, pvar, 8, POFF(p_sig), LONG, "x"},
	{{"sigmask", "blocked"}, "BLOCKED",
		0, pvar, 8, POFF(p_sigmask), LONG, "x"},
	{{"sigignore", "ignored"}, "IGNORED",
		0, pvar, 8, POFF(p_sigignore), LONG, "x"},
	{{"sigcatch", "caught"}, "CAUGHT",
		0, pvar, 8, POFF(p_sigcatch), LONG, "x"},
	{{"user", "uname"}, "USER", LJUST, uname, USERLEN},
	{{"ruser", "runame"}, "RUSER", LJUST, runame, USERLEN},
	{{"pgid"}, "PGID", 0, evar, PIDLEN, EOFF(e_pgid), USHORT, PIDFMT},
	{{"jobc"}, "JOBC", 0, evar, 4, EOFF(e_jobc), SHORT, "d"},
	{{"sess", "session"}, "SESS", 0, evar, 6, EOFF(e_sess), KPTR, "x"},
	{{"tdev", "dev"}, "TDEV", 0, tdev, 4},
D 62
	{{"tname", "tty", "tt"}, "TT", LJUST, tname, 2},
E 62
I 62
	{{"tname", "tty", "tt"}, "TT", LJUST, tname, 3},
E 62
	{{"longtname", "longtty"}, "TT", LJUST, longtname, 8},
	{{"tpgid"}, "TPGID", 0, evar, 4, EOFF(e_tpgid), USHORT, PIDFMT},
D 69
	{{"tsession", "tsess"}, "TSESS", 
E 69
I 69
	{{"tsession", "tsess"}, "TSESS",
E 69
		0, evar, 6, EOFF(e_tsess), KPTR, "x"},
	{{"paddr", "procaddr"}, "PADDR",
		0, evar, 6, EOFF(e_paddr), KPTR, "x"},
D 62
	{{"state", "stat"}, "STAT", 0, state, 3},
E 62
I 62
	{{"state", "stat"}, "STAT", 0, state, 4},
E 62
	{{"pri"}, "PRI", 0, pri, 3},
	{{"usrpri"}, "UPR", 0, pvar, 3, POFF(p_usrpri), CHAR, "d"},
D 69
	{{"nice", "ni"}, "NI", 0, pvar, 2, POFF(p_nice), CHAR, "d"}, 
E 69
I 69
	{{"nice", "ni"}, "NI", 0, pvar, 2, POFF(p_nice), CHAR, "d"},
E 69
	{{"vsize", "vsz"}, "VSZ", 0, vsize, 5},
	{{"rssize", "rsz"}, "RSZ", 0, rssize, 4},
	{{"rss", "p_rss"}, "RSS", 0, p_rssize, 4},
	{{"u_procp", "uprocp"}, "UPROCP",
		USER, uvar, 6, UOFF(u_procp), KPTR, "x"},
D 70
	{{"umask", "u_cmask"}, "UMASK",
D 62
		USER, uvar, 3, UOFF(u_cmask), CHAR, "o"},
E 62
I 62
		USER, uvar, 3, UOFF(u_cmask), CHAR, "#o"},
E 70
E 62
	{{"acflag", "acflg"}, "ACFLG",
		USER, uvar, 3, UOFF(u_acflag), SHORT, "x"},
	{{"start"}, "STARTED", USER|LJUST, started, 8},
	{{"lstart"}, "STARTED", USER|LJUST, lstarted, 28},
D 65
	{{"cputime", "time"}, "TIME", USER, cputime, 6},
E 65
I 65
	{{"cputime", "time"}, "TIME", USER, cputime, 9},
E 65
	{{"p_ru"}, "P_RU", 0, pvar, 6, POFF(p_ru), KPTR, "x"},
	{{"pcpu", "%cpu"}, "%CPU", NLIST, pcpu, 4},
	{{"pmem", "%mem"}, "%MEM", NLIST, pmem, 4},
	{{"sl", "slp", "slptime"}, "SL",
		0, pvar, 3, POFF(p_slptime), CHAR, "d"},
	{{"re", "resident"}, "RE",
		0, pvar, 3, POFF(p_time), CHAR, "d"},
	{{"pagein", "majflt"}, "PAGEIN", USER, pagein, 6},
	{{"lim", "maxrss"}, "LIM", 0, maxrss, 5},
	{{"tsiz"}, "TSIZ", 0, tsize, 4},
	{{"trs"}, "TRS", 0, trss, 3},
	/***
	{{"utime"}, "UTIME", USER, utime, 4},
	{{"stime"}, "STIME", USER, stime, 4},
	{{"ixrss"}, "IXRSS", USER, ixrss, 4},
	{{"idrss"}, "IDRSS", USER, idrss, 4},
	{{"isrss"}, "ISRSS", USER, isrss, 4},
	***/
D 69
	{{"minflt"}, "MINFLT", 
E 69
I 69
	{{"minflt"}, "MINFLT",
E 69
		USER, rvar, 4, ROFF(ru_minflt), LONG, "d"},
D 69
	{{"majflt"}, "MAJFLT", 
E 69
I 69
	{{"majflt"}, "MAJFLT",
E 69
		USER, rvar, 4, ROFF(ru_majflt), LONG, "d"},
D 69
	{{"nswap"}, "NSWAP", 	
E 69
I 69
	{{"nswap"}, "NSWAP",
E 69
		USER, rvar, 4, ROFF(ru_nswap), LONG, "d"},
D 69
	{{"inblock", "inblk"}, "INBLK", 	
E 69
I 69
	{{"inblock", "inblk"}, "INBLK",
E 69
		USER, rvar, 4, ROFF(ru_inblock), LONG, "d"},
D 69
	{{"oublock", "oublk"}, "OUBLK", 
E 69
I 69
	{{"oublock", "oublk"}, "OUBLK",
E 69
		USER, rvar, 4, ROFF(ru_oublock), LONG, "d"},
D 69
	{{"msgsnd"}, "MSGSND", 
E 69
I 69
	{{"msgsnd"}, "MSGSND",
E 69
		USER, rvar, 4, ROFF(ru_msgsnd), LONG, "d"},
D 69
	{{"msgrcv"}, "MSGRCV", 
E 69
I 69
	{{"msgrcv"}, "MSGRCV",
E 69
		USER, rvar, 4, ROFF(ru_msgrcv), LONG, "d"},
D 69
	{{"nsignals", "nsigs"}, "NSIGS", 
E 69
I 69
	{{"nsignals", "nsigs"}, "NSIGS",
E 69
		USER, rvar, 4, ROFF(ru_nsignals), LONG, "d"},
D 69
	{{"nvcsw", "vcsw"}, "VCSW", 
E 69
I 69
	{{"nvcsw", "vcsw"}, "VCSW",
E 69
		USER, rvar, 5, ROFF(ru_nvcsw), LONG, "d"},
D 69
	{{"nivcsw", "ivcsw"}, "IVCSW", 
E 69
I 69
	{{"nivcsw", "ivcsw"}, "IVCSW",
E 69
		USER, rvar, 5, ROFF(ru_nivcsw), LONG, "d"},
	NULL
};
E 61

D 61
/*
 * These are used by vstodb to interpret the swap area 
 * while searching for the command
E 61
I 61
D 69
/* 
 * combination variables 
E 69
I 69
/*
 * combination variables
E 69
E 61
 */
D 61
	"_nswap",
#define	X_NSWAP		26
	"_dmmin",
#define	X_DMMIN		27
	"_dmmax",
#define	X_DMMAX		28
E 59
E 58
	""
E 61
I 61
struct combovar {
	char *name;
	char *replace;
} combovar[] = {
	"RUSAGE", "minflt majflt nswap inblock oublock \
		msgsnd msgrcv nsigs nvcsw nivcsw",
	0, 0
E 61
E 39
E 23
};
I 61
D 62
#define DFMT	"pid tname stat cputime comm"
E 62
I 62
#define DFMT	"pid tname state cputime comm"
E 71
I 71
D 72
#define DFMT	"pid tname state cputime command"
#define	JFMT	"user pid ppid pgid sess jobc state tname cputime command"
E 72
I 72
D 76
#define DFMT	"pid tt state time command"
#define	JFMT	"user pid ppid pgid sess jobc state tt time command"
E 72
E 71
E 62
#define LFMT \
D 62
	"flag uid pid ppid cp pri nice vsz rss wchan stat tname cputime comm"
#define	JFMT	"user pid ppid pgid sess jobc stat tname cputime comm"
E 62
I 62
D 71
	"uid pid ppid cp pri nice vsz rss wchan state tname cputime comm"
#define	JFMT	"user pid ppid pgid sess jobc state tname cputime comm"
E 62
D 67
#define	SFMT	"user pid cursig sig sigmask sigignore sigcatch tname comm"
E 67
I 67
#define	SFMT	"uid pid sig sigmask sigignore sigcatch stat tname comm"
E 67
#define	VFMT \
D 62
	"pid tt stat time sl re pagein vsz rss lim tsiz trs %cpu %mem comm"
E 62
I 62
	"pid tt state time sl re pagein vsz rss lim tsiz trs %cpu %mem comm"
E 71
I 71
D 72
	"uid pid ppid cpu pri nice vsize rss wchan state tname cputime command"
#define	SFMT	"uid pid sig sigmask sigignore sigcatch state tname command"
E 72
I 72
	"uid pid ppid cpu pri nice vsz rss wchan state tt time command"
D 74
#define	SFMT	"uid pid sig sigmask sigignore sigcatch state tt command"
E 74
E 72
E 71
E 62
#define UFMT \
D 62
	"uname pid %cpu %mem vsz rss tt stat start time comm"
E 62
I 62
D 71
	"uname pid %cpu %mem vsz rss tt state start time comm"
E 71
I 71
D 72
	"user pid pcpu pmem vsize rss tname state start cputime command"
E 72
I 72
	"user pid %cpu %mem vsz rss tt state start time command"
E 72
#define	VFMT \
D 72
	"pid tname state cputime sl re pagein vsize rss lim tsiz trs pcpu pmem command"
E 72
I 72
D 73
	"pid tt state time sl re pagein vsz rss lim tsiz trs %cpu %mem command"
E 73
I 73
	"pid state time sl re pagein vsz rss lim tsiz trs %cpu %mem command"
E 76
I 76
char dfmt[] = "pid tt state time command";
char jfmt[] = "user pid ppid pgid sess jobc state tt time command";
char lfmt[] = "uid pid ppid cpu pri nice vsz rss wchan state tt time command";
char   o1[] = "pid";
char   o2[] = "tt state time command";
char ufmt[] = "user pid %cpu %mem vsz rss tt state start time command";
D 91
char vfmt[] =
	"pid state time sl re pagein vsz rss lim tsiz trs %cpu %mem command";
E 91
I 91
char vfmt[] = "pid state time sl re pagein vsz rss lim tsiz %cpu %mem command";
E 91
E 76
E 73
E 72
E 71
E 62
E 61

I 86
kvm_t *kd;

I 88
int
E 88
E 86
I 39
D 61
struct nlist *nl;			/* all because we can't init unions */
int nllen;				/* # of nlist entries */
E 61
I 61
D 71
struct kinfo {
	struct proc *ki_p;	/* proc structure */
	struct eproc *ki_e;	/* extra stuff */
	struct usave *ki_u;	/* interesting parts of user */
	char *ki_args;		/* exec args (should be char **) */
	char *ki_env;		/* environment (should be char **) */
} *kinfo;
E 61

E 39
D 61
struct	savcom {
	union {
		struct	lsav *lp;
		float	u_pctcpu;
		struct	vsav *vp;
		int	s_ssiz;
I 16
D 19
		struct	sssav *ssp;	/* RAND 2/81 */
E 19
I 19
D 23
		struct	sssav *ssp;
E 19
E 16
	} sun;
E 23
I 23
	} s_un;
E 23
	struct	asav *ap;
D 8
} savcom[NPROC];
E 8
I 8
} *savcom;
E 8

struct	asav {
	char	*a_cmdp;
	int	a_flag;
D 2
	short	a_stat, a_uid, a_pid, a_nice;
E 2
I 2
	short	a_stat, a_uid, a_pid, a_nice, a_pri, a_slptime, a_time;
E 2
D 4
	size_t	a_size, a_rss;
E 4
I 4
	size_t	a_size, a_rss, a_tsiz, a_txtrss;
	short	a_xccount;
E 4
D 19
	char	a_tty[DIRSIZ+1];
E 19
I 19
	char	a_tty[MAXNAMLEN+1];
E 19
D 60
	dev_t	a_ttyd;
E 60
I 60
	int   	a_pgid;
	int     a_session;
	dev_t   a_ttyd;
	int     a_tsession;
	int   	a_tpgid;
E 60
D 2
	time_t	a_time;
E 2
I 2
	time_t	a_cpu;
I 9
	size_t	a_maxrss;
I 60
	pid_t   a_ppid;
E 60
E 9
E 2
};

char	*lhdr;
I 39
int	wcwidth;		/* width of the wchan field for sprintf*/
E 39
D 2
/*	    F S UID   PID  PPID CP PRI NICE ADDR  SZ  RSS WCHAN TTY TIME */
E 2
I 2
D 3
/*	     F UID   PID  PPID CP PRI NI ADDR  SZ  RSS WCHAN S  TT  TIME */
E 3
I 3
D 4
/*	     F UID   PID  PPID CP PRI NI ADDR  SZ  RSS WCHAN ST TT  TIME */
E 4
E 3
E 2
struct	lsav {
D 60
	short	l_ppid;
E 60
D 2
	char	l_cpu, l_pri;
E 2
I 2
D 54
	char	l_cpu;
E 54
I 54
	u_char	l_cpu;
E 54
E 2
	int	l_addr;
	caddr_t	l_wchan;
};

I 16
D 19
char	*sshdr;				/* RAND 2/81 */
struct	sssav {				/* RAND 2/81 */
	short 	ss_ppid;		/* RAND 2/81 */
	short	ss_brother;		/* RAND 2/81 */
	short	ss_sons;		/* RAND 2/81 */
};					/* RAND 2/81 */
E 19
I 19
D 23
char	*sshdr;
struct	sssav {
	short 	ss_ppid;
	short	ss_brother;
	short	ss_sons;
};
E 19

E 23
E 16
char	*uhdr;
D 2
/*	 USER       PID %CPU NICE  SZ  RSS TTY TIME */
E 2
I 2
D 3
/*	USER       PID %CPU NICE  SZ  RSS TT F  TIME */
E 3
I 3
D 4
/*	USER       PID %CPU NI   SZ  RSS TT ST TIME */
E 3
E 2

E 4
char	*shdr;
I 60
char	*jhdr;
E 60
D 2
/*	 SSIZ   PID TTY TIME */
E 2
I 2
D 3
/*	SSIZ   PID TT S  TIME */
E 3
I 3
D 4
/*	SSIZ   PID TT ST TIME */
E 4
E 3
E 2

char	*vhdr;
D 2
/*	F     PID TTY  TIME TIM SL  MINFLT  MAJFLT SIZE  RSS  SRS TSIZ TRS PF*/
E 2
I 2
D 3
/*	F     PID TT  TIME RES SL  MINFLT  MAJFLT SIZE  RSS  SRS TSIZ TRS PF*/
E 3
I 3
D 4
/*	   PID TT ST    TIME RES SL MINFLT MAJFLT SIZE  RSS  SRS TSIZ TRS %CP*/
E 4
E 3
E 2
struct	vsav {
D 2
	short	v_slptime, v_pri;
E 2
D 4
	u_int	v_minflt, v_majflt;
	size_t	v_swrss, v_tsiz, v_txtrss, v_txtswrss;
	short	v_xccount;
D 3
	short	v_aveflt;
E 3
I 3
	short	v_pctcpu;
E 4
I 4
	u_int	v_majflt;
	size_t	v_swrss, v_txtswrss;
	float	v_pctcpu;
E 4
E 3
};
E 61
I 61
struct	var *vhead, *vtail;
int	termwidth;	/* width of screen (0 == infinity) */
#define UNLIMITED	0
int	totwidth;	/* calculated width of requested variables */
int	sumrusage;
int	rawcpu;
int	sortby;
#define	SORTMEM	1
#define	SORTCPU 2
E 61

D 29
struct	proc proc[8];		/* 8 = a few, for less syscalls */
E 29
I 29
D 61
#define	NPROC	16
E 61
I 61
int	uid = -1;
dev_t	ttydev = NODEV;
int	pid = -1;
int	all;
int	xflg;
int	prtheader;
int	lineno;
E 61

D 61
struct	proc proc[NPROC];		/* a few, for less syscalls */
E 29
struct	proc *mproc;
struct	text *text;

I 7
D 19
int	paduser1;		/* avoid hardware mem clobbering botch */
E 19
E 7
union {
	struct	user user;
	char	upages[UPAGES][NBPG];
} user;
#define u	user.user
I 7
D 19
int	paduser2;		/* avoid hardware mem clobbering botch */
E 19
E 7

D 29
#define clear(x) 	((int)x & 0x7fffffff)
E 29
I 29
#ifndef	PSFILE
D 57
char	*psdb	= "/etc/psdatabase";
E 57
I 57
char	*psdb	= _PATH_PSDATABASE;
E 57
#else
char	*psdb	= PSFILE;
#endif
E 29

D 42
int	chkpid;
E 42
I 42
int	chkpid = -1;
E 42
D 16
int	aflg, cflg, eflg, gflg, kflg, lflg, sflg, uflg, vflg, xflg;
E 16
I 16
D 19
int	aflg, cflg, eflg, gflg, kflg, lflg, sflg, ssflg,  /* RAND 2/81 */
E 19
I 19
D 23
int	aflg, cflg, eflg, gflg, kflg, lflg, sflg, ssflg,
E 19
	nonssflg, uflg, vflg, xflg;
E 23
I 23
D 39
int	aflg, cflg, eflg, gflg, kflg, lflg, sflg,
E 39
I 39
int	aflg, cflg, eflg, gflg, kflg, lflg, nflg, sflg,
E 39
D 29
	uflg, vflg, xflg;
E 29
I 29
D 60
	uflg, vflg, xflg, Uflg;
E 60
I 60
	uflg, vflg, xflg, Uflg, jflg;
E 60
I 39
int	nchans;				/* total # of wait channels */
E 39
E 29
E 23
E 16
char	*tptr;
D 2
char	*gettty(), *getcmd(), *getname(), *savestr(), *alloc();
E 2
I 2
D 29
char	*gettty(), *getcmd(), *getname(), *savestr(), *alloc(), *state();
E 29
I 29
char	*gettty(), *getcmd(), *getname(), *savestr(), *state();
E 29
I 16
D 19
char	*rindex();		/* RAND 2/81 */
E 19
I 19
char	*rindex(), *calloc(), *sbrk(), *strcpy(), *strcat(), *strncat();
I 24
D 29
char	*index(), *ttyname(), mytty[16];
E 29
I 29
D 36
char	*strncpy(), *index(), *ttyname(), mytty[16];
E 36
I 36
char	*strncpy(), *index(), *ttyname(), mytty[MAXPATHLEN+1];
I 38
D 39
char	*malloc();
E 39
I 39
char	*malloc(), *getchan();
E 39
E 38
E 36
E 29
E 24
long	lseek();
I 29
off_t	vtophys();
E 29
E 19
E 16
I 3
D 4
double	pcpu();
E 4
I 4
double	pcpu(), pmem();
I 39
int	wchancomp();
E 39
E 4
E 3
E 2
int	pscomp();
D 2
int	nswap;
E 2
I 2
D 59
int	nswap, maxslp;
E 59
I 59
int	nswap;
E 59
I 8
struct	text *atext;
E 8
I 3
D 58
double	ccpu;
E 58
I 58
fixpt_t	ccpu;
E 58
I 4
int	ecmx;
E 4
E 3
E 2
D 29
struct	pte *Usrptma, *usrpt;
E 29
I 29
struct	pte *Usrptmap, *usrpt;
E 29
I 8
D 23
int	nproc, ntext, hz;
E 23
I 23
D 58
int	nproc, ntext;
E 58
I 58
int	nproc, ntext, fscale;
E 58
I 26
int	dmmin, dmmax;
I 29
struct	pte *Sysmap;
int	Syssize;
E 29
E 26
E 23
E 8

I 29
D 38
#ifndef	MAXTTYS
#define	MAXTTYS		256
#endif

E 38
int	nttys;

E 29
struct	ttys {
D 19
	char	name[DIRSIZ+1];
E 19
I 19
D 29
	char	name[MAXNAMLEN+1];
E 29
E 19
	dev_t	ttyd;
D 29
	struct	ttys *next;
E 29
D 38
	struct	ttys *cand;
E 38
I 38
	int cand;
E 38
D 29
} *allttys, *cand[16];
E 29
I 29
	char	name[MAXNAMLEN+1];
D 38
} allttys[MAXTTYS], *cand[16];
E 38
I 38
} *allttys;
int cand[16] = {-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1};
struct lttys {
	struct ttys ttys;
	struct lttys *next;
} *lallttys;
E 38
E 29

E 61
I 39
/*
D 61
 * struct for the symbolic wait channel info
 *
 * WNAMESIZ is the max # of chars saved of the symbolic wchan gleaned
 * from the namelist.  Normally, only WSNAMESIZ are printed in the long
 * format, unless the terminal width is greater than WTSIZ wide.
E 61
I 61
 * variables retrieved via nlist
E 61
 */
D 61
#define WNAMESIZ	12
#define WSNAMESIZ	6
#define WTSIZ		95
E 39
I 38

I 39
struct wchan {
	char	wc_name[WNAMESIZ+1];	/* symbolic name */
	caddr_t wc_caddr;		/* addr in kmem */
} *wchanhd;				/* an array sorted by wc_caddr */

#define NWCINDEX	10		/* the size of the index array */

caddr_t wchan_index[NWCINDEX];		/* used to speed searches */
/*
 * names listed here are not kept as wait channels -- this is used to 
 * remove names that confuse ps, like symbols that define the end of an
 * array that happen to be equal to the next symbol.
 */
char *wchan_stop_list[] = {
	"umbabeg",
	"umbaend",
	"calimit",
	NULL
E 61
I 61
struct	nlist psnl[] = {
	{"_ecmx"},
#define	X_ECMX		0
	{"_fscale"},
#define	X_FSCALE	1
	{"_ccpu"},
#define	X_CCPU		2
	{NULL}
E 61
};
I 61
int	fscale;
int	ecmx;
fixpt_t	ccpu;
E 61

E 39
E 38
D 8
struct	savcom savcom[NPROC];
E 8
D 61
int	npr;
E 61
I 61
#define USAGE	"ps [ -(o|O) fmt ] [ -wlvujnsaxSCLmcr ] [ -p pid ] [ -t tty ]"
E 61

E 71
D 61
int	cmdstart;
int	twidth;
I 34
D 35
struct winsize win;
E 35
I 35
struct	winsize win;
E 35
E 34
char	*kmemf, *memf, *swapf, *nlistf;
D 20
int	kmem, mem, swap;
E 20
I 20
int	kmem, mem, swap = -1;
E 20
I 4
D 5
int	rawcpu;
E 5
I 5
int	rawcpu, sumcpu;
E 5
E 4

int	pcbpf;
int	argaddr;
D 35
extern	char _sobuf[];
E 35

I 23
D 27
#define	pgtok(a)	((a)*CLBYTES/1024)
E 27
I 27
#define	pgtok(a)	((a)/(1024/NBPG))
E 27

E 23
main(argc, argv)
	char **argv;
E 61
I 61
D 69
main (argc, argv) 
E 69
I 69
D 70
main (argc, argv)
E 70
I 70
main(argc, argv)
	int argc;
E 70
E 69
D 71
	char *argv[];
E 71
I 71
D 88
	char **argv;
E 88
I 88
	char *argv[];
E 88
E 71
E 61
{
D 61
	register int i, j;
	register char *ap;
	int uid;
	off_t procp;
I 34
	int width;
E 61
I 61
D 88
	extern char *optarg;
	extern int optind;
D 69
	int ch; 
	register i;
E 69
I 69
D 71
	int ch;
	register int i;
E 69
	register struct var *v;
E 71
	register struct proc *p;
E 88
I 71
D 86
	register size_t nentries;
E 86
I 86
D 96
	register struct kinfo_proc *kp;
E 86
D 78
	register VAR *v;
E 78
I 78
	register struct varent *vent;
I 86
	int nentries;
E 86
E 78
	register int i;
E 96
I 96
	struct kinfo_proc *kp;
	struct varent *vent;
E 96
E 71
	struct winsize ws;
D 69
	struct kinfo_proc *kprocs;
	int nentries;
E 69
I 69
D 71
	size_t nentries;
E 69
	int fmt = 0;
E 71
I 71
	dev_t ttydev;
D 88
	int all, ch, flag, fmt, lineno, pid, prtheader, uid, what, xflg;
E 71
	int pscomp();
I 80
	char *nlistf, *memf, *swapf;
E 80
D 71
	int what, flag;
E 71
	char *kludge_oldps_options();
I 86
	char errbuf[80];
I 87
	int wflag = 0;
E 88
I 88
D 96
	int all, ch, flag, fmt, lineno, pid, prtheader, uid, wflag, what, xflg;
E 96
I 96
	pid_t pid;
	uid_t uid;
	int all, ch, flag, i, fmt, lineno, nentries;
	int prtheader, wflag, what, xflg;
E 96
	char *nlistf, *memf, *swapf, errbuf[256];
E 88
E 87
E 86
E 61
E 34

D 20
	if (chdir("/dev") < 0) {
		perror("/dev");
		exit(1);
	}
E 20
D 34
	twidth = 80;
E 34
I 34
D 43
	if (ioctl(0, TIOCGWINSZ, &win) == -1)
E 43
I 43
D 61
	if (ioctl(1, TIOCGWINSZ, &win) == -1)
E 43
		twidth = 80;
E 61
I 61
D 69
	if ((ioctl(1, TIOCGWINSZ, &ws) == -1 && 
	     ioctl(2, TIOCGWINSZ, &ws) == -1 &&
	     ioctl(0, TIOCGWINSZ, &ws) == -1) ||
E 69
I 69
D 71
	if ((ioctl(1, TIOCGWINSZ, (char *)&ws) == -1 &&
	     ioctl(2, TIOCGWINSZ, (char *)&ws) == -1 &&
	     ioctl(0, TIOCGWINSZ, (char *)&ws) == -1) ||
E 71
I 71
	if ((ioctl(STDOUT_FILENO, TIOCGWINSZ, (char *)&ws) == -1 &&
	     ioctl(STDERR_FILENO, TIOCGWINSZ, (char *)&ws) == -1 &&
	     ioctl(STDIN_FILENO,  TIOCGWINSZ, (char *)&ws) == -1) ||
E 71
E 69
	     ws.ws_col == 0)
		termwidth = 79;
E 61
	else
D 61
		twidth = (win.ws_col == 0 ? 80 : win.ws_col);
E 34
I 16
D 20

E 20
D 19
	if (ap = rindex(argv[0], '/'))		/* RAND 2/81 */
E 19
I 19
D 23
	if (ap = rindex(argv[0], '/'))
E 19
		ap++;
	else
		ap = argv[0];
	if (*ap == 's')				/* If name starts with 's' */
		ssflg++;

E 23
E 16
D 19
	setbuf(stdout, _sobuf);
E 19
	argc--, argv++;
	if (argc > 0) {
		ap = argv[0];
		while (*ap) switch (*ap++) {
E 61
I 61
		termwidth = ws.ws_col - 1;
I 71

E 71
	if (argc > 1)
		argv[1] = kludge_oldps_options(argv[1]);
E 61

I 4
D 61
		case 'C':
D 16
			rawcpu++;
E 16
I 16
D 23
			rawcpu++; nonssflg++;
E 23
I 23
			rawcpu++;
E 61
I 61
D 65
	while ((ch = getopt(argc, argv, "o:O:wlvujnsaxt:p:SCLmchT")) != EOF)
E 65
I 65
D 67
	while ((ch = getopt(argc, argv, "o:O:wlvujnsaxt:p:SCLmchTg")) != EOF)
E 67
I 67
D 71
	while ((ch = getopt(argc, argv, "o:O:wlvujnsaxt:p:SCLmrhTg")) != EOF)
E 71
I 71
D 88
	fmt = 0;
	all = xflg = 0;
E 88
I 88
D 92
	all = fmt = wflag = xflg = 0;
E 92
I 92
	all = fmt = prtheader = wflag = xflg = 0;
E 92
E 88
D 96
	pid = uid = -1;
E 96
I 96
	pid = -1;
	uid = (uid_t) -1;
E 96
	ttydev = NODEV;
D 75
	while ((ch = getopt(argc, argv, "aCghjLlmO:o:p:rSsTt:uvwx")) != EOF)
E 75
I 75
D 80
	while ((ch = getopt(argc, argv, "aCghjLlmO:o:p:rSTt:uvwx")) != EOF)
E 80
I 80
	memf = nlistf = swapf = NULL;
	while ((ch = getopt(argc, argv,
D 86
	    "aCghjLlM:mN:O:o:p:rSTt:uvW:wx")) != EOF)
E 86
I 86
	    "aCeghjLlM:mN:O:o:p:rSTt:uvW:wx")) != EOF)
E 86
E 80
E 75
E 71
E 67
E 65
		switch((char)ch) {
D 71
		case 'o':
			parsefmt(optarg);
			fmt++;
E 71
I 71
		case 'a':
			all = 1;
E 71
E 61
E 23
E 16
			break;
I 86
D 92
		case 'e':
			/* XXX set ufmt */
E 92
I 92
		case 'e':			/* XXX set ufmt */
E 92
			needenv = 1;
			break;
E 86
I 5
D 61
		case 'S':
			sumcpu++;
E 61
I 61
D 71
		case 'O':
			parsefmt("pid");
			parsefmt(optarg);
D 62
			parsefmt("stat tt time command");
E 62
I 62
			parsefmt("state tt time command");
E 62
			fmt++;
E 71
I 71
		case 'C':
			rawcpu = 1;
E 71
E 61
			break;
I 29
D 61

		case 'U':
			Uflg++;
E 61
I 61
D 71
		case 'w':
			if (termwidth < 131)
				termwidth = 131;
			else
				termwidth = UNLIMITED;
E 71
I 71
		case 'g':
D 92
			break;	/* no-op */
E 92
I 92
			break;			/* no-op */
E 92
		case 'h':
			prtheader = ws.ws_row > 5 ? ws.ws_row : 22;
E 71
E 61
			break;
I 71
		case 'j':
D 76
			parsefmt(JFMT);
E 76
I 76
			parsefmt(jfmt);
E 76
			fmt = 1;
I 83
			jfmt[0] = '\0';
E 83
			break;
D 86
		case 'L': 
E 86
I 86
		case 'L':
E 86
			showkey();
			exit(0);
E 71
D 61

E 29
E 5
E 4
		case 'a':
			aflg++;
E 61
I 61
		case 'l':
D 76
			parsefmt(LFMT);
E 76
I 76
			parsefmt(lfmt);
E 76
D 71
			fmt++;
E 71
I 71
			fmt = 1;
I 83
			lfmt[0] = '\0';
E 83
E 71
E 61
			break;
I 80
		case 'M':
			memf = optarg;
			break;
E 80
D 61
		case 'c':
D 16
			cflg = !cflg;
E 16
I 16
D 23
			cflg = !cflg; nonssflg++;
E 23
I 23
			cflg = !cflg;
E 61
I 61
D 71
		case 'v':
			parsefmt(VFMT);
E 71
I 71
		case 'm':
E 71
			sortby = SORTMEM;
D 71
			fmt++;
E 71
E 61
E 23
E 16
			break;
I 80
		case 'N':
			nlistf = optarg;
			break;
E 80
D 61
		case 'e':
D 16
			eflg++;
E 16
I 16
D 23
			eflg++; nonssflg++;
E 23
I 23
			eflg++;
E 61
I 61
D 71
		case 'u':
			parsefmt(UFMT);
E 71
I 71
		case 'O':
D 76
			parsefmt("pid");
E 76
I 76
			parsefmt(o1);
E 76
			parsefmt(optarg);
D 72
			parsefmt("state tname cputime command");
E 72
I 72
D 76
			parsefmt("tt state time command");
E 76
I 76
			parsefmt(o2);
I 83
			o1[0] = o2[0] = '\0';
E 83
E 76
E 72
			fmt = 1;
			break;
		case 'o':
			parsefmt(optarg);
			fmt = 1;
			break;
		case 'p':
D 96
			pid = atoi(optarg);
E 96
I 96
			pid = atol(optarg);
E 96
			xflg = 1;
			break;
		case 'r':
E 71
			sortby = SORTCPU;
D 71
			fmt++;
E 71
E 61
E 23
E 16
			break;
D 61
		case 'g':
D 16
			gflg++;
E 16
I 16
D 23
			gflg++; nonssflg++;
E 23
I 23
			gflg++;
E 23
E 16
			break;
E 61
I 60
D 71
		case 'j':
D 61
			jflg++;
E 61
I 61
			parsefmt(JFMT);
			fmt++;
E 71
I 71
		case 'S':
			sumrusage = 1;
E 71
E 61
			break;
E 60
D 61
		case 'k':
D 16
			kflg++;
E 16
I 16
D 23
			kflg++; nonssflg++;
E 23
I 23
			kflg++;
E 61
I 61
D 74
		case 's':
			parsefmt(SFMT);
D 71
			fmt++;
E 71
I 71
			fmt = 1;
E 71
E 61
E 23
E 16
			break;
E 74
D 61
		case 'l':
D 16
			lflg++;
E 16
I 16
D 23
			lflg++; nonssflg++;
E 23
I 23
			lflg++;
E 61
I 61
		case 'T':
I 69
D 71
			if ((optarg = ttyname(0)) == NULL)
				error("<stdin>: not a terminal");
E 71
I 71
			if ((optarg = ttyname(STDIN_FILENO)) == NULL)
D 81
				error("stdin: not a terminal");
E 81
I 81
D 92
				err("stdin: not a terminal");
E 92
I 92
				errx(1, "stdin: not a terminal");
E 92
E 81
E 71
			/* FALLTHROUGH */
E 69
		case 't': {
I 69
D 88
			char *ttypath;
E 69
			struct stat stbuf;
D 69
			char *tname, *ttyname();
			char termname[MAXPATHLEN+1];
E 69
I 69
			char pathbuf[MAXPATHLEN];
E 88
I 88
			struct stat sb;
			char *ttypath, pathbuf[MAXPATHLEN];
E 88
E 69

D 69
			if (ch == 'T') {
				if ((tname = ttyname(0)) == NULL)
					error("<stdin>: not a terminal");
			} else 
				tname = optarg;
			if (strlen(tname) == 2) {
				if (strcmp(tname, "co") == 0)
					strcpy(termname, "/dev/console");
				else {
					strcpy(termname, "/dev/tty");
					strcat(termname, tname);
				}
			} else if (*tname != '/') {
				strcpy(termname, "/dev/");
				strcat(termname, tname);
			} else
				strcpy(termname, tname);
			if (stat(termname, &stbuf) == -1)
				syserror(termname);
E 69
I 69
			if (strcmp(optarg, "co") == 0)
				ttypath = _PATH_CONSOLE;
			else if (*optarg != '/')
D 88
				(void) sprintf(ttypath = pathbuf, "%s%s",
				    _PATH_TTY, optarg);
E 88
I 88
				(void)snprintf(ttypath = pathbuf,
				    sizeof(pathbuf), "%s%s", _PATH_TTY, optarg);
E 88
			else
				ttypath = optarg;
D 71
			if (stat(ttypath, &stbuf) == -1)
				syserror(ttypath);
E 69
D 62
			if ((stbuf.st_mode&S_IFMT) != S_IFCHR)
E 62
I 62
			if ((stbuf.st_mode & S_IFMT) != S_IFCHR)
E 71
I 71
D 81
			if (stat(ttypath, &stbuf) == -1) {
				(void)fprintf(stderr,
D 74
				    "ps: %s: %s\n", strerror(ttypath));
E 74
I 74
				    "ps: %s: %s\n", ttypath, strerror(errno));
E 74
				exit(1);
			}
E 81
I 81
D 88
			if (stat(ttypath, &stbuf) == -1)
E 88
I 88
			if (stat(ttypath, &sb) == -1)
E 88
D 92
				err("%s: %s", ttypath, strerror(errno));
E 92
I 92
				err(1, "%s", ttypath);
E 92
E 81
D 88
			if (!S_ISCHR(stbuf.st_mode))
E 88
I 88
			if (!S_ISCHR(sb.st_mode))
E 88
E 71
E 62
D 69
				error("%s: not a terminal", termname);
E 69
I 69
D 81
				error("%s: not a terminal", ttypath);
E 81
I 81
D 92
				err("%s: not a terminal", ttypath);
E 92
I 92
				errx(1, "%s: not a terminal", ttypath);
E 92
E 81
E 69
D 88
			ttydev = stbuf.st_rdev;
E 88
I 88
			ttydev = sb.st_rdev;
E 88
E 61
E 23
E 16
			break;
I 39
D 61
		case 'n':
			nflg++;
E 61
I 61
		}
D 71
		case 'p':
			pid = atoi(optarg);
I 67
			xflg++;
E 71
I 71
		case 'u':
D 76
			parsefmt(UFMT);
E 76
I 76
			parsefmt(ufmt);
E 76
			sortby = SORTCPU;
			fmt = 1;
I 83
			ufmt[0] = '\0';
E 83
E 71
E 67
E 61
			break;
E 39
D 61
		case 's':
D 16
			sflg++;
E 16
I 16
D 23
			sflg++; nonssflg++;
E 23
I 23
			sflg++;
E 61
I 61
D 71
		case 'S':
			sumrusage++;
E 71
I 71
		case 'v':
D 76
			parsefmt(VFMT);
E 76
I 76
			parsefmt(vfmt);
E 76
			sortby = SORTMEM;
			fmt = 1;
I 83
			vfmt[0] = '\0';
E 83
E 71
E 61
E 23
E 16
			break;
I 80
		case 'W':
			swapf = optarg;
			break;
E 80
D 61
		case 't':
			if (*ap)
				tptr = ap;
I 24
D 36
			else if ((tptr = ttyname(2)) != 0) {
				strcpy(mytty, tptr);
				if ((tptr = index(mytty,'y')) != 0)
					tptr++;
E 36
I 36
			else if ((tptr = ttyname(0)) != 0) {
				tptr = strcpy(mytty, tptr);
D 57
				if (strncmp(tptr, "/dev/", 5) == 0)
E 57
I 57
				if (strncmp(tptr, _PATH_DEV,
				    sizeof(_PATH_DEV) - 1) == 0)
E 57
					tptr += 5;
E 61
I 61
D 71
		case 'C':
			rawcpu++;
E 71
I 71
		case 'w':
D 87
			if (termwidth < 131)
				termwidth = 131;
			else
E 87
I 87
			if (wflag)
E 87
				termwidth = UNLIMITED;
I 87
			else if (termwidth < 131)
				termwidth = 131;
			wflag++;
E 87
E 71
			break;
D 71
		case 'L': {
D 69
			int i = 0;
E 69
			struct combovar *cb = &combovar[0];
D 69
			char *cp;
E 69
I 69
			char *cp, *sep = "";
E 69

D 69
			v = &var[0];
			for (;;) {
				if (v->name[0] != NULL) {
					cp = v->name[0];
					v++;
				} else if (cb->name != NULL) {
					cp = cb->name;
					cb++;
				} else
E 69
I 69
			for (i = 0, v = &var[0];;) {
				if (v->name[0] != NULL)
					cp = v++->name[0];
				else if (cb->name != NULL)
					cp = cb++->name;
				else
E 69
					break;
D 69
				if (termwidth && 
				   (i += strlen(cp)+1) > termwidth)
					i = strlen(cp), printf("\n");
				printf("%s ", cp);
E 69
I 69
				if (termwidth &&
				    (i += strlen(cp) + 1) > termwidth)
					i = strlen(cp), sep = "\n";
				(void) printf("%s%s", sep, cp);
				sep = " ";
E 69
E 61
E 36
			}
I 36
D 61
			if (strncmp(tptr, "tty", 3) == 0)
				tptr += 3;
E 36
E 24
D 16
			aflg++;
E 16
I 16
D 23
			aflg++; nonssflg++;
E 23
I 23
			aflg++;
E 23
E 16
			gflg++;
D 23
			if (*tptr == '?')
E 23
I 23
			if (tptr && *tptr == '?')
E 23
				xflg++;
			while (*ap)
				ap++;
E 61
I 61
D 69
			printf("\n");
E 69
I 69
			(void) printf("\n");
E 69
			exit(0);
		}
		case 'a':
			all++;
E 61
			break;
E 71
D 16
		case 'u':
			uflg++;
E 16
I 16
D 61
		case 'u': 
D 23
			uflg++; nonssflg++;
E 23
I 23
			uflg++;
E 61
I 61
		case 'x':
D 71
			xflg++;
E 71
I 71
			xflg = 1;
E 71
E 61
E 23
E 16
			break;
D 61
		case 'v':
			cflg = 1;
D 16
			vflg++;
E 16
I 16
D 23
			vflg++; nonssflg++;
E 23
I 23
			vflg++;
E 61
I 61
D 71
		case 'm':
			sortby = SORTMEM;
E 61
E 23
E 16
			break;
D 61
		case 'w':
D 34
			if (twidth == 80)
E 34
I 34
			if (twidth < 132)
E 34
				twidth = 132;
			else
				twidth = BUFSIZ;
E 61
I 61
D 67
		case 'c':
E 67
I 67
		case 'r':
E 67
			sortby = SORTCPU;
E 61
			break;
D 61
		case 'x':
			xflg++;
E 61
I 61
		case 'h':
			prtheader = ws.ws_row > 5 ? ws.ws_row : 22;
E 61
			break;
I 65
		case 'g':
			break;	/* no-op */
E 71
E 65
I 61
		case '?':
E 61
I 16
D 23
		case 'y':		/* Rand 2/81 */
			ssflg++;
			break;
E 23
E 16
		default:
D 61
			if (!isdigit(ap[-1]))
				break;
			chkpid = atoi(--ap);
			*ap = 0;
D 16
			aflg++;
E 16
I 16
D 23
			aflg++;	nonssflg++;
E 23
I 23
			aflg++;
E 23
E 16
			xflg++;
			break;
		}
	}
I 16
D 19
	if (ssflg) {			/* RAND 2/81 */
E 19
I 19
D 23
	if (ssflg) {
E 19
		if (nonssflg) {
			fprintf (stderr, "Usage: ss [axwS]\n");
			exit(1);
		}
		uflg++;
		gflg++;
	}
E 23
D 20

E 20
E 16
	openfiles(argc, argv);
	getkvars(argc, argv);
I 20
D 29
	if (chdir("/dev") < 0) {
		perror("/dev");
		exit(1);
	}
E 20
	getdev();
E 29
	uid = getuid();
	printhdr();
D 8
	procp = nl[X_PROC].n_value;
	for (i=0; i<NPROC; i += 8) {
E 8
I 8
	procp = getw(nl[X_PROC].n_value);
	nproc = getw(nl[X_NPROC].n_value);
D 21
	hz = getw(nl[X_HZ].n_value);
E 21
D 29
	savcom = (struct savcom *)calloc(nproc, sizeof (*savcom));
	for (i=0; i<nproc; i += 8) {
E 29
I 29
	savcom = (struct savcom *)calloc((unsigned) nproc, sizeof (*savcom));
	for (i=0; i<nproc; i += NPROC) {
E 29
E 8
D 18
		lseek(kmem, (char *)procp, 0);
E 18
I 18
D 19
		klseek(kmem, (char *)procp, 0);
E 19
I 19
		klseek(kmem, (long)procp, 0);
E 19
E 18
D 8
		j = NPROC - i;
E 8
I 8
		j = nproc - i;
E 8
D 29
		if (j > 8)
			j = 8;
E 29
I 29
		if (j > NPROC)
			j = NPROC;
E 29
		j *= sizeof (struct proc);
D 20
		if (read(kmem, (char *)proc, j) != j)
E 20
I 20
		if (read(kmem, (char *)proc, j) != j) {
E 20
			cantread("proc table", kmemf);
E 61
I 61
D 69
			fprintf(stderr, "usage: %s\n", USAGE);
E 69
I 69
D 71
			(void) fprintf(stderr, "usage: %s\n", USAGE);
E 69
E 61
I 20
			exit(1);
E 71
I 71
			usage();
E 71
		}
E 20
D 61
		procp += j;
		for (j = j / sizeof (struct proc) - 1; j >= 0; j--) {
			mproc = &proc[j];
			if (mproc->p_stat == 0 ||
			    mproc->p_pgrp == 0 && xflg == 0)
D 2
			continue;
E 2
I 2
				continue;
E 2
			if (tptr == 0 && gflg == 0 && xflg == 0 &&
D 18
			    mproc->p_ppid == 1 && (mproc->p_flag&SDETACH) == 0)
E 18
I 18
			    mproc->p_ppid == 1)
E 18
				continue;
D 29
			if (uid != mproc->p_uid && aflg==0 ||
			    chkpid != 0 && chkpid != mproc->p_pid)
E 29
I 29
			if (uid != mproc->p_uid && aflg==0)
E 29
				continue;
I 29
D 42
			if (chkpid != 0 && chkpid != mproc->p_pid)
E 42
I 42
			if (chkpid != -1 && chkpid != mproc->p_pid)
E 42
				continue;
E 29
			if (vflg && gflg == 0 && xflg == 0) {
				if (mproc->p_stat == SZOMB ||
				    mproc->p_flag&SWEXIT)
					continue;
				if (mproc->p_slptime > MAXSLP &&
				    (mproc->p_stat == SSLEEP ||
				     mproc->p_stat == SSTOP))
				continue;
			}
			save();
E 61
I 61
	argc -= optind;
	argv += optind;
D 69
	
E 69
I 69

I 80
#define	BACKWARD_COMPATIBILITY
#ifdef	BACKWARD_COMPATIBILITY
E 80
E 69
	if (*argv) {
D 80
		char *nlistf, *memf = NULL, *swapf = NULL;
E 80
D 92

E 92
D 80
		nlistf = *argv++;
		if (*argv) {
			memf = *argv++;
			if (*argv)
				swapf = *argv++;
E 80
I 80
		nlistf = *argv;
		if (*++argv) {
			memf = *argv;
			if (*++argv)
				swapf = *argv;
E 80
E 61
		}
I 61
D 80
		if (kvm_openfiles(nlistf, memf, swapf) == -1)
			error("kvm_openfiles: %s", kvm_geterr());
E 80
E 61
	}
I 80
#endif
I 85
	/*
	 * Discard setgid privileges if not the running kernel so that bad
	 * guys can't print interesting stuff from kernel memory.
	 */
	if (nlistf != NULL || memf != NULL || swapf != NULL)
		setgid(getgid());

E 85
D 86
	if (kvm_openfiles(nlistf, memf, swapf) == -1)
D 81
		error("kvm_openfiles: %s", kvm_geterr());
E 81
I 81
		err("kvm_openfiles: %s", kvm_geterr());
E 86
I 86
	kd = kvm_openfiles(nlistf, memf, swapf, O_RDONLY, errbuf);
	if (kd == 0)
D 92
		err("%s", errbuf);
E 92
I 92
		errx(1, "%s", errbuf);
E 92
E 86
E 81
E 80
I 34
D 61
	width = twidth - cmdstart - 2;
	if (width < 0)
		width = 0;
E 34
D 29
	qsort(savcom, npr, sizeof(savcom[0]), pscomp);
E 29
I 29
	qsort((char *) savcom, npr, sizeof(savcom[0]), pscomp);
E 29
I 16
D 19
	if (ssflg) {			/* RAND 2/81 */
E 19
I 19
D 23
	if (ssflg) {
E 19
		walk(npr);
		exit (npr == 0);
	}
E 23
E 16
	for (i=0; i<npr; i++) {
		register struct savcom *sp = &savcom[i];
		if (lflg)
			lpr(sp);
I 60
		else if (jflg)
			jpr(sp);
E 60
		else if (vflg)
			vpr(sp);
		else if (uflg)
			upr(sp);
		else
			spr(sp);
D 36
		if (sp->ap->a_flag & SWEXIT)
			printf(" <exiting>");
		else if (sp->ap->a_stat == SZOMB)
E 36
I 36
		if (sp->ap->a_stat == SZOMB)
E 36
D 54
			printf(" <defunct>");
E 54
I 54
			printf(" %.*s", twidth - cmdstart - 2, "<defunct>");
E 54
I 36
		else if (sp->ap->a_flag & SWEXIT)
D 54
			printf(" <exiting>");
E 54
I 54
			printf(" %.*s", twidth - cmdstart - 2, "<exiting>");
E 54
E 36
		else if (sp->ap->a_pid == 0)
D 54
			printf(" swapper");
E 54
I 54
			printf(" %.*s", twidth - cmdstart - 2, "swapper");
E 54
		else if (sp->ap->a_pid == 2)
D 54
			printf(" pagedaemon");
E 54
I 54
			printf(" %.*s", twidth - cmdstart - 2, "pagedaemon");
E 54
I 11
D 36
		else if (sp->ap->a_pid == 3 && sp->ap->a_flag & SSYS)
D 14
			printf(" net input");
E 14
I 14
			printf(" ip input");
E 36
E 14
E 11
		else
			printf(" %.*s", twidth - cmdstart - 2, sp->ap->a_cmdp);
		printf("\n");
E 61
I 61

	if (!fmt)
D 76
		parsefmt(DFMT);
E 76
I 76
		parsefmt(dfmt);
E 76

	if (!all && ttydev == NODEV && pid == -1)  /* XXX - should be cleaner */
		uid = getuid();

	/*
	 * scan requested variables, noting what structures are needed,
	 * and adjusting header widths as appropiate.
	 */
	scanvars();
I 67
D 70
#ifdef notdef
E 70
E 67
D 71
	if (sortby == SORTCPU)
		neednlist = 1;
I 67
D 70
#endif
E 70
E 67
	if (neednlist)
		donlist();
E 71
	/*
	 * get proc list
	 */
D 96
	if (uid != -1) {
E 96
I 96
	if (uid != (uid_t) -1) {
E 96
D 90
		what = KINFO_PROC_UID;
E 90
I 90
		what = KERN_PROC_UID;
E 90
		flag = uid;
	} else if (ttydev != NODEV) {
D 90
		what = KINFO_PROC_TTY;
E 90
I 90
		what = KERN_PROC_TTY;
E 90
		flag = ttydev;
	} else if (pid != -1) {
D 90
		what = KINFO_PROC_PID;
E 90
I 90
		what = KERN_PROC_PID;
E 90
		flag = pid;
E 61
D 66
D 67
	}
E 67
I 67
D 92
	} else
E 92
I 92
	} else {
E 92
D 90
		what = KINFO_PROC_ALL;
E 90
I 90
		what = KERN_PROC_ALL;
I 92
		flag = 0;
	}
E 92
E 90
E 67
E 66
I 66
D 68
	} else
		what = KINFO_PROC_ALL;
E 68
E 66
D 61
	exit(npr == 0);
E 61
I 61
	/*
	 * select procs
	 */
D 81
	if ((nentries = kvm_getprocs(what, flag)) == -1) {
D 69
		fprintf(stderr, "ps: %s\n", kvm_geterr());
E 69
I 69
		(void) fprintf(stderr, "ps: %s\n", kvm_geterr());
E 69
		exit(1);
	}
D 71
	kinfo = (struct kinfo *)malloc(nentries * sizeof (struct kinfo));
	if (kinfo == NULL)
		error("out of memory");
	i = 0;
	while ((p = kvm_nextproc()) != NULL) {
		kinfo[i].ki_p = p;
		kinfo[i].ki_e = kvm_geteproc(p);
E 71
I 71
	kinfo = (KINFO *)malloc(nentries * sizeof(KINFO));
	if (kinfo == NULL) {
		(void)fprintf(stderr, "ps: %s\n", strerror(ENOMEM));
		exit(1);
	}
E 81
I 81
D 86
	if ((nentries = kvm_getprocs(what, flag)) == -1)
		err("%s", kvm_geterr());
	kinfo = malloc(nentries * sizeof(KINFO));
E 86
I 86
	if ((kp = kvm_getprocs(kd, what, flag, &nentries)) == 0)
D 92
		err("%s", kvm_geterr(kd));
	kinfo = malloc(nentries * sizeof(*kinfo));
E 86
	if (kinfo == NULL)
		err("%s", strerror(errno));
E 92
I 92
		errx(1, "%s", kvm_geterr(kd));
	if ((kinfo = malloc(nentries * sizeof(*kinfo))) == NULL)
		err(1, NULL);
E 92
E 81
D 86
	for (nentries = 0; p = kvm_nextproc(); ++nentries) {
		kinfo[nentries].ki_p = p;
		kinfo[nentries].ki_e = kvm_geteproc(p);
E 86
I 86
	for (i = nentries; --i >= 0; ++kp) {
		kinfo[i].ki_p = kp;
E 86
E 71
		if (needuser)
D 71
			saveuser(&kinfo[i]);
		i++;
E 71
I 71
D 86
			saveuser(&kinfo[nentries]);
E 86
I 86
			saveuser(&kinfo[i]);
E 86
E 71
	}
D 71
	nentries = i;
E 71
	/*
	 * print header
	 */
	printheader();
	if (nentries == 0)
		exit(0);
	/*
	 * sort proc list
	 */
D 69
	qsort(kinfo, nentries, sizeof (struct kinfo), pscomp);
E 69
I 69
D 71
	qsort((void *)kinfo, nentries, sizeof (struct kinfo), pscomp);
E 71
I 71
D 88
	qsort((void *)kinfo, nentries, sizeof(KINFO), pscomp);
E 88
I 88
	qsort(kinfo, nentries, sizeof(KINFO), pscomp);
E 88
E 71
E 69
	/*
	 * for each proc, call each variable output function.
	 */
D 71
	for (i = 0; i < nentries; i++) {
E 71
I 71
	for (i = lineno = 0; i < nentries; i++) {
E 71
D 64
		if (xflg == 0 && kinfo[i].ki_e->e_tdev == NODEV)
E 64
I 64
D 86
		if (xflg == 0 && (kinfo[i].ki_e->e_tdev == NODEV ||
		    (kinfo[i].ki_p->p_flag & SCTTY ) == 0))
E 86
I 86
		if (xflg == 0 && (KI_EPROC(&kinfo[i])->e_tdev == NODEV ||
D 94
		    (KI_PROC(&kinfo[i])->p_flag & SCTTY ) == 0))
E 94
I 94
		    (KI_PROC(&kinfo[i])->p_flag & P_CONTROLT ) == 0))
E 94
E 86
E 64
			continue;
D 71
		for (v = vhead; v != NULL; v = v->next) {
E 71
I 71
D 78
		for (v = vhead; v; v = v->next) {
E 71
			(*v->oproc)(&kinfo[i], v);
			if (v->next != NULL)
E 78
I 78
		for (vent = vhead; vent; vent = vent->next) {
D 88
			(*vent->var->oproc)(&kinfo[i], vent->var, vent->next);
E 88
I 88
			(vent->var->oproc)(&kinfo[i], vent);
E 88
			if (vent->next != NULL)
E 78
D 69
				putchar(' ');
E 69
I 69
D 88
				(void) putchar(' ');
E 88
I 88
				(void)putchar(' ');
E 88
E 69
		}
D 69
		putchar('\n');
E 69
I 69
D 88
		(void) putchar('\n');
E 88
I 88
		(void)putchar('\n');
E 88
E 69
D 92
		if (prtheader && lineno++ == prtheader-4) {
E 92
I 92
		if (prtheader && lineno++ == prtheader - 4) {
E 92
D 69
			putchar('\n');
E 69
I 69
D 88
			(void) putchar('\n');
E 88
I 88
			(void)putchar('\n');
E 88
E 69
			printheader();
			lineno = 0;
		}
	}
D 71

	exit(0);
E 71
I 71
	exit(eval);
E 71
E 61
}

I 88
static void
E 88
I 8
D 61
getw(loc)
D 19
	off_t loc;
E 19
I 19
	unsigned long loc;
E 61
I 61
D 71
#define FMTSEP	" \t,\n"

parsefmt(fmt)
	char *fmt;
E 61
E 19
{
D 29
	long word;
E 29
I 29
D 61
	int word;
E 61
I 61
D 69
	register char *f = fmt, *cp, *hp;
E 69
I 69
	register char *cp, *hp;
E 69
	struct var *v;
D 69
	char *strtok(), *index();
	char newbuf[1024], *nb = newbuf; /* XXX */
E 69
	char *lookupcombo();
	struct var *lookupvar();
D 69
	
	/*
	 * strtok is not &^%^& re-entrant, so we have
	 * only one level of expansion, looking for combo
	 * variables once here, and expanding the string
	 * before really parsing it.  With strtok_r,
	 * you would move the expansion to before the
	 * lookupvar inside the 2nd while loop with a
	 * recursive call to parsefmt.
	 */
	while ((cp = strtok(f, FMTSEP)) != NULL) {
		if ((hp = lookupcombo(cp)) == NULL);
			hp = cp;
		if (((nb + strlen(hp)) - newbuf) >= 1024)
			error("format too large");
		strcpy(nb, hp);
		while (*nb)
			nb++;
		*nb++ = ' ';
		*nb =  '\0';
		f = NULL;
	}
	f = newbuf;
	while ((cp = strtok(f, FMTSEP)) != NULL) {
		if (hp = index(cp, '='))
E 69
I 69

	while (fmt) {
		while ((cp = strsep(&fmt, FMTSEP)) != NULL && *cp == '\0')
			/* void */;
		if ((hp = lookupcombo(cp)) != NULL) {
			parsefmt(hp);
			continue;
		}
		if ((hp = index(cp, '=')) != NULL)
E 69
			*hp++ = '\0';
		v = lookupvar(cp);
		if (v == NULL)
			error("unknown variable in format: %s", cp);
D 69
		if (v->next != NULL || vtail == v)
			error("can't specify a variable twice: %s", cp);
E 69
I 69
		if (v->next != NULL || vtail == v) {
			(void) fprintf(stderr,
			    "ps: can't specify a variable twice: %s\n", cp);
			continue;
		}
E 69
		if (hp)
			v->header = hp;
		if (vhead == NULL)
			vhead = vtail = v;
		else {
			vtail->next = v;
			vtail = v;
		}
D 69
		f = NULL;	/* for strtok */
E 69
	}
E 61
E 29
D 69

E 69
D 18
	lseek(kmem, loc, 0);
E 18
I 18
D 19
	klseek(kmem, loc, 0);
E 18
	if (read(kmem, &word, sizeof (word)) != sizeof (word))
E 19
I 19
D 61
	klseek(kmem, (long)loc, 0);
	if (read(kmem, (char *)&word, sizeof (word)) != sizeof (word))
E 19
		printf("error reading kmem at %x\n", loc);
	return (word);
E 61
}

E 71
I 18
D 61
klseek(fd, loc, off)
D 19
	int fd, loc, off;
E 19
I 19
	int fd;
	long loc;
	int off;
E 61
I 61
scanvars()
E 61
E 19
{
I 78
D 96
	register struct varent *vent;
E 78
D 29

	if (kflg)
		loc &= 0x7fffffff;
E 29
I 29
D 61
	if (kflg) {
		if ((loc = vtophys(loc)) == -1)
			return;
E 61
I 61
D 71
	register i;
	register struct var *v;
E 71
I 71
	register VAR *v;
	register int i;
E 96
I 96
	struct varent *vent;
	VAR *v;
	int i;
E 96
E 71

D 71
	for (v = vhead; v != NULL; v = v->next) {
E 71
I 71
D 78
	for (v = vhead; v; v = v->next) {
E 78
I 78
	for (vent = vhead; vent; vent = vent->next) {
		v = vent->var;
E 78
E 71
		i = strlen(v->header);
		if (v->width < i)
			v->width = i;
		totwidth += v->width + 1;	/* +1 for space */
		if (v->flag & USER)
			needuser = 1;
		if (v->flag & COMM)
			needcomm = 1;
D 71
		if (v->flag & NLIST)
			neednlist = 1;
E 71
E 61
	}
E 29
D 19
	lseek(fd, loc, off);
E 19
I 19
D 61
	(void) lseek(fd, (long)loc, off);
E 61
I 61
	totwidth--;
E 61
E 19
}
I 69

I 86
D 88
extern char *fmt_argv __P((char **, char *, int));
E 86
E 69
I 61
D 71
printheader()
{
	register struct var *v;
E 71
E 61

E 88
I 44
D 61
/*
 * Version allows change of db format w/o temporarily bombing ps's
 */
char thisversion[4] = "V2";		/* length must remain 4 */
E 61
I 61
D 71
	for (v = vhead; v != NULL; v = v->next) {
		if (v->flag & LJUST) {
			if (v->next == NULL)	/* last one */
D 69
				printf("%s", v->header);
E 69
I 69
				(void) printf("%s", v->header);
E 69
			else
D 69
				printf("%-*s",v->width, v->header);
E 69
I 69
				(void) printf("%-*s", v->width, v->header);
E 69
		} else
D 69
			printf("%*s",v->width, v->header);
E 69
I 69
			(void) printf("%*s", v->width, v->header);
E 69
		if (v->next != NULL)
D 69
			putchar(' ');
E 69
I 69
			(void) putchar(' ');
E 69
	}
D 69
	putchar('\n');
E 69
I 69
	(void) putchar('\n');
E 69
}
E 61

E 44
I 29
D 61
writepsdb(unixname)
	char *unixname;
E 61
I 61
D 69
command(k, v) 
E 69
I 69
command(k, v)
E 69
	struct kinfo *k;
	struct var *v;
E 61
{
D 39
	int nllen;
E 39
D 61
	register FILE *fp;
I 38
	struct lttys *lt;
I 44
	struct stat stb;
E 61
E 44
E 38

I 36
D 61
	setgid(getgid());
E 36
	setuid(getuid());
	if ((fp = fopen(psdb, "w")) == NULL) {
		perror(psdb);
		exit(1);
E 61
I 61
D 69
	if (v->next == NULL) {		
E 69
I 69
	if (v->next == NULL) {
E 69
		/* last field */
		if (termwidth == UNLIMITED)
D 69
			printf("%s", k->ki_args);
E 69
I 69
			(void) printf("%s", k->ki_args);
E 69
		else {
D 69
			register left = termwidth - (totwidth - v->width);
E 69
I 69
			register int left = termwidth - (totwidth - v->width);
E 69
			register char *cp = k->ki_args;

D 69
			if (left < 1)	/* already wrapped, just use std width */
E 69
I 69
			if (left < 1) /* already wrapped, just use std width */
E 69
				left = v->width;
D 69
			while (left-- && *cp)
				putchar(*cp++);
E 69
I 69
			while (--left >= 0 && *cp)
				(void) putchar(*cp++);
E 69
		}
E 61
	} else
D 61
		fchmod(fileno(fp), 0644);
E 61
I 61
D 69
		printf("%-*.*s", v->width, v->width, k->ki_args);
		
E 69
I 69
		(void) printf("%-*.*s", v->width, v->width, k->ki_args);

E 69
}
E 61
I 44

D 46
	fwrite(thisversion, sizeof (thisversion), 1, fp);
E 46
I 46
D 61
	fwrite(thisversion, sizeof thisversion, 1, fp);
E 46
	fwrite(unixname, strlen(unixname) + 1, 1, fp);
	if (stat(unixname, &stb) < 0)
		stb.st_mtime = 0;
D 46
	fwrite((char *) &stb.st_mtime, sizeof (stb.st_mtime), 1, fp);
E 46
I 46
	fwrite((char *) &stb.st_mtime, sizeof stb.st_mtime, 1, fp);
E 61
I 61
D 69
ucomm(k, v) 
E 69
I 69
ucomm(k, v)
E 69
	struct kinfo *k;
	struct var *v;
{
E 61
E 46

E 44
D 39
	nllen = sizeof nl / sizeof (struct nlist);
E 39
D 61
	fwrite((char *) &nllen, sizeof nllen, 1, fp);
	fwrite((char *) nl, sizeof (struct nlist), nllen, fp);
I 38
	fwrite((char *) cand, sizeof (cand), 1, fp);
E 38
	fwrite((char *) &nttys, sizeof nttys, 1, fp);
D 38
	fwrite((char *) allttys, sizeof (struct ttys), nttys, fp);
E 38
I 38
	for (lt = lallttys ; lt ; lt = lt->next)
		fwrite((char *)&lt->ttys, sizeof (struct ttys), 1, fp);
I 39
	fwrite((char *) &nchans, sizeof nchans, 1, fp);
	fwrite((char *) wchanhd, sizeof (struct wchan), nchans, fp);
	fwrite((char *) wchan_index, sizeof (caddr_t), NWCINDEX, fp);
E 39
E 38
D 44
	fwrite(unixname, strlen(unixname) + 1, 1, fp);
E 44
	fclose(fp);
E 61
I 61
D 69
	printf("%-*s", v->width, k->ki_p->p_comm);
E 69
I 69
	(void) printf("%-*s", v->width, k->ki_p->p_comm);
E 69
E 61
}

D 61
readpsdb(unixname)
	char *unixname;
E 61
I 61
D 69
logname(k, v) 
E 69
I 69
logname(k, v)
E 69
	struct kinfo *k;
	struct var *v;
E 61
{
D 39
	int nllen;
E 39
D 61
	register i;
	register FILE *fp;
	char unamebuf[BUFSIZ];
	char *p	= unamebuf;
I 44
	char dbversion[sizeof thisversion];
	struct stat stb;
	time_t dbmtime;
E 44
	extern int errno;
E 61

D 61
	if ((fp = fopen(psdb, "r")) == NULL) {
		if (errno == ENOENT)
			return (0);
		perror(psdb);
		exit(1);
	}
E 61
I 61
D 69
	printf("%-*s", v->width, k->ki_p->p_logname);
E 69
I 69
	(void) printf("%-*s", v->width, k->ki_p->p_logname);
E 69
}
E 61

I 44
D 61
	/*
	 * Does the db file match this unix?
	 */
	fread(dbversion, sizeof dbversion, 1, fp);
	if (bcmp(thisversion, dbversion, sizeof thisversion))
		goto bad;
	while ((*p = getc(fp)) != '\0')
		p++;
	if (strcmp(unixname, unamebuf))
		goto bad;
	fread((char *) &dbmtime, sizeof dbmtime, 1, fp);
	if (stat(unixname, &stb) < 0)
		stb.st_mtime = 0;
	if (stb.st_mtime != dbmtime)
		goto bad;
E 61
I 61
state(k, v)
	struct kinfo *k;
	struct var *v;
{
D 62
	char buf[6];
	char *cp = buf;
	struct proc *p = k->ki_p;
E 62
I 62
	char buf[16];
	register char *cp = buf;
	register struct proc *p = k->ki_p;
	register flag = p->p_flag;
E 62
E 61

E 44
D 61
	fread((char *) &nllen, sizeof nllen, 1, fp);
I 39
	nl = (struct nlist *) malloc (nllen * sizeof (struct nlist));
E 39
	fread((char *) nl, sizeof (struct nlist), nllen, fp);
I 38
	fread((char *) cand, sizeof (cand), 1, fp);
E 38
	fread((char *) &nttys, sizeof nttys, 1, fp);
I 38
	allttys = (struct ttys *)malloc(sizeof(struct ttys)*nttys);
	if (allttys == NULL) {
		fprintf(stderr, "ps: Can't malloc space for tty table\n");
		exit(1);
E 61
I 61
	switch (p->p_stat) {

	case SSTOP:
		*cp = 'T';
		break;

	case SSLEEP:
D 62
		if (p->p_pri > PZERO)
			if (p->p_slptime >= MAXSLP)
				*cp = 'I';
			else
				*cp = 'S';
		else if (p->p_flag & SPAGE)
			*cp = 'P';
		else
			*cp = 'D';
E 62
I 62
		if (flag & SSINTR)	/* interuptable (long) */
			*cp = p->p_slptime >= MAXSLP ? 'I' : 'S';
D 69
		else 
E 69
I 69
		else
E 69
			*cp = (flag & SPAGE) ? 'P' : 'D';
E 62
		break;

D 62
	case SWAIT:
E 62
	case SRUN:
	case SIDL:
		*cp = 'R';
		break;

	case SZOMB:
		*cp = 'Z';
		break;

	default:
		*cp = '?';
E 61
	}
E 38
D 61
	fread((char *) allttys, sizeof (struct ttys), nttys, fp);
I 39
	fread((char *) &nchans, sizeof nchans, 1, fp);
	wchanhd = (struct wchan *) malloc(nchans * sizeof (struct wchan));
	if (wchanhd == NULL) {
		fprintf(stderr, "ps: Can't malloc space for wait channels\n");
		nflg++;
		fseek(fp, (long) nchans * sizeof (struct wchan), 1);
E 61
I 61
	cp++;
D 62
	if (p->p_flag & SLOAD) {
E 62
I 62
	if (flag & SLOAD) {
E 62
		if (p->p_rssize > p->p_maxrss)
			*cp++ = '>';
E 61
	} else
D 61
		fread((char *) wchanhd, sizeof (struct wchan), nchans, fp);
	fread((char *) wchan_index, sizeof (caddr_t), NWCINDEX, fp);
E 39
D 44
	while ((*p = getc(fp)) != '\0')
		p++;
	return (strcmp(unixname, unamebuf) == 0);
E 44
I 44
	fclose(fp);
	return(1);

bad:
	fclose(fp);
	return(0);
E 61
I 61
		*cp++ = 'W';
	if (p->p_nice < NZERO)
		*cp++ = '<';
	else if (p->p_nice > NZERO)
		*cp++ = 'N';
D 62
	if (p->p_flag & SUANOM)
E 62
I 62
	if (flag & SUANOM)
E 62
		*cp++ = 'A';
D 62
	else if (p->p_flag & SSEQL)
E 62
I 62
	else if (flag & SSEQL)
E 62
		*cp++ = 'S';
D 62
	if (p->p_flag&SCTTY && k->ki_e->e_tpgid == k->ki_e->e_pgid)
E 62
I 62
	if (flag & STRC)
		*cp++ = 'X';
	if (flag & SWEXIT)
		*cp++ = 'E';
	if (flag & SVFORK)
		*cp++ = 'V';
	if (flag & (SSYS|SLOCK|SULOCK|SKEEP|SPHYSIO))
		*cp++ = 'L';
D 67
	if ((flag & SCTTY) && k->ki_e->e_pgid == k->ki_e->e_pgid)
E 67
I 67
	if (k->ki_e->e_flag & EPROC_SLEADER)
		*cp++ = 's';
	if ((flag & SCTTY) && k->ki_e->e_pgid == k->ki_e->e_tpgid)
E 67
E 62
		*cp++ = '+';
	*cp = '\0';
D 69
	printf("%-*s", v->width, buf);
E 69
I 69
	(void) printf("%-*s", v->width, buf);
E 69
E 61
E 44
}

E 29
E 18
E 8
D 61
openfiles(argc, argv)
	char **argv;
E 61
I 61
pri(k, v)
	struct kinfo *k;
	struct var *v;
E 61
{

D 20
	kmemf = "kmem";
E 20
I 20
D 57
	kmemf = "/dev/kmem";
E 57
I 57
D 61
	kmemf = _PATH_KMEM;
E 57
E 20
	if (kflg)
D 20
		kmemf = argc > 1 ? argv[1] : "/vmcore";
E 20
I 20
D 57
		kmemf = argc > 2 ? argv[2] : "/vmcore";
E 57
I 57
		kmemf = argc > 2 ? argv[2] : _PATH_VMCORE;
E 57
E 20
	kmem = open(kmemf, 0);
	if (kmem < 0) {
		perror(kmemf);
		exit(1);
	}
	if (kflg)  {
		mem = kmem;
		memf = kmemf;
	} else {
D 20
		memf = "mem";
E 20
I 20
D 57
		memf = "/dev/mem";
E 57
I 57
		memf = _PATH_MEM;
E 57
E 20
		mem = open(memf, 0);
		if (mem < 0) {
			perror(memf);
			exit(1);
		}
	}
D 20
	swapf = argc>2 ? argv[2]: "drum";
	swap = open(swapf, 0);
	if (swap < 0) {
		perror(swapf);
		exit(1);
E 20
I 20
	if (kflg == 0 || argc > 3) {
D 57
		swapf = argc>3 ? argv[3]: "/dev/drum";
E 57
I 57
		swapf = argc>3 ? argv[3]: _PATH_DRUM;
E 57
		swap = open(swapf, 0);
		if (swap < 0) {
			perror(swapf);
			exit(1);
		}
E 20
	}
E 61
I 61
D 69
	printf("%*d", v->width, k->ki_p->p_pri - PZERO);
E 69
I 69
	(void) printf("%*d", v->width, k->ki_p->p_pri - PZERO);
E 69
E 61
}

D 61
getkvars(argc, argv)
	char **argv;
E 61
I 61
uname(k, v)
	struct kinfo *k;
	struct var *v;
E 61
{
I 39
D 61
	int faildb = 0;			/* true if psdatabase init failed */
I 44
	int i;
E 61
E 44
E 39
D 29
	register struct nlist *nlp;
E 29

D 20
	nlistf = argc > 3 ? argv[3] : "/vmunix";
E 20
I 20
D 57
	nlistf = argc > 1 ? argv[1] : "/vmunix";
E 57
I 57
D 61
	nlistf = argc > 1 ? argv[1] : _PATH_UNIX;
E 57
E 20
D 29
	nlist(nlistf, nl);
E 29
I 29
	if (Uflg) {
I 39
		init_nlist();
E 39
		nlist(nlistf, nl);
I 39
		getvchans();
E 39
		getdev();
		writepsdb(nlistf);
		exit (0);
	} else if (!readpsdb(nlistf)) {
I 39
		init_nlist();
E 39
		if (!kflg)
D 39
			nl[X_SYSMAP].n_name = "";
E 39
I 39
			nl[X_SYSMAP].n_un.n_name = "";
		faildb = 1;
E 39
		nlist(nlistf, nl);
I 31
D 36
		nttys =  0;
E 36
I 36
		nttys = 0;
E 36
E 31
		getdev();
	}
E 61
I 61
D 69
	printf("%-*s", v->width, user_from_uid(k->ki_p->p_uid, 0));
E 69
I 69
	(void) printf("%-*s", v->width, user_from_uid(k->ki_p->p_uid, 0));
E 69
}
E 61

E 29
D 61
	if (nl[0].n_type == 0) {
		fprintf(stderr, "%s: No namelist\n", nlistf);
		exit(1);
	}
D 29
	if (kflg)
		for (nlp = nl; nlp < &nl[sizeof (nl)/sizeof (nl[0])]; nlp++)
			nlp->n_value = clear(nlp->n_value);
I 20
	usrpt = (struct pte *)nl[X_USRPT].n_value;	/* don't clear!! */
E 20
	Usrptma = (struct pte *)nl[X_USRPTMA].n_value;
E 29
I 29
	if (kflg) {
		/* We must do the sys map first because klseek uses it */
		long	addr;
E 61
I 61
runame(k, v)
	struct kinfo *k;
	struct var *v;
{
E 61

D 61
		Syssize = nl[X_SYSSIZE].n_value;
		Sysmap = (struct pte *)
			calloc((unsigned) Syssize, sizeof (struct pte));
		if (Sysmap == NULL) {
			fprintf(stderr, "Out of space for Sysmap\n");
			exit(1);
		}
		addr = (long) nl[X_SYSMAP].n_value;
D 48
		addr &= ~0x80000000;
E 48
I 48
		addr &= ~KERNBASE;
E 48
		(void) lseek(kmem, addr, 0);
		read(kmem, (char *) Sysmap, Syssize * sizeof (struct pte));
	}
I 39
	if (faildb)
		getvchans();
E 39
	usrpt = (struct pte *)nl[X_USRPT].n_value;
	Usrptmap = (struct pte *)nl[X_USRPTMAP].n_value;
E 29
D 20
	usrpt = (struct pte *)nl[X_USRPT].n_value;
E 20
D 18
	lseek(kmem, (long)nl[X_NSWAP].n_value, 0);
E 18
I 18
	klseek(kmem, (long)nl[X_NSWAP].n_value, 0);
E 18
D 19
	if (read(kmem, &nswap, sizeof (nswap)) != sizeof (nswap)) {
E 19
I 19
	if (read(kmem, (char *)&nswap, sizeof (nswap)) != sizeof (nswap)) {
E 19
		cantread("nswap", kmemf);
		exit(1);
	}
I 2
D 18
	lseek(kmem, (long)nl[X_MAXSLP].n_value, 0);
E 18
I 18
D 59
	klseek(kmem, (long)nl[X_MAXSLP].n_value, 0);
E 18
D 19
	if (read(kmem, &maxslp, sizeof (maxslp)) != sizeof (maxslp)) {
E 19
I 19
	if (read(kmem, (char *)&maxslp, sizeof (maxslp)) != sizeof (maxslp)) {
E 19
		cantread("maxslp", kmemf);
		exit(1);
	}
E 59
I 3
D 18
	lseek(kmem, (long)nl[X_CCPU].n_value, 0);
E 18
I 18
	klseek(kmem, (long)nl[X_CCPU].n_value, 0);
E 18
D 19
	if (read(kmem, &ccpu, sizeof (ccpu)) != sizeof (ccpu)) {
E 19
I 19
	if (read(kmem, (char *)&ccpu, sizeof (ccpu)) != sizeof (ccpu)) {
E 19
		cantread("ccpu", kmemf);
		exit(1);
	}
E 3
E 2
D 4
	if (vflg) {
E 4
I 4
D 18
	lseek(kmem, (long)nl[X_ECMX].n_value, 0);
E 18
I 18
	klseek(kmem, (long)nl[X_ECMX].n_value, 0);
E 18
D 19
	if (read(kmem, &ecmx, sizeof (ecmx)) != sizeof (ecmx)) {
E 19
I 19
	if (read(kmem, (char *)&ecmx, sizeof (ecmx)) != sizeof (ecmx)) {
E 19
		cantread("ecmx", kmemf);
		exit(1);
	}
	if (uflg || vflg) {
E 4
D 8
		text = (struct text *)alloc(NTEXT * sizeof (struct text));
E 8
I 8
		ntext = getw(nl[X_NTEXT].n_value);
D 29
		text = (struct text *)alloc(ntext * sizeof (struct text));
E 29
I 29
		text = (struct text *)
			calloc((unsigned) ntext, sizeof (struct text));
E 29
E 8
		if (text == 0) {
			fprintf(stderr, "no room for text table\n");
			exit(1);
		}
D 8
		lseek(kmem, (long)nl[X_TEXT].n_value, 0);
		if (read(kmem, (char *)text, NTEXT * sizeof (struct text))
		    != NTEXT * sizeof (struct text)) {
E 8
I 8
		atext = (struct text *)getw(nl[X_TEXT].n_value);
D 18
		lseek(kmem, (int)atext, 0);
E 18
I 18
D 19
		klseek(kmem, (int)atext, 0);
E 19
I 19
		klseek(kmem, (long)atext, 0);
E 19
E 18
		if (read(kmem, (char *)text, ntext * sizeof (struct text))
		    != ntext * sizeof (struct text)) {
E 8
			cantread("text table", kmemf);
			exit(1);
		}
	}
I 26
	dmmin = getw(nl[X_DMMIN].n_value);
	dmmax = getw(nl[X_DMMAX].n_value);
I 58
	fscale = getw(nl[X_FSCALE].n_value);
E 61
I 61
D 69
	printf("%-*s", v->width, user_from_uid(k->ki_p->p_ruid, 0));
E 69
I 69
	(void) printf("%-*s", v->width, user_from_uid(k->ki_p->p_ruid, 0));
E 69
E 61
E 58
E 26
}

I 39
D 61
/*
 * get the valloc'ed kernel variables for symbolic wait channels
 */
getvchans()
E 61
I 61
tdev(k, v)
	struct kinfo *k;
	struct var *v;
E 61
{
D 61
	int i, tmp;
E 61
I 61
	dev_t dev = k->ki_e->e_tdev;
E 61

D 61
	if (nflg)
		return;
E 61
I 61
	if (dev == NODEV)
D 69
		printf("%*s", v->width, "??");
E 69
I 69
		(void) printf("%*s", v->width, "??");
E 69
	else {
		char buff[16];
E 61

D 61
#define addv(i) 	addchan(&nl[i].n_un.n_name[1], getw(nl[i].n_value))
D 59
	addv(X_INODE);
E 59
I 59
	addv(X_VNODE);
E 59
	addv(X_FILE);
	addv(X_PROC);
	addv(X_TEXT);
	addv(X_CFREE);
	addv(X_CALLOUT);
	addv(X_SWAPMAP);
	addv(X_ARGMAP);
	addv(X_KERNELMAP);
	addv(X_MBMAP);
	addv(X_NCH);
	if (nl[X_QUOTA].n_value != 0) {	/* these are #ifdef QUOTA */
		addv(X_QUOTA);
		addv(X_DQUOT);
E 61
I 61
D 69
		sprintf(buff, "%d/%d", major(dev), minor(dev));
		printf("%*s", v->width, buff);
E 69
I 69
		(void) sprintf(buff, "%d/%d", major(dev), minor(dev));
		(void) printf("%*s", v->width, buff);
E 69
E 61
	}
D 61
	addv(X_SWBUF);
	addv(X_BUF);
	addv(X_CMAP);
	addv(X_BUFFERS);
	qsort(wchanhd, nchans, sizeof (struct wchan), wchancomp);
	for (i = 0; i < NWCINDEX; i++) {
		tmp = i * nchans;
		wchan_index[i] = wchanhd[tmp / NWCINDEX].wc_caddr;
	}
#undef addv
E 61
}
E 39
D 61
printhdr()
E 61
I 61

D 63
char *devname();
E 63
I 63
extern char *devname();
E 63

tname(k, v)
	struct kinfo *k;
	struct var *v;
E 61
{
D 61
	char *hdr;
E 61
I 61
	dev_t dev = k->ki_e->e_tdev;
D 69
	char *tname;
E 69
I 69
	char *ttname;
E 69
E 61

D 61
	if (sflg+lflg+vflg+uflg > 1) {
		fprintf(stderr, "ps: specify only one of s,l,v and u\n");
		exit(1);
E 61
I 61
D 63
	if (dev == NODEV || (tname = devname(dev, 1)) == NULL)
E 63
I 63
D 69
	if (dev == NODEV || (tname = devname(dev, S_IFCHR)) == NULL)
E 63
		printf("%-*s", v->width, "??");
E 69
I 69
	if (dev == NODEV || (ttname = devname(dev, S_IFCHR)) == NULL)
		(void) printf("%-*s", v->width, "??");
E 69
	else {
D 69
		if (strncmp(tname, "tty", 3) == 0)
			tname += 3;
D 62
		printf("%-*.*s", v->width, v->width, tname);
E 62
I 62
		printf("%*.*s%c", v->width-1, v->width-1, tname,
E 69
I 69
		if (strncmp(ttname, "tty", 3) == 0)
			ttname += 3;
		(void) printf("%*.*s%c", v->width-1, v->width-1, ttname,
E 69
D 67
			k->ki_p->p_flag & SCTTY ? ' ' : '-');
E 67
I 67
			k->ki_e->e_flag & EPROC_CTTY ? ' ' : '-');
E 67
E 62
E 61
	}
D 16
	hdr = lflg ? lhdr : (vflg ? vhdr : (uflg ? uhdr : shdr));
E 16
I 16
D 19
	hdr = ssflg ? sshdr : 		/* RAND 2/81 */
E 19
I 19
D 23
	hdr = ssflg ? sshdr :
E 19
		(lflg ? lhdr : 
E 23
I 23
D 39
	hdr = lflg ? lhdr : 
E 23
			(vflg ? vhdr : 
D 23
				(uflg ? uhdr : shdr))); 
E 23
I 23
				(uflg ? uhdr : shdr));
E 39
I 39
D 61
	if (lflg) {
		if (nflg)
			wcwidth = 6;
		else if (twidth > WTSIZ)
			wcwidth = -WNAMESIZ;
		else
			wcwidth = -WSNAMESIZ;
		if ((hdr = malloc(strlen(lhdr) + WNAMESIZ)) == NULL) {
			fprintf(stderr, "ps: out of memory\n");
			exit(1);
		}
D 49
		sprintf(hdr, lhdr, wcwidth, "WCHAN");
E 49
I 49
		(void)sprintf(hdr, lhdr, wcwidth, "WCHAN");
E 49
	} else if (vflg)
		hdr = vhdr;
D 60
	else if (uflg) {
E 60
I 60
	else if (jflg) {
		hdr = jhdr;
	} else if (uflg) {
E 60
		/* add enough on so that it can hold the sprintf below */
		if ((hdr = malloc(strlen(uhdr) + 10)) == NULL) {
			fprintf(stderr, "ps: out of memory\n");
			exit(1);
		}
D 49
		sprintf(hdr, uhdr, nflg ? " UID" : "USER    ");
E 49
I 49
		(void)sprintf(hdr, uhdr, nflg ? " UID" : "USER    ");
E 49
	} else
		hdr = shdr;
E 39
E 23
E 16
D 60
	if (lflg+vflg+uflg+sflg == 0)
E 60
I 60
	if (lflg+vflg+uflg+sflg+jflg == 0)	/* this code is ICK */
E 60
D 2
		hdr += strlen(" SSIZ");
E 2
I 2
		hdr += strlen("SSIZ ");
E 2
	cmdstart = strlen(hdr);
	printf("%s COMMAND\n", hdr);
D 19
	fflush(stdout);
E 19
I 19
	(void) fflush(stdout);
E 61
E 19
}

D 61
cantread(what, fromwhat)
	char *what, *fromwhat;
E 61
I 61
longtname(k, v)
	struct kinfo *k;
	struct var *v;
E 61
{
I 61
	dev_t dev = k->ki_e->e_tdev;
D 69
	char *tname;
E 69
I 69
	char *ttname;
E 69
E 61

D 20
	fprintf(stderr, "ps: error reading %s from %s", what, fromwhat);
E 20
I 20
D 61
	fprintf(stderr, "ps: error reading %s from %s\n", what, fromwhat);
E 61
I 61
D 63
	if (dev == NODEV || (tname = devname(dev, 1)) == NULL)
E 63
I 63
D 69
	if (dev == NODEV || (tname = devname(dev, S_IFCHR)) == NULL)
E 63
		printf("%-*s", v->width, "??");
E 69
I 69
	if (dev == NODEV || (ttname = devname(dev, S_IFCHR)) == NULL)
		(void) printf("%-*s", v->width, "??");
E 69
	else
D 69
		printf("%-*s", v->width, tname);
E 69
I 69
		(void) printf("%-*s", v->width, ttname);
E 69
E 61
E 20
}

D 19
struct	direct dbuf;
E 19
I 19
D 61
struct	direct *dbuf;
E 19
int	dialbase;
E 61
I 61
#include <sys/time.h>
E 61

D 61
getdev()
E 61
I 61
started(k, v)
	struct kinfo *k;
	struct var *v;
E 61
{
D 19
	register FILE *df;
	register struct ttys *dp;
E 19
I 19
D 61
	register DIR *df;
I 38
	struct ttys *t;
	struct lttys *lt;
E 61
I 61
	extern char *attime();
E 61
E 38
E 19

I 29
D 57
	if (chdir("/dev") < 0) {
		perror("/dev");
E 57
I 57
D 61
	if (chdir(_PATH_DEV) < 0) {
		perror(_PATH_DEV);
E 57
		exit(1);
	}
E 29
	dialbase = -1;
D 19
	if ((df = fopen(".", "r")) == NULL) {
E 19
I 19
	if ((df = opendir(".")) == NULL) {
E 19
D 57
		fprintf(stderr, "Can't open . in /dev\n");
E 57
I 57
		fprintf(stderr, "ps: can't open . in %s\n", _PATH_DEV);
E 57
		exit(1);
	}
D 19
	while (fread((char *)&dbuf, sizeof(dbuf), 1, df) == 1) {
		if (dbuf.d_ino == 0)
			continue;
		maybetty(dp);
	}
	fclose(df);
E 19
I 19
	while ((dbuf = readdir(df)) != NULL) 
		maybetty();
	closedir(df);
I 38
	allttys = (struct ttys *)malloc(sizeof(struct ttys)*nttys);
	if (allttys == NULL) {
D 57
		fprintf(stderr, "ps: Can't malloc space for tty table\n");
E 57
I 57
		fprintf(stderr, "ps: can't malloc space for tty table\n");
E 57
		exit(1);
	}
	for (lt = lallttys, t = allttys; lt ; lt = lt->next, t++)
		*t = lt->ttys;
E 61
I 61
D 69
	printf("%-*s", v->width, k->ki_u ? 
E 69
I 69
	(void) printf("%-*s", v->width, k->ki_u ?
E 69
		attime(&k->ki_u->u_start.tv_sec) : "-");
D 69
		
E 69
I 69

E 69
E 61
E 38
E 19
}

D 61
/*
 * Attempt to avoid stats by guessing minor device
 * numbers from tty names.  Console is known,
 * know that r(hp|up|mt) are unlikely as are different mem's,
 * floppy, null, tty, etc.
 */
maybetty()
E 61
I 61
lstarted(k, v)
	struct kinfo *k;
	struct var *v;
E 61
{
D 19
	register char *cp = dbuf.d_name;
E 19
I 19
D 61
	register char *cp = dbuf->d_name;
E 19
D 38
	register struct ttys *dp;
E 38
I 38
	static struct lttys *dp;
	struct lttys *olddp;
E 38
	int x;
	struct stat stb;
E 61
I 61
	extern char *ctime();
D 69
	char *tp; 
E 69
I 69
	char *tp;
E 69
E 61

D 61
	switch (cp[0]) {
E 61
I 61
	if (k->ki_u)
		(tp = ctime(&k->ki_u->u_start.tv_sec))[24] = '\0';
	else
		tp = "-";
D 69
	printf("%-*s", v->width, tp);
E 69
I 69
	(void) printf("%-*s", v->width, tp);
E 69
}
E 61

D 61
	case 'c':
		if (!strcmp(cp, "console")) {
			x = 0;
			goto donecand;
		}
		/* cu[la]? are possible!?! don't rule them out */
		break;
E 61
I 61
wchan(k, v)
	struct kinfo *k;
	struct var *v;
{
E 61

D 61
	case 'd':
		if (!strcmp(cp, "drum"))
D 19
			return (0);
E 19
I 19
			return;
E 19
		break;

	case 'f':
		if (!strcmp(cp, "floppy"))
D 19
			return (0);
E 19
I 19
			return;
E 19
		break;

	case 'k':
		cp++;
		if (*cp == 'U')
			cp++;
		goto trymem;

	case 'r':
		cp++;
D 31
		if (*cp == 'r' || *cp == 'u' || *cp == 'h')
			cp++;
E 31
#define is(a,b) cp[0] == 'a' && cp[1] == 'b'
D 31
		if (is(r,p) || is(u,p) || is(r,k) || is(r,m) || is(m,t)) {
E 31
I 31
D 35
		if (is(h,p) || is(r,a) || is(u,p) || is(r,k) 
		    || is(r,m) || is(m,t)) {
E 35
I 35
		if (is(h,p) || is(r,a) || is(u,p) || is(h,k) 
		    || is(r,b) || is(m,t)) {
E 35
E 31
			cp += 2;
			if (isdigit(*cp) && cp[2] == 0)
D 19
				return (0);
E 19
I 19
				return;
E 19
		}
		break;

	case 'm':
trymem:
		if (cp[0] == 'm' && cp[1] == 'e' && cp[2] == 'm' && cp[3] == 0)
D 19
			return (0);
E 19
I 19
			return;
E 19
I 14
		if (cp[0] == 'm' && cp[1] == 't')
D 19
			return (0);
E 19
I 19
			return;
E 19
E 14
		break;

	case 'n':
		if (!strcmp(cp, "null"))
I 35
			return;
		if (!strncmp(cp, "nrmt", 4))
			return;
		break;

	case 'p':
		if (cp[1] && cp[1] == 't' && cp[2] == 'y')
E 35
D 19
			return (0);
E 19
I 19
			return;
E 19
		break;

	case 'v':
		if ((cp[1] == 'a' || cp[1] == 'p') && isdigit(cp[2]) &&
		    cp[3] == 0)
D 19
			return (0);
E 19
I 19
			return;
E 19
		break;
	}
D 19
mightbe:
	cp = dbuf.d_name;
	while (cp < &dbuf.d_name[DIRSIZ] && *cp)
		cp++;
	--cp;
E 19
I 19
	cp = dbuf->d_name + dbuf->d_namlen - 1;
E 19
	x = 0;
	if (cp[-1] == 'd') {
		if (dialbase == -1) {
			if (stat("ttyd0", &stb) == 0)
				dialbase = stb.st_rdev & 017;
			else
				dialbase = -2;
		}
		if (dialbase == -2)
			x = 0;
E 61
I 61
	if (k->ki_p->p_wchan) {
		if (k->ki_p->p_pri > PZERO)
D 69
			printf("%-*.*s", v->width, v->width, k->ki_e->e_wmesg);
E 69
I 69
			(void) printf("%-*.*s", v->width, v->width, k->ki_e->e_wmesg);
E 69
E 61
		else
D 61
			x = 11;
	}
D 19
	if (cp > dbuf.d_name && isdigit(cp[-1]) && isdigit(*cp))
E 19
I 19
	if (cp > dbuf->d_name && isdigit(cp[-1]) && isdigit(*cp))
E 19
		x += 10 * (cp[-1] - ' ') + cp[0] - '0';
	else if (*cp >= 'a' && *cp <= 'f')
		x += 10 + *cp - 'a';
	else if (isdigit(*cp))
		x += *cp - '0';
	else
		x = -1;
donecand:
D 29
	dp = (struct ttys *)alloc(sizeof (struct ttys));
E 29
I 29
D 38
	if (nttys >= MAXTTYS) {
		fprintf(stderr, "ps: tty table overflow\n");
E 38
I 38
	olddp = dp;
	dp = (struct lttys *)malloc(sizeof(struct lttys));
	if (dp == NULL) {
		fprintf(stderr, "ps: Can't malloc space for tty table\n");
E 38
		exit(1);
	}
D 38
	dp = &allttys[nttys++];
E 29
D 19
	strncpy(dp->name, dbuf.d_name, DIRSIZ);
E 19
I 19
	(void) strcpy(dp->name, dbuf->d_name);
E 38
I 38
	if (lallttys == NULL)
		lallttys = dp;
	nttys++;
	if (olddp)
		olddp->next = dp;
	dp->next = NULL;
	(void) strcpy(dp->ttys.name, dbuf->d_name);
E 38
E 19
D 29
	dp->next = allttys;
	dp->ttyd = -1;
	allttys = dp;
E 29
I 29
	if (Uflg) {
D 38
		if (stat(dp->name, &stb) == 0 &&
E 38
I 38
		if (stat(dp->ttys.name, &stb) == 0 &&
E 38
		   (stb.st_mode&S_IFMT)==S_IFCHR)
D 38
			dp->ttyd = x = stb.st_rdev;
E 38
I 38
			dp->ttys.ttyd = x = stb.st_rdev;
E 38
		else {
			nttys--;
I 38
			if (lallttys == dp)
				lallttys = NULL;
			free(dp);
			dp = olddp;
			if (dp)
				dp->next = NULL;
E 38
			return;
		}
E 61
I 61
D 69
			printf("%*x", v->width, 
E 69
I 69
			(void) printf("%*x", v->width,
E 69
				(int)k->ki_p->p_wchan &~ KERNBASE);
E 61
	} else
D 38
		dp->ttyd = -1;
E 38
I 38
D 61
		dp->ttys.ttyd = -1;
E 38
E 29
	if (x == -1)
		return;
	x &= 017;
D 38
	dp->cand = cand[x];
	cand[x] = dp;
E 38
I 38
	dp->ttys.cand = cand[x];
	cand[x] = nttys-1;
E 61
I 61
D 69
		printf("%-*s", v->width, "-");
E 69
I 69
		(void) printf("%-*s", v->width, "-");
E 69
E 61
E 38
}

D 61
char *
D 60
gettty()
E 60
I 60
gettty(dev)
	dev_t dev;
E 61
I 61
D 66
D 67
#define pgtok(a)        ((a)/(1024/NBPG))
E 67
I 67
#define pgtok(a)        (((a)*NBPG)/1024)
E 67
E 66
I 66
D 70
#define pgtok(a)        (((a)*NBPG)/1024)
E 70
E 66

vsize(k, v)
	struct kinfo *k;
	struct var *v;
E 61
E 60
{
D 61
	register char *p;
	register struct ttys *dp;
	struct stat stb;
	int x;
E 61

D 60
	if (u.u_ttyp == 0)
D 55
		return("?");
E 55
I 55
		return(" ?");
E 55
	x = u.u_ttyd & 017;
E 60
I 60
D 61
	x = dev & 017;
E 60
D 38
	for (dp = cand[x]; dp; dp = dp->cand) {
E 38
I 38
	for (dp = &allttys[cand[x]]; dp != &allttys[-1];
	     dp = &allttys[dp->cand]) {
E 38
		if (dp->ttyd == -1) {
D 2
			if (stat(dp->name, &stb) == 0)
E 2
I 2
			if (stat(dp->name, &stb) == 0 &&
			   (stb.st_mode&S_IFMT)==S_IFCHR)
E 2
				dp->ttyd = stb.st_rdev;
			else
				dp->ttyd = -2;
		}
D 60
		if (dp->ttyd == u.u_ttyd)
E 60
I 60
		if (dp->ttyd == dev)
E 60
			goto found;
	}
	/* ick */
D 29
	for (dp = allttys; dp; dp = dp->next) {
E 29
I 29
	for (dp = allttys; dp < &allttys[nttys]; dp++) {
E 29
		if (dp->ttyd == -1) {
D 14
			if (stat(dp->name, &stb) == 0)
E 14
I 14
			if (stat(dp->name, &stb) == 0 &&
			   (stb.st_mode&S_IFMT)==S_IFCHR)
E 14
				dp->ttyd = stb.st_rdev;
			else
				dp->ttyd = -2;
		}
D 60
		if (dp->ttyd == u.u_ttyd)
E 60
I 60
		if (dp->ttyd == dev)
E 60
			goto found;
	}
	return ("?");
found:
	p = dp->name;
	if (p[0]=='t' && p[1]=='t' && p[2]=='y')
		p += 3;
	return (p);
E 61
I 61
D 69
	printf("%*d", v->width, 
E 69
I 69
	(void) printf("%*d", v->width,
E 69
		pgtok(k->ki_p->p_dsize + k->ki_p->p_ssize + k->ki_e->e_xsize));
E 61
}

D 61
save()
E 61
I 61
rssize(k, v)
	struct kinfo *k;
	struct var *v;
E 61
{
D 61
	register struct savcom *sp;
	register struct asav *ap;
	register char *cp;
I 4
	register struct text *xp;
E 4
D 60
	char *ttyp, *cmdp;
E 60
I 60
	char *ttyp = "?", *cmdp;
	struct pgrp pgrp;
	struct pgrp tpgrp;
	struct session session;
	struct tty tty;
	int hasctty = 0;
E 61
E 60

D 61
	if (mproc->p_stat != SZOMB && getu() == 0)
		return;
D 60
	ttyp = gettty();
E 60
I 60
	sp = &savcom[npr];
	sp->ap = ap = (struct asav *)calloc(1, sizeof (struct asav));
	ap->a_pgid = -1;
	ap->a_session = -1;
	ap->a_ttyd = -1;
	ap->a_tsession = -1;
	ap->a_tpgid = -1;
	klseek(kmem, mproc->p_pgrp, 0);
	if (read(kmem, &pgrp, sizeof(pgrp)) != sizeof(pgrp))
		fprintf(stderr, "ps: can't read pgrp\n");
	else {
		ap->a_pgid = pgrp.pg_id;
		ap->a_session = (int)pgrp.pg_session;
		klseek(kmem, pgrp.pg_session, 0);
		if (read(kmem, &session, sizeof(session)) != sizeof(session))
			fprintf(stderr, "ps: can't read session\n");
		else {
			if (session.s_ttyp != 0) {
				klseek(kmem, session.s_ttyp, 0);
				if (read(kmem, &tty, sizeof(tty)) == sizeof(tty)) {
					ttyp = gettty(tty.t_dev);
					ap->a_ttyd = tty.t_dev;
					ap->a_tsession = (int)tty.t_session;
					if (tty.t_pgrp != 0) {
						klseek(kmem, tty.t_pgrp, 0);
						if (read(kmem, &tpgrp, sizeof(tpgrp)) ==
						    sizeof(tpgrp))
							ap->a_tpgid = tpgrp.pg_id;
					}
				} else
					fprintf(stderr, "ps: can't read tty\n");
			}
		}
	}
E 60
D 16
	if (xflg == 0 && ttyp[0] == '?' || tptr && strcmpn(tptr, ttyp, 2))
E 16
I 16
	if (xflg == 0 && ttyp[0] == '?' || tptr && strncmp(tptr, ttyp, 2))
E 16
		return;
D 60
	sp = &savcom[npr];
E 60
	cmdp = getcmd();
	if (cmdp == 0)
		return;
D 29
	sp->ap = ap = (struct asav *)alloc(sizeof (struct asav));
E 29
I 29
D 60
	sp->ap = ap = (struct asav *)calloc(1, sizeof (struct asav));
E 60
E 29
	sp->ap->a_cmdp = cmdp;
#define e(a,b) ap->a = mproc->b
	e(a_flag, p_flag); e(a_stat, p_stat); e(a_nice, p_nice);
D 2
	e(a_uid, p_uid); e(a_pid, p_pid); e(a_rss, p_rssize);
E 2
I 2
D 4
	e(a_uid, p_uid); e(a_pid, p_pid); e(a_rss, p_rssize); e(a_pri, p_pri);
E 4
I 4
	e(a_uid, p_uid); e(a_pid, p_pid); e(a_pri, p_pri);
E 4
	e(a_slptime, p_slptime); e(a_time, p_time);
E 2
D 4
#undef e
E 4
	ap->a_tty[0] = ttyp[0];
	ap->a_tty[1] = ttyp[1] ? ttyp[1] : ' ';
	if (ap->a_stat == SZOMB) {
D 23
		register struct xproc *xp = (struct xproc *)mproc;

E 23
D 2
		ap->a_time = xp->xp_vm.vm_utime + xp->xp_vm.vm_stime;
E 2
I 2
D 21
		ap->a_cpu = xp->xp_vm.vm_utime + xp->xp_vm.vm_stime;
E 21
I 21
		ap->a_cpu = 0;
E 21
E 2
	} else {
		ap->a_size = mproc->p_dsize + mproc->p_ssize;
I 4
		e(a_rss, p_rssize); 
E 4
D 60
		ap->a_ttyd = u.u_ttyd;
E 60
D 2
		ap->a_time = u.u_vm.vm_utime + u.u_vm.vm_stime;
E 2
I 2
D 21
		ap->a_cpu = u.u_vm.vm_utime + u.u_vm.vm_stime;
E 21
I 21
		ap->a_cpu = u.u_ru.ru_utime.tv_sec + u.u_ru.ru_stime.tv_sec;
E 21
I 5
		if (sumcpu)
D 21
			ap->a_cpu += u.u_cvm.vm_utime + u.u_cvm.vm_stime;
E 21
I 21
			ap->a_cpu += u.u_cru.ru_utime.tv_sec + u.u_cru.ru_stime.tv_sec;
E 21
E 5
I 4
D 6
		if (mproc->p_textp) {
E 6
I 6
		if (mproc->p_textp && text) {
E 6
D 8
			xp = &text[mproc->p_textp -
				    (struct text *)nl[X_TEXT].n_value];
E 8
I 8
			xp = &text[mproc->p_textp - atext];
E 8
			ap->a_tsiz = xp->x_size;
			ap->a_txtrss = xp->x_rssize;
			ap->a_xccount = xp->x_ccount;
		}
E 4
E 2
	}
I 60
	e(a_ppid, p_ppid); 
E 60
I 4
#undef e
E 4
D 2
	ap->a_time /= HZ;
E 2
I 2
D 8
	ap->a_cpu /= HZ;
E 8
I 8
D 21
	ap->a_cpu /= hz;
E 21
I 9
	ap->a_maxrss = mproc->p_maxrss;
E 9
E 8
E 2
	if (lflg) {
		register struct lsav *lp;
E 61
I 61
D 69
	printf("%*d", v->width, 
		pgtok(k->ki_p->p_rssize + (k->ki_e->e_xccount ? 
E 69
I 69
	(void) printf("%*d", v->width,
		pgtok(k->ki_p->p_rssize + (k->ki_e->e_xccount ?
E 69
		      (k->ki_e->e_xrssize / k->ki_e->e_xccount) : 0)));
}
E 61

D 23
		sp->sun.lp = lp = (struct lsav *)alloc(sizeof (struct lsav));
E 23
I 23
D 29
		sp->s_un.lp = lp = (struct lsav *)alloc(sizeof (struct lsav));
E 29
I 29
D 61
		sp->s_un.lp = lp = (struct lsav *)
			calloc(1, sizeof (struct lsav));
E 29
E 23
#define e(a,b) lp->a = mproc->b
D 2
		e(l_ppid, p_ppid); e(l_cpu, p_cpu); e(l_pri, p_pri);
E 2
I 2
D 60
		e(l_ppid, p_ppid); e(l_cpu, p_cpu);
E 60
I 60
		e(l_cpu, p_cpu);
E 60
E 2
		if (ap->a_stat != SZOMB)
			e(l_wchan, p_wchan);
#undef e
		lp->l_addr = pcbpf;
	} else if (vflg) {
		register struct vsav *vp;
E 61
I 61
p_rssize(k, v)		/* doesn't account for text */
	struct kinfo *k;
	struct var *v;
{
E 61
D 4
		register struct text *xp;
E 4

D 23
		sp->sun.vp = vp = (struct vsav *)alloc(sizeof (struct vsav));
E 23
I 23
D 29
		sp->s_un.vp = vp = (struct vsav *)alloc(sizeof (struct vsav));
E 29
I 29
D 61
		sp->s_un.vp = vp = (struct vsav *)
			calloc(1, sizeof (struct vsav));
E 29
E 23
#define e(a,b) vp->a = mproc->b
D 2
		e(v_slptime, p_slptime); e(v_pri, p_pri);
E 2
		if (ap->a_stat != SZOMB) {
D 3
			e(v_swrss, p_swrss); e(v_aveflt, p_aveflt);
E 3
I 3
			e(v_swrss, p_swrss);
E 3
D 4
			vp->v_minflt = u.u_vm.vm_minflt;
E 4
D 21
			vp->v_majflt = u.u_vm.vm_majflt;
E 21
I 21
			vp->v_majflt = u.u_ru.ru_majflt;
E 21
D 4
			if (mproc->p_textp) {
				xp = &text[mproc->p_textp -
				    (struct text *)nl[X_TEXT].n_value];
				vp->v_tsiz = xp->x_size;
				vp->v_txtrss = xp->x_rssize;
E 4
I 4
			if (mproc->p_textp)
E 4
				vp->v_txtswrss = xp->x_swrss;
D 4
				vp->v_xccount = xp->x_ccount;
			}
E 4
		}
I 3
		vp->v_pctcpu = pcpu();
E 3
#undef e
D 16
	} else if (uflg)
D 3
		sp->sun.u_pctcpu = 0.0;
E 3
I 3
		sp->sun.u_pctcpu = pcpu();
E 3
	else if (sflg) {
E 16
I 16
D 23
	} else if (uflg) {
D 19
		if (!ssflg) 		/* RAND 2/18 */
E 19
I 19
		if (!ssflg)
E 19
			sp->sun.u_pctcpu = pcpu();
		else {
			register struct sssav *ssp;

			sp->sun.ssp =ssp= (struct sssav *)alloc(sizeof (struct sssav));
			ssp->ss_ppid = mproc->p_ppid;
		}
	} else if (sflg) {
E 23
I 23
	} else if (uflg)
		sp->s_un.u_pctcpu = pcpu();
	else if (sflg) {
E 23
E 16
		if (ap->a_stat != SZOMB) {
			for (cp = (char *)u.u_stack;
D 8
			    cp < &user.upages[UPAGES][NBPG]; )
E 8
I 8
			    cp < &user.upages[UPAGES][0]; )
E 8
				if (*cp++)
					break;
D 8
			sp->sun.s_ssiz = (&user.upages[UPAGES][NBPG] - cp);
E 8
I 8
D 23
			sp->sun.s_ssiz = (&user.upages[UPAGES][0] - cp);
E 23
I 23
			sp->s_un.s_ssiz = (&user.upages[UPAGES][0] - cp);
E 23
E 8
		}
	}
I 16

E 16
	npr++;
E 61
I 61
D 69
	printf("%*d", v->width, pgtok(k->ki_p->p_rssize));
E 69
I 69
	(void) printf("%*d", v->width, pgtok(k->ki_p->p_rssize));
E 69
E 61
}

I 3
D 61
double
I 4
pmem(ap)
	register struct asav *ap;
E 61
I 61
cputime(k, v)
	struct kinfo *k;
	struct var *v;
E 61
{
D 61
	double fracmem;
	int szptudot;
E 61
I 61
	long secs;
D 65
	char obuff[8];
E 65
I 65
	long psecs;	/* "parts" of a second. first micro, then centi */
	char obuff[128];
E 65
E 61

D 61
	if ((ap->a_flag&SLOAD) == 0)
		fracmem = 0.0;
E 61
I 61
D 65
	if (k->ki_p->p_stat == SZOMB || k->ki_u == NULL)
E 65
I 65
	if (k->ki_p->p_stat == SZOMB || k->ki_u == NULL) {
E 65
		secs = 0;
E 61
D 65
	else {
E 65
I 65
		psecs = 0;
	} else {
E 65
D 61
		szptudot = UPAGES + clrnd(ctopt(ap->a_size+ap->a_tsiz));
		fracmem = ((float)ap->a_rss+szptudot)/CLSIZE/ecmx;
		if (ap->a_xccount)
			fracmem += ((float)ap->a_txtrss)/CLSIZE/
			    ap->a_xccount/ecmx;
E 61
I 61
D 62
		secs = k->ki_u->u_ru.ru_utime.tv_sec + 
			k->ki_u->u_ru.ru_stime.tv_sec;
E 62
I 62
D 69
		secs = k->ki_p->p_utime.tv_sec + 
E 69
I 69
		secs = k->ki_p->p_utime.tv_sec +
E 69
			k->ki_p->p_stime.tv_sec;
E 62
D 65
		if (sumrusage)
E 65
I 65
D 69
		psecs = k->ki_p->p_utime.tv_usec + 
E 69
I 69
		psecs = k->ki_p->p_utime.tv_usec +
E 69
			k->ki_p->p_stime.tv_usec;
		if (sumrusage) {
E 65
D 69
			secs += k->ki_u->u_cru.ru_utime.tv_sec + 
E 69
I 69
			secs += k->ki_u->u_cru.ru_utime.tv_sec +
E 69
				k->ki_u->u_cru.ru_stime.tv_sec;
I 65
D 69
			psecs += k->ki_u->u_cru.ru_utime.tv_usec + 
E 69
I 69
			psecs += k->ki_u->u_cru.ru_utime.tv_usec +
E 69
				k->ki_u->u_cru.ru_stime.tv_usec;
		}
		/*
		 * round and scale to 100's
		 */
		psecs = (psecs + 5000) / 10000;
		if (psecs >= 100) {
			psecs -= 100;
			secs++;
		}
E 65
E 61
	}
D 61
	return (100.0 * fracmem);
E 61
I 61
D 65
	sprintf(obuff, "%3ld:%02ld", secs/60, secs%60);
E 65
I 65
D 69
	sprintf(obuff, "%3ld:%02ld.%02ld", secs/60, secs%60, psecs);
E 65
	printf("%*s", v->width, obuff);
E 69
I 69
	(void) sprintf(obuff, "%3ld:%02ld.%02ld", secs/60, secs%60, psecs);
	(void) printf("%*s", v->width, obuff);
E 69
E 61
}

I 58
D 61
#define	fxtofl(fixpt)	((double) fixpt / fscale)
E 61
E 58
double
E 4
D 61
pcpu()
E 61
I 61
getpcpu(k)
	struct kinfo *k;
E 61
{
I 4
D 61
	time_t time;
E 61
I 61
	/*
	 * note: this routine requires ccpu and fscale
	 * be initialized.  If you call this routine from
	 * somewhere new, insure that the "neednlist" flag
	 * gets set.
	 */
	struct proc *p = k->ki_p;
#define	fxtofl(fixpt)	((double)(fixpt) / fscale)
E 61
E 4

D 4
	if (mproc->p_time == 0 || (mproc->p_flag&SLOAD) == 0)
E 4
I 4
D 61
	time = mproc->p_time;
	if (time == 0 || (mproc->p_flag&SLOAD) == 0)
E 61
I 61
D 62
	if (p->p_time == 0 || (p->p_flag&SLOAD) == 0)
E 62
I 62
D 67
	if (p->p_time == 0 || (p->p_flag & SLOAD) == 0)
E 67
I 67
	if (p->p_time == 0 || (p->p_flag & SLOAD) == 0)	/* XXX - I don't like this */
E 67
E 62
E 61
E 4
		return (0.0);
D 4
	return (100.0 * mproc->p_pctcpu / (1.0 - exp(mproc->p_time * log(ccpu))));
E 4
I 4
	if (rawcpu)
D 58
		return (100.0 * mproc->p_pctcpu);
	return (100.0 * mproc->p_pctcpu / (1.0 - exp(time * log(ccpu))));
E 58
I 58
D 61
		return (100.0 * fxtofl(mproc->p_pctcpu));
	return (100.0 * fxtofl(mproc->p_pctcpu) /
	        (1.0 - exp(time * log(fxtofl(ccpu)))));
E 61
I 61
		return (100.0 * fxtofl(p->p_pctcpu));
	return (100.0 * fxtofl(p->p_pctcpu) /
		(1.0 - exp(p->p_time * log(fxtofl(ccpu)))));
E 61
E 58
E 4
}
I 58
D 61
#undef fxtofl
E 61
E 58

E 3
D 61
getu()
E 61
I 61
pcpu(k, v)
	struct kinfo *k;
	struct var *v;
E 61
{
D 7
	struct pte *pteaddr, apte, arguutl[UPAGES+CLSIZE];
E 7
I 7
D 61
	struct pte *pteaddr, apte;
D 19
	int pad1;	/* avoid hardware botch */
E 19
	struct pte arguutl[UPAGES+CLSIZE];
D 19
	int pad2;	/* avoid hardware botch */
E 19
E 7
	register int i;
	int ncl, size;
E 61

D 61
	size = sflg ? ctob(UPAGES) : sizeof (struct user);
	if ((mproc->p_flag & SLOAD) == 0) {
I 20
		if (swap < 0)
			return (0);
E 20
D 19
		lseek(swap, ctob(mproc->p_swaddr), 0);
E 19
I 19
D 23
		(void) lseek(swap, (long)ctob(mproc->p_swaddr), 0);
E 23
I 23
		(void) lseek(swap, (long)dtob(mproc->p_swaddr), 0);
E 23
E 19
		if (read(swap, (char *)&user.user, size) != size) {
			fprintf(stderr, "ps: cant read u for pid %d from %s\n",
			    mproc->p_pid, swapf);
			return (0);
		}
		pcbpf = 0;
		argaddr = 0;
		return (1);
	}
I 18
D 29
	if (kflg)
		mproc->p_p0br = (struct pte *)clear(mproc->p_p0br);
E 18
	pteaddr = &Usrptma[btokmx(mproc->p_p0br) + mproc->p_szpt - 1];
E 29
I 29
	pteaddr = &Usrptmap[btokmx(mproc->p_p0br) + mproc->p_szpt - 1];
E 29
D 18
	lseek(kmem, kflg ? clear(pteaddr) : (int)pteaddr, 0);
E 18
I 18
D 19
	klseek(kmem, pteaddr, 0);
E 19
I 19
	klseek(kmem, (long)pteaddr, 0);
E 19
E 18
	if (read(kmem, (char *)&apte, sizeof(apte)) != sizeof(apte)) {
		printf("ps: cant read indir pte to get u for pid %d from %s\n",
D 29
		    mproc->p_pid, swapf);
E 29
I 29
		    mproc->p_pid, kmemf);
E 29
		return (0);
	}
D 19
	lseek(mem,
	    ctob(apte.pg_pfnum+1) - (UPAGES+CLSIZE) * sizeof (struct pte), 0);
E 19
I 19
D 20
	(void) lseek(mem,
E 20
I 20
D 29
	klseek(mem,
E 29
I 29
	lseek(mem,
E 29
E 20
	    (long)ctob(apte.pg_pfnum+1) - (UPAGES+CLSIZE) * sizeof (struct pte),
		0);
E 19
	if (read(mem, (char *)arguutl, sizeof(arguutl)) != sizeof(arguutl)) {
		printf("ps: cant read page table for u of pid %d from %s\n",
D 20
		    mproc->p_pid, swapf);
E 20
I 20
D 29
		    mproc->p_pid, kmemf);
E 29
I 29
		    mproc->p_pid, memf);
E 29
E 20
		return (0);
	}
	if (arguutl[0].pg_fod == 0 && arguutl[0].pg_pfnum)
		argaddr = ctob(arguutl[0].pg_pfnum);
	else
		argaddr = 0;
	pcbpf = arguutl[CLSIZE].pg_pfnum;
	ncl = (size + NBPG*CLSIZE - 1) / (NBPG*CLSIZE);
	while (--ncl >= 0) {
		i = ncl * CLSIZE;
D 19
		lseek(mem, ctob(arguutl[CLSIZE+i].pg_pfnum), 0);
E 19
I 19
D 20
		(void) lseek(mem, (long)ctob(arguutl[CLSIZE+i].pg_pfnum), 0);
E 20
I 20
D 29
		klseek(mem, (long)ctob(arguutl[CLSIZE+i].pg_pfnum), 0);
E 29
I 29
		lseek(mem, (long)ctob(arguutl[CLSIZE+i].pg_pfnum), 0);
E 29
E 20
E 19
		if (read(mem, user.upages[i], CLSIZE*NBPG) != CLSIZE*NBPG) {
			printf("ps: cant read page %d of u of pid %d from %s\n",
			    arguutl[CLSIZE+i].pg_pfnum, mproc->p_pid, memf);
			return(0);
		}
	}
	return (1);
E 61
I 61
D 69
	printf("%*.1f", v->width, getpcpu(k));
E 69
I 69
	(void) printf("%*.1f", v->width, getpcpu(k));
E 69
E 61
}

D 61
char *
getcmd()
E 61
I 61
double
D 69
getpmem(k, v)
E 69
I 69
getpmem(k)
E 69
	struct kinfo *k;
D 69
	struct var *v;
E 69
E 61
{
D 23
	char cmdbuf[BUFSIZ];
E 23
I 23
D 61
	char cmdbuf[CLSIZE*NBPG];
E 23
I 7
D 19
	int pad1;		/* avoid hardware botch */
E 19
E 7
	union {
		char	argc[CLSIZE*NBPG];
		int	argi[CLSIZE*NBPG/sizeof (int)];
	} argspac;
I 7
D 19
	int pad2;		/* avoid hardware botch */
E 19
E 7
	register char *cp;
	register int *ip;
	char c;
	int nbad;
	struct dblock db;
I 20
	char *file;
E 61
I 61
	struct proc *p = k->ki_p;
	struct eproc *e = k->ki_e;
	double fracmem;
	int szptudot;
	/*
	 * note: this routine requires that ecmx
	 * be initialized.  If you call this routine from
	 * somewhere new, insure that the "neednlist" flag
	 * gets set.
	 */
E 61
E 20

D 61
	if (mproc->p_stat == SZOMB || mproc->p_flag&(SSYS|SWEXIT))
		return ("");
	if (cflg) {
D 19
		strncpy(cmdbuf, u.u_comm, sizeof (u.u_comm));
E 19
I 19
D 60
		(void) strncpy(cmdbuf, u.u_comm, sizeof (u.u_comm));
E 60
I 60
		(void) strncpy(cmdbuf, mproc->p_comm, sizeof (mproc->p_comm));
E 60
E 19
		return (savestr(cmdbuf));
	}
	if ((mproc->p_flag & SLOAD) == 0 || argaddr == 0) {
I 20
		if (swap < 0)
			goto retucomm;
E 20
		vstodb(0, CLSIZE, &u.u_smap, &db, 1);
D 19
		lseek(swap, ctob(db.db_base), 0);
E 19
I 19
D 23
		(void) lseek(swap, (long)ctob(db.db_base), 0);
E 23
I 23
		(void) lseek(swap, (long)dtob(db.db_base), 0);
E 23
E 19
		if (read(swap, (char *)&argspac, sizeof(argspac))
		    != sizeof(argspac))
			goto bad;
I 20
		file = swapf;
E 20
	} else {
D 19
		lseek(mem, argaddr, 0);
E 19
I 19
D 20
		(void) lseek(mem, (long)argaddr, 0);
E 20
I 20
D 29
		klseek(mem, (long)argaddr, 0);
E 29
I 29
		lseek(mem, (long)argaddr, 0);
E 29
E 20
E 19
		if (read(mem, (char *)&argspac, sizeof (argspac))
		    != sizeof (argspac))
			goto bad;
I 20
		file = memf;
E 20
	}
	ip = &argspac.argi[CLSIZE*NBPG/sizeof (int)];
	ip -= 2;		/* last arg word and .long 0 */
	while (*--ip)
		if (ip == argspac.argi)
			goto retucomm;
	*(char *)ip = ' ';
	ip++;
	nbad = 0;
	for (cp = (char *)ip; cp < &argspac.argc[CLSIZE*NBPG]; cp++) {
		c = *cp & 0177;
		if (c == 0)
			*cp = ' ';
		else if (c < ' ' || c > 0176) {
			if (++nbad >= 5*(eflg+1)) {
				*cp++ = ' ';
				break;
			}
			*cp = '?';
		} else if (eflg == 0 && c == '=') {
			while (*--cp != ' ')
				if (cp <= (char *)ip)
					break;
			break;
		}
	}
	*cp = 0;
	while (*--cp == ' ')
		*cp = 0;
	cp = (char *)ip;
D 19
	strncpy(cmdbuf, cp, &argspac.argc[CLSIZE*NBPG] - cp);
E 19
I 19
	(void) strncpy(cmdbuf, cp, &argspac.argc[CLSIZE*NBPG] - cp);
E 19
	if (cp[0] == '-' || cp[0] == '?' || cp[0] <= ' ') {
D 19
		strcat(cmdbuf, " (");
		strncat(cmdbuf, u.u_comm, sizeof(u.u_comm));
		strcat(cmdbuf, ")");
E 19
I 19
		(void) strcat(cmdbuf, " (");
D 60
		(void) strncat(cmdbuf, u.u_comm, sizeof(u.u_comm));
E 60
I 60
		(void) strncat(cmdbuf, mproc->p_comm, sizeof(mproc->p_comm));
E 60
		(void) strcat(cmdbuf, ")");
E 19
	}
I 2
D 29
/*
E 2
	if (xflg == 0 && gflg == 0 && tptr == 0 && cp[0] == '-')
		return (0);
I 2
*/
E 29
E 2
	return (savestr(cmdbuf));
E 61
I 61
D 62
	if (p->p_flag&SLOAD == 0)
E 62
I 62
D 69
	if (p->p_flag & SLOAD == 0)
E 69
I 69
	if ((p->p_flag & SLOAD) == 0)
E 69
E 62
		return (0.0);
	szptudot = UPAGES + clrnd(ctopt(p->p_dsize + p->p_ssize + e->e_xsize));
	fracmem = ((float)p->p_rssize + szptudot)/CLSIZE/ecmx;
	if (p->p_textp && e->e_xccount)
		fracmem += ((float)e->e_xrssize)/CLSIZE/e->e_xccount/ecmx;
	return (100.0 * fracmem);
}
E 61

D 61
bad:
D 20
	fprintf(stderr, "ps: error locating command name for pid %d\n",
	    mproc->p_pid);
E 20
I 20
	fprintf(stderr, "ps: error locating command name for pid %d from %s\n",
	    mproc->p_pid, file);
E 20
retucomm:
D 19
	strcpy(cmdbuf, " (");
	strncat(cmdbuf, u.u_comm, sizeof (u.u_comm));
	strcat(cmdbuf, ")");
E 19
I 19
	(void) strcpy(cmdbuf, " (");
D 60
	(void) strncat(cmdbuf, u.u_comm, sizeof (u.u_comm));
E 60
I 60
	(void) strncat(cmdbuf, mproc->p_comm, sizeof (mproc->p_comm));
E 60
	(void) strcat(cmdbuf, ")");
E 19
	return (savestr(cmdbuf));
E 61
I 61
pmem(k, v)
	struct kinfo *k;
	struct var *v;
{

D 69
	printf("%*.1f", v->width, getpmem(k));
E 69
I 69
	(void) printf("%*.1f", v->width, getpmem(k));
E 69
E 61
}

D 61
char	*lhdr =
D 2
"     F S UID   PID  PPID CP PRI NI ADDR  SZ  RSS WCHAN TTY TIME";
E 2
I 2
D 3
"     F UID   PID  PPID CP PRI NI ADDR  SZ  RSS WCHAN S  TT  TIME";
E 3
I 3
D 4
"     F UID   PID  PPID CP PRI NI ADDR  SZ  RSS WCHAN ST TT  TIME";
E 4
I 4
D 23
"     F UID   PID  PPID CP PRI NI ADDR  SZ  RSS WCHAN STAT TT  TIME";
E 23
I 23
D 30
"      F UID   PID  PPID CP PRI NI ADDR  SZ  RSS WCHAN STAT TT  TIME";
E 30
I 30
D 36
"      F UID   PID  PPID CP PRI NI ADDR  SZ  RSS WCHAN  STAT TT  TIME";
E 36
I 36
D 39
"      F UID   PID  PPID CP PRI NI ADDR  SZ  RSS  WCHAN STAT TT  TIME";
E 39
I 39
D 50
"      F UID   PID  PPID CP PRI NI ADDR  SZ  RSS %*s STAT TT  TIME";
E 50
I 50
D 52
"      F UID   PID  PPID CP PRI NI ADDR    SZ  RSS %*sSTAT TT  TIME";
E 52
I 52
D 54
"      F  UID   PID  PPID CP PRI NI ADDR    SZ  RSS %*sSTAT TT  TIME";
E 54
I 54
D 56
"     F  UID   PID  PPID CP PRI NI ADDR    SZ  RSS %*sSTAT TT  TIME";
E 56
I 56
"      F  UID   PID  PPID CP PRI NI ADDR    SZ  RSS %*sSTAT TT  TIME";
E 56
E 54
E 52
E 50
E 39
E 36
E 30
E 23
E 4
E 3
E 2
lpr(sp)
	struct savcom *sp;
E 61
I 61
pagein(k, v)
	struct kinfo *k;
	struct var *v;
E 61
{
D 61
	register struct asav *ap = sp->ap;
D 23
	register struct lsav *lp = sp->sun.lp;
E 23
I 23
	register struct lsav *lp = sp->s_un.lp;
E 61
E 23

D 2
	printf("%6x %c%4d%6u%6u%3d%4d%2d%6x%4d%5d",
	    ap->a_flag, "0SWRIZT"[ap->a_stat], ap->a_uid,
	    ap->a_pid, lp->l_ppid, lp->l_cpu&0377, lp->l_pri-PZERO,
	    ap->a_nice-NZERO, lp->l_addr, ap->a_size, ap->a_rss);
E 2
I 2
D 23
	printf("%6x%4d%6u%6u%3d%4d%3d%5x%4d%5d",
E 23
I 23
D 50
	printf("%7x%4d%6u%6u%3d%4d%3d%5x%4d%5d",
E 50
I 50
D 52
	printf("%7x %3d %5u %5u %2d %3d %2d %4x %5d %4d",
E 52
I 52
D 54
	printf("%7x %4d %5u %5u %2d %3d %2d %4x %5d %4d",
E 52
E 50
E 23
	    ap->a_flag, ap->a_uid,
	    ap->a_pid, lp->l_ppid, lp->l_cpu&0377, ap->a_pri-PZERO,
D 23
	    ap->a_nice-NZERO, lp->l_addr, ap->a_size/2, ap->a_rss/2);
E 23
I 23
	    ap->a_nice-NZERO, lp->l_addr, pgtok(ap->a_size), pgtok(ap->a_rss));
E 54
I 54
D 56
	printf("%6x %4d %5u %5u %2d %3d %2d %4x %5d %4d",
E 56
I 56
D 61
	printf("%7x %4d %5u %5u %2d %3d %2d %4x %5d %4d",
E 56
	    (ap->a_flag &~ SPTECHG),				/* XXX */
D 60
	    ap->a_uid, ap->a_pid, lp->l_ppid,
E 60
I 60
	    ap->a_uid, ap->a_pid, ap->a_ppid,
E 60
	    lp->l_cpu > 99 ? 99 : lp->l_cpu, ap->a_pri-PZERO,
	    ap->a_nice, lp->l_addr, pgtok(ap->a_size), pgtok(ap->a_rss));
E 54
E 23
E 2
D 30
	printf(lp->l_wchan ? " %5x" : "      ", (int)lp->l_wchan&0xfffff);
E 30
I 30
D 39
	printf(lp->l_wchan ? " %6x" : "       ", (int)lp->l_wchan&0xffffff);
E 39
I 39
	if (lp->l_wchan == 0)
		printf(" %*s", wcwidth, "");
	else if (nflg)
D 50
		printf(" %*x", wcwidth, (int)lp->l_wchan&0xffffff);
E 50
I 50
		printf(" %*x", wcwidth, (int)lp->l_wchan&~KERNBASE);
E 50
	else
		printf(" %*.*s", wcwidth, abs(wcwidth), getchan(lp->l_wchan));
E 39
E 30
I 2
D 4
	printf(" %2.2s ", state(ap));
E 4
I 4
D 50
	printf(" %4.4s ", state(ap));
E 50
I 50
D 55
	printf(" %-3.3s ", state(ap));
E 55
I 55
	printf(" %-2.3s ", state(ap));
E 55
E 50
E 4
E 2
	ptty(ap->a_tty);
I 60
	ptime(ap);
E 61
I 61
D 69
	printf("%*d", v->width, k->ki_u ? k->ki_u->u_ru.ru_majflt : 0);
E 69
I 69
	(void) printf("%*d", v->width, k->ki_u ? k->ki_u->u_ru.ru_majflt : 0);
E 69
E 61
}

D 61
char *jhdr = 
" UID   PID  PPID  PGID SESSION STAT TT TPGID TSESSION  TIME";
jpr(sp)
	struct savcom *sp;
E 61
I 61
maxrss(k, v)
	struct kinfo *k;
	struct var *v;
E 61
{
D 61
	register struct asav *ap = sp->ap;
E 61

D 61
	printf("%4d %5u %5u %5u %8x %-2.3s ", ap->a_uid, ap->a_pid, ap->a_ppid,
		ap->a_pgid, ap->a_session, state(ap));
	ptty(ap->a_tty);
	if (ap->a_tpgid == -1)
		printf("   -   ");
E 61
I 61
	if (k->ki_p->p_maxrss != (RLIM_INFINITY/NBPG))
D 69
		printf("%*d", v->width, pgtok(k->ki_p->p_maxrss));
E 69
I 69
		(void) printf("%*d", v->width, pgtok(k->ki_p->p_maxrss));
E 69
E 61
	else
D 61
		printf(" %5u ", ap->a_tpgid);
	if (ap->a_tsession == -1)
		printf("     -    ");
	else
		printf("%8x ", ap->a_tsession);
E 60
	ptime(ap);
E 61
I 61
D 69
		printf("%*s", v->width, "-");
E 69
I 69
		(void) printf("%*s", v->width, "-");
E 69
E 61
}

D 61
ptty(tp)
	char *tp;
E 61
I 61
tsize(k, v)
	struct kinfo *k;
	struct var *v;
E 61
{
I 61
D 69
	
	printf("%*d", v->width, pgtok(k->ki_e->e_xsize));
E 69
I 69

	(void) printf("%*d", v->width, pgtok(k->ki_e->e_xsize));
E 69
}
E 61

D 2
	printf(" %-2.2s", tp);
E 2
I 2
D 61
	printf("%-2.2s", tp);
E 61
I 61
trss(k, v)
	struct kinfo *k;
	struct var *v;
{

D 69
	printf("%*d", v->width, pgtok(k->ki_e->e_xrssize));
E 69
I 69
	(void) printf("%*d", v->width, pgtok(k->ki_e->e_xrssize));
E 69
E 61
E 2
}

D 61
ptime(ap)
	struct asav *ap;
E 61
I 61
/*
 * Generic output routines.  Print fields from various prototype
 * structures.
 */
D 69
pvar(k, v) 
E 69
I 69
pvar(k, v)
E 69
	struct kinfo *k;
	struct var *v;
E 61
{
I 61
D 69
 
E 69
I 69

E 69
	printval((char *)((char *)k->ki_p + v->off), v);
}
E 61

D 2
	printf("%3ld:%02ld", ap->a_time / HZ, ap->a_time % HZ);
E 2
I 2
D 8
	printf("%3ld:%02ld", ap->a_cpu / HZ, ap->a_cpu % HZ);
E 8
I 8
D 21
	printf("%3ld:%02ld", ap->a_cpu / hz, ap->a_cpu % hz);
E 21
I 21
D 50
	printf("%3ld:%02ld", ap->a_cpu / 60, ap->a_cpu % 60);
E 50
I 50
D 55
	printf(" %2ld:%02ld", ap->a_cpu / 60, ap->a_cpu % 60);
E 55
I 55
D 61
	printf(" %3ld:%02ld", ap->a_cpu / 60, ap->a_cpu % 60);
E 61
I 61
D 69
evar(k, v) 
E 69
I 69
evar(k, v)
E 69
	struct kinfo *k;
	struct var *v;
{
D 69
 
E 69
I 69

E 69
	printval((char *)((char *)k->ki_e + v->off), v);
E 61
E 55
E 50
E 21
E 8
E 2
}

D 61
char	*uhdr =
D 2
"USER       PID %CPU NICE  SZ  RSS TTY TIME";
E 2
I 2
D 3
"USER       PID %CPU NICE  SZ  RSS TT F   TIME";
E 3
I 3
D 4
"USER       PID %CPU NI   SZ  RSS TT ST  TIME";
E 4
I 4
D 39
"USER       PID %CPU %MEM   SZ  RSS TT STAT  TIME";
E 39
I 39
D 50
"%s   PID %%CPU %%MEM   SZ  RSS TT STAT  TIME";
E 50
I 50
"%s   PID %%CPU %%MEM    SZ   RSS TT STAT TIME";
E 50
E 39
E 4
E 3
E 2
upr(sp)
	struct savcom *sp;
E 61
I 61
D 69
uvar(k, v) 
E 69
I 69
uvar(k, v)
E 69
	struct kinfo *k;
	struct var *v;
E 61
{
D 61
	register struct asav *ap = sp->ap;
I 4
	int vmsize, rmsize;
E 61
I 61
D 69
 
E 69
I 69

E 69
	if (k->ki_u)
		printval((char *)((char *)k->ki_u + v->off), v);
	else
D 69
		printf("%*s", v->width, "-");
E 69
I 69
		(void) printf("%*s", v->width, "-");
E 69
}
E 61
E 4

D 3
	printf("%-8.8s %5u%5.1f%5d%4d%5d",
E 3
I 3
D 4
	printf("%-8.8s %5u%5.1f%3d%5d%5d",
E 3
	    getname(ap->a_uid), ap->a_pid, sp->sun.u_pctcpu, ap->a_nice-NZERO,
D 2
	    ap->a_size, ap->a_rss);
E 2
I 2
	    ap->a_size/2, ap->a_rss/2);
E 4
I 4
D 23
	vmsize = (ap->a_size + ap->a_tsiz)/2;
	rmsize = ap->a_rss/2;
E 23
I 23
D 61
	vmsize = pgtok((ap->a_size + ap->a_tsiz));
	rmsize = pgtok(ap->a_rss);
E 23
	if (ap->a_xccount)
D 23
		rmsize += ap->a_txtrss/ap->a_xccount/2;
E 23
I 23
		rmsize += pgtok(ap->a_txtrss/ap->a_xccount);
E 23
D 39
	printf("%-8.8s %5d%5.1f%5.1f%5d%5d",
D 23
	    getname(ap->a_uid), ap->a_pid, sp->sun.u_pctcpu, pmem(ap),
E 23
I 23
	    getname(ap->a_uid), ap->a_pid, sp->s_un.u_pctcpu, pmem(ap),
E 23
	    vmsize, rmsize);
E 39
I 39
	if (nflg)
		printf("%4d ", ap->a_uid);
E 61
I 61
rvar(k, v)
	struct kinfo *k;
	struct var *v;
{
D 69
	
E 69
I 69

E 69
	if (k->ki_u)
		printval((char *)((char *)(&k->ki_u->u_ru) + v->off), v);
E 61
	else
D 61
		printf("%-8.8s ", getname(ap->a_uid));
D 50
	printf("%5d%5.1f%5.1f%5d%5d",
E 50
I 50
	printf("%5d %4.1f %4.1f %5d %5d",
E 50
	    ap->a_pid, sp->s_un.u_pctcpu, pmem(ap), vmsize, rmsize);
E 39
E 4
	putchar(' ');
E 2
	ptty(ap->a_tty);
I 2
D 4
	printf(" %2.2s", state(ap));
E 4
I 4
D 50
	printf(" %4.4s", state(ap));
E 50
I 50
D 55
	printf(" %-3.3s", state(ap));
E 55
I 55
	printf(" %-2.3s", state(ap));
E 55
E 50
E 4
E 2
	ptime(ap);
E 61
I 61
D 69
		printf("%*s", v->width, "-");
E 69
I 69
		(void) printf("%*s", v->width, "-");
E 69
E 61
}

D 61
char *vhdr =
D 2
"F     PID TTY  TIME RES SL  MINFLT  MAJFLT SIZE  RSS  SRS TSIZ TRS PF";
E 2
I 2
D 3
"   PID TT S     TIME RES SL MINFLT MAJFLT SIZE  RSS  SRS TSIZ TRS PF";
E 3
I 3
D 4
"   PID TT ST    TIME RES SL MINFLT MAJFLT SIZE  RSS  SRS TSIZ TRS %CP";
E 4
I 4
D 9
"  PID TT STAT  TIME SL RE PAGEIN SIZE  RSS  SRS TSIZ TRS %CPU %MEM";
E 9
I 9
D 23
"  PID TT STAT  TIME SL RE PAGEIN SIZE  RSS  LIM TSIZ TRS %CPU %MEM";
E 23
I 23
D 46
" SIZE  PID TT STAT  TIME SL RE PAGEIN SIZE  RSS  LIM TSIZ TRS %CPU %MEM"+5;
E 46
I 46
D 50
" SIZE  PID TT STAT  TIME SL RE PAGEIN SIZE  RSS   LIM TSIZ TRS %CPU %MEM"+5;
E 50
I 50
" SIZE  PID TT STAT TIME SL RE PAGEIN  SIZE   RSS   LIM TSIZ TRS %CPU %MEM"+5;
E 50
E 46
E 23
E 9
E 4
E 3
E 2
vpr(sp)
	struct savcom *sp;
E 61
I 61
char *
lookupcombo(cp)
	char *cp;
E 61
{
D 23
	register struct vsav *vp = sp->sun.vp;
E 23
I 23
D 61
	register struct vsav *vp = sp->s_un.vp;
E 23
	register struct asav *ap = sp->ap;
E 61
I 61
	register struct combovar *cv = &combovar[0];
E 61
D 2
	char stat, nice, anom;
E 2

I 2
D 4
	printf("%6u ", ap->a_pid);
E 4
I 4
D 61
	printf("%5u ", ap->a_pid);
E 4
	ptty(ap->a_tty);
D 4
	printf(" %4s", state(ap));
E 4
I 4
D 50
	printf(" %4.4s", state(ap));
E 50
I 50
D 55
	printf(" %-3.3s", state(ap));
E 55
I 55
	printf(" %-2.3s", state(ap));
E 55
E 50
E 4
	ptime(ap);
D 3
	printf("%4d%3d%7d%7d%5d%5d%5d%5d%4d%3d",
E 3
I 3
D 4
	printf("%4d%3d%7d%7d%5d%5d%5d%5d%4d%4d",
E 3
	   ap->a_time, ap->a_slptime, vp->v_minflt, vp->v_majflt,
E 4
I 4
D 9
	printf("%3d%3d%7d%5d%5d%5d%5d%4d%5.1f%5.1f",
	   ap->a_slptime, ap->a_time > 99 ? 99 : ap->a_time, vp->v_majflt,
E 4
	   ap->a_size/2, ap->a_rss/2, vp->v_swrss/2,
E 9
I 9
D 50
	printf("%3d%3d%7d%5d%5d",
E 50
I 50
	printf(" %2d %2d %6d %5d %5d",
E 50
	   ap->a_slptime > 99 ? 99 : ap-> a_slptime,
	   ap->a_time > 99 ? 99 : ap->a_time, vp->v_majflt,
D 23
	   ap->a_size/2, ap->a_rss/2);
	if (ap->a_maxrss == (INFINITY/NBPG))
E 23
I 23
	   pgtok(ap->a_size), pgtok(ap->a_rss));
	if (ap->a_maxrss == (RLIM_INFINITY/NBPG))
E 23
D 10
		printf("   oo");
E 10
I 10
D 46
		printf("   xx");
E 46
I 46
		printf("    xx");
E 46
E 10
	else
D 23
		printf("%5d", ap->a_maxrss/2);
E 23
I 23
D 46
		printf("%5d", pgtok(ap->a_maxrss));
E 46
I 46
D 50
		printf("%6d", pgtok(ap->a_maxrss));
E 46
E 23
	printf("%5d%4d%5.1f%5.1f",
E 50
I 50
		printf(" %5d", pgtok(ap->a_maxrss));
	printf(" %4d %3d %4.1f %4.1f",
E 50
E 9
D 3
	   vp->v_tsiz/2, vp->v_txtrss/2, vp->v_aveflt);
E 3
I 3
D 4
	   vp->v_tsiz/2, vp->v_txtrss/2, vp->v_pctcpu);
E 4
I 4
D 23
	   ap->a_tsiz/2, ap->a_txtrss/2, vp->v_pctcpu, pmem(ap));
E 23
I 23
	   pgtok(ap->a_tsiz), pgtok(ap->a_txtrss), vp->v_pctcpu, pmem(ap));
E 61
I 61
	for (; cv->name; cv++)
		if (strcmp(cp, cv->name) == 0)
			return (cv->replace);
	return (NULL);
E 61
E 23
E 4
E 3
}

D 61
char	*shdr =
D 3
"SSIZ   PID TT S   TIME";
E 3
I 3
D 4
"SSIZ   PID TT ST  TIME";
E 4
I 4
"SSIZ   PID TT STAT  TIME";
E 4
E 3
spr(sp)
	struct savcom *sp;
E 61
I 61
struct var *
lookupvar(cp)
	char *cp;
E 61
{
D 61
	register struct asav *ap = sp->ap;
E 61
I 61
	register int i, j;
E 61

D 61
	if (sflg)
D 23
		printf("%4d ", sp->sun.s_ssiz);
E 23
I 23
		printf("%4d ", sp->s_un.s_ssiz);
E 23
	printf("%5u", ap->a_pid);
	putchar(' ');
	ptty(ap->a_tty);
D 4
	printf(" %2.2s", state(ap));
E 4
I 4
D 50
	printf(" %4.4s", state(ap));
E 50
I 50
D 55
	printf(" %-3.3s", state(ap));
E 55
I 55
	printf(" %-2.3s", state(ap));
E 55
E 50
E 4
	ptime(ap);
E 61
I 61
	for (i=0; var[i].name[0] != NULL; i++)
		for (j=0; var[i].name[j] != NULL; j++)
			if (strcmp(cp, var[i].name[j]) == 0)
				return (&var[i]);
	return (NULL);
E 61
}

D 61
char *
state(ap)
	register struct asav *ap;
E 61
I 61
printval(bp, v)
	char *bp;
	struct var *v;
E 61
{
D 50
	char stat, load, nice, anom;
E 50
D 61
	static char res[5];
I 50
	char *cp = res;
E 61
I 61
D 62
	static char ofmt[16] = "%";
	char *cp = ofmt+1;
E 62
I 62
	static char ofmt[32] = "%";
	register char *cp = ofmt+1, *fcp = v->fmt;
E 62
E 61
E 50

E 2
D 61
	switch (ap->a_stat) {
E 61
I 61
	if (v->flag & LJUST)
		*cp++ = '-';
	*cp++ = '*';
D 62
	*cp++ = *v->fmt;
	*cp++ = '\0';
E 62
I 62
	while (*cp++ = *fcp++)
		;
E 62
E 61

D 2
	case SSLEEP:
E 2
D 61
	case SSTOP:
D 2
		if ((ap->a_flag & SLOAD) == 0)
			stat = 'W';
		else if (vp->v_pri >= PZERO)
			stat = 'S';
E 2
I 2
D 50
		stat = 'T';
E 50
I 50
		*cp = 'T';
E 61
I 61
	switch (v->type) {
	case CHAR:
D 69
		printf(ofmt, v->width, *(char *)bp);
E 69
I 69
		(void) printf(ofmt, v->width, *(char *)bp);
E 69
E 61
E 50
		break;

D 61
	case SSLEEP:
		if (ap->a_pri >= PZERO)
			if (ap->a_slptime >= MAXSLP)
D 50
				stat = 'I';
E 50
I 50
				*cp = 'I';
E 50
			else
D 50
				stat = 'S';
E 50
I 50
				*cp = 'S';
E 50
E 2
		else if (ap->a_flag & SPAGE)
D 50
			stat = 'P';
E 50
I 50
			*cp = 'P';
E 50
		else
D 50
			stat = 'D';
E 50
I 50
			*cp = 'D';
E 61
I 61
	case UCHAR:
D 69
		printf(ofmt, v->width, *(u_char *)bp);
E 69
I 69
		(void) printf(ofmt, v->width, *(u_char *)bp);
E 69
E 61
E 50
		break;

I 2
D 61
	case SWAIT:
E 2
	case SRUN:
	case SIDL:
D 2
		stat = ap->a_flag & SLOAD ? 'R' : 'W';
E 2
I 2
D 50
		stat = 'R';
E 50
I 50
		*cp = 'R';
E 61
I 61
	case SHORT:
D 69
		printf(ofmt, v->width, *(short *)bp);
E 69
I 69
		(void) printf(ofmt, v->width, *(short *)bp);
E 69
E 61
E 50
E 2
		break;
I 2

D 61
	case SZOMB:
D 50
		stat = 'Z';
E 50
I 50
		*cp = 'Z';
E 61
I 61
	case USHORT:
D 69
		printf(ofmt, v->width, *(u_short *)bp);
E 69
I 69
		(void) printf(ofmt, v->width, *(u_short *)bp);
E 69
E 61
E 50
		break;

I 61
	case LONG:
D 69
		printf(ofmt, v->width, *(long *)bp);
E 69
I 69
		(void) printf(ofmt, v->width, *(long *)bp);
E 69
		break;

	case ULONG:
D 69
		printf(ofmt, v->width, *(u_long *)bp);
E 69
I 69
		(void) printf(ofmt, v->width, *(u_long *)bp);
E 69
		break;

	case KPTR:
D 69
		printf(ofmt, v->width, *(u_long *)bp &~ KERNBASE);
E 69
I 69
		(void) printf(ofmt, v->width, *(u_long *)bp &~ KERNBASE);
E 69
		break;

E 61
	default:
D 50
		stat = '?';
E 50
I 50
D 61
		*cp = '?';
E 61
I 61
		error("unknown type %d", v->type);
E 61
E 50
E 2
	}
I 2
D 9
	load = ap->a_flag & SLOAD ? ' ' : 'W';
E 9
I 9
D 50
	load = ap->a_flag & SLOAD ? (ap->a_rss>ap->a_maxrss ? '>' : ' ') : 'W';
E 50
I 50
D 61
	cp++;
	if (ap->a_flag & SLOAD) {
		if (ap->a_rss > ap->a_maxrss)
			*cp++ = '>';
	} else
		*cp++ = 'W';
E 50
E 9
E 2
D 4
	nice = ap->a_nice > NZERO ? 'N' : ' ';
E 4
I 4
	if (ap->a_nice < NZERO)
D 50
		nice = '<';
E 50
I 50
		*cp++ = '<';
E 50
	else if (ap->a_nice > NZERO)
D 50
		nice = 'N';
	else
		nice = ' ';
E 4
D 10
	anom = ap->a_flag & (SANOM|SUANOM) ? 'A' : ' ';
E 10
I 10
	anom = (ap->a_flag&SUANOM) ? 'A' : ((ap->a_flag&SSEQL) ? 'S' : ' ');
E 10
D 2
	printf("%c%c%c%6u ", stat, nice, anom, ap->a_pid);
	ptty(ap->a_tty);
	ptime(ap);
	printf("%4d%3d%8d%8d%5d%5d%5d%5d%4d%3d",
	   ap->a_time, vp->v_slptime, vp->v_minflt, vp->v_majflt,
	   ap->a_size, ap->a_rss / 2, vp->v_swrss / 2,
	   vp->v_tsiz / 2, vp->v_txtrss / 2, vp->v_aveflt);
}

char	*shdr =
" SSIZ   PID TTY TIME";
spr(sp)
	struct savcom *sp;
{
	register struct asav *ap = sp->ap;

	if (sflg)
		printf("%5d", sp->sun.s_ssiz);
	printf(" %5u", ap->a_pid);
	ptty(ap->a_tty);
	ptime(ap);
E 2
I 2
	res[0] = stat; res[1] = load; res[2] = nice; res[3] = anom;
E 50
I 50
		*cp++ = 'N';
	if (ap->a_flag & SUANOM)
		*cp++ = 'A';
	else if (ap->a_flag & SSEQL)
		*cp++ = 'S';
I 52
	*cp = '\0';
E 52
E 50
	return (res);
E 61
E 2
}

E 71
D 61
/*
 * Given a base/size pair in virtual swap area,
 * return a physical base/size pair which is the
 * (largest) initial, physically contiguous block.
 */
vstodb(vsbase, vssize, dmp, dbp, rev)
	register int vsbase;
	int vssize;
	struct dmap *dmp;
	register struct dblock *dbp;
E 61
I 61
D 86
/* XXX - redo */
D 69
struct usave *
saveuser(ki) 
E 69
I 69
saveuser(ki)
E 86
I 86
static char *
fmt(fn, ki, comm, maxlen)
	char **(*fn) __P((kvm_t *, const struct kinfo_proc *, int));
E 86
E 69
D 71
	struct kinfo *ki;
E 71
I 71
	KINFO *ki;
I 86
	char *comm;
	int maxlen;
E 86
E 71
E 61
{
D 26
	register int blk = DMMIN;
E 26
I 26
D 61
	register int blk = dmmin;
E 26
	register swblk_t *ip = dmp->dm_map;

I 23
	vsbase = ctod(vsbase);
	vssize = ctod(vssize);
E 23
	if (vsbase < 0 || vsbase + vssize > dmp->dm_size)
		panic("vstodb");
	while (vsbase >= blk) {
		vsbase -= blk;
D 26
		if (blk < DMMAX)
E 26
I 26
		if (blk < dmmax)
E 26
			blk *= 2;
		ip++;
E 61
I 61
D 86
	register struct usave *usp;
	register struct user *up;
E 86
I 86
D 96
	register char *s;
E 96
I 96
	char *s;
E 96
E 86
D 69
	
E 69
I 69

E 69
D 71
	if ((usp = (struct usave *)calloc(1, sizeof (struct usave))) == NULL) {
D 69
		fprintf(stderr, "ps: out of memory\n");
E 69
I 69
		(void) fprintf(stderr, "ps: out of memory\n");
E 71
I 71
D 81
	if ((usp = (struct usave *)calloc(1, sizeof(struct usave))) == NULL) {
		(void)fprintf(stderr, "ps: %s\n", strerror(errno));
E 71
E 69
		exit(1);
E 61
	}
E 81
I 81
D 86
	if ((usp = calloc(1, sizeof(struct usave))) == NULL)
E 86
I 86
D 92
	s = fmt_argv((*fn)(kd, ki->ki_p, termwidth), comm, maxlen);
	if (s == NULL)
E 86
		err("%s", strerror(errno));
E 92
I 92
	if ((s =
	    fmt_argv((*fn)(kd, ki->ki_p, termwidth), comm, maxlen)) == NULL)
		err(1, NULL);
E 92
E 81
D 61
	if (*ip <= 0 || *ip + blk > nswap)
		panic("vstodb *ip");
	dbp->db_size = min(vssize, blk - vsbase);
	dbp->db_base = *ip + (rev ? blk - (vsbase + dbp->db_size) : vsbase);
E 61
I 61
D 84
	ki->ki_u = usp;
E 84
D 86
	up = kvm_getu(ki->ki_p);
	/*
	 * save arguments if needed
	 */
D 71
	if (needcomm)
D 69
		ki->ki_args = saveargs(ki->ki_p, up);
E 69
I 69
		ki->ki_args = strdup(kvm_getargs(ki->ki_p, up));
E 69
	else
		ki->ki_args = NULL;
E 71
I 71
	ki->ki_args = needcomm ? strdup(kvm_getargs(ki->ki_p, up)) : NULL;
E 71
D 69
	if (up != NULL) { 
E 69
I 69
	if (up != NULL) {
I 84
		ki->ki_u = usp;
E 86
I 86
	return (s);
}

I 88
static void
E 88
saveuser(ki)
	KINFO *ki;
{
D 96
	register struct usave *usp = &ki->ki_u;
E 96
	struct pstats pstats;
D 96
	extern char *fmt_argv();
E 96
I 96
	struct usave *usp;
E 96

I 96
	usp = &ki->ki_u;
E 96
	if (kvm_read(kd, (u_long)&KI_PROC(ki)->p_addr->u_stats,
D 96
		     (char *)&pstats, sizeof(pstats)) == sizeof(pstats)) {
E 96
I 96
	    (char *)&pstats, sizeof(pstats)) == sizeof(pstats)) {
E 96
E 86
E 84
E 69
		/*
D 86
		 * save important fields
E 86
I 86
		 * The u-area might be swapped out, and we can't get
		 * at it because we have a crashdump and no swap.
		 * If it's here fill in these fields, otherwise, just
		 * leave them 0.
E 86
		 */
I 77
D 86
#ifdef NEWVM
		usp->u_start = up->u_stats.p_start;
		usp->u_ru = up->u_stats.p_ru;
		usp->u_cru = up->u_stats.p_cru;
#else
E 77
		usp->u_procp = up->u_procp;
		usp->u_start = up->u_start;
		usp->u_ru = up->u_ru;
		usp->u_cru = up->u_cru;
D 70
		usp->u_cmask = up->u_cmask;
E 70
		usp->u_acflag = up->u_acflag;
I 77
#endif
E 86
I 86
		usp->u_start = pstats.p_start;
		usp->u_ru = pstats.p_ru;
		usp->u_cru = pstats.p_cru;
		usp->u_valid = 1;
E 86
E 77
D 84
	}
E 84
I 84
	} else
D 86
		free(usp);
E 86
I 86
		usp->u_valid = 0;
	/*
	 * save arguments if needed
	 */
	if (needcomm)
		ki->ki_args = fmt(kvm_getargv, ki, KI_PROC(ki)->p_comm,
		    MAXCOMLEN);
	else
		ki->ki_args = NULL;
	if (needenv)
		ki->ki_env = fmt(kvm_getenvv, ki, (char *)NULL, 0);
	else
		ki->ki_env = NULL;
E 86
E 84
D 69
	return;
E 69
E 61
}

D 61
/*ARGSUSED*/
panic(cp)
	char *cp;
E 61
I 61
D 69
char *
saveargs(p, up)
	struct proc *p;
	struct user *up;
E 61
{
I 61
	char *savestr();
E 69
E 61
D 71

E 71
D 61
#ifdef DEBUG
	printf("%s\n", cp);
#endif
E 61
I 61
D 69
	return(savestr(kvm_getargs(p, up)));
E 61
}
I 61
	
E 61

E 69
D 61
min(a, b)
E 61
I 61
D 88
pscomp(k1, k2)
D 71
	struct kinfo *k1, *k2;
E 71
I 71
	KINFO *k1, *k2;
E 88
I 88
static int
pscomp(a, b)
	const void *a, *b;
E 88
E 71
E 61
{
I 61
	int i;
I 77
#ifdef NEWVM
D 86
#define VSIZE(k) ((k)->ki_e->e_vm.vm_dsize + (k)->ki_e->e_vm.vm_ssize + \
		  (k)->ki_e->e_vm.vm_tsize)
E 86
I 86
#define VSIZE(k) (KI_EPROC(k)->e_vm.vm_dsize + KI_EPROC(k)->e_vm.vm_ssize + \
		  KI_EPROC(k)->e_vm.vm_tsize)
E 86
#else
E 77
#define VSIZE(k) ((k)->ki_p->p_dsize + (k)->ki_p->p_ssize + (k)->ki_e->e_xsize)
I 77
#endif
E 77
E 61

D 61
	return (a < b ? a : b);
}

pscomp(s1, s2)
	struct savcom *s1, *s2;
{
	register int i;

I 3
D 16
	if (uflg)
E 16
I 16
D 23
	if (uflg && !ssflg)
E 16
		return (s2->sun.u_pctcpu > s1->sun.u_pctcpu ? 1 : -1);
E 23
I 23
	if (uflg)
		return (s2->s_un.u_pctcpu > s1->s_un.u_pctcpu ? 1 : -1);
E 23
E 3
	if (vflg)
		return (vsize(s2) - vsize(s1));
	i = s1->ap->a_ttyd - s2->ap->a_ttyd;
E 61
I 61
	if (sortby == SORTCPU)
D 88
		return (getpcpu(k2) - getpcpu(k1));
E 88
I 88
		return (getpcpu((KINFO *)b) - getpcpu((KINFO *)a));
E 88
I 67
D 70
#ifdef notyet
E 70
I 70
D 71
#ifdef notdef
E 70
	if (sortby == SORTRUN)
		return (proc_compare(k1->ki_p, k2->ki_p));
#endif
E 71
E 67
	if (sortby == SORTMEM)
D 88
		return (VSIZE(k2) - VSIZE(k1));
D 86
	i =  k1->ki_e->e_tdev - k2->ki_e->e_tdev;
E 86
I 86
	i =  KI_EPROC(k1)->e_tdev - KI_EPROC(k2)->e_tdev;
E 88
I 88
		return (VSIZE((KINFO *)b) - VSIZE((KINFO *)a));
	i =  KI_EPROC((KINFO *)a)->e_tdev - KI_EPROC((KINFO *)b)->e_tdev;
E 88
E 86
E 61
	if (i == 0)
D 61
		i = s1->ap->a_pid - s2->ap->a_pid;
E 61
I 61
D 86
		i = k1->ki_p->p_pid - k2->ki_p->p_pid;
E 86
I 86
D 88
		i = KI_PROC(k1)->p_pid - KI_PROC(k2)->p_pid;
E 88
I 88
		i = KI_PROC((KINFO *)a)->p_pid - KI_PROC((KINFO *)b)->p_pid;
E 88
E 86
E 61
	return (i);
}

D 61
vsize(sp)
	struct savcom *sp;
E 61
I 61
D 71
donlist()
E 61
{
I 69
#define kread(x, v) \
	kvm_read(psnl[x].n_value, (char *)&v, sizeof v) != sizeof(v)

E 69
D 61
	register struct asav *ap = sp->ap;
D 23
	register struct vsav *vp = sp->sun.vp;
E 23
I 23
	register struct vsav *vp = sp->s_un.vp;
E 23
	
	if (ap->a_flag & SLOAD)
		return (ap->a_rss +
D 4
		    vp->v_txtrss / (vp->v_xccount ? vp->v_xccount : 1));
	return (vp->v_swrss + (vp->v_xccount ? 0 : vp->v_txtswrss));
E 4
I 4
		    ap->a_txtrss / (ap->a_xccount ? ap->a_xccount : 1));
	return (vp->v_swrss + (ap->a_xccount ? 0 : vp->v_txtswrss));
E 61
I 61
	if (kvm_nlist(psnl) != 0)
		error("can't get namelist");
D 69
	if (kvm_read(psnl[X_FSCALE].n_value, &fscale, sizeof(int)) !=
	    sizeof (int))
E 69
I 69
	if (kread(X_FSCALE, fscale))
E 69
		error("error reading fscale: %s", kvm_geterr());
D 69
	if (kvm_read(psnl[X_ECMX].n_value, &ecmx, sizeof(int)) !=
	    sizeof (int))
E 69
I 69
	if (kread(X_ECMX, ecmx))
E 69
		error("error reading ecmx: %s", kvm_geterr());
D 69
	if (kvm_read(psnl[X_CCPU].n_value, &ccpu, sizeof(fixpt_t)) !=
	    sizeof (fixpt_t))
E 69
I 69
	if (kread(X_CCPU, ccpu))
E 69
		error("error reading ccpu: %s", kvm_geterr());
I 69
#undef kread
E 69
E 61
E 4
}

D 25
#define	NMAX	8
#define	NUID	2048
E 25
I 25
D 41
#define	NMAX	8	/* sizeof loginname (should be sizeof (utmp.ut_name)) */
#define NUID	2048	/* must not be a multiple of 5 */
E 41
I 41
D 61
#include <utmp.h>
E 41
E 25

D 25
char	names[NUID][NMAX+1];
E 25
I 25
D 41
struct nametable {
	char	nt_name[NMAX+1];
	int	nt_uid;
} nametable[NUID];
E 41
I 41
struct	utmp utmp;
#define	NMAX	(sizeof (utmp.ut_name))
#define SCPYN(a, b)	strncpy(a, b, NMAX)
E 41
E 25

D 25
/*
 * Stolen from ls...
 */
E 25
I 25
D 41
struct nametable *
findslot(uid)
D 29
unsigned short	uid;
E 29
I 29
int	uid;
E 29
{
	register struct nametable	*n, *start;
E 41
I 41
#define NUID	64
E 41

D 41
	/*
	 * find the uid or an empty slot.
	 * return NULL if neither found.
	 */
E 41
I 41
struct ncache {
	int	uid;
	char	name[NMAX+1];
} nc[NUID];
E 41

D 41
	n = start = nametable + (uid % (NUID - 20));
	while (n->nt_name[0] && n->nt_uid != uid) {
		if ((n += 5) >= &nametable[NUID])
			n -= NUID;
		if (n == start)
			return((struct nametable *)NULL);
	}
	return(n);
}

E 41
I 41
/*
 * This function assumes that the password file is hashed
 * (or some such) to allow fast access based on a uid key.
 */
E 61
E 41
E 25
D 69
char *
D 61
getname(uid)
{
D 25
	register struct passwd *pw;
	static init;
	struct passwd *getpwent();
E 25
I 25
D 41
	register struct passwd		*pw;
	static				init = 0;
	struct passwd			*getpwent();
	register struct nametable	*n;
I 34
	extern int			_pw_stayopen;
E 41
I 41
	register struct passwd *pw;
	struct passwd *getpwent();
	register int cp;
I 57
#ifdef notdef
E 57
	extern int _pw_stayopen;
E 41
E 34
E 25

D 4
	if (names[uid][0])
E 4
I 4
D 25
	if (uid >= 0 && uid < NUID && names[uid][0])
E 4
		return (&names[uid][0]);
	if (init == 2)
		return (0);
	if (init == 0)
		setpwent(), init = 1;
	while (pw = getpwent()) {
		if (pw->pw_uid >= NUID)
			continue;
		if (names[pw->pw_uid][0])
			continue;
D 19
		strncpy(names[pw->pw_uid], pw->pw_name, NMAX);
E 19
I 19
		(void) strncpy(names[pw->pw_uid], pw->pw_name, NMAX);
E 19
		if (pw->pw_uid == uid)
			return (&names[uid][0]);
E 25
I 25
D 41
	/*
	 * find uid in hashed table; add it if not found.
	 * return pointer to name.
	 */
E 41
I 41
	_pw_stayopen = 1;
I 57
#endif
E 57
E 41

D 41
	if ((n = findslot(uid)) == NULL)
		return((char *)NULL);

	if (n->nt_name[0])	/* occupied? */
		return(n->nt_name);

	switch (init) {
		case 0:
			setpwent();
I 34
			_pw_stayopen = 1;
E 34
			init = 1;
			/* intentional fall-thru */
		case 1:
			while (pw = getpwent()) {
				if (pw->pw_uid < 0)
					continue;
				if ((n = findslot(pw->pw_uid)) == NULL) {
					endpwent();
					init = 2;
					return((char *)NULL);
				}
				if (n->nt_name[0])
					continue;	/* duplicate, not uid */
				strncpy(n->nt_name, pw->pw_name, NMAX);
				n->nt_uid = pw->pw_uid;
				if (pw->pw_uid == uid)
					return (n->nt_name);
			}
			endpwent();
			init = 2;
			/* intentional fall-thru */
		case 2:
			return ((char *)NULL);
E 25
	}
I 29
	/* NOTREACHED */
E 41
I 41
#if	(((NUID) & ((NUID) - 1)) != 0)
	cp = uid % (NUID);
#else
	cp = uid & ((NUID) - 1);
#endif
	if (uid >= 0 && nc[cp].uid == uid && nc[cp].name[0])
		return (nc[cp].name);
	pw = getpwuid(uid);
	if (!pw)
		return (0);
	nc[cp].uid = uid;
	SCPYN(nc[cp].name, pw->pw_name);
	return (nc[cp].name);
E 41
E 29
D 25
	init = 2;
	endpwent();
	return (0);
E 25
}

D 29
char	*freebase;
int	nleft;

E 29
char *
E 61
D 29
alloc(size)
	int size;
{
	register char *cp;
	register int i;

I 23
#ifdef sun
	size = (size+1)&~1;
#endif
E 23
	if (size > nleft) {
D 19
		freebase = (char *)sbrk(i = size > 2048 ? size : 2048);
E 19
I 19
		freebase = (char *)sbrk((int)(i = size > 2048 ? size : 2048));
E 19
D 28
		if (freebase == 0) {
E 28
I 28
		if (freebase == (char *)-1) {
E 28
			fprintf(stderr, "ps: ran out of memory\n");
			exit(1);
		}
		nleft = i - size;
	} else
		nleft -= size;
	cp = freebase;
	for (i = size; --i >= 0; )
		*cp++ = 0;
	freebase = cp;
	return (cp - size);
}

char *
E 29
savestr(cp)
	char *cp;
E 69
I 69
#ifdef lint
/* VARARGS1 */
error(fmt) char *fmt; { (void) fputs(fmt, stderr); exit(1); /* NOTREACHED */ }
#else
error(va_alist)
	va_dcl
E 69
{
D 29
	register int len;
E 29
I 29
D 69
	register unsigned len;
E 29
	register char *dp;
E 69
I 69
	char *fmt;
	va_list ap;
E 69

D 69
	len = strlen(cp);
D 29
	dp = (char *)alloc(len+1);
E 29
I 29
	dp = (char *)calloc(len+1, sizeof (char));
E 29
D 19
	strcpy(dp, cp);
E 19
I 19
	(void) strcpy(dp, cp);
E 19
	return (dp);
I 29
}

D 61
/*
 * This routine was stolen from adb to simulate memory management
 * on the VAX.
 */
off_t
vtophys(loc)
long	loc;
E 61
I 61
error(a, b, c, d, e)
	char *a, *b, *c, *d, *e;
E 61
{
D 61
	register	p;
	off_t	newloc;

D 48
	newloc = loc & ~0xc0000000;
E 48
I 48
	newloc = loc & ~KERNBASE;
E 48
	p = btop(newloc);
D 48
	if ((loc & 0xc0000000) == 0) {
E 48
I 48
	if ((loc & KERNBASE) == 0) {
E 48
		fprintf(stderr, "Vtophys: translating non-kernel address\n");
		return((off_t) -1);
	}
	if (p >= Syssize) {
		fprintf(stderr, "Vtophys: page out of bound (%d>=%d)\n",
			p, Syssize);
		return((off_t) -1);
	}
	if (Sysmap[p].pg_v == 0
	&& (Sysmap[p].pg_fod || Sysmap[p].pg_pfnum == 0)) {
		fprintf(stderr, "Vtophys: page not valid\n");
		return((off_t) -1);
	}
	loc = (long) (ptob(Sysmap[p].pg_pfnum) + (loc & PGOFSET));
	return(loc);
E 61
I 61
	fprintf(stderr, "ps: ");
	fprintf(stderr, a, b, c, d, e);
	fprintf(stderr, "\n");
E 69
I 69
	va_start(ap);
	fmt = va_arg(ap, char *);
	(void) fprintf(stderr, "ps: ");
	(void) vfprintf(stderr, fmt, ap);
	(void) fprintf(stderr, "\n");
E 69
	exit(1);
E 61
I 39
}
I 69
#endif
E 69

D 61
/*
 * since we can't init unions, the cleanest way to use a.out.h instead
 * of nlist.h (required since nlist() uses some defines) is to do a
 * runtime copy into the nl array -- sigh
 */
init_nlist()
E 61
I 61
syserror(a)
	char *a;
E 61
{
D 61
	register struct nlist *np;
	register char **namep;
E 61
I 61
	extern errno;
E 61

D 61
	nllen = sizeof nl_names / sizeof (char *);
	np = nl = (struct nlist *) malloc(nllen * sizeof (struct nlist));
	if (np == NULL) {
		fprintf(stderr, "ps: out of memory allocating namelist\n");
		exit(1);
	}
	namep = &nl_names[0];
	while (nllen > 0) {
		np->n_un.n_name = *namep;
		if (**namep == '\0')
			break;
		namep++;
		np++;
	}
E 61
I 61
	error("%s: %s", a, strerror(errno));
E 61
}

E 71
/*
D 61
 * nlist - retreive attributes from name list (string table version)
 * 	modified to add wait channels - Charles R. LaBrec 8/85
E 61
I 61
 * ICK (all for getopt), would rather hide the ugliness
 * here than taint the main code.
 *
 *  ps foo -> ps -foo
 *  ps 34 -> ps -p34
 *
 * The old convention that 't' with no trailing tty arg means the users
 * tty, is only supported if argv[1] doesn't begin with a '-'.  This same
 * feature is available with the option 'T', which takes no argument.
E 61
 */
D 61
nlist(name, list)
	char *name;
	struct nlist *list;
{
	register struct nlist *p, *q;
	register char *s1, *s2;
	register n, m;
	int maxlen, nreq;
	FILE *f;
	FILE *sf;
	off_t sa;		/* symbol address */
	off_t ss;		/* start of strings */
	int type;
	struct exec buf;
	struct nlist space[BUFSIZ/sizeof (struct nlist)];
	char nambuf[BUFSIZ];

	maxlen = 0;
	for (q = list, nreq = 0; q->n_un.n_name && q->n_un.n_name[0]; q++, nreq++) {
		q->n_type = 0;
		q->n_value = 0;
		q->n_desc = 0;
		q->n_other = 0;
		n = strlen(q->n_un.n_name);
		if (n > maxlen)
			maxlen = n;
	}
	f = fopen(name, "r");
	if (f == NULL)
		return (-1);
	fread((char *)&buf, sizeof buf, 1, f);
	if (N_BADMAG(buf)) {
		fclose(f);
		return (-1);
	}
	sf = fopen(name, "r");
	if (sf == NULL) {
		/* ??? */
		fclose(f);
		return(-1);
	}
	sa = N_SYMOFF(buf);
	ss = sa + buf.a_syms;
	n = buf.a_syms;
	fseek(f, sa, 0);
	while (n) {
		m = sizeof (space);
		if (n < m)
			m = n;
		if (fread((char *)space, m, 1, f) != 1)
			break;
		n -= m;
		for (q = space; (m -= sizeof(struct nlist)) >= 0; q++) {
			if (q->n_un.n_strx == 0 || q->n_type & N_STAB)
				continue;
			/*
			 * since we know what type of symbols we will get,
			 * we can make a quick check here -- crl
			 */
			type = q->n_type & (N_TYPE | N_EXT);
			if ((q->n_type & N_TYPE) != N_ABS
			    && type != (N_EXT | N_DATA)
			    && type != (N_EXT | N_BSS))
				continue;
			fseek(sf, ss+q->n_un.n_strx, 0);
			fread(nambuf, maxlen+1, 1, sf);
			/* if using wchans, add it to the list of channels */
			if (!nflg)
				addchan(&nambuf[1], (caddr_t) q->n_value);
			for (p = list; p->n_un.n_name && p->n_un.n_name[0]; p++) {
				s1 = p->n_un.n_name;
				s2 = nambuf;
				if (strcmp(p->n_un.n_name, nambuf) == 0) {
					p->n_value = q->n_value;
					p->n_type = q->n_type;
					p->n_desc = q->n_desc;
					p->n_other = q->n_other;
					--nreq;
					break;
				}
			}
		}
	}
alldone:
	fclose(f);
	fclose(sf);
	return (nreq);
}

/*
 * add the given channel to the channel list
 */
addchan(name, caddr)
char *name;
caddr_t caddr;
{
	static int left = 0;
	register struct wchan *wp;
	register char **p;

	for (p = wchan_stop_list; *p; p++) {
		if (**p != *name)	/* quick check first */
			continue;
		if (strncmp(name, *p, WNAMESIZ) == 0)
			return;		/* if found, don't add */
	}
	if (left == 0) {
		if (wchanhd) {
			left = 100;
			wchanhd = (struct wchan *) realloc(wchanhd,
				(nchans + left) * sizeof (struct wchan));
		} else {
			left = 600;
			wchanhd = (struct wchan *) malloc(left
				* sizeof (struct wchan));
		}
		if (wchanhd == NULL) {
			fprintf(stderr, "ps: out of memory allocating wait channels\n");
			nflg++;
			return;
		}
	}
	left--;
	wp = &wchanhd[nchans++];
	strncpy(wp->wc_name, name, WNAMESIZ);
	wp->wc_name[WNAMESIZ] = '\0';
	wp->wc_caddr = caddr;
}

/*
 * returns the symbolic wait channel corresponding to chan
 */
E 61
D 88
char *
E 88
I 88
static char *
E 88
D 61
getchan(chan)
register caddr_t chan;
E 61
I 61
kludge_oldps_options(s)
	char *s;
E 61
{
D 61
	register i, iend;
	register char *prevsym;
	register struct wchan *wp;
E 61
I 61
D 69
	int len = strlen(s), numlen = 0;
E 69
I 69
D 71
	size_t len = strlen(s);
E 71
I 71
	size_t len;
E 71
E 69
	char *newopts, *ns, *cp;
E 61

D 61
	prevsym = "???";		/* nothing, to begin with */
	if (chan) {
		for (i = 0; i < NWCINDEX; i++)
			if ((unsigned) chan < (unsigned) wchan_index[i])
				break;
		iend = i--;
		if (i < 0)		/* can't be found */
			return prevsym;
		iend *= nchans;
		iend /= NWCINDEX;
		i *= nchans;
		i /= NWCINDEX;
		wp = &wchanhd[i];
		for ( ; i < iend; i++, wp++) {
			if ((unsigned) wp->wc_caddr > (unsigned) chan)
				break;
			prevsym = wp->wc_name;
E 61
I 61
D 69
	if ((newopts = ns = (char *)malloc(len+2)) == NULL)
E 69
I 69
D 71
	if ((newopts = ns = malloc(len + 2)) == NULL)
E 69
		error("out of memory");
E 71
I 71
	len = strlen(s);
D 81
	if ((newopts = ns = malloc(len + 2)) == NULL) {
		(void)fprintf(stderr, "ps: %s\n", strerror(errno));
		exit(1);
	}
E 81
I 81
	if ((newopts = ns = malloc(len + 2)) == NULL)
D 92
		err("%s", strerror(errno));
E 92
I 92
		err(1, NULL);
E 92
E 81
E 71
	/*
	 * options begin with '-'
	 */
	if (*s != '-')
		*ns++ = '-';	/* add option flag */
	/*
	 * gaze to end of argv[1]
	 */
	cp = s + len - 1;
	/*
	 * if last letter is a 't' flag with no argument (in the context
	 * of the oldps options -- option string NOT starting with a '-' --
D 69
	 * then convert to 'T' (meaning *this* terminal, i.e. ttyname(0).
E 69
I 69
	 * then convert to 'T' (meaning *this* terminal, i.e. ttyname(0)).
E 69
	 */
	if (*cp == 't' && *s != '-')
		*cp = 'T';
	else {
		/*
		 * otherwise check for trailing number, which *may* be a
		 * pid.
		 */
D 69
		while (isdigit(*cp)) {
E 69
I 69
		while (cp >= s && isdigit(*cp))
E 69
			--cp;
D 69
			numlen++;
E 61
		}
E 69
	}
D 61
	return prevsym;
}
E 61
I 61
	cp++;
D 69
	bcopy(s, ns, cp - s);	/* copy everything up to trailing number */
	while (*ns)
		ns++;
E 69
I 69
D 92
	bcopy(s, ns, (size_t)(cp - s));	/* copy up to trailing number */
E 92
I 92
	memmove(ns, s, (size_t)(cp - s));	/* copy up to trailing number */
E 92
	ns += cp - s;
E 69
	/*
	 * if there's a trailing number, and not a preceding 'p' (pid) or
	 * 't' (tty) flag, then assume it's a pid and insert a 'p' flag.
	 */
D 69
	if (isdigit(*cp) && (cp == s || *(cp-1) != 't' && *(cp-1) != 'p' &&
	   ((cp-1) == s || *(cp-2) != 't')))
E 69
I 69
	if (isdigit(*cp) && (cp == s || cp[-1] != 't' && cp[-1] != 'p' &&
	    (cp - 1 == s || cp[-2] != 't')))
E 69
		*ns++ = 'p';
D 69
	strcat(ns, cp);		/* and append the number */
E 69
I 69
D 88
	(void) strcpy(ns, cp);		/* and append the number */
E 88
I 88
	(void)strcpy(ns, cp);		/* and append the number */
E 88
E 69
E 61

D 61
/*
 * used in sorting the wait channel array
 */
int
wchancomp (w1, w2)
struct wchan *w1, *w2;
{
	register unsigned c1, c2;

	c1 = (unsigned) w1->wc_caddr;
	c2 = (unsigned) w2->wc_caddr;
	if (c1 > c2)
		return 1;
	else if (c1 == c2)
		return 0;
	else
		return -1;
E 61
I 61
	return (newopts);
I 71
D 92
}

D 81
#ifdef lint
/* VARARGS1 */
error(fmt) char *fmt; { (void) fputs(fmt, stderr); exit(1); /* NOTREACHED */ }
E 81
I 81
#if __STDC__
#include <stdarg.h>
E 81
#else
D 81
error(fmt)
E 81
I 81
#include <varargs.h>
#endif

void
#if __STDC__
err(const char *fmt, ...)
#else
err(fmt, va_alist)
E 81
	char *fmt;
I 81
        va_dcl
#endif
E 81
{
	va_list ap;
D 81

E 81
I 81
#if __STDC__
E 81
	va_start(ap, fmt);
D 81
	(void) fprintf(stderr, "ps: ");
	(void) vfprintf(stderr, fmt, ap);
	(void) fprintf(stderr, "\n");
E 81
I 81
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "ps: ");
	(void)vfprintf(stderr, fmt, ap);
E 81
	va_end(ap);
I 81
	(void)fprintf(stderr, "\n");
E 81
	exit(1);
I 81
	/* NOTREACHED */
E 92
E 81
}
D 81
#endif
E 81

I 88
static void
E 88
usage()
{
I 96

E 96
D 88
	(void) fprintf(stderr,
E 88
I 88
	(void)fprintf(stderr,
E 88
D 81
	    "usage:\tps [ -aChjlmrSsTuvwx ] [ -O|o fmt ] [ -p pid ] [ -t tty ] [ system ] [ core ] [ swap ]\n\t ps [ -L ]\n");
E 81
I 81
D 96
"usage: ps [-aChjlmrSTuvwx] [-O|o fmt] [-p pid] [-t tty]\n\t  [-M core] [-N system] [-W swap]\n       ps [-L]\n");
E 96
I 96
	    "usage:\t%s\n\t   %s\n\t%s\n",
	    "ps [-aChjlmrSTuvwx] [-O|o fmt] [-p pid] [-t tty]",
	    "[-M core] [-N system] [-W swap]",
	    "ps [-L]");
E 96
E 81
	exit(1);
E 71
E 61
E 39
E 29
I 16
D 23
}

walk(np)
	int np;
{
	register int i, j, k, l, m;
#undef afl
#undef sfl
#define afl(i,f) savcom[i].ap -> f
#define sfl(i,f) savcom[i].sun.ssp -> f

	for(i = 0; i < np; i = j) {
		for(j = i; afl(j,a_ttyd) == afl(i,a_ttyd); j++) {
			sfl(j,ss_brother) = -1;
			sfl(j,ss_sons) = -1;
		}
		for(k = i+1; k < j; k++) {
			if(sfl(k,ss_ppid) == sfl(i,ss_ppid)) {
				for(l=i; sfl(l,ss_brother) != -1; 
					l=sfl(l,ss_brother)) ;
				sfl(l,ss_brother) = k;
				goto next;
			}
			for(l = i; l < j; l++) {
				if(l == k) continue;
				if(sfl(k,ss_ppid) == afl(l,a_pid)) {
					if(sfl(l,ss_sons) == -1)
					    sfl(l,ss_sons) = k;
					else {
					    for(m = sfl(l,ss_sons);
						sfl(m,ss_brother) != -1;
						m = sfl(m,ss_brother)) ;
					    sfl(m,ss_brother) = k;
					}
					goto next;
				}
			}
			for(l = i; l < j; l++) {
				if(l == k) continue;
				if(sfl(k,ss_ppid) == sfl(l,ss_ppid)) {
					for(m = k; sfl(m,ss_brother) != -1;
					    m = sfl(m,ss_brother)) ;
					sfl(m,ss_brother) = l;
				}
			}
		next: ;
		}
		walk1(i, 0);
	}
}

walk1(pno, depth)
	int pno, depth;
{
	if(pno == -1)
		return;
/***    printf("%5d, %d\n",outargs[pno].o_pid, depth);  ***/
	walkpr(&savcom[pno], depth);
	walk1(sfl(pno,ss_sons), depth+1);
	walk1(sfl(pno,ss_brother), depth);
}

char *sshdr =
"TTY User     SZ RSS  CPU  S      PID  ";

walkpr(a, depth)
	register struct savcom *a;
	int depth;
{
D 19
	long tm;
E 19

	if(!depth) {
		printf("%-2.2s", a->ap->a_tty);
		printf(" %-8.8s", getname(a->ap->a_uid));
	} else
		printf("   %-8s", &".......*"[8-(depth<=8?depth:8)]);
	printf("%4d%4d", a->ap->a_size/2, a->ap->a_rss/2);
	ptime(a->ap);
	/* Once there was a "CCPU" field here.  Subsumed by -S now. */
	printf(" %4.4s", state(a->ap));
	printf("%6u ", a->ap->a_pid);
	if (a->ap->a_pid == 0)
		printf(" swapper");
	else if (a->ap->a_pid == 2)
		printf(" pagedaemon");
	else
		printf(" %.*s", twidth - cmdstart - 2, a->ap->a_cmdp);
	putchar('\n');
E 23
E 16
}
E 1
