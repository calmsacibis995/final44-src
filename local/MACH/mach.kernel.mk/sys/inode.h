/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	inode.h,v $
 * Revision 2.13  90/07/03  16:50:12  mrt
 * 	Added an inode type for the Coda file system.
 * 	[90/05/23            dcs]
 * 
 * Revision 2.12  90/02/09  12:30:54  berman
 * 	Fixed #define for i_socket to point into vnode (inode_header),
 * 	not inode.
 * 	[90/02/09            parker]
 * 
 * Revision 2.11  89/10/10  11:00:14  mwyoung
 * 	Make fast symbolic links an architecture-independent option.
 * 	[89/05/12  16:04:39  mwyoung]
 * 
 * Revision 2.10  89/05/30  10:43:23  rvb
 * 	Byte order-dependencies are keyed on BYTE_MSF now.
 * 	[89/04/20            af]
 * 
 * Revision 2.9  89/04/22  15:31:48  gm0w
 * 	Removed MACH_VFS code.  Changed to include new inode macros for
 * 	manipulation of inodes using either <kern/inode_macros.h> or
 * 	<vfs/inode_macros.h> depending upon MACH_VFS.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.8  89/03/09  22:04:57  rpd
 * 	More cleanup.
 * 
 * Revision 2.7  89/02/27  21:03:46  mrt
 * 	Defined MACH_VFS to be true outside the kernel. Thus the
 * 	inode structure will only be correct outside of the kernel
 * 	for MACH_VFS kernels. Made the VICE and MACH_RFS 
 * 	conditionals in the inode struct be always true.
 * 	[89/02/27            mrt]
 * 
 * Revision 2.6  89/02/25  17:54:10  gm0w
 * 	Made all CMUCS conditionals always true. Removed include
 * 	of cputypes.h by using compiler defined symbols for all
 * 	machine types. Made all the conditionals on MACH_VFS outside
 * 	the kernel true and the VICE conditionals outside the kernel
 * 	false (for X75 binary compatibility -  needs to be fixed.
 * 	[89/02/13            mrt]
 * 
 * Revision 2.5  89/01/23  22:26:22  af
 * 	Added Mips byte-order dependencies.
 * 	[89/01/09            af]
 * 	
 * 	Changes for I386: treat like a vax.  But why should file system
 * 	need to know byte ordering?  Ans.  Some genius decided that the
 * 	file size is 64 bits.
 * 	[89/01/09            rvb]
 * 
 * Revision 2.4  89/01/18  01:16:06  jsb
 * 	Add vnode support by merging the Mach (bsd) and Sun versions of this
 * 	file. Yuck.
 * 	[89/01/13            jsb]
 * 
 * Revision 2.3  88/08/24  02:28:52  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:13:20  mwyoung]
 *
 * 27-Oct-87  Peter King (king) at NeXT
 *	MACH_VFS: Added NFS support.
 *
 * 25-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Use vm_info field regardless of which options are enabled.
 *
 * 27-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	MACH_NBC: add vm_info field which holds pointer to information
 *	about the potentially mapped files.
 *
 *  7-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Merge VICE changes -- include vice.h and change to #if VICE.
 *
 * 22-Jan-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH_XP: Correct type for inode.pager field.
 *
 * 22-Dec-86  David L. Black (dlb) at Carnegie-Mellon University
 *	MULTIMAX: support Encore's fast symbolic links.
 *
 *  2-Dec-86  Jay Kistler (jjk) at Carnegie-Mellon University
 *	VICE: added i_rmt_dev field to "inode" struct;
 *	added vicemagic definitions.
 *
 * 21-Oct-86  Jonathan J. Chew at Carnegie-Mellon University
 *	Use romp definition of "i_size" and "di_size" fields in inode
 *	structure with 68000.
 *
 * 14-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added changes for ns32000 byte ordering (from dlb).
 *
 * 31-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Set the pager_id field in the inode structure.  This is a back
 *	pointer to the real pager id which will allow for pager id's to
 *	be different than inode numbers.
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 18-Feb-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	Added different definitions of i_size and di_size for Sailboat
 *	from IBM code under switch ROMP.  These differences are
 *	presumably because of byte ordering differences.
 *
 * 20-Jul-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RFS:  Changed to declare cnamei() rather than namei.
 *	[V1(1)]
 *
 * 13-May-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Upgraded to 4.2BSD.  Carried over change below.
 *
 * 20-Feb-82  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_ICHK: Added iincr_chk() and idecr_chk() macros to modify inode
 *	reference counts and check for consistency (V3.04c).
 *
 */
 /*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)inode.h	7.1 (Berkeley) 6/4/86
 */

