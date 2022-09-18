/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	node.h,v $
 * Revision 2.1  89/08/03  16:38:24  rwd
 * Created.
 * 
 *  3-Mar-89  David Golub (dbg) at Carnegie-Mellon University
 *	Stolen from Bob Baron.
 *
 */

struct ioa_node {
	char *		addr;		/* address of IO adaptor */
	int		node;		/* node number on backplane */

	struct bi_node	*bddr;		/* address... */
	int		bnode;		/* and node number
					   for BI node connecting to
					   IO adaptor
					 */
	struct bi_node *bi_paddr;	/* physical address of BI bus
					   for this IO adaptor */
	struct bi_node *bi_vaddr;	/* virtual address of BI bus
					   for this IO adaptor */
	unsigned int	bi_present;	/* mask of BI nodes present:
					   bit (1<<node) marks node */
};

struct mem_node {
	char *		addr;		/* address of memory controller */
	int		node;		/* node on bus */
};

struct cpu_node {
	char *		addr;		/* address of CPU registers */
	int		node;		/* node on bus */
};

extern struct ioa_node	ioa_node[];
extern int		nioa;
extern struct mem_node	mem_node[];
extern int		nmem;
extern struct cpu_node	cpu_node[];
extern int		ncpu;

/*
 * cpu_node[] is sparsely indexed, by cpu_number.
 * mem_node[] and ioa_node[] are dense.
 */
