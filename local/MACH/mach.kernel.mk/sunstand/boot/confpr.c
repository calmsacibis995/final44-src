/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	confpr.c,v $
 * Revision 2.2  89/07/12  00:10:30  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
#ifndef lint
static	char sccsid[] = "@(#)confpr.c	1.3 88/02/08	Copyr 1985 Sun Micro";
#endif

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

/*
 * Device configuration table and interface for standalone I/O system.
 *
 * This version contains no drivers; it uses the boottab in the PROMs.
 */

#include "../lib/stand/saio.h"

/* Dummy device table to satisfy external references */
struct boottab *(devsw[]) = {(struct boottab *)0, };
