/*
 * 8800.
 */

char * nmi_nbia_addr[4] = {
	NMI_NBI+0*NMI_NBI_SZ+NMI_NBIA,
	NMI_NBI+0*NMI_NBI_SZ+NMI_NBIA,
	NMI_NBI+2*NMI_NBI_SZ+NMI_NBIA,
	NMI_NBI+2*NMI_NBI_SZ+NMI_NBIA
};

char * nmi_bi_addr[4] = {
	NMI_NBI+0*NMI_NBI_SZ,
	NMI_NBI+1*NMI_NBI_SZ,
	NMI_NBI+2*NMI_NBI_SZ,
	NMI_NBI+3*NMI_NBI_SZ
};

int	ka8800_setup(), ka8800_init(), ka8800_config(),
	ka8800_slave_config(),
	ka8800_reboot_ok(), ka8800_crd(), ka8800_mchk(),
	ka8800_halt(), ka8800_interrupt();

struct model_dep ka8800_model = {
	ka8800_setup,
	ka8800_init,
	ka8800_config,
	ka8800_slave_config,
	ka8800_reboot_ok,
	ka8800_crd,
	ka8800_mchk,
	ka8800_halt,
	ka8800_interrupt,
	10
};

ka8800_cache_on()
{
	mtpr(COR, 1);
}

ka8800_setup()
{
}

ka8800_init()
{
	cpusid.cpusid = mfpr(SID);

	printf("VAX 8800\n");
	printf("cpu 0:\n");

	mtpr(NICTRL, 0xe1);	/* enable NMI interrupts */

	/*
	 * Processors are in slots 0 and 1.
	 */
	machine_slot[0].is_cpu = TRUE;
	machine_slot[1].is_cpu = TRUE;

	vax_putc(0);		/* wait for console to come ready */
	mtpr(TXDB, 0xf05);	/* boot other CPU */

	/*
	 * Map in memory controller
	 */
	{
	    struct mcl	*nmp;

	    nmp = (struct mcl *)io_map(NMI_MCL, sizeof(struct mcl));

	    mem_node[nmem].addr = (char *)nmp;
	    mem_node[nmem].node = 0;
	    nmem++;

	    printf("MEM 0:  V/P  %x/%x", (char *)nmp, NMI_MCL);
	    pms88_size();
	}

	for (i = 0; i < 4; i++) {
	    struct ioa_node *ioa = &ioa_node[nioa];
	    struct nbi	*ip;

	    /*
	     * Check for BI bus address space
	     */
	    nmi = io_map(nmi_bi_addr[i], NMI_SIZE);
	    if (nmi_badaddr(nmi, sizeof(int))) {
		io_unmap(nmi, NMI_SIZE);
		continue;
	    }
	    io_unmap(nmi, NMI_SIZE);

	    /*
	     * Check for NMI adaptor address space
	     */
	    ip = (struct nbi *)io_map(nmi_nbia_addr[i], NBI_SIZE);
	    if (nmi_badaddr(ip, sizeof(int))) {
		io_unmap(ip, NMI_SIZE);
		continue;
	    }

	    ioa->addr = (char *)ip;
	    ioa->node = i;
	    ioa->bi_paddr = (char *)nmi_bi_addr[i];

	    /*
	     * As soon as we enable, we see a power-on interrupt
	     * unless...
	     */
	    ip->csr1 |= (NBIACSR1_BI0PWR | NBIACSR1_BI1PWR);
	    ip->csr0 |= NBIACSR0_IE;

	    printf("IOA %x:  V/P  %x/%x", i, (char *)ip, nmi_nbia_addr[i]);
	    scan_bix(ioa);
	    nioa++;
	}

	bi_settle();

}

ka8800_config()
{
	for (i = 0; i < nioa; i++) {
	    struct ioa_node *ioa = &ioa_node[i];
	    struct bi_node *biv = ioa->bddr;

	    if (ioa->addr) {
		probe_bi(i, 0, 1<<ioa->bnode);

		biv->ber = biv->ber & BER_ERR;
		biv->bicsr |= BICSR_HEIE | BICSR_SEIE;
	    }
	}
}

ka8800_slave_config()
{
	ka8800_cache_on();
}

ka8800_reboot_ok()
{
	tocons(TXDB_CWSI);
	tocons(TXDB_CCSI);
}

boolean_t
nmi_badaddr(addr, size)
	char *	addr;
	int	size;
{
	register int spl;

	spl = splblock();
	if (badaddr(addr, size)) {
	    mtpr(TOSTS, 0);
	    mtpr(MCSTS, 0);
	    splx(spl);
	    return (TRUE);
	}
	splx(spl);
	return (FALSE);
}

