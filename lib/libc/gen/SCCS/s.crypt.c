h27162
s 00001/00003/00937
d D 8.1.1.1 93/08/18 16:14:24 mckusick 20 19
c disable decryption for foreign sites
e
s 00002/00002/00938
d D 8.1 93/06/04 12:00:38 bostic 19 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00003/00937
d D 5.11.1.1 91/08/19 18:20:06 mckusick 18 17
c disable decryption for foreign sites
e
s 00010/00010/00930
d D 5.11 91/06/25 10:23:26 karels 17 16
c fix typo (wonder how this was tested???); KNF for return ()
e
s 00047/00050/00893
d D 5.10 91/05/21 11:46:48 bostic 16 15
c check that chars are 8 bits; change the way that long pw's are
c encrypted; minor cleanups -- from Tom Truscott
e
s 00016/00010/00927
d D 5.9 91/05/18 14:56:22 bostic 15 14
c add return values to setkey, encrypt, des_setkey, des_cipher to
c distinguish failure (no hardware support or foreign distribution)
e
s 00001/00011/00936
d D 5.8 91/04/26 14:51:21 bostic 14 13
c new copyright; att/bsd/shared
e
s 00012/00010/00935
d D 5.7 91/04/21 15:11:59 bostic 13 11
c #define '_' in pwd.h as _PASSWORD_EFMT1
e
s 00011/00010/00935
d R 5.7 91/04/21 15:10:35 bostic 12 11
c #define '_' in pwd.h as _PASSWORD_EFMT1
e
s 00044/00030/00901
d D 5.6 91/04/21 15:07:34 bostic 11 9
c change null characters in salt or iteration to be '.', avoiding bug
c where crypt("anything!", "*") returned "*"; lots of comment changes, minor
c cleanups
e
s 00041/00038/00893
d R 5.6 91/04/21 14:28:38 bostic 10 9
c from Tom Truscott -- encrypted password of "*" always succeeded
e
s 00850/00309/00081
d D 5.5 91/03/06 14:49:56 bostic 9 8
c Tom Truscott's version of crypt
e
s 00008/00003/00382
d D 5.4 91/02/23 19:49:33 donn 8 6
c Add include files to get prototype declarations, and fix bugs found.
e
s 00002/00005/00380
d D 5.3.1.1 90/10/21 15:41:53 mckusick 7 6
c delete decryption for the foreign sites
e
s 00001/00001/00384
d D 5.3 90/05/11 17:53:04 bostic 6 4
c HP integration
e
s 00002/00005/00380
d D 5.2.1.1 86/08/12 14:35:49 mckusick 5 4
c delete decryption for the foreign sites
e
s 00002/00002/00383
d D 5.2 86/03/09 19:45:06 donn 4 3
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00381
d D 5.1 85/06/05 12:09:07 mckusick 3 2
c Add copyright
e
s 00019/00018/00363
d D 4.2 84/11/05 13:15:12 ralph 2 1
c init E table in setkey so encrypt can be used outside of crypt.
e
s 00381/00000/00000
d D 4.1 80/12/21 16:39:32 wnj 1 0
c date and time created 80/12/21 16:39:32 by wnj
e
u
U
f b 
t
T
I 9
/*
D 19
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 19
I 19
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 19
 *
 * This code is derived from software contributed to Berkeley by
 * Tom Truscott.
 *
D 14
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 14
I 14
 * %sccs.include.redist.c%
E 14
 */

E 9
I 1
D 3
/* %W% (Berkeley) %G% */
E 3
I 3
D 4
#ifndef lint
E 4
I 4
#if defined(LIBC_SCCS) && !defined(lint)
E 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
D 9
#endif LIBC_SCCS and not lint
E 9
I 9
#endif /* LIBC_SCCS and not lint */
E 9
E 4

I 9
D 11
#include <sys/cdefs.h>
E 11
E 9
I 8
#include <unistd.h>
I 16
#include <limits.h>
E 16
I 13
#include <pwd.h>
E 13

E 8
E 3
/*
D 9
 * This program implements the
 * Proposed Federal Information Processing
 *  Data Encryption Standard.
 * See Federal Register, March 17, 1975 (40FR12134)
E 9
I 9
 * UNIX password, and DES, encryption.
 * By Tom Truscott, trt@rti.rti.org,
 * from algorithms by Robert W. Baldwin and James Gillogly.
 *
 * References:
 * "Mathematical Cryptology for Computer Scientists and Mathematicians,"
 * by Wayne Patterson, 1987, ISBN 0-8476-7438-X.
 *
 * "Password Security: A Case History," R. Morris and Ken Thompson,
 * Communications of the ACM, vol. 22, pp. 594-597, Nov. 1979.
 *
 * "DES will be Totally Insecure within Ten Years," M.E. Hellman,
 * IEEE Spectrum, vol. 16, pp. 32-39, July 1979.
E 9
 */

I 9
/* =====  Configuration ==================== */

E 9
/*
D 9
 * Initial permutation,
E 9
I 9
 * define "MUST_ALIGN" if your compiler cannot load/store
 * long integers at arbitrary (e.g. odd) memory locations.
 * (Either that or never pass unaligned addresses to des_cipher!)
E 9
 */
D 9
static	char	IP[] = {
	58,50,42,34,26,18,10, 2,
	60,52,44,36,28,20,12, 4,
	62,54,46,38,30,22,14, 6,
	64,56,48,40,32,24,16, 8,
	57,49,41,33,25,17, 9, 1,
	59,51,43,35,27,19,11, 3,
	61,53,45,37,29,21,13, 5,
	63,55,47,39,31,23,15, 7,
};
E 9
I 9
#if !defined(vax)
#define	MUST_ALIGN
#endif
E 9

I 16
#ifdef CHAR_BITS
#if CHAR_BITS != 8
	#error C_block structure assumes 8 bit characters
#endif
#endif

E 16
/*
D 9
 * Final permutation, FP = IP^(-1)
E 9
I 9
 * define "LONG_IS_32_BITS" only if sizeof(long)==4.
 * This avoids use of bit fields (your compiler may be sloppy with them).
E 9
 */
D 9
static	char	FP[] = {
	40, 8,48,16,56,24,64,32,
	39, 7,47,15,55,23,63,31,
	38, 6,46,14,54,22,62,30,
	37, 5,45,13,53,21,61,29,
	36, 4,44,12,52,20,60,28,
	35, 3,43,11,51,19,59,27,
	34, 2,42,10,50,18,58,26,
	33, 1,41, 9,49,17,57,25,
};
E 9
I 9
#if !defined(cray)
#define	LONG_IS_32_BITS
#endif
E 9

/*
D 9
 * Permuted-choice 1 from the key bits
 * to yield C and D.
 * Note that bits 8,16... are left out:
 * They are intended for a parity check.
E 9
I 9
 * define "B64" to be the declaration for a 64 bit integer.
 * XXX this feature is currently unused, see "endian" comment below.
E 9
 */
D 9
static	char	PC1_C[] = {
	57,49,41,33,25,17, 9,
	 1,58,50,42,34,26,18,
	10, 2,59,51,43,35,27,
	19,11, 3,60,52,44,36,
};
E 9
I 9
#if defined(cray)
#define	B64	long
#endif
#if defined(convex)
#define	B64	long long
#endif
E 9

D 9
static	char	PC1_D[] = {
	63,55,47,39,31,23,15,
	 7,62,54,46,38,30,22,
	14, 6,61,53,45,37,29,
	21,13, 5,28,20,12, 4,
};

E 9
/*
D 9
 * Sequence of shifts used for the key schedule.
*/
static	char	shifts[] = {
	1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1,
};

