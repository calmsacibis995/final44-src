/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	fpa.c,v $
 * Revision 2.5  89/07/11  17:38:21  jjc
 * 	Changed to include machine dependent header files from machine/ not sun3/ because the Sun 4 uses this device driver too.
 * 	[89/07/06  16:52:44  jjc]
 * 
 * Revision 2.4  89/03/09  21:41:30  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:51:03  gm0w
 * 	Added new copyright and fixed includes as part of kernel
 * 	cleanup.
 * 	[89/02/10            jjc]
 * 
 * 11-Feb-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	1) Removed initialization of the FPA from fpaopen() and 
 *	   fpa_fork_context().  Instead, initialize FPA in trap()
 *	   when the thread first tries to use it.
 *	2) Changed fpa_close() to return if FPA_USED isn't set and
 *	   not to try freeing a FPA context that has been stolen 
 *	   (ie. FPA_CTX_SAVED is on).
 *	3) Cloned fpaclose() into fpaclose_thread() which takes a thread
 *	   as an argument.
 *	4) Changed fpa_alloc_context() to swipe another thread's
 *	   FPA context if all 32 are in use, saving the FPA state of
 *	   the other thread and setting the FPA_CTX_SAVED bit.
 *	5) Added ability to save and restore FPA data registers to
 *	   fpa_save() and fpa_dorestore().
 *	6) Removed fpa_copydata().  Just do it inline in 
 *	   fpa_fork_context().
 *	7) Changed fpa_fork_context() to copy FPA data registers into
 *	   child's pcb instead of allocating a context and putting
 *	   them into the context right away.  Let trap() load them.
 *
 * 12-Nov-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Commented out include of ../h/{vfs,vnode}.h.
 *	Included fs.h and inode.h from ../h instead ../ufs.
 *	Defined FPA_INFORK and FPA_USED instead U_<name>.
 *	Changed fpa_procp to be a table of thread pointers instead of
 *	proc pointers for each context.
 *	Modified fpaopen(), fpaclose(), fpa_save(), fpa_restore(), and
 *	fpa_dorestore() to manipulate the FPA state kept in the pcb
 *	instead of the u-area.
 *	Rewrote fpa_fork_context(), removing code that fiddles with
 *	/dev/fpa and incorporating some FPA specific code from Sun's
 *	version of fork1().
 *	Commented out code in fpa_shutdown() to kill processes using
 *	FPA.
 *
 */
#ifndef	lint
static  char sccsid[] = "@(#)fpa.c 1.1 86/09/25";
#endif

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */

/*
 * Sun Floating Point Accelerator driver
 */

#include <sys/param.h>
#include <sys/user.h>
#include <sys/file.h>
#include <sys/fs.h>
#include <sys/inode.h>
#include <sys/ioctl.h>
#include <sys/buf.h>
#include <sys/conf.h>
#include <sys/proc.h>
#include <sys/systm.h>
#include <sundev/mbvar.h>
#include <sundev/fpareg.h>
#include <machine/enable.h>
#include <vm/vm_kern.h>

int	fpaprobe();

struct mb_device *fpainfo[1];		/* XXX only support one board */

struct mb_driver fpadriver = {
	fpaprobe, 0, 0, 0, 0, 0,
	sizeof (struct fpa_device), "fpa", fpainfo, 0, 0, 0
};

/* fpa_thread[i] points to the thread that is using FPA context i. */
thread_t fpa_thread[FPA_NCONTEXTS];
int	fpa_ncontexts = FPA_NCONTEXTS;
/*
 * Fpa_exist == 0 if FPA does not exist.  Fpa_exist == 1 if there is a
 * functioning FPA attached.  Fpa_exist == -1 if the FPA is disabled
 * due to FPA hardware problems.
 */
short	fpa_exist;
enum fpa_state	fpa_state = FPA_SINGLE_USER;
short	fpa_last_ctx = 0; /* last context number allocated */

