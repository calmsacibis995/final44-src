h44733
s 00066/00065/00241
d D 8.2 94/07/10 22:52:48 bostic 28 27
c changes for 64-bit machines; reformat the comments
e
s 00002/00002/00304
d D 8.1 93/06/02 19:53:06 bostic 27 26
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00303
d D 7.25 93/05/24 23:24:35 torek 26 25
c pedantically ANSI, i.e., nothing after #else/#endif
e
s 00002/00000/00304
d D 7.24 93/03/09 10:17:30 hibler 25 24
c add FS_BOOT to identify partitions with bootstrap code
e
s 00004/00002/00300
d D 7.23 92/12/21 08:52:53 hibler 24 23
c add HP types (cs80 and fiberlink)
e
s 00006/00000/00296
d D 7.22 92/11/10 17:02:24 mckusick 23 22
c names from BSDI for PC type filesystems
e
s 00002/00001/00294
d D 7.21 91/11/04 14:36:53 mckusick 22 20
c add LFS file system type
e
s 00013/00014/00281
d R 7.21 91/11/04 11:57:43 bostic 21 20
c add typename for LFS, integrate comments into structure.  Not sure this
c will compile everywhere, but if it had been integrated before I wouldn't
c have missed the typename.
e
s 00007/00001/00288
d D 7.20 91/11/01 16:32:33 bostic 20 19
c LFS version 1; how to find other superblocks if standard one bad
e
s 00000/00001/00289
d D 7.19 91/05/07 07:09:14 william 19 18
c MAXPARTITIONS enforced differently on i386; no need for bigger const
e
s 00004/00001/00286
d D 7.18 91/04/28 16:26:01 william 18 17
c errata
e
s 00003/00001/00284
d D 7.17 91/04/28 16:11:14 william 17 16
c added ST506 and MSDOS fields
e
s 00010/00000/00275
d D 7.16 91/04/28 15:25:25 william 16 15
c added label sector for i386, different from tahoe/vax
e
s 00007/00005/00268
d D 7.15 91/02/05 17:04:24 bostic 15 14
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00011/00272
d D 7.14 90/06/28 21:58:30 bostic 14 13
c new copyright notice
e
s 00001/00001/00282
d D 7.13 90/05/29 19:29:47 bostic 13 12
c C++ needs prototypes, too
e
s 00005/00000/00278
d D 7.12 90/05/15 08:51:08 bostic 12 11
c add SCSI d_blind
e
s 00007/00002/00271
d D 7.11 90/03/06 17:07:55 bostic 11 10
c add ANSI C prototypes, rename the path constant
e
s 00011/00006/00262
d D 7.10 88/06/27 18:41:27 bostic 10 9
c install approved copyright notice
e
s 00007/00001/00261
d D 7.9 88/04/14 12:12:25 karels 9 8
c add ioctl to resynch bad sector table; no union in kernel or standalone
c (so can initialize)
e
s 00022/00005/00240
d D 7.8 88/02/08 21:53:00 karels 8 7
c getdiskbyname needs alt. bootstrap return
e
s 00018/00008/00227
d D 7.7 87/12/18 11:31:15 bostic 7 6
c add Berkeley header, fix for ANSI C
e
s 00003/00003/00232
d D 7.6 87/11/23 12:55:02 karels 6 5
c cast magic to u_long
e
s 00010/00001/00225
d D 7.5 87/03/27 17:48:19 karels 5 4
c add partinfo structure, op
e
s 00009/00014/00217
d D 7.4 87/02/02 22:25:33 karels 4 3
c forget byteswapping
e
s 00002/00001/00229
d D 7.3 87/01/19 15:19:36 karels 3 2
c keep npartitions independent of byte order
e
s 00089/00039/00141
d D 7.2 87/01/19 14:15:43 karels 2 1
c new fields for interleaving and spares, various cleanups
e
s 00180/00000/00000
d D 7.1 86/12/19 11:35:47 karels 1 0
c date and time created 86/12/19 11:35:47 by karels
e
u
U
t
T
I 1
/*
I 7
D 8
 * Copyright (c) 1987 Regents of the University of California.
E 8
I 8
D 10
 * Copyright (c) 1987,1988 Regents of the University of California.
E 10
I 10
D 27
 * Copyright (c) 1987, 1988 Regents of the University of California.
E 10
E 8
 * All rights reserved.
E 27
I 27
 * Copyright (c) 1987, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 27
 *
D 14
 * Redistribution and use in source and binary forms are permitted
D 10
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 10
I 10
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 14
I 14
 * %sccs.include.redist.c%
E 14
E 10
 *
E 7
 *	%W% (Berkeley) %G%
 */

