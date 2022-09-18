/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	atbus.h,v $
 * Revision 2.2.1.2  90/11/27  13:40:45  rvb
 * 	Synched 2.5 & 3.0 at I386q (r2.2.1.2) & XMK35 (r2.4)
 * 	[90/11/15            rvb]
 * 
 * Revision 2.3  90/08/27  21:58:38  dbg
 * 	Fixed copyright to show that this file came from a released BSD
 * 	file.
 * 	[90/08/16            dbg]
 * 
 * Revision 2.2.1.1  90/07/10  11:43:04  rvb
 * 	Clean up structures a bit.  AND now we are an isa bus vs
 * 	i386.
 * 	[90/06/15            rvb]
 * 
 * Revision 2.2  90/05/03  15:40:34  dbg
 * 	Adapted for pure kernel.
 * 	[90/02/20            dbg]
 * 
 * Revision 2.2  89/07/17  10:38:43  rvb
 * 	Olivetti Changes to X79 upto 5/9/89:
 * 		An legitimate bus/controller/device definition.
 * 	[89/07/11            rvb]
 * 
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *      @(#)ubavar.h    7.7 (Berkeley) 6/28/90
 */


#ifndef	_I386AT_ATBUS_H_
#define	_I386AT_ATBUS_H_

/*
 * per-controller & driver definitions
 */

/*
 * Per-controller structure.
 * (E.g. one for each disk and tape controller, and other things
 * which have slave-style devices).
 *
 */
struct isa_ctlr {
	struct	isa_driver *ctlr_driver;
	long	ctlr_ctlr;	/* controller index in driver */
	long	ctlr_alive;	/* controller exists */
	caddr_t	ctlr_addr;	/* csr address */
	long	ctlr_spl;	/* spl level set upon interrupt */
	long	ctlr_pic;	/* pic line for controller */
	int	(**ctlr_intr)();/* interrupt handler */
	caddr_t	ctlr_start;	/* start address in mem space */
	u_long	ctlr_len;	/* length of mem space used */
};

/*
 * Per ``device'' structure.
 * (Everything else is a ``device''.)
 *
 * If a controller has many drives attached, then there will
 * be several isa_dev structures associated
 *
 */
struct isa_dev {
	struct	isa_driver *dev_driver;
	long	dev_unit;	/* unit number on the system */
	long	dev_ctlr;	/* ctlr number; -1 if none */
	long	dev_slave;	/* slave on controller */
	long	dev_alive;	/* Was it found at config time? */
	caddr_t	dev_addr;	/* csr address */
	short	dev_spl;	/* spl level */
	long	dev_pic;	/* pic line for device */
	long	dev_dk;		/* if init 1 set to number for iostat */
	long	dev_flags;	/* parameter from system specification */
	int	(**dev_intr)();	/* interrupt handler(s) */
	caddr_t	dev_start;	/* start address in mem space */
	u_long	dev_len;	/* length of mem space used */
	long	dev_type;	/* driver specific type information */
/* this is the forward link in a list of devices on a controller */
	struct	isa_dev *dev_forw;
/* if the device is connected to a controller, this is the controller */
	struct	isa_ctlr *dev_mi;
};

/*
 * Per-driver structure.
 *
 * Each driver defines entries for a set of routines for use
 * at boot time by the autoconfig routines.
 */
struct isa_driver {
	int	(*driver_probe)();	/* see if a driver is really there */
	int	(*driver_slave)();	/* see if a slave is there */
	int	(*driver_attach)();	/* setup driver for a slave */
	char	*driver_dname;		/* name of a device */
	struct	isa_dev *driver_dinfo;/* backptrs to init structs */
	char	*driver_mname;		/* name of a controller */
	struct	isa_ctlr **driver_minfo;/* backpointers to init structs */
};

#endif	_I386AT_ATBUS_H_
