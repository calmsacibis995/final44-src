h42786
s 00002/00002/00045
d D 8.1 93/06/11 14:59:41 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00004/00047
d D 7.2 92/12/17 03:08:22 utashiro 2 1
c make kernel includes standard
e
s 00051/00000/00000
d D 7.1 92/06/04 16:03:43 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Sony Corp. and Kazumasa Utashiro of Software Research Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 * from: $Hdr: scu.h,v 4.300 91/07/02 16:38:38 root Rel41 $ SONY
 *
 *	%W% (Berkeley) %G%
 */

/*
 * screg.h
 */

#ifndef __SCU__
#define __SCU__ 1

D 2
#ifdef KERNEL
#include "ioctl.h"
#else
E 2
#include <sys/ioctl.h>
D 2
#endif
E 2

#define	RAWSCSI_USE_PIO		0
#define	RAWSCSI_USE_DMA		1

#define	SCSIIOCCMD		_IOWR('S', 0, struct sc_ureq)
#define	SCSIIOCGTIMEO		_IOR('S', 1, int)
#define	SCSIIOCSTIMEO		_IOW('S', 2, int)

/*
 *	scsi user request parameter block
 */
struct sc_ureq {
/*00*/	u_int	scu_istatus;
/*04*/	u_int	scu_tstatus;
/*08*/	u_int	scu_identify;
/*0c*/	u_int	scu_message;
/*10*/	u_int	scu_bytesec;
/*14*/	u_char	scu_cdb[12];
/*20*/	u_char	scu_param[20];
/*34*/	u_char	*scu_addr;
/*38*/	u_int	scu_count;
/*3c*/
};

#endif /* !__SCU__ */
E 1
