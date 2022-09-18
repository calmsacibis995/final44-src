/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 **********************************************************************
 * HISTORY
 * $Log:	if_subr.c,v $
 * Revision 2.9  91/01/10  14:44:50  mja
 * 	Fixed bug in ether_pullup.  mbuf with full cluster would get m_off
 * 	updated such that when deallocated, mtod() would point to
 * 	wrong cluster (correct cluster +1).
 * 	[90/11/27            parker]
 * 
 * Revision 2.8  90/07/03  16:49:54  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  18:16:37  mrt]
 * 
 * Revision 2.7  89/07/11  18:20:45  jjc
 * 	Moved localetheraddr() and ether_print() to 
 * 	sunif/if_subr.c.
 * 	[88/07/12            jjc]
 * 
 * Revision 2.6  89/03/09  21:52:45  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  20:03:33  gm0w
 * 	Added new copyright and fixed includes as part of kernel cleanup.
 * 	Switched CMU conditionals to MACH.
 * 	[89/02/12            jjc]
 * 
 * Revision 2.4  88/11/22  13:01:16  rvb
 * 	Sigh, register max bound on bfffo is #31 for both compilers.
 * 	But then is swtch() wrong?
 * 	[88/11/22            rvb]
 * 
 * Revision 2.3  88/11/21  16:59:25  rvb
 * 	IF_CNTRS says whether packet statistics are kept.  For now this
 * 	is always true iff MACH is true.
 * 	MACH_DEVICE (and DLI) turns on the special hack to let the
 * 	emulation guys read and write the raw ether.
 * 	
 * 		Add counters: if_[le]{out,in} -- e is log packet size, l is size
 * 		in 8 byte multiples to 128.  in and out are measured at the
 * 		interface.  if_narp says don't count arp packets if_arp is
 * 		always the arp count.
 * 	[88/10/18            rvb]
 * 
 * Revision 2.2  88/08/24  02:19:24  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 
 *
 * 28-Feb-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Made 4.3 change to ether_attach() to enable broadcasts.
 *
 * 23-Oct-86  David Golub (dbg) at Carnegie-Mellon University
 *	Merged in further 4.3 (real release) changes.
 *
 * 12-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Upgraded to 4.3 under switch CS_GENERIC.
 *
 */
#ifndef	lint
static  char sccsid[] = "@(#)if_subr.c 1.1 86/02/03 Copyr 1985 Sun Micro";
#endif

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

#include <dli.h>
#include <mach_device.h>

#ifdef	sun4
#else	sun4
#define IF_CNTRS	MACH
#endif	sun4

/*
 * Device independent subroutines used by Ethernet device drivers.
 * Mostly this code takes care of protocols and sockets and
 * stuff.  Knows about Ethernet in general, but is ignorant of the
 * details of any particular Ethernet chip or board.
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/buf.h>
#include <sys/socket.h>
#include <sys/errno.h>
#include <sys/time.h>

#include <net/if.h>
#include <net/route.h>
#include <net/netisr.h>
#ifdef	NIT
#include <net/nit.h>
#endif
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#ifdef	MACH
#include <sunif/ether_addr.h>
#include <netinet/in_var.h>
#endif	MACH

#if	DLI
#include <net/dli_var.h>
#include <le.h>
#include <ie.h>
/*
 * Below is an unfortunate hack.  Because we are common to le and ie ether devices
 * and don't want to hack up the soft structure to contain the dlv pointer,
 * we will take advantage of the fact that we (I hope) can not have both an le and
 * ie on the same machine.
 */
struct dli_var if_dlv[NLE+NIE];
#endif	DLI

extern	struct ifnet loif;

/*
 * Interface exists: make available by filling in network interface
 * record.  System will initialize the interface when it is ready
 * to accept packets.
 * Any hardware-specific initialization is done by the caller.
 */
ether_attach(ifp, unit, name, init, ioctl, output, reset)
	register struct ifnet *ifp;
	int unit;
	char *name;
	int (*init)(), (*ioctl)(), (*output)(), (*reset)();
{

	ifp->if_unit = unit;
	ifp->if_name = name;
	ifp->if_mtu = ETHERMTU;

#ifdef	MACH
	ifp->if_flags = IFF_BROADCAST;	/* Enable broadcast here in 4.3 */
#else	MACH
	((struct sockaddr_in *)&(ifp->if_addr))->sin_family = AF_INET;
#endif	MACH
	ifp->if_init = init;
	ifp->if_ioctl = ioctl;
	ifp->if_output = output;
	ifp->if_reset = reset;
	if_attach(ifp);
}