extern	u_char enablereg;	/* soft copy of ENABLE register */
extern  short fppstate;		/* whether 68881 exists */
extern	on_enablereg();		/* turn on a bit in enable reg */
extern	off_enablereg();	/* turn off a bit in enable reg */

/*
 * fpaprobe() checks if an FPA is attached.  It assigns the address of
 * FPA to global variable fpa and turns on fpa_exist if the FPA is there.
 */
/*ARGSUSED*/
fpaprobe(reg, unit)
	caddr_t reg;
	int unit;
{
	long i;

	fpa = (struct fpa_device *)reg;
	on_enablereg((u_char)ENA_FPA); /* turn on before access FPA */
	if (peekl((long *)&fpa->fp_ierr, &i) == 0)
		fpa_exist = 1;
	else 
		fpa_exist = 0;
	off_enablereg((u_char)ENA_FPA); /* It'll be truned on by fpaopen */
	return (fpa_exist);
}

/*
 * fpaopen() is called before the first FPA instruction is executed.
 * Does some error checking, but doesn't allocate an FPA context and
 * set up the FPA for this thread.
 * Instead, let the thread fault when it uses the FPA.  Then allocate a
 * context for it and set up the FPA for it to use.
 */
/*ARGSUSED*/
fpaopen(dev, flag, truedev)
	dev_t dev;
	int flag;
	dev_t *truedev;
{
	register int context_no;
	register struct fpa_device *rfpa = fpa;

	if (!fpa_exist){
		fpa_state = FPA_DISABLED;
		return (ENXIO);		/* FPA board not exist */
	}
	if (!fppstate){
		fpa_state = FPA_DISABLED;
		return (ENOENT);	/* 68881 chip not exist */
	}
	if (fpa_state == FPA_DISABLED)
		return (ENETDOWN);	/* FPA is disabled */

	/* Only ONE root can use fpa while in FPA_SINGLE_USER */
	if (fpa_state == FPA_SINGLE_USER)
		if (!suser() || fpa_busy())
			return (EIO);
	return (0);
}

/*
 * fpaioctl() is called to turn on/off the load enable bit and the
 * regram access bit of the FPA STATE register.  Download program
 * calls ioctl() to change state from FPA_SINGLE_USER to FPA_MULTI_USER
 * after the microcode has been downloaded successfully.
 * Also, diagnostic programs disables FPA through ioctl().
 * FPA_GET_DATAREGS is only used by gcore() to read FPA data registers.
 */
/*ARGSUSED*/
fpaioctl(dev, cmd, data, flag)
	dev_t dev;
	int cmd, flag;
	caddr_t data;
{

	if (!suser() && cmd != FPA_GET_DATAREGS)
		return (EPERM);
	if ((fpa->fp_pipe_status & FPA_PIPE_MASK) != FPA_PIPE_CLEAR)
		return (EPIPE);

	switch (cmd) {
	case FPA_ACCESS_ON:
		fpa->fp_state |= FPA_ACCESS_BIT;
		break;
	case FPA_ACCESS_OFF:
		fpa->fp_state &= ~FPA_ACCESS_BIT;
		break;
	case FPA_LOAD_ON:
		fpa->fp_state |= FPA_LOAD_BIT;
		break;
	case FPA_LOAD_OFF:
		fpa->fp_state &= ~FPA_LOAD_BIT;
		break;
	case FPA_GET_DATAREGS: {
			union fpa_qtr_dregs *p = (union fpa_qtr_dregs *)data;
			int count = p->fq_params.fqp_count,
			    state_reg = p->fq_params.fqp_state;

			fpa_get_dataregs(state_reg, count, data);
		}
		break;
	case FPA_FAIL:
		printf(data);
		fpa_shutdown();
		break;
	case FPA_INIT_DONE:
		fpa_state = FPA_MULTI_USER;
		break;
	default:
		return (EINVAL);
	}
	return (0);
}

/*
 * fpaclose() is called when exit() or execve() is called.
 * It marks that this process is not using FPA, runs a destructive
 * RAM test, frees the FPA context, and turns off the FPA enable bit
 * in the ENABLE register.
 */
