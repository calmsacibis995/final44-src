/* $XConsortium: pl_oc_attr.c,v 1.7 92/08/26 13:06:11 mor Exp $ */

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
#include "pl_oc_util.h"

extern void _PEXCopyPaddedBytesToOC();


void
PEXSetMarkerType (display, resource_id, req_type, type)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		type;

{
    pexEnumTypeIndex	t = type;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCMarkerType,
	sizeof (pexEnumTypeIndex), &t);
}


void
PEXSetMarkerScale (display, resource_id, req_type, scale)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT double		scale;

{
    float		s = scale;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCMarkerScale,
	sizeof (float), &s);
}


void
PEXSetMarkerColorIndex (display, resource_id, req_type, index)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned int	index;

{
    pexTableIndex	i = index;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCMarkerColorIndex,
	sizeof (pexTableIndex), &i);
}


void
PEXSetMarkerColor (display, resource_id, req_type, colorType, color)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		colorType;
INPUT PEXColor		*color;

{
    PEXColorSpecifier	pcs;

    InitializeColorSpecifier (pcs, color, colorType);

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCMarkerColor,
	sizeof (PEXColorSpecifier) - AdjustSizeFromType (colorType), &pcs);
}


void
PEXSetMarkerBundleIndex (display, resource_id, req_type, index)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned int	index;

{
    pexTableIndex	i = index;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCMarkerBundleIndex,
	sizeof (pexTableIndex), &i);
}


void
PEXSetTextFontIndex (display, resource_id, req_type, index)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned int	index;

{
    pexTableIndex	i = index;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCTextFontIndex,
	sizeof (pexTableIndex), &i);
}


void
PEXSetTextPrecision (display, resource_id, req_type, precision)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		precision;

{
    CARD16		p = precision;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCTextPrecision,
	sizeof (CARD16), &p);
}


void
PEXSetCharExpansion (display, resource_id, req_type, expansion)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT double		expansion;

{
    float		e = expansion;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCCharExpansion,
	sizeof (float), &e);
}


void
PEXSetCharSpacing (display, resource_id, req_type, spacing)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT double		spacing;

{
    float		s = spacing;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCCharSpacing,
	sizeof (float), &s);
}


void
PEXSetTextColorIndex (display, resource_id, req_type, index)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned int	index;

{
    pexTableIndex	i = index;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCTextColorIndex,
	sizeof (pexTableIndex), &i);
}


void
PEXSetTextColor (display, resource_id, req_type, colorType, color)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		colorType;
INPUT PEXColor		*color;

{
    PEXColorSpecifier	pcs;

    InitializeColorSpecifier (pcs, color, colorType);

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCTextColor,
	sizeof (PEXColorSpecifier) - AdjustSizeFromType (colorType), &pcs);
}


void
PEXSetCharHeight (display, resource_id, req_type, height)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT double		height;

{
    float		h = height;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCCharHeight,
	sizeof (float), &h);
}


void
PEXSetCharUpVector (display, resource_id, req_type, vector)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT PEXVector2D	*vector;

{
    PEXAddSimpleOC (display, resource_id, req_type, PEXOCCharUpVector,
	sizeof (PEXVector2D), vector);
}


void
PEXSetTextPath (display, resource_id, req_type, path)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		path;

{
    CARD16		p = path;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCTextPath,
	sizeof (CARD16), &p);
}


void
PEXSetTextAlignment (display, resource_id, req_type, halignment, valignment)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		halignment;
INPUT int		valignment;

{
    pexTextAlignmentData	a;

    a.vertical = valignment;
    a.horizontal = halignment;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCTextAlignment,
	sizeof (pexTextAlignmentData), &a);
}


void
PEXSetATextHeight (display, resource_id, req_type, height)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT double		height;

{
    float		h = height;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCATextHeight,
	sizeof (float), &h);
}


void
PEXSetATextUpVector (display, resource_id, req_type, vector)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT PEXVector2D	*vector;

