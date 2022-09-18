h08040
s 00002/00002/00127
d D 7.4 90/12/16 16:39:45 bostic 4 3
c kernel reorg
e
s 00002/00002/00127
d D 7.3 90/07/01 00:32:12 karels 3 2
c updates to use dinodes directly, etc
e
s 00002/00002/00127
d D 7.2 90/06/24 14:58:27 karels 2 1
c update includes
e
s 00129/00000/00000
d D 7.1 90/05/08 22:45:57 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Header file for standalone package
 */

D 2
#include "../h/types.h"
#include "../h/param.h"
E 2
I 2
D 3
#include "types.h"
#include "param.h"
E 3
I 3
#include <sys/param.h>
E 3
E 2
D 4
#include "../ufs/dinode.h"
#include "../ufs/fs.h"
E 4
I 4
#include "ufs/dinode.h"
#include "ufs/fs.h"
E 4

/*
 * Io block: includes a
 * dinode, cells for the use of seek, etc,
 * and a buffer.
 */
struct	iob {
	int	i_flgs;		/* see F_ below */
	struct	dinode i_ino;	/* dinode, if file */
	int	i_unit;		/* pseudo device unit */
	daddr_t	i_boff;		/* block offset on device */
	daddr_t	i_cyloff;	/* cylinder offset on device */
	off_t	i_offset;	/* seek offset in file */
I 3
	dev_t	i_dev;		/* associated device */
E 3
	daddr_t	i_bn;		/* 1st block # of next read */
	char	*i_ma;		/* memory address of i/o buffer */
	int	i_cc;		/* character count of transfer */
	int	i_error;	/* error # return */
	int	i_errcnt;	/* error count for driver retries */
	int	i_errblk;	/* block # in error for error reporting */
	char	i_buf[MAXBSIZE];/* i/o buffer */
	union {
		struct fs ui_fs;	/* file system super block info */
		char dummy[SBSIZE];
	} i_un;
};
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
	int	(*dv_strategy)();
	int	(*dv_open)();
	int	(*dv_close)();
	int	(*dv_ioctl)();
};

struct devsw devsw[];

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

/*
 * Request codes. Must be the same a F_XXX above
 */
#define	READ	1
#define	WRITE	2

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