ka88_badaddr()
{
	mtpr(TOSTS, 0);
	mtpr(MCSTS, 0);
}

ka8800_crd()
{
	printf("ka8800_crd\n");
	pka88();
	pms88();
}

int	mcheck_skips = 0;

ka8800_mchk(cmcf)
	char *	cmcf;
{
struct mc8800frame {
	int	mc88_bcnt;		/* byte count = 0x20 */
	int	mc88_mcsts;		/* machine check status register */
	int	mc88_mpc;		/* micro pc */
	int	mc88_va;		/* va register */
	int	mc88_iber;		/* ibox error register */
	int	mc88_cber;		/* cbox error register */
	int	mc88_eber;		/* ebox error register */
	int	mc88_nmifsr;		/* nmi fault summary register */
	int	mc88_nmiear;		/* nmi error address register */
	int	mc88_pc;		/* current PC */
	int	mc88_psl;		/* current PSL */
};
	register struct mc8800frame *mcf = (struct mc8800frame *)cmcf;

	/*
	 *	For reasons which I do not understand, the 8800
	 *	seems to take lots of unnecessary machine checks
	 *	so for now, ignore them (some of them anyway).
	 */
	if (mcf->mc88_nmifsr == 0xc0000) {
		printf("spurious machine check\n");
		pka88();
		mtpr(TOSTS, 0);
		mtpr(MCSTS, 0);
		mcheck_skips++;
		return;
	}

	printf("mcsts %x mpc %x va %x\n", mcf->mc88_mcsts,
		mcf->mc88_mpc, mcf->mc88_va);
	printf("ibox %b\n", mcf->mc88_iber, IBOX);
	printf("cbox %b\n", mcf->mc88_cber, CBOX);
	printf("ebox %b\n", mcf->mc88_eber, EBOX);
	printf("nmifsr %b\n", mcf->mc88_nmifsr, NMIFSR_B);
	printf("nmiear %x\n", mcf->mc88_nmiear, NMIEAR_B);
	printf("pc %x psl %x\n", mcf->mc88_pc, mcf->mc88_psl);
	pka88();
	printf("halting...\n");
	mtpr(TOSTS, 0);
	mtpr(MCSTS, 0);
	asm("halt");
	return;
}

ka8800_halt(reboot)
	boolean_t	reboot;
{
	if (reboot) {
	    tocons(TXDB_BOOT);
	    for (;;)
		asm("halt");
	    /*NOTREACHED*/
	}
	printf("halting (in tight loop); hit\n\t^P\n\tHALT\n\n");
	for (;;)
	    ;
	/*NOTREACHED*/
}

ka8800_interrupt(dest)
	int	dest;
{
	/*
	 * Assume interrupting the other CPU (there are only 2)...
	 */
	mtpr(INOP,0);
}

nmi_fault()
{
	register int	dest;
	register struct mcl *mp = (struct mcl *)mem_node[0].addr;

	printf("nmi fault:");
	pka88();
	pms88();
	dest = mp->csr4;
	dest = mp->csr5;
}

nbib_error(which)
	int	which;
{
	register struct nbi *nbip = (struct nbi *)ioa_node[which*2].addr;

	printf("nbib_error\n");
	pka88();
	pnbi(nbip);
	nbip->csr0 = nbip->csr0;
	nbip->csr1 = nbip->csr1;
}

nmi_err(pc, psl, ioa)
{
	register struct nbi *nbip     = (struct nbi *)ioa_node[ioa].addr;
	register struct ioa_node *ioap = &ioa_node[ioa];
	register struct bi_node *biv  = ioa_node[ioa].bddr;

	if (pc)
	    printf("nmi_err(pc %x, psl %x, ioa %x)\n", pc, psl, ioa);
/*	else
	    it was called by bi_err */

	if ((int) nbip) {
	    printf("Bcard Node %x V %x\n",
		   ioap->bnode,
		   ioap->bddr);
	    print_bi(ioap->bddr);
	    printf("IOA %x\tNODE %x\tBNODE %x\t A/B %x/%x PHYS %x\n",
		   ioa,
		   ioap->node,
		   ioap->bnode,
		   ioap->addr,
		   ioap->bddr,
		   ioap->bi_paddr);
	    pnbi(nbip);
	}

	printf("CPU = Node%x\n", master_cpu);

	pka88();
}

/*
 *	Handle a command received from the console.
 */
nautilus_cin(c)
	register int	c;
{
	register int		id;
	register struct tty	*tp;
	extern struct tty	cons;

	tp = &cons;
	id = c&RXDB_ID;
	switch (id) {
	/* Remote console input */
	case 0x300:
	case 0x600:
		(*linesw[tp->t_line].l_rint)(c&0177, tp);
		return;
	}
	printf("unexpected nautilus input: c = 0x%x.\n", c);
	asm("halt");
}