#ifndef	_SYS_INODE_H_
#define _SYS_INODE_H_

/*
 * The I node is the focus of all file activity in UNIX.
 * There is a unique inode allocated for each active file,
 * each current directory, each mounted-on file, text file, and the root.
 * An inode is 'named' by its dev/inumber pair. (iget/iget.c)
 * Data in icommon is read in from permanent inode on volume.
 */

#if	KERNEL
#include <mach_rfs.h>
#include <mach_vfs.h>
#include <mach_fastlink.h>
#if	MACH_VFS
#include <vfs/inode_macros.h>
#else	MACH_VFS
#include <kern/inode_macros.h>
#endif	MACH_VFS
#else	KERNEL
#ifndef	MACH_RFS
#define	MACH_RFS	1
#endif	MACH_RFS
#ifndef	MACH_VFS
#define	MACH_VFS	1
#endif	MACH_VFS
#ifndef	MACH_FASTLINK
#define	MACH_FASTLINK	1
#endif	MACH_FASTLINK
#endif	KERNEL

#include <sys/types.h>

#if	MACH_RFS
/*
 *  The following macro is used to identify the special CMU file type which is
 *  currently used to implement remote node pointer files.
 */
#define isesctype(ip)	\
	((ip)->i_gid == 64)

/*
 *  The following macro is used to distinguish the special CMU
 *  remote node pointer.
 */
#define isrfslnk(ip)	\
	( isesctype(ip) && \
	  ( (((ip)->i_mode&(IFMT|IEXEC|(IEXEC>>3)|(IEXEC>>6))) == (IFREG|IEXEC)) || \
	    (((ip)->i_mode&(IFMT|IEXEC|(IEXEC>>3)|(IEXEC>>6))) == (IFLNK|IEXEC)) \
	  ) \
	)
#endif	MACH_RFS

#define NDADDR	12		/* direct addresses in inode */
#define NIADDR	3		/* indirect addresses in inode */

#define MAX_FASTLINK_SIZE	((NDADDR + NIADDR) * sizeof (daddr_t))

/* inode header */
struct inode_header {
	struct inode_header *ih_chain[2]; /* must be first */
	u_short ih_type;	/* inode type (see below) */
	u_short	ih_flag;	/* inode flags (see below) */
	u_short	ih_count;	/* reference count */
	u_short	ih_shlockc;	/* count of shared locks on inode */
	u_short	ih_exlockc;	/* count of exclusive locks on inode */
	u_short ih_mode;	/* mode/type of inode */
	dev_t ih_rdev;		/* block or char device */
	struct socket *ih_socket; /* unix socket */
	struct vfs *ih_mountedfs; /* filesystem mounted here */
	struct vfs *ih_fs;	/* filesystem we are in */
	struct vm_info *ih_vm_info; /* pointer to VM info structure */
} i_header;

struct inode {
	struct inode_header i_header; /* inode header */
#define	i_chain		i_header.ih_chain
#define	i_type		i_header.ih_type
#define	i_flag		i_header.ih_flag
#define	i_count		i_header.ih_count
#define	i_shlockc	i_header.ih_shlockc
#define	i_exlockc	i_header.ih_exlockc
#define	i_socket	i_header.ih_socket
#define	i_vm_info	i_header.ih_vm_info
	dev_t	i_dev;		/* device where inode resides */
	struct	inode *i_devp;	/* inode for block I/O */
	ino_t	i_number;	/* i number, 1-to-1 with device address */
	int	i_diroff;	/* offset in dir, where we found last entry */
	long	i_id;		/* unique identifier */
	struct	fs *i_fs;	/* file sys associated with this inode */
	struct	dquot *i_dquot;	/* quota structure controlling this file */
	struct	text *i_text;	/* text entry, if any (should be region) */
	union {
		daddr_t	if_lastr;	/* last read (read-ahead) */
		struct	socket *is_socket;
		struct	{
			struct inode  *if_freef;	/* free list forward */
			struct inode **if_freeb;	/* free list back */
		} i_fr;
	} i_un;
	struct 	icommon
	{
		u_short	ic_mode;	/*  0: mode and type of file */
		short	ic_nlink;	/*  2: number of links to file */
		uid_t	ic_uid;		/*  4: owner's user id */
		gid_t	ic_gid;		/*  6: owner's group id */
		quad	ic_size;	/*  8: number of bytes in file */
		time_t	ic_atime;	/* 16: time last accessed */
		long	ic_atspare;
		time_t	ic_mtime;	/* 24: time last modified */
		long	ic_mtspare;
		time_t	ic_ctime;	/* 32: last time inode changed */
		long	ic_ctspare;
#if	MACH_FASTLINK
		union {
		    struct { 
			daddr_t	Mb_db[NDADDR]; /* 40: disk block addresses*/
			daddr_t	Mb_ib[NIADDR]; /* 88: indirect blocks */
		    } ic_Mb;
#define ic_db	ic_Mun.ic_Mb.Mb_db
#define ic_ib	ic_Mun.ic_Mb.Mb_ib
		    char	ic_Msymlink[MAX_FASTLINK_SIZE];
						/* 40: symbolic link name */
		} ic_Mun;
#define ic_symlink	ic_Mun.ic_Msymlink
#else	MACH_FASTLINK
		daddr_t	ic_db[NDADDR];	/* 40: disk block addresses */
		daddr_t	ic_ib[NIADDR];	/* 88: indirect blocks */
#endif	MACH_FASTLINK
		long	ic_flags;	/* 100: status, currently unused */
#define IC_FASTLINK	0x0001		/* Symbolic link in inode */
		long	ic_blocks;	/* 104: blocks actually held */
		long	ic_gen;		/* 108: generation number */
		long	ic_spare[4];	/* 112: reserved, currently unused */
	} i_ic;

