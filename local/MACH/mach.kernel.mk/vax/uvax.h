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
 * $Log:	uvax.h,v $
 * Revision 2.3  89/03/09  22:22:47  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  10:49:35  gm0w
 * 	Changes for cleanup.
 * 
 * 11-Nov-87  David Golub (dbg) at Carnegie-Mellon University
 *	Remove 'extern' from declarations of firmware and cpmbx so that
 *	they are defined somewhere even without VAX650 turned on!
 *
 * 30-Oct-87  Robert V. Baron (rvb) at Carnegie-Mellon University
 *	Definitions common to uVaxII (ka630) and Mayfair (ka650)
 *	Created
 *
 */

#ifdef	KERNEL
#include <cputypes.h>
#endif	KERNEL

#if	VAX650 || VAX630
#define QBUS_CSR	((caddr_t) 0x20000000)
#define QBUS_MAP	((int *)   0x20088000)
#define QBUS_MEM	((caddr_t) 0x30000000)

/* Bdr register bits */
	/* Unfortunately, Machine specific */

#define set_cpmbx(code)	(*cpmbx=(*cpmbx&CPMBX_LANG)|(code))

/* CPMBX bits */
#define CPMBX_HLTACT	03
/* halt action values */
#define CPMBX_RSBOOT	00	/* Restart/Boot */
#define CPMBX_RESTRT	01
#define CPMBX_REBOOT	02
#define CPMBX_HALT	03
/* in progress flags */
#define CPMBX_BOOT	04
#define CPMBX_RSTRT	010
#define CPMBX_LANG	0360

#ifdef	KERNEL
char *firmware;		/* address of ROM - currently used only for VAX650 */
char *cpmbx;		/* address of console program mail box */
#endif	KERNEL
#endif	VAX650 || VAX630
