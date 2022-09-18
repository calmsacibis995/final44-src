/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ka820.c,v $
 * Revision 2.6  89/02/26  10:58:37  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.5  89/01/15  16:38:51  rpd
 * 	Updated includes to the new style.
 * 	Use decl_simple_lock_data.
 * 	[89/01/15  15:26:00  rpd]
 * 
 * Revision 2.4  88/10/11  13:07:11  rpd
 * 	Now we need a bi_settle() before probe_bi.
 * 	[88/10/05            rvb]
 * 
 * Revision 2.3  88/08/11  13:24:22  rvb
 * Put rxcd_intr code in an NCPUS > 1 conditional.  It would not be used
 * on a uniprocessor and some of the variables it references are not defined
 * unless NCPUS > 1.
 * 
 * Revision 2.2  88/08/10  10:50:04  rvb
 *   1-Jun-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Can not printf chars received from slave, since he may have
 * 	printf lock.
 * 
 *   6-May-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Formed from code in bi.c.
 * 
 *  28-Apr-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	KA820: Don't echo characters slave sends (echos) back in response
 * 	to what we send it.  This will clean up the slave startup
 * 	verbiage.
 * 
 *
 * 19-Aug-87  David Golub (dbg) at Carnegie-Mellon University
 *	Include cpu.h to get cpu_number definition (for single-cpu
 *	configuration).
 *
 * 11-Feb-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added interprocessor interrupt send and receive routines.
 *	Receive is (temporarily) tied to pmap_update_interrupt.
 *
 * 14-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added send_string_to_console routine to send commands to
 *	logical consoles.
 *
 *  4-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created.
 *
 */
/*
 *	File:	vax/bi.c
 *	Author:	Avadis Tevanian, Jr.
 *
 *	Copyright (C) 1986, Avadis Tevanian, Jr.
 *
 *	VAX BI Bus support.
 *
 *  NOTES:
 *  a.	Unless "t" is done on boot, all the bi regs are unchanged.  This
 *	is wrong.  Devices like ni, must be reset and it is cleaner to have
 *	the processor not able to interrupt until autoconf finds it.
 *  b.	When doing send_string to the console program on a slave, you must
 *	pace yourself.  If you write full speed, the console program can not
 *	keep up.
 *  c.	When "z" over to another machine, I believe it is the console program
 *	running on the "master" that reads the rxcd register and echo's.
 *  d.	We observe that during the machine checks that come with probing,
 *	we get EVENT=1a and EVENT=18 which have a corresponding processor
 *	ber of NEX and RDS respectively. The former comes from bi probes
 *	and the latter comes from unibus probes.  BUT NEVER in all this
 *	is anything set in the Port Controller Register.  Hmm.
 *
 */

#include <cputypes.h>
#if	VAX820

#include <cpus.h>

#include <sys/types.h>
#include <mach/vm_param.h>
#include <vm/vm_kern.h>

#include <vaxnb/ka820.h>
#include <vax/watch_chip.h>
#include <vax/mtpr.h>
#include <vax/cpu.h>
#include <vax/bi_node.h>
#include <vaxnb/node.h>

int *ka820_csr;


extern int crd;
extern int crd_cnt;

ka820_init()
{
	mtpr(CADR, 0);
	if (crd)
		*ka820_csr |= PCCSR_CRD;

	pka820();
}

ka820_conf()
{
	union cpusid 		cpusid;
	extern int		cpuspeed;
	extern int 		intmask;

	cpuspeed = 1;
	cpusid.cpusid = mfpr(SID);
	printf("VAX 8200, urev=%d, patch rev=%d, cpu rev=%d\n",
		cpusid.cpu820.cp_urev, cpusid.cpu820.cp_prev,
		cpusid.cpu820.cp_crev);
	/*
	 *	Map the watch chip.
	 */
	watch_chip = (struct watch_chip *)
			kmem_alloc_pageable(kernel_map,
					sizeof(struct watch_chip));
	ioaccess((caddr_t)0x200b8000,
		 (vm_offset_t) watch_chip, sizeof(struct watch_chip));
	/*
	 *	This node is the master CPU.
	 */
	master_cpu = mfpr(BINID);
	intmask = 1 << master_cpu;
	set_cpu_number();

	{
		struct ioanode *ioap = &ioanode[nioa];

		ioap->bi_addr = BI_ADDR(0);
		printf("\n NODE               V/P       TYPE\n");
		scan_bix(ioap);
		bi_settle();
		probe_bi(ioap->bi_addr, IO_BI, intmask);
		nioa++;
	}
}

