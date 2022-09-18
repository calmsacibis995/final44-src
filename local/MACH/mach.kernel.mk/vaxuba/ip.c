/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ip.c,v $
 * Revision 2.3  89/03/09  22:35:32  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  11:04:02  gm0w
 * 	Updated copyright.
 * 	[89/02/23            gm0w]
 * 
 */
#include <ip.h>
#if	NIP > 0
int gtudbg = 0;
#define IP8500HI
char ipSCCSid[]="@(#)ip.c 1.42 83/03/25 (Use RCS's ident command)";
char ipRCSid[]=	"$ Header: /a/display/driver/ip.c,v 1.10 84/01/16 10:37:46 bob Exp $";
/*
 * Deanza IP8500 image processing display driver.
 * DMA interface.
 */
#include <sys/param.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/systm.h>
#include <sys/map.h>
#include <sys/kernel.h>

#include <sys/uio.h>
#include <machine/pte.h>
#include <vaxuba/ubavar.h>
#include <vaxuba/ubareg.h>

#include <vaxuba/ipconfig.h>
#include <vaxuba/ipstructs.h>

#define BIT(x)	(1<<x)
#define BUTTON_DELTA	BIT(6)
#define TRKB_DELTA	BIT(7)

#define CNTLRESET	0040000
#define SYSRESET	0100000
#define GTU_RESET	0x80
#define GTU_WRPGO	0x10

/* 8500 instructions */
#define COUNT	(9)		/* for LR|COUNT */
#define CE	0200		/* for LR and RR count enable */
#define LR	(0001<<8)	/* load command window registers */
#define RR	(0002<<8)	/* read command window registers */
#define WI	(0003<<8)	/* write image */
#define RI	(0004<<8)	/* read image */
#define WR	(0005<<8)	/* write rectangle */
#define WAU	(0006<<8)	/* write and update */
#define LMC	(0100<<8)	/* load memory controller */
#define RMC	(0110<<8)	/* SOFTWARE!! read memory controller */
#define BMC	(0120<<8)	/* broad memory controller */
#define LPA	(0101<<8)	/* load peripheral reg */
#define RPA	(0111<<8)	/* read peripheral reg */
#define BPA	(0121<<8)	/* broadcast peripheral reg */
#define LPR	(0202<<8)	/* load peripheral reg */
#define RPR	(0212<<8)	/* read peripheral reg */

/* fuword, but returns 32bits instead of 16 on VAX; f is fromUserSpacePointer */
#define FUSHORT(fromP)	(*(fromP))
/* suword, but sets 32 bits at toUserSpacePointer equal to value */
#define SUSHORT(toP,value)	(*toP = value)
#define CNT	bp->b_bcount>>1
#define IPPRI	(PZERO-2)
#define IPPRITB	(PZERO+5)
#define IPPRIALLOC (PZERO+6)

struct	ipdevice {	/* the first 8 registers always respond on the unibus */
	short	cmd;
	short	isr;	/* reading this register clears it */
	short	reserv1;
	short	psr;
	short	rsr;
	short	dw;
	short	reserv2;
	short	dr;

	short	ir;	/* the next 56 shorts are available if CW is set */
	short	count;
	short	cntrl;
	short	res;
	short	foregnd, backgnd;
	short	reserv3[2];
	short	xpos, xt, xmin, xmax, xamin, xamax, dx, xtemp;
	short	ypos, yt, ymin, ymax, yamin, yamax, dy, ytemp;
	short	cmr[32];

	short	reserv4[16];	/* and finally, the DMA registers */
	short	dawc;
	u_short	daba;
	short	dacs;
};
/****************************************************************************
  a handy guide for some important deanza registers -
15  14  13  12     11  10  09  08     07  06  05  04     03  02  01  00
SR  CR  DWE CWE    BR  ie  s2  DWie   CD  VB  AD  p1     p0   D   I  MS   CMD
II  IQ  IC  IA     IS  s2b s2a ID     CD  VB  AD  p1     p0   D   I  MS   ISR
A2  A1  A0  u12    u11 u10 u9  u8     u7  u6  u5  u4     u3  u2  u1  u0   PSR
			       HS     CD  VB  AP  RR     WR  ID  EF  MS   RSR
IF  NEX ATT WCZ                CY     RDY IE  ex1 ex0    fn2 fn1 fn0 GO   DACS
******************************************************************************/

/* BIT PATTERNS FOR %b formatted diagnostics */
char dacs_b[]="\20\20IF\17NEX\16ATT\15WCZ\11CY\10RDY\7IE";
char cmd_b[]="\20\20SR\17CR\16DW\15CW\14SC\13IE\12S2\11DW\10CD\7VB\
					\6AD\5P1\4P0\3D\2I\1MS";
char isr_b[]="\20\20II\17IQ\16IC\15IA\14IS\13S2B\12S2A\11ID\10CD\7VB\
					\6AD\5P1\4P0\3D\2I\1MS";
char psr_b[]="\20\20A2\17A1\16A0\10U7\7U6\6U5\5U4\4U3\3U2\2U1\1U0";

/* bits used int the DMA control+status register (dacs) */
#define IP_INTRFLG	0100000
#define IP_NEX		0040000
#define IP_ATT		0020000
#define IP_WCZ		0010000
#define IP_CYCLE	0000400
#define IP_RDY		0000200
#define IP_IE		0000100
#define IP_READ		0000004
#define IP_WRITE	0000002
#define IP_DMA_GO	0000001

struct	buf ripbuf[NIP];

struct	dev_alloc {
	short	processor;
	short	digitizer;
	long	memory;
	};

