/* 
 * Mach Operating System
 * Copyright (c) 1991,1989,1988,1987 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */

/*
 * HISTORY
 * $Log:	cpmbx.h,v $
 * Revision 2.4  91/06/19  12:00:24  rvb
 * 	cputypes.h->platforms.h
 * 	[91/06/12  13:57:47  rvb]
 * 
 * 	Support for VaxStation 3100: cvax like VAX6x0
 * 	[91/06/04            rvb]
 * 
 * Revision 2.3  91/05/14  17:42:03  mrt
 * 	Correcting copyright
 * 
 * Revision 2.2  91/05/08  13:14:59  dbg
 * 	Changed to new copyright.
 * 	[91/04/26  15:14:22  dbg]
 * 
 * Revision 2.1  89/08/03  16:19:56  rwd
 * Created.
 * 
 * 14-Aug-88  David Golub (dbg) at Carnegie-Mellon University
 *	Only define console program mailbox fields.
 *
 * 11-Nov-87  David Golub (dbg) at Carnegie-Mellon University
 *	Remove 'extern' from declarations of firmware and cpmbx so that
 *	they are defined somewhere even without VAX650 turned on!
 *
 * 30-Oct-87  Robert V. Baron (rvb) at Carnegie-Mellon University
 *	Definitions common to uVaxII (ka630) and Mayfair (ka650)
 *	Created
 */

#ifndef	_VAX_CPMBX_H_
#define	_VAX_CPMBX_H_

#ifdef	KERNEL
#include <platforms.h>
#endif	KERNEL

#if	VAX650 || VAX630 || VAX3100
/* CPMBX bits */
#define	CPMBX_HLTACT	0x03

/* halt action values */
#define CPMBX_RSBOOT	0x00	/* Restart/Boot */
#define	CPMBX_RESTRT	0x01
#define	CPMBX_REBOOT	0x02
#define	CPMBX_HALT	0x03

/* in progress flags */
#define	CPMBX_BOOT	0x04
#define	CPMBX_RSTRT	0x08

/* language code - preserve when setting other fields */
#define	CPMBX_LANG	0xf0

#define	set_cpmbx(code)	(*cpmbx=(*cpmbx&CPMBX_LANG)|(code))

#ifdef	KERNEL
char *cpmbx;		/* address of console program mail box */
#endif	KERNEL

#endif  VAX650 || VAX630 || VAX3100
#endif	/* _VAX_CPMBX_H_ */
