/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char sccsid[] = "@(#)put.c	5.3 (Berkeley) 4/12/91";
#endif /* not lint */

/*
 * put.c
 *
 * Intermediate code generation procedures common to both
 * Johnson (Portable) and Ritchie families of second passes
 *
 * University of Utah CS Dept modification history:
 *
 * $Log:	put.c,v $
 * Revision 3.2  85/05/04  15:41:24  mckusick
 * Fix alignment problem -- change code to match comment...
 * 
 * Revision 3.2  85/04/29  21:36:07  donn
 * Fix alignment problem -- change code to match comment...
 * 
 * Revision 3.1  85/02/27  19:12:04  donn
 * Changed to use pcc.h instead of pccdefs.h.
 * 
 * Revision 2.1  84/07/19  12:04:21  donn
 * Changed comment headers for UofU.
 * 
 * Revision 1.2  84/04/02  14:40:21  donn
 * Added fixes from Conrad Huang at UCSF for calculating the length of a
 * concatenation of strings correctly.
 * 
 */

#include "defs.h"

#if FAMILY == PCC
#	include <pcc.h>
#else
#	include "dmrdefs.h"
#endif

/*
char *ops [ ] =
	{
	"??", "+", "-", "*", "/", "**", "-",
	"OR", "AND", "EQV", "NEQV", "NOT",
	"CONCAT",
	"<", "==", ">", "<=", "!=", ">=",
	" of ", " ofC ", " = ", " += ", " *= ", " CONV ", " << ", " % ",
	" , ", " ? ", " : "
	" abs ", " min ", " max ", " addr ", " indirect ",
	" bitor ", " bitand ", " bitxor ", " bitnot ", " >> ", " () "
	};
*/

int ops2 [ ] =
	{
	PCC_ERROR, PCC_PLUS, PCC_MINUS, PCC_MUL, PCC_DIV, PCC_ERROR, PCC_UMINUS,
	PCC_OROR, PCC_ANDAND, PCC_EQ, PCC_NE, PCC_NOT,
	PCC_ERROR,
	PCC_LT, PCC_EQ, PCC_GT, PCC_LE, PCC_NE, PCC_GE,
	PCC_CALL, PCC_CALL, PCC_ASSIGN, PCC_PLUSEQ, PCC_MULEQ, PCC_SCONV, PCC_LS, PCC_MOD,
	PCC_COMOP, PCC_QUEST, PCC_COLON,
	PCC_ERROR, PCC_ERROR, PCC_ERROR, PCC_ERROR, PCC_DEREF,
	PCC_OR, PCC_AND, PCC_ER, PCC_COMPL, PCC_RS, PCC_ERROR
	};


int types2 [ ] =
	{
	PCC_ERROR, PCCT_INT|PCCTM_PTR, PCCT_SHORT, PCCT_LONG, PCCT_FLOAT, PCCT_DOUBLE,
#if TARGET == INTERDATA
	PCC_ERROR, PCC_ERROR, PCCT_LONG, PCCT_CHAR, PCCT_INT, PCC_ERROR
#else
	PCCT_FLOAT, PCCT_DOUBLE, PCCT_LONG, PCCT_CHAR, PCCT_INT, PCC_ERROR
#endif
	};


setlog()
{
types2[TYLOGICAL] = types2[tylogical];
typesize[TYLOGICAL] = typesize[tylogical];
typealign[TYLOGICAL] = typealign[tylogical];
}


putex1(p)
expptr p;
{
putx( fixtype(p) );

if (!optimflag)
	{
	templist = hookup(templist, holdtemps);
	holdtemps = NULL;
	}
}





putassign(lp, rp)
expptr lp, rp;
{
putx( fixexpr( mkexpr(OPASSIGN, lp, rp) ));
}




puteq(lp, rp)
expptr lp, rp;
{
putexpr( mkexpr(OPASSIGN, lp, rp) );
}




/* put code for  a *= b */

putsteq(a, b)
expptr a, b;
{
putx( fixexpr( mkexpr(OPSTAREQ, cpexpr(a), cpexpr(b)) ));
}





Addrp realpart(p)
register Addrp p;
{
register Addrp q;

q = (Addrp) cpexpr(p);
if( ISCOMPLEX(p->vtype) )
	q->vtype += (TYREAL-TYCOMPLEX);
return(q);
}




expptr imagpart(p)
register expptr p;
{
register Addrp q;
expptr mkrealcon();

if (ISCONST(p))
	{
	if (ISCOMPLEX(p->constblock.vtype))
		return(mkrealcon(p->constblock.vtype == TYCOMPLEX ?
					TYREAL : TYDREAL,
				p->constblock.constant.cd[1]));
	else if (p->constblock.vtype == TYDREAL)
		return(mkrealcon(TYDREAL, 0.0));
	else
		return(mkrealcon(TYREAL, 0.0));
	}
else if (p->tag == TADDR)
	{
	if( ISCOMPLEX(p->addrblock.vtype) )
		{
		q = (Addrp) cpexpr(p);
		q->vtype += (TYREAL-TYCOMPLEX);
		q->memoffset = mkexpr(OPPLUS, q->memoffset,
					ICON(typesize[q->vtype]));
		return( (expptr) q );
		}
	else
		return( mkrealcon( ISINT(p->addrblock.vtype) ?
			TYDREAL : p->addrblock.vtype , 0.0));
	}
else
	badtag("imagpart", p->tag);
}