struct	unit {
	int ipcmdVal; 	/* current bit pattern for cmd register */
	int ip_state;	/* software state of the 8500 */
	int ip_ubinfo;	/* UNIBUS allocation info */
	struct environ *ip_curEnviron;	/* Environ. regs. for owning process */
	short gtu_cntl_stat;	/* GTU control-0 and status regs. 
					(low byte/high byte) */
	short ip_softar[NBOARDS][5];/* soft copy of mem contr registers */
	short ip_isr;		/* contents of isr reg. from last interrupt */
	struct	dev_alloc ipa;	/* record of devices allocated */
	struct	subunit {
		int sub_state;	/* state of subunit */
		long ip_sig;	/* async. notification of trkball activity */
		long ip_pid;
		struct proc *ip_procp;
		struct dev_alloc ipasub;/* devices allocated for subunit */
		int ip_TBpending;	/* flag to show trkball data pending */
		struct iptrack trk;	/* storage for trkball data til read */
		struct timeval b_time;	/* time of last good button interrupt.
					Needed to debounce buttons. */
		struct environ {	/* Interface regs. for preserving
					environ */
			short en_control;	/* control */
			short en_res;		/* resolution */
			short en_fg;		/* foreground */
			short en_bg;		/* background */
			short en_resrvd[2];	/* reserved */
			short en_x;		/* X coord. */
			short en_xt;		/* X translate */
			short en_xmin;		/* min. X address */
			short en_xmax;		/* max. X address */
			short en_xamin;		/* min. X access */
			short en_xamax;		/* max. X access */
			short en_dx;		/* delta X for matrix mode */
			short en_xtemp;		/* temp. X */
			short en_y;		/* Y coord. */
			short en_yt;		/* Y translate */
			short en_ymin;		/* min. Y address */
			short en_ymax;		/* max. Y address */
			short en_yamin;		/* min. Y access */
			short en_yamax;		/* max. Y access */
			short en_dy;		/* delta Y for matrix mode */
			short en_ytemp;		/* temp. Y */
			short en_cmr[32];	/* channel mask registers */
		} sub_env;
		struct defer {	/* Holding space for deferred instructions */
			short de_count;		/* for count reg. */
			unsigned short de_cmd;	/* deferred command */
			int de_bcnt;		/* no. of bytes of data */
		} def_op;
	} ip_subunit[NVOC];	/* Need above info on a per sub-device basis */
} ip_unit[NIP];	/* Need above info on a per device (minor) basis */

/* State bits for recording the state of a display generator or subunit
	of a generator (ie. VOC and associated mem. and periphs.).  Used
	to set and clear bits in the state variables in the ip_unit and
	ip_subunit structures */

#define IPS_OPEN	0000001		/* unit or subunit open */
#define IPS_ERR		0000002		/* Illegal addr, count, seq. or inst. */
#define IPS_NEXERR	0000004		/* non-ex. mem. dma error */
#define IPS_WANT_SIG	0000010		/* Process wants a sig. on tkb. int. */
#define READ_DEFERRED	0000020		/* A write sys. call was done to
					prime display for a read */
#define WRITE_DEFERRED	0000040		/* A write sys. call contained
					instruction only -- data to follow */
#define NON_DEF_INSTR	0000100		/* Instr. not from previous 
					write sys call */
#define DMA_ACTIVE	0000200		/* DMA is active on interface */
#define GTU_ACTIVE	0000400		/* GTU is active */
#define GTU_TIMEOUT	0001000		/* GTU timed out */

#define IPUNIT(dev)	(minor(dev) >> 3)
#define SUBUNIT(dev)	((minor(dev) & 07))

int ipmindma=512;	/* use DMA if u_count >= ipmindma; else progrm I/O */
int ipnoisy = 1;	/* stray intr get printed if non-zero */
int resetip_on= 0;	/* If non-zero will print on con. when display reset */

/* Should have been done in hardware!  Stupid to have do debounce w/ software */
long tkbwait = 500000;	/* debounce time for buttons */

int	ipprobe(), ipattach();
struct	uba_device *ipdinfo[NIP];
u_short	ipstd[] = { 0766000, 0 };
struct uba_driver ipdriver={ ipprobe, 0, ipattach, 0, ipstd, "ip", ipdinfo };

/*******************************************************************/
ipprobe(reg)	/* during autoconfig, force ip to show its vec, br */
caddr_t reg;
{
	register int br, cvec;		/* value-result */
	register struct ipdevice *ipaddr = (struct ipdevice *)reg;
#ifdef	lint
	br = 0; cvec = br; br = cvec;
#endif

	/* start a DMA xfer of zero words to force intr */
	ipaddr->cmd  = 02000;	/* enable interrupts here */
	ipaddr->dawc = 0;
	ipaddr->dacs = 0300;	/* enable interrupts here too */
	ipaddr->dacs = 0303;	/* DMA out to device */
	DELAY(10000);
	ipaddr->dacs = 0;
	ipaddr->cmd = 0;
	return(sizeof(struct ipdevice));
}

/*******************************************************************/
/*ARGSUSED*/
ipattach(ui)
struct uba_device *ui;
{
	return(0);
}

/*******************************************************************/
ipopen(dev)	/* attempt to open ip for exclusive use */
dev_t dev;
{
	register struct uba_device *ui = ipdinfo[IPUNIT(dev)];
	register struct unit   *ipU  = &ip_unit[IPUNIT(dev)];
	register struct subunit *ipSU = &ipU->ip_subunit[SUBUNIT(dev)];
	int s;

	if (	IPUNIT(dev) >= NIP
		|| SUBUNIT(dev) >= NVOC
		|| ui == 0
		|| ui->ui_alive == 0)
		return(ENXIO);
	if (ipSU->sub_state)
		return(EBUSY);
	if(ipU->ip_state == 0)
	{
		ipU->ipcmdVal = 0x1408; /* 12CW 10IE 3P0 in cmd register*/
		ipreset_cntrl (IPUNIT(dev));
		ipU->ip_state = IPS_OPEN;
		ipU->ip_curEnviron = &ipSU->sub_env;
		ipU->ipa.processor = IP_DVP | IP_GTU;
	}
	ipSU->sub_state = IPS_OPEN;
	ipSU->ip_procp = u.u_procp;		/* process pointer */
	ipSU->ip_pid   = u.u_procp->p_pid;	/* process id */
	ipSU->trk.control = 0;			/* trackball control word */
	ipSU->ip_TBpending=0;			/* start trackball off clean */
	s = spl7();
	ipSU->b_time = time;
	splx(s);

	return(0);
}

