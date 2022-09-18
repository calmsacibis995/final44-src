h14408
s 00001/00001/00386
d D 8.2 95/01/09 18:28:58 cgd 10 9
c ioctl cmd arg is u_long, strategy returns void.
e
s 00002/00002/00385
d D 8.1 93/06/16 17:47:58 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00006/00377
d D 7.7 93/06/16 17:47:43 mckusick 8 6
c lint
e
s 00002/00002/00381
d R 8.1 93/06/10 21:33:49 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00007/00376
d D 7.6 92/10/11 09:24:05 bostic 6 5
c make kernel includes standard
e
s 00003/00002/00380
d D 7.5 92/07/12 17:43:39 pendry 5 4
c MIN -> min
e
s 00001/00001/00381
d D 7.4 92/06/05 15:31:02 hibler 4 3
c merge latest Utah hp300 code including 68040 support
e
s 00004/00004/00378
d D 7.3 90/12/16 16:36:49 bostic 3 2
c kernel reorg
e
s 00254/00026/00128
d D 7.2 90/11/04 19:38:28 mckusick 2 1
c update from Mike Hibler
e
s 00154/00000/00000
d D 7.1 90/05/08 22:07:05 mckusick 1 0
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
 * Printer/Plotter HPIB interface
 */

#include "ppi.h"
#if NPPI > 0

D 3
#include "param.h"
#include "errno.h"
#include "uio.h"
#include "malloc.h"
E 3
I 3
D 6
#include "sys/param.h"
I 5
#include "sys/systm.h"
E 5
#include "sys/errno.h"
#include "sys/uio.h"
#include "sys/malloc.h"
E 6
I 6
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/errno.h>
#include <sys/uio.h>
#include <sys/malloc.h>
E 6
E 3

D 4
#include "device.h"
E 4
I 4
D 6
#include "hp/dev/device.h"
E 4
I 2
#include "ppiioctl.h"
E 6
I 6
#include <hp/dev/device.h>
#include <hp300/dev/ppiioctl.h>
E 6
E 2

D 2
int	ppiattach(), ppistart();
E 2
I 2
D 8
int	ppiattach(), ppistart(), ppitimo();
E 8
I 8
int	ppiattach(), ppistart();
void	ppitimo();
E 8
E 2
struct	driver ppidriver = {
	ppiattach, "ppi", ppistart,
};

struct	ppi_softc {
	int	sc_flags;
	struct	devqueue sc_dq;
	struct	hp_device *sc_hd;
I 2
	struct	ppiparam sc_param;
#define sc_burst sc_param.burst
#define sc_timo  sc_param.timo
#define sc_delay sc_param.delay
	int	sc_sec;
E 2
} ppi_softc[NPPI];

/* sc_flags values */
D 2
#define	PPIF_ALIVE	0x1	
#define	PPIF_OPEN	0x2	
E 2
I 2
#define	PPIF_ALIVE	0x01	
#define	PPIF_OPEN	0x02	
#define PPIF_UIO	0x04
#define PPIF_TIMO	0x08
#define PPIF_DELAY	0x10
E 2

#define UNIT(x)		minor(x)

I 2
#ifdef DEBUG
int	ppidebug = 0x80;
#define PDB_FOLLOW	0x01
#define PDB_IO		0x02
#define PDB_NOCHECK	0x80
#endif

E 2
ppiattach(hd)
	register struct hp_device *hd;
{
	register struct ppi_softc *sc = &ppi_softc[hd->hp_unit];

I 2
#ifdef DEBUG
	if ((ppidebug & PDB_NOCHECK) == 0)
#endif
E 2
	/*
	 * XXX: the printer/plotter doesn't seem to really return
	 * an ID but this will at least prevent us from mistaking
	 * a cs80 disk or tape for a ppi device.
	 */
	if (hpibid(hd->hp_ctlr, hd->hp_slave) & 0x200)
		return(0);
	sc->sc_flags = PPIF_ALIVE;
	sc->sc_dq.dq_ctlr = hd->hp_ctlr;
	sc->sc_dq.dq_unit = hd->hp_unit;
	sc->sc_dq.dq_slave = hd->hp_slave;
	sc->sc_dq.dq_driver = &ppidriver;
	sc->sc_hd = hd;
	return(1);
}

