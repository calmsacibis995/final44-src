h54170
s 00002/00002/00249
d D 8.1 93/07/15 16:59:41 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00250
d D 7.8 93/07/15 16:11:00 hibler 9 7
c initialize variable in ctopen
e
s 00002/00002/00248
d R 8.1 93/06/10 21:46:37 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00249
d D 7.7 93/05/24 22:50:05 mckusick 7 6
c fix include directives
e
s 00005/00004/00245
d D 7.6 92/10/11 10:01:35 bostic 6 5
c make kernel includes standard
e
s 00004/00000/00245
d D 7.5 92/08/14 09:27:48 hibler 5 4
c missing "return(0)" in open, check for 0-length IO requests
e
s 00052/00047/00193
d D 7.4 92/06/18 21:33:18 hibler 4 3
c merge with latest Utah version
e
s 00004/00004/00236
d D 7.3 91/05/05 13:31:38 bostic 3 2
c READ, WRITE -> F_READ, FWRITE
e
s 00002/00002/00238
d D 7.2 90/12/16 16:39:12 bostic 2 1
c kernel reorg
e
s 00240/00000/00000
d D 7.1 90/05/08 22:46:01 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 10
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * CS80 tape driver
 */
D 2
#include "../sys/types.h"
#include "../hpdev/ctreg.h"
E 2
I 2
D 3
#include "sys/types.h"
E 3
I 3
D 4
#include <sys/param.h>
E 4
I 4
D 6
#include "sys/param.h"
E 4
E 3
#include "../dev/ctreg.h"
E 6
I 6
#include <sys/param.h>
E 6
E 2

D 6
#include "saio.h"
#include "samachdep.h"
E 6
I 6
#include <hp300/dev/ctreg.h>

D 7
#include <stand/saio.h>
E 7
I 7
#include <stand.att/saio.h>
E 7
#include <hp300/stand/samachdep.h>
E 6

struct	ct_iocmd ct_ioc;
struct	ct_rscmd ct_rsc;
struct	ct_stat ct_stat;
struct	ct_ssmcmd ct_ssmc;

struct	ct_softc {
	char	sc_retry;
	char	sc_alive;
	short	sc_punit;
	int	sc_blkno;
D 4
} ct_softc[NCT];
E 4
I 4
} ct_softc[NHPIB][NCT];
E 4

#define	CTRETRY		5
#define	MTFSF		10
#define	MTREW		11

struct	ctinfo {
	short	hwid;
	short	punit;
} ctinfo[] = {
	CT7946ID,	1,
	CT7912PID,	1,
	CT7914PID,	1,
	CT9144ID,	0,
	CT9145ID,	0,
};
int	nctinfo = sizeof(ctinfo) / sizeof(ctinfo[0]);

D 4
ctinit(unit)
	register int unit;
E 4
I 4
ctinit(ctlr, unit)
	register int ctlr, unit;
E 4
{
D 4
	register struct ct_softc *rs = &ct_softc[unit];
E 4
I 4
	register struct ct_softc *rs = &ct_softc[ctlr][unit];
E 4
	u_char stat;
	register int type;

D 4
	if (hpibrecv(unit, C_QSTAT, &stat, 1) != 1 || stat)
E 4
I 4
	if (hpibrecv(ctlr, unit, C_QSTAT, &stat, 1) != 1 || stat)
E 4
		return (0);
D 4
	if (ctident(unit) < 0)
E 4
I 4
	if (ctident(ctlr, unit) < 0)
E 4
		return (0);
	ct_ssmc.unit = C_SUNIT(rs->sc_punit);
	ct_ssmc.cmd = C_SSM;
	ct_ssmc.fefm = FEF_MASK;
	ct_ssmc.refm = REF_MASK;
	ct_ssmc.aefm = AEF_MASK;
	ct_ssmc.iefm = IEF_MASK;
D 4
	hpibsend(unit, C_CMD, &ct_ssmc, sizeof(ct_ssmc));
	hpibswait(unit);
	hpibrecv(unit, C_QSTAT, &stat, 1);
E 4
I 4
	hpibsend(ctlr, unit, C_CMD, &ct_ssmc, sizeof(ct_ssmc));
	hpibswait(ctlr, unit);
	hpibrecv(ctlr, unit, C_QSTAT, &stat, 1);
E 4
	rs->sc_alive = 1;
	return (1);
}