/*******************************************************************/
ipstrategy(bp)	/* set up for a DMA xfer, directly into user space */
register struct buf *bp;
{
	struct uba_device *ui = ipdinfo[IPUNIT(bp->b_dev)];
	register struct unit   *ipU  = &ip_unit[IPUNIT(bp->b_dev)];
	register struct subunit *ipSU = &ipU->ip_subunit[SUBUNIT(bp->b_dev)];
	register struct ipdevice *ipaddr = (struct ipdevice *)ui->ui_addr;
	register short *usradr;
	int i,j;
	int board, ra, cmrnum, bitarray, lastreg;
	dev_t unit;
	short ipsofttmp[5];
	unsigned short I_psr;
	unsigned short opcode;
	unsigned short com;
	unsigned wcnt;

	unit = IPUNIT(bp->b_dev);	/* Display unit number */

	(void) spl6();
	ipU->ipcmdVal &= (~BIT(3));		/* prevent trkball interrupts */
	ipaddr->cmd = ipU->ipcmdVal;
	(void) spl0();

	ip_set_environ (bp->b_dev);	/* save old/get new environ */

	if (ipSU->sub_state & (READ_DEFERRED | WRITE_DEFERRED))
	{
		ipaddr->dr = LR | COUNT;
		ipaddr->dr = ipSU->def_op.de_count;
		ipaddr->dr = ipSU->def_op.de_cmd;
	}

	opcode = ipSU->def_op.de_cmd & 0xFF00;

	/* Intercept instructions written to 8500, looking for 
	certain opcodes.  Needed to provide software registers 
	where hard ones are missing. */

	if ((opcode == LMC) || (opcode == BMC))
	{
		ra = ipSU->def_op.de_cmd & 7; /* register address */
		if ((lastreg = ra + ipSU->def_op.de_count - 1) > 4)
			lastreg = 4;
		usradr = (short *)bp->b_un.b_addr;
		if (ipSU->sub_state & NON_DEF_INSTR) 
		 	if (FUSHORT(usradr++) == (LR|COUNT))
			{
				usradr++; usradr++;
			}
		if (opcode == LMC)	/* Load Mem. Cntl. Reg. */
		{
			board= (ipSU->def_op.de_cmd >> 3) & 037;
			if((ra <= 4) && (board < NBOARDS))
				for(i = ra; i <= lastreg; i++)
					ipU->ip_softar[board][i]=
						FUSHORT(usradr++);
		}
		else	/* Broadcast Mem. Cntl. Reg. */
		{
			if(ra <= 4)
			{	/* First save values to be broadcast.
				** Load bitarray with specified chan. mask reg.
				** Initially bit 0 corresponds to board 0.
				** If bit set, load ipS->ip_softar.
				** Go on to next bit and board.
				*/
				for(i = ra; i <= lastreg; i++)
					ipsofttmp[i] = FUSHORT(usradr++);
				cmrnum = (ipSU->def_op.de_cmd >> 4) & 0xF;
				bitarray = ipaddr->cmr[cmrnum*2];/* CMRs 
								are long*/
				for(j = 0; j < NBOARDS; j++)
				{
				    if(bitarray & 1)
					for(i = ra; i <= lastreg; i++)
					    ipU->ip_softar[j][i] = ipsofttmp[i];
				    bitarray >>= 1;
				}
			}
		}
	}
	if ((opcode == WR) || (opcode == WAU))
	{
		(void) spl6();
		ipaddr->cmd = ipU->ipcmdVal | BIT(1);/* IE instr. complete */
					/* Ipintr will clear this bit */
		ipaddr->dr = ipSU->def_op.de_cmd;
		while ((ipaddr->rsr & BIT(2)) == 0)
			sleep ((caddr_t)&ipU->ip_state, IPPRI);
		(void) spl0();
	}
	else if (bp->b_bcount < ipmindma)
	{
	/*
	 * dr in IP8500 UNIBUS Address Space <--> User Space transfer
	 */
		wcnt = CNT;
		usradr = (short *)bp->b_un.b_addr;
		if (bp->b_flags & B_READ)
		{
			for (i = wcnt; i > 0; i--)
			{
				if( ipU->ip_state&IPS_ERR)
					break;
				 SUSHORT(usradr++, ipaddr->dr);
			}
		}
		else
		{
			for (i = wcnt; i > 0; i--)
			{
				if( ipU->ip_state&IPS_ERR)
					break;
				ipaddr->dr = FUSHORT(usradr++);
			}
		}
	}
	else
	{
		(void) spl6();
		ipU->ip_ubinfo = ubasetup(ui->ui_ubanum, bp, UBA_NEEDBDP);
		ipaddr->dawc = CNT;
		if(bp->b_flags&B_READ)
		{
			com = IP_CYCLE | IP_IE 
				| ((ipU->ip_ubinfo>>12)&0x30) | IP_READ;
		}
		else
		{
			com = IP_CYCLE | IP_IE 
				| ((ipU->ip_ubinfo>>12)&0x30) | IP_WRITE;
		}
		ipaddr->dacs = com;
		ipaddr->daba = ipU->ip_ubinfo;
		ipaddr->dacs = com | IP_DMA_GO;
		ipU->ip_state |= DMA_ACTIVE;
	
		while( ipU->ip_state & DMA_ACTIVE )
			/* Expect a WCZ interrupt to wake us up.  However,
			   we cannot check IP_RDY because of an error on the DMA
			   interface PC board that connects the wrong signal
			   to the ready bit in the dacs */
			sleep( (caddr_t)&(ipU->ip_state), IPPRI);

		ubarelse(ui->ui_ubanum, &ipU->ip_ubinfo);
		(void) spl0();
	}
	if (ipU->ip_state & IPS_ERR)
	{
		bp->b_flags |= B_ERROR;
		ipU->ip_state &= ~IPS_ERR;
		if (ipU->ip_isr & BIT(15))
			uprintf ("ip%d:  Illegal instruction.\n", unit);
		if (ipU->ip_isr & BIT(14))
			uprintf ("ip%d:  Illegal sequence.\n", unit);
		if (ipU->ip_isr & BIT(13))
			uprintf ("ip%d:  Illegal count.\n", unit);
		if (ipU->ip_isr & BIT(12))
			uprintf ("ip%d:  Illegal address.\n", unit);
	}
	(void) spl6();
	ipU->ipcmdVal |= BIT(3);	/* re-enable trackball interrupts */
	ipaddr->cmd = ipU->ipcmdVal;
	if ((I_psr = ipaddr->psr) & 0xf)
		ip_periphs(unit,I_psr);
	(void) spl0();

	ipSU->sub_state &= ~(NON_DEF_INSTR | READ_DEFERRED | WRITE_DEFERRED);
	iodone(bp);

	return;
}

