/* 
 * Mach Operating System
 * Copyright (c) 1994 Carnegie Mellon University
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
 * $Log:	int_frame.h,v $
 * Revision 2.2  94/12/15  15:24:21  dbg
 * 	Created.
 * 	[94/06/06            dbg]
 * 
 */

#ifndef	_I386_INT_FRAME_H_
#define	_I386_INT_FRAME_H_

#include <platforms.h>

#include <i386/eflags.h>
#include <i386/machspl.h>

/*
 *	Interrupt frame pushed on stack.
 *
 *	An interrupt routine is called as:
 *
 *	void	(*interrupt)(int iunit, struct int_frame if)
 */

struct int_regs {
	int	es;
	int	ds;
	int	edx;
	int	ecx;
	int	eax;
	int	eip;
	int	cs;
	int	efl;
};

struct int_frame {
#ifdef	PS2
	int		ivec;		/* interrupt number */
#endif
	spl_t		old_spl;	/* interrupted SPL */
	char *		ret_addr;	/* return address to lowest-level
					   assembly routine */
	struct int_regs	*regs;		/* pointer to saved registers */
};

extern char	return_to_iret[];	/* if ret_addr is return_to_iret,
					   ir is valid.  Otherwise, we
					   have been called from within
					   another interrupt routine. */
#define	USERMODE(if) \
	((if).ret_addr == return_to_iret && \
	    ((if.regs->efl & EFL_VM) != 0 || (if.regs->cs & 0x3) != 0))

#endif	/* _I386_INT_FRAME_H_ */
