/*
 * Copyright (c) 1988, 1989  Regents of the University of California. All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following
 * conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and
 * the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of
 * conditions and the following disclaimer in the documentation and/or other materials provided with the distribution. 3.
 * All advertising materials mentioning features or use of this software must display the following acknowledgement: This
 * product includes software developed by the University of California, Berkeley and its contributors. 4. Neither the name
 * of the University nor the names of its contributors may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO
 * EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * 
 * @(#)radix.c	7.14 (Berkeley) 5/21/92
 */

/*
 * Routines to build and maintain radix trees for routing lookups.
 */
#ifndef RNF_NORMAL
#include "param.h"
#include "radix.h"
#include "malloc.h"
#define	M_DONTWAIT M_NOWAIT
#endif
struct radix_mask *rnode_mkfreelist;
struct radix_node_head *mask_rnhead;
#define rnode_maskhead (mask_rnhead->rnh_treetop)
#undef Bcmp
#define Bcmp(a, b, l) (l == 0 ? 0 : bcmp((caddr_t)(a), (caddr_t)(b), (u_long)l))

/*
 * The data structure for the keys is a radix tree with one way branching removed.  The index rnode_b at an internal node n
 * represents a bit position to be tested.  The tree is arranged so that all descendants of a node n have keys whose bits
 * all agree up to position rnode_b - 1. (We say the index of n is rnode_b.)
 * 
 * There is at least one descendant which has a one bit at position rnode_b, and at least one with a zero there.
 * 
 * A route is determined by a pair of key and mask.  We require that the bit-wise logical and of the key and mask to be the
 * key. We define the index of a route to associated with the mask to be the first bit number in the mask where 0 occurs
 * (with bit number 0 representing the highest order bit).
 * 
 * We say a mask is normal if every bit is 0, past the index of the mask. If a node n has a descendant (k, m) with index(m) ==
 * index(n) == rnode_b, and m is a normal mask, then the route applies to every descendant of n. If the index(m) < rnode_b, this
 * implies the trailing last few bits of k before bit b are all 0, (and hence consequently true of every descendant of n),
 * so the route applies to all descendants of the node as well.
 * 
 * The present version of the code makes no use of normal routes, but similar logic shows that a non-normal mask m such that
 * index(m) <= index(n) could potentially apply to many children of n. Thus, for each non-host route, we attach its mask to
 * a list at an internal node as high in the tree as we can go.
 */

struct radix_node *
rnode_search(v, head)
struct radix_node *head;
register caddr_t v;
{
    register struct radix_node *x;

    for (x = head; x->rnode_b >= 0;) {
	if (x->rnode_bmask & v[x->rnode_off]) {
	    x = x->rnode_r;
	} else {
	    x = x->rnode_l;
	}
    }
    return x;
};

struct radix_node *
rnode_search_m(v, head, m)
struct radix_node *head;
register caddr_t v, m;
{
    register struct radix_node *x;

    for (x = head; x->rnode_b >= 0;) {
	if ((x->rnode_bmask & m[x->rnode_off]) &&
		(x->rnode_bmask & v[x->rnode_off])) {
	    x = x->rnode_r;
	} else {
	    x = x->rnode_l;
	}
    }
    return x;
};

rnode_refines(m, n)
register caddr_t m, n;
{
    register caddr_t lim, lim2 = lim = n + *(u_char *) n;
    int longer = (*(u_char *) n++) - (int) (*(u_char *) m++);
    int masks_are_equal = 1;

    if (longer > 0) {
	lim -= longer;
    }
    while (n < lim) {
	if (*n & ~(*m)) {
	    return 0;
	}
	if (*n++ != *m++) {
	    masks_are_equal = 0;
	}
    }
    while (n < lim2) {
	if (*n++) {
	    return 0;
	}
    }
    if (masks_are_equal && (longer < 0)) {
	for (lim2 = m - longer; m < lim2;) {
	    if (*m++) {
		return 1;
	    }
	}
    }
    
    return !masks_are_equal;
}


#define MAXKEYLEN 52
static int gotOddMasks;
static char maskedKey[MAXKEYLEN];

