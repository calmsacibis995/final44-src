/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	node.h,v $
 * Revision 2.3  89/02/26  10:59:04  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  88/08/10  10:51:59  rvb
 * 	Created.  Week of 4/4.
 * 
 */
/*
 *	File:	node.h
 *	Author:	Robert V. Baron
 *
 *	Definitions for <foo>node structures for storing useful stuff
 *	 about each node. 
 */
#include <cputypes.h>

#define NNODES 16
	/*
	 * cpunode is kept sparse so that cpunode[i] is the info for
	 * cpu_number() == i;
	 * The other tables are dense, filling up to nmem or noia
	 * entries.
	 */

struct	cpunode {
	union {
#if	VAX6200
		struct ka62a	*m62;
#endif	VAX6200
#if	VAX820
		struct bi_node	*m82;
#endif	VAX820
	} addr;
	int		 node;	
};

struct	memnode {
	union {
#if	VAX6200
		struct ms62a	*m62;
#endif	VAX6200
#if	VAX8800
		struct mcl	*m88;
#endif	VAX8800
#if	VAX820
		struct bi_node	*m82;
#endif	VAX820
	} addr;
	int		 node;
};

struct	ioanode {
	union {
#if	VAX6200
		struct dwmba	*m62;
#endif	VAX6200
#if	VAX8800
		struct nbi	*m88;
#endif	VAX8800
#if	VAX820
		struct bi_node	*m82;
#endif	VAX820
	} addr;
	int		node;
	struct bi_node	*bddr;
	int		bnode;
	caddr_t		bi_addr;
	struct bi_node	*bi[BI_MAX_NODE];
};

#define addr62 addr.m62
#define addr82 addr.m82
#define addr88 addr.m88


#ifdef	KERNEL
#ifndef	ASSEMBLER

extern int 	ncpu;
extern struct	cpunode	cpunode[];	/* remember node address */
extern int	nmem;
extern struct	memnode memnode[];
extern int	nioa;			/* number of io adapters */
extern struct	ioanode	ioanode[];	/* remember node address */

#endif	ASSEMBLER
#endif	KERNEL