address_known(ifp)
	struct ifnet *ifp;
{
#ifdef	MACH
	return(ifp->if_addrlist != (struct ifaddr *)0);
#else	MACH
	return (((struct sockaddr_in *)&(ifp->if_addr))->sin_addr.s_addr != 0);
#endif	MACH
}

/*
 * This is used from within an ioctl service routine to process the
 * SIOCSIFADDR request.  This should be called at interrupt priority
 * level to prevent races.
 */
#ifdef	MACH
set_if_addr(ifp, data)
	register struct ifnet *ifp;
	caddr_t data;
{
	int	error = 0;
	register struct ifaddr	*ifa = (struct ifaddr *)data;

	ifp->if_flags |= IFF_UP;
	(*ifp->if_init)(ifp->if_unit);
	switch (ifa->ifa_addr.sa_family) {
#ifdef	INET
	case AF_INET:
		((struct arpcom *)ifp)->ac_ipaddr = 
			IA_SIN(ifa)->sin_addr;
		arpwhohas((struct arpcom *)ifp,
			&IA_SIN(ifa)->sin_addr);
		break;
#endif	INET
	default:
		error = EINVAL;
	}
	return(error);
}
#else	MACH
set_if_addr(ifp, data, enaddr)
	register struct ifnet *ifp;
	caddr_t data;
	struct ether_addr *enaddr;
{
	struct sockaddr_in *sin = (struct sockaddr_in *)data;
	struct sockaddr *sa = (struct sockaddr *)data;

	if (sa->sa_family == AF_UNSPEC) {
		if (sa->sa_data[0] & 1)  /* broad or multi-cast */
			return (EINVAL);

		*enaddr = *(struct ether_addr *)sa->sa_data;
		(*ifp->if_init)(ifp->if_unit);
		return (0);
	}

	if (sin->sin_family != AF_INET)
		return (EINVAL);

	if (ifp->if_flags & IFF_RUNNING)
		if_rtinit(ifp, -1);	/* delete previous route */
	setaddr(ifp, sin);
	(*ifp->if_init)(ifp->if_unit);

	return (0);
}
#endif	MACH

/*
 * Ethernet output routine.
 * Encapsulate a packet of type family for the local net.
 * Use trailer local net encapsulation if enough data in first
 * packet leaves a multiple of 512 bytes of data in remainder.
 * If destination is this address or broadcast, send packet to
 * loop device to kludge around the fact that interfaces can't
 * talk to themselves.
 */
ether_output(ifp, m0, dst, startout, ap)
	struct ifnet *ifp;
	struct mbuf *m0;
	struct sockaddr *dst;
	int (*startout)(); /* Hardware-specific routine to start output */
	struct arpcom *ap;
{
	int type, s;
	struct ether_addr edst;
	struct in_addr idst;
	register struct mbuf *m = m0;
	register struct ether_header *header;
	register int off = 0;
	struct mbuf *mcopy = (struct mbuf *)0;		/* Null */
#ifdef	MACH
	int	usetrailers;
#endif	MACH

	if ((ifp->if_flags & (IFF_UP|IFF_RUNNING)) != (IFF_UP|IFF_RUNNING))
		return (ENETDOWN);

