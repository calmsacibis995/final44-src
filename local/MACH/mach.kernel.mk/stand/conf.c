/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 *
 */

/*
 **********************************************************************
 * HISTORY
 * $Log:	conf.c,v $
 * Revision 2.4  89/03/09  21:13:53  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/26  14:19:14  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  88/08/08  13:42:50  rvb
 * Include all machine support in device switch.
 * 
 **********************************************************************
 */

#ifdef	notdef
#include "cputypes.h"
#endif	notdef
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)conf.c	7.1 (Berkeley) 6/5/86
 */

#include <machine/pte.h>

#include <sys/param.h>
#include <sys/inode.h>
#include <sys/fs.h>

#include <vaxmba/mbareg.h>

#include "saio.h"

devread(io)
	register struct iob *io;
{
	int cc;

	io->i_flgs |= F_RDDATA;
	io->i_error = 0;
	cc = (*devsw[io->i_ino.i_dev].dv_strategy)(io, READ);
	io->i_flgs &= ~F_TYPEMASK;
	return (cc);
}

devwrite(io)
	register struct iob *io;
{
	int cc;

	io->i_flgs |= F_WRDATA;
	io->i_error = 0;
	cc = (*devsw[io->i_ino.i_dev].dv_strategy)(io, WRITE);
	io->i_flgs &= ~F_TYPEMASK;
	return (cc);
}

devopen(io)
	register struct iob *io;
{

	(*devsw[io->i_ino.i_dev].dv_open)(io);
}

devclose(io)
	register struct iob *io;
{

	(*devsw[io->i_ino.i_dev].dv_close)(io);
}

devioctl(io, cmd, arg)
	register struct iob *io;
	int cmd;
	caddr_t arg;
{

	return ((*devsw[io->i_ino.i_dev].dv_ioctl)(io, cmd, arg));
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
int	hpstrategy(), hpopen(), hpioctl();
int	upstrategy(), upopen(), upioctl();
int	rkstrategy(), rkopen(), rkioctl();
int	rastrategy(), raopen(), raioctl();
int	idcstrategy(), idcopen(), idcioctl();
int	rlstrategy(), rlopen(), rlioctl();
#ifndef	BOOT
int	tmstrategy(), tmopen(), tmclose();
int	tsstrategy(), tsopen(), tsclose();
int	htstrategy(), htopen(), htclose();
int	mtstrategy(), mtopen(), mtclose();
int	utstrategy(), utopen(), utclose();
#endif

struct devsw devsw[] = {
	{ "hp",	hpstrategy,	hpopen,		nullsys,	hpioctl },
	{ "up",	upstrategy,	upopen,		nullsys,	upioctl },
	{ "hk",	rkstrategy,	rkopen,		nullsys,	rkioctl },
	{ "ra",	rastrategy,	raopen,		nullsys,	raioctl },
	{ "rb",	idcstrategy,	idcopen,	nullsys,	idcioctl },
	{ "rl",	rlstrategy,	rlopen,		nullsys,	rlioctl },
#ifndef	BOOT
	{ "ts",	tsstrategy,	tsopen,		tsclose,	nullioctl },
	{ "ht",	htstrategy,	htopen,		htclose,	nullioctl },
	{ "mt",	mtstrategy,	mtopen,		mtclose,	nullioctl },
	{ "tm",	tmstrategy,	tmopen,		tmclose,	nullioctl },
	{ "ut",	utstrategy,	utopen,		utclose,	nullioctl },
#endif
	{ 0, 0, 0, 0, 0 },
};
