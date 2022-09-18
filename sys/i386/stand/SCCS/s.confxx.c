h09396
s 00005/00000/00019
d D 8.2 94/01/21 17:08:15 bostic 5 4
c add USL's copyright notice
e
s 00002/00002/00017
d D 8.1 93/06/11 15:57:53 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00072/00015
d D 7.3 91/05/04 15:28:56 bostic 3 2
c use standard device routines in stand/dev.c
e
s 00003/00013/00084
d D 7.2 91/04/28 17:03:24 william 2 1
c merge for common sys.c
e
s 00097/00000/00000
d D 7.1 90/04/24 19:56:37 william 1 0
c date and time created 90/04/24 19:56:37 by william
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
I 5
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 5
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 2
 * %sccs.include.noredist.c%
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
 */

D 2
#include "../machine/pte.h"

#include "../h/param.h"
#include "../h/inode.h"
#include "../h/fs.h"
E 2
I 2
D 3
#include "param.h"
E 2
#include "saio.h"
E 3
I 3
int	xxstrategy(), xxopen(), xxioctl();
E 3

D 3
devread(io)
	register struct iob *io;
{
	int cc;

	io->i_flgs |= F_RDDATA;
	io->i_error = 0;
	cc = (*devsw[0].dv_strategy)(io, READ);
	io->i_flgs &= ~F_TYPEMASK;
	return (cc);
}

devwrite(io)
	register struct iob *io;
{
	int cc;

	io->i_flgs |= F_WRDATA;
	io->i_error = 0;
	cc = (*devsw[0].dv_strategy)(io, WRITE);
	io->i_flgs &= ~F_TYPEMASK;
	return (cc);
}

devopen(io)
	register struct iob *io;
{

	(*devsw[0].dv_open)(io);
}

devclose(io)
	register struct iob *io;
{

	(*devsw[0].dv_close)(io);
}

devioctl(io, cmd, arg)
	register struct iob *io;
	int cmd;
	caddr_t arg;
{

	return ((*devsw[0].dv_ioctl)(io, cmd, arg));
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
int	xxstrategy(), xxopen()/*, xxioctl()*/;

E 3
struct devsw devsw[] = {
D 2
	{ "XX",	xxstrategy,	xxopen,		nullsys,	/*xxioctl*/ },
	{ 0, 0, 0, 0, 0 }
E 2
I 2
D 3
	{ "XX",	xxstrategy,	xxopen,		nullsys,	/*xxioctl*/ }
E 3
I 3
	{ "XX",	xxstrategy,	xxopen,		nullsys,	noioctl },
E 3
E 2
};
D 2
#ifdef	TP
char	bootprog[] = "XX0b:" ;
#else
char	bootprog[] = "XX0a:/boot" ;
#endif
E 2
D 3
int ndevs = 1 ;
E 3
I 3

int	ndevs = (sizeof(devsw) / sizeof(devsw[0]));
E 3
E 1
