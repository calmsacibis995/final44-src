/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	cpu.addrs.h,v $
 * Revision 2.2  89/07/11  23:24:21  jjc
 * 	Changed where cpu.addrs.h is included from.
 * 	[89/06/04            jjc]
 * 
 */
/*
 * cpu.addrs.h
 *
 * @(#)cpu.addrs.h 1.6 88/02/08
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */

#if defined(SUN2) || defined(sun2)
#include "../sun2/cpu.addrs.h"
#endif defined(SUN2) || defined(sun2)

#if defined(SUN3) || defined(sun3)
#if	CMUCS
#include <mon/sun3/cpu.addrs.h>
#else	CMUCS
#include "../../mon/sun3/cpu.addrs.h"
#endif	CMUCS
#endif defined(SUN3) || defined(sun3)

#if defined(SUN4) || defined(sun4)
#if	CMUCS
#include <mon/sun4/cpu.addrs.h>
#else	CMUCS
#include "../sun4/cpu.addrs.h"   
#endif	CMUCS
#endif defined(SUN4) || defined(sun4)
