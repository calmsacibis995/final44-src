/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * Copyright (c) 1986 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 *
 */

/*
 **********************************************************************
 * HISTORY
 * $Log:	uda.c,v $
 * Revision 2.4  89/03/09  21:17:44  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/26  14:36:29  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  88/08/08  13:48:02  rvb
 * Synchronize the offset table with what the os normally uses.
 * This means that CS_GENERIC must be defined as 1 and CS_DISK
 * must be set as required for your disks.
 * Fix uda unitialization so you can now mistype the boot name
 * and try again.
 * 
 *
 * 16-Apr-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Fixed to handle more than a single controller (although still
 *	only one per boot).
 *	[ V5.1(F8) ]
 *
 * 10-Dec-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Supply a reasonable default for "off" when disk type is unknown.
 *
 * 10-Dec-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Updated for 4.3 (what a pain it's been).  I also think I fixed
 *	the uVax II boot hanging program by adding a bit more
 *	initialization to raopen.
 *
 * 11-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Support for KDB50 controller on a BI bus.  Note that conditional
 *	compilation was not used.  The main reason was because it was
 *	difficult to fit bootra in 7.5K with conditional compilation.
 *	Besides, I'm getting sick and tired of conditional compilation
 *	for features we obviously always want.
 *
 **********************************************************************
 */

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)uda.c	7.1 (Berkeley) 6/5/86
 */

/*
 * UDA50/RAxx disk device driver
 */
#include <machine/pte.h>

#include <sys/param.h>
#include <sys/inode.h>
#include <sys/fs.h>

#include "saio.h"
#include "savax.h"

#define NRA	4
/*
 * Parameters for the communications area
 */
#define NRSPL2	0
#define NCMDL2	0
#define NRSP	(1<<NRSPL2)
#define NCMD	(1<<NCMDL2)

#define NBI 1

#include <vaxuba/udareg.h>
#include <vaxuba/ubareg.h>
#include <vax/mscp.h>

#include <vax/bi_node.h>

u_short udastd[] = { 0772150, 0760334, 0760340, 0 };

struct iob	cudbuf;

struct udadevice *udaddr = 0;
int	iskdb50 = 0;

struct uda {
	struct udaca	uda_ca;
	struct mscp	uda_rsp;
	struct mscp	uda_cmd;
} uda;

struct uda *ud_ubaddr;			/* Unibus address of uda structure */

int uda_off[] = { 0, 15884, 0, -1, -1, -1, 49324, 131404 };


