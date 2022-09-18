h21495
s 00001/00001/01283
d D 8.4 95/01/09 17:54:16 cgd 23 22
c 64-bit changes: casts, and ioctl cmds are u_longs
e
s 00002/00008/01282
d D 8.3 94/08/10 22:24:03 mckusick 22 21
c inline => __inline (from cgd)
e
s 00008/00008/01282
d D 8.2 94/03/28 08:06:34 bostic 21 20
c fix compiler warning
c From: ralphc@pyramid.com (Ralph Campbell)
e
s 00002/00002/01288
d D 8.1 93/06/10 22:39:37 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00025/00013/01265
d D 7.15 93/06/04 17:30:32 bostic 19 18
c prototype everything
e
s 00013/00000/01265
d D 7.14 93/04/17 18:54:45 torek 18 17
c add bpfilterattach
e
s 00000/00001/01265
d D 7.13 93/02/10 20:38:43 bostic 17 16
c bpf doesn't need sys/dir.h
e
s 00008/00005/01258
d D 7.12 92/07/16 12:44:31 mckusick 16 15
c update from Jeff Forys for rbootd support
e
s 00002/00002/01261
d D 7.11 92/07/12 17:40:34 pendry 15 14
c MIN -> min
e
s 00001/00001/01262
d D 7.10 92/07/11 19:19:59 mckusick 14 13
c change definition of __inline__ to match __inline of cdefs.h
e
s 00186/00129/01077
d D 7.9 92/06/07 19:29:59 mccanne 13 12
c update from helios -- many changes and bug fixes
e
s 00002/00010/01204
d D 7.8 92/02/15 18:05:16 mckusick 12 11
c use selrecord and selwakeup to implement selecting
e
s 00004/00030/01210
d D 7.7 91/10/29 19:56:02 mccanne 11 10
c restore sccs keywords
e
s 00219/00056/01021
d D 7.6 91/10/27 21:28:30 mccanne 10 9
c new SunOS/BSD unified source
e
s 00002/00004/01075
d D 7.5 91/07/15 11:11:31 mccanne 9 8
c fixed memory leak in bpf_setf()
e
s 00003/00007/01076
d D 7.4 91/06/17 16:03:25 mccanne 8 7
c bug fix -- large snapshots with large packets previously could 
c overflow the input buffer
e
s 00003/00001/01080
d D 7.3 91/05/14 22:56:11 mccanne 7 6
c be paranoid and pass ifr arg to device driver SIOCSIFFLAGS ioctl
e
s 00003/00019/01078
d D 7.2 91/05/14 16:13:57 mccanne 6 5
c fixed bpfselect() bugs -- had semantics wrong
c don't special case absent filter anymore
e
s 00011/00054/01086
d D 7.1 91/05/07 12:19:16 bostic 5 4
c from Steve McCanne, delete dead code
c new copyright; att/bsd/shared
e
s 00059/00063/01081
d D 1.4 91/05/05 23:01:48 mccanne 4 3
c bpf interfaces now allocated dynamically; perhaps they should go
c in the driver's softc
c bpf_devp is gone; instead we have an ioctl to get the link type
c bpf_mtap now just passes mbuf to filter -- no pull up
c 
e
s 00015/00017/01129
d D 1.3 91/05/02 21:26:22 mccanne 3 2
c nuked bpf_default_filter; no filter is now NULL
e
s 00204/00282/00942
d D 1.2 91/05/02 11:05:21 mccanne 2 1
c checkpoint before porting new insn format from horse
e
s 01224/00000/00000
d D 1.1 91/03/19 18:27:13 mccanne 1 0
c date and time created 91/03/19 18:27:13 by mccanne
e
u
U
t
T
I 1
D 5
/*
 * Copyright (c) 1990 The Regents of the University of California.
E 5
I 5
D 11
/*-
D 10
 * Copyright (c) 1991 The Regents of the University of California.
E 10
I 10
 * Copyright (c) 1990-1991 The Regents of the University of California.
E 11
I 11
/*
D 20
 * Copyright (c) 1990, 1991 Regents of the University of California.
E 11
E 10
E 5
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1990, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
D 5
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that: (1) source code distributions
 * retain the above copyright notice and this paragraph in its entirety, (2)
 * distributions including binary code include the above copyright notice and
 * this paragraph in its entirety in the documentation or other materials
 * provided with the distribution, and (3) all advertising materials mentioning
 * features or use of this software display the following acknowledgement:
 * ``This product includes software developed by the University of California,
 * Lawrence Berkeley Laboratory and its contributors.'' Neither the name of
 * the University nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior
 * written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
E 5
 * This code is derived from the Stanford/CMU enet packet filter,
D 5
 * (net/enet.c) distributed in 4.3BSD Unix.
E 5
I 5
 * (net/enet.c) distributed as part of 4.3BSD, and code contributed
D 10
 * to Berkeley by Steven McCanne of Lawrence Berkeley Laboratory.
E 10
I 10
 * to Berkeley by Steven McCanne and Van Jacobson both of Lawrence 
 * Berkeley Laboratory.
E 10
 *
D 10
 * %sccs.include.redist.c%
E 10
I 10
D 11
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
E 11
I 11
 * %sccs.include.redist.c%
E 11
E 10
 *
D 10
 *	%W% (Berkeley) %G%
E 10
I 10
D 11
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
E 10
 *
I 10
 *	@(#)bpf.c	7.5 (Berkeley) 7/15/91
E 11
I 11
 *      %W% (Berkeley) %G%
E 11
 *
E 10
 * static char rcsid[] =
D 10
 * "$Header: bpf.c,v 1.23 91/01/30 18:22:13 mccanne Exp $";
E 10
I 10
 * "$Header: bpf.c,v 1.33 91/10/27 21:21:58 mccanne Exp $";
E 10
E 5
 */
D 5
#ifndef lint
static char rcsid[] =
    "$Header: bpf.c,v 1.23 91/01/30 18:22:13 mccanne Exp $";
#endif
E 5

#include "bpfilter.h"

D 10
#if (NBPFILTER > 0)
E 10
I 10
#if NBPFILTER > 0
E 10

I 10
D 22
#ifndef __GNUC__
#define inline
#else
D 14
#define inline __inline__
E 14
I 14
#define inline __inline
E 14
#endif

E 22
E 10
D 5
#ifndef __GNUC__
#define inline
#endif

E 5
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/buf.h>
D 17
#include <sys/dir.h>
E 17
I 13
#include <sys/time.h>
E 13
I 2
#include <sys/proc.h>
E 2
#include <sys/user.h>
#include <sys/ioctl.h>
#include <sys/map.h>
D 2
#include <sys/proc.h>
E 2

#include <sys/file.h>
D 10
#ifdef sparc
E 10
I 10
#if defined(sparc) && BSD < 199103
E 10
#include <sys/stream.h>
#endif
#include <sys/tty.h>
#include <sys/uio.h>

#include <sys/protosw.h>
#include <sys/socket.h>
#include <net/if.h>

#include <net/bpf.h>
#include <net/bpfdesc.h>

#include <sys/errno.h>

#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <sys/kernel.h>

I 10
/*
 * Older BSDs don't have kernel malloc.
 */
#if BSD < 199103
extern bcopy();
static caddr_t bpf_alloc();
D 13
#define malloc(size, type, canwait) bpf_alloc(size, canwait)
#define free(cp, type) m_free(*(struct mbuf **)(cp - 8))
#define M_WAITOK M_WAIT
E 13
I 13
#include <net/bpf_compat.h>
E 13
#define BPF_BUFSIZE (MCLBYTES-8)
D 13
#define ERESTART EINTR
E 13
I 13
#define UIOMOVE(cp, len, code, uio) uiomove(cp, len, code, uio)
E 13
#else
#define BPF_BUFSIZE 4096
I 13
#define UIOMOVE(cp, len, code, uio) uiomove(cp, len, uio)
E 13
#endif

E 10
#define PRINET  26			/* interruptible */

/*
I 2
 * The default read buffer size is patchable.
 */
D 10
int bpf_bufsize = MCLBYTES;
E 10
I 10
int bpf_bufsize = BPF_BUFSIZE;
E 10

/*
E 2
D 4
 *  'bpf_iftab' is the driver state table per logical unit number
 *  'bpf_dtab' holds the descriptors, indexed by minor device #
 *  'bpf_units' is the number of attached units
E 4
I 4
 *  bpf_iflist is the list of interfaces; each corresponds to an ifnet
 *  bpf_dtab holds the descriptors, indexed by minor device #
E 4
D 13
 *
 * We really don't need NBPFILTER bpf_if entries, but this eliminates
 * the need to account for all possible drivers here.
 * This problem will go away when these structures are allocated dynamically.
E 13
 */
D 4
static struct bpf_if 	bpf_iftab[NBPFILTER];
E 4
I 4
D 13
static struct bpf_if 	*bpf_iflist;
E 4
static struct bpf_d	bpf_dtab[NBPFILTER];
E 13
I 13
struct bpf_if	*bpf_iflist;
struct bpf_d	bpf_dtab[NBPFILTER];
E 13
D 4
static u_int		bpf_units = 0;
E 4

I 18
#if BSD >= 199207
/*
 * bpfilterattach() is called at boot time in new systems.  We do
 * nothing here since old systems will not call this.
 */
/* ARGSUSED */
void
bpfilterattach(n)
	int n;
{
}
#endif

