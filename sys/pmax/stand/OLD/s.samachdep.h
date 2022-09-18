h46361
s 00031/00000/00000
d D 7.1 92/11/15 16:46:58 ralph 1 0
c date and time created 92/11/15 16:46:58 by ralph
e
u
U
t
T
I 1
/*
 * Copyright (c) 1982, 1992 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifdef DS5000
#define	NASC		1

/*
 * Define different classes of device drivers for booting.
 */
#define TC_SCSI		0

struct intr_tab {
	void	(*func)();	/* pointer to interrupt routine */
	int	unit;		/* logical unit number */
};

extern	struct intr_tab intr_tab[];
#endif

#ifdef DS3100
#define	NSII		1
#endif

#define NRZ		7
#define NTZ		7
E 1
