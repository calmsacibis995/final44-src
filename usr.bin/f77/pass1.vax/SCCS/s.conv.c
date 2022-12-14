h54238
s 00006/00005/00935
d D 5.3 91/04/12 16:08:34 bostic 3 2
c new copyright; att/bsd/shared
e
s 00050/00050/00890
d D 5.2 88/01/03 15:56:39 bostic 2 1
c const is an ANSI C keyword
e
s 00940/00000/00000
d D 5.1 85/06/07 21:25:12 mckusick 1 0
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
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
#endif /* not lint */
E 3

/*
 * conv.c
 *
 * Routines for type conversions, f77 compiler pass 1.
 *
 * University of Utah CS Dept modification history:
 *
 * $Log:	conv.c,v $
 * Revision 2.2  85/06/07  21:09:29  root
 * Add copyright
 * 
 * Revision 2.1  84/07/19  12:02:29  donn
 * Changed comment headers for UofU.
 * 
 * Revision 1.2  84/04/13  01:07:02  donn
 * Fixed value of dminreal to be -1.7e38 + epsilon instead of -2.59e33, per
 * Bob Corbett's approval.
 * 
 */

#include "defs.h"
#include "conv.h"

int badvalue;


/*  The following constants are used to check the limits of  */
/*  conversions.  Dmaxword is the largest double precision   */
/*  number which can be converted to a two-byte integer      */
/*  without overflow.  Dminword is the smallest double       */
/*  precision value which can be converted to a two-byte     */
/*  integer without overflow.  Dmaxint and dminint are the   */
/*  analogous values for four-byte integers.                 */


LOCAL long dmaxword[] = { 0xfeff47ff, 0xffffffff };
LOCAL long dminword[] = { 0x00ffc800, 0xffffffff };

LOCAL long dmaxint[]  = { 0xffff4fff, 0xfffffeff };
LOCAL long dminint[]  = { 0x0000d000, 0xffff00ff };

LOCAL long dmaxreal[] = { 0xffff7fff, 0xffff7fff };
LOCAL long dminreal[] = { 0xffffffff, 0xffff7fff };



/*  The routines which follow are used to convert  */
/*  constants into constants of other types.       */

LOCAL char *
grabbits(len, cp)
int len;
Constp cp;
{

  static char *toobig = "bit value too large";

  register char *p;
  register char *bits;
  register int i;
  register int k;
  register int lenb;

D 2
  bits = cp->const.ccp;
  lenb = cp->vleng->constblock.const.ci;
E 2
I 2
  bits = cp->constant.ccp;
  lenb = cp->vleng->constblock.constant.ci;
E 2

  p = (char *) ckalloc(len);

  if (len >= lenb)
    k = lenb;
  else
    {
      k = len;
      if ( badvalue == 0 )
	{
#if (TARGET == PDP11 || TARGET == VAX)
	  i = len;
	  while ( i < lenb && bits[i] == 0 )
	    i++;
	  if (i < lenb)
	    badvalue = 1;
#else
	  i = lenb - len - 1;
	  while ( i >= 0 && bits[i] == 0)
	    i--;
	  if (i >= 0)
	    badvalue = 1;
#endif
	  if (badvalue)
	    warn(toobig);
	}
    }

#if (TARGET == PDP11 || TARGET == VAX)
  i = 0;
  while (i < k)
    {
      p[i] = bits[i];
      i++;
    }
#else
  i = lenb;
  while (k > 0)
    p[--k] = bits[--i];
#endif

  return (p);
}



LOCAL char *
grabbytes(len, cp)
int len;
Constp cp;
{
  register char *p;
  register char *bytes;
  register int i;
  register int k;
  register int lenb;

D 2
  bytes = cp->const.ccp;
  lenb = cp->vleng->constblock.const.ci;
E 2
I 2
  bytes = cp->constant.ccp;
  lenb = cp->vleng->constblock.constant.ci;
E 2

  p = (char *) ckalloc(len);

  if (len >= lenb)
    k = lenb;
  else
    k = len;

  i = 0;
  while (i < k)
    {
      p[i] = bytes[i];
      i++;
    }

  while (i < len)
    p[i++] = BLANK;

  return (p);
}



