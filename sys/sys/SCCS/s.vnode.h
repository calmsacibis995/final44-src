h55803
s 00002/00001/00409
d D 8.17 95/05/20 16:33:40 mckusick 90 89
c add v_vnlock for non-locking filesystems
e
s 00047/00006/00363
d D 8.16 95/05/14 00:09:18 mckusick 89 88
c add interlock; add vn_lock, vrecycle, and vop_nolock* functions
e
s 00002/00001/00367
d D 8.15 95/03/22 14:55:46 mckusick 88 87
c add exclusive create flag for passing to VOP_CREATE
e
s 00002/00001/00366
d D 8.14 95/02/23 11:28:37 mckusick 87 84
c vgoneall is replaced by vop_revoke; add REVOKEALL flag
e
s 00001/00001/00366
d R 8.14 95/02/22 20:57:31 mckusick 86 84
c vgoneall is replaced by vop_revoke
e
s 00000/00001/00366
d R 8.14 95/02/22 18:43:17 mckusick 85 84
c vgoneall is replaced by vop_revoke
e
s 00003/00000/00364
d D 8.13 95/02/19 07:50:45 cgd 84 83
c add protos for cvtstat and insmntque.
e
s 00005/00003/00359
d D 8.12 95/01/09 18:16:23 cgd 83 82
c 64-bit changes: ioctl cmd -> u_long, some protos.  some style, return vals.
e
s 00001/00000/00361
d D 8.11 94/11/21 14:38:23 mckusick 82 81
c add VISTTY flag to identify tty vnodes
e
s 00000/00006/00361
d D 8.10 94/08/10 23:13:25 mckusick 81 80
c move NFS specific call to kern_time.c
e
s 00000/00004/00367
d D 8.9 94/08/10 22:57:11 mckusick 80 79
c LEASE_CHECK => VOP_LEASE
e
s 00000/00000/00371
d D 8.8 94/07/28 03:39:31 pendry 79 78
c changes for whiteouts and union filesystem
e
s 00002/00001/00369
d D 8.7 94/02/04 10:51:52 pendry 78 77
c added VT_UNION
e
s 00003/00002/00367
d D 8.6 94/01/12 14:32:13 hibler 77 76
c new v_maxra field for clustering,
c add VT_ISOFS.
e
s 00004/00001/00365
d D 8.5 94/01/04 17:16:14 pendry 76 75
c add remaining vtagtypes
e
s 00001/00001/00365
d D 8.4 93/12/14 00:46:27 mckusick 75 74
c vget needs to take a flag on whether to lock the vnode
e
s 00007/00007/00359
d D 8.3 93/12/13 23:44:20 mckusick 74 73
c convert vnode freelist, mount point list, and clean and dirty buffer lists
c to use the <sys/queue.h> macros
e
s 00001/00001/00365
d D 8.2 93/09/05 09:43:15 bostic 73 72
c Cleanups for 4.4BSD-Lite
e
s 00002/00002/00364
d D 8.1 93/06/02 19:57:01 bostic 72 71
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00003/00366
d D 7.69 93/05/07 14:52:59 mckusick 71 70
c no need to include endian.h as it is brought in by types.h
e
s 00001/00000/00368
d D 7.68 93/03/19 14:34:26 hibler 70 69
c add another long to vattr struct to keep it quad aligned
e
s 00001/00001/00367
d D 7.67 93/03/08 10:27:27 bostic 69 68
c rename va_cflags -> va_vaflags
e
s 00006/00000/00362
d D 7.66 93/03/05 17:22:46 bostic 68 67
c make utime(NULL) work for POSIX 1003.1 compatibility
e
s 00001/00001/00361
d D 7.65 93/02/02 20:50:34 mckusick 67 66
c add two parameters to vinvalbuf to allow interruptable sleeps
e
s 00006/00001/00356
d D 7.64 92/12/09 16:03:04 margo 66 65
c add read/write cluster fields
e
s 00002/00001/00355
d D 7.63 92/11/15 21:53:05 mckusick 65 64
c add vflush flag WRITECLOSE to close only writable vnodes
e
s 00021/00020/00335
d D 7.62 92/10/22 22:52:48 mckusick 64 63
c use new queue conventions
e
s 00002/00000/00353
d D 7.61 92/10/07 17:24:03 margo 63 62
c Add vinvalbuf flags.
e
s 00003/00001/00350
d D 7.60 92/07/24 11:26:40 bostic 62 61
c fix public/private declarations for fstat
e
s 00001/00000/00350
d D 7.59 92/07/23 17:53:15 bostic 61 60
c predeclare strust stat
e
s 00002/00001/00348
d D 7.58 92/07/23 17:16:10 bostic 60 59
c vnode_if.h now in compile directory, add vn_stat prototype
e
s 00008/00001/00341
d D 7.57 92/07/12 13:12:31 heideman 59 58
c add flags to describe WILLRELE info
e
s 00003/00001/00339
d D 7.56 92/06/25 12:49:22 mckusick 58 57
c use S_IFMT in place of IFMT to use sys/stat.h instead of ufs/ufs/dinode.h
e
s 00001/00000/00339
d D 7.55 92/06/23 00:09:40 bostic 57 56
c add VDIROP flags; flags if vnode part of an LFS directory op
e
s 00002/00011/00337
d D 7.54 92/06/19 23:12:25 mckusick 56 55
c get rid of the fiction of NOQUAD
e
s 00003/00003/00345
d D 7.53 92/06/18 18:16:12 mckusick 55 54
c timeval => timespec
e
s 00075/00090/00273
d D 7.52 92/06/08 14:18:01 bostic 54 53
c fix prototypes so fstat will compile; other cleanups, nothing major
e
s 00155/00152/00208
d D 7.51 92/05/15 15:37:00 heideman 53 52
c vnode interface conversion
e
s 00007/00004/00353
d D 7.50 92/05/13 14:45:21 mckusick 52 51
c 32-bit dev's; more prototypes
e
s 00003/00003/00354
d D 7.49 92/04/21 13:34:17 mckusick 51 49
c VOP_TRUNCATE now takes a cred argument
e
s 00002/00002/00355
d R 7.49 92/04/21 13:07:35 mckusick 50 49
c VOP_TRUNCATE now takes a credential argument
e
s 00002/00002/00355
d D 7.48 92/04/21 10:28:20 mckusick 49 48
c v_lastr is a daddr_t, truncate length is off_t not u_long
e
s 00010/00000/00347
d D 7.47 92/02/04 15:37:21 mckusick 48 47
c move IFMT => VTYPE and VTYPE => IFMT to vnode since stat requires it
e
s 00001/00002/00346
d D 7.46 92/02/03 23:22:19 mckusick 47 46
c no longer pass proc to vn_open as a parameter (now in ndp)
e
s 00037/00027/00311
d D 7.45 92/01/22 15:41:49 heideman 46 45
c works with lookup converted
e
s 00019/00001/00319
d D 7.44 92/01/14 12:00:48 mckusick 45 43
c add support for NFS leases
e
s 00018/00001/00319
d R 7.44 92/01/09 21:59:00 mckusick 44 43
c support for leases
e
s 00011/00012/00309
d D 7.43 91/12/19 12:42:31 mckusick 43 42
c quad => quad_t; select va_size based on _NOQUAD support
e
s 00005/00006/00316
d D 7.42 91/12/16 15:21:16 mckusick 42 41
c eliminate private area and let filesystems allocate their own space
e
s 00019/00000/00303
d D 7.41 91/11/05 15:25:27 mckusick 41 40
c reorganization to move ufsmount ops to be vnode ops; add new ops
e
s 00044/00048/00259
d D 7.40 91/11/01 16:29:23 bostic 40 39
c LFS version 1
e
s 00001/00000/00306
d D 7.39 91/06/27 12:00:47 mckusick 39 38
c add vn_closefile to avoid warnings about void * coersions
e
s 00004/00002/00302
d D 7.38 91/06/21 10:53:44 mckusick 38 37
c new calling convention for vn_close; 
c maintain count of references for writing on vnode
e
s 00066/00066/00238
d D 7.37 91/05/16 18:59:43 mckusick 37 36
c change vn_ to vop_ (for marc :-)
e
s 00003/00002/00301
d D 7.36 91/05/07 19:56:19 karels 36 35
c fix format; #ifdef __STDC__ for structure declarations
c (even though probably not necessary)
e
s 00097/00207/00206
d D 7.35 91/05/04 15:03:59 karels 35 34
c reformat prototypes, etc. to standard style
e
s 00002/00001/00411
d D 7.34 91/04/19 17:03:16 mckusick 34 33
c add VXLOCK as condition making VOP_ISLOCKED true
e
s 00250/00103/00162
d D 7.33 91/04/15 23:31:07 mckusick 33 32
c add prototypes for vnode ops; add proc pointer to many vnode ops;
c add prototypes for exported vnode routines
e
s 00003/00006/00262
d D 7.32 91/02/01 16:13:35 mckusick 32 31
c add POSIX-style byte-level record locking
e
s 00002/00002/00266
d D 7.31 90/12/05 15:52:51 mckusick 31 30
c update for new VM
e
s 00001/00011/00267
d D 7.30 90/06/28 22:02:04 bostic 30 29
c new copyright notice
e
s 00002/00002/00276
d D 7.29 90/05/10 13:28:10 mckusick 29 28
c size and bytes should be unsigned quads
e
s 00006/00003/00272
d D 7.28 90/05/03 18:46:06 mckusick 28 27
c add VATTR_NULL as shorthand for vattr_null
e
s 00016/00007/00259
d D 7.27 90/05/02 19:22:40 mckusick 27 26
c define vflush flags; add NULLVP; shuffle flags
e
s 00001/00003/00265
d D 7.26 90/04/10 20:39:46 mckusick 26 25
c vnodes are now dynamically allocated
e
s 00000/00020/00268
d D 7.25 90/03/27 19:26:02 mckusick 25 24
c specinfo structure moved to specdev.h
e
s 00015/00004/00273
d D 7.24 90/03/27 15:38:14 mckusick 24 23
c va_size and va_bytes become quads
e
s 00008/00000/00269
d D 7.23 90/03/08 17:16:05 mckusick 23 22
c add flags field to specinfo to mark mounted block devices
e
s 00002/00002/00267
d D 7.22 90/03/05 18:04:26 mckusick 22 21
c readdir now takes a fourth argument (from macklem)
e
s 00001/00001/00268
d D 7.21 90/02/21 00:07:47 mckusick 21 20
c VOP_SELECT needs the file flags
e
s 00003/00003/00266
d D 7.20 90/02/19 18:27:02 mckusick 20 19
c add support for FIFO's
e
s 00002/00000/00267
d D 7.19 90/01/14 10:44:15 mckusick 19 18
c add VOP_ISLOCKED to test for underlying object locked
e
s 00012/00011/00255
d D 7.18 90/01/04 16:13:01 mckusick 18 17
c add dirty buffer list
e
s 00016/00011/00250
d D 7.17 89/12/30 22:21:15 mckusick 17 16
c v_count =>v_usecount; add v_refcount, v_lastr, two spares;
c specinfo loses si_lastr, si_mounton, but gains si_hashchain;
c add VHOLD and HOLDRELE macros to manipulate v_refcount
e
s 00004/00000/00257
d D 7.16 89/12/29 09:27:23 mckusick 16 15
c debugging, force VREF to call vref so that we can check on usage
e
s 00003/00000/00254
d D 7.15 89/11/30 11:17:40 mckusick 15 14
c add an operation to print contents of a vnode
e
s 00002/00001/00252
d D 7.14 89/11/25 23:31:14 mckusick 14 13
c add new public functions delete old functions
e
s 00019/00002/00234
d D 7.13 89/11/25 21:40:39 mckusick 13 12
c VBLK and VCHR now maintain additional state in a specinfo structure
e
s 00001/00001/00235
d D 7.12 89/11/22 22:42:30 mckusick 12 11
c FSYNC now takes a waitfor flag
e
s 00001/00001/00235
d D 7.11 89/11/21 22:42:15 mckusick 11 10
c READDIR no longer takes an offp
e
s 00002/00002/00234
d D 7.10 89/11/21 21:18:48 mckusick 10 9
c VOP_READ and VOP_WRITE no longer take an offset pointer
e
s 00010/00004/00226
d D 7.9 89/10/29 23:06:18 mckusick 9 8
c define the rest of the public vnode functions
e
s 00002/00000/00228
d D 7.8 89/10/26 12:14:56 mckusick 8 7
c have to add locking so that underlying type can be changed
e
s 00001/00000/00227
d D 7.7 89/10/26 01:34:44 mckusick 7 6
c add new public function
e
s 00003/00001/00224
d D 7.6 89/10/24 18:21:05 mckusick 6 5
c link together all buffers associated with a particular vnode
e
s 00034/00018/00191
d D 7.5 89/10/24 18:17:33 mckusick 5 4
c merge inode and nfsnode tables into a single vnode table;
c link together all vnodes associated with a particular mount point
e
s 00001/00000/00208
d D 7.4 89/08/25 21:35:12 mckusick 4 3
c add v_id as capability identifier
e
s 00001/00000/00207
d D 7.3 89/06/27 22:22:31 mckusick 3 2
c add VREF macro
e
s 00002/00000/00205
d D 7.2 89/06/06 17:55:57 mckusick 2 1
c return file flags and generation number
e
s 00205/00000/00000
d D 7.1 89/05/09 16:34:11 mckusick 1 0
c first bootable vnodes
e
u
U
t
T
I 1
/*
D 72
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 72
I 72
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 72
 *
D 30
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
E 30
I 30
 * %sccs.include.redist.c%
E 30
 *
 *	%W% (Berkeley) %G%
 */