struct radix_node *
rnode_match(v, head)
struct radix_node *head;
caddr_t v;
{
    register struct radix_node *t = head, *x;
    register caddr_t cp = v, cp2, cp3;
    caddr_t cplim, mstart;
    struct radix_node *saved_t;
    int off = t->rnode_off, vlen = *(u_char *) cp, matched_off;

    /*
     * Open code rnode_search(v, head) to avoid overhead of extra subroutine call.
     */
    for (; t->rnode_b >= 0;) {
	if (t->rnode_bmask & cp[t->rnode_off]) {
	    t = t->rnode_r;
	} else {
	    t = t->rnode_l;
	}
    }

    /*
     * See if we match exactly as a host destination
     */
    cp += off;
    cp2 = t->rnode_key + off;
    cplim = v + vlen;
    for (; cp < cplim; cp++, cp2++) {
	if (*cp != *cp2) {
	    goto on1;
	}
    }

    /*
     * This extra grot is in case we are explicitly asked to look up the default.  Ugh!
     */
    if ((t->rnode_flags & RNF_ROOT) && t->rnode_dupedkey) {
	t = t->rnode_dupedkey;
    }
    return t;

  on1:
    matched_off = cp - v;
    saved_t = t;
    do {
	if (t->rnode_mask) {

	    /*
	     * Even if we don't match exactly as a hosts; we may match if the leaf we wound up at is a route to a net.
	     */
	    cp3 = matched_off + t->rnode_mask;
	    cp2 = matched_off + t->rnode_key;
	    for (; cp < cplim; cp++) {
		if ((*cp2++ ^ *cp) & *cp3++) {
		    break;
		}
	    }
	    if (cp == cplim) {
		return t;
	    }
	    cp = matched_off + v;
	}
    } while (t = t->rnode_dupedkey);
    t = saved_t;
    /* start searching up the tree */
    do {
	register struct radix_mask *m;
	t = t->rnode_p;
	if (m = t->rnode_mklist) {

	    /*
	     * After doing measurements here, it may turn out to be faster to open code rnode_search_m here instead of always
	     * copying and masking.
	     */
	    off = MIN(t->rnode_off, matched_off);
	    mstart = maskedKey + off;
	    do {
		cp2 = mstart;
		cp3 = m->rm_mask + off;
		for (cp = v + off; cp < cplim;) {
		    *cp2++ = *cp++ & *cp3++;
		}
		x = rnode_search(maskedKey, t);
		while (x && x->rnode_mask != m->rm_mask) {
		    x = x->rnode_dupedkey;
		}
		if (x &&
			(Bcmp(mstart, x->rnode_key + off,
			      vlen - off) == 0)) {
		    return x;
		}
	    } while (m = m->rm_mklist);
	}
    } while (t != head);
    return 0;
};

#ifdef RNODE_DEBUG
int rnode_nodenum;
struct radix_node *rnode_clist;
int rnode_saveinfo;
#endif

struct radix_node *
rnode_newpair(v, b, nodes)
caddr_t v;
int b;
struct radix_node nodes[2];
{
    register struct radix_node *tt = nodes, *t = tt + 1;
    t->rnode_b = b;
    t->rnode_bmask = 0x80 >> (b & 7);
    t->rnode_l = tt;
    t->rnode_off = b >> 3;
    tt->rnode_b = -1;
    tt->rnode_key = v;
    tt->rnode_p = t;
    tt->rnode_flags = t->rnode_flags = RNF_ACTIVE;
#ifdef RNODE_DEBUG
    tt->rnode_info = rnode_nodenum++;
    t->rnode_info = rnode_nodenum++;
    tt->rnode_twin = t;
    tt->rnode_ybro = rnode_clist;
    rnode_clist = tt;
#endif
    return t;
}

int rnode_debug = 1;
struct radix_node *
rnode_insert(v, head, dupentry, nodes)
caddr_t v;
struct radix_node *head;
int *dupentry;
struct radix_node nodes[2];
{
    int head_off = head->rnode_off, vlen = (int) *((u_char *) v);
    register struct radix_node *t = rnode_search(v, head);
    register caddr_t cp = v + head_off;
    register int b;
    struct radix_node *tt;

