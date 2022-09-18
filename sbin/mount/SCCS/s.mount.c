h27183
s 00004/00053/00456
d D 8.25 95/05/08 13:02:36 mckusick 88 87
c break out vfslist.c for df
e
s 00007/00004/00502
d D 8.24 95/04/27 16:36:02 mckusick 87 86
c check /etc/fstab for update so can use it if available
e
s 00014/00019/00492
d D 8.23 95/04/26 16:22:25 mckusick 86 85
c mount -u does not need entries in /etc/fstab
e
s 00001/00014/00510
d D 8.22 95/04/26 12:41:03 mckusick 85 84
c update for new kernel filesystem structure (vfsconf)
e
s 00017/00010/00507
d D 8.21 94/07/14 12:14:04 mckusick 84 83
c add ownership of non-root mounts
e
s 00036/00005/00481
d D 8.20 94/06/16 17:43:10 mckusick 83 82
c add noauto (from mycroft)
e
s 00001/00001/00485
d D 8.19 94/04/19 23:48:38 mckusick 82 81
c do not complain if mountd is not found
e
s 00007/00015/00479
d D 8.18 94/04/02 09:33:31 bostic 81 80
c if it's an update, ignore the fstab file options.
e
s 00003/00000/00491
d D 8.17 94/03/31 05:43:18 pendry 80 79
c last checkin missed internal mount_ufs support.
c added it back.
e
s 00294/00382/00197
d D 8.16 94/03/27 07:46:03 bostic 79 78
c Jan-Simon and my new versions of the mount commands
c table driven options, delete -F in favor of -o being passed down
e
s 00001/00001/00578
d D 8.15 94/02/21 12:47:22 pendry 78 77
c pid > 0 && pid != -1  becomes  pid > 0
e
s 00026/00022/00553
d D 8.14 94/02/21 06:03:35 bostic 77 76
c merge "ret" and "rval" into one variable; usage() doesn't return;
c check the return of fscanf
e
s 00013/00007/00562
d D 8.13 94/02/20 17:16:34 pendry 76 75
c only signal mountd if necessary & possible.
e
s 00007/00005/00562
d D 8.12 94/02/20 16:56:58 pendry 75 74
c fix usage.  print MNT_USER flag if set.
e
s 00006/00007/00561
d D 8.11 94/02/17 08:37:18 bostic 74 73
c no newlines on err(3) calls; section 3 sets errno, too
e
s 00130/00147/00438
d D 8.10 94/02/17 08:15:45 bostic 73 72
c error exit if mountd exists and we fail to signal it
c pass gcc -Wall, unused #defines, variables, KNF, prettiness police
e
s 00009/00000/00576
d D 8.9 94/02/17 07:22:45 pendry 72 71
c apply realpath() to the mountpoint
e
s 00026/00038/00550
d D 8.8 94/02/17 03:23:10 pendry 71 70
c user err() where possible
c fix argument parsing to detect unreasonable combinations, such
c as "mount -t foo /bar"
c don't ever try to mount "/" twice - the kernel will deadlock.
c general cleanup.
e
s 00050/00035/00538
d D 8.7 94/02/17 00:20:43 pendry 70 69
c lint
e
s 00000/00008/00573
d D 8.6 94/02/16 23:49:23 pendry 69 68
c no longer needs support for nfs and other "external" filesystems.
e
s 00002/00002/00579
d D 8.5 94/01/24 06:37:50 bostic 68 67
c Mirror Kirk's 8.9 change to /sys/sys/mount.h; ISOFS => CD9660
e
s 00003/00000/00578
d D 8.4 94/01/23 22:02:15 mckusick 67 66
c complain about unknown options
e
s 00005/00003/00573
d D 8.3 94/01/12 22:08:31 hibler 66 65
c reflect changes in mount.h, support for ISOFS
e
s 00009/00000/00567
d D 8.2 94/01/11 23:26:31 mckusick 65 64
c add generic MNT_ASYNC flag
e
s 00005/00005/00562
d D 8.1 93/06/05 11:01:26 bostic 64 63
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00567
d D 5.52 93/06/04 16:48:35 cgd 63 62
c make LFS and "external" mount type
e
s 00011/00006/00557
d D 5.51 92/11/15 23:43:35 mckusick 62 61
c -f flag (fake) becomes -d (debug); -f used to force downgrade from
c read/write to read-only mount mode
e
s 00009/00000/00554
d D 5.50 92/07/19 17:06:31 pendry 61 60
c understand and allow for union mounts
e
s 00037/00004/00517
d D 5.49 92/05/28 00:10:19 mckusick 60 59
c make `mount -u /' work for diskless workstations (from leres@lbl)
e
s 00003/00001/00518
d D 5.48 92/01/13 23:38:17 mckusick 59 58
c fix default NFS behavior with @ or :
e
s 00005/00260/00514
d D 5.47 92/01/06 11:13:18 mckusick 58 57
c break out NFS handling (to mount_nfs)
e
s 00001/00000/00773
d D 5.46 91/12/31 16:47:42 bostic 57 56
c <sys/mount.h> needs <sys/uncred.h>
e
s 00003/00000/00770
d D 5.45 91/12/31 16:47:09 bostic 56 55
c add LFS support
e
s 00003/00002/00767
d D 5.44 91/02/26 15:36:26 bostic 55 54
c ANSI fixes
e
s 00031/00032/00738
d D 5.43 90/12/04 17:12:51 mckusick 54 53
c lint, minor optimizations (from torek)
e
s 00015/00009/00755
d D 5.42 90/11/12 19:04:56 karels 53 52
c fix up error messages: print whole spec name (without nulling colons),
c and make it clear which messages are remote/RPC errors; EACCESS isn't
c a good default in case of failure after retries
e
s 00007/00008/00757
d D 5.41 90/11/07 10:00:09 bostic 52 51
c add stdlib.h, remove errno define, rework #includes
e
s 00002/00000/00763
d D 5.40 90/10/01 17:14:31 mckusick 51 50
c add compress option for NFS
e
s 00018/00000/00745
d D 5.39 90/06/22 10:16:50 mckusick 50 49
c add support for spongy mounts
e
s 00008/00000/00737
d D 5.38 90/06/03 11:55:14 mckusick 49 48
c add Sun compatibility ala assuming NFS when spec contains ':' or '@'
e
s 00001/00011/00736
d D 5.37 90/06/01 16:18:06 bostic 48 47
c new copyright notice
e
s 00045/00040/00702
d D 5.36 90/05/19 13:07:45 bostic 47 46
c group options together in output display
c don't walk off the end of arg list in verbose mode
c lots of lint fluff (and not-so-fluff)
e
s 00001/00001/00741
d D 5.35 90/05/15 19:52:42 bostic 46 45
c string.h is ANSI C include file
e
s 00017/00008/00725
d D 5.34 90/05/14 14:01:22 mckusick 45 44
c update for TCP based NFS from Rick Macklem
e
s 00024/00024/00709
d D 5.33 90/05/04 22:38:47 mckusick 44 43
c mount flags changed from M_ to MNT_
e
s 00009/00002/00724
d D 5.32 90/05/02 09:39:18 mckusick 43 42
c add LOCAL and QUOTA flags
e
s 00006/00001/00720
d D 5.31 90/04/10 12:31:54 mckusick 42 41
c update usage message
e
s 00022/00004/00699
d D 5.30 90/04/08 17:23:32 mckusick 41 40
c observe -t option when no arguments
e
s 00025/00040/00678
d D 5.29 90/03/15 17:25:54 mckusick 40 39
c notify mountd of changes by signalling pid stored in /var/run/mountd.pid
e
s 00030/00000/00688
d D 5.28 90/03/08 15:23:48 mckusick 39 38
c check to see if ufs filesystem is being exported and mark appropriately
e
s 00000/00009/00688
d D 5.27 90/03/06 22:00:17 mckusick 38 37
c do not trim leading pathname from special device name
e
s 00002/00002/00695
d D 5.26 90/03/06 21:23:58 mckusick 37 36
c add MNT_NOWAIT parameter to getmntinfo
e
s 00001/00000/00696
d D 5.25 90/03/05 11:18:56 bostic 36 35
c fix errno for ANSI C variable scoping
e
s 00004/00000/00692
d D 5.24 90/02/16 16:46:26 mckusick 35 34
c hack to avoid requirement to name root device for `mount -u /'
e
s 00000/00003/00692
d D 5.23 90/02/16 16:26:10 mckusick 34 33
c eliminate spurious includes
e
s 00055/00001/00640
d D 5.22 90/02/09 18:35:41 mckusick 33 32
c make -t meaningful in conjuction with -a
e
s 00003/00003/00638
d D 5.21 89/11/24 15:17:34 mckusick 32 31
c use static for returned variables!
e
s 00004/00002/00637
d D 5.20 89/11/24 14:57:11 mckusick 31 30
c unknown types use /sbin/mount_XXX
e
s 00004/00002/00635
d D 5.19 89/11/13 11:25:31 mckusick 30 29
c print proper error messages from NFS, null terminate arg list
e
s 00030/00001/00607
d D 5.18 89/10/31 17:41:45 mckusick 29 28
c for update requests scan kernel mount table, not fstab for entries
e
s 00058/00040/00550
d D 5.17 89/10/19 00:07:13 mckusick 28 27
c add -u flag to allow mounted file systems to be updated
e
s 00006/00013/00584
d D 5.16 89/10/18 16:41:00 mckusick 27 26
c generalize MFS interface to allow externalized file systems
e
s 00043/00026/00554
d D 5.15 89/10/17 16:24:01 mckusick 26 25
c if type is unknown, try to exec filesystem by that name
e
s 00004/00018/00576
d D 5.14 89/10/17 15:17:46 mckusick 25 24
c getmntinfo becomes a C library routine
e
s 00133/00082/00461
d D 5.13 89/10/17 14:04:28 mckusick 24 23
c add parsing of standard options; more verbose output
e
s 00027/00015/00516
d D 5.12 89/09/12 22:07:58 mckusick 23 22
c must get mount type when reading from fstab
e
s 00150/00082/00381
d D 5.11 89/09/12 18:36:07 mckusick 22 21
c add memory filesystem
e
s 00154/00165/00309
d D 5.10 89/08/16 00:04:15 mckusick 21 20
c eliminate mtab; reorganize NFS code
e
s 00245/00008/00229
d D 5.9 89/07/11 19:04:10 mckusick 20 19
c update to support NFS (from Rick Macklem)
e
s 00001/00001/00236
d D 5.8 89/06/28 00:08:21 mckusick 19 18
c proper include path
e
s 00008/00002/00229
d D 5.7 89/05/19 15:48:49 mckusick 18 17
c merge in vnodes
e
s 00010/00005/00221
d D 5.6 88/08/15 13:11:35 bostic 17 16
c always fake mounting '/'
e
s 00011/00011/00215
d D 5.5 88/08/15 10:37:55 bostic 16 15
c fix return value; bug fix to mountfs, mount(2) takes integer arg
e
s 00005/00003/00221
d D 5.4 88/08/05 15:17:29 bostic 15 14
c provide correct exit values
e
s 00156/00129/00068
d D 5.3 88/08/05 14:35:55 bostic 14 13
c add -w flag, fix to allow either special file or directory,
c getopt(3), make -[rw] flag work correctly, enhance error messages,
c should add Berkeley copyright as soon as mtab moves into the kernel
e
s 00005/00001/00192
d D 5.2 85/11/21 18:22:25 karels 13 12
c "mount foo" should skip xx'd entries, mount in same manner as "mount -a"
e
s 00014/00002/00179
d D 5.1 85/05/28 15:00:00 dist 12 11
c Add copyright
e
s 00019/00001/00162
d D 4.11 84/07/05 20:06:44 sam 11 10
c add errno interpretation code 
e
s 00068/00044/00095
d D 4.10 83/05/28 13:08:04 sam 10 9
c lots of cleanups; use <mtab.h>; handle quotas more cleanly; add 
c type field to mtab so we can see read-only and quotas
e
s 00002/00001/00137
d D 4.9 83/05/25 23:02:29 sam 9 8
c quotas
e
s 00005/00003/00133
d D 4.8 83/02/09 14:58:32 sam 8 7
c braindamage
e
s 00002/00004/00134
d D 4.7 82/03/31 12:04:15 root 7 6
c fix -r option and arg count to a real diagnostic
e
s 00011/00003/00127
d D 4.6 81/11/25 14:46:21 root 6 5
c implement -r
e
s 00071/00080/00059
d D 4.5 81/10/03 16:07:04 root 5 4
c add -f and -v
e
s 00004/00002/00135
d D 4.4 81/07/12 16:34:52 root 4 3
c mount -f makes a mount table entry
e
s 00043/00021/00094
d D 4.3 80/10/15 23:48:57 bill 3 2
c new routines
e
s 00009/00015/00106
d D 4.2 80/10/13 17:03:08 bill 2 1
c Adding calls to fstab routines
e
s 00121/00000/00000
d D 4.1 80/10/01 17:27:32 bill 1 0
c date and time created 80/10/01 17:27:32 by bill
e
u
U
t
T
I 12
/*
D 26
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 26
I 26
D 64
 * Copyright (c) 1980, 1989 The Regents of the University of California.
 * All rights reserved.
E 64
I 64
D 79
 * Copyright (c) 1980, 1989, 1993
E 79
I 79
 * Copyright (c) 1980, 1989, 1993, 1994
E 79
 *	The Regents of the University of California.  All rights reserved.
E 64
 *
D 48
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
E 48
I 48
 * %sccs.include.redist.c%
E 48
E 26
 */

E 12
I 8
#ifndef lint
E 8
I 1
D 12
static char *sccsid = "%W% (Berkeley) %G%";
D 8
#include <stdio.h>
#include <fstab.h>
E 8
I 8
#endif
E 12
I 12
D 64
char copyright[] =
D 26
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 26
I 26
"%Z% Copyright (c) 1980, 1989 The Regents of the University of California.\n\
E 26
 All rights reserved.\n";
E 64
I 64
static char copyright[] =
D 79
"%Z% Copyright (c) 1980, 1989, 1993\n\
E 79
I 79
"%Z% Copyright (c) 1980, 1989, 1993, 1994\n\
E 79
	The Regents of the University of California.  All rights reserved.\n";
E 64
D 26
#endif not lint
E 26
I 26
#endif /* not lint */
E 26

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 26
#endif not lint
E 26
I 26
#endif /* not lint */
E 26
E 12
E 8

I 73
#include <sys/param.h>
D 79
#include <sys/wait.h>
E 79
#include <sys/mount.h>
I 79
#include <sys/wait.h>
E 79
E 73
I 22
D 52
#include "pathnames.h"
E 52
E 22
D 14
/*
D 2
 *	Mount file systems.
 *
 *	mount -a	Mount all file systems, as determined from the
 *			file /etc/fstab.
 *	If the name entry in /etc/fstab is "/", don't mount.
 *	If the read only entry in /etc/fstab is "ro", mount read only
 *	The special file names in /etc/fstab are the block devices;
 *		this is what we want to mount.
 *	Tries to mount all of the files in /etc/fstab.
 *	
 *	mount special name	Mount special on name
 *	mount special name -r	Mount special on name, read/write
E 2
I 2
 * mount
E 2
 */