LOCAL expptr
cshort(cp)
Constp cp;
{
  static char *toobig = "data value too large";
  static char *reserved = "reserved operand assigned to an integer";
  static char *compat1 = "logical datum assigned to an integer variable";
  static char *compat2 = "character datum assigned to an integer variable";

  register expptr p;
  register short *shortp;
  register ftnint value;
  register long *rp;
  register double *minp;
  register double *maxp;
  realvalue x;

  switch (cp->vtype)
    {
    case TYBITSTR:
      shortp = (short *) grabbits(2, cp);
      p = (expptr) mkconst(TYSHORT);
D 2
      p->constblock.const.ci = *shortp;
E 2
I 2
      p->constblock.constant.ci = *shortp;
E 2
      free((char *) shortp);
      break;

    case TYSHORT:
      p = (expptr) cpexpr(cp);
      break;

    case TYLONG:
D 2
      value = cp->const.ci;
E 2
I 2
      value = cp->constant.ci;
E 2
      if (value >= MINWORD && value <= MAXWORD)
	{
	  p = (expptr) mkconst(TYSHORT);
D 2
	  p->constblock.const.ci = value;
E 2
I 2
	  p->constblock.constant.ci = value;
E 2
	}
      else
	{
	  if (badvalue <= 1)
	    {
	      badvalue = 2;
	      err(toobig);
	    }
	  p = errnode();
	}
      break;

    case TYREAL:
    case TYDREAL:
    case TYCOMPLEX:
    case TYDCOMPLEX:
      minp = (double *) dminword;
      maxp = (double *) dmaxword;
D 2
      rp = (long *) &(cp->const.cd[0]);
E 2
I 2
      rp = (long *) &(cp->constant.cd[0]);
E 2
      x.q.word1 = rp[0];
      x.q.word2 = rp[1];
      if (x.f.sign == 1 && x.f.exp == 0)
	{
	  if (badvalue <= 1)
	    {
	      badvalue = 2;
	      err(reserved);
	    }
	  p = errnode();
	}
      else if (x.d >= *minp && x.d <= *maxp)
	{
	  p = (expptr) mkconst(TYSHORT);
D 2
	  p->constblock.const.ci = x.d;
E 2
I 2
	  p->constblock.constant.ci = x.d;
E 2
	}
      else
	{
	  if (badvalue <= 1)
	    {
	      badvalue = 2;
	      err(toobig);
	    }
	  p = errnode();
	}
      break;

    case TYLOGICAL:
      if (badvalue <= 1)
	{
	  badvalue = 2;
	  err(compat1);
	}
      p = errnode();
      break;

    case TYCHAR:
      if ( !ftn66flag && badvalue == 0 )
	{
	  badvalue = 1;
	  warn(compat2);
	}

    case TYHOLLERITH:
      shortp = (short *) grabbytes(2, cp);
      p = (expptr) mkconst(TYSHORT);
D 2
      p->constblock.const.ci = *shortp;
E 2
I 2
      p->constblock.constant.ci = *shortp;
E 2
      free((char *) shortp);
      break;

    case TYERROR:
      p = errnode();
      break;
    }

  return (p);
}



LOCAL expptr
clong(cp)
Constp cp;
{
  static char *toobig = "data value too large";
  static char *reserved = "reserved operand assigned to an integer";
  static char *compat1 = "logical datum assigned to an integer variable";
  static char *compat2 = "character datum assigned to an integer variable";

  register expptr p;
  register ftnint *longp;
  register long *rp;
  register double *minp;
  register double *maxp;
  realvalue x;

  switch (cp->vtype)
    {
    case TYBITSTR:
      longp = (ftnint *) grabbits(4, cp);
      p = (expptr) mkconst(TYLONG);
D 2
      p->constblock.const.ci = *longp;
E 2
I 2
      p->constblock.constant.ci = *longp;
E 2
      free((char *) longp);
      break;

    case TYSHORT:
      p = (expptr) mkconst(TYLONG);
D 2
      p->constblock.const.ci = cp->const.ci;
E 2
I 2
      p->constblock.constant.ci = cp->constant.ci;
E 2
      break;

    case TYLONG:
      p = (expptr) cpexpr(cp);
      break;

    case TYREAL:
    case TYDREAL:
    case TYCOMPLEX:
    case TYDCOMPLEX:
      minp = (double *) dminint;
      maxp = (double *) dmaxint;
D 2
      rp = (long *) &(cp->const.cd[0]);
E 2
I 2
      rp = (long *) &(cp->constant.cd[0]);
E 2
      x.q.word1 = rp[0];
      x.q.word2 = rp[1];
      if (x.f.sign == 1 && x.f.exp == 0)
	{
	  if (badvalue <= 1)
	    {
	      badvalue = 2;
	      err(reserved);
	    }
	  p = errnode();
	}
      else if (x.d >= *minp && x.d <= *maxp)
	{
	  p = (expptr) mkconst(TYLONG);
D 2
	  p->constblock.const.ci = x.d;
E 2
I 2
	  p->constblock.constant.ci = x.d;
E 2
	}
      else
	{
	  if (badvalue <= 1)
	    {
	      badvalue = 2;
	      err(toobig);
	    }
	  p = errnode();
	}
      break;

    case TYLOGICAL:
      if (badvalue <= 1)
	{
	  badvalue = 2;
	  err(compat1);
	}
      p = errnode();
      break;

    case TYCHAR:
      if ( !ftn66flag && badvalue == 0 )
	{
	  badvalue = 1;
	  warn(compat2);
	}

    case TYHOLLERITH:
      longp = (ftnint *) grabbytes(4, cp);
      p = (expptr) mkconst(TYLONG);
D 2
      p->constblock.const.ci = *longp;
E 2
I 2
      p->constblock.constant.ci = *longp;
E 2
      free((char *) longp);
      break;

    case TYERROR:
      p = errnode();
      break;
    }

  return (p);
}



