/* $XConsortium: OCprim.h,v 5.2 92/03/04 14:19:20 hersh Exp $ */

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

LOCAL_FLAG unsigned char * SWAP_FUNC_PREFIX(SwapFacet) ();
LOCAL_FLAG unsigned char * SWAP_FUNC_PREFIX(SwapColourSpecifier) ();
LOCAL_FLAG unsigned char * SWAP_FUNC_PREFIX(SwapReflectionAttr) ();

LOCAL_FLAG void 
	SWAP_FUNC_PREFIX(SwapMonoEncoding) ();

LOCAL_FLAG ErrorCode
	SWAP_FUNC_PREFIX(PEXModelClipVolume) (),
	SWAP_FUNC_PREFIX(PEXModelClipVolume2D) (),
	SWAP_FUNC_PREFIX(PEXAddToNameSet) (),
	SWAP_FUNC_PREFIX(PEXMarker) (),
	SWAP_FUNC_PREFIX(PEXMarker2D) (),
	SWAP_FUNC_PREFIX(PEXPolyline) (),
	SWAP_FUNC_PREFIX(PEXPolyline2D) (),
	SWAP_FUNC_PREFIX(PEXPolylineSet) (),
	SWAP_FUNC_PREFIX(PEXNurbCurve) (),
	SWAP_FUNC_PREFIX(PEXFillArea) (),
	SWAP_FUNC_PREFIX(PEXFillArea2D) (),
	SWAP_FUNC_PREFIX(PEXExtFillArea) (),
	SWAP_FUNC_PREFIX(PEXFillAreaSet) (),
	SWAP_FUNC_PREFIX(PEXFillAreaSet2D) (),
	SWAP_FUNC_PREFIX(PEXExtFillAreaSet) (),
	SWAP_FUNC_PREFIX(PEXTriangleStrip) (),
	SWAP_FUNC_PREFIX(PEXQuadrilateralMesh) (),
	SWAP_FUNC_PREFIX(PEXSOFAS) (),
	SWAP_FUNC_PREFIX(PEXNurbSurface) (),
	SWAP_FUNC_PREFIX(PEXCellArray) (),
	SWAP_FUNC_PREFIX(PEXCellArray2D) (),
	SWAP_FUNC_PREFIX(PEXExtCellArray) (),
	SWAP_FUNC_PREFIX(PEXGdp) (),
	SWAP_FUNC_PREFIX(PEXGdp2D) (),
	SWAP_FUNC_PEX_PFX(Text) (),
	SWAP_FUNC_PEX_PFX(Text2D) (),
	SWAP_FUNC_PEX_PFX(AnnotationText) (),
	SWAP_FUNC_PEX_PFX(AnnotationText2D) (),
	SWAP_FUNC_PEX_PFX(ParaSurfCharacteristics) (),
	SWAP_FUNC_PREFIX(PEXNoop) ();
