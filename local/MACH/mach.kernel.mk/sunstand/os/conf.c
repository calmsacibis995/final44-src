/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	conf.c,v $
 * Revision 2.2  89/07/12  01:11:06  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
#ifndef lint
static        char sccsid[] = "@(#)conf.c 1.7 88/02/08 Copyr 1986 Sun Micro";
#endif

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */

/*
 * Configuration table for standalone I/O system.
 *
 * This table lists all the supported drivers.  It is searched by open()
 * to parse the device specification.
 */

#include <stand/saio.h>

#ifdef	sun3
extern struct boottab ledriver;
#endif	/* sun3 */
extern struct boottab sddriver;
extern struct boottab iedriver;
extern struct boottab ecdriver;
extern struct boottab xydriver;

/*
 * The device table
 */
struct boottab *(devsw[]) = {
#ifdef	sun3
	&ledriver,
#endif	/* sun3 */
	&iedriver,
	&ecdriver,
	(struct boottab *)0,
};
