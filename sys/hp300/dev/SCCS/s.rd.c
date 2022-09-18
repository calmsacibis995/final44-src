h09883
s 00001/00004/01077
d D 8.5 95/05/14 00:51:38 mckusick 24 23
c just use <vm/vm.h> for VM include files
e
s 00001/00001/01080
d D 8.4 95/05/10 10:31:28 root 23 22
c lock.h moves to /sys/sys
e
s 00001/00001/01080
d D 8.3 95/01/09 18:28:58 cgd 22 21
c ioctl cmd arg is u_long, strategy returns void.
e
s 00003/00000/01078
d D 8.2 94/05/19 21:40:37 hibler 21 20
c if no label, reset partition info since readdisklabel changes it
e
s 00002/00002/01076
d D 8.1 93/06/10 21:33:57 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/01077
d D 7.19 93/02/18 20:46:49 hibler 19 18
c default ncylinders to 1 for disklabel
e
s 00297/00367/00780
d D 7.18 92/12/27 09:32:33 hibler 18 17
c disklabel support
e
s 00013/00013/01134
d D 7.17 92/10/11 09:24:07 bostic 17 16
c make kernel includes standard
e
s 00000/00011/01147
d D 7.16 92/08/03 13:46:31 hibler 16 15
c make the UTAH partition table for the 7937 standard
c (this gets rid of the last remaining UTAH ifdef)
e
s 00005/00004/01153
d D 7.15 92/07/07 19:02:36 torek 15 14
c lint
e
s 00001/00001/01156
d D 7.14 92/06/05 15:31:51 hibler 14 13
c merge latest Utah hp300 code including 68040 support
e
s 00001/00001/01156
d D 7.13 92/02/19 21:03:05 mckusick 13 12
c pmap_kernel() becomes kernel_pmap
e
s 00002/00001/01155
d D 7.12 91/11/05 17:03:07 mckusick 12 11
c lint
e
s 00001/00001/01155
d D 7.11 91/09/12 16:38:54 marc 11 10
c need vm_prot.h before pmap.h
e
s 00000/00001/01156
d D 7.10 91/08/28 15:48:44 mckusick 10 9
c no longer need vm_statistics.h
e
s 00018/00010/01139
d D 7.9 91/05/07 09:48:12 hibler 9 8
c get rid of rdbuf, new proc param to many routines
e
s 00001/00001/01148
d D 7.8 91/05/04 19:50:35 karels 8 7
c don't lose bits from unit number
e
s 00002/00000/01147
d D 7.7 91/05/04 19:49:25 karels 7 6
c update to current include, device calling conventions
e
s 00028/00001/01119
d D 7.6 91/02/25 22:41:03 mckusick 6 5
c update from Hibler for additional HP disks
e
s 00010/00010/01110
d D 7.5 90/12/16 16:36:56 bostic 5 4
c kernel reorg
e
s 00027/00020/01093
d D 7.4 90/12/05 18:26:37 mckusick 4 3
c update from Mike Hibler for new VM and other machine support
e
s 00039/00017/01074
d D 7.3 90/05/25 15:45:07 mckusick 3 2
c "update from Mike Hibler at Utah"
e
s 00001/00001/01090
d D 7.2 90/05/15 22:04:39 mckusick 2 1
c use proper include files
e
s 01091/00000/00000
d D 7.1 90/05/08 22:07:06 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 20
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 6
 * from: Utah $Hdr: rd.c 1.30 89/09/17$
E 6
I 6
D 9
 * from: Utah $Hdr: rd.c 1.3 90/10/12$
E 9
I 9
D 18
 * from: Utah $Hdr: rd.c 1.38 90/10/12$
E 18
I 18
 * from: Utah $Hdr: rd.c 1.44 92/12/26$
E 18
E 9
E 6
 *
 *	%W% (Berkeley) %G%
 */

/*
 * CS80/SS80 disk driver
 */
#include "rd.h"
#if NRD > 0

D 5
#include "param.h"
#include "systm.h"
#include "errno.h"
#include "dkstat.h"
#include "disklabel.h"
#include "buf.h"
#include "uio.h"
E 5
I 5
D 17
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/errno.h"
#include "sys/dkstat.h"
#include "sys/disklabel.h"
#include "sys/buf.h"
#include "sys/uio.h"
E 17
I 17
#include <sys/param.h>
#include <sys/systm.h>
D 18
#include <sys/errno.h>
E 18
I 18
#include <sys/buf.h>
#include <sys/stat.h>
E 18
#include <sys/dkstat.h>
#include <sys/disklabel.h>
D 18
#include <sys/buf.h>
#include <sys/uio.h>
E 18
I 18
#include <sys/ioctl.h>
#include <sys/fcntl.h>
E 18
E 17
E 5

D 14
#include "device.h"
E 14
I 14
D 17
#include "hp/dev/device.h"
E 14
#include "rdreg.h"
E 17
I 17
#include <hp/dev/device.h>
#include <hp300/dev/rdreg.h>
I 18
#include <hp300/dev/rdvar.h>
#ifdef USELEDS
#include <hp300/hp300/led.h>
#endif
E 18
E 17

I 4
D 5
#include "../vm/vm_param.h"
#include "../vm/pmap.h"
#include "../vm/vm_prot.h"
E 5
I 5
D 17
#include "vm/vm_param.h"
I 7
#include "vm/lock.h"
D 10
#include "vm/vm_statistics.h"
E 10
E 7
D 11
#include "vm/pmap.h"
E 11
#include "vm/vm_prot.h"
I 11
#include "vm/pmap.h"
E 17
I 17
D 24
#include <vm/vm_param.h>
D 23
#include <vm/lock.h>
E 23
I 23
#include <sys/lock.h>
E 23
#include <vm/vm_prot.h>
#include <vm/pmap.h>
E 24
I 24
#include <vm/vm.h>
E 24
E 17
E 11
E 5

E 4
int	rdinit(), rdstart(), rdgo(), rdintr();
I 18
void	rdstrategy();
E 18
struct	driver rddriver = {
	rdinit, "rd", rdstart, rdgo, rdintr,
};

D 18
struct	rd_softc {
	struct	hp_device *sc_hd;
I 3
	int	sc_flags;
	short	sc_type;
	short	sc_punit;
	char	*sc_addr;
	int	sc_resid;
	u_int	sc_wpms;
	struct	rdinfo *sc_info;
	struct	devqueue sc_dq;
E 3
	struct	rd_iocmd sc_ioc;
	struct	rd_rscmd sc_rsc;
	struct	rd_stat sc_stat;
	struct	rd_ssmcmd sc_ssmc;
	struct	rd_srcmd sc_src;
	struct	rd_clearcmd sc_clear;
D 3
	int	sc_resid;
	char	*sc_addr;
	struct	rdinfo *sc_info;
	int	sc_flags;
	short	sc_type;
	short	sc_punit;
	struct	devqueue sc_dq;
E 3
} rd_softc[NRD];
E 18
I 18
struct	rd_softc rd_softc[NRD];
struct	buf rdtab[NRD];
int	rderrthresh = RDRETRY-1;	/* when to start reporting errors */
E 18

D 18
/* sc_flags values */
#define	RDF_ALIVE	0x1
#define	RDF_SEEK	0x2
#define RDF_SWAIT	0x4

struct	size {
	daddr_t	nblocks;
	int	cyloff;
};

E 18
#ifdef DEBUG
D 18
int rddebug = 0x80;
#define RDB_FOLLOW	0x01
#define RDB_STATUS	0x02
#define RDB_IDENT	0x04
#define RDB_IO		0x08
#define RDB_ASYNC	0x10
#define RDB_ERROR	0x80
#define RDB_DUMP	0x80000000

struct rdstats {
	long	rdretries;
	long	rdresets;
	long	rdtimeouts;
	long	rdpolltries;
	long	rdpollwaits;
} rdstats[NRD];

E 18
/* error message tables */
char *err_reject[] = {
	0, 0,
	"channel parity error",		/* 0x2000 */
	0, 0,
	"illegal opcode",		/* 0x0400 */
	"module addressing",		/* 0x0200 */
	"address bounds",		/* 0x0100 */
	"parameter bounds",		/* 0x0080 */
	"illegal parameter",		/* 0x0040 */
	"message sequence",		/* 0x0020 */
	0,
	"message length",		/* 0x0008 */
	0, 0, 0
};

char *err_fault[] = {
	0,
	"cross unit",			/* 0x4000 */
	0,
	"controller fault",		/* 0x1000 */
	0, 0,
	"unit fault",			/* 0x0200 */
	0,
	"diagnostic result",		/* 0x0080 */
	0,
	"operator release request",	/* 0x0020 */
	"diagnostic release request",	/* 0x0010 */
	"internal maintenance release request",	/* 0x0008 */
	0,
	"power fail",			/* 0x0002 */
	"retransmit"			/* 0x0001 */
};