/*******************************************************************/
unsigned
ipminphys(bp)
register struct buf *bp;
{
	if (bp->b_bcount > 120*512)
		bp->b_bcount = 120*512;
}

/*******************************************************************/
ipread(dev,uio)
dev_t dev;
struct uio *uio;
{
	register int unit = IPUNIT(dev);
	register struct unit   *ipU  = &ip_unit[IPUNIT(dev)];
	register struct subunit *ipSU = &ipU->ip_subunit[SUBUNIT(dev)];
	register struct ipdevice *ipaddr 
		= (struct ipdevice *)ipdinfo[IPUNIT(dev)]->ui_addr;
	register struct iovec *iov = uio->uio_iov;
	int board, ra;

	if (uio->uio_iovcnt != 1)
	{
		printf("ip: iovcnt != 1\n");
		return(EIO);
	}
	if (!(ipSU->sub_state & READ_DEFERRED)
		|| (ipSU->sub_state & WRITE_DEFERRED))
	{
		ipSU->sub_state &= ~(READ_DEFERRED | WRITE_DEFERRED);
		return(EIO);
	}
	if ((ipSU->def_op.de_cmd & 0xFF00) == RMC)
	{
		ipSU->sub_state &= ~(READ_DEFERRED | WRITE_DEFERRED);
		ra = ipSU->def_op.de_cmd & 7; /* register address */
		board = (ipSU->def_op.de_cmd >> 3) & 037;
		if ((ipSU->def_op.de_count) != (iov->iov_len >> 1))
			return (ENXIO);
		copyout ((caddr_t)&ipU->ip_softar[board][ra], 
			(caddr_t)iov->iov_base, iov->iov_len);
		uio->uio_resid -= iov->iov_len;
		uio->uio_offset += iov->iov_len;
		iov->iov_len = 0;
		uio->uio_iov++;
		uio->uio_iovcnt++;
		return (0);
	}
	return(physio(ipstrategy, &ripbuf[IPUNIT(dev)], dev, B_READ, ipminphys,uio));
}

/*******************************************************************/
ipwrite(dev,uio)
dev_t dev;
struct uio *uio;
{
	register struct ipdevice *ipaddr = 
		(struct ipdevice *)ipdinfo[IPUNIT(dev)]->ui_addr;
	register struct unit   *ipU  = &ip_unit[ IPUNIT(dev)];
	register struct subunit *ipSU = &ipU->ip_subunit[SUBUNIT(dev)];
	register struct iovec *iov = uio->uio_iov;
	register short *fromuser;
	register i,j;
	unsigned short opcode;
	unsigned short instr;
	short datavals;
	short count=1;
	int bcnt;
	int board, ra, cmrnum, bitarray;

	if (uio->uio_iovcnt != 1)
	{
		printf("ipwrite: iovcnt != 1\n");
		return(EIO);
	}
	if (ipSU->sub_state & WRITE_DEFERRED)
	{	/* A write cmd. was prev. sent.  This must be data. */
		if (ipSU->def_op.de_bcnt != iov->iov_len)
		{
			ipSU->sub_state &= 
			    ~(NON_DEF_INSTR | READ_DEFERRED | WRITE_DEFERRED);
			return(EIO);
		}
	}
	else
	{
		/* check def. read pending -- if so then error */
		if (ipSU->sub_state & READ_DEFERRED)
		{
			ipSU->sub_state &= 
			    ~(NON_DEF_INSTR | READ_DEFERRED | WRITE_DEFERRED);
			return(EIO);
		}
		if (!useracc(iov->iov_base, iov->iov_len, B_READ))
		{
			ipSU->sub_state &= 
			    ~(NON_DEF_INSTR | READ_DEFERRED | WRITE_DEFERRED);
			return(EFAULT);
		}
		fromuser = (short *)iov->iov_base;
		if ((instr = FUSHORT(fromuser++)) == (LR|COUNT))
		{
			count = FUSHORT(fromuser++);
			instr = FUSHORT(fromuser++);
			datavals = iov->iov_len - 6;
		}
		else
		{
			datavals = iov->iov_len - 2;
		}
		opcode = instr & 0xFF00;
		if ((opcode != WI)
			&& (opcode != RI)
			&& (opcode != LPA)
			&& (opcode != RPA)
			&& (opcode != BPA))
		{	/* word oriented instructions */
			datavals = datavals >> 1;	/* count is wds. */
			bcnt = count << 1;		/* byte count */
		}
		else
		{	/* byte oriented instructions */
			bcnt = count;		/* byte count */
			if (bcnt & 1)
			{
				bcnt++;		/* make it even */
				if (datavals)
					/* adjust for odd byte count */
					datavals--;
			}
		}
		ipSU->def_op.de_count = count;
		ipSU->def_op.de_cmd = instr;
		ipSU->def_op.de_bcnt = bcnt;
		if (( opcode == LR) || (opcode == RR))
			ipSU->def_op.de_cmd |= CE;	/* cnt enable */

		if (((datavals != count) && (datavals != 0))
		    || ((count == 0) && (opcode != WR) && (opcode != WAU)))
			/* count specified does not match i/o size */
			return(EIO);

		if (opcode == RMC)	/* Read Mem. Cntl. Reg. */
		{
			ra = instr&7; /* register address */
			board= (instr>>3)&037;
			if(((count + ra) > 4) || (board >= NBOARDS))
				return (ENXIO);
		}
		if ((datavals == 0) && (opcode != WR) && (opcode != WAU))
		{	/* either a read operation or the data is 
			   to come later so defer the operation */
			if ((opcode == RR) 
				|| (opcode == RI) 
				|| (opcode & (010 << 8)))
				ipSU->sub_state |= READ_DEFERRED;
			else
				ipSU->sub_state |= WRITE_DEFERRED;
			uio->uio_resid -= iov->iov_len;
			uio->uio_offset += iov->iov_len;
			iov->iov_len = 0;
			uio->uio_iov++;
			uio->uio_iovcnt++;
			return(0);
		}
		else
		{
			ipSU->sub_state |= NON_DEF_INSTR;
		}
	}

	return(physio(ipstrategy, &ripbuf[IPUNIT(dev)], dev, B_WRITE, ipminphys,uio));
}

