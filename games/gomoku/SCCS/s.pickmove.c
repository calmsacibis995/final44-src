h17018
s 00961/00388/00492
d D 8.2 95/05/03 19:34:01 mckusick 2 1
c update from Ralph
e
s 00880/00000/00000
d D 8.1 94/07/24 22:58:11 mckusick 1 0
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

#include <stdio.h>
#include <curses.h>
I 2
#include <machine/limits.h>
E 2

#include "gomoku.h"

D 2
struct	combostr *sortcombos[2];	/* combos at higher levels */
int	combolen[2];			/* number of combos in sortcombos */
int	nextcolor;			/* color of next move */
E 2
I 2
#define BITS_PER_INT	(sizeof(int) * CHAR_BIT)
#define MAPSZ		(BAREA / BITS_PER_INT)
E 2

D 2
extern char pdir[];
E 2
I 2
#define BIT_SET(a, b)	((a)[(b)/BITS_PER_INT] |= (1 << ((b) % BITS_PER_INT)))
#define BIT_CLR(a, b)	((a)[(b)/BITS_PER_INT] &= ~(1 << ((b) % BITS_PER_INT)))
#define BIT_TEST(a, b)	((a)[(b)/BITS_PER_INT] & (1 << ((b) % BITS_PER_INT)))
E 2

I 2
struct	combostr *hashcombos[FAREA];	/* hash list for finding duplicates */
struct	combostr *sortcombos;		/* combos at higher levels */
int	combolen;			/* number of combos in sortcombos */
int	nextcolor;			/* color of next move */
int	elistcnt;			/* count of struct elist allocated */
int	combocnt;			/* count of struct combostr allocated */
int	forcemap[MAPSZ];		/* map for blocking <1,x> combos */
int	tmpmap[MAPSZ];			/* map for blocking <1,x> combos */
int	nforce;				/* count of opponent <1,x> combos */

E 2
pickmove(us)
	int us;
{
	register struct spotstr *sp, *sp1, *sp2;
D 2
	register union combo *Ocp, *Tcp;
E 2
I 2
	register union comboval *Ocp, *Tcp;
	char *str;
	int i, j, m;
E 2

	/* first move is easy */
	if (movenum == 1)
		return (PT(K,10));

	/* initialize all the board values */
	for (sp = &board[PT(T,20)]; --sp >= &board[PT(A,1)]; ) {
D 2
		sp->s_combo[BLACK].s = MAXCOMBO;
		sp->s_combo[WHITE].s = MAXCOMBO;
E 2
I 2
		sp->s_combo[BLACK].s = MAXCOMBO + 1;
		sp->s_combo[WHITE].s = MAXCOMBO + 1;
E 2
		sp->s_level[BLACK] = 255;
		sp->s_level[WHITE] = 255;
		sp->s_nforce[BLACK] = 0;
		sp->s_nforce[WHITE] = 0;
		sp->s_flg &= ~(FFLAGALL | MFLAGALL);
	}
I 2
	nforce = 0;
	memset(forcemap, 0, sizeof(forcemap));
E 2

D 2
	/* remove old combos */
	removecombos(BLACK);
	removecombos(WHITE);
	removeemptyspots();

E 2
	/* compute new values */
	nextcolor = us;
	scanframes(BLACK);
	scanframes(WHITE);

	/* find the spot with the highest value */
	for (sp = sp1 = sp2 = &board[PT(T,19)]; --sp >= &board[PT(A,1)]; ) {
		if (sp->s_occ != EMPTY)
			continue;
D 2
		if (debug && (sp->s_combo[BLACK].s < 0x200 ||
		    sp->s_combo[WHITE].s < 0x200)) {
E 2
I 2
		if (debug && (sp->s_combo[BLACK].c.a == 1 ||
		    sp->s_combo[WHITE].c.a == 1)) {
E 2
			sprintf(fmtbuf, "- %s %x/%d %d %x/%d %d %d", stoc(sp - board),
				sp->s_combo[BLACK].s, sp->s_level[BLACK],
				sp->s_nforce[BLACK],
				sp->s_combo[WHITE].s, sp->s_level[WHITE],
				sp->s_nforce[WHITE],
				sp->s_wval);
			dlog(fmtbuf);
		}
		/* pick the best black move */
		if (better(sp, sp1, BLACK))
			sp1 = sp;
		/* pick the best white move */
		if (better(sp, sp2, WHITE))
			sp2 = sp;
	}
I 2

E 2
	if (debug) {
		sprintf(fmtbuf, "B %s %x/%d %d %x/%d %d %d %d",
			stoc(sp1 - board),
			sp1->s_combo[BLACK].s, sp1->s_level[BLACK],
			sp1->s_nforce[BLACK],
			sp1->s_combo[WHITE].s, sp1->s_level[WHITE],
D 2
			sp1->s_nforce[WHITE], sp1->s_wval, combolen[BLACK]);
E 2
I 2
			sp1->s_nforce[WHITE], sp1->s_wval);
E 2
		dlog(fmtbuf);
		sprintf(fmtbuf, "W %s %x/%d %d %x/%d %d %d %d",
			stoc(sp2 - board),
			sp2->s_combo[WHITE].s, sp2->s_level[WHITE],
			sp2->s_nforce[WHITE],
			sp2->s_combo[BLACK].s, sp2->s_level[BLACK],
D 2
			sp2->s_nforce[BLACK], sp2->s_wval, combolen[WHITE]);
E 2
I 2
			sp2->s_nforce[BLACK], sp2->s_wval);
E 2
		dlog(fmtbuf);
I 2
		/*
		 * Check for more than one force that can't
		 * all be blocked with one move.
		 */
		sp = (us == BLACK) ? sp2 : sp1;
		m = sp - board;
		if (sp->s_combo[!us].c.a == 1 && !BIT_TEST(forcemap, m))
			dlog("*** Can't be blocked");
E 2
	}
	if (us == BLACK) {
		Ocp = &sp1->s_combo[BLACK];
		Tcp = &sp2->s_combo[WHITE];
	} else {
		Tcp = &sp1->s_combo[BLACK];
		Ocp = &sp2->s_combo[WHITE];
		sp = sp1;
		sp1 = sp2;
		sp2 = sp;
	}
	/*
	 * Block their combo only if we have to (i.e., if they are one move
	 * away from completing a force and we don't have a force that
	 * we can complete which takes fewer moves to win).
	 */
	if (Tcp->c.a <= 1 && (Ocp->c.a > 1 ||
	    Tcp->c.a + Tcp->c.b < Ocp->c.a + Ocp->c.b))
		return (sp2 - board);
	return (sp1 - board);
}

/*
 * Return true if spot 'sp' is better than spot 'sp1' for color 'us'.
 */
better(sp, sp1, us)
	struct spotstr *sp;
	struct spotstr *sp1;
	int us;
{
D 2
	int them;
E 2
I 2
	int them, s, s1;
E 2

	if (sp->s_combo[us].s < sp1->s_combo[us].s)
		return (1);
	if (sp->s_combo[us].s != sp1->s_combo[us].s)
		return (0);
	if (sp->s_level[us] < sp1->s_level[us])
		return (1);
	if (sp->s_level[us] != sp1->s_level[us])
		return (0);
	if (sp->s_nforce[us] > sp1->s_nforce[us])
		return (1);
	if (sp->s_nforce[us] != sp1->s_nforce[us])
		return (0);

	them = !us;
I 2
	s = sp - board;
	s1 = sp1 - board;
	if (BIT_TEST(forcemap, s) && !BIT_TEST(forcemap, s1))
		return (1);
	if (!BIT_TEST(forcemap, s) && BIT_TEST(forcemap, s1))
		return (0);
E 2
	if (sp->s_combo[them].s < sp1->s_combo[them].s)
		return (1);
	if (sp->s_combo[them].s != sp1->s_combo[them].s)
		return (0);
	if (sp->s_level[them] < sp1->s_level[them])
		return (1);
	if (sp->s_level[them] != sp1->s_level[them])
		return (0);
	if (sp->s_nforce[them] > sp1->s_nforce[them])
		return (1);
	if (sp->s_nforce[them] != sp1->s_nforce[them])
		return (0);

	if (sp->s_wval > sp1->s_wval)
		return (1);
	if (sp->s_wval != sp1->s_wval)
		return (0);

#ifdef SVR4
	return (rand() & 1);
#else
	return (random() & 1);
#endif
}

D 2
int		curcolor;	/* implicit parameter to makecombo() */
int		curlevel;	/* implicit parameter to makecombo() */
E 2
I 2
int	curcolor;	/* implicit parameter to makecombo() */
int	curlevel;	/* implicit parameter to makecombo() */
E 2

/*
D 2
 * Scan the sorted list of frames and update the minimum combo values.
E 2
I 2
 * Scan the sorted list of non-empty frames and
 * update the minimum combo values for each empty spot.
 * Also, try to combine frames to find more complex (chained) moves.
E 2
 */
