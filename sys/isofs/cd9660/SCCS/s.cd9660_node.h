h49138
s 00001/00003/00118
d D 8.6 95/05/14 00:34:07 mckusick 6 5
c convert to using lock manager
e
s 00001/00000/00120
d D 8.5 95/02/22 21:05:03 mckusick 5 4
c define cd9660_revoke to use vop_revoke
e
s 00006/00000/00114
d D 8.4 94/12/05 21:50:55 mckusick 4 3
c update from mycroft
e
s 00010/00013/00104
d D 8.3 94/07/13 16:35:22 mckusick 3 2
c update for 4.4BSD-Lite (from mycroft)
e
s 00022/00022/00095
d D 8.2 94/01/23 23:50:46 mckusick 2 1
c isofs => cd9660 naming convention
e
s 00117/00000/00000
d D 8.1 94/01/21 18:28:57 mckusick 1 0
c from Mike Hibler
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley
 * by Pace Willisson (pace@blitz.com).  The Rock Ridge Extension
 * Support code is derived from software contributed to Berkeley
 * by Atsushi Murai (amurai@spec.co.jp).
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Theoretically, directories can be more than 2Gb in length,
 * however, in practice this seems unlikely. So, we define
 * the type doff_t as a long to keep down the cost of doing
 * lookup on a 32-bit machine. If you are porting to a 64-bit
 * architecture, you should make doff_t the same as off_t.
 */
#define doff_t	long

typedef	struct	{
	struct timespec	iso_atime;	/* time of last access */
	struct timespec	iso_mtime;	/* time of last modification */
	struct timespec	iso_ctime;	/* time file changed */
	u_short		iso_mode;	/* files access mode and type */
	uid_t		iso_uid;	/* owner user id */
	gid_t		iso_gid;	/* owner group id */
	short		iso_links;	/* links of file */
	dev_t		iso_rdev;	/* Major/Minor number for special */
} ISO_RRIP_INODE;

D 3
#ifdef	ISODEVMAP
E 3
I 3
#ifdef ISODEVMAP
E 3
/*
 * FOr device# (major,minor) translation table
 */
struct iso_dnode {
D 3
	struct iso_dnode *d_chain[2];	/* hash chain, MUST be first */
E 3
I 3
	struct iso_dnode *d_next, **d_prev;	/* hash chain */
E 3
	dev_t		i_dev;		/* device where dnode resides */
	ino_t		i_number;	/* the identity of the inode */
	dev_t		d_dev;		/* device # for translation */
};
D 3
#define	d_forw		d_chain[0]
#define	d_back		d_chain[1]
E 3
#endif

struct iso_node {
D 3
	struct	iso_node *i_chain[2]; /* hash chain, MUST be first */
E 3
I 3
	struct	iso_node *i_next, **i_prev;	/* hash chain */
E 3
	struct	vnode *i_vnode;	/* vnode associated with this inode */
	struct	vnode *i_devvp;	/* vnode for block I/O */
	u_long	i_flag;		/* see below */
	dev_t	i_dev;		/* device where inode resides */
	ino_t	i_number;	/* the identity of the inode */
				/* we use the actual starting block of the file */
	struct	iso_mnt *i_mnt;	/* filesystem associated with this inode */
	struct	lockf *i_lockf;	/* head of byte-level lock list */
	doff_t	i_endoff;	/* end of useful stuff in directory */
	doff_t	i_diroff;	/* offset in dir, where we found last entry */
	doff_t	i_offset;	/* offset of free space in directory */
	ino_t	i_ino;		/* inode number of found directory */
D 3
	long	i_spare0;
	long	i_spare1;
E 3
I 3
D 6
	pid_t	i_lockholder, i_lockwaiter;
E 6
I 6
	struct	lock i_lock;	/* node lock */
E 6
E 3

	long iso_extent;	/* extent of file */
	long i_size;
	long iso_start;		/* actual start of data of file (may be different */
				/* from iso_extent, if file has extended attributes) */
	ISO_RRIP_INODE  inode;
};

#define	i_forw		i_chain[0]
#define	i_back		i_chain[1]

