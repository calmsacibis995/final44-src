h41553
s 00002/00002/00044
d D 8.1 93/06/10 22:16:44 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00046/00000/00000
d D 7.1 92/06/15 06:45:50 fujita 1 0
c date and time created 92/06/15 06:45:50 by fujita
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
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
 * OMRON Corporation.
 *
 * %sccs.include.redist.c%
 *
 *
 *	%W% (Berkeley) %G%
 */

/*
 * OMRON: $Id: nvram.h,v 1.1 92/05/27 14:32:51 moti Exp $
 * by Shigeto Mochida
 */

/*
 * Non Volatile RAM
 */

#define	NVRAMSZ		2040	/* Size of NVRAM. (Total 2040 bytes) */
#define NVSYMSZ		16
#define NVVALSZ		16
#define NVSYSSZ		42
#define NVUSRSZ		512

/*
 * Battery back-up memory space.
 */
struct nvram {
	char	nv_testwrite[4];	/* for battery check */
	char	nv_hdr[4];		/* header name */
	long	nv_machtype;		/* machine-type ID */
	long	nv_machno;		/* machine number */
	char	nv_calclock[12];	/* RTC initialize */
	char	nv_checksum[4];		/* check sum for "nv_system" */
	struct nv_system {
		char	nv_symbol[NVSYMSZ];
		char	nv_value[NVVALSZ];
	} nv_system[NVSYSSZ];		/* system define */
	char	nv_reserve[152];	/* reserved */
	char	nv_user[NVUSRSZ];		/* user avail area */
};
E 1
