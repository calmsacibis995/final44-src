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
 * $Log:	clock_dev.c,v $
 * Revision 2.4  93/12/23  10:04:36  dbg
 * 	Use bcopy to get and set status variable for CLOCK_TIME, since
 * 	the alignment may not be correct (on the ALPHA, dev_status_t is
 * 	32-bit aligned, but time_spec_t is 64-bit aligned).  The real fix
 * 	is to devise a separate interface for getting/setting the time
 * 	that describes the data structure correctly.  An even better fix
 * 	would be to drop the 'ioctl'-like interfaces and move to an
 * 	object-oriented device interface.
 * 	[93/12/17            dbg]
 * 
 * Revision 2.3  93/12/07  13:53:33  dbg
 * 	Return weekday from seconds_to_ymd as 0..6.
 * 	[93/12/06            dbg]
 * 
 * Revision 2.2  93/11/17  16:30:15  dbg
 * 	Maintain clock->check_seconds to allow reading time without
 * 	locking clock.
 * 	[93/06/18            dbg]
 * 
 * 	Pulled common routines from various clock device drivers
 * 	into this file.
 * 	[93/06/02            dbg]
 * 
 */

/*
 *	Common clock device routines.
 */

#include <mach/boolean.h>
#include <mach/time_spec.h>
#include <mach/machine/vm_types.h>

#include <ipc/ipc_types.h>
#include <kern/macro_help.h>
#include <kern/memory.h>
#include <kern/lock.h>
#include <kern/clock.h>
#include <vm/vm_kern.h>

#include <device/device_types.h>
#include <device/clock_status.h>
#include <machine/machspl.h>

/*
 *	Routine:	convert_device_port_to_clock
 *	Purpose:	Takes a device port (passed in to timer_create) and
 *			calls the d_dev_info function to obtain the a pointer
 *			to a clock structure which is returned.  If the 
 *			device does not represent a clock then the call 
 *			returns CLOCK_NULL.
 *	Conditions:	None
 */
mach_clock_t convert_device_port_to_clock(
	ipc_port_t	port)
{
	mach_clock_t	clock;
	device_t	clock_device;

	clock_device = dev_port_lookup(port);

	if (clock_device == DEVICE_NULL)
	    return CLOCK_NULL;

	if ((*clock_device->dev_ops->d_dev_info)(clock_device->dev_number,
						 D_INFO_CLOCK,
						 &clock) != D_SUCCESS)
	    return CLOCK_NULL;

	return clock;
}

/*
 *	Routine:	convert_clock_to_device_port
 *	Purpose:	takes a clock reference, and converts
 *			it to a port to the unprivileged clock device.
 *
 *	(Not implemented yet - returns MACH_PORT_NULL.)
 */
ipc_port_t
convert_clock_to_device_port(
	mach_clock_t	clock)
{
	return IP_NULL;
}

/*
 *	Open a clock.
 */
io_return_t clock_open(
	mach_clock_t	clock)
{
	if (clock->mtime == 0) {
	    spl_t	s;

	    if (kmem_alloc_wired(kernel_map,
				 (vm_offset_t *)&clock->mtime,
				 PAGE_SIZE) != KERN_SUCCESS)
		return KERN_RESOURCE_SHORTAGE;

	    bzero((char *)clock->mtime, PAGE_SIZE);

	    s = splsched();
	    clock_queue_lock(clock);
	    clock_set_mtime(clock);
	    clock_queue_unlock(clock);
	    splx(s);
	}

	return D_SUCCESS;
}

io_return_t clock_getstat(
	mach_clock_t	clock,
	dev_flavor_t	flavor,
	dev_status_t	stat,
	natural_t	*count)
{
	spl_t		s;

	switch (flavor) {
	    case CLOCK_TIME:
	    {
		time_spec_t	cur_time;

		if (*count < CLOCK_TIME_COUNT)
		    return D_INVALID_SIZE;

		clock_read(cur_time, clock);

		bcopy(&cur_time, stat, sizeof(time_spec_t));	/* XXX */
		*count = CLOCK_TIME_COUNT;

		break;
	    }

	    case CLOCK_RESOLUTION:
	    {
		clock_resolution_t	request;

		if (*count < CLOCK_RESOLUTION_COUNT)
		    return D_INVALID_SIZE;

		*count = CLOCK_RESOLUTION_COUNT;
		request = (clock_resolution_t) stat;

		s = splsched();
		clock_queue_lock(clock);

		request->resolution = clock->resolution;
		request->skew	    = clock->skew;

		clock_queue_unlock(clock);
		splx(s);

		break;
	    }

	    case CLOCK_CORRECTION:
	    {
		clock_correction_t request;

		if (*count < CLOCK_CORRECTION_COUNT)
		    return D_INVALID_SIZE;

		*count = CLOCK_CORRECTION_COUNT;
		request = (clock_correction_t) stat;

		s = splsched();
		clock_queue_lock(clock);

		request->delta = clock->correction_delta;
		request->count = clock->correction_count;

		clock_queue_unlock(clock);
		splx(s);

		break;
	    }
	    default:
		return D_INVALID_OPERATION;
	}

	return D_SUCCESS;
}

