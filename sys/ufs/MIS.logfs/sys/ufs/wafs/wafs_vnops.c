#ifdef CLFS
/*
 * CLFS
 * $Log: wafs_vnops.c,v $
 * Revision 1.9  1994/11/29  15:50:24  margo
 * Add wafs_lookup so that it can zero the vnode as well as returning an error.
 *
 * Revision 1.8  1994/10/04  17:02:38  margo
 * Make 4.4Lite version compile under BSD4.4-Lite.
 *
 * Revision 1.3  1994/09/27  18:53:29  jat
 * Fixed includes for alternate AIX/SPARC building.
 *
 * Revision 1.2  1994/09/26  19:48:30  jat
 * Fixed arguments to uiomove calls for AIX.
 *
 * Revision 1.1  1994/09/26  18:47:44  jat
 * Initial WAFS checkin.
 *
 */
#endif
/*
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 * Copyright (c) 1994
 * 	The President and Fellows of Harvard University.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	$Id: wafs_vnops.c,v 1.9 1994/11/29 15:50:24 margo Exp $
 * For version 1, we are going to make all the operations that we do
 * not need EOPNOTSUP.  For version2, we can decide which ones we ultimately
 * need to support.
 */
static char *rcsid = "$Id: wafs_vnops.c,v 1.9 1994/11/29 15:50:24 margo Exp $";

#ifdef CLFS
#include <sys/compat.h>
#include <sys/bsd_types.h>
#include <sys/bsd_param.h>
#include <clfs_param.h>
#include <sys/cdefs.h>
#include <sys/ucred.h>
#include <sys/intr.h>
#include <sys/sleep.h>

#include <sys/param.h>
#include <sys/vnode.h>
#include <sys/socket.h>
#include <sys/mbuf.h>
#include <sys/file.h>
#include <sys/disklabel.h>
#include <sys/filio.h>
#include <sys/errno.h>
#include <sys/malloc.h>

#include <miscfs/specfs/specdev.h>
#include <ufs/ufs/quota.h>
#include <ufs/ufs/ufsmount.h>
#include <ufs/ufs/inode.h>
#include <ufs/ufs/ufs_extern.h>

#else /* CLFS */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/resourcevar.h>
#include <sys/kernel.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/buf.h>
#include <sys/filedesc.h>
#include <sys/proc.h>
#include <sys/conf.h>
#include <sys/mount.h>
#include <sys/vnode.h>
#include <sys/malloc.h>
#include <sys/time.h>
#include <sys/uio.h>
#include <sys/ioctl.h>

#include <vm/vm.h>

#include <miscfs/specfs/specdev.h>
#include <miscfs/fifofs/fifo.h>
#include <ufs/ufs/quota.h>
#include <ufs/ufs/ufsmount.h>
#include <ufs/ufs/inode.h>
#include <ufs/ufs/ufs_extern.h>
#endif /* CLFS */

#include <ufs/wafs/wafs.h>
#include <ufs/wafs/wnode.h>
#include <ufs/wafs/wafs_extern.h>
#include <ufs/wafs/lffs.h>

#ifdef AIX
int vn_bwrite();
extern struct timestruc_t tod;
#endif

