/* $XConsortium: pl_wks.c,v 1.8 92/08/26 13:06:25 mor Exp $ */

/******************************************************************************
Copyright 1987,1991 by Digital Equipment Corporation, Maynard, Massachusetts
Copyright 1992 by ShoGraphics, Inc., Mountain View, California
Copyright 1992 by the Massachusetts Institute of Technology

                        All Rights Reserved

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that copyright
notice and this permission notice appear in supporting documentation, and that
the name of Digital, ShowGraphics, or M.I.T. not be used in advertising or
publicity pertaining to distribution of the software without specific, written
prior permission.  Digital, ShowGraphics, and M.I.T. make no representations
about the suitability of this software for any purpose.  It is provided "as is"
without express or implied warranty.

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

SHOGRAPHICS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
SHOGRAPHICS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.
*************************************************************************/

#include "PEXlib.h"
#include "PEXlibint.h"


PEXWorkstation
PEXCreateWorkstation (display, drawable, lineBundle, markerBundle, textBundle,
    interiorBundle, edgeBundle, colorTable, patternTable, textFontTable,
    depthCueTable, lightTable, colorApproxTable, highlightIncl,
    highlightExcl, invisibilityIncl, invisibilityExcl, bufferMode)

INPUT Display		*display;
INPUT Drawable		drawable;
INPUT PEXLookupTable	lineBundle;
INPUT PEXLookupTable	markerBundle;
INPUT PEXLookupTable	textBundle;
INPUT PEXLookupTable	interiorBundle;
INPUT PEXLookupTable	edgeBundle;
INPUT PEXLookupTable	colorTable;
INPUT PEXLookupTable	patternTable;
INPUT PEXLookupTable	textFontTable;
INPUT PEXLookupTable	depthCueTable;
INPUT PEXLookupTable	lightTable;
INPUT PEXLookupTable	colorApproxTable;
INPUT PEXNameSet	highlightIncl;
INPUT PEXNameSet	highlightExcl;
INPUT PEXNameSet	invisibilityIncl;
INPUT PEXNameSet	invisibilityExcl;
INPUT int		bufferMode;

{
    pexCreateWorkstationReq	*req;
    PEXWorkstation		wks;


    /*
     * Get a Phigs Workstation resource id from X.
     */

    wks = XAllocID (display);


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (CreateWorkstation, req);
    req->drawable = drawable;
    req->wks = wks;
    req->lineBundle = lineBundle;
    req->markerBundle = markerBundle;
    req->textBundle = textBundle;
    req->interiorBundle = interiorBundle;
    req->edgeBundle = edgeBundle;
    req->colorTable = colorTable;
    req->patternTable = patternTable;
    req->textFontTable = textFontTable;
    req->depthCueTable = depthCueTable;
    req->lightTable = lightTable;
    req->colorApproxTable = colorApproxTable;
    req->highlightIncl = highlightIncl;
    req->highlightExcl = highlightExcl;
    req->invisIncl = invisibilityIncl;
    req->invisExcl = invisibilityExcl;
    req->bufferMode = bufferMode;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (wks);
}


void
PEXFreeWorkstation (display, wks)

INPUT Display		*display;
INPUT PEXWorkstation	wks;

