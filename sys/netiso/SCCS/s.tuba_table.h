h24557
s 00001/00000/00033
d D 8.2 94/07/13 18:02:46 sklower 11 10
c further fixes, rn_inithead called with wrong offsets and 
c need to store NSAP with net/radix.c conventions for length byte instead of
e
s 00002/00002/00031
d D 8.1 93/06/10 23:21:41 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00028
d D 7.9 92/11/25 20:09:39 sklower 9 8
c this version supports TCP between two workstations on the same ethernet
e
s 00002/00002/00031
d D 7.8 92/11/20 22:45:25 sklower 8 7
c minor fixes & improvements: swab not in kernel; make sure NSEL is 
c 6 when connecting; don't bother to save extra 2 cksum fudges; change convention
c on who moves pointer past CLNP header; on input, if you have to pull up TCP
c header, do it directly into aligned header.
e
s 00006/00004/00027
d D 7.7 92/11/19 02:38:17 sklower 7 6
c changes thought to be required for new pseudo-header, not tested
e
s 00001/00001/00030
d D 7.6 92/11/08 15:31:28 sklower 6 5
c this version works well enough for a simple sender & receiver to talk
e
s 00002/00001/00029
d D 7.5 92/11/05 15:00:40 sklower 5 4
c checkpoint further progress, still doesn't connect tho.
e
s 00003/00001/00027
d D 7.4 92/11/05 07:13:00 sklower 4 3
c checkpoint, doesn't do checksum right yet
e
s 00003/00002/00025
d D 7.3 92/10/15 18:51:30 sklower 3 2
c this version compiles and matches current #include convention
e
s 00001/00001/00026
d D 7.2 92/10/09 01:08:01 sklower 2 1
c correct defective copyright dates
e
s 00027/00000/00000
d D 7.1 92/10/09 00:51:46 sklower 1 0
c date and time created 92/10/09 00:51:46 by sklower
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1991 The Regents of the University of California.
E 2
I 2
D 10
 * Copyright (c) 1992 The Regents of the University of California.
E 2
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

struct tuba_cache {
	struct	radix_node tc_nodes[2];		/* convenient lookup */
	int	tc_refcnt;
	int	tc_time;			/* last looked up */
	int	tc_flags;
#define TCF_PERM	1
	int	tc_index;
D 7
	u_short	tc_sum_in;			/* for inbound cksum */
	u_short	tc_sum_out;			/* for outbound cksum */
E 7
I 7
	u_short	tc_sum;				/* cksum of nsap inc. length */
	u_short	tc_ssum;			/* swab(tc_sum) */
D 8
	u_short	tc_sum_d;			/* o.c. diff sum - index */
	u_short	tc_ssum_d;			/* o.c. diff ssum - index */
E 8
E 7
D 5
	struct	iso_addr tc_addr;
E 5
I 5
D 6
	struct	iso_addr tc_addr;		/* so you can respond */
E 6
I 6
	struct	sockaddr_iso tc_siso;		/* for responding */
I 11
	struct	iso_addr tc_addr;
E 11
E 6
D 7
	char	tc_EID[7];			/* what counts for lookups */
E 7
E 5
};

D 4
#define ICKSUM(a, b) ((a = (b) % 0xffff), (a == 0 ? a = 0xffff : a))
E 4
I 4
#define ADDCARRY(x)  (x >= 65535 ? x -= 65535 : x)
#define REDUCE(a, b) { union { u_short s[2]; long l;} l_util; long x; \
D 7
	l_util.l = (b); x = l_util.s[0] + l_util.s[1]; ADDCARRY(x); a = x;}
E 7
I 7
	l_util.l = (b); x = l_util.s[0] + l_util.s[1]; ADDCARRY(x); \
	if (x == 0) x = 0xffff; a = x;}
I 8
D 9
#define SWAB(a, b) { union { u_char c[2]; u_short s;} s_util; u_short x; \
	u_char t; s_util.s = b; t = c[0]; c[0] = c[1]; c[1] = t; }
E 9
I 9
#define SWAB(a, b) { union { u_char c[2]; u_short s;} s; u_char t; \
	s.s = (b); t = s.c[0]; s.c[0] = s.c[1]; s.c[1] = t; a = s.s;}
E 9
E 8
E 7
E 4

#ifdef KERNEL
D 3
extern struct tuba_cache **tuba_table;
struct radix_node_head *tuba_tree;
E 3
I 3
D 9
extern int	tuba_table_size;
extern struct	tuba_cache **tuba_table;
extern struct	radix_node_head *tuba_tree;
E 9
I 9
extern	int	tuba_table_size;
extern	struct	tuba_cache **tuba_table;
extern	struct	radix_node_head *tuba_tree;
E 9
E 3
#endif
E 1
