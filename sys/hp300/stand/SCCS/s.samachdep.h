h63456
s 00002/00002/00045
d D 8.1 93/06/10 21:47:42 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00046
d D 7.4 92/12/26 16:49:48 hibler 4 3
c Utah update (mostly disklabels)
e
s 00014/00005/00032
d D 7.3 92/06/18 21:33:16 hibler 3 2
c merge with latest Utah version
e
s 00014/00001/00023
d D 7.2 91/05/07 10:05:41 hibler 2 1
c DIO-II support
e
s 00024/00000/00000
d D 7.1 90/05/08 22:45:57 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#define	NHPIB		4
D 3
#define NITE		4
E 3
#define	NSCSI		2
D 3
#define NRD		(NHPIB * 8)
#define NCT		(NHPIB * 8)
#define NSD		(NSCSI * 8)
E 3
I 3
#define NRD		8
#define NCT		8
#define NSD		8
E 3

I 3
#define NITE		4

E 3
D 2
#define IOV(x)		(x)
E 2
I 2
/* from cpu.h */
#define IIOV(x)		(x)
#define DIOBASE		(0x600000)
#define	DIOCSIZE	(0x10000)
#define DIOIIBASE	(0x01000000)
#define DIOIICSIZE	(0x00400000)

#define HP_320		0	/* 16Mhz 68020+HP MMU+16K external cache */
#define HP_330		1	/* 16Mhz 68020+68851 MMU */
#define HP_350		2	/* 25Mhz 68020+HP MMU+32K external cache */
#define HP_360		3	/* 25Mhz 68030 */
#define HP_370		4	/* 33Mhz 68030+64K external cache */
#define HP_340		5	/* 16Mhz 68030 */
#define HP_375		6	/* 50Mhz 68030+32K external cache */
I 3
#define HP_380		7	/* 25Mhz 68040 */
I 4
#define HP_433		8	/* 33Mhz 68040 */
E 4
E 3
E 2

D 3
extern	int howto, devtype;
E 3
I 3
#define MHZ_8		1
#define MHZ_16		2
#define MHZ_25		3
#define MHZ_33		4
#define MHZ_50		6

extern	int cpuspeed, machineid;
extern	int howto, bootdev;
E 3

/* bogon grfinfo structure to keep grf_softc happy */
struct grfinfo {
	int	grf_foo;
};
E 1
