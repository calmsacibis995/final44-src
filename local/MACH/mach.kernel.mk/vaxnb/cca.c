/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	cca.c,v $
 * Revision 2.4  89/02/26  10:58:09  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  88/10/11  13:06:09  rpd
 * 	cca_snarf now takes a verbose switch.
 * 	[88/10/10            rvb]
 * 
 * Revision 2.2  88/08/10  10:45:59  rvb
 * 	Add cca_halt() and cca_reboot() to get cca flags right.
 * 	Try to appease the VAX6200 console monitor.
 * 	Created.  Week of 4/4.
 * 
 */
/*
 *	File:	cca.c
 *	Author:	Robert V. Baron
 *
 *	Routines for finding, printing, manipulating CCA.
 */
#include <cputypes.h>
#if	VAX6200

#include <sys/types.h>
#include <vaxnb/cca.h>

#define PR(str,ptr) printf("\t%s \t%x\n", str, ptr)
#define Pb(str,ptr,bits) printf("\t%s \t%b\n", str, ptr, bits)
#define Pval(str,ptr) if (ptr || p0val) PR(str, ptr)
#define Pvalb(str,ptr,bits) if (ptr || p0val) Pb(str,ptr,bits)
extern int p0val;

	/*
	 * find_cca() is run when addresses are still physical.
	 * For all the other routines the vm system is on.
	 */
struct cca *
find_cca(strt)
caddr_t strt;
{
register int i;
register u_char sum;
register struct cca *ccp = (struct cca *) strt;
register u_char *cp = (u_char *) strt;

	while  ( (strt -= 512) > 0) {
		register u_char *cp = (u_char *) strt;

		ccp = (struct cca *) strt;

		if (ccp->base != (u_int) ccp)
			continue;
		if (ccp->ident != 'CC')
			continue;
		for (i = 0, sum = 0; i < 9; i++)
			sum += *cp++;
		if (sum == ccp->chksum)
			break;
	}

	if (!strt)
		panic("cca");

	return ccp;
}

cca_to_slave(no, msg)
int no;
char *msg;
{
	register struct com_buf *cbp = &cca->buf[no];
	register int len = strlen(msg);
	register int cnt = 1000;

/*	while ((bbssi(0, cbp->flags)) && cnt-- > 0) ;*/

	while ( (cbp->flags & XCBUF_RXRDY) && cnt-- > 0);
	if (cnt <= 0) {
		printf("\tcca: Cannot get interlock, giving up\n");
		return;
	}
	bcopy(msg, cbp->rx, len);
	cbp->rxlen = len;
	cbp->flags |= XCBUF_RXRDY;
}

static int putsl();
cca_snarf(no, verbose)
int no;
{
	register int bit = 1<<no;
	register struct com_buf *cbp = &cca->buf[no];

	while (! (cca->ready[0] & bit));
	if (verbose)
		putsl(no, cbp->tx, cbp->txlen);
	cca->ready[0] &= ~(1<<no);
}

cca_halt(cpn)
{
	cca->restartip[0] &= ~(1<<cpn);
	ka62a_halt(cpn);
}

cca_reboot(cpn)
{
	cca->hflag |= HFLAG_REBOOT;	/* please do reboot */

	cca_halt(cpn);
}

pcca()
{
register struct cca *ccp = cca;
register struct hw_revision *hwp;
register struct com_buf *bp;
register int i;

	PR("Base Address", ccp->base);
	PR("Size of CCA", ccp->size);
	PR("'CC' Hex  \t", ccp->ident);
	PR("16 Processors", ccp->nproc);
	PR("Check Sum", ccp->chksum);
	Pb("Boot Flags", ccp->hflag, HFLAG);
	PR("CCA Version", ccp->revision);
	PR("Ready to Primary", ccp->ready[0]);
	PR("Console Mode", ccp->console[0]);
	PR("Ready to Go", ccp->enabled[0]);
	PR("Bitmap Size", ccp->bitmap_sz);
	PR("Bitmap Addr", ccp->bitmap);
	PR("Bitmap Cksum", ccp->bitmap_cksum);
	PR("TK50 XMI/BI", ccp->tk50_node);
	PR("Started by Primary", ccp->secstart[0]);
	PR("Restarting Self", ccp->restartip[0]);
	PR("Halted by ^P", ccp->user_halted[0]);
/*	PR("Serial Number", ccp->serialnum);*/

	for (i = 0, hwp = ccp->hw_revision; i < 16; i++, hwp++) {
		printf("\tNode %x HW REVISION: CVAX %x SSC %x FPA %x MODULE %x Compat %x\n",
			i, hwp->cvax_rev, hwp->ssc_rev, hwp->fpa_rev, hwp->mod_rev, hwp->com_grp);
	}

	for (i = 0, bp = ccp->buf; i < 16; i++, bp++) {
		printf("COM AREA Node %x @%x\n", i, bp);
		pcca_cpubuf(bp);
	}
}

pcca_cpubuf(bp)
register struct com_buf *bp;
{
register u_char *cp, *cpe;

	printf("\tControl and Status %b, Dest %x, Sender %x RXCD buf %x\n",
		bp->flags, XCBUF, bp->zdest, bp->zsrc, bp->zrxcd);

	printf("\t\tTXMT(%d)\t", bp->txlen);
	for (cp = bp->tx, cpe = &bp->tx[bp->txlen]; *cp && cp < cpe;)
		cnputc(*cp++);
		cnputc('\n');

	printf("\t\tRecvX(%d)\t", bp->rxlen);
	for (cp = bp->rx, cpe = &bp->rx[bp->rxlen]; *cp && cp < cpe;)
		cnputc(*cp++);
		cnputc('\n');
}

static int
putsl(no, str, len)
char *str;
{
register int c;

	cnputc('<');
	cnputc(no > 9 ? 'a' + no - 10 : '0' + no);
	cnputc('>');
	cnputc(' ');
	str += 2;			/* skip \r\n */
	while (len--) {
		cnputc(c = *str++);
		if (c == '\r') break;
	}
	if (str[-1] != '\n')
		cnputc('\n');

	for(c = 0; c < 2000; c++);
}
#endif	VAX6200
