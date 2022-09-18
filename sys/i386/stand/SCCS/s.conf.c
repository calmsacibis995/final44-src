h40096
s 00005/00000/00030
d D 8.2 94/01/21 17:08:14 bostic 6 5
c add USL's copyright notice
e
s 00002/00002/00028
d D 8.1 93/06/11 15:57:49 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00027
d D 7.4 92/10/11 10:22:56 bostic 4 3
c make kernel includes standard
e
s 00011/00090/00018
d D 7.3 91/05/04 15:28:19 bostic 3 2
c use standard device routines in stand/dev.c
e
s 00026/00014/00082
d D 7.2 91/04/28 17:00:37 william 2 1
c modified for common sys.c
e
s 00096/00000/00000
d D 7.1 90/04/24 19:56:33 william 1 0
c date and time created 90/04/24 19:56:33 by william
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
I 6
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 6
E 5
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

I 2
D 3
#include "param.h"
E 3
I 3
D 4
#include "sys/param.h"
#include "stand/saio.h"
E 4
I 4
#include <sys/param.h>

#include <stand/saio.h>
E 4
E 3
E 2

D 2
/*#include "../machine/pte.h"*/

#include "../h/param.h"
#include "../h/inode.h"
#include "../h/fs.h"


E 2
D 3
#include "saio.h"
I 2
#ifdef BOOT
extern exception;
extern int debugflag;
#endif
E 3
I 3
extern int	nullsys(), nodev(), noioctl();
E 3
E 2

D 3
devread(io)
	register struct iob *io;
{
	int cc;
I 2
	char c;
E 3
I 3
int	wdstrategy(), wdopen();
#define	wdioctl	noioctl
E 3
E 2

D 3
	io->i_flgs |= F_RDDATA;
	io->i_error = 0;
D 2
	cc = (*devsw[major(io->i_ino.i_dev)].dv_strategy)(io, READ);
E 2
I 2
	cc = (*devsw[io->i_dev].dv_strategy)(io, READ);
E 2
	io->i_flgs &= ~F_TYPEMASK;
E 3
I 3
int	fdstrategy(), fdopen();
#define	fdioctl noioctl
E 3
I 2

D 3
#ifdef BOOT
if(/*io->i_error || */(c=scankbd()))
	_longjmp(&exception,1);
#endif
E 2
	return (cc);
}

devwrite(io)
	register struct iob *io;
{
	int cc;
I 2
	char c;
E 2

	io->i_flgs |= F_WRDATA;
	io->i_error = 0;
D 2
	cc = (*devsw[major(io->i_ino.i_dev)].dv_strategy)(io, WRITE);
E 2
I 2
	cc = (*devsw[io->i_dev].dv_strategy)(io, WRITE);
E 2
	io->i_flgs &= ~F_TYPEMASK;
I 2
#ifdef BOOT
if(/* io->i_error || */ (c=scankbd()))
	_longjmp(&exception,1);
#endif
E 2
	return (cc);
}

devopen(io)
	register struct iob *io;
{

D 2
	(*devsw[major(io->i_ino.i_dev)].dv_open)(io);
E 2
I 2
	(*devsw[io->i_dev].dv_open)(io);
E 2
}

devclose(io)
	register struct iob *io;
{

D 2
	(*devsw[major(io->i_ino.i_dev)].dv_close)(io);
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
	return ((*devsw[major(io->i_ino.i_dev)].dv_ioctl)(io, cmd, arg));
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
int	wdstrategy(), wdopen()/*, wdioctl()*/;
I 2
int	fdstrategy(), fdopen()/*, fdioctl()*/;
E 2

E 3
struct devsw devsw[] = {
D 3
	/*{ "xx",	xxstrategy,	xxopen,		nullsys, nullioctl },*/
	{ "wd",	wdstrategy,	wdopen,		nullsys,/*wdioctl*/ nullioctl },
I 2
	{ "", 0, 0, 0, 0 }, /* swapdev place holder */
	{ "fd",	fdstrategy,	fdopen,		nullsys,/*fdioctl*/ nullioctl },
E 2
	{ 0, 0, 0, 0, 0 },
E 3
I 3
	{ "wd",	wdstrategy,	wdopen,	nullsys, wdioctl },	/* 0 = wd */
	{ NULL },				/* swapdev place holder */
	{ "fd",	fdstrategy,	fdopen,	nullsys, fdioctl },	/* 2 = fd */
E 3
};
D 2
int ndevs = 2 ;
E 2
I 2
D 3
int ndevs = 3 ;
E 3
I 3
int	ndevs = (sizeof(devsw)/sizeof(devsw[0]));
E 3
E 2
E 1
