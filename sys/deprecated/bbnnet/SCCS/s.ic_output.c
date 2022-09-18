h49685
s 00030/00005/00243
d D 1.5 85/12/27 12:42:25 lam 5 4
c Added ping_addr() to take care of case of ping from ic_timeo().
e
s 00000/00005/00248
d D 1.4 85/12/27 09:04:19 lam 4 3
c 
e
s 00008/00000/00245
d D 1.3 85/12/05 10:15:35 lam 3 2
c Commented out performance hack which caused concurrency bug
c in icmp_addr() :  global variable inetifp may not always be set when 
c icmp_addr() is called.  (For example, not set when called via ic_timeo())
e
s 00001/00001/00244
d D 1.2 85/10/15 09:28:19 karels 2 1
c update syslog
e
s 00245/00000/00000
d D 1.1 85/10/14 18:13:45 karels 1 0
c from BBN
e
u
U
t
T
I 1
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/mbuf.h"
#include "../h/socket.h"
#include "../h/socketvar.h"
#include "../h/protosw.h"
#include "../h/syslog.h"

#include "../net/if.h"
#include "../net/route.h"

#include "../bbnnet/in.h"
#include "../bbnnet/net.h"
#include "../bbnnet/in_pcb.h"
#include "../bbnnet/in_var.h"
#include "../bbnnet/ip.h"
#include "../bbnnet/icmp.h"
#include "../bbnnet/nopcb.h"

extern struct ifnet *inetifp;

/*
 * We are generating an ICMP error message in response to this packet sent
 * to us.  Too bad the device driver doesn't pair a pointer to its ifnet with
 * the incoming packet.  That would save us a search, and we could use that
 * for our source address in the ICMP error message.
 *
 * Pick a source address for that ICMP error message we send.  We can't
 * always use ip_dst of the original for the ip_src of the ICMP error
 * message since the packet may have been broadcast.
 *
 * We try to establish a proper interface to respond by in case we're
 * multi-homed.  Try to respond by interface received on rather than
 * interface that represents most direct route back.
 */
struct in_addr icmp_addr (ip)
struct ip	*ip;
{
    struct in_ifaddr *ia;

I 3
D 5
/*
E 5
E 3
#ifdef bsd42
I 3
D 5
*/
E 5
E 3
    /* don't want broadcasts to match */
    if (! (ia = in_iawithaddr(ip->ip_dst, FALSE)))
    {
	/* hmm, try for the net... */
	if ((ia = in_iawithnet(ip->ip_dst)) == NULL)
	{
	    struct in_addr l;

	    /*
	     * The message will be sent by ip_send() who will
	     * route the message and discover that a local address
	     * should be set on the basis of the route used.
	     */
	    l.s_addr = INADDR_ANY;
	    return (l);
	}
    }
I 3
D 5
/*
E 5
E 3
#endif
    ia = in_iafromif(inetifp);
I 3
D 5
*/
E 5
E 3
    return (IA_INADDR(ia));
}

I 5



struct in_addr ping_addr (ip)
struct ip	*ip;
{
    struct in_ifaddr *ia;

    /* don't want broadcasts to match */
    if (! (ia = in_iawithaddr(ip->ip_dst, FALSE)))
    {
	/* hmm, try for the net... */
	if ((ia = in_iawithnet(ip->ip_dst)) == NULL)
	{
	    struct in_addr l;

	    /*
	     * The message will be sent by ip_send() who will
	     * route the message and discover that a local address
	     * should be set on the basis of the route used.
	     */
	    l.s_addr = INADDR_ANY;
	    return (l);
	}
    }
    return (IA_INADDR(ia));
}

E 5
/*
 * notes to above mostly apply
 *
 * icmp_addr() sort of assumes the packet was addressed to us.  But when we
 * act as a getway, S sends to A1, and we use A2 to get to D.  We want to
 * reply with the A1 address, not the A2 address.
 */
struct in_addr redir_addr (ip)
struct ip	*ip;
{
    register struct in_ifaddr *ia;

I 3
D 4
/*
E 4
E 3
#ifdef bsd42
I 3
D 4
*/
E 4
E 3
    /* note we use ip_src, not ip_dst here */
    if ((ia = in_iawithnet(ip->ip_src)) == NULL)
    {
	struct in_addr l;

	l.s_addr = INADDR_ANY;
	return (l);
    }
I 5
#endif
E 5
I 3
D 4
/*
E 3
#endif
E 4
    ia = in_iafromif(inetifp);
I 3
D 4
*/
E 4
E 3
    return (IA_INADDR(ia));
}

