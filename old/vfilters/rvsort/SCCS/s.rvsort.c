h28545
s 00000/00005/00485
d D 5.5 91/03/02 15:10:01 bostic 7 6
c ANSI
e
s 00001/00011/00489
d D 5.4 90/06/01 18:46:58 bostic 6 5
c new copyright notice
e
s 00010/00005/00490
d D 5.3 88/06/30 17:53:20 bostic 5 4
c install approved copyright notice
e
s 00015/00003/00480
d D 5.2 88/03/08 08:30:06 bostic 4 3
c add Berkeley specific header
e
s 00007/00001/00476
d D 5.1 85/05/15 11:32:49 dist 3 2
c Add copyright notice
e
s 00004/00001/00473
d D 4.2 83/07/16 23:48:08 sam 2 1
c add useful sccs id's
e
s 00474/00000/00000
d D 4.1 80/11/30 15:56:14 root 1 0
c date and time created 80/11/30 15:56:14 by root
e
u
U
t
T
I 3
/*
 * Copyright (c) 1983 Regents of the University of California.
D 4
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * All rights reserved.
 *
D 6
 * Redistribution and use in source and binary forms are permitted
D 5
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 5
I 5
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 5
E 4
 */

E 3
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
#ifndef lint
I 4
char copyright[] =
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
E 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif
E 3
I 3
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4
E 3

E 2
/*
 * Sort troff output for versatec to reduce amount of reverse leading
 */ 

# include <stdio.h>

#define NULL 0

double atof();
char *calloc();

FILE *in,*out;

struct achar *piles[500], *afreel;

int skipfirst = 1;	/* skip the first leading so start at top of page */
int cpsize = 02;	/*  Funny sizes  */
struct point_sizes {
	int stupid_code;
	int real_code;
} point_sizes[] = {
	010, 6,
	0, 7,
	01, 8,
	07, 9,
	02, 10,
	03, 11,
	04, 12,
	05, 14,
	0211, 16,
	06, 18,
	0212, 20,
	0213, 22,
	0214, 24,
	0215, 28,
	0216, 36,
	0, 0
};

int	pagelength = 144 * 11;	/* in Leading units */
int	pagemod;		/* horizontal page number (for versatec) */
#define	MODOFF 3672		/* 432 * 8.5 */

int	esc, lead, back, verd, mcase, railmag;
int	col, row;

int	oback, omcase, orailmag, ocol, orow, overd;
int	opsize = 02;

struct	achar
{
	char	code;
	char	psize;
	short	col;
	short	row;
	char	railmag;
	char	verd;
	char	back;
	char	mcase;
	struct	achar *next;
};

main(argc, argv) 
	int argc;
	char *argv[];
{
	register i;

	for(i = 3; i < 15; i++)
		close(i);
	while (argc > 1 && argv[1][0] == '-') {
		switch (argv[1][1]) {
			case 'l': {
				float f = 144 * atof(argv[1] + 2);
				if (f < 144) {
					error("bad length");
					exit(1);
				}
				pagelength = f;
				break;
			}
		}
		argc--; argv++;
	}
	out = stdout;
	if(argc > 1) {
		while(--argc) {
			argv++;
			if((in=fopen(argv[0], "r")) == NULL)
				perror("vsort");
			else {
				ofile();
				fclose(in);
			}
		}
	} else {
		in = stdin;
		ofile();
	}
	exit(0);
}

ofile()
{
	register int c;
	static int initialized;

	while((c = getch()) != -1) {
		if(!c)
			continue;
		if(c & 0200) {		/* escape (left/right) */
			esc += (~c) & 0177;
			continue;
		}
		if(esc) {
			if(back)
				esc = -esc;
			col += esc;
			esc = 0;
		}
		if((c & 0377) < 0100)	/*  Purely for efficiency  */
			goto normal_char;
		switch(c) {

		case 0100:
			if(initialized++) {
				linesflush();
				return;
			}
			row = 0;
			col = 0;	esc = 0;
			lead = 0;
			verd = 0;	back = 0;	mcase = 0;
			railmag = 0;
			ocol = 0;
			orow = 0;
			oback = 0;	omcase = 0;
			orailmag = 0;
			if(loadfont(railmag, cpsize) < 0)
				error("init");
			putc(0100, out);
			break;

		case 0101:	/* lower rail */
			crail(railmag &= ~01);
			break;

		case 0102:	/* upper rail */
			crail(railmag |= 01);
			break;

		case 0103:	/* upper mag */
			crail(railmag |= 02);
			break;

		case 0104:	/* lower mag */
			crail(railmag &= ~02);
			break;

		case 0105:	/* lower case */
			mcase = 0;
			break;

		case 0106:	/* upper case */
			mcase = 1;
			break;

		case 0107:	/* escape forward */
			back = 0;
			break;

		case 0110:	/* escape backwards */
			back = 1;
			break;

		case 0111:	/* stop */
			break;

		case 0112:	/* lead forward */
			verd = 0;
			break;

		case 0113:	/* undefined */
			break;

		case 0114:	/* lead backward */
			verd = 1;
			break;

		case 0115:	/* undefined */
		case 0116:
		case 0117:
			break;

		default:
			if((c & 0340) == 0140) {/* leading */
				lead = (~c) & 037;
				if(verd)
					lead = -lead;
				if (skipfirst > 0) {
					skipfirst--;
					continue;
				}
				row += lead;
				if (row >= pagelength)
					allflush();
				continue;
			}
			if((c & 0360)== 0120) {	/* size change */
				col += stupidadj(c & 017, cpsize);
				loadfont(railmag, c & 017);
				continue;
			}
			if(c & 0300)
				continue;
		normal_char:
			c = (c & 077);
			stuffc(c);
		}
	}
	linesflush();
	putc(0111, out);
	putc(0111, out);
	putc(0111, out);
	putc(0111, out);
	putc(0111, out);
	putc(0111, out);
	putc(0111, out);
	putc(0111, out);
}