	switch (dst->sa_family) {

#ifdef	INET
	case AF_INET:
		idst = ((struct sockaddr_in *)dst)->sin_addr;
#ifdef	MACH
		if (!arpresolve(ap, m, &idst, &edst, &usetrailers))
#else	MACH
		if (!arpresolve(ap, m, &idst, &edst))
#endif	MACH
			return (0);	/* if not yet resolved */
		if (in_lnaof(idst) == INADDR_ANY)
			mcopy = m_copy(m, 0, M_COPYALL);
		off = ((u_short)mtod(m, struct ip *)->ip_len) - m->m_len;
#ifdef	MACH
		if (usetrailers &&
#else	MACH
		if ((ifp->if_flags & IFF_NOTRAILERS) == 0 &&
#endif	MACH
		    off > 0 && (off & 0x1ff) == 0 &&
		    m->m_off >= MMINOFF + 2 * sizeof (u_short)) {
#ifdef	MACH
			type = ETHERTYPE_TRAIL + (off>>9);
#else	MACH
			type = ETHERPUP_TRAIL + (off>>9);
#endif	MACH
			m->m_off -= 2 * sizeof (u_short);
			m->m_len += 2 * sizeof (u_short);
#ifdef	MACH
			*mtod(m, u_short *) = ETHERTYPE_IP;
#else	MACH
			*mtod(m, u_short *) = ETHERPUP_IPTYPE;
#endif	MACH
			*(mtod(m, u_short *) + 1) = m->m_len;
		} else {
#ifdef	MACH
			type = ETHERTYPE_IP;
#else	MACH
			type = ETHERPUP_IPTYPE;
#endif	MACH
			off = 0;
		}
		break;
#endif	INET

	case AF_UNSPEC:
		header = (struct ether_header *)dst->sa_data;
#ifdef	MACH
		bcopy((caddr_t)header->ether_dhost,
			(caddr_t)edst.ether_addr_octet,
			sizeof(struct ether_addr));
#else	MACH
		edst = header->ether_dhost;
#endif	MACH
		type = header->ether_type;
		break;
#if	DLI
	case AF_DLI:
#if	MACH_DEVICE
		goto pure;
#else	MACH_DEVICE
#endif	MACH_DEVICE
		break;
#endif	DLI
	default:
		identify(ifp);
		printf("can't handle AF 0x%x\n", dst->sa_family);
		m_freem(m0);
		return (EAFNOSUPPORT);
	}

	if (off) {
		/*
		 * Packet to be sent as trailer: move first packet
		 * (control information) to end of chain.
		 */
		while (m->m_next)
			m = m->m_next;
		m->m_next = m0;
		m = m0->m_next;
		m0->m_next = 0;
		m0 = m;
	}

	/*
	 * Add local net header.  If no space in first mbuf,
	 * allocate another.
	 */
	if (m->m_off > MMAXOFF ||
	    MMINOFF + sizeof (struct ether_header) > m->m_off) {
		m = m_get(M_DONTWAIT, MT_DATA);
#ifdef	DEBUG
		chkmbuf(m);
#endif	DEBUG
		if (m == 0) {
			m_freem(m0);
			identify(ifp);
			printf("WARNING: no mbufs\n");
			return (ENOBUFS);
		}
		m->m_next = m0;
		m->m_len = sizeof (struct ether_header);
	} else {
		m->m_off -= sizeof (struct ether_header);
		m->m_len += sizeof (struct ether_header);
	}
	header = mtod(m, struct ether_header *);
#ifdef	MACH
#if	DLI
	if (dst->sa_family == AF_DLI) {
		register struct ether_header *eh;
#if	MACH_DEVICE
#else	MACH_DEVICE
		eh = (struct ether_header *)dst->sa_data;
		bcopy((caddr_t)eh->ether_dhost,
			(caddr_t)edst.ether_addr_octet,
			sizeof(struct ether_addr));
#endif	MACH_DEVICE
	}
#endif	DLI
	bcopy((caddr_t)edst.ether_addr_octet, (caddr_t)header->ether_dhost,
		sizeof(struct ether_addr));
	bcopy((caddr_t)ap->ac_enaddr,
	      (caddr_t)header->ether_shost,
	      sizeof(ap->ac_enaddr));
#else	MACH
	header->ether_dhost = edst;
#endif	MACH
	header->ether_type = type;
#if	DLI
#if	MACH_DEVICE
pure:
#endif	MACH_DEVICE
#endif	DLI

	/*
	 * Queue message on interface, and start output if interface
	 * not yet active.
	 */
	s = splimp();
	if (IF_QFULL(&ifp->if_snd)) {
		IF_DROP(&ifp->if_snd);
#ifdef	DEBUG
		chkmbuf(m);
#endif	DEBUG
		m_freem(m);
		identify(ifp);
		printf("WARNING: if_snd full\n");
		(void) splx(s);
		return (ENOBUFS);
	}
	IF_ENQUEUE(&ifp->if_snd, m);
	(*startout)(ifp->if_unit);
	(void) splx(s);
	return (mcopy ? looutput(&loif, mcopy, dst) : 0);
}

#ifdef	MACH
#else	MACH
/*
 * This is called from within set_if_addr and is not used by external
 * routines.
 */
setaddr(ifp, sin)
	register struct ifnet *ifp;
	register struct sockaddr_in *sin;
{

	ifp->if_addr = *(struct sockaddr *)sin;
	ifp->if_net = in_netof(sin->sin_addr);
	ifp->if_host[0] = in_lnaof(sin->sin_addr);
	sin = (struct sockaddr_in *)&ifp->if_broadaddr;
	sin->sin_family = AF_INET;
	sin->sin_addr = if_makeaddr(ifp->if_net, INADDR_ANY);
	ifp->if_flags |= IFF_BROADCAST|IFF_NOTRAILERS;
}

/*
 * Start route and arp related stuff
 */
route_arp(ifp, ac)
	struct ifnet *ifp;
	struct arpcom *ac;
{