/* Global vnode data structures for wafs. */
int (**wafs_vnodeop_p)();
struct vnodeopv_entry_desc wafs_vnodeop_entries[] = {
	{ &vop_default_desc, vn_default_error },
	{ &vop_lookup_desc, wafs_lookup },		/* lookup */
	{ &vop_create_desc, vn_default_error },		/* create */
	{ &vop_mknod_desc, vn_default_error },		/* mknod */
	{ &vop_open_desc, wafs_open },			/* open */
	{ &vop_close_desc, wafs_close },		/* close */
	{ &vop_access_desc, wafs_access },		/* access */
	{ &vop_getattr_desc, wafs_getattr },		/* getattr */
	{ &vop_setattr_desc, vn_default_error },	/* setattr */
	{ &vop_read_desc, wafs_read },			/* read */
	{ &vop_write_desc, wafs_write },		/* write */
	{ &vop_ioctl_desc, wafs_ioctl },		/* ioctl */
	{ &vop_select_desc, vn_default_error },		/* select */
	{ &vop_mmap_desc, vn_default_error },		/* mmap */
	{ &vop_fsync_desc, wafs_fsync },		/* fsync */
	{ &vop_seek_desc, vn_default_error },		/* seek */
	{ &vop_remove_desc, vn_default_error },		/* remove */
	{ &vop_link_desc, vn_default_error },		/* link */
	{ &vop_rename_desc, vn_default_error },		/* rename */
	{ &vop_mkdir_desc, vn_default_error },		/* mkdir */
	{ &vop_rmdir_desc, vn_default_error },		/* rmdir */
	{ &vop_symlink_desc, vn_default_error },	/* symlink */
	{ &vop_readdir_desc, vn_default_error },	/* readdir */
	{ &vop_readlink_desc, vn_default_error },	/* readlink */
	{ &vop_abortop_desc, vn_default_error },	/* abortop */
	{ &vop_inactive_desc, vn_default_error },	/* inactive */
	{ &vop_reclaim_desc, wafs_reclaim },		/* reclaim */
	{ &vop_lock_desc, wafs_lock },			/* lock */
	{ &vop_unlock_desc, wafs_unlock },		/* unlock */
	{ &vop_bmap_desc, wafs_bmap },			/* bmap */
	{ &vop_strategy_desc, wafs_strategy },		/* strategy */
	{ &vop_print_desc, vn_default_error },		/* print */
	{ &vop_islocked_desc, vn_default_error },	/* islocked */
	{ &vop_pathconf_desc, vn_default_error },	/* pathconf */
	{ &vop_advlock_desc, vn_default_error },	/* advlock */
	{ &vop_blkatoff_desc, vn_default_error },	/* blkatoff */
	{ &vop_valloc_desc, vn_default_error },		/* valloc */
	{ &vop_vfree_desc, vn_default_error },		/* vfree */
	{ &vop_truncate_desc, vn_default_error },	/* truncate */
	{ &vop_update_desc, wafs_update },		/* update */
	{ &vop_bwrite_desc, vn_bwrite },
	{ (struct vnodeop_desc*)NULL, (int(*)())NULL }
};
struct vnodeopv_desc wafs_vnodeop_opv_desc =
	{ &wafs_vnodeop_p, wafs_vnodeop_entries };

/*
 * Vnode operation for open.  Enforce constraints that WAFS is append-only.
 */
/* ARGSUSED */
int
wafs_open(ap)
	struct vop_open_args /* {
		struct vnode *a_vp;
		int  a_mode;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{

	/*
	 * Files must be opened READONLY or APPEND.
	 */
	if ((ap->a_mode & (FWRITE | O_APPEND)) == FWRITE)
		return (EPERM);
	return (0);
}

/*
 * Close called,
 * Nop for wafs.
 */
/* ARGSUNUSED */
int
wafs_close(ap)
	struct vop_close_args /* {
		struct vnode *a_vp;
		int  a_fflag;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
	return (0);
}

/*
 * XXX
 * Check mode permission on wnode pointer. For now, we are using
 * WAFS only for file system logging.  I do not know what kind
 * of permission checking to do, so I'm going to punt for now.
 */
int
wafs_access(ap)
	struct vop_access_args /* {
		struct vnode *a_vp;
		int  a_mode;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
	register struct vnode *vp = ap->a_vp;
	register struct ucred *cred = ap->a_cred;
	mode_t mode = ap->a_mode;

#ifdef DIAGNOSTIC
	if (!VOP_ISLOCKED(vp)) {
		vprint("ufs_access: not locked", vp);
		panic("ufs_access: not locked");
	}
#endif
	/*
	 * If you're the super-user, you always get access.
	 * XXX For now, we assume this is always the case.
	 */
	/* if (cred->cr_uid == 0) */
		return (0);
}

/* ARGSUSED */
int
wafs_getattr(ap)
	struct vop_getattr_args /* {
		struct vnode *a_vp;
		struct vattr *a_vap;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
	register struct vnode *vp = ap->a_vp;
	register struct wnode *wp = VTOW(vp);
	register struct vattr *vap = ap->a_vap;

	/*
	 * Copy from wnode table
	 */
	vap->va_fsid = wp->w_dev;
	vap->va_fileid = wp->w_ino;
	vap->va_mode = 0;
	vap->va_nlink = 0;
	vap->va_uid = 0;
	vap->va_gid = 0;
	vap->va_rdev = wp->w_dev;
	vap->va_size = wp->w_tail;
	vap->va_atime = wp->w_atime;
	vap->va_mtime = wp->w_mtime;
	vap->va_ctime = wp->w_ctime;
	vap->va_flags = wp->w_flag;
	vap->va_gen = 0;
	/* this doesn't belong here */
