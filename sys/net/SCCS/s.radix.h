h08042
s 00011/00002/00125
d D 8.2 94/10/31 13:42:55 sklower 13 10
c compromise fixes for duped keys
e
s 00011/00002/00125
d D 8.1.2.1 94/10/09 01:44:23 sklower 12 10
c this version corresponds to radix.c SID 8.2.2.1 making use of 
c normal routes when present, but allowing non-contiguous masks, \ 
e
s 00026/00025/00102
d D 8.1.1.1 94/09/23 18:59:10 sklower 11 10
c put in branch delta for normal-only routes, and mapping capabilities;
c first version; probably doesn't work yet.
e
s 00002/00002/00125
d D 8.1 93/06/10 22:45:14 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00022/00007/00105
d D 7.9 93/06/04 17:31:29 bostic 9 8
c prototype everything
e
s 00019/00008/00093
d D 7.8 93/04/08 17:12:46 sklower 8 7
c new conventions for using routing tree
e
s 00011/00004/00090
d D 7.7 92/07/13 00:07:42 mckusick 7 6
c add function prototypes; protect against multiple inclusion
e
s 00002/00000/00092
d D 7.6 92/07/09 00:02:41 sklower 6 5
c changes to add routing tables via the domain switch
e
s 00006/00006/00086
d D 7.5 91/07/30 17:37:12 sklower 5 4
c some changes to make it possible to have different methods
c for different address families; move MAXKEYLEN out of header file to radix.c
e
s 00001/00011/00091
d D 7.4 90/06/28 21:31:35 bostic 4 3
c new copyright notice
e
s 00007/00009/00095
d D 7.3 89/04/22 12:11:30 sklower 3 2
c checkpoint at first working tp4 connection; before gnodes
e
s 00029/00041/00075
d D 7.2 88/12/13 13:30:32 sklower 2 1
c checkpoint semi-working version with routing socket
e
s 00116/00000/00000
d D 7.1 88/11/09 23:31:35 sklower 1 0
c date and time created 88/11/09 23:31:35 by sklower
e
u
U
f b 
t
T
I 1
/*
D 3
 * Copyright (c) 1988 Regents of the University of California.
E 3
I 3
D 10
 * Copyright (c) 1988, 1989 Regents of the University of California.
E 3
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1988, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
 */

I 7
#ifndef _RADIX_H_
#define	_RADIX_H_

E 7
/*
 * Radix search tree node layout.
 */

struct radix_node {
D 11
	struct	radix_mask *rn_mklist;	/* list of masks contained in subtree */
E 11
I 11
	struct	radix_node *rn_mklist;	/* list of masks contained in subtree */
E 11
	struct	radix_node *rn_p;	/* parent */
	short	rn_b;			/* bit offset; -1-index(netmask) */
	char	rn_bmask;		/* node: mask for bit test*/
	u_char	rn_flags;		/* enumerated next */
#define RNF_NORMAL	1		/* leaf contains normal route */
#define RNF_ROOT	2		/* leaf is root leaf for tree */
#define RNF_ACTIVE	4		/* This node is alive (for rtfree) */
	union {
		struct {			/* leaf only data: */
D 2
			char 	*rn_Key;	/* object of search */
			char	*rn_Mask;	/* netmask, if present */
E 2
I 2
			caddr_t	rn_Key;	/* object of search */
			caddr_t	rn_Mask;	/* netmask, if present */
E 2
			struct	radix_node *rn_Dupedkey;
		} rn_leaf;
		struct {			/* node only data: */
			int	rn_Off;		/* where to start compare */
			struct	radix_node *rn_L;/* progeny */
			struct	radix_node *rn_R;/* progeny */
		}rn_node;
	}		rn_u;
#ifdef RN_DEBUG
	int rn_info;
	struct radix_node *rn_twin;
	struct radix_node *rn_ybro;
#endif
};

I 2
D 5
#define MAXKEYLEN 32

E 5
E 2
#define rn_dupedkey rn_u.rn_leaf.rn_Dupedkey
#define rn_key rn_u.rn_leaf.rn_Key
#define rn_mask rn_u.rn_leaf.rn_Mask
#define rn_off rn_u.rn_node.rn_Off
#define rn_l rn_u.rn_node.rn_L
#define rn_r rn_u.rn_node.rn_R
I 2

E 2
D 11
/*
 * Annotations to tree concerning potential routes applying to subtrees.
 */
D 2
struct radix_mask {
E 2
I 2

extern struct radix_mask {
E 2
	short	rm_b;			/* bit offset; -1-index(netmask) */
	char	rm_unused;		/* cf. rn_bmask */
	u_char	rm_flags;		/* cf. rn_flags */
	struct	radix_mask *rm_mklist;	/* more masks to try */
D 2
	char	*rm_mask;		/* the mask */
E 2
I 2
D 12
D 13
	caddr_t	rm_mask;		/* the mask */
E 13
I 13
	union	{
		caddr_t	rmu_mask;		/* the mask */
		struct	radix_node *rmu_leaf;	/* for normal routes */
	}	rm_rmu;
E 13
E 12
I 12
	union	{
		caddr_t	rmu_mask;		/* the mask */
		struct	radix_node *rmu_leaf;	/* for normal routes */
	}	rm_rmu;
E 12
E 2
	int	rm_refs;		/* # of references to this struct */
D 2
};
E 2
I 2
} *rn_mkfreelist;
E 2

