h49500
s 00003/00002/01042
d D 8.16 95/05/09 17:14:15 mckusick 92 91
c change mountlist to CIRCLEQ so we can do unmountall (from mycroft)
e
s 00013/00033/01031
d D 8.15 95/05/02 12:36:47 mckusick 91 90
c new header files and new mount organization
e
s 00004/00004/01060
d D 8.14 95/04/30 09:15:05 bostic 90 89
c I changed the printout for the t_session field since in MIPS,
c the address can be 0x80000000 to 0xC0000000 and masking the high
c order bit off still generates a 7 digit address (instead of only 6
c for the print field).
c From: ralphc@pyramid.com (Ralph Campbell)
e
s 00005/00004/01059
d D 8.13 95/04/29 11:53:37 bostic 89 88
c change devname(3) to return NULL, not ??
e
s 00004/00004/01059
d D 8.12 94/08/20 23:01:17 mckusick 88 87
c use new queue.h data structures
e
s 00000/00001/01063
d D 8.11 94/08/14 16:44:50 mckusick 87 86
c MNT_USER is gone
e
s 00097/00117/00967
d D 8.10 94/04/28 07:34:38 pendry 86 85
c recognise all mount flags, fs type names, and union vnodes.
e
s 00002/00001/01082
d D 8.9 94/02/16 18:03:12 bostic 85 84
c init the 'num' variable in kinfo_vnodes().
c From: "Chris G. Demetriou" <cgd@vangogh.CS.Berkeley.EDU>
e
s 00000/00002/01083
d D 8.8 94/02/10 23:09:06 pendry 84 83
c don't need pathnames.h any more
e
s 00001/00001/01084
d D 8.7 94/01/23 12:21:30 bostic 83 82
c MOUNT_PC -> MOUNT_MSDOS
e
s 00002/00002/01083
d D 8.6 94/01/23 12:19:36 bostic 82 81
c MOUNT_PC -> MOUNT_MSDOS
e
s 00014/00014/01071
d D 8.5 94/01/04 14:50:44 mckusick 81 80
c update for new queue structures
e
s 00009/00008/01076
d D 8.4 93/12/02 21:00:16 hibler 80 79
c make swapmode output format consistent with df's
e
s 00064/00023/01020
d D 8.3 93/12/01 00:06:56 hibler 79 78
c teach it about sequential swap devices
e
s 00013/00013/01030
d D 8.2 93/09/23 19:37:42 bostic 78 77
c changes for 4.4BSD-Lite requested by USL
e
s 00005/00005/01038
d D 8.1 93/06/06 14:04:02 bostic 77 76
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00260/00286/00783
d D 5.42 93/06/05 18:15:53 bostic 76 75
c lots of semantic sugar, do things the 4BSD way... ;-}
e
s 00219/00271/00850
d D 5.41 93/06/05 17:00:12 mckusick 75 74
c detox; cleanup to reflect current system
e
s 00012/00000/01109
d D 5.40 93/04/13 19:52:24 ralph 74 73
c added mips ttys
e
s 00086/00551/01023
d D 5.39 93/04/02 23:37:53 mckusick 73 72
c convert kinfo to sysctl; fix vnode and file printing
e
s 00007/00009/01567
d D 5.38 92/01/27 15:15:42 bostic 72 71
c put on SCCS headers
e
s 00018/00013/01558
d D 5.37 92/01/27 15:14:34 bostic 71 70
c don't let users create their own symbol table for the running kernel
e
s 00071/00089/01500
d D 5.36 92/01/27 14:13:19 marc 70 69
c make vodes work on dead kernel
e
s 00075/00035/01514
d D 5.35 91/06/26 14:00:38 marc 69 68
c print file structures from kernel
e
s 00002/00001/01547
d D 5.34 91/05/29 08:59:29 karels 68 67
c can't print bits that no longer exist
e
s 00002/00002/01546
d D 5.33 91/05/17 15:15:10 marc 67 66
c bug - calling devname with wrong argument
e
s 00004/00004/01544
d D 5.32 91/05/06 17:04:07 karels 66 64
c no text.h for newvm; use S_IFCHR/S_IFBLK as second arg to devname
e
s 00006/00004/01544
d R 5.32 91/05/06 16:40:31 karels 65 64
c update to new devname
e
s 00054/00022/01494
d D 5.31 91/05/02 19:08:19 karels 64 63
c hack for newvm; need to fix some of this later.
c For now (at least), disable -p and -U; swap ought to be fixed.
e
s 00060/00071/01456
d D 5.30 91/05/02 15:26:00 marc 63 62
c split out namelist into mandatory and optional parts, different vnode fal;gs, casts (yuck)
e
s 00003/00002/01524
d D 5.29 91/03/15 10:17:21 bostic 62 61
c ANSI
e
s 00042/00007/01484
d D 5.28 90/10/29 13:39:33 karels 61 60
c add hp tty devices; add session to -t output, removing rcc/ccc/occ;
c hack to continue if nlist entries aren't found; minor cleanups
e
s 00085/00079/01406
d D 5.27 90/08/31 15:55:06 marc 60 59
c fix -u (change to -U); fix -s
e
s 00049/00039/01436
d D 5.26 90/06/29 00:48:17 marc 59 58
c update -v;  -u still broken
e
s 00097/00090/01378
d D 5.25 90/05/08 15:58:46 marc 58 57
c address of vnode prepends vnode, new mount flags, print tty pgid
e
s 00475/00176/00993
d D 5.24 90/04/18 14:41:44 marc 57 56
c vnodes
e
s 00002/00003/01167
d D 5.23 89/08/15 16:42:12 mckusick 56 55
c delete PGRP (the id is no longer in the proc structure);
c expand the flags field to eight bytes to show all flags (4.3BSD/etc/160)
e
s 00003/00001/01167
d D 5.22 89/08/14 18:24:27 bostic 55 54
c NETLDISC isn't in new tty driver by default
e
s 00027/00021/01141
d D 5.21 89/08/10 17:55:33 mckusick 54 53
c update for vnodes
e
s 00005/00004/01157
d D 5.20 89/04/02 14:38:22 bostic 53 52
c add pathnames.h
e
s 00052/00030/01109
d D 5.19 88/10/20 18:52:37 marc 52 51
c new terminal driver == new -t format
e
s 00006/00000/01133
d D 5.18 88/02/27 11:11:19 bostic 51 50
c add mpcc tty driver; from Keith Muller
e
s 00033/00052/01100
d D 5.17 88/01/01 17:12:18 bostic 50 49
c use getopt; fix usage statement; -a should imply -p; minor cleanups
e
s 00001/00000/01151
d D 5.16 87/12/26 13:04:56 bostic 49 48
c declare rmalloc, ANSI C fix
e
s 00020/00020/01131
d D 5.15 87/08/30 08:58:06 mckusick 48 47
c getw => getword to avoid stdio definition; bug report 4.3BSD/etc/84
e
s 00004/00000/01147
d D 5.14 87/08/27 07:23:59 bostic 47 46
c make pstat recgonize SLIP; bug report 4.3BSD/etc/82
e
s 00032/00001/01115
d D 5.13 87/08/06 15:35:44 marc 46 45
c under -t, check for qdss tty structs
e
s 00006/00006/01110
d D 5.12 87/04/06 14:58:07 bostic 45 44
c printf format/arg mismatch
e
s 00001/00001/01115
d D 5.11 87/04/06 11:39:05 bostic 44 43
c printf format/argument mismatch
e
s 00004/00008/01112
d D 5.10 87/03/28 17:34:51 karels 43 42
c make -k work on tahoe
e
s 00059/00040/01061
d D 5.9 86/10/13 15:09:00 sam 42 41
c tahoe support
e
s 00002/00001/01099
d D 5.8 86/05/05 17:53:21 mckusick 41 40
c do not count swap devices that have not been enabled (from Guy Harris)
e
s 00093/00022/01007
d D 5.7 86/01/31 08:16:31 karels 40 39
c sanity checks on array sizes, check return of malloc;
c core dumping if /vmunix is wrong is not very elegant
e
s 00001/00005/01028
d D 5.6 85/11/10 13:25:13 karels 39 38
c no more ntab discipline
e
s 00006/00000/01027
d D 5.5 85/10/28 12:36:24 bloom 38 37
c add support for dmz
e
s 00001/00001/01026
d D 5.4 85/10/28 10:15:43 bloom 37 36
c change define for SYSMAP to be correct
e
s 00036/00079/00991
d D 5.3 85/09/04 21:03:15 mckusick 36 35
c dhu support (from mcvax!jim Jim McKie)
e
s 00032/00004/01038
d D 5.2 85/07/26 15:41:33 mckusick 35 34
c fixes for reading kernel dumps (from pur-ee!ghg)
e
s 00015/00002/01027
d D 5.1 85/06/04 16:43:34 dist 34 33
c Add copyright
e
s 00048/00031/00981
d D 4.30 85/06/03 09:39:59 karels 33 32
c hacks on -u: use /dev/mem, fix up format; still lose because 1K
c isn't enough of the u.
e
s 00062/00024/00950
d D 4.29 85/04/16 09:17:59 karels 32 31
c missing ctod(); handle >128 terminals
e
s 00002/00002/00972
d D 4.28 85/04/03 17:04:38 kupfer 31 30
c Fix calculation of swap allocation for text segments.
e
s 00028/00012/00946
d D 4.27 85/02/04 17:29:51 edward 30 29
c print more (but not all) state info in -t
e
s 00007/00011/00951
d D 4.26 84/07/25 15:32:35 bloom 29 28
c Fix user structure to agree with namei change
e
s 00020/00002/00942
d D 4.25 84/02/06 15:34:01 ralph 28 27
c check for dmf's too (-t option).
e
s 00065/00050/00879
d D 4.24 83/10/15 18:45:56 sam 27 26
c swap stats cleanup: print values in kilobytes, calculate true 
c size of swap space instead of believing nswap variable in kernel, rearrange 
c allocations to come before read of swap map in case segment expansion forces 
c change in swap map state (unlikely); also put xdsize routine in-line and 
c take vusize routine verbatim from kernel code
e
s 00001/00000/00928
d D 4.23 83/10/06 10:54:38 sam 26 25
c correct swap map overflow problem; from kre
e
s 00003/00002/00925
d D 4.22 83/06/18 17:07:48 sam 25 24
c no string present to print in case of error
e
s 00004/00001/00923
d D 4.21 83/06/14 01:31:27 sam 24 23
c file table definition changed
e
s 00008/00011/00916
d D 4.20 83/05/28 14:49:43 sam 23 22
c fix up file table printout
e
s 00219/00037/00708
d D 4.19 83/05/18 02:45:42 sam 22 21
c changes mostly for new swapping algorithms (from shannon@sun.UUCP)
e
s 00026/00004/00719
d D 4.18 83/04/15 14:29:14 edward 21 20
c Now knows about dmf.  And formatting changed slightly.
e
s 00001/00001/00722
d D 4.17 82/12/24 12:47:37 sam 20 19
c pte.h moved
e
s 00014/00018/00709
d D 4.16 82/12/13 21:58:29 sam 19 18
c update for new data structures
e
s 00042/00019/00685
d D 4.15 82/10/19 16:37:23 sam 18 16
c add usage messages and update for 4.1b
e
s 00042/00019/00685
d R 4.15 82/10/19 16:35:08 sam 17 16
c add usages and fix up tables printouts for 4.1b
e
s 00001/00001/00703
d D 4.14 82/06/27 11:35:35 root 16 15
c fix to -f per cak@purdue
e
s 00000/00001/00704
d D 4.13 82/05/10 17:35:23 sam 15 14
c no more u_dbuf
e
s 00001/00001/00704
d D 4.12 82/05/10 17:32:57 sam 14 13
c i_rdev redefined
e
s 00012/00018/00693
d D 4.11 82/03/31 12:04:38 root 13 12
c pty stuff
e
s 00031/00115/00680
d D 4.10 82/02/28 21:27:24 wnj 12 9
c new flag names for tty and no mpx and sockets
e
s 00034/00006/00839
d R 4.11 81/06/11 15:45:08 wnj 11 10
c print pty's
e
s 00050/00000/00795
d R 4.10 81/05/08 15:04:09 root 10 9
c add stuff for new pipe code
e
s 00010/00000/00785
d D 4.9 81/05/07 14:21:41 root 9 8
c fix pstat -tk
e
s 00002/00000/00783
d D 4.8 81/04/15 03:06:53 root 8 7
c fix bug in 'k' option
e
s 00002/00005/00781
d D 4.7 81/04/14 20:08:59 root 7 6
c fixed bugs with 'k' flag
e
s 00007/00006/00779
d D 4.6 81/03/10 07:02:00 wnj 6 5
c miscellaneous minor fixups
e
s 00093/00053/00692
d D 4.5 81/02/28 23:05:43 wnj 5 4
c new kernel proc structure scheme
e
s 00120/00001/00625
d D 4.4 81/02/10 14:47:36 hickman 4 3
c Added mpx debug stuff (-mg flags) (kebh)
e
s 00002/00002/00624
d D 4.3 80/11/15 14:26:48 bill 3 2
c fixes per mja
e
s 00004/00005/00622
d D 4.2 80/10/15 23:52:44 bill 2 1
c un-barfup pstat
e
s 00627/00000/00000
d D 4.1 80/10/01 17:27:52 bill 1 0
c date and time created 80/10/01 17:27:52 by bill
e
u
U
t
T
I 34
D 72
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 72
I 72
/*-
D 75
 * Copyright (c) 1980, 1991 The Regents of the University of California.
E 75
I 75
D 77
 * Copyright (c) 1980, 1991, 1993 The Regents of the University of California.
E 75
 * All rights reserved.
E 77
I 77
D 86
 * Copyright (c) 1980, 1991, 1993
E 86
I 86
 * Copyright (c) 1980, 1991, 1993, 1994
E 86
 *	The Regents of the University of California.  All rights reserved.
E 77
 *
D 75
 * %sccs.include.proprietary.c%
E 75
I 75
 * %sccs.include.redist.c%
E 75
E 72
 */

E 34
I 18
#ifndef lint
E 18
I 1
D 12
static char *sccsid = "%W% (Berkeley) %G%";
E 12
I 12
D 22
static char *sccsid = "%Z% (Berkeley) %E%";
E 22
I 22
D 34
static char *sccsid = "%W% (Berkeley) %G%";
E 22
I 18
#endif
E 34
I 34
D 77
char copyright[] =
D 70
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 70
I 70
D 72
"@(#) Copyright (c) 1980 Regents of the University of California.\n\
E 72
I 72
D 75
"%Z% Copyright (c) 1980, 1991 The Regents of the University of California.\n\
E 75
I 75
"%Z% Copyright (c) 1980, 1991, 1993 The Regents of the University of California.\n\
E 75
E 72
E 70
 All rights reserved.\n";
E 77
I 77
static char copyright[] =
D 86
"%Z% Copyright (c) 1980, 1991, 1993\n\
E 86
I 86
"%Z% Copyright (c) 1980, 1991, 1993, 1994\n\
E 86
	The Regents of the University of California.  All rights reserved.\n";
E 77
D 50
#endif not lint
E 50
I 50
#endif /* not lint */
E 50

#ifndef lint
D 70
static char sccsid[] = "%W% (Berkeley) %G%";
E 70
I 70
D 72
static char sccsid[] = "@(#)pstat.c	5.35 (Berkeley) 6/26/91";
E 72
I 72
static char sccsid[] = "%W% (Berkeley) %G%";
E 72
E 70
D 50
#endif not lint
E 50
I 50
#endif /* not lint */
E 50

E 34
E 18
E 12
D 72
/*
 * Print system stuff
 */
E 72
D 54

E 54
D 43
#define mask(x) (x&0377)
I 42
#ifdef vax
E 42
#define	clear(x) ((int)x&0x7fffffff)
I 42
#endif
#ifdef tahoe
#define	clear(x) ((int)x&~0xc0000000)
#endif
E 42

E 43
#include <sys/param.h>
D 57
#include <sys/dir.h>
I 18
#define	KERNEL
E 18
#include <sys/file.h>
I 18
#undef	KERNEL
E 57
E 18
D 75
#include <sys/user.h>
#include <sys/proc.h>
E 75
D 66
#include <sys/text.h>
E 66
D 54
#include <sys/inode.h>
E 54
I 54
#include <sys/time.h>
#include <sys/vnode.h>
E 54
#include <sys/map.h>
I 81
#include <sys/ucred.h>
E 81
I 52
#define KERNEL
I 57
D 73
#define NFS
E 73
#include <sys/file.h>
D 73
#include <sys/mount.h>
E 73
I 58
D 70
#include <ufs/quota.h>
E 58
#include <ufs/inode.h>
E 70
I 70
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
I 73
D 81
#undef KERNEL
E 81
#define NFS
#include <sys/mount.h>
#undef NFS
I 86
#include <sys/uio.h>
#include <sys/namei.h>
#include <miscfs/union/union.h>
E 86
I 81
#undef KERNEL
E 81
E 73
E 70
#include <sys/stat.h>
I 91
#include <nfs/rpcv2.h>
#include <nfs/nfsproto.h>
#include <nfs/nfs.h>
E 91
D 73
#include <nfs/nfsv2.h>
#include <nfs/nfs.h>
E 73
#include <nfs/nfsnode.h>
I 73
D 75
/* #include <nfs/nfsv2.h> */
/* #include <nfs/nfs.h> */
E 75
E 73
E 57
E 52
I 19
#include <sys/ioctl.h>
E 19
#include <sys/tty.h>
I 52
D 73
#undef KERNEL
E 73
E 52
#include <sys/conf.h>
I 64

D 73
#ifdef SPPWAIT
#define NEWVM
#endif
E 73
I 73
#include <sys/sysctl.h>
E 73

D 73
#ifndef NEWVM
E 64
#include <sys/vm.h>
D 54
#include <nlist.h>
E 54
I 54
D 57
#include <ufs/inode.h>
E 57
E 54
D 20
#include <sys/pte.h>
E 20
I 20
#include <machine/pte.h>
I 66
#include <sys/text.h>
E 66
I 64
#endif
E 64
I 63
#include <sys/kinfo.h>
E 63
I 54

E 73
I 57
D 63
#include <kvm.h>
E 63
E 57
D 76
#include <nlist.h>
E 76
I 76
#include <err.h>
E 76
I 63
#include <kvm.h>
I 76
#include <limits.h>
#include <nlist.h>
E 76
E 63
E 54
I 40
#include <stdio.h>
I 75
#include <stdlib.h>
E 75
I 73
D 76
#include <limits.h>
E 76
I 76
#include <string.h>
#include <unistd.h>

E 76
E 73
I 53
D 84
#include "pathnames.h"
E 53
E 40
E 20
I 4
D 18
#define	KERNEL
D 12
#include <sys/mx.h>
E 12
#undef	KERNEL
E 18
I 18
D 23
#include <sys/descrip.h>
E 23
E 18
E 4

E 84
I 43
D 75
#define mask(x)		(x&0377)
#define	clear(x)	((int)x &~ KERNBASE)

E 43
D 53
char	*fcore	= "/dev/kmem";
I 33
char	*fmem	= "/dev/mem";
E 33
char	*fnlist	= "/vmunix";
E 53
I 53
D 57
char	*fcore	= _PATH_KMEM;
char	*fmem	= _PATH_MEM;
char	*fnlist	= _PATH_UNIX;
E 53
D 33
int	fc;
E 33
I 33
int	fc, fm;
E 57
I 57
D 71
char	*fnlist	= NULL;
char	*fcore	= NULL;
E 71
I 71
char	*nlistf	= NULL;
char	*memf	= NULL;
E 71
E 57
E 33