    /*
     * find first bit at which v and t->rnode_key differ
     */
    {
	register caddr_t cp2 = t->rnode_key + head_off;
	register int cmp_res;
	caddr_t cplim = v + vlen;

	while (cp < cplim) {
	    if (*cp2++ != *cp++) {
		goto on1;
	    }
	}
	*dupentry = 1;
	return t;
      on1:
	*dupentry = 0;
	cmp_res = (cp[-1] ^ cp2[-1]) & 0xff;
	for (b = (cp - v) << 3; cmp_res; b--) {
	    cmp_res >>= 1;
	}
    }
    {
	register struct radix_node *p, *x = head;
	cp = v;
	do {
	    p = x;
	    if (cp[x->rnode_off] & x->rnode_bmask) {
		x = x->rnode_r;
	    } else {
		x = x->rnode_l;
	    }
	} while (b > (unsigned) x->rnode_b);	/* x->rnode_b < b && x->rnode_b >= 0 */
#ifdef RNODE_DEBUG
	if (rnode_debug) {
	    printf("Going In:\n"), traverse(p);
	}
#endif
	t = rnode_newpair(v, b, nodes);
	tt = t->rnode_l;
	if ((cp[p->rnode_off] & p->rnode_bmask) == 0) {
	    p->rnode_l = t;
	} else {
	    p->rnode_r = t;
	}
	x->rnode_p = t;
	t->rnode_p = p;			/* frees x, p as temp vars below */
	if ((cp[t->rnode_off] & t->rnode_bmask) == 0) {
	    t->rnode_r = x;
	} else {
	    t->rnode_r = tt;
	    t->rnode_l = x;
	}
#ifdef RNODE_DEBUG
	if (rnode_debug) {
	    printf("Coming out:\n"), traverse(p);
	}
#endif
    }
    return tt;
}

struct radix_node *
rnode_addmask(netmask, search, skip)
caddr_t netmask;
int search, skip;
{
    register struct radix_node *x;
    register caddr_t cp, cplim;
    register int b, mlen, j;
    int maskduplicated;

    mlen = *(u_char *) netmask;
    if (search) {
	x = rnode_search(netmask, rnode_maskhead);
	mlen = *(u_char *) netmask;
	if (Bcmp(netmask, x->rnode_key, mlen) == 0) {
	    return x;
	}
    }
    R_Malloc(x, struct radix_node *, MAXKEYLEN + 2 * sizeof (*x));
    if (x == 0) {
	return 0;
    }
    Bzero(x, MAXKEYLEN + 2 * sizeof (*x));
    cp = (caddr_t) (x + 2);
    Bcopy(netmask, cp, mlen);
    netmask = cp;
    x = rnode_insert(netmask, rnode_maskhead, &maskduplicated, x);

    /*
     * Calculate index of mask.
     */
    cplim = netmask + mlen;
    for (cp = netmask + skip; cp < cplim; cp++) {
	if (*(u_char *) cp != 0xff) {
	    break;
	}
    }
    b = (cp - netmask) << 3;
    if (cp != cplim) {
	if (*cp != 0) {
	    gotOddMasks = 1;
	    for (j = 0x80; j; b++, j >>= 1) {
		if ((j & *cp) == 0) {
		    break;
		}
	    }
	}
    }
    x->rnode_b = -1 - b;
    return x;
}

struct radix_node *
rnode_addroute(v, netmask, head, treenodes)
caddr_t v, netmask;
struct radix_node *head;
struct radix_node treenodes[2];
{
    register int j;
    register caddr_t cp;
    register struct radix_node *t, *x, *tt;
    short b = 0, b_leaf;
    int vlen = *(u_char *) v, mlen, keyduplicated;
    caddr_t cplim;
    unsigned char *maskp;
    struct radix_mask *m, **mp;
    struct radix_node *saved_tt;

