h52604
s 00015/00000/00115
d D 4.3 94/05/30 15:55:38 bostic 3 2
c add a realloc() call, for the C library
e
s 00003/00001/00112
d D 4.2 83/08/11 20:18:40 sam 2 1
c standardize sccs keyword lines
e
s 00113/00000/00000
d D 4.1 82/05/07 19:36:24 mckusick 1 0
c date and time created 82/05/07 19:36:24 by mckusick
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
#ifndef lint
static char sccsid[] = "%W% %G%";
#endif
E 2

#
/*
 *	UNIX shell
 *
 *	S. R. Bourne
 *	Bell Telephone Laboratories
 *
 */

#include	"defs.h"


/*
 *	storage allocator
 *	(circular first fit strategy)
 */

#define BUSY 01
#define busy(x)	(Rcheat((x)->word)&BUSY)

POS		brkincr=BRKINCR;
BLKPTR		blokp;			/*current search pointer*/
BLKPTR		bloktop=BLK(end);	/*top of arena (last blok)*/



ADDRESS	alloc(nbytes)
	POS		nbytes;
{
	REG POS		rbytes = round(nbytes+BYTESPERWORD,BYTESPERWORD);

	LOOP	INT		c=0;
		REG BLKPTR	p = blokp;
		REG BLKPTR	q;
		REP	IF !busy(p)
			THEN	WHILE !busy(q = p->word) DO p->word = q->word OD
				IF ADR(q)-ADR(p) >= rbytes
				THEN	blokp = BLK(ADR(p)+rbytes);
					IF q > blokp
					THEN	blokp->word = p->word;
					FI
					p->word=BLK(Rcheat(blokp)|BUSY);
					return(ADR(p+1));
				FI
			FI
			q = p; p = BLK(Rcheat(p->word)&~BUSY);
		PER	p>q ORF (c++)==0 DONE
		addblok(rbytes);
	POOL
}

VOID	addblok(reqd)
	POS		reqd;
{
	IF stakbas!=staktop
	THEN	REG STKPTR	rndstak;
		REG BLKPTR	blokstak;

		pushstak(0);
		rndstak=round(staktop,BYTESPERWORD);
		blokstak=BLK(stakbas)-1;
		blokstak->word=stakbsy; stakbsy=blokstak;
		bloktop->word=BLK(Rcheat(rndstak)|BUSY);
		bloktop=BLK(rndstak);
	FI
	reqd += brkincr; reqd &= ~(brkincr-1);
	blokp=bloktop;
	bloktop=bloktop->word=BLK(Rcheat(bloktop)+reqd);
	bloktop->word=BLK(ADR(end)+1);
	BEGIN
	   REG STKPTR stakadr=STK(bloktop+2);
	   staktop=movstr(stakbot,stakadr);
	   stakbas=stakbot=stakadr;
	END
}

VOID	free(ap)
	BLKPTR		ap;
{
	REG BLKPTR	p;

	IF (p=ap) ANDF p<bloktop
	THEN	Lcheat((--p)->word) &= ~BUSY;
	FI
}

#ifdef DEBUG
chkbptr(ptr)
	BLKPTR	ptr;
{
	INT		exf=0;
	REG BLKPTR	p = end;
	REG BLKPTR	q;
	INT		us=0, un=0;

	LOOP
	   q = Rcheat(p->word)&~BUSY;
	   IF p==ptr THEN exf++ FI
	   IF q<end ORF q>bloktop THEN abort(3) FI
	   IF p==bloktop THEN break FI
	   IF busy(p)
	   THEN us += q-p;
	   ELSE un += q-p;
	   FI
	   IF p>=q THEN abort(4) FI
	   p=q;
	POOL
	IF exf==0 THEN abort(1) FI
	prn(un); prc(SP); prn(us); prc(NL);
}
#endif
I 3

void *
realloc(cp, nbytes)
	void *cp;
	unsigned int nbytes;
{
	void *new;

	new = malloc(nbytes);
	if (cp == 0)
		return (new);
	bcopy(cp, new, nbytes);
	free(cp);
	return (new);
}
E 3
E 1
