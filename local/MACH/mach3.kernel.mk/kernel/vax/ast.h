/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988 Carnegie Mellon University
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
 * $Log:	ast.h,v $
 * Revision 2.7  93/02/01  09:51:46  danner
 * 	Include gcc_asm.h
 * 
 * Revision 2.6  91/05/14  17:41:09  mrt
 * 	Correcting copyright
 * 
 * Revision 2.5  91/05/08  13:10:19  dbg
 * 	Import mtpr and AST register definitions from mtpr.h.
 * 	[91/03/21            dbg]
 * 
 * Revision 2.4  91/03/16  15:01:42  rpd
 * 	Updated for the new AST interface.
 * 	[91/03/13            rpd]
 * 
 * Revision 2.3  90/06/02  15:07:56  rpd
 * 	Cleaned up.
 * 	[90/03/26  23:02:26  rpd]
 * 
 * Revision 2.2  90/01/11  11:44:39  dbg
 * 	Make ast_propagate more palatable to lint.
 * 	[89/12/06            dbg]
 * 
 * Revision 2.1  89/08/03  16:13:26  rwd
 * Created.
 * 
 *  6-Sep-88  David Golub (dbg) at Carnegie-Mellon University
 *	Merged with David Black's new AST mechanism.
 *
 * 19-Jul-88  David Golub (dbg) at Carnegie-Mellon University
 *	Created.
 *
 */
/*
 *	AST definitions for VAX.
 */

#ifndef	_VAX_AST_H_
#define	_VAX_AST_H_

#include <vax/mtpr.h>

#define	MACHINE_AST
			/* VAX has its own AST mechanism */

#define	VAX_AST_USER	3
#define	VAX_AST_NONE	4

#define	aston(mycpu)	(mtpr(ASTLVL, VAX_AST_USER))
#define	astoff(mycpu)	(mtpr(ASTLVL, VAX_AST_NONE))

#include <vax/gcc_asm.h>
#endif	_VAX_AST_H_
