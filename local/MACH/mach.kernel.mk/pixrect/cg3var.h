/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	cg3var.h,v $
 * Revision 2.2  90/12/17  17:11:12  berman
 * 	Created from SunOS 4.0.3c for SPARCstation I port.
 * 	[90/10/01            berman]
 * 
 *
 */
/* @(#)cg3var.h 1.1 89/02/22 SMI */

/*
 * Copyright 1989 by Sun Microsystems, Inc.
 */

#ifndef	cg3var_DEFINED
#define	cg3var_DEFINED

/*
 * cg3 -- color memory frame buffer
 */

/*
 * On architectures where cg4s have been implemented we need a nice big
 * mmap offset to avoid the cg4 compatible simulated overlay/enable planes.
 * On e.g. the 386i might as well start at zero.
 */
#if defined(mc68000) || defined(sparc)
#define	CG3_MMAP_OFFSET	0x04000000	/* 8K x 8K */
#else
#define	CG3_MMAP_OFFSET	0
#endif

/*
 * In the kernel we just use a memory pixrect so we don't
 * need any of this stuff.
 */
#ifndef KERNEL
#include <pixrect/memvar.h>

/* pixrect private data */
struct cg3_data {
	struct mprp_data mprp;		/* memory pixrect simulator */
	int fd;				/* file descriptor */
};

#define	cg3_d(pr)	((struct cg3_data *) (pr)->pr_data)

/* pixrect ops vector */
extern struct pixrectops cg3_ops;

Pixrect	*cg3_make();
int cg3_destroy();
Pixrect *cg3_region();
int cg3_putcolormap();
int cg3_getcolormap();
#endif !KERNEL

#endif	!cg3var_DEFINED
