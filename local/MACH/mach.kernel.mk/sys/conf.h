/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	conf.h,v $
 * Revision 2.6  89/03/09  22:03:02  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  17:52:34  gm0w
 * 	Got rid of MACH conditionals and non-MACH code.
 * 	Changed romp to ibmrt
 * 	[89/02/13            mrt]
 * 
 * Revision 2.4  89/01/23  22:25:15  af
 * 	Made declarations "extern", to make Mips compiler happy.
 * 	[89/01/04            af]
 * 
 * Revision 2.3  88/08/24  02:25:01  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:10:54  mwyoung]
 * 
 * 24-Dec-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	romp: Added l_select field to linesw for X on the RT.
 *
 * 17-Jul-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	MACH: removed definition of swdevt.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)conf.h	7.1 (Berkeley) 6/4/86
 */

#ifndef	_SYS_CONF_H_
#define _SYS_CONF_H_

/*
 * Declaration of block device
 * switch. Each entry (row) is
 * the only link between the
 * main unix code and the driver.
 * The initialization of the
 * device switches is in the
 * file conf.c.
 */

struct bdevsw
{
	int	(*d_open)();
	int	(*d_close)();
	int	(*d_strategy)();
	int	(*d_dump)();
	int	(*d_psize)();
	int	d_flags;
};

#ifdef	KERNEL
extern struct	bdevsw bdevsw[];
#endif	KERNEL

/*
 * Character device switch.
 */

struct cdevsw
{
	int	(*d_open)();
	int	(*d_close)();
	int	(*d_read)();
	int	(*d_write)();
	int	(*d_ioctl)();
	int	(*d_stop)();
	int	(*d_reset)();
	struct tty *d_ttys;
	int	(*d_select)();
	int	(*d_mmap)();
};

#ifdef	KERNEL
extern struct	cdevsw cdevsw[];
#endif	KERNEL

/*
 * tty line control switch.
 */

struct linesw
{
	int	(*l_open)();
	int	(*l_close)();
	int	(*l_read)();
	int	(*l_write)();
	int	(*l_ioctl)();
	int	(*l_rint)();
	int	(*l_rend)();
	int	(*l_meta)();
	int	(*l_start)();
	int	(*l_modem)();
#ifdef	ibmrt
	int	(*l_select)();
#endif	ibmrt
};

#ifdef	KERNEL
extern struct	linesw linesw[];
#endif	KERNEL
#endif	_SYS_CONF_H_