/*******************************************************************/
/*ARGSUSED*/
ipioctl(dev, com, arg, flag)
dev_t dev;
int com;
caddr_t arg;
int flag;
{
	register struct ipdevice *ipaddr 
		= (struct ipdevice *)ipdinfo[IPUNIT(dev)]->ui_addr;
	register struct iptrack *iptr;
	register struct unit   *ipU  = &ip_unit[IPUNIT(dev)];
	register struct subunit *ipSU = &ipU->ip_subunit[SUBUNIT(dev)];

	struct ipPoints *ipp;
	struct ip_alloc *ipalloc;
	short ipunit = IPUNIT(dev);
	short subunit = SUBUNIT(dev);
	long signo;
	extern ip_timeout();

	iptr = (struct iptrack *)arg;
	ipp = (struct ipPoints *)arg;
	ipalloc = (struct ip_alloc *)arg;

	switch (com)
	{
	case IPINIT:		/* initialize ip hardware */
			/* should also zero soft memory registers XXX */
		if(!suser())
			return(EPERM);
		ipreset_cntrl (ipunit);

		wakeup((caddr_t) &ipU->ip_state);
		wakeup((caddr_t) &ipSU->ip_TBpending);
		wakeup ((caddr_t) &ripbuf[ipunit]);

		break;

	case IP_ALLOC:		/* allocate a display resource */
		switch (ipalloc->resource)
		{
		case IP_PROC:	/* allocate a DVP or a GTU */
			if ((ipalloc->unit & ipSU->ipasub.processor) ==
			    ipalloc->unit)
				break;	/* already have it allocated */
			while ((ipalloc->unit & ipU->ipa.processor) !=
			    ipalloc->unit)
				sleep((caddr_t)&ipU->ipa.processor, IPPRIALLOC);
			ipSU->ipasub.processor |= ipalloc->unit;	
			ipU->ipa.processor &= ~ipalloc->unit;	
			break;
		default:
			return (ENXIO);
		}
		break;

	case IP_DEALLOC:	/* deallocate a display resource */
		switch (ipalloc->resource)
		{
		case IP_PROC:	/* deallocate a DVP or GTU */
		    {
			register int temp;

			if (temp = ipalloc->unit & ipSU->ipasub.processor)
				break;	/* not currently allocated */
			ipSU->ipasub.processor &= ~temp;
			ipU->ipa.processor |= temp;
			wakeup((caddr_t) &ipU->ipa.processor);
			break;
		    }
		default:
			return (ENXIO);
		}
		break;

	case IP_GO:
	    {
		unsigned short I_psr;

/* Disable forced allocation
		if (!(*(long *)arg & ipSU->ipasub.processor))
			return (EIO);
*/
		ipget_cntlr (ipunit);

		spl6();
		ip_set_environ (dev);	/* save old/get new environ */
		ipU->ipcmdVal &= ~BIT(3);	/* disable trackball interrupts */
		spl0();

		switch (*arg)
		{
		case IP_DVP:
			ipaddr->cmd = ipU->ipcmdVal | BIT(5); /* Enable 
				interrupts for DVP.  Ipintr will clear this */
			spl6();
			ipaddr->cntrl |= BIT(6);	/* Start DVP */
			while ((ipaddr->rsr & BIT(5)) == 0)
				sleep ((caddr_t)&ipU->ip_state, IPPRI);
			spl0();
			break;

		case IP_GTU:
			ipaddr->count = 1;	/* read to get state of bits
						in cntrl-0 reg. and to clear
						status reg. */
			ipaddr->dr = RMC | (18 << 3) | 0;
			ipU->gtu_cntl_stat = ipaddr->dr;
			timeout (ip_timeout, dev, 5 * 60 * hz);
			ipU->ip_state |= GTU_ACTIVE;
			ipaddr->cmd = ipU->ipcmdVal | BIT(9); /* Enable 
				interrupts for GTU.  Ipintr will clear this */
			ipaddr->count = 1;
			ipaddr->dr = LMC | (18 << 3) | 0;
			spl6();
			ipaddr->dr = GTU_WRPGO 
					| (ipU->gtu_cntl_stat & GTU_1KMEM);
			while (ipU->ip_state & GTU_ACTIVE)
				sleep ((caddr_t)&ipU->ip_state, IPPRI);
			if (!(ipU->ip_state & GTU_TIMEOUT))
				untimeout (ip_timeout, dev);
			spl0();
			break;

		default:
			iprel_cntlr (ipunit);
			return (ENXIO);
		}
		iprel_cntlr (ipunit);
		spl6();
		if ((I_psr = ipaddr->psr) & 0xf)
			ip_periphs(IPUNIT(dev),I_psr);

		ipU->ipcmdVal |= BIT(3);		/* re-enable trackball ints. */
		ipaddr->cmd = ipU->ipcmdVal;
		spl0();
	    }
		break;

	case IP_LGTU_ARY:
	    {
		register struct ip_gtu *ipgtu;

		ipgtu = (struct ip_gtu *) arg;
		ipget_cntlr (ipunit);
		spl6();
		ipaddr->count = 1;
		ipaddr->dr = LMC | (18 << 3) | 1;
		ipaddr->dr = ipgtu->arrayptr;
		spl0();
		iprel_cntlr (ipunit);
		break;
	    }

	case IP_LGTU_C0:
	    {
		register struct ip_gtu *ipgtu;

		ipgtu = (struct ip_gtu *) arg;
		if ((!suser ()) && (~GTU_1KMEM & ipgtu->cntl0))
			return (EPERM);

		ipget_cntlr (ipunit);
		spl6();
		ipaddr->count = 1;
		ipaddr->dr = LMC | (18 << 3) | 0;
		ipaddr->dr = (short) ipgtu->cntl0;
		spl0();
		iprel_cntlr (ipunit);
		break;
	    }

	case IP_LGTU_C1:
	    {
		register struct ip_gtu *ipgtu;

		if (!suser())
			return (EPERM);

		ipgtu = (struct ip_gtu *) arg;
		ipget_cntlr (ipunit);
		spl6();
		ipaddr->count = 1;
		ipaddr->dr = LMC | (18 << 3) | 2;
		ipaddr->dr = ipgtu->cntl1;
		spl0();
		iprel_cntlr (ipunit);
		break;
	    }

	case IP_RGTU:
	    {
		register struct ip_gtu *ipgtu;
		register short temp;

		ipgtu = (struct ip_gtu *) arg;
		ipget_cntlr (ipunit);
		spl6();
		ipaddr->count = 3;
		ipaddr->dr = RMC | (18 << 3) | 0;
		temp = ipaddr->dr;
		ipgtu->cntl0 = (char) temp;
		ipgtu->status = (char) (temp >> 8);
		ipgtu->arrayptr = ipaddr->dr;
		temp = ipaddr->dr;
		ipgtu->cntl1 = (char) temp;
		spl0();
		iprel_cntlr (ipunit);
		break;
	    }

	case IP_GTU_RESET:

		ipget_cntlr (ipunit);
		spl6();
		ipaddr->count = 1;
		ipaddr->dr = LMC | (18 << 3) | 0;
		ipaddr->dr = GTU_RESET;
		spl0();
		iprel_cntlr (ipunit);
		break;

	case IP_TB_SET:		/* setup for trackball interrupts */
		ipget_cntlr (ipunit);
		spl6();
		ipaddr->count = 3;
		ipaddr->dr = LPR | (subunit << 4) | 1;
		ipaddr->dr = 0;		/* deanza says to zero this first */
		ipaddr->dr = iptr->x;
		ipaddr->dr = iptr->y;

		ipaddr->dr = LPR | (subunit << 4) | 1;
		ipaddr->dr = iptr->control;
	
		ipaddr->dr = RPR | (subunit << 4) | 0;	/* clear out possible 
							pending intrs */
		iptr->status = ipaddr->dr;
		ipSU->trk.status &= ~(BUTTON_DELTA | TRKB_DELTA); /* since
					a signal may have already been sent for
					received trackball data we must clear
					those status bits so that if the user
					reads them they will indicate that
					nothing changed */
		ipSU->trk.control = iptr->control; /* Save new control word */
		spl0();
		iprel_cntlr (ipunit);
		break;

	case IP_TB_GET:
		spl6();
		while(ipSU->ip_TBpending == 0)
			sleep((caddr_t)&ipSU->ip_TBpending, IPPRITB);
		ipSU->ip_TBpending = 0;
		iptr->status =	ipSU->trk.status;
		iptr->control =	ipSU->trk.control;
		iptr->x	=	ipSU->trk.x;
		iptr->y  =	ipSU->trk.y;
		spl0();
		break;

	case IP_TB_SIG:
		if(*(int *)arg < 1 || *(int *)arg > NSIG)
			return(EINVAL);
		ipSU->ip_sig = *(int *)arg;
		ipSU->sub_state |= IPS_WANT_SIG;
		if (ipSU->ip_TBpending)
			psignal (ipSU->ip_procp, ipSU->ip_sig); /* signal
				process if data already pending */
		break;

	case IP_SYS_GET:
	    {
		register struct ipsysreg *ipsys;
		ipsys = (struct ipsysreg *)arg;
		if(!suser())
			return(EPERM);
		ipget_cntlr (ipunit);
		spl6();
		ipsys->cmd = ipaddr->cmd;
		ipsys->isr = ipaddr->isr; /* reading this is dangerous
					because it could cause interrupts 
					to be lost */
		ipsys->psr = ipaddr->psr;
		ipsys->rsr = ipaddr->rsr;
		ipsys->dw  = ipaddr->dw;
		spl0();
		iprel_cntlr (ipunit);
		break;
	    }
	case IP_POINTS:
	    {
		register short *shortp;
		register int pointcount;
		register int i;
		unsigned short I_psr;
		int xstart, ystart, xend, yend;

		pointcount = ipp->pointcount;
		shortp = ipp->ppoint;
		/* 2 shorts per point */
		if (!useracc(shortp, 2*pointcount*(sizeof *shortp), B_READ))
			return(EFAULT);

		ipget_cntlr (ipunit);
		spl6();
		ip_set_environ (dev);	/* save old/get new environ */
		ipU->ipcmdVal &= ~BIT(3);	/* disable trackball interrupts */
		ipaddr->cmd = ipU->ipcmdVal;
		spl0();
		ipaddr->dx = 0; ipaddr->dy = 0;
		while( pointcount-- > 0 && (ipU->ip_state&IPS_ERR)==0 )
		{
			ipaddr->xpos = *shortp++;
			ipaddr->ypos = *shortp++;
			ipaddr->dr   = WAU;
		}
		iprel_cntlr (ipunit);
		spl6();
		if ((I_psr = ipaddr->psr) & 0xf)
			ip_periphs(IPUNIT(dev),I_psr);

		ipU->ipcmdVal |= BIT(3);		/* re-enable trackball ints. */
		ipaddr->cmd = ipU->ipcmdVal;
		spl0();
	    }
		break;

	default:
		return(ENXIO);

	} /* end switch */

	if (ipU->ip_state & (IPS_ERR | GTU_TIMEOUT))
	{
		if (ipU->ip_state & GTU_TIMEOUT)
		{
			ipaddr->count = 1;
			ipaddr->dr = RMC | (18 << 3) | 0;
			ipU->gtu_cntl_stat = ipaddr->dr;
			uprintf ("ip%d:  GTU timeout -- status = 0x%x.\n",
				ipunit, ipU->gtu_cntl_stat >> 8);
		}
		ipU->ip_state &= ~(IPS_ERR | GTU_TIMEOUT);
		ipreset_cntrl (ipunit);
		return(EIO);
	}
	return(0);
}

