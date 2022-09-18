/*	%M%	(Berkeley)	%I%	%E%
 *
 *	"long" fixed-point arithmetic package library
 *
 *	This DEPENDS on a sign-filled arithmetic right-shift
 */

#include "fixpoint.h"


#define F_INTEGER	(((1<<F_INTSHFT)-1)<<F_INTSHFT)
#define F_FRACTION	((1<<F_INTSHFT)-1)
#define F_FRACT		((1<<F_QSHFT)-1)
#define	F_SIGN_BIT	(1 << ((F_INTSHFT * 2) - 1))


/*----------------------------------------------------------------------------*
 | Routine:	fmult (fixed x, fixed y)
 |
 | Results:	returns fixed-point product of x and y (fixed-point numbers)
 |
 | Bugs:	Requires arithmetic right-shift
 *----------------------------------------------------------------------------*/

fixed fmult(x, y)
register fixed x;
register fixed y;
{
    return
    ((x >> F_QSHFT) * (y >> F_QSHFT))			/* int * int */
    + (((x >> F_QSHFT) * (y & F_FRACT)) >> F_QSHFT)	/* int * fract */ 
    + (((y >> F_QSHFT) * (x & F_FRACT)) >> F_QSHFT);	/* fract * int */
}


/*----------------------------------------------------------------------------*
 | Routine:	fdiv (fixed x, fixed y)
 |
 | Results:	returns the fixed-point quotient of x / y (fixed-point numbers)
 |
 | Bugs:	returns largest possible numbers on divide by zero.
 |		Requires arithmetic right-shift
 *----------------------------------------------------------------------------*/

fixed fdiv(x, y)
register fixed x;
register fixed y;
{
    register int i = F_INTSHFT;
    register fixed temp;

    if (y == 0)
	return (x < 0 ? (fixed) F_SIGN_BIT : (fixed)~F_SIGN_BIT);

    while (((temp = x << 1) & F_SIGN_BIT) == (x & F_SIGN_BIT)) {
	x = temp;
	i--;
    }
    while (!(y & 1)) {
	y >>= 1;
	i--;
    }
    if(i<0)
	return ((x / y) >> -i);
    return ((x / y) << i);
}
