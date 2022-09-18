h60723
s 00011/00009/00112
d D 8.4 95/05/14 00:18:14 mckusick 54 53
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK
e
s 00001/00001/00120
d D 8.3 95/01/09 18:22:32 cgd 53 52
c return types, 64-bit changes: ioctl cmd -> u_long, casts, etc.
e
s 00002/00002/00119
d D 8.2 93/09/23 15:36:50 bostic 52 51
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00119
d D 8.1 93/06/10 21:59:30 bostic 51 50
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00119
d D 7.22 93/04/28 20:35:09 mckusick 50 49
c refinement in comment in previous delta from Mike Karels at BSDI
e
s 00010/00000/00111
d D 7.21 93/04/28 15:37:07 mckusick 49 48
c relax restrictions on opening /dev/tty (from Karels at BSDI)
e
s 00008/00008/00103
d D 7.20 92/10/11 10:38:44 bostic 48 47
c make kernel includes standard
e
s 00000/00012/00111
d D 7.19 92/07/03 01:38:21 mckusick 47 46
c delete USES
e
s 00012/00000/00111
d D 7.18 92/05/14 17:34:52 heideman 46 37
c vnode interface conversion
e
s 00012/00000/00111
d R 7.18 92/05/14 15:50:15 heideman 45 37
c vnode interface conversion
e
s 00012/00000/00111
d R 7.18 92/05/14 14:53:44 heideman 44 37
c vnode interface conversion
e
s 00012/00000/00111
d R 7.18 92/05/14 12:58:19 heideman 43 37
c vnode interface conversion
e
s 00012/00000/00111
d R 7.18 92/05/14 11:55:57 heideman 42 37
c vnode interface conversion
e
s 00012/00000/00111
d R 7.18 92/05/14 10:36:00 heideman 41 37
c vnode interface conversion
e
s 00012/00000/00111
d R 7.18 92/05/13 23:15:04 heideman 40 37
c vnode interface conversion
e
s 00012/00000/00111
d R 7.18 92/05/13 19:00:19 heideman 39 37
c vnode interface conversion
e
s 00012/00000/00111
d R 7.18 92/05/13 18:32:21 heideman 38 37
c vnode interface conversion
e
s 00001/00001/00110
d D 7.17 92/02/15 17:32:36 mckusick 37 36
c must include proc before tty.h and socketvar.h
e
s 00002/00000/00109
d D 7.16 92/02/14 17:40:30 torek 36 35
c lint
e
s 00003/00003/00106
d D 7.15 91/05/28 17:39:36 mckusick 35 34
c vnode must now be locked when calling VOP_OPEN
e
s 00005/00004/00104
d D 7.14 91/05/09 21:21:39 bostic 34 33
c new copyright; att/bsd/shared
e
s 00004/00006/00104
d D 7.13 91/05/05 15:51:31 karels 33 32
c proc parameter for read/write now in uio
e
s 00004/00004/00106
d D 7.12 91/04/15 23:45:45 mckusick 32 31
c add proc pointers to appropriate VOP operations
e
s 00020/00018/00090
d D 7.11 91/03/24 15:24:20 karels 31 29
c new device calling conventions, return correct error after revocation
e
s 00009/00009/00099
d R 7.11 91/03/24 15:17:21 karels 30 29
c new device calling conventions
e
s 00014/00013/00094
d D 7.10 91/03/17 15:42:11 karels 29 28
c more-or-less working with new proc & user structs
e
s 00001/00001/00106
d D 7.9 90/06/21 19:08:16 karels 28 27
c select routines don't return errors
e
s 00005/00002/00102
d D 7.8 90/05/01 23:34:13 mckusick 27 26
c must have vnode locked when calling VOP_ACCESS
e
s 00001/00001/00103
d D 7.7 90/02/21 00:08:16 mckusick 26 25
c VOP_SELECT needs file flags
e
s 00012/00006/00092
d D 7.6 89/11/22 21:41:28 mckusick 25 24
c must lock before calling READ/WRITE
e
s 00032/00026/00066
d D 7.5 89/11/20 18:14:16 marc 24 23
c controlling terminal is a vnode
e
s 00000/00001/00092
d D 7.4 89/05/05 00:06:57 mckusick 23 22
c delete unneeded include of dir.h
e
s 00006/00006/00087
d D 7.3 89/05/01 23:05:20 marc 22 21
c /dev/tty takes flag and passes to line discipline, also - 
c naw - thats it
e
s 00008/00002/00085
d D 7.2 88/10/18 15:16:42 marc 21 20
c new terminal driver
e
s 00001/00001/00086
d D 7.1 86/06/05 00:10:57 mckusick 20 19
c 4.3BSD release version
e
s 00007/00001/00080
d D 6.3 85/06/08 14:48:28 mckusick 19 18
c Add copyright
e
s 00009/00009/00072
d D 6.2 84/08/29 20:24:58 bloom 18 17
c Change to includes.  no more ../h
e
s 00000/00000/00081
d D 6.1 83/07/29 06:40:23 sam 17 16
c 4.2 distribution
e
s 00001/00000/00080
d D 4.14 82/12/05 22:01:34 sam 16 15
c include ioctl.h separate from tty.h
e
s 00003/00000/00077
d D 4.13 82/10/17 14:05:55 root 15 14
c fix lint
e
s 00009/00011/00068
d D 4.12 82/10/17 11:30:16 root 14 13
c returns error in open, ioctl
e
s 00006/00010/00073
d D 4.11 82/10/13 22:09:25 root 13 12
c return errors from ioctl routines and internal ldisc routines
e
s 00009/00004/00074
d D 4.10 82/08/22 20:42:29 root 12 11
c uio'd
e
s 00001/00001/00077
d D 4.9 82/03/31 09:08:58 wnj 11 10
c bug fix to syselect found by mosher
e
s 00000/00001/00078
d D 4.8 82/01/24 22:02:06 wnj 10 9
c clean up SDETACH
e
s 00005/00001/00074
d D 4.7 82/01/24 19:46:11 root 9 8
c clear SDETACH when TIOCNOTTY
e
s 00005/00005/00070
d D 4.6 82/01/19 02:01:45 wnj 8 7
c no more SDETACH crap
e
s 00012/00006/00063
d D 4.5 82/01/13 10:32:35 wnj 7 6
c TIOCNOTTY
e
s 00012/00000/00057
d D 4.4 81/10/11 13:02:39 wnj 6 5
c first bootable version
e
s 00002/00002/00055
d D 4.3 81/03/09 01:49:15 wnj 5 4
c lint and a few minor fixed
e
s 00013/00001/00044
d D 4.2 81/01/28 12:05:35 wnj 4 3
c no access to /dev/tty for SDETACH processes.
e
s 00000/00000/00045
d D 4.1 80/11/09 17:32:46 bill 3 2
c minor fixups to restart stuff; version 4.1 for distrib
e
s 00001/00001/00044
d D 3.2 80/06/07 02:47:41 bill 2 1
c %H%->%G%
e
s 00045/00000/00000
d D 3.1 80/04/09 16:04:23 bill 1 0
c date and time created 80/04/09 16:04:23 by bill
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%H%	*/
E 2
I 2
D 5
/*	%M%	%I%	%G%	*/
E 5
I 5
D 19
/*	%M%	%I%	%E%	*/
E 19
I 19
D 34
/*
D 20
 * Copyright (c) 1982 Regents of the University of California.
E 20
I 20
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 20
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 34
I 34
/*-
D 51
 * Copyright (c) 1982, 1986, 1991 The Regents of the University of California.
 * All rights reserved.
E 51
I 51
D 54
 * Copyright (c) 1982, 1986, 1991, 1993
E 54
I 54
 * Copyright (c) 1982, 1986, 1991, 1993, 1995
E 54
 *	The Regents of the University of California.  All rights reserved.
E 51
 *
 * %sccs.include.redist.c%
E 34
 *
 *	%W% (Berkeley) %G%
 */
