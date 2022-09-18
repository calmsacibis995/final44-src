/* $XConsortium: pl_pc.c,v 1.8 92/08/26 13:06:18 mor Exp $ */

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

static void _PEXGeneratePCList();
static void _PEXGeneratePCAttr();


PEXPipelineContext
PEXCreatePipelineContext (display, valueMask, values)

INPUT Display		*display;
INPUT unsigned long	*valueMask;
INPUT PEXPCAttributes	*values;

{
    pexCreatePipelineContextReq		*req;
    PEXPipelineContext			pc;
    int					convertFP;


    /*
     * Get a pipeline context resource id from X.
     */

    pc = XAllocID (display);


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetFPReq (CreatePipelineContext, req, convertFP);
    req->pc = pc;
    req->itemMask0 = valueMask[0];
    req->itemMask1 = valueMask[1];
    req->itemMask2 = valueMask[2];

    if (valueMask[0] != 0 || valueMask[1] != 0 || valueMask[2] != 0)
    {
	_PEXGeneratePCList (display, (pexReq *) req, valueMask, values);
    }

    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (pc);
}


void
PEXFreePipelineContext (display, pc)

INPUT Display			*display;
INPUT PEXPipelineContext	pc;

{
    pexFreePipelineContextReq		*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (FreePipelineContext, req);
    req->id = pc;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXCopyPipelineContext (display, valueMask, srcPc, destPc)

INPUT Display			*display;
INPUT unsigned long		*valueMask;
INPUT PEXPipelineContext	srcPc;
INPUT PEXPipelineContext	destPc;

{
    pexCopyPipelineContextReq		*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (CopyPipelineContext, req);
    req->src = srcPc;
    req->dst = destPc;
    req->itemMask0 = valueMask[0];
    req->itemMask1 = valueMask[1];
    req->itemMask2 = valueMask[2];


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


PEXPCAttributes *
PEXGetPipelineContext (display, pc, valueMask)

INPUT Display			*display;
INPUT PEXPipelineContext	pc;
INPUT unsigned long		*valueMask;

{
    pexGetPipelineContextReq	*req;
    pexGetPipelineContextReply	rep;
    unsigned long		*pv;
    PEXPCAttributes		*ppca;
    int				convertFP;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetFPReq (GetPipelineContext, req, convertFP);
    req->pc = pc;
    req->itemMask0 = valueMask[0];
    req->itemMask1 = valueMask[1];
    req->itemMask2 = valueMask[2];

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
	UnlockDisplay (display);
	PEXSyncHandle (display);
	return (NULL);         /* return an error */
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

    ppca = (PEXPCAttributes *)
	PEXAllocBuf ((unsigned) (sizeof (PEXPCAttributes)));

    _PEXGeneratePCAttr (pv, valueMask, ppca);


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (ppca);
}


void
PEXChangePipelineContext (display, pc, valueMask, pcAttributes)

INPUT Display			*display;
INPUT PEXPipelineContext	pc;
INPUT unsigned long		*valueMask;
INPUT PEXPCAttributes		*pcAttributes;

{
    pexChangePipelineContextReq		*req;
    int					convertFP;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetFPReq (ChangePipelineContext, req, convertFP);
    req->pc = pc;
    req->itemMask0 = valueMask[0];
    req->itemMask1 = valueMask[1];
    req->itemMask2 = valueMask[2];

    _PEXGeneratePCList (display, (pexReq *) req, valueMask, pcAttributes);


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}



/*
 * Routine to write a packed list of pc attributes into the transport buf.
 */

static void
_PEXGeneratePCList (display, req, valueMask, values)

INPUT Display             *display;
INPUT pexReq              *req;
INPUT unsigned long       *valueMask;
INPUT PEXPCAttributes	  *values;

{
    long		*pv;
    long		*pvSend;
    unsigned long       f;
    int			length, n;
    int			sizeColor;
    long		size;
    Bool		bitSet;
    int 		pscType;
    INT16		*pint;


    /*
     * f is the maximum size we might need to store the PC list.  Just
     * use 2*sizeof(PEXPCAttributes) to account for padding between shorts.
     */

    f = 2 * sizeof (PEXPCAttributes);

    if (valueMask[1] &
	1L << (PEXPCModelClipVolume - PEXPCBFInteriorStyleIndex))
	f += values->model_clip_volume.count * sizeof (pexHalfSpace);

    if (valueMask[1] & 1L << (PEXPCLightState - PEXPCBFInteriorStyleIndex))
	f += PADDED_BYTES (values->light_state.count * sizeof (pexTableIndex));

    pv = pvSend = (long *) _XAllocScratch (display, (unsigned long) f);

    for (n = 0; n < (PEXPCMaxShift + 1); n++)
    {
	bitSet = valueMask[n >> 5] & (1L << (n & 0x1f));
	if (bitSet != 0)
        {
            switch (n)
	    {
	    /* note that there are 2 bytes of pad between 2 byte items */
            case PEXPCMarkerType:
		*pv = values->marker_type;
		pv++;
		break;
            case PEXPCMarkerScale:
		*((float *) pv) = values->marker_scale;
		pv++;
		break;
            case PEXPCMarkerColor:
		PackColorSpecifier (&(values->marker_color), pv, sizeColor);
		pv += NUMWORDS (sizeof (pexColorSpecifier) + sizeColor); 
		break;
            case PEXPCMarkerBundleIndex:
		*pv = values->marker_bundle_index;
		pv++;
		break;
            case PEXPCTextFont:
		*pv = values->text_font;
		pv++;
		break;
            case PEXPCTextPrecision:
		*pv = values->text_precision;
		pv++;
		break;
            case PEXPCCharExpansion:
		*((float *) pv) = values->char_expansion;
		pv++;
		break;
            case PEXPCCharSpacing:
		*((float *) pv) = values->char_spacing;
		pv++;
		break;
            case PEXPCTextColor:
		PackColorSpecifier (&(values->text_color), pv, sizeColor);
		pv += NUMWORDS (sizeof (pexColorSpecifier) + sizeColor); 
		break;
            case PEXPCCharHeight:
		*((float *) pv) = values->char_height;
		pv++;
		break;
            case PEXPCCharUpVector:
#ifdef WORD64
#else
		*((pexVector2D *) pv) = *(pexVector2D *)
		    &(values->char_up_vector);
#endif
		pv += LENOF (pexVector2D); 
		break;
            case PEXPCTextPath:
		*pv = values->text_path;
		pv++;
		break;
            case PEXPCTextAlignment:
#ifdef WORD64
#else
		*((pexTextAlignmentData *) pv) =
		    *(pexTextAlignmentData *) &(values->text_alignment);
#endif
		pv += LENOF (pexTextAlignmentData); 
		break;
            case PEXPCATextHeight:
		*((float *) pv) = values->atext_height;
		pv++;
		break;
            case PEXPCATextUpVector:
#ifdef WORD64
#else
		*((pexVector2D *) pv) = *(pexVector2D *)
		    &(values->atext_up_vector);
#endif
		pv += LENOF (pexVector2D); 
		break;
            case PEXPCATextPath:
		*pv = values->atext_path;
		pv++;
		break;
            case PEXPCATextAlignment:
#ifdef WORD64
#else
		*((pexTextAlignmentData *) pv) =
		    *(pexTextAlignmentData *) &(values->atext_alignment);
#endif
		pv += LENOF (pexTextAlignmentData); 
		break;
            case PEXPCATextStyle:
		*pv = values->atext_style;
		pv++;
		break;
            case PEXPCTextBundleIndex:
		*pv = values->text_bundle_index;
		pv++;
		break;
            case PEXPCLineType:
		*pv = values->line_type;
		pv++;
		break;
            case PEXPCLineWidth:
		*((float *) pv) = values->line_width;
		pv++;
		break;
            case PEXPCLineColor:
		PackColorSpecifier (&(values->line_color), pv, sizeColor);
		pv += NUMWORDS (sizeof (pexColorSpecifier) + sizeColor); 
		break;
            case PEXPCCurveApprox:
		*pv = values->curve_approx.method;
		pv++;
		*((float *) pv) = values->curve_approx.tolerance;
		pv++;
		break;
            case PEXPCPolylineInterp:
		*pv = values->polyline_interp;
		pv++;
		break;
            case PEXPCLineBundleIndex:
		*pv = values->line_bundle_index;
		pv++;
		break;
            case PEXPCInteriorStyle:
		*pv = values->interior_style;
		pv++;
		break;
            case PEXPCInteriorStyleIndex:
		*pv = values->interior_style_index;
		pv++;
		break;
            case PEXPCSurfaceColor:
		PackColorSpecifier (&(values->surface_color), pv, sizeColor);
		pv += NUMWORDS (sizeof (pexColorSpecifier) + sizeColor); 
		break;
            case PEXPCReflectionAttr:
		((pexReflectionAttr *) pv)->ambient = 
		    values->reflection_attr.ambient;
		((pexReflectionAttr *) pv)->diffuse = 
		    values->reflection_attr.diffuse;
		((pexReflectionAttr *) pv)->specular = 
		    values->reflection_attr.specular;
		((pexReflectionAttr *) pv)->specularConc = 
		    values->reflection_attr.specular_conc;
		((pexReflectionAttr *) pv)->transmission = 
		    values->reflection_attr.transmission;
		PackColorSpecifier (&(values->reflection_attr.specular_color), 
		    &(((pexReflectionAttr *) pv)->specularColor), 
		    sizeColor);
		pv += NUMWORDS (sizeof (pexReflectionAttr) + sizeColor); 
		break;
            case PEXPCReflectionModel:
		*pv = values->reflection_model;
		pv++;
		break;
            case PEXPCSurfaceInterp:
		*pv = values->surface_interp;
		pv++;
		break;
            case PEXPCBFInteriorStyle:
		*pv = values->bf_interior_style;
		pv++;
		break;
            case PEXPCBFInteriorStyleIndex:
		*pv = values->bf_interior_style_index;
		pv++;
		break;
            case PEXPCBFSurfaceColor:
		PackColorSpecifier (&(values->bf_surface_color),
		    pv, sizeColor);
		pv += NUMWORDS (sizeof (pexColorSpecifier) + sizeColor); 
		break;
            case PEXPCBFReflectionAttr:
		((pexReflectionAttr *) pv)->ambient = 
		    values->bf_reflection_attr.ambient;
		((pexReflectionAttr *) pv)->diffuse = 
		    values->bf_reflection_attr.diffuse;
		((pexReflectionAttr *) pv)->specular = 
		    values->bf_reflection_attr.specular;
		((pexReflectionAttr *) pv)->specularConc = 
		    values->bf_reflection_attr.specular_conc;
		((pexReflectionAttr *) pv)->transmission = 
		    values->bf_reflection_attr.transmission;
		PackColorSpecifier (
		    &(values->bf_reflection_attr.specular_color), 
		    &(((pexReflectionAttr *) pv)->specularColor), 
		    sizeColor);
		pv += NUMWORDS (sizeof (pexReflectionAttr) + sizeColor); 
		break;
            case PEXPCBFReflectionModel:
		*pv = values->bf_reflection_model;
		pv++;
		break;
            case PEXPCBFSurfaceInterp:
		*pv = values->bf_surface_interp;
		pv++;
		break;
            case PEXPCSurfaceApprox:
		*pv = values->surface_approx.method;
		pv++;
		*((float *) pv) = values->surface_approx.u_tolerance;
		pv++;
		*((float *) pv) = values->surface_approx.v_tolerance;
		pv++;
		break;
            case PEXPCCullingMode:
		*pv = values->culling_mode;
		pv++;
		break;
            case PEXPCDistinguishFlag:
		*pv = values->distinguish;
		pv++;
		break;
            case PEXPCPatternSize:
#ifdef WORD64
#else
		*((pexCoord2D *) pv) = *(pexCoord2D *) &(values->pattern_size);
#endif
		pv += LENOF (pexCoord2D);
		break;
            case PEXPCPatternRefPoint:
#ifdef WORD64
#else
		*((pexCoord3D *) pv) =
		    *(pexCoord3D *) &(values->pattern_ref_point);
#endif
		pv += LENOF (pexCoord3D);
		break;
            case PEXPCPatternRefVec1:
#ifdef WORD64
#else
		*((pexVector3D *) pv) =
		    *(pexVector3D *) &(values->pattern_ref_vec1);
#endif
		pv += LENOF (pexVector3D);
		break;
            case PEXPCPatternRefVec2:
#ifdef WORD64
#else
		*((pexVector3D *) pv) =
		    *(pexVector3D *) &(values->pattern_ref_vec2);
#endif
		pv += LENOF (pexVector3D);
		break;
            case PEXPCInteriorBundleIndex:
		*pv = values->interior_bundle_index;
		pv++;
		break;
            case PEXPCSurfaceEdgeFlag:
		*pv = values->surface_edges;
		pv++;
		break;
            case PEXPCSurfaceEdgeType:
		*pv = values->surface_edge_type;
		pv++;
		break;
            case PEXPCSurfaceEdgeWidth:
		*((float *) pv) = values->surface_edge_width;
		pv++;
		break;
            case PEXPCSurfaceEdgeColor:
		PackColorSpecifier (&(values->surface_edge_color), pv, 
		    sizeColor);
		pv += NUMWORDS (sizeof (pexColorSpecifier) + sizeColor); 
		break;
            case PEXPCEdgeBundleIndex:
		*pv = values->edge_bundle_index;
		pv++;
		break;
            case PEXPCLocalTransform:
		COPY_AREA ((char *) values->local_transform,
		    (char *) pv, sizeof (pexMatrix));
		pv += LENOF (pexMatrix);
		break;
            case PEXPCGlobalTransform:
		COPY_AREA ((char *) values->global_transform,
		    (char *) pv, sizeof (pexMatrix));
		pv += LENOF (pexMatrix);
		break;
            case PEXPCModelClip:
		*pv = values->model_clip;
		pv++;
		break;
            case PEXPCModelClipVolume:
		size = values->model_clip_volume.count;
		*((long *) pv) = size;
		pv++;
		size *= sizeof (pexHalfSpace);
		COPY_AREA ((char *) values->model_clip_volume.half_spaces,
		    (char *) pv, size);
		pv += NUMWORDS (size);
		break;
            case PEXPCViewIndex:
		*pv = values->view_index;
		pv++;
		break;
            case PEXPCLightState:
		size = values->light_state.count;
		*((long *) pv) = size;
		pv++;
		size *= sizeof (pexTableIndex);
		COPY_AREA ((char *) values->light_state.indices,
		    (char *) pv, size);
		pv += NUMWORDS (size);
		break;
            case PEXPCDepthCueIndex:
		*pv = values->depth_cue_index;
		pv++;
		break;
            case PEXPCPickID:
		*((CARD32 *) pv) = values->pick_id;
		pv++;
		break;
            case PEXPCHLHSRIdentifier:
		*((CARD32 *) pv) = values->hlhsr_id;
		pv++;
		break;
            case PEXPCNameSet:
		*((pexNameSet *) pv) = values->name_set;
		pv += LENOF (pexNameSet);
		break;
            case PEXPCASFValues:
		*((unsigned long *) pv) = values->asf_enables;
		pv++;
		*((unsigned long *) pv) = values->asf_values;
		pv++;
		break;
	    case PEXPCColorApproxIndex:
		*pv = values->color_approx_index;
		pv++;
		break;
	    case PEXPCRenderingColorModel:
		*pv = values->rendering_color_model;
		pv++;
		break;
	    case PEXPCParaSurfCharacteristics:
		pscType = values->para_surf_char.type;
		pint = (INT16 *) pv;

		if (pscType == PEXPSCIsoCurves)
		{
		    size = sizeof (PEXPSCIsoparametricCurves);
		    *(pint++) = PEXPSCIsoCurves;
		    *(pint++) = size;
		    pv = (long *) pint;

		    COPY_AREA (&(values->para_surf_char.psc.iso_curves),
		       (char *) pv, sizeof (PEXPSCIsoparametricCurves));
		    pv = (long *) ((char *) pv +
			sizeof (PEXPSCIsoparametricCurves));
		}
		else if (pscType == PEXPSCMCLevelCurves ||
		    pscType == PEXPSCWCLevelCurves)
		{
		    int param_size = sizeof (float) *
			 values->para_surf_char.psc.level_curves.count;
		    size = sizeof (pexPSC_LevelCurves) + param_size;

		    *(pint++) = pscType;
		    *(pint++) = size;
		    pv = (long *) pint;

		    COPY_AREA (&(values->para_surf_char.psc.level_curves),
		       (char *) pv, sizeof (pexPSC_LevelCurves));
		    pv = (long *) ((char *) pv + sizeof (pexPSC_LevelCurves));
		    COPY_AREA ((char *)
			values->para_surf_char.psc.level_curves.parameters,
			(char *) pv, param_size);
		    pv = (long *) ((char *) pv + param_size);
		}
		break;
	    }
	}
    }

    length = pv - pvSend;
    req->length += length;

    Data (display, (char *) pvSend, (length << 2));
}


/*
 * Routine to fill in a PEXPCAttributes structure from the PC attributes
 * part of a Get PC reply.
 */

static void
_PEXGeneratePCAttr (pv, valueMask, ppca)

INPUT unsigned long			*pv;
INPUT unsigned long			valueMask[3];
OUTPUT PEXPCAttributes			*ppca;

{
    Bool			bitSet;
    int				sizeColor;
    int				size, n, pscType;
    INT16			*pint;


    /*
     * PEXFreePCAttributes will check for NULL before freeing.
     */

    ppca->model_clip_volume.count = 0;
    ppca->model_clip_volume.half_spaces = NULL;
    ppca->light_state.count = 0;
    ppca->light_state.indices = NULL;
    ppca->para_surf_char.type = 0;


    /*
     * Fill in the PC attributes.
     */

    for (n = 0; n < (PEXPCMaxShift + 1); n++)
    {
	bitSet = valueMask[n >> 5] & (1L << (n & 0x1f));

	if (bitSet != 0)
        {
            switch (n)
	    {
	    /* note:  2 bytes of pad between 2 byte items */
            case PEXPCMarkerType:
		ppca->marker_type = *pv;
		pv++;
		break;
            case PEXPCMarkerScale:
		ppca->marker_scale = *((float *) pv);
		pv++;
		break;
            case PEXPCMarkerColor:
		PackColorSpecifier (pv, &(ppca->marker_color), sizeColor);
		pv += NUMWORDS (sizeof (pexColorSpecifier) + sizeColor); 
		break;
            case PEXPCMarkerBundleIndex:
		ppca->marker_bundle_index = *pv;
		pv++;
		break;
            case PEXPCTextFont:
		ppca->text_font = *pv;
		pv++;
		break;
            case PEXPCTextPrecision:
		ppca->text_precision = *pv;
		pv++;
		break;
            case PEXPCCharExpansion:
	  	ppca->char_expansion = *((float *) pv);
		pv++;
		break;
            case PEXPCCharSpacing:
		ppca->char_spacing = *((float *) pv);
		pv++;
		break;
            case PEXPCTextColor:
		PackColorSpecifier (pv, &(ppca->text_color), sizeColor);
		pv += NUMWORDS (sizeof (pexColorSpecifier) + sizeColor); 
		break;
            case PEXPCCharHeight:
		ppca->char_height = *((float *) pv);
		pv++;
		break;
            case PEXPCCharUpVector:
#ifdef WORD64
#else
		ppca->char_up_vector = *((PEXVector2D *) pv);
#endif
		pv += LENOF (pexVector2D); 
		break;
            case PEXPCTextPath:
		ppca->text_path = *pv;
		pv++;
		break;
            case PEXPCTextAlignment:
#ifdef WORD64
#else
		ppca->text_alignment = *((PEXTextAlignment *)pv);
#endif
		pv += LENOF (pexTextAlignmentData);
		break;
            case PEXPCATextHeight:
		ppca->atext_height = *((float *) pv);
		pv++;
		break;
            case PEXPCATextUpVector:
#ifdef WORD64
#else
		ppca->atext_up_vector = *((PEXVector2D *) pv);
#endif
		pv += LENOF (pexVector2D); 
		break;
            case PEXPCATextPath:
		ppca->atext_path = *pv;
		pv++;
		break;
            case PEXPCATextAlignment:
#ifdef WORD64
#else
		ppca->atext_alignment = *((PEXTextAlignment *) pv);
#endif
		pv += LENOF (pexTextAlignmentData);
		break;
            case PEXPCATextStyle:
		ppca->atext_style = *pv;
		pv++;
		break;
            case PEXPCTextBundleIndex:
		ppca->text_bundle_index = *pv;
		pv++;
		break;
            case PEXPCLineType:
		ppca->line_type = *pv;
		pv++;
		break;
            case PEXPCLineWidth:
		ppca->line_width = *((float *) pv);
		pv++;
		break;
            case PEXPCLineColor:
		PackColorSpecifier (pv, &(ppca->line_color), sizeColor);
		pv += NUMWORDS (sizeof (pexColorSpecifier) + sizeColor); 
		break;
            case PEXPCCurveApprox:
		ppca->curve_approx.method = *pv;
		pv++;
		ppca->curve_approx.tolerance = *((float *) pv);
		pv++;
		break;
            case PEXPCPolylineInterp:
		ppca->polyline_interp = *pv;
		pv++;
		break;
            case PEXPCLineBundleIndex:
		ppca->line_bundle_index = *pv;
		pv++;
		break;
            case PEXPCInteriorStyle:
		ppca->interior_style = *pv;
		pv++;
		break;
            case PEXPCInteriorStyleIndex:
		ppca->interior_style_index = *pv;
		pv++;
		break;
            case PEXPCSurfaceColor:
		PackColorSpecifier (pv, &(ppca->surface_color), sizeColor);
		pv += NUMWORDS (sizeof (pexColorSpecifier) + sizeColor); 
		break;
            case PEXPCReflectionAttr:
		ppca->reflection_attr.ambient = 
		    ((pexReflectionAttr *) pv)->ambient;
		ppca->reflection_attr.diffuse = 
		    ((pexReflectionAttr *) pv)->diffuse;
		ppca->reflection_attr.specular = 
		    ((pexReflectionAttr *) pv)->specular;
		ppca->reflection_attr.specular_conc = 
		    ((pexReflectionAttr *) pv)->specularConc;
		ppca->reflection_attr.transmission = 
		    ((pexReflectionAttr *) pv)->transmission;
		PackColorSpecifier ( 
		    &(((pexReflectionAttr *) pv)->specularColor), 
		    &(ppca->reflection_attr.specular_color), sizeColor);
		pv += NUMWORDS (sizeof (pexReflectionAttr) + sizeColor); 
		break;
            case PEXPCReflectionModel:
		ppca->reflection_model = *pv;
		pv++;
		break;
            case PEXPCSurfaceInterp:
		ppca->surface_interp = *pv;
		pv++;
		break;
            case PEXPCBFInteriorStyle:
		ppca->bf_interior_style = *pv;
		pv++;
		break;
            case PEXPCBFInteriorStyleIndex:
		ppca->bf_interior_style_index = *pv;
		pv++;
		break;
            case PEXPCBFSurfaceColor:
		PackColorSpecifier (pv, &(ppca->bf_surface_color), sizeColor);
		pv += NUMWORDS (sizeof (pexColorSpecifier) + sizeColor); 
		break;
            case PEXPCBFReflectionAttr:
		ppca->bf_reflection_attr.ambient = 
		    ((pexReflectionAttr *) pv)->ambient;
		ppca->bf_reflection_attr.diffuse = 
		    ((pexReflectionAttr *) pv)->diffuse;
		ppca->bf_reflection_attr.specular = 
		    ((pexReflectionAttr *) pv)->specular;
		ppca->bf_reflection_attr.specular_conc = 
		    ((pexReflectionAttr *) pv)->specularConc;
		ppca->bf_reflection_attr.transmission = 
		    ((pexReflectionAttr *) pv)->transmission;
		PackColorSpecifier ( 
		    &(((pexReflectionAttr *) pv)->specularColor), 
		    &(ppca->bf_reflection_attr.specular_color), sizeColor);
		pv += NUMWORDS (sizeof (pexReflectionAttr) + sizeColor); 
		break;
            case PEXPCBFReflectionModel:
		ppca->bf_reflection_model = *pv;
		pv++;
		break;
            case PEXPCBFSurfaceInterp:
		ppca->bf_surface_interp = *pv;
		pv++;
		break;
            case PEXPCSurfaceApprox:
		ppca->surface_approx.method = *pv;
		pv++;
		ppca->surface_approx.u_tolerance = *((float *) pv);
		pv++;
		ppca->surface_approx.v_tolerance = *((float *) pv);
		pv++;
		break;
            case PEXPCCullingMode:
		ppca->culling_mode = *pv;
		pv++;
		break;
            case PEXPCDistinguishFlag:
		ppca->distinguish = *pv;
		pv++;
		break;
            case PEXPCPatternSize:
#ifdef WORD64
#else
		ppca->pattern_size = *((PEXCoord2D *) pv);
#endif
		pv += LENOF (pexCoord2D);
		break;
            case PEXPCPatternRefPoint:
#ifdef WORD64
#else
		ppca->pattern_ref_point = *((PEXCoord *) pv);
#endif
		pv += LENOF (pexCoord3D);
		break;
            case PEXPCPatternRefVec1:
#ifdef WORD64
#else
		ppca->pattern_ref_vec1 = *((PEXVector *) pv);
#endif
		pv += LENOF (pexVector3D); 
		break;
            case PEXPCPatternRefVec2:
#ifdef WORD64
#else
		ppca->pattern_ref_vec2 = *((PEXVector *) pv);
#endif
		pv += LENOF (pexVector3D); 
		break;
            case PEXPCInteriorBundleIndex:
		ppca->interior_bundle_index = *pv;
		pv++;
		break;
            case PEXPCSurfaceEdgeFlag:
		ppca->surface_edges = *pv;
		pv++;
		break;
            case PEXPCSurfaceEdgeType:
		ppca->surface_edge_type = *pv;
		pv++;
		break;
            case PEXPCSurfaceEdgeWidth:
		ppca->surface_edge_width = *((float *) pv);
		pv++;
		break;
            case PEXPCSurfaceEdgeColor:
		PackColorSpecifier (pv, &(ppca->surface_edge_color),
		    sizeColor);
		pv += NUMWORDS (sizeof (pexColorSpecifier) + sizeColor); 
		break;
            case PEXPCEdgeBundleIndex:
		ppca->edge_bundle_index = *pv;
		pv++;
		break;
            case PEXPCLocalTransform:
		COPY_AREA ((char *) pv, (char *) ppca->local_transform,
		    sizeof (PEXMatrix));
		pv += LENOF (pexMatrix);
		break;
            case PEXPCGlobalTransform:
		COPY_AREA ((char *) pv, (char *) ppca->global_transform,
		    sizeof (PEXMatrix));
		pv += LENOF (pexMatrix);
		break;
            case PEXPCModelClip:
		ppca->model_clip = *pv;
		pv++;
		break;
            case PEXPCModelClipVolume:
		size = *pv;
		pv++;
		ppca->model_clip_volume.count = size;
		size *= sizeof (PEXHalfSpace);
		ppca->model_clip_volume.half_spaces =
		    (PEXHalfSpace *) PEXAllocBuf ((unsigned) size);
		COPY_AREA ((char *)pv,
		    (char *) (ppca->model_clip_volume.half_spaces), size);
		pv += NUMWORDS (size);
		break;
            case PEXPCViewIndex:
		ppca->view_index = *pv;
		pv++;
		break;
            case PEXPCLightState:
		size = *pv;
		pv++;
		ppca->light_state.count = size;
		size *= sizeof (PEXTableIndex);
		ppca->light_state.indices =
		    (PEXTableIndex *) PEXAllocBuf ((unsigned) size);
		COPY_AREA ((char *) pv,
		    (char *) (ppca->light_state.indices), size);
		pv += NUMWORDS (size);
		break;
            case PEXPCDepthCueIndex:
		ppca->depth_cue_index = *pv;
		pv++;
		break;
            case PEXPCPickID:
		ppca->pick_id = *((INT32 *) pv);
		pv++;
		break;
            case PEXPCHLHSRIdentifier:
		ppca->hlhsr_id = *((CARD32 *) pv);
		pv++;
		break;
            case PEXPCNameSet:
		ppca->name_set = *((PEXNameSet *) pv);
		pv += LENOF (pexNameSet);
		break;
            case PEXPCASFValues:
		ppca->asf_enables = *((CARD32 *) pv);
		pv++;
		ppca->asf_values = *((CARD32 *) pv);
		pv++;
		break;
	    case PEXPCColorApproxIndex:
		ppca->color_approx_index = *pv;
		pv++;
		break;
	    case PEXPCRenderingColorModel:
		ppca->rendering_color_model = *pv;
		pv++;
		break;
	    case PEXPCParaSurfCharacteristics:
		pint = (INT16 *) pv;
		ppca->para_surf_char.type = pscType = *(pint++);
		pv++;
		if (pscType == PEXPSCIsoCurves)
		{
		    COPY_AREA ((char *) pv,
			(char *) &(ppca->para_surf_char.psc.iso_curves),
			sizeof (PEXPSCIsoparametricCurves));
		    pv = (unsigned long *) ((char *) pv +
			sizeof (PEXPSCIsoparametricCurves));
		}
		else if (pscType == PEXPSCMCLevelCurves ||
		    pscType == PEXPSCWCLevelCurves)
		{
		    int param_size = *pint - sizeof (pexPSC_LevelCurves);

		    COPY_AREA ((char *) pv,
		        (char *) &(ppca->para_surf_char.psc.level_curves),
		        sizeof (pexPSC_LevelCurves));
		    pv = (unsigned long *) ((char *) pv +
			sizeof (pexPSC_LevelCurves));
		    ppca->para_surf_char.psc.level_curves.parameters = 
		        (float *) PEXAllocBuf ((unsigned) param_size);
		    COPY_AREA ((char *) pv, (char *)
			(ppca->para_surf_char.psc.level_curves.parameters),
		        param_size);
		    pv = (unsigned long *) ((char *) pv + *pint);
		}
		break;
	    }
	}
    }
}
