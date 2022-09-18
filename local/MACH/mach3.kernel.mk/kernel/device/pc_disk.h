/* 
 * Mach Operating System
 * Copyright (c) 1994-1989 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
/* 
 * HISTORY
 * $Log:	pc_disk.h,v $
 * Revision 2.2  94/12/15  15:21:35  dbg
 * 	Renamed device/pc_disk.h, since it is used by different device
 * 	drivers and since PCs are common.
 * 	[94/02/21            dbg]
 * 
 * Revision 2.11  93/08/10  15:57:47  mrt
 * 	Deal with bsd labels
 * 	[93/07/09            rvb]
 * 
 * Revision 2.10  93/03/11  13:57:56  danner
 * 	u_long -> u_int.
 * 	[93/03/09            danner]
 * 
 * Revision 2.9  91/10/07  17:25:18  af
 * 	From 2.5:
 * 	 	p_flag & p_tag -> p_flag
 * 	[91/09/09            rvb]
 * 
 * Revision 2.8  91/05/14  16:22:27  mrt
 * 	Correcting copyright
 * 
 * Revision 2.7  91/03/16  14:45:57  rpd
 * 	Fixed ioctl definitions for ANSI C.
 * 	[91/02/20            rpd]
 * 
 * Revision 2.6  91/02/05  17:16:54  mrt
 * 	Changed to new Mach copyright
 * 	[91/02/01  17:42:52  mrt]
 * 
 * Revision 2.5  91/01/08  17:32:46  rpd
 * 	Add V_ABS to log absolute address for 3.0 get/set stat version
 * 	of V_RDABS AND V_WRABS
 * 	[91/01/04  12:18:16  rvb]
 * 
 * Revision 2.4  90/11/26  14:49:32  rvb
 * 	jsb beat me to XMK34, sigh ...
 * 	[90/11/26            rvb]
 * 	Synched 2.5 & 3.0 at I386q (r2.2.1.9) & XMK35 (r2.4)
 * 	Minor syntax cleanup
 * 	[90/11/15            rvb]
 * 
 * Revision 2.2.1.8  90/09/18  08:38:34  rvb
 * 	Move setparams here and get IOC correct.
 * 	[90/09/08            rvb]
 * 
 * Revision 2.2.1.7  90/07/27  11:25:51  rvb
 * 	Fix Intel Copyright as per B. Davies authorization.
 * 	[90/07/27            rvb]
 * 
 * Revision 2.2  90/05/03  15:42:03  dbg
 * 	First checkin.
 * 
 * Revision 2.2.1.6  90/02/28  15:49:27  rvb
 * 	Make DISK_PART value conditional on OLD_PARTITIONS.
 * 	[90/02/28            rvb]
 * 
 * Revision 2.2.1.5  90/01/16  15:54:26  rvb
 * 	FLush pdinfo/vtoc -> evtoc
 * 	[90/01/16            rvb]
 * 
 * Revision 2.2.1.4  90/01/08  13:31:52  rvb
 * 	Add Intel copyright.
 * 	[90/01/08            rvb]
 * 
 * Revision 2.2.1.3  90/01/02  13:50:46  rvb
 * 	Add evtoc definition.
 * 
 * Revision 2.2.1.2  89/12/21  17:59:52  rvb
 * 	Changes from Eugene:
 * 		typedef of altinfo_t & partition_t
 * 	[89/12/07            rvb]
 * 
 * Revision 2.2.1.1  89/10/22  11:33:54  rvb
 * 	Add PART_DISK to indicate the "c" slice.
 * 	[89/10/21            rvb]
 * 
 * Revision 2.2  89/09/25  12:32:57  rvb
 * 	File was provided by Intel 9/18/89.
 * 	[89/09/23            rvb]
 * 
 */
 
/*
  Copyright 1988, 1989 by Intel Corporation, Santa Clara, California.

		All Rights Reserved

Permission to use, copy, modify, and distribute this software and
its documentation for any purpose and without fee is hereby
granted, provided that the above copyright notice appears in all
copies and that both the copyright notice and this permission notice
appear in supporting documentation, and that the name of Intel
not be used in advertising or publicity pertaining to distribution
of the software without specific, written prior permission.

INTEL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
IN NO EVENT SHALL INTEL BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#ifndef	_DEVICE_PC_DISK_H_
#define	_DEVICE_PC_DISK_H_

#include <sys/ioctl.h>

/*
 *	Definitions for PC-compatible disk structures:
 *	BIOS boot block
 *	BIOS partition table
 *
 *	Definitions for SYSV/386 disk layout, used for
 *	Mach on PC-compatibles with IDE disks.
 *
 *	Disk status operations used on PC compatibles
 *	running Mach.
 */