/* THIS SHOULD BE READ OFF THE PACK, PER DRIVE */
/* BUT AT THE VERY LEAST THE OS AND STANDALONE MUST USE THE SAME TABLE */
struct size {
	daddr_t nblocks;
	daddr_t offset;
}  ra25_sizes[8] = {
	15884,	0,		/* A=blk 0 thru 15883 */
	10032,	15884,		/* B=blk 15884 thru 49323 */
	-1,	0,		/* C=blk 0 thru end */
	0,	0,		/* D=blk 340670 thru 356553 */
	0,	0,		/* E=blk 356554 thru 412489 */
	0,	0,		/* F=blk 412490 thru end */
	-1,	25916,		/* G=blk 49324 thru 131403 */
	0,	0,		/* H=blk 131404 thru end */
}, rd52_sizes[8] = {
	15884,	0,		/* A=blk 0 thru 15883 */
	9766,	15884,		/* B=blk 15884 thru 25649 */
	-1,	0,		/* C=blk 0 thru end */
#if	CS_DISK
	32000,	9766+15884,	/* D=blk 25650 thru 57649 */
	-1,	9766+15884+32000,/* E=blk 57650 thru end */
	-1,	15884,		/* F=blk 15884 thru end */
#else	CS_DISK
	0,	0,		/* D=unused */
	0,	0,		/* E=unused */
	0,	0,		/* F=unused */
#endif	CS_DISK
	-1,	25650,		/* G=blk 25650 thru end */
#if	CS_DISK
	-1,	9766+15884,	/* H=blk 25650 thru end */
#else	CS_DISK
	0,	0,		/* H=unused */
#endif	CS_DISK
}, rd53_sizes[8] = {
	15884,	0,		/* A=blk 0 thru 15883 */
	33440,	15884,		/* B=blk 15884 thru 49323 */
	-1,	0,		/* C=blk 0 thru end */
#if	CS_DISK
	34830,	15884+33440,	/* D=blk 49324 thru 84153 */
	-1,	15884+33440+34830,/* E=blk 84154 thru end */
	0,	0,		/* F=blk 0 thru end */
#else	CS_DISK
	0,	0,		/* D=unused */
	33440,	0,		/* E=blk 0 thru 33439 */
	-1,	33440,		/* F=blk 33440 thru end */
#endif	CS_DISK
	-1,	49324,		/* G=blk 49324 thru end */
#if	CS_DISK
	-1,	15884+33440,	/* H=blk 49324 thru end */
#else	CS_DISK
	-1,	15884,		/* H=blk 15884 thru end */
#endif	CS_DISK
}, rd54_sizes[8] ={
	15884,	0,		/* A=blk 0 thru 15883 */
	33440,	15884,		/* B=blk 15884 thru 49323 */
	-1,	0,		/* C=blk 0 thru end 311200 */
	130938,	49324,		/* D=blk 49324 thru 180261 */
	-1,	180262,		/* E=blk 180262 thru end   */
	0,	0,
	-1,	49324,		/* G=blk 49324 thru end */
	0,	0
}, rx50_sizes[8] = {
	800,	0,		/* A = sectors 0 thru 799 */
	0,	0,
	0,	0,
	0,	0,
	0,	0,
	0,	0,
	0,	0,
	0,	0,
}, ra60_sizes[8] = {
	15884,	0,		/* A=sectors 0 thru 15883 */
	33440,	15884,		/* B=sectors 15884 thru 49323 */
	400176,	0,		/* C=sectors 0 thru 400175 */
	82080,	49324,		/* 4.2 G => D=sectors 49324 thru 131403 */
	268772,	131404,		/* 4.2 H => E=sectors 131404 thru 400175 */
	350852,	49324,		/* F=sectors 49324 thru 400175 */
	157570,	242606,		/* UCB G => G=sectors 242606 thru 400175 */
	193282,	49324,		/* UCB H => H=sectors 49324 thru 242605 */
}, ra70_sizes[8] = {
	15884,	0,		/* A=blk 0 thru 15883 */
	33440,	15884,		/* B=blk 15884 thru 49323 */
	-1,	0,		/* C=blk 0 thru end (547041) */
	138545,	131404,	 	/* D=blk 131404 thru 269948 */
	138545,	269949,	 	/* E=blk 269949 thru 408493 */
	-1,	408494,		/* F=blk 408494 thru end */
	82080,	49324,		/* G=blk 49324 thru 131403 */
	-1,	131404		/* H=blk 131404 thru end */
}, ra80_sizes[8] = {
	15884,	0,		/* A=sectors 0 thru 15883 */
	33440,	15884,		/* B=sectors 15884 thru 49323 */
#if	CS_DISK
	-1,	0,		/* C=sectors 0 thru end */
	34830,	15884+33440,	/* D=blk 49324 thru 84153 */
	-1,	15884+33440+34830,/* E=blk 84154 thru end */
	0,	0,		/* F=blk 0 thru end */
	0,	0,		/* G=blk 0 thru end */
	-1,	15884+33440,	/* H=blk 49324 thru end */
#else	CS_DISK
	242606,	0,		/* C=sectors 0 thru 242605 */
	0,	0,		/* D=unused */
	193282,	49324,		/* UCB H => E=sectors 49324 thru 242605 */
	82080,	49324,		/* 4.2 G => F=sectors 49324 thru 131403 */
	192696,	49910,		/* G=sectors 49910 thru 242605 */
	111202,	131404,		/* 4.2 H => H=sectors 131404 thru 242605 */
#endif	CS_DISK
}, ra81_sizes[8] ={
#if	CS_DISK
	15884,	0,		/* A=blk 0 thru 15883 */
	33440,	15884,		/* B=blk 15884 thru 49323 */
	-1,	0,		/* C=blk 0 thru end */
	184458,	15884+33440,	/* D=blk 49324 thru 233781 */
	-1,	15884+33440+184458,/* E=blk 233782 thru end */
	368916,	15884+33440,	/* F=blk 49324 thru 418239 */
	-1,	15884+33440+368916,/* G=blk 418240 thru end */
	-1,	15884+33440,	/* H=blk 49324 thru end */
#else	CS_DISK
/*
 * These are the new standard partition sizes for ra81's.
 * An RA_COMPAT system is compiled with D, E, and F corresponding
 * to the 4.2 partitions for G, H, and F respectively.
 */
#ifndef	UCBRA
	15884,	0,		/* A=sectors 0 thru 15883 */
	66880,	16422,		/* B=sectors 16422 thru 83301 */
	891072,	0,		/* C=sectors 0 thru 891071 */
#ifdef	RA_COMPAT
	82080,	49324,		/* 4.2 G => D=sectors 49324 thru 131403 */
	759668,	131404,		/* 4.2 H => E=sectors 131404 thru 891071 */
	478582,	412490,		/* 4.2 F => F=sectors 412490 thru 891071 */
#else
	15884,	375564,		/* D=sectors 375564 thru 391447 */
	307200,	391986,		/* E=sectors 391986 thru 699185 */
	191352,	699720,		/* F=sectors 699720 thru 891071 */
#endif	RA_COMPAT
	515508,	375564,		/* G=sectors 375564 thru 891071 */
	291346,	83538,		/* H=sectors 83538 thru 374883 */

/*
 * These partitions correspond to the sizes used by sites at Berkeley,
 * and by those sites that have received copies of the Berkeley driver
 * with deltas 6.2 or greater (11/15/83).
 */
#else	UCBRA

	15884,	0,		/* A=sectors 0 thru 15883 */
	33440,	15884,		/* B=sectors 15884 thru 49323 */
	891072,	0,		/* C=sectors 0 thru 891071 */
	15884,	242606,		/* D=sectors 242606 thru 258489 */
	307200,	258490,		/* E=sectors 258490 thru 565689 */
	325382,	565690,		/* F=sectors 565690 thru 891071 */
	648466,	242606,		/* G=sectors 242606 thru 891071 */
	193282,	49324,		/* H=sectors 49324 thru 242605 */

#endif	UCBRA
#endif	CS_DISK
}, ra82_sizes[8] ={
	15884,	0,		/* A=blk 0 thru 15883 */
	66690,	15884,		/* B=blk 15884 thru 82573 */
	-1,	0,		/* C=blk 0 thru end */
	220096,	82574,	 	/* D=blk 82574 thru 302669 */
	219735,	302670,	 	/* E=blk 302670 thru 522404 */
	437760,	522405, 	/* F=blk 522405 thru 960164 */
	877591,	82574,		/* G=blk 82574 thru 960164 */
	-1,	960165		/* H=blk 960165 thru end */
};

