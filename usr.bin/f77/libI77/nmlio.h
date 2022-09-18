/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 *
 *	@(#)nmlio.h	5.2 (Berkeley) 4/12/91
 */

/*	header for namelist I/O */

#define ERRNM(x)	if(n=(x)) return(n);
#define VL		16	/* variable name length from f77pass1/defs.h */

extern char namelistkey_;

typedef struct
{
	char namelistname[VL+4];	/* 4 for padding */
	struct namelistentry
		{
		char varname[VL+4];	/* 4 for padding */
		char *varaddr;
		short int type;
		short int typelen;
		/*
		 * If dimp is not null, then the corner element of the array is
		 * at varaddr.  However,  the element with subscripts:
		 * (i1,...,in) is at
		 *
		 *	varaddr - dimp->baseoffset + sizeoftype *
		 *			((i1-1)+span[0]*((i2-1)+span[1]*...)
		 */
		int *dimp;	/* dimension info: (null means scalar)
					*dimp: numb. of dim.,
					dimp[0]: number of dimensions
					dimp[1]: total number of elements,
					dimp[2]: base offset,
					dimp[3]: span of 1st dimension
					dimp[4]: span of 2nd dimension
						...			 */
		} names[1];	/* actually one per name in the namelist */
} Namelist;

typedef struct
{	flag cierr;
	ftnint ciunit;
	flag ciend;
	Namelist *namelist;
} namelist_arglist;
