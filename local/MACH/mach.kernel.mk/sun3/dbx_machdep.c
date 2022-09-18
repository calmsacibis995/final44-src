/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	dbx_machdep.c,v $
 * Revision 2.3  89/03/09  21:32:33  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:33:41  gm0w
 * 	Changes for cleanup.
 * 
 */
#ifndef	lint
static	char sccsid[] = "@(#)dbx_machdep.c 1.1 86/02/03 Copyr 1985 Sun Micro";
#endif

/*
 * This file is optionally brought in by including a
 * "psuedo-device dbx" line in the config file.  It is
 * compiled using the "-g" flag to generate structure
 * information which is used by dbx with the -k flag.
 */

#include <sys/param.h>

#include <sun3/buserr.h>
#include <sun3/clock.h>
#include <sun3/eccreg.h>
#include <sun3/mmu.h>
#include <sun3/cpu.h>
#include <sun3/frame.h>
#include <sun3/memerr.h>
