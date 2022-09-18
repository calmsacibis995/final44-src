/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vmtp_debug.c,v $
 * Revision 2.3  89/03/09  20:48:08  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:03:15  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Updated from new VMTP sources from Stanford (June 87).
 *
 * 29-May-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources.
 *
 */
 
#include <mach_vmtp.h>

/*
 * $ Header: vmtp_debug.c,v 2.1 87/08/14 15:43:09 mrt Exp $
 */

/*
 * 	vmtp_debug.c	0.1	10/19/86
 *	Written by Joyo Wijaya and Erik Nordmark
 */

#if	MACH_VMTP

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>

#include <net/if.h>
#include <net/route.h>

#include "in.h"
#include "in_pcb.h"
#include "in_systm.h"
#include "ip.h"
#include "ip_var.h"
#include "vmtp_so.h"
#include "vmtp.h"
#include "vmtp_ip.h"
#include "vmtp_var.h"
#include "vmtp_group.h"

/*
 * VMTP dump vmtp eid routine.
 */
vmtp_dumpeid(x, n, m)
	register struct vmtpeid *x;
	char	*n, *m;
{
	printf("%s: struct vmtpeid %s: ", m, n);
	if (x) {
		printf("%x:%x:%x\n", getve_flags(*x),	getve_tmstamp(*x), 
			x->ve_inaddr);
	} else
		printf("NULL\n");
} /* vmtp_dumpeid */

/*
 * VMTP dump vmtp ucb routine.
 */
vmtp_dumpucb(x, n, m)
	register struct vmtpucb *x;
	char	*n, *m;
{
	int i;

	printf("%s: struct vmtpucb %s: ", m, n);
	if (x) {
		printf("\n\tvu_code = 0x%x ", x->vu_code);
		printf("vu_dlvrmsk = 0x%x ", x->vu_dlvrmsk);
		printf("vu_segsize = %d\n", x->vu_segsize);
		printf("\tvu_data = ");
		for (i = 0; i < 5; i++)
			printf("0x%x ", x->vu_longdata[i]);
		printf("\n");
	} else
		printf("NULL\n");
} /* vmtp_dumpucb */

/*
 * VMTP dump vmtp mcb routine.
 */
vmtp_dumpmcb(x, n, m)
	register struct vmtpmcb *x;
	char	*n, *m;
{
	int i;

	printf("%s: struct vmtpmcb %s: ", m, n);
	if (x) {
		printf("\n");
		vmtp_dumpeid(&x->vm_eid, "vm_eid", n);
		vmtp_dumpucb(&x->vm_ucb, "vm_ucb", n);
	} else
		printf("NULL\n");
} /* vmtp_dumpmcb */

/*
 * VMTP dump vmtp_header
 */
vmtp_dumpvh(x, n, m)
	register struct vmtp_header *x;
	char	*n, *m;
{
	int i;

	printf("%s: struct vmtp_header %s: ", m, n);
	if (x) {
	    	printf("\n\tvh_ifp = 0x%x ", (u_long)x->vh_ifp);
		printf("vh_addr.va_type = %d ", x->vh_addr.va_type);
		if (x->vh_addr.va_type == VAT_INET)
			printf("va_inet = 0x%x\n", x->vh_addr.va_inet);
		else
			printf("va_ether = %s\n", 
				ether_sprintf(x->vh_addr.va_ether));
		printf("\tvh_type = 0x%x ", x->vh_type);
		printf("vh_len = %d ", x->vh_len);
		printf("vh_ttl = %d\n", x->vh_ttl);
	} else
		printf("NULL\n");
} /* vmtp_dumpvh */

/*
 * VMTP dump vmtp-ip packet header routine.
 */
vmtp_dumpvi(x, n, m)
	register struct vmtpiphdr *x;
	char	*n, *m;
{
	int i;

	printf("%s: struct vmtpiphdr %s: ", m, n);
	if (x) {
	    	printf("\n\tvi_ifp = 0x%x ", (u_long)x->vi_ifp);
		printf("vi_addr.va_type = %d ", x->vi_addr.va_type);
		if (x->vi_addr.va_type == VAT_INET)
			printf("va_inet = 0x%x\n", x->vi_addr.va_inet);
		else
			printf("va_ether = %s\n", 
				ether_sprintf(x->vi_addr.va_ether));
		printf("\tvi_type = 0x%x ", x->vi_type);
		printf("vi_len = %d ", x->vi_len);
		printf("vi_ttl = %d\n", x->vi_ttl);
		printf("\tvi_client = %x:%x:%x\n", getve_flags(x->vi_client),
			getve_tmstamp(x->vi_client), x->vi_client.ve_inaddr);
		printf("\n\tvi_server = %x:%x:%x\n", getve_flags(x->vi_server),
			getve_tmstamp(x->vi_server), x->vi_server.ve_inaddr);
		printf("\tvi_fnctcode = 0%o ", 07 & getvi_fnctcode(x));
		printf("0%o ", 077 & getvi_inpktgap(x));
		printf("0%o ", 07 & getvi_priority(x));
		printf("vi_control = 0x%x ", 0xfff & getvi_control(x));
		printf("0x%x ", 0xff & getvi_domain(x));
		printf("0%o\n", 07 & getvi_version(x));
		printf("\tvi_transid = 0x%x ", x->vi_transid);
		printf("vi_dlvrmsk = 0x%x\n", x->vi_dlvrmsk);
		printf("\tvi_code = 0x%x ", x->vi_code);
		printf("vi_usrdlvrmsk = 0x%x ", x->vi_usrdlvrmsk);
		printf("vi_segsize = %d\n", x->vi_segsize);
		printf("\tvi_data = ");
		for (i = 0; i < 5; i++)
			printf("0x%x ", x->vi_vmtp.vh_ucb.vu_longdata[i]);
		printf("\n");
	} else
		printf("NULL\n");
} /* vmtp_dumpvi */

