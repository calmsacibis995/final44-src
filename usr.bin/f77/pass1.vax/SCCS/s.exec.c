h13714
s 00006/00005/00866
d D 5.7 91/04/12 16:08:42 bostic 7 6
c new copyright; att/bsd/shared
e
s 00008/00008/00863
d D 5.6 88/01/03 15:56:52 bostic 6 5
c const is an ANSI C keyword
e
s 00025/00000/00846
d D 5.5 86/01/07 18:48:51 donn 5 4
c (1) Assignment statements are executable statements -- advance
c the magic parser state to forbid DATA statements and statement functions.
c (2) Complain about calls to things which aren't subroutines.
e
s 00006/00001/00840
d D 5.4 85/08/29 00:32:47 donn 4 3
c Make error message more useful (from Jerry Berkman).
e
s 00001/00001/00840
d D 5.3 85/07/18 18:58:57 mckusick 3 2
c fix spelling
e
s 00000/00004/00841
d D 5.2 85/06/07 22:01:08 mckusick 2 1
c fix copyright
e
s 00845/00000/00000
d D 5.1 85/06/07 21:30:59 mckusick 1 0
c 4.3BSD beta release version
e
u
U
t
T
I 1
D 7
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
E 7
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7

/*
 * exec.c
 *
 * Routines for handling the semantics of control structures.
 * F77 compiler, pass 1.
 *
 * University of Utah CS Dept modification history:
 * 
I 4
 * $Log:	exec.c,v $
I 5
 * Revision 5.6  85/12/20  19:42:46  donn
 * Change style of error reporting in last fix.
 * 
 * Revision 5.5  85/12/20  18:54:10  donn
 * Complain about calls to things which aren't subroutines.
 * 
 * Revision 5.4  85/12/18  19:57:58  donn
 * Assignment statements are executable statements -- advance the magic
 * parser state to forbid DATA statements and statement functions.
 * 
 * Revision 5.3  85/11/25  00:23:49  donn
 * 4.3 beta
 * 
E 5
 * Revision 5.2  85/08/10  04:07:36  donn
 * Changed an error message to correct spelling and be more accurate.
 * From Jerry Berkman.
 * 
E 4
 * Revision 2.3  85/03/18  08:03:31  donn
 * Hacks for conversions from type address to numeric type -- prevent addresses
 * from being stored in shorts and prevent warnings about implicit conversions.
 * 
 * Revision 2.2  84/09/03  23:18:30  donn
 * When a DO loop had the same variable as its loop variable and its limit,
 * the limit temporary was assigned to AFTER the original value of the variable
 * was destroyed by assigning the initial value to the loop variable.  I
 * swapped the operands of a comparison and changed the direction of the
 * operator...  This only affected programs when optimizing.  (This may not
 * be enough if something alters the order of evaluation of side effects
 * later on... sigh.)
 * 
 * Revision 2.1  84/07/19  12:02:53  donn
 * Changed comment headers for UofU.
 * 
 * Revision 1.3  84/07/12  18:35:12  donn
 * Added change to enddo() to detect open 'if' blocks at the ends of loops.
 * 
 * Revision 1.2  84/06/08  11:22:53  donn
 * Fixed bug in exdo() -- if a loop parameter contained an instance of the loop
 * variable and the optimizer was off, the loop variable got converted to
 * register before the parameters were processed and so the loop parameters
 * were initialized from garbage in the register instead of the memory version
 * of the loop variable.
 * 
 */

D 2
#ifndef lint
static	char *sccsid = "%W% (Berkeley) %E%";
#endif

E 2
#include "defs.h"
#include "optim.h"


/*   Logical IF codes
*/


exif(p)
expptr p;
{
register int k;
pushctl(CTLIF);
ctlstack->elselabel = newlabel();

if( ( k = (p = fixtype(p))->headblock.vtype) != TYLOGICAL)
	{
	if(k != TYERROR)
		err("non-logical expression in IF statement");
	frexpr(p);
	}
else if (optimflag)
	optbuff (SKIFN, p, ctlstack->elselabel, 0);
else
	putif (p, ctlstack->elselabel);
}