	if_rtinit(ifp, RTF_UP);
	(void) arpwhohas(ac, &((struct sockaddr_in *)&ifp->if_addr)->sin_addr);
}
#endif	MACH

/*
 * Prints the name of the interface, i.e. ec0.  Doing this in a
 * subroutine instead of in-line makes several error printf's
 * not have to have the name of the interface hardwire into the
 * printf format string.  Since errors should be infrequent,
 * speed is not an issue.
 */
identify(ifp)
	register struct ifnet *ifp;
{

	printf("%s%d: ",ifp->if_name, ifp->if_unit);
}

/*
 * Checks to see if the packet is a trailer packet.  If so, the
 * offset of the trailer (after the type and remaining length fields)
 * is written into offout and length is changed to reflect the length
 * of the trailer packet (minus the the type and remaining length fields).
 * If it is not a trailer packet, 0 is written into offout and length
 * is left unchanged.
 *
 * The return value is 0 if there is no error, 1 if there is an error.
 */
check_trailer(header, buffer, length, offout)
	struct ether_header *header;
	caddr_t buffer;
	int *length, *offout;
{
	register int off, resid;

	/*
	 * Deal with trailer protocol: if type is PUP trailer
	 * get true type from first 16-bit word past data.
	 * Remember that type was trailer by setting off.
	 */
	*offout = 0;
	off = 0;
#ifdef	MACH
	if (header->ether_type >= ETHERTYPE_TRAIL &&
	    header->ether_type < ETHERTYPE_TRAIL+ETHERTYPE_NTRAILER)
		off = (header->ether_type - ETHERTYPE_TRAIL) << 9;
#else	/* MACH */
	if (header->ether_type >= ETHERPUP_TRAIL &&
	    header->ether_type < ETHERPUP_TRAIL+ETHERPUP_NTRAILER)
		off = (header->ether_type - ETHERPUP_TRAIL) << 9;
#endif	/* MACH */
	if (off == 0)
		return(0);
	if (off >= ETHERMTU)
		return (1);		/* sanity */
	header->ether_type = *(u_short *)((char *)(buffer + off));
	resid = *(u_short *)((char *)(buffer+off+2));
	/*
	 * Can  off + resid  ever be  < length?  If not,
	 * the test should be for  !=  instead of  >, and
	 * *length could be left alone.
	 */
	if (off + resid > *length)
		return (1);		/* sanity */

	/*
	 * Off is now the offset to the start of the
	 * trailer portion, which includes 2 shorts that were
	 * added.  The 2 shorts will be removed by copy_to_mbufs.
	 * The 2 extra shorts contain the real type field and the
	 * length of the trailer.
	 */
	*length = sizeof (struct ether_header) + off + resid;
	*offout = off;
	return (0);
}

#ifdef	IF_CNTRS
int if_narp = 1, if_arp = 0;
int if_ein[32], if_eout[32]; 
int if_lin[128/8], if_lout[128/8]; 

if_log_2(i)
{
	register int no = i;
	register int ans;

#ifdef	__GNU__
	asm("bfffo %1{#0,#31}, %0" : "=g" (ans) : "g" (i));
#else	__GNU__
	asm("bfffo d7{#0:#31}, d6");
#endif	__GNU__
	return (31-ans);
}
#endif	IF_CNTRS

#if	MACH_DEVICE
extern char dli_from[6];
extern char dli_all[6];
extern int dli_active;
#endif	MACH_DEVICE

do_protocol(header, m, ap, wirelen)
	struct ether_header *header;
	struct mbuf *m;
	struct arpcom * ap;
	int wirelen;
{
	register struct ifqueue *inq;
#ifdef	NIT
	struct nit_ii nii;

	nii.nii_header = (caddr_t)header;
	nii.nii_hdrlen = sizeof (*header);
	nii.nii_type = header->ether_type;
	nii.nii_datalen = wirelen;
	nii.nii_promisc =
	    bcmp((caddr_t)&header->ether_dhost, (caddr_t)&ap->ac_enaddr,
	        sizeof (struct ether_addr)) != 0 &&
	    bcmp((caddr_t)&header->ether_dhost, (caddr_t)&etherbroadcastaddr,
	        sizeof (struct ether_addr)) != 0;
	nit_tap(&ap->ac_if, m, &nii);
	if (nii.nii_promisc) {
		m_freem(m);
		return;
	}
#endif	NIT

#if	DLI
#if	MACH_DEVICE
	if ( (dli_active && !bcmp(header->ether_shost, dli_from, 6)) ||
	     (dli_active && !bcmp(dli_from, dli_all, 6))) {

		dli_input(m, header->ether_type, &header->ether_shost[0], 
 			  &if_dlv[ap->ac_if.if_unit], header);
		return;
	}
#endif	MACH_DEVICE
#endif	DLI
	switch (header->ether_type) {

#ifdef	INET
#ifdef	MACH
	case ETHERTYPE_IP:
#else	MACH
	case ETHERPUP_IPTYPE:
#endif	MACH
#ifdef	DEBUG
#if	1
		dumpbuffer(header, (caddr_t)&header[1]);
#else	1
		printf(" IP ");
#ifdef	notdef
		dumpbuffer(header, (caddr_t)&header[1]);
#endif	notdef
#endif	1
#endif	DEBUG

#ifdef	IP_ENADDR
		arpipin(header, m);
#endif	IP_ENADDR
		schednetisr(NETISR_IP);
		inq = &ipintrq;
		break;

#ifdef	MACH
	case ETHERTYPE_ARP:
#else	MACH
	case ETHERPUP_ARPTYPE:
#endif	MACH
/*
#ifdef	DEBUG
		printf(" ARP ");
#endif	DEBUG
*/
		arpinput(ap, m);
#ifdef	IF_CNTRS
		if_arp++;
		if (if_narp) {int l = wirelen;
			      extern int if_log_2();
			if_ein[if_log_2(l)]--;
			if (l < 128) if_lin[l>>3]--;
		}
#endif	IF_CNTRS
		return;

#ifdef	REVARP
	case ETHERPUP_REVARPTYPE:
		revarpinput(ap, m);
		return;
#endif	REVARP

#endif	INET
	default:
/*
#ifdef	DEBUG
		printf(" BOGUS ");
#endif	DEBUG
*/
#if	DLI
#if	MACH_DEVICE
		m_freem(m);
#else	MACH_DEVICE
		dli_input(m, header->ether_type, &header->ether_shost[0], 
 			  &if_dlv[ap->ac_if.if_unit], header);
#endif	MACH_DEVICE
#else	DLI
		m_freem(m);
#endif	DLI
		return;
	}

	if (IF_QFULL(inq)) {
#ifdef	DEBUG
		printf(" QFULL ");
#endif	DEBUG
		IF_DROP(inq);
		m_freem(m);
		return;
	}
	IF_ENQUEUE(inq, m);
/*
#ifdef	DEBUG
	printf(")");
#endif	DEBUG
*/
}

/*
 * Routine to copy from an buffer belonging to an interface into mbufs.
 *
 * The buffer consists of a header and a body.  In the normal case,
 * the buffer starts with the header, which is followed immediately
 * by the body.  However, the buffer may contain a trailer packet.
 * In this case, the body appears first and is followed by an expanded
 * header that starts with two additional shorts (containing a type and
 * a header length) and finishes with a header identical in format to
 * that of the normal case.
 *
 * These cases are distinguished by off0, which is the offset to the
 * start of the header part of the buffer.  If nonzero, then we have a
 * trailer packet and must start copying from the beginning of the
 * header as adjusted to skip over its extra leading fields.  Totlen is
 * the overall length of the buffer, including the contribution (if any)
 * of the extra fields in the trailing header.
 */
#ifdef	MACH
/*
 *	4.3 change:
 *	Prepend a pointer to the interface structure, so that protocols
 *	can determine where incoming packets arrived.
 */
struct mbuf *
copy_to_mbufs(buffer, totlen, off0, ifp)
	caddr_t	buffer;
	int	totlen, off0;
	struct ifnet	*ifp;
#else	MACH
struct mbuf *
copy_to_mbufs(buffer, totlen, off0)
	caddr_t buffer;
	int totlen, off0;
#endif	MACH
{
	register caddr_t	cp = buffer;
	caddr_t			cplim = cp + totlen;
	register int		len;
	register struct mbuf	*m;
	struct mbuf		*top = (struct mbuf *) 0,
				**mp = &top;
	if (off0) {
		/*
		 * Trailer: adjust starting positions and lengths
		 * to start of header.
		 */
		cp += off0 + 2 * sizeof (short);
		totlen -= 2 * sizeof (short);
	}

	while (totlen > 0) {
		MGET(m, M_DONTWAIT, MT_DATA);
		if (m == (struct mbuf *) 0) {
			m_freem(top);
			return ((struct mbuf *) 0);
		}

		/*
		 * If the copy has proceeded past the end of buffer,
		 * move back to the start.  This occurs when the copy
		 * of the header portion of a trailer packet completes.
		 */
		if (cp >= cplim) {
			cp = buffer;
			cplim = cp + off0;
		}

		/*
		 * Get length for the next mbuf of the chain,
		 * allocating a cluster mbuf if the remaining
		 * length justifies it.
		 */
		len = cplim - cp;
#ifdef	MACH
		m->m_len = MLEN;
		/*
		 *	Allocate an mbuf page if too much data.
		 */
		if (len > CLBYTES) {		/* XXX too big for SUN */
			MCLGET(m);
		}

		if (ifp) {
			/*
			 *	leave room for ifp.
			 */
			m->m_len = MIN(m->m_len - sizeof(ifp), len);
			m->m_off += sizeof(ifp);
		}
		else
			m->m_len = MIN(m->m_len, len);
#else	MACH
		if (len < MCLBYTES || mclget(m) == 0)
			m->m_len = MIN(MLEN, len);
#endif	MACH
		len = m->m_len;
		bcopy(cp, mtod(m, caddr_t), (u_int) len);
		cp += len;
		totlen -= len;

		*mp = m;
		mp = &m->m_next;
#ifdef	MACH
		if (ifp) {
			/*
			 *	Prepend interface pointer to first mbuf.
			 */
			m->m_len += sizeof(ifp);
			m->m_off -= sizeof(ifp);
			*(mtod(m, struct ifnet **)) = ifp;
			ifp = (struct ifnet *)0;
		}
#endif	MACH
	}
	
	return (top);
}

/*
 * Routine to copy from mbuf chain to a transmit buffer.
 * Returns the number of bytes copied
 */
copy_from_mbufs(buffer, m)
	register u_char *buffer;
	struct mbuf *m;
{
	register struct mbuf *mp;
	register int off;