I 89
#include <sys/lock.h>
E 89
I 33
D 71
#ifndef KERNEL
E 33
I 24
#include <machine/endian.h>
I 33
#endif
E 71
I 64
#include <sys/queue.h>
E 64
E 33

E 24
/*
D 40
 * The vnode is the focus of all file activity in UNIX.
 * There is a unique vnode allocated for each active file,
 * each current directory, each mounted-on file, text file, and the root.
E 40
I 40
D 54
 * The vnode is the focus of all file activity in UNIX.  There is a unique
 * vnode allocated for each active file, each current directory, each
 * mounted-on file, text file, and the root.
E 54
I 54
 * The vnode is the focus of all file activity in UNIX.  There is a
 * unique vnode allocated for each active file, each current directory,
 * each mounted-on file, text file, and the root.
E 54
E 40
 */

/*
D 54
 * vnode types. VNON means no type.
E 54
I 54
 * Vnode types.  VNON means no type.
E 54
 */
D 20
enum vtype 	{ VNON, VREG, VDIR, VBLK, VCHR, VLNK, VSOCK, VBAD };
E 20
I 20
D 54
enum vtype 	{ VNON, VREG, VDIR, VBLK, VCHR, VLNK, VSOCK, VFIFO, VBAD };
E 54
I 54
enum vtype	{ VNON, VREG, VDIR, VBLK, VCHR, VLNK, VSOCK, VFIFO, VBAD };
E 54
E 20

I 5
/*
 * Vnode tag types.
 * These are for the benefit of external programs only (e.g., pstat)
D 54
 * and should NEVER be inspected inside the kernel.
E 54
I 54
 * and should NEVER be inspected by the kernel.
E 54
 */
D 40
enum vtagtype	{ VT_NON, VT_UFS, VT_NFS, VT_MFS };
E 40
I 40
D 76
enum vtagtype	{ VT_NON, VT_UFS, VT_NFS, VT_MFS, VT_LFS };
E 76
I 76
enum vtagtype	{
	VT_NON, VT_UFS, VT_NFS, VT_MFS, VT_PC, VT_LFS, VT_LOFS, VT_FDESC,
D 77
	VT_PORTAL, VT_NULL, VT_UMAP, VT_KERNFS, VT_PROCFS, VT_AFS
E 77
I 77
D 78
	VT_PORTAL, VT_NULL, VT_UMAP, VT_KERNFS, VT_PROCFS, VT_AFS, VT_ISOFS
E 78
I 78
	VT_PORTAL, VT_NULL, VT_UMAP, VT_KERNFS, VT_PROCFS, VT_AFS, VT_ISOFS,
	VT_UNION
E 78
E 77
};
E 76
E 40

/*
D 40
 * This defines the maximum size of the private data area
 * permitted for any file system type. A defined constant 
 * is used rather than a union structure to cut down on the
 * number of header files that must be included.
E 40
I 40
D 42
 * This defines the maximum size of the private data area for any file system
 * type.  A defined constant is used rather than a union structure to reduce
 * the number of header files that must be included.
E 42
I 42
 * Each underlying filesystem allocates its own private area and hangs
D 54
 * it from v_data. If non-null, this area is free in getnewvnode().
E 54
I 54
D 74
 * it from v_data.  If non-null, this area is free in getnewvnode().
E 74
I 74
 * it from v_data.  If non-null, this area is freed in getnewvnode().
E 74
E 54
E 42
E 40
 */
I 74
LIST_HEAD(buflists, buf);

I 89
/*
 * Reading or writing any of these items requires holding the appropriate lock.
 * v_freelist is locked by the global vnode_free_list simple lock.
 * v_mntvnodes is locked by the global mntvnodes simple lock.
 * v_flag, v_usecount, v_holdcount and v_writecount are
 *    locked by the v_interlock simple lock.
 */
E 89
E 74
D 6
#define VN_MAXPRIVATE	204
E 6
I 6
D 17
#define VN_MAXPRIVATE	196
E 17
I 17
D 32
#define VN_MAXPRIVATE	184
E 32
I 32
D 35
#define VN_MAXPRIVATE	188
E 35
I 35
D 42
#define	VN_MAXPRIVATE	188
E 35
E 32
E 17
E 6

E 42
E 5
struct vnode {
D 64
	u_long		v_flag;			/* vnode flags (see below) */
D 17
	long		v_count;		/* reference count */
E 17
I 17
D 38
	long		v_usecount;		/* reference count of users */
E 38
I 38
	short		v_usecount;		/* reference count of users */
	short		v_writecount;		/* reference count of writers */
E 38
	long		v_holdcnt;		/* page & buffer references */
E 17
D 32
	u_short		v_shlockc;		/* count of shared locks */
	u_short		v_exlockc;		/* count of exclusive locks */
E 32
I 17
D 49
	off_t		v_lastr;		/* last read (read-ahead) */
E 49
I 49
	daddr_t		v_lastr;		/* last read (read-ahead) */
E 49
	u_long		v_id;			/* capability identifier */
E 17
	struct mount	*v_mount;		/* ptr to vfs we are in */
D 53
	struct vnodeops	*v_op;			/* vnode operations */
E 53
I 53
	int 		(**v_op)();		/* vnode operations vector */
E 53
I 4
D 17
	u_long		v_id;			/* capability identifier */
E 17
I 5
	struct vnode	*v_freef;		/* vnode freelist forward */
	struct vnode	**v_freeb;		/* vnode freelist back */
	struct vnode	*v_mountf;		/* vnode mountlist forward */
	struct vnode	**v_mountb;		/* vnode mountlist back */
I 6
D 18
	struct buf	*v_blockh;		/* logical blocklist head */
D 17
	struct buf	**v_blockt;		/* logical blocklist tail */
E 17
I 17
	long		v_spare0;
	long		v_spare1;
E 18
I 18
	struct buf	*v_cleanblkhd;		/* clean blocklist head */
	struct buf	*v_dirtyblkhd;		/* dirty blocklist head */
	long		v_numoutput;		/* num of writes in progress */
E 18
E 17
E 6
E 5
E 4
	enum vtype	v_type;			/* vnode type */
E 64
I 64
	u_long	v_flag;				/* vnode flags (see below) */
	short	v_usecount;			/* reference count of users */
	short	v_writecount;			/* reference count of writers */
	long	v_holdcnt;			/* page & buffer references */
	daddr_t	v_lastr;			/* last read (read-ahead) */
	u_long	v_id;				/* capability identifier */
	struct	mount *v_mount;			/* ptr to vfs we are in */
	int 	(**v_op)();			/* vnode operations vector */
D 74
	struct	vnode *v_freef;			/* vnode freelist forward */
	struct	vnode **v_freeb;		/* vnode freelist back */
	struct	vnode *v_mountf;		/* vnode mountlist forward */
	struct	vnode **v_mountb;		/* vnode mountlist back */
	struct	list_entry v_cleanblkhd;	/* clean blocklist head */
	struct	list_entry v_dirtyblkhd;	/* dirty blocklist head */
E 74
I 74
	TAILQ_ENTRY(vnode) v_freelist;		/* vnode freelist */
	LIST_ENTRY(vnode) v_mntvnodes;		/* vnodes for mount point */
	struct	buflists v_cleanblkhd;		/* clean blocklist head */
	struct	buflists v_dirtyblkhd;		/* dirty blocklist head */
E 74
	long	v_numoutput;			/* num of writes in progress */
	enum	vtype v_type;			/* vnode type */
E 64
	union {
		struct mount	*vu_mountedhere;/* ptr to mounted vfs (VDIR) */
		struct socket	*vu_socket;	/* unix ipc (VSOCK) */
D 31
		struct text	*vu_text;	/* text/mapped region (VREG) */
E 31
I 31
D 33
		caddr_t		vu_vmdata;	/* private data for vm */
E 33
I 33
		caddr_t		vu_vmdata;	/* private data for vm (VREG) */
E 33
E 31
D 13
		dev_t		vu_rdev;	/* device (VCHR, VBLK) */
E 13
I 13
		struct specinfo	*vu_specinfo;	/* device (VCHR, VBLK) */
I 20
		struct fifoinfo	*vu_fifoinfo;	/* fifo (VFIFO) */
E 20
E 13
	} v_un;
I 42
D 45
	long		v_spare[14];		/* round to 128 bytes */
E 45
I 45
D 64
	struct nqlease	*v_lease;		/* Soft reference to lease */
	long		v_spare[13];		/* round to 128 bytes */
E 45
E 42
D 5
	qaddr_t		v_data;			/* private data for fs */
E 5
I 5
	enum vtagtype	v_tag;			/* type of underlying data */
D 42
	char v_data[VN_MAXPRIVATE];		/* private data for fs */
E 42
I 42
	void 		*v_data;		/* private data for fs */
E 64
I 64
	struct	nqlease *v_lease;		/* Soft reference to lease */
D 66
	long	v_spare[13];			/* round to 128 bytes */
E 66
I 66
	daddr_t	v_lastw;			/* last write (write cluster) */
	daddr_t	v_cstart;			/* start block of cluster */
	daddr_t	v_lasta;			/* last allocation */
	int	v_clen;				/* length of current cluster */
	int	v_ralen;			/* Read-ahead length */
D 77
	long	v_spare[8];			/* round to 128 bytes */
E 77
I 77
	daddr_t	v_maxra;			/* last readahead block */
D 89
	long	v_spare[7];			/* round to 128 bytes */
E 89
I 89
	struct	simplelock v_interlock;		/* lock on usecount and flag */
D 90
	long	v_spare[6];			/* round to 128 bytes */
E 90
I 90
	struct	lock *v_vnlock;			/* used for non-locking fs's */
	long	v_spare[5];			/* round to 128 bytes */
E 90
E 89
E 77
E 66
	enum	vtagtype v_tag;			/* type of underlying data */
	void 	*v_data;			/* private data for fs */
E 64
E 42
E 5
};
D 35
#define v_mountedhere v_un.vu_mountedhere
#define v_socket v_un.vu_socket
D 31
#define v_text v_un.vu_text
E 31
I 31
#define v_vmdata v_un.vu_vmdata
E 31
D 13
#define v_rdev v_un.vu_rdev
E 13
I 13
#define v_specinfo v_un.vu_specinfo
I 20
#define v_fifoinfo v_un.vu_fifoinfo
E 35
I 35
#define	v_mountedhere	v_un.vu_mountedhere
#define	v_socket	v_un.vu_socket
#define	v_vmdata	v_un.vu_vmdata
#define	v_specinfo	v_un.vu_specinfo
#define	v_fifoinfo	v_un.vu_fifoinfo
E 35
E 20
E 13

