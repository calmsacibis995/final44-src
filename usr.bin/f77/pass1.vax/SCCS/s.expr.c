h64764
s 00007/00006/03009
d D 5.10 91/04/12 16:08:44 bostic 10 9
c new copyright; att/bsd/shared
e
s 00085/00085/02930
d D 5.9 88/01/03 15:56:55 bostic 9 8
c const is an ANSI C keyword
e
s 00032/00001/02983
d D 5.8 86/05/09 22:54:28 donn 8 7
c (1) The compiler permitted the ordinary relational operators to be used with
c LOGICAL values but didn't produce useful results.  Now you can use .eq. and
c .ne. (although a warning is printed) and the other relational operators
c elicit errors.  (2) Length information on expressions is now properly
c propagated and freed; this used to cause confusion for certain concatenations.
e
s 00009/00000/02975
d D 5.7 86/04/26 23:47:23 donn 7 6
c Someone forgot about comparisons of logical constants in consbinop() --
c the results of such tests were garbage.
e
s 00007/00002/02968
d D 5.6 86/02/20 22:51:01 donn 6 5
c Fix memory management problem with reordering of array dimension and
c substring code in mklhs().
e
s 00134/00010/02836
d D 5.5 86/01/07 19:05:26 donn 5 4
c (1) Lots of changes for handling hardware errors which can crop up
c when evaluating constant expressions.  (2) Don't optimize first/last char
c values when they contain function calls or array references.  (3)  Name
c the offending subroutine when it's used as a function.  (4) Fix bug in
c mklhs() that caused the 'first character' substring parameter to be
c evaluated twice.
e
s 00022/00003/02824
d D 5.4 85/08/29 00:44:29 donn 4 3
c Added Jerry Berkman's changes to call pow() directly rather than
c indirectly through pow_dd(), in mkpower(); fixed another of my goofs in
c the substring parameter conversion code in mkprim().
e
s 00009/00002/02818
d D 5.3 85/06/23 13:32:33 mckusick 3 2
c fix from donn@utah-cs
e
s 00016/00006/02804
d D 5.2 85/06/09 10:01:50 mckusick 2 1
c from donn@utah-cs.ARPA
e
s 02810/00000/00000
d D 5.1 85/06/07 21:32:28 mckusick 1 0
c 4.3BSD beta release version
e
u
U
t
T
I 1
D 10
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
E 10
 */

#ifndef lint
D 10
static char *sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 10
I 10
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 10

/*
 * expr.c
 *
 * Routines for handling expressions, f77 compiler pass 1.
 *
 * University of Utah CS Dept modification history:
 *
D 2
 * Revision 3.13  85/05/13  16:40:37  mckusick
 * fix to copy character values into numerics (from donn@utah-cs)
E 2
I 2
 * $Log:	expr.c,v $
I 8
 * Revision 5.13  86/05/07  18:54:23  donn
 * Adjusted the warning for OPEQ with logical operands -- this is now printed
 * in mkexpr since cktype can be called several times on the same operands
 * (argh -- how slow can this compiler get?!).
 * 
 * Revision 5.12  86/05/07  17:40:54  donn
 * Make the lengths of expr nodes be copied by cpexpr and freed by frexpr.
 * 
 * Revision 5.11  86/05/07  16:57:17  donn
 * Logical data is supposed to be compared using .eqv. and .neqv., but we
 * will support .eq. and .ne. with a warning.  Other relational operators
 * now provoke errors when used with logical operands.
 * 
E 8
I 7
 * Revision 5.10  86/04/26  13:24:30  donn
 * Someone forgot about comparisons of logical constants in consbinop() --
 * the results of such tests were garbage.
 * 
E 7
I 6
 * Revision 5.9  86/02/20  23:38:31  donn
 * Fix memory management problem with reordering of array dimension and
 * substring code in mklhs().
 * 
E 6
I 5
 * Revision 5.8  85/12/20  21:37:58  donn
 * Fix bug in mklhs() that caused the 'first character' substring parameter
 * to be evaluated twice.
 * 
 * Revision 5.7  85/12/20  19:42:05  donn
 * Be more specfic -- name the offending subroutine when it's used as a
 * function.
 * 
 * Revision 5.6  85/12/19  20:08:12  donn
 * Don't optimize first/last char values when they contain function calls
 * or array references.
 * 
 * Revision 5.5  85/12/19  00:35:22  donn
 * Lots of changes for handling hardware errors which can crop up when
 * evaluating constant expressions.
 * 
 * Revision 5.4  85/11/25  00:23:53  donn
 * 4.3 beta
 * 
E 5
I 4
 * Revision 5.3  85/08/10  05:48:16  donn
 * Fixed another of my goofs in the substring parameter conversion code.
 * 
 * Revision 5.2  85/08/10  04:13:51  donn
 * Jerry Berkman's change to call pow() directly rather than indirectly
 * through pow_dd, in mkpower().
 * 
 * Revision 5.1  85/08/10  03:44:19  donn
 * 4.3 alpha
 * 
E 4
I 3
 * Revision 3.16  85/06/21  16:38:09  donn
 * The fix to mkprim() didn't handle null substring parameters (sigh).
 * 
E 3
 * Revision 3.15  85/06/04  04:37:03  donn
 * Changed mkprim() to force substring parameters to be integral types.
E 2
 * 
I 2
 * Revision 3.14  85/06/04  03:41:52  donn
 * Change impldcl() to handle functions of type 'undefined'.
 * 
 * Revision 3.13  85/05/06  23:14:55  donn
 * Changed mkconv() so that it calls mkaltemp() instead of mktemp() to get
 * a temporary when converting character strings to integers; previously we
 * were having problems because mkconv() was called after tempalloc().
 * 
E 2
 * Revision 3.12  85/03/18  08:07:47  donn
 * Fixes to help out with short integers -- if integers are by default short,
 * then so are constants; and if addresses can't be stored in shorts, complain.
 * 
 * Revision 3.11  85/03/16  22:31:27  donn
 * Added hack to mkconv() to allow character values of length > 1 to be
 * converted to numeric types, for Helge Skrivervik.  Note that this does
 * not affect use of the intrinsic ichar() conversion.
 * 
 * Revision 3.10  85/01/15  21:06:47  donn
 * Changed mkconv() to comment on implicit conversions; added intrconv() for
 * use with explicit conversions by intrinsic functions.
 * 
 * Revision 3.9  85/01/11  21:05:49  donn
 * Added changes to implement SAVE statements.
 * 
 * Revision 3.8  84/12/17  02:21:06  donn
 * Added a test to prevent constant folding from being done on expressions
 * whose type is not known at that point in mkexpr().
 * 
 * Revision 3.7  84/12/11  21:14:17  donn
 * Removed obnoxious 'excess precision' warning.
 * 
 * Revision 3.6  84/11/23  01:00:36  donn
 * Added code to trim excess precision from single-precision constants, and
 * to warn the user when this occurs.
 * 
 * Revision 3.5  84/11/23  00:10:39  donn
 * Changed stfcall() to remark on argument type clashes in 'calls' to
 * statement functions.
 * 
 * Revision 3.4  84/11/22  21:21:17  donn
 * Fixed bug in fix to mkexpr() that caused IMPLICIT to affect intrinsics.
 * 
 * Revision 3.3  84/11/12  18:26:14  donn
 * Shuffled some code around so that the compiler remembers to free some vleng
 * structures which used to just sit around.
 * 
 * Revision 3.2  84/10/16  19:24:15  donn
 * Fix for Peter Montgomery's bug with -C and invalid subscripts -- prevent
 * core dumps by replacing bad subscripts with good ones.
 * 
 * Revision 3.1  84/10/13  01:31:32  donn
 * Merged Jerry Berkman's version into mine.
 * 
 * Revision 2.7  84/09/27  15:42:52  donn
 * The last fix for multiplying undeclared variables by 0 isn't sufficient,
 * since the type of the 0 may not be the (implicit) type of the variable.
 * I added a hack to check the implicit type of implicitly declared
 * variables...
 * 
 * Revision 2.6  84/09/14  19:34:03  donn
 * Problem noted by Mike Vevea -- mkexpr will sometimes attempt to convert
 * 0 to type UNKNOWN, which is illegal.  Fix is to use native type instead.
 * Not sure how correct (or important) this is...
 * 
 * Revision 2.5  84/08/05  23:05:27  donn
 * Added fixes to prevent fixexpr() from slicing and dicing complex conversions
 * with two operands.
 * 
 * Revision 2.4  84/08/05  17:34:48  donn
 * Added an optimization to mklhs() to detect substrings of the form ch(i:i)
 * and assign constant length 1 to them.
 * 
 * Revision 2.3  84/07/19  19:38:33  donn
 * Added a typecast to the last fix.  Somehow I missed it the first time...
 * 
 * Revision 2.2  84/07/19  17:19:57  donn
 * Caused OPPAREN expressions to inherit the length of their operands, so
 * that parenthesized character expressions work correctly.
 * 
 * Revision 2.1  84/07/19  12:03:02  donn
 * Changed comment headers for UofU.
 * 
 * Revision 1.2  84/04/06  20:12:17  donn
 * Fixed bug which caused programs with mixed-type multiplications involving
 * the constant 0 to choke the compiler.
 * 
 */

#include "defs.h"


/* little routines to create constant blocks */

Constp mkconst(t)
register int t;
{
register Constp p;

p = ALLOC(Constblock);
p->tag = TCONST;
p->vtype = t;
return(p);
}


expptr mklogcon(l)
register int l;
{
register Constp  p;

p = mkconst(TYLOGICAL);
D 9
p->const.ci = l;
E 9
I 9
p->constant.ci = l;
E 9
return( (expptr) p );
}



expptr mkintcon(l)
ftnint l;
{
register Constp p;
int usetype;

if(tyint == TYSHORT)
  {
    short s = l;
    if(l != s)
      usetype = TYLONG;
    else
      usetype = TYSHORT;
  }
else
  usetype = tyint;
p = mkconst(usetype);
D 9
p->const.ci = l;
E 9
I 9
p->constant.ci = l;
E 9
return( (expptr) p );
}



expptr mkaddcon(l)
register int l;
{
register Constp p;

p = mkconst(TYADDR);
D 9
p->const.ci = l;
E 9
I 9
p->constant.ci = l;
E 9
return( (expptr) p );
}



expptr mkrealcon(t, d)
register int t;
double d;
{
register Constp p;

if(t == TYREAL)
  {
    float f = d;
    if(f != d)
      {
#ifdef notdef
	warn("excess precision in real constant lost");
#endif notdef
	d = f;
      }
  }
p = mkconst(t);
D 9
p->const.cd[0] = d;
E 9
I 9
p->constant.cd[0] = d;
E 9
return( (expptr) p );
}


