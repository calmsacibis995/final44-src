/* 
 * Mach Operating System
 * Copyright (c) 1991,1990 Carnegie Mellon University
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
 * $Log:	db_trace.c,v $
 * Revision 2.7  93/01/14  18:00:23  danner
 * 	Fixed args to db_printsym.c
 * 	[93/01/14            danner]
 * 
 * Revision 2.6  92/01/03  20:32:38  dbg
 * 	Fix trace's test for kernel stack - use state & TH_SWAPPED.
 * 	[91/11/01            dbg]
 * 
 * Revision 2.5  91/10/09  16:18:49  af
 * 	Added parens to initializers for db_regs[].
 * 	[91/10/07            af]
 * 
 * Revision 2.4  91/05/14  17:42:58  mrt
 * 	Correcting copyright
 * 
 * Revision 2.3  91/05/08  13:16:37  dbg
 * 	Add stack_switching support.
 * 	[91/03/06            dbg]
 * 
 * Revision 2.2  90/08/27  22:13:45  dbg
 * 	Fix declaration of db_regs.
 * 	[90/08/20            dbg]
 * 	Fix type declarations.
 * 	[90/08/10  14:37:42  dbg]
 * 
 * 	Created.
 * 	[90/07/25            dbg]
 * 
 */

/*
 * Register list and stack trace for VAX.
 */
#include <mach/boolean.h>
#include <machine/db_machdep.h>

#include <ddb/db_access.h>
#include <ddb/db_sym.h>
#include <ddb/db_variables.h>

#include <kern/thread.h>

/*
 *	Machine register set.
 */
struct db_variable db_regs[] = {
	{ "r0",	(int *)&ddb_regs.r0,	FCN_NULL },
	{ "r1",	(int *)&ddb_regs.r1,	FCN_NULL },
	{ "r2",	(int *)&ddb_regs.r2,	FCN_NULL },
	{ "r3",	(int *)&ddb_regs.r3,	FCN_NULL },
	{ "r4",	(int *)&ddb_regs.r4,	FCN_NULL },
	{ "r5",	(int *)&ddb_regs.r5,	FCN_NULL },
	{ "r6",	(int *)&ddb_regs.r6,	FCN_NULL },
	{ "r7",	(int *)&ddb_regs.r7,	FCN_NULL },
	{ "r8",	(int *)&ddb_regs.r8,	FCN_NULL },
	{ "r9",	(int *)&ddb_regs.r9,	FCN_NULL },
	{ "r10", (int *)&ddb_regs.r10,	FCN_NULL },
	{ "r11", (int *)&ddb_regs.r11,	FCN_NULL },
	{ "ap",	(int *)&ddb_regs.ap,	FCN_NULL },
	{ "fp",	(int *)&ddb_regs.fp,	FCN_NULL },
	{ "sp",	(int *)&ddb_regs.sp,	FCN_NULL },
	{ "pc",	(int *)&ddb_regs.pc,	FCN_NULL },
	{ "psl", (int *)&ddb_regs.ps,	FCN_NULL }
};
struct db_variable *db_eregs = db_regs + sizeof(db_regs)/sizeof(db_regs[0]);

/*
 *	Frame tracing.
 */
#define	INKERNEL(va)	(((vm_offset_t)(va)) >= VM_MIN_KERNEL_ADDRESS)

db_addr_t	db_trap_symbol_value = 0;
boolean_t	db_trace_symbols_found = FALSE;

void
db_find_trace_symbols()
{
	db_expr_t	value;

	if (db_value_of_name("_trap", &value))
	    db_trap_symbol_value = (db_addr_t) value;
	db_trace_symbols_found = TRUE;
}

struct vax_call_frame {
	int	(*f_handler)();		/* exception handler */
	short	f_psw;			/* saved psw */
	short	f_mask;			/* register save mask */
	int	*f_ap;			/* saved argument pointer */
	struct vax_call_frame *
		f_fp;			/* saved frame pointer */
	char *	f_pc;			/* saved PC */
};