/* flags */
D 3
#define	ILOCKED		0x0001		/* inode is locked */
#define	IWANT		0x0002		/* some process waiting on lock */
#define	IACC		0x0020		/* inode access time to be updated */
E 3
I 3
D 6
#define	IN_LOCKED	0x0001		/* inode is locked */
#define	IN_WANTED	0x0002		/* some process waiting on lock */
E 6
#define	IN_ACCESS	0x0020		/* inode access time to be updated */
E 3

#define VTOI(vp) ((struct iso_node *)(vp)->v_data)
#define ITOV(ip) ((ip)->i_vnode)

D 3
#define ISO_ILOCK(ip)	iso_ilock(ip)
#define ISO_IUNLOCK(ip)	iso_iunlock(ip)

E 3
/*
 * Prototypes for ISOFS vnode operations
 */
D 2
int isofs_lookup __P((struct vop_lookup_args *));
int isofs_open __P((struct vop_open_args *));
int isofs_close __P((struct vop_close_args *));
int isofs_access __P((struct vop_access_args *));
int isofs_getattr __P((struct vop_getattr_args *));
int isofs_read __P((struct vop_read_args *));
int isofs_ioctl __P((struct vop_ioctl_args *));
int isofs_select __P((struct vop_select_args *));
int isofs_mmap __P((struct vop_mmap_args *));
int isofs_seek __P((struct vop_seek_args *));
int isofs_readdir __P((struct vop_readdir_args *));
int isofs_abortop __P((struct vop_abortop_args *));
int isofs_inactive __P((struct vop_inactive_args *));
int isofs_reclaim __P((struct vop_reclaim_args *));
int isofs_bmap __P((struct vop_bmap_args *));
int isofs_lock __P((struct vop_lock_args *));
int isofs_unlock __P((struct vop_unlock_args *));
int isofs_strategy __P((struct vop_strategy_args *));
int isofs_print __P((struct vop_print_args *));
int isofs_islocked __P((struct vop_islocked_args *));
void isofs_defattr __P((struct iso_directory_record *,
E 2
I 2
int cd9660_lookup __P((struct vop_lookup_args *));
int cd9660_open __P((struct vop_open_args *));
int cd9660_close __P((struct vop_close_args *));
int cd9660_access __P((struct vop_access_args *));
int cd9660_getattr __P((struct vop_getattr_args *));
int cd9660_read __P((struct vop_read_args *));
int cd9660_ioctl __P((struct vop_ioctl_args *));
int cd9660_select __P((struct vop_select_args *));
int cd9660_mmap __P((struct vop_mmap_args *));
int cd9660_seek __P((struct vop_seek_args *));
int cd9660_readdir __P((struct vop_readdir_args *));
int cd9660_abortop __P((struct vop_abortop_args *));
int cd9660_inactive __P((struct vop_inactive_args *));
int cd9660_reclaim __P((struct vop_reclaim_args *));
int cd9660_bmap __P((struct vop_bmap_args *));
int cd9660_lock __P((struct vop_lock_args *));
int cd9660_unlock __P((struct vop_unlock_args *));
int cd9660_strategy __P((struct vop_strategy_args *));
int cd9660_print __P((struct vop_print_args *));
int cd9660_islocked __P((struct vop_islocked_args *));
I 4
int cd9660_pathconf __P((struct vop_pathconf_args *));
int cd9660_blkatoff __P((struct vop_blkatoff_args *));
I 5
#define cd9660_revoke vop_revoke
E 5

E 4
void cd9660_defattr __P((struct iso_directory_record *,
E 2
			struct iso_node *, struct buf *));
D 2
void isofs_deftstamp __P((struct iso_directory_record *,
E 2
I 2
void cd9660_deftstamp __P((struct iso_directory_record *,
E 2
			struct iso_node *, struct buf *));
I 3
struct vnode *cd9660_ihashget __P((dev_t, ino_t));
void cd9660_ihashins __P((struct iso_node *));
void cd9660_ihashrem __P((struct iso_node *));
I 4
int cd9660_tstamp_conv7 __P((u_char *, struct timespec *));
int cd9660_tstamp_conv17 __P((u_char *, struct timespec *));
ino_t isodirino __P((struct iso_directory_record *, struct iso_mnt *));
E 4
E 3
#ifdef	ISODEVMAP
struct iso_dnode *iso_dmap __P((dev_t, ino_t, int));
void iso_dunmap __P((dev_t));
#endif
E 1