    /*
     * In dealing with non-contiguous masks, there may be many different routes which have the same mask. We will find it
     * useful to have a unique pointer to the mask to speed avoiding duplicate references at nodes and possibly save time in
     * calculating indices.
     */
    if (netmask) {
	x = rnode_search(netmask, rnode_maskhead);
	mlen = *(u_char *) netmask;
	if (Bcmp(netmask, x->rnode_key, mlen) != 0) {
	    x = rnode_addmask(netmask, 0, head->rnode_off);
	    if (x == 0) {
		return 0;
	    }
	}
	netmask = x->rnode_key;
	b = -1 - x->rnode_b;
    }

    /*
     * Deal with duplicated keys: attach node to previous instance
     */
    saved_tt = tt = rnode_insert(v, head, &keyduplicated, treenodes);
    if (keyduplicated) {
	do {
	    if (tt->rnode_mask == netmask) {
		return 0;
	    }
	    t = tt;
	    if (netmask == 0 ||
		    (tt->rnode_mask && rnode_refines(netmask, tt->rnode_mask))) {
		break;
	    }
	} while (tt = tt->rnode_dupedkey);

	/*
	 * If the mask is not duplicated, we wouldn't find it among possible duplicate key entries anyway, so the above test
	 * doesn't hurt.
	 * 
	 * We sort the masks for a duplicated key the same way as in a masklist -- most specific to least specific. This may
	 * require the unfortunate nuisance of relocating the head of the list.
	 */
	if (tt && t == saved_tt) {
	    struct radix_node *xx = x;
	    /* link in at head of list */
	    (tt = treenodes)->rnode_dupedkey = t;
	    tt->rnode_flags = t->rnode_flags;
	    tt->rnode_p = x = t->rnode_p;
	    if (x->rnode_l == t) {
		x->rnode_l = tt;
	    } else {
		x->rnode_r = tt;
	    }
	    saved_tt = tt;
	    x = xx;
	} else {
	    (tt = treenodes)->rnode_dupedkey = t->rnode_dupedkey;
	    t->rnode_dupedkey = tt;
	}
#ifdef RNODE_DEBUG
	t = tt + 1;
	tt->rnode_info = rnode_nodenum++;
	t->rnode_info = rnode_nodenum++;
	tt->rnode_twin = t;
	tt->rnode_ybro = rnode_clist;
	rnode_clist = tt;
#endif
	t = saved_tt;
	tt->rnode_key = (caddr_t) v;
	tt->rnode_b = -1;
	tt->rnode_flags = t->rnode_flags & ~RNF_ROOT;
    }

    /*
     * Put mask in tree.
     */
    if (netmask) {
	tt->rnode_mask = netmask;
	tt->rnode_b = x->rnode_b;
    }
    t = saved_tt->rnode_p;
    b_leaf = -1 - t->rnode_b;
    if (t->rnode_r == saved_tt) {
	x = t->rnode_l;
    } else {
	x = t->rnode_r;
    }
    /* Promote general routes from below */
    if (x->rnode_b < 0) {
	if (x->rnode_mask && (x->rnode_b >= b_leaf) && x->rnode_mklist == 0) {
	    MKGet(m);
	    if (m) {
		Bzero(m, sizeof *m);
		m->rm_b = x->rnode_b;
		m->rm_mask = x->rnode_mask;
		x->rnode_mklist = t->rnode_mklist = m;
	    }
	}
    } else if (x->rnode_mklist) {

	/*
	 * Skip over masks whose index is > that of new node
	 */
	for (mp = &x->rnode_mklist; m = *mp; mp = &m->rm_mklist) {
	    if (m->rm_b >= b_leaf) {
		break;
	    }
	}
	t->rnode_mklist = m;
	*mp = 0;
    }
    /* Add new route to highest possible ancestor's list */
    if ((netmask == 0) || (b > t->rnode_b)) {
	return tt;			/* can't lift at all */
    }
    b_leaf = tt->rnode_b;
    do {
	x = t;
	t = t->rnode_p;
    } while (b <= t->rnode_b && x != head);