nautilus_cout()
{
}



#define PR(str,ptr) printf("\t%s \t%x\n", str, ptr)
#define Pb(str,ptr,bits) printf("\t%s \t%b\n", str, ptr, bits)
#define Pval(str,ptr) if (ptr || p0val) PR(str, ptr)
#define Pvalb(str,ptr,bits) if (ptr || p0val) Pb(str,ptr,bits)
extern int p0val;

static char *mcl_size_code[] = {
	"   ",
	"res",
	"res",
	" 4M",
	" 8M",
	"16M",
	"32M",
	"cap"};

static int mcl_size_val[] = { 0, 0, 0, 4, 8, 16, 32, 0};

static int pka88ed = 0;

pka88()
{
	register int tmp;

	tmp = mfpr(MCSTS);
	Pb("Machine Check Status Register", tmp, C88MCSTS);

	/* Write Only
	  tmp = mfpr(NICTRL);
	  Pb("NMI Interrupt Control Register", tmp, NICTRL_B);
	*/

	tmp = mfpr(NMIFSR);
	Pb("NMI Fault Summary Register", tmp, NMIFSR_B);

	tmp = mfpr(NMISILO);
	Pb("NMI Silo Data Register ", tmp, NMISILO_B);

	tmp = mfpr(NMIEAR);
	Pb("NMI Error Address Register", tmp, NMIEAR_B);

	tmp = mfpr(COR);
	Pb("Cache Enable(On) Register", tmp, C88COR);

	if (!(++pka88ed)) {
	    tmp = mfpr(REVR1);
	    Pb("Revision Register 1", tmp, C88REVR1);

	    tmp = mfpr(REVR2);
	    Pb("Revision Register 2", tmp, C88REVR2);
	}

	/* Apparently also Write Only
	  tmp = mfpr(TOSTS);
	  Pval("TimeOut Status Register", tmp);
	 */
}

pms88()
{
	register struct mcl *mp= (struct mcl *)mem_node[0].addr;

	printf("MEM  %x/%x\n", mp, NMI_MCL);

	Pb("MCL CSR 0", mp->csr0, MCLCSR0);
	Pb("MCL SR  1", mp->csr1, MCLSR1);
	Pb("MCL CSR 1", mp->csr1, MCLCSR1);
	Pb("MCL CSR 2", mp->csr2, MCLCSR2);
	Pb("MCL CSR 3", mp->csr3, MCLCSR3);
}

pms88_size()
{
	register struct mcl *mp = (struct mcl *)mem_node[0].addr;
	register int tmp;
	register int i;
	register int no;
	register int sum = 0;

	for (i=0, tmp = mp->csr3; i < 8; i++, tmp >>= 3) {
	    no = tmp & MCLCSR3_MSK;
	    sum += mcl_size_val[no];
	}
	printf("	%dM: ", sum);
	for (i=0, tmp = mp->csr3; i < 8; i++, tmp >>= 3) {
	    no = tmp & MCLCSR3_MSK;
	    if (mcl_size_val[no])
		printf("%d - %s, ", i, mcl_size_code[no]);
	}
	printf("\n");
}

pnbi(nbiap)
	register struct nbi *nbiap;
{
	register caddr_t phys = (caddr_t)pmap_extract(kernel_pmap, nbiap);

	printf("ADAPTOR %x V/P %x/%x\n",
		phys == nmi_nbia_addr[0] ? 0 : 1,
		nbiap,
		phys);
	Pb("NBIA CSR0", nbiap->csr0, NBIACSR0);
	Pb("NBIA CSR1", nbiap->csr1, NBIACSR1);
	Pval("NBIA BR4", nbiap->br4vr);
	Pval("NBIA BR5", nbiap->br5vr);
	Pval("NBIA BR6", nbiap->br6vr);
	Pval("NBIA BR7", nbiap->br7vr);
}

dump8800()
{
	pka88();
	pms88();
	dumpnbi();
}

dumpnbi()
{
	register int i, j;
	register struct ioa_node *ip = ioa_node;

	for (i = 0; i < nioa; i++, ip++) {
	    printf("IOA %x\tNODE %x\tBNODE %x\t A/B %x/%x PHYS %x\n",
		   i,
		   ip->node,
		   ip->bnode,
		   ip->addr,
		   ip->bddr,
		   ip->bi_paddr);
	    pnbi((struct nbi *)ip->addr);
	    for (j = 0; j < BI_MAX_NODE; j++) {
		if (ip->bi[j]) {
		    printf("BI NODE %x\n", j);
		    pbi(ip->bi[j]);
		}
	    }
	}
}

