/* 
 * Mach Operating System
 * Copyright (c) 1994-1989 Carnegie Mellon University
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
 * $Log:	mips_box.c,v $
 * Revision 2.22  94/12/16  11:03:05  dbg
 * 	Removed some lint.
 * 	[94/12/05            dbg]
 * 
 * 	Bus_master_init and bus_device_init are now built by config.
 * 	[94/07/20            dbg]
 * 
 * 	Use chips/tc.h.
 * 	[94/07/08            dbg]
 * 
 * 	RT-Mach merge: changed mc_driver to mcdriver.  mc_intr now calls
 * 	clock_interrupt itself.
 * 	[94/06/22            dbg]
 * 
 * Revision 2.21  93/11/17  17:52:18  dbg
 * 	Changed for new clock devices.
 * 	[93/06/11            dbg]
 * 
 * Revision 2.20  93/05/15  19:12:02  mrt
 * 	machparam.h -> machspl.h
 * 
 * Revision 2.19  93/05/10  21:20:46  rvb
 * 	No more sys/types.h
 * 	[93/05/06  09:40:51  af]
 * 
 * Revision 2.18  93/02/05  08:04:03  danner
 * 	Clock got more generic.
 * 	[93/02/04  02:03:31  af]
 * 
 * Revision 2.17  93/01/21  12:23:32  danner
 * 	ecc --> atm
 * 	[93/01/19  16:35:47  bershad]
 * 
 * Revision 2.16  93/01/14  17:50:31  danner
 * 	Added sfb.
 * 	[92/11/29            af]
 * 
 * Revision 2.15  92/05/22  15:48:59  jfriedl
 * 	Typos on slaves 27.  Now Mark is happy.
 * 	[92/05/13            af]
 * 
 * Revision 2.14  92/05/05  10:46:47  danner
 * 	Added scsi-cpu links to other processors.
 * 	[92/04/14  12:10:07  af]
 * 
 * 	Added maxine's mappable timer.
 * 	[92/03/11  02:36:18  af]
 * 
 * Revision 2.13  92/04/03  12:09:42  rpd
 * 	To support the FORE ATM TurboChannel board.
 * 	[92/03/23            rvb]
 * 
 * Revision 2.12  92/04/01  15:14:57  rpd
 * 	Added maxine's mappable timer.
 * 	[92/03/11  02:36:18  af]
 * 
 * Revision 2.11  92/03/02  18:34:44  rpd
 * 	Added MAXine's drivers.
 * 	[92/03/02  02:20:00  af]
 * 
 * Revision 2.10  91/08/24  12:21:39  af
 * 	Spl defines, SCC and ASIC drivers, a bunch more disks and tapes
 * 	so that we can play any number of additional SCSI interface boards.
 * 	New fb screen driver.
 * 	[91/08/02  03:36:23  af]
 * 
 * Revision 2.9  91/06/19  11:56:09  rvb
 * 	The busses.h and other header files have moved to the "chips"
 * 	directory.
 * 	[91/06/07            rvb]
 * 
 * Revision 2.8  91/05/14  17:24:39  mrt
 * 	Correcting copyright
 * 
 * Revision 2.7  91/02/14  14:34:52  mrt
 * 	In clock interrupt routine, drop priority as now required.
 * 	[91/02/12  12:59:26  af]
 * 
 * 	Defined pmax_memcheck() and related default implementation.
 * 	[91/01/03  02:10:32  af]
 * 
 * Revision 2.6  91/02/05  17:42:47  mrt
 * 	Added author notices
 * 	[91/02/04  11:15:22  mrt]
 * 
 * 	Changed to use new Mach copyright
 * 	[91/02/02  12:14:01  mrt]
 * 
 * Revision 2.5  91/01/09  19:49:54  rpd
 * 	Defined pmax_memcheck() and related default implementation.
 * 	[91/01/03  02:10:32  af]
 * 
 * Revision 2.4  90/12/05  23:32:43  af
 * 	Moved a number of pmax-specific handlers in kn01.c
 * 	[90/12/03  23:28:42  af]
 * 
 * Revision 2.2.1.2  90/11/01  03:47:10  af
 * 	Mostly renames for new, copyright free drivers.
 * 	Added "pm" driver.
 * 
 * Revision 2.2.1.1  90/10/03  11:54:25  af
 * 	Reflected changes in new autoconf TC code.  Also, moved wildcarded
 * 	"se" driver entry after non-wildcarded ones.
 * 
 * Revision 2.2  90/08/07  22:25:14  rpd
 * 	Created.
 * 	[90/08/07  15:49:22  af]
 * 
 * Revision 2.1.1.1  90/05/30  15:49:07  af
 * 	Created.
 * 	[90/05/28            af]
 * 
 */
/*
 *	File: mips_box.c
 * 	Author: Alessandro Forin, Carnegie Mellon University
 *	Date:	5/90
 *
 *	Box-specific routines and data required by the MI code
 */

#include <gx.h>
#include <atm.h>

#include <mips/mips_cpu.h>
#include <machine/machspl.h>		/* spl definitions */
#include <chips/busses.h>
#include <chips/tc.h>
#include <mips/PMAX/mips_box.h>

#include <mips/PMAX/kmin.h>

extern void	kn01_scsi_intr(), kn01_se_intr(),
		kn01_dz_intr(), kn01_err_intr();

/* Common clock interrupt routine for pmax/3max */
/* use mc_intr in device driver */
extern void	mc_intr();

void (*pmax_intr2)() = kn01_scsi_intr;		/* SCSI */
void (*pmax_intr3)() = kn01_se_intr;		/* Lance */
void (*pmax_intr4)() = kn01_dz_intr;		/* DZ */
void (*pmax_intr5)() = mc_intr;			/* RTC */
void (*pmax_intr6)() = kn01_err_intr;		/* Write timeouts */

static
boolean_t null_memcheck(unsigned int addr, unsigned int pc)
{
	return FALSE;
}
boolean_t (*pmax_memcheck)() = null_memcheck;

