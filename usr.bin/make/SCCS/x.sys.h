h07213
s 00023/00005/00053
d D 5.2 90/03/11 16:51:00 bostic 2 1
c add Berkeley specific copyright notices
e
s 00058/00000/00000
d D 5.1 90/03/11 16:48:09 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 1
/*
D 2
 * sys.h --
E 2
I 2
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * Copyright (c) 1988, 1989 by Adam de Boor
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
E 2
 *
D 2
 *     User-level definitions of routines and types for the sys module.
E 2
I 2
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
E 2
 *
D 2
 * Copyright 1986 Regents of the University of California
 * All rights reserved.
E 2
I 2
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
 *
D 2
 * $Id: sys.h,v 2.2 89/07/03 15:58:14 adam Exp $ SPRITE (Berkeley)
E 2
I 2
 *	%W% (Berkeley) %G%
 */

/*
 * sys.h --
E 2
 *
I 2
 *     User-level definitions of routines and types for the sys module.
E 2
 */

#ifndef _SYSUSER
#define _SYSUSER

typedef enum {
    SYS_WARNING, 
    SYS_FATAL
} Sys_PanicLevel;

/*
 * Flags for Sys_Shutdown.
 *
 *    SYS_REBOOT         Reboot the system. 
 *    SYS_HALT           Halt the system.
 *    SYS_KILL_PROCESSES Kill all processes.
 *    SYS_DEBUG		 Enter the debugger.
 *    SYS_WRITE_BACK	 Write back the cache after killing all processes but
 *			 obviously before halting or rebooting.
 */

#define SYS_REBOOT              0x01
#define SYS_HALT                0x02
#define	SYS_KILL_PROCESSES	0x04
#define	SYS_DEBUG		0x08
#define	SYS_WRITE_BACK		0x10

/*
 * Machine architecture and type values from Sys_GetMachineInfo().
 */

#define SYS_SPUR		1
#define SYS_SUN2		2
#define SYS_SUN3		3
#define SYS_SUN4		4
#define SYS_MICROVAX_2		5

#define SYS_SUN_2_50		0x02
#define SYS_SUN_2_120		0x01
#define SYS_SUN_2_160		0x02
#define SYS_SUN_3_75		0x11
#define SYS_SUN_3_160		0x11
#define SYS_SUN_3_50		0x12

extern ReturnStatus		Sys_GetMachineInfo();
extern void			Sys_Panic();

#endif _SYSUSER
E 1