/*ARGSUSED*/
fpaclose(dev, flag)
	dev_t dev;
	int flag;
{
	short fpa_stk_allocsize;
	register struct pcb *pcb;

	pcb = current_thread()->pcb;
	if ((pcb->pcb_fpa_flags & FPA_USED) == 0)
		return;
	if (pcb->pcb_fpa_fmtptr != NULL) {
		fpa_stk_allocsize = *(short *)(pcb->pcb_fpa_fmtptr + sizeof (short));
		if (fpa_stk_allocsize <= 0)
			panic("fpaclose: fmt inconsistent!");
		kmem_free(kernel_map, pcb->pcb_fpa_fmtptr, (u_int)fpa_stk_allocsize);
		pcb->pcb_fpa_fmtptr = NULL;
	}
	/* Skip any microcode execution if microcode is not loaded. */
	if (fpa_state == FPA_MULTI_USER) {
		fpa->fp_clear_pipe = 0; /* clear FPA pipe before the RAM test */
		fpa->fp_restore_mode3_0 = FPA_MODE3_INITVAL;
		if (fparamtest() < 0) {
			printf("FPA RAM test fails, FPA is shutdown!\n");
			uprintf("FPA test fails, computation result may be wrong!\n");
			fpa_shutdown();
		}
	}
	/*
	 * Don't free the FPA context for this thread if some thread 
	 * stole it already.  That's why our context is saved.
	 */
	if ((pcb->pcb_fpa_flags & FPA_CTX_SAVED) == 0)
		fpa_free_context(pcb->pcb_fpa_status.fpas_state & FPA_CONTEXT);
	pcb->pcb_fpa_flags = 0;		/* mark that FPA is not used */
	/* turn off bit EN.FPA on both Unix and hard enable register */
	off_enablereg((u_char)ENA_FPA);
}


/*
 * This is exactly like fpaclose() except that its argument is the thread
 * whose fpa context is to be freed.
 */
fpaclose_thread(thread)
	thread_t thread;
{
	short fpa_stk_allocsize;
	register struct pcb *pcb;

	pcb = thread->pcb;
	if ((pcb->pcb_fpa_flags & FPA_USED) == 0)
		return;
	if (pcb->pcb_fpa_fmtptr != NULL) {
		fpa_stk_allocsize = *(short *)(pcb->pcb_fpa_fmtptr + sizeof (short));
		if (fpa_stk_allocsize <= 0)
			panic("fpaclose: fmt inconsistent!");
		kmem_free(kernel_map, pcb->pcb_fpa_fmtptr, (u_int)fpa_stk_allocsize);
		pcb->pcb_fpa_fmtptr = NULL;
	}
	/* Skip any microcode execution if microcode is not loaded. */
	if (fpa_state == FPA_MULTI_USER) {
		fpa->fp_clear_pipe = 0; /* clear FPA pipe before the RAM test */
		fpa->fp_restore_mode3_0 = FPA_MODE3_INITVAL;
		if (fparamtest() < 0) {
			printf("FPA RAM test fails, FPA is shutdown!\n");
			uprintf("FPA test fails, computation result may be wrong!\n");
			fpa_shutdown();
		}
	}
	/*
	 * Don't free the FPA context for this thread if some thread 
	 * stole it already.  That's why our context is saved.
	 */
	if ((pcb->pcb_fpa_flags & FPA_CTX_SAVED) == 0)
		fpa_free_context(pcb->pcb_fpa_status.fpas_state & FPA_CONTEXT);
	pcb->pcb_fpa_flags = 0;		/* mark that FPA is not used */
	/* turn off bit EN.FPA on both Unix and hard enable register */
	off_enablereg((u_char)ENA_FPA);
}


/*
 * fpa_alloc_context() allocates an FPA context.
 * It returns the context number of the new context.
 * If fpa_thread[i] == NULL, FPA context i is free.
 * To allow diagnostic programs check the RAM of every context,
 * we don't always start allocating cantext from context 0.
 */
