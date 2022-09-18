h63864
s 00007/00006/00094
d D 5.3 91/04/12 16:00:56 bostic 3 2
c new copyright; att/bsd/shared
e
s 00002/00002/00098
d D 5.2 91/02/06 12:14:13 bostic 2 1
c ANSI; const -> constant, inline -> inlne
e
s 00100/00000/00000
d D 5.1 90/06/17 18:08:46 bostic 1 0
c date and time created 90/06/17 18:08:46 by bostic
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
static char sccsid[] = "@(#)paramset.c	5.1 (Berkeley) 6/7/85";
#endif not lint
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

/*
 * paramset.c
 *
 * Routines for handling PARAMETER statements, f77 compiler, 4.2 BSD.
 *
 * $Log:	paramset.c,v $
 * Revision 3.2  84/10/13  03:52:03  donn
 * Setting a parameter variable to a nonconstant expression is an error;
 * previously a mere warning was emitted.  Also added a comment header.
 * 
 */

#include "defs.h"
#include "data.h"

/*	process the items in a PARAMETER statement	*/
paramset( param_item_nm, param_item_vl )
Namep param_item_nm;
expptr param_item_vl;
{
  if (param_item_nm->vstg != STGUNKNOWN && param_item_nm->vstg != STGCONST )
    dclerr("conflicting declarations", param_item_nm);
  else if (param_item_nm->vclass == CLUNKNOWN)
    param_item_nm->vclass = CLPARAM;
  else if ( param_item_nm->vclass == CLPARAM )
    dclerr("redefining PARAMETER value", param_item_nm );
  else
    dclerr("conflicting declarations", param_item_nm);

  if (param_item_nm->vclass == CLPARAM)
    {
      if (!ISCONST(param_item_vl))
	param_item_vl = fixtype(param_item_vl);

      if (param_item_nm->vtype == TYUNKNOWN)
	{
	  char c;

	  c = param_item_nm->varname[0];
	  if (c >= 'A' && c <= 'Z')
	    c = c - 'A';
	  else
	    c = c - 'a';
	  param_item_nm->vtype = impltype[c];
	  param_item_nm->vleng = ICON(implleng[c]);
	}
      if (param_item_nm->vtype == TYUNKNOWN)
	{ 
	  warn1("type undefined for %s",
		varstr(VL, param_item_nm->varname));
	  ((struct Paramblock *) (param_item_nm))->paramval = param_item_vl;
	}
      else
	{
	  extern int badvalue;
	  extern expptr constconv();
	  int type;
	  ftnint len;

	  type = param_item_nm->vtype;
	  if (type == TYCHAR)
	    {
	      if (param_item_nm->vleng != NULL)
D 2
		len = param_item_nm->vleng->constblock.const.ci;
E 2
I 2
		len = param_item_nm->vleng->constblock.constant.ci;
E 2
	      else if (ISCONST(param_item_vl) &&
			param_item_vl->constblock.vtype == TYCHAR)
		len = param_item_vl->constblock.vleng->
D 2
			constblock.const.ci;
E 2
I 2
			constblock.constant.ci;
E 2
	      else
		len = 1;
	    }
	  badvalue = 0;
	  if (ISCONST(param_item_vl))
	    {
	      ((struct Paramblock *) (param_item_nm))->paramval =
	        convconst(param_item_nm->vtype, len, param_item_vl);
	      if (type == TYLOGICAL)
		((struct Paramblock *) (param_item_nm))->paramval->
		  headblock.vtype = TYLOGICAL;
	      frexpr((tagptr) param_item_vl);
	    }
	  else
	    {
	      erri("%s set to a nonconstant",
		    varstr(VL, param_item_nm->varname));
	      ((struct Paramblock *) (param_item_nm))->paramval = param_item_vl;
	    }
	}
    }
}
E 1
