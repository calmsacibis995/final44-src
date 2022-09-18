h55036
s 00002/00002/00136
d D 8.1 93/06/10 22:29:06 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00138/00000/00000
d D 7.1 92/12/13 03:50:09 akito 1 0
c date and time created 92/12/13 03:50:09 by akito
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
 *	%W% (Berkeley) %G%
 */

#include <luna68k/stand/saio.h>

devread(io)
	register struct iob *io;
{
	int cc;

	io->i_flgs |= F_RDDATA;
	io->i_error = 0;
	cc = (*devsw[io->i_dev].dv_strategy)(io, READ);
	io->i_flgs &= ~F_TYPEMASK;
	return (cc);
}

devwrite(io)
	register struct iob *io;
{
	int cc;

	io->i_flgs |= F_WRDATA;
	io->i_error = 0;
	cc = (*devsw[io->i_dev].dv_strategy)(io, WRITE);
	io->i_flgs &= ~F_TYPEMASK;
	return (cc);
}

devopen(io)
	register struct iob *io;
{

	(*devsw[io->i_dev].dv_open)(io);
}

devclose(io)
	register struct iob *io;
{

	(*devsw[io->i_dev].dv_close)(io);
}

devioctl(io, cmd, arg)
	register struct iob *io;
	int cmd;
	caddr_t arg;
{

	return ((*devsw[io->i_dev].dv_ioctl)(io, cmd, arg));
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
int	sdstrategy(), sdopen(), sdioctl();

struct devsw devsw[] = {
	{ "sd",	sdstrategy,	sdopen,		nullsys,	nullioctl },
	{ 0, 0, 0, 0, 0 },
};

dev_t
make_device(str)
	char *str;
{
	char *cp;
	struct devsw *dp;
	int major, unit, part;

	/*
	 * parse path strings
	 */
							/* find end of dev type name */
	for (cp = str; *cp && *cp != '('; cp++)
			;
	if (*cp != '(') {
		return (-1);
	}
							/* compare dev type name */
	*cp = '\0';
	for (dp = devsw; dp->dv_name; dp++)
		if (!strcmp(str, dp->dv_name))
			break;
	*cp++ = '(';
	if (dp->dv_name == NULL) {
		return (-1);
	}
	major = dp - devsw;
							/* get unit number */
	unit = *cp++ - '0';
	if (*cp >= '0' && *cp <= '9')
		unit = unit * 10 + *cp++ - '0';
	if (unit < 0 || unit > 63) {
		return (-1);
	}
							/* get partition offset */
	if (*cp++ != ',') {
		return (-1);
	}
	part = *cp - '0';
							/* check out end of dev spec */
	for (;;) {
		if (*cp == ')')
			break;
		if (*cp++)
			continue;
		return (-1);
	}

	return(major << 8 | unit << 3 | part);
}
E 1