/*
 * Permuted-choice 2, to pick out the bits from
 * the CD array that generate the key schedule.
E 9
I 9
 * define "LARGEDATA" to get faster permutations, by using about 72 kilobytes
 * of lookup tables.  This speeds up des_setkey() and des_cipher(), but has
D 11
 * little effect on crypt(). 
E 11
I 11
 * little effect on crypt().
E 11
E 9
 */
D 9
static	char	PC2_C[] = {
	14,17,11,24, 1, 5,
	 3,28,15, 6,21,10,
	23,19,12, 4,26, 8,
	16, 7,27,20,13, 2,
};
E 9
I 9
#if defined(notdef)
#define	LARGEDATA
#endif
E 9

D 9
static	char	PC2_D[] = {
	41,52,31,37,47,55,
	30,40,51,45,33,48,
	44,49,39,56,34,53,
	46,42,50,36,29,32,
};
E 9
I 9
D 11
/* comment out "static" when profiling */
E 11
I 11
/* compile with "-DSTATIC=int" when profiling */
#ifndef STATIC
E 11
#define	STATIC	static
D 11
STATIC init_des(), perminit(), permute();
E 11
I 11
#endif
STATIC init_des(), init_perm(), permute();
E 11
#ifdef DEBUG
STATIC prtab();
#endif
E 9

I 9
/* ==================================== */

E 9
/*
D 9
 * The C and D arrays used to calculate the key schedule.
E 9
I 9
 * Cipher-block representation (Bob Baldwin):
 *
 * DES operates on groups of 64 bits, numbered 1..64 (sigh).  One
 * representation is to store one bit per byte in an array of bytes.  Bit N of
 * the NBS spec is stored as the LSB of the Nth byte (index N-1) in the array.
 * Another representation stores the 64 bits in 8 bytes, with bits 1..8 in the
 * first byte, 9..16 in the second, and so on.  The DES spec apparently has
 * bit 1 in the MSB of the first byte, but that is particularly noxious so we
 * bit-reverse each byte so that bit 1 is the LSB of the first byte, bit 8 is
 * the MSB of the first byte.  Specifically, the 64-bit input data and key are
 * converted to LSB format, and the output 64-bit block is converted back into
 * MSB format.
 *
 * DES operates internally on groups of 32 bits which are expanded to 48 bits
 * by permutation E and shrunk back to 32 bits by the S boxes.  To speed up
 * the computation, the expansion is applied only once, the expanded
 * representation is maintained during the encryption, and a compression
 * permutation is applied only at the end.  To speed up the S-box lookups,
 * the 48 bits are maintained as eight 6 bit groups, one per byte, which
 * directly feed the eight S-boxes.  Within each byte, the 6 bits are the
 * most significant ones.  The low two bits of each byte are zero.  (Thus,
 * bit 1 of the 48 bit E expansion is stored as the "4"-valued bit of the
 * first byte in the eight byte representation, bit 2 of the 48 bit value is
D 11
 * the "8"-valued bit, and so on.) In fact, a combined "SPE"-box lookup is
E 11
I 11
 * the "8"-valued bit, and so on.)  In fact, a combined "SPE"-box lookup is
E 11
 * used, in which the output is the 64 bit result of an S-box lookup which
 * has been permuted by P and expanded by E, and is ready for use in the next
 * iteration.  Two 32-bit wide tables, SPE[0] and SPE[1], are used for this
 * lookup.  Since each byte in the 48 bit path is a multiple of four, indexed
 * lookup of SPE[0] and SPE[1] is simple and fast.  The key schedule and
 * "salt" are also converted to this 8*(6+2) format.  The SPE table size is
 * 8*64*8 = 4K bytes.
 *
 * To speed up bit-parallel operations (such as XOR), the 8 byte
 * representation is "union"ed with 32 bit values "i0" and "i1", and, on
 * machines which support it, a 64 bit value "b64".  This data structure,
 * "C_block", has two problems.  First, alignment restrictions must be
 * honored.  Second, the byte-order (e.g. little-endian or big-endian) of
 * the architecture becomes visible.
 *
 * The byte-order problem is unfortunate, since on the one hand it is good
 * to have a machine-independent C_block representation (bits 1..8 in the
 * first byte, etc.), and on the other hand it is good for the LSB of the
 * first byte to be the LSB of i0.  We cannot have both these things, so we
 * currently use the "little-endian" representation and avoid any multi-byte
 * operations that depend on byte order.  This largely precludes use of the
 * 64-bit datatype since the relative order of i0 and i1 are unknown.  It
 * also inhibits grouping the SPE table to look up 12 bits at a time.  (The
 * 12 bits can be stored in a 16-bit field with 3 low-order zeroes and 1
D 11
 * high-order zero, providing fast indexing into a 64-bit wide SPE.) On the
E 11
I 11
 * high-order zero, providing fast indexing into a 64-bit wide SPE.)  On the
E 11
 * other hand, 64-bit datatypes are currently rare, and a 12-bit SPE lookup
 * requires a 128 kilobyte table, so perhaps this is not a big loss.
 *
 * Permutation representation (Jim Gillogly):
 *
 * A transformation is defined by its effect on each of the 8 bytes of the
 * 64-bit input.  For each byte we give a 64-bit output that has the bits in
 * the input distributed appropriately.  The transformation is then the OR
 * of the 8 sets of 64-bits.  This uses 8*256*8 = 16K bytes of storage for
 * each transformation.  Unless LARGEDATA is defined, however, a more compact
 * table is used which looks up 16 4-bit "chunks" rather than 8 8-bit chunks.
 * The smaller table uses 16*16*8 = 2K bytes for each transformation.  This
 * is slower but tolerable, particularly for password encryption in which
 * the SPE transformation is iterated many times.  The small tables total 9K
 * bytes, the large tables total 72K bytes.
 *
 * The transformations used are:
 * IE3264: MSB->LSB conversion, initial permutation, and expansion.
 *	This is done by collecting the 32 even-numbered bits and applying
 *	a 32->64 bit transformation, and then collecting the 32 odd-numbered
 *	bits and applying the same transformation.  Since there are only
 *	32 input bits, the IE3264 transformation table is half the size of
 *	the usual table.
 * CF6464: Compression, final permutation, and LSB->MSB conversion.
 *	This is done by two trivial 48->32 bit compressions to obtain
 *	a 64-bit block (the bit numbering is given in the "CIFP" table)
 *	followed by a 64->64 bit "cleanup" transformation.  (It would
 *	be possible to group the bits in the 64-bit block so that 2
 *	identical 32->32 bit transformations could be used instead,
 *	saving a factor of 4 in space and possibly 2 in time, but
 *	byte-ordering and other complications rear their ugly head.
 *	Similar opportunities/problems arise in the key schedule
 *	transforms.)
 * PC1ROT: MSB->LSB, PC1 permutation, rotate, and PC2 permutation.
 *	This admittedly baroque 64->64 bit transformation is used to
 *	produce the first code (in 8*(6+2) format) of the key schedule.
 * PC2ROT[0]: Inverse PC2 permutation, rotate, and PC2 permutation.
 *	It would be possible to define 15 more transformations, each
 *	with a different rotation, to generate the entire key schedule.
 *	To save space, however, we instead permute each code into the
 *	next by using a transformation that "undoes" the PC2 permutation,
 *	rotates the code, and then applies PC2.  Unfortunately, PC2
 *	transforms 56 bits into 48 bits, dropping 8 bits, so PC2 is not
 *	invertible.  We get around that problem by using a modified PC2
 *	which retains the 8 otherwise-lost bits in the unused low-order
 *	bits of each byte.  The low-order bits are cleared when the
 *	codes are stored into the key schedule.
 * PC2ROT[1]: Same as PC2ROT[0], but with two rotations.
 *	This is faster than applying PC2ROT[0] twice,
 *
 * The Bell Labs "salt" (Bob Baldwin):
 *
 * The salting is a simple permutation applied to the 48-bit result of E.
 * Specifically, if bit i (1 <= i <= 24) of the salt is set then bits i and
 * i+24 of the result are swapped.  The salt is thus a 24 bit number, with
 * 16777216 possible values.  (The original salt was 12 bits and could not
 * swap bits 13..24 with 36..48.)
 *
D 11
 * It is possible, but expensive and ugly, to warp the SPE table account for
 * the salt permutation.  Fortunately, the conditional bit swapping requires
 * only about four machine instructions and can be done on-the-fly with only
 * a 2% performance penalty.
E 11
I 11
 * It is possible, but ugly, to warp the SPE table to account for the salt
 * permutation.  Fortunately, the conditional bit swapping requires only
 * about four machine instructions and can be done on-the-fly with about an
 * 8% performance penalty.
E 11
E 9
 */
