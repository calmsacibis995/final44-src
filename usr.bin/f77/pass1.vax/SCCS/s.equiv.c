h07916
s 00007/00006/00329
d D 5.3 91/04/12 16:08:41 bostic 3 2
c new copyright; att/bsd/shared
e
s 00001/00001/00334
d D 5.2 88/01/03 15:56:50 bostic 2 1
c const is an ANSI C keyword
e
s 00335/00000/00000
d D 5.1 85/06/07 21:29:49 mckusick 1 0
c 4.3BSD beta release version
e
u
U
t
T
I 1
D 3
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
E 3
 */

#ifndef lint
D 3
static char *sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

/*
 * equiv.c
 *
 * Routines related to equivalence class processing, f77 compiler, 4.2 BSD.
 *
 * University of Utah CS Dept modification history:
 * 
 * Revision 3.2  85/01/14  00:14:12  donn
 * Fixed bug in eqvcommon that was causing the calculations of multilevel
 * equivalences to be screwed up.
 * 
 * Revision 3.1  84/10/13  01:16:08  donn
 * Installed Jerry Berkman's version; added UofU comment header.
 * 
 */


#include "defs.h"

#ifdef SDB
#	include <a.out.h>
#	ifndef N_SO
#		include <stab.h>
#	endif
#endif

/* called at end of declarations section to process chains
   created by EQUIVALENCE statements
 */

doequiv()
{
register int i;
int inequiv, comno, ovarno;
ftnint comoffset, offset, leng;
register struct Equivblock *p;
register struct Eqvchain *q;
struct Primblock *itemp;
register Namep np;
expptr offp, suboffset();
int ns, nsubs();
chainp cp;
char *memname();
int doeqverr = 0;

for(i = 0 ; i < nequiv ; ++i)
	{
	p = &eqvclass[i];
	p->eqvbottom = p->eqvtop = 0;
	comno = -1;

	for(q = p->equivs ; q ; q = q->eqvnextp)
		{
		offset = 0;
		itemp = q->eqvitem.eqvlhs;
		if( itemp == NULL ) fatal("error processing equivalence");
		equivdcl = YES;
		vardcl(np = itemp->namep);
		equivdcl = NO;
		if(itemp->argsp || itemp->fcharp)
			{
			if(np->vdim!=NULL && np->vdim->ndim>1 &&
			   nsubs(itemp->argsp)==1 )
				{
				if(! ftn66flag)
					warn("1-dim subscript in EQUIVALENCE");
				cp = NULL;
				ns = np->vdim->ndim;
				while(--ns > 0)
					cp = mkchain( ICON(1), cp);
				itemp->argsp->listp->nextp = cp;
				}

			offp = suboffset(itemp);
			if(ISICON(offp))
D 2
				offset = offp->constblock.const.ci;
E 2
I 2
				offset = offp->constblock.constant.ci;
E 2
			else	{
				dclerr("illegal subscript in equivalence ",
					np);
				np = NULL;
				doeqverr = 1;
				}
			frexpr(offp);
			}
		frexpr(itemp);

		if(np && (leng = iarrlen(np))<0)
			{
			dclerr("argument in equivalence", np);
			np = NULL;
			doeqverr =1;
			}

		if(np) switch(np->vstg)
			{
			case STGUNKNOWN:
			case STGBSS:
			case STGEQUIV:
				break;

			case STGCOMMON:
				comno = np->vardesc.varno;
				comoffset = np->voffset + offset;
				break;

			default:
				dclerr("bad storage class in equivalence", np);
				np = NULL;
				doeqverr = 1;
				break;
			}

		if(np)
			{
			q->eqvoffset = offset;
			p->eqvbottom = lmin(p->eqvbottom, -offset);
			p->eqvtop = lmax(p->eqvtop, leng-offset);
			}
		q->eqvitem.eqvname = np;
		}

	if(comno >= 0)
		eqvcommon(p, comno, comoffset);
	else  for(q = p->equivs ; q ; q = q->eqvnextp)
		{
		if(np = q->eqvitem.eqvname)
			{
			inequiv = NO;
			if(np->vstg==STGEQUIV)
				if( (ovarno = np->vardesc.varno) == i)
					{
					if(np->voffset + q->eqvoffset != 0)
						dclerr("inconsistent equivalence", np);
						doeqverr = 1;
					}
				else	{
					offset = np->voffset;
					inequiv = YES;
					}

			np->vstg = STGEQUIV;
			np->vardesc.varno = i;
			np->voffset = - q->eqvoffset;

			if(inequiv)
				eqveqv(i, ovarno, q->eqvoffset + offset);
			}
		}
	}

if( !doeqverr )
  for(i = 0 ; i < nequiv ; ++i)
	{
	p = & eqvclass[i];
	if(p->eqvbottom!=0 || p->eqvtop!=0)	/* a live chain */
		{
		for(q = p->equivs ; q; q = q->eqvnextp)
			{
			np = q->eqvitem.eqvname;
			np->voffset -= p->eqvbottom;
			if(np->voffset % typealign[np->vtype] != 0)
				dclerr("bad alignment forced by equivalence", np);
			}
		p->eqvtop -= p->eqvbottom;
		p->eqvbottom = 0;
 		}
	freqchain(p);
	}
}





