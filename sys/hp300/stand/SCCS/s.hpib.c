h48961
s 00002/00002/00124
d D 8.1 93/06/10 21:46:53 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00125
d D 7.8 93/05/24 22:50:06 mckusick 8 7
c fix include directives
e
s 00006/00006/00120
d D 7.7 92/10/11 10:01:39 bostic 7 6
c make kernel includes standard
e
s 00029/00059/00097
d D 7.6 92/06/18 21:33:23 hibler 6 5
c merge with latest Utah version
e
s 00004/00004/00152
d D 7.5 91/05/07 10:05:49 hibler 5 4
c DIO-II support
e
s 00004/00003/00152
d D 7.4 91/05/05 13:31:56 bostic 4 3
c includes for standard stand source, READ, WRITE -> F_READ, FWRITE
e
s 00002/00002/00153
d D 7.3 90/12/16 16:39:20 bostic 3 2
c kernel reorg
e
s 00001/00001/00154
d D 7.2 90/06/24 14:58:24 karels 2 1
c update includes
e
s 00155/00000/00000
d D 7.1 90/05/08 22:46:04 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 9
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * HPIB driver
 */
D 2
#include "../h/reboot.h"
E 2
I 2
D 3
#include "reboot.h"
E 2
#include "../hpdev/device.h"
E 3
I 3
D 4
#include "sys/reboot.h"
E 4
I 4
D 6
#include <sys/param.h>
#include <sys/reboot.h>
E 4
#include "../dev/device.h"
E 6
I 6
D 7
#include "sys/param.h"
#include "sys/reboot.h"
#include "hp/dev/device.h"
E 6
E 3
#include "hpibvar.h"
E 7
I 7
#include <sys/param.h>
#include <sys/reboot.h>
#include <hp/dev/device.h>
#include <hp300/stand/hpibvar.h>
E 7

D 7
#include "saio.h"
#include "samachdep.h"
E 7
I 7
D 8
#include <stand/saio.h>
E 8
I 8
#include <stand.att/saio.h>
E 8
#include <hp300/stand/samachdep.h>
E 7

D 5
int	internalhpib = 0x478000;
E 5
I 5
int	internalhpib = IIOV(0x478000);
E 5
int	fhpibppoll(), nhpibppoll();

struct	hpib_softc hpib_softc[NHPIB];

D 6
#define	hpibunit(x)	((x) >> 3)
#define	hpibslave(x)	((x) & 7)