expptr mkbitcon(shift, leng, s)
int shift;
register int leng;
register char *s;
{
  Constp p;
  register int i, j, k;
  register char *bp;
  int size;

  size = (shift*leng + BYTESIZE -1)/BYTESIZE;
  bp = (char *) ckalloc(size);

  i = 0;

#if (TARGET == PDP11 || TARGET == VAX)
  j = 0;
#else
  j = size;
#endif

  k = 0;

  while (leng > 0)
    {
      k |= (hextoi(s[--leng]) << i);
      i += shift;
      if (i >= BYTESIZE)
	{
#if (TARGET == PDP11 || TARGET == VAX)
	  bp[j++] = k & MAXBYTE;
#else
	  bp[--j] = k & MAXBYTE;
#endif
	  k = k >> BYTESIZE;
	  i -= BYTESIZE;
	}
    }

  if (k != 0)
#if (TARGET == PDP11 || TARGET == VAX)
    bp[j++] = k;
#else
    bp[--j] = k;
#endif

  p = mkconst(TYBITSTR);
  p->vleng = ICON(size);
D 9
  p->const.ccp = bp;
E 9
I 9
  p->constant.ccp = bp;
E 9

  return ((expptr) p);
}



expptr mkstrcon(l,v)
int l;
register char *v;
{
register Constp p;
register char *s;

p = mkconst(TYCHAR);
p->vleng = ICON(l);
D 9
p->const.ccp = s = (char *) ckalloc(l);
E 9
I 9
p->constant.ccp = s = (char *) ckalloc(l);
E 9
while(--l >= 0)
	*s++ = *v++;
return( (expptr) p );
}


expptr mkcxcon(realp,imagp)
register expptr realp, imagp;
{
int rtype, itype;
register Constp p;

rtype = realp->headblock.vtype;
itype = imagp->headblock.vtype;

if( ISCONST(realp) && ISNUMERIC(rtype) && ISCONST(imagp) && ISNUMERIC(itype) )
	{
	p = mkconst( (rtype==TYDREAL||itype==TYDREAL) ? TYDCOMPLEX : TYCOMPLEX);
	if( ISINT(rtype) )
D 9
		p->const.cd[0] = realp->constblock.const.ci;
	else	p->const.cd[0] = realp->constblock.const.cd[0];
E 9
I 9
		p->constant.cd[0] = realp->constblock.constant.ci;
	else	p->constant.cd[0] = realp->constblock.constant.cd[0];
E 9
	if( ISINT(itype) )
D 9
		p->const.cd[1] = imagp->constblock.const.ci;
	else	p->const.cd[1] = imagp->constblock.const.cd[0];
E 9
I 9
		p->constant.cd[1] = imagp->constblock.constant.ci;
	else	p->constant.cd[1] = imagp->constblock.constant.cd[0];
E 9
	}
else
	{
	err("invalid complex constant");
	p = (Constp) errnode();
	}

frexpr(realp);
frexpr(imagp);
return( (expptr) p );
}


expptr errnode()
{
struct Errorblock *p;
p = ALLOC(Errorblock);
p->tag = TERROR;
p->vtype = TYERROR;
return( (expptr) p );
}





expptr mkconv(t, p)
register int t;
register expptr p;
{
register expptr q;
Addrp r, s;
register int pt;
expptr opconv();

if(t==TYUNKNOWN || t==TYERROR)
	badtype("mkconv", t);
pt = p->headblock.vtype;
if(t == pt)
	return(p);

if( pt == TYCHAR && ISNUMERIC(t) )
	{
	warn("implicit conversion of character to numeric type");

	/*
	 * Ugly kluge to copy character values into numerics.
	 */
	s = mkaltemp(t, ENULL);
	r = (Addrp) cpexpr(s);
	r->vtype = TYCHAR;
	r->varleng = typesize[t];
	r->vleng = mkintcon(r->varleng);
	q = mkexpr(OPASSIGN, r, p);
	q = mkexpr(OPCOMMA, q, s);
	return(q);
	}

#if SZADDR > SZSHORT
if( pt == TYADDR && t == TYSHORT)
	{
	err("insufficient precision to hold address type");
	return( errnode() );
	}
#endif
if( pt == TYADDR && ISNUMERIC(t) )
	warn("implicit conversion of address to numeric type");

if( ISCONST(p) && pt!=TYADDR)
	{
	q = (expptr) mkconst(t);
D 9
	consconv(t, &(q->constblock.const),
		p->constblock.vtype, &(p->constblock.const) );
E 9
I 9
	consconv(t, &(q->constblock.constant),
		p->constblock.vtype, &(p->constblock.constant) );
E 9
	frexpr(p);
	}
#if TARGET == PDP11
else if(ISINT(t) && pt==TYCHAR)
	{
	q = mkexpr(OPBITAND, opconv(p,TYSHORT), ICON(255));
	if(t == TYLONG)
		q = opconv(q, TYLONG);
	}
#endif
else
	q = opconv(p, t);

if(t == TYCHAR)
	q->constblock.vleng = ICON(1);
return(q);
}



/* intrinsic conversions */
expptr intrconv(t, p)
register int t;
register expptr p;
{
register expptr q;
register int pt;
expptr opconv();

if(t==TYUNKNOWN || t==TYERROR)
	badtype("intrconv", t);
pt = p->headblock.vtype;
if(t == pt)
	return(p);

else if( ISCONST(p) && pt!=TYADDR)
	{
	q = (expptr) mkconst(t);
D 9
	consconv(t, &(q->constblock.const),
		p->constblock.vtype, &(p->constblock.const) );
E 9
I 9
	consconv(t, &(q->constblock.constant),
		p->constblock.vtype, &(p->constblock.constant) );
E 9
	frexpr(p);
	}
#if TARGET == PDP11
else if(ISINT(t) && pt==TYCHAR)
	{
	q = mkexpr(OPBITAND, opconv(p,TYSHORT), ICON(255));
	if(t == TYLONG)
		q = opconv(q, TYLONG);
	}
#endif
else
	q = opconv(p, t);

if(t == TYCHAR)
	q->constblock.vleng = ICON(1);
return(q);
}



expptr opconv(p, t)
expptr p;
int t;
{
register expptr q;

q = mkexpr(OPCONV, p, PNULL);
q->headblock.vtype = t;
return(q);
}



expptr addrof(p)
expptr p;
{
return( mkexpr(OPADDR, p, PNULL) );
}



tagptr cpexpr(p)
register tagptr p;
{
register tagptr e;
int tag;
register chainp ep, pp;
tagptr cpblock();

static int blksize[ ] =
	{	0,
		sizeof(struct Nameblock),
		sizeof(struct Constblock),
		sizeof(struct Exprblock),
		sizeof(struct Addrblock),
		sizeof(struct Tempblock),
		sizeof(struct Primblock),
		sizeof(struct Listblock),
		sizeof(struct Errorblock)
	};

if(p == NULL)
	return(NULL);

if( (tag = p->tag) == TNAME)
	return(p);

e = cpblock( blksize[p->tag] , p);

switch(tag)
	{
	case TCONST:
		if(e->constblock.vtype == TYCHAR)
			{
D 9
			e->constblock.const.ccp =
				copyn(1+strlen(e->constblock.const.ccp),
					e->constblock.const.ccp);
E 9
I 9
			e->constblock.constant.ccp =
				copyn(1+strlen(e->constblock.constant.ccp),
					e->constblock.constant.ccp);
E 9
			e->constblock.vleng =
				(expptr) cpexpr(e->constblock.vleng);
			}
	case TERROR:
		break;

	case TEXPR:
		e->exprblock.leftp =  (expptr) cpexpr(p->exprblock.leftp);
		e->exprblock.rightp = (expptr) cpexpr(p->exprblock.rightp);
I 8
		e->addrblock.vleng =  (expptr) cpexpr(e->addrblock.vleng);
E 8
		break;

	case TLIST:
		if(pp = p->listblock.listp)
			{
			ep = e->listblock.listp =
				mkchain( cpexpr(pp->datap), CHNULL);
			for(pp = pp->nextp ; pp ; pp = pp->nextp)
				ep = ep->nextp =
					mkchain( cpexpr(pp->datap), CHNULL);
			}
		break;

	case TADDR:
		e->addrblock.vleng = (expptr)  cpexpr(e->addrblock.vleng);
		e->addrblock.memoffset = (expptr)cpexpr(e->addrblock.memoffset);
		e->addrblock.istemp = NO;
		break;

	case TTEMP:
		e->tempblock.vleng = (expptr)  cpexpr(e->tempblock.vleng);
		e->tempblock.istemp = NO;
		break;

	case TPRIM:
		e->primblock.argsp = (struct Listblock *)
					cpexpr(e->primblock.argsp);
		e->primblock.fcharp = (expptr) cpexpr(e->primblock.fcharp);
		e->primblock.lcharp = (expptr) cpexpr(e->primblock.lcharp);
		break;

	default:
		badtag("cpexpr", tag);
	}

return(e);
}

frexpr(p)
register tagptr p;
{
register chainp q;

if(p == NULL)
	return;

switch(p->tag)
	{
	case TCONST:
		switch (p->constblock.vtype)
			{
			case TYBITSTR:
			case TYCHAR:
			case TYHOLLERITH:
D 9
				free( (charptr) (p->constblock.const.ccp) );
E 9
I 9
				free( (charptr) (p->constblock.constant.ccp) );
E 9
				frexpr(p->constblock.vleng);
			}
		break;

	case TADDR:
		if (!optimflag && p->addrblock.istemp)
			{
			frtemp(p);
			return;
			}
		frexpr(p->addrblock.vleng);
		frexpr(p->addrblock.memoffset);
		break;

	case TTEMP:
		frexpr(p->tempblock.vleng);
		break;

	case TERROR:
		break;

	case TNAME:
		return;

	case TPRIM:
		frexpr(p->primblock.argsp);
		frexpr(p->primblock.fcharp);
		frexpr(p->primblock.lcharp);
		break;

	case TEXPR:
		frexpr(p->exprblock.leftp);
		if(p->exprblock.rightp)
			frexpr(p->exprblock.rightp);
I 8
		if(p->exprblock.vleng)
			frexpr(p->exprblock.vleng);
E 8
		break;

	case TLIST:
		for(q = p->listblock.listp ; q ; q = q->nextp)
			frexpr(q->datap);
		frchain( &(p->listblock.listp) );
		break;

	default:
		badtag("frexpr", p->tag);
	}

free( (charptr) p );
}

/* fix up types in expression; replace subtrees and convert
   names to address blocks */

expptr fixtype(p)
register tagptr p;
{

if(p == 0)
	return(0);

switch(p->tag)
	{
	case TCONST:
		return( (expptr) p );

	case TADDR:
		p->addrblock.memoffset = fixtype(p->addrblock.memoffset);
		return( (expptr) p);

	case TTEMP:
		return( (expptr) p);

	case TERROR:
		return( (expptr) p);

	default:
		badtag("fixtype", p->tag);

	case TEXPR:
		return( fixexpr(p) );

	case TLIST:
		return( (expptr) p );

	case TPRIM:
		if(p->primblock.argsp && p->primblock.namep->vclass!=CLVAR)
			{
			if(p->primblock.namep->vtype == TYSUBR)
				{
D 5
				err("function invocation of subroutine");
E 5
I 5
				dclerr("function invocation of subroutine",
					p->primblock.namep);
E 5
				return( errnode() );
				}
			else
				return( mkfunct(p) );
			}
		else	return( mklhs(p) );
	}
}