/*
 *	Sector size for PC-compatible disks
 */
#define	SECSIZE		512

/*
 *	BIOS boot block and partition table.
 */

#define BOOTSZ		446		/* size of boot code in
					   master boot block */
#define FD_NUMPART	4		/* number of partitions in BIOS
					   partition table */
#define ACTIVE		128		/* indicator of active partition */
#define	BOOT_MAGIC	0xAA55		/* signature of the boot record */
#define	UNIXOS		99		/* UNIX (SYSV386) partition */
#define BSDOS		165		/* BSD partition */

/*
 *	BIOS partition table entry
 */
struct ipart {
	unsigned char	bootid;		/* bootable or not */
	unsigned char	beghead;	/* beginning head, sector, cylinder */
	unsigned char	begsect;	/* begcyl is a 10-bit number. */
	unsigned char	begcyl;		/* High 2 bits are in begsect. */
	unsigned char	systid;		/* OS type */
	unsigned char	endhead;	/* ending head, sector, cylinder */
	unsigned char	endsect;	/* endcyl is a 10-bit number. */
	unsigned char	endcyl;		/* High 2 bits are in endsect. */
	unsigned int	relsect;	/* first sector relative to start
					   of disk */
	unsigned int	numsect;	/* number of sectors in partition */
};

/*
 * Structure to hold master boot block in physical sector 0 of the disk.
 * Note that partition structure can't be directly included, because
 * it is on an odd halfword, but the compiler will align it on a
 * longword boundary.
 */
struct mboot {				     /* master boot block */
	unsigned char	bootinst[BOOTSZ];
	unsigned char	parts[FD_NUMPART * sizeof(struct ipart)];
	unsigned short	signature;
};


/*
 *	Sectors 0..28 of the UX BIOS partition are for the
 *	boot code.  The EVTOC at sector 29 describes the
 *	UX partitions within the BIOS partition.
 */


/* Sanity word for the physical description area */
#define VALID_PD	0xCA5E600D

#define V_NUMPAR        16              /* maximum number of partitions */

#define VTOC_SANE       0x600DDEEE      /* Indicates a sane VTOC */

#define	HDPDLOC		29		/* location of pdinfo/vtoc */
#define	LBLLOC		1		/* label block for xxxbsd */

/*
 *	One partition
 */
struct localpartition	{
	unsigned int	p_flag;		/* permission flags */
	unsigned int	p_start;	/* physical starting sector */
	int		p_size;		/* number of physical sectors */
};
typedef struct localpartition localpartition_t;

/*
 *	Volume Table of Contents (vtoc)
 */
struct evtoc {
	unsigned int	fill0[6];
	unsigned int	cyls;		/* cylinders per drive */
	unsigned int	tracks;		/* tracks per cylinder */
	unsigned int	sectors;	/* sectors per track */
	unsigned int	fill1[13];
	unsigned int	version;	/* layout version */
	unsigned int	alt_ptr;	/* byte offset of alternates table */
	unsigned short	alt_len;	/* byte length of alternates table */
	unsigned short	fill1a;
	unsigned int	sanity;		/* to verify vtoc sanity */
	unsigned int	xcyls;		/* cylinders per drive */
	unsigned int	xtracks;	/* tracks per cylinder */
	unsigned int	xsectors;	/* sectors per track */
	unsigned short	nparts;		/* number of partitions */
	unsigned short	fill2;
	char		label[40];
	struct localpartition
			part[V_NUMPAR];	/* partition headers */
	char		fill[512-352];
};

/*
 *	Table for alternate tracks and sectors
 */

#define MAX_ALTENTS     253		/* Maximum # of slots for alts */
					/* allowed for in the table. */

#define ALT_SANITY      0xdeadbeef      /* magic # to validate alt table */

struct  alt_table {
	unsigned short	alt_used;	/* # of alternates already assigned */
	unsigned short	alt_reserved;	/* # of alternates reserved on disk */
	long	alt_base;		/* 1st sector (abs) of the alt area */
	long	alt_bad[MAX_ALTENTS];	/* list of bad sectors/tracks	*/
};

struct alt_info {			/* table length should be
					   multiple of 512 */
	long		alt_sanity;	/* to validate correctness */
	unsigned short	alt_version;	/* to corroborate vintage */
	unsigned short	alt_pad;	/* padding for alignment */
	struct alt_table alt_trk;	/* bad track table */
	struct alt_table alt_sec;	/* bad sector table */
};
typedef struct alt_info altinfo_t;

