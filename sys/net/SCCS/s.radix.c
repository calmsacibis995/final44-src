h64578
s 00032/00013/00854
d D 8.5 95/05/19 15:00:53 sklower 28 26
c put in stuff to shut up gcc and reverse thread dupedkey chains for pst
e
s 00169/00275/00592
d D 8.2.3.1 94/12/02 14:55:12 sklower 27 24
c this doesn't include annotation bugfixes, but documents
c work sent to mitre for a tunnel driver
e
s 00001/00001/00866
d D 8.4 94/11/02 17:19:50 sklower 26 25
c put in too many flags when setting netmask
e
s 00269/00133/00598
d D 8.3 94/10/31 13:42:52 sklower 25 22
c compromise fixes for duped keys
e
s 00269/00133/00598
d D 8.2.2.1 94/10/09 01:37:30 sklower 24 22
c This version supports both non-contiguous masks and prefix-only ones
c and contains some fixes suggested by Richard Woundy as well as some of my own
c for cases of super nets being added in arbitrary order;
c This version does some optimizations when prefix-only routes are in use;
c It has had limited testing in user space and shouldn't be suffering from
c typographical-level errors, and has been tested against all the end-cases
c that Woundy sought to fix.
e
s 00392/00330/00401
d D 8.2.1.1 94/09/23 18:59:08 sklower 23 22
c put in branch delta for normal-only routes, and mapping capabilities;
c first version; probably doesn't work yet.
e
s 00002/00004/00729
d D 8.2 94/01/04 21:49:14 bostic 22 21
c lint
e
s 00002/00002/00731
d D 8.1 93/06/10 22:45:10 bostic 21 20
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00051/00031/00682
d D 7.20 93/06/04 17:30:53 bostic 20 19
c prototype everything
e
s 00001/00001/00712
d D 7.19 93/05/24 23:46:21 torek 19 18
c pedantically ANSI, i.e., nothing after #else/#endif
e
s 00035/00033/00678
d D 7.18 93/04/08 17:12:44 sklower 18 17
c new conventions for using routing tree
e
s 00007/00005/00704
d D 7.17 92/10/11 11:49:03 bostic 17 16
c make kernel includes standard
e
s 00001/00000/00708
d D 7.16 92/07/12 17:38:14 pendry 16 15
c need to include "systm.h"
e
s 00060/00027/00648
d D 7.15 92/07/09 00:02:37 sklower 15 14
c changes to add routing tables via the domain switch
e
s 00015/00006/00660
d D 7.14 92/05/21 17:02:29 sklower 14 13
c make rn_refines into rn_strictly_refines, so that ifa_ifwithnet()
c will return the first of two equally good matches (which happens when you
c have two IP address on the same subnet).
e
s 00007/00005/00659
d D 7.13 92/01/29 19:23:38 torek 13 12
c lint and formatting changes, checked in by KLS.
e
s 00006/00004/00658
d D 7.12 91/08/08 14:33:23 sklower 12 11
c move logic about traversing dupkeyed entries from rtdumpentry to rn_walk
e
s 00045/00016/00617
d D 7.11 91/07/31 18:05:39 sklower 11 10
c sort duped key chains
e
s 00031/00011/00602
d D 7.10 91/07/30 17:38:32 sklower 10 9
c use vector instead of linked list for tree heads; walk routine
c is now a method, and is included with other things that know about radix nodes.
e
s 00002/00002/00611
d D 7.9 91/02/04 16:02:58 sklower 9 8
c bugfix from john@labtam.labtam.oz.au
e
s 00007/00009/00606
d D 7.8 90/11/15 16:28:30 sklower 8 7
c fix "Orphaned mask" and "Can't find our annotation" bugs.
e
s 00001/00011/00614
d D 7.7 90/06/28 21:31:27 bostic 7 6
c new copyright notice
e
s 00050/00031/00575
d D 7.6 90/06/20 19:05:19 sklower 6 5
c changes designed so that ESIS and ARP may use routing table
c instead of private cache; allow RTM_CHANGE to specify new ifp.
e
s 00002/00000/00604
d D 7.5 90/04/05 11:28:58 sklower 5 4
c no longer included in route.c; needed "malloc.h" to stand on own.
e
s 00061/00056/00543
d D 7.4 89/08/29 14:59:17 sklower 4 3
c various fixes concerning lost annotations; check in for ``alpha tape''
e
s 00033/00002/00566
d D 7.3 89/04/22 12:11:26 sklower 3 2
c checkpoint at first working tp4 connection; before gnodes
e
s 00031/00031/00537
d D 7.2 88/12/13 13:30:29 sklower 2 1
c checkpoint semi-working version with routing socket
e
s 00568/00000/00000
d D 7.1 88/11/09 23:27:29 sklower 1 0
c date and time created 88/11/09 23:27:29 by sklower
e
u
U
f b 
t
T
I 1
/*
D 3
 * Copyright (c) 1982, 1988 Regents of the University of California.
E 3
I 3
D 21
 * Copyright (c) 1988, 1989  Regents of the University of California.
E 3
 * All rights reserved.
E 21
I 21
D 27
 * Copyright (c) 1988, 1989, 1993
E 27
I 27
 * Copyright (c) 1988, 1991, 1993
E 27
 *	The Regents of the University of California.  All rights reserved.
E 21
 *
D 7
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * %sccs.include.redist.c%
E 7
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Routines to build and maintain radix trees for routing lookups.
 */
D 24
D 25
#ifndef RNF_NORMAL
E 25
I 25
#ifndef _RADIX_H_
E 25
E 24
I 24
D 27
#ifndef _RADIX_H_
E 27
I 27
#ifndef RNF_NORMAL
E 27
E 24
D 2
typedef unsigned char u_char;
E 2
I 2
D 17
#include "param.h"
I 16
#include "systm.h"
E 16
E 2
#include "radix.h"
I 5
#include "malloc.h"
E 17
I 17
#include <sys/param.h>
I 25
#ifdef	KERNEL
E 25
I 24
D 27
#ifdef	KERNEL
E 27
E 24
#include <sys/systm.h>
#include <sys/malloc.h>
E 17
#define	M_DONTWAIT M_NOWAIT
I 27
#ifdef	KERNEL
E 27
I 15
D 24
D 25
#ifdef	KERNEL
E 25
E 24
D 17
#include "domain.h"
E 17
I 17
#include <sys/domain.h>
I 25
#else
#include <stdlib.h>
E 25
I 24
D 27
#else
#include <stdlib.h>
E 27
E 24
E 17
E 15
E 5
#endif
I 25
#include <sys/syslog.h>
#include <net/radix.h>
E 25
I 24
D 27
#include <sys/syslog.h>
#include <net/radix.h>
E 27
E 24
I 15
#endif
I 17

I 27
#include <net/radix.h>

E 27
D 23
D 24
D 25
#include <net/radix.h>
E 23
I 23
#include "radix.h"
E 23

E 25
E 24
E 17
int	max_keylen;
E 15
D 4
struct radix_node_head *radix_node_head;
E 4
I 4
D 10
struct radix_node_head *mask_rnhead;
#define rn_maskhead mask_rnhead->rnh_treetop
E 10
E 4
D 23
struct radix_mask *rn_mkfreelist;
E 23
D 4
#define rn_maskhead radix_node_head->rnh_treetop
E 4
I 4
D 10
struct radix_node_head *radix_node_head;
E 10
I 10
struct radix_node_head *mask_rnhead;
I 15
D 23
D 24
D 25
static int gotOddMasks;
static char *maskedKey;
E 25
I 25
static char *addmask_key;
static char normal_chars[] = {0, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, -1};
E 25
E 24
I 24
D 27
static char *addmask_key;
static char normal_chars[] = {0, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, -1};
E 27
I 27
static int gotOddMasks;
static char *maskedKey;
E 27
E 24
E 23
static char *rn_zeros, *rn_ones;

E 15
D 18
#define rn_maskhead (mask_rnhead->rnh_treetop)
E 18
I 18
#define rn_masktop (mask_rnhead->rnh_treetop)
E 18
E 10
#undef Bcmp
#define Bcmp(a, b, l) (l == 0 ? 0 : bcmp((caddr_t)(a), (caddr_t)(b), (u_long)l))
E 4
/*
 * The data structure for the keys is a radix tree with one way
 * branching removed.  The index rn_b at an internal node n represents a bit
 * position to be tested.  The tree is arranged so that all descendants
 * of a node n have keys whose bits all agree up to position rn_b - 1.
 * (We say the index of n is rn_b.)
 *
 * There is at least one descendant which has a one bit at position rn_b,
 * and at least one with a zero there.
 *
 * A route is determined by a pair of key and mask.  We require that the
 * bit-wise logical and of the key and mask to be the key.
 * We define the index of a route to associated with the mask to be
 * the first bit number in the mask where 0 occurs (with bit number 0
 * representing the highest order bit).
 * 
 * We say a mask is normal if every bit is 0, past the index of the mask.
 * If a node n has a descendant (k, m) with index(m) == index(n) == rn_b,
 * and m is a normal mask, then the route applies to every descendant of n.
 * If the index(m) < rn_b, this implies the trailing last few bits of k
 * before bit b are all 0, (and hence consequently true of every descendant
 * of n), so the route applies to all descendants of the node as well.
D 24
D 25
 *
D 23
 * The present version of the code makes no use of normal routes,
 * but similar logic shows that a non-normal mask m such that
E 25
I 25
 * 
 * Similar logic shows that a non-normal mask m such that
E 25
E 24
I 24
D 27
 * 
 * Similar logic shows that a non-normal mask m such that
E 27
I 27
 *
 * The present version of the code makes no use of normal routes,
 * but similar logic shows that a non-normal mask m such that
E 27
E 24
 * index(m) <= index(n) could potentially apply to many children of n.
 * Thus, for each non-host route, we attach its mask to a list at an internal
 * node as high in the tree as we can go. 
I 25
 *
 * The present version of the code makes use of normal routes in short-
 * circuiting an explict mask and compare operation when testing whether
 * a key satisfies a normal route, and also in remembering the unique leaf
 * that governs a subtree.
E 25
I 24
D 27
 *
 * The present version of the code makes use of normal routes in short-
 * circuiting an explict mask and compare operation when testing whether
 * a key satisfies a normal route, and also in remembering the unique leaf
 * that governs a subtree.
E 27
E 24
E 23
I 23
 * This version of the code assumes that all masks are normal,
 * and consequently the only thing that needs to be stored about a mask
 * is its length.  This version also permits mapped, and fixed length
 * elements to be entered into the tree.
E 23
 */

struct radix_node *
D 20
rn_search(v, head)
E 20
I 20
D 23
rn_search(v_arg, head)
E 23
I 23
rn_search(v_arg, top)
E 23
	void *v_arg;
E 20
D 23
	struct radix_node *head;
E 23
I 23
	struct radix_node *top;
E 23
D 2
	register char *v;
E 2
I 2
D 20
	register caddr_t v;
