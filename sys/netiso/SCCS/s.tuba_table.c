h36445
s 00001/00001/00122
d D 8.6 94/09/22 19:11:03 sklower 19 18
c minor fixes from cgd@alpha.bostic.com
e
s 00001/00001/00122
d D 8.5 94/07/13 18:11:52 sklower 18 17
c 'nother oops tc->index shouldbe tc->tc_index
e
s 00014/00008/00109
d D 8.4 94/07/13 18:02:45 sklower 17 16
c further fixes, rn_inithead called with wrong offsets and 
c need to store NSAP with net/radix.c conventions for length byte instead of
e
s 00001/00001/00116
d D 8.3 94/06/30 19:08:44 sklower 16 15
c bug fix from Doug Montgomery at NIST.  Forgot to compensate for
c changes to rn_match conventions.
e
s 00000/00001/00117
d D 8.2 93/11/15 13:35:43 sklower 15 14
c af.h has been retired
e
s 00002/00002/00116
d D 8.1 93/06/10 23:21:39 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00006/00115
d D 7.13 93/06/04 14:05:05 sklower 13 12
c changed conventions on rn_delete
e
s 00001/00001/00120
d D 7.12 93/04/25 23:25:20 sklower 12 11
c tuba table now points to sockaddr's_iso instead of iso_addrs, so
c skip 40 bits.
e
s 00001/00001/00120
d D 7.11 93/03/25 17:02:36 sklower 11 10
c yet another fix from Francis.Dupont.  siso_data is signed, spoiling checksums!
e
s 00001/00001/00120
d D 7.10 93/02/12 14:50:46 sklower 10 9
c number of bits to ignore in matches is wrong; causes panic(tuba_lookup)
e
s 00008/00008/00113
d D 7.9 92/11/25 20:09:38 sklower 9 8
c this version supports TCP between two workstations on the same ethernet
e
s 00001/00004/00120
d D 7.8 92/11/20 22:45:24 sklower 8 7
c minor fixes & improvements: swab not in kernel; make sure NSEL is 
c 6 when connecting; don't bother to save extra 2 cksum fudges; change convention
c on who moves pointer past CLNP header; on input, if you have to pull up TCP
c header, do it directly into aligned header.
e
s 00021/00024/00103
d D 7.7 92/11/19 02:38:16 sklower 7 6
c changes thought to be required for new pseudo-header, not tested
e
s 00007/00006/00120
d D 7.6 92/11/08 15:31:27 sklower 6 5
c this version works well enough for a simple sender & receiver to talk
e
s 00003/00003/00123
d D 7.5 92/11/05 15:00:39 sklower 5 4
c checkpoint further progress, still doesn't connect tho.
e
s 00028/00015/00098
d D 7.4 92/11/05 07:13:00 sklower 4 3
c checkpoint, doesn't do checksum right yet
e
s 00025/00025/00088
d D 7.3 92/10/15 18:51:32 sklower 3 2
c this version compiles and matches current #include convention
e
s 00003/00006/00110
d D 7.2 92/10/09 01:08:02 sklower 2 1
c correct defective copyright dates
e
s 00116/00000/00000
d D 7.1 92/10/09 00:51:47 sklower 1 0
c date and time created 92/10/09 00:51:47 by sklower
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1980, 1986, 1991 Regents of the University of California.
E 2
I 2
D 14
 * Copyright (c) 1992 Regents of the University of California.
E 2
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
D 3
#include "param.h"
#include "systm.h"
#include "proc.h"
#include "mbuf.h"
#include "socket.h"
#include "socketvar.h"
#include "domain.h"
#include "protosw.h"
#include "ioctl.h"
E 3
I 3
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/kernel.h>
E 3

D 3
#include "net/if.h"
#include "net/af.h"
#include "net/radix.h"
E 3
I 3
#include <net/if.h>
D 15
#include <net/af.h>
E 15
#include <net/radix.h>
E 3

