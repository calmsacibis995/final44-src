/*
 **************************************************************************
 * Mach Operating System
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 **************************************************************************
 * HISTORY
 * $Log:	ma780.c,v $
 * Revision 2.1  89/08/03  16:24:02  rwd
 * Created.
 * 
 * 23-Aug-88  David Golub (dbg) at Carnegie-Mellon University
 *	Moved mpm_find and hack_mpm here from autoconf for MACH_KERNEL.
 *
 *  4-Mar-87  David Golub (dbg) at Carnegie-Mellon University
 *	Removed separate slave interrupt as it is a duplicate of the
 *	master interrupt routine.
 *
 * 21-Sep-84  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Call mp_rint to process interrupts from other processors.
 *
 * 14-Sep-84  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Inhibit mpm status printout on power change
 **************************************************************************
 */

#include <cpus.h>

#include <kern/cpu_number.h>
#include <mach/machine.h>
#include <sys/types.h>

#include <vax/mem.h>
#include <vax/mtpr.h>
#include <vax/nexus.h>
#include <vax/ma780reg.h>
#include <vax/ma780var.h>

/* 
 * Find multiport memory.
 */
mpmfind(nxv, nxp, nexnum)
	struct nexus *nxv, *nxp;
	int	nexnum;
{
	register struct mpm_regs *mpmp;
	register caddr_t addr;
 
	mpmp = (struct mpm_regs *)nxv;
	mpm_hd[nummpm].ph_mpm = mpmp;
	mpm_hd[nummpm].ph_physmpm = (struct mpm_regs *)nxp;
 
	mpmp->mpm_sr &= ~ MPSR_INVALDIS;
	mpmp->mpm_cr &= ~(MPCR_IVDTACK|MPCR_MSTRIE);
 
	/*
	 *	Force cache invalidates on all SBI ID's.  This
	 *	can be turned off as soon as the cache ID is set
	 *	but I'm not sure how to do this yet.
	 */
 
	mpmp->mpm_invld |= (MPINVLD_CACHEFORCED);
 
	/*
	 * Set origin of multiport memory.
	 * WARNING: this code KNOWS that there are 4 mpms, at
	 * tr2..tr5.
	 */
	mpmp->mpm_invld = (mpmp->mpm_invld & ~(MPADDR_MSK<<MPADDR_SFT))
			   | (((MPMEM_ORIGIN/0x40000) | 8 * (nexnum - 2))
					  << MPADDR_SFT);
	addr = (caddr_t) (0x40000*(MPADDR_MSK&(mpmp->mpm_invld>>MPADDR_SFT)));
	printf("mem at %x ", addr);
 
	if (cpu_number() != (mpmp->mpm_csr & MP_PORT)) {
	    printf("\n\nTurkey!!! The same CPU has different port numbers for different MA780\'s.  Have your hardware fixed.\n");
	    asm("halt");
	}

	printf("port %d\n", mpmp->mpm_csr & MP_PORT);
 
	mpm_dismiss(nummpm, MP_TO_ME);
	mpm_dismiss(nummpm, MP_FROM_ME);
	mpm_on(nummpm);
	mpm_enable(nummpm, MP_TO_ME);
}
 
hack_mpm(i)
int i;
{
	register struct mpm_regs *mpmp;

	mpmp = mpm_hd[i].ph_mpm;
	M780MA_ENA( ((struct mcr *) mpmp) );

	mpmp->mpm_sr &= ~ MPSR_INVALDIS;
	mpmp->mpm_cr &= ~(MPCR_IVDTACK|MPCR_MSTRIE);
  
	mpmp->mpm_invld |= (MPINVLD_CACHEFORCED);	/* see earlier */
  
	printf("mem at %x ", 0x40000 * (
			       MPADDR_MSK&(mpmp->mpm_invld>>MPADDR_SFT)));
 
	printf("port %d\n", mpmp->mpm_csr & MP_PORT);
 
	mpm_dismiss(i, MP_TO_ME);
	mpm_dismiss(i, MP_FROM_ME);
	mpm_on(i);
	mpm_enable(i, MP_TO_ME);
}

mpmintr(mpmno)
{
	register struct mpm_regs *mpmp = mpm_hd[mpmno].ph_mpm ;

	printf("Interrupted mpm%d start at %x\n",
		mpmno, 0x40000 * (
		MPADDR_MSK & (mpmp->mpm_invld >> MPADDR_SFT))) ;

	if (mpmp->mpm_csr & (PWR_UP|PWR_DN)) {
		printf ("Power: %x\n", mpmp->mpm_csr) ;
		mpmp->mpm_csr = (PWR_UP|PWR_DN) ;/* stupid bits cleared by
						 * setting to one */
		/*
		 mpm_prf(mpmno) ;
		 */
	} else {
		printf("MPM: unknown interrupt reason.  Disabling Interrupts.\n") ;
		mpmp->mpm_cr &= ~MPCR_MSTRIE ;
		mpm_prf(mpmno) ;
	}
}


char *mpm_reg_name[] = { "Configuration", "Interface Control",
			"Controller Status", "Invalidation Control",
			"Array Error", "Configuration Status #0",
			"Configuration Status #1", "Maintainance Control",
			"Interrupt Request", "Interrupt Enable" } ;

mpm_prf(mpmnum)
{
	register struct mpm_regs *mpmp = mpm_hd[mpmnum].ph_mpm ;

	printf("mpm%d|00\t %s Register\n",
		mpmnum, mpm_reg_name[0]) ;
	printf("\t\t %b\n", mpmp->mpm_csr, MPCSR_BITS) ;

	printf("mpm%d|04\t %s Register\n",
		mpmnum, mpm_reg_name[1]) ;
	printf("\t\t %b\n", mpmp->mpm_cr, MPCR_BITS) ;

	printf("mpm%d|08\t %s Register\n",
		mpmnum, mpm_reg_name[2]) ;
	printf("\t\t %b\n", mpmp->mpm_sr, MPSR_BITS) ;

	printf("mpm%d|0c\t %s Register\n",
		mpmnum, mpm_reg_name[3]) ;
	printf("\t\t %b\n", mpmp->mpm_invld, MPINVLD_BITS) ;

	printf("mpm%d|10\t %s Register\n",
		mpmnum, mpm_reg_name[4]) ;
	printf("\t\t %b\n", mpmp->mpm_err,  MPERR_BITS) ;

	printf("mpm%d|14\t %s Register\n",
		mpmnum, mpm_reg_name[5]) ;
	printf("\t\t %b\n", mpmp->mpm_sr0,  MPSR0_BITS) ;

	printf("mpm%d|18\t %s Register\n",
		mpmnum, mpm_reg_name[6]) ;
	printf("\t\t %b\n", mpmp->mpm_sr1, MPSR1_BITS) ;

	printf("mpm%d|1c\t %s Register\n",
		mpmnum, mpm_reg_name[7]) ;
	printf("\t\t %b\n", mpmp->mpm_maint, MPMAINT_BITS) ;

	printf("mpm%d|20\t %s Register\n",
		mpmnum, mpm_reg_name[8]) ;
	printf("\t\t %b\n", mpmp->mpm_ir,  MPISTAT_BITS) ;

	printf("mpm%d|24\t %s Register\n",
		mpmnum, mpm_reg_name[9]) ;
	printf("\t\t %b\n", mpmp->mpm_en, MPESTAT_BITS) ;

}
