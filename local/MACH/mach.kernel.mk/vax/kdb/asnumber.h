/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	asnumber.h,v $
 * Revision 2.5  89/03/09  22:16:41  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  20:21:00  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  88/12/19  02:54:01  mwyoung
 * 	Remove more lint.
 * 	[88/12/17            mwyoung]
 * 
 *  3-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University.
 *	Delinted for kernel use.
 *
 */

/*
 *	Copyright (c) 1982 Regents of the University of California
 *	@(#)asnumber.h 4.3 2/14/82
 */

union Ib_int{		/* byte */
	u_char	Ib_uchar[1];
	char	Ichar;
};
union Iw_int{		/* word */
	u_char	Iw_uchar[2];
	u_short	Iw_ushort[1];
	short	Iw_short;
};
union Il_int{		/* long word */
	u_char	Il_uchar[4];
	u_short	Il_ushort[2];
	u_int	Il_ulong[1];
	int	Il_long;
};

union Iq_int{		/* quad word */
	u_char	Iq_uchar[8];
	u_short	Iq_ushort[4];
	u_int	Iq_ulong[2];
};

union Io_int{		/* octal word */
	u_char	Io_uchar[16];
	u_short	Io_ushort[8];
	u_int	Io_ulong[4];
	union	Iq_int	Io_quad[2];
};

union Ff_float{
	u_char	Ff_uchar[4];
	u_short	Ff_ushort[2];
	u_int	Ff_ulong[1];
	float	Ff_value;
};

union Fd_float{
	u_char	Fd_uchar[8];
	u_short	Fd_ushort[4];
	u_int	Fd_ulong[2];
	double	Fd_value;
};

union Fg_float{
	u_char	Fg_uchar[8];
	u_short	Fg_ushort[4];
	u_int	Fg_ulong[2];
};

union Fh_float{
	u_char	Fh_uchar[16];
	u_short	Fh_ushort[8];
	u_int	Fh_ulong[4];
};

struct	as_number{
	union {
		union Ib_int	numIb_int;
		union Iw_int	numIw_int;
		union Il_int	numIl_int;
		union Iq_int	numIq_int;
		union Io_int	numIo_int;
		union Ff_float	numFf_float;
		union Fd_float	numFd_float;
		union Fg_float	numFg_float;
		union Fh_float	numFh_float;
	}num_num;
	char	num_tag;		/* the key field: TYPB..TYPUNPACKED */
	char	num_sign;		/* when unpacked, the sign */
	short	num_exponent;		/* when unpacked, the unexcessed exp */
};
typedef	struct as_number	Bignum;


#define num_uchar	num_num.numIq_int.Iq_uchar
#define num_uint	num_num.numIq_int.Iq_ulong
#define num_ulong	num_num.numIq_int.Iq_ulong
#define num_ushort	num_num.numIq_int.Iq_ushort
/*
 *	The following definitions must all be consistent.
 *	They define the granularity of working on longs, quad and octal
 *	words. Currently, the granularity is as large as it can be: 32 bits
 *	in a chunk.
 */
#define CH_N		4		/* number of pieces */
#define CH_BITS		32		/* number of bits per piece */
#define CH_FIELD(x)	((x).num_num.numIo_int.Io_ulong)
typedef	u_int		*chptr;		/* basic data type */
#define SIGNBIT		0x80000000

#define HOC		(CH_N - 1)	/* high order chunk */
/*
 *	These values were computed using dc, so are exact.
 *	Only MAXINT_10 and MAXINT_5 are used in the programs.
 */
#define MAXINT_1	2147483648
#define MAXINT_10	214748364
#define MAXINT_5	429496729

Bignum intconvert();		/* converts amongst float #s */

/*
 *	Definitions for overflows.
 */
typedef	u_int	Ovf;

#define OVF_ADDV	(1<<0)	/* integer: adding two vectors overflowed */
#define OVF_LSHIFT	(1<<1)	/* integer: left shifting a vector lost bits */
#define OVF_POSOVF	(1<<2)	/* integer: positive number overflowed */
#define OVF_MAXINT	(1<<3)	/* integer: the number was the maxint + 1*/
#define OVF_F		(1<<4)	/* float: F overflow */
#define OVF_D		(1<<5)	/* float: D overflow */
#define OVF_G		(1<<6)	/* float: G overflow */
#define OVF_H		(1<<7)	/* float: H overflow */
#define OVF_OVERFLOW	(1<<9)	/* overflow in conversion */
#define OVF_UNDERFLOW	(1<<10)	/* underflow in conversion */


/*
 *	Definitions to unpack big numbers numbers into
 *	a 128 bit fraction and 16 bit excess-free exponent,
 *	and an 8 copy bits for the sign.
 *
 *	The fraction is represented as a normalized binary number,
 *	128 bits long, with the binary point between bits 127 and the
 *	hypothetical 128'th bit.  This hypothetical 128'th bit
 *	is always assumed to be one.
 */
/*
 *	A map entry is NOTAKE if the corresponding byte is
 *	not to be taken
 *
 *	The maps are for going from packed to unpacked format (b_up)
 *	and from unpacked to packed format (b_p)
 *	for the mantissa (b_upmmap) and for the exponent(b_upemap)
 *
 *	byte #i in the packed number goes to byte #b_upmmap[i] in the unpacked
 */
#define NOTAKE	-1
/*
 *	Bit manipulations
 */
#define ONES(n)	((1 << (n)) - 1)
/*
 *	Assertions
 */
#include <kern/assert.h>
