h14461
s 00006/00005/00123
d D 7.5 92/10/11 11:28:18 bostic 5 4
c make kernel includes standard
e
s 00001/00000/00127
d D 7.4 92/09/13 11:51:45 ralph 4 3
c fix undefined time_t
e
s 00002/00001/00125
d D 7.3 92/03/07 10:01:21 ralph 3 2
c fixes for ds5000
e
s 00003/00003/00123
d D 7.2 92/02/29 15:16:20 ralph 2 1
c changes for ufs include files
e
s 00126/00000/00000
d D 7.1 92/01/07 20:45:20 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Header file for standalone package
 */

/*
 * Fake vnode structure to keep compiler happy
 */
struct vnode {
	int fake;
};

D 3
#include "param.h"
E 3
I 3
D 5
#include "sys/param.h"
I 4
#include "sys/time.h"
E 4
E 3
D 2
#include "ufs/quota.h"
#include "ufs/inode.h"
#include "ufs/fs.h"
E 2
I 2
#include "ufs/ufs/quota.h"
#include "ufs/ufs/inode.h"
#include "ufs/ffs/fs.h"
E 5
I 5
#include <sys/param.h>
#include <sys/time.h>

#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
#include <ufs/ffs/fs.h>
E 5
E 2

/*
 * Io block: includes an
 * inode, cells for the use of seek, etc,
 * and a buffer.
 */
struct	iob {
	int	i_flgs;		/* see F_ below */
	struct	inode i_ino;	/* inode, if file */
	int	i_dev;		/* index into devsw[] */
	int	i_unit;		/* (used by drvr only) */
	daddr_t	i_boff;		/* block offset on device */
	off_t	i_offset;	/* seek offset in file */
	daddr_t	i_bn;		/* 1st block # of next read */
	char	*i_ma;		/* memory address of i/o buffer */
	int	i_cc;		/* character count of transfer */
	int	i_error;	/* error # return */
	char	i_buf[MAXBSIZE];/* i/o buffer */
	union {
		struct fs ui_fs;	/* file system super block info */
		char dummy[SBSIZE];
	} i_un;
};
I 3
#undef i_fs
E 3
#define i_fs i_un.ui_fs
#define NULL 0

#define F_READ		0x1	/* file opened for reading */
#define F_WRITE		0x2	/* file opened for writing */
#define F_ALLOC		0x4	/* buffer allocated */
#define F_FILE		0x8	/* file instead of device */
#define F_NBSF		0x10	/* no bad sector forwarding */
#define F_SSI		0x40	/* set skip sector inhibit */
/* io types */
#define	F_RDDATA	0x0100	/* read data */
#define	F_WRDATA	0x0200	/* write data */
#define F_HDR		0x0400	/* include header on next i/o */
#define F_CHECK		0x0800	/* perform check of data read/write */
#define F_HCHECK	0x1000	/* perform check of header and data */

#define	F_TYPEMASK	0xff00

/*
 * Device switch.
 */
struct devsw {
	char	*dv_name;
};

extern struct devsw devsw[];

/*
 * Drive description table.
 * Returned from SAIODEVDATA call.
 */
struct st {
	short	nsect;		/* # sectors/track */
	short	ntrak;		/* # tracks/surfaces/heads */
	short	nspc;		/* # sectors/cylinder */
	short	ncyl;		/* # cylinders */
	short	*off;		/* partition offset table (cylinders) */
};

#define	NBUFS	4
char	b[NBUFS][MAXBSIZE];
daddr_t	blknos[NBUFS];

#define	NFILES	4
struct	iob iob[NFILES];

extern	int errno;	/* just like unix */

/* error codes */
#define	EBADF	1	/* bad file descriptor */
#define	EOFFSET	2	/* relative seek not supported */
#define	EDEV	3	/* improper device specification on open */
#define	ENXIO	4	/* unknown device specified */
#define	EUNIT	5	/* improper unit specification */
#define	ESRCH	6	/* directory search for file failed */
#define	EIO	7	/* generic error */
#define	ECMD	10	/* undefined driver command */
#define	EBSE	11	/* bad sector error */
#define	EWCK	12	/* write check error */
#define	EECC	13	/* uncorrectable ecc error */
#define	EHER	14	/* hard error */

/* ioctl's -- for disks just now */
#define	SAIOHDR		(('d'<<8)|1)	/* next i/o includes header */
#define	SAIOCHECK	(('d'<<8)|2)	/* next i/o checks data */
#define	SAIOHCHECK	(('d'<<8)|3)	/* next i/o checks header & data */
#define	SAIONOBAD	(('d'<<8)|4)	/* inhibit bad sector forwarding */
#define	SAIODOBAD	(('d'<<8)|5)	/* enable bad sector forwarding */
#define	SAIOECCLIM	(('d'<<8)|6)	/* set limit to ecc correction, bits */
#define	SAIORETRIES	(('d'<<8)|7)	/* set retry count for unit */
#define	SAIODEVDATA	(('d'<<8)|8)	/* get device data */
#define	SAIOSSI		(('d'<<8)|9)	/* set skip sector inhibit */
#define	SAIONOSSI	(('d'<<8)|10)	/* inhibit skip sector handling */
#define	SAIOSSDEV	(('d'<<8)|11)	/* is device skip sector type? */
#define	SAIODEBUG	(('d'<<8)|12)	/* enable/disable debugging */
#define	SAIOGBADINFO	(('d'<<8)|13)	/* get bad-sector table */
E 1