	for (off = 0, mp = m; mp; mp = mp->m_next) {
		register u_int len = mp->m_len;
		u_char *mcp;

		if (len != 0) {
			mcp = mtod(mp, u_char *);
			bcopy((caddr_t)mcp, (caddr_t)buffer, len);
			off += len;
			buffer += len;
		}
	}
	m_freem(m);
	return (off);
}

/*
 * Routine to copy from Multibus memory into mbufs.
 *
 * This is how easy it would be if we didn't have to worry about trailers
 */
#ifdef	notdef
struct mbuf *
copy_to_mbufs_no_trailers(buffer, totlen)
	u_char *buffer;
	int totlen;
{
	register struct mbuf *m;
	struct mbuf *top = 0, **mp = &top;
	register int len;
	u_char *cp;

	for (cp = buffer; totlen; cp += len, totlen -= len) {
		MGET(m, M_DONTWAIT, MT_DATA);
		if (m == 0) {
			m_freem(top);
			return (0);
		}
		len = totlen;
		if (len < MCLBYTES || mclget(m) == 0) {
			m->m_len =  MIN(MLEN, len);
			m->m_off = MMINOFF;
		}
		len = m->m_len;
		bcopy((caddr_t)cp, mtod(m,caddr_t), (u_int)len);
		*mp = m;
		mp = &m->m_next;
	}
	return (top);
}
#endif	notdef

/*
 * A close relative of m_pullup, differing from it in that:
 *    -	It is not an error for the aggregate length of the subject
 *	mbuf chain to be less than the length requested.
 *    -	Where possible (and convenient), it avoids allocating a
 *	fresh mbuf, instead using the first mbuf of the subject chain.
 *    -	It guarantees that the first mbuf of the resulting chain
 *	has its data portion start at MMINOFF, so that its entire
 *	buffer area is available.
 */
struct mbuf *
ether_pullup(m0, len)
	struct mbuf *m0;
	register int len;
{
	register struct mbuf *m, *n;
	register int count;

	n = m0;
	if (len > MLEN)
		goto bad;
	/*
	 * See whether we can optimize by avoiding mbuf allocation.
	 */
	if (n->m_off == MMINOFF) {
		m = n;
		n = n->m_next;
		if (m->m_len >= len || ! n)
			return (m);
		len -= m->m_len;
	}
	else {
		MGET(m, M_DONTWAIT, n->m_type);
		if (m == 0)
			goto bad;
		m->m_len = 0;
	}
	/*
	 * M names the mbuf we're filling.  N moves through
	 * the mbufs that are drained into m.
	 */
	do {
		count = MIN(MLEN - m->m_len, len);
		if (count > n->m_len)
			count = n->m_len;
		if (count > 0) {
			bcopy(mtod(n, caddr_t), mtod(m, caddr_t)+m->m_len,
			  (unsigned)count);
			len -= count;
			m->m_len += count;
			n->m_len -= count;
		}
		if (n->m_len > 0) {
			n->m_off += count;
			break;
		}
		n = m_free(n);
	} while (n);
	m->m_next = n;
	return (m);
bad:
	m_freem(n);
	return ((struct mbuf *) 0);
}

#if	MACH
localetheraddr(hint, result)
	struct ether_addr *hint, *result;
{
	static int found = 0;
	static struct ether_addr addr;