{
    PEXAddSimpleOC (display, resource_id, req_type, PEXOCATextUpVector,
	sizeof (PEXVector2D), vector);
}


void
PEXSetATextPath (display, resource_id, req_type, path)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		path;

{
    CARD16		p = path;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCATextPath,
	sizeof (CARD16), &p);
}


void
PEXSetATextAlignment (display, resource_id, req_type, halignment, valignment)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		halignment;
INPUT int		valignment;

{
    pexTextAlignmentData	a;

    a.vertical = valignment;
    a.horizontal = halignment;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCATextAlignment,
	sizeof (pexTextAlignmentData), &a);
}


void
PEXSetATextStyle (display, resource_id, req_type, style)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		style;

{
    pexEnumTypeIndex	s = style;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCATextStyle,
	sizeof (pexEnumTypeIndex), &s);
}


void
PEXSetTextBundleIndex (display, resource_id, req_type, index)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned int	index;

{
    pexTableIndex	i = index;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCTextBundleIndex,
	sizeof (pexTableIndex), &i);
}


void
PEXSetLineType (display, resource_id, req_type, type)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		type;

{
    pexEnumTypeIndex	t = type;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCLineType,
	sizeof (pexEnumTypeIndex), &t);
}


void
PEXSetLineWidth (display, resource_id, req_type, width)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT double		width;

{
    float		w = width;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCLineWidth,
	sizeof (float), &w);
}


void
PEXSetLineColorIndex (display, resource_id, req_type, index)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned int	index;

{
    pexTableIndex	i = index;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCLineColorIndex,
	sizeof (pexTableIndex), &i);
}


void
PEXSetLineColor (display, resource_id, req_type, colorType, color)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		colorType;
INPUT PEXColor		*color;

{
    PEXColorSpecifier	pcs;

    InitializeColorSpecifier (pcs, color, colorType);

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCLineColor,
	sizeof (PEXColorSpecifier) - AdjustSizeFromType (colorType), &pcs);
}


void
PEXSetCurveApprox (display, resource_id, req_type, approxMethod, tolerance)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		approxMethod;
INPUT double		tolerance;

{
    pexCurveApprox	c;

    c.approxMethod = approxMethod;
    c.tolerance = tolerance;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCCurveApprox,
	sizeof (pexCurveApprox), &c);
}


void
PEXSetPolylineInterpMethod (display, resource_id, req_type, method)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		method;

{
    CARD16		m = method;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCPolylineInterpMethod,
	sizeof (CARD16), &m);
}


void
PEXSetLineBundleIndex (display, resource_id, req_type, index)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned int	index;

{
    pexTableIndex	i = index;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCLineBundleIndex,
	sizeof (pexTableIndex), &i);
}


void
PEXSetInteriorStyle (display, resource_id, req_type, style)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		style;

{
    pexEnumTypeIndex	s = style;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCInteriorStyle,
	sizeof (pexEnumTypeIndex), &s);
}


void
PEXSetInteriorStyleIndex (display, resource_id, req_type, index)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		index;

{
    pexTableIndex	i = index;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCInteriorStyleIndex,
	sizeof (pexTableIndex), &i);
}


void
PEXSetSurfaceColorIndex (display, resource_id, req_type, index)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned int	index;

{
    pexTableIndex	i = index;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCSurfaceColorIndex,
	sizeof (pexTableIndex), &i);
}


void
PEXSetSurfaceColor (display, resource_id, req_type, colorType, color)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		colorType;
INPUT PEXColor		*color;

{
    PEXColorSpecifier	pcs;

    InitializeColorSpecifier (pcs, color, colorType);

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCSurfaceColor,
	sizeof (PEXColorSpecifier) - AdjustSizeFromType (colorType), &pcs);
}


void
PEXSetReflectionAttributes (display, resource_id, req_type, reflectionAttr)

INPUT Display			*display;
INPUT XID			resource_id;
INPUT PEXOCRequestType		req_type;
INPUT PEXReflectionAttributes	*reflectionAttr;

