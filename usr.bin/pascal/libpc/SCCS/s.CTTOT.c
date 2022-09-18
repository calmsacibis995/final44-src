h24185
s 00002/00002/00130
d D 8.1 93/06/06 15:15:18 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00123
d D 1.6 90/04/09 18:24:29 bostic 6 5
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00027/00008/00098
d D 1.5 89/01/09 15:38:33 mckusick 5 4
c update from John Gilmore for gcc
e
s 00000/00001/00106
d D 1.4 81/06/10 00:37:32 mckusic 4 3
c move the text of error messages from ERROR to the functions
c which generate them.
e
s 00005/00003/00102
d D 1.3 81/06/08 00:34:53 mckusic 3 2
c put in better error messages
e
s 00041/00027/00064
d D 1.2 81/03/07 15:53:42 mckusic 2 1
c merge in onyx changes
e
s 00091/00000/00000
d D 1.1 80/10/30 00:33:00 mckusick 1 0
c date and time created 80/10/30 00:33:00 by mckusick
e
u
U
t
T
I 1
D 6
/* Copyright (c) 1979 Regents of the University of California */
E 6
I 6
/*-
D 7
 * Copyright (c) 1979 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1979, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
 */
E 6

D 6
static char sccsid[] = "%Z%%M% %I% %G%";
E 6
I 6
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 6

I 2
#include "whoami.h"
E 2
#include "h00vars.h"
D 4
#include "h01errs.h"
E 4

long	_mask[] = {	
I 2
#		ifdef DEC11
E 2
		    0xffffffff , 0xfffffffe , 0xfffffffc , 0xfffffff8 ,
		    0xfffffff0 , 0xffffffe0 , 0xffffffc0 , 0xffffff80 ,
		    0xffffff00 , 0xfffffe00 , 0xfffffc00 , 0xfffff800 ,
		    0xfffff000 , 0xffffe000 , 0xffffc000 , 0xffff8000 ,
		    0xffff0000 , 0xfffe0000 , 0xfffc0000 , 0xfff80000 ,
		    0xfff00000 , 0xffe00000 , 0xffc00000 , 0xff800000 ,
		    0xff000000 , 0xfe000000 , 0xfc000000 , 0xf8000000 ,
		    0xf0000000 , 0xe0000000 , 0xc0000000 , 0x80000000 ,
		    0x00000000
D 2
		 };
E 2
I 2
#		else
		    0xffffffff , 0xfeffffff , 0xfcffffff , 0xf8ffffff ,
		    0xf0ffffff , 0xe0ffffff , 0xc0ffffff , 0x80ffffff ,
		    0x00ffffff , 0x00feffff , 0x00fcffff , 0x00f8ffff ,
		    0x00f0ffff , 0x00e0ffff , 0x00c0ffff , 0x0080ffff ,
		    0x0000ffff , 0x0000feff , 0x0000fcff , 0x0000f8ff ,
		    0x0000f0ff , 0x0000e0ff , 0x0000c0ff , 0x000080ff ,
		    0x000000ff , 0x000000fe , 0x000000fc , 0x000000f8 ,
		    0x000000f0 , 0x000000e0 , 0x000000c0 , 0x00000080 ,
		    0x00000000
#		endif DEC11
	    };
E 2
/*
D 5
 * Constant set constructor
E 5
I 5
 * Constant set constructors.
 *
 * CTTOT is called from compiled Pascal.  It takes the list of ranges
 * and single elements on the stack, varargs style.
 *
 * CTTOTA is called from the px interpreter.  It takes a pointer to the
 * list of ranges and single elements.
 *
 * This was easier than changing the compiler to pass a pointer into
 * its own partially-constructed stack, while working to make px portable.
E 5
 */

I 5
long *CTTOTA();

E 5
long *
D 2
CTTOT(result, lowerbnd, upperbnd, paircnt, singcnt, data)
E 2
I 2
D 5
CTTOT(result0, lwrbnd, uprbnd, paircnt, singcnt, data)
E 5
I 5
CTTOT(result, lwrbnd, uprbnd, paircnt, singcnt, data)
E 5
E 2

D 2
	long	*result;	/* pointer to final set */
	int	lowerbnd;	/* lower bound of set */
	int	upperbnd;	/* upper - lower of set */
	int	paircnt;	/* number of pairs to construct */
	int	singcnt;	/* number of singles to construct */
	int	data;		/* paircnt plus singcnt sets of data */
E 2
I 2
D 5
	long	*result0;	/* pointer to final set */
E 5
I 5
	long	*result;	/* pointer to final set */
