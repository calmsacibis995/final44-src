h24137
s 00001/00001/00098
d D 8.4 94/06/16 17:05:11 mckusick 32 31
c break out reclaim operations (from mycroft)
e
s 00002/00001/00097
d D 8.3 94/04/16 06:31:56 bostic 31 30
c merge ffs_root and lfs_root into ufs_root
e
s 00000/00003/00098
d D 8.2 94/01/12 15:37:26 hibler 30 29
c export routine and ufs_mountedon defns moved to mount.h.
e
s 00002/00002/00099
d D 8.1 93/06/11 16:28:47 bostic 29 28
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00100
d D 7.20 93/05/25 15:42:30 mckusick 28 27
c add pathconf
e
s 00002/00000/00098
d D 7.19 92/12/09 15:25:30 margo 27 26
c add ihashlookup
e
s 00000/00003/00098
d D 7.18 92/11/14 23:48:22 mckusick 26 25
c delete ufs_iput, ufs_ilock, and ufs_iunlock
e
s 00001/00000/00100
d D 7.17 92/11/13 16:53:57 mckusick 25 24
c ffs_inactive moves to ufs_inactive
e
s 00002/00000/00098
d D 7.16 92/10/07 17:04:21 margo 24 23
c Add ufs_bmap and ufs_getlbns declarations.
e
s 00000/00001/00098
d D 7.15 92/09/24 21:37:01 bostic 23 22
c printing buffer statistics is done at a higher level
e
s 00003/00000/00096
d D 7.14 92/09/14 17:21:19 mckusick 22 20
c add ufs_check_export
e
s 00002/00000/00096
d R 7.14 92/09/14 17:16:32 mckusick 21 20
c add ufs_check_export
e
s 00002/00001/00094
d D 7.13 92/07/20 00:30:09 mckusick 20 19
c new parameter types and functions for inode hashing
e
s 00003/00000/00092
d D 7.12 92/07/02 20:05:37 mckusick 19 18
c hang_addrlist and free_addrlist move in from nfs/nfs_socket.c
e
s 00001/00001/00091
d D 7.11 92/06/27 22:25:26 mckusick 18 17
c ufs_dirbadentry needs an extra parameter
e
s 00000/00003/00092
d D 7.10 92/06/21 01:04:49 torek 17 16
c ufs_chmod, ufs_chown are static and should not be declared here
e
s 00024/00024/00071
d D 7.9 92/05/15 12:19:49 heideman 16 15
c prototypes cleaned up after vn_if change
e
s 00034/00045/00061
d D 7.8 92/05/14 17:41:47 heideman 15 12
c vnode interface conversion
e
s 00034/00045/00061
d R 7.8 92/05/14 16:00:37 heideman 14 12
c vnode interface conversion
e
s 00034/00045/00061
d R 7.8 92/05/14 14:59:47 heideman 13 12
c vnode interface conversion
e
s 00001/00001/00105
d D 7.7 92/05/14 14:37:00 heideman 12 6
c ufs_vinit prototype changed for new vn_if
e
s 00030/00036/00070
d R 7.7 92/05/14 13:08:06 heideman 11 6
c vnode interface conversion
e
s 00030/00036/00070
d R 7.7 92/05/14 12:04:14 heideman 10 6
c vnode interface conversion
e
s 00030/00036/00070
d R 7.7 92/05/14 11:27:45 heideman 9 6
c vnode interface conversion
e
s 00030/00036/00070
d R 7.7 92/05/13 23:23:31 heideman 8 6
c vnode interface conversion
e
s 00030/00036/00070
d R 7.7 92/05/13 19:06:13 heideman 7 6
c vnode interface conversion
e
s 00001/00001/00105
d D 7.6 92/05/13 15:00:31 mckusick 6 5
c fix prototypes
e
s 00003/00002/00103
d D 7.5 92/04/21 11:13:51 mckusick 5 4
c ufs_chown and ufs_chmod now take cred pointers
e
s 00001/00001/00104
d D 7.4 92/03/27 17:39:19 mckusick 4 3
c define doff_t for size of directory offsets
e
s 00018/00015/00087
d D 7.3 92/01/22 09:38:55 heideman 3 2
c lookup converted to new form
e
s 00004/00007/00098
d D 7.2 91/11/05 14:40:46 mckusick 2 1
c reorganization to move ufsmount ops to be vnode ops
e
s 00105/00000/00000
d D 7.1 91/11/01 18:15:39 bostic 1 0
c UFS/FFS split for LFS version 1
e
u
U
t
T
I 1
/*-
D 29
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 29
I 29
D 31
 * Copyright (c) 1991, 1993
E 31
I 31
 * Copyright (c) 1991, 1993, 1994
E 31
 *	The Regents of the University of California.  All rights reserved.
E 29
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

struct buf;
struct direct;
struct disklabel;
struct fid;
struct flock;
struct inode;
I 22
struct mbuf;
E 22
struct mount;
struct nameidata;
struct proc;
struct ucred;
struct uio;
struct vattr;
struct vnode;
I 19
struct ufs_args;
E 19

__BEGIN_DECLS
void	 diskerr
	    __P((struct buf *, char *, char *, int, int, struct disklabel *));
void	 disksort __P((struct buf *, struct buf *));
u_int	 dkcksum __P((struct disklabel *));
char	*readdisklabel __P((dev_t, int (*)(), struct disklabel *));
int	 setdisklabel __P((struct disklabel *, struct disklabel *, u_long));
int	 writedisklabel __P((dev_t, int (*)(), struct disklabel *));

D 3
int	 ufs_abortop __P((struct nameidata *));
E 3
I 3
D 15
int	 ufs_abortop __P((struct vnode *, struct componentname *));
E 3
int	 ufs_access __P((struct vnode *, int, struct ucred *, struct proc *));
int	 ufs_advlock __P((struct vnode *, caddr_t, int, struct flock *, int));
E 15
I 15
D 16
int	 ufs_abortop __P((struct vop_abortop_args *)); /* XXX */
int	 ufs_access __P((struct vop_access_args *)); /* XXX */
int	 ufs_advlock __P((struct vop_advlock_args *)); /* XXX */
E 16
I 16
int	 ufs_abortop __P((struct vop_abortop_args *));
int	 ufs_access __P((struct vop_access_args *));
int	 ufs_advlock __P((struct vop_advlock_args *));
I 24
int	 ufs_bmap __P((struct vop_bmap_args *));
E 24
E 16
E 15
D 2
int	 ufs_bmap __P((struct vnode *, daddr_t, struct vnode **, daddr_t *));
E 2
D 23
void	 ufs_bufstats __P((void));
E 23
I 22
int	 ufs_check_export __P((struct mount *, struct ufid *, struct mbuf *,
		struct vnode **, int *exflagsp, struct ucred **));
