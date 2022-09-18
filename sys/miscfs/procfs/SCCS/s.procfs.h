h63461
s 00004/00003/00164
d D 8.9 95/05/14 00:43:17 mckusick 9 8
c convert locking to use vop_nolock* functions
e
s 00001/00000/00166
d D 8.8 95/04/03 23:17:43 mckusick 8 7
c add revoke operator
e
s 00027/00021/00139
d D 8.7 94/06/15 12:30:43 pendry 7 6
c merge in netbsd changes.
c security fixes, curproc becomes symlink, misc other trash.
e
s 00001/00000/00159
d D 8.6 94/02/03 12:31:53 pendry 6 5
c add forward declaration of struct fpreg (like struct reg)
e
s 00004/00000/00155
d D 8.5 94/01/27 11:30:44 pendry 5 4
c add fpregs entry point
e
s 00002/00002/00153
d D 8.4 94/01/21 19:59:06 bostic 4 3
c copyright typo
e
s 00000/00001/00155
d D 8.3 94/01/17 14:43:17 pendry 3 2
c add pathconf entry
e
s 00001/00000/00155
d D 8.2 94/01/05 12:53:28 pendry 2 1
c declare procfs_fix_sstep
e
s 00155/00000/00000
d D 8.1 94/01/05 12:34:08 pendry 1 0
c date and time created 94/01/05 12:34:08 by pendry
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1993 The Regents of the University of California.
E 4
 * Copyright (c) 1993 Jan-Simon Pendry
D 4
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * From:
 *	$Id: procfs.h,v 3.2 1993/12/15 09:40:17 jsp Exp $
 */

/*
 * The different types of node in a procfs filesystem
 */
typedef enum {
	Proot,		/* the filesystem root */
I 7
	Pcurproc,	/* symbolic link for curproc */
E 7
	Pproc,		/* a process-specific sub-directory */
	Pfile,		/* the executable file */
	Pmem,		/* the process's memory image */
	Pregs,		/* the process's register set */
I 5
	Pfpregs,	/* the process's FP register set */
E 5
	Pctl,		/* process control */
	Pstatus,	/* process status */
	Pnote,		/* process notifier */
	Pnotepg		/* process group notifier */
} pfstype;

/*
 * control data for the proc file system.
 */
struct pfsnode {
	struct pfsnode	*pfs_next;	/* next on list */
	struct vnode	*pfs_vnode;	/* vnode associated with this pfsnode */
	pfstype		pfs_type;	/* type of procfs node */
	pid_t		pfs_pid;	/* associated process */
	u_short		pfs_mode;	/* mode bits for stat() */
	u_long		pfs_flags;	/* open flags */
	u_long		pfs_fileno;	/* unique file id */
};

#define PROCFS_NOTELEN	64	/* max length of a note (/proc/$pid/note) */
#define PROCFS_CTLLEN 	8	/* max length of a ctl msg (/proc/$pid/ctl */

/*
 * Kernel stuff follows
 */
#ifdef KERNEL
#define CNEQ(cnp, s, len) \
	 ((cnp)->cn_namelen == (len) && \
	  (bcmp((s), (cnp)->cn_nameptr, (len)) == 0))

/*
 * Format of a directory entry in /proc, ...
 * This must map onto struct dirent (see <dirent.h>)
 */
#define PROCFS_NAMELEN 8
struct pfsdent {
	u_long	d_fileno;
	u_short	d_reclen;
	u_char	d_type;
	u_char	d_namlen;
	char	d_name[PROCFS_NAMELEN];
};
#define UIO_MX sizeof(struct pfsdent)
#define PROCFS_FILENO(pid, type) \
D 7
	(((type) == Proot) ? \
			2 : \
			((((pid)+1) << 3) + ((int) (type))))
E 7
I 7
	(((type) < Pproc) ? \
			((type) + 2) : \
			((((pid)+1) << 4) + ((int) (type))))
E 7