ppiopen(dev, flags)
	dev_t dev;
{
	register int unit = UNIT(dev);
	register struct ppi_softc *sc = &ppi_softc[unit];

	if (unit >= NPPI || (sc->sc_flags & PPIF_ALIVE) == 0)
		return(ENXIO);
I 2
#ifdef DEBUG
	if (ppidebug & PDB_FOLLOW)
		printf("ppiopen(%x, %x): flags %x\n",
		       dev, flags, sc->sc_flags);
#endif
E 2
	if (sc->sc_flags & PPIF_OPEN)
		return(EBUSY);
	sc->sc_flags |= PPIF_OPEN;
I 2
	sc->sc_burst = PPI_BURST;
	sc->sc_timo = ppimstohz(PPI_TIMO);
	sc->sc_delay = ppimstohz(PPI_DELAY);
	sc->sc_sec = -1;
E 2
	return(0);
}

ppiclose(dev, flags)
	dev_t dev;
{
	register int unit = UNIT(dev);
	register struct ppi_softc *sc = &ppi_softc[unit];

I 2
#ifdef DEBUG
	if (ppidebug & PDB_FOLLOW)
		printf("ppiclose(%x, %x): flags %x\n",
		       dev, flags, sc->sc_flags);
#endif
E 2
	sc->sc_flags &= ~PPIF_OPEN;
	return(0);
}

ppistart(unit)
D 2
	register int unit;
E 2
I 2
	int unit;
E 2
{
I 2
#ifdef DEBUG
	if (ppidebug & PDB_FOLLOW)
		printf("ppistart(%x)\n", unit);
#endif
	ppi_softc[unit].sc_flags &= ~PPIF_DELAY;
E 2
	wakeup(&ppi_softc[unit]);
I 8
	return (0);
E 8
}

I 8
void
E 8
I 2
ppitimo(unit)
	int unit;
{
#ifdef DEBUG
	if (ppidebug & PDB_FOLLOW)
		printf("ppitimo(%x)\n", unit);
#endif
	ppi_softc[unit].sc_flags &= ~(PPIF_UIO|PPIF_TIMO);
	wakeup(&ppi_softc[unit]);
}

E 2
ppiread(dev, uio)
	dev_t dev;
	struct uio *uio;
{

D 2
	return (ppirw(dev, uio, UIO_READ));
E 2
I 2
#ifdef DEBUG
	if (ppidebug & PDB_FOLLOW)
		printf("ppiread(%x, %x)\n", dev, uio);
#endif
	return (ppirw(dev, uio));
E 2
}

ppiwrite(dev, uio)
	dev_t dev;
	struct uio *uio;
{

D 2
	return (ppirw(dev, uio, UIO_WRITE));
E 2
I 2
#ifdef DEBUG
	if (ppidebug & PDB_FOLLOW)
		printf("ppiwrite(%x, %x)\n", dev, uio);
#endif
	return (ppirw(dev, uio));
E 2
}

D 2
ppirw(dev, uio, rw)
E 2
I 2
ppirw(dev, uio)
E 2
	dev_t dev;
	register struct uio *uio;
D 2
	enum uio_rw rw;