/* special case tree transformations and cleanups of expression trees */

expptr fixexpr(p)
register Exprp p;
{
expptr lp;
register expptr rp;
register expptr q;
int opcode, ltype, rtype, ptype, mtype;
expptr lconst, rconst;
expptr mkpower();

if( ISERROR(p) )
	return( (expptr) p );
else if(p->tag != TEXPR)
	badtag("fixexpr", p->tag);
opcode = p->opcode;
if (ISCONST(p->leftp))
	lconst = (expptr) cpexpr(p->leftp);
else
	lconst = NULL;
if (p->rightp && ISCONST(p->rightp))
	rconst = (expptr) cpexpr(p->rightp);
else
	rconst = NULL;
lp = p->leftp = fixtype(p->leftp);
ltype = lp->headblock.vtype;
if(opcode==OPASSIGN && lp->tag!=TADDR && lp->tag!=TTEMP)
	{
	err("left side of assignment must be variable");
	frexpr(p);
	return( errnode() );
	}

if(p->rightp)
	{
	rp = p->rightp = fixtype(p->rightp);
	rtype = rp->headblock.vtype;
	}
else
	{
	rp = NULL;
	rtype = 0;
	}

if(ltype==TYERROR || rtype==TYERROR)
	{
	frexpr(p);
	frexpr(lconst);
	frexpr(rconst);
	return( errnode() );
	}

/* force folding if possible */
if( ISCONST(lp) && (rp==NULL || ISCONST(rp)) )
	{
	q = mkexpr(opcode, lp, rp);
	if( ISCONST(q) )
		{
		frexpr(lconst);
		frexpr(rconst);
		return(q);
		}
	free( (charptr) q );	/* constants did not fold */
	}

if( (ptype = cktype(opcode, ltype, rtype)) == TYERROR)
	{
	frexpr(p);
	frexpr(lconst);
	frexpr(rconst);
	return( errnode() );
	}

switch(opcode)
	{
	case OPCONCAT:
		if(p->vleng == NULL)
			p->vleng = mkexpr(OPPLUS,
				cpexpr(lp->headblock.vleng),
				cpexpr(rp->headblock.vleng) );
		break;

	case OPASSIGN:
	case OPPLUSEQ:
	case OPSTAREQ:
		if(ltype == rtype)
			break;
		if( ! rconst && ISREAL(ltype) && ISREAL(rtype) )
			break;
		if( ISCOMPLEX(ltype) || ISCOMPLEX(rtype) )
			break;
		if( ONEOF(ltype, MSKADDR|MSKINT) && ONEOF(rtype, MSKADDR|MSKINT)
#if FAMILY==PCC
		    && typesize[ltype]>=typesize[rtype] )
#else
		    && typesize[ltype]==typesize[rtype] )
#endif
			break;
		if (rconst)
			{
			p->rightp = fixtype( mkconv(ptype, cpexpr(rconst)) );
			frexpr(rp);
			}
		else
			p->rightp = fixtype(mkconv(ptype, rp));
		break;

	case OPSLASH:
		if( ISCOMPLEX(rtype) )
			{
			p = (Exprp) call2(ptype,
				ptype==TYCOMPLEX? "c_div" : "z_div",
				mkconv(ptype, lp), mkconv(ptype, rp) );
			break;
			}
	case OPPLUS:
	case OPMINUS:
	case OPSTAR:
	case OPMOD:
		if(ptype==TYDREAL && ( (ltype==TYREAL && ! lconst ) ||
		    (rtype==TYREAL && ! rconst ) ))
			break;
		if( ISCOMPLEX(ptype) )
			break;
		if(ltype != ptype)
			if (lconst)
				{
				p->leftp = fixtype(mkconv(ptype,
						cpexpr(lconst)));
				frexpr(lp);
				}
			else
				p->leftp = fixtype(mkconv(ptype,lp));
		if(rtype != ptype)
			if (rconst)
				{
				p->rightp = fixtype(mkconv(ptype,
						cpexpr(rconst)));
				frexpr(rp);
				}
			else
				p->rightp = fixtype(mkconv(ptype,rp));
		break;

	case OPPOWER:
		return( mkpower(p) );

	case OPLT:
	case OPLE:
	case OPGT:
	case OPGE:
	case OPEQ:
	case OPNE:
		if(ltype == rtype)
			break;
		mtype = cktype(OPMINUS, ltype, rtype);
		if(mtype==TYDREAL && ( (ltype==TYREAL && ! lconst) ||
		    (rtype==TYREAL && ! rconst) ))
			break;
		if( ISCOMPLEX(mtype) )
			break;
		if(ltype != mtype)
			if (lconst)
				{
				p->leftp = fixtype(mkconv(mtype,
						cpexpr(lconst)));
				frexpr(lp);
				}
			else
				p->leftp = fixtype(mkconv(mtype,lp));
		if(rtype != mtype)
			if (rconst)
				{
				p->rightp = fixtype(mkconv(mtype,
						cpexpr(rconst)));
				frexpr(rp);
				}
			else
				p->rightp = fixtype(mkconv(mtype,rp));
		break;


	case OPCONV:
		if(ISCOMPLEX(p->vtype))
			{
			ptype = cktype(OPCONV, p->vtype, ltype);
			if(p->rightp)
				ptype = cktype(OPCONV, ptype, rtype);
			break;
			}
		ptype = cktype(OPCONV, p->vtype, ltype);
		if(lp->tag==TEXPR && lp->exprblock.opcode==OPCOMMA)
			{
			lp->exprblock.rightp =
				fixtype( mkconv(ptype, lp->exprblock.rightp) );
			free( (charptr) p );
			p = (Exprp) lp;
			}
		break;

	case OPADDR:
		if(lp->tag==TEXPR && lp->exprblock.opcode==OPADDR)
			fatal("addr of addr");
		break;

	case OPCOMMA:
	case OPQUEST:
	case OPCOLON:
		break;

	case OPPAREN:
		p->vleng = (expptr) cpexpr( lp->headblock.vleng );
		break;

	case OPMIN:
	case OPMAX:
		ptype = p->vtype;
		break;

	default:
		break;
	}

p->vtype = ptype;
frexpr(lconst);
frexpr(rconst);
return((expptr) p);
}

#if SZINT < SZLONG
/*
   for efficient subscripting, replace long ints by shorts
   in easy places
*/

expptr shorten(p)
register expptr p;
{
register expptr q;

if(p->headblock.vtype != TYLONG)
	return(p);

switch(p->tag)
	{
	case TERROR:
	case TLIST:
		return(p);

	case TCONST:
	case TADDR:
		return( mkconv(TYINT,p) );

	case TEXPR:
		break;

	default:
		badtag("shorten", p->tag);
	}

switch(p->exprblock.opcode)
	{
	case OPPLUS:
	case OPMINUS:
	case OPSTAR:
		q = shorten( cpexpr(p->exprblock.rightp) );
		if(q->headblock.vtype == TYINT)
			{
			p->exprblock.leftp = shorten(p->exprblock.leftp);
			if(p->exprblock.leftp->headblock.vtype == TYLONG)
				frexpr(q);
			else
				{
				frexpr(p->exprblock.rightp);
				p->exprblock.rightp = q;
				p->exprblock.vtype = TYINT;
				}
			}
		break;

	case OPNEG:
	case OPPAREN:
		p->exprblock.leftp = shorten(p->exprblock.leftp);
		if(p->exprblock.leftp->headblock.vtype == TYINT)
			p->exprblock.vtype = TYINT;
		break;

	case OPCALL:
	case OPCCALL:
		p = mkconv(TYINT,p);
		break;
	default:
		break;
	}

return(p);
}
#endif

/* fix an argument list, taking due care for special first level cases */

fixargs(doput, p0)
int doput;	/* doput is true if the function is not intrinsic;
		   was used to decide whether to do a putconst,
		   but this is no longer done here (Feb82)*/
struct Listblock *p0;
{
register chainp p;
register tagptr q, t;
register int qtag;
int nargs;
Addrp mkscalar();

nargs = 0;
if(p0)
    for(p = p0->listp ; p ; p = p->nextp)
	{
	++nargs;
	q = p->datap;
	qtag = q->tag;
	if(qtag == TCONST)
		{
		if(q->constblock.vtype == TYSHORT)
			q = (tagptr) mkconv(tyint, q);
		p->datap = q ;
		}
	else if(qtag==TPRIM && q->primblock.argsp==0 &&
		q->primblock.namep->vclass==CLPROC)
			p->datap = (tagptr) mkaddr(q->primblock.namep);
	else if(qtag==TPRIM && q->primblock.argsp==0 &&
		q->primblock.namep->vdim!=NULL)
			p->datap = (tagptr) mkscalar(q->primblock.namep);
	else if(qtag==TPRIM && q->primblock.argsp==0 &&
		q->primblock.namep->vdovar && 
		(t = (tagptr) memversion(q->primblock.namep)) )
			p->datap = (tagptr) fixtype(t);
	else
		p->datap = (tagptr) fixtype(q);
	}
return(nargs);
}


Addrp mkscalar(np)
register Namep np;
{
register Addrp ap;

vardcl(np);
ap = mkaddr(np);

#if TARGET == VAX
	/* on the VAX, prolog causes array arguments
	   to point at the (0,...,0) element, except when
	   subscript checking is on
	*/
#ifdef SDB
	if( !checksubs && !sdbflag && np->vstg==STGARG)
#else
	if( !checksubs && np->vstg==STGARG)
#endif
		{
		register struct Dimblock *dp;
		dp = np->vdim;
		frexpr(ap->memoffset);
		ap->memoffset = mkexpr(OPSTAR,
				(np->vtype==TYCHAR ?
					cpexpr(np->vleng) :
					(tagptr)ICON(typesize[np->vtype]) ),
				cpexpr(dp->baseoffset) );
		}
#endif
return(ap);
}





expptr mkfunct(p)
register struct Primblock *p;
{
struct Entrypoint *ep;
Addrp ap;
struct Extsym *extp;
register Namep np;
register expptr q;
expptr intrcall(), stfcall();
int k, nargs;
int class;

if(p->tag != TPRIM)
	return( errnode() );

np = p->namep;
class = np->vclass;

if(class == CLUNKNOWN)
	{
	np->vclass = class = CLPROC;
	if(np->vstg == STGUNKNOWN)
		{
		if(np->vtype!=TYSUBR && (k = intrfunct(np->varname)) )
			{
			np->vstg = STGINTR;
			np->vardesc.varno = k;
			np->vprocclass = PINTRINSIC;
			}
		else
			{
			extp = mkext( varunder(VL,np->varname) );
			extp->extstg = STGEXT;
			np->vstg = STGEXT;
			np->vardesc.varno = extp - extsymtab;
			np->vprocclass = PEXTERNAL;
			}
		}
	else if(np->vstg==STGARG)
		{
		if(np->vtype!=TYCHAR && !ftn66flag)
		    warn("Dummy procedure not declared EXTERNAL. Code may be wrong.");
		np->vprocclass = PEXTERNAL;
		}
	}

if(class != CLPROC)
	fatali("invalid class code %d for function", class);
if(p->fcharp || p->lcharp)
	{
	err("no substring of function call");
	goto error;
	}
impldcl(np);
nargs = fixargs( np->vprocclass!=PINTRINSIC,  p->argsp);

switch(np->vprocclass)
	{
	case PEXTERNAL:
		ap = mkaddr(np);
	call:
		q = mkexpr(OPCALL, ap, p->argsp);
		if( (q->exprblock.vtype = np->vtype) == TYUNKNOWN)
			{
			err("attempt to use untyped function");
			goto error;
			}
		if(np->vleng)
			q->exprblock.vleng = (expptr) cpexpr(np->vleng);
		break;

	case PINTRINSIC:
		q = intrcall(np, p->argsp, nargs);
		break;

	case PSTFUNCT:
		q = stfcall(np, p->argsp);
		break;

	case PTHISPROC:
		warn("recursive call");
		for(ep = entries ; ep ; ep = ep->entnextp)
			if(ep->enamep == np)
				break;
		if(ep == NULL)
			fatal("mkfunct: impossible recursion");
		ap = builtin(np->vtype, varstr(XL, ep->entryname->extname) );
		goto call;

	default:
		fatali("mkfunct: impossible vprocclass %d",
			(int) (np->vprocclass) );
	}
free( (charptr) p );
return(q);

error:
	frexpr(p);
	return( errnode() );
}