E 19
E 5
E 2

/*
D 5
 *	indirect driver for controlling tty.
E 5
I 5
 * Indirect driver for controlling tty.
I 6
D 24
 *
 * THIS IS GARBAGE: MUST SOON BE DONE WITH struct inode * IN PROC TABLE.
E 24
E 6
E 5
 */
D 18
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/conf.h"
#include "../h/dir.h"
#include "../h/user.h"
I 16
#include "../h/ioctl.h"
E 16
#include "../h/tty.h"
#include "../h/proc.h"
I 12
#include "../h/uio.h"
E 18
I 18
D 48
#include "param.h"
#include "systm.h"
#include "conf.h"
D 23
#include "dir.h"
E 23
D 31
#include "user.h"
E 31
#include "ioctl.h"
D 37
#include "tty.h"
E 37
#include "proc.h"
I 37
#include "tty.h"
E 37
I 24
#include "vnode.h"
#include "file.h"
E 48
I 48
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/conf.h>
#include <sys/ioctl.h>
#include <sys/proc.h>
#include <sys/tty.h>
#include <sys/vnode.h>
#include <sys/file.h>
E 48
E 24
D 31
#include "uio.h"
E 31
E 18
E 12

I 24
D 52
#define cttyvp(p) ((p)->p_flag&SCTTY ? (p)->p_session->s_ttyvp : NULL)
E 52
I 52
#define cttyvp(p) ((p)->p_flag & P_CONTROLT ? (p)->p_session->s_ttyvp : NULL)
E 52

