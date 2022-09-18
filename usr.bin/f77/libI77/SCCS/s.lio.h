h39241
s 00005/00004/00064
d D 5.4 91/04/12 15:23:22 bostic 5 4
c new copyright; att/bsd/shared
e
s 00002/00002/00066
d D 5.3 90/05/13 11:53:25 bostic 4 3
c gcc work-around; cpp doesn't do replacement the same as Reiser's.
e
s 00002/00000/00066
d D 5.2 85/07/30 16:40:23 jerry 3 2
c implement namelist
e
s 00007/00001/00059
d D 5.1 85/06/07 23:37:34 kre 2 1
c Add copyright
e
s 00060/00000/00000
d D 1.1 81/02/18 18:02:30 dlw 1 0
c date and time created 81/02/18 18:02:30 by dlw
e
u
U
t
T
I 1
D 5
/*
D 2
char id_lio[] = "%W%";
E 2
I 2
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
E 5
E 2
 *
I 2
 *	%W% (Berkeley) %G%
 */

/*
E 2
 * copy of ftypes from the compiler
 * variable types numeric assumptions:
 *	int < reals < complexes
 *	TYDREAL-TYREAL = TYDCOMPLEX-TYCOMPLEX
 */

#define TYUNKNOWN 0
#define TYADDR 1
#define TYSHORT 2
#define TYLONG 3
#define TYREAL 4
#define TYDREAL 5
#define TYCOMPLEX 6
#define TYDCOMPLEX 7
#define TYLOGICAL 8
#define TYCHAR 9
#define TYSUBR 10
#define TYERROR 11

#define NTYPES (TYERROR+1)
 
#define	LINE	80
#define LINTW	(strlen(buf))
#define	LLOGW	3
#define LSTRW	(len+2)
#define	LLOW	1.0e-1
D 4
#define	LHIGH	1.0e+LFD
#define LDHIGH	1.0e+LDFD
E 4
I 4
#define	LHIGH	1.0e+6			/* 1.0e+LFD */
#define LDHIGH	1.0e+14			/* 1.0e+LDFD */
E 4
#define	LFD	6
#define	LFW	(LFD+4)
#define LDFD	14
#define LDFW	(LDFD+4)
#define	LED	LFD
#define	LEW	LFW+4
#define	LEE	2
#define LDED	LDFD
#define LDEW	LDFW+4
#define LDEE	2
#define LCW	(width(a)+width(b)+5)
#define LDCW	(dwidth(a)+dwidth(b)+5)

#define abs(z)	(z<0?-z:z)
#define width(z) ((z!=0.0 && (abs(z)>=LHIGH || abs(z)<LLOW))?LEW:LFW)
#define dwidth(z) ((z!=0.0 && (abs(z)>=LDHIGH || abs(z)<LLOW))?LDEW:LDFW)
#define ERR(x)	if(n=(x)) err(n>0?errflag:endflag,n,"list io")
I 3
#define ERRCHK(x)	if(n=(x)) goto got_err;
#define chk_len(w) if(recpos+w > line_len) PUT('\n');
E 3

typedef union
{	short	flshort;
	ftnint	flint;
	float	flreal;
	double	fldouble;
} flex;

extern int (*lioproc)();
extern flag leof;
extern ioflag lquit,l_first;
extern int lcount,line_len;
E 1