D 4
ctident(unit)
	int unit;
E 4
I 4
ctident(ctlr, unit)
	int ctlr, unit;
E 4
{
	struct ct_describe desc;
	u_char stat, cmd[3];
	char name[7];
	int id, i;

D 4
	id = hpibid(unit);
E 4
I 4
	id = hpibid(ctlr, unit);
E 4
	if ((id & 0x200) == 0)
		return(-1);
	for (i = 0; i < nctinfo; i++)
		if (id == ctinfo[i].hwid)
			break;
	if (i == nctinfo)
		return(-1);
D 4
	ct_softc[unit].sc_punit = ctinfo[i].punit;
E 4
I 4
	ct_softc[ctlr][unit].sc_punit = ctinfo[i].punit;
E 4
	id = i;

	/*
	 * Collect device description.
	 * Right now we only need this to differentiate 7945 from 7946.
	 * Note that we always issue the describe command to unit 0.
	 */
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
	switch (ctinfo[id].hwid) {
	case CT7946ID:
		if (bcmp(name, "079450", 6) == 0)
			id = -1;		/* not really a 7946 */
		break;
	default:
		break;
	}
	return(id);
}

ctopen(io)
	struct iob *io;
{
D 4
	register int unit = io->i_unit;
	register struct ct_softc *rs = &ct_softc[unit];
E 4
I 4
	register struct ct_softc *rs;
	register int unit, ctlr;
E 4
	register int skip;

D 4
	if (hpibalive(unit) == 0)
		_stop("ct controller not configured");
E 4
I 4
	devconvert(io);

	ctlr = io->i_adapt;
	if (ctlr >= NHPIB || hpibalive(ctlr) == 0)
		return(EADAPT);
	unit = io->i_ctlr;
	if (unit >= NCT)
		return(ECTLR);
I 9
	rs = &ct_softc[ctlr][unit];
E 9
E 4
	if (rs->sc_alive == 0)
D 4
		if (ctinit(unit) == 0)
			_stop("ct init failed");
E 4
I 4
		if (ctinit(ctlr, unit) == 0)
			return(ENXIO);
E 4
	ctstrategy(io, MTREW);
D 4
	skip = io->i_boff;
E 4
I 4
	skip = io->i_part;
E 4
	while (skip--)
		ctstrategy(io, MTFSF);
I 5
	return(0);
E 5
}

ctclose(io)
	struct iob *io;
{
	ctstrategy(io, MTREW);
}