/*
 * VMTP dump vmtp csr routine.
 */
vmtp_dumpcsr(x, n, m)
	register struct vmtpcsr *x;
	char	*n, *m;
{
	printf("%s: struct vmtpcsr %s: ", m, n);
	if (x) {
		printf("\n");
		vmtp_dumpvi(x->vc_vihdr, "vc_vihdr", n);
		printf("\tvc_next = %d ", x->vc_next);
		printf("vc_state = %d ", x->vc_state);
		printf("vc_rexmtcnt = %d ", x->vc_rexmtcnt);
		printf("vc_tleft = %d\n", x->vc_tleft);
		printf("\tvc_qnext = 0x%x ", x->vc_qnext);
		printf("vc_qprev = 0x%x ", x->vc_qprev);
		printf("vc_qhead = 0x%x\n", x->vc_qhead);		
		printf("\tvc_txmsk = 0x%x\n", x->vc_txmsk);
	} else
		printf("NULL\n");
} /* vmtp_dumpcsr */

vmtp_dumpcsrs(csr, n, m)
	struct vmtpcsr *csr;
	char	*n, *m;
{
	while (csr) {
		vmtp_dumpcsr(csr, n, m);
		csr = csr->vc_next;
	}
} /* vmtp_dumpcsrs */

/*
 * VMTP dump vmtp ser routine.
 */
vmtp_dumpser(x,n,m)
	register struct vmtpser *x;
	char	*n, *m;
{
	printf("%s: struct vmtpser %s: ", m, n);
	if (x) {
		printf("\n");
		printf("\tvs_server = %x:%x:%x\n", getve_flags(x->vs_server),
			getve_tmstamp(x->vs_server), x->vs_server.ve_inaddr);
		printf("\tvs_next = 0x%x ", (u_long)x->vs_next);
		printf("vs_flags = 0x%x\n ", 0xffff & x->vs_flags);
		printf("\tvs_chead = 0x%x ", (u_long)x->vs_chead);
		printf("vs_cnext = 0x%x ", (u_long)x->vs_cnext);
		printf("vs_ctail = 0x%x\n", (u_long)x->vs_ctail);
		printf("\tvs_type = %d\n", 0xffff & x->vs_type);
	} else
		printf("NULL\n");
} /* vmtp_dumpser */

vmtp_dumpsers(ser, n, m)
	struct vmtpser *ser;
	char	*n, *m;
{
	while (ser) {
		vmtp_dumpser(ser, n, m);
		ser = ser->vs_next;
	}
} /* vmtp_dumpsers */
	
/*
 * VMTP dump vmtp sermap routine.
 */
vmtp_dumpvservermap(m)
	char *m;
{
	int i;
	char n[20];

	printf("%s: VMTP SERVER MAP\n", m);
	for (i = 0; i < VMTP_HASHMAPSIZE; i++) {
		if (vservermap[i] != NULL) {
			printf("vservermap[%d]:", i);
			vmtp_dumpsers(vservermap[i], "", "");
		}
		else {
			if (vservermap[i+1] != NULL) {
				printf("vservermap[%d]: NULL\n", i);
			}
			else {
				printf("vservermap[%d:", i);
				while (vservermap[i+1] == NULL
				      && i+1<VMTP_HASHMAPSIZE)
					i++;
				printf("%d]: NULL\n", i);
			}
		}
	}
} /* vmtp_dumpvservermap */

/*
 * VMTP dump vmtp local csr map routine.
 */
vmtp_dumplocalmap(m)
	char *m;
{
	int i;
	char n[20];

	printf("%s: VMTP LOCAL CSR MAP\n", m);
	for (i = 0; i < VMTP_HASHMAPSIZE; i++) {
		if (vlocalcsrmap[i] != NULL) {
			printf("vlocalcsrmap[%d]\n", i);
			vmtp_dumpcsrs(vlocalcsrmap[i], "vlocalcsrmap[]", "");
		} else {
			if (vlocalcsrmap[i+1] != NULL) {
				printf("struct vmtpcsr:\n");
				printf("\tvlocalcsrmap[%d] = NULL\n", i);
			} else {
				printf("\tvlocalcsrmap[%d:", i);
				while (vlocalcsrmap[i+1] == NULL
				      && i+1<VMTP_HASHMAPSIZE)
					i++;
				printf("%d] = NULL\n", i);
			}
		}
	}
} /* vmtp_dumplocalmap */

