h21165
s 00050/00050/00145
d D 8.2 94/02/21 15:08:10 bostic 12 11
c first pass at making DB use basic integral types (the Alpha port)
e
s 00002/00002/00193
d D 8.1 93/06/04 15:20:09 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00003/00193
d D 5.10 93/05/16 15:42:16 bostic 10 9
c lint; break BTF flags up into btree/recno (B_, R_) categories
e
s 00001/00001/00195
d D 5.9 93/05/01 22:59:51 bostic 9 8
c lint
e
s 00102/00044/00094
d D 5.8 93/05/01 15:35:55 bostic 8 7
c add code to swap the meta page as as it is read in or out
c break the pgin/pgout routines up again -- they can't be the same because the
c interal information in the file has been switched either before or after the
c rest of the page!!!
e
s 00001/00001/00137
d D 5.7 93/02/14 17:39:16 bostic 7 6
c index -> indx_t
e
s 00001/00001/00137
d D 5.6 93/02/11 11:39:19 bostic 6 5
c move db.h to the end of the includes, make compat.h work better
e
s 00002/00000/00136
d D 5.5 92/11/13 16:03:58 bostic 5 4
c prettiness police
e
s 00005/00005/00131
d D 5.4 91/12/16 14:02:26 bostic 4 3
c get the swap macro sizes right
e
s 00003/00003/00133
d D 5.3 91/11/20 11:31:25 bostic 3 2
c cast GETBINTERNAL calls for pcc
e
s 00073/00062/00063
d D 5.2 91/09/12 11:11:33 bostic 2 1
c make the swap code for both in and out routines the same; make
c it really work.
e
s 00125/00000/00000
d D 5.1 91/09/04 12:50:45 bostic 1 0
c Rev #2.  Redo the btree code add recno's and checkpoint
e
u
U
t
T
I 1
/*-
D 11
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * This code is derived from software contributed to Berkeley by
 * Mike Olson.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/param.h>
I 5

E 5
D 6
#include <db.h>
E 6
#include <stdio.h>
I 5

I 6
#include <db.h>
E 6
E 5
#include "btree.h"

I 2
D 10
static void kdswap __P((PAGE *));
E 10
I 8
static void mswap __P((PAGE *));
E 8

E 2
/*
 * __BT_BPGIN, __BT_BPGOUT --
 *	Convert host-specific number layout to/from the host-independent
 *	format stored on disk.
 *
 * Parameters:
D 2
 *	tree:	tree
E 2
I 2
 *	t:	tree
 *	pg:	page number
E 2
 *	h:	page to convert
D 2
 *
 * Side Effects:
 *	Layout of tree metadata on the page is changed in place.
 *
 * Warnings:
 *	Everywhere else in the code, the types pgno_t and index_t are
 *	opaque.  These two routines know what they really are.
E 2
 */
void
D 8
__bt_pgin(t, pg, p)
E 8
I 8
__bt_pgin(t, pg, pp)
E 8
	void *t;
	pgno_t pg;
D 8
	void *p;
E 8
I 8
	void *pp;
