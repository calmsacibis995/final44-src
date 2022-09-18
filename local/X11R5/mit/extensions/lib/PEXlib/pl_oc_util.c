/* $XConsortium: pl_oc_util.c,v 1.13 92/11/10 11:46:09 mor Exp $ */

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


Status
PEXStartOCs (display, resource_id, req_type, float_format, numOCs, numWords)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		float_format;
INPUT int		numOCs;
INPUT int		numWords;

{
    PEXDisplayInfo 	*pexDisplayInfo;
    pexOCRequestHeader 	*currentReq;


    /*
     * Is the oc larger than the protocol max request size?
     * If so, return an error.
     */

    if (numWords + LENOF (pexOCRequestHeader) > MAX_REQUEST_SIZE)
        return (0);


    /*
     * If possible add the OC to a ROC or StoreElements request,
     * otherwise start a new request.
     */
    
    PEXGetDisplayInfo (display, pexDisplayInfo);
    LockDisplay (display);

    currentReq = (XBufferFlushed (display)) ? 
	(NULL) : ((pexOCRequestHeader *) (display->last_req));
    
    if (currentReq == NULL ||
	pexDisplayInfo->lastReqNum != display->request ||
	pexDisplayInfo->lastResID != resource_id ||
	pexDisplayInfo->lastReqType != req_type ||
	req_type == PEXOCRenderSingle || req_type == PEXOCStoreSingle ||
	display->synchandler ||
	(LENOF (pexOCRequestHeader) + numWords > WordsLeftInXBuffer (display)))
    {
	PEXGetOCReq (display,
	    sizeof (pexOCRequestHeader) + NUMBYTES (numWords));
	
	pexDisplayInfo->lastResID = resource_id;
	pexDisplayInfo->lastReqType = req_type;
	pexDisplayInfo->lastReqNum = display->request;
	
	currentReq = (pexOCRequestHeader *) (display->bufptr);

	currentReq->extOpcode = pexDisplayInfo->extOpcode;
	currentReq->pexOpcode =
	    (req_type == PEXOCStore || req_type == PEXOCStoreSingle) ?
	    PEXRCStoreElements : PEXRCRenderOutputCommands;
	currentReq->reqLength = LENOF (pexOCRequestHeader) + numWords;
	currentReq->fpFormat = float_format;
	currentReq->target = resource_id;
	currentReq->numCommands = numOCs;

        display->bufptr += sizeof (pexOCRequestHeader);
    }
    else
    {
	currentReq->reqLength += numWords;
	currentReq->numCommands += numOCs;
    }
    
    return (1);
}


void
PEXFinishOCs (display)

INPUT Display	*display;

{
    UnlockDisplay (display);
}


void
_PEXSendBytesToOC (display, numBytes, data) 

INPUT Display		*display;
INPUT int		numBytes;
INPUT char		*data;

{
    PEXDisplayInfo 	*pexDisplayInfo;
    int			mod4bytes;


    /*
     * _XSend will take care of splitting the buffer into chunks
     * small enough to fit in the transport buffer.  _XSend will
     * only copy a multiple of 4 bytes, so we must do some extra
     * work if numBytes % 4 != 0.
     */
	
    if (mod4bytes = numBytes % 4)
    {
	if (mod4bytes > BytesLeftInXBuffer (display))
	    _XFlush (display);

	COPY_SMALL_AREA (data, display->bufptr, mod4bytes);
	display->bufptr += mod4bytes;

	data += mod4bytes;
	numBytes -= mod4bytes;
    }

    _XSend (display, data, numBytes);


    /*
     * Make sure that the next oc starts a new request.
     */
	
    PEXGetDisplayInfo (display, pexDisplayInfo);
    pexDisplayInfo->lastReqNum = -1;
}


#ifdef PEXCopyBytesToOC
#undef PEXCopyBytesToOC
#endif

void
PEXCopyBytesToOC (display, numBytes, data) 

INPUT Display		*display;
INPUT int		numBytes;
INPUT char		*data;

{
    if (numBytes <= BytesLeftInXBuffer (display))
    {
	/*
	 * There is room in the X buffer to do the copy.
	 */

	COPY_AREA (data, display->bufptr, numBytes);
	display->bufptr += numBytes;
    }
    else
    {
	/*
	 * Copying this OC will overflow the transport buffer.  We
	 * can't do a simple bcopy.
	 */

	_PEXSendBytesToOC (display, numBytes, data);
    }
}


/* INTERNAL */

void
_PEXCopyPaddedBytesToOC (display, numBytes, data) 

INPUT Display		*display;
INPUT int		numBytes;
INPUT char		*data;

{
    PEXDisplayInfo 	*pexDisplayInfo;
    int			paddedBytes = PADDED_BYTES (numBytes);


    if (paddedBytes <= BytesLeftInXBuffer (display))
    {
	/*
	 * There is room in the X buffer to do the copy.
	 */

	COPY_AREA (data, display->bufptr, numBytes);
	display->bufptr += paddedBytes;
    }
    else
    {
	/*
	 * Copying this OC will overflow the transport buffer.  Using
	 * _XSend will take care of splitting the buffer into chunks
	 * small enough to fit in the transport buffer.
	 */
	
	_XSend (display, data, numBytes);


	/*
	 * Make sure that the next oc starts a new request.
	 */
	
	PEXGetDisplayInfo (display, pexDisplayInfo);
	pexDisplayInfo->lastReqNum = -1;
    }
}


char *
PEXGetOCAddr (display, numBytes) 

INPUT Display		*display;
INPUT int		numBytes;

{
    PEXDisplayInfo 	*pexDisplayInfo;
    char		*retPtr;


    /*
     * If numBytes is larger than the max allowed size, return error.
     */

    if (numBytes >  PEXGetOCAddrMaxSize (display))
	return (NULL);


    /*
     * If there isn't enough space in the X buffer, flush it
     * and make sure that the next OC starts a new request.
     */

    if (numBytes > BytesLeftInXBuffer (display))
    {
	_XFlush (display);
	PEXGetDisplayInfo (display, pexDisplayInfo);
	pexDisplayInfo->lastReqNum = -1;
    }


    /*
     * Return a pointer to the bytes, and update the display's bufptr.
     */

    retPtr = display->bufptr;
    display->bufptr += numBytes;

    return (retPtr);
}


void
PEXSendOCs (display, resource_id, req_type, float_format,
    oc_count, numBytes, encoded_ocs)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		float_format;