/*
 * There are a few icmp output routines since the header has some variable
 * types in it ...
 */
send_redirect (redirip, use, code, icmplen)
struct ip	*redirip;
struct in_addr	 use;
unsigned icmplen;
{
    register struct mbuf	*m;
    int error;

    if (m = m_get(M_DONTWAIT, MT_HEADER)) 
    {
	m->m_len = ICMPSIZE + icmplen;
	m->m_off = MMAXOFF - m->m_len;
	{
	register struct icmp	*ic;

	ic = mtod(m, struct icmp *);
	ic->ic_type = ICMP_REDIR;
	ic->ic_code = code;
	ic->ic_sum = 0;
	ic->ic_gaddr = use;
	if (icmplen > 0)
	    bcopy ((caddr_t)redirip, ic->ic_data, icmplen);

	/* used to use an inline cksum here  */
	ic->ic_sum = in_cksum (m, m->m_len);
	}

	m->m_off -= sizeof(struct ip);
	m->m_len += sizeof(struct ip);
	{
	register struct ip	*ip;

	ip = mtod(m, struct ip *);
	ip->ip_p = IPPROTO_ICMP;
	ip->ip_tos = 0;
	ip->ip_dst = redirip->ip_src;
	ip->ip_src = redir_addr(redirip);
	}
	NOPCB_IPSEND (m, (int)icmplen, FALSE, error);

#ifdef lint
	error = error ;
#endif
    }
}

/*
 * Send an ICMP error message.  Note that data must not exceed single mbuf.
 */
ic_errmsg (src, dst, type, code, off, dlen, dp)
struct in_addr	 src;
struct in_addr  dst;
unsigned dlen;
caddr_t dp;	/* assumed to be contiguous */
{
    register struct mbuf	*m;
    register unsigned	 len;
    int error;

    if ((m = m_get(M_DONTWAIT, MT_HEADER)) == NULL)
	return /*ENOBUFS*/;

    /*
     * Build ICMP header
     */
    len = ICMPSIZE + dlen;
    m->m_off = MMAXOFF - len;
    if (m->m_off < (MMINOFF + sizeof(struct ip))) 
    {
D 2
	log (KERN_RECOV, "ic_errmsg len %d", len);
E 2
I 2
	log (LOG_INFO, "ic_errmsg len %d", len);
E 2
	m_free (m);
	return;
    }
    m->m_len = len;

    /* ICMP header */
    {
	register struct icmp	*ic;

	ic = mtod(m, struct icmp *);
	ic->ic_type	= type;
	ic->ic_code	= code;
	ic->ic_off	= off;
	if (dlen > 0)
	    bcopy(dp, ic->ic_data, dlen);
	ic->ic_sum	= 0;
	ic->ic_sum	= in_cksum(m, len);
    }

    /* IP header */
    {
	register struct ip	*ip;

	m->m_off -= sizeof(struct ip);
	m->m_len += sizeof(struct ip);
	ip = mtod(m, struct ip *);
	ip->ip_p	= IPPROTO_ICMP;
	ip->ip_tos	= 0;
	ip->ip_src	= src;
	ip->ip_dst	= dst;
    }

    NOPCB_IPSEND (m, (int)len, FALSE, error);

#ifdef lint
    error = error;
#endif
}

#ifdef BBNPING
ping(gwaddr)
struct in_addr gwaddr;
{
    register struct mbuf *m;

    if ((m = m_get(M_DONTWAIT, MT_HEADER)) == NULL)
	return;
    m->m_off = MMAXOFF - ICMPSIZE;
    m->m_len = ICMPSIZE;
    {
	register struct icmp *ic;

	ic = mtod (m, struct icmp *);
	ic->ic_type	= ICMP_ECHO;
	ic->ic_code	= 0;
	ic->ic_id	= MY_ECHO_ID;
	ic->ic_sum	= 0;
	ic->ic_sum	= in_cksum(m, ICMPSIZE);
    }

    m->m_off -= sizeof(struct ip);
    m->m_len += sizeof(struct ip);
    {
	register struct ip *ip;

	ip = mtod(m, struct ip *);
	ip->ip_p	= IPPROTO_ICMP;
	ip->ip_tos	= 0;
	ip->ip_dst	= gwaddr;
D 5
	ip->ip_src	= icmp_addr (ip);
E 5
I 5
	ip->ip_src	= ping_addr (ip);
E 5
    }

    {
	register int error;

	NOPCB_IPSEND (m, ICMPSIZE, FALSE, error);
#ifdef lint
	error = error;
#endif
    }
}
#endif
E 1
