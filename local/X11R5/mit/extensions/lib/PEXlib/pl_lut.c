/* $XConsortium: pl_lut.c,v 1.8 92/10/27 15:43:42 mor Exp $ */

/******************************************************************************
Copyright 1987,1991 by Digital Equipment Corporation, Maynard, Massachusetts
Copyright 1992 by the Massachusetts Institute of Technology

                        All Rights Reserved

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that copyright
notice and this permission notice appear in supporting documentation, and that
the name of Digital or M.I.T. not be used in advertising or publicity
pertaining to distribution of the software without specific, written prior
permission.  Digital and M.I.T. make no representations about the suitability
of this software for any purpose.  It is provided "as is" without express or
implied warranty.

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.
******************************************************************************/

#include "PEXlib.h"
#include "PEXlibint.h"

static PEXPointer _PEXRepackLUTEntries();

#define GetLUTEntryBuffer(_numEntries, _entryType, _buf) \
    (_buf) = (char *) PEXAllocBuf ((_numEntries) * (sizeof (_entryType)));


PEXLookupTable
PEXCreateLookupTable (display, d, type)

INPUT Display	*display;
INPUT Drawable	d;
INPUT int	type;

{
    PEXLookupTable		id;
    pexCreateLookupTableReq	*req;


    /*
     * Get a lookup table resource id from X.
     */

    id = XAllocID (display);


    /*
     * Lock around critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (CreateLookupTable, req);
    req->drawableExample = d;
    req->lut = id;
    req->tableType = type;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (id);
}


void
PEXFreeLookupTable (display, lut)

INPUT Display		*display;
INPUT PEXLookupTable	lut;

{
    pexFreeLookupTableReq     *req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (FreeLookupTable, req);
    req->id = lut;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXCopyLookupTable (display, srcLut, destLut)

INPUT Display		*display;
INPUT PEXLookupTable	srcLut;
INPUT PEXLookupTable	destLut;

{
    pexCopyLookupTableReq     *req;


    /*
     * Lock around critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (CopyLookupTable, req);
    req->src = srcLut;
    req->dst = destLut;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


Status
PEXGetTableInfo (display, d, type, info)

INPUT Display		*display;
INPUT Drawable		d;
INPUT int		type;
INPUT PEXTableInfo	*info;

{
    pexGetTableInfoReq     	*req;
    pexGetTableInfoReply   	rep;


    /*
     * Lock around critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetReq (GetTableInfo, req);
    req->drawableExample = d;
    req->tableType = type;

    if (_XReply (display, &rep, 0, xTrue) == 0)
    {
	UnlockDisplay (display);
	PEXSyncHandle (display);
	return (0);            /* return an error */
    }

    info->definable_entries = rep.definableEntries;
    info->predefined_count = rep.numPredefined;
    info->predefined_min = rep.predefinedMin;
    info->predefined_max = rep.predefinedMax;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (1);
}


Status
PEXGetPredefinedEntries (display, d, type, start, count, entriesReturn)

INPUT Display		*display;
INPUT Drawable		d;
INPUT int		type;
INPUT unsigned int	start;
INPUT unsigned int	count;
OUTPUT PEXPointer	*entriesReturn;

{
    pexGetPredefinedEntriesReq		*req;
    pexGetPredefinedEntriesReply	rep;
    char				*pt;
    int					convertFP;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetFPReq (GetPredefinedEntries, req, convertFP);
    req->drawableExample = d;
    req->tableType = type;
    req->start = start;
    req->count = count;

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
	UnlockDisplay (display);
	PEXSyncHandle (display);
	*entriesReturn = NULL;
	return (0);          /* return an error */
    }


    /*
     * Read the reply into a scratch buffer, then repack the entries
     * into a buffer allocated for the application.
     */

    pt = (char *) _XAllocScratch (display, (unsigned long) (rep.length << 2));

    _XRead (display, (char *) pt, (long) (rep.length << 2));

    *entriesReturn = _PEXRepackLUTEntries (
	(char *) pt, (int) rep.numEntries, type);


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (1);
}


Status
PEXGetDefinedIndices (display, lut, numIndicesReturn, indicesReturn)

