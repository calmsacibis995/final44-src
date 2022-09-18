/*	%M%	(Berkeley)	%I%	%E%
 *
 *	"long" fixed-point arithmetic package
 *
 *	This DEPENDS on a sign-filled arithmetic right-shift
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
#define ffix(x)		((fixed)((x)<<F_INTSHFT))
#define ffixd(x)	((fixed)(((x) * (float)(1<<F_INTSHFT)) + ((x)<0 ? -0.5 : 0.5)))
