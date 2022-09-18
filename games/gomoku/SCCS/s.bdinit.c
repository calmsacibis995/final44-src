h42712
s 00062/00020/00158
d D 8.2 95/05/03 19:31:49 mckusick 2 1
c update from Ralph
e
s 00178/00000/00000
d D 8.1 94/07/24 22:58:09 mckusick 1 0
c from Ralph Campbell
e
u
U
t
T
I 1
/*
 * Copyright (c) 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 2
#include <string.h>
E 2
#include "gomoku.h"

bdinit(bp)
	struct spotstr *bp;
{
	register int i, j, r;
	register struct spotstr *sp;
	register struct combostr *cbp;

	movenum = 1;

	/* mark the borders as such */
	sp = bp;
	for (i = BSZ2; --i >= 0; sp++) {
		sp->s_occ = BORDER;		/* top border */
		sp->s_flg = BFLAGALL;
	}

	/* fill entire board with EMPTY spots */
I 2
	memset(frames, 0, sizeof(frames));
E 2
	cbp = frames;
	for (j = 0; ++j < BSZ1; sp++) {			/* for each row */
		for (i = 0; ++i < BSZ1; sp++) {		/* for each column */
			sp->s_occ = EMPTY;
			sp->s_flg = 0;
			sp->s_wval = 0;
			if (j < 5) {
				/* directions 1, 2, 3 are blocked */
				sp->s_flg |= (BFLAG << 1) | (BFLAG << 2) |
					(BFLAG << 3);
				sp->s_fval[BLACK][1].s = MAXCOMBO;
				sp->s_fval[BLACK][2].s = MAXCOMBO;
				sp->s_fval[BLACK][3].s = MAXCOMBO;
				sp->s_fval[WHITE][1].s = MAXCOMBO;
				sp->s_fval[WHITE][2].s = MAXCOMBO;
				sp->s_fval[WHITE][3].s = MAXCOMBO;
			} else if (j == 5) {
				/* five spaces, blocked on one side */
				sp->s_fval[BLACK][1].s = 0x500;
				sp->s_fval[BLACK][2].s = 0x500;
				sp->s_fval[BLACK][3].s = 0x500;
				sp->s_fval[WHITE][1].s = 0x500;
				sp->s_fval[WHITE][2].s = 0x500;
				sp->s_fval[WHITE][3].s = 0x500;
			} else {
				/* six spaces, not blocked */
				sp->s_fval[BLACK][1].s = 0x401;
				sp->s_fval[BLACK][2].s = 0x401;
				sp->s_fval[BLACK][3].s = 0x401;
				sp->s_fval[WHITE][1].s = 0x401;
				sp->s_fval[WHITE][2].s = 0x401;
				sp->s_fval[WHITE][3].s = 0x401;
			}
			if (i > (BSZ - 4)) {
				/* directions 0, 1 are blocked */
				sp->s_flg |= BFLAG | (BFLAG << 1);
				sp->s_fval[BLACK][0].s = MAXCOMBO;
				sp->s_fval[BLACK][1].s = MAXCOMBO;
				sp->s_fval[WHITE][0].s = MAXCOMBO;
				sp->s_fval[WHITE][1].s = MAXCOMBO;
			} else if (i == (BSZ - 4)) {
				sp->s_fval[BLACK][0].s = 0x500;
				sp->s_fval[WHITE][0].s = 0x500;
				/* if direction 1 is not blocked */
				if (!(sp->s_flg & (BFLAG << 1))) {
					sp->s_fval[BLACK][1].s = 0x500;
					sp->s_fval[WHITE][1].s = 0x500;
				}
			} else {
				sp->s_fval[BLACK][0].s = 0x401;
				sp->s_fval[WHITE][0].s = 0x401;
				if (i < 5) {
					/* direction 3 is blocked */
					sp->s_flg |= (BFLAG << 3);
					sp->s_fval[BLACK][3].s = MAXCOMBO;
					sp->s_fval[WHITE][3].s = MAXCOMBO;
				} else if (i == 5 &&
				    !(sp->s_flg & (BFLAG << 3))) {
					sp->s_fval[BLACK][3].s = 0x500;
					sp->s_fval[WHITE][3].s = 0x500;
				}
			}
			/*
			 * Allocate a frame structure for non blocked frames.
			 */
			for (r = 4; --r >= 0; ) {
				if (sp->s_flg & (BFLAG << r))
					continue;
D 2
				cbp->c_next = (struct combostr *)0;
				cbp->c_prev = (struct combostr *)0;
				cbp->c_link[0] = (struct combostr *)0;
				cbp->c_link[1] = (struct combostr *)0;
E 2
				cbp->c_combo.s = sp->s_fval[BLACK][r].s;
				cbp->c_vertex = sp - board;
				cbp->c_nframes = 1;
				cbp->c_dir = r;
D 2
				cbp->c_flg = 0;
				cbp->c_refcnt = 0;
E 2
				sp->s_frame[r] = cbp;
				cbp++;
			}
		}
		sp->s_occ = BORDER;		/* left & right border */
		sp->s_flg = BFLAGALL;
	}

	/* mark the borders as such */
	for (i = BSZ1; --i >= 0; sp++) {
		sp->s_occ = BORDER;		/* bottom border */
		sp->s_flg = BFLAGALL;
	}

	sortframes[BLACK] = (struct combostr *)0;
	sortframes[WHITE] = (struct combostr *)0;
	init_overlap();
}

