/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*	@(#)kern_sig.c 1.1 86/02/03 SMI; from UCB 5.23 83/06/24	*/
/*
 * HISTORY
 * $Log:	core.c,v $
 * Revision 2.7  89/07/11  13:55:00  jjc
 * 	Modified for sparc.
 * 	[88/07/05            jjc]
 * 
 * Revision 2.6  89/04/22  15:30:46  gm0w
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	[89/04/18            gm0w]
 * 
 * Revision 2.5  89/03/09  21:29:55  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  19:27:59  gm0w
 * 	Removed else legs of MACH and CMU conditionals and fixed 
 * 	includes as part of kernel cleanup.
 * 	[89/02/08            jjc]
 * 
 * Revision 2.3  89/01/18  01:10:23  jsb
 * 	Vnode support.
 * 	[89/01/17  10:53:06  jsb]
 *
 * 16-Feb-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Changed sun_core() to dump FPA registers if pcb_fpa_flags
 *	has the used bit on not just if it's nonzero because it is
 *	used to indicate other things too.
 *
 * 12-Nov-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added code to dump FPA data registers if FPA microcode is
 *	loaded.
 *
 * 31-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Support for MACH_TT.
 *
 * 05-Mar-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Created from Sun's version of core().
 *
 */ 
/*	@(#)kern_sig.c 1.1 86/02/03 SMI; from UCB 5.23 83/06/24	*/

#include <kern/thread.h>

#include <sys/param.h>
#include <sys/user.h>
#include <sys/inode.h>
#include <vm/vm_kern.h>
#include <sun/core.h>
#include <fpa.h>
#if	NFPA > 0
#include <sundev/fpareg.h>
#endif	NFPA > 0


/*
 *	Write Sun's core structure at beginning of core file
 */
sun_core(ip, offset)
struct inode	*ip;
off_t		*offset;
{
	register struct core		*corep;
	register struct fp_status	*fp_status;
	int				len;
	register struct pcb		*pcb;

#ifdef sun4
        flush_user_windows();   /* flush user register windows to stack */
#endif
	/*
	 * Dump the specific areas of the u area into the new
	 * core structure for examination by debuggers.  The
	 * new format is now independent of the user structure and
	 * only the information needed by the debuggers is included.
	 */
	corep = (struct core *)kmem_alloc_pageable(kernel_map, sizeof (struct core));
	bzero((caddr_t)corep, sizeof (struct core));
	corep->c_magic = CORE_MAGIC;
	corep->c_len = sizeof (struct core);
	corep->c_regs = *(struct regs *)u.u_ar0;
	pcb = current_thread()->pcb;
#if	sparc
	corep->c_fpu = pcb->pcb_fpu;
#else	sparc
	fp_status = &pcb->pcb_fp_status;
	fp_status->fps_flags = EXT_FPS_FLAGS(&pcb->pcb_fp_istate);
	fp_status->fps_code = u.u_code;
	corep->c_fpstatus = *fp_status;
#endif	sparc

#if	NFPA > 0
	/*
	 * Dump FPA regs only when pcb->pcb_fpa_flags indicate that the
	 * FPA is being used and FPA_LOAD_BIT is off.
	 * The reason is that if FPA_LOAD_BIT is on, it means that there
	 * is no microcode in FPA board, we cannot access FPA data regs.
	 */
	corep->c_fparegs.fpar_flags = pcb->pcb_fpa_flags;
	if ((pcb->pcb_fpa_flags & FPA_USED) &&
	    !(fpa->fp_state & FPA_LOAD_BIT)) {
		/* loop until FPA pipe become stable */
		CDELAY(fpa->fp_pipe_status & FPA_STABLE, 300);
		if (fpa->fp_pipe_status & FPA_STABLE) {
			corep->c_fparegs.fpar_status =
			    *((struct fpa_status *) &fpa->fp_state);
			fpa->fp_clear_pipe = 0; /* clear pipe to read data */
			bcopy((char *)fpa->fp_data,
			    (char *)corep->c_fparegs.fpar_data,
			    sizeof (fpa->fp_data));
		} else {
			fpa_shutdown();
			printf("FPA not stable in core(), FPA is shutdown!\n");
		}
	}
#endif	NFPA > 0
	corep->c_aouthdr = pcb->pcb_exec;
	corep->c_signo = u.u_arg[0];
	corep->c_tsize = ctob(u.u_tsize);
	corep->c_dsize = ctob(u.u_dsize);

	corep->c_ssize = ctob(u.u_ssize);
	len = min(MAXCOMLEN, CORE_NAMELEN);
	(void) strncpy(corep->c_cmdname, u.u_comm, len);
	corep->c_cmdname[len] = '\0';
	u.u_error = RDWRI(UIO_WRITE, ip,
	    (caddr_t)corep, sizeof (struct core),
	    0, 1, (int *)0);
	*offset += sizeof (struct core);
	kmem_free(kernel_map, (caddr_t)corep, sizeof (struct core));
}
