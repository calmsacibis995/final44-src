/* $XConsortium: pl_oc_prim.c,v 1.11 92/11/10 11:45:32 mor Exp $ */

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
PEXMarkers (display, resource_id, req_type, numPoints, points)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned int	numPoints;
INPUT PEXCoord 		*points;

{
    PEXAddListOC (display, resource_id, req_type, PEXOCMarkers,
    	False /* count needed */,
	numPoints, sizeof (PEXCoord), (char *) points);
}


void
PEXMarkers2D (display, resource_id, req_type, numPoints, points)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned int	numPoints;
INPUT PEXCoord2D	*points;

{
    PEXAddListOC (display, resource_id, req_type, PEXOCMarkers2D,
	False /* count needed */,
	numPoints, sizeof (PEXCoord2D), (char *) points);
}


void
PEXText (display, resource_id, req_type, origin, vec1, vec2, count, string)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT PEXCoord		*origin;
INPUT PEXVector		*vec1;
INPUT PEXVector		*vec2;
INPUT int		count;
INPUT char		*string;

{
    pexText	*pReq;


    /*
     * Initialize the OC request.
     */

    PEXInitOC (display, resource_id, req_type, PEXOCText,
	LENOF (pexText), 
	LENOF (pexMonoEncoding) + NUMWORDS (count),
	pexText, pReq);

    if (pReq == NULL) return;


    /* 
     * Store the text request header data. 
     */

    pReq->origin = *(pexCoord3D *) origin;
    pReq->vector1 = *(pexVector3D *) vec1;
    pReq->vector2 = *(pexVector3D *) vec2;
    pReq->numEncodings = (CARD16) 1;


    /*
     * Store the mono-encoded string.
     */

    StoreDefaultMonoString (display, count, string);

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXText2D (display, resource_id, req_type, origin, count, string)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT PEXCoord2D	*origin;
INPUT int		count;
INPUT char		*string;

{
    pexText2D	*pReq;


    /*
     * Initialize the OC request.
     */

    PEXInitOC (display, resource_id, req_type, PEXOCText2D,
	LENOF (pexText2D), 
	LENOF (pexMonoEncoding) + NUMWORDS (count),
	pexText2D, pReq);

    if (pReq == NULL) return;


    /* 
     * Store the text header request data. 
     */

    pReq->origin = *(pexCoord2D *) origin;
    pReq->numEncodings = (CARD16) 1;


    /*
     * Store the mono-encoded string.
     */

    StoreDefaultMonoString (display, count, string);

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXAnnotationText (display, resource_id, req_type,
    origin, offset, count, string)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT PEXCoord		*origin;
INPUT PEXCoord		*offset;
INPUT int		count;
INPUT char		*string;

{
    pexAnnotationText	*pReq;


    /*
     * Initialize the OC request.
     */

    PEXInitOC (display, resource_id, req_type, PEXOCAnnotationText,
	LENOF (pexAnnotationText),
	LENOF (pexMonoEncoding) + NUMWORDS (count),
	pexAnnotationText, pReq);

    if (pReq == NULL) return;


    /* 
     * Store the atext request header data. 
     */

    pReq->origin = *(pexCoord3D *) origin;
    pReq->offset = *(pexCoord3D *) offset;
    pReq->numEncodings = (CARD16) 1;


    /*
     * Store the mono-encoded string.
     */

    StoreDefaultMonoString (display, count, string);

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXAnnotationText2D (display, resource_id, req_type,
    origin, offset, count, string)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT PEXCoord2D	*origin;
INPUT PEXCoord2D	*offset;
INPUT int		count;
INPUT char		*string;

{
    pexAnnotationText2D	*pReq;


    /*
     * Initialize the OC request.
     */

    PEXInitOC (display, resource_id, req_type, PEXOCAnnotationText2D,
	LENOF (pexAnnotationText2D), 
	LENOF (pexMonoEncoding) + NUMWORDS (count),
	pexAnnotationText2D, pReq);

    if (pReq == NULL) return;


    /*
     * Store the atext request header data. 
     */

    pReq->origin = *(pexCoord2D *) origin;
    pReq->offset = *(pexCoord2D *) offset;
    pReq->numEncodings = (CARD16) 1;


    /*
     * Store the mono-encoded string.
     */

    StoreDefaultMonoString (display, count, string);

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXEncodedText (display, resource_id, req_type,
    origin, vec1, vec2, numEncodings, encodedTextList)

INPUT Display			*display;
INPUT XID			resource_id;
INPUT PEXOCRequestType		req_type;
INPUT PEXCoord			*origin;
INPUT PEXVector			*vec1;
INPUT PEXVector			*vec2;
INPUT unsigned int		numEncodings;
INPUT PEXEncodedTextData	*encodedTextList;

{
    pexText		*pReq;
    int 		lenofStrings, i;
    PEXEncodedTextData  *nextString;


    /*
     * Get length of mono-encoded strings. 
     */

    GetStringsLength (numEncodings, encodedTextList, lenofStrings);


    /*
     * Initialize the OC request.
     */

    PEXInitOC (display, resource_id, req_type, PEXOCText,
	LENOF (pexText), lenofStrings, pexText, pReq);

    if (pReq == NULL) return;


    /* 
     * Store the text request header data. 
     */

    pReq->origin = *(pexCoord3D *) origin;
    pReq->vector1 = *(pexVector3D *) vec1;
    pReq->vector2 = *(pexVector3D *) vec2;
    pReq->numEncodings = (CARD16) numEncodings;


    /*
     * Store the mono-encoded string.
     */

    StoreMonoStrings (display, numEncodings, encodedTextList);

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXEncodedText2D (display, resource_id, req_type,
    origin, numEncodings, encodedTextList)

INPUT Display			*display;
INPUT XID			resource_id;
INPUT PEXOCRequestType		req_type;
INPUT PEXCoord2D		*origin;
INPUT unsigned int		numEncodings;
INPUT PEXEncodedTextData	*encodedTextList;

{
    pexText2D		*pReq;
    PEXEncodedTextData	*nextString;
    int 		lenofStrings, i;


    /*
     * Get length of mono-encoded strings. 
     */

    GetStringsLength (numEncodings, encodedTextList, lenofStrings);


    /*
     * Initialize the OC request.
     */

    PEXInitOC (display, resource_id, req_type, PEXOCText2D,
	LENOF (pexText2D), lenofStrings, pexText2D, pReq);

    if (pReq == NULL) return;


    /* 
     * Store the text header request data. 
     */

    pReq->origin = *(pexCoord2D *) origin;
    pReq->numEncodings = (CARD16) numEncodings;


    /*
     * Store the mono-encoded string.
     */

    StoreMonoStrings (display, numEncodings, encodedTextList);

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXEncodedAnnoText (display, resource_id, req_type,
    origin, offset, numEncodings, encodedTextList)

INPUT Display			*display;
INPUT XID			resource_id;
INPUT PEXOCRequestType		req_type;
INPUT PEXCoord			*origin;
INPUT PEXCoord			*offset;
INPUT unsigned int		numEncodings;
INPUT PEXEncodedTextData 	*encodedTextList;

{
    pexAnnotationText	*pReq;
    PEXEncodedTextData	*nextString;
    int 		lenofStrings, i;


    /*
     * Get length of mono-encoded strings. 
     */

    GetStringsLength (numEncodings, encodedTextList, lenofStrings);


    /*
     * Initialize the OC request.
     */

    PEXInitOC (display, resource_id, req_type, PEXOCAnnotationText,
	LENOF (pexAnnotationText), lenofStrings, pexAnnotationText, pReq);

    if (pReq == NULL) return;


    /* 
     * Store the atext request header data. 
     */

    pReq->origin = *(pexCoord3D *) origin;
    pReq->offset = *(pexCoord3D *) offset;
    pReq->numEncodings = (CARD16) numEncodings;


    /*
     * Store the mono-encoded string.
     */

    StoreMonoStrings (display, numEncodings, encodedTextList);

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXEncodedAnnoText2D (display, resource_id, req_type,
    origin, offset, numEncodings, encodedTextList)

INPUT Display			*display;
INPUT XID			resource_id;
INPUT PEXOCRequestType		req_type;
INPUT PEXCoord2D		*origin;
INPUT PEXCoord2D		*offset;
INPUT unsigned int		numEncodings;
INPUT PEXEncodedTextData 	*encodedTextList;

{
    pexAnnotationText2D	*pReq;
    PEXEncodedTextData	*nextString;
    int 		lenofStrings, i;


    /*
     * Get length of mono-encoded strings. 
     */

    GetStringsLength (numEncodings, encodedTextList, lenofStrings);


    /*
     * Initialize the OC request.
     */

    PEXInitOC (display, resource_id, req_type, PEXOCAnnotationText2D,
	LENOF (pexAnnotationText2D), lenofStrings, pexAnnotationText2D, pReq);

    if (pReq == NULL) return;


    /* 
     * Store the atext request header data. 
     */

    pReq->origin = *(pexCoord2D *) origin;
    pReq->offset = *(pexCoord2D *) offset;
    pReq->numEncodings = (CARD16) numEncodings;


    /*
     * Store the mono-encoded string.
     */

    StoreMonoStrings (display, numEncodings, encodedTextList);

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXPolyline (display, resource_id, req_type, numVertices, vertices)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned int	numVertices;
INPUT PEXCoord		*vertices;

{
    PEXAddListOC (display, resource_id, req_type, PEXOCPolyline,
	False /* count needed */,
	numVertices, sizeof (PEXCoord), (char *) vertices);
}


void
PEXPolyline2D (display, resource_id, req_type, numVertices, vertices)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned int	numVertices;
INPUT PEXCoord2D	*vertices;

{
    PEXAddListOC (display, resource_id, req_type, PEXOCPolyline2D,
	False /* count needed */,
	numVertices, sizeof (PEXCoord2D), (char *) vertices);
}


void
PEXPolylineSetWithData (display, resource_id, req_type,
    vertexAttributes, colorType, numPolylines, polylines)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT unsigned int	vertexAttributes;
INPUT int		colorType;
INPUT unsigned int	numPolylines;
INPUT PEXListOfVertex	*polylines;

{
    pexPolylineSet	*pReq;
    CARD32 		*pData;
    int			numPoints, i;
    int			lenofVertex;


    /* 
     * Calculate the total number of vertices.
     */

    for (i = 0, numPoints = 0; i < numPolylines; i++)
	numPoints += polylines[i].count;


    /* 
     * Calculate how big each vertex is.
     */

    lenofVertex = LENOF (PEXCoord) +
	((vertexAttributes & PEXGAColor) ? GetColorLength (colorType) : 0); 


    /*
     * Initialize the OC request.
     */

    PEXInitOC (display, resource_id, req_type, PEXOCPolylineSetWithData, 
	LENOF (pexPolylineSet), 
	numPolylines + (numPoints * lenofVertex),
	pexPolylineSet, pReq);

    if (pReq == NULL) return;


    /* 
     * Store the polyline request header data. 
     */

    pReq->colorType = colorType;
    pReq->vertexAttribs = vertexAttributes;
    pReq->numLists = numPolylines;


    /* 
     * For each polyline store a count and then the list of vertices. 
     * Note that the vertices are padded to end on a word boundary
     */

    for (i = 0; i < numPolylines; i++)
    {
	pData = (CARD32 *) PEXGetOCAddr (display, sizeof (CARD32));
	*pData = polylines[i].count;  

	PEXCopyWordsToOC (display, polylines[i].count * lenofVertex, 
	    (char *) polylines[i].vertices.no_data);
    }

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXNURBCurve (display, resource_id, req_type,
    rationality, order, knots, numPoints, points, tmin, tmax)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		rationality;
INPUT int		order;
INPUT float		*knots;
INPUT unsigned int	numPoints;
INPUT PEXArrayOfCoord	points;
INPUT double		tmin;
INPUT double		tmax;

{
    pexNurbCurve 	*pReq;
    int			lenofVertexList;
    int			lenofKnotList;


    /* 
     * Calculate the number of words in the vertex list and knot list.  The 
     * number of knots = order + number of points.
     */

    lenofVertexList = numPoints * ((rationality == PEXRational) ?
	LENOF (PEXCoord4D) : LENOF (PEXCoord));
    lenofKnotList = order + numPoints;


    /*
     * Initialize the OC request.
     */

    PEXInitOC (display, resource_id, req_type, PEXOCNURBCurve,
	LENOF (pexNurbCurve),
	lenofKnotList + lenofVertexList,
	pexNurbCurve, pReq);

    if (pReq == NULL) return;


    /* 
     * Store the nurb request header data. 
     */

    pReq->curveOrder = order;
    pReq->coordType = rationality;
    pReq->tmin = tmin;
    pReq->tmax = tmax;
    pReq->numKnots = order + numPoints;
    pReq->numPoints = numPoints;


    /*
     * Store the knot list and the vertex list.
     */

    PEXCopyWordsToOC (display, lenofKnotList, (char *) knots);
    PEXCopyWordsToOC (display, lenofVertexList, (char *) points.point);

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXFillArea (display, resource_id, req_type,
    shape, ignoreEdges, numPoints, points)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		shape;
INPUT int		ignoreEdges;
INPUT unsigned int	numPoints;
INPUT PEXCoord 		*points;

{
    pexFillArea		*pReq;
    int			lenofVertexList;


    /*
     * Initialize the OC request.
     */

    lenofVertexList = numPoints * LENOF (PEXCoord);

    PEXInitOC (display, resource_id, req_type, PEXOCFillArea,
	LENOF (pexFillArea), lenofVertexList, pexFillArea, pReq);

    if (pReq == NULL) return;


    /* 
     * Store the fill area request data. 
     */

    pReq->shape = shape;
    pReq->ignoreEdges = ignoreEdges;


    /*
     * Copy the vertex data to the oc.
     */

    PEXCopyWordsToOC (display, lenofVertexList, (char *) points);

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXFillArea2D (display, resource_id, req_type,
    shape, ignoreEdges, numPoints, points)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		shape;
INPUT int		ignoreEdges;
INPUT unsigned int	numPoints;
INPUT PEXCoord2D	*points;

{
    pexFillArea2D	*pReq;
    int			lenofVertexList;


    /*
     * Initialize the OC request.
     */

    lenofVertexList = numPoints * LENOF (PEXCoord2D);

    PEXInitOC (display, resource_id, req_type, PEXOCFillArea2D,
        LENOF (pexFillArea2D), lenofVertexList, pexFillArea2D, pReq);

    if (pReq == NULL) return;


    /* 
     * Store the fill area request data. 
     */

    pReq->shape = shape;
    pReq->ignoreEdges = ignoreEdges;


    /*
     * Copy the vertex data to the oc.
     */

    PEXCopyWordsToOC (display, lenofVertexList, (char *) points);

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXFillAreaWithData (display, resource_id, req_type,
    shape, ignoreEdges, facetAttributes, vertexAttributes, colorType,
    facetData, numVertices, vertices)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		shape;
INPUT int		ignoreEdges;
INPUT unsigned int	facetAttributes;
INPUT unsigned int	vertexAttributes;
INPUT int		colorType;
INPUT PEXFacetData	*facetData;
INPUT unsigned int	numVertices;
INPUT PEXArrayOfVertex	vertices;

{
    pexExtFillArea 	*pReq;
    CARD32		*pData;
    int			lenofFacetData;
    int			lenofVertex;
    int			lenofColor;


    /* 
     * Calculate the number of words in the optional facet data and the
     * number of words per vertex.
     */

    lenofColor = GetColorLength (colorType);
    lenofFacetData = GetFacetDataLength (facetAttributes, lenofColor); 
    lenofVertex = GetVertexWithDataLength (vertexAttributes, lenofColor);


    /*
     * Initialize the OC request.
     */

    PEXInitOC (display, resource_id, req_type, PEXOCFillAreaWithData,
	LENOF (pexExtFillArea),
	lenofFacetData + 1 /* count */ + numVertices * lenofVertex,
        pexExtFillArea, pReq);

    if (pReq == NULL) return;


    /* 
     * Store the fill area request header data. 
     */

    pReq->shape = shape;
    pReq->ignoreEdges = ignoreEdges;
    pReq->colorType = colorType;
    pReq->facetAttribs = facetAttributes;
    pReq->vertexAttribs = vertexAttributes;


    /*
     * Copy the facet data and vertices to the oc.
     */

    if (facetAttributes)
        PEXCopyWordsToOC (display, lenofFacetData, (char *) facetData);

    pData = (CARD32 *) PEXGetOCAddr (display, sizeof (CARD32));
    *pData = numVertices;

    PEXCopyWordsToOC (display, lenofVertex * numVertices,
	(char *) vertices.no_data);

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXFillAreaSet (display, resource_id, req_type,
    shape, ignoreEdges,	contourHint, numFillAreas, vertices)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		shape;
INPUT int		ignoreEdges;
INPUT int		contourHint;
INPUT unsigned int	numFillAreas;
INPUT PEXListOfCoord	*vertices;

{
    pexFillAreaSet	*pReq;
    CARD32		*pData;
    int			numPoints, i;


    /* 
     * Calculate the total number of vertices 
     */

    for (i = 0, numPoints = 0; i < numFillAreas; i++)
	numPoints += vertices[i].count;


    /*
     * Initialize the OC request.
     */

    PEXInitOC (display, resource_id, req_type, PEXOCFillAreaSet,
	LENOF (pexFillAreaSet),
	numFillAreas /* counts */ + (numPoints * LENOF (PEXCoord)),
	pexFillAreaSet, pReq);

    if (pReq == NULL) return;


    /* 
     * Store the fill area set request header data. 
     */

    pReq->shape = shape; 
    pReq->ignoreEdges = ignoreEdges;
    pReq->contourHint = contourHint;
    pReq->numLists = numFillAreas;


    /*
     * Now store the fill area set.  Each fill area in the set consists of
     * a vertex count followed a polygon.
     */

    for (i = 0; i < numFillAreas; i++)
    {
	pData = (CARD32 *) PEXGetOCAddr (display, sizeof (CARD32));
	*pData = vertices[i].count;

	PEXCopyWordsToOC (display, vertices[i].count * LENOF (PEXCoord), 
	    (char *) vertices[i].points);
    }

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXFillAreaSet2D (display, resource_id, req_type,
    shape, ignoreEdges, contourHint, numFillAreas, vertices)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		shape;
INPUT int		ignoreEdges;
INPUT int		contourHint;
INPUT unsigned int	numFillAreas;
INPUT PEXListOfCoord2D	*vertices;

{
    pexFillAreaSet2D	*pReq;
    CARD32		*pData;
    int			numPoints, i;


    /* 
     * Calculate the total number of vertices 
     */

    for (i = 0, numPoints = 0; i < numFillAreas; i++)
	numPoints += vertices[i].count;


    /*
     * Initialize the OC request.
     */

    PEXInitOC (display, resource_id, req_type, PEXOCFillAreaSet2D,
	LENOF (pexFillAreaSet2D),
	numFillAreas /* counts */ + (numPoints * LENOF (PEXCoord2D)), 
	pexFillAreaSet2D, pReq);

    if (pReq == NULL) return;


    /* 
     * Store the fill area set request header data. 
     */

    pReq->shape = shape;
    pReq->ignoreEdges = ignoreEdges;
    pReq->contourHint = contourHint;
    pReq->numLists = numFillAreas;


    /*
     * Now store the fill area set.  Each fill area in the set consists of
     * a vertex count followed a polygon.
     */

    for (i = 0; i < numFillAreas; i++)
    {
	pData = (CARD32 *) PEXGetOCAddr (display, sizeof (CARD32));
	*pData = vertices[i].count;  

	PEXCopyWordsToOC (display, vertices[i].count * LENOF (PEXCoord2D), 
	   (char *) vertices[i].points);
    }

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXFillAreaSetWithData (display, resource_id, req_type,
    shape, ignoreEdges, contourHint, facetAttributes, vertexAttributes,
    colorType, numFillAreas, facetData, vertices)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		shape;
INPUT int		ignoreEdges;
INPUT int		contourHint;
INPUT unsigned int	facetAttributes;
INPUT unsigned int	vertexAttributes;
INPUT int		colorType;
INPUT unsigned int	numFillAreas;
INPUT PEXFacetData	*facetData;
INPUT PEXListOfVertex	*vertices;

{
    pexExtFillAreaSet		*pReq;
    CARD32			*pData;
    int				lenofColor;
    int				lenofFacetData;
    int				lenofVertex;
    int				numVertices, j;


    /* 
     * Calculate the size of the facet data and vertex data.
     */

    lenofColor = GetColorLength (colorType);
    lenofFacetData = GetFacetDataLength (facetAttributes, lenofColor); 
    lenofVertex = GetVertexWithDataLength (vertexAttributes, lenofColor);

    if (vertexAttributes & PEXGAEdges)
	lenofVertex++; 			/* edge switch is CARD32 */

    for (j = 0, numVertices = 0; j < numFillAreas; j++)
	numVertices += vertices[j].count;


    /*
     * Initialize the OC request.
     */

    PEXInitOC (display, resource_id, req_type, PEXOCFillAreaSetWithData, 
	LENOF (pexExtFillAreaSet), 
	lenofFacetData + numFillAreas + numVertices * lenofVertex,
	pexExtFillAreaSet, pReq);

    if (pReq == NULL) return;


    /* 
     * Store the fill area set request header data. 
     */

    pReq->shape = shape;
    pReq->ignoreEdges = ignoreEdges;
    pReq->contourHint = contourHint;
    pReq->colorType = colorType;
    pReq->facetAttribs = facetAttributes;
    pReq->vertexAttribs = vertexAttributes;
    pReq->numLists = numFillAreas;


    /*
     * Copy the facet data
     */

    if (facetAttributes)
	PEXCopyWordsToOC (display, lenofFacetData, (char *) facetData);


    /*
     * Copy the polygon vertices, preceded by a count.
     * Note that the vertices are padded to end on a word boundary.
     */

    for (j = 0; j < numFillAreas; j++)
    {
	pData = (CARD32 *) PEXGetOCAddr (display, sizeof (CARD32));
	*pData = vertices[j].count; 

	PEXCopyWordsToOC (display, vertices[j].count * lenofVertex,
	    (char *) vertices[j].vertices.no_data);
    }

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXSetOfFillAreaSets (display, resource_id, req_type, shape,
    facetAttributes, vertexAttributes, edgeAttributes, contourHint,
    contoursAllOne, colorType, numFillAreaSets, facetData,
    numVertices, vertices, numIndices, edgeFlags, connectivity)

INPUT Display			*display;
INPUT XID			resource_id;
INPUT PEXOCRequestType		req_type;
INPUT int			shape;
INPUT unsigned int		facetAttributes;
INPUT unsigned int		vertexAttributes;
INPUT unsigned int		edgeAttributes;
INPUT int			contourHint;
INPUT int			contoursAllOne;
INPUT int			colorType;
INPUT unsigned int		numFillAreaSets;
INPUT PEXArrayOfFacetData 	facetData;
INPUT unsigned int		numVertices; 
INPUT PEXArrayOfVertex		vertices;
INPUT unsigned int		numIndices; 
INPUT PEXSwitch			*edgeFlags;
INPUT PEXConnectivityData	*connectivity;

{
    pexSOFAS		*pReq;
    PEXConnectivityData *pConnectivity;
    PEXListOfUShort 	*pList;
    int 		lenofColor;
    int 		lenofFacet;
    int 		lenofVertex;
    int 		sizeofEdge;
    int			totLength;
    int 		numContours;
    int 		count = 0;
    int			i, j, cbytes;
    CARD16		*pData;


    /* 
     * Calculate the total number of contours.
     */

    numContours = 0;
    pConnectivity = connectivity;
    for (i = 0; i < numFillAreaSets; i++, pConnectivity++)
	numContours += pConnectivity->count;


    /* 
     * Calculate the size of the facet data and vertex data
     */

    lenofColor = GetColorLength (colorType);
    lenofFacet = GetFacetDataLength (facetAttributes, lenofColor); 
    lenofVertex = GetVertexWithDataLength (vertexAttributes, lenofColor);
    sizeofEdge = edgeAttributes ? sizeof (CARD8) : 0;

    cbytes = sizeof (CARD16) * (numFillAreaSets + numContours + numIndices);

    totLength = (lenofFacet * numFillAreaSets) + (lenofVertex * numVertices) + 
	NUMWORDS (sizeofEdge * numIndices) + NUMWORDS (cbytes);


    /*
     * Initialize the OC request.
     */

    PEXInitOC (display, resource_id, req_type, PEXOCSetOfFillAreaSets,
	LENOF (pexSOFAS), totLength, pexSOFAS, pReq);

    if (pReq == NULL) return;


    /* 
     * Store the SOFA request header data. 
     */

    pReq->shape = shape;
    pReq->colorType = colorType;
    pReq->FAS_Attributes = facetAttributes;
    pReq->vertexAttributes = vertexAttributes;
    pReq->edgeAttributes = edgeAttributes ? PEXOn : PEXOff;
    pReq->contourHint = contourHint;
    pReq->contourCountsFlag = contoursAllOne;
    pReq->numFAS = numFillAreaSets;
    pReq->numVertices = numVertices;
    pReq->numEdges = numIndices;
    pReq->numContours = numContours;


    /*
     * Copy the facet and vertex data to the oc.
     */

    if (facetAttributes )
	PEXCopyWordsToOC (display, lenofFacet * numFillAreaSets,
            (char *) facetData.index);

    PEXCopyWordsToOC (display, lenofVertex * numVertices,
            (char *) vertices.no_data);

    if (edgeAttributes)
	_PEXCopyPaddedBytesToOC (display, numIndices * sizeof (CARD8),
	    (char *) edgeFlags);


    /*
     * Now add the connectivity data.
     */

    pConnectivity = connectivity;

    for (i = 0 ; i < numFillAreaSets; i++)
    {
	pData = (CARD16 *) PEXGetOCAddr (display, sizeof (CARD16));
	*pData = count = pConnectivity->count;

	for (j = 0, pList = pConnectivity->lists; j < count; j++, pList++)
	{
	    pData = (CARD16 *) PEXGetOCAddr (display, sizeof (CARD16));
	    *pData = pList->count;

	    PEXCopyBytesToOC (display, pList->count * sizeof (CARD16),
		(char *) pList->shorts);
	}

	pConnectivity++;
    }

    if (PAD (cbytes))
	PEXGetOCAddr (display, PAD (cbytes));

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXTriangleStrip (display, resource_id, req_type,
    facetAttributes, vertexAttributes, colorType,
    facetData, numVertices, vertices)

INPUT Display			*display;
INPUT XID			resource_id;
INPUT PEXOCRequestType		req_type;
INPUT unsigned int		facetAttributes;
INPUT unsigned int		vertexAttributes;
INPUT int			colorType;
INPUT PEXArrayOfFacetData 	facetData;
INPUT unsigned int		numVertices;
INPUT PEXArrayOfVertex		vertices;

{
    pexTriangleStrip	*pReq;
    int			lenofColor;
    int			lenofFacetDataList;
    int			lenofVertexList;


    /* 
     * Calculate number of words in the list of facet data and the vertex list.
     */

    lenofColor = GetColorLength (colorType);
    lenofFacetDataList = (numVertices - 2) *
	GetFacetDataLength (facetAttributes, lenofColor); 
    lenofVertexList = numVertices *
	GetVertexWithDataLength (vertexAttributes, lenofColor);


    /*
     * Initialize the OC request.
     */

    PEXInitOC (display, resource_id, req_type, PEXOCTriangleStrip, 
	LENOF (pexTriangleStrip),
	lenofFacetDataList + lenofVertexList,
	pexTriangleStrip, pReq);

    if (pReq == NULL) return;


    /* 
     * Store the triangle strip request header data. 
     */

    pReq->colorType = colorType;
    pReq->facetAttribs = facetAttributes;
    pReq->vertexAttribs = vertexAttributes;
    pReq->numVertices = numVertices;


    /*
     * Copy the facet data and vertices to the oc.
     */

    if (facetAttributes)
        PEXCopyWordsToOC (display, lenofFacetDataList,
	    (char *) facetData.index);

    PEXCopyWordsToOC (display, lenofVertexList, (char *) vertices.no_data);

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXQuadrilateralMesh (display, resource_id, req_type,
    shape, facetAttributes, vertexAttributes, colorType,
    facetData, colCount, rowCount, vertices)

INPUT Display			*display;
INPUT XID			resource_id;
INPUT PEXOCRequestType		req_type;
INPUT int			shape;
INPUT unsigned int		facetAttributes;
INPUT unsigned int		vertexAttributes;
INPUT int			colorType;
INPUT PEXArrayOfFacetData 	facetData;
INPUT unsigned int		colCount;
INPUT unsigned int		rowCount;
INPUT PEXArrayOfVertex		vertices;

{
    pexQuadrilateralMesh 	*pReq;
    int				lenofColor;
    int				lenofFacetDataList;
    int				lenofVertexList;


    /* 
     * Calculate the number of words in the facet data list and vertex list.
     */

    lenofColor = GetColorLength (colorType);
    lenofFacetDataList = ((rowCount - 1) * (colCount - 1)) *
	GetFacetDataLength (facetAttributes, lenofColor); 
    lenofVertexList = rowCount * colCount *
	GetVertexWithDataLength (vertexAttributes, lenofColor);


    /*
     * Initialize the OC request.
     */

    PEXInitOC (display, resource_id, req_type, PEXOCQuadrilateralMesh, 
	LENOF (pexQuadrilateralMesh),
	lenofFacetDataList + lenofVertexList,
	pexQuadrilateralMesh, pReq);

    if (pReq == NULL) return;


    /* 
     * Store the quad mesh request header data. 
     */

    pReq->colorType = colorType;
    pReq->mPts = colCount;
    pReq->nPts = rowCount;
    pReq->facetAttribs = facetAttributes;
    pReq->vertexAttribs = vertexAttributes;
    pReq->shape = shape;


    /*
     * Copy the facet data and vertices to the oc.
     */

    if (facetAttributes)
        PEXCopyWordsToOC (display, lenofFacetDataList,
            (char *) facetData.index);

    PEXCopyWordsToOC (display, lenofVertexList, (char *) vertices.no_data);

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXNURBSurface (display, resource_id, req_type, rationality, uorder, vorder,
    uknots, vknots, numMPoints, numNPoints, points, numTrimLoops, trimLoops)

INPUT Display			*display;
INPUT XID			resource_id;
INPUT PEXOCRequestType		req_type;
INPUT int			rationality;
INPUT int			uorder;
INPUT int			vorder;
INPUT float			*uknots;
INPUT float			*vknots;
INPUT unsigned int		numMPoints;
INPUT unsigned int		numNPoints;
INPUT PEXArrayOfCoord		points;
INPUT unsigned int		numTrimLoops;
INPUT PEXListOfTrimCurve 	*trimLoops;

{
    pexNurbSurface	*pReq;
    pexTrimCurve	*pTCHead;
    PEXTrimCurve	*ptrimCurve;
    PEXListOfTrimCurve	*ptrimLoop;
    CARD32		*pData;
    int			lenofVertexList;
    int			lenofUKnotList;
    int			lenofVKnotList;
    int			lenofTrimData;
    int			thisLength, i;
    int			count = 0;


    /* 
     * Calculate the number of words in the vertex list and the knot lists.
     */

    lenofVertexList = numMPoints * numNPoints *
        ((rationality == PEXRational) ? LENOF (PEXCoord4D) : LENOF (PEXCoord));
    lenofUKnotList = uorder + numMPoints;
    lenofVKnotList = vorder + numNPoints;


    /* 
     * Calculate the number of words in the trim curve data.  Note that the
     * vertices for the trim curve are in parametric space so they are either
     * 3D or 2D.
     */

    lenofTrimData = numTrimLoops * LENOF (CARD32);   /* count per loop */

    for (i = 0, ptrimLoop = trimLoops; i < numTrimLoops; i++, ptrimLoop++)
    {
	ptrimCurve = ptrimLoop->curves;
	count = ptrimLoop->count;
		
	while (count--)
	{
	    lenofTrimData += (LENOF (pexTrimCurve) +
		ptrimCurve->count + ptrimCurve->order +     /* knot list */
		ptrimCurve->count *
		(ptrimCurve->rationality == PEXRational ?
		    LENOF (pexCoord3D) : LENOF (pexCoord2D)));
	    ptrimCurve++;
	}
    }


    /*
     * Initialize the OC request.
     */

    PEXInitOC (display, resource_id, req_type, PEXOCNURBSurface,
	LENOF (pexNurbSurface),
	(lenofUKnotList + lenofVKnotList + lenofVertexList + lenofTrimData), 
	pexNurbSurface, pReq);

    if (pReq == NULL) return;


    /*
     * Store the nurb surface request header data.
     */

    pReq->type = rationality;
    pReq->uOrder = uorder;
    pReq->vOrder = vorder;
    pReq->numUknots = uorder + numMPoints;
    pReq->numVknots = vorder + numNPoints;
    pReq->mPts = numMPoints;
    pReq->nPts = numNPoints;
    pReq->numLists = numTrimLoops;


    /*
     * Now copy the knot lists and the vertex list.
     */

    PEXCopyWordsToOC (display, lenofUKnotList, (char *) uknots);
    PEXCopyWordsToOC (display, lenofVKnotList, (char *) vknots);
    PEXCopyWordsToOC (display, lenofVertexList, (char *) points.point);


    /* 
     * Now add the list of trim curve (LISTofTrimCurve).  A trim curve list
     * consists of a count followed by a list of trim curves. 
     */

    for (i = 0, ptrimLoop = trimLoops; i < numTrimLoops; i++, ptrimLoop++)
    {
	pData = (CARD32 *) PEXGetOCAddr (display, sizeof (CARD32));
	*pData = count = ptrimLoop->count;

	ptrimCurve = ptrimLoop->curves;

	while (count--)
	{
	    /*
	     * Add the trim curve header data.
	     */

	    thisLength = ptrimCurve->order + ptrimCurve->count;

	    pTCHead = (pexTrimCurve *)
		PEXGetOCAddr (display, sizeof (pexTrimCurve));

	    pTCHead->visibility = (pexSwitch) ptrimCurve->visibility;
	    pTCHead->order = (CARD16) ptrimCurve->order;
	    pTCHead->type = (pexCoordType) ptrimCurve->rationality;
	    pTCHead->approxMethod = (INT16) ptrimCurve->approx_method;
	    pTCHead->tolerance = (float) ptrimCurve->tolerance;
	    pTCHead->tMin = (float) ptrimCurve->tmin;
	    pTCHead->tMax = (float) ptrimCurve->tmax;
	    pTCHead->numKnots = thisLength;
	    pTCHead->numCoord = ptrimCurve->count;


	    /*
	     * Add the trim curve knot list and vertex list.
	     */

    	    PEXCopyWordsToOC (display, thisLength,
		(char *) ptrimCurve->knots.floats);

	    thisLength = ptrimCurve->count *
		((ptrimCurve->rationality == PEXRational) ?
		LENOF (PEXCoord) : LENOF (PEXCoord2D));

    	    PEXCopyWordsToOC (display, thisLength,
		(char *) ptrimCurve->control_points.point);

	    ptrimCurve++;
	}
    }

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXCellArray (display, resource_id, req_type, pt1, pt2, pt3, dx, dy, icolors)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT PEXCoord		*pt1;
INPUT PEXCoord		*pt2;
INPUT PEXCoord		*pt3;
INPUT unsigned int	dx;
INPUT unsigned int	dy;
INPUT PEXTableIndex 	*icolors;

{
    pexCellArray	*pReq;


    /*
     * Initialize the OC request.
     */

    PEXInitOC (display, resource_id, req_type, PEXOCCellArray,
	LENOF (pexCellArray),
	NUMWORDS (dx * dy * sizeof (pexTableIndex)),
        pexCellArray, pReq);

    if (pReq == NULL) return;


    /*
     * Store the cell array header data.
     */

    pReq->point1 = *(pexCoord3D *) pt1;
    pReq->point2 = *(pexCoord3D *) pt2;
    pReq->point3 = *(pexCoord3D *) pt3;
    pReq->dx = dx;
    pReq->dy = dy;


    /*
     * Copy the color data to the oc.
     */

    _PEXCopyPaddedBytesToOC (display, dx * dy * sizeof (pexTableIndex),
	(char *) icolors);

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXCellArray2D (display, resource_id, req_type, pt1, pt2, dx, dy, icolors)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT PEXCoord2D	*pt1;
INPUT PEXCoord2D	*pt2;
INPUT unsigned int	dx;
INPUT unsigned int	dy;
INPUT PEXTableIndex	*icolors;

{
    pexCellArray2D	*pReq;


    /*
     * Initialize the OC request.
     */

    PEXInitOC (display, resource_id, req_type, PEXOCCellArray2D,
	LENOF (pexCellArray2D), 
	NUMWORDS (dx * dy * sizeof (pexTableIndex)),
	pexCellArray2D,	pReq);

    if (pReq == NULL) return;


    /*
     * Store the cell array header data.
     */

    pReq->point1 = *(pexCoord2D *) pt1;
    pReq->point2 = *(pexCoord2D *) pt2;
    pReq->dx = dx;
    pReq->dy = dy;


    /*
     * Copy the color data to the oc.
     */

    _PEXCopyPaddedBytesToOC (display, dx * dy * sizeof (pexTableIndex),
	(char *) icolors);

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXExtendedCellArray (display, resource_id, req_type,
    pt1, pt2, pt3, dx, dy, colorType, colors)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT PEXCoord		*pt1;
INPUT PEXCoord		*pt2;
INPUT PEXCoord		*pt3;
INPUT unsigned int	dx;
INPUT unsigned int	dy;
INPUT int		colorType;
INPUT PEXArrayOfColor 	colors;

{
    pexExtCellArray 	*pReq;
    int			lenofColorList;


    /*
     * Initialize the OC request.
     */

    lenofColorList = dx * dy * GetColorLength (colorType);

    PEXInitOC (display, resource_id, req_type, PEXOCExtendedCellArray,
	LENOF (pexExtCellArray), lenofColorList, pexExtCellArray, pReq);

    if (pReq == NULL) return;


    /*
     * Store the cell array header data.
     */

    pReq->colorType = colorType;
    pReq->point1 = *(pexCoord3D *) pt1;
    pReq->point2 = *(pexCoord3D *) pt2;
    pReq->point3 = *(pexCoord3D *) pt3;
    pReq->dx = dx;
    pReq->dy = dy;


    /*
     * Copy the color data to the oc.
     */

    PEXCopyWordsToOC (display, lenofColorList, (char *) colors.indexed);

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXGDP (display, resource_id, req_type, id, numPoints, points, numBytes, data)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT long		id;
INPUT unsigned int	numPoints;
INPUT PEXCoord		*points;
INPUT unsigned long	numBytes;
INPUT char		*data;

{
    pexGdp	*pReq;
    int		lenofVertexList;


    /*
     * Initialize the OC request.
     */

    lenofVertexList = numPoints * LENOF (PEXCoord);

    PEXInitOC (display, resource_id, req_type, PEXOCGDP, LENOF (pexGdp), 
	lenofVertexList + NUMWORDS (numBytes), pexGdp, pReq);

    if (pReq == NULL) return;


    /*
     * Store the gdp header data.
     */

    pReq->gdpId = id; 
    pReq->numPoints = numPoints; 
    pReq->numBytes = numBytes;


    /*
     * Copy the vertices and GDP data to the oc.
     */

    PEXCopyWordsToOC (display, lenofVertexList, (char *) points);

    _PEXCopyPaddedBytesToOC (display, numBytes, (char *) data);

    PEXFinishOC (display);
    PEXSyncHandle (display);
}


void
PEXGDP2D (display, resource_id, req_type,
    id, numPoints, points, numBytes, data)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT long		id;
INPUT unsigned int	numPoints;
INPUT PEXCoord2D	*points;
INPUT unsigned long	numBytes;
INPUT char		*data;

{
    pexGdp2D	*pReq;
    int		lenofVertexList;


    /*
     * Initialize the OC request.
     */

    lenofVertexList = numPoints * LENOF (PEXCoord2D);

    PEXInitOC (display, resource_id, req_type, PEXOCGDP2D, LENOF (pexGdp2D), 
	lenofVertexList + NUMWORDS (numBytes), pexGdp2D, pReq);

    if (pReq == NULL) return;


    /*
     * Store the gdp header data.
     */

    pReq->gdpId = id; 
    pReq->numPoints = numPoints; 
    pReq->numBytes = numBytes;


    /*
     * Copy the vertices and GDP data to the oc.
     */

    PEXCopyWordsToOC (display, lenofVertexList, (char *) points);

    _PEXCopyPaddedBytesToOC (display, numBytes, (char *) data);

    PEXFinishOC (display);
    PEXSyncHandle (display);
}