int
fpa_alloc_context()
{
	register int i;
	register int j = (int)fpa_last_ctx;
	register thread_t thread;

	for (i = 0; i < fpa_ncontexts; i++) {
		j = (j + 1) % fpa_ncontexts;
		if (fpa_thread[j] == NULL) {
			fpa_thread[j] = current_thread();
			fpa_last_ctx = j;
			return (j);
		}
	}
	/*
	 * No free contexts, so need to swipe someone else's.
	 * Push their full FPA state back into their pcb and set
	 * a flag saying so.
	 */
	thread = fpa_thread[j];
	if (thread == current_thread())
		panic("fpa_alloc_context: can't steal my own context!");
	on_enablereg((u_char)ENA_FPA);
	fpa_save(fpa_thread[j], 1);
	off_enablereg((u_char)ENA_FPA);
	(fpa_thread[j])->pcb->pcb_fpa_flags |= FPA_CTX_SAVED;
	fpa_thread[j] = current_thread();
	fpa_last_ctx = j;
	return (j);
}

/*
 * fpa_free_context(context_no) frees this FPA context.
 */
fpa_free_context(context_no)
	u_int context_no;
{

	if (fpa_thread[context_no] == NULL)
		panic("fpa_free_context");
	fpa_thread[context_no] = NULL;
}

/*
 * fpa_busy() returns 1 if FPA is being used, 0 if nobody is using FPA.
 */
int
fpa_busy()
{
	register i;

	for (i = 0; i < fpa_ncontexts; i++)
		if (fpa_thread[i])
			return (1);
	return (0);
}

/*
 * fparamtest() starts a destructive RAM test, waits until the
 * the pipe is ready, checks if the test is succeeded, and returns
 * 0 if the test succeeds or -1 if the test fails.
 */
int
fparamtest()
{
	register struct fpa_device *rfpa = fpa;

	rfpa->fp_destructive_test = 0;
	CDELAY(rfpa->fp_pipe_status & FPA_STABLE, 300);
	if ( (rfpa->fp_pipe_status & FPA_STABLE) &&
	    !(rfpa->fp_pipe_status & FPA_HUNG))
		return (0);
	else {
		if (!(rfpa->fp_pipe_status & FPA_STABLE))
			printf("fparamtest: nonstable after delay 300 us.\n");
		else
			printf("fparamtest: pipe is hung\n");
		return (-1);
	}
}

/*
 * fpa_shutdown() is called to disable FPA and kill all processes
 * using FPA.  It is called when an FPA hardware problem is found.
 * It marks FPA is unavailable and kills all processes using FPA.
 */
fpa_shutdown()
{
	register int i;

	fpa_state = FPA_DISABLED;
	printf("FPA shutdown\n");
/*
	for (i = 0; i < FPA_NCONTEXTS; i++)
		if (fpa_procp[i])
			psignal(fpa_procp[i], SIGKILL);
*/
}

/*
 * fpa_get_dataregs() is called from fpaioctl() to return a quarter
 * of FPA data registers to the user.  State_reg is that of the probed proc,
 * count tells which quarter the user requests, data is a pointer to
 * where we will dump the value of data registers.
 */
fpa_get_dataregs(state_reg, count, data)
	int state_reg, count;
	caddr_t data;
{
	register int i = 0;
	register struct fpa_device *rfpa = fpa;
	int saved_state = rfpa->fp_state;

	/* wait till FPA pipe is stable */
	CDELAY(rfpa->fp_pipe_status & FPA_STABLE, 300);
	if (!(rfpa->fp_pipe_status & FPA_STABLE)) {
		printf("FPA pipe is not stable\n");
		uprintf("FPA pipe not stable, cannot get FPA data registers\n");
		fpa_shutdown();
		return;
	}
	rfpa->fp_state = state_reg; /* change state register */
	/* copy data registers */
	for (i = 0; i < FPA_QTR_SIZE; i++)
		*((fpa_long *)data + i) =
		    rfpa->fp_data[count * FPA_QTR_SIZE + i];
	rfpa->fp_state = saved_state; /* restore state register */
}