E 14
I 10
D 71
#include <sys/param.h>
I 57
D 58
#include <sys/ucred.h>
E 58
E 57
D 14

E 10
I 8
#include <stdio.h>
E 14
I 14
D 70
#include <sys/file.h>
E 70
I 19
D 20
#include <sys/mount.h>
E 20
I 20
#include <sys/time.h>
I 23
#include <sys/wait.h>
E 23
E 20
E 19
E 14
D 52
#include <fstab.h>
I 10
D 21
#include <mtab.h>
E 21
I 11
#include <errno.h>
I 14
#include <stdio.h>
I 40
#include <signal.h>
E 40
I 20
D 46
#include <strings.h>
E 46
I 46
#include <string.h>
E 52
I 52
#include <sys/errno.h>
D 70
#include <sys/signal.h>
I 58
#include <sys/ucred.h>
E 70
I 70
#include <signal.h>
E 70
E 58
E 52
E 46
D 34
#include <sys/dir.h>
#include <sys/uio.h>
#include <sys/namei.h>
E 34
#include <sys/mount.h>
D 58
#ifdef NFS
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <netdb.h>
#include <rpc/rpc.h>
#include <rpc/pmap_clnt.h>
#include <rpc/pmap_prot.h>
#include <nfs/rpcv2.h>
#include <nfs/nfsv2.h>
#include <nfs/nfs.h>
#endif
E 58
I 52
#include <fstab.h>
#include <string.h>
E 71
I 71

I 73
#include <err.h>
#include <errno.h>
#include <fstab.h>
I 84
#include <pwd.h>
E 84
#include <signal.h>
E 73
E 71
#include <stdio.h>
#include <stdlib.h>
I 70
D 73
#include <unistd.h>
E 73
I 71
#include <string.h>
D 73
#include <errno.h>
#include <signal.h>
#include <fstab.h>
#include <sys/param.h>
#include <sys/wait.h>
#include <sys/mount.h>
E 73
I 73
#include <unistd.h>

E 73
E 71
E 70
#include "pathnames.h"
E 52
E 20
I 18
D 19
#include </usr/src/local/mkmsys/macklem/mkmsys/h/mount.h>
E 19
E 18
E 14
E 11
E 10
E 8

I 79
D 88
int debug, verbose, skipvfs;
E 88
I 88
int debug, verbose;
E 88
E 79
I 39
D 73
#define DEFAULT_ROOTUID	-2
E 73

E 39
D 5
int	mountall;
E 5
D 10
#define	NMOUNT	16
#define	NAMSIZ	32
E 10
I 10
D 14
#define	DNMAX	(sizeof (mtab[0].m_dname) - 1)
#define	PNMAX	(sizeof (mtab[0].m_path) - 1)
E 14
I 14
D 73
#define	BADTYPE(type) \
	(strcmp(type, FSTAB_RO) && strcmp(type, FSTAB_RW) && \
	    strcmp(type, FSTAB_RQ))
#define	SETTYPE(type) \
	(!strcmp(type, FSTAB_RW) || !strcmp(type, FSTAB_RQ))
E 14
E 10

D 10
struct mtab {
	char	file[NAMSIZ];
	char	spec[NAMSIZ];
} mtab[NMOUNT];
E 10
I 10
D 14
struct	mtab mtab[NMOUNT];
E 14
I 14
D 21
#define	MTAB	"/etc/mtab"
E 14
E 10

I 5
D 14
int	all;
E 5
I 3
int	ro;
I 4
int	fake;
I 5
int	verbose;
I 10
char	*index(), *rindex();
E 14
I 14
static struct mtab mtab[NMOUNT];
E 21
D 15
static int fake, verbose;
E 15
I 15
D 16
static int fake, rval, verbose;
E 16
I 16
D 20
static int fake, verbose;
E 20
I 20
D 26
static int fake, verbose, mnttype;
I 22
char **envp;
E 26
I 26
D 28
int fake, verbose, mnttype;
E 28
I 28
D 62
int fake, verbose, updateflg, mnttype;
E 62
I 62
int debug, force, verbose, updateflg, mnttype;
E 73
I 73
D 79
int debug, force, verbose, mnttype, skipvfs;
E 73
E 62
E 28
D 70
char *mntname, **envp;
I 33
char **vfslist, **makevfslist();
I 55
static void prmount();
E 70
I 70
char *mntname;
D 73
char **vfslist;
static int badvfstype __P((int, char **));
static int badvfsname __P((char *, char **));
static int getexecopts __P((char *, char **));
static struct statfs *getmntpt __P((char *));
static int getmnttype __P((char *));
static void getstdopts __P((char *, int *));
static void getufsopts __P((char *, int *));
static char **makevfslist __P((char *));
static int mountfs __P((char *, char *, int, char *, char *, char *));
static void prmount __P((char *, char *, int));
static void usage __P((void));
E 73
E 70
E 55
E 33
E 26

I 73
int    badvfsname __P((char *, char **));
int    badvfstype __P((int, char **));
int    getexecopts __P((char *, char **));
E 79
I 79
D 88
int	badvfsname __P((const char *, const char **));
int	badvfstype __P((int, const char **));
E 88
I 88
int	checkvfsname __P((const char *, const char **));
E 88
char   *catopt __P((char *, const char *));
E 79
struct statfs
D 79
      *getmntpt __P((char *));
int    getmnttype __P((char *));
void   getstdopts __P((char *, int *));
void   getufsopts __P((char *, int *));
char **makevfslist __P((char *));
int    mountfs __P((char *, char *, int, char *, char *, char *));
void   prmount __P((char *, char *, int));
void   usage __P((void));
E 79
I 79
       *getmntpt __P((const char *));
I 83
int	hasopt __P((const char *, const char *));
E 83
const char
      **makevfslist __P((char *));
void	mangle __P((char *, int *, const char **));
int	mountfs __P((const char *, const char *, const char *,
			int, const char *, const char *));
D 84
void	prmount __P((const char *, const char *, int));
E 84
I 84
void	prmount __P((struct statfs *));
E 84
void	usage __P((void));
E 79

I 79
/* From mount_ufs.c. */
int	mount_ufs __P((int, char * const *));

/* Map from mount otions to printable formats. */
static struct opt {
	int o_opt;
	const char *o_name;
} optnames[] = {
	{ MNT_ASYNC,		"asynchronous" },
	{ MNT_EXPORTED,		"NFS exported" },
	{ MNT_LOCAL,		"local" },
	{ MNT_NODEV,		"nodev" },
	{ MNT_NOEXEC,		"noexec" },
	{ MNT_NOSUID,		"nosuid" },
	{ MNT_QUOTA,		"with quotas" },
	{ MNT_RDONLY,		"read-only" },
	{ MNT_SYNCHRONOUS,	"synchronous" },
	{ MNT_UNION,		"union" },
D 84
	{ MNT_USER,		"user mount" },
E 84
	{ NULL }
};

