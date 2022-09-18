/*
 ****************************************************************
 * Mach Operating System
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 ****************************************************************
 */
/*CMU:	mpm_intr.c	7.1	5/29/84	*/

#include <mach_mpm.h>

#include <sys/types.h>
#include <vax/nexus.h>
#include <vax/ma780reg.h>
#include <vax/ma780var.h>

/*
 **************************************************************************
 * HISTORY
 * $Log:	ma780subrs.c,v $
 * Revision 2.2  93/03/11  13:46:44  danner
 * 	u_long -> u_int
 * 	[93/03/09            danner]
 * 
 * Revision 2.1  89/08/03  16:27:31  rwd
 * Created.
 * 
 * 26-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Removed obsolete MACH_REMOTE option.
 *
 *  4-Mar-87  David Golub (dbg) at Carnegie-Mellon University
 *	Removed separate slave interrupt routine as it was exactly the
 *	same as the master interrupt routine.
 *
 * 11-Feb-87  David Golub (dbg) at Carnegie-Mellon University
 *	Changed 'interrupt_processor' to 'mpm_interrupt_processor'.
 *	Temporarily wired interprocessor interrupt to call
 *	pmap_update_interrupt.
 *
 * 15-Nov-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Flushed wb_ml.h.
 *
 * 21-Sep-84  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Call mp_rint to process interrupts from other processors.
 *
 * 14-Sep-84  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Inhibit mpm status printout on power change
 **************************************************************************
 */

mpmcintr(mpmno)
	int mpmno;
{
	register struct mpm_regs *mpmp = mpm_hd[mpmno].ph_mpm ;

	/*
	 * Check to see that there is a pending interrupt on this
	 * port.
	 */

	if (mpmp->mpm_ir & MPISTAT_TOME) {
		mpmp->mpm_ir = MPISTAT_TOME;	/* clear pending interrupt */
	}
	else {
		printf("Cross interrupted mpm%d start at %x\n",
			mpmno, 0x40000 * (
			MPADDR_MSK & (mpmp->mpm_invld >> MPADDR_SFT))) ;
		printf("MPM: unknown interrupt reason.  Disabling Interrupts.\n") ;
		mpmp->mpm_cr &= ~MPCR_MSTRIE ;
		mpm_prf(mpmno) ;
		return;
	}

	/*
	 *	The only use of multiprocessor interrupts at the
	 *	moment is the TLB shootdown code.  If we find
	 *	more uses for them (e.g. signal/interrupts for
	 *	running threads) this call must be replaced by
	 *	a call to a general interprocessor interrupt
	 *	routine.
	 */
	{
	    extern void	pmap_update_interrupt();

	    pmap_update_interrupt();	/* XXX */
	}
}


u_int MPISTAT_to[] =
	{ MPISTAT_TO0, MPISTAT_TO1, MPISTAT_TO2, MPISTAT_TO3 } ;

u_int MPISTAT_from[] =
	{ MPISTAT_FROM0, MPISTAT_FROM1, MPISTAT_FROM2, MPISTAT_FROM3 } ;

u_int MPIR_to[] =
	{ MPIR_TO0, MPIR_TO1, MPIR_TO2, MPIR_TO3 } ;

u_int MPIR_from[] =
	{ MPIR_FROM0, MPIR_FROM1, MPIR_FROM2, MPIR_FROM3 } ;

u_int MPESTAT_to[] =
	{ MPESTAT_TO0, MPESTAT_TO1, MPESTAT_TO2, MPESTAT_TO3 } ;

u_int MPESTAT_from[] =
	{ MPESTAT_FROM0, MPESTAT_FROM1, MPESTAT_FROM2, MPESTAT_FROM3 } ;

u_int MPEN_to[] =
	{ MPEN_TO0, MPEN_TO1, MPEN_TO2, MPEN_TO3 } ;

u_int MPEN_from[] =
	{ MPEN_FROM0, MPEN_FROM1, MPEN_FROM2, MPEN_FROM3 } ;

mpm_on(mpmnum)
{
	register struct mpm_regs *mpmp = mpm_hd[mpmnum].ph_mpm;

	mpmp->mpm_cr |= (MPCR_MSTRIE);	/* master interrupt enable */
	mpmp->mpm_cr |= (MPCR_PIERR);	/* port interface error int enable */
	mpmp->mpm_sr |= (MPSR_ERRIE);	/* error interrupt enable */
}

mpm_off(mpmnum)
{
	register struct mpm_regs *mpmp = mpm_hd[mpmnum].ph_mpm;

	mpmp->mpm_cr &= ~(MPCR_MSTRIE);
}

mpm_enable(mpmnum, who)
{
	register struct mpm_regs *mpmp = mpm_hd[mpmnum].ph_mpm;

	switch (who) {
	case MP_TO_ME:
		mpmp->mpm_en = MPEN_to[cpu_number()];
		break;
	case MP_FROM_ME:
		mpmp->mpm_en = MPEN_from[cpu_number()];
		break;
	default:
		;
	}
}

mpm_disable(mpmnum, who)
{
	register struct mpm_regs *mpmp = mpm_hd[mpmnum].ph_mpm;

	switch (who) {
	case MP_TO_ME:
		mpmp->mpm_en = MPESTAT_to[cpu_number()];
		break;
	case MP_FROM_ME:
		mpmp->mpm_en = MPESTAT_from[cpu_number()];
		break;
	default:
		;
	}
}

mpm_interrupt(mpmnum, who)
{
	register struct mpm_regs *mpmp = mpm_hd[mpmnum].ph_mpm;

	switch (who) {
	case MP_TO_ME:
		mpmp->mpm_ir = MPIR_to[cpu_number()];
		break;
	case MP_FROM_ME:
		mpmp->mpm_ir = MPIR_from[cpu_number()];
		break;
	default:
		mpmp->mpm_ir = who << 16;
		break;
	}
}

mpcauseint(mask)
	int mask;
{
	register struct mpm_regs *mpmp = mpm_hd[0].ph_mpm;

	mpmp->mpm_ir = mask << 16;
}

mpm_interrupt_processor(who)
	int who;
{
	register struct mpm_regs *mpmp = mpm_hd[0].ph_mpm;
	register int mask;

	mask = (1 << who);

	mpmp->mpm_ir = mask << 16;
}

mpm_dismiss(mpmnum, who)
{
	register struct mpm_regs *mpmp = mpm_hd[mpmnum].ph_mpm;

	switch (who) {
	case MP_TO_ME:
		mpmp->mpm_ir = MPISTAT_to[cpu_number()];
		break;
	case MP_FROM_ME:
		mpmp->mpm_ir = MPISTAT_from[cpu_number()];
		break;
	default:
		;
	}
}
