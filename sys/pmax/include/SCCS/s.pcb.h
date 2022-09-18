h40847
s 00002/00002/00032
d D 8.1 93/06/10 23:02:27 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00033
d D 7.3 93/05/09 16:09:40 ralph 3 2
c new improved pmap changes
e
s 00008/00000/00025
d D 7.2 92/07/27 21:31:38 ralph 2 1
c added md_coredump struct
e
s 00025/00000/00000
d D 7.1 92/01/07 20:35:50 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department and Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: pcb.h 1.13 89/04/23$
 *
 *	%W% (Berkeley) %G%
 */

/*
 * PMAX process control block
 */
struct pcb
{
	int	pcb_regs[69];	/* saved CPU and floating point registers */
	label_t	pcb_context;	/* kernel context for resume */
	int	pcb_onfault;	/* for copyin/copyout faults */
I 3
	void	*pcb_segtab;	/* copy of pmap pm_segtab */
E 3
};
I 2

/*
 * The pcb is augmented with machine-dependent additional data for
 * core dumps. For the PMAX, there is nothing to add.
 */
struct md_coredump {
	long	md_pad[8];
};
E 2
E 1