E 5
	long	lwrbnd;		/* lower bound of set */
	long	uprbnd;		/* upper - lower of set */
	long	paircnt;	/* number of pairs to construct */
	long	singcnt;	/* number of singles to construct */
	long	data;		/* paircnt plus singcnt sets of data */
E 2
{
D 2
	register int	lower;
	register int	lowerdiv;
	register int	lowermod;
	register int	upper;
	int		upperdiv;
	int		uppermod;
	register int	*dataptr;
E 2
I 2
D 5
	register long	*result = result0;
	register long	*dataptr = &data;
E 5
I 5
	return CTTOTA(result, lwrbnd, uprbnd, paircnt, singcnt, &data);
}

long *
CTTOTA(result, lwrbnd, uprbnd, paircnt, singcnt, dataptr)

	register long	*result;	/* pointer to final set */
	long	lwrbnd;			/* lower bound of set */
	long	uprbnd;			/* upper - lower of set */
	long	paircnt;		/* number of pairs to construct */
	long	singcnt;		/* number of singles to construct */
	register long	*dataptr;	/* ->paircnt plus singcnt data values */
{
E 5
	int		lowerbnd = lwrbnd;
	int		upperbnd = uprbnd;
E 2
	register long	*lp;
I 2
	register char	*cp;
	register long	temp;
E 2
	long		*limit;
D 2
	long		temp;
	long		cnt;
E 2
I 2
	int		lower;
	int		lowerdiv;
	int		lowermod;
	int		upper;
	int		upperdiv;
	int		uppermod;
	int		cnt;
E 2

D 2
	limit = &result[(upperbnd + 1 + BITSPERLONG - 1) / BITSPERLONG];
E 2
I 2
	limit = &result[(upperbnd + 1 + BITSPERLONG - 1) >> LG2BITSLONG];
E 2
	for (lp = result; lp < limit; )
		*lp++ = 0;
D 2
	dataptr = &data;
E 2
	for (cnt = 0; cnt < paircnt; cnt++) {
		upper = *dataptr++ - lowerbnd;
		if (upper < 0 || upper > upperbnd) {
D 3
			ERROR(ECTUPR, *--dataptr);
E 3
I 3
			ERROR("Range upper bound of %D out of set bounds\n",
				*--dataptr);
E 3
D 5
			return;
E 5
		}
		lower = *dataptr++ - lowerbnd;
		if (lower < 0 || lower > upperbnd) {
D 3
			ERROR(ECTLWR, *--dataptr);
E 3
I 3
			ERROR("Range lower bound of %D out of set bounds\n",
				*--dataptr);
E 3
D 5
			return;
E 5
		}
		if (lower > upper) {
			continue;
		}
D 2
		lowerdiv = lower / BITSPERLONG;
		lowermod = lower % BITSPERLONG;
		upperdiv = upper / BITSPERLONG;
		uppermod = upper % BITSPERLONG;
E 2
I 2
		lowerdiv = lower >> LG2BITSLONG;
		lowermod = lower & MSKBITSLONG;
		upperdiv = upper >> LG2BITSLONG;
		uppermod = upper & MSKBITSLONG;
E 2
		temp = _mask [lowermod];
		if ( lowerdiv == upperdiv ) {
			temp &= ~_mask[ uppermod + 1 ];
		}
		result[ lowerdiv ] |= temp;
		limit = &result[ upperdiv-1 ];
		for ( lp = &result[ lowerdiv+1 ] ; lp <= limit ; lp++ ) {
			*lp |= ~0;
		}
		if ( lowerdiv != upperdiv ) {
			result[ upperdiv ] |= ~_mask[ uppermod + 1 ];
		}
	}
D 2
	for (cnt = 0; cnt < singcnt; cnt++) {
E 2
I 2
	for (cnt = 0, cp = (char *)result; cnt < singcnt; cnt++) {
E 2
		lower = *dataptr++ - lowerbnd;
		if (lower < 0 || lower > upperbnd) {
D 3
			ERROR(ECTSNG, *--dataptr);
E 3
I 3
			ERROR("Value of %D out of set bounds\n", *--dataptr);
E 3
D 5
			return;
E 5
		}
D 2
		lowerdiv = lower / BITSPERLONG;
		lowermod = lower % BITSPERLONG;
		result[ lowerdiv ] |= ( 1 << lowermod );
E 2
I 2
		cp[ lower >> LG2BITSBYTE ] |= (1 << (lower & MSKBITSBYTE));
E 2
	}
	return(result);
}
E 1
