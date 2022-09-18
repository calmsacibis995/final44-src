/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	fpascii.c,v $
 * Revision 2.5  89/03/09  21:34:18  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  19:40:23  gm0w
 * 	Changes for cleanup.
 * 
 * 08-Feb-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Removed else leg of KERNEL conditionals and fixed 
 *	includes as part of kernel cleanup.
 *
 * 29-Dec-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Gcc wants "unsigned" in typedef "bcd" terminated by ";"
 *
 * 29-Jan-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Conditionalized kdb code under KERNEL and changed pathnames
 *	of include files to be kernel relative in order to make
 *	kdb part of the kernel rather than a separate library.
 *
 *  5-Sep-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Converted into kernel debugger, "kdb".
 *	Temporary: can't print a floating point number (doubletos)
 *	if no 68881 present.
 *
 */
#ifndef	lint
static  char sccsid[] = "@(#)fpascii.c 1.1 86/02/03 Copyr 1985 Sun Micro";
#endif

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

#include <sun3/reg.h>
#include <sun3/kdb/fpascii.h>

void fprtos( fpr, s )

	ext_fp *fpr ;
	char *s ;

/*
 *	Converts floating point register at fpr to string at s.
 */

{
typedef struct 
	{ 
	unsigned s:4, e2:4, e1:4, e0:4,
		u2:4, u1:4, u0:4, m16:4,
		m15:4, m14:4, m13:4, m12:4,
		m11:4, m10:4, m9:4, m8:4,
		m7:4, m6:4, m5:4, m4:4,
		m3:4, m2:4, m1:4, m0:4;
	} bcd ;

bcd p ;
int fps ;

fps = fprtop( fpr, &p ) ;
if (p.s & 8)
	*s++ = '-' ;
else
	*s++ = ' ' ;
if (p.e2 == 0xf)
	{ /* inf or nan */
	if (p.m15||p.m14||p.m13||p.m12||p.m11||p.m10||p.m9||p.m8||
		p.m7||p.m6||p.m5||p.m4||p.m3||p.m2||p.m1||p.m0)
		{ /* nan */
		*s++ = 'N' ;
		*s++ = 'a' ;
		*s++ = 'N' ;
		} /* nan */
	else
		{ /* inf */
		*s++ = 'I' ;
		*s++ = 'n' ;
		*s++ = 'f' ;
		} /* inf */
	} /* inf or nan */
else
	{ /* number */
	if (p.m16 == 0)
		{ /* zero */
		*s++ = '0' ;
		} /* zero */
	else
		{ /* subnormal or normal */
		*s++ = '0' + p.m16 ;
		*s++ = '.' ;
		*s++ = '0' + p.m15 ;
		*s++ = '0' + p.m14 ;
		*s++ = '0' + p.m13 ;
		*s++ = '0' + p.m12 ;
		*s++ = '0' + p.m11 ;
		*s++ = '0' + p.m10 ;
		*s++ = '0' + p.m9 ;
		*s++ = '0' + p.m8 ;
		*s++ = '0' + p.m7 ;
		*s++ = '0' + p.m6 ;
		*s++ = '0' + p.m5 ;
		*s++ = '0' + p.m4 ;
		*s++ = '0' + p.m3 ;
		*s++ = '0' + p.m2 ;
		*s++ = '0' + p.m1 ;
		*s++ = '0' + p.m0 ;
		*s++ = 'E' ;
		if (fps & 0x1000) 
			{ /* Overflowed exponent - A79J bugs. */
			if (p.s & 4)
				{
				if (((*fpr).fp[0] & 0x7fffffff) >= 0x3fff0000)
					*s++ = '+' ;
				else
					*s++ = '-' ;
				}
			else
				*s++ = '+' ;
			*s++ = '0' + p.u2  ;
			}
		else
			{ /* Normal case. */
			if (p.s & 4)
		 		*s++ = '-' ;
		 	else
		 		*s++ = '+' ;
			}
		*s++ = '0' + p.e2 ;
		*s++ = '0' + p.e1 ;
		*s++ = '0' + p.e0 ;
		} /* normal or subnormal */
	} /* number */
if (fps & 0x200) 
	{ /* broken for now
	*s++ = '(' ;
	*s++ = 'i' ;
	*s++ = 'n' ;
	*s++ = 'e' ;
	*s++ = 'x' ;
	*s++ = 'a' ;
	*s++ = 'c' ;
	*s++ = 't' ;
	*s++ = ')' ;
	  broken for now */ }
*s++ = 0 ;
}

void doubletos(d,s)

double d ;
char *s ;

/* Prints double precision number d. */

{

if (mc68881==0)
	{ /* no 68881 */
	union { double d ; 
		struct  { unsigned s:1, e:11, f1:20 ; long f2; } i ; } equivalence ;

	equivalence.d = d ;
        if (equivalence.i.e == 0x7ff)
        	{
		if ((equivalence.i.f1 == 0) && (equivalence.i.f2 == 0))
			strcpy(s , (equivalence.i.s == 0) ? "Inf" : "-Inf") ;
		else
			strcpy(s , (equivalence.i.s == 0) ? "NaN" : "-NaN") ;
		}
        else
		strcpy(s, "sorry, no floating point");
	} /* no 68881 */
else
	{ /* 68881 */
	ext_fp fpr ;

	dtofpr( &d, &fpr ) ;
	fprtos( &fpr, s ) ;
	} /* 68881 */
}

/*
 *	The kernel's already determined whether there's a 68881.
 */
int MC68881Present ()

/*	Function to return 1 if physical 68881 is present, 0 if not. */

{
	extern int	fppstate;

	mc68881 = fppstate;
	return(mc68881);
}
