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
 * $Log:	db_examine.h,v $
 * Revision 2.2  93/11/17  19:12:17  dbg
 * 	Created.
 * 	[93/10/13            dbg]
 * 
 */

/*
 *	Data examination and modification commands.
 */
#ifndef	_DDB_DB_EXAMINE_H_
#define	_DDB_DB_EXAMINE_H_

extern void
db_examine_cmd(
	db_expr_t	addr,
	int		have_addr,
	db_expr_t	count,
	char *		modif);

extern void
db_examine_forward(
	db_expr_t	addr,
	int		have_addr,
	db_expr_t	count,
	char *		modif);

extern void
db_examine_backward(
	db_expr_t	addr,
	int		have_addr,
	db_expr_t	count,
	char *		modif);

extern void
db_print_cmd();

extern void
db_search_cmd();

extern void
db_write_cmd(
	db_expr_t	addr,
	int		have_addr,
	db_expr_t	count,
	char *		modif);

extern void
db_print_loc_and_inst(
	db_addr_t	loc,
	task_t		task);


#endif	/* _DDB_DB_EXAMINE_H_ */

