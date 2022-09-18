/* $XConsortium: PEXtempl.h,v 5.1 91/02/16 09:48:55 rws Exp $ */

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

/* Useful templates for reading and writing PEX buffers. */

#ifndef PEXTEMPL_H
#define PEXTEMPL_H

typedef union {
	pexIndexedColour	indexed;
	pexRgb8Colour		rgb8;
	pexRgb16Colour		rgb16;
	pexRgbFloatColour	rgbFloat;
	pexHsvColour		hsvFloat;
	pexHlsColour		hlsFloat;
	pexCieColour		cieFloat;
} Pextmpl_colour_format;

typedef struct {
    pexColourSpecifier		type;
    Pextmpl_colour_format	format;
} Pextmpl_colour_spec;

#endif /* PEXTEMPL_H */