struct mscp *udcmd();
static int ratype[NRA];

raopen(io)
	register struct iob *io;
{
	short *wr;
	static int udainit, udadriveinit[NRA];
	int i;
	daddr_t off;

	if (udaddr == 0)
		udaddr = (struct udadevice *)ubamem(io->i_unit,
			 udastd[UNITTOCTLR(io->i_unit)]);
	if (ud_ubaddr == 0) {
		/*
		 * Initialise cudbuf.i_unit so that controllers
		 * on UNIBUSes other than 0 can be used.
		 */
		cudbuf.i_unit = io->i_unit;
		cudbuf.i_ma = (caddr_t)&uda;
		cudbuf.i_cc = sizeof(uda);
		if (iskdb50)
			ud_ubaddr = (struct uda *) &uda;
		else
			ud_ubaddr = (struct uda *)ubasetup(&cudbuf, 2);
#ifdef	DEBUG
		printf("ud_ubaddr set to 0x%x.\n", ud_ubaddr);
#endif	DEBUG
	}
	if (udainit == 0) {
		udaddr->udaip = 0;
		if (iskdb50)
			wr = &(((struct kdb50device *)udaddr)->kdbwr);
		else
			wr = &udaddr->udasa;
#ifdef	DEBUG
		printf("Wait for step 1\n");
#endif	DEBUG
		while ((udaddr->udasa & UDA_STEP1) == 0)
			;
#ifdef	DEBUG
		printf("Wait for step 2\n");
#endif	DEBUG
		*wr = UDA_ERR;
		while ((udaddr->udasa & UDA_STEP2) == 0)
			;
#ifdef	DEBUG
		printf("Wait for step 3\n");
#endif	DEBUG
		*wr = (short)&ud_ubaddr->uda_ca.ca_ringbase;
		while ((udaddr->udasa & UDA_STEP3) == 0)
			;
#ifdef	DEBUG
		printf("Wait for step 4\n");
#endif	DEBUG
		*wr = (short)(((int)&ud_ubaddr->uda_ca.ca_ringbase) >> 16);
		while ((udaddr->udasa & UDA_STEP4) == 0)
			;
#ifdef	DEBUG
		printf("Step 4 complete\n");
#endif	DEBUG
		*wr = UDA_GO;
		uda.uda_ca.ca_rspdsc[0] = (long)&ud_ubaddr->uda_rsp.mscp_cmdref;
		uda.uda_ca.ca_cmddsc[0] = (long)&ud_ubaddr->uda_cmd.mscp_cmdref;
		uda.uda_rsp.mscp_dscptr = &uda.uda_ca.ca_rspdsc[0];
		uda.uda_cmd.mscp_dscptr = &uda.uda_ca.ca_cmddsc[0];
		uda.uda_rsp.mscp_header.uda_msglen = mscp_msglen;
		uda.uda_cmd.mscp_header.uda_msglen = mscp_msglen;
		uda.uda_cmd.mscp_cntflgs = 0;
		if (udcmd(M_OP_STCON) == 0) {
			_stop("ra: open error, STCON");
			return;
		}
	}
	i = io->i_unit & 7;
	if (udadriveinit[i] == 0) {
		uda.uda_cmd.mscp_unit = i;
		if (udcmd(M_OP_ONLIN) == 0) {
			_stop("ra: open error, ONLIN");
			return;
		}
		udainit = 1;
		udadriveinit[i] = 1;
	}
	if (io->i_boff < 0 || io->i_boff > 7)
		_stop("ra: bad unit");

	switch (ratype[i]) {
	case    25:
		off = ra25_sizes[io->i_boff].offset;
		break;
	case	50:
		off = rx50_sizes[io->i_boff].offset;
		break;
	case    52:
		off = rd52_sizes[io->i_boff].offset;
		break;
	case    53:
		off = rd53_sizes[io->i_boff].offset;
		break;
	case    54:
		off = rd54_sizes[io->i_boff].offset;
		break;
	case    60:
		off = ra60_sizes[io->i_boff].offset;
		break;
	case    70:
		off = ra70_sizes[io->i_boff].offset;
		break;
	case    80:
		off = ra80_sizes[io->i_boff].offset;
		break;
	case    81:
		off = ra81_sizes[io->i_boff].offset;
		break;
	case    82:
		off = ra82_sizes[io->i_boff].offset;
		break;
	default:
		off = uda_off[io->i_boff];
		break;
	}
	if (off == -1)
		_stop("ra: bad partition");
	io->i_boff = off;
}