LOCAL expptr stfcall(np, actlist)
Namep np;
struct Listblock *actlist;
{
register chainp actuals;
int nargs;
chainp oactp, formals;
int type;
expptr q, rhs, ap;
Namep tnp;
register struct Rplblock *rp;
struct Rplblock *tlist;

if(actlist)
	{
	actuals = actlist->listp;
	free( (charptr) actlist);
	}
else
	actuals = NULL;
oactp = actuals;

nargs = 0;
tlist = NULL;
if( (type = np->vtype) == TYUNKNOWN)
	{
	err("attempt to use untyped statement function");
	q = errnode();
	goto ret;
	}
formals = (chainp) (np->varxptr.vstfdesc->datap);
rhs = (expptr) (np->varxptr.vstfdesc->nextp);

/* copy actual arguments into temporaries */
while(actuals!=NULL && formals!=NULL)
	{
	rp = ALLOC(Rplblock);
	rp->rplnp = tnp = (Namep) (formals->datap);
	ap = fixtype(actuals->datap);
	if(tnp->vtype==ap->headblock.vtype && tnp->vtype!=TYCHAR
	   && (ap->tag==TCONST || ap->tag==TADDR || ap->tag==TTEMP) )
		{
		rp->rplvp = (expptr) ap;
		rp->rplxp = NULL;
		rp->rpltag = ap->tag;
		}
	else	{
		rp->rplvp = (expptr) mktemp(tnp->vtype, tnp->vleng);
		rp->rplxp = fixtype( mkexpr(OPASSIGN, cpexpr(rp->rplvp), ap) );
		if( (rp->rpltag = rp->rplxp->tag) == TERROR)
			err("disagreement of argument types in statement function call");
		else if(tnp->vtype!=ap->headblock.vtype)
			warn("argument type mismatch in statement function");
		}
	rp->rplnextp = tlist;
	tlist = rp;
	actuals = actuals->nextp;
	formals = formals->nextp;
	++nargs;
	}

if(actuals!=NULL || formals!=NULL)
	err("statement function definition and argument list differ");

/*
   now push down names involved in formal argument list, then
   evaluate rhs of statement function definition in this environment
*/

if(tlist)	/* put tlist in front of the rpllist */
	{
	for(rp = tlist; rp->rplnextp; rp = rp->rplnextp)
		;
	rp->rplnextp = rpllist;
	rpllist = tlist;
	}

q = (expptr) mkconv(type, fixtype(cpexpr(rhs)) );

/* now generate the tree ( t1=a1, (t2=a2,... , f))))) */
while(--nargs >= 0)
	{
	if(rpllist->rplxp)
		q = mkexpr(OPCOMMA, rpllist->rplxp, q);
	rp = rpllist->rplnextp;
	frexpr(rpllist->rplvp);
	free(rpllist);
	rpllist = rp;
	}

ret:
	frchain( &oactp );
	return(q);
}




Addrp mkplace(np)
register Namep np;
{
register Addrp s;
register struct Rplblock *rp;
int regn;

/* is name on the replace list? */

for(rp = rpllist ; rp ; rp = rp->rplnextp)
	{
	if(np == rp->rplnp)
		{
		if(rp->rpltag == TNAME)
			{
			np = (Namep) (rp->rplvp);
			break;
			}
		else	return( (Addrp) cpexpr(rp->rplvp) );
		}
	}

/* is variable a DO index in a register ? */

if(np->vdovar && ( (regn = inregister(np)) >= 0) )
	if(np->vtype == TYERROR)
		return( (Addrp) errnode() );
	else
		{
		s = ALLOC(Addrblock);
		s->tag = TADDR;
		s->vstg = STGREG;
		s->vtype = TYIREG;
		s->issaved = np->vsave;
		s->memno = regn;
		s->memoffset = ICON(0);
		return(s);
		}

vardcl(np);
return(mkaddr(np));
}




expptr mklhs(p)
register struct Primblock *p;
{
expptr suboffset();
I 5
expptr ep = ENULL;
E 5
register Addrp s;
Namep np;

if(p->tag != TPRIM)
	return( (expptr) p );
np = p->namep;

s = mkplace(np);
if(s->tag!=TADDR || s->vstg==STGREG)
	{
	free( (charptr) p );
	return( (expptr) s );
	}

D 5
/* compute the address modified by subscripts */
E 5
I 5
/* do the substring part */
E 5

D 5
s->memoffset = mkexpr(OPPLUS, s->memoffset, suboffset(p) );
frexpr(p->argsp);
p->argsp = NULL;

/* now do substring part */

E 5
if(p->fcharp || p->lcharp)
	{
	if(np->vtype != TYCHAR)
		errstr("substring of noncharacter %s", varstr(VL,np->varname));
	else	{
		if(p->lcharp == NULL)
			p->lcharp = (expptr) cpexpr(s->vleng);
		frexpr(s->vleng);
		if(p->fcharp)
			{
			if(p->fcharp->tag == TPRIM && p->lcharp->tag == TPRIM
D 5
			&& p->fcharp->primblock.namep == p->lcharp->primblock.namep)
E 5
I 5
			&& p->fcharp->primblock.namep == p->lcharp->primblock.namep
			&& p->fcharp->primblock.argsp == NULL
			&& p->lcharp->primblock.argsp == NULL)
E 5
				/* A trivial optimization -- upper == lower */
				s->vleng = ICON(1);
			else
I 5
				{
				if(p->fcharp->tag == TEXPR
				|| (p->fcharp->tag == TPRIM
				   && p->fcharp->primblock.argsp != NULL))
					{
D 6
					ep = fixtype(p->fcharp);
E 6
I 6
					ep = fixtype(cpexpr(p->fcharp));
E 6
					p->fcharp = (expptr) mktemp(ep->headblock.vtype, ENULL);
					}
E 5
				s->vleng = mkexpr(OPMINUS, p->lcharp,
D 6
					mkexpr(OPMINUS, p->fcharp, ICON(1) ));
E 6
I 6
				 mkexpr(OPMINUS, cpexpr(p->fcharp), ICON(1) ));
E 6
I 5
				}
E 5
			}
		else
			s->vleng = p->lcharp;
		}
	}

I 5
/* compute the address modified by subscripts */

s->memoffset = mkexpr(OPPLUS, s->memoffset, suboffset(p) );
frexpr(p->argsp);
p->argsp = NULL;

E 5
s->vleng = fixtype( s->vleng );
s->memoffset = fixtype( s->memoffset );
I 5
if(ep)
	/* this code depends on memoffset being evaluated before vleng */
	s->memoffset = mkexpr(OPCOMMA, mkexpr(OPASSIGN, cpexpr(p->fcharp), ep), s->memoffset);
I 6
frexpr(p->fcharp);
E 6
E 5
free( (charptr) p );
return( (expptr) s );
}





deregister(np)
Namep np;
{
if(nregvar>0 && regnamep[nregvar-1]==np)
	{
	--nregvar;
#if FAMILY == DMR
	putnreg();
#endif
	}
}




Addrp memversion(np)
register Namep np;
{
register Addrp s;

if(np->vdovar==NO || (inregister(np)<0) )
	return(NULL);
np->vdovar = NO;
s = mkplace(np);
np->vdovar = YES;
return(s);
}



inregister(np)
register Namep np;
{
register int i;

for(i = 0 ; i < nregvar ; ++i)
	if(regnamep[i] == np)
		return( regnum[i] );
return(-1);
}




enregister(np)
Namep np;
{
if( inregister(np) >= 0)
	return(YES);
if(nregvar >= maxregvar)
	return(NO);
vardcl(np);
if( ONEOF(np->vtype, MSKIREG) )
	{
	regnamep[nregvar++] = np;
	if(nregvar > highregvar)
		highregvar = nregvar;
#if FAMILY == DMR
	putnreg();
#endif
	return(YES);
	}
else
	return(NO);
}




expptr suboffset(p)
register struct Primblock *p;
{
int n;
expptr size;
expptr oftwo();
chainp cp;
expptr offp, prod;
expptr subcheck();
struct Dimblock *dimp;
expptr sub[MAXDIM+1];
register Namep np;

np = p->namep;
offp = ICON(0);
n = 0;
if(p->argsp)
	for(cp = p->argsp->listp ; cp ; ++n, cp = cp->nextp)
		{
		sub[n] = fixtype(cpexpr(cp->datap));
		if ( ! ISINT(sub[n]->headblock.vtype)) {
			errstr("%s: non-integer subscript expression",
				varstr(VL, np->varname) );
			/* Provide a substitute -- go on to find more errors */
			frexpr(sub[n]);
			sub[n] = ICON(1);
		}
		if(n > maxdim)
			{
			   char str[28+VL];
			   sprintf(str, "%s: more than %d subscripts",
				varstr(VL, np->varname), maxdim );
			   err( str );
			break;
			}
		}

dimp = np->vdim;
if(n>0 && dimp==NULL)
	errstr("%s: subscripts on scalar variable", 
		varstr(VL, np->varname), maxdim );
else if(dimp && dimp->ndim!=n)
	errstr("wrong number of subscripts on %s",
		varstr(VL, np->varname) );
else if(n > 0)
	{
	prod = sub[--n];
	while( --n >= 0)
		prod = mkexpr(OPPLUS, sub[n],
			mkexpr(OPSTAR, prod, cpexpr(dimp->dims[n].dimsize)) );
#if TARGET == VAX
#ifdef SDB
	if(checksubs || np->vstg!=STGARG || sdbflag)
#else
	if(checksubs || np->vstg!=STGARG)
#endif
		prod = mkexpr(OPMINUS, prod, cpexpr(dimp->baseoffset));
#else
	prod = mkexpr(OPMINUS, prod, cpexpr(dimp->baseoffset));
#endif
	if(checksubs)
		prod = subcheck(np, prod);
	size = np->vtype == TYCHAR ?
		(expptr) cpexpr(np->vleng) : ICON(typesize[np->vtype]);
	if (!oftwo(size))
		prod = mkexpr(OPSTAR, prod, size);
	else
		prod = mkexpr(OPLSHIFT,prod,oftwo(size));

	offp = mkexpr(OPPLUS, offp, prod);
	}

if(p->fcharp && np->vtype==TYCHAR)
	offp = mkexpr(OPPLUS, offp, mkexpr(OPMINUS, cpexpr(p->fcharp), ICON(1) ));

return(offp);
}