ctstrategy(io, func)
	register struct iob *io;
	register int func;
{
D 4
	register int unit = io->i_unit;
	register struct ct_softc *rs = &ct_softc[unit];
E 4
I 4
	register int ctlr = io->i_adapt;
	register int unit = io->i_ctlr;
	register struct ct_softc *rs = &ct_softc[ctlr][unit];
E 4
	char stat;
I 5

	if (io->i_cc == 0 && (func == F_READ || func == F_WRITE))
		return(0);
E 5

	rs->sc_retry = 0;
	ct_ioc.unit = C_SUNIT(rs->sc_punit);
	ct_ioc.saddr = C_SADDR;
	ct_ioc.nop2 = C_NOP;
	ct_ioc.slen = C_SLEN;
	ct_ioc.nop3 = C_NOP;
top:
D 3
	if (func == READ) {
E 3
I 3
	if (func == F_READ) {
E 3
		ct_ioc.cmd = C_READ;
		ct_ioc.addr = rs->sc_blkno;
		ct_ioc.len = io->i_cc;
	}
D 3
	else if (func == WRITE) {
E 3
I 3
	else if (func == F_WRITE) {
E 3
		ct_ioc.cmd = C_WRITE;
		ct_ioc.addr = rs->sc_blkno;
		ct_ioc.len = io->i_cc;
	}
	else if (func == MTFSF) {
		ct_ioc.cmd = C_READ;
		ct_ioc.addr = rs->sc_blkno;
		ct_ioc.len = io->i_cc = MAXBSIZE;
		io->i_ma = io->i_buf;
	}
	else {
		ct_ioc.cmd = C_READ;
		ct_ioc.addr = 0;
		ct_ioc.len = 0;
		rs->sc_blkno = 0;
		io->i_cc = 0;
	}
retry:
D 4
	hpibsend(unit, C_CMD, &ct_ioc, sizeof(ct_ioc));
E 4
I 4
	hpibsend(ctlr, unit, C_CMD, &ct_ioc, sizeof(ct_ioc));
E 4
	if (func != MTREW) {
D 4
		hpibswait(unit);
		hpibgo(unit, C_EXEC, io->i_ma, io->i_cc,
E 4
I 4
		hpibswait(ctlr, unit);
		hpibgo(ctlr, unit, C_EXEC, io->i_ma, io->i_cc,
E 4
D 3
			func != WRITE ? READ : WRITE);
E 3
I 3
			func != F_WRITE ? F_READ : F_WRITE);
E 3
D 4
		hpibswait(unit);
	}
	else {
		while (hpibswait(unit) < 0)
E 4
I 4
		hpibswait(ctlr, unit);
	} else {
		while (hpibswait(ctlr, unit) < 0)
E 4
			;
	}
D 4
	hpibrecv(unit, C_QSTAT, &stat, 1);
E 4
I 4
	hpibrecv(ctlr, unit, C_QSTAT, &stat, 1);
E 4
	if (stat) {
D 4
		stat = cterror(unit);
E 4
I 4
		stat = cterror(ctlr, unit);
E 4
		if (stat == 0)
			return (-1);
		if (stat == 2)
			return (0);
		if (++rs->sc_retry > CTRETRY)
			return (-1);
D 4
		else
			goto retry;
E 4
I 4
		goto retry;
E 4
	}
	rs->sc_blkno += CTBTOK(io->i_cc);
	if (func == MTFSF)
		goto top;
	return (io->i_cc);
}

D 4
cterror(unit)
	register int unit;
E 4
I 4
cterror(ctlr, unit)
	register int ctlr, unit;
E 4
{
D 4
	register struct ct_softc *ct = &ct_softc[unit];
E 4
I 4
	register struct ct_softc *rs = &ct_softc[ctlr][unit];
E 4
	char stat;

D 4
	ct_rsc.unit = C_SUNIT(ct->sc_punit);
E 4
I 4
	ct_rsc.unit = C_SUNIT(rs->sc_punit);
E 4
	ct_rsc.cmd = C_STATUS;
D 4
	hpibsend(unit, C_CMD, &ct_rsc, sizeof(ct_rsc));
	hpibrecv(unit, C_EXEC, &ct_stat, sizeof(ct_stat));
	hpibrecv(unit, C_QSTAT, &stat, 1);
E 4
I 4
	hpibsend(ctlr, unit, C_CMD, &ct_rsc, sizeof(ct_rsc));
	hpibrecv(ctlr, unit, C_EXEC, &ct_stat, sizeof(ct_stat));
	hpibrecv(ctlr, unit, C_QSTAT, &stat, 1);
E 4
	if (stat) {
		printf("ct%d: request status fail %d\n", unit, stat);
		return(0);
	}
	if (ct_stat.c_aef & AEF_EOF) {
		/* 9145 drives don't increment block number at EOF */
D 4
		if ((ct_stat.c_blk - ct->sc_blkno) == 0)
			ct->sc_blkno++;
E 4
I 4
		if ((ct_stat.c_blk - rs->sc_blkno) == 0)
			rs->sc_blkno++;
E 4
		else
D 4
			ct->sc_blkno = ct_stat.c_blk;
E 4
I 4
			rs->sc_blkno = ct_stat.c_blk;
E 4
		return (2);
	}
	printf("ct%d err: vu 0x%x, pend 0x%x, bn%d", unit,
		ct_stat.c_vu, ct_stat.c_pend, ct_stat.c_blk);
	printf(", R 0x%x F 0x%x A 0x%x I 0x%x\n", ct_stat.c_ref,
		ct_stat.c_fef, ct_stat.c_aef, ct_stat.c_ief);
	return (1);
}
E 1