scanframes(color)
	int color;
{
	register struct combostr *cbp, *ecbp;
	register struct spotstr *sp;
D 2
	register union combo *cp;
	register struct elist *ep;
E 2
I 2
	register union comboval *cp;
	register struct elist *ep, *nep;
E 2
	register int i, r, d, n;
D 2
	union combo cb;
E 2
I 2
	union comboval cb;
E 2

	curcolor = color;

	/* check for empty list of frames */
	cbp = sortframes[color];
	if (cbp == (struct combostr *)0)
		return;

	/* quick check for four in a row */
	sp = &board[cbp->c_vertex];
	cb.s = sp->s_fval[color][d = cbp->c_dir].s;
	if (cb.s < 0x101) {
		d = dd[d];
		for (i = 5 + cb.c.b; --i >= 0; sp += d) {
			if (sp->s_occ != EMPTY)
				continue;
			sp->s_combo[color].s = cb.s;
			sp->s_level[color] = 1;
		}
		return;
	}

D 2
	/* update the minimum combo value for each spot in the frame */
	n = combolen[color];
E 2
I 2
	/*
	 * Update the minimum combo value for each spot in the frame
	 * and try making all combinations of two frames intersecting at
	 * an empty spot.
	 */
	n = combolen;
E 2
	ecbp = cbp;
	do {
		sp = &board[cbp->c_vertex];
		cp = &sp->s_fval[color][r = cbp->c_dir];
		d = dd[r];
		if (cp->c.b) {
I 2
			/*
			 * Since this is the first spot of an open ended
			 * frame, we treat it as a closed frame.
			 */
E 2
			cb.c.a = cp->c.a + 1;
			cb.c.b = 0;
			if (cb.s < sp->s_combo[color].s) {
				sp->s_combo[color].s = cb.s;
				sp->s_level[color] = 1;
			}
D 2
			makecombo2(cbp, sp, cb.s);
E 2
I 2
			/*
			 * Try combining other frames that intersect
			 * at this spot.
			 */
			makecombo2(cbp, sp, 0, cb.s);
E 2
			if (cp->s != 0x101)
				cb.s = cp->s;
I 2
			else if (color != nextcolor)
				memset(tmpmap, 0, sizeof(tmpmap));
E 2
			sp += d;
D 2
			i = 4;
E 2
I 2
			i = 1;
E 2
		} else {
			cb.s = cp->s;
D 2
			i = 5;
E 2
I 2
			i = 0;
E 2
		}
D 2
		for (; --i >= 0; sp += d) {	/* for each spot */
E 2
I 2
		for (; i < 5; i++, sp += d) {	/* for each spot */
E 2
			if (sp->s_occ != EMPTY)
				continue;
			if (cp->s < sp->s_combo[color].s) {
				sp->s_combo[color].s = cp->s;
				sp->s_level[color] = 1;
			}
D 2
			if (cp->s == 0x101)
E 2
I 2
			if (cp->s == 0x101) {
E 2
				sp->s_nforce[color]++;
D 2
			makecombo2(cbp, sp, cb.s);
E 2
I 2
				if (color != nextcolor) {
					n = sp - board;
					BIT_SET(tmpmap, n);
				}
			}
			/*
			 * Try combining other frames that intersect
			 * at this spot.
			 */
			makecombo2(cbp, sp, i, cb.s);
E 2
		}
I 2
		if (cp->s == 0x101 && color != nextcolor) {
			if (nforce == 0)
				memcpy(forcemap, tmpmap, sizeof(tmpmap));
			else {
				for (i = 0; i < MAPSZ; i++)
					forcemap[i] &= tmpmap[i];
			}
		}
E 2
		/* mark frame as having been processed */
		board[cbp->c_vertex].s_flg |= MFLAG << r;
	} while ((cbp = cbp->c_next) != ecbp);

D 2
	/* try to make new 3rd level combos, 4th level, etc. */
E 2
I 2
	/*
	 * Try to make new 3rd level combos, 4th level, etc.
	 * Limit the search depth early in the game.
	 */
E 2
	d = 2;
D 2
	while (combolen[color] > n) {
E 2
I 2
	while (d <= ((movenum + 1) >> 1) && combolen > n) {
E 2
		if (debug) {
D 2
			sprintf(fmtbuf, "%cL%d %d", "BW"[color], d,
				combolen[color] - n);
E 2
I 2
			sprintf(fmtbuf, "%cL%d %d %d %d", "BW"[color],
				d, combolen - n, combocnt, elistcnt);
E 2
			dlog(fmtbuf);
			refresh();
		}
D 2
		n = combolen[color];
E 2
I 2
		n = combolen;
E 2
		addframes(d);
		d++;
	}

	/* scan for combos at empty spots */
	for (sp = &board[PT(T,20)]; --sp >= &board[PT(A,1)]; ) {
D 2
		for (ep = sp->s_empty[color]; ep; ep = ep->e_next) {
E 2
I 2
		for (ep = sp->s_empty; ep; ep = nep) {
E 2
			cbp = ep->e_combo;
D 2
			if (cbp->c_combo.s < sp->s_combo[color].s) {
				sp->s_combo[color].s = cbp->c_combo.s;
				sp->s_level[color] = cbp->c_nframes;
			} else if (cbp->c_combo.s == sp->s_combo[color].s &&
			    cbp->c_nframes < sp->s_level[color])
				sp->s_level[color] = cbp->c_nframes;
E 2
I 2
			if (cbp->c_combo.s <= sp->s_combo[color].s) {
				if (cbp->c_combo.s != sp->s_combo[color].s) {
					sp->s_combo[color].s = cbp->c_combo.s;
					sp->s_level[color] = cbp->c_nframes;
				} else if (cbp->c_nframes < sp->s_level[color])
					sp->s_level[color] = cbp->c_nframes;
			}
			nep = ep->e_next;
			free(ep);
			elistcnt--;
E 2
		}
I 2
		sp->s_empty = (struct elist *)0;
		for (ep = sp->s_nempty; ep; ep = nep) {
			cbp = ep->e_combo;
			if (cbp->c_combo.s <= sp->s_combo[color].s) {
				if (cbp->c_combo.s != sp->s_combo[color].s) {
					sp->s_combo[color].s = cbp->c_combo.s;
					sp->s_level[color] = cbp->c_nframes;
				} else if (cbp->c_nframes < sp->s_level[color])
					sp->s_level[color] = cbp->c_nframes;
			}
			nep = ep->e_next;
			free(ep);
			elistcnt--;
		}
		sp->s_nempty = (struct elist *)0;
E 2
	}
I 2

	/* remove old combos */
	if ((cbp = sortcombos) != (struct combostr *)0) {
		struct combostr *ncbp;

		/* scan the list */
		ecbp = cbp;
		do {
			ncbp = cbp->c_next;
			free(cbp);
			combocnt--;
		} while ((cbp = ncbp) != ecbp);
		sortcombos = (struct combostr *)0;
	}
	combolen = 0;

#ifdef DEBUG
	if (combocnt) {
		sprintf(fmtbuf, "scanframes: %c combocnt %d", "BW"[color],
			combocnt);
		dlog(fmtbuf);
		whatsup(0);
	}
	if (elistcnt) {
		sprintf(fmtbuf, "scanframes: %c elistcnt %d", "BW"[color],
			elistcnt);
		dlog(fmtbuf);
		whatsup(0);
	}
#endif
E 2
}

/*
 * Compute all level 2 combos of frames intersecting spot 'osp'
 * within the frame 'ocbp' and combo value 's'.
 */
D 2
makecombo2(ocbp, osp, s)
E 2
I 2
makecombo2(ocbp, osp, off, s)
E 2
	struct combostr *ocbp;
	struct spotstr *osp;
I 2
	int off;
E 2
	int s;
{
	register struct spotstr *sp, *fsp;
D 2
	register struct combostr *cbp;
E 2
I 2
	register struct combostr *ncbp;
E 2
	register int f, r, d, c;
D 2
	int baseB, bmask, n;
	union combo ocb, fcb;
E 2
I 2
	int baseB, fcnt, emask, bmask, n;
	union comboval ocb, fcb;
	struct combostr **scbpp, *fcbp;
E 2

	/* try to combine a new frame with those found so far */
	ocb.s = s;
	baseB = ocb.c.a + ocb.c.b - 1;
I 2
	fcnt = ocb.c.a - 2;
	emask = fcnt ? ((ocb.c.b ? 0x1E : 0x1F) & ~(1 << off)) : 0;
E 2
	for (r = 4; --r >= 0; ) {			/* for each direction */
D 2
	    /* don't include frames that overlap ones already included */
E 2
I 2
	    /* don't include frames that overlap in the same direction */
E 2
	    if (r == ocbp->c_dir)
		continue;
	    d = dd[r];
I 2
	    /*
	     * Frame A combined with B is the same value as B combined with A
	     * so skip frames that have already been processed (MFLAG).
	     * Also skip blocked frames (BFLAG) and frames that are <1,x>
	     * since combining another frame with it isn't valid.
	     */
E 2
	    bmask = (BFLAG | FFLAG | MFLAG) << r;
	    fsp = osp;
D 2
	    for (f = 5; --f >= 0; fsp -= d) {		/* for each frame */
		/*
		 * Don't include frames that are blocked or
		 * part of a <1,x> combo.
		 */
E 2
I 2
	    for (f = 0; f < 5; f++, fsp -= d) {		/* for each frame */
E 2
		if (fsp->s_occ == BORDER)
		    break;
		if (fsp->s_flg & bmask)
		    continue;

		/* don't include frames of the wrong color */
		fcb.s = fsp->s_fval[curcolor][r].s;
		if (fcb.c.a >= MAXA)
		    continue;

		/*
		 * Get the combo value for this frame.
		 * If this is the end point of the frame,
		 * use the closed ended value for the frame.
		 */
D 2
		if (f == 4 && fcb.c.b || fcb.s == 0x101) {
E 2
I 2
		if (f == 0 && fcb.c.b || fcb.s == 0x101) {
E 2
		    fcb.c.a++;
		    fcb.c.b = 0;
		}

		/* compute combo value */
		c = fcb.c.a + ocb.c.a - 3;
D 2
		if (c > 3)
E 2
I 2
		if (c > 4)
E 2
		    continue;
		n = fcb.c.a + fcb.c.b - 1;
		if (baseB < n)
		    n = baseB;

		/* make a new combo! */
D 2
		cbp = (struct combostr *)malloc(sizeof(struct combostr));
		cbp->c_combo.c.a = c;
		cbp->c_combo.c.b = n;
		cbp->c_link[0] = ocbp;
		cbp->c_link[1] = fsp->s_frame[r];
		cbp->c_vertex = osp - board;
		cbp->c_nframes = 2;
		cbp->c_dir = 0;
		cbp->c_flg = 0;
		cbp->c_refcnt = 0;
E 2
I 2
		ncbp = (struct combostr *)malloc(sizeof(struct combostr) +
		    2 * sizeof(struct combostr *));
		scbpp = (struct combostr **)(ncbp + 1);
		fcbp = fsp->s_frame[r];
		if (ocbp < fcbp) {
		    scbpp[0] = ocbp;
		    scbpp[1] = fcbp;
		} else {
		    scbpp[0] = fcbp;
		    scbpp[1] = ocbp;
		}
		ncbp->c_combo.c.a = c;
		ncbp->c_combo.c.b = n;
		ncbp->c_link[0] = ocbp;
		ncbp->c_link[1] = fcbp;
		ncbp->c_linkv[0].s = ocb.s;
		ncbp->c_linkv[1].s = fcb.s;
		ncbp->c_voff[0] = off;
		ncbp->c_voff[1] = f;
		ncbp->c_vertex = osp - board;
		ncbp->c_nframes = 2;
		ncbp->c_dir = 0;
		ncbp->c_frameindex = 0;
		ncbp->c_flg = (ocb.c.b) ? C_OPEN_0 : 0;
		if (fcb.c.b)
		    ncbp->c_flg |= C_OPEN_1;
		ncbp->c_framecnt[0] = fcnt;
		ncbp->c_emask[0] = emask;
		ncbp->c_framecnt[1] = fcb.c.a - 2;
		ncbp->c_emask[1] = ncbp->c_framecnt[1] ?
		    ((fcb.c.b ? 0x1E : 0x1F) & ~(1 << f)) : 0;
		combocnt++;
E 2

		if (c == 1 && debug > 1 || debug > 3) {
D 2
		    sprintf(fmtbuf, "%c %s %x/2 r%d f%d %x",
			curcolor == BLACK ? 'b' : 'w',
			stoc(osp - board), cbp->c_combo.s, r, f, ocb.s);
E 2
I 2
		    sprintf(fmtbuf, "%c c %d %d m %x %x o %d %d",
			"bw"[curcolor],
			ncbp->c_framecnt[0], ncbp->c_framecnt[1],
			ncbp->c_emask[0], ncbp->c_emask[1],
			ncbp->c_voff[0], ncbp->c_voff[1]);
E 2
		    dlog(fmtbuf);
D 2
#ifdef DEBUG
		    markcombo(cbp, curcolor, 0);
		    bdisp();
		    whatsup(0);
		    clearcombo(cbp, curcolor, 0);
#endif
E 2
I 2
		    printcombo(ncbp, fmtbuf);
		    dlog(fmtbuf);
E 2
		}
		if (c > 1) {
D 2
		    if (ocb.c.a > 2)
			makeempty(cbp, ocbp, ocb.c.b);
		    if (fcb.c.a > 2)
			makeempty(cbp, cbp->c_link[1], fcb.c.b);
E 2
I 2
		    /* record the empty spots that will complete this combo */
		    makeempty(ncbp);
E 2

		    /* add the new combo to the end of the list */
D 2
		    appendcombo(cbp, curcolor);
E 2
I 2
		    appendcombo(ncbp, curcolor);
E 2
		} else {
D 2
		    updatecombo(cbp, curcolor);
		    free(cbp);
E 2
I 2
		    updatecombo(ncbp, curcolor);
		    free(ncbp);
		    combocnt--;
E 2
		}
I 2
#ifdef DEBUG
		if (c == 1 && debug > 1 || debug > 5) {
		    markcombo(ncbp);
		    bdisp();
		    whatsup(0);
		    clearcombo(ncbp, 0);
		}
#endif /* DEBUG */
E 2
	    }
	}
}

/*
D 2
 * Scan the sorted list of frames and try to combine into combos.
E 2
I 2
 * Scan the sorted list of frames and try to add a frame to
 * combinations of 'level' number of frames.
E 2
 */
addframes(level)
	int level;
{
	register struct combostr *cbp, *ecbp;
	register struct spotstr *sp, *fsp;
I 2
	register struct elist *ep, *nep;
E 2
	register int i, r, d;
D 2
	union combo fcb, cb;
E 2
I 2
	struct combostr **cbpp, *pcbp;
	union comboval fcb, cb;
E 2

	curlevel = level;

D 2
	/* clear MFLAG for this level */
E 2
I 2
	/* scan for combos at empty spots */
	i = curcolor;
	for (sp = &board[PT(T,20)]; --sp >= &board[PT(A,1)]; ) {
		for (ep = sp->s_empty; ep; ep = nep) {
			cbp = ep->e_combo;
			if (cbp->c_combo.s <= sp->s_combo[i].s) {
				if (cbp->c_combo.s != sp->s_combo[i].s) {
					sp->s_combo[i].s = cbp->c_combo.s;
					sp->s_level[i] = cbp->c_nframes;
				} else if (cbp->c_nframes < sp->s_level[i])
					sp->s_level[i] = cbp->c_nframes;
			}
			nep = ep->e_next;
			free(ep);
			elistcnt--;
		}
		sp->s_empty = sp->s_nempty;
		sp->s_nempty = (struct elist *)0;
	}

	/* try to add frames to the uncompleted combos at level curlevel */
E 2
	cbp = ecbp = sortframes[curcolor];
	do {
D 2
		board[cbp->c_vertex].s_flg &= ~MFLAGALL;
	} while ((cbp = cbp->c_next) != ecbp);

	cbp = ecbp;
	do {
E 2
		fsp = &board[cbp->c_vertex];
		r = cbp->c_dir;
		/* skip frames that are part of a <1,x> combo */
		if (fsp->s_flg & (FFLAG << r))
			continue;

		/*
		 * Don't include <1,x> combo frames,
D 2
		 * treat it as a blocked three in a row instead.
E 2
I 2
		 * treat it as a closed three in a row instead.
E 2
		 */
		fcb.s = fsp->s_fval[curcolor][r].s;
		if (fcb.s == 0x101)
			fcb.s = 0x200;

		/*
		 * If this is an open ended frame, use
		 * the combo value with the end closed.
		 */
		if (fsp->s_occ == EMPTY) {
			if (fcb.c.b) {
				cb.c.a = fcb.c.a + 1;
				cb.c.b = 0;
			} else
				cb.s = fcb.s;
D 2
			makecombo(cbp, fsp, cb.s);
E 2
I 2
			makecombo(cbp, fsp, 0, cb.s);
E 2
		}

		/*
		 * The next four spots are handled the same for both
		 * open and closed ended frames.
		 */
		d = dd[r];
		sp = fsp + d;
D 2
		for (i = 4; --i >= 0; sp += d) {
E 2
I 2
		for (i = 1; i < 5; i++, sp += d) {
E 2
			if (sp->s_occ != EMPTY)
				continue;
D 2
			makecombo(cbp, sp, fcb.s);
E 2
I 2
			makecombo(cbp, sp, i, fcb.s);
E 2
		}
D 2

		/* mark frame as having been processed */
		fsp->s_flg |= MFLAG << r;
E 2
	} while ((cbp = cbp->c_next) != ecbp);
I 2

	/* put all the combos in the hash list on the sorted list */
	cbpp = &hashcombos[FAREA];
	do {
		cbp = *--cbpp;
		if (cbp == (struct combostr *)0)
			continue;
		*cbpp = (struct combostr *)0;
		ecbp = sortcombos;
		if (ecbp == (struct combostr *)0)
			sortcombos = cbp;
		else {
			/* append to sort list */
			pcbp = ecbp->c_prev;
			pcbp->c_next = cbp;
			ecbp->c_prev = cbp->c_prev;
			cbp->c_prev->c_next = ecbp;
			cbp->c_prev = pcbp;
		}
	} while (cbpp != hashcombos);
E 2
}

/*
 * Compute all level N combos of frames intersecting spot 'osp'
 * within the frame 'ocbp' and combo value 's'.
 */
D 2
makecombo(ocbp, osp, s)
E 2
I 2
makecombo(ocbp, osp, off, s)
E 2
	struct combostr *ocbp;
	struct spotstr *osp;
I 2
	int off;
E 2
	int s;
{
	register struct combostr *cbp, *ncbp;
	register struct spotstr *sp;
	register struct elist *ep;
	register int n, c;
	struct elist *nep, **epp;
D 2
	struct combostr *fcbp;
	int baseB, verts, d;
	union combo ocb, cb;
E 2
I 2
	struct combostr **scbpp;
	int baseB, fcnt, emask, verts, d;
	union comboval ocb, cb;
	struct ovlp_info vertices[1];
E 2

	ocb.s = s;
	baseB = ocb.c.a + ocb.c.b - 1;
D 2
	for (ep = osp->s_empty[curcolor]; ep; ep = ep->e_next) {
	    /* don't try to combine this combo if it is the wrong level */
E 2
I 2
	fcnt = ocb.c.a - 2;
	emask = fcnt ? ((ocb.c.b ? 0x1E : 0x1F) & ~(1 << off)) : 0;
	for (ep = osp->s_empty; ep; ep = ep->e_next) {
	    /* check for various kinds of overlap */
E 2
	    cbp = ep->e_combo;
D 2
	    if (cbp->c_nframes > curlevel)
E 2
I 2
	    verts = checkframes(cbp, ocbp, osp, s, vertices);
	    if (verts < 0)
E 2
		continue;
D 2
	    if (cbp->c_nframes != curlevel)
		break;
E 2

D 2
	    /* don't include frames that overlap ones already included */
	    ncbp = ep->e_frame;
	    if (ncbp->c_dir == ocbp->c_dir ||
		(cbp->c_flg & C_LOOP) && cbp->c_dir == ocbp->c_dir ||
		(n = checkframes(cbp, ocbp, osp - board, ncbp)) < 0)
		    continue;

	    /* compute first half of combo value */
	    c = cbp->c_combo.c.a + ocb.c.a - 3;
	    if (c > 3)
		continue;

E 2
	    /* check to see if this frame forms a valid loop */
D 2
	    verts = 0;
	    if (n) {
		sp = &board[ocbp->c_vertex];
		d = dd[ocbp->c_dir];
		if (n = ocb.c.b)
			sp += d;
		for (; n < 5; n++, sp += d) {
		    if (sp->s_occ != EMPTY || sp == osp)
			continue;
		    for (nep = sp->s_empty[curcolor]; nep; nep = nep->e_next) {
			if (nep->e_combo == cbp) {
			    verts++;
			    fcbp = nep->e_frame;
			    continue;
			}
			if (nep->e_combo->c_nframes < cbp->c_nframes)
			    break;
		    }
E 2
I 2
	    if (verts) {
		sp = &board[vertices[0].o_intersect];
#ifdef DEBUG
		if (sp->s_occ != EMPTY) {
		    sprintf(fmtbuf, "loop: %c %s", "BW"[curcolor],
			stoc(sp - board));
		    dlog(fmtbuf);
		    whatsup(0);
E 2
		}
D 2
#if 0
		{
		char *str;
		sprintf(fmtbuf, "%c v%d %s%c",
		    curcolor == BLACK ? 'b' : 'w', verts,
		    stoc(ocbp->c_vertex), pdir[ocbp->c_dir]);
		str = fmtbuf + strlen(fmtbuf);
		for (; cbp->c_link[1]; cbp = cbp->c_link[0]) {
		    sprintf(str, " %s%c", stoc(cbp->c_link[1]->c_vertex),
			pdir[cbp->c_link[1]->c_dir]);
		    str += strlen(str);
		}
		sprintf(str, " %s%c", stoc(cbp->c_vertex), pdir[cbp->c_dir]);
		dlog(fmtbuf);
		cbp = ep->e_combo;
		}
E 2
#endif
I 2
		/*
		 * It is a valid loop if the intersection spot
		 * of the frame we are trying to attach is one
		 * of the completion spots of the combostr
		 * we are trying to attach the frame to.
		 */
		for (nep = sp->s_empty; nep; nep = nep->e_next) {
		    if (nep->e_combo == cbp)
			goto fnd;
		    if (nep->e_combo->c_nframes < cbp->c_nframes)
			break;
		}
E 2
		/* frame overlaps but not at a valid spot */
D 2
		if (verts == 0 || ocb.c.a < 3)
		    continue;
E 2
I 2
		continue;
	    fnd:
		;
E 2
	    }

D 2
	    /* compute second half of combo value */
	    cb.s = board[ncbp->c_vertex].s_fval[curcolor][ncbp->c_dir].s;
	    n = cb.c.a + cb.c.b - 1;
E 2
I 2
	    /* compute the first half of the combo value */
	    c = cbp->c_combo.c.a + ocb.c.a - verts - 3;
	    if (c > 4)
		continue;

	    /* compute the second half of the combo value */
	    n = ep->e_fval.c.a + ep->e_fval.c.b - 1;
E 2
	    if (baseB < n)
		n = baseB;

	    /* make a new combo! */
D 2
	    ncbp = (struct combostr *)malloc(sizeof(struct combostr));
	    c -= verts;
E 2
I 2
	    ncbp = (struct combostr *)malloc(sizeof(struct combostr) +
		(cbp->c_nframes + 1) * sizeof(struct combostr *));
	    scbpp = (struct combostr **)(ncbp + 1);
	    if (sortcombo(scbpp, (struct combostr **)(cbp + 1), ocbp)) {
		free(ncbp);
		continue;
	    }
	    combocnt++;

E 2
	    ncbp->c_combo.c.a = c;
	    ncbp->c_combo.c.b = n;
	    ncbp->c_link[0] = cbp;
	    ncbp->c_link[1] = ocbp;
I 2
	    ncbp->c_linkv[1].s = ocb.s;
	    ncbp->c_voff[1] = off;
E 2
	    ncbp->c_vertex = osp - board;
	    ncbp->c_nframes = cbp->c_nframes + 1;
D 2
	    ncbp->c_refcnt = 0;
E 2
I 2
	    ncbp->c_flg = ocb.c.b ? C_OPEN_1 : 0;
	    ncbp->c_frameindex = ep->e_frameindex;
	    /*
	     * Update the completion spot mask of the frame we
	     * are attaching 'ocbp' to so the intersection isn't
	     * listed twice.
	     */
	    ncbp->c_framecnt[0] = ep->e_framecnt;
	    ncbp->c_emask[0] = ep->e_emask;
E 2
	    if (verts) {
D 2
		ncbp->c_flg = C_LOOP;
		ncbp->c_dir = fcbp->c_dir;

		/* add the combo to the list of empty spots */
		nep = (struct elist *)malloc(sizeof(struct elist));
		nep->e_combo = ncbp;
		nep->e_frame = ocbp;
		if (debug > 2) {
		    sprintf(fmtbuf, "e %s", stoc(ncbp->c_vertex));
		    dlog(fmtbuf);
		}

		/* sort by the number of frames in the combo */
		epp = &board[ncbp->c_vertex].s_empty[curcolor];
		while (*epp) {
		    if (cbp->c_nframes >= (*epp)->e_combo->c_nframes)
			break;
		    epp = &(*epp)->e_next;
		}
		nep->e_next = *epp;
		*epp = nep;
E 2
I 2
		ncbp->c_flg |= C_LOOP;
		ncbp->c_dir = vertices[0].o_frameindex;
		ncbp->c_framecnt[1] = fcnt - 1;
		if (ncbp->c_framecnt[1]) {
		    n = (vertices[0].o_intersect - ocbp->c_vertex) /
			dd[ocbp->c_dir];
		    ncbp->c_emask[1] = emask & ~(1 << n);
		} else
		    ncbp->c_emask[1] = 0;
		ncbp->c_voff[0] = vertices[0].o_off;
E 2
	    } else {
D 2
		ncbp->c_flg = 0;
E 2
		ncbp->c_dir = 0;
D 2
		if (ocb.c.a > 2)
		    makeempty(ncbp, ocbp, ocb.c.b);
E 2
I 2
		ncbp->c_framecnt[1] = fcnt;
		ncbp->c_emask[1] = emask;
		ncbp->c_voff[0] = ep->e_off;
E 2
	    }
D 2
	    if (verts > 1 && debug || c == 1 && debug > 1 || debug > 2) {
		char *str;
E 2

D 2
		sprintf(fmtbuf, "%c %s%c %x v%d %x/%d",
		    curcolor == BLACK ? 'b' : 'w',
		    stoc(osp - board), pdir[ocbp->c_dir], ocb.s,
		    verts, ncbp->c_combo.s, ncbp->c_nframes);
E 2
I 2
	    if (c == 1 && debug > 1 || debug > 3) {
		sprintf(fmtbuf, "%c v%d i%d d%d c %d %d m %x %x o %d %d",
		    "bw"[curcolor], verts, ncbp->c_frameindex, ncbp->c_dir,
		    ncbp->c_framecnt[0], ncbp->c_framecnt[1],
		    ncbp->c_emask[0], ncbp->c_emask[1],
		    ncbp->c_voff[0], ncbp->c_voff[1]);
E 2
		dlog(fmtbuf);
D 2
		str = fmtbuf;
		for (cbp = ncbp; cbp->c_link[1]; cbp = cbp->c_link[0]) {
		    sprintf(str, " %s%c", stoc(cbp->c_link[1]->c_vertex),
			pdir[cbp->c_link[1]->c_dir]);
		    str += strlen(str);
		}
		sprintf(str, " %s%c", stoc(cbp->c_vertex), pdir[cbp->c_dir]);
E 2
I 2
		printcombo(ncbp, fmtbuf);
E 2
		dlog(fmtbuf);
D 2
#ifdef DEBUG
		markcombo(ncbp, curcolor, 0);
		bdisp();
		whatsup(0);
		clearcombo(ncbp, curcolor, 0);
#endif
E 2
	    }
	    if (c > 1) {
D 2
		/* add the new combo to the end of the list */
		appendcombo(ncbp, curcolor);
E 2
I 2
		/* record the empty spots that will complete this combo */
		makeempty(ncbp);
		combolen++;
E 2
	    } else {
I 2
		/* update board values */
E 2
		updatecombo(ncbp, curcolor);
D 2
		free(ncbp);
E 2
	    }
I 2
#ifdef DEBUG
	    if (c == 1 && debug > 1 || debug > 4) {
		markcombo(ncbp);
		bdisp();
		whatsup(0);
		clearcombo(ncbp, 0);
	    }
#endif /* DEBUG */
E 2
	}
}

I 2
#define MAXDEPTH	100
struct elist	einfo[MAXDEPTH];
struct combostr	*ecombo[MAXDEPTH];	/* separate from elist to save space */

E 2
/*
D 2
 * Add the combostr 'cbp' to the empty spots list for each empty spot
 * in the frame 'fcbp' except for the intersection.
 * 's' is zero if 'fcbp' is a closed ended frame, else it is one.
 * Return the number of valid intersections with ocbp for detecting loops.
E 2
I 2
 * Add the combostr 'ocbp' to the empty spots list for each empty spot
 * in 'ocbp' that will complete the combo.
E 2
 */
D 2
makeempty(cbp, fcbp, s)
	struct combostr *cbp;
	struct combostr *fcbp;
	int s;
E 2
I 2
makeempty(ocbp)
	struct combostr *ocbp;
E 2
{
D 2
	struct spotstr *sp, *vsp;
	struct elist *ep, **epp;
	int d;
E 2
I 2
	struct combostr *cbp, *tcbp, **cbpp;
	struct elist *ep, *nep, **epp;
	struct spotstr *sp;
	int s, d, m, emask, i;
	int nframes;
E 2

	if (debug > 2) {
D 2
		sprintf(fmtbuf, "E %s%c s%d", stoc(fcbp->c_vertex),
			pdir[fcbp->c_dir], s);
		sprintf(fmtbuf + strlen(fmtbuf), " %s", stoc(cbp->c_vertex));
E 2
I 2
		sprintf(fmtbuf, "E%c ", "bw"[curcolor]);
		printcombo(ocbp, fmtbuf + 3);
E 2
		dlog(fmtbuf);
	}
D 2
	vsp = &board[cbp->c_vertex];
	sp = &board[fcbp->c_vertex];
	d = dd[fcbp->c_dir];
	if (s)
		sp += d;
	for (; s < 5; s++, sp += d) {
		if (sp->s_occ != EMPTY || sp == vsp)
			continue;
E 2

D 2
		/* add the combo to the list of empty spots */
		ep = (struct elist *)malloc(sizeof(struct elist));
E 2
I 2
	/* should never happen but check anyway */
	if ((nframes = ocbp->c_nframes) >= MAXDEPTH)
		return;

	/*
	 * The lower level combo can be pointed to by more than one
	 * higher level 'struct combostr' so we can't modify the
	 * lower level. Therefore, higher level combos store the
	 * real mask of the lower level frame in c_emask[0] and the
	 * frame number in c_frameindex.
	 *
	 * First we traverse the tree from top to bottom and save the
	 * connection info. Then we traverse the tree from bottom to
	 * top overwriting lower levels with the newer emask information.
	 */
	ep = &einfo[nframes];
	cbpp = &ecombo[nframes];
	for (cbp = ocbp; tcbp = cbp->c_link[1]; cbp = cbp->c_link[0]) {
		ep--;
E 2
		ep->e_combo = cbp;
D 2
		ep->e_frame = fcbp;
		if (debug > 2) {
			sprintf(fmtbuf, "e %s", stoc(sp - board));
			dlog(fmtbuf);
E 2
I 2
		*--cbpp = cbp->c_link[1];
		ep->e_off = cbp->c_voff[1];
		ep->e_frameindex = cbp->c_frameindex;
		ep->e_fval.s = cbp->c_linkv[1].s;
		ep->e_framecnt = cbp->c_framecnt[1];
		ep->e_emask = cbp->c_emask[1];
	}
	cbp = ep->e_combo;
	ep--;
	ep->e_combo = cbp;
	*--cbpp = cbp->c_link[0];
	ep->e_off = cbp->c_voff[0];
	ep->e_frameindex = 0;
	ep->e_fval.s = cbp->c_linkv[0].s;
	ep->e_framecnt = cbp->c_framecnt[0];
	ep->e_emask = cbp->c_emask[0];

	/* now update the emask info */
	s = 0;
	for (i = 2, ep += 2; i < nframes; i++, ep++) {
		cbp = ep->e_combo;
		nep = &einfo[ep->e_frameindex];
		nep->e_framecnt = cbp->c_framecnt[0];
		nep->e_emask = cbp->c_emask[0];

		if (cbp->c_flg & C_LOOP) {
			s++;
			/*
			 * Account for the fact that this frame connects
			 * to a previous one (thus forming a loop).
			 */
			nep = &einfo[cbp->c_dir];
			if (--nep->e_framecnt)
				nep->e_emask &= ~(1 << cbp->c_voff[0]);
			else
				nep->e_emask = 0;
E 2
		}
I 2
	}
E 2

D 2
		/* sort by the number of frames in the combo */
		epp = &sp->s_empty[curcolor];
		while (*epp) {
			if (cbp->c_nframes >= (*epp)->e_combo->c_nframes)
				break;
			epp = &(*epp)->e_next;
E 2
I 2
	/*
	 * We only need to update the emask values of "complete" loops
	 * to include the intersection spots.
	 */
	if (s && ocbp->c_combo.c.a == 2) {
		/* process loops from the top down */
		ep = &einfo[nframes];
		do {
			ep--;
			cbp = ep->e_combo;
			if (!(cbp->c_flg & C_LOOP))
				continue;

			/*
			 * Update the emask values to include the
			 * intersection spots.
			 */
			nep = &einfo[cbp->c_dir];
			nep->e_framecnt = 1;
			nep->e_emask = 1 << cbp->c_voff[0];
			ep->e_framecnt = 1;
			ep->e_emask = 1 << ep->e_off;
			ep = &einfo[ep->e_frameindex];
			do {
				ep->e_framecnt = 1;
				ep->e_emask = 1 << ep->e_off;
				ep = &einfo[ep->e_frameindex];
			} while (ep > nep);
		} while (ep != einfo);
	}

	/* check all the frames for completion spots */
	for (i = 0, ep = einfo, cbpp = ecombo; i < nframes; i++, ep++, cbpp++) {
		/* skip this frame if there are no incomplete spots in it */
		if ((emask = ep->e_emask) == 0)
			continue;
		cbp = *cbpp;
		sp = &board[cbp->c_vertex];
		d = dd[cbp->c_dir];
		for (s = 0, m = 1; s < 5; s++, sp += d, m <<= 1) {
			if (sp->s_occ != EMPTY || !(emask & m))
				continue;

			/* add the combo to the list of empty spots */
			nep = (struct elist *)malloc(sizeof(struct elist));
			nep->e_combo = ocbp;
			nep->e_off = s;
			nep->e_frameindex = i;
			if (ep->e_framecnt > 1) {
				nep->e_framecnt = ep->e_framecnt - 1;
				nep->e_emask = emask & ~m;
			} else {
				nep->e_framecnt = 0;
				nep->e_emask = 0;
			}
			nep->e_fval.s = ep->e_fval.s;
			if (debug > 2) {
				sprintf(fmtbuf, "e %s o%d i%d c%d m%x %x",
					stoc(sp - board),
					nep->e_off,
					nep->e_frameindex,
					nep->e_framecnt,
					nep->e_emask,
					nep->e_fval.s);
				dlog(fmtbuf);
			}

			/* sort by the number of frames in the combo */
			nep->e_next = sp->s_nempty;
			sp->s_nempty = nep;
			elistcnt++;
E 2
		}
D 2
		ep->e_next = *epp;
		*epp = ep;
E 2
	}
}

/*
 * Update the board value based on the combostr.
 * This is called only if 'cbp' is a <1,x> combo.
 * We handle things differently depending on whether the next move
 * would be trying to "complete" the combo or trying to block it.
 */
updatecombo(cbp, color)
	struct combostr *cbp;
	int color;
{
	register struct framestr *fp;
	register struct spotstr *sp;
	register struct combostr *tcbp;
	register int i, d;
D 2
	int nframes, vertex;
	union combo cb;
E 2
I 2
	int nframes, flg, s;
	union comboval cb;
E 2

I 2
	/* save the top level value for the whole combo */
	cb.c.a = cbp->c_combo.c.a;
	nframes = cbp->c_nframes;

	if (color != nextcolor)
		memset(tmpmap, 0, sizeof(tmpmap));

E 2
	for (; tcbp = cbp->c_link[1]; cbp = cbp->c_link[0]) {
I 2
		flg = cbp->c_flg;
		cb.c.b = cbp->c_combo.c.b;
E 2
		if (color == nextcolor) {
			/* update the board value for the vertex */
			sp = &board[cbp->c_vertex];
			sp->s_nforce[color]++;
D 2
			if (cbp->c_combo.s < sp->s_combo[color].s) {
				sp->s_combo[color].s = cbp->c_combo.s;
				sp->s_level[color] = cbp->c_nframes;
			} else if (cbp->c_combo.s == sp->s_combo[color].s &&
			    cbp->c_nframes < sp->s_level[color])
				sp->s_level[color] = cbp->c_nframes;
E 2
I 2
			if (cb.s <= sp->s_combo[color].s) {
				if (cb.s != sp->s_combo[color].s) {
					sp->s_combo[color].s = cb.s;
					sp->s_level[color] = nframes;
				} else if (nframes < sp->s_level[color])
					sp->s_level[color] = nframes;
			}
E 2
		} else {
			/* update the board values for each spot in frame */
D 2
			vertex = cbp->c_vertex;
			sp = &board[tcbp->c_vertex];
			if (sp->s_fval[color][tcbp->c_dir].c.b &&
			    tcbp->c_vertex != vertex)
				i = 6;
			else
				i = 5;
E 2
I 2
			sp = &board[s = tcbp->c_vertex];
E 2
			d = dd[tcbp->c_dir];
D 2
			cb.s = cbp->c_combo.s;
			nframes = cbp->c_nframes;
			for (; --i >= 0; sp += d) {
E 2
I 2
			i = (flg & C_OPEN_1) ? 6 : 5;
			for (; --i >= 0; sp += d, s += d) {
				if (sp->s_occ != EMPTY)
					continue;
E 2
				sp->s_nforce[color]++;
D 2
				if (cb.s < sp->s_combo[color].s) {
					sp->s_combo[color].s = cb.s;
					sp->s_level[color] = nframes;
				} else if (cb.s == sp->s_combo[color].s &&
				    cbp->c_nframes < sp->s_level[color])
					sp->s_level[color] = nframes;
E 2
I 2
				if (cb.s <= sp->s_combo[color].s) {
					if (cb.s != sp->s_combo[color].s) {
						sp->s_combo[color].s = cb.s;
						sp->s_level[color] = nframes;
					} else if (nframes < sp->s_level[color])
						sp->s_level[color] = nframes;
				}
				BIT_SET(tmpmap, s);
E 2
			}
		}

		/* mark the frame as being part of a <1,x> combo */
		board[tcbp->c_vertex].s_flg |= FFLAG << tcbp->c_dir;
	}

	if (color != nextcolor) {
		/* update the board values for each spot in frame */
D 2
		sp = &board[cbp->c_vertex];
		if (sp->s_fval[color][cbp->c_dir].c.b &&
		    cbp->c_vertex != vertex)
			i = 6;
		else
			i = 5;
E 2
I 2
		sp = &board[s = cbp->c_vertex];
E 2
		d = dd[cbp->c_dir];
D 2
		for (; --i >= 0; sp += d) {
E 2
I 2
		i = (flg & C_OPEN_0) ? 6 : 5;
		for (; --i >= 0; sp += d, s += d) {
			if (sp->s_occ != EMPTY)
				continue;
E 2
			sp->s_nforce[color]++;
D 2
			if (cb.s < sp->s_combo[color].s) {
				sp->s_combo[color].s = cb.s;
				sp->s_level[color] = nframes;
			} else if (cb.s == sp->s_combo[color].s &&
			    cbp->c_nframes < sp->s_level[color])
				sp->s_level[color] = nframes;
E 2
I 2
			if (cb.s <= sp->s_combo[color].s) {
				if (cb.s != sp->s_combo[color].s) {
					sp->s_combo[color].s = cb.s;
					sp->s_level[color] = nframes;
				} else if (nframes < sp->s_level[color])
					sp->s_level[color] = nframes;
			}
			BIT_SET(tmpmap, s);
E 2
		}
I 2
		if (nforce == 0)
			memcpy(forcemap, tmpmap, sizeof(tmpmap));
		else {
			for (i = 0; i < MAPSZ; i++)
				forcemap[i] &= tmpmap[i];
		}
		nforce++;
E 2
	}

	/* mark the frame as being part of a <1,x> combo */
	board[cbp->c_vertex].s_flg |= FFLAG << cbp->c_dir;
}

/*
D 2
 * Free all elist structures.
 */
removeemptyspots()
{
	register struct elist *ep, *nep;
	register struct spotstr *sp;
	int i;

	for (sp = &board[PT(T,20)]; --sp >= &board[PT(A,1)]; ) {
		for (i = BLACK; i <= WHITE; i++) {
			for (ep = sp->s_empty[i]; ep; ep = nep) {
				nep = ep->e_next;
				free(ep);
			}
			sp->s_empty[i] = (struct elist *)0;
		}
	}
}

/*
 * Remove all combo structures.
 */
removecombos(color)
	int color;
{
	register struct combostr *cbp, *ncbp, *endcbp;

	/* check the list */
	if ((cbp = sortcombos[color]) == (struct combostr *)0)
		return;

	/* scan the list */
	endcbp = cbp;
	do {
		ncbp = cbp->c_next;
		cbp->c_next = (struct combostr *)0;
		cbp->c_prev = (struct combostr *)0;
		free(cbp);
		cbp = ncbp;
	} while (cbp != endcbp);

	sortcombos[color] = (struct combostr *)0;
	combolen[color] = 0;
}

/*
E 2
 * Add combo to the end of the list.
 */
appendcombo(cbp, color)
	struct combostr *cbp;
	int color;
{
	struct combostr *pcbp, *ncbp;

D 2
	combolen[color]++;
	ncbp = sortcombos[color];
E 2
I 2
	combolen++;
	ncbp = sortcombos;
E 2
	if (ncbp == (struct combostr *)0) {
D 2
		sortcombos[color] = cbp;
E 2
I 2
		sortcombos = cbp;
E 2
		cbp->c_next = cbp;
		cbp->c_prev = cbp;
		return;
	}
	pcbp = ncbp->c_prev;
	cbp->c_next = ncbp;
	cbp->c_prev = pcbp;
	ncbp->c_prev = cbp;
	pcbp->c_next = cbp;
}

/*
D 2
 * Return positive if frame 'fcbp' overlaps any of the frames in 'cbp'
 * other than the frame 'ecbp'.
 * Return -1 if any of the frames in 'cbp' are marked or part of a <1,x> combo.
 * Else, return zero.
E 2
I 2
 * Return zero if it is valid to combine frame 'fcbp' with the frames
 * in 'cbp' and forms a linked chain of frames (i.e., a tree; no loops).
 * Return positive if combining frame 'fcbp' to the frames in 'cbp'
 * would form some kind of valid loop. Also return the intersection spots
 * in 'vertices[]' beside the known intersection at spot 'osp'.
 * Return -1 if 'fcbp' should not be combined with 'cbp'.
 * 's' is the combo value for frame 'fcpb'.
E 2
 */
D 2
checkframes(cbp, fcbp, vertex, ecbp)
E 2
I 2
checkframes(cbp, fcbp, osp, s, vertices)
E 2
	struct combostr *cbp;
	struct combostr *fcbp;
D 2
	int vertex;
	struct combostr *ecbp;
E 2
I 2
	struct spotstr *osp;
	int s;
	struct ovlp_info *vertices;
E 2
{
D 2
	struct combostr *tcbp;
	char *str;
	int i, n, mask;
E 2
I 2
	struct combostr *tcbp, *lcbp;
	int i, n, mask, flg, verts, loop, index, fcnt;
	union comboval cb;
	u_char *str;
E 2
	short *ip;

I 2
	cb.s = s;
	fcnt = cb.c.a - 2;
	verts = 0;
	loop = 0;
	index = cbp->c_nframes;
E 2
	n = (fcbp - frames) * FAREA;
	str = &overlap[n];
	ip = &intersect[n];
D 2
	i = vertex == fcbp->c_vertex ? 2 : 0;
	for (; tcbp = cbp->c_link[1]; cbp = cbp->c_link[0]) {
#if 0
		if (board[tcbp->c_vertex].s_flg & (FFLAG << tcbp->c_dir))
E 2
I 2
	/*
	 * i == which overlap bit to test based on whether 'fcbp' is
	 * an open or closed frame.
	 */
	i = cb.c.b ? 2 : 0;
	for (; tcbp = cbp->c_link[1]; lcbp = cbp, cbp = cbp->c_link[0]) {
		if (tcbp == fcbp)
			return (-1);	/* fcbp is already included */

		/* check for intersection of 'tcbp' with 'fcbp' */
		index--;
		mask = str[tcbp - frames];
		flg = cbp->c_flg;
		n = i + ((flg & C_OPEN_1) != 0);
		if (mask & (1 << n)) {
			/*
			 * The two frames are not independent if they
			 * both lie in the same line and intersect at
			 * more than one point.
			 */
			if (tcbp->c_dir == fcbp->c_dir && (mask & (0x10 << n)))
				return (-1);
			/*
			 * If this is not the spot we are attaching
			 * 'fcbp' to and it is a reasonable intersection
			 * spot, then there might be a loop.
			 */
			n = ip[tcbp - frames];
			if (osp != &board[n]) {
				/* check to see if this is a valid loop */
				if (verts)
					return (-1);
				if (fcnt == 0 || cbp->c_framecnt[1] == 0)
					return (-1);
				/*
				 * Check to be sure the intersection is not
				 * one of the end points if it is an open
				 * ended frame.
				 */
				if ((flg & C_OPEN_1) &&
				    (n == tcbp->c_vertex ||
				     n == tcbp->c_vertex + 5 * dd[tcbp->c_dir]))
					return (-1);	/* invalid overlap */
				if (cb.c.b &&
				    (n == fcbp->c_vertex ||
				     n == fcbp->c_vertex + 5 * dd[fcbp->c_dir]))
					return (-1);	/* invalid overlap */

				vertices->o_intersect = n;
				vertices->o_fcombo = cbp;
				vertices->o_link = 1;
				vertices->o_off = (n - tcbp->c_vertex) /
					dd[tcbp->c_dir];
				vertices->o_frameindex = index;
				verts++;
			}
		}
		n = i + ((flg & C_OPEN_0) != 0);
	}
	if (cbp == fcbp)
		return (-1);	/* fcbp is already included */

	/* check for intersection of 'cbp' with 'fcbp' */
	mask = str[cbp - frames];
	if (mask & (1 << n)) {
		/*
		 * The two frames are not independent if they
		 * both lie in the same line and intersect at
		 * more than one point.
		 */
		if (cbp->c_dir == fcbp->c_dir && (mask & (0x10 << n)))
E 2
			return (-1);
D 2
#endif
		vertex = cbp->c_vertex;
		if (tcbp == ecbp)
			continue;
		n = tcbp - frames;
		if (board[ip[n]].s_occ != EMPTY)
			continue;
		mask = str[n];
		if (mask & (1 << (i + (tcbp->c_vertex == vertex))))
			return (1);
E 2
I 2
		/*
		 * If this is not the spot we are attaching
		 * 'fcbp' to and it is a reasonable intersection
		 * spot, then there might be a loop.
		 */
		n = ip[cbp - frames];
		if (osp != &board[n]) {
			/* check to see if this is a valid loop */
			if (verts)
				return (-1);
			if (fcnt == 0 || lcbp->c_framecnt[0] == 0)
				return (-1);
			/*
			 * Check to be sure the intersection is not
			 * one of the end points if it is an open
			 * ended frame.
			 */
			if ((flg & C_OPEN_0) &&
			    (n == cbp->c_vertex ||
			     n == cbp->c_vertex + 5 * dd[cbp->c_dir]))
				return (-1);	/* invalid overlap */
			if (cb.c.b &&
			    (n == fcbp->c_vertex ||
			     n == fcbp->c_vertex + 5 * dd[fcbp->c_dir]))
				return (-1);	/* invalid overlap */

			vertices->o_intersect = n;
			vertices->o_fcombo = lcbp;
			vertices->o_link = 0;
			vertices->o_off = (n - cbp->c_vertex) /
				dd[cbp->c_dir];
			vertices->o_frameindex = 0;
			verts++;
		}
E 2
	}
D 2
#if 0
	if (board[cbp->c_vertex].s_flg & (FFLAG << cbp->c_dir))
		return (-1);
#endif
	if (cbp == ecbp)
		return (0);
	n = cbp - frames;
	if (board[ip[n]].s_occ != EMPTY)
		return (0);
	mask = str[n];
	return (mask & (1 << (i + (cbp->c_vertex == vertex))));
E 2
I 2
	return (verts);
E 2
}

I 2
/*
 * Merge sort the frame 'fcbp' and the sorted list of frames 'cbpp' and
 * store the result in 'scbpp'. 'curlevel' is the size of the 'cbpp' array.
 * Return true if this list of frames is already in the hash list.
 * Otherwise, add the new combo to the hash list.
 */
sortcombo(scbpp, cbpp, fcbp)
	struct combostr **scbpp;
	struct combostr **cbpp;
	struct combostr *fcbp;
{
	struct combostr **spp, **cpp;
	struct combostr *cbp, *ecbp;
	int n, inx;

E 2
#ifdef DEBUG
D 2
markcombo(cbp, color, vertex)
E 2
I 2
	if (debug > 3) {
		char *str;

		sprintf(fmtbuf, "sortc: %s%c l%d", stoc(fcbp->c_vertex),
			pdir[fcbp->c_dir], curlevel);
		dlog(fmtbuf);
		str = fmtbuf;
		for (cpp = cbpp; cpp < cbpp + curlevel; cpp++) {
			sprintf(str, " %s%c", stoc((*cpp)->c_vertex),
				pdir[(*cpp)->c_dir]);
			str += strlen(str);
		}
		dlog(fmtbuf);
	}
#endif /* DEBUG */

	/* first build the new sorted list */
	n = curlevel + 1;
	spp = scbpp + n;
	cpp = cbpp + curlevel;
	do {
		cpp--;
		if (fcbp > *cpp) {
			*--spp = fcbp;
			do
				*--spp = *cpp;
			while (cpp-- != cbpp);
			goto inserted;
		}
		*--spp = *cpp;
	} while (cpp != cbpp);
	*--spp = fcbp;
inserted:

	/* now check to see if this list of frames has already been seen */
	cbp = hashcombos[inx = *scbpp - frames];
	if (cbp == (struct combostr *)0) {
		/*
		 * Easy case, this list hasn't been seen.
		 * Add it to the hash list.
		 */
		fcbp = (struct combostr *)
			((char *)scbpp - sizeof(struct combostr));
		hashcombos[inx] = fcbp;
		fcbp->c_next = fcbp->c_prev = fcbp;
		return (0);
	}
	ecbp = cbp;
	do {
		cbpp = (struct combostr **)(cbp + 1);
		cpp = cbpp + n;
		spp = scbpp + n;
		cbpp++;	/* first frame is always the same */
		do {
			if (*--spp != *--cpp)
				goto next;
		} while (cpp != cbpp);
		/* we found a match */
#ifdef DEBUG
		if (debug > 3) {
			char *str;

			sprintf(fmtbuf, "sort1: n%d", n);
			dlog(fmtbuf);
			str = fmtbuf;
			for (cpp = scbpp; cpp < scbpp + n; cpp++) {
				sprintf(str, " %s%c", stoc((*cpp)->c_vertex),
					pdir[(*cpp)->c_dir]);
				str += strlen(str);
			}
			dlog(fmtbuf);
			printcombo(cbp, fmtbuf);
			dlog(fmtbuf);
			str = fmtbuf;
			cbpp--;
			for (cpp = cbpp; cpp < cbpp + n; cpp++) {
				sprintf(str, " %s%c", stoc((*cpp)->c_vertex),
					pdir[(*cpp)->c_dir]);
				str += strlen(str);
			}
			dlog(fmtbuf);
		}
#endif /* DEBUG */
		return (1);
	next:
		;
	} while ((cbp = cbp->c_next) != ecbp);
	/*
	 * This list of frames hasn't been seen.
	 * Add it to the hash list.
	 */
	ecbp = cbp->c_prev;
	fcbp = (struct combostr *)((char *)scbpp - sizeof(struct combostr));
	fcbp->c_next = cbp;
	fcbp->c_prev = ecbp;
	cbp->c_prev = fcbp;
	ecbp->c_next = fcbp;
	return (0);
}

/*
 * Print the combo into string 'str'.
 */
printcombo(cbp, str)
E 2
	struct combostr *cbp;
D 2
	int color;
	int vertex;
E 2
I 2
	char *str;
E 2
{
D 2
	register struct spotstr *sp;
E 2
	struct combostr *tcbp;
D 2
	int i, d, r, n, mask;
E 2

D 2
	for (; tcbp = cbp->c_link[1]; cbp = cbp->c_link[0])
		markcombo(tcbp, color, vertex = cbp->c_vertex);
	sp = &board[cbp->c_vertex];
	d = dd[r = cbp->c_dir];
	mask = (IFLAG | CFLAG) << r;
	n = sp->s_fval[color][r].c.b && cbp->c_vertex != vertex ? 6 : 5;
	for (i = 0; i < n; i++, sp += d) {
		if (n == 6 && (i == 0 || i == 5))
			sp->s_flg |= CFLAG << r;
		else
			sp->s_flg |= mask;
E 2
I 2
	sprintf(str, "%x/%d", cbp->c_combo.s, cbp->c_nframes);
	str += strlen(str);
	for (; tcbp = cbp->c_link[1]; cbp = cbp->c_link[0]) {
		sprintf(str, " %s%c%x", stoc(tcbp->c_vertex), pdir[tcbp->c_dir],
			cbp->c_flg);
		str += strlen(str);
E 2
	}
I 2
	sprintf(str, " %s%c", stoc(cbp->c_vertex), pdir[cbp->c_dir]);
E 2
}

D 2
clearcombo(cbp, color, vertex)
E 2
I 2
#ifdef DEBUG
markcombo(ocbp)
	struct combostr *ocbp;
{
	struct combostr *cbp, *tcbp, **cbpp;
	struct elist *ep, *nep, **epp;
	struct spotstr *sp;
	int s, d, m, i;
	int nframes;
	int r, n, flg, cmask, omask;

	/* should never happen but check anyway */
	if ((nframes = ocbp->c_nframes) >= MAXDEPTH)
		return;

	/*
	 * The lower level combo can be pointed to by more than one
	 * higher level 'struct combostr' so we can't modify the
	 * lower level. Therefore, higher level combos store the
	 * real mask of the lower level frame in c_emask[0] and the
	 * frame number in c_frameindex.
	 *
	 * First we traverse the tree from top to bottom and save the
	 * connection info. Then we traverse the tree from bottom to
	 * top overwriting lower levels with the newer emask information.
	 */
	ep = &einfo[nframes];
	cbpp = &ecombo[nframes];
	for (cbp = ocbp; tcbp = cbp->c_link[1]; cbp = cbp->c_link[0]) {
		ep--;
		ep->e_combo = cbp;
		*--cbpp = cbp->c_link[1];
		ep->e_off = cbp->c_voff[1];
		ep->e_frameindex = cbp->c_frameindex;
		ep->e_fval.s = cbp->c_linkv[1].s;
		ep->e_framecnt = cbp->c_framecnt[1];
		ep->e_emask = cbp->c_emask[1];
	}
	cbp = ep->e_combo;
	ep--;
	ep->e_combo = cbp;
	*--cbpp = cbp->c_link[0];
	ep->e_off = cbp->c_voff[0];
	ep->e_frameindex = 0;
	ep->e_fval.s = cbp->c_linkv[0].s;
	ep->e_framecnt = cbp->c_framecnt[0];
	ep->e_emask = cbp->c_emask[0];

	/* now update the emask info */
	s = 0;
	for (i = 2, ep += 2; i < nframes; i++, ep++) {
		cbp = ep->e_combo;
		nep = &einfo[ep->e_frameindex];
		nep->e_framecnt = cbp->c_framecnt[0];
		nep->e_emask = cbp->c_emask[0];

		if (cbp->c_flg & C_LOOP) {
			s++;
			/*
			 * Account for the fact that this frame connects
			 * to a previous one (thus forming a loop).
			 */
			nep = &einfo[cbp->c_dir];
			if (--nep->e_framecnt)
				nep->e_emask &= ~(1 << cbp->c_voff[0]);
			else
				nep->e_emask = 0;
		}
	}

	/*
	 * We only need to update the emask values of "complete" loops
	 * to include the intersection spots.
	 */
	if (s && ocbp->c_combo.c.a == 2) {
		/* process loops from the top down */
		ep = &einfo[nframes];
		do {
			ep--;
			cbp = ep->e_combo;
			if (!(cbp->c_flg & C_LOOP))
				continue;

			/*
			 * Update the emask values to include the
			 * intersection spots.
			 */
			nep = &einfo[cbp->c_dir];
			nep->e_framecnt = 1;
			nep->e_emask = 1 << cbp->c_voff[0];
			ep->e_framecnt = 1;
			ep->e_emask = 1 << ep->e_off;
			ep = &einfo[ep->e_frameindex];
			do {
				ep->e_framecnt = 1;
				ep->e_emask = 1 << ep->e_off;
				ep = &einfo[ep->e_frameindex];
			} while (ep > nep);
		} while (ep != einfo);
	}

	/* mark all the frames with the completion spots */
	for (i = 0, ep = einfo, cbpp = ecombo; i < nframes; i++, ep++, cbpp++) {
		m = ep->e_emask;
		cbp = *cbpp;
		sp = &board[cbp->c_vertex];
		d = dd[s = cbp->c_dir];
		cmask = CFLAG << s;
		omask = (IFLAG | CFLAG) << s;
		s = ep->e_fval.c.b ? 6 : 5;
		for (; --s >= 0; sp += d, m >>= 1)
			sp->s_flg |= (m & 1) ? omask : cmask;
	}
}

clearcombo(cbp, open)
E 2
	struct combostr *cbp;
D 2
	int color;
	int vertex;
E 2
I 2
	int open;
E 2
{
	register struct spotstr *sp;
	struct combostr *tcbp;
D 2
	int i, d, r, n, mask;
E 2
I 2
	int d, n, mask;
E 2

D 2
	for (; tcbp = cbp->c_link[1]; cbp = cbp->c_link[0])
		clearcombo(tcbp, color, vertex = cbp->c_vertex);
E 2
I 2
	for (; tcbp = cbp->c_link[1]; cbp = cbp->c_link[0]) {
		clearcombo(tcbp, cbp->c_flg & C_OPEN_1);
		open = cbp->c_flg & C_OPEN_0;
	}
E 2
	sp = &board[cbp->c_vertex];
D 2
	d = dd[r = cbp->c_dir];
	mask = ~((IFLAG | CFLAG) << r);
	n = sp->s_fval[color][r].c.b && cbp->c_vertex != vertex ? 6 : 5;
	for (i = 0; i < n; i++, sp += d)
E 2
I 2
	d = dd[n = cbp->c_dir];
	mask = ~((IFLAG | CFLAG) << n);
	n = open ? 6 : 5;
	for (; --n >= 0; sp += d)
E 2
		sp->s_flg &= mask;
I 2
}

list_eq(scbpp, cbpp, n)
	struct combostr **scbpp;
	struct combostr **cbpp;
	int n;
{
	struct combostr **spp, **cpp;

	spp = scbpp + n;
	cpp = cbpp + n;
	do {
		if (*--spp != *--cpp)
			return (0);
	} while (cpp != cbpp);
	/* we found a match */
	return (1);
E 2
}
#endif /* DEBUG */
E 1
