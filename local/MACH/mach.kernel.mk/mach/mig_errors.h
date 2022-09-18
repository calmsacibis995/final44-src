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
 * $Log:	mig_errors.h,v $
 * Revision 2.6  90/07/03  16:39:02  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  17:55:56  mrt]
 * 
 * Revision 1.8  89/11/30  17:49:44  mrt
 * 	Changed one more instance of hc to __HC__
 * 	[89/11/30            pds]
 * 
 * Revision 1.7  89/05/20  22:17:01  mrt
 * 	Source in kernel/mach/mig_errors.h
 * 
 * Revision 2.5  89/03/09  20:21:26  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  18:38:41  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  89/02/07  01:01:21  mwyoung
 * Relocated from sys/mig_errors.h
 * 
 * Revision 2.2  88/07/20  21:05:51  rpd
 * Added definition of mig_symtab_t.
 * 
 *  2-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added MIG_ARRAY_TOO_LARGE.
 *
 * 25-May-87  Richard Draves (rpd) at Carnegie-Mellon University
 *	Added definition of death_pill_t.
 *
 * 31-Jul-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Created.
 *
 */
/*
 * Mach Interface Generator errors
 *
 */

#ifndef	_MACH_MIG_ERRORS_H_
#define _MACH_MIG_ERRORS_H_

#include <mach/kern_return.h>
#include <mach/message.h>

#define MIG_TYPE_ERROR		-300		/* Type check failure */
#define MIG_REPLY_MISMATCH	-301		/* Wrong return message ID */
#define MIG_REMOTE_ERROR	-302		/* Server detected error */
#define MIG_BAD_ID		-303		/* Bad message ID */
#define MIG_BAD_ARGUMENTS	-304		/* Server found wrong arguments */
#define MIG_NO_REPLY		-305		/* Server shouldn't reply */
#define MIG_EXCEPTION		-306		/* Server raised exception */
#define MIG_ARRAY_TOO_LARGE	-307		/* User specified array not large enough
						   to hold returned array */

typedef struct {
	msg_header_t	Head;
	msg_type_t	RetCodeType;
	kern_return_t	RetCode;
} death_pill_t;

typedef struct mig_symtab {
	char	*ms_routine_name;
	int	ms_routine_number;
#if	(defined(__STDC__) || defined(c_plusplus)) || defined(__HC__)
	void
#else
	int
#endif
		(*ms_routine)();
} mig_symtab_t;

#endif	_MACH_MIG_ERRORS_H_
