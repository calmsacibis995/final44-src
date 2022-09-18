h12775
s 00010/00000/00112
d D 8.2 94/04/18 14:02:29 bostic 4 3
c new version from Keith Muller (muller@sdcc3.ucsd.edu)
e
s 00002/00002/00110
d D 8.1 93/05/31 14:53:43 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00048/00026/00064
d D 1.2 93/01/14 15:21:41 muller 2 1
c added ifdef _PAX_ for pax specific defines. Cleaned up a bit.
e
s 00090/00000/00000
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
 * defines and data structures common to all tar formats
 */
D 2
#define NULLCNT		2		/* number of null blks in trailer */
E 2
I 2
#define CHK_LEN		8		/* length of checksum field */
E 2
#define TNMSZ		100		/* size of name field */
I 2
#ifdef _PAX_
#define NULLCNT		2		/* number of null blocks in trailer */
E 2
#define CHK_OFFSET	148		/* start of chksum field */
D 2
#define CHK_LEN		8		/* length of checksum field */
E 2
#define BLNKSUM		256L		/* sum of checksum field using ' ' */
I 2
#endif /* _PAX_ */
E 2

/*
D 2
 * Pad with a bit mask, much faster than doing a mod but only works on powers
 * of 2. Macro below is for block of 512 bytes.
E 2
I 2
 * Values used in typeflag field in all tar formats
 * (only REGTYPE, LNKTYPE and SYMTYPE are used in old bsd tar headers)
E 2
 */
D 2
#define TAR_PAD(x)	((512 - ((x) & 511)) & 511)
E 2
I 2
#define	REGTYPE		'0'		/* Regular File */
#define	AREGTYPE	'\0'		/* Regular File */
#define	LNKTYPE		'1'		/* Link */
#define	SYMTYPE		'2'		/* Symlink */
#define	CHRTYPE		'3'		/* Character Special File */
#define	BLKTYPE		'4'		/* Block Special File */
#define	DIRTYPE		'5'		/* Directory */
#define	FIFOTYPE	'6'		/* FIFO */
#define	CONTTYPE	'7'		/* high perf file */
E 2

/*
D 2
 * -o options for telling tar to not write directories to the archive
E 2
I 2
 * Mode field encoding of the different file types - values in octal
E 2
 */
D 2
#define TAR_NODIR	"nodir"
#define TAR_OPTION	"write_opt"
E 2
I 2
#define TSUID		04000		/* Set UID on execution */
#define TSGID		02000		/* Set GID on execution */
#define TSVTX		01000		/* Reserved */
#define TUREAD		00400		/* Read by owner */
#define TUWRITE		00200		/* Write by owner */
#define TUEXEC		00100		/* Execute/Search by owner */
#define TGREAD		00040		/* Read by group */
#define TGWRITE		00020		/* Write by group */
#define TGEXEC		00010		/* Execute/Search by group */
#define TOREAD		00004		/* Read by other */
#define TOWRITE		00002		/* Write by other */
#define TOEXEC		00001		/* Execute/Search by other */
E 2

I 2
#ifdef _PAX_
E 2
/*
D 2
 * structure of an old tar header as appeared in BSD releases
E 2
I 2
 * Pad with a bit mask, much faster than doing a mod but only works on powers
 * of 2. Macro below is for block of 512 bytes.
E 2
 */
I 2
#define TAR_PAD(x)	((512 - ((x) & 511)) & 511)
#endif /* _PAX_ */

/*
 * structure of an old tar header as it appeared in BSD releases
 */
E 2
typedef struct {
	char name[TNMSZ];		/* name of entry */
	char mode[8]; 			/* mode */
	char uid[8]; 			/* uid */
	char gid[8];			/* gid */
	char size[12];			/* size */
	char mtime[12];			/* modification time */
D 2
	char chksum[8];			/* checksum */
E 2
I 2
	char chksum[CHK_LEN];		/* checksum */
E 2
	char linkflag;			/* norm, hard, or sym. */
	char linkname[TNMSZ];		/* linked to name */
} HD_TAR;

I 2
#ifdef _PAX_
E 2
/*
D 2
 * Data Interchange Format - Extended tar Format - POSIX 1003.1-1990
E 2
I 2
 * -o options for BSD tar to not write directories to the archive
E 2
 */
I 2
#define TAR_NODIR	"nodir"
#define TAR_OPTION	"write_opt"
I 4

/*
 * default device names
 */
#define	DEV_0		"/dev/rmt0"
#define	DEV_1		"/dev/rmt1"
#define	DEV_4		"/dev/rmt4"
#define	DEV_5		"/dev/rmt5"
#define	DEV_7		"/dev/rmt7"
#define	DEV_8		"/dev/rmt8"
E 4
#endif /* _PAX_ */

/*
 * Data Interchange Format - Extended tar header format - POSIX 1003.1-1990
 */
E 2
#define TPFSZ		155
#define	TMAGIC		"ustar"		/* ustar and a null */
#define	TMAGLEN		6
#define	TVERSION	"00"		/* 00 and no null */
#define	TVERSLEN	2

typedef struct {
	char name[TNMSZ];		/* name of entry */
	char mode[8]; 			/* mode */
	char uid[8]; 			/* uid */
	char gid[8];			/* gid */
	char size[12];			/* size */
	char mtime[12];			/* modification time */
D 2
	char chksum[8];			/* checksum */
E 2
I 2
	char chksum[CHK_LEN];		/* checksum */
E 2
	char typeflag;			/* type of file. */
	char linkname[TNMSZ];		/* linked to name */
	char magic[TMAGLEN];		/* magic cookie */
	char version[TVERSLEN];		/* version */
	char uname[32];			/* ascii owner name */
	char gname[32];			/* ascii group name */
	char devmajor[8];		/* major device number */
	char devminor[8];		/* minor device number */
	char prefix[TPFSZ];		/* linked to name */
} HD_USTAR;
D 2

/*
 * Values used in typeflag field
 * (only REGTYPE, LNKTYPE and SYMTYPE are used in old tar headers)
 */
#define	REGTYPE		'0'		/* Regular File */
#define	AREGTYPE	'\0'		/* Regular File */
#define	LNKTYPE		'1'		/* Link */
#define	SYMTYPE		'2'		/* Symlink */
#define	CHRTYPE		'3'		/* Character Special File */
#define	BLKTYPE		'4'		/* Block Special File */
#define	DIRTYPE		'5'		/* Directory */
#define	FIFOTYPE	'6'		/* FIFO */
#define	CONTTYPE	'7'		/* high perf file */
E 2
E 1