E 18
D 2
static int	bpf_timeout();
E 2
D 19
static void	bpf_ifname();
static void	catchpacket();
I 13
static void	bpf_freed();
E 13
static int	bpf_setif();
static int	bpf_initd();
I 13
static int	bpf_allocbufs();
E 19
I 19
static int	bpf_allocbufs __P((struct bpf_d *));
static int	bpf_allocbufs __P((struct bpf_d *));
static void	bpf_freed __P((struct bpf_d *));
static void	bpf_freed __P((struct bpf_d *));
static void	bpf_ifname __P((struct ifnet *, struct ifreq *));
static void	bpf_ifname __P((struct ifnet *, struct ifreq *));
D 21
static void	bpf_mcopy __P((void *, void *, u_int));
E 21
I 21
static void	bpf_mcopy __P((const void *, void *, u_int));
E 21
static int	bpf_movein __P((struct uio *, int,
		    struct mbuf **, struct sockaddr *, int *));
static int	bpf_setif __P((struct bpf_d *, struct ifreq *));
static int	bpf_setif __P((struct bpf_d *, struct ifreq *));
D 22
static inline void
E 22
I 22
static __inline void
E 22
		bpf_wakeup __P((struct bpf_d *));
static void	catchpacket __P((struct bpf_d *, u_char *, u_int,
D 21
		    u_int, void (*)(void *, void *, u_int)));
E 21
I 21
		    u_int, void (*)(const void *, void *, u_int)));
E 21
static void	reset_d __P((struct bpf_d *));
E 19
E 13

D 3
/*
 * The default filter accepts the maximum number of bytes from each packet.
 */
struct bpf_insn bpf_default_filter[] = {
D 2
	BPF_STMT(RetOp, MCLBYTES),
E 2
I 2
	BPF_STMT(RetOp, -1),
E 2
};

E 3
D 2
/*
 * This routine was inspired by/stolen from ../sys/uipc_socket.c
 * Move data from 'm' to user's read buffer.  
 * We assume 'm' is not chained.
 * Returns error code (or 0 if success).
 */
static inline int
bpf_moveout(m, uio)
	register struct mbuf *m;
	register struct uio *uio;
{
	register int len;
	
	len = m->m_len;
	if (uio->uio_resid < len)
		len = uio->uio_resid;

	if (len > 0)
		return uiomove(mtod(m, caddr_t), len, UIO_READ, uio);

	return 0;
}

E 2
static int
D 16
bpf_movein(uio, linktype, mp, sockp)
E 16
I 16
bpf_movein(uio, linktype, mp, sockp, datlen)
E 16
	register struct uio *uio;
D 16
	int linktype;
E 16
I 16
	int linktype, *datlen;
