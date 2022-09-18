h37708
s 00002/00002/00050
d D 8.1 93/06/10 21:46:31 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00051
d D 7.6 93/05/24 22:50:04 mckusick 6 5
c fix include directives
e
s 00002/00002/00050
d D 7.5 92/10/11 10:01:34 bostic 5 4
c make kernel includes standard
e
s 00025/00009/00027
d D 7.4 92/06/18 21:33:38 hibler 4 3
c merge with latest Utah version
e
s 00016/00074/00020
d D 7.3 91/05/05 13:43:27 bostic 3 2
c use common device routines
e
s 00005/00005/00089
d D 7.2 90/07/01 00:32:09 karels 2 1
c updates to use dinodes directly, etc
e
s 00094/00000/00000
d D 7.1 90/05/08 22:46:00 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 3
D 4
#include <sys/param.h>
E 4
I 4
D 5
#include "sys/param.h"
E 4
E 3
#include "saio.h"
E 5
I 5
#include <sys/param.h>
D 6
#include <stand/saio.h>
E 6
I 6
#include <stand.att/saio.h>
E 6
E 5

D 3
devread(io)
	register struct iob *io;
{
	int cc;
E 3
I 3
extern int	nullsys(), nodev(), noioctl();
E 3

D 3
	/* check for interrupt */
	(void) peekchar();

	io->i_flgs |= F_RDDATA;
	io->i_error = 0;
D 2
	cc = (*devsw[io->i_ino.i_dev].dv_strategy)(io, READ);
E 2
I 2
	cc = (*devsw[io->i_dev].dv_strategy)(io, READ);
E 2
	io->i_flgs &= ~F_TYPEMASK;
	return (cc);
}

devwrite(io)
	register struct iob *io;
{
	int cc;

	io->i_flgs |= F_WRDATA;
	io->i_error = 0;
D 2
	cc = (*devsw[io->i_ino.i_dev].dv_strategy)(io, WRITE);
E 2
I 2
	cc = (*devsw[io->i_dev].dv_strategy)(io, WRITE);
E 2
	io->i_flgs &= ~F_TYPEMASK;
	return (cc);
}

devopen(io)
	register struct iob *io;
{

D 2
	(*devsw[io->i_ino.i_dev].dv_open)(io);
E 2
I 2
	(*devsw[io->i_dev].dv_open)(io);
E 2
}

devclose(io)
	register struct iob *io;
{

D 2
	(*devsw[io->i_ino.i_dev].dv_close)(io);
E 2
I 2
	(*devsw[io->i_dev].dv_close)(io);
E 2
}

devioctl(io, cmd, arg)
	register struct iob *io;
	int cmd;
	caddr_t arg;
{

D 2
	return ((*devsw[io->i_ino.i_dev].dv_ioctl)(io, cmd, arg));
E 2
I 2
	return ((*devsw[io->i_dev].dv_ioctl)(io, cmd, arg));
E 2
}

/*ARGSUSED*/
nullsys(io)
	struct iob *io;
{

	;
}

/*ARGSUSED*/
nullioctl(io, cmd, arg)
	struct iob *io;
	int cmd;
	caddr_t arg;
{

	return (ECMD);
}

int	nullsys(), nullioctl();
int	rdstrategy(), rdopen(), rdioctl();
int	sdstrategy(), sdopen(), sdioctl();
E 3
D 4
#ifndef BOOT
E 4
I 4
#ifdef BOOT
#define	ctstrategy	nullsys
#define	ctopen		nodev
#define	ctclose		nullsys
#else
E 4
int	ctstrategy(), ctopen(), ctclose();
I 3
D 4
#define	ctioctl	noioctl
E 4
E 3
#endif
I 4
#define	ctioctl	noioctl
E 4

I 3
int	rdstrategy(), rdopen();
#define	rdioctl	noioctl

int	sdstrategy(), sdopen();
#define	sdioctl	noioctl


E 3
struct devsw devsw[] = {
D 3
	{ "rd",	rdstrategy,	rdopen,		nullsys,	nullioctl },
	{ "sd",	sdstrategy,	sdopen,		nullsys,	nullioctl },
E 3
I 3
D 4
	{ "rd",	rdstrategy,	rdopen,	nullsys, noioctl },	/* 0 = rd */
	{ "sd",	sdstrategy,	sdopen,	nullsys, noioctl },	/* 1 = sd */
E 3
#ifndef BOOT
D 3
	{ "ct",	ctstrategy,	ctopen,		ctclose,	nullioctl },
E 3
I 3
	{ "ct",	ctstrategy,	ctopen,	ctclose, noioctl },	/* 2 = ct */
E 3
#endif
D 3
	{ 0, 0, 0, 0, 0 },
E 3
I 3
	{ NULL },
E 4
I 4
	{ "ct",	ctstrategy,	ctopen,	ctclose,	ctioctl }, /*0*/
	{ "??",	nullsys,	nodev,	nullsys,	noioctl }, /*1*/
	{ "rd",	rdstrategy,	rdopen,	nullsys,	rdioctl }, /*2*/
	{ "??",	nullsys,	nodev,	nullsys,	noioctl }, /*3*/
	{ "sd",	sdstrategy,	sdopen,	nullsys,	sdioctl }, /*4*/
E 4
E 3
};
I 3

int	ndevs = (sizeof(devsw)/sizeof(devsw[0]));
I 4

/*
 * Convert old style unit syntax into adaptor/controller/unit
 */
devconvert(io)
	register struct iob *io;
{
	if (io->i_unit == 0 || io->i_adapt || io->i_ctlr)
		return;
	io->i_adapt = io->i_unit / 8;
	io->i_ctlr = io->i_unit % 8;
	io->i_unit = 0;
}
E 4
E 3
E 1
