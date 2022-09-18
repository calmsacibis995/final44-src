/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	fpascii.h,v $
 * Revision 2.3  89/02/25  19:40:29  gm0w
 * 	Changes for cleanup.
 * 
 */
/*      @(#)fpascii.h 1.1 86/02/03 SMI      */

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

#define FP0     19
#define FP7     40
#define FPC     43
#define FPS     44
#define FPI     45
#define FPS_CODE        46
#define FPS_FLAGS       47

extern void ltofpr(/* l, fpr */) ;

long fp_reg_address ; /* address of first word of register image */

/*
 *	long l ;
 *	ext_fp *fpr ;
 *
 * 	Converts long l to floating point register at fpr.
 */

extern void dtofpr(/* d, fpr */) ;

/*
 *	double *d ;
 *	ext_fp *fpr ;
 *
 * 	Converts double at d to floating point register at fpr.
 */

extern int fprtop(/* fpr, p */) ;

/*
 *	ext_fp *fpr
 *	char p[12]
 * 
 * 	Converts floating point register at fpr to 
 *	68881 packed bcd record at p.
 *	Function result is fps register.
 */

void	fprtos(/* fpr, s */) ;

/*
 *	ext_fp *fpr ;
 *	char *s ;
 *
 *	Converts floating point register at fpr to string at s.
 */

void	doubletos (/* d, s */) ;

/*
 *	double d ;
 *	char *s ;
 *
 *	Prints double precision number d. 
 */

int	mc68881 ;

int	M68881Present() ;

/*
 *	Returns 0 if physical 68881 present, 1 if absent. 
 */

