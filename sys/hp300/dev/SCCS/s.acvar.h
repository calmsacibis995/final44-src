h13249
s 00002/00002/00057
d D 8.1 93/06/10 21:31:47 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00059/00000/00000
d D 7.1 92/06/05 15:33:07 hibler 1 0
c merge latest Utah hp300 code including 68040 support
e
u
U
t
T
I 1
/*
 * Copyright (c) 1991 University of Utah.
D 2
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: acvar.h 1.1 91/06/19$
 *
 *	%W% (Berkeley) %G%
 */

struct	ac_softc {
	struct	hp_device *sc_hd;
	int	sc_flags;
	struct	buf *sc_bp;
	struct	scsi_fmt_cdb *sc_cmd;
	struct	acinfo sc_einfo;
	short	sc_punit;
	short	sc_picker;
	struct	devqueue sc_dq;
};

#define	ACF_ALIVE	0x01
#define ACF_OPEN	0x02
#define ACF_ACTIVE	0x04

#define ACCMD_INITES	0x07
#define	ACCMD_MODESENSE	0x1A
#define ACCMD_READES	0xB8
#define ACCMD_MOVEM	0xA5

struct	ac_restathdr {
	short	ac_felt;	/* first element reported */
	short	ac_nelt;	/* number of elements reported */
	long	ac_bcount;	/* length of report (really only 24 bits) */
};

struct	ac_restatphdr {
	char	ac_type;	/* type code */
	char	ac_res;
	short	ac_dlen;	/* element descriptor length */
	long	ac_bcount;	/* byte count (really only 24 bits) */
};

struct	ac_restatdb {
	short	ac_eaddr;	/* element address */
	u_int	ac_res1:2,
		ac_ie:1,	/* import enabled (IEE only) */
		ac_ee:1,	/* export enabled (IEE only) */
		ac_acc:1,	/* accessible from MTE */
		ac_exc:1,	/* element in abnormal state */
		ac_imp:1,	/* 1 == user inserted medium (IEE only) */
		ac_full:1;	/* element contains media */
};
E 1
