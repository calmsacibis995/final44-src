/* 
 * Mach Operating System
 * Copyright (c) 1994,1993,1992 Carnegie Mellon University
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
 * $Log:	clockpit.h,v $
 * Revision 2.3  94/12/15  15:30:32  dbg
 * 	Renamed 'time_spec' to 'timespec'.
 * 	[94/05/24            dbg]
 * 
 * Revision 2.2  93/11/17  16:42:11  dbg
 * 	Merged into mainline.
 * 
 * 	Created
 * 	[92/06/22	savage]
 * 
 */

#ifndef	_I386AT_CLOCKPIT_H_
#define	_I386AT_CLOCKPIT_H_

#include <i386/mach_param.h>		/* for default HZ */
#include <mach/timespec.h>

io_return_t	clockpitprobe();
io_return_t	clockpitattach();
io_return_t	clockpitopen();
io_return_t	clockpitopen();
io_return_t	clockpitgetstat();
io_return_t	clockpitsetstat();
io_return_t	clockpitmmap();
int		clockrtsetresolution();

/*
 *	Adjust for PIT clock round off... Ugly, but true...
 */
#define CLOCKPIT_SKEW(res)		(((CLKNUM%(NANOSEC_PER_SEC/res)) \
					       * res) / CLKNUM)
#define CLOCKPIT_DEFAULT_RESOLUTION	(NANOSEC_PER_SEC/HZ - \
					 CLOCKPIT_SKEW((NANOSEC_PER_SEC/HZ)))

#define CLOCKPIT_MAX_RESOLUTION 	(10000000)

/*
 *	Minimum set to 1/2 a millisecond... if you want to play with lower
 *	then change this number.
 */
#define CLOCKPIT_MIN_RESOLUTION		(500000)


#endif	/* _I386AT_CLOCKPIT_H_ */