    /*
     * Search through routes associated with node to insert new route according to index. For nodes of equal index, place
     * more specific masks first.
     */
    cplim = netmask + mlen;
    for (mp = &x->rnode_mklist; m = *mp; mp = &m->rm_mklist) {
	if (m->rm_b < b_leaf) {
	    continue;
	}
	if (m->rm_b > b_leaf) {
	    break;
	}
	if (m->rm_mask == netmask) {
	    m->rm_refs++;
	    tt->rnode_mklist = m;
	    return tt;
	}
	if (rnode_refines(netmask, m->rm_mask)) {
	    break;
	}
    }
    MKGet(m);
    if (m == 0) {
	printf("Mask for route not entered\n");
	return tt;
    }
    Bzero(m, sizeof *m);
    m->rm_b = b_leaf;
    m->rm_mask = netmask;
    m->rm_mklist = *mp;
    *mp = m;
    tt->rnode_mklist = m;
    return tt;
}

struct radix_node *
rnode_delete(v, netmask, head)
caddr_t v, netmask;
struct radix_node *head;
{
    register struct radix_node *t, *p, *x = head;
    register struct radix_node *tt = rnode_search(v, x);
    int b, head_off = x->rnode_off, vlen = *(u_char *) v;
    struct radix_mask *m, *saved_m, **mp;
    struct radix_node *dupedkey, *saved_tt = tt;

    if (tt == 0 ||
	    Bcmp(v + head_off, tt->rnode_key + head_off, vlen - head_off)) {
	return 0;
    }

    /*
     * Delete our route from mask lists.
     */
    if (dupedkey = tt->rnode_dupedkey) {
	if (netmask) {
	    netmask = rnode_search(netmask, rnode_maskhead)->rnode_key;
	}
	while (tt->rnode_mask != netmask) {
	    if ((tt = tt->rnode_dupedkey) == 0) {
		return 0;
	    }
	}
    }
    if (tt->rnode_mask == 0 || (saved_m = m = tt->rnode_mklist) == 0) {
	goto on1;
    }
    if (m->rm_mask != tt->rnode_mask) {
	printf("rnode_delete: inconsistent annotation\n");
	goto on1;
    }
    if (--m->rm_refs >= 0) {
	goto on1;
    }
    b = -1 - tt->rnode_b;
    t = saved_tt->rnode_p;
    if (b > t->rnode_b) {
	goto on1;			/* Wasn't lifted at all */
    }
    do {
	x = t;
	t = t->rnode_p;
    } while (b <= t->rnode_b && x != head);
    for (mp = &x->rnode_mklist; m = *mp; mp = &m->rm_mklist) {
	if (m == saved_m) {
	    *mp = m->rm_mklist;
	    MKFree(m);
	    break;
	}
    }
    if (m == 0) {
	printf("rnode_delete: couldn't find our annotation\n");
    }
  on1:

    /*
     * Eliminate us from tree
     */
    if (tt->rnode_flags & RNF_ROOT) {
	return 0;
    }
#ifdef RNODE_DEBUG
    /* Get us out of the creation list */
    for (t = rnode_clist; t && t->rnode_ybro != tt; t = t->rnode_ybro) {
    }
    if (t) {
	t->rnode_ybro = tt->rnode_ybro;
    }
#endif	/* RNODE_DEBUG */
    t = tt->rnode_p;
    if (dupedkey) {
	if (tt == saved_tt) {
	    x = dupedkey;
	    x->rnode_p = t;
	    if (t->rnode_l == tt) {
		t->rnode_l = x;
	    } else {
		t->rnode_r = x;
	    }
	} else {
	    for (x = p = saved_tt; p && p->rnode_dupedkey != tt;) {
		p = p->rnode_dupedkey;
	    }
	    if (p) {
		p->rnode_dupedkey = tt->rnode_dupedkey;
	    } else {
		printf("rnode_delete: couldn't find us\n");
	    }
	}
	t = tt + 1;
	if (t->rnode_flags & RNF_ACTIVE) {
#ifndef RNODE_DEBUG
	    *++x = *t;
	    p = t->rnode_p;
#else
	    b = t->rnode_info;
	    *++x = *t;
	    t->rnode_info = b;
	    p = t->rnode_p;
#endif
	    if (p->rnode_l == t) {
		p->rnode_l = x;
	    } else {
		p->rnode_r = x;
	    }
	    x->rnode_l->rnode_p = x;
	    x->rnode_r->rnode_p = x;
	}
	goto out;
    }
    if (t->rnode_l == tt) {
	x = t->rnode_r;
    } else {
	x = t->rnode_l;
    }
    p = t->rnode_p;
    if (p->rnode_r == t) {
	p->rnode_r = x;
    } else {
	p->rnode_l = x;
    }
    x->rnode_p = p;