E 79
E 73
E 22
D 58
#ifdef NFS
int xdr_dir(), xdr_fh();
I 21
char *getnfsargs();
E 21
D 45
struct nfs_args nfsargs = {
	(struct sockaddr_in *)0,
E 45
I 45
struct nfs_args nfsdefargs = {
	(struct sockaddr *)0,
	SOCK_DGRAM,
	0,
E 45
	(nfsv2fh_t *)0,
	0,
	NFS_WSIZE,
	NFS_RSIZE,
	NFS_TIMEO,
	NFS_RETRANS,
	(char *)0,
};
E 20
E 16
E 15
E 14
E 10
I 6

I 20
struct nfhret {
	u_long	stat;
	nfsv2fh_t nfh;
};
D 33
int retrycnt = 10000;
E 33
I 33
#define	DEF_RETRY	10000
int retrycnt;
E 33
#define	BGRND	1
#define	ISBGRND	2
int opflags = 0;
#endif

E 58
E 20
E 6
E 5
E 4
E 3
D 22
main(argc, argv)
E 22
I 22
D 70
main(argc, argv, arge)
E 70
I 70
int
main(argc, argv)
E 70
E 22
D 6
char **argv;
E 6
I 6
	int argc;
D 73
	char **argv;
E 73
I 73
D 79
	char *argv[];
E 79
I 79
	char * const argv[];
E 79
E 73
I 22
D 70
	char **arge;
E 70
E 22
E 6
{
I 79
D 86
	const char *mntonname, **vfslist, *vfstype;
E 86
I 86
D 87
	const char **vfslist, *vfstype;
E 87
I 87
	const char *mntfromname, **vfslist, *vfstype;
E 87
E 86
E 79
I 14
D 70
	extern char *optarg;
	extern int optind;
E 14
D 3
	register int ro;
E 3
D 21
	register struct mtab *mp;
E 21
D 14
	register char *np;
	int mf;
I 10
	char *type = FSTAB_RW;
E 14
I 14
	register struct fstab *fs;
E 70
I 70
	struct fstab *fs;
E 70
D 47
	register int cnt;
E 47
D 16
	int all, ch, fd;
E 16
I 16
D 17
	int all, ch, fd, rval;
E 17
I 17
D 21
	int all, ch, fd, rval, sfake;
E 21
I 21
D 28
	int all, ch, rval, sfake, i;
E 28
I 28
D 40
	int all, ch, rval, flags, i;
E 40
I 40
D 73
	int all, ch, rval, flags, ret, pid, i;
E 40
E 28
	long mntsize;
E 73
D 25
	struct statfs statfsbuf, *mntbuf;
E 25
I 25
D 29
	struct statfs *mntbuf;
E 29
I 29
D 70
	struct statfs *mntbuf, *getmntpt();
E 70
I 70
	struct statfs *mntbuf;
E 70
E 29
E 25
E 21
E 17
E 16
D 22
	char *type;
E 22
I 22
D 73
	char *type, *options = NULL;
E 73
I 40
D 77
	FILE *pidfile;
E 77
I 77
	FILE *mountdfp;
	pid_t pid;
E 77
I 73
D 79
	long mntsize;
D 76
	int all, ch, i, pid, ret, rval, updateflg;
E 76
I 76
D 77
	int all, ch, i, ret, rval, updateflg;
E 77
I 77
	int all, ch, i, rval, updateflg;
E 77
E 76
	char *cp, *type, *options, **vfslist;
E 79
I 79
	int all, ch, i, init_flags, mntsize, rval;
	char *options;
E 79
E 73
E 40
E 22
E 14
E 10

I 22
D 70
	envp = arge;
E 70
E 22
D 5
	mountall = 0;
E 5
D 14
	mf = open("/etc/mtab", 0);
D 10
	read(mf, (char *)mtab, NMOUNT*2*NAMSIZ);
	if (argc==1) {
E 10
I 10
	read(mf, (char *)mtab, sizeof (mtab));
	if (argc == 1) {
E 10
		for (mp = mtab; mp < &mtab[NMOUNT]; mp++)
D 10
			if (mp->file[0])
				printf("%s on %s\n", mp->spec, mp->file);
E 10
I 10
			if (mp->m_path[0] != '\0')
				prmtab(mp);
E 10
		exit(0);
	}
D 5

	if (argc == 2){
		if (strcmp(argv[1], "-a") == 0)
			mountall++;
		else {
D 3
			fprintf(stderr,"arg count\n");
E 3
I 3
			fprintf(stdout,"arg count\n");
E 3
			exit(1);
E 5
I 5
top:
	if (argc > 1) {
D 6
		if (strcmp(argv[1], "-a") == 0) {
E 6
I 6
		if (!strcmp(argv[1], "-a")) {
E 6
			all++;
			argc--, argv++;
			goto top;
E 5
		}
I 6
		if (!strcmp(argv[1], "-r")) {
E 14
I 14
D 73
	all = 0;
	type = NULL;
D 20
	while ((ch = getopt(argc, argv, "afrwv")) != EOF)
E 20
I 20
	mnttype = MOUNT_UFS;
E 73
I 26
D 79
	mntname = "ufs";
E 26
D 28
	while ((ch = getopt(argc, argv, "afrwvt:o:")) != EOF)
E 28
I 28
D 62
	while ((ch = getopt(argc, argv, "afrwuvt:o:")) != EOF)
E 62
I 62
D 73
	while ((ch = getopt(argc, argv, "adfrwuvt:o:")) != EOF)
E 62
E 28
E 20
		switch((char)ch) {
E 73
I 73
	mnttype = MOUNT_UFS;

	all = updateflg = 0;
	options = type = NULL;
E 79
I 79
	all = init_flags = 0;
	options = NULL;
E 79
	vfslist = NULL;
I 79
	vfstype = "ufs";
E 79
	while ((ch = getopt(argc, argv, "adfo:rwt:uv")) != EOF)
D 79
		switch(ch) {
E 79
I 79
		switch (ch) {
E 79
E 73
		case 'a':
			all = 1;
			break;
I 62
		case 'd':
			debug = 1;
			break;
E 62
		case 'f':
D 62
			fake = 1;
E 62
I 62
D 79
			force = 1;
E 79
I 79
			init_flags |= MNT_FORCE;
E 79
E 62
			break;
I 73
		case 'o':
D 79
			options = optarg;
E 79
I 79
			if (*optarg)
				options = catopt(options, optarg);
E 79
			break;
E 73
		case 'r':
E 14
D 10
			ro++;
E 10
I 10
D 79
			type = FSTAB_RO;
E 79
I 79
			init_flags |= MNT_RDONLY;
E 79
E 10
D 14
			argc--, argv++;
			goto top;
E 14
I 14
			break;
I 73
		case 't':
I 79
			if (vfslist != NULL)
				errx(1, "only one -t option may be specified.");
E 79
			vfslist = makevfslist(optarg);
D 79
			mnttype = getmnttype(optarg);
E 79
I 79
			vfstype = optarg;
E 79
			break;
E 73
I 28
		case 'u':
D 44
			updateflg = M_UPDATE;
E 44
I 44
D 79
			updateflg = MNT_UPDATE;
E 79
I 79
			init_flags |= MNT_UPDATE;
E 79
E 44
			break;
E 28
		case 'v':
			verbose = 1;
			break;
		case 'w':
D 79
			type = FSTAB_RW;
E 79
I 79
			init_flags &= ~MNT_RDONLY;
E 79
			break;
I 20
D 22
#ifdef NFS
		case 't':
			if (!strcmp(optarg, "nfs"))
				mnttype = MOUNT_NFS;
			break;
E 22
D 73
		case 'o':
D 21
			getoptions(optarg,&nfsargs,&opflags,&retrycnt);
E 21
I 21
D 22
			getoptions(optarg, &nfsargs, &opflags, &retrycnt);
E 22
I 22
			options = optarg;
E 22
E 21
			break;
D 22
#endif
E 22
I 22
		case 't':
I 33
			vfslist = makevfslist(optarg);
E 33
D 23
			if (!strcmp(optarg, "ufs")) {
				mnttype = MOUNT_UFS;
E 23
I 23
D 26
			if (mnttype = getmnttype(optarg))
E 23
				break;
D 23
			}
			if (!strcmp(optarg, "nfs")) {
				mnttype = MOUNT_NFS;
				break;
			}
			if (!strcmp(optarg, "mfs")) {
				mnttype = MOUNT_MFS;
				break;
			}
E 23
			/* fall through */
E 26
I 26
			mnttype = getmnttype(optarg);
			break;
E 73
E 26
E 22
E 20
		case '?':
		default:
			usage();
I 22
			/* NOTREACHED */
E 22
E 14
		}
E 6
D 5
	}
I 4
	if (!strcmp(argv[1], "-f"))
		fake++, argc--, argv++;
E 4

	if (!mountall){
		ro = 0;
		if(argc > 3)
			ro++;
D 3
		if (mountfs(argv[1], argv[2], ro))
E 3
I 3
		if (mountfs(argv[1], argv[2], ro)){
			perror("mount");
E 3
			exit(1);
E 5
I 5
D 14
		if (!strcmp(argv[1], "-f")) {
			fake++;
			argc--, argv++;
			goto top;
E 5
D 3
	} else {
		FILE	*fs_file;
		struct	fstab	fs;
D 2
		if ( (fs_file = fopen(FSTAB, "r")) == NULL){
E 2
I 2
		if ((fs_file = fopen(FSTAB, "r")) == NULL){
E 2
			perror(FSTAB);
			exit(1);
E 3
		}
D 3
		while (!feof(fs_file)){
I 2
			int ro;
E 2
			fscanf(fs_file, FSTABFMT, FSTABARG(&fs));
			if (strcmp(fs.fs_file, "/") == 0)
E 3
I 3
D 5
	} else {
E 5
I 5
		if (!strcmp(argv[1], "-v")) {
			verbose++;
			argc--, argv++;
			goto top;
		}
E 14
I 14
	argc -= optind;
	argv += optind;

D 73
	/* NOSTRICT */
E 73
I 73
#define	BADTYPE(type)							\
	(strcmp(type, FSTAB_RO) &&					\
	    strcmp(type, FSTAB_RW) && strcmp(type, FSTAB_RQ))
E 73
D 21
	if ((fd = open(MTAB, O_RDONLY, 0)) >= 0) {
		if (read(fd, (char *)mtab, NMOUNT * sizeof(struct mtab)) < 0)
			mtaberr();
		(void)close(fd);
E 14
	}
E 21
I 14

I 77
	rval = 0;
E 77
E 14
D 79
	if (all) {
I 16
D 77
		rval = 0;
E 77
E 16
E 5
D 6
		struct	fstab	*fsp;
E 6
I 6
D 14
		struct fstab *fsp;
E 14
I 14
D 17
		while ((fs = getfsent()))
			if (strcmp(fs->fs_file, "/") && !BADTYPE(fs->fs_type))
D 16
				mountfs(fs->fs_spec, fs->fs_file,
E 16
I 16
				rval |= mountfs(fs->fs_spec, fs->fs_file,
E 16
				    type ? type : fs->fs_type);
E 17
I 17
D 28
		for (sfake = fake; fs = getfsent(); fake = sfake) {
E 28
I 28
D 73
		while (fs = getfsent()) {
E 73
I 73
		while ((fs = getfsent()) != NULL) {
E 73
E 28
			if (BADTYPE(fs->fs_type))
				continue;
I 33
D 41
			if (badvfstype(fs->fs_vfstype, vfslist))
E 41
I 41
			if (badvfsname(fs->fs_vfstype, vfslist))
E 41
				continue;
E 33
D 73
			/* `/' is special, it's always mounted */
E 73
I 73
			/* `/' is special, it's always mounted. */
E 73
D 71
			if (!strcmp(fs->fs_file, "/"))
D 28
				fake = 1;
I 23
			if ((mnttype = getmnttype(fs->fs_vfstype)) == 0) {
				fprintf(stderr,
				    "%s %s type of file system is unknown.\n",
				    "mount:", fs->fs_vfstype);
				continue;
			}
E 23
I 20
D 22
#ifdef NFS
			if (index(fs->fs_spec, '@') != NULL) {
				if (fs->fs_vfstype != NULL &&
				    strcmp(fs->fs_vfstype, "nfs"))
					continue;
				if (fs->fs_mntops != NULL)
					getoptions(fs->fs_mntops, &nfsargs,
						&opflags, &retrycnt);
				mnttype = MOUNT_NFS;
			} else
				mnttype = MOUNT_UFS;
#endif
E 22
E 20
			rval |= mountfs(fs->fs_spec, fs->fs_file,
D 22
			    type ? type : fs->fs_type);
E 22
I 22
			    type ? type : fs->fs_type, options, fs->fs_mntops);
E 28
I 28
D 44
				flags = M_UPDATE;
E 44
I 44
				flags = MNT_UPDATE;
E 44
			else
				flags = updateflg;
E 71
			mnttype = getmnttype(fs->fs_vfstype);
D 71
			rval |= mountfs(fs->fs_spec, fs->fs_file, flags,
E 71
I 71
D 77
			rval |= mountfs(fs->fs_spec, fs->fs_file, updateflg,
E 71
			    type, options, fs->fs_mntops);
E 77
I 77
			if (mountfs(fs->fs_spec, fs->fs_file, updateflg,
			    type, options, fs->fs_mntops))
				rval = 1;
E 79
I 79
	switch (argc) {
	case 0:
		if (all)
			while ((fs = getfsent()) != NULL) {
				if (BADTYPE(fs->fs_type))
					continue;
D 88
				if (badvfsname(fs->fs_vfstype, vfslist))
E 88
I 88
				if (checkvfsname(fs->fs_vfstype, vfslist))
E 88
					continue;
I 83
				if (hasopt(fs->fs_mntops, "noauto"))
					continue;
E 83
				if (mountfs(fs->fs_vfstype, fs->fs_spec,
				    fs->fs_file, init_flags, options,
				    fs->fs_mntops))
					rval = 1;
			}
		else {
D 81
			if (verbose) {
				usage();
				/* NOTREACHED */
			}

E 81
			if ((mntsize = getmntinfo(&mntbuf, MNT_NOWAIT)) == 0)
				err(1, "getmntinfo");
			for (i = 0; i < mntsize; i++) {
D 85
				if (badvfstype(mntbuf[i].f_type, vfslist))
E 85
I 85
D 88
				if (badvfsname(mntbuf[i].f_fstypename, vfslist))
E 88
I 88
				if (checkvfsname(mntbuf[i].f_fstypename, vfslist))
E 88
E 85
					continue;
D 84
				prmount(mntbuf[i].f_mntfromname,
D 81
				     mntbuf[i].f_mntonname, mntbuf[i].f_flags);
E 81
I 81
				    mntbuf[i].f_mntonname, mntbuf[i].f_flags);
E 84
I 84
				prmount(&mntbuf[i]);
E 84
E 81
			}
E 79
E 77
E 28
E 22
		}
E 17
D 15
		exit(0);
E 15
I 15
		exit(rval);
E 15
D 79
	}
E 14

E 6
I 5
D 14
		if (argc > 1)
			goto argcnt;
E 5
		close(2); dup(1);
		if (setfsent() == 0)
			perror(FSTAB), exit(1);
D 5
		while ( (fsp = getfsent()) != 0){
E 5
I 5
D 10
		while ( (fsp = getfsent()) != 0) {
E 10
I 10
		while ((fsp = getfsent()) != 0) {
E 10
E 5
			if (strcmp(fsp->fs_file, "/") == 0)
E 3
				continue;
I 2
D 3
			ro = !strcmp(fs.fs_type, "ro");
			if (ro==0 && strcmp(fs.fs_type, "rw"))
E 3
I 3
D 10
			ro = !strcmp(fsp->fs_type, FSTAB_RO);
D 9
			if (ro==0 && strcmp(fsp->fs_type, FSTAB_RW))
E 9
I 9
			if (ro==0 && strcmp(fsp->fs_type, FSTAB_RW) &&
E 10
I 10
			if (strcmp(fsp->fs_type, FSTAB_RO) &&
			    strcmp(fsp->fs_type, FSTAB_RW) &&
E 10
			    strcmp(fsp->fs_type, FSTAB_RQ))
E 9
E 3
				continue;
E 2
D 3
			fprintf(stderr, "Mounting %s on %s %s",
				fs.fs_file, fs.fs_spec,
D 2
				FSRO(&fs) ? "(Read Only)\n" : "\n");
			mountfs(fs.fs_spec, fs.fs_file, FSRO(&fs));
E 2
I 2
				ro ? "(Read Only)\n" : "\n");
			mountfs(fs.fs_spec, fs.fs_file, ro);
E 3
I 3
D 5
			if (mountfs(fsp->fs_spec, fsp->fs_file, ro))
				failed(fsp);
			else
				succeed(fsp);
E 5
I 5
D 10
			mountfs(fsp->fs_spec, fsp->fs_file, ro);
E 10
I 10
			mountfs(fsp->fs_spec, fsp->fs_file, fsp->fs_type);
E 10
E 5
E 3
E 2
		}
E 14
I 14
	if (argc == 0) {
D 62
		if (verbose || fake || type)
E 62
I 62
		if (verbose || debug || type)
E 79
I 79
	case 1:
D 81
		if (vfslist != NULL) {
E 81
I 81
		if (vfslist != NULL)
E 81
E 79
E 62
			usage();
D 21
		for (mp = mtab, cnt = NMOUNT; cnt--; ++mp)
			if (*mp->m_path)
				prmtab(mp);
E 21
I 21
D 25
		if ((mntsize = getfsstat(0, 0)) < 0) {
			perror("mount");
E 25
I 25
D 37
		if ((mntsize = getmntinfo(&mntbuf)) == 0) {
E 37
I 37
D 74
		if ((mntsize = getmntinfo(&mntbuf, MNT_NOWAIT)) == 0) {
E 37
D 54
			fprintf(stderr,
E 54
I 54
D 71
			(void) fprintf(stderr,
E 54
				"mount: cannot get mount information\n");
E 25
			exit(1);
E 71
I 71
			errx(1, "cannot get mount information");
E 71
		}
E 74
I 74
D 79
		if ((mntsize = getmntinfo(&mntbuf, MNT_NOWAIT)) == 0)
			err(1, "getmntinfo");
E 74
D 25
		mntbuf = 0;
		do {
			if (mntbuf)
				free(mntbuf);
			i = (mntsize + 1) * sizeof(struct statfs);
			if ((mntbuf = (struct statfs *)malloc(i)) == 0) {
				fprintf(stderr,
					"no space for mount table buffer\n");
				exit(1);
			}
			if ((mntsize = getfsstat(mntbuf, i)) < 0) {
D 22
				perror("df");
E 22
I 22
				perror("mount");
E 22
				exit(1);
			}
		} while (i == mntsize * sizeof(struct statfs));
E 25
D 24
		for (i = 0; i < mntsize; i++) {
			if (mntbuf[i].f_flags & M_RDONLY)
				type = "ro";
			else
				type = "rw";
E 24
I 24
D 41
		for (i = 0; i < mntsize; i++)
E 41
I 41
		for (i = 0; i < mntsize; i++) {
			if (badvfstype(mntbuf[i].f_type, vfslist))
				continue;
E 41
E 24
D 73
			prmount(mntbuf[i].f_mntfromname, mntbuf[i].f_mntonname,
D 24
				type);
		}
E 24
I 24
				mntbuf[i].f_flags);
E 73
I 73
			prmount(mntbuf[i].f_mntfromname,
			     mntbuf[i].f_mntonname, mntbuf[i].f_flags);
E 79
I 79
D 81
			/* NOTREACHED */
E 79
E 73
I 41
		}
E 81
E 41
E 24
E 21
E 14
D 3
		fclose(fs_file);
E 3
I 3
D 5
		endfsent();
E 5
I 5
D 79
		exit(0);
E 5
E 3
	}
E 79
I 10
D 14
	if (argc == 2) {
		struct fstab *fs;
E 14

I 71
D 73
	if (argc == 1 && vfslist) {
E 73
I 73
D 77
	if (argc == 1 && vfslist != NULL)
E 77
I 77
D 79
	if (argc == 1 && vfslist != NULL) {
E 77
E 73
		usage();
I 77
		/* NOTREACHED */
	}
E 77
D 73
	}
E 73

E 71
I 29
	if (argc == 1 && updateflg) {
D 73
		if ((mntbuf = getmntpt(*argv)) == NULL) {
D 54
			fprintf(stderr,
E 54
I 54
D 71
			(void) fprintf(stderr,
E 54
			    "mount: unknown special file or file system %s.\n",
E 71
I 71
			errx(1, "unknown special file or file system %s.",
E 71
			    *argv);
D 71
			exit(1);
E 71
		}
E 73
I 73
		if ((mntbuf = getmntpt(*argv)) == NULL)
			errx(1,
			    "unknown special file or file system %s.", *argv);
E 73
		mnttype = mntbuf->f_type;
I 35
D 60
		if (!strcmp(mntbuf->f_mntfromname, "root_device")) {
			fs = getfsfile("/");
			strcpy(mntbuf->f_mntfromname, fs->fs_spec);
E 60
I 60
D 73
		if ((fs = getfsfile(mntbuf->f_mntonname)) == NULL) {
E 73
I 73
		if ((fs = getfsfile(mntbuf->f_mntonname)) == NULL)
E 73
D 71
			(void) fprintf(stderr,
			    "mount: can't find fstab entry for %s.\n", *argv);
			exit(1);
E 71
I 71
			errx(1, "can't find fstab entry for %s.", *argv);
E 71
E 60
D 73
		}
E 73
E 35
D 40
		exit(mountfs(mntbuf->f_mntfromname, mntbuf->f_mntonname,
		    updateflg, type, options, NULL));
	}

E 29
D 14
		if (setfsent() == 0)
			perror(FSTAB), exit(1);
		fs = getfsfile(argv[1]);
		if (fs == NULL)
			goto argcnt;
D 13
		mountfs(fs->fs_spec, fs->fs_file, type);
E 13
I 13
		if (strcmp(fs->fs_type, FSTAB_RO) &&
		    strcmp(fs->fs_type, FSTAB_RW) &&
		    strcmp(fs->fs_type, FSTAB_RQ))
			goto argcnt;
		mountfs(fs->fs_spec, fs->fs_file, fs->fs_type);
E 14
I 14
D 23
	if (all)
		usage();

E 23
	if (argc == 1) {
E 40
I 40
D 60
		ret = mountfs(mntbuf->f_mntfromname, mntbuf->f_mntonname,
E 60
I 60
		mntname = fs->fs_vfstype;

		/*
		 * Default type to fstab version if none specified on the
		 * command line.
		 */
		if (type == NULL)
			type = fs->fs_type;

		/*
		 * Default options to fstab version if none specified on the
		 * command line.
		 */
		if (options == NULL)
			options = fs->fs_mntops;
		else {
D 70
			register char *cp;
E 70
I 70
D 73
			char *cp;
E 70

E 73
			/*
			 * Concat the two strings with the command line
			 * options last so that they will override the
			 * fstab options.
			 */
			i = strlen(fs->fs_mntops) + strlen(options) + 2;
D 73
			if ((cp = malloc((size_t)i)) == NULL) {
E 73
I 73
			if ((cp = malloc((size_t)i)) == NULL)
E 73
D 71
				(void) fprintf(stderr,
				    "mount: -u malloc failed\n");
				exit(1);
E 71
I 71
D 74
				errx(1, "-u malloc failed");
E 74
I 74
				err(1, NULL);
E 74
E 71
D 73
			}
			sprintf(cp, "%s,%s", fs->fs_mntops, options);
E 73
I 73
			(void)snprintf(cp, i, "%s,%s", fs->fs_mntops, options);
E 73
			options = cp;
E 79
I 79
		if (init_flags & MNT_UPDATE) {
			if ((mntbuf = getmntpt(*argv)) == NULL)
				errx(1,
				    "unknown special file or file system %s.",
				    *argv);
D 86
			if ((fs = getfsfile(mntbuf->f_mntonname)) == NULL)
				errx(1, "can't find fstab entry for %s.",
				    *argv);
I 81
			/* If it's an update, ignore the fstab file options. */
			fs->fs_mntops = NULL;
E 81
			mntonname = mntbuf->f_mntonname;
		} else {
			if ((fs = getfsfile(*argv)) == NULL &&
			    (fs = getfsspec(*argv)) == NULL)
				errx(1,
				    "%s: unknown special file or file system.",
				    *argv);
			if (BADTYPE(fs->fs_type))
				errx(1, "%s has unknown file system type.",
				    *argv);
			mntonname = fs->fs_file;
E 86
I 86
D 87
			rval = mountfs(mntbuf->f_fstypename,
			    mntbuf->f_mntfromname, mntbuf->f_mntonname,
			    init_flags, options, 0);
E 87
I 87
			if ((fs = getfsfile(mntbuf->f_mntonname)) != NULL)
				mntfromname = fs->fs_spec;
			else
				mntfromname = mntbuf->f_mntfromname;
			rval = mountfs(mntbuf->f_fstypename, mntfromname,
			    mntbuf->f_mntonname, init_flags, options, 0);
E 87
			break;
E 86
E 79
		}
D 73
		ret = mountfs(fs->fs_spec, mntbuf->f_mntonname,
E 60
D 47
		    updateflg, type, options, NULL);
E 47
I 47
		    updateflg, type, options, (char *)NULL);
E 73
I 73
D 77
		ret = mountfs(fs->fs_spec,
E 77
I 77
D 79
		rval = mountfs(fs->fs_spec,
E 77
		    mntbuf->f_mntonname, updateflg, type, options, NULL);
E 73
E 47
	} else if (argc == 1) {
E 40
D 73
		if (!(fs = getfsfile(*argv)) && !(fs = getfsspec(*argv))) {
D 54
			fprintf(stderr,
E 54
I 54
D 71
			(void) fprintf(stderr,
E 54
			    "mount: unknown special file or file system %s.\n",
E 71
I 71
			errx(1, "unknown special file or file system %s.\n",
E 71
			    *argv);
D 71
			exit(1);
E 71
		}
		if (BADTYPE(fs->fs_type)) {
E 73
I 73
		if ((fs = getfsfile(*argv)) == NULL &&
		    (fs = getfsspec(*argv)) == NULL)
			errx(1,
D 74
			    "unknown special file or file system %s.\n", *argv);
E 74
I 74
D 77
			    "unknown special file or file system %s.", *argv);
E 77
I 77
			    "%s: unknown special file or file system.", *argv);
E 77
E 74
		if (BADTYPE(fs->fs_type))
E 73
D 54
			fprintf(stderr,
E 54
I 54
D 71
			(void) fprintf(stderr,
E 54
			    "mount: %s has unknown file system type.\n", *argv);
			exit(1);
E 71
I 71
D 74
			errx(1, "%s has unknown file system type.\n", *argv);
E 74
I 74
			errx(1, "%s has unknown file system type.", *argv);
E 74
E 71
D 73
		}
E 73
I 23
D 28
		if ((mnttype = getmnttype(fs->fs_vfstype)) == 0) {
			fprintf(stderr,
			    "mount: %s type of file system is unknown.\n",
			    fs->fs_vfstype);
			exit(1);
		}
E 23
D 16
		mountfs(fs->fs_spec, fs->fs_file, type ? type : fs->fs_type);
E 14
E 13
D 15
		exit(0);
E 15
I 15
		exit(rval);
E 16
I 16
		exit(mountfs(fs->fs_spec, fs->fs_file,
D 22
		    type ? type : fs->fs_type));
E 22
I 22
		    type ? type : fs->fs_type, options, fs->fs_mntops));
E 28
I 28
		mnttype = getmnttype(fs->fs_vfstype);
D 40
		exit(mountfs(fs->fs_spec, fs->fs_file, updateflg,
		    type, options, fs->fs_mntops));
E 28
E 22
E 16
E 15
	}
E 10
D 5
	exit(0);
E 5
I 5
D 8
	if (argc < 2 || argc > 3) {
E 8
I 8
D 14
	if (argc != 3) {
E 8
argcnt:
D 7
		printf("arg count\n");
E 7
I 7
		fprintf(stderr,
D 10
	    "usage: mount [ -a ] [ -r ] [ -f ] [ -v ] [ special dir ]\n");
E 10
I 10
    "usage: mount [ -a ] [ -r ] [ -f ] [ -v ] [ special dir ] [ dir ]\n");
E 10
E 7
		exit(1);
	}
D 7
	ro = 0;
	if(argc > 3)
		ro++;
E 7
D 10
	mountfs(argv[1], argv[2], ro);
E 10
I 10
	mountfs(argv[1], argv[2], type);
E 10
E 5
}
E 14
I 3
D 5
failed(fsp)
	register	struct	fstab *fsp;
{
	extern int errno;
	extern char *sys_errlist[];
	int err = errno;
	printf("Attempt to mount ");
	location(fsp);
	printf("FAILED: %s\n", sys_errlist[err]);
}
succeed(fsp)
	register	struct	fstab *fsp;
{
	printf("Mounted ");
	location(fsp);
	printf("\n");
}
location(fsp)
	register	struct	fstab *fsp;
{
	extern	int	ro;
	printf("%s on %s %s ",
		fsp->fs_file, fsp->fs_spec,
		ro ? "(Read Only)" : "");
}
E 5
E 3

D 10
mountfs(spec, name, ro)
D 5
	char	*spec, *name;
	int	ro;
E 5
I 5
	char *spec, *name;
E 10
I 10
D 14
prmtab(mp)
	register struct mtab *mp;
E 10
E 5
{
E 14
I 14
	if (argc != 2)
E 40
I 40
D 73
		ret = mountfs(fs->fs_spec, fs->fs_file, updateflg,
		    type, options, fs->fs_mntops);
E 73
I 73
D 77
		ret = mountfs(fs->fs_spec,
E 77
I 77
		rval = mountfs(fs->fs_spec,
E 77
		    fs->fs_file, updateflg, type, options, fs->fs_mntops);
E 73
	} else if (argc != 2) {
E 40
		usage();
E 14
I 10
D 40

D 14
	printf("%s on %s", mp->m_dname, mp->m_path);
	if (strcmp(mp->m_type, FSTAB_RO) == 0)
		printf("\t(read-only)");
	if (strcmp(mp->m_type, FSTAB_RQ) == 0)
		printf("\t(with quotas)");
	putchar('\n');
E 14
I 14
D 16
	mountfs(argv[0], argv[1], type ? type : "rw");
I 15
	exit(rval);
E 16
I 16
D 22
	exit(mountfs(argv[0], argv[1], type ? type : "rw"));
E 22
I 22
D 28
	exit(mountfs(argv[0], argv[1], type ? type : "rw", options, NULL));
E 28
I 28
	exit(mountfs(argv[0], argv[1], updateflg, type, options, NULL));
E 40
I 40
D 77
		ret = 1;
E 77
I 77
		/* NOTREACHED */
E 77
	} else {
E 79
I 79
D 86
		rval = mountfs(fs->fs_vfstype, fs->fs_spec,
		    mntonname, init_flags, options, fs->fs_mntops);
E 86
I 86
		if ((fs = getfsfile(*argv)) == NULL &&
		    (fs = getfsspec(*argv)) == NULL)
			errx(1, "%s: unknown special file or file system.",
			    *argv);
		if (BADTYPE(fs->fs_type))
			errx(1, "%s has unknown file system type.",
			    *argv);
		rval = mountfs(fs->fs_vfstype, fs->fs_spec, fs->fs_file,
		    init_flags, options, fs->fs_mntops);
E 86
		break;
	case 2:
E 79
I 49
		/*
D 73
		 * If -t flag has not been specified, and spec
		 * contains either a ':' or a '@' then assume that
		 * an NFS filesystem is being specified ala Sun.
E 73
I 73
		 * If -t flag has not been specified, and spec contains either
		 * a ':' or a '@' then assume that an NFS filesystem is being
		 * specified ala Sun.
E 73
		 */
D 73
		if (vfslist == (char **)0 &&
E 73
I 73
D 81
		if (vfslist == NULL &&
E 73
D 59
		    (index(argv[0], ':') || index(argv[0], '@')))
E 59
I 59
D 71
		    (index(argv[0], ':') || index(argv[0], '@'))) {
E 71
I 71
D 79
		    (strchr(argv[0], ':') || strchr(argv[0], '@'))) {
E 71
E 59
			mnttype = MOUNT_NFS;
I 59
			mntname = "nfs";
		}
E 59
E 49
D 47
		ret = mountfs(argv[0], argv[1], updateflg, type, options, NULL);
E 47
I 47
D 73
		ret = mountfs(argv[0], argv[1], updateflg, type, options,
		    (char *)NULL);
E 73
I 73
D 77
		ret = mountfs(argv[0], argv[1], updateflg, type, options, NULL);
E 77
I 77
		rval =
		    mountfs(argv[0], argv[1], updateflg, type, options, NULL);
E 79
I 79
		    (strchr(argv[0], ':') != NULL ||
		    strchr(argv[0], '@') != NULL))
E 81
I 81
		if (vfslist == NULL && strpbrk(argv[0], ":@") != NULL)
E 81
			vfstype = "nfs";
		rval = mountfs(vfstype,
		    argv[0], argv[1], init_flags, options, NULL);
		break;
	default:
		usage();
		/* NOTREACHED */
E 79
E 77
E 73
E 47
	}
I 79

E 79
D 76
	if ((pidfile = fopen(_PATH_MOUNTDPID, "r")) != NULL) {
		pid = 0;
D 73
		fscanf(pidfile, "%d", &pid);
		fclose(pidfile);
		if (pid > 0)
			kill(pid, SIGHUP);
E 73
I 73
		(void)fscanf(pidfile, "%ld", &pid);
		(void)fclose(pidfile);
		if (pid > 0 && kill(pid, SIGHUP))
			err(1, "signal mountd");
E 76
I 76
	/*
D 77
	 * If the mount succeeded, and we're running as root,
	 * then tell mountd the good news.
E 77
I 77
D 79
	 * If the mount succeeded, and root did the mount, then tell
	 * mountd the good news.  Pid checks are probably unnecessary,
	 * but don't hurt.
E 79
I 79
	 * If the mount was successfully, and done by root, tell mountd the
	 * good news.  Pid checks are probably unnecessary, but don't hurt.
E 79
E 77
	 */
D 77
	if ((ret == 0) && (getuid() == 0)) {
		if ((pidfile = fopen(_PATH_MOUNTDPID, "r")) != NULL) {
			pid_t pid = 0;
			(void)fscanf(pidfile, "%ld", &pid);
			(void)fclose(pidfile);
			if (pid > 0 && kill(pid, SIGHUP))
				err(1, "signal mountd");
		}
E 77
I 77
	if (rval == 0 && getuid() == 0 &&
	    (mountdfp = fopen(_PATH_MOUNTDPID, "r")) != NULL) {
		if (fscanf(mountdfp, "%ld", &pid) == 1 &&
D 78
		    pid > 0 && pid != -1 && kill(pid, SIGHUP))
E 78
I 78
D 79
		    pid > 0 && kill(pid, SIGHUP))
E 79
I 79
D 82
		     pid > 0 && kill(pid, SIGHUP))
E 82
I 82
		     pid > 0 && kill(pid, SIGHUP) == -1 && errno != ESRCH)
E 82
E 79
E 78
			err(1, "signal mountd");
		(void)fclose(mountdfp);
E 77
E 76
E 73
	}
I 73

E 73
D 71
	exit (ret);
E 71
I 71
D 77
	exit(ret);
E 77
I 77
	exit(rval);
E 77
E 71
E 40
E 28
E 22
E 16
E 15
E 14
}

I 70
D 73
static int
E 73
I 73
int
I 83
hasopt(mntopts, option)
	const char *mntopts, *option;
{
	int negative, found;
	char *opt, *optbuf;

	if (option[0] == 'n' && option[1] == 'o') {
		negative = 1;
		option += 2;
	} else
		negative = 0;
	optbuf = strdup(mntopts);
	found = 0;
	for (opt = optbuf; (opt = strtok(opt, ",")) != NULL; opt = NULL) {
		if (opt[0] == 'n' && opt[1] == 'o') {
			if (!strcasecmp(opt + 2, option))
				found = negative;
		} else if (!strcasecmp(opt, option))
			found = !negative;
	}
	free(optbuf);
	return (found);
}

int
E 83
E 73
E 70
I 14
D 22
static
E 14
mountfs(spec, name, type)
	char *spec, *name, *type;
E 22
I 22
D 28
mountfs(spec, name, type, options, mntopts)
E 28
I 28
D 79
mountfs(spec, name, flags, type, options, mntopts)
E 28
	char *spec, *name, *type, *options, *mntopts;
E 79
I 79
mountfs(vfstype, spec, name, flags, options, mntopts)
	const char *vfstype, *spec, *name, *options, *mntopts;
E 79
I 28
	int flags;
E 28
E 22
{
E 10
D 5
	register	char	*np;
	register	struct	mtab	*mp;
	int	mf;
E 5
I 5
D 14
	register char *np;
	register struct mtab *mp;
	int mf;
E 14
I 14
D 52
	extern int errno;
E 52
D 21
	register struct mtab *mp, *space;
E 21
D 47
	register int cnt;
D 21
	register char *p;
I 20
#ifdef NFS
	register CLIENT *clp;
	struct hostent *hp;
	struct sockaddr_in saddr;
	struct timeval pertry, try;
	enum clnt_stat clnt_stat;
	int so = RPC_ANYSOCK;
	char *hostp, *delimp;
	u_short tport;
	struct nfhret nfhret;
	char nam[MNAMELEN+1];
#endif
E 20
D 18
	int fd;
E 18
I 18
	int fd, flags;
E 21
I 21
D 22
	int flags;
E 22
I 22
D 28
	int flags, argc, status, i;
E 28
I 28
	int argc, status, i;
E 47
I 47
D 70
	union wait status;
E 70
I 70
D 73
	int status;
E 70
	pid_t pid;
	int argc, i;
E 73
E 47
E 28
E 22
E 21
D 79
	struct ufs_args args;
E 79
I 79
	/* List of directories containing mount_xxx subcommands. */
	static const char *edirs[] = {
		_PATH_SBIN,
		_PATH_USRSBIN,
		NULL
	};
	const char *argv[100], **edir;
	struct statfs sf;
E 79
I 73
	pid_t pid;
	int argc, i, status;
E 73
I 45
D 58
	struct nfs_args nfsargs;
E 58
E 45
E 18
D 20
	char *index(), *rindex(), *strcpy();
E 20
I 20
D 22
	char *argp;
E 22
I 22
D 79
	char *argp, *argv[50];
I 26
D 73
	char execname[MAXPATHLEN + 1], flagval[12];
I 72
	char mntpath[MAXPATHLEN];
E 73
I 73
	char execname[MAXPATHLEN + 1], flagval[12], mntpath[MAXPATHLEN];
E 79
I 79
	char *optbuf, execname[MAXPATHLEN + 1], mntpath[MAXPATHLEN];
E 79
E 73
E 72
E 26
E 22
E 20
E 14
E 5

I 45
D 58
	nfsargs = nfsdefargs;
E 58
E 45
D 4
	if(mount(spec, name, ro) < 0) {
E 4
I 4
D 5
	if(fake==0 && mount(spec, name, ro) < 0)
E 4
D 3
		perror("mount");
E 3
		return(1);
E 5
I 5
D 10
	if (fake==0) {
		if (mount(spec, name, ro) < 0) {
E 10
I 10
D 24
	if (!fake) {
D 14
		if (mount(spec, name, strcmp(type, FSTAB_RO) == 0) < 0) {
I 11
			extern int errno;
			char *cp;

E 11
E 10
			fprintf(stderr, "%s on ", spec);
E 14
I 14
D 16
		if (mount(spec, name, type)) {
I 15
			rval = 1;
E 16
I 16
D 18
		if (mount(spec, name, !strcmp(type, FSTAB_RO))) {
E 18
I 18
		flags = 0;
		if (!strcmp(type, FSTAB_RO))
			flags |= M_RDONLY;
D 20
		args.fspec = spec;
		if (mount(MOUNT_UFS, name, flags, &args)) {
E 20
I 20
D 21
#ifdef NFS
E 21
		switch (mnttype) {
		case MOUNT_UFS:
I 22
			if (options)
				getufsopts(options, &flags);
			if (mntopts)
				getufsopts(mntopts, &flags);
E 22
			args.fspec = spec;
			argp = (caddr_t)&args;
			break;
E 24
I 24
D 28
	flags = 0;
	if (!strcmp(type, FSTAB_RO))
		flags |= M_RDONLY;
	if (options)
		getstdopts(options, &flags);
E 28
D 79
	if (mntopts)
		getstdopts(mntopts, &flags);
I 28
	if (options)
		getstdopts(options, &flags);
	if (type)
		getstdopts(type, &flags);
I 62
	if (force)
		flags |= MNT_FORCE;
I 72

	if (realpath(name, mntpath) == 0) {
E 79
I 79
	if (realpath(name, mntpath) == NULL) {
E 79
D 83
		warn("%s", mntpath);
E 83
I 83
		warn("realpath %s", mntpath);
E 83
		return (1);
	}

	name = mntpath;

I 83
	if (mntopts == NULL)
		mntopts = "";
E 83
I 79
D 81
	if (options == 0) {
		if (!mntopts || !*mntopts)
E 81
I 81
	if (options == NULL) {
D 83
		if (mntopts == NULL || *mntopts == '\0')
E 83
I 83
		if (*mntopts == '\0') {
E 83
E 81
			options = "rw";
D 83
		else
E 83
I 83
		} else {
E 83
			options = mntopts;
D 83
		mntopts = "";
E 83
I 83
			mntopts = "";
		}
E 83
D 81

E 81
	}
	optbuf = catopt(strdup(mntopts), options);

E 79
E 72
I 71
	if (strcmp(name, "/") == 0)
		flags |= MNT_UPDATE;
I 79
	if (flags & MNT_FORCE)
		optbuf = catopt(optbuf, "force");
	if (flags & MNT_RDONLY)
		optbuf = catopt(optbuf, "ro");
	/*
	 * XXX
	 * The mount_mfs (newfs) command uses -o to select the
	 * optimisation mode.  We don't pass the default "-o rw"
	 * for that reason.
	 */
	if (flags & MNT_UPDATE)
		optbuf = catopt(optbuf, "update");
E 79

E 71
E 62
E 28
I 26
D 27
	argc = 1;
E 27
E 26
D 79
	switch (mnttype) {
I 56
D 63
	case MOUNT_LFS:
E 63
E 56
	case MOUNT_UFS:
D 28
		if (options)
			getufsopts(options, &flags);
E 28
		if (mntopts)
			getufsopts(mntopts, &flags);
I 28
		if (options)
			getufsopts(options, &flags);
E 28
		args.fspec = spec;
I 73
#define	DEFAULT_ROOTUID	-2
E 73
I 39
D 66
		args.exroot = DEFAULT_ROOTUID;
E 66
I 66
		args.export.ex_root = DEFAULT_ROOTUID;
E 66
D 40
		args.exflags = getexportflags(name, flags);
E 40
I 40
D 44
		if (flags & M_RDONLY)
			args.exflags = M_EXRDONLY;
E 44
I 44
		if (flags & MNT_RDONLY)
D 66
			args.exflags = MNT_EXRDONLY;
E 66
I 66
			args.export.ex_flags = MNT_EXRDONLY;
E 66
E 44
		else
D 66
			args.exflags = 0;
E 66
I 66
			args.export.ex_flags = 0;
E 66
E 40
E 39
		argp = (caddr_t)&args;
		break;
E 24
I 21
D 73

E 73
D 58
#ifdef NFS
E 21
D 24
		case MOUNT_NFS:
I 22
			if (options)
				getnfsopts(options, &nfsargs, &opflags,
					&retrycnt);
			if (mntopts)
				getnfsopts(mntopts, &nfsargs, &opflags,
					&retrycnt);
E 22
D 21
			strncpy(nam, spec, MNAMELEN);
			nam[MNAMELEN] = '\0';
			if ((delimp = index(spec, '@')) != NULL) {
				hostp = delimp+1;
			} else if ((delimp = index(spec, ':')) != NULL) {
				hostp = spec;
				spec = delimp+1;
			} else {
				fprintf(stderr, "No <host>:<dirpath> or <dirpath>@<host> spec\n");
				return (1);
			}
			*delimp = '\0';
			if ((hp = gethostbyname(hostp)) == NULL) {
				fprintf(stderr,"Can't get net id for host\n");
				return (1);
			}
			bcopy(hp->h_addr,(caddr_t)&saddr.sin_addr,hp->h_length);
			nfhret.stat = EACCES;	/* Mark not yet successful */
			while (retrycnt > 0) {
				saddr.sin_family = AF_INET;
				saddr.sin_port = htons(PMAPPORT);
				if ((tport = pmap_getport(&saddr, RPCPROG_NFS,
					NFS_VER2, IPPROTO_UDP)) == 0) {
					if ((opflags & ISBGRND) == 0)
						clnt_pcreateerror("NFS Portmap");
				} else {
					saddr.sin_port = 0;
					pertry.tv_sec = 10;
					pertry.tv_usec = 0;
					if ((clp = clntudp_create(&saddr, RPCPROG_MNT,
						RPCMNT_VER1, pertry, &so)) == NULL) {
						if ((opflags & ISBGRND) == 0)
							clnt_pcreateerror("Cannot MNT PRC");
					} else {
						clp->cl_auth = authunix_create_default();
						try.tv_sec = 10;
						try.tv_usec = 0;
						clnt_stat = clnt_call(clp, RPCMNT_MOUNT, xdr_dir, spec,
							xdr_fh, &nfhret, try);
						if (clnt_stat != RPC_SUCCESS) {
							if ((opflags & ISBGRND) == 0)
								clnt_perror(clp, "Bad MNT RPC");
						} else {
							auth_destroy(clp->cl_auth);
							clnt_destroy(clp);
							retrycnt = 0;
						}
					}
				}
				if (--retrycnt > 0) {
					if (opflags & BGRND) {
						opflags &= ~BGRND;
						if (fork())
							return (0);
						else
							opflags |= ISBGRND;
					} 
					sleep(10);
				}
			}
			if (nfhret.stat) {
				if (opflags & ISBGRND)
					exit(1);
				fprintf(stderr, "Can't access %s, errno=%d\n",
					spec, nfhret.stat);
				return (1);
			}
			saddr.sin_port = htons(tport);
			nfsargs.addr = &saddr;
			nfsargs.fh = &nfhret.nfh;
			nfsargs.hostname = nam;
			argp = (caddr_t)&nfsargs;
			break;
E 21
I 21
			if (argp = getnfsargs(spec, name, type))
				break;
			return (1);
E 24
I 24
	case MOUNT_NFS:
I 33
		retrycnt = DEF_RETRY;
E 33
D 28
		if (options)
			getnfsopts(options, &nfsargs, &opflags,
				&retrycnt);
E 28
		if (mntopts)
D 28
			getnfsopts(mntopts, &nfsargs, &opflags,
				&retrycnt);
E 28
I 28
			getnfsopts(mntopts, &nfsargs, &opflags, &retrycnt);
		if (options)
			getnfsopts(options, &nfsargs, &opflags, &retrycnt);
E 28
D 45
		if (argp = getnfsargs(spec, name, type))
E 45
I 45
		if (argp = getnfsargs(spec, &nfsargs))
E 45
			break;
		return (1);
E 24
#endif /* NFS */

E 58
I 22
D 27
#ifdef MFS
E 27
D 24
		case MOUNT_MFS:
			argv[0] = "memfs";
			argc = 1;
			if (options)
				argc += getmfsopts(options, &argv[argc]);
			if (mntopts)
				argc += getmfsopts(mntopts, &argv[argc]);
			argv[argc++] = spec;
			argv[argc++] = name;
			if (i = vfork()) {
				if (i == -1) {
					perror("mount: vfork for memfs");
					return (1);
				}
				if (waitpid(i, &status, 0) != -1 &&
				    WIFEXITED(status) &&
				    WEXITSTATUS(status) != 0)
					return (WEXITSTATUS(status));
				spec = "memfs";
				goto out;
E 24
I 24
	case MOUNT_MFS:
I 58
	case MOUNT_NFS:
E 58
D 26
		argv[0] = "memfs";
		argc = 1;
E 26
I 26
D 27
		mntname = "memfs";
E 26
		if (options)
			argc += getmfsopts(options, &argv[argc]);
		if (mntopts)
			argc += getmfsopts(mntopts, &argv[argc]);
I 26
		/* fall through to */
#endif /* MFS */

E 27
	default:
		argv[0] = mntname;
I 27
		argc = 1;
E 27
		if (flags) {
			argv[argc++] = "-F";
D 73
			sprintf(flagval, "%d", flags);
E 73
I 73
			(void)snprintf(flagval, sizeof(flagval), "%d", flags);
E 73
			argv[argc++] = flagval;
E 79
I 79
	argc = 0;
	argv[argc++] = vfstype;
	mangle(optbuf, &argc, argv);
	argv[argc++] = spec;
	argv[argc++] = name;
	argv[argc] = NULL;

	if (debug) {
		(void)printf("exec: mount_%s", vfstype);
		for (i = 1; i < argc; i++)
			(void)printf(" %s", argv[i]);
		(void)printf("\n");
		return (0);
	}

	switch (pid = vfork()) {
	case -1:				/* Error. */
		warn("vfork");
		free(optbuf);
		return (1);
	case 0:					/* Child. */
I 80
		if (strcmp(vfstype, "ufs") == 0)
			exit(mount_ufs(argc, (char * const *) argv));

E 80
		/* Go find an executable. */
		edir = edirs;
		do {
			(void)snprintf(execname,
			    sizeof(execname), "%s/mount_%s", *edir, vfstype);
			execv(execname, (char * const *)argv);
			if (errno != ENOENT)
				warn("exec %s for %s", execname, name);
		} while (*++edir != NULL);

		if (errno == ENOENT)
			warn("exec %s for %s", execname, name);
		exit(1);
		/* NOTREACHED */
	default:				/* Parent. */
		free(optbuf);

		if (waitpid(pid, &status, 0) < 0) {
			warn("waitpid");
			return (1);
E 79
		}
I 27
D 28
		if (options)
			argc += getexecopts(options, &argv[argc]);
E 28
D 79
		if (mntopts)
			argc += getexecopts(mntopts, &argv[argc]);
I 28
		if (options)
			argc += getexecopts(options, &argv[argc]);
E 28
E 27
E 26
		argv[argc++] = spec;
		argv[argc++] = name;
I 30
		argv[argc++] = NULL;
E 30
I 26
D 31
		sprintf(execname, "%s/%s", _PATH_EXECDIR, mntname);
E 31
I 31
D 73
		sprintf(execname, "%s/mount_%s", _PATH_EXECDIR, mntname);
E 73
I 73
		snprintf(execname, sizeof(execname),
		    "%s/mount_%s", _PATH_EXECDIR, mntname);
E 73
E 31
E 26
		if (verbose) {
D 26
			printf("exec:");
			for (i = 0; i < argc; i++)
E 26
I 26
D 47
			printf("exec: %s", execname);
			for (i = 1; i < argc; i++)
E 26
				printf(" %s", argv[i]);
			printf("\n");
E 47
I 47
			(void)printf("exec: %s", execname);
			for (i = 1; i < argc - 1; i++)
				(void)printf(" %s", argv[i]);
			(void)printf("\n");
E 47
		}
D 62
		if (fake)
E 62
I 62
		if (debug)
E 62
			break;
D 47
		if (i = vfork()) {
			if (i == -1) {
E 47
I 47
		if (pid = vfork()) {
			if (pid == -1) {
E 47
D 26
				perror("mount: vfork for memfs");
E 26
I 26
D 71
				perror("mount: vfork starting file system");
E 71
I 71
				warn("vfork starting file system");
E 71
E 26
				return (1);
E 24
			}
D 24
			execve(_PATH_MEMFS, argv, envp);
			perror(_PATH_MEMFS);
			exit (1);
E 24
I 24
D 47
			if (waitpid(i, &status, 0) != -1 &&
E 47
I 47
D 55
			if (waitpid(pid, &status, 0) != -1 &&
E 55
I 55
D 70
			if (waitpid(pid, (int *)&status, 0) != -1 &&
E 70
I 70
			if (waitpid(pid, &status, 0) != -1 &&
E 70
E 55
E 47
			    WIFEXITED(status) &&
			    WEXITSTATUS(status) != 0)
E 79
I 79

		if (WIFEXITED(status)) {
			if (WEXITSTATUS(status) != 0)
E 79
				return (WEXITSTATUS(status));
D 26
			spec = "memfs";
E 26
I 26
D 79
			spec = mntname;
E 26
			goto out;
E 79
I 79
		} else if (WIFSIGNALED(status)) {
			warnx("%s: %s", name, sys_siglist[WTERMSIG(status)]);
			return (1);
E 79
		}
D 26
		execve(_PATH_MEMFS, argv, envp);
		perror(_PATH_MEMFS);
E 26
I 26
D 70
		execve(execname, argv, envp);
E 70
I 70
D 79
		execv(execname, argv);
E 70
D 31
		perror(execname);
E 31
I 31
D 54
		fprintf(stderr, "mount: cannot exec %s for %s: ",
E 54
I 54
D 71
		(void) fprintf(stderr, "mount: cannot exec %s for %s: ",
E 54
			execname, name);
D 47
		perror("");
E 47
I 47
		perror((char *)NULL);
E 47
E 31
E 26
D 70
		exit (1);
E 70
I 70
		exit(1);
E 71
I 71
		err(1, "cannot exec %s for %s", execname, name);
E 71
E 70
E 24
D 26
#endif /* MFS */

E 22
D 24
		default:
			if (opflags & ISBGRND)
				exit(1);
			fprintf(stderr, "%d: unknown mount type\n", mnttype);
E 24
I 24
	default:
		if (opflags & ISBGRND)
E 24
			exit(1);
D 24
			/* NOTREACHED */
E 24
I 24
		fprintf(stderr, "%d: unknown mount type\n", mnttype);
		exit(1);
E 26
		/* NOTREACHED */
E 79
E 24

E 21
D 24
		};
D 21
#endif
E 21
		if (mount(mnttype, name, flags, argp)) {
			if (opflags & ISBGRND)
				exit(1);
E 20
E 18
E 16
E 15
			fprintf(stderr, "%s on %s: ", spec, name);
E 14
D 11
			perror(name);
E 11
I 11
			switch (errno) {
D 14

E 14
			case EMFILE:
D 14
				cp = "Mount table full";
E 14
I 14
				fprintf(stderr, "Mount table full\n");
E 14
				break;
D 14

E 14
			case EINVAL:
D 14
				cp = "Bogus super block";
E 14
I 14
				fprintf(stderr, "Bogus super block\n");
E 14
				break;
D 14

E 14
			default:
D 14
				perror(name);
				return;
E 14
I 14
				perror((char *)NULL);
				break;
E 14
			}
D 14
			fprintf(stderr, "%s: %s\n", name, cp);
E 14
E 11
D 16
			return;
E 16
I 16
			return(1);
E 24
I 24
D 79
	}
D 62
	if (!fake && mount(mnttype, name, flags, argp)) {
E 62
I 62
	if (!debug && mount(mnttype, name, flags, argp)) {
E 62
D 58
		if (opflags & ISBGRND)
			exit(1);
E 58
D 54
		fprintf(stderr, "%s on %s: ", spec, name);
E 54
I 54
D 73
		(void) fprintf(stderr, "%s on %s: ", spec, name);
E 73
I 73
		(void)fprintf(stderr, "%s on %s: ", spec, name);
E 73
E 54
		switch (errno) {
		case EMFILE:
D 54
			fprintf(stderr, "Mount table full\n");
E 54
I 54
D 73
			(void) fprintf(stderr, "Mount table full\n");
E 73
I 73
D 74
			(void)fprintf(stderr, "Mount table full\n");
E 74
I 74
			(void)fprintf(stderr, "Mount table full.\n");
E 74
E 73
E 54
			break;
		case EINVAL:
D 28
			fprintf(stderr, "Bogus super block\n");
E 28
I 28
D 44
			if (flags & M_UPDATE)
E 44
I 44
			if (flags & MNT_UPDATE)
E 44
D 54
				fprintf(stderr, "Specified device does %s\n",
					"not match mounted device");
E 54
I 54
D 73
				(void) fprintf(stderr, "Specified device %s\n",
E 73
I 73
				(void)fprintf(stderr, "Specified device %s\n",
E 73
					"does not match mounted device");
E 54
D 53
			else
E 53
I 53
			else if (mnttype == MOUNT_UFS)
E 53
D 54
				fprintf(stderr, "Bogus super block\n");
E 54
I 54
D 73
				(void) fprintf(stderr, "Bogus super block\n");
E 73
I 73
				(void)fprintf(stderr, "Bogus super block\n");
E 73
E 54
I 53
			else
D 73
				perror((char *)NULL);
E 73
I 73
				perror(NULL);
E 73
E 53
E 28
			break;
I 28
D 54
		case EOPNOTSUPP:
			fprintf(stderr, "Operation not supported\n");
			break;
E 54
E 28
		default:
D 73
			perror((char *)NULL);
E 73
I 73
			perror(NULL);
E 73
			break;
E 79
I 79
		if (verbose) {
			if (statfs(name, &sf) < 0) {
D 83
				warn("%s", name);
E 83
I 83
				warn("statfs %s", name);
E 83
				return (1);
			}
D 84
			prmount(sf.f_mntfromname, sf.f_mntonname, sf.f_flags);
E 84
I 84
			prmount(&sf);
E 84
E 79
E 24
E 16
		}
I 24
D 70
		return(1);
E 70
I 70
D 79
		return (1);
E 79
I 79
		break;
E 79
E 70
E 24
I 14
D 22

E 22
E 14
I 10
D 21
		/* we don't do quotas.... */
		if (strcmp(type, FSTAB_RQ) == 0)
			type = FSTAB_RW;
E 21
E 10
	}
D 10
	if (verbose)
		fprintf(stderr, "%s on %s%s\n", spec, name,
		    ro ? " read only" : "");
E 5
D 4
	}
E 4
	np = spec;
D 5
	while(*np++)
E 5
I 5
	while (*np++)
E 5
		;
	np--;
E 10
I 10
D 14
	np = index(spec, '\0');
E 10
D 5
	while(*--np == '/')
E 5
I 5
	while (*--np == '/')
E 5
		*np = '\0';
D 5
	while(np > spec && *--np != '/')
E 5
I 5
D 10
	while (np > spec && *--np != '/')
E 5
		;
D 5
	if(*np == '/')
E 5
I 5
	if (*np == '/')
E 5
		np++;
	spec = np;
E 10
I 10
	np = rindex(spec, '/');
	if (np) {
		*np++ = '\0';
		spec = np;
E 14
I 14

I 22
D 73
out:
E 22
D 21
	/* trim trailing /'s and find last component of name */
	for (p = index(spec, '\0'); *--p == '/';);
	*++p = '\0';
	if (p = rindex(spec, '/')) {
		*p = '\0';
		spec = p + 1;
E 14
	}
E 10
D 5
	for (mp = mtab; mp < &mtab[NMOUNT]; mp++) {
		if (mp->file[0] == 0) {
			for (np = mp->spec; np < &mp->spec[NAMSIZ-1];)
				if ((*np++ = *spec++) == 0)
					spec--;
			for (np = mp->file; np < &mp->file[NAMSIZ-1];)
				if ((*np++ = *name++) == 0)
					name--;
			mp = &mtab[NMOUNT];
			while ((--mp)->file[0] == 0);
			mf = creat("/etc/mtab", 0644);
			write(mf, (char *)mtab, (mp-mtab+1)*2*NAMSIZ);
I 2
			return(0);
E 2
		}
	}
	return(0);
E 5
I 5
D 14
	for (mp = mtab; mp < &mtab[NMOUNT]; mp++)
D 10
		if (!strcmp(mp->spec, spec))
E 10
I 10
		if (strcmp(mp->m_dname, spec) == 0)
E 10
			goto replace;
	for (mp = mtab; mp < &mtab[NMOUNT]; mp++)
D 10
		if (mp->file[0] == 0)
E 10
I 10
		if (mp->m_path[0] == '\0')
E 10
			goto replace;
	return;
replace:
D 10
	for (np = mp->spec; np < &mp->spec[NAMSIZ-1];)
		if ((*np++ = *spec++) == 0)
			spec--;
	for (np = mp->file; np < &mp->file[NAMSIZ-1];)
		if ((*np++ = *name++) == 0)
			name--;
	mp = &mtab[NMOUNT];
	while ((--mp)->file[0] == 0);
E 10
I 10
	strncpy(mp->m_dname, spec, DNMAX);
E 14
I 14

	for (mp = mtab, cnt = NMOUNT, space = NULL; cnt--; ++mp) {
		if (!strcmp(mp->m_dname, spec))
			break;
		if (!space && !*mp->m_path)
			space = mp;
	}
	if (cnt == -1) {
		if (!space) {
D 20
			fprintf(stderr, "mount: no more room in %s.\n", MTAB);
E 20
I 20
			if ((opflags & ISBGRND) == 0)
				fprintf(stderr, "mount: no more room in %s.\n", MTAB);
E 20
			exit(1);
		}
		mp = space;
	}

#define	DNMAX	(sizeof(mtab[0].m_dname) - 1)
#define	PNMAX	(sizeof(mtab[0].m_path) - 1)

	(void)strncpy(mp->m_dname, spec, DNMAX);
E 14
	mp->m_dname[DNMAX] = '\0';
D 14
	strncpy(mp->m_path, name, PNMAX);
E 14
I 14
	(void)strncpy(mp->m_path, name, PNMAX);
E 14
	mp->m_path[PNMAX] = '\0';
D 14
	strcpy(mp->m_type, type);
E 14
I 14
	(void)strcpy(mp->m_type, type);

E 21
E 14
	if (verbose)
E 73
I 73
D 79
out:	if (verbose)
E 73
D 21
		prmtab(mp);
E 21
I 21
D 24
		prmount(spec, name, type);
E 24
I 24
		prmount(spec, name, flags);
E 79
E 24
E 21
D 14
	mp = mtab + NMOUNT - 1;
	while (mp > mtab && mp->m_path[0] == '\0')
		--mp;
E 10
	mf = creat("/etc/mtab", 0644);
D 10
	write(mf, (char *)mtab, (mp-mtab+1)*2*NAMSIZ);
E 10
I 10
	write(mf, (char *)mtab, (mp - mtab + 1) * sizeof (struct mtab));
E 10
	close(mf);
	return;
E 14
I 14
D 73

E 73
D 21
	for (mp = mtab + NMOUNT - 1; mp > mtab && !*mp->m_path; --mp);
	if ((fd = open(MTAB, O_WRONLY|O_CREAT|O_TRUNC, 0644)) < 0)
		mtaberr();
	cnt = (mp - mtab + 1) * sizeof(struct mtab);
	/* NOSTRICT */
	if (write(fd, (char *)mtab, cnt) != cnt)
		mtaberr();
	(void)close(fd);
E 21
I 16
D 20
	return(0);
E 20
I 20
D 58
	if (opflags & ISBGRND)
D 47
		exit();
	else
		return(0);
E 47
I 47
		exit(1);
E 58
D 70
	return(0);
E 70
I 70
	return (0);
E 70
E 47
E 20
E 16
}

D 55
static
E 55
I 55
D 73
static void
E 73
I 73
void
E 73
E 55
D 21
prmtab(mp)
	register struct mtab *mp;
E 21
I 21
D 24
prmount(spec, name, type)
	char *spec, *name, *type;
E 24
I 24
D 84
prmount(spec, name, flags)
D 79
	char *spec, *name;
E 79
I 79
	const char *spec, *name;
E 79
D 47
	long flags;
E 47
I 47
D 70
	register short flags;
E 70
I 70
	int flags;
E 84
I 84
prmount(sfp)
	struct statfs *sfp;
E 84
E 70
E 47
E 24
E 21
{
I 84
	int flags;
E 84
I 47
D 70
	register int first;
E 70
I 70
D 79
	int first;
E 79
I 79
	struct opt *o;
I 84
	struct passwd *pw;
E 84
	int f;
E 79
E 70
E 47
I 21
D 38
	register char *root;
E 38

E 21
I 20
D 58
	if (opflags & ISBGRND)
		return;
E 58
E 20
D 21
	printf("%s on %s", mp->m_dname, mp->m_path);
	if (!strcmp(mp->m_type, FSTAB_RO))
E 21
I 21
D 38
	/*
	 * trim trailing /'s and find last component of name
	 */
	for (root = index(spec, '\0'); *--root == '/';)
		/* void */;
	*++root = '\0';
	if (root = rindex(spec, '/'))
		spec = root + 1;
E 38
D 47
	printf("%s on %s", spec, name);
E 47
I 47
D 84
	(void)printf("%s on %s", spec, name);
E 84
I 84
	(void)printf("%s on %s", sfp->f_mntfromname, sfp->f_mntonname);
E 84
D 79
	if (!(flags & MNT_VISFLAGMASK)) {
		(void)printf("\n");
		return;
	}
	first = 0;
#define	PR(msg)	(void)printf("%s%s", !first++ ? " (" : ", ", msg)
E 47
D 24
	if (!strcmp(type, FSTAB_RO))
E 21
		printf("\t(read-only)");
D 21
	else if (!strcmp(mp->m_type, FSTAB_RQ))
E 21
I 21
	else if (!strcmp(type, FSTAB_RQ))
E 21
		printf("\t(with quotas)");
E 24
I 24
D 44
	if (flags & M_RDONLY)
E 44
I 44
	if (flags & MNT_RDONLY)
E 44
D 47
		printf(" (read-only)");
E 47
I 47
		PR("read-only");
E 47
D 44
	if (flags & M_NOEXEC)
E 44
I 44
	if (flags & MNT_NOEXEC)
E 44
D 47
		printf(" (noexec)");
E 47
I 47
		PR("noexec");
E 47
D 44
	if (flags & M_NOSUID)
E 44
I 44
	if (flags & MNT_NOSUID)
E 44
D 47
		printf(" (nosuid)");
E 47
I 47
		PR("nosuid");
E 47
D 44
	if (flags & M_NODEV)
E 44
I 44
	if (flags & MNT_NODEV)
E 44
D 47
		printf(" (nodev)");
E 47
I 47
		PR("nodev");
E 47
D 44
	if (flags & M_SYNCHRONOUS)
E 44
I 44
	if (flags & MNT_SYNCHRONOUS)
E 44
D 47
		printf(" (synchronous)");
E 47
I 47
		PR("synchronous");
I 65
	if (flags & MNT_ASYNC)
		PR("asynchronous");
E 65
E 47
I 28
D 43
	if (flags & M_UPDATE)
		printf(" (update only)");
E 43
I 43
D 44
	if (flags & M_QUOTA)
E 44
I 44
	if (flags & MNT_QUOTA)
E 44
D 47
		printf(" (with quotas)");
E 47
I 47
		PR("with quotas");
E 47
D 44
	if (flags & M_LOCAL)
E 44
I 44
	if (flags & MNT_LOCAL)
E 44
D 47
		printf(" (local)");
E 47
I 47
		PR("local");
I 75
	if (flags & MNT_USER)
		PR("user mount");
E 75
I 61
	if (flags & MNT_UNION)
		PR("union");
E 61
E 47
D 44
	if (flags & M_EXPORTED)
		if (flags & M_EXRDONLY)
E 44
I 44
	if (flags & MNT_EXPORTED)
D 58
		if (flags & MNT_EXRDONLY)
E 44
D 47
			printf(" (NFS exported read-only)");
E 47
I 47
			PR("NFS exported read-only");
E 47
		else
D 47
			printf(" (NFS exported)");
E 43
E 28
E 24
	printf("\n");
E 47
I 47
			PR("NFS exported");
E 58
I 58
		PR("NFS exported");
E 58
	(void)printf(")\n");
E 47
}
E 79

I 70
D 73
static int
E 73
I 73
D 79
int
E 73
E 70
D 23
static
E 23
I 23
getmnttype(fstype)
	char *fstype;
{

I 26
	mntname = fstype;
E 26
D 73
	if (!strcmp(fstype, "ufs"))
		return (MOUNT_UFS);
D 69
	if (!strcmp(fstype, "nfs"))
		return (MOUNT_NFS);
	if (!strcmp(fstype, "mfs"))
		return (MOUNT_MFS);
I 56
	if (!strcmp(fstype, "lfs"))
		return (MOUNT_LFS);
I 66
D 68
	if (!strcmp(fstype, "isofs"))
		return (MOUNT_ISOFS);
E 68
I 68
	if (!strcmp(fstype, "iso9660fs"))
		return (MOUNT_CD9660);
E 69
E 68
E 66
E 56
	return (0);
E 73
I 73
	return (strcmp(fstype, "ufs") == 0 ? MOUNT_UFS : 0);
E 73
}

I 70
D 73
static void
E 70
E 23
D 21
mtaberr()
{
I 20
	if (opflags & ISBGRND)
		exit(1);
E 20
	fprintf(stderr, "mount: %s: ", MTAB);
	perror((char *)NULL);
	exit(1);
}

static
E 21
usage()
{
D 16
	fprintf(stderr, "usage: mount [-arw]\nor mount [-rw] special | node\nor mount [-rw] special node\n");
E 16
I 16
D 28
	fprintf(stderr, "usage: mount [-afrw]\nor mount [-frw] special | node\nor mount [-frw] special node\n");
E 28
I 28
D 42
	fprintf(stderr, "usage: mount [-afurw]\nor mount [-furw] special | node\nor mount [-furw] special node\n");
E 42
I 42

D 54
	fprintf(stderr, "usage:\n  mount %s %s\n  mount %s\n  mount %s\n",
E 54
I 54
	(void) fprintf(stderr,
		"usage:\n  mount %s %s\n  mount %s\n  mount %s\n",
E 54
D 58
		"[ -frwu ] [ -t nfs | ufs | external_type ]",
E 58
I 58
		"[ -frwu ] [ -t ufs | external_type ]",
E 58
		"[ -o options ] special node",
D 58
		"[ -afrwu ] [ -t nfs | ufs | external_type ]",
E 58
I 58
		"[ -afrwu ] [ -t ufs | external_type ]",
E 58
		"[ -frwu ] special | node");
E 42
E 28
E 16
	exit(1);
I 24
}

I 70
static void
E 73
I 73
void
E 73
E 70
getstdopts(options, flagp)
	char *options;
D 47
	long *flagp;
E 47
I 47
	int *flagp;
E 47
{
D 70
	register char *opt;
E 70
I 70
D 73
	char *opt;
E 73
E 70
	int negative;
D 47
	char *optbuf[BUFSIZ], *strtok();
E 47
I 47
D 73
	char optbuf[BUFSIZ];
E 73
I 73
	char *opt, optbuf[BUFSIZ];
E 73
E 47

D 47
	strcpy(optbuf, options);
	for (opt = strtok(optbuf, ","); opt; opt = strtok(NULL, ",")) {
E 47
I 47
	(void)strcpy(optbuf, options);
D 73
	for (opt = strtok(optbuf, ","); opt; opt = strtok((char *)NULL, ",")) {
E 73
I 73
	for (opt = strtok(optbuf, ","); opt; opt = strtok(NULL, ",")) {
E 73
I 67
		if (opt[0] == '-')
			continue;
E 67
E 47
		if (opt[0] == 'n' && opt[1] == 'o') {
			negative++;
			opt += 2;
D 73
		} else {
E 73
I 73
		} else
E 73
			negative = 0;
D 73
		}
E 73
I 28
		if (!negative && !strcasecmp(opt, FSTAB_RO)) {
D 44
			*flagp |= M_RDONLY;
E 44
I 44
			*flagp |= MNT_RDONLY;
E 44
			continue;
E 79
I 79
D 84
	flags &= MNT_VISFLAGMASK;
E 84
I 84
	flags = sfp->f_flags & MNT_VISFLAGMASK;
E 84
	for (f = 0, o = optnames; flags && o->o_opt; o++)
		if (flags & o->o_opt) {
			(void)printf("%s%s", !f++ ? " (" : ", ", o->o_name);
			flags &= ~o->o_opt;
E 79
		}
I 84
	if (sfp->f_owner) {
		(void)printf("%smounted by ", !f++ ? " (" : ", ");
		if ((pw = getpwuid(sfp->f_owner)) != NULL)
			(void)printf("%s", pw->pw_name);
		else
			(void)printf("%d", sfp->f_owner);
	}
E 84
D 79
		if (!negative && !strcasecmp(opt, FSTAB_RW)) {
D 44
			*flagp &= ~M_RDONLY;
E 44
I 44
			*flagp &= ~MNT_RDONLY;
E 44
			continue;
		}
E 28
		if (!strcasecmp(opt, "exec")) {
			if (negative)
D 44
				*flagp |= M_NOEXEC;
E 44
I 44
				*flagp |= MNT_NOEXEC;
E 44
I 28
			else
D 44
				*flagp &= ~M_NOEXEC;
E 44
I 44
				*flagp &= ~MNT_NOEXEC;
E 44
E 28
			continue;
		}
		if (!strcasecmp(opt, "suid")) {
			if (negative)
D 44
				*flagp |= M_NOSUID;
E 44
I 44
				*flagp |= MNT_NOSUID;
E 44
I 28
			else
D 44
				*flagp &= ~M_NOSUID;
E 44
I 44
				*flagp &= ~MNT_NOSUID;
E 44
E 28
			continue;
		}
		if (!strcasecmp(opt, "dev")) {
			if (negative)
D 44
				*flagp |= M_NODEV;
E 44
I 44
				*flagp |= MNT_NODEV;
E 44
I 28
			else
D 44
				*flagp &= ~M_NODEV;
E 44
I 44
				*flagp &= ~MNT_NODEV;
E 44
E 28
			continue;
		}
		if (!strcasecmp(opt, "synchronous")) {
			if (!negative)
D 44
				*flagp |= M_SYNCHRONOUS;
E 44
I 44
				*flagp |= MNT_SYNCHRONOUS;
E 44
I 28
			else
D 44
				*flagp &= ~M_SYNCHRONOUS;
E 44
I 44
				*flagp &= ~MNT_SYNCHRONOUS;
I 65
			continue;
		}
		if (!strcasecmp(opt, "asynchronous")) {
			if (!negative)
				*flagp |= MNT_ASYNC;
			else
				*flagp &= ~MNT_ASYNC;
E 65
I 61
			continue;
		}
		if (!strcasecmp(opt, "union")) {
			if (!negative)
				*flagp |= MNT_UNION;
			else
				*flagp &= ~MNT_UNION;
E 61
E 44
E 28
			continue;
		}
I 67
D 73
		(void) fprintf(stderr, "mount: %s: unknown option\n", opt);
E 73
I 73
		(void)fprintf(stderr, "mount: %s: unknown option\n", opt);
E 73
E 67
	}
E 79
I 79
	(void)printf(f ? ")\n" : "\n");
E 79
E 24
E 14
E 5
}
I 20

I 47
D 79
/* ARGSUSED */
I 70
D 73
static void
E 73
I 73
void
E 73
E 70
E 47
I 22
getufsopts(options, flagp)
	char *options;
D 47
	long *flagp;
E 47
I 47
	int *flagp;
E 47
{
I 70

E 70
D 47

E 47
	return;
}

I 70
D 73
static int
E 73
I 73
int
E 73
E 70
D 27
#ifdef MFS
getmfsopts(options, argv)
E 27
I 27
getexecopts(options, argv)
E 27
D 73
	char *options;
	char **argv;
E 73
I 73
	char *options, **argv;
E 73
{
D 70
	register int argc = 0;
	register char *opt;
E 70
I 70
D 73
	int argc = 0;
E 73
I 73
	int argc;
E 73
	char *opt;
E 70
D 47
	char *strtok();
E 47

D 47
	for (opt = strtok(options, ","); opt; opt = strtok(NULL, ",")) {
E 47
I 47
D 73
	for (opt = strtok(options, ","); opt; opt = strtok((char *)NULL, ",")) {
E 73
I 73
	argc = 0;
	for (opt = strtok(options, ","); opt; opt = strtok(NULL, ",")) {
E 73
E 47
		if (opt[0] != '-')
			continue;
		argv[argc++] = opt;
		if (opt[2] == '\0' || opt[2] != '=')
			continue;
		opt[2] = '\0';
		argv[argc++] = &opt[3];
	}
	return (argc);
I 29
}

E 79
D 70
struct statfs *
E 70
I 70
D 73
static struct statfs *
E 73
I 73
struct statfs *
E 73
E 70
getmntpt(name)
D 79
	char *name;
E 79
I 79
	const char *name;
E 79
{
D 73
	long mntsize;
D 70
	register long i;
E 70
I 70
	long i;
E 73
E 70
	struct statfs *mntbuf;
I 73
D 79
	long i, mntsize;
E 79
I 79
	int i, mntsize;
E 79
E 73

D 37
	mntsize = getmntinfo(&mntbuf);
E 37
I 37
	mntsize = getmntinfo(&mntbuf, MNT_NOWAIT);
E 37
D 79
	for (i = 0; i < mntsize; i++) {
		if (!strcmp(mntbuf[i].f_mntfromname, name) ||
		    !strcmp(mntbuf[i].f_mntonname, name))
E 79
I 79
	for (i = 0; i < mntsize; i++)
		if (strcmp(mntbuf[i].f_mntfromname, name) == 0 ||
		    strcmp(mntbuf[i].f_mntonname, name) == 0)
E 79
			return (&mntbuf[i]);
D 79
	}
E 79
D 73
	return ((struct statfs *)0);
E 73
I 73
	return (NULL);
E 73
I 33
D 88
}

D 73
static int skipvfs;

I 70
static int
E 73
I 73
int
E 73
E 70
D 79
badvfstype(vfstype, vfslist)
D 41
	char *vfstype;
E 41
I 41
D 47
	long vfstype;
E 47
I 47
D 70
	short vfstype;
E 70
I 70
	int vfstype;
E 70
E 47
E 41
	char **vfslist;
E 79
I 79
badvfsname(vfsname, vfslist)
	const char *vfsname;
	const char **vfslist;
E 79
{

D 73
	if (vfslist == 0)
E 73
I 73
	if (vfslist == NULL)
E 73
D 70
		return(0);
E 70
I 70
		return (0);
E 70
D 73
	while (*vfslist) {
E 73
I 73
	while (*vfslist != NULL) {
E 73
D 41
		if (strcmp(vfstype, *vfslist) == 0)
E 41
I 41
D 79
		if (vfstype == getmnttype(*vfslist))
E 79
I 79
		if (strcmp(vfsname, *vfslist) == 0)
E 79
D 70
			return(skipvfs);
E 70
I 70
			return (skipvfs);
E 70
D 79
		vfslist++;
E 79
I 79
		++vfslist;
E 79
	}
	return (!skipvfs);
D 85
}

I 70
D 73
static int
E 73
I 73
int
E 73
E 70
D 79
badvfsname(vfsname, vfslist)
	char *vfsname;
	char **vfslist;
E 79
I 79
badvfstype(vfstype, vfslist)
	int vfstype;
	const char **vfslist;
E 79
{
I 79
static const char *vfsnames[] = INITMOUNTNAMES;
E 79

D 73
	if (vfslist == 0)
E 73
I 73
D 79
	if (vfslist == NULL)
E 79
I 79
	if ((vfstype < 0) || (vfstype > MOUNT_MAXTYPE))
E 79
E 73
D 70
		return(0);
E 70
I 70
		return (0);
E 70
D 73
	while (*vfslist) {
E 73
I 73
D 79
	while (*vfslist != NULL) {
E 73
		if (strcmp(vfsname, *vfslist) == 0)
E 41
D 70
			return(skipvfs);
E 70
I 70
			return (skipvfs);
E 70
		vfslist++;
	}
	return (!skipvfs);
E 79
I 79

	return (badvfsname(vfsnames[vfstype], vfslist));
E 85
E 79
}

D 70
char **
E 70
I 70
D 73
static char **
E 73
I 73
D 79
char **
E 79
I 79
const char **
E 79
E 73
E 70
makevfslist(fslist)
	char *fslist;
{
I 79
	const char **av;
E 79
D 70
	register char **av, *nextcp;
	register int i;
E 70
I 70
D 73
	char **av, *nextcp;
E 73
	int i;
I 73
D 79
	char **av, *nextcp;
E 79
I 79
	char *nextcp;
E 79
E 73
E 70
D 47
	char *malloc();
E 47

	if (fslist == NULL)
		return (NULL);
	if (fslist[0] == 'n' && fslist[1] == 'o') {
		fslist += 2;
		skipvfs = 1;
	}
	for (i = 0, nextcp = fslist; *nextcp; nextcp++)
		if (*nextcp == ',')
			i++;
D 47
	av = (char **)malloc((i+2) * sizeof(char *));
E 47
I 47
D 73
	av = (char **)malloc((size_t)(i+2) * sizeof(char *));
E 73
I 73
D 79
	av = malloc((size_t)(i + 2) * sizeof(char *));
E 73
E 47
	if (av == NULL)
E 79
I 79
	if ((av = malloc((size_t)(i + 2) * sizeof(char *))) == NULL) {
		warn(NULL);
E 79
		return (NULL);
I 79
	}
E 79
	nextcp = fslist;
	i = 0;
	av[i++] = nextcp;
D 73
	while (nextcp = index(nextcp, ',')) {
E 73
I 73
D 79
	while ((nextcp = index(nextcp, ',')) != NULL) {
E 79
I 79
	while ((nextcp = strchr(nextcp, ',')) != NULL) {
E 79
E 73
		*nextcp++ = '\0';
		av[i++] = nextcp;
	}
D 73
	av[i++] = 0;
E 73
I 73
	av[i++] = NULL;
E 73
	return (av);
E 88
I 73
}

I 79
char *
catopt(s0, s1)
	char *s0;
	const char *s1;
{
	size_t i;
	char *cp;

	if (s0 && *s0) {
		i = strlen(s0) + strlen(s1) + 1 + 1;
		if ((cp = malloc(i)) == NULL)
			err(1, NULL);
		(void)snprintf(cp, i, "%s,%s", s0, s1);
	} else
		cp = strdup(s1);

	if (s0)
		free(s0);
	return (cp);
}

E 79
void
I 79
mangle(options, argcp, argv)
	char *options;
	int *argcp;
	const char **argv;
{
	char *p, *s;
	int argc;

	argc = *argcp;
	for (s = options; (p = strsep(&s, ",")) != NULL;)
		if (*p != '\0')
			if (*p == '-') {
				argv[argc++] = p;
				p = strchr(p, '=');
				if (p) {
					*p = '\0';
					argv[argc++] = p+1;
				}
			} else if (strcmp(p, "rw") != 0) {
				argv[argc++] = "-o";
				argv[argc++] = p;
			}

	*argcp = argc;
}

void
E 79
usage()
{

	(void)fprintf(stderr,
D 75
		"usage:\n  mount %s %s\n  mount %s\n  mount %s\n",
		"[ -frwu ] [ -t ufs | external_type ]",
		"[ -o options ] special node",
		"[ -afrwu ] [ -t ufs | external_type ]",
		"[ -frwu ] special | node");
E 75
I 75
D 79
		"usage: %s %s\n       %s\n       %s\n",
		"mount [-dfruvw] [-t ufs | external_type]",
			"[-o options] special node",
		"mount [-adfruvw] [-t ufs | external_type]",
		"mount [-dfruvw] special | node");
E 79
I 79
		"usage: mount %s %s\n       mount %s\n       mount %s\n",
		"[-dfruvw] [-o options] [-t ufs | external_type]",
			"special node",
		"[-adfruvw] [-t ufs | external_type]",
		"[-dfruvw] special | node");
E 79
E 75
	exit(1);
E 73
I 39
D 40
}

/*
 * Check to see if a UFS filesystem is being exported.
 */
getexportflags(name, mntflags)
	char *name;
	int mntflags;
{
	FILE *fd;
	int flags = 0;
	char *cp, line[BUFSIZ];

	if (mntflags & M_RDONLY)
		flags |= M_EXRDONLY;
	if ((fd = fopen(_PATH_EXPORTS, "r")) == NULL)
		return (flags);
	while (fgets(line, BUFSIZ, fd)) {
		cp = strtok(line, " \t\n");
		if (strcmp(cp, name))
			continue;
		flags |= M_EXPORTED;
		break;
	}
	fclose(fd);
	return (flags);
E 40
E 39
E 33
E 29
}
D 27
#endif /* MFS */
E 27
D 58

E 22
#ifdef NFS
I 54
exclusive(a, b)
	char *a, *b;
{

	(void) fprintf(stderr, "mount: Options %s, %s mutually exclusive\n",
	    a, b);
	exit(1);
}

E 54
I 22
/*
 * Handle the getoption arg.
 * Essentially update "opflags", "retrycnt" and "nfsargs"
 */
getnfsopts(optarg, nfsargsp, opflagsp, retrycntp)
	char *optarg;
D 54
	struct nfs_args *nfsargsp;
E 54
I 54
	register struct nfs_args *nfsargsp;
E 54
	int *opflagsp;
	int *retrycntp;
{
	register char *cp, *nextcp;
	int num;
	char *nump;

D 54
	cp = optarg;
	while (cp != NULL && *cp != '\0') {
E 54
I 54
	for (cp = optarg; cp != NULL && *cp != '\0'; cp = nextcp) {
E 54
		if ((nextcp = index(cp, ',')) != NULL)
			*nextcp++ = '\0';
		if ((nump = index(cp, '=')) != NULL) {
			*nump++ = '\0';
			num = atoi(nump);
		} else
			num = -1;
		/*
		 * Just test for a string match and do it
		 */
		if (!strcmp(cp, "bg")) {
			*opflagsp |= BGRND;
		} else if (!strcmp(cp, "soft")) {
I 50
D 54
			if (nfsargsp->flags & NFSMNT_SPONGY) {
				fprintf(stderr,
					"Options soft, spongy mutually exclusive\n");
				exit(1);
			}
E 54
I 54
			if (nfsargsp->flags & NFSMNT_SPONGY)
				exclusive("soft, spongy");
E 54
E 50
			nfsargsp->flags |= NFSMNT_SOFT;
I 50
		} else if (!strcmp(cp, "spongy")) {
D 54
			if (nfsargsp->flags & NFSMNT_SOFT) {
				fprintf(stderr,
					"Options soft, spongy mutually exclusive\n");
				exit(1);
			}
E 54
I 54
			if (nfsargsp->flags & NFSMNT_SOFT)
				exclusive("soft, spongy");
E 54
			nfsargsp->flags |= NFSMNT_SPONGY;
I 51
		} else if (!strcmp(cp, "compress")) {
			nfsargsp->flags |= NFSMNT_COMPRESS;
E 51
E 50
		} else if (!strcmp(cp, "intr")) {
			nfsargsp->flags |= NFSMNT_INT;
I 45
		} else if (!strcmp(cp, "tcp")) {
			nfsargsp->sotype = SOCK_STREAM;
		} else if (!strcmp(cp, "noconn")) {
			nfsargsp->flags |= NFSMNT_NOCONN;
E 45
		} else if (!strcmp(cp, "retry") && num > 0) {
			*retrycntp = num;
		} else if (!strcmp(cp, "rsize") && num > 0) {
			nfsargsp->rsize = num;
			nfsargsp->flags |= NFSMNT_RSIZE;
		} else if (!strcmp(cp, "wsize") && num > 0) {
			nfsargsp->wsize = num;
			nfsargsp->flags |= NFSMNT_WSIZE;
		} else if (!strcmp(cp, "timeo") && num > 0) {
			nfsargsp->timeo = num;
			nfsargsp->flags |= NFSMNT_TIMEO;
		} else if (!strcmp(cp, "retrans") && num > 0) {
			nfsargsp->retrans = num;
			nfsargsp->flags |= NFSMNT_RETRANS;
		}
D 54
		cp = nextcp;
E 54
I 50
	}
	if (nfsargsp->sotype == SOCK_DGRAM) {
		if (nfsargsp->rsize > NFS_MAXDGRAMDATA)
			nfsargsp->rsize = NFS_MAXDGRAMDATA;
		if (nfsargsp->wsize > NFS_MAXDGRAMDATA)
			nfsargsp->wsize = NFS_MAXDGRAMDATA;
E 50
	}
}

E 22
I 21
char *
D 45
getnfsargs(spec)
E 45
I 45
getnfsargs(spec, nfsargsp)
E 45
	char *spec;
I 45
	struct nfs_args *nfsargsp;
E 45
{
I 36
D 52
	extern int errno;
E 52
E 36
	register CLIENT *clp;
	struct hostent *hp;
D 32
	struct sockaddr_in saddr;
E 32
I 32
	static struct sockaddr_in saddr;
E 32
	struct timeval pertry, try;
	enum clnt_stat clnt_stat;
	int so = RPC_ANYSOCK;
D 53
	char *hostp, *delimp;
E 53
I 53
	char *fsp, *hostp, *delimp;
E 53
	u_short tport;
D 32
	struct nfhret nfhret;
	char nam[MNAMELEN + 1];
E 32
I 32
	static struct nfhret nfhret;
	static char nam[MNAMELEN + 1];
I 53
	char buf[MAXPATHLEN + 1];
E 53
E 32

I 53
	strncpy(buf, spec, MAXPATHLEN);
	buf[MAXPATHLEN] = '\0';
E 53
	strncpy(nam, spec, MNAMELEN);
	nam[MNAMELEN] = '\0';
D 53
	if ((delimp = index(spec, '@')) != NULL) {
E 53
I 53
	if ((delimp = index(buf, '@')) != NULL) {
E 53
		hostp = delimp + 1;
D 53
	} else if ((delimp = index(spec, ':')) != NULL) {
		hostp = spec;
		spec = delimp + 1;
E 53
I 53
		fsp = buf;
	} else if ((delimp = index(buf, ':')) != NULL) {
		hostp = buf;
		fsp = delimp + 1;
E 53
	} else {
D 54
		fprintf(stderr,
		    "No <host>:<dirpath> or <dirpath>@<host> spec\n");
E 54
I 54
		(void) fprintf(stderr,
		    "mount: No <host>:<dirpath> or <dirpath>@<host> spec\n");
E 54
		return (0);
	}
	*delimp = '\0';
	if ((hp = gethostbyname(hostp)) == NULL) {
D 54
		fprintf(stderr, "Can't get net id for host\n");
E 54
I 54
		(void) fprintf(stderr, "mount: Can't get net id for host\n");
E 54
		return (0);
	}
	bcopy(hp->h_addr, (caddr_t)&saddr.sin_addr, hp->h_length);
D 53
	nfhret.stat = EACCES;	/* Mark not yet successful */
E 53
I 53
	nfhret.stat = ETIMEDOUT;	/* Mark not yet successful */
E 53
	while (retrycnt > 0) {
		saddr.sin_family = AF_INET;
		saddr.sin_port = htons(PMAPPORT);
		if ((tport = pmap_getport(&saddr, RPCPROG_NFS,
		    NFS_VER2, IPPROTO_UDP)) == 0) {
			if ((opflags & ISBGRND) == 0)
				clnt_pcreateerror("NFS Portmap");
		} else {
			saddr.sin_port = 0;
			pertry.tv_sec = 10;
			pertry.tv_usec = 0;
			if ((clp = clntudp_create(&saddr, RPCPROG_MNT,
			    RPCMNT_VER1, pertry, &so)) == NULL) {
				if ((opflags & ISBGRND) == 0)
					clnt_pcreateerror("Cannot MNT PRC");
			} else {
				clp->cl_auth = authunix_create_default();
				try.tv_sec = 10;
				try.tv_usec = 0;
				clnt_stat = clnt_call(clp, RPCMNT_MOUNT,
D 53
				    xdr_dir, spec, xdr_fh, &nfhret, try);
E 53
I 53
				    xdr_dir, fsp, xdr_fh, &nfhret, try);
E 53
				if (clnt_stat != RPC_SUCCESS) {
					if ((opflags & ISBGRND) == 0)
						clnt_perror(clp, "Bad MNT RPC");
				} else {
					auth_destroy(clp->cl_auth);
					clnt_destroy(clp);
					retrycnt = 0;
				}
			}
		}
		if (--retrycnt > 0) {
			if (opflags & BGRND) {
				opflags &= ~BGRND;
				if (fork())
					return (0);
				else
					opflags |= ISBGRND;
			} 
			sleep(10);
		}
	}
	if (nfhret.stat) {
		if (opflags & ISBGRND)
			exit(1);
D 30
		fprintf(stderr, "Can't access %s, errno=%d\n", spec,
		    nfhret.stat);
E 30
I 30
D 53
		fprintf(stderr, "Can't access %s: ", spec);
E 53
I 53
D 54
		fprintf(stderr, "Mount RPC error on %s: ", spec);
E 54
I 54
		(void) fprintf(stderr, "Mount RPC error on %s: ", spec);
E 54
E 53
		errno = nfhret.stat;
D 47
		perror(NULL);
E 47
I 47
		perror((char *)NULL);
E 47
E 30
		return (0);
	}
	saddr.sin_port = htons(tport);
D 45
	nfsargs.addr = &saddr;
	nfsargs.fh = &nfhret.nfh;
	nfsargs.hostname = nam;
	return ((caddr_t)&nfsargs);
E 45
I 45
	nfsargsp->addr = (struct sockaddr *) &saddr;
	nfsargsp->fh = &nfhret.nfh;
	nfsargsp->hostname = nam;
	return ((caddr_t)nfsargsp);
E 45
}

E 21
/*
 * xdr routines for mount rpc's
 */
xdr_dir(xdrsp, dirp)
	XDR *xdrsp;
	char *dirp;
{
	return (xdr_string(xdrsp, &dirp, RPCMNT_PATHLEN));
}

xdr_fh(xdrsp, np)
	XDR *xdrsp;
	struct nfhret *np;
{
	if (!xdr_u_long(xdrsp, &(np->stat)))
		return (0);
	if (np->stat)
		return (1);
	return (xdr_opaque(xdrsp, (caddr_t)&(np->nfh), NFSX_FH));
D 22
}

/*
 * Handle the getoption arg.
 * Essentially update "opflags", "retrycnt" and "nfsargs"
 */
getoptions(optarg, nfsargsp, opflagsp, retrycntp)
	char *optarg;
	struct nfs_args *nfsargsp;
	int *opflagsp;
	int *retrycntp;
{
	register char *cp, *nextcp;
	int num;
	char *nump;

	cp = optarg;
	while (cp != NULL && *cp != '\0') {
		if ((nextcp = index(cp, ',')) != NULL)
			*nextcp++ = '\0';
		if ((nump = index(cp, '=')) != NULL) {
			*nump++ = '\0';
			num = atoi(nump);
		} else
			num = -1;
		/*
		 * Just test for a string match and do it
		 */
		if (!strcmp(cp, "bg")) {
			*opflagsp |= BGRND;
		} else if (!strcmp(cp, "soft")) {
			nfsargsp->flags |= NFSMNT_SOFT;
		} else if (!strcmp(cp, "intr")) {
			nfsargsp->flags |= NFSMNT_INT;
		} else if (!strcmp(cp, "retry") && num > 0) {
			*retrycntp = num;
		} else if (!strcmp(cp, "rsize") && num > 0) {
			nfsargsp->rsize = num;
			nfsargsp->flags |= NFSMNT_RSIZE;
		} else if (!strcmp(cp, "wsize") && num > 0) {
			nfsargsp->wsize = num;
			nfsargsp->flags |= NFSMNT_WSIZE;
		} else if (!strcmp(cp, "timeo") && num > 0) {
			nfsargsp->timeo = num;
			nfsargsp->flags |= NFSMNT_TIMEO;
		} else if (!strcmp(cp, "retrans") && num > 0) {
			nfsargsp->retrans = num;
			nfsargsp->flags |= NFSMNT_RETRANS;
		}
		cp = nextcp;
	}
E 22
}
D 21
#endif
E 21
I 21
#endif /* NFS */
E 58
E 21
E 20
E 1