INPUT Display		*display;
INPUT PEXLookupTable	lut;
OUTPUT unsigned long	*numIndicesReturn;
OUTPUT PEXTableIndex	**indicesReturn;

{
    pexGetDefinedIndicesReq	*req;
    pexGetDefinedIndicesReply	rep;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetReq (GetDefinedIndices, req);
    req->id = lut;

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
	UnlockDisplay (display);
	PEXSyncHandle (display);
	*numIndicesReturn = 0;
	*indicesReturn = NULL;
	return (0);              /* return an error */
    }

    *numIndicesReturn = rep.numIndices;


    /*
     * Allocate a buffer for the replies to pass back to the user.
     */

    *indicesReturn = (PEXTableIndex *) PEXAllocBuf (
	(unsigned) (rep.length << 2));

    _XRead (display, (char *) *indicesReturn, (long) (rep.length << 2));


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (1);
}


PEXPointer
PEXGetTableEntry (display, lut, index, valueType,
    statusReturn, table_type_return)

INPUT Display		*display;
INPUT PEXLookupTable	lut;
INPUT unsigned int	index;
INPUT int		valueType;
OUTPUT int		*statusReturn;
OUTPUT int		*table_type_return;

{
    pexGetTableEntryReq		*req;
    pexGetTableEntryReply	rep;
    char			*pt;
    int				convertFP;
    PEXPointer			entryReturn;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetFPReq (GetTableEntry, req, convertFP);
    req->valueType = valueType;
    req->lut = lut;
    req->index = index;

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
	UnlockDisplay (display);
	PEXSyncHandle (display);
	return (NULL);               /* return an error */
    }

    *statusReturn = rep.status;
    *table_type_return = rep.tableType;


    /*
     * Read the reply into a scratch buffer, then repack the entries
     * into a buffer allocated for the application.
     */

    pt = (char *) _XAllocScratch (display, (unsigned long) (rep.length << 2));

    _XRead (display, (char *) pt, (long) (rep.length << 2));

    entryReturn = _PEXRepackLUTEntries ((char *) pt, 1, (int) rep.tableType);


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (entryReturn);
}


Status
PEXGetTableEntries (display, lut, start, count, valueType,
    table_type_return, entriesReturn)

INPUT Display		*display;
INPUT PEXLookupTable	lut;
INPUT unsigned int	start;
INPUT unsigned int	count;
INPUT int		valueType;
OUTPUT int		*table_type_return;
OUTPUT PEXPointer	*entriesReturn;

{
    pexGetTableEntriesReq	*req;
    pexGetTableEntriesReply	rep;
    char			*pt;
    int				convertFP;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetFPReq (GetTableEntries, req, convertFP);
    req->valueType = valueType;
    req->lut = lut;
    req->start = start;
    req->count = count;

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
	UnlockDisplay (display);
	PEXSyncHandle (display);
	*entriesReturn = NULL;
	return (0);         /* return an error */
    }

    *table_type_return = rep.tableType;


    /*
     * Read the reply into a scratch buffer, then repack the entries
     * into a buffer allocated for the application.
     */

    pt = (char *) _XAllocScratch (display, (unsigned long) (rep.length << 2));

    _XRead (display, (char *) pt, (long) (rep.length << 2));

    *entriesReturn = _PEXRepackLUTEntries ((char *) pt, (int) rep.numEntries,
	(int) rep.tableType);


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (1);
}


void
PEXSetTableEntries (display, lut, start, count, type, entries)

INPUT Display		*display;
INPUT PEXLookupTable	lut;
INPUT unsigned int	start;
INPUT unsigned int	count;
INPUT int		type;
INPUT PEXPointer	entries;

