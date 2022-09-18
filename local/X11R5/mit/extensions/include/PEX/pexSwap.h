/* $XConsortium: pexSwap.h,v 5.5 92/03/04 14:08:10 hersh Exp $ */

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
 *	Swapping information used by both the dipex portions of the
 *	server and by the archive sections of the api.
 */

#ifndef PEXSWAP_H
#define PEXSWAP_H 1

#include <X11/extensions/PEXErr.h>

typedef void	    (*ConvFunction)();
typedef void	    (*SwapShortFunction)();
typedef void	    (*SwapLongFunction)();
typedef ErrorCode   (*OCFunction)();

typedef struct {
    SwapShortFunction	ConvertCARD16;
    SwapLongFunction	ConvertCARD32;
    ConvFunction	ConvertFLOAT;
} pexSwap;

extern void SwapCARD16();
extern void SwapCARD32();
extern void  SwapFLOAT();
extern void  ConvertFLOAT();

/* not sure if this is the right place for this */
extern void SwapPEXMaxHitsReachedEvent();

#endif