exelif(p)
expptr p;
{
int k,oldelse;

if( ( k = (p = fixtype(p))->headblock.vtype) != TYLOGICAL)
	{
	if(k != TYERROR)
		err("non-logical expression in IF statement");
	frexpr(p);
	}
else    {
        if(ctlstack->ctltype == CTLIF)
		{
		if(ctlstack->endlabel == 0) ctlstack->endlabel = newlabel();
        	oldelse=ctlstack->elselabel;
		ctlstack->elselabel = newlabel();
		if (optimflag)
			{
			optbuff (SKGOTO, 0, ctlstack->endlabel, 0);
			optbuff (SKLABEL, 0, oldelse, 0);
			optbuff (SKIFN, p, ctlstack->elselabel, 0);
			}
		else
			{
			putgoto (ctlstack->endlabel);
			putlabel (oldelse);
			putif (p, ctlstack->elselabel);
			}
		}
        else	execerr("elseif out of place", CNULL);
        }
}





exelse()
{
if(ctlstack->ctltype==CTLIF)
	{
	if(ctlstack->endlabel == 0)
		ctlstack->endlabel = newlabel();
	ctlstack->ctltype = CTLELSE;
	if (optimflag)
		{
		optbuff (SKGOTO, 0, ctlstack->endlabel, 0);
		optbuff (SKLABEL, 0, ctlstack->elselabel, 0);
		}
	else
		{
		putgoto (ctlstack->endlabel);
		putlabel (ctlstack->elselabel);
		}
	}

else	execerr("else out of place", CNULL);
}


exendif()
{
if (ctlstack->ctltype == CTLIF)
	{
	if (optimflag)
		{
		optbuff (SKLABEL, 0, ctlstack->elselabel, 0);
		if (ctlstack->endlabel)
			optbuff (SKLABEL, 0, ctlstack->endlabel, 0);
		}
	else
		{
		putlabel (ctlstack->elselabel);
		if (ctlstack->endlabel)
			putlabel (ctlstack->endlabel);
		}
	popctl ();
	}
else if (ctlstack->ctltype == CTLELSE)
	{
	if (optimflag)
		optbuff (SKLABEL, 0, ctlstack->endlabel, 0);
	else
		putlabel (ctlstack->endlabel);
	popctl ();
	}
else
	execerr("endif out of place", CNULL);
}



LOCAL pushctl(code)
int code;
{
register int i;

/* fprintf(diagfile,"old blklevel %d \n",blklevel); dmpframe(ctlstack); */
if(++ctlstack >= lastctl)
	many("loops or if-then-elses", 'c');
ctlstack->ctltype = code;
for(i = 0 ; i < 4 ; ++i)
	ctlstack->ctlabels[i] = 0;
++blklevel;
}


LOCAL popctl()
{
if( ctlstack-- < ctls )
	fatal("control stack empty");
--blklevel;
}



LOCAL poplab()
{
register struct Labelblock  *lp;

for(lp = labeltab ; lp < highlabtab ; ++lp)
	if(lp->labdefined)
		{
		/* mark all labels in inner blocks unreachable */
		if(lp->blklevel > blklevel)
			lp->labinacc = YES;
		}
	else if(lp->blklevel > blklevel)
		{
		/* move all labels referred to in inner blocks out a level */
		lp->blklevel = blklevel;
		}
}



/*  BRANCHING CODE
*/

exgoto(lab)
struct Labelblock *lab;
{
if (optimflag)
	optbuff (SKGOTO, 0, lab->labelno, 0);
else
	putgoto (lab->labelno);
}







exequals(lp, rp)
register struct Primblock *lp;
register expptr rp;
{
register Namep np;

if(lp->tag != TPRIM)
	{
	err("assignment to a non-variable");
	frexpr(lp);
	frexpr(rp);
	}
else if(lp->namep->vclass!=CLVAR && lp->argsp)
	{
	if(parstate >= INEXEC)
D 3
		err("assignment to an undimemsioned array");
E 3
I 3
D 4
		err("assignment to an undimensioned array");
E 4
I 4
		err("undimensioned array or statement function out of order");
E 4
E 3
	else
		mkstfunct(lp, rp);
	}
else
	{
	np = (Namep) lp->namep;
	if (np->vclass == CLPROC && np->vprocclass == PTHISPROC
		&& proctype == TYSUBR)
		{
		err("assignment to a subroutine name");
		return;
		}
	if(parstate < INDATA)
		enddcl();
I 5
	parstate = INEXEC;
E 5
	if (optimflag)
		optbuff (SKEQ, mkexpr(OPASSIGN, mklhs(lp), fixtype(rp)), 0, 0);
	else
		puteq (mklhs(lp), fixtype(rp));
	}
}