	dev_t	i_rmt_dev;	/* device for VICE communications with an agent
				   process maintaining a remote fs */
};

struct dinode {
	union {
		struct	icommon di_icom;
		char	di_size[128];
	} di_un;
};

#define	ITOIH(ip)	((struct inode_header *)(ip))
#define	IHTOI(ihp)	((struct inode *)(ihp))

#define i_mode		i_ic.ic_mode
#define i_nlink		i_ic.ic_nlink
#define i_uid		i_ic.ic_uid
#define i_gid		i_ic.ic_gid
#if	BYTE_MSF
#define i_size		i_ic.ic_size.val[1]
#else	BYTE_MSF
#define i_size		i_ic.ic_size.val[0]
#endif	BYTE_MSF
#define i_db		i_ic.ic_db
#define i_ib		i_ic.ic_ib
#define i_symlink	i_ic.ic_symlink
#define i_icflags	i_ic.ic_flags
#define i_atime		i_ic.ic_atime
#define i_mtime		i_ic.ic_mtime
#define i_ctime		i_ic.ic_ctime
#define i_blocks	i_ic.ic_blocks
#define i_rdev		i_ic.ic_db[0]
#define i_gen		i_ic.ic_gen
#define i_lastr		i_un.if_lastr
/* #define i_socket	i_un.is_socket */
#define i_forw		i_chain[0]
#define i_back		i_chain[1]
#define i_freef		i_un.i_fr.if_freef
#define i_freeb		i_un.i_fr.if_freeb
	/* used by VICE code */
#define i_vicemagic	i_ic.ic_gen
#define VICEMAGIC	0x84fa1cb6
#define i_vicep1	i_ic.ic_spare[0]
#define i_vicep2	i_ic.ic_spare[1]
#define i_vicep3	i_ic.ic_spare[2]
#define i_vicep4	i_ic.ic_spare[3]

#define di_ic		di_un.di_icom
#define di_mode		di_ic.ic_mode
#define di_nlink	di_ic.ic_nlink
#define di_uid		di_ic.ic_uid
#define di_gid		di_ic.ic_gid
#if	BYTE_MSF
#define di_size		di_ic.ic_size.val[1]
#else	BYTE_MSF
#define di_size		di_ic.ic_size.val[0]
#endif	BYTE_MSF
#define di_db		di_ic.ic_db
#define di_ib		di_ic.ic_ib
#define di_symlink	di_ic.ic_symlink
#define di_icflags	di_ic.ic_flags
#define di_atime	di_ic.ic_atime
#define di_mtime	di_ic.ic_mtime
#define di_ctime	di_ic.ic_ctime
#define di_rdev		di_ic.ic_db[0]
#define di_blocks	di_ic.ic_blocks
#define di_gen		di_ic.ic_gen
	/* used by VICE code */
#define di_vicemagic	di_ic.ic_gen
#define di_vicep1	di_ic.ic_spare[0]
#define di_vicep2	di_ic.ic_spare[1]
#define di_vicep3	di_ic.ic_spare[2]
#define di_vicep4	di_ic.ic_spare[3]


#ifdef	KERNEL
#include <kern/macro_help.h>

extern struct inode *inode;		/* the inode table itself */
extern struct inode *inodeNINODE;	/* the end of the inode table */
extern int	ninode;			/* number of slots in the table */

