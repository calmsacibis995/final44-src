h64532
s 00009/00000/00079
d D 8.2 94/03/21 13:50:27 bostic 3 2
c add add a copyright  noitce
e
s 00000/00000/00079
d D 8.1 93/06/10 21:36:18 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00079/00000/00000
d D 7.1 92/06/05 15:35:25 hibler 1 0
c merge latest Utah hp300 code including 68040 support
e
u
U
t
T
I 3
/*-
 * Copyright (c) 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 3
I 1
/*
 * Derived from X11R4
 */

/* the following notes use the following conventions:
SCREEN LEFT				SCREEN RIGHT
in this file and maskbits.c, left and right refer to screen coordinates,
NOT bit numbering in registers.

starttab[n]
	bits[0,n-1] = 0	bits[n,31] = 1
endtab[n] =
	bits[0,n-1] = 1	bits[n,31] = 0

maskbits(x, w, startmask, endmask, nlw)
	for a span of width w starting at position x, returns
a mask for ragged bits at start, mask for ragged bits at end,
and the number of whole longwords between the ends.

*/

#define maskbits(x, w, startmask, endmask, nlw) \
    startmask = starttab[(x)&0x1f]; \
    endmask = endtab[((x)+(w)) & 0x1f]; \
    if (startmask) \
	nlw = (((w) - (32 - ((x)&0x1f))) >> 5); \
    else \
	nlw = (w) >> 5;

#define FASTGETBITS(psrc, x, w, dst) \
    asm ("bfextu %3{%1:%2},%0" \
    : "=d" (dst) : "di" (x), "di" (w), "o" (*(char *)(psrc)))

#define FASTPUTBITS(src, x, w, pdst) \
    asm ("bfins %3,%0{%1:%2}" \
	 : "=o" (*(char *)(pdst)) \
	 : "di" (x), "di" (w), "d" (src), "0" (*(char *) (pdst)))

#define getandputrop(psrc, srcbit, dstbit, width, pdst, rop) \
{ \
  register unsigned int _tmpsrc, _tmpdst; \
  FASTGETBITS(pdst, dstbit, width, _tmpdst); \
  FASTGETBITS(psrc, srcbit, width, _tmpsrc); \
  DoRop(_tmpdst, rop, _tmpsrc, _tmpdst); \
  FASTPUTBITS(_tmpdst, dstbit, width, pdst); \
}

#define getandputrop0(psrc, srcbit, width, pdst, rop) \
    	getandputrop(psrc, srcbit, 0, width, pdst, rop)

#define getunalignedword(psrc, x, dst) { \
        register int _tmp; \
        FASTGETBITS(psrc, x, 32, _tmp); \
        dst = _tmp; \
}

#define fnCLEAR(src, dst)       (0)
#define fnCOPY(src, dst)        (src)
#define fnXOR(src, dst)         (src ^ dst)
#define fnCOPYINVERTED(src, dst)(~src)

#define DoRop(result, alu, src, dst) \
{ \
    if (alu == RR_COPY) \
        result = fnCOPY (src, dst); \
    else \
        switch (alu) \
        { \
          case RR_CLEAR: \
            result = fnCLEAR (src, dst); \
            break; \
          case RR_XOR: \
            result = fnXOR (src, dst); \
            break; \
          case RR_COPYINVERTED: \
            result = fnCOPYINVERTED (src, dst); \
            break; \
        } \
}
E 1