/*
D 54
 * vnode flags.
E 54
I 54
 * Vnode flags.
E 54
 */
D 18
#define	VROOT		0x01	/* root of its file system */
#define	VTEXT		0x02	/* vnode is a pure text prototype */
I 8
#define VXLOCK		0x04	/* vnode is locked to change underlying type */
#define VXWANT		0x08	/* process is waiting for vnode */
E 8
#define	VEXLOCK		0x10	/* exclusive lock */
#define	VSHLOCK		0x20	/* shared lock */
#define	VLWAIT		0x40	/* proc is waiting on shared or excl. lock */
I 13
#define	VALIASED	0x80	/* vnode has an alias */
E 18
I 18
#define	VROOT		0x0001	/* root of its file system */
#define	VTEXT		0x0002	/* vnode is a pure text prototype */
D 27
#define	VXLOCK		0x0004	/* vnode is locked to change underlying type */
#define	VXWANT		0x0008	/* process is waiting for vnode */
E 27
I 27
#define	VSYSTEM		0x0004	/* vnode being used by kernel */
I 82
#define	VISTTY		0x0008	/* vnode represents a tty */
E 82
E 27
D 32
#define	VEXLOCK		0x0010	/* exclusive lock */
#define	VSHLOCK		0x0020	/* shared lock */
#define	VLWAIT		0x0040	/* proc is waiting on shared or excl. lock */
E 32
D 27
#define	VALIASED	0x0080	/* vnode has an alias */
#define	VBWAIT		0x0100	/* waiting for output to complete */
E 27
I 27
#define	VXLOCK		0x0100	/* vnode is locked to change underlying type */
#define	VXWANT		0x0200	/* process is waiting for vnode */
#define	VBWAIT		0x0400	/* waiting for output to complete */
#define	VALIASED	0x0800	/* vnode has an alias */
I 57
#define	VDIROP		0x1000	/* LFS: vnode is involved in a directory op */
E 57
E 27
E 18
E 13

/*
D 33
 * Operations on vnodes.
 */
struct vnodeops {
	int	(*vn_lookup)(		/* ndp */ );
	int	(*vn_create)(		/* ndp, fflags, vap, cred */ );
	int	(*vn_mknod)(		/* ndp, vap, cred */ );
	int	(*vn_open)(		/* vp, fflags, cred */ );
	int	(*vn_close)(		/* vp, fflags, cred */ );
	int	(*vn_access)(		/* vp, fflags, cred */ );
	int	(*vn_getattr)(		/* vp, vap, cred */ );
	int	(*vn_setattr)(		/* vp, vap, cred */ );

	int	(*vn_read)(		/* vp, uiop, offp, ioflag, cred */ );
	int	(*vn_write)(		/* vp, uiop, offp, ioflag, cred */ );
	int	(*vn_ioctl)(		/* vp, com, data, fflag, cred */ );
	int	(*vn_select)(		/* vp, which, cred */ );
	int	(*vn_mmap)(		/* vp, ..., cred */ );
	int	(*vn_fsync)(		/* vp, fflags, cred */ );
	int	(*vn_seek)(		/* vp, (old)offp, off, whence */ );

	int	(*vn_remove)(		/* ndp */ );
	int	(*vn_link)(		/* vp, ndp */ );
	int	(*vn_rename)(		/* ndp, ndp */ );
	int	(*vn_mkdir)(		/* ndp, vap */ );
	int	(*vn_rmdir)(		/* ndp */ );
	int	(*vn_symlink)(		/* ndp, vap, nm */ );
D 22
	int	(*vn_readdir)(		/* vp, uiop, ioflag, cred */ );
E 22
I 22
	int	(*vn_readdir)(		/* vp, uiop, cred, eofflagp */ );
E 22
	int	(*vn_readlink)(		/* vp, uiop, cred */ );

	int	(*vn_abortop)(		/* ndp */ );
	int	(*vn_inactive)(		/* vp */ );
I 5
	int	(*vn_reclaim)(		/* vp */ );
E 5
	int	(*vn_lock)(		/* vp */ );
	int	(*vn_unlock)(		/* vp */ );

	int	(*vn_bmap)(		/* vp, bn, vpp, bnp */ );
	int	(*vn_strategy)(		/* bp */ );
I 15

	int	(*vn_print)(		/* vp */ );
I 19
	int	(*vn_islocked)(		/* vp */ );
I 32
	int	(*vn_advlock)(		/* vp, proc, op, lck, flg */ );
E 32
E 19
E 15
};

/* Macros to call the vnode ops */
#define	VOP_LOOKUP(v,n)		(*((v)->v_op->vn_lookup))((v),(n))
#define	VOP_CREATE(n,a)		(*((n)->ni_dvp->v_op->vn_create))((n),(a))
#define	VOP_MKNOD(n,a,c)	(*((n)->ni_dvp->v_op->vn_mknod))((n),(a),(c))
#define	VOP_OPEN(v,f,c)		(*((v)->v_op->vn_open))((v),(f),(c))
#define	VOP_CLOSE(v,f,c)	(*((v)->v_op->vn_close))((v),(f),(c))
#define	VOP_ACCESS(v,f,c)	(*((v)->v_op->vn_access))((v),(f),(c))
#define	VOP_GETATTR(v,a,c)	(*((v)->v_op->vn_getattr))((v),(a),(c))
#define	VOP_SETATTR(v,a,c)	(*((v)->v_op->vn_setattr))((v),(a),(c))
D 10
#define	VOP_READ(v,u,o,i,c)	(*((v)->v_op->vn_read))((v),(u),(o),(i),(c))
#define	VOP_WRITE(v,u,o,i,c)	(*((v)->v_op->vn_write))((v),(u),(o),(i),(c))
E 10
I 10
#define	VOP_READ(v,u,i,c)	(*((v)->v_op->vn_read))((v),(u),(i),(c))
#define	VOP_WRITE(v,u,i,c)	(*((v)->v_op->vn_write))((v),(u),(i),(c))
E 10
#define	VOP_IOCTL(v,o,d,f,c)	(*((v)->v_op->vn_ioctl))((v),(o),(d),(f),(c))
D 21
#define	VOP_SELECT(v,w,c)	(*((v)->v_op->vn_select))((v),(w),(c))
E 21
I 21
#define	VOP_SELECT(v,w,f,c)	(*((v)->v_op->vn_select))((v),(w),(f),(c))
E 21
#define	VOP_MMAP(v,c)		(*((v)->v_op->vn_mmap))((v),(c))
D 12
#define	VOP_FSYNC(v,f,c)	(*((v)->v_op->vn_fsync))((v),(f),(c))
E 12
I 12
#define	VOP_FSYNC(v,f,c,w)	(*((v)->v_op->vn_fsync))((v),(f),(c),(w))
E 12
#define	VOP_SEEK(v,p,o,w)	(*((v)->v_op->vn_seek))((v),(p),(o),(w))
#define	VOP_REMOVE(n)		(*((n)->ni_dvp->v_op->vn_remove))(n)
#define	VOP_LINK(v,n)		(*((n)->ni_dvp->v_op->vn_link))((v),(n))
#define	VOP_RENAME(s,t)		(*((s)->ni_dvp->v_op->vn_rename))((s),(t))
#define	VOP_MKDIR(n,a)		(*((n)->ni_dvp->v_op->vn_mkdir))((n),(a))
#define	VOP_RMDIR(n)		(*((n)->ni_dvp->v_op->vn_rmdir))(n)
#define	VOP_SYMLINK(n,a,m)	(*((n)->ni_dvp->v_op->vn_symlink))((n),(a),(m))
D 11
#define	VOP_READDIR(v,u,i,c)	(*((v)->v_op->vn_readdir))((v),(u),(i),(c))
E 11
I 11
D 22
#define	VOP_READDIR(v,u,c)	(*((v)->v_op->vn_readdir))((v),(u),(c))
E 22
I 22
#define	VOP_READDIR(v,u,c,e)	(*((v)->v_op->vn_readdir))((v),(u),(c),(e))
E 22
E 11
#define	VOP_READLINK(v,u,c)	(*((v)->v_op->vn_readlink))((v),(u),(c))
#define	VOP_ABORTOP(n)		(*((n)->ni_dvp->v_op->vn_abortop))(n)
#define	VOP_INACTIVE(v)		(*((v)->v_op->vn_inactive))(v)
I 5
#define	VOP_RECLAIM(v)		(*((v)->v_op->vn_reclaim))(v)
E 5
#define	VOP_LOCK(v)		(*((v)->v_op->vn_lock))(v)
#define	VOP_UNLOCK(v)		(*((v)->v_op->vn_unlock))(v)
#define	VOP_BMAP(v,s,p,n)	(*((v)->v_op->vn_bmap))((v),(s),(p),(n))
#define	VOP_STRATEGY(b)		(*((b)->b_vp->v_op->vn_strategy))(b)
I 15
#define	VOP_PRINT(v)		(*((v)->v_op->vn_print))(v)
I 19
#define	VOP_ISLOCKED(v)		(*((v)->v_op->vn_islocked))(v)
I 32
#define	VOP_ADVLOCK(v,p,o,l,f)	(*((v)->v_op->vn_advlock))((v),(p),(o),(l),(f))
E 32
E 19
E 15
I 13

/*
D 25
 * This structure defines the information maintained about
 * special devices. It is allocated in checkalias and freed
 * in vgone.
 */
struct specinfo {
D 17
	dev_t	si_rdev;
	daddr_t	si_lastr;
	struct	mount *si_mounton;
E 17
I 17
	struct	vnode **si_hashchain;
E 17
	struct	vnode *si_specnext;
I 23
	long	si_flags;
E 23
I 17
	dev_t	si_rdev;
E 17
};
I 23
/*
 * Exported shorthand
 */
E 23
D 17
#define v_rdev v_specinfo->si_rdev
#define v_lastr v_specinfo->si_lastr
#define v_mounton v_specinfo->si_mounton
E 17
I 17
D 20
#define v_hashchain v_specinfo->si_hashchain
E 17
#define v_specnext v_specinfo->si_specnext
E 20
I 17
#define v_rdev v_specinfo->si_rdev
I 23
/*
 * Flags for specinfo
 */
#define	SI_MOUNTEDON	0x0001	/* block special device is mounted on */
E 23
E 17
E 13

/*
E 25
 * flags for ioflag
 */
D 5
#define IO_ATOMIC	0x01		/* do io as atomic unit for VOP_RDWR */
#define IO_APPEND	0x02		/* append write for VOP_RDWR */
#define IO_SYNC		0x04		/* sync io for VOP_RDWR */
E 5
I 5
#define IO_UNIT		0x01		/* do I/O as atomic unit */
#define IO_APPEND	0x02		/* append write to end */
#define IO_SYNC		0x04		/* do I/O synchronously */
E 5
#define	IO_NODELOCKED	0x08		/* underlying node already locked */
#define	IO_NDELAY	0x10		/* FNDELAY flag set in file table */

