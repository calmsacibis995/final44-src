h32883
s 00001/00001/00085
d D 8.2 95/01/09 18:16:09 cgd 4 3
c 64-bit changes: ioctl cmd -> u_long, some protos.  some style, return vals.
e
s 00002/00002/00084
d D 8.1 93/06/02 19:53:04 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00003/00078
d D 5.2 92/11/18 20:34:38 torek 2 1
c dk_wpms => dk_bps; minor copyright fix
e
s 00081/00000/00000
d D 5.1 92/07/10 00:14:44 torek 1 0
c date and time created 92/07/10 00:14:44 by torek
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Lawrence Berkeley Laboratory.
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 2
 * from: $Header: disk.h,v 1.1 92/07/10 07:13:43 torek Exp $ (LBL)
E 2
I 2
 * from: $Header: disk.h,v 1.5 92/11/19 04:33:03 torek Exp $ (LBL)
E 2
 */

/*
 * Disk device structures.
 *
 * Note that this is only a preliminary outline.  The final disk structures
 * may be somewhat different.
 */
struct buf;

struct dkdevice {
	struct	device dk_dev;		/* base device */
	struct	dkdevice *dk_next;	/* list of disks; not yet used */
D 2
	int	dk_wpms;		/* xfer rate */
E 2
I 2
	int	dk_bps;			/* xfer rate: bytes per second */
E 2
	int	dk_bopenmask;		/* block devices open */
	int	dk_copenmask;		/* character devices open */
	int	dk_openmask;		/* composite (bopen|copen) */
	int	dk_state;		/* label state   ### */
	int	dk_blkshift;		/* shift to convert DEV_BSIZE to blks */
	int	dk_byteshift;		/* shift to convert bytes to blks */
	struct	dkdriver *dk_driver;	/* pointer to driver */
	daddr_t	dk_labelsector;		/* sector containing label */
	struct	disklabel dk_label;	/* label */
};

struct dkdriver {
	void	(*d_strategy) __P((struct buf *));
#ifdef notyet
	int	(*d_open) __P((dev_t dev, int ifmt, int, struct proc *));
	int	(*d_close) __P((dev_t dev, int, int ifmt, struct proc *));
D 4
	int	(*d_ioctl) __P((dev_t dev, int cmd, caddr_t data, int fflag,
E 4
I 4
	int	(*d_ioctl) __P((dev_t dev, u_long cmd, caddr_t data, int fflag,
E 4
				struct proc *));
	int	(*d_dump) __P((dev_t));
D 2
#endif
E 2
	void	(*d_start) __P((struct buf *, daddr_t));
	int	(*d_mklabel) __P((struct dkdevice *));
I 2
#endif
E 2
};

/* states */
#define	DK_CLOSED	0		/* drive is closed */
#define	DK_WANTOPEN	1		/* drive being opened */
#define	DK_WANTOPENRAW	2		/* drive being opened */
#define	DK_RDLABEL	3		/* label being read */
#define	DK_OPEN		4		/* label read, drive open */
#define	DK_OPENRAW	5		/* open without label */

#ifdef DISKSORT_STATS
/*
 * Stats from disksort().
 */
struct disksort_stats {
	long	ds_newhead;		/* # new queue heads created */
	long	ds_newtail;		/* # new queue tails created */
	long	ds_midfirst;		/* # insertions into sort list */
	long	ds_endfirst;		/* # insertions at end of sort list */
	long	ds_newsecond;		/* # inversions (2nd lists) created */
	long	ds_midsecond;		/* # insertions into 2nd list */
	long	ds_endsecond;		/* # insertions at end of 2nd list */
};
#endif

#ifdef KERNEL
void	disksort __P((struct buf *, struct buf *));
char	*readdisklabel __P((struct dkdevice *, int));
int	setdisklabel __P((struct dkdevice *, struct disklabel *));
int	writedisklabel __P((struct dkdevice *, int));
int	diskerr __P((struct dkdevice *, struct buf *, char *, int, int));
#endif
E 1