expptr subcheck(np, p)
Namep np;
register expptr p;
{
struct Dimblock *dimp;
expptr t, checkvar, checkcond, badcall;

dimp = np->vdim;
if(dimp->nelt == NULL)
	return(p);	/* don't check arrays with * bounds */
checkvar = NULL;
checkcond = NULL;
if( ISICON(p) )
	{
D 9
	if(p->constblock.const.ci < 0)
E 9
I 9
	if(p->constblock.constant.ci < 0)
E 9
		goto badsub;
	if( ISICON(dimp->nelt) )
D 9
		if(p->constblock.const.ci < dimp->nelt->constblock.const.ci)
E 9
I 9
		if(p->constblock.constant.ci < dimp->nelt->constblock.constant.ci)
E 9
			return(p);
		else
			goto badsub;
	}
if(p->tag==TADDR && p->addrblock.vstg==STGREG)
	{
	checkvar = (expptr) cpexpr(p);
	t = p;
	}
else	{
	checkvar = (expptr) mktemp(p->headblock.vtype, ENULL);
	t = mkexpr(OPASSIGN, cpexpr(checkvar), p);
	}
checkcond = mkexpr(OPLT, t, cpexpr(dimp->nelt) );
if( ! ISICON(p) )
	checkcond = mkexpr(OPAND, checkcond,
			mkexpr(OPLE, ICON(0), cpexpr(checkvar)) );

badcall = call4(p->headblock.vtype, "s_rnge",
		mkstrcon(VL, np->varname),
		mkconv(TYLONG,  cpexpr(checkvar)),
		mkstrcon(XL, procname),
		ICON(lineno) );
badcall->exprblock.opcode = OPCCALL;
p = mkexpr(OPQUEST, checkcond,
	mkexpr(OPCOLON, checkvar, badcall));

return(p);

badsub:
	frexpr(p);
	errstr("subscript on variable %s out of range", varstr(VL,np->varname));
	return ( ICON(0) );
}




Addrp mkaddr(p)
register Namep p;
{
struct Extsym *extp;
register Addrp t;
Addrp intraddr();

switch( p->vstg)
	{
	case STGUNKNOWN:
		if(p->vclass != CLPROC)
			break;
		extp = mkext( varunder(VL, p->varname) );
		extp->extstg = STGEXT;
		p->vstg = STGEXT;
		p->vardesc.varno = extp - extsymtab;
		p->vprocclass = PEXTERNAL;

	case STGCOMMON:
	case STGEXT:
	case STGBSS:
	case STGINIT:
	case STGEQUIV:
	case STGARG:
	case STGLENG:
	case STGAUTO:
		t = ALLOC(Addrblock);
		t->tag = TADDR;
		if(p->vclass==CLPROC && p->vprocclass==PTHISPROC)
			t->vclass = CLVAR;
		else
			t->vclass = p->vclass;
		t->vtype = p->vtype;
		t->vstg = p->vstg;
		t->memno = p->vardesc.varno;
		t->issaved = p->vsave;
                if(p->vdim) t->isarray = YES;
		t->memoffset = ICON(p->voffset);
		if(p->vleng)
			{
			t->vleng = (expptr) cpexpr(p->vleng);
			if( ISICON(t->vleng) )
D 9
				t->varleng = t->vleng->constblock.const.ci;
E 9
I 9
				t->varleng = t->vleng->constblock.constant.ci;
E 9
			}
		if (p->vstg == STGBSS)
			t->varsize = p->varsize;
		else if (p->vstg == STGEQUIV)
			t->varsize = eqvclass[t->memno].eqvleng;
		return(t);

	case STGINTR:
		return( intraddr(p) );

	}
/*debug*/fprintf(diagfile,"mkaddr. vtype=%d, vclass=%d\n", p->vtype, p->vclass);
badstg("mkaddr", p->vstg);
/* NOTREACHED */
}




Addrp mkarg(type, argno)
int type, argno;
{
register Addrp p;

p = ALLOC(Addrblock);
p->tag = TADDR;
p->vtype = type;
p->vclass = CLVAR;
p->vstg = (type==TYLENG ? STGLENG : STGARG);
p->memno = argno;
return(p);
}




expptr mkprim(v, args, substr)
register union
	{
	struct Paramblock paramblock;
	struct Nameblock nameblock;
	struct Headblock headblock;
	} *v;
struct Listblock *args;
chainp substr;
{
register struct Primblock *p;

if(v->headblock.vclass == CLPARAM)
	{
	if(args || substr)
		{
		errstr("no qualifiers on parameter name %s",
			varstr(VL,v->paramblock.varname));
		frexpr(args);
		if(substr)
			{
			frexpr(substr->datap);
			frexpr(substr->nextp->datap);
			frchain(&substr);
			}
		frexpr(v);
		return( errnode() );
		}
	return( (expptr) cpexpr(v->paramblock.paramval) );
	}

p = ALLOC(Primblock);
p->tag = TPRIM;
p->vtype = v->nameblock.vtype;
p->namep = (Namep) v;
p->argsp = args;
if(substr)
	{
D 2
	p->fcharp = (expptr) (substr->datap);
	p->lcharp = (expptr) (substr->nextp->datap);
E 2
I 2
D 3
	p->fcharp = mkconv(tyint, substr->datap);
	p->lcharp = mkconv(tyint, substr->nextp->datap);
E 3
I 3
	p->fcharp = (expptr) substr->datap;
D 4
	if (p->fcharp != ENULL && ! ISINT(p->fcharp.headblock->vtype))
E 4
I 4
	if (p->fcharp != ENULL && ! ISINT(p->fcharp->headblock.vtype))
E 4
		p->fcharp = mkconv(TYINT, p->fcharp);
	p->lcharp = (expptr) substr->nextp->datap;
D 4
	if (p->lcharp != ENULL && ! ISINT(p->lcharp.headblock->vtype))
E 4
I 4
	if (p->lcharp != ENULL && ! ISINT(p->lcharp->headblock.vtype))
E 4
		p->lcharp = mkconv(TYINT, p->lcharp);
E 3
E 2
	frchain(&substr);
	}
return( (expptr) p);
}



vardcl(v)
register Namep v;
{
int nelt;
struct Dimblock *t;
Addrp p;
expptr neltp;
int eltsize;
int varsize;
int tsize;
int align;

if(v->vdcldone)
	return;
if(v->vclass == CLNAMELIST)
	return;

if(v->vtype == TYUNKNOWN)
	impldcl(v);
if(v->vclass == CLUNKNOWN)
	v->vclass = CLVAR;
else if(v->vclass!=CLVAR && v->vprocclass!=PTHISPROC)
	{
	dclerr("used both as variable and non-variable", v);
	return;
	}
if(v->vstg==STGUNKNOWN)
	v->vstg = implstg[ letter(v->varname[0]) ];

switch(v->vstg)
	{
	case STGBSS:
		v->vardesc.varno = ++lastvarno;
		if (v->vclass != CLVAR)
			break;
		nelt = 1;
		t = v->vdim;
		if (t)
			{
			neltp = t->nelt;
			if (neltp && ISICON(neltp))
D 9
				nelt = neltp->constblock.const.ci;
E 9
I 9
				nelt = neltp->constblock.constant.ci;
E 9
			else
				dclerr("improperly dimensioned array", v);
			}

		if (v->vtype == TYCHAR)
			{
			v->vleng = fixtype(v->vleng);
			if (v->vleng == NULL)
				eltsize = typesize[TYCHAR];
			else if (ISICON(v->vleng))
				eltsize = typesize[TYCHAR] *
D 9
					v->vleng->constblock.const.ci;
E 9
I 9
					v->vleng->constblock.constant.ci;
E 9
			else if (v->vleng->tag != TERROR)
				{
				errstr("nonconstant string length on %s",
					varstr(VL, v->varname));
				eltsize = 0;
				}
			}
		else
			eltsize = typesize[v->vtype];

		v->varsize = nelt * eltsize;
		break;
	case STGAUTO:
		if(v->vclass==CLPROC && v->vprocclass==PTHISPROC)
			break;
		nelt = 1;
		if(t = v->vdim)
			if( (neltp = t->nelt) && ISCONST(neltp) )
D 9
				nelt = neltp->constblock.const.ci;
E 9
I 9
				nelt = neltp->constblock.constant.ci;
E 9
			else
				dclerr("adjustable automatic array", v);
		p = autovar(nelt, v->vtype, v->vleng);
		v->vardesc.varno = p->memno;
D 9
		v->voffset = p->memoffset->constblock.const.ci;
E 9
I 9
		v->voffset = p->memoffset->constblock.constant.ci;
E 9
		frexpr(p);
		break;

	default:
		break;
	}
v->vdcldone = YES;
}




impldcl(p)
register Namep p;
{
register int k;
int type, leng;

if(p->vdcldone || (p->vclass==CLPROC && p->vprocclass==PINTRINSIC) )
	return;
if(p->vtype == TYUNKNOWN)
	{
	k = letter(p->varname[0]);
	type = impltype[ k ];
	leng = implleng[ k ];
	if(type == TYUNKNOWN)
		{
		if(p->vclass == CLPROC)
D 2
			return;
		dclerr("attempt to use undefined variable", p);
E 2
I 2
			dclerr("attempt to use function of undefined type", p);
		else
			dclerr("attempt to use undefined variable", p);
E 2
		type = TYERROR;
		leng = 1;
		}
	settype(p, type, leng);
	}
}




LOCAL letter(c)
register int c;
{
if( isupper(c) )
	c = tolower(c);
return(c - 'a');
}

D 9
#define ICONEQ(z, c)  (ISICON(z) && z->constblock.const.ci==c)
E 9
I 9
#define ICONEQ(z, c)  (ISICON(z) && z->constblock.constant.ci==c)
E 9
#define COMMUTE	{ e = lp;  lp = rp;  rp = e; }


