/* $XConsortium: pexLookup.h,v 5.1 91/02/16 09:57:42 rws Exp $ */

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

#ifndef PEX_LOOKUP_H
#define PEX_LOOKUP_H	1

#include "resource.h"
#include "dipex.h"

/*	PEX types	*/

#define LU_PEXFONT(id, ptr) \
    if (! ((ptr) = (diFontHandle) LookupIDByType ((id), PEXFontType)) ) { \
	err = PEX_ERROR_CODE(PEXFontError); \
	PEX_ERR_EXIT(err,(id),cntxtPtr); }

#define LU_TABLE(id, ptr) \
    if (! ((ptr) = (diLUTHandle) LookupIDByType ((id), PEXLutType)) ) { \
	err = PEX_ERROR_CODE(PEXLookupTableError); \
	PEX_ERR_EXIT(err,(id),cntxtPtr); }

#define LU_NAMESET(id,ns_handle) \
    if (! (ns_handle = (diNSHandle) LookupIDByType ((id), PEXNameType)) ) { \
	err = PEX_ERROR_CODE(PEXNameSetError); \
	PEX_ERR_EXIT(err,(id),cntxtPtr); }

#define LU_PHIGSWKS(id,ptr) \
    if (! ((ptr) = (dipexPhigsWks *) LookupIDByType ((id), PEXWksType)) ) { \
	err = PEX_ERROR_CODE(PEXPhigsWksError); \
	PEX_ERR_EXIT(err,(id),cntxtPtr); }

#define LU_PICKMEASURE(id,ptr) \
    if (! ((ptr) = (diPMHandle) LookupIDByType ((id), PEXPickType)) ) { \
	err = PEX_ERROR_CODE(PEXPickMeasureError); \
	PEX_ERR_EXIT(err,(id),cntxtPtr); }

#define LU_PIPELINECONTEXT(id,ptr) \
    if (! ((ptr) = (ddPCStr *) LookupIDByType ((id), PEXPipeType)) ) { \
	err = PEX_ERROR_CODE(PEXPipelineContextError); \
	PEX_ERR_EXIT(err,(id),cntxtPtr); }

#define LU_RENDERER(id, ptr) \
    if (! ((ptr) = (ddRendererStr *)LookupIDByType((id), PEXRendType)) ) { \
	err = PEX_ERROR_CODE(PEXRendererError); \
	PEX_ERR_EXIT(err,(id),cntxtPtr); }

#define LU_SEARCHCONTEXT(id,ptr) \
    if (! ((ptr) = (ddSCStr *) LookupIDByType ((id), PEXSearchType)) ) { \
	err = PEX_ERROR_CODE(PEXSearchContextError); \
	PEX_ERR_EXIT(err,(id),cntxtPtr); }

#define LU_STRUCTURE(id,ptr) \
    if (! ((ptr) = (diStructHandle) LookupIDByType ((id), PEXStructType))) {\
	err = PEX_ERROR_CODE(PEXStructureError); \
	PEX_ERR_EXIT(err,(id),cntxtPtr); }


/*	Other useful types	*/

#define LU_DRAWABLE(id,ptr) \
    if (!((ptr) = (DrawablePtr) LookupIDByClass ((id), RC_DRAWABLE))) { \
	err = BadDrawable; \
	PEX_ERR_EXIT(err,(id),cntxtPtr); }


#endif
