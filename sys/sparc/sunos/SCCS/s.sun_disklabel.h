h16857
s 00002/00002/00085
d D 8.1 93/06/11 15:19:32 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00086
d D 7.3 93/04/06 19:40:20 torek 3 2
c spelling
e
s 00005/00000/00082
d D 7.2 92/07/21 16:55:42 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00082/00000/00000
d D 7.1 92/07/13 00:40:45 torek 1 0
c date and time created 92/07/13 00:40:45 by torek
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 3
 *	California, Lawrence Berkeley Laboratories.
E 3
I 3
 *	California, Lawrence Berkeley Laboratory.
E 3
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * from: $Header: sun_disklabel.h,v 1.4 92/06/17 07:04:13 torek Exp $
 */

/*
 * SunOS disk label layout (only relevant portions discovered here).
 */

#define	SUN_DKMAGIC	55998

/* These are the guys that Sun's dkinfo needs... */
#define DKIOCGGEOM	_IOR('d', 2, struct sun_dkgeom)	/* geometry info */
#define DKIOCINFO	_IOR('d', 8, struct sun_dkctlr)	/* controller info */
#define DKIOCGPART	_IOR('d', 4, struct sun_dkpart)	/* partition info */

/* geometry info */
struct sun_dkgeom {
	u_short	sdkc_ncylinders;	/* data cylinders */
	u_short	sdkc_acylinders;	/* alternate cylinders */
	u_short	sdkc_xxx1;
	u_short	sdkc_ntracks;		/* tracks per cylinder */
	u_short	sdkc_xxx2;
	u_short	sdkc_nsectors;		/* sectors per track */
	u_short	sdkc_interleave;	/* interleave factor */
	u_short	sdkc_xxx3;
	u_short	sdkc_xxx4;
	u_short	sdkc_sparespercyl;	/* spare sectors per cylinder */
	u_short	sdkc_rpm;		/* rotational speed */
	u_short	sdkc_pcylinders;	/* physical cylinders */
	u_short	sdkc_xxx5[7];
};

/* controller info */
struct sun_dkctlr {
	int	sdkc_addr;		/* controller address */
	short	sdkc_unit;		/* unit (slave) address */
	short	sdkc_type;		/* controller type */
	short	sdkc_flags;		/* flags */
};

/* partition info */
struct sun_dkpart {
	long	sdkp_cyloffset;		/* starting cylinder */
	long	sdkp_nsectors;		/* number of sectors */
};

struct sun_disklabel {			/* total size = 512 bytes */
	char	sl_text[128];
	char	sl_xxx1[292];
	u_short sl_rpm;			/* rotational speed */
	char	sl_xxx2[2];
	u_short sl_sparespercyl;	/* spare sectors per cylinder */
	char	sl_xxx3[4];
	u_short sl_interleave;		/* interleave factor */
	u_short	sl_ncylinders;		/* data cylinders */
	u_short	sl_acylinders;		/* alternate cylinders */
	u_short	sl_ntracks;		/* tracks per cylinder */
	u_short	sl_nsectors;		/* sectors per track */
	char	sl_xxx4[4];
	struct sun_dkpart sl_part[8];	/* partition layout */
	u_short	sl_magic;		/* == SUN_DKMAGIC */
	u_short	sl_cksum;		/* xor checksum of all shorts */
};

#ifdef KERNEL
/* reads sun label in sector at [cp..cp+511] and sets *lp to BSD label */
int	sun_disklabel __P((caddr_t, struct disklabel *)); /* true on success */

/* compatability dk ioctl's */
int	sun_dkioctl __P((struct dkdevice *, int, caddr_t, int));
#endif
E 1