expptr mkexpr(opcode, lp, rp)
int opcode;
register expptr lp, rp;
{
register expptr e, e1;
int etype;
int ltype, rtype;
int ltag, rtag;
expptr q, q1;
expptr fold();
int k;

ltype = lp->headblock.vtype;
ltag = lp->tag;
if(rp && opcode!=OPCALL && opcode!=OPCCALL)
	{
	rtype = rp->headblock.vtype;
	rtag = rp->tag;
	}
else	{
	rtype = 0;
	rtag = 0;
	}

/*
 * Yuck.  Why can't we fold constants AFTER
 * variables are implicitly declared???
 */
if(ltype == TYUNKNOWN && ltag == TPRIM && lp->primblock.argsp == NULL)
	{
	k = letter(lp->primblock.namep->varname[0]);
	ltype = impltype[ k ];
	}
if(rtype == TYUNKNOWN && rtag == TPRIM && rp->primblock.argsp == NULL)
	{
	k = letter(rp->primblock.namep->varname[0]);
	rtype = impltype[ k ];
	}

I 5
/*
 * Eliminate all but the topmost OPPAREN operator when folding constants.
 */
if(lp->tag == TEXPR &&
   lp->exprblock.opcode == OPPAREN &&
   lp->exprblock.leftp->tag == TCONST)
	{
	q = (expptr) cpexpr(lp->exprblock.leftp);
	frexpr(lp);
	lp = q;
	ltag = TCONST;
	ltype = lp->constblock.vtype;
	}
if(rp &&
   rp->tag == TEXPR &&
   rp->exprblock.opcode == OPPAREN &&
   rp->exprblock.leftp->tag == TCONST)
	{
	q = (expptr) cpexpr(rp->exprblock.leftp);
	frexpr(rp);
	rp = q;
	rtag = TCONST;
	rtype = rp->constblock.vtype;
	}

E 5
etype = cktype(opcode, ltype, rtype);
if(etype == TYERROR)
	goto error;

D 5
if(etype != TYUNKNOWN)
E 5
I 5
if(ltag==TCONST && (rp==0 || rtag==TCONST) )
	goto makenode;
if(etype == TYUNKNOWN)
	goto makenode;

E 5
switch(opcode)
	{
	/* check for multiplication by 0 and 1 and addition to 0 */

	case OPSTAR:
		if( ISCONST(lp) )
			COMMUTE

		if( ISICON(rp) )
			{
D 9
			if(rp->constblock.const.ci == 0)
E 9
I 9
			if(rp->constblock.constant.ci == 0)
E 9
				{
				if(etype == TYUNKNOWN)
					break;
				rp = mkconv(etype, rp);
				goto retright;
				}
			if ((lp->tag == TEXPR) &&
			    ((lp->exprblock.opcode == OPPLUS) ||
			     (lp->exprblock.opcode == OPMINUS)) &&
			    ISCONST(lp->exprblock.rightp) &&
			    ISINT(lp->exprblock.rightp->constblock.vtype))
				{
				q1 = mkexpr(OPSTAR, lp->exprblock.rightp,
					   cpexpr(rp));
				q = mkexpr(OPSTAR, lp->exprblock.leftp, rp);
				q = mkexpr(lp->exprblock.opcode, q, q1);
				free ((char *) lp);
				return q;
				}
			else
				goto mulop;
			}
		break;

	case OPSLASH:
	case OPMOD:
		if( ICONEQ(rp, 0) )
			{
			err("attempted division by zero");
			rp = ICON(1);
			break;
			}
		if(opcode == OPMOD)
			break;


	mulop:
		if( ISICON(rp) )
			{
D 9
			if(rp->constblock.const.ci == 1)
E 9
I 9
			if(rp->constblock.constant.ci == 1)
E 9
				goto retleft;

D 9
			if(rp->constblock.const.ci == -1)
E 9
I 9
			if(rp->constblock.constant.ci == -1)
E 9
				{
				frexpr(rp);
				return( mkexpr(OPNEG, lp, PNULL) );
				}
			}

		if( ISSTAROP(lp) && ISICON(lp->exprblock.rightp) )
			{
			if(opcode == OPSTAR)
				e = mkexpr(OPSTAR, lp->exprblock.rightp, rp);
			else  if(ISICON(rp) &&
D 9
				(lp->exprblock.rightp->constblock.const.ci %
					rp->constblock.const.ci) == 0)
E 9
I 9
				(lp->exprblock.rightp->constblock.constant.ci %
					rp->constblock.constant.ci) == 0)
E 9
				e = mkexpr(OPSLASH, lp->exprblock.rightp, rp);
			else	break;

			e1 = lp->exprblock.leftp;
			free( (charptr) lp );
			return( mkexpr(OPSTAR, e1, e) );
			}
		break;


	case OPPLUS:
		if( ISCONST(lp) )
			COMMUTE
		goto addop;

	case OPMINUS:
		if( ICONEQ(lp, 0) )
			{
			frexpr(lp);
			return( mkexpr(OPNEG, rp, ENULL) );
			}

		if( ISCONST(rp) )
			{
			opcode = OPPLUS;
			consnegop(rp);
			}

	addop:
		if( ISICON(rp) )
			{
D 9
			if(rp->constblock.const.ci == 0)
E 9
I 9
			if(rp->constblock.constant.ci == 0)
E 9
				goto retleft;
			if( ISPLUSOP(lp) && ISICON(lp->exprblock.rightp) )
				{
				e = mkexpr(OPPLUS, lp->exprblock.rightp, rp);
				e1 = lp->exprblock.leftp;
				free( (charptr) lp );
				return( mkexpr(OPPLUS, e1, e) );
				}
			}
		break;


	case OPPOWER:
		break;

	case OPNEG:
		if(ltag==TEXPR && lp->exprblock.opcode==OPNEG)
			{
			e = lp->exprblock.leftp;
			free( (charptr) lp );
			return(e);
			}
		break;

	case OPNOT:
		if(ltag==TEXPR && lp->exprblock.opcode==OPNOT)
			{
			e = lp->exprblock.leftp;
			free( (charptr) lp );
			return(e);
			}
		break;

	case OPCALL:
	case OPCCALL:
		etype = ltype;
		if(rp!=NULL && rp->listblock.listp==NULL)
			{
			free( (charptr) rp );
			rp = NULL;
			}
		break;

	case OPAND:
	case OPOR:
		if( ISCONST(lp) )
			COMMUTE

		if( ISCONST(rp) )
			{
D 9
			if(rp->constblock.const.ci == 0)
E 9
I 9
			if(rp->constblock.constant.ci == 0)
E 9
				if(opcode == OPOR)
					goto retleft;
				else
					goto retright;
			else if(opcode == OPOR)
				goto retright;
			else
				goto retleft;
			}
	case OPLSHIFT:
		if (ISICON(rp))
			{
D 9
			if (rp->constblock.const.ci == 0)
E 9
I 9
			if (rp->constblock.constant.ci == 0)
E 9
				goto retleft;
			if ((lp->tag == TEXPR) &&
			    ((lp->exprblock.opcode == OPPLUS) ||
			     (lp->exprblock.opcode == OPMINUS)) &&
			    ISICON(lp->exprblock.rightp))
				{
				q1 = mkexpr(OPLSHIFT, lp->exprblock.rightp,
					cpexpr(rp));
				q = mkexpr(OPLSHIFT, lp->exprblock.leftp, rp);
				q = mkexpr(lp->exprblock.opcode, q, q1);
				free((char *) lp);
				return q;
				}
			}

	case OPEQV:
	case OPNEQV:

	case OPBITAND:
	case OPBITOR:
	case OPBITXOR:
	case OPBITNOT:
	case OPRSHIFT:

	case OPLT:
	case OPGT:
	case OPLE:
	case OPGE:
I 8
		break;

E 8
	case OPEQ:
	case OPNE:
I 8
		/*
		 * This warning is here instead of in cktype because
		 * cktype repeats warnings (it can be run more
		 * than once on an expression).
		 */
		if (ltype == TYLOGICAL)
			warn("logical operand of nonlogical operator");
		break;
E 8

	case OPCONCAT:
D 8
		break;
E 8
I 8

E 8
	case OPMIN:
	case OPMAX:

	case OPASSIGN:
	case OPPLUSEQ:
	case OPSTAREQ:

	case OPCONV:
	case OPADDR:

	case OPCOMMA:
	case OPQUEST:
	case OPCOLON:

	case OPPAREN:
		break;

	default:
		badop("mkexpr", opcode);
	}

I 5
makenode:

E 5
e = (expptr) ALLOC(Exprblock);
e->exprblock.tag = TEXPR;
e->exprblock.opcode = opcode;
e->exprblock.vtype = etype;
e->exprblock.leftp = lp;
e->exprblock.rightp = rp;
if(ltag==TCONST && (rp==0 || rtag==TCONST) )
	e = fold(e);
return(e);

retleft:
	frexpr(rp);
	return(lp);

retright:
	frexpr(lp);
	return(rp);

error:
	frexpr(lp);
	if(rp && opcode!=OPCALL && opcode!=OPCCALL)
		frexpr(rp);
	return( errnode() );
}

#define ERR(s)   { errs = s; goto error; }

cktype(op, lt, rt)
register int op, lt, rt;
{
char *errs;

if(lt==TYERROR || rt==TYERROR)
	goto error1;

if(lt==TYUNKNOWN)
	return(TYUNKNOWN);
if(rt==TYUNKNOWN)
	if (op!=OPNOT && op!=OPBITNOT && op!=OPNEG && op!=OPCALL &&
	    op!=OPCCALL && op!=OPADDR && op!=OPPAREN)
		return(TYUNKNOWN);

switch(op)
	{
	case OPPLUS:
	case OPMINUS:
	case OPSTAR:
	case OPSLASH:
	case OPPOWER:
	case OPMOD:
		if( ISNUMERIC(lt) && ISNUMERIC(rt) )
			return( maxtype(lt, rt) );
		ERR("nonarithmetic operand of arithmetic operator")

	case OPNEG:
		if( ISNUMERIC(lt) )
			return(lt);
		ERR("nonarithmetic operand of negation")

	case OPNOT:
		if(lt == TYLOGICAL)
			return(TYLOGICAL);
		ERR("NOT of nonlogical")

	case OPAND:
	case OPOR:
	case OPEQV:
	case OPNEQV:
		if(lt==TYLOGICAL && rt==TYLOGICAL)
			return(TYLOGICAL);
		ERR("nonlogical operand of logical operator")

	case OPLT:
	case OPGT:
	case OPLE:
	case OPGE:
	case OPEQ:
	case OPNE:
		if(lt==TYCHAR || rt==TYCHAR || lt==TYLOGICAL || rt==TYLOGICAL)
			{
			if(lt != rt)
				ERR("illegal comparison")
I 8
			if(lt == TYLOGICAL)
				{
				if(op!=OPEQ && op!=OPNE)
					ERR("order comparison of complex data")
				}
E 8
			}

		else if( ISCOMPLEX(lt) || ISCOMPLEX(rt) )
			{
			if(op!=OPEQ && op!=OPNE)
				ERR("order comparison of complex data")
			}

		else if( ! ISNUMERIC(lt) || ! ISNUMERIC(rt) )
			ERR("comparison of nonarithmetic data")
		return(TYLOGICAL);

	case OPCONCAT:
		if(lt==TYCHAR && rt==TYCHAR)
			return(TYCHAR);
		ERR("concatenation of nonchar data")

	case OPCALL:
	case OPCCALL:
		return(lt);

	case OPADDR:
		return(TYADDR);

	case OPCONV:
		if(ISCOMPLEX(lt))
			{
			if(ISNUMERIC(rt))
				return(lt);
			ERR("impossible conversion")
			}
		if(rt == 0)
			return(0);
		if(lt==TYCHAR && ISINT(rt) )
			return(TYCHAR);
	case OPASSIGN:
	case OPPLUSEQ:
	case OPSTAREQ:
		if( ISINT(lt) && rt==TYCHAR)
			return(lt);
		if(lt==TYCHAR || rt==TYCHAR || lt==TYLOGICAL || rt==TYLOGICAL)
			if(op!=OPASSIGN || lt!=rt)
				{
/* debug fprintf(diagfile, " lt=%d, rt=%d, op=%d\n", lt, rt, op); */
/* debug fatal("impossible conversion.  possible compiler bug"); */
				ERR("impossible conversion")
				}
		return(lt);

	case OPMIN:
	case OPMAX:
	case OPBITOR:
	case OPBITAND:
	case OPBITXOR:
	case OPBITNOT:
	case OPLSHIFT:
	case OPRSHIFT:
	case OPPAREN:
		return(lt);

	case OPCOMMA:
	case OPQUEST:
	case OPCOLON:
		return(rt);

	default:
		badop("cktype", op);
	}
error:	err(errs);
error1:	return(TYERROR);
}