/*
 * Initialize the overlap array.
D 2
 * Each entry in the array is a bit mask with four bits corresponding
 * to whether frame A overlaps frame B. The four combinations are
 * whether A and B are open ended (length 6) or closed (length 5).
 *	0	A open and B open
 *	1	A open and B closed
 *	2	A closed and B open
 *	3	A closed and B closed
E 2
I 2
 * Each entry in the array is a bit mask with eight bits corresponding
 * to whether frame B overlaps frame A (as indexed by overlap[A * FAREA + B]).
 * The eight bits coorespond to whether A and B are open ended (length 6) or
 * closed (length 5).
 *	0	A closed and B closed
 *	1	A closed and B open
 *	2	A open and B closed
 *	3	A open and B open
 *	4	A closed and B closed and overlaps in more than one spot
 *	5	A closed and B open and overlaps in more than one spot
 *	6	A open and B closed and overlaps in more than one spot
 *	7	A open and B open and overlaps in more than one spot
 * As pieces are played, it can make frames not overlap if there are no
 * common open spaces shared between the two frames.
E 2
 */
init_overlap()
{
	register struct spotstr *sp1, *sp2;
	register struct combostr *cbp;
	register int i, f, r, n, d1, d2;
	int mask, bmask, vertex, s;
D 2
	char *str;
E 2
I 2
	u_char *str;
E 2
	short *ip;

	memset(overlap, 0, sizeof(overlap));
	memset(intersect, 0, sizeof(intersect));
	str = &overlap[FAREA * FAREA];
	ip = &intersect[FAREA * FAREA];
D 2
	for (cbp = frames + FAREA; --cbp >= frames; ) {
E 2
I 2
	for (cbp = frames + FAREA; --cbp >= frames; ) {		/* each frame */
E 2
	    str -= FAREA;
	    ip -= FAREA;
	    sp1 = &board[vertex = cbp->c_vertex];
	    d1 = dd[r = cbp->c_dir];
D 2
	    s = sp1->s_fval[BLACK][r].c.b;
	    for (i = 5 + s; --i >= 0; sp1 += d1, vertex += d1) {
		mask = (s && i == 0) ? 0xC : 0xF;
E 2
I 2
	    /*
	     * s = 5 if closed, 6 if open.
	     * At this point black & white are the same.
	     */
	    s = 5 + sp1->s_fval[BLACK][r].c.b;
	    /* for each spot in frame A */
	    for (i = 0; i < s; i++, sp1 += d1, vertex += d1) {
		/* the sixth spot in frame A only overlaps if it is open */
		mask = (i == 5) ? 0xC : 0xF;
		/* for each direction */
E 2
		for (r = 4; --r >= 0; ) {
		    bmask = BFLAG << r;
		    sp2 = sp1;
		    d2 = dd[r];
D 2
		    for (f = 6; --f >= 0; sp2 -= d2) {
E 2
I 2
		    /* for each frame that intersects at spot sp1 */
		    for (f = 0; f < 6; f++, sp2 -= d2) {
E 2
			if (sp2->s_occ == BORDER)
			    break;
			if (sp2->s_flg & bmask)
			    continue;
			n = sp2->s_frame[r] - frames;
D 2
			str[n] |= (f == 0) ? mask & 0x5 : mask;
E 2
			ip[n] = vertex;
I 2
			str[n] |= (f == 5) ? mask & 0xA : mask;
			if (r == cbp->c_dir) {
			    /* compute the multiple spot overlap values */
			    switch (i) {
			    case 0:	/* sp1 is the first spot in A */
				if (f == 4)
				    str[n] |= 0xA0;
				else if (f != 5)
				    str[n] |= 0xF0;
				break;
			    case 1:	/* sp1 is the second spot in A */
				if (f == 5)
				    str[n] |= 0xA0;
				else
				    str[n] |= 0xF0;
				break;
			    case 4:	/* sp1 is the penultimate spot in A */
				if (f == 0)
				    str[n] |= 0xC0;
				else
				    str[n] |= 0xF0;
				break;
			    case 5:	/* sp1 is the last spot in A */
				if (f == 1)
				    str[n] |= 0xC0;
				else if (f != 0)
				    str[n] |= 0xF0;
				break;
			    default:
				str[n] |= 0xF0;
			    }
			}
E 2
		    }
		}
	    }
	}
}
E 1