E 6
hpibinit()
{
	extern struct hp_hw sc_table[];
	register struct hp_hw *hw;
	register struct hpib_softc *hs;
	register int i, addr;
D 6
	static int first = 1;
	
E 6
I 6

E 6
	i = 0;
D 5
	for (hw = sc_table; i < NHPIB && hw < &sc_table[MAX_CTLR]; hw++) {
		if (hw->hw_type != HPIB)
E 5
I 5
	for (hw = sc_table; i < NHPIB && hw < &sc_table[MAXCTLRS]; hw++) {
		if (!HW_ISHPIB(hw))
E 5
			continue;
		hs = &hpib_softc[i];
D 5
		hs->sc_addr = hw->hw_addr;
E 5
I 5
		hs->sc_addr = hw->hw_kva;
E 5
		if (nhpibinit(i) == 0)
			if (fhpibinit(i) == 0)
				continue;
		if (howto & RB_ASKNAME)
			printf("hpib%d at sc%d\n", i, hw->hw_sc);
D 6
		/*
		 * Adjust devtype on first call.  This routine assumes that
		 * adaptor is in the high byte of devtype.
		 */
		if (first && ((devtype >> 24) & 0xff) == hw->hw_sc) {
			devtype = (devtype & 0x00ffffff) | (i << 24);
			first = 0;
		}
E 6
I 6
		hw->hw_pa = (caddr_t) i;	/* XXX for autoconfig */
E 6
		hs->sc_alive = 1;
		i++;
	}
}

hpibalive(unit)
	register int unit;
{
D 6
	unit = hpibunit(unit);
E 6
	if (unit >= NHPIB || hpib_softc[unit].sc_alive == 0)
		return (0);
	return (1);
}

D 6
hpibid(unit)
	register int unit;
E 6
I 6
hpibid(unit, slave)
	int unit, slave;
E 6
{
D 6
	register struct hpib_softc *hs = &hpib_softc[hpibunit(unit)];
	register int slave;
E 6
	short id;
I 6
	int rv;
E 6

D 6
	slave = hpibslave(unit);
	unit = hpibunit(unit);
	if (hs->sc_type == HPIBC)
		slave = fhpibrecv(unit, 31, slave, &id, 2);
E 6
I 6
	if (hpib_softc[unit].sc_type == HPIBC)
		rv = fhpibrecv(unit, 31, slave, &id, 2);
E 6
	else
D 6
		slave = nhpibrecv(unit, 31, slave, &id, 2);
	if (slave != 2)
E 6
I 6
		rv = nhpibrecv(unit, 31, slave, &id, 2);
	if (rv != 2)
E 6
		return (0);
	return (id);
}

D 6
hpibsend(unit, sec, buf, cnt)
	register char *buf;
	register int cnt;
E 6
I 6
hpibsend(unit, slave, sec, buf, cnt)
	int unit, slave;
	char *buf;
	int cnt;
E 6
{
D 6
	register struct hpib_softc *hs = &hpib_softc[hpibunit(unit)];
	register int slave;

	slave = hpibslave(unit);
	unit = hpibunit(unit);
	if (hs->sc_type == HPIBC)
E 6
I 6
	if (hpib_softc[unit].sc_type == HPIBC)
E 6
		return (fhpibsend(unit, slave, sec, buf, cnt));
D 6
	else
		return (nhpibsend(unit, slave, sec, buf, cnt));
E 6
I 6
	return (nhpibsend(unit, slave, sec, buf, cnt));
E 6
}

D 6
hpibrecv(unit, sec, buf, cnt)
	register char *buf;
	register int cnt;
E 6
I 6
hpibrecv(unit, slave, sec, buf, cnt)
	int unit, slave;
	char *buf;
	int cnt;
E 6
{
D 6
	register struct hpib_softc *hs = &hpib_softc[hpibunit(unit)];
	register int slave;

	slave = hpibslave(unit);
	unit = hpibunit(unit);
	if (hs->sc_type == HPIBC)
E 6
I 6
	if (hpib_softc[unit].sc_type == HPIBC)
E 6
		return (fhpibrecv(unit, slave, sec, buf, cnt));
D 6
	else
		return (nhpibrecv(unit, slave, sec, buf, cnt));
E 6
I 6
	return (nhpibrecv(unit, slave, sec, buf, cnt));
E 6
}

D 6
hpibswait(unit)
	register int unit;
E 6
I 6
hpibswait(unit, slave)
	register int unit, slave;
E 6
{
	register int timo = 1000000;
D 6
	register int slave = 0x80 >> hpibslave(unit);
E 6
	register int (*poll)();

D 6
	unit = hpibunit(unit);
E 6
I 6
	slave = 0x80 >> slave;
E 6
	if (hpib_softc[unit].sc_type == HPIBC)
		poll = fhpibppoll;
	else
		poll = nhpibppoll;
	while (((*poll)(unit) & slave) == 0)
		if (--timo == 0)
			break;
	if (timo == 0)
		return (-1);
	return (0);
}

D 6
hpibgo(unit, sec, addr, count, flag)
	register int unit;
E 6
I 6
hpibgo(unit, slave, sec, addr, count, flag)
	int unit, slave;
E 6
	char *addr;
{
D 6
	register int slave;

	slave = hpibslave(unit);
	unit = hpibunit(unit);
E 6
	if (hpib_softc[unit].sc_type == HPIBC)
D 4
		if (flag == READ)
E 4
I 4
		if (flag == F_READ)
E 4
			fhpibrecv(unit, slave, sec, addr, count);
		else
			fhpibsend(unit, slave, sec, addr, count);
	else
D 4
		if (flag == READ)
E 4
I 4
		if (flag == F_READ)
E 4
			nhpibrecv(unit, slave, sec, addr, count);
		else
			nhpibsend(unit, slave, sec, addr, count);
}
E 1