/*
 * fpa_save() is called to force a context save before clearing 
 * fpa pipe.  It is followed by calling fpa_dorestore().
 * It is NOT called during context switch.
 */
fpa_save(thread, full_save)
	register thread_t thread;
	int full_save;
{
	register struct pcb *pcb;
	register struct fpa_device *rfpa = fpa;
	int saved_state;

	CDELAY(rfpa->fp_pipe_status & FPA_STABLE, 300);
	if (rfpa->fp_pipe_status & FPA_STABLE) {
		pcb = thread->pcb;
		saved_state = rfpa->fp_state;	/* save state register */
		if (thread != current_thread())
			/*
			 * Not current thread, so set FPA state register
			 * to value saved in pcb
			 */
			rfpa->fp_state = pcb->pcb_fpa_status.fpas_state;
		pcb->pcb_fpa_status = *((struct fpa_status *)&fpa->fp_state);
		if (full_save)		/* save registers too */
			bcopy((char *)rfpa->fp_data, (char *)pcb->pcb_fpa_data,
				sizeof(pcb->pcb_fpa_data));
		rfpa->fp_state = saved_state;	/* restore state register */
	}
	else {
		printf("FPA pipe is not stable\n");
		fpa_shutdown();
	}
}

#define pcb_fpas_state		pcb_fpa_status.fpas_state
#define pcb_fpas_imask		pcb_fpa_status.fpas_imask
#define pcb_fpas_load_ptr	pcb_fpa_status.fpas_load_ptr
#define pcb_fpas_ierr		pcb_fpa_status.fpas_ierr
#define pcb_fpas_mode3_0	pcb_fpa_status.fpas_mode3_0
#define pcb_fpas_wstatus	pcb_fpa_status.fpas_wstatus
#define pcb_fpas_act_instr	pcb_fpa_status.fpas_act_instr
#define pcb_fpas_nxt_instr	pcb_fpa_status.fpas_nxt_instr
#define pcb_fpas_act_d1half	pcb_fpa_status.fpas_act_d1half
#define pcb_fpas_act_d2half	pcb_fpa_status.fpas_act_d2half
#define pcb_fpas_nxt_d1half	pcb_fpa_status.fpas_nxt_d1half
#define pcb_fpas_nxt_d2half	pcb_fpa_status.fpas_nxt_d2half
/*
 * fpa_restore() is called from vax.s to turn on Enable Register and
 * check if we are the last process using FPA.  We skip restoring FPA
 * context if we are the last process using FPA.
 * This is also called from trap() if we fault trying to use the FPA
 * and we have our FPA state saved in our pcb.
 */
fpa_restore(thread, full_restore)
	thread_t thread;
	int full_restore;
{
	on_enablereg((u_char)ENA_FPA);
	if ((fpa->fp_state & FPA_STATE_BITS) !=
	    (thread->pcb->pcb_fpas_state & FPA_STATE_BITS))
		fpa_dorestore(thread, full_restore);
}

/*
 * fpa_dorestore() is called from fpa_restore if we are not the last
 * process using FPA and from procxmt() to restore FPA context
 * after calling fpa_save() and clearing FPA pipe.
 */
