h54750
s 00111/00100/00553
d D 8.9 95/02/14 10:40:49 cgd 109 108
c new argument passing conventions.  minor type size cleanup.
e
s 00010/00013/00643
d D 8.8 94/08/11 12:35:56 mckusick 108 107
c further select refinements (from torek via karels)
e
s 00019/00012/00637
d D 8.7 94/08/10 22:19:13 mckusick 107 106
c a zero-valued timeout (which should poll and return) gets turned into
c a one-tick timeout, and (worse) the amount of time to sleep is not 
c recomputed after each sleep.  I.e., if the timeout is 10 sec, and 
c select is incorrectly after 9 sec, it will go back to sleep for up 
c to 10 sec.  In fact, in the worst case it will never return. (from karels)
e
s 00002/00010/00647
d D 8.6 94/07/07 15:38:18 mckusick 106 104
c size size_t is unsigned must check for overflow incrementally (from karels)
e
s 00000/00008/00649
d R 8.6 94/06/04 17:04:30 mckusick 105 104
c since size_t is unsigned, testing iov_len < 0 is futile
e
s 00005/00000/00652
d D 8.5 94/01/21 17:17:54 bostic 104 103
c add USL's copyright notice
e
s 00006/00006/00646
d D 8.4 93/09/23 15:32:34 bostic 103 102
c changes for 4.4BSD-Lite requested by USL
e
s 00017/00016/00635
d D 8.3 93/09/21 07:36:07 bostic 102 101
c changes for 4.4BSD-Lite requested by USL
e
s 00041/00041/00610
d D 8.2 93/09/05 09:36:24 bostic 101 100
c Cleanups for 4.4BSD-Lite
e
s 00002/00002/00649
d D 8.1 93/07/19 00:17:37 bostic 100 99
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00014/00015/00637
d D 7.39 93/07/19 00:17:05 mckusick 99 97
c guard against negative fd counts in select
e
s 00002/00002/00650
d R 8.1 93/06/10 21:58:41 bostic 98 97
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/00647
d D 7.38 93/02/26 11:35:05 mckusick 97 96
c explicitly avoid sleeping forever in select
e
s 00012/00012/00635
d D 7.37 92/10/11 10:38:26 bostic 96 95
c make kernel includes standard
e
s 00036/00035/00611
d D 7.36 92/07/10 21:05:46 torek 95 94
c ANSIfy syscall args; readv does not need ARGSUSED; no longer need
c ugly __STDC__ hack
e
s 00002/00002/00644
d D 7.35 92/07/07 16:49:53 torek 94 93
c only need to block clock; volatile poisoning
e
s 00003/00001/00643
d D 7.34 92/06/23 11:25:16 bostic 93 92
c select(2) race condition with small timeout values; bug net2/sys/11
e
s 00003/00003/00641
d D 7.33 92/03/13 16:51:46 mckusick 92 91
c minor optimization from torek
e
s 00038/00007/00606
d D 7.32 92/02/15 21:13:52 mckusick 91 90
c define new select interface, selrecord/selwakeup
e
s 00026/00035/00587
d D 7.31 92/02/13 17:56:52 torek 90 89
c cleanups for GCC, minor optimization in selscan
e
s 00002/00002/00620
d D 7.30 91/05/30 14:51:27 mckusick 89 88
c make file flags consistent
e
s 00001/00001/00621
d D 7.29 91/05/06 13:00:57 karels 88 87
c define selwait
e
s 00042/00004/00580
d D 7.28 91/04/16 00:01:31 mckusick 87 86
c add proc pointers to uio setup operations; inline expand fset/fioctl
e
s 00012/00009/00572
d D 7.27 91/04/12 18:08:54 karels 86 85
c rm user.h, OFILE*; seltrue needs ansified declaration
e
s 00015/00013/00566
d D 7.26 91/03/17 15:41:36 karels 85 84
c more-or-less working with new proc & user structs
e
s 00024/00017/00555
d D 7.25 91/01/10 23:43:47 mckusick 84 83
c add dynamically allocated file descriptors
e
s 00002/00000/00570
d D 7.24 90/08/24 10:41:40 bostic 83 82
c lint
e
s 00016/00014/00554
d D 7.23 90/07/22 10:22:13 karels 82 81
c free beginning of iovec buffer, not end; common subexpression elimination
e
s 00001/00011/00567
d D 7.22 90/06/28 21:22:28 bostic 81 80
c new copyright notice
e
s 00019/00019/00559
d D 7.21 90/06/28 17:11:10 karels 80 79
c RETURN => return, remove syscontext.h
e
s 00005/00004/00573
d D 7.20 90/06/22 17:19:26 mckusick 79 78
c have to pass error to ktrace
e
s 00001/00001/00576
d D 7.19 90/06/21 22:39:44 mckusick 78 77
c missing return value
e
s 00001/00004/00576
d D 7.18 90/06/21 19:35:28 mckusick 77 76
c devices no longer return errors; minor cleanup
e
s 00072/00053/00508
d D 7.17 90/06/05 22:02:11 mckusick 76 75
c update to new system call convention; expunge more u.u_error
e
s 00002/00006/00559
d D 7.16 90/05/15 15:51:10 mckusick 75 74
c clean up unexecuted code; lint
e
s 00008/00005/00557
d D 7.15 90/05/01 11:19:50 marc 74 73
c only ktrace i/o if successful
e
s 00068/00110/00494
d D 7.14 90/04/03 21:25:20 karels 73 72
c remove setjmp's; check for EINTR/ERESTART, and clear error if there's
c a short count to return; tsleep cleans up select; reduce use of u.u_error
e
s 00001/00001/00603
d D 7.13 90/02/07 15:39:53 marc 72 71
c tsleep
e
s 00002/00002/00602
d D 7.12 89/08/13 18:11:47 marc 71 70
c passing wrong argument to ktrgenio
e
s 00004/00004/00600
d D 7.11 89/05/27 14:42:59 mckusick 70 69
c must use saved credentials, not u.u_cred
e
s 00201/00085/00403
d D 7.10 89/05/09 17:02:35 mckusick 69 68
c merge in vnodes
e
s 00070/00023/00418
d D 7.9 89/03/10 10:33:21 karels 68 67
c marc's changes: malloc uio if too large, ktrace
e
s 00000/00013/00441
d D 7.8 88/08/27 15:45:26 karels 67 66
c rm 4.1 compat
e
s 00002/00001/00452
d D 7.7 88/05/24 19:26:06 mckusick 66 65
c lint
e
s 00001/00001/00452
d D 7.6 88/03/10 18:28:56 karels 65 64
c clear SSEL when done selecting
e
s 00003/00003/00450
d D 7.5 88/02/08 21:40:19 karels 64 63
c lint
e
s 00010/00007/00443
d D 7.4 87/06/20 15:02:05 mckusick 63 62
c replace geteblk with malloc
e
s 00000/00002/00450
d D 7.3 87/03/17 18:02:23 mckusick 62 61
c must avoid race between use and updating of f_offset pointer
e
s 00031/00016/00421
d D 7.2 87/02/19 17:27:56 karels 61 60
c allow ioctl to handle larger buffers (for pack labels)
e
s 00001/00001/00436
d D 7.1 86/06/05 00:07:39 mckusick 60 59
c 4.3BSD release version
e
s 00007/00007/00430
d D 6.15 86/03/04 19:55:01 karels 59 57
c consistency
e
s 00437/00000/00000
d R 6.15 86/03/04 19:25:23 karels 58 57
c consistency
e
s 00004/00004/00433
d D 6.14 86/02/20 15:58:28 karels 57 56
c cleanups from Sam: format, spl's, ptrace defs
e
s 00001/00001/00436
d D 6.13 86/02/04 17:17:03 karels 56 55
c consistency in select: never modify masks on return with an error,
c always if no error ( return >= 0)
e
s 00013/00022/00424
d D 6.12 85/06/17 21:58:39 karels 55 54
c move select bitmask macros to types.h, rename and structurize
e
s 00007/00001/00439
d D 6.11 85/06/08 14:42:53 mckusick 54 53
c Add copyright
e
s 00005/00003/00435
d D 6.10 85/05/27 19:59:51 karels 53 52
c select now leaves masks unmodified if interrupted (always)
e
s 00001/00002/00437
d D 6.9 85/05/22 19:48:31 mckusick 52 51
c eliminate double meaning of SOUSIG
e
s 00008/00003/00431
d D 6.8 85/03/12 13:53:12 mckusick 51 50
c add another bit to sigvec() flags to disable system call restart
e
s 00004/00004/00430
d D 6.7 85/02/08 17:52:59 karels 50 49
c don't drop spl during selwakeup
e
s 00039/00028/00395
d D 6.6 84/12/27 16:43:10 karels 49 48
c select on >32 files
e
s 00006/00003/00417
d D 6.5 84/10/19 10:54:16 karels 48 47
c don't setrun stopped procs in selwakeup
e
s 00010/00010/00410
d D 6.4 84/08/29 20:21:54 bloom 47 46
c Change to includes.  no more ../h
e
s 00001/00002/00419
d D 6.3 84/08/22 16:56:59 mckusick 46 45
c use GETF macro where appropriate
e
s 00001/00001/00420
d D 6.2 84/07/08 22:20:23 mckusick 45 44
c use proper definition of UIO flags
e
s 00000/00000/00421
d D 6.1 83/07/29 06:36:48 sam 44 43
c 4.2 distribution
e
s 00001/00000/00420
d D 5.42 83/06/24 14:47:26 sam 43 42
c infinite loop
e
s 00001/00001/00419
d D 5.41 83/06/21 20:36:00 sam 42 41
c change NOCOMPAT to COMPAT and make it work
e
s 00000/00018/00420
d D 5.40 83/06/12 14:28:47 sam 41 40
c cleanup fstat
e
s 00003/00001/00435
d D 5.39 83/06/12 12:46:36 sam 40 38
c blew it last time
e
s 00003/00001/00435
d R 5.39 83/06/11 12:30:32 sam 39 38
c mask bits so ffs in selscan always returns properly bounded value
e
s 00003/00001/00433
d D 5.38 83/06/10 21:24:31 sam 38 37
c timercmp isn't all that it's cracked up to be
e
s 00001/00001/00433
d D 5.37 83/06/02 15:57:16 sam 37 36
c new signals
e
s 00204/00352/00230
d D 5.36 83/05/27 12:47:42 sam 36 35
c merge of bill's code plus lint (plus, of course, cleanup of bill's bugs)
e
s 00000/00010/00582
d D 5.35 83/05/21 15:36:16 sam 35 34
c purge mush
e
s 00002/00002/00590
d D 5.34 83/05/08 13:37:43 sam 34 33
c format
e
s 00002/00001/00590
d D 5.33 83/05/06 17:01:23 helge 33 32
c added f_flag to the call to the driver ioctl routine
e
s 00002/00000/00589
d D 5.32 83/02/25 05:30:19 sam 32 31
c from shannon
e
s 00002/00000/00587
d D 5.31 83/02/18 12:43:51 sam 31 30
c put back append mode?
e
s 00013/00011/00574
d D 5.30 83/01/23 00:01:49 sam 30 29
c don't zero buffer when doing in/out ioctl's
e
s 00011/00015/00574
d D 5.29 82/12/28 23:47:44 sam 29 28
c copyin & copyout now return EFAULT and all callers uniformly 
c return (or ignore) this value
e
s 00001/00001/00588
d D 5.28 82/12/28 22:30:48 sam 28 27
c using return val from copyin/copyout -- causes uiomove to 
c give errno of -1 instead of EFAULT!!!
e
s 00001/00002/00588
d D 5.27 82/12/21 14:59:09 sam 27 26
c error uninitialized in uiomove
e
s 00001/00000/00589
d D 5.26 82/12/21 14:39:08 sam 26 25
c make mkdir & rmdir work with rdwri (still kludged)
e
s 00002/00002/00587
d D 5.25 82/12/09 19:01:57 sam 25 24
c u.u_pofile flags are now UF_*
e
s 00001/00001/00588
d D 5.24 82/12/05 22:00:34 sam 24 23
c include ioctl.h separate from tty.h
e
s 00003/00001/00586
d D 5.23 82/11/17 00:07:34 sam 23 22
c no return value and add read(..., 0) early return
e
s 00005/00001/00582
d D 5.22 82/11/13 22:48:40 sam 22 21
c merge of 4.1b and 4.1c; and missing check for 0 length write
e
s 00001/00001/00582
d D 5.21 82/10/21 23:53:36 root 21 20
c lint
e
s 00003/00001/00580
d D 5.20 82/10/21 20:58:02 root 20 19
c lint
e
s 00002/00002/00579
d D 5.19 82/10/19 10:31:12 root 19 18
c more lint
e
s 00002/00001/00579
d D 5.18 82/10/17 21:49:48 root 18 17
c more lint
e
s 00003/00003/00577
d D 5.17 82/10/17 11:34:46 root 17 16
c ioctl lower levels return errno's
e
s 00002/00002/00578
d D 5.16 82/10/13 22:08:14 root 16 15
c return errors from ioctl routines and internal ldisc routines
e
s 00003/00004/00577
d D 5.15 82/10/10 15:55:50 root 15 14
c header files to vax directories
e
s 00002/00002/00579
d D 5.14 82/09/08 08:07:19 root 14 13
c label_t now structure
e
s 00010/00000/00571
d D 5.13 82/09/06 22:54:24 root 13 12
c  
e
s 00002/00002/00569
d D 5.12 82/09/04 09:17:31 root 12 11
c cosmetic for new style limits
e
s 00376/00370/00195
d D 5.11 82/08/22 20:38:31 root 11 10
c first completely uio'd version
e
s 00026/00105/00539
d D 5.10 82/08/14 18:54:28 root 10 9
c no more readi()
e
s 00072/00035/00572
d D 5.9 82/08/14 18:01:26 root 9 8
c read() now goes through readip()
e
s 00012/00002/00595
d D 5.8 82/08/13 00:04:22 wnj 8 7
c fixes to get uio'd readi for char devs
e
s 00106/00000/00491
d D 5.7 82/08/11 21:11:35 root 7 6
c first use of readip()
e
s 00006/00014/00485
d D 5.6 82/08/10 17:44:45 sam 6 5
c don't copy stuff out if an error in lower levels
e
s 00081/00030/00418
d D 5.5 82/08/01 19:21:04 sam 5 4
c new ioctl's
e
s 00007/00011/00441
d D 5.4 82/07/25 23:13:15 root 4 3
c add more error checking on result of bmap (chk u.u_error)
e
s 00016/00003/00436
d D 5.3 82/07/24 18:10:50 root 3 2
c merge with calder
e
s 00009/00000/00430
d D 5.2 82/07/22 13:20:08 kre 2 1
c mush
e
s 00430/00000/00000
d D 5.1 82/07/15 20:16:17 root 1 0
c date and time created 82/07/15 20:16:17 by root
e
u
U
f i 
t
T
I 1
D 54
/*	%M%	%I%	%E%	*/
E 54
I 54
/*
D 60
 * Copyright (c) 1982 Regents of the University of California.
E 60
I 60
D 68
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 68
I 68
D 69
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
E 68
E 60
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 69
I 69
D 100
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
 * All rights reserved.
E 100
I 100
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
I 104
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 104
E 100
E 69
 *
I 69
D 81
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
E 81
I 81
 * %sccs.include.redist.c%
E 81
 *
E 69
 *	%W% (Berkeley) %G%
 */