mkstfunct(lp, rp)
struct Primblock *lp;
expptr rp;
{
register struct Primblock *p;
register Namep np;
chainp args;

if(parstate < INDATA)
	{
	enddcl();
	parstate = INDATA;
	}

np = lp->namep;
if(np->vclass == CLUNKNOWN)
	np->vclass = CLPROC;
else
	{
	dclerr("redeclaration of statement function", np);
	return;
	}
np->vprocclass = PSTFUNCT;
np->vstg = STGSTFUNCT;
impldcl(np);
args = (lp->argsp ? lp->argsp->listp : CHNULL);
np->varxptr.vstfdesc = mkchain(args , rp );

for( ; args ; args = args->nextp)
	if( args->datap->tag!=TPRIM ||
		(p = (struct Primblock *) (args->datap) )->argsp ||
		p->fcharp || p->lcharp )
		err("non-variable argument in statement function definition");
	else
		{
		args->datap = (tagptr) (p->namep);
		vardcl(p->namep);
		free(p);
		}
}



excall(name, args, nstars, labels)
Namep name;
struct Listblock *args;
int nstars;
struct Labelblock *labels[ ];
{
register expptr p;

I 5
if (name->vdcldone)
	if (name->vclass != CLPROC && name->vclass != CLENTRY)
		{
		dclerr("call to non-subroutine", name);
		return;
		}
	else if (name->vtype != TYSUBR)
		{
		dclerr("subroutine invocation of function", name);
		return;
		}
E 5
settype(name, TYSUBR, ENULL);
p = mkfunct( mkprim(name, args, CHNULL) );
p->exprblock.vtype = p->exprblock.leftp->headblock.vtype = TYINT;
if (nstars > 0)
	if (optimflag)
		optbuff (SKCMGOTO, p, nstars, labels);
	else
		putcmgo (p, nstars, labels);
else
	if (optimflag)
		optbuff (SKCALL, p, 0, 0);
	else
		putexpr (p);
}



exstop(stop, p)
int stop;
register expptr p;
{
char *q;
int n;
expptr mkstrcon();

if(p)
	{
	if( ! ISCONST(p) )
		{
		execerr("pause/stop argument must be constant", CNULL);
		frexpr(p);
		p = mkstrcon(0, CNULL);
		}
	else if( ISINT(p->constblock.vtype) )
		{
D 6
		q = convic(p->constblock.const.ci);
E 6
I 6
		q = convic(p->constblock.constant.ci);
E 6
		n = strlen(q);
		if(n > 0)
			{
D 6
			p->constblock.const.ccp = copyn(n, q);
E 6
I 6
			p->constblock.constant.ccp = copyn(n, q);
E 6
			p->constblock.vtype = TYCHAR;
			p->constblock.vleng = (expptr) ICON(n);
			}
		else
			p = (expptr) mkstrcon(0, CNULL);
		}
	else if(p->constblock.vtype != TYCHAR)
		{
		execerr("pause/stop argument must be integer or string", CNULL);
		p = (expptr) mkstrcon(0, CNULL);
		}
	}
else	p = (expptr) mkstrcon(0, CNULL);

if (optimflag)
	optbuff ((stop ? SKSTOP : SKPAUSE), p, 0, 0);
else
	putexpr (call1(TYSUBR, (stop ? "s_stop" : "s_paus"), p));
}


/* UCB DO LOOP CODE */

#define DOINIT	par[0]
#define DOLIMIT	par[1]
#define DOINCR	par[2]

D 6
#define CONSTINIT  const[0]
#define CONSTLIMIT const[1]
#define CONSTINCR  const[2]
E 6
I 6
#define CONSTINIT  constant[0]
#define CONSTLIMIT constant[1]
#define CONSTINCR  constant[2]
E 6

#define VARSTEP	0
#define POSSTEP	1
#define NEGSTEP	2


exdo(range, spec)
int range;
chainp spec;