E 2
{
D 2
	register struct ppi_softc *sc = &ppi_softc[UNIT(dev)];
E 2
I 2
	int unit = UNIT(dev);
	register struct ppi_softc *sc = &ppi_softc[unit];
E 2
	register int s, len, cnt;
	register char *cp;
D 2
	int error = 0;
E 2
I 2
	int error = 0, gotdata = 0;
	int buflen;
	char *buf;
E 2

D 2
	len = MIN(CLBYTES, uio->uio_resid);
	cp = (char *)malloc(len, M_TEMP, M_WAITOK);
E 2
I 2
	if (uio->uio_resid == 0)
		return(0);

#ifdef DEBUG
	if (ppidebug & (PDB_FOLLOW|PDB_IO))
		printf("ppirw(%x, %x, %c): burst %d, timo %d, resid %x\n",
		       dev, uio, uio->uio_rw == UIO_READ ? 'R' : 'W',
		       sc->sc_burst, sc->sc_timo, uio->uio_resid);
#endif
D 5
	buflen = MIN(sc->sc_burst, uio->uio_resid);
E 5
I 5
	buflen = min(sc->sc_burst, uio->uio_resid);
E 5
	buf = (char *)malloc(buflen, M_DEVBUF, M_WAITOK);
	sc->sc_flags |= PPIF_UIO;
	if (sc->sc_timo > 0) {
		sc->sc_flags |= PPIF_TIMO;
D 8
		timeout(ppitimo, unit, sc->sc_timo);
E 8
I 8
		timeout(ppitimo, (void *)unit, sc->sc_timo);
E 8
	}
E 2
	while (uio->uio_resid > 0) {
D 2
		len = MIN(CLBYTES, uio->uio_resid);
		if (rw == UIO_WRITE) {
E 2
I 2
D 5
		len = MIN(buflen, uio->uio_resid);
E 5
I 5
		len = min(buflen, uio->uio_resid);
E 5
		cp = buf;
		if (uio->uio_rw == UIO_WRITE) {
E 2
			error = uiomove(cp, len, uio);
			if (error)
				break;
		}
I 2
again:
E 2
		s = splbio();
D 2
		if (hpibreq(&sc->sc_dq) == 0)
			sleep(sc, PRIBIO + 1);
E 2
I 2
		if ((sc->sc_flags & PPIF_UIO) && hpibreq(&sc->sc_dq) == 0)
			sleep(sc, PRIBIO+1);
		/*
		 * Check if we timed out during sleep or uiomove
		 */
		(void) splsoftclock();
		if ((sc->sc_flags & PPIF_UIO) == 0) {
#ifdef DEBUG
			if (ppidebug & PDB_IO)
				printf("ppirw: uiomove/sleep timo, flags %x\n",
				       sc->sc_flags);
#endif
			if (sc->sc_flags & PPIF_TIMO) {
D 8
				untimeout(ppitimo, unit);
E 8
I 8
				untimeout(ppitimo, (void *)unit);
E 8
				sc->sc_flags &= ~PPIF_TIMO;
			}
			splx(s);
			break;
		}
E 2
		splx(s);
D 2
		if (rw == UIO_WRITE)
E 2
I 2
		/*
		 * Perform the operation
		 */
		if (uio->uio_rw == UIO_WRITE)
E 2
			cnt = hpibsend(sc->sc_hd->hp_ctlr, sc->sc_hd->hp_slave,
D 2
				-1, cp, len);
E 2
I 2
				       sc->sc_sec, cp, len);
E 2
		else
			cnt = hpibrecv(sc->sc_hd->hp_ctlr, sc->sc_hd->hp_slave,
D 2
				-1, cp, len);
E 2
I 2
				       sc->sc_sec, cp, len);
E 2
		s = splbio();
		hpibfree(&sc->sc_dq);
I 2
#ifdef DEBUG
		if (ppidebug & PDB_IO)
			printf("ppirw: %s(%d, %d, %x, %x, %d) -> %d\n",
			       uio->uio_rw == UIO_READ ? "recv" : "send",
			       sc->sc_hd->hp_ctlr, sc->sc_hd->hp_slave,
			       sc->sc_sec, cp, len, cnt);
#endif
E 2
		splx(s);
D 2
		if (rw == UIO_READ) {
			error = uiomove(cp, cnt, uio);
			if (error)
E 2
I 2
		if (uio->uio_rw == UIO_READ) {
			if (cnt) {
				error = uiomove(cp, cnt, uio);
				if (error)
					break;
				gotdata++;
			}
			/*
			 * Didn't get anything this time, but did in the past.
			 * Consider us done.
			 */
			else if (gotdata)
E 2
				break;
		}
D 2
		if (cnt != len) {
			if (rw == UIO_WRITE)
				uio->uio_resid += len - cnt;
E 2
I 2
		s = splsoftclock();
		/*
		 * Operation timeout (or non-blocking), quit now.
		 */
		if ((sc->sc_flags & PPIF_UIO) == 0) {
#ifdef DEBUG
			if (ppidebug & PDB_IO)
				printf("ppirw: timeout/done\n");
#endif
			splx(s);
E 2
			break;
		}
I 2
		/*
		 * Implement inter-read delay
		 */
		if (sc->sc_delay > 0) {
			sc->sc_flags |= PPIF_DELAY;
D 8
			timeout(ppistart, unit, sc->sc_delay);
E 8
I 8
			timeout((void (*)__P((void *)))ppistart, (void *)unit,
			    sc->sc_delay);
E 8
			error = tsleep(sc, PCATCH|PZERO+1, "hpib", 0);
			if (error) {
				splx(s);
				break;
			}
		}
		splx(s);
		/*
		 * Must not call uiomove again til we've used all data
		 * that we already grabbed.
		 */
		if (uio->uio_rw == UIO_WRITE && cnt != len) {
			cp += cnt;
			len -= cnt;
			cnt = 0;
			goto again;
		}
E 2
	}
D 2
	free(cp, M_TEMP);
E 2
I 2
	s = splsoftclock();
	if (sc->sc_flags & PPIF_TIMO) {
D 8
		untimeout(ppitimo, unit);
E 8
I 8
		untimeout(ppitimo, (void *)unit);
E 8
		sc->sc_flags &= ~PPIF_TIMO;
	}
	if (sc->sc_flags & PPIF_DELAY) {
D 8
		untimeout(ppistart, unit);
E 8
I 8
		untimeout((void (*)__P((void *)))ppistart, (void *)unit);
E 8
		sc->sc_flags &= ~PPIF_DELAY;
	}
	splx(s);
	/*
	 * Adjust for those chars that we uiomove'ed but never wrote
	 */
	if (uio->uio_rw == UIO_WRITE && cnt != len) {
		uio->uio_resid += (len - cnt);
#ifdef DEBUG
		if (ppidebug & PDB_IO)
			printf("ppirw: short write, adjust by %d\n",
			       len-cnt);
#endif
	}
	free(buf, M_DEVBUF);
#ifdef DEBUG
	if (ppidebug & (PDB_FOLLOW|PDB_IO))
		printf("ppirw: return %d, resid %d\n", error, uio->uio_resid);
#endif
E 2
	return (error);
I 2
}

ppiioctl(dev, cmd, data, flag)
	dev_t dev;
D 10
	int cmd;
E 10
I 10
	u_long cmd;
E 10
	caddr_t data;
	int flag;
{
	struct ppi_softc *sc = &ppi_softc[UNIT(dev)];
	struct ppiparam *pp, *upp;
	int error = 0;

	switch (cmd) {
	case PPIIOCGPARAM:
		pp = &sc->sc_param;
		upp = (struct ppiparam *)data;
		upp->burst = pp->burst;
		upp->timo = ppihztoms(pp->timo);
		upp->delay = ppihztoms(pp->delay);
		break;
	case PPIIOCSPARAM:
		pp = &sc->sc_param;
		upp = (struct ppiparam *)data;
		if (upp->burst < PPI_BURST_MIN || upp->burst > PPI_BURST_MAX ||
		    upp->delay < PPI_DELAY_MIN || upp->delay > PPI_DELAY_MAX)
			return(EINVAL);
		pp->burst = upp->burst;
		pp->timo = ppimstohz(upp->timo);
		pp->delay = ppimstohz(upp->delay);
		break;
	case PPIIOCSSEC:
		sc->sc_sec = *(int *)data;
		break;
	default:
		return(EINVAL);
	}
	return (error);
}

ppihztoms(h)
	int h;
{
	extern int hz;
	register int m = h;

	if (m > 0)
		m = m * 1000 / hz;
	return(m);
}

ppimstohz(m)
	int m;
{
	extern int hz;
	register int h = m;

	if (h > 0) {
		h = h * hz / 1000;
		if (h == 0)
			h = 1000 / hz;
	}
	return(h);
E 2
}
#endif
E 1