LOCAL expptr
creal(cp)
Constp cp;
{
  static char *toobig = "data value too large";
  static char *compat1 = "logical datum assigned to a real variable";
  static char *compat2 = "character datum assigned to a real variable";

  register expptr p;
  register long *longp;
  register long *rp;
  register double *minp;
  register double *maxp;
  realvalue x;
  float y;

  switch (cp->vtype)
    {
    case TYBITSTR:
      longp = (long *) grabbits(4, cp);
      p = (expptr) mkconst(TYREAL);
D 2
      rp = (long *) &(p->constblock.const.cd[0]);
E 2
I 2
      rp = (long *) &(p->constblock.constant.cd[0]);
E 2
      rp[0] = *longp;
      free((char *) longp);
      break;

    case TYSHORT:
    case TYLONG:
      p = (expptr) mkconst(TYREAL);
D 2
      p->constblock.const.cd[0] = cp->const.ci;
E 2
I 2
      p->constblock.constant.cd[0] = cp->constant.ci;
E 2
      break;

    case TYREAL:
    case TYDREAL:
    case TYCOMPLEX:
    case TYDCOMPLEX:
      minp = (double *) dminreal;
      maxp = (double *) dmaxreal;
D 2
      rp = (long *) &(cp->const.cd[0]);
E 2
I 2
      rp = (long *) &(cp->constant.cd[0]);
E 2
      x.q.word1 = rp[0];
      x.q.word2 = rp[1];
      if (x.f.sign == 1 && x.f.exp == 0)
	{
	  p = (expptr) mkconst(TYREAL);
D 2
	  rp = (long *) &(p->constblock.const.cd[0]);
E 2
I 2
	  rp = (long *) &(p->constblock.constant.cd[0]);
E 2
	  rp[0] = x.q.word1;
	}
      else if (x.d >= *minp && x.d <= *maxp)
	{
	  p = (expptr) mkconst(TYREAL);
	  y = x.d;
D 2
	  p->constblock.const.cd[0] = y;
E 2
I 2
	  p->constblock.constant.cd[0] = y;
E 2
	}
      else
	{
	  if (badvalue <= 1)
	    {
	      badvalue = 2;
	      err(toobig);
	    }
	  p = errnode();
	}
      break;

    case TYLOGICAL:
      if (badvalue <= 1)
	{
	  badvalue = 2;
	  err(compat1);
	}
      p = errnode();
      break;

    case TYCHAR:
      if ( !ftn66flag && badvalue == 0)
	{
	  badvalue = 1;
	  warn(compat2);
	}

    case TYHOLLERITH:
      longp = (long *) grabbytes(4, cp);
      p = (expptr) mkconst(TYREAL);
D 2
      rp = (long *) &(p->constblock.const.cd[0]);
E 2
I 2
      rp = (long *) &(p->constblock.constant.cd[0]);
E 2
      rp[0] = *longp;
      free((char *) longp);
      break;

    case TYERROR:
      p = errnode();
      break;
    }

  return (p);
}



