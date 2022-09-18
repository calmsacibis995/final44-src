h21444
s 00008/00066/00853
d D 2.4 93/07/27 09:15:39 bostic 5 4
c checkpoint; Mike Karels left this checked out.
e
s 00001/00001/00918
d D 2.3 86/11/27 16:42:45 jaap 4 3
c Fixed casepm (thanks to bwk)
e
s 00012/00000/00907
d D 2.2 85/08/14 14:58:04 jaap 3 2
c fixed again an old bug (page 1 will be 0 if first line .tl '''' etc.)
e
s 00241/00211/00666
d D 2.1 85/07/18 14:22:30 jaap 2 1
c Edition 8 Version of troff (May 1985), (Dennis did the caching). 
c Local hacks from jaap.
e
s 00877/00000/00000
d D 1.1 85/07/17 17:54:22 jaap 1 0
c date and time created 85/07/17 17:54:22 by jaap
e
u
U
t
T
I 1
#ifndef lint
D 5
static char sccsid[] = "%W% (CWI) %E%";
E 5
I 5
/*
static char sccsid[] = "@(#)n3.c	2.3 (CWI) 86/11/27";
*/
static char sccsid[] = "%W% (Berkeley) %G%";
E 5
#endif lint
I 2
/*      @(#)n3.c	1.1     */
/*
 * troff3.c
 * 
 * macro and string routines, storage allocation
 */
E 2

I 2

E 2
#include "tdef.h"
D 2
extern
#include "d.h"
extern
#include "v.h"
E 2
#ifdef NROFF
D 2
extern
E 2
#include "tw.h"
#endif
D 2
#include "s.h"

/*
troff3.c

macro and string routines, storage allocation
*/

E 2
#include <sgtty.h>
#include "ext.h"
D 2
#define	blisti(i)	(((i)-NEV*EVS)/BLK)
E 2
I 2

#define	MHASH(x)	((x>>6)^x)&0177
struct	contab *mhash[128];	/* 128 == the 0177 on line above */
#define	blisti(i)	(((i)-NEV*(int)sizeof(env))/BLK)
E 2
filep	blist[NBLIST];
tchar	*argtop;
int	pagech = '%';
int	strflg;
D 2
extern struct contab {
	int	rq;
	union {
		int	(*f)();
		unsigned	mx;
	} x;
} contab[NM];
E 2

D 5
#ifdef	INCORE
E 5
	tchar *wbuf;
D 2
	tchar *rbuf;
	tchar corebuf[NBLIST*BLK];
E 2
I 2
	tchar corebuf[NEV*sizeof(env)/sizeof(tchar) + NBLIST*BLK+ 1];
E 2
D 5
#else
	tchar wbuf[BLK];
	tchar rbuf[BLK];
#endif
E 5

caseig()
{
	register i;

	offset = 0;
	if ((i = copyb()) != '.')
		control(i, 1);
}


casern()
{
	register i, j;

	lgf++;
	skip();
	if ((i = getrq()) == 0 || (oldmn = findmn(i)) < 0)
		return;
	skip();
	clrmn(findmn(j = getrq()));
D 2
	if (j)
		contab[oldmn].rq = (contab[oldmn].rq & MMASK) | j;
E 2
I 2
	if (j) {
		munhash(&contab[oldmn]);
		contab[oldmn].rq = j;
		maddhash(&contab[oldmn]);
	}
E 2
}

I 2
maddhash(rp)
register struct contab *rp;
{
	register struct contab **hp;
E 2

I 2
	if (rp->rq == 0)
		return;
	hp = &mhash[MHASH(rp->rq)];
	rp->link = *hp;
	*hp = rp;
}

munhash(mp)
register struct contab *mp;
{	
	register struct contab *p;
	register struct contab **lp;

	if (mp->rq == 0)
		return;
	lp = &mhash[MHASH(mp->rq)];
	p = *lp;
	while (p) {
		if (p == mp) {
			*lp = p->link;
			p->link = 0;
			return;
		}
		lp = &p->link;
		p = p->link;
	}
}

mrehash()
{
	register struct contab *p;
	register i;

	for (i=0; i<128; i++)
		mhash[i] = 0;
	for (p=contab; p < &contab[NM]; p++)
		p->link = 0;
	for (p=contab; p < &contab[NM]; p++) {
		if (p->rq == 0)
			continue;
		i = MHASH(p->rq);
		p->link = mhash[i];
		mhash[i] = p;
	}
}

E 2
caserm()
{
I 2
	int j;

E 2
	lgf++;
D 2
	while (!skip()) {
		clrmn(findmn(getrq()));
	}
E 2
I 2
	while (!skip() && (j = getrq()) != 0)
		clrmn(findmn(j));
	lgf--;
E 2
}


caseas()
{
	app++;
	caseds();
}


caseds()
{
	ds++;
	casede();
}


caseam()
{
	app++;
	casede();
}


casede()
{
	register i, req;
	register filep savoff;
	extern filep finds();

	if (dip != d)
		wbfl();
	req = '.';
	lgf++;
	skip();
	if ((i = getrq()) == 0)
		goto de1;
	if ((offset = finds(i)) == 0)
		goto de1;
	if (ds)
		copys();
	else 
		req = copyb();
	wbfl();
	clrmn(oldmn);
D 2
	if (newmn)
		contab[newmn].rq = i | MMASK;
E 2
I 2
	if (newmn) {
		if (contab[newmn].rq)
			munhash(&contab[newmn]);
		contab[newmn].rq = i;
		maddhash(&contab[newmn]);
	}
E 2
	if (apptr) {
		savoff = offset;
		offset = apptr;
		wbt((tchar) IMP);
		offset = savoff;
	}
	offset = dip->op;
	if (req != '.')
		control(req, 1);
de1:
	ds = app = 0;
	return;
}


findmn(i)
register int	i;
{
D 2
	register j;
E 2
	register struct contab *p;

D 2
	for (p = contab; p < &contab[NM]; p++) {
		if (i == (p->rq & ~MMASK))
			break;
	}
	j = p - contab;
	if (j == NM)
		j = -1;
	return(j);
E 2
I 2
	for (p = mhash[MHASH(i)]; p; p = p->link)
		if (i == p->rq)
			return(p - contab);
	return(-1);
E 2
}


clrmn(i)
register int	i;
{
	if (i >= 0) {
D 2
		if (contab[i].rq & MMASK)
			ffree((filep)contab[i].x.mx);
E 2
I 2
		if (contab[i].mx)
			ffree((filep)contab[i].mx);
		munhash(&contab[i]);
E 2
		contab[i].rq = 0;
D 2
		contab[i].x.mx = 0;
E 2
I 2
		contab[i].mx = 0;
		contab[i].f = 0;
E 2
	}
}


filep finds(mn)
register int	mn;
{
	register i;
	register filep savip;
	extern filep alloc();
	extern filep incoff();

	oldmn = findmn(mn);
	newmn = 0;
	apptr = (filep)0;
D 2
	if (app && oldmn >= 0 && (contab[oldmn].rq & MMASK)) {
E 2
I 2
	if (app && oldmn >= 0 && contab[oldmn].mx) {
E 2
		savip = ip;
D 2
		ip = (filep)contab[oldmn].x.mx;
E 2
I 2
		ip = (filep)contab[oldmn].mx;
E 2
		oldmn = -1;
		while ((i = rbf()) != 0)
			;
		apptr = ip;
		if (!diflg)
			ip = incoff(ip);
		nextb = ip;
		ip = savip;
	} else {
		for (i = 0; i < NM; i++) {
			if (contab[i].rq == 0)
				break;
		}
		if (i == NM || (nextb = alloc()) == 0) {
			app = 0;
			if (macerr++ > 1)
				done2(02);
D 2
			fprintf(stderr, "troff: Too many (%d) string/macro names.\n", NM);
E 2
I 2
			errprint("Too many (%d) string/macro names", NM);
E 2
			edone(04);
			return(offset = 0);
		}
D 2
		contab[i].x.mx = (unsigned) nextb;
E 2
I 2
		contab[i].mx = (unsigned) nextb;
E 2
		if (!diflg) {
			newmn = i;
			if (oldmn == -1)
				contab[i].rq = -1;
		} else {
D 2
			contab[i].rq = mn | MMASK;
E 2
I 2
			contab[i].rq = mn;
			maddhash(&contab[i]);
E 2
		}
	}
	app = 0;
	return(offset = nextb);
}


skip()
{
D 2
	tchar i;
E 2
I 2
	register tchar i;
E 2

	while (cbits(i = getch()) == ' ')
		;
	ch = i;
	return(nlflg);
}


copyb()
{
D 2
	register i, j, k;
	int	req, state;
	tchar ii;
E 2
I 2
	register i, j, state;
	register tchar ii;
	int	req, k;
E 2
	filep savoff;

	if (skip() || !(j = getrq()))
		j = '.';
	req = j;
	k = j >> BYTE;
D 2
	j &= BMASK;
E 2
I 2
	j &= BYTEMASK;
E 2
	copyf++;
	flushi();
	nlflg = 0;
	state = 1;
	while (1) {
		i = cbits(ii = getch());
		if (state == 3) {
			if (i == k)
				break;
			if (!k) {
				ch = ii;
				i = getach();
				ch = ii;
				if (!i)
					break;
			}
			state = 0;
			goto c0;
		}
		if (i == '\n') {
			state = 1;
			nlflg = 0;
			goto c0;
		}
		if (state == 1 && i == '.') {
			state++;
			savoff = offset;
			goto c0;
		}
		if ((state == 2) && (i == j)) {
			state++;
			goto c0;
		}
		state = 0;
c0:
		if (offset)
			wbf(ii);
	}
	if (offset) {
		wbfl();
		offset = savoff;
		wbt((tchar)0);
	}
	copyf--;
	return(req);
}


copys()
{
D 2
	tchar i;
E 2
I 2
	register tchar i;
E 2

	copyf++;
	if (skip())
		goto c0;
	if (cbits(i = getch()) != '"')
		wbf(i);
	while (cbits(i = getch()) != '\n')
		wbf(i);
c0:
	wbt((tchar)0);
	copyf--;
}


filep alloc()
{
	register i;
D 2
	filep j;
E 2
I 2
	register filep j;
E 2

	for (i = 0; i < NBLIST; i++) {
		if (blist[i] == 0)
			break;
	}
	if (i == NBLIST) {
		j = 0;
	} else {
		blist[i] = -1;
D 2
		if ((j = ((filep)i * BLK + NEV * EVS)) < NEV * EVS)
E 2
I 2
		if ((j = ((filep)i * BLK + NEV*(int)sizeof(env))) < NEV*(int)sizeof(env))
E 2
			j = 0;
	}
	return(nextb = j);
}


ffree(i)
filep i;
{
	register j;

D 2
	while ((blist[j = blisti(i)]) != -1) {
		i = ((filep)blist[j]);
E 2
I 2
	while (blist[j = blisti(i)] != (unsigned) ~0) {
		i = (filep) blist[j];
E 2
		blist[j] = 0;
	}
	blist[j] = 0;
}

D 2

E 2
wbt(i)
tchar i;
{
	wbf(i);
	wbfl();
}


wbf(i)
D 2
tchar i;
E 2
I 2
register tchar i;
E 2
{
	register j;

	if (!offset)
		return;
	if (!woff) {
		woff = offset;
D 5
#ifdef INCORE
E 5
		wbuf = &corebuf[woff];	/* INCORE only */
D 5
#endif
E 5
		wbfi = 0;
	}
	wbuf[wbfi++] = i;
	if (!((++offset) & (BLK - 1))) {
		wbfl();
D 2
		if (blist[j = blisti(--offset)] == -1) {
E 2
I 2
		j = blisti(--offset);
		if (j < 0 || j >= NBLIST) {
			errprint("Out of temp file space");
			done2(01);
		}
		if (blist[j] == (unsigned) ~0) {
E 2
			if (alloc() == 0) {
D 2
				fprintf(stderr, "troff: Out of temp file space at %d.\n", v.cd);
E 2
I 2
				errprint("Out of temp file space");
E 2
				done2(01);
			}
			blist[j] = (unsigned)(nextb);
		}
		offset = ((filep)blist[j]);
	}
	if (wbfi >= BLK)
		wbfl();
}


wbfl()
{
	if (woff == 0)
		return;
D 5
#ifndef INCORE
	lseek(ibf, ((long)woff) * sizeof(tchar), 0);
	write(ibf, (char *)wbuf, wbfi * sizeof(tchar));
#endif
E 5
	if ((woff & (~(BLK - 1))) == (roff & (~(BLK - 1))))
		roff = -1;
	woff = 0;
}


tchar rbf()
{
D 2
	tchar i;
E 2
I 2
	register tchar i;
E 2
	register filep j, p;
	extern filep incoff();

I 2
	if (ip == NBLIST*BLK) {		/* for rdtty */
		if (j = rdtty())
			return(j);
		else
			return(popi());
	}
E 2
	/* this is an inline expansion of rbf0: dirty! */
D 2
	if ((j = ip & ~(BLK - 1)) != roff) {
		roff = j;
E 2
D 5
#ifndef INCORE
D 2
		lseek(ibf, (long)roff * sizeof(tchar), 0);
		if (read(ibf, (char *)rbuf, BLK * sizeof(tchar)) == 0)
E 2
I 2
	j = ip & ~(BLK - 1);
	if (j != roff) {
		roff = j;
		lseek(ibf, (long)j * sizeof(tchar), 0);
		if (read(ibf, (char *)rbuf, BLK * sizeof(tchar)) <= 0)
E 2
			i = 0;
		else
			i = rbuf[ip & (BLK-1)];
D 2
#else
		rbuf = &corebuf[roff];
		i = rbuf[ip & (BLK-1)];
#endif
E 2
	} else
		i = rbuf[ip & (BLK-1)];
I 2
#else
E 5
	i = corebuf[ip];
D 5
#endif
E 5
E 2
	/* end of rbf0 */
	if (i == 0) {
		if (!app)
			i = popi();
D 2
	} else {
		/* this is an inline expansion of incoff: also dirty */
		int i;
		p = ip;
		if (!((j = ++p) & (BLK - 1))) {
			if ((i = blist[blisti(--p)]) == -1) {
				fprintf(stderr, "troff: Bad storage allocation.\n");
				done2(-5);
			}
			j = ((filep)i);
E 2
I 2
		return(i);
	}
	/* this is an inline expansion of incoff: also dirty */
	p = ++ip;
	if ((p & (BLK - 1)) == 0) {
		if ((ip = blist[blisti(p-1)]) == (unsigned) ~0) {
			ip = 0;
			errprint("Bad storage allocation");
			done2(-5);
E 2
		}
D 2
		ip = j;
E 2
I 2
		/* this was meant to protect against people removing
		/* the macro they were standing on, but it's too
		/* sensitive to block boundaries.
		/* if (ip == 0) {
		/*	errprint("Block removed while in use");
		/*	done2(-6);
		/* }
		*/
E 2
	}
	return(i);
}


tchar rbf0(p)
register filep p;
{
I 2
D 5
#ifndef INCORE
E 2
	register filep i;

	if ((i = p & ~(BLK - 1)) != roff) {
		roff = i;
D 2
#ifndef INCORE
E 2
		lseek(ibf, (long)roff * sizeof(tchar), 0);
		if (read(ibf, (char *)rbuf, BLK * sizeof(tchar)) == 0)
			return(0);
D 2
#else
		rbuf = &corebuf[roff];
#endif
E 2
	}
	return(rbuf[p & (BLK-1)]);
I 2
#else
E 5
	return(corebuf[p]);
D 5
#endif
E 5
E 2
}


filep incoff(p)
register filep p;
{
D 2
	register i;
	register filep j;

	if (!((j = ++p) & (BLK - 1))) {
		if ((i = blist[blisti(--p)]) == -1) {
			fprintf(stderr, "troff: Bad storage allocation.\n");
E 2
I 2
	p++;
	if ((p & (BLK - 1)) == 0) {
		if ((p = blist[blisti(p-1)]) == (unsigned) ~0) {
			errprint("Bad storage allocation");
E 2
			done2(-5);
		}
D 2
		j = (filep) i;
E 2
	}
D 2
	return(j);
E 2
I 2
	return(p);
E 2
}


tchar popi()
{
	register struct s *p;

	if (frame == stk)
		return(0);
	if (strflg)
		strflg--;
	p = nxf = frame;
	p->nargs = 0;
	frame = p->pframe;
	ip = p->pip;
D 2
	nchar = p->pnchar;
	rchar = p->prchar;
E 2
	pendt = p->ppendt;
D 2
	ap = p->pap;
	cp = p->pcp;
	ch0 = p->pch0;
E 2
I 2
	lastpbp = p->lastpbp;
E 2
	return(p->pch);
}

/*
 *	test that the end of the allocation is above a certain location
 *	in memory
 */
I 5
#ifdef notdef
E 5
#define SPACETEST(base, size) while ((enda - (size)) <= (char *)(base)){setbrk(DELTA);}
I 5
#else
#define SPACETEST(base, size)
#endif
E 5

D 2
pushi(newip)
E 2
I 2
pushi(newip, mname)
E 2
filep newip;
I 2
int mname;
E 2
{
	register struct s *p;
D 2
	extern char	*setbrk();
E 2
I 2
D 5
	extern char *setbrk();
E 5
E 2

	SPACETEST(nxf, sizeof(struct s));
	p = nxf;
	p->pframe = frame;
	p->pip = ip;
D 2
	p->pnchar = nchar;
	p->prchar = rchar;
E 2
	p->ppendt = pendt;
D 2
	p->pap = ap;
	p->pcp = cp;
	p->pch0 = ch0;
E 2
	p->pch = ch;
D 2
	cp = ap = 0;
	nchar = rchar = pendt = ch0 = ch = 0;
E 2
I 2
	p->lastpbp = lastpbp;
	p->mname = mname;
	lastpbp = pbp;
	pendt = ch = 0;
E 2
	frame = nxf;
	if (nxf->nargs == 0) 
		nxf += 1;
	else 
		nxf = (struct s *)argtop;
	return(ip = newip);
}

D 5

char	*setbrk(x)
int	x;
{
	register char	*i;
I 2
	register j;
E 2
	char	*sbrk();

D 2
	if (x % 2 == 1) 
		x++;
	if ((i = sbrk(x)) == MAXPTR) {
		fprintf(stderr, "troff: Core limit reached.\n");
E 2
I 2
	if (j = x % sizeof(int))	/*allocate only whole words for 3B*/
		x += sizeof(int) - j;
	if ((i = sbrk(x)) == (char *) -1) {
		errprint("Core limit reached");
E 2
		edone(0100);
	} else {
I 2
		if ((unsigned)i % sizeof(int)) {	/*check alignment for 3B*/
			errprint("alignment problem");
			edone(0100);
		}
E 2
		enda = i + x;
	}
	return(i);
}


E 5
getsn()
{
	register i;

	if ((i = getach()) == 0)
		return(0);
	if (i == '(')
		return(getrq());
	else 
		return(i);
}


setstr()
{
D 2
	register i;
E 2
I 2
	register i, j;
E 2

	lgf++;
D 2
	if (((i = getsn()) == 0) ||  ((i = findmn(i)) == -1) ||  !(contab[i].rq & MMASK)) {
E 2
I 2
	if ((i = getsn()) == 0 || (j = findmn(i)) == -1 || !contab[j].mx) {
E 2
		lgf--;
		return(0);
	} else {
		SPACETEST(nxf, sizeof(struct s));
		nxf->nargs = 0;
		strflg++;
		lgf--;
D 2
		return(pushi(((filep)contab[i].x.mx)));
E 2
I 2
		return pushi((filep)contab[j].mx, i);
E 2
	}
}



collect()
{
	register j;
D 2
	tchar i;
E 2
I 2
	register tchar i;
E 2
	register tchar *strp;
	tchar * lim;
	tchar * *argpp, **argppend;
	int	quote;
	struct s *savnxf;

	copyf++;
	nxf->nargs = 0;
	savnxf = nxf;
	if (skip())
		goto rtn;

	{
		char *memp;
		memp = (char *)savnxf;
		/*
		 *	1 s structure for the macro descriptor
		 *	APERMAC tchar *'s for pointers into the strings
		 *	space for the tchar's themselves
		 */
		memp += sizeof(struct s);
		/*
		 *	CPERMAC (the total # of characters for ALL arguments)
		 *	to a macros, has been carefully chosen
		 *	so that the distance between stack frames is < DELTA 
		 */
#define	CPERMAC	200
#define	APERMAC	9
		memp += APERMAC * sizeof(tchar *);
		memp += CPERMAC * sizeof(tchar);
		nxf = (struct s*)memp;
	}
	lim = (tchar *)nxf;
	argpp = (tchar **)(savnxf + 1);
	argppend = &argpp[APERMAC];
	SPACETEST(argppend, sizeof(tchar *));
	strp = (tchar *)argppend;
	/*
	 *	Zero out all the string pointers before filling them in.
	 */
	for (j = 0; j < APERMAC; j++){
		argpp[j] = (tchar *)0;
	}
#if 0
D 2
	fprintf(stderr, "savnxf=0x%x,nxf=0x%x,argpp=0x%x,strp=argppend=0x%x,lim=0x%x,enda=0x%x\n",
E 2
I 2
	errprint("savnxf=0x%x,nxf=0x%x,argpp=0x%x,strp=argppend=0x%x,lim=0x%x,enda=0x%x",
E 2
		savnxf, nxf, argpp, strp, lim, enda);
#endif 0
	strflg = 0;
	while ((argpp != argppend) && (!skip())) {
		*argpp++ = strp;
		quote = 0;
		if (cbits(i = getch()) == '"')
			quote++;
		else 
			ch = i;
		while (1) {
			i = getch();
D 2
			if ( nlflg ||  (!quote && cbits(i) == ' '))
E 2
I 2
			if (nlflg || (!quote && cbits(i) == ' '))
E 2
				break;
			if (   quote
			    && (cbits(i) == '"')
			    && (cbits(i = getch()) != '"')) {
				ch = i;
				break;
			}
			*strp++ = i;
D 2
			if (strflg && (strp >= lim)) {
E 2
I 2
			if (strflg && strp >= lim) {
E 2
D 5
#if 0
D 2
				fprintf(stderr, "strp=0x%x, lim = 0x%x\n",
E 2
I 2
				errprint("strp=0x%x, lim = 0x%x",
E 2
					strp, lim);
#endif 0
E 5
D 2
				fprintf(stderr,
					"troff: Macro argument too long.\n");
E 2
I 2
				errprint("Macro argument too long");
E 2
				copyf--;
				edone(004);
			}
			SPACETEST(strp, 3 * sizeof(tchar));
		}
		*strp++ = 0;
	}
	nxf = savnxf;
	nxf->nargs = argpp - (tchar **)(savnxf + 1);
	argtop = strp;
rtn:
	copyf--;
}


seta()
{
	register i;

	i = cbits(getch()) - '0';
D 2
	if (   (i > 0)
	    && (i <= APERMAC)
	    && (i <= frame->nargs)){
		ap = *(((tchar **)(frame + 1)) + i - 1);
	}
E 2
I 2
	if (i > 0 && i <= APERMAC && i <= frame->nargs)
		pushback(*(((tchar **)(frame + 1)) + i - 1));
E 2
}


caseda()
{
	app++;
	casedi();
}


casedi()
{
	register i, j;
	register *k;

	lgf++;
D 2
	if (skip() || ((i = getrq()) == 0)) {
E 2
I 2
	if (skip() || (i = getrq()) == 0) {
E 2
		if (dip != d)
			wbt((tchar)0);
		if (dilev > 0) {
D 2
			v.dn = dip->dnl;
			v.dl = dip->maxl;
E 2
I 2
			numtab[DN].val = dip->dnl;
			numtab[DL].val = dip->maxl;
E 2
			dip = &d[--dilev];
			offset = dip->op;
		}
		goto rtn;
	}
	if (++dilev == NDI) {
		--dilev;
D 2
		fprintf(stderr, "troff: Diversions nested too deep.\n");
E 2
I 2
		errprint("Diversions nested too deep");
E 2
		edone(02);
	}
	if (dip != d)
		wbt((tchar)0);
	diflg++;
	dip = &d[dilev];
	dip->op = finds(i);
	dip->curd = i;
	clrmn(oldmn);
	k = (int *) & dip->dnl;
	for (j = 0; j < 10; j++)
		k[j] = 0;	/*not op and curd*/
rtn:
	app = 0;
	diflg = 0;
}


casedt()
{
	lgf++;
	dip->dimac = dip->ditrap = dip->ditf = 0;
	skip();
	dip->ditrap = vnumb((int *)0);
	if (nonumb)
		return;
	skip();
	dip->dimac = getrq();
}


casetl()
{
	register j;
D 2
	int	w1, w2, w3;
E 2
I 2
	int w[3];
	tchar buf[LNSIZE];
	register tchar *tp;
E 2
	tchar i, delim;
D 2
	filep begin;
	extern width(), pchar();
E 2

I 3
	/*
	 * bug fix
	 *
	 * if .tl is the first thing in the file, the p1
	 * doesn't come out, also the pagenumber will be 0
	 *
	 * tends too confuse the device filter (and the user as well)
	 */
	if( dip == d && numtab[NL].val == -1)
		newline(1);

	/* end fix */
E 3
D 2
					/* bug fix jna
					 * if v.nl isn't 0 and tl is the
					 * first text to be output, you lose
					 * the first page. In older n/troff
					 * the -o1 option fails.
					 *
					 * Could in ditroff repaired by
					 * initializing v.nl to zero,
					 * but this is more subtle, and
					 * src compatible with its predecessor
					 */
	if ((dip == d) && (v.nl == -1))
		newline(1); 
					/* End of fix */
E 2
	dip->nls = 0;
	skip();
D 2
	if (dip != d)
		wbfl();
	if ((offset = begin = alloc()) == 0)
		return;
E 2
	if (ismot(delim = getch())) {
		ch = delim;
		delim = '\'';
	} else 
		delim = cbits(delim);
D 2
	if (!nlflg)
		while (cbits(i = getch()) != '\n') {
			if (cbits(i) == cbits(delim))
				i = IMP;
			wbf(i);
E 2
I 2
	tp = buf;
	numtab[HP].val = 0;
	w[0] = w[1] = w[2] = 0;
	j = 0;
	while (cbits(i = getch()) != '\n') {
		if (cbits(i) == cbits(delim)) {
			if (j < 3)
				w[j] = numtab[HP].val;
			numtab[HP].val = 0;
			j++;
			*tp++ = 0;
		} else {
			if (cbits(i) == pagech) {
				setn1(numtab[PN].val, numtab[findr('%')].fmt,
				      i&SFMASK);
				continue;
			}
			numtab[HP].val += width(i);
			if (tp < &buf[LNSIZE-10])
				*tp++ = i;
E 2
		}
D 2
	wbf((tchar)IMP);
	wbf((tchar)IMP);
	wbt((tchar)0);

	w1 = hseg(width, begin);
	w2 = hseg(width, (filep)0);
	w3 = hseg(width, (filep)0);
	offset = dip->op;
E 2
I 2
	}
	if (j<3)
		w[j] = numtab[HP].val;
	*tp++ = 0;
	*tp++ = 0;
	*tp++ = 0;
	tp = buf;
E 2
#ifdef NROFF
D 2
	if (!offset)
		horiz(po);
E 2
I 2
	horiz(po);
E 2
#endif
D 2
	hseg(pchar, begin);
	if (w2 || w3)
		horiz(j = quant((lt - w2) / 2 - w1, HOR));
	hseg(pchar, (filep)0);
	if (w3) {
		horiz(lt - w1 - w2 - w3 - j);
		hseg(pchar, (filep)0);
E 2
I 2
	while (i = *tp++)
		pchar(i);
	if (w[1] || w[2])
		horiz(j = quant((lt - w[1]) / 2 - w[0], HOR));
	while (i = *tp++)
		pchar(i);
	if (w[2]) {
		horiz(lt - w[0] - w[1] - w[2] - j);
		while (i = *tp++)
			pchar(i);
E 2
	}
	newline(0);
	if (dip != d) {
		if (dip->dnl > dip->hnl)
			dip->hnl = dip->dnl;
	} else {
D 2
		if (v.nl > dip->hnl)
			dip->hnl = v.nl;
E 2
I 2
		if (numtab[NL].val > dip->hnl)
			dip->hnl = numtab[NL].val;
E 2
	}
D 2
	ffree(begin);
E 2
}


casepc()
{
	pagech = chget(IMP);
}


D 2
hseg(f, p)
int	(*f)();
filep p;
{
	register acc;
	tchar i;
	static filep q;

	acc = 0;
	if (p)
		q = p;
	while (1) {
		i = rbf0(q);
		q = incoff(q);
		if (!i || i == IMP)
			return(acc);
		if (cbits(i) == pagech) {
			nrbits = i & SFMASK;
			nform = fmt[findr('%')];
			acc += fnumb(v.pn, f);
		} else 
			acc += (*f)(i);
	}
}


E 2
casepm()
{
	register i, k;
	register char	*p;
	int	xx, cnt, tcnt, kk, tot;
	filep j;
	char	pmline[10];

	kk = cnt = tcnt = 0;
	tot = !skip();
	for (i = 0; i < NM; i++) {
D 2
		if (contab[i].rq)
			tcnt++;
		if (!((xx = contab[i].rq) & MMASK))
E 2
I 2
D 4
		if (!(xx = contab[i].rq))
E 4
I 4
		if ((xx = contab[i].rq) == 0 || contab[i].mx == 0)
E 4
E 2
			continue;
I 2
		tcnt++;
E 2
		p = pmline;
D 2
		j = (filep) contab[i].x.mx;
E 2
I 2
		j = (filep) contab[i].mx;
E 2
		k = 1;
D 2
		while ((j = blist[blisti(j)]) != -1) {
E 2
I 2
		while ((j = blist[blisti(j)]) != (unsigned) ~0) {
E 2
			k++; 
		}
		cnt++;
		kk += k;
		if (!tot) {
			*p++ = xx & 0177;
			if (!(*p++ = (xx >> BYTE) & 0177))
				*(p - 1) = ' ';
			*p++ = 0;
D 2
			fprintf(stderr, "%s %d\n", pmline, k);
E 2
I 2
			fdprintf(stderr, "%s %d\n", pmline, k);
E 2
		}
	}
D 2
	fprintf(stderr, "pm: total %d, macros %d, space %d\n", tcnt, cnt, kk);
E 2
I 2
	fdprintf(stderr, "pm: total %d, macros %d, space %d\n", tcnt, cnt, kk);
E 2
}

D 2

dummy()
E 2
I 2
stackdump()	/* dumps stack of macros in process */
E 2
{
I 2
	struct s *p;

	if (p != stk) {
		for (p = frame; p != stk; p = p->pframe)
			fdprintf(stderr, "%c%c ", p->mname&0177, (p->mname>>BYTE)&0177);
		fdprintf(stderr, "\n");
	}
E 2
}
E 1