{
    PEXAddSimpleOC (display, resource_id, req_type, PEXOCReflectionAttributes,
	sizeof (PEXReflectionAttributes) -
	AdjustSizeFromType (reflectionAttr->specular_color.type),
    	reflectionAttr);
}


void
PEXSetReflectionModel (display, resource_id, req_type, model)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		model;

{
    pexEnumTypeIndex	m = model;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCReflectionModel,
	sizeof (pexEnumTypeIndex), &m);
}


void
PEXSetSurfaceInterpMethod (display, resource_id, req_type, method)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		method;

{
    pexEnumTypeIndex	m = method;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCSurfaceInterpMethod,
	sizeof (pexEnumTypeIndex), &m);
}


void
PEXSetBFInteriorStyle (display, resource_id, req_type, style)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		style;

{
    pexEnumTypeIndex	s = style;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCBFInteriorStyle,
	sizeof (pexEnumTypeIndex), &s);
}


void
PEXSetBFInteriorStyleIndex (display, resource_id, req_type, index)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		index;

{
    pexTableIndex	i = index;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCBFInteriorStyleIndex,
	sizeof (pexTableIndex), &i);
}


void
PEXSetBFSurfaceColorIndex (display, resource_id, req_type, index)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned int	index;

{
    pexTableIndex	i = index;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCBFSurfaceColorIndex,
	sizeof (pexTableIndex), &i);
}


void
PEXSetBFSurfaceColor (display, resource_id, req_type, colorType, color)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		colorType;
INPUT PEXColor		*color;

{
    PEXColorSpecifier	pcs;

    InitializeColorSpecifier (pcs, color, colorType);

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCBFSurfaceColor,
        sizeof (PEXColorSpecifier) - AdjustSizeFromType (colorType), &pcs);
}


void
PEXSetBFReflectionAttributes (display, resource_id, req_type, reflectionAttr)

INPUT Display			*display;
INPUT XID			resource_id;
INPUT PEXOCRequestType		req_type;
INPUT PEXReflectionAttributes	*reflectionAttr;

{
    PEXAddSimpleOC (display, resource_id, req_type,
	PEXOCBFReflectionAttributes, sizeof (PEXReflectionAttributes) -
 	AdjustSizeFromType (reflectionAttr->specular_color.type),
     	reflectionAttr);
}


void
PEXSetBFReflectionModel (display, resource_id, req_type, model)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		model;

{
    pexEnumTypeIndex	m = model;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCBFReflectionModel,
	sizeof (pexEnumTypeIndex), &m);
}


void
PEXSetBFSurfaceInterpMethod (display, resource_id, req_type, method)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		method;

{
    pexEnumTypeIndex	m = method;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCBFSurfaceInterpMethod,
	sizeof (pexEnumTypeIndex), &m);
}


void
PEXSetSurfaceApprox (display, resource_id, req_type,
    approxMethod, uTolerance, vTolerance)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		approxMethod;
INPUT double		uTolerance;
INPUT double		vTolerance;

{
    pexSurfaceApprox	a;

    a.approxMethod = approxMethod;
    a.uTolerance = uTolerance;
    a.vTolerance = vTolerance;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCSurfaceApprox,
	sizeof (pexSurfaceApprox), &a);
}


void
PEXSetFacetCullingMode (display, resource_id, req_type, mode)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		mode;

{
    pexCullMode		m = mode;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCFacetCullingMode,
	sizeof (pexCullMode), &m);
}


void
PEXSetFacetDistinguishFlag (display, resource_id, req_type, flag)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		flag;

{
    pexSwitch		f = flag;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCFacetDistinguishFlag,
	sizeof (pexSwitch), &f);
}


void
PEXSetPatternSize (display, resource_id, req_type, width, height)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT double		width;
INPUT double		height;

{
    pexVector2D		vec;

    vec.x = width;
    vec.y = height;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCPatternSize,
	sizeof (pexVector2D), &vec);
}