INPUT unsigned long	oc_count;
INPUT unsigned int	numBytes;
INPUT char		*encoded_ocs;

{
    PEXStartOCs (display, resource_id, req_type, float_format,
	oc_count, NUMWORDS (numBytes));

    _PEXCopyPaddedBytesToOC (display, numBytes, encoded_ocs);

    PEXFinishOC (display);
}


void _PEXGenOCBadLengthError (display, resource_id, req_type)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;

{
    PEXDisplayInfo 	*pexDisplayInfo;
    pexOCRequestHeader 	*req;


    /*
     * Generate an OC request with a zero request length.
     */

    LockDisplay (display);

    PEXGetDisplayInfo (display, pexDisplayInfo);
    PEXGetOCReq (display, 0);
    req = (pexOCRequestHeader *) (display->bufptr);

    req->extOpcode = pexDisplayInfo->extOpcode;
    req->pexOpcode =
	(req_type == PEXOCStore || req_type == PEXOCStoreSingle) ?
	PEXRCStoreElements : PEXRCRenderOutputCommands;
    req->reqLength = 0;
    req->fpFormat = pexDisplayInfo->fpFormat;
    req->target = resource_id;
    req->numCommands = 1;


    /*
     * Make sure that the next oc starts a new request.
     */

    pexDisplayInfo->lastReqNum = -1;
    pexDisplayInfo->lastResID = resource_id;
    pexDisplayInfo->lastReqType = req_type;
	
    UnlockDisplay (display);
}


int
PEXGetSizeOCs (float_format, oc_count, oc_data)

INPUT int		float_format;
INPUT int		oc_count;
INPUT PEXOCData		*oc_data;