    /*
     * Demote routes attached to us.
     */
    if (t->rnode_mklist) {
	if (x->rnode_b >= 0) {
	    for (mp = &x->rnode_mklist; m = *mp;) {
		mp = &m->rm_mklist;
	    }
	    *mp = t->rnode_mklist;
	} else {
	    for (m = t->rnode_mklist; m;) {
		struct radix_mask *mm = m->rm_mklist;
		if (m == x->rnode_mklist && (--(m->rm_refs) < 0)) {
		    x->rnode_mklist = 0;
		    MKFree(m);
		} else {
		    printf("%s %x at %x\n",
			   "rnode_delete: Orphaned Mask", m, x);
		}
		m = mm;
	    }
	}
    }

    /*
     * We may be holding an active internal node in the tree.
     */
    x = tt + 1;
    if (t != x) {
#ifndef RNODE_DEBUG
	*t = *x;
#else
	b = t->rnode_info;
	*t = *x;
	t->rnode_info = b;
#endif
	t->rnode_l->rnode_p = t;
	t->rnode_r->rnode_p = t;
	p = x->rnode_p;
	if (p->rnode_l == x) {
	    p->rnode_l = t;
	} else {
	    p->rnode_r = t;
	}
    }
  out:
    tt->rnode_flags &= ~RNF_ACTIVE;
    tt[1].rnode_flags &= ~RNF_ACTIVE;
    return tt;
}

rnode_walk(rn, f, w)
register struct radix_node *rn;
register int (*f) ();
caddr_t w;
{
    int error;
    struct radix_node *orn;
    for (;;) {
	while (rn->rnode_b >= 0) {
	    rn = rn->rnode_l;		/* First time through node, go left */
	}
	for (orn = rn; rn; rn = rn->rnode_dupedkey) {
	    /* Process Leaves */
	    if (!(rn->rnode_flags & RNF_ROOT) && (error = (*f) (rn, w))) {
		return error;
	    }
	}
	for (rn = orn; rn->rnode_p->rnode_r == rn;) {	/* If at right child */
	    rn = rn->rnode_p;		/* go back up */
	    if (rn->rnode_flags & RNF_ROOT) {
		return 0;
	    }
	}
	rn = rn->rnode_p->rnode_r;		/* otherwhise, go right */
    }
}
char rnode_zeros[MAXKEYLEN], rnode_ones[MAXKEYLEN];

rnode_inithead(head, off)
struct radix_node_head **head;
int off;
{
    register struct radix_node_head *rnh;
    register struct radix_node *t, *tt, *ttt;
    if (*head) {
	return 1;
    }
    R_Malloc(rnh, struct radix_node_head *, sizeof (*rnh));
    if (rnh == 0) {
	return 0;
    }
    Bzero(rnh, sizeof (*rnh));
    *head = rnh;
    t = rnode_newpair(rnode_zeros, off, rnh->rnh_nodes);
    ttt = rnh->rnh_nodes + 2;
    t->rnode_r = ttt;
    t->rnode_p = t;
    tt = t->rnode_l;
    tt->rnode_flags = t->rnode_flags = RNF_ROOT | RNF_ACTIVE;
    tt->rnode_b = -1 - off;
    *ttt = *tt;
    ttt->rnode_key = rnode_ones;
    rnh->rnh_add = rnode_addroute;
    rnh->rnh_delete = rnode_delete;
    rnh->rnh_match = rnode_match;
    rnh->rnh_walk = rnode_walk;
    rnh->rnh_treetop = t;
    if (mask_rnhead == 0) {
	caddr_t cp = rnode_ones, cplim = rnode_ones + MAXKEYLEN;
	while (cp < cplim) {
	    *cp++ = -1;
	}
	if (rnode_inithead(&mask_rnhead, 0) == 0) {
	    Free(rnh);
	    *head = 0;
	    return 0;
	}
    }
    return 1;
}
