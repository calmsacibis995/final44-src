/* 
 * Mach Operating System
 * Copyright (c) 1993-1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	exec.c,v $
 * Revision 2.3  93/02/04  10:41:00  mrt
 * 	Changed mach/mach.h to mach.h.
 * 	[93/02/04            mrt]
 * 
 * Revision 2.2  92/01/03  19:58:26  dbg
 * 	Moved outside of kernel.
 * 	[91/09/04            dbg]
 * 
 * Revision 2.5  91/07/31  18:18:25  dbg
 * 	Changed get_symtab to copy out the size of the symbol table and
 * 	return the symbol table size + string table size.
 * 	[91/07/31            dbg]
 * 
 * Revision 2.4  90/08/27  22:14:00  dbg
 * 	Add get_symtab to find symbol table in file.
 * 	[90/08/20            dbg]
 * 	Use new error names.  Use new file_io package.
 * 	[90/07/16            dbg]
 * 
 * Revision 2.3  90/06/02  15:08:06  rpd
 * 	Converted to new IPC.
 * 	[90/03/26  23:03:23  rpd]
 * 
 * Revision 2.2  90/01/11  11:45:26  dbg
 * 	De-linted.
 * 	[90/01/03            dbg]
 * 
 * Revision 2.1  89/08/03  16:32:06  rwd
 * Created.
 * 
 *  3-Mar-89  David Golub (dbg) at Carnegie-Mellon University
 *	Created.
 *
 */
/*
 * VAX-specific routines for loading a.out files.
 */

#include <mach.h>
#include <mach/machine/vm_param.h>

#include "file_io.h"
#include "loader_info.h"

#include <vax/exec.h>

/*
 *	Machine-dependent portions of execve() for the VAX.
 */

#define	LOADER_PAGE_SIZE	(1024)
#define loader_round_page(x)	((vm_offset_t)((((vm_offset_t)(x)) \
						+ LOADER_PAGE_SIZE - 1) \
					& ~(LOADER_PAGE_SIZE-1)))

int ex_get_header(fp, lp)
	struct file *fp;
	register struct loader_info *lp;
{
	struct exec	x;
	register int	result;
	vm_size_t	resid;

	result = read_file(fp, 0, (vm_offset_t)&x, sizeof(x), &resid);
	if (result)
		return (result);
	if (resid)
		return (EX_NOT_EXECUTABLE);

	switch ((int)x.a_magic) {

	    case 0407:
		lp->text_start  = 0;
		lp->text_size   = 0;
		lp->text_offset = 0;
		lp->data_start  = 0;
		lp->data_size   = x.a_text + x.a_data;
		lp->data_offset = sizeof(struct exec);
		lp->bss_size    = x.a_bss;
		break;

	    case 0410:
		if (x.a_text == 0) {
			return(EX_NOT_EXECUTABLE);
		}
		lp->text_start  = 0;
		lp->text_size   = loader_round_page(x.a_text);
		lp->text_offset = sizeof(struct exec);
		lp->data_start  = loader_round_page(x.a_text);
		lp->data_size   = loader_round_page(x.a_data);
		lp->data_offset = lp->text_offset + lp->text_size;
		lp->bss_size    = loader_round_page(x.a_bss);
		break;

	    case 0413:
		if (x.a_text == 0) {
			return(EX_NOT_EXECUTABLE);
		}
		lp->text_start  = 0;
		lp->text_size   = loader_round_page(x.a_text);
		lp->text_offset = 1024;
		lp->data_start  = loader_round_page(x.a_text);
		lp->data_size   = loader_round_page(x.a_data);
		lp->data_offset = lp->text_offset + lp->text_size;
		lp->bss_size    = loader_round_page(x.a_bss);
		break;
	    default:
		return (EX_NOT_EXECUTABLE);
	}
	lp->entry_1 = x.a_entry + 2;
	lp->entry_2 = 0;

	return(0);
}

#define	STACK_SIZE	(64*1024)

char *set_regs(user_task, user_thread, lp, arg_size)
	mach_port_t	user_task;
	mach_port_t	user_thread;
	struct loader_info *lp;
	int		arg_size;
{
	vm_offset_t	stack_start;
	vm_offset_t	stack_end;
	struct vax_thread_state	regs;
	unsigned int		reg_size;

	/*
	 * Allocate stack.
	 */
	stack_end = VM_MAX_ADDRESS;
	stack_start = VM_MAX_ADDRESS - STACK_SIZE;
	(void)vm_allocate(user_task,
			  &stack_start,
			  (vm_size_t)(stack_end - stack_start),
			  FALSE);

	reg_size = VAX_THREAD_STATE_COUNT;
	(void)thread_get_state(user_thread,
				VAX_THREAD_STATE,
				(thread_state_t)&regs,
				&reg_size);

	regs.pc = lp->entry_1;
	regs.sp = (int)((stack_end - arg_size) & ~(sizeof(int)-1));

	(void)thread_set_state(user_thread,
				VAX_THREAD_STATE,
				(thread_state_t)&regs,
				reg_size);

	return ((char *)regs.sp);
}

boolean_t
get_symtab(fp, symoff_p, symsize_p, header, header_size)
	struct file	*fp;
	vm_offset_t	*symoff_p;	/* out */
	vm_size_t	*symsize_p;	/* out */
	char		header[];	/* out array */
	vm_size_t	*header_size;	/* out */
{
	register int		result;
	vm_offset_t		resid;
	vm_offset_t		sym_off;
	vm_offset_t		str_off;
	vm_size_t		sym_size;
	vm_size_t		str_size;
	struct exec		x;

	result = read_file(fp, 0, (vm_offset_t)&x, sizeof(x), &resid);
	if (result || resid)
	    return (FALSE);

	sym_off = ((x.a_magic == ZMAGIC) ? 1024 : sizeof(struct exec))
		  + x.a_text + x.a_data + x.a_trsize + x.a_drsize;
	sym_size = x.a_syms;
	str_off  = sym_off + sym_size;
	result = read_file(fp, str_off,
			&str_size, sizeof(int), &resid);
	if (result || resid)
	    return (FALSE);

	/*
	 * Return the entire symbol table + string table.
	 * Add a header:
	 *   size of symbol table
	 */

	*symoff_p = sym_off;
	*symsize_p = sym_size + str_size;
	*(int *)header = sym_size;
	*header_size = sizeof(int);

	return (TRUE);
}
