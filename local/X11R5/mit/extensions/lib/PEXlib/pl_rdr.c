/* $XConsortium: pl_rdr.c,v 1.6 92/08/26 13:06:20 mor Exp $ */

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

static void _PEXGenerateRendererList();


PEXRenderer
PEXCreateRenderer (display, d, valueMask, values)

INPUT Display			*display;
INPUT Drawable			d;
INPUT unsigned long		valueMask;
INPUT PEXRendererAttributes 	*values;

{
    pexCreateRendererReq	*req;
    PEXRenderer			rdr;
    int				convertFP;


    /*
     * Get a renderer resource id from X.
     */

    rdr = XAllocID (display);


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     * For the value mask, turn off the Current Path and Renderer State bits,
     * since these attributes are not modifiable.
     */

    valueMask &= ~(PEXRACurrentPath | PEXRARendererState);

    PEXGetFPReq (CreateRenderer, req, convertFP);
    req->drawable = d;
    req->rdr = rdr;
    req->itemMask = valueMask;

    _PEXGenerateRendererList (display, (pexReq *) req, valueMask, values);


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (rdr);
}


void
PEXFreeRenderer (display, renderer)

INPUT Display		*display;
INPUT PEXRenderer	renderer;

{
    pexFreeRendererReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (FreeRenderer, req);
    req->id = renderer;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


PEXRendererAttributes *
PEXGetRendererAttributes (display, renderer, valueMask)

INPUT Display			*display;
INPUT PEXRenderer		renderer;
INPUT unsigned long		valueMask;

{
    pexGetRendererAttributesReq		*req;
    pexGetRendererAttributesReply	rep;
    PEXRendererAttributes		*prdra;
    unsigned long			*pv;
    unsigned long			f;
    int					size, i, n;
    int					sizeColor;
    int					convertFP;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetFPReq (GetRendererAttributes, req, convertFP);
    req->rdr = renderer;
    req->itemMask = valueMask;

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
        return (NULL);            /* return an error */
    }


    /*
     * Allocate a scratch buffer and copy the reply data to the buffer.
     */

    pv = (unsigned long *) _XAllocScratch (display,
	(unsigned long) (rep.length << 2));

    _XRead (display, (char *) pv, (long) (rep.length << 2));


    /*
     * Allocate a buffer for the replies to pass back to the client.
     */

    prdra = (PEXRendererAttributes *)
        PEXAllocBuf ((unsigned) (sizeof (PEXRendererAttributes)));

    prdra->current_path.count = 0;
    prdra->current_path.elements = NULL;
    prdra->clip_list.count = 0;
    prdra->clip_list.rectangles = NULL;
    prdra->pick_start_path.count = 0;
    prdra->pick_start_path.elements = NULL;

    for (i = 0; i < (PEXRAMaxShift + 1); i++)
    {
	f = (1L << i);
	if (valueMask & f)
	{
            switch (f)
	    {
	    case PEXRACurrentPath:
		n = *pv;
		pv++;
		prdra->current_path.count = n;
		size = n * sizeof (PEXElementRef);
		prdra->current_path.elements =
		    (PEXElementRef *) PEXAllocBuf ((unsigned) size);
		COPY_AREA ((char *) pv,
		    (char *) prdra->current_path.elements, size);
		pv += NUMWORDS (size);
		break;
	    case PEXRAPipelineContext:
		prdra->pipeline_context = *((PEXPipelineContext *) pv);
		pv++;
		break;
	    case PEXRAMarkerBundle:
		prdra->marker_bundle = *((PEXLookupTable *) pv);
		pv++;
		break;
	    case PEXRATextBundle:
		prdra->text_bundle = *((PEXLookupTable *) pv);
		pv++;
		break;
	    case PEXRALineBundle:
		prdra->line_bundle = *((PEXLookupTable *) pv);
		pv++;
		break;
	    case PEXRAInteriorBundle:
		prdra->interior_bundle = *((PEXLookupTable *) pv);
		pv++;
		break;
	    case PEXRAEdgeBundle:
		prdra->edge_bundle = *((PEXLookupTable *) pv);
		pv++;
		break;
	    case PEXRAViewTable:
		prdra->view_table = *((PEXLookupTable *) pv);
		pv++;
		break;
	    case PEXRAColorTable:
		prdra->color_table = *((PEXLookupTable *) pv);
		pv++;
		break;
	    case PEXRADepthCueTable:
		prdra->depth_cue_table = *((PEXLookupTable *) pv);
		pv++;
		break;
	    case PEXRALightTable:
		prdra->light_table = *((PEXLookupTable *) pv);
		pv++;
		break;
	    case PEXRAColorApproxTable:
		prdra->color_approx_table = *((PEXLookupTable *) pv);
		pv++;
		break;
	    case PEXRAPatternTable:
		prdra->pattern_table = *((PEXLookupTable *) pv);
		pv++;
		break;
	    case PEXRATextFontTable:
		prdra->text_font_table = *((PEXLookupTable *) pv);
		pv++;
		break;
	    case PEXRAHighlightIncl:
		prdra->highlight_incl = *((PEXNameSet *) pv);
		pv++;
		break;
	    case PEXRAHighlightExcl:
		prdra->highlight_excl = *((PEXNameSet *) pv);
		pv++;
		break;
	    case PEXRAInvisibilityIncl:
		prdra->invisibility_incl = *((PEXNameSet *) pv);
		pv++;
		break;
	    case PEXRAInvisibilityExcl:
		prdra->invisibility_excl = *((PEXNameSet *) pv);
		pv++;
		break;
	    case PEXRARendererState:
		prdra->renderer_state = *pv;
		pv++;
		break;
	    case PEXRAHLHSRMode:
		prdra->hlhsr_mode = *pv;
		pv++;
		break;
	    case PEXRANPCSubVolume:
		prdra->npc_subvolume = *((PEXNPCSubVolume *) pv);
		pv += LENOF (pexNpcSubvolume);
		break;
	    case PEXRAViewport:
		prdra->viewport = *((PEXViewport *) pv);
		pv += LENOF (pexViewport);
		break;
	    case PEXRAClipList:
		n = *pv;
		pv++;
		prdra->clip_list.count = n;
		size = n * sizeof (PEXDeviceRect);
		prdra->clip_list.rectangles =
		    (PEXDeviceRect *) PEXAllocBuf ((unsigned) size);
		COPY_AREA ((char *) pv,
		    (char *) (prdra->clip_list.rectangles), size);
		pv += NUMWORDS (size);
		break;
	    case PEXRAPickIncl:
		prdra->pick_incl = *((PEXNameSet *) pv);
		pv++;
		break;
	    case PEXRAPickExcl:
		prdra->pick_excl = *((PEXNameSet *) pv);
		pv++;
		break;
	    case PEXRAPickStartPath:
		n = *pv;
		pv++;
		prdra->pick_start_path.count = n;
		size = n * sizeof (PEXElementRef);
		prdra->pick_start_path.elements =
		    (PEXElementRef *) PEXAllocBuf ((unsigned) size);
		COPY_AREA ((char *) pv,
		    (char *) prdra->pick_start_path.elements, size);
		pv += NUMWORDS (size);
		break;
	    case PEXRABackgroundColor:
		PackColorSpecifier (pv, &(prdra->background_color),
		    sizeColor);
		pv += NUMWORDS (sizeof (pexColorSpecifier) + sizeColor); 
		break;
	    case PEXRAClearImage:
		prdra->clear_image = *pv;
		pv++;
		break;
	    case PEXRAClearZ:
		prdra->clear_z = *pv;
		pv++;
		break;
	    case PEXRAEchoMode:
		prdra->echo_mode = *pv;
		pv++;
		break;
	    }
	}
    }


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (prdra);
}