E 22
int	 ufs_checkpath __P((struct inode *, struct inode *, struct ucred *));
D 5
int	 ufs_chmod __P((struct vnode *, int, struct proc *));
int	 ufs_chown __P((struct vnode *, u_int, u_int, struct proc *));
E 5
I 5
D 17
int	 ufs_chmod __P((struct vnode *, int, struct ucred *, struct proc *));
int	 ufs_chown
D 6
	    __P((struct vnode *, u_int, u_int, struct ucred *, struct proc *));
E 6
I 6
	    __P((struct vnode *, uid_t, gid_t, struct ucred *, struct proc *));
E 17
E 6
E 5
D 15
int	 ufs_close __P((struct vnode *, int, struct ucred *, struct proc *));
D 3
int	 ufs_create __P((struct nameidata *, struct vattr *, struct proc *));
E 3
I 3
int	 ufs_create __P((struct vnode *, struct vnode **,
			 struct componentname *, struct vattr *));
E 15
I 15
D 16
int	 ufs_close __P((struct vop_close_args *)); /* XXX */
E 16
I 16
int	 ufs_close __P((struct vop_close_args *));
E 16
int	 ufs_create __P((struct vop_create_args *));
E 15
E 3
D 4
void	 ufs_dirbad __P((struct inode *, off_t, char *));
E 4
I 4
void	 ufs_dirbad __P((struct inode *, doff_t, char *));
E 4
D 18
int	 ufs_dirbadentry __P((struct direct *, int));
E 18
I 18
int	 ufs_dirbadentry __P((struct vnode *, struct direct *, int));
E 18
int	 ufs_dirempty __P((struct inode *, ino_t, struct ucred *));
D 3
int	 ufs_direnter __P((struct inode *, struct nameidata *));
int	 ufs_dirremove __P((struct nameidata *));
E 3
I 3
int	 ufs_direnter __P((struct inode *, struct vnode *,struct componentname *));
int	 ufs_dirremove __P((struct vnode *, struct componentname*));
E 3
int	 ufs_dirrewrite
D 3
	    __P((struct inode *, struct inode *, struct nameidata *));
E 3
I 3
	    __P((struct inode *, struct inode *, struct componentname *));
I 19
D 30
void	 ufs_free_addrlist __P((struct ufsmount *));
E 30
E 19
E 3
D 2
int	 ufs_fhtovp __P((struct mount *, struct fid *, struct vnode **));
E 2
D 15
int	 ufs_getattr __P((struct vnode *,
	    struct vattr *, struct ucred *, struct proc *));