/*******************************************************************/
/* TCP-IP uses ipintr(), so we must use Ipintr(). --ghg */

Ipintr(dev)
dev_t dev;
{
	register struct ipdevice *ipaddr = 
		(struct ipdevice *)ipdinfo[dev]->ui_addr;
	register struct unit   *ipU  = &ip_unit[dev];
	unsigned short I_cmd,I_dacs,I_psr;

	I_dacs = ipaddr->dacs;
	ipaddr->dacs = IP_IE; /*writing resets logic to allow future ints */

	if (ipU->ip_state & DMA_ACTIVE)
	{	/* DMA is active on interface. */

		if(I_dacs & (IP_WCZ | IP_NEX))
		{	/* word count zero, or nonex. mem. interrupt */

			ipU->ip_state &= ~DMA_ACTIVE;
			wakeup((caddr_t) &ipU->ip_state);
			if(I_dacs & IP_NEX)
				ipU->ip_state |= IPS_NEXERR; /* set err. flag */
		}
		else
		{	/* This should not happen since only dma ints. are on */
			printf ("\nip%d:  Stray Int. during DMA, dacs = %d\n",
				dev, I_dacs, dacs_b);
		}
	}
	else if ((ipU->ip_isr = ipaddr->isr) & 0xf022a)
	{	/* Interrupts handled are:	Illegal instruction.
						Illegal sequence.
						Illegal count.
						Illegal address.
						Other intrf. device (warper).
						Array processor done.
						Periph. set 0.
						Instruction complete.
		*/
		I_psr = ipaddr->psr;
		I_cmd = ipaddr->cmd;
		ipaddr->cmd = ipU->ipcmdVal; /* write to cmd to allow future int?? */

		if(ipU->ip_isr & BIT(3))	/* periph. set 0 (trackball)  */
			ip_periphs(dev, I_psr);

		if(ipU->ip_isr & BIT(1))
		{	/* instr. complete */
			wakeup((caddr_t) &ipU->ip_state);
		}
		if(ipU->ip_isr & BIT(5))
		{	/* array proc. done */
			wakeup((caddr_t) &ipU->ip_state);
		}
		if(ipU->ip_isr & BIT(9))
		{	/* GTU done */
			ipaddr->count = 1;	/* read control-0 & status */
			ipaddr->dr = RMC | (18 << 3) | 0;
			ipU->gtu_cntl_stat = ipaddr->dr;

			ipU->ip_state &= ~GTU_ACTIVE;
			wakeup((caddr_t) &ipU->ip_state);
if (gtudbg)
	printf("ip%d: GTU int., dacs=%b cmd=%b isr=%b psr=%b\n",
			    dev, I_dacs,dacs_b, I_cmd,cmd_b, 
			    ipU->ip_isr,isr_b, I_psr,psr_b);
		}
		if(ipU->ip_isr & 0xf000)	/* illegal instruction, seq., 
						count, or address */
		{
			ipU->ip_state |= IPS_ERR; 
			ipreset_cntrl (dev);
			wakeup((caddr_t) &ipU->ip_state);
		    	printf(
			"ip%d:  Illegal oper., dacs=%b cmd=%b isr=%b psr=%b\n", 
			    dev, I_dacs,dacs_b, I_cmd,cmd_b, 
			    ipU->ip_isr,isr_b, I_psr,psr_b);
		} 
	}
	else 
	{
		I_psr = ipaddr->psr;
		I_cmd = ipaddr->cmd;
		ipU->ip_state |= IPS_ERR;

		if(ipnoisy)
		    printf( "ip%d:  Stray Int. dacs=%b cmd=%b isr=%b psr=%b\n",
			dev, I_dacs,dacs_b, I_cmd,cmd_b, ipU->ip_isr,isr_b, 
			I_psr,psr_b);
		wakeup((caddr_t) &ipU->ip_state); 
	}
}

