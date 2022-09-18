h53016
s 00118/00094/00786
d D 8.8 95/02/14 10:26:41 cgd 99 98
c new argument passing conventions.  minor type size cleanup.
e
s 00009/00017/00871
d D 8.7 94/08/22 10:20:11 mckusick 98 97
c use new queue.h data structures
e
s 00005/00003/00883
d D 8.6 94/04/19 22:15:25 mckusick 97 96
c do not call close operator of the f_ops vector has not yet been set
e
s 00005/00000/00881
d D 8.5 94/01/21 17:17:34 bostic 96 95
c add USL's copyright notice
e
s 00001/00001/00880
d D 8.4 94/01/06 16:24:30 mckusick 95 94
c off by one error (from karels@bsdi.com)
e
s 00000/00001/00881
d D 8.3 94/01/04 18:40:18 bostic 94 93
c lint
e
s 00003/00003/00879
d D 8.2 93/09/23 15:42:11 bostic 93 92
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00880
d D 8.1 93/06/10 21:56:56 bostic 92 91
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00039/00000/00843
d D 7.42 93/05/25 17:16:12 mckusick 91 90
c add fpathconf
e
s 00049/00041/00794
d D 7.41 93/03/23 10:53:30 mckusick 90 89
c limit maximum file descriptors to maxfiles (from torek)
e
s 00002/00001/00833
d D 7.40 93/03/12 18:21:55 mckusick 89 88
c avoid requests for more descriptors than the kernel allows
e
s 00005/00005/00829
d D 7.39 92/12/01 13:35:37 mckusick 88 87
c RLIMIT_OFILE => RLIMIT_NOFILE for compatibility with other UNIX's
e
s 00015/00015/00819
d D 7.38 92/10/11 10:37:59 bostic 87 86
c make kernel includes standard
e
s 00038/00029/00796
d D 7.37 92/07/10 21:36:27 torek 86 84
c ANSIfy syscall args
e
s 00038/00029/00796
d R 7.37 92/07/10 20:48:00 torek 85 84
c ANSIfy syscall args
e
s 00000/00003/00825
d D 7.36 92/07/03 01:40:10 mckusick 84 83
c delete USES
e
s 00003/00003/00825
d D 7.35 92/06/23 20:28:00 mckusick 83 82
c merge in changes for Sparc
e
s 00053/00012/00775
d D 7.34 92/06/03 00:04:43 pendry 82 81
c dupfdopen extended to allow file stealing in addition to dup function.
e
s 00002/00002/00785
d D 7.33 92/05/31 21:24:20 mckusick 81 80
c fstat becomes ofstat; fqstat becomes the real fstat
e
s 00004/00000/00783
d D 7.32 92/05/14 17:31:52 heideman 80 71
c vnode interface conversion
e
s 00004/00000/00783
d R 7.32 92/05/14 15:45:45 heideman 79 71
c vnode interface conversion
e
s 00004/00000/00783
d R 7.32 92/05/14 14:50:57 heideman 78 71
c vnode interface conversion
e
s 00004/00000/00783
d R 7.32 92/05/14 12:55:04 heideman 77 71
c vnode interface conversion
e
s 00004/00000/00783
d R 7.32 92/05/14 11:52:28 heideman 76 71
c vnode interface conversion
e
s 00004/00000/00783
d R 7.32 92/05/14 10:32:39 heideman 75 71
c vnode interface conversion
e
s 00004/00000/00783
d R 7.32 92/05/13 23:11:26 heideman 74 71
c vnode interface conversion
e
s 00004/00000/00783
d R 7.32 92/05/13 18:57:26 heideman 73 71
c vnode interface conversion
e
s 00004/00000/00783
d R 7.32 92/05/13 18:29:31 heideman 72 71
c vnode interface conversion
e
s 00043/00000/00740
d D 7.31 92/05/13 14:48:21 mckusick 71 70
c add fqstat for 64-bit file sizes, 32-bit uid, gid, and dev's
e
s 00003/00002/00737
d D 7.30 92/02/18 15:55:27 mckusick 70 69
c device open routine now gets a proc pointer
e
s 00005/00001/00734
d D 7.29 91/12/19 21:08:15 karels 69 68
c closef must be prepared for a null proc pointer from unp_discard
e
s 00001/00001/00734
d D 7.28 91/06/25 12:14:33 mckusick 68 66
c select list before initializing the ofile entry
e
s 00001/00001/00734
d R 7.27 91/06/21 10:49:56 mckusick 67 66
c new calling convention for fo_close
e
s 00048/00018/00687
d D 7.26 91/06/03 20:36:13 mckusick 66 65
c file structures are now dynamically allocated and linked together on a list 
c call ffree to free file structures
e
s 00012/00002/00693
d D 7.25 91/05/30 16:47:57 mckusick 65 63
c use FHASLOCK and SADVLCK to track processes using locks to save work in close
e
s 00006/00002/00693
d R 7.25 91/05/30 15:32:10 mckusick 64 63
c use FHASLOCK and SADVLCK to track processes using locks to save work in close
e
s 00003/00009/00692
d D 7.24 91/05/30 14:40:35 mckusick 63 62
c dead code elimination
e
s 00052/00078/00649
d D 7.23 91/04/16 00:05:38 mckusick 62 61
c add proc pointers to appropriate VOP and vnode operations;
c inline expand fgetown/fsetown/fioctl and delete discrete routines
e
s 00099/00078/00628
d D 7.22 91/03/25 12:27:28 karels 61 60
c now use single array of descriptors, either within filedesc0 struct
c or external; rm OFILE* macros; use resource limit for open files; various
c cleanups
e
s 00142/00163/00564
d D 7.21 91/03/17 15:41:18 karels 60 59
c more-or-less working with new proc & user structs
e
s 00002/00000/00725
d D 7.20 91/02/28 15:11:11 mckusick 59 58
c have to set offset for SEEK_CUR in F_GETLK too (from scooter@gene.com)
e
s 00003/00003/00722
d D 7.19 91/02/21 16:16:22 karels 58 57
c changes to fflags FCNTLCANT => FCNTLFLAGS, FFLAGS/OFLAGS
e
s 00089/00011/00636
d D 7.18 91/02/01 16:24:50 mckusick 57 56
c add POSIX-style byte-level record locking
e
s 00213/00062/00434
d D 7.17 91/01/10 23:43:37 mckusick 56 55
c add dynamically allocated file descriptors
e
s 00001/00011/00495
d D 7.16 90/06/28 21:18:30 bostic 55 54
c new copyright notice
e
s 00032/00032/00474
d D 7.15 90/06/28 17:10:05 karels 54 53
c RETURN => return, remove syscontext.h
e
s 00002/00004/00504
d D 7.14 90/06/22 17:20:21 mckusick 53 52
c p_devtmp => p_dupfd
e
s 00030/00025/00478
d D 7.13 90/06/21 23:53:45 mckusick 52 51
c communicate through p_devtmp instead r_val1; 
c fdopen returns only error and index, open operates on file table
e
s 00129/00089/00374
d D 7.12 90/06/04 12:43:29 mckusick 51 50
c new system call convention
e
s 00000/00001/00463
d D 7.11 90/05/04 14:08:49 mckusick 50 49
c delete unneeded headers
e
s 00024/00030/00440
d D 7.10 90/04/10 16:55:34 bostic 49 48
c fdopen: eliminate unnecessary tests, only test for sufficient permissions
e
s 00002/00002/00468
d D 7.9 90/04/03 21:26:15 karels 48 47
c Yech! use a "reserved" errno for fdopen
e
s 00003/00003/00467
d D 7.8 89/12/19 11:38:55 mckusick 47 46
c get rid of unnecessary test
e
s 00001/00001/00469
d D 7.7 89/11/12 10:14:51 mckusick 46 45
c have to check mode of descriptor being duped, not the new one
e
s 00007/00011/00463
d D 7.6 89/11/09 19:38:18 mckusick 45 44
c fdopen has to return a special error so that resources get cleaned up
e
s 00016/00013/00458
d D 7.5 89/10/19 23:35:29 mckusick 44 43
c closef now returns errors
e
s 00099/00103/00372
d D 7.4 89/05/09 17:02:07 mckusick 43 42
c merge in vnodes
e
s 00063/00000/00412
d D 7.3 89/05/01 23:02:13 marc 42 41
c /dev/fd driver
e
s 00003/00004/00409
d D 7.2 88/10/18 15:14:37 marc 41 40
c posix style job control - new process groups
e
s 00001/00001/00412
d D 7.1 86/06/05 00:02:01 mckusick 40 39
c 4.3BSD release version
e
s 00001/00001/00412
d D 6.13 86/05/15 09:42:27 karels 39 38
c correct no-such-process error
e
s 00000/00007/00413
d D 6.12 85/12/19 14:42:50 karels 38 37
c move unp_gc call to unp_detach
e
s 00007/00001/00413
d D 6.11 85/06/08 14:35:17 mckusick 37 36
c Add copyright
e
s 00012/00006/00402
d D 6.10 85/05/27 19:53:45 karels 36 35
c implement high-water mark on file descriptors in use
e
s 00000/00001/00408
d D 6.9 85/03/19 20:47:56 mckusick 35 34
c eliminate extraneous include of conf.h
e
s 00004/00001/00405
d D 6.8 85/02/16 15:45:42 karels 34 33
c satisfy ino_lock's assumptions
e
s 00003/00003/00403
d D 6.7 84/11/27 17:06:09 karels 33 32
c no close-on-exec for new fd after dup/dup2/fcntl(DUPFD)
e
s 00004/00003/00402
d D 6.6 84/11/27 16:27:07 karels 32 31
c off-by-one in fcntl-DUPFD; avoid panic on flock(f,0) if holding shared
c lock; don't fail when changing lock types without blocking if we hold the only
c lock
e
s 00014/00014/00391
d D 6.5 84/08/29 20:19:04 bloom 31 30
c Change to includes.  no more ../h
e
s 00006/00018/00399
d D 6.4 84/08/22 16:56:47 mckusick 30 29
c use GETF macro where appropriate
e
s 00002/00002/00415
d D 6.3 83/11/18 10:04:30 karels 29 28
c Zero file f_count exactly once (in closef only);
c catch interrupted device close routines so ino_close always returns
c to closef
e
s 00009/00009/00408
d D 6.2 83/09/25 12:26:54 karels 28 27
c manifest constants '5' and '6' were backwards
e
s 00000/00000/00417
d D 6.1 83/07/29 06:32:36 sam 27 26
c 4.2 distribution
e
s 00014/00061/00403
d D 5.26 83/06/14 01:36:50 sam 26 25
c revamp locking to be done at the file table level
e
s 00108/00006/00356
d D 5.25 83/06/12 14:29:54 sam 25 24
c cleanup locking a bit; fix problem with close not unlocking
e
s 00147/00321/00215
d D 5.24 83/05/27 12:46:13 sam 24 23
c merge of bill's code plus lint (plus, of course, cleanup of bill's bugs)
e
s 00000/00002/00536
d D 5.23 83/01/17 16:16:52 sam 23 22
c sun mods
e
s 00004/00007/00534
d D 5.22 83/01/12 15:38:52 sam 22 21
c race condition: pty input arrives at spl0 and results in 
c ttwakeup call -> selwakeup; if any thing else arrives as input, the 
c call to setrun can be interrupted by another setrun call and setrun will 
c then panic
e
s 00016/00018/00525
d D 5.21 82/12/28 23:45:58 sam 21 20
c copyin & copyout now return EFAULT and all callers uniformly 
c return (or ignore) this value
e
s 00000/00002/00543
d D 5.20 82/12/17 11:43:30 sam 20 19
c sun merge
e
s 00005/00005/00540
d D 5.19 82/12/09 19:01:20 sam 19 18
c u.u_pofile flags are now UF_*
e
s 00007/00007/00538
d D 5.18 82/11/13 22:49:39 sam 18 17
c merge of 4.1b and 4.1c
e
s 00008/00000/00537
d D 5.17 82/10/30 20:48:12 root 17 16
c first version with 68k stuff
e
s 00003/00005/00534
d D 5.16 82/10/23 16:39:10 root 16 15
c bug fixes and more forgiveness in select()
e
s 00008/00011/00531
d D 5.15 82/10/22 00:01:35 root 15 14
c fixes to select
e
s 00001/00002/00541
d D 5.14 82/10/20 01:09:42 root 14 13
c lint
e
s 00003/00003/00540
d D 5.13 82/10/17 21:48:34 root 13 12
c more lint
e
s 00001/00001/00542
d D 5.12 82/10/17 14:04:32 root 12 11
c fix lint
e
s 00000/00001/00543
d D 5.11 82/10/10 15:02:07 root 11 10
c split header files over to vax directories
e
s 00035/00010/00509
d D 5.10 82/09/11 13:12:25 root 10 9
c working select()
e
s 00007/00000/00512
d D 5.9 82/09/08 08:07:26 root 9 8
c opause not here
e
s 00104/00073/00408
d D 5.8 82/09/08 07:58:28 root 8 7
c first attempt at a new select
e
s 00036/00043/00445
d D 5.7 82/09/06 22:38:59 root 7 6
c more work on timer stuff
e
s 00044/00049/00444
d D 5.6 82/09/04 09:07:39 root 6 5
c new clock style; select not tested
e
s 00004/00000/00489
d D 5.5 82/08/22 20:30:37 root 5 4
c lint
e
s 00030/00087/00459
d D 5.4 82/08/10 17:41:14 sam 4 3
c file locking
e
s 00000/00012/00546
d D 5.3 82/08/03 14:03:59 sam 3 2
c purge EFS stuff
e
s 00370/00047/00188
d D 5.2 82/07/24 18:09:01 root 2 1
c merge with calder
e
s 00235/00000/00000
d D 5.1 82/07/15 20:13:31 root 1 0
c date and time created 82/07/15 20:13:31 by root
e
u
U
t
T
I 1
D 37
/*	%M%	%I%	%E%	*/
E 37
I 37
/*
D 40
 * Copyright (c) 1982 Regents of the University of California.
E 40
I 40
D 43
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 40
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 43
I 43
D 61
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
E 61
I 61
D 92
 * Copyright (c) 1982, 1986, 1989, 1991 Regents of the University of California.
E 61
 * All rights reserved.
E 92
I 92
 * Copyright (c) 1982, 1986, 1989, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
I 96
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 96
E 92
E 43
 *
I 43
D 55
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
E 55
I 55
 * %sccs.include.redist.c%
E 55
 *
E 43
 *	%W% (Berkeley) %G%
 */
E 37

D 31
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
I 6
#include "../h/kernel.h"
E 6
D 2
#include "../h/reg.h"
E 2
#include "../h/inode.h"
#include "../h/proc.h"
D 2
#include "../h/clock.h"
#include "../h/mtpr.h"
#include "../h/timeb.h"
#include "../h/times.h"
#include "../h/reboot.h"
#include "../h/fs.h"
E 2
#include "../h/conf.h"
D 2
#include "../h/buf.h"
#include "../h/mount.h"
E 2
#include "../h/file.h"
D 11
#include "../h/inline.h"
E 11
#include "../h/socket.h"
#include "../h/socketvar.h"
I 2
#include "../h/mount.h"
I 25
#include "../h/stat.h"
E 31
I 31
D 87
#include "param.h"
#include "systm.h"
D 43
#include "dir.h"
#include "user.h"
E 43
I 43
D 54
#include "syscontext.h"
E 54
I 54
D 61
#include "user.h"
E 61
I 56
#include "filedesc.h"
E 56
E 54
E 43
#include "kernel.h"
D 43
#include "inode.h"
E 43
I 43
#include "vnode.h"
E 43
#include "proc.h"
D 35
#include "conf.h"
E 35
#include "file.h"
#include "socket.h"
#include "socketvar.h"
D 50
#include "mount.h"
E 50
#include "stat.h"
E 31
E 25
E 2
D 52

E 52
I 2
D 24
#include "../h/descrip.h"
E 24
I 24
D 31
#include "../h/ioctl.h"
E 31
I 31
#include "ioctl.h"
I 57
#include "fcntl.h"
E 57
I 56
#include "malloc.h"
#include "syslog.h"
I 61
#include "resourcevar.h"
E 87
I 87
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/filedesc.h>
#include <sys/kernel.h>
#include <sys/vnode.h>
#include <sys/proc.h>
#include <sys/file.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/fcntl.h>
#include <sys/malloc.h>
#include <sys/syslog.h>
I 91
#include <sys/unistd.h>
E 91
#include <sys/resourcevar.h>
E 87
E 61
E 56
E 31
E 24