char *err_access[] = {
	"illegal parallel operation",	/* 0x8000 */
	"uninitialized media",		/* 0x4000 */
	"no spares available",		/* 0x2000 */
	"not ready",			/* 0x1000 */
	"write protect",		/* 0x0800 */
	"no data found",		/* 0x0400 */
	0, 0,
	"unrecoverable data overflow",	/* 0x0080 */
	"unrecoverable data",		/* 0x0040 */
	0,
	"end of file",			/* 0x0010 */
	"end of volume",		/* 0x0008 */
	0, 0, 0
};

char *err_info[] = {
	"operator release request",	/* 0x8000 */
	"diagnostic release request",	/* 0x4000 */
	"internal maintenance release request",	/* 0x2000 */
	"media wear",			/* 0x1000 */
	"latency induced",		/* 0x0800 */
	0, 0,
	"auto sparing invoked",		/* 0x0100 */
	0,
	"recoverable data overflow",	/* 0x0040 */
	"marginal data",		/* 0x0020 */
	"recoverable data",		/* 0x0010 */
	0,
	"maintenance track overflow",	/* 0x0004 */
	0, 0
};
I 18

struct	rdstats rdstats[NRD];
int	rddebug = 0x80;
#define RDB_FOLLOW	0x01
#define RDB_STATUS	0x02
#define RDB_IDENT	0x04
#define RDB_IO		0x08
#define RDB_ASYNC	0x10
#define RDB_ERROR	0x80
E 18
#endif

/*
D 18
 * CS/80 partitions.  We reserve the first cylinder for a LIF
 * style boot directory (the 8k allowed in the BSD filesystem
 * is just way too small).  This boot area is outside of all but
 * the C partition.  This implies that you cannot use the C 
 * partition on a bootable disk since the filesystem would overlay
 * the boot area.  You must use the A partition.
 *
 * These maps support four basic layouts:
 *
 *	A/B/G:   This is the "traditional" setup for a bootable disk.
 *	         A is the root partition, B the swap, and G a user partition.
 *	A/D/H:   This is a setup for bootable systems requiring more swap
 *		 (e.g. those who use HPCL).  It has A as the root, D as a
 *		 larger swap, and H as a smaller user partition.
 *	A/D/E/F: Similar to A/D/H with E and F breaking H into two partitions.
 *		 E could be used for /usr and F for users.
 *	C:       This gives a single, non-bootable, large user filesystem.
 *	         Good for second drives on a machine (e.g. /usr/src).
E 18
I 18
 * Misc. HW description, indexed by sc_type.
 * Nothing really critical here, could do without it.
E 18
 */