I 11

E 11
I 9
typedef union {
	unsigned char b[8];
	struct {
#if defined(LONG_IS_32_BITS)
		/* long is often faster than a 32-bit bit field */
		long	i0;
		long	i1;
#else
		long	i0: 32;
		long	i1: 32;
#endif
	} b32;
#if defined(B64)
	B64	b64;
#endif
} C_block;
E 9

D 9
static	char	C[28];
static	char	D[28];
E 9
/*
D 9
 * The key schedule.
 * Generated from the key.
E 9
I 9
 * Convert twenty-four-bit long in host-order
 * to six bits (and 2 low-order zeroes) per char little-endian format.
E 9
 */
D 9
static	char	KS[16][48];
E 9
I 9
#define	TO_SIX_BIT(rslt, src) {				\
		C_block cvt;				\
		cvt.b[0] = src; src >>= 6;		\
		cvt.b[1] = src; src >>= 6;		\
		cvt.b[2] = src; src >>= 6;		\
		cvt.b[3] = src;				\
		rslt = (cvt.b32.i0 & 0x3f3f3f3fL) << 2;	\
	}
E 9

/*
I 2
D 9
 * The E bit-selection table.
E 9
I 9
 * These macros may someday permit efficient use of 64-bit integers.
E 9
 */
D 9
static	char	E[48];
static	char	e[] = {
	32, 1, 2, 3, 4, 5,
	 4, 5, 6, 7, 8, 9,
	 8, 9,10,11,12,13,
	12,13,14,15,16,17,
	16,17,18,19,20,21,
	20,21,22,23,24,25,
	24,25,26,27,28,29,
	28,29,30,31,32, 1,
E 9
I 9
#define	ZERO(d,d0,d1)			d0 = 0, d1 = 0
#define	LOAD(d,d0,d1,bl)		d0 = (bl).b32.i0, d1 = (bl).b32.i1
#define	LOADREG(d,d0,d1,s,s0,s1)	d0 = s0, d1 = s1
#define	OR(d,d0,d1,bl)			d0 |= (bl).b32.i0, d1 |= (bl).b32.i1
#define	STORE(s,s0,s1,bl)		(bl).b32.i0 = s0, (bl).b32.i1 = s1
#define	DCL_BLOCK(d,d0,d1)		long d0, d1

#if defined(LARGEDATA)
	/* Waste memory like crazy.  Also, do permutations in line */
#define	LGCHUNKBITS	3
#define	CHUNKBITS	(1<<LGCHUNKBITS)
#define	PERM6464(d,d0,d1,cpp,p)				\
	LOAD(d,d0,d1,(p)[(0<<CHUNKBITS)+(cpp)[0]]);		\
	OR (d,d0,d1,(p)[(1<<CHUNKBITS)+(cpp)[1]]);		\
	OR (d,d0,d1,(p)[(2<<CHUNKBITS)+(cpp)[2]]);		\
	OR (d,d0,d1,(p)[(3<<CHUNKBITS)+(cpp)[3]]);		\
	OR (d,d0,d1,(p)[(4<<CHUNKBITS)+(cpp)[4]]);		\
	OR (d,d0,d1,(p)[(5<<CHUNKBITS)+(cpp)[5]]);		\
	OR (d,d0,d1,(p)[(6<<CHUNKBITS)+(cpp)[6]]);		\
	OR (d,d0,d1,(p)[(7<<CHUNKBITS)+(cpp)[7]]);
#define	PERM3264(d,d0,d1,cpp,p)				\
	LOAD(d,d0,d1,(p)[(0<<CHUNKBITS)+(cpp)[0]]);		\
	OR (d,d0,d1,(p)[(1<<CHUNKBITS)+(cpp)[1]]);		\
	OR (d,d0,d1,(p)[(2<<CHUNKBITS)+(cpp)[2]]);		\
	OR (d,d0,d1,(p)[(3<<CHUNKBITS)+(cpp)[3]]);
#else
	/* "small data" */
#define	LGCHUNKBITS	2
#define	CHUNKBITS	(1<<LGCHUNKBITS)
#define	PERM6464(d,d0,d1,cpp,p)				\
	{ C_block tblk; permute(cpp,&tblk,p,8); LOAD (d,d0,d1,tblk); }
#define	PERM3264(d,d0,d1,cpp,p)				\
	{ C_block tblk; permute(cpp,&tblk,p,4); LOAD (d,d0,d1,tblk); }

STATIC
permute(cp, out, p, chars_in)
	unsigned char *cp;
	C_block *out;
	register C_block *p;
	int chars_in;
{
	register DCL_BLOCK(D,D0,D1);
	register C_block *tp;
	register int t;

	ZERO(D,D0,D1);
	do {
		t = *cp++;
		tp = &p[t&0xf]; OR(D,D0,D1,*tp); p += (1<<CHUNKBITS);
		tp = &p[t>>4];  OR(D,D0,D1,*tp); p += (1<<CHUNKBITS);
	} while (--chars_in > 0);
	STORE(D,D0,D1,*out);
}
#endif /* LARGEDATA */


/* =====  (mostly) Standard DES Tables ==================== */

static unsigned char IP[] = {		/* initial permutation */
	58, 50, 42, 34, 26, 18, 10,  2,
	60, 52, 44, 36, 28, 20, 12,  4,
	62, 54, 46, 38, 30, 22, 14,  6,
	64, 56, 48, 40, 32, 24, 16,  8,
	57, 49, 41, 33, 25, 17,  9,  1,
	59, 51, 43, 35, 27, 19, 11,  3,
	61, 53, 45, 37, 29, 21, 13,  5,
	63, 55, 47, 39, 31, 23, 15,  7,
E 9
};

I 9
/* The final permutation is the inverse of IP - no table is necessary */

static unsigned char ExpandTr[] = {	/* expansion operation */
	32,  1,  2,  3,  4,  5,
	 4,  5,  6,  7,  8,  9,
	 8,  9, 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32,  1,
};

D 16
static unsigned char PC1[] = {		/* permuted choice table (key)  */
E 16
I 16
static unsigned char PC1[] = {		/* permuted choice table 1 */
E 16
	57, 49, 41, 33, 25, 17,  9,
	 1, 58, 50, 42, 34, 26, 18,
	10,  2, 59, 51, 43, 35, 27,
	19, 11,  3, 60, 52, 44, 36,

	63, 55, 47, 39, 31, 23, 15,
	 7, 62, 54, 46, 38, 30, 22,
	14,  6, 61, 53, 45, 37, 29,
	21, 13,  5, 28, 20, 12,  4,
};

D 16
static unsigned char Rotates[] = {	/* number of rotations of PC1 */
E 16
I 16
static unsigned char Rotates[] = {	/* PC1 rotation schedule */
E 16
	1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1,
};

/* note: each "row" of PC2 is left-padded with bits that make it invertible */
D 16
static unsigned char PC2[] = {		/* permuted choice key (table)  */
E 16
I 16
static unsigned char PC2[] = {		/* permuted choice table 2 */
E 16
	 9, 18,    14, 17, 11, 24,  1,  5,
	22, 25,     3, 28, 15,  6, 21, 10,
	35, 38,    23, 19, 12,  4, 26,  8,
	43, 54,    16,  7, 27, 20, 13,  2,

	 0,  0,    41, 52, 31, 37, 47, 55,
	 0,  0,    30, 40, 51, 45, 33, 48,
	 0,  0,    44, 49, 39, 56, 34, 53,
	 0,  0,    46, 42, 50, 36, 29, 32,
};

static unsigned char S[8][64] = {	/* 48->32 bit substitution tables */
					/* S[1]			*/
	14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
	 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
	 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
	15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13,
					/* S[2]			*/
	15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
	 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
	 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
	13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9,
					/* S[3]			*/
	10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
	13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
	13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
	 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12,
					/* S[4]			*/
	 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
	13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
	10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
	 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14,
					/* S[5]			*/
	 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
	14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
	 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
	11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3,
					/* S[6]			*/
	12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
	10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
	 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
	 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13,
					/* S[7]			*/
	 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
	13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
	 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
	 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12,
					/* S[8]			*/
	13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
	 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
	 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
	 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11,
};

static unsigned char P32Tr[] = {	/* 32-bit permutation function */
	16,  7, 20, 21,
	29, 12, 28, 17,
	 1, 15, 23, 26,
	 5, 18, 31, 10,
	 2,  8, 24, 14,
	32, 27,  3,  9,
	19, 13, 30,  6,
	22, 11,  4, 25,
};

static unsigned char CIFP[] = {		/* compressed/interleaved permutation */
	 1,  2,  3,  4,   17, 18, 19, 20,
	 5,  6,  7,  8,   21, 22, 23, 24,
	 9, 10, 11, 12,   25, 26, 27, 28,
	13, 14, 15, 16,   29, 30, 31, 32,

	33, 34, 35, 36,   49, 50, 51, 52,
	37, 38, 39, 40,   53, 54, 55, 56,
	41, 42, 43, 44,   57, 58, 59, 60,
	45, 46, 47, 48,   61, 62, 63, 64,
};

static unsigned char itoa64[] =		/* 0..63 => ascii-64 */
	"./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";


/* =====  Tables that are initialized at run time  ==================== */


static unsigned char a64toi[128];	/* ascii-64 => 0..63 */

/* Initial key schedule permutation */
static C_block	PC1ROT[64/CHUNKBITS][1<<CHUNKBITS];

/* Subsequent key schedule rotation permutations */
static C_block	PC2ROT[2][64/CHUNKBITS][1<<CHUNKBITS];

/* Initial permutation/expansion table */
static C_block	IE3264[32/CHUNKBITS][1<<CHUNKBITS];

/* Table that combines the S, P, and E operations.  */
static long SPE[2][8][64];

/* compressed/interleaved => final permutation table */
static C_block	CF6464[64/CHUNKBITS][1<<CHUNKBITS];


/* ==================================== */


static C_block	constdatablock;			/* encryption constant */
static char	cryptresult[1+4+4+11+1];	/* encrypted result */

E 9
/*
E 2
D 9
 * Set up the key schedule from the key.
E 9
I 9
D 11
 * XXX need comment
E 11
I 11
 * Return a pointer to static data consisting of the "setting"
 * followed by an encryption produced by the "key" and "setting".
E 11
E 9
 */
D 9

I 8
void
E 8
setkey(key)
D 8
char *key;
E 8
I 8
const char *key;
E 9
I 9
char *
crypt(key, setting)
	register const char *key;
	register const char *setting;
E 9
E 8
{
D 9
	register i, j, k;
	int t;
E 9
I 9
	register char *encp;
	register long i;
I 11
	register int t;
E 11
	long salt;
D 16
	int num_iter, salt_size, key_size;
E 16
I 16
	int num_iter, salt_size;
E 16
	C_block keyblock, rsltblock;
E 9

I 9
D 11
	for (i = 0; i < 8; i++)
		if ((keyblock.b[i] = 2*(unsigned char)(*key)) != 0)
E 11
I 11
	for (i = 0; i < 8; i++) {
		if ((t = 2*(unsigned char)(*key)) != 0)
E 11
			key++;
I 11
		keyblock.b[i] = t;
	}
E 11
D 15
	des_setkey((char *)keyblock.b);	/* also initializes "a64toi" */
E 15
I 15
	if (des_setkey((char *)keyblock.b))	/* also initializes "a64toi" */
D 17
		return(NULL);
E 17
I 17
		return (NULL);
E 17
E 15

	encp = &cryptresult[0];
D 13
	if (*setting != '_') {	/* old style */
		num_iter = 25;
		salt_size = 2;
		key_size = 8;
	}
	else {			/* new style */
E 13
I 13
	switch (*setting) {
	case _PASSWORD_EFMT1:
I 16
		/*
		 * Involve the rest of the password 8 characters at a time.
		 */
		while (*key) {
			if (des_cipher((char *)&keyblock,
			    (char *)&keyblock, 0L, 1))
D 17
				return(NULL);
E 17
I 17
				return (NULL);
E 17
			for (i = 0; i < 8; i++) {
				if ((t = 2*(unsigned char)(*key)) != 0)
					key++;
				keyblock.b[i] ^= t;
			}
			if (des_setkey((char *)keyblock.b))
D 17
				retrun(NULL);
E 17
I 17
				return (NULL);
E 17
		}

E 16
E 13
		*encp++ = *setting++;

		/* get iteration count */
		num_iter = 0;
		for (i = 4; --i >= 0; ) {
D 11
			num_iter = (num_iter<<6) |
				a64toi[(unsigned char)
					(encp[i] = (unsigned char)setting[i])];
E 11
I 11
			if ((t = (unsigned char)setting[i]) == '\0')
				t = '.';
			encp[i] = t;
			num_iter = (num_iter<<6) | a64toi[t];
E 11
		}
		setting += 4;
		encp += 4;
		salt_size = 4;
D 16
		key_size = 128;
E 16
I 13
		break;
	default:
		num_iter = 25;
		salt_size = 2;
D 16
		key_size = 8;
E 16
E 13
	}

	salt = 0;
	for (i = salt_size; --i >= 0; ) {
D 11
		salt = (salt<<6) |
			a64toi[(unsigned char)
				(encp[i] = (unsigned char)setting[i])];
E 11
I 11
		if ((t = (unsigned char)setting[i]) == '\0')
			t = '.';
		encp[i] = t;
		salt = (salt<<6) | a64toi[t];
E 11
	}
	encp += salt_size;
D 15
	des_cipher((char *)&constdatablock, (char *)&rsltblock, salt, num_iter);
E 15
I 15
	if (des_cipher((char *)&constdatablock, (char *)&rsltblock,
	    salt, num_iter))
D 17
		return(NULL);
E 17
I 17
		return (NULL);
E 17
E 15

E 9
	/*
D 9
	 * First, generate C and D by permuting
	 * the key.  The low order bit of each
	 * 8-bit char is not used, so C and D are only 28
	 * bits apiece.
E 9
I 9
D 16
	 * encrypt the remainder of the password 8 characters at a time.
E 9
	 */
D 9
	for (i=0; i<28; i++) {
		C[i] = key[PC1_C[i]-1];
		D[i] = key[PC1_D[i]-1];
E 9
I 9
	while ((key_size -= 8) > 0 && *key) {
		C_block xdatablock;

D 11
		for (i = 0; i < 8; i++)
			if ((keyblock.b[i] = 2*(unsigned char)(*key)) != 0)
E 11
I 11
		for (i = 0; i < 8; i++) {
			if ((t = 2*(unsigned char)(*key)) != 0)
E 11
				key++;
D 11
			else
E 11
I 11
			keyblock.b[i] = t;
			if (t == 0)
E 11
				break;	/* pad out with previous key */
I 11
		}
E 11
D 15
		des_setkey((char *)keyblock.b);
		des_cipher((char *)&constdatablock, (char *)&xdatablock, 0L, 1);
E 15
I 15
		if (des_setkey((char *)keyblock.b))
			return(NULL);
		if (des_cipher((char *)&constdatablock,
		    (char *)&xdatablock, 0L, 1))
			return(NULL);
E 15
		rsltblock.b32.i0 ^= xdatablock.b32.i0;
		rsltblock.b32.i1 ^= xdatablock.b32.i1;
E 9
	}
I 9

E 9
	/*
E 16
D 9
	 * To generate Ki, rotate C and D according
	 * to schedule and pick up a permutation
	 * using PC2.
E 9
I 9
	 * Encode the 64 cipher bits as 11 ascii characters.
E 9
	 */
D 9
	for (i=0; i<16; i++) {
		/*
		 * rotate.
		 */
		for (k=0; k<shifts[i]; k++) {
			t = C[0];
			for (j=0; j<28-1; j++)
				C[j] = C[j+1];
			C[27] = t;
			t = D[0];
			for (j=0; j<28-1; j++)
				D[j] = D[j+1];
			D[27] = t;
		}
		/*
		 * get Ki. Note C and D are concatenated.
		 */
		for (j=0; j<24; j++) {
			KS[i][j] = C[PC2_C[j]-1];
			KS[i][j+24] = D[PC2_D[j]-28-1];
		}
E 9
I 9
	i = ((long)((rsltblock.b[0]<<8) | rsltblock.b[1])<<8) | rsltblock.b[2];
	encp[3] = itoa64[i&0x3f];	i >>= 6;
	encp[2] = itoa64[i&0x3f];	i >>= 6;
	encp[1] = itoa64[i&0x3f];	i >>= 6;
	encp[0] = itoa64[i];		encp += 4;
	i = ((long)((rsltblock.b[3]<<8) | rsltblock.b[4])<<8) | rsltblock.b[5];
	encp[3] = itoa64[i&0x3f];	i >>= 6;
	encp[2] = itoa64[i&0x3f];	i >>= 6;
	encp[1] = itoa64[i&0x3f];	i >>= 6;
	encp[0] = itoa64[i];		encp += 4;
	i = ((long)((rsltblock.b[6])<<8) | rsltblock.b[7])<<2;
	encp[2] = itoa64[i&0x3f];	i >>= 6;
	encp[1] = itoa64[i&0x3f];	i >>= 6;
	encp[0] = itoa64[i];

	encp[3] = 0;
I 11

E 11
D 17
	return(cryptresult);
E 17
I 17
	return (cryptresult);
E 17
}


/*
 * The Key Schedule, filled in by des_setkey() or setkey().
 */
#define	KS_SIZE	16
static C_block	KS[KS_SIZE];

/*
 * Set up the key schedule from the key.
 */
D 15
void
E 15
des_setkey(key)
	register const char *key;
{
	register DCL_BLOCK(K, K0, K1);
	register C_block *ptabp;
	register int i;
	static int des_ready = 0;

	if (!des_ready) {
		init_des();
		des_ready = 1;
E 9
	}
I 2

D 9
	for(i=0;i<48;i++)
		E[i] = e[i];
E 9
I 9
	PERM6464(K,K0,K1,(unsigned char *)key,(C_block *)PC1ROT);
	key = (char *)&KS[0];
D 16
	STORE(K&0xfcfcfcfcL, K0&0xfcfcfcfcL, K1, *(C_block *)key);
E 16
I 16
	STORE(K&~0x03030303L, K0&~0x03030303L, K1, *(C_block *)key);
E 16
	for (i = 1; i < 16; i++) {
		key += sizeof(C_block);
		STORE(K,K0,K1,*(C_block *)key);
		ptabp = (C_block *)PC2ROT[Rotates[i]-1];
		PERM6464(K,K0,K1,(unsigned char *)key,ptabp);
D 16
		STORE(K&0xfcfcfcfcL, K0&0xfcfcfcfcL, K1, *(C_block *)key);
E 16
I 16
		STORE(K&~0x03030303L, K0&~0x03030303L, K1, *(C_block *)key);
E 16
	}
I 15
D 17
	return(0);
E 17
I 17
	return (0);
E 17
E 15
E 9
E 2
}

/*
D 2
 * The E bit-selection table.
 */
static	char	E[48];
static	char	e[] = {
	32, 1, 2, 3, 4, 5,
	 4, 5, 6, 7, 8, 9,
	 8, 9,10,11,12,13,
	12,13,14,15,16,17,
	16,17,18,19,20,21,
	20,21,22,23,24,25,
	24,25,26,27,28,29,
	28,29,30,31,32, 1,
};

/*
E 2
D 9
 * The 8 selection functions.
 * For some reason, they give a 0-origin
 * index, unlike everything else.
E 9
I 9
 * Encrypt (or decrypt if num_iter < 0) the 8 chars at "in" with abs(num_iter)
 * iterations of DES, using the the given 24-bit salt and the pre-computed key
 * schedule, and store the resulting 8 chars at "out" (in == out is permitted).
 *
 * NOTE: the performance of this routine is critically dependent on your
 * compiler and machine architecture.
E 9
 */
D 9
static	char	S[8][64] = {
	14, 4,13, 1, 2,15,11, 8, 3,10, 6,12, 5, 9, 0, 7,
	 0,15, 7, 4,14, 2,13, 1,10, 6,12,11, 9, 5, 3, 8,
	 4, 1,14, 8,13, 6, 2,11,15,12, 9, 7, 3,10, 5, 0,
	15,12, 8, 2, 4, 9, 1, 7, 5,11, 3,14,10, 0, 6,13,
E 9
I 9
D 15
void
E 15
des_cipher(in, out, salt, num_iter)
	const char *in;
	char *out;
D 11
	u_long salt;
E 11
I 11
	long salt;
E 11
	int num_iter;
{
	/* variables that we want in registers, most important first */
#if defined(pdp11)
	register int j;
#endif
	register long L0, L1, R0, R1, k;
	register C_block *kp;
	register int ks_inc, loop_count;
	C_block B;
E 9

D 9
	15, 1, 8,14, 6,11, 3, 4, 9, 7, 2,13,12, 0, 5,10,
	 3,13, 4, 7,15, 2, 8,14,12, 0, 1,10, 6, 9,11, 5,
	 0,14, 7,11,10, 4,13, 1, 5, 8,12, 6, 9, 3, 2,15,
	13, 8,10, 1, 3,15, 4, 2,11, 6, 7,12, 0, 5,14, 9,
E 9
I 9
	L0 = salt;
D 16
	TO_SIX_BIT(salt, L0);	/* convert to 8*(6+2) format */
E 16
I 16
	TO_SIX_BIT(salt, L0);	/* convert to 4*(6+2) format */
E 16
E 9

D 9
	10, 0, 9,14, 6, 3,15, 5, 1,13,12, 7,11, 4, 2, 8,
	13, 7, 0, 9, 3, 4, 6,10, 2, 8, 5,14,12,11,15, 1,
	13, 6, 4, 9, 8,15, 3, 0,11, 1, 2,12, 5,10,14, 7,
	 1,10,13, 0, 6, 9, 8, 7, 4,15,14, 3,11, 5, 2,12,
E 9
I 9
#if defined(vax) || defined(pdp11)
	salt = ~salt;	/* "x &~ y" is faster than "x & y". */
#define	SALT (~salt)
#else
#define	SALT salt
#endif
E 9

D 9
	 7,13,14, 3, 0, 6, 9,10, 1, 2, 8, 5,11,12, 4,15,
	13, 8,11, 5, 6,15, 0, 3, 4, 7, 2,12, 1,10,14, 9,
	10, 6, 9, 0,12,11, 7,13,15, 1, 3,14, 5, 2, 8, 4,
	 3,15, 0, 6,10, 1,13, 8, 9, 4, 5,11,12, 7, 2,14,
E 9
I 9
#if defined(MUST_ALIGN)
	B.b[0] = in[0]; B.b[1] = in[1]; B.b[2] = in[2]; B.b[3] = in[3];
	B.b[4] = in[4]; B.b[5] = in[5]; B.b[6] = in[6]; B.b[7] = in[7];
	LOAD(L,L0,L1,B);
#else
	LOAD(L,L0,L1,*(C_block *)in);
#endif
	LOADREG(R,R0,R1,L,L0,L1);
	L0 &= 0x55555555L;
	L1 &= 0x55555555L;
	L0 = (L0 << 1) | L1;	/* L0 is the even-numbered input bits */
	R0 &= 0xaaaaaaaaL;
	R1 = (R1 >> 1) & 0x55555555L;
	L1 = R0 | R1;		/* L1 is the odd-numbered input bits */
	STORE(L,L0,L1,B);
	PERM3264(L,L0,L1,B.b,  (C_block *)IE3264);	/* even bits */
	PERM3264(R,R0,R1,B.b+4,(C_block *)IE3264);	/* odd bits */
E 9

D 9
	 2,12, 4, 1, 7,10,11, 6, 8, 5, 3,15,13, 0,14, 9,
	14,11, 2,12, 4, 7,13, 1, 5, 0,15,10, 3, 9, 8, 6,
	 4, 2, 1,11,10,13, 7, 8,15, 9,12, 5, 6, 3, 0,14,
	11, 8,12, 7, 1,14, 2,13, 6,15, 0, 9,10, 4, 5, 3,
E 9
I 9
	if (num_iter >= 0)
	{		/* encryption */
		kp = &KS[0];
		ks_inc  = sizeof(*kp);
	}
	else
	{		/* decryption */
D 18
D 20
		num_iter = -num_iter;
		kp = &KS[KS_SIZE-1];
		ks_inc  = -sizeof(*kp);
E 20
I 20
		return (1); /* always fail */
E 20
E 18
I 18
		return (1); /* always fail */
E 18
	}
E 9

D 9
	12, 1,10,15, 9, 2, 6, 8, 0,13, 3, 4,14, 7, 5,11,
	10,15, 4, 2, 7,12, 9, 5, 6, 1,13,14, 0,11, 3, 8,
	 9,14,15, 5, 2, 8,12, 3, 7, 0, 4,10, 1,13,11, 6,
	 4, 3, 2,12, 9, 5,15,10,11,14, 1, 7, 6, 0, 8,13,
E 9
I 9
	while (--num_iter >= 0) {
		loop_count = 8;
		do {
E 9

D 9
	 4,11, 2,14,15, 0, 8,13, 3,12, 9, 7, 5,10, 6, 1,
	13, 0,11, 7, 4, 9, 1,10,14, 3, 5,12, 2,15, 8, 6,
	 1, 4,11,13,12, 3, 7,14,10,15, 6, 8, 0, 5, 9, 2,
	 6,11,13, 8, 1, 4,10, 7, 9, 5, 0,15,14, 2, 3,12,
E 9
I 9
D 16
#define	BTAB(i)		(((unsigned char *)&B.b[0])[i])
#define	SPTAB(t, i)	(*(long *)((unsigned char *)t \
				+ i*(sizeof(long)/4)))
E 16
I 16
#define	SPTAB(t, i)	(*(long *)((unsigned char *)t + i*(sizeof(long)/4)))
E 16
#if defined(gould)
D 16
			/* use this if BTAB(i) is evaluated just once ... */
#define	DOXOR(a,b,i)	a^=SPTAB(SPE[0][i],BTAB(i));b^=SPTAB(SPE[1][i],BTAB(i));
E 16
I 16
			/* use this if B.b[i] is evaluated just once ... */
#define	DOXOR(x,y,i)	x^=SPTAB(SPE[0][i],B.b[i]); y^=SPTAB(SPE[1][i],B.b[i]);
E 16
#else
#if defined(pdp11)
			/* use this if your "long" int indexing is slow */
D 16
#define	DOXOR(a,b,i)	j=BTAB(i); a^=SPTAB(SPE[0][i],j); b^=SPTAB(SPE[1][i],j);
E 16
I 16
#define	DOXOR(x,y,i)	j=B.b[i]; x^=SPTAB(SPE[0][i],j); y^=SPTAB(SPE[1][i],j);
E 16
#else
			/* use this if "k" is allocated to a register ... */
D 16
#define	DOXOR(a,b,i)	k=BTAB(i); a^=SPTAB(SPE[0][i],k); b^=SPTAB(SPE[1][i],k);
E 16
I 16
#define	DOXOR(x,y,i)	k=B.b[i]; x^=SPTAB(SPE[0][i],k); y^=SPTAB(SPE[1][i],k);
E 16
#endif
#endif
E 9

D 9
	13, 2, 8, 4, 6,15,11, 1,10, 9, 3,14, 5, 0,12, 7,
	 1,15,13, 8,10, 3, 7, 4,12, 5, 6,11, 0,14, 9, 2,
	 7,11, 4, 1, 9,12,14, 2, 0, 6,10,13,15, 3, 5, 8,
	 2, 1,14, 7, 4,10, 8,13,15,12, 9, 0, 3, 5, 6,11,
};
E 9
I 9
D 16
#define	CRUNCH(L0, L1, R0, R1)	\
			k = (R0 ^ R1) & SALT;	\
			B.b32.i0 = k ^ R0 ^ kp->b32.i0;		\
			B.b32.i1 = k ^ R1 ^ kp->b32.i1;		\
E 16
I 16
#define	CRUNCH(p0, p1, q0, q1)	\
			k = (q0 ^ q1) & SALT;	\
			B.b32.i0 = k ^ q0 ^ kp->b32.i0;		\
			B.b32.i1 = k ^ q1 ^ kp->b32.i1;		\
E 16
			kp = (C_block *)((char *)kp+ks_inc);	\
							\
D 16
			DOXOR(L0, L1, 0);		\
			DOXOR(L0, L1, 1);		\
			DOXOR(L0, L1, 2);		\
			DOXOR(L0, L1, 3);		\
			DOXOR(L0, L1, 4);		\
			DOXOR(L0, L1, 5);		\
			DOXOR(L0, L1, 6);		\
			DOXOR(L0, L1, 7);
E 16
I 16
			DOXOR(p0, p1, 0);		\
			DOXOR(p0, p1, 1);		\
			DOXOR(p0, p1, 2);		\
			DOXOR(p0, p1, 3);		\
			DOXOR(p0, p1, 4);		\
			DOXOR(p0, p1, 5);		\
			DOXOR(p0, p1, 6);		\
			DOXOR(p0, p1, 7);
E 16
E 9

D 9
/*
 * P is a permutation on the selected combination
 * of the current L and key.
 */
static	char	P[] = {
	16, 7,20,21,
	29,12,28,17,
	 1,15,23,26,
	 5,18,31,10,
	 2, 8,24,14,
	32,27, 3, 9,
	19,13,30, 6,
	22,11, 4,25,
};
E 9
I 9
			CRUNCH(L0, L1, R0, R1);
			CRUNCH(R0, R1, L0, L1);
		} while (--loop_count != 0);
		kp = (C_block *)((char *)kp-(ks_inc*KS_SIZE));
E 9

D 9
/*
 * The current block, divided into 2 halves.
 */
D 6
static	char	L[32], R[32];
E 6
I 6
static	char	L[64], *R = L+32;
E 6
static	char	tempL[32];
static	char	f[32];
E 9

D 9
/*
 * The combination of the key and the input, before selection.
 */
static	char	preS[48];
E 9
I 9
		/* swap L and R */
		L0 ^= R0;  L1 ^= R1;
		R0 ^= L0;  R1 ^= L1;
		L0 ^= R0;  L1 ^= R1;
	}
E 9

I 9
	/* store the encrypted (or decrypted) result */
	L0 = ((L0 >> 3) & 0x0f0f0f0fL) | ((L1 << 1) & 0xf0f0f0f0L);
	L1 = ((R0 >> 3) & 0x0f0f0f0fL) | ((R1 << 1) & 0xf0f0f0f0L);
	STORE(L,L0,L1,B);
	PERM6464(L,L0,L1,B.b, (C_block *)CF6464);
#if defined(MUST_ALIGN)
	STORE(L,L0,L1,B);
	out[0] = B.b[0]; out[1] = B.b[1]; out[2] = B.b[2]; out[3] = B.b[3];
	out[4] = B.b[4]; out[5] = B.b[5]; out[6] = B.b[6]; out[7] = B.b[7];
#else
	STORE(L,L0,L1,*(C_block *)out);
#endif
I 15
D 17
	return(0);
E 17
I 17
	return (0);
E 17
E 15
}


E 9
/*
D 9
 * The payoff: encrypt a block.
E 9
I 9
 * Initialize various tables.  This need only be done once.  It could even be
 * done at compile time, if the compiler were capable of that sort of thing.
E 9
 */
D 9

I 8
void
E 8
encrypt(block, edflag)
char *block;
I 8
int edflag;
E 9
I 9
STATIC
init_des()
E 9
E 8
{
D 9
	int i, ii;
	register t, j, k;
E 9
I 9
	register int i, j;
	register long k;
	register int tableno;
	static unsigned char perm[64], tmp32[32];	/* "static" for speed */
E 9

	/*
D 9
	 * First, permute the bits in the input
E 9
I 9
	 * table that converts chars "./0-9A-Za-z"to integers 0-63.
E 9
	 */
D 9
	for (j=0; j<64; j++)
		L[j] = block[IP[j]-1];
E 9
I 9
	for (i = 0; i < 64; i++)
		a64toi[itoa64[i]] = i;

E 9
	/*
D 9
	 * Perform an encryption operation 16 times.
E 9
I 9
	 * PC1ROT - bit reverse, then PC1, then Rotate, then PC2.
E 9
	 */
D 9
	for (ii=0; ii<16; ii++) {
		/*
D 5
D 7
		 * Set direction
E 7
I 7
		 * Only encrypt for now.
E 7
E 5
I 5
		 * Only encrypt for now.
E 5
		 */
D 5
D 7
		if (edflag)
			i = 15-ii;
		else
			i = ii;
E 7
I 7
		i = ii;
E 7
E 5
I 5
		i = ii;
E 5
		/*
		 * Save the R array,
		 * which will be the new L.
		 */
		for (j=0; j<32; j++)
			tempL[j] = R[j];
		/*
		 * Expand R to 48 bits using the E selector;
		 * exclusive-or with the current key bits.
		 */
		for (j=0; j<48; j++)
			preS[j] = R[E[j]-1] ^ KS[i][j];
		/*
		 * The pre-select bits are now considered
		 * in 8 groups of 6 bits each.
		 * The 8 selection functions map these
		 * 6-bit quantities into 4-bit quantities
		 * and the results permuted
		 * to make an f(R, K).
		 * The indexing into the selection functions
		 * is peculiar; it could be simplified by
		 * rewriting the tables.
		 */
		for (j=0; j<8; j++) {
			t = 6*j;
			k = S[j][(preS[t+0]<<5)+
				(preS[t+1]<<3)+
				(preS[t+2]<<2)+
				(preS[t+3]<<1)+
				(preS[t+4]<<0)+
				(preS[t+5]<<4)];
			t = 4*j;
			f[t+0] = (k>>3)&01;
			f[t+1] = (k>>2)&01;
			f[t+2] = (k>>1)&01;
			f[t+3] = (k>>0)&01;
E 9
I 9
	for (i = 0; i < 64; i++)
		perm[i] = 0;
	for (i = 0; i < 64; i++) {
		if ((k = PC2[i]) == 0)
			continue;
		k += Rotates[0]-1;
		if ((k%28) < Rotates[0]) k -= 28;
		k = PC1[k];
		if (k > 0) {
			k--;
			k = (k|07) - (k&07);
			k++;
E 9
		}
D 9
		/*
		 * The new R is L ^ f(R, K).
		 * The f here has to be permuted first, though.
		 */
		for (j=0; j<32; j++)
			R[j] = L[j] ^ f[P[j]-1];
		/*
		 * Finally, the new L (the original R)
		 * is copied back.
		 */
		for (j=0; j<32; j++)
			L[j] = tempL[j];
E 9
I 9
		perm[i] = k;
E 9
	}
I 9
#ifdef DEBUG
	prtab("pc1tab", perm, 8);
#endif
D 11
	perminit(PC1ROT, perm, 8, 8);
E 11
I 11
	init_perm(PC1ROT, perm, 8, 8);
E 11

E 9
	/*
D 9
	 * The output L and R are reversed.
E 9
I 9
	 * PC2ROT - PC2 inverse, then Rotate (once or twice), then PC2.
E 9
	 */
D 9
	for (j=0; j<32; j++) {
		t = L[j];
		L[j] = R[j];
		R[j] = t;
E 9
I 9
	for (j = 0; j < 2; j++) {
		unsigned char pc2inv[64];
		for (i = 0; i < 64; i++)
			perm[i] = pc2inv[i] = 0;
		for (i = 0; i < 64; i++) {
			if ((k = PC2[i]) == 0)
				continue;
			pc2inv[k-1] = i+1;
		}
		for (i = 0; i < 64; i++) {
			if ((k = PC2[i]) == 0)
				continue;
			k += j;
			if ((k%28) <= j) k -= 28;
			perm[i] = pc2inv[k];
		}
#ifdef DEBUG
		prtab("pc2tab", perm, 8);
#endif
D 11
		perminit(PC2ROT[j], perm, 8, 8);
E 11
I 11
		init_perm(PC2ROT[j], perm, 8, 8);
E 11
E 9
	}
I 9

E 9
	/*
D 9
	 * The final output
	 * gets the inverse permutation of the very original.
E 9
I 9
	 * Bit reverse, then initial permutation, then expansion.
E 9
	 */
D 9
	for (j=0; j<64; j++)
		block[j] = L[FP[j]-1];
E 9
I 9
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			k = (j < 2)? 0: IP[ExpandTr[i*6+j-2]-1];
			if (k > 32)
				k -= 32;
			else if (k > 0)
				k--;
			if (k > 0) {
				k--;
				k = (k|07) - (k&07);
				k++;
			}
			perm[i*8+j] = k;
		}
	}
#ifdef DEBUG
	prtab("ietab", perm, 8);
#endif
D 11
	perminit(IE3264, perm, 4, 8);
E 11
I 11
	init_perm(IE3264, perm, 4, 8);
E 11

	/*
	 * Compression, then final permutation, then bit reverse.
	 */
	for (i = 0; i < 64; i++) {
		k = IP[CIFP[i]-1];
		if (k > 0) {
			k--;
			k = (k|07) - (k&07);
			k++;
		}
		perm[k-1] = i+1;
	}
#ifdef DEBUG
	prtab("cftab", perm, 8);
#endif
D 11
	perminit(CF6464, perm, 8, 8);
E 11
I 11
	init_perm(CF6464, perm, 8, 8);
E 11

	/*
	 * SPE table
	 */
	for (i = 0; i < 48; i++)
		perm[i] = P32Tr[ExpandTr[i]-1];
	for (tableno = 0; tableno < 8; tableno++) {
		for (j = 0; j < 64; j++)  {
			k = (((j >> 0) &01) << 5)|
			    (((j >> 1) &01) << 3)|
			    (((j >> 2) &01) << 2)|
			    (((j >> 3) &01) << 1)|
			    (((j >> 4) &01) << 0)|
			    (((j >> 5) &01) << 4);
			k = S[tableno][k];
			k = (((k >> 3)&01) << 0)|
			    (((k >> 2)&01) << 1)|
			    (((k >> 1)&01) << 2)|
			    (((k >> 0)&01) << 3);
			for (i = 0; i < 32; i++)
				tmp32[i] = 0;
			for (i = 0; i < 4; i++)
				tmp32[4 * tableno + i] = (k >> i) & 01;
			k = 0;
			for (i = 24; --i >= 0; )
				k = (k<<1) | tmp32[perm[i]-1];
			TO_SIX_BIT(SPE[0][tableno][j], k);
			k = 0;
			for (i = 24; --i >= 0; )
				k = (k<<1) | tmp32[perm[i+24]-1];
			TO_SIX_BIT(SPE[1][tableno][j], k);
		}
	}
E 9
}

D 9
char *
crypt(pw,salt)
D 8
char *pw;
char *salt;
E 8
I 8
const char *pw;
const char *salt;
E 9
I 9
D 11

E 11
/*
D 11
 * XXX need comment
E 11
I 11
 * Initialize "perm" to represent transformation "p", which rearranges
 * (perhaps with expansion and/or contraction) one packed array of bits
 * (of size "chars_in" characters) into another array (of size "chars_out"
 * characters).
 *
E 11
 * "perm" must be all-zeroes on entry to this routine.
 */
STATIC
D 11
perminit(perm, p, chars_in, chars_out)
E 11
I 11
init_perm(perm, p, chars_in, chars_out)
E 11
	C_block perm[64/CHUNKBITS][1<<CHUNKBITS];
	unsigned char p[64];
	int chars_in, chars_out;
E 9
E 8
{
D 9
	register i, j, c;
	int temp;
	static char block[66], iobuf[16];
E 9
I 9
	register int i, j, k, l;
E 9
I 2

E 2
D 9
	for(i=0; i<66; i++)
		block[i] = 0;
	for(i=0; (c= *pw) && i<64; pw++){
		for(j=0; j<7; j++, i++)
			block[i] = (c>>(6-j)) & 01;
		i++;
E 9
I 9
	for (k = 0; k < chars_out*8; k++) {	/* each output bit position */
		l = p[k] - 1;		/* where this bit comes from */
		if (l < 0)
			continue;	/* output bit is always 0 */
		i = l>>LGCHUNKBITS;	/* which chunk this bit comes from */
		l = 1<<(l&(CHUNKBITS-1));	/* mask for this bit */
		for (j = 0; j < (1<<CHUNKBITS); j++) {	/* each chunk value */
			if ((j & l) != 0)
				perm[i][j].b[k>>3] |= 1<<(k&07);
		}
E 9
	}
D 9
	
	setkey(block);
	
	for(i=0; i<66; i++)
		block[i] = 0;
E 9
I 9
}
E 9
D 2

	for(i=0;i<48;i++)
		E[i] = e[i];
E 2

D 9
	for(i=0;i<2;i++){
		c = *salt++;
		iobuf[i] = c;
		if(c>'Z') c -= 6;
		if(c>'9') c -= 7;
		c -= '.';
		for(j=0;j<6;j++){
			if((c>>j) & 01){
				temp = E[6*i+j];
				E[6*i+j] = E[6*i+j+24];
				E[6*i+j+24] = temp;
				}
			}
E 9
I 9
/*
 * "setkey" routine (for backwards compatibility)
 */
D 15
void
E 15
setkey(key)
	register const char *key;
{
	register int i, j, k;
	C_block keyblock;

	for (i = 0; i < 8; i++) {
		k = 0;
		for (j = 0; j < 8; j++) {
			k <<= 1;
			k |= (unsigned char)*key++;
E 9
		}
D 9
	
	for(i=0; i<25; i++)
		encrypt(block,0);
	
	for(i=0; i<11; i++){
		c = 0;
		for(j=0; j<6; j++){
			c <<= 1;
			c |= block[6*i+j];
			}
		c += '.';
		if(c>'9') c += 7;
		if(c>'Z') c += 6;
		iobuf[i+2] = c;
E 9
I 9
		keyblock.b[i] = k;
E 9
	}
D 9
	iobuf[i+2] = 0;
	if(iobuf[1]==0)
		iobuf[1] = iobuf[0];
	return(iobuf);
E 9
I 9
D 15
	des_setkey((char *)keyblock.b);
E 15
I 15
D 17
	return(des_setkey((char *)keyblock.b));
E 17
I 17
	return (des_setkey((char *)keyblock.b));
E 17
E 15
E 9
}
I 9

/*
 * "encrypt" routine (for backwards compatibility)
 */
D 15
void
E 15
encrypt(block, flag)
	register char *block;
	int flag;
{
	register int i, j, k;
	C_block cblock;

	for (i = 0; i < 8; i++) {
		k = 0;
		for (j = 0; j < 8; j++) {
			k <<= 1;
			k |= (unsigned char)*block++;
		}
		cblock.b[i] = k;
	}
D 15
	des_cipher((char *)&cblock, (char *)&cblock, 0L, (flag? -1: 1));
E 15
I 15
	if (des_cipher((char *)&cblock, (char *)&cblock, 0L, (flag ? -1: 1)))
D 17
		return(1);
E 17
I 17
		return (1);
E 17
E 15
	for (i = 7; i >= 0; i--) {
		k = cblock.b[i];
		for (j = 7; j >= 0; j--) {
			*--block = k&01;
			k >>= 1;
		}
	}
I 15
D 17
	return(0);
E 17
I 17
	return (0);
E 17
E 15
}

#ifdef DEBUG
STATIC
prtab(s, t, num_rows)
	char *s;
	unsigned char *t;
	int num_rows;
{
	register int i, j;

D 13
	printf("%s:\n", s);
E 13
I 13
	(void)printf("%s:\n", s);
E 13
	for (i = 0; i < num_rows; i++) {
		for (j = 0; j < 8; j++) {
D 13
			 printf("%3d", t[i*8+j]);
E 13
I 13
			 (void)printf("%3d", t[i*8+j]);
E 13
		}
D 13
		printf("\n");
E 13
I 13
		(void)printf("\n");
E 13
	}
D 13
	printf("\n");
E 13
I 13
	(void)printf("\n");
E 13
}
#endif
E 9
E 1
