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
 * $Log:	db_macro.h,v $
 * Revision 2.2  93/11/17  19:12:00  dbg
 * 	Created.
 * 	[93/10/07            dbg]
 * 
 */

#ifndef	_DDB_DB_MACRO_H_
#define	_DDB_DB_MACRO_H_

/*
 *	Debugger macro package.
 */

#include <mach/boolean.h>
#include <machine/db_machdep.h>
#include <ddb/db_variables.h>

extern void
db_def_macro_cmd();

extern void
db_del_macro_cmd();

extern void
db_show_macro();

extern void
db_clear_macro_level(void);

extern boolean_t
db_exec_macro(
	const char *	name);

extern void
db_arg_variable(
	struct db_variable	*vp,
	db_expr_t		*valuep,
	int			flag,
	db_var_aux_param_t	ap);

#endif	/* _DDB_DB_MACRO_H_ */