E 54

D 47
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
I 24
#include "../h/ioctl.h"
E 24
D 36
#include "../h/tty.h"
E 36
I 3
D 6
#include "../h/fcntl.h"
E 6
E 3
#include "../h/file.h"
I 22
D 24
#define	IDEBUG
E 24
E 22
D 36
#include "../h/inode.h"
#include "../h/buf.h"
E 36
#include "../h/proc.h"
D 15
#include "../h/inline.h"
E 15
D 36
#include "../h/conf.h"
#include "../h/socket.h"
#include "../h/socketvar.h"
D 11
#include "../h/cmap.h"
#include "../h/vlimit.h"
E 11
#include "../h/fs.h"
I 2
D 35
#ifdef MUSH
#include "../h/quota.h"
#include "../h/share.h"
#else
#define	CHARGE(nothing)
#endif
E 35
I 11
D 12
#include "../h/vlimit.h"
E 12
E 11
I 3
#include "../h/descrip.h"
E 36
I 7
#include "../h/uio.h"
I 19
D 36
#include "../h/cmap.h"
E 36
I 36
#include "../h/kernel.h"
#include "../h/stat.h"
E 47
I 47
D 96
#include "param.h"
#include "systm.h"
D 69
#include "dir.h"
#include "user.h"
E 69
I 69
D 80
#include "syscontext.h"
E 80
I 80
D 86
#include "user.h"
E 86
I 84
#include "filedesc.h"
E 84
E 80
E 69
#include "ioctl.h"
#include "file.h"
I 87
D 91
#include "socketvar.h"
E 91
E 87
#include "proc.h"
I 91
#include "socketvar.h"
E 91
#include "uio.h"
#include "kernel.h"
#include "stat.h"
I 61
D 63
#include "buf.h"				/* XXX */
E 63
I 63
#include "malloc.h"
E 96
I 96
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/filedesc.h>
#include <sys/ioctl.h>
#include <sys/file.h>
#include <sys/proc.h>
#include <sys/socketvar.h>
#include <sys/uio.h>
#include <sys/kernel.h>
#include <sys/stat.h>
#include <sys/malloc.h>
E 96
I 68
#ifdef KTRACE
D 96
#include "ktrace.h"
E 96
I 96
#include <sys/ktrace.h>
E 96
#endif
E 68
E 63
E 61
E 47
E 36
E 19
E 7
E 3
E 2

I 109
#include <sys/mount.h>
#include <sys/syscallargs.h>

E 109
/*
 * Read system call.
 */
I 95
D 109
struct read_args {
D 101
	int	fdes;
	char	*cbuf;
	unsigned count;
E 101
I 101
	int	fd;
	char	*buf;
	u_int	nbyte;
E 101
};
E 109
E 95
I 83
/* ARGSUSED */
I 109
int
E 109
E 83
D 76
read()
{
D 11
	register struct file *fp;
	register struct inode *ip;
E 11
	register struct a {
E 76
I 76
read(p, uap, retval)
	struct proc *p;
D 95
	register struct args {
E 76
		int	fdes;
		char	*cbuf;
		unsigned count;
D 11
	} *uap;
E 11
I 11
D 76
	} *uap = (struct a *)u.u_ap;
E 76
I 76
	} *uap;
E 95
I 95
D 109
	register struct read_args *uap;
E 95
	int *retval;
E 109
I 109
	register struct read_args /* {
		syscallarg(int) fd;
		syscallarg(char *) buf;
		syscallarg(u_int) nbyte;
	} */ *uap;
	register_t *retval;