/*******************************************************************/
/* Process perpherial input.  Only the trackball is currently handled. */

ip_periphs(dev,periphs_psr)
dev_t dev;
unsigned short periphs_psr;
{
	register struct ipdevice *ipaddr = 
		(struct ipdevice *)ipdinfo[dev]->ui_addr;
	register unsigned short trk_stat;
	register struct unit *ipU  = &ip_unit[dev];
	register struct subunit *ipSU;
						
	struct timeval time_now;
	struct timeval delta_time;
	short	i,devices;
	int	s;

	devices = periphs_psr & 0xf;
	ipSU = &ipU->ip_subunit[0];

	for (i = 0; i < NVOC; i++)
	{
		if (devices & BIT(0))
		{
			ipaddr->count = 1;
			ipaddr->dr = RPR | (i << 4) | 0;
			trk_stat = ipaddr->dr;
			if (trk_stat & BUTTON_DELTA)
			{   /*	Since the hdw. designer was too lazy, we have
				to debounce the buttons here by throwing away
				interrupts that happen too close together in
				time. */
				s = spl7();
				time_now = time;
				splx(s);
				delta_time = time_now;
				timevalsub (&ipSU->b_time, &delta_time);
			}
			if ((trk_stat & TRKB_DELTA)
			    || (delta_time.tv_sec != 0)
			    || (delta_time.tv_usec > tkbwait))
			{   /*	Either the ball has moved or more than tkbwait
				microsecs. have past since last button 
				interrupt */
				ipaddr->count = 3;
				ipaddr->dr = RPR | (i << 4) | 1;
				ipSU->trk.status = trk_stat;
				ipSU->trk.control = ipaddr->dr;
				ipSU->trk.x = ipaddr->dr;
				ipSU->trk.y = ipaddr->dr;
				if (ipSU->sub_state&IPS_WANT_SIG
				    && (ipSU->ip_TBpending == 0)
				    && ipSU->ip_procp!=(struct proc *)0
				    && ipSU->ip_procp->p_pid == ipSU->ip_pid)
					psignal (ipSU->ip_procp, ipSU->ip_sig);
				ipSU->ip_TBpending = 1;
				ipSU->b_time = time_now;
				wakeup((caddr_t) &ipSU->ip_TBpending);
			}
		}
		devices = devices >> 1;
		ipSU++;
	}
}
/*******************************************************************/
ipclose(dev)
dev_t dev;
{
	register struct ipdevice *ipaddr = 
		(struct ipdevice *)ipdinfo[IPUNIT(dev)]->ui_addr;
	register struct unit   *ipU  = &ip_unit[ IPUNIT(dev)];
	register struct subunit *ipSU = &ipU->ip_subunit[SUBUNIT(dev)];
	register struct uba_device *ui = ipdinfo[IPUNIT(dev)];
	int i;
#ifdef	notdef
	if (	IPUNIT(dev) >= NIP
			|| ipU->ip_state
			|| ui == 0
			|| ui->ui_alive == 0)
		return(ENXIO);
#endif
	ipSU->ip_procp = (struct proc *) 0;
	ipSU->ip_pid   = 0;
	ipSU->ip_sig   = 0;
	ipSU->sub_state = 0;

	if(ipSU->trk.control)
	{	/* Disable trackball */
		ipaddr->count = 1;
		ipaddr->dr = LPR |(SUBUNIT(dev) << 4) | 1;
		ipaddr->dr = 0;
	}
	if (ipSU->ipasub.processor)
	{	/* deallocate DVP */
		ipU->ipa.processor |= ipSU->ipasub.processor;
		ipSU->ipasub.processor = 0;
		wakeup((caddr_t) &ipU->ipa.processor);
	}
	if (ipSU->ipasub.digitizer)
	{	/* deallocate digitizer */
		ipU->ipa.digitizer |= ipSU->ipasub.digitizer;
		ipSU->ipasub.digitizer = 0;
		wakeup((caddr_t) &ipU->ipa.digitizer);
	}
	if (ipSU->ipasub.memory)
	{	/* deallocate memory */
		ipU->ipa.memory |= ipSU->ipasub.memory;
		ipSU->ipasub.memory = 0;
		wakeup((caddr_t) &ipU->ipa.memory);
	}
	for (i = 0; i < NVOC; i++)
		if(ipU->ip_subunit[i].sub_state != 0)
			break;
	if (i == NVOC)
	{
		ipaddr->cmd = 0;
		ipaddr->dacs = 0;
		ipU->ip_state = 0;
	}
	return;
}

