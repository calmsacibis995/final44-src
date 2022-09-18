/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	zs_proto.c,v $
 * Revision 2.3  89/03/09  21:50:44  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  20:00:39  gm0w
 * 	Changes for cleanup.
 * 
 */
#ifndef	lint
static	char sccsid[] = "@(#)zs_proto.c 1.1 86/02/03 Copyr 1984 Sun Micro";
#endif

/*
 * Copyright (c) 1984 by Sun Microsystems, Inc.
 */

#include <zs.h>
#if	NZS > 0
#include <sys/types.h>
#include <sundev/zscom.h>

extern struct zsops zsops_null;
extern struct zsops zsops_async;

struct zsops *zs_proto[] = {
	&zsops_null,			/* must be first */
	&zsops_async,
	/* new entries go here */
	0,				/* must be last */
};
#endif
