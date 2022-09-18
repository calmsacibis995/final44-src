h43035
s 00002/00002/00043
d D 8.1 93/06/11 14:59:28 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00045/00000/00000
d D 7.1 92/06/04 16:03:41 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
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
 * Sony Corp. and Kazumasa Utashiro of Software Research Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 * from: $Hdr: ioptohb.h,v 4.300 91/06/09 06:38:04 root Rel41 $ SONY
 *
 *	%W% (Berkeley) %G%
 */

#ifndef __IOPTOHB__
#define __IOPTOHB__ 1

#ifdef CPU_SINGLE
# define	iop		hb

# define	im_driver	hm_driver
# define	im_ctlr		hm_ctlr
# define	im_alive	hm_alive
# define	im_addr		hm_addr
# define	im_intr		hm_intr
# define	im_scnum	hm_scnum
# define	im_hd		hm_hd
# define	im_tab		hm_tab

# define	ii_driver	hi_driver
# define	ii_unit		hi_unit
# define	ii_ctlr		hi_ctlr
# define	ii_slave	hi_slave
# define	ii_addr		hi_addr
# define	ii_intr		hi_intr
# define	ii_dk		hi_dk
# define	ii_flags	hi_flags
# define	ii_alive	hi_alive
# define	ii_type		hi_type
# define	ii_forw		hi_forw
# define	ii_mi		hi_mi
# define	ii_hd		hi_hd
#endif /* CPU_SINGLE */

#endif /* !__IOPTOHB__ */
E 1