E 109
{
E 76
I 69
	register struct file *fp;
I 84
	register struct filedesc *fdp = p->p_fd;
E 84
E 69
E 11
I 9
	struct uio auio;
	struct iovec aiov;
I 69
	long cnt, error = 0;
#ifdef KTRACE
	struct iovec ktriov;
#endif
E 69
E 9

I 69
D 84
	if (((unsigned)uap->fdes) >= NOFILE ||
	    (fp = u.u_ofile[uap->fdes]) == NULL ||
E 84
I 84
D 85
	if (((unsigned)uap->fdes) >= fdp->fd_maxfiles ||
E 85
I 85
D 101
	if (((unsigned)uap->fdes) >= fdp->fd_nfiles ||
E 85
D 86
	    (fp = OFILE(fdp, uap->fdes)) == NULL ||
E 86
I 86
	    (fp = fdp->fd_ofiles[uap->fdes]) == NULL ||
E 101
I 101
D 109
	if (((u_int)uap->fd) >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[uap->fd]) == NULL ||
E 109
I 109
	if (((u_int)SCARG(uap, fd)) >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[SCARG(uap, fd)]) == NULL ||
E 109
E 101
E 86
E 84
	    (fp->f_flag & FREAD) == 0)
D 80
		RETURN (EBADF);
E 80
I 80
		return (EBADF);
E 80
D 75
	if (uap->count < 0)
		RETURN (EINVAL);
E 75
E 69
D 11
	uap = (struct a *)u.u_ap;
	if ((int)uap->count < 0) {
		u.u_error = EINVAL;
		return;
	}
	GETF(fp, uap->fdes);
	if ((fp->f_flag&FREAD) == 0) {
		u.u_error = EBADF;
		return;
	}
E 11
D 9
	u.u_base = (caddr_t)uap->cbuf;
	u.u_count = uap->count;
	u.u_segflg = 0;
E 9
I 9
D 101
	aiov.iov_base = (caddr_t)uap->cbuf;
	aiov.iov_len = uap->count;
E 101
I 101
D 109
	aiov.iov_base = (caddr_t)uap->buf;
	aiov.iov_len = uap->nbyte;
E 109
I 109
	aiov.iov_base = (caddr_t)SCARG(uap, buf);
	aiov.iov_len = SCARG(uap, nbyte);
E 109
E 101
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
D 11
	auio.uio_segflg = 0;
	auio.uio_resid = uap->count;
	u.u_base = (caddr_t)0xc0000000;
	u.u_count = 0x40000000;
E 9
	if ((u.u_procp->p_flag&SNUSIG) && setjmp(u.u_qsav)) {
D 9
		if (u.u_count == uap->count)
E 9
I 9
		if (auio.uio_resid == uap->count)
E 9
			u.u_eosys = RESTARTSYS;
D 3
	} else if (fp->f_flag & FSOCKET)
E 3
I 3
	} else if (fp->f_type == DTYPE_SOCKET)
E 3
D 9
		u.u_error = soreceive(fp->f_socket, (struct sockaddr *)0);
E 9
I 9
		u.u_error = soreceive(fp->f_socket, (struct sockaddr *)0, &auio);
E 9
	else {
		ip = fp->f_inode;
D 9
		u.u_offset = fp->f_offset;
E 9
I 9
		auio.uio_offset = fp->f_offset;
E 9
		if ((ip->i_mode&IFMT) == IFREG) {
			ilock(ip);
D 9
			readi(ip);
E 9
I 9
			u.u_error = readip(ip, &auio);
E 9
			iunlock(ip);
		} else
D 9
			readi(ip);
		fp->f_offset += uap->count - u.u_count;
E 9
I 9
			u.u_error = readip(ip, &auio);
		fp->f_offset += uap->count - auio.uio_resid;
E 11
I 11
D 69
	rwuio(&auio, UIO_READ);
E 69
I 69
D 101
	auio.uio_resid = uap->count;
E 101
I 101
D 109
	auio.uio_resid = uap->nbyte;
E 109
I 109
	auio.uio_resid = SCARG(uap, nbyte);
E 109
E 101
	auio.uio_rw = UIO_READ;
	auio.uio_segflg = UIO_USERSPACE;
I 87
	auio.uio_procp = p;
E 87
#ifdef KTRACE
	/*
	 * if tracing, save a copy of iovec
	 */
D 76
	if (KTRPOINT(u.u_procp, KTR_GENIO))
E 76
I 76
	if (KTRPOINT(p, KTR_GENIO))
E 76
		ktriov = aiov;
#endif
D 101
	cnt = uap->count;
E 101
I 101
D 109
	cnt = uap->nbyte;
E 109
I 109
	cnt = SCARG(uap, nbyte);
E 109
E 101
D 73
	if (setjmp(&u.u_qsave)) {
		if (auio.uio_resid == cnt) {
			if ((u.u_sigintr & sigmask(u.u_procp->p_cursig)) != 0)
				error = EINTR;
			else
				u.u_eosys = RESTARTSYS;
		}
	} else
D 70
		error = (*fp->f_ops->fo_read)(fp, &auio, u.u_cred);
E 70
I 70
		error = (*fp->f_ops->fo_read)(fp, &auio, fp->f_cred);
E 73
I 73
	if (error = (*fp->f_ops->fo_read)(fp, &auio, fp->f_cred))
		if (auio.uio_resid != cnt && (error == ERESTART ||
		    error == EINTR || error == EWOULDBLOCK))
			error = 0;
E 73
E 70
	cnt -= auio.uio_resid;
#ifdef KTRACE
D 74
	if (KTRPOINT(u.u_procp, KTR_GENIO))
E 74
I 74
D 76
	if (KTRPOINT(u.u_procp, KTR_GENIO) && error == 0)
E 74
D 71
		ktrgenio(u.u_procp->p_tracep, uap->fdes, UIO_READ, ktriov, cnt);
E 71
I 71
		ktrgenio(u.u_procp->p_tracep, uap->fdes, UIO_READ, &ktriov, cnt);
E 76
I 76
	if (KTRPOINT(p, KTR_GENIO) && error == 0)
D 79
		ktrgenio(p->p_tracep, uap->fdes, UIO_READ, &ktriov, cnt);
E 79
I 79
D 101
		ktrgenio(p->p_tracep, uap->fdes, UIO_READ, &ktriov, cnt, error);
E 101
I 101
D 109
		ktrgenio(p->p_tracep, uap->fd, UIO_READ, &ktriov, cnt, error);
E 109
I 109
		ktrgenio(p->p_tracep, SCARG(uap, fd), UIO_READ, &ktriov,
		    cnt, error);
E 109
E 101
E 79
E 76
E 71
#endif
D 76
	u.u_r.r_val1 = cnt;
E 76
I 76
	*retval = cnt;
E 76
D 80
	RETURN (error);
E 80
I 80
	return (error);
E 80
E 69
}

D 76
readv()
{
	register struct a {
E 76
I 76
/*
 * Scatter read system call.
 */
I 83
D 95
/* ARGSUSED */
E 95
I 95
D 109
struct readv_args {
	int	fdes;
	struct	iovec *iovp;
D 101
	unsigned iovcnt;
E 101
I 101
	u_int	iovcnt;
E 101
};
E 109
I 109
int
E 109
E 95
E 83
readv(p, uap, retval)
	struct proc *p;
D 95
	register struct args {
E 76
		int	fdes;
		struct	iovec *iovp;
D 59
		int	iovcnt;
E 59
I 59
		unsigned iovcnt;
E 59
D 76
	} *uap = (struct a *)u.u_ap;
E 76
I 76
	} *uap;
E 95
I 95
D 109
	register struct readv_args *uap;
E 95
	int *retval;
E 109
I 109
	register struct readv_args /* {
		syscallarg(int) fd;
		syscallarg(struct iovec *) iovp;
		syscallarg(u_int) iovcnt;
	} */ *uap;
	register_t *retval;
E 109
{
E 76
I 69
	register struct file *fp;
I 84
	register struct filedesc *fdp = p->p_fd;
E 84
E 69
	struct uio auio;
D 68
	struct iovec aiov[16];		/* XXX */
E 68
I 68
D 69
	struct iovec aiov[UIO_SMALLIOV], *iov;
E 69
I 69
	register struct iovec *iov;
I 82
D 90
	struct iovec *saveiov;
E 90
I 90
	struct iovec *needfree;
E 90
E 82
	struct iovec aiov[UIO_SMALLIOV];
	long i, cnt, error = 0;
I 82
D 101
	unsigned iovlen;
E 101
I 101
	u_int iovlen;
E 101
E 82
#ifdef KTRACE
	struct iovec *ktriov = NULL;
#endif
E 69
E 68

I 69
D 84
	if (((unsigned)uap->fdes) >= NOFILE ||
	    (fp = u.u_ofile[uap->fdes]) == NULL ||
E 84
I 84
D 85
	if (((unsigned)uap->fdes) >= fdp->fd_maxfiles ||
E 85
I 85
D 101
	if (((unsigned)uap->fdes) >= fdp->fd_nfiles ||
E 101
I 101
D 109
	if (((u_int)uap->fdes) >= fdp->fd_nfiles ||
E 101
E 85
D 86
	    (fp = OFILE(fdp, uap->fdes)) == NULL ||
E 86
I 86
	    (fp = fdp->fd_ofiles[uap->fdes]) == NULL ||
E 109
I 109
	if (((u_int)SCARG(uap, fd)) >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[SCARG(uap, fd)]) == NULL ||
E 109
E 86
E 84
	    (fp->f_flag & FREAD) == 0)
D 80
		RETURN (EBADF);
E 80
I 80
		return (EBADF);
I 82
	/* note: can't use iovlen until iovcnt is validated */
D 109
	iovlen = uap->iovcnt * sizeof (struct iovec);
E 82
E 80
E 69
D 59
	if (uap->iovcnt <= 0 || uap->iovcnt > sizeof(aiov)/sizeof(aiov[0])) {
E 59
I 59
D 68
	if (uap->iovcnt > sizeof(aiov)/sizeof(aiov[0])) {
E 59
		u.u_error = EINVAL;
		return;
E 11
E 9
	}
D 9
	u.u_r.r_val1 = uap->count - u.u_count;
E 9
I 9
D 11
	u.u_r.r_val1 = uap->count - auio.uio_resid;
E 11
I 11
	auio.uio_iov = aiov;
E 68
I 68
	if (uap->iovcnt > UIO_SMALLIOV) {
D 69
		if (uap->iovcnt > UIO_MAXIOV) {
			u.u_error = EINVAL;
			return;
		}
E 69
I 69
		if (uap->iovcnt > UIO_MAXIOV)
E 109
I 109
	iovlen = SCARG(uap, iovcnt) * sizeof (struct iovec);
	if (SCARG(uap, iovcnt) > UIO_SMALLIOV) {
		if (SCARG(uap, iovcnt) > UIO_MAXIOV)
E 109
D 80
			RETURN (EINVAL);
E 80
I 80
			return (EINVAL);
E 80
E 69
D 82
		MALLOC(iov, struct iovec *, 
		      sizeof(struct iovec) * uap->iovcnt, M_IOV, M_WAITOK);
E 82
I 82
		MALLOC(iov, struct iovec *, iovlen, M_IOV, M_WAITOK);
D 90
		saveiov = iov;
E 82
D 69
		if (iov == NULL) {
			u.u_error = ENOMEM;
			return;
		}
E 69
	} else
E 90
I 90
		needfree = iov;
	} else {
E 90
		iov = aiov;
I 90
		needfree = NULL;
	}
E 90
	auio.uio_iov = iov;
E 68
D 109
	auio.uio_iovcnt = uap->iovcnt;
E 109
I 109
	auio.uio_iovcnt = SCARG(uap, iovcnt);
E 109
D 29
	if (copyin((caddr_t)uap->iovp, (caddr_t)aiov,
	    (unsigned)(uap->iovcnt * sizeof (struct iovec)))) {
		u.u_error = EFAULT;
E 29
I 29
D 68
	u.u_error = copyin((caddr_t)uap->iovp, (caddr_t)aiov,
E 68
I 68
D 69
	u.u_error = copyin((caddr_t)uap->iovp, (caddr_t)auio.uio_iov,
E 68
D 59
	    (unsigned)(uap->iovcnt * sizeof (struct iovec)));
E 59
I 59
	    uap->iovcnt * sizeof (struct iovec));
E 59
	if (u.u_error)
E 69
I 69
	auio.uio_rw = UIO_READ;
	auio.uio_segflg = UIO_USERSPACE;
I 87
	auio.uio_procp = p;
E 87
D 82
	if (error = copyin((caddr_t)uap->iovp, (caddr_t)iov,
	    uap->iovcnt * sizeof (struct iovec)))
E 82
I 82
D 109
	if (error = copyin((caddr_t)uap->iovp, (caddr_t)iov, iovlen))
E 109
I 109
	if (error = copyin((caddr_t)SCARG(uap, iovp), (caddr_t)iov, iovlen))
E 109
E 82
E 69
E 29
D 68
		return;
E 68
I 68
		goto done;
E 68
D 29
	}
E 29
D 69
	rwuio(&auio, UIO_READ);
E 69
I 69
	auio.uio_resid = 0;
D 109
	for (i = 0; i < uap->iovcnt; i++) {
E 109
I 109
	for (i = 0; i < SCARG(uap, iovcnt); i++) {
E 109
D 106
		if (iov->iov_len < 0) {
E 106
I 106
		if (auio.uio_resid + iov->iov_len < auio.uio_resid) {
E 106
			error = EINVAL;
			goto done;
		}
		auio.uio_resid += iov->iov_len;
D 106
		if (auio.uio_resid < 0) {
			error = EINVAL;
			goto done;
		}
E 106
		iov++;
	}
#ifdef KTRACE
	/*
	 * if tracing, save a copy of iovec
	 */
D 76
	if (KTRPOINT(u.u_procp, KTR_GENIO))  {
E 76
I 76
	if (KTRPOINT(p, KTR_GENIO))  {
E 76
D 75
		int iovlen = auio.uio_iovcnt * sizeof (struct iovec);
E 75
I 75
D 82
		unsigned iovlen = auio.uio_iovcnt * sizeof (struct iovec);
E 75

E 82
		MALLOC(ktriov, struct iovec *, iovlen, M_TEMP, M_WAITOK);
		bcopy((caddr_t)auio.uio_iov, (caddr_t)ktriov, iovlen);
	}
#endif
	cnt = auio.uio_resid;
D 73
	if (setjmp(&u.u_qsave)) {
		if (auio.uio_resid == cnt) {
			if ((u.u_sigintr & sigmask(u.u_procp->p_cursig)) != 0)
				error = EINTR;
			else
				u.u_eosys = RESTARTSYS;
		}
	} else
D 70
		error = (*fp->f_ops->fo_read)(fp, &auio, u.u_cred);
E 70
I 70
		error = (*fp->f_ops->fo_read)(fp, &auio, fp->f_cred);
E 73
I 73
	if (error = (*fp->f_ops->fo_read)(fp, &auio, fp->f_cred))
		if (auio.uio_resid != cnt && (error == ERESTART ||
		    error == EINTR || error == EWOULDBLOCK))
			error = 0;
E 73
E 70
	cnt -= auio.uio_resid;
#ifdef KTRACE
	if (ktriov != NULL) {
D 74
		ktrgenio(u.u_procp->p_tracep, uap->fdes, UIO_READ, ktriov, cnt);
E 74
I 74
		if (error == 0)
D 76
			ktrgenio(u.u_procp->p_tracep, uap->fdes, UIO_READ, 
				ktriov, cnt);
E 76
I 76
D 79
			ktrgenio(p->p_tracep, uap->fdes, UIO_READ, ktriov, cnt);
E 79
I 79
D 109
			ktrgenio(p->p_tracep, uap->fdes, UIO_READ, ktriov,
E 109
I 109
			ktrgenio(p->p_tracep, SCARG(uap, fd), UIO_READ, ktriov,
E 109
			    cnt, error);
E 79
E 76
E 74
		FREE(ktriov, M_TEMP);
	}
#endif
D 76
	u.u_r.r_val1 = cnt;
E 76
I 76
	*retval = cnt;
E 76
E 69
I 68
done:
D 69
	if (iov != aiov)
E 69
I 69
D 90
	if (uap->iovcnt > UIO_SMALLIOV)
E 69
D 82
		FREE(iov, M_IOV);
E 82
I 82
		FREE(saveiov, M_IOV);
E 90
I 90
	if (needfree)
		FREE(needfree, M_IOV);
E 90
E 82
I 69
D 80
	RETURN (error);
E 80
I 80
	return (error);
E 80
E 69
E 68
E 11
E 9
}

/*
 * Write system call
 */
I 95
D 109
struct write_args {
D 101
	int	fdes;
	char	*cbuf;
	unsigned count;
E 101
I 101
	int	fd;
	char	*buf;
	u_int	nbyte;
E 101
};
E 109
I 109
int
E 109
E 95
D 76
write()
{
D 11
	register struct file *fp;
	register struct inode *ip;
E 11
	register struct a {
E 76
I 76
write(p, uap, retval)
	struct proc *p;
D 95
	register struct args {
E 76
		int	fdes;
		char	*cbuf;
D 11
		unsigned count;
	} *uap;
E 11
I 11
D 59
		int	count;
E 59
I 59
		unsigned count;
E 59
D 76
	} *uap = (struct a *)u.u_ap;
E 76
I 76
	} *uap;
E 95
I 95
D 109
	register struct write_args *uap;
E 95
	int *retval;
E 109
I 109
	register struct write_args /* {
		syscallarg(int) fd;
		syscallarg(char *) buf;
		syscallarg(u_int) nbyte;
	} */ *uap;
	register_t *retval;
E 109
{
E 76
I 69
	register struct file *fp;
I 84
	register struct filedesc *fdp = p->p_fd;
E 84
E 69
	struct uio auio;
	struct iovec aiov;
I 69
	long cnt, error = 0;
#ifdef KTRACE
	struct iovec ktriov;
#endif
E 69
E 11

I 69
D 84
	if (((unsigned)uap->fdes) >= NOFILE ||
	    (fp = u.u_ofile[uap->fdes]) == NULL ||
E 84
I 84
D 85
	if (((unsigned)uap->fdes) >= fdp->fd_maxfiles ||
E 85
I 85
D 101
	if (((unsigned)uap->fdes) >= fdp->fd_nfiles ||
E 85
D 86
	    (fp = OFILE(fdp, uap->fdes)) == NULL ||
E 86
I 86
	    (fp = fdp->fd_ofiles[uap->fdes]) == NULL ||
E 101
I 101
D 109
	if (((u_int)uap->fd) >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[uap->fd]) == NULL ||
E 109
I 109
	if (((u_int)SCARG(uap, fd)) >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[SCARG(uap, fd)]) == NULL ||
E 109
E 101
E 86
E 84
	    (fp->f_flag & FWRITE) == 0)
D 80
		RETURN (EBADF);
E 80
I 80
		return (EBADF);
E 80
D 75
	if (uap->count < 0)
		RETURN (EINVAL);
E 75
D 101
	aiov.iov_base = (caddr_t)uap->cbuf;
	aiov.iov_len = uap->count;
E 101
I 101
D 109
	aiov.iov_base = (caddr_t)uap->buf;
	aiov.iov_len = uap->nbyte;
E 109
I 109
	aiov.iov_base = (caddr_t)SCARG(uap, buf);
	aiov.iov_len = SCARG(uap, nbyte);
E 109
E 101
E 69
D 11
	uap = (struct a *)u.u_ap;
	if ((int)uap->count < 0) {
E 11
I 11
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
D 69
	aiov.iov_base = uap->cbuf;
	aiov.iov_len = uap->count;
	rwuio(&auio, UIO_WRITE);
E 69
I 69
D 101
	auio.uio_resid = uap->count;
E 101
I 101
D 109
	auio.uio_resid = uap->nbyte;
E 109
I 109
	auio.uio_resid = SCARG(uap, nbyte);
E 109
E 101
	auio.uio_rw = UIO_WRITE;
	auio.uio_segflg = UIO_USERSPACE;
I 87
	auio.uio_procp = p;
E 87
#ifdef KTRACE
	/*
	 * if tracing, save a copy of iovec
	 */
D 76
	if (KTRPOINT(u.u_procp, KTR_GENIO))
E 76
I 76
	if (KTRPOINT(p, KTR_GENIO))
E 76
		ktriov = aiov;
#endif
D 101
	cnt = uap->count;
E 101
I 101
D 109
	cnt = uap->nbyte;
E 109
I 109
	cnt = SCARG(uap, nbyte);
E 109
E 101
D 73
	if (setjmp(&u.u_qsave)) {
		if (auio.uio_resid == cnt) {
			if ((u.u_sigintr & sigmask(u.u_procp->p_cursig)) != 0)
				error = EINTR;
			else
				u.u_eosys = RESTARTSYS;
		}
	} else
D 70
		error = (*fp->f_ops->fo_write)(fp, &auio, u.u_cred);
E 70
I 70
		error = (*fp->f_ops->fo_write)(fp, &auio, fp->f_cred);
E 73
I 73
	if (error = (*fp->f_ops->fo_write)(fp, &auio, fp->f_cred)) {
		if (auio.uio_resid != cnt && (error == ERESTART ||
		    error == EINTR || error == EWOULDBLOCK))
			error = 0;
		if (error == EPIPE)
D 76
			psignal(u.u_procp, SIGPIPE);
E 76
I 76
			psignal(p, SIGPIPE);
E 76
	}
E 73
E 70
	cnt -= auio.uio_resid;
#ifdef KTRACE
D 74
	if (KTRPOINT(u.u_procp, KTR_GENIO))
E 74
I 74
D 76
	if (KTRPOINT(u.u_procp, KTR_GENIO) && error == 0)
E 74
		ktrgenio(u.u_procp->p_tracep, uap->fdes, UIO_WRITE,
E 76
I 76
	if (KTRPOINT(p, KTR_GENIO) && error == 0)
D 101
		ktrgenio(p->p_tracep, uap->fdes, UIO_WRITE,
E 101
I 101
D 109
		ktrgenio(p->p_tracep, uap->fd, UIO_WRITE,
E 109
I 109
		ktrgenio(p->p_tracep, SCARG(uap, fd), UIO_WRITE,
E 109
E 101
E 76
D 71
		    ktriov, cnt);
E 71
I 71
D 79
		    &ktriov, cnt);
E 79
I 79
		    &ktriov, cnt, error);
E 79
E 71
#endif
D 76
	u.u_r.r_val1 = cnt;
E 76
I 76
	*retval = cnt;
E 76
D 80
	RETURN (error);
E 80
I 80
	return (error);
E 80
E 69
}

D 76
writev()
{
	register struct a {
E 76
I 76
/*
 * Gather write system call
 */
I 95
D 109
struct writev_args {
D 101
	int	fdes;
E 101
I 101
	int	fd;
E 101
	struct	iovec *iovp;
D 101
	unsigned iovcnt;
E 101
I 101
	u_int	iovcnt;
E 101
};
E 109
I 109
int
E 109
E 95
writev(p, uap, retval)
	struct proc *p;
D 95
	register struct args {
E 76
		int	fdes;
		struct	iovec *iovp;
D 59
		int	iovcnt;
E 59
I 59
		unsigned iovcnt;
E 59
D 76
	} *uap = (struct a *)u.u_ap;
E 76
I 76
	} *uap;
E 95
I 95
D 109
	register struct writev_args *uap;
E 95
	int *retval;
E 109
I 109
	register struct writev_args /* {
		syscallarg(int) fd;
		syscallarg(struct iovec *) iovp;
		syscallarg(u_int) iovcnt;
	} */ *uap;
	register_t *retval;
E 109
{
E 76
I 69
	register struct file *fp;
I 84
	register struct filedesc *fdp = p->p_fd;
E 84
E 69
	struct uio auio;
D 68
	struct iovec aiov[16];		/* XXX */
E 68
I 68
D 69
	struct iovec aiov[UIO_SMALLIOV], *iov;
E 69
I 69
	register struct iovec *iov;
I 82
D 90
	struct iovec *saveiov;
E 90
I 90
	struct iovec *needfree;
E 90
E 82
	struct iovec aiov[UIO_SMALLIOV];
	long i, cnt, error = 0;
I 82
D 101
	unsigned iovlen;
E 101
I 101
	u_int iovlen;
E 101
E 82
#ifdef KTRACE
	struct iovec *ktriov = NULL;
#endif
E 69
E 68

I 69
D 84
	if (((unsigned)uap->fdes) >= NOFILE ||
	    (fp = u.u_ofile[uap->fdes]) == NULL ||
E 84
I 84
D 85
	if (((unsigned)uap->fdes) >= fdp->fd_maxfiles ||
E 85
I 85
D 101
	if (((unsigned)uap->fdes) >= fdp->fd_nfiles ||
E 85
D 86
	    (fp = OFILE(fdp, uap->fdes)) == NULL ||
E 86
I 86
	    (fp = fdp->fd_ofiles[uap->fdes]) == NULL ||
E 101
I 101
D 109
	if (((u_int)uap->fd) >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[uap->fd]) == NULL ||
E 109
I 109
	if (((u_int)SCARG(uap, fd)) >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[SCARG(uap, fd)]) == NULL ||
E 109
E 101
E 86
E 84
	    (fp->f_flag & FWRITE) == 0)
D 80
		RETURN (EBADF);
E 80
I 80
		return (EBADF);
I 82
	/* note: can't use iovlen until iovcnt is validated */
D 109
	iovlen = uap->iovcnt * sizeof (struct iovec);
E 82
E 80
E 69
D 59
	if (uap->iovcnt <= 0 || uap->iovcnt > sizeof(aiov)/sizeof(aiov[0])) {
E 59
I 59
D 68
	if (uap->iovcnt > sizeof(aiov)/sizeof(aiov[0])) {
E 59
E 11
		u.u_error = EINVAL;
		return;
	}
D 11
	GETF(fp, uap->fdes);
	if ((fp->f_flag&FWRITE) == 0) {
E 11
I 11
	auio.uio_iov = aiov;
E 68
I 68
	if (uap->iovcnt > UIO_SMALLIOV) {
D 69
		if (uap->iovcnt > UIO_MAXIOV) {
			u.u_error = EINVAL;
			return;
		}
E 69
I 69
		if (uap->iovcnt > UIO_MAXIOV)
E 109
I 109
	iovlen = SCARG(uap, iovcnt) * sizeof (struct iovec);
	if (SCARG(uap, iovcnt) > UIO_SMALLIOV) {
		if (SCARG(uap, iovcnt) > UIO_MAXIOV)
E 109
D 80
			RETURN (EINVAL);
E 80
I 80
			return (EINVAL);
E 80
E 69
D 82
		MALLOC(iov, struct iovec *, 
		      sizeof(struct iovec) * uap->iovcnt, M_IOV, M_WAITOK);
E 82
I 82
		MALLOC(iov, struct iovec *, iovlen, M_IOV, M_WAITOK);
D 90
		saveiov = iov;
E 82
D 69
		if (iov == NULL) {
			u.u_error = ENOMEM;
			return;
		}
E 69
	} else
E 90
I 90
		needfree = iov;
	} else {
E 90
		iov = aiov;
I 90
		needfree = NULL;
	}
E 90
	auio.uio_iov = iov;
E 68
D 109
	auio.uio_iovcnt = uap->iovcnt;
E 109
I 109
	auio.uio_iovcnt = SCARG(uap, iovcnt);
E 109
D 29
	if (copyin((caddr_t)uap->iovp, (caddr_t)aiov,
	    (unsigned)(uap->iovcnt * sizeof (struct iovec)))) {
		u.u_error = EFAULT;
E 29
I 29
D 68
	u.u_error = copyin((caddr_t)uap->iovp, (caddr_t)aiov,
E 68
I 68
D 69
	u.u_error = copyin((caddr_t)uap->iovp, (caddr_t)auio.uio_iov,
E 68
D 59
	    (unsigned)(uap->iovcnt * sizeof (struct iovec)));
E 59
I 59
	    uap->iovcnt * sizeof (struct iovec));
E 59
	if (u.u_error)
E 69
I 69
	auio.uio_rw = UIO_WRITE;
	auio.uio_segflg = UIO_USERSPACE;
I 87
	auio.uio_procp = p;
E 87
D 82
	if (error = copyin((caddr_t)uap->iovp, (caddr_t)iov,
	    uap->iovcnt * sizeof (struct iovec)))
E 82
I 82
D 109
	if (error = copyin((caddr_t)uap->iovp, (caddr_t)iov, iovlen))
E 109
I 109
	if (error = copyin((caddr_t)SCARG(uap, iovp), (caddr_t)iov, iovlen))
E 109
E 82
E 69
E 29
D 68
		return;
E 68
I 68
		goto done;
E 68
D 29
	}
E 29
D 69
	rwuio(&auio, UIO_WRITE);
I 68
done:
	if (iov != aiov)
		FREE(iov, M_IOV);
E 68
}

rwuio(uio, rw)
	register struct uio *uio;
	enum uio_rw rw;
{
	struct a {
		int	fdes;
	};
	register struct file *fp;
	register struct iovec *iov;
D 36
	register struct inode *ip;
E 36
	int i, count;
I 68
#ifdef KTRACE
	struct iovec *ktriov = NULL;
#endif
E 68

I 68

E 68
	GETF(fp, ((struct a *)u.u_ap)->fdes);
	if ((fp->f_flag&(rw==UIO_READ ? FREAD : FWRITE)) == 0) {
E 11
		u.u_error = EBADF;
		return;
	}
D 11
	u.u_base = (caddr_t)uap->cbuf;
	u.u_count = uap->count;
	u.u_segflg = 0;
E 11
I 11
	uio->uio_resid = 0;
D 45
	uio->uio_segflg = 0;
E 45
I 45
	uio->uio_segflg = UIO_USERSPACE;
E 45
	iov = uio->uio_iov;
	for (i = 0; i < uio->uio_iovcnt; i++) {
E 69
I 69
	auio.uio_resid = 0;
D 109
	for (i = 0; i < uap->iovcnt; i++) {
E 109
I 109
	for (i = 0; i < SCARG(uap, iovcnt); i++) {
E 109
E 69
D 106
		if (iov->iov_len < 0) {
E 106
I 106
		if (auio.uio_resid + iov->iov_len < auio.uio_resid) {
E 106
D 69
			u.u_error = EINVAL;
			return;
E 69
I 69
			error = EINVAL;
			goto done;
E 69
		}
D 69
		uio->uio_resid += iov->iov_len;
		if (uio->uio_resid < 0) {
			u.u_error = EINVAL;
			return;
E 69
I 69
		auio.uio_resid += iov->iov_len;
D 106
		if (auio.uio_resid < 0) {
			error = EINVAL;
			goto done;
E 69
		}
E 106
I 43
		iov++;
E 43
	}
D 69
	count = uio->uio_resid;
E 69
I 68
#ifdef KTRACE
D 69
	/* if tracing, save a copy of iovec */
E 69
I 69
	/*
	 * if tracing, save a copy of iovec
	 */
E 69
D 76
	if (KTRPOINT(u.u_procp, KTR_GENIO))  {
E 76
I 76
	if (KTRPOINT(p, KTR_GENIO))  {
E 76
D 69
		int iovlen = uio->uio_iovcnt * sizeof (struct iovec);
E 69
I 69
D 75
		int iovlen = auio.uio_iovcnt * sizeof (struct iovec);
E 75
I 75
D 82
		unsigned iovlen = auio.uio_iovcnt * sizeof (struct iovec);
E 75
E 69

E 82
		MALLOC(ktriov, struct iovec *, iovlen, M_TEMP, M_WAITOK);
D 69
		if (ktriov != NULL)
			bcopy((caddr_t)uio->uio_iov, (caddr_t)ktriov, iovlen);
E 69
I 69
		bcopy((caddr_t)auio.uio_iov, (caddr_t)ktriov, iovlen);
E 69
	}
#endif
I 69
	cnt = auio.uio_resid;
E 69
E 68
I 36
D 62
	uio->uio_offset = fp->f_offset;
E 62
E 36
E 11
D 14
	if ((u.u_procp->p_flag&SNUSIG) && setjmp(u.u_qsav)) {
E 14
I 14
D 37
	if ((u.u_procp->p_flag&SNUSIG) && setjmp(&u.u_qsave)) {
E 37
I 37
D 51
	if ((u.u_procp->p_flag&SOUSIG) == 0 && setjmp(&u.u_qsave)) {
E 37
E 14
D 11
		if (u.u_count == uap->count)
E 11
I 11
		if (uio->uio_resid == count)
E 11
			u.u_eosys = RESTARTSYS;
E 51
I 51
D 73
	if (setjmp(&u.u_qsave)) {
D 69
		if (uio->uio_resid == count) {
E 69
I 69
		if (auio.uio_resid == cnt) {
E 69
D 52
			if ((u.u_sigintr & sigmask(u.u_procp->p_cursig)) != 0 ||
			    (u.u_procp->p_flag & SOUSIG) != 0)
E 52
I 52
			if ((u.u_sigintr & sigmask(u.u_procp->p_cursig)) != 0)
E 52
D 69
				u.u_error = EINTR;
E 69
I 69
				error = EINTR;
E 69
			else
				u.u_eosys = RESTARTSYS;
		}
E 51
D 3
	} else if (fp->f_flag & FSOCKET)
E 3
I 3
D 11
	} else if (fp->f_type == DTYPE_SOCKET)
E 3
		u.u_error = sosend(fp->f_socket, (struct sockaddr *)0);
	else {
E 11
I 11
D 36
	} else if (fp->f_type == DTYPE_SOCKET) {
		int sosend(), soreceive();
		u.u_error = 
		    (*(rw==UIO_READ?soreceive:sosend))
D 15
		      (fp->f_socket, (struct sockaddr *)0, uio);
E 15
I 15
		      (fp->f_socket, (struct sockaddr *)0, uio, 0);
E 15
	} else {
E 11
		ip = fp->f_inode;
I 3
D 6
		if (fp->f_flag & O_APPEND)
E 6
I 6
D 11
		if (fp->f_flag&FAPPEND)
E 6
			fp->f_offset = ip->i_size;
E 3
		u.u_offset = fp->f_offset;
E 11
I 11
		uio->uio_offset = fp->f_offset;
E 11
		if ((ip->i_mode&IFMT) == IFREG) {
D 15
			ilock(ip);
E 15
I 15
			ILOCK(ip);
I 31
			if (fp->f_flag&FAPPEND && rw == UIO_WRITE)
				uio->uio_offset = fp->f_offset = ip->i_size;
E 31
E 15
D 11
			writei(ip);
E 11
I 11
			u.u_error = rwip(ip, uio, rw);
E 11
D 15
			iunlock(ip);
E 15
I 15
			IUNLOCK(ip);
E 15
		} else
D 11
			writei(ip);
		fp->f_offset += uap->count - u.u_count;
E 11
I 11
			u.u_error = rwip(ip, uio, rw);
		fp->f_offset += count - uio->uio_resid;
E 11
	}
E 36
I 36
	} else
D 69
		u.u_error = (*fp->f_ops->fo_rw)(fp, rw, uio);
E 36
D 11
	u.u_r.r_val1 = uap->count - u.u_count;
E 11
I 11
	u.u_r.r_val1 = count - uio->uio_resid;
E 69
I 69
D 70
		error = (*fp->f_ops->fo_write)(fp, &auio, u.u_cred);
E 70
I 70
		error = (*fp->f_ops->fo_write)(fp, &auio, fp->f_cred);
E 73
I 73
	if (error = (*fp->f_ops->fo_write)(fp, &auio, fp->f_cred)) {
		if (auio.uio_resid != cnt && (error == ERESTART ||
		    error == EINTR || error == EWOULDBLOCK))
			error = 0;
		if (error == EPIPE)
D 76
			psignal(u.u_procp, SIGPIPE);
E 76
I 76
			psignal(p, SIGPIPE);
E 76
	}
E 73
E 70
	cnt -= auio.uio_resid;
E 69
I 68
#ifdef KTRACE
	if (ktriov != NULL) {
D 69
		ktrgenio(u.u_procp->p_tracep, ((struct a *)u.u_ap)->fdes,
			rw, ktriov, u.u_r.r_val1);
E 69
I 69
D 74
		ktrgenio(u.u_procp->p_tracep, uap->fdes, UIO_WRITE,
		    ktriov, cnt);
E 74
I 74
		if (error == 0)
D 76
			ktrgenio(u.u_procp->p_tracep, uap->fdes, UIO_WRITE,
E 76
I 76
D 101
			ktrgenio(p->p_tracep, uap->fdes, UIO_WRITE,
E 101
I 101
D 109
			ktrgenio(p->p_tracep, uap->fd, UIO_WRITE,
E 109
I 109
			ktrgenio(p->p_tracep, SCARG(uap, fd), UIO_WRITE,
E 109
E 101
E 76
D 79
				ktriov, cnt);
E 79
I 79
				ktriov, cnt, error);
E 79
E 74
E 69
		FREE(ktriov, M_TEMP);
	}
#endif
I 69
D 76
	u.u_r.r_val1 = cnt;
E 76
I 76
	*retval = cnt;
E 76
done:
D 90
	if (uap->iovcnt > UIO_SMALLIOV)
D 82
		FREE(iov, M_IOV);
E 82
I 82
		FREE(saveiov, M_IOV);
E 90
I 90
	if (needfree)
		FREE(needfree, M_IOV);
E 90
E 82
D 80
	RETURN (error);
E 80
I 80
	return (error);
E 80
E 69
E 68
I 36
D 62
	fp->f_offset += u.u_r.r_val1;
E 62
E 36
E 11
}

I 3
D 11
readv()
E 11
I 11
D 36
rdwri(rw, ip, base, len, offset, segflg, aresid)
	struct inode *ip;
	caddr_t base;
	int len, offset, segflg;
	int *aresid;
	enum uio_rw rw;
E 11
{
I 11
	struct uio auio;
	struct iovec aiov;
	int error;
E 11
E 3

I 11
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	aiov.iov_base = base;
	aiov.iov_len = len;
	auio.uio_resid = len;
	auio.uio_offset = offset;
	auio.uio_segflg = segflg;
	error = rwip(ip, &auio, rw);
	if (aresid)
		*aresid = auio.uio_resid;
	else
		if (auio.uio_resid)
			error = EIO;
	return (error);
E 11
I 3
}

D 11
writev()
E 11
I 11
rwip(ip, uio, rw)
	register struct inode *ip;
	register struct uio *uio;
	enum uio_rw rw;
E 11
{
I 11
	dev_t dev = (dev_t)ip->i_rdev;
	struct buf *bp;
	struct fs *fs;
	daddr_t lbn, bn;
D 19
	register int on, type;
	register unsigned n;
E 19
I 19
	register int n, on, type;
E 19
	int size;
	long bsize;
	extern int mem_no;
	int error = 0;
E 11

I 11
	if (rw != UIO_READ && rw != UIO_WRITE)
		panic("rwip");
I 23
	if (rw == UIO_READ && uio->uio_resid == 0)
		return (0);
E 23
	if (uio->uio_offset < 0 &&
	    ((ip->i_mode&IFMT) != IFCHR || mem_no != major(dev)))
D 22
		return (EINVAL); if (rw == UIO_READ)
E 22
I 22
		return (EINVAL);
	if (rw == UIO_READ)
E 22
		ip->i_flag |= IACC;
	type = ip->i_mode&IFMT;
	if (type == IFCHR) {
D 35
#ifdef QUOTA
		register c = uio->uio_resid;
#endif
E 35
		if (rw == UIO_READ)
D 16
			(*cdevsw[major(dev)].d_read)(dev, uio);
E 16
I 16
			u.u_error = (*cdevsw[major(dev)].d_read)(dev, uio);
E 16
		else {
			ip->i_flag |= IUPD|ICHG;
D 16
			(*cdevsw[major(dev)].d_write)(dev, uio);
E 16
I 16
			u.u_error = (*cdevsw[major(dev)].d_write)(dev, uio);
E 16
		}
D 35
		CHARGE(sc_tio * (c - uio->uio_resid));
E 35
		return (u.u_error);
	}
I 22
	if (uio->uio_resid == 0)
D 23
		return;
E 23
I 23
		return (0);
E 23
E 22
	if (rw == UIO_WRITE && type == IFREG &&
D 12
	    uio->uio_offset + uio->uio_resid > u.u_limit[LIM_FSIZE]) {
E 12
I 12
	    uio->uio_offset + uio->uio_resid >
	      u.u_rlimit[RLIMIT_FSIZE].rlim_cur) {
E 12
		psignal(u.u_procp, SIGXFSZ);
		return (EMFILE);
	}
	if (type != IFBLK) {
		dev = ip->i_dev;
		fs = ip->i_fs;
		bsize = fs->fs_bsize;
	} else
		bsize = BLKDEV_IOSIZE;
	do {
		lbn = uio->uio_offset / bsize;
		on = uio->uio_offset % bsize;
		n = MIN((unsigned)(bsize - on), uio->uio_resid);
		if (type != IFBLK) {
			if (rw == UIO_READ) {
				int diff = ip->i_size - uio->uio_offset;
				if (diff <= 0)
					return (0);
				if (diff < n)
					n = diff;
			}
I 26
D 27
			u.u_error = 0;		/* XXX */
E 27
E 26
			bn = fsbtodb(fs,
			    bmap(ip, lbn, rw == UIO_WRITE ? B_WRITE: B_READ, (int)(on+n)));
			if (u.u_error || rw == UIO_WRITE && (long)bn<0)
				return (u.u_error);
			if (rw == UIO_WRITE && uio->uio_offset + n > ip->i_size &&
			   (type == IFDIR || type == IFREG || type == IFLNK))
				ip->i_size = uio->uio_offset + n;
			size = blksize(fs, ip, lbn);
		} else {
			bn = lbn * (BLKDEV_IOSIZE/DEV_BSIZE);
			rablock = bn + (BLKDEV_IOSIZE/DEV_BSIZE);
			rasize = size = bsize;
		}
		if (rw == UIO_READ) {
			if ((long)bn<0) {
				bp = geteblk(size);
				clrbuf(bp);
			} else if (ip->i_lastr + 1 == lbn)
				bp = breada(dev, bn, size, rablock, rasize);
			else
				bp = bread(dev, bn, size);
			ip->i_lastr = lbn;
		} else {
			int i, count;
I 18
			extern struct cmap *mfind();
E 18

			count = howmany(size, DEV_BSIZE);
			for (i = 0; i < count; i += CLSIZE)
				if (mfind(dev, bn + i))
					munhash(dev, bn + i);
			if (n == bsize) 
				bp = getblk(dev, bn, size);
			else
				bp = bread(dev, bn, size);
		}
		n = MIN(n, size - bp->b_resid);
		if (bp->b_flags & B_ERROR) {
			error = EIO;
			brelse(bp);
			goto bad;
		}
		u.u_error =
D 18
		    uiomove(bp->b_un.b_addr+on, (u_int)n, rw, uio);
E 18
I 18
D 20
		    uiomove(bp->b_un.b_addr+on, n, rw, uio);
E 20
I 20
D 21
		    (void) uiomove(bp->b_un.b_addr+on, n, rw, uio);
E 21
I 21
		    uiomove(bp->b_un.b_addr+on, n, rw, uio);
E 21
E 20
E 18
		if (rw == UIO_READ) {
			if (n + on == bsize || uio->uio_offset == ip->i_size)
				bp->b_flags |= B_AGE;
			brelse(bp);
		} else {
			if ((ip->i_mode&IFMT) == IFDIR)
				bwrite(bp);
			else if (n + on == bsize) {
				bp->b_flags |= B_AGE;
				bawrite(bp);
			} else
				bdwrite(bp);
			ip->i_flag |= IUPD|ICHG;
			if (u.u_ruid != 0)
				ip->i_mode &= ~(ISUID|ISGID);
		}
	} while (u.u_error == 0 && uio->uio_resid > 0 && n != 0);
bad:
	return (error);
E 11
}

I 11
uiomove(cp, n, rw, uio)
	register caddr_t cp;
	register int n;
	enum uio_rw rw;
	register struct uio *uio;
{
	register struct iovec *iov;
D 27
	int error;
E 27
	u_int cnt;
I 27
	int error = 0;
E 27

	while (n > 0 && uio->uio_resid) {
		iov = uio->uio_iov;
		cnt = iov->iov_len;
		if (cnt == 0) {
			uio->uio_iov++;
			uio->uio_iovcnt--;
			continue;
		}
		if (cnt > n)
			cnt = n;
		switch (uio->uio_segflg) {

		case 0:
		case 2:
			if (rw == UIO_READ)
				error = copyout(cp, iov->iov_base, cnt);
			else
				error = copyin(iov->iov_base, cp, cnt);
			if (error)
D 28
				return (error);
E 28
I 28
D 29
				return (EFAULT);	/* XXX */
E 29
I 29
				return (error);
E 29
E 28
			break;

		case 1:
			if (rw == UIO_READ)
				bcopy((caddr_t)cp, iov->iov_base, cnt);
			else
				bcopy(iov->iov_base, (caddr_t)cp, cnt);
			break;
		}
		iov->iov_base += cnt;
		iov->iov_len -= cnt;
		uio->uio_resid -= cnt;
		uio->uio_offset += cnt;
		cp += cnt;
		n -= cnt;
	}
	return (error);
}

E 36
E 11
E 3
/*
I 11
D 36
 * Give next character to user as result of read.
 */
ureadc(c, uio)
	register int c;
	register struct uio *uio;
{
	register struct iovec *iov;

again:
	if (uio->uio_iovcnt == 0)
		panic("ureadc");
	iov = uio->uio_iov;
	if (iov->iov_len <= 0 || uio->uio_resid <= 0) {
		uio->uio_iovcnt--;
		uio->uio_iov++;
		goto again;
	}
	switch (uio->uio_segflg) {

	case 0:
		if (subyte(iov->iov_base, c) < 0)
			return (EFAULT);
		break;

	case 1:
		*iov->iov_base = c;
		break;

	case 2:
		if (suibyte(iov->iov_base, c) < 0)
			return (EFAULT);
		break;
	}
	iov->iov_base++;
	iov->iov_len--;
	uio->uio_resid--;
	uio->uio_offset++;
	return (0);
}

I 20
#ifdef notdef
E 20
/*
 * Get next character written in by user from uio.
 */
uwritec(uio)
	struct uio *uio;
{
	register struct iovec *iov;
	register int c;

again:
	if (uio->uio_iovcnt <= 0 || uio->uio_resid <= 0)
		panic("uwritec");
	iov = uio->uio_iov;
	if (iov->iov_len == 0) {
		uio->uio_iovcnt--;
		uio->uio_iov++;
		goto again;
	}
	switch (uio->uio_segflg) {

	case 0:
		c = fubyte(iov->iov_base);
		break;

	case 1:
		c = *iov->iov_base & 0377;
		break;

	case 2:
		c = fuibyte(iov->iov_base);
		break;
	}
	if (c < 0)
		return (-1);
	iov->iov_base++;
	iov->iov_len--;
	uio->uio_resid--;
	uio->uio_offset++;
	return (c & 0377);
}
I 20
#endif
E 20

/*
E 36
E 11
 * Ioctl system call
D 5
 * Check legality, execute common code, and switch out to individual
 * device routine.
E 5
I 5
D 36
 * Check legality, execute common code,
 * and switch out to individual device routine.
E 36
E 5
 */
I 95
D 109
struct ioctl_args {
D 101
	int	fdes;
	int	cmd;
	caddr_t	cmarg;
E 101
I 101
	int	fd;
	int	com;
	caddr_t	data;
E 101
};
E 109
E 95
D 76
ioctl()
{
	register struct file *fp;
D 5
	register struct inode *ip;
	register struct a {
E 5
I 5
	struct a {
E 76
I 76
/* ARGSUSED */
I 109
int
E 109
ioctl(p, uap, retval)
	struct proc *p;
D 95
	register struct args {
E 76
E 5
		int	fdes;
		int	cmd;
		caddr_t	cmarg;
D 69
	} *uap;
E 69
I 69
D 76
	} *uap = (struct a *)u.u_ap;
E 76
I 76
	} *uap;
E 95
I 95
D 109
	register struct ioctl_args *uap;
E 95
	int *retval;
E 109
I 109
	register struct ioctl_args /* {
		syscallarg(int) fd;
		syscallarg(u_long) com;
		syscallarg(caddr_t) data;
	} */ *uap;
	register_t *retval;
E 109
{
	register struct file *fp;
I 84
D 102
	register struct filedesc *fdp = p->p_fd;
E 102
I 102
	register struct filedesc *fdp;
E 102
E 84
E 76
E 69
D 5
	register dev_t dev;
	register fmt;
E 5
I 5
D 11
	register int com, size;
E 11
I 11
D 73
	register int com;
E 73
I 73
D 109
	register int com, error;
E 109
I 109
	register u_long com;
	register int error;
E 109
E 73
	register u_int size;
E 11
D 61
	char data[IOCPARM_MASK+1];
E 61
I 61
D 63
	struct buf *bp = 0;
E 63
I 63
D 102
	caddr_t memp = 0;
E 102
I 102
	caddr_t data, memp;
	int tmp;
E 102
E 63
#define STK_PARAMS	128
D 64
	char buf[STK_PARAMS];
	caddr_t data = buf;
E 64
I 64
	char stkbuf[STK_PARAMS];
D 102
	caddr_t data = stkbuf;
I 87
	int tmp;
E 102
E 87
E 64
E 61
E 5

I 102
	fdp = p->p_fd;
E 102
D 69
	uap = (struct a *)u.u_ap;
D 46
	if ((fp = getf(uap->fdes)) == NULL)
		return;
E 46
I 46
	GETF(fp, uap->fdes);
E 69
I 69
D 84
	if ((unsigned)uap->fdes >= NOFILE ||
	    (fp = u.u_ofile[uap->fdes]) == NULL)
E 84
I 84
D 85
	if ((unsigned)uap->fdes >= fdp->fd_maxfiles ||
E 85
I 85
D 101
	if ((unsigned)uap->fdes >= fdp->fd_nfiles ||
E 85
D 86
	    (fp = OFILE(fdp, uap->fdes)) == NULL)
E 86
I 86
	    (fp = fdp->fd_ofiles[uap->fdes]) == NULL)
E 101
I 101
D 109
	if ((u_int)uap->fd >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[uap->fd]) == NULL)
E 109
I 109
	if ((u_int)SCARG(uap, fd) >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[SCARG(uap, fd)]) == NULL)
E 109
E 101
E 86
E 84
D 80
		RETURN (EBADF);
E 80
I 80
		return (EBADF);
E 80
E 69
E 46
D 73
	if ((fp->f_flag & (FREAD|FWRITE)) == 0) {
		u.u_error = EBADF;
		return;
	}
E 73
I 73
D 102
	if ((fp->f_flag & (FREAD|FWRITE)) == 0)
E 102
I 102

	if ((fp->f_flag & (FREAD | FWRITE)) == 0)
E 102
D 80
		RETURN (EBADF);
E 80
I 80
		return (EBADF);
E 80
E 73
D 5
	if (uap->cmd==FIOCLEX) {
E 5
I 5
D 101
	com = uap->cmd;
E 101
I 101
D 102
	com = uap->com;
E 102
E 101

D 6
#ifndef ONLYNEWIOCTLS
E 6
I 6
D 36
#ifndef NOCOMPAT
E 36
I 36
D 42
#if defined(vax) && !defined(NOCOMPAT)
E 42
I 42
D 67
#if defined(vax) && defined(COMPAT)
E 42
E 36
E 6
	/*
	 * Map old style ioctl's into new for the
	 * sake of backwards compatibility (sigh).
	 */
	if ((com&~0xffff) == 0) {
		com = mapioctl(com);
		if (com == 0) {
			u.u_error = EINVAL;
			return;
		}
	}
#endif
E 67
D 102
	if (com == FIOCLEX) {
E 102
I 102
D 109
	switch (com = uap->com) {
E 109
I 109
	switch (com = SCARG(uap, com)) {
E 109
	case FIONCLEX:
D 109
		fdp->fd_ofileflags[uap->fd] &= ~UF_EXCLOSE;
E 109
I 109
		fdp->fd_ofileflags[SCARG(uap, fd)] &= ~UF_EXCLOSE;
E 109
		return (0);
	case FIOCLEX:
E 102
E 5
D 25
		u.u_pofile[uap->fdes] |= EXCLOSE;
E 25
I 25
D 84
		u.u_pofile[uap->fdes] |= UF_EXCLOSE;
E 84
I 84
D 86
		OFILEFLAGS(fdp, uap->fdes) |= UF_EXCLOSE;
E 86
I 86
D 101
		fdp->fd_ofileflags[uap->fdes] |= UF_EXCLOSE;
E 101
I 101
D 109
		fdp->fd_ofileflags[uap->fd] |= UF_EXCLOSE;
E 109
I 109
		fdp->fd_ofileflags[SCARG(uap, fd)] |= UF_EXCLOSE;
E 109
E 101
E 86
E 84
E 25
D 78
		return;
E 78
I 78
D 80
		RETURN (0);
E 80
I 80
		return (0);
E 80
E 78
	}
D 5
	if (uap->cmd==FIONCLEX) {
E 5
I 5
D 102
	if (com == FIONCLEX) {
E 5
D 25
		u.u_pofile[uap->fdes] &= ~EXCLOSE;
E 25
I 25
D 84
		u.u_pofile[uap->fdes] &= ~UF_EXCLOSE;
E 84
I 84
D 86
		OFILEFLAGS(fdp, uap->fdes) &= ~UF_EXCLOSE;
E 86
I 86
D 101
		fdp->fd_ofileflags[uap->fdes] &= ~UF_EXCLOSE;
E 101
I 101
		fdp->fd_ofileflags[uap->fd] &= ~UF_EXCLOSE;
E 101
E 86
E 84
E 25
D 73
		return;
E 73
I 73
D 80
		RETURN (0);
E 80
I 80
		return (0);
E 80
E 73
	}
E 102
D 3
	if (fp->f_flag & FSOCKET) {
E 3
I 3
D 5
	if (fp->f_type == DTYPE_SOCKET) {
E 3
		soioctl(fp->f_socket, uap->cmd, uap->cmarg);
E 5
I 5

	/*
D 102
	 * Interpret high order word to find
	 * amount of data to be copied to/from the
	 * user's address space.
E 102
I 102
	 * Interpret high order word to find amount of data to be
	 * copied to/from the user's address space.
E 102
D 11
	 * (this'll have to change if we have in+out ioctls)
E 11
	 */
D 61
	size = (com &~ (IOC_INOUT|IOC_VOID)) >> 16;
	if (size > sizeof (data)) {
E 61
I 61
	size = IOCPARM_LEN(com);
D 73
	if (size > IOCPARM_MAX) {
E 61
D 68
		u.u_error = EFAULT;
E 68
I 68
		u.u_error = ENOTTY;
E 68
E 5
		return;
	}
E 73
I 73
	if (size > IOCPARM_MAX)
D 80
		RETURN (ENOTTY);
E 80
I 80
		return (ENOTTY);
I 102
	memp = NULL;
E 102
E 80
E 73
I 61
D 64
	if (size > sizeof (buf)) {
E 64
I 64
	if (size > sizeof (stkbuf)) {
E 64
D 63
		bp = geteblk(IOCPARM_MAX);		/* XXX */
		data = bp->b_un.b_addr;
E 63
I 63
D 66
		memp = (caddr_t)malloc(IOCPARM_MAX, M_IOCTLOPS, M_WAITOK);
E 66
I 66
D 68
		memp = (caddr_t)malloc((u_long)IOCPARM_MAX, M_IOCTLOPS,
E 68
I 68
D 77
		memp = (caddr_t)malloc((u_long)IOCPARM_LEN(com), M_IOCTLOPS,
E 68
		    M_WAITOK);
E 77
I 77
		memp = (caddr_t)malloc((u_long)size, M_IOCTLOPS, M_WAITOK);
E 77
E 66
		data = memp;
E 63
D 102
	}
E 102
I 102
	} else
		data = stkbuf;
E 102
E 61
D 5
	ip = fp->f_inode;
	fmt = ip->i_mode & IFMT;
	if (fmt != IFCHR) {
		if (uap->cmd==FIONREAD && (fmt == IFREG || fmt == IFDIR)) {
			off_t nread = ip->i_size - fp->f_offset;
E 5
I 5
D 6
	if ((com&IOC_IN) && size) {
E 6
I 6
D 30
	if (com&IOC_IN && size) {
E 6
D 11
		if (copyin(uap->cmarg, (caddr_t)data, size)) {
E 11
I 11
D 29
		if (copyin(uap->cmarg, (caddr_t)data, (u_int)size)) {
E 11
			u.u_error = EFAULT;
E 29
I 29
		u.u_error = copyin(uap->cmarg, (caddr_t)data, (u_int)size);
		if (u.u_error)
E 29
			return;
D 29
		}
E 29
	} else
		*(caddr_t *)data = uap->cmarg;
	/*
	 * Zero the buffer on the stack so the user
	 * always gets back something deterministic.
	 */
	if ((com&IOC_OUT) && size)
E 30
I 30
	if (com&IOC_IN) {
		if (size) {
D 68
			u.u_error =
D 61
			    copyin(uap->cmarg, (caddr_t)data, (u_int)size);
E 61
I 61
			    copyin(uap->cmarg, data, (u_int)size);
E 68
I 68
D 73
			u.u_error = copyin(uap->cmarg, data, (u_int)size);
E 68
E 61
D 63
			if (u.u_error)
E 63
I 63
			if (u.u_error) {
E 73
I 73
D 101
			error = copyin(uap->cmarg, data, (u_int)size);
E 101
I 101
D 109
			error = copyin(uap->data, data, (u_int)size);
E 109
I 109
			error = copyin(SCARG(uap, data), data, (u_int)size);
E 109
E 101
			if (error) {
E 73
				if (memp)
					free(memp, M_IOCTLOPS);
E 63
D 73
				return;
E 73
I 73
D 80
				RETURN (error);
E 80
I 80
				return (error);
E 80
E 73
I 63
			}
E 63
		} else
D 101
			*(caddr_t *)data = uap->cmarg;
E 101
I 101
D 109
			*(caddr_t *)data = uap->data;
E 109
I 109
			*(caddr_t *)data = SCARG(uap, data);
E 109
E 101
	} else if ((com&IOC_OUT) && size)
		/*
D 68
		 * Zero the buffer on the stack so the user
		 * always gets back something deterministic.
E 68
I 68
		 * Zero the buffer so the user always
		 * gets back something deterministic.
E 68
		 */
E 30
D 61
		bzero((caddr_t)data, size);
E 61
I 61
		bzero(data, size);
E 61
I 32
	else if (com&IOC_VOID)
D 101
		*(caddr_t *)data = uap->cmarg;
E 101
I 101
D 109
		*(caddr_t *)data = uap->data;
E 109
I 109
		*(caddr_t *)data = SCARG(uap, data);
E 109
E 101
E 32
E 5

D 5
			if (copyout((caddr_t)&nread, uap->cmarg, sizeof(off_t)))
				u.u_error = EFAULT;
		} else if (uap->cmd == FIONBIO || uap->cmd == FIOASYNC)
E 5
I 5
D 36
	if (fp->f_type == DTYPE_SOCKET)
D 17
		soioctl(fp->f_socket, com, data);
E 17
I 17
		u.u_error = soioctl(fp->f_socket, com, data);
E 17
	else {
		register struct inode *ip = fp->f_inode;
		int fmt = ip->i_mode & IFMT;
		dev_t dev;
E 36
I 36
	switch (com) {
E 36

D 36
		if (fmt != IFCHR) {
			if (com == FIONREAD && (fmt == IFREG || fmt == IFDIR)) {
				*(off_t *)data = ip->i_size - fp->f_offset;
				goto returndata;
			}
			if (com != FIONBIO && com != FIOASYNC)
				u.u_error = ENOTTY;
E 5
			return;
D 5
		else
			u.u_error = ENOTTY;
		return;
E 5
I 5
		}
		dev = ip->i_rdev;
		u.u_r.r_val1 = 0;
D 14
		if ((u.u_procp->p_flag&SNUSIG) && setjmp(u.u_qsav)) {
E 14
I 14
		if ((u.u_procp->p_flag&SNUSIG) && setjmp(&u.u_qsave)) {
E 14
			u.u_eosys = RESTARTSYS;
			return;
		}
D 17
		(*cdevsw[major(dev)].d_ioctl)(dev, com, data, 0);
E 17
I 17
D 33
		u.u_error = (*cdevsw[major(dev)].d_ioctl)(dev, com, data, 0);
E 33
I 33
D 34
		u.u_error = (*cdevsw[major(dev)].d_ioctl)(dev, com, data, 
								fp->f_flag);
E 34
I 34
		u.u_error =
		   (*cdevsw[major(dev)].d_ioctl)(dev, com, data, fp->f_flag);
E 34
E 33
E 17
E 5
	}
E 36
I 36
	case FIONBIO:
D 73
		u.u_error = fset(fp, FNDELAY, *(int *)data);
E 73
I 73
D 87
		error = fset(fp, FNDELAY, *(int *)data);
E 87
I 87
		if (tmp = *(int *)data)
D 89
			fp->f_flag |= FNDELAY;
E 89
I 89
			fp->f_flag |= FNONBLOCK;
E 89
		else
D 89
			fp->f_flag &= ~FNDELAY;
E 89
I 89
			fp->f_flag &= ~FNONBLOCK;
E 89
		error = (*fp->f_ops->fo_ioctl)(fp, FIONBIO, (caddr_t)&tmp, p);
E 87
E 73
D 61
		return;
E 61
I 61
		break;
E 61
E 36
D 5
	dev = ip->i_rdev;
	u.u_r.r_val1 = 0;
	if ((u.u_procp->p_flag&SNUSIG) && setjmp(u.u_qsav)) {
		u.u_eosys = RESTARTSYS;
		return;
	}
	(*cdevsw[major(dev)].d_ioctl)(dev, uap->cmd, uap->cmarg, 0);
E 5
I 5

D 36
returndata:
E 36
I 36
	case FIOASYNC:
D 73
		u.u_error = fset(fp, FASYNC, *(int *)data);
E 73
I 73
D 87
		error = fset(fp, FASYNC, *(int *)data);
E 87
I 87
		if (tmp = *(int *)data)
			fp->f_flag |= FASYNC;
		else
			fp->f_flag &= ~FASYNC;
		error = (*fp->f_ops->fo_ioctl)(fp, FIOASYNC, (caddr_t)&tmp, p);
E 87
E 73
D 61
		return;
E 61
I 61
		break;
E 61

	case FIOSETOWN:
D 73
		u.u_error = fsetown(fp, *(int *)data);
E 73
I 73
D 87
		error = fsetown(fp, *(int *)data);
E 87
I 87
		tmp = *(int *)data;
		if (fp->f_type == DTYPE_SOCKET) {
			((struct socket *)fp->f_data)->so_pgid = tmp;
			error = 0;
			break;
		}
		if (tmp <= 0) {
			tmp = -tmp;
		} else {
			struct proc *p1 = pfind(tmp);
			if (p1 == 0) {
				error = ESRCH;
				break;
			}
			tmp = p1->p_pgrp->pg_id;
		}
		error = (*fp->f_ops->fo_ioctl)
D 109
			(fp, (int)TIOCSPGRP, (caddr_t)&tmp, p);
E 109
I 109
			(fp, TIOCSPGRP, (caddr_t)&tmp, p);
E 109
E 87
E 73
D 61
		return;
E 61
I 61
		break;
E 61

	case FIOGETOWN:
D 73
		u.u_error = fgetown(fp, (int *)data);
E 73
I 73
D 87
		error = fgetown(fp, (int *)data);
E 87
I 87
		if (fp->f_type == DTYPE_SOCKET) {
			error = 0;
			*(int *)data = ((struct socket *)fp->f_data)->so_pgid;
			break;
		}
D 109
		error = (*fp->f_ops->fo_ioctl)(fp, (int)TIOCGPGRP, data, p);
E 109
I 109
		error = (*fp->f_ops->fo_ioctl)(fp, TIOCGPGRP, data, p);
E 109
		*(int *)data = -*(int *)data;
E 87
E 73
D 61
		return;
E 61
I 61
		break;
I 87

E 87
	default:
D 73
		if (setjmp(&u.u_qsave))
			u.u_error = EINTR;
		else
			u.u_error = (*fp->f_ops->fo_ioctl)(fp, com, data);
E 73
I 73
D 85
		error = (*fp->f_ops->fo_ioctl)(fp, com, data);
E 85
I 85
		error = (*fp->f_ops->fo_ioctl)(fp, com, data, p);
E 85
E 73
		/*
		 * Copy any data to user, size was
		 * already set and checked above.
		 */
D 73
		if (u.u_error == 0 && (com&IOC_OUT) && size)
			u.u_error = copyout(data, uap->cmarg, (u_int)size);
E 73
I 73
		if (error == 0 && (com&IOC_OUT) && size)
D 101
			error = copyout(data, uap->cmarg, (u_int)size);
E 101
I 101
D 109
			error = copyout(data, uap->data, (u_int)size);
E 109
I 109
			error = copyout(data, SCARG(uap, data), (u_int)size);
E 109
E 101
E 73
		break;
E 61
	}
D 61
	u.u_error = (*fp->f_ops->fo_ioctl)(fp, com, data);
E 36
	/*
	 * Copy any data to user, size was
	 * already set and checked above.
	 */
D 6
	if ((com&IOC_OUT) && size && copyout(data, uap->cmarg, size))
		u.u_error = EFAULT;
E 6
I 6
D 11
	if (u.u_error == 0 && com&IOC_OUT)
		if (size && copyout(data, uap->cmarg, size))
E 11
I 11
D 29
	if (u.u_error == 0 && (com&IOC_OUT))
		if (size && copyout(data, uap->cmarg, (u_int)size))
E 11
			u.u_error = EFAULT;
E 29
I 29
	if (u.u_error == 0 && (com&IOC_OUT) && size)
		u.u_error = copyout(data, uap->cmarg, (u_int)size);
E 61
I 61
D 63
	if (bp)
		brelse(bp);
E 63
I 63
	if (memp)
		free(memp, M_IOCTLOPS);
I 73
D 80
	RETURN (error);
E 80
I 80
	return (error);
E 80
E 73
E 63
E 61
E 29
E 6
E 5
}

I 36
D 73
int	unselect();
E 73
D 88
int	nselcoll;
E 88
I 88
int	selwait, nselcoll;
E 88
I 49

E 49
E 36
/*
I 49
D 55
 * Select uses bit masks of file descriptors in ints.
 * These macros manipulate such bit fields (the filesystem macros use chars).
 */
#define NBI		(sizeof(int) * NBBY)		/* bits per int */
#define	NI		howmany(NOFILE, NBI)
#define	tbit(p, n)	((p)[(n)/NBI] & (1 << ((n) % NBI)))
#define	sbit(p, n)	((p)[(n)/NBI] |= (1 << ((n) % NBI)))
#define	cbit(p, n)	((p)[(n)/NBI] &= ~(1 << ((n) % NBI)))

/*
E 55
E 49
D 36
 * Do nothing specific version of line
 * discipline specific ioctl command.
E 36
I 36
 * Select system call.
E 36
 */
I 95
D 109
struct select_args {
D 99
	int	nd;
E 99
I 99
	u_int	nd;
E 99
	fd_set	*in, *ou, *ex;
	struct	timeval *tv;
};
I 108

E 109
I 109
int
E 109
E 108
E 95
I 36
D 76
select()
{
	register struct uap  {
E 76
I 76
select(p, uap, retval)
	register struct proc *p;
D 95
	register struct args {
E 76
		int	nd;
D 49
		long	*in, *ou, *ex;
E 49
I 49
D 55
		int	*in, *ou, *ex;
E 55
I 55
		fd_set	*in, *ou, *ex;
E 55
E 49
		struct	timeval *tv;
D 76
	} *uap = (struct uap *)u.u_ap;
E 76
I 76
	} *uap;
E 95
I 95
D 109
	register struct select_args *uap;
E 95
	int *retval;
E 109
I 109
	register struct select_args /* {
		syscallarg(u_int) nd;
		syscallarg(fd_set *) in;
		syscallarg(fd_set *) ou;
		syscallarg(fd_set *) ex;
		syscallarg(struct timeval *) tv;
	} */ *uap;
	register_t *retval;
E 109
{
E 76
D 49
	int ibits[3], obits[3];
E 49
I 49
D 55
	int ibits[3][NI], obits[3][NI];
E 55
I 55
	fd_set ibits[3], obits[3];
E 55
E 49
	struct timeval atv;
D 40
	int s, ncoll;
E 40
I 40
D 49
	int s, ncoll, mask;
E 49
I 49
D 73
	int s, ncoll, ni;
E 49
E 40
	label_t lqsave;
E 73
I 73
D 99
	int s, ncoll, ni, error = 0, timo;
E 99
I 99
D 107
	int s, ncoll, error = 0, timo;
E 107
I 107
D 108
	int s, ncoll, error = 0, timo, doblock;
E 108
I 108
	int s, ncoll, error, timo = 0;
E 108
E 107
	u_int ni;
E 99
E 73

D 49
	obits[0] = obits[1] = obits[2] = 0;
E 49
I 49
D 57
	bzero(ibits, sizeof(ibits));
	bzero(obits, sizeof(obits));
E 57
I 57
	bzero((caddr_t)ibits, sizeof(ibits));
	bzero((caddr_t)obits, sizeof(obits));
I 99
D 109
	if (uap->nd > FD_SETSIZE)
E 109
I 109
	if (SCARG(uap, nd) > FD_SETSIZE)
E 109
		return (EINVAL);
E 99
E 57
E 49
D 84
	if (uap->nd > NOFILE)
		uap->nd = NOFILE;	/* forgiving, if slightly wrong */
E 84
I 84
D 85
	if (uap->nd > p->p_fd->fd_maxfiles)
		uap->nd = p->p_fd->fd_maxfiles;	/* forgiving; slightly wrong */
E 85
I 85
D 109
	if (uap->nd > p->p_fd->fd_nfiles)
		uap->nd = p->p_fd->fd_nfiles;	/* forgiving; slightly wrong */
E 85
E 84
I 40
D 49
	mask = (1 << uap->nd) - 1;
E 49
I 49
D 55
	ni = howmany(uap->nd, NBI);
E 55
I 55
D 99
	ni = howmany(uap->nd, NFDBITS);
E 99
I 99
	ni = howmany(uap->nd, NFDBITS) * sizeof(fd_mask);
E 109
I 109
	if (SCARG(uap, nd) > p->p_fd->fd_nfiles) {
		/* forgiving; slightly wrong */
		SCARG(uap, nd) = p->p_fd->fd_nfiles;
	}
	ni = howmany(SCARG(uap, nd), NFDBITS) * sizeof(fd_mask);
E 109
E 99
E 55
E 49
E 40

#define	getbits(name, x) \
D 99
	if (uap->name) { \
D 49
		u.u_error = copyin((caddr_t)uap->name, (caddr_t)&ibits[x], \
		    sizeof (ibits[x])); \
E 49
I 49
D 55
		u.u_error = copyin((caddr_t)uap->name, (caddr_t)ibits[x], \
		    ni * sizeof(int)); \
E 55
I 55
D 73
		u.u_error = copyin((caddr_t)uap->name, (caddr_t)&ibits[x], \
E 73
I 73
		error = copyin((caddr_t)uap->name, (caddr_t)&ibits[x], \
E 73
D 57
		    ni * sizeof(fd_mask)); \
E 57
I 57
		    (unsigned)(ni * sizeof(fd_mask))); \
E 57
E 55
E 49
D 73
		if (u.u_error) \
E 73
I 73
		if (error) \
E 73
			goto done; \
I 40
D 49
		ibits[x] &= mask; \
E 40
	} else \
		ibits[x] = 0;
E 49
I 49
	}
E 99
I 99
D 109
	if (uap->name && \
	    (error = copyin((caddr_t)uap->name, (caddr_t)&ibits[x], ni))) \
E 109
I 109
	if (SCARG(uap, name) && (error = copyin((caddr_t)SCARG(uap, name), \
	    (caddr_t)&ibits[x], ni))) \
E 109
		goto done;
E 99
E 49
	getbits(in, 0);
	getbits(ou, 1);
	getbits(ex, 2);
#undef	getbits

D 109
	if (uap->tv) {
D 73
		u.u_error = copyin((caddr_t)uap->tv, (caddr_t)&atv,
E 73
I 73
		error = copyin((caddr_t)uap->tv, (caddr_t)&atv,
E 109
I 109
	if (SCARG(uap, tv)) {
		error = copyin((caddr_t)SCARG(uap, tv), (caddr_t)&atv,
E 109
E 73
			sizeof (atv));
D 73
		if (u.u_error)
E 73
I 73
		if (error)
E 73
			goto done;
		if (itimerfix(&atv)) {
D 73
			u.u_error = EINVAL;
E 73
I 73
			error = EINVAL;
E 73
			goto done;
		}
D 50
		s = spl7(); timevaladd(&atv, &time); splx(s);
E 50
I 50
D 93
		s = splhigh(); timevaladd(&atv, &time); splx(s);
E 93
I 93
D 94
		s = splhigh();
		timevaladd(&atv, &time);
E 94
I 94
D 107
		s = splclock();
		timevaladd(&atv, (struct timeval *)&time);
E 94
E 93
E 50
D 73
	}
E 73
I 73
		timo = hzto(&atv);
E 107
I 97
D 108
		/*
D 107
		 * Avoid inadvertently sleeping forever.
E 107
I 107
		 * Don't let a short time get rounded down to zero
		 * and cause us to sleep forever, but exactly zero
		 * means "do not block".
E 107
		 */
D 107
		if (timo == 0)
			timo = 1;
E 107
I 107
		doblock = (atv.tv_usec || atv.tv_sec);
E 108
		s = splclock();
		timevaladd(&atv, (struct timeval *)&time);
E 107
E 97
I 93
		splx(s);
E 93
D 108
	} else
		timo = 0;
E 108
I 108
	}
E 108
E 73
retry:
	ncoll = nselcoll;
D 76
	u.u_procp->p_flag |= SSEL;
D 49
	u.u_r.r_val1 = selscan(ibits, obits);
E 49
I 49
D 73
	u.u_r.r_val1 = selscan(ibits, obits, uap->nd);
E 49
	if (u.u_error || u.u_r.r_val1)
E 73
I 73
	u.u_r.r_val1 = selscan(ibits, obits, uap->nd, &error);
E 76
I 76
D 103
	p->p_flag |= SSEL;
E 103
I 103
	p->p_flag |= P_SELECT;
E 103
D 84
	error = selscan(ibits, obits, uap->nd, retval);
E 84
I 84
D 85
	error = selscan(p->p_fd, ibits, obits, uap->nd, retval);
E 85
I 85
D 109
	error = selscan(p, ibits, obits, uap->nd, retval);
E 109
I 109
	error = selscan(p, ibits, obits, SCARG(uap, nd), retval);
E 109
E 85
E 84
E 76
D 77
	if (error == 0)
		error = u.u_error;		/* XXX */
E 77
D 76
	if (error || u.u_r.r_val1)
E 76
I 76
	if (error || *retval)
E 76
E 73
		goto done;
D 50
	s = spl6();
E 50
I 50
	s = splhigh();
E 50
D 38
	if (uap->tv && timercmp(&time, &atv, >=)) {
E 38
I 38
D 107
	/* this should be timercmp(&time, &atv, >=) */
	if (uap->tv && (time.tv_sec > atv.tv_sec ||
	    time.tv_sec == atv.tv_sec && time.tv_usec >= atv.tv_usec)) {
E 38
		splx(s);
		goto done;
E 107
I 107
D 109
	if (uap->tv) {
E 109
I 109
	if (SCARG(uap, tv)) {
E 109
		if (timercmp(&time, &atv, >=)) {
			splx(s);
			goto done;
		}
D 108
		timo = hzto(&atv);
E 108
		/*
D 108
		 * Avoid inadvertently sleeping forever.
E 108
I 108
		 * If poll wait was tiny, this could be zero; we will
		 * have to round it up to avoid sleeping forever.  If
		 * we retry below, the timercmp above will get us out.
		 * Note that if wait was 0, the timercmp will prevent
		 * us from getting here the first time.
E 108
		 */
D 108
		if (doblock && timo == 0)
E 108
I 108
		timo = hzto(&atv);
		if (timo == 0)
E 108
			timo = 1;
E 107
	}
D 76
	if ((u.u_procp->p_flag & SSEL) == 0 || nselcoll != ncoll) {
E 76
I 76
D 103
	if ((p->p_flag & SSEL) == 0 || nselcoll != ncoll) {
E 103
I 103
	if ((p->p_flag & P_SELECT) == 0 || nselcoll != ncoll) {
E 103
E 76
D 65
		u.u_procp->p_flag &= ~SSEL;
E 65
		splx(s);
		goto retry;
	}
D 76
	u.u_procp->p_flag &= ~SSEL;
E 76
I 76
D 103
	p->p_flag &= ~SSEL;
E 103
I 103
	p->p_flag &= ~P_SELECT;
I 107
D 108
	doblock = 0;
E 108
E 107
E 103
E 76
D 73
	if (uap->tv) {
		lqsave = u.u_qsave;
		if (setjmp(&u.u_qsave)) {
			untimeout(unselect, (caddr_t)u.u_procp);
			u.u_error = EINTR;
			splx(s);
			goto done;
		}
		timeout(unselect, (caddr_t)u.u_procp, hzto(&atv));
	}
D 72
	sleep((caddr_t)&selwait, PZERO+1);
E 72
I 72
	tsleep((caddr_t)&selwait, PZERO+1, SLP_SELECT, 0);
E 72
	if (uap->tv) {
		u.u_qsave = lqsave;
		untimeout(unselect, (caddr_t)u.u_procp);
	}
E 73
I 73
	error = tsleep((caddr_t)&selwait, PSOCK | PCATCH, "select", timo);
E 73
	splx(s);
D 73
	goto retry;
E 73
I 73
	if (error == 0)
		goto retry;
E 73
done:
I 65
D 76
	u.u_procp->p_flag &= ~SSEL;
E 76
I 76
D 103
	p->p_flag &= ~SSEL;
E 103
I 103
	p->p_flag &= ~P_SELECT;
E 103
E 76
I 73
	/* select is not restarted after signals... */
	if (error == ERESTART)
		error = EINTR;
	if (error == EWOULDBLOCK)
		error = 0;
E 73
E 65
#define	putbits(name, x) \
D 99
	if (uap->name) { \
D 49
		int error = copyout((caddr_t)&obits[x], (caddr_t)uap->name, \
		    sizeof (obits[x])); \
E 49
I 49
D 55
		int error = copyout((caddr_t)obits[x], (caddr_t)uap->name, \
		    ni * sizeof(int)); \
E 55
I 55
D 73
		int error = copyout((caddr_t)&obits[x], (caddr_t)uap->name, \
E 73
I 73
		int error2 = copyout((caddr_t)&obits[x], (caddr_t)uap->name, \
E 73
D 57
		    ni * sizeof(fd_mask)); \
E 57
I 57
		    (unsigned)(ni * sizeof(fd_mask))); \
E 57
E 55
E 49
D 73
		if (error) \
			u.u_error = error; \
E 73
I 73
		if (error2) \
			error = error2; \
E 73
	}
E 99
I 99
D 109
	if (uap->name && \
	    (error2 = copyout((caddr_t)&obits[x], (caddr_t)uap->name, ni))) \
E 109
I 109
	if (SCARG(uap, name) && (error2 = copyout((caddr_t)&obits[x], \
	    (caddr_t)SCARG(uap, name), ni))) \
E 109
		error = error2;
E 99
D 53
	putbits(in, 0);
	putbits(ou, 1);
	putbits(ex, 2);
E 53
I 53
D 56
	if (u.u_error != EINTR) {
E 56
I 56
D 73
	if (u.u_error == 0) {
E 73
I 73
	if (error == 0) {
I 99
		int error2;

E 99
E 73
E 56
		putbits(in, 0);
		putbits(ou, 1);
		putbits(ex, 2);
E 53
#undef putbits
I 53
	}
I 73
D 80
	RETURN (error);
E 80
I 80
	return (error);
E 80
E 73
E 53
}

I 109
int
E 109
D 73
unselect(p)
	register struct proc *p;
{
D 50
	register int s = spl6();
E 50
I 50
	register int s = splhigh();
E 50

	switch (p->p_stat) {

	case SSLEEP:
		setrun(p);
		break;

	case SSTOP:
		unsleep(p);
		break;
	}
	splx(s);
}

D 49
selscan(ibits, obits)
	int *ibits, *obits;
E 49
I 49
selscan(ibits, obits, nfd)
E 73
I 73
D 76
selscan(ibits, obits, nfd, errp)
E 76
I 76
D 84
selscan(ibits, obits, nfd, retval)
E 84
I 84
D 85
selscan(fdp, ibits, obits, nfd, retval)
	register struct filedesc *fdp;
E 85
I 85
selscan(p, ibits, obits, nfd, retval)
	struct proc *p;
E 85
E 84
E 76
E 73
D 55
	int (*ibits)[NI], (*obits)[NI];
E 55
I 55
	fd_set *ibits, *obits;
I 73
D 76
	int nfd, *errp;
E 76
I 76
D 109
	int nfd, *retval;
E 109
I 109
	int nfd;
	register_t *retval;
E 109
E 76
E 73
E 55
E 49
{
I 85
	register struct filedesc *fdp = p->p_fd;
E 85
D 49
	register int which, bits, i;
E 49
I 49
D 55
	register int which, bits, i, j;
E 55
I 55
D 90
	register int which, i, j;
E 90
I 90
	register int msk, i, j, fd;
E 90
	register fd_mask bits;
E 55
E 49
D 90
	int flag;
E 90
	struct file *fp;
D 76
	int n = 0;
E 76
I 76
D 90
	int error = 0, n = 0;
E 90
I 90
	int n = 0;
	static int flag[3] = { FREAD, FWRITE, 0 };
E 90
E 76

D 90
	for (which = 0; which < 3; which++) {
D 49
		bits = ibits[which];
		obits[which] = 0;
E 49
		switch (which) {

		case 0:
			flag = FREAD; break;

		case 1:
			flag = FWRITE; break;

		case 2:
			flag = 0; break;
		}
E 90
I 90
	for (msk = 0; msk < 3; msk++) {
E 90
D 49
		while (i = ffs(bits)) {
			bits &= ~(1<<(i-1));
			fp = u.u_ofile[i-1];
			if (fp == NULL) {
				u.u_error = EBADF;
				break;
			}
			if ((*fp->f_ops->fo_select)(fp, flag)) {
				obits[which] |= (1<<(i-1));
				n++;
E 49
I 49
D 55
		for (i = 0; i < nfd; i += NBI) {
			bits = ibits[which][i/NBI];
E 55
I 55
		for (i = 0; i < nfd; i += NFDBITS) {
D 90
			bits = ibits[which].fds_bits[i/NFDBITS];
E 55
			while ((j = ffs(bits)) && i + --j < nfd) {
E 90
I 90
			bits = ibits[msk].fds_bits[i/NFDBITS];
			while ((j = ffs(bits)) && (fd = i + --j) < nfd) {
E 90
				bits &= ~(1 << j);
D 84
				fp = u.u_ofile[i + j];
E 84
I 84
D 86
				fp = OFILE(fdp, i + j);
E 86
I 86
D 90
				fp = fdp->fd_ofiles[i + j];
E 86
E 84
				if (fp == NULL) {
D 73
					u.u_error = EBADF;
E 73
I 73
D 76
					*errp = EBADF;
E 76
I 76
					error = EBADF;
E 76
E 73
					break;
				}
D 85
				if ((*fp->f_ops->fo_select)(fp, flag)) {
E 85
I 85
				if ((*fp->f_ops->fo_select)(fp, flag, p)) {
E 85
D 55
					sbit(obits[which], i + j);
E 55
I 55
					FD_SET(i + j, &obits[which]);
E 90
I 90
				fp = fdp->fd_ofiles[fd];
				if (fp == NULL)
					return (EBADF);
				if ((*fp->f_ops->fo_select)(fp, flag[msk], p)) {
					FD_SET(fd, &obits[msk]);
E 90
E 55
					n++;
				}
E 49
			}
		}
	}
D 76
	return (n);
E 76
I 76
	*retval = n;
D 90
	return (error);
E 90
I 90
	return (0);
E 90
E 76
}

E 36
/*ARGSUSED*/
I 109
int
E 109
I 86
D 95
#ifdef __STDC__
seltrue(dev_t dev, int which, struct proc *p)
#else
E 95
E 86
D 5
nullioctl(tp, cmd, addr)
E 5
I 5
D 36
nullioctl(tp, cmd, data, flags)
E 5
	struct tty *tp;
D 5
	caddr_t addr;
E 5
I 5
	char *data;
	int flags;
E 36
I 36
D 85
seltrue(dev, flag)
E 85
I 85
seltrue(dev, flag, p)
E 85
	dev_t dev;
	int flag;
I 85
	struct proc *p;
I 86
D 95
#endif
E 95
E 86
E 85
E 36
E 5
{

I 5
D 36
#ifdef lint
	tp = tp; data = data; flags = flags;
#endif
E 5
D 17
	return (cmd);
E 17
I 17
	return (-1);
E 36
I 36
	return (1);
E 36
E 17
D 11
}

/*
D 10
 * Read the file corresponding to
 * the inode pointed at by the argument.
 * The actual read arguments are found
 * in the variables:
 *	u_base		core address for destination
 *	u_offset	byte offset in file
 *	u_count		number of bytes to read
 *	u_segflg	read to kernel/user/user I
 */
readi(ip)
	register struct inode *ip;
{
	struct buf *bp;
	struct fs *fs;
	dev_t dev;
	daddr_t lbn, bn;
	off_t diff;
	register int on, type;
	register unsigned n;
	int size;
	long bsize;
	extern int mem_no;

	if (u.u_count == 0)
		return;
	dev = (dev_t)ip->i_rdev;
	if (u.u_offset < 0 && ((ip->i_mode&IFMT) != IFCHR ||
	    mem_no != major(dev))) {
		u.u_error = EINVAL;
		return;
	}
	ip->i_flag |= IACC;
	type = ip->i_mode&IFMT;
	if (type == IFCHR) {
I 2
		register c = u.u_count;
E 2
D 8
		(*cdevsw[major(dev)].d_read)(dev);
I 2
		CHARGE(sc_tio * (c - u.u_count));
E 8
I 8
		struct uio auio;
		struct iovec aiov;
		auio.uio_iov = &aiov;
		auio.uio_iovcnt = 1;
		aiov.iov_base = u.u_base;
		aiov.iov_len = u.u_count;
		auio.uio_offset = u.u_offset;
		auio.uio_segflg = u.u_segflg;
		auio.uio_resid = u.u_count;
		(*cdevsw[major(dev)].d_read)(dev, &auio);
		CHARGE(sc_tio * (c - auio.uio_resid));
		u.u_count = auio.uio_resid;
E 8
E 2
		return;
	}
	if (type != IFBLK) {
		dev = ip->i_dev;
		fs = ip->i_fs;
		bsize = fs->fs_bsize;
	} else
		bsize = BLKDEV_IOSIZE;
	do {
		lbn = u.u_offset / bsize;
		on = u.u_offset % bsize;
		n = MIN((unsigned)(bsize - on), u.u_count);
		if (type != IFBLK) {
			diff = ip->i_size - u.u_offset;
			if (diff <= 0)
				return;
			if (diff < n)
				n = diff;
			bn = fsbtodb(fs, bmap(ip, lbn, B_READ));
			if (u.u_error)
				return;
			size = blksize(fs, ip, lbn);
		} else {
			size = bsize;
			bn = lbn * (BLKDEV_IOSIZE/DEV_BSIZE);
			rablock = bn + (BLKDEV_IOSIZE/DEV_BSIZE);
			rasize = bsize;
		}
		if ((long)bn<0) {
			bp = geteblk(size);
			clrbuf(bp);
		} else if (ip->i_lastr + 1 == lbn)
			bp = breada(dev, bn, size, rablock, rasize);
		else
			bp = bread(dev, bn, size);
		ip->i_lastr = lbn;
		n = MIN(n, size - bp->b_resid);
		if (n != 0) {
D 6
#ifdef UNFAST
			iomove(bp->b_un.b_addr + on, n, B_READ);
#else
E 6
			if (u.u_segflg != 1) {
				if (copyout(bp->b_un.b_addr+on, u.u_base, n)) {
					u.u_error = EFAULT;
					goto bad;
				}
			} else
				bcopy(bp->b_un.b_addr + on, u.u_base, n);
			u.u_base += n;
			u.u_offset += n;
			u.u_count -= n;
bad:
			;
D 6
#endif
E 6
		}
		if (n + on == bsize || u.u_offset == ip->i_size)
			bp->b_flags |= B_AGE;
		brelse(bp);
	} while (u.u_error == 0 && u.u_count != 0 && n != 0);
}

/*
E 10
 * Write the file corresponding to
 * the inode pointed at by the argument.
 * The actual write arguments are found
 * in the variables:
 *	u_base		core address for source
 *	u_offset	byte offset in file
 *	u_count		number of bytes to write
 *	u_segflg	write to kernel/user/user I
 */
writei(ip)
	register struct inode *ip;
{
	struct buf *bp;
	register struct fs *fs;
	dev_t dev;
	daddr_t lbn, bn;
	register int on, type;
	register unsigned n;
	long bsize;
	int size, i, count;
	extern int mem_no;

	dev = (dev_t)ip->i_rdev;
	if (u.u_offset < 0 && ((ip->i_mode&IFMT) != IFCHR ||
	    mem_no != major(dev)) ) {
		u.u_error = EINVAL;
		return;
	}
	type = ip->i_mode & IFMT;
	if (type == IFCHR) {
		ip->i_flag |= IUPD|ICHG;
I 2
		CHARGE(sc_tio * u.u_count);
E 2
		(*cdevsw[major(dev)].d_write)(dev);
		return;
	}
	if (u.u_count == 0)
		return;
	if ((ip->i_mode & IFMT) == IFREG &&
	    u.u_offset + u.u_count > u.u_limit[LIM_FSIZE]) {
		psignal(u.u_procp, SIGXFSZ);
		u.u_error = EMFILE;
		return;
	}
	if (type!=IFBLK) {
		dev = ip->i_dev;
		fs = ip->i_fs;
		bsize = fs->fs_bsize;
D 4
	} else {
E 4
I 4
	} else
E 4
		bsize = BLKDEV_IOSIZE;
D 4
	}
E 4
	do {
		lbn = u.u_offset / bsize;
		on = u.u_offset % bsize;
		n = MIN((unsigned)(bsize - on), u.u_count);
		if (type != IFBLK) {
			bn = fsbtodb(fs, bmap(ip, lbn, B_WRITE, (int)(on + n)));
D 4
			if ((long)bn<0)
E 4
I 4
			if (u.u_error || (long)bn<0)
E 4
				return;
			if(u.u_offset + n > ip->i_size &&
			   (type == IFDIR || type == IFREG || type == IFLNK))
				ip->i_size = u.u_offset + n;
			size = blksize(fs, ip, lbn);
		} else {
			size = bsize;
			bn = lbn * (BLKDEV_IOSIZE/DEV_BSIZE);
		}
D 4
		if (bn) {
			count = howmany(size, DEV_BSIZE);
			for (i = 0; i < count; i += CLSIZE) {
				if (mfind(dev, bn + i))
					munhash(dev, bn + i);
			}
		}
		if(n == bsize) 
E 4
I 4
		count = howmany(size, DEV_BSIZE);
		for (i = 0; i < count; i += CLSIZE)
			if (mfind(dev, bn + i))
				munhash(dev, bn + i);
		if (n == bsize) 
E 4
			bp = getblk(dev, bn, size);
		else
			bp = bread(dev, bn, size);
D 6
#ifdef UNFAST
		iomove(bp->b_un.b_addr + on, n, B_WRITE);
#else
E 6
		if (u.u_segflg != 1) {
			if (copyin(u.u_base, bp->b_un.b_addr + on, n)) {
				u.u_error = EFAULT;
				goto bad;
			}
		} else
			bcopy(u.u_base, bp->b_un.b_addr + on, n);
		u.u_base += n;
		u.u_offset += n;
		u.u_count -= n;
bad:
		;
D 6
#endif
E 6
		if (u.u_error != 0)
			brelse(bp);
		else {
			if ((ip->i_mode&IFMT) == IFDIR)
				/*
				 * Writing to clear a directory entry.
				 * Must insure the write occurs before
				 * the inode is freed, or may end up
				 * pointing at a new (different) file
				 * if inode is quickly allocated again
				 * and system crashes.
				 */
				bwrite(bp);
			else if (n + on == bsize) {
				bp->b_flags |= B_AGE;
				bawrite(bp);
			} else
				bdwrite(bp);
		}
		ip->i_flag |= IUPD|ICHG;
		if (u.u_ruid != 0)
			ip->i_mode &= ~(ISUID|ISGID);
	} while (u.u_error == 0 && u.u_count != 0);
}

/*
 * Move n bytes at byte location
 * &bp->b_un.b_addr[o] to/from (flag) the
 * user/kernel (u.segflg) area starting at u.base.
 * Update all the arguments by the number
 * of bytes moved.
 */
iomove(cp, n, flag)
	register caddr_t cp;
	register unsigned n;
{
	register int t;

	if (n==0)
		return;
	if (u.u_segflg != 1) {
		if (flag==B_WRITE)
			t = copyin(u.u_base, (caddr_t)cp, n);
		else
			t = copyout((caddr_t)cp, u.u_base, n);
		if (t) {
			u.u_error = EFAULT;
			return;
		}
	} else
		if (flag == B_WRITE)
			bcopy(u.u_base, (caddr_t)cp, n);
		else
			bcopy((caddr_t)cp, u.u_base, n);
	u.u_base += n;
	u.u_offset += n;
	u.u_count -= n;
I 10
}

readip1(ip, base, len, offset, segflg, aresid)
	struct inode *ip;
	caddr_t base;
	int len, offset, segflg;
	int *aresid;
{
	struct uio auio;
	struct iovec aiov;
	int error;

	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	aiov.iov_base = base;
	aiov.iov_len = len;
	auio.uio_resid = len;
	auio.uio_offset = offset;
	auio.uio_segflg = segflg;
	error = readip(ip, &auio);
	if (aresid)
		*aresid = auio.uio_resid;
	else
		if (auio.uio_resid)
			error = EIO;
	return (error);
E 10
I 7
}

readip(ip, uio)
	register struct inode *ip;
	register struct uio *uio;
{
D 9
	register struct iovec *iov = uio->uio_iov;
E 9
I 9
	register struct iovec *iov;
E 9
	struct buf *bp;
	struct fs *fs;
	dev_t dev;
	daddr_t lbn, bn;
	off_t diff;
	register int on, type;
	register unsigned n;
	int size;
	long bsize;
	extern int mem_no;
	int error = 0;

D 9
	uio->uio_resid = 0;
	if (uio->uio_iovcnt == 0)
		return (0);
E 9
	dev = (dev_t)ip->i_rdev;
	if (uio->uio_offset < 0 &&
D 9
	    ((ip->i_mode&IFMT) != IFCHR || mem_no != major(dev))) {
		error = EINVAL;
		goto bad;
	}
E 9
I 9
	    ((ip->i_mode&IFMT) != IFCHR || mem_no != major(dev)))
		return (EINVAL);
E 9
	ip->i_flag |= IACC;
	type = ip->i_mode&IFMT;
	if (type == IFCHR) {
		register c = u.u_count;
D 9
		error = (*cdevsw[major(dev)].d_read)(dev, uio);
		CHARGE(sc_tio * (c - u.u_count));
		return (error);
E 9
I 9
		(*cdevsw[major(dev)].d_read)(dev, uio);
		CHARGE(sc_tio * (c - uio->uio_resid));
		return (u.u_error);
E 9
	}
	if (type != IFBLK) {
		dev = ip->i_dev;
		fs = ip->i_fs;
		bsize = fs->fs_bsize;
	} else
		bsize = BLKDEV_IOSIZE;
nextiov:
	if (uio->uio_iovcnt == 0)
D 9
		goto getresid;
E 9
I 9
		return (0);
	iov = uio->uio_iov;
E 9
	if (iov->iov_len > 0)
	do {
		lbn = uio->uio_offset / bsize;
		on = uio->uio_offset % bsize;
		n = MIN((unsigned)(bsize - on), iov->iov_len);
		if (type != IFBLK) {
			diff = ip->i_size - uio->uio_offset;
			if (diff <= 0)
				return;
			if (diff < n)
				n = diff;
			bn = fsbtodb(fs, bmap(ip, lbn, B_READ));
			if (u.u_error)
D 9
				goto getresid;
E 9
I 9
				return (u.u_error);
E 9
			size = blksize(fs, ip, lbn);
		} else {
			size = bsize;
			bn = lbn * (BLKDEV_IOSIZE/DEV_BSIZE);
			rablock = bn + (BLKDEV_IOSIZE/DEV_BSIZE);
			rasize = bsize;
		}
		if ((long)bn<0) {
			bp = geteblk(size);
			clrbuf(bp);
		} else if (ip->i_lastr + 1 == lbn)
			bp = breada(dev, bn, size, rablock, rasize);
		else
			bp = bread(dev, bn, size);
		ip->i_lastr = lbn;
		n = MIN(n, size - bp->b_resid);
		if (n != 0) {
			if (uio->uio_segflg != 1) {
				if (copyout(bp->b_un.b_addr+on, iov->iov_base, n)) {
D 9
					error = EFAULT;
					goto getresid;
E 9
I 9
					brelse(bp);
					return (EFAULT);
E 9
				}
			} else
				bcopy(bp->b_un.b_addr + on, iov->iov_base, n);
			iov->iov_base += n;
			uio->uio_offset += n;
			iov->iov_len -= n;
D 9
bad:
			;
E 9
I 9
			uio->uio_resid -= n;
E 9
		}
		if (n + on == bsize || uio->uio_offset == ip->i_size)
			bp->b_flags |= B_AGE;
		brelse(bp);
	} while (u.u_error == 0 && iov->iov_len != 0 && n != 0);
D 9
	if (u.u_error == 0 && n > 0) {
		iov++;
E 9
I 9
	if (u.u_error == 0 && iov->iov_len == 0) {
		uio->uio_iov++;
E 9
		uio->uio_iovcnt--;
		goto nextiov;
	}
D 9
getresid:
	while (uio->uio_iovcnt > 0) {
		uio->uio_resid += iov->iov_len;
		iov++;
		uio->uio_iovcnt--;
	}
E 9
	return (error);
I 9
}

uiomove(cp, n, dir, uio)
	register caddr_t cp;
	register unsigned n;
	enum uio_direction dir;
	struct uio *uio;
{
	register struct iovec *iov;
	int bad, cnt;

	if (n == 0)
		return (0);
	if (uio->uio_segflg != 1) {
		if (dir == UIO_READFROM)
#ifdef notdef
			bad = copyuin(uio, (caddr_t)cp, n);
#else
			panic("uiomove");
#endif
		else
			bad = copyuout((caddr_t)cp, n, uio);
		if (bad)
			return (EFAULT);
	} else {
		while (n > 0 && uio->uio_iovcnt) {
			iov = uio->uio_iov;
			cnt = iov->iov_len;
			if (cnt > n)
				cnt = n;
			if (dir == UIO_READFROM)
				bcopy(iov->iov_base, (caddr_t)cp, cnt);
			else
				bcopy((caddr_t)cp, iov->iov_base, cnt);
			iov->iov_base += cnt;
			iov->iov_len -= cnt;
			uio->uio_resid -= cnt;
			n -= cnt;
		}
	}
	return (0);
E 11
E 9
E 7
}
I 13

D 36
ostty()
E 36
I 36
D 91
selwakeup(p, coll)
	register struct proc *p;
	int coll;
E 91
I 91
/*
 * Record a select request.
 */
void
selrecord(selector, sip)
	struct proc *selector;
	struct selinfo *sip;
E 91
E 36
{
I 91
	struct proc *p;
	pid_t mypid;
E 91

I 36
D 91
	if (coll) {
E 91
I 91
	mypid = selector->p_pid;
	if (sip->si_pid == mypid)
		return;
	if (sip->si_pid && (p = pfind(sip->si_pid)) &&
	    p->p_wchan == (caddr_t)&selwait)
		sip->si_flags |= SI_COLL;
	else
		sip->si_pid = mypid;
}

/*
 * Do a wakeup when a selectable event occurs.
 */
void
selwakeup(sip)
	register struct selinfo *sip;
{
	register struct proc *p;
	int s;

	if (sip->si_pid == 0)
		return;
	if (sip->si_flags & SI_COLL) {
E 91
		nselcoll++;
I 91
		sip->si_flags &= ~SI_COLL;
E 91
		wakeup((caddr_t)&selwait);
	}
D 91
	if (p) {
D 50
		int s = spl6();
E 50
I 50
		int s = splhigh();
E 91
I 91
D 92
	if ((p = pfind(sip->si_pid)) == 0) {
		sip->si_pid = 0;
	} else {
E 92
I 92
	p = pfind(sip->si_pid);
	sip->si_pid = 0;
	if (p != NULL) {
E 92
		s = splhigh();
E 91
E 50
D 48
		if (p->p_wchan == (caddr_t)&selwait)
			setrun(p);
		else if (p->p_flag & SSEL)
E 48
I 48
		if (p->p_wchan == (caddr_t)&selwait) {
			if (p->p_stat == SSLEEP)
D 102
				setrun(p);
E 102
I 102
				setrunnable(p);
E 102
			else
				unsleep(p);
D 103
		} else if (p->p_flag & SSEL)
E 48
			p->p_flag &= ~SSEL;
E 103
I 103
		} else if (p->p_flag & P_SELECT)
			p->p_flag &= ~P_SELECT;
E 103
		splx(s);
	}
E 36
}
D 41

D 36
ogtty()
E 36
I 36
fstat()
E 36
{
I 36
	register struct file *fp;
	register struct a {
		int	fdes;
		struct	stat *sb;
	} *uap;
	struct stat ub;
E 36

I 36
	uap = (struct a *)u.u_ap;
	fp = getf(uap->fdes);
	if (fp == 0)
		return;
	u.u_error = (*fp->f_ops->fo_stat)(fp, &ub);
	if (u.u_error == 0)
		u.u_error = copyout(&ub, uap->sb, sizeof (ub));
E 36
}
E 41
E 13
E 1
