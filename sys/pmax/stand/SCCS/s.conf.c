h41617
s 00002/00002/00034
d D 8.1 93/06/10 23:31:14 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00012/00030
d D 7.5 93/02/15 11:22:40 ralph 5 4
c use old DS3100 style entry point for SCSI disk I/O
e
s 00026/00018/00016
d D 7.4 92/10/24 14:36:23 ralph 4 3
c new libsa version
e
s 00002/00002/00032
d D 7.3 92/10/11 11:28:16 bostic 3 2
c make kernel includes standard
e
s 00000/00006/00034
d D 7.2 92/03/07 09:58:37 ralph 2 1
c fixes for ds5000
e
s 00040/00000/00000
d D 7.1 92/01/07 20:45:19 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 3
#include "saio.h"
#include "../include/machMon.h"
E 3
I 3
D 4
#include <pmax/stand/saio.h>
#include <machine/machMon.h>
E 4
I 4
#include <stand/stand.h>
D 5
#include <pmax/stand/samachdep.h>
E 5
E 4
E 3

I 5
const	struct callback *callv;
int	errno;

E 5
D 4
devread(io)
	register struct iob *io;
{
E 4
I 4
extern int	nullsys(), nodev(), noioctl();
E 4

D 4
	if (lseek(io->i_unit, (io->i_bn + io->i_boff) * DEV_BSIZE, 0) < 0)
		return (-1);
	return (read(io->i_unit, io->i_ma, io->i_cc));
}
E 4
I 4
D 5
#if NRZ > 0
E 5
int	rzstrategy(), rzopen(), rzclose();
D 5
#else
#define	rzstrategy	nodev
#define	rzopen		nodev
#define	rzclose		nodev
#endif
E 5
#define	rzioctl		noioctl
E 4

D 4
#ifndef SMALL
devwrite(io)
	register struct iob *io;
{

	if (lseek(io->i_unit, (io->i_bn + io->i_boff) * DEV_BSIZE, 0) < 0)
		return (-1);
	return (write(io->i_unit, io->i_ma, io->i_cc));
}
E 4
I 4
D 5
#if NTZ > 0 && !defined(BOOT)
E 5
I 5
#ifndef BOOT
E 5
int	tzstrategy(), tzopen(), tzclose();
D 5
#else
#define	tzstrategy	nodev
#define	tzopen		nodev
#define	tzclose		nodev
E 5
E 4
#endif
I 4
#define	tzioctl		noioctl


struct devsw devsw[] = {
	{ "rz",	rzstrategy,	rzopen,	rzclose,	rzioctl }, /*0*/
I 5
#ifndef BOOT
E 5
	{ "tz",	tzstrategy,	tzopen,	tzclose,	tzioctl }, /*1*/
I 5
#endif
E 5
};

int	ndevs = (sizeof(devsw)/sizeof(devsw[0]));
E 4
D 2

struct devsw devsw[] = {
	"rz",
	"tz",
	0,
};
E 2
E 1