I 2
D 3
#include "netiso/iso.h"
E 2
#include "tuba_addr.h"
E 3
I 3
#include <netiso/iso.h>
D 4
#include <netiso/tuba_addr.h>
E 4
I 4
#include <netiso/tuba_table.h>
E 4
E 3

D 2
#include "netiso/iso.h"

#define	SA(p) ((struct sockaddr *)(p))

E 2
int	tuba_table_size;
struct	tuba_cache **tuba_table;
struct	radix_node_head *tuba_tree;
extern	int arpt_keep, arpt_prune;	/* use same values as arp cache */

void
tuba_timer()
{
	int s = splnet();
	int	i;
D 3
	register struct	tuba_cache **tc;
E 3
I 3
	register struct	tuba_cache *tc;
E 3
	long	timelimit = time.tv_sec - arpt_keep;

	timeout(tuba_timer, (caddr_t)0, arpt_prune * hz);
	for (i = tuba_table_size; i > 0; i--)
		if ((tc = tuba_table[i]) && (tc->tc_refcnt == 0) &&
		    (tc->tc_time < timelimit)) {
			tuba_table[i] = 0;
D 4
			rn_delete((caddr_t)&tc->tc_addr, (caddr_t)0, tuba_tree);
E 4
I 4
D 6
			rn_delete((caddr_t)&tc->tc_addr, (caddr_t)0,
E 6
I 6
D 7
			rn_delete((caddr_t)&tc->tc_EID, (caddr_t)0,
E 7
I 7
D 13
			rn_delete((caddr_t)&tc->tc_siso.siso_addr, (caddr_t)0,
E 7
E 6
					tuba_tree->rnh_treetop);
E 13
I 13
			rn_delete(&tc->tc_siso.siso_addr, NULL, tuba_tree);
E 13
E 4
			free((caddr_t)tc, M_RTABLE);
		}
	splx(s);
}

D 2
tuba_init()
E 2
I 2
D 3
tuba_timer_init()
E 3
I 3
tuba_table_init()
E 3
E 2
{
D 10
	rn_inithead((void **)&tuba_tree, 40);
E 10
I 10
D 12
	rn_inithead((void **)&tuba_tree, 8);
E 12
I 12
D 17
	rn_inithead((void **)&tuba_tree, 40);
E 17
I 17
	rn_inithead((void **)&tuba_tree, 0);
E 17
E 12
E 10
	timeout(tuba_timer, (caddr_t)0, arpt_prune * hz);
}

int
D 4
tuba_lookup(isoa, flags, wait)
E 4
I 4
D 9
tuba_lookup(isoa, wait)
E 4
	register struct iso_addr *isoa;
E 9
I 9
tuba_lookup(siso, wait)
	register struct sockaddr_iso *siso;
E 9
D 4
	int flags;
E 4
{
D 3
	struct radix_node *rn;
E 3
I 3
	struct radix_node *rn, *rn_match();
E 3
	register struct tuba_cache *tc;
D 3
	int dupentry = 0, sum_even = 0, sum_odd = 0, delta, i;
E 3
I 3
	struct tuba_cache **new;
D 4
	int dupentry = 0, sum_even = 0, sum_odd = 0, old_size, i;
E 4
I 4
	int dupentry = 0, sum_a = 0, sum_b = 0, old_size, i;
D 7
	char EID[7];
E 7
E 4
E 3

I 17
	siso->siso_nlen++;
E 17
D 4
	if (rn = rn_match(tuba_tree, (caddr_t)isoa)) {
E 4
I 4
D 7
	if (isoa->isoa_len < 7)
		return (0);
	bcopy(isoa->isoa_genaddr + isoa->isoa_len - 7, EID + 1, EID[0] = 6);
	if ((rn = rn_match((caddr_t)EID, tuba_tree->rnh_treetop)) &&
E 7
I 7
D 9
	if ((rn = rn_match((caddr_t)isoa, tuba_tree->rnh_treetop)) &&
E 7
	    ((rn->rn_flags & RNF_ROOT) == 0)) {
E 9
I 9
D 16
	if ((rn = rn_match((caddr_t)&siso->siso_addr, tuba_tree->rnh_treetop))
E 16
I 16
	if ((rn = rn_match((caddr_t)&siso->siso_addr, tuba_tree))
E 16
	     && ((rn->rn_flags & RNF_ROOT) == 0)) {
E 9
E 4
		tc = (struct tuba_cache *)rn;
		tc->tc_time = time.tv_sec;
D 17
		return (tc->tc_index);
E 17
I 17
D 18
		i = tc->index;
E 18
I 18
		i = tc->tc_index;
E 18
	done:	siso->siso_nlen--;
		return (i);
E 17
	}
	if ((tc = (struct tuba_cache *)malloc(sizeof(*tc), M_RTABLE, wait))
D 17
		== NULL)
		return (0);
E 17
I 17
		== NULL) {
		i = 0;
		goto done;
	}
E 17
D 3
	bzero((caddr_t)tc, sizeof (*tc))
E 3
I 3
	bzero((caddr_t)tc, sizeof (*tc));
E 3
D 4
	bcopy((caddr_t)isoa, (caddr_t)&tc->tc_addr, 1 + isoa->isoa_len);
	rn_insert((caddr_t)&tc->tc_addr, tuba_tree, &dupentry, tc->tc_nodes);
E 4
I 4
D 5
	bcopy((caddr_t)EID, (caddr_t)&tc->tc_addr, 1 + EID[0]);
	rn_insert((caddr_t)&tc->tc_addr, tuba_tree->rnh_treetop,
		&dupentry, tc->tc_nodes);
E 5
I 5
D 7
	bcopy((caddr_t)EID, (caddr_t)&tc->tc_EID, sizeof(EID));
D 6
	bcopy((caddr_t)isoa, (caddr_t)&tc->tc_addr, 1 + isoa->isoa_len);
E 6
	rn_insert(tc->tc_EID, tuba_tree->rnh_treetop, &dupentry, tc->tc_nodes);
E 5
E 4
	if (dupentry)
		panic("tuba_lookup 1");
E 7
I 6
D 9
	bcopy((caddr_t)isoa, (caddr_t)&tc->tc_siso.siso_addr,
		1 + isoa->isoa_len);
E 9
I 9
D 17
	bcopy(siso->siso_data, tc->tc_siso.siso_data,
		tc->tc_siso.siso_nlen =  siso->siso_nlen);
E 9
I 7
D 13
	rn_insert((caddr_t)&tc->tc_siso.siso_addr,
		  tuba_tree->rnh_treetop, &dupentry, tc->tc_nodes);
E 13
I 13
	rn_insert(&tc->tc_siso.siso_addr, tuba_tree, &dupentry, tc->tc_nodes);
E 17
I 17
	tc->tc_addr = siso->siso_addr;
	siso->siso_nlen--;
	tc->tc_siso.siso_addr = siso->siso_addr;
	rn_insert(&tc->tc_addr, tuba_tree, &dupentry, tc->tc_nodes);
E 17
E 13
	if (dupentry)
		panic("tuba_lookup 1");
E 7
	tc->tc_siso.siso_family = AF_ISO;
	tc->tc_siso.siso_len = sizeof(tc->tc_siso);
E 6
	tc->tc_time = time.tv_sec;
D 4
	tc->tc_flags = flags;
D 3
	sum_even = isoa->isoa_len;
	for (i = sum_even; --i >= 0; ) {
		delta = isoa->isoa_genaddr[i];
		i & 1 ? sum_even += delta : sum_odd += delta;
	}
E 3
I 3
	for (i = isoa->isoa_len; --i >= 0; )
		(i & 1 ? sum_even : sum_odd) += isoa->isoa_genaddr[i];
E 3
	ICKSUM(tc->tc_sum_in, (sum_even << 8) + sum_odd);
D 3
	ICKSUM(tc->tc_sum_out, tc->sum_in + 0x1fffe - tc->tc_index);
E 3
I 3
	ICKSUM(tc->tc_sum_out, tc->tc_sum_in + 0x1fffe - tc->tc_index);
E 4
I 4
D 6
	for (i = EID[0]; i > 0; ) {
E 6
I 6
D 7
	for (i = EID[0]; i > 0; i--)
E 6
		(i & 1 ? sum_a : sum_b) += EID[i];
D 6
		i--;
	}
E 6
	REDUCE(tc->tc_sum_in, (sum_a << 8) + sum_b);
	HTONS(tc->tc_sum_in);
E 7
I 7
D 9
	for (i = sum_a = isoa->isoa_len; --i >= 0; )
E 9
I 9
	for (i = sum_a = tc->tc_siso.siso_nlen; --i >= 0; )
E 9
D 11
		(i & 1 ? sum_a : sum_b) += tc->tc_siso.siso_data[i];
E 11
I 11
D 19
		(i & 1 ? sum_a : sum_b) += (u_char)tc->tc_siso.siso_data[i];
E 19
I 19
		*(i & 1 ? &sum_a : &sum_b) += (u_char)tc->tc_siso.siso_data[i];
E 19
E 11
	REDUCE(tc->tc_sum, (sum_a << 8) + sum_b);
	HTONS(tc->tc_sum);
D 8
	tc->tc_ssum = swab(tc->tc_sum);
E 8
I 8
	SWAB(tc->tc_ssum, tc->tc_sum);
E 8
E 7
E 4
E 3
	for (i = tuba_table_size; i > 0; i--)
		if (tuba_table[i] == 0)
D 7
			break;
	if (i) {
D 4
		tc->tc_index = 1;
E 4
I 4
		tc->tc_index = i;
		REDUCE(tc->tc_sum_out, tc->tc_sum_in + (0xffff ^ tc->tc_index));
E 4
		tuba_table[i] = tc;
		return (i);
	}
E 7
I 7
			goto fixup;
E 7
I 4
	old_size = tuba_table_size;
E 4
	if (tuba_table_size == 0)
		tuba_table_size = 15;
	if (tuba_table_size > 0x7fff)
		return (0);
	tuba_table_size = 1 + 2 * tuba_table_size;
	i = (tuba_table_size + 1) * sizeof(tc);
	new = (struct tuba_cache **)malloc((unsigned)i, M_RTABLE, wait);
	if (new == 0) {
		tuba_table_size = old_size;
D 6
		rn_delete((caddr_t)&tc->tc_addr, (caddr_t)0, tuba_tree);
E 6
I 6
D 7
		rn_delete((caddr_t)&tc->tc_EID, (caddr_t)0, tuba_tree);
E 7
I 7
D 13
		rn_delete((caddr_t)&tc->tc_siso.siso_addr,
D 9
			  (caddr_t)0, tuba_tree);
E 9
I 9
			  (caddr_t)0, tuba_tree->rnh_treetop);
E 13
I 13
D 17
		rn_delete(&tc->tc_siso.siso_addr, NULL, tuba_tree);
E 17
I 17
		rn_delete(&tc->tc_addr, NULL, tuba_tree);
E 17
E 13
E 9
E 7
E 6
		free((caddr_t)tc, M_RTABLE);
		return (0);
	}
	bzero((caddr_t)new, (unsigned)i);
D 4
	if (tuba_table)
E 4
I 4
	if (tuba_table) {
E 4
		bcopy((caddr_t)tuba_table, (caddr_t)new, i >> 1);
I 4
		free((caddr_t)tuba_table, M_RTABLE);
	}
	tuba_table = new;
E 4
D 7
	tuba_table[tc->tc_index = tuba_table_size] = tc;
I 4
	REDUCE(tc->tc_sum_out, tc->tc_sum_in + (0xffff ^ tc->tc_index));
E 7
I 7
	i = tuba_table_size;
fixup:
	tuba_table[i] = tc;
	tc->tc_index = i;
D 8
	i ^= 0xffff;
	REDUCE(tc->tc_sum_d, tc->tc_sum + i);
	REDUCE(tc->tc_ssum_d, tc->tc_ssum + i);
E 8
E 7
E 4
	return (tc->tc_index);
}
E 1