#ifndef AIX
	if (vp->v_type == VBLK)
		vap->va_blocksize = BLKDEV_IOSIZE;
	else if (vp->v_type == VCHR)
		vap->va_blocksize = MAXBSIZE;
	else
#endif
		vap->va_blocksize = vp->v_mount->mnt_stat.f_iosize;
	vap->va_bytes = wp->w_head;
	vap->va_type = vp->v_type;
	vap->va_filerev = 0;
	return (0);
}

/* ARGUSED */
int
wafs_ioctl(ap)
	struct vop_ioctl_args /* {
		struct vnode *a_vp;
		int  a_command;
		caddr_t  a_data;
		int  a_fflag;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
	struct wnode *wp;
	struct lwrite_entry *lwp;
	int error;
	off_t *offp;

	if (ap->a_command != FIOFSYNC && ap->a_command != FIOLOG)
		return (ENOTTY);

	wp = VTOW(ap->a_vp);
	VOP_LOCK(ap->a_vp);
	error = 0;
	switch(ap->a_command) {
	case FIOFSYNC:
		offp = (off_t *)ap->a_data;
		if (wp->w_lastlsn >= *offp)
			break;
		error = VOP_FSYNC(ap->a_vp, ap->a_cred, 1, ap->a_p);
		if (!error)
			*offp = wp->w_lastlsn;
		break;

	case FIOLOG:
		lwp = (struct lwrite_entry *)ap->a_data;
		lwp->logrec_begin = wp->w_head;
		error = VOP_WRITE(ap->a_vp, lwp->uio, ap->a_fflag | IO_APPEND,
		    ap->a_cred);
		lwp->logrec_end = wp->w_head;
		break;
	}

	VOP_UNLOCK(ap->a_vp);
	return(error);
}

/*
 * Synch an open file.
 */
/* ARGSUSED */
int
wafs_fsync(ap)
	struct vop_fsync_args /* {
		struct vnode *a_vp;
		struct ucred *a_cred;
		int a_waitfor;
		struct proc *a_p;
	} */ *ap;
{
	register struct vnode *vp = ap->a_vp;
	struct wnode *wp = VTOW(vp);
	register struct buf *bp;
	struct timeval tv;
	struct buf *nbp;
	int s;

	/*
	 * Flush all dirty buffers associated with a vnode.
	 */
loop:
#ifdef AIX
	s = i_disable(INTIODONE);
#else
	s = splbio();
#endif
	for (bp = vp->v_dirtyblkhd.lh_first; bp; bp = nbp) {
		nbp = bp->b_vnbufs.le_next;
		if ((bp->b_flags & B_BUSY))
			continue;
		if ((bp->b_flags & B_DELWRI) == 0)
			panic("wafs_fsync: not dirty");
		bremfree(bp);
		bp->b_flags |= B_BUSY;
#ifdef AIX
		i_enable(s);
#else
		splx(s);
#endif
		/*
		 * Wait for I/O associated with indirect blocks to complete,
		 * since there is no way to quickly wait for them below.
		 */
		if (bp->b_vp == vp || ap->a_waitfor == MNT_NOWAIT)
			(void) bawrite(bp);
		else
			(void) bwrite(bp);
		goto loop;
	}
	if (ap->a_waitfor == MNT_WAIT) {
		while (vp->v_numoutput) {
			vp->v_flag |= VBWAIT;
#ifdef AIX
			e_sleep(&vp->v_event, EVENT_SHORT);
#else
			sleep((caddr_t)&vp->v_numoutput, PRIBIO + 1);
#endif
		}
#ifdef DIAGNOSTIC
		if (vp->v_dirtyblkhd.lh_first) {
			vprint("wafs_fsync: dirty", vp);
			goto loop;
		}
#endif
	}
#ifdef AIX
	i_enable(s);
	tv = *((struct timeval *)&tod);
#else
	splx(s);
	tv = time;
#endif
	return (VOP_UPDATE(ap->a_vp, &tv, &tv, ap->a_waitfor == MNT_WAIT));
}

/*
 * Lock a wnode. If its already locked, set the WANT bit and sleep.
 */