ka820_halt(c)
{
	mtpr(MAPEN, 0);		/* seems to confuse it and it does not restart */
	asm("halt");
}

ka820_reboot(c)
{
	asm("halt");		/* TXDB_BOOT was already set */
}

mchk_ka820(cmcf)
caddr_t cmcf;
{
struct mc820frame {
	int	mc82_bcnt;		/* byte count = 0x20 */
	int	mc82_fill;
	int	mc82_parm1;		/* parameter 1 */
	int	mc82_var;		/* va register */
	int	mc82_vapr;		/* va prime register */
	int	mc82_mar;		/* memory address */
	int	mc82_status;		/* status word */
	int	mc82_pcf;		/* PC at failure */
	int	mc82_upc;		/* microcode pc */
	int	mc82_pc;		/* current PC */
	int	mc82_psl;		/* current PSL */
};
	register struct mc820frame *mcf = (struct mc820frame *)cmcf;
	register struct bi_node *biv = ioanode[0].bi[cpu_number()];

	printf("Machine Check: status %b\n", mcf->mc82_status, KA820MCHK);
	printf("va %x vap %x mar %x pc %x pcf = %x psl %x\n",
		mcf->mc82_var, mcf->mc82_vapr, mcf->mc82_mar, mcf->mc82_pc,
		mcf->mc82_pcf, mcf->mc82_psl);
	pka820();
	if (biv) {
		pbi(biv);
		biv->ber = biv->ber & BER_ERR;
	}
	*ka820_csr = (*ka820_csr & PCCSR_RW) | PCCSR_ERR;
	mtpr(MCESR, 0);
}

crd_ka820()
{
	register int i;

	printf("ka820 crd error\n");
	pka820();

	for (i = 0; i < nmem; i++) {
		register struct bi_node *mp = memnode[i].addr82;
		{
			printf("MEMORY Node %x at %x\n",
				memnode[i].node, pmap_extract(kernel_pmap, mp));
			pbi(mp);
		}
	}
	if (crd_cnt++ >= 10)
		*ka820_csr = ((*ka820_csr & PCCSR_RW) | PCCSR_ERR) & ~PCCSR_CRD;

}

bi_bus_error()
{
	int	node;

/*
	bi_node_local just went away
	It was being mapped to 0x2080,,0000 which is a pretty bogus place.

	node = mfpr(BINID);
	printf("VAXBI: Bus error, node0x%x: ber = 0x%x\n", node,
		bi_node_local->ber);
*/
	printf("does anyone ever call this\n");
}

/*
 *	rxcd_intr is called at interrupt time to receive a character
 *	from the logical console.
 */
rxcd_intr()
{
	register int	val;
	register unsigned char	c;
	register int 	sender;
	extern	master_cpu;

#if	NCPUS > 1
	val = rxcd_receive();		/* need to do flow control and test "V" bit */
	c = (val & 0xff);
	sender = (val & 0xf00) >> 8;

	/*
	 *	If we are the master, then echo the character.
	 *	If we are a slave, then simulate receiving a
	 *	character on the console.
	 */

	if (cpu_number() == master_cpu) {
		decl_simple_lock_data(extern,printf_lock)
		if (printf_lock.lock_data) {
			cnputc(c);	/* easy way out */
		}
	} else
		slave_input(c);
#else	NCPUS > 1
	panic("rxcd_intr: ncpus <= 1");
#endif	NCPUS > 1
}

/*
 *	send_string_to_console(cpu, str) sends the string to the
 *	specified cpu.
 */

send_string_to_console(dest_cpu, str)
	register int	dest_cpu;
	register unsigned char	*str;
{
	register int i;

	while (i = *str++) {
		rxcd_send(dest_cpu, i);
		for (i = 10000; i-- > 0;) ;	/* methinks you can not hit the console pgm too fast */
	}					/* and 1000 is to small but 10000 works !*/
}

bi_interrupt_processor(dest_cpu)
	int	dest_cpu;
{
	mtpr(IPIR, 1<<dest_cpu);
}


#define PR(str,ptr) printf("\t%s \t%x\n", str, ptr)
#define Pb(str,ptr,bits) printf("\t%s \t%b\n", str, ptr, bits)
#define Pval(str,ptr) if (ptr || p0val) PR(str, ptr)
#define Pvalb(str,ptr,bits) if (ptr || p0val) Pb(str,ptr,bits)
extern int p0val;

pka820()
{
	Pb("Port Controller CSR", *ka820_csr, PCCSR);
}
#endif	VAX820