{
    int		totalSize, i;


    for (i = totalSize = 0; i < oc_count; i++, oc_data++)
    {
	switch (oc_data->oc_type)
	{
	case PEXOCMarkerType:
	case PEXOCLineType:
	case PEXOCATextStyle:
	case PEXOCBFInteriorStyle:
	case PEXOCBFReflectionModel:
	case PEXOCBFSurfaceInterpMethod:
	case PEXOCInteriorStyle:
	case PEXOCPolylineInterpMethod:
	case PEXOCReflectionModel:
	case PEXOCRenderingColorModel:
	case PEXOCSurfaceEdgeType:
	case PEXOCSurfaceInterpMethod:

	    totalSize += sizeof (pexMarkerType);
	    break;

	case PEXOCMarkerColorIndex:
	case PEXOCMarkerBundleIndex:
	case PEXOCTextFontIndex:
	case PEXOCTextColorIndex:
	case PEXOCTextBundleIndex:
	case PEXOCLineColorIndex:
	case PEXOCLineBundleIndex:
	case PEXOCSurfaceColorIndex:
	case PEXOCBFInteriorStyleIndex:
	case PEXOCBFSurfaceColorIndex:
	case PEXOCInteriorBundleIndex:
	case PEXOCInteriorStyleIndex:
	case PEXOCSurfaceEdgeColorIndex:
	case PEXOCEdgeBundleIndex:
	case PEXOCViewIndex:
	case PEXOCDepthCueIndex:
	case PEXOCColorApproxIndex:

	    totalSize += sizeof (pexMarkerColorIndex);
	    break;

	case PEXOCMarkerColor:
	case PEXOCTextColor:
	case PEXOCLineColor:
	case PEXOCSurfaceColor:
	case PEXOCBFSurfaceColor:
	case PEXOCSurfaceEdgeColor:

	    totalSize += (sizeof (pexMarkerColor) +
	        GetColorSize (oc_data->data.SetMarkerColor.color_type));
	    break;

	case PEXOCMarkerScale:
	case PEXOCCharExpansion:
	case PEXOCCharSpacing:
	case PEXOCCharHeight:
	case PEXOCATextHeight:
	case PEXOCLineWidth:
	case PEXOCSurfaceEdgeWidth:

	    totalSize += sizeof (pexMarkerScale);
	    break;

	case PEXOCTextPrecision:
	case PEXOCTextPath:
	case PEXOCATextPath:

	    totalSize += sizeof (pexTextPrecision);
	    break;

	case PEXOCCharUpVector:
	case PEXOCATextUpVector:

	    totalSize += sizeof (pexCharUpVector);
	    break;

	case PEXOCTextAlignment:
	case PEXOCATextAlignment:

	    totalSize += sizeof (pexTextAlignment);
	    break;

	case PEXOCCurveApprox:

	    totalSize += sizeof (pexCurveApproximation);
	    break;

	case PEXOCReflectionAttributes:
	case PEXOCBFReflectionAttributes:

	    totalSize += (sizeof (pexSurfaceReflAttr) + GetColorSize (
                oc_data->data.SetReflectionAttributes.attributes.specular_color.type));
	    break;

	case PEXOCSurfaceApprox:

	    totalSize += sizeof (pexSurfaceApproximation);
	    break;

	case PEXOCFacetCullingMode:

	    totalSize += sizeof (pexCullingMode);
	    break;

	case PEXOCFacetDistinguishFlag:
	case PEXOCSurfaceEdgeFlag:
	case PEXOCModelClipFlag:

	    totalSize += sizeof (pexDistinguishFlag);
	    break;

	case PEXOCPatternSize:

	    totalSize += sizeof (pexPatternSize);
	    break;

	case PEXOCPatternAttributes2D:

	    totalSize += sizeof (pexPatternRefPt);
	    break;

	case PEXOCPatternAttributes:

	    totalSize += sizeof (pexPatternAttr);
	    break;

	case PEXOCIndividualASF:

	    totalSize += sizeof (pexSetAsfValues);
	    break;

	case PEXOCLocalTransform:

	    totalSize += sizeof (pexLocalTransform);
	    break;

	case PEXOCLocalTransform2D:

	    totalSize += sizeof (pexLocalTransform2D);
	    break;

	case PEXOCGlobalTransform:

	    totalSize += sizeof (pexGlobalTransform);
	    break;

	case PEXOCGlobalTransform2D:

	    totalSize += sizeof (pexGlobalTransform2D);
	    break;

	case PEXOCModelClipVolume:

	    totalSize += (sizeof (pexModelClipVolume) +
    	        sizeof (pexHalfSpace) *
	        oc_data->data.SetModelClipVolume.count);
	    break;

	case PEXOCModelClipVolume2D:

	    totalSize += (sizeof (pexModelClipVolume2D) +
    	        sizeof (pexHalfSpace2D) *
	        oc_data->data.SetModelClipVolume2D.count);
	    break;

	case PEXOCRestoreModelClipVolume:

	    totalSize += sizeof (pexRestoreModelClip);
	    break;

	case PEXOCLightSourceState:

	{
    	    int	sizeofEnableList, sizeofDisableList;

    	    sizeofEnableList = sizeof (CARD16) *
	        oc_data->data.SetLightSourceState.enable_count;

    	    sizeofDisableList = sizeof (CARD16) *
	        oc_data->data.SetLightSourceState.disable_count;
	    
	    totalSize += (sizeof (pexLightState) +
	        PADDED_BYTES (sizeofEnableList) +
	        PADDED_BYTES (sizeofDisableList));
	    break;
	}

	case PEXOCPickID:
	case PEXOCHLHSRID:

	    totalSize += sizeof (pexPickId);
	    break;

	case PEXOCParaSurfCharacteristics:

	{
	    int	pscDataSize = 0;

	    switch (oc_data->data.SetParaSurfCharacteristics.psc_type)
	    {
	    case PEXPSCIsoCurves:
	        pscDataSize = sizeof (PEXPSCIsoparametricCurves);
	        break;

	    case PEXPSCMCLevelCurves:
	    case PEXPSCWCLevelCurves:
	        pscDataSize = sizeof (pexPSC_LevelCurves) + sizeof (float) *
	    	oc_data->data.SetParaSurfCharacteristics.characteristics.level_curves.count;
	        break;

	    default:
	        break;
	    }

	    totalSize += (sizeof (pexParaSurfCharacteristics) + pscDataSize);
	    break;
  	}

	case PEXOCAddToNameSet:
	case PEXOCRemoveFromNameSet:

	    totalSize += (sizeof (pexAddToNameSet) + 
	        oc_data->data.AddToNameSet.count * sizeof (pexName));
	    break;

	case PEXOCExecuteStructure:

	    totalSize += sizeof (pexExecuteStructure);
	    break;

	case PEXOCLabel:

	    totalSize += sizeof (pexLabel);
	    break;

	case PEXOCApplicationData:

	    totalSize += (sizeof (pexApplicationData) +
	        PADDED_BYTES (oc_data->data.ApplicationData.length));
	    break;

	case PEXOCGSE:

	    totalSize += (sizeof (pexGse) +
	        PADDED_BYTES (oc_data->data.GSE.length));
	    break;

	case PEXOCMarkers:
	case PEXOCPolyline:

	    totalSize += (sizeof (pexMarker) +
	        oc_data->data.Markers.count * sizeof (pexCoord3D));
	    break;

	case PEXOCMarkers2D:
	case PEXOCPolyline2D:

	    totalSize += (sizeof (pexMarker2D) +
	        oc_data->data.Markers2D.count * sizeof (pexCoord2D));
	    break;

	case PEXOCText:

	{
	    /* Text is always mono encoded */

	    PEXEncodedTextData  	*nextString;
	    int 			lenofStrings, i;

	    GetStringsLength (oc_data->data.EncodedText.count,
	        oc_data->data.EncodedText.encoded_text, lenofStrings)

	    totalSize += (sizeof (pexText) + NUMBYTES (lenofStrings));
	    break;
	}

	case PEXOCText2D:

	{
	    /* Text is always mono encoded */

	    PEXEncodedTextData  	*nextString;
	    int 			lenofStrings, i;

	    GetStringsLength (oc_data->data.EncodedText2D.count,
	        oc_data->data.EncodedText2D.encoded_text, lenofStrings)

	    totalSize += (sizeof (pexText2D) + NUMBYTES (lenofStrings));
	    break;
	}

	case PEXOCAnnotationText:

	{
	    /* Anno Text is always mono encoded */

	    PEXEncodedTextData  	*nextString;
	    int 			lenofStrings, i;

	    GetStringsLength (oc_data->data.EncodedAnnoText.count,
	        oc_data->data.EncodedAnnoText.encoded_text, lenofStrings)

	    totalSize += (sizeof (pexAnnotationText) + NUMBYTES (lenofStrings));
	    break;
	}

	case PEXOCAnnotationText2D:

	{
	    /* Anno Text is always mono encoded */

	    PEXEncodedTextData  	*nextString;
	    int 			lenofStrings, i;

	    GetStringsLength (oc_data->data.EncodedAnnoText2D.count,
	        oc_data->data.EncodedAnnoText2D.encoded_text, lenofStrings)

	    totalSize += (sizeof (pexAnnotationText2D) +
		NUMBYTES (lenofStrings));
	    break;
	}

	case PEXOCPolylineSetWithData:

	{
	    int numPoints, lenofVertex, i;

	    for (i = 0, numPoints = 0;
	         i < oc_data->data.PolylineSetWithData.count; i++)
	        numPoints +=
	        oc_data->data.PolylineSetWithData.vertex_lists[i].count;

	    lenofVertex = LENOF (pexCoord3D) +
	        ((oc_data->data.PolylineSetWithData.vertex_attributes &
	         PEXGAColor) ? GetColorLength (
	         oc_data->data.PolylineSetWithData.color_type) : 0);

	    totalSize += (sizeof (pexPolylineSet) + NUMBYTES (
	        oc_data->data.PolylineSetWithData.count +
	        numPoints * lenofVertex));
	    break;
	}

	case PEXOCNURBCurve:

	{
	    int sizeofVertexList, sizeofKnotList;

    	    sizeofVertexList =
	        oc_data->data.NURBCurve.count *
	        ((oc_data->data.NURBCurve.rationality == PEXRational) ?
	        sizeof (pexCoord4D) : sizeof (pexCoord3D));

	    sizeofKnotList = NUMBYTES (
	        oc_data->data.NURBCurve.order +
	        oc_data->data.NURBCurve.count);

	    totalSize += (sizeof (pexNurbCurve) +
	        sizeofVertexList + sizeofKnotList);
	    break;
	}

	case PEXOCFillArea:

	    totalSize += (sizeof (pexFillArea) +
	        oc_data->data.FillArea.count * sizeof (pexCoord3D));
	    break;

	case PEXOCFillArea2D:

	    totalSize += (sizeof (pexFillArea2D) +
	        oc_data->data.FillArea2D.count * sizeof (pexCoord2D));
	    break;

	case PEXOCFillAreaWithData:

	{
	    int lenofColor, lenofFacet, lenofVertex;

    	    lenofColor =
	        GetColorLength (oc_data->data.FillAreaWithData.color_type);

	    lenofFacet =
	        GetFacetDataLength (
	    	oc_data->data.FillAreaWithData.facet_attributes,
	    	lenofColor); 

	    lenofVertex =
	        GetVertexWithDataLength (
	    	oc_data->data.FillAreaWithData.vertex_attributes,
	    	lenofColor);

	    totalSize += (sizeof (pexExtFillArea) +
	        NUMBYTES (lenofFacet + 1 +
	        oc_data->data.FillAreaWithData.count * lenofVertex));
	    break;
	}

	case PEXOCFillAreaSet:

	{
	    int numPoints, i;

	    for (i = 0, numPoints = 0;
	        i < oc_data->data.FillAreaSet.count; i++)
	        numPoints +=
	        oc_data->data.FillAreaSet.point_lists[i].count;

	    totalSize += (sizeof (pexFillAreaSet) +
	        NUMBYTES (oc_data->data.FillAreaSet.count) +
	        numPoints * sizeof (pexCoord3D));
	    break;
	}

	case PEXOCFillAreaSet2D:

	{
	    int numPoints, i;

	    for (i = 0, numPoints = 0;
	        i < oc_data->data.FillAreaSet2D.count; i++)
	        numPoints +=
	        oc_data->data.FillAreaSet2D.point_lists[i].count;

	    totalSize += (sizeof (pexFillAreaSet2D) +
	        NUMBYTES (oc_data->data.FillAreaSet2D.count) +
	        numPoints * sizeof (pexCoord2D));
	    break;
	}

	case PEXOCFillAreaSetWithData:

	{
	    int lenofColor, lenofFacet, lenofVertex;
	    int numVertices, i;

    	    lenofColor = GetColorLength (
	        oc_data->data.FillAreaSetWithData.color_type);

	    lenofFacet =
	        GetFacetDataLength (
	        oc_data->data.FillAreaSetWithData.facet_attributes,
	        lenofColor); 

	    lenofVertex =
	        GetVertexWithDataLength (
	        oc_data->data.FillAreaSetWithData.vertex_attributes,
	        lenofColor);

	    if (oc_data->data.FillAreaSetWithData.vertex_attributes &
	        PEXGAEdges)
	        lenofVertex++;         /* edge switch is CARD32 */

	    for (i = 0, numVertices = 0;
	        i < oc_data->data.FillAreaSetWithData.count; i++)
	        numVertices +=
	        oc_data->data.FillAreaSetWithData.vertex_lists[i].count;

	    totalSize += (sizeof (pexExtFillAreaSet) +
	        NUMBYTES (lenofFacet +
	        oc_data->data.FillAreaSetWithData.count +
	        numVertices * lenofVertex));
	    break;
	}

	case PEXOCTriangleStrip:

	{
	    int lenofColor, lenofFacetList, lenofVertexList;

    	    lenofColor =
	        GetColorLength (oc_data->data.TriangleStrip.color_type);

	    lenofFacetList = (oc_data->data.TriangleStrip.count - 2) *
	        GetFacetDataLength (
	        oc_data->data.TriangleStrip.facet_attributes, lenofColor);

	    lenofVertexList = oc_data->data.TriangleStrip.count *
	        GetVertexWithDataLength (
	        oc_data->data.TriangleStrip.vertex_attributes, lenofColor);

	    totalSize += (sizeof (pexTriangleStrip) +
	        NUMBYTES (lenofFacetList + lenofVertexList));
	    break;
	}

	case PEXOCQuadrilateralMesh:

	{
	    int lenofColor, lenofFacetList, lenofVertexList;

    	    lenofColor =
	        GetColorLength (oc_data->data.QuadrilateralMesh.color_type);

	    lenofFacetList =
	        (oc_data->data.QuadrilateralMesh.row_count - 1) *
	        (oc_data->data.QuadrilateralMesh.col_count - 1) *
	        GetFacetDataLength (
	            oc_data->data.QuadrilateralMesh.facet_attributes,
	    	lenofColor);

	    lenofVertexList =
	        oc_data->data.QuadrilateralMesh.row_count *
	        oc_data->data.QuadrilateralMesh.col_count *
	        GetVertexWithDataLength (
	            oc_data->data.QuadrilateralMesh.vertex_attributes,
	            lenofColor);

	    totalSize += (sizeof (pexQuadrilateralMesh) +
	        NUMBYTES (lenofFacetList + lenofVertexList));
	    break;
	}

	case PEXOCSetOfFillAreaSets:

	{
	    PEXConnectivityData *pConnectivity;
	    int 	lenofColor, lenofFacet, lenofVertex;
	    int 	sizeofEdge, sofaLength;
	    int 	numContours, numFillAreaSets;
	    int		numIndices, numVertices, i;

	    numFillAreaSets = oc_data->data.SetOfFillAreaSets.set_count;
	    numIndices = oc_data->data.SetOfFillAreaSets.index_count;
	    numVertices = oc_data->data.SetOfFillAreaSets.vertex_count;

	    pConnectivity = oc_data->data.SetOfFillAreaSets.connectivity;
	    numContours = 0;
	    for (i = 0; i < numFillAreaSets; i++, pConnectivity++)
	        numContours += pConnectivity->count;

	    lenofColor = GetColorLength (
	        oc_data->data.SetOfFillAreaSets.color_type);
	    lenofFacet = GetFacetDataLength (
 	        oc_data->data.SetOfFillAreaSets.facet_attributes,
	        lenofColor); 
	    lenofVertex = GetVertexWithDataLength (
	        oc_data->data.SetOfFillAreaSets.vertex_attributes,
	        lenofColor);

	    sizeofEdge = oc_data->data.SetOfFillAreaSets.edge_attributes ?
		sizeof (CARD8) : 0;

	    sofaLength = (lenofFacet * numFillAreaSets) +
	        (lenofVertex * numVertices) + 
	        NUMWORDS (sizeofEdge * numIndices) +
	        NUMWORDS (sizeof (CARD16) *
	        (numFillAreaSets + numContours + numIndices));

	    totalSize += (sizeof (pexSOFAS) + NUMBYTES (sofaLength));
	    break;
	}

	case PEXOCNURBSurface:
	{
	    PEXListOfTrimCurve *ptrimLoop;
	    PEXTrimCurve	   *ptrimCurve;
	    int 	numMPoints, numNPoints, numTrimLoops;
	    int 	uorder, vorder;
	    int 	lenofVertexList, lenofUKnotList, lenofVKnotList;
	    int 	lenofTrimData, count, i;

	    numMPoints = oc_data->data.NURBSurface.col_count;
	    numNPoints = oc_data->data.NURBSurface.row_count;
	    numTrimLoops = oc_data->data.NURBSurface.curve_count;
	    uorder = oc_data->data.NURBSurface.uorder;
	    vorder = oc_data->data.NURBSurface.vorder;

	    lenofVertexList = numMPoints * numNPoints *
                ((oc_data->data.NURBSurface.rationality == PEXRational)
	        ? LENOF (pexCoord4D) : LENOF (pexCoord3D));
	    lenofUKnotList = uorder + numMPoints;
	    lenofVKnotList = vorder + numNPoints;

	    lenofTrimData = numTrimLoops * LENOF (CARD32);

	    ptrimLoop = oc_data->data.NURBSurface.trim_curves;
	    for (i = 0; i < numTrimLoops; i++, ptrimLoop++)
	    {
	        ptrimCurve = ptrimLoop->curves;
	        count = ptrimLoop->count;
	    
	        while (count--)
	        {
	    	lenofTrimData += (LENOF (pexTrimCurve) +
	    	    ptrimCurve->count + ptrimCurve->order +
	                ptrimCurve->count *
	                (ptrimCurve->rationality == PEXRational ?
	                LENOF (pexCoord3D) : LENOF (pexCoord2D)));
	            ptrimCurve++;
	        }
	    }

	    totalSize += (sizeof (pexNurbSurface) +
	        NUMBYTES (lenofUKnotList + lenofVKnotList +
	        lenofVertexList + lenofTrimData));
	    break;
	}

	case PEXOCCellArray:

	{
	    int bytes;

	    bytes = oc_data->data.CellArray.col_count *
	        oc_data->data.CellArray.row_count * sizeof (pexTableIndex);
	    totalSize += (sizeof (pexCellArray) + PADDED_BYTES (bytes));
	    break;
	}

	case PEXOCCellArray2D:

	{
	    int bytes;

	    bytes = oc_data->data.CellArray2D.col_count *
	        oc_data->data.CellArray2D.row_count *
	        sizeof (pexTableIndex);
	    totalSize += (sizeof (pexCellArray2D) + PADDED_BYTES (bytes));
	    break;
	}

	case PEXOCExtendedCellArray:

	{
	    int lenofColorList;

	    lenofColorList = oc_data->data.ExtendedCellArray.col_count *
	        oc_data->data.ExtendedCellArray.row_count * GetColorLength (
	        oc_data->data.ExtendedCellArray.color_type);

	    totalSize += (sizeof (pexExtCellArray) +
	        NUMBYTES (lenofColorList));
	    break;
	}

	case PEXOCGDP:

	    totalSize += (sizeof (pexGdp) +
	        oc_data->data.GDP.count * sizeof (pexCoord3D) +
	        PADDED_BYTES (oc_data->data.GDP.length));
	    break;

	case PEXOCGDP2D:

	    totalSize += (sizeof (pexGdp2D) +
	        oc_data->data.GDP2D.count * sizeof (pexCoord2D) +
	        PADDED_BYTES (oc_data->data.GDP2D.length));
	    break;

	case PEXOCNoop:

	    totalSize += sizeof (pexNoop);
	    break;

	default:
	    break;
	}
    }

#ifdef DEBUG
    if (totalSize % 4)
    {
	printf ("PEXlib WARNING : Internal error in PEXGetSizeOCs :\n");
	printf ("Memory allocated is not word aligned.\n");
    }
#endif

    return (totalSize);
}