void
db_stack_trace_cmd(addr, have_addr, count, modif)
	db_expr_t	addr;
	boolean_t	have_addr;
	db_expr_t	count;
	char		*modif;
{
	register struct vax_call_frame *frame;
	register char	*argp;
	db_addr_t	callpc;
	struct vax_call_frame *lastframe;
	int		kernel_only = TRUE;
	int		trace_thread = FALSE;

	if (!db_trace_symbols_found)
	    db_find_trace_symbols();

	{
	    register char *cp = modif;
	    register char c;

	    while ((c = *cp++) != 0) {
		if (c == 't')
		    trace_thread = TRUE;
		if (c == 'u')
		    kernel_only = FALSE;
	    }
	}

	if (count == -1)
	    count = 65535;

	if (!have_addr) {
	    argp   = (char *) ddb_regs.ap;
	    frame  = (struct vax_call_frame *) ddb_regs.fp;
	    callpc = (db_addr_t) ddb_regs.pc;
	}
	else if (trace_thread) {
	    register thread_t th;
	    register pcb_t t_pcb;
	    int		state;

	    th = (thread_t) addr;
	    t_pcb = (pcb_t) db_get_value((db_addr_t)&th->pcb,
					sizeof(pcb_t),
					FALSE);

	    /*
	     * Check state to test whether thread has a kernel stack.
	     */
	    state = db_get_value((int)&th->state, 4, FALSE);
	    if ((state & TH_SWAPPED) == 0) {

		/*
		 * Has a stack.  Get call frame from kernel_state.
		 */
		register struct vax_kernel_state *vks;

		vks = (struct vax_kernel_state *)
			db_get_value((db_addr_t)&t_pcb->vks_p,
					sizeof(int),
					FALSE);
		argp = (char *)
			db_get_value((db_addr_t)&vks->ap,
					sizeof(int),
					FALSE);
		frame = (struct vax_call_frame *)
			db_get_value((db_addr_t)&vks->fp,
					sizeof(int),
					FALSE);
		callpc = (db_addr_t)
			db_get_value((db_addr_t)&vks->pc,
					sizeof(int),
					FALSE);
	    }
	    else {
		/*
		 * No stack.  Only have user register state.
		 */
		argp = (char *)
			db_get_value((db_addr_t)&t_pcb->vss.ap,
					sizeof(int),
					FALSE);
		frame = (struct vax_call_frame *)
			db_get_value((db_addr_t)&t_pcb->vss.fp,
					sizeof(int),
					FALSE);
		callpc = (db_addr_t)
			db_get_value((db_addr_t)&t_pcb->vss.pc,
					sizeof(int),
					FALSE);
	    }
	}
	else {
	    register int mask, regmask;

	    frame = (struct vax_call_frame *) addr;
	    callpc = (db_addr_t) db_get_value((db_addr_t)&frame->f_pc,
					sizeof(int),
					FALSE);	/* pc from call frame */
	    /*
	     * If calls, arglist is after frame + regs + alignment
	     */
	    mask = db_get_value((db_addr_t)&frame->f_mask,
					sizeof(short), FALSE);
	    if (mask & 0x2000) {
		/* callS frame */
		argp = (char *)(frame + 1);	/* end of frame */
		regmask = mask & 0x0fff;	/* saved registers */
		while (regmask & 1) {
		    argp += sizeof(int);
		    regmask >>= 1;
		}
		argp += (mask >> 14) & 0x3;	/* alignment bits */
	    }
	    else {
		/* have no idea what argptr is */
		argp = 0;	/* no args */
	    }
	}

	lastframe = 0;
	while (count-- && frame != 0) {
	    char *	name;
	    db_expr_t	offset;
	    register int narg;
	    boolean_t	is_trap;

	    if (INKERNEL(frame) && callpc == db_trap_symbol_value) {
		narg = 5;
		is_trap = TRUE;
	    }
	    else {
		is_trap = FALSE;
		if (argp == 0)
		    narg = 0;
		else
		    narg = db_get_value((db_addr_t)argp,
					sizeof(char),
					FALSE);
	    }

	    db_find_sym_and_offset(callpc, &name, &offset);
	    db_printf("%s(", name);

	    while (narg) {
		argp += sizeof(int);
		db_printf("%x", db_get_value((db_addr_t)argp,
					     sizeof(int),
					     FALSE));
		if (--narg != 0)
		    db_printf(",");
	    }
	    db_printf(") at ");
	    db_printsym(callpc,DB_STGY_ANY);
	    db_printf("\n");

	    lastframe = frame;
	    argp = (char *)
			db_get_value((db_addr_t)&lastframe->f_ap,
					sizeof(int), FALSE);
	    frame = (struct vax_call_frame *)
			db_get_value((db_addr_t)&lastframe->f_fp,
					sizeof(int), FALSE);
	    if (is_trap)
		callpc = (db_addr_t)
			db_get_value((db_addr_t)(argp + 16),
					sizeof(int), FALSE);
	    else
		callpc = (db_addr_t)
			db_get_value((db_addr_t)&lastframe->f_pc,
					sizeof(int), FALSE);

	    if (frame == 0) {
		/* end of frame chain */
		break;
	    }
	    if (INKERNEL(frame)) {
		/* staying in kernel */
		if ((vm_offset_t)frame <= (vm_offset_t)lastframe) {
		    db_printf("Bad frame pointer: 0x%x\n", frame);
		    break;
		}
	    }
	    else if (INKERNEL(lastframe)) {
		/* switch from user to kernel */
		if (kernel_only)
		    break;		/* kernel stack only */
	    }
	    else {
		/* in user */
		if ((vm_offset_t)frame <= (vm_offset_t)lastframe) {
		    db_printf("Bad frame pointer: 0x%x\n", frame);
		    break;
		}
	    }
	}
}