	if (!found) {
		found = 1;
		if (hint == NULL)
			return (0);
		addr = *hint;
		printf("Ethernet address = ");
		ether_print(&addr);
	}
	if (result != NULL)
		*result = addr;
	return (1);
}

ether_print(ea)
	struct ether_addr *ea;
{
	u_char *cp = &ea->ether_addr_octet[0];

	printf("%x:%x:%x:%x:%x:%x\n", cp[0], cp[1], cp[2], cp[3], cp[4], cp[5]);
}
#endif	MACH

#ifdef	DEBUG
dumpbuffer(header, buffer)
	struct ether_header *header;
	caddr_t buffer;
{
	int i, j;
	short *buf = (short *)buffer;
	int length = buf[1];  /* Specific to IP packets */

	length /= 2;  /* convert to words */
	if (length > 48)
		length = 48;

#ifdef	MACH
	if (header->ether_dhost[0] != 0xff)
#else	MACH
	if (header->ether_dhost.ether_addr_octet[0] != 0xff)
#endif	MACH
	{
		printf("\nSource: ");
		for (i = 0; i < 6; i++)
			printf("%x ",
#ifdef	MACH
			    header->ether_shost[i]&0xff);
#else	MACH
			    header->ether_shost.ether_addr_octet[i]&0xff);
#endif	MACH
		printf("\nDestin: ");
		for (i = 0; i < 6; i++)
			printf("%x ",
#ifdef	MACH
			    header->ether_dhost[i]&0xff);
#else	MACH
			    header->ether_dhost.ether_addr_octet[i]&0xff);
#endif	MACH
		printf("\nBuffer");
		j = 0;
		for (i = 0; i < length; i++) {
			if (j == 0)
				printf("\n");
			if (++j == 16)
				j = 0;
			printf("%x ", buf[i]&0xffff);
		}
		printf("\n");
	} else
		printf(" Broadcast ");
}

chkmbuf()
{
}
#endif	DEBUG
