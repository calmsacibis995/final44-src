h11237
s 00002/00002/00050
d D 8.1 93/06/10 21:31:49 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00049
d D 7.2 92/10/11 09:23:38 bostic 2 1
c make kernel includes standard
e
s 00051/00000/00000
d D 7.1 92/06/05 15:33:06 hibler 1 0
c merge latest Utah hp300 code including 68040 support
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 3
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: cons_conf.c 1.1 92/01/21
 *
 *	%W% (Berkeley) %G%
 */

/*
 * This entire table could be autoconfig()ed but that would mean that
 * the kernel's idea of the console would be out of sync with that of
 * the standalone boot.  I think it best that they both use the same
 * known algorithm unless we see a pressing need otherwise.
 */
D 2
#include "sys/types.h"
#include "hp/dev/cons.h"
E 2
I 2
#include <sys/types.h>

#include <hp/dev/cons.h>
E 2

#include "ite.h"
#include "dca.h"
#include "dcm.h"

#if NITE > 0
extern int itecnprobe(), itecninit(), itecngetc(), itecnputc();
#endif
#if NDCA > 0
extern	int dcacnprobe(), dcacninit(), dcacngetc(), dcacnputc();
#endif
#if NDCM > 0
extern	int dcmcnprobe(), dcmcninit(), dcmcngetc(), dcmcnputc();
#endif

struct	consdev constab[] = {
#if NITE > 0
	{ itecnprobe,	itecninit,	itecngetc,	itecnputc },
#endif
#if NDCA > 0
	{ dcacnprobe,	dcacninit,	dcacngetc,	dcacnputc },
#endif
#if NDCM > 0
	{ dcmcnprobe,	dcmcninit,	dcmcngetc,	dcmcnputc },
#endif
	{ 0 },
};
E 1