{
    pexSetTableEntriesReq	*req;
    int				sizeColor, size, i;
    int				convertFP;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetFPReq (SetTableEntries, req, convertFP);
    req->lut = lut;
    req->start = start;
    req->count = count;

    switch (type)
    {
    case PEXLUTLineBundle:
    {
	pexLineBundleEntry *dst, *dstStart;
	PEXLineBundleEntry *src = (PEXLineBundleEntry *) entries;
	
	dstStart = dst = (pexLineBundleEntry *)
	    _XAllocScratch (display, count * sizeof (PEXLineBundleEntry));

	for (i = 0; i < count; i++, src++)
	{
	    dst->lineType = src->type;
	    dst->polylineInterp = src->interp_method;
#ifdef WORD64
#else
	    dst->curveApprox = *(pexCurveApprox *) &(src->curve_approx);
#endif
	    dst->lineWidth = src->width;
	    
	    PackColorSpecifier (&(src->color), &(dst->lineColor), sizeColor);

	    dst = (pexLineBundleEntry *) ((char *) dst + 
		sizeof (pexLineBundleEntry) + sizeColor);
	}

	/* update the request length */
	size = (char *) dst - (char *) dstStart;
	req->length += (size + 3) >> 2;
	
	/* add the table entry data to the end of the X request */
	Data (display, (char *) dstStart, size);

	break;
    }

    case PEXLUTMarkerBundle:
    {
	pexMarkerBundleEntry *dst, *dstStart;
	PEXMarkerBundleEntry *src = (PEXMarkerBundleEntry *) entries;

	dstStart = dst = (pexMarkerBundleEntry *) _XAllocScratch (
	    display, count * sizeof (PEXMarkerBundleEntry));

	for (i = 0; i < count; i++, src++)
	{
	    dst->markerType = src->type;
	    dst->markerScale = src->scale;
	    
	    PackColorSpecifier (&(src->color), &(dst->markerColor), sizeColor);

	    dst = (pexMarkerBundleEntry *) ((char *) dst + 
		sizeof (pexMarkerBundleEntry) + sizeColor);
	}

	/* update the request length */
	size = (char *) dst - (char *) dstStart;
	req->length += (size + 3) >> 2;
	
	/* add the table entry data to the end of the X request */
	Data (display, (char *) dstStart, size);
	
	break;
    }

    case PEXLUTTextBundle:
    {
	pexTextBundleEntry *dst, *dstStart;
	PEXTextBundleEntry *src = (PEXTextBundleEntry *) entries;

	dstStart = dst = (pexTextBundleEntry *)
	    _XAllocScratch (display, count * sizeof (PEXTextBundleEntry));

	for (i = 0; i < count; i++, src++)
	{
	    dst->textFontIndex = src->font_index;
	    dst->textPrecision = src->precision;
	    dst->charExpansion = src->char_expansion;
	    dst->charSpacing = src->char_spacing;
	    
	    PackColorSpecifier (&(src->color), &(dst->textColor), sizeColor);

	    dst = (pexTextBundleEntry *) ((char *) dst + 
		sizeof (pexTextBundleEntry) + sizeColor);
	}

	/* update the request length */
	size = (char *) dst - (char *) dstStart;
	req->length += (size + 3) >> 2;

	/* add the table entry data to the end of the X request */
	Data (display, (char *) dstStart, size);

	break;
    }

    case PEXLUTInteriorBundle:
    {
	char *dst, *dstStart;
	PEXInteriorBundleEntry *src = (PEXInteriorBundleEntry *) entries;

	dstStart = dst = (char *) _XAllocScratch (display,
	    count * sizeof (PEXInteriorBundleEntry));

	for (i = 0; i < count; i++, src++)
	{
	    ((pexInteriorBundleEntry *) dst)->interiorStyle =
		src->style;
	    ((pexInteriorBundleEntry *) dst)->interiorStyleIndex =
		src->style_index;
	    ((pexInteriorBundleEntry *) dst)->reflectionModel =
		src->reflection_model;
	    ((pexInteriorBundleEntry *) dst)->surfaceInterp =
		src->interp_method;
	    ((pexInteriorBundleEntry *) dst)->bfInteriorStyle =
		src->bf_style;
	    ((pexInteriorBundleEntry *) dst)->bfInteriorStyleIndex =
		src->bf_style_index;
	    ((pexInteriorBundleEntry *) dst)->bfReflectionModel =
		src->bf_reflection_model;
	    ((pexInteriorBundleEntry *) dst)->bfSurfaceInterp =
		src->bf_interp_method;
#ifdef WORD64
#else
	    ((pexInteriorBundleEntry *) dst)->surfaceApprox =
		*(pexSurfaceApprox *) &(src->surface_approx);
#endif
	    dst += sizeof (pexInteriorBundleEntry);

	    /* copy surfaceColor */
	    PackColorSpecifier (&(src->color), dst, sizeColor);
	    dst += sizeof (pexColorSpecifier) + sizeColor;

	    /* copy reflectionAttr */
	    ((pexReflectionAttr *) dst)->ambient =
		src->reflection_attr.ambient;
	    ((pexReflectionAttr *) dst)->diffuse = 
		src->reflection_attr.diffuse;
	    ((pexReflectionAttr *) dst)->specular =
		src->reflection_attr.specular;
	    ((pexReflectionAttr *) dst)->specularConc = 
		src->reflection_attr.specular_conc;
	    ((pexReflectionAttr *) dst)->transmission = 
		src->reflection_attr.transmission;
	    PackColorSpecifier ( 
		&(src->reflection_attr.specular_color),
		&(((pexReflectionAttr *) dst)->specularColor), sizeColor);
	    dst += sizeof (pexReflectionAttr) + sizeColor;

	    /* copy bfSurfaceColor */
	    PackColorSpecifier (&(src->bf_color), dst, sizeColor);
	    dst += sizeof (pexColorSpecifier) + sizeColor;

	    /* copy bfReflectionAttr */
	    ((pexReflectionAttr *) dst)->ambient =
		src->bf_reflection_attr.ambient;
	    ((pexReflectionAttr *) dst)->diffuse =
		src->bf_reflection_attr.diffuse;
	    ((pexReflectionAttr *) dst)->specular = 
		src->bf_reflection_attr.specular;
	    ((pexReflectionAttr *) dst)->specularConc = 
		src->bf_reflection_attr.specular_conc;
	    ((pexReflectionAttr *) dst)->transmission = 
		src->bf_reflection_attr.transmission;
	    PackColorSpecifier ( 
		&(src->bf_reflection_attr.specular_color),
		&(((pexReflectionAttr *) dst)->specularColor), sizeColor);
	    dst += sizeof (pexReflectionAttr) + sizeColor;
	}
	
	/* update the request length */
	size = (char *) dst - (char *) dstStart;
	req->length += (size + 3) >> 2;
	
	/* add the table entry data to the end of the X request */
	Data (display, (char *) dstStart, size);

	break;
    }

    case PEXLUTEdgeBundle:
    {
	pexEdgeBundleEntry *dst, *dstStart;
	PEXEdgeBundleEntry *src = (PEXEdgeBundleEntry *) entries;

	dstStart = dst = (pexEdgeBundleEntry *)
	    _XAllocScratch (display, count * sizeof (PEXEdgeBundleEntry));

	for (i = 0; i < count; i++, src++)
	{
	    dst->edges = src->edge_flag;
	    dst->edgeType = src->type;
	    dst->edgeWidth = src->width;
	    
	    PackColorSpecifier (&(src->color), &(dst->edgeColor), sizeColor);

	    dst = (pexEdgeBundleEntry *) ((char *) dst + 
		sizeof (pexEdgeBundleEntry) + sizeColor);
	}

	/* update the request length */
	size = (char *) dst - (char *) dstStart;
	req->length += (size + 3) >> 2;
	
	/* add the table entry data to the end of the X request */
	Data (display, (char *) dstStart, size);

	break;
    }

    case PEXLUTPattern:
    {
	pexPatternEntry *dst, *dstStart;
	PEXPatternEntry *src = (PEXPatternEntry *)entries;

	size = count * sizeof (pexPatternEntry);
	for (i = 0; i < count; i++)
	{
	    size += (src[i].col_count *
		src[i].row_count * sizeof (PEXColor));
	}

	dstStart = dst = (pexPatternEntry *)
	    _XAllocScratch (display, (unsigned long) size);

	for (i = 0; i < count; i++, src++)
	{
	    dst->colorType = src->color_type;
	    dst->numx = src->col_count;
	    dst->numy = src->row_count;

	    sizeColor = GetColorSize (src->color_type);
	    sizeColor *= (src->col_count * src->row_count);
	    COPY_AREA ((char *) src->colors.indexed, &dst[1], sizeColor);

	    dst = (pexPatternEntry *) ((char *) dst + 
		sizeof (pexPatternEntry) + sizeColor);
	}

	/* update the request length */
	size = (char *) dst - (char *) dstStart;
	req->length += (size + 3) >> 2;

	/* add the table entry data to the end of the X request */
	Data (display, (char *) dstStart, size);

	break;
    }

    case PEXLUTTextFont:
    {
	pexTextFontEntry *dst, *dstStart;
	PEXTextFontEntry *src = (PEXTextFontEntry *)entries;

	size = count * sizeof (pexTextFontEntry);
	for (i = 0; i < count; i++)
	{
	    size += src[i].count * sizeof (pexFont);
	}

	dstStart = dst = (pexTextFontEntry *)
	    _XAllocScratch (display, (unsigned long) size);

	for (i = 0; i < count; i++, src++)
	{
	    dst->numFonts = src->count;
	    
	    COPY_AREA (src->fonts, &dst[1], src->count * sizeof (pexFont));

	    dst = (pexTextFontEntry *) ((char *) dst + 
		sizeof (pexTextFontEntry) + (src->count * sizeof (pexFont)));
	}

	/* update the request length */
	size = (char *) dst - (char *) dstStart;
	req->length += (size + 3) >> 2;

	/* add the table entry data to the end of the X request */
	Data (display, (char *) dstStart, size);
	
	break;
    }

    case PEXLUTColor:
    {
	pexColorSpecifier *dst, *dstStart;
	PEXColorEntry *src = (PEXColorEntry *) entries;

	dstStart = dst = (pexColorSpecifier *)
	    _XAllocScratch (display, count * sizeof (PEXColorEntry));

	for (i = 0; i < count; i++, src++)
	{
	    PackColorSpecifier (src, dst, sizeColor);
	    
	    dst = (pexColorSpecifier *) ((char *) dst + 
		sizeof (pexColorSpecifier) + sizeColor);
	}

	/* update the request length */
	size = (char *) dst - (char *) dstStart;
	req->length += (size + 3) >> 2;

	/* add the table entry data to the end of the X request */
	Data (display, (char *) dstStart, size);

	break;
    }

    case PEXLUTView:
        size = count * sizeof (PEXViewEntry);

        /* update the request length */
	req->length += (size + 3) >> 2;

	/* add the table entry data to the end of the X request */
	Data (display, (char *) entries, size);

	break;

     case PEXLUTLight:
     {
	 pexLightEntry *dst, *dstStart;
	 PEXLightEntry *src = (PEXLightEntry *) entries;

	 dstStart = dst = (pexLightEntry *)
	     _XAllocScratch (display, count * sizeof (PEXLightEntry));

	 for (i = 0; i < count; i++, src++)
	 {
	     dst->lightType = src->type;
#ifdef WORD64
#else
	     dst->direction = *(pexVector3D *) &(src->direction);
	     dst->point = *(pexCoord3D *) &(src->point);
#endif
	     dst->concentration = src->concentration;
	     dst->spreadAngle = src->spread_angle;
	     dst->attenuation1 = src->attenuation1;
	     dst->attenuation2 = src->attenuation2;
		
	     PackColorSpecifier (&(src->color), &(dst->lightColor), sizeColor);

	     dst = (pexLightEntry *) ((char *) dst + 
		 sizeof (pexLightEntry) + sizeColor);
	 }

	 /* update the request length */
	 size = (char *) dst - (char *) dstStart;
	 req->length += (size + 3) >> 2;

	 /* add the table entry data to the end of the X request */
	 Data (display, (char *) dstStart, size);
	 
	 break;
     }

     case PEXLUTDepthCue:
     {
	 pexDepthCueEntry *dst, *dstStart;
	 PEXDepthCueEntry *src = (PEXDepthCueEntry *) entries;

	 dstStart = dst = (pexDepthCueEntry *)
	     _XAllocScratch (display, count * sizeof (PEXDepthCueEntry));

	 for (i = 0; i < count; i++, src++)
	 {
	     dst->mode = src->mode;
	     dst->frontPlane = src->front_plane;
	     dst->backPlane = src->back_plane;
	     dst->frontScaling = src->front_scaling;
	     dst->backScaling = src->back_scaling;
	     
	     PackColorSpecifier (&(src->color), &(dst->depthCueColor), 
		 sizeColor);

	     dst = (pexDepthCueEntry *) ((char *) dst + 
		 sizeof (pexDepthCueEntry) + sizeColor);
	 }

	 /* update the request length */
	 size = (char *) dst - (char *) dstStart;
	 req->length += (size + 3) >> 2;
	 
	 /* add the table entry data to the end of the X request */
	 Data (display, (char *) dstStart, size);

	 break;
     }

     case PEXLUTColorApprox:
	size = count * sizeof (PEXColorApproxEntry);

	/* update the request length */
	req->length += (size + 3) >> 2;

	/* add the table entry data to the end of the X request */
	Data (display, (char *) entries, size);
	break;
    }


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXDeleteTableEntries (display, lut, start, count)

INPUT Display		*display;
INPUT PEXLookupTable	lut;
INPUT unsigned int	start;
INPUT unsigned int	count;

{
    pexDeleteTableEntriesReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (DeleteTableEntries, req);
    req->lut = lut;
    req->start = start;
    req->count = count;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}



/* This routine repacks the lut entries returned by PEXGetTableEntry,
 * PEXGetTableEntries, and PEXGetPredefinedEntries.  This is mostly to
 * change the colors, which may be of different sizes, to a fixed size
 * to make it easier for application programs.  This isn't the fastest
 * way to process replies that have no colors, but it's not expected to
 * be used a whole lot.
*/

static PEXPointer
_PEXRepackLUTEntries (pt, numEntries, type)

INPUT  char		*pt;
INPUT  int		numEntries;
INPUT  int		type;

{
    int			sizeColor, i;
    char		*buf;


    switch (type)
    {
    case PEXLUTLineBundle:
    {
	PEXLineBundleEntry *dst;
	pexLineBundleEntry *src = (pexLineBundleEntry *) pt;

	GetLUTEntryBuffer (numEntries, PEXLineBundleEntry, buf);
	dst = (PEXLineBundleEntry *) buf;

	for (i = 0; i < numEntries; i++, dst++)
	{
	    dst->type = src->lineType;
	    dst->interp_method = src->polylineInterp;
#ifdef WORD64
#else
	    dst->curve_approx = *(PEXCurveApprox *) &(src->curveApprox);
#endif
	    dst->width = src->lineWidth;

	    PackColorSpecifier (&(src->lineColor), &(dst->color), sizeColor);

	    src = (pexLineBundleEntry *) ((char *) src +
		sizeof (pexLineBundleEntry) + sizeColor);
	}

	break;
    }

    case PEXLUTMarkerBundle:
    {
	PEXMarkerBundleEntry *dst;
	pexMarkerBundleEntry *src = (pexMarkerBundleEntry *) pt;

	GetLUTEntryBuffer (numEntries, PEXMarkerBundleEntry, buf);
	dst = (PEXMarkerBundleEntry *) buf;

	for (i = 0; i < numEntries; i++, dst++)
	{
	    dst->type = src->markerType;
	    dst->scale = src->markerScale;
	    
	    PackColorSpecifier (&(src->markerColor), &(dst->color), sizeColor);

	    src = (pexMarkerBundleEntry *) ((char *) src +
		sizeof (pexMarkerBundleEntry) + sizeColor);
	}

	break;
    }

    case PEXLUTTextBundle:
    {
	PEXTextBundleEntry *dst;
	pexTextBundleEntry *src = (pexTextBundleEntry *) pt;
	    
	GetLUTEntryBuffer (numEntries, PEXTextBundleEntry, buf);
	dst = (PEXTextBundleEntry *) buf;

	for (i = 0; i < numEntries; i++, dst++)
	{
	    dst->font_index = src->textFontIndex;
	    dst->precision = src->textPrecision;
	    dst->char_expansion = src->charExpansion;
	    dst->char_spacing = src->charSpacing;
	    
	    PackColorSpecifier (&(src->textColor), &(dst->color), sizeColor);

	    src = (pexTextBundleEntry *) ((char *) src +
		sizeof (pexTextBundleEntry) + sizeColor);
	}

	break;
    }

    case PEXLUTInteriorBundle:
    {
	PEXInteriorBundleEntry *dst;
	char *src = (char *) pt;

	GetLUTEntryBuffer (numEntries, PEXInteriorBundleEntry, buf);
	dst = (PEXInteriorBundleEntry *) buf;

	for (i = 0; i < numEntries; i++, dst++)
	{
	    dst->style =
		((pexInteriorBundleEntry *) src)->interiorStyle;
	    dst->style_index =
		((pexInteriorBundleEntry *) src)->interiorStyleIndex;
	    dst->reflection_model =
		((pexInteriorBundleEntry *) src)->reflectionModel;
	    dst->interp_method =
		((pexInteriorBundleEntry *) src)->surfaceInterp;
	    dst->bf_style =
		((pexInteriorBundleEntry *) src)->bfInteriorStyle;
	    dst->bf_style_index =
		((pexInteriorBundleEntry *) src)->bfInteriorStyleIndex;
	    dst->bf_reflection_model =
		((pexInteriorBundleEntry *) src)->bfReflectionModel;
	    dst->bf_interp_method =
		((pexInteriorBundleEntry *) src)->bfSurfaceInterp;
#ifdef WORD64
#else
	    dst->surface_approx = *(PEXSurfaceApprox *)
		&(((pexInteriorBundleEntry *) src)->surfaceApprox);
#endif
	    src += sizeof (pexInteriorBundleEntry);

	    /* copy surfaceColor */
	    PackColorSpecifier (src, &(dst->color), sizeColor);
	    src += sizeof (pexColorSpecifier) + sizeColor;

	    /* copy reflectionAttr */
	    dst->reflection_attr.ambient = 
		((pexReflectionAttr *) src)->ambient;
	    dst->reflection_attr.diffuse =
		((pexReflectionAttr *) src)->diffuse;
	    dst->reflection_attr.specular =
		((pexReflectionAttr *) src)->specular;
	    dst->reflection_attr.specular_conc =
		((pexReflectionAttr *) src)->specularConc;
	    dst->reflection_attr.transmission =
		((pexReflectionAttr *) src)->transmission;
	    PackColorSpecifier (
                &(((pexReflectionAttr *)src)->specularColor),
                &(dst->reflection_attr.specular_color), sizeColor);
	    src += sizeof (pexReflectionAttr) + sizeColor;

	    /* copy bfSurfaceColor */
	    PackColorSpecifier (src, &(dst->bf_color), sizeColor);
	    src += sizeof (pexColorSpecifier) + sizeColor;

	    /* copy bfReflectionAttr */
	    dst->bf_reflection_attr.ambient =
		((pexReflectionAttr *) src)->ambient;
	    dst->bf_reflection_attr.diffuse =
		((pexReflectionAttr *) src)->diffuse;
	    dst->bf_reflection_attr.specular =
		((pexReflectionAttr *) src)->specular;
	    dst->bf_reflection_attr.specular_conc =
		((pexReflectionAttr *) src)->specularConc;
	    dst->bf_reflection_attr.transmission =
		((pexReflectionAttr *) src)->transmission;
	    PackColorSpecifier (
                &(((pexReflectionAttr *) src)->specularColor),
                &(dst->bf_reflection_attr.specular_color), sizeColor);
	    src += sizeof (pexReflectionAttr) + sizeColor;
	}

	break;
    }

    case PEXLUTEdgeBundle:
    {
	PEXEdgeBundleEntry *dst;
	pexEdgeBundleEntry *src = (pexEdgeBundleEntry *) pt;
         
	GetLUTEntryBuffer (numEntries, PEXEdgeBundleEntry, buf);
	dst = (PEXEdgeBundleEntry *) buf;

	for (i = 0; i < numEntries; i++, dst++)
	{
	    dst->edge_flag = src->edges;
	    dst->type = src->edgeType;
	    dst->width = src->edgeWidth;

	    PackColorSpecifier (&(src->edgeColor), &(dst->color), sizeColor);

	    src = (pexEdgeBundleEntry *) ((char *) src +
		sizeof (pexEdgeBundleEntry) + sizeColor);
	}

	break;
    }

    case PEXLUTPattern:
    {
	PEXPatternEntry *dst;
	pexPatternEntry *src = (pexPatternEntry *)pt;
    
	GetLUTEntryBuffer (numEntries, PEXPatternEntry, buf);
	dst = (PEXPatternEntry *) buf;

	for (i = 0; i < numEntries; i++, dst++)
	{
	    dst->color_type = src->colorType;
	    dst->col_count = src->numx;
	    dst->row_count = src->numy;

	    sizeColor = GetColorSize (src->colorType);
	    sizeColor *= (src->numx * src->numy);
	    dst->colors.indexed =
		(PEXColorIndexed *) PEXAllocBuf ((unsigned) sizeColor);
	    COPY_AREA (&src[1], (char *) dst->colors.indexed, sizeColor);

	    src = (pexPatternEntry *) ((char *) src +
		sizeof (pexPatternEntry) + sizeColor);
	}
	break;
    }

    case PEXLUTTextFont:
    {
	PEXTextFontEntry *dst;
	pexTextFontEntry *src = (pexTextFontEntry *) pt;

	GetLUTEntryBuffer (numEntries, PEXTextFontEntry, buf);
	dst = (PEXTextFontEntry *) buf;

	for (i = 0; i < numEntries; i++, dst++)
	{
	    dst->count = src->numFonts;
	    dst->fonts = (pexFont *)
		PEXAllocBuf (src->numFonts * sizeof (pexFont));
	    
	    COPY_AREA (&src[1], dst->fonts,
		src->numFonts * sizeof (pexFont));

	    src = (pexTextFontEntry *) ((char *) src + 
		sizeof (pexTextFontEntry) +
		(src->numFonts * sizeof (pexFont)));
	}
	
	break;
    }

    case PEXLUTColor:
    {
	PEXColorEntry *dst;
	pexColorSpecifier *src = (pexColorSpecifier *) pt;
    
	GetLUTEntryBuffer (numEntries, PEXColorEntry, buf);
	dst = (PEXColorEntry *) buf;

	for (i = 0; i < numEntries; i++, dst++)
	{
	    PackColorSpecifier (src, dst, sizeColor);

	    src = (pexColorSpecifier *) ((char *) src +
		sizeof (pexColorSpecifier) + sizeColor);
	}
    
	break;
    }

    case PEXLUTView:
	GetLUTEntryBuffer (numEntries, PEXViewEntry, buf);

	COPY_AREA ((char *) pt, (char *) buf,
	    numEntries * sizeof (pexViewEntry));

	break;

    case PEXLUTLight:
    {
	PEXLightEntry *dst;
	pexLightEntry *src = (pexLightEntry *) pt;
	
	GetLUTEntryBuffer (numEntries, PEXLightEntry, buf);
	dst = (PEXLightEntry *) buf;

	for (i = 0; i < numEntries; i++, dst++)
	{
	    dst->type = src->lightType;
#ifdef WORD64
#else
	    dst->direction = *(PEXVector *) &(src->direction);
	    dst->point = *(PEXCoord *) &(src->point);
#endif
	    dst->concentration = src->concentration;
	    dst->spread_angle = src->spreadAngle;
	    dst->attenuation1 = src->attenuation1;
	    dst->attenuation2 = src->attenuation2;
	    
	    PackColorSpecifier (&(src->lightColor), &(dst->color), sizeColor);

	    src = (pexLightEntry *) ((char *) src +
		sizeof (pexLightEntry) + sizeColor);
	}

	break;
    }

    case PEXLUTDepthCue:
    {
	PEXDepthCueEntry *dst;
	pexDepthCueEntry *src = (pexDepthCueEntry *) pt;
    
	GetLUTEntryBuffer (numEntries, PEXDepthCueEntry, buf);
	dst = (PEXDepthCueEntry *) buf;
	
	for (i = 0; i < numEntries; i++, dst++)
	{
	    dst->mode = src->mode;
	    dst->front_plane = src->frontPlane;
	    dst->back_plane = src->backPlane;
	    dst->front_scaling = src->frontScaling;
	    dst->back_scaling = src->backScaling;
	    
	    PackColorSpecifier (&(src->depthCueColor), &(dst->color),
                sizeColor);

	    src = (pexDepthCueEntry *) ((char *) src +
		sizeof (pexDepthCueEntry) + sizeColor);
	}

	break;
    }

    case PEXLUTColorApprox:
	GetLUTEntryBuffer (numEntries, PEXColorApproxEntry, buf);

	COPY_AREA ((char *) pt, (char *) buf,
	    numEntries * sizeof (pexColorApproxEntry));

        break;
    }

    return ((PEXPointer) buf);
}