/*
 * Convert between pfsnode vnode
 */
#define VTOPFS(vp)	((struct pfsnode *)(vp)->v_data)
#define PFSTOV(pfs)	((pfs)->pfs_vnode)

typedef struct vfs_namemap vfs_namemap_t;
struct vfs_namemap {
	const char *nm_name;
	int nm_val;
};

D 7
extern int vfs_getuserstr __P((struct uio *, char *, int *));
extern vfs_namemap_t *vfs_findname __P((vfs_namemap_t *, char *, int));
E 7
I 7
int vfs_getuserstr __P((struct uio *, char *, int *));
vfs_namemap_t *vfs_findname __P((vfs_namemap_t *, char *, int));
E 7

/* <machine/reg.h> */
struct reg;
I 6
struct fpreg;
E 6

#define PFIND(pid) ((pid) ? pfind(pid) : &proc0)
D 7
extern int procfs_freevp __P((struct vnode *));
extern int procfs_allocvp __P((struct mount *, struct vnode **, long, pfstype));
extern struct vnode *procfs_findtextvp __P((struct proc *));
extern int procfs_sstep __P((struct proc *));
I 2
extern void procfs_fix_sstep __P((struct proc *));
E 2
extern int procfs_read_regs __P((struct proc *, struct reg *));
extern int procfs_write_regs __P((struct proc *, struct reg *));
I 5
extern int procfs_read_fpregs __P((struct proc *, struct fpreg *));
extern int procfs_write_fpregs __P((struct proc *, struct fpreg *));
E 5
extern int procfs_donote __P((struct proc *, struct proc *, struct pfsnode *pfsp, struct uio *uio));
extern int procfs_doregs __P((struct proc *, struct proc *, struct pfsnode *pfsp, struct uio *uio));
I 5
extern int procfs_dofpregs __P((struct proc *, struct proc *, struct pfsnode *pfsp, struct uio *uio));
E 5
extern int procfs_domem __P((struct proc *, struct proc *, struct pfsnode *pfsp, struct uio *uio));
extern int procfs_doctl __P((struct proc *, struct proc *, struct pfsnode *pfsp, struct uio *uio));
extern int procfs_dostatus __P((struct proc *, struct proc *, struct pfsnode *pfsp, struct uio *uio));
E 7
I 7
int procfs_freevp __P((struct vnode *));
int procfs_allocvp __P((struct mount *, struct vnode **, long, pfstype));
struct vnode *procfs_findtextvp __P((struct proc *));
int procfs_sstep __P((struct proc *, int));
void procfs_fix_sstep __P((struct proc *));
int procfs_read_regs __P((struct proc *, struct reg *));
int procfs_write_regs __P((struct proc *, struct reg *));
int procfs_read_fpregs __P((struct proc *, struct fpreg *));
int procfs_write_fpregs __P((struct proc *, struct fpreg *));
int procfs_donote __P((struct proc *, struct proc *, struct pfsnode *pfsp, struct uio *uio));
int procfs_doregs __P((struct proc *, struct proc *, struct pfsnode *pfsp, struct uio *uio));
int procfs_dofpregs __P((struct proc *, struct proc *, struct pfsnode *pfsp, struct uio *uio));
int procfs_domem __P((struct proc *, struct proc *, struct pfsnode *pfsp, struct uio *uio));
int procfs_doctl __P((struct proc *, struct proc *, struct pfsnode *pfsp, struct uio *uio));
int procfs_dostatus __P((struct proc *, struct proc *, struct pfsnode *pfsp, struct uio *uio));
E 7

I 7
/* functions to check whether or not files should be displayed */
int procfs_validfile __P((struct proc *));
int procfs_validfpregs __P((struct proc *));
int procfs_validregs __P((struct proc *));

E 7
#define PROCFS_LOCKED	0x01
#define PROCFS_WANT	0x02

extern int (**procfs_vnodeop_p)();
extern struct vfsops procfs_vfsops;

