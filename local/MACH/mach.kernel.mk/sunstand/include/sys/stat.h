/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	stat.h,v $
 * Revision 2.2  89/07/12  00:14:36  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)stat.h 2.8 88/02/08 SMI; from UCB 4.7 83/05/21	*/

#ifndef __STAT_HEADER__
#define __STAT_HEADER__

struct	stat
{
	dev_t	st_dev;
	ino_t	st_ino;
	unsigned short st_mode;
	short	st_nlink;
	short	st_uid;
	short	st_gid;
	dev_t	st_rdev;
	off_t	st_size;
	time_t	st_atime;
	int	st_spare1;
	time_t	st_mtime;
	int	st_spare2;
	time_t	st_ctime;
	int	st_spare3;
	long	st_blksize;
	long	st_blocks;
	long	st_spare4[2];
};

#define	S_IFMT	0170000		/* type of file */
#define		S_IFDIR	0040000	/* directory */
#define		S_IFCHR	0020000	/* character special */
#define		S_IFBLK	0060000	/* block special */
#define		S_IFREG	0100000	/* regular */
#define		S_IFLNK	0120000	/* symbolic link */
#define		S_IFSOCK 0140000/* socket */
#define		S_IFIFO	0010000	/* fifo */
#define	S_ISUID	0004000		/* set user id on execution */
#define	S_ISGID	0002000		/* set group id on execution */
#define	S_ISVTX	0001000		/* save swapped text even after use */
#define	S_IREAD	0000400		/* read permission, owner */
#define	S_IWRITE 0000200	/* write permission, owner */
#define	S_IEXEC	0000100		/* execute/search permission, owner */

#define	S_IRUSR 0000400		/* read permission, owner */
#define	S_IWUSR 0000200		/* write permission, owner */
#define	S_IXUSR 0000100		/* execute/search permission, owner */
#define	S_IRGRP 0000040		/* read permission, group */
#define	S_IWGRP 0000020		/* write permission, grougroup */
#define	S_IXGRP 0000010		/* execute/search permission, group */
#define	S_IROTH 0000004		/* read permission, other */
#define	S_IWOTH 0000002		/* write permission, other */
#define	S_IXOTH 0000001		/* execute/search permission, other */
#define	S_ENFMT 0000000		/* enforcement-mode locking not implemented */

#endif !__STAT_HEADER__
