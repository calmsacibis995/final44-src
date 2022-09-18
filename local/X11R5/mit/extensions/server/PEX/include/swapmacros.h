/* $XConsortium: swapmacros.h,v 5.3 91/07/01 16:26:23 hersh Exp $ */

/***********************************************************
Copyright 1989, 1990, 1991 by Sun Microsystems, Inc. and the X Consortium.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Sun Microsystems,
the X Consortium, and MIT not be used in advertising or publicity 
pertaining to distribution of the software without specific, written 
prior permission.  

SUN MICROSYSTEMS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, 
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT 
SHALL SUN MICROSYSTEMS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL 
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/


/* 
 * swapmacros.h - Macros used for byte swapping. and float converting
 * 
 * Copyright 1988-1991
 * Center for Information Technology Integration (CITI)
 * Information Technology Division
 * University of Michigan
 * Ann Arbor, Michigan
 *
 *                         All Rights Reserved
 * 
 * Permission to use, copy, modify, and distribute this software and
 * its documentation for any purpose and without fee is hereby
 * granted, provided that the above copyright notice appear in all
 * copies and that both that copyright notice and this permission
 * notice appear in supporting documentation, and that the names of
 * CITI or THE UNIVERSITY OF MICHIGAN not be used in advertising or
 * publicity pertaining to distribution of the software without
 * specific, written prior permission.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS." CITI AND THE UNIVERSITY OF
 * MICHIGAN DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN
 * NO EVENT SHALL CITI OR THE UNIVERSITY OF MICHIGAN BE LIABLE FOR ANY
 * SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
 * AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 */

#include "misc.h"

/* byteswap a long in place.  (given a pointer) */
#define pswaplong(x, n)\
    n = ((char *) (x))[0];\
    ((char *) (x))[0] = ((char *) (x))[3];\
    ((char *) (x))[3] = n;\
    n = ((char *) (x))[1];\
    ((char *) (x))[1] = ((char *) (x))[2];\
    ((char *) (x))[2] = n

/* byteswap a short in place.  (given a pointer) */
#define pswapshort(x, n)\
    n = ((char *) (x))[0];\
    ((char *) (x))[0] = ((char *) (x))[1];\
    ((char *) (x))[1] = n

/* byteswaps as above but no pointer is given. */
#define swaplong(x, n) pswaplong(&(x), n)
#define swapshort(x, n) pswapshort(&(x), n)

/* byte swap AND COPY a long (given pointer) */
#define pswaplongc(x, y)\
    ((char *) (y))[3] = ((char *) (x))[0];\
    ((char *) (y))[0] = ((char *) (x))[3];\
    ((char *) (y))[2] = ((char *) (x))[1];\
    ((char *) (y))[1] = ((char *) (x))[2]

/* byte swap AND COPY a short (given pointer) */
#define pswapshortc(x, y)\
    ((char *) (y))[1] = ((char *) (x))[0];\
    ((char *) (y))[0] = ((char *) (x))[1]

#define swaplongc(x, y) pswaplongc(&(x), &(y))
#define swapshortc(x, y) pswapshortc(&(x), &(y))
#define swapfloatc(x, y) pswapfloatc(&(x), &(y)) /* float convert and swap */
#define plaincopy(x, y) (y)=(x)

    /* Macros below swap and convert a FLOAT in place.  This is still SLOW.
     * The ones which copy have been made 5x10 times faster so we use them.
     */
#define swapConvFloat(x, n) pswaplong((CARD32 *)&(x), n); convFloat(x)
#define pswapConvFloat(x, n) pswaplong((CARD32 *)(x), n); pconvFloat(x)



#if (TargetFloat == DEC_F_Floating)	/* IEEE to VAX conversions */

	/* exponent needs += 2, */
	/* bit 0 of byte 0 is bit 1 of the exponent */
	/* also we swap the word as two shorts!! */
#define pswapfloatc(x, y)\
    ((char *) (y))[1] = (((char *) (x))[0]+1);\
    ((char *) (y))[0] = ((char *) (x))[1];\
    ((char *) (y))[3] = ((char *) (x))[2];\
    ((char *) (y))[2] = ((char *) (x))[3]

#define pswapConvFloatc(x, y)\
if ((*((CARD32 *)(x)) == 0)|| (((((char *)(x))[0] + 1) & 0x7f) == 0))\
    *((float *)y) = 0.0; else { pswapfloatc(x, y); }

#define swapConvFloatc(x, y) \
if (((*((CARD32 *)&(x))) == 0)|| (((((char *)&(x))[0] + 1) & 0x7f) == 0))\
    y = 0.0; else { swapfloatc(x, y); }

    
#define pconvFloatc(x, y) *(PEXFLOAT *)(y) = ConvertIEEEtoVax((PEXFLOAT *)(x))
#define convFloatc(x, y) (y) = ConvertIEEEtoVax((PEXFLOAT *)&(x))
#define pconvFloat(x) *(PEXFLOAT *)(x) = ConvertIEEEtoVax((PEXFLOAT *)(x))
#define convFloat(x) (x) = ConvertIEEEtoVax((PEXFLOAT *)&(x))

#else					/* VAX to IEEE conversions */

	/* exponent needs -= 2, */
	/* bit 0 of byte 1 is bit 1 of the exponent */ 
	/* also we swap the word as two shorts!! */
#define pswapfloatc(x, y)\
    ((char *) (y))[0] = (((char *) (x))[1]-1);\
    ((char *) (y))[1] = ((char *) (x))[0];\
    ((char *) (y))[3] = ((char *) (x))[2];\
    ((char *) (y))[2] = ((char *) (x))[3]

#define pswapConvFloatc(x, y) \
if ((*((CARD32 *)(x)) == 0)|| ((( ((char *)(x))[1] - 1) & 0x7f) == 0x7f)) \
    *((float *)y) = 0.0; else { pswapfloatc(x, y); }

#define swapConvFloatc(x, y) \
if (((*((CARD32 *)&(x))) == 0)|| (((((char *)&(x))[1] - 1) & 0x7f) == 0x7f))\
    y = 0.0; else { swapfloatc(x, y); }

#define pconvFloatc(x, y) *(PEXFLOAT *)(y) = ConvertVaxToIEEE((PEXFLOAT *)(x))
#define convFloatc(x, y) (y) = ConvertVaxToIEEE((PEXFLOAT *)&(x))
#define pconvFloat(x) *(PEXFLOAT *)(x) = ConvertVaxToIEEE((PEXFLOAT *)(x))
#define convFloat(x) (x) = ConvertVaxToIEEE((PEXFLOAT *)&(x))
#endif