{
  register expptr p, q;
  expptr q1;
  register Namep np;
  chainp cp;
  register int i;
  int dotype, incsign;
  Addrp dovarp, dostgp;
  expptr par[3];
D 6
  expptr const[3];
E 6
I 6
  expptr constant[3];
E 6
  Slotp doslot;

  pushctl(CTLDO);
  dorange = ctlstack->dolabel = range;
  np = (Namep) (spec->datap);
  ctlstack->donamep = NULL;
  if(np->vdovar)
    {
      errstr("nested loops with variable %s", varstr(VL,np->varname));
      return;
    }

  dovarp = mkplace(np);
  dotype = dovarp->vtype;

  if( ! ONEOF(dotype, MSKINT|MSKREAL) )
    {
      err("bad type on DO variable");
      return;
    }


  for(i=0 , cp = spec->nextp ; cp!=NULL && i<3 ; cp = cp->nextp)
    {
      p = fixtype((expptr) cpexpr((tagptr) q = cp->datap));
      if(!ONEOF(p->headblock.vtype, MSKINT|MSKREAL) )
	{
	  err("bad type on DO parameter");
	  return;
	}


      if (ISCONST(q))
D 6
	const[i] = mkconv(dotype, q);
E 6
I 6
	constant[i] = mkconv(dotype, q);
E 6
      else
	{
	  frexpr(q);
D 6
	  const[i] = NULL;
E 6
I 6
	  constant[i] = NULL;
E 6
	}

      par[i++] = mkconv(dotype, p);
    }

  frchain(&spec);
  switch(i)
    {
    case 0:
    case 1:
      err("too few DO parameters");
      return;

    case 2:
      DOINCR = (expptr) ICON(1);
      CONSTINCR = ICON(1);

    case 3:
      break;

    default:
      err("too many DO parameters");
      return;
    }

  ctlstack->donamep = np;

  np->vdovar = YES;
  if( !optimflag && enregister(np) )
    {
      /* stgp points to a storage version, varp to a register version */
      dostgp = dovarp;
      dovarp = mkplace(np);
    }
  else
    dostgp = NULL;

  for (i = 0; i < 4; i++)
    ctlstack->ctlabels[i] = newlabel();

  if( CONSTLIMIT )
    ctlstack->domax = DOLIMIT;
  else
    ctlstack->domax = (expptr) mktemp(dotype, PNULL);

  if( CONSTINCR )
    {
      ctlstack->dostep = DOINCR;
      if( (incsign = conssgn(CONSTINCR)) == 0)
	err("zero DO increment");
      ctlstack->dostepsign = (incsign > 0 ? POSSTEP : NEGSTEP);
    }
  else
    {
      ctlstack->dostep = (expptr) mktemp(dotype, PNULL);
      ctlstack->dostepsign = VARSTEP;
    }

if (optimflag)
	doslot = optbuff (SKDOHEAD,0,0,ctlstack);

if( CONSTLIMIT && CONSTINIT && ctlstack->dostepsign!=VARSTEP)
	{
	if (optimflag)
		optbuff (SKEQ,mkexpr(OPASSIGN,cpexpr(dovarp),cpexpr(DOINIT)),
			0,0);
	else
		puteq (cpexpr(dovarp), cpexpr(DOINIT));
	if( ! onetripflag )
		{
		q = mkexpr(OPMINUS, cpexpr(CONSTLIMIT), cpexpr(CONSTINIT));
		if((incsign * conssgn(q)) == -1)
			{
			warn("DO range never executed");
			if (optimflag)
				optbuff (SKGOTO,0,ctlstack->endlabel,0);
			else
				putgoto (ctlstack->endlabel);
			}
		frexpr(q);
		}
	}


else if (ctlstack->dostepsign != VARSTEP && !onetripflag)
	{
	if (CONSTLIMIT)
		q = (expptr) cpexpr(ctlstack->domax);
	else
		q = mkexpr(OPASSIGN, cpexpr(ctlstack->domax), DOLIMIT);
	q1 = mkexpr(OPASSIGN, cpexpr(dovarp), DOINIT);
	q = mkexpr( (ctlstack->dostepsign == POSSTEP ? OPGE : OPLE),
		   q, q1);
	if (optimflag)
		optbuff (SKIFN,q, ctlstack->endlabel,0);
	else
		putif (q, ctlstack->endlabel);
	}
else
	{
	if (!CONSTLIMIT)
	    if (optimflag)
		optbuff (SKEQ,
			mkexpr(OPASSIGN,cpexpr(ctlstack->domax),DOLIMIT),0,0);
	    else
		puteq (cpexpr(ctlstack->domax), DOLIMIT);
	q = DOINIT;
	if (!onetripflag)
		q = mkexpr(OPMINUS, q,
			mkexpr(OPASSIGN, cpexpr(ctlstack->dostep),
			       DOINCR) );
	if (optimflag)
		optbuff (SKEQ,mkexpr(OPASSIGN,cpexpr(dovarp), q),0,0);
	else
		puteq (cpexpr(dovarp), q);
	if (onetripflag && ctlstack->dostepsign == VARSTEP)
	    if (optimflag)
		optbuff (SKEQ,
			mkexpr(OPASSIGN,cpexpr(ctlstack->dostep),DOINCR),0,0);
	    else
		puteq (cpexpr(ctlstack->dostep), DOINCR);
	}

if (ctlstack->dostepsign == VARSTEP)
	{
	expptr incr,test;
	if (onetripflag)
		if (optimflag)
			optbuff (SKGOTO,0,ctlstack->dobodylabel,0);
		else
			putgoto (ctlstack->dobodylabel);
	else
	    if (optimflag)
		optbuff (SKIFN,mkexpr(OPGE, cpexpr(ctlstack->dostep), ICON(0)),
			ctlstack->doneglabel,0);
	    else
		putif (mkexpr(OPGE, cpexpr(ctlstack->dostep), ICON(0)),
			ctlstack->doneglabel);
	if (optimflag)
		optbuff (SKLABEL,0,ctlstack->doposlabel,0);
	else
		putlabel (ctlstack->doposlabel);
	incr = mkexpr(OPPLUSEQ, cpexpr(dovarp), cpexpr(ctlstack->dostep));
	test = mkexpr(OPLE, incr, cpexpr(ctlstack->domax));
	if (optimflag)
		optbuff (SKIFN,test, ctlstack->endlabel,0);
	else
		putif (test, ctlstack->endlabel);
	}

if (optimflag)
	optbuff (SKLABEL,0,ctlstack->dobodylabel,0);
else
	putlabel (ctlstack->dobodylabel);
if (dostgp)
	{
	if (optimflag)
		optbuff (SKEQ,mkexpr(OPASSIGN,dostgp, dovarp),0,0);
	else
		puteq (dostgp, dovarp);
	}
else
	frexpr(dovarp);
if (optimflag)
	doslot->nullslot = optbuff (SKNULL,0,0,0);

frexpr(CONSTINIT);
frexpr(CONSTLIMIT);
frexpr(CONSTINCR);
}


