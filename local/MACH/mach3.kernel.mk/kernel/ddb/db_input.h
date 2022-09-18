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
 * $Log:	db_input.h,v $
 * Revision 2.2  93/11/17  19:12:09  dbg
 * 	Created.
 * 	[93/10/08            dbg]
 * 
 */

/*
 * Input routines for kernel debugger.
 */

#ifndef	_DDB_DB_INPUT_H_
#define	_DDB_DB_INPUT_H_

/*
 * Read a line of input into the supplied buffer.
 */
extern int
db_readline(
	char *	lstart,
	int	lsize);

/*
 * Check for interrupts during long computation or output.
 */
extern void
db_check_interrupt(void);

#endif	/* _DDB_DB_INPUT_H_ */
