/*	macdefs.h	1.7	88/05/31	*/

#ifndef _MACDEFS_
#define _MACDEFS_

#define makecc(val,i)	lastcon = (lastcon<<8)|((val<<24)>>24);		

#define ARGINIT		SZINT
#define AUTOINIT	(13*SZINT)

/*
 * Storage space requirements.
 */
#define SZCHAR		8
#define SZINT		32
#define SZFLOAT		32
#define SZDOUBLE	64
#define SZLONG		32
#define SZSHORT		16
#define SZPOINT		32

/*
 * Alignment constraints
 */
#define ALCHAR		8
#define ALINT		32
#define ALFLOAT		32
#define ALDOUBLE	32
#define ALLONG		32
#define ALSHORT		16
#define ALPOINT		32
#define ALSTRUCT	8
#define ALSTACK		32	

#define ACONFMT	"$0x%lx"	/* format for printing address constants */
#define CONFMT	"%ld"		/* format for printing constants */
#define LABFMT	"L%d"		/* format for printing labels */

typedef	long	CONSZ;		/* size in which constants are converted */
typedef	unsigned long	U_CONSZ;/* unsigned version of the above */
typedef	long	OFFSZ;		/* size in which offsets are kept */

#define CCTRANS(x) x		/* character set macro */

/*
 * Register cookie for stack pointer.
 */
#define STKREG	13		/* stack pointer */

/*
 * Maximum and minimum register variables
 */
#define MINRVAR	6		/* use R6 thru ... */
#define MAXRVAR	12		/* ... R12 */

#define BACKAUTO		/* stack grows negatively for automatics */
#define BACKTEMP		/* stack grows negatively for temporaries */
/*#define FIELDOPS	/* no hardware field support */
/*#define RTOLBYTES	/* bytes are number from left to right */
#define ADDROREG		/* can unwind &o, where o is OREG */

#define ASSTRINGS		/* assembler handles string initializations */
#define STABDOT			/* assembler understands .stabd */
#define LCOMM			/* assembler supports .lcomm */
#define SPRECC			/* double only arithmetic not supported */

#define ENUMSIZE(high,low) INT	/* enums are always stored in full int */

#define FIXDEF(p)	if (!nerrors) outstab(p); else
#define FIXARG(p)	if (!nerrors) fixarg(p); else
#define FIXSTRUCT(p,q)	if (!nerrors) outstruct(p,q); else

#ifndef ncopy
#define	ncopy(q, p)	((q)->in = (p)->in)
#endif

#define aobeg()
#define aocode(p)
#define aoend()

#define	PRTDCON			/* use machine-specific prtdcon routine */
extern	prtdcon();
#endif
