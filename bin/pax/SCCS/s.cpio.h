h54346
s 00002/00002/00123
d D 8.1 93/05/31 14:52:35 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00017/00010/00108
d D 1.2 93/01/12 02:43:13 muller 2 1
c added ifdef _PAX_ for pax specific defines
e
s 00118/00000/00000
d D 1.1 92/12/13 22:51:34 muller 1 0
c date and time created 92/12/13 22:51:34 by muller
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1992 Keith Muller.
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Keith Muller of the University of California, San Diego.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Defines common to all versions of cpio
 */
#define TRAILER		"TRAILER!!!"	/* name in last archive record */

/*
 * Header encoding of the different file types
 */
#define	C_ISDIR		 040000		/* Directory */
#define	C_ISFIFO	 010000		/* FIFO */
#define	C_ISREG		0100000		/* Regular file */
#define	C_ISBLK		 060000		/* Block special file */
#define	C_ISCHR		 020000		/* Character special file */
#define	C_ISCTG		0110000		/* Reserved for contiguous files */
#define	C_ISLNK		0120000		/* Reserved for symbolic links */
#define	C_ISOCK		0140000		/* Reserved for sockets */
#define C_IFMT		0170000		/* type of file */

/*
D 2
 * Data Interchange Format - Extended cpio Format - POSIX 1003.1-1990
E 2
I 2
 * Data Interchange Format - Extended cpio header format - POSIX 1003.1-1990
E 2
 */
typedef struct {
	char	c_magic[6];		/* magic cookie */
	char	c_dev[6];		/* device number */
	char	c_ino[6];		/* inode number */
	char	c_mode[6];		/* file type/access */
	char	c_uid[6];		/* owners uid */
	char	c_gid[6];		/* owners gid */
	char	c_nlink[6];		/* # of links at archive creation */
	char	c_rdev[6];		/* block/char major/minor # */
	char	c_mtime[11];		/* modification time */
	char	c_namesize[6];		/* length of pathname */
	char	c_filesize[11];		/* length of file in bytes */
} HD_CPIO; 

#define	MAGIC		070707		/* transportable archive id */
D 2
#define	AMAGIC		"070707"	/* ascii string of above */
E 2
I 2

#ifdef _PAX_
#define	AMAGIC		"070707"	/* ascii equivalent string of MAGIC */
E 2
#define CPIO_MASK	0x3ffff		/* bits valid in the dev/ino fields */
					/* used for dev/inode remaps */
I 2
#endif /* _PAX_ */
E 2

/*
D 2
 * Binary cpio structure 
E 2
I 2
 * Binary cpio header structure 
E 2
 *
 * CAUTION! CAUTION! CAUTION!
D 2
 * Each field really represents a 16 bit short (NOT ASCII). We deal with it as
E 2
I 2
 * Each field really represents a 16 bit short (NOT ASCII). Described as
E 2
 * an array of chars in an attempt to improve portability!!
 */
typedef struct {
	u_char	h_magic[2];
	u_char	h_dev[2];
	u_char	h_ino[2];
	u_char	h_mode[2];
	u_char	h_uid[2];
	u_char	h_gid[2];
	u_char	h_nlink[2];
	u_char	h_rdev[2];
	u_char	h_mtime_1[2];
	u_char	h_mtime_2[2];
	u_char	h_namesize[2];
	u_char	h_filesize_1[2];
	u_char	h_filesize_2[2];
} HD_BCPIO; 

I 2
#ifdef _PAX_
E 2
/*
D 2
 * extraction and creation macros
E 2
I 2
 * extraction and creation macros for binary cpio
E 2
 */
#define SHRT_EXT(ch)	((((unsigned)(ch)[0])<<8) | (((unsigned)(ch)[1])&0xff))
#define RSHRT_EXT(ch)	((((unsigned)(ch)[1])<<8) | (((unsigned)(ch)[0])&0xff))
#define CHR_WR_0(val)	((char)(((val) >> 24) & 0xff))
#define CHR_WR_1(val)	((char)(((val) >> 16) & 0xff))
#define CHR_WR_2(val)	((char)(((val) >> 8) & 0xff))
#define CHR_WR_3(val)	((char)((val) & 0xff))

/*
D 2
 * masks and pads
E 2
I 2
 * binary cpio masks and pads
E 2
 */
#define BCPIO_PAD(x)	((2 - ((x) & 1)) & 1)	/* pad to next 2 byte word */
#define BCPIO_MASK	0xffff			/* mask for dev/ino fields */
I 2
#endif /* _PAX_ */
E 2

/*
D 2
 * System VR4 cpio structure 
E 2
I 2
 * System VR4 cpio header structure (with/without file data crc)
E 2
 */
typedef struct {
	char	c_magic[6];		/* magic cookie */
	char	c_ino[8];		/* inode number */
	char	c_mode[8];		/* file type/access */
	char	c_uid[8];		/* owners uid */
	char	c_gid[8];		/* owners gid */
	char	c_nlink[8];		/* # of links at archive creation */
	char	c_mtime[8];		/* modification time */
	char	c_filesize[8];		/* length of file in bytes */
	char	c_maj[8];		/* block/char major # */
	char	c_min[8];		/* block/char minor # */
	char	c_rmaj[8];		/* special file major # */
	char	c_rmin[8];		/* special file minor # */
	char	c_namesize[8];		/* length of pathname */
D 2
	char	c_chksum[8];		/* 0 OR CRC of bytes in FILE */
E 2
I 2
	char	c_chksum[8];		/* 0 OR CRC of bytes of FILE data */
E 2
} HD_VCPIO; 

#define	VMAGIC		070701		/* sVr4 new portable archive id */
D 2
#define	AVMAGIC		"070701"	/* ascii string of above */
E 2
#define	VCMAGIC		070702		/* sVr4 new portable archive id CRC */
I 2
#ifdef _PAX_
#define	AVMAGIC		"070701"	/* ascii string of above */
E 2
#define	AVCMAGIC	"070702"	/* ascii string of above */
D 2
#define VCPIO_PAD(x)	((4 - ((x) & 3)) & 3)	/*pad to next 4 byte word */
E 2
I 2
#define VCPIO_PAD(x)	((4 - ((x) & 3)) & 3)	/* pad to next 4 byte word */
E 2
#define VCPIO_MASK	0xffffffff	/* mask for dev/ino fields */
I 2
#endif /* _PAX_ */
E 2
E 1