/*
 *	Status operations for manipulating the disk information
 *	structures and for bypassing the partition tables
 *	(absolute IO)
 */
#define PART_DISK	2		/* partition number for entire disk */

/* Partition permission flags */
#define V_OPEN          0x100           /* Partition open (for driver use) */
#define V_VALID         0x200           /* Partition is valid to use */

/* driver ioctl() commands */
#define V_CONFIG        _IOW('v',1,union io_arg)
					/* Configure Drive */
#define V_REMOUNT       _IO('v',2)    	/* Remount Drive */
#define V_ADDBAD        _IOW('v',3,union io_arg)
					/* Add Bad Sector */
#define V_GETPARMS      _IOR('v',4,struct disk_parms)
					/* Get drive/partition parameters */
#define V_FORMAT        _IOW('v',5,union io_arg)
					/* Format track(s) */
#define V_PDLOC		_IOR('v',6,int)	/* Ask driver where pdinfo is on disk */

#define V_ABS		_IOW('v',9,int)	/* set a sector for an absolute addr */
#define V_RDABS		_IOW('v',10,struct absio)
					/* Read a sector at an absolute addr */
#define V_WRABS		_IOW('v',11,struct absio)
					/* Write a sector to absolute addr */
#define V_VERIFY	_IOWR('v',12,union vfy_io)
					/* Read verify sector(s) */
#define V_XFORMAT	_IO('v',13)	/* Selectively mark sectors as bad */
#define V_SETPARMS	_IOW('v',14,int)/* Set drivers parameters */

union io_arg {
	struct {
	    unsigned short  ncyl;	/* number of cylinders on drive */
	    unsigned char   nhead;	/* number of heads/cyl */
	    unsigned char   nsec;	/* number of sectors/track */
	    unsigned short  secsiz;	/* number of bytes/sector */
	} ia_cd;			/* used for Configure Drive cmd */
	struct {
	    unsigned short  flags;	/* flags (see below) */
	    long	    bad_sector;	/* absolute sector number */
	    long	    new_sector;	/* RETURNED alternate sect assigned */
	} ia_abs;			/* used for Add Bad Sector cmd */
	struct {
	    unsigned short  start_trk;	/* first track # */
	    unsigned short  num_trks;	/* number of tracks to format */
	    unsigned short  intlv;	/* interleave factor */
	} ia_fmt;			/* used for Format Tracks cmd */
	struct {
	    unsigned short  start_trk;	/* first track */
	    char	   *intlv_tbl;	/* interleave table */
	} ia_xfmt;			/* used for the V_XFORMAT ioctl */
};

/*
 * Data structure for the V_VERIFY ioctl
 */
union vfy_io {
	struct {
	    long	    abs_sec;	/* absolute sector number        */
	    unsigned short  num_sec;	/* number of sectors to verify   */
	    unsigned short  time_flg;	/* flag to indicate time the ops */
	} vfy_in;
	struct {
	    long	    deltatime;	/* duration of operation */
	    unsigned short  err_code;	/* reason for failure    */
	} vfy_out;
};

#define	BAD_BLK		0x80		/* bad block from verify */

/*
 * Data structure for the V_RDABS/V_WRABS ioctls
 */
struct absio {
	long	abs_sec;		/* Absolute sector number (from 0) */
	char	*abs_buf;		/* Sector buffer */
};


/* data structure returned by the Get Parameters ioctl: */
struct disk_parms {
/*00*/	char		dp_type;	/* Disk type (see below) */
	unsigned char	dp_heads;	/* Number of heads */
	unsigned short	dp_cyls;	/* Number of cylinders */
/*04*/	unsigned char	dp_sectors;	/* Number of sectors/track */
	unsigned short	dp_secsiz;	/* Number of bytes/sector */
					/* for this partition: */
/*08*/	unsigned short	dp_ptag;	/* Partition tag */
	unsigned short	dp_pflag;	/* Partition flag */
/*0c*/	long		dp_pstartsec;	/* Starting absolute sector number */
/*10*/	long		dp_pnumsec;	/* Number of sectors */
/*14*/	unsigned char	dp_dosheads;	/* Number of heads */
	unsigned short	dp_doscyls;	/* Number of cylinders */
/*18*/	unsigned char	dp_dossectors;	/* Number of sectors/track */
};

/* Disk types for disk_parms.dp_type: */
#define DPT_NOTDISK     0               /* Not a disk device */
#define DPT_WINI        1               /* Winchester disk */
#define DPT_FLOPPY      2               /* Floppy */
#define DPT_OTHER       3               /* Other type of disk */


#endif	/* _DEVICE_PC_DISK_H_ */