{
    pexFreeWorkstationReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (FreeWorkstation, req);
    req->id = wks;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


PEXWorkstationAttributes *
PEXGetWorkstationAttributes (display, wks, valueMask)

INPUT Display		*display;
INPUT PEXWorkstation	wks;
INPUT unsigned long	*valueMask;

{
    pexGetWorkstationAttributesReq	*req;
    pexGetWorkstationAttributesReply	rep;
    PEXWorkstationAttributes		*ppwi;
    unsigned long			*pv;
    Bool				bitSet;
    int					i, size;
    int					convertFP;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetFPReq (GetWorkstationAttributes, req, convertFP);
    req->wks = wks;
    req->itemMask0 = valueMask[0];
    req->itemMask1 = valueMask[1];

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

    ppwi = (PEXWorkstationAttributes *)
        PEXAllocBuf ((unsigned) (sizeof (PEXWorkstationAttributes)));

    ppwi->defined_views.count = 0;
    ppwi->defined_views.views = NULL;
    ppwi->posted_structures.count = 0;
    ppwi->posted_structures.structures = NULL;

    for (i = 0; i < (PEXPWMaxShift + 1); i++)
    {
	bitSet = valueMask[i >> 5] & (1L << (i & 0x1f));
	if (bitSet != 0)
	{
	    switch (i)
	    {
	    case PEXPWDisplayUpdate:
		ppwi->drawable_update = *pv;
		pv++;
		break;
	    case PEXPWVisualState:
		ppwi->visual_state = *pv;
		pv++;
		break;
	    case PEXPWDisplaySurface:
		ppwi->drawable_surface = *pv;
		pv++;
		break;
	    case PEXPWViewUpdate:
		ppwi->view_update = *pv;
		pv++;
		break;
	    case PEXPWDefinedViews:
		size = *((int *) pv);
		pv++;
		ppwi->defined_views.count = size;
		size *= sizeof (pexTableIndex);
		ppwi->defined_views.views = 
		    (PEXTableIndex *) PEXAllocBuf ((unsigned) size);
		COPY_AREA ((char *) pv,
		    (char *) (ppwi->defined_views.views), size);
		pv += NUMWORDS (size);
		break;
	    case PEXPWWorkstationUpdate:
		ppwi->wks_update = *pv;
		pv++;
		break;
	    case PEXPWReqNPCSubVolume:
		ppwi->req_npc_subvolume = *((PEXNPCSubVolume *) pv);
		pv += LENOF (pexNpcSubvolume);
		break;
	    case PEXPWCurNPCSubVolume:
		ppwi->cur_npc_subvolume = *((PEXNPCSubVolume *) pv);
		pv += LENOF (pexNpcSubvolume);
		break;
	    case PEXPWReqViewport:
		ppwi->req_workstation_viewport = *((PEXViewport *) pv);
		pv += LENOF (pexViewport);
		break;
	    case PEXPWCurViewport:
		ppwi->cur_workstation_viewport = *((PEXViewport *) pv);
		pv += LENOF (pexViewport);
		break;
	    case PEXPWHLHSRUpdate:
		ppwi->hlhsr_update = *pv;
		pv++;
		break;
	    case PEXPWReqHLHSRMode:
		ppwi->req_hlhsr_mode = *pv;
		pv++;
		break;
	    case PEXPWCurHLHSRMode:
		ppwi->cur_hlhsr_mode = *pv;
		pv++;
		break;
	    case PEXPWDrawable:
		ppwi->drawable = *((Drawable *) pv);
		pv += LENOF (Drawable);
		break;
	    case PEXPWMarkerBundle:
		ppwi->marker_bundle = *((PEXLookupTable *) pv);
		pv += LENOF (pexLookupTable);
		break;
	    case PEXPWTextBundle:
		ppwi->text_bundle = *((PEXLookupTable *) pv);
		pv += LENOF (pexLookupTable);
		break;
	    case PEXPWLineBundle:
		ppwi->line_bundle = *((PEXLookupTable *) pv);
		pv += LENOF (pexLookupTable);
		break;
	    case PEXPWInteriorBundle:
		ppwi->interior_bundle = *((PEXLookupTable *) pv);
		pv += LENOF (pexLookupTable);
		break;
	    case PEXPWEdgeBundle:
		ppwi->edge_bundle = *((PEXLookupTable *) pv);
		pv += LENOF (pexLookupTable);
		break;
	    case PEXPWColorTable:
		ppwi->color_table = *((PEXLookupTable *) pv);
		pv += LENOF (pexLookupTable);
		break;
	    case PEXPWDepthCueTable:
		ppwi->depth_cue_table = *((PEXLookupTable *) pv);
		pv += LENOF (pexLookupTable);
		break;
	    case PEXPWLightTable:
		ppwi->light_table = *((PEXLookupTable *) pv);
		pv += LENOF (pexLookupTable);
		break;
	    case PEXPWColorApproxTable:
		ppwi->color_approx_table = *((PEXLookupTable *) pv);
		pv += LENOF (pexLookupTable);
		break;
	    case PEXPWPatternTable:
		ppwi->pattern_table = *((PEXLookupTable *) pv);
		pv += LENOF (pexLookupTable);
		break;
	    case PEXPWTextFontTable:
		ppwi->text_font_table = *((PEXLookupTable *) pv);
		pv += LENOF (pexLookupTable);
		break;
	    case PEXPWHighlightIncl:
		ppwi->highlight_incl = *((PEXNameSet *) pv);
		pv += LENOF (pexNameSet);
		break;
	    case PEXPWHighlightExcl:
		ppwi->highlight_excl = *((PEXNameSet *) pv);
		pv += LENOF (pexNameSet);
		break;
	    case PEXPWInvisibilityIncl:
		ppwi->invisibility_incl = *((PEXNameSet *) pv);
		pv += LENOF (pexNameSet);
		break;
	    case PEXPWInvisibilityExcl:
		ppwi->invisibility_excl = *((PEXNameSet *) pv);
		pv += LENOF (pexNameSet);
		break;
	    case PEXPWPostedStructures:
		size = *((int *) pv);
		pv++;
		ppwi->posted_structures.count = size;
		size *= sizeof (pexStructureInfo);
		ppwi->posted_structures.structures = 
		    (PEXPostedStructure *) PEXAllocBuf ((unsigned) size);
		COPY_AREA ((char *) pv,
		    (char *) (ppwi->posted_structures.structures), size);
		pv += NUMWORDS (size);
		break;
	    case PEXPWNumPriorities:
		ppwi->count_priorities = *pv;
		pv++;
		break;
	    case PEXPWBufferUpdate:
		ppwi->buffer_update = *pv;
		pv++;
		break;
	    case PEXPWReqBufferMode:
		ppwi->req_buffer_mode = *pv;
		pv++;
		break;
	    case PEXPWCurBufferMode:
		ppwi->cur_buffer_mode = *pv;
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

    return (ppwi);
}


Status
PEXGetWorkstationDynamics (display, d, dynamics)

INPUT Display			*display;
INPUT Drawable			d;
INPUT PEXWorkstationDynamics	*dynamics;

{
    pexGetWorkstationDynamicsReq	*req;
    pexGetWorkstationDynamicsReply	rep;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetReq (GetWorkstationDynamics, req);
    req->drawable = d;

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
        return (0);            /* return an error */
    }


    /*
     * Fill in the dynamics.
     */

    dynamics->view_rep = rep.viewRep;
    dynamics->marker_bundle = rep.markerBundle;
    dynamics->text_bundle = rep.textBundle;
    dynamics->line_bundle = rep.lineBundle;
    dynamics->interior_bundle = rep.interiorBundle;
    dynamics->edge_bundle = rep.edgeBundle;
    dynamics->color_table = rep.colorTable;
    dynamics->pattern_table = rep.patternTable;
    dynamics->wks_transform = rep.wksTransform;
    dynamics->highlight_filter = rep.highlightFilter;
    dynamics->invisibility_filter = rep.invisibilityFilter;
    dynamics->hlhsr_mode = rep.HlhsrMode;
    dynamics->structure_modify = rep.structureModify;
    dynamics->post_structure = rep.postStructure;
    dynamics->unpost_structure = rep.unpostStructure;
    dynamics->delete_structure = rep.deleteStructure;
    dynamics->reference_modify = rep.referenceModify;
    dynamics->buffer_modify = rep.bufferModify;
    dynamics->light_table = rep.lightTable;
    dynamics->depth_cue_table = rep.depthCueTable;
    dynamics->color_approx_table = rep.colorApproxTable;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (1);
}


Status
PEXGetWorkstationViewRep (display, wks, index,
    viewUpdateReturn, reqViewReturn, curViewReturn)

INPUT Display		*display;
INPUT PEXWorkstation	wks;
INPUT unsigned int	index;
OUTPUT int		*viewUpdateReturn;
OUTPUT PEXViewRep	*reqViewReturn;
OUTPUT PEXViewRep	*curViewReturn;

{
    pexGetWorkstationViewRepReq		*req;
    pexGetWorkstationViewRepReply	rep;
    unsigned long			*pv;
    int					convertFP;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetFPReq (GetWorkstationViewRep, req, convertFP);
    req->wks = wks;
    req->index = index;


    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
        return (0);            /* return an error */
    }

    *viewUpdateReturn = rep.viewUpdate;


    /*
     * Allocate a scratch buffer and copy the reply data to the buffer.
     */

    pv = (unsigned long *) _XAllocScratch (display,
        (unsigned long) (rep.length << 2));

    _XRead (display, (char *) pv, (long) (rep.length << 2));


    /*
     * Fill in the current and requested view reps.
     */

    reqViewReturn->index = *pv;
    pv ++;
    reqViewReturn->view.clip_flags = *pv;
    pv++;

#ifdef WORD64
#else
    reqViewReturn->view.clip_limits = *((PEXNPCSubVolume *) pv);
#endif
    pv += LENOF (pexNpcSubvolume);

    COPY_AREA ((char *) pv,
        (char *) (reqViewReturn->view.orientation), sizeof (pexMatrix));
    pv += LENOF (pexMatrix);
    COPY_AREA ((char *) pv, (char *) (reqViewReturn->view.mapping),
	 sizeof (pexMatrix));
    pv += LENOF (pexMatrix);

    curViewReturn->index = *pv;
    pv++;
    curViewReturn->view.clip_flags = *pv;
    pv++;

#ifdef WORD64
#else
    curViewReturn->view.clip_limits = *((PEXNPCSubVolume *) pv);
#endif
    pv += LENOF (pexNpcSubvolume);

    COPY_AREA ((char *) pv,
        (char *)(curViewReturn->view.orientation), sizeof (pexMatrix));
    pv += LENOF (pexMatrix);
    COPY_AREA ((char *) pv, (char *) (curViewReturn->view.mapping),
        sizeof (pexMatrix));
    pv += LENOF (pexMatrix);


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (1);
}


Status
PEXGetWorkstationPostings (display, structure, numWksReturn, wksReturn)

INPUT Display		*display;
INPUT PEXStructure	structure;
OUTPUT unsigned long	*numWksReturn;
OUTPUT PEXWorkstation	**wksReturn;

{
    pexGetWorkstationPostingsReq	*req;
    pexGetWorkstationPostingsReply	rep;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetReq (GetWorkstationPostings, req);
    req->id = structure;

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
	*wksReturn = NULL;
        return (0);            /* return an error */
    }

    *numWksReturn = rep.length;


    /*
     * Allocate a buffer for the replies to pass back to the client.
     */

    *wksReturn = (PEXWorkstation *) PEXAllocBuf (
	(unsigned) (rep.length << 2));

    _XRead (display, (char *) *wksReturn, (long) (rep.length << 2));


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (1);
}


void
PEXSetWorkstationViewPriority (display, wks, index1, index2, priority)

INPUT Display		*display;
INPUT PEXWorkstation	wks;
INPUT unsigned int	index1;
INPUT unsigned int	index2;
INPUT int		priority;

{
    pexSetWorkstationViewPriorityReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (SetWorkstationViewPriority, req);
    req->wks = wks;
    req->index1 = index1;
    req->index2 = index2;
    req->priority = priority;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXSetWorkstationDisplayUpdateMode (display, wks, displayUpdate)

INPUT Display		*display;
INPUT PEXWorkstation	wks;
INPUT int		displayUpdate;

{
    pexSetWorkstationDisplayUpdateModeReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (SetWorkstationDisplayUpdateMode, req);
    req->wks = wks;
    req->displayUpdate = displayUpdate;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXSetWorkstationBufferMode (display, wks, bufferMode)

INPUT Display		*display;
INPUT PEXWorkstation	wks;
INPUT int		bufferMode;

{
    pexSetWorkstationBufferModeReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (SetWorkstationBufferMode, req);
    req->wks = wks;
    req->bufferMode = bufferMode;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXSetWorkstationViewRep (display, wks, viewIndex, values)

INPUT Display		*display;
INPUT PEXWorkstation	wks;
INPUT unsigned int	viewIndex;
INPUT PEXViewEntry	*values;

{
    pexSetWorkstationViewRepReq		*req;
    int					convertFP;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetFPReq (SetWorkstationViewRep, req, convertFP);
    req->wks = wks;
    req->viewRep.index = viewIndex;
#ifdef WORD64
#else
    req->viewRep.view = *(pexViewEntry *) values;
#endif


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXSetWorkstationWindow (display, wks, npcSubvolume)

INPUT Display		*display;
INPUT PEXWorkstation	wks;
INPUT PEXNPCSubVolume	*npcSubvolume;

{
    pexSetWorkstationWindowReq	*req;
    int				convertFP;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetFPReq (SetWorkstationWindow, req, convertFP);
    req->wks = wks;
#ifdef WORD64
#else
    req->npcSubvolume = *(pexNpcSubvolume *) npcSubvolume;
#endif


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXSetWorkstationViewport (display, wks, viewport)

INPUT Display		*display;
INPUT PEXWorkstation	wks;
INPUT PEXViewport	*viewport;

{
    pexSetWorkstationViewportReq	*req;
    int					convertFP;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetFPReq (SetWorkstationViewport, req, convertFP);
    req->wks = wks;
#ifdef WORD64
#else
    req->viewport = *(pexViewport *) viewport;
#endif


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXSetWorkstationHLHSRMode (display, wks, hlhsrMode)

INPUT Display		*display;
INPUT PEXWorkstation	wks;
INPUT int		hlhsrMode;

{
    pexSetWorkstationHLHSRModeReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (SetWorkstationHLHSRMode, req);
    req->wks = wks;
    req->mode = (pexEnumTypeIndex)hlhsrMode;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXRedrawAllStructures (display, wks)

INPUT Display		*display;
INPUT PEXWorkstation	wks;

{
    pexRedrawAllStructuresReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (RedrawAllStructures, req);
    req->id = wks;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXUpdateWorkstation (display, wks)

INPUT Display		*display;
INPUT PEXWorkstation	wks;

{
    pexUpdateWorkstationReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (UpdateWorkstation, req);
    req->id = wks;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXExecuteDeferredActions (display, wks)

INPUT Display		*display;
INPUT PEXWorkstation	wks;

{
    pexExecuteDeferredActionsReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (ExecuteDeferredActions, req);
    req->id = wks;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


Status
PEXMapDCToWC (display, wks, dc_count, dc_points,
    view_index_return, wc_count_return, wc_points_return)

INPUT Display			*display;
INPUT PEXWorkstation		wks;
INPUT unsigned long		dc_count;
INPUT PEXDeviceCoord		*dc_points;
OUTPUT unsigned int		*view_index_return;
OUTPUT unsigned long		*wc_count_return;
OUTPUT PEXCoord			**wc_points_return;

{
    pexMapDCtoWCReq	*req;
    pexMapDCtoWCReply	rep;
    int			size;
    int			convertFP;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    size = dc_count * sizeof (PEXDeviceCoord);

    PEXGetFPReqExtra (MapDCtoWC, size, req, convertFP);
    req->wks = wks;
    req->numCoords = dc_count;

    COPY_AREA ((char *) dc_points, ((char *) &req[1]), size);

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
	*wc_count_return = 0;
	*wc_points_return = NULL;
        return (0);            /* return an error */
    }

    *view_index_return = rep.viewIndex;
    *wc_count_return = rep.numCoords;


    /*
     * Allocate a buffer for the replies to pass back to the client.
     */

    *wc_points_return = (PEXCoord *) PEXAllocBuf (
	(unsigned) (rep.length << 2));

    _XRead (display, (char *) *wc_points_return, (long) (rep.length << 2));


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (1);
}


Status
PEXMapWCToDC (display, wks, wc_count, wc_points,
    view_index, dc_count_return, dc_points_return)

INPUT Display			*display;
INPUT PEXWorkstation		wks;
INPUT unsigned long		wc_count;
INPUT PEXCoord			*wc_points;
INPUT unsigned int		view_index;
OUTPUT unsigned long		*dc_count_return;
OUTPUT PEXDeviceCoord		**dc_points_return;

{
    pexMapWCtoDCReq	*req;
    pexMapWCtoDCReply	rep;
    int			size;
    int			convertFP;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    size = wc_count * sizeof (PEXCoord);

    PEXGetFPReqExtra (MapWCtoDC, size, req, convertFP);
    req->wks = wks;
    req->index = view_index;
    req->numCoords = wc_count;

    COPY_AREA ((char *) wc_points, ((char *) &req[1]), size);

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
	*dc_count_return = 0;
	*dc_points_return = NULL;
        return (0);            /* return an error */
    }

    *dc_count_return = rep.numCoords;


    /*
     * Allocate a buffer for the replies to pass back to the client.
     */

    *dc_points_return = (PEXDeviceCoord *) PEXAllocBuf (
	(unsigned) (rep.length << 2));

    _XRead (display, (char *) *dc_points_return, (long) (rep.length << 2));


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (1);
}


void
PEXPostStructure (display, wks, structure, priority)

INPUT Display		*display;
INPUT PEXWorkstation	wks;
INPUT PEXStructure	structure;
INPUT double		priority;

{
    pexPostStructureReq	*req;
    int			convertFP;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetFPReq (PostStructure, req, convertFP);
    req->wks = wks;
    req->sid = structure;
    req->priority = priority;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXUnpostStructure (display, wks, structure)

INPUT Display		*display;
INPUT PEXWorkstation	wks;
INPUT PEXStructure	structure;

{
    pexUnpostStructureReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (UnpostStructure, req);
    req->wks = wks;
    req->sid = structure;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXUnpostAllStructures (display, wks)

INPUT Display		*display;
INPUT PEXWorkstation	wks;

{
    pexUnpostAllStructuresReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (UnpostAllStructures, req);
    req->id = wks;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXRedrawClipRegion (display, wks, numRectangles, deviceRectangles)

INPUT Display		*display;
INPUT PEXWorkstation	wks;
INPUT unsigned long	numRectangles;
INPUT PEXDeviceRect	*deviceRectangles;

{
    pexRedrawClipRegionReq	*req;
    int				size;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    size = numRectangles * sizeof (PEXDeviceRect);

    PEXGetReqExtra (RedrawClipRegion, size, req);
    req->wks = wks;
    req->numRects = numRectangles;

    COPY_AREA ((char *) deviceRectangles, ((char *) &req[1]), size);


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}