D 5
#define IO_UNIT		IO_ATOMIC	/* compat */

E 5
/*
E 33
D 40
 * Vnode attributes.  A field value of VNOVAL
 * represents a field whose value is unavailable
 * (getattr) or which is not to be changed (setattr).
E 40
I 40
 * Vnode attributes.  A field value of VNOVAL represents a field whose value
 * is unavailable (getattr) or which is not to be changed (setattr).
E 40
 */
struct vattr {
	enum vtype	va_type;	/* vnode type (for create) */
	u_short		va_mode;	/* files access mode and type */
	short		va_nlink;	/* number of references to file */
	uid_t		va_uid;		/* owner user id */
	gid_t		va_gid;		/* owner group id */
	long		va_fsid;	/* file system id (dev for now) */
	long		va_fileid;	/* file id */
D 24
	u_long		va_size;	/* file size in bytes (quad?) */
	u_long		va_size1;	/* reserved if not quad */
E 24
I 24
D 29
	quad		va_qsize;	/* file size in bytes */
E 29
I 29
D 43
	u_quad		va_qsize;	/* file size in bytes */
E 43
I 43
D 56
	u_quad_t	va_qsize;	/* file size in bytes */
E 56
I 56
	u_quad_t	va_size;	/* file size in bytes */
E 56
E 43
E 29
E 24
	long		va_blocksize;	/* blocksize preferred for i/o */
D 55
	struct timeval	va_atime;	/* time of last access */
	struct timeval	va_mtime;	/* time of last modification */
	struct timeval	va_ctime;	/* time file changed */
E 55
I 55
	struct timespec	va_atime;	/* time of last access */
	struct timespec	va_mtime;	/* time of last modification */
	struct timespec	va_ctime;	/* time file changed */
E 55
I 2
	u_long		va_gen;		/* generation number of file */
	u_long		va_flags;	/* flags defined for file */
E 2
	dev_t		va_rdev;	/* device the special file represents */
I 42
D 52
	short		va_pad;		/* pad out to long */
E 52
E 42
D 24
	u_long		va_bytes;	/* bytes of disk space held by file */
	u_long		va_bytes1;	/* reserved if va_bytes not a quad */
E 24
I 24
D 29
	quad		va_qbytes;	/* bytes of disk space held by file */
E 29
I 29
D 43
	u_quad		va_qbytes;	/* bytes of disk space held by file */
E 43
I 43
D 56
	u_quad_t	va_qbytes;	/* bytes of disk space held by file */
E 56
I 56
	u_quad_t	va_bytes;	/* bytes of disk space held by file */
E 56
	u_quad_t	va_filerev;	/* file modification number */
I 68
D 69
	u_int		va_cflags;	/* operations flags, see below */
E 69
I 69
	u_int		va_vaflags;	/* operations flags, see below */
I 70
	long		va_spare;	/* remain quad aligned */
E 70
E 69
E 68
E 43
E 29
E 24
};
I 68

/*
D 88
 * Flags for va_cflags.
E 88
I 88
 * Flags for va_vaflags.
E 88
 */
#define	VA_UTIMES_NULL	0x01		/* utimes argument was NULL */
I 88
#define VA_EXCLUSIVE	0x02		/* exclusive create request */
E 88
E 68
I 24
D 43
#if BYTE_ORDER == LITTLE_ENDIAN
#define	va_size		va_qsize.val[0]
#define	va_size_rsv	va_qsize.val[1]
#define	va_bytes	va_qbytes.val[0]
#define	va_bytes_rsv	va_qbytes.val[1]
E 43
I 43
D 56
#ifdef _NOQUAD
D 54
#define va_size		va_qsize.val[_QUAD_LOWWORD]
#define va_size_rsv	va_qsize.val[_QUAD_HIGHWORD]
#define va_bytes	va_qbytes.val[_QUAD_LOWWORD]
#define va_bytes_rsv	va_qbytes.val[_QUAD_HIGHWORD]
E 54
I 54
#define	va_size		va_qsize.val[_QUAD_LOWWORD]
#define	va_size_rsv	va_qsize.val[_QUAD_HIGHWORD]
#define	va_bytes	va_qbytes.val[_QUAD_LOWWORD]
#define	va_bytes_rsv	va_qbytes.val[_QUAD_HIGHWORD]
E 54
E 43
#else
D 43
#define	va_size		va_qsize.val[1]
#define	va_size_rsv	va_qsize.val[0]
#define	va_bytes	va_qbytes.val[1]
#define	va_bytes_rsv	va_qbytes.val[0]
E 43
I 43
D 54
#define va_size		va_qsize
#define va_bytes	va_qbytes
E 54
I 54
#define	va_size		va_qsize
#define	va_bytes	va_qbytes
E 54
E 43
#endif
E 56
E 24

/*
I 33
D 54
 * Operations on vnodes.
E 54
I 54
 * Flags for ioflag.
E 54
 */
I 36
D 54
#ifdef __STDC__
E 36
D 35
struct file;
E 35
struct flock;
struct nameidata;
I 46
struct componentname;
E 46
I 36
#endif
E 36
I 35