struct mscp *
udcmd(op)
	int op;
{
	struct mscp *mp;
	int i;

	uda.uda_cmd.mscp_opcode = op;
	uda.uda_rsp.mscp_header.uda_msglen = sizeof (struct mscp);
	uda.uda_cmd.mscp_header.uda_msglen = sizeof (struct mscp);
	uda.uda_ca.ca_rspdsc[0] |= UDA_OWN|UDA_INT;
	uda.uda_ca.ca_cmddsc[0] |= UDA_OWN|UDA_INT;
	i = udaddr->udaip;
	for (;;) {
		if (uda.uda_ca.ca_cmdint)
			uda.uda_ca.ca_cmdint = 0;
		if (uda.uda_ca.ca_rspint)
			break;
	}
	uda.uda_ca.ca_rspint = 0;
	mp = &uda.uda_rsp;
	if (mp->mscp_opcode != (op|M_OP_END) ||
	    (mp->mscp_status&M_ST_MASK) != M_ST_SUCC)
		return(0);
	if (mp->mscp_opcode == (M_OP_ONLIN|M_OP_END))
		ratype[uda.uda_cmd.mscp_unit] = mp->mscp_mediaid & 0x7f;
	return(mp);
}

rastrategy(io, func)
	register struct iob *io;
{
	register struct mscp *mp;
	int ubinfo;

	if (!iskdb50)
		ubinfo = ubasetup(io, 1);
	mp = &uda.uda_cmd;
	mp->mscp_lbn = io->i_bn;
	mp->mscp_unit = io->i_unit&7;
	mp->mscp_bytecnt = io->i_cc;
	if (iskdb50)
		mp->mscp_buffer = (int)io->i_ma;
	else
		mp->mscp_buffer = (ubinfo & 0x3fffff) | (((ubinfo>>28)&0xf)<<24);
	if ((mp = udcmd(func == READ ? M_OP_READ : M_OP_WRITE)) == 0) {
		printf("ra: I/O error\n");
		if (!iskdb50)
			ubafree(io, ubinfo);
		return(-1);
	}
	if (!iskdb50)
		ubafree(io, ubinfo);
	return(io->i_cc);
}

/*ARGSUSED*/
raioctl(io, cmd, arg)
	struct iob *io;
	int cmd;
	caddr_t arg;
{

	return (ECMD);
}