int	peekc;

getch()
{
	register c;

	if(peekc) {
		c = peekc;
		peekc = 0;
		return(c);
	}
	return(getc(in));
}

D 7
ungetc(c)
{
	peekc = c;
}

E 7
error(s)
	char *s;
{

	fflush(out);
	fprintf(stderr, "vsort: %s\n", s);
}

crail(nrail)
	int nrail;
{

	railmag = nrail;
	loadfont(nrail, cpsize);
}

loadfont(fnum, size)
	int fnum;
	int size;
{

	cpsize = size;
	return(0);
}

stuffc(code)
	register int code;
{
	register struct achar *ap, **bp;

	if (col < 0 || col >= 500*8)
		return;
	if (afreel) {
		ap = afreel;
		afreel = ap->next;
	} else
		ap = (struct achar *)malloc(sizeof (*ap));
	ap->row = row;
	ap->col = col;
	ap->psize = cpsize;
	ap->verd = verd;
	ap->back = back;
	ap->mcase = mcase;
	ap->code = code;
	ap->railmag = railmag;
	bp = &piles[col / 8];
	ap->next = *bp;
	*bp = ap;
}

allflush()
{

	linesflush();
	if (row > orow)
		ptlead(row - orow);
	row -= pagelength;
	orow = row;
}


linesflush()
{
	register struct achar **ap, *bp, *cp;
	static notfirst;

	if (notfirst)
		putc(0115, out);
	orow = 0;
	ocol = 0;
	notfirst = 1;
	for (ap = &piles[0]; ap < &piles[500]; ap++) {
		for (bp = *ap; bp; bp = cp) {
			sendchar(bp);
			cp = bp->next;
			bp->next = afreel;
			afreel = bp;
		}
		*ap = 0;
	}
}

sendchar(cp)
	register struct achar *cp;
{
	register int i;

#ifdef DUMPCHAR
	dumpchar(cp);
#endif
	if(cp->railmag != orailmag)
		ptrail(cp->railmag);
	if(cp->psize != opsize)
		ptsize(cp->psize);
	if(cp->mcase != omcase)
		ptmcase();
	if(cp->row != orow)
		ptlead(cp->row - orow);
	if(cp->col != ocol)
		ptesc(cp->col - ocol);
	if(cp->back != oback)
		ptback();
	putc(cp->code, out);
	orow = cp->row;
	orailmag = cp->railmag;
	opsize = cp->psize;
	omcase = cp->mcase;
	ocol = cp->col;
	oback = cp->back;
}

ptrail(rlmg)
	register int rlmg;
{

	if((rlmg & 01) != (orailmag & 01))
		putc((rlmg & 01) ? 0102:0101, out);	/*  rail  */
	if((rlmg & 02) != (orailmag & 02))
		putc((rlmg & 02) ? 0103:0104, out);	/*  mag  */
}

ptback()
{

	putc(oback ? 0107:0110, out);
	oback = !oback;
}

ptsize(size)
	register int size;
{

	putc(0120 | (size & 017), out);
	ptesc(-stupidadj(size, opsize));
}

stupidadj(code, lcode)
	register int code;
	int lcode;
{
	register struct point_sizes *psp;
	register struct point_sizes *lpsp;

	psp = point_sizes;
	while(psp->real_code != 0) {
		if((psp->stupid_code & 017) == code)
			break;
		psp++;
	}
	lpsp = point_sizes;
	while(lpsp->real_code != 0) {
		if((lpsp->stupid_code & 017) == lcode)
			break;
		lpsp++;
	}
	code = 0;
	if(!(lpsp->stupid_code & 0200) && (psp->stupid_code & 0200))
		code = -55;
	else
		if((lpsp->stupid_code & 0200) && !(psp->stupid_code & 0200))
			code = 55;
	return(code);
}

ptmcase()
{

	putc(omcase ? 0105:0106, out);
}

ptesc(escc)
	register int escc;
{

	if((escc < 0 && !oback ) || (escc >= 0 && oback))
		ptback();
	escc = abs(escc);
	while(escc > 0177) {
		putc(0200, out);
		escc -= 0177;
	}
	if(escc)
		putc(0200 | ((~escc) & 0177), out);
}

ptlead(leadd)
	register int leadd;
{

	if (leadd == 0)
		return;
	if (leadd < 0) {
		if (overd == 0)
			putc(0114, out), overd = 1;
		leadd = -leadd;
	} else {
		if (overd)
			putc(0112, out), overd = 0;
	}
	if (leadd > 64) {
		putc(0116, out);
		putc(leadd / 64, out);
		leadd %= 64;
	}
	while (leadd > 037) {
		putc(0140, out);
		leadd -= 037;
	}
	if (leadd)
		putc(0140 | ((~leadd) & 037), out);
}

#ifdef DUMPLINE
dumpchar(cp)
register struct achar *cp;
{

	fprintf(stderr,
"code %o psize %d col %d row %d railmag %d verd %d back %d mcase %d\n",
	    cp->code, cp->psize, cp->col, cp->row, cp->railmag, cp->verd,
	    cp->back, cp->mcase);
}
#endif
E 1