E 20
E 2
{
	register struct radix_node *x;
I 20
	register caddr_t v;
E 20

D 20
	for (x = head; x->rn_b >= 0;) {
E 20
I 20
D 23
	for (x = head, v = v_arg; x->rn_b >= 0;) {
E 23
I 23
	for (x = top, v = v_arg; x->rn_b >= 0;) {
E 23
E 20
		if (x->rn_bmask & v[x->rn_off])
			x = x->rn_r;
		else
			x = x->rn_l;
	}
D 20
	return x;
E 20
I 20
	return (x);
E 20
};

I 23
static char search_bits[] = {0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1};

E 23
I 3
D 4
#ifdef notdef
E 4
struct radix_node *
D 20
rn_search_m(v, head, m)
E 20
I 20
D 23
rn_search_m(v_arg, head, m_arg)
E 20
	struct radix_node *head;
D 20
	register caddr_t v, m;
E 20
I 20
	void *v_arg, *m_arg;
E 23
I 23
rn_search_unmapped(v_arg, head)
	void *v_arg;
	struct radix_node_head *head;
E 23
E 20
{
D 23
	register struct radix_node *x;
I 20
	register caddr_t v = v_arg, m = m_arg;
E 23
I 23
	register struct radix_node *x = head->rnh_treetop;
	register char *v;
	register int index;
E 23
E 20
E 3

I 3
D 23
	for (x = head; x->rn_b >= 0;) {
		if ((x->rn_bmask & m[x->rn_off]) &&
		    (x->rn_bmask & v[x->rn_off]))
E 23
I 23
	for (v = v_arg; x->rn_b >= 0;) {
		index = x->rn_b + head->rnh_offset;
		if (search_bits[index & 7] & v[index >> 3])
E 23
			x = x->rn_r;
		else
			x = x->rn_l;
	}
D 23
	return x;
E 23
I 23
	return (x);
E 23
};
D 4
#endif
E 4

I 11
D 20
rn_refines(m, n)
	register caddr_t m, n;
E 20
I 20
D 23
int
E 23
I 23

/*
 * This routine is used elsewhere in the kernel concerning
 * best matches for interfaces and is no longer used in the
 * radix code.  
 *
 */
int 
E 23
rn_refines(m_arg, n_arg)
	void *m_arg, *n_arg;
E 20
{
I 20
	register caddr_t m = m_arg, n = n_arg;
E 20
	register caddr_t lim, lim2 = lim = n + *(u_char *)n;
	int longer = (*(u_char *)n++) - (int)(*(u_char *)m++);
I 14
	int masks_are_equal = 1;
E 14
E 11

I 11
	if (longer > 0)
		lim -= longer;
D 14
	while (n < lim)
		if (*n++ & ~(*m++))
E 14
I 14
	while (n < lim) {
		if (*n & ~(*m))
E 14
			return 0;
I 14
		if (*n++ != *m++)
			masks_are_equal = 0;
I 27
			
E 27
D 24
D 25
			
E 25
E 24
	}
E 14
	while (n < lim2)
		if (*n++)
			return 0;
D 14
	return 1;
E 14
I 14
	if (masks_are_equal && (longer < 0))
		for (lim2 = m - longer; m < lim2; )
			if (*m++)
				return 1;
	return (!masks_are_equal);
E 14
}
I 23
/* Begin bits.c */
static int low_bits[] = {1, 3, 7, 15, 31, 63, 127, 255};
static int mask_bits[] = {1, 2, 4, 8, 16, 32, 64, 128};
E 23

I 25
struct radix_node *
rn_lookup(v_arg, m_arg, head)
	void *v_arg, *m_arg;
	struct radix_node_head *head;
{
	register struct radix_node *x;
	caddr_t netmask = 0;
E 25
I 24
D 27
struct radix_node *
rn_lookup(v_arg, m_arg, head)
	void *v_arg, *m_arg;
	struct radix_node_head *head;
{
	register struct radix_node *x;
	caddr_t netmask = 0;
E 27
E 24
I 23
#define x1(a,n) ( a > ((1 << (n + 1)) - 1) ? n+1 : n)
#define x2(a,n) (( a > ((1 << (2 + n)) - 1)) ? x1(a,n+2) : x1(a,n))
#define x4(a,n) (( a > ((1 << (4 + n)) - 1)) ? x2(a,n+4) : x2(a,n))
#define x8(a,n) (( a > ((1 << (8 + n)) - 1)) ? x4(a,n+8) : x4(a,n))
#define x16(a,n) ((a > (((1 << n) - 1)+(65535 << n))) ? x8(a,n+16) : x8(a,n))
E 23

I 25
	if (m_arg) {
		if ((x = rn_addmask(m_arg, 1, head->rnh_treetop->rn_off)) == 0)
			return (0);
		netmask = x->rn_key;
	}
	x = rn_match(v_arg, head);
	if (x && netmask) {
		while (x && x->rn_mask != netmask)
			x = x->rn_dupedkey;
	}
	return x;
}

D 28
static
E 28
I 28
static int
E 28
rn_satsifies_leaf(trial, leaf, skip)
	char *trial;
	register struct radix_node *leaf;
	int skip;
{
	register char *cp = trial, *cp2 = leaf->rn_key, *cp3 = leaf->rn_mask;
	char *cplim;
	int length = min(*(u_char *)cp, *(u_char *)cp2);

	if (cp3 == 0)
		cp3 = rn_ones;
	else
		length = min(length, *(u_char *)cp3);
	cplim = cp + length; cp3 += skip; cp2 += skip;
	for (cp += skip; cp < cplim; cp++, cp2++, cp3++)
		if ((*cp ^ *cp2) & *cp3)
			return 0;
	return 1;
}

E 25
I 24
D 27
	if (m_arg) {
		if ((x = rn_addmask(m_arg, 1, head->rnh_treetop->rn_off)) == 0)
			return (0);
		netmask = x->rn_key;
	}
	x = rn_match(v_arg, head);
	if (x && netmask) {
		while (x && x->rn_mask != netmask)
			x = x->rn_dupedkey;
	}
	return x;
}

static
rn_satsifies_leaf(trial, leaf, skip)
	char *trial;
	register struct radix_node *leaf;
	int skip;
{
	register char *cp = trial, *cp2 = leaf->rn_key, *cp3 = leaf->rn_mask;
	char *cplim;
	int length = min(*(u_char *)cp, *(u_char *)cp2);

	if (cp3 == 0)
		cp3 = rn_ones;
	else
		length = min(length, *(u_char *)cp3);
	cplim = cp + length; cp3 += skip; cp2 += skip;
	for (cp += skip; cp < cplim; cp++, cp2++, cp3++)
		if ((*cp ^ *cp2) & *cp3)
			return 0;
	return 1;
}

E 27
E 24
I 23
int
rn_mapped_bits_matched(t_a, r_a, rnh, masklen)
	void	*t_a;			/* Under scrutiny, assumed mapped */
	void	*r_a;			/* being compared to, not mapped */
	struct	radix_node_head *rnh;	/* has offset for ref, map for trial */
	int	masklen;		/* only need this many bits to match*/	
{
	register struct radix_index_table *table = rnh->rnh_table;
	int matched = 0, k, l;
	u_char	*trial = t_a;		/* Under scrutiny, assumed mapped */
	u_char	*ref = r_a;		/* being compared to, not mapped */

#ifdef utterly_straightforward_way_of_doing_this
	for (; table->limit; table++) {
		for (; matched < table->limit; matched++) {
			if (matched >= masklen - 1)
				return (matched);
			k = matched + table->offset;
			l = matched + rnh->rnh_offset;
			/* is bit l of ref == bit k of trial */
			if (((ref[l >> 3] >> (7 - (l & 7))) ^
			     (trial[k >> 3] >> (7 - (k & 7)))) & 1)
				return (matched);
		}
	}
#else
	int test_info, trial_bits, ref_bits, limit, sum_bits, delta;

	for (; table->limit; table++) {
		limit = MIN(masklen, table->limit);
		while (matched < limit) {
			k = matched + table->offset;
			l = matched + rnh->rnh_offset;
			trial_bits = 7 - (k & 7);
			ref_bits = 7 - (l & 7);
			delta = MIN(MIN(trial_bits, ref_bits), limit - matched);
			sum_bits = trial_bits + ref_bits;

			test_info = ((int)ref[k >> 3]) << ref_bits;
			test_info ^= ((int)trial[l >> 3]) << trial_bits;
			test_info &= low_bits[sum_bits];
			test_info &= ~low_bits[sum_bits - delta];
			if (test_info != 0) {
				int count, mask = mask_bits[sum_bits];
				for (count = delta; count >= 0; count--) {
					if (mask & test_info)
						return (matched);
					matched++; mask >>= 1;
				}
				printf("Bits_matched: should never get here!");
			}
			matched += delta;
			if (matched >= masklen)
				return (matched);
		}
	}
#endif
	return (matched);
}

#if defined(IPPROTO_IP) && defined(IPVERSION) /* #include <netinet/i{n,p}.h>" */
int ip_mapped_bits_matched
	(void *t_a, void *r_a, struct radix_node_head *rnh, int masklen)
{
	struct ip *trial = t_a;
	struct sockaddr_in *ref = r_a;

	u_long bits = trial->sin_addr.s_addr ^ ip->ip_dst.s_adddr;
	if (bits == 0) return (32); 	/* expected case !*/
	bits = ntohl(bits);
	bits =  x16(bits, 0);
	return bits;
}
#endif

rn_mapped_set_mask(index, rn, rnh)
	int index;
	register struct radix_node *rn;
	register struct radix_node_head *rnh;
{
	register struct radix_index_table *table;

	for (table = rnh->rnh_table; table->limit && index < table->limit;)
		table++;
	if (table->limit) {
		index += table->offset;
		rn->rn_bmask = mask_bits[7 - (index & 7)];
		rn->rn_off = (index >> 3);
	}
}

rn_unmapped_bits_matched(t_a, r_a, rnh, masklen)
	void	*t_a;			/* Under scrutiny, assumed mapped */
	void	*r_a;			/* being compared to, not mapped */
	struct	radix_node_head *rnh;	/* has offset for ref, map for trial */
	int	masklen;		/* only need this many bits to match*/	
{
	register u_char *cp1, *cp2, *limit;
	int offset = rnh->rnh_offset >> 3;/* XXX: off must be n * 8 */
	int matched, test_info;
	u_char	*trial = t_a;		/* Under scrutiny, assumed mapped */
	u_char	*ref = r_a;		/* being compared to, not mapped */

	cp1 = trial + offset;
	limit = cp1 + ((masklen + 7) >> 3);
	for (cp2 = ref + offset; cp1 < limit;)
		if (*cp1++ != *cp2++) {
			test_info = cp1[-1] ^ cp2[-1];
			matched = (cp1 - trial - offset) << 3;
			for (; test_info; matched--)
				test_info >>= 1;
			if (matched > masklen)
				matched = masklen;
			return (matched);
		}
	return (masklen);
}

rn_unmapped_set_mask(index, rn, rnh)
	int index;
	register struct radix_node *rn;
	register struct radix_node_head *rnh;
{
	index += rnh->rnh_offset;
	rn->rn_bmask = mask_bits[7 - (index & 7)];
	rn->rn_off = (index >> 3);
}
/* End bits.c */

E 23
E 11
I 10
D 15
#define MAXKEYLEN 52
E 10
E 3
static int gotOddMasks;
static char maskedKey[MAXKEYLEN];

E 15
D 18
struct radix_node *
E 18
I 18
D 20
static struct radix_node *
E 18
rn_match(v, head)
E 20
I 20
struct radix_node *
rn_match(v_arg, head)
	void *v_arg;
E 20
D 18
	struct radix_node *head;
E 18
I 18
	struct radix_node_head *head;
E 18
D 2
	char *v;
E 2
I 2
D 20
	caddr_t v;
E 20
E 2
{
I 20
D 23
	caddr_t v = v_arg;
E 20
D 18
	register struct radix_node *t = head, *x;
E 18
I 18
	register struct radix_node *t = head->rnh_treetop, *x;
E 18
D 2
	register char *cp = v, *cp2, *cp3;
	char *cplim, *mstart;
E 2
I 2
D 24
D 25
	register caddr_t cp = v, cp2, cp3;
	caddr_t cplim, mstart;
E 25
I 25
	register caddr_t cp = v, cp2;
	caddr_t cplim;
E 25
E 24
I 24
D 27
	register caddr_t cp = v, cp2;
	caddr_t cplim;
E 27
I 27
	register caddr_t cp = v, cp2, cp3;
	caddr_t cplim, mstart;
E 27
E 24
E 23
I 23
	register char *cp = (char *)(v_arg);
	register struct radix_node *m, *t = head->rnh_treetop;
E 23
E 2
D 18
	struct radix_node *saved_t;
E 18
I 18
	struct radix_node *saved_t, *top = t;
E 18
D 2
	int off = t->rn_off, vlen = *(u_char *)cp, head_off, matched_off;
E 2
I 2
D 23
	int off = t->rn_off, vlen = *(u_char *)cp, matched_off;
I 25
	register int test, b, rn_b;
E 25
I 24
D 27
	register int test, b, rn_b;
E 27
E 24
E 23
I 23
	int bits_matched, rn_b;
E 23
E 2

	/*
D 18
	 * Open code rn_search(v, head) to avoid overhead of extra
E 18
I 18
	 * Open code rn_search(v, top) to avoid overhead of extra
E 18
	 * subroutine call.
	 */
D 23
	for (; t->rn_b >= 0; ) {
E 23
I 23
	while (t->rn_b >= 0)
E 23
		if (t->rn_bmask & cp[t->rn_off])
			t = t->rn_r;
		else
			t = t->rn_l;
D 23
	}
E 23
I 23
	bits_matched = (*head->rnh_bits_matched)
				(v_arg, t->rn_key, head, -1 - t->rn_b);
	rn_b = -1 - bits_matched;	/* XXX: compatability */
E 23
	/*
D 23
	 * See if we match exactly as a host destination
I 25
	 * or at least learn how many bits match, for normal mask finesse.
	 *
	 * It doesn't hurt us to limit how many bytes to check
	 * to the length of the mask, since if it matches we had a genuine
	 * match and the leaf we have is the most specific one anyway;
	 * if it didn't match with a shorter length it would fail
	 * with a long one.  This wins big for class B&C netmasks which
	 * are probably the most common case...
E 25
I 24
D 27
	 * or at least learn how many bits match, for normal mask finesse.
	 *
	 * It doesn't hurt us to limit how many bytes to check
	 * to the length of the mask, since if it matches we had a genuine
	 * match and the leaf we have is the most specific one anyway;
	 * if it didn't match with a shorter length it would fail
	 * with a long one.  This wins big for class B&C netmasks which
	 * are probably the most common case...
E 27
E 24
E 23
I 23
	 * Check this node, and any other duped keys.
	 * We want to match the most specific possible mask, so
	 * duplicates are sorted longest mask to shortest.
E 23
	 */
I 25
	if (t->rn_mask)
		vlen = *(u_char *)t->rn_mask;
E 25
I 24
D 27
	if (t->rn_mask)
		vlen = *(u_char *)t->rn_mask;
E 27
E 24
D 23
	cp += off; cp2 = t->rn_key + off; cplim = v + vlen;
	for (; cp < cplim; cp++, cp2++)
		if (*cp != *cp2)
			goto on1;
I 3
	/*
	 * This extra grot is in case we are explicitly asked
	 * to look up the default.  Ugh!
	 */
	if ((t->rn_flags & RNF_ROOT) && t->rn_dupedkey)
		t = t->rn_dupedkey;
E 3
	return t;
on1:
I 25
	test = (*cp ^ *cp2) & 0xff; /* find first bit that differs */
	for (b = 7; (test >>= 1) > 0;)
		b--;
E 25
I 24
D 27
	test = (*cp ^ *cp2) & 0xff; /* find first bit that differs */
	for (b = 7; (test >>= 1) > 0;)
		b--;
E 27
E 24
	matched_off = cp - v;
D 24
D 25
	saved_t = t;
	do {
	    if (t->rn_mask) {
E 25
I 25
	b += matched_off << 3;
	rn_b = -1 - b;
	/*
	 * If there is a host route in a duped-key chain, it will be first.
	 */
	if ((saved_t = t)->rn_mask == 0)
		t = t->rn_dupedkey;
	for (; t; t = t->rn_dupedkey)
E 25
E 24
I 24
D 27
	b += matched_off << 3;
	rn_b = -1 - b;
	/*
	 * If there is a host route in a duped-key chain, it will be first.
	 */
	if ((saved_t = t)->rn_mask == 0)
		t = t->rn_dupedkey;
	for (; t; t = t->rn_dupedkey)
E 27
I 27
	saved_t = t;
	do {
	    if (t->rn_mask) {
E 27
E 24
		/*
D 24
D 25
		 * Even if we don't match exactly as a hosts;
E 25
I 25
		 * Even if we don't match exactly as a host,
E 25
E 24
I 24
D 27
		 * Even if we don't match exactly as a host,
E 27
I 27
		 * Even if we don't match exactly as a hosts;
E 27
E 24
		 * we may match if the leaf we wound up at is
		 * a route to a net.
		 */
D 24
D 25
		cp3 = matched_off + t->rn_mask;
I 4
		cp2 = matched_off + t->rn_key;
E 4
		for (; cp < cplim; cp++)
			if ((*cp2++ ^ *cp) & *cp3++)
				break;
		if (cp == cplim)
			return t;
I 4
		cp = matched_off + v;
E 4
	    }
	} while (t = t->rn_dupedkey);
E 25
I 25
		if (t->rn_flags & RNF_NORMAL) {
			if (rn_b <= t->rn_b)
				return t;
		} else if (rn_satsifies_leaf(v, t, matched_off))
				return t;
E 25
E 24
I 24
D 27
		if (t->rn_flags & RNF_NORMAL) {
			if (rn_b <= t->rn_b)
				return t;
		} else if (rn_satsifies_leaf(v, t, matched_off))
				return t;
E 27
I 27
		cp3 = matched_off + t->rn_mask;
		cp2 = matched_off + t->rn_key;
		for (; cp < cplim; cp++)
			if ((*cp2++ ^ *cp) & *cp3++)
				break;
		if (cp == cplim)
			return t;
		cp = matched_off + v;
	    }
	} while (t = t->rn_dupedkey);
E 27
E 24
	t = saved_t;
	/* start searching up the tree */
	do {
		register struct radix_mask *m;
		t = t->rn_p;
D 28
		if (m = t->rn_mklist) {
E 28
I 28
		m = t->rn_mklist;
		if (m) {
E 28
E 23
I 23
	for (saved_t = t; t; t = t->rn_dupedkey)
		/* if (bits_matched >= mask_index) */
		if (rn_b <= t->rn_b) {
E 23
I 3
			/*
D 23
D 24
D 25
			 * After doing measurements here, it may
			 * turn out to be faster to open code
			 * rn_search_m here instead of always
			 * copying and masking.
E 25
I 25
			 * If non-contiguous masks ever become important
			 * we can restore the masking and open coding of
			 * the search and satisfaction test and put the
			 * calculation of "off" back before the "do".
E 25
E 24
I 24
D 27
			 * If non-contiguous masks ever become important
			 * we can restore the masking and open coding of
			 * the search and satisfaction test and put the
			 * calculation of "off" back before the "do".
E 27
I 27
			 * After doing measurements here, it may
			 * turn out to be faster to open code
			 * rn_search_m here instead of always
			 * copying and masking.
E 27
E 24
E 23
I 23
			 * This extra grot is in case we are explicitly asked
			 * to look up the default.  Ugh!
E 23
			 */
I 27
			off = min(t->rn_off, matched_off);
			mstart = maskedKey + off;
E 27
E 3
D 23
D 24
D 25
			off = min(t->rn_off, matched_off);
			mstart = maskedKey + off;
E 25
E 24
			do {
D 24
D 25
				cp2 = mstart;
				cp3 = m->rm_mask + off;
				for (cp = v + off; cp < cplim;)
					*cp2++ =  *cp++ & *cp3++;
				x = rn_search(maskedKey, t);
				while (x && x->rn_mask != m->rm_mask)
					x = x->rn_dupedkey;
				if (x &&
				    (Bcmp(mstart, x->rn_key + off,
					vlen - off) == 0))
					    return x;
E 25
I 25
				if (m->rm_flags & RNF_NORMAL) {
					if (rn_b <= m->rm_b)
						return (m->rm_leaf);
				} else {
					off = min(t->rn_off, matched_off);
					x = rn_search_m(v, t, m->rm_mask);
					while (x && x->rn_mask != m->rm_mask)
						x = x->rn_dupedkey;
					if (x && rn_satsifies_leaf(v, x, off))
						    return x;
				}
E 25
E 24
I 24
D 27
				if (m->rm_flags & RNF_NORMAL) {
					if (rn_b <= m->rm_b)
						return (m->rm_leaf);
				} else {
					off = min(t->rn_off, matched_off);
					x = rn_search_m(v, t, m->rm_mask);
					while (x && x->rn_mask != m->rm_mask)
						x = x->rn_dupedkey;
					if (x && rn_satsifies_leaf(v, x, off))
						    return x;
				}
E 27
I 27
				cp2 = mstart;
				cp3 = m->rm_mask + off;
				for (cp = v + off; cp < cplim;)
					*cp2++ =  *cp++ & *cp3++;
				x = rn_search(maskedKey, t);
				while (x && x->rn_mask != m->rm_mask)
					x = x->rn_dupedkey;
				if (x &&
				    (Bcmp(mstart, x->rn_key + off,
					vlen - off) == 0))
					    return x;
E 27
E 24
D 28
			} while (m = m->rm_mklist);
E 28
I 28
			m = m->rm_mklist;
			} while (m);
E 28
E 23
I 23
			if ((t->rn_flags & RNF_ROOT) && t->rn_dupedkey)
				t = t->rn_dupedkey;
			return (t);
E 23
		}
I 23
	/* start searching up the tree */
	t = saved_t;
	do {
		t = t->rn_p;
		for (m = t->rn_mklist; m; m = m->rn_mklist)
			/* if (bits_matched >= mask_index) */
			if (rn_b <= m->rn_b)
				return (m);
E 23
D 18
	} while (t != head);
E 18
I 18
	} while (t != top);
E 18
	return 0;
};
		
#ifdef RN_DEBUG
int	rn_nodenum;
struct	radix_node *rn_clist;
int	rn_saveinfo;
I 18
int	rn_debug =  1;
E 18
#endif

struct radix_node *
D 23
rn_newpair(v, b, nodes)
E 23
I 23
rn_newpair1(v, b, nodes, rnh)
E 23
D 2
	char *v;
E 2
I 2
D 20
	caddr_t v;
E 20
I 20
	void *v;
E 20
I 13
	int b;
E 13
E 2
	struct radix_node nodes[2];
I 23
	struct radix_node_head *rnh;
E 23
{
	register struct radix_node *tt = nodes, *t = tt + 1;
D 23
	t->rn_b = b; t->rn_bmask = 0x80 >> (b & 7);
	t->rn_l = tt; t->rn_off = b >> 3;
E 23
I 23
	if (rnh == 0)
		panic("rn_newpair1");
	t->rn_b = b; t->rn_l = tt;
	(*rnh->rnh_set_mask)(b, t, rnh);
E 23
D 20
	tt->rn_b = -1; tt->rn_key = v; tt->rn_p = t;
E 20
I 20
	tt->rn_b = -1; tt->rn_key = (caddr_t)v; tt->rn_p = t;
E 20
	tt->rn_flags = t->rn_flags = RNF_ACTIVE;
#ifdef RN_DEBUG
	tt->rn_info = rn_nodenum++; t->rn_info = rn_nodenum++;
	tt->rn_twin = t; tt->rn_ybro = rn_clist; rn_clist = tt;
#endif
	return t;
}

I 23
#define DEFAULT(a, b) (a > 0 ? a : b)
#define VLEN(v, h) ((DEFAULT(h->rnh_addrsize, *(u_char *)v) << 3) - h->rnh_offset)

E 23
D 18
int rn_debug =  1;
struct radix_node *
E 18
I 18
D 20
static struct radix_node *
E 18
rn_insert(v, head, dupentry, nodes)
D 2
	char *v;
E 2
I 2
	caddr_t v;
E 20
I 20
struct radix_node *
rn_insert(v_arg, head, dupentry, nodes)
	void *v_arg;
E 20
E 2
D 18
	struct radix_node *head;
E 18
I 18
D 23
	struct radix_node_head *head;
E 23
I 23
	register struct radix_node_head *head;
E 23
E 18
	int *dupentry;
	struct radix_node nodes[2];
{
I 20
D 23
	caddr_t v = v_arg;
E 20
D 18
	int head_off = head->rn_off, vlen = (int)*((u_char *)v);
	register struct radix_node *t = rn_search(v, head);
E 18
I 18
	struct radix_node *top = head->rnh_treetop;
	int head_off = top->rn_off, vlen = (int)*((u_char *)v);
D 20
	register struct radix_node *t = rn_search(v, top);
E 20
I 20
	register struct radix_node *t = rn_search(v_arg, top);
E 20
E 18
D 2
	register char *cp = v + head_off;
E 2
I 2
	register caddr_t cp = v + head_off;
E 2
	register int b;
	struct radix_node *tt;
E 23
I 23
	caddr_t v = (caddr_t)v_arg, cp = (head->rnh_offset >> 3) + v;
	register struct radix_node *t = rn_search_unmapped(v, head);
	register struct radix_node *p, *x;
	int b, vlen = VLEN(v, head);
E 23
    	/*
D 23
D 24
D 25
	 *find first bit at which v and t->rn_key differ
E 25
I 25
	 * Find first bit at which v and t->rn_key differ
E 25
E 24
I 24
D 27
	 * Find first bit at which v and t->rn_key differ
E 27
I 27
	 *find first bit at which v and t->rn_key differ
E 27
E 24
E 23
I 23
	 * Find first bit at which v and t->rn_key differ
E 23
	 */
D 23
    {
D 2
	register char *cp2 = t->rn_key + head_off;
E 2
I 2
	register caddr_t cp2 = t->rn_key + head_off;
E 2
	register int cmp_res;
D 2
	char *cplim = v + vlen;
E 2
I 2
	caddr_t cplim = v + vlen;
E 2

	while (cp < cplim)
		if (*cp2++ != *cp++)
			goto on1;
	*dupentry = 1;
	return t;
on1:
	*dupentry = 0;
	cmp_res = (cp[-1] ^ cp2[-1]) & 0xff;
	for (b = (cp - v) << 3; cmp_res; b--)
		cmp_res >>= 1;
    }
    {
D 18
	register struct radix_node *p, *x = head;
E 18
I 18
	register struct radix_node *p, *x = top;
E 18
	cp = v;
E 23
I 23
	b = rn_unmapped_bits_matched(v, t->rn_key, head, vlen);
	if (b == vlen) {
		*dupentry = 1;
		return t;
	}
	/*
	 * Find appropriate node after which to insert new key
	 */
	p = t;
E 23
	do {
D 23
		p = x;
		if (cp[x->rn_off] & x->rn_bmask) 
			x = x->rn_r;
		else x = x->rn_l;
	} while (b > (unsigned) x->rn_b); /* x->rn_b < b && x->rn_b >= 0 */
E 23
I 23
		x = p;
		p = x->rn_p;
        } while (b <= p->rn_b);

E 23
#ifdef RN_DEBUG
	if (rn_debug)
D 24
D 25
		printf("Going In:\n"), traverse(p);
E 25
I 25
		log(LOG_DEBUG, "rn_insert: Going In:\n"), traverse(p);
E 25
E 24
I 24
D 27
		log(LOG_DEBUG, "rn_insert: Going In:\n"), traverse(p);
E 27
I 27
		printf("Going In:\n"), traverse(p);
E 27
E 24
#endif
D 20
	t = rn_newpair(v, b, nodes); tt = t->rn_l;
E 20
I 20
D 23
	t = rn_newpair(v_arg, b, nodes); tt = t->rn_l;
E 20
	if ((cp[p->rn_off] & p->rn_bmask) == 0)
E 23
I 23
	t = rn_newpair1(v, b, nodes, head);
	/*
	 * If we went to the left during the matching process,
	 * the spliced-in node will still be on the left.
	 */
	if (p->rn_l == x)
E 23
		p->rn_l = t;
	else
		p->rn_r = t;
D 23
	x->rn_p = t; t->rn_p = p; /* frees x, p as temp vars below */
	if ((cp[t->rn_off] & t->rn_bmask) == 0) {
E 23
I 23
	t->rn_p = p;
	/*
	 * If the first bit of the input string that didn't match
	 * was set, put the new leaf to the right of the new node. 
	 */
	if (cp[b >> 3] & search_bits[b & 7]) {
		t->rn_r = nodes; t->rn_l = x;
	} else
E 23
		t->rn_r = x;
D 23
	} else {
		t->rn_r = tt; t->rn_l = x;
	}
E 23
I 23
	x->rn_p = t;
E 23
#ifdef RN_DEBUG
	if (rn_debug)
D 24
D 25
		printf("Coming out:\n"), traverse(p);
E 25
I 25
		log(LOG_DEBUG, "rn_insert: Coming Out:\n"), traverse(p);
E 25
E 24
I 24
D 27
		log(LOG_DEBUG, "rn_insert: Coming Out:\n"), traverse(p);
E 27
I 27
		printf("Coming out:\n"), traverse(p);
E 27
E 24
#endif
D 23
    }
	return (tt);
E 23
I 23
	return (nodes);
E 23
}

I 23
/*
 * Here mostly for compatability's sake with
 * the previous networking code, which expects to find masks.
 */
E 23
struct radix_node *
I 6
D 20
rn_addmask(netmask, search, skip)
D 13
caddr_t netmask;
E 13
I 13
	caddr_t netmask;
E 20
I 20
D 23
rn_addmask(n_arg, search, skip)
E 20
	int search, skip;
I 20
	void *n_arg;
E 23
I 23
rn_masksubr(n_arg, v_arg, skip, head, len_p)
	void *n_arg, *v_arg;
	int skip, *len_p;
	struct radix_node_head *head;
E 23
E 20
E 13
{
I 20
D 23
	caddr_t netmask = (caddr_t)n_arg;
E 20
	register struct radix_node *x;
E 23
I 23
	caddr_t netmask = (caddr_t)n_arg, v = v_arg;
	register struct radix_node *x = rn_masktop;
E 23
	register caddr_t cp, cplim;
D 23
D 24
D 25
	register int b, mlen, j;
E 23
I 23
	register int b, j, mlen, vlen;
E 23
	int maskduplicated;
E 25
I 25
	register int b = 0, mlen, j;
	int maskduplicated, m0, isnormal;
	struct radix_node *saved_x;
	static int last_zeroed = 0;
E 25
E 24
I 24
D 27
	register int b = 0, mlen, j;
	int maskduplicated, m0, isnormal;
	struct radix_node *saved_x;
	static int last_zeroed = 0;
E 27
I 27
	register int b, mlen, j;
	int maskduplicated;
E 27
E 24
I 23
	struct radix_node *saved_x;
E 23

D 23
D 24
D 25
	mlen = *(u_char *)netmask;
	if (search) {
D 18
		x = rn_search(netmask, rn_maskhead);
E 18
I 18
		x = rn_search(netmask, rn_masktop);
E 18
		mlen = *(u_char *)netmask;
		if (Bcmp(netmask, x->rn_key, mlen) == 0)
			return (x);
E 25
I 25
	if ((mlen = *(u_char *)netmask) > max_keylen)
		mlen = max_keylen;
	if (skip == 0)
		skip = 1;
	if (mlen <= skip)
		return (mask_rnhead->rnh_nodes);
	if (skip > 1)
		Bcopy(rn_ones + 1, addmask_key + 1, skip - 1);
	if ((m0 = mlen) > skip)
		Bcopy(netmask + skip, addmask_key + skip, mlen - skip);
	/*
	 * Trim trailing zeroes.
	 */
	for (cp = addmask_key + mlen; (cp > addmask_key) && cp[-1] == 0;)
		cp--;
	mlen = cp - addmask_key;
	if (mlen <= skip) {
		if (m0 >= last_zeroed)
			last_zeroed = mlen;
		return (mask_rnhead->rnh_nodes);
E 25
E 24
I 24
D 27
	if ((mlen = *(u_char *)netmask) > max_keylen)
		mlen = max_keylen;
	if (skip == 0)
		skip = 1;
	if (mlen <= skip)
		return (mask_rnhead->rnh_nodes);
	if (skip > 1)
		Bcopy(rn_ones + 1, addmask_key + 1, skip - 1);
	if ((m0 = mlen) > skip)
		Bcopy(netmask + skip, addmask_key + skip, mlen - skip);
	/*
	 * Trim trailing zeroes.
	 */
	for (cp = addmask_key + mlen; (cp > addmask_key) && cp[-1] == 0;)
		cp--;
	mlen = cp - addmask_key;
	if (mlen <= skip) {
		if (m0 >= last_zeroed)
			last_zeroed = mlen;
		return (mask_rnhead->rnh_nodes);
E 27
I 27
	mlen = *(u_char *)netmask;
	if (search) {
		x = rn_search(netmask, rn_masktop);
		mlen = *(u_char *)netmask;
		if (Bcmp(netmask, x->rn_key, mlen) == 0)
			return (x);
E 27
E 24
E 23
I 23
	if (head == 0)
		head = mask_rnhead;
	if (netmask == 0) {
		if (*len_p)
			*len_p = VLEN(v, head);
		return 0;
E 23
	}
I 25
	if (m0 < last_zeroed)
		Bzero(addmask_key + m0, last_zeroed - m0);
	*addmask_key = last_zeroed = mlen;
	x = rn_search(addmask_key, rn_masktop);
	if (Bcmp(addmask_key, x->rn_key, mlen) != 0)
		x = 0;
	if (x || search)
		return (x);
E 25
I 24
D 27
	if (m0 < last_zeroed)
		Bzero(addmask_key + m0, last_zeroed - m0);
	*addmask_key = last_zeroed = mlen;
	x = rn_search(addmask_key, rn_masktop);
	if (Bcmp(addmask_key, x->rn_key, mlen) != 0)
		x = 0;
	if (x || search)
		return (x);
E 27
E 24
I 23
	if (skip > 0)
		for (j = skip << 3; j > ((unsigned)x->rn_b);)
			x = x->rn_r;
	x = rn_search(netmask, x);
	mlen = *(u_char *)netmask;
	if ((skip > mlen) ||
	    Bcmp(netmask + skip, x->rn_key + skip, mlen - skip) == 0)
		goto found;
E 23
D 15
	R_Malloc(x, struct radix_node *, MAXKEYLEN + 2 * sizeof (*x));
E 15
I 15
	R_Malloc(x, struct radix_node *, max_keylen + 2 * sizeof (*x));
E 15
D 24
D 25
	if (x == 0)
E 25
I 25
	if ((saved_x = x) == 0)
E 25
E 24
I 24
D 27
	if ((saved_x = x) == 0)
E 27
I 27
	if (x == 0)
E 27
E 24
		return (0);
I 23
	saved_x = x;
E 23
D 15
	Bzero(x, MAXKEYLEN + 2 * sizeof (*x));
E 15
I 15
	Bzero(x, max_keylen + 2 * sizeof (*x));
E 15
D 24
D 25
	cp = (caddr_t)(x + 2);
	Bcopy(netmask, cp, mlen);
D 23
	netmask = cp;
D 18
	x = rn_insert(netmask, rn_maskhead, &maskduplicated, x);
E 18
I 18
	x = rn_insert(netmask, mask_rnhead, &maskduplicated, x);
E 25
I 25
	netmask = cp = (caddr_t)(x + 2);
	Bcopy(addmask_key, cp, mlen);
	x = rn_insert(cp, mask_rnhead, &maskduplicated, x);
	if (maskduplicated) {
		log(LOG_ERR, "rn_addmask: mask impossibly already in tree");
		Free(saved_x);
		return (x);
	}
E 25
E 24
I 24
D 27
	netmask = cp = (caddr_t)(x + 2);
	Bcopy(addmask_key, cp, mlen);
	x = rn_insert(cp, mask_rnhead, &maskduplicated, x);
	if (maskduplicated) {
		log(LOG_ERR, "rn_addmask: mask impossibly already in tree");
		Free(saved_x);
		return (x);
	}
E 27
I 27
	cp = (caddr_t)(x + 2);
	Bcopy(netmask, cp, mlen);
	netmask = cp;
	x = rn_insert(netmask, mask_rnhead, &maskduplicated, x);
E 27
E 24
E 18
	/*
D 24
D 25
	 * Calculate index of mask.
E 25
I 25
	 * Calculate index of mask, and check for normalcy.
E 25
E 24
I 24
D 27
	 * Calculate index of mask, and check for normalcy.
E 27
I 27
	 * Calculate index of mask.
E 27
E 24
	 */
D 24
D 25
	cplim = netmask + mlen;
	for (cp = netmask + skip; cp < cplim; cp++)
		if (*(u_char *)cp != 0xff)
			break;
	b = (cp - netmask) << 3;
E 25
I 25
	cplim = netmask + mlen; isnormal = 1;
	for (cp = netmask + skip; (cp < cplim) && *(u_char *)cp == 0xff;)
		cp++;
E 25
E 24
I 24
D 27
	cplim = netmask + mlen; isnormal = 1;
	for (cp = netmask + skip; (cp < cplim) && *(u_char *)cp == 0xff;)
		cp++;
E 27
I 27
	cplim = netmask + mlen;
	for (cp = netmask + skip; cp < cplim; cp++)
		if (*(u_char *)cp != 0xff)
			break;
	b = (cp - netmask) << 3;
E 27
E 24
	if (cp != cplim) {
D 24
D 25
		if (*cp != 0) {
			gotOddMasks = 1;
			for (j = 0x80; j; b++, j >>= 1)  
				if ((j & *cp) == 0)
					break;
		}
E 25
I 25
		for (j = 0x80; (j & *cp) != 0; j >>= 1)  
			b++;
		if (*cp != normal_chars[b] || cp != (cplim - 1))
			isnormal = 0;
E 25
E 24
I 24
D 27
		for (j = 0x80; (j & *cp) != 0; j >>= 1)  
			b++;
		if (*cp != normal_chars[b] || cp != (cplim - 1))
			isnormal = 0;
E 27
I 27
		if (*cp != 0) {
			gotOddMasks = 1;
			for (j = 0x80; j; b++, j >>= 1)  
				if ((j & *cp) == 0)
					break;
		}
E 27
E 24
E 23
I 23
	if (skip > 1) 
		Bcopy(rn_ones, cp + 1, skip - 1);
	maskduplicated = 0;
	x = rn_insert(cp, mask_rnhead, &maskduplicated, x);
	mlen = rn_unmapped_bits_matched(cp, rn_ones, head, mlen << 3);
	if (maskduplicated) {
		printf("rn_addmask1: impossible dup");
		Free(saved_x);
	} else {
		x->rn_b = -1 - mlen;
E 23
	}
I 25
	b += (cp - netmask) << 3;
E 25
I 24
D 27
	b += (cp - netmask) << 3;
E 27
E 24
D 23
	x->rn_b = -1 - b;
I 25
	if (isnormal)
		x->rn_flags |= RNF_NORMAL;
E 25
I 24
D 27
	if (isnormal)
		x->rn_flags |= RNF_NORMAL;
E 27
E 24
E 23
I 23
found:
	if (len_p)
		*len_p = (-1 - x->rn_b) - head->rnh_offset;
E 23
	return (x);
}

I 25
static int	/* XXX: arbitrary ordering for non-contiguous masks */
rn_lexobetter(m_arg, n_arg)
	void *m_arg, *n_arg;
{
	register u_char *mp = m_arg, *np = n_arg, *lim;

	if (*mp > *np)
		return 1;  /* not really, but need to check longer one first */
	if (*mp == *np) 
		for (lim = mp + *mp; mp < lim;)
			if (*mp++ > *np++)
				return 1;
	return 0;
}

static struct radix_mask *
rn_new_radix_mask(tt, next)
	register struct radix_node *tt;
	register struct radix_mask *next;
{
	register struct radix_mask *m;

	MKGet(m);
	if (m == 0) {
		log(LOG_ERR, "Mask for route not entered\n");
		return (0);
	}
	Bzero(m, sizeof *m);
	m->rm_b = tt->rn_b;
	m->rm_flags = tt->rn_flags;
	if (tt->rn_flags & RNF_NORMAL)
		m->rm_leaf = tt;
	else
		m->rm_mask = tt->rn_mask;
	m->rm_mklist = next;
	tt->rn_mklist = m;
	return m;
}

E 25
I 24
D 27
static int	/* XXX: arbitrary ordering for non-contiguous masks */
rn_lexobetter(m_arg, n_arg)
	void *m_arg, *n_arg;
{
	register u_char *mp = m_arg, *np = n_arg, *lim;

	if (*mp > *np)
		return 1;  /* not really, but need to check longer one first */
	if (*mp == *np) 
		for (lim = mp + *mp; mp < lim;)
			if (*mp++ > *np++)
				return 1;
	return 0;
}

static struct radix_mask *
rn_new_radix_mask(tt, next)
	register struct radix_node *tt;
	register struct radix_mask *next;
{
	register struct radix_mask *m;

	MKGet(m);
	if (m == 0) {
		log(LOG_ERR, "Mask for route not entered\n");
		return (0);
	}
	Bzero(m, sizeof *m);
	m->rm_b = tt->rn_b;
	m->rm_flags = tt->rn_flags;
	if (tt->rn_flags & RNF_NORMAL)
		m->rm_leaf = tt;
	else
		m->rm_mask = tt->rn_mask;
	m->rm_mklist = next;
	tt->rn_mklist = m;
	return m;
}

E 27
E 24
D 18
struct radix_node *
E 18
I 18
D 20
static struct radix_node *
E 18
E 6
rn_addroute(v, netmask, head, treenodes)
D 6
	struct radix_node *head;
E 6
I 6
D 13
struct radix_node *head;
E 6
D 2
	char *netmask, *v;
E 2
I 2
	caddr_t netmask, v;
E 13
I 13
	caddr_t v, netmask;
E 20
I 20
struct radix_node *
rn_addroute(v_arg, n_arg, head, treenodes)
	void *v_arg, *n_arg;
E 20
D 18
	struct radix_node *head;
E 18
I 18
	struct radix_node_head *head;
E 18
E 13
E 2
	struct radix_node treenodes[2];
{
I 20
	caddr_t v = (caddr_t)v_arg, netmask = (caddr_t)n_arg;
E 20
D 22
	register int j;
D 2
	register char *cp;
E 2
I 2
	register caddr_t cp;
E 22
E 2
D 23
D 28
	register struct radix_node *t, *x, *tt;
E 28
I 28
	register struct radix_node *t, *x = 0, *tt;
E 28
I 18
	struct radix_node *saved_tt, *top = head->rnh_treetop;
E 23
I 23
	register struct radix_node *m, *us = treenodes;
	struct radix_node *t, *tt, *x, *base, *top = head->rnh_treetop;
	struct radix_node *s /*sibling*/, *p /*parent*/, **mp;
E 23
E 18
D 28
	short b = 0, b_leaf;
E 28
I 28
	short b = 0, b_leaf = 0;
E 28
D 6
	int vlen = *(u_char *)v, maskduplicated = 0, mlen, keyduplicated;
E 6
I 6
D 22
	int vlen = *(u_char *)v, mlen, keyduplicated;
E 6
D 2
	char *cplim; unsigned char *maskp;
E 2
I 2
	caddr_t cplim; unsigned char *maskp;
E 22
I 22
D 23
D 24
D 25
	int mlen, keyduplicated;
	caddr_t cplim;
E 25
I 25
	int keyduplicated;
	caddr_t mmask;
E 25
E 24
I 24
D 27
	int keyduplicated;
	caddr_t mmask;
E 27
I 27
	int mlen, keyduplicated;
	caddr_t cplim;
E 27
E 24
E 22
E 2
	struct radix_mask *m, **mp;
E 23
I 23
	int masklen, masklen_leaf, mlen, keyduplicated = 0;
E 23
D 18
	struct radix_node *saved_tt;
E 18

	/*
D 23
	 * In dealing with non-contiguous masks, there may be
	 * many different routes which have the same mask.
	 * We will find it useful to have a unique pointer to
	 * the mask to speed avoiding duplicate references at
	 * nodes and possibly save time in calculating indices.
E 23
I 23
	 * This version assumes contiguous masks and only cares about
	 * the index of the mask, if present.
E 23
	 */
D 23
	if (netmask)  {
D 18
		x = rn_search(netmask, rn_maskhead);
E 18
I 18
D 24
D 25
		x = rn_search(netmask, rn_masktop);
E 18
		mlen = *(u_char *)netmask;
D 6
		if (Bcmp(netmask, x->rn_key, mlen) == 0) {
			maskduplicated = 1;
			netmask = x->rn_key;
			b = -1 - x->rn_b;
I 4
		} else {
			maskduplicated = 0;
			R_Malloc(x, struct radix_node *, MAXKEYLEN + 2 * sizeof (*x));
E 6
I 6
		if (Bcmp(netmask, x->rn_key, mlen) != 0) {
D 18
			x = rn_addmask(netmask, 0, head->rn_off);
E 18
I 18
			x = rn_addmask(netmask, 0, top->rn_off);
E 18
E 6
			if (x == 0)
				return (0);
D 6
			Bzero(x, MAXKEYLEN + 2 * sizeof (*x));
			cp = (caddr_t)(x + 2);
			Bcopy(netmask, cp, mlen);
			netmask = cp;
			x = rn_insert(netmask, rn_maskhead, &maskduplicated, x);
			/*
			 * Calculate index of mask.
			 */
			cplim = netmask + vlen;
			for (cp = netmask + head->rn_off; cp < cplim; cp++)
				if (*(u_char *)cp != 0xff)
					break;
			b = (cp - netmask) << 3;
			if (cp != cplim) {
				if (*cp != 0) {
					gotOddMasks = 1;
					for (j = 0x80; j; b++, j >>= 1)  
						if ((j & *cp) == 0)
							break;
				}
			}
			x->rn_b = -1 - b;
E 6
E 4
		}
I 6
		netmask = x->rn_key;
E 25
I 25
		if ((x = rn_addmask(netmask, 0, top->rn_off)) == 0)
			return (0);
		b_leaf = x->rn_b;
E 25
E 24
I 24
D 27
		if ((x = rn_addmask(netmask, 0, top->rn_off)) == 0)
			return (0);
		b_leaf = x->rn_b;
E 24
		b = -1 - x->rn_b;
E 27
I 27
		x = rn_search(netmask, rn_masktop);
		mlen = *(u_char *)netmask;
		if (Bcmp(netmask, x->rn_key, mlen) != 0) {
			x = rn_addmask(netmask, 0, top->rn_off);
			if (x == 0)
				return (0);
		}
E 27
I 25
		netmask = x->rn_key;
E 25
I 24
		netmask = x->rn_key;
I 27
		b = -1 - x->rn_b;
E 27
E 24
E 6
	}
E 23
I 23
	(void) rn_masksubr(v_arg, n_arg, (head->rnh_offset >> 3), head, &masklen);
	masklen_leaf = -1 - masklen;
	base = tt = rn_insert(v, head, &keyduplicated, treenodes);
	t = p = tt->rn_p;
E 23
	/*
	 * Deal with duplicated keys: attach node to previous instance
I 23
	 * We sort the nodes so that the longest mask comes first.
E 23
	 */
D 23
	saved_tt = tt = rn_insert(v, head, &keyduplicated, treenodes);
E 23
	if (keyduplicated) {
D 4
		if (tt->rn_mask == netmask)
			return (0);
		for (; tt->rn_dupedkey; tt = tt->rn_dupedkey)
E 4
I 4
D 23
D 24
D 25
		do {
E 25
I 25
		for (t = tt; tt; t = tt, tt = tt->rn_dupedkey) {
E 25
E 24
I 24
D 27
		for (t = tt; tt; t = tt, tt = tt->rn_dupedkey) {
E 24
E 4
			if (tt->rn_mask == netmask)
				return (0);
E 27
I 27
		do {
			t = tt;
E 27
I 4
D 24
D 25
			t = tt;
E 25
E 24
I 11
			if (netmask == 0 ||
D 24
D 25
			    (tt->rn_mask && rn_refines(netmask, tt->rn_mask)))
E 25
I 25
			    (tt->rn_mask &&
			     ((b_leaf < tt->rn_b) || /* index(netmask) > node */
			       rn_refines(netmask, tt->rn_mask) ||
			       rn_lexobetter(netmask, tt->rn_mask))))
E 25
E 24
I 24
D 27
			    (tt->rn_mask &&
			     ((b_leaf < tt->rn_b) || /* index(netmask) > node */
			       rn_refines(netmask, tt->rn_mask) ||
			       rn_lexobetter(netmask, tt->rn_mask))))
E 27
I 27
			    (tt->rn_mask && rn_refines(netmask, tt->rn_mask)))
E 27
E 24
				break;
E 11
D 24
D 25
		} while (tt = tt->rn_dupedkey);
E 25
I 25
		}
E 25
E 24
I 24
D 27
		}
E 27
I 27
		} while (tt = tt->rn_dupedkey);
E 27
E 24
E 23
E 4
		/*
D 23
		 * If the mask is not duplicated, we wouldn't
		 * find it among possible duplicate key entries
		 * anyway, so the above test doesn't hurt.
		 *
D 11
		 * XXX: we really ought to sort the masks
E 11
I 11
D 14
		 * We sort the masks
E 11
		 * for a duplicated key the same way as in a masklist.
		 * It is an unfortunate pain having to relocate
E 14
I 14
		 * We sort the masks for a duplicated key the same way as
		 * in a masklist -- most specific to least specific.
		 * This may require the unfortunate nuisance of relocating
E 14
		 * the head of the list.
I 28
		 *
		 * We also reverse, or doubly link the list through the
		 * parent pointer.
E 28
E 23
I 23
		 * Examine each node and continue past any where the
		 * mask length is greater than the new one;
		 * since we are storing -1 - masklength, the sense
		 * of the test is reversed.
E 23
		 */
D 4
		tt->rn_dupedkey = treenodes;
		tt = treenodes;
E 4
I 4
D 11
		t->rn_dupedkey = tt = treenodes;
E 11
I 11
D 23
D 24
D 25
		if (tt && t == saved_tt) {
E 25
I 25
		if (tt == saved_tt) {
E 25
E 24
I 24
D 27
		if (tt == saved_tt) {
E 27
I 27
		if (tt && t == saved_tt) {
E 27
E 24
			struct	radix_node *xx = x;
E 23
I 23
		for (; tt && (tt->rn_b <= masklen_leaf);
					x = tt, tt = tt->rn_dupedkey)
			if (tt->rn_mask == netmask)
				return (0);  /* mask is also duplicated */
		if (tt == base) {
E 23
			/* link in at head of list */
D 23
			(tt = treenodes)->rn_dupedkey = t;
			tt->rn_flags = t->rn_flags;
			tt->rn_p = x = t->rn_p;
I 28
			t->rn_p = tt;
E 28
			if (x->rn_l == t) x->rn_l = tt; else x->rn_r = tt;
			saved_tt = tt; x = xx;
E 23
I 23
			us->rn_dupedkey = tt;
			us->rn_p = p;
			if (p->rn_l == tt)
				p->rn_l = us; else p->rn_r = us;
			base = us;
E 23
		} else {
D 23
			(tt = treenodes)->rn_dupedkey = t->rn_dupedkey;
			t->rn_dupedkey = tt;
I 28
			tt->rn_p = t;
			if (tt->rn_dupedkey)
				tt->rn_dupedkey->rn_p = tt;
E 28
E 23
I 23
			us->rn_dupedkey = x->rn_dupedkey;
			x->rn_dupedkey = us;
E 23
		}
E 11
E 4
#ifdef RN_DEBUG
		t=tt+1; tt->rn_info = rn_nodenum++; t->rn_info = rn_nodenum++;
		tt->rn_twin = t; tt->rn_ybro = rn_clist; rn_clist = tt;
#endif
I 27
		t = saved_tt;
E 27
D 23
D 24
D 25
		t = saved_tt;
E 25
E 24
D 4
		tt->rn_key = t->rn_key;
		tt->rn_b = t->rn_b;
E 4
I 4
		tt->rn_key = (caddr_t) v;
		tt->rn_b = -1;
E 4
D 24
D 25
		tt->rn_flags = t->rn_flags & ~RNF_ROOT;
E 25
I 25
		tt->rn_flags = RNF_ACTIVE;
E 25
E 24
I 24
D 27
		tt->rn_flags = RNF_ACTIVE;
E 27
I 27
		tt->rn_flags = t->rn_flags & ~RNF_ROOT;
E 27
E 24
E 23
I 23
		us->rn_key = (caddr_t) v;
		us->rn_flags = RNF_ACTIVE;
E 23
	}
I 23
	us->rn_b = masklen_leaf;
	us->rn_mask = netmask;
E 23
	/*
D 23
	 * Put mask in tree.
E 23
I 23
	 * Annotate tree about masks.
E 23
	 */
D 4
	if (netmask == 0)
		goto on1;
	if (maskduplicated == 0) {
D 2
		Malloc(x, struct radix_node *, MAXKEYLEN + 2 * sizeof (*x));
E 2
I 2
		R_Malloc(x, struct radix_node *, MAXKEYLEN + 2 * sizeof (*x));
E 2
		if (x == 0)
			return (0);
		Bzero(x, MAXKEYLEN + 2 * sizeof (*x));
D 2
		cp = (char *)(x + 2);
E 2
I 2
		cp = (caddr_t)(x + 2);
E 2
D 3
		bcopy(netmask, cp, mlen);
E 3
I 3
		Bcopy(netmask, cp, mlen);
E 3
		netmask = cp;
		x = rn_insert(netmask, rn_maskhead, &maskduplicated, x);
		/*
		 * Calculate index of mask.
		 */
		cplim = netmask + vlen;
		for (cp = netmask + head->rn_off; cp < cplim; cp++)
			if (*(u_char *)cp != 0xff)
				break;
		b = (cp - netmask) << 3;
		if (cp != cplim) {
			if (*cp != 0) {
				gotOddMasks = 1;
				for (j = 0x80; j; b++, j >>= 1)  
					if ((j & *cp) == 0)
						break;
			}
		}
		x->rn_b = -1 - b;
E 4
I 4
D 23
	if (netmask) {
		tt->rn_mask = netmask;
		tt->rn_b = x->rn_b;
I 25
D 26
		tt->rn_flags = x->rn_flags;
E 26
I 26
		tt->rn_flags |= x->rn_flags & RNF_NORMAL;
E 26
E 25
I 24
D 27
		tt->rn_flags = x->rn_flags;
E 27
E 24
E 4
	}
D 4
	/*
	 * Set up usual parameters
	 */
	tt->rn_mask = netmask;
	tt->rn_b = x->rn_b;
on1:
E 4
	t = saved_tt->rn_p;
I 25
	if (keyduplicated)
		goto on2;
E 25
I 24
D 27
	if (keyduplicated)
		goto on2;
E 27
E 24
	b_leaf = -1 - t->rn_b;
	if (t->rn_r == saved_tt) x = t->rn_l; else x = t->rn_r;
	/* Promote general routes from below */
	if (x->rn_b < 0) { 
I 25
	    for (mp = &t->rn_mklist; x; x = x->rn_dupedkey)
E 25
I 24
D 27
	    for (mp = &t->rn_mklist; x; x = x->rn_dupedkey)
E 27
E 24
D 8
		if (x->rn_mask && (x->rn_b >= b_leaf)) {
E 8
I 8
		if (x->rn_mask && (x->rn_b >= b_leaf) && x->rn_mklist == 0) {
E 8
D 24
D 25
			MKGet(m);
			if (m) {
				Bzero(m, sizeof *m);
				m->rm_b = x->rn_b;
				m->rm_mask = x->rn_mask;
D 4
				t->rn_mklist = m;
E 4
I 4
				x->rn_mklist = t->rn_mklist = m;
E 23
I 23
	b = p->rn_b;
	b_leaf = -1 - b;
	if (p->rn_r == base) s = p->rn_l; else s = p->rn_r;
	if (s->rn_b < 0) { 
	    if (s->rn_mask || s->rn_dupedkey) {
		/*
		 * There may be network routes among our sibling's
		 * dupedkey chain that previously couldn't be lifted
		 * which should now be added to the new parent.
		 */
		int previous_index = p->rn_p->rn_b;
		mp = &(p->rn_mklist);
		for (m = s; m; m = m->rn_dupedkey) {
			if (m->rn_mask) {
				int m_index = -1 - m->rn_b;
				if (previous_index < m_index && b >= m_index) {
					*mp = m;
					mp = &(m->rn_mklist);
				}
E 23
E 4
			}
E 25
I 25
D 28
			if (*mp = m = rn_new_radix_mask(x, 0))
E 28
I 28
			*mp = m = rn_new_radix_mask(x, 0);
			if (m)
E 28
				mp = &m->rm_mklist;
E 25
E 24
I 24
D 27
			if (*mp = m = rn_new_radix_mask(x, 0))
				mp = &m->rm_mklist;
E 27
I 27
			MKGet(m);
			if (m) {
				Bzero(m, sizeof *m);
				m->rm_b = x->rn_b;
				m->rm_mask = x->rn_mask;
				x->rn_mklist = t->rn_mklist = m;
			}
E 27
E 24
I 23

E 23
		}
D 23
	} else if (x->rn_mklist) {
E 23
I 23
	    }
	} else if (s->rn_mklist) {
E 23
		/*
		 * Skip over masks whose index is > that of new node
		 */
D 23
D 28
		for (mp = &x->rn_mklist; m = *mp; mp = &m->rm_mklist)
E 28
I 28
		for (mp = &x->rn_mklist; (m = *mp); mp = &m->rm_mklist)
E 28
			if (m->rm_b >= b_leaf)
E 23
I 23
		for (mp = &(s->rn_mklist); m = *mp; mp = &m->rn_mklist)
			if (m->rn_b >= b_leaf)
E 23
				break;
D 23
		t->rn_mklist = m; *mp = 0;
E 23
I 23
		p->rn_mklist = m; *mp = 0;
E 23
	}
I 25
on2:
E 25
I 24
D 27
on2:
E 27
E 24
	/* Add new route to highest possible ancestor's list */
D 23
	if ((netmask == 0) || (b > t->rn_b ))
		return tt; /* can't lift at all */
	b_leaf = tt->rn_b;
E 23
I 23
	if ((netmask == 0) || (masklen > p->rn_b ))
		return us; /* can't lift at all */
E 23
	do {
		x = t;
		t = t->rn_p;
D 18
	} while (b <= t->rn_b && x != head);
E 18
I 18
D 23
	} while (b <= t->rn_b && x != top);
E 23
I 23
	} while (masklen <= t->rn_b && x != top);
E 23
E 18
	/*
	 * Search through routes associated with node to
	 * insert new route according to index.
D 24
D 25
	 * For nodes of equal index, place more specific
	 * masks first.
E 25
I 25
	 * Need same criteria as when sorting dupedkeys to avoid
	 * double loop on deletion.
E 25
E 24
I 24
D 27
	 * Need same criteria as when sorting dupedkeys to avoid
	 * double loop on deletion.
E 27
I 27
	 * For nodes of equal index, place more specific
	 * masks first.
E 27
E 24
	 */
I 27
	cplim = netmask + mlen;
E 27
D 23
D 24
D 25
	cplim = netmask + mlen;
E 25
E 24
D 28
	for (mp = &x->rn_mklist; m = *mp; mp = &m->rm_mklist) {
E 28
I 28
	for (mp = &x->rn_mklist; (m = *mp); mp = &m->rm_mklist) {
E 28
		if (m->rm_b < b_leaf)
E 23
I 23
	for (mp = &x->rn_mklist; m = *mp; mp = &m->rn_mklist) {
		if (m->rn_b > masklen_leaf)
E 23
			continue;
D 23
		if (m->rm_b > b_leaf)
E 23
I 23
		if (m->rn_b < masklen_leaf)
E 23
			break;
D 23
D 24
D 25
		if (m->rm_mask == netmask) {
E 25
I 25
		if (m->rm_flags & RNF_NORMAL) {
			mmask = m->rm_leaf->rn_mask;
			if (tt->rn_flags & RNF_NORMAL) {
				log(LOG_ERR,
				   "Non-unique normal route, mask not entered");
				return tt;
			}
		} else
			mmask = m->rm_mask;
		if (mmask == netmask) {
E 25
E 24
I 24
D 27
		if (m->rm_flags & RNF_NORMAL) {
			mmask = m->rm_leaf->rn_mask;
			if (tt->rn_flags & RNF_NORMAL) {
				log(LOG_ERR,
				   "Non-unique normal route, mask not entered");
				return tt;
			}
		} else
			mmask = m->rm_mask;
		if (mmask == netmask) {
E 27
I 27
		if (m->rm_mask == netmask) {
E 27
E 24
			m->rm_refs++;
			tt->rn_mklist = m;
			return tt;
E 23
I 23
		if (m->rn_b == masklen_leaf) {
			printf("rn_addroute: impossible duplicate mask\n");
			return us;
E 23
		}
D 11
		maskp = (u_char *)m->rm_mask;
		for (cp = netmask; cp < cplim; cp++)
			if (*(u_char *)cp > *maskp++)
				goto on2;
E 11
I 11
D 23
D 24
D 25
		if (rn_refines(netmask, m->rm_mask))
E 25
I 25
		if (rn_refines(netmask, mmask) || rn_lexobetter(netmask, mmask))
E 25
E 24
I 24
D 27
		if (rn_refines(netmask, mmask) || rn_lexobetter(netmask, mmask))
E 27
I 27
		if (rn_refines(netmask, m->rm_mask))
E 27
E 24
			break;
E 23
E 11
	}
D 11
on2:
E 11
D 23
D 24
D 25
	MKGet(m);
	if (m == 0) {
		printf("Mask for route not entered\n");
		return (tt);
	}
	Bzero(m, sizeof *m);
	m->rm_b = b_leaf;
	m->rm_mask = netmask;
	m->rm_mklist = *mp;
	*mp = m;
	tt->rn_mklist = m;
E 25
I 25
	*mp = rn_new_radix_mask(tt, *mp);
E 25
E 24
I 24
D 27
	*mp = rn_new_radix_mask(tt, *mp);
E 27
I 27
	MKGet(m);
	if (m == 0) {
		printf("Mask for route not entered\n");
		return (tt);
	}
	Bzero(m, sizeof *m);
	m->rm_b = b_leaf;
	m->rm_mask = netmask;
	m->rm_mklist = *mp;
	*mp = m;
	tt->rn_mklist = m;
E 27
E 24
	return tt;
E 23
I 23
	*mp = us;
	us->rn_mklist = m;
	return us;
E 23
}

D 18
struct radix_node *
E 18
I 18
D 20
static struct radix_node *
E 18
rn_delete(v, netmask, head)
D 2
	char *v, *netmask;
E 2
I 2
	caddr_t v, netmask;
E 20
I 20
struct radix_node *
D 23
rn_delete(v_arg, netmask_arg, head)
	void *v_arg, *netmask_arg;
E 23
I 23
rn_delete(v_arg, n_arg, head)
	void *v_arg, *n_arg;
E 23
E 20
E 2
D 18
	struct radix_node *head;
E 18
I 18
	struct radix_node_head *head;
E 18
{
I 27
	register struct radix_node *t, *x, *tt;
	struct radix_node *dupedkey;
	caddr_t v, netmask;
	int b, head_off, vlen;

	v = v_arg;
	x = head->rnh_treetop;
	tt = rn_search(v, x);
	head_off = x->rn_off;
	vlen =  *(u_char *)v;
	if (tt == 0 ||
	    Bcmp(v + head_off, tt->rn_key + head_off, vlen - head_off))
		return (0);
	/*
	 * Check for possiblity of key being duped in tree.
	 */
	if (dupedkey = tt->rn_dupedkey) {
		if (netmask_arg) 
			netmask = rn_search(netmask_arg, rn_masktop)->rn_key;
		else
			netmask = 0;
		while (tt->rn_mask != netmask)
			if ((tt = tt->rn_dupedkey) == 0)
				return (0);
	}
	return (rn_delete1(tt, head));
}

struct radix_node *
rn_delete1(rn, head)
	struct radix_node *rn;
	struct radix_node_head *head;
{
E 27
D 18
	register struct radix_node *t, *p, *x = head;
E 18
I 18
D 20
	register struct radix_node *t, *p, *x = head->rnh_treetop;
E 18
	register struct radix_node *tt = rn_search(v, x);
	int b, head_off = x->rn_off, vlen =  * (u_char *) v;
E 20
I 20
	register struct radix_node *t, *p, *x, *tt;
E 20
D 4
	struct radix_mask *m, **mp;
E 4
I 4
D 23
	struct radix_mask *m, *saved_m, **mp;
E 4
D 18
	struct radix_node *dupedkey, *saved_tt = tt;
E 18
I 18
D 20
	struct radix_node *dupedkey, *saved_tt = tt, *top = x;
E 20
I 20
	struct radix_node *dupedkey, *saved_tt, *top;
D 27
	caddr_t v, netmask;
E 27
I 27
	caddr_t v, netmask = 0;
E 27
	int b, head_off, vlen;
E 23
I 23
	struct radix_node *m, *saved_m, **mp;
	struct radix_node *dupedkey, *base, *top = head->rnh_treetop;
	int b, head_off = head->rnh_offset >> 3, masklen, masklen_leaf;
	int vlen = VLEN(v_arg, head) >> 3;
	caddr_t v = v_arg;
E 23
E 20
E 18

I 20
D 23
D 27
	v = v_arg;
	netmask = netmask_arg;
E 27
I 27
	v = rn->rn_key;
	netmask = rn->rn_mask;
E 27
	x = head->rnh_treetop;
	tt = rn_search(v, x);
	head_off = x->rn_off;
	vlen =  *(u_char *)v;
	saved_tt = tt;
	top = x;
E 20
	if (tt == 0 ||
	    Bcmp(v + head_off, tt->rn_key + head_off, vlen - head_off))
E 23
I 23
	base = tt = rn_search_unmapped(v_arg, head);
	if (tt == 0 || Bcmp(v + head_off, tt->rn_key + head_off, vlen))
E 23
		return (0);
I 27

E 27
D 23
	/*
	 * Delete our route from mask lists.
	 */
E 23
I 23
	p = t = tt->rn_p;
	(void) rn_masksubr(v_arg, n_arg, head_off, head, &masklen);
	masklen_leaf = -1 - masklen;
E 23
D 24
D 25
	if (dupedkey = tt->rn_dupedkey) {
D 23
		if (netmask) 
D 18
			netmask = rn_search(netmask, rn_maskhead)->rn_key;
E 18
I 18
			netmask = rn_search(netmask, rn_masktop)->rn_key;
E 25
I 25
	if (netmask) {
		if ((x = rn_addmask(netmask, 1, head_off)) == 0)
			return (0);
		netmask = x->rn_key;
E 25
E 24
I 24
D 27
	if (netmask) {
		if ((x = rn_addmask(netmask, 1, head_off)) == 0)
			return (0);
		netmask = x->rn_key;
E 27
I 27
	if (dupedkey = tt->rn_dupedkey) {
E 27
E 24
E 18
D 9
		for (; tt->rn_mask != netmask; tt = tt->rn_dupedkey)
			if (tt == 0)
E 9
I 9
		while (tt->rn_mask != netmask)
E 23
I 23
		while (tt->rn_b != masklen_leaf)
E 23
			if ((tt = tt->rn_dupedkey) == 0)
E 9
				return (0);
	}
D 4
	if (tt->rn_mask == 0)
E 4
I 4
D 23
	if (tt->rn_mask == 0 || (saved_m = m = tt->rn_mklist) == 0)
E 4
		goto on1;
D 4
	if ((m = tt->rn_mklist) && --m->rm_refs >= 0)
E 4
I 4
D 24
D 25
	if (m->rm_mask != tt->rn_mask) {
		printf("rn_delete: inconsistent annotation\n");
E 4
		goto on1;
E 25
I 25
	if (tt->rn_flags & RNF_NORMAL) {
		if (m->rm_leaf != tt || m->rm_refs > 0) {
			log(LOG_ERR, "rn_delete: inconsistent annotation\n");
			return 0;  /* dangling ref could cause disaster */
		}
	} else { 
		if (m->rm_mask != tt->rn_mask) {
			log(LOG_ERR, "rn_delete: inconsistent annotation\n");
			goto on1;
		}
		if (--m->rm_refs >= 0)
			goto on1;
E 25
E 24
I 24
D 27
	if (tt->rn_flags & RNF_NORMAL) {
		if (m->rm_leaf != tt || m->rm_refs > 0) {
			log(LOG_ERR, "rn_delete: inconsistent annotation\n");
			return 0;  /* dangling ref could cause disaster */
		}
	} else { 
		if (m->rm_mask != tt->rn_mask) {
			log(LOG_ERR, "rn_delete: inconsistent annotation\n");
			goto on1;
		}
		if (--m->rm_refs >= 0)
			goto on1;
E 27
I 27
	if (m->rm_mask != tt->rn_mask) {
		printf("rn_delete: inconsistent annotation\n");
		goto on1;
E 27
E 24
I 4
	}
I 27
	if (--m->rm_refs >= 0)
		goto on1;
E 27
D 24
D 25
	if (--m->rm_refs >= 0)
		goto on1;
E 25
E 24
E 4
	b = -1 - tt->rn_b;
	t = saved_tt->rn_p;
	if (b > t->rn_b)
E 23
I 23
	/*
	 * Delete our route from mask lists.
	 */
	if (tt->rn_mask == 0 || masklen > t->rn_b)
E 23
		goto on1; /* Wasn't lifted at all */
	do {
D 23
		x = t;
		t = t->rn_p;
D 18
	} while (b <= t->rn_b && x != head);
E 18
I 18
	} while (b <= t->rn_b && x != top);
E 18
D 28
	for (mp = &x->rn_mklist; m = *mp; mp = &m->rm_mklist)
E 28
I 28
	for (mp = &x->rn_mklist; (m = *mp); mp = &m->rm_mklist)
E 28
D 4
		if (m->rm_mask == tt->rn_mask)
			break;
	if (m) {
		if (m->rm_refs < 0) {
E 4
I 4
		if (m == saved_m) {
E 4
			*mp = m->rm_mklist;
			MKFree(m);
E 23
I 23
		x = p;
		p = p->rn_p;
	} while (masklen <= p->rn_b && x != top);
	for (mp = &x->rn_mklist; m = *mp; mp = &m->rn_mklist)
		if (m == tt) {
			*mp = tt->rn_mklist;
E 23
I 4
			break;
E 4
		}
D 4
	} else
		printf("rn_delete: couldn't find our mask\n");
E 4
I 4
D 24
D 25
	if (m == 0)
		printf("rn_delete: couldn't find our annotation\n");
E 25
I 25
	if (m == 0) {
		log(LOG_ERR, "rn_delete: couldn't find our annotation\n");
		if (tt->rn_flags & RNF_NORMAL)
			return (0); /* Dangling ref to us */
	}
E 25
E 24
I 24
D 27
	if (m == 0) {
		log(LOG_ERR, "rn_delete: couldn't find our annotation\n");
		if (tt->rn_flags & RNF_NORMAL)
			return (0); /* Dangling ref to us */
	}
E 27
I 27
	if (m == 0)
		printf("rn_delete: couldn't find our annotation\n");
E 27
E 24
E 4
on1:
	/*
	 * Eliminate us from tree
	 */
	if (tt->rn_flags & RNF_ROOT)
		return (0);
#ifdef RN_DEBUG
	/* Get us out of the creation list */
	for (t = rn_clist; t && t->rn_ybro != tt; t = t->rn_ybro) {}
	if (t) t->rn_ybro = tt->rn_ybro;
D 19
#endif RN_DEBUG
E 19
I 19
#endif
E 19
D 23
	t = tt->rn_p;
E 23
D 24
D 25
	if (dupedkey) {
E 25
I 25
D 28
	if (dupedkey = saved_tt->rn_dupedkey) {
E 28
I 28
	dupedkey = saved_tt->rn_dupedkey;
	if (dupedkey) {
		/*
		 * Here, tt is the deletion target, and
		 * saved_tt is the head of the dupedkey chain.
		 */
E 28
E 25
E 24
I 24
D 27
	if (dupedkey = saved_tt->rn_dupedkey) {
E 27
I 27
	if (dupedkey) {
E 27
E 24
D 23
		if (tt == saved_tt) {
E 23
I 23
		if (tt == base) {
E 23
			x = dupedkey; x->rn_p = t;
			if (t->rn_l == tt) t->rn_l = x; else t->rn_r = x;
I 11
		} else {
I 28
			/* find node in front of tt on the chain */
E 28
D 23
			for (x = p = saved_tt; p && p->rn_dupedkey != tt;)
				p = p->rn_dupedkey;
D 28
			if (p) p->rn_dupedkey = tt->rn_dupedkey;
E 23
I 23
			for (x = base; x && x->rn_dupedkey != tt;)
				x = x->rn_dupedkey;
			if (x) x->rn_dupedkey = tt->rn_dupedkey;
E 23
D 24
D 25
			else printf("rn_delete: couldn't find us\n");
E 25
I 25
			else log(LOG_ERR, "rn_delete: couldn't find us\n");
E 28
I 28
			if (p) {
				p->rn_dupedkey = tt->rn_dupedkey;
				if (tt->rn_dupedkey)
					tt->rn_dupedkey->rn_p = p;
			} else log(LOG_ERR, "rn_delete: couldn't find us\n");
E 28
E 25
E 24
I 24
D 27
			else log(LOG_ERR, "rn_delete: couldn't find us\n");
E 27
I 27
			else printf("rn_delete: couldn't find us\n");
E 27
E 24
		}
D 23
		t = tt + 1;
		if  (t->rn_flags & RNF_ACTIVE) {
E 11
#ifndef RN_DEBUG
D 11
			x++; t = tt + 1; *x = *t; p = t->rn_p;
E 11
I 11
			*++x = *t; p = t->rn_p;
E 11
#else
D 11
			x++; b = x->rn_info; t = tt + 1; *x = *t; p = t->rn_p;
			x->rn_info = b;
E 11
I 11
			b = t->rn_info; *++x = *t; t->rn_info = b; p = t->rn_p;
E 11
#endif
			if (p->rn_l == t) p->rn_l = x; else p->rn_r = x;
			x->rn_l->rn_p = x; x->rn_r->rn_p = x;
E 23
I 23
		x = tt + 1;
		if  (x->rn_flags & RNF_ACTIVE) {
		/* Find inactive node to clober among this chain.  */
			for (t = base; t; t = x->rn_dupedkey)
				if ((t[1].rn_flags & RNF_ACTIVE) == 0)
					break;
			if (t == 0) {
				printf("rn_delete: lost inactive node");
				return (0);
			}
			t++;
			goto clobber;
E 23
D 11
		} else {
			for (p = saved_tt; p && p->rn_dupedkey != tt;)
				p = p->rn_dupedkey;
			if (p) p->rn_dupedkey = tt->rn_dupedkey;
			else printf("rn_delete: couldn't find us\n");
E 11
		}
		goto out;
	}
	if (t->rn_l == tt) x = t->rn_r; else x = t->rn_l;
	p = t->rn_p;
	if (p->rn_r == t) p->rn_r = x; else p->rn_l = x;
	x->rn_p = p;
	/*
	 * Demote routes attached to us.
	 */
	if (t->rn_mklist) {
		if (x->rn_b >= 0) {
D 8
			if (m = x->rn_mklist) {
				while (m->rm_mklist)
					m = m->rm_mklist;
				m->rm_mklist = t->rn_mklist;
			} else
				x->rn_mklist = m;
E 8
I 8
D 28
			for (mp = &x->rn_mklist; m = *mp;)
E 28
I 28
			for (mp = &x->rn_mklist; (m = *mp);)
E 28
D 23
				mp = &m->rm_mklist;
E 23
I 23
				mp = &m->rn_mklist;
E 23
			*mp = t->rn_mklist;
E 8
D 23
		} else {
D 24
D 25
			for (m = t->rn_mklist; m;) {
				struct radix_mask *mm = m->rm_mklist;
D 4
				MKFree(m);
E 4
I 4
				if (m == x->rn_mklist && (--(m->rm_refs) < 0)) {
E 25
I 25
			/* If there are any key,mask pairs in a sibling
			   duped-key chain, some subset will appear sorted
			   in the same order attached to our mklist */
			for (m = t->rn_mklist; m && x; x = x->rn_dupedkey)
				if (m == x->rn_mklist) {
					struct radix_mask *mm = m->rm_mklist;
E 25
E 24
I 24
D 27
			/* If there are any key,mask pairs in a sibling
			   duped-key chain, some subset will appear sorted
			   in the same order attached to our mklist */
			for (m = t->rn_mklist; m && x; x = x->rn_dupedkey)
				if (m == x->rn_mklist) {
					struct radix_mask *mm = m->rm_mklist;
E 27
I 27
			for (m = t->rn_mklist; m;) {
				struct radix_mask *mm = m->rm_mklist;
				if (m == x->rn_mklist && (--(m->rm_refs) < 0)) {
E 27
E 24
					x->rn_mklist = 0;
D 24
D 25
					MKFree(m);
D 8
				} else
					printf("rn_delete: Orphaned mask\n");
E 8
I 8
				} else 
					printf("%s %x at %x\n",
E 25
I 25
					if (--(m->rm_refs) < 0)
						MKFree(m);
					m = mm;
				}
			if (m)
				log(LOG_ERR, "%s %x at %x\n",
E 25
E 24
I 24
D 27
					if (--(m->rm_refs) < 0)
						MKFree(m);
					m = mm;
				}
			if (m)
				log(LOG_ERR, "%s %x at %x\n",
E 27
I 27
					MKFree(m);
				} else 
					printf("%s %x at %x\n",
E 27
E 24
					    "rn_delete: Orphaned Mask", m, x);
I 27
				m = mm;
			}
E 27
E 8
E 4
D 24
D 25
				m = mm;
			}
E 25
E 24
E 23
		}
	}
	/*
	 * We may be holding an active internal node in the tree.
	 */
	x = tt + 1;
	if (t != x) {
I 23
clobber:
E 23
#ifndef RN_DEBUG
		*t = *x;
#else
		b = t->rn_info; *t = *x; t->rn_info = b;
#endif
		t->rn_l->rn_p = t; t->rn_r->rn_p = t;
		p = x->rn_p;
		if (p->rn_l == x) p->rn_l = t; else p->rn_r = t;
	}
out:
	tt->rn_flags &= ~RNF_ACTIVE;
	tt[1].rn_flags &= ~RNF_ACTIVE;
	return (tt);
}
I 10

I 20
int
E 20
D 18
rn_walk(rn, f, w)
	register struct radix_node *rn;
E 18
I 18
rn_walktree(h, f, w)
	struct radix_node_head *h;
E 18
	register int (*f)();
D 20
	caddr_t  w;
E 20
I 20
	void *w;
E 20
{
	int error;
I 12
D 15
	struct radix_node *orn;
E 15
I 15
	struct radix_node *base, *next;
I 18
	register struct radix_node *rn = h->rnh_treetop;
E 18
	/*
	 * This gets complicated because we may delete the node
	 * while applying the function f to it, so we need to calculate
	 * the successor node in advance.
	 */
	/* First time through node, go left */
	while (rn->rn_b >= 0)
		rn = rn->rn_l;
E 15
E 12
	for (;;) {
D 15
		while (rn->rn_b >= 0)
			rn = rn->rn_l;	/* First time through node, go left */
D 12
		if (error = (*f)(rn, w))
			return (error);	/* Process Leaf */
		while (rn->rn_p->rn_r == rn) {	/* if coming back from right */
E 12
I 12
		for (orn = rn; rn; rn = rn->rn_dupedkey) /* Process Leaves */
E 15
I 15
		base = rn;
		/* If at right child go back up, otherwise, go right */
		while (rn->rn_p->rn_r == rn && (rn->rn_flags & RNF_ROOT) == 0)
			rn = rn->rn_p;
		/* Find the next *leaf* since next node might vanish, too */
		for (rn = rn->rn_p->rn_r; rn->rn_b >= 0;)
			rn = rn->rn_l;
		next = rn;
		/* Process leaves */
		while (rn = base) {
			base = rn->rn_dupedkey;
E 15
			if (!(rn->rn_flags & RNF_ROOT) && (error = (*f)(rn, w)))
				return (error);
D 15
		for (rn = orn; rn->rn_p->rn_r == rn; ) { /* If at right child */
E 12
			rn = rn->rn_p;		/* go back up */
			if (rn->rn_flags & RNF_ROOT)
				return 0;
E 15
		}
D 12
		rn = rn->rn_p->rn_r;		/* otherwise, go right*/
E 12
I 12
D 15
		rn = rn->rn_p->rn_r;		/* otherwhise, go right*/
E 15
I 15
		rn = next;
		if (rn->rn_flags & RNF_ROOT)
			return (0);
E 15
E 12
	}
I 20
	/* NOTREACHED */
E 20
D 11
	return 0;
E 11
}
E 10
D 15
char rn_zeros[MAXKEYLEN], rn_ones[MAXKEYLEN];
E 15

I 20
int
E 20
D 10
rn_inithead(head, off, af)
E 10
I 10
rn_inithead(head, off)
E 10
D 13
struct radix_node_head **head;
int off;
E 13
I 13
D 15
	struct radix_node_head **head;
E 15
I 15
	void **head;
E 15
	int off;
E 13
{
D 2
	register struct radix_node_head *hp;
E 2
I 2
	register struct radix_node_head *rnh;
E 2
	register struct radix_node *t, *tt, *ttt;
	if (*head)
		return (1);
D 2
	Malloc(hp, struct radix_node_head *, sizeof (*hp));
	if (hp == 0)
E 2
I 2
	R_Malloc(rnh, struct radix_node_head *, sizeof (*rnh));
	if (rnh == 0)
E 2
		return (0);
D 2
	Bzero(hp, sizeof (*hp));
	*head = hp;
	t = rn_newpair(rn_zeros, off, hp->rnh_nrt.nrt_nodes);
	ttt = &(hp->rnh_upper);
E 2
I 2
	Bzero(rnh, sizeof (*rnh));
	*head = rnh;
D 23
	t = rn_newpair(rn_zeros, off, rnh->rnh_nodes);
E 23
I 23
	rnh->rnh_offset = off;
	t = rn_newpair1(rn_zeros, 0, rnh->rnh_nodes, rnh);
E 23
	ttt = rnh->rnh_nodes + 2;
E 2
	t->rn_r = ttt;
	t->rn_p = t;
	tt = t->rn_l;
	tt->rn_flags = t->rn_flags = RNF_ROOT | RNF_ACTIVE;
D 23
	tt->rn_b = -1 - off;
E 23
I 23
	tt->rn_b = -1;
E 23
	*ttt = *tt;
	ttt->rn_key = rn_ones;
I 23
	rnh->rnh_treetop = t;
E 23
D 2
	hp->rnh_af = af;
	hp->rnh_treetop = t;
E 2
I 2
D 10
	rnh->rnh_af = af;
E 10
I 10
D 18
	rnh->rnh_add = rn_addroute;
	rnh->rnh_delete = rn_delete;
	rnh->rnh_match = rn_match;
	rnh->rnh_walk = rn_walk;
E 18
I 18
	rnh->rnh_addaddr = rn_addroute;
	rnh->rnh_deladdr = rn_delete;
	rnh->rnh_matchaddr = rn_match;
I 25
	rnh->rnh_lookup = rn_lookup;
E 25
I 24
D 27
	rnh->rnh_lookup = rn_lookup;
E 27
E 24
	rnh->rnh_walktree = rn_walktree;
E 18
E 10
D 23
	rnh->rnh_treetop = t;
E 23
I 23
	rnh->rnh_bits_matched = rn_unmapped_bits_matched;
	rnh->rnh_set_mask = rn_unmapped_set_mask;
E 23
E 2
D 10
	if (radix_node_head == 0) {
E 10
I 10
D 15
	if (mask_rnhead == 0) {
E 10
D 2
		char *cp = rn_ones, *cplim = rn_ones + MAXKEYLEN;
E 2
I 2
		caddr_t cp = rn_ones, cplim = rn_ones + MAXKEYLEN;
E 2
		while (cp < cplim)
			*cp++ = -1;
D 10
		if (rn_inithead(&radix_node_head, 0, 0) == 0) {
E 10
I 10
		if (rn_inithead(&mask_rnhead, 0) == 0) {
E 10
D 2
			Free(hp);
E 2
I 2
			Free(rnh);
E 2
			*head = 0;
			return (0);
		}
I 4
D 10
		mask_rnhead = radix_node_head;
E 10
E 4
	}
E 15
D 2
	hp->rnh_next = radix_node_head->rnh_next;
	if (radix_node_head != hp)
		radix_node_head->rnh_next = hp;
E 2
I 2
D 10
	rnh->rnh_next = radix_node_head->rnh_next;
	if (radix_node_head != rnh)
		radix_node_head->rnh_next = rnh;
E 10
E 2
	return (1);
I 15
}

I 20
void
E 20
rn_init()
{
	char *cp, *cplim;
#ifdef KERNEL
	struct domain *dom;

	for (dom = domains; dom; dom = dom->dom_next)
		if (dom->dom_maxrtkey > max_keylen)
			max_keylen = dom->dom_maxrtkey;
#endif
	if (max_keylen == 0) {
D 24
D 25
		printf("rn_init: radix functions require max_keylen be set\n");
E 25
I 25
		log(LOG_ERR,
		    "rn_init: radix functions require max_keylen be set\n");
E 25
E 24
I 24
D 27
		log(LOG_ERR,
		    "rn_init: radix functions require max_keylen be set\n");
E 27
I 27
		printf("rn_init: radix functions require max_keylen be set\n");
E 27
E 24
		return;
	}
	R_Malloc(rn_zeros, char *, 3 * max_keylen);
	if (rn_zeros == NULL)
		panic("rn_init");
D 23
	Bzero(rn_zeros, 3 * max_keylen);
E 23
I 23
	Bzero(rn_zeros, 2 * max_keylen);
E 23
	rn_ones = cp = rn_zeros + max_keylen;
D 23
D 24
D 25
	maskedKey = cplim = rn_ones + max_keylen;
E 25
I 25
	addmask_key = cplim = rn_ones + max_keylen;
E 25
E 24
I 24
D 27
	addmask_key = cplim = rn_ones + max_keylen;
E 27
I 27
	maskedKey = cplim = rn_ones + max_keylen;
E 27
E 24
E 23
	while (cp < cplim)
		*cp++ = -1;
	if (rn_inithead((void **)&mask_rnhead, 0) == 0)
		panic("rn_init 2");
E 15
}
E 1
