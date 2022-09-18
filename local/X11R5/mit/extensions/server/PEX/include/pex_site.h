/* $XConsortium: pex_site.h,v 5.1 91/02/16 09:57:43 rws Exp $ */

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

#ifndef PEX_SITE
#define PEX_SITE 1


/*
	Server native formats
 */
#define LOCAL_PEX_NAME "X3D-PEX"
#define PEX_VENDOR "X3D-PEX Sample Implementation"
#define PEX_RELEASE_NUMBER 0
#define PEX_SUBSET PEXCompleteImplementation

#define	SERVER_NATIVE_FP	PEXIeee_754_32
#define OTHER_FP		PEXDEC_F_Floating
#define SERVER_SUPPORTED_COLOURS	PEXRgbFloatColour

/*
	Server supported formats
 */
#define CHECK_FP_FORMAT(FP) \
    if ((FP != PEXIeee_754_32) && (FP != PEXDEC_F_Floating)) { \
	err = PEX_ERROR_CODE(PEXFloatingPointFormatError); \
	PEX_ERR_EXIT(err,0,cntxtPtr); }

#define CHECK_COLOUR_FORMAT(C) \
    if (C != SERVER_SUPPORTED_COLOURS) { \
	err = PEX_ERROR_CODE(PEXDirectColourFormatError); \
	PEX_ERR_EXIT(err,0,cntxtPtr); }


/*
	Font path
 */
#ifdef FONTDIR
#define FONT_DIRECTORY FONTDIR/PEXfonts
#endif

#endif
