/*	%M%	(Berkeley)	%I%	%E%
 *
 *	Fixed-Point Arithmetic Package Library
 *
 *	This DEPENDS on a sign-filled arithmetic right-shift and 8-bit bytes
 *
 *	A Fixed point number is stored, half integer, half fraction, into a
 *	variable of type "fixed" (defined here as a "long").  Fixed point
 *	numbers may be directly added, subtracted and compared against each
 *	other and zero.  They may not be compared with regular integers or
 *	floating-point numbers.  Other supported operations are listed below.
 *	As in normal arithmetic operations, overflow and underflow are not
 *	detected.  Division by zero results in the largest possible (positive
 *	or negative) fixed-point number.
 *
 * The following "functions" return fixed-point numbers:
 *	fadd(x, y)	add two fixed-point numbers.  It is also perfectly
 *			legal to simply perform "x + y" instead.
 *	fsub(x, y)	subtract y from x, if both are fixed-point numbers.
 *			"x - y" will work also.
 *	fmult(x, y)	multiply fixed point numbers x and y.  This is a
 *			true function call.  Do NOT use "x * y"
 *	fdiv(x, y)	divide fixed point number x by y.  This is also a
 *			true function call.
 *	ffix(x)		convert (long, integer, short) x to fixed-point
 *	ffixd(x)	convert (float, double) x to fixed-point
 *			NOTE:  THIS MACRO USES "x" TWICE.
 *
 * The following "functions" return "int"s:
 *	fint(x)		return integral portion of fixed-point number "x"
 *	fintr(x)	like "fint", but x is rounded up first
 */

typedef long fixed;

#define	F_QSHFT		(sizeof(fixed) * 2)
#define F_INTSHFT	(sizeof(fixed) * 4)

/*(old )#define	fmult(x,y)	(((x)>>F_QSHFT) * ((y)>>F_QSHFT)) */
/*(defs)#define fdiv(x,y)	(((x) / ((y)>>F_QSHFT))<<F_QSHFT) */
#define fadd(x,y)	((x) + (y))
#define fsub(x,y)	((x) - (y))
#define fint(x)		((int)((x)>>F_INTSHFT))
#define fintr(x)	((int)(((x)+(1<<(F_INTSHFT-1)))>>F_INTSHFT))
#define ffix(x)		((fixed)(((fixed)(x))<<F_INTSHFT))
#define ffixd(x)	((fixed)(((x) * (double)(1<<F_INTSHFT)) + ((x)<0 ? -0.5 : 0.5)))