E 8
{
D 2
	register BINTERNAL *bi;
	register BLEAF *bl;
	register int i, top;
E 2
	PAGE *h;
I 8
D 12
	int i, top;
E 12
I 12
	indx_t i, top;
E 12
	u_char flags;
	char *p;
E 8

D 8
	if (((BTREE *)t)->bt_lorder == BYTE_ORDER)
E 8
I 8
D 10
	if (!ISSET(((BTREE *)t), BTF_NEEDSWAP))
E 10
I 10
	if (!ISSET(((BTREE *)t), B_NEEDSWAP))
E 10
E 8
		return;
I 8
	if (pg == P_META) {
		mswap(pp);
		return;
	}
E 8

D 8
	h = p;
E 8
I 8
	h = pp;
E 8
D 12
	BLSWAP(h->pgno);
	BLSWAP(h->prevpg);
	BLSWAP(h->nextpg);
	BLSWAP(h->flags);
D 2
	BLSWAP(h->lower);
	BLSWAP(h->upper);

	top = NEXTINDEX(h);
	if (!(h->flags & (P_BLEAF | P_RLEAF)))
		for (i = 0; i < top; i++) {
			BLSWAP(h->linp[i]);
			bi = GETBINTERNAL(h, i);
			BLSWAP(bi->ksize);
			BLSWAP(bi->pgno);
			BLSWAP(bi->flags);
			if (bi->flags & P_BIGKEY)
				BLSWAP(*(long *)bi->bytes);
		}
	else if (!(h->flags & P_OVERFLOW))
		for (i = 0; i < top; i++) {
			BLSWAP(h->linp[i]);
			bl = GETBLEAF(h, i);
			BLSWAP(bl->dsize);
			BLSWAP(bl->ksize);
			BLSWAP(bl->flags);
			if (bl->flags & P_BIGKEY)
				BLSWAP(*(long *)bl->bytes);
			if (bl->flags & P_BIGDATA)
				BLSWAP(*(long *)(bl->bytes + bl->ksize));
		}
E 2
I 2
	BSSWAP(h->lower);
	BSSWAP(h->upper);
E 12
I 12
	M_32_SWAP(h->pgno);
	M_32_SWAP(h->prevpg);
	M_32_SWAP(h->nextpg);
	M_32_SWAP(h->flags);
	M_16_SWAP(h->lower);
	M_16_SWAP(h->upper);
E 12
D 8
	kdswap(h);
E 8
I 8

	top = NEXTINDEX(h);
	if ((h->flags & P_TYPE) == P_BINTERNAL)
		for (i = 0; i < top; i++) {
D 12
			BSSWAP(h->linp[i]);
E 12
I 12
			M_16_SWAP(h->linp[i]);
E 12
			p = (char *)GETBINTERNAL(h, i);
D 12
			BLPSWAP(p);
E 12
I 12
			P_32_SWAP(p);
E 12
			p += sizeof(size_t);
D 12
			BLPSWAP(p);
E 12
I 12
			P_32_SWAP(p);
E 12
			p += sizeof(pgno_t);
			if (*(u_char *)p & P_BIGKEY) {
				p += sizeof(u_char);
D 12
				BLPSWAP(p);
E 12
I 12
				P_32_SWAP(p);
E 12
				p += sizeof(pgno_t);
D 12
				BLPSWAP(p);
E 12
I 12
				P_32_SWAP(p);
E 12
			}
		}
	else if ((h->flags & P_TYPE) == P_BLEAF)
		for (i = 0; i < top; i++) {
D 12
			BSSWAP(h->linp[i]);
E 12
I 12
			M_16_SWAP(h->linp[i]);
E 12
			p = (char *)GETBLEAF(h, i);
D 12
			BLPSWAP(p);
E 12
I 12
			P_32_SWAP(p);
E 12
			p += sizeof(size_t);
D 12
			BLPSWAP(p);
E 12
I 12
			P_32_SWAP(p);
E 12
			p += sizeof(size_t);
			flags = *(u_char *)p;
			if (flags & (P_BIGKEY | P_BIGDATA)) {
				p += sizeof(u_char);
				if (flags & P_BIGKEY) {
D 12
					BLPSWAP(p);
E 12
I 12
					P_32_SWAP(p);
E 12
					p += sizeof(pgno_t);
D 12
					BLPSWAP(p);
E 12
I 12
					P_32_SWAP(p);
E 12
				}
				if (flags & P_BIGDATA) {
					p += sizeof(size_t);
D 12
					BLPSWAP(p);
E 12
I 12
					P_32_SWAP(p);
E 12
					p += sizeof(pgno_t);
D 12
					BLPSWAP(p);
E 12
I 12
					P_32_SWAP(p);
E 12
				}
			}
		}
E 8
E 2
}

void
D 8
__bt_pgout(t, pg, p)
E 8
I 8
__bt_pgout(t, pg, pp)
E 8
	void *t;
	pgno_t pg;
D 8
	void *p;