LOCAL expptr
cdreal(cp)
Constp cp;
{
  static char *compat1 =
	"logical datum assigned to a double precision variable";
  static char *compat2 =
	"character datum assigned to a double precision variable";

  register expptr p;
  register long *longp;
  register long *rp;

  switch (cp->vtype)
    {
    case TYBITSTR:
      longp = (long *) grabbits(8, cp);
      p = (expptr) mkconst(TYDREAL);
D 2
      rp = (long *) &(p->constblock.const.cd[0]);
E 2
I 2
      rp = (long *) &(p->constblock.constant.cd[0]);
E 2
      rp[0] = longp[0];
      rp[1] = longp[1];
      free((char *) longp);
      break;

    case TYSHORT:
    case TYLONG:
      p = (expptr) mkconst(TYDREAL);
D 2
      p->constblock.const.cd[0] = cp->const.ci;
E 2
I 2
      p->constblock.constant.cd[0] = cp->constant.ci;
E 2
      break;

    case TYREAL:
    case TYDREAL:
    case TYCOMPLEX:
    case TYDCOMPLEX:
      p = (expptr) mkconst(TYDREAL);
D 2
      longp = (long *) &(cp->const.cd[0]);
      rp = (long *) &(p->constblock.const.cd[0]);
E 2
I 2
      longp = (long *) &(cp->constant.cd[0]);
      rp = (long *) &(p->constblock.constant.cd[0]);
E 2
      rp[0] = longp[0];
      rp[1] = longp[1];
      break;

    case TYLOGICAL:
      if (badvalue <= 1)
	{
	  badvalue = 2;
	  err(compat1);
	}
      p = errnode();
      break;

    case TYCHAR:
      if ( !ftn66flag && badvalue == 0 )
	{
	  badvalue = 1;
	  warn(compat2);
	}

    case TYHOLLERITH:
      longp = (long *) grabbytes(8, cp);
      p = (expptr) mkconst(TYDREAL);
D 2
      rp = (long *) &(p->constblock.const.cd[0]);
E 2
I 2
      rp = (long *) &(p->constblock.constant.cd[0]);
E 2
      rp[0] = longp[0];
      rp[1] = longp[1];
      free((char *) longp);
      break;

    case TYERROR:
      p = errnode();
      break;
    }

  return (p);
}



LOCAL expptr
ccomplex(cp)
Constp cp;
{
  static char *toobig = "data value too large";
  static char *compat1 = "logical datum assigned to a complex variable";
  static char *compat2 = "character datum assigned to a complex variable";

  register expptr p;
  register long *longp;
  register long *rp;
  register double *minp;
  register double *maxp;
  realvalue re, im;
  int overflow;
  float x;

  switch (cp->vtype)
    {
    case TYBITSTR:
      longp = (long *) grabbits(8, cp);
      p = (expptr) mkconst(TYCOMPLEX);
D 2
      rp = (long *) &(p->constblock.const.cd[0]);
E 2
I 2
      rp = (long *) &(p->constblock.constant.cd[0]);
E 2
      rp[0] = longp[0];
      rp[2] = longp[1];
      free((char *) longp);
      break;

    case TYSHORT:
    case TYLONG:
      p = (expptr) mkconst(TYCOMPLEX);
D 2
      p->constblock.const.cd[0] = cp->const.ci;
E 2
I 2
      p->constblock.constant.cd[0] = cp->constant.ci;
E 2
      break;

    case TYREAL:
    case TYDREAL:
    case TYCOMPLEX:
    case TYDCOMPLEX:
      overflow = 0;
      minp = (double *) dminreal;
      maxp = (double *) dmaxreal;
D 2
      rp = (long *) &(cp->const.cd[0]);
E 2
I 2
      rp = (long *) &(cp->constant.cd[0]);
E 2
      re.q.word1 = rp[0];
      re.q.word2 = rp[1];
      im.q.word1 = rp[2];
      im.q.word2 = rp[3];
      if (((re.f.sign == 0 || re.f.exp != 0) &&
	   (re.d < *minp || re.d > *maxp))       ||
	  ((im.f.sign == 0 || re.f.exp != 0) &&
	   (im.d < *minp || re.d > *maxp)))
	{
	  if (badvalue <= 1)
	    {
	      badvalue = 2;
	      err(toobig);
	    }
	  p = errnode();
	}
      else
	{
	  p = (expptr) mkconst(TYCOMPLEX);
	  if (re.f.sign == 1 && re.f.exp == 0)
	    re.q.word2 = 0;
	  else
	    {
	      x = re.d;
	      re.d = x;
	    }
	  if (im.f.sign == 1 && im.f.exp == 0)
	    im.q.word2 = 0;
	  else
	    {
	      x = im.d;
	      im.d = x;
	    }
D 2
	  rp = (long *) &(p->constblock.const.cd[0]);
E 2
I 2
	  rp = (long *) &(p->constblock.constant.cd[0]);
E 2
	  rp[0] = re.q.word1;
	  rp[1] = re.q.word2;
	  rp[2] = im.q.word1;
	  rp[3] = im.q.word2;
	}
      break;

    case TYLOGICAL:
      if (badvalue <= 1)
	{
	  badvalue = 2;
	  err(compat1);
	}
      break;

    case TYCHAR:
      if ( !ftn66flag && badvalue == 0)
	{
	  badvalue = 1;
	  warn(compat2);
	}

    case TYHOLLERITH:
      longp = (long *) grabbytes(8, cp);
      p = (expptr) mkconst(TYCOMPLEX);
D 2
      rp = (long *) &(p->constblock.const.cd[0]);
E 2
I 2
      rp = (long *) &(p->constblock.constant.cd[0]);
E 2
      rp[0] = longp[0];
      rp[2] = longp[1];
      free((char *) longp);
      break;

    case TYERROR:
      p = errnode();
      break;
    }

  return (p);
}



