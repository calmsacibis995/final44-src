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
 * $Log:	port.h,v $
 * Revision 2.10  89/03/09  20:22:30  rpd
 * 	More cleanup.
 * 
 * Revision 2.9  89/03/05  16:49:06  rpd
 * 	Moved ownership rights under MACH_IPC_XXXHACK.
 * 	[89/02/16            rpd]
 * 
 * Revision 2.8  89/02/25  18:39:37  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.7  89/02/07  00:52:59  mwyoung
 * Relocated from sys/port.h
 * 
 * Revision 2.6  89/01/10  23:32:30  rpd
 * 	Only define PORT_ENABLED when MACH_IPC_XXXHACK is turned on.
 * 	[89/01/10  23:10:59  rpd]
 * 
 * Revision 2.5  88/09/25  22:16:30  rpd
 * 	Removed PORT_INVALID.  Cast PORT_NULL as port_name_t and
 * 	PORT_ENABLED as port_set_name_t.
 * 	[88/09/24  18:11:43  rpd]
 * 
 * Revision 2.4  88/07/29  03:21:36  rpd
 * When non-KERNEL, don't define PORT_ILLEGAL and define PORT_ENABLED as
 * a global port-set variable.  Compatibility code in libmach will implement
 * port_enable/port_disable using a PORT_ENABLED variable.
 * 
 * Revision 2.3  88/07/20  21:06:54  rpd
 * Added port_set_name_t, port_name_array_t, port_type_t, port_type_array_t.
 * Added PORT_TYPE_* definitions.
 * Add port_name_t type.
 * 
 * Revision 2.2  88/07/17  18:53:32  mwyoung
 * .
 * 
 * Revision 2.1.2.1  88/06/28  20:51:47  mwyoung
 * Pick up rpd's changes.
 * 
 * Revision 2.1.1.1  88/06/23  23:30:39  rpd
 * Add port_name_t type.
 * 
 * 10-Nov-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added PORT_INVALID and some more documentation.
 *
 * 28-Oct-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added port_*_t types; not all are used by the
 *	kernel, but names are exported for consistency.
 *
 * 21-Oct-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added port_rcv_t type; used by the interface generator.
 *
 * 19-Jul-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Documentation change only.
 *
 * 26-Jun-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added PORT_ENABLED to refer to any enabled port.
 *
 *  8-May-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Created
 *
 */
/*
 *	File:	mach/port.h
 *
 *	Definition of a port
 *
 *	[The basic port_t type should probably be machine-dependent,
 *	as it must be represented by a 32-bit integer.]
 */

#ifndef	_MACH_PORT_H_
#define _MACH_PORT_H_

#ifdef	KERNEL
#include <mach_ipc_xxxhack.h>
#endif	KERNEL

typedef int 		port_name_t;		/* A capability's name */
typedef port_name_t	port_set_name_t;	/* Descriptive alias */
typedef port_name_t	*port_name_array_t;

typedef int		port_type_t;		/* What kind of capability? */
typedef port_type_t	*port_type_array_t;

	/* Values for port_type_t */

#define PORT_TYPE_NONE		0		/* No rights */
#define PORT_TYPE_SEND		1		/* Send rights */
#if	!defined(KERNEL) || MACH_IPC_XXXHACK
#define PORT_TYPE_RECEIVE	3		/* Send, receive rights */
#define PORT_TYPE_OWN		5		/* Send, ownership rights */
#endif	!defined(KERNEL) || MACH_IPC_XXXHACK
#define PORT_TYPE_RECEIVE_OWN	7		/* Send, receive, ownership */
#define PORT_TYPE_SET		9		/* Set ownership */
#define PORT_TYPE_LAST		10		/* Last assigned */

typedef	port_name_t	port_t;			/* Port with send rights */
typedef	port_t		port_rcv_t;		/* Port with receive rights */
typedef	port_t		port_own_t;		/* Port with ownership rights */
typedef	port_t		port_all_t;		/* Port with receive and ownership */
typedef	port_t		*port_array_t;

#define PORT_NULL	((port_name_t) 0)	/* Used to denote no port; legal value */
#ifdef	KERNEL
#if	MACH_IPC_XXXHACK
#define PORT_ENABLED	((port_set_name_t) -1)	/* Used in msg_receive */
#endif	MACH_IPC_XXXHACK
#else	KERNEL
extern port_set_name_t PORT_ENABLED;
#endif	KERNEL
#endif	_MACH_PORT_H_