/*
 * Disk description table, see disktab(5)
 */
D 11
#define	DISKTAB		"/etc/disktab"
E 11
I 11
#define	_PATH_DISKTAB	"/etc/disktab"
#define	DISKTAB		"/etc/disktab"		/* deprecated */
E 11

/*
 * Each disk has a label which includes information about the hardware
 * disk geometry, filesystem partitions, and drive specific information.
 * The label is in block 0 or 1, possibly offset from the beginning
 * to leave room for a bootstrap, etc.
I 2
D 4
 * All fields are stored in "standard" (network) byte order.
E 4
E 2
 */

I 16
/* XXX these should be defined per controller (or drive) elsewhere, not here! */
#ifdef i386
#define LABELSECTOR	1			/* sector containing label */
#define LABELOFFSET	0			/* offset of label in sector */
D 19
#define	MAXPARTITIONS	32
E 19
#endif

D 18
#ifdef	LABELSECTOR
E 18
I 18
#ifndef	LABELSECTOR
E 18
E 16
D 6
#define LABELSECTOR	0		/* sector containing label */
#define LABELOFFSET	64		/* offset of label in sector */
#define DISKMAGIC	0x82564557	/* The disk magic number */
E 6
I 6
#define LABELSECTOR	0			/* sector containing label */
I 18
#endif

#ifndef	LABELOFFSET
E 18
#define LABELOFFSET	64			/* offset of label in sector */
I 16
#endif

E 16
D 28
#define DISKMAGIC	((u_long) 0x82564557)	/* The disk magic number */
E 28
I 28
#define DISKMAGIC	((u_int32_t)0x82564557)	/* The disk magic number */
E 28
E 6
#ifndef MAXPARTITIONS
#define	MAXPARTITIONS	8
#endif

D 2
#define	DTYPE_SMD		1		/* SMD, XSMD; VAX hp/up */
#define	DTYPE_MSCP		2		/* MSCP */
#define	DTYPE_DEC		3		/* other DEC (rk, rl) */
#define	DTYPE_SCSI		4		/* SCSI/ST506 etc. */
#define	DTYPE_ESDI		5		/* ESDI interface */
#define	DTYPE_FLOPPY		10		/* floppy */
E 2

D 2
#ifdef DKTYPENAMES
static char *dktypenames[] = {
	"unknown",
	"SMD",
	"MSCP",
	"old DEC",
	"SCSI",
	"ESDI",
	"type 6",
	"type 7",
	"type 8",
	"type 9",
	"floppy",
	0
};
#define DKMAXTYPES	(sizeof(dktypenames) / sizeof(dktypenames[0]) - 1)
#endif