extern long	nextinodeid;	/* unique id generator */
extern struct	inode *rootdir;	/* pointer to inode of root directory */

/*
 * Invalidate an inode. Used by the namei cache to detect stale
 * information. At an absurd rate of 100 calls/second, the inode
 * table invalidation should only occur once every 16 months.
 */
#define cacheinval(ip)			\
MACRO_BEGIN				\
	(ip)->i_id = ++nextinodeid;	\
	if (nextinodeid == 0)		\
		cacheinvalall();	\
MACRO_END

extern struct	inode *ialloc();
extern struct	inode *iget();
extern struct	inode *owner();
extern struct	inode *maknode();
#if	MACH_RFS
extern struct	inode *cnamei();
#else	MACH_RFS
extern struct	inode *namei();
#endif	MACH_RFS

extern ino_t	dirpref();
#endif	KERNEL

/* types */
#define	ITYPE_UFS	0
#define	ITYPE_NFS	1
#define	ITYPE_AFS	2
#define	ITYPE_BDEV	3
#define	ITYPE_SPEC	4
#define ITYPE_CFS	5

/* flags */
#define ILOCKED		0x1		/* inode is locked */
#define IUPD		0x2		/* file has been modified */
#define IACC		0x4		/* inode access time to be updated */
#define IMOUNT		0x8		/* inode is mounted on */
#define IWANT		0x10		/* some process waiting on lock */
#define ITEXT		0x20		/* inode is pure text prototype */
#define ICHG		0x40		/* inode has been changed */
#define ISHLOCK		0x80		/* file has shared lock */
#define IEXLOCK		0x100		/* file has exclusive lock */
#define ILWAIT		0x200		/* someone waiting on file lock */
#define IMOD		0x400		/* inode has been modified */
#define IRENAME		0x800		/* inode is being renamed */
#define IREMOTE		0x1000		/* inode is remote.  Note, this
					   is only used for inodes that are
					   opened without a file descrip-
					   tor, by the kernel - VICE */
#define IREF		0x2000		/* inode is being referenced */
#define	IROOT		0x4000		/* inode is root inode */

/* modes */
#define IFMT		0170000		/* type of file */
#define IFCHR		0020000		/* character special */
#define IFDIR		0040000		/* directory */
#define IFBLK		0060000		/* block special */
#define IFREG		0100000		/* regular */
#define IFLNK		0120000		/* symbolic link */
#define IFSOCK		0140000		/* socket */

#define ISUID		04000		/* set user id on execution */
#define ISGID		02000		/* set group id on execution */
#define ISVTX		01000		/* save swapped text even after use */
#define IREAD		0400		/* read, write, execute permissions */
#define IWRITE		0200
#define IEXEC		0100

#ifdef	KERNEL
/*
 * Fast link runtime controls
 */

#if	MACH_FASTLINK
extern	int		use_fastlinks;
extern	int		create_fastlinks;
#endif	MACH_FASTLINK

/*
 * Lock and unlock inodes.
 */

#define ILOCK(ip)				\
MACRO_BEGIN					\
	while ((ip)->i_flag & ILOCKED) {	\
		(ip)->i_flag |= IWANT;		\
		sleep((caddr_t)(ip), PINOD);	\
	}					\
	(ip)->i_flag |= ILOCKED;		\
MACRO_END

#define IUNLOCK(ip)				\
MACRO_BEGIN					\
	(ip)->i_flag &= ~ILOCKED;		\
	if ((ip)->i_flag&IWANT) {		\
		(ip)->i_flag &= ~IWANT;		\
		wakeup((caddr_t)(ip));		\
	}					\
MACRO_END

#define IUPDAT(ip, t1, t2, waitfor)		\
MACRO_BEGIN					\
	if (INODE_CHANGED(ip))			\
		iupdat(ip, t1, t2, waitfor);	\
MACRO_END

#define ITIMES(ip, t1, t2)				\
MACRO_BEGIN						\
	if ((ip)->i_flag&(IUPD|IACC|ICHG)) {		\
		(ip)->i_flag |= IMOD;			\
		if ((ip)->i_flag&IACC)			\
			(ip)->i_atime = (t1)->tv_sec;	\
		if ((ip)->i_flag&IUPD)			\
			(ip)->i_mtime = (t2)->tv_sec;	\
		if ((ip)->i_flag&ICHG)			\
			(ip)->i_ctime = time.tv_sec;	\
		(ip)->i_flag &= ~(IACC|IUPD|ICHG);	\
	}						\
MACRO_END
#endif	KERNEL
#endif	_SYS_INODE_H_