enddo(here)
int here;

{
  register struct Ctlframe *q;
  Namep np;
  Addrp ap, rv;
  expptr t;
  register int i;
  Slotp doslot;

  while (here == dorange)
    {
      while (ctlstack->ctltype == CTLIF || ctlstack->ctltype == CTLELSE)
	{
	  execerr("missing endif", CNULL);
	  exendif();
	}
      
      if (np = ctlstack->donamep)
	{
	rv = mkplace (np);

	t = mkexpr(OPPLUSEQ, cpexpr(rv), cpexpr(ctlstack->dostep) );

	if (optimflag)
		doslot = optbuff (SKENDDO,0,0,ctlstack);

	if (ctlstack->dostepsign == VARSTEP)
		if (optimflag)
			{
			optbuff (SKIFN,
				mkexpr(OPLE, cpexpr(ctlstack->dostep), ICON(0)),
				ctlstack->doposlabel,0);
			optbuff (SKLABEL,0,ctlstack->doneglabel,0);
			optbuff (SKIFN,mkexpr(OPLT, t, ctlstack->domax),
				ctlstack->dobodylabel,0);
			}
		else
			{
			putif (mkexpr(OPLE, cpexpr(ctlstack->dostep), ICON(0)),
				ctlstack->doposlabel);
			putlabel (ctlstack->doneglabel);
			putif (mkexpr(OPLT, t, ctlstack->domax),
				ctlstack->dobodylabel);
			}
	else
		{
		int op;
		op = (ctlstack->dostepsign == POSSTEP ? OPGT : OPLT);
		if (optimflag)
			optbuff (SKIFN, mkexpr(op,t,ctlstack->domax),
				ctlstack->dobodylabel,0);
		else
			putif (mkexpr(op, t, ctlstack->domax),
				ctlstack->dobodylabel);
		}
	if (optimflag)
		optbuff (SKLABEL,0,ctlstack->endlabel,0);
	else
		putlabel (ctlstack->endlabel);

	if (ap = memversion(np))
		{
		if (optimflag)
			optbuff (SKEQ,mkexpr(OPASSIGN,ap, rv),0,0);
		else
			puteq (ap, rv);
		}
	else
		frexpr(rv);
	for (i = 0; i < 4; i++)
		ctlstack->ctlabels[i] = 0;
	if (!optimflag)
		deregister(ctlstack->donamep);
	ctlstack->donamep->vdovar = NO;
	if (optimflag)
		doslot->nullslot = optbuff (SKNULL,0,0,0);
	}

      popctl();
      poplab();
      
      dorange = 0;
      for (q = ctlstack; q >= ctls; --q)
	if (q->ctltype == CTLDO)
	  {
	    dorange = q->dolabel;
	    break;
	  }
    }
}