int
wafs_lock(ap)
	struct vop_lock_args /* {
		struct vnode *a_vp;
	} */ *ap;
{
	register struct vnode *vp = ap->a_vp;
	register struct wnode *wp;
#ifndef AIX
	struct proc *p = curproc;	/* XXX */
#endif

start:
	while (vp->v_flag & VXLOCK) {
		vp->v_flag |= VXWANT;
#ifdef AIX
		e_sleep(&vp->v_event, EVENT_SHORT);
#else
		sleep((caddr_t)vp, PINOD);
#endif
	}
	if (vp->v_tag == VT_NON)
		return (ENOENT);
	wp = VTOW(vp);
	if (wp->w_flag & WLOCKED) {
		wp->w_flag |= WWANT;
#ifdef DIAGNOSTIC
		if (p) {
			if (p->p_pid == wp->w_lockholder)
				panic("locking against myself");
			wp->w_lockwaiter = p->p_pid;
		} else
			wp->w_lockwaiter = -1;
#endif
#ifdef AIX
		e_sleep(&wp->w_event, EVENT_SHORT);
#else
		(void) sleep((caddr_t)wp, PINOD);
#endif
		goto start;
	}
#ifdef DIAGNOSTIC
	wp->w_lockwaiter = 0;
	if (wp->w_lockholder != 0)
		panic("lockholder (%d) != 0", wp->w_lockholder);
	if (p && p->p_pid == 0)
		printf("locking by process 0\n");
	if (p)
		wp->w_lockholder = p->p_pid;
	else
		wp->w_lockholder = -1;
#endif
	wp->w_flag |= WLOCKED;
	return (0);
}

/*
 * Unlock an wnode.  If WANT bit is on, wakeup.
 */
int wafs_lockcount = 90;
int
wafs_unlock(ap)
	struct vop_unlock_args /* {
		struct vnode *a_vp;
	} */ *ap;
{
	register struct wnode *wp = VTOW(ap->a_vp);
#ifndef AIX
	struct proc *p = curproc;	/* XXX */
#endif
#ifdef DIAGNOSTIC
	if ((wp->w_flag & WLOCKED) == 0) {
		vprint("wafs_unlock: unlocked inode", ap->a_vp);
		panic("wafs_unlock NOT LOCKED");
	}
	if (p && p->p_pid != wp->w_lockholder && p->p_pid > -1 &&
	    wp->w_lockholder > -1 && wafs_lockcount++ < 100)
		panic("unlocker (%d) != lock holder (%d)",
		    p->p_pid, wp->w_lockholder);
	wp->w_lockholder = 0;
#endif
	wp->w_flag &= ~WLOCKED;
	if (wp->w_flag & WWANT) {
		wp->w_flag &= ~WWANT;
#ifdef AIX
		e_wakeup(&wp->w_event);
#else
		wakeup((caddr_t)wp);
#endif
	}
	return (0);
}

/*
 * Calculate the logical to physical mapping if not done already,
 * then call the device strategy routine.
 */
int
wafs_strategy(ap)
	struct vop_strategy_args /* {
		struct buf *a_bp;
	} */ *ap;
{
	register struct buf *bp = ap->a_bp;
	register struct vnode *vp = bp->b_vp;
	register struct wnode *wp;
	int error;

	wp = VTOW(vp);
	if (vp->v_type == VBLK || vp->v_type == VCHR)
		panic("wafs_strategy: spec");
	if (bp->b_blkno == bp->b_lblkno) {
		if (error =
		    VOP_BMAP(vp, bp->b_lblkno, NULL, &bp->b_blkno, NULL)) {
			bp->b_error = error;
			bp->b_flags |= B_ERROR;
			biodone(bp);
			return (error);
		}
		if ((long)bp->b_blkno == -1)
			clrbuf(bp);
	}
	if ((long)bp->b_blkno == -1) {
		biodone(bp);
		return (0);
	}
	vp = wp->w_devvp;
#ifdef AIX
	bp->b_dev = VP_RDEV(vp);
#else
	bp->b_dev = vp->v_rdev;
#endif
	VOCALL (vp->v_op, VOFFSET(vop_strategy), ap);
	return (0);
}

int
wafs_lookup(ap)
	struct vop_lookup_args /* {
		struct vnode *a_dvp;
		struct vnode **a_vpp;
		struct componentname *a_cnp;
	} */ *ap;
{
	*ap->a_vpp = NULL;
	return(EOPNOTSUPP);
}
