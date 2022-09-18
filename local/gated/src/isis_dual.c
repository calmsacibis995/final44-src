/*
 *  isis_dual.c,v 1.11 1993/01/07 22:39:14 jch Exp
 */

/* Gated Release 3.0 */
/* Copyright (c) 1990, 1991, 1992 by Cornell University. All rights reserved. */
/* Refer to Particulars and other Copyright notices at the end of this file. */


#include "include.h"
#include "isis_includes.h"

/*
*	associates an ip address with a circuit entry structure.
*	may be called multiple times, although multiple calls setting
*	the same value ipaddr are ignored.
*
*	This will effect the LSPs that the system generates, although
*	a change instigated here will NOT cause an LSP to be regenerated.
*	(it would basically have to make every lsp numbered zero - pseudo
*	and non pseudonode alike to be rebuilt).
*/
void
addIPAddr __PF2(c, CircuitEntry *,
		ipaddr, struct in_addr)
{
    if (c->ipAddrs.cnt >= MAXIPADDRS) {
	trace_log_tf(isis_trace_options,
		     0,
		     LOG_ERR,
		     ("%s: too many addresses configured",
		      c->name));
    } else {
	c->ipAddrs.addrs[c->ipAddrs.cnt++] = ipaddr;
	buildIPAddrOption();
    }
}

/* DUAL: insert the protocols supported option */
/* if prepend is true, then add the code and length field */
u_char *
insertProtoSup __PF2(
	    bp, u_char *,
	    prepend, Boolean)
{
	if (prepend) {
		*bp++ = ProtoSupportedCode;
		*bp++ = ip_supported + clnp_supported;	/* IP and OSI */
	}
	if (clnp_supported) *bp++ = OSI_NLPID;
	if (ip_supported) *bp++ = IP_NLPID;
	return(bp);
}

/* DUAL: insert the IP interface address option */
/* if prepend is true, then add the code and length field */
u_char *
insertIPaddr __PF3(
	    c, CircuitEntry *,
	    bp, u_char *,
	    prepend, Boolean)
{
    if (c->ipAddrs.cnt) {
	int	i;

	if (prepend) {
	    *bp++ = IPIfAddrCode;
	    *bp++ = sizeof(struct in_addr) * c->ipAddrs.cnt;
	}

	for (i=0; i<c->ipAddrs.cnt; i++) {
	    bcopy((caddr_t)&c->ipAddrs.addrs[i], (caddr_t) bp, sizeof(struct in_addr));
	    bp += sizeof(struct in_addr);
	}
    }
    return(bp);
}


prefIP *
setIPReachable __PF6(
	    level, int,
	    code, u_char,
	    metrics, MetricList,
	    addr, struct in_addr,
	    mask, struct in_addr, 
	    path, as_path *)
{
    prefIP *p = 0;

    if (!(level == 1 || level == 2)) {
	trace_log_tf(isis_trace_options,
		     0,
		     LOG_ERR,
		     ("setIPReachable: bad level %d",
		      level));
	return(p);
    }

    switch(code) {
    case IPIntReachCode:
	metrics.defalt &= 0x3f; 	/* clear I/E bit */
	if (level == 1)
	    p = addIPReachToLSP(L1LSP, metrics, addr, mask, code, path);
	else
	    p = addIPReachToLSP(L2LSP, metrics, addr, mask, code, path);
	break;

    case IPExtReachCode:
	if (level != 2) {
	    trace_log_tf(isis_trace_options,
			 0,
			 LOG_ERR,
			 ("setIPReachable: IPExtReachCode level must be 2"));
	    return(p);
	}
	metrics.defalt |= 0x40; 	/* set I/E bit */
	p = addIPReachToLSP(L2LSP, metrics, addr, mask, code, path);
	break;
	
    default:
	trace_log_tf(isis_trace_options,
		     0,
		     LOG_ERR,
		     ("setIPReachable: bad code %d",
		      code));
	break;
    }
    return(p);
}

void 
clearIPReachable __PF3( level, int,
	    		code, u_char,
			p, prefIP *)
{
    if (!(level == 1 || level == 2)) {
	trace_log_tf(isis_trace_options,
		     0,
		     LOG_ERR,
		     ("clearIPReachable: bad level %d",
		      level));
	return;
    }

    switch(code) {
    case IPIntReachCode:
	delIPReach(p);
	break;
    case IPExtReachCode:
	if (level != 2) {
	    trace_log_tf(isis_trace_options,
			 0,
			 LOG_ERR,
			 ("clearIPReachable: IPExtReachCode level must be 2"));
	    return;
	}
	delIPReach(p);
	break;
    default:
	trace_log_tf(isis_trace_options,
		     0,
		     LOG_ERR,
		     ("clearIPReachable: bad code %d",
		      code));
	break;
    }
}


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
