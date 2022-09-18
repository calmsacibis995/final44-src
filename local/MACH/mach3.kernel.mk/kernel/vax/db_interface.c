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
 * $Log:	db_interface.c,v $
 * Revision 2.8  92/04/08  22:39:14  rpd
 * 	Added task argument to db_read_bytes and db_write_bytes.
 * 	[92/04/08            rpd]
 * 
 * Revision 2.7  92/01/03  20:32:34  dbg
 * 	Ignore RB_KDB - always enter DDB.
 * 	[91/09/12            dbg]
 * 
 * Revision 2.6  91/05/14  17:42:42  mrt
 * 	Correcting copyright
 * 
 * Revision 2.5  91/05/08  13:16:17  dbg
 * 	Pass regs structure directly to kdb_trap.
 * 	[91/03/21            dbg]
 * 
 * Revision 2.4  91/03/16  15:02:09  rpd
 * 	Replaced db_nofault with db_recover.
 * 	[91/03/14            rpd]
 * 
 * Revision 2.3  90/10/25  14:49:06  rwd
 * 	Added watchpoint support.
 * 	[90/10/18            rpd]
 * 
 * Revision 2.2  90/08/27  22:13:36  dbg
 * 	Reduce lint.
 * 	[90/08/07            dbg]
 * 	Created.
 * 	[90/07/25            dbg]
 * 
 */

/*
 * Interface to new debugger.
 */
#include <sys/reboot.h>
#include <vm/pmap.h>
#include <kern/thread.h>
#include <ddb/db_task_thread.h>

#include <vax/thread.h>
#include <vax/db_machdep.h>
#include <vax/trap.h>
#include <vax/mtpr.h>
#include <vax/setjmp.h>

int	db_active = 0;

/*
 * Received keyboard interrupt sequence.
 */
kdb_kintr()
{
	if (db_active == 0) {
	    printf("\n\nkernel: keyboard interrupt\n");
	    mtpr(SIRR, 0xf);
	}
}

/*
 *  kdb_trap - field a TRACE or BPT trap
 */

extern jmp_buf_t *db_recover;

kdb_trap(regs)
    register struct vax_saved_state *regs;
{
    int	exception, code;

    exception = regs->exception;
    code = regs->code;

    switch (exception)
    {
	case EXC_BREAKPOINT:	/* breakpoint */
	case T_KDB_ENTRY:	/* keyboard interrupt */
	case T_WATCHPOINT:	/* watchpoint */
	    break;

	default:
	{
	    kdbprinttrap(exception, code);
	    if (db_recover != 0) {
		db_printf("Caught exception in ddb.\n");
		db_error("");
		/*NOTREACHED*/
	    }
	}
    }

    /*  Should switch to kdb`s own stack here. */

    ddb_regs.r0  = regs->r0;
    ddb_regs.r1  = regs->r1;
    ddb_regs.r2  = regs->r2;
    ddb_regs.r3  = regs->r3;
    ddb_regs.r4  = regs->r4;
    ddb_regs.r5  = regs->r5;
    ddb_regs.r6  = regs->r6;
    ddb_regs.r7  = regs->r7;
    ddb_regs.r8  = regs->r8;
    ddb_regs.r9  = regs->r9;
    ddb_regs.r10 = regs->r10;
    ddb_regs.r11 = regs->r11;
    ddb_regs.ap  = regs->ap;
    ddb_regs.fp  = regs->fp;
    if (USERMODE(regs->psl)) {
	/*
	 * User mode - get stack pointer from machine
	 */
	ddb_regs.sp = mfpr(USP);
    }
    else {
	/*
	 * Kernel mode - stack pointer is above save area
	 */
	ddb_regs.sp = (int) (regs+1);
    }
    ddb_regs.pc  = regs->pc;
    ddb_regs.ps  = regs->psl;

    db_active++;
    cnpollc(TRUE);
    db_trap(exception, code);
    cnpollc(FALSE);
    db_active--;

    regs->r0  = ddb_regs.r0;
    regs->r1  = ddb_regs.r1;
    regs->r2  = ddb_regs.r2;
    regs->r3  = ddb_regs.r3;
    regs->r4  = ddb_regs.r4;
    regs->r5  = ddb_regs.r5;
    regs->r6  = ddb_regs.r6;
    regs->r7  = ddb_regs.r7;
    regs->r8  = ddb_regs.r8;
    regs->r9  = ddb_regs.r9;
    regs->r10 = ddb_regs.r10;
    regs->r11 = ddb_regs.r11;
    regs->ap  = ddb_regs.ap;
    regs->fp  = ddb_regs.fp;
    if (USERMODE(regs->psl)) {
	/*
	 * User mode - get stack pointer from machine
	 */
	mtpr(USP, ddb_regs.sp);
    }
    else {
	/*
	 * Kernel mode - can`t change stack pointer
	 */
    }
    regs->pc  = ddb_regs.pc;
    regs->psl = ddb_regs.ps;

    return(1);
}

char *exception_type[] = {
	"",
	"bad access",
	"bad instruction",
	"arithmetic error",
	"emulation",
	"software trap",
	"breakpoint"
};
int  exception_count = sizeof(exception_type)/sizeof(exception_type[0]);

/*
 * Print trap reason.
 */
kdbprinttrap(exception, code)
	int	exception, code;
{
	printf("kernel: ");
	if ((unsigned) exception >= exception_count)
	    printf("type %d", exception);
	else
	    printf("%s", exception_type[exception]);
	printf(" trap, code=%x\n", code);
}

/*
 * Read bytes from kernel address space for debugger.
 */
void
db_read_bytes(addr, size, data, task)
	vm_offset_t	addr;
	register int	size;
	register char	*data;
	task_t		task;
{
	register char	*src;

	if (!db_is_current_task(task))
	    return;

	src = (char *)addr;
	while (--size >= 0)
	    *data++ = *src++;
}

/*
 * Write bytes to kernel address space for debugger.
 */
void
db_write_bytes(addr, size, data, task)
	vm_offset_t	addr;
	register int	size;
	register char	*data;
	task_t		task;
{
	register char	*dst;

	register struct pt_entry *ptep0 = 0;
	struct pt_entry	oldmap0;
	vm_offset_t	addr1;
	register struct pt_entry *ptep1 = 0;
	struct pt_entry	oldmap1;
	extern char	etext;

	if (!db_is_current_task(task))
	    return;

	if (addr >= VM_MIN_KERNEL_ADDRESS &&
	    addr <= (vm_offset_t)&etext)
	{
	    ptep0 = pmap_pte(kernel_pmap, addr);
	    oldmap0 = *ptep0;
	    ptep0->prot = VAX_KW;
	    mtpr(TBIS, (int)addr);

	    addr1 = vax_trunc_page(addr + size - 1);
	    if (vax_trunc_page(addr) != addr1) {
		/* data crosses a page boundary */

		ptep1 = pmap_pte(kernel_pmap, addr1);
		oldmap1 = *ptep1;
		ptep1->prot = VAX_KW;
		mtpr(TBIS, (int)addr1);
	    }
	}

	dst = (char *)addr;

	while (--size >= 0)
	    *dst++ = *data++;

	if (ptep0) {
	    *ptep0 = oldmap0;
	    mtpr(TBIS, (int)addr);
	    if (ptep1) {
		*ptep1 = oldmap1;
		mtpr(TBIS, (int)addr1);
	    }
	}
}