I 99
#include <sys/mount.h>
#include <sys/syscallargs.h>

E 99
I 52
D 53
#define	p_devtmp	p_logname[11]

E 53
E 52
E 2
/*
D 2
 * the dup system call.
E 2
I 2
 * Descriptor management.
E 2
 */
I 66
D 98
struct file *filehead;	/* head of list of open files */
int nfiles;		/* actual number of open files */
E 98
I 98
struct filelist filehead;	/* head of list of open files */
int nfiles;			/* actual number of open files */
E 98
E 66
I 56
D 60
int nofile = NOFILE;		/* per-process maximum open files */
E 60
E 56
I 2

/*
D 43
 * TODO:
D 24
 *	getf should be renamed
 *	ufalloc side effects are gross
E 24
I 24
D 36
 *	increase NOFILE
E 36
 *	eliminate u.u_error side effects
E 24
 */

/*
E 43
 * System calls on descriptors.
 */
I 86
D 99
struct getdtablesize_args {
	int	dummy;
};
E 99
E 86
D 6
dstd()
E 6
I 6
D 51
getdtablesize()
E 51
I 51
/* ARGSUSED */
I 99
int
E 99
getdtablesize(p, uap, retval)
	struct proc *p;
D 86
	struct args *uap;
E 86
I 86
D 99
	struct getdtablesize_args *uap;
E 86
	int *retval;
E 99
I 99
	void *uap;
	register_t *retval;
E 99
E 51
E 6
{

D 51
	u.u_r.r_val1 = NOFILE;
E 51
I 51
D 56
	*retval = NOFILE;
E 56
I 56
D 60
	*retval = nofile;
E 60
I 60
D 88
	*retval = p->p_rlimit[RLIMIT_OFILE].rlim_cur;
E 88
I 88
D 90
	*retval = p->p_rlimit[RLIMIT_NOFILE].rlim_cur;
E 90
I 90
	*retval = min((int)p->p_rlimit[RLIMIT_NOFILE].rlim_cur, maxfiles);
E 90
E 88
E 60
E 56
D 54
	RETURN (0);
E 54
I 54
	return (0);
E 54
E 51
}

I 7
D 24
getdprop()
{
	register struct a {
		int	d;
		struct	dtype *dtypeb;
	} *uap = (struct a *)u.u_ap;
	register struct file *fp;
	struct dtype adtype;

	fp = getf(uap->d);
	if (fp == 0)
		return;
	adtype.dt_type = 0;		/* XXX */
	adtype.dt_protocol = 0;		/* XXX */
D 21
	if (copyout((caddr_t)&adtype, (caddr_t)uap->dtypeb,
	    sizeof (struct dtype)) < 0) {
		u.u_error = EFAULT;
E 21
I 21
	u.u_error = copyout((caddr_t)&adtype, (caddr_t)uap->dtypeb,
	    sizeof (struct dtype)); 
	if (u.u_error)
E 21
		return;
D 21
	}
E 21
}

E 24
D 43
getdopt()
{

}

setdopt()
{

}

E 43
E 7
E 2
D 51
dup()
{
I 2
	register struct a {
E 51
I 51
/*
 * Duplicate a file descriptor.
 */
I 86
D 99
struct dup_args {
D 90
	int	i;
E 90
I 90
	u_int	fd;
E 90
};
E 99
E 86
/* ARGSUSED */
I 99
int
E 99
dup(p, uap, retval)
	struct proc *p;
D 86
	struct args {
E 51
		int	i;
D 51
	} *uap = (struct a *) u.u_ap;
E 51
I 51
	} *uap;
E 86
I 86
D 99
	struct dup_args *uap;
E 86
	int *retval;
E 99
I 99
	struct dup_args /* {
		syscallarg(u_int) fd;
	} */ *uap;
	register_t *retval;
E 99
{
I 56
D 90
	register struct filedesc *fdp = p->p_fd;
E 56
E 51
E 2
D 4
	register struct file *fp;
I 2
	register int j;
E 4
I 4
	struct file *fp;
D 51
	int j;
E 51
I 51
	int fd, error;
E 90
I 90
	register struct filedesc *fdp;
	u_int old;
	int new, error;
E 90
E 51
E 4

I 90
D 99
	old = uap->fd;
E 99
I 99
	old = SCARG(uap, fd);
E 99
E 90
D 51
	if (uap->i &~ 077) { uap->i &= 077; dup2(); return; }	/* XXX */
E 51
I 51
	/*
	 * XXX Compatibility
	 */
D 54
	if (uap->i &~ 077) { uap->i &= 077; RETURN (dup2(p, uap, retval)); }
E 54
I 54
D 90
	if (uap->i &~ 077) { uap->i &= 077; return (dup2(p, uap, retval)); }
E 90
I 90
D 99
	if (old &~ 077) { uap->fd &= 077; return (dup2(p, uap, retval)); }
E 99
I 99
	if (old &~ 077) {
		SCARG(uap, fd) &= 077;
		return (dup2(p, uap, retval));
	}
E 99
E 90
E 54
E 51

D 30
	fp = getf(uap->i);
	if (fp == 0)
		return;
E 30
I 30
D 43
	GETF(fp, uap->i);
E 30
D 24
	j = ufalloc();
E 24
I 24
	j = ufalloc(0);
E 24
	if (j < 0)
E 43
I 43
D 56
	if ((unsigned)uap->i >= NOFILE || (fp = u.u_ofile[uap->i]) == NULL)
E 56
I 56
D 60
	if ((unsigned)uap->i >= fdp->fd_maxfiles ||
E 60
I 60
D 90
	if ((unsigned)uap->i >= fdp->fd_nfiles ||
E 60
D 61
	    (fp = OFILE(fdp, uap->i)) == NULL)
E 61
I 61
	    (fp = fdp->fd_ofiles[uap->i]) == NULL)
E 90
I 90
	fdp = p->p_fd;
	if (old >= fdp->fd_nfiles || fdp->fd_ofiles[old] == NULL)
E 90
E 61
E 56
D 54
		RETURN (EBADF);
E 54
I 54
		return (EBADF);
E 54
D 51
	if (u.u_error = ufalloc(0, &j))
E 43
		return;
I 43
	u.u_r.r_val1 = j;
E 43
D 4
	u.u_ofile[j] = fp;
	fp->f_count++;
E 4
I 4
D 18
	dupit(j, fp, u.u_pofile[uap->i] & (RDLOCK|WRLOCK));
E 18
I 18
D 19
	dupit(j, fp, u.u_pofile[uap->i] & (SHLOCK|EXLOCK));
E 19
I 19
D 24
	dupit(j, fp, u.u_pofile[uap->i] & (UF_SHLOCK|UF_EXLOCK));
E 24
I 24
D 33
	dupit(j, fp, u.u_pofile[uap->i]);
E 33
I 33
	dupit(j, fp, u.u_pofile[uap->i] &~ UF_EXCLOSE);
E 51
I 51
D 56
	if (error = ufalloc(0, &fd))
E 56
I 56
D 60
	if (error = ufalloc(fdp, 0, &fd))
E 60
I 60
D 90
	if (error = fdalloc(p, 0, &fd))
E 90
I 90
	if (error = fdalloc(p, 0, &new))
E 90
E 60
E 56
D 54
		RETURN (error);
E 54
I 54
		return (error);
E 54
D 56
	u.u_ofile[fd] = fp;
	u.u_pofile[fd] = u.u_pofile[uap->i] &~ UF_EXCLOSE;
E 56
I 56
D 61
	OFILE(fdp, fd) = fp;
	OFILEFLAGS(fdp, fd) = OFILEFLAGS(fdp, uap->i) &~ UF_EXCLOSE;
E 61
I 61
D 90
	fdp->fd_ofiles[fd] = fp;
	fdp->fd_ofileflags[fd] = fdp->fd_ofileflags[uap->i] &~ UF_EXCLOSE;
E 61
E 56
	fp->f_count++;
D 56
	if (fd > u.u_lastfile)
		u.u_lastfile = fd;
E 56
I 56
	if (fd > fdp->fd_lastfile)
		fdp->fd_lastfile = fd;
E 56
	*retval = fd;
D 54
	RETURN (0);
E 54
I 54
	return (0);
E 90
I 90
	return (finishdup(fdp, (int)old, new, retval));
E 90
E 54
E 51
E 33
E 24
E 19
E 18
E 4
}

D 51
dup2()
E 51
I 51
/*
 * Duplicate a file descriptor to a particular value.
 */
I 86
D 99
struct dup2_args {
	u_int	from;
	u_int	to;
};
E 99
E 86
/* ARGSUSED */
I 99
int
E 99
dup2(p, uap, retval)
	struct proc *p;
D 61
	register struct args {
		int	i;
		int	j;
E 61
I 61
D 86
	struct args {
		u_int	from;
		u_int	to;
E 61
	} *uap;
E 86
I 86
D 99
	struct dup2_args *uap;
E 86
	int *retval;
E 99
I 99
	struct dup2_args /* {
		syscallarg(u_int) from;
		syscallarg(u_int) to;
	} */ *uap;
	register_t *retval;
E 99
E 51
{
I 56
	register struct filedesc *fdp = p->p_fd;
E 56
E 2
D 51
	register struct a {
D 2
		int	fdes;
		int	fdes2;
	} *uap;
	register i, m;
E 2
I 2
		int	i, j;
	} *uap = (struct a *) u.u_ap;
E 51
D 90
	register struct file *fp;
E 90
I 61
D 99
	register u_int old = uap->from, new = uap->to;
E 99
I 99
	register int old = SCARG(uap, from), new = SCARG(uap, to);
E 99
E 61
I 44
D 56
	int error;
E 56
I 56
	int i, error;
E 56
E 44
E 2

D 2
	uap = (struct a *)u.u_ap;
	m = uap->fdes & ~077;
	uap->fdes &= 077;
	fp = getf(uap->fdes);
	if (fp == NULL)
E 2
I 2
D 30
	fp = getf(uap->i);
	if (fp == 0)
E 2
		return;
E 30
I 30
D 43
	GETF(fp, uap->i);
E 43
I 43
D 56
	if ((unsigned)uap->i >= NOFILE || (fp = u.u_ofile[uap->i]) == NULL)
E 56
I 56
D 60
	if ((unsigned)uap->i >= fdp->fd_maxfiles ||
E 60
I 60
D 61
	if ((unsigned)uap->i >= fdp->fd_nfiles ||
E 60
	    (fp = OFILE(fdp, uap->i)) == NULL ||
D 60
	    (unsigned)uap->j >= nofile)
E 60
I 60
	    (unsigned)uap->j >= p->p_rlimit[RLIMIT_OFILE].rlim_cur)
E 61
I 61
	if (old >= fdp->fd_nfiles ||
D 90
	    (fp = fdp->fd_ofiles[old]) == NULL ||
E 90
I 90
	    fdp->fd_ofiles[old] == NULL ||
E 90
D 88
	    new >= p->p_rlimit[RLIMIT_OFILE].rlim_cur)
E 88
I 88
D 89
	    new >= p->p_rlimit[RLIMIT_NOFILE].rlim_cur)
E 89
I 89
	    new >= p->p_rlimit[RLIMIT_NOFILE].rlim_cur ||
D 90
	    new > maxfiles)
E 90
I 90
	    new >= maxfiles)
E 90
E 89
E 88
E 61
E 60
E 56
D 54
		RETURN (EBADF);
E 54
I 54
		return (EBADF);