I 5
#if HERE == VAX
#include <signal.h>
#include <setjmp.h>
#define	setfpe()	;asm("bispsw	$0x60")
jmp_buf jmp_fpe;

LOCAL int fold_fpe_handler( sig, code )
int sig;
int code;
{
char		*message;

switch ( code )
	{
	case FPE_INTOVF_TRAP:
		message = "integer overflow"; break;
	case FPE_INTDIV_TRAP:
		message = "integer divide by zero"; break;
	case FPE_FLTOVF_TRAP:
	case FPE_FLTOVF_FAULT:
		message = "floating overflow"; break;
	case FPE_FLTDIV_TRAP:
	case FPE_FLTDIV_FAULT:
		message = "floating divide by zero"; break;
	case FPE_FLTUND_TRAP:
	case FPE_FLTUND_FAULT:
		message = "floating underflow"; break;
	default:
		message		= "arithmetic exception";
	}
errstr("%s in constant expression", message);
longjmp(jmp_fpe, 1);
}
#endif

#ifndef setfpe
#define	setfpe()
#endif

E 5
LOCAL expptr fold(e)
register expptr e;
{
Constp p;
register expptr lp, rp;
int etype, mtype, ltype, rtype, opcode;
int i, ll, lr;
char *q, *s;
union Constant lcon, rcon;

I 5
#if HERE == VAX
int (*fpe_handler)();

if(setjmp(jmp_fpe))
	{
	(void) signal(SIGFPE, fpe_handler);
	frexpr(e);
	return(errnode());
	}
fpe_handler = signal(SIGFPE, fold_fpe_handler);
setfpe();
#endif

E 5
opcode = e->exprblock.opcode;
etype = e->exprblock.vtype;

lp = e->exprblock.leftp;
ltype = lp->headblock.vtype;
rp = e->exprblock.rightp;

if(rp == 0)
	switch(opcode)
		{
		case OPNOT:
D 9
			lp->constblock.const.ci = ! lp->constblock.const.ci;
E 9
I 9
			lp->constblock.constant.ci = ! lp->constblock.constant.ci;
E 9
			return(lp);

		case OPBITNOT:
D 9
			lp->constblock.const.ci = ~ lp->constblock.const.ci;
E 9
I 9
			lp->constblock.constant.ci = ~ lp->constblock.constant.ci;
E 9
			return(lp);

		case OPNEG:
			consnegop(lp);
			return(lp);

		case OPCONV:
		case OPADDR:
		case OPPAREN:
			return(e);

		default:
			badop("fold", opcode);
		}

rtype = rp->headblock.vtype;

p = ALLOC(Constblock);
p->tag = TCONST;
p->vtype = etype;
p->vleng = e->exprblock.vleng;

switch(opcode)
	{
	case OPCOMMA:
	case OPQUEST:
	case OPCOLON:
		return(e);

	case OPAND:
D 9
		p->const.ci = lp->constblock.const.ci &&
				rp->constblock.const.ci;
E 9
I 9
		p->constant.ci = lp->constblock.constant.ci &&
				rp->constblock.constant.ci;
E 9
		break;

	case OPOR:
D 9
		p->const.ci = lp->constblock.const.ci ||
				rp->constblock.const.ci;
E 9
I 9
		p->constant.ci = lp->constblock.constant.ci ||
				rp->constblock.constant.ci;
E 9
		break;

	case OPEQV:
D 9
		p->const.ci = lp->constblock.const.ci ==
				rp->constblock.const.ci;
E 9
I 9
		p->constant.ci = lp->constblock.constant.ci ==
				rp->constblock.constant.ci;
E 9
		break;

	case OPNEQV:
D 9
		p->const.ci = lp->constblock.const.ci !=
				rp->constblock.const.ci;
E 9
I 9
		p->constant.ci = lp->constblock.constant.ci !=
				rp->constblock.constant.ci;
E 9
		break;

	case OPBITAND:
D 9
		p->const.ci = lp->constblock.const.ci &
				rp->constblock.const.ci;
E 9
I 9
		p->constant.ci = lp->constblock.constant.ci &
				rp->constblock.constant.ci;
E 9
		break;

	case OPBITOR:
D 9
		p->const.ci = lp->constblock.const.ci |
				rp->constblock.const.ci;
E 9
I 9
		p->constant.ci = lp->constblock.constant.ci |
				rp->constblock.constant.ci;
E 9
		break;

	case OPBITXOR:
D 9
		p->const.ci = lp->constblock.const.ci ^
				rp->constblock.const.ci;
E 9
I 9
		p->constant.ci = lp->constblock.constant.ci ^
				rp->constblock.constant.ci;
E 9
		break;

	case OPLSHIFT:
D 9
		p->const.ci = lp->constblock.const.ci <<
				rp->constblock.const.ci;
E 9
I 9
		p->constant.ci = lp->constblock.constant.ci <<
				rp->constblock.constant.ci;
E 9
		break;

	case OPRSHIFT:
D 9
		p->const.ci = lp->constblock.const.ci >>
				rp->constblock.const.ci;
E 9
I 9
		p->constant.ci = lp->constblock.constant.ci >>
				rp->constblock.constant.ci;
E 9
		break;

	case OPCONCAT:
D 9
		ll = lp->constblock.vleng->constblock.const.ci;
		lr = rp->constblock.vleng->constblock.const.ci;
		p->const.ccp = q = (char *) ckalloc(ll+lr);
E 9
I 9
		ll = lp->constblock.vleng->constblock.constant.ci;
		lr = rp->constblock.vleng->constblock.constant.ci;
		p->constant.ccp = q = (char *) ckalloc(ll+lr);
E 9
		p->vleng = ICON(ll+lr);
D 9
		s = lp->constblock.const.ccp;
E 9
I 9
		s = lp->constblock.constant.ccp;
E 9
		for(i = 0 ; i < ll ; ++i)
			*q++ = *s++;
D 9
		s = rp->constblock.const.ccp;
E 9
I 9
		s = rp->constblock.constant.ccp;
E 9
		for(i = 0; i < lr; ++i)
			*q++ = *s++;
		break;


	case OPPOWER:
		if( ! ISINT(rtype) )
			return(e);
D 9
		conspower(&(p->const), lp, rp->constblock.const.ci);
E 9
I 9
		conspower(&(p->constant), lp, rp->constblock.constant.ci);
E 9
		break;


	default:
		if(ltype == TYCHAR)
			{
D 9
			lcon.ci = cmpstr(lp->constblock.const.ccp,
					rp->constblock.const.ccp,
					lp->constblock.vleng->constblock.const.ci,
					rp->constblock.vleng->constblock.const.ci);
E 9
I 9
			lcon.ci = cmpstr(lp->constblock.constant.ccp,
					rp->constblock.constant.ccp,
					lp->constblock.vleng->constblock.constant.ci,
					rp->constblock.vleng->constblock.constant.ci);
E 9
			rcon.ci = 0;
			mtype = tyint;
			}
		else	{
			mtype = maxtype(ltype, rtype);
D 9
			consconv(mtype, &lcon, ltype, &(lp->constblock.const) );
			consconv(mtype, &rcon, rtype, &(rp->constblock.const) );
E 9
I 9
			consconv(mtype, &lcon, ltype, &(lp->constblock.constant) );
			consconv(mtype, &rcon, rtype, &(rp->constblock.constant) );
E 9
			}
D 9
		consbinop(opcode, mtype, &(p->const), &lcon, &rcon);
E 9
I 9
		consbinop(opcode, mtype, &(p->constant), &lcon, &rcon);
E 9
		break;
	}

frexpr(e);
return( (expptr) p );
}



/* assign constant l = r , doing coercion */

consconv(lt, lv, rt, rv)
int lt, rt;
register union Constant *lv, *rv;
{
switch(lt)
	{
	case TYCHAR:
		*(lv->ccp = (char *) ckalloc(1)) = rv->ci;
		break;

	case TYSHORT:
	case TYLONG:
		if(rt == TYCHAR)
			lv->ci = rv->ccp[0];
		else if( ISINT(rt) )
			lv->ci = rv->ci;
		else	lv->ci = rv->cd[0];
		break;

	case TYCOMPLEX:
	case TYDCOMPLEX:
		switch(rt)
			{
			case TYSHORT:
			case TYLONG:
				/* fall through and do real assignment of
				   first element
				*/
			case TYREAL:
			case TYDREAL:
				lv->cd[1] = 0; break;
			case TYCOMPLEX:
			case TYDCOMPLEX:
				lv->cd[1] = rv->cd[1]; break;
			}

	case TYREAL:
	case TYDREAL:
		if( ISINT(rt) )
			lv->cd[0] = rv->ci;
		else	lv->cd[0] = rv->cd[0];
		if( lt == TYREAL)
			{
			float f = lv->cd[0];
			lv->cd[0] = f;
			}
		break;

	case TYLOGICAL:
		lv->ci = rv->ci;
		break;
	}
}



consnegop(p)
register Constp p;
{
I 5
setfpe();

E 5
switch(p->vtype)
	{
	case TYSHORT:
	case TYLONG:
D 9
		p->const.ci = - p->const.ci;
E 9
I 9
		p->constant.ci = - p->constant.ci;
E 9
		break;

	case TYCOMPLEX:
	case TYDCOMPLEX:
D 9
		p->const.cd[1] = - p->const.cd[1];
E 9
I 9
		p->constant.cd[1] = - p->constant.cd[1];
E 9
		/* fall through and do the real parts */
	case TYREAL:
	case TYDREAL:
D 9
		p->const.cd[0] = - p->const.cd[0];
E 9
I 9
		p->constant.cd[0] = - p->constant.cd[0];
E 9
		break;
	default:
		badtype("consnegop", p->vtype);
	}
}