D 25
static off_t dummyoff;

E 25
E 24
/*ARGSUSED*/
D 29
syopen(dev, flag)
E 29
I 29
D 31
cttyopen(dev, flag)
E 31
I 31
cttyopen(dev, flag, mode, p)
E 31
E 29
I 14
	dev_t dev;
D 31
	int flag;
E 31
I 31
	int flag, mode;
	struct proc *p;
E 31
E 14
{
I 46
D 47
	USES_VOP_ACCESS;
	USES_VOP_LOCK;
	USES_VOP_OPEN;
	USES_VOP_UNLOCK;
E 47
E 46
I 24
D 29
	struct vnode *ttyvp = cttyvp(u.u_procp);
E 29
I 29
D 31
	struct proc *p = curproc;
E 31
	struct vnode *ttyvp = cttyvp(p);
E 29
	int error;
E 24

D 4
	if(u.u_ttyp == NULL) {
E 4
I 4
D 8
	if(u.u_ttyp == NULL || (u.u_procp->p_flag&SDETACH)) {
E 8
I 8
D 14
	if (u.u_ttyp == NULL) {
E 8
E 4
		u.u_error = ENXIO;
		return;
	}
	(*cdevsw[major(u.u_ttyd)].d_open)(u.u_ttyd, flag);
E 14
I 14
D 24
	if (u.u_ttyp == NULL)
E 24
I 24
	if (ttyvp == NULL)
E 24
		return (ENXIO);
D 24
	return ((*cdevsw[major(u.u_ttyd)].d_open)(u.u_ttyd, flag));
E 24
I 24
D 27
	if (error = VOP_ACCESS(ttyvp,
	   (flag&FREAD ? VREAD : 0) | (flag&FWRITE ? VWRITE : 0), u.u_cred))
E 27
I 27
D 54
	VOP_LOCK(ttyvp);
E 54
I 54
	vn_lock(ttyvp, LK_EXCLUSIVE | LK_RETRY, p);
E 54
I 49
#ifdef PARANOID
	/*
D 50
	 * Since group is tty and mode is 620 on all terminal lines
E 50
I 50
	 * Since group is tty and mode is 620 on most terminal lines
E 50
	 * and since sessions protect terminals from processes outside
	 * your session, this check is probably no longer necessary.
	 * Since it inhibits setuid root programs that later switch 
	 * to another user from accessing /dev/tty, we have decided
D 50
	 * to delete this test for now.
E 50
I 50
	 * to delete this test. (mckusick 5/93)
E 50
	 */
E 49
	error = VOP_ACCESS(ttyvp,
D 29
	   (flag&FREAD ? VREAD : 0) | (flag&FWRITE ? VWRITE : 0), u.u_cred);
E 29
I 29
D 32
	   (flag&FREAD ? VREAD : 0) | (flag&FWRITE ? VWRITE : 0), p->p_ucred);
E 32
I 32
	  (flag&FREAD ? VREAD : 0) | (flag&FWRITE ? VWRITE : 0), p->p_ucred, p);
I 35
	if (!error)
I 49
#endif /* PARANOID */
E 49
		error = VOP_OPEN(ttyvp, flag, NOCRED, p);
E 35
E 32
E 29
D 54
	VOP_UNLOCK(ttyvp);
E 54
I 54
	VOP_UNLOCK(ttyvp, 0, p);
E 54
D 35
	if (error)
E 27
		return (error);
D 32
	return (VOP_OPEN(ttyvp, flag, NOCRED));
E 32
I 32
	return (VOP_OPEN(ttyvp, flag, NOCRED, p));
E 35
I 35
	return (error);
E 35
E 32
E 24
E 14
}

