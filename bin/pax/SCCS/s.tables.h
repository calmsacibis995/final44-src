h20377
s 00002/00002/00144
d D 8.1 93/05/31 14:53:35 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00146/00000/00000
d D 1.1 92/12/13 22:51:39 muller 1 0
c date and time created 92/12/13 22:51:39 by muller
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1992 Keith Muller.
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Keith Muller of the University of California, San Diego.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * data structures and constants used by the different databases kept by pax
 */

/*
 * Hash Table Sizes MUST BE PRIME, if set too small performance suffers.
 * Probably safe to expect 500000 inodes per tape. Assuming good key
 * distribution (inodes) chains of under 50 long (worse case) is ok.
 */
#define L_TAB_SZ	2503		/* hard link hash table size */
#define F_TAB_SZ	50503		/* file time hash table size */
#define N_TAB_SZ	541		/* interactive rename hash table */
#define D_TAB_SZ	317		/* unique device mapping table */
#define A_TAB_SZ	317		/* ftree dir access time reset table */
#define MAXKEYLEN	64		/* max number of chars for hash */

/*
 * file hard link structure (hashed by dev/ino and chained) used to find the
 * hard links in a file system or with some archive formats (cpio)
 */
typedef struct hrdlnk {
	char		*name;	/* name of first file seen with this ino/dev */
	dev_t		dev;	/* files device number */
	ino_t		ino;	/* files inode number */
	u_long		nlink;	/* expected link count */
	struct hrdlnk	*fow;
} HRDLNK;

/*
 * Archive write update file time table (the -u, -C flag), hashed by filename.
 * Filenames are stored in a scratch file at seek offset into the file. The
 * file time (mod time) and the file name length (for a quick check) are
 * stored in a hash table node. We were forced to use a scratch file because
 * with -u, the mtime for every node in the archive must always be available
 * to compare against (and this data can get REALLY large with big archives).
 * By being careful to read only when we have a good chance of a match, the
 * performance loss is not measurable (and the size of the archive we can
 * handle is greatly increased).
 */
typedef struct ftm {
	int		namelen;	/* file name length */
	time_t		mtime;		/* files last modification time */
	off_t		seek;		/* loacation in scratch file */
	struct ftm	*fow;
} FTM;

/*
 * Interactive rename table (-i flag), hashed by orig filename.
 * We assume this will not be a large table as this mapping data can only be
 * obtained through interactive input by the user. Nobody is going to type in
 * changes for 500000 files? We use chaining to resolve collisions.
 */

typedef struct namt {
	char		*oname;		/* old name */
	char		*nname;		/* new name typed in by the user */
	struct namt	*fow;
} NAMT;

/*
 * Unique device mapping tables. Some protocols (e.g. cpio) require that the
 * <c_dev,c_ino> pair will uniquely identify a file in an archive unless they
 * are links to the same file. Appending to archives can break this. For those
 * protocols that have this requirement we map c_dev to a unique value not seen
 * in the archive when we append. We also try to handle inode truncation with
 * this table. (When the inode field in the archive header are too small, we
 * remap the dev on writes to remove accidental collisions).
 *
 * The list is hashed by device number using chain collision resolution. Off of 
 * each DEVT are linked the various remaps for this device based on those bits
 * in the inode which were truncated. For example if we are just remapping to
 * avoid a device number during an update append, off the DEVT we would have
 * only a single DLIST that has a truncation id of 0 (no inode bits were
 * stripped for this device so far). When we spot inode truncation we create
 * a new mapping based on the set of bits in the inode which were stripped off.
 * so if the top four bits of the inode are stripped and they have a pattern of
 * 0110...... (where . are those bits not truncated) we would have a mapping
 * assigned for all inodes that has the same 0110.... pattern (with this dev
 * number of course). This keeps the mapping sparse and should be able to store
 * close to the limit of files which can be represented by the optimal
 * combination of dev and inode bits, and without creating a fouled up archive.
 * Note we also remap truncated devs in the same way (an exercise for the
 * dedicated reader; always wanted to say that...:)
 */

typedef struct devt {
	dev_t		dev;	/* the orig device number we now have to map */
	struct devt	*fow;	/* new device map list */
	struct dlist	*list;	/* map list based on inode truncation bits */
} DEVT;

typedef struct dlist {
	ino_t trunc_bits;	/* truncation pattern for a specific map */
	dev_t dev;		/* the new device id we use */
	struct dlist *fow;
} DLIST;

/*
 * ftree directory access time reset table. When we are done with with a
 * subtree we reset the access and mod time of the directory when the tflag is
 * set. Not really explicitly specified in the pax spec, but easy and fast to
 * do (and this may have even been intended in the spec, it is not clear).
 * table is hashed by inode with chaining.
 */

typedef struct atdir {
	char *name;	/* name of directory to reset */
	dev_t dev;	/* dev and inode for fast lookup */
	ino_t ino;
	time_t mtime;	/* access and mod time to reset to */
	time_t atime;
	struct atdir *fow;
} ATDIR;

/*
 * created directory time and mode storage entry. After pax is finished during
 * extraction or copy, we must reset directory access modes and times that
 * may have been modified after creation (they no longer have the specified
 * times and/or modes). We must reset time in the reverse order of creation,
 * because entries are added  from the top of the file tree to the bottom.
 * We MUST reset times from leaf to root (it will not work the other
 * direction).  Entries are recorded into a spool file to make reverse
 * reading faster.
 */

typedef struct dirdata {
	int nlen;	/* length of the directory name (includes \0) */
	off_t npos;	/* position in file where this dir name starts */
	mode_t mode;	/* file mode to restore */
	time_t mtime;	/* mtime to set */
	time_t atime;	/* atime to set */
	int frc_mode;	/* do we force mode settings? */
} DIRDATA;
E 1