E 2
#ifndef LOCORE
struct disklabel {
D 28
	u_long	d_magic;		/* the magic number */
	short	d_type;			/* drive type */
	short	d_subtype;		/* controller/d_type specific */
I 2
	char	d_typename[16];		/* type name, e.g. "eagle" */
E 28
I 28
	u_int32_t d_magic;		/* the magic number */
	u_int16_t d_type;		/* drive type */
	u_int16_t d_subtype;		/* controller/d_type specific */
	char	  d_typename[16];	/* type name, e.g. "eagle" */

E 28
D 8
	char	d_name[16];		/* pack identifier */
D 4
#define	d_swabfirst d_secsize
E 4

E 8
I 8
	/* 
	 * d_packname contains the pack identifier and is returned when
	 * the disklabel is read off the disk or in-core copy.
	 * d_boot0 and d_boot1 are the (optional) names of the
	 * primary (block 0) and secondary (block 1-15) bootstraps
	 * as found in /usr/mdec.  These are returned when using
	 * getdiskbyname(3) to retrieve the values from /etc/disktab.
	 */
D 9
	 union {
E 9
I 9
#if defined(KERNEL) || defined(STANDALONE)
D 28
	char	d_packname[16];			/* pack identifier */ 
E 28
I 28
	char	  d_packname[16];		/* pack identifier */ 
E 28
#else
	union {
E 9
		char	un_d_packname[16];	/* pack identifier */ 
		struct {
			char *un_d_boot0;	/* primary bootstrap name */
			char *un_d_boot1;	/* secondary bootstrap name */
		} un_b; 
	} d_un; 
#define d_packname	d_un.un_d_packname
#define d_boot0		d_un.un_b.un_d_boot0
#define d_boot1		d_un.un_b.un_d_boot1
I 9
#endif	/* ! KERNEL or STANDALONE */
I 28

E 28
E 9
E 8
E 2
			/* disk geometry: */
D 28
	u_long	d_secsize;		/* # of bytes per sector */
D 2
	u_long	d_nsectors;		/* # of sectors per track */
E 2
I 2
	u_long	d_nsectors;		/* # of data sectors per track */
E 2
	u_long	d_ntracks;		/* # of tracks per cylinder */
D 2
	u_long	d_ncylinders;		/* # of cylinders per unit */
E 2
I 2
	u_long	d_ncylinders;		/* # of data cylinders per unit */
	u_long	d_secpercyl;		/* # of data sectors per cylinder */
	u_long	d_secperunit;		/* # of data sectors per unit */
E 28
I 28
	u_int32_t d_secsize;		/* # of bytes per sector */
	u_int32_t d_nsectors;		/* # of data sectors per track */
	u_int32_t d_ntracks;		/* # of tracks per cylinder */
	u_int32_t d_ncylinders;		/* # of data cylinders per unit */
	u_int32_t d_secpercyl;		/* # of data sectors per cylinder */
	u_int32_t d_secperunit;		/* # of data sectors per unit */

E 28
	/*
D 28
	 * Spares (bad sector replacements) below
	 * are not counted in d_nsectors or d_secpercyl.
	 * Spare sectors are assumed to be physical sectors
	 * which occupy space at the end of each track and/or cylinder.
E 28
I 28
	 * Spares (bad sector replacements) below are not counted in
	 * d_nsectors or d_secpercyl.  Spare sectors are assumed to
	 * be physical sectors which occupy space at the end of each
	 * track and/or cylinder.
E 28
	 */
D 4
	u_long	d_sparespertrack;	/* # of spare sectors per track */
	u_long	d_sparespercyl;		/* # of spare sectors per cylinder */
E 4
I 4
D 28
	u_short	d_sparespertrack;	/* # of spare sectors per track */
	u_short	d_sparespercyl;		/* # of spare sectors per cylinder */
E 28
I 28
	u_int16_t d_sparespertrack;	/* # of spare sectors per track */
	u_int16_t d_sparespercyl;	/* # of spare sectors per cylinder */
E 28
E 4
	/*
D 28
	 * Alternate cylinders include maintenance, replacement,
	 * configuration description areas, etc.
E 28
I 28
	 * Alternate cylinders include maintenance, replacement, configuration
	 * description areas, etc.
E 28
	 */
E 2
D 28
	u_long	d_acylinders;		/* # of alt. cylinders per unit */
E 28
I 28
	u_int32_t d_acylinders;		/* # of alt. cylinders per unit */
E 28
D 2
	u_long	d_secpercyl;		/* # of sectors per cylinder */
	u_long	d_secperunit;		/* # of sectors per unit */
E 2
I 2

E 2
			/* hardware characteristics: */
D 4
	u_long	d_rpm;			/* rotational speed */
E 4
D 2
	u_short	d_interleave;		/* hardware sector interleave */
	u_short	d_sectorskew;		/* sector 0 skew, per track */
	u_short	d_headswitch;		/* head switch time, usec */
	u_short	d_trkseek;		/* track-to-track seek, usec */
E 2
I 2
	/*
	 * d_interleave, d_trackskew and d_cylskew describe perturbations
	 * in the media format used to compensate for a slow controller.
D 28
	 * Interleave is physical sector interleave, set up by the formatter
	 * or controller when formatting.  When interleaving is in use,
	 * logically adjacent sectors are not physically contiguous,
	 * but instead are separated by some number of sectors.
	 * It is specified as the ratio of physical sectors traversed
	 * per logical sector.  Thus an interleave of 1:1 implies contiguous
	 * layout, while 2:1 implies that logical sector 0 is separated
	 * by one sector from logical sector 1.
	 * d_trackskew is the offset of sector 0 on track N
	 * relative to sector 0 on track N-1 on the same cylinder.
	 * Finally, d_cylskew is the offset of sector 0 on cylinder N
	 * relative to sector 0 on cylinder N-1.
E 28
I 28
	 * Interleave is physical sector interleave, set up by the
	 * formatter or controller when formatting.  When interleaving is
	 * in use, logically adjacent sectors are not physically
	 * contiguous, but instead are separated by some number of
	 * sectors.  It is specified as the ratio of physical sectors
	 * traversed per logical sector.  Thus an interleave of 1:1
	 * implies contiguous layout, while 2:1 implies that logical
	 * sector 0 is separated by one sector from logical sector 1.
	 * d_trackskew is the offset of sector 0 on track N relative to
	 * sector 0 on track N-1 on the same cylinder.  Finally, d_cylskew
	 * is the offset of sector 0 on cylinder N relative to sector 0
	 * on cylinder N-1.
E 28
	 */
D 4
	u_long	d_interleave;		/* hardware sector interleave */
	u_long	d_trackskew;		/* sector 0 skew, per track */
	u_long	d_cylskew;		/* sector 0 skew, per cylinder */
E 4
I 4
D 28
	u_short	d_rpm;			/* rotational speed */
	u_short	d_interleave;		/* hardware sector interleave */
	u_short	d_trackskew;		/* sector 0 skew, per track */
	u_short	d_cylskew;		/* sector 0 skew, per cylinder */
E 4
	u_long	d_headswitch;		/* head switch time, usec */
	u_long	d_trkseek;		/* track-to-track seek, usec */
E 2
	u_long	d_flags;		/* generic flags */
E 28
I 28
	u_int16_t d_rpm;		/* rotational speed */
	u_int16_t d_interleave;		/* hardware sector interleave */
	u_int16_t d_trackskew;		/* sector 0 skew, per track */
	u_int16_t d_cylskew;		/* sector 0 skew, per cylinder */
	u_int32_t d_headswitch;		/* head switch time, usec */
	u_int32_t d_trkseek;		/* track-to-track seek, usec */
	u_int32_t d_flags;		/* generic flags */
E 28
D 2
#define NDDATA 10
E 2
I 2
#define NDDATA 5
E 2
D 28
	u_long	d_drivedata[NDDATA];	/* drive-type specific information */
E 28
I 28
	u_int32_t d_drivedata[NDDATA];	/* drive-type specific information */
E 28
D 2
			/* other identification: */
	char	d_typename[16];		/* type name, e.g. "eagle" */
	char	d_name[16];		/* pack identifier */
E 2
I 2
#define NSPARE 5
D 28
	u_long	d_spare[NSPARE];	/* reserved for future use */
E 2
	u_long	d_magic2;		/* the magic number (again) */
D 2
	u_short	d_checksum;		/* xor of data incl. partitions */
E 2
I 2
D 4
	u_long	d_checksum;		/* xor of data incl. partitions */
E 4
I 4
	u_short	d_checksum;		/* xor of data incl. partitions */
E 28
I 28
	u_int32_t d_spare[NSPARE];	/* reserved for future use */
	u_int32_t d_magic2;		/* the magic number (again) */
	u_int16_t d_checksum;		/* xor of data incl. partitions */
E 28
E 4

E 2
			/* filesystem and partition information: */
I 4
D 28
	u_short	d_npartitions;		/* number of partitions in following */
E 4
D 2
	u_short	d_npartitions;		/* number of partitions in following */
E 2
I 2
D 3
	u_long	d_npartitions;		/* number of partitions in following */
E 3
E 2
	u_long	d_bbsize;		/* size of boot area at sn0, bytes */
	u_long	d_sbsize;		/* max size of fs superblock, bytes */
E 28
I 28
	u_int16_t d_npartitions;	/* number of partitions in following */
	u_int32_t d_bbsize;		/* size of boot area at sn0, bytes */
	u_int32_t d_sbsize;		/* max size of fs superblock, bytes */
E 28
I 2
D 4
#define	d_swablast d_sbsize
I 3
	u_char	d_unused[3];		/* padding */
	u_char	d_npartitions;		/* number of partitions in following */
E 4
E 3
E 2
	struct	partition {		/* the partition table */
D 28
		u_long	p_size;		/* number of sectors in partition */
		u_long	p_offset;	/* starting sector */
		u_long	p_fsize;	/* filesystem basic fragment size */
		u_char	p_fstype;	/* filesystem type, see below */
		u_char	p_frag;		/* filesystem fragments per block */
E 28
I 28
		u_int32_t p_size;	/* number of sectors in partition */
		u_int32_t p_offset;	/* starting sector */
		u_int32_t p_fsize;	/* filesystem basic fragment size */
		u_int8_t p_fstype;	/* filesystem type, see below */
		u_int8_t p_frag;	/* filesystem fragments per block */
E 28
D 20
		u_short	p_cpg;		/* filesystem cylinders per group */
E 20
I 20
		union {
D 28
			u_short	cpg;	/* UFS: FS cylinders per group */
			u_short	sgs;	/* LFS: FS segment shift */
E 28
I 28
			u_int16_t cpg;	/* UFS: FS cylinders per group */
			u_int16_t sgs;	/* LFS: FS segment shift */
E 28
		} __partition_u1;
#define	p_cpg	__partition_u1.cpg
#define	p_sgs	__partition_u1.sgs
E 20
	} d_partitions[MAXPARTITIONS];	/* actually may be more */
};
I 2
D 26
#else LOCORE
E 26
I 26
#else /* LOCORE */
E 26
	/*
	 * offsets for asm boot files.
D 4
	 * Warning: all fields in big-endian byte order!
E 4
	 */
	.set	d_secsize,40
	.set	d_nsectors,44
	.set	d_ntracks,48
	.set	d_ncylinders,52
	.set	d_secpercyl,56
	.set	d_secperunit,60
D 4
	.set	d_end_,292		/* size of disk label */
E 4
I 4
	.set	d_end_,276		/* size of disk label */
E 4
E 2
D 26
#endif LOCORE
E 26
I 26
#endif /* LOCORE */
E 26
I 2

/* d_type values: */
#define	DTYPE_SMD		1		/* SMD, XSMD; VAX hp/up */
#define	DTYPE_MSCP		2		/* MSCP */
#define	DTYPE_DEC		3		/* other DEC (rk, rl) */
#define	DTYPE_SCSI		4		/* SCSI */
#define	DTYPE_ESDI		5		/* ESDI interface */
#define	DTYPE_ST506		6		/* ST506 etc. */
I 24
#define	DTYPE_HPIB		7		/* CS/80 on HP-IB */
#define	DTYPE_HPFL		8		/* HP Fiber-link */
E 24
#define	DTYPE_FLOPPY		10		/* floppy */

#ifdef DKTYPENAMES
static char *dktypenames[] = {
	"unknown",
	"SMD",
	"MSCP",
	"old DEC",
	"SCSI",
	"ESDI",
D 17
	"type 6",
E 17
I 17
	"ST506",
E 17
D 24
	"type 7",
	"type 8",
E 24
I 24
	"HP-IB",
	"HP-FL",
E 24
	"type 9",
	"floppy",
D 28
	0
E 28
I 28
	NULL
E 28
};
#define DKMAXTYPES	(sizeof(dktypenames) / sizeof(dktypenames[0]) - 1)
#endif
E 2

/*
 * Filesystem type and version.
 * Used to interpret other filesystem-specific
 * per-partition information.
 */
#define	FS_UNUSED	0		/* unused */
#define	FS_SWAP		1		/* swap */
#define	FS_V6		2		/* Sixth Edition */
#define	FS_V7		3		/* Seventh Edition */
#define	FS_SYSV		4		/* System V */
#define	FS_V71K		5		/* V7 with 1K blocks (4.1, 2.9) */
#define	FS_V8		6		/* Eighth Edition, 4K blocks */
#define	FS_BSDFFS	7		/* 4.2BSD fast file system */
I 17
#define	FS_MSDOS	8		/* MSDOS file system */
I 20
D 22
#define	FS_LFS		9		/* 4.4BSD log-structured file system */
E 22
I 22
#define	FS_BSDLFS	9		/* 4.4BSD log-structured file system */
I 23
#define	FS_OTHER	10		/* in use, but unknown/unsupported */
#define	FS_HPFS		11		/* OS/2 high-performance file system */
#define	FS_ISO9660	12		/* ISO 9660, normally CD-ROM */
I 25
#define	FS_BOOT		13		/* partition contains bootstrap */
E 25
E 23
E 22
E 20
E 17

#ifdef	DKTYPENAMES
static char *fstypenames[] = {
	"unused",
	"swap",
	"Version 6",
	"Version 7",
	"System V",
	"4.1BSD",
	"Eighth Edition",
	"4.2BSD",
I 17
	"MSDOS",
I 22
	"4.4LFS",
I 23
	"unknown",
	"HPFS",
	"ISO9660",
I 25
	"boot",
E 25
E 23
E 22
E 17
D 28
	0
E 28
I 28
	NULL
E 28
};
#define FSMAXTYPES	(sizeof(fstypenames) / sizeof(fstypenames[0]) - 1)
#endif

/*
 * flags shared by various drives:
 */
#define		D_REMOVABLE	0x01		/* removable media */
#define		D_ECC		0x02		/* supports ECC */
#define		D_BADSECT	0x04		/* supports bad sector forw. */
#define		D_RAMDISK	0x08		/* disk emulator */
#define		D_CHAIN		0x10		/* can do back-back transfers */

/*
 * Drive data for SMD.
 */
#define	d_smdflags	d_drivedata[0]
#define		D_SSE		0x1		/* supports skip sectoring */
#define	d_mindist	d_drivedata[1]
#define	d_maxdist	d_drivedata[2]
#define	d_sdist		d_drivedata[3]

/*
 * Drive data for ST506.
 */
#define d_precompcyl	d_drivedata[0]
#define d_gap3		d_drivedata[1]		/* used only when formatting */

I 12
/*
 * Drive data for SCSI.
 */
#define	d_blind		d_drivedata[0]

E 12
#ifndef LOCORE
/*
D 28
 * Structure used to perform a format
 * or other raw operation, returning data
 * and/or register values.
 * Register identification and format
E 28
I 28
 * Structure used to perform a format or other raw operation, returning
 * data and/or register values.  Register identification and format
E 28
 * are device- and driver-dependent.
 */
struct format_op {
	char	*df_buf;
D 28
	int	df_count;		/* value-result */
	daddr_t	df_startblk;
	int	df_reg[8];		/* result */
E 28
I 28
	int	 df_count;		/* value-result */
	daddr_t	 df_startblk;
	int	 df_reg[8];		/* result */
E 28
};

/*
I 5
D 28
 * Structure used internally to retrieve
 * information about a partition on a disk.
E 28
I 28
 * Structure used internally to retrieve information about a partition
 * on a disk.
E 28
 */
struct partinfo {
	struct disklabel *disklab;
	struct partition *part;
};

/*
E 5
 * Disk-specific ioctls.
 */
D 8
		/* get and set disklabel; last form used internally */
E 8
I 8
		/* get and set disklabel; DIOCGPART used internally */
E 8
D 7
#define DIOCGDINFO	_IOR(d, 101, struct disklabel)	/* get */
#define DIOCSDINFO	_IOW(d, 102, struct disklabel)	/* set */
#define DIOCWDINFO	_IOW(d, 103, struct disklabel)	/* set and write back */
D 5
#define DIOCGDINFOP	_IOW(d, 104, struct disklabel *) /* get pointer */
E 5
I 5
#define DIOCGPART	_IOW(d, 104, struct partinfo)	/* get partition */
E 7
I 7
#define DIOCGDINFO	_IOR('d', 101, struct disklabel)/* get */
#define DIOCSDINFO	_IOW('d', 102, struct disklabel)/* set */
D 8
#define DIOCWDINFO	_IOW('d', 103, struct disklabel)/* set and write back */
E 8
I 8
#define DIOCWDINFO	_IOW('d', 103, struct disklabel)/* set, update disk */
E 8
#define DIOCGPART	_IOW('d', 104, struct partinfo)	/* get partition */
E 7
E 5

/* do format operation, read or write */
D 7
#define DIOCRFORMAT	_IOWR(d, 105, struct format_op)
#define DIOCWFORMAT	_IOWR(d, 106, struct format_op)
E 7
I 7
#define DIOCRFORMAT	_IOWR('d', 105, struct format_op)
#define DIOCWFORMAT	_IOWR('d', 106, struct format_op)
E 7

D 7
#define DIOCSSTEP	_IOW(d, 107, int)	/* set step rate */
#define DIOCSRETRIES	_IOW(d, 108, int)	/* set # of retries */
E 7
I 7
#define DIOCSSTEP	_IOW('d', 107, int)	/* set step rate */
#define DIOCSRETRIES	_IOW('d', 108, int)	/* set # of retries */
I 8
#define DIOCWLABEL	_IOW('d', 109, int)	/* write en/disable label */
I 9

#define DIOCSBAD	_IOW('d', 110, struct dkbad)	/* set kernel dkbad */
E 9
E 8
E 7

D 26
#endif LOCORE
E 26
I 26
#endif /* LOCORE */
E 26

#if !defined(KERNEL) && !defined(LOCORE)
D 11
struct	disklabel *getdiskbyname();
E 11
I 11
D 13
#ifdef __STDC__
E 13
I 13
D 15
#if __STDC__ || c_plusplus
E 13
extern struct disklabel *getdiskbyname(const char *);
#else
extern struct disklabel *getdiskbyname();
#endif
E 15
I 15

#include <sys/cdefs.h>

__BEGIN_DECLS
struct disklabel *getdiskbyname __P((const char *));
__END_DECLS

E 15
E 11
#endif
E 1