exassign(vname, labelval)
Namep vname;
struct Labelblock *labelval;
{
Addrp p;
expptr mkaddcon();

p = mkplace(vname);
#if SZADDR > SZSHORT
if( p->vtype == TYSHORT )
	err("insufficient precision in ASSIGN variable");
else
#endif
if( ! ONEOF(p->vtype, MSKINT|MSKADDR) )
	err("noninteger assign variable");
else
	{
	if (optimflag)
		optbuff (SKASSIGN, p, labelval->labelno, 0);
	else
		puteq (p, intrconv(p->vtype, mkaddcon(labelval->labelno)));
	}
}



exarif(expr, neglab, zerlab, poslab)
expptr expr;
struct Labelblock *neglab, *zerlab, *poslab;
{
register int lm, lz, lp;
struct Labelblock *labels[3];

lm = neglab->labelno;
lz = zerlab->labelno;
lp = poslab->labelno;
expr = fixtype(expr);

if( ! ONEOF(expr->headblock.vtype, MSKINT|MSKREAL) )
	{
	err("invalid type of arithmetic if expression");
	frexpr(expr);
	}
else
	{
	if(lm == lz)
		exar2(OPLE, expr, lm, lp);
	else if(lm == lp)
		exar2(OPNE, expr, lm, lz);
	else if(lz == lp)
		exar2(OPGE, expr, lz, lm);
	else
		if (optimflag)
			{
			labels[0] = neglab;
			labels[1] = zerlab;
			labels[2] = poslab;
			optbuff (SKARIF, expr, 0, labels);
			}
		else
			prarif(expr, lm, lz, lp);
	}
}



LOCAL exar2 (op, e, l1, l2)
int	op;
expptr	e;
int	l1,l2;
{
if (optimflag)
	{
	optbuff (SKIFN, mkexpr(op, e, ICON(0)), l2, 0);
	optbuff (SKGOTO, 0, l1, 0);
	}
else
	{
	putif (mkexpr(op, e, ICON(0)), l2);
	putgoto (l1);
	}
}


exreturn(p)
register expptr p;
{
if(procclass != CLPROC)
	warn("RETURN statement in main or block data");
if(p && (proctype!=TYSUBR || procclass!=CLPROC) )
	{
	err("alternate return in nonsubroutine");
	p = 0;
	}

if(p)
	if (optimflag)
		optbuff (SKRETURN, p, retlabel, 0);
	else
		{
		putforce (TYINT, p);
		putgoto (retlabel);
		}
else
	if (optimflag)
		optbuff (SKRETURN, p,
			 (proctype==TYSUBR ? ret0label : retlabel), 0);
	else
		putgoto (proctype==TYSUBR ? ret0label : retlabel);
}



exasgoto(labvar)
struct Hashentry *labvar;
{
register Addrp p;

p = mkplace(labvar);
if( ! ISINT(p->vtype) )
	err("assigned goto variable must be integer");
else
	if (optimflag)
		optbuff (SKASGOTO, p, 0, 0);
	else
		putbranch (p);
}
E 1