void
PEXSetPatternAttributes2D (display, resource_id, req_type, ref_point)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT PEXCoord2D	*ref_point;

{
    PEXAddSimpleOC (display, resource_id, req_type, PEXOCPatternAttributes2D,
	sizeof (PEXCoord2D), ref_point);
}


void
PEXSetPatternAttributes (display, resource_id, req_type, refPt, vec1, vec2)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT PEXCoord  	*refPt;
INPUT PEXVector 	*vec1;
INPUT PEXVector 	*vec2;

{
    pexCoord3D		attr[3];

    attr[0].x = refPt->x;
    attr[0].y = refPt->y;
    attr[0].z = refPt->z;
    attr[1].x = vec1->x;
    attr[1].y = vec1->y;
    attr[1].z = vec1->z;
    attr[2].x = vec2->x;
    attr[2].y = vec2->y;
    attr[2].z = vec2->z;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCPatternAttributes,
	sizeof (attr), attr);
}


void
PEXSetInteriorBundleIndex (display, resource_id, req_type, index)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned int	index;

{
    pexTableIndex	i = index;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCInteriorBundleIndex,
	sizeof (pexTableIndex), &i);
}


void
PEXSetSurfaceEdgeFlag (display, resource_id, req_type, flag)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		flag;

{
    pexSwitch		f = flag;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCSurfaceEdgeFlag,
	sizeof (pexSwitch), &f);
}


void
PEXSetSurfaceEdgeType (display, resource_id, req_type, type)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		type;

{
    pexEnumTypeIndex	t = type;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCSurfaceEdgeType,
	sizeof (pexEnumTypeIndex), &t);
}


void
PEXSetSurfaceEdgeWidth (display, resource_id, req_type, width)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT double		width;

{
    float		w = width;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCSurfaceEdgeWidth,
	sizeof (float), &w);
}


void
PEXSetSurfaceEdgeColorIndex (display, resource_id, req_type, index)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned int	index;

{
    pexTableIndex	i = index;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCSurfaceEdgeColorIndex,
	sizeof (pexTableIndex), &i);
}


void
PEXSetSurfaceEdgeColor (display, resource_id, req_type, colorType, color)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		colorType;
INPUT PEXColor		*color;

{
    PEXColorSpecifier	pcs;

    InitializeColorSpecifier (pcs, color, colorType);

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCSurfaceEdgeColor,
	sizeof (PEXColorSpecifier) - AdjustSizeFromType (colorType), &pcs);
}


void
PEXSetEdgeBundleIndex (display, resource_id, req_type, index)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned int	index;

{
    pexTableIndex	i = index;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCEdgeBundleIndex,
	sizeof (pexTableIndex), &i);
}


void
PEXSetIndividualASF (display, resource_id, req_type, attribute, value)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned long	attribute;
INPUT int		value;

{
    PEXASFData		asf;

    asf.attribute = attribute;
    asf.value = value;
    
    PEXAddSimpleOC (display, resource_id, req_type, PEXOCIndividualASF,
        sizeof (PEXASFData), &asf);
}


void
PEXSetLocalTransform (display, resource_id, req_type, compType, transform)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		compType;
INPUT PEXMatrix		transform;

