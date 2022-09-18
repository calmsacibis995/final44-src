h48767
s 00002/00002/00496
d D 8.1 93/06/04 17:00:10 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00005/00498
d D 5.6 90/10/09 17:52:11 bostic 16 15
c new copyright notice
e
s 00001/00011/00502
d D 5.5 90/06/01 15:40:33 bostic 15 14
c new copyright notice
e
s 00026/00024/00487
d D 5.4 88/09/22 16:26:42 bostic 14 13
c update for ANSI C from Alex Zliu and John Gilmore
e
s 00010/00005/00501
d D 5.3 88/06/30 17:23:02 bostic 13 12
c install approved copyright notice
e
s 00016/00013/00490
d D 5.2 88/04/29 12:23:23 bostic 12 11
c add Berkeley specific copyright
e
s 00000/00000/00503
d D 5.1 87/11/30 18:42:13 bostic 11 10
c tahoe release
e
s 00052/00052/00451
d D 1.10 87/07/13 19:49:18 zliu 10 9
c clean-ups.
e
s 00030/00009/00473
d D 1.9 87/07/11 13:39:55 zliu 9 8
c making error handling consistent in support.c by calling
c infnan() in sqrt() and drem(); ifdef out those finite and (x!=x)'s.
e
s 00010/00003/00472
d D 1.8 87/07/11 12:25:27 zliu 8 7
c re-install -r1.4
e
s 00004/00002/00471
d D 1.7 87/07/10 20:28:31 zliu 7 6
c fixing bug in drem (reserved-operand fault).
e
s 00003/00010/00470
d D 1.6 87/07/10 17:55:00 zliu 6 5
c incorporating changes made by CSRG people(?)
e
s 00014/00014/00466
d D 1.5 87/07/07 01:06:11 zliu 5 4
c first shot at TAHOE.
e
s 00010/00003/00470
d D 1.4 86/11/02 23:12:17 elefunt 4 3
c fix bugs in drem when second arg is inf or NaN
e
s 00001/00001/00472
d D 1.3 86/04/26 20:37:26 zliu 3 2
c Under 4.3BSD (unsigned short) op (short) becomes (unsigned short)
c 
e
s 00002/00001/00471
d D 1.2 85/09/12 20:22:01 elefunt 2 1
c 4.3BSD version dated 09/12/85.
e
s 00472/00000/00000
d D 1.1 85/09/06 17:51:28 zliu 1 0
c date and time created 85/09/06 17:51:28 by zliu
e
u
U
t
T
I 1
D 12
/* 
E 12
I 12
/*
E 12
D 17
 * Copyright (c) 1985 Regents of the University of California.
D 12
 * 
 * Use and reproduction of this software are granted  in  accordance  with
 * the terms and conditions specified in  the  Berkeley  Software  License
 * Agreement (in particular, this entails acknowledgement of the programs'
 * source, and inclusion of this notice) with the additional understanding
 * that  all  recipients  should regard themselves as participants  in  an
 * ongoing  research  project and hence should  feel  obligated  to report
 * their  experiences (good or bad) with these elementary function  codes,
 * using "sendbug 4bsd-bugs@BERKELEY", to the authors.
E 12
I 12
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
D 15
 * Redistribution and use in source and binary forms are permitted
D 13
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 13
I 13
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 15
I 15
 * %sccs.include.redist.c%
E 15
E 13
D 16
 *
 * All recipients should regard themselves as participants in an ongoing
 * research project and hence should feel obligated to report their
 * experiences (good or bad) with these elementary function codes, using
 * the sendbug(8) program, to the authors.
E 16
E 12
 */

#ifndef lint
D 2
static char sccsid[] = "%W% (ELEFUNT) %G%";
E 2
I 2
D 12
static char sccsid[] =
"%Z%%M%	1.1 (Berkeley) 5/23/85; %I% (ucb.elefunt) %G%";
E 2
D 10
#endif not lint
E 10
I 10
#endif	/* not lint */
E 12
I 12
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 12
E 10