E 16
	register struct mbuf **mp;
	register struct sockaddr *sockp;
{
	struct mbuf *m;
	int error;
	int len;
	int hlen;

	/*
	 * Build a sockaddr based on the data link layer type.
	 * We do this at this level because the ethernet header
	 * is copied directly into the data field of the sockaddr.
	 * In the case of SLIP, there is no header and the packet
	 * is forwarded as is.
	 * Also, we are careful to leave room at the front of the mbuf
	 * for the link level header.
	 */
	switch (linktype) {
I 13

E 13
	case DLT_SLIP:
		sockp->sa_family = AF_INET;
		hlen = 0;
		break;

	case DLT_EN10MB:
		sockp->sa_family = AF_UNSPEC;
		/* XXX Would MAXLINKHDR be better? */
		hlen = sizeof(struct ether_header);
		break;

D 13
       case DLT_FDDI:
E 13
I 13
	case DLT_FDDI:
E 13
		sockp->sa_family = AF_UNSPEC;
		/* XXX 4(FORMAC)+6(dst)+6(src)+3(LLC)+5(SNAP) */
		hlen = 24;
		break;

I 13
	case DLT_NULL:
		sockp->sa_family = AF_UNSPEC;
		hlen = 0;
		break;

E 13
	default:
D 2
		return EIO;
E 2
I 2
		return (EIO);
E 2
	}

	len = uio->uio_resid;
I 16
	*datlen = len - hlen;
E 16
	if ((unsigned)len > MCLBYTES)
D 2
		return EIO;
E 2
I 2
		return (EIO);
E 2

	MGET(m, M_WAIT, MT_DATA);
	if (m == 0)
D 2
		return ENOBUFS;
E 2
I 2
		return (ENOBUFS);
E 2
	if (len > MLEN) {
I 10
#if BSD >= 199103
E 10
D 2
		MCLGET(m);
		if (m->m_len != MCLBYTES) {
E 2
I 2
		MCLGET(m, M_WAIT);
		if ((m->m_flags & M_EXT) == 0) {
E 2
D 10
			error = ENOBUFS;
E 10
I 10
#else
		MCLGET(m);
D 13
		if (m->m_len == MCLBYTES) {
E 13
I 13
		if (m->m_len != MCLBYTES) {
E 13
#endif
D 13
			error = ENOBUFS;		
E 13
I 13
			error = ENOBUFS;
E 13
E 10
			goto bad;
		}
	}
	m->m_len = len;
	*mp = m;
	/*
	 * Make room for link header.
	 */
D 13
	if (hlen) {
E 13
I 13
	if (hlen != 0) {
E 13
		m->m_len -= hlen;
I 10
#if BSD >= 199103
E 10
D 2
		m->m_off += hlen;
E 2
I 2
		m->m_data += hlen; /* XXX */
E 2
D 10

E 10
I 10
#else
		m->m_off += hlen;
#endif
E 10
D 2
		error = uiomove((caddr_t)sockp->sa_data, hlen, UIO_WRITE, uio);
E 2
I 2
D 13
		error = uiomove((caddr_t)sockp->sa_data, hlen, uio);
E 13
I 13
		error = UIOMOVE((caddr_t)sockp->sa_data, hlen, UIO_WRITE, uio);
E 13
E 2
		if (error)
			goto bad;
	}
D 2
	error = uiomove(mtod(m, caddr_t), len - hlen, UIO_WRITE, uio);
E 2
I 2
D 13
	error = uiomove(mtod(m, caddr_t), len - hlen, uio);
E 2
	if (!error) 
E 13
I 13
	error = UIOMOVE(mtod(m, caddr_t), len - hlen, UIO_WRITE, uio);
	if (!error)
E 13
D 2
		return 0;
E 2
I 2
		return (0);
E 2
 bad:
	m_freem(m);
D 2
	return error;
E 2
I 2
	return (error);
E 2
}

/*
D 10
 * Attach 'd' to the bpf interface 'bp', i.e. make 'd' listen on 'bp'.
E 10
I 10
 * Attach file to the bpf interface, i.e. make d listen on bp.
E 10
 * Must be called at splimp.
 */
static void
bpf_attachd(d, bp)
	struct bpf_d *d;
	struct bpf_if *bp;
{
D 2
	/* Point 'd' at 'bp'. */
E 2
I 2
D 10
	/* Point d at bp. */
E 10
I 10
	/*
	 * Point d at bp, and add d to the interface's list of listeners.
	 * Finally, point the driver's bpf cookie at the interface so
	 * it will divert packets to bpf.
	 */
E 10
E 2
	d->bd_bif = bp;
D 10

D 2
	/* Add 'd' to 'bp's list of listeners. */
E 2
I 2
	/* Add d to bp's list of listeners. */
E 10
E 2
	d->bd_next = bp->bif_dlist;
	bp->bif_dlist = d;

D 10
	/*
	 * Let the driver know we're here (if it doesn't already).
	 */
E 10
	*bp->bif_driverp = bp;
}

I 10
/*
 * Detach a file from its interface.
 */
E 10
static void
bpf_detachd(d)
	struct bpf_d *d;
{
	struct bpf_d **p;
	struct bpf_if *bp;

	bp = d->bd_bif;
	/*
	 * Check if this descriptor had requested promiscuous mode.
	 * If so, turn it off.
	 */
	if (d->bd_promisc) {
		d->bd_promisc = 0;
		if (ifpromisc(bp->bif_ifp, 0))
			/*
			 * Something is really wrong if we were able to put
			 * the driver into promiscuous mode, but can't
			 * take it out.
			 */
D 2
			panic("bpf_detachd: exit promisc unsucessful");
E 2
I 2
D 10
			panic("bpf_detachd: ifpromisc failed");
E 10
I 10
			panic("bpf: ifpromisc failed");
E 10
E 2
	}
D 10
	/* Remove 'd' from the interface's descriptor list. */
E 10
I 10
	/* Remove d from the interface's descriptor list. */
E 10
	p = &bp->bif_dlist;
	while (*p != d) {
		p = &(*p)->bd_next;
		if (*p == 0)
			panic("bpf_detachd: descriptor not in list");
	}
	*p = (*p)->bd_next;
	if (bp->bif_dlist == 0)
		/*
		 * Let the driver know that there are no more listeners.
		 */
		*d->bd_bif->bif_driverp = 0;
	d->bd_bif = 0;
}


/*
D 13
 * Mark a descriptor free by making it point to itself. 
E 13
I 13
 * Mark a descriptor free by making it point to itself.
E 13
 * This is probably cheaper than marking with a constant since
 * the address should be in a register anyway.
 */
#define D_ISFREE(d) ((d) == (d)->bd_next)
#define D_MARKFREE(d) ((d)->bd_next = (d))
#define D_MARKUSED(d) ((d)->bd_next = 0)

/*
D 13
 *  bpfopen - open ethernet device
 *
 *  Errors:	ENXIO	- illegal minor device number
 *		EBUSY	- too many files open
E 13
I 13
 * Open ethernet device.  Returns ENXIO for illegal minor device number,
 * EBUSY if file is open by another process.
E 13
 */
/* ARGSUSED */
int
bpfopen(dev, flag)
	dev_t dev;
	int flag;
{
D 13
	int error, s;
E 13
	register struct bpf_d *d;
D 13
	
E 13
I 13

E 13
	if (minor(dev) >= NBPFILTER)
D 2
		return ENXIO;
E 2
I 2
		return (ENXIO);
E 2
D 13

E 13
	/*
	 * Each minor can be opened by only one process.  If the requested
	 * minor is in use, return EBUSY.
	 */
D 13
	s = splimp();
E 13
	d = &bpf_dtab[minor(dev)];
D 13
	if (!D_ISFREE(d)) {
		splx(s);
E 13
I 13
	if (!D_ISFREE(d))
E 13
D 2
		return EBUSY;
E 2
I 2
		return (EBUSY);
E 2
D 13
	} else
		/* Mark "free" and do most initialization. */
		bzero((char *)d, sizeof(*d));
D 3
	d->bd_filter = bpf_default_filter;
E 3
	splx(s);
E 13

D 13
	error = bpf_initd(d);
	if (error) {
		D_MARKFREE(d);
D 2
		return error;
E 2
I 2
		return (error);
E 2
	}
E 13
I 13
	/* Mark "free" and do most initialization. */
	bzero((char *)d, sizeof(*d));
	d->bd_bufsize = bpf_bufsize;

E 13
D 2
	return 0;
E 2
I 2
	return (0);
E 2
}

/*
 * Close the descriptor by detaching it from its interface,
 * deallocating its buffers, and marking it free.
 */
/* ARGSUSED */
I 13
int
E 13
bpfclose(dev, flag)
	dev_t dev;
	int flag;
{
	register struct bpf_d *d = &bpf_dtab[minor(dev)];
D 13
	int s;
E 13
I 13
	register int s;
E 13

	s = splimp();
	if (d->bd_bif)
		bpf_detachd(d);
	splx(s);
D 13

E 13
D 2
	/* Let the buffers go. */
	m_freem(d->bd_hbuf);
	m_freem(d->bd_sbuf);
	m_freem(d->bd_fbuf);
	m_freem(d->bd_filterm);
E 2
I 2
D 10
	/* Free the buffer space. */
	if (d->bd_hbuf)
		free(d->bd_hbuf, M_DEVBUF);
	if (d->bd_fbuf)
		free(d->bd_fbuf, M_DEVBUF);
	free(d->bd_sbuf, M_DEVBUF);
D 3

	if (d->bd_filter != bpf_default_filter)
E 3
I 3
	if (d->bd_filter)
E 3
		free((caddr_t)d->bd_filter, M_DEVBUF);
E 2
	
	D_MARKFREE(d);
E 10
I 10
	bpf_freed(d);
I 13

	return (0);
E 13
E 10
}

I 13
/*
 * Support for SunOS, which does not have tsleep.
 */
E 13
I 10
#if BSD < 199103
static
bpf_timeout(arg)
	caddr_t arg;
{
	struct bpf_d *d = (struct bpf_d *)arg;
	d->bd_timedout = 1;
	wakeup(arg);
}

D 13
static int
tsleep(cp, pri, s, t)
	register caddr_t cp;
	register int pri;
	char *s;
	register int t;
E 13
I 13
#define BPF_SLEEP(chan, pri, s, t) bpf_sleep((struct bpf_d *)chan)

int
bpf_sleep(d)
	register struct bpf_d *d;
E 13
{
D 13
	register struct bpf_d *d = (struct bpf_d *)cp;
	register int error;
E 13
I 13
	register int rto = d->bd_rtout;
	register int st;
E 13

D 13
	if (t != 0) {
E 13
I 13
	if (rto != 0) {
E 13
		d->bd_timedout = 0;
D 13
		timeout(bpf_timeout, cp);
E 13
I 13
		timeout(bpf_timeout, (caddr_t)d, rto);
E 13
	}
D 13
	error = sleep(cp, pri);
	if (t != 0) {
		if (d->bd_timedout != 0)
E 13
I 13
	st = sleep((caddr_t)d, PRINET|PCATCH);
	if (rto != 0) {
		if (d->bd_timedout == 0)
			untimeout(bpf_timeout, (caddr_t)d);
		else if (st == 0)
E 13
			return EWOULDBLOCK;
D 13
		untimeout(bpf_timeout, cp);
E 13
	}
D 13
	return error;
E 13
I 13
	return (st != 0) ? EINTR : 0;
E 13
}
I 13
#else
#define BPF_SLEEP tsleep
E 13
#endif

E 10
D 2
#define RS_IDLE 0
#define RS_WAIT 1
#define RS_TIMEDOUT 2

E 2
/*
I 2
 * Rotate the packet buffers in descriptor d.  Move the store buffer
D 13
 * into the hold slot, and the free buffer into the store slot.  
E 13
I 13
 * into the hold slot, and the free buffer into the store slot.
E 13
 * Zero the length of the new store buffer.
 */
#define ROTATE_BUFFERS(d) \
	(d)->bd_hbuf = (d)->bd_sbuf; \
	(d)->bd_hlen = (d)->bd_slen; \
	(d)->bd_sbuf = (d)->bd_fbuf; \
	(d)->bd_slen = 0; \
D 13
	(d)->bd_fbuf = 0; 
E 13
I 13
	(d)->bd_fbuf = 0;
E 13
/*
E 2
 *  bpfread - read next chunk of packets from buffers
 */
int
bpfread(dev, uio)
	dev_t dev;
	register struct uio *uio;
{
	register struct bpf_d *d = &bpf_dtab[minor(dev)];
D 2
	struct mbuf *m;
E 2
	int error;
	int s;

	/*
D 13
	 * Restrict application to use a buffer the same size as 
E 13
I 13
	 * Restrict application to use a buffer the same size as
E 13
	 * as kernel buffers.
	 */
D 2
	if (uio->uio_resid != MCLBYTES)
		return EIO;
E 2
I 2
	if (uio->uio_resid != d->bd_bufsize)
D 4
		return (EIO);
E 4
I 4
		return (EINVAL);
E 4
E 2

	s = splimp();
	/*
D 13
	 * If the hold buffer is empty, then set a timer and sleep
	 * until either the timeout has occurred or enough packets have
	 * arrived to fill the store buffer.
E 13
I 13
	 * If the hold buffer is empty, then do a timed sleep, which
	 * ends when the timeout expires or when enough packets
	 * have arrived to fill the store buffer.
E 13
	 */
	while (d->bd_hbuf == 0) {
D 2
		if (d->bd_immediate && d->bd_sbuf->m_len) {
E 2
I 2
		if (d->bd_immediate && d->bd_slen != 0) {
E 2
			/*
			 * A packet(s) either arrived since the previous
			 * read or arrived while we were asleep.
			 * Rotate the buffers and return what's here.
			 */
D 2
			d->bd_hbuf = d->bd_sbuf;
			d->bd_sbuf = d->bd_fbuf;
			d->bd_sbuf->m_len = 0;
			d->bd_fbuf = 0;
E 2
I 2
			ROTATE_BUFFERS(d);
E 2
			break;
		}
D 2
		if (d->bd_rtout) {
			/*
			 * If there was a previous timeout pending for this 
			 * file, cancel it before setting another.  This is
			 * necessary since a cancel after the sleep might 
			 * never happen if the read is interrupted by a signal.
			 */
			if (d->bd_state == RS_WAIT)
				untimeout(bpf_timeout, (caddr_t)d);
			timeout(bpf_timeout, (caddr_t)d, (int)d->bd_rtout);
			d->bd_state = RS_WAIT;
E 2
I 2
D 13
		error = tsleep((caddr_t)d, PRINET|PCATCH, "bpf", d->bd_rtout);
E 13
I 13
		error = BPF_SLEEP((caddr_t)d, PRINET|PCATCH, "bpf",
				  d->bd_rtout);
E 13
		if (error == EINTR || error == ERESTART) {
			splx(s);
			return (error);
E 2
		}
D 2
		else
			d->bd_state = RS_IDLE;
		
		sleep((caddr_t)d, PRINET);
		
		if (d->bd_state == RS_WAIT) {
			untimeout(bpf_timeout, (caddr_t)d);
			d->bd_state = RS_IDLE;
		}
		else if (d->bd_state == RS_TIMEDOUT) {
E 2
I 2
		if (error == EWOULDBLOCK) {
E 2
			/*
			 * On a timeout, return what's in the buffer,
D 2
			 * which may be nothing.  We do this by moving
			 * the store buffer into the hold slot.
E 2
I 2
			 * which may be nothing.  If there is something
			 * in the store buffer, we can rotate the buffers.
E 2
			 */
			if (d->bd_hbuf)
				/*
D 13
				 * We filled up the buffer in between 
E 13
I 13
				 * We filled up the buffer in between
E 13
				 * getting the timeout and arriving
				 * here, so we don't need to rotate.
				 */
				break;

D 2
			if (d->bd_sbuf->m_len == 0) {
E 2
I 2
			if (d->bd_slen == 0) {
E 2
				splx(s);
D 2
				return(0);
E 2
I 2
				return (0);
E 2
			}
D 2
			d->bd_hbuf = d->bd_sbuf;
			d->bd_sbuf = d->bd_fbuf;
			d->bd_sbuf->m_len = 0;
			d->bd_fbuf = 0;
E 2
I 2
			ROTATE_BUFFERS(d);
E 2
			break;
		}
	}
	/*
	 * At this point, we know we have something in the hold slot.
	 */
D 2
	m = d->bd_hbuf;

E 2
	splx(s);
D 13
	
	/*  
E 13
I 13

	/*
E 13
	 * Move data from hold buffer into user space.
	 * We know the entire buffer is transferred since
D 2
	 * we checked above that the read buffer is MCLBYTES.
E 2
I 2
	 * we checked above that the read buffer is bpf_bufsize bytes.
E 2
	 */
I 10
D 13
#if BSD >= 199103
E 10
D 2
	error = bpf_moveout(m, uio);
E 2
I 2
	error = uiomove(d->bd_hbuf, d->bd_hlen, uio);
E 2
D 10

E 10
I 10
#else
	error = uiomove(d->bd_hbuf, d->bd_hlen, UIO_READ, uio);
#endif
E 13
I 13
	error = UIOMOVE(d->bd_hbuf, d->bd_hlen, UIO_READ, uio);

E 13
E 10
	s = splimp();
D 2
	if (d->bd_fbuf != 0)
		panic("bpfread: free mbuf slot occupied");
	d->bd_fbuf = m;
	d->bd_hbuf = (struct mbuf *)0;
E 2
I 2
	d->bd_fbuf = d->bd_hbuf;
	d->bd_hbuf = 0;
I 13
	d->bd_hlen = 0;
E 13
E 2
	splx(s);
D 13
	
E 13
I 13

E 13
D 2
	return error;
E 2
I 2
	return (error);
E 2
}


/*
D 2
 * If there are processes select sleeping on this descriptor,
 * wake them up.  
E 2
I 2
D 13
 * If there are processes sleeping on this descriptor, wake them up.  
E 13
I 13
 * If there are processes sleeping on this descriptor, wake them up.
E 13
E 2
 */
D 22
static inline void
E 22
I 22
static __inline void
E 22
bpf_wakeup(d)
	register struct bpf_d *d;
{
D 2
	if (d->bd_SelProc) {
		selwakeup(d->bd_SelProc, (int)d->bd_SelColl);
		d->bd_SelColl = 0;
		d->bd_SelProc = 0;
E 2
I 2
	wakeup((caddr_t)d);
D 12
	if (d->bd_selproc) {
		selwakeup(d->bd_selproc, (int)d->bd_selcoll);
		d->bd_selcoll = 0;
		d->bd_selproc = 0;
E 2
	}
E 12
I 12
D 13
	selwakeup(&d->bd_selproc);
E 13
I 13
#if BSD >= 199103
	selwakeup(&d->bd_sel);
	/* XXX */
	d->bd_sel.si_pid = 0;
#else
	if (d->bd_selproc) {
		selwakeup(d->bd_selproc, (int)d->bd_selcoll);
		d->bd_selcoll = 0;
		d->bd_selproc = 0;
	}
#endif
E 13
E 12
}

D 2
/*
 *  bpf_timeout - process ethernet read timeout
 */
static int
bpf_timeout(d)
	register struct bpf_d * d;
{
	register int s = splimp();

	d->bd_state = RS_TIMEDOUT;
	wakeup((caddr_t)d);
	bpf_wakeup(d);

	splx(s);
}

E 2
int
bpfwrite(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	register struct bpf_d *d = &bpf_dtab[minor(dev)];
	struct ifnet *ifp;
	struct mbuf *m;
	int error, s;
	static struct sockaddr dst;
I 16
	int datlen;
E 16

	if (d->bd_bif == 0)
D 2
		return ENXIO;
E 2
I 2
		return (ENXIO);
E 2

	ifp = d->bd_bif->bif_ifp;

	if (uio->uio_resid == 0)
D 2
		return 0;
E 2
I 2
		return (0);
E 2
D 16
	if (uio->uio_resid > ifp->if_mtu)
D 2
		return EMSGSIZE;
E 2
I 2
		return (EMSGSIZE);
E 16
E 2

D 4
	error = bpf_movein(uio, (int)d->bd_bif->bif_devp.bdev_type, &m, &dst);
E 4
I 4
D 16
	error = bpf_movein(uio, (int)d->bd_bif->bif_dlt, &m, &dst);
E 16
I 16
	error = bpf_movein(uio, (int)d->bd_bif->bif_dlt, &m, &dst, &datlen);
E 16
E 4
	if (error)
D 2
		return error;
E 2
I 2
		return (error);
I 16

	if (datlen > ifp->if_mtu)
		return (EMSGSIZE);
E 16
E 2

	s = splnet();
I 10
#if BSD >= 199103
D 13
	error = (*ifp->if_output)(ifp, m, &dst, (struct rtenty *)0);
E 13
I 13
	error = (*ifp->if_output)(ifp, m, &dst, (struct rtentry *)0);
E 13
#else
E 10
	error = (*ifp->if_output)(ifp, m, &dst);
I 10
#endif
E 10
	splx(s);
	/*
D 13
	 * The driver frees the mbuf. 
E 13
I 13
	 * The driver frees the mbuf.
E 13
	 */
D 2
	return error;
E 2
I 2
	return (error);
E 2
}

/*
D 2
 * Reset a descriptor by flushing its packet before
 * and clearing the receive and drop counts.  Should
 * be called at splimp.
E 2
I 2
D 13
 * Reset a descriptor by flushing its packet bufferand clearing the receive
 * and drop counts.  Should be called at splimp.
E 13
I 13
 * Reset a descriptor by flushing its packet buffer and clearing the
 * receive and drop counts.  Should be called at splimp.
E 13
E 2
 */
static void
reset_d(d)
	struct bpf_d *d;
{
	if (d->bd_hbuf) {
		/* Free the hold buffer. */
		d->bd_fbuf = d->bd_hbuf;
		d->bd_hbuf = 0;
	}
D 2
	d->bd_sbuf->m_len = 0;
E 2
I 2
	d->bd_slen = 0;
I 13
	d->bd_hlen = 0;
E 13
E 2
	d->bd_rcount = 0;
	d->bd_dcount = 0;
}

/*
D 4
 *  bpfioctl - packet filter control
 *
E 4
 *  FIONREAD		Check for read packet available.
 *  SIOCGIFADDR		Get interface address - convenient hook to driver.
D 10
 *  BIOCGFLEN		Get max filter len.
E 10
 *  BIOCGBLEN		Get buffer len [for read()].
 *  BIOCSETF		Set ethernet read filter.
 *  BIOCFLUSH		Flush read packet buffer.
 *  BIOCPROMISC		Put interface into promiscuous mode.
D 4
 *  BIOCDEVP		Get device parameters.
E 4
I 4
 *  BIOCGDLT		Get link layer type.
E 4
 *  BIOCGETIF		Get interface name.
 *  BIOCSETIF		Set interface.
 *  BIOCSRTIMEOUT	Set read timeout.
 *  BIOCGRTIMEOUT	Get read timeout.
 *  BIOCGSTATS		Get packet stats.
 *  BIOCIMMEDIATE	Set immediate mode.
I 13
 *  BIOCVERSION		Get filter language version.
E 13
 */
/* ARGSUSED */
int
bpfioctl(dev, cmd, addr, flag)
	dev_t dev;
D 23
	int cmd;
E 23
I 23
	u_long cmd;
E 23
	caddr_t addr;
	int flag;
{
	register struct bpf_d *d = &bpf_dtab[minor(dev)];
	int s, error = 0;

	switch (cmd) {

	default:
		error = EINVAL;
		break;

	/*
	 * Check for read packet available.
	 */
	case FIONREAD:
		{
			int n;
D 13
		
E 13
I 13

E 13
			s = splimp();
D 2
			n = d->bd_sbuf->m_len;
E 2
I 2
			n = d->bd_slen;
E 2
D 13
			if (d->bd_hbuf) 
E 13
I 13
			if (d->bd_hbuf)
E 13
D 2
				n += d->bd_hbuf->m_len;
E 2
I 2
				n += d->bd_hlen;
E 2
			splx(s);

			*(int *)addr = n;
			break;
		}

	case SIOCGIFADDR:
		{
			struct ifnet *ifp;

			if (d->bd_bif == 0)
				error = EINVAL;
			else {
				ifp = d->bd_bif->bif_ifp;
D 13
				error =  (*ifp->if_ioctl)(ifp, cmd, addr);
E 13
I 13
				error = (*ifp->if_ioctl)(ifp, cmd, addr);
E 13
			}
			break;
		}

	/*
D 10
	 * Get max filter len.
	 */
	case BIOCGFLEN:
D 2
		*(u_int *)addr = MCLBYTES / sizeof(struct bpf_insn);
E 2
I 2
		*(u_int *)addr = BPF_MAXINSNS;
E 2
		break;
	/*
E 10
	 * Get buffer len [for read()].
	 */
	case BIOCGBLEN:
D 2
		*(u_int *)addr = MCLBYTES;
E 2
I 2
		*(u_int *)addr = d->bd_bufsize;
E 2
		break;

	/*
I 13
	 * Set buffer length.
	 */
	case BIOCSBLEN:
#if BSD < 199103
		error = EINVAL;
#else
		if (d->bd_bif != 0)
			error = EINVAL;
		else {
			register u_int size = *(u_int *)addr;

			if (size > BPF_MAXBUFSIZE)
				*(u_int *)addr = size = BPF_MAXBUFSIZE;
			else if (size < BPF_MINBUFSIZE)
				*(u_int *)addr = size = BPF_MINBUFSIZE;
			d->bd_bufsize = size;
		}
#endif
		break;

	/*
E 13
D 10
	 * Set ethernet read filter.
E 10
I 10
	 * Set link layer read filter.
E 10
	 */
D 13
        case BIOCSETF:
E 13
I 13
	case BIOCSETF:
E 13
		error = bpf_setf(d, (struct bpf_program *)addr);
		break;

	/*
	 * Flush read packet buffer.
	 */
	case BIOCFLUSH:
		s = splimp();
		reset_d(d);
		splx(s);
		break;

	/*
	 * Put interface into promiscuous mode.
	 */
	case BIOCPROMISC:
		if (d->bd_bif == 0) {
			/*
			 * No interface attached yet.
			 */
			error = EINVAL;
			break;
		}
		s = splimp();
		if (d->bd_promisc == 0) {
D 10
			d->bd_promisc = 1;
E 10
			error = ifpromisc(d->bd_bif->bif_ifp, 1);
I 10
			if (error == 0)
				d->bd_promisc = 1;
E 10
		}
		splx(s);
		break;

	/*
	 * Get device parameters.
	 */
D 4
	case BIOCDEVP:
E 4
I 4
	case BIOCGDLT:
E 4
		if (d->bd_bif == 0)
			error = EINVAL;
		else
D 4
			*(struct bpf_devp *)addr = d->bd_bif->bif_devp;
E 4
I 4
			*(u_int *)addr = d->bd_bif->bif_dlt;
E 4
		break;

	/*
	 * Set interface name.
	 */
	case BIOCGETIF:
		if (d->bd_bif == 0)
			error = EINVAL;
		else
			bpf_ifname(d->bd_bif->bif_ifp, (struct ifreq *)addr);
		break;

	/*
	 * Set interface.
	 */
	case BIOCSETIF:
		error = bpf_setif(d, (struct ifreq *)addr);
		break;

	/*
	 * Set read timeout.
	 */
D 13
 	case BIOCSRTIMEOUT:
E 13
I 13
	case BIOCSRTIMEOUT:
E 13
		{
			struct timeval *tv = (struct timeval *)addr;
			u_long msec;

			/* Compute number of milliseconds. */
			msec = tv->tv_sec * 1000 + tv->tv_usec / 1000;
			/* Scale milliseconds to ticks.  Assume hard
			   clock has millisecond or greater resolution
			   (i.e. tick >= 1000).  For 10ms hardclock,
			   tick/1000 = 10, so rtout<-msec/10. */
			d->bd_rtout = msec / (tick / 1000);
			break;
		}

	/*
	 * Get read timeout.
	 */
D 13
 	case BIOCGRTIMEOUT:
E 13
I 13
	case BIOCGRTIMEOUT:
E 13
		{
			struct timeval *tv = (struct timeval *)addr;
			u_long msec = d->bd_rtout;

			msec *= tick / 1000;
			tv->tv_sec = msec / 1000;
			tv->tv_usec = msec % 1000;
			break;
		}

	/*
	 * Get packet stats.
	 */
	case BIOCGSTATS:
		{
			struct bpf_stat *bs = (struct bpf_stat *)addr;

			bs->bs_recv = d->bd_rcount;
			bs->bs_drop = d->bd_dcount;
			break;
		}

	/*
	 * Set immediate mode.
	 */
	case BIOCIMMEDIATE:
		d->bd_immediate = *(u_int *)addr;
		break;
I 13

	case BIOCVERSION:
		{
			struct bpf_version *bv = (struct bpf_version *)addr;

			bv->bv_major = BPF_MAJOR_VERSION;
			bv->bv_minor = BPF_MINOR_VERSION;
			break;
		}
E 13
	}
D 2
	return error;
E 2
I 2
	return (error);
E 2
}

D 13
/* 
E 13
I 13
/*
E 13
D 10
 * Set d's packet filter program to 'fp'.  If 'd' already has a filter,
E 10
I 10
 * Set d's packet filter program to fp.  If this file already has a filter,
E 10
D 2
 * free it and replace it.  Returns an appropriate ioctl error code.
E 2
I 2
 * free it and replace it.  Returns EINVAL for bogus requests.
E 2
 */
int
bpf_setf(d, fp)
	struct bpf_d *d;
	struct bpf_program *fp;
{
D 2
	struct bpf_insn *fcode;
	struct mbuf *m;
E 2
I 2
	struct bpf_insn *fcode, *old;
E 2
	u_int flen, size;
	int s;

I 2
	old = d->bd_filter;
E 2
	if (fp->bf_insns == 0) {
D 2
		s = splimp();
E 2
		if (fp->bf_len != 0)
D 2
			return EINVAL;
		if (d->bd_filterm)
			m_freem(d->bd_filterm);
		d->bd_filterm = 0;
E 2
I 2
			return (EINVAL);
E 2
D 3
		d->bd_filter = bpf_default_filter;
E 3
I 2
		s = splimp();
I 3
		d->bd_filter = 0;
E 3
E 2
		reset_d(d);
		splx(s);
D 2
		return 0;
E 2
I 2
D 3
		if (old != bpf_default_filter)
E 3
I 3
		if (old != 0)
E 3
			free((caddr_t)old, M_DEVBUF);
		return (0);
E 2
	}
	flen = fp->bf_len;
I 2
	if (flen > BPF_MAXINSNS)
		return (EINVAL);

E 2
	size = flen * sizeof(*fp->bf_insns);
I 2
	fcode = (struct bpf_insn *)malloc(size, M_DEVBUF, M_WAITOK);
D 9
	if (copyin((caddr_t)fp->bf_insns, (caddr_t)fcode, size))
		return (EINVAL);
E 2
	
D 2
	if (size > MCLBYTES)
		return EINVAL;
	
	MGET(m, M_DONTWAIT, MT_DATA);
	if (m == 0)
		return ENOBUFS;
	
	if (size > MLEN) {
		MCLGET(m);
		if (m->m_len != MCLBYTES) {
			m_freem(m);
			return ENOBUFS;
		}
	}
	fcode = mtod(m, struct bpf_insn *);
	if (copyin((caddr_t)(fp->bf_insns), (caddr_t)fcode, size))
		return EINVAL;
	
E 2
	if (bpf_validate(fcode, (int)flen)) {
E 9
I 9
	if (copyin((caddr_t)fp->bf_insns, (caddr_t)fcode, size) == 0 &&
	    bpf_validate(fcode, (int)flen)) {
E 9
D 2
		s = splimp();
		if (d->bd_filterm)
			m_freem(d->bd_filterm);
		d->bd_filterm = m;
E 2
D 3
		d->bd_filter = fcode;
E 3
I 2
		s = splimp();
I 3
		d->bd_filter = fcode;
E 3
E 2
		reset_d(d);
		splx(s);
I 2
D 3
		if (old != bpf_default_filter)
E 3
I 3
		if (old != 0)
E 3
			free((caddr_t)old, M_DEVBUF);
E 2

D 2
		return 0;
E 2
I 2
		return (0);
E 2
	}
D 2
	m_freem(m);
	return EINVAL;
E 2
I 2
	free((caddr_t)fcode, M_DEVBUF);
	return (EINVAL);
E 2
}

/*
D 10
 * Detach 'd' from its current interface (if attached at all) and attach to 
 * the interface named 'name'.  Return ioctl error code or 0.
E 10
I 10
D 13
 * Detach a file from its current interface (if attached at all) and attach 
 * to the interface indicated by the name stored in ifr.  
E 13
I 13
 * Detach a file from its current interface (if attached at all) and attach
 * to the interface indicated by the name stored in ifr.
E 13
 * Return an errno or 0.
E 10
 */
static int
bpf_setif(d, ifr)
	struct bpf_d *d;
	struct ifreq *ifr;
{
	struct bpf_if *bp;
	char *cp;
D 4
	int unit, i, s;
E 4
I 4
D 13
	int unit, s;
E 13
I 13
	int unit, s, error;
E 13
E 4

	/*
	 * Separate string into name part and unit number.  Put a null
D 13
	 * byte at the end of the name part, and compute the number. 
E 13
I 13
	 * byte at the end of the name part, and compute the number.
E 13
	 * If the a unit number is unspecified, the default is 0,
D 2
	 * as initialized above.
E 2
I 2
	 * as initialized above.  XXX This should be common code.
E 2
	 */
	unit = 0;
	cp = ifr->ifr_name;
	cp[sizeof(ifr->ifr_name) - 1] = '\0';
	while (*cp++) {
		if (*cp >= '0' && *cp <= '9') {
			unit = *cp - '0';
			*cp++ = '\0';
			while (*cp)
				unit = 10 * unit + *cp++ - '0';
			break;
		}
	}
	/*
	 * Look through attached interfaces for the named one.
	 */
D 4
	bp = bpf_iftab;
	for (i = 0; i < NBPFILTER; ++bp, ++i) {
E 4
I 4
	for (bp = bpf_iflist; bp != 0; bp = bp->bif_next) {
E 4
		struct ifnet *ifp = bp->bif_ifp;

D 13
		if (ifp == 0 || unit != ifp->if_unit 
E 13
I 13
		if (ifp == 0 || unit != ifp->if_unit
E 13
		    || strcmp(ifp->if_name, ifr->ifr_name) != 0)
			continue;
		/*
D 13
		 * We found the requested interface.  If we're
		 * already attached to it, just flush the buffer.
E 13
I 13
		 * We found the requested interface.
E 13
		 * If it's not up, return an error.
I 13
		 * Allocate the packet buffers if we need to.
		 * If we're already attached to requested interface,
		 * just flush the buffer.
E 13
		 */
		if ((ifp->if_flags & IFF_UP) == 0)
D 2
			return ENETDOWN;
E 2
I 2
			return (ENETDOWN);
I 13

		if (d->bd_sbuf == 0) {
			error = bpf_allocbufs(d);
			if (error != 0)
				return (error);
		}
E 13
E 2
		s = splimp();
		if (bp != d->bd_bif) {
			if (d->bd_bif)
D 13
				/* 
E 13
I 13
				/*
E 13
D 2
				 * Detach if attached to  something else.
E 2
I 2
				 * Detach if attached to something else.
E 2
				 */
				bpf_detachd(d);

			bpf_attachd(d, bp);
		}
		reset_d(d);
		splx(s);
D 2
		return 0;
E 2
I 2
		return (0);
E 2
	}
	/* Not found. */
D 2
	return ENXIO;
E 2
I 2
	return (ENXIO);
E 2
}

/*
D 10
 * Lookup the name of the 'ifp' interface and return it in 'ifr->ifr_name'.
 * We augment the ifp's base name with its unit number.
E 10
I 10
 * Convert an interface name plus unit number of an ifp to a single
 * name which is returned in the ifr.
E 10
 */
static void
bpf_ifname(ifp, ifr)
	struct ifnet *ifp;
	struct ifreq *ifr;
{
	char *s = ifp->if_name;
	char *d = ifr->ifr_name;

	while (*d++ = *s++)
D 13
		;
E 13
I 13
		continue;
E 13
D 2
	/* Assume that unit number is less than 10. */
E 2
I 2
	/* XXX Assume that unit number is less than 10. */
E 2
	*d++ = ifp->if_unit + '0';
	*d = '\0';
}

/*
I 10
 * The new select interface passes down the proc pointer; the old select
 * stubs had to grab it out of the user struct.  This glue allows either case.
 */
#if BSD >= 199103
#define bpf_select bpfselect
#else
int
bpfselect(dev, rw)
	register dev_t dev;
	int rw;
{
D 13
	bpf_select(dev, rw, u.u_procp);
E 13
I 13
	return (bpf_select(dev, rw, u.u_procp));
E 13
}
#endif

/*
E 10
 * Support for select() system call
D 19
 * Inspired by the code in tty.c for the same purpose.
E 19
 *
D 13
 * bpfselect - returns true iff the specific operation
 *	will not block indefinitely.  Otherwise, return
 *	false but make a note that a selwakeup() must be done.
E 13
I 13
 * Return true iff the specific operation will not block indefinitely.
 * Otherwise, return false but make a note that a selwakeup() must be done.
E 13
 */
int
D 2
bpfselect(dev, rw)
E 2
I 2
D 10
bpfselect(dev, rw, p)
E 10
I 10
bpf_select(dev, rw, p)
E 10
E 2
	register dev_t dev;
	int rw;
I 2
	struct proc *p;
E 2
{
	register struct bpf_d *d;
	register int s;
D 13
	
E 13
I 13

E 13
	if (rw != FREAD)
D 2
		return 0;
E 2
I 2
		return (0);
E 2
	/*
	 * An imitation of the FIONREAD ioctl code.
	 */
	d = &bpf_dtab[minor(dev)];
D 13
	
E 13
I 13

E 13
	s = splimp();
D 2
	if (d->bd_sbuf->m_len ||
	    d->bd_hbuf && d->bd_hbuf->m_len) {
E 2
I 2
D 6
	if (d->bd_slen != 0 || d->bd_hbuf && d->bd_hlen != 0) {
E 6
I 6
	if (d->bd_hlen != 0 || (d->bd_immediate && d->bd_slen != 0)) {
E 6
E 2
		/*
		 * There is data waiting.
		 */
		splx(s);
D 2
		return 1;
E 2
I 2
		return (1);
E 2
	}
I 13
#if BSD >= 199103
	selrecord(p, &d->bd_sel);
#else
E 13
	/*
	 * No data ready.  If there's already a select() waiting on this
D 13
	 * minor device then this is a collision.  This shouldn't happen 
E 13
I 13
	 * minor device then this is a collision.  This shouldn't happen
E 13
	 * because minors really should not be shared, but if a process
	 * forks while one of these is open, it is possible that both
	 * processes could select on the same descriptor.
	 */
D 2
	if (d->bd_SelProc && d->bd_SelProc->p_wchan == (caddr_t)&selwait)
		d->bd_SelColl = 1;
E 2
I 2
D 12
	if (d->bd_selproc && d->bd_selproc->p_wchan == (caddr_t)&selwait)
		d->bd_selcoll = 1;
E 2
	else
D 2
		d->bd_SelProc = u.u_procp;		
E 2
I 2
		d->bd_selproc = p;

E 12
I 12
D 13
	selrecord(p, &d->bd_selproc);
E 12
E 2
	splx(s);	
E 13
I 13
	if (d->bd_selproc && d->bd_selproc->p_wchan == (caddr_t)&selwait)
		d->bd_selcoll = 1;
	else
		d->bd_selproc = p;
#endif
	splx(s);
E 13
D 2
	return 0;
E 2
I 2
	return (0);
E 2
}

/*
D 13
 * bpf_tap - incoming linkage from device drivers
E 13
I 13
 * Incoming linkage from device drivers.  Process the packet pkt, of length
 * pktlen, which is stored in a contiguous buffer.  The packet is parsed
 * by each process' filter, and if accepted, stashed into the corresponding
 * buffer.
E 13
 */
void
D 2
bpf_tap(arg, pbuf, plen)
E 2
I 2
bpf_tap(arg, pkt, pktlen)
E 2
	caddr_t arg;
D 2
	register u_char *pbuf;
	register u_int plen;
E 2
I 2
	register u_char *pkt;
	register u_int pktlen;
E 2
{
	struct bpf_if *bp;
	register struct bpf_d *d;
	register u_int slen;
D 4
	extern bcopy();
E 4
	/*
	 * Note that the ipl does not have to be raised at this point.
	 * The only problem that could arise here is that if two different
	 * interfaces shared any data.  This is not the case.
	 */
	bp = (struct bpf_if *)arg;
	for (d = bp->bif_dlist; d != 0; d = d->bd_next) {
		++d->bd_rcount;
D 2
		slen = bpf_filter(d->bd_filter, pbuf, plen, plen);
E 2
I 2
D 3
		slen = bpf_filter(d->bd_filter, pkt, pktlen, pktlen);
E 3
I 3
D 4
		if (d->bd_filter) 
			slen = bpf_filter(d->bd_filter, pkt, pktlen, pktlen);
		else 
			slen = (u_int)-1;

E 4
I 4
D 6
		if (d->bd_filter == 0) {
			catchpacket(d, pkt, pktlen, (u_int)-1, bcopy);
			continue;
		}
E 6
		slen = bpf_filter(d->bd_filter, pkt, pktlen, pktlen);
E 4
E 3
E 2
		if (slen != 0)
D 2
			catchpacket(d, pbuf, plen, slen, (void (*)())bcopy);
E 2
I 2
D 4
			catchpacket(d, pkt, pktlen, slen, (void (*)())bcopy);
E 4
I 4
			catchpacket(d, pkt, pktlen, slen, bcopy);
E 4
E 2
	}
}

/*
 * Copy data from an mbuf chain into a buffer.  This code is derived
 * from m_copydata in sys/uipc_mbuf.c.
 */
static void
D 4
bpf_m_copydata(src, dst, len)
E 4
I 4
D 19
bpf_mcopy(src, dst, len)
E 4
	u_char *src;
	u_char *dst;
	register int len;
E 19
I 19
bpf_mcopy(src_arg, dst_arg, len)
D 21
	void *src_arg, *dst_arg;
E 21
I 21
	const void *src_arg;
	void *dst_arg;
E 21
	register u_int len;
E 19
{
D 19
	register struct mbuf *m = (struct mbuf *)src;
	register unsigned count;
E 19
I 19
D 21
	register struct mbuf *m;
E 21
I 21
	register const struct mbuf *m;
E 21
	register u_int count;
D 21
	u_char *src, *dst;
E 21
I 21
	u_char *dst;
E 21
E 19

I 19
D 21
	src = src_arg;
	dst = dst_arg;
E 21
	m = src_arg;
I 21
	dst = dst_arg;
E 21
E 19
	while (len > 0) {
		if (m == 0)
D 4
			panic("bpf_m_copydata");
E 4
I 4
			panic("bpf_mcopy");
E 4
D 15
		count = MIN(m->m_len, len);
E 15
I 15
		count = min(m->m_len, len);
E 15
D 4
		(void)bcopy(mtod(m, caddr_t), (caddr_t)dst, count);
		len -= count;
		dst += count;
E 4
I 4
		bcopy(mtod(m, caddr_t), (caddr_t)dst, count);
E 4
		m = m->m_next;
I 4
		dst += count;
		len -= count;
E 4
	}
}

/*
D 2
 * Length of ethernet and TCP/IP header header with no IP options.
E 2
I 2
D 6
 * Length of ethernet and TCP/IP header with no IP options.
E 2
 */
#define BPF_MIN_SNAPLEN 50

/*
E 6
D 10
 * bpf_mtap - incoming linkage from device drivers, when packet
 *   is in an mbuf chain
E 10
I 10
D 13
 * bpf_mtap -	incoming linkage from device drivers, when packet
 *		is in an mbuf chain
E 13
I 13
 * Incoming linkage from device drivers, when packet is in an mbuf chain.
E 13
E 10
 */
void
D 4
bpf_mtap(arg, m0)
E 4
I 4
bpf_mtap(arg, m)
E 4
	caddr_t arg;
D 4
	struct mbuf *m0;
E 4
I 4
	struct mbuf *m;
E 4
{
D 2
	static u_char buf[BPF_MIN_SNAPLEN];

E 2
	struct bpf_if *bp = (struct bpf_if *)arg;
	struct bpf_d *d;
I 4
	u_int pktlen, slen;
	struct mbuf *m0;
D 5
#ifdef notdef
E 4
	u_char *cp;
D 2
	u_int slen, plen;
E 2
I 2
D 4
	u_int slen, pktlen;
E 4
E 2
	int nbytes;
D 4
	struct mbuf *m;
E 4
I 2
	static u_char buf[BPF_MIN_SNAPLEN];
E 5
E 2

D 4
	if (m0->m_len >= BPF_MIN_SNAPLEN) {
		slen = m0->m_len;
		cp = mtod(m0, u_char *);
E 4
I 4
D 5
	if (m->m_len >= BPF_MIN_SNAPLEN) {
		slen = m->m_len;
		cp = mtod(m, u_char *);
E 4
	} 
	else {
		nbytes = BPF_MIN_SNAPLEN;
		cp = buf;
D 4
		m = m0;
		while (m && nbytes > 0) {		
			slen = MIN(m->m_len, nbytes);
			bcopy(mtod(m, char *), (char *)cp, slen);
E 4
I 4
		m0 = m;
		while (m0 && nbytes > 0) {		
			slen = MIN(m0->m_len, nbytes);
			bcopy(mtod(m0, char *), (char *)cp, slen);
E 4
			cp += slen;
			nbytes -= slen;
D 4
			m = m->m_next;
E 4
I 4
			m0 = m0->m_next;
E 4
		}
		if (nbytes > 0)
			/* Packet too small? */
			return;

		slen = BPF_MIN_SNAPLEN;
		cp = buf;
	}
I 4
#endif
E 5
E 4
D 2
	plen = 0;
E 2
I 2
	pktlen = 0;
E 2
D 4
	m = m0;
	while (m) {
D 2
		plen += m->m_len;
E 2
I 2
		pktlen += m->m_len;
E 2
		m = m->m_next;
E 4
I 4
D 6
	m0 = m;
	while (m0) {
E 6
I 6
D 10
	for (m0 = m; m0 != m; m0 = m0->m_next)
E 10
I 10
	for (m0 = m; m0 != 0; m0 = m0->m_next)
E 10
E 6
		pktlen += m0->m_len;
D 6
		m0 = m0->m_next;
E 4
	}
E 6
I 6

E 6
	for (d = bp->bif_dlist; d != 0; d = d->bd_next) {
		++d->bd_rcount;
D 2
		slen = bpf_filter(d->bd_filter, cp, plen, slen);
E 2
I 2
D 3
		slen = bpf_filter(d->bd_filter, cp, pktlen, slen);
E 3
I 3
D 4
		if (d->bd_filter)
			slen = bpf_filter(d->bd_filter, cp, pktlen, slen);
		else
			slen = (u_int)-1;
E 4
I 4
D 6
		if (d->bd_filter == 0) {
			catchpacket(d, (u_char *)m, pktlen, (u_int)-1,
				    bpf_mcopy);
			continue;
		}
E 6
		slen = bpf_filter(d->bd_filter, (u_char *)m, pktlen, 0);
E 4
E 3
E 2
		if (slen != 0)
D 2
			catchpacket(d, (u_char *)m0, plen, slen,
E 2
I 2
D 4
			catchpacket(d, (u_char *)m0, pktlen, slen,
E 2
				    bpf_m_copydata);
E 4
I 4
			catchpacket(d, (u_char *)m, pktlen, slen, bpf_mcopy);
E 4
	}
}

/*
D 2
 * Move the packet data from interface memory ('pbuf') into the
E 2
I 2
D 4
 * Move the packet data from interface memory ('pkt') into the
E 4
I 4
 * Move the packet data from interface memory (pkt) into the
E 4
E 2
 * store buffer.  Return 1 if it's time to wakeup a listener (buffer full),
D 10
 * otherwise 0.  'copy' is the routine called to do the actual data 
 * transfer.  'bcopy' is passed in to copy contiguous chunks, while
D 4
 * 'bpf_m_copydata' is passed in to copy mbuf chains.  In the latter
E 4
I 4
 * 'bpf_mcopy' is passed in to copy mbuf chains.  In the latter
E 4
D 2
 * case, 'pbuf' is really an mbuf.
E 2
I 2
 * case, 'pkt' is really an mbuf.
E 10
I 10
D 13
 * otherwise 0.  "copy" is the routine called to do the actual data 
E 13
I 13
 * otherwise 0.  "copy" is the routine called to do the actual data
E 13
 * transfer.  bcopy is passed in to copy contiguous chunks, while
 * bpf_mcopy is passed in to copy mbuf chains.  In the latter case,
 * pkt is really an mbuf.
E 10
E 2
 */
static void
D 2
catchpacket(d, pbuf, plen, snaplen, cpfn)
	struct bpf_d *d;
	u_char *pbuf;
	u_int plen, snaplen;
	void (*cpfn)();
E 2
I 2
catchpacket(d, pkt, pktlen, snaplen, cpfn)
	register struct bpf_d *d;
	register u_char *pkt;
	register u_int pktlen, snaplen;
D 21
	register void (*cpfn)();
E 21
I 21
	register void (*cpfn)(const void *, void *, u_int);
E 21
E 2
{
D 2
	struct mbuf *m;
	struct bpf_hdr *hp;
	int totlen, curlen;
	int hdrlen = d->bd_bif->bif_hdrlen;
E 2
I 2
	register struct bpf_hdr *hp;
	register int totlen, curlen;
	register int hdrlen = d->bd_bif->bif_hdrlen;
E 2
	/*
	 * Figure out how many bytes to move.  If the packet is
	 * greater or equal to the snapshot length, transfer that
	 * much.  Otherwise, transfer the whole packet (unless
D 2
	 * we hit the cluster limit).
E 2
I 2
	 * we hit the buffer size limit).
E 2
	 */
D 2
	if (snaplen <= plen)
E 2
I 2
D 8
	if (snaplen <= pktlen)
E 2
		totlen = snaplen + hdrlen;
	else {
D 2
		totlen = plen + hdrlen;
		if (totlen > MCLBYTES)
			totlen = MCLBYTES;
E 2
I 2
		totlen = pktlen + hdrlen;
		if (totlen > d->bd_bufsize)
			totlen = d->bd_bufsize;
E 2
	}
E 8
I 8
D 15
	totlen = hdrlen + MIN(snaplen, pktlen);
E 15
I 15
	totlen = hdrlen + min(snaplen, pktlen);
E 15
	if (totlen > d->bd_bufsize)
		totlen = d->bd_bufsize;
E 8

D 2
	m = d->bd_sbuf;

E 2
	/*
	 * Round up the end of the previous packet to the next longword.
	 */
D 2
	curlen = BPF_WORDALIGN(m->m_len);

	if (curlen + totlen > MCLBYTES) {
E 2
I 2
	curlen = BPF_WORDALIGN(d->bd_slen);
	if (curlen + totlen > d->bd_bufsize) {
E 2
		/*
		 * This packet will overflow the storage buffer.
D 2
		 * Move the current cluster buffer to the hold slot,
		 * and grab the free one.
E 2
I 2
		 * Rotate the buffers if we can, then wakeup any
		 * pending reads.
E 2
		 */
		if (d->bd_fbuf == 0) {
D 13
			/* 
D 2
			 * We haven't completed the previous read yet?
			 * Drop the packet.
E 2
I 2
			 * We haven't completed the previous read yet, 
E 13
I 13
			/*
			 * We haven't completed the previous read yet,
E 13
			 * so drop the packet.
E 2
			 */
			++d->bd_dcount;
			return;
		}
D 2
		/*
		 * Rotate the buffers.  Move the 'store' buffer
		 * into the 'hold' slot, and the 'free' buffer
		 * into the 'store' slot.  Zero out the length of
		 * the new 'store' buffer.
		 */
		d->bd_hbuf = d->bd_sbuf;
		m = d->bd_sbuf = d->bd_fbuf;
		d->bd_fbuf = 0;
		curlen = m->m_len = 0;

		/*
		 * Wake up anyone sleeping on this descriptor. 
		 */
		wakeup((caddr_t)d);
E 2
I 2
		ROTATE_BUFFERS(d);
E 2
		bpf_wakeup(d);
I 2
		curlen = 0;
E 2
	}
D 2
	else if (d->bd_immediate) {
E 2
I 2
D 13
	else if (d->bd_immediate) 
E 13
I 13
	else if (d->bd_immediate)
E 13
E 2
		/*
		 * Immediate mode is set.  A packet arrived so any
		 * reads should be woken up.
		 */
D 2
		wakeup((caddr_t)d);
E 2
		bpf_wakeup(d);
D 2
	}
E 2
I 2

E 2
	/*
	 * Append the bpf header.
	 */
D 2
	hp = (struct bpf_hdr *)(mtod(m, u_char *) + curlen);
E 2
I 2
	hp = (struct bpf_hdr *)(d->bd_sbuf + curlen);
E 2
D 13
#ifdef sun
	uniqtime(&hp->bh_tstamp);
#else
E 13
D 10
#ifdef hp300
E 10
I 10
#if BSD >= 199103
E 10
	microtime(&hp->bh_tstamp);
I 13
#elif defined(sun)
	uniqtime(&hp->bh_tstamp);
E 13
#else
	hp->bh_tstamp = time;
#endif
D 13
#endif
E 13
D 2
	hp->bh_datalen = plen;
E 2
I 2
	hp->bh_datalen = pktlen;
E 2
	hp->bh_hdrlen = hdrlen;
	/*
D 2
	 * Copy the packet data into the 'store' buffer and
	 * update the cluster length.
E 2
I 2
	 * Copy the packet data into the store buffer and update its length.
E 2
	 */
D 2
	(*cpfn)(pbuf, (u_char *)hp + hdrlen, hp->bh_caplen = totlen - hdrlen);

	m->m_len = curlen + totlen;
E 2
I 2
	(*cpfn)(pkt, (u_char *)hp + hdrlen, (hp->bh_caplen = totlen - hdrlen));
	d->bd_slen = curlen + totlen;
E 2
}

D 2
/*
 * Allocate an mbuf cluster and clear its length field.
 * If resources unavaiable, return 0.
 * We can wait in MGET since we assume that we are called
 * at a low priority.
 */
static struct mbuf *
bpf_mcluster()
{
	struct mbuf *m;

	MGET(m, M_WAIT, MT_DATA);
	if (m == 0)
		return 0;
	MCLGET(m);
	if (m->m_len == MCLBYTES) {
		m->m_len = 0;
		return m;
	}
	m_freem(m);
	return 0;
}

E 2
D 13
/* 
E 13
I 13
/*
E 13
 * Initialize all nonzero fields of a descriptor.
 */
static int
D 13
bpf_initd(d)
E 13
I 13
bpf_allocbufs(d)
E 13
	register struct bpf_d *d;
{
D 2
	struct mbuf *m;
E 2
I 2
D 13
	d->bd_bufsize = bpf_bufsize;
E 13
	d->bd_fbuf = (caddr_t)malloc(d->bd_bufsize, M_DEVBUF, M_WAITOK);
	if (d->bd_fbuf == 0)
		return (ENOBUFS);
E 2

D 2
	/* Get the buffer space. */
	m = bpf_mcluster();
	if (m == 0)
		return ENOBUFS;
	d->bd_fbuf = m;
	m = bpf_mcluster();
	if (m == 0) {
		m_freem(d->bd_fbuf);
		return ENOBUFS;
E 2
I 2
	d->bd_sbuf = (caddr_t)malloc(d->bd_bufsize, M_DEVBUF, M_WAITOK);
	if (d->bd_sbuf == 0) {
		free(d->bd_fbuf, M_DEVBUF);
		return (ENOBUFS);
E 2
	}
D 2
	d->bd_sbuf = m;

	return 0;
E 2
I 2
	d->bd_slen = 0;
	d->bd_hlen = 0;
	return (0);
E 2
}

/*
D 4
 * Register 'ifp' with bpf.  'devp' is the link-level device descriptor
E 4
I 4
D 10
 * Register 'ifp' with bpf.  XXX
E 4
 * and 'driverp' is a pointer to the 'struct bpf_if *' in the driver's softc.
E 10
I 10
 * Free buffers currently in use by a descriptor.
 * Called on close.
E 10
 */
I 13
static void
E 13
I 10
bpf_freed(d)
	register struct bpf_d *d;
{
	/*
	 * We don't need to lock out interrupts since this descriptor has
D 13
	 * been detached from its interface and it yet hasn't been marked 
E 13
I 13
	 * been detached from its interface and it yet hasn't been marked
E 13
	 * free.
	 */
D 13
	if (d->bd_hbuf)
		free(d->bd_hbuf, M_DEVBUF);
	if (d->bd_fbuf)
		free(d->bd_fbuf, M_DEVBUF);
	free(d->bd_sbuf, M_DEVBUF);
E 13
I 13
	if (d->bd_sbuf != 0) {
		free(d->bd_sbuf, M_DEVBUF);
		if (d->bd_hbuf != 0)
			free(d->bd_hbuf, M_DEVBUF);
		if (d->bd_fbuf != 0)
			free(d->bd_fbuf, M_DEVBUF);
	}
E 13
	if (d->bd_filter)
		free((caddr_t)d->bd_filter, M_DEVBUF);
D 13
	
E 13
I 13

E 13
	D_MARKFREE(d);
}

/*
 * Attach an interface to bpf.  driverp is a pointer to a (struct bpf_if *)
 * in the driver's softc; dlt is the link layer type; hdrlen is the fixed
 * size of the link header (variable length headers not yet supported).
 */
E 10
void
D 4
bpfattach(driverp, ifp, devp)
E 4
I 4
bpfattach(driverp, ifp, dlt, hdrlen)
E 4
	caddr_t *driverp;
	struct ifnet *ifp;
D 4
	struct bpf_devp *devp;
E 4
I 4
	u_int dlt, hdrlen;
E 4
{
	struct bpf_if *bp;
	int i;
I 10
#if BSD < 199103
	static struct bpf_if bpf_ifs[NBPFILTER];
	static int bpfifno;
E 10

I 10
	bp = (bpfifno < NBPFILTER) ? &bpf_ifs[bpfifno++] : 0;
#else
E 10
D 4
	if (bpf_units >= NBPFILTER) {
		printf("bpf: too many interfaces: %s%d not attached\n",
		       ifp->if_name, ifp->if_unit);
		return;
	}
	bp = &bpf_iftab[bpf_units++];
E 4
I 4
	bp = (struct bpf_if *)malloc(sizeof(*bp), M_DEVBUF, M_DONTWAIT);
I 10
#endif
E 10
	if (bp == 0)
		panic("bpfattach");
E 4

	bp->bif_dlist = 0;
	bp->bif_driverp = (struct bpf_if **)driverp;
	bp->bif_ifp = ifp;
D 4
	bp->bif_devp = *devp;
E 4
I 4
	bp->bif_dlt = dlt;
E 4

I 4
	bp->bif_next = bpf_iflist;
	bpf_iflist = bp;

E 4
I 2
	*bp->bif_driverp = 0;

E 2
	/*
	 * Compute the length of the bpf header.  This is not necessarily
D 13
	 * equal to SIZEOF_BPF_HDR because we want to insert spacing such 
	 * that the network layer header begins on a longword boundary (for 
E 13
I 13
	 * equal to SIZEOF_BPF_HDR because we want to insert spacing such
	 * that the network layer header begins on a longword boundary (for
E 13
	 * performance reasons and to alleviate alignment restrictions).
	 */
D 4
	i = devp->bdev_hdrlen;
	bp->bif_hdrlen = BPF_WORDALIGN(i + SIZEOF_BPF_HDR) - i;
E 4
I 4
	bp->bif_hdrlen = BPF_WORDALIGN(hdrlen + SIZEOF_BPF_HDR) - hdrlen;
E 4

	/*
	 * Mark all the descriptors free if this hasn't been done.
	 */
	if (!D_ISFREE(&bpf_dtab[0]))
		for (i = 0; i < NBPFILTER; ++i)
			D_MARKFREE(&bpf_dtab[i]);

	printf("bpf: %s%d attached\n", ifp->if_name, ifp->if_unit);
I 2
}

I 10
#if BSD >= 199103
E 10
D 3
/* XXX This routine goes in net/if.c. */
E 3
I 3
/* XXX This routine belongs in net/if.c. */
E 3
/*
D 13
 * Set/clear promiscuous mode on interface ifp based on the truth value`
E 13
I 13
 * Set/clear promiscuous mode on interface ifp based on the truth value
E 13
 * of pswitch.  The calls are reference counted so that only the first
D 13
 * on request actually has an effect, as does the final off request.
 * Results are undefined if the off and on requests are not matched.
E 13
I 13
 * "on" request actually has an effect, as does the final "off" request.
 * Results are undefined if the "off" and "on" requests are not matched.
E 13
 */
int
ifpromisc(ifp, pswitch)
	struct ifnet *ifp;
	int pswitch;
{
I 7
	struct ifreq ifr;
E 7
D 13
	/* 
E 13
I 13
	/*
E 13
	 * If the device is not configured up, we cannot put it in
	 * promiscuous mode.
	 */
	if ((ifp->if_flags & IFF_UP) == 0)
		return (ENETDOWN);

	if (pswitch) {
		if (ifp->if_pcount++ != 0)
			return (0);
		ifp->if_flags |= IFF_PROMISC;
	} else {
		if (--ifp->if_pcount > 0)
			return (0);
		ifp->if_flags &= ~IFF_PROMISC;
	}
D 7
	return ((*ifp->if_ioctl)(ifp, SIOCSIFFLAGS, (caddr_t)0));
E 7
I 7
	ifr.ifr_flags = ifp->if_flags;
	return ((*ifp->if_ioctl)(ifp, SIOCSIFFLAGS, (caddr_t)&ifr));
E 7
E 2
}
I 10
#endif
E 10

D 10
#endif (NBPFILTER > 0)
E 10
I 10
#if BSD < 199103
/*
 * Allocate some memory for bpf.  This is temporary SunOS support, and
D 13
 * is admittedly a gross hack.
E 13
I 13
 * is admittedly a hack.
E 13
 * If resources unavaiable, return 0.
 */
static caddr_t
bpf_alloc(size, canwait)
	register int size;
	register int canwait;
{
	register struct mbuf *m;

	if ((unsigned)size > (MCLBYTES-8))
		return 0;

	MGET(m, canwait, MT_DATA);
	if (m == 0)
		return 0;
	if ((unsigned)size > (MLEN-8)) {
		MCLGET(m);
		if (m->m_len != MCLBYTES) {
			m_freem(m);
			return 0;
		}
	}
	*mtod(m, struct mbuf **) = m;
	return mtod(m, caddr_t) + 8;
}
#endif
#endif
E 10
E 1
