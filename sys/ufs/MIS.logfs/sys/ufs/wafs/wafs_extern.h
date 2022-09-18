#ifdef CLFS
/*
 * CLFS
 * $Log: wafs_extern.h,v $
 * Revision 1.7  1994/11/29  15:50:24  margo
 * Add wafs_lookup so that it can zero the vnode as well as returning an error.
 *
 * Revision 1.6  1994/10/04  17:03:04  margo
 * Make 4.4Lite version compile under BSD4.4-Lite.
 *
 * Revision 1.1  1994/09/26  18:47:38  jat
 * Initial WAFS checkin.
 *
 */
#endif
/*
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
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
 *	$Id: wafs_extern.h,v 1.7 1994/11/29 15:50:24 margo Exp $
 */

struct fid;
struct mount;
struct nameidata;
struct proc;
struct statfs;
struct timeval;
struct inode;
struct uio;
struct mbuf;

__BEGIN_DECLS
int	wafs_access __P((struct vop_access_args *));
int	wafs_bmap __P((struct vop_bmap_args *));
int	wafs_close __P((struct vop_close_args *));
int	wafs_fhtovp __P((struct mount *, struct fid *, struct mbuf *,
			 struct vnode **, int *, struct ucred **));
int	wafs_fsync __P((struct vop_fsync_args *));
int	wafs_init __P((void));
int	wafs_getattr __P((struct vop_getattr_args *));
int	wafs_ioctl __P((struct vop_ioctl_args *));
int	wafs_lock __P((struct vop_lock_args *));
int	wafs_lookup __P((struct vop_lookup_args *));
int	wafs_mount __P((struct mount *, char *, caddr_t, struct nameidata *,
			struct proc *));
int	wafs_open __P((struct vop_open_args *));
int	wafs_read __P((struct vop_read_args *));
int	wafs_reclaim __P((struct vop_reclaim_args  *));
int	wafs_root __P((struct mount *, struct vnode **));
int	wafs_sbupdate __P((struct ufsmount *, int waitfor));
int	wafs_statfs __P((struct mount *, struct statfs *, struct proc *));
int	wafs_strategy __P((struct vop_strategy_args *));
int	wafs_sync __P((struct mount *, int, struct ucred *, struct proc *));
int	wafs_unlock __P((struct vop_unlock_args *));
int	wafs_update __P((struct vop_update_args *));
int	wafs_vget __P((struct mount *, ino_t, struct vnode **));
int	wafs_vptofh __P((struct vnode *, struct fid *));
int	wafs_write __P((struct vop_write_args *));
int	wafs_unmount __P((struct mount *, int, struct proc *));
#ifdef DEBUG
#endif
__END_DECLS

extern int (**wafs_vnodeop_p)();
extern int (**wafs_specop_p)();
#ifdef FIFO
extern int (**wafs_fifoop_p)();
#define WAFS_FIFOOPS wafs_fifoop_p
#else
#define WAFS_FIFOOPS NULL
#endif