{
    pexLocalTransform	*pReq;

    PEXInitOC (display, resource_id, req_type, PEXOCLocalTransform, 
	LENOF (pexLocalTransform), 0, pexLocalTransform, pReq);

    if (pReq == NULL) return;

    pReq->compType = compType;
    COPY_AREA (transform, pReq->matrix, sizeof (pexMatrix));

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXSetLocalTransform2D (display, resource_id, req_type, compType, transform)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		compType;
INPUT PEXMatrix3x3	transform;

{
    pexLocalTransform2D	*pReq;

    PEXInitOC (display, resource_id, req_type, PEXOCLocalTransform2D, 
	LENOF (pexLocalTransform2D), 0, pexLocalTransform2D, pReq);

    if (pReq == NULL) return;

    pReq->compType = compType;
    COPY_AREA (transform, pReq->matrix3X3, sizeof (pexMatrix3X3));

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXSetGlobalTransform (display, resource_id, req_type, transform)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT PEXMatrix		transform;

{
    PEXAddSimpleOC (display, resource_id, req_type, PEXOCGlobalTransform,
	sizeof (PEXMatrix), transform);
}


void
PEXSetGlobalTransform2D (display, resource_id, req_type, transform)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT PEXMatrix3x3	transform;

{
    PEXAddSimpleOC (display, resource_id, req_type, PEXOCGlobalTransform2D,
	sizeof (PEXMatrix3x3), transform);
}


void
PEXSetModelClipFlag (display, resource_id, req_type, flag)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		flag;

{
    pexSwitch		f = flag;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCModelClipFlag,
	sizeof (pexSwitch), &f);
}


void
PEXSetModelClipVolume (display, resource_id, req_type, op,
    numHalfSpaces, halfSpaces)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		op;
INPUT unsigned int	numHalfSpaces;
INPUT PEXHalfSpace	*halfSpaces;

{
    pexModelClipVolume 	*pReq;
    int			lenofData;


    /*
     * Initialize the OC request.
     */

    lenofData = NUMWORDS (numHalfSpaces * sizeof (PEXHalfSpace));

    PEXInitOC (display, resource_id, req_type, PEXOCModelClipVolume, 
	LENOF (pexModelClipVolume), lenofData, pexModelClipVolume, pReq);

    if (pReq == NULL) return;


    /* 
     * Store the request header data. 
     */

    pReq->modelClipOperator = op; 
    pReq->numHalfSpaces = numHalfSpaces;


    /*
     * Copy the oc data.
     */

    PEXCopyWordsToOC (display, lenofData, (char *) halfSpaces);

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXSetModelClipVolume2D (display, resource_id, req_type, op,
    numHalfSpaces, halfSpaces)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		op;
INPUT unsigned int	numHalfSpaces;
INPUT PEXHalfSpace2D	*halfSpaces;

{
    pexModelClipVolume2D 	*pReq;
    int				lenofData;


    /*
     * Initialize the OC request.
     */

    lenofData = NUMWORDS (numHalfSpaces * sizeof (PEXHalfSpace2D));

    PEXInitOC (display, resource_id, req_type, PEXOCModelClipVolume2D, 
	LENOF (pexModelClipVolume2D), lenofData, pexModelClipVolume2D, pReq);

    if (pReq == NULL) return;


    /* 
     * Store the request header data. 
     */

    pReq->modelClipOperator = op; 
    pReq->numHalfSpaces = numHalfSpaces;


    /*
     * Copy the oc data.
     */

    PEXCopyWordsToOC (display, lenofData, (char *) halfSpaces);

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXRestoreModelClipVolume (display, resource_id, req_type)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;

{
    PEXAddSimpleOC (display, resource_id, req_type,
	PEXOCRestoreModelClipVolume, 0, (char *) NULL);
}


void
PEXSetViewIndex (display, resource_id, req_type, index)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned int	index;

{
    pexTableIndex	i = index;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCViewIndex,
	sizeof (pexTableIndex), &i);
}


void
PEXSetLightSourceState (display, resource_id, req_type,
    numEnable, enable, numDisable, disable)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned int	numEnable;
INPUT PEXTableIndex	*enable;
INPUT unsigned int	numDisable;
INPUT PEXTableIndex	*disable;

{
    pexLightState	*pReq;
    int			sizofEnableList = numEnable * sizeof (CARD16);
    int			sizofDisableList = numDisable * sizeof (CARD16);


    /*
     * Initialize the OC request.
     */

    PEXInitOC (display, resource_id, req_type, PEXOCLightSourceState,
	LENOF (pexLightState),
	NUMWORDS (sizofEnableList) + NUMWORDS (sizofDisableList),
	pexLightState, pReq);

    if (pReq == NULL) return;


    /* 
     * Store the request header data. 
     */

    pReq->numEnable = numEnable;
    pReq->numDisable = numDisable;


    /*
     * Copy the oc data.
     */

    _PEXCopyPaddedBytesToOC (display, sizofEnableList, (char *) enable); 
    _PEXCopyPaddedBytesToOC (display, sizofDisableList, (char *) disable); 

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXSetDepthCueIndex (display, resource_id, req_type, index)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned int	index;

{
    pexTableIndex	i = index;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCDepthCueIndex,
	sizeof (pexTableIndex), &i);
}


void
PEXSetPickID (display, resource_id, req_type, id)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned long	id;

{
    PEXAddSimpleOC (display, resource_id, req_type, PEXOCPickID,
	sizeof (CARD32), &id);
}


void
PEXSetHLHSRID (display, resource_id, req_type, id)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned long	id;

{
    PEXAddSimpleOC (display, resource_id, req_type, PEXOCHLHSRID,
	sizeof (CARD32), &id);
}


void
PEXSetColorApproxIndex (display, resource_id, req_type, index)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned int	index;

{
    pexTableIndex	i = index;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCColorApproxIndex,
	sizeof (pexTableIndex), &i);
}


void
PEXSetParaSurfCharacteristics (display, resource_id, req_type,
    pscType, pscData)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		pscType;
INPUT PEXPSCData	*pscData;

{
    pexParaSurfCharacteristics 	*pReq;
    int                 	lenofData;


    /*
     * Initialize the OC request.
     */

    lenofData = 0; 
    if (pscType == PEXPSCIsoCurves)
    {
	lenofData = LENOF (PEXPSCIsoparametricCurves);
    }
    else if (pscType == PEXPSCMCLevelCurves || pscType == PEXPSCWCLevelCurves)
    {
	lenofData = NUMWORDS (sizeof (pexPSC_LevelCurves) +
		(pscData->level_curves.count * sizeof (float)));
    }

    PEXInitOC (display, resource_id, req_type, PEXOCParaSurfCharacteristics,
	LENOF (pexParaSurfCharacteristics), lenofData,
	pexParaSurfCharacteristics, pReq);

    if (pReq == NULL) return;


    /* 
     * Store the request header data. 
     */

    pReq->characteristics = pscType;
    pReq->length = NUMBYTES (lenofData);


    /*
     * Copy the oc data.
     */

    if (lenofData > 0)
    {
	if (pscType == PEXPSCIsoCurves)
	{
	    PEXCopyWordsToOC (display, lenofData, (char *) pscData);
	}
	else if (pscType == PEXPSCMCLevelCurves ||
	    pscType == PEXPSCWCLevelCurves)
	{
	    PEXCopyBytesToOC (display,  sizeof (pexPSC_LevelCurves),
		(char *) pscData);

	    PEXCopyBytesToOC (display,
		pscData->level_curves.count * sizeof (float),
		(char *) (pscData->level_curves.parameters));
	}
    }

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXSetRenderingColorModel (display, resource_id, req_type, model)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		model;

{
    pexEnumTypeIndex	m = model;

    PEXAddSimpleOC (display, resource_id, req_type, PEXOCRenderingColorModel,
	sizeof (pexEnumTypeIndex), &m);
}


void
PEXAddToNameSet (display, resource_id, req_type, numNames, names)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned long	numNames;
INPUT PEXName		*names;

{
    PEXAddListOC (display, resource_id, req_type, PEXOCAddToNameSet,
	False /* count needed */,
	numNames, sizeof (PEXName), (char *) names);
}


void
PEXRemoveFromNameSet (display, resource_id, req_type, numNames, names)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned long	numNames;
INPUT PEXName		*names;

{
    PEXAddListOC (display, resource_id, req_type, PEXOCRemoveFromNameSet,
	False /* count needed */, 
	numNames, sizeof (PEXName), (char *) names);
}