LOCAL expptr
cdcomplex(cp)
Constp cp;
{
  static char *compat1 = "logical datum assigned to a complex variable";
  static char *compat2 = "character datum assigned to a complex variable";

  register expptr p;
  register long *longp;
  register long *rp;

  switch (cp->vtype)
    {
    case TYBITSTR:
      longp = (long *) grabbits(16, cp);
      p = (expptr) mkconst(TYDCOMPLEX);
D 2
      rp = (long *) &(p->constblock.const.cd[0]);
E 2
I 2
      rp = (long *) &(p->constblock.constant.cd[0]);
E 2
      rp[0] = longp[0];
      rp[1] = longp[1];
      rp[2] = longp[2];
      rp[3] = longp[3];
      free((char *) longp);
      break;

    case TYSHORT:
    case TYLONG:
      p = (expptr) mkconst(TYDCOMPLEX);
D 2
      p->constblock.const.cd[0] = cp->const.ci;
E 2
I 2
      p->constblock.constant.cd[0] = cp->constant.ci;
E 2
      break;

    case TYREAL:
    case TYDREAL:
    case TYCOMPLEX:
    case TYDCOMPLEX:
      p = (expptr) mkconst(TYDCOMPLEX);
D 2
      longp = (long *) &(cp->const.cd[0]);
      rp = (long *) &(p->constblock.const.cd[0]);
E 2
I 2
      longp = (long *) &(cp->constant.cd[0]);
      rp = (long *) &(p->constblock.constant.cd[0]);
E 2
      rp[0] = longp[0];
      rp[1] = longp[1];
      rp[2] = longp[2];
      rp[3] = longp[3];
      break;

    case TYLOGICAL:
      if (badvalue <= 1)
	{
	  badvalue = 2;
	  err(compat1);
	}
      p = errnode();
      break;

    case TYCHAR:
      if ( !ftn66flag && badvalue == 0 )
	{
	  badvalue = 1;
	  warn(compat2);
	}

    case TYHOLLERITH:
      longp = (long *) grabbytes(16, cp);
      p = (expptr) mkconst(TYDCOMPLEX);
D 2
      rp = (long *) &(p->constblock.const.cd[0]);
E 2
I 2
      rp = (long *) &(p->constblock.constant.cd[0]);
E 2
      rp[0] = longp[0];
      rp[1] = longp[1];
      rp[2] = longp[2];
      rp[3] = longp[3];
      free((char *) longp);
      break;

    case TYERROR:
      p = errnode();
      break;
    }

  return (p);
}