/* 
D 9
 * Some IEEE standard p754 recommended functions and remainder and sqrt for 
E 9
I 9
 * Some IEEE standard 754 recommended functions and remainder and sqrt for 
E 9
 * supporting the C elementary functions.
 ******************************************************************************
 * WARNING:
 *      These codes are developed (in double) to support the C elementary
 * functions temporarily. They are not universal, and some of them are very
 * slow (in particular, drem and sqrt is extremely inefficient). Each 
 * computer system should have its implementation of these functions using 
 * its own assembler.
 ******************************************************************************
 *
D 9
 * IEEE p754 required operations:
E 9
I 9
 * IEEE 754 required operations:
E 9
 *     drem(x,p) 
 *              returns  x REM y  =  x - [x/y]*y , where [x/y] is the integer
 *              nearest x/y; in half way case, choose the even one.
 *     sqrt(x) 
 *              returns the square root of x correctly rounded according to 
 *		the rounding mod.
 *
D 9
 * IEEE p754 recommended functions:
E 9
I 9
 * IEEE 754 recommended functions:
E 9
 * (a) copysign(x,y) 
 *              returns x with the sign of y. 
 * (b) scalb(x,N) 
 *              returns  x * (2**N), for integer values N.
 * (c) logb(x) 
 *              returns the unbiased exponent of x, a signed integer in 
 *              double precision, except that logb(0) is -INF, logb(INF) 
 *              is +INF, and logb(NAN) is that NAN.
 * (d) finite(x) 
 *              returns the value TRUE if -INF < x < +INF and returns 
 *              FALSE otherwise.
 *
 *
 * CODED IN C BY K.C. NG, 11/25/84;
 * REVISED BY K.C. NG on 1/22/85, 2/13/85, 3/24/85.
 */

I 14
#include "mathimpl.h"
E 14

D 5
#ifdef VAX      /* VAX D format */
E 5
I 5
D 10
#if (defined(VAX)||defined(TAHOE))      /* VAX D format */
E 10
I 10
#if defined(vax)||defined(tahoe)      /* VAX D format */
E 10
I 9
#include <errno.h>
E 9
E 5
D 14
    static unsigned short msign=0x7fff , mexp =0x7f80 ;
    static short  prep1=57, gap=7, bias=129           ;   
    static double novf=1.7E38, nunf=3.0E-39, zero=0.0 ;
E 14
I 14
    static const unsigned short msign=0x7fff , mexp =0x7f80 ;
    static const short  prep1=57, gap=7, bias=129           ;   
    static const double novf=1.7E38, nunf=3.0E-39, zero=0.0 ;
E 14
D 10
#else           /*IEEE double format */
E 10
I 10
#else	/* defined(vax)||defined(tahoe) */
E 10
D 14
    static unsigned short msign=0x7fff, mexp =0x7ff0  ;
    static short prep1=54, gap=4, bias=1023           ;
    static double novf=1.7E308, nunf=3.0E-308,zero=0.0;
E 14
I 14
    static const unsigned short msign=0x7fff, mexp =0x7ff0  ;
    static const short prep1=54, gap=4, bias=1023           ;
    static const double novf=1.7E308, nunf=3.0E-308,zero=0.0;
E 14
D 10
#endif
E 10
I 10
#endif	/* defined(vax)||defined(tahoe) */
E 10

