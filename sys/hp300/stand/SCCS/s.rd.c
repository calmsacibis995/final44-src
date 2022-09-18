h54944
s 00002/00002/00345
d D 8.1 93/07/15 16:59:48 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00346
d D 7.9 93/07/15 16:11:34 hibler 10 8
c don't check unit vs. ri_maxunum, it isn't the right value anyway
e
s 00002/00002/00345
d R 8.1 93/06/10 21:47:37 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00346
d D 7.8 93/05/24 22:50:07 mckusick 8 7
c fix include directives
e
s 00132/00053/00215
d D 7.7 92/12/26 16:49:47 hibler 7 6
c Utah update (mostly disklabels)
e
s 00004/00004/00264
d D 7.6 92/10/11 10:01:48 bostic 6 5
c make kernel includes standard
e
s 00004/00000/00264
d D 7.5 92/08/14 09:28:01 hibler 5 4
c missing "return(0)" in open, check for 0-length IO requests
e
s 00065/00051/00199
d D 7.4 92/06/18 21:33:34 hibler 4 3
c merge with latest Utah version
e
s 00002/00001/00248
d D 7.3 91/05/05 13:32:25 bostic 3 2
c includes for standard stand source, READ, WRITE -> F_READ, FWRITE
e
s 00001/00001/00248
d D 7.2 90/12/16 16:39:43 bostic 2 1
c kernel reorg
e
s 00249/00000/00000
d D 7.1 90/05/08 22:46:11 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 11
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 4
 * from: Utah $Hdr: rd.c 1.14 89/02/27$
E 4
I 4
D 7
 * from: Utah $Hdr: rd.c 1.17 92/06/18$
E 7
I 7
 * from: Utah $Hdr: rd.c 1.20 92/12/21$
E 7
E 4
 *
 *	%W% (Berkeley) %G%
 */

/*
 * CS80/SS80 disk driver
 */
I 3
D 4
#include <sys/param.h>
E 4
I 4
D 6
#include "sys/param.h"
E 4
E 3
#include "saio.h"
#include "samachdep.h"
E 6
I 6
#include <sys/param.h>
I 7
#include <sys/disklabel.h>
E 7
D 8
#include <stand/saio.h>
E 8
I 8
#include <stand.att/saio.h>
E 8
#include <hp300/stand/samachdep.h>
E 6

D 2
#include "../hpdev/rdreg.h"
E 2
I 2
D 6
#include "../dev/rdreg.h"
E 6
I 6
#include <hp300/dev/rdreg.h>
E 6
E 2

struct	rd_iocmd rd_ioc;
struct	rd_rscmd rd_rsc;
struct	rd_stat rd_stat;
struct	rd_ssmcmd rd_ssmc;

I 7
struct	disklabel rdlabel;

struct	rdminilabel {
	u_short	npart;
	u_long	offset[MAXPARTITIONS];
};

E 7
struct	rd_softc {
	char	sc_retry;
	char	sc_alive;
	short	sc_type;
I 7
	struct	rdminilabel sc_pinfo;
E 7
D 4
} rd_softc[NRD];
E 4
I 4
} rd_softc[NHPIB][NRD];
E 4

#define	RDRETRY		5