E 35
D 53
struct vnodeops {
I 40
D 46
#define	VOP_LOOKUP(v,n,p)	(*((v)->v_op->vop_lookup))(v,n,p)
E 40
D 35
	int	(*vn_lookup)__P((
			struct vnode *vp,
			struct nameidata *ndp,
			struct proc *p));
	int	(*vn_create)__P((
			struct nameidata *ndp,
			struct vattr *vap,
			struct proc *p));
	int	(*vn_mknod)__P((
			struct nameidata *ndp,
			struct vattr *vap,
			struct ucred *cred,
			struct proc *p));
	int	(*vn_open)__P((
			struct vnode *vp,
			int mode,
			struct ucred *cred,
			struct proc *p));
	int	(*vn_close)__P((
			struct vnode *vp,
			int fflag,
			struct ucred *cred,
			struct proc *p));
	int	(*vn_access)__P((
			struct vnode *vp,
			int mode,
			struct ucred *cred,
			struct proc *p));
	int	(*vn_getattr)__P((
			struct vnode *vp,
			struct vattr *vap,
			struct ucred *cred,
			struct proc *p));
	int	(*vn_setattr)__P((
			struct vnode *vp,
			struct vattr *vap,
			struct ucred *cred,
			struct proc *p));
	int	(*vn_read)__P((
			struct vnode *vp,
			struct uio *uio,
			int ioflag,
			struct ucred *cred));
	int	(*vn_write)__P((
			struct vnode *vp,
			struct uio *uio,
			int ioflag,
			struct ucred *cred));
	int	(*vn_ioctl)__P((
			struct vnode *vp,
			int command,
			caddr_t data,
			int fflag,
			struct ucred *cred,
			struct proc *p));
	int	(*vn_select)__P((
			struct vnode *vp,
			int which,
			int fflags,
			struct ucred *cred,
			struct proc *p));
	int	(*vn_mmap)__P((
			struct vnode *vp,
			int fflags,
			struct ucred *cred,
			struct proc *p));
	int	(*vn_fsync)__P((
			struct vnode *vp,
			int fflags,
			struct ucred *cred,
			int waitfor,
			struct proc *p));
	int	(*vn_seek)__P((
			struct vnode *vp,
			off_t oldoff,
			off_t newoff,
			struct ucred *cred));
	int	(*vn_remove)__P((
			struct nameidata *ndp,
			struct proc *p));
	int	(*vn_link)__P((
			struct vnode *vp,
			struct nameidata *ndp,
			struct proc *p));
	int	(*vn_rename)__P((
			struct nameidata *fndp,
			struct nameidata *tdnp,
			struct proc *p));
	int	(*vn_mkdir)__P((
			struct nameidata *ndp,
			struct vattr *vap,
			struct proc *p));
	int	(*vn_rmdir)__P((
			struct nameidata *ndp,
			struct proc *p));
	int	(*vn_symlink)__P((
			struct nameidata *ndp,
			struct vattr *vap,
			char *target,
			struct proc *p));
	int	(*vn_readdir)__P((
			struct vnode *vp,
			struct uio *uio,
			struct ucred *cred,
			int *eofflagp));
	int	(*vn_readlink)__P((
			struct vnode *vp,
			struct uio *uio,
			struct ucred *cred));
	int	(*vn_abortop)__P((
			struct nameidata *ndp));
	int	(*vn_inactive)__P((
			struct vnode *vp,
			struct proc *p));
	int	(*vn_reclaim)__P((
			struct vnode *vp));
	int	(*vn_lock)__P((
			struct vnode *vp));
	int	(*vn_unlock)__P((
			struct vnode *vp));
	int	(*vn_bmap)__P((
			struct vnode *vp,
			daddr_t bn,
			struct vnode **vpp,
			daddr_t *bnp));
	int	(*vn_strategy)__P((
			struct buf *bp));
	int	(*vn_print)__P((
			struct vnode *vp));
	int	(*vn_islocked)__P((
			struct vnode *vp));
	int	(*vn_advlock)__P((
			struct vnode *vp,
			caddr_t id,
			int op,
			struct flock *fl,
			int flags));
E 35
I 35
D 37
	int	(*vn_lookup)	__P((struct vnode *vp, struct nameidata *ndp,
E 37
I 37
	int	(*vop_lookup)	__P((struct vnode *vp, struct nameidata *ndp,
E 37
				    struct proc *p));
I 40
#define	VOP_CREATE(n,a,p)	(*((n)->ni_dvp->v_op->vop_create))(n,a,p)
E 40
D 37
	int	(*vn_create)	__P((struct nameidata *ndp, struct vattr *vap,
E 37
I 37
	int	(*vop_create)	__P((struct nameidata *ndp, struct vattr *vap,
E 37
				    struct proc *p));
I 40
#define	VOP_MKNOD(n,a,c,p)	(*((n)->ni_dvp->v_op->vop_mknod))(n,a,c,p)
E 40
D 37
	int	(*vn_mknod)	__P((struct nameidata *ndp, struct vattr *vap,
E 37
I 37
	int	(*vop_mknod)	__P((struct nameidata *ndp, struct vattr *vap,
E 37
				    struct ucred *cred, struct proc *p));
E 46
I 46
#define	VOP_LOOKUP(d,v,c)	(*((d)->v_op->vop_lookup))(d,v,c)
	int	(*vop_lookup)	__P((struct vnode *dvp, struct vnode **vpp,
				     struct componentname *cnp));
#define	VOP_CREATE(d,v,c,a)	(*((d)->v_op->vop_create))(d,v,c,a)
	int	(*vop_create)	__P((struct vnode *dvp, struct vnode **vpp,
				     struct componentname *cnp,
				     struct vattr *vap));
#define	VOP_MKNOD(d,v,c,a)	(*((d)->v_op->vop_mknod))(d,v,c,a)
	int	(*vop_mknod)	__P((struct vnode *dvp, struct vnode **vpp,
				     struct componentname *cnp,
				     struct vattr *vap));
E 46
I 40
#define	VOP_OPEN(v,f,c,p)	(*((v)->v_op->vop_open))(v,f,c,p)
E 40
D 37
	int	(*vn_open)	__P((struct vnode *vp, int mode,
E 37
I 37
	int	(*vop_open)	__P((struct vnode *vp, int mode,
E 37
				    struct ucred *cred, struct proc *p));
I 40
#define	VOP_CLOSE(v,f,c,p)	(*((v)->v_op->vop_close))(v,f,c,p)
E 40
D 37
	int	(*vn_close)	__P((struct vnode *vp, int fflag,
E 37
I 37
	int	(*vop_close)	__P((struct vnode *vp, int fflag,
E 37
				    struct ucred *cred, struct proc *p));
I 40
#define	VOP_ACCESS(v,f,c,p)	(*((v)->v_op->vop_access))(v,f,c,p)
E 40
D 37
	int	(*vn_access)	__P((struct vnode *vp, int mode,
E 37
I 37
	int	(*vop_access)	__P((struct vnode *vp, int mode,
E 37
				    struct ucred *cred, struct proc *p));
I 40
#define	VOP_GETATTR(v,a,c,p)	(*((v)->v_op->vop_getattr))(v,a,c,p)
E 40
D 37
	int	(*vn_getattr)	__P((struct vnode *vp, struct vattr *vap,
E 37
I 37
	int	(*vop_getattr)	__P((struct vnode *vp, struct vattr *vap,
E 37
D 36
				    struct ucred *cred,
				    struct proc *p));
E 36
I 36
				    struct ucred *cred, struct proc *p));
I 40
#define	VOP_SETATTR(v,a,c,p)	(*((v)->v_op->vop_setattr))(v,a,c,p)
E 40
E 36
D 37
	int	(*vn_setattr)	__P((struct vnode *vp, struct vattr *vap,
E 37
I 37
	int	(*vop_setattr)	__P((struct vnode *vp, struct vattr *vap,
E 37
				    struct ucred *cred, struct proc *p));
I 40
#define	VOP_READ(v,u,i,c)	(*((v)->v_op->vop_read))(v,u,i,c)
E 40
D 37
	int	(*vn_read)	__P((struct vnode *vp, struct uio *uio,
E 37
I 37
	int	(*vop_read)	__P((struct vnode *vp, struct uio *uio,
E 37
				    int ioflag, struct ucred *cred));
I 40
#define	VOP_WRITE(v,u,i,c)	(*((v)->v_op->vop_write))(v,u,i,c)
E 40
D 37
	int	(*vn_write)	__P((struct vnode *vp, struct uio *uio,
E 37
I 37
	int	(*vop_write)	__P((struct vnode *vp, struct uio *uio,
E 37
				    int ioflag, struct ucred *cred));
I 40
#define	VOP_IOCTL(v,o,d,f,c,p)	(*((v)->v_op->vop_ioctl))(v,o,d,f,c,p)
E 40
D 37
	int	(*vn_ioctl)	__P((struct vnode *vp, int command,
E 37
I 37
	int	(*vop_ioctl)	__P((struct vnode *vp, int command,
E 37
				    caddr_t data, int fflag,
				    struct ucred *cred, struct proc *p));
I 40
#define	VOP_SELECT(v,w,f,c,p)	(*((v)->v_op->vop_select))(v,w,f,c,p)
E 40
D 37
	int	(*vn_select)	__P((struct vnode *vp, int which, int fflags,
E 37
I 37
	int	(*vop_select)	__P((struct vnode *vp, int which, int fflags,
E 37
				    struct ucred *cred, struct proc *p));
I 40
#define	VOP_MMAP(v,c,p)		(*((v)->v_op->vop_mmap))(v,c,p)
E 40
D 37
	int	(*vn_mmap)	__P((struct vnode *vp, int fflags,
E 37
I 37
	int	(*vop_mmap)	__P((struct vnode *vp, int fflags,
E 37
				    struct ucred *cred, struct proc *p));
I 40
#define	VOP_FSYNC(v,f,c,w,p)	(*((v)->v_op->vop_fsync))(v,f,c,w,p)
E 40
D 37
	int	(*vn_fsync)	__P((struct vnode *vp, int fflags,
E 37
I 37
	int	(*vop_fsync)	__P((struct vnode *vp, int fflags,
E 37
				    struct ucred *cred, int waitfor,
				    struct proc *p));
I 40
#define	VOP_SEEK(v,p,o,w)	(*((v)->v_op->vop_seek))(v,p,o,w)
E 40
D 37
	int	(*vn_seek)	__P((struct vnode *vp, off_t oldoff,
E 37
I 37
	int	(*vop_seek)	__P((struct vnode *vp, off_t oldoff,
E 37
				    off_t newoff, struct ucred *cred));
I 40
D 46
#define	VOP_REMOVE(n,p)		(*((n)->ni_dvp->v_op->vop_remove))(n,p)
E 40
D 37
	int	(*vn_remove)	__P((struct nameidata *ndp, struct proc *p));
	int	(*vn_link)	__P((struct vnode *vp, struct nameidata *ndp,
E 37
I 37
	int	(*vop_remove)	__P((struct nameidata *ndp, struct proc *p));
I 40
#define	VOP_LINK(v,n,p)		(*((n)->ni_dvp->v_op->vop_link))(v,n,p)
E 40
	int	(*vop_link)	__P((struct vnode *vp, struct nameidata *ndp,
E 37
				    struct proc *p));
I 40
#define	VOP_RENAME(s,t,p)	(*((s)->ni_dvp->v_op->vop_rename))(s,t,p)
E 40
D 37
	int	(*vn_rename)	__P((struct nameidata *fndp,
E 37
I 37
	int	(*vop_rename)	__P((struct nameidata *fndp,
E 37
				    struct nameidata *tdnp, struct proc *p));
I 40
#define	VOP_MKDIR(n,a,p)	(*((n)->ni_dvp->v_op->vop_mkdir))(n,a,p)
E 40
D 37
	int	(*vn_mkdir)	__P((struct nameidata *ndp, struct vattr *vap,
E 37
I 37
	int	(*vop_mkdir)	__P((struct nameidata *ndp, struct vattr *vap,
E 37
				    struct proc *p));
I 40
#define	VOP_RMDIR(n,p)		(*((n)->ni_dvp->v_op->vop_rmdir))(n,p)
E 40
D 37
	int	(*vn_rmdir)	__P((struct nameidata *ndp, struct proc *p));
	int	(*vn_symlink)	__P((struct nameidata *ndp, struct vattr *vap,
E 37
I 37
	int	(*vop_rmdir)	__P((struct nameidata *ndp, struct proc *p));
I 40
#define	VOP_SYMLINK(n,a,m,p)	(*((n)->ni_dvp->v_op->vop_symlink))(n,a,m,p)
E 40
	int	(*vop_symlink)	__P((struct nameidata *ndp, struct vattr *vap,
E 37
				    char *target, struct proc *p));
E 46
I 46
#define	VOP_REMOVE(d,v,c)	(*((d)->v_op->vop_remove))(d,v,c)
	int	(*vop_remove)	__P((struct vnode *dvp, struct vnode *vp,
				     struct componentname *cnp));
#define	VOP_LINK(v,d,c)		(*((v)->v_op->vop_link))(v,d,c)
	int	(*vop_link)	__P((struct vnode *vp, struct vnode *tdvp,
				     struct componentname *cnp));
#define	VOP_RENAME(fd,fv,fc,td,tv,tc) (*((fd)->v_op->vop_rename))(fd,fv,fc,td,tv,tc)
	int	(*vop_rename)	__P((struct vnode *fdvp, struct vnode *fvp,
				     struct componentname *fcnp,
				     struct vnode *tdvp, struct vnode *tvp,
				     struct componentname *tcnp));
#define	VOP_MKDIR(d,v,c,a)	(*((d)->v_op->vop_mkdir))(d,v,c,a)
	int	(*vop_mkdir)	__P((struct vnode *dvp, struct vnode **vpp,
				     struct componentname *cnp,
				     struct vattr *vap));
#define	VOP_RMDIR(d,v,c)	(*((d)->v_op->vop_rmdir))(d,v,c)
	int	(*vop_rmdir)	__P((struct vnode *dvp, struct vnode *vp,
				     struct componentname *cnp));
#define	VOP_SYMLINK(d,v,c,a,t)	(*((d)->v_op->vop_symlink))(d,v,c,a,t)
	int	(*vop_symlink)	__P((struct vnode *dvp, struct vnode **vpp,
				     struct componentname *cnp,
				     struct vattr *vap, char *target));
E 46
I 40
#define	VOP_READDIR(v,u,c,e)	(*((v)->v_op->vop_readdir))(v,u,c,e)
E 40
D 37
	int	(*vn_readdir)	__P((struct vnode *vp, struct uio *uio,
E 37
I 37
	int	(*vop_readdir)	__P((struct vnode *vp, struct uio *uio,
E 37
				    struct ucred *cred, int *eofflagp));
I 40
#define	VOP_READLINK(v,u,c)	(*((v)->v_op->vop_readlink))(v,u,c)
E 40
D 37
	int	(*vn_readlink)	__P((struct vnode *vp, struct uio *uio,
E 37
I 37
	int	(*vop_readlink)	__P((struct vnode *vp, struct uio *uio,
E 37
				    struct ucred *cred));
I 40
D 46
#define	VOP_ABORTOP(n)		(*((n)->ni_dvp->v_op->vop_abortop))(n)
E 40
D 37
	int	(*vn_abortop)	__P((struct nameidata *ndp));
	int	(*vn_inactive)	__P((struct vnode *vp, struct proc *p));
	int	(*vn_reclaim)	__P((struct vnode *vp));
	int	(*vn_lock)	__P((struct vnode *vp));
	int	(*vn_unlock)	__P((struct vnode *vp));
	int	(*vn_bmap)	__P((struct vnode *vp, daddr_t bn,
E 37
I 37
	int	(*vop_abortop)	__P((struct nameidata *ndp));
E 46
I 46
#define	VOP_ABORTOP(d,c)	(*((d)->v_op->vop_abortop))(d,c)
	int	(*vop_abortop)	__P((struct vnode *dvp,
				     struct componentname *cnp));
E 46
I 40
#define	VOP_INACTIVE(v,p)	(*((v)->v_op->vop_inactive))(v,p)
E 40
	int	(*vop_inactive)	__P((struct vnode *vp, struct proc *p));
I 40
#define	VOP_RECLAIM(v)		(*((v)->v_op->vop_reclaim))(v)
E 40
	int	(*vop_reclaim)	__P((struct vnode *vp));
I 40
#define	VOP_LOCK(v)		(*((v)->v_op->vop_lock))(v)
E 40
	int	(*vop_lock)	__P((struct vnode *vp));
I 40
#define	VOP_UNLOCK(v)		(*((v)->v_op->vop_unlock))(v)
E 40
	int	(*vop_unlock)	__P((struct vnode *vp));
I 40
#define	VOP_BMAP(v,s,p,n)	(*((v)->v_op->vop_bmap))(v,s,p,n)
E 40
	int	(*vop_bmap)	__P((struct vnode *vp, daddr_t bn,
E 37
				    struct vnode **vpp, daddr_t *bnp));
I 40
#define	VOP_STRATEGY(b)		(*((b)->b_vp->v_op->vop_strategy))(b)
E 40
D 37
	int	(*vn_strategy)	__P((struct buf *bp));
	int	(*vn_print)	__P((struct vnode *vp));
	int	(*vn_islocked)	__P((struct vnode *vp));
	int	(*vn_advlock)	__P((struct vnode *vp, caddr_t id, int op,
E 37
I 37
	int	(*vop_strategy)	__P((struct buf *bp));
I 40
#define	VOP_PRINT(v)		(*((v)->v_op->vop_print))(v)
E 40
	int	(*vop_print)	__P((struct vnode *vp));
I 40
#define	VOP_ISLOCKED(v)		(((v)->v_flag & VXLOCK) || \
				(*((v)->v_op->vop_islocked))(v))
E 40
	int	(*vop_islocked)	__P((struct vnode *vp));
I 40
#define	VOP_ADVLOCK(v,p,o,l,f)	(*((v)->v_op->vop_advlock))(v,p,o,l,f)
E 40
	int	(*vop_advlock)	__P((struct vnode *vp, caddr_t id, int op,
E 37
				    struct flock *fl, int flags));
I 41
#define	VOP_BLKATOFF(v,o,r,b)	(*((v)->v_op->vop_blkatoff))(v,o,r,b)
	int	(*vop_blkatoff) __P((struct vnode *vp,
		    off_t offset, char **res, struct buf **bpp));
#define	VOP_VGET(v,i,vp)	(*((v)->v_op->vop_vget))((v)->v_mount,i,vp)
	int	(*vop_vget)
		    __P((struct mount *mp, ino_t ino, struct vnode **vpp));
#define	VOP_VALLOC(v,m,c,vp)	(*((v)->v_op->vop_valloc))(v,m,c,vp)
	int	(*vop_valloc) __P((struct vnode *pvp,
		    int mode, struct ucred *cred, struct vnode **vpp));
#define	VOP_VFREE(v,i,m)	(*((v)->v_op->vop_vfree))(v,i,m)
	void	(*vop_vfree) __P((struct vnode *pvp, ino_t ino, int mode));
D 51
#define	VOP_TRUNCATE(v,l,f)	(*((v)->v_op->vop_truncate))(v,l,f)
	int	(*vop_truncate)
D 49
		    __P((struct vnode *vp, u_long length, int flags));
E 49
I 49
		    __P((struct vnode *vp, off_t length, int flags));
E 51
I 51
#define	VOP_TRUNCATE(v,l,f,c)	(*((v)->v_op->vop_truncate))(v,l,f,c)
	int	(*vop_truncate) __P((struct vnode *vp,
		    off_t length, int flags, struct ucred *cred));
E 51
E 49
#define	VOP_UPDATE(v,ta,tm,w)	(*((v)->v_op->vop_update))(v,ta,tm,w)
	int	(*vop_update) __P((struct vnode *vp,
		    struct timeval *ta, struct timeval *tm, int waitfor));
#define	VOP_BWRITE(b)		(*((b)->b_vp->v_op->vop_bwrite))(b)
	int	(*vop_bwrite) __P((struct buf *bp));
E 41
E 35
};
E 53

D 40
/* Macros to call the vnode ops */
D 37
#define	VOP_LOOKUP(v,n,p)	(*((v)->v_op->vn_lookup))(v,n,p)
#define	VOP_CREATE(n,a,p)	(*((n)->ni_dvp->v_op->vn_create))(n,a,p)
#define	VOP_MKNOD(n,a,c,p)	(*((n)->ni_dvp->v_op->vn_mknod))(n,a,c,p)
#define	VOP_OPEN(v,f,c,p)	(*((v)->v_op->vn_open))(v,f,c,p)
#define	VOP_CLOSE(v,f,c,p)	(*((v)->v_op->vn_close))(v,f,c,p)
#define	VOP_ACCESS(v,f,c,p)	(*((v)->v_op->vn_access))(v,f,c,p)
#define	VOP_GETATTR(v,a,c,p)	(*((v)->v_op->vn_getattr))(v,a,c,p)
#define	VOP_SETATTR(v,a,c,p)	(*((v)->v_op->vn_setattr))(v,a,c,p)
#define	VOP_READ(v,u,i,c)	(*((v)->v_op->vn_read))(v,u,i,c)
#define	VOP_WRITE(v,u,i,c)	(*((v)->v_op->vn_write))(v,u,i,c)
#define	VOP_IOCTL(v,o,d,f,c,p)	(*((v)->v_op->vn_ioctl))(v,o,d,f,c,p)
#define	VOP_SELECT(v,w,f,c,p)	(*((v)->v_op->vn_select))(v,w,f,c,p)
#define	VOP_MMAP(v,c,p)		(*((v)->v_op->vn_mmap))(v,c,p)
#define	VOP_FSYNC(v,f,c,w,p)	(*((v)->v_op->vn_fsync))(v,f,c,w,p)
#define	VOP_SEEK(v,p,o,w)	(*((v)->v_op->vn_seek))(v,p,o,w)
#define	VOP_REMOVE(n,p)		(*((n)->ni_dvp->v_op->vn_remove))(n,p)
#define	VOP_LINK(v,n,p)		(*((n)->ni_dvp->v_op->vn_link))(v,n,p)
#define	VOP_RENAME(s,t,p)	(*((s)->ni_dvp->v_op->vn_rename))(s,t,p)
#define	VOP_MKDIR(n,a,p)	(*((n)->ni_dvp->v_op->vn_mkdir))(n,a,p)
#define	VOP_RMDIR(n,p)		(*((n)->ni_dvp->v_op->vn_rmdir))(n,p)
#define	VOP_SYMLINK(n,a,m,p)	(*((n)->ni_dvp->v_op->vn_symlink))(n,a,m,p)
#define	VOP_READDIR(v,u,c,e)	(*((v)->v_op->vn_readdir))(v,u,c,e)
#define	VOP_READLINK(v,u,c)	(*((v)->v_op->vn_readlink))(v,u,c)
#define	VOP_ABORTOP(n)		(*((n)->ni_dvp->v_op->vn_abortop))(n)
#define	VOP_INACTIVE(v,p)	(*((v)->v_op->vn_inactive))(v,p)
#define	VOP_RECLAIM(v)		(*((v)->v_op->vn_reclaim))(v)
#define	VOP_LOCK(v)		(*((v)->v_op->vn_lock))(v)
#define	VOP_UNLOCK(v)		(*((v)->v_op->vn_unlock))(v)
#define	VOP_BMAP(v,s,p,n)	(*((v)->v_op->vn_bmap))(v,s,p,n)
#define	VOP_STRATEGY(b)		(*((b)->b_vp->v_op->vn_strategy))(b)
#define	VOP_PRINT(v)		(*((v)->v_op->vn_print))(v)
E 37
I 37
#define	VOP_LOOKUP(v,n,p)	(*((v)->v_op->vop_lookup))(v,n,p)
#define	VOP_CREATE(n,a,p)	(*((n)->ni_dvp->v_op->vop_create))(n,a,p)
#define	VOP_MKNOD(n,a,c,p)	(*((n)->ni_dvp->v_op->vop_mknod))(n,a,c,p)
#define	VOP_OPEN(v,f,c,p)	(*((v)->v_op->vop_open))(v,f,c,p)
#define	VOP_CLOSE(v,f,c,p)	(*((v)->v_op->vop_close))(v,f,c,p)
#define	VOP_ACCESS(v,f,c,p)	(*((v)->v_op->vop_access))(v,f,c,p)
#define	VOP_GETATTR(v,a,c,p)	(*((v)->v_op->vop_getattr))(v,a,c,p)
#define	VOP_SETATTR(v,a,c,p)	(*((v)->v_op->vop_setattr))(v,a,c,p)
#define	VOP_READ(v,u,i,c)	(*((v)->v_op->vop_read))(v,u,i,c)
#define	VOP_WRITE(v,u,i,c)	(*((v)->v_op->vop_write))(v,u,i,c)
#define	VOP_IOCTL(v,o,d,f,c,p)	(*((v)->v_op->vop_ioctl))(v,o,d,f,c,p)
#define	VOP_SELECT(v,w,f,c,p)	(*((v)->v_op->vop_select))(v,w,f,c,p)
#define	VOP_MMAP(v,c,p)		(*((v)->v_op->vop_mmap))(v,c,p)
#define	VOP_FSYNC(v,f,c,w,p)	(*((v)->v_op->vop_fsync))(v,f,c,w,p)
#define	VOP_SEEK(v,p,o,w)	(*((v)->v_op->vop_seek))(v,p,o,w)
#define	VOP_REMOVE(n,p)		(*((n)->ni_dvp->v_op->vop_remove))(n,p)
#define	VOP_LINK(v,n,p)		(*((n)->ni_dvp->v_op->vop_link))(v,n,p)
#define	VOP_RENAME(s,t,p)	(*((s)->ni_dvp->v_op->vop_rename))(s,t,p)
#define	VOP_MKDIR(n,a,p)	(*((n)->ni_dvp->v_op->vop_mkdir))(n,a,p)
#define	VOP_RMDIR(n,p)		(*((n)->ni_dvp->v_op->vop_rmdir))(n,p)
#define	VOP_SYMLINK(n,a,m,p)	(*((n)->ni_dvp->v_op->vop_symlink))(n,a,m,p)
#define	VOP_READDIR(v,u,c,e)	(*((v)->v_op->vop_readdir))(v,u,c,e)
#define	VOP_READLINK(v,u,c)	(*((v)->v_op->vop_readlink))(v,u,c)
#define	VOP_ABORTOP(n)		(*((n)->ni_dvp->v_op->vop_abortop))(n)
#define	VOP_INACTIVE(v,p)	(*((v)->v_op->vop_inactive))(v,p)
#define	VOP_RECLAIM(v)		(*((v)->v_op->vop_reclaim))(v)
#define	VOP_LOCK(v)		(*((v)->v_op->vop_lock))(v)
#define	VOP_UNLOCK(v)		(*((v)->v_op->vop_unlock))(v)
#define	VOP_BMAP(v,s,p,n)	(*((v)->v_op->vop_bmap))(v,s,p,n)
#define	VOP_STRATEGY(b)		(*((b)->b_vp->v_op->vop_strategy))(b)
#define	VOP_PRINT(v)		(*((v)->v_op->vop_print))(v)
E 37
D 34
#define	VOP_ISLOCKED(v)		(*((v)->v_op->vn_islocked))(v)
E 34
I 34
#define	VOP_ISLOCKED(v)		(((v)->v_flag & VXLOCK) || \
D 37
				(*((v)->v_op->vn_islocked))(v))
E 34
#define	VOP_ADVLOCK(v,p,o,l,f)	(*((v)->v_op->vn_advlock))(v,p,o,l,f)
E 37
I 37
				(*((v)->v_op->vop_islocked))(v))
#define	VOP_ADVLOCK(v,p,o,l,f)	(*((v)->v_op->vop_advlock))(v,p,o,l,f)
E 37

E 40
/*
 * flags for ioflag
 */
E 54
D 35
#define IO_UNIT		0x01		/* do I/O as atomic unit */
#define IO_APPEND	0x02		/* append write to end */
#define IO_SYNC		0x04		/* do I/O synchronously */
E 35
I 35
#define	IO_UNIT		0x01		/* do I/O as atomic unit */
#define	IO_APPEND	0x02		/* append write to end */
#define	IO_SYNC		0x04		/* do I/O synchronously */
E 35
#define	IO_NODELOCKED	0x08		/* underlying node already locked */
#define	IO_NDELAY	0x10		/* FNDELAY flag set in file table */

/*
E 33
D 54
 *  Modes. Some values same as Ixxx entries from inode.h for now
E 54
I 54
 *  Modes.  Some values same as Ixxx entries from inode.h for now.
E 54
 */
#define	VSUID	04000		/* set user id on execution */
#define	VSGID	02000		/* set group id on execution */
#define	VSVTX	01000		/* save swapped text even after use */
D 54
#define	VREAD	0400		/* read, write, execute permissions */
#define	VWRITE	0200
#define	VEXEC	0100
E 54
I 54
#define	VREAD	00400		/* read, write, execute permissions */
#define	VWRITE	00200
#define	VEXEC	00100
E 54
I 5

E 5
/*
D 54
 * Token indicating no attribute value yet assigned
E 54
I 54
 * Token indicating no attribute value yet assigned.
E 54
 */
D 35
#define VNOVAL	((unsigned)0xffffffff)
E 35
I 35
D 43
#define	VNOVAL	((unsigned)0xffffffff)
E 43
I 43
#define	VNOVAL	(-1)
E 43
E 35

#ifdef KERNEL
/*
I 48
 * Convert between vnode types and inode formats (since POSIX.1
 * defines mode word of stat structure in terms of inode formats).
 */
extern enum vtype	iftovt_tab[];
extern int		vttoif_tab[];
D 58
#define IFTOVT(mode)	(iftovt_tab[((mode) & IFMT) >> 12])
E 58
I 58
#define IFTOVT(mode)	(iftovt_tab[((mode) & S_IFMT) >> 12])
E 58
#define VTTOIF(indx)	(vttoif_tab[(int)(indx)])
#define MAKEIMODE(indx, mode)	(int)(VTTOIF(indx) | (mode))

/*
E 48
D 53
 * public vnode manipulation functions
 */
D 33
extern int vn_open();			/* open vnode */
extern int vn_rdwr();			/* read or write vnode */
extern int vn_close();			/* close vnode */
I 5
D 9
extern void vref();			/* reference vnode */
E 9
I 9
extern void vattr_null();		/* set attributes to null */
extern int getnewvnode();		/* allocate a new vnode */
extern int bdevvp();			/* allocate a new special dev vnode */
extern struct vnode *checkalias();	/* check for special device aliases */
I 14
extern int vcount();			/* total references to a device */
E 14
extern int vget();			/* get first reference to a vnode */
extern void vref();			/* increase reference to a vnode */
E 9
extern void vput();			/* unlock and release vnode */
E 5
extern void vrele();			/* release vnode */
D 9
extern void vattr_null();		/* set attributes to null */
I 7
extern struct vnode *checkalias();	/* check for block device aliases */
E 7
I 3
D 5
#define VREF(vp)	(vp)->v_count++;/* increment vnode reference count */
E 5
I 5
#define VREF(vp)    (vp)->v_count++;	/* increment vnode reference count */
E 9
I 9
D 14
extern void vclean();			/* clean out filesystem data in vnode */
E 14
extern void vgone();			/* completely recycle vnode */
I 14
extern void vgoneall();			/* recycle vnode and all its aliases */
E 33
I 33
D 35
int 	vn_open __P((			/* open vnode */
		struct nameidata *ndp,
		struct proc *p,
		int fmode,
		int cmode));
int 	vn_rdwr __P((			/* read or write vnode */
		enum uio_rw rw,
		struct vnode *vp,
		caddr_t base,
		int len,
		off_t offset,
		enum uio_seg segflg,
		int ioflg,
		struct ucred *cred,
		int *aresid,
		struct proc *p));
int	vn_read __P((			/* read a vnode into a uio structure */
		struct file *fp,
		struct uio *uio,
		struct ucred *cred));
int	vn_write __P((			/* write a vnode from a uio structure */
		struct file *fp,
		struct uio *uio,
		struct ucred *cred));
int	vn_ioctl __P((			/* do an ioctl operation on a vnode */
		struct file *fp,
		int com,
		caddr_t data,
		struct proc *p));
int	vn_select __P((			/* do a select operation on a vnode */
		struct file *fp,
		int which,
		struct proc *p));
int 	vn_close __P((			/* close vnode */
		struct file *fp,
		struct proc *p));
int 	getnewvnode __P((		/* allocate a new vnode */
		enum vtagtype tag,
		struct mount *mp,
		struct vnodeops *vops,
		struct vnode **vpp));
int 	bdevvp __P((			/* allocate a new special dev vnode */
		int dev,		/* XXX should be type dev_t, not int */
		struct vnode **vpp));
struct 	vnode *checkalias __P((		/* check for special device aliases */
		struct vnode *vp,
		int nvp_rdev,		/* XXX should be type dev_t, not int */
		struct mount *mp));
void 	vattr_null __P((		/* set attributes to null */
		struct vattr *vap));
E 35
I 35
D 47
int 	vn_open __P((struct nameidata *ndp, struct proc *p, int fmode,
	    int cmode));
E 47
I 47
int 	vn_open __P((struct nameidata *ndp, int fmode, int cmode));
E 47
I 38
int 	vn_close __P((struct vnode *vp, int flags, struct ucred *cred,
	    struct proc *p));
E 38
int 	vn_rdwr __P((enum uio_rw rw, struct vnode *vp, caddr_t base,
	    int len, off_t offset, enum uio_seg segflg, int ioflg,
	    struct ucred *cred, int *aresid, struct proc *p));
int	vn_read __P((struct file *fp, struct uio *uio, struct ucred *cred));
int	vn_write __P((struct file *fp, struct uio *uio, struct ucred *cred));
int	vn_ioctl __P((struct file *fp, int com, caddr_t data, struct proc *p));
int	vn_select __P((struct file *fp, int which, struct proc *p));
I 39
int 	vn_closefile __P((struct file *fp, struct proc *p));
E 39
D 38
int 	vn_close __P(( struct file *fp, struct proc *p));
E 38
int 	getnewvnode __P((enum vtagtype tag, struct mount *mp,
	    struct vnodeops *vops, struct vnode **vpp));
D 52
int 	bdevvp __P((int dev, struct vnode **vpp));
E 52
I 52
int 	bdevvp __P((dev_t dev, struct vnode **vpp));
E 52
	/* check for special device aliases */
D 52
	/* XXX nvp_rdev should be type dev_t, not int */
struct 	vnode *checkalias __P((struct vnode *vp, int nvp_rdev,
E 52
I 52
struct 	vnode *checkalias __P((struct vnode *vp, dev_t nvp_rdev,
E 52
	    struct mount *mp));
void 	vattr_null __P((struct vattr *vap));
E 35
int 	vcount __P((struct vnode *vp));	/* total references to a device */
int 	vget __P((struct vnode *vp));	/* get first reference to a vnode */
void 	vref __P((struct vnode *vp));	/* increase reference to a vnode */
void 	vput __P((struct vnode *vp));	/* unlock and release vnode */
void 	vrele __P((struct vnode *vp));	/* release vnode */
void 	vgone __P((struct vnode *vp));	/* completely recycle vnode */
void 	vgoneall __P((struct vnode *vp));/* recycle vnode and all its aliases */
E 33
E 14

I 16
D 27
#ifdef notdef
E 27
I 27
/*
E 53
 * Flags to various vnode functions.
 */
#define	SKIPSYSTEM	0x0001		/* vflush: skip vnodes marked VSYSTEM */
#define	FORCECLOSE	0x0002		/* vflush: force file closeure */
D 65
#define	DOCLOSE		0x0004		/* vclean: close active files */
E 65
I 65
#define	WRITECLOSE	0x0004		/* vflush: only close writeable files */
#define	DOCLOSE		0x0008		/* vclean: close active files */
E 65
I 63
#define	V_SAVE		0x0001		/* vinvalbuf: sync file first */
#define	V_SAVEMETA	0x0002		/* vinvalbuf: leave indirect blocks */
I 87
#define	REVOKEALL	0x0001		/* vop_revoke: revoke all aliases */
E 87
E 63

D 54
#ifndef DIAGNOSTIC
E 27
E 16
D 17
#define VREF(vp)    (vp)->v_count++;	/* increase reference to a vnode */
E 17
I 17
D 28
#define VREF(vp)    (vp)->v_usecount++;	/* increase reference to a vnode */
#define VHOLD(vp)   (vp)->v_holdcnt++;	/* increase buf or page ref to vnode */
#define HOLDRELE(vp) (vp)->v_holdcnt--;	/* decrease buf or page ref to vnode */
E 28
I 28
D 35
#define VREF(vp)    (vp)->v_usecount++	/* increase reference to a vnode */
#define VHOLD(vp)   (vp)->v_holdcnt++	/* increase buf or page ref to vnode */
#define HOLDRELE(vp) (vp)->v_holdcnt--	/* decrease buf or page ref to vnode */
#define	VATTR_NULL(vap) *(vap) = va_null /* initialize a vattr stucture */
E 35
I 35
#define	VREF(vp)	(vp)->v_usecount++	/* increase reference */
#define	VHOLD(vp)	(vp)->v_holdcnt++	/* increase buf or page ref */
#define	HOLDRELE(vp)	(vp)->v_holdcnt--	/* decrease buf or page ref */
#define	VATTR_NULL(vap)	(*(vap) = va_null)	/* initialize a vattr */
E 35
E 28
E 17
I 16
D 27
#else
E 27
I 27
D 40
#else /* DIAGNOSTIC */
E 40
I 40
#else
E 40
E 27
D 35
#define VREF(vp)    vref(vp)
I 17
#define VHOLD(vp)   vhold(vp)
#define HOLDRELE(vp) holdrele(vp)
I 28
#define	VATTR_NULL(vap) vattr_null(vap)
E 35
I 35
#define	VREF(vp)	vref(vp)
#define	VHOLD(vp)	vhold(vp)
E 54
I 54
#ifdef DIAGNOSTIC
E 54
#define	HOLDRELE(vp)	holdrele(vp)
#define	VATTR_NULL(vap)	vattr_null(vap)
I 54
#define	VHOLD(vp)	vhold(vp)
#define	VREF(vp)	vref(vp)
E 54
I 52

void	holdrele __P((struct vnode *));
void	vattr_null __P((struct vattr *));
void	vhold __P((struct vnode *));
void	vref __P((struct vnode *));
I 54
#else
D 89
#define	HOLDRELE(vp)	(vp)->v_holdcnt--	/* decrease buf or page ref */
E 89
#define	VATTR_NULL(vap)	(*(vap) = va_null)	/* initialize a vattr */
D 89
#define	VHOLD(vp)	(vp)->v_holdcnt++	/* increase buf or page ref */
#define	VREF(vp)	(vp)->v_usecount++	/* increase reference */
E 54
E 52
E 35
E 28
E 17
#endif
E 89
I 89
#define	HOLDRELE(vp)	holdrele(vp)		/* decrease buf or page ref */
static __inline holdrele(vp)
	struct vnode *vp;
{
	simple_lock(&vp->v_interlock);
	vp->v_holdcnt--;
	simple_unlock(&vp->v_interlock);
}
#define	VHOLD(vp)	vhold(vp)		/* increase buf or page ref */
static __inline vhold(vp)
	struct vnode *vp;
{
	simple_lock(&vp->v_interlock);
	vp->v_holdcnt++;
	simple_unlock(&vp->v_interlock);
}
#define	VREF(vp)	vref(vp)		/* increase reference */
static __inline vref(vp)
	struct vnode *vp;
{
	simple_lock(&vp->v_interlock);
	vp->v_usecount++;
	simple_unlock(&vp->v_interlock);
}
#endif /* DIAGNOSTIC */
E 89
E 16
E 9
E 5
E 3

I 27
D 35
#define	NULLVP	((struct vnode *)0)
E 35
I 35
#define	NULLVP	((struct vnode *)NULL)
E 35

E 27
D 5
#define vinit(vp, mountp, type, vops)	{ \
	(vp)->v_flag = 0; \
	(vp)->v_count++; \
	(vp)->v_shlockc = (vp)->v_exlockc = 0; \
	(vp)->v_mount = (mountp); \
	(vp)->v_type = (type); \
	(vp)->v_op = (vops); \
	(vp)->v_socket = 0; \
}

E 5
/*
 * Global vnode data.
 */
D 5
extern struct vnode	*rootdir;		/* root (i.e. "/") vnode */
E 5
I 5
D 73
extern	struct vnode *rootdir;		/* root (i.e. "/") vnode */
E 73
I 73
extern	struct vnode *rootvnode;	/* root (i.e. "/") vnode */
E 73
E 5
D 27

E 27
I 5
D 26
extern	struct vnode *vnode;		/* The vnode table itself */
extern	struct vnode *vnodeNVNODE;	/* The end of the vnode table */
extern	int nvnode;			/* number of slots in the table */
E 26
I 26
extern	int desiredvnodes;		/* number of vnodes desired */
I 28
extern	struct vattr va_null;		/* predefined null vattr structure */
I 45

/*
 * Macro/function to check for client cache inconsistency w.r.t. leasing.
 */
#define	LEASE_READ	0x1		/* Check lease for readers */
#define	LEASE_WRITE	0x2		/* Check lease for modifiers */

D 81
#ifdef NFS
D 80
void	lease_check __P((struct vnode *vp, struct proc *p,
D 54
		struct ucred *ucred, int flag));
E 54
I 54
	    struct ucred *ucred, int flag));
E 80
E 54
void	lease_updatetime __P((int deltat));
D 80
#define	LEASE_CHECK(vp, p, cred, flag)	lease_check((vp), (p), (cred), (flag))
E 80
#define	LEASE_UPDATETIME(dt)		lease_updatetime(dt)
#else
D 80
#define	LEASE_CHECK(vp, p, cred, flag)
E 80
#define	LEASE_UPDATETIME(dt)
#endif /* NFS */
E 81
E 45
E 28
E 26
E 5
D 62
#endif
E 62
I 62
#endif /* KERNEL */
E 62
I 53


/*
 * Mods for exensibility.
 */

/*
D 54
 * flags for vdesc_flags:
E 54
I 54
 * Flags for vdesc_flags:
E 54
 */
#define VDESC_MAX_VPS		16
D 54
/* low order 16 flag bits are reserved for map flags for vp arguments. */
E 54
I 54
D 59
/* Low order 16 flag bits are reserved for map flags for vp arguments. */
E 59
I 59
/* Low order 16 flag bits are reserved for willrele flags for vp arguments. */
#define VDESC_VP0_WILLRELE	0x0001
#define VDESC_VP1_WILLRELE	0x0002
#define VDESC_VP2_WILLRELE	0x0004
#define VDESC_VP3_WILLRELE	0x0008
E 59
E 54
#define VDESC_NOMAP_VPP		0x0100
I 59
#define VDESC_VPP_WILLRELE	0x0200
E 59

/*
 * VDESC_NO_OFFSET is used to identify the end of the offset list
 * and in places where no such field exists.
 */
#define VDESC_NO_OFFSET -1

/*
 * This structure describes the vnode operation taking place.
 */
struct vnodeop_desc {
	int	vdesc_offset;		/* offset in vector--first for speed */
	char    *vdesc_name;		/* a readable name for debugging */
	int	vdesc_flags;		/* VDESC_* flags */

	/*
D 54
	 * These ops are used by bypass routines
	 * to map and locate arguments.
	 * Creds and procs are not needed in bypass routines,
	 * but sometimes they are useful to (for example)
	 * transport layers.
E 54
I 54
	 * These ops are used by bypass routines to map and locate arguments.
	 * Creds and procs are not needed in bypass routines, but sometimes
	 * they are useful to (for example) transport layers.
I 59
	 * Nameidata is useful because it has a cred in it.
E 59
E 54
	 */
	int	*vdesc_vp_offsets;	/* list ended by VDESC_NO_OFFSET */
	int	vdesc_vpp_offset;	/* return vpp location */
	int	vdesc_cred_offset;	/* cred location, if any */
	int	vdesc_proc_offset;	/* proc location, if any */
I 59
	int	vdesc_componentname_offset; /* if any */
E 59
	/*
D 54
	 * Finally, we've got a list of private data
	 * (about each operation) for each transport layer.
	 * (Support to manage this list is not yet part of BSD.)
E 54
I 54
	 * Finally, we've got a list of private data (about each operation)
	 * for each transport layer.  (Support to manage this list is not
	 * yet part of BSD.)
E 54
	 */
	caddr_t	*vdesc_transports;
};

I 62
#ifdef KERNEL
E 62
/*
 * A list of all the operation descs.
 */
extern struct vnodeop_desc *vnodeop_descs[];

I 89
/*
 * Interlock for scanning list of vnodes attached to a mountpoint
 */
struct simplelock mntvnode_slock;
E 89

/*
 * This macro is very helpful in defining those offsets in the vdesc struct.
 *
 * This is stolen from X11R4.  I ingored all the fancy stuff for
 * Crays, so if you decide to port this to such a serious machine,
 * you might want to consult Intrisics.h's XtOffset{,Of,To}.
 */
#define VOPARG_OFFSET(p_type,field) \
        ((int) (((char *) (&(((p_type)NULL)->field))) - ((char *) NULL)))
#define VOPARG_OFFSETOF(s_type,field) \
	VOPARG_OFFSET(s_type*,field)
#define VOPARG_OFFSETTO(S_TYPE,S_OFFSET,STRUCT_P) \
	((S_TYPE)(((char*)(STRUCT_P))+(S_OFFSET)))


/*
 * This structure is used to configure the new vnodeops vector.
 */
struct vnodeopv_entry_desc {
	struct vnodeop_desc *opve_op;   /* which operation this is */
D 54
	int (*opve_impl)();	/* code implementing this operation */
E 54
I 54
	int (*opve_impl)();		/* code implementing this operation */
E 54
};
struct vnodeopv_desc {
D 54
	int (***opv_desc_vector_p)();
E 54
			/* ptr to the ptr to the vector where op should go */
I 54
	int (***opv_desc_vector_p)();
E 54
	struct vnodeopv_entry_desc *opv_desc_ops;   /* null terminated list */
};

/*
 * A default routine which just returns an error.
 */
D 54
extern int vn_default_error();
E 54
I 54
int vn_default_error __P((void));
E 54

/*
 * A generic structure.
 * This can be used by bypass routines to identify generic arguments.
 */
struct vop_generic_args {
	struct vnodeop_desc *a_desc;
	/* other random data follows, presumably */
};

/*
D 54
 * Standards, standards, standards...
E 54
I 54
 * VOCALL calls an op given an ops vector.  We break it out because BSD's
 * vclean changes the ops vector and then wants to call ops with the old
 * vector.
E 54
 */
D 54
#ifdef __STDC__
#define CONCAT2(A,B) A##B
#else
#define CONCAT2(A,B) A/**/B
#endif
E 54
I 54
#define VOCALL(OPSV,OFF,AP) (( *((OPSV)[(OFF)])) (AP))
E 54

/*
D 54
 * VOCALL calls an op given an ops vector.
 * We break it out because BSD's vclean changes
 * the ops vector and then wants to call ops
 * with the old vector.
 */
#define VOCALL(OPSV,OFF,AP) (( *((OPSV)[(OFF)])) (AP))
/*
E 54
 * This call works for vnodes in the kernel.
 */
#define VCALL(VP,OFF,AP) VOCALL((VP)->v_op,(OFF),(AP))
D 54
#define VDESC(OP) (& CONCAT2(OP,_desc))
E 54
I 54
#define VDESC(OP) (& __CONCAT(OP,_desc))
E 54
#define VOFFSET(OP) (VDESC(OP)->vdesc_offset)

/*
 * Finally, include the default set of vnode operations.
 */
D 60
#include <sys/vnode_if.h>
E 60
I 60
#include <vnode_if.h>
E 60

/*
D 54
 * public vnode manipulation functions
E 54
I 54
 * Public vnode manipulation functions.
E 54
 */
I 54
struct file;
struct mount;
struct nameidata;
I 84
struct ostat;
E 84
struct proc;
I 61
struct stat;
E 61
struct ucred;
struct uio;
struct vattr;
struct vnode;
struct vop_bwrite_args;

int 	bdevvp __P((dev_t dev, struct vnode **vpp));
I 84
void	cvtstat __P((struct stat *st, struct ostat *ost));
E 84
int 	getnewvnode __P((enum vtagtype tag,
	    struct mount *mp, int (**vops)(), struct vnode **vpp));
I 84
void	insmntque __P((struct vnode *vp, struct mount *mp));
E 84
I 58
D 83
int	vinvalbuf __P((struct vnode *vp, int save, struct ucred *cred,
D 67
	    struct proc *p));
E 67
I 67
	    struct proc *p, int slpflag, int slptimeo));
E 83
E 67
E 58
void 	vattr_null __P((struct vattr *vap));
int 	vcount __P((struct vnode *vp));
D 75
int 	vget __P((struct vnode *vp));
E 75
I 75
D 89
int 	vget __P((struct vnode *vp, int lockflag));
E 89
I 89
int	vflush __P((struct mount *mp, struct vnode *skipvp, int flags));
int 	vget __P((struct vnode *vp, int lockflag, struct proc *p));
E 89
E 75
void 	vgone __P((struct vnode *vp));
D 87
void 	vgoneall __P((struct vnode *vp));
E 87
I 83
int	vinvalbuf __P((struct vnode *vp, int save, struct ucred *cred,
	    struct proc *p, int slpflag, int slptimeo));
void	vprint __P((char *label, struct vnode *vp));
I 89
int	vrecycle __P((struct vnode *vp, struct simplelock *inter_lkp,
	    struct proc *p));
E 89
E 83
int	vn_bwrite __P((struct vop_bwrite_args *ap));
int 	vn_close __P((struct vnode *vp,
	    int flags, struct ucred *cred, struct proc *p));
int 	vn_closefile __P((struct file *fp, struct proc *p));
D 83
int	vn_ioctl __P((struct file *fp, int com, caddr_t data, struct proc *p));
E 83
I 83
int	vn_ioctl __P((struct file *fp, u_long com, caddr_t data,
	    struct proc *p));
I 89
int	vn_lock __P((struct vnode *vp, int flags, struct proc *p));
E 89
E 83
E 54
int 	vn_open __P((struct nameidata *ndp, int fmode, int cmode));
D 54
int 	vn_close __P((struct vnode *vp, int flags, struct ucred *cred,
	    struct proc *p));
E 54
int 	vn_rdwr __P((enum uio_rw rw, struct vnode *vp, caddr_t base,
	    int len, off_t offset, enum uio_seg segflg, int ioflg,
	    struct ucred *cred, int *aresid, struct proc *p));
int	vn_read __P((struct file *fp, struct uio *uio, struct ucred *cred));
D 54
int	vn_write __P((struct file *fp, struct uio *uio, struct ucred *cred));
int	vn_bwrite __P((struct vop_bwrite_args *ap));
int	vn_ioctl __P((struct file *fp, int com, caddr_t data, struct proc *p));
E 54
int	vn_select __P((struct file *fp, int which, struct proc *p));
I 60
int	vn_stat __P((struct vnode *vp, struct stat *sb, struct proc *p));
E 60
D 54
int 	vn_closefile __P((struct file *fp, struct proc *p));
int 	getnewvnode __P((enum vtagtype tag, struct mount *mp,
	    int (**vops)(), struct vnode **vpp));
int 	bdevvp __P((dev_t dev, struct vnode **vpp));
	/* check for special device aliases */
struct 	vnode *checkalias __P((struct vnode *vp, dev_t nvp_rdev,
	    struct mount *mp));
void 	vattr_null __P((struct vattr *vap));
int 	vcount __P((struct vnode *vp));	/* total references to a device */
int 	vget __P((struct vnode *vp));	/* get first reference to a vnode */
void 	vref __P((struct vnode *vp));	/* increase reference to a vnode */
void 	vput __P((struct vnode *vp));	/* unlock and release vnode */
void 	vrele __P((struct vnode *vp));	/* release vnode */
void 	vgone __P((struct vnode *vp));	/* completely recycle vnode */
void 	vgoneall __P((struct vnode *vp));/* recycle vnode and all its aliases */



E 54
I 54
int	vn_write __P((struct file *fp, struct uio *uio, struct ucred *cred));
I 89
int	vop_noislocked __P((struct vop_islocked_args *));
int	vop_nolock __P((struct vop_lock_args *));
int	vop_nounlock __P((struct vop_unlock_args *));
E 89
I 87
int	vop_revoke __P((struct vop_revoke_args *));
E 87
struct vnode *
	checkalias __P((struct vnode *vp, dev_t nvp_rdev, struct mount *mp));
void 	vput __P((struct vnode *vp));
void 	vref __P((struct vnode *vp));
void 	vrele __P((struct vnode *vp));
I 62
#endif /* KERNEL */
E 62
E 54
E 53
E 1