E 8
I 8
	void *pp;
E 8
{
D 2
	register BINTERNAL *bi;
	register BLEAF *bl;
	register int i, top;
E 2
	PAGE *h;
I 8
D 12
	int i, top;
E 12
I 12
	indx_t i, top;
E 12
	u_char flags;
	char *p;
E 8

D 8
	if (((BTREE *)t)->bt_lorder == BYTE_ORDER)
E 8
I 8
D 10
	if (!ISSET(((BTREE *)t), BTF_NEEDSWAP))
E 10
I 10
	if (!ISSET(((BTREE *)t), B_NEEDSWAP))
E 10
E 8
		return;
I 8
	if (pg == P_META) {
		mswap(pp);
		return;
	}
E 8

D 8
	h = p;
I 2
	kdswap(h);
	BLSWAP(h->pgno);
	BLSWAP(h->prevpg);
	BLSWAP(h->nextpg);
	BLSWAP(h->flags);
	BSSWAP(h->lower);
	BSSWAP(h->upper);
}

/*
 * KDSWAP -- Actually swap the bytes on the page.
 *
 * Parameters:
 *	h:	page to convert
 *
 * Warnings:
D 7
 *	Everywhere else in the code, the pgno_t and index_t types are
E 7
I 7
 *	Everywhere else in the code, the pgno_t and indx_t types are
E 7
 *	opaque.  These routines know what they really are.
 */
static void
kdswap(h)
	PAGE *h;
{
	register int i, top;
D 3
	register void *p;
E 3
I 3
	register char *p;			/* Really void, thanks ANSI! */
E 3
	u_char flags;

E 8
I 8
	h = pp;
E 8
E 2
	top = NEXTINDEX(h);
D 2
	if (!(h->flags & (P_BLEAF | P_RLEAF)))
E 2
I 2
D 8
	switch (h->flags & P_TYPE) {
	case P_BINTERNAL:
E 8
I 8
	if ((h->flags & P_TYPE) == P_BINTERNAL)
E 8
E 2
		for (i = 0; i < top; i++) {
D 2
			bi = GETBINTERNAL(h, i);
			BLSWAP(bi->ksize);
			BLSWAP(bi->pgno);
			if (bi->flags & P_BIGKEY)
				BLSWAP(*(long *)bi->bytes);
			BLSWAP(h->linp[i]);
E 2
I 2
D 8
			BSSWAP(h->linp[i]);
E 8
D 3
			p = GETBINTERNAL(h, i);
E 3
I 3
			p = (char *)GETBINTERNAL(h, i);
E 3
D 12
			BLPSWAP(p);
E 12
I 12
			P_32_SWAP(p);
E 12
			p += sizeof(size_t);
D 12
			BLPSWAP(p);
E 12
I 12
			P_32_SWAP(p);
E 12
			p += sizeof(pgno_t);
			if (*(u_char *)p & P_BIGKEY) {
				p += sizeof(u_char);
D 12
				BLPSWAP(p);
E 12
I 12
				P_32_SWAP(p);
E 12
				p += sizeof(pgno_t);
D 4
				BSPSWAP(p);
E 4
I 4
D 12
				BLPSWAP(p);
E 12
I 12
				P_32_SWAP(p);
E 12
E 4
			}
I 8
D 12
			BSSWAP(h->linp[i]);
E 12
I 12
			M_16_SWAP(h->linp[i]);
E 12
E 8
E 2
		}
D 2
	else if (!(h->flags & P_OVERFLOW))
E 2
I 2
D 8
		break;
	case P_BLEAF:
E 8
I 8
	else if ((h->flags & P_TYPE) == P_BLEAF)
E 8
E 2
		for (i = 0; i < top; i++) {
D 2
			bl = GETBLEAF(h, i);
			BLSWAP(bl->ksize);
			BLSWAP(bl->dsize);
			if (bl->flags & P_BIGKEY)
				BLSWAP(*(long *)bl->bytes);
			if (bl->flags & P_BIGDATA)
				BLSWAP(*(long *)(bl->bytes + bl->ksize));
			BLSWAP(h->linp[i]);
E 2
I 2
D 8
			BSSWAP(h->linp[i]);
E 8
D 3
			p = GETBLEAF(h, i);
E 3
I 3
			p = (char *)GETBLEAF(h, i);
E 3
D 4
			BSPSWAP(p);
E 4
I 4
D 12
			BLPSWAP(p);
E 12
I 12
			P_32_SWAP(p);
E 12
E 4
			p += sizeof(size_t);
D 4
			BSPSWAP(p);
E 4
I 4
D 12
			BLPSWAP(p);
E 12
I 12
			P_32_SWAP(p);
E 12
E 4
			p += sizeof(size_t);
			flags = *(u_char *)p;
			if (flags & (P_BIGKEY | P_BIGDATA)) {
				p += sizeof(u_char);
				if (flags & P_BIGKEY) {
D 12
					BLPSWAP(p);
E 12
I 12
					P_32_SWAP(p);
E 12
					p += sizeof(pgno_t);
D 4
					BSPSWAP(p);
E 4
I 4
D 12
					BLPSWAP(p);
E 12
I 12
					P_32_SWAP(p);
E 12
E 4
				}
				if (flags & P_BIGDATA) {
					p += sizeof(size_t);
D 12
					BLPSWAP(p);
E 12
I 12
					P_32_SWAP(p);
E 12
					p += sizeof(pgno_t);
D 4
					BSPSWAP(p);
E 4
I 4
D 12
					BLPSWAP(p);
E 12
I 12
					P_32_SWAP(p);
E 12
E 4
				}
			}
I 8
D 12
			BSSWAP(h->linp[i]);
E 12
I 12
			M_16_SWAP(h->linp[i]);
E 12
E 8
E 2
		}
D 2
	BLSWAP(h->pgno);
	BLSWAP(h->prevpg);
	BLSWAP(h->nextpg);
	BLSWAP(h->flags);
	BLSWAP(h->lower);
	BLSWAP(h->upper);
E 2
I 2
D 8
		break;
	}
E 8
I 8

D 12
	BLSWAP(h->pgno);
	BLSWAP(h->prevpg);
	BLSWAP(h->nextpg);
	BLSWAP(h->flags);
	BSSWAP(h->lower);
	BSSWAP(h->upper);
E 12
I 12
	M_32_SWAP(h->pgno);
	M_32_SWAP(h->prevpg);
	M_32_SWAP(h->nextpg);
	M_32_SWAP(h->flags);
	M_16_SWAP(h->lower);
	M_16_SWAP(h->upper);
E 12
}