/*
 *	Generic set status routine.
 *	Cannot change resolution.
 */
io_return_t clock_setstat(
	mach_clock_t	clock,
	dev_flavor_t	flavor,
	dev_status_t	stat,
	natural_t	count)
{
	spl_t	s;

	switch (flavor) {
	    case CLOCK_TIME:
	    {
		time_spec_t	new_time, delta;

		if (count < CLOCK_TIME_COUNT)
		    return D_INVALID_SIZE;

		bcopy(stat, &new_time, sizeof(time_spec_t));	/* XXX */

		s = splsched();
		clock_queue_lock(clock);

		/*
		 *	Adjust the time for all relative timers.
		 */
		delta = new_time;
		time_spec_subtract(delta, clock->time);
		clock_timer_adjust(clock, delta);

		/*
		 *	Change the time in software...
		 */
		clock->check_seconds = new_time.seconds;
		clock->time = new_time;
		clock_set_mtime(clock);

		/*
		 *	... and hardware.
		 */
		(*clock->ops->set_time)(clock, new_time);

		clock_queue_unlock(clock);
		splx(s);

		break;
	    }

	    case CLOCK_CORRECTION:
	    {
		clock_correction_t request;

		if (count < CLOCK_CORRECTION_COUNT)
		    return D_INVALID_SIZE;

		request = (clock_correction_t) stat;

		s = splsched();
		clock_queue_lock(clock);

		clock->correction_delta = request->delta;
		clock->correction_count = request->count;

		clock_queue_unlock(clock);
		splx(s);

		break;
	    }
	    default:
		return D_INVALID_OPERATION;
	}

	return D_SUCCESS;
}

vm_offset_t clock_map_page(
	mach_clock_t	clock,
	vm_offset_t	off,
	vm_prot_t	prot)
{
	if (prot & VM_PROT_WRITE)
	    return -1;	/* invalid */

	return pmap_extract(pmap_kernel(),
			    (vm_offset_t) clock->mtime);
}

#if 0
/*
 *	Implemented in individual clock drivers
 */
io_return_t clock_info(
	mach_clock_t	clock,
	dev_flavor_t	flavor,
	vm_offset_t	*info)
{
	if (flavor == D_INFO_CLOCK) {
	    *info = (vm_offset_t) clock;
	    return D_SUCCESS;
	}
	else {
	    return D_INVALID_OPERATION;
	}
}
#endif

/*
 *	Routines to convert between seconds and
 *	day/month/year.
 */

int	days_per_month[12] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

#define	leap_year(year)		(((year) % 4) == 0)

/*
 *	Convert year/month/day/hours:minutes:seconds to
 *	seconds since Jan 1, 1970.
 */
natural_t ymd_to_seconds(
	int	year,
	int	month,
	int	day,
	int	hour,
	int	minute,
	int	second)
{
	unsigned int	days_in_year;

	days_in_year = 0;
	if (leap_year(year) && month > 2)
	    days_in_year = 1;	/* leap year, after Feb 29 */

	for (--year; year >= 1970; year--) {
	    days_in_year += 365;
	    if (leap_year(year))
		days_in_year++;
	}
	while (month > 1)
	    days_in_year += days_per_month[--month - 1];

	second += minute * 60;
	second += hour * (60 * 60);
	second += (day - 1) * (24 * 60 * 60);	/* 1-based */

	second += days_in_year * (24 * 60 * 60);
			/* no, we don`t account for leap_seconds */
	return second;
}

/*
 *	Convert seconds since Jan 1, 1970 to
 *	year/month/day/hours:minutes:seconds.
 */
void seconds_to_ymd(
	natural_t	seconds,	/* in */
	int	*year,			/* 1970 .. ? */
	int	*month,			/* 1 .. 12 */
	int	*day,			/* 1 .. 31 */
	int	*hour,			/* 0 .. 23 */
	int	*minute,		/* 0 .. 59 */
	int	*second,		/* 0 .. 59 */
	int	*day_of_week)		/* 0 (Sun) .. 6 (Sat) */
{
	unsigned int years, months, days, temp;

	temp = seconds;

	/*
	 *	Convert seconds since Jan 1, 1970 to
	 *	year/month/day/...
	 */

	*second	= temp % 60;
	temp	= temp / 60;

	*minute	= temp % 60;
	temp	= temp / 60;

	*hour	= temp % 24;
	temp	= temp / 24;

	*day_of_week = (temp + 4) % 7;	/* Jan 1, 1970 is Thursday */

	years = 1970;
	for (;;) {
	    days = 365;
	    if (leap_year(years))
		days++;
	    if (temp < days)
		break;
	    temp -= days;
	    years++;
	}

	months = 0;
	for (;;) {
	    days = days_per_month[months++];
	    if (months == 2 && leap_year(years))
		days++;
	    if (temp < days)
		break;
	    temp -= days;
	}

	*day = temp + 1;	/* from 1 */
	*month = months;
	*year = years;
}