/*
 * VMTP dump vmtp remote csr map routine.
 */
vmtp_dumpremotemap(m)
	char *m;
{
	int i;
	char n[20];

	printf("%s: VMTP REMOTE CSR MAP\n", m);
	for (i=0; i<VMTP_HASHMAPSIZE; i++) {
		if (vremotecsrmap[i] != NULL) {
			printf("vremotecsrmap[%d]\n", i);
			vmtp_dumpcsrs(vremotecsrmap[i], "vremotecsrmap[]", "");
		} else {
			if (vremotecsrmap[i+1] != NULL) {
				printf("struct vmtpcsr:\n");
				printf("\tvremotecsrmap[%d] = NULL\n", i);
			} else {
				printf("\tvremotecsrmap[%d:", i);
				while (vremotecsrmap[i+1] == NULL
			 	      && i+1<VMTP_HASHMAPSIZE)
					i++;
				printf("%d] = NULL\n", i);
			}
		}
	}
} /* vmtp_dumpremotemap */


#ifdef	notdef
/* Out of date */
/*
 * VMTP dump csr queue
 */
vmtp_dumpcsrqueue(head, m)
	struct vmtpcsr *head;
	char *m;
{
	register struct vmtpcsr *p;

	printf("%s: VMTP CSR QUEUE\n", m);
	for (p=head; p!=NULL; p=p->vc_qnext)
		vmtp_dumpcsr(p,"queue",m);
} /* vmtp_dumpcsrqueue */
#endif	notdef

/*
 * Print the key fields of an mbuf - only the first buffer in 
 * a chain is printed.
 */
vmtp_dumpmbuf(mp, n, m)
	struct mbuf *mp;
	char *n, *m;
{
	int i;
	char *c;

	printf("%s: struct mbuf %s: ", m, n);
	if (mp) {
		printf("\n\tm_next = 0x%x ", (u_long)mp->m_next);
		printf("m_off = %d ", mp->m_off);
		printf("m_len = %d ", mp->m_len);
		printf("m_type = %d ", mp->m_type);
/*
		if (mp->m_off > MMAXOFF)
			printf("m_cltype = %d\n", mp->m_cltype);
		else
*/
			printf("\n");
		printf("\tm_dat = ");
		c = mtod(mp, char*);
		for (i = 0; i < 20 && i < mp->m_len; i++) 
				printf("0x%x ", c[i]);
		printf("\n");
	} 
	else 
		printf("NULL\n");
} /* vmtp_dumpmbuf */

vmtp_dumpgroup(g, n, m)
	struct vmtpgroup *g;
	char	*n, *m;
{
	printf("%s: struct vmtpgroup %s: ", m, n);
	if (g) {
		vmtp_dumpeid(&g->vg_eid, "vg_eid", n);
		printf("vg_flags = 0x%x, vg_members = 0x%x\n", g->vg_flags, 
			g->vg_members);
		printf("vg_next = 0x%x\n", g->vg_next);
		if (g->vg_members)
			vmtp_dumpmembers(g->vg_members, "vg_members", n);
	}
} /* vmtp_dumpgroup */

vmtp_dumpgroups(g, n, m)
	struct vmtpgroup *g;
	char	*n, *m;
{
	while (g) {
		vmtp_dumpgroup(g, n, m);
		g = g->vg_next;
	}
} /* vmtp_dumpgroups */

vmtp_dumpmember(mem, n, m)
	struct vmtpmember *mem;
	char	*n, *m;
{
	printf("%s: struct vmtpmember %s: ", m, n);
	if (mem) {
		vmtp_dumpeid(&mem->vm_eid, "vm_eid", n);
		printf("vm_flags = 0x%x\n", mem->vm_flags);
		printf("vm_next = 0x%x\n", mem->vm_next);
	}

} /* vmtp_dumpmember */

vmtp_dumpmembers(mem, n, m)
	struct vmtpmember *mem;
	char	*n, *m;
{

	while (mem) {
		vmtp_dumpmember(mem, n, m);
		mem = mem->vm_next;
	}
} /* vmtp_dumpmembers */

/*
 * Dump the complete group map with all members 
 */
vmtp_dumpgroupmap(m)
	char *m;
{
	int i;
	char n[20];

	printf("%s: VMTP GROUP MAP\n", m);
	for (i=0; i<VMTP_HASHMAPSIZE; i++) {
		if (vg_groupmap[i] != NULL) {
			printf("vg_groupmap[%d]\n", i);
			vmtp_dumpgroups(vg_groupmap[i], "vg_groupmap[]", "");
		} else {
			if (vg_groupmap[i+1] != NULL) {
				printf("struct vmtpgroup:\n");
				printf("\tvg_grouppmap[%d] = NULL\n", i);
			} else {
				printf("\tvg_groupapmap[%d:", i);
				while (vg_groupmap[i+1] == NULL
			 	      && i+1<VMTP_HASHMAPSIZE)
					i++;
				printf("%d] = NULL\n", i);
			}
		}
	}
} /* vmtp_dumpgroupmap */

#endif	MACH_VMTP

