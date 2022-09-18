h09733
s 00002/00000/00490
d D 8.7 94/08/05 16:34:11 mckusick 109 108
c put white-out in conditionally
e
s 00011/00001/00479
d D 8.6 94/07/28 03:38:14 pendry 108 107
c changes for whiteouts and union filesystem
e
s 00002/00002/00478
d D 8.5 94/04/02 09:56:11 pendry 107 106
c add 1994 copyright
e
s 00002/00001/00478
d D 8.4 94/04/01 09:57:07 bostic 106 105
c check for fts_read error
c don't bother closing down the tree, we're going to exit
e
s 00003/00004/00476
d D 8.3 94/04/01 09:55:20 bostic 105 104
c setting errno and then not exiting isn't safe
e
s 00008/00009/00472
d D 8.2 94/04/01 02:08:17 pendry 104 103
c prettyness police
e
s 00004/00004/00477
d D 8.1 93/06/02 18:29:08 mckusick 103 102
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00481
d D 5.77 93/06/02 18:28:05 mckusick 102 100
c getbsize now comes from libc
e
s 00004/00004/00479
d R 8.1 93/05/31 14:45:51 bostic 101 100
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/00480
d D 5.76 93/05/05 13:03:43 bostic 100 99
c use fts_errno field, stat may not have been called
e
s 00011/00010/00470
d D 5.75 93/04/29 12:40:15 bostic 99 98
c use err/warn routines from C library
e
s 00002/00002/00478
d D 5.74 93/04/28 17:22:38 bostic 98 97
c getbsize doesn't need the program name any longer
e
s 00001/00004/00479
d D 5.73 93/04/28 17:17:54 bostic 97 96
c delete -k option
e
s 00000/00002/00483
d D 5.72 93/04/28 10:38:57 bostic 96 95
c move user_from_uid and group_from_gid into libc
e
s 00002/00034/00483
d D 5.71 93/03/03 20:36:26 bostic 95 94
c break flags_from_fid out into separate file, stat_flags.c
c used by chflags, install
e
s 00004/00003/00513
d D 5.70 93/01/15 11:00:46 elan 94 93
c Fixed bug in traverse() that caused empty directories and permission
c errors to look the same.
e
s 00008/00004/00508
d D 5.69 92/10/17 15:09:25 bostic 93 92
c snprintf returns printed length, not actual length
e
s 00001/00001/00511
d D 5.68 92/09/16 14:53:22 elan 92 91
c copyright -> static.
e
s 00010/00004/00502
d D 5.67 92/06/28 15:43:44 bostic 91 90
c make display line up if block/char devices displayed with other
c files.  (Jan-Simon has *way* too much free time...)
e
s 00009/00009/00497
d D 5.66 92/06/02 15:55:32 bostic 90 89
c values handed to printf(3) as field widths are really ints
e
s 00002/00001/00504
d D 5.65 92/06/01 22:25:02 mckusick 89 88
c sizes are now 64-bit numbers
e
s 00001/00001/00504
d D 5.64 92/04/02 14:18:02 bostic 88 87
c don't put fts_open in the error message
e
s 00004/00002/00501
d D 5.63 92/03/13 17:18:55 bostic 87 86
c always print out something for -o option
e
s 00128/00030/00375
d D 5.62 92/03/13 17:09:04 elan 86 85
c calculate all of the field sizes dynamically
e
s 00005/00004/00400
d D 5.61 92/03/02 15:07:36 bostic 85 84
c minor wordsmithign
e
s 00014/00007/00390
d D 5.60 92/03/01 16:52:49 bostic 84 83
c replace -k with the BLOCKSIZE environmental variable
e
s 00065/00071/00332
d D 5.59 92/03/01 13:23:17 bostic 83 82
c fix newline/directory name display logic; fts_children fix for stats
e
s 00003/00002/00400
d D 5.58 92/02/26 16:14:38 bostic 82 81
c KNF
e
s 00004/00002/00398
d D 5.57 92/02/25 14:56:47 elan 81 80
c Fixed no stat'ing on -i option -- need to stat.
e
s 00010/00002/00390
d D 5.56 92/02/04 16:57:19 bostic 80 79
c use FTS_COMFOLLOW flag to follow symlinks unless -l, -d, or -F
e
s 00022/00045/00370
d D 5.55 92/02/03 16:42:39 bostic 79 78
c make routines public; fix physical/logical walk; clean up dot/dotdot
c handling on directory visit; don't test errno explicitly, FTS_NS is always
c an error.
e
s 00002/00009/00413
d D 5.54 92/02/03 13:51:49 elan 78 77
c Fixed bug that prevented '.' files from being listed when on argument
c line.
e
s 00199/00247/00223
d D 5.53 92/01/29 16:14:56 elan 77 76
c New version of using fts(3) routines.  This version is more robust /
e
s 00005/00001/00465
d D 5.52 91/12/12 16:36:56 mckusick 76 75
c add -o option to list file flags
e
s 00001/00001/00465
d D 5.51 91/11/19 23:38:46 torek 75 74
c doargs writes on argv via prcopy, so provide writable "."
e
s 00005/00007/00461
d D 5.50 91/11/06 15:15:39 bostic 74 73
c don't step over the end of the argv array
e
s 00038/00041/00430
d D 5.49 91/10/28 15:45:21 bostic 73 72
c It's a brave new ANSI world!
e
s 00001/00001/00470
d D 5.48 91/04/03 13:59:21 bostic 72 71
c oops.  Got stat test logic wrong
e
s 00017/00014/00454
d D 5.47 91/04/02 17:42:06 bostic 71 70
c When reading a directory, -L should still apply, don't always use
c lstat(2).  I'm not positive this is right, since I'm not sure that the same
c criteria for stat function selection applies when traversing directories.
c When this gets converted to fts(3), it should be rethought.
e
s 00002/00001/00466
d D 5.46 91/04/02 16:55:50 bostic 70 69
c ls -F foo, where foo is a symbolic link should display "foo@"
e
s 00001/00001/00466
d D 5.45 91/03/04 10:30:15 bostic 69 68
c fix for pcc
e
s 00003/00001/00464
d D 5.44 91/02/26 15:06:04 bostic 68 67
c ANSI makes strings unwriteable
e
s 00005/00001/00460
d D 5.43 90/07/22 12:56:29 bostic 67 66
c there needs to be a way to get the hour/minute of a file that's more
c than six months old.  And ls(1) needs more options anyway.
e
s 00002/00002/00459
d D 5.42 90/05/17 17:30:59 bostic 66 65
c ANSI C redefined bcopy and strlen
e
s 00001/00001/00460
d D 5.41 90/05/15 19:41:21 bostic 65 64
c string.h is ANSI C include file
e
s 00006/00003/00455
d D 5.40 90/05/10 20:50:46 bostic 64 63
c don't exit if stat fails; could reasonably happen under NFS
e
s 00001/00001/00457
d D 5.39 90/04/09 17:58:28 bostic 63 62
c sccs include now replaces the line
e
s 00000/00000/00458
d D 5.38 90/04/08 17:41:43 bostic 62 61
c get redist notice from /usr/share/misc
e
s 00001/00011/00457
d D 5.37 90/04/08 17:26:51 bostic 61 60
c get redistribution notice from /usr/share/misc
e
s 00021/00020/00447
d D 5.36 90/02/22 12:34:06 bostic 60 59
c no assignment to the pointer was made after the realloc; rework so
c that no allocation is done for empty directories
e
s 00002/00004/00465
d D 5.35 90/01/03 16:12:45 bostic 59 58
c assign immediately, so on error return NULL's aren't free'd.
e
s 00006/00002/00463
d D 5.34 89/09/02 10:44:11 bostic 58 57
c put -f flag back in; it only stops sorting now
e
s 00005/00001/00460
d D 5.33 89/08/22 12:26:38 bostic 57 56
c default sizes are in 512-byte blocks; add -k flag for kilobytes
e
s 00011/00059/00450
d D 5.32 89/08/16 14:46:41 bostic 56 55
c remove -f option, can't use readdir any more, won't work over NFS
e
s 00008/00006/00501
d D 5.31 89/07/09 11:39:04 bostic 55 54
c more symlink fixes
e
s 00007/00005/00500
d D 5.30 89/06/27 18:23:08 bostic 54 53
c don't assign result until after all reallocs; grow size faster
e
s 00017/00017/00488
d D 5.29 89/06/27 18:02:19 bostic 53 52
c make `total' line, directory name, and preceding newline right
e
s 00008/00002/00497
d D 5.28 89/06/26 19:55:11 bostic 52 51
c make -f output look like standard outputs
e
s 00064/00040/00435
d D 5.27 89/06/26 19:45:31 bostic 51 50
c count blocks/length in argument code, as well as in directory reading
c minor cleanups, move f_special code out of argument reading routine
e
s 00001/00001/00474
d D 5.26 89/06/26 16:33:53 bostic 50 49
c set newline arg if printing multiple directories w/o reg files
e
s 00010/00016/00465
d D 5.25 89/06/26 16:33:34 bostic 49 48
c print totals for -s flag, as well as -l
e
s 00000/00002/00481
d D 5.24 89/06/26 16:33:11 bostic 48 47
c don't need sgbuf
e
s 00006/00003/00477
d D 5.23 89/06/26 16:32:47 bostic 47 46
c always have a termwidth, even if not to a tty
e
s 00050/00016/00430
d D 5.22 89/06/26 16:32:28 bostic 46 45
c keep track of blocks and max file name length in tabdir
e
s 00021/00002/00425
d D 5.21 89/06/26 16:32:10 bostic 45 44
c get window size, break up printdir into three functions
e
s 00017/00017/00410
d D 5.20 89/06/26 16:31:54 bostic 44 43
c rename routines to be more informative
e
s 00013/00009/00414
d D 5.19 89/06/26 16:31:35 bostic 43 42
c get inode from directory for -f option; don't require stat for -i
e
s 00032/00015/00391
d D 5.18 89/06/26 16:31:17 bostic 42 41
c cleanups, comment better, use pointers rather than offsets
e
s 00012/00005/00394
d D 5.17 89/06/26 16:30:55 bostic 41 40
c add getwd/chdir for multiple directory operands
e
s 00042/00040/00357
d D 5.16 89/06/26 16:30:32 bostic 40 39
c fix up flags; document options better; get rid of f_modetime;
c only args() needs a stat function pointer, make -L work right
e
s 00022/00029/00375
d D 5.15 89/06/26 16:30:04 bostic 39 38
c keep track of path end; fix open fd error, -f blocks -R and -F
e
s 00191/00543/00213
d D 5.14 89/06/26 16:29:44 bostic 38 37
c breakup into multiple files
e
s 00504/00563/00252
d D 5.13 89/06/26 16:29:12 bostic 37 36
c first working version of new ls
e
s 00701/00545/00114
d D 5.12 89/06/26 16:03:03 bostic 36 35
c original code from Michael Fischbein (mfischbein@Sun.COM)
e
s 00002/00000/00657
d D 5.11 89/03/06 20:41:22 bostic 35 34
c add setpassent/setgroupent to speed up user uid/gid access
e
s 00000/00002/00657
d D 5.10 88/12/28 14:24:55 bostic 34 33
c remove pw_stayopen
e
s 00001/00001/00658
d D 5.9 87/10/22 09:51:43 bostic 33 32
c ANSI C; sprintf now returns an int.
e
s 00006/00006/00653
d D 5.8 87/09/11 11:40:32 bostic 32 31
c use S/T if exec bit not set; bug report 4.3BSD/bin/57
e
s 00091/00125/00568
d D 5.7 87/07/01 13:05:42 bostic 31 29
c use getopt(3), use uid_t/gid_t, minor lint work, cache group id's 
c in same fashion as uid's.
e
s 00065/00064/00629
d R 5.7 87/06/22 12:32:30 bostic 30 29
c lint, getopt
e
s 00000/00000/00693
d D 5.6 86/05/12 14:38:55 karels 29 28
x 26
c undo -S
e
s 00001/00001/00701
d D 5.5 86/03/04 05:14:51 lepreau 28 27
c XTABS is a 2 bit field
e
s 00001/00001/00701
d D 5.4 85/11/25 13:30:35 mckusick 27 26
c file systems grow larger
e
s 00011/00002/00691
d D 5.3 85/09/04 18:32:51 bloom 26 25
c add sort by size and bug fix (from serge@arpa)
e
s 00001/00001/00692
d D 5.2 85/07/26 10:36:52 bloom 25 24
c fix problem with -R listing incorrect directories
e
s 00014/00002/00679
d D 5.1 85/04/30 14:57:30 dist 24 23
c Add copyright
e
s 00018/00042/00663
d D 4.22 85/03/04 13:40:07 bloom 23 21
c major performance improvement
e
s 00011/00034/00671
d R 4.22 85/02/21 17:32:15 bloom 22 21
c don't waste time with getpwent, use getpwuid (a major win with
c a large password file
e
s 00007/00001/00698
d D 4.21 85/02/20 11:23:20 bloom 21 20
c use window size ioctl for output width
e
s 00006/00008/00693
d D 4.20 83/09/22 22:10:33 sam 20 19
c bug with large uids
e
s 00008/00007/00693
d D 4.19 83/08/19 16:19:19 sam 19 18
c incorrect max login name size
e
s 00001/00001/00699
d D 4.18 83/08/15 15:56:56 karels 18 17
c always complain if file can't be lstat'ed
e
s 00004/00002/00696
d D 4.17 83/08/14 22:53:00 sam 17 16
c default to lstat's when symbolic link points to oblivion
e
s 00019/00011/00679
d D 4.16 83/08/14 00:45:47 sam 16 15
c fix ralph's blunder
e
s 00011/00019/00679
d D 4.15 83/08/09 11:02:10 ralph 15 14
c fixed ls -L -f -F for symbolic links
e
s 00000/00000/00698
d D 4.14 83/07/01 23:57:30 wnj 14 13
c include problems
e
s 00001/00001/00697
d D 4.13 83/06/30 14:38:11 sam 13 12
c include fix
e
s 00001/00001/00697
d D 4.12 83/05/24 11:06:30 sam 12 11
c blew last delta, things changed while robert was away
e
s 00017/00028/00681
d D 4.11 83/05/22 18:06:27 sam 11 10
c user block count in inode (from kre)
e
s 00026/00003/00683
d D 4.10 83/05/10 12:53:20 mckusick 10 9
c fix -l to list groups with gid > NGID by name
e
s 00025/00002/00661
d D 4.9 83/05/09 18:02:34 mckusick 9 8
c fix -l so that it works with uid's that are >NUID
e
s 00009/00001/00654
d D 4.8 82/12/03 20:23:36 mckusick 8 7
c follow symbolic links that point to directories
e
s 00009/00001/00646
d D 4.7 82/11/14 16:33:00 sam 7 6
c convert to 4.1c sys calls and directory layout
e
s 00001/00001/00646
d D 4.6 82/05/07 16:20:29 mckusick 6 5
c update to new fs
e
s 00004/00004/00643
d D 4.5 82/03/31 11:44:38 root 5 4
c L option; use lstat by default
e
s 00001/00001/00646
d D 4.4 82/03/27 18:47:16 wnj 4 3
c too many args to sprintf in fmtentry
e
s 00002/00000/00645
d D 4.3 82/03/15 05:09:29 root 3 2
c ls -F prints links followed by @
e
s 00006/00006/00639
d D 4.2 82/03/05 15:16:18 root 2 1
c -l on dev and error message fixes
e
s 00645/00000/00000
d D 4.1 82/03/05 02:29:00 wnj 1 0
c date and time created 82/03/05 02:29:00 by wnj
e
u
U
t
T
I 24
/*
D 36
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 36
I 36
D 37
 * Written by Michael Fischbein, currently with Sun Microsystems, Inc.
 * (sun!sunbow!msf)
 * 16 June 1989 18:41
E 37
I 37
D 103
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 103
I 103
D 107
 * Copyright (c) 1989, 1993
E 107
I 107
 * Copyright (c) 1989, 1993, 1994
E 107
 *	The Regents of the University of California.  All rights reserved.
E 103
 *
 * This code is derived from software contributed to Berkeley by
 * Michael Fischbein.
 *
D 61
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 61
I 61
D 63
%sccs.include.redist.c%
E 63
I 63
 * %sccs.include.redist.c%
E 63
E 61
E 37
E 36
 */
D 36

E 24
I 1
#ifndef lint
D 11
static	char *sccsid = "%W% %E%";
E 11
I 11
D 24
static	char *sccsid = "%W% (Berkeley) %G%";
E 11
#endif
E 24
I 24
char copyright[] =
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
 All rights reserved.\n";
#endif not lint

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 24

/*
 * ls
 *
D 11
 * 4.2bsd version for symbolic links and variable length directory entries.
E 11
I 11
 * 4.2bsd version for symbolic links, variable length
 * directory entries, block size in the inode, etc.
E 11
 */
D 11

E 11
#include <sys/param.h>
#include <sys/stat.h>
D 6
#include <ndir.h>
E 6
I 6
D 13
#include <dir.h>
E 13
I 13
#include <sys/dir.h>
E 36
E 13
E 6
D 37
#include <stdio.h>
D 36
#include <sgtty.h>
E 36
I 36
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
E 37
I 37

#ifndef lint
D 92
char copyright[] =
E 92
I 92
static char copyright[] =
E 92
D 103
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 103
I 103
D 107
"%Z% Copyright (c) 1989, 1993\n\
E 107
I 107
"%Z% Copyright (c) 1989, 1993, 1994\n\
E 107
	The Regents of the University of California.  All rights reserved.\n";
E 103
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 37
D 77
#include <sys/param.h>
E 77
I 77
D 86
#include <sys/types.h>	
E 86
I 86
#include <sys/types.h>
E 86
E 77
I 37
#include <sys/stat.h>
I 45
#include <sys/ioctl.h>
I 99

E 99
I 83
#include <dirent.h>
E 83
E 45
D 38
#include <sys/time.h>
E 38
E 37
D 77
#include <dirent.h>
E 77
I 73
D 99
#include <unistd.h>
E 99
I 99
#include <err.h>
#include <errno.h>
E 99
I 77
#include <fts.h>
I 99
#include <stdio.h>
E 99
E 77
#include <stdlib.h>
E 73
D 37
#include <sys/sysmacros.h>
E 37
D 38
#include <grp.h>
#include <pwd.h>
E 38
D 37
#include <time.h>
E 37
I 37
D 65
#include <strings.h>
E 65
I 65
#include <string.h>
E 65
D 38
#include <tzfile.h>
E 38
D 99
#include <errno.h>
#include <stdio.h>
E 99
I 99
#include <unistd.h>

E 99
E 37
D 38
#include <ctype.h>
E 38
I 38
#include "ls.h"
I 73
#include "extern.h"
E 73
E 38
E 36

I 56
D 73
int (*sortfcn)(), (*printfcn)();
E 56
D 11
#define	kbytes(size)	((size + 1023) / 1024)
E 11
I 11
D 36
#define	kbytes(size)	(((size) + 1023) / 1024)
E 36
I 36
D 37
extern int getopt();
extern char *optarg;
extern int optind, opterr;
extern int stat(), lstat();
E 36
E 11

D 36
struct afile {
	char	ftype;		/* file type, e.g. 'd', 'c', 'f' */
	ino_t	fnum;		/* inode number of file */
	short	fflags;		/* mode&~S_IFMT, perhaps ISARG */
	short	fnl;		/* number of links */
D 31
	short	fuid;		/* owner id */
	short	fgid;		/* group id */
	long	fsize;		/* file size */
E 31
I 31
	uid_t	fuid;		/* owner id */
	gid_t	fgid;		/* group id */
	off_t	fsize;		/* file size */
E 31
I 11
	long	fblks;		/* number of blocks used */
E 11
	time_t	fmtime;		/* time (modify or access or create) */
	char	*fname;		/* file name */
	char	*flinkto;	/* symbolic link value */
};
E 36
I 36
int     namecmp();		/* name comparison for qsort */
int     revnamecmp();
int     acccmp();		/* access time comparison for qsort */
int     revacccmp();
int     modcmp();		/* modify time comparixon for qsort */
int     revmodcmp();
int     statcmp();		/* status time comparixon for qsort */
int     revstatcmp();
int     printfancy();
int     prablelen();
char   *emalloc();
E 36

D 36
#define ISARG	0x8000		/* extra ``mode'' */
E 36
I 36
typedef struct lsstruct {
	char   *name;		/* pointer to filename */
E 37
I 37
D 38
typedef struct _lsstruct {
E 37
	struct stat lstat;
D 37
}       lsstruct;
E 37
I 37
	char *name;		/* pointer to filename */
} LS;
E 38
I 38
D 46
int lstat(), strlen(), prablelen();
E 46
I 46
D 66
int lstat(), strlen();
E 66
I 66
int lstat();
E 66
E 46
char *emalloc();
E 73
I 73
D 77
static void	displaydir __P((LS *, int));
static void	doargs __P((int, char **));
static void	subdir __P((LS *));
static int	tabdir __P((LS *, LS **, char **));
E 77
I 77
D 79
static void	display __P((int, FTSENT *, FTSENT *));
static int	mastercmp __P((const FTSENT **, const FTSENT **));
static void	traverse __P((int, char **, int));
E 79
I 79
D 83
void	display __P((int, FTSENT *, FTSENT *));
E 83
I 83
D 84
void	display __P((FTSENT *, FTSENT *));
E 83
int	mastercmp __P((const FTSENT **, const FTSENT **));
void	traverse __P((int, char **, int));
E 84
I 84
D 86
void	 display __P((FTSENT *, FTSENT *));
char	*getbsize __P((char *, int *, int *));
int	 mastercmp __P((const FTSENT **, const FTSENT **));
void	 traverse __P((int, char **, int));
E 86
I 86
D 98
char	*getbsize __P((char *, int *, long *));
E 98
I 98
D 102
char	*getbsize __P((int *, long *));
E 98
D 96
char	*group_from_gid __P((u_int, int));
char	*user_from_uid __P((u_int, int));
E 96
E 86
E 84
E 79
E 77
E 73
E 38
E 37
E 36

E 102
I 77
D 86
static void (*printfcn) __P((FTSENT *, int, u_long, int));
E 86
I 86
static void	 display __P((FTSENT *, FTSENT *));
D 95
static char	*flags_from_fid __P((u_long));
E 95
static int	 mastercmp __P((const FTSENT **, const FTSENT **));
static void	 traverse __P((int, char **, int));

static void (*printfcn) __P((DISPLAY *));
E 86
static int (*sortfcn) __P((const FTSENT *, const FTSENT *));

I 86
long blocksize;			/* block size units */
E 86
E 77
D 36
struct subdirs {
	char	*sd_name;
	struct	subdirs *sd_next;
} *subdirs;
E 36
D 37

E 37
D 15
int	aflg, dflg, gflg, lflg, sflg, tflg, uflg, iflg, fflg, cflg, rflg = 1;
E 15
I 15
D 16
int	aflg, dflg, gflg, lflg, sflg, tflg, uflg, iflg, cflg, rflg = 1;
E 16
I 16
D 36
int	aflg, dflg, gflg, lflg, sflg, tflg, uflg, iflg, fflg, cflg, rflg = 1;
E 16
E 15
D 5
int	qflg, Aflg, Fflg, Rflg, Cflg, hflg;
E 5
I 5
D 26
int	qflg, Aflg, Cflg, Fflg, Lflg, Rflg;
E 36
I 36
D 38
/* globals */
D 37
int     (*statfcn) () = lstat;
int     (*lengthfcn) () = strlen;
int     listallflag;		/* list .xxx files? */
int     listalwaysflag;		/* list . and .. */
int     modtimeflag;		/* use time of last change for time */
int     accesstimeflag;		/* use time of last access */
int     statustimeflag;		/* use time of last mode change */
int     singlecolflag;		/* use single column output */
int     sortacrossflag;		/* sort across vice down */
int     listdirflag;		/* list actual directory, not contents */
int     specialdirflag;		/* force params to be directories */
int     fancyflag;		/* add /, * @ = to mark non-regular files */
int     groupflag;		/* show group ownership of a file */
int     inodeflag;		/* print inode */
int     longformflag;		/* long listing format */
int     nonprintflag;		/* show unprintables as ? */
int     reversesortflag;	/* reverse whatever sort is used */
int     recursiveflag;		/* ls subdirectories also */
int     sizeflag;		/* list size in short listing */
int     timesortflag;		/* sort by time vice name */
int     numberflag;		/* list UID and GID by number */
int     firsttimethruflag;	/* to control recursion */
E 37
I 37
extern int lstat(), strlen(), prablelen();
E 38
D 40
int (*statfcn)() = lstat;
E 40
D 56
int (*lengthfcn)() = strlen;
int (*sortfcn)();
I 45
int (*printfcn)();
E 45
I 38
D 53
int needstat;
E 53
I 45
D 47
int termwidth;
E 47
E 45
E 38
E 37
E 36
E 26
I 26
int	qflg, Aflg, Cflg, Fflg, Lflg, Rflg, Sflg;
E 26
E 5

E 56
I 47
int termwidth = 80;		/* default terminal width */
I 84
D 86
int blocksize;			/* block size units */
E 86
E 84

E 47
D 36
int	usetabs;

time_t	now, sixmonthsago;

char	*dotp = ".";

I 21
D 23
struct winsize win;
E 23
I 23
struct	winsize win;
E 23
int	twidth;

E 21
struct	afile *gstat();
int	fcmp();
char	*cat(), *savestr();
char	*fmtentry();
char	*getname(), *getgroup();

char	*ctime();
char	*malloc(), *calloc(), *realloc();
D 33
char	*sprintf(), *strcpy(), *strcat();
E 33
I 33
char	*strcpy(), *strcat();
E 33

E 36
I 36
D 37
/*
 * entry point for ls.
 * Parse options and call appropriate subroutines
 */
E 36
main(argc, argv)
D 36
	int argc;
	char *argv[];
E 36
I 36
int     argc;
char   *argv[];
E 37
I 37
/* flags */
D 38
int f_listall;			/* list .xxx files? */
int f_listalways;		/* list . and .. */
E 38
I 38
D 40
int f_listdot;			/* list files beginning with . */
int f_listalldot;		/* list . and .. as well */
E 38
int f_modtime;			/* use time of last change for time */
E 40
int f_accesstime;		/* use time of last access */
I 51
int f_column;			/* columnated format */
E 51
D 40
int f_statustime;		/* use time of last mode change */
int f_singlecol;		/* use single column output */
int f_listdir;			/* list actual directory, not contents */
int f_specialdir;		/* force params to be directories */
D 38
int f_type;			/* add /, * @ = to mark non-regular files */
E 38
I 38
int f_type;			/* add type character for non-regular files */
E 40
I 40
D 45
int f_firsttime = 1;		/* to control recursion */
E 45
E 40
E 38
D 86
int f_group;			/* show group ownership of a file */
E 86
I 76
int f_flags;			/* show flags associated with a file */
E 76
I 40
D 79
int f_ignorelink;		/* indirect through symbolic link operands */
E 79
E 40
int f_inode;			/* print inode */
I 57
D 84
int f_kblocks;			/* print size in kilobytes */
E 84
E 57
I 40
D 79
int f_listalldot;		/* list . and .. as well */
E 79
int f_listdir;			/* list actual directory, not contents */
int f_listdot;			/* list files beginning with . */
E 40
int f_longform;			/* long listing format */
I 53
D 77
int f_needstat;			/* if need to stat files */
E 77
I 77
D 79
int f_needstat;                 /* need stat(2) information */
E 79
E 77
int f_newline;			/* if precede with newline */
E 53
int f_nonprint;			/* show unprintables as ? */
I 58
int f_nosort;			/* don't sort output */
E 58
D 40
int f_reversesort;		/* reverse whatever sort is used */
E 40
int f_recursive;		/* ls subdirectories also */
I 40
int f_reversesort;		/* reverse whatever sort is used */
I 67
int f_sectime;			/* print the real time for all files */
E 67
int f_singlecol;		/* use single column output */
E 40
int f_size;			/* list size in short listing */
I 40
D 56
int f_specialdir;		/* force params to be directories */
E 56
int f_statustime;		/* use time of last mode change */
I 53
int f_dirname;			/* if precede with directory name */
E 53
E 40
int f_timesort;			/* sort by time vice name */
I 53
D 77
int f_total;			/* if precede with "total" line */
E 77
E 53
D 38
int f_number;			/* list UID and GID by number */
E 38
D 40
int f_firsttime = 1;		/* to control recursion */
E 40
I 40
int f_type;			/* add type character for non-regular files */
I 108
int f_whiteout;			/* show whiteout entries */
E 108
E 40
E 37

I 71
D 73
int (*statfcn)(), stat(), lstat();
E 73
I 73
D 77
void (*printfcn)();
int (*statfcn)(), (*sortfcn)();
E 73

E 77
I 77
D 79
void
E 79
I 79
int
E 79
E 77
E 71
I 37
main(argc, argv)
	int argc;
D 77
	char **argv;
E 77
I 77
	char *argv[];
E 77
E 37
E 36
{
I 83
	static char dot[] = ".", *dotav[] = { dot, NULL };
E 83
D 31
	int i;
E 31
I 31
D 36
	extern int optind;
E 31
	struct afile *fp0, *fplast;
	register struct afile *fp;
	struct sgttyb sgbuf;
I 31
	int ch, i;
	time_t time();
E 36
I 36
D 37
	static char options[] = "aAcCdfFgilLqrRstu1";
	int     inch;		/* input character */
E 37
I 37
D 73
	extern int optind, stat();
E 73
I 45
D 48
	struct sgttyb sgbuf;
E 48
	struct winsize win;
E 45
D 77
	int ch;
E 77
I 77
D 84
	int ch, fts_options;
E 84
I 84
	int ch, fts_options, notused;
E 84
E 77
I 45
D 73
	char *p, *getenv();
E 45
D 51
	int namecmp(), revnamecmp(), acccmp(), revacccmp();
	int modcmp(), revmodcmp(), statcmp(), revstatcmp();
I 45
	int printcol(), printlong(), printscol();
E 51
I 51
D 66
	int acccmp(), bcopy(), modcmp(), namecmp(), prcopy(), printcol();
E 66
I 66
	int acccmp(), modcmp(), namecmp(), prcopy(), printcol();
E 66
	int printlong(), printscol(), revacccmp(), revmodcmp(), revnamecmp();
	int revstatcmp(), statcmp();
E 73
I 73
	char *p;
E 73
E 51
E 45
E 37
E 36
E 31

D 31
	argc--, argv++;
	if (getuid() == 0)
		Aflg++;
E 31
I 31
D 36
	Aflg = !getuid();
E 31
	(void) time(&now); sixmonthsago = now - 6L*30L*24L*60L*60L; now += 60;
I 21
	twidth = 80;
E 36
I 36
D 37
 /* set up defaults for terminal/nonterminal stdout */
	firsttimethruflag = 1;
E 37
I 37
D 40
	 /* set up defaults for terminal/nonterminal stdout */
E 40
I 40
D 51
	/*
	 * terminal defaults to -C -q
	 * non-terminal defaults to -1
	 */
E 51
I 51
D 77
	/* terminal defaults to -Cq, non-terminal defaults to -1 */
E 77
I 77
	/* Terminal defaults to -Cq, non-terminal defaults to -1. */
E 77
E 51
E 40
E 37
E 36
E 21
D 83
	if (isatty(1)) {
D 11

E 11
D 36
		qflg = Cflg = 1;
		(void) gtty(1, &sgbuf);
I 21
		if (ioctl(1, TIOCGWINSZ, &win) != -1)
			twidth = (win.ws_col == 0 ? 80 : win.ws_col);
E 21
D 28
		if ((sgbuf.sg_flags & XTABS) == 0)
E 28
I 28
		if ((sgbuf.sg_flags & XTABS) != XTABS)
E 28
			usetabs = 1;
	} else
		usetabs = 1;
D 31
	while (argc > 0 && **argv == '-') {
		(*argv)++;
		while (**argv) switch (*(*argv)++) {

		case 'C':
			Cflg = 1; break;
		case 'q':
			qflg = 1; break;
E 31
I 31
	while ((ch = getopt(argc, argv, "1ACLFRacdfgilqrstu")) != EOF)
		switch((char)ch) {
E 31
		case '1':
			Cflg = 0; break;
D 31
		case 'a':
			aflg++; break;
E 31
		case 'A':
			Aflg++; break;
I 31
		case 'C':
			Cflg = 1; break;
		case 'L':
			Lflg++; break;
		case 'F':
			Fflg++; break;
		case 'R':
			Rflg++; break;
E 36
I 36
D 37
		singlecolflag = 0;
		sortacrossflag = 0;
		nonprintflag++;
E 37
I 37
		f_nonprint = 1;
E 37
D 46
		lengthfcn = prablelen;
E 46
I 45
D 48
		(void)ioctl(1, TIOCGETP, &sgbuf);
E 48
D 47
		if (ioctl(1, TIOCGWINSZ, &win) == -1 || !win.ws_col)
			termwidth = (p = getenv("COLUMNS")) ? atoi(p) : 80;
E 47
I 47
		if (ioctl(1, TIOCGWINSZ, &win) == -1 || !win.ws_col) {
E 83
I 83
	if (isatty(STDOUT_FILENO)) {
		if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &win) == -1 ||
		    !win.ws_col) {
E 83
D 104
			if (p = getenv("COLUMNS"))
E 104
I 104
			if ((p = getenv("COLUMNS")) != NULL)
E 104
				termwidth = atoi(p);
		}
E 47
		else
			termwidth = win.ws_col;
I 51
D 83
		f_column = 1;
E 83
I 83
		f_column = f_nonprint = 1;
E 83
E 51
E 45
D 37
	} else {
		singlecolflag++;
	}
E 37
I 37
	} else
		f_singlecol = 1;
E 37

D 37
	if (getuid() == 0) {
		listallflag++;
	}
	while ((inch = getopt(argc, argv, options)) != -1) {
		switch (inch) {
E 36
		case 'a':
D 36
			aflg++; break;
E 36
I 36
			listallflag++;
			listalwaysflag++;
E 37
I 37
D 40
	/* root sees all files automatically */
E 40
I 40
D 77
	/* root is -A automatically */
E 77
I 77
	/* Root is -A automatically. */
E 77
E 40
	if (!getuid())
D 38
		f_listall = 1;
E 38
I 38
		f_listdot = 1;
E 38

I 77
D 79
	fts_options = 0;
E 79
I 79
	fts_options = FTS_PHYSICAL;
E 79
E 77
D 56
	while ((ch = getopt(argc, argv, "1ACFLRacdfgilqrstu")) != EOF) {
E 56
I 56
D 57
	while ((ch = getopt(argc, argv, "1ACFLRacdgilqrstu")) != EOF) {
E 57
I 57
D 58
	while ((ch = getopt(argc, argv, "1ACFLRacdgiklqrstu")) != EOF) {
E 58
I 58
D 67
	while ((ch = getopt(argc, argv, "1ACFLRacdfgiklqrstu")) != EOF) {
E 67
I 67
D 76
	while ((ch = getopt(argc, argv, "1ACFLRTacdfgiklqrstu")) != EOF) {
E 76
I 76
D 97
	while ((ch = getopt(argc, argv, "1ACFLRTacdfgikloqrstu")) != EOF) {
E 97
I 97
D 108
	while ((ch = getopt(argc, argv, "1ACFLRTacdfgiloqrstu")) != EOF) {
E 108
I 108
	while ((ch = getopt(argc, argv, "1ACFLRTWacdfgiloqrstu")) != EOF) {
E 108
E 97
E 76
E 67
E 58
E 57
E 56
		switch (ch) {
I 40
		/*
D 77
		 * -1, -C and -l all override each other
		 * so shell aliasing works right
E 77
I 77
		 * The -1, -C and -l options all override each other so shell
		 * aliasing works right.
E 77
		 */
E 40
		case '1':
			f_singlecol = 1;
I 40
D 51
			f_longform = 0;
E 51
I 51
			f_column = f_longform = 0;
E 51
E 40
E 37
			break;
I 37
		case 'C':
I 51
			f_column = 1;
E 51
I 40
			f_longform = f_singlecol = 0;
			break;
		case 'l':
			f_longform = 1;
E 40
D 51
			f_singlecol = 0;
E 51
I 51
			f_column = f_singlecol = 0;
E 51
			break;
I 40
D 83
		/* -c and -u override each other */
E 83
I 83
		/* The -c and -u options override each other. */
E 83
		case 'c':
			f_statustime = 1;
			f_accesstime = 0;
			break;
		case 'u':
			f_accesstime = 1;
			f_statustime = 0;
			break;
E 40
		case 'F':
			f_type = 1;
			break;
		case 'L':
D 40
			statfcn = stat;
E 40
I 40
D 79
			f_ignorelink = 1;
E 79
I 79
			fts_options &= ~FTS_PHYSICAL;
			fts_options |= FTS_LOGICAL;
E 79
E 40
			break;
		case 'R':
			f_recursive = 1;
D 40
			statfcn = lstat;
E 40
			break;
		case 'a':
I 77
			fts_options |= FTS_SEEDOT;
E 77
D 38
			f_listalways = 1;
E 38
I 38
D 79
			f_listalldot = 1;
E 79
E 38
			/* FALLTHROUGH */
E 37
		case 'A':
D 37
			listallflag++;
E 37
I 37
D 38
			f_listall = 1;
E 38
I 38
			f_listdot = 1;
E 38
E 37
			break;
I 83
		/* The -d option turns off the -R option. */
E 83
E 36
E 31
D 40
		case 'c':
D 36
			cflg++; break;
E 36
I 36
D 37
			statustimeflag++;
			modtimeflag = 0;
			accesstimeflag = 0;
E 37
I 37
			f_statustime = 1;
			f_modtime = f_accesstime = 0;
E 37
			break;
E 40
D 37
		case 'C':
			singlecolflag = 0;
			sortacrossflag = 0;
			break;
E 37
E 36
I 26
		case 'S':
			Sflg++; /* fall into... */
E 26
D 31
		case 's':
			sflg++; break;
E 31
		case 'd':
D 36
			dflg++; break;
E 36
I 36
D 37
			listdirflag++;
E 37
I 37
			f_listdir = 1;
I 83
			f_recursive = 0;
E 83
E 37
			break;
I 58
		case 'f':
			f_nosort = 1;
			break;
E 58
E 36
I 31
D 56
		case 'f':
D 36
			fflg++; break;
E 36
I 36
D 37
			longformflag = 0;
			timesortflag = 0;
			sizeflag = 0;
			reversesortflag = 0;
			listallflag++;
			listalwaysflag++;
			specialdirflag++;
E 37
I 37
			f_specialdir = 1;
E 37
			break;
E 56
D 37
		case 'F':
			fancyflag++;
			break;
E 37
E 36
E 31
D 86
		case 'g':
D 36
			gflg++; break;
E 36
I 36
D 37
			groupflag++;
E 37
I 37
			f_group = 1;
E 86
I 86
		case 'g':		/* Compatibility with 4.3BSD. */
E 86
E 37
			break;
E 36
I 31
		case 'i':
D 36
			iflg++; break;
E 36
I 36
D 37
			inodeflag++;
E 37
I 37
			f_inode = 1;
I 57
D 97
			break;
D 84
		case 'k':
			f_kblocks = 1;
E 84
I 84
		case 'k':		/* Delete before 4.4BSD. */
			(void)fprintf(stderr, "ls: -k no longer supported\n");
E 97
E 84
I 76
			break;
		case 'o':
			f_flags = 1;
E 76
E 57
E 37
			break;
E 36
E 31
D 40
		case 'l':
D 36
			lflg++; break;
E 36
I 36
D 37
			longformflag++;
			numberflag = 0;
			singlecolflag = 0;
E 37
I 37
			f_longform = 1;
D 38
			f_number = f_singlecol = 0;
E 38
I 38
			f_singlecol = 0;
E 38
E 37
			statfcn = lstat;
D 37
			if (accesstimeflag == 0 && statustimeflag == 0) {
				modtimeflag++;
			}
E 37
I 37
			if (!f_accesstime && !f_statustime)
				f_modtime = 1;
E 37
			break;
E 40
D 37
		case 'L':
			statfcn = stat;
			break;
E 37
E 36
I 31
		case 'q':
D 36
			qflg = 1; break;
E 36
I 36
D 37
			nonprintflag++;
E 37
I 37
			f_nonprint = 1;
E 37
D 46
			lengthfcn = prablelen;
E 46
			break;
E 36
E 31
		case 'r':
D 36
			rflg = -1; break;
E 36
I 36
D 37
			reversesortflag++;
E 37
I 37
			f_reversesort = 1;
E 37
			break;
D 37
		case 'R':
			recursiveflag++;
			statfcn = lstat;
			break;
E 37
E 36
I 31
		case 's':
D 36
			sflg++; break;
E 36
I 36
D 37
			sizeflag++;
E 37
I 37
			f_size = 1;
I 67
			break;
		case 'T':
			f_sectime = 1;
E 67
E 37
D 40
			statfcn = lstat;
E 40
			break;
E 36
E 31
		case 't':
D 36
			tflg++; break;
E 36
I 36
D 37
			timesortflag++;
			if (accesstimeflag == 0 && statustimeflag == 0) {
				modtimeflag++;
			}
E 37
I 37
			f_timesort = 1;
D 40
			if (!f_accesstime && !f_statustime)
				f_modtime = 1;
E 40
E 37
			break;
I 108
		case 'W':
			f_whiteout = 1;
			break;
E 108
E 36
D 40
		case 'u':
D 36
			uflg++; break;
D 31
		case 'i':
			iflg++; break;
I 16
		case 'f':
			fflg++; break;
E 16
D 15
		case 'f':
			fflg++; break;
E 15
D 5
		case 'h':
			hflg++; break;
E 5
I 5
		case 'L':
			Lflg++; break;
E 5
		case 'F':
		        Fflg++; break;
		case 'R':
		        Rflg++; break;
		}
		argc--, argv++;
E 31
I 31
		case '?':
E 36
I 36
D 37
			accesstimeflag++;
			modtimeflag = 0;
			statustimeflag = 0;
E 37
I 37
			f_modtime = f_statustime = 0;
			f_accesstime = 1;
E 37
			break;
E 40
D 37
		case '1':
			singlecolflag++;
			break;
E 37
E 36
		default:
D 36
			fputs("usage: ls [ -1ACLFRacdfgilqrstu ] [ file ]\n", stderr);
E 36
I 36
		case '?':
D 37
			(void) fprintf(stderr, "Usage: %s [-%s] [file ...]\n", argv[0], options);
E 36
			exit(1);
E 37
I 37
			usage();
E 37
E 31
D 36
	}
I 16
	if (fflg) { 
D 26
		aflg++; lflg = 0; sflg = 0; tflg = 0;
E 26
I 26
		aflg++; Sflg = 0; tflg = 0; /* -f: only turn off sort flags */
E 26
	}
E 16
D 15
	if (fflg) { 
		aflg++; lflg = 0; sflg = 0; tflg = 0;
	}
E 15
	if (lflg)
		Cflg = 0;
I 31
	argc -= optind;
	argv += optind;
E 31
	if (argc == 0) {
		argc++;
		argv = &dotp;
	}
D 31
	fp = (struct afile *)calloc(argc, sizeof (struct afile));
E 31
I 31
	fp = (struct afile *)calloc((u_int)argc, sizeof (struct afile));
E 31
	if (fp == 0) {
D 31
		fprintf(stderr, "ls: out of memory\n");
E 31
I 31
		fputs("ls: out of memory\n", stderr);
E 31
		exit(1);
	}
	fp0 = fp;
I 35
	setpassent(1);
	setgroupent(1);
E 35
	for (i = 0; i < argc; i++) {
D 2
		if (gstat(fp, *argv, 1, (int *)0) == 0)
			continue;
		fp->fname = *argv;
		fp->fflags |= ISARG;
		fp++;
E 2
I 2
		if (gstat(fp, *argv, 1, (int *)0)) {
			fp->fname = *argv;
			fp->fflags |= ISARG;
			fp++;
E 36
		}
E 2
D 36
		argv++;
	}
	fplast = fp;
	qsort(fp0, fplast - fp0, sizeof (struct afile), fcmp);
	if (dflg) {
		formatf(fp0, fplast);
		exit(0);
	}
D 15
	if (fflg)
		fp = fp0;
	else {
		for (fp = fp0; fp < fplast && fp->ftype != 'd'; fp++)
			continue;
		formatf(fp0, fp);
	}
E 15
I 15
D 16
	for (fp = fp0; fp < fplast && fp->ftype != 'd'; fp++)
		continue;
	formatf(fp0, fp);
E 16
I 16
	if (fflg)
		fp = fp0;
	else {
		for (fp = fp0; fp < fplast && fp->ftype != 'd'; fp++)
			continue;
		formatf(fp0, fp);
	}
E 16
E 15
	if (fp < fplast) {
		if (fp > fp0)
D 31
			printf("\n");
E 31
I 31
			putchar('\n');
E 31
		for (;;) {
			formatd(fp->fname, argc > 1);
			while (subdirs) {
				struct subdirs *t;
E 36
I 36
D 37
	}			/* end of option loop */
 /* do the work */
	if (argc > optind) {
		lsdir(argc - optind, &argv[optind]);
E 37
I 37
	}
I 38
	argc -= optind;
	argv += optind;
E 38

D 39
	/* -f turns off -l, -t, -s, -r, turns on -a */
E 39
I 39
D 56
	/* -f turns off -F, -R, -l, -t, -s, -r, turns on -a */
E 39
	if (f_specialdir) {
D 38
		f_longform = f_timesort = f_size = f_reversesort = 0;
		f_listall = f_listalways = 1;
E 38
I 38
D 39
		f_longform = f_timesort = f_size = f_reversesort =
		f_recursive = f_type = 0;
E 39
I 39
		f_longform = f_recursive = f_reversesort = f_size =
		f_timesort = f_type = 0;
E 39
		f_listdot = f_listalldot = 1;
E 38
	}

E 56
I 38
D 77
	/* -d turns off -R */
E 77
I 77
D 83
	/* The -d option turns off the -R option. */
E 77
	if (f_listdir)
		f_recursive = 0;

E 83
D 41
	/* if will need to stat files */
E 41
I 41
D 77
	/* if need to stat files */
E 41
D 43
	needstat = f_longform || f_recursive || f_timesort || f_size ||
	    f_inode || f_type;
E 43
I 43
D 53
	needstat = f_longform || f_recursive || f_timesort || f_size || f_type;
E 53
I 53
	f_needstat = f_longform || f_recursive || f_timesort ||
	    f_size || f_type;
E 77
I 77
D 80
	/* If options require that the files be stat'ed. */
E 80
I 80
D 81
	/* If not -F, -l -s or -t options, don't require stat information. */
E 80
D 79
	f_needstat =
	    f_longform || f_timesort || f_size || f_type;
	if (!f_needstat)
E 79
I 79
	if (!f_longform && !f_size && !f_timesort && !f_type)
E 81
I 81
D 82
	/* If not -F, -l -i, -s or -t options, don't require stat 
E 82
I 82
	/*
	 * If not -F, -i, -l, -s or -t options, don't require stat
E 82
	 * information.
	 */
D 82
	if (!f_longform && !f_size && !f_timesort && !f_type && !f_inode)
E 82
I 82
	if (!f_inode && !f_longform && !f_size && !f_timesort && !f_type)
E 82
E 81
E 79
		fts_options |= FTS_NOSTAT;
E 77
E 53
E 43

I 80
	/*
	 * If not -F, -d or -l options, follow any symbolic links listed on
	 * the command line.
	 */
	if (!f_longform && !f_listdir && !f_type)
		fts_options |= FTS_COMFOLLOW;
I 108

	/*
	 * If -W, show whiteout entries
	 */
I 109
#ifdef FTS_WHITEOUT
E 109
	if (f_whiteout)
		fts_options |= FTS_WHITEOUT;
I 109
#endif
E 109
E 108
I 84

	/* If -l or -s, figure out block size. */
	if (f_longform || f_size) {
D 98
		(void)getbsize("ls", &notused, &blocksize);
E 98
I 98
		(void)getbsize(&notused, &blocksize);
E 98
		blocksize /= 512;
	}
E 84

E 80
E 38
D 77
	/* select a sort function */
E 77
I 77
	/* Select a sort function. */
E 77
	if (f_reversesort) {
		if (!f_timesort)
			sortfcn = revnamecmp;
		else if (f_accesstime)
			sortfcn = revacccmp;
D 40
		else if (f_modtime)
			sortfcn = revmodcmp;
E 40
		else if (f_statustime)
			sortfcn = revstatcmp;
I 40
D 77
		else /* use modification time */
E 77
I 77
		else /* Use modification time. */
E 77
			sortfcn = revmodcmp;
E 40
E 37
	} else {
D 37
		char   *defname = ".";
E 37
I 37
		if (!f_timesort)
			sortfcn = namecmp;
		else if (f_accesstime)
			sortfcn = acccmp;
D 40
		else if (f_modtime)
			sortfcn = modcmp;
E 40
		else if (f_statustime)
			sortfcn = statcmp;
I 40
D 77
		else /* use modification time */
E 77
I 77
		else /* Use modification time. */
E 77
			sortfcn = modcmp;
E 40
	}
E 37
E 36

I 45
D 77
	/* select a print function */
E 77
I 77
	/* Select a print function. */
E 77
	if (f_singlecol)
		printfcn = printscol;
	else if (f_longform)
		printfcn = printlong;
D 51
	else
E 51
I 51
D 56
	else {
		/*
		 * set f_column, in case f_longform selected, then turned
		 * off by f_special.
		 */
		f_column = 1;
E 56
I 56
	else
E 56
E 51
		printfcn = printcol;
I 51
D 56
	}
E 56
E 51

I 71
D 77
	/* if -l, -d or -F, and not ignoring the link, use lstat() */
	statfcn =
	    (f_longform || f_listdir || f_type) && !f_ignorelink ? lstat : stat;
E 77
I 77
D 79
	/* If -l or -F, and not ignoring the link, use lstat(). */
	fts_options |= (f_longform || f_type) && !f_ignorelink ?
	    FTS_PHYSICAL : FTS_LOGICAL;
E 77

E 79
E 71
E 45
I 37
D 38
	if (argc > optind)
		lsdir(argc - optind, &argv[optind]);
	else {
		char *defname = ".";

E 37
D 36
				t = subdirs; subdirs = t->sd_next;
D 31
				printf("\n");
E 31
I 31
				putchar('\n');
E 31
				formatd(t->sd_name, 1);
				cfree(t->sd_name);
				cfree((char *)t);
			}
			if (++fp == fplast)
				break;
D 31
			printf("\n");
E 31
I 31
			putchar('\n');
E 31
		}
E 36
I 36
		lsdir(1, &defname);
E 36
	}
E 38
I 38
D 51
	if (argc)
E 51
I 51
D 56
	if (f_specialdir) {
		if (!argc) {
			(void)fprintf(stderr, "ls: -f requires operands.\n");
			exit(1);
		}
D 52
		for (; *argv; ++argv)
E 52
I 52
		for (;;) {
			if (argc > 1)
				(void)printf("%s:\n", *argv);
E 52
			dodir(*argv);
I 52
			if (!*++argv)
				break;
			putchar('\n');
		}
E 52
	} else if (argc)
E 51
D 44
		args(argc, argv);
E 44
I 44
		doargs(argc, argv);
E 44
	else
D 44
		curdir();
E 44
I 44
D 51
		dodot();
E 51
I 51
		dodir(".");
E 56
I 56
D 74
	if (!argc) {
I 68
D 69
		char dot[] = ".";	/* ANSI says it's not writable.*/
E 69
I 69
		static char dot[] = ".";
E 69

E 68
		argc = 1;
D 68
		argv[0] = ".";
E 68
I 68
		argv[0] = dot;
E 68
		argv[1] = NULL;
E 74
I 74
	if (argc)
D 77
		doargs(argc, argv);
E 77
I 77
		traverse(argc, argv, fts_options);
E 77
D 83
	else {
D 75
		static char *dotav[] = { ".", NULL };
E 75
I 75
		static char dot[] = ".", *dotav[] = { dot, NULL };
E 83
I 83
	else
E 83
E 75
D 77
		doargs(1, dotav);
E 77
I 77
		traverse(1, dotav, fts_options);
E 77
E 74
D 83
	}
E 83
D 74
	doargs(argc, argv);
E 74
E 56
E 51
E 44
E 38
I 37
	exit(0);
E 37
D 36
	exit(0);
E 36
}

I 83
static int output;			/* If anything output. */

E 83
D 36
formatd(name, title)
	char *name;
	int title;
E 36
I 36
D 38
/*
 * list the files in a directory
E 38
I 38
D 39
/**
 * curdir --
 *	no arguments, list the current directory; this is the
 *	most common case, so it must run labooh.
E 38
 */
E 39
D 37


E 37
D 38
extern int errno;

D 37
int     lsdir(argc, argv)
int     argc;			/* count of file names passed */
char   *argv[];			/* array of file names */

E 37
I 37
lsdir(argc, argv)
	int argc;		/* count of file names passed */
	char **argv;		/* array of file names */
E 38
I 38
D 44
curdir()
E 44
I 44
D 51
dodot()
E 51
I 51
D 56
dodir(name)
	char *name;
E 51
E 44
E 38
E 37
E 36
{
D 36
	register struct afile *fp;
	register struct subdirs *dp;
	struct afile *dfp0, *dfplast;
	int nkb;
E 36
I 36
D 37
	int     curname;
	int     goodcount = 0;
	lsstruct *stats;
	int     i;
E 37
D 38
	static char curpath[MAXPATHLEN + 1];
D 37
	char   *midpt;
E 37
I 37
	register char *p;
	LS *stats;
	int curname, entries, i, needstat, neednewline;
	char *emalloc();
E 38
I 38
	LS local, *stats;
	int num;
	char *names;
E 38
E 37
E 36

D 36
	nkb = getdir(name, &dfp0, &dfplast);
	if (dfp0 == 0)
		return;
D 15
	if (fflg == 0)
		qsort(dfp0, dfplast - dfp0, sizeof (struct afile), fcmp);
E 15
I 15
D 16
	qsort(dfp0, dfplast - dfp0, sizeof (struct afile), fcmp);
E 16
I 16
	if (fflg == 0)
		qsort(dfp0, dfplast - dfp0, sizeof (struct afile), fcmp);
E 16
E 15
	if (title)
		printf("%s:\n", name);
	if (lflg || sflg)
D 31
		printf("total %ld\n", nkb);
E 31
I 31
		printf("total %d\n", nkb);
E 31
	formatf(dfp0, dfplast);
	if (Rflg)
D 25
		for (fp = dfplast; fp >= dfp0; fp--) {
E 25
I 25
		for (fp = dfplast - 1; fp >= dfp0; fp--) {
E 25
			if (fp->ftype != 'd' ||
			    !strcmp(fp->fname, ".") ||
			    !strcmp(fp->fname, ".."))
E 36
I 36
D 37
 /* allocate memory to proceed. Lint complains, but emalloc is aligned */
	stats = (lsstruct *) emalloc((unsigned) argc * (sizeof(struct lsstruct)));
E 37
I 37
D 38
	stats = (LS *)emalloc((u_int)argc * (sizeof(LS)));
E 37

D 37
	for (curname = 0; curname < argc; ++curname) {
		if (!firsttimethruflag) {
E 37
I 37
	needstat = f_firsttime || f_longform || f_recursive || f_timesort ||
	    f_size || f_inode || f_type;
	neednewline = !f_firsttime;
E 37

D 37
		/*
		 * check for .xxx files. Note can't get listalways without
		 * listall being set
		 */
			if (argv[curname][0] == '.' && !listallflag) {
E 36
				continue;
D 36
			dp = (struct subdirs *)malloc(sizeof (struct subdirs));
			dp->sd_name = savestr(cat(name, fp->fname));
			dp->sd_next = subdirs; subdirs = dp;
E 36
I 36
			}
		/* and now for listalways: . and .. */
			if ((argv[curname][0] == '.' && argv[curname][1] == '\0') ||
					(argv[curname][0] == '.' && argv[curname][1] == '.' &&
					 argv[curname][2] == '\0')) {
				if (!listalwaysflag)
E 37
I 37
	for (entries = curname = 0; curname < argc; ++curname) {
		if (!f_firsttime) {
			/*
			 * check for .xxx files.  Note can't get listalways
			 * without listall being set.
			 */
			p = argv[curname];
			if (p[0] == '.') {
				if (!f_listall)
E 37
					continue;
D 37
			}
		}		/* end of not firsttimethru test */
		if (firsttimethruflag || longformflag || recursiveflag || timesortflag || sizeflag || inodeflag || fancyflag) {
			if (statfcn(argv[curname], &stats[goodcount].lstat) == -1) {
				if (errno == ENOENT) {
					(void) fprintf(stderr, "%s not found\n", argv[curname]);
E 37
I 37
				/* and now for listalways: . and .. */
				if ((!p[1] || p[1] == '.' && !p[2]) &&
				    !f_listalways)
E 37
					continue;
D 37
				} else {
					perror(argv[curname]);
					exit(1);
				}
			}	/* end of stat error check */
E 37
I 37
			}
E 37
E 36
		}
D 36
	for (fp = dfp0; fp < dfplast; fp++) {
		if ((fp->fflags&ISARG) == 0 && fp->fname)
			cfree(fp->fname);
		if (fp->flinkto)
			cfree(fp->flinkto);
E 36
I 36
D 37
		stats[goodcount].name = argv[curname];
		goodcount++;
	}			/* end of per name loop */

 /* sort the names */
	if (goodcount > 1 && !specialdirflag) {
		if (reversesortflag) {
			if (!timesortflag) {
				qsort((char *) stats, goodcount, sizeof(struct lsstruct), revnamecmp);
			} else {
				if (accesstimeflag) {
					qsort((char *) stats, goodcount, sizeof(struct lsstruct), revacccmp);
				} else {
					if (modtimeflag) {
						qsort((char *) stats, goodcount, sizeof(struct lsstruct), revmodcmp);
					} else {
						if (statustimeflag) {
							qsort((char *) stats, goodcount, sizeof(struct lsstruct), revstatcmp);
						} else {
						}
					}
				}
E 37
I 37
		if (needstat) {
			if (statfcn(argv[curname], &stats[entries].lstat)) {
				(void)fprintf(stderr, "ls: %s: %s\n",
				    argv[curname], strerror(errno));
				if (errno == ENOENT)
					continue;
				exit(1);
E 37
			}
D 37
		} else {
			if (!timesortflag) {
				qsort((char *) stats, goodcount, sizeof(struct lsstruct), namecmp);
			} else {
				if (accesstimeflag) {
					qsort((char *) stats, goodcount, sizeof(struct lsstruct), acccmp);
				} else {
					if (modtimeflag) {
						qsort((char *) stats, goodcount, sizeof(struct lsstruct), modcmp);
					} else {
						if (statustimeflag) {
							qsort((char *) stats, goodcount, sizeof(struct lsstruct), statcmp);
						} else {
						}
					}
				}
			}
E 37
I 37
			if (!S_ISDIR(stats[entries].lstat.st_mode))
				neednewline = 1;
E 37
		}
D 37
	}			/* end of sort conditionals */
	prindir(stats, goodcount);
E 37
I 37
		stats[entries++].name = argv[curname];
E 38
I 38
D 40
	if (statfcn(local.name = ".", &local.lstat)) {
E 40
I 40
D 51
	if (lstat(local.name = ".", &local.lstat)) {
E 51
I 51
	if (lstat(local.name = name, &local.lstat)) {
E 51
E 40
D 52
		(void)fprintf(stderr, "ls: .: %s\n", strerror(errno));
E 52
I 52
		(void)fprintf(stderr, "ls: %s: %s\n", name, strerror(errno));
E 52
D 51
		exit(1);
E 51
I 51
		return;
E 51
E 38
	}
D 38
	if (!entries)
		return;
E 37

D 37
	if ((firsttimethruflag && !listdirflag) || recursiveflag) {
		for (i = 0; i < goodcount; ++i) {
		/* recurse on directories */
			if ((stats[i].lstat.st_mode & S_IFMT) == S_IFDIR) {
			/* don't recurse on . or .. */
				if ((stats[i].name[0] == '.' && stats[i].name[1] == '\0') ||
						(stats[i].name[0] == '.' && stats[i].name[1] == '.' && stats[i].name[2] == '\0')) {
					if (!firsttimethruflag) {
						continue;
					}
				}
				if (chdir(stats[i].name) == -1) {
					perror(stats[i].name);
E 37
I 37
	if (entries > 1 && !f_specialdir)
		qsort((char *)stats, entries, sizeof(LS), sortfcn);

	prindir(stats, entries);

	if ((f_firsttime && !f_listdir) || f_recursive) {
		for (i = 0; i < entries; ++i) {
			/* recurse on directories */
			if (S_ISDIR(stats[i].lstat.st_mode)) {
				/* don't recurse on . or .. */
				p = stats[i].name;
				if (p[0] == '.' && (!p[1] ||
				    p[1] == '.' && !p[2]) &&
				    !f_firsttime)
					continue;
				if (chdir(p)) {
					(void)fprintf(stderr, "ls: %s: %s\n",
					    p, strerror(errno));
E 37
					break;
				}
D 37
				if (goodcount > 1 || !firsttimethruflag || recursiveflag) {
				/* add current name to path */
					if ((midpt = strchr(curpath, (int) '\0')) != curpath) {
						if (midpt[-1] != '/') {
							*midpt++ = '/';
						}
E 37
I 37
				if (entries > 1 ||
				    !f_firsttime || f_recursive) {
					/* add current name to path */
					p = rindex(curpath, '\0');
					if (p != curpath && p[-1] != '/')
						*p++ = '/';
					(void)strcpy(p, stats[i].name);
					if (entries > 1 || !f_firsttime) {
						if (neednewline)
							(void)putchar('\n');
						(void)printf("%s:\n",
						    curpath);
E 37
					}
D 37
					(void) strcpy(midpt, stats[i].name);

					if (goodcount > 1 || !firsttimethruflag) {
						(void) printf("\n%s:\n", curpath);
					}
E 37
				}
				recursedir(&stats[i]);
D 37
				if (goodcount > 1 || !firsttimethruflag) {
					*midpt = '\0';
E 37
I 37
				if (entries > 1 || !f_firsttime)
					*p = '\0';
				if (chdir("..")) {
					(void)fprintf(stderr, "ls: ..: %s\n",
					    strerror(errno));
					exit(1);
E 37
				}
D 37
				if (chdir("..") == -1) {
					perror(stats[i].name);
				}
E 37
			}
D 37
		}		/* end of for loop looking for directories */
		firsttimethruflag = 0;
E 37
I 37
		}
		f_firsttime = 0;
E 37
E 36
	}
D 36
	cfree((char *)dfp0);
E 36
I 36
D 37
	free((char *) stats);
E 37
I 37
	free((char *)stats);
E 38
I 38
D 44
	if (num = buildstats(&local, &stats, &names))
		ls(stats, num);
E 44
I 44
	if (num = tabdir(&local, &stats, &names))
		displaydir(stats, num);
I 51
	(void)free((char *)stats);
	(void)free((char *)names);
E 51
E 44
E 38
E 37
E 36
}

E 56
D 36
getdir(dir, pfp0, pfplast)
	char *dir;
	struct afile **pfp0, **pfplast;
E 36
I 36
D 38
/*
 * set up the call to lsdir (lsdir(count, argv-type array))
 * mutually recursive with lsdir
E 38
I 38
D 39
/**
 * args --
 *	handle arguments; this is separated out since we want to do the
 *	files first, then the directories, plus we must return to the
 *	current directory each time.
E 38
 */
E 39
I 39
D 77
static char path[MAXPATHLEN + 1];
static char *endofpath = path;
E 77
I 77
D 79
#define	IS_DDOT(name) \
	((name)[0] == '.' && ((name)[1] == '\0' || \
	    ((name)[1] == '.' && (name)[2] == '\0')))
E 77

E 79
I 77
/*
 * Traverse() walks the logical directory structure specified by the argv list
 * in the order specified by the mastercmp() comparison function.  During the
 * traversal it passes linked lists of structures to display() which represent
 * a superset (may be exact set) of the files to be displayed.
 */
E 77
I 73
D 79
static void
E 79
I 79
D 86
void
E 86
I 86
static void
E 86
E 79
E 73
E 39
D 37


E 37
D 38
recursedir(orig)
D 37
lsstruct *orig;
E 37
I 37
	LS *orig;
E 38
I 38
D 44
args(argc, argv)
E 44
I 44
D 77
doargs(argc, argv)
E 77
I 77
traverse(argc, argv, options)
	int argc, options;
	char *argv[];
{
D 104
	register FTS *ftsp;
D 94
	register FTSENT *p;
E 94
I 94
	register FTSENT *p, *chp;
E 104
I 104
	FTS *ftsp;
	FTSENT *p, *chp;
E 104
E 94
D 79
	register char *name;
E 79
D 83
	register int is_ddot;
E 83
I 83
	int ch_options;
E 83
D 86
	
E 86
I 86

E 86
	if ((ftsp =
	    fts_open(argv, options, f_nosort ? NULL : mastercmp)) == NULL)
D 88
		err(1, "fts_open: %s", strerror(errno));
E 88
I 88
D 99
		err(1, "%s", strerror(errno));
E 99
I 99
		err(1, NULL);
E 99
E 88
I 80

E 80
D 83
	display(argc, NULL, fts_children(ftsp));
E 83
I 83
	display(NULL, fts_children(ftsp, 0));
E 83
	if (f_listdir)
		return;
I 83

I 85
	/*
	 * If not recursing down this tree and don't need stat info, just get
	 * the names.
	 */
E 85
	ch_options = !f_recursive && options & FTS_NOSTAT ? FTS_NAMEONLY : 0;
I 85

E 85
E 83
D 104
	while (p = fts_read(ftsp))
E 104
I 104
	while ((p = fts_read(ftsp)) != NULL)
E 104
D 100
		switch(p->fts_info) {
E 100
I 100
		switch (p->fts_info) {
E 100
		case FTS_DC:
D 99
			err(0, "%s: directory causes a cycle", p->fts_name);
E 99
I 99
			warnx("%s: directory causes a cycle", p->fts_name);
E 99
			break;
		case FTS_DNR:
		case FTS_ERR:
I 100
D 105
			errno = p->fts_errno;
E 100
D 99
			err(0, "%s: %s",
			    p->fts_name, strerror(p->fts_errno));
E 99
I 99
			warn("%s", p->fts_name);
E 105
I 105
			warnx("%s: %s", p->fts_name, strerror(p->fts_errno));
E 105
E 99
			break;
		case FTS_D:
D 79
			name = p->fts_name;
			is_ddot = IS_DDOT(name);
			if (!is_ddot ||
			    (is_ddot && p->fts_level == FTS_ROOTLEVEL)) {
D 78
				if (name[0] == '.' && !f_listdot && !is_ddot)
E 78
I 78
				if (name[0] == '.' && !f_listdot && !is_ddot &&
				    p->fts_level != FTS_ROOTLEVEL)
E 78
					break;
				display(argc, p, fts_children(ftsp));
				if (!f_recursive)
					(void)fts_set(ftsp, p, FTS_SKIP);
			}
E 79
I 79
			if (p->fts_level != FTS_ROOTLEVEL &&
			    p->fts_name[0] == '.' && !f_listdot)
				break;
D 83
			display(argc, p, fts_children(ftsp));
E 83
I 83

			/*
			 * If already output something, put out a newline as
			 * a separator.  If multiple arguments, precede each
			 * directory with its name.
			 */
			if (output)
				(void)printf("\n%s:\n", p->fts_path);
			else if (argc > 1) {
				(void)printf("%s:\n", p->fts_path);
				output = 1;
			}

D 85
			/*
			 * If not recursing down this tree and don't need stat
			 * info, just get the names.
			 */
E 85
D 94
			display(p, fts_children(ftsp, ch_options));
E 94
I 94
			chp = fts_children(ftsp, ch_options);
			display(p, chp);
E 94

E 83
D 94
			if (!f_recursive)
E 94
I 94
			if (!f_recursive && chp != NULL)
E 94
				(void)fts_set(ftsp, p, FTS_SKIP);
E 79
			break;
		}
D 106
	(void)fts_close(ftsp);
E 106
I 106
	if (errno)
		err(1, "fts_read");
E 106
}

/*
D 83
 * Display() takes a linked list of FTSENT structures and based on the flags
 * set on the command line passes the list along with any other necessary
 * information to the print function (printfcn()).  P always points to the
 * parent directory of the display list.
E 83
I 83
D 91
 * Display() takes a linked list of FTSENT structures passes the list along
 * with any other necessary information to the print function (printfcn()).
 * P points to the parent directory of the display list.
E 91
I 91
 * Display() takes a linked list of FTSENT structures and passes the list
 * along with any other necessary information to the print function.  P
 * points to the parent directory of the display list.
E 91
E 83
 */
D 79
static void
E 79
I 79
D 86
void
E 86
I 86
static void
E 86
E 79
D 83
display(argc, p, list)
E 77
E 44
	int argc;
E 83
I 83
display(p, list)
E 83
D 77
	char **argv;
E 77
I 77
D 104
	register FTSENT *p;
	FTSENT *list;
E 104
I 104
	FTSENT *p, *list;
E 104
E 77
E 38
E 37
E 36
{
D 36
	register struct afile *fp;
	DIR *dirp;
	register struct direct *dp;
D 11
	int nkb, nent = 20;
E 11
I 11
	int nb, nent = 20;
E 36
I 36
D 37
	DIR    *dirp;
E 37
I 37
D 38
	DIR *dirp;
E 37
	struct dirent *entry;
D 37
	char   *argvblock;
	char  **argv;
	int     blocksub = 0;
	int     vsub = 0;
	int     oldfirsttimeflag;
E 37
I 37
	int blocksub, vsub, oldfirsttimeflag;
	char **argv, *argvblock, *emalloc();
E 38
I 38
D 42
	register LS *dstats, *rstats;
E 42
I 42
D 77
	register LS *dstatp, *rstatp;
I 51
	register int cnt, dircnt, maxlen, regcnt;
E 51
	LS *dstats, *rstats;
E 42
D 51
	register int cnt, dircnt, regcnt;
E 51
	struct stat sb;
D 51
	LS *stats;
D 40
	int num;
E 40
I 40
	int num, (*statfcn)(), stat(), lstat();
E 40
D 41
	char *names;
E 41
I 41
	char *names, top[MAXPATHLEN + 1];
E 51
I 51
D 71
	int (*statfcn)(), stat(), lstat();
E 71
	char top[MAXPATHLEN + 1];
	u_long blocks;
E 77
I 77
D 104
	register FTSENT *cur;
E 104
D 86
	u_long btotal;
	int entries, maxlen;
	
E 86
I 86
	struct stat *sp;
	DISPLAY d;
I 104
	FTSENT *cur;
E 104
	NAMES *np;
D 90
	u_long btotal, flen, glen, ulen;
D 89
	u_long maxblock, maxgroup, maxinode, maxlen, maxnlink, maxsize;
E 89
I 89
	u_long maxblock, maxgroup, maxinode, maxlen, maxnlink;
E 89
	u_long maxuser, maxflags;
I 89
	quad_t maxsize;
E 90
I 90
D 104
	u_long btotal, maxblock, maxinode, maxlen, maxnlink;
E 104
	u_quad_t maxsize;
I 104
	u_long btotal, maxblock, maxinode, maxlen, maxnlink;
E 104
D 91
	int flen, glen, ulen, maxflags, maxgroup, maxuser;
E 91
I 91
	int bcfile, flen, glen, ulen, maxflags, maxgroup, maxuser;
E 91
E 90
E 89
	int entries, needstats;
	char *user, *group, *flags, buf[20];	/* 32 bits == 10 digits */

E 86
	/*
	 * If list is NULL there are two possibilities: that the parent
	 * directory p has no children, or that fts_children() returned an
D 80
	 * error.  We ignore the error case since, it will be replicated
E 80
I 80
	 * error.  We ignore the error case since it will be replicated
E 80
	 * on the next call to fts_read() on the post-order visit to the
	 * directory p, and will be signalled in traverse().
	 */
D 83
	if (list == NULL && (p->fts_level != FTS_ROOTLEVEL || argc != 1)) {
		(void)printf("\n%s:\n", p->fts_path);
E 83
I 83
	if (list == NULL)
E 83
		return;
D 83
	}
E 83
E 77
E 51
E 41
E 38
E 37
E 36
E 11

I 42
D 83
	/*
D 77
	 * walk through the operands, building separate arrays of LS
	 * structures for directory and non-directory files.
E 77
I 77
	 * P can only be NULL if list is the argv list.  This list must be
	 * handled slightly differently due to the fact that there does not
	 * exist a proper parent directory and different rules apply to it.
E 77
	 */
E 83
E 42
I 37
D 38
	blocksub = vsub = 0;

E 37
D 36
	dirp = opendir(dir);
	if (dirp == NULL) {
		*pfp0 = *pfplast = NULL;
		printf("%s unreadable\n", dir);		/* not stderr! */
		return (0);
E 36
I 36
	if ((dirp = opendir(".")) == NULL) {
D 37
	/* perror(orig->name); more info, less compatible */
		(void) fprintf(stderr, "%s unreadable\n", orig->name);
E 37
I 37
		(void)fprintf(stderr, "ls: %s: %s\n",
		    orig->name, strerror(errno));
E 37
		return;
E 36
	}
D 36
	fp = *pfp0 = (struct afile *)calloc(nent, sizeof (struct afile));
	*pfplast = *pfp0 + nent;
D 11
	nkb = 0;
E 11
I 11
	nb = 0;
E 11
	while (dp = readdir(dirp)) {
		if (dp->d_ino == 0)
			continue;
		if (aflg == 0 && dp->d_name[0]=='.' &&
		    (Aflg == 0 || dp->d_name[1]==0 ||
		     dp->d_name[1]=='.' && dp->d_name[2]==0))
			continue;
D 11
		if (gstat(fp, cat(dir, dp->d_name), Fflg+Rflg, &nkb) == 0)
E 11
I 11
		if (gstat(fp, cat(dir, dp->d_name), Fflg+Rflg, &nb) == 0)
E 11
			continue;
		fp->fnum = dp->d_ino;
		fp->fname = savestr(dp->d_name);
		fp++;
		if (fp == *pfplast) {
			*pfp0 = (struct afile *)realloc((char *)*pfp0,
			    2 * nent * sizeof (struct afile));
			if (*pfp0 == 0) {
D 31
				fprintf(stderr, "ls: out of memory\n");
E 31
I 31
				fputs("ls: out of memory\n", stderr);
E 31
				exit(1);
			}
			fp = *pfp0 + nent;
			*pfplast = fp + nent;
			nent *= 2;
		}
E 36
I 36
D 37
 /* wildly overestimate dynamic amount of memory needed */
 /* lint complains about casting off_t to unsigned int. */
	argvblock = emalloc((unsigned) orig->lstat.st_size);
 /* lint also complains about this alignment.  It's OK */
	argv = (char **) emalloc((unsigned) orig->lstat.st_size);
E 37
I 37
	/* wildly overestimate dynamic amount of memory needed */
	argvblock = emalloc((u_int)orig->lstat.st_size);
	argv = (char **)emalloc((u_int)orig->lstat.st_size);
E 37

	while ((entry = readdir(dirp)) != NULL) {
D 37
		argv[vsub++] = strncpy(&argvblock[blocksub], entry->d_name, (int) entry->d_namlen);
E 37
I 37
		argv[vsub++] = strncpy(&argvblock[blocksub], entry->d_name,
		    (int)entry->d_namlen);
E 37
		blocksub += entry->d_namlen;
		argvblock[blocksub++] = '\0';
E 36
	}
D 36
	closedir(dirp);
	*pfplast = fp;
D 11
	return (nkb);
E 11
I 11
	return (kbytes(dbtob(nb)));
E 36
I 36
D 37
	(void) closedir(dirp);
E 37
I 37
	(void)closedir(dirp);
E 37

D 37
	oldfirsttimeflag = firsttimethruflag;
	firsttimethruflag = 0;
E 37
I 37
	oldfirsttimeflag = f_firsttime;
	f_firsttime = 0;
E 37

	lsdir(vsub, argv);

D 37
	firsttimethruflag = oldfirsttimeflag;
E 37
I 37
	f_firsttime = oldfirsttimeflag;
E 37

	free(argvblock);
D 37
	free((char *) argv);
E 37
I 37
	free((char *)argv);
E 37
E 36
E 11
}

D 36
int	stat(), lstat();
E 36
I 36
/*
 * print a statted (if necessary), sorted directory by listing option
 */
E 36
D 37

D 36
struct afile *
D 11
gstat(fp, file, statarg, pnkb)
E 11
I 11
gstat(fp, file, statarg, pnb)
E 11
	register struct afile *fp;
	char *file;
D 11
	int statarg, *pnkb;
E 11
I 11
	int statarg, *pnb;
E 36
I 36
int     printaname();

E 37
prindir(stats, endcount)
D 37
lsstruct stats[];		/* the statted, sorted directory */
int     endcount;

E 37
I 37
	LS *stats;		/* the statted, sorted directory */
	register int endcount;
E 37
E 36
E 11
{
D 5
	int (*statf)() = hflg ? lstat : stat;
E 5
I 5
D 11
	int (*statf)() = Lflg ? stat : lstat;
E 11
I 11
D 12
	int (*statf)() = Lflg || Fflg ? lstat : stat;
E 12
I 12
D 15
	int (*statf)() = Lflg || Fflg ? stat : lstat;
E 15
I 15
D 16
	int (*statf)() = Lflg ? lstat : stat;
E 16
I 16
D 36
	int (*statf)() = Lflg ? stat : lstat;
E 16
E 15
E 12
E 11
E 5
	char buf[BUFSIZ]; int cc;
	static struct afile azerofile;
E 36
I 36
D 37
	int     i;		/* subscript to stats */
	int     maxlen;		/* length of longest name string */
	int     colwidth;	/* width of a printing column */
	int     numcols;	/* number of columns */
	int     collength;	/* lines in longest column */
	int     base;		/* subscript for leftmost column */
	int     offset;		/* delta from base to next column */
	int     chcnt;		/* character count printed */
	long    blocks;		/* sum of blocks in longform listing */
E 37
I 37
	register int entry;
	int i;			/* subscript to stats */
	int maxlen;		/* length of longest name string */
	int colwidth;		/* width of a printing column */
	int numcols;		/* number of columns */
	int collength;		/* lines in longest column */
	int base;		/* subscript for leftmost column */
	int offset;		/* delta from base to next column */
	int chcnt;		/* character count printed */
	long blocks;		/* sum of blocks in longform listing */
E 37
E 36

D 36
	*fp = azerofile;
	fp->fflags = 0;
	fp->fnum = 0;
	fp->ftype = '-';
	if (statarg || sflg || lflg || tflg) {
D 8
		struct stat stb;
E 8
I 8
		struct stat stb, stb1;
E 36
I 36
D 37
	if (endcount <= 0) {	/* sanity check; also if only bad names given */
E 37
I 37
	if (f_singlecol) {
		for (entry = 0; entry < endcount; ++entry)
			if (!f_firsttime ||
			    !S_ISDIR(stats[entry].lstat.st_mode)) {
				(void)printaname(&stats[entry]);
				(void)putchar('\n');
			}
E 37
		return;
	}
D 37
/* don't print out a single directory name as argument first time around */
	if (!((firsttimethruflag && !listdirflag) && (endcount == 1) && ((stats[0].lstat.st_mode & S_IFMT) == S_IFDIR))) {
		if (singlecolflag) {
			for (i = 0; i < endcount; ++i) {
				(void) printaname(&stats[i]);
				(void) putchar('\n');
			}
		} else if (longformflag) {
			for (i = 0, blocks = 0; i < endcount; ++i) {
E 37
I 37

	if (f_longform) {
		if (!f_firsttime) {
			for (i = 0, blocks = 0; i < endcount; ++i)
E 37
				blocks += stats[i].lstat.st_blocks;
D 37
			}
			(void) printf("total %ld\n", blocks / 2);
			for (i = 0; i < endcount; ++i) {
				if (inodeflag) {
					(void) printf("%6d ", stats[i].lstat.st_ino);
				}
				if (sizeflag) {
					(void) printf("%4d ", stats[i].lstat.st_blocks / 2);
				}
				printperms(stats[i].lstat.st_mode);
				(void) printf("%3d ", stats[i].lstat.st_nlink);
				printowner(stats[i].lstat.st_uid);
				if (groupflag) {
					printgrp(stats[i].lstat.st_gid);
				}
				if (((stats[i].lstat.st_mode & S_IFMT) == S_IFCHR) ||
						((stats[i].lstat.st_mode & S_IFMT) == S_IFBLK)) {
					(void) printf("%3d,%4d ", major(stats[i].lstat.st_rdev), minor(stats[i].lstat.st_rdev));
				} else {
					(void) printf("%8d ", stats[i].lstat.st_size);
				}
				if (accesstimeflag) {
					printtime(stats[i].lstat.st_atime);
				} else if (statustimeflag) {
					printtime(stats[i].lstat.st_ctime);
				} else {
					printtime(stats[i].lstat.st_mtime);
				}
				(void) printf("%s", stats[i].name);
				if (fancyflag) {
					(void) printfancy(stats[i].lstat.st_mode);
				}
				if ((stats[i].lstat.st_mode & S_IFMT) == S_IFLNK) {
					char    buf[MAXPATHLEN + 1];
					int     j;
E 37
I 37
			(void)printf("total %ld\n", blocks / 2);
E 38
I 38
D 77
	dstats = rstats = NULL;
I 40
D 55
	statfcn = f_ignorelink ? stat : lstat;
E 55
I 55
D 70
	statfcn = (f_longform || f_listdir) && !f_ignorelink ? lstat : stat;
E 70
I 70
D 71
	statfcn =
	    (f_longform || f_listdir || f_type) && !f_ignorelink ? lstat : stat;
E 71
E 70
E 55
E 40
	for (dircnt = regcnt = 0; *argv; ++argv) {
D 71
		if (statfcn(*argv, &sb)) {
D 51
			(void)fprintf(stderr, "ls: %s: %s\n",
			    *argv, strerror(errno));
E 51
I 51
D 55
			(void)fprintf(stderr, "ls: %s: %s\n", *argv,
			    strerror(errno));
E 51
			if (errno == ENOENT)
				continue;
			exit(1);
E 55
I 55
			if (statfcn != stat || lstat(*argv, &sb)) {
				(void)fprintf(stderr, "ls: %s: %s\n", *argv,
				    strerror(errno));
				if (errno == ENOENT)
					continue;
				exit(1);
			}
E 71
I 71
		if (statfcn(*argv, &sb) &&
D 72
		    statfcn == stat && lstat(*argv, &sb)) {
E 72
I 72
		    (statfcn == lstat || lstat(*argv, &sb))) {
E 72
D 73
			(void)fprintf(stderr,
			    "ls: %s: %s\n", *argv, strerror(errno));
			if (errno == ENOENT)
E 73
I 73
			if (errno == ENOENT) {
				warn("%s: %s", *argv, strerror(errno));
E 77
I 77
D 86
	btotal = 0;
	maxlen = 0;
E 86
I 86
	needstats = f_inode || f_longform || f_size;
	flen = 0;
D 90
	btotal = maxblock = maxinode = maxlen = maxnlink = maxsize = 0;
E 90
I 90
	btotal = maxblock = maxinode = maxlen = maxnlink = 0;
I 91
	bcfile = 0;
E 91
E 90
	maxuser = maxgroup = maxflags = 0;
I 90
	maxsize = 0;
E 90
E 86
D 83
	if (p == NULL)
		for (cur = list, entries = 0; cur; cur = cur->fts_link) {
			if (cur->fts_info == FTS_ERR ||
D 79
			    cur->fts_errno == ENOENT ||
			    cur->fts_info == FTS_NS && f_needstat) {
E 79
I 79
			    cur->fts_info == FTS_NS) {
E 79
				err(0, "%s: %s",
				    cur->fts_name, strerror(cur->fts_errno));
				cur->fts_number = NO_PRINT;
E 77
E 73
				continue;
D 73
			exit(1);
E 73
I 73
			}
D 77
			err("%s: %s", *argv, strerror(errno));
E 73
E 71
E 55
E 38
		}
D 38
		for (i = 0; i < endcount; ++i) {
			if (f_inode)
				(void)printf("%6lu ", stats[i].lstat.st_ino);
			if (f_size)
				(void)printf("%4ld ",
				    stats[i].lstat.st_blocks / 2);
			printperms(stats[i].lstat.st_mode);
			(void)printf("%3d ", stats[i].lstat.st_nlink);
			printowner(stats[i].lstat.st_uid);
			if (f_group)
				printgrp(stats[i].lstat.st_gid);
			if (S_ISCHR(stats[i].lstat.st_mode) ||
			    S_ISBLK(stats[i].lstat.st_mode))
				(void)printf("%3d,%4d ",
				    major(stats[i].lstat.st_rdev),
				    minor(stats[i].lstat.st_rdev));
			else
				(void)printf("%8ld ", stats[i].lstat.st_size);
			if (f_accesstime)
				printtime(stats[i].lstat.st_atime);
			else if (f_statustime)
				printtime(stats[i].lstat.st_ctime);
			else
				printtime(stats[i].lstat.st_mtime);
			(void)printf("%s", stats[i].name);
			if (f_type)
				(void)printtype(stats[i].lstat.st_mode);
			if (S_ISLNK(stats[i].lstat.st_mode))
				printlink(stats[i].name);
			(void)putchar('\n');
E 38
I 38
D 51
		if (!f_specialdir && !f_listdir && S_ISDIR(sb.st_mode)) {
E 51
I 51
		if (S_ISDIR(sb.st_mode) && !f_listdir) {
E 51
			if (!dstats)
D 42
				dstats = (LS *)emalloc((u_int)argc *
E 42
I 42
D 73
				dstatp = dstats = (LS *)emalloc((u_int)argc *
E 42
				    (sizeof(LS)));
E 73
I 73
				dstatp = dstats =
				    emalloc((u_int)argc * (sizeof(LS)));
E 73
D 42
			dstats[dircnt].name = *argv;
			dstats[dircnt].lstat = sb;
E 42
I 42
			dstatp->name = *argv;
			dstatp->lstat = sb;
			++dstatp;
E 42
			++dircnt;
E 38
		}
D 38
		return;
E 38
I 38
		else {
D 51
			if (!rstats)
E 51
I 51
			if (!rstats) {
E 51
D 42
				rstats = (LS *)emalloc((u_int)argc *
E 42
I 42
D 73
				rstatp = rstats = (LS *)emalloc((u_int)argc *
E 42
				    (sizeof(LS)));
E 73
I 73
				rstatp = rstats =
				    emalloc((u_int)argc * (sizeof(LS)));
E 73
I 51
				blocks = 0;
				maxlen = -1;
E 77
I 77
			/*
			 * If cur is a directory, do not print it out now.  Its
			 * contents will be printed out when fts_read() reads
			 * it.
			 */
E 83
I 83
	for (cur = list, entries = 0; cur; cur = cur->fts_link) {
		if (cur->fts_info == FTS_ERR || cur->fts_info == FTS_NS) {
I 100
D 105
			errno = cur->fts_errno;
E 100
D 99
			err(0, "%s: %s",
			    cur->fts_name, strerror(cur->fts_errno));
E 99
I 99
			warn("%s", cur->fts_name);
E 105
I 105
			warnx("%s: %s",
			    cur->fts_name, strerror(cur->fts_errno));
E 105
E 99
			cur->fts_number = NO_PRINT;
			continue;
		}

		/*
D 86
		 * P is NULL if list is the argv list.  Different rules apply
		 * to this list.
E 86
I 86
		 * P is NULL if list is the argv list, to which different rules
		 * apply.
E 86
		 */
		if (p == NULL) {
			/* Directories will be displayed later. */
E 83
			if (cur->fts_info == FTS_D && !f_listdir) {
D 78
				cur->fts_number = NO_PRINT;
				continue;
E 77
			}
E 51
D 42
			rstats[regcnt].name = *argv;
			rstats[regcnt].lstat = sb;
E 42
I 42
D 77
			rstatp->name = *argv;
			rstatp->lstat = sb;
I 51

			/* save name length for -C format */
			rstatp->len = strlen(*argv);

E 77
I 77
			/*
			 * If file is dot file and no -a or -A is set,
			 * do not display.
			 */
			if (cur->fts_name[0] == '.' && !f_listdot) {
E 78
				cur->fts_number = NO_PRINT;
				continue;
			}
D 83
			++entries;
E 77
			if (f_nonprint)
D 77
				prcopy(*argv, *argv, rstatp->len);

			/* calculate number of blocks if -l/-s formats */
			if (f_longform || f_size)
				blocks += sb.st_blocks;

			/* save max length if -C format */
			if (f_column && maxlen < rstatp->len)
				maxlen = rstatp->len;

E 51
			++rstatp;
E 42
			++regcnt;
E 77
I 77
				prcopy(cur->fts_name, cur->fts_name,
				    cur->fts_namelen);
			if (f_column && cur->fts_namelen > maxlen)
				maxlen = cur->fts_namelen;
E 77
		}
E 38
D 77
	}
I 42
	/* display regular files */
E 42
E 37
E 36
E 8
D 38

D 36
		if ((*statf)(file, &stb) < 0) {
D 15
			fprintf(stderr, "%s not found\n", file);
			return (0);
E 15
I 15
D 16
			if (Lflg == 0 && lstat(file, &stb) < 0) {
				fprintf(stderr, "%s not found\n", file);
				return (0);
			}
E 16
I 16
D 17
			fprintf(stderr, "%s not found\n", file);
			return (0);
E 17
I 17
D 18
			if (statf == stat && lstat(file, &stb) < 0) {
E 18
I 18
			if (statf == lstat || lstat(file, &stb) < 0) {
E 18
				fprintf(stderr, "%s not found\n", file);
				return (0);
E 36
I 36
D 37
					if ((j = readlink(stats[i].name, buf, MAXPATHLEN)) == -1) {
						perror(stats[i].name);
						(void) putchar('\n');
						continue;
					}
					buf[j + 1] = '\0';
					(void) printf(" -> %s", buf);
				}
				(void) putchar('\n');
E 36
			}
E 17
E 16
E 15
D 36
		}
I 11
		fp->fblks = stb.st_blocks;
E 11
I 2
		fp->fsize = stb.st_size;
E 2
		switch (stb.st_mode & S_IFMT) {
E 36
I 36
		} else {
E 37
I 37
	/*
	 * assume tabs every 8 columns WARNING: bad code (hard coded
	 * constants) follows:
	 */
E 37
E 36

D 36
		case S_IFDIR:
			fp->ftype = 'd'; break;
		case S_IFBLK:
			fp->ftype = 'b'; fp->fsize = stb.st_rdev; break;
		case S_IFCHR:
			fp->ftype = 'c'; fp->fsize = stb.st_rdev; break;
I 7
		case S_IFSOCK:
			fp->ftype = 's'; fp->fsize = 0; break;
E 7
		case S_IFLNK:
			fp->ftype = 'l';
			if (lflg) {
				cc = readlink(file, buf, BUFSIZ);
				if (cc >= 0) {
					buf[cc] = 0;
					fp->flinkto = savestr(buf);
E 36
I 36
D 37
		/*
		 * assume tabs every 8 columns WARNING: bad code (hard coded
		 * constants) follows:
		 */
E 37
I 37
	/* figure out max width */
	maxlen = -1;
	for (i = 0; i < endcount; ++i) {
		if (maxlen < lengthfcn(stats[i].name))
			maxlen = lengthfcn(stats[i].name);
	}
E 37

D 37
		/* figure out max width */
			maxlen = 0;
			for (i = 0; i < endcount; ++i) {
				if (maxlen < lengthfcn(stats[i].name)) {
					maxlen = lengthfcn(stats[i].name);
E 36
				}
I 8
D 36
				break;
E 36
I 36
			}	/* end of determining max width of name */

		/* add fudge factors to max name length */
			if (inodeflag) {
				maxlen += 6;
E 36
			}
D 36
			if (stat(file, &stb1) < 0)
				break;
			if ((stb1.st_mode & S_IFMT) == S_IFDIR) {
				stb = stb1;
				fp->ftype = 'd';
				fp->fsize = stb.st_size;
I 11
				fp->fblks = stb.st_blocks;
E 36
I 36
			if (sizeflag) {
				maxlen += 5;
E 36
E 11
E 8
			}
D 36
			break;
		}
		fp->fnum = stb.st_ino;
		fp->fflags = stb.st_mode & ~S_IFMT;
		fp->fnl = stb.st_nlink;
		fp->fuid = stb.st_uid;
		fp->fgid = stb.st_gid;
D 2
		fp->fsize = stb.st_size;
E 2
		if (uflg)
			fp->fmtime = stb.st_atime;
		else if (cflg)
			fp->fmtime = stb.st_ctime;
		else
			fp->fmtime = stb.st_mtime;
D 11
		if (pnkb)
D 7
			if (fp->ftype != 'b' && fp->ftype != 'c')
E 7
I 7
			if (fp->ftype != 'b' && fp->ftype != 'c' &&
			    fp->ftype != 's')
E 7
				*pnkb += kbytes(fp->fsize);
E 11
I 11
		if (pnb)
			*pnb += stb.st_blocks;
E 11
	}
	return (fp);
}
E 36
I 36
			if (fancyflag) {
				maxlen += 1;
			}
			colwidth = (maxlen + 9) & ~0x7;	/* one tab after maxlen */
			numcols = (80 + colwidth - maxlen) / colwidth;
			collength = (int) ((float) endcount / (float) numcols + 0.999);
E 37
I 37
	/* add fudge factors to max name length */
	if (f_inode)
		maxlen += 6;
	if (f_size)
		maxlen += 5;
	if (f_type)
		maxlen += 1;
	/* one tab after maxlen */
	colwidth = (maxlen + 9) & ~0x7;
	numcols = (80 + colwidth - maxlen) / colwidth;
	collength = (int)((float)endcount / (float)numcols + 0.999);
E 37
E 36

D 36
formatf(fp0, fplast)
	struct afile *fp0, *fplast;
{
	register struct afile *fp;
D 31
	int width = 0, w, nentry = fplast - fp0;
	int i, j, columns, lines;
E 31
I 31
	register int i, j, w;
	int width = 0, nentry = fplast - fp0;
	int columns, lines;
E 31
	char *cp;
E 36
I 36
D 37
			for (base = 0; base < collength; base++) {
				for (offset = 0, i = 0; i < numcols; ++i, offset += collength) {
E 36

D 36
	if (fp0 == fplast)
		return;
	if (lflg || Cflg == 0)
		columns = 1;
	else {
		for (fp = fp0; fp < fplast; fp++) {
			int len = strlen(fmtentry(fp));
E 36
I 36
					if ((base + offset) >= endcount) {
						break;
					}
					chcnt = printaname(&stats[base + offset]);
E 36

D 36
			if (len > width)
				width = len;
		}
		if (usetabs)
			width = (width + 8) &~ 7;
		else
			width += 2;
D 21
		columns = 80 / width;
E 21
I 21
		columns = twidth / width;
E 21
		if (columns == 0)
			columns = 1;
	}
	lines = (nentry + columns - 1) / columns;
	for (i = 0; i < lines; i++) {
		for (j = 0; j < columns; j++) {
			fp = fp0 + j * lines + i;
			cp = fmtentry(fp);
D 31
			printf("%s", cp);
E 31
I 31
			fputs(cp, stdout);
E 31
			if (fp + lines >= fplast) {
D 31
				printf("\n");
E 31
I 31
				putchar('\n');
E 31
				break;
			}
			w = strlen(cp);
			while (w < width)
				if (usetabs) {
					w = (w + 8) &~ 7;
					putchar('\t');
				} else {
					w++;
					putchar(' ');
E 36
I 36
					if ((base + offset + collength) < endcount) {
						while (chcnt + 8 < colwidth) {
							(void) putchar('\t');
							chcnt += 8;
						}
						if (chcnt < colwidth) {
							(void) putchar('\t');
						}
						chcnt = (chcnt + 8) & ~0x7;
					}
E 37
I 37
	for (base = 0; base < collength; base++) {
		for (offset = 0, i = 0; i < numcols; ++i, offset += collength) {
			if (base + offset >= endcount)
				break;
			chcnt = printaname(&stats[base + offset]);
			if (base + offset + collength < endcount) {
				while (chcnt + 8 < colwidth) {
					(void)putchar('\t');
					chcnt += 8;
E 37
E 36
				}
I 36
D 37
				if (base + offset < endcount) {
					(void) printaname(&stats[base + offset]);
				}
				(void) printf("\n");
			}	/* end of base and offset loop */
E 37
I 37
				if (chcnt < colwidth)
					(void)putchar('\t');
				chcnt = (chcnt + 8) & ~0x7;
E 38
I 38
	if (regcnt) {
I 42
D 51
		/*
		 * for -f flag -- switch above treats all -f operands as
D 44
		 * regular files; this code uses buildstats() to read
E 44
I 44
		 * regular files; this code uses tabdir() to read
E 44
		 * them as directories.
		 */
E 42
		if (f_specialdir) {
D 42
			for (cnt = 0; cnt < regcnt; ++cnt) {
E 42
I 42
			for (cnt = regcnt; cnt--;) {
E 42
D 44
				if (num = buildstats(rstats++, &stats, &names))
					ls(stats, num);
E 44
I 44
				if (num = tabdir(rstats++, &stats, &names))
					displaydir(stats, num);
E 44
				(void)free((char *)stats);
				(void)free((char *)names);
E 38
			}
E 37
E 36
D 38
		}
I 37
		if (base + offset < endcount)
			(void)printaname(&stats[base + offset]);
		(void)printf("\n");
E 38
I 38
		} else
D 44
			ls(rstats, regcnt);
E 44
I 44
			displaydir(rstats, regcnt);
E 51
I 51
		rstats[0].lstat.st_btotal = blocks;
		rstats[0].lstat.st_maxlen = maxlen;
		displaydir(rstats, regcnt);
I 53
		f_newline = f_dirname = 1;
E 53
E 51
E 44
D 42
		if (dircnt)
			(void)putchar('\n');
E 42
E 38
E 37
	}
I 42
	/* display directories */
E 42
D 38
}

D 36
fcmp(f1, f2)
	register struct afile *f1, *f2;
E 36
I 36
/*
 * print [inode] [size] name
D 37
 * return # of characters printed
 * no trailing characters
E 37
I 37
 * return # of characters printed, no trailing characters
E 37
 */
D 37
int     printaname(entry)
lsstruct *entry;
E 37
I 37
printaname(entry)
	LS *entry;
E 37
E 36
{
I 36
D 37
	int     chcnt = 0;
E 37
I 37
	int chcnt = 0;
E 37
E 36

D 15
	if (dflg == 0 && fflg == 0) {
E 15
I 15
D 16
	if (dflg == 0) {
E 16
I 16
D 36
	if (dflg == 0 && fflg == 0) {
E 16
E 15
		if ((f1->fflags&ISARG) && f1->ftype == 'd') {
			if ((f2->fflags&ISARG) == 0 || f2->ftype != 'd')
				return (1);
		} else {
			if ((f2->fflags&ISARG) && f2->ftype == 'd')
				return (-1);
		}
E 36
I 36
D 37
	if (inodeflag) {
		chcnt += printf("%5d ", entry->lstat.st_ino);
E 36
	}
D 36
	if (tflg) {
		if (f2->fmtime == f1->fmtime)
			return (0);
		if (f2->fmtime > f1->fmtime)
I 26
			return (rflg);
		return (-rflg);
	}
	if (Sflg) {
		if (f2->fsize == f1->fsize)
			return (0);
		if (f2->fsize > f1->fsize)
E 26
			return (rflg);
		return (-rflg);
E 36
I 36
	if (sizeflag) {
		chcnt += printf("%4d ", entry->lstat.st_blocks / 2);
E 36
	}
E 37
I 37
	if (f_inode)
		chcnt += printf("%5lu ", entry->lstat.st_ino);
	if (f_size)
		chcnt += printf("%4ld ", entry->lstat.st_blocks / 2);
E 37
D 36
	return (rflg * strcmp(f1->fname, f2->fname));
E 36
I 36
	chcnt += printf("%s", entry->name);
D 37

	if (fancyflag) {
		return (chcnt + printfancy(entry->lstat.st_mode));
	}
	return chcnt;
E 37
I 37
	if (f_type)
		chcnt += printtype(entry->lstat.st_mode);
	return(chcnt);
E 37
E 36
}

D 36
char *
cat(dir, file)
	char *dir, *file;
E 36
I 36
/*
 * print group and user name
 */
D 37



printgrp(groupid)
short   groupid;
E 37
I 37
printgrp(gid)
	gid_t gid;
E 37
E 36
{
D 36
	static char dfile[BUFSIZ];
I 31
	register int dlen;
E 36
I 36
	struct group *groupentry;
E 36
E 31

D 31
	if (strlen(dir)+1+strlen(file)+1 > BUFSIZ) {
		fprintf(stderr, "ls: filename too long\n");
E 31
I 31
D 36
	if ((dlen = strlen(dir))+1+strlen(file)+1 > BUFSIZ) {
		fputs("ls: filename too long\n", stderr);
E 31
		exit(1);
E 36
I 36
D 37
	if ((groupentry = getgrgid((int) groupid)) == NULL) {
	/* can't find group, print out number instead */
		(void) printf("%-9d ", groupid);
E 37
I 37
	if ((groupentry = getgrgid((int)gid)) == NULL) {
		/* can't find group, print out number instead */
		(void)printf("%-9u ", gid);
E 37
		return;
E 38
I 38
	if (dircnt) {
I 39
		register char *p;

I 53
		f_total = 1;
E 53
E 39
D 41
		if (dircnt > 1)
E 41
I 41
		if (dircnt > 1) {
			(void)getwd(top);
E 41
			qsort((char *)dstats, dircnt, sizeof(LS), sortfcn);
I 53
			f_dirname = 1;
E 53
D 39
		for (cnt = 0; cnt < dircnt; ++cnt)
E 39
I 39
D 41
		for (cnt = 0; cnt < dircnt; ++cnt) {
E 41
I 41
		}
		for (cnt = 0; cnt < dircnt; ++dstats) {
E 41
			for (endofpath = path, p = dstats->name;
			    *endofpath = *p++; ++endofpath);
E 39
D 41
			ls_dir(dstats++, cnt, regcnt || dircnt > 1);
E 41
I 41
D 42
			ls_dir(dstats, cnt, regcnt || dircnt > 1);
E 42
I 42
D 44
			ls_dir(dstats, regcnt, regcnt || dircnt > 1);
E 44
I 44
D 50
			subdir(dstats, regcnt, regcnt || dircnt > 1);
E 50
I 50
D 53
			subdir(dstats, regcnt || cnt, regcnt || dircnt > 1);
E 53
I 53
			subdir(dstats);
			f_newline = 1;
E 53
E 50
E 44
E 42
D 73
			if (++cnt < dircnt && chdir(top)) {
				(void)fprintf(stderr, "ls: %s: %s\n",
				    top, strerror(errno));
				exit(1);
			}
E 73
I 73
			if (++cnt < dircnt && chdir(top))
				err("%s: %s", top, strerror(errno));
E 73
E 41
I 39
		}
E 39
E 38
E 36
	}
D 31
	if (!strcmp(dir, "") || !strcmp(dir, ".")) {
		(void) strcpy(dfile, file);
		return (dfile);
	}
E 31
I 31
D 36
	if (!dir[0] || dir[0] == '.' && !dir[1])
		return(strcpy(dfile, file));
E 31
	(void) strcpy(dfile, dir);
D 31
	if (dir[strlen(dir) - 1] != '/' && *file != '/')
		(void) strcat(dfile, "/");
	(void) strcat(dfile, file);
E 31
I 31
	if (dir[dlen - 1] != '/' && *file != '/')
		dfile[dlen++] = '/';
	(void) strcpy(dfile + dlen, file);
E 31
	return (dfile);
E 36
I 36
D 37
	(void) printf("%-9s", groupentry->gr_name);
	(void) getgrent();	/* to rewind group file */
E 37
I 37
D 38
	(void)printf("%-9s", groupentry->gr_name);
	(void)getgrent();		/* to rewind group file */
E 38
I 38
D 42
#ifdef whybother
	(void)free((char *)rstats);
	(void)free((char *)dstats);
#endif
E 42
E 38
E 37
E 36
}

I 73
static void
E 73
D 36
char *
savestr(str)
	char *str;
E 36
I 36
D 37

E 37
D 38
printowner(uid)
D 37
short   uid;
E 37
I 37
	uid_t uid;
E 38
I 38
D 44
ls(stats, num)
E 44
I 44
displaydir(stats, num)
E 44
	LS *stats;
	register int num;
E 38
E 37
E 36
{
D 36
	char *cp = malloc(strlen(str) + 1);
E 36
I 36
D 38
	struct passwd *pwentry;
E 38
I 38
D 39
	register char *p;
E 39
I 39
	register char *p, *savedpath;
E 39
	LS *lp;
I 46
D 49
	u_long save;
E 49
E 46
E 38
E 36

D 36
	if (cp == NULL) {
D 31
		fprintf(stderr, "ls: out of memory\n");
E 31
I 31
		fputs("ls: out of memory\n", stderr);
E 31
		exit(1);
E 36
I 36
D 37
	if ((pwentry = getpwuid((int) uid)) == NULL) {
	/* can't find owner, print out number instead */
		(void) printf("%-9d ", uid);
E 37
I 37
D 38
	if ((pwentry = getpwuid((int)uid)) == NULL) {
		/* can't find owner, print out number instead */
		(void)printf("%-9u ", uid);
E 37
		return;
E 36
	}
D 31
	(void) strcpy(cp, str);
	return (cp);
E 31
I 31
D 36
	return(strcpy(cp, str));
E 36
I 36
D 37
	(void) printf("%-9s", pwentry->pw_name);
	(void) getpwent();
E 37
I 37
	(void)printf("%-9s", pwentry->pw_name);
	(void)getpwent();
E 37
E 36
E 31
}
E 38
I 38
D 46
	if (num > 1 && !f_specialdir)
E 46
I 46
D 56
	if (num > 1 && !f_specialdir) {
E 56
I 56
D 58
	if (num > 1) {
E 58
I 58
	if (num > 1 && !f_nosort) {
E 58
E 56
D 49
		save = stats[0].lstat.st_flags;
E 49
I 49
		u_long save1, save2;

		save1 = stats[0].lstat.st_btotal;
		save2 = stats[0].lstat.st_maxlen;
E 49
E 46
		qsort((char *)stats, num, sizeof(LS), sortfcn);
I 46
D 49
		stats[0].lstat.st_flags = save;
E 49
I 49
		stats[0].lstat.st_btotal = save1;
		stats[0].lstat.st_maxlen = save2;
E 49
	}
E 46
E 38

D 36
char	*fmtinum(), *fmtsize(), *fmtlstuff(), *fmtmode();
E 36
I 36
D 37
#define SIXMONTHS 6l*30l*24l*3600l
time_t  time();
E 37
I 37
D 38
#define	SIXMONTHS	((DAYSPERNYEAR / 2) * SECSPERDAY)
time_t time();
E 38
I 38
D 45
	printdir(stats, num);
E 45
I 45
	printfcn(stats, num);
E 45
E 38
E 37
E 36

D 36
char *
fmtentry(fp)
	register struct afile *fp;
E 36
I 36
D 38
printtime(ftime)
D 37
time_t  ftime;
E 37
I 37
	time_t ftime;
E 37
E 36
{
D 36
	static char fmtres[BUFSIZ];
	register char *cp, *dp;
E 36
I 36
D 37
	int     i;
	char   *longstring;
E 37
I 37
	int i;
	char *longstring;
E 37
E 36

D 4
	(void) sprintf(fmtres, "%s%s%s%s",
E 4
I 4
D 36
	(void) sprintf(fmtres, "%s%s%s",
E 4
	    iflg ? fmtinum(fp) : "",
	    sflg ? fmtsize(fp) : "",
	    lflg ? fmtlstuff(fp) : "");
	dp = &fmtres[strlen(fmtres)];
	for (cp = fp->fname; *cp; cp++)
		if (qflg && (*cp < ' ' || *cp >= 0177))
			*dp++ = '?';
		else
			*dp++ = *cp;
	if (Fflg) {
		if (fp->ftype == 'd')
			*dp++ = '/';
I 3
		else if (fp->ftype == 'l')
			*dp++ = '@';
I 7
		else if (fp->ftype == 's')
			*dp++ = '=';
E 7
E 3
		else if (fp->fflags & 0111)
			*dp++ = '*';
E 36
I 36
D 37
	longstring = ctime((long *) &ftime);
E 37
I 37
	longstring = ctime((long *)&ftime);
	for (i = 4; i < 11; ++i)
		(void)putchar(longstring[i]);
E 37

D 37
	for (i = 4; i < 11; ++i) {
		(void) putchar(longstring[i]);
E 37
I 37
	if (ftime + SIXMONTHS > time((time_t *)NULL))
		for (i = 11; i < 16; ++i)
			(void)putchar(longstring[i]);
	else {
		(void)putchar(' ');
		for (i = 20; i < 24; ++i)
			(void)putchar(longstring[i]);
E 37
E 36
	}
D 36
	if (lflg && fp->flinkto) {
		(void) strcpy(dp, " -> "); dp += 4;
		for (cp = fp->flinkto; *cp; cp++)
			if (qflg && (*cp < ' ' || *cp >= 0177))
				*dp++ = '?';
			else
				*dp++ = *cp;
E 36
I 36
D 37

	if (ftime + SIXMONTHS > time((time_t *) NULL)) {
		for (i = 11; i < 16; ++i) {
			(void) putchar(longstring[i]);
		}
	} else {
		(void) putchar(' ');
		for (i = 20; i < 24; ++i) {
			(void) putchar(longstring[i]);
		}
E 36
	}
D 36
	*dp++ = 0;
	return (fmtres);
E 36
I 36
	(void) putchar(' ');
E 37
I 37
	(void)putchar(' ');
E 38
I 38
D 39
	if (f_recursive)
E 39
I 39
	if (f_recursive) {
		savedpath = endofpath;
E 39
		for (lp = stats; num--; ++lp) {
			if (!S_ISDIR(lp->lstat.st_mode))
E 77
I 77
	else {
		if (p->fts_level != FTS_ROOTLEVEL || argc != 1)
			(void)printf("\n%s:\n", p->fts_path);
		
		for (cur = list, entries = 0; cur; cur = cur->fts_link) {
			if (cur->fts_info == FTS_ERR ||
D 79
			    cur->fts_errno == ENOENT ||
			    cur->fts_info == FTS_NS && f_needstat) {
E 79
I 79
			    cur->fts_info == FTS_NS) {
E 79
				err(0, "%s: %s",
				    cur->fts_name, strerror(cur->fts_errno));
				cur->fts_number = NO_PRINT;
E 77
				continue;
D 77
			p = lp->name;
			if (p[0] == '.' && (!p[1] || p[1] == '.' && !p[2]))
E 77
I 77
			}
D 79
			/*
			 * If file is dot file and no -a or -A is set,
			 * do not display.
			 */
E 79
I 79
			/* Don't display dot file if -a/-A not set. */
E 83
I 83
		} else {
			/* Only display dot file if -a/-A set. */
E 83
E 79
			if (cur->fts_name[0] == '.' && !f_listdot) {
				cur->fts_number = NO_PRINT;
E 77
				continue;
I 39
D 77
			if (endofpath != path && endofpath[-1] != '/')
				*endofpath++ = '/';
			for (; *endofpath = *p++; ++endofpath);
E 39
D 44
			ls_dir(lp, 1, 1);
E 44
I 44
D 53
			subdir(lp, 1, 1);
E 53
I 53
			f_newline = f_dirname = f_total = 1;
			subdir(lp);
E 53
E 44
I 39
			*(endofpath = savedpath) = '\0';
E 77
I 77
			}
D 83
			++entries;
			if (f_nonprint)
				prcopy(cur->fts_name, cur->fts_name,
				       cur->fts_namelen);
			if (f_column && cur->fts_namelen > maxlen)
				maxlen = cur->fts_namelen;
E 83
D 86
			
			if (f_longform || f_size)
				btotal += cur->fts_statp->st_blocks;
E 86
E 77
E 39
		}
I 83
		if (f_nonprint)
			prcopy(cur->fts_name, cur->fts_name, cur->fts_namelen);
D 86
		if (f_column && cur->fts_namelen > maxlen)
E 86
I 86
		if (cur->fts_namelen > maxlen)
E 86
			maxlen = cur->fts_namelen;
I 86
		if (needstats) {
			sp = cur->fts_statp;
			if (sp->st_blocks > maxblock)
				maxblock = sp->st_blocks;
			if (sp->st_ino > maxinode)
				maxinode = sp->st_ino;
			if (sp->st_nlink > maxnlink)
				maxnlink = sp->st_nlink;
			if (sp->st_size > maxsize)
				maxsize = sp->st_size;

			btotal += sp->st_blocks;
			if (f_longform) {
				user = user_from_uid(sp->st_uid, 0);
				if ((ulen = strlen(user)) > maxuser)
					maxuser = ulen;
				group = group_from_gid(sp->st_gid, 0);
				if ((glen = strlen(group)) > maxgroup)
					maxgroup = glen;
				if (f_flags) {
D 95
					flags = flags_from_fid(sp->st_flags);
E 95
I 95
					flags =
					    flags_to_string(sp->st_flags, "-");
E 95
					if ((flen = strlen(flags)) > maxflags)
						maxflags = flen;
				} else
					flen = 0;

				if ((np = malloc(sizeof(NAMES) +
				    ulen + glen + flen + 3)) == NULL)
D 99
					err(1, "%s", strerror(errno));
E 99
I 99
					err(1, NULL);
E 99

				np->user = &np->data[0];
				(void)strcpy(np->user, user);
				np->group = &np->data[ulen + 1];
				(void)strcpy(np->group, group);

I 91
				if (S_ISCHR(sp->st_mode) ||
				    S_ISBLK(sp->st_mode))
					bcfile = 1;

E 91
				if (f_flags) {
					np->flags = &np->data[ulen + glen + 2];
				  	(void)strcpy(np->flags, flags);
				}
				cur->fts_pointer = np;
			}
		}
E 86
		++entries;
E 83
I 39
	}
E 39
E 38
E 37
E 36
D 77
}
E 77

I 73
D 77
static void
E 73
D 36
char *
fmtinum(p)
	register struct afile *p;
{
	static char inumbuf[8];
E 36
I 36
D 38
/*
 * act like strlen, but also translate non-printing chars to '?'
 */
E 36
D 37

D 27
	(void) sprintf(inumbuf, "%5d ", p->fnum);
E 27
I 27
D 31
	(void) sprintf(inumbuf, "%6d ", p->fnum);
E 31
I 31
D 36
	(void) sprintf(inumbuf, "%6ld ", p->fnum);
E 31
E 27
	return (inumbuf);
}
E 36

D 36
char *
fmtsize(p)
	register struct afile *p;
E 36
I 36
int     prablelen(cp)
char   *cp;
E 37
I 37
prablelen(cp)
	char *cp;
E 38
I 38
D 44
ls_dir(lp, newline, tag)
E 44
I 44
D 53
subdir(lp, newline, tag)
E 53
I 53
subdir(lp)
E 53
E 44
	LS *lp;
D 53
	int newline, tag;
E 53
E 38
E 37
E 36
{
D 36
	static char sizebuf[32];
E 36
I 36
D 38
	register int len = 0;
E 38
I 38
D 39
	static char path[MAXPATHLEN + 1];
	register char *p;
E 39
	LS *stats;
	int num;
D 39
	char *endofname, *names;
E 39
I 39
	char *names;
E 39
E 38
E 36

I 42
D 53
	/*
	 * this doesn't really belong here, but it's the only place that
	 * everybody goes through; the `tag' variable is so that we don't
	 * print the header for directories unless we're going to display
	 * more directories, or we've already displayed files or directories.
	 * The `newline' variable keeps us from inserting a newline before
	 * we've displayed anything at all.
	 */
E 42
D 11
	switch (p->ftype) {

	case 'b':
	case 'c':
I 7
	case 's':
E 7
		(void) sprintf(sizebuf, "%4ld ", 0);
		break;

	default:
		(void) sprintf(sizebuf, "%4ld ", kbytes(p->fsize));
		break;
	}
E 11
I 11
D 36
	(void) sprintf(sizebuf, "%4ld ", kbytes(dbtob(p->fblks)));
E 11
	return (sizebuf);
E 36
I 36
D 37
	while (*cp != '\0') {
		if (!isprint(*cp)) {
E 37
I 37
D 38
	for (; *cp; ++len, ++cp)
		if (!isprint(*cp))
E 37
			*cp = '?';
D 37
		}
		++len;
		++cp;
	}
	return len;
E 37
I 37
	return(len);
E 37
E 36
}
E 38
I 38
D 39
	/* add current name to path */
	p = index(path, '\0');
	if (p != path && p[-1] != '/')
		*p++ = '/';
	(void)strcpy(p, lp->name);
	endofname = p;
E 38

E 39
D 36
char *
fmtlstuff(p)
	register struct afile *p;
E 36
I 36
D 38
/*
 * do the permissions printing, passed the mode
 */
D 37

E 37
printperms(mode)
D 37
u_short mode;
E 37
I 37
	mode_t mode;
E 37
E 36
{
D 36
	static char lstuffbuf[256];
	char gname[32], uname[32], fsize[32], ftime[32];
	register char *lp = lstuffbuf;
E 36
I 36
D 37
 /* print type */
E 37
I 37
	 /* print type */
E 37
	switch (mode & S_IFMT) {
D 37
	case S_IFDIR:		/* directory */
		(void) putchar('d');
E 37
I 37
	case S_IFDIR:			/* directory */
		(void)putchar('d');
E 37
		break;
D 37
	case S_IFCHR:		/* character special */
		(void) putchar('c');
E 37
I 37
	case S_IFCHR:			/* character special */
		(void)putchar('c');
E 37
		break;
D 37
	case S_IFBLK:		/* block special */
		(void) putchar('b');
E 37
I 37
	case S_IFBLK:			/* block special */
		(void)putchar('b');
E 37
		break;
D 37
	case S_IFREG:		/* regular */
		(void) putchar('-');
E 37
I 37
	case S_IFREG:			/* regular */
		(void)putchar('-');
E 37
		break;
D 37
	case S_IFLNK:		/* symbolic link */
		(void) putchar('l');
E 37
I 37
	case S_IFLNK:			/* symbolic link */
		(void)putchar('l');
E 37
		break;
D 37
	case S_IFSOCK:		/* socket */
		(void) putchar('s');
E 37
I 37
	case S_IFSOCK:			/* socket */
		(void)putchar('s');
E 37
		break;
#ifdef S_IFIFO
D 37
	case S_IFIFO:		/* fifo */
		(void) putchar('p');
E 37
I 37
	case S_IFIFO:			/* fifo */
		(void)putchar('p');
E 37
		break;
#endif
D 37
	default:		/* unknown */
		(void) putchar('?');
E 37
I 37
	default:			/* unknown */
		(void)putchar('?');
E 37
		break;
	}
D 37
 /* usr */
	if (mode & S_IRUSR) {
		(void) putchar('r');
	} else {
		(void) putchar('-');
	}
	if (mode & S_IWUSR) {
		(void) putchar('w');
	} else {
		(void) putchar('-');
	}
E 37
I 37
	/* usr */
	if (mode & S_IRUSR)
		(void)putchar('r');
	else
		(void)putchar('-');
	if (mode & S_IWUSR)
		(void)putchar('w');
	else
		(void)putchar('-');
E 37
	switch (mode & (S_IXUSR | S_ISUID)) {
	case 0:
D 37
		(void) putchar('-');
E 37
I 37
		(void)putchar('-');
E 37
		break;
	case S_IXUSR:
D 37
		(void) putchar('x');
E 37
I 37
		(void)putchar('x');
E 37
		break;
	case S_ISUID:
D 37
		(void) putchar('S');
E 37
I 37
		(void)putchar('S');
E 37
		break;
	case S_IXUSR | S_ISUID:
D 37
		(void) putchar('s');
E 37
I 37
		(void)putchar('s');
E 37
		break;
	}
D 37
 /* group */
	if (mode & S_IRGRP) {
		(void) putchar('r');
	} else {
		(void) putchar('-');
	}
	if (mode & S_IWGRP) {
		(void) putchar('w');
	} else {
		(void) putchar('-');
	}
E 37
I 37
	/* group */
	if (mode & S_IRGRP)
		(void)putchar('r');
	else
		(void)putchar('-');
	if (mode & S_IWGRP)
		(void)putchar('w');
	else
		(void)putchar('-');
E 37
	switch (mode & (S_IXGRP | S_ISGID)) {
	case 0:
D 37
		(void) putchar('-');
E 37
I 37
		(void)putchar('-');
E 37
		break;
	case S_IXGRP:
D 37
		(void) putchar('x');
E 37
I 37
		(void)putchar('x');
E 37
		break;
	case S_ISGID:
D 37
		(void) putchar('S');
E 37
I 37
		(void)putchar('S');
E 37
		break;
	case S_IXGRP | S_ISGID:
D 37
		(void) putchar('s');
E 37
I 37
		(void)putchar('s');
E 37
		break;
	}
D 37
 /* other */
	if (mode & S_IROTH) {
		(void) putchar('r');
	} else {
		(void) putchar('-');
	}
	if (mode & S_IWOTH) {
		(void) putchar('w');
	} else {
		(void) putchar('-');
	}
E 37
I 37
	/* other */
	if (mode & S_IROTH)
		(void)putchar('r');
	else
		(void)putchar('-');
	if (mode & S_IWOTH)
		(void)putchar('w');
	else
		(void)putchar('-');
E 37
	switch (mode & (S_IXOTH | S_ISVTX)) {
	case 0:
D 37
		(void) putchar('-');
E 37
I 37
		(void)putchar('-');
E 37
		break;
	case S_IXOTH:
D 37
		(void) putchar('x');
E 37
I 37
		(void)putchar('x');
E 37
		break;
	case S_ISVTX:
D 37
		(void) putchar('T');
E 37
I 37
		(void)putchar('T');
E 37
		break;
	case S_IXOTH | S_ISVTX:
D 37
		(void) putchar('t');
E 37
I 37
		(void)putchar('t');
E 37
		break;
	}
}
E 38
I 38
	if (newline)
E 53
I 53
	if (f_newline)
E 53
		(void)putchar('\n');
D 53
	if (tag)
E 53
I 53
	if (f_dirname)
E 53
		(void)printf("%s:\n", path);
E 38
E 36

D 36
	/* type mode uname gname fsize ftime */
/* get uname */
	{ char *cp = getname(p->fuid);
	  if (cp)
		(void) sprintf(uname, "%-9.9s", cp);
	  else
D 31
		(void) sprintf(uname, "%-9d", p->fuid);
E 31
I 31
		(void) sprintf(uname, "%-9u", p->fuid);
E 36
I 36
D 37
int     printfancy(mode)
u_short mode;
E 37
I 37
D 38
printtype(mode)
	mode_t mode;
E 37
{
D 37
	if ((mode & S_IFMT) == S_IFDIR) {
		(void) putchar('/');
		return 1;
E 37
I 37
	switch(mode & S_IFMT) {
	case S_IFDIR:
		(void)putchar('/');
		return(1);
	case S_IFLNK:
		(void)putchar('@');
		return(1);
	case S_IFSOCK:
		(void)putchar('=');
		return(1);
E 38
I 38
	if (chdir(lp->name)) {
D 54
		(void)fprintf(stderr, "ls: %s: %s\n",
		    lp->name, strerror(errno));
E 54
I 54
D 73
		(void)fprintf(stderr, "ls: %s: %s\n", lp->name,
		     strerror(errno));
E 73
I 73
		warn("%s: %s", lp->name, strerror(errno));
E 73
E 54
		return;
E 38
E 37
E 36
E 31
	}
D 36
/* get gname */
	if (gflg) {
	  char *cp = getgroup(p->fgid);
	  if (cp)
		(void) sprintf(gname, "%-9.9s", cp);
	  else
D 31
		(void) sprintf(gname, "%-9d", p->fgid);
E 31
I 31
		(void) sprintf(gname, "%-9u", p->fgid);
E 36
I 36
D 37
	if ((mode & S_IFMT) == S_IFLNK && !longformflag) {
		(void) putchar('@');
		return 1;
E 36
E 31
	}
D 36
/* get fsize */
	if (p->ftype == 'b' || p->ftype == 'c')
		(void) sprintf(fsize, "%3d,%4d",
		    major(p->fsize), minor(p->fsize));
I 7
	else if (p->ftype == 's')
D 31
		(void) sprintf(fsize, "%8ld", 0);
E 31
I 31
		(void) sprintf(fsize, "%8ld", 0L);
E 31
E 7
	else
		(void) sprintf(fsize, "%8ld", p->fsize);
/* get ftime */
	{ char *cp = ctime(&p->fmtime);
	  if ((p->fmtime < sixmonthsago) || (p->fmtime > now))
		(void) sprintf(ftime, " %-7.7s %-4.4s ", cp+4, cp+20);
	  else
		(void) sprintf(ftime, " %-12.12s ", cp+4);
E 36
I 36
	if ((mode & S_IFMT) == S_IFSOCK) {
		(void) putchar('=');
		return 1;
E 36
	}
E 37
D 36
/* splat */
	*lp++ = p->ftype;
	lp = fmtmode(lp, p->fflags);
	(void) sprintf(lp, "%3d %s%s%s%s",
	    p->fnl, uname, gflg ? gname : "", fsize, ftime);
	return (lstuffbuf);
E 36
I 36
D 38
	if (mode & (S_IXUSR | S_IXGRP | S_IXOTH)) {
D 37
		(void) putchar('*');
		return 1;
E 37
I 37
		(void)putchar('*');
		return(1);
E 37
	}
D 37
	return 0;
E 37
I 37
	return(0);
E 37
E 36
}
E 38
I 38
D 44
	if (num = buildstats(lp, &stats, &names))
		ls(stats, num);
E 44
I 44
D 60
	if (num = tabdir(lp, &stats, &names))
E 60
I 60
	if (num = tabdir(lp, &stats, &names)) {
E 60
		displaydir(stats, num);
E 44
E 38
D 39

D 36
int	m1[] = { 1, S_IREAD>>0, 'r', '-' };
int	m2[] = { 1, S_IWRITE>>0, 'w', '-' };
D 32
int	m3[] = { 2, S_ISUID, 's', S_IEXEC>>0, 'x', '-' };
E 32
I 32
int	m3[] = { 3, S_ISUID|(S_IEXEC>>0), 's', S_ISUID, 'S', S_IEXEC>>0, 'x', '-' };
E 32
int	m4[] = { 1, S_IREAD>>3, 'r', '-' };
int	m5[] = { 1, S_IWRITE>>3, 'w', '-' };
D 32
int	m6[] = { 2, S_ISGID, 's', S_IEXEC>>3, 'x', '-' };
E 32
I 32
int	m6[] = { 3, S_ISGID|(S_IEXEC>>3), 's', S_ISGID, 'S', S_IEXEC>>3, 'x', '-' };
E 32
int	m7[] = { 1, S_IREAD>>6, 'r', '-' };
int	m8[] = { 1, S_IWRITE>>6, 'w', '-' };
D 32
int	m9[] = { 2, S_ISVTX, 't', S_IEXEC>>6, 'x', '-' };
E 32
I 32
int	m9[] = { 3, S_ISVTX|(S_IEXEC>>6), 't', S_ISVTX, 'T', S_IEXEC>>6, 'x', '-' };
E 36
I 36
D 37
/*
 * error checks for dynamic memory;
 * comparison routines for various calls to qsort(3)
 */
E 37
I 37
D 38
printlink(name)
	char *name;
{
	char path[MAXPATHLEN + 1];
	int lnklen;
E 37
E 36
E 32

D 36
int	*m[] = { m1, m2, m3, m4, m5, m6, m7, m8, m9};
E 36
I 36
D 37
int     namecmp(a, b)
lsstruct *a, *b;
E 37
I 37
	if ((lnklen = readlink(name, path, MAXPATHLEN)) == -1) {
		(void)fprintf(stderr, "\nls: %s: %s\n", name, strerror(errno));
		return;
E 38
I 38
	*endofname = '\0';
E 39
D 60
	(void)free((char *)stats);
	(void)free((char *)names);
E 60
I 60
D 73
		(void)free((char *)stats);
		(void)free((char *)names);
E 73
I 73
		free(stats);
		free(names);
E 73
	}
E 60
D 73
	if (chdir("..")) {
		(void)fprintf(stderr, "ls: ..: %s\n", strerror(errno));
		exit(1);
E 38
	}
E 73
I 73
	if (chdir(".."))
		err("..: %s", strerror(errno));
E 77
I 77
D 83
	if (entries)
E 83
I 83
D 86
	if (entries) {
E 83
		printfcn(list, entries, btotal, maxlen);
I 83
		output = 1;
E 86
I 86
	if (!entries)
		return;

	d.list = list;
	d.entries = entries;
	d.maxlen = maxlen;
	if (needstats) {
I 91
		d.bcfile = bcfile;
E 91
		d.btotal = btotal;
D 90
		d.s_block = snprintf(buf, sizeof(buf), "%d", maxblock);
E 90
I 90
D 93
		d.s_block = snprintf(buf, sizeof(buf), "%lu", maxblock);
E 93
I 93
		(void)snprintf(buf, sizeof(buf), "%lu", maxblock);
		d.s_block = strlen(buf);
E 93
E 90
		d.s_flags = maxflags;
		d.s_group = maxgroup;
D 90
		d.s_inode = snprintf(buf, sizeof(buf), "%d", maxinode);
		d.s_nlink = snprintf(buf, sizeof(buf), "%d", maxnlink);
		d.s_size = snprintf(buf, sizeof(buf), "%d", maxsize);
E 90
I 90
D 93
		d.s_inode = snprintf(buf, sizeof(buf), "%lu", maxinode);
		d.s_nlink = snprintf(buf, sizeof(buf), "%lu", maxnlink);
		d.s_size = snprintf(buf, sizeof(buf), "%qu", maxsize);
E 93
I 93
		(void)snprintf(buf, sizeof(buf), "%lu", maxinode);
		d.s_inode = strlen(buf);
		(void)snprintf(buf, sizeof(buf), "%lu", maxnlink);
		d.s_nlink = strlen(buf);
		(void)snprintf(buf, sizeof(buf), "%qu", maxsize);
		d.s_size = strlen(buf);
E 93
E 90
		d.s_user = maxuser;
E 86
	}
I 86

	printfcn(&d);
	output = 1;

	if (f_longform)
		for (cur = list; cur; cur = cur->fts_link)
			free(cur->fts_pointer);
E 86
E 83
E 77
E 73
D 38
	path[lnklen] = '\0';
	(void)printf(" -> %s", path);
E 38
}

I 77
/*
 * Ordering for mastercmp:
 * If ordering the argv (fts_level = FTS_ROOTLEVEL) return non-directories
 * as larger than directories.  Within either group, use the sort function.
 * All other levels use the sort function.  Error entries remain unsorted.
 */
E 77
I 73
D 79
static int
E 79
I 79
D 86
int
E 86
I 86
static int
E 86
E 79
E 73
D 38
namecmp(a, b)
	LS *a, *b;
E 38
I 38
D 46
static
E 46
D 44
buildstats(lp, s_stats, s_names)
E 44
I 44
D 77
tabdir(lp, s_stats, s_names)
E 44
	LS *lp, **s_stats;
	char **s_names;
E 77
I 77
mastercmp(a, b)
	const FTSENT **a, **b;
E 77
E 38
E 37
{
D 37
	return strcmp(a->name, b->name);
E 37
I 37
D 38
	return(strcmp(a->name, b->name));
E 37
}
E 38
I 38
D 46
	register int cnt, maxentry;
E 46
I 46
D 77
	register DIR *dirp;
	register int cnt, maxentry, maxlen;
E 46
	register char *p, *names;
D 43
	struct dirent *entry;
E 43
I 43
	struct dirent *dp;
I 46
D 73
	u_long blocks;
E 73
E 46
E 43
	LS *stats;
I 73
	u_long blocks;
E 77
I 77
D 104
	register int a_info, b_info;
E 104
I 104
	int a_info, b_info;
E 104
E 77
E 73
D 46
	DIR *dirp;
E 46
E 38
E 36

D 36
char *
fmtmode(lp, flags)
	char *lp;
D 31
	int flags;
E 31
I 31
	register int flags;
E 36
I 36
D 37
int     revnamecmp(a, b)
lsstruct *a, *b;
E 37
I 37
D 38
revnamecmp(a, b)
	LS *a, *b;
E 37
E 36
E 31
{
D 36
	int **mp;
E 36
I 36
D 37
	return strcmp(b->name, a->name);
E 37
I 37
	return(strcmp(b->name, a->name));
E 37
}
E 38
I 38
D 46
	/* make this big so we don't realloc often */
E 46
I 46
D 60
	/*
	 * allocate space for array of LS structures and the file names
	 * the name field will point to.  Make it big so we don't have
	 * to realloc often.
	 */
E 46
#define	DEFNUM	256
	maxentry = DEFNUM;
D 54
	*s_stats = stats = (LS *)emalloc((u_int)DEFNUM * sizeof(LS));
	*s_names = names = emalloc((u_int)lp->lstat.st_size);
E 54
I 54
D 59
	stats = (LS *)emalloc((u_int)DEFNUM * sizeof(LS));
	names = emalloc((u_int)lp->lstat.st_size);
E 59
I 59
	*s_stats = stats = (LS *)emalloc((u_int)DEFNUM * sizeof(LS));
	*s_names = names = emalloc((u_int)lp->lstat.st_size);
E 59
E 54
E 38
E 36

E 60
D 36
	for (mp = &m[0]; mp < &m[sizeof(m)/sizeof(m[0])]; ) {
		register int *pairp = *mp++;
		register int n = *pairp++;
E 36
I 36
D 37
int     modcmp(a, b)
lsstruct *a, *b;
E 37
I 37
D 38
modcmp(a, b)
	LS *a, *b;
E 37
{
D 37
	return (a->lstat.st_mtime < b->lstat.st_mtime);
E 37
I 37
	return(a->lstat.st_mtime < b->lstat.st_mtime);
E 37
}
E 36

D 32
		while (--n >= 0 && (flags&*pairp++) == 0)
			pairp++;
		*lp++ = *pairp;
E 32
I 32
D 36
		while (--n >= 0 && (flags&*pairp) != *pairp)
			pairp += 2;
		*lp++ = pairp[n>=0];
E 32
	}
	return (lp);
E 36
I 36
D 37
int     revmodcmp(a, b)
lsstruct *a, *b;
E 37
I 37
revmodcmp(a, b)
	LS *a, *b;
E 37
{
D 37
	return (b->lstat.st_mtime < a->lstat.st_mtime);
E 37
I 37
	return(b->lstat.st_mtime < a->lstat.st_mtime);
E 37
E 36
}

D 36
/* rest should be done with nameserver or database */
E 36
I 36
D 37
int     acccmp(a, b)
lsstruct *a, *b;
E 37
I 37
acccmp(a, b)
	LS *a, *b;
E 37
{
D 37
	return (a->lstat.st_atime < b->lstat.st_atime);
E 37
I 37
	return(a->lstat.st_atime < b->lstat.st_atime);
E 37
}
E 36

D 36
#include <pwd.h>
#include <grp.h>
#include <utmp.h>
E 36
I 36
D 37
int     revacccmp(a, b)
lsstruct *a, *b;
E 37
I 37
revacccmp(a, b)
	LS *a, *b;
E 37
{
D 37
	return (b->lstat.st_atime < a->lstat.st_atime);
E 37
I 37
	return(b->lstat.st_atime < a->lstat.st_atime);
E 37
}
E 36

D 36
struct	utmp utmp;
I 19
#define	NMAX	(sizeof (utmp.ut_name))
#define SCPYN(a, b)	strncpy(a, b, NMAX)
E 19

D 23
#define NUID	2048
E 23
I 23
D 31
#define NUID	64	/* power of 2 */
#define UIDMASK	0x3f
E 23
#define NGID	300
E 31
I 31
#define NCACHE	64		/* power of 2 */
#define CAMASK	NCACHE - 1
E 31
D 19
#define	NMAX	(sizeof (utmp.ut_name))
E 19

D 23
char	names[NUID][NMAX+1];
E 23
I 23
D 31
struct ncache {
	int	uid;
	char	name[NMAX+1];
} nc[NUID];
E 23
D 10
char	groups[NGID][NMAX+1];
E 10
I 9
char	outrangename[NMAX+1];
int	outrangeuid = -1;
I 10
char	groups[NGID][NMAX+1];
char	outrangegroup[NMAX+1];
int	outrangegid = -1;
E 10
E 9

E 31
char *
getname(uid)
I 31
	uid_t uid;
E 36
I 36
D 37
int     statcmp(a, b)
lsstruct *a, *b;
E 37
I 37
statcmp(a, b)
	LS *a, *b;
E 37
E 36
E 31
{
D 31
	register struct passwd *pw;
D 23
	static init;
E 23
	struct passwd *getpwent();
E 31
I 23
D 34
	extern int _pw_stayopen;
E 34
D 31
	register int cp;
E 31
I 31
D 36
	static struct ncache {
		uid_t	uid;
		char	name[NMAX+1];
	} c_uid[NCACHE];
	register struct passwd *pw;
	register struct ncache *cp;
E 36
I 36
D 37
	return (a->lstat.st_ctime < b->lstat.st_ctime);
E 37
I 37
	return(a->lstat.st_ctime < b->lstat.st_ctime);
E 37
}
E 36
E 31
E 23

D 23
	if (uid >= 0 && uid < NUID && names[uid][0])
		return (&names[uid][0]);
D 9
	if (init == 2)
E 9
I 9
	if (uid >= 0 && uid == outrangeuid)
		return (outrangename);
I 20
rescan:
E 20
	if (init == 2) {
		if (uid < NUID)
			return (0);
		setpwent();
		while (pw = getpwent()) {
			if (pw->pw_uid != uid)
				continue;
			outrangeuid = pw->pw_uid;
D 19
			strncpy(outrangename, pw->pw_name, NUID);
E 19
I 19
			SCPYN(outrangename, pw->pw_name);
E 19
			endpwent();
			return (outrangename);
		}
		endpwent();
E 23
I 23
D 34
	_pw_stayopen = 1;
E 34
D 31
	cp = uid & UIDMASK;
	if (uid >= 0 && nc[cp].uid == uid && nc[cp].name[0])
		return (nc[cp].name);
	pw = getpwuid(uid);
	if (!pw)
E 23
E 9
		return (0);
I 9
D 23
	}
E 9
	if (init == 0)
		setpwent(), init = 1;
	while (pw = getpwent()) {
D 9
		if (pw->pw_uid < 0 || pw->pw_uid >= NUID)
E 9
I 9
		if (pw->pw_uid < 0 || pw->pw_uid >= NUID) {
			if (pw->pw_uid == uid) {
				outrangeuid = pw->pw_uid;
D 19
				strncpy(outrangename, pw->pw_name, NUID);
E 19
I 19
				SCPYN(outrangename, pw->pw_name);
E 19
				return (outrangename);
			}
E 9
			continue;
I 9
		}
E 9
		if (names[pw->pw_uid][0])
			continue;
D 19
		strncpy(names[pw->pw_uid], pw->pw_name, NMAX);
E 19
I 19
		SCPYN(names[pw->pw_uid], pw->pw_name);
E 19
D 20
		if (pw->pw_uid == uid) {
E 20
I 20
		if (pw->pw_uid == uid)
E 20
			return (&names[uid][0]);
D 20
		}
E 20
	}
	init = 2;
D 20
	endpwent();
	return (0);
E 20
I 20
	goto rescan;
E 23
I 23
	nc[cp].uid = uid;
	SCPYN(nc[cp].name, pw->pw_name);
	return (nc[cp].name);
E 31
I 31
D 36
	cp = c_uid + (uid & CAMASK);
	if (cp->uid == uid && *cp->name)
		return(cp->name);
	if (!(pw = getpwuid(uid)))
		return((char *)0);
	cp->uid = uid;
	SCPYN(cp->name, pw->pw_name);
	return(cp->name);
E 36
I 36
D 37
int     revstatcmp(a, b)
lsstruct *a, *b;
E 37
I 37
revstatcmp(a, b)
	LS *a, *b;
E 37
{
D 37
	return (b->lstat.st_ctime < a->lstat.st_ctime);
E 37
I 37
	return(b->lstat.st_ctime < a->lstat.st_ctime);
E 37
E 36
E 31
E 23
E 20
}

D 36
char *
getgroup(gid)
I 31
	gid_t gid;
E 36
I 36
D 37
char   *malloc();

char   *emalloc(size)
unsigned size;
E 37
I 37
char
*emalloc(size)
	u_int size;
E 37
E 36
E 31
{
I 31
D 36
	static struct ncache {
		gid_t	gid;
		char	name[NMAX+1];
	} c_gid[NCACHE];
E 31
	register struct group *gr;
D 31
	static init;
	struct group *getgrent();
E 31
I 31
	register struct ncache *cp;
E 36
I 36
D 37
	register char *retval;
E 37
I 37
	char *retval, *malloc();
E 37
E 36
E 31

D 31
	if (gid >= 0 && gid < NGID && groups[gid][0])
		return (&groups[gid][0]);
D 10
	if (init == 2)
E 10
I 10
	if (gid >= 0 && gid == outrangegid)
		return (outrangegroup);
I 20
rescan:
E 20
	if (init == 2) {
		if (gid < NGID)
			return (0);
		setgrent();
		while (gr = getgrent()) {
			if (gr->gr_gid != gid)
				continue;
			outrangegid = gr->gr_gid;
D 19
			strncpy(outrangegroup, gr->gr_name, NGID);
E 19
I 19
			SCPYN(outrangegroup, gr->gr_name);
E 19
			endgrent();
			return (outrangegroup);
		}
		endgrent();
E 10
		return (0);
I 10
	}
E 10
	if (init == 0)
		setgrent(), init = 1;
	while (gr = getgrent()) {
D 10
		if (gr->gr_gid < 0 || gr->gr_gid >= NGID)
E 10
I 10
		if (gr->gr_gid < 0 || gr->gr_gid >= NGID) {
			if (gr->gr_gid == gid) {
				outrangegid = gr->gr_gid;
D 19
				strncpy(outrangegroup, gr->gr_name, NGID);
E 19
I 19
				SCPYN(outrangegroup, gr->gr_name);
E 19
				return (outrangegroup);
			}
E 10
			continue;
I 10
		}
E 10
		if (groups[gr->gr_gid][0])
			continue;
D 19
		strncpy(groups[gr->gr_gid], gr->gr_name, NMAX);
E 19
I 19
		SCPYN(groups[gr->gr_gid], gr->gr_name);
E 19
D 20
		if (gr->gr_gid == gid) {
E 20
I 20
		if (gr->gr_gid == gid)
E 20
			return (&groups[gid][0]);
D 20
		}
E 20
	}
	init = 2;
D 20
	endgrent();
	return (0);
E 20
I 20
	goto rescan;
E 31
I 31
D 36
	cp = c_gid + (gid & CAMASK);
	if (cp->gid == gid && *cp->name)
		return(cp->name);
	if (!(gr = getgrgid(gid)))
		return((char *)0);
	cp->gid = gid;
	SCPYN(cp->name, gr->gr_name);
	return(cp->name);
E 36
I 36
	if ((retval = malloc(size)) == NULL) {
D 37
		perror("Can't find memory");
E 37
I 37
		(void)fprintf(stderr, "ls: out of memory.\n");
E 37
		exit(1);
E 38
I 38
D 56
	if (!(dirp = opendir(f_specialdir ? lp->name : "."))) {
E 56
I 56
D 77
	if (!(dirp = opendir("."))) {
E 56
D 46
		(void)fprintf(stderr, "ls: %s: %s\n",
		    lp->name, strerror(errno));
E 46
I 46
D 73
		(void)fprintf(stderr, "ls: %s: %s\n", lp->name,
		    strerror(errno));
E 46
		return(0);
E 73
I 73
		warn("%s: %s", lp->name, strerror(errno));
E 77
I 77
	a_info = (*a)->fts_info;
	if (a_info == FTS_ERR)
E 77
		return (0);
E 73
E 38
D 77
	}
I 46
D 60
	blocks = 0;
	maxlen = -1;
E 60
I 60
	blocks = maxentry = maxlen = 0;
	stats = NULL;
E 60
E 46
D 37
	return retval;
E 37
I 37
D 38
	return(retval);
}

usage()
{
	(void)fprintf(stderr, "usage: ls [-1ACFLRacdfgilqrstu] [file ...]\n");
	exit(1);
E 38
I 38
D 43
	for (cnt = 0; entry = readdir(dirp);) {
E 43
I 43
	for (cnt = 0; dp = readdir(dirp);) {
E 43
I 42
		/* this does -A and -a */
E 42
D 43
		p = entry->d_name;
E 43
I 43
		p = dp->d_name;
E 43
		if (p[0] == '.') {
			if (!f_listdot)
				continue;
			if (!f_listalldot && (!p[1] || p[1] == '.' && !p[2]))
				continue;
		}
		if (cnt == maxentry) {
D 54
			maxentry += DEFNUM;
E 54
I 54
D 60
			maxentry *= 2;
E 54
			if (!(stats = (LS *)realloc((char *)stats,
E 60
I 60
			if (!maxentry)
				*s_names = names =
				    emalloc((u_int)lp->lstat.st_size);
#define	DEFNUM	256
			maxentry += DEFNUM;
D 73
			if (!(*s_stats = stats = (LS *)realloc((char *)stats,
E 73
I 73
			if (!(*s_stats = stats = realloc((char *)stats,
E 73
E 60
			    (u_int)maxentry * sizeof(LS))))
D 73
				nomem();
E 73
I 73
				err("%s", strerror(errno));
E 73
		}
D 40
		if (needstat && statfcn(entry->d_name, &stats[cnt].lstat)) {
E 40
I 40
D 43
		if (needstat && lstat(entry->d_name, &stats[cnt].lstat)) {
E 43
I 43
D 53
		if (needstat && lstat(dp->d_name, &stats[cnt].lstat)) {
E 53
I 53
D 71
		if (f_needstat && lstat(dp->d_name, &stats[cnt].lstat)) {
E 71
I 71
		if (f_needstat && statfcn(dp->d_name, &stats[cnt].lstat) &&
		    statfcn == stat && lstat(dp->d_name, &stats[cnt].lstat)) {
E 71
I 64
			/*
			 * don't exit -- this could be an NFS mount that has
			 * gone away.  Flush stdout so the messages line up.
			 */
			(void)fflush(stdout);
E 64
E 53
E 43
E 40
D 71
			(void)fprintf(stderr, "ls: %s: %s\n",
D 43
			    entry->d_name, strerror(errno));
E 43
I 43
			    dp->d_name, strerror(errno));
E 71
I 71
D 73
			(void)fprintf(stderr,
			    "ls: %s: %s\n", dp->d_name, strerror(errno));
E 73
I 73
			warn("%s: %s", dp->d_name, strerror(errno));
E 73
E 71
E 43
D 64
			if (errno == ENOENT)
				continue;
			exit(1);
E 64
I 64
			continue;
E 64
		}
I 43
D 46
		/*
		 * get the inode from the directory, in case the -f flag
		 * was set and we can't stat the actual file.
		 */
		stats[cnt].lstat.st_ino = dp->d_ino;
E 46
E 43
		stats[cnt].name = names;
E 77
I 77
	b_info = (*b)->fts_info;
	if (b_info == FTS_ERR)
		return (0);
D 79
	if (f_needstat && (a_info == FTS_NS || b_info == FTS_NS))
E 79
I 79

	if (a_info == FTS_NS || b_info == FTS_NS)
E 79
		return (namecmp(*a, *b));
E 77
D 43
		bcopy(entry->d_name, names, (int)entry->d_namlen);
		names += entry->d_namlen;
E 43
I 43
D 46
		bcopy(dp->d_name, names, (int)dp->d_namlen);
E 46
I 46

D 51
		/* strip out unprintables */
E 51
D 77
		if (f_nonprint)
			prcopy(dp->d_name, names, (int)dp->d_namlen);
		else
			bcopy(dp->d_name, names, (int)dp->d_namlen);
E 46
		names += dp->d_namlen;
E 43
		*names++ = '\0';
E 77
I 77
D 86
	if (a_info == b_info)  
E 86
I 86
	if (a_info == b_info)
E 86
		return (sortfcn(*a, *b));
E 77
I 46

D 77
		/*
		 * get the inode from the directory, so the -f flag
		 * works right.
		 */
		stats[cnt].lstat.st_ino = dp->d_ino;

		/* save name length for -C format */
		stats[cnt].len = dp->d_namlen;
D 51
		/* calculate number of blocks if -l format */
E 51
I 51

		/* calculate number of blocks if -l/-s formats */
E 51
D 49
		if (f_longform)
E 49
I 49
		if (f_longform || f_size)
E 49
			blocks += stats[cnt].lstat.st_blocks;
I 51

E 51
		/* save max length if -C format */
D 49
		else if (!f_singlecol && maxlen < (int)dp->d_namlen)
E 49
I 49
D 51
		if (!f_longform && !f_singlecol && maxlen < (int)dp->d_namlen)
E 51
I 51
		if (f_column && maxlen < (int)dp->d_namlen)
E 51
E 49
			maxlen = dp->d_namlen;
E 46
		++cnt;
	}
I 54
D 59
	*s_stats = stats;
	*s_names = names;
E 59
E 54
I 46
D 49
	/*
	 * overload -- we probably have to save either blocks or maxlen
	 * with the lstat array, so we stuff it into an unused field in
	 * the first stat structure.  If there's ever a type larger than
	 * u_long, fix this.  This information must be saved if qsort
	 * is called.
	 */
	if (f_longform)
		stats[0].lstat.st_flags = blocks;
	else if (!f_singlecol)
		stats[0].lstat.st_flags = maxlen;
E 49
I 49
D 60
	stats[0].lstat.st_btotal = blocks;
	stats[0].lstat.st_maxlen = maxlen;
E 49
E 46
I 39
	closedir(dirp);
E 60
I 60
	(void)closedir(dirp);

	if (cnt) {
		stats[0].lstat.st_btotal = blocks;
		stats[0].lstat.st_maxlen = maxlen;
	} else if (stats) {
D 73
		(void)free((char *)stats);
		(void)free((char *)names);
E 73
I 73
		free(stats);
		free(names);
E 73
	}
E 60
E 39
D 73
	return(cnt);
E 73
I 73
	return (cnt);
E 77
I 77
	if ((*a)->fts_level == FTS_ROOTLEVEL)
D 86
		if (a_info == FTS_D)        
E 86
I 86
		if (a_info == FTS_D)
E 86
			return (1);
		else if (b_info == FTS_D)
			return (-1);
		else
			return (sortfcn(*a, *b));
	else
		return (sortfcn(*a, *b));
I 86
D 95
}

static char *
flags_from_fid(flags)
	u_long flags;
{
	static char buf[20];
	register int comma;
	register char *p;

	p = buf;
	if (flags & ARCHIVED) {
		(void)strcpy(p, "arch");
		p += sizeof("arch") - 1;
		comma = 1;
	} else
		comma = 0;
	if (flags & NODUMP) {
D 87
		if (comma)
E 87
I 87
		if (comma++)
E 87
			*p++ = ',';
		(void)strcpy(p, "nodump");
		p += sizeof("nodump") - 1;
	}
	if (flags & IMMUTABLE) {
D 87
		if (comma)
E 87
I 87
		if (comma++)
E 87
			*p++ = ',';
		(void)strcpy(p, "nochg");
		p += sizeof("nochg") - 1;
	}
I 87
	if (!comma)
		(void)strcpy(p, "-");
E 87
	return (buf);
E 95
E 86
E 77
E 73
E 38
E 37
E 36
E 31
E 20
}
E 1
