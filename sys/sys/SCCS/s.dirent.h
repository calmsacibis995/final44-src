h27117
s 00001/00000/00050
d D 8.3 94/08/10 23:17:35 pendry 7 6
c add whiteout entry type
e
s 00004/00004/00046
d D 8.2 94/07/10 23:01:59 bostic 6 5
c changes for 64-bit machines
e
s 00002/00002/00048
d D 8.1 93/06/02 19:53:01 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00046
d D 7.4 93/02/10 20:29:06 bostic 4 3
c u_short, u_long aren't POSIX, so may not be typdef'd
e
s 00014/00008/00036
d D 7.3 92/06/25 19:13:01 mckusick 3 2
c define directory types for easy mapping to stat structure types
e
s 00014/00001/00030
d D 7.2 92/05/31 21:21:04 mckusick 2 1
c break up namlen into char of namlen and char of file type
e
s 00031/00000/00000
d D 7.1 92/02/06 17:46:50 mckusick 1 0
c extracted from <dirent.h>
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * The dirent structure defines the format of directory entries returned by 
 * the getdirentries(2) system call.
 *
 * A directory entry has a struct dirent at the front of it, containing its
 * inode number, the length of the entry, and the length of the name
 * contained in the entry.  These are followed by the name padded to a 4
 * byte boundary with null bytes.  All names are guaranteed null terminated.
 * The maximum length of a name in a directory is MAXNAMLEN.
 */

struct dirent {
D 4
	u_long	d_fileno;		/* file number of entry */
	u_short	d_reclen;		/* length of this record */
D 2
	u_short	d_namlen;		/* length of string in d_name */
E 2
I 2
	u_char	d_type; 		/* file type, see below */
	u_char	d_namlen;		/* length of string in d_name */
E 4
I 4
D 6
	unsigned long	d_fileno;	/* file number of entry */
	unsigned short	d_reclen;	/* length of this record */
	unsigned char	d_type; 	/* file type, see below */
	unsigned char	d_namlen;	/* length of string in d_name */
E 6
I 6
	u_int32_t d_fileno;		/* file number of entry */
	u_int16_t d_reclen;		/* length of this record */
	u_int8_t  d_type; 		/* file type, see below */
	u_int8_t  d_namlen;		/* length of string in d_name */
E 6
E 4
E 2
#ifdef _POSIX_SOURCE
	char	d_name[255 + 1];	/* name must be no longer than this */
#else
#define	MAXNAMLEN	255
	char	d_name[MAXNAMLEN + 1];	/* name must be no longer than this */
#endif
};
I 2

/*
 * File types
 */
D 3
#define		D_UNKNOWN	0
#define		D_REG		1
#define		D_DIR		2
#define		D_BLK		3
#define		D_CHR		4
#define		D_LNK		5
#define		D_SOCK		6
#define		D_FIFO		7
E 3
I 3
#define	DT_UNKNOWN	 0
#define	DT_FIFO		 1
#define	DT_CHR		 2
#define	DT_DIR		 4
#define	DT_BLK		 6
#define	DT_REG		 8
#define	DT_LNK		10
#define	DT_SOCK		12
I 7
#define	DT_WHT		14
E 7

/*
 * Convert between stat structure types and directory types.
 */
#define	IFTODT(mode)	(((mode) & 0170000) >> 12)
#define	DTTOIF(dirtype)	((dirtype) << 12)
E 3
E 2
E 1
