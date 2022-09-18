/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 **********************************************************************
 * HISTORY
 * $Log:	de.c,v $
 * Revision 2.3  89/03/09  21:14:12  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  14:20:35  gm0w
 * 	Changes for cleanup.
 * 
 **********************************************************************
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)uda.c	7.1 (Berkeley) 6/5/86
 */

/*
 * DEUNA ethernet device driver
 */
#include <machine/pte.h>

#include <sys/param.h>
#include <sys/inode.h>
#include <sys/fs.h>

#include "saio.h"
#include "savax.h"

#define NDE	1

#define NBI 1

#include <vaxuba/ubareg.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <vaxif/if_dereg.h>

u_short destd[] = { 0774510, 0760450, 0 };

char de_init[NDE] = {0};


struct dedevice *de_addr[NDE] = {0};

deopen(io)
	register struct iob *io;
{
	register int unit = UNITTODRIVE(io->i_unit);

	if (de_addr[unit] == 0)
		de_addr[unit] = (struct dedevice *)ubamem(io->i_unit,
			 destd[UNITTOCTLR(io->i_unit)]);
	if (de_init[unit] == 0)
	{
	}
}


destrategy(io, func)
	register struct iob *io;
{
	while (io->i_cc > 0)
	{
		rdprequest(io, func);
	}
}


dewrite(io, buf, l)
	register struct iob *io;
	struct de_buf *buf;
{
	register struct rdp *rdp = (struct rdp *)&buf->db_data[0];

	rdp->rdp_cksm = 0;
	rdp->rdp_cksm = cksm(rdp, l>>1);
}


deread(io, buf)
	register struct iob *io;
	struct de_buf *buf;
{
	register struct rdp *rdp = (struct rdp *)&buf->db_data[0];

	while (1)
	{
	}
}

/*ARGSUSED*/
deioctl(io, cmd, arg)
	struct iob *io;
	int cmd;
	caddr_t arg;
{

	return (ECMD);
}