LOCAL conspower(powp, ap, n)
register union Constant *powp;
Constp ap;
ftnint n;
{
register int type;
union Constant x;

switch(type = ap->vtype)	/* pow = 1 */ 
	{
	case TYSHORT:
	case TYLONG:
		powp->ci = 1;
		break;
	case TYCOMPLEX:
	case TYDCOMPLEX:
		powp->cd[1] = 0;
	case TYREAL:
	case TYDREAL:
		powp->cd[0] = 1;
		break;
	default:
		badtype("conspower", type);
	}

if(n == 0)
	return;
if(n < 0)
	{
	if( ISINT(type) )
		{
D 9
		if (ap->const.ci == 0)
E 9
I 9
		if (ap->constant.ci == 0)
E 9
			err("zero raised to a negative power");
D 9
		else if (ap->const.ci == 1)
E 9
I 9
		else if (ap->constant.ci == 1)
E 9
			return;
D 9
		else if (ap->const.ci == -1)
E 9
I 9
		else if (ap->constant.ci == -1)
E 9
			{
			if (n < -2)
				n = n + 2;
			n = -n;
			if (n % 2 == 1)
				powp->ci = -1;
			}
		else
			powp->ci = 0;
		return;
		}
	n = - n;
D 9
	consbinop(OPSLASH, type, &x, powp, &(ap->const));
E 9
I 9
	consbinop(OPSLASH, type, &x, powp, &(ap->constant));
E 9
	}
else
D 9
	consbinop(OPSTAR, type, &x, powp, &(ap->const));
E 9
I 9
	consbinop(OPSTAR, type, &x, powp, &(ap->constant));
E 9

for( ; ; )
	{
	if(n & 01)
		consbinop(OPSTAR, type, powp, powp, &x);
	if(n >>= 1)
		consbinop(OPSTAR, type, &x, &x, &x);
	else
		break;
	}
}



/* do constant operation cp = a op b */


LOCAL consbinop(opcode, type, cp, ap, bp)
int opcode, type;
register union Constant *ap, *bp, *cp;
{
int k;
double temp;

I 5
setfpe();

E 5
switch(opcode)
	{
	case OPPLUS:
		switch(type)
			{
			case TYSHORT:
			case TYLONG:
				cp->ci = ap->ci + bp->ci;
				break;
			case TYCOMPLEX:
			case TYDCOMPLEX:
				cp->cd[1] = ap->cd[1] + bp->cd[1];
			case TYREAL:
			case TYDREAL:
				cp->cd[0] = ap->cd[0] + bp->cd[0];
				break;
			}
		break;

	case OPMINUS:
		switch(type)
			{
			case TYSHORT:
			case TYLONG:
				cp->ci = ap->ci - bp->ci;
				break;
			case TYCOMPLEX:
			case TYDCOMPLEX:
				cp->cd[1] = ap->cd[1] - bp->cd[1];
			case TYREAL:
			case TYDREAL:
				cp->cd[0] = ap->cd[0] - bp->cd[0];
				break;
			}
		break;

	case OPSTAR:
		switch(type)
			{
			case TYSHORT:
			case TYLONG:
				cp->ci = ap->ci * bp->ci;
				break;
			case TYREAL:
			case TYDREAL:
				cp->cd[0] = ap->cd[0] * bp->cd[0];
				break;
			case TYCOMPLEX:
			case TYDCOMPLEX:
				temp = ap->cd[0] * bp->cd[0] -
					    ap->cd[1] * bp->cd[1] ;
				cp->cd[1] = ap->cd[0] * bp->cd[1] +
					    ap->cd[1] * bp->cd[0] ;
				cp->cd[0] = temp;
				break;
			}
		break;
	case OPSLASH:
		switch(type)
			{
			case TYSHORT:
			case TYLONG:
				cp->ci = ap->ci / bp->ci;
				break;
			case TYREAL:
			case TYDREAL:
				cp->cd[0] = ap->cd[0] / bp->cd[0];
				break;
			case TYCOMPLEX:
			case TYDCOMPLEX:
				zdiv(cp,ap,bp);
				break;
			}
		break;

	case OPMOD:
		if( ISINT(type) )
			{
			cp->ci = ap->ci % bp->ci;
			break;
			}
		else
			fatal("inline mod of noninteger");

	default:	  /* relational ops */
		switch(type)
			{
			case TYSHORT:
			case TYLONG:
				if(ap->ci < bp->ci)
					k = -1;
				else if(ap->ci == bp->ci)
					k = 0;
				else	k = 1;
				break;
			case TYREAL:
			case TYDREAL:
				if(ap->cd[0] < bp->cd[0])
					k = -1;
				else if(ap->cd[0] == bp->cd[0])
					k = 0;
				else	k = 1;
				break;
			case TYCOMPLEX:
			case TYDCOMPLEX:
				if(ap->cd[0] == bp->cd[0] &&
				   ap->cd[1] == bp->cd[1] )
I 7
					k = 0;
				else	k = 1;
				break;
			case TYLOGICAL:
				if(ap->ci == bp->ci)
E 7
					k = 0;
				else	k = 1;
				break;
			}

		switch(opcode)
			{
			case OPEQ:
				cp->ci = (k == 0);
				break;
			case OPNE:
				cp->ci = (k != 0);
				break;
			case OPGT:
				cp->ci = (k == 1);
				break;
			case OPLT:
				cp->ci = (k == -1);
				break;
			case OPGE:
				cp->ci = (k >= 0);
				break;
			case OPLE:
				cp->ci = (k <= 0);
				break;
			default:
				badop ("consbinop", opcode);
			}
		break;
	}
}




conssgn(p)
register expptr p;
{
if( ! ISCONST(p) )
	fatal( "sgn(nonconstant)" );

switch(p->headblock.vtype)
	{
	case TYSHORT:
	case TYLONG:
D 9
		if(p->constblock.const.ci > 0) return(1);
		if(p->constblock.const.ci < 0) return(-1);
E 9
I 9
		if(p->constblock.constant.ci > 0) return(1);
		if(p->constblock.constant.ci < 0) return(-1);
E 9
		return(0);

	case TYREAL:
	case TYDREAL:
D 9
		if(p->constblock.const.cd[0] > 0) return(1);
		if(p->constblock.const.cd[0] < 0) return(-1);
E 9
I 9
		if(p->constblock.constant.cd[0] > 0) return(1);
		if(p->constblock.constant.cd[0] < 0) return(-1);
E 9
		return(0);

	case TYCOMPLEX:
	case TYDCOMPLEX:
D 9
		return(p->constblock.const.cd[0]!=0 || p->constblock.const.cd[1]!=0);
E 9
I 9
		return(p->constblock.constant.cd[0]!=0 || p->constblock.constant.cd[1]!=0);
E 9

	default:
		badtype( "conssgn", p->constblock.vtype);
	}
/* NOTREACHED */
}

char *powint[ ] = { "pow_ii", "pow_ri", "pow_di", "pow_ci", "pow_zi" };


LOCAL expptr mkpower(p)
register expptr p;
{
register expptr q, lp, rp;
int ltype, rtype, mtype;
I 4
struct Listblock *args, *mklist();
Addrp ap;
E 4

lp = p->exprblock.leftp;
rp = p->exprblock.rightp;
ltype = lp->headblock.vtype;
rtype = rp->headblock.vtype;

if(ISICON(rp))
	{
D 9
	if(rp->constblock.const.ci == 0)
E 9
I 9
	if(rp->constblock.constant.ci == 0)
E 9
		{
		frexpr(p);
		if( ISINT(ltype) )
			return( ICON(1) );
		else
			{
			expptr pp;
			pp = mkconv(ltype, ICON(1));
			return( pp );
			}
		}
D 9
	if(rp->constblock.const.ci < 0)
E 9
I 9
	if(rp->constblock.constant.ci < 0)
E 9
		{
		if( ISINT(ltype) )
			{
			frexpr(p);
			err("integer**negative");
			return( errnode() );
			}
D 9
		rp->constblock.const.ci = - rp->constblock.const.ci;
E 9
I 9
		rp->constblock.constant.ci = - rp->constblock.constant.ci;
E 9
		p->exprblock.leftp = lp = fixexpr(mkexpr(OPSLASH, ICON(1), lp));
		}
D 9
	if(rp->constblock.const.ci == 1)
E 9
I 9
	if(rp->constblock.constant.ci == 1)
E 9
		{
		frexpr(rp);
		free( (charptr) p );
		return(lp);
		}

	if( ONEOF(ltype, MSKINT|MSKREAL) )
		{
		p->exprblock.vtype = ltype;
		return(p);
		}
	}
if( ISINT(rtype) )
	{
	if(ltype==TYSHORT && rtype==TYSHORT && (!ISCONST(lp) || tyint==TYSHORT) )
		q = call2(TYSHORT, "pow_hh", lp, rp);
	else	{
		if(ltype == TYSHORT)
			{
			ltype = TYLONG;
			lp = mkconv(TYLONG,lp);
			}
		q = call2(ltype, powint[ltype-TYLONG], lp, mkconv(TYLONG, rp));
		}
	}
else if( ISREAL( (mtype = maxtype(ltype,rtype)) ))
D 4
	q = call2(mtype, "pow_dd", mkconv(TYDREAL,lp), mkconv(TYDREAL,rp));
E 4
I 4
	{
	args = mklist( mkchain( mkconv(TYDREAL,lp), mkchain( mkconv(TYDREAL,rp), CHNULL ) ) );
	fixargs(YES, args );
	ap = builtin( TYDREAL, "pow" );
	ap->vstg = STGINTR;
	q = fixexpr( mkexpr(OPCCALL, ap, args ));
	q->exprblock.vtype = mtype;
	}
E 4
else	{
	q  = call2(TYDCOMPLEX, "pow_zz",
		mkconv(TYDCOMPLEX,lp), mkconv(TYDCOMPLEX,rp));
	if(mtype == TYCOMPLEX)
		q = mkconv(TYCOMPLEX, q);
	}
free( (charptr) p );
return(q);
}



/* Complex Division.  Same code as in Runtime Library
*/

struct dcomplex { double dreal, dimag; };


LOCAL zdiv(c, a, b)
register struct dcomplex *a, *b, *c;
{
double ratio, den;
double abr, abi;
I 5

setfpe();
E 5

if( (abr = b->dreal) < 0.)
	abr = - abr;
if( (abi = b->dimag) < 0.)
	abi = - abi;
if( abr <= abi )
	{
	if(abi == 0)
		fatal("complex division by zero");
	ratio = b->dreal / b->dimag ;
	den = b->dimag * (1 + ratio*ratio);
	c->dreal = (a->dreal*ratio + a->dimag) / den;
	c->dimag = (a->dimag*ratio - a->dreal) / den;
	}

else
	{
	ratio = b->dimag / b->dreal ;
	den = b->dreal * (1 + ratio*ratio);
	c->dreal = (a->dreal + a->dimag*ratio) / den;
	c->dimag = (a->dimag - a->dreal*ratio) / den;
	}

}

expptr oftwo(e)
expptr e;
{
	int val,res;

	if (! ISCONST (e))
		return (0);

D 9
	val = e->constblock.const.ci;
E 9
I 9
	val = e->constblock.constant.ci;
E 9
	switch (val)
		{
		case 2:		res = 1; break;
		case 4:		res = 2; break;
		case 8:		res = 3; break;
		case 16:	res = 4; break;
		case 32:	res = 5; break;
		case 64:	res = 6; break;
		case 128:	res = 7; break;
		case 256:	res = 8; break;
		default:	return (0);
		}
	return (ICON (res));
}
E 1