double scalb(x,N)
double x; int N;
{
        int k;
D 14
        double scalb();
E 14

D 10
#ifdef NATIONAL
E 10
I 10
#ifdef national
E 10
        unsigned short *px=(unsigned short *) &x + 3;
D 5
#else /* VAX, SUN, ZILOG */
E 5
I 5
D 10
#else /* VAX, SUN, ZILOG, TAHOE */
E 10
I 10
#else	/* national */
E 10
E 5
        unsigned short *px=(unsigned short *) &x;
D 10
#endif
E 10
I 10
#endif	/* national */
E 10

        if( x == zero )  return(x); 

D 5
#ifdef VAX
E 5
I 5
D 10
#if (defined(VAX)||defined(TAHOE))
E 10
I 10
#if defined(vax)||defined(tahoe)
E 10
E 5
        if( (k= *px & mexp ) != ~msign ) {
D 9
            if( N<-260) return(nunf*nunf); else if(N>260) return(novf+novf);
E 9
I 9
            if (N < -260)
		return(nunf*nunf);
	    else if (N > 260) {
D 14
		extern double infnan(),copysign();
E 14
		return(copysign(infnan(ERANGE),x));
	    }
E 9
D 10
#else   /* IEEE */
E 10
I 10
#else	/* defined(vax)||defined(tahoe) */
E 10
        if( (k= *px & mexp ) != mexp ) {
            if( N<-2100) return(nunf*nunf); else if(N>2100) return(novf+novf);
            if( k == 0 ) {
                 x *= scalb(1.0,(int)prep1);  N -= prep1; return(scalb(x,N));}
D 10
#endif
E 10
I 10
#endif	/* defined(vax)||defined(tahoe) */
E 10

            if((k = (k>>gap)+ N) > 0 )
                if( k < (mexp>>gap) ) *px = (*px&~mexp) | (k<<gap);
                else x=novf+novf;               /* overflow */
            else
                if( k > -prep1 ) 
                                        /* gradual underflow */
                    {*px=(*px&~mexp)|(short)(1<<gap); x *= scalb(1.0,k-1);}
                else
                return(nunf*nunf);
            }
        return(x);
}


double copysign(x,y)
double x,y;
{
D 10
#ifdef NATIONAL
E 10
I 10
#ifdef national
E 10
        unsigned short  *px=(unsigned short *) &x+3,
                        *py=(unsigned short *) &y+3;
D 5
#else /* VAX, SUN, ZILOG */
E 5
I 5
D 10
#else /* VAX, SUN, ZILOG,TAHOE */
E 10
I 10
#else	/* national */
E 10
E 5
        unsigned short  *px=(unsigned short *) &x,
                        *py=(unsigned short *) &y;
D 10
#endif
E 10
I 10
#endif	/* national */
E 10

D 5
#ifdef VAX
E 5
I 5
D 10
#if (defined(VAX)||defined(TAHOE))
E 10
I 10
#if defined(vax)||defined(tahoe)
E 10
E 5
        if ( (*px & mexp) == 0 ) return(x);
D 10
#endif
E 10
I 10
#endif	/* defined(vax)||defined(tahoe) */
E 10

        *px = ( *px & msign ) | ( *py & ~msign );
        return(x);
}

double logb(x)
double x; 
{

D 10
#ifdef NATIONAL
E 10
I 10
#ifdef national
E 10
        short *px=(short *) &x+3, k;
D 5
#else /* VAX, SUN, ZILOG */
E 5
I 5
D 10
#else /* VAX, SUN, ZILOG, TAHOE */
E 10
I 10
#else	/* national */
E 10
E 5
        short *px=(short *) &x, k;
D 10
#endif
E 10
I 10
#endif	/* national */
E 10

D 5
#ifdef VAX
E 5
I 5
D 10
#if (defined(VAX)||defined(TAHOE))
E 10
I 10
#if defined(vax)||defined(tahoe)
E 10
E 5
D 3
        return( ((*px & mexp)>>gap) - bias);
E 3
I 3
        return (int)(((*px&mexp)>>gap)-bias);
E 3
D 10
#else /* IEEE */
E 10
I 10
#else	/* defined(vax)||defined(tahoe) */
E 10
        if( (k= *px & mexp ) != mexp )
            if ( k != 0 )
                return ( (k>>gap) - bias );
            else if( x != zero)
                return ( -1022.0 );
            else        
                return(-(1.0/zero));    
        else if(x != x)
            return(x);
        else
            {*px &= msign; return(x);}
D 10
#endif
E 10
I 10
#endif	/* defined(vax)||defined(tahoe) */
E 10
}

finite(x)
double x;    
{
D 5
#ifdef VAX
E 5
I 5
D 10
#if (defined(VAX)||defined(TAHOE))
E 10
I 10
#if defined(vax)||defined(tahoe)
E 10
E 5
D 9
        return(1.0);
E 9
I 9
        return(1);
E 9
D 10
#else  /* IEEE */
#ifdef NATIONAL
E 10
I 10
#else	/* defined(vax)||defined(tahoe) */
#ifdef national
E 10
        return( (*((short *) &x+3 ) & mexp ) != mexp );
D 10
#else /* SUN, ZILOG */
E 10
I 10
#else	/* national */
E 10
        return( (*((short *) &x ) & mexp ) != mexp );
D 10
#endif
#endif
E 10
I 10
#endif	/* national */
#endif	/* defined(vax)||defined(tahoe) */
E 10
}

double drem(x,p)
double x,p;
{
        short sign;
D 14
        double hp,dp,tmp,drem(),scalb();
E 14
I 14
        double hp,dp,tmp;
E 14
        unsigned short  k; 
D 10
#ifdef NATIONAL
E 10
I 10
#ifdef national
E 10
        unsigned short
              *px=(unsigned short *) &x  +3, 
              *pp=(unsigned short *) &p  +3,
              *pd=(unsigned short *) &dp +3,
              *pt=(unsigned short *) &tmp+3;
D 5
#else /* VAX, SUN, ZILOG */
E 5
I 5
D 10
#else /* VAX, SUN, ZILOG, TAHOE */
E 10
I 10
#else	/* national */
E 10
E 5
        unsigned short
              *px=(unsigned short *) &x  , 
              *pp=(unsigned short *) &p  ,
              *pd=(unsigned short *) &dp ,
              *pt=(unsigned short *) &tmp;
D 10
#endif
E 10
I 10
#endif	/* national */
E 10

        *pp &= msign ;

D 5
#ifdef VAX
E 5
I 5
D 10
#if (defined(VAX)||defined(TAHOE))
E 10
I 10
#if defined(vax)||defined(tahoe)
E 10
E 5
D 4
        if( ( *px & mexp ) == ~msign || p == zero )
E 4
I 4
D 6
        if( ( *px & mexp ) == ~msign )
E 6
I 6
D 8
        if( ( *px & mexp ) == ~msign || p == zero )
E 8
I 8
D 9
        if( ( *px & mexp ) == ~msign )
E 9
I 9
        if( ( *px & mexp ) == ~msign )	/* is x a reserved operand? */
E 9
E 8
E 6
E 4
D 10
#else /* IEEE */
E 10
I 10
#else	/* defined(vax)||defined(tahoe) */
E 10
D 4
        if( ( *px & mexp ) == mexp || p == zero )
E 4
I 4
D 6
        if( ( *px & mexp ) == mexp )
E 6
I 6
D 8
        if( ( *px & mexp ) == mexp || p == zero )
E 8
I 8
        if( ( *px & mexp ) == mexp )
E 8
E 6
E 4
D 10
#endif
E 10
I 10
#endif	/* defined(vax)||defined(tahoe) */
E 10
I 4
D 6
		return  (x-p)-(x-p);	/* create nan if x is inf */
	if(p==zero) return zero/zero;
D 5
#ifdef VAX
E 5
I 5
#if (defined(VAX)||defined(TAHOE))
E 5
        if( ( *pp & mexp ) == ~msign )
#else /* IEEE */
        if( ( *pp & mexp ) == mexp )
#endif
		{ if (p != p) return p; else return x;}
E 6
E 4
D 7

E 7
I 6
D 8
                return( (x != x)? x:zero/zero );
E 8
I 8
		return  (x-p)-(x-p);	/* create nan if x is inf */
D 9
	if(p==zero) return zero/zero;
E 9
I 9
	if (p == zero) {
E 9
D 10
#if (defined(VAX)||defined(TAHOE))
E 10
I 10
#if defined(vax)||defined(tahoe)
E 10
D 9
        if( ( *pp & mexp ) == ~msign )
E 9
I 9
D 14
		extern double infnan();
E 14
		return(infnan(EDOM));
D 10
#else
E 10
I 10
#else	/* defined(vax)||defined(tahoe) */
E 10
		return zero/zero;
D 10
#endif
E 10
I 10
#endif	/* defined(vax)||defined(tahoe) */
E 10
	}

D 10
#if (defined(VAX)||defined(TAHOE))
E 10
I 10
#if defined(vax)||defined(tahoe)
E 10
        if( ( *pp & mexp ) == ~msign )	/* is p a reserved operand? */
E 9
D 10
#else /* IEEE */
E 10
I 10
#else	/* defined(vax)||defined(tahoe) */
E 10
        if( ( *pp & mexp ) == mexp )
D 10
#endif
E 10
I 10
#endif	/* defined(vax)||defined(tahoe) */
E 10
		{ if (p != p) return p; else return x;}
E 8
E 6
D 4
                return( (x != x)? x:zero/zero );
E 4

        else  if ( ((*pp & mexp)>>gap) <= 1 ) 
                /* subnormal p, or almost subnormal p */
            { double b; b=scalb(1.0,(int)prep1);
              p *= b; x = drem(x,p); x *= b; return(drem(x,p)/b);}
        else  if ( p >= novf/2)
            { p /= 2 ; x /= 2; return(drem(x,p)*2);}
        else 
            {
                dp=p+p; hp=p/2;
                sign= *px & ~msign ;
                *px &= msign       ;
                while ( x > dp )
                    {
                        k=(*px & mexp) - (*pd & mexp) ;
                        tmp = dp ;
                        *pt += k ;

D 5
#ifdef VAX
E 5
I 5
D 10
#if (defined(VAX)||defined(TAHOE))
E 10
I 10
#if defined(vax)||defined(tahoe)
E 10
E 5
                        if( x < tmp ) *pt -= 128 ;
D 10
#else /* IEEE */
E 10
I 10
#else	/* defined(vax)||defined(tahoe) */
E 10
                        if( x < tmp ) *pt -= 16 ;
D 10
#endif
E 10
I 10
#endif	/* defined(vax)||defined(tahoe) */
E 10

                        x -= tmp ;
                    }
                if ( x > hp )
                    { x -= p ;  if ( x >= hp ) x -= p ; }

D 7
		*px = *px ^ sign;
E 7
I 7
D 10
#if (defined(VAX)||defined(TAHOE))
E 10
I 10
#if defined(vax)||defined(tahoe)
E 10
		if (x)
D 10
#endif
E 10
I 10
#endif	/* defined(vax)||defined(tahoe) */
E 10
			*px ^= sign;
E 7
                return( x);

            }
}
I 14


E 14
double sqrt(x)
double x;
{
        double q,s,b,r;
D 14
        double logb(),scalb();
        double t,zero=0.0;
        int m,n,i,finite();
E 14
I 14
        double t;
	double const zero=0.0;
        int m,n,i;
E 14
D 5
#ifdef VAX
E 5
I 5
D 10
#if (defined(VAX)||defined(TAHOE))
E 10
I 10
#if defined(vax)||defined(tahoe)
E 10
E 5
        int k=54;
D 10
#else   /* IEEE */
E 10
I 10
#else	/* defined(vax)||defined(tahoe) */
E 10
        int k=51;
D 10
#endif
E 10
I 10
#endif	/* defined(vax)||defined(tahoe) */
E 10

    /* sqrt(NaN) is NaN, sqrt(+-0) = +-0 */
        if(x!=x||x==zero) return(x);

    /* sqrt(negative) is invalid */
D 9
        if(x<zero) return(zero/zero);
E 9
I 9
        if(x<zero) {
D 10
#if (defined(VAX)||defined(TAHOE))
E 10
I 10
#if defined(vax)||defined(tahoe)
E 10
D 14
		extern double infnan();
E 14
		return (infnan(EDOM));	/* NaN */
D 10
#else	/* IEEE double */
E 10
I 10
#else	/* defined(vax)||defined(tahoe) */
E 10
		return(zero/zero);
D 10
#endif
E 10
I 10
#endif	/* defined(vax)||defined(tahoe) */
E 10
	}
E 9

    /* sqrt(INF) is INF */
        if(!finite(x)) return(x);               

    /* scale x to [1,4) */
        n=logb(x);
        x=scalb(x,-n);
        if((m=logb(x))!=0) x=scalb(x,-m);       /* subnormal number */
        m += n; 
        n = m/2;
        if((n+n)!=m) {x *= 2; m -=1; n=m/2;}

    /* generate sqrt(x) bit by bit (accumulating in q) */
            q=1.0; s=4.0; x -= 1.0; r=1;
            for(i=1;i<=k;i++) {
                t=s+1; x *= 4; r /= 2;
                if(t<=x) {
                    s=t+t+2, x -= t; q += r;}
                else
                    s *= 2;
                }
            
    /* generate the last bit and determine the final rounding */
            r/=2; x *= 4; 
            if(x==zero) goto end; 100+r; /* trigger inexact flag */
            if(s<x) {
                q+=r; x -=s; s += 2; s *= 2; x *= 4;
                t = (x-s)-5; 
                b=1.0+3*r/4; if(b==1.0) goto end; /* b==1 : Round-to-zero */
                b=1.0+r/4;   if(b>1.0) t=1;	/* b>1 : Round-to-(+INF) */
                if(t>=0) q+=r; }	      /* else: Round-to-nearest */
            else { 
                s *= 2; x *= 4; 
                t = (x-s)-1; 
                b=1.0+3*r/4; if(b==1.0) goto end;
                b=1.0+r/4;   if(b>1.0) t=1;
                if(t>=0) q+=r; }
            
end:        return(scalb(q,n));
}

#if 0
/* DREM(X,Y)
 * RETURN X REM Y =X-N*Y, N=[X/Y] ROUNDED (ROUNDED TO EVEN IN THE HALF WAY CASE)
 * DOUBLE PRECISION (VAX D format 56 bits, IEEE DOUBLE 53 BITS)
 * INTENDED FOR ASSEMBLY LANGUAGE
 * CODED IN C BY K.C. NG, 3/23/85, 4/8/85.
 *
 * Warning: this code should not get compiled in unless ALL of
 * the following machine-dependent routines are supplied.
 * 
 * Required machine dependent functions (not on a VAX):
 *     swapINX(i): save inexact flag and reset it to "i"
 *     swapENI(e): save inexact enable and reset it to "e"
 */

double drem(x,y)	
double x,y;
{

D 10
#ifdef NATIONAL		/* order of words in floating point number */
E 10
I 10
#ifdef national		/* order of words in floating point number */
E 10
D 14
	static n0=3,n1=2,n2=1,n3=0;
E 14
I 14
	static const n0=3,n1=2,n2=1,n3=0;
E 14
D 5
#else /* VAX, SUN, ZILOG */
E 5
I 5
#else /* VAX, SUN, ZILOG, TAHOE */
E 5
D 14
	static n0=0,n1=1,n2=2,n3=3;
E 14
I 14
	static const n0=0,n1=1,n2=2,n3=3;
E 14
#endif

D 14
    	static unsigned short mexp =0x7ff0, m25 =0x0190, m57 =0x0390;
	static double zero=0.0;
E 14
I 14
    	static const unsigned short mexp =0x7ff0, m25 =0x0190, m57 =0x0390;
	static const double zero=0.0;
E 14
	double hy,y1,t,t1;
	short k;
	long n;
	int i,e; 
	unsigned short xexp,yexp, *px  =(unsigned short *) &x  , 
	      		nx,nf,	  *py  =(unsigned short *) &y  ,
	      		sign,	  *pt  =(unsigned short *) &t  ,
	      			  *pt1 =(unsigned short *) &t1 ;

	xexp = px[n0] & mexp ;	/* exponent of x */
	yexp = py[n0] & mexp ;	/* exponent of y */
	sign = px[n0] &0x8000;	/* sign of x     */

/* return NaN if x is NaN, or y is NaN, or x is INF, or y is zero */
	if(x!=x) return(x); if(y!=y) return(y);	     /* x or y is NaN */
	if( xexp == mexp )   return(zero/zero);      /* x is INF */
	if(y==zero) return(y/y);

/* save the inexact flag and inexact enable in i and e respectively
 * and reset them to zero
 */
	i=swapINX(0);	e=swapENI(0);	

/* subnormal number */
	nx=0;
	if(yexp==0) {t=1.0,pt[n0]+=m57; y*=t; nx=m57;}

/* if y is tiny (biased exponent <= 57), scale up y to y*2**57 */
	if( yexp <= m57 ) {py[n0]+=m57; nx+=m57; yexp+=m57;}

	nf=nx;
	py[n0] &= 0x7fff;	
	px[n0] &= 0x7fff;

/* mask off the least significant 27 bits of y */
	t=y; pt[n3]=0; pt[n2]&=0xf800; y1=t;

/* LOOP: argument reduction on x whenever x > y */
loop:
	while ( x > y )
	{
	    t=y;
	    t1=y1;
	    xexp=px[n0]&mexp;	  /* exponent of x */
	    k=xexp-yexp-m25;
	    if(k>0) 	/* if x/y >= 2**26, scale up y so that x/y < 2**26 */
		{pt[n0]+=k;pt1[n0]+=k;}
	    n=x/t; x=(x-n*t1)-n*(t-t1);
	}	
    /* end while (x > y) */

	if(nx!=0) {t=1.0; pt[n0]+=nx; x*=t; nx=0; goto loop;}

/* final adjustment */

	hy=y/2.0;
	if(x>hy||((x==hy)&&n%2==1)) x-=y; 
	px[n0] ^= sign;
	if(nf!=0) { t=1.0; pt[n0]-=nf; x*=t;}

/* restore inexact flag and inexact enable */
	swapINX(i); swapENI(e);	

	return(x);	
}
#endif

#if 0
/* SQRT
 * RETURN CORRECTLY ROUNDED (ACCORDING TO THE ROUNDING MODE) SQRT
 * FOR IEEE DOUBLE PRECISION ONLY, INTENDED FOR ASSEMBLY LANGUAGE
 * CODED IN C BY K.C. NG, 3/22/85.
 *
 * Warning: this code should not get compiled in unless ALL of
 * the following machine-dependent routines are supplied.
 * 
 * Required machine dependent functions:
 *     swapINX(i)  ...return the status of INEXACT flag and reset it to "i"
 *     swapRM(r)   ...return the current Rounding Mode and reset it to "r"
 *     swapENI(e)  ...return the status of inexact enable and reset it to "e"
 *     addc(t)     ...perform t=t+1 regarding t as a 64 bit unsigned integer
 *     subc(t)     ...perform t=t-1 regarding t as a 64 bit unsigned integer
 */

D 14
static unsigned long table[] = {
E 14
I 14
static const unsigned long table[] = {
E 14
0, 1204, 3062, 5746, 9193, 13348, 18162, 23592, 29598, 36145, 43202, 50740,
58733, 67158, 75992, 85215, 83599, 71378, 60428, 50647, 41945, 34246, 27478,
21581, 16499, 12183, 8588, 5674, 3403, 1742, 661, 130, };

double newsqrt(x)
double x;
{
D 14
        double y,z,t,addc(),subc(),b54=134217728.*134217728.; /* b54=2**54 */
        long mx,scalx,mexp=0x7ff00000;
E 14
I 14
        double y,z,t,addc(),subc()
	double const b54=134217728.*134217728.; /* b54=2**54 */
        long mx,scalx;
	long const mexp=0x7ff00000;
E 14
        int i,j,r,e,swapINX(),swapRM(),swapENI();       
        unsigned long *py=(unsigned long *) &y   ,
                      *pt=(unsigned long *) &t   ,
                      *px=(unsigned long *) &x   ;
D 10
#ifdef NATIONAL         /* ordering of word in a floating point number */
E 10
I 10
#ifdef national         /* ordering of word in a floating point number */
E 10
D 14
        int n0=1, n1=0; 
E 14
I 14
        const int n0=1, n1=0; 
E 14
#else
D 14
        int n0=0, n1=1; 
E 14
I 14
        const int n0=0, n1=1; 
E 14
#endif
/* Rounding Mode:  RN ...round-to-nearest 
 *                 RZ ...round-towards 0
 *                 RP ...round-towards +INF
 *		   RM ...round-towards -INF
 */
D 14
        int RN=0,RZ=1,RP=2,RM=3;/* machine dependent: work on a Zilog Z8070
E 14
I 14
        const int RN=0,RZ=1,RP=2,RM=3;
				/* machine dependent: work on a Zilog Z8070
E 14
                                 * and a National 32081 & 16081
                                 */

/* exceptions */
	if(x!=x||x==0.0) return(x);  /* sqrt(NaN) is NaN, sqrt(+-0) = +-0 */
	if(x<0) return((x-x)/(x-x)); /* sqrt(negative) is invalid */
        if((mx=px[n0]&mexp)==mexp) return(x);  /* sqrt(+INF) is +INF */

/* save, reset, initialize */
        e=swapENI(0);   /* ...save and reset the inexact enable */
        i=swapINX(0);   /* ...save INEXACT flag */
        r=swapRM(RN);   /* ...save and reset the Rounding Mode to RN */
        scalx=0;

/* subnormal number, scale up x to x*2**54 */
        if(mx==0) {x *= b54 ; scalx-=0x01b00000;}

/* scale x to avoid intermediate over/underflow:
 * if (x > 2**512) x=x/2**512; if (x < 2**-512) x=x*2**512 */
        if(mx>0x5ff00000) {px[n0] -= 0x20000000; scalx+= 0x10000000;}
        if(mx<0x1ff00000) {px[n0] += 0x20000000; scalx-= 0x10000000;}

/* magic initial approximation to almost 8 sig. bits */
        py[n0]=(px[n0]>>1)+0x1ff80000;
        py[n0]=py[n0]-table[(py[n0]>>15)&31];

/* Heron's rule once with correction to improve y to almost 18 sig. bits */
        t=x/y; y=y+t; py[n0]=py[n0]-0x00100006; py[n1]=0;

/* triple to almost 56 sig. bits; now y approx. sqrt(x) to within 1 ulp */
        t=y*y; z=t;  pt[n0]+=0x00100000; t+=z; z=(x-z)*y; 
        t=z/(t+x) ;  pt[n0]+=0x00100000; y+=t;

/* twiddle last bit to force y correctly rounded */ 
        swapRM(RZ);     /* ...set Rounding Mode to round-toward-zero */
        swapINX(0);     /* ...clear INEXACT flag */
        swapENI(e);     /* ...restore inexact enable status */
        t=x/y;          /* ...chopped quotient, possibly inexact */
        j=swapINX(i);   /* ...read and restore inexact flag */
        if(j==0) { if(t==y) goto end; else t=subc(t); }  /* ...t=t-ulp */
        b54+0.1;        /* ..trigger inexact flag, sqrt(x) is inexact */
        if(r==RN) t=addc(t);            /* ...t=t+ulp */
        else if(r==RP) { t=addc(t);y=addc(y);}/* ...t=t+ulp;y=y+ulp; */
        y=y+t;                          /* ...chopped sum */
        py[n0]=py[n0]-0x00100000;       /* ...correctly rounded sqrt(x) */
end:    py[n0]=py[n0]+scalx;            /* ...scale back y */
        swapRM(r);                      /* ...restore Rounding Mode */
        return(y);
}
#endif
E 1