unsigned long
PEXCountOCs (float_format, length, encoded_ocs)

INPUT int		float_format;
INPUT unsigned long     length;
INPUT char		*encoded_ocs;

{
    char		*ptr = encoded_ocs;
    unsigned long	oc_count = 0;
    int			totalSize = 0;
    pexElementInfo	*elemInfo;


    /*
     * Keep parsing the data until the end of the buffer is reached.
     * Increment the oc count as we go along.
     */

    while (totalSize < length)
    {
	elemInfo = (pexElementInfo *) ptr;

	switch (elemInfo->elementType)
	{
	case PEXOCMarkerType:
	case PEXOCLineType:
	case PEXOCATextStyle:
	case PEXOCBFInteriorStyle:
	case PEXOCBFReflectionModel:
	case PEXOCBFSurfaceInterpMethod:
	case PEXOCInteriorStyle:
	case PEXOCPolylineInterpMethod:
	case PEXOCReflectionModel:
	case PEXOCRenderingColorModel:
	case PEXOCSurfaceEdgeType:
	case PEXOCSurfaceInterpMethod:

	    ptr += sizeof (pexMarkerType);
	    break;

	case PEXOCMarkerColorIndex:
	case PEXOCMarkerBundleIndex:
	case PEXOCTextFontIndex:
	case PEXOCTextColorIndex:
	case PEXOCTextBundleIndex:
	case PEXOCLineColorIndex:
	case PEXOCLineBundleIndex:
	case PEXOCSurfaceColorIndex:
	case PEXOCBFInteriorStyleIndex:
	case PEXOCBFSurfaceColorIndex:
	case PEXOCInteriorBundleIndex:
	case PEXOCInteriorStyleIndex:
	case PEXOCSurfaceEdgeColorIndex:
	case PEXOCEdgeBundleIndex:
	case PEXOCViewIndex:
	case PEXOCDepthCueIndex:
	case PEXOCColorApproxIndex:

	    ptr += sizeof (pexMarkerColorIndex);
	    break;

	case PEXOCMarkerColor:
	case PEXOCTextColor:
	case PEXOCLineColor:
	case PEXOCSurfaceColor:
	case PEXOCBFSurfaceColor:
	case PEXOCSurfaceEdgeColor:

	{
	    pexMarkerColor *oc = (pexMarkerColor *) ptr;
    
	    ptr += (sizeof (pexMarkerColor) +
		GetColorSize (oc->colorSpec.colorType));
	    break;
	}

	case PEXOCMarkerScale:
	case PEXOCCharExpansion:
	case PEXOCCharSpacing:
	case PEXOCCharHeight:
	case PEXOCATextHeight:
	case PEXOCLineWidth:
	case PEXOCSurfaceEdgeWidth:

	    ptr += sizeof (pexMarkerScale);
	    break;

	case PEXOCTextPrecision:
	case PEXOCTextPath:
	case PEXOCATextPath:

	    ptr += sizeof (pexTextPrecision);
	    break;

	case PEXOCCharUpVector:
	case PEXOCATextUpVector:

	    ptr += sizeof (pexCharUpVector);
	    break;

	case PEXOCTextAlignment:
	case PEXOCATextAlignment:

	    ptr += sizeof (pexTextAlignment);
	    break;

	case PEXOCCurveApprox:

	    ptr += sizeof (pexCurveApproximation);
	    break;

	case PEXOCReflectionAttributes:
	case PEXOCBFReflectionAttributes:

	{
	    pexSurfaceReflAttr *oc = (pexSurfaceReflAttr *) ptr;
    
	    ptr += (sizeof (pexSurfaceReflAttr) +
		GetColorSize (oc->reflectionAttr.specularColor.colorType));
	    break;
	}

	case PEXOCSurfaceApprox:

	    ptr += sizeof (pexSurfaceApproximation);
	    break;

	case PEXOCFacetCullingMode:

	    ptr += sizeof (pexCullingMode);
	    break;

	case PEXOCFacetDistinguishFlag:
	case PEXOCSurfaceEdgeFlag:
	case PEXOCModelClipFlag:

	    ptr += sizeof (pexDistinguishFlag);
	    break;

	case PEXOCPatternSize:

	    ptr += sizeof (pexPatternSize);
	    break;

	case PEXOCPatternAttributes2D:

	    ptr += sizeof (pexPatternRefPt);
	    break;

	case PEXOCPatternAttributes:

	    ptr += sizeof (pexPatternAttr);
	    break;

	case PEXOCIndividualASF:

	    ptr += sizeof (pexSetAsfValues);
	    break;

	case PEXOCLocalTransform:

	    ptr += sizeof (pexLocalTransform);
	    break;

	case PEXOCLocalTransform2D:

	    ptr += sizeof (pexLocalTransform2D);
	    break;

	case PEXOCGlobalTransform:

	    ptr += sizeof (pexGlobalTransform);
	    break;

	case PEXOCGlobalTransform2D:

	    ptr += sizeof (pexGlobalTransform2D);
	    break;

	case PEXOCModelClipVolume:

	{
	    pexModelClipVolume 	*oc = (pexModelClipVolume *) ptr;
    
	    ptr += (sizeof (pexModelClipVolume) +
		oc->numHalfSpaces * sizeof (pexHalfSpace));
	    break;
	}

	case PEXOCModelClipVolume2D:

	{
	    pexModelClipVolume2D *oc = (pexModelClipVolume2D *) ptr;
    
	    ptr += (sizeof (pexModelClipVolume2D) +
		oc->numHalfSpaces * sizeof (pexHalfSpace2D));
	    break;
	}

	case PEXOCRestoreModelClipVolume:

	    ptr += sizeof (pexRestoreModelClip);
	    break;

	case PEXOCLightSourceState:

	{
	    pexLightState 	*oc = (pexLightState *) ptr;
	    int			size;
    
	    size = oc->numEnable * sizeof (PEXTableIndex);
	    ptr += (sizeof (pexLightState) + PADDED_BYTES (size));
    
	    size = oc->numDisable * sizeof (PEXTableIndex);
	    ptr += PADDED_BYTES (size);
	    break;
	}

	case PEXOCPickID:
	case PEXOCHLHSRID:

	    ptr += sizeof (pexPickId);
	    break;

	case PEXOCParaSurfCharacteristics:

	{
	    pexParaSurfCharacteristics *oc = (pexParaSurfCharacteristics *) ptr;

	    switch (oc->characteristics)
	    {
	    case PEXPSCIsoCurves:
		ptr = (char *) (oc + 1) + sizeof (pexPSC_IsoparametricCurves);
		break;
	
	    case PEXPSCMCLevelCurves:
	    case PEXPSCWCLevelCurves:
	    {
		pexPSC_LevelCurves *level = (pexPSC_LevelCurves *) (oc + 1);

		ptr = (char *) (level + 1) +
		    sizeof (float) * level->numberIntersections;
		break;
	    }
	
	    default:
		ptr = (char *) (oc + 1) + PADDED_BYTES (oc->length);
		break;
	    }

	    break;
	}

	case PEXOCAddToNameSet:
	case PEXOCRemoveFromNameSet:

	    ptr += (sizeof (pexAddToNameSet) +
		(elemInfo->length - 1) * sizeof (PEXName));
	    break;

	case PEXOCExecuteStructure:

	    ptr += sizeof (pexExecuteStructure);
	    break;

	case PEXOCLabel:

	    ptr += sizeof (pexLabel);
	    break;

	case PEXOCApplicationData:

	{
	    pexApplicationData *oc = (pexApplicationData *) ptr;

	    ptr += (sizeof (pexApplicationData) +
		PADDED_BYTES (oc->numElements));
	    break;
	}

	case PEXOCGSE:

	{
	    pexGse *oc = (pexGse *) ptr;

	    ptr += (sizeof (pexGse) + PADDED_BYTES (oc->numElements));
	    break;
	}

	case PEXOCMarkers:
	case PEXOCPolyline:

	    ptr += (sizeof (pexMarker) + sizeof (pexCoord3D) *
	    	(sizeof (CARD32) * (elemInfo->length-1)) / sizeof (pexCoord3D));
	    break;

	case PEXOCMarkers2D:
	case PEXOCPolyline2D:

	    ptr += (sizeof (pexMarker2D) + sizeof (pexCoord2D) *
	    	(sizeof (CARD32) * (elemInfo->length-1)) / sizeof (pexCoord2D));
	    break;

	case PEXOCText:

	{
	    /* Text is always mono encoded */

	    pexText 		*oc = (pexText *) ptr;
	    pexMonoEncoding	*enc;
	    int			size, i;

	    enc = (pexMonoEncoding *) (oc + 1);

	    for (i = 0; i < (int) oc->numEncodings; i++)
	    {
		if (enc->characterSetWidth == PEXCSLong)
		    size = enc->numChars * sizeof (long);
		else if (enc->characterSetWidth == PEXCSShort)
		    size = enc->numChars * sizeof (short);
		else /* enc->characterSetWidth == PEXCSByte) */
		    size = enc->numChars;

		enc = (pexMonoEncoding *) ((char *) enc +
	            sizeof (pexMonoEncoding) + PADDED_BYTES (size));
	    }

	    ptr = (char *) enc;
	    break;
	}

	case PEXOCText2D:

	{
	    /* Text is always mono encoded */

	    pexText2D 		*oc = (pexText2D *) ptr;
	    pexMonoEncoding	*enc;
	    int			size, i;

	    enc = (pexMonoEncoding *) (oc + 1);

	    for (i = 0; i < (int) oc->numEncodings; i++)
	    {
		if (enc->characterSetWidth == PEXCSLong)
		    size = enc->numChars * sizeof (long);
		else if (enc->characterSetWidth == PEXCSShort)
		    size = enc->numChars * sizeof (short);
		else /* enc->characterSetWidth == PEXCSByte) */
		    size = enc->numChars;

		enc = (pexMonoEncoding *) ((char *) enc +
	            sizeof (pexMonoEncoding) + PADDED_BYTES (size));
	    }

	    ptr = (char *) enc;
	    break;
	}

	case PEXOCAnnotationText:

	{
	    /* Anno Text is always mono encoded */

	    pexAnnotationText 	*oc = (pexAnnotationText *) ptr;
	    pexMonoEncoding	*enc;
	    int			size, i;

	    enc = (pexMonoEncoding *) (oc + 1);

	    for (i = 0; i < (int) oc->numEncodings; i++)
	    {
		if (enc->characterSetWidth == PEXCSLong)
		    size = enc->numChars * sizeof (long);
		else if (enc->characterSetWidth == PEXCSShort)
		    size = enc->numChars * sizeof (short);
		else /* enc->characterSetWidth == PEXCSByte) */
		    size = enc->numChars;

		enc = (pexMonoEncoding *) ((char *) enc +
	            sizeof (pexMonoEncoding) + PADDED_BYTES (size));
	    }

	    ptr = (char *) enc;
	    break;
	}

	case PEXOCAnnotationText2D:

	{
	    /* Anno Text is always mono encoded */

	    pexAnnotationText2D	*oc = (pexAnnotationText2D *) ptr;
	    pexMonoEncoding	*enc;
	    int			size, i;

	    enc = (pexMonoEncoding *) (oc + 1);

	    for (i = 0; i < (int) oc->numEncodings; i++)
	    {
		if (enc->characterSetWidth == PEXCSLong)
		    size = enc->numChars * sizeof (long);
		else if (enc->characterSetWidth == PEXCSShort)
		    size = enc->numChars * sizeof (short);
		else /* enc->characterSetWidth == PEXCSByte) */
		    size = enc->numChars;

		enc = (pexMonoEncoding *) ((char *) enc +
	            sizeof (pexMonoEncoding) + PADDED_BYTES (size));
	    }

	    ptr = (char *) enc;
	    break;
	}

	case PEXOCPolylineSetWithData:

	{
	    pexPolylineSet 	*oc = (pexPolylineSet *) ptr;
	    int			lenofVertex, count, i;

	    lenofVertex = LENOF (pexCoord3D) +
		((oc->vertexAttribs & PEXGAColor) ?
		GetColorLength (oc->colorType) : 0); 

	    ptr = (char *) (oc + 1);

	    for (i = 0; i < oc->numLists; i++)
	    {
		count = *((CARD32 *) ptr);
		ptr += (sizeof (CARD32) + NUMBYTES (count * lenofVertex));
	    }
	    break;
	}

	case PEXOCNURBCurve:

	{
	    pexNurbCurve	*oc = (pexNurbCurve *) ptr;

	    ptr += (sizeof (pexNurbCurve) + oc->numKnots * sizeof (float) +
	        (oc->numPoints * ((oc->coordType == PEXRational) ?
		sizeof (pexCoord4D) : sizeof (pexCoord3D))));
	    break;
	}

	case PEXOCFillArea:

	{
	    int 		count;
    
	    count = (sizeof (CARD32) * (elemInfo->length - 2)) /
		sizeof (pexCoord3D);
    
	    ptr += (sizeof (pexFillArea) + count * sizeof (pexCoord3D));
	    break;
	}

	case PEXOCFillArea2D:

	{
	    int 		count;
    
	    count = (sizeof (CARD32) * (elemInfo->length - 2)) /
		sizeof (pexCoord2D);
    
	    ptr += (sizeof (pexFillArea2D) + count * sizeof (pexCoord2D));
	    break;
	}

	case PEXOCFillAreaWithData:

	{
	    pexExtFillArea 	*oc = (pexExtFillArea *) ptr;
	    int			lenofFacetData;
	    int			lenofVertex;
	    int			lenofColor, count;
    
	    lenofColor = GetColorLength (oc->colorType);
	    lenofFacetData = GetFacetDataLength (oc->facetAttribs, lenofColor); 
	    lenofVertex = GetVertexWithDataLength (
		oc->vertexAttribs, lenofColor);

	    ptr = (char *) (oc + 1);

	    if (oc->facetAttribs)
		ptr += NUMBYTES (lenofFacetData);

	    count = *((CARD32 *) ptr);
	    ptr += (sizeof (CARD32) + count * NUMBYTES (lenofVertex));
	    break;
	}

	case PEXOCFillAreaSet:

	{
	    pexFillAreaSet 	*oc = (pexFillAreaSet *) ptr;
	    int			count, i;

	    ptr = (char *) (oc + 1);

	    for (i = 0; i < oc->numLists; i++)
	    {
		count = *((CARD32 *) ptr);
		ptr += (sizeof (CARD32) + count * sizeof (pexCoord3D));
	    }
	    break;
	}

	case PEXOCFillAreaSet2D:

	{
	    pexFillAreaSet2D 	*oc = (pexFillAreaSet2D *) ptr;
	    int			count, i;

	    ptr = (char *) (oc + 1);

	    for (i = 0; i < oc->numLists; i++)
	    {
		count = *((CARD32 *) ptr);
		ptr += (sizeof (CARD32) + count * sizeof (pexCoord2D));
	    }
	    break;
	}

	case PEXOCFillAreaSetWithData:

	{
	    pexExtFillAreaSet 	*oc = (pexExtFillAreaSet *) ptr;
	    int			lenofFacetData;
	    int			lenofVertex;
	    int			lenofColor, count, i;

	    lenofColor = GetColorLength (oc->colorType);
	    lenofFacetData = GetFacetDataLength (oc->facetAttribs, lenofColor); 
	    lenofVertex = GetVertexWithDataLength (
		oc->vertexAttribs, lenofColor);
    
	    if (oc->vertexAttribs & PEXGAEdges)
		lenofVertex++; 			/* edge switch is CARD32 */

	    ptr = (char *) (oc + 1);

	    if (oc->facetAttribs)
		ptr += NUMBYTES (lenofFacetData);

	    for (i = 0; i < oc->numLists; i++)
	    {
		count = *((CARD32 *) ptr);
		ptr += (sizeof (CARD32) + count * NUMBYTES (lenofVertex));
	    }
	    break;
	}

	case PEXOCTriangleStrip:

	{
	    pexTriangleStrip 	*oc = (pexTriangleStrip *) ptr;
	    int			lenofColor;
	    int			lenofFacetDataList;
	    int			lenofVertexList;

	    lenofColor = GetColorLength (oc->colorType);
	    lenofFacetDataList = (oc->numVertices - 2) *
		GetFacetDataLength (oc->facetAttribs, lenofColor); 
	    lenofVertexList = oc->numVertices *
		GetVertexWithDataLength (oc->vertexAttribs, lenofColor);

	    ptr = (char *) (oc + 1);

	    if (oc->facetAttribs)
		ptr += NUMBYTES (lenofFacetDataList);

	    ptr += NUMBYTES (lenofVertexList);
	    break;
	}

	case PEXOCQuadrilateralMesh:

	{
	    pexQuadrilateralMesh 	*oc = (pexQuadrilateralMesh *) ptr;
	    int				lenofColor;
	    int				lenofFacetDataList;
	    int				lenofVertexList;

	    lenofColor = GetColorLength (oc->colorType);
	    lenofFacetDataList = ((oc->mPts - 1) * (oc->nPts - 1)) *
		GetFacetDataLength (oc->facetAttribs, lenofColor); 
	    lenofVertexList = oc->mPts * oc->nPts *
		GetVertexWithDataLength (oc->vertexAttribs, lenofColor);

	    ptr = (char *) (oc + 1);

	    if (oc->facetAttribs)
		ptr += NUMBYTES (lenofFacetDataList);

	    ptr += NUMBYTES (lenofVertexList);
	    break;
	}

	case PEXOCSetOfFillAreaSets:

	{
	    pexSOFAS		*oc = (pexSOFAS *) ptr;
	    int 		lenofColor;
	    int 		lenofFacet;
	    int 		lenofVertex;
	    int			count, scount, cbytes, i, j;

	    lenofColor = GetColorLength (oc->colorType);
	    lenofFacet = GetFacetDataLength (oc->FAS_Attributes, lenofColor); 
	    lenofVertex = GetVertexWithDataLength (
		oc->vertexAttributes, lenofColor);

	    ptr = (char *) (oc + 1);

	    if (oc->FAS_Attributes)
		ptr += (NUMBYTES (lenofFacet) * oc->numFAS);

	    ptr += (NUMBYTES (lenofVertex) * oc->numVertices);

	    if (oc->edgeAttributes)
		ptr += PADDED_BYTES (oc->numEdges * sizeof (CARD8));
	
	    for (i = 0; i < (int) oc->numFAS; i++)
	    {
		count = *((CARD16 *) ptr);
		ptr += sizeof (CARD16);

		for (j = 0; j < count; j++)
		{
		    scount = *((CARD16 *) ptr);
		    ptr += (sizeof (CARD16) + (scount * sizeof (CARD16)));
		}
	    }
	
	    cbytes = sizeof (CARD16) *
		(oc->numFAS + oc->numContours + oc->numEdges);

	    ptr += PAD (cbytes);
	    break;
	}

	case PEXOCNURBSurface:

	{
	    pexNurbSurface	*oc = (pexNurbSurface *) ptr;
	    int			sizeofVertexList;
	    int			sizeofUKnotList;
	    int			sizeofVKnotList;
	    pexTrimCurve	*trim;
	    int			count, i, j;

	    sizeofVertexList = oc->mPts * oc->nPts *
		((oc->type == PEXRational) ?
		sizeof (pexCoord4D) : sizeof (pexCoord3D));
	    sizeofUKnotList = NUMBYTES (oc->uOrder + oc->mPts);
	    sizeofVKnotList = NUMBYTES (oc->vOrder + oc->nPts);

	    ptr += (sizeof (pexNurbSurface) +
		sizeofUKnotList + sizeofVKnotList + sizeofVertexList);

	    for (i = 0; i < oc->numLists; i++)
	    {
		count = *((CARD32 *) ptr);
		ptr += sizeof (CARD32);

		for (j = 0; j < count; j++)
		{
		    trim = (pexTrimCurve *) ptr;
		    ptr += (sizeof (pexTrimCurve) +
		        NUMBYTES (trim->order + trim->numCoord) +
		        trim->numCoord * ((trim->type == PEXRational) ?
		        sizeof (pexCoord3D) : sizeof (pexCoord2D)));
		}
	    }
	    break;
	}

	case PEXOCCellArray:

	{
	    pexCellArray	*oc = (pexCellArray *) ptr;
	    int			size;

	    size = oc->dx * oc->dy * sizeof (pexTableIndex);
	    ptr += (sizeof (pexCellArray) + PADDED_BYTES (size));
	    break;
	}

	case PEXOCCellArray2D:

	{
	    pexCellArray2D	*oc = (pexCellArray2D *) ptr;
	    int			size;

	    size = oc->dx * oc->dy * sizeof (pexTableIndex);
	    ptr += (sizeof (pexCellArray2D) + PADDED_BYTES (size));
	    break;
	}

	case PEXOCExtendedCellArray:

	{
	    pexExtCellArray	*oc = (pexExtCellArray *) ptr;

	    ptr += (sizeof (pexExtCellArray) + 
		oc->dx * oc->dy * NUMBYTES (GetColorLength (oc->colorType)));
	    break;
	}

	case PEXOCGDP:

	{
	    pexGdp	*oc = (pexGdp *) ptr;

	    ptr += (sizeof (pexGdp) + oc->numPoints * sizeof (pexCoord3D) +
	        PADDED_BYTES (oc->numBytes));
	    break;
	}

	case PEXOCGDP2D:

	{
	    pexGdp2D	*oc = (pexGdp2D *) ptr;

	    ptr += (sizeof (pexGdp2D) + oc->numPoints * sizeof (pexCoord2D) +
	        PADDED_BYTES (oc->numBytes));
	    break;
	}

	case PEXOCNoop:

	    ptr += sizeof (pexNoop);
	    break;

	default:
	    break;
	}

	totalSize += (ptr - (char *) elemInfo);
	oc_count++;
    }

#ifdef DEBUG
    if (totalSize > length)
    {
	printf ("PEXlib WARNING : Internal error in PEXCountOCs :\n");
	printf ("OC parsing continued past the end of the input buffer.\n");
    }
#endif

    return (oc_count);
}