D 7
int rdcyloff[][8] = {
	{ 1, 143, 0, 143, 0,   0,   323, 503, },	/* 7945A */
	{ 1, 167, 0, 0,   0,   0,   0,   0,   },	/* 9134D */
	{ 0, 0,   0, 0,   0,   0,   0,   0,   },	/* 9122S */
	{ 0, 71,  0, 221, 292, 542, 221, 0,   },	/* 7912P */
	{ 1, 72,  0, 72,  362, 802, 252, 362, },	/* 7914P */
	{ 1, 28,  0, 140, 167, 444, 140, 721, },	/* 7933H */
	{ 1, 200, 0, 200, 0,   0,   450, 600, },	/* 9134L */
	{ 1, 105, 0, 105, 380, 736, 265, 380, },	/* 7957A */
	{ 1, 65,  0, 65,  257, 657, 193, 257, },	/* 7958A */
	{ 1, 128, 0, 128, 518, 918, 388, 518, },	/* 7957B */
	{ 1, 44,  0, 44,  174, 496, 131, 174, },	/* 7958B */
D 4
	{ 1, 44,  0, 44,  218, 918, 174, 218, },	/* 7959B */
E 4
I 4
	{ 1, 44,  0, 44,  218, 1022,174, 218, },	/* 7959B */
	{ 1, 37,  0, 37,  183, 857, 147, 183, },	/* 2200A */
	{ 1, 19,  0, 94,  112, 450, 94,  788, },	/* 2203A */
E 4
	{ 1, 20,  0, 98,  117, 256, 98,  397, },	/* 7936H */
	{ 1, 11,  0, 53,  63,  217, 53,  371, },	/* 7937H */
E 7
I 7
struct	rdidentinfo {
	short	ri_hwid;
	short	ri_maxunum;
	int	ri_nblocks;
} rdidentinfo[] = {
	{ RD7946AID,	0,	 108416 },
	{ RD9134DID,	1,	  29088 },
	{ RD9134LID,	1,	   1232 },
	{ RD7912PID,	0,	 128128 },
	{ RD7914PID,	0,	 258048 },
	{ RD7958AID,	0,	 255276 },
	{ RD7957AID,	0,	 159544 },
	{ RD7933HID,	0,	 789958 },
	{ RD9134LID,	1,	  77840 },
	{ RD7936HID,	0,	 600978 },
	{ RD7937HID,	0,	1116102 },
	{ RD7914CTID,	0,	 258048 },
	{ RD7946AID,	0,	 108416 },
	{ RD9134LID,	1,	   1232 },
	{ RD7957BID,	0,	 159894 },
	{ RD7958BID,	0,	 297108 },
	{ RD7959BID,	0,	 594216 },
	{ RD2200AID,	0,	 654948 },
	{ RD2203AID,	0,	1309896 }
E 7
};
I 7
int numrdidentinfo = sizeof(rdidentinfo) / sizeof(rdidentinfo[0]);
E 7

D 7
struct rdinfo {
	int	nbpc;
	int	hwid;
	int	*cyloff;
} rdinfo[] = {
	NRD7945ABPT*NRD7945ATRK, RD7946AID, rdcyloff[0],
	NRD9134DBPT*NRD9134DTRK, RD9134DID, rdcyloff[1],
	NRD9122SBPT*NRD9122STRK, RD9134LID, rdcyloff[2],
	NRD7912PBPT*NRD7912PTRK, RD7912PID, rdcyloff[3],
	NRD7914PBPT*NRD7914PTRK, RD7914PID, rdcyloff[4],
	NRD7958ABPT*NRD7958ATRK, RD7958AID, rdcyloff[8],
	NRD7957ABPT*NRD7957ATRK, RD7957AID, rdcyloff[7],
	NRD7933HBPT*NRD7933HTRK, RD7933HID, rdcyloff[5],
	NRD9134LBPT*NRD9134LTRK, RD9134LID, rdcyloff[6],
D 4
	NRD7936HBPT*NRD7936HTRK, RD7936HID, rdcyloff[12],
	NRD7937HBPT*NRD7937HTRK, RD7937HID, rdcyloff[13],
E 4
I 4
	NRD7936HBPT*NRD7936HTRK, RD7936HID, rdcyloff[14],
	NRD7937HBPT*NRD7937HTRK, RD7937HID, rdcyloff[15],
E 4
	NRD7914PBPT*NRD7914PTRK, RD7914CTID,rdcyloff[4],
	NRD7945ABPT*NRD7945ATRK, RD7946AID, rdcyloff[0],
	NRD9122SBPT*NRD9122STRK, RD9134LID, rdcyloff[2],
	NRD7957BBPT*NRD7957BTRK, RD7957BID, rdcyloff[9],
	NRD7958BBPT*NRD7958BTRK, RD7958BID, rdcyloff[10],
	NRD7959BBPT*NRD7959BTRK, RD7959BID, rdcyloff[11],
I 4
	NRD2200ABPT*NRD2200ATRK, RD2200AID, rdcyloff[12],
	NRD2203ABPT*NRD2203ATRK, RD2203AID, rdcyloff[13],
E 4
};
int	nrdinfo = sizeof(rdinfo) / sizeof(rdinfo[0]);
					
E 7
D 4
rdinit(unit)
	register int unit;
E 4
I 4
rdinit(ctlr, unit)
	int ctlr, unit;
E 4
{
D 4
	register struct rd_softc *rs;
E 4
I 4
	register struct rd_softc *rs = &rd_softc[ctlr][unit];
E 4
	u_char stat;

D 4
	if (unit > NRD)
		return (0);
	rs = &rd_softc[unit];
	rs->sc_type = rdident(unit);
E 4
I 4
	rs->sc_type = rdident(ctlr, unit);
E 4
	if (rs->sc_type < 0)
		return (0);
	rs->sc_alive = 1;
	return (1);
}

D 4
rdreset(unit)
E 4
I 4
rdreset(ctlr, unit)
	register int ctlr, unit;
E 4
{
	u_char stat;

	rd_ssmc.c_unit = C_SUNIT(0);
	rd_ssmc.c_cmd = C_SSM;
	rd_ssmc.c_refm = REF_MASK;
	rd_ssmc.c_fefm = FEF_MASK;
	rd_ssmc.c_aefm = AEF_MASK;
	rd_ssmc.c_iefm = IEF_MASK;
D 4
	hpibsend(unit, C_CMD, &rd_ssmc, sizeof(rd_ssmc));
	hpibswait(unit);
	hpibrecv(unit, C_QSTAT, &stat, 1);
E 4
I 4
	hpibsend(ctlr, unit, C_CMD, &rd_ssmc, sizeof(rd_ssmc));
	hpibswait(ctlr, unit);
	hpibrecv(ctlr, unit, C_QSTAT, &stat, 1);
E 4
}

D 4
rdident(unit)
E 4
I 4
rdident(ctlr, unit)
	register int ctlr, unit;
E 4
{
	struct rd_describe desc;
	u_char stat, cmd[3];
	char name[7];
	register int id, i;

D 4
	id = hpibid(unit);
E 4
I 4
	id = hpibid(ctlr, unit);
E 4
	if ((id & 0x200) == 0)
		return(-1);
D 7
	for (i = 0; i < nrdinfo; i++)
		if (id == rdinfo[i].hwid)
E 7
I 7
	for (i = 0; i < numrdidentinfo; i++)
		if (id == rdidentinfo[i].ri_hwid)
E 7
			break;
D 7
	if (i == nrdinfo)
E 7
I 7
D 10
	if (i == numrdidentinfo || unit > rdidentinfo[i].ri_maxunum)
E 10
I 10
	if (i == numrdidentinfo)
E 10
E 7
		return(-1);
	id = i;
D 4
	rdreset(unit);
E 4
I 4
	rdreset(ctlr, unit);
E 4
	cmd[0] = C_SUNIT(0);
	cmd[1] = C_SVOL(0);
	cmd[2] = C_DESC;
D 4
	hpibsend(unit, C_CMD, cmd, sizeof(cmd));
	hpibrecv(unit, C_EXEC, &desc, 37);
	hpibrecv(unit, C_QSTAT, &stat, sizeof(stat));
E 4
I 4
	hpibsend(ctlr, unit, C_CMD, cmd, sizeof(cmd));
	hpibrecv(ctlr, unit, C_EXEC, &desc, 37);
	hpibrecv(ctlr, unit, C_QSTAT, &stat, sizeof(stat));
E 4
	bzero(name, sizeof(name));
	if (!stat) {
		register int n = desc.d_name;
		for (i = 5; i >= 0; i--) {
			name[i] = (n & 0xf) + '0';
			n >>= 4;
		}
	}
	/*
	 * Take care of a couple of anomolies:
	 * 1. 7945A and 7946A both return same HW id
	 * 2. 9122S and 9134D both return same HW id
	 * 3. 9122D and 9134L both return same HW id
	 */
D 7
	switch (rdinfo[id].hwid) {
E 7
I 7
	switch (rdidentinfo[id].ri_hwid) {
E 7
	case RD7946AID:
		if (bcmp(name, "079450", 6) == 0)
			id = RD7945A;
		else
			id = RD7946A;
		break;

	case RD9134LID:
		if (bcmp(name, "091340", 6) == 0)
			id = RD9134L;
		else
			id = RD9122D;
		break;

	case RD9134DID:
		if (bcmp(name, "091220", 6) == 0)
			id = RD9122S;
		else
			id = RD9134D;
		break;
	}
	return(id);
}

I 7
#ifdef COMPAT_NOLABEL
int rdcyloff[][8] = {
	{ 1, 143, 0, 143, 0,   0,   323, 503, },	/* 7945A */
	{ 1, 167, 0, 0,   0,   0,   0,   0,   },	/* 9134D */
	{ 0, 0,   0, 0,   0,   0,   0,   0,   },	/* 9122S */
	{ 0, 71,  0, 221, 292, 542, 221, 0,   },	/* 7912P */
	{ 1, 72,  0, 72,  362, 802, 252, 362, },	/* 7914P */
	{ 1, 28,  0, 140, 167, 444, 140, 721, },	/* 7933H */
	{ 1, 200, 0, 200, 0,   0,   450, 600, },	/* 9134L */
	{ 1, 105, 0, 105, 380, 736, 265, 380, },	/* 7957A */
	{ 1, 65,  0, 65,  257, 657, 193, 257, },	/* 7958A */
	{ 1, 128, 0, 128, 518, 918, 388, 518, },	/* 7957B */
	{ 1, 44,  0, 44,  174, 496, 131, 174, },	/* 7958B */
	{ 1, 44,  0, 44,  218, 1022,174, 218, },	/* 7959B */
	{ 1, 37,  0, 37,  183, 857, 147, 183, },	/* 2200A */
	{ 1, 19,  0, 94,  112, 450, 94,  788, },	/* 2203A */
	{ 1, 20,  0, 98,  117, 256, 98,  397, },	/* 7936H */
	{ 1, 11,  0, 53,  63,  217, 53,  371, },	/* 7937H */
};

struct rdcompatinfo {
	int	nbpc;
	int	*cyloff;
} rdcompatinfo[] = {
	NRD7945ABPT*NRD7945ATRK, rdcyloff[0],
	NRD9134DBPT*NRD9134DTRK, rdcyloff[1],
	NRD9122SBPT*NRD9122STRK, rdcyloff[2],
	NRD7912PBPT*NRD7912PTRK, rdcyloff[3],
	NRD7914PBPT*NRD7914PTRK, rdcyloff[4],
	NRD7958ABPT*NRD7958ATRK, rdcyloff[8],
	NRD7957ABPT*NRD7957ATRK, rdcyloff[7],
	NRD7933HBPT*NRD7933HTRK, rdcyloff[5],
	NRD9134LBPT*NRD9134LTRK, rdcyloff[6],
	NRD7936HBPT*NRD7936HTRK, rdcyloff[14],
	NRD7937HBPT*NRD7937HTRK, rdcyloff[15],
	NRD7914PBPT*NRD7914PTRK, rdcyloff[4],
	NRD7945ABPT*NRD7945ATRK, rdcyloff[0],
	NRD9122SBPT*NRD9122STRK, rdcyloff[2],
	NRD7957BBPT*NRD7957BTRK, rdcyloff[9],
	NRD7958BBPT*NRD7958BTRK, rdcyloff[10],
	NRD7959BBPT*NRD7959BTRK, rdcyloff[11],
	NRD2200ABPT*NRD2200ATRK, rdcyloff[12],
	NRD2203ABPT*NRD2203ATRK, rdcyloff[13],
};
int	nrdcompatinfo = sizeof(rdcompatinfo) / sizeof(rdcompatinfo[0]);
#endif					

rdgetinfo(io)
	register struct iob *io;
{
	struct rd_softc *rs = &rd_softc[io->i_adapt][io->i_ctlr];
	register struct rdminilabel *pi = &rs->sc_pinfo;
	register struct disklabel *lp = &rdlabel;
	char *msg, *readdisklabel();
	int rdstrategy(), i;

	bzero((caddr_t)lp, sizeof *lp);
	lp->d_secsize = DEV_BSIZE;
	msg = readdisklabel(io, rdstrategy, lp);
	if (msg) {
		printf("rd(%d,%d,%d,%d): WARNING: %s, ",
		       io->i_adapt, io->i_ctlr, io->i_unit, io->i_part, msg);
#ifdef COMPAT_NOLABEL
		{
			register struct rdcompatinfo *ci;

			printf("using old default partitioning\n");
			ci = &rdcompatinfo[rs->sc_type];
			pi->npart = 8;
			for (i = 0; i < pi->npart; i++)
				pi->offset[i] = ci->cyloff[i] * ci->nbpc;
		}
#else
		printf("defining `c' partition as entire disk\n");
		pi->npart = 3;
		pi->offset[0] = pi->offset[1] = -1;
		pi->offset[2] = 0;
#endif
	} else {
		pi->npart = lp->d_npartitions;
		for (i = 0; i < pi->npart; i++)
			pi->offset[i] = lp->d_partitions[i].p_size == 0 ?
				-1 : lp->d_partitions[i].p_offset;
	}
	return(1);
}

E 7
rdopen(io)
	struct iob *io;
{
D 4
	register int unit = io->i_unit;
	register struct rd_softc *rs = &rd_softc[unit];
E 4
I 4
	register struct rd_softc *rs;
E 4
	struct rdinfo *ri;
I 4
	int unit, ctlr, part;
E 4

D 4
	if (hpibalive(unit) == 0)
		_stop("rd controller not configured");
E 4
I 4
	devconvert(io);

	ctlr = io->i_adapt;
	if (ctlr >= NHPIB || hpibalive(ctlr) == 0)
		return (EADAPT);
	unit = io->i_ctlr;
	if (unit >= NRD)
		return (ECTLR);
	rs = &rd_softc[ctlr][unit];
E 4
D 7
	if (rs->sc_alive == 0)
E 7
I 7
	if (rs->sc_alive == 0) {
E 7
D 4
		if (rdinit(unit) == 0)
			_stop("rd init failed");
	if (io->i_boff < 0 || io->i_boff > 7)
		_stop("rd bad minor");
E 4
I 4
		if (rdinit(ctlr, unit) == 0)
			return (ENXIO);
I 7
		if (rdgetinfo(io) == 0)
			return (ERDLAB);
	}
E 7
	part = io->i_part;
D 7
	if (part >= 8)
E 7
I 7
	if (part >= rs->sc_pinfo.npart || rs->sc_pinfo.offset[part] == -1)
E 7
		return (EPART);
E 4
D 7
	ri = &rdinfo[rs->sc_type];
D 4
	io->i_boff = ri->cyloff[io->i_boff] * ri->nbpc;
E 4
I 4
	io->i_boff = ri->cyloff[part] * ri->nbpc;
E 7
I 7
	io->i_boff = rs->sc_pinfo.offset[part];
E 7
I 5
	return (0);
E 5
E 4
}

rdstrategy(io, func)
	register struct iob *io;
D 4
	register int func;
E 4
I 4
	int func;
E 4
{
D 4
	register int unit = io->i_unit;
	register struct rd_softc *rs = &rd_softc[unit];
E 4
I 4
	register int ctlr = io->i_adapt;
	register int unit = io->i_ctlr;
	register struct rd_softc *rs = &rd_softc[ctlr][unit];
E 4
	char stat;
I 5

	if (io->i_cc == 0)
		return(0);
E 5

	rs->sc_retry = 0;
	rd_ioc.c_unit = C_SUNIT(0);
	rd_ioc.c_volume = C_SVOL(0);
	rd_ioc.c_saddr = C_SADDR;
	rd_ioc.c_hiaddr = 0;
	rd_ioc.c_addr = RDBTOS(io->i_bn);
	rd_ioc.c_nop2 = C_NOP;
	rd_ioc.c_slen = C_SLEN;
	rd_ioc.c_len = io->i_cc;
D 3
	rd_ioc.c_cmd = func == READ ? C_READ : C_WRITE;
E 3
I 3
	rd_ioc.c_cmd = func == F_READ ? C_READ : C_WRITE;
E 3
retry:
D 4
	hpibsend(unit, C_CMD, &rd_ioc.c_unit, sizeof(rd_ioc)-2);
	hpibswait(unit);
	hpibgo(unit, C_EXEC, io->i_ma, io->i_cc, func);
	hpibswait(unit);
	hpibrecv(unit, C_QSTAT, &stat, 1);
E 4
I 4
	hpibsend(ctlr, unit, C_CMD, &rd_ioc.c_unit, sizeof(rd_ioc)-2);
	hpibswait(ctlr, unit);
	hpibgo(ctlr, unit, C_EXEC, io->i_ma, io->i_cc, func);
	hpibswait(ctlr, unit);
	hpibrecv(ctlr, unit, C_QSTAT, &stat, 1);
E 4
	if (stat) {
D 4
		if (rderror(unit) == 0)
E 4
I 4
		if (rderror(ctlr, unit, io->i_part) == 0)
E 4
			return(-1);
		if (++rs->sc_retry > RDRETRY)
			return(-1);
D 4
		else
			goto retry;
E 4
I 4
		goto retry;
E 4
	}
	return(io->i_cc);
}

D 4
rderror(unit)
	register int unit;
E 4
I 4
rderror(ctlr, unit, part)
	register int ctlr, unit;
	int part;
E 4
{
D 4
	register struct rd_softc *rd = &rd_softc[unit];
E 4
I 4
	register struct rd_softc *rd = &rd_softc[ctlr][unit];
E 4
	char stat;

	rd_rsc.c_unit = C_SUNIT(0);
	rd_rsc.c_sram = C_SRAM;
	rd_rsc.c_ram = C_RAM;
	rd_rsc.c_cmd = C_STATUS;
D 4
	hpibsend(unit, C_CMD, &rd_rsc, sizeof(rd_rsc));
	hpibrecv(unit, C_EXEC, &rd_stat, sizeof(rd_stat));
	hpibrecv(unit, C_QSTAT, &stat, 1);
E 4
I 4
	hpibsend(ctlr, unit, C_CMD, &rd_rsc, sizeof(rd_rsc));
	hpibrecv(ctlr, unit, C_EXEC, &rd_stat, sizeof(rd_stat));
	hpibrecv(ctlr, unit, C_QSTAT, &stat, 1);
E 4
	if (stat) {
D 4
		printf("rd(%d,?): request status fail %d\n", unit, stat);
E 4
I 4
		printf("rd(%d,%d,0,%d): request status fail %d\n",
		       ctlr, unit, part, stat);
E 4
		return(0);
	}
D 4
	printf("rd(%d,?) err: vu 0x%x", unit, rd_stat.c_vu);
E 4
I 4
	printf("rd(%d,%d,0,%d) err: vu 0x%x",
	       ctlr, unit, part, rd_stat.c_vu);
E 4
	if ((rd_stat.c_aef & AEF_UD) || (rd_stat.c_ief & (IEF_MD|IEF_RD)))
		printf(", block %d", rd_stat.c_blk);
	printf(", R0x%x F0x%x A0x%x I0x%x\n",
	       rd_stat.c_ref, rd_stat.c_fef, rd_stat.c_aef, rd_stat.c_ief);
	return(1);
}
E 1