Status
PEXGetRendererDynamics (display, renderer, tablesReturn,
    namesetsReturn, attributesReturn)

INPUT Display			*display;
INPUT PEXRenderer		renderer;
OUTPUT unsigned long		*tablesReturn;
OUTPUT unsigned long		*namesetsReturn;
OUTPUT unsigned long		*attributesReturn;

{
    pexGetRendererDynamicsReq		*req;
    pexGetRendererDynamicsReply		rep;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetReq (GetRendererDynamics, req);
    req->id = renderer;

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
	*tablesReturn = *namesetsReturn = *attributesReturn = 0;
        return (0);	            /* return an error */
    }

    *tablesReturn = rep.tables;
    *namesetsReturn = rep.namesets;
    *attributesReturn = rep.attributes;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (1);
}


void
PEXChangeRenderer (display, renderer, valueMask, values)

INPUT Display			*display;
INPUT PEXRenderer		renderer;
INPUT unsigned long		valueMask;
INPUT PEXRendererAttributes 	*values;

{
    pexChangeRendererReq	*req;
    int				convertFP;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     * For the item mask, turn off the Current Path and Renderer State
     * attributes, since these are not modifiable.
     */

    valueMask &= ~(PEXRACurrentPath | PEXRARendererState);

    PEXGetFPReq (ChangeRenderer, req, convertFP);
    req->rdr = renderer;
    req->itemMask = valueMask;

    _PEXGenerateRendererList (display, (pexReq *) req, valueMask, values);


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXBeginRendering (display, d, renderer)

INPUT Display		*display;
INPUT Drawable		d;
INPUT PEXRenderer	renderer;

{
    pexBeginRenderingReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (BeginRendering, req);
    req->rdr = renderer;
    req->drawable = d;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXEndRendering (display, renderer, flush)

INPUT Display		*display;
INPUT PEXRenderer	renderer;
INPUT int		flush;

{
    pexEndRenderingReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (EndRendering, req);
    req->rdr = renderer;
    req->flushFlag = flush;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXBeginStructure (display, renderer, id)

INPUT Display		*display;
INPUT PEXRenderer	renderer;
INPUT long		id;

{
    pexBeginStructureReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (BeginStructure, req);
    req->rdr = renderer;
    req->sid = id;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXEndStructure (display, renderer)

INPUT Display		*display;
INPUT PEXRenderer	renderer;

{
    pexEndStructureReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (EndStructure, req);
    req->id = renderer;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXRenderNetwork (display, d, renderer, structure)

INPUT Display		*display;
INPUT Drawable		d;
INPUT PEXRenderer	renderer;
INPUT PEXStructure	structure;

{
    pexRenderNetworkReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (RenderNetwork, req);
    req->rdr = renderer;
    req->drawable = d;
    req->sid = structure;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXRenderElements (display, renderer, sid, whence1, offset1, whence2, offset2)

INPUT Display		*display;
INPUT PEXRenderer	renderer;
INPUT PEXStructure	sid;
INPUT int		whence1;
INPUT long		offset1;
INPUT int		whence2;
INPUT long		offset2;

{
    pexRenderElementsReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (RenderElements, req);
    req->rdr = renderer;
    req->sid = sid;
    req->range.position1.whence = whence1;
    req->range.position1.offset = offset1;
    req->range.position2.whence = whence2;
    req->range.position2.offset = offset2;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXAccumulateState (display, renderer, numElements, elements)

INPUT Display		*display;
INPUT PEXRenderer	renderer;
INPUT unsigned long	numElements;
INPUT PEXElementRef	*elements;

{
    pexAccumulateStateReq	*req;
    unsigned int		size;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    size = numElements * sizeof (PEXElementRef);

    PEXGetReqExtra (AccumulateState, size, req);
    req->rdr = renderer;
    req->numElRefs = numElements;

    COPY_AREA (elements, ((char *) &req[1]), size);


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}



/*
 * Routine to write a packed list of renderer attributes to the
 * transport buffer.
 */

static void
_PEXGenerateRendererList (display, req, valueMask, values)

INPUT Display             	*display;
INPUT pexReq		    	*req;
INPUT unsigned long       	valueMask;
INPUT PEXRendererAttributes 	*values;

{
    CARD32		*pv, *pvSend;
    int			i, n, length;
    int			sizeColor;
    unsigned long	size, f;


    /*
     * Count the number of attributes being set, then allocate a
     * scratch buffer used to pack the attributes.  It's not worth
     * computing the exact amount of memory needed, so assume
     * worse case.
     */

    CountOnes (valueMask, n);
    size =  n * sizeof (CARD32) + 
	sizeof (pexNpcSubvolume) +
	sizeof (pexViewport) +
	sizeof (pexColorSpecifier);

    if (valueMask & PEXRAClipList)
    {
	size += values->clip_list.count * sizeof (pexDeviceRect);
    }

    if (valueMask & PEXRAPickStartPath)
    {
	size += values->pick_start_path.count * sizeof (pexElementRef);
    }

    pv = pvSend = (CARD32 *) _XAllocScratch (display, (unsigned long) size);


    /*
     * Pack the attributes.
     */

    for (i = 0; i < (PEXRAMaxShift + 1); i++)
    {
	f = (1L << i);
	if (valueMask & f)
	{
            switch (f)
	    {
	    case PEXRACurrentPath:
		/*
		 * Current path doesn't make sense in a new or changed
		 * renderer, so ignore it.
		 */
		break;
	    case PEXRAPipelineContext:
		*((pexPC *) pv) = values->pipeline_context;
		pv++;
		break;
	    case PEXRAMarkerBundle:
		*((pexLookupTable *) pv) = values->marker_bundle;
		pv++;
		break;
	    case PEXRATextBundle:
		*((pexLookupTable *) pv) = values->text_bundle;
		pv++;
		break;
	    case PEXRALineBundle:
		*((pexLookupTable *) pv) = values->line_bundle;
		pv++;
		break;
	    case PEXRAInteriorBundle:
		*((pexLookupTable *) pv) = values->interior_bundle;
		pv++;
		break;
	    case PEXRAEdgeBundle:
		*((pexLookupTable *) pv) = values->edge_bundle;
		pv++;
		break;
	    case PEXRAViewTable:
		*((pexLookupTable *) pv) = values->view_table;
		pv++;
		break;
	    case PEXRAColorTable:
		*((pexLookupTable *) pv) = values->color_table;
		pv++;
		break;
	    case PEXRADepthCueTable:
		*((pexLookupTable *) pv) = values->depth_cue_table;
		pv++;
		break;
	    case PEXRALightTable:
		*((pexLookupTable *) pv) = values->light_table;
		pv++;
		break;
	    case PEXRAColorApproxTable:
		*((pexLookupTable *) pv) = values->color_approx_table;
		pv++;
		break;
	    case PEXRAPatternTable:
		*((pexLookupTable *) pv) = values->pattern_table;
		pv++;
		break;
	    case PEXRATextFontTable:
		*((pexLookupTable *) pv) = values->text_font_table;
		pv++;
		break;
	    case PEXRAHighlightIncl:
		*((pexNameSet *) pv) = values->highlight_incl;
		pv++;
		break;
	    case PEXRAHighlightExcl:
		*((pexNameSet *) pv) = values->highlight_excl;
		pv++;
		break;
	    case PEXRAInvisibilityIncl:
		*((pexNameSet *) pv) = values->invisibility_incl;
		pv++;
		break;
	    case PEXRAInvisibilityExcl:
		*((pexNameSet *) pv) = values->invisibility_excl;
		pv++;
		break;
	    case PEXRARendererState:
		/*
		 * Renderer state doesn't make sense in a new or changed
		 * renderer, so ignore it.
		 */
		break;
	    case PEXRAHLHSRMode:
		*pv = values->hlhsr_mode;
		pv++;
		break;
	    case PEXRANPCSubVolume:
#ifdef WORD64
#else
		*((pexNpcSubvolume *) pv) =
		    *(pexNpcSubvolume *) &(values->npc_subvolume);
#endif
		pv += LENOF (pexNpcSubvolume);
		break;
	    case PEXRAViewport:
#ifdef WORD64
#else
		*((pexViewport *) pv) =
		    *(pexViewport *) &(values->viewport);
#endif
		pv += LENOF (pexViewport);
		break;
	    case PEXRAClipList:
		length = values->clip_list.count;
		*pv = length;
		pv++;
		length *= sizeof (pexDeviceRect);
		COPY_AREA ((char *) values->clip_list.rectangles,
		    (char *) pv, length);
		pv += NUMWORDS (length);
		break;
	    case PEXRAPickIncl:
		*((pexNameSet *) pv) = values->pick_incl;
		pv++;
		break;
	    case PEXRAPickExcl:
		*((pexNameSet *) pv) = values->pick_excl;
		pv++;
		break;
	    case PEXRAPickStartPath:
		length = values->pick_start_path.count;
		*pv = length;
		pv++;
		length *= sizeof (pexElementRef);
		COPY_AREA (values->pick_start_path.elements, pv, length);
		pv = (CARD32 *) ((char *) pv + length);
		break;
	    case PEXRABackgroundColor:
		PackColorSpecifier (&(values->background_color),
		    pv, sizeColor);
		pv += NUMWORDS (sizeof (pexColorSpecifier) + sizeColor); 
		break;
	    case PEXRAClearImage:
		*pv = values->clear_image;
		pv++;
		break;
	    case PEXRAClearZ:
		*pv = values->clear_z;
		pv++;
		break;
	    case PEXRAEchoMode:
		*pv = values->echo_mode;
		pv++;
		break;
	    }
	}
    }

    length = pv - pvSend;
    req->length += length;

    Data (display, (char *) pvSend, (length << 2));
}