/*
 * Prototypes for procfs vnode ops
 */
int	procfs_badop();	/* varargs */
int	procfs_rw __P((struct vop_read_args *));
int	procfs_lookup __P((struct vop_lookup_args *));
#define procfs_create ((int (*) __P((struct vop_create_args *))) procfs_badop)
#define procfs_mknod ((int (*) __P((struct vop_mknod_args *))) procfs_badop)
int	procfs_open __P((struct vop_open_args *));
int	procfs_close __P((struct vop_close_args *));
int	procfs_access __P((struct vop_access_args *));
int	procfs_getattr __P((struct vop_getattr_args *));
int	procfs_setattr __P((struct vop_setattr_args *));
#define	procfs_read procfs_rw
#define	procfs_write procfs_rw
int	procfs_ioctl __P((struct vop_ioctl_args *));
#define procfs_select ((int (*) __P((struct vop_select_args *))) procfs_badop)
#define procfs_mmap ((int (*) __P((struct vop_mmap_args *))) procfs_badop)
I 8
#define	procfs_revoke vop_revoke
E 8
#define procfs_fsync ((int (*) __P((struct vop_fsync_args *))) procfs_badop)
#define procfs_seek ((int (*) __P((struct vop_seek_args *))) procfs_badop)
#define procfs_remove ((int (*) __P((struct vop_remove_args *))) procfs_badop)
#define procfs_link ((int (*) __P((struct vop_link_args *))) procfs_badop)
#define procfs_rename ((int (*) __P((struct vop_rename_args *))) procfs_badop)
#define procfs_mkdir ((int (*) __P((struct vop_mkdir_args *))) procfs_badop)
#define procfs_rmdir ((int (*) __P((struct vop_rmdir_args *))) procfs_badop)
#define procfs_symlink ((int (*) __P((struct vop_symlink_args *))) procfs_badop)
int	procfs_readdir __P((struct vop_readdir_args *));
D 7
#define procfs_readlink ((int (*) __P((struct vop_readlink_args *))) procfs_badop)
E 7
I 7
int	procfs_readlink __P((struct vop_readlink_args *));
E 7
int	procfs_abortop __P((struct vop_abortop_args *));
int	procfs_inactive __P((struct vop_inactive_args *));
int	procfs_reclaim __P((struct vop_reclaim_args *));
D 9
#define procfs_lock ((int (*) __P((struct vop_lock_args *))) nullop)
#define procfs_unlock ((int (*) __P((struct vop_unlock_args *))) nullop)
E 9
I 9
#define procfs_lock ((int (*) __P((struct  vop_lock_args *)))vop_nolock)
#define procfs_unlock ((int (*) __P((struct  vop_unlock_args *)))vop_nounlock)
E 9
int	procfs_bmap __P((struct vop_bmap_args *));
#define	procfs_strategy ((int (*) __P((struct vop_strategy_args *))) procfs_badop)
int	procfs_print __P((struct vop_print_args *));
D 9
#define procfs_islocked ((int (*) __P((struct vop_islocked_args *))) nullop)
E 9
I 9
#define procfs_islocked \
	((int (*) __P((struct vop_islocked_args *)))vop_noislocked)
E 9
#define procfs_advlock ((int (*) __P((struct vop_advlock_args *))) procfs_badop)
D 3
#define procfs_pathconf ((int (*) __P((struct vop_pathconf_args *))) procfs_badop)
E 3
#define procfs_blkatoff ((int (*) __P((struct vop_blkatoff_args *))) procfs_badop)
#define procfs_valloc ((int (*) __P((struct vop_valloc_args *))) procfs_badop)
#define procfs_vfree ((int (*) __P((struct vop_vfree_args *))) nullop)
#define procfs_truncate ((int (*) __P((struct vop_truncate_args *))) procfs_badop)
#define procfs_update ((int (*) __P((struct vop_update_args *))) nullop)
#endif /* KERNEL */
E 1
