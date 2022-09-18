/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	pixrect_hs.h,v $
 * Revision 2.4  89/03/09  20:56:59  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:12:15  gm0w
 * 	Added new copyright and #ifndef <filename>_H_ around whole
 * 	file as part of kernel cleanup.
 * 	[89/02/13            jjc]
 * 
 */
/*	@(#)pixrect_hs.h 1.3 87/01/08 SMI	*/

/*
 * Copyright 1986 by Sun Microsystems, Inc.
 */

/*
 * Include this header file to get all pixrect related header files.
 */

#ifndef	PIXRECT_HS_H
#define PIXRECT_HS_H

#include <sys/types.h>
#include <pixrect/pixrect.h>
#include <pixrect/pr_dblbuf.h>
#include <pixrect/pr_line.h>
#include <pixrect/pr_planegroups.h>
#include <pixrect/pr_util.h>
#include <pixrect/traprop.h>

#include <pixrect/bw1var.h>
#include <pixrect/cg1var.h>
#include <pixrect/bw2var.h>
#include <pixrect/cg2var.h>
#include <pixrect/gp1var.h>
#include <pixrect/cg4var.h>
#include <pixrect/memvar.h>

#include <pixrect/pixfont.h>

#include <rasterfile.h>
#include <pixrect/pr_io.h>

#endif	PIXRECT_HS_H
