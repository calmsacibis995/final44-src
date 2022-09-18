/* 
 * Mach Operating System
 * Copyright (c) 1993 Carnegie Mellon University
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
 * $Log:	clock_dev.h,v $
 * Revision 2.2  93/11/17  19:05:40  dbg
 * 	Created.
 * 	[93/09/29            dbg]
 * 
 */

#ifndef	_DEVICE_CLOCK_DEV_H_
#define	_DEVICE_CLOCK_DEV_H_

/*
 *	Common operations on clock devices.
 */

#include <mach/machine/vm_types.h>
#include <mach/vm_prot.h>
#include <kern/clock.h>
#include <device/device_types.h>
#include <device/clock_status.h>

/*
 *	Common clock routines.
 */
extern io_return_t
clock_open(
	mach_clock_t	clock);

extern io_return_t
clock_getstat(
	mach_clock_t	clock,
	dev_flavor_t	flavor,
	dev_status_t	stat,
	natural_t	*count);

extern io_return_t
clock_setstat(
	mach_clock_t	clock,
	dev_flavor_t	flavor,
	dev_status_t	stat,
	natural_t	count);

extern vm_offset_t
clock_map_page(
	mach_clock_t	clock,
	vm_offset_t	off,
	vm_prot_t	prot);

/*
 *	Conversion between dates (Y/M/D H:M:S) and
 *	seconds since January 1, 1970 (our arbitrary
 *	time base)
 */
extern natural_t
ymd_to_seconds(
	int		year,
	int		month,
	int		day,
	int		hour,
	int		minute,
	int		second);

extern void
seconds_to_ymd(
	natural_t	seconds,
	int		*year,
	int		*month,
	int		*day,
	int		*hour,
	int		*minute,
	int		*second,
	int		*day_of_week);

#endif	/* _DEVICE_CLOCK_DEV_H_ */
