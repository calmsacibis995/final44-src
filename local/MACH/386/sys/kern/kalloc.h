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
 * $Log:	kalloc.h,v $
 * Revision 2.10  89/03/09  20:13:03  rpd
 * 	More cleanup.
 * 
 * Revision 2.9  89/02/25  18:04:45  gm0w
 * 	Kernel code cleanup.	
 * 	Put entire file under #ifdef KERNEL
 * 	[89/02/15            mrt]
 * 
 * Revision 2.8  89/02/07  01:01:53  mwyoung
 * Relocated from sys/kalloc.h
 * 
 * Revision 2.7  89/01/18  02:10:51  jsb
 * 	Fixed log.
 * 	[88/01/18            rpd]
 * 
 * Revision 2.2  89/01/18  01:16:25  jsb
 * 	Use MINSIZE of 16 instead of 64 (mostly for afs);
 * 	eliminate NQUEUES (see kalloc.c).
 * 	[89/01/13            jsb]
 *
 * 26-Oct-87 Peter King (king) at NeXT, Inc.
 *	Created.
 */ 

#ifndef	_KERN_KALLOC_H_
#define _KERN_KALLOC_H_

#include <sys/types.h>

#define MINSIZE 16

extern caddr_t kalloc();
extern caddr_t kget();

#ifdef	lint
extern void kfree();
#endif	lint

#endif	_KERN_KALLOC_H_