E 75
struct nlist nl[] = {
D 57
#define	SINODE	0
	{ "_inode" },
#define	STEXT	1
E 57
I 57
D 64
#define	STEXT	0
E 57
	{ "_text" },
I 57
D 63
#define	SCONS	1
	{ "_cons" },
E 57
#define	SPROC	2
E 63
I 63
#define	SPROC	1
E 63
	{ "_proc" },
D 42
#define	SDZ	3
	{ "_dz_tty" },
#define	SNDZ	4
	{ "_dz_cnt" },
#define	SKL	5
E 42
I 42
D 57
#define	SCONS	3
E 42
	{ "_cons" },
D 42
#define	SFIL	6
E 42
I 42
#define	SFIL	4
E 57
I 57
D 63
#define	SFIL	3
E 63
I 63
#define	SFIL	2
E 63
E 57
E 42
	{ "_file" },
D 42
#define	USRPTMA	7
E 42
I 42
D 57
#define	USRPTMA	5
E 42
	{ "_Usrptmap" },
D 42
#define	USRPT	8
E 42
I 42
#define	USRPT	6
E 42
	{ "_usrpt" },
D 27
#define	SNSWAP	9
	{ "_nswap" },
#define	SWAPMAP	10
E 27
I 27
D 42
#define	SWAPMAP	9
E 42
I 42
#define	SWAPMAP	7
E 57
I 57
D 63
#define	SWAPMAP	4
E 63
I 63
#define	SWAPMAP	3
E 64
I 64
D 75
#define	SWAPMAP	0
E 64
E 63
E 57
E 42
E 27
	{ "_swapmap" },
D 27
#define	SDH	11
E 27
I 27
D 42
#define	SDH	10
E 27
	{ "_dh11" },
D 27
#define	SNDH	12
E 27
I 27
#define	SNDH	11
E 27
	{ "_ndh11" },
I 4
D 13
#define	SGROUP	13
	{ "_groups" },
#define	SCHANS	14
	{ "_chans" },
#define	SSCHANS	15
	{ "_schans" },
I 5
#define	SNPROC	16
E 13
I 13
D 27
#define	SNPROC	13
E 27
I 27
#define	SNPROC	12
E 42
I 42
D 57
#define	SNPROC	8
E 57
I 57
D 63
#define	SNPROC	5
E 63
I 63
D 64
#define	SNPROC	4
E 63
E 57
E 42
E 27
E 13
	{ "_nproc" },
D 13
#define	SNTEXT	17
E 13
I 13
D 27
#define	SNTEXT	14
E 27
I 27
D 42
#define	SNTEXT	13
E 42
I 42
D 57
#define	SNTEXT	9
E 57
I 57
D 63
#define	SNTEXT	6
E 63
I 63
#define	SNTEXT	5
E 63
E 57
E 42
E 27
E 13
	{ "_ntext" },
D 13
#define	SNFILE	18
E 13
I 13
D 27
#define	SNFILE	15
E 27
I 27
D 42
#define	SNFILE	14
E 42
I 42
D 57
#define	SNFILE	10
E 57
I 57
D 63
#define	SNFILE	7
E 63
I 63
#define	SNFILE	6
E 63
E 57
E 42
E 27
E 13
	{ "_nfile" },
D 13
#define	SNINODE	19
E 13
I 13
D 27
#define	SNINODE	16
E 27
I 27
D 42
#define	SNINODE	15
E 42
I 42
D 57
#define	SNINODE	11
E 42
E 27
E 13
	{ "_ninode" },
D 13
#define	SNSWAPMAP 20
E 13
I 13
D 27
#define	SNSWAPMAP 17
E 27
I 27
D 42
#define	SNSWAPMAP 16
E 42
I 42
#define	SNSWAPMAP 12
E 57
I 57
D 63
#define	SNSWAPMAP 8
E 63
I 63
#define	SNSWAPMAP 7
E 64
I 64
#define	SNSWAPMAP 1
E 64
E 63
E 57
E 42
E 27
E 13
	{ "_nswapmap" },
I 12
D 13
#define	SPTY	21
E 13
I 13
D 27
#define	SPTY	18
E 27
I 27
D 42
#define	SPTY	17
E 42
I 42
D 57
#define	SPTY	13
E 57
I 57
D 63
#define	SPTY	9
E 57
E 42
E 27
E 13
	{ "_pt_tty" },
I 21
D 22
#define SDMF	19
	{ "_dmf_tty" },
#define SNDMF	20
	{ "_ndmf" },
E 22
I 22
D 27
#define	SDMMIN	19
E 27
I 27
D 42
#define	SDMMIN	18
E 42
I 42
D 57
#define	SDMMIN	14
E 57
I 57
#define	SDMMIN	10
E 63
I 63
D 64
#define	SDMMIN	8
E 64
I 64
#define	SDMMIN	2
E 64
E 63
E 57
E 42
E 27
	{ "_dmmin" },
D 27
#define	SDMMAX	20
E 27
I 27
D 42
#define	SDMMAX	19
E 42
I 42
D 57
#define	SDMMAX	15
E 57
I 57
D 63
#define	SDMMAX	11
E 63
I 63
D 64
#define	SDMMAX	9
E 64
I 64
#define	SDMMAX	3
E 64
E 63
E 57
E 42
E 27
	{ "_dmmax" },
D 27
#define	SNSWDEV	21
E 27
I 27
D 42
#define	SNSWDEV	20
E 42
I 42
D 57
#define	SNSWDEV	16
E 57
I 57
D 63
#define	SNSWDEV	12
E 63
I 63
D 64
#define	SNSWDEV	10
E 64
I 64
#define	SNSWDEV	4
E 64
E 63
E 57
E 42
E 27
	{ "_nswdev" },
E 22
E 21
E 12
E 5
E 4
D 27
	0,
E 27
I 27
D 42
#define	SSWDEVT	21
E 42
I 42
D 57
#define	SSWDEVT	17
E 57
I 57
D 63
#define	SSWDEVT	13
E 63
I 63
D 64
#define	SSWDEVT	11
E 64
I 64
#define	SSWDEVT	5
E 64
E 63
E 57
E 42
	{ "_swdevt" },
I 63
D 64
#define NLMANDATORY SSWDEVT	/* names up to here are mandatory */
#define	SCONS	12
E 64
I 64
D 69
#define	SFIL	6
	{ "_file" },
#define	SNFILE	7
	{ "_nfile" },
E 69
D 70
#ifdef NEWVM
E 70
D 69
#define NLMANDATORY SNFILE	/* names up to here are mandatory */
E 69
I 69
#define NLMANDATORY SSWDEVT	/* names up to here are mandatory */
E 75
I 75
#define VM_SWAPMAP	0
	{ "_swapmap" },	/* list of free swap areas */
#define VM_NSWAPMAP	1
	{ "_nswapmap" },/* size of the swap map */
#define VM_SWDEVT	2
	{ "_swdevt" },	/* list of swap devices and sizes */
#define VM_NSWAP	3
	{ "_nswap" },	/* size of largest swap device */
#define VM_NSWDEV	4
	{ "_nswdev" },	/* number of swap devices */
#define VM_DMMAX	5
	{ "_dmmax" },	/* maximum size of a swap block */
D 81
#define V_NUMV		6
E 81
I 81
#define	V_MOUNTLIST	6
	{ "_mountlist" },	/* address of head of mount list. */
#define V_NUMV		7
E 81
	{ "_numvnodes" },
D 81
#define V_ROOTFS	7
	{ "_rootfs" },
E 81
#define	FNL_NFILE	8
	{"_nfiles"},
#define FNL_MAXFILE	9
	{"_maxfiles"},
#define NLMANDATORY FNL_MAXFILE	/* names up to here are mandatory */
E 75
E 69
D 70
#else
#define	STEXT	8
	{ "_text" },
#define	SNTEXT	9
	{ "_ntext" },
#define	SPROC	10
	{ "_proc" },
#define	SNPROC	11
	{ "_nproc" },
#define NLMANDATORY SNPROC	/* names up to here are mandatory */
#endif

E 70
D 79
#define	SCONS	NLMANDATORY + 1
E 79
I 79
#define VM_NISWAP	NLMANDATORY + 1
	{ "_niswap" },
#define VM_NISWDEV	NLMANDATORY + 2
	{ "_niswdev" },
#define	SCONS		NLMANDATORY + 3
E 79
E 64
	{ "_cons" },
D 64
#define	SPTY	13
E 64
I 64
D 79
#define	SPTY	NLMANDATORY + 2
E 79
I 79
#define	SPTY		NLMANDATORY + 4
E 79
E 64
	{ "_pt_tty" },
E 63
I 28
D 42
#define	SDMF	22
E 42
I 42
D 57
#define	SYSMAP	18
	{ "_Sysmap" },
#define	SNPTY	19
E 57
I 57
D 64
#define	SNPTY	14
E 64
I 64
D 79
#define	SNPTY	NLMANDATORY + 3
E 79
I 79
#define	SNPTY		NLMANDATORY + 5
E 79
E 64
E 57
	{ "_npty" },
D 75
#ifdef vax
#define	SDZ	(SNPTY+1)
	{ "_dz_tty" },
#define	SNDZ	(SNPTY+2)
	{ "_dz_cnt" },
#define	SDMF	(SNPTY+3)
E 42
	{ "_dmf_tty" },
D 42
#define	SNDMF	23
E 42
I 42
#define	SNDMF	(SNPTY+4)
E 42
	{ "_ndmf" },
I 32
D 42
#define	SNPTY	24
	{ "_npty" },
I 36
#define	SDHU	25
E 42
I 42
#define	SDH	(SNPTY+5)
	{ "_dh11" },
#define	SNDH	(SNPTY+6)
	{ "_ndh11" },
#define	SDHU	(SNPTY+7)
E 42
	{ "_dhu_tty" },
D 42
#define	SNDHU	26
E 42
I 42
#define	SNDHU	(SNPTY+8)
E 42
	{ "_ndhu" },
E 36
I 35
D 37
#define	SYSMAP	25
E 37
I 37
D 42
#define	SYSMAP	27
E 37
	{ "_Sysmap" },
I 38
#define	SDMZ	28
E 42
I 42
#define	SDMZ	(SNPTY+9)
E 42
	{ "_dmz_tty" },
D 42
#define	SNDMZ	29
E 42
I 42
#define	SNDMZ	(SNPTY+10)
E 42
	{ "_ndmz" },
I 46
#define	SQD	(SNPTY+11)
	{ "_qd_tty" },
#define	SNQD	(SNPTY+12)
	{ "_nNQD" },
E 46
I 42
#endif
E 75
I 61

E 61
D 75
#ifdef tahoe
#define	SVX	(SNPTY+1)
	{ "_vx_tty" },
#define	SNVX	(SNPTY+2)
	{ "_nvx" },
I 51
D 52
#define	SMP	(SNPTY+3)
E 52
I 52
#define SMP	(SNPTY+3)
E 52
	{ "_mp_tty" },
D 52
#define	SNMP	(SNPTY+4)
E 52
I 52
#define SNMP	(SNPTY+4)
E 52
	{ "_nmp" },
E 51
#endif
I 61

E 75
#ifdef hp300
#define	SDCA	(SNPTY+1)
	{ "_dca_tty" },
#define	SNDCA	(SNPTY+2)
	{ "_ndca" },
#define	SDCM	(SNPTY+3)
	{ "_dcm_tty" },
#define	SNDCM	(SNPTY+4)
D 63
	{ "_dcm_cnt" },
E 63
I 63
	{ "_ndcm" },
E 63
#define	SDCL	(SNPTY+5)
	{ "_dcl_tty" },
#define	SNDCL	(SNPTY+6)
	{ "_ndcl" },
#define	SITE	(SNPTY+7)
	{ "_ite_tty" },
#define	SNITE	(SNPTY+8)
	{ "_nite" },
#endif
I 74

#ifdef mips
#define SDC	(SNPTY+1)
	{ "_dc_tty" },
#define SNDC	(SNPTY+2)
	{ "_dc_cnt" },
#endif

E 74
E 61
E 42
E 38
E 35
E 32
E 28
	{ "" }
E 27
};

D 57
int	inof;
E 57
I 57
D 75
int	vnof;
E 57
int	txtf;
int	prcf;
int	ttyf;
int	usrf;
I 4
D 18
int	mpxf;
int	groupf;
E 18
E 4
D 59
long	ubase;
E 59
I 59
int	upid;
E 59
int	filf;
int	swpf;
int	totflg;
char	partab[1];
struct	cdevsw	cdevsw[1];
struct	bdevsw	bdevsw[1];
int	allflg;
D 57
int	kflg;
struct	pte *Usrptma;
struct	pte *usrpt;
E 57
I 57
int	nflg;
E 57
I 40
D 48
u_long	getw();
E 48
I 48
u_long	getword();
E 48
off_t	mkphys();
E 75
I 75
int	usenumflag;
int	totalflag;
char	*nlistf	= NULL;
char	*memf	= NULL;
E 75
I 73
kvm_t	*kd;
E 73
E 40

I 86
D 91
const char *mountname[] = INITMOUNTNAMES;
E 91
struct {
	int m_flag;
	const char *m_name;
} mnt_flags[] = {
	{ MNT_RDONLY, "rdonly" },
	{ MNT_SYNCHRONOUS, "sync" },
	{ MNT_NOEXEC, "noexec" },
	{ MNT_NOSUID, "nosuid" },
	{ MNT_NODEV, "nodev" },
	{ MNT_UNION, "union" },
	{ MNT_ASYNC, "async" },
	{ MNT_EXRDONLY, "exrdonly" },
	{ MNT_EXPORTED, "exported" },
	{ MNT_DEFEXPORTED, "defexported" },
	{ MNT_EXPORTANON, "exportanon" },
	{ MNT_EXKERB, "exkerb" },
	{ MNT_LOCAL, "local" },
	{ MNT_QUOTA, "quota" },
	{ MNT_ROOTFS, "rootfs" },
D 87
	{ MNT_USER, "user" },
E 87
	{ MNT_UPDATE, "update" },
	{ MNT_DELEXPORT },
	{ MNT_UPDATE, "update" },
	{ MNT_DELEXPORT, "delexport" },
	{ MNT_RELOAD, "reload" },
	{ MNT_FORCE, "force" },
	{ MNT_MLOCK, "mlock" },
	{ MNT_WAIT, "wait" },
	{ MNT_MPBUSY, "mpbusy" },
	{ MNT_MPWANT, "mpwant" },
	{ MNT_UNMOUNT, "unmount" },
	{ MNT_WANTRDWR, "wantrdwr" },
	{ 0 }
};


E 86
I 57
D 71
char	*Program;

E 71
I 63
D 73
#define V(x)	(void *)(x)
E 73
I 73
D 75
#define V(x)	(u_long)(x)
E 75
I 75
#define	SVAR(var) __STRING(var)	/* to force expansion */
D 76
#define	KGET(idx, var) \
E 76
I 76
#define	KGET(idx, var)							\
E 76
	KGET1(idx, &var, sizeof(var), SVAR(var))
D 76
#define	KGET1(idx, p, s, msg) \
E 76
I 76
#define	KGET1(idx, p, s, msg)						\
E 76
	KGET2(nl[idx].n_value, p, s, msg)
D 76
#define	KGET2(addr, p, s, msg) \
	if (kvm_read(kd, (u_long)(addr), p, s) != s) \
		error("cannot read %s: %s", msg, kvm_geterr(kd))