LOCAL expptr
clogical(cp)
Constp cp;
{
  static char *compat1 = "numeric datum assigned to a logical variable";
  static char *compat2 = "character datum assigned to a logical variable";

  register expptr p;
  register long *longp;
  register short *shortp;
  register int size;

  size = typesize[tylogical];

  switch (cp->vtype)
    {
    case TYBITSTR:
      p = (expptr) mkconst(tylogical);
      if (tylogical == TYSHORT)
	{
	  shortp = (short *) grabbits(size, cp);
D 2
	  p->constblock.const.ci = (int) *shortp;
E 2
I 2
	  p->constblock.constant.ci = (int) *shortp;
E 2
	  free((char *) shortp);
	}
      else
	{
	  longp = (long *) grabbits(size, cp);
D 2
	  p->constblock.const.ci = *longp;
E 2
I 2
	  p->constblock.constant.ci = *longp;
E 2
	  free((char *) longp);
	}
      break;

    case TYSHORT:
    case TYLONG:
    case TYREAL:
    case TYDREAL:
    case TYCOMPLEX:
    case TYDCOMPLEX:
      if (badvalue <= 1)
	{
	  badvalue = 2;
	  err(compat1);
	}
      p = errnode();
      break;

    case TYLOGICAL:
      p = (expptr) cpexpr(cp);
      p->constblock.vtype = tylogical;
      break;

    case TYCHAR:
      if ( !ftn66flag && badvalue == 0 )
	{
	  badvalue = 1;
	  warn(compat2);
	}

    case TYHOLLERITH:
      p = (expptr) mkconst(tylogical);
      if (tylogical == TYSHORT)
	{
	  shortp = (short *) grabbytes(size, cp);
D 2
	  p->constblock.const.ci = (int) *shortp;
E 2
I 2
	  p->constblock.constant.ci = (int) *shortp;
E 2
	  free((char *) shortp);
	}
      else
	{
	  longp = (long *) grabbytes(4, cp);
D 2
	  p->constblock.const.ci = *longp;
E 2
I 2
	  p->constblock.constant.ci = *longp;
E 2
	  free((char *) longp);
	}
      break;

    case TYERROR:
      p = errnode();
      break;
    }

  return (p);
}



LOCAL expptr
cchar(len, cp)
int len;
Constp cp;
{
  static char *compat1 = "numeric datum assigned to a character variable";
  static char *compat2 = "logical datum assigned to a character variable";

  register expptr p;
  register char *value;

  switch (cp->vtype)
    {
    case TYBITSTR:
      value = grabbits(len, cp);
      p = (expptr) mkstrcon(len, value);
      free(value);
      break;

    case TYSHORT:
    case TYLONG:
    case TYREAL:
    case TYDREAL:
    case TYCOMPLEX:
    case TYDCOMPLEX:
      if (badvalue <= 1)
	{
	  badvalue = 2;
	  err(compat1);
	}
      p = errnode();
      break;

    case TYLOGICAL:
      if (badvalue <= 1)
	{
	  badvalue = 2;
	  err(compat2);
	}
      p = errnode();
      break;

    case TYCHAR:
    case TYHOLLERITH:
      value = grabbytes(len, cp);
      p = (expptr) mkstrcon(len, value);
      free(value);
      break;

    case TYERROR:
      p = errnode();
      break;
    }

  return (p);
}



expptr
D 2
convconst(type, len, const)
E 2
I 2
convconst(type, len, constant)
E 2
int type;
int len;
D 2
Constp const;
E 2
I 2
Constp constant;
E 2
{
  register expptr p;

  switch (type)
    {
    case TYSHORT:
D 2
      p = cshort(const);
E 2
I 2
      p = cshort(constant);
E 2
      break;

    case TYLONG:
D 2
      p = clong(const);
E 2
I 2
      p = clong(constant);
E 2
      break;

    case TYREAL:
D 2
      p = creal(const);
E 2
I 2
      p = creal(constant);
E 2
      break;

    case TYDREAL:
D 2
      p = cdreal(const);
E 2
I 2
      p = cdreal(constant);
E 2
      break;

    case TYCOMPLEX:
D 2
      p = ccomplex(const);
E 2
I 2
      p = ccomplex(constant);
E 2
      break;

    case TYDCOMPLEX:
D 2
      p = cdcomplex(const);
E 2
I 2
      p = cdcomplex(constant);
E 2
      break;

    case TYLOGICAL:
D 2
      p = clogical(const);
E 2
I 2
      p = clogical(constant);
E 2
      break;

    case TYCHAR:
D 2
      p = cchar(len, const);
E 2
I 2
      p = cchar(len, constant);
E 2
      break;

    case TYERROR:
    case TYUNKNOWN:
      p = errnode();
      break;

    default:
      badtype("convconst", type);
    }

  return (p);
}
E 1