E 15
I 15
int	 ufs_getattr __P((struct vop_getattr_args *));
I 24
int	 ufs_getlbns __P((struct vnode *, daddr_t, struct indir *, int *));
E 24
I 19
D 30
int	 ufs_hang_addrlist __P((struct mount *, struct ufs_args *));
E 30
E 19
E 15
D 2
struct inode *
E 2
I 2
struct vnode *
E 2
D 20
	 ufs_ihashget __P((int, ino_t));
E 20
I 20
	 ufs_ihashget __P((dev_t, ino_t));
E 20
void	 ufs_ihashinit __P((void));
void	 ufs_ihashins __P((struct inode *));
I 27
struct vnode *
	 ufs_ihashlookup __P((dev_t, ino_t));
E 27
I 20
void	 ufs_ihashrem __P((struct inode *));
E 20
D 26
void	 ufs_ilock __P((struct inode *));
E 26
I 25
int	 ufs_inactive __P((struct vop_inactive_args *));
E 25
D 2
int	 ufs_inactive __P((struct vnode *, struct proc *));
E 2
int	 ufs_init __P((void));
D 15
int	 ufs_ioctl __P((struct vnode *,
	    int, caddr_t, int, struct ucred *, struct proc *));
E 15
I 15
int	 ufs_ioctl __P((struct vop_ioctl_args *));
E 15
D 26
void	 ufs_iput __P((struct inode *));
E 26
D 15
int	 ufs_islocked __P((struct vnode *));
E 15
I 15
D 16
int	 ufs_islocked __P((struct vop_islocked_args *)); /* XXX */
E 16
I 16
int	 ufs_islocked __P((struct vop_islocked_args *));
E 16
E 15
D 26
void	 ufs_iunlock __P((struct inode *));
E 26
D 3
int	 ufs_link __P((struct vnode *, struct nameidata *, struct proc *));
E 3
I 3
D 15
int	 ufs_link __P((struct vnode *, struct vnode *, struct componentname *));
E 3
int	 ufs_lock __P((struct vnode *));
D 3
int	 ufs_lookup __P((struct vnode *, struct nameidata *, struct proc *));
I 2
int	 ufs_makeinode __P((int mode, struct nameidata *, struct vnode **));
E 2
int	 ufs_mkdir __P((struct nameidata *, struct vattr *, struct proc *));
int	 ufs_mknod __P((struct nameidata *,
	    struct vattr *, struct ucred *, struct proc *));
E 3
I 3
int	 ufs_lookup __P((struct vnode *, struct vnode **, struct componentname *));
E 15
I 15
D 16
int	 ufs_link __P((struct vop_link_args *)); /* XXX */
int	 ufs_lock __P((struct vop_lock_args *)); /* XXX */
int	 ufs_lookup __P((struct vop_lookup_args *)); /* XXX */
E 16
I 16
int	 ufs_link __P((struct vop_link_args *));
int	 ufs_lock __P((struct vop_lock_args *));
int	 ufs_lookup __P((struct vop_lookup_args *));
E 16
E 15
int	 ufs_makeinode __P((int mode, struct vnode *, struct vnode **, struct componentname *));
D 15
int	 ufs_mkdir __P((struct vnode *, struct vnode **,
			struct componentname *, struct vattr *));
int	 ufs_mknod __P((struct vnode *, struct vnode **,
			struct componentname *, struct vattr *));
E 3
int	 ufs_mmap __P((struct vnode *, int, struct ucred *, struct proc *));
E 15
I 15
int	 ufs_mkdir __P((struct vop_mkdir_args *));
int	 ufs_mknod __P((struct vop_mknod_args *));
D 16
int	 ufs_mmap __P((struct vop_mmap_args *)); /* XXX */
E 16
I 16
int	 ufs_mmap __P((struct vop_mmap_args *));
E 16
E 15
D 30
int	 ufs_mountedon __P((struct vnode *));
E 30
D 15
int	 ufs_open __P((struct vnode *, int, struct ucred *, struct proc *));
int	 ufs_print __P((struct vnode *));
int	 ufs_readdir __P((struct vnode *, struct uio *, struct ucred *, int *));
int	 ufs_readlink __P((struct vnode *, struct uio *, struct ucred *));
int	 ufs_reclaim __P((struct vnode *));
D 3
int	 ufs_remove __P((struct nameidata *, struct proc *));
E 3
I 3
int	 ufs_remove __P((struct vnode *, struct vnode *, struct componentname *));
E 3
int	 ufs_rename
D 3
	    __P((struct nameidata *, struct nameidata *, struct proc *));
int	 ufs_rmdir __P((struct nameidata *, struct proc *));
E 3
I 3
	    __P((struct vnode *, struct vnode *, struct componentname *,
		 struct vnode *, struct vnode *, struct componentname *));
int	 ufs_rmdir __P((struct vnode *, struct vnode *, struct componentname *));
E 3
D 2
int	 ufs_root __P((struct mount *, struct vnode **));
E 2
int	 ufs_seek __P((struct vnode *, off_t, off_t, struct ucred *));
int	 ufs_select
	    __P((struct vnode *, int, int, struct ucred *, struct proc *));