fpa_dorestore(thread, full_restore)
	thread_t thread;
	int full_restore;
{
	register u_int	instr_addr;
	register struct pcb *pcb;
	register struct fpa_device *rfpa = fpa;

	pcb = thread->pcb;
	rfpa->fp_clear_pipe = 0; /* clear FPA pipe */
	rfpa->fp_state = pcb->pcb_fpas_state;
	rfpa->fp_imask = pcb->pcb_fpas_imask;
	rfpa->fp_load_ptr = pcb->pcb_fpas_load_ptr;
	rfpa->fp_ierr = pcb->pcb_fpas_ierr;

	/*
	 * Restore everything including registers
	 */
	if (full_restore)
		bcopy((char *)pcb->pcb_fpa_data, (char *)rfpa->fp_data,
			sizeof(rfpa->fp_data));

	/*
	 * If microcode is not loaded, don't touch MODE3_0, WSTATUS, and
	 * shadow registers.
	 */
	if (!(rfpa->fp_state & FPA_LOAD_BIT)) {
		/* restore MODE3_0 */
		rfpa->fp_restore_mode3_0 = pcb->pcb_fpas_mode3_0 & FPA_MODE_BITS;
		/* restore WSTATUS */
		if (pcb->pcb_fpas_wstatus & FPA_STATUS_VALID)
			/* restore WSTATUS */
			rfpa->fp_restore_wstatus = pcb->pcb_fpas_wstatus;
		/* update shadow registers */
		rfpa->fp_restore_shadow = 0;
	}

	/*
	 * Restore FPA pipe.
	 * If (v bit is valid)
	 *	write corresponding data to the address specified by the
	 *	instruction half; (v is 0 => valid!)
	 */
	if (!(pcb->pcb_fpas_act_instr & FPA_FIRST_V)) {
		instr_addr = (pcb->pcb_fpas_act_instr & FPA_FIRST_HALF)
			>> FPA_ADDR_SHIFT;
		*( (u_int *)((u_int)rfpa + instr_addr) ) = pcb->pcb_fpas_act_d1half;
	}
	if (!(pcb->pcb_fpas_act_instr & FPA_SECOND_V)) {
		instr_addr = pcb->pcb_fpas_act_instr & FPA_SECOND_HALF;
		*( (u_int *)((u_int)rfpa + instr_addr) ) = pcb->pcb_fpas_act_d2half;
	}
	if (!(pcb->pcb_fpas_nxt_instr & FPA_FIRST_V)) {
		instr_addr = (pcb->pcb_fpas_nxt_instr & FPA_FIRST_HALF)
			>> FPA_ADDR_SHIFT;
		*( (u_int *)((u_int)rfpa + instr_addr) ) = pcb->pcb_fpas_nxt_d1half;
	}
	if (!(pcb->pcb_fpas_nxt_instr & FPA_SECOND_V)) {
		instr_addr = (pcb->pcb_fpas_nxt_instr & FPA_SECOND_HALF);
		*( (u_int *)((u_int)rfpa + instr_addr) ) = pcb->pcb_fpas_nxt_d2half;
	}
}


/*
 * Copy and initialize FPA state for child on fork
 */
fpa_fork_context(parent, child)
	thread_t parent, child;
{
	register struct pcb *pcb;
	register struct pcb *childpcb;

	pcb = parent->pcb;
	/*
	 * Return if FPA not in use or no FPA context
	 */
	if (pcb->pcb_fpa_flags == 0 || pcb->pcb_fpa_status.fpas_state == NULL)
		return(1);

	childpcb = child->pcb;
	/*
	 * Copy parent's FPA data registers into child's pcb and set 
	 * pcb_fpa_flags to indicate that the state is saved (used
	 * when we bus error trying to use the FPA)
	 */
	if ((pcb->pcb_fpa_flags & FPA_CTX_SAVED) == 0)
		bcopy((char *)fpa->fp_data, (char *)childpcb->pcb_fpa_data,
			sizeof(childpcb->pcb_fpa_data));
	else
		bcopy((char *)pcb->pcb_fpa_data,(char *)childpcb->pcb_fpa_data,
			sizeof(childpcb->pcb_fpa_data));
	childpcb->pcb_fpa_flags = FPA_CTX_SAVED;
	/*
	 * Since recomputation will never call fork(),
	 * we avoid the allocation and coping of
	 * FPA exception frame to the child.
	 */
	childpcb->pcb_fpa_fmtptr = NULL;
	childpcb->pcb_fpa_pc = 0;
	childpcb->pcb_fpas_state = 0;
	childpcb->pcb_fpas_ierr = childpcb->pcb_fpas_imask = 
		childpcb->pcb_fpas_load_ptr = 0;
	return (0);
}