E 54
E 43
E 30
D 2
	if ((m&0100) == 0) {
		if ((i = ufalloc()) < 0)
			return;
	} else {
		i = uap->fdes2;
		if (i<0 || i>=NOFILE) {
			u.u_error = EBADF;
			return;
		}
		u.u_r.r_val1 = i;
E 2
I 2
D 44
	if (uap->j < 0 || uap->j >= NOFILE) {
		u.u_error = EBADF;
		return;
E 2
	}
E 44
I 44
D 56
	if (uap->j < 0 || uap->j >= NOFILE)
D 54
		RETURN (EBADF);
E 54
I 54
		return (EBADF);
E 56
E 54
E 44
D 2
	if (i != uap->fdes) {
		if (u.u_ofile[i]!=NULL)
			closef(u.u_ofile[i], 0);
E 2
I 2
D 51
	u.u_r.r_val1 = uap->j;
E 51
I 51
D 61
	*retval = uap->j;
E 51
	if (uap->i == uap->j)
E 61
I 61
D 90
	*retval = new;
	if (old == new)
E 90
I 90
	if (old == new) {
		*retval = new;
E 90
E 61
D 44
		return;
E 44
I 44
D 54
		RETURN (0);
E 54
I 54
		return (0);
I 90
	}
E 90
E 54
E 44
D 56
	if (u.u_ofile[uap->j]) {
I 17
D 20
#ifdef SUNMMAP
E 20
		if (u.u_pofile[uap->j] & UF_MAPPED)
			munmapfd(uap->j);
D 20
#endif
E 20
E 17
D 4
		closef(u.u_ofile[uap->j], 0);
E 4
I 4
D 24
		closef(u.u_ofile[uap->j], 0, u.u_pofile[uap->j]);
E 24
I 24
D 26
		closef(u.u_ofile[uap->j], u.u_pofile[uap->j]);
E 26
I 26
D 44
		closef(u.u_ofile[uap->j]);
E 26
E 24
E 4
E 2
		if (u.u_error)
			return;
E 44
I 44
		error = closef(u.u_ofile[uap->j]);
E 56
I 56
D 60
	if ((unsigned)uap->j >= fdp->fd_maxfiles) {
		if (error = ufalloc(fdp, uap->j, &i))
E 60
I 60
D 61
	if ((unsigned)uap->j >= fdp->fd_nfiles) {
		if (error = fdalloc(p, uap->j, &i))
E 61
I 61
	if (new >= fdp->fd_nfiles) {
		if (error = fdalloc(p, new, &i))
E 61
E 60
			return (error);
D 61
		if (uap->j != i)
E 61
I 61
		if (new != i)
E 61
D 60
			panic("dup2: ufalloc");
E 60
I 60
			panic("dup2: fdalloc");
E 60
D 61
	} else if (OFILE(fdp, uap->j)) {
		if (OFILEFLAGS(fdp, uap->j) & UF_MAPPED)
			(void) munmapfd(p, uap->j);
D 60
		error = closef(OFILE(fdp, uap->j));
E 60
I 60
		error = closef(OFILE(fdp, uap->j), p);
E 61
I 61
	} else if (fdp->fd_ofiles[new]) {
		if (fdp->fd_ofileflags[new] & UF_MAPPED)
			(void) munmapfd(p, new);
		/*
		 * dup2() must succeed even if the close has an error.
		 */
		(void) closef(fdp->fd_ofiles[new], p);
E 61
E 60
E 56
E 44
D 2
		u.u_ofile[i] = fp;
		fp->f_count++;
E 2
I 2
D 26
		/* u.u_ofile[uap->j] = 0; */
I 4
		/* u.u_pofile[uap->j] = 0; */
E 26
E 4
E 2
	}
I 2
D 4
	u.u_ofile[uap->j] = fp;
E 4
I 4
D 18
	dupit(uap->j, fp, u.u_pofile[uap->i] & (RDLOCK|WRLOCK));
E 18
I 18
D 19
	dupit(uap->j, fp, u.u_pofile[uap->i] & (SHLOCK|EXLOCK));
E 19
I 19
D 24
	dupit(uap->j, fp, u.u_pofile[uap->i] & (UF_SHLOCK|UF_EXLOCK));
E 24
I 24
D 33
	dupit(uap->j, fp, u.u_pofile[uap->i]);
E 33
I 33
D 51
	dupit(uap->j, fp, u.u_pofile[uap->i] &~ UF_EXCLOSE);
E 51
I 51
D 56
	u.u_ofile[uap->j] = fp;
	u.u_pofile[uap->j] = u.u_pofile[uap->i] &~ UF_EXCLOSE;
E 56
I 56
D 61
	OFILE(fdp, uap->j) = fp;
	OFILEFLAGS(fdp, uap->j) = OFILEFLAGS(fdp, uap->i) &~ UF_EXCLOSE;
E 61
I 61
D 90
	fdp->fd_ofiles[new] = fp;
	fdp->fd_ofileflags[new] = fdp->fd_ofileflags[old] &~ UF_EXCLOSE;
E 61
E 56
	fp->f_count++;
D 56
	if (uap->j > u.u_lastfile)
		u.u_lastfile = uap->j;
E 56
I 56
D 61
	if (uap->j > fdp->fd_lastfile)
		fdp->fd_lastfile = uap->j;
E 56
E 51
I 44
	/*
	 * dup2() must succeed even though the close had an error.
	 */
	error = 0;		/* XXX */
D 54
	RETURN (error);
E 54
I 54
	return (error);
E 61
I 61
	if (new > fdp->fd_lastfile)
		fdp->fd_lastfile = new;
	return (0);
E 90
I 90
	return (finishdup(fdp, (int)old, (int)new, retval));
E 90
E 61
E 54
E 44
E 33
E 24
E 19
E 18
}

D 26
dupit(fd, fp, lockflags)
E 26
I 26
D 51
dupit(fd, fp, flags)
E 26
	int fd;
	register struct file *fp;
D 26
	register int lockflags;
E 26
I 26
	register int flags;
E 26
{

	u.u_ofile[fd] = fp;
D 26
	u.u_pofile[fd] = lockflags;
E 26
I 26
	u.u_pofile[fd] = flags;
E 26
E 4
	fp->f_count++;
I 36
	if (fd > u.u_lastfile)
		u.u_lastfile = fd;
E 36
I 24
D 26
/* THIS DOESN'T BELONG HERE */
E 24
I 4
D 18
	if (lockflags&RDLOCK)
		fp->f_inode->i_rdlockc++;
	if (lockflags&WRLOCK)
		fp->f_inode->i_wrlockc++;
E 18
I 18
D 19
	if (lockflags&SHLOCK)
E 19
I 19
	if (lockflags&UF_SHLOCK)
E 19
D 24
		fp->f_inode->i_shlockc++;
E 24
I 24
		((struct inode *)fp->f_data)->i_shlockc++;
E 24
D 19
	if (lockflags&EXLOCK)
E 19
I 19
	if (lockflags&UF_EXLOCK)
E 19
D 24
		fp->f_inode->i_exlockc++;
E 24
I 24
		((struct inode *)fp->f_data)->i_exlockc++;
/* END DOESN'T BELONG */
E 26
E 24
E 18
E 4
E 2
}

E 51
I 2
D 24
close()
E 24
I 24
/*
 * The file control system call.
 */
I 86
D 99
struct fcntl_args {
	int	fd;
	int	cmd;
	int	arg;
};
E 99
E 86
D 51
fcntl()
E 24
{
D 24
	register struct a {
		int	i;
	} *uap = (struct a *)u.u_ap;
E 24
	register struct file *fp;
D 24

	fp = getf(uap->i);
	if (fp == 0)
		return;
I 17
D 23
#ifdef SUNMMAP
E 23
	if (u.u_pofile[uap->i] & UF_MAPPED)
		munmapfd(uap->i);
D 23
#endif
E 23
E 17
D 4
	u.u_ofile[uap->i] = 0;
	closef(fp, 0);
E 4
I 4
	closef(fp, 0, u.u_pofile[uap->i]);
E 4
	/* WHAT IF u.u_error ? */
I 4
	u.u_ofile[uap->i] = NULL;
	u.u_pofile[uap->i] = 0;
E 4
}

D 6
dtype()
E 6
I 6
D 7
getdprop()
E 6
{
	register struct a {
		int	d;
		struct	dtype *dtypeb;
	} *uap = (struct a *)u.u_ap;
	register struct file *fp;
	struct dtype adtype;

	fp = getf(uap->d);
	if (fp == 0)
		return;
	adtype.dt_type = 0;		/* XXX */
	adtype.dt_protocol = 0;		/* XXX */
	if (copyout((caddr_t)&adtype, (caddr_t)uap->dtypeb,
	    sizeof (struct dtype)) < 0) {
		u.u_error = EFAULT;
		return;
	}
}

E 7
D 6
dwrap()
E 6
I 6
wrap()
E 6
{
E 24
	register struct a {
E 51
I 51
/* ARGSUSED */
I 99
int
E 99
fcntl(p, uap, retval)
	struct proc *p;
D 86
	register struct args {
E 51
D 24
		int	d;
		struct	dtype *dtypeb;
	} *uap = (struct a *)u.u_ap;
	register struct file *fp;
	struct dtype adtype;
E 24
I 24
D 60
		int	fdes;
E 60
I 60
		int	fd;
E 60
		int	cmd;
		int	arg;
D 43
	} *uap;
	register i;
E 43
I 43
D 51
	} *uap = (struct a *)u.u_ap;
E 51
I 51
	} *uap;
E 86
I 86
D 99
	register struct fcntl_args *uap;
E 86
	int *retval;
E 99
I 99
	register struct fcntl_args /* {
		syscallarg(int) fd;
		syscallarg(int) cmd;
		syscallarg(void *) arg;
	} */ *uap;
	register_t *retval;
E 99
{
I 99
	int fd = SCARG(uap, fd);
E 99
I 80
D 84
	USES_VOP_ADVLOCK;
E 84
E 80
I 56
	register struct filedesc *fdp = p->p_fd;
E 56
	register struct file *fp;
E 51
E 43
	register char *pop;
I 43
D 51
	int i;
E 51
I 51
D 57
	int i, error;
E 57
I 57
	struct vnode *vp;
D 62
	int i, error, flags = F_POSIX;
E 62
I 62
	int i, tmp, error, flg = F_POSIX;
E 62
	struct flock fl;
I 90
	u_int newmin;
E 90
E 57
E 51
E 43
E 24

D 24
	fp = getf(uap->d);
	if (fp == 0)
E 24
I 24
D 43
	uap = (struct a *)u.u_ap;
D 30
	fp = getf(uap->fdes);
	if (fp == NULL)
E 24
		return;
E 30
I 30
	GETF(fp, uap->fdes);
E 43
I 43
D 56
	if ((unsigned)uap->fdes >= NOFILE ||
	    (fp = u.u_ofile[uap->fdes]) == NULL)
E 56
I 56
D 60
	if ((unsigned)uap->fdes >= fdp->fd_maxfiles ||
	    (fp = OFILE(fdp, uap->fdes)) == NULL)
E 60
I 60
D 99
	if ((unsigned)uap->fd >= fdp->fd_nfiles ||
D 61
	    (fp = OFILE(fdp, uap->fd)) == NULL)
E 61
I 61
	    (fp = fdp->fd_ofiles[uap->fd]) == NULL)
E 99
I 99
	if ((u_int)fd >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[fd]) == NULL)
E 99
E 61
E 60
E 56
D 54
		RETURN (EBADF);
E 54
I 54
		return (EBADF);
E 54
E 43
E 30
D 21
	if (copyin((caddr_t)uap->dtypeb, (caddr_t)&adtype,
	    sizeof (struct dtype)) < 0) {
		u.u_error = EFAULT;
E 21
I 21
D 24
	u.u_error = copyin((caddr_t)uap->dtypeb, (caddr_t)&adtype,
	    sizeof (struct dtype));
	if (u.u_error)
E 21
		return;
D 21
	}
E 21
	/* DO WRAP */
}
E 24
I 24
D 56
	pop = &u.u_pofile[uap->fdes];
E 56
I 56
D 60
	pop = &OFILEFLAGS(fdp, uap->fdes);
E 60
I 60
D 61
	pop = &OFILEFLAGS(fdp, uap->fd);
E 61
I 61
D 99
	pop = &fdp->fd_ofileflags[uap->fd];
E 61
E 60
E 56
D 90
	switch(uap->cmd) {
E 90
I 90
	switch (uap->cmd) {
E 99
I 99
	pop = &fdp->fd_ofileflags[fd];
	switch (SCARG(uap, cmd)) {
E 99

E 90
D 28
	case 0:
E 28
I 28
	case F_DUPFD:
E 28
D 43
		i = uap->arg;
D 32
		if (i < 0 || i > NOFILE) {
E 32
I 32
		if (i < 0 || i >= NOFILE) {
E 43
I 43
D 51
		if (uap->arg < 0 || uap->arg >= NOFILE) {
E 43
E 32
			u.u_error = EINVAL;
			return;
		}
D 43
		if ((i = ufalloc(i)) < 0)
E 43
I 43
		if (u.u_error = ufalloc(uap->arg, &i))
E 43
			return;
I 43
		u.u_r.r_val1 = i;
E 43
D 33
		dupit(i, fp, *pop);
E 33
I 33
		dupit(i, fp, *pop &~ UF_EXCLOSE);
E 33
		break;
E 51
I 51
D 56
		if (uap->arg < 0 || uap->arg >= NOFILE)
E 56
I 56
D 60
		if ((unsigned)uap->arg >= nofile)
E 60
I 60
D 88
		if ((unsigned)uap->arg >= p->p_rlimit[RLIMIT_OFILE].rlim_cur)
E 88
I 88
D 90
		if ((unsigned)uap->arg >= p->p_rlimit[RLIMIT_NOFILE].rlim_cur)
E 90
I 90
D 99
		newmin = uap->arg;
E 99
I 99
		newmin = (long)SCARG(uap, arg);
E 99
		if (newmin >= p->p_rlimit[RLIMIT_NOFILE].rlim_cur ||
		    newmin >= maxfiles)
E 90
E 88
E 60
E 56
D 54
			RETURN (EINVAL);
E 54
I 54
			return (EINVAL);
E 54
D 56
		if (error = ufalloc(uap->arg, &i))
E 56
I 56
D 60
		if (error = ufalloc(fdp, uap->arg, &i))
E 60
I 60
D 90
		if (error = fdalloc(p, uap->arg, &i))
E 90
I 90
		if (error = fdalloc(p, newmin, &i))
E 90
E 60
E 56
D 54
			RETURN (error);
E 54
I 54
			return (error);
E 54
D 56
		u.u_ofile[i] = fp;
		u.u_pofile[i] = *pop &~ UF_EXCLOSE;
E 56
I 56
D 61
		OFILE(fdp, i) = fp;
		OFILEFLAGS(fdp, i) = *pop &~ UF_EXCLOSE;
E 61
I 61
D 90
		fdp->fd_ofiles[i] = fp;
		fdp->fd_ofileflags[i] = *pop &~ UF_EXCLOSE;
E 61
E 56
		fp->f_count++;
D 56
		if (i > u.u_lastfile)
			u.u_lastfile = i;
E 56
I 56
		if (i > fdp->fd_lastfile)
			fdp->fd_lastfile = i;
E 56
		*retval = i;
D 54
		RETURN (0);
E 54
I 54
		return (0);
E 90
I 90
D 99
		return (finishdup(fdp, uap->fd, i, retval));
E 99
I 99
		return (finishdup(fdp, fd, i, retval));
E 99
E 90
E 54
E 51
E 24

I 8
D 24
int	unselect();
E 8
D 6
dselect()
E 6
I 6
D 7
select()
E 6
{

}

E 7
D 6
dnblock()
{
I 5
#ifdef notdef
E 5
	register struct a {
		int	d;
		int	how;
	} *uap = (struct a *)u.u_ap;

	/* XXX */
I 5
#endif
E 5
}

dsignal()
{
I 5
#ifdef notdef
E 5
	register struct a {
		int	d;
		int	how;
	} *uap = (struct a *)u.u_ap;

	/* XXX */
I 5
#endif
E 5
}

E 6
E 2
int	nselcoll;
/*
 * Select system call.
 */
D 2
select()
E 2
I 2
D 7
oselect()
E 7
I 7
select()
E 7
E 2
{
	register struct uap  {
D 7
		int	nfd;
		fd_set	*rp, *wp;
E 7
I 7
D 8
		fd_set	*rp, *wp, *ep;
E 8
I 8
D 10
		long	*ibits;
		long	*obits;
E 10
I 10
		int	nd;
		long	*in;
		long	*ou;
		long	*ex;
E 10
E 8
E 7
D 6
		int	timo;
	} *ap = (struct uap *)u.u_ap;
E 6
I 6
		struct	timeval *tv;
	} *uap = (struct uap *)u.u_ap;
E 6
D 8
	fd_set rd, wr;
	int nfds = 0, readable = 0, writeable = 0;
D 6
	time_t t = time;
E 6
I 6
	struct timeval atv, origin, now;
E 8
I 8
	int ibits[3], obits[3];
	struct timeval atv;
E 8
E 6
D 12
	int s, tsel, ncoll, rem;
E 12
I 12
	int s, ncoll;
E 12
I 8
	label_t lqsave;
E 24
I 24
D 28
	case 1:
E 28
I 28
	case F_GETFD:
E 28
D 51
		u.u_r.r_val1 = *pop & 1;
		break;
E 51
I 51
		*retval = *pop & 1;
D 54
		RETURN (0);
E 54
I 54
		return (0);
E 54
E 51
E 24
E 8

I 15
D 24
	obits[0] = obits[1] = obits[2] = 0;
E 15
I 10
D 16
	if (uap->nd >= NOFILE) {
		u.u_error = EINVAL;
D 15
		return;
E 15
I 15
		goto done;
E 15
	}
E 16
I 16
	if (uap->nd > NOFILE)
		uap->nd = NOFILE;	/* forgiving, if slightly wrong */
E 24
I 24
D 28
	case 2:
E 28
I 28
	case F_SETFD:
E 28
D 99
		*pop = (*pop &~ 1) | (uap->arg & 1);
E 99
I 99
		*pop = (*pop &~ 1) | ((long)SCARG(uap, arg) & 1);
E 99
D 51
		break;
E 51
I 51
D 54
		RETURN (0);
E 54
I 54
		return (0);
E 54
E 51
E 24
E 16

D 24
#define	getbits(name, x) \
	if (uap->name) { \
D 21
		if (copyin((caddr_t)uap->name, (caddr_t)&ibits[x], \
		    sizeof (ibits[x]))) { \
			u.u_error = EFAULT; \
E 21
I 21
		u.u_error = copyin((caddr_t)uap->name, (caddr_t)&ibits[x], \
		    sizeof (ibits[x])); \
		if (u.u_error) \
E 21
D 15
			return; \
E 15
I 15
			goto done; \
E 15
D 21
		} \
E 21
	} else \
		ibits[x] = 0;
	getbits(in, 0);
	getbits(ou, 1);
	getbits(ex, 2);
#undef	getbits
E 24
I 24
D 28
	case 3:
E 28
I 28
	case F_GETFL:
E 28
D 51
		u.u_r.r_val1 = fp->f_flag+FOPEN;
		break;
E 51
I 51
D 58
		*retval = fp->f_flag + FOPEN;
E 58
I 58
		*retval = OFLAGS(fp->f_flag);
E 58
D 54
		RETURN (0);
E 54
I 54
		return (0);
E 54
E 51
E 24

E 10
D 6
	if (ap->nfd > NOFILE)
		ap->nfd = NOFILE;
	if (ap->nfd < 0) {
E 6
I 6
D 7
	if (uap->nfd > NOFILE)
		uap->nfd = NOFILE;
	if (uap->nfd < 0) {
E 6
		u.u_error = EBADF;
		return;
	}
E 7
D 6
	if (ap->rp && copyin((caddr_t)ap->rp,(caddr_t)&rd,sizeof(fd_set)))
E 6
I 6
D 24
	if (uap->tv) {
D 21
		if (copyin((caddr_t)uap->tv, (caddr_t)&atv, sizeof (atv))) {
			u.u_error = EFAULT;
E 21
I 21
		u.u_error = copyin((caddr_t)uap->tv, (caddr_t)&atv,
			sizeof (atv));
E 24
I 24
D 28
	case 4:
E 28
I 28
	case F_SETFL:
E 28
D 58
		fp->f_flag &= FCNTLCANT;
		fp->f_flag |= (uap->arg-FOPEN) &~ FCNTLCANT;
E 58
I 58
		fp->f_flag &= ~FCNTLFLAGS;
D 99
		fp->f_flag |= FFLAGS(uap->arg) & FCNTLFLAGS;
E 99
I 99
		fp->f_flag |= FFLAGS((long)SCARG(uap, arg)) & FCNTLFLAGS;
E 99
E 58
D 51
		u.u_error = fset(fp, FNDELAY, fp->f_flag & FNDELAY);
E 24
		if (u.u_error)
E 21
D 15
			return;
E 15
I 15
D 24
			goto done;
E 15
D 21
		}
E 21
D 8
	} else
		timerclear(&atv);
	if (uap->rp && copyin((caddr_t)uap->rp,(caddr_t)&rd,sizeof(fd_set)))
E 8
I 8
		if (itimerfix(&atv)) {
			u.u_error = EINVAL;
D 15
			return;
E 15
I 15
			goto done;
E 15
		}
		s = spl7(); timevaladd(&atv, &time); splx(s);
	}
D 10
	if (copyin((caddr_t)uap->ibits, (caddr_t)ibits, sizeof (ibits))) {
		u.u_error = EFAULT;
E 8
E 6
		return;
D 6
	if (ap->wp && copyin((caddr_t)ap->wp,(caddr_t)&wr,sizeof(fd_set)))
E 6
I 6
D 8
	if (uap->wp && copyin((caddr_t)uap->wp,(caddr_t)&wr,sizeof(fd_set)))
E 6
		return;
E 8
I 8
	}
E 10
E 8
retry:
I 6
D 8
	s = spl7(); now = time; splx(s);
E 8
E 6
	ncoll = nselcoll;
	u.u_procp->p_flag |= SSEL;
D 6
	if (ap->rp)
		readable = selscan(ap->nfd, rd, &nfds, FREAD);
	if (ap->wp)
		writeable = selscan(ap->nfd, wr, &nfds, FWRITE);
E 6
I 6
D 8
	if (uap->rp)
D 7
		readable = selscan(uap->nfd, rd, &nfds, FREAD);
E 7
I 7
		readable = selscan(rd, &nfds, FREAD);
E 7
	if (uap->wp)
D 7
		writeable = selscan(uap->nfd, wr, &nfds, FWRITE);
E 7
I 7
		writeable = selscan(wr, &nfds, FWRITE);
E 8
I 8
	u.u_r.r_val1 = selscan(ibits, obits);
E 8
E 7
E 6
D 15
	if (u.u_error)
I 8
		return;
	if (u.u_r.r_val1)
E 15
I 15
	if (u.u_error || u.u_r.r_val1)
E 15
E 8
		goto done;
D 8
	if (readable || writeable)
		goto done;
D 6
	rem = (ap->timo+999)/1000 - (time - t);
	if (ap->timo == 0 || rem <= 0)
E 6
I 6
	if (!timerisset(&atv))
E 6
		goto done;
E 8
	s = spl6();
I 8
D 10
	if (uap->tv && timercmp(&atv, &time, >=)) {
E 10
I 10
	if (uap->tv && timercmp(&time, &atv, >=)) {
E 10
		splx(s);
		goto done;
	}
E 8
	if ((u.u_procp->p_flag & SSEL) == 0 || nselcoll != ncoll) {
		u.u_procp->p_flag &= ~SSEL;
		splx(s);
		goto retry;
	}
	u.u_procp->p_flag &= ~SSEL;
D 6
	tsel = tsleep((caddr_t)&selwait, PZERO+1, rem);
E 6
I 6
D 8
	tsel = tsleep((caddr_t)&selwait, PZERO+1, &atv);
E 8
I 8
	if (uap->tv) {
		lqsave = u.u_qsave;
		if (setjmp(&u.u_qsave)) {
D 13
			untimeout(unselect, u.u_procp);
E 13
I 13
			untimeout(unselect, (caddr_t)u.u_procp);
E 13
			u.u_error = EINTR;
			splx(s);
D 15
			return;
E 15
I 15
			goto done;
E 15
		}
D 13
		timeout(unselect, u.u_procp, hzto(&atv));
E 13
I 13
		timeout(unselect, (caddr_t)u.u_procp, hzto(&atv));
E 13
	}
	sleep((caddr_t)&selwait, PZERO+1);
	if (uap->tv) {
		u.u_qsave = lqsave;
D 13
		untimeout(unselect, u.u_procp);
E 13
I 13
		untimeout(unselect, (caddr_t)u.u_procp);
E 13
	}
E 8
E 6
	splx(s);
D 8
	switch (tsel) {
E 8
I 8
	goto retry;
done:
D 10
	if (copyout((caddr_t)obits, (caddr_t)uap->obits, sizeof (obits))) {
		u.u_error = EFAULT;
		return;
E 10
I 10
#define	putbits(name, x) \
	if (uap->name) { \
D 16
		if (copyout((caddr_t)obits[x], (caddr_t)uap->name, \
E 16
I 16
D 21
		if (copyout((caddr_t)&obits[x], (caddr_t)uap->name, \
E 16
D 15
		    sizeof (obits[x]))) { \
E 15
I 15
		    sizeof (obits[x]))) \
E 15
			u.u_error = EFAULT; \
E 21
I 21
		int error = copyout((caddr_t)&obits[x], (caddr_t)uap->name, \
		    sizeof (obits[x])); \
		if (error) \
			u.u_error = error; \
E 21
D 15
			return; \
		} \
E 15
E 10
	}
I 10
	putbits(in, 0);
	putbits(ou, 1);
	putbits(ex, 2);
#undef putbits
E 10
}
E 24
I 24
			break;
		u.u_error = fset(fp, FASYNC, fp->f_flag & FASYNC);
		if (u.u_error)
E 51
I 51
D 62
		if (error = fset(fp, FNDELAY, fp->f_flag & FNDELAY))
E 62
I 62
D 63
		if (tmp = (fp->f_flag & FNDELAY))
			fp->f_flag |= FNDELAY;
		else
			fp->f_flag &= ~FNDELAY;
E 63
I 63
		tmp = fp->f_flag & FNONBLOCK;
E 63
		error = (*fp->f_ops->fo_ioctl)(fp, FIONBIO, (caddr_t)&tmp, p);
		if (error)
E 62
D 54
			RETURN (error);
E 54
I 54
			return (error);
E 54
D 62
		if (error = fset(fp, FASYNC, fp->f_flag & FASYNC))
E 51
			(void) fset(fp, FNDELAY, 0);
E 62
I 62
D 63
		if (tmp = (fp->f_flag & FASYNC))
			fp->f_flag |= FASYNC;
		else
			fp->f_flag &= ~FASYNC;
E 63
I 63
		tmp = fp->f_flag & FASYNC;
E 63
		error = (*fp->f_ops->fo_ioctl)(fp, FIOASYNC, (caddr_t)&tmp, p);
		if (!error)
			return (0);
D 63
		fp->f_flag &= ~FNDELAY;
E 63
I 63
		fp->f_flag &= ~FNONBLOCK;
E 63
		tmp = 0;
		(void) (*fp->f_ops->fo_ioctl)(fp, FIONBIO, (caddr_t)&tmp, p);
E 62
D 51
		break;
E 51
I 51
D 54
		RETURN (error);
E 54
I 54
		return (error);
E 54
E 51
E 24
E 8

D 8
	case TS_OK:
I 6
		now = time;
		timevalsub(&now, &origin);
		timevalsub(&atv, now);
		if (atv.tv_sec < 0 || atv.tv_usec < 0)
			timerclear(&atv);
E 6
		goto retry;
E 8
I 8
D 24
unselect(p)
	register struct proc *p;
{
	register int s = spl6();
E 8

D 8
	case TS_SIG:
		u.u_error = EINTR;
		return;
E 8
I 8
	switch (p->p_stat) {
E 8

D 8
	case TS_TIME:
E 8
I 8
	case SSLEEP:
		setrun(p);
E 24
I 24
D 28
	case 5:
		u.u_error = fsetown(fp, uap->arg);
E 28
I 28
	case F_GETOWN:
D 51
		u.u_error = fgetown(fp, &u.u_r.r_val1);
E 28
E 24
E 8
		break;
E 51
I 51
D 54
		RETURN (fgetown(fp, retval));
E 54
I 54
D 62
		return (fgetown(fp, retval));
E 62
I 62
		if (fp->f_type == DTYPE_SOCKET) {
			*retval = ((struct socket *)fp->f_data)->so_pgid;
			return (0);
		}
		error = (*fp->f_ops->fo_ioctl)
D 99
			(fp, (int)TIOCGPGRP, (caddr_t)retval, p);
E 99
I 99
			(fp, TIOCGPGRP, (caddr_t)retval, p);
E 99
		*retval = -*retval;
		return (error);
E 62
E 54
E 51
I 8

D 24
	case SSTOP:
		unsleep(p);
E 24
I 24
D 28
	case 6:
		u.u_error = fgetown(fp, &u.u_r.r_val1);
E 28
I 28
	case F_SETOWN:
D 51
		u.u_error = fsetown(fp, uap->arg);
E 28
E 24
		break;
E 51
I 51
D 54
		RETURN (fsetown(fp, uap->arg));
E 54
I 54
D 62
		return (fsetown(fp, uap->arg));
E 62
I 62
		if (fp->f_type == DTYPE_SOCKET) {
D 99
			((struct socket *)fp->f_data)->so_pgid = uap->arg;
E 99
I 99
			((struct socket *)fp->f_data)->so_pgid =
			    (long)SCARG(uap, arg);
E 99
			return (0);
		}
D 99
		if (uap->arg <= 0) {
			uap->arg = -uap->arg;
E 99
I 99
		if ((long)SCARG(uap, arg) <= 0) {
			SCARG(uap, arg) = (void *)(-(long)SCARG(uap, arg));
E 99
		} else {
D 99
			struct proc *p1 = pfind(uap->arg);
E 99
I 99
			struct proc *p1 = pfind((long)SCARG(uap, arg));
E 99
			if (p1 == 0)
				return (ESRCH);
D 99
			uap->arg = p1->p_pgrp->pg_id;
E 99
I 99
			SCARG(uap, arg) = (void *)(long)p1->p_pgrp->pg_id;
E 99
		}
		return ((*fp->f_ops->fo_ioctl)
D 99
			(fp, (int)TIOCSPGRP, (caddr_t)&uap->arg, p));
E 99
I 99
			(fp, TIOCSPGRP, (caddr_t)&SCARG(uap, arg), p));
E 99
E 62
E 54
E 51
I 24

I 57
	case F_SETLKW:
D 62
		flags |= F_WAIT;
E 62
I 62
		flg |= F_WAIT;
E 62
		/* Fall into F_SETLK */

	case F_SETLK:
		if (fp->f_type != DTYPE_VNODE)
			return (EBADF);
		vp = (struct vnode *)fp->f_data;
		/* Copy in the lock structure */
D 99
		error = copyin((caddr_t)uap->arg, (caddr_t)&fl, sizeof (fl));
E 99
I 99
		error = copyin((caddr_t)SCARG(uap, arg), (caddr_t)&fl,
		    sizeof (fl));
E 99
		if (error)
			return (error);
		if (fl.l_whence == SEEK_CUR)
			fl.l_start += fp->f_offset;
		switch (fl.l_type) {

		case F_RDLCK:
			if ((fp->f_flag & FREAD) == 0)
				return (EBADF);
I 65
D 93
			p->p_flag |= SADVLCK;
E 93
I 93
			p->p_flag |= P_ADVLOCK;
E 93
E 65
D 62
			return (VOP_ADVLOCK(vp, p, F_SETLK, &fl, flags));
E 62
I 62
			return (VOP_ADVLOCK(vp, (caddr_t)p, F_SETLK, &fl, flg));
E 62

		case F_WRLCK:
			if ((fp->f_flag & FWRITE) == 0)
				return (EBADF);
I 65
D 93
			p->p_flag |= SADVLCK;
E 93
I 93
			p->p_flag |= P_ADVLOCK;
E 93
E 65
D 62
			return (VOP_ADVLOCK(vp, p, F_SETLK, &fl, flags));
E 62
I 62
			return (VOP_ADVLOCK(vp, (caddr_t)p, F_SETLK, &fl, flg));
E 62

		case F_UNLCK:
D 62
			return (VOP_ADVLOCK(vp, p, F_UNLCK, &fl, F_POSIX));
E 62
I 62
			return (VOP_ADVLOCK(vp, (caddr_t)p, F_UNLCK, &fl,
				F_POSIX));
E 62

		default:
			return (EINVAL);
		}

	case F_GETLK:
		if (fp->f_type != DTYPE_VNODE)
			return (EBADF);
		vp = (struct vnode *)fp->f_data;
		/* Copy in the lock structure */
D 99
		error = copyin((caddr_t)uap->arg, (caddr_t)&fl, sizeof (fl));
E 99
I 99
		error = copyin((caddr_t)SCARG(uap, arg), (caddr_t)&fl,
		    sizeof (fl));
E 99
		if (error)
			return (error);
I 59
		if (fl.l_whence == SEEK_CUR)
			fl.l_start += fp->f_offset;
E 59
D 62
		if (error = VOP_ADVLOCK(vp, p, F_GETLK, &fl, F_POSIX))
E 62
I 62
		if (error = VOP_ADVLOCK(vp, (caddr_t)p, F_GETLK, &fl, F_POSIX))
E 62
			return (error);
D 99
		return (copyout((caddr_t)&fl, (caddr_t)uap->arg, sizeof (fl)));
E 99
I 99
		return (copyout((caddr_t)&fl, (caddr_t)SCARG(uap, arg),
		    sizeof (fl)));
E 99

E 57
	default:
D 51
		u.u_error = EINVAL;
E 51
I 51
D 54
		RETURN (EINVAL);
E 54
I 54
		return (EINVAL);
E 54
E 51
E 24
E 8
	}
I 51
	/* NOTREACHED */
E 51
D 8
done:
	rd.fds_bits[0] = readable;
	wr.fds_bits[0] = writeable;
	s = sizeof (fd_set);
D 6
	if (s * NBBY > ap->nfd)
		s = (ap->nfd + NBBY - 1) / NBBY;
E 6
I 6
D 7
	if (s * NBBY > uap->nfd)
		s = (uap->nfd + NBBY - 1) / NBBY;
E 7
E 6
	u.u_r.r_val1 = nfds;
D 6
	if (ap->rp)
		(void) copyout((caddr_t)&rd, (caddr_t)ap->rp, sizeof(fd_set));
	if (ap->wp)
		(void) copyout((caddr_t)&wr, (caddr_t)ap->wp, sizeof(fd_set));
E 6
I 6
	if (uap->rp)
		(void) copyout((caddr_t)&rd, (caddr_t)uap->rp, sizeof(fd_set));
	if (uap->wp)
		(void) copyout((caddr_t)&wr, (caddr_t)uap->wp, sizeof(fd_set));
E 8
I 8
D 24
	splx(s);
E 24
E 8
E 6
}

D 7
selscan(nfd, fds, nfdp, flag)
	int nfd;
E 7
I 7
D 8
selscan(fds, nfdp, flag)
E 7
	fd_set fds;
	int *nfdp, flag;
E 8
I 8
D 24
selscan(ibits, obits)
	int *ibits, *obits;
E 8
{
I 8
	register int which, bits, i;
	int flag;
E 24
I 24
D 62
fset(fp, bit, value)
E 24
E 8
	struct file *fp;
I 8
D 24
	int able;
E 8
	struct inode *ip;
D 8
	register int bits;
	int i, able, res = 0;
		
	bits = fds.fds_bits[0];
	while (i = ffs(bits)) {
D 7
		if (i > nfd)
			break;
E 7
		bits &= ~(1<<(i-1));
		fp = u.u_ofile[i-1];
		if (fp == NULL) {
			u.u_error = EBADF;
			return (0);
		}
D 2
		if (fp->f_flag & FSOCKET)
E 2
I 2
		if (fp->f_type == DTYPE_SOCKET)
E 2
			able = soselect(fp->f_socket, flag);
		else {
			ip = fp->f_inode;
			switch (ip->i_mode & IFMT) {
E 8
I 8
	int n = 0;
E 24
I 24
	int bit, value;
{
E 24
E 8

D 8
			case IFCHR:
				able =
				    (*cdevsw[major(ip->i_rdev)].d_select)
					(ip->i_rdev, flag);
				break;
E 8
I 8
D 24
	for (which = 0; which < 3; which++) {
		bits = ibits[which];
		obits[which] = 0;
		switch (which) {
E 24
I 24
	if (value)
		fp->f_flag |= bit;
	else
		fp->f_flag &= ~bit;
	return (fioctl(fp, (int)(bit == FNDELAY ? FIONBIO : FIOASYNC),
	    (caddr_t)&value));
}
E 24
E 8

D 8
			case IFBLK:
			case IFREG:
			case IFDIR:
				able = 1;
E 8
I 8
D 24
		case 0:
			flag = FREAD; break;
E 24
I 24
fgetown(fp, valuep)
	struct file *fp;
	int *valuep;
{
	int error;
E 24

D 24
		case 1:
			flag = FWRITE; break;
E 24
I 24
	switch (fp->f_type) {
E 24

D 24
		case 2:
			flag = 0; break;
		}
		while (i = ffs(bits)) {
			bits &= ~(1<<(i-1));
			fp = u.u_ofile[i-1];
			if (fp == NULL) {
				u.u_error = EBADF;
E 8
				break;
			}
I 8
			if (fp->f_type == DTYPE_SOCKET)
				able = soselect(fp->f_socket, flag);
			else {
				ip = fp->f_inode;
				switch (ip->i_mode & IFMT) {
E 24
I 24
	case DTYPE_SOCKET:
D 41
		*valuep = ((struct socket *)fp->f_data)->so_pgrp;
E 41
I 41
		*valuep = ((struct socket *)fp->f_data)->so_pgid;
E 41
		return (0);
E 24
E 8
I 2

I 8
D 24
				case IFCHR:
					able =
					    (*cdevsw[major(ip->i_rdev)].d_select)
						(ip->i_rdev, flag);
					break;

				case IFBLK:
				case IFREG:
				case IFDIR:
					able = 1;
					break;
				}

			}
			if (able) {
				obits[which] |= (1<<(i-1));
				n++;
			}
E 8
E 2
		}
E 24
I 24
	default:
		error = fioctl(fp, (int)TIOCGPGRP, (caddr_t)valuep);
		*valuep = -*valuep;
		return (error);
E 24
D 8
		if (able) {
			res |= (1<<(i-1));
			(*nfdp)++;
		}
E 8
	}
D 8
	return (res);
E 8
I 8
D 24
	return (n);
E 24
E 8
}

D 24
/*ARGSUSED*/
seltrue(dev, flag)
	dev_t dev;
	int flag;
E 24
I 24
fsetown(fp, value)
	struct file *fp;
	int value;
E 24
{
I 43

E 43
D 41

E 41
D 24
	return (1);
E 24
I 24
	if (fp->f_type == DTYPE_SOCKET) {
D 41
		((struct socket *)fp->f_data)->so_pgrp = value;
E 41
I 41
		((struct socket *)fp->f_data)->so_pgid = value;
E 41
		return (0);
	}
	if (value > 0) {
		struct proc *p = pfind(value);
		if (p == 0)
D 39
			return (EINVAL);
E 39
I 39
			return (ESRCH);
E 39
D 41
		value = p->p_pgrp;
E 41
I 41
		value = p->p_pgrp->pg_id;
E 41
	} else
		value = -value;
	return (fioctl(fp, (int)TIOCSPGRP, (caddr_t)&value));
E 24
}

D 24
selwakeup(p, coll)
	register struct proc *p;
	int coll;
E 24
I 24
fioctl(fp, cmd, value)
	struct file *fp;
	int cmd;
	caddr_t value;
E 24
{
D 22
	int s;
E 22

D 24
	if (coll) {
		nselcoll++;
		wakeup((caddr_t)&selwait);
	}
	if (p) {
I 22
		int s = spl6();
E 22
		if (p->p_wchan == (caddr_t)&selwait)
			setrun(p);
D 22
		else {
			s = spl6();
			if (p->p_flag & SSEL)
				p->p_flag &= ~SSEL;
			splx(s);
		}
E 22
I 22
		else if (p->p_flag & SSEL)
			p->p_flag &= ~SSEL;
		splx(s);
E 22
	}
E 24
I 24
	return ((*fp->f_ops->fo_ioctl)(fp, cmd, value));
E 24
I 6
}

E 62
D 24
revoke()
E 24
I 24
D 51
close()
E 24
{
I 24
D 36
	register struct a {
E 36
I 36
	struct a {
E 51
I 51
/*
I 90
 * Common code for dup, dup2, and fcntl(F_DUPFD).
 */
int
finishdup(fdp, old, new, retval)
	register struct filedesc *fdp;
D 99
	register int old, new, *retval;
E 99
I 99
	register int old, new;
	register_t *retval;
E 99
{
	register struct file *fp;

	fp = fdp->fd_ofiles[old];
	fdp->fd_ofiles[new] = fp;
	fdp->fd_ofileflags[new] = fdp->fd_ofileflags[old] &~ UF_EXCLOSE;
	fp->f_count++;
	if (new > fdp->fd_lastfile)
		fdp->fd_lastfile = new;
	*retval = new;
	return (0);
}

/*
E 90
 * Close a file descriptor.
 */
I 86
D 99
struct close_args {
	int	fd;
};
E 99
E 86
/* ARGSUSED */
I 99
int
E 99
close(p, uap, retval)
	struct proc *p;
D 86
	struct args {
E 51
E 36
D 43
		int	i;
E 43
I 43
D 60
		int	fdes;
E 60
I 60
		int	fd;
E 60
E 43
D 51
	} *uap = (struct a *)u.u_ap;
E 51
I 51
	} *uap;
E 86
I 86
D 99
	struct close_args *uap;
E 86
	int *retval;
E 99
I 99
	struct close_args /* {
		syscallarg(int) fd;
	} */ *uap;
	register_t *retval;
E 99
{
I 99
	int fd = SCARG(uap, fd);
E 99
I 56
	register struct filedesc *fdp = p->p_fd;
E 56
E 51
I 36
D 43
	register int i = uap->i;
E 43
E 36
	register struct file *fp;
I 60
D 99
	register int fd = uap->fd;
E 99
E 60
I 25
	register u_char *pf;
E 25
E 24

D 24
	/* XXX */
E 24
I 24
D 30
	fp = getf(uap->i);
	if (fp == 0)
		return;
E 30
I 30
D 36
	GETF(fp, uap->i);
E 30
D 25
	if (u.u_pofile[uap->i] & UF_MAPPED)
E 25
I 25
	pf = (u_char *)&u.u_pofile[uap->i];
E 36
I 36
D 43
	GETF(fp, i);
	pf = (u_char *)&u.u_pofile[i];
E 43
I 43
D 56
	if ((unsigned)uap->fdes >= NOFILE ||
	    (fp = u.u_ofile[uap->fdes]) == NULL)
E 56
I 56
D 60
	if ((unsigned)uap->fdes >= fdp->fd_maxfiles ||
	    (fp = OFILE(fdp, uap->fdes)) == NULL)
E 60
I 60
D 99
	if ((unsigned)fd >= fdp->fd_nfiles ||
E 99
I 99
	if ((u_int)fd >= fdp->fd_nfiles ||
E 99
D 61
	    (fp = OFILE(fdp, fd)) == NULL)
E 61
I 61
	    (fp = fdp->fd_ofiles[fd]) == NULL)
E 61
E 60
E 56
D 54
		RETURN (EBADF);
E 54
I 54
		return (EBADF);
E 54
D 56
	pf = (u_char *)&u.u_pofile[uap->fdes];
E 56
I 56
D 60
	pf = (u_char *)&OFILEFLAGS(fdp, uap->fdes);
E 60
I 60
D 61
	pf = (u_char *)&OFILEFLAGS(fdp, fd);
E 61
I 61
	pf = (u_char *)&fdp->fd_ofileflags[fd];
E 61
E 60
E 56
E 43
E 36
	if (*pf & UF_MAPPED)
E 25
D 36
		munmapfd(uap->i);
D 25
	closef(fp, u.u_pofile[uap->i]);
E 25
I 25
D 26
	if (*pf & (UF_SHLOCK|UF_EXLOCK))
		unlockf(fp, pf);
E 26
D 29
	closef(fp);
E 25
	/* WHAT IF u.u_error ? */
E 29
	u.u_ofile[uap->i] = NULL;
E 36
I 36
D 43
		munmapfd(i);
	u.u_ofile[i] = NULL;
E 43
I 43
D 56
		munmapfd(uap->fdes);
	u.u_ofile[uap->fdes] = NULL;
E 43
	while (u.u_lastfile >= 0 && u.u_ofile[u.u_lastfile] == NULL)
		u.u_lastfile--;
E 56
I 56
D 60
		(void) munmapfd(p, uap->fdes);
	OFILE(fdp, uap->fdes) = NULL;
E 60
I 60
		(void) munmapfd(p, fd);
D 61
	OFILE(fdp, fd) = NULL;
E 60
	while (fdp->fd_lastfile >= 0 && OFILE(fdp, fdp->fd_lastfile) == NULL)
E 61
I 61
	fdp->fd_ofiles[fd] = NULL;
	while (fdp->fd_lastfile > 0 && fdp->fd_ofiles[fdp->fd_lastfile] == NULL)
E 61
		fdp->fd_lastfile--;
I 60
	if (fd < fdp->fd_freefile)
		fdp->fd_freefile = fd;
E 60
E 56
E 36
D 25
	u.u_pofile[uap->i] = 0;
E 25
I 25
	*pf = 0;
I 29
D 44
	closef(fp);
	/* WHAT IF u.u_error ? */
E 44
I 44
D 54
	RETURN (closef(fp));
E 54
I 54
D 60
	return (closef(fp));
E 60
I 60
	return (closef(fp, p));
E 60
E 54
E 44
E 29
E 25
E 24
E 6
}

I 71
D 83
#ifdef COMPAT_43
E 83
I 83
#if defined(COMPAT_43) || defined(COMPAT_SUNOS)
E 83
E 71
I 25
D 51
fstat()
{
	register struct file *fp;
	register struct a {
E 51
I 51
/*
 * Return status information about a file descriptor.
 */
I 86
D 99
struct ofstat_args {
	int	fd;
	struct	ostat *sb;
};
E 99
E 86
/* ARGSUSED */
D 81
fstat(p, uap, retval)
E 81
I 81
D 99
ofstat(p, uap, retval)
E 99
I 99
int
compat_43_fstat(p, uap, retval)
E 99
E 81
I 71
	struct proc *p;
D 86
	register struct args {
		int	fd;
		struct	ostat *sb;
	} *uap;
E 86
I 86
D 99
	register struct ofstat_args *uap;
E 86
	int *retval;
E 99
I 99
	register struct compat_43_fstat_args /* {
		syscallarg(int) fd;
		syscallarg(struct ostat *) sb;
	} */ *uap;
	register_t *retval;
E 99
{
I 99
	int fd = SCARG(uap, fd);
E 99
	register struct filedesc *fdp = p->p_fd;
	register struct file *fp;
	struct stat ub;
	struct ostat oub;
	int error;

D 99
	if ((unsigned)uap->fd >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[uap->fd]) == NULL)
E 99
I 99
	if ((u_int)fd >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[fd]) == NULL)
E 99
		return (EBADF);
	switch (fp->f_type) {

	case DTYPE_VNODE:
		error = vn_stat((struct vnode *)fp->f_data, &ub, p);
		break;

	case DTYPE_SOCKET:
		error = soo_stat((struct socket *)fp->f_data, &ub);
		break;

	default:
D 83
		panic("fstat");
E 83
I 83
		panic("ofstat");
E 83
		/*NOTREACHED*/
	}
	cvtstat(&ub, &oub);
	if (error == 0)
D 99
		error = copyout((caddr_t)&oub, (caddr_t)uap->sb, sizeof (oub));
E 99
I 99
		error = copyout((caddr_t)&oub, (caddr_t)SCARG(uap, sb),
		    sizeof (oub));
E 99
	return (error);
}
D 83
#endif /* COMPAT_43 */
E 83
I 83
#endif /* COMPAT_43 || COMPAT_SUNOS */
E 83

/*
 * Return status information about a file descriptor.
 */
I 86
D 99
struct fstat_args {
	int	fd;
	struct	stat *sb;
};
E 99
E 86
/* ARGSUSED */
I 99
int
E 99
D 81
fqstat(p, uap, retval)
E 81
I 81
fstat(p, uap, retval)
E 81
E 71
	struct proc *p;
D 86
	register struct args {
E 51
D 60
		int	fdes;
E 60
I 60
		int	fd;
E 60
		struct	stat *sb;
D 43
	} *uap;
E 43
I 43
D 51
	} *uap = (struct a *)u.u_ap;
E 51
I 51
	} *uap;
E 86
I 86
D 99
	register struct fstat_args *uap;
E 86
	int *retval;
E 99
I 99
	register struct fstat_args /* {
		syscallarg(int) fd;
		syscallarg(struct stat *) sb;
	} */ *uap;
	register_t *retval;
E 99
{
I 99
	int fd = SCARG(uap, fd);
E 99
I 56
	register struct filedesc *fdp = p->p_fd;
E 56
	register struct file *fp;
E 51
E 43
	struct stat ub;
I 51
	int error;
E 51

D 43
	uap = (struct a *)u.u_ap;
D 30
	fp = getf(uap->fdes);
	if (fp == 0)
		return;
E 30
I 30
	GETF(fp, uap->fdes);
E 43
I 43
D 56
	if ((unsigned)uap->fdes >= NOFILE ||
	    (fp = u.u_ofile[uap->fdes]) == NULL)
E 56
I 56
D 60
	if ((unsigned)uap->fdes >= fdp->fd_maxfiles ||
	    (fp = OFILE(fdp, uap->fdes)) == NULL)
E 60
I 60
D 99
	if ((unsigned)uap->fd >= fdp->fd_nfiles ||
D 61
	    (fp = OFILE(fdp, uap->fd)) == NULL)
E 61
I 61
	    (fp = fdp->fd_ofiles[uap->fd]) == NULL)
E 99
I 99
	if ((u_int)fd >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[fd]) == NULL)
E 99
E 61
E 60
E 56
D 54
		RETURN (EBADF);
E 54
I 54
		return (EBADF);
E 54
E 43
E 30
	switch (fp->f_type) {

D 43
	case DTYPE_INODE:
		u.u_error = ino_stat((struct inode *)fp->f_data, &ub);
E 43
I 43
	case DTYPE_VNODE:
D 51
		u.u_error = vn_stat((struct vnode *)fp->f_data, &ub);
E 51
I 51
D 62
		error = vn_stat((struct vnode *)fp->f_data, &ub);
E 62
I 62
		error = vn_stat((struct vnode *)fp->f_data, &ub, p);
E 62
E 51
E 43
		break;

	case DTYPE_SOCKET:
D 51
		u.u_error = soo_stat((struct socket *)fp->f_data, &ub);
E 51
I 51
		error = soo_stat((struct socket *)fp->f_data, &ub);
E 51
		break;

	default:
		panic("fstat");
		/*NOTREACHED*/
	}
D 51
	if (u.u_error == 0)
D 26
		u.u_error = copyout(&ub, uap->sb, sizeof (ub));
E 26
I 26
		u.u_error = copyout((caddr_t)&ub, (caddr_t)uap->sb,
		    sizeof (ub));
E 51
I 51
	if (error == 0)
D 99
		error = copyout((caddr_t)&ub, (caddr_t)uap->sb, sizeof (ub));
E 99
I 99
		error = copyout((caddr_t)&ub, (caddr_t)SCARG(uap, sb),
		    sizeof (ub));
E 99
D 54
	RETURN (error);
E 54
I 54
	return (error);
I 91
}

/*
 * Return pathconf information about a file descriptor.
 */
D 99
struct fpathconf_args {
	int	fd;
	int	name;
};
E 99
/* ARGSUSED */
I 99
int
E 99
fpathconf(p, uap, retval)
	struct proc *p;
D 99
	register struct fpathconf_args *uap;
	int *retval;
E 99
I 99
	register struct fpathconf_args /* {
		syscallarg(int) fd;
		syscallarg(int) name;
	} */ *uap;
	register_t *retval;
E 99
{
I 99
	int fd = SCARG(uap, fd);
E 99
	struct filedesc *fdp = p->p_fd;
	struct file *fp;
	struct vnode *vp;

D 99
	if ((unsigned)uap->fd >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[uap->fd]) == NULL)
E 99
I 99
	if ((u_int)fd >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[fd]) == NULL)
E 99
		return (EBADF);
	switch (fp->f_type) {

	case DTYPE_SOCKET:
D 99
		if (uap->name != _PC_PIPE_BUF)
E 99
I 99
		if (SCARG(uap, name) != _PC_PIPE_BUF)
E 99
			return (EINVAL);
		*retval = PIPE_BUF;
		return (0);

	case DTYPE_VNODE:
		vp = (struct vnode *)fp->f_data;
D 99
		return (VOP_PATHCONF(vp, uap->name, retval));
E 99
I 99
		return (VOP_PATHCONF(vp, SCARG(uap, name), retval));
E 99

	default:
		panic("fpathconf");
	}
	/*NOTREACHED*/
E 91
E 54
E 51
E 26
}

E 25
I 2
D 4

E 4
E 2
/*
D 2
 * Close system call
E 2
I 2
D 60
 * Allocate a user file descriptor.
E 60
I 60
 * Allocate a file descriptor for the process.
E 60
E 2
 */
D 2
close()
E 2
I 2
D 24
ufalloc()
E 24
I 24
D 43
ufalloc(i)
	register int i;
E 43
I 43
D 56
ufalloc(want, result)
E 56
I 56
D 60
int fdexpand, fdreexpand;
E 60
I 60
int fdexpand;
E 60

I 99
int
E 99
D 60
ufalloc(fdp, want, result)
	register struct filedesc *fdp;
E 56
	register int want;
E 60
I 60
fdalloc(p, want, result)
	struct proc *p;
	int want;
E 60
	int *result;
E 43
E 24
E 2
{
I 56
D 60
	int last, osize, ofiles, nfiles;
E 60
I 60
	register struct filedesc *fdp = p->p_fd;
	register int i;
	int lim, last, nfiles;
E 60
	struct file **newofile;
	char *newofileflags;
E 56
I 2
D 24
	register i;
E 24

I 60
	/*
	 * Search for a free descriptor starting at the higher
	 * of want or fd_freefile.  If that fails, consider
	 * expanding the ofile array.
	 */
D 88
	lim = p->p_rlimit[RLIMIT_OFILE].rlim_cur;
E 88
I 88
D 90
	lim = p->p_rlimit[RLIMIT_NOFILE].rlim_cur;
E 90
I 90
	lim = min((int)p->p_rlimit[RLIMIT_NOFILE].rlim_cur, maxfiles);
E 90
E 88
E 60
D 24
	for (i=0; i<NOFILE; i++)
E 24
I 24
D 43
	for (; i < NOFILE; i++)
E 24
		if (u.u_ofile[i] == NULL) {
			u.u_r.r_val1 = i;
			u.u_pofile[i] = 0;
I 36
			if (i > u.u_lastfile)
				u.u_lastfile = i;
E 36
			return (i);
E 43
I 43
D 47
	for (; want < NOFILE; want++)
E 47
I 47
D 56
	for (; want < NOFILE; want++) {
E 47
		if (u.u_ofile[want] == NULL) {
			u.u_pofile[want] = 0;
			if (want > u.u_lastfile)
				u.u_lastfile = want;
D 47
			if (result)
				*result = want;
E 47
I 47
			*result = want;
E 47
			return (0);
E 56
I 56
	for (;;) {
D 60
		last = (fdp->fd_maxfiles < nofile) ? fdp->fd_maxfiles : nofile;
		for (; want < last; want++) {
			if (OFILE(fdp, want) == NULL) {
				OFILEFLAGS(fdp, want) = 0;
				if (want > fdp->fd_lastfile)
					fdp->fd_lastfile = want;
				*result = want;
E 60
I 60
		last = min(fdp->fd_nfiles, lim);
		if ((i = want) < fdp->fd_freefile)
			i = fdp->fd_freefile;
		for (; i < last; i++) {
D 61
			if (OFILE(fdp, i) == NULL) {
				OFILEFLAGS(fdp, i) = 0;
E 61
I 61
			if (fdp->fd_ofiles[i] == NULL) {
				fdp->fd_ofileflags[i] = 0;
E 61
				if (i > fdp->fd_lastfile)
					fdp->fd_lastfile = i;
D 61
				if (fdp->fd_freefile <= want)
E 61
I 61
				if (want <= fdp->fd_freefile)
E 61
					fdp->fd_freefile = i;
				*result = i;
E 60
				return (0);
			}
E 56
E 43
		}
I 56
D 60
		if (fdp->fd_maxfiles >= nofile)
E 60
I 60

		/*
		 * No space in current array.  Expand?
		 */
		if (fdp->fd_nfiles >= lim)
E 60
			return (EMFILE);
D 60
		if (fdp->fd_maxfiles == NDFILE) {
			fdp->fd_moreofiles = (struct file **)
			    malloc(NDEXTENT * OFILESIZE, M_FILE, M_WAITOK);
			fdp->fd_moreofileflags =
			    (char *)&fdp->fd_moreofiles[NDEXTENT];
			bzero((char *)fdp->fd_moreofiles, NDEXTENT * OFILESIZE);
			fdp->fd_maxfiles = NDFILE + NDEXTENT;
			fdexpand++;
			continue;
		}
		ofiles = fdp->fd_maxfiles - NDFILE;
		osize = ofiles * OFILESIZE;
		nfiles = (2 * osize) / OFILESIZE;
		newofile = (struct file **) malloc(2 * osize, M_FILE, M_WAITOK);
		newofileflags = (char *)&newofile[nfiles];
		bzero((char *)newofile, 2 * osize);
		bcopy((char *)fdp->fd_moreofiles, (char *)newofile,
			sizeof(struct file *) * ofiles);
		bcopy((char *)fdp->fd_moreofileflags, (char *)newofileflags,
			sizeof(char) * ofiles);
		free(fdp->fd_moreofiles, M_FILE);
		fdp->fd_moreofiles = newofile;
		fdp->fd_moreofileflags = newofileflags;
		fdp->fd_maxfiles = NDFILE + nfiles;
		fdreexpand++;
E 60
I 60
D 61
		nfiles = 2 * fdp->fd_nfiles;
E 61
I 61
		if (fdp->fd_nfiles < NDEXTENT)
			nfiles = NDEXTENT;
		else
			nfiles = 2 * fdp->fd_nfiles;
E 61
		MALLOC(newofile, struct file **, nfiles * OFILESIZE,
		    M_FILEDESC, M_WAITOK);
		newofileflags = (char *) &newofile[nfiles];
		/*
		 * Copy the existing ofile and ofileflags arrays
		 * and zero the new portion of each array.
		 */
		bcopy(fdp->fd_ofiles, newofile,
			(i = sizeof(struct file *) * fdp->fd_nfiles));
		bzero((char *)newofile + i, nfiles * sizeof(struct file *) - i);
		bcopy(fdp->fd_ofileflags, newofileflags,
			(i = sizeof(char) * fdp->fd_nfiles));
		bzero(newofileflags + i, nfiles * sizeof(char) - i);
D 61
		FREE(fdp->fd_ofiles, M_FILEDESC);
E 61
I 61
		if (fdp->fd_nfiles > NDFILE)
			FREE(fdp->fd_ofiles, M_FILEDESC);
E 61
		fdp->fd_ofiles = newofile;
		fdp->fd_ofileflags = newofileflags;
		fdp->fd_nfiles = nfiles;
		fdexpand++;
E 60
E 56
I 47
	}
E 47
D 43
	u.u_error = EMFILE;
	return (-1);
E 43
I 43
D 56
	return (EMFILE);
E 56
E 43
}

I 51
/*
D 60
 * Check to see if any user file descriptors are available.
E 60
I 60
D 61
 * Check to see whether n user file descriptors are available.
E 61
I 61
 * Check to see whether n user file descriptors
 * are available to the process p.
E 61
E 60
 */
I 99
int
E 99
E 51
I 24
D 56
ufavail()
E 56
I 56
D 60
ufavail(fdp)
	register struct filedesc *fdp;
E 60
I 60
fdavail(p, n)
	struct proc *p;
	register int n;
E 60
E 56
{
D 56
	register int i, avail = 0;
E 56
I 56
D 60
	register int i, avail;
E 60
I 60
	register struct filedesc *fdp = p->p_fd;
I 61
	register struct file **fpp;
E 61
D 90
	register int i;
E 90
I 90
	register int i, lim;
E 90
E 60
E 56

D 56
	for (i = 0; i < NOFILE; i++)
		if (u.u_ofile[i] == NULL)
E 56
I 56
D 60
	avail = nofile - fdp->fd_maxfiles;
	for (i = 0; i < fdp->fd_maxfiles; i++)
		if (OFILE(fdp, i) == NULL)
E 56
			avail++;
	return (avail);
E 60
I 60
D 88
	if ((i = p->p_rlimit[RLIMIT_OFILE].rlim_cur - fdp->fd_nfiles) > 0 &&
E 88
I 88
D 90
	if ((i = p->p_rlimit[RLIMIT_NOFILE].rlim_cur - fdp->fd_nfiles) > 0 &&
E 88
	    (n -= i) <= 0)
E 90
I 90
	lim = min((int)p->p_rlimit[RLIMIT_NOFILE].rlim_cur, maxfiles);
	if ((i = lim - fdp->fd_nfiles) > 0 && (n -= i) <= 0)
E 90
		return (1);
D 61
	for (i = fdp->fd_freefile; i < fdp->fd_nfiles; i++)
		if (OFILE(fdp, i) == NULL && --n <= 0)
E 61
I 61
	fpp = &fdp->fd_ofiles[fdp->fd_freefile];
	for (i = fdp->fd_nfiles - fdp->fd_freefile; --i >= 0; fpp++)
		if (*fpp == NULL && --n <= 0)
E 61
			return (1);
D 61
	for (i = 0; i < fdp->fd_freefile; i++)
		if (OFILE(fdp, i) == NULL && --n <= 0)
			return (1);
E 61
	return (0);
E 60
}

E 24
D 66
struct	file *lastf;
E 66
/*
D 60
 * Allocate a user file descriptor
 * and a file structure.
 * Initialize the descriptor
 * to point at the file structure.
E 60
I 60
 * Create a new open file structure and allocate
 * a file decriptor for the process that refers to it.
E 60
 */
I 99
int
E 99
D 43
struct file *
falloc()
E 43
I 43
D 56
falloc(resultfp, resultfd)
E 56
I 56
falloc(p, resultfp, resultfd)
	register struct proc *p;
E 56
	struct file **resultfp;
	int *resultfd;
E 43
{
E 2
D 66
	register struct file *fp;
E 66
I 66
D 98
	register struct file *fp, *fq, **fpp;
E 98
I 98
	register struct file *fp, *fq;
E 98
E 66
D 2
	register struct a {
		int	fdes;
	} *uap;
E 2
I 2
D 43
	register i;
E 43
I 43
	int error, i;
E 43
E 2

D 2
	uap = (struct a *)u.u_ap;
	fp = getf(uap->fdes);
E 2
I 2
D 24
	i = ufalloc();
E 24
I 24
D 43
	i = ufalloc(0);
E 24
	if (i < 0)
		return (NULL);
E 43
I 43
D 56
	if (error = ufalloc(0, &i))
E 56
I 56
D 60
	if (error = ufalloc(p->p_fd, 0, &i))
E 60
I 60
	if (error = fdalloc(p, 0, &i))
E 60
E 56
		return (error);
E 43
D 66
	if (lastf == 0)
		lastf = file;
	for (fp = lastf; fp < fileNFILE; fp++)
		if (fp->f_count == 0)
			goto slot;
	for (fp = file; fp < lastf; fp++)
		if (fp->f_count == 0)
			goto slot;
	tablefull("file");
D 43
	u.u_error = ENFILE;
	return (NULL);
E 43
I 43
	return (ENFILE);
E 43
slot:
E 66
I 66
	if (nfiles >= maxfiles) {
		tablefull("file");
		return (ENFILE);
	}
	/*
	 * Allocate a new file descriptor.
	 * If the process has file descriptor zero open, add to the list
	 * of open files at that point, otherwise put it at the front of
	 * the list of open files.
	 */
	nfiles++;
	MALLOC(fp, struct file *, sizeof(struct file), M_FILE, M_WAITOK);
I 97
	bzero(fp, sizeof(struct file));
E 97
E 66
D 56
	u.u_ofile[i] = fp;
E 56
I 56
D 61
	OFILE(p->p_fd, i) = fp;
E 61
I 61
D 68
	p->p_fd->fd_ofiles[i] = fp;
E 68
I 66
D 98
	if (fq = p->p_fd->fd_ofiles[0])
		fpp = &fq->f_filef;
	else
		fpp = &filehead;
E 98
I 98
	if (fq = p->p_fd->fd_ofiles[0]) {
		LIST_INSERT_AFTER(fq, fp, f_list);
	} else {
		LIST_INSERT_HEAD(&filehead, fp, f_list);
	}
E 98
I 68
	p->p_fd->fd_ofiles[i] = fp;
E 68
D 98
	if (fq = *fpp)
		fq->f_fileb = &fp->f_filef;
	fp->f_filef = fq;
	fp->f_fileb = fpp;
	*fpp = fp;
E 98
E 66
E 61
E 56
D 24
	fp->f_count++;
E 24
I 24
	fp->f_count = 1;
D 66
	fp->f_data = 0;
E 66
I 66
D 97
	fp->f_msgcount = 0;
E 66
E 24
	fp->f_offset = 0;
E 97
I 43
D 60
	fp->f_cred = u.u_cred;
E 60
I 60
	fp->f_cred = p->p_ucred;
E 60
	crhold(fp->f_cred);
E 43
D 24
	fp->f_inode = 0;
E 24
D 66
	lastf = fp + 1;
E 66
D 43
	return (fp);
E 43
I 43
	if (resultfp)
		*resultfp = fp;
	if (resultfd)
		*resultfd = i;
	return (0);
E 43
}
I 24

E 24
/*
I 66
 * Free a file descriptor.
 */
I 99
void
E 99
ffree(fp)
	register struct file *fp;
{
	register struct file *fq;

D 98
	if (fq = fp->f_filef)
		fq->f_fileb = fp->f_fileb;
	*fp->f_fileb = fq;
E 98
I 98
	LIST_REMOVE(fp, f_list);
E 98
	crfree(fp->f_cred);
#ifdef DIAGNOSTIC
D 98
	fp->f_filef = NULL;
	fp->f_fileb = NULL;
E 98
	fp->f_count = 0;
#endif
	nfiles--;
	FREE(fp, M_FILE);
}

/*
E 66
I 56
D 60
 * Duplicate a filedesc structure.
E 60
I 60
 * Copy a filedesc structure.
E 60
 */
struct filedesc *
D 60
fddup(fdp, justref)
	register struct filedesc *fdp;
	int justref;
E 60
I 60
fdcopy(p)
	struct proc *p;
E 60
{
I 60
D 61
	register struct filedesc *fdp = p->p_fd;
E 60
	register struct filedesc *newfdp;
	register struct file *fp;
E 61
I 61
	register struct filedesc *newfdp, *fdp = p->p_fd;
	register struct file **fpp;
E 61
	register int i;
D 60
	int j, last;
E 60

D 60
	if (justref) {
		fdp->fd_refcnt++;
		return (fdp);
	}
	MALLOC(newfdp, struct filedesc *, sizeof(*fdp), M_FILE, M_WAITOK);
	bcopy((char *)fdp, (char *)newfdp, sizeof(*fdp));
E 60
I 60
D 61
	MALLOC(newfdp, struct filedesc *, sizeof(*fdp), M_FILEDESC, M_WAITOK);
	bcopy(fdp, newfdp, sizeof(*fdp));
E 61
I 61
	MALLOC(newfdp, struct filedesc *, sizeof(struct filedesc0),
	    M_FILEDESC, M_WAITOK);
	bcopy(fdp, newfdp, sizeof(struct filedesc));
E 61
E 60
	VREF(newfdp->fd_cdir);
	if (newfdp->fd_rdir)
		VREF(newfdp->fd_rdir);
	newfdp->fd_refcnt = 1;
D 60
	newfdp->fd_maxfiles = NDFILE;
	if (fdp->fd_lastfile > NDFILE &&
	    ufalloc(newfdp, fdp->fd_lastfile, &j)) {
		log(LOG_ERR, "fddup: lost file descriptor(s)");
		last = newfdp->fd_maxfiles;
	} else
		last = fdp->fd_lastfile;
	for (i = 0; i <= last; i++) {
		fp = OFILE(fdp, i);
		if (fp == NULL)
			continue;
		fp->f_count++;
		OFILE(newfdp, i) = fp;
		OFILEFLAGS(newfdp, i) = OFILEFLAGS(fdp, i);
	}
E 60
I 60

	/*
D 61
	 * Compute the smallest multiple of NOEXTENT needed
	 * for the file descriptors currently in use,
	 * allowing the table to shrink.
E 61
I 61
	 * If the number of open files fits in the internal arrays
	 * of the open file structure, use them, otherwise allocate
	 * additional memory for the number of descriptors currently
	 * in use.
E 61
	 */
D 61
	i = newfdp->fd_nfiles;
	while (i > NOEXTENT * 2 && i >= (fdp->fd_lastfile + 1) / 2)
		i /= 2;
E 61
I 61
	if (newfdp->fd_lastfile < NDFILE) {
		newfdp->fd_ofiles = ((struct filedesc0 *) newfdp)->fd_dfiles;
		newfdp->fd_ofileflags =
		    ((struct filedesc0 *) newfdp)->fd_dfileflags;
		i = NDFILE;
	} else {
		/*
		 * Compute the smallest multiple of NDEXTENT needed
		 * for the file descriptors currently in use,
		 * allowing the table to shrink.
		 */
		i = newfdp->fd_nfiles;
D 95
		while (i > 2 * NDEXTENT && i >= newfdp->fd_lastfile * 2)
E 95
I 95
		while (i > 2 * NDEXTENT && i > newfdp->fd_lastfile * 2)
E 95
			i /= 2;
		MALLOC(newfdp->fd_ofiles, struct file **, i * OFILESIZE,
		    M_FILEDESC, M_WAITOK);
		newfdp->fd_ofileflags = (char *) &newfdp->fd_ofiles[i];
	}
E 61
	newfdp->fd_nfiles = i;
D 61
	MALLOC(newfdp->fd_ofiles, struct file **, i * OFILESIZE,
	    M_FILEDESC, M_WAITOK);
	newfdp->fd_ofileflags = (char *) &newfdp->fd_ofiles[i];
E 61
	bcopy(fdp->fd_ofiles, newfdp->fd_ofiles, i * sizeof(struct file **));
	bcopy(fdp->fd_ofileflags, newfdp->fd_ofileflags, i * sizeof(char));
D 61
	for (i = 0; i <= newfdp->fd_lastfile; i++)
		if (fp = OFILE(newfdp, i))
			fp->f_count++;
E 61
I 61
	fpp = newfdp->fd_ofiles;
	for (i = newfdp->fd_lastfile; i-- >= 0; fpp++)
		if (*fpp != NULL)
			(*fpp)->f_count++;
E 61
E 60
	return (newfdp);
}

/*
 * Release a filedesc structure.
 */
I 61
void
E 61
D 60
fdrele(fdp)
	register struct filedesc *fdp;
E 60
I 60
fdfree(p)
	struct proc *p;
E 60
{
D 60
	struct file *f;
E 60
I 60
	register struct filedesc *fdp = p->p_fd;
D 61
	struct file *fp;
E 61
I 61
	struct file **fpp;
E 61
E 60
	register int i;

D 60
	if (fdp->fd_refcnt > 1) {
		fdp->fd_refcnt--;
E 60
I 60
	if (--fdp->fd_refcnt > 0)
E 60
		return;
D 60
	}
	for (i = 0; i <= fdp->fd_lastfile; i++) {
		if (f = OFILE(fdp, i)) {
			OFILE(fdp, i) = NULL;
			OFILEFLAGS(fdp, i) = 0;
			(void) closef(f);
		}
	}
	if (fdp->fd_maxfiles > NDFILE)
		FREE(fdp->fd_moreofiles, M_FILE);
E 60
I 60
D 61
	for (i = 0; i <= fdp->fd_lastfile; i++)
		if (fp = OFILE(fdp, i))
			(void) closef(fp, p);
	FREE(fdp->fd_ofiles, M_FILEDESC);
E 61
I 61
	fpp = fdp->fd_ofiles;
	for (i = fdp->fd_lastfile; i-- >= 0; fpp++)
		if (*fpp)
			(void) closef(*fpp, p);
	if (fdp->fd_nfiles > NDFILE)
		FREE(fdp->fd_ofiles, M_FILEDESC);
E 61
E 60
	vrele(fdp->fd_cdir);
	if (fdp->fd_rdir)
		vrele(fdp->fd_rdir);
D 60
	FREE(fdp, M_FILE);
E 60
I 60
	FREE(fdp, M_FILEDESC);
E 60
}

/*
E 56
D 43
 * Convert a user supplied file descriptor into a pointer
 * to a file structure.  Only task is to check range of the descriptor.
D 24
 * Critical paths should use the GETF macro, defined in inline.h.
E 24
I 24
 * Critical paths should use the GETF macro.
E 24
 */
struct file *
getf(f)
	register int f;
{
	register struct file *fp;

	if ((unsigned)f >= NOFILE || (fp = u.u_ofile[f]) == NULL) {
		u.u_error = EBADF;
		return (NULL);
	}
	return (fp);
}

/*
E 43
 * Internal form of close.
D 24
 * Decrement reference count on
 * file structure.
 * Also make sure the pipe protocol
 * does not constipate.
 *
 * Decrement reference count on the inode following
 * removal to the referencing file structure.
 * Call device handler on last close.
 * Nouser indicates that the user isn't available to present
 * errors to.
I 4
 *
 * Handling locking at this level is RIDICULOUS.
E 24
I 24
 * Decrement reference count on file structure.
I 69
 * Note: p may be NULL when closing a file
 * that was being passed in a message.
E 69
D 38
 * If last reference not going away, but no more
 * references except in message queues, run a
 * garbage collect.  This would better be done by
 * forcing a gc() to happen sometime soon, rather
 * than running one each time.
E 38
E 24
E 4
 */
I 99
int
E 99
D 4
closef(fp, nouser)
E 4
I 4
D 24
closef(fp, nouser, flags)
E 24
I 24
D 25
closef(fp, flags)
E 25
I 25
D 60
closef(fp)
E 60
I 60
closef(fp, p)
E 60
E 25
E 24
E 4
	register struct file *fp;
I 60
D 66
	struct proc *p;
E 66
I 66
	register struct proc *p;
E 66
E 60
I 4
D 24
	int nouser, flags;
E 24
I 24
D 25
	int flags;					/* XXX */
E 25
E 24
E 4
{
I 80
D 84
	USES_VOP_ADVLOCK;
E 84
E 80
I 57
D 60
	struct proc *p = u.u_procp;		/* XXX */
E 60
	struct vnode *vp;
	struct flock lf;
E 57
I 44
	int error;
E 44
D 24
	register struct inode *ip;
	register struct mount *mp;
	int flag, mode;
	dev_t dev;
	register int (*cfunc)();
E 24

E 2
	if (fp == NULL)
D 44
		return;
E 44
I 44
		return (0);
I 57
	/*
	 * POSIX record locking dictates that any close releases ALL
	 * locks owned by this process.  This is handled by setting
	 * a flag in the unlock to free ONLY locks obeying POSIX
	 * semantics, and not to free BSD-style file locks.
I 69
	 * If the descriptor was in a message, POSIX-style locks
	 * aren't passed with the descriptor.
E 69
	 */
D 65
	if (fp->f_type == DTYPE_VNODE) {
E 65
I 65
D 69
	if ((p->p_flag & SADVLCK) && fp->f_type == DTYPE_VNODE) {
E 69
I 69
D 93
	if (p && (p->p_flag & SADVLCK) && fp->f_type == DTYPE_VNODE) {
E 93
I 93
	if (p && (p->p_flag & P_ADVLOCK) && fp->f_type == DTYPE_VNODE) {
E 93
E 69
E 65
		lf.l_whence = SEEK_SET;
		lf.l_start = 0;
		lf.l_len = 0;
		lf.l_type = F_UNLCK;
		vp = (struct vnode *)fp->f_data;
D 62
		(void) VOP_ADVLOCK(vp, p, F_UNLCK, &lf, F_POSIX);
E 62
I 62
		(void) VOP_ADVLOCK(vp, (caddr_t)p, F_UNLCK, &lf, F_POSIX);
E 62
	}
E 57
E 44
D 2
	if (u.u_vrpages[uap->fdes]) {
		u.u_error = ETXTBSY;
E 2
I 2
D 60
	if (fp->f_count > 1) {
		fp->f_count--;
E 60
I 60
	if (--fp->f_count > 0)
E 60
I 24
D 38
		if (fp->f_count == fp->f_msgcount)
			unp_gc();
E 38
E 24
E 2
D 44
		return;
E 44
I 44
		return (0);
E 44
D 60
	}
I 43
	if (fp->f_count < 1)
		panic("closef: count < 1");
E 60
I 60
	if (fp->f_count < 0)
		panic("closef: count < 0");
E 60
I 57
D 65
	if (fp->f_type == DTYPE_VNODE)
E 65
I 65
	if ((fp->f_flag & FHASLOCK) && fp->f_type == DTYPE_VNODE) {
		lf.l_whence = SEEK_SET;
		lf.l_start = 0;
		lf.l_len = 0;
		lf.l_type = F_UNLCK;
		vp = (struct vnode *)fp->f_data;
E 65
D 62
		(void) VOP_ADVLOCK(vp, fp, F_UNLCK, &lf, F_FLOCK);
E 57
E 43
D 2
	u.u_ofile[uap->fdes] = NULL;
	closef(fp, 0);
E 2
I 2
D 24
	if (fp->f_type == DTYPE_SOCKET) {
D 14
		u.u_error = 0;			/* XXX */
		soclose(fp->f_socket, nouser);
E 14
I 14
		u.u_error = soclose(fp->f_socket, nouser);
E 14
		if (nouser == 0 && u.u_error)
			return;
		fp->f_socket = 0;
		fp->f_count = 0;
		return;
	}
	flag = fp->f_flag;
	ip = fp->f_inode;
	dev = (dev_t)ip->i_rdev;
	mode = ip->i_mode & IFMT;
I 4
D 18
	flags &= RDLOCK|WRLOCK;			/* conservative */
E 18
I 18
D 19
	flags &= SHLOCK|EXLOCK;			/* conservative */
E 19
I 19
	flags &= UF_SHLOCK|UF_EXLOCK;			/* conservative */
E 19
E 18
	if (flags)
		funlocki(ip, flags);
E 4
	ilock(ip);
	iput(ip);
E 24
I 24
D 25
	(*fp->f_ops->fo_close)(fp, flags);
E 25
I 25
D 44
	(*fp->f_ops->fo_close)(fp);
E 44
I 44
	error = (*fp->f_ops->fo_close)(fp);
E 62
I 62
		(void) VOP_ADVLOCK(vp, (caddr_t)fp, F_UNLCK, &lf, F_FLOCK);
I 65
	}
E 65
D 97
	error = (*fp->f_ops->fo_close)(fp, p);
E 97
I 97
	if (fp->f_ops)
		error = (*fp->f_ops->fo_close)(fp, p);
	else
		error = 0;
E 97
E 62
E 44
I 43
D 66
	crfree(fp->f_cred);
E 43
E 25
E 24
	fp->f_count = 0;
E 66
I 66
	ffree(fp);
E 66
I 44
	return (error);
E 44
I 25
}

/*
 * Apply an advisory lock on a file descriptor.
I 57
 *
 * Just attempt to get a record lock of the requested type on
 * the entire file (l_whence = SEEK_SET, l_start = 0, l_len = 0).
E 57
 */
I 57
D 86

E 86
I 86
D 99
struct flock_args {
	int	fd;
	int	how;
};
E 99
E 86
E 57
D 51
flock()
{
	register struct a {
E 51
I 51
/* ARGSUSED */
I 99
int
E 99
flock(p, uap, retval)
	struct proc *p;
D 86
	register struct args {
E 51
D 43
		int	fd;
E 43
I 43
D 60
		int	fdes;
E 60
I 60
		int	fd;
E 60
E 43
		int	how;
D 51
	} *uap = (struct a *)u.u_ap;
E 51
I 51
	} *uap;
E 86
I 86
D 99
	register struct flock_args *uap;
E 86
	int *retval;
E 99
I 99
	register struct flock_args /* {
		syscallarg(int) fd;
		syscallarg(int) how;
	} */ *uap;
	register_t *retval;
E 99
{
I 99
	int fd = SCARG(uap, fd);
	int how = SCARG(uap, how);
E 99
I 80
D 84
	USES_VOP_ADVLOCK;
E 84
E 80
I 56
	register struct filedesc *fdp = p->p_fd;
E 56
E 51
	register struct file *fp;
I 57
	struct vnode *vp;
	struct flock lf;
D 94
	int error;
E 94
E 57
D 26
	register u_char *pf;
	int cmd;
E 26

D 30
	fp = getf(uap->fd);
	if (fp == NULL)
		return;
E 30
I 30
D 43
	GETF(fp, uap->fd);
E 30
D 26
	cmd = uap->how;
	pf = (u_char *)&u.u_pofile[uap->fd];
	if (cmd & LOCK_UN) {
		unlockf(fp, pf);
E 26
I 26
	if (fp->f_type != DTYPE_INODE) {
E 43
I 43
D 56
	if ((unsigned)uap->fdes >= NOFILE ||
	    (fp = u.u_ofile[uap->fdes]) == NULL)
E 56
I 56
D 60
	if ((unsigned)uap->fdes >= fdp->fd_maxfiles ||
	    (fp = OFILE(fdp, uap->fdes)) == NULL)
E 60
I 60
D 99
	if ((unsigned)uap->fd >= fdp->fd_nfiles ||
D 61
	    (fp = OFILE(fdp, uap->fd)) == NULL)
E 61
I 61
	    (fp = fdp->fd_ofiles[uap->fd]) == NULL)
E 99
I 99
	if ((u_int)fd >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[fd]) == NULL)
E 99
E 61
E 60
E 56
D 54
		RETURN (EBADF);
E 54
I 54
		return (EBADF);
E 54
D 51
	if (fp->f_type != DTYPE_VNODE) {
E 43
		u.u_error = EOPNOTSUPP;
E 26
		return;
	}
E 51
I 51
	if (fp->f_type != DTYPE_VNODE)
D 54
		RETURN (EOPNOTSUPP);
E 54
I 54
		return (EOPNOTSUPP);
I 57
	vp = (struct vnode *)fp->f_data;
	lf.l_whence = SEEK_SET;
	lf.l_start = 0;
	lf.l_len = 0;
E 57
E 54
E 51
D 26
	/*
	 * No reason to write lock a file we've already
	 * write locked, similarly with a read lock.
	 */
	if ((*pf & UF_EXLOCK) && (cmd & LOCK_EX) ||
	    (*pf & UF_SHLOCK) && (cmd & LOCK_SH))
E 26
I 26
D 99
	if (uap->how & LOCK_UN) {
E 99
I 99
	if (how & LOCK_UN) {
E 99
D 43
		ino_unlock(fp, FSHLOCK|FEXLOCK);
E 43
I 43
D 57
		vn_unlock(fp, FSHLOCK|FEXLOCK);
E 43
E 26
D 51
		return;
E 51
I 51
D 54
		RETURN (0);
E 54
I 54
		return (0);
E 57
I 57
		lf.l_type = F_UNLCK;
I 65
		fp->f_flag &= ~FHASLOCK;
E 65
D 62
		return (VOP_ADVLOCK(vp, fp, F_UNLCK, &lf, F_FLOCK));
E 62
I 62
		return (VOP_ADVLOCK(vp, (caddr_t)fp, F_UNLCK, &lf, F_FLOCK));
E 62
E 57
E 54
E 51
D 26
	switch (fp->f_type) {

	case DTYPE_INODE:
		u.u_error = ino_lock((struct inode *)fp->f_data, pf, cmd);
		break;

	case DTYPE_SOCKET:
		u.u_error = soo_lock((struct socket *)fp->f_data, pf, cmd);
		break;

	default:
		panic("lockf");
E 26
	}
I 32
D 57
	if ((uap->how & (LOCK_SH | LOCK_EX)) == 0)
D 51
		return;					/* error? */
E 51
I 51
D 54
		RETURN (0);				/* error? */
E 54
I 54
		return (0);				/* error? */
E 57
E 54
E 51
I 34
D 99
	if (uap->how & LOCK_EX)
E 99
I 99
	if (how & LOCK_EX)
E 99
D 57
		uap->how &= ~LOCK_SH;
E 34
E 32
D 26
}

unlockf(fp, pf)
	register struct file *fp;
	register u_char *pf;
{

	if ((*pf & (UF_SHLOCK|UF_EXLOCK)) == 0)
E 26
I 26
	/* avoid work... */
D 32
	if ((fp->f_flag & FEXLOCK) && (uap->how & LOCK_EX) ||
	    (fp->f_flag & FSHLOCK) && (uap->how & LOCK_SH))
E 32
I 32
D 34
	if ((fp->f_flag & FEXLOCK) && (uap->how & LOCK_EX))
E 34
I 34
	if ((fp->f_flag & FEXLOCK) && (uap->how & LOCK_EX) ||
	    (fp->f_flag & FSHLOCK) && (uap->how & LOCK_SH))
E 34
E 32
E 26
D 51
		return;
D 26
	switch (fp->f_type) {

	case DTYPE_INODE:
		ino_unlock((struct inode *)fp->f_data, *pf);
		break;

	case DTYPE_SOCKET:
		soo_unlock((struct socket *)fp->f_data, *pf);
		break;

	default:
		panic("unlockf");
	}
	*pf &= ~(UF_SHLOCK|UF_EXLOCK);
E 26
I 26
D 43
	u.u_error = ino_lock(fp, uap->how);
E 43
I 43
	u.u_error = vn_lock(fp, uap->how);
E 51
I 51
D 54
		RETURN (0);
	RETURN (vn_lock(fp, uap->how));
E 54
I 54
		return (0);
	return (vn_lock(fp, uap->how));
E 57
I 57
		lf.l_type = F_WRLCK;
D 99
	else if (uap->how & LOCK_SH)
E 99
I 99
	else if (how & LOCK_SH)
E 99
		lf.l_type = F_RDLCK;
	else
		return (EBADF);
I 65
	fp->f_flag |= FHASLOCK;
E 65
D 99
	if (uap->how & LOCK_NB)
E 99
I 99
	if (how & LOCK_NB)
E 99
D 62
		return (VOP_ADVLOCK(vp, fp, F_SETLK, &lf, F_FLOCK));
	return (VOP_ADVLOCK(vp, fp, F_SETLK, &lf, F_FLOCK|F_WAIT));
E 62
I 62
		return (VOP_ADVLOCK(vp, (caddr_t)fp, F_SETLK, &lf, F_FLOCK));
	return (VOP_ADVLOCK(vp, (caddr_t)fp, F_SETLK, &lf, F_FLOCK|F_WAIT));
E 62
E 57
E 54
E 51
E 43
E 26
E 25
D 24

	switch (mode) {

	case IFCHR:
		cfunc = cdevsw[major(dev)].d_close;
D 3
#ifdef EFS
		/*
		 * Every close() must call the driver if the
		 * extended file system is being used -- not
		 * just the last close.  Pass along the file
		 * pointer for reference later.
		 */
		if (major(dev) == efs_major) {
			(*cfunc)(dev, flag, fp, nouser);
			return;
		}
#endif
E 3
		break;

	case IFBLK:
		/*
		 * We don't want to really close the device if it is mounted
		 */
		for (mp = mount; mp < &mount[NMOUNT]; mp++)
			if (mp->m_bufp != NULL && mp->m_dev == dev)
				return;
		cfunc = bdevsw[major(dev)].d_close;
		break;

	default:
		return;
	}
	for (fp = file; fp < fileNFILE; fp++) {
		if (fp->f_type == DTYPE_SOCKET)		/* XXX */
			continue;
		if (fp->f_count && (ip = fp->f_inode) &&
		    ip->i_rdev == dev && (ip->i_mode&IFMT) == mode)
			return;
	}
	if (mode == IFBLK) {
		/*
		 * On last close of a block device (that isn't mounted)
		 * we must invalidate any in core blocks
		 */
		bflush(dev);
		binval(dev);
	}
	(*cfunc)(dev, flag, fp);
E 2
}
I 9

opause()
{

	for (;;)
		sleep((caddr_t)&u, PSLEP);
E 24
}
I 42

/*
 * File Descriptor pseudo-device driver (/dev/fd/).
 *
D 52
 * Fred Blonder - U of Maryland	11-Sep-1984
 *
E 52
 * Opening minor device N dup()s the file (if any) connected to file
 * descriptor N belonging to the calling process.  Note that this driver
 * consists of only the ``open()'' routine, because all subsequent
 * references to this file will be direct to the other driver.
 */
D 43
fdopen(dev, mode)
E 43
I 43
/* ARGSUSED */
I 99
int
E 99
D 70
fdopen(dev, mode, type)
E 70
I 70
fdopen(dev, mode, type, p)
E 70
E 43
	dev_t dev;
D 43
	int mode;
E 43
I 43
	int mode, type;
I 70
	struct proc *p;
E 70
E 43
{
I 80
D 82
	USES_VOP_OPEN;
E 82
E 80
D 52
	struct file *fp, *wfp;
D 43
	struct inode *ip, *wip;
	int rwmode;
E 43
I 43
D 49
	int indx, dfd, rwmode;
E 49
I 49
	int indx, dfd;
E 52
I 52
D 60
	struct proc *p = u.u_procp;		/* XXX */
E 60
E 52
E 49
E 43

	/*
D 49
	 * Note the horrid kludge here: u.u_r.r_val1 contains the value
D 43
	 * of the new file descriptor, which has not been disturbed since
	 * it was allocated.
E 43
I 43
	 * of the new file descriptor, which was set before the call to
	 * vn_open() by copen() in vfs_syscalls.c
E 49
I 49
D 52
	 * XXX
	 * Horrid kludge: u.u_r.r_val1 contains the value of the new file
	 * descriptor, which was set before the call to vn_open() by copen()
	 * in vfs_syscalls.c.
E 52
I 52
D 53
	 * XXX Kludge: set p->p_devtmp to contain the value of the
E 53
I 53
D 60
	 * XXX Kludge: set p->p_dupfd to contain the value of the
E 60
I 60
	 * XXX Kludge: set curproc->p_dupfd to contain the value of the
E 60
E 53
	 * the file descriptor being sought for duplication. The error 
	 * return ensures that the vnode for this device will be released
	 * by vn_open. Open will detect this special error and take the
	 * actions in dupfdopen below. Other callers of vn_open or VOP_OPEN
	 * will simply report the error.
E 52
E 49
E 43
	 */
D 43
	if ((fp = getf(u.u_r.r_val1)) == NULL)
		return (u.u_error);
	if ((wfp = getf(minor(dev))) == NULL)
		return (u.u_error);
E 43
I 43
D 45
	indx = u.u_r.r_val1;		/* XXX */
E 45
I 45
D 49
	indx = u.u_r.r_val1;		/* XXX from copen */
E 45
	if ((unsigned)indx >= NOFILE || (fp = u.u_ofile[indx]) == NULL)
		return (EBADF);
	dfd = minor(dev);
	if ((unsigned)dfd >= NOFILE || (wfp = u.u_ofile[dfd]) == NULL)
		return (EBADF);
E 49
I 49
D 52
	indx = u.u_r.r_val1;
	fp = u.u_ofile[indx];
E 52
I 52
D 53
	p->p_devtmp = minor(dev);
E 53
I 53
D 60
	p->p_dupfd = minor(dev);
E 60
I 60
D 70
	curproc->p_dupfd = minor(dev);		/* XXX */
E 70
I 70
	p->p_dupfd = minor(dev);
E 70
E 60
E 53
	return (ENODEV);
}
E 52

I 52
/*
 * Duplicate the specified descriptor to a free descriptor.
 */
I 99
int
E 99
D 56
dupfdopen(indx, dfd, mode)
E 56
I 56
D 82
dupfdopen(fdp, indx, dfd, mode)
E 82
I 82
dupfdopen(fdp, indx, dfd, mode, error)
E 82
	register struct filedesc *fdp;
E 56
	register int indx, dfd;
	int mode;
I 82
	int error;
E 82
{
	register struct file *wfp;
	struct file *fp;
D 99
	
E 99
I 99

E 99
E 52
E 49
E 43
	/*
D 49
	 * We must explicitly test for this case because ufalloc() may
	 * have allocated us the same file desriptor we are referring
	 * to, if the proccess referred to an invalid (closed) descriptor.
D 43
	 * Ordinarily this would be caught by getf(), but by the time we
	 * reach this routine u_pofile[minor(dev)] could already be set
	 * to point to our file struct.
E 43
I 43
	 * Ordinarily this would be caught by the check for NULL above,
	 * but by the time we reach this routine u_pofile[minor(dev)]
	 * could already be set to point to our file struct.
E 49
I 49
D 52
	 * File system device minor number is the to-be-dup'd fd number.
	 * If it is greater than the allowed number of file descriptors,
	 * or the fd to be dup'd has already been closed, reject.  Note,
 	 * check for new == old is necessary as u_falloc could allocate
	 * an already closed to-be-dup'd descriptor as the new descriptor.
E 52
I 52
	 * If the to-be-dup'd fd number is greater than the allowed number
	 * of file descriptors, or the fd to be dup'd has already been
	 * closed, reject.  Note, check for new == old is necessary as
	 * falloc could allocate an already closed to-be-dup'd descriptor
	 * as the new descriptor.
E 52
E 49
E 43
	 */
D 49
	if (fp == wfp)
E 49
I 49
D 52
	dfd = minor(dev);
E 52
I 52
D 56
	fp = u.u_ofile[indx];
E 52
	if ((u_int)dfd >= NOFILE || (wfp = u.u_ofile[dfd]) == NULL ||
E 56
I 56
D 61
	fp = OFILE(fdp, indx);
D 60
	if ((u_int)dfd >= fdp->fd_maxfiles || (wfp = OFILE(fdp, dfd)) == NULL ||
E 60
I 60
	if ((u_int)dfd >= fdp->fd_nfiles || (wfp = OFILE(fdp, dfd)) == NULL ||
E 60
E 56
	    fp == wfp)
E 61
I 61
	fp = fdp->fd_ofiles[indx];
	if ((u_int)dfd >= fdp->fd_nfiles ||
	    (wfp = fdp->fd_ofiles[dfd]) == NULL || fp == wfp)
E 61
E 49
		return (EBADF);
I 49

E 49
	/*
D 49
	 * Fake a ``dup()'' sys call.
	 * Check that the mode the file is being opened
	 * for is consistent with the mode of the existing
	 * descriptor. This isn't as clean as it should be,
	 * but this entire driver is a real kludge anyway.
E 49
I 49
D 82
	 * Check that the mode the file is being opened for is a subset 
	 * of the mode of the existing descriptor.
E 82
I 82
	 * There are two cases of interest here.
	 *
	 * For ENODEV simply dup (dfd) to file descriptor
	 * (indx) and return.
	 *
	 * For ENXIO steal away the file structure from (dfd) and
	 * store it in (indx).  (dfd) is effectively closed by
	 * this operation.
	 *
	 * Any other error code is just returned.
E 82
E 49
	 */
D 49
	rwmode = mode & (FREAD|FWRITE);
D 46
	if ((fp->f_flag & rwmode) != rwmode)
E 46
I 46
	if ((wfp->f_flag & rwmode) != rwmode)
E 49
I 49
D 52
	if ((mode & (FREAD|FWRITE) | wfp->f_flag) != wfp->f_flag)
E 52
I 52
D 82
	if (((mode & (FREAD|FWRITE)) | wfp->f_flag) != wfp->f_flag)
E 52
E 49
E 46
		return (EACCES);
D 45
	/*
	 * Delete references to this pseudo-device.
	 * Note that fp->f_count is guaranteed == 1, and
D 43
	 * that fp references the inode for this driver.
E 43
I 43
	 * that fp references the vnode for this driver.
E 43
	 */
D 43
	if (fp->f_count != 1 || fp->f_type != DTYPE_INODE) 
E 43
I 43
	if (fp->f_count != 1 || fp->f_type != DTYPE_VNODE) 
E 43
		panic("fdopen");
D 43
	irele((struct inode *)fp->f_data);
E 43
I 43
	vrele((struct vnode *)fp->f_data);
E 43
	fp->f_count = 0;
E 45
D 49
	/* 
	 * Dup the file descriptor. 
	 */
E 49
D 43
	dupit(u.u_r.r_val1, wfp, u.u_pofile[minor(dev)]);
E 43
I 43
D 51
	dupit(indx, wfp, u.u_pofile[dfd]);
E 51
I 51
D 56
	u.u_ofile[indx] = wfp;
	u.u_pofile[indx] = u.u_pofile[dfd];
E 56
I 56
D 61
	OFILE(fdp, indx) = wfp;
	OFILEFLAGS(fdp, indx) = OFILEFLAGS(fdp, dfd);
E 61
I 61
	fdp->fd_ofiles[indx] = wfp;
	fdp->fd_ofileflags[indx] = fdp->fd_ofileflags[dfd];
E 61
E 56
	wfp->f_count++;
D 56
	if (indx > u.u_lastfile)
		u.u_lastfile = indx;
E 56
I 56
	if (indx > fdp->fd_lastfile)
		fdp->fd_lastfile = indx;
E 56
E 51
I 49
D 52

E 49
E 43
D 45
	return (0);
E 45
I 45
	/*
D 49
	 * Delete references to this pseudo-device by returning
D 48
	 * a special error (-1) that will cause all resources to
E 48
I 48
	 * a special error (EJUSTRETURN) that will cause all resources to
E 48
	 * be freed, then detected and cleared by copen.
E 49
I 49
	 * Delete references to this pseudo-device by returning a special
	 * error (EJUSTRETURN) that will cause all resources to be freed,
	 * then detected and cleared by copen().
E 49
	 */
D 48
	return (-1);
E 48
I 48
	return (EJUSTRETURN);			/* XXX */
E 52
I 52
	return (0);
E 82
I 82
	switch (error) {
	case ENODEV:
		/*
		 * Check that the mode the file is being opened for is a
		 * subset of the mode of the existing descriptor.
		 */
		if (((mode & (FREAD|FWRITE)) | wfp->f_flag) != wfp->f_flag)
			return (EACCES);
		fdp->fd_ofiles[indx] = wfp;
		fdp->fd_ofileflags[indx] = fdp->fd_ofileflags[dfd];
		wfp->f_count++;
		if (indx > fdp->fd_lastfile)
			fdp->fd_lastfile = indx;
		return (0);

	case ENXIO:
		/*
		 * Steal away the file pointer from dfd, and stuff it into indx.
		 */
		fdp->fd_ofiles[indx] = fdp->fd_ofiles[dfd];
		fdp->fd_ofiles[dfd] = NULL;
		fdp->fd_ofileflags[indx] = fdp->fd_ofileflags[dfd];
		fdp->fd_ofileflags[dfd] = 0;
		/*
		 * Complete the clean up of the filedesc structure by
		 * recomputing the various hints.
		 */
		if (indx > fdp->fd_lastfile)
			fdp->fd_lastfile = indx;
		else
			while (fdp->fd_lastfile > 0 &&
			       fdp->fd_ofiles[fdp->fd_lastfile] == NULL)
				fdp->fd_lastfile--;
			if (dfd < fdp->fd_freefile)
				fdp->fd_freefile = dfd;
		return (0);

	default:
		return (error);
	}
	/* NOTREACHED */
E 82
E 52
E 48
E 45
}
I 56
D 60

#if defined(vax) || defined(tahoe)
/*
 * Brain dead routines to compensate for limitations in PCC
 */
struct file **
ofilefunc(fdp, indx)
	struct filedesc *fdp;
	int indx;
{

	if (indx < NDFILE)
		return (&fdp->fd_ofile[indx]);
	return (&fdp->fd_moreofiles[indx - NDFILE]);
}

char *
ofileflagsfunc(fdp, indx)
	struct filedesc *fdp;
	int indx;
{

	if (indx < NDFILE)
		return (&fdp->fd_ofileflags[indx]);
	return (&fdp->fd_moreofileflags[indx - NDFILE]);
}
#endif
E 60
E 56
E 42
E 9
I 2
D 4

#ifdef CAD
/*
 * chfile -- change all references to the inode named by
 *	     device/inum to the file referred to by fd.
 * Used by init to remove all references to the device.
 */
chfile()
{
	register struct file *fp;
	register struct inode *from;
	register struct inode *to;
	off_t offset;
	dev_t dev;
	int rw;
	struct a {
		int	device;		/* actually dev_t */
		int	inum;		/* actually ino_t */
		int	fd;
	} *uap;

	if (!suser()) {
		u.u_error = EPERM;
		return;
	}
	uap = (struct a *) u.u_ap;
	fp = getf(uap->fd);
	if (fp == NULL) {
		u.u_error = EBADF;
		return;
	}
	if (fp->f_type == DTYPE_SOCKET) {
		u.u_error = EINVAL;
		return;
	}
	for (from = &inode[0]; from < &inode[ninode]; from++)
		if (from->i_number == (ino_t)uap->inum
		   && from->i_dev == (dev_t)uap->device)
			break;
	if (from >= &inode[ninode]) {
		u.u_error = ENXIO;
		return;
	}
	offset = fp->f_offset;
	to = fp->f_inode;
	from->i_count++;
	for (fp = &file[0]; fp < &file[nfile]; fp++) {
		if (fp->f_count > 0 && fp->f_inode == from) {
			fp->f_inode = to;
			to->i_count++;
			fp->f_offset = offset;
			rw |= fp->f_flag & FWRITE;
			iput(from);
		}
	}
	/*
	 * This inode is no longer referenced.
	 * Switch out to the appropriate close
	 * routine, if required
	 */
	dev = (dev_t)from->i_un.i_rdev;
	switch(from->i_mode & IFMT) {

	case IFCHR:
		(*cdevsw[major(dev)].d_close)(dev, rw);
		break;
	
	case IFBLK:
		(*bdevsw[major(dev)].d_close)(dev, rw);
		break;

	default:
		break;
	}
	iput(from);
}
#endif
E 4
E 2
E 1
