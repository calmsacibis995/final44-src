/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vfs_sysnames.h,v $
 * Revision 2.5  91/04/03  13:18:10  mbj
 * 	vfs changes for omron/luna88k.
 * 	[91/03/07  11:33:40  rvb]
 * 
 * Revision 2.4  90/08/30  11:51:37  bohman
 * 	Changes for mac2.
 * 	[90/08/28            bohman]
 * 
 * Revision 2.3  89/07/12  01:28:23  jjc
 * 	Added definition of SYS_NAME for Sun 4.  Conditionalized
 * 	definition using "sun3_mach" on "sun3" not just "sun".
 * 	[89/07/11            jjc]
 * 
 * Revision 2.2  89/06/03  15:42:38  jsb
 * 	Picked up pmax_mach and mseries_mach definitions from af/rvb.
 * 	[89/06/02  12:52:06  jsb]
 * 
 * 	Created from afs/param.h to support @sys expansion in all filesystems.
 * 	[89/05/26  16:53:30  jsb]
 * 
 */
#if	defined(mac2)
#ifdef	CMU_MACMACH
#define SYS_NAME	"mac2_51"
#else
#define SYS_NAME	"mac2_mach"
#endif
#endif	defined(mac2)
#if	sun3
#define SYS_NAME	"sun3_mach"
#endif	sun3
#if	sun4
#define SYS_NAME	"sun4_mach"
#endif	sun4
#if	vax
#define SYS_NAME	"vax_mach"
#endif	vax
#if	ibmrt
#define SYS_NAME	"rt_mach"
#endif	ibmrt
#ifdef	multimax
#define SYS_NAME	"mmax_mach"
#endif	multimax
#ifdef	i386
#define SYS_NAME	"i386_mach"
#endif	i386
#ifdef	mips
#ifdef	PMAX
#define SYS_NAME	"pmax_mach"
#endif	PMAX
#ifdef	MSERIES
#define SYS_NAME	"mseries_mach"
#endif	MSERIES
#endif	mips
#ifdef	luna88k
#define SYS_NAME	"luna88k_mach"
#endif	luna88k