#define	KGETRET(addr, p, s, msg) \
	if (kvm_read(kd, (u_long)(addr), p, s) != s) { \
		error("cannot read %s: %s", msg, kvm_geterr(kd)); \
		return (0); \
E 76
I 76
#define	KGET2(addr, p, s, msg)						\
	if (kvm_read(kd, (u_long)(addr), p, s) != s)			\
		warnx("cannot read %s: %s", msg, kvm_geterr(kd))
#define	KGETRET(addr, p, s, msg)					\
	if (kvm_read(kd, (u_long)(addr), p, s) != s) {			\
		warnx("cannot read %s: %s", msg, kvm_geterr(kd));	\
		return (0);						\
E 76
	}
E 75
E 73

I 76
void	filemode __P((void));
int	getfiles __P((char **, int *));
struct mount *
	getmnt __P((struct mount *));
struct e_vnode *
	kinfo_vnodes __P((int *));
struct e_vnode *
	loadvnodes __P((int *));
void	mount_print __P((struct mount *));
void	nfs_header __P((void));
int	nfs_print __P((struct vnode *));
void	swapmode __P((void));
void	ttymode __P((void));
void	ttyprt __P((struct tty *, int));
void	ttytype __P((struct tty *, char *, int, int));
void	ufs_header __P((void));
int	ufs_print __P((struct vnode *));
I 86
void	union_header __P((void));
int	union_print __P((struct vnode *));
E 86
void	usage __P((void));
void	vnode_header __P((void));
void	vnode_print __P((struct vnode *, struct vnode *));
void	vnodemode __P((void));

int
E 76
E 63
E 57
main(argc, argv)
D 50
char **argv;
E 50
I 50
	int argc;
D 71
	char **argv;
E 71
I 71
	char *argv[];
E 71
E 50
{
D 50
	register char *argp;
I 18
	int allflags;
E 50
I 50
	extern char *optarg;
	extern int optind;
D 63
	int ch;
E 63
I 63
D 76
	int ch, ret;
I 75
	int swapflag = 0, vnodeflag = 0, ttyflag = 0, fileflag = 0;
E 76
I 76
	int ch, i, quit, ret;
	int fileflag, swapflag, ttyflag, vnodeflag;
E 76
E 75
I 73
	char buf[_POSIX2_LINE_MAX];
E 73
E 63
E 50
E 18

I 76
	fileflag = swapflag = ttyflag = vnodeflag = 0;
E 76
D 50
	argc--, argv++;
	while (argc > 0 && **argv == '-') {
		argp = *argv++;
		argp++;
		argc--;
		while (*argp++)
		switch (argp[-1]) {

E 50
I 50
D 57
	while ((ch = getopt(argc, argv, "Tafikptu:sx")) != EOF)
E 57
I 57
D 71
        Program = argv[0];
E 71
D 60
	while ((ch = getopt(argc, argv, "Tafvikptu:sxn")) != EOF)
E 60
I 60
D 75
	while ((ch = getopt(argc, argv, "TafvikptU:sxnu")) != EOF)
E 75
I 75
	while ((ch = getopt(argc, argv, "TM:N:finstv")) != EOF)
E 75
E 60
E 57
D 61
		switch((char)ch) {
E 61
I 61
		switch (ch) {
I 76
		case 'f':
			fileflag = 1;
			break;
E 76
E 61
E 50
D 75
		case 'T':
			totflg++;
E 75
I 75
		case 'M':
			memf = optarg;
E 75
			break;
D 50

E 50
D 75
		case 'a':
			allflg++;
I 50
			/*FALLTHROUGH*/
		case 'p':
			prcf++;
E 75
I 75
		case 'N':
			nlistf = optarg;
E 75
E 50
			break;
I 75
D 76
		case 'T':
			totalflag++;
E 76
I 76
		case 'n':
			usenumflag = 1;
E 76
			break;
E 75
D 50

E 50
I 50
D 76
		case 'f':
D 75
			filf++;
E 75
I 75
			fileflag++;
E 76
I 76
		case 's':
			swapflag = 1;
E 76
E 75
			break;
I 57
D 76
		case 'v':
E 57
E 50
		case 'i':
D 57
			inof++;
E 57
I 57
D 75
			vnof++;
E 75
I 75
			vnodeflag++;
E 76
I 76
		case 'T':
			totalflag = 1;
E 76
E 75
E 57
			break;
D 50

		case 'k':
E 50
I 50
D 57
		case 'k':			/* undocumented */
E 50
			kflg++;
D 33
			fcore = "/vmcore";
E 33
I 33
D 53
			fcore = fmem = "/vmcore";
E 53
I 53
			fcore = fmem = _PATH_CORE;
E 53
E 33
			break;
E 57
D 50

		case 'x':
			txtf++;
			break;

		case 'p':
			prcf++;
			break;

E 50
		case 't':
D 75
			ttyf++;
E 75
I 75
D 76
			ttyflag++;
E 76
I 76
			ttyflag = 1;
E 76
E 75
			break;
D 50

E 50
D 60
		case 'u':
E 60
I 60
D 75
		case 'U':
E 60
D 50
			if (argc == 0)
				break;
			argc--;
E 50
			usrf++;
D 50
			sscanf( *argv++, "%x", &ubase);
E 50
I 50
D 59
			sscanf(optarg, "%x", &ubase);
E 59
I 59
			sscanf(optarg, "%d", &upid);
E 59
E 50
			break;
E 75
D 50

		case 'f':
			filf++;
			break;
E 50
D 76
		case 's':
D 75
			swpf++;
E 75
I 75
			swapflag++;
E 76
I 76
		case 'v':
		case 'i':		/* Backward compatibility. */
			vnodeflag = 1;
E 76
E 75
			break;
I 50
D 75
		case 'x':
			txtf++;
			break;
E 75
I 57
D 76
		case 'n':
D 75
			nflg++;
E 75
I 75
			usenumflag++;
E 75
			break;
E 76
I 60
D 75
		case 'u':
			fprintf(stderr, "pstat: use [ -U pid ] for -u\n");
			exit(1);
E 60
E 57
		case '?':
E 75
E 50
I 4
D 18
		case 'm':
			mpxf++;
			break;
		case 'g':
			groupf++;
			break;
E 18
I 18
		default:
D 50
			usage();
E 50
I 50
D 59
			printf("usage: pstat -[Tafiptsx] [-u [ubase]] [system] [core]\n");
E 59
I 59
D 60
			printf("usage: pstat -[Tafiptsx] [-u [pid]] [system] [core]\n");
E 60
I 60
D 73
			fprintf(stderr, "usage: pstat -[Tafiptsx] [-U [pid]] [system] [core]\n");
E 60
E 59
E 50
			exit(1);
E 73
I 73
			usage();
E 73
E 18
E 4
		}
D 50
	}
E 50
I 50
	argc -= optind;
	argv += optind;

E 50
D 18
	if (argc>0)
		fcore = argv[0];
E 18
I 18
D 40
	if (argc>1)
E 40
I 40
D 57
	if (argc>1) {
E 40
D 33
		fcore = argv[1];
E 33
I 33
		fcore = fmem = argv[1];
I 40
		kflg++;
	}
E 40
E 33
E 18
D 50
	if ((fc = open(fcore, 0)) < 0) {
		printf("Can't find %s\n", fcore);
E 50
I 50
	if ((fc = open(fcore, O_RDONLY, 0)) < 0) {
		perror(fcore);
E 57
I 57
D 75
	if (argc > 1)
D 71
		fcore = argv[1];
E 71
I 71
		memf = argv[1];
E 71
	if (argc > 0)
D 71
		fnlist = argv[0];
	if (kvm_openfiles(fnlist, fcore, NULL) == -1) {
E 71
I 71
		nlistf = argv[0];

E 75
	/*
	 * Discard setgid privileges if not the running kernel so that bad
	 * guys can't print interesting stuff from kernel memory.
	 */
	if (nlistf != NULL || memf != NULL)
D 76
		setgid(getgid());
E 76
I 76
		(void)setgid(getgid());
E 76

D 73
	if (kvm_openfiles(nlistf, memf, NULL) == -1) {
E 71
D 63
		syserror("kvm_openfiles: %s", kvm_geterr());
E 63
I 63
		error("kvm_openfiles: %s", kvm_geterr());
E 73
I 73
D 76
	if ((kd = kvm_openfiles(nlistf, memf, NULL, O_RDONLY, buf)) == 0) {
		error("kvm_openfiles: %s", buf);
E 73
E 63
E 57
E 50
		exit(1);
	}
E 76
I 76
	if ((kd = kvm_openfiles(nlistf, memf, NULL, O_RDONLY, buf)) == 0)
		errx(1, "kvm_openfiles: %s", buf);
E 76
I 33
D 50
	if ((fm = open(fmem, 0)) < 0) {
		printf("Can't find %s\n", fmem);
E 50
I 50
D 57
	if ((fm = open(fmem, O_RDONLY, 0)) < 0) {
		perror(fmem);
E 57
I 57
D 63
	if (kvm_nlist(nl) != 0) {
		syserror("kvm_nlist: %s", kvm_geterr());
I 61
		/*
E 61
E 57
E 50
		exit(1);
I 61
		*/
E 63
I 63
D 73
	if ((ret = kvm_nlist(nl)) != 0) {
E 73
I 73
	if ((ret = kvm_nlist(kd, nl)) != 0) {
E 73
D 76
		int i, quit = 0;

		if (ret == -1) {
D 73
			error("kvm_nlist: %s", kvm_geterr());
E 73
I 73
			error("kvm_nlist: %s", kvm_geterr(kd));
E 73
			exit(1);
		}
		for (i = 0; i <= NLMANDATORY; i++) {
E 76
I 76
		if (ret == -1)
			errx(1, "kvm_nlist: %s", kvm_geterr(kd));
		for (i = quit = 0; i <= NLMANDATORY; i++)
E 76
			if (!nl[i].n_value) {
				quit = 1;
D 76
				error("undefined symbol: %s\n",
					nl[i].n_name);
E 76
I 76
				warnx("undefined symbol: %s\n", nl[i].n_name);
E 76
			}
D 76
		}
E 76
		if (quit)
			exit(1);
E 63
E 61
	}
E 33
D 18
	if (argc>1)
		fnlist = argv[1];
E 18
I 18
D 57
	if (argc>0)
		fnlist = argv[0];
E 18
	nlist(fnlist, nl);
D 7
	if (kflg) {
		register struct nlist *nlp;
		for (nlp=nl; nlp < &nl[sizeof (nl)/sizeof(nl[0])]; nlp++)
			nlp->n_value = clear(nlp->n_value);
	}
E 7
D 50
	usrpt = (struct pte *)nl[USRPT].n_value;
	Usrptma = (struct pte *)nl[USRPTMA].n_value;
E 50
	if (nl[0].n_type == 0) {
D 50
		printf("no namelist\n");
E 50
I 50
		printf("pstat: no namelist.\n");
E 57
I 57
D 73
	if (!(filf | totflg | vnof | prcf | txtf | ttyf | usrf | swpf)) {
D 60
		printf("pstat: one or more of -[aivxptfsu] is required\n");
E 60
I 60
		printf("pstat: one or more of -[aivxptfsU] is required\n");
E 60
E 57
E 50
		exit(1);
	}
E 73
I 73
D 75
	if (!(filf | totflg | vnof | prcf | txtf | ttyf | usrf | swpf))
E 75
I 75
	if (!(fileflag | vnodeflag | ttyflag | swapflag | totalflag))
E 75
		usage();
E 73
I 18
D 50
	allflags = filf | totflg | inof | prcf | txtf | ttyf | usrf | swpf;
	if (allflags == 0) {
E 50
I 50
D 57
	usrpt = (struct pte *)nl[USRPT].n_value;
	Usrptma = (struct pte *)nl[USRPTMA].n_value;
	if (!(filf | totflg | inof | prcf | txtf | ttyf | usrf | swpf)) {
E 50
		printf("pstat: one or more of -[aixptfsu] is required\n");
		exit(1);
	}
E 57
E 18
D 75
	if (filf||totflg)
E 75
I 75
	if (fileflag || totalflag)
E 75
D 5
		dofil();
E 5
I 5
D 76
		dofile();
E 76
I 76
		filemode();
E 76
E 5
D 57
	if (inof||totflg)
		doinode();
E 57
I 57
D 75
	if (vnof||totflg)
E 75
I 75
	if (vnodeflag || totalflag)
E 75
D 76
		dovnode();
E 76
I 76
		vnodemode();
E 76
E 57
D 75
	if (prcf||totflg)
		doproc();
	if (txtf||totflg)
		dotext();
	if (ttyf)
E 75
I 75
	if (ttyflag)
E 75
D 76
		dotty();
E 76
I 76
		ttymode();
E 76
D 75
	if (usrf)
		dousr();
	if (swpf||totflg)
E 75
I 75
	if (swapflag || totalflag)
E 75
D 76
		doswap();
E 76
I 76
		swapmode();
	exit (0);
E 76
I 4
D 5
	if (mpxf||totflg)
E 5
I 5
D 12
	if (mpxf)
E 5
		dompx();
D 5
	if (groupf||totflg)
E 5
I 5
	if (groupf)
E 5
		dogroup();
E 12
E 4
D 50
}

I 18
usage()
{

	printf("usage: pstat -[aixptfs] [-u [ubase]] [system] [core]\n");
E 50
}

I 73
D 76
usage()
{

	fprintf(stderr,
D 75
	    "usage: pstat -[Tafiptsx] [-U [pid]] [system] [core]\n");
E 75
I 75
	    "usage: pstat -Tfnstv [system] [core]\n");
E 75
	exit(1);
}

E 76
E 73
I 58
struct e_vnode {
	struct vnode *avnode;
	struct vnode vnode;
};

E 58
E 18
D 57
doinode()
E 57
I 57
D 76
dovnode()
E 76
I 76
void
vnodemode()
E 76
E 57
{
I 57
D 58
	register struct vnode *vp, *vnodebase, *evnode;
E 58
I 58
D 86
	register struct e_vnode *e_vnodebase, *endvnode, *evp;
	register struct vnode *vp;
E 58
D 76
	register struct mount *maddr = NULL, *mp;
E 76
I 76
	register struct mount *maddr, *mp;
E 86
I 86
	struct e_vnode *e_vnodebase, *endvnode, *evp;
	struct vnode *vp;
	struct mount *maddr, *mp;
E 86
E 76
E 57
D 62
	register struct inode *ip;
E 62
I 54
D 57
	register struct vnode *vp;
E 54
D 5
	struct inode xinode[NINODE];
	register int nin, loc;
E 5
I 5
	struct inode *xinode, *ainode;
	register int nin;
	int ninode;
E 57
I 57
	int numvnodes;
D 58
	struct vnode *loadvnodes();
E 58
I 58
D 76
	struct e_vnode *loadvnodes();
E 58
	struct mount *getmnt();
E 76
E 57
E 5

D 57
	nin = 0;
D 5
	lseek(fc, (long)nl[SINODE].n_value, 0);
	read(fc, xinode, sizeof(xinode));
	for (ip = xinode; ip < &xinode[NINODE]; ip++)
E 5
I 5
D 48
	ninode = getw(nl[SNINODE].n_value);
E 48
I 48
	ninode = getword(nl[SNINODE].n_value);
E 48
	xinode = (struct inode *)calloc(ninode, sizeof (struct inode));
D 35
	lseek(fc, (int)(ainode = (struct inode *)getw(nl[SINODE].n_value)), 0);
E 35
I 35
D 48
	ainode = (struct inode *)getw(nl[SINODE].n_value);
E 48
I 48
	ainode = (struct inode *)getword(nl[SINODE].n_value);
E 48
D 40
	lseek(fc, mkphys((int)ainode), 0);
E 40
I 40
	if (ninode < 0 || ninode > 10000) {
		fprintf(stderr, "number of inodes is preposterous (%d)\n",
			ninode);
		return;
	}
	if (xinode == NULL) {
		fprintf(stderr, "can't allocate memory for inode table\n");
		return;
	}
	lseek(fc, mkphys((off_t)ainode), 0);
E 40
E 35
	read(fc, xinode, ninode * sizeof(struct inode));
D 54
	for (ip = xinode; ip < &xinode[ninode]; ip++)
E 5
		if (ip->i_count)
E 54
I 54
	for (ip = xinode; ip < &xinode[ninode]; ip++) {
		vp = &ip->i_vnode;
		if (vp->v_count)
E 54
			nin++;
I 54
	}
E 57
I 57
D 58
	vnodebase = loadvnodes(&numvnodes);
E 58
I 58
	e_vnodebase = loadvnodes(&numvnodes);
E 58
E 57
E 54
D 75
	if (totflg) {
E 75
I 75
	if (totalflag) {
E 75
D 5
		printf("%3d/%3d inodes\n", nin, NINODE);
E 5
I 5
D 57
		printf("%3d/%3d inodes\n", nin, ninode);
E 57
I 57
D 76
		printf("%7d vnodes\n", numvnodes);
E 76
I 76
		(void)printf("%7d vnodes\n", numvnodes);
E 76
E 57
E 5
		return;
	}
D 5
	printf("%d/%d active xinodes\n", nin, NINODE);
E 5
I 5
D 57
	printf("%d/%d active inodes\n", nin, ninode);
E 57
I 57
D 58
	evnode = vnodebase + numvnodes;
E 58
I 58
	endvnode = e_vnodebase + numvnodes;
E 58
D 76
	printf("%d active vnodes\n", numvnodes);
E 76
I 76
	(void)printf("%d active vnodes\n", numvnodes);
E 76


D 58
#define ST	mp->m_stat
	for (vp = vnodebase; vp < evnode; vp++) {
E 58
I 58
#define ST	mp->mnt_stat
I 76
	maddr = NULL;
E 76
	for (evp = e_vnodebase; evp < endvnode; evp++) {
		vp = &evp->vnode;
E 58
		if (vp->v_mount != maddr) {
			/*
			 * New filesystem
			 */
			if ((mp = getmnt(vp->v_mount)) == NULL)
				continue;
			maddr = vp->v_mount;
			mount_print(mp);
			vnode_header();
D 86
			switch(ST.f_type) {
E 86
I 86
D 91
			switch (ST.f_type) {
E 86
			case MOUNT_UFS:
			case MOUNT_MFS:
E 91
I 91
			if (!strcmp(ST.f_fstypename, "ufs") ||
			    !strcmp(ST.f_fstypename, "mfs"))
E 91
				ufs_header();
D 91
				break;
			case MOUNT_NFS:
E 91
I 91
			else if (!strcmp(ST.f_fstypename, "nfs"))
E 91
				nfs_header();
D 91
				break;
I 86
			case MOUNT_UNION:
E 91
I 91
			else if (!strcmp(ST.f_fstypename, "union"))
E 91
				union_header();
D 91
				break;
E 86
			case MOUNT_NONE:
D 82
			case MOUNT_PC:
E 82
I 82
			case MOUNT_MSDOS:
E 82
			default:
				break;
			}
E 91
D 76
			printf("\n");
E 76
I 76
			(void)printf("\n");
E 76
		}
D 58
		vnode_print(vp);
E 58
I 58
		vnode_print(evp->avnode, vp);
E 58
D 86
		switch(ST.f_type) {
E 86
I 86
D 91
		switch (ST.f_type) {
E 86
		case MOUNT_UFS:
		case MOUNT_MFS:
E 91
I 91
		if (!strcmp(ST.f_fstypename, "ufs") ||
		    !strcmp(ST.f_fstypename, "mfs"))
E 91
			ufs_print(vp);
D 91
			break;
		case MOUNT_NFS:
E 91
I 91
		else if (!strcmp(ST.f_fstypename, "nfs"))
E 91
			nfs_print(vp);
D 91
			break;
I 86
		case MOUNT_UNION:
E 91
I 91
		else if (!strcmp(ST.f_fstypename, "union"))
E 91
			union_print(vp);
D 91
			break;
E 86
		case MOUNT_NONE:
D 82
		case MOUNT_PC:
E 82
I 82
		case MOUNT_MSDOS:
E 82
		default:
			break;
		}
E 91
D 76
		printf("\n");
E 76
I 76
		(void)printf("\n");
E 76
D 58
#ifdef notdef
E 57
E 5
D 18
	printf("   LOC    FLAGS  CNT DEVICE   INO  MODE  NLK UID   SIZE/DEV\n");
E 18
I 18
printf("   LOC      FLAGS    CNT DEVICE  RDC WRC  INO  MODE  NLK UID   SIZE/DEV\n");
E 18
D 5
	loc = nl[SINODE].n_value;
	for (ip = xinode; ip < &xinode[NINODE]; ip++, loc += sizeof(xinode[0])) {
E 5
I 5
D 57
	for (ip = xinode; ip < &xinode[ninode]; ip++) {
E 5
D 54
		if (ip->i_count == 0)
E 54
I 54
		vp = &ip->i_vnode;
		if (vp->v_count == 0)
E 54
			continue;
D 5
		printf("%8.1x ", loc);
E 5
I 5
		printf("%8.1x ", ainode + (ip - xinode));
E 57
I 57
		ip = VTOI(vp);
		/* HOW ???  - use pointer back to vnode in data area
			printf("%8.1x ", ainode + (ip - xinode)); 
		*/
E 57
E 5
D 19
		putf(ip->i_flag&ILOCK, 'L');
E 19
I 19
		putf(ip->i_flag&ILOCKED, 'L');
E 19
		putf(ip->i_flag&IUPD, 'U');
		putf(ip->i_flag&IACC, 'A');
D 54
		putf(ip->i_flag&IMOUNT, 'M');
E 54
		putf(ip->i_flag&IWANT, 'W');
D 54
		putf(ip->i_flag&ITEXT, 'T');
E 54
I 18
		putf(ip->i_flag&ICHG, 'C');
		putf(ip->i_flag&ISHLOCK, 'S');
		putf(ip->i_flag&IEXLOCK, 'E');
		putf(ip->i_flag&ILWAIT, 'Z');
E 18
D 54
		printf("%4d", ip->i_count&0377);
E 54
I 54
		putf(ip->i_flag&IMOD, 'M');
		putf(ip->i_flag&IRENAME, 'R');
D 57
		printf("%4d", vp->v_count&0377);
E 57
I 57
		printf("%4d", vp->v_usecount&0377);
E 57
E 54
		printf("%4d,%3d", major(ip->i_dev), minor(ip->i_dev));
I 18
D 19
		printf("%4d", ip->i_rdlockc&0377);
		printf("%4d", ip->i_wrlockc&0377);
E 19
I 19
D 54
		printf("%4d", ip->i_shlockc&0377);
		printf("%4d", ip->i_exlockc&0377);
E 54
I 54
		printf("%4d", vp->v_shlockc&0377);
		printf("%4d", vp->v_exlockc&0377);
E 54
E 19
E 18
		printf("%6d", ip->i_number);
		printf("%6x", ip->i_mode & 0xffff);
		printf("%4d", ip->i_nlink);
		printf("%4d", ip->i_uid);
		if ((ip->i_mode&IFMT)==IFBLK || (ip->i_mode&IFMT)==IFCHR)
D 14
			printf("%6d,%3d", major(ip->i_un.i_rdev), minor(ip->i_un.i_rdev));
E 14
I 14
			printf("%6d,%3d", major(ip->i_rdev), minor(ip->i_rdev));
E 14
		else
			printf("%10ld", ip->i_size);
		printf("\n");
I 57
#endif
E 58
E 57
	}
I 5
D 57
	free(xinode);
E 57
I 57
D 58
	free(vnodebase);
E 58
I 58
	free(e_vnodebase);
E 58
E 57
E 5
}

I 76
void
E 76
I 57
vnode_header()
{
D 58
	printf("TYP VFLAG  USE  REF");
E 58
I 58
D 61
	printf("ADDR     TYP VFLAG  USE  REF");
E 61
I 61
D 76
	printf("ADDR     TYP VFLAG  USE HOLD");
E 76
I 76
	(void)printf("ADDR     TYP VFLAG  USE HOLD");
E 76
E 61
E 58
}

I 76
void
E 76
D 58
vnode_print(vp)
E 58
I 58
vnode_print(avnode, vp)
	struct vnode *avnode;
E 58
	struct vnode *vp;
{
	char *type, flags[16]; 
	char *fp = flags;
D 76
	register flag;
E 76
I 76
D 86
	register int flag;
E 86
I 86
	int flag;
E 86
E 76

	/*
	 * set type
	 */
D 86
	switch(vp->v_type) {
E 86
I 86
	switch (vp->v_type) {
E 86
	case VNON:
		type = "non"; break;
	case VREG:
		type = "reg"; break;
	case VDIR:
		type = "dir"; break;
	case VBLK:
		type = "blk"; break;
	case VCHR:
		type = "chr"; break;
	case VLNK:
		type = "lnk"; break;
	case VSOCK:
		type = "soc"; break;
	case VFIFO:
		type = "fif"; break;
	case VBAD:
		type = "bad"; break;
	default: 
		type = "unk"; break;
	}
	/*
	 * gather flags
	 */
	flag = vp->v_flag;
	if (flag & VROOT)
		*fp++ = 'R';
	if (flag & VTEXT)
		*fp++ = 'T';
I 63
	if (flag & VSYSTEM)
		*fp++ = 'S';
E 63
	if (flag & VXLOCK)
		*fp++ = 'L';
	if (flag & VXWANT)
		*fp++ = 'W';
D 63
	if (flag & VEXLOCK)
		*fp++ = 'E';
	if (flag & VSHLOCK)
		*fp++ = 'S';
	if (flag & VLWAIT)
		*fp++ = 'T';
	if (flag & VALIASED)
		*fp++ = 'A';
E 63
	if (flag & VBWAIT)
		*fp++ = 'B';
I 63
	if (flag & VALIASED)
		*fp++ = 'A';
E 63
	if (flag == 0)
		*fp++ = '-';
	*fp = '\0';
D 76
	/*
	 * print it
	 */
D 58
	printf("%s %5s %4d %4d",
		type, flags, vp->v_usecount, vp->v_holdcnt);
E 58
I 58
	printf("%8x %s %5s %4d %4d",
		avnode, type, flags, vp->v_usecount, vp->v_holdcnt);
E 76
I 76
	(void)printf("%8x %s %5s %4d %4d",
	    avnode, type, flags, vp->v_usecount, vp->v_holdcnt);
E 76
E 58
}

I 76
void
E 76
ufs_header() 
{
D 58
	printf("     LOC FILEID IFLAG RDEV|SZ");
E 58
I 58
D 76
	printf(" FILEID IFLAG RDEV|SZ");
E 76
I 76
	(void)printf(" FILEID IFLAG RDEV|SZ");
E 76
E 58
}

I 76
int
E 76
ufs_print(vp) 
	struct vnode *vp;
{
I 76
D 86
	register int flag;
E 86
I 86
	int flag;
E 86
E 76
D 73
	struct inode *ip = VTOI(vp);
E 73
I 73
	struct inode inode, *ip = &inode;
E 73
	char flagbuf[16], *flags = flagbuf;
D 76
	register flag;
E 76
	char *name;
	mode_t type;
D 76
	extern char *devname();
E 76

I 73
D 75
	if (kvm_read(kd, V(VTOI(vp)), &inode, sizeof(struct inode)) != 
	    sizeof(struct inode)) {
		error("can't read inode for %x", vp);
		return;
	}
E 75
I 75
D 76

E 76
	KGETRET(VTOI(vp), &inode, sizeof(struct inode), "vnode's inode");
E 75
E 73
	flag = ip->i_flag;
D 78
	if (flag & ILOCKED)
E 78
I 78
	if (flag & IN_LOCKED)
E 78
		*flags++ = 'L';
D 78
	if (flag & IWANT)
E 78
I 78
	if (flag & IN_WANTED)
E 78
		*flags++ = 'W';
D 78
	if (flag & IRENAME)
E 78
I 78
	if (flag & IN_RENAME)
E 78
		*flags++ = 'R';
D 78
	if (flag & IUPD)
E 78
I 78
	if (flag & IN_UPDATE)
E 78
		*flags++ = 'U';
D 78
	if (flag & IACC)
E 78
I 78
	if (flag & IN_ACCESS)
E 78
		*flags++ = 'A';
D 78
	if (flag & ICHG)
E 78
I 78
	if (flag & IN_CHANGE)
E 78
		*flags++ = 'C';
D 78
	if (flag & IMOD)
E 78
I 78
	if (flag & IN_MODIFIED)
E 78
		*flags++ = 'M';
D 78
	if (flag & ISHLOCK)
E 78
I 78
	if (flag & IN_SHLOCK)
E 78
		*flags++ = 'S';
D 78
	if (flag & IEXLOCK)
E 78
I 78
	if (flag & IN_EXLOCK)
E 78
		*flags++ = 'E';
D 78
	if (flag & ILWAIT)
E 78
I 78
	if (flag & IN_LWAIT)
E 78
		*flags++ = 'Z';
	if (flag == 0)
		*flags++ = '-';
	*flags = '\0';

D 58
	printf(" %7x %6d %5s",
		clear(ip->i_vnode), ip->i_number, flagbuf);
E 58
I 58
D 76
	printf(" %6d %5s", ip->i_number, flagbuf);
E 76
I 76
	(void)printf(" %6d %5s", ip->i_number, flagbuf);
E 76
E 58
	type = ip->i_mode & S_IFMT;
D 76
	if (type == S_IFCHR || type == S_IFBLK)
E 76
I 76
	if (S_ISCHR(ip->i_mode) || S_ISBLK(ip->i_mode))
E 76
D 66
		if (nflg || ((name = devname(ip->i_rdev, type)) == NULL))
E 66
I 66
D 67
		if (nflg || ((name = devname(ip->i_rdev, S_IFBLK)) == NULL))
E 67
I 67
D 75
		if (nflg || ((name = devname(ip->i_rdev, type)) == NULL))
E 75
I 75
		if (usenumflag || ((name = devname(ip->i_rdev, type)) == NULL))
E 75
E 67
E 66
D 76
			printf("   %2d,%-2d", 
				major(ip->i_rdev), minor(ip->i_rdev));
E 76
I 76
			(void)printf("   %2d,%-2d", 
			    major(ip->i_rdev), minor(ip->i_rdev));
E 76
		else
D 76
			printf(" %7s", name);
E 76
I 76
			(void)printf(" %7s", name);
E 76
	else
D 73
		printf(" %7d", ip->i_size);
E 73
I 73
D 76
		printf(" %7qd", ip->i_size);
E 76
I 76
		(void)printf(" %7qd", ip->i_size);
	return (0);
E 76
E 73
}

I 76
void
E 76
nfs_header() 
{
D 58
	printf("     LOC FILEID NFLAG RDEV|SZ");
E 58
I 58
D 76
	printf(" FILEID NFLAG RDEV|SZ");
E 76
I 76
	(void)printf(" FILEID NFLAG RDEV|SZ");
E 76
E 58
}

I 76
int
E 76
nfs_print(vp) 
	struct vnode *vp;
{
D 58
	struct nfsnode *np = VTOI(vp);
E 58
I 58
D 73
	struct nfsnode *np = VTONFS(vp);
E 73
I 73
	struct nfsnode nfsnode, *np = &nfsnode;
E 73
E 58
	char flagbuf[16], *flags = flagbuf;
D 76
	register flag;
E 76
I 76
D 86
	register int flag;
E 86
I 86
	int flag;
E 86
E 76
	char *name;
	mode_t type;
D 75
	extern char *devname();
E 75

I 73
D 75
	if (kvm_read(kd, V(VTONFS(vp)), &nfsnode, sizeof(struct nfsnode)) != 
	    sizeof(struct nfsnode)) {
		error("can't read nfsnode for %x", vp);
		return;
	}
E 75
I 75
	KGETRET(VTONFS(vp), &nfsnode, sizeof(nfsnode), "vnode's nfsnode");
E 75
E 73
	flag = np->n_flag;
D 73
	if (flag & NLOCKED)
		*flags++ = 'L';
	if (flag & NWANT)
E 73
I 73
	if (flag & NFLUSHWANT)
E 73
		*flags++ = 'W';
I 73
	if (flag & NFLUSHINPROG)
		*flags++ = 'P';
E 73
	if (flag & NMODIFIED)
		*flags++ = 'M';
D 59
	if (flag & NBUFFERED)
		*flags++ = 'B';
	if (flag & NPAGEDON)
		*flags++ = 'P';
E 59
	if (flag & NWRITEERR)
		*flags++ = 'E';
I 73
	if (flag & NQNFSNONCACHE)
		*flags++ = 'X';
	if (flag & NQNFSWRITE)
		*flags++ = 'O';
	if (flag & NQNFSEVICTED)
		*flags++ = 'G';
E 73
	if (flag == 0)
		*flags++ = '-';
	*flags = '\0';

#define VT	np->n_vattr
D 58
	printf(" %7x %6d %5s",
		clear(np->n_vnode), VT.va_fileid, flagbuf);
E 58
I 58
D 76
	printf(" %6d %5s", VT.va_fileid, flagbuf);
E 76
I 76
	(void)printf(" %6d %5s", VT.va_fileid, flagbuf);
E 76
E 58
	type = VT.va_mode & S_IFMT;
D 76
	if (type == S_IFCHR || type == S_IFBLK)
E 76
I 76
	if (S_ISCHR(VT.va_mode) || S_ISBLK(VT.va_mode))
E 76
D 66
		if (nflg || ((name = devname(VT.va_rdev, type)) == NULL))
E 66
I 66
D 67
		if (nflg || ((name = devname(VT.va_rdev, S_IFBLK)) == NULL))
E 67
I 67
D 75
		if (nflg || ((name = devname(VT.va_rdev, type)) == NULL))
E 75
I 75
		if (usenumflag || ((name = devname(VT.va_rdev, type)) == NULL))
E 75
E 67
E 66
D 76
			printf("   %2d,%-2d", 
				major(VT.va_rdev), minor(VT.va_rdev));
E 76
I 76
			(void)printf("   %2d,%-2d", 
			    major(VT.va_rdev), minor(VT.va_rdev));
E 76
		else
D 76
			printf(" %7s", name);
E 76
I 76
			(void)printf(" %7s", name);
E 76
	else
D 73
		printf(" %7d", np->n_size);
E 73
I 73
D 76
		printf(" %7qd", np->n_size);
E 76
I 76
		(void)printf(" %7qd", np->n_size);
	return (0);
E 76
E 73
}
I 86

void
union_header() 
{
	(void)printf("    UPPER    LOWER");
}

int
union_print(vp) 
	struct vnode *vp;
{
	struct union_node unode, *up = &unode;

	KGETRET(VTOUNION(vp), &unode, sizeof(unode), "vnode's unode");

	(void)printf(" %8x %8x", up->un_uppervp, up->un_lowervp);
	return (0);
}
E 86
	
/*
 * Given a pointer to a mount structure in kernel space,
 * read it in and return a usable pointer to it.
 */
struct mount *
getmnt(maddr)
	struct mount *maddr;
{
	static struct mtab {
		struct mtab *next;
		struct mount *maddr;
		struct mount mount;
	} *mhead = NULL;
D 86
	register struct mtab *mt;
E 86
I 86
	struct mtab *mt;
E 86

	for (mt = mhead; mt != NULL; mt = mt->next)
		if (maddr == mt->maddr)
			return (&mt->mount);
D 76
	if ((mt = (struct mtab *)malloc(sizeof (struct mtab))) == NULL) {
		error("out of memory");
		exit(1);
	}
E 76
I 76
	if ((mt = malloc(sizeof(struct mtab))) == NULL)
		err(1, NULL);
E 76
D 63
	if (kvm_read((off_t)maddr, &mt->mount, sizeof(struct mount)) != 
E 63
I 63
D 73
	if (kvm_read(V(maddr), &mt->mount, sizeof(struct mount)) != 
E 73
I 73
D 75
	if (kvm_read(kd, V(maddr), &mt->mount, sizeof(struct mount)) != 
E 73
E 63
	    sizeof(struct mount)) {
		error("can't read mount table at %x", maddr);
		return (NULL);
	}
E 75
I 75
	KGETRET(maddr, &mt->mount, sizeof(struct mount), "mount table");
E 75
	mt->maddr = maddr;
	mt->next = mhead;
	mhead = mt;
	return (&mt->mount);
}

I 76
void
E 76
mount_print(mp)
	struct mount *mp;
{
D 76
	char *type = "unknown";
	register flags;
E 76
I 76
D 86
	register int flags;
	char *type;
E 86
I 86
	int flags;
	const char *type;
E 86
E 76

D 58
#define ST	mp->m_stat
E 58
I 58
#define ST	mp->mnt_stat
E 58
D 76
	printf("*** MOUNT ");
E 76
I 76
D 91
	(void)printf("*** MOUNT ");
E 76
D 86
	switch (ST.f_type) {
	case MOUNT_NONE:
		type = "none";
		break;
	case MOUNT_UFS:
		type = "ufs";
		break;
	case MOUNT_NFS:
		type = "nfs";
		break;
	case MOUNT_MFS:
		type = "mfs";
		break;
D 83
	case MOUNT_PC:
E 83
I 83
	case MOUNT_MSDOS:
E 83
		type = "pc";
		break;
I 76
	default:
E 86
I 86
	if (ST.f_type >= sizeof(mountname)/sizeof(mountname[0]))
E 86
		type = "unknown";
D 86
		break;
E 76
	}
E 86
I 86
	else
		type = mountname[ST.f_type];
E 86
D 76
	printf("%s %s on %s", type, ST.f_mntfromname, ST.f_mntonname);
E 76
I 76
	(void)printf("%s %s on %s", type, ST.f_mntfromname, ST.f_mntonname);
E 91
I 91
	(void)printf("*** MOUNT %s %s on %s", ST.f_fstypename,
	    ST.f_mntfromname, ST.f_mntonname);
E 91
E 76
D 58
	if (flags = mp->m_flag) {
E 58
I 58
	if (flags = mp->mnt_flag) {
E 58
D 86
		char *comma = "(";
E 86
I 86
		int i;
		const char *sep = " (";
E 86

D 86
		putchar(' ');
D 58
		if (flags & M_RDONLY) {
E 58
I 58
		/* user visable flags */
		if (flags & MNT_RDONLY) {
E 58
D 76
			printf("%srdonly", comma);
E 76
I 76
			(void)printf("%srdonly", comma);
E 76
I 58
			flags &= ~MNT_RDONLY;
E 58
			comma = ",";
E 86
I 86
		for (i = 0; mnt_flags[i].m_flag; i++) {
			if (flags & mnt_flags[i].m_flag) {
				(void)printf("%s%s", sep, mnt_flags[i].m_name);
				flags &= ~mnt_flags[i].m_flag;
				sep = ",";
			}
E 86
		}
D 58
		if (flags & M_SYNCHRONOUS) {
E 58
I 58
D 86
		if (flags & MNT_SYNCHRONOUS) {
E 58
D 76
			printf("%ssynchronous", comma);
E 76
I 76
			(void)printf("%ssynchronous", comma);
E 76
I 58
			flags &= ~MNT_SYNCHRONOUS;
E 58
			comma = ",";
		}
D 58
		if (flags & M_NOEXEC) {
E 58
I 58
		if (flags & MNT_NOEXEC) {
E 58
D 76
			printf("%snoexec", comma);
E 76
I 76
			(void)printf("%snoexec", comma);
E 76
I 58
			flags &= ~MNT_NOEXEC;
E 58
			comma = ",";
		}
D 58
		if (flags & M_NOSUID) {
E 58
I 58
		if (flags & MNT_NOSUID) {
E 58
D 76
			printf("%snosuid", comma);
E 76
I 76
			(void)printf("%snosuid", comma);
E 76
I 58
			flags &= ~MNT_NOSUID;
E 58
			comma = ",";
		}
D 58
		if (flags & M_NODEV) {
E 58
I 58
		if (flags & MNT_NODEV) {
E 58
D 76
			printf("%snodev", comma);
E 76
I 76
			(void)printf("%snodev", comma);
E 76
I 58
			flags &= ~MNT_NODEV;
E 58
			comma = ",";
		}
D 58
		if (flags & M_EXPORTED) {
E 58
I 58
		if (flags & MNT_EXPORTED) {
E 58
D 76
			printf("%sexport", comma);
E 76
I 76
			(void)printf("%sexport", comma);
E 76
I 58
			flags &= ~MNT_EXPORTED;
E 58
			comma = ",";
		}
D 58
		if (flags & M_EXRDONLY) {
E 58
I 58
		if (flags & MNT_EXRDONLY) {
E 58
D 76
			printf("%sexrdonly", comma);
E 76
I 76
			(void)printf("%sexrdonly", comma);
E 76
I 58
			flags &= ~MNT_EXRDONLY;
E 58
			comma = ",";
		}
D 58
		if (flags & M_MLOCK) {
E 58
I 58
		if (flags & MNT_LOCAL) {
D 76
			printf("%slocal", comma);
E 76
I 76
			(void)printf("%slocal", comma);
E 76
			flags &= ~MNT_LOCAL;
			comma = ",";
		}
		if (flags & MNT_QUOTA) {
D 76
			printf("%squota", comma);
E 76
I 76
			(void)printf("%squota", comma);
E 76
			flags &= ~MNT_QUOTA;
			comma = ",";
		}
		/* filesystem control flags */
		if (flags & MNT_UPDATE) {
D 76
			printf("%supdate", comma);
E 76
I 76
			(void)printf("%supdate", comma);
E 76
			flags &= ~MNT_UPDATE;
			comma = ",";
		}
		if (flags & MNT_MLOCK) {
E 58
D 76
			printf("%slock", comma);
E 76
I 76
			(void)printf("%slock", comma);
E 76
I 58
			flags &= ~MNT_MLOCK;
E 58
			comma = ",";
		}
D 58
		if (flags & M_MWAIT) {
E 58
I 58
		if (flags & MNT_MWAIT) {
E 58
D 76
			printf("%swait", comma);
E 76
I 76
			(void)printf("%swait", comma);
E 76
I 58
			flags &= ~MNT_MWAIT;
E 58
			comma = ",";
		}
D 58
		if (flags & M_UPDATE) {
			printf("%supdate only", comma);
E 58
I 58
		if (flags & MNT_MPBUSY) {
D 76
			printf("%sbusy", comma);
E 76
I 76
			(void)printf("%sbusy", comma);
E 76
			flags &= ~MNT_MPBUSY;
E 58
			comma = ",";
		}
I 58
		if (flags & MNT_MPWANT) {
D 76
			printf("%swant", comma);
E 76
I 76
			(void)printf("%swant", comma);
E 76
			flags &= ~MNT_MPWANT;
			comma = ",";
		}
		if (flags & MNT_UNMOUNT) {
D 76
			printf("%sunmount", comma);
E 76
I 76
			(void)printf("%sunmount", comma);
E 76
			flags &= ~MNT_UNMOUNT;
			comma = ",";
		}
E 86
		if (flags)
D 76
			printf("%sunknown_flags:%x", flags);
E 58
		printf(")");
E 76
I 76
D 86
			(void)printf("%sunknown_flags:%x", comma, flags);
E 86
I 86
			(void)printf("%sunknown_flags:%x", sep, flags);
E 86
		(void)printf(")");
E 76
	}
D 76
	printf("\n");
E 76
I 76
	(void)printf("\n");
E 76
#undef ST
}

D 58
struct vnode *
E 58
I 58
struct e_vnode *
E 58
loadvnodes(avnodes)
	int *avnodes;
{
D 62
	int ret, copysize, i;
E 62
I 62
D 73
	int ret, copysize;
E 73
I 73
	int mib[2];
	size_t copysize;
E 73
E 62
D 58
	struct vnode *vnodebase;
E 58
I 58
	struct e_vnode *vnodebase;
I 70
D 76
	struct e_vnode *kinfo_vnodes();
E 76
E 70
E 58

D 71
	if (fcore != NULL) {
E 71
I 71
	if (memf != NULL) {
E 71
D 69
		error("vnodes on dead kernel, not impl yet\n");
E 69
I 69
		/*
D 70
		 * add emulation of KINFO_VNODE here
E 70
I 70
		 * do it by hand
E 70
		 */
D 70
		error("vnodes on dead kernel, not impl\n");
E 69
		exit(1);
E 70
I 70
		return (kinfo_vnodes(avnodes));
E 70
	}
D 73
	if ((ret = getkerninfo(KINFO_VNODE, NULL, NULL, 0)) == -1) {
		syserror("can't get estimate for kerninfo");
E 73
I 73
	mib[0] = CTL_KERN;
	mib[1] = KERN_VNODE;
D 76
	if (sysctl(mib, 2, NULL, &copysize, NULL, 0) == -1) {
		syserror("can't get estimate from sysctl");
E 73
		exit(1);
	}
D 73
	copysize = ret;
D 58
	if ((vnodebase = (struct vnode *)malloc(copysize)) 
E 58
I 58
	if ((vnodebase = (struct e_vnode *)malloc(copysize)) 
E 58
	     == NULL) {
E 73
I 73
	if ((vnodebase = (struct e_vnode *)malloc(copysize)) == NULL) {
E 73
		error("out of memory");
		exit(1);
	}
D 73
	if ((ret = getkerninfo(KINFO_VNODE, vnodebase, &copysize, 0)) 
	     == -1) {
E 73
I 73
	if (sysctl(mib, 2, vnodebase, &copysize, NULL, 0) == -1) {
E 73
		syserror("can't get vnode list");
		exit(1);
	}
D 58
	if (copysize % sizeof (struct vnode)) {
E 58
I 58
	if (copysize % sizeof (struct e_vnode)) {
E 58
		error("vnode size mismatch");
D 63
		error(1);
E 63
I 63
		exit(1);
E 63
	}
D 58
	*avnodes = copysize / sizeof (struct vnode);
E 58
I 58
	*avnodes = copysize / sizeof (struct e_vnode);
E 76
I 76
	if (sysctl(mib, 2, NULL, &copysize, NULL, 0) == -1)
		err(1, "sysctl: KERN_VNODE");
	if ((vnodebase = malloc(copysize)) == NULL)
		err(1, NULL);
	if (sysctl(mib, 2, vnodebase, &copysize, NULL, 0) == -1)
		err(1, "sysctl: KERN_VNODE");
	if (copysize % sizeof(struct e_vnode))
		errx(1, "vnode size mismatch");
	*avnodes = copysize / sizeof(struct e_vnode);
E 76
E 58

	return (vnodebase);
}

I 70
/*
 * simulate what a running kernel does in in kinfo_vnode
 */
struct e_vnode *
kinfo_vnodes(avnodes)
	int *avnodes;
{
D 75
	struct nlist vnl[] = {
#define V_NUMV	0
		{ "_numvnodes" },
#define V_ROOTFS 1
		{ "_rootfs" },
		{""}
	};
E 75
D 81
	int numvnodes;
	struct mount *rootfs, *mp, mount;
	char *vbuf, *evbuf, *bp;
E 81
I 81
	struct mntlist mountlist;
	struct mount *mp, mount;
E 81
	struct vnode *vp, vnode;
D 81
	int num;
E 81
I 81
	char *vbuf, *evbuf, *bp;
	int num, numvnodes;
E 81

D 76
#define VPTRSZ  sizeof (struct vnode *)
#define VNODESZ sizeof (struct vnode)
E 76
I 76
#define VPTRSZ  sizeof(struct vnode *)
#define VNODESZ sizeof(struct vnode)
E 76
D 75
#define NVAL(indx)	vnl[(indx)].n_value
E 75

D 73
	if (kvm_nlist(vnl) != 0) {
		error("nlist vnl: %s", kvm_geterr());
E 73
I 73
D 75
	if (kvm_nlist(kd, vnl) != 0) {
		error("nlist vnl: %s", kvm_geterr(kd));
E 73
		exit(1);
	}
	numvnodes = getword(NVAL(V_NUMV));
E 75
I 75
	KGET(V_NUMV, numvnodes);
E 75
D 76
	if ((vbuf = (char *)malloc((numvnodes + 20) * (VPTRSZ + VNODESZ))) 
	    == NULL) {
		error("out of memory");
		exit(1);
	}
E 76
I 76
	if ((vbuf = malloc((numvnodes + 20) * (VPTRSZ + VNODESZ))) == NULL)
		err(1, NULL);
E 76
	bp = vbuf;
	evbuf = vbuf + (numvnodes + 20) * (VPTRSZ + VNODESZ);
D 75
	mp = rootfs = (struct mount *)getword(NVAL(V_ROOTFS));
E 75
I 75
D 81
	KGET(V_ROOTFS, rootfs);
	mp = rootfs;
E 75
	do {
E 81
I 81
	KGET(V_MOUNTLIST, mountlist);
D 85
	for (mp = mountlist.tqh_first; mp != NULL; mp = mp->mnt_list.tqe_next) {
E 85
I 85
D 92
	for (num = 0, mp = mountlist.tqh_first;
	    mp != NULL; mp = mp->mnt_list.tqe_next) {
E 92
I 92
	for (num = 0, mp = mountlist.cqh_first; ; mp = mp->mnt_list.cqe_next) {
E 92
E 85
E 81
D 73
		kvm_read(mp, &mount, sizeof(mount));
E 73
I 73
D 75
		kvm_read(kd, V(mp), &mount, sizeof(mount));
E 75
I 75
		KGET2(mp, &mount, sizeof(mount), "mount entry");
E 75
E 73
D 81
		for (vp = mount.mnt_mounth; vp; vp = vnode.v_mountf) {
E 81
I 81
		for (vp = mount.mnt_vnodelist.lh_first;
		    vp != NULL; vp = vp->v_mntvnodes.le_next) {
E 81
D 73
			kvm_read(vp, &vnode, sizeof (vnode));
E 73
I 73
D 75
			kvm_read(kd, V(vp), &vnode, sizeof (vnode));
E 75
I 75
			KGET2(vp, &vnode, sizeof(vnode), "vnode");
E 75
E 73
D 76
			if ((bp + VPTRSZ + VNODESZ) > evbuf) {
E 76
I 76
			if ((bp + VPTRSZ + VNODESZ) > evbuf)
E 76
				/* XXX - should realloc */
D 76
				fprintf(stderr, "pstat: ran out of room for vnodes\n");
				exit(1);
			}
			bcopy(&vp, bp, VPTRSZ);
E 76
I 76
				errx(1, "no more room for vnodes");
			memmove(bp, &vp, VPTRSZ);
E 76
			bp += VPTRSZ;
D 76
			bcopy(&vnode, bp, VNODESZ);
E 76
I 76
			memmove(bp, &vnode, VNODESZ);
E 76
			bp += VNODESZ;
			num++;
		}
I 92
		if (mp == mountlist.cqh_last)
			break;
E 92
D 81
		mp = mount.mnt_next;
	} while (mp != rootfs);
E 81
I 81
	}
E 81
	*avnodes = num;
	return ((struct e_vnode *)vbuf);
}
	
D 75
	
E 70
E 57
I 40
u_long
E 40
I 5
D 48
getw(loc)
E 48
I 48
getword(loc)
E 48
D 63
	off_t loc;
E 63
I 63
	int loc;
E 63
{
D 40
	int word;
E 40
I 40
	u_long word;
E 40

I 7
D 57
	if (kflg)
D 42
		loc &= 0x7fffffff;
E 42
I 42
		loc = clear(loc);
E 42
E 7
	lseek(fc, loc, 0);
	read(fc, &word, sizeof (word));
E 57
I 57
D 63
	kvm_read(loc, &word, sizeof (word));
E 63
I 63
D 73
	kvm_read(V(loc), &word, sizeof (word));
E 73
I 73
	kvm_read(kd, V(loc), &word, sizeof (word));
E 73
E 63
E 57
I 8
D 40
	if (kflg)
		word &= 0x7fffffff;
E 40
E 8
	return (word);
}

E 5
putf(v, n)
{
	if (v)
		printf("%c", n);
	else
D 4
		printf(" ");
E 4
I 4
D 5
		printf("_");
E 5
I 5
		printf(" ");
E 5
E 4
}

dotext()
{
I 64
D 73
#ifdef NEWVM
	printf("no text table in this system\n");
#else
E 64
	register struct text *xp;
D 5
	struct text xtext[NTEXT];
	register loc;
E 5
I 5
	int ntext;
	struct text *xtext, *atext;
E 5
D 40
	int ntx;
E 40
I 40
	int ntx, ntxca;
E 73
E 40

D 40
	ntx = 0;
E 40
I 40
D 73
	ntx = ntxca = 0;
E 40
D 5
	lseek(fc, (long)nl[STEXT].n_value, 0);
	read(fc, xtext, sizeof(xtext));
	for (xp = xtext; xp < &xtext[NTEXT]; xp++)
E 5
I 5
D 48
	ntext = getw(nl[SNTEXT].n_value);
E 48
I 48
	ntext = getword(nl[SNTEXT].n_value);
E 48
	xtext = (struct text *)calloc(ntext, sizeof (struct text));
D 35
	lseek(fc, (int)(atext = (struct text *)getw(nl[STEXT].n_value)), 0);
E 35
I 35
D 48
	atext = (struct text *)getw(nl[STEXT].n_value);
E 48
I 48
	atext = (struct text *)getword(nl[STEXT].n_value);
E 48
D 40
	lseek(fc, mkphys((int)atext), 0);
E 40
I 40
	if (ntext < 0 || ntext > 10000) {
		fprintf(stderr, "number of texts is preposterous (%d)\n",
			ntext);
		return;
	}
	if (xtext == NULL) {
		fprintf(stderr, "can't allocate memory for text table\n");
		return;
	}
D 57
	lseek(fc, mkphys((off_t)atext), 0);
E 40
E 35
	read(fc, xtext, ntext * sizeof (struct text));
E 57
I 57
	kvm_read(atext, xtext, ntext * sizeof (struct text));
E 57
D 40
	for (xp = xtext; xp < &xtext[ntext]; xp++)
E 5
		if (xp->x_iptr!=NULL)
E 40
I 40
	for (xp = xtext; xp < &xtext[ntext]; xp++) {
D 54
		if (xp->x_iptr != NULL)
E 54
I 54
		if (xp->x_vptr != NULL)
E 54
			ntxca++;
		if (xp->x_count != 0)
E 40
			ntx++;
I 40
	}
E 40
	if (totflg) {
D 5
		printf("%3d/%3d texts\n", ntx, NTEXT);
E 5
I 5
D 40
		printf("%3d/%3d texts\n", ntx, ntext);
E 40
I 40
		printf("%3d/%3d texts active, %3d used\n", ntx, ntext, ntxca);
E 40
E 5
		return;
	}
I 5
D 40
	printf("%d/%d active texts\n", ntx, ntext);
E 5
D 2
	printf("   LOC   FLAGS  PTDADDR DADDR  CADDR  RSS   SIZE   IPTR    CNT CCNT\n");
E 2
I 2
	printf("   LOC   FLAGS DADDR      CADDR  RSS SIZE      IPTR  CNT CCNT\n");
E 40
I 40
	printf("%d/%d active texts, %d used\n", ntx, ntext, ntxca);
	printf("\
D 54
   LOC   FLAGS DADDR     CADDR  RSS SIZE     IPTR   CNT CCNT      FORW     BACK\n");
E 54
I 54
   LOC   FLAGS DADDR     CADDR  RSS SIZE     VPTR   CNT CCNT      FORW     BACK\n");
E 54
E 40
E 2
D 5
	loc = nl[STEXT].n_value;
	for (xp = xtext; xp < &xtext[NTEXT]; xp++, loc+=sizeof(xtext[0])) {
E 5
I 5
	for (xp = xtext; xp < &xtext[ntext]; xp++) {
E 5
D 54
		if (xp->x_iptr == NULL)
E 54
I 54
		if (xp->x_vptr == NULL)
E 54
			continue;
D 5
		printf("%8.1x", loc);
E 5
I 5
		printf("%8.1x", atext + (xp - xtext));
E 5
		printf(" ");
D 54
		putf(xp->x_flag&XPAGI, 'P');
E 54
I 54
		putf(xp->x_flag&XPAGV, 'P');
E 54
		putf(xp->x_flag&XTRC, 'T');
		putf(xp->x_flag&XWRIT, 'W');
		putf(xp->x_flag&XLOAD, 'L');
		putf(xp->x_flag&XLOCK, 'K');
		putf(xp->x_flag&XWANT, 'w');
D 2
		printf("%8x", xp->x_ptdaddr);
E 2
		printf("%5x", xp->x_daddr[0]);
D 40
		printf("%11x", xp->x_caddr);
E 40
I 40
		printf("%10x", xp->x_caddr);
E 40
		printf("%5d", xp->x_rssize);
		printf("%5d", xp->x_size);
D 54
		printf("%10.1x", xp->x_iptr);
E 54
I 54
		printf("%10.1x", xp->x_vptr);
E 54
		printf("%5d", xp->x_count&0377);
D 2
		printf("%4d", xp->x_ccount);
E 2
I 2
		printf("%5d", xp->x_ccount);
I 40
		printf("%10x", xp->x_forw);
		printf("%9x", xp->x_back);
E 40
E 2
		printf("\n");
	}
I 5
	free(xtext);
I 64
#endif
E 73
I 73
	printf("no text table in this system\n");
E 73
E 64
E 5
}

doproc()
{
I 64
D 70
#ifdef NEWVM
D 69
	printf("pstat: -p no longer supported\n");
E 69
I 69
	printf("pstat: -p no longer supported (use ps)\n");
E 69
#else
E 64
D 5
	struct proc xproc[NPROC];
E 5
I 5
	struct proc *xproc, *aproc;
	int nproc;
E 5
	register struct proc *pp;
	register loc, np;
I 62
	/*
E 62
	struct pte apte;
I 62
	*/
E 62

D 5
	lseek(fc, (long)nl[SPROC].n_value, 0);
	read(fc, xproc, sizeof(xproc));
E 5
I 5
D 48
	nproc = getw(nl[SNPROC].n_value);
E 48
I 48
	nproc = getword(nl[SNPROC].n_value);
E 48
	xproc = (struct proc *)calloc(nproc, sizeof (struct proc));
D 35
	lseek(fc, (int)(aproc = (struct proc *)getw(nl[SPROC].n_value)), 0);
E 35
I 35
D 48
	aproc = (struct proc *)getw(nl[SPROC].n_value);
E 48
I 48
	aproc = (struct proc *)getword(nl[SPROC].n_value);
E 48
D 40
	lseek(fc, mkphys((int)aproc), 0);
E 40
I 40
D 60
	if (nproc < 0 || nproc > 10000) {
E 60
I 60
	if (nproc < 0 || nproc > 100000) {
E 60
		fprintf(stderr, "number of procs is preposterous (%d)\n",
			nproc);
		return;
	}
	if (xproc == NULL) {
		fprintf(stderr, "can't allocate memory for proc table\n");
		return;
	}
D 57
	lseek(fc, mkphys((off_t)aproc), 0);
E 40
E 35
	read(fc, xproc, nproc * sizeof (struct proc));
E 57
I 57
	kvm_read(aproc, xproc, nproc * sizeof (struct proc));
E 57
E 5
	np = 0;
D 5
	for (pp=xproc; pp < &xproc[NPROC]; pp++)
E 5
I 5
	for (pp=xproc; pp < &xproc[nproc]; pp++)
E 5
		if (pp->p_stat)
			np++;
	if (totflg) {
D 5
		printf("%3d/%3d processes\n", np, NPROC);
E 5
I 5
		printf("%3d/%3d processes\n", np, nproc);
E 5
		return;
	}
D 5
	printf("%d/%d processes\n", np, NPROC);
E 5
I 5
	printf("%d/%d processes\n", np, nproc);
E 5
D 2
	printf("   LOC    S    F POIP PRI SIG  UID  SLP TIM  CPU  NI    PGRP   PID   PPID    ADDR   RSS  SRSS SIZE   WCHAN    LINK   TEXTP CLKT\n");
E 2
I 2
D 33
	printf("   LOC    S    F POIP PRI      SIG  UID SLP TIM  CPU  NI   PGRP    PID   PPID    ADDR   RSS SRSS SIZE    WCHAN    LINK   TEXTP CLKT\n");
E 33
I 33
D 56
	printf("   LOC    S    F POIP PRI      SIG  UID SLP TIM  CPU  NI   PGRP    PID   PPID    ADDR   RSS SRSS SIZE    WCHAN    LINK   TEXTP\n");
E 56
I 56
	printf("   LOC    S        F POIP PRI      SIG  UID SLP TIM  CPU  NI    PID   PPID    ADDR   RSS SRSS SIZE    WCHAN    LINK   TEXTP\n");
E 56
E 33
E 2
D 5
	for (loc=nl[SPROC].n_value,pp=xproc; pp<&xproc[NPROC]; pp++,loc+=sizeof(xproc[0])) {
E 5
I 5
	for (pp=xproc; pp<&xproc[nproc]; pp++) {
E 5
		if (pp->p_stat==0 && allflg==0)
			continue;
D 5
		printf("%8x", loc);
E 5
I 5
		printf("%8x", aproc + (pp - xproc));
E 5
		printf(" %2d", pp->p_stat);
D 56
		printf(" %4x", pp->p_flag & 0xffff);
E 56
I 56
		printf(" %8x", pp->p_flag);
E 56
		printf(" %4d", pp->p_poip);
		printf(" %3d", pp->p_pri);
D 2
		printf(" %4x", pp->p_sig);
E 2
I 2
		printf(" %8x", pp->p_sig);
E 2
		printf(" %4d", pp->p_uid);
		printf(" %3d", pp->p_slptime);
		printf(" %3d", pp->p_time);
		printf(" %4d", pp->p_cpu&0377);
		printf(" %3d", pp->p_nice);
D 56
		printf(" %6d", pp->p_pgrp);
E 56
		printf(" %6d", pp->p_pid);
		printf(" %6d", pp->p_ppid);
D 57
		if (kflg)
			pp->p_addr = (struct pte *)clear((int)pp->p_addr);
E 57
I 57
		/* 
E 57
D 33
		lseek(fc, (long)(Usrptma+btokmx(pp->p_addr)), 0);
		read(fc, &apte, sizeof(apte));
		printf(" %8x", ctob(apte.pg_pfnum+1) - sizeof(struct pte) * UPAGES);
E 33
I 33
		if (pp->p_flag & SLOAD) {
D 57
			lseek(fc, (long)pp->p_addr, 0);
			read(fc, &apte, sizeof(apte));
E 57
I 57
			kvm_read(pp->p_addr, &apte, sizeof(apte));
E 57
			printf(" %8x", apte.pg_pfnum);
		} else
			printf(" %8x", pp->p_swaddr);
I 57
		*/
E 57
E 33
		printf(" %4x", pp->p_rssize);
		printf(" %4x", pp->p_swrss);
		printf(" %5x", pp->p_dsize+pp->p_ssize);
		printf(" %7x", clear(pp->p_wchan));
		printf(" %7x", clear(pp->p_link));
		printf(" %7x", clear(pp->p_textp));
D 19
		printf("    %u", pp->p_clktim);
E 19
		printf("\n");
	}
I 40
	free(xproc);
I 64
#endif
E 70
I 70
	if (!totflg)
		printf("pstat: -p no longer supported (use ps)\n");
E 70
E 64
E 40
}

I 36
D 54
static char mesg[] =
D 52
" # RAW CAN OUT     MODE     ADDR DEL COL     STATE  PGRP DISC\n";
E 52
I 52
" #  DEV RAW CAN OUT    RCC    CCC    OCC  HWT LWT     ADDR COL STATE  PGRP DISC\n";
E 54
I 54
D 57
static char mesg[] = " #  DEV RAW CAN OUT    RCC    CCC    OCC  HWT LWT     ADDR COL STATE  PGRP DISC\n";
E 54
E 52
static int ttyspace = 128;
static struct tty *tty;
E 57
I 57
D 58
char mesg[] = " #  DEV RAW CAN OUT    RCC    CCC    OCC  HWT LWT     ADDR COL STATE  PGRP DISC\n";
E 58
I 58
D 60
char mesg[] = "LINE    RAW CAN OUT    RCC    CCC    OCC  HWT LWT     ADDR COL STATE  PGID DISC\n";
E 60
I 60
D 61
char mesg[] = "  LINE RAW CAN OUT    RCC    CCC    OCC  HWT LWT     ADDR COL STATE  PGID DISC\n";
E 61
I 61
char mesg[] = "  LINE RAW CAN OUT  HWT LWT     ADDR COL STATE  SESS  PGID DISC\n";
E 75
I 75
D 78
char hdr[]="  LINE RAW CAN OUT  HWT LWT     ADDR COL STATE  SESS  PGID DISC\n";
E 78
I 78
D 90
char hdr[]="  LINE RAW CAN OUT  HWT LWT     COL STATE  SESS  PGID DISC\n";
E 90
I 90
char hdr[]="  LINE RAW CAN OUT  HWT LWT     COL STATE  SESS      PGID DISC\n";
E 90
E 78
E 75
E 61
E 60
E 58
int ttyspace = 128;
D 76
struct tty *tty;
E 76
E 57

E 36
D 76
dotty()
E 76
I 76
void
ttymode()
E 76
{
I 76
	struct tty *tty;
E 76
D 13
	struct tty dz_tty[64];
E 13
I 13
D 32
	struct tty dz_tty[128];
E 13
	int ndz;
E 32
I 32
D 36
	struct tty *tty;
	int ntty, ttyspace = 128;
E 32
	register struct tty *tp;
I 32
	extern char *malloc(), *realloc();
E 32
D 30
	register char *mesg;
E 30
I 30
	static char mesg[] =
	" # RAW CAN OUT     MODE     ADDR DEL COL     STATE  PGRP DISC\n";
E 36
I 36
D 57
	extern char *malloc();
E 57
E 36
E 30

I 32
D 76
	if ((tty = (struct tty *)malloc(ttyspace * sizeof(*tty))) == 0) {
		printf("pstat: out of memory\n");
		return;
	}
E 76
I 76
	if ((tty = malloc(ttyspace * sizeof(*tty))) == NULL)
		err(1, NULL);
E 76
I 61
D 90
#ifndef hp300
E 90
I 90
#if !defined(hp300) && !defined(mips)
E 90
E 61
E 32
I 21
D 22
	mesg = " # RAW CAN OUT     MODE     ADDR DEL COL STATE     PGRP DISC\n";
E 22
E 21
D 76
	printf("1 cons\n");
E 76
I 76
	(void)printf("1 console\n");
E 76
I 9
D 57
	if (kflg)
D 42
		nl[SKL].n_value = clear(nl[SKL].n_value);
E 9
	lseek(fc, (long)nl[SKL].n_value, 0);
E 42
I 42
		nl[SCONS].n_value = clear(nl[SCONS].n_value);
	lseek(fc, (long)nl[SCONS].n_value, 0);
E 42
D 32
	read(fc, dz_tty, sizeof(dz_tty[0]));
E 32
I 32
	read(fc, tty, sizeof(*tty));
E 57
I 57
D 63
	kvm_read((long)nl[SCONS].n_value, tty, sizeof(*tty));
E 63
I 63
D 73
	kvm_read(V(nl[SCONS].n_value), tty, sizeof(*tty));
E 73
I 73
D 75
	kvm_read(kd, V(nl[SCONS].n_value), tty, sizeof(*tty));
E 73
E 63
E 57
E 32
I 22
D 30
	mesg = " # RAW CAN OUT   MODE    ADDR   DEL COL  STATE   PGRP DISC\n";
E 30
E 22
D 21
	mesg = " # RAW CAN OUT   MODE    ADDR   DEL COL  STATE   PGRP DISC\n";
E 21
	printf(mesg);
E 75
I 75
	KGET(SCONS, *tty);
D 76
	printf(hdr);
E 76
I 76
	(void)printf(hdr);
E 76
E 75
D 32
	ttyprt(&dz_tty[0], 0);
E 32
I 32
	ttyprt(&tty[0], 0);
I 61
#endif
E 61
I 42
#ifdef vax
I 46
	if (nl[SNQD].n_type != 0) 
D 76
		doqdss();
E 76
I 76
		qdss();
E 76
E 46
E 42
E 32
D 3
	if (nl[SNDZ].n_type == -1)
E 3
I 3
D 36
	if (nl[SNDZ].n_type == 0)
E 3
		goto dh;
I 9
	if (kflg) {
		nl[SNDZ].n_value = clear(nl[SNDZ].n_value);
		nl[SDZ].n_value = clear(nl[SDZ].n_value);
	}
E 9
	lseek(fc, (long)nl[SNDZ].n_value, 0);
D 32
	read(fc, &ndz, sizeof(ndz));
	printf("%d dz lines\n", ndz);
E 32
I 32
	read(fc, &ntty, sizeof(ntty));
	printf("%d dz lines\n", ntty);
	if (ntty > ttyspace) {
		ttyspace = ntty;
		if ((tty = (struct tty *)realloc(tty, ttyspace * sizeof(*tty))) == 0) {
			printf("pstat: out of memory\n");
			return;
		}
	}
E 32
	lseek(fc, (long)nl[SDZ].n_value, 0);
D 13
	read(fc, dz_tty, sizeof(dz_tty));
E 13
I 13
D 32
	read(fc, dz_tty, ndz * sizeof (struct tty));
E 32
I 32
	read(fc, tty, ntty * sizeof (struct tty));
E 32
I 30
	printf(mesg);
E 30
I 21
D 22
	printf(mesg);
E 22
E 21
E 13
D 32
	for (tp = dz_tty; tp < &dz_tty[ndz]; tp++)
		ttyprt(tp, tp - dz_tty);
E 32
I 32
	for (tp = tty; tp < &tty[ntty]; tp++)
		ttyprt(tp, tp - tty);
E 32
dh:
D 3
	if (nl[SNDH].n_type == -1)
E 3
I 3
	if (nl[SNDH].n_type == 0)
E 3
D 12
		return;
E 12
I 12
D 21
		goto pty;
E 21
I 21
D 22
		goto dmf;
E 22
I 22
D 28
		goto pty;
E 28
I 28
		goto dmf;
E 28
E 22
E 21
E 12
I 9
	if (kflg) {
		nl[SNDH].n_value = clear(nl[SNDH].n_value);
		nl[SDH].n_value = clear(nl[SDH].n_value);
	}
E 9
	lseek(fc, (long)nl[SNDH].n_value, 0);
D 32
	read(fc, &ndz, sizeof(ndz));
	printf("%d dh lines\n", ndz);
E 32
I 32
	read(fc, &ntty, sizeof(ntty));
	printf("%d dh lines\n", ntty);
	if (ntty > ttyspace) {
		ttyspace = ntty;
		if ((tty = (struct tty *)realloc(tty, ttyspace * sizeof(*tty))) == 0) {
			printf("pstat: out of memory\n");
			return;
		}
	}
E 32
	lseek(fc, (long)nl[SDH].n_value, 0);
D 13
	read(fc, dz_tty, sizeof(dz_tty));
E 13
I 13
D 32
	read(fc, dz_tty, ndz * sizeof(struct tty));
E 32
I 32
	read(fc, tty, ntty * sizeof(struct tty));
E 32
I 30
	printf(mesg);
E 30
I 21
D 22
	printf(mesg);
E 22
E 21
E 13
D 32
	for (tp = dz_tty; tp < &dz_tty[ndz]; tp++)
		ttyprt(tp, tp - dz_tty);
E 32
I 32
	for (tp = tty; tp < &tty[ntty]; tp++)
		ttyprt(tp, tp - tty);
E 32
I 28
dmf:
	if (nl[SNDMF].n_type == 0)
		goto pty;
	if (kflg) {
		nl[SNDMF].n_value = clear(nl[SNDMF].n_value);
		nl[SDMF].n_value = clear(nl[SDMF].n_value);
	}
	lseek(fc, (long)nl[SNDMF].n_value, 0);
D 32
	read(fc, &ndz, sizeof(ndz));
	printf("%d dmf lines\n", ndz);
E 32
I 32
	read(fc, &ntty, sizeof(ntty));
	printf("%d dmf lines\n", ntty);
	if (ntty > ttyspace) {
		ttyspace = ntty;
		if ((tty = (struct tty *)realloc(tty, ttyspace * sizeof(*tty))) == 0) {
			printf("pstat: out of memory\n");
			return;
		}
	}
E 32
	lseek(fc, (long)nl[SDMF].n_value, 0);
D 32
	read(fc, dz_tty, ndz * sizeof(struct tty));
E 32
I 32
	read(fc, tty, ntty * sizeof(struct tty));
E 32
I 30
	printf(mesg);
E 30
D 32
	for (tp = dz_tty; tp < &dz_tty[ndz]; tp++)
		ttyprt(tp, tp - dz_tty);
E 32
I 32
	for (tp = tty; tp < &tty[ntty]; tp++)
		ttyprt(tp, tp - tty);
E 32
E 28
I 21
D 22
dmf:
	if (nl[SNDMF].n_type == 0)
		goto pty;
	if (kflg) {
		nl[SNDMF].n_value = clear(nl[SNDMF].n_value);
		nl[SDMF].n_value = clear(nl[SDMF].n_value);
	}
	lseek(fc, (long)nl[SNDMF].n_value, 0);
	read(fc, &ndz, sizeof(ndz));
	printf("%d dmf lines\n", ndz);
	lseek(fc, (long)nl[SDMF].n_value, 0);
	read(fc, dz_tty, ndz * sizeof(struct tty));
	printf(mesg);
	for (tp = dz_tty; tp < &dz_tty[ndz]; tp++)
		ttyprt(tp, tp - dz_tty);
E 22
E 21
I 12
pty:
	if (nl[SPTY].n_type == 0)
E 36
I 36
	if (nl[SNDZ].n_type != 0)
D 76
		dottytype("dz", SDZ, SNDZ);
E 76
I 76
		ttytype(tty, "dz", SDZ, SNDZ);
E 76
	if (nl[SNDH].n_type != 0)
D 76
		dottytype("dh", SDH, SNDH);
E 76
I 76
		ttytype(tty, "dh", SDH, SNDH);
E 76
	if (nl[SNDMF].n_type != 0)
D 76
		dottytype("dmf", SDMF, SNDMF);
E 76
I 76
		ttytype(tty, "dmf", SDMF, SNDMF);
E 76
	if (nl[SNDHU].n_type != 0)
D 76
		dottytype("dhu", SDHU, SNDHU);
E 76
I 76
		ttytype(tty, "dhu", SDHU, SNDHU);
E 76
I 38
	if (nl[SNDMZ].n_type != 0)
D 76
		dottytype("dmz", SDMZ, SNDMZ);
E 76
I 76
		ttytype(tty, "dmz", SDMZ, SNDMZ);
E 76
I 42
#endif
#ifdef tahoe
	if (nl[SNVX].n_type != 0)
D 76
		dottytype("vx", SVX, SNVX);
E 76
I 76
		ttytype(tty, "vx", SVX, SNVX);
E 76
I 51
	if (nl[SNMP].n_type != 0)
D 76
		dottytype("mp", SMP, SNMP);
E 76
I 76
		ttytype(tty, "mp", SMP, SNMP);
E 76
E 51
#endif
I 61
#ifdef hp300
	if (nl[SNITE].n_type != 0)
D 76
		dottytype("ite", SITE, SNITE);
E 76
I 76
		ttytype(tty, "ite", SITE, SNITE);
E 76
	if (nl[SNDCA].n_type != 0)
D 76
		dottytype("dca", SDCA, SNDCA);
E 76
I 76
		ttytype(tty, "dca", SDCA, SNDCA);
E 76
	if (nl[SNDCM].n_type != 0)
D 76
		dottytype("dcm", SDCM, SNDCM);
E 76
I 76
		ttytype(tty, "dcm", SDCM, SNDCM);
E 76
	if (nl[SNDCL].n_type != 0)
D 76
		dottytype("dcl", SDCL, SNDCL);
E 76
I 76
		ttytype(tty, "dcl", SDCL, SNDCL);
E 76
I 74
#endif
#ifdef mips
	if (nl[SNDC].n_type != 0)
D 76
		dottytype("dc", SDC, SNDC);
E 76
I 76
		ttytype(tty, "dc", SDC, SNDC);
E 76
E 74
#endif
E 61
E 42
E 38
	if (nl[SNPTY].n_type != 0)
D 76
		dottytype("pty", SPTY, SNPTY);
E 76
I 76
		ttytype(tty, "pty", SPTY, SNPTY);
E 76
}

I 46
D 75
/* 
D 52
 * Special case the qdss because there are 4 tty structs per qdss 
 * and only the first of each is used as a tty.  
E 52
I 52
 * Special case the qdss: there are 4 ttys per qdss,
 * but only the first of each is used as a tty.  
E 52
 */
#ifdef vax
doqdss()
{
	int nqd;
	register struct tty *tp;

D 57
	if (kflg) {
		nl[SNQD].n_value = clear(nl[SNQD].n_value);
		nl[SQD].n_value = clear(nl[SQD].n_value);
	}
	lseek(fc, (long)nl[SNQD].n_value, 0);
	read(fc, &nqd, sizeof(nqd));
E 57
I 57
D 63
	kvm_read((long)nl[SNQD].n_value, &nqd, sizeof(nqd));
E 63
I 63
D 73
	kvm_read(V(nl[SNQD].n_value), &nqd, sizeof(nqd));
E 73
I 73
	kvm_read(kd, V(nl[SNQD].n_value), &nqd, sizeof(nqd));
E 73
E 63
E 57
	printf("%d qd\n", nqd);
D 57
	lseek(fc, (long)nl[SQD].n_value, 0);
	read(fc, tty, nqd * sizeof(struct tty) * 4);
E 57
I 57
D 63
	kvm_read((long)nl[SQD].n_value, tty, nqd * sizeof(struct tty) * 4);
E 63
I 63
D 70
	kvm_read((V(nl[SQD].n_value), tty, nqd * sizeof(struct tty) * 4);
E 70
I 70
D 73
	kvm_read(V(nl[SQD].n_value), tty, nqd * sizeof(struct tty) * 4);
E 73
I 73
	kvm_read(kd, V(nl[SQD].n_value), tty, nqd * sizeof(struct tty) * 4);
E 73
E 70
E 63
E 57
	printf(mesg);
	for (tp = tty; tp < &tty[nqd * 4]; tp += 4)
		ttyprt(tp, tp - tty);
}
#endif

E 75
E 46
D 76
dottytype(name, type, number)
char *name;
E 76
I 76
void
ttytype(tty, name, type, number)
D 86
	register struct tty *tty;
E 86
I 86
	struct tty *tty;
E 86
	char *name;
	int type, number;
E 76
{
D 76
	int ntty;
E 76
D 86
	register struct tty *tp;
E 86
I 86
	struct tty *tp;
E 86
I 76
	int ntty;
E 76
D 75
	extern char *realloc();
E 75

D 46
	if (tty == (struct tty *)0)
E 46
I 46
D 76
	if (tty == (struct tty *)0) 
E 76
I 76
	if (tty == NULL)
E 76
E 46
E 36
D 28
		goto pty;
E 28
I 28
		return;
E 28
D 57
	if (kflg) {
D 36
		nl[SPTY].n_value = clear(nl[SPTY].n_value);
I 32
		nl[SNPTY].n_value = clear(nl[SNPTY].n_value);
E 36
I 36
		nl[number].n_value = clear(nl[number].n_value);
		nl[type].n_value = clear(nl[type].n_value);
E 36
E 32
	}
D 13
	printf("16 pty lines\n");
E 13
I 13
D 32
	printf("32 pty lines\n");
E 32
I 32
D 36
	lseek(fc, (long)nl[SNPTY].n_value, 0);
E 36
I 36
	lseek(fc, (long)nl[number].n_value, 0);
E 36
	read(fc, &ntty, sizeof(ntty));
E 57
I 57
D 63
	kvm_read((long)nl[number].n_value, &ntty, sizeof(ntty));
E 63
I 63
D 73
	kvm_read(V(nl[number].n_value), &ntty, sizeof(ntty));
E 73
I 73
D 75
	kvm_read(kd, V(nl[number].n_value), &ntty, sizeof(ntty));
E 75
I 75
	KGET(number, ntty);
E 75
E 73
E 63
E 57
D 36
	printf("%d pty lines\n", ntty);
E 36
I 36
D 70
	printf("%d %s lines\n", ntty, name);
E 70
I 70
D 76
	printf("%d %s %s\n", ntty, name, (ntty == 1) ? "line" :
	    "lines");
E 76
I 76
	(void)printf("%d %s %s\n", ntty, name, (ntty == 1) ? "line" : "lines");
E 76
E 70
E 36
	if (ntty > ttyspace) {
		ttyspace = ntty;
D 76
		if ((tty = (struct tty *)realloc(tty, ttyspace * sizeof(*tty))) == 0) {
			printf("pstat: out of memory\n");
			return;
		}
E 76
I 76
		if ((tty = realloc(tty, ttyspace * sizeof(*tty))) == 0)
			err(1, NULL);
E 76
	}
E 32
E 13
D 36
	lseek(fc, (long)nl[SPTY].n_value, 0);
D 13
	read(fc, dz_tty, sizeof(dz_tty));
	for (tp = dz_tty; tp < &dz_tty[16]; tp++)
E 13
I 13
D 32
	read(fc, dz_tty, 32*sizeof(struct tty));
E 32
I 32
	read(fc, tty, ntty*sizeof(struct tty));
E 36
I 36
D 57
	lseek(fc, (long)nl[type].n_value, 0);
	read(fc, tty, ntty * sizeof(struct tty));
E 57
I 57
D 63
	kvm_read((long)nl[type].n_value, tty, ntty * sizeof(struct tty));
E 63
I 63
D 73
	kvm_read(V(nl[type].n_value), tty, ntty * sizeof(struct tty));
E 73
I 73
D 75
	kvm_read(kd, V(nl[type].n_value), tty, ntty * sizeof(struct tty));
E 73
E 63
E 57
E 36
E 32
I 30
	printf(mesg);
E 75
I 75
	KGET1(type, tty, ntty * sizeof(struct tty), "tty structs");
D 76
	printf(hdr);
E 76
I 76
	(void)printf(hdr);
E 76
E 75
E 30
I 21
D 22
	printf(mesg);
E 22
E 21
D 32
	for (tp = dz_tty; tp < &dz_tty[32]; tp++)
E 13
		ttyprt(tp, tp - dz_tty);
E 32
I 32
	for (tp = tty; tp < &tty[ntty]; tp++)
		ttyprt(tp, tp - tty);
E 32
E 12
}

I 52
struct {
	int flag;
	char val;
} ttystates[] = {
D 76
	TS_WOPEN,	'W',
	TS_ISOPEN,	'O',
	TS_CARR_ON,	'C',
	TS_TIMEOUT,	'T',
	TS_FLUSH,	'F',
	TS_BUSY,	'B',
	TS_ASLEEP,	'A',
	TS_XCLUDE,	'X',
	TS_TTSTOP,	'S',
D 68
	TS_HUPCLS,	'H',
E 68
	TS_TBLOCK,	'K',
D 73
	TS_RCOLL,	'R',
	TS_WCOLL,	'I',	/* running short on letters ! */
E 73
	TS_ASYNC,	'Y',
	TS_BKSL,	'D',
	TS_ERASE,	'E',
	TS_LNCH,	'L',
	TS_TYPEN,	'P',
	TS_CNTTB,	'N',
	0,	0
E 76
I 76
	{ TS_WOPEN,	'W'},
	{ TS_ISOPEN,	'O'},
	{ TS_CARR_ON,	'C'},
	{ TS_TIMEOUT,	'T'},
	{ TS_FLUSH,	'F'},
	{ TS_BUSY,	'B'},
	{ TS_ASLEEP,	'A'},
	{ TS_XCLUDE,	'X'},
	{ TS_TTSTOP,	'S'},
	{ TS_TBLOCK,	'K'},
	{ TS_ASYNC,	'Y'},
	{ TS_BKSL,	'D'},
	{ TS_ERASE,	'E'},
	{ TS_LNCH,	'L'},
	{ TS_TYPEN,	'P'},
	{ TS_CNTTB,	'N'},
	{ 0,	       '\0'},
E 76
};

E 52
D 76
ttyprt(atp, line)
D 75
struct tty *atp;
E 75
I 75
	struct tty *atp;
E 75
{
E 76
I 76
void
ttyprt(tp, line)
E 76
D 86
	register struct tty *tp;
E 86
I 86
	struct tty *tp;
E 86
I 52
D 76
	char state[20];
	register i, j;
I 58
	char *name;
E 76
I 76
	int line;
{
D 86
	register int i, j;
E 86
I 86
	int i, j;
E 86
E 76
D 75
	extern char *devname();
E 75
	pid_t pgid;
I 76
	char *name, state[20];
E 76
E 58
E 52

D 52
	printf("%2d", line);
E 52
D 76
	tp = atp;
E 76
I 52
D 58
	printf("%2d %2d/%-2d ", line, major(tp->t_dev), minor(tp->t_dev));
E 52
	switch (tp->t_line) {

I 12
D 42
/*
E 42
I 42
D 55
#ifdef notdef
E 55
I 55
#ifdef BERKNET_WAS_A_LONG_TIME_AGO
E 55
E 42
E 12
	case NETLDISC:
		if (tp->t_rec)
			printf("%4d%4d", 0, tp->t_inbuf);
		else
			printf("%4d%4d", tp->t_inbuf, 0);
		break;
I 12
D 42
*/
E 42
I 42
#endif
E 42
E 12

	default:
D 30
		printf("%4d", tp->t_rawq.c_cc);
		printf("%4d", tp->t_canq.c_cc);
E 30
I 30
D 52
		printf("%4d%4d", tp->t_rawq.c_cc, tp->t_canq.c_cc);
E 52
I 52
		printf("%2d %3d ", tp->t_rawq.c_cc, tp->t_canq.c_cc);
E 52
E 30
	}
E 58
I 58
D 66
	if (nflg || tp->t_dev == 0 || 	/* XXX */
E 66
I 66
D 75
	if (nflg || tp->t_dev == 0 ||
E 75
I 75
	if (usenumflag || tp->t_dev == 0 ||
E 75
E 66
	   (name = devname(tp->t_dev, S_IFCHR)) == NULL)
D 76
		printf("%7d ", line); 
E 76
I 76
		(void)printf("%7d ", line); 
E 76
	else
D 76
		printf("%7s ", name);
	printf("%2d %3d ", tp->t_rawq.c_cc, tp->t_canq.c_cc);
E 58
D 30
	printf("%4d", tp->t_outq.c_cc);
D 19
	printf("%8.1o", tp->t_flags);
E 19
I 19
D 21
	printf("%8.1x", tp->t_flags);
E 21
I 21
D 22
	printf(" %8.1x", tp->t_flags);
E 22
I 22
	printf("%8.1x", tp->t_flags);
E 22
E 21
E 19
	printf(" %8.1x", tp->t_addr);
D 21
	printf("%3d", tp->t_delct);
E 21
I 21
D 22
	printf(" %3d", tp->t_delct);
E 22
I 22
	printf("%3d", tp->t_delct);
E 22
E 21
	printf("%4d ", tp->t_col);
E 30
I 30
D 52
	printf("%4d %8x %8x%4d%4d", tp->t_outq.c_cc, tp->t_flags,
		tp->t_addr, tp->t_delct, tp->t_col);
E 30
D 12
	putf(tp->t_state&TIMEOUT, 'T');
	putf(tp->t_state&WOPEN, 'W');
	putf(tp->t_state&ISOPEN, 'O');
	putf(tp->t_state&CARR_ON, 'C');
	putf(tp->t_state&BUSY, 'B');
	putf(tp->t_state&ASLEEP, 'A');
	putf(tp->t_state&XCLUDE, 'X');
E 12
I 12
	putf(tp->t_state&TS_TIMEOUT, 'T');
	putf(tp->t_state&TS_WOPEN, 'W');
	putf(tp->t_state&TS_ISOPEN, 'O');
I 30
	putf(tp->t_state&TS_FLUSH, 'F');
E 30
	putf(tp->t_state&TS_CARR_ON, 'C');
	putf(tp->t_state&TS_BUSY, 'B');
	putf(tp->t_state&TS_ASLEEP, 'A');
	putf(tp->t_state&TS_XCLUDE, 'X');
I 30
	putf(tp->t_state&TS_TTSTOP, 'S');
E 30
E 12
D 19
/*
E 19
D 12
	putf(tp->t_state&HUPCLS, 'H');
E 12
I 12
	putf(tp->t_state&TS_HUPCLS, 'H');
E 12
D 19
 */
E 19
	printf("%6d", tp->t_pgrp);
E 52
I 52
D 61
	printf("%3d %6d %6d %6d %4d %3d %8x %3d ", tp->t_outq.c_cc, 
		tp->t_rawcc, tp->t_cancc, tp->t_outcc, 
E 61
I 61
	printf("%3d %4d %3d %8x %3d ", tp->t_outq.c_cc, 
E 76
I 76
		(void)printf("%7s ", name);
	(void)printf("%2d %3d ", tp->t_rawq.c_cc, tp->t_canq.c_cc);
D 78
	(void)printf("%3d %4d %3d %8x %3d ", tp->t_outq.c_cc, 
E 76
E 61
		tp->t_hiwat, tp->t_lowat, tp->t_addr, tp->t_col);
E 78
I 78
D 90
	(void)printf("%3d %4d %3d %3d ", tp->t_outq.c_cc, 
E 90
I 90
	(void)printf("%3d %4d %3d %7d ", tp->t_outq.c_cc, 
E 90
		tp->t_hiwat, tp->t_lowat, tp->t_column);
E 78
	for (i = j = 0; ttystates[i].flag; i++)
		if (tp->t_state&ttystates[i].flag)
			state[j++] = ttystates[i].val;
I 61
	if (j == 0)
		state[j++] = '-';
E 61
	state[j] = '\0';
D 57
	printf("%-5s ", state);
	printf("%5d ", tp->t_pgid);
E 57
I 57
D 61
	printf("%-4s ", state);
E 61
I 61
D 76
	printf("%-4s %6x", state, (u_long)tp->t_session & ~KERNBASE);
E 76
I 76
D 90
	(void)printf("%-4s %6x", state, (u_long)tp->t_session & ~KERNBASE);
E 90
I 90
	(void)printf("%-6s %8x", state, (u_long)tp->t_session);
E 90
E 76
E 61
D 58
	printf("%6x ", clear(tp->t_pgrp));
E 58
I 58
D 73
	if (tp->t_pgrp == NULL || kvm_read(&tp->t_pgrp->pg_id, &pgid, 
E 73
I 73
D 75
	if (tp->t_pgrp == NULL || kvm_read(kd, V(&tp->t_pgrp->pg_id), &pgid, 
E 73
	    sizeof (pid_t)) != sizeof (pid_t))
		pgid = 0;
E 75
I 75
	pgid = 0;
	if (tp->t_pgrp != NULL)
D 76
		KGET2(&tp->t_pgrp->pg_id, &pgid, sizeof (pid_t), "pgid");
E 75
	printf("%6d ", pgid);
E 76
I 76
		KGET2(&tp->t_pgrp->pg_id, &pgid, sizeof(pid_t), "pgid");
	(void)printf("%6d ", pgid);
E 76
E 58
E 57
E 52
	switch (tp->t_line) {
D 76

E 76
I 30
D 52
	case OTTYDISC:
		printf("\n");
E 52
I 52
D 61
	case 0:
E 61
I 61
	case TTYDISC:
E 61
D 76
		printf("term\n");
E 76
I 76
		(void)printf("term\n");
E 76
E 52
		break;
D 58

I 55
#ifdef BERKNET_WAS_A_LONG_TIME_AGO
E 55
E 30
D 52
	case NTTYDISC:
D 30
		printf(" ntty");
E 30
I 30
		printf(" ntty\n");
E 30
		break;

E 52
	case NETLDISC:
D 30
		printf(" net");
E 30
I 30
D 39
		printf(" net\n");
E 39
I 39
D 52
		printf(" berknet\n");
E 52
I 52
		printf("berknet\n");
E 52
E 39
E 30
		break;
I 55
#endif
E 58
E 55
I 30
D 76

E 76
	case TABLDISC:
D 52
		printf(" tab\n");
E 52
I 52
D 76
		printf("tab\n");
E 76
I 76
		(void)printf("tab\n");
E 76
E 52
D 39
		break;

	case NTABLDISC:
		printf(" ntab\n");
E 39
		break;
D 76

E 76
I 47
	case SLIPDISC:
D 52
		printf(" slip\n");
E 52
I 52
D 76
		printf("slip\n");
E 76
I 76
		(void)printf("slip\n");
E 76
E 52
		break;
D 76

E 76
E 47
	default:
D 52
		printf(" %d\n", tp->t_line);
E 52
I 52
D 76
		printf("%d\n", tp->t_line);
E 76
I 76
		(void)printf("%d\n", tp->t_line);
		break;
E 76
E 52
E 30
	}
D 30
	printf("\n");
E 30
}

I 63
D 75
/*
 * The user structure is going away.  What's left here won't
 * be around for long.
 */
E 63
dousr()
{
I 64
D 73
#ifdef NEWVM
	printf("nothing left in user structure in this system\n");
#else
E 64
D 59
	struct user U;
E 59
I 59
D 60
#ifdef notyet
E 60
	register struct user *up;
E 59
	register i, j, *ip;
I 29
D 60
	register struct nameidata *nd = &U.u_nd;
E 60
I 60
	register struct nameidata *nd;
E 60
I 59
	struct proc *p;
I 60
	int ret;
E 73
E 60
E 59
E 29

D 33
	/* This wins only if PAGSIZ > sizeof (struct user) */
	lseek(fc, ubase * NBPG, 0);
	read(fc, &U, sizeof(U));
E 33
I 33
D 60
	/* This wins only if CLBYTES >= sizeof (struct user) */
D 57
	lseek(fm, ubase * NBPG, 0);
	read(fm, &U, sizeof(U));
E 57
I 57
	/* (WHICH IT ISN'T, but u. is going away - so who cares */
D 59
	kvm_read(ubase * NBPG, &U, sizeof(U));
E 59
I 59
	if (kvm_getprocs(KINFO_PROC_PID, upid) != 0) {
		error("kvm_getproc: %s", kvm_geterr());
E 60
I 60
D 73
	if ((ret = kvm_getprocs(KINFO_PROC_PID, upid)) != 1) {
		if (ret == -1)
			error("kvm_getproc: %s", kvm_geterr());
		else
			error("can't locate process %d", upid);
E 60
		return (1);
	}
D 60
	if ((p = kvm_nextproc()); == NULL) {
E 60
I 60
	if ((p = kvm_nextproc()) == NULL) {
E 60
		error("kvm_nextproc: %s", kvm_geterr());
		return (1);
	}
D 60
	if (up = kvm_getu(p)) == NULL) {
E 60
I 60
	if ((up = kvm_getu(p)) == NULL) {
E 60
		error("kvm_getu: %s", kvm_geterr());
		return (1);
	}
I 60
	nd = &up->u_nd;
E 60
E 59
E 57
E 33
	printf("pcb");
D 59
	ip = (int *)&U.u_pcb;
	while (ip < &U.u_arg[0]) {
		if ((ip - (int *)&U.u_pcb) % 4 == 0)
E 59
I 59
	ip = (int *)&up->u_pcb;
D 60
	while (ip < &up->u_arg[0]) {
		if ((ip - (int *)&up->u_pcb) % 4 == 0)
E 59
			printf("\t");
		printf("%x ", *ip++);
D 59
		if ((ip - (int *)&U.u_pcb) % 4 == 0)
E 59
I 59
		if ((ip - (int *)&up->u_pcb) % 4 == 0)
E 59
			printf("\n");
E 60
I 60
	i = 0;
	while (ip < (int *)((char *)&up->u_pcb + sizeof (struct pcb))) {
		if (i%4 == 0)
			putchar('\t');
		printf("%#10x ", *ip++);
		if (i%4 == 3)
			putchar('\n');
		i++;
E 60
	}
D 59
	if ((ip - (int *)&U.u_pcb) % 4 != 0)
E 59
I 59
D 60
	if ((ip - (int *)&up->u_pcb) % 4 != 0)
E 59
		printf("\n");
D 33
	printf("arg\t");
	for (i=0; i<5; i++)
		printf(" %.1x", U.u_arg[i]);
	printf("\n");
	for (i=0; i<sizeof(label_t)/sizeof(int); i++) {
E 33
I 33
	printf("arg");
D 59
	for (i=0; i<sizeof(U.u_arg)/sizeof(U.u_arg[0]); i++) {
E 59
I 59
	for (i=0; i<sizeof(up->u_arg)/sizeof(up->u_arg[0]); i++) {
E 60
I 60
	if (i%4)
		putchar('\n');
	printf("procp\t%#x\n", up->u_procp);
	printf("ar0\t%#x\n", up->u_ar0);
	printf("sizes\ttext %d data %d stack %d\n", 
		up->u_tsize, up->u_dsize, up->u_ssize);
D 63
	/* DMAPS */
E 63
	printf("ssave");
	for (i=0; i<sizeof(label_t)/sizeof(int); i++) {
E 60
E 59
E 33
		if (i%5==0)
			printf("\t");
D 19
		printf("%9.1x", U.u_ssav[i]);
E 19
I 19
D 33
		printf("%9.1x", U.u_ssave.val[i]);
E 33
I 33
D 59
		printf(" %.1x", U.u_arg[i]);
E 59
I 59
D 60
		printf(" %.1x", up->u_arg[i]);
E 60
I 60
		printf("%#11x", up->u_ssave.val[i]);
E 60
E 59
E 33
E 19
		if (i%5==4)
			printf("\n");
	}
	if (i%5)
		printf("\n");
D 29
	printf("segflg\t%d\nerror %d\n", U.u_segflg, U.u_error);
E 29
I 29
D 59
	printf("segflg\t%d\nerror %d\n", nd->ni_segflg, U.u_error);
E 29
	printf("uids\t%d,%d,%d,%d\n", U.u_uid,U.u_gid,U.u_ruid,U.u_rgid);
	printf("procp\t%.1x\n", U.u_procp);
	printf("ap\t%.1x\n", U.u_ap);
	printf("r_val?\t%.1x %.1x\n", U.u_r.r_val1, U.u_r.r_val2);
E 59
I 59
D 60
	printf("segflg\t%d\nerror %d\n", nd->ni_segflg, up->u_error);
	printf("uids\t%d,%d,%d,%d\n", up->u_uid,up->u_gid,up->u_ruid,up->u_rgid);
	printf("procp\t%.1x\n", up->u_procp);
	printf("ap\t%.1x\n", up->u_ap);
	printf("r_val?\t%.1x %.1x\n", up->u_r.r_val1, up->u_r.r_val2);
E 59
D 29
	printf("base, count, offset %.1x %.1x %ld\n", U.u_base,
		U.u_count, U.u_offset);
E 29
I 29
	printf("base, count, offset %.1x %.1x %ld\n", nd->ni_base,
		nd->ni_count, nd->ni_offset);
E 29
D 59
	printf("cdir rdir %.1x %.1x\n", U.u_cdir, U.u_rdir);
E 59
I 59
	printf("cdir rdir %.1x %.1x\n", up->u_cdir, up->u_rdir);
E 59
D 15
	printf("dbuf %.14s\n", U.u_dbuf);
E 15
D 29
	printf("dirp %.1x\n", U.u_dirp);
	printf("dent %d %.14s\n", U.u_dent.d_ino, U.u_dent.d_name);
	printf("pdir %.1o\n", U.u_pdir);
E 29
I 29
	printf("dirp %.1x\n", nd->ni_dirp);
	printf("dent %d %.14s\n", nd->ni_dent.d_ino, nd->ni_dent.d_name);
D 54
	printf("pdir %.1o\n", nd->ni_pdir);
E 54
I 54
	printf("dvp vp %.1x %.1x\n", nd->ni_dvp, nd->ni_vp);
E 54
E 29
D 33
	printf("file\t");
	for (i=0; i<10; i++)
E 33
I 33
	printf("file");
	for (i=0; i<NOFILE; i++) {
E 60
I 60
	printf("odsize\t%#x\n", up->u_odsize);
	printf("ossize\t%#x\n", up->u_ossize);
	printf("outime\t%d\n", up->u_outime);
	printf("mmap\t%#x\n", up->u_mmap);
	printf("sigs");
	for (i=0; i<NSIG; i++) {
E 60
		if (i % 8 == 0)
			printf("\t");
E 33
D 59
		printf("%9.1x", U.u_ofile[i]);
E 59
I 59
D 60
		printf("%9.1x", up->u_ofile[i]);
E 60
I 60
		printf("%#x ", up->u_signal[i]);
E 60
E 59
D 33
	printf("\n\t");
	for (i=10; i<NOFILE; i++)
		printf("%9.1x", U.u_ofile[i]);
	printf("\n");
	printf("pofile\t");
	for (i=0; i<10; i++)
E 33
I 33
		if (i % 8 == 7)
			printf("\n");
	}
	if (i % 8)
		printf("\n");
D 60
	printf("pofile");
	for (i=0; i<NOFILE; i++) {
E 60
I 60
	printf("sigmask");
	for (i=0; i<NSIG; i++) {
E 60
		if (i % 8 == 0)
			printf("\t");
E 33
D 59
		printf("%9.1x", U.u_pofile[i]);
E 59
I 59
D 60
		printf("%9.1x", up->u_pofile[i]);
E 60
I 60
		printf("%#x ", up->u_sigmask[i]);
E 60
E 59
D 33
	printf("\n\t");
	for (i=10; i<NOFILE; i++)
		printf("%9.1x", U.u_pofile[i]);
	printf("\n");
E 33
I 33
		if (i % 8 == 7)
			printf("\n");
	}
	if (i % 8)
		printf("\n");
E 33
D 19
	printf("ssav");
E 19
I 19
D 60
	printf("ssave");
E 19
	for (i=0; i<sizeof(label_t)/sizeof(int); i++) {
		if (i%5==0)
E 60
I 60
	printf("sigonstack\t%#x\n", up->u_sigonstack);
	printf("sigintr\t%#x\n", up->u_sigintr);
	printf("oldmask\t%#x\n", up->u_oldmask);
	printf("sigstack\t%#x %#x\n", 
		up->u_sigstack.ss_sp, up->u_sigstack.ss_onstack);
	printf("sig\t%#x\n", up->u_sig);
	printf("code\t%#x\n", up->u_code);
D 63
	printf("file");
	for (i=0; i<NOFILE; i++) {
		if (i % 6 == 0)
E 60
			printf("\t");
D 19
		printf("%9.1x", U.u_ssav[i]);
E 19
I 19
D 59
		printf("%9.1x", U.u_ssave.val[i]);
E 59
I 59
D 60
		printf("%9.1x", up->u_ssave.val[i]);
E 59
E 19
		if (i%5==4)
E 60
I 60
		printf("%#11x", up->u_ofile[i]);
		if (i % 6 == 5)
E 60
			printf("\n");
	}
D 60
	if (i%5)
E 60
I 60
	if (i % 6)
E 60
		printf("\n");
D 33
	printf("sigs\t");
	for (i=0; i<NSIG; i++)
E 33
I 33
D 60
	printf("sigs");
	for (i=0; i<NSIG; i++) {
		if (i % 8 == 0)
E 60
I 60
	printf("pofile");
	for (i=0; i<NOFILE; i++) {
		if (i % 6 == 0)
E 60
			printf("\t");
E 33
D 59
		printf("%.1x ", U.u_signal[i]);
E 59
I 59
D 60
		printf("%.1x ", up->u_signal[i]);
E 59
D 33
	printf("\n");
E 33
I 33
		if (i % 8 == 7)
E 60
I 60
		printf("%#11x", up->u_pofile[i]);
		if (i % 6 == 5)
E 60
			printf("\n");
	}
D 60
	if (i % 8)
E 60
I 60
	if (i % 6)
E 60
		printf("\n");
E 33
D 6
	printf("cfcode\t%.1x\n", U.u_cfcode);
E 6
I 6
D 59
	printf("code\t%.1x\n", U.u_code);
E 6
	printf("ar0\t%.1x\n", U.u_ar0);
D 45
	printf("prof\t%X %X %X %X\n", U.u_prof.pr_base, U.u_prof.pr_size,
E 45
I 45
	printf("prof\t%x %x %x %x\n", U.u_prof.pr_base, U.u_prof.pr_size,
E 45
	    U.u_prof.pr_off, U.u_prof.pr_scale);
D 57
	printf("\neosys\t%d\n", U.u_eosys);
D 19
	printf("sep\t%d\n", U.u_sep);
E 19
	printf("ttyp\t%.1x\n", U.u_ttyp);
	printf("ttyd\t%d,%d\n", major(U.u_ttyd), minor(U.u_ttyd));
D 29
	printf("exdata\t");
	ip = (int *)&U.u_exdata;
	for (i = 0; i < 8; i++)
		printf("%.1D ", *ip++);
	printf("\n");
E 29
	printf("comm %.14s\n", U.u_comm);
I 54
	printf("logname %.12s\n", U.u_logname);
E 57
E 54
D 45
	printf("start\t%D\n", U.u_start);
	printf("acflag\t%D\n", U.u_acflag);
D 19
	printf("fpflag\t%D\n", U.u_fpflag);
E 19
	printf("cmask\t%D\n", U.u_cmask);
E 45
I 45
	printf("start\t%ld\n", U.u_start.tv_sec);
	printf("acflag\t%ld\n", U.u_acflag);
	printf("cmask\t%ld\n", U.u_cmask);
E 45
	printf("sizes\t%.1x %.1x %.1x\n", U.u_tsize, U.u_dsize, U.u_ssize);
E 59
I 59
D 60
	printf("code\t%.1x\n", up->u_code);
	printf("ar0\t%.1x\n", up->u_ar0);
	printf("prof\t%x %x %x %x\n", up->u_prof.pr_base, up->u_prof.pr_size,
E 60
I 60
	printf("lastfile\t%d\n", up->u_lastfile);
	printf("cmask\t%#o\n", up->u_cmask);
	/* RUSAGES */
	/* TIMERS */
E 63
	printf("start\t%ld secs %ld usecs\n", 
		up->u_start.tv_sec, up->u_start.tv_usec);
	printf("acflag\t%#x\n", up->u_acflag);
	printf("prof\t%#x %#x %#x %#x\n", up->u_prof.pr_base, up->u_prof.pr_size,
E 60
	    up->u_prof.pr_off, up->u_prof.pr_scale);
D 60
	printf("start\t%ld\n", up->u_start.tv_sec);
	printf("acflag\t%ld\n", up->u_acflag);
	printf("cmask\t%ld\n", up->u_cmask);
	printf("sizes\t%.1x %.1x %.1x\n", up->u_tsize, up->u_dsize, up->u_ssize);
E 60
E 59
D 19
	printf("vm\t");
	ip = (int *)&U.u_vm;
	for (i = 0; i < sizeof(U.u_vm)/sizeof(int); i++)
E 19
I 19
	printf("ru\t");
D 59
	ip = (int *)&U.u_ru;
	for (i = 0; i < sizeof(U.u_ru)/sizeof(int); i++)
E 59
I 59
	ip = (int *)&up->u_ru;
	for (i = 0; i < sizeof(up->u_ru)/sizeof(int); i++)
E 59
E 19
D 45
		printf("%D ", ip[i]);
E 45
I 45
		printf("%ld ", ip[i]);
E 45
	printf("\n");
D 19
	ip = (int *)&U.u_cvm;
	printf("cvm\t");
	for (i = 0; i < sizeof(U.u_vm)/sizeof(int); i++)
E 19
I 19
D 59
	ip = (int *)&U.u_cru;
E 59
I 59
	ip = (int *)&up->u_cru;
E 59
	printf("cru\t");
D 59
	for (i = 0; i < sizeof(U.u_cru)/sizeof(int); i++)
E 59
I 59
	for (i = 0; i < sizeof(up->u_cru)/sizeof(int); i++)
E 59
E 19
D 45
		printf("%D ", ip[i]);
E 45
I 45
		printf("%ld ", ip[i]);
E 45
	printf("\n");
I 64
#endif
E 73
I 73
	printf("nothing left in user structure in this system\n");
E 73
E 64
D 42
/*
E 42
I 42
D 60
#ifdef notdef
E 42
D 59
	i =  U.u_stack - &U;
E 59
I 59
	i =  up->u_stack - &U;
E 59
	while (U[++i] == 0);
	i &= ~07;
	while (i < 512) {
		printf("%x ", 0140000+2*i);
		for (j=0; j<8; j++)
			printf("%9x", U[i++]);
		printf("\n");
	}
I 59
#endif
E 59
D 42
*/
E 42
I 42
#endif
E 60
I 60
D 63
	/* NAMEI */
E 63
E 60
E 42
}

oatoi(s)
char *s;
{
	register v;

	v = 0;
	while (*s)
		v = (v<<3) + *s++ - '0';
	return(v);
}

E 75
D 5
dofil()
E 5
I 5
D 76
dofile()
E 76
I 76
void
filemode()
E 76
E 5
{
D 5
	struct file xfile[NFILE];
E 5
I 5
D 69
	int nfile;
	struct file *xfile, *afile;
E 69
E 5
D 86
	register struct file *fp;
E 86
I 86
	struct file *fp;
E 86
D 69
	register nf;
	int loc;
E 69
I 69
	struct file *addr;
D 75
	char *buf;
E 75
I 75
	char *buf, flagbuf[16], *fbp;
E 75
	int len, maxfile, nfile;
D 75
	struct nlist fnl[] = {
#define	FNL_NFILE	0
		{"_nfiles"},
#define FNL_MAXFILE	1
		{"_maxfiles"},
		{""}
	};
E 75
E 69
I 18
D 23
	static char *dtypes[] = {
		"???", "kernel", "fsys", "file", "dir", "bdev",
		"cdev", "proc", "socket", "domain", "tty"
	};
E 23
I 23
	static char *dtypes[] = { "???", "inode", "socket" };
E 23
E 18

D 69
	nf = 0;
D 5
	lseek(fc, (long)nl[SFIL].n_value, 0);
	read(fc, xfile, sizeof(xfile));
	for (fp=xfile; fp < &xfile[NFILE]; fp++)
E 5
I 5
D 48
	nfile = getw(nl[SNFILE].n_value);
E 48
I 48
	nfile = getword(nl[SNFILE].n_value);
E 48
	xfile = (struct file *)calloc(nfile, sizeof (struct file));
D 35
	lseek(fc, (int)(afile = (struct file *)getw(nl[SFIL].n_value)), 0);
E 35
I 35
D 48
	afile = (struct file *)getw(nl[SFIL].n_value);
E 48
I 48
	afile = (struct file *)getword(nl[SFIL].n_value);
E 48
D 40
	lseek(fc, (mkphys((int)afile)), 0);
E 40
I 40
D 60
	if (nfile < 0 || nfile > 10000) {
E 60
I 60
	if (nfile < 0 || nfile > 100000) {
E 60
		fprintf(stderr, "number of files is preposterous (%d)\n",
			nfile);
E 69
I 69
D 73
	if (kvm_nlist(fnl) != 0) {
E 73
I 73
D 75
	if (kvm_nlist(kd, fnl) != 0) {
E 73
		error("kvm_nlist: no _nfiles or _maxfiles: %s", 
D 73
			kvm_geterr());
E 73
I 73
			kvm_geterr(kd));
E 73
E 69
		return;
	}
D 69
	if (xfile == NULL) {
		fprintf(stderr, "can't allocate memory for file table\n");
		return;
	}
D 57
	lseek(fc, mkphys((off_t)afile), 0);
E 40
E 35
	read(fc, xfile, nfile * sizeof (struct file));
E 57
I 57
	kvm_read(afile, xfile, nfile * sizeof (struct file));
E 57
	for (fp=xfile; fp < &xfile[nfile]; fp++)
E 5
		if (fp->f_count)
			nf++;
E 69
I 69
D 73
	kvm_read(V(fnl[FNL_MAXFILE].n_value), &maxfile,
E 73
I 73
	kvm_read(kd, V(fnl[FNL_MAXFILE].n_value), &maxfile,
E 73
		sizeof (maxfile));
E 69
	if (totflg) {
D 5
		printf("%3d/%3d files\n", nf, NFILE);
E 5
I 5
D 69
		printf("%3d/%3d files\n", nf, nfile);
E 69
I 69
D 73
		kvm_read(V(fnl[FNL_NFILE].n_value), &nfile, sizeof (nfile));
E 73
I 73
		kvm_read(kd, V(fnl[FNL_NFILE].n_value), &nfile, sizeof (nfile));
E 75
I 75
	KGET(FNL_MAXFILE, maxfile);
	if (totalflag) {
		KGET(FNL_NFILE, nfile);
E 75
E 73
D 76
		printf("%3d/%3d files\n", nfile, maxfile);
E 76
I 76
		(void)printf("%3d/%3d files\n", nfile, maxfile);
E 76
E 69
E 5
		return;
	}
D 5
	printf("%d/%d open files\n", nf, NFILE);
E 5
I 5
D 69
	printf("%d/%d open files\n", nf, nfile);
E 69
I 69
	if (getfiles(&buf, &len) == -1)
		return;
	/*
D 76
	 * getfiles returns in malloc'd buf a pointer to the first file
	 * structure, and then an array of file structs (whose
	 * addresses are derivable from the previous entry)
E 76
I 76
	 * Getfiles returns in malloc'd memory a pointer to the first file
	 * structure, and then an array of file structs (whose addresses are
	 * derivable from the previous entry).
E 76
	 */
D 88
	addr = *((struct file **)buf);
D 76
	fp = (struct file *)(buf + sizeof (struct file *));
	nfile = (len - sizeof (struct file *)) / sizeof (struct file);
E 76
I 76
	fp = (struct file *)(buf + sizeof(struct file *));
	nfile = (len - sizeof(struct file *)) / sizeof(struct file);
E 88
I 88
	addr = ((struct filelist *)buf)->lh_first;
	fp = (struct file *)(buf + sizeof(struct filelist));
	nfile = (len - sizeof(struct filelist)) / sizeof(struct file);
E 88
E 76
	
D 76
	printf("%d/%d open files\n", nfile, maxfile);
E 69
E 5
D 12
	printf("   LOC   FLG  CNT   INO    OFFS\n");
E 12
I 12
D 18
	printf("   LOC   FLG  CNT   INO    OFFS|SOCK\n");
E 18
I 18
D 23
	printf("   LOC   TYPE    FLG  CNT   INO    OFFS|SOCK\n");
E 23
I 23
D 24
	printf("   LOC   TYPE    FLG  CNT  MSG    DATA    OFFSET\n");
E 24
I 24
	printf("   LOC   TYPE    FLG     CNT  MSG    DATA    OFFSET\n");
E 76
I 76
	(void)printf("%d/%d open files\n", nfile, maxfile);
	(void)printf("   LOC   TYPE    FLG     CNT  MSG    DATA    OFFSET\n");
E 76
E 24
E 23
E 18
E 12
D 5
	for (fp=xfile,loc=nl[SFIL].n_value; fp < &xfile[NFILE]; fp++,loc+=sizeof(xfile[0])) {
E 5
I 5
D 16
	for (fp=xfile,loc=nl[SFIL].n_value; fp < &xfile[nfile]; fp++,loc+=sizeof(xfile[0])) {
E 16
I 16
D 69
	for (fp=xfile,loc=(int)afile; fp < &xfile[nfile]; fp++,loc+=sizeof(xfile[0])) {
E 16
E 5
		if (fp->f_count==0)
			continue;
D 60
		printf("%8x ", loc);
E 60
I 60
		printf("%x ", loc);
E 69
I 69
D 88
	for (; (char *)fp < buf + len; addr = fp->f_filef, fp++) {
E 88
I 88
	for (; (char *)fp < buf + len; addr = fp->f_list.le_next, fp++) {
E 88
I 73
		if ((unsigned)fp->f_type > DTYPE_SOCKET)
			continue;
E 73
D 76
		printf("%x ", addr);
E 69
E 60
I 18
D 23
		if (fp->f_type <= DTYPE_TERMINAL)
E 23
I 23
D 73
		if (fp->f_type <= DTYPE_SOCKET)
E 23
			printf("%-8.8s", dtypes[fp->f_type]);
		else
D 44
			printf("8d", fp->f_type);
E 44
I 44
			printf("%8d", fp->f_type);
E 73
I 73
		printf("%-8.8s", dtypes[fp->f_type]);
E 76
I 76
		(void)printf("%x ", addr);
		(void)printf("%-8.8s", dtypes[fp->f_type]);
E 76
E 73
E 44
E 18
D 75
		putf(fp->f_flag&FREAD, 'R');
		putf(fp->f_flag&FWRITE, 'W');
D 12
		putf(fp->f_flag&FPIPE, 'P');
E 12
I 12
D 18
		putf(fp->f_flag&FSOCKET, 'S');
E 18
I 18
		putf(fp->f_flag&FAPPEND, 'A');
E 75
I 75
		fbp = flagbuf;
		if (fp->f_flag & FREAD)
			*fbp++ = 'R';
		if (fp->f_flag & FWRITE)
			*fbp++ = 'W';
		if (fp->f_flag & FAPPEND)
			*fbp++ = 'A';
E 75
I 68
#ifdef FSHLOCK	/* currently gone */
E 68
I 24
D 75
		putf(fp->f_flag&FSHLOCK, 'S');
		putf(fp->f_flag&FEXLOCK, 'X');
I 69
#else
		putf(0, ' ');
		putf(0, ' ');
E 75
I 75
		if (fp->f_flag & FSHLOCK)
			*fbp++ = 'S';
		if (fp->f_flag & FEXLOCK)
			*fbp++ = 'X';
E 75
E 69
I 68
#endif
E 68
D 75
		putf(fp->f_flag&FASYNC, 'I');
E 24
E 18
E 12
D 23
		printf("%4d", mask(fp->f_count));
		printf("%9.1x", fp->f_inode);
D 12
		printf("  %ld\n", fp->f_un.f_offset);
E 12
I 12
D 18
		if (fp->f_flag&FSOCKET)
E 18
I 18
		if (fp->f_type == DTYPE_SOCKET)
E 18
			printf("  %x\n", fp->f_socket);
E 23
I 23
D 69
		printf("  %3d", mask(fp->f_count));
		printf("  %3d", mask(fp->f_msgcount));
E 69
I 69
		printf("  %3d", fp->f_count);
E 75
I 75
		if (fp->f_flag & FASYNC)
			*fbp++ = 'I';
		*fbp = '\0';
D 76
		printf("%6s  %3d", flagbuf, fp->f_count);
E 75
		printf("  %3d", fp->f_msgcount);
E 69
		printf("  %8.1x", fp->f_data);
E 76
I 76
		(void)printf("%6s  %3d", flagbuf, fp->f_count);
		(void)printf("  %3d", fp->f_msgcount);
		(void)printf("  %8.1x", fp->f_data);
E 76
		if (fp->f_offset < 0)
D 75
			printf("  %x\n", fp->f_offset);
E 75
I 75
D 76
			printf("  %qx\n", fp->f_offset);
E 76
I 76
			(void)printf("  %qx\n", fp->f_offset);
E 76
E 75
E 23
		else
D 75
			printf("  %ld\n", fp->f_offset);
E 75
I 75
D 76
			printf("  %qd\n", fp->f_offset);
E 76
I 76
			(void)printf("  %qd\n", fp->f_offset);
E 76
E 75
E 12
	}
I 40
D 69
	free(xfile);
E 69
I 69
	free(buf);
E 69
E 40
}
I 69

I 76
int
E 76
getfiles(abuf, alen)
	char **abuf;
	int *alen;
{
D 76
	char *buf;
D 73
	int len;
E 73
I 73
	int mib[2];
E 76
	size_t len;
I 76
	int mib[2];
	char *buf;
E 76
E 73

D 71
	if (fcore != NULL) {
E 71
I 71
D 76
	if (memf != NULL) {
E 71
		/*
		 * add emulation of KINFO_FILE here
		 */
		error("files on dead kernel, not impl\n");
		exit(1);
	}
E 76
I 76
	/*
	 * XXX
	 * Add emulation of KINFO_FILE here.
	 */
	if (memf != NULL)
		errx(1, "files on dead kernel, not implemented\n");

E 76
D 73
	if ((len = getkerninfo(KINFO_FILE, NULL, NULL, 0)) == -1) {
		syserror("getkerninfo estimate");
E 73
I 73
	mib[0] = CTL_KERN;
	mib[1] = KERN_FILE;
	if (sysctl(mib, 2, NULL, &len, NULL, 0) == -1) {
D 76
		syserror("sysctl size estimate");
E 76
I 76
		warn("sysctl: KERN_FILE");
E 76
E 73
		return (-1);
	}
D 76
	if ((buf = (char *)malloc(len)) == NULL) {
		error("out of memory");
		return (-1);
	}
E 76
I 76
	if ((buf = malloc(len)) == NULL)
		err(1, NULL);
E 76
D 73
	if ((len = getkerninfo(KINFO_FILE, buf, &len, 0)) == -1) {
		syserror("getkerninfo");
E 73
I 73
	if (sysctl(mib, 2, buf, &len, NULL, 0) == -1) {
D 76
		syserror("sysctl");
E 76
I 76
		warn("sysctl: KERN_FILE");
E 76
E 73
		return (-1);
	}
	*abuf = buf;
	*alen = len;
	return (0);
}

E 69
D 75

E 75
I 75
/*
D 76
 * doswap is based on a program called swapinfo written
E 76
I 76
 * swapmode is based on a program called swapinfo written
E 76
 * by Kevin Lahey <kml@rokkaku.atl.ga.us>.
 */
E 75
I 64
D 73
#ifdef NEWVM
E 73
D 76
doswap()
E 76
I 76
void
swapmode()
E 76
{
D 75
	printf("swap statistics not yet supported in this system\n");
E 75
I 75
D 89
	char *header;
E 89
I 89
	char *header, *p;
E 89
D 79
	int hlen, nswap, nswdev, dmmax, nswapmap;
	int s, e, div, i, avail, nfree, npfree, used;
E 79
I 79
	int hlen, nswap, nswdev, dmmax, nswapmap, niswap, niswdev;
	int s, e, div, i, l, avail, nfree, npfree, used;
E 79
	struct swdevt *sw;
	long blocksize, *perdev;
	struct map *swapmap, *kswapmap;
	struct mapent *mp;

	KGET(VM_NSWAP, nswap);
	KGET(VM_NSWDEV, nswdev);
	KGET(VM_DMMAX, dmmax);
	KGET(VM_NSWAPMAP, nswapmap);
	KGET(VM_SWAPMAP, kswapmap);	/* kernel `swapmap' is a pointer */
D 76
	if ((sw = (struct swdevt *)malloc(nswdev * sizeof(*sw))) == NULL ||
	    (perdev = (long *)malloc(nswdev * sizeof(*perdev))) == NULL ||
	    (mp = (struct mapent *)malloc(nswapmap * sizeof(*mp))) == NULL)
E 76
I 76
	if ((sw = malloc(nswdev * sizeof(*sw))) == NULL ||
	    (perdev = malloc(nswdev * sizeof(*perdev))) == NULL ||
	    (mp = malloc(nswapmap * sizeof(*mp))) == NULL)
E 76
		err(1, "malloc");
	KGET1(VM_SWDEVT, sw, nswdev * sizeof(*sw), "swdevt");
	KGET2((long)kswapmap, mp, nswapmap * sizeof(*mp), "swapmap");

I 79
	/* Supports sequential swap */
	if (nl[VM_NISWAP].n_value != 0) {
		KGET(VM_NISWAP, niswap);
		KGET(VM_NISWDEV, niswdev);
	} else {
		niswap = nswap;
		niswdev = nswdev;
	}

E 79
D 76
	/* first entry in map is `struct map'; rest are mapent's */
E 76
I 76
	/* First entry in map is `struct map'; rest are mapent's. */
E 76
	swapmap = (struct map *)mp;
	if (nswapmap != swapmap->m_limit - (struct mapent *)kswapmap)
		errx(1, "panic: nswapmap goof");

D 76
	/*
	 * Count up swap space.
	 */
E 76
I 76
	/* Count up swap space. */
E 76
	nfree = 0;
D 76
	bzero(perdev, nswdev * sizeof(*perdev));
E 76
I 76
	memset(perdev, 0, nswdev * sizeof(*perdev));
E 76
	for (mp++; mp->m_addr != 0; mp++) {
		s = mp->m_addr;			/* start of swap region */
		e = mp->m_addr + mp->m_size;	/* end of region */
		nfree += mp->m_size;

		/*
		 * Swap space is split up among the configured disks.
D 79
		 * The first dmmax blocks of swap space some from the
		 * first disk, the next dmmax blocks from the next, 
		 * and so on.  The list of free space joins adjacent
		 * free blocks, ignoring device boundries.  If we want
		 * to keep track of this information per device, we'll
		 * just have to extract it ourselves.
E 79
I 79
		 *
		 * For interleaved swap devices, the first dmmax blocks
		 * of swap space some from the first disk, the next dmmax
		 * blocks from the next, and so on up to niswap blocks.
		 *
		 * Sequential swap devices follow the interleaved devices
		 * (i.e. blocks starting at niswap) in the order in which
		 * they appear in the swdev table.  The size of each device
		 * will be a multiple of dmmax.
		 *
		 * The list of free space joins adjacent free blocks,
		 * ignoring device boundries.  If we want to keep track
		 * of this information per device, we'll just have to
		 * extract it ourselves.  We know that dmmax-sized chunks
		 * cannot span device boundaries (interleaved or sequential)
		 * so we loop over such chunks assigning them to devices.
E 79
		 */
D 79

		/* calculate first device on which this falls */
		i = (s / dmmax) % nswdev;
E 79
I 79
		i = -1;
E 79
		while (s < e) {		/* XXX this is inefficient */
			int bound = roundup(s+1, dmmax);

			if (bound > e)
				bound = e;
D 79
			perdev[i] += bound - s;
			if (++i >= nswdev)
				i = 0;
E 79
I 79
			if (bound <= niswap) {
				/* Interleaved swap chunk. */
				if (i == -1)
					i = (s / dmmax) % niswdev;
				perdev[i] += bound - s;
				if (++i >= niswdev)
					i = 0;
			} else {
				/* Sequential swap chunk. */
				if (i < niswdev) {
					i = niswdev;
					l = niswap + sw[i].sw_nblks;
				}
				while (s >= l) {
					/* XXX don't die on bogus blocks */
					if (i == nswdev-1)
						break;
					l += sw[++i].sw_nblks;
				}
				perdev[i] += bound - s;
			}
E 79
			s = bound;
		}
	}

	header = getbsize(&hlen, &blocksize);
	if (!totalflag)
D 79
		(void)printf("%-10s %*s %10s %10s %10s\n",
		    "Device", hlen, header, "Used", "Available", "Capacity");
E 79
I 79
D 80
		(void)printf("%-10s %4s %*s %10s %10s %10s\n",
		    "Device", "Type", hlen, header,
		    "Used", "Available", "Capacity");
E 80
I 80
		(void)printf("%-11s %*s %8s %8s %8s  %s\n",
		    "Device", hlen, header,
		    "Used", "Avail", "Capacity", "Type");
E 80
E 79
	div = blocksize / 512;
	avail = npfree = 0;
	for (i = 0; i < nswdev; i++) {
		int xsize, xfree;

D 89
		if (!totalflag)
D 79
			(void)printf("/dev/%-5s %*d ",
E 79
I 79
D 80
			(void)printf("/dev/%-5s %4s %*d ",
E 80
I 80
			(void)printf("/dev/%-6s %*d ",
E 80
E 79
			    devname(sw[i].sw_dev, S_IFBLK),
E 89
I 89
		if (!totalflag) {
			p = devname(sw[i].sw_dev, S_IFBLK);
			(void)printf("/dev/%-6s %*d ", p == NULL ? "??" : p,
E 89
I 79
D 80
			    (sw[i].sw_flags & SW_SEQUENTIAL) ? "Seq" : "Int",
E 80
E 79
			    hlen, sw[i].sw_nblks / div);
I 89
		}
E 89

		/*
		 * Don't report statistics for partitions which have not
		 * yet been activated via swapon(8).
		 */
D 79
		if (!sw[i].sw_freed) {
E 79
I 79
		if (!(sw[i].sw_flags & SW_FREED)) {
E 79
			if (totalflag)
				continue;
			(void)printf(" *** not available for swapping ***\n");
			continue;
		}
		xsize = sw[i].sw_nblks;
		xfree = perdev[i];
		used = xsize - xfree;
		npfree++;
		avail += xsize;
		if (totalflag)
			continue;
D 79
		(void)printf("%10d %10d %7.0f%%\n", 
E 79
I 79
D 80
		(void)printf("%10d %10d %9.0f%%\n", 
E 80
I 80
		(void)printf("%8d %8d %5.0f%%    %s\n", 
E 80
E 79
		    used / div, xfree / div,
D 80
		    (double)used / (double)xsize * 100.0);
E 80
I 80
		    (double)used / (double)xsize * 100.0,
		    (sw[i].sw_flags & SW_SEQUENTIAL) ?
			     "Sequential" : "Interleaved");
E 80
	}

	/* 
	 * If only one partition has been set up via swapon(8), we don't
	 * need to bother with totals.
	 */
	used = avail - nfree;
	if (totalflag) {
D 76
		printf("%dM/%dM swap space\n", used / 2048, avail / 2048);
E 76
I 76
		(void)printf("%dM/%dM swap space\n", used / 2048, avail / 2048);
E 76
		return;
	}
	if (npfree > 1) {
D 79
		(void)printf("%-10s %*d %10d %10d %7.0f%%\n",
E 79
I 79
D 80
		(void)printf("%-10s      %*d %10d %10d %9.0f%%\n",
E 80
I 80
		(void)printf("%-11s %*d %8d %8d %5.0f%%\n",
E 80
E 79
		    "Total", hlen, avail / div, used / div, nfree / div,
		    (double)used / (double)avail * 100.0);
	}
E 75
}
D 73

#else /* NEWVM */
E 64
I 22
int dmmin, dmmax, nswdev;

E 22
doswap()
{
D 5
	struct proc proc[NPROC];
	struct text xtext[NTEXT];
	struct map swapmap[SMAPSIZ];
E 5
I 5
	struct proc *proc;
	int nproc;
	struct text *xtext;
	int ntext;
	struct map *swapmap;
	int nswapmap;
I 27
	struct swdevt *swdevt, *sw;
E 27
E 5
	register struct proc *pp;
D 22
	int nswap, used, tused, free;
E 22
I 22
	int nswap, used, tused, free, waste;
	int db, sb;
E 22
D 6
	register struct map *mp;
E 6
I 6
	register struct mapent *me;
E 6
	register struct text *xp;
I 22
	int i, j;
I 49
	long rmalloc();
E 49
E 22

D 5
	lseek(fc, (long)nl[SPROC].n_value, 0);
	read(fc, proc, sizeof(proc));
	lseek(fc, (long)nl[SWAPMAP].n_value, 0);
	read(fc, swapmap, sizeof(swapmap));
	lseek(fc, (long)nl[SNSWAP].n_value, 0);
	read(fc, &nswap, sizeof(nswap));
E 5
I 5
D 48
	nproc = getw(nl[SNPROC].n_value);
D 40
	proc = (struct proc *)calloc(nproc, sizeof (struct proc));
E 40
D 27
	lseek(fc, getw(nl[SPROC].n_value), 0);
	read(fc, proc, nproc * sizeof (struct proc));
E 27
I 27
	ntext = getw(nl[SNTEXT].n_value);
E 48
I 48
	nproc = getword(nl[SNPROC].n_value);
	ntext = getword(nl[SNTEXT].n_value);
E 48
I 40
	if (nproc < 0 || nproc > 10000 || ntext < 0 || ntext > 10000) {
		fprintf(stderr, "number of procs/texts is preposterous (%d, %d)\n",
			nproc, ntext);
		return;
	}
	proc = (struct proc *)calloc(nproc, sizeof (struct proc));
	if (proc == NULL) {
		fprintf(stderr, "can't allocate memory for proc table\n");
		exit(1);
	}
E 40
	xtext = (struct text *)calloc(ntext, sizeof (struct text));
I 40
	if (xtext == NULL) {
		fprintf(stderr, "can't allocate memory for text table\n");
		exit(1);
	}
E 40
E 27
D 48
	nswapmap = getw(nl[SNSWAPMAP].n_value);
E 48
I 48
	nswapmap = getword(nl[SNSWAPMAP].n_value);
E 48
	swapmap = (struct map *)calloc(nswapmap, sizeof (struct map));
I 40
	if (swapmap == NULL) {
		fprintf(stderr, "can't allocate memory for swapmap\n");
		exit(1);
	}
E 40
I 27
D 48
	nswdev = getw(nl[SNSWDEV].n_value);
E 48
I 48
	nswdev = getword(nl[SNSWDEV].n_value);
E 48
	swdevt = (struct swdevt *)calloc(nswdev, sizeof (struct swdevt));
D 40
	lseek(fc, nl[SSWDEVT].n_value, L_SET);
E 40
I 40
	if (swdevt == NULL) {
		fprintf(stderr, "can't allocate memory for swdevt table\n");
		exit(1);
	}
D 57
	lseek(fc, mkphys((off_t)nl[SSWDEVT].n_value), L_SET);
E 40
	read(fc, swdevt, nswdev * sizeof (struct swdevt));
D 40
	lseek(fc, getw(nl[SPROC].n_value), 0);
E 40
I 40
D 48
	lseek(fc, mkphys((off_t)getw(nl[SPROC].n_value)), 0);
E 48
I 48
	lseek(fc, mkphys((off_t)getword(nl[SPROC].n_value)), 0);
E 48
E 40
	read(fc, proc, nproc * sizeof (struct proc));
D 40
	lseek(fc, getw(nl[STEXT].n_value), 0);
E 40
I 40
D 48
	lseek(fc, mkphys((off_t)getw(nl[STEXT].n_value)), 0);
E 48
I 48
	lseek(fc, mkphys((off_t)getword(nl[STEXT].n_value)), 0);
E 48
E 40
	read(fc, xtext, ntext * sizeof (struct text));
E 27
D 40
	lseek(fc, getw(nl[SWAPMAP].n_value), 0);
E 40
I 40
D 48
	lseek(fc, mkphys((off_t)getw(nl[SWAPMAP].n_value)), 0);
E 48
I 48
	lseek(fc, mkphys((off_t)getword(nl[SWAPMAP].n_value)), 0);
E 48
E 40
	read(fc, swapmap, nswapmap * sizeof (struct map));
E 57
I 57
D 60
	kvm_read(nl[SSWDEVT].n_value, swdevt, nswdev * sizeof (struct swdevt));
	kvm_read(nl[SPROC].n_value, proc, nproc * sizeof (struct proc));
	kvm_read(nl[STEXT].n_value, xtext, ntext * sizeof (struct text));
	kvm_read(nl[SWAPMAP].n_value, swapmap, nswapmap * sizeof (struct map));
E 60
I 60
D 63
	kvm_read(nl[SSWDEVT].n_value, swdevt,
E 63
I 63
	kvm_read(V(nl[SSWDEVT].n_value), swdevt,
E 63
		nswdev * sizeof (struct swdevt));
D 63
	kvm_read(getword(nl[SPROC].n_value), proc,
E 63
I 63
	kvm_read(V(getword(nl[SPROC].n_value)), proc,
E 63
		nproc * sizeof (struct proc));
D 63
	kvm_read(getword(nl[STEXT].n_value), xtext,
E 63
I 63
	kvm_read(V(getword(nl[STEXT].n_value)), xtext,
E 63
		ntext * sizeof (struct text));
D 63
	kvm_read(getword(nl[SWAPMAP].n_value), swapmap,
E 63
I 63
	kvm_read(V(getword(nl[SWAPMAP].n_value)), swapmap,
E 63
		nswapmap * sizeof (struct map));
E 60

E 57
I 25
	swapmap->m_name = "swap";
I 26
	swapmap->m_limit = (struct mapent *)&swapmap[nswapmap];
E 26
E 25
D 27
	nswap = getw(nl[SNSWAP].n_value);
E 27
I 22
D 48
	dmmin = getw(nl[SDMMIN].n_value);
	dmmax = getw(nl[SDMMAX].n_value);
E 48
I 48
	dmmin = getword(nl[SDMMIN].n_value);
	dmmax = getword(nl[SDMMAX].n_value);
E 48
D 27
	nswdev = getw(nl[SNSWDEV].n_value);
E 27
I 27
	nswap = 0;
	for (sw = swdevt; sw < &swdevt[nswdev]; sw++)
D 41
		nswap += sw->sw_nblks,
E 41
I 41
		if (sw->sw_freed)
			nswap += sw->sw_nblks;
E 41
E 27
E 22
E 5
	free = 0;
D 5
	for (mp = swapmap; mp < &swapmap[SMAPSIZ]; mp++)
E 5
I 5
D 6
	for (mp = swapmap; mp < &swapmap[nswapmap]; mp++)
E 5
		free += mp->m_size;
E 6
I 6
	for (me = (struct mapent *)(swapmap+1);
	    me < (struct mapent *)&swapmap[nswapmap]; me++)
		free += me->m_size;
E 6
D 5
	lseek(fc, (long)nl[STEXT].n_value, 0);
	read(fc, xtext, sizeof(xtext));
E 5
I 5
D 27
	ntext = getw(nl[SNTEXT].n_value);
	xtext = (struct text *)calloc(ntext, sizeof (struct text));
	lseek(fc, getw(nl[STEXT].n_value), 0);
	read(fc, xtext, ntext * sizeof (struct text));
E 27
E 5
	tused = 0;
D 5
	for (xp = xtext; xp < &xtext[NTEXT]; xp++)
E 5
I 5
	for (xp = xtext; xp < &xtext[ntext]; xp++)
E 5
D 27
		if (xp->x_iptr!=NULL)
			tused += xdsize(xp);
E 27
I 27
D 54
		if (xp->x_iptr!=NULL) {
E 54
I 54
		if (xp->x_vptr!=NULL) {
E 54
D 31
			tused += ctod(xp->x_size);
E 31
I 31
			tused += ctod(clrnd(xp->x_size));
E 31
D 54
			if (xp->x_flag & XPAGI)
E 54
I 54
			if (xp->x_flag & XPAGV)
E 54
D 31
				tused += ctod(ctopt(xp->x_size));
E 31
I 31
				tused += ctod(clrnd(ctopt(xp->x_size)));
E 31
		}
E 27
	used = tused;
I 22
	waste = 0;
E 22
D 5
	for (pp = proc; pp < &proc[NPROC]; pp++) {
E 5
I 5
	for (pp = proc; pp < &proc[nproc]; pp++) {
E 5
		if (pp->p_stat == 0 || pp->p_stat == SZOMB)
			continue;
		if (pp->p_flag & SSYS)
			continue;
D 22
		used += up(pp->p_dsize) + up(pp->p_ssize);
E 22
I 22
D 27
		db = ctod(pp->p_dsize);
		sb = ctod(pp->p_ssize);
		waste -= db + sb;
		db = up(db);
		sb = up(sb);
		used += db + sb;
		waste += db + sb;
E 27
I 27
		db = ctod(pp->p_dsize), sb = up(db);
		used += sb;
		waste += sb - db;
		db = ctod(pp->p_ssize), sb = up(db);
		used += sb;
		waste += sb - db;
E 27
E 22
		if ((pp->p_flag&SLOAD) == 0)
D 32
			used += vusize(pp);
E 32
I 32
			used += ctod(vusize(pp));
E 32
	}
D 6
	/* a DMMAX block goes to argmap */
E 6
I 6
D 27
	/* a DMMAX/2 block goes to argmap */
E 27
E 6
	if (totflg) {
D 22
		printf("%3d/%3d 00k swap\n", used/2/100, (used+free)/2/100);
E 22
I 22
D 27
		printf("%3d/%3d 00k swap\n", used/100, (used+free)/100);
E 27
I 27
#define	btok(x)	((x) / (1024 / DEV_BSIZE))
		printf("%3d/%3d 00k swap\n",
		    btok(used/100), btok((used+free)/100));
E 27
E 22
		return;
	}
D 22
	printf("%d used (%d text), %d free, %d missing\n",
D 6
	    used/2, tused/2, free/2, (nswap - DMMAX - (used + free))/2);
E 6
I 6
	    used/2, tused/2, free/2, (nswap - DMMAX/2 - (used + free))/2);
E 22
I 22
D 27
	printf("%d used (%d text), %d free, %d wasted, %d missing\n",
	    used, tused, free, waste, (nswap - dmmax/2 - (used + free)));
E 27
I 27
	printf("%dk used (%dk text), %dk free, %dk wasted, %dk missing\n",
	    btok(used), btok(tused), btok(free), btok(waste),
/* a dmmax/2 block goes to argmap */
	    btok(nswap - dmmax/2 - (used + free)));
E 27
	printf("avail: ");
	for (i = dmmax; i >= dmmin; i /= 2) {
		j = 0;
		while (rmalloc(swapmap, i) != 0)
			j++;
D 27
		if (j) printf("%d*%d ", j, i);
E 27
I 27
		if (j) printf("%d*%dk ", j, btok(i));
E 27
	}
D 27
	printf("\n");
E 27
I 27
	free = 0;
	for (me = (struct mapent *)(swapmap+1);
	    me < (struct mapent *)&swapmap[nswapmap]; me++)
		free += me->m_size;
	printf("%d*1k\n", btok(free));
E 27
E 22
E 6
}

up(size)
	register int size;
{
	register int i, block;

	i = 0;
D 22
	block = DMMIN;
E 22
I 22
	block = dmmin;
E 22
	while (i < size) {
		i += block;
D 22
		if (block < DMMAX)
E 22
I 22
		if (block < dmmax)
E 22
			block *= 2;
	}
	return (i);
}

I 27
/*
 * Compute number of pages to be allocated to the u. area
 * and data and stack area page tables, which are stored on the
 * disk immediately after the u. area.
 */
E 27
vusize(p)
D 25
struct proc *p;
E 25
I 25
D 27
	struct proc *p;
E 27
I 27
	register struct proc *p;
E 27
E 25
{
	register int tsz = p->p_tsize / NPTEPG;

D 22
	return (clrnd(UPAGES + clrnd(ctopt(p->p_tsize+p->p_dsize+p->p_ssize+UPAGES)) - tsz));
E 22
I 22
D 27
	return (ctod(clrnd(UPAGES +
	    clrnd(ctopt(p->p_tsize+p->p_dsize+p->p_ssize+UPAGES)) - tsz)));
E 22
}

xdsize(xp)
D 25
struct text *xp;
E 25
I 25
	struct text *xp;
E 25
{

	if (xp->x_flag & XPAGI)
D 22
		return (clrnd(xp->x_size + ctopt(xp->x_size)));
	return (xp->x_size);
E 22
I 22
		return (ctod(clrnd(xp->x_size + ctopt(xp->x_size))));
	return (ctod(xp->x_size));
E 27
I 27
	/*
	 * We do not need page table space on the disk for page
	 * table pages wholly containing text. 
	 */
	return (clrnd(UPAGES +
	    clrnd(ctopt(p->p_tsize+p->p_dsize+p->p_ssize+UPAGES)) - tsz));
E 27
}

/*
 * Allocate 'size' units from the given
 * map. Return the base of the allocated space.
 * In a map, the addresses are increasing and the
 * list is terminated by a 0 size.
 *
 * Algorithm is first-fit.
 *
 * This routine knows about the interleaving of the swapmap
 * and handles that.
 */
long
rmalloc(mp, size)
	register struct map *mp;
	long size;
{
	register struct mapent *ep = (struct mapent *)(mp+1);
	register int addr;
	register struct mapent *bp;
	swblk_t first, rest;

	if (size <= 0 || size > dmmax)
		return (0);
	/*
	 * Search for a piece of the resource map which has enough
	 * free space to accomodate the request.
	 */
	for (bp = ep; bp->m_size; bp++) {
		if (bp->m_size >= size) {
			/*
			 * If allocating from swapmap,
			 * then have to respect interleaving
			 * boundaries.
			 */
			if (nswdev > 1 &&
			    (first = dmmax - bp->m_addr%dmmax) < bp->m_size) {
				if (bp->m_size - first < size)
					continue;
				addr = bp->m_addr + first;
				rest = bp->m_size - first - size;
				bp->m_size = first;
				if (rest)
					rmfree(mp, rest, addr+size);
				return (addr);
			}
			/*
			 * Allocate from the map.
			 * If there is no space left of the piece
			 * we allocated from, move the rest of
			 * the pieces to the left.
			 */
			addr = bp->m_addr;
			bp->m_addr += size;
			if ((bp->m_size -= size) == 0) {
				do {
					bp++;
					(bp-1)->m_addr = bp->m_addr;
				} while ((bp-1)->m_size = bp->m_size);
			}
			if (addr % CLSIZE)
				return (0);
			return (addr);
		}
	}
	return (0);
}

/*
 * Free the previously allocated space at addr
 * of size units into the specified map.
 * Sort addr into map and combine on
 * one or both ends if possible.
 */
rmfree(mp, size, addr)
	struct map *mp;
	long size, addr;
{
	struct mapent *firstbp;
	register struct mapent *bp;
	register int t;

	/*
	 * Both address and size must be
	 * positive, or the protocol has broken down.
	 */
	if (addr <= 0 || size <= 0)
		goto badrmfree;
	/*
	 * Locate the piece of the map which starts after the
	 * returned space (or the end of the map).
	 */
	firstbp = bp = (struct mapent *)(mp + 1);
	for (; bp->m_addr <= addr && bp->m_size != 0; bp++)
		continue;
	/*
	 * If the piece on the left abuts us,
	 * then we should combine with it.
	 */
	if (bp > firstbp && (bp-1)->m_addr+(bp-1)->m_size >= addr) {
		/*
		 * Check no overlap (internal error).
		 */
		if ((bp-1)->m_addr+(bp-1)->m_size > addr)
			goto badrmfree;
		/*
		 * Add into piece on the left by increasing its size.
		 */
		(bp-1)->m_size += size;
		/*
		 * If the combined piece abuts the piece on
		 * the right now, compress it in also,
		 * by shifting the remaining pieces of the map over.
		 */
		if (bp->m_addr && addr+size >= bp->m_addr) {
			if (addr+size > bp->m_addr)
				goto badrmfree;
			(bp-1)->m_size += bp->m_size;
			while (bp->m_size) {
				bp++;
				(bp-1)->m_addr = bp->m_addr;
				(bp-1)->m_size = bp->m_size;
			}
		}
		goto done;
	}
	/*
	 * Don't abut on the left, check for abutting on
	 * the right.
	 */
	if (addr+size >= bp->m_addr && bp->m_size) {
		if (addr+size > bp->m_addr)
			goto badrmfree;
		bp->m_addr -= size;
		bp->m_size += size;
		goto done;
	}
	/*
	 * Don't abut at all.  Make a new entry
	 * and check for map overflow.
	 */
	do {
		t = bp->m_addr;
		bp->m_addr = addr;
		addr = t;
		t = bp->m_size;
		bp->m_size = size;
		bp++;
	} while (size = t);
	/*
	 * Segment at bp is to be the delimiter;
	 * If there is not room for it 
	 * then the table is too full
	 * and we must discard something.
	 */
	if (bp+1 > mp->m_limit) {
		/*
		 * Back bp up to last available segment.
		 * which contains a segment already and must
		 * be made into the delimiter.
		 * Discard second to last entry,
		 * since it is presumably smaller than the last
		 * and move the last entry back one.
		 */
		bp--;
		printf("%s: rmap ovflo, lost [%d,%d)\n", mp->m_name,
		    (bp-1)->m_addr, (bp-1)->m_addr+(bp-1)->m_size);
		bp[-1] = bp[0];
		bp[0].m_size = bp[0].m_addr = 0;
	}
done:
	return;
badrmfree:
	printf("bad rmfree\n");
I 35
}
I 64
#endif /* NEWVM */
E 73
E 64
D 57
/*
 * "addr"  is a kern virt addr and does not correspond
 * To a phys addr after zipping out the high bit..
 * since it was valloc'd in the kernel.
 *
 * We return the phys addr by simulating kernel vm (/dev/kmem)
 * when we are reading a crash dump.
 */
I 40
off_t
E 40
mkphys(addr)
I 40
	off_t addr;
E 57
I 57

D 76
#include <varargs.h>

error(va_alist)
	va_dcl
E 76
I 76
void
usage()
E 76
E 57
E 40
{
D 40
	register o;
E 40
I 40
D 57
	register off_t o;
E 57
I 57
D 76
	char *fmt;
	va_list ap;
	extern errno;
E 57
E 40

D 57
	if (!kflg)
		return(addr);
I 43
	addr = clear(addr);
E 43
	o = addr & PGOFSET;
	addr >>= PGSHIFT;
	addr &= PG_PFNUM;
	addr *=  NBPW;
D 48
	addr = getw(nl[SYSMAP].n_value + addr);
E 48
I 48
	addr = getword(nl[SYSMAP].n_value + addr);
E 48
	addr = ((addr & PG_PFNUM) << PGSHIFT) | o;
	return(addr);
E 57
I 57
D 71
	fprintf(stderr, "%s: ", Program);
E 71
I 71
	fprintf(stderr, "pstat: ");
E 71
	va_start(ap);
	fmt = va_arg(ap, char *);
	(void) vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, "\n");
}

syserror(va_alist)
	va_dcl
{
	char *fmt;
	va_list ap;
	extern errno;

D 71
	fprintf(stderr, "%s: ", Program);
E 71
I 71
	fprintf(stderr, "pstat: ");
E 71
	va_start(ap);
	fmt = va_arg(ap, char *);
	(void) vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, ": %s\n", strerror(errno));
E 76
I 76
	(void)fprintf(stderr,
	    "usage: pstat -Tfnstv [system] [-M core] [-N system]\n");
	exit(1);
E 76
E 57
E 35
E 22
I 4
}
D 18

E 18
D 12
dompx()
{
	register int i;
	struct chan chans[NCHANS];
	struct schan schans[NPORTS];

	lseek(fc, (long)nl[SCHANS].n_value, 0);
	read(fc, chans, sizeof chans);
	lseek(fc, (long)nl[SSCHANS].n_value, 0);
	read(fc, schans, sizeof schans);

	printf("CHAN  FLAGS            INDEX     LINE  GROUP     FILE      TTYP      CTLX      PGRP    OTTYP     OLINE  DATQ      CTLY\n");
	for (i = 0; i < NCHANS; i++) {
		printf("%3d   ", i);
		putf(chans[i].c_flags&INUSE, 'I');
		putf(chans[i].c_flags&SIOCTL, 'S');
		putf(chans[i].c_flags&XGRP, 'X');
		putf(chans[i].c_flags&YGRP, 'Y');
		putf(chans[i].c_flags&WCLOSE, 'W');
		putf(chans[i].c_flags&ISGRP, 'i');
		putf(chans[i].c_flags&BLOCK, 'B');
		putf(chans[i].c_flags&EOTMARK, 'E');
		putf(chans[i].c_flags&SIGBLK, 's');
		putf(chans[i].c_flags&BLKMSG, 'b');
		putf(chans[i].c_flags&ENAMSG, 'e');
		putf(chans[i].c_flags&WFLUSH, 'w');
		putf(chans[i].c_flags&NMBUF, 'N');
		putf(chans[i].c_flags&PORT, 'P');
		putf(chans[i].c_flags&ALT, 'A');
		putf(chans[i].c_flags&FBLOCK, 'F');
		printf("%8x  ", chans[i].c_index);
		printf("%3d   ", chans[i].c_line);
		printf("%8x  ", chans[i].c_group);
		printf("%8x  ", chans[i].c_fy);
		printf("%8x  ", chans[i].c_ttyp);
		printf("%8x  ", chans[i].c_ctlx);
		printf("%6d  ", chans[i].c_pgrp);
		printf("%8x  ", chans[i].c_ottyp);
		printf("%3d   ", chans[i].c_oline);
		printf("%8x  ", chans[i].cx.datq);
		printf("%8x\n", chans[i].c_ctly);
	}

	printf("\nCHAN  FLAGS            INDEX     LINE  GROUP     FILE      TTYP      CTLX      PGRP\n");
	for (i = 0; i < NPORTS; i++) {
		printf("%3d  ", i);
		putf(schans[i].c_flags&INUSE, 'I');
		putf(schans[i].c_flags&SIOCTL, 'S');
		putf(schans[i].c_flags&XGRP, 'X');
		putf(schans[i].c_flags&YGRP, 'Y');
		putf(schans[i].c_flags&WCLOSE, 'W');
		putf(schans[i].c_flags&ISGRP, 'i');
		putf(schans[i].c_flags&BLOCK, 'B');
		putf(schans[i].c_flags&EOTMARK, 'E');
		putf(schans[i].c_flags&SIGBLK, 's');
		putf(schans[i].c_flags&BLKMSG, 'b');
		putf(schans[i].c_flags&ENAMSG, 'e');
		putf(schans[i].c_flags&WFLUSH, 'w');
		putf(schans[i].c_flags&NMBUF, 'N');
		putf(schans[i].c_flags&PORT, 'P');
		putf(schans[i].c_flags&ALT, 'A');
		putf(schans[i].c_flags&FBLOCK, 'F');
		printf("%8x  ", schans[i].c_index);
		printf("%3d   ", schans[i].c_line);
		printf("%8x  ", schans[i].c_group);
		printf("%8x  ", schans[i].c_fy);
		printf("%8x  ", schans[i].c_ttyp);
		printf("%8x  ", schans[i].c_ctlx);
		printf("%6d\n", schans[i].c_pgrp);
	}
}

dogroup()
{
	register int i, j;
	struct group *groups[NGROUPS];
	struct group g;

	lseek(fc, (long)nl[SGROUP].n_value, 0);
	read(fc, groups, sizeof groups);
	printf("GROUP STATE      INDEX     ROT  *GROUP    *INODE    *FILE     ROTM  DATQ\n");
	for (i = 0; i < NGROUPS; i++) {
		if (groups[i] == 0)
			continue;
		lseek(fc, (long) groups[i], 0);
		read(fc, &g, sizeof g);
		printf("%3d   ", i);
		printf("%8x  ", g.g_state);
		printf("%8x  ", g.g_index);
		printf("%3d  ", g.g_rot);
		printf("%8x  ", g.g_group);
		printf("%8x  ", g.g_inode);
		printf("%8x  ", g.g_file);
		printf("%3d   ", g.g_rotmask);
		printf("%3d\n", g.g_datq);
	}
E 4
}
E 12
E 1