D 18
struct size rd7945A_sizes[8] = {
	RDSZ(15904),	1,		/* A=cyl 1 thru 142 */
	RDSZ(20160),	143,		/* B=cyl 143 thru 322 */
	RDSZ(108416),	0,		/* C=cyl 0 thru 967 */
	RDSZ(40320),	143,		/* D=cyl 143 thru 502 */
	RDSZ(0),	0,		/* E=<undefined> */
	RDSZ(0),	0,		/* F=<undefined> */
	RDSZ(72240),	323,		/* G=cyl 323 thru 967 */
	RDSZ(52080),	503,		/* H=cyl 503 thru 967 */
}, rd9134D_sizes[8] = {
	RDSZ(15936),	1,		/* A=cyl 1 thru 166 */
	RDSZ(13056),	167,		/* B=cyl 167 thru 302 */
	RDSZ(29088),	0,		/* C=cyl 0 thru 302 */
	RDSZ(0),	0,		/* D=<undefined> */
	RDSZ(0),	0,		/* E=<undefined> */
	RDSZ(0),	0,		/* F=<undefined> */
	RDSZ(0),	0,		/* G=<undefined> */
	RDSZ(0),	0,		/* H=<undefined> */
}, rd9122S_sizes[8] = {
	RDSZ(0),	0,		/* A=<undefined> */
	RDSZ(0),	0,		/* B=<undefined> */
	RDSZ(1232),	0,		/* C=cyl 0 thru 76 */
	RDSZ(0),	0,		/* D=<undefined> */
	RDSZ(0),	0,		/* E=<undefined> */
	RDSZ(0),	0,		/* F=<undefined> */
	RDSZ(0),	0,		/* G=<undefined> */
	RDSZ(0),	0,		/* H=<undefined> */
}, rd7912P_sizes[8] = {
	RDSZ(15904),	0,		/* A=cyl 1 thru 71 */
	RDSZ(22400),	72,		/* B=cyl 72 thru 171 */
	RDSZ(128128),	0,		/* C=cyl 0 thru 571 */
	RDSZ(42560),	72,		/* D=cyl 72 thru 261 */
	RDSZ(0),	292,		/* E=<undefined> */
	RDSZ(0),	542,		/* F=<undefined> */
	RDSZ(89600),	172,		/* G=cyl 221 thru 571 */
	RDSZ(69440),	262,		/* H=cyl 262 thru 571 */
}, rd7914P_sizes[8] = {
	RDSZ(15904),	1,		/* A=cyl 1 thru 71 */
	RDSZ(40320),	72,		/* B=cyl 72 thru 251 */
	RDSZ(258048),	0,		/* C=cyl 0 thru 1151 */
	RDSZ(64960),	72,		/* D=cyl 72 thru 361 */
	RDSZ(98560),	362,		/* E=cyl 362 thru 801 */
	RDSZ(78400),	802,		/* F=cyl 802 thru 1151 */
	RDSZ(201600),	252,		/* G=cyl 221 thru 1151 */
	RDSZ(176960),	362,		/* H=cyl 362 thru 1151 */
}, rd7933H_sizes[8] = {
	RDSZ(16146),	1,		/* A=cyl 1 thru 27 */
	RDSZ(66976),	28,		/* B=cyl 28 thru 139 */
	RDSZ(789958),	0,		/* C=cyl 0 thru 1320 */
	RDSZ(16146),	140,		/* D=cyl 140 thru 166 */
	RDSZ(165646),	167,		/* E=cyl 167 thru 443 */
	RDSZ(165646),	444,		/* F=cyl 444 thru 720 */
	RDSZ(706238),	140,		/* G=cyl 140 thru 1320 */
	RDSZ(358800),	721,		/* H=cyl 721 thru 1320 */
}, rd9134L_sizes[8] = {
	RDSZ(15920),	1,		/* A=cyl 1 thru 199 */
	RDSZ(20000),	200,		/* B=cyl 200 thru 449 */
	RDSZ(77840),	0,		/* C=cyl 0 thru 972 */
	RDSZ(32000),	200,		/* D=cyl 200 thru 599 */
	RDSZ(0),	0,		/* E=<undefined> */
	RDSZ(0),	0,		/* F=<undefined> */
	RDSZ(41840),	450,		/* G=cyl 450 thru 972 */
	RDSZ(29840),	600,		/* H=cyl 600 thru 972 */
}, rd7957A_sizes[8] = {
	RDSZ(16016),	1,		/* A=cyl 1 thru 104 */
	RDSZ(24640),	105,		/* B=cyl 105 thru 264 */
	RDSZ(159544),	0,		/* C=cyl 0 thru 1035 */
	RDSZ(42350),	105,		/* D=cyl 105 thru 379 */
	RDSZ(54824),	380,		/* E=cyl 380 thru 735 */
	RDSZ(46200),	736,		/* F=cyl 736 thru 1035 */
	RDSZ(118734),	265,		/* G=cyl 265 thru 1035 */
	RDSZ(101024),	380,		/* H=cyl 380 thru 1035 */
}, rd7958A_sizes[8] = {
	RDSZ(16128),	1,		/* A=cyl 1 thru 64 */
	RDSZ(32256),	65,		/* B=cyl 65 thru 192 */
	RDSZ(255276),	0,		/* C=cyl 0 thru 1012 */
	RDSZ(48384),	65,		/* D=cyl 65 thru 256 */
	RDSZ(100800),	257,		/* E=cyl 257 thru 656 */
	RDSZ(89712),	657,		/* F=cyl 657 thru 1012 */
	RDSZ(206640),	193,		/* G=cyl 193 thru 1012 */
	RDSZ(190512),	257,		/* H=cyl 257 thru 1012 */
}, rd7957B_sizes[8] = {
	RDSZ(16002),	1,		/* A=cyl 1 thru 127 */
	RDSZ(32760),	128,		/* B=cyl 128 thru 387 */
	RDSZ(159894),	0,		/* C=cyl 0 thru 1268 */
	RDSZ(49140),	128,		/* D=cyl 128 thru 517 */
	RDSZ(50400),	518,		/* E=cyl 518 thru 917 */
	RDSZ(44226),	918,		/* F=cyl 918 thru 1268 */
	RDSZ(111006),	388,		/* G=cyl 388 thru 1268 */
	RDSZ(94626),	518,		/* H=cyl 518 thru 1268 */
}, rd7958B_sizes[8] = {
	RDSZ(16254),	1,		/* A=cyl 1 thru 43 */
	RDSZ(32886),	44,		/* B=cyl 44 thru 130 */
	RDSZ(297108),	0,		/* C=cyl 0 thru 785 */
	RDSZ(49140),	44,		/* D=cyl 44 thru 173 */
	RDSZ(121716),	174,		/* E=cyl 174 thru 495 */
	RDSZ(109620),	496,		/* F=cyl 496 thru 785 */
	RDSZ(247590),	131,		/* G=cyl 131 thru 785 */
	RDSZ(231336),	174,		/* H=cyl 174 thru 785 */
}, rd7959B_sizes[8] = {
	RDSZ(16254),	1,		/* A=cyl 1 thru 43 */
	RDSZ(49140),	44,		/* B=cyl 44 thru 173 */
	RDSZ(594216),	0,		/* C=cyl 0 thru 1571 */
	RDSZ(65772),	44,		/* D=cyl 44 thru 217 */
	RDSZ(303912),	218,		/* E=cyl 218 thru 1021 */
	RDSZ(207900),	1022,		/* F=cyl 1022 thru 1571 */
	RDSZ(528444),	174,		/* G=cyl 174 thru 1571 */
	RDSZ(511812),	218,		/* H=cyl 218 thru 1571 */
I 6
}, rd2200A_sizes[8] = {
	RDSZ(16272),	1,		/* A=cyl 1 thru 36 */
	RDSZ(49720),	37,		/* B=cyl 37 thru 146 */
	RDSZ(654948),	0,		/* C=cyl 0 thru 1448 */
	RDSZ(65992),	37,		/* D=cyl 37 thru 182 */
	RDSZ(304648),	183,		/* E=cyl 183 thru 856 */
	RDSZ(267584),	857,		/* F=cyl 857 thru 1448 */
	RDSZ(588504),	147,		/* G=cyl 147 thru 1448 */
	RDSZ(572232),	183,		/* H=cyl 183 thru 1448 */
}, rd2203A_sizes[8] = {
	/* modelled after the 7937; i.e. bogus */
	RDSZ(16272),	1,		/* A=cyl 1 thru 18 */
	RDSZ(67800),	19,		/* B=cyl 19 thru 93 */
	RDSZ(1309896),	0,		/* C=cyl 0 thru 1448 */
	RDSZ(16272),	94,		/* D=cyl 19 thru 111 */
	RDSZ(305552),	112,		/* E=cyl 112 thru 449 */
	RDSZ(305552),	450,		/* F=cyl 450 thru 787 */
	RDSZ(1224920),	94,		/* G=cyl 94 thru 1448 */
	RDSZ(597544),	788,		/* H=cyl 788 thru 1448 */
E 6

#if DEV_BSIZE == 512
/*
 * These values would not work for 1k,
 * since the number of cylinders would be different.
 */
}, rd7936H_sizes[8] = {
	RDSZ(16359),	1,		/* A=cyl 1 thru 19 */
	RDSZ(67158),	20,		/* B=cyl 20 thru 97 */
	RDSZ(600978),	0,		/* C=cyl 0 thru 697 */
	RDSZ(16359),	98,		/* D=cyl 98 thru 116 */
	RDSZ(120540),	117,		/* E=cyl 117 thru 256 */
	RDSZ(120540),	256,		/* F=cyl 256 thru 396 */
	RDSZ(516600),	98,		/* G=cyl 98 thru 697 */
	RDSZ(259161),	397,		/* H=cyl 397 thru 697 */
}, rd7937H_sizes[8] = {
D 16
#ifdef UTAH
E 16
	RDSZ(15990),	1,		/* A=cyl 1 thru 10 */
	RDSZ(67158),	11,		/* B=cyl 11 thru 52 */
	RDSZ(1116102),	0,		/* C=cyl 0 thru 697 */
	RDSZ(124722),	53,		/* D=cyl 53 thru 130 */
	RDSZ(163098),	131,		/* E=cyl 131 thru 232 */
	RDSZ(287820),	233,		/* F=cyl 233 thru 412 */
	RDSZ(1031355),	53,		/* G=cyl 53 thru 697 */
	RDSZ(455715),	413,		/* H=cyl 413 thru 697 */
D 16
#else
	RDSZ(15990),	1,		/* A=cyl 1 thru 10 */
	RDSZ(67158),	11,		/* B=cyl 11 thru 52 */
	RDSZ(1116102),	0,		/* C=cyl 0 thru 697 */
	RDSZ(15990),	53,		/* D=cyl 53 thru 62 */
	RDSZ(246246),	63,		/* E=cyl 63 thru 216 */
	RDSZ(246246),	217,		/* F=cyl 217 thru 370 */
	RDSZ(1031355),	53,		/* G=cyl 53 thru 697 */
	RDSZ(522873),	371,		/* H=cyl 371 thru 697 */
#endif
E 16
#endif
E 18
I 18
struct rdidentinfo rdidentinfo[] = {
	{ RD7946AID,	0,	"7945A",	 108416 },
	{ RD9134DID,	1,	"9134D",	  29088 },
	{ RD9134LID,	1,	"9122S",	   1232 },
	{ RD7912PID,	0,	"7912P",	 128128 },
	{ RD7914PID,	0,	"7914P",	 258048 },
	{ RD7958AID,	0,	"7958A",	 255276 },
	{ RD7957AID,	0,	"7957A",	 159544 },
	{ RD7933HID,	0,	"7933H",	 789958 },
	{ RD9134LID,	1,	"9134L",	  77840 },
	{ RD7936HID,	0,	"7936H",	 600978 },
	{ RD7937HID,	0,	"7937H",	1116102 },
	{ RD7914CTID,	0,	"7914CT",	 258048 },
	{ RD7946AID,	0,	"7946A",	 108416 },
	{ RD9134LID,	1,	"9122D",	   1232 },
	{ RD7957BID,	0,	"7957B",	 159894 },
	{ RD7958BID,	0,	"7958B",	 297108 },
	{ RD7959BID,	0,	"7959B",	 594216 },
	{ RD2200AID,	0,	"2200A",	 654948 },
	{ RD2203AID,	0,	"2203A",	1309896 }
E 18
};
I 18
int numrdidentinfo = sizeof(rdidentinfo) / sizeof(rdidentinfo[0]);
E 18

D 18
struct	rdinfo {
	int	nbpt;		/* DEV_BSIZE blocks per track */
	int	ntpc;		/* tracks per cylinder */
	int	nbpc;		/* blocks per cylinder */
	struct	size *sizes;	/* default partition info (if no disklabel) */
	short	hwid;		/* 2 byte HW id */
	short	maxunum;	/* maximum allowed unit number */
	char	*desc;		/* drive type description */
};

struct rdinfo rdinfo[] = {
	NRD7945ABPT,	NRD7945ATRK,	NRD7945ABPT * NRD7945ATRK,
	rd7945A_sizes,	RD7946AID,	0,	"7945A",
	NRD9134DBPT,	NRD9134DTRK,	NRD9134DBPT * NRD9134DTRK,
	rd9134D_sizes,	RD9134DID,	1,	"9134D",
	NRD9122SBPT,	NRD9122STRK,	NRD9122SBPT * NRD9122STRK,
	rd9122S_sizes,	RD9134LID,	1,	"9122S",
	NRD7912PBPT,	NRD7912PTRK,	NRD7912PBPT * NRD7912PTRK,
	rd7912P_sizes,	RD7912PID,	0,	"7912P",
	NRD7914PBPT,	NRD7914PTRK,	NRD7914PBPT * NRD7914PTRK,
	rd7914P_sizes,	RD7914PID,	0,	"7914P",
	NRD7958ABPT,	NRD7958ATRK,	NRD7958ABPT * NRD7958ATRK,
	rd7958A_sizes,	RD7958AID,	0,	"7958A",
	NRD7957ABPT,	NRD7957ATRK,	NRD7957ABPT * NRD7957ATRK,
	rd7957A_sizes,	RD7957AID,	0,	"7957A",
	NRD7933HBPT,	NRD7933HTRK,	NRD7933HBPT * NRD7933HTRK,
	rd7933H_sizes,	RD7933HID,	0,	"7933H",
	NRD9134LBPT,	NRD9134LTRK,	NRD9134LBPT * NRD9134LTRK,
	rd9134L_sizes,	RD9134LID,	1,	"9134L",
	NRD7936HBPT,	NRD7936HTRK,	NRD7936HBPT * NRD7936HTRK,
	rd7936H_sizes,	RD7936HID,	0,	"7936H",
	NRD7937HBPT,	NRD7937HTRK,	NRD7937HBPT * NRD7937HTRK,
	rd7937H_sizes,	RD7937HID,	0,	"7937H",
	NRD7914PBPT,	NRD7914PTRK,	NRD7914PBPT * NRD7914PTRK,
	rd7914P_sizes,	RD7914CTID,	0,	"7914CT",
	NRD7945ABPT,	NRD7945ATRK,	NRD7945ABPT * NRD7945ATRK,
	rd7945A_sizes,	RD7946AID,	0,	"7946A",
	NRD9122SBPT,	NRD9122STRK,	NRD9122SBPT * NRD9122STRK,
	rd9122S_sizes,	RD9134LID,	1,	"9122D",
	NRD7957BBPT,	NRD7957BTRK,	NRD7957BBPT * NRD7957BTRK,
	rd7957B_sizes,	RD7957BID,	0,	"7957B",
	NRD7958BBPT,	NRD7958BTRK,	NRD7958BBPT * NRD7958BTRK,
	rd7958B_sizes,	RD7958BID,	0,	"7958B",
	NRD7959BBPT,	NRD7959BTRK,	NRD7959BBPT * NRD7959BTRK,
	rd7959B_sizes,	RD7959BID,	0,	"7959B",
I 6
	NRD2200ABPT,	NRD2200ATRK,	NRD2200ABPT * NRD2200ATRK,
	rd2200A_sizes,	RD2200AID,	0,	"2200A",
	NRD2203ABPT,	NRD2203ATRK,	NRD2203ABPT * NRD2203ATRK,
	rd2203A_sizes,	RD2203AID,	0,	"2203A",
E 6
};
int nrdinfo = sizeof(rdinfo) / sizeof(rdinfo[0]);

struct	buf rdtab[NRD];
D 9
struct	buf rdbuf[NRD];
E 9

D 8
#define	rdunit(x)	((minor(x) >> 3) & 0xf)
E 8
I 8
#define	rdunit(x)	(minor(x) >> 3)
E 8
#define rdpart(x)	(minor(x) & 0x7)
#define	rdpunit(x)	((x) & 7)
#define	b_cylin		b_resid
#define	RDRETRY		5
#define RDWAITC		1	/* min time for timeout in seconds */

I 3
int rderrthresh = RDRETRY-1;	/* when to start reporting errors */

E 18
E 3
rdinit(hd)
	register struct hp_device *hd;
{
	register struct rd_softc *rs = &rd_softc[hd->hp_unit];

	rs->sc_hd = hd;
	rs->sc_punit = rdpunit(hd->hp_flags);
	rs->sc_type = rdident(rs, hd);
	if (rs->sc_type < 0)
		return(0);
	rs->sc_dq.dq_ctlr = hd->hp_ctlr;
	rs->sc_dq.dq_unit = hd->hp_unit;
	rs->sc_dq.dq_slave = hd->hp_slave;
	rs->sc_dq.dq_driver = &rddriver;
D 18
	rs->sc_info = &rdinfo[rs->sc_type];
E 18
	rs->sc_flags = RDF_ALIVE;
I 3
#ifdef DEBUG
	/* always report errors */
	if (rddebug & RDB_ERROR)
		rderrthresh = 0;
#endif
E 3
	return(1);
}

rdident(rs, hd)
	struct rd_softc *rs;
	struct hp_device *hd;
{
	struct rd_describe desc;
	u_char stat, cmd[3];
	int unit, lunit;
	char name[7];
	register int ctlr, slave, id, i;

	ctlr = hd->hp_ctlr;
	slave = hd->hp_slave;
	unit = rs->sc_punit;
	lunit = hd->hp_unit;

	/*
	 * Grab device id and make sure:
	 * 1. It is a CS80 device.
	 * 2. It is one of the types we support.
	 * 3. If it is a 7946, we are accessing the disk unit (0)
	 */
	id = hpibid(ctlr, slave);
I 6
#ifdef DEBUG
	if (rddebug & RDB_IDENT)
		printf("hpibid(%d, %d) -> %x\n", ctlr, slave, id);
#endif
E 6
	if ((id & 0x200) == 0)
		return(-1);
D 18
	for (i = 0; i < nrdinfo; i++)
		if (id == rdinfo[i].hwid)
E 18
I 18
	for (i = 0; i < numrdidentinfo; i++)
		if (id == rdidentinfo[i].ri_hwid)
E 18
			break;
D 18
	if (i == nrdinfo || unit > rdinfo[i].maxunum)
E 18
I 18
	if (i == numrdidentinfo || unit > rdidentinfo[i].ri_maxunum)
E 18
		return(-1);
	id = i;

	/*
	 * Reset drive and collect device description.
	 * Don't really use the description info right now but
	 * might come in handy in the future (for disk labels).
	 */
	rdreset(rs, hd);
	cmd[0] = C_SUNIT(unit);
	cmd[1] = C_SVOL(0);
	cmd[2] = C_DESC;
	hpibsend(ctlr, slave, C_CMD, cmd, sizeof(cmd));
	hpibrecv(ctlr, slave, C_EXEC, &desc, 37);
	hpibrecv(ctlr, slave, C_QSTAT, &stat, sizeof(stat));
	bzero(name, sizeof(name));
	if (!stat) {
		register int n = desc.d_name;
		for (i = 5; i >= 0; i--) {
			name[i] = (n & 0xf) + '0';
			n >>= 4;
		}
I 3
		/* use drive characteristics to calculate xfer rate */
		rs->sc_wpms = 1000000 * (desc.d_sectsize/2) / desc.d_blocktime;
E 3
	}
#ifdef DEBUG
	if (rddebug & RDB_IDENT) {
		printf("rd%d: name: %x ('%s')\n",
		       lunit, desc.d_name, name);
		printf("  iuw %x, maxxfr %d, ctype %d\n",
		       desc.d_iuw, desc.d_cmaxxfr, desc.d_ctype);
		printf("  utype %d, bps %d, blkbuf %d, burst %d, blktime %d\n",
		       desc.d_utype, desc.d_sectsize,
		       desc.d_blkbuf, desc.d_burstsize, desc.d_blocktime);
		printf("  avxfr %d, ort %d, atp %d, maxint %d, fv %x, rv %x\n",
		       desc.d_uavexfr, desc.d_retry, desc.d_access,
		       desc.d_maxint, desc.d_fvbyte, desc.d_rvbyte);
		printf("  maxcyl/head/sect %d/%d/%d, maxvsect %d, inter %d\n",
		       desc.d_maxcyl, desc.d_maxhead, desc.d_maxsect,
		       desc.d_maxvsectl, desc.d_interleave);
	}
#endif
	/*
	 * Take care of a couple of anomolies:
	 * 1. 7945A and 7946A both return same HW id
	 * 2. 9122S and 9134D both return same HW id
	 * 3. 9122D and 9134L both return same HW id
	 */
D 18
	switch (rdinfo[id].hwid) {
E 18
I 18
	switch (rdidentinfo[id].ri_hwid) {
E 18
	case RD7946AID:
		if (bcmp(name, "079450", 6) == 0)
			id = RD7945A;
		else
			id = RD7946A;
		break;

	case RD9134LID:
		if (bcmp(name, "091340", 6) == 0)
			id = RD9134L;
		else
			id = RD9122D;
		break;

	case RD9134DID:
		if (bcmp(name, "091220", 6) == 0)
			id = RD9122S;
		else
			id = RD9134D;
		break;
	}
D 18
	printf("rd%d: %s\n", lunit, rdinfo[id].desc);
E 18
I 18
	printf("rd%d: %s\n", lunit, rdidentinfo[id].ri_desc);
E 18
	return(id);
}

rdreset(rs, hd)
	register struct rd_softc *rs;
	register struct hp_device *hd;
{
	u_char stat;

	rs->sc_clear.c_unit = C_SUNIT(rs->sc_punit);
	rs->sc_clear.c_cmd = C_CLEAR;
	hpibsend(hd->hp_ctlr, hd->hp_slave, C_TCMD, &rs->sc_clear,
		sizeof(rs->sc_clear));
	hpibswait(hd->hp_ctlr, hd->hp_slave);
	hpibrecv(hd->hp_ctlr, hd->hp_slave, C_QSTAT, &stat, sizeof(stat));
	rs->sc_src.c_unit = C_SUNIT(RDCTLR);
	rs->sc_src.c_nop = C_NOP;
	rs->sc_src.c_cmd = C_SREL;
	rs->sc_src.c_param = C_REL;
	hpibsend(hd->hp_ctlr, hd->hp_slave, C_CMD, &rs->sc_src,
		sizeof(rs->sc_src));
	hpibswait(hd->hp_ctlr, hd->hp_slave);
	hpibrecv(hd->hp_ctlr, hd->hp_slave, C_QSTAT, &stat, sizeof(stat));
	rs->sc_ssmc.c_unit = C_SUNIT(rs->sc_punit);
	rs->sc_ssmc.c_cmd = C_SSM;
	rs->sc_ssmc.c_refm = REF_MASK;
	rs->sc_ssmc.c_fefm = FEF_MASK;
	rs->sc_ssmc.c_aefm = AEF_MASK;
	rs->sc_ssmc.c_iefm = IEF_MASK;
	hpibsend(hd->hp_ctlr, hd->hp_slave, C_CMD, &rs->sc_ssmc,
		sizeof(rs->sc_ssmc));
	hpibswait(hd->hp_ctlr, hd->hp_slave);
	hpibrecv(hd->hp_ctlr, hd->hp_slave, C_QSTAT, &stat, sizeof(stat));
#ifdef DEBUG
	rdstats[hd->hp_unit].rdresets++;
#endif
}

I 18
/*
 * Read or constuct a disklabel
 */
E 18
D 9
/*ARGSUSED*/
rdopen(dev, flags)
E 9
I 9
int
I 18
rdgetinfo(dev)
	dev_t dev;
{
	int unit = rdunit(dev);
	register struct rd_softc *rs = &rd_softc[unit];
	register struct disklabel *lp = &rs->sc_info.ri_label;
	register struct partition *pi;
	char *msg, *readdisklabel();

	/*
	 * Set some default values to use while reading the label
	 * or to use if there isn't a label.
	 */
	bzero((caddr_t)lp, sizeof *lp);
	lp->d_type = DTYPE_HPIB;
	lp->d_secsize = DEV_BSIZE;
	lp->d_nsectors = 32;
	lp->d_ntracks = 20;
I 19
	lp->d_ncylinders = 1;
E 19
	lp->d_secpercyl = 32*20;
	lp->d_npartitions = 3;
	lp->d_partitions[2].p_offset = 0;
	lp->d_partitions[2].p_size = LABELSECTOR+1;

	/*
	 * Now try to read the disklabel
	 */
	msg = readdisklabel(rdlabdev(dev), rdstrategy, lp);
	if (msg == NULL)
		return(0);

	pi = lp->d_partitions;
	printf("rd%d: WARNING: %s, ", unit, msg);
#ifdef COMPAT_NOLABEL
	printf("using old default partitioning\n");
	rdmakedisklabel(unit, lp);
#else
	printf("defining `c' partition as entire disk\n");
	pi[2].p_size = rdidentinfo[rs->sc_type].ri_nblocks;
I 21
	/* XXX reset other info since readdisklabel screws with it */
	lp->d_npartitions = 3;
	pi[0].p_size = 0;
E 21
#endif
	return(0);
}

int
E 18
rdopen(dev, flags, mode, p)
E 9
	dev_t dev;
I 9
	int flags, mode;
	struct proc *p;
E 9
{
	register int unit = rdunit(dev);
	register struct rd_softc *rs = &rd_softc[unit];
I 18
	int error, mask;
E 18

	if (unit >= NRD || (rs->sc_flags & RDF_ALIVE) == 0)
		return(ENXIO);
I 18

	/*
	 * Wait for any pending opens/closes to complete
	 */
	while (rs->sc_flags & (RDF_OPENING|RDF_CLOSING))
		sleep((caddr_t)rs, PRIBIO);

	/*
	 * On first open, get label and partition info.
	 * We may block reading the label, so be careful
	 * to stop any other opens.
	 */
	if (rs->sc_info.ri_open == 0) {
		rs->sc_flags |= RDF_OPENING;
		error = rdgetinfo(dev);
		rs->sc_flags &= ~RDF_OPENING;
		wakeup((caddr_t)rs);
		if (error)
			return(error);
	}
E 18
D 3
	if (rs->sc_hd->hp_dk >= 0)
	dk_wpms[rs->sc_hd->hp_dk] = 60 * rs->sc_info->nbpt * DEV_BSIZE / 2;
E 3
I 3
	if (rs->sc_hd->hp_dk >= 0) {
		/* guess at xfer rate based on 3600 rpm (60 rps) */
		if (rs->sc_wpms == 0)
D 18
			rs->sc_wpms = 60 * rs->sc_info->nbpt * DEV_BSIZE / 2;
E 18
I 18
			rs->sc_wpms = 60 * rs->sc_info.ri_label.d_nsectors
				* DEV_BSIZE / 2;
E 18
		dk_wpms[rs->sc_hd->hp_dk] = rs->sc_wpms;
	}
I 18

	mask = 1 << rdpart(dev);
	if (mode == S_IFCHR)
		rs->sc_info.ri_copen |= mask;
	else
		rs->sc_info.ri_bopen |= mask;
	rs->sc_info.ri_open |= mask;
E 18
E 3
	return(0);
}

I 18
int
rdclose(dev, flag, mode, p)
	dev_t dev;
	int flag, mode;
	struct proc *p;
{
	int unit = rdunit(dev);
	register struct rd_softc *rs = &rd_softc[unit];
	register struct rdinfo *ri = &rs->sc_info;
	int mask, s;

	mask = 1 << rdpart(dev);
	if (mode == S_IFCHR)
		ri->ri_copen &= ~mask;
	else
		ri->ri_bopen &= ~mask;
	ri->ri_open = ri->ri_bopen | ri->ri_copen;
	/*
	 * On last close, we wait for all activity to cease since
	 * the label/parition info will become invalid.  Since we
	 * might sleep, we must block any opens while we are here.
	 * Note we don't have to about other closes since we know
	 * we are the last one.
	 */
	if (ri->ri_open == 0) {
		rs->sc_flags |= RDF_CLOSING;
		s = splbio();
		while (rdtab[unit].b_active) {
			rs->sc_flags |= RDF_WANTED;
			sleep((caddr_t)&rdtab[unit], PRIBIO);
		}
		splx(s);
		rs->sc_flags &= ~(RDF_CLOSING|RDF_WLABEL);
		wakeup((caddr_t)rs);
	}
	return(0);
}

void
E 18
rdstrategy(bp)
	register struct buf *bp;
{
D 4
	register int part = rdpart(bp->b_dev);
E 4
D 18
	register int unit = rdunit(bp->b_dev);
E 18
I 18
	int unit = rdunit(bp->b_dev);
E 18
D 4
	register int bn, sz;
E 4
	register struct rd_softc *rs = &rd_softc[unit];
I 4
D 18
	register struct size *pinfo = &rs->sc_info->sizes[rdpart(bp->b_dev)];
E 18
E 4
	register struct buf *dp = &rdtab[unit];
I 18
	register struct partition *pinfo;
E 18
D 4
	int s;
E 4
I 4
	register daddr_t bn;
	register int sz, s;
E 4

#ifdef DEBUG
	if (rddebug & RDB_FOLLOW)
		printf("rdstrategy(%x): dev %x, bn %x, bcount %x, %c\n",
		       bp, bp->b_dev, bp->b_blkno, bp->b_bcount,
		       (bp->b_flags & B_READ) ? 'R' : 'W');
#endif
	bn = bp->b_blkno;
D 4
	sz = (bp->b_bcount + (DEV_BSIZE - 1)) >> DEV_BSHIFT;
	if (bn < 0 || bn + sz > rs->sc_info->sizes[part].nblocks) {
		if (bn == rs->sc_info->sizes[part].nblocks) {
E 4
I 4
	sz = howmany(bp->b_bcount, DEV_BSIZE);
D 18
	if (bn < 0 || bn + sz > pinfo->nblocks) {
		sz = pinfo->nblocks - bn;
E 18
I 18
	pinfo = &rs->sc_info.ri_label.d_partitions[rdpart(bp->b_dev)];
	if (bn < 0 || bn + sz > pinfo->p_size) {
		sz = pinfo->p_size - bn;
E 18
		if (sz == 0) {
E 4
			bp->b_resid = bp->b_bcount;
			goto done;
		}
D 4
		bp->b_error = EINVAL;
		goto bad;
E 4
I 4
		if (sz < 0) {
			bp->b_error = EINVAL;
D 18
			bp->b_flags |= B_ERROR;
			goto done;
E 18
I 18
			goto bad;
E 18
		}
		bp->b_bcount = dbtob(sz);
E 4
	}
D 4
	bp->b_cylin = bn / rs->sc_info->nbpc + rs->sc_info->sizes[part].cyloff;
E 4
I 4
D 18
	bp->b_cylin = bn / rs->sc_info->nbpc + pinfo->cyloff;
E 18
I 18
	/*
	 * Check for write to write protected label
	 */
	if (bn + pinfo->p_offset <= LABELSECTOR &&
#if LABELSECTOR != 0
	    bn + pinfo->p_offset + sz > LABELSECTOR &&
#endif
	    !(bp->b_flags & B_READ) && !(rs->sc_flags & RDF_WLABEL)) {
		bp->b_error = EROFS;
		goto bad;
	}
	bp->b_cylin = bn + pinfo->p_offset;
E 18
E 4
	s = splbio();
	disksort(dp, bp);
	if (dp->b_active == 0) {
		dp->b_active = 1;
		rdustart(unit);
	}
	splx(s);
	return;
I 18
bad:
	bp->b_flags |= B_ERROR;
E 18
D 4
bad:
	bp->b_flags |= B_ERROR;
E 4
done:
	biodone(bp);
}

/*
 * Called from timeout() when handling maintenance releases
 */
D 15
rdrestart(unit)
	int unit;
E 15
I 15
void
rdrestart(arg)
	void *arg;
E 15
{
	int s = splbio();
D 15
	rdustart(unit);
E 15
I 15
	rdustart((int)arg);
E 15
	splx(s);
}

rdustart(unit)
	register int unit;
{
	register struct buf *bp;
	register struct rd_softc *rs = &rd_softc[unit];

	bp = rdtab[unit].b_actf;
	rs->sc_addr = bp->b_un.b_addr;
	rs->sc_resid = bp->b_bcount;
	if (hpibreq(&rs->sc_dq))
		rdstart(unit);
}

I 18
struct buf *
rdfinish(unit, rs, bp)
	int unit;
	register struct rd_softc *rs;
	register struct buf *bp;
{
	register struct buf *dp = &rdtab[unit];

	dp->b_errcnt = 0;
	dp->b_actf = bp->b_actf;
	bp->b_resid = 0;
	biodone(bp);
	hpibfree(&rs->sc_dq);
	if (dp->b_actf)
		return(dp->b_actf);
	dp->b_active = 0;
	if (rs->sc_flags & RDF_WANTED) {
		rs->sc_flags &= ~RDF_WANTED;
		wakeup((caddr_t)dp);
	}
	return(NULL);
}

E 18
rdstart(unit)
	register int unit;
{
	register struct rd_softc *rs = &rd_softc[unit];
	register struct buf *bp = rdtab[unit].b_actf;
	register struct hp_device *hp = rs->sc_hd;
	register int part;

again:
#ifdef DEBUG
	if (rddebug & RDB_FOLLOW)
		printf("rdstart(%d): bp %x, %c\n", unit, bp,
		       (bp->b_flags & B_READ) ? 'R' : 'W');
#endif
	part = rdpart(bp->b_dev);
	rs->sc_flags |= RDF_SEEK;
	rs->sc_ioc.c_unit = C_SUNIT(rs->sc_punit);
	rs->sc_ioc.c_volume = C_SVOL(0);
	rs->sc_ioc.c_saddr = C_SADDR;
	rs->sc_ioc.c_hiaddr = 0;
D 18
	rs->sc_ioc.c_addr = RDBTOS(bp->b_blkno + rs->sc_info->nbpc *
		rs->sc_info->sizes[part].cyloff);
E 18
I 18
	rs->sc_ioc.c_addr = RDBTOS(bp->b_cylin);
E 18
	rs->sc_ioc.c_nop2 = C_NOP;
	rs->sc_ioc.c_slen = C_SLEN;
	rs->sc_ioc.c_len = rs->sc_resid;
	rs->sc_ioc.c_cmd = bp->b_flags & B_READ ? C_READ : C_WRITE;
#ifdef DEBUG
	if (rddebug & RDB_IO)
		printf("rdstart: hpibsend(%x, %x, %x, %x, %x)\n",
		       hp->hp_ctlr, hp->hp_slave, C_CMD,
		       &rs->sc_ioc.c_unit, sizeof(rs->sc_ioc)-2);
#endif
	if (hpibsend(hp->hp_ctlr, hp->hp_slave, C_CMD, &rs->sc_ioc.c_unit,
		     sizeof(rs->sc_ioc)-2) == sizeof(rs->sc_ioc)-2) {
		if (hp->hp_dk >= 0) {
			dk_busy |= 1 << hp->hp_dk;
			dk_seek[hp->hp_dk]++;
		}
#ifdef DEBUG
		if (rddebug & RDB_IO)
			printf("rdstart: hpibawait(%x)\n", hp->hp_ctlr);
#endif
		hpibawait(hp->hp_ctlr);
		return;
	}
	/*
	 * Experience has shown that the hpibwait in this hpibsend will
	 * occasionally timeout.  It appears to occur mostly on old 7914
	 * drives with full maintenance tracks.  We should probably
	 * integrate this with the backoff code in rderror.
	 */
#ifdef DEBUG
	if (rddebug & RDB_ERROR)
		printf("rd%d: rdstart: cmd %x adr %d blk %d len %d ecnt %d\n",
		       unit, rs->sc_ioc.c_cmd, rs->sc_ioc.c_addr,
		       bp->b_blkno, rs->sc_resid, rdtab[unit].b_errcnt);
	rdstats[unit].rdretries++;
#endif
	rs->sc_flags &= ~RDF_SEEK;
	rdreset(rs, hp);
	if (rdtab[unit].b_errcnt++ < RDRETRY)
		goto again;
	printf("rd%d: rdstart err: cmd 0x%x sect %d blk %d len %d\n",
	       unit, rs->sc_ioc.c_cmd, rs->sc_ioc.c_addr,
	       bp->b_blkno, rs->sc_resid);
D 18
	rdtab[unit].b_errcnt = 0;
	rdtab[unit].b_actf = bp->b_actf;
E 18
	bp->b_flags |= B_ERROR;
	bp->b_error = EIO;
D 18
	bp->b_resid = 0;
	biodone(bp);
	hpibfree(&rs->sc_dq);
	bp = rdtab[unit].b_actf;
	if (bp == NULL) {
		rdtab[unit].b_active = 0;
		return;
E 18
I 18
	bp = rdfinish(unit, rs, bp);
	if (bp) {
		rs->sc_addr = bp->b_un.b_addr;
		rs->sc_resid = bp->b_bcount;
		if (hpibreq(&rs->sc_dq))
			goto again;
E 18
	}
D 18
	rs->sc_addr = bp->b_un.b_addr;
	rs->sc_resid = bp->b_bcount;
	if (hpibreq(&rs->sc_dq))
		goto again;
E 18
}

rdgo(unit)
	register int unit;
{
	register struct rd_softc *rs = &rd_softc[unit];
	register struct hp_device *hp = rs->sc_hd;
	struct buf *bp = rdtab[unit].b_actf;

	if (hp->hp_dk >= 0) {
		dk_busy |= 1 << hp->hp_dk;
		dk_xfer[hp->hp_dk]++;
		dk_wds[hp->hp_dk] += rs->sc_resid >> 6;
	}
I 18
#ifdef USELEDS
	if (inledcontrol == 0)
		ledcontrol(0, 0, LED_DISK);
#endif
E 18
	hpibgo(hp->hp_ctlr, hp->hp_slave, C_EXEC,
	       rs->sc_addr, rs->sc_resid, bp->b_flags & B_READ);
}

rdintr(unit)
	register int unit;
{
	register struct rd_softc *rs = &rd_softc[unit];
	register struct buf *bp = rdtab[unit].b_actf;
	register struct hp_device *hp = rs->sc_hd;
	u_char stat = 13;	/* in case hpibrecv fails */
D 4
	int restart;
E 4
I 4
	int rv, restart;
E 4
	
#ifdef DEBUG
	if (rddebug & RDB_FOLLOW)
		printf("rdintr(%d): bp %x, %c, flags %x\n", unit, bp,
		       (bp->b_flags & B_READ) ? 'R' : 'W', rs->sc_flags);
	if (bp == NULL) {
		printf("rd%d: bp == NULL\n", unit);
		return;
	}
#endif
	if (hp->hp_dk >= 0)
		dk_busy &= ~(1 << hp->hp_dk);
	if (rs->sc_flags & RDF_SEEK) {
		rs->sc_flags &= ~RDF_SEEK;
		if (hpibustart(hp->hp_ctlr))
			rdgo(unit);
		return;
	}
	if ((rs->sc_flags & RDF_SWAIT) == 0) {
#ifdef DEBUG
		rdstats[unit].rdpolltries++;
#endif
		if (hpibpptest(hp->hp_ctlr, hp->hp_slave) == 0) {
#ifdef DEBUG
			rdstats[unit].rdpollwaits++;
#endif
			if (hp->hp_dk >= 0)
				dk_busy |= 1 << hp->hp_dk;
			rs->sc_flags |= RDF_SWAIT;
			hpibawait(hp->hp_ctlr);
			return;
		}
	} else
		rs->sc_flags &= ~RDF_SWAIT;
D 4
	if (!hpibrecv(hp->hp_ctlr, hp->hp_slave, C_QSTAT, &stat, 1) || stat) {
E 4
I 4
	rv = hpibrecv(hp->hp_ctlr, hp->hp_slave, C_QSTAT, &stat, 1);
	if (rv != 1 || stat) {
E 4
#ifdef DEBUG
		if (rddebug & RDB_ERROR)
			printf("rdintr: recv failed or bad stat %d\n", stat);
#endif
		restart = rderror(unit);
#ifdef DEBUG
		rdstats[unit].rdretries++;
#endif
		if (rdtab[unit].b_errcnt++ < RDRETRY) {
			if (restart)
				rdstart(unit);
			return;
		}
		bp->b_flags |= B_ERROR;
		bp->b_error = EIO;
	}
D 18
	rdtab[unit].b_errcnt = 0;
	rdtab[unit].b_actf = bp->b_actf;
	bp->b_resid = 0;
	biodone(bp);
	hpibfree(&rs->sc_dq);
	if (rdtab[unit].b_actf)
E 18
I 18
	if (rdfinish(unit, rs, bp))
E 18
		rdustart(unit);
D 18
	else
		rdtab[unit].b_active = 0;
E 18
}

rdstatus(rs)
	register struct rd_softc *rs;
{
	register int c, s;
	u_char stat;
	int rv;

	c = rs->sc_hd->hp_ctlr;
	s = rs->sc_hd->hp_slave;
	rs->sc_rsc.c_unit = C_SUNIT(rs->sc_punit);
	rs->sc_rsc.c_sram = C_SRAM;
	rs->sc_rsc.c_ram = C_RAM;
	rs->sc_rsc.c_cmd = C_STATUS;
	bzero((caddr_t)&rs->sc_stat, sizeof(rs->sc_stat));
	rv = hpibsend(c, s, C_CMD, &rs->sc_rsc, sizeof(rs->sc_rsc));
	if (rv != sizeof(rs->sc_rsc)) {
#ifdef DEBUG
		if (rddebug & RDB_STATUS)
			printf("rdstatus: send C_CMD failed %d != %d\n",
			       rv, sizeof(rs->sc_rsc));
#endif
		return(1);
	}
	rv = hpibrecv(c, s, C_EXEC, &rs->sc_stat, sizeof(rs->sc_stat));
	if (rv != sizeof(rs->sc_stat)) {
#ifdef DEBUG
		if (rddebug & RDB_STATUS)
			printf("rdstatus: send C_EXEC failed %d != %d\n",
			       rv, sizeof(rs->sc_stat));
#endif
		return(1);
	}
	rv = hpibrecv(c, s, C_QSTAT, &stat, 1);
	if (rv != 1 || stat) {
#ifdef DEBUG
		if (rddebug & RDB_STATUS)
			printf("rdstatus: recv failed %d or bad stat %d\n",
			       rv, stat);
#endif
		return(1);
	}
	return(0);
}

/*
 * Deal with errors.
 * Returns 1 if request should be restarted,
 * 0 if we should just quietly give up.
 */
rderror(unit)
	int unit;
{
	struct rd_softc *rs = &rd_softc[unit];
	register struct rd_stat *sp;
	struct buf *bp;
D 3
	daddr_t bn, pbn;
E 3
I 3
	daddr_t hwbn, pbn;
E 3

	if (rdstatus(rs)) {
#ifdef DEBUG
		printf("rd%d: couldn't get status\n", unit);
#endif
		rdreset(rs, rs->sc_hd);
		return(1);
	}
	sp = &rs->sc_stat;
	if (sp->c_fef & FEF_REXMT)
		return(1);
	if (sp->c_fef & FEF_PF) {
		rdreset(rs, rs->sc_hd);
		return(1);
	}
	/*
	 * Unit requests release for internal maintenance.
	 * We just delay awhile and try again later.  Use expontially
	 * increasing backoff ala ethernet drivers since we don't really
	 * know how long the maintenance will take.  With RDWAITC and
	 * RDRETRY as defined, the range is 1 to 32 seconds.
	 */
	if (sp->c_fef & FEF_IMR) {
		extern int hz;
		int rdtimo = RDWAITC << rdtab[unit].b_errcnt;
#ifdef DEBUG
		printf("rd%d: internal maintenance, %d second timeout\n",
		       unit, rdtimo);
		rdstats[unit].rdtimeouts++;
#endif
		hpibfree(&rs->sc_dq);
D 15
		timeout(rdrestart, unit, rdtimo*hz);
E 15
I 15
		timeout(rdrestart, (void *)unit, rdtimo * hz);
E 15
		return(0);
	}
D 3
	bp = rdtab[unit].b_actf;
E 3
	/*
I 3
	 * Only report error if we have reached the error reporting
	 * threshhold.  By default, this will only report after the
	 * retry limit has been exceeded.
	 */
	if (rdtab[unit].b_errcnt < rderrthresh)
		return(1);

	/*
E 3
	 * First conjure up the block number at which the error occured.
	 * Note that not all errors report a block number, in that case
	 * we just use b_blkno.
 	 */
D 3
	pbn = RDSTOB(rs->sc_info->nbpc *
		     rs->sc_info->sizes[rdpart(bp->b_dev)].cyloff);
E 3
I 3
	bp = rdtab[unit].b_actf;
D 18
	pbn = rs->sc_info->nbpc *
		rs->sc_info->sizes[rdpart(bp->b_dev)].cyloff;
E 18
I 18
	pbn = rs->sc_info.ri_label.d_partitions[rdpart(bp->b_dev)].p_offset;
E 18
E 3
	if ((sp->c_fef & FEF_CU) || (sp->c_fef & FEF_DR) ||
	    (sp->c_ief & IEF_RRMASK)) {
D 3
		bn = pbn + bp->b_blkno;
E 3
I 3
		hwbn = RDBTOS(pbn + bp->b_blkno);
E 3
		pbn = bp->b_blkno;
	} else {
D 3
		bn = RDSTOB(sp->c_blk);
		pbn = bn - pbn;
E 3
I 3
		hwbn = sp->c_blk;
		pbn = RDSTOB(hwbn) - pbn;
E 3
	}
	/*
	 * Now output a generic message suitable for badsect.
	 * Note that we don't use harderr cuz it just prints
	 * out b_blkno which is just the beginning block number
	 * of the transfer, not necessary where the error occured.
	 */
	printf("rd%d%c: hard error sn%d\n",
	       rdunit(bp->b_dev), 'a'+rdpart(bp->b_dev), pbn);
	/*
	 * Now report the status as returned by the hardware with
	 * attempt at interpretation (unless debugging).
	 */
	printf("rd%d %s error:",
	       unit, (bp->b_flags & B_READ) ? "read" : "write");
#ifdef DEBUG
	if (rddebug & RDB_ERROR) {
		/* status info */
		printf("\n    volume: %d, unit: %d\n",
		       (sp->c_vu>>4)&0xF, sp->c_vu&0xF);
		rdprinterr("reject", sp->c_ref, err_reject);
		rdprinterr("fault", sp->c_fef, err_fault);
		rdprinterr("access", sp->c_aef, err_access);
		rdprinterr("info", sp->c_ief, err_info);
D 3
		printf("    block: %d, P1-P10: ", bn);
E 3
I 3
		printf("    block: %d, P1-P10: ", hwbn);
E 3
		printf("%s", hexstr(*(u_int *)&sp->c_raw[0], 8));
		printf("%s", hexstr(*(u_int *)&sp->c_raw[4], 8));
		printf("%s\n", hexstr(*(u_short *)&sp->c_raw[8], 4));
		/* command */
		printf("    ioc: ");
		printf("%s", hexstr(*(u_int *)&rs->sc_ioc.c_pad, 8));
		printf("%s", hexstr(*(u_short *)&rs->sc_ioc.c_hiaddr, 4));
		printf("%s", hexstr(*(u_int *)&rs->sc_ioc.c_addr, 8));
		printf("%s", hexstr(*(u_short *)&rs->sc_ioc.c_nop2, 4));
		printf("%s", hexstr(*(u_int *)&rs->sc_ioc.c_len, 8));
		printf("%s\n", hexstr(*(u_short *)&rs->sc_ioc.c_cmd, 4));
		return(1);
	}
#endif
	printf(" v%d u%d, R0x%x F0x%x A0x%x I0x%x\n",
	       (sp->c_vu>>4)&0xF, sp->c_vu&0xF,
	       sp->c_ref, sp->c_fef, sp->c_aef, sp->c_ief);
	printf("P1-P10: ");
	printf("%s", hexstr(*(u_int *)&sp->c_raw[0], 8));
	printf("%s", hexstr(*(u_int *)&sp->c_raw[4], 8));
	printf("%s\n", hexstr(*(u_short *)&sp->c_raw[8], 4));
	return(1);
}

D 9
rdread(dev, uio)
E 9
I 9
int
rdread(dev, uio, flags)
E 9
	dev_t dev;
	struct uio *uio;
I 9
	int flags;
E 9
{
D 18
	register int unit = rdunit(dev);
E 18

D 9
	return(physio(rdstrategy, &rdbuf[unit], dev, B_READ, minphys, uio));
E 9
I 9
	return (physio(rdstrategy, NULL, dev, B_READ, minphys, uio));
E 9
}

D 9
rdwrite(dev, uio)
E 9
I 9
int
rdwrite(dev, uio, flags)
E 9
	dev_t dev;
	struct uio *uio;
I 9
	int flags;
E 9
{
D 18
	register int unit = rdunit(dev);
E 18

D 9
	return(physio(rdstrategy, &rdbuf[unit], dev, B_WRITE, minphys, uio));
E 9
I 9
	return (physio(rdstrategy, NULL, dev, B_WRITE, minphys, uio));
E 9
}

D 9
/*ARGSUSED*/
rdioctl(dev, cmd, data, flag)
E 9
I 9
int
rdioctl(dev, cmd, data, flag, p)
E 9
	dev_t dev;
D 22
	int cmd;
E 22
I 22
	u_long cmd;
E 22
	caddr_t data;
	int flag;
I 9
	struct proc *p;
E 9
{
I 18
	int unit = rdunit(dev);
	register struct rd_softc *sc = &rd_softc[unit];
	register struct disklabel *lp = &sc->sc_info.ri_label;
	int error, flags;

	switch (cmd) {
	case DIOCGDINFO:
		*(struct disklabel *)data = *lp;
		return (0);

	case DIOCGPART:
		((struct partinfo *)data)->disklab = lp;
		((struct partinfo *)data)->part =
			&lp->d_partitions[rdpart(dev)];
		return (0);

        case DIOCWLABEL:
                if ((flag & FWRITE) == 0)
                        return (EBADF);
		if (*(int *)data)
			sc->sc_flags |= RDF_WLABEL;
		else
			sc->sc_flags &= ~RDF_WLABEL;
		return (0);

        case DIOCSDINFO:
                if ((flag & FWRITE) == 0)
                        return (EBADF);
		return (setdisklabel(lp, (struct disklabel *)data,
				     (sc->sc_flags & RDF_WLABEL) ? 0
				     : sc->sc_info.ri_open));

        case DIOCWDINFO:
		if ((flag & FWRITE) == 0)
			return (EBADF);
		error = setdisklabel(lp, (struct disklabel *)data,
				     (sc->sc_flags & RDF_WLABEL) ? 0
				     : sc->sc_info.ri_open);
		if (error)
			return (error);
		flags = sc->sc_flags;
		sc->sc_flags = RDF_ALIVE | RDF_WLABEL;
		error = writedisklabel(rdlabdev(dev), rdstrategy, lp);
		sc->sc_flags = flags;
		return (error);
	}
E 18
	return(EINVAL);
}

I 9
int
E 9
rdsize(dev)
	dev_t dev;
{
	register int unit = rdunit(dev);
	register struct rd_softc *rs = &rd_softc[unit];
I 18
	int psize, didopen = 0;
E 18

	if (unit >= NRD || (rs->sc_flags & RDF_ALIVE) == 0)
		return(-1);
D 18
	return(rs->sc_info->sizes[rdpart(dev)].nblocks);
E 18
I 18

	/*
	 * We get called very early on (via swapconf)
	 * without the device being open so we may need
	 * to handle it here.
	 */
	if (rs->sc_info.ri_open == 0) {
		if (rdopen(dev, FREAD|FWRITE, S_IFBLK, NULL))
			return(-1);
		didopen = 1;
	}
	psize = rs->sc_info.ri_label.d_partitions[rdpart(dev)].p_size;
	if (didopen)
		(void) rdclose(dev, FREAD|FWRITE, S_IFBLK, NULL);
	return (psize);
E 18
}

#ifdef DEBUG
rdprinterr(str, err, tab)
	char *str;
	short err;
	char *tab[];
{
	register int i;
	int printed;

	if (err == 0)
		return;
	printf("    %s error field:", str, err);
	printed = 0;
	for (i = 0; i < 16; i++)
		if (err & (0x8000 >> i))
			printf("%s%s", printed++ ? " + " : " ", tab[i]);
	printf("\n");
}
#endif

D 4
#include "machine/pte.h"
#include "machine/vmparam.h"
D 2
#include "../h/vmmac.h"
E 2
I 2
#include "../sys/vmmac.h"
E 2

E 4
/*
 * Non-interrupt driven, non-dma dump routine.
 */
I 9
int
E 9
rddump(dev)
	dev_t dev;
{
	int part = rdpart(dev);
	int unit = rdunit(dev);
	register struct rd_softc *rs = &rd_softc[unit];
	register struct hp_device *hp = rs->sc_hd;
I 18
	register struct partition *pinfo;
E 18
	register daddr_t baddr;
D 4
	register int maddr;
	register int pages, i;
E 4
I 4
	register int maddr, pages, i;
E 4
	char stat;
	extern int lowram, dumpsize;
I 4
#ifdef DEBUG
	extern int pmapdebug;
	pmapdebug = 0;
#endif
E 4

D 18
	pages = dumpsize;
#ifdef DEBUG
	if (rddebug & RDB_DUMP)
		printf("rddump(%x): u %d p %d dumplo %d ram %x pmem %d\n",
		       dev, unit, part, dumplo, lowram, ctod(pages));
#endif
E 18
	/* is drive ok? */
	if (unit >= NRD || (rs->sc_flags & RDF_ALIVE) == 0)
		return (ENXIO);
I 18
	pinfo = &rs->sc_info.ri_label.d_partitions[part];
	/* dump parameters in range? */
	if (dumplo < 0 || dumplo >= pinfo->p_size ||
	    pinfo->p_fstype != FS_SWAP)
		return (EINVAL);
	pages = dumpsize;
	if (dumplo + ctod(pages) > pinfo->p_size)
		pages = dtoc(pinfo->p_size - dumplo);
	maddr = lowram;
	baddr = dumplo + pinfo->p_offset;
E 18
	/* HPIB idle? */
	if (!hpibreq(&rs->sc_dq)) {
D 18
#ifdef DEBUG
		/* is this a safe thing to do?? */
E 18
		hpibreset(hp->hp_ctlr);
		rdreset(rs, rs->sc_hd);
		printf("[ drive %d reset ] ", unit);
D 18
#else
		return (EFAULT);
#endif
E 18
	}
D 18
	/* dump parameters in range? */
	if (dumplo < 0 || dumplo >= rs->sc_info->sizes[part].nblocks)
		return (EINVAL);
	if (dumplo + ctod(pages) > rs->sc_info->sizes[part].nblocks)
		pages = dtoc(rs->sc_info->sizes[part].nblocks - dumplo);
	maddr = lowram;
	baddr = dumplo + rs->sc_info->nbpc * rs->sc_info->sizes[part].cyloff;
#ifdef DEBUG
	if (rddebug & RDB_DUMP)
		printf("rddump: dumping %d pages from %x to disk block %d\n",
		       pages, maddr, baddr);
#endif
E 18
	for (i = 0; i < pages; i++) {
D 18
#ifdef DEBUG
E 18
#define NPGMB	(1024*1024/NBPG)
		/* print out how many Mbs we have dumped */
		if (i && (i % NPGMB) == 0)
			printf("%d ", i / NPGMB);
#undef NPBMG
D 18
#endif
E 18
		rs->sc_ioc.c_unit = C_SUNIT(rs->sc_punit);
		rs->sc_ioc.c_volume = C_SVOL(0);
		rs->sc_ioc.c_saddr = C_SADDR;
		rs->sc_ioc.c_hiaddr = 0;
		rs->sc_ioc.c_addr = RDBTOS(baddr);
		rs->sc_ioc.c_nop2 = C_NOP;
		rs->sc_ioc.c_slen = C_SLEN;
		rs->sc_ioc.c_len = NBPG;
		rs->sc_ioc.c_cmd = C_WRITE;
		hpibsend(hp->hp_ctlr, hp->hp_slave, C_CMD,
			 &rs->sc_ioc.c_unit, sizeof(rs->sc_ioc)-2);
D 18
		if (hpibswait(hp->hp_ctlr, hp->hp_slave)) {
#ifdef DEBUG
			if (rddebug & RDB_DUMP)
				printf("rddump: IOC wait timeout\n");
#endif
E 18
I 18
		if (hpibswait(hp->hp_ctlr, hp->hp_slave))
E 18
			return (EIO);
D 18
		}
E 18
D 4
		mapin(mmap, (u_int)vmmap, btop(maddr), PG_URKR|PG_CI|PG_V);
E 4
I 4
D 12
		pmap_enter(pmap_kernel(), vmmap, maddr, VM_PROT_READ, TRUE);
E 12
I 12
D 13
		pmap_enter(pmap_kernel(), (vm_offset_t)vmmap, maddr,
E 13
I 13
		pmap_enter(kernel_pmap, (vm_offset_t)vmmap, maddr,
E 13
		    VM_PROT_READ, TRUE);
E 12
E 4
		hpibsend(hp->hp_ctlr, hp->hp_slave, C_EXEC, vmmap, NBPG);
D 18
		if (hpibswait(hp->hp_ctlr, hp->hp_slave)) {
#ifdef DEBUG
			if (rddebug & RDB_DUMP)
				printf("rddump: write wait timeout\n");
#endif
		}
E 18
I 18
		(void) hpibswait(hp->hp_ctlr, hp->hp_slave);
E 18
		hpibrecv(hp->hp_ctlr, hp->hp_slave, C_QSTAT, &stat, 1);
D 18
		if (stat) {
#ifdef DEBUG
			if (rddebug & RDB_DUMP)
				printf("rddump: write failed, status %x\n",
				       stat);
#endif
E 18
I 18
		if (stat)
E 18
			return (EIO);
D 18
		}
E 18
		maddr += NBPG;
		baddr += ctod(1);
	}
	return (0);
}
#endif
E 1
