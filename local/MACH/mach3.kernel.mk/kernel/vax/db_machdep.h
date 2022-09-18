/* 
 * Mach Operating System
 * Copyright (c) 1993-1990 Carnegie Mellon University
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
 * $Log:	db_machdep.h,v $
 * Revision 2.8  93/01/24  14:14:55  danner
 * 	Say we only support a.out files.
 * 	[93/01/18            mrt]
 * 
 * Revision 2.7  92/04/08  22:39:07  rpd
 * 	Added DB_ACCESS_LEVEL.
 * 	[92/04/08            rpd]
 * 
 * Revision 2.6  91/05/14  17:42:52  mrt
 * 	Correcting copyright
 * 
 * Revision 2.5  91/05/08  13:16:26  dbg
 * 	Changed to new copyright.
 * 	[91/04/25            dbg]
 * 
 * Revision 2.4  91/01/08  15:55:21  rpd
 * 	Added dummy inst_load/inst_store macros.
 * 	[91/01/06            rpd]
 * 
 * Revision 2.3  90/10/25  14:49:12  rwd
 * 	Added watchpoint support.
 * 	[90/10/18            rpd]
 * 
 * Revision 2.2  90/08/27  22:13:40  dbg
 * 	Created.
 * 	[90/07/25            dbg]
 * 
 */

/*
 * Machine-dependent defines for new kernel debugger.
 */
#ifndef	_VAX_DB_MACHDEP_H_
#define	_VAX_DB_MACHDEP_H_

#include <mach/vax/vm_types.h>
#include <mach/vax/vm_param.h>
#include <mach/vax/thread_status.h>
#include <mach/exception.h>
#include <vax/psl.h>
#include <vax/trap.h>

typedef	vm_offset_t	db_addr_t;	/* address - unsigned */
typedef	int		db_expr_t;	/* expression - signed */

typedef struct vax_thread_state db_regs_t;
db_regs_t	ddb_regs;	/* register state */
#define DDB_REGS	(&ddb_regs)

#define PC_REGS(regs)	((db_addr_t)(regs)->pc)

#define	BKPT_INST	0x03		/* breakpoint instruction */
#define	BKPT_SIZE	(1)		/* size of breakpoint inst */
#define	BKPT_SET(inst)	(BKPT_INST)

/* #define FIXUP_PC_AFTER_BREAK */

#define	db_clear_single_step(regs)	((regs)->ps &= ~PSL_T)
#define	db_set_single_step(regs)	((regs)->ps |=  PSL_T)

#define	IS_BREAKPOINT_TRAP(type, code)	\
		((type) == EXC_BREAKPOINT && (code) == EXC_VAX_BPT)
#define	IS_WATCHPOINT_TRAP(type, code)	\
		((type) == T_WATCHPOINT)

#define	I_CALLG		0xfa
#define	I_CALLS		0xfb
#define	I_RET		0x04
#define	I_REI		0x02

#define	inst_trap_return(ins)	(((ins)&0xff) == I_REI)
#define	inst_return(ins)	(((ins)&0xff) == I_RET)
#define	inst_call(ins)		(((ins)&0xff) == I_CALLS || \
				 ((ins)&0xff) == I_CALLG)
#define inst_load(ins)		0
#define inst_store(ins)		0

#define DB_ACCESS_LEVEL		DB_ACCESS_CURRENT

/* only a.out symbol tables */
 
#define DB_NO_COFF		1

#endif	/* _VAX_DDB_MACHDEP_H_ */