I 13
#define rm_mask rm_rmu.rmu_mask
#define rm_leaf rm_rmu.rmu_leaf		/* extra field would make 32 bytes */

E 13
I 12
#define rm_mask rm_rmu.rmu_mask
#define rm_leaf rm_rmu.rmu_leaf		/* extra field would make 32 bytes */

E 12
I 2
#define MKGet(m) {\
	if (rn_mkfreelist) {\
		m = rn_mkfreelist; \
		rn_mkfreelist = (m)->rm_mklist; \
	} else \
		R_Malloc(m, struct radix_mask *, sizeof (*(m))); }\

#define MKFree(m) { (m)->rm_mklist = rn_mkfreelist; rn_mkfreelist = (m);}

E 11
D 5
extern struct radix_node_head {
	struct	radix_node_head *rnh_next;
E 5
I 5
struct radix_node_head {
E 5
	struct	radix_node *rnh_treetop;
D 5
	int	rnh_af;
E 5
I 5
D 7
	struct	radix_node *(*rnh_add)();
	struct	radix_node *(*rnh_delete)();
	struct	radix_node *(*rnh_match)();
	int	(*rnh_walk)();
E 7
I 7
D 8
	struct	radix_node *(*rnh_add) __P((caddr_t v, caddr_t netmask,
		struct radix_node *head, struct radix_node treenodes[]));
	struct	radix_node *(*rnh_delete) __P((caddr_t v, caddr_t netmask,
		struct radix_node *head));
	struct	radix_node *(*rnh_match) __P((caddr_t v,
		struct radix_node *head));
	int	(*rnh_walk) __P((struct radix_node *rn, int (*f)(), void *w));
E 7
E 5
	struct	radix_node rnh_nodes[3];
E 8
I 8
	int	rnh_addrsize;		/* permit, but not require fixed keys */
	int	rnh_pktsize;		/* permit, but not require fixed keys */
	struct	radix_node *(*rnh_addaddr)	/* add based on sockaddr */
D 9
		__P((caddr_t v, caddr_t mask,
E 9
I 9
		__P((void *v, void *mask,
E 9
		     struct radix_node_head *head, struct radix_node nodes[]));
	struct	radix_node *(*rnh_addpkt)	/* add based on packet hdr */
D 9
		__P((caddr_t v, caddr_t mask,
E 9
I 9
		__P((void *v, void *mask,
E 9
		     struct radix_node_head *head, struct radix_node nodes[]));
	struct	radix_node *(*rnh_deladdr)	/* remove based on sockaddr */
D 9
		__P((caddr_t v, caddr_t mask, struct radix_node_head *head));
E 9
I 9
		__P((void *v, void *mask, struct radix_node_head *head));
E 9
	struct	radix_node *(*rnh_delpkt)	/* remove based on packet hdr */
D 9
		__P((caddr_t v, caddr_t mask, struct radix_node_head *head));
E 9
I 9
		__P((void *v, void *mask, struct radix_node_head *head));
E 9
	struct	radix_node *(*rnh_matchaddr)	/* locate based on sockaddr */
D 9
		__P((caddr_t v, struct radix_node_head *head));
E 9
I 9
		__P((void *v, struct radix_node_head *head));
I 13
	struct	radix_node *(*rnh_lookup)	/* locate based on sockaddr */
		__P((void *v, void *mask, struct radix_node_head *head));
E 13
I 12
	struct	radix_node *(*rnh_lookup)	/* locate based on sockaddr */
		__P((void *v, void *mask, struct radix_node_head *head));
E 12
E 9
	struct	radix_node *(*rnh_matchpkt)	/* locate based on packet hdr */
D 9
		__P((caddr_t v, struct radix_node_head *head));
E 9
I 9
		__P((void *v, struct radix_node_head *head));
E 9
	int	(*rnh_walktree)			/* traverse tree */
		__P((struct radix_node_head *head, int (*f)(), void *w));
I 11
/* mapping stuff */
	struct	radix_index_table  {
		short	limit;
		short	offset;
	}	*rnh_table;			/* how to re-order the bits */
	int	rnh_offset;			/* for martialed keys */
	int	(*rnh_bits_matched)		/* used in matching, insert */
		__P((void *trial, void *ref,
		     struct radix_node_head *head, int masklen));
	int	(*rnh_set_mask)			/* used in insertion */
		__P((int index,
		     struct radix_node *rn, struct radix_node_head *rnh));
/* the treetop itself */
E 11
	struct	radix_node rnh_nodes[3];	/* empty tree for common case */
E 8
D 5
} *radix_node_head;
E 5
I 5
};
E 5


E 2
#ifndef KERNEL
D 3
char *malloc();
E 3
#define Bcmp(a, b, n) bcmp(((char *)(a)), ((char *)(b)), (n))
I 13
#define Bcopy(a, b, n) bcopy(((char *)(a)), ((char *)(b)), (unsigned)(n))
E 13
I 12
#define Bcopy(a, b, n) bcopy(((char *)(a)), ((char *)(b)), (unsigned)(n))
E 12
D 2
#define Malloc(p, t, n) (p = (t) malloc((unsigned int)(n)))
E 2
#define Bzero(p, n) bzero((char *)(p), (int)(n));
I 2
#define R_Malloc(p, t, n) (p = (t) malloc((unsigned int)(n)))
E 2
#define Free(p) free((char *)p);
D 3
#define min(a, b) ((a) < (b) ? (a) : (b))
E 3
D 2
#ifndef RTF_UP
/*
 * probably just testing here . . .
 */
struct rtentry {
	int	rt_unused;
};
#endif
E 2
#else
D 3
#define Bcmp(a, b, n) bcmp(((caddr_t)(a)), ((caddr_t)(b)), (n))
D 2
#define Malloc(p, t, n) (p = (t) malloc((n), M_RTABLE, M_DONTWAIT))
E 2
I 2
#define Bcopy(a, b, n) bcopy(((caddr_t)(a)), ((caddr_t)(b)), (n))
E 2
#define Bzero(p, n) bzero((caddr_t)(p), (int)(n));
I 2
#define R_Malloc(p, t, n) (p = (t) malloc((n), M_RTABLE, M_DONTWAIT))
E 2
#define Free(p) free((caddr_t)p);
#endif KERNEL
E 3
I 3
#define Bcmp(a, b, n) bcmp(((caddr_t)(a)), ((caddr_t)(b)), (unsigned)(n))
#define Bcopy(a, b, n) bcopy(((caddr_t)(a)), ((caddr_t)(b)), (unsigned)(n))
#define Bzero(p, n) bzero((caddr_t)(p), (unsigned)(n));
#define R_Malloc(p, t, n) (p = (t) malloc((unsigned long)(n), M_RTABLE, M_DONTWAIT))
#define Free(p) free((caddr_t)p, M_RTABLE);
I 13
#endif /*KERNEL*/
E 13
I 12
#endif /*KERNEL*/
E 12
I 11
#endif /*KERNEL*/
E 11
I 6

D 9
int	rn_inithead __P((void **, int));
E 9
I 9
void	 rn_init __P((void));
int	 rn_inithead __P((void **, int));
int	 rn_refines __P((void *, void *));
int	 rn_walktree __P((struct radix_node_head *, int (*)(), void *));
struct radix_node
	 *rn_addmask __P((void *, int, int)),
	 *rn_addroute __P((void *, void *, struct radix_node_head *,
			struct radix_node [2])),
	 *rn_delete __P((void *, void *, struct radix_node_head *)),
	 *rn_insert __P((void *, struct radix_node_head *, int *,
			struct radix_node [2])),
	 *rn_match __P((void *, struct radix_node_head *)),
	 *rn_newpair __P((void *, int, struct radix_node[2])),
	 *rn_search __P((void *, struct radix_node *)),
D 11
	 *rn_search_m __P((void *, struct radix_node *, void *));
E 11
I 11
	 *rn_search_unmapped __P((void *, struct radix_node_head *));
E 11

E 9
E 6
D 11
D 12
D 13
#endif /*KERNEL*/
E 13
E 12
E 11
I 11
int	 rn_set_unmapped_mask
		__P((int, struct radix_node *, struct radix_node_head *)),
	 rn_set_mapped_mask
		__P((int, struct radix_node *, struct radix_node_head *)),
	 rn_mapped_bits_matched
		__P((void *, void *, struct radix_node_head *, int)),
	 rn_unmapped_bits_matched
		__P((void *, void *, struct radix_node_head *, int));
					

E 11
I 7
#endif /* _RADIX_H_ */
E 7
E 3
D 2

struct nrtentry {
	struct	radix_node nrt_nodes[2];
	struct	rtentry nrt_rt;
};

#define MAXKEYLEN 32

extern struct radix_node_head {
	struct	radix_node_head *rnh_next;
	struct	radix_node *rnh_treetop;
	int	rnh_af;
	struct	radix_node rnh_upper;
	struct	nrtentry rnh_nrt;
} *radix_node_head;

extern struct radix_mask *rn_mkfreelist;

#define MKGet(m) {\
	if (rn_mkfreelist) {\
		m = rn_mkfreelist; \
		rn_mkfreelist = (m)->rm_mklist; \
	} else \
		Malloc(m, struct radix_mask *, sizeof (*(m))); }\

#define MKFree(m) { (m)->rm_mklist = rn_mkfreelist; rn_mkfreelist = (m);}
E 2
E 1