ncat(p)
register expptr p;
{
if(p->tag==TEXPR && p->exprblock.opcode==OPCONCAT)
	return( ncat(p->exprblock.leftp) + ncat(p->exprblock.rightp) );
else	return(1);
}




ftnint lencat(p)
register expptr p;
{
if(p->tag==TEXPR && p->exprblock.opcode==OPCONCAT)
	return( lencat(p->exprblock.leftp) + lencat(p->exprblock.rightp) );
else if( p->headblock.vleng!=NULL && ISICON(p->headblock.vleng) )
	return(p->headblock.vleng->constblock.constant.ci);
else if(p->tag==TADDR && p->addrblock.varleng!=0)
	return(p->addrblock.varleng);
else if(p->tag==TTEMP && p->tempblock.varleng!=0)
	return(p->tempblock.varleng);
else
	{
	err("impossible element in concatenation");
	return(0);
	}
}

Addrp putconst(p)
register Constp p;
{
register Addrp q;
struct Literal *litp, *lastlit;
int i, k, type;
int litflavor;

if( p->tag != TCONST )
	badtag("putconst", p->tag);

q = ALLOC(Addrblock);
q->tag = TADDR;
type = p->vtype;
q->vtype = ( type==TYADDR ? TYINT : type );
q->vleng = (expptr) cpexpr(p->vleng);
q->vstg = STGCONST;
q->memno = newlabel();
q->memoffset = ICON(0);

/* check for value in literal pool, and update pool if necessary */

switch(type = p->vtype)
	{
	case TYCHAR:
		if(p->vleng->constblock.constant.ci > XL)
			break;	/* too long for literal table */
		litflavor = 1;
		goto loop;

	case TYREAL:
	case TYDREAL:
		litflavor = 2;
		goto loop;

	case TYLOGICAL:
		type = tylogical;
	case TYSHORT:
	case TYLONG:
		litflavor = 3;

	loop:
		lastlit = litpool + nliterals;
		for(litp = litpool ; litp<lastlit ; ++litp)
			if(type == litp->littype) switch(litflavor)
				{
			case 1:
				if(p->vleng->constblock.constant.ci != litp->litval.litcval.litclen)
					break;
				if(! eqn( (int) p->vleng->constblock.constant.ci, p->constant.ccp,
					litp->litval.litcval.litcstr) )
						break;

			ret:
				q->memno = litp->litnum;
				frexpr(p);
				return(q);

			case 2:
				if(p->constant.cd[0] == litp->litval.litdval)
					goto ret;
				break;

			case 3:
				if(p->constant.ci == litp->litval.litival)
					goto ret;
				break;
				}
		if(nliterals < MAXLITERALS)
			{
			++nliterals;
			litp->littype = type;
			litp->litnum = q->memno;
			switch(litflavor)
				{
				case 1:
					litp->litval.litcval.litclen =
						p->vleng->constblock.constant.ci;
					cpn( (int) litp->litval.litcval.litclen,
						p->constant.ccp,
						litp->litval.litcval.litcstr);
					break;

				case 2:
					litp->litval.litdval = p->constant.cd[0];
					break;

				case 3:
					litp->litval.litival = p->constant.ci;
					break;
				}
			}
	default:
		break;
	}

preven(typealign[ type==TYCHAR ? TYLONG : type ]);
prlabel(asmfile, q->memno);

k = 1;
switch(type)
	{
	case TYLOGICAL:
	case TYSHORT:
	case TYLONG:
		prconi(asmfile, type, p->constant.ci);
		break;

	case TYCOMPLEX:
		k = 2;
	case TYREAL:
		type = TYREAL;
		goto flpt;

	case TYDCOMPLEX:
		k = 2;
	case TYDREAL:
		type = TYDREAL;

	flpt:
		for(i = 0 ; i < k ; ++i)
			prconr(asmfile, type, p->constant.cd[i]);
		break;

	case TYCHAR:
		putstr(asmfile, p->constant.ccp,
			(int) (p->vleng->constblock.constant.ci) );
		break;

	case TYADDR:
		prcona(asmfile, p->constant.ci);
		break;

	default:
		badtype("putconst", p->vtype);
	}

frexpr(p);
return( q );
}

/*
 * put out a character string constant.  begin every one on
 * a long integer boundary, and pad with nulls
 */
putstr(fp, s, n)
FILEP fp;
register char *s;
register int n;
{
int b[SZLONG];
register int i;

i = 0;
while(--n >= 0)
	{
	b[i++] = *s++;
	if(i == SZLONG)
		{
		prchars(fp, b);
		prchars(fp, b+SZSHORT);
		i = 0;
		}
	}

while(i < SZLONG)
	b[i++] = '\0';
prchars(fp, b);
prchars(fp, b+SZSHORT);
}
