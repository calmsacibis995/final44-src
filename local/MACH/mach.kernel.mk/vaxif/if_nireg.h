/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	if_nireg.h,v $
 * Revision 2.2  89/02/26  10:54:46  gm0w
 * 	Updated copyright.
 * 	[89/02/23            gm0w]
 * 
 */
/*	@(#)nireg.h	1.2	ULTRIX	5/2/86	*/ 
/************************************************************************
 *									*
 *			Copyright (c) 1986 by				*
 *		Digital Equipment Corporation, Maynard, MA		*
 *			All rights reserved.				*
 *									*
 *   This software is furnished under a license and may be used and	*
 *   copied  only  in accordance with the terms of such license and	*
 *   with the  inclusion  of  the  above  copyright  notice.   This	*
 *   software  or  any  other copies thereof may not be provided or	*
 *   otherwise made available to any other person.  No title to and	*
 *   ownership of the software is hereby transferred.			*
 *									*
 *   The information in this software is subject to change  without	*
 *   notice  and should not be construed as a commitment by Digital	*
 *   Equipment Corporation.						*
 *									*
 *   Digital assumes no responsibility for the use  or  reliability	*
 *   of its software on equipment which is not supplied by Digital.	*
 *									*
 ************************************************************************/

struct nidevice {
	unsigned long 	pc;
	unsigned long 	ps;
	unsigned long	pe;
	unsigned long	pd;
};
struct ni {
	VPPQB *ni_pqb;
	struct nidevice *ni_regs;
	int unit;
	int alive;
	unsigned int phys_pqb;
	char *ui;
	char *mbuf_clusters[NI_NRECV];
	caddr_t bde_virtual[NI_NBUF * (NI_NFREEQ-1)];
	caddr_t bde_base_addr;
};

#define MULTISIZE	6
