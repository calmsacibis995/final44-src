/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	confxx.c,v $
 * Revision 2.2  89/07/12  00:10:35  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*
 * @(#)confxx.c 1.3 88/02/08 Copyright (c) 1985 by Sun Microsystems, Inc.
 */

/*
 * Device configuration table and interface for standalone I/O system.
 *
 * This version contains exactly one driver; it is used in the boot block
 * (first 15 sectors after label) of disk drives.
 */

#include "../lib/stand/saio.h"

/*
 * Throughout this module, "xx" is replaced by the name
 * of the particular device being booted from.
 */
extern struct boottab xxdriver;

struct boottab *(devsw[]) = {
	&xxdriver,
	(struct boottab *)0,
};