/*******************************************************************/
/* a UNIBUS is being reset, we must reset specified ip8500 */
ipreset(uban)
int uban;
{
	register int unit;
	register struct uba_device *ui;

	for (unit = 0; unit < NIP; unit++)
	{
		ui = ipdinfo[unit];
		if (ui == 0 || ui->ui_ubanum != uban || ui->ui_alive == 0)
			continue;
		ipreset_cntrl (unit);
		printf(" ip%d", unit);
	}
}

/*******************************************************************/
/* convert IP8500 opcode to an array index or error code if nonexist */

/* NOT CURRENTLY USED

ipoper (opcode)
short opcode;
{
	if (opcode >= 0 && opcode <= 6)
		return(opcode);
	if (opcode >= 0100 && opcode <= 0122)
		return(opcode - 0100 + 010);
	if (opcode >= 0200 && opcode <= 0224)
		return(opcode - 0200 + 040);
	return(-1);
}
*/

/*******************************************************************/
/* Claim IP8500 controller */
ipget_cntlr (dev)
dev_t dev;
{
	register struct unit   *ipU  = &ip_unit[dev];
	register struct buf *bp = &ripbuf[dev];	/* I/O buffer pointer */
	int s;

	s=spl6();
	while (bp->b_flags & B_BUSY)
	{
		bp->b_flags |= B_WANTED;
		sleep ((caddr_t)bp, PRIBIO + 1);
	}
	splx(s);
	bp->b_flags |= B_BUSY;
}

/*******************************************************************/
/* Release IP8500 controller */
iprel_cntlr (dev)
dev_t dev;
{
	register struct unit   *ipU  = &ip_unit[dev];
	register struct buf *bp = &ripbuf[dev];	/* I/O buffer pointer */
	int s;

	s = spl6();
	if (bp->b_flags & B_WANTED)
		wakeup ((caddr_t)bp);
	splx(s);
	bp->b_flags &= ~(B_BUSY | B_WANTED);
}

/*******************************************************************/
/* Reset IP8500 controller */
ipreset_cntrl (dev)
dev_t dev;
{
	struct uba_device *ui = ipdinfo[dev];
	register struct ipdevice *ipaddr = (struct ipdevice *)ui->ui_addr;

	ipaddr->cmd = SYSRESET;
	DELAY(1000);
	ipaddr->dr = LR|COUNT;
	ipaddr->dr = 0;
	ipaddr->cmd = 0x1408;
	ipaddr->dacs = IP_IE;
	if (resetip_on)
		printf ("ip%d: Reset.\n", dev);
	return;
}
/*******************************************************************/
/* Save and restore interface registers to preserve environment in a
	multi-user situation. */

ip_set_environ (dev)
dev_t dev;
{
	register struct ipdevice *ipaddr 
		= (struct ipdevice *)ipdinfo[IPUNIT(dev)]->ui_addr;
	register struct iptrack *iptr;
	register struct unit   *ipU  = &ip_unit[IPUNIT(dev)];
	register struct subunit *ipSU = &ipU->ip_subunit[SUBUNIT(dev)];
	register short *ip_s;
	int i;

	if (ipU->ip_curEnviron != &ipSU->sub_env)
	{

		ip_s = (short *)ipU->ip_curEnviron;
		ipaddr->count = sizeof(struct environ) >> 1;
		ipaddr->dr = RR|0200|10;
		for (i = sizeof(struct environ) >> 1; i; i--)
			*ip_s++ = ipaddr->dr;
		ip_s = (short *)&ipSU->sub_env;
		ipaddr->count = sizeof(struct environ) >> 1;
		ipaddr->dr = LR|0200|10;
		for (i = sizeof(struct environ) >> 1; i; i--)
			ipaddr->dr = *ip_s++ ;
		ipU->ip_curEnviron = &ipSU->sub_env;
	}
	return;
}
/*******************************************************************/
/*	Timeout handler.  Called if i/o operation hangs. */
ip_timeout (dev)
dev_t dev;
{
	register struct ipdevice *ipaddr 
		= (struct ipdevice *)ipdinfo[IPUNIT(dev)]->ui_addr;
	register struct unit   *ipU  = &ip_unit[IPUNIT(dev)];

	if (ipU->ip_state & GTU_ACTIVE)
	{
		ipaddr->count = 1;	/* read control-0 & status */
		ipaddr->dr = RMC | (18 << 3) | 0;
		ipU->gtu_cntl_stat = ipaddr->dr;

		ipaddr->count = 1;	/* reset gtu */
		ipaddr->dr = LMC | (18 << 3) | 0;
		ipaddr->dr = GTU_RESET;

		ipU->ip_state &= ~GTU_ACTIVE;
		ipU->ip_state |= GTU_TIMEOUT;
		wakeup((caddr_t) &ipU->ip_state);
		printf ("ip%d:  GTU timeout, stat = 0x%x\n", IPUNIT(dev),
				ipU->gtu_cntl_stat >> 8);
	}
}
#endif