/*ARGSUSED*/
D 12
syread(dev)
E 12
I 12
D 22
syread(dev, uio)
E 22
I 22
D 29
syread(dev, uio, flag)
E 29
I 29
D 31
cttyread(dev, uio, flag)
E 31
I 31
D 33
cttyread(dev, uio, flag, p)
E 33
I 33
cttyread(dev, uio, flag)
E 33
E 31
E 29
E 22
	dev_t dev;
	struct uio *uio;
I 36
	int flag;
E 36
I 31
D 33
	struct proc *p;
E 33
E 31
E 12
{
I 46
D 47
	USES_VOP_LOCK;
	USES_VOP_READ;
	USES_VOP_UNLOCK;
E 47
E 46
I 24
D 25
	struct vnode *ttyvp = cttyvp(u.u_procp);
E 25
I 25
D 29
	register struct vnode *ttyvp = cttyvp(u.u_procp);
E 29
I 29
D 31
	register struct vnode *ttyvp = cttyvp(curproc);
E 31
I 31
D 33
	register struct vnode *ttyvp = cttyvp(p);
E 33
I 33
D 54
	register struct vnode *ttyvp = cttyvp(uio->uio_procp);
E 54
I 54
	struct proc *p = uio->uio_procp;
	register struct vnode *ttyvp = cttyvp(p);
E 54
E 33
E 31
E 29
	int error;
E 25
E 24

I 4
D 7
	if (u.u_procp->p_flag&SDETACH) {
E 7
I 7
D 8
	if (u.u_ttyp == NULL || (u.u_procp->p_flag&SDETACH)) {
E 8
I 8
D 13
	if (u.u_ttyp == NULL) {
E 8
E 7
		u.u_error = ENXIO;
		return;
	}
E 4
D 12
	(*cdevsw[major(u.u_ttyd)].d_read)(u.u_ttyd);
E 12
I 12
	(*cdevsw[major(u.u_ttyd)].d_read)(u.u_ttyd, uio);
E 13
I 13
D 24
	if (u.u_ttyp == NULL)
E 24
I 24
	if (ttyvp == NULL)
E 24
D 31
		return (ENXIO);
E 31
I 31
		return (EIO);
E 31
D 22
	return ((*cdevsw[major(u.u_ttyd)].d_read)(u.u_ttyd, uio));
E 22
I 22
D 24
	return ((*cdevsw[major(u.u_ttyd)].d_read)(u.u_ttyd, uio, flag));
E 24
I 24
D 25
	return (VOP_READ(ttyvp, uio, &dummyoff, flag, NOCRED));
E 25
I 25
D 54
	VOP_LOCK(ttyvp);
E 54
I 54
	vn_lock(ttyvp, LK_EXCLUSIVE | LK_RETRY, p);
E 54
	error = VOP_READ(ttyvp, uio, flag, NOCRED);
D 54
	VOP_UNLOCK(ttyvp);
E 54
I 54
	VOP_UNLOCK(ttyvp, 0, p);
E 54
	return (error);
E 25
E 24
E 22
E 13
E 12
}

/*ARGSUSED*/
D 12
sywrite(dev)
E 12
I 12
D 22
sywrite(dev, uio)
E 22
I 22
D 29
sywrite(dev, uio, flag)
E 29
I 29
D 31
cttywrite(dev, uio, flag)
E 31
I 31
D 33
cttywrite(dev, uio, flag, p)
E 33
I 33
cttywrite(dev, uio, flag)
E 33
E 31
E 29
E 22
	dev_t dev;
	struct uio *uio;
I 36
	int flag;
E 36
I 31
D 33
	struct proc *p;
E 33
E 31
E 12
{
I 46
D 47
	USES_VOP_LOCK;
	USES_VOP_UNLOCK;
	USES_VOP_WRITE;
E 47
E 46
I 24
D 25
	struct vnode *ttyvp = cttyvp(u.u_procp);
E 25
I 25
D 29
	register struct vnode *ttyvp = cttyvp(u.u_procp);
E 29
I 29
D 31
	register struct vnode *ttyvp = cttyvp(curproc);
E 31
I 31
D 33
	register struct vnode *ttyvp = cttyvp(p);
E 33
I 33
D 54
	register struct vnode *ttyvp = cttyvp(uio->uio_procp);
E 54
I 54
	struct proc *p = uio->uio_procp;
	struct vnode *ttyvp = cttyvp(uio->uio_procp);
E 54
E 33
E 31
E 29
	int error;
E 25
E 24

I 4
D 7
	if (u.u_procp->p_flag&SDETACH) {
E 7
I 7
D 8
	if (u.u_ttyp == NULL || (u.u_procp->p_flag&SDETACH)) {
E 8
I 8
D 13
	if (u.u_ttyp == NULL) {
E 8
E 7
		u.u_error = ENXIO;
		return;
	}
E 4
D 12
	(*cdevsw[major(u.u_ttyd)].d_write)(u.u_ttyd);
E 12
I 12
	(*cdevsw[major(u.u_ttyd)].d_write)(u.u_ttyd, uio);
E 13
I 13
D 24
	if (u.u_ttyp == NULL)
E 24
I 24
	if (ttyvp == NULL)
E 24
D 31
		return (ENXIO);
E 31
I 31
		return (EIO);
E 31
D 22
	return ((*cdevsw[major(u.u_ttyd)].d_write)(u.u_ttyd, uio));
E 22
I 22
D 24
	return ((*cdevsw[major(u.u_ttyd)].d_write)(u.u_ttyd, uio, flag));
E 24
I 24
D 25
	return (VOP_WRITE(ttyvp, uio, &dummyoff, flag, NOCRED));
E 25
I 25
D 54
	VOP_LOCK(ttyvp);
E 54
I 54
	vn_lock(ttyvp, LK_EXCLUSIVE | LK_RETRY, p);
E 54
	error = VOP_WRITE(ttyvp, uio, flag, NOCRED);
D 54
	VOP_UNLOCK(ttyvp);
E 54
I 54
	VOP_UNLOCK(ttyvp, 0, p);
E 54
	return (error);
E 25
E 24
E 22
E 13
E 12
}

/*ARGSUSED*/
D 29
syioctl(dev, cmd, addr, flag)
E 29
I 29
D 31
cttyioctl(dev, cmd, addr, flag)
E 31
I 31
cttyioctl(dev, cmd, addr, flag, p)
E 31
E 29
D 9
caddr_t addr;
E 9
I 9
	dev_t dev;
D 53
	int cmd;
E 53
I 53
	u_long cmd;
E 53
	caddr_t addr;
	int flag;
I 31
	struct proc *p;
E 31
E 9
{
I 46
D 47
	USES_VOP_IOCTL;
E 47
E 46
I 24
D 29
	struct vnode *ttyvp = cttyvp(u.u_procp);
E 29
I 29
D 31
	struct vnode *ttyvp = cttyvp(curproc);
E 31
I 31
	struct vnode *ttyvp = cttyvp(p);
E 31
E 29
E 24

I 24
	if (ttyvp == NULL)
D 31
		return (ENXIO);
E 31
I 31
		return (EIO);
E 31
E 24
I 4
D 7
	if (u.u_procp->p_flag&SDETACH) {
E 7
I 7
	if (cmd == TIOCNOTTY) {
D 22
		u.u_ttyp = 0;
		u.u_ttyd = 0;
E 22
D 21
		u.u_procp->p_pgrp = 0;
E 21
I 21
D 24
		if (SESS_LEADER(u.u_procp)) {
			/* 
			 * XXX - check posix draft
			 */
			u.u_ttyp->t_session = 0;
			u.u_ttyp->t_pgid = 0;
		}
I 22
		u.u_ttyp = 0;
		u.u_ttyd = 0;
E 22
E 21
I 9
D 10
		u.u_procp->p_flags &= ~SDETACH;
E 10
E 9
D 14
		return;
E 14
I 14
		return (0);
E 24
I 24
D 29
		if (!SESS_LEADER(u.u_procp)) {
			u.u_procp->p_flag &= ~SCTTY;
E 29
I 29
D 31
		if (!SESS_LEADER(curproc)) {
			curproc->p_flag &= ~SCTTY;
E 31
I 31
		if (!SESS_LEADER(p)) {
D 52
			p->p_flag &= ~SCTTY;
E 52
I 52
			p->p_flag &= ~P_CONTROLT;
E 52
E 31
E 29
			return (0);
		} else
			return (EINVAL);
E 24
E 14
	}
D 8
	if (u.u_ttyp == NULL || (u.u_procp->p_flag&SDETACH)) {
E 8
I 8
D 14
	if (u.u_ttyp == NULL) {
E 8
E 7
		u.u_error = ENXIO;
		return;
	}
E 4
	(*cdevsw[major(u.u_ttyd)].d_ioctl)(u.u_ttyd, cmd, addr, flag);
E 14
I 14
D 24
	if (u.u_ttyp == NULL)
		return (ENXIO);
	return ((*cdevsw[major(u.u_ttyd)].d_ioctl)(u.u_ttyd, cmd, addr, flag));
E 24
I 24
D 32
	return (VOP_IOCTL(ttyvp, cmd, addr, flag, NOCRED));
E 32
I 32
	return (VOP_IOCTL(ttyvp, cmd, addr, flag, NOCRED, p));
E 32
E 24
E 14
I 6
}

I 15
/*ARGSUSED*/
E 15
D 29
syselect(dev, flag)
E 29
I 29
D 31
cttyselect(dev, flag)
E 31
I 31
cttyselect(dev, flag, p)
E 31
E 29
I 15
	dev_t dev;
	int flag;
I 31
	struct proc *p;
E 31
E 15
{
I 46
D 47
	USES_VOP_SELECT;
E 47
E 46
I 24
D 29
	struct vnode *ttyvp = cttyvp(u.u_procp);
E 29
I 29
D 31
	struct vnode *ttyvp = cttyvp(curproc);
E 31
I 31
	struct vnode *ttyvp = cttyvp(p);
E 31
E 29
E 24

D 7
	if (u.u_procp->p_flag&SDETACH) {
E 7
I 7
D 8
	if (u.u_ttyp == NULL || (u.u_procp->p_flag&SDETACH)) {
E 8
I 8
D 24
	if (u.u_ttyp == NULL) {
E 8
E 7
		u.u_error = ENXIO;
D 7
		return;
E 7
I 7
		return (0);
E 7
	}
D 7
	(*cdevsw[major(u.u_ttyd)].d_select)(dev, flag);
E 7
I 7
D 11
	return ((*cdevsw[major(u.u_ttyd)].d_select)(dev, flag));
E 11
I 11
	return ((*cdevsw[major(u.u_ttyd)].d_select)(u.u_ttyd, flag));
E 24
I 24
	if (ttyvp == NULL)
D 28
		return (ENXIO);
E 28
I 28
		return (1);	/* try operation to get EOF/failure */
E 28
D 26
	return (VOP_SELECT(ttyvp, flag, NOCRED));
E 26
I 26
D 32
	return (VOP_SELECT(ttyvp, flag, FREAD|FWRITE, NOCRED));
E 32
I 32
	return (VOP_SELECT(ttyvp, flag, FREAD|FWRITE, NOCRED, p));
E 32
E 26
E 24
E 11
E 7
E 6
}
E 1