/*
 * MSWAP -- Actually swap the bytes on the meta page.
 *
 * Parameters:
 *	p:	page to convert
 */
D 9
void
E 9
I 9
static void
E 9
mswap(pg)
	PAGE *pg;
{
	char *p;

	p = (char *)pg;
D 12
	BLPSWAP(p);		/* m_magic */
	p += sizeof(u_long);
	BLPSWAP(p);		/* m_version */
	p += sizeof(u_long);
	BLPSWAP(p);		/* m_psize */
	p += sizeof(u_long);
	BLPSWAP(p);		/* m_free */
	p += sizeof(u_long);
	BLPSWAP(p);		/* m_nrecs */
	p += sizeof(u_long);
	BLPSWAP(p);		/* m_flags */
	p += sizeof(u_long);
E 12
I 12
	P_32_SWAP(p);		/* m_magic */
	p += sizeof(u_int32_t);
	P_32_SWAP(p);		/* m_version */
	p += sizeof(u_int32_t);
	P_32_SWAP(p);		/* m_psize */
	p += sizeof(u_int32_t);
	P_32_SWAP(p);		/* m_free */
	p += sizeof(u_int32_t);
	P_32_SWAP(p);		/* m_nrecs */
	p += sizeof(u_int32_t);
	P_32_SWAP(p);		/* m_flags */
	p += sizeof(u_int32_t);
E 12
E 8
E 2
}
E 1