/* put equivalence chain p at common block comno + comoffset */

LOCAL eqvcommon(p, comno, comoffset)
struct Equivblock *p;
int comno;
ftnint comoffset;
{
int ovarno;
ftnint k, offq;
register Namep np;
register struct Eqvchain *q;

if(comoffset + p->eqvbottom < 0)
	{
	errstr("attempt to extend common %s backward",
		nounder(XL, extsymtab[comno].extname) );
	freqchain(p);
	return;
	}

if( (k = comoffset + p->eqvtop) > extsymtab[comno].extleng)
	extsymtab[comno].extleng = k;

#ifdef SDB
if(sdbflag)
	prstab( varstr(XL,extsymtab[comno].extname), N_BCOMM,0,0);
#endif

for(q = p->equivs ; q ; q = q->eqvnextp)
	if(np = q->eqvitem.eqvname)
		{
		switch(np->vstg)
			{
			case STGUNKNOWN:
			case STGBSS:
				np->vstg = STGCOMMON;
				np->vardesc.varno = comno;
				np->voffset = comoffset - q->eqvoffset;
#ifdef SDB
				if(sdbflag)
					{
					namestab(np);
					}
#endif
				break;

			case STGEQUIV:
				ovarno = np->vardesc.varno;
				offq = comoffset - q->eqvoffset - np->voffset;
				np->vstg = STGCOMMON;
				np->vardesc.varno = comno;
				np->voffset = comoffset + q->eqvoffset;
				if(ovarno != (p - eqvclass))
					eqvcommon(&eqvclass[ovarno], comno, offq);
#ifdef SDB
				if(sdbflag)
					{
					namestab(np);
					}
#endif
				break;

			case STGCOMMON:
				if(comno != np->vardesc.varno ||
				   comoffset != np->voffset+q->eqvoffset)
					dclerr("inconsistent common usage", np);
				break;


			default:
				badstg("eqvcommon", np->vstg);
			}
		}

#ifdef SDB
if(sdbflag)
	prstab( varstr(XL,extsymtab[comno].extname), N_ECOMM,0,0);
#endif

freqchain(p);
p->eqvbottom = p->eqvtop = 0;
}


/* put all items on ovarno chain on front of nvarno chain
 * adjust offsets of ovarno elements and top and bottom of nvarno chain
 */

LOCAL eqveqv(nvarno, ovarno, delta)
int ovarno, nvarno;
ftnint delta;
{
register struct Equivblock *p0, *p;
register Namep np;
struct Eqvchain *q, *q1;

p0 = eqvclass + nvarno;
p = eqvclass + ovarno;
p0->eqvbottom = lmin(p0->eqvbottom, p->eqvbottom - delta);
p0->eqvtop = lmax(p0->eqvtop, p->eqvtop - delta);
p->eqvbottom = p->eqvtop = 0;

for(q = p->equivs ; q ; q = q1)
	{
	q1 = q->eqvnextp;
	if( (np = q->eqvitem.eqvname) && np->vardesc.varno==ovarno)
		{
		q->eqvnextp = p0->equivs;
		p0->equivs = q;
		q->eqvoffset -= delta;
		np->vardesc.varno = nvarno;
		np->voffset -= delta;
		}
	else	free( (charptr) q);
	}
p->equivs = NULL;
}




LOCAL freqchain(p)
register struct Equivblock *p;
{
register struct Eqvchain *q, *oq;

for(q = p->equivs ; q ; q = oq)
	{
	oq = q->eqvnextp;
	free( (charptr) q);
	}
p->equivs = NULL;
}





LOCAL nsubs(p)
register struct Listblock *p;
{
register int n;
register chainp q;

n = 0;
if(p)
	for(q = p->listp ; q ; q = q->nextp)
		++n;

return(n);
}
E 1
