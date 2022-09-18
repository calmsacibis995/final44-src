/* 
 * Mach Operating System
 * Copyright (c) 1994 Carnegie Mellon University
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
 * $Log:	ipc_clock.c,v $
 * Revision 2.2  94/12/16  10:42:50  dbg
 * 	Added ikot_clock_control; converted to new ipc_kobject_type_t.
 * 	[94/06/01            dbg]
 * 
 * 	Created (destroying old file of same name in the process)
 * 	[94/03/15            jimz]
 * 
 */

/*
 *	IPC control over clocks.
 *
 *	Locking is not needed because clocks are created once,
 *	at system initialization, and never destroyed.
 */
#include <ipc/ipc_port.h>
#include <ipc/ipc_space.h>
#include <kern/assert.h>
#include <kern/ipc_kobject.h>
#include <kern/mach_clock.h>

struct ipc_kobject_type	ikot_clock = {
	0,
	0,
	FALSE,
	FALSE
};

struct ipc_kobject_type	ikot_clock_control = {
	0,
	0,
	FALSE,
	FALSE
};


	
/*
 *	Routine:	ipc_clock_enable
 *	Purpose:	Enable a clock for IPC access
 *	Conditions:	None
 */
void ipc_clock_enable(
	mach_clock_t clock)
{
	ipc_port_t kport, kport_ctrl;

	kport = ipc_port_alloc_kernel();	/* status port */
	if (kport == IP_NULL)
	    panic("ipc_clock_enable");

	kport_ctrl = ipc_port_alloc_kernel();	/* control port */
	if (kport_ctrl == IP_NULL)
	    panic("ipc_clock_enable");

	clock->clk_status = kport;
	ipc_kobject_set(kport, (ipc_kobject_t) clock, &ikot_clock);

	clock->clk_control = kport_ctrl;
	ipc_kobject_set(kport_ctrl, (ipc_kobject_t) clock,
			&ikot_clock_control);
}

/*
 *	Routine:	convert_port_to_clock
 *	Purpose:	Convert from a port to a clock.  If the port isn't
 *			valid, or doesn't represent a clock then return
 *			MACH_CLOCK_NULL.
 *	Conditions:	None
 */
mach_clock_t convert_port_to_clock(
	ipc_port_t	port)
{
	mach_clock_t clock = MACH_CLOCK_NULL;

	if (IP_VALID(port)) {
	    ip_lock(port);
	    if (ip_active(port) &&
		(port->ip_kotype == &ikot_clock ||
		 port->ip_kotype == &ikot_clock_control))
	    {
		clock = (mach_clock_t) port->ip_kobject;
	    }
	    ip_unlock(port);
	}

	return clock;
}


/*
 *	Routine:	convert_port_to_clock_control
 *	Purpose:	Convert from a port to a clock control port.
 *			If the port isn't
 *			valid, or doesn't represent a clock then return
 *			MACH_CLOCK_NULL.
 *	Conditions:	None
 */
mach_clock_t convert_port_to_clock_control(
	ipc_port_t	port)
{
	mach_clock_t clock = MACH_CLOCK_NULL;

	if (IP_VALID(port)) {
	    ip_lock(port);
	    if (ip_active(port) && port->ip_kotype == &ikot_clock_control) {
		clock = (mach_clock_t) port->ip_kobject;
	    }
	    ip_unlock(port);
	}

	return clock;
}


/*
 *	Routine:	convert_clock_to_port
 *	Purpose:	Convert from a clock to a port.
 *	Conditions:	None
 */
ipc_port_t convert_clock_to_port(
	mach_clock_t	clock)
{
	assert(clock->clk_status != IP_NULL);
	return ipc_port_make_send(clock->clk_status);
}

/*
 *	Routine:	convert_clock_control_to_port
 *	Purpose:	Convert from a clock to a port.
 *	Conditions:	None
 */
ipc_port_t convert_clock_control_to_port(
	mach_clock_t clock)
{
	assert(clock->clk_control != IP_NULL);
	return ipc_port_make_send(clock->clk_control);
}