int	 ufs_setattr __P((struct vnode *,
	    struct vattr *, struct ucred *, struct proc *));
E 15
I 15
D 16
int	 ufs_open __P((struct vop_open_args *)); /* XXX */
int	 ufs_print __P((struct vop_print_args *)); /* XXX */
int	 ufs_readdir __P((struct vop_readdir_args *)); /* XXX */
int	 ufs_readlink __P((struct vop_readlink_args *)); /* XXX */
int	 ufs_reclaim __P((struct vop_reclaim_args *)); /* XXX */
int	 ufs_remove __P((struct vop_remove_args *)); /* XXX */
E 16
I 16
int	 ufs_open __P((struct vop_open_args *));
I 28
int	 ufs_pathconf __P((struct vop_pathconf_args *));
E 28
int	 ufs_print __P((struct vop_print_args *));
int	 ufs_readdir __P((struct vop_readdir_args *));
int	 ufs_readlink __P((struct vop_readlink_args *));
D 32
int	 ufs_reclaim __P((struct vop_reclaim_args *));
E 32
I 32
int	 ufs_reclaim __P((struct vnode *));
E 32
int	 ufs_remove __P((struct vop_remove_args *));
E 16
int	 ufs_rename __P((struct vop_rename_args *));
D 16
int	 ufs_rmdir __P((struct vop_rmdir_args *)); /* XXX */
int	 ufs_seek __P((struct vop_seek_args *)); /* XXX */
E 16
I 16
int	 ufs_rmdir __P((struct vop_rmdir_args *));
I 31
int	 ufs_root __P((struct mount *, struct vnode **));
E 31
int	 ufs_seek __P((struct vop_seek_args *));
E 16
int	 ufs_select __P((struct vop_select_args *));
int	 ufs_setattr __P((struct vop_setattr_args *));
E 15
int	 ufs_start __P((struct mount *, int, struct proc *));
D 15
int	 ufs_strategy __P((struct buf *));
int	 ufs_symlink
D 3
	    __P((struct nameidata *, struct vattr *, char *, struct proc *));
E 3
I 3
	    __P((struct vnode *, struct vnode **, struct componentname *, struct vattr *, char *));
E 3
int	 ufs_unlock __P((struct vnode *));
E 15
I 15
D 16
int	 ufs_strategy __P((struct vop_strategy_args *)); /* XXX */
E 16
I 16
int	 ufs_strategy __P((struct vop_strategy_args *));
E 16
int	 ufs_symlink __P((struct vop_symlink_args *));
D 16
int	 ufs_unlock __P((struct vop_unlock_args *)); /* XXX */
E 16
I 16
int	 ufs_unlock __P((struct vop_unlock_args *));
E 16
E 15
D 2
int	 ufs_vinit __P((struct mount *, struct vnode **));
int	 ufs_vptofh __P((struct vnode *, struct fid *));
E 2
I 2
int	 ufs_vinit __P((struct mount *,
D 12
	    struct vnodeops *, struct vnodeops *, struct vnode **));
E 12
I 12
	    int (**)(), int (**)(), struct vnode **));
E 12
E 2
D 15
int	 ufsspec_close
	    __P((struct vnode *, int, struct ucred *, struct proc *));
int	 ufsspec_read __P((struct vnode *, struct uio *, int, struct ucred *));
int	 ufsspec_write __P((struct vnode *, struct uio *, int, struct ucred *));
E 15
I 15
int	 ufsspec_close __P((struct vop_close_args *));
D 16
int	 ufsspec_read __P((struct vop_read_args *)); /* XXX */
int	 ufsspec_write __P((struct vop_write_args *)); /* XXX */
E 16
I 16
int	 ufsspec_read __P((struct vop_read_args *));
int	 ufsspec_write __P((struct vop_write_args *));
E 16
E 15

#ifdef FIFO
D 15
int	ufsfifo_read __P((struct vnode *, struct uio *, int, struct ucred *));
int	ufsfifo_write __P((struct vnode *, struct uio *, int, struct ucred *));
int	ufsfifo_close __P((struct vnode *, int, struct ucred *, struct proc *));
E 15
I 15
D 16
int	ufsfifo_read __P((struct vop_read_args *)); /* XXX */
int	ufsfifo_write __P((struct vop_write_args *)); /* XXX */
int	ufsfifo_close __P((struct vop_close_args *)); /* XXX */
E 16
I 16
int	ufsfifo_read __P((struct vop_read_args *));
int	ufsfifo_write __P((struct vop_write_args *));
int	ufsfifo_close __P((struct vop_close_args *));
E 16
E 15
#endif
__END_DECLS
E 1
