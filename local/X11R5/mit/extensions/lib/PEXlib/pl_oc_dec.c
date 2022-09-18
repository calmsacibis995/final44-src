/* $XConsortium: pl_oc_dec.c,v 1.9 92/11/10 11:46:13 mor Exp $ */

/******************************************************************************
Copyright 1992 by the Massachusetts Institute of Technology

                        All Rights Reserved

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation, and that the name of M.I.T. not be used in advertising or
publicity pertaining to distribution of the software without specific,
written prior permission.  M.I.T. makes no representations about the
suitability of this software for any purpose.  It is provided "as is"
without express or implied warranty.
******************************************************************************/

#include "PEXlib.h"
#include "PEXlibint.h"
#include "pl_oc_util.h"


PEXOCData *
PEXDecodeOCs (float_format, oc_count, length, encoded_ocs)

INPUT int		float_format;
INPUT unsigned long	oc_count;
INPUT unsigned long	length;
INPUT char		*encoded_ocs;

{
    extern void		(*(PEX_decode_oc_funcs[]))();
    PEXOCData		*ocDest, *ocRet;
    pexElementInfo	*elemInfo;
    char		*ocSrc;
    int			i;


    /*
     * Allocate a buffer to hold the decoded OC data.
     */

    ocRet = (PEXOCData *) PEXAllocBuf ((unsigned)
	(oc_count * sizeof (PEXOCData)));


    /*
     * Now, decode the OCs.
     */

    ocSrc = encoded_ocs;
    ocDest = ocRet;

    for (i = 0; i < oc_count; i++, ocDest++)
    {
	elemInfo = (pexElementInfo *) ocSrc;
	ocDest->oc_type = elemInfo->elementType;
	(*PEX_decode_oc_funcs[elemInfo->elementType]) (float_format,
	    &ocSrc, ocDest);
    }

#ifdef DEBUG
    if (ocSrc - encoded_ocs != length)
    {
	printf ("PEXlib WARNING : Internal error in PEXDecodeOCs :\n");
	printf ("Number of bytes parsed not equal to size of input buffer.\n");
    }
#endif

    return (ocRet);
}


void _PEXDecodeEnumType (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexMarkerType *oc = (pexMarkerType *) *ocSrc;

    ocDest->data.SetMarkerType.marker_type = oc->markerType;
    *ocSrc = (char *) (oc + 1);
}


void _PEXDecodeTableIndex (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexMarkerColorIndex *oc = (pexMarkerColorIndex *) *ocSrc;

    ocDest->data.SetMarkerColorIndex.index = oc->index;
    *ocSrc = (char *) (oc + 1);
}


void _PEXDecodeColor (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexMarkerColor *oc = (pexMarkerColor *) *ocSrc;
    
    ocDest->data.SetMarkerColor.color_type = oc->colorSpec.colorType;
    
    COPY_AREA ((oc + 1), &(ocDest->data.SetMarkerColor.color),
	GetColorSize (oc->colorSpec.colorType));
    
    *ocSrc += (sizeof (pexMarkerColor) +
	GetColorSize (oc->colorSpec.colorType));
}


void _PEXDecodeFloat (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexMarkerScale *oc = (pexMarkerScale *) *ocSrc;

    ocDest->data.SetMarkerScale.scale = oc->scale;
    *ocSrc = (char *) (oc + 1);
}


void _PEXDecodeCARD16 (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexTextPrecision *oc = (pexTextPrecision *) *ocSrc;

    ocDest->data.SetTextPrecision.precision = oc->precision;
    *ocSrc = (char *) (oc + 1);
}


void _PEXDecodeVector2D (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexCharUpVector *oc = (pexCharUpVector *) *ocSrc;

    ocDest->data.SetCharUpVector.vector.x = oc->up.x;
    ocDest->data.SetCharUpVector.vector.y = oc->up.y;
    *ocSrc = (char *) (oc + 1);
}


void _PEXDecodeTextAlignment (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexTextAlignment *oc = (pexTextAlignment *) *ocSrc;

    ocDest->data.SetTextAlignment.halignment = oc->alignment.horizontal;
    ocDest->data.SetTextAlignment.valignment = oc->alignment.vertical;
    *ocSrc = (char *) (oc + 1);
}


void _PEXDecodeCurveApprox (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexCurveApproximation *oc = (pexCurveApproximation *) *ocSrc;
    
    ocDest->data.SetCurveApprox.method = oc->approx.approxMethod;
    ocDest->data.SetCurveApprox.tolerance = oc->approx.tolerance;
    
    *ocSrc = (char *) (oc + 1);
}


void _PEXDecodeReflectionAttr (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexSurfaceReflAttr *oc = (pexSurfaceReflAttr *) *ocSrc;
    
    ocDest->data.SetReflectionAttributes.attributes.ambient =
	oc->reflectionAttr.ambient;
    ocDest->data.SetReflectionAttributes.attributes.diffuse =
	oc->reflectionAttr.diffuse;
    ocDest->data.SetReflectionAttributes.attributes.specular =
	oc->reflectionAttr.specular;
    ocDest->data.SetReflectionAttributes.attributes.specular_conc =
	oc->reflectionAttr.specularConc;
    ocDest->data.SetReflectionAttributes.attributes.transmission =
	oc->reflectionAttr.transmission;
    
    InitializeColorSpecifier (
	ocDest->data.SetReflectionAttributes.attributes.specular_color,
	(oc + 1), oc->reflectionAttr.specularColor.colorType);
    
    *ocSrc += (sizeof (pexSurfaceReflAttr) +
	GetColorSize (oc->reflectionAttr.specularColor.colorType));
}


void _PEXDecodeSurfaceApprox (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexSurfaceApproximation *oc = (pexSurfaceApproximation *) *ocSrc;
    
    ocDest->data.SetSurfaceApprox.method = oc->approx.approxMethod;
    ocDest->data.SetSurfaceApprox.utolerance = oc->approx.uTolerance;
    ocDest->data.SetSurfaceApprox.vtolerance = oc->approx.vTolerance;
    *ocSrc = (char *) (oc + 1);
}


void _PEXDecodeCullMode (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexCullingMode *oc = (pexCullingMode *) *ocSrc;
    
    ocDest->data.SetFacetCullingMode.mode = oc->cullMode;
    *ocSrc = (char *) (oc + 1);
}


void _PEXDecodeSwitch (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexDistinguishFlag *oc = (pexDistinguishFlag *) *ocSrc;
    
    ocDest->data.SetFacetDistinguishFlag.flag = oc->distinguish;
    *ocSrc = (char *) (oc + 1);
}


void _PEXDecodePatternSize (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexPatternSize *oc = (pexPatternSize *) *ocSrc;
    
    ocDest->data.SetPatternSize.width = oc->size.x;
    ocDest->data.SetPatternSize.height = oc->size.y;
    *ocSrc = (char *) (oc + 1);
}


void _PEXDecodePatternAttr2D (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexPatternRefPt *oc = (pexPatternRefPt *) *ocSrc;
    
    ocDest->data.SetPatternAttributes2D.ref_point.x = oc->point.x;
    ocDest->data.SetPatternAttributes2D.ref_point.y = oc->point.y;
    *ocSrc = (char *) (oc + 1);
}


void _PEXDecodePatternAttr (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexPatternAttr *oc = (pexPatternAttr *) *ocSrc;
    
    ocDest->data.SetPatternAttributes.ref_point.x = oc->refPt.x;
    ocDest->data.SetPatternAttributes.ref_point.y = oc->refPt.y;
    ocDest->data.SetPatternAttributes.ref_point.z = oc->refPt.z;
    ocDest->data.SetPatternAttributes.vector1.x = oc->vector1.x;
    ocDest->data.SetPatternAttributes.vector1.y = oc->vector1.y;
    ocDest->data.SetPatternAttributes.vector1.z = oc->vector1.z;
    ocDest->data.SetPatternAttributes.vector2.x = oc->vector2.x;
    ocDest->data.SetPatternAttributes.vector2.y = oc->vector2.y;
    ocDest->data.SetPatternAttributes.vector2.z = oc->vector2.z;
    *ocSrc = (char *) (oc + 1);
}


void _PEXDecodeASF (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexSetAsfValues *oc = (pexSetAsfValues *) *ocSrc;
    
    ocDest->data.SetIndividualASF.attribute = oc->attribute;
    ocDest->data.SetIndividualASF.asf = oc->source;
    *ocSrc = (char *) (oc + 1);
}


void _PEXDecodeLocalTransform (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexLocalTransform *oc = (pexLocalTransform *) *ocSrc;
    
    COPY_AREA (oc->matrix, ocDest->data.SetLocalTransform.transform,
	sizeof (pexMatrix));
    ocDest->data.SetLocalTransform.composition = oc->compType;
    *ocSrc = (char *) (oc + 1);
}


void _PEXDecodeLocalTransform2D (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexLocalTransform2D *oc = (pexLocalTransform2D *) *ocSrc;
    
    COPY_AREA (oc->matrix3X3, ocDest->data.SetLocalTransform2D.transform,
	sizeof (pexMatrix3X3));
    ocDest->data.SetLocalTransform2D.composition = oc->compType;
    *ocSrc = (char *) (oc + 1);
}


void _PEXDecodeGlobalTransform (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexGlobalTransform *oc = (pexGlobalTransform *) *ocSrc;
    
    COPY_AREA (oc->matrix, ocDest->data.SetGlobalTransform.transform,
	sizeof (pexMatrix));
    *ocSrc = (char *) (oc + 1);
}


void _PEXDecodeGlobalTransform2D (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexGlobalTransform2D *oc = (pexGlobalTransform2D *) *ocSrc;
    
    COPY_AREA (oc->matrix3X3, ocDest->data.SetGlobalTransform2D.transform,
	sizeof (pexMatrix3X3));
    *ocSrc = (char *) (oc + 1);
}


void _PEXDecodeModelClipVolume (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexModelClipVolume 	*oc = (pexModelClipVolume *) *ocSrc;
    int		   	size;
    
    ocDest->data.SetModelClipVolume.op = oc->modelClipOperator;
    ocDest->data.SetModelClipVolume.count = oc->numHalfSpaces;
    size = oc->numHalfSpaces * sizeof (PEXHalfSpace);
    ocDest->data.SetModelClipVolume.half_spaces =
	(PEXHalfSpace *) PEXAllocBuf ((unsigned) size);
    COPY_AREA ((oc + 1), ocDest->data.SetModelClipVolume.half_spaces, size);
    *ocSrc += (sizeof (pexModelClipVolume) +
	oc->numHalfSpaces * sizeof (pexHalfSpace));
}


void _PEXDecodeModelClipVolume2D (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexModelClipVolume2D	*oc = (pexModelClipVolume2D *) *ocSrc;
    int		   		size;
    
    ocDest->data.SetModelClipVolume2D.op = oc->modelClipOperator;
    ocDest->data.SetModelClipVolume2D.count = oc->numHalfSpaces;
    size = oc->numHalfSpaces * sizeof (PEXHalfSpace2D);
    ocDest->data.SetModelClipVolume2D.half_spaces =
	(PEXHalfSpace2D *) PEXAllocBuf ((unsigned) size);
    COPY_AREA ((oc + 1), ocDest->data.SetModelClipVolume2D.half_spaces, size);
    *ocSrc += (sizeof (pexModelClipVolume2D) +
	oc->numHalfSpaces * sizeof (pexHalfSpace2D));
}


void _PEXDecodeRestoreModelClip (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexRestoreModelClip	*oc = (pexRestoreModelClip *) *ocSrc;

    *ocSrc = (char *) (oc + 1);
}


void _PEXDecodeLightSourceState (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexLightState 	*oc = (pexLightState *) *ocSrc;
    int			size;
    
    ocDest->data.SetLightSourceState.enable_count = oc->numEnable;
    ocDest->data.SetLightSourceState.disable_count = oc->numDisable;
    
    size = oc->numEnable * sizeof (PEXTableIndex);
    ocDest->data.SetLightSourceState.enable =
	(PEXTableIndex *) PEXAllocBuf ((unsigned) size);
    COPY_AREA ((oc + 1), ocDest->data.SetLightSourceState.enable, size);
    *ocSrc += (sizeof (pexLightState) + PADDED_BYTES (size));
    
    size = oc->numDisable * sizeof (PEXTableIndex);
    ocDest->data.SetLightSourceState.disable =
	(PEXTableIndex *) PEXAllocBuf ((unsigned) size);
    COPY_AREA (*ocSrc, ocDest->data.SetLightSourceState.disable, size);
    *ocSrc += PADDED_BYTES (size);
}


void _PEXDecodeID (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexPickId *oc = (pexPickId *) *ocSrc;
    
    ocDest->data.SetPickID.pick_id = oc->pickId;
    *ocSrc = (char *) (oc + 1);
}


void _PEXDecodePSC (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexParaSurfCharacteristics *oc = (pexParaSurfCharacteristics *) *ocSrc;

    ocDest->data.SetParaSurfCharacteristics.psc_type = oc->characteristics;

    switch (oc->characteristics)
    {
    case PEXPSCIsoCurves:
    {
	pexPSC_IsoparametricCurves *isoSrc =
	    (pexPSC_IsoparametricCurves *) (oc + 1);
	
	PEXPSCIsoparametricCurves *isoDest = (PEXPSCIsoparametricCurves *)
	    &ocDest->data.SetParaSurfCharacteristics.characteristics.iso_curves;

	isoDest->placement_type = isoSrc->placementType;
	isoDest->u_count = isoSrc->numUcurves;
	isoDest->v_count = isoSrc->numVcurves;

	*ocSrc = (char *) (isoSrc + 1);
	break;
    }
	
    case PEXPSCMCLevelCurves:
    case PEXPSCWCLevelCurves:
    {
	pexPSC_LevelCurves 	*levelSrc = (pexPSC_LevelCurves *) (oc + 1);
	PEXPSCLevelCurves 	*levelDest = (PEXPSCLevelCurves *)
	  &ocDest->data.SetParaSurfCharacteristics.characteristics.level_curves;

	levelDest->origin.x = levelSrc->origin.x;
	levelDest->origin.y = levelSrc->origin.y;
	levelDest->origin.z = levelSrc->origin.z;
	levelDest->direction.x = levelSrc->direction.x;
	levelDest->direction.y = levelSrc->direction.y;
	levelDest->direction.z = levelSrc->direction.z;
	levelDest->count = levelSrc->numberIntersections;
	levelDest->parameters = (float *) PEXAllocBuf ((unsigned)
	    (sizeof (float) * levelSrc->numberIntersections));
	COPY_AREA ((levelSrc + 1), levelDest->parameters,
	    sizeof (float) * levelSrc->numberIntersections);

	*ocSrc = (char *) (levelSrc + 1) +
	    sizeof (float) * levelSrc->numberIntersections;
	break;
    }
	
    default:
    	*ocSrc = (char *) (oc + 1) + PADDED_BYTES (oc->length);
	break;
    }

}


void _PEXDecodeNameSet (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexElementInfo	*elemInfo = (pexElementInfo *) *ocSrc;
    int 		size;
    
    ocDest->data.AddToNameSet.count = elemInfo->length - 1;
    size = (elemInfo->length - 1) * sizeof (PEXName);
    ocDest->data.AddToNameSet.names = (PEXName *)
	PEXAllocBuf ((unsigned) size);
    COPY_AREA ((elemInfo + 1), ocDest->data.AddToNameSet.names, size);
    *ocSrc += (sizeof (pexAddToNameSet) + size);
}


void _PEXDecodeExecuteStructure (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexExecuteStructure *oc = (pexExecuteStructure *) *ocSrc;

    ocDest->data.ExecuteStructure.structure = oc->id;
    *ocSrc = (char *) (oc + 1);
}


void _PEXDecodeLabel (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexLabel *oc = (pexLabel *) *ocSrc;

    ocDest->data.Label.label = oc->label;
    *ocSrc = (char *) (oc + 1);
}


void _PEXDecodeApplicationData (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexApplicationData *oc = (pexApplicationData *) *ocSrc;
    
    ocDest->data.ApplicationData.length = oc->numElements;
    ocDest->data.ApplicationData.data =
	(PEXPointer) PEXAllocBuf ((unsigned) oc->numElements);
    
    COPY_AREA ((oc + 1), ocDest->data.ApplicationData.data, oc->numElements);
    
    *ocSrc += (sizeof (pexApplicationData) + PADDED_BYTES (oc->numElements));
}


void _PEXDecodeGSE (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexGse *oc = (pexGse *) *ocSrc;
    
    ocDest->data.GSE.id = oc->id;
    ocDest->data.GSE.length = oc->numElements;
    ocDest->data.GSE.data = (char *) PEXAllocBuf ((unsigned) oc->numElements);
    
    COPY_AREA ((oc + 1), ocDest->data.GSE.data, oc->numElements);
    
    *ocSrc += (sizeof (pexGse) + PADDED_BYTES (oc->numElements));
}


void _PEXDecodeMarkers (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexElementInfo	*elemInfo = (pexElementInfo *) *ocSrc;
    pexMarker 		*oc = (pexMarker *) elemInfo;
    int 		size;
    
    ocDest->data.Markers.count =
	(sizeof (CARD32) * (elemInfo->length - 1)) / sizeof (pexCoord3D);
    
    size = ocDest->data.Markers.count * sizeof (PEXCoord);
    ocDest->data.Markers.points = (PEXCoord *) PEXAllocBuf ((unsigned) size);
    COPY_AREA ((oc + 1), ocDest->data.Markers.points, size);
    *ocSrc += (sizeof (pexMarker) + size);
}


void _PEXDecodeMarkers2D (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexElementInfo	*elemInfo = (pexElementInfo *) *ocSrc;
    pexMarker2D		*oc = (pexMarker2D *) elemInfo;
    int 		size;
    
    ocDest->data.Markers2D.count =
	(sizeof (CARD32) * (elemInfo->length - 1)) / sizeof (pexCoord2D);
    
    size = ocDest->data.Markers2D.count * sizeof (PEXCoord2D);
    ocDest->data.Markers2D.points = (PEXCoord2D *)
	PEXAllocBuf ((unsigned) size);
    COPY_AREA ((oc + 1), ocDest->data.Markers2D.points, size);
    *ocSrc += (sizeof (pexMarker2D) + size);
}


void _PEXDecodePolyline (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexElementInfo	*elemInfo = (pexElementInfo *) *ocSrc;
    pexPolyline 	*oc = (pexPolyline *) elemInfo;
    int 		size;
    
    ocDest->data.Polyline.count =
	(sizeof (CARD32) * (elemInfo->length - 1)) / sizeof (pexCoord3D);
    
    size = ocDest->data.Polyline.count * sizeof (PEXCoord);
    ocDest->data.Polyline.points = (PEXCoord *) PEXAllocBuf ((unsigned) size);
    COPY_AREA ((oc + 1), ocDest->data.Polyline.points, size);
    *ocSrc += (sizeof (pexPolyline) + size);
}


void _PEXDecodePolyline2D (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexElementInfo	*elemInfo = (pexElementInfo *) *ocSrc;
    pexPolyline2D	*oc = (pexPolyline2D *) elemInfo;
    int 		size;
    
    ocDest->data.Polyline2D.count =
	(sizeof (CARD32) * (elemInfo->length - 1)) / sizeof (pexCoord2D);
    
    size = ocDest->data.Polyline2D.count * sizeof (PEXCoord2D);
    ocDest->data.Polyline2D.points = (PEXCoord2D *)
	PEXAllocBuf ((unsigned) size);
    COPY_AREA ((oc + 1), ocDest->data.Polyline2D.points, size);
    *ocSrc += (sizeof (pexPolyline2D) + size);
}


void _PEXDecodeText (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    /* Text is always mono encoded */

    pexText 		*oc = (pexText *) *ocSrc;
    pexMonoEncoding	*srcEnc;
    PEXEncodedTextData	*destEnc;
    int			size, i;

    ocDest->data.EncodedText.origin.x = oc->origin.x;
    ocDest->data.EncodedText.origin.y = oc->origin.y;
    ocDest->data.EncodedText.origin.z = oc->origin.z;
    ocDest->data.EncodedText.vector1.x = oc->vector1.x;
    ocDest->data.EncodedText.vector1.y = oc->vector1.y;
    ocDest->data.EncodedText.vector1.z = oc->vector1.z;
    ocDest->data.EncodedText.vector2.x = oc->vector2.x;
    ocDest->data.EncodedText.vector2.y = oc->vector2.y;
    ocDest->data.EncodedText.vector2.z = oc->vector2.z;
    ocDest->data.EncodedText.count = oc->numEncodings;

    size = oc->numEncodings * sizeof (PEXEncodedTextData);
    ocDest->data.EncodedText.encoded_text =
	(PEXEncodedTextData *) PEXAllocBuf ((unsigned) size);

    srcEnc = (pexMonoEncoding *) (oc + 1);
    destEnc = ocDest->data.EncodedText.encoded_text;

    for (i = 0; i < (int) oc->numEncodings; i++, destEnc++)
    {
	destEnc->character_set = srcEnc->characterSet;
	destEnc->character_set_width = srcEnc->characterSetWidth;
	destEnc->encoding_state = srcEnc->encodingState;
	destEnc->length = srcEnc->numChars;

	if (srcEnc->characterSetWidth == PEXCSLong)
	    size = srcEnc->numChars * sizeof (long);
	else if (srcEnc->characterSetWidth == PEXCSShort)
	    size = srcEnc->numChars * sizeof (short);
	else /* srcEnc->characterSetWidth == PEXCSByte) */
	    size = srcEnc->numChars;
	
	destEnc->ch = (char *) PEXAllocBuf ((unsigned) size);
	COPY_AREA ((srcEnc + 1), destEnc->ch, size);
	srcEnc = (pexMonoEncoding *) ((char *) srcEnc +
	    sizeof (pexMonoEncoding) + PADDED_BYTES (size));
    }

    *ocSrc = (char *) srcEnc;
}


void _PEXDecodeText2D (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    /* Text is always mono encoded */

    pexText2D 		*oc = (pexText2D *) *ocSrc;
    pexMonoEncoding	*srcEnc;
    PEXEncodedTextData	*destEnc;
    int			size, i;

    ocDest->data.EncodedText2D.origin.x = oc->origin.x;
    ocDest->data.EncodedText2D.origin.y = oc->origin.y;
    ocDest->data.EncodedText2D.count = oc->numEncodings;

    size = oc->numEncodings * sizeof (PEXEncodedTextData);
    ocDest->data.EncodedText2D.encoded_text =
	(PEXEncodedTextData *) PEXAllocBuf ((unsigned) size);

    srcEnc = (pexMonoEncoding *) (oc + 1);
    destEnc = ocDest->data.EncodedText2D.encoded_text;

    for (i = 0; i < (int) oc->numEncodings; i++, destEnc++)
    {
	destEnc->character_set = srcEnc->characterSet;
	destEnc->character_set_width = srcEnc->characterSetWidth;
	destEnc->encoding_state = srcEnc->encodingState;
	destEnc->length = srcEnc->numChars;

	if (srcEnc->characterSetWidth == PEXCSLong)
	    size = srcEnc->numChars * sizeof (long);
	else if (srcEnc->characterSetWidth == PEXCSShort)
	    size = srcEnc->numChars * sizeof (short);
	else /* srcEnc->characterSetWidth == PEXCSByte) */
	    size = srcEnc->numChars;
	
	destEnc->ch = (char *) PEXAllocBuf ((unsigned) size);
	COPY_AREA ((srcEnc + 1), destEnc->ch, size);
	srcEnc = (pexMonoEncoding *) ((char *) srcEnc +
	    sizeof (pexMonoEncoding) + PADDED_BYTES (size));
    }

    *ocSrc = (char *) srcEnc;
}


void _PEXDecodeAnnoText (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    /* Anno Text is always mono encoded */

    pexAnnotationText	*oc = (pexAnnotationText *) *ocSrc;
    pexMonoEncoding	*srcEnc;
    PEXEncodedTextData	*destEnc;
    int			size, i;

    ocDest->data.EncodedAnnoText.origin.x = oc->origin.x;
    ocDest->data.EncodedAnnoText.origin.y = oc->origin.y;
    ocDest->data.EncodedAnnoText.origin.z = oc->origin.z;
    ocDest->data.EncodedAnnoText.offset.x = oc->offset.x;
    ocDest->data.EncodedAnnoText.offset.y = oc->offset.y;
    ocDest->data.EncodedAnnoText.offset.z = oc->offset.z;
    ocDest->data.EncodedAnnoText.count = oc->numEncodings;

    size = oc->numEncodings * sizeof (PEXEncodedTextData);
    ocDest->data.EncodedAnnoText.encoded_text =
	(PEXEncodedTextData *) PEXAllocBuf ((unsigned) size);

    srcEnc = (pexMonoEncoding *) (oc + 1);
    destEnc = ocDest->data.EncodedAnnoText.encoded_text;

    for (i = 0; i < (int) oc->numEncodings; i++, destEnc++)
    {
	destEnc->character_set = srcEnc->characterSet;
	destEnc->character_set_width = srcEnc->characterSetWidth;
	destEnc->encoding_state = srcEnc->encodingState;
	destEnc->length = srcEnc->numChars;

	if (srcEnc->characterSetWidth == PEXCSLong)
	    size = srcEnc->numChars * sizeof (long);
	else if (srcEnc->characterSetWidth == PEXCSShort)
	    size = srcEnc->numChars * sizeof (short);
	else /* srcEnc->characterSetWidth == PEXCSByte) */
	    size = srcEnc->numChars;
	
	destEnc->ch = (char *) PEXAllocBuf ((unsigned) size);
	COPY_AREA ((srcEnc + 1), destEnc->ch, size);
	srcEnc = (pexMonoEncoding *) ((char *) srcEnc +
	    sizeof (pexMonoEncoding) + PADDED_BYTES (size));
    }

    *ocSrc = (char *) srcEnc;
}


void _PEXDecodeAnnoText2D (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    /* Anno Text is always mono encoded */

    pexAnnotationText2D	*oc = (pexAnnotationText2D *) *ocSrc;
    pexMonoEncoding	*srcEnc;
    PEXEncodedTextData	*destEnc;
    int			size, i;

    ocDest->data.EncodedAnnoText2D.origin.x = oc->origin.x;
    ocDest->data.EncodedAnnoText2D.origin.y = oc->origin.y;
    ocDest->data.EncodedAnnoText2D.offset.x = oc->offset.x;
    ocDest->data.EncodedAnnoText2D.offset.y = oc->offset.y;
    ocDest->data.EncodedAnnoText2D.count = oc->numEncodings;

    size = oc->numEncodings * sizeof (PEXEncodedTextData);
    ocDest->data.EncodedAnnoText2D.encoded_text =
	(PEXEncodedTextData *) PEXAllocBuf ((unsigned) size);

    srcEnc = (pexMonoEncoding *) (oc + 1);
    destEnc = ocDest->data.EncodedAnnoText2D.encoded_text;

    for (i = 0; i < (int) oc->numEncodings; i++, destEnc++)
    {
	destEnc->character_set = srcEnc->characterSet;
	destEnc->character_set_width = srcEnc->characterSetWidth;
	destEnc->encoding_state = srcEnc->encodingState;
	destEnc->length = srcEnc->numChars;

	if (srcEnc->characterSetWidth == PEXCSLong)
	    size = srcEnc->numChars * sizeof (long);
	else if (srcEnc->characterSetWidth == PEXCSShort)
	    size = srcEnc->numChars * sizeof (short);
	else /* srcEnc->characterSetWidth == PEXCSByte) */
	    size = srcEnc->numChars;
	
	destEnc->ch = (char *) PEXAllocBuf ((unsigned) size);
	COPY_AREA ((srcEnc + 1), destEnc->ch, size);
	srcEnc = (pexMonoEncoding *) ((char *) srcEnc +
	    sizeof (pexMonoEncoding) + PADDED_BYTES (size));
    }

    *ocSrc = (char *) srcEnc;
}


void _PEXDecodePolylineSet (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexPolylineSet 	*oc = (pexPolylineSet *) *ocSrc;
    PEXListOfVertex	*plset;
    char		*pData;
    int			lenofVertex, size, i;

    ocDest->data.PolylineSetWithData.vertex_attributes = oc->vertexAttribs;
    ocDest->data.PolylineSetWithData.color_type = oc->colorType;
    ocDest->data.PolylineSetWithData.count = oc->numLists;
    ocDest->data.PolylineSetWithData.vertex_lists = plset = (PEXListOfVertex *)
	PEXAllocBuf ((unsigned) (oc->numLists * sizeof (PEXListOfVertex)));

    lenofVertex = LENOF (PEXCoord) + ((oc->vertexAttribs & PEXGAColor) ?
	GetColorLength (oc->colorType) : 0); 

    pData = (char *) (oc + 1);

    for (i = 0; i < oc->numLists; i++, plset++)
    {
	plset->count = *((CARD32 *) pData);
	pData += sizeof (CARD32);

	size = NUMBYTES (plset->count * lenofVertex);
	plset->vertices.no_data = (PEXCoord *) PEXAllocBuf ((unsigned) size);
	COPY_AREA (pData, plset->vertices.no_data, size);
	pData += size;
    }

    *ocSrc = pData;
}


void _PEXDecodeNURBCurve (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexNurbCurve	*oc = (pexNurbCurve *) *ocSrc;
    char		*pData;
    int	   		size;

    ocDest->data.NURBCurve.rationality = oc->coordType;
    ocDest->data.NURBCurve.order = oc->curveOrder;
    ocDest->data.NURBCurve.tmin = oc->tmin;
    ocDest->data.NURBCurve.tmax = oc->tmax;
    ocDest->data.NURBCurve.count = oc->numPoints;

    size = oc->numKnots * sizeof (float);
    ocDest->data.NURBCurve.knots = (float *) PEXAllocBuf ((unsigned) size);

    pData = (char *) (oc + 1);
    COPY_AREA (pData, ocDest->data.NURBCurve.knots, size);
    pData += size;

    size = oc->numPoints * ((oc->coordType == PEXRational) ?
	sizeof (PEXCoord4D) : sizeof (PEXCoord));

    ocDest->data.NURBCurve.points.point =
	(PEXCoord *) PEXAllocBuf ((unsigned) size);

    COPY_AREA (pData, ocDest->data.NURBCurve.points.point, size);

    *ocSrc = pData + size;
}


void _PEXDecodeFillArea (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexElementInfo	*elemInfo = (pexElementInfo *) *ocSrc;
    pexFillArea 	*oc = (pexFillArea *) elemInfo;
    int 		size;
    
    ocDest->data.FillArea.shape_hint = oc->shape;
    ocDest->data.FillArea.ignore_edges = oc->ignoreEdges;
    
    ocDest->data.FillArea.count =
	(sizeof (CARD32) * (elemInfo->length - 2)) / sizeof (pexCoord3D);
    
    size = ocDest->data.FillArea.count * sizeof (PEXCoord);
    ocDest->data.FillArea.points = (PEXCoord *) PEXAllocBuf ((unsigned) size);
    COPY_AREA ((oc + 1), ocDest->data.FillArea.points, size);
    *ocSrc += (sizeof (pexFillArea) + size);
}


void _PEXDecodeFillArea2D (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexElementInfo	*elemInfo = (pexElementInfo *) *ocSrc;
    pexFillArea2D 	*oc = (pexFillArea2D *) elemInfo;
    int 		size;
    
    ocDest->data.FillArea2D.shape_hint = oc->shape;
    ocDest->data.FillArea2D.ignore_edges = oc->ignoreEdges;
    
    ocDest->data.FillArea2D.count =
	(sizeof (CARD32) * (elemInfo->length - 2)) / sizeof (pexCoord2D);
    
    size = ocDest->data.FillArea2D.count * sizeof (PEXCoord2D);
    ocDest->data.FillArea2D.points = (PEXCoord2D *)
	PEXAllocBuf ((unsigned) size);
    COPY_AREA ((oc + 1), ocDest->data.FillArea2D.points, size);
    *ocSrc += (sizeof (pexFillArea2D) + size);
}


void _PEXDecodeFillAreaWithData (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexExtFillArea 	*oc = (pexExtFillArea *) *ocSrc;
    char		*pData;
    int			lenofFacetData;
    int			lenofVertex;
    int			lenofColor, size;
    
    ocDest->data.FillAreaWithData.shape_hint = oc->shape;
    ocDest->data.FillAreaWithData.ignore_edges = oc->ignoreEdges;
    ocDest->data.FillAreaWithData.facet_attributes = oc->facetAttribs;
    ocDest->data.FillAreaWithData.vertex_attributes = oc->vertexAttribs;
    ocDest->data.FillAreaWithData.color_type = oc->colorType;

    lenofColor = GetColorLength (oc->colorType);
    lenofFacetData = GetFacetDataLength (oc->facetAttribs, lenofColor); 
    lenofVertex = GetVertexWithDataLength (oc->vertexAttribs, lenofColor);

    pData = (char *) (oc + 1);

    if (oc->facetAttribs)
    {
	size = NUMBYTES (lenofFacetData);
	COPY_AREA (pData,
	    &(ocDest->data.FillAreaWithData.facet_data.index), size);
	pData += size;
    }

    ocDest->data.FillAreaWithData.count = *((CARD32 *) pData);
    pData += sizeof (CARD32);

    size = ocDest->data.FillAreaWithData.count * NUMBYTES (lenofVertex);
    ocDest->data.FillAreaWithData.vertices.no_data =
	(PEXCoord *) PEXAllocBuf ((unsigned) size);

    COPY_AREA (pData, ocDest->data.FillAreaWithData.vertices.no_data, size);

    *ocSrc = (char *) (pData + size);
}


void _PEXDecodeFillAreaSet (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexFillAreaSet 	*oc = (pexFillAreaSet *) *ocSrc;
    PEXListOfCoord	*pList;
    char		*pData;
    int			size, i;

    ocDest->data.FillAreaSet.shape_hint = oc->shape;
    ocDest->data.FillAreaSet.ignore_edges = oc->ignoreEdges;
    ocDest->data.FillAreaSet.contour_hint = oc->contourHint;
    ocDest->data.FillAreaSet.count = oc->numLists;

    ocDest->data.FillAreaSet.point_lists = pList = (PEXListOfCoord *)
	PEXAllocBuf ((unsigned) (oc->numLists * sizeof (PEXListOfCoord)));

    pData = (char *) (oc + 1);

    for (i = 0; i < oc->numLists; i++, pList++)
    {
	pList->count = *((CARD32 *) pData);
	pData += sizeof (CARD32);
	size = pList->count * sizeof (PEXCoord);
	pList->points = (PEXCoord *) PEXAllocBuf ((unsigned) size);
	COPY_AREA (pData, pList->points, size);
	pData += size;
    }

    *ocSrc = pData;
}


void _PEXDecodeFillAreaSet2D (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexFillAreaSet2D 	*oc = (pexFillAreaSet2D *) *ocSrc;
    PEXListOfCoord2D	*pList;
    char		*pData;
    int			size, i;

    ocDest->data.FillAreaSet2D.shape_hint = oc->shape;
    ocDest->data.FillAreaSet2D.ignore_edges = oc->ignoreEdges;
    ocDest->data.FillAreaSet2D.contour_hint = oc->contourHint;
    ocDest->data.FillAreaSet2D.count = oc->numLists;

    ocDest->data.FillAreaSet2D.point_lists = pList = (PEXListOfCoord2D *)
	PEXAllocBuf ((unsigned) (oc->numLists * sizeof (PEXListOfCoord2D)));

    pData = (char *) (oc + 1);

    for (i = 0; i < oc->numLists; i++, pList++)
    {
	pList->count = *((CARD32 *) pData);
	pData += sizeof (CARD32);
	size = pList->count * sizeof (PEXCoord2D);
	pList->points = (PEXCoord2D *) PEXAllocBuf ((unsigned) size);
	COPY_AREA (pData, pList->points, size);
	pData += size;
    }

    *ocSrc = pData;
}


void _PEXDecodeFillAreaSetWithData (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexExtFillAreaSet 	*oc = (pexExtFillAreaSet *) *ocSrc;
    char		*pData;
    PEXListOfVertex	*pList;
    int			lenofFacetData;
    int			lenofVertex;
    int			lenofColor, size, i;

    ocDest->data.FillAreaSetWithData.shape_hint = oc->shape;
    ocDest->data.FillAreaSetWithData.ignore_edges = oc->ignoreEdges;
    ocDest->data.FillAreaSetWithData.contour_hint = oc->contourHint;
    ocDest->data.FillAreaSetWithData.facet_attributes = oc->facetAttribs;
    ocDest->data.FillAreaSetWithData.vertex_attributes = oc->vertexAttribs;
    ocDest->data.FillAreaSetWithData.color_type = oc->colorType;

    lenofColor = GetColorLength (oc->colorType);
    lenofFacetData = GetFacetDataLength (oc->facetAttribs, lenofColor); 
    lenofVertex = GetVertexWithDataLength (oc->vertexAttribs, lenofColor);
    
    if (oc->vertexAttribs & PEXGAEdges)
	lenofVertex++; 				/* edge switch is CARD32 */

    pData = (char *) (oc + 1);

    if (oc->facetAttribs)
    {
	size = NUMBYTES (lenofFacetData);
	COPY_AREA (pData,
	    &(ocDest->data.FillAreaSetWithData.facet_data.index), size);
	pData += size;
    }

    ocDest->data.FillAreaSetWithData.count = oc->numLists;
    ocDest->data.FillAreaSetWithData.vertex_lists = pList = (PEXListOfVertex *)
	PEXAllocBuf ((unsigned) (oc->numLists * sizeof (PEXListOfVertex)));
    
    for (i = 0; i < oc->numLists; i++, pList++)
    {
	pList->count = *((CARD32 *) pData);
	pData += sizeof (CARD32);
	size = pList->count * NUMBYTES (lenofVertex);
	pList->vertices.no_data = (PEXCoord *) PEXAllocBuf ((unsigned) size);
	COPY_AREA (pData, pList->vertices.no_data, size);
	pData += size;
    }

    *ocSrc = pData;
}


void _PEXDecodeTriangleStrip (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexTriangleStrip 	*oc = (pexTriangleStrip *) *ocSrc;
    int			lenofColor;
    int			lenofFacetDataList;
    int			lenofVertexList, size;
    char		*pData;

    ocDest->data.TriangleStrip.facet_attributes = oc->facetAttribs;
    ocDest->data.TriangleStrip.vertex_attributes = oc->vertexAttribs;
    ocDest->data.TriangleStrip.color_type = oc->colorType;
    ocDest->data.TriangleStrip.count = oc->numVertices;

    lenofColor = GetColorLength (oc->colorType);
    lenofFacetDataList = (oc->numVertices - 2) *
	GetFacetDataLength (oc->facetAttribs, lenofColor); 
    lenofVertexList = oc->numVertices *
	GetVertexWithDataLength (oc->vertexAttribs, lenofColor);

    pData = (char *) (oc + 1);

    if (oc->facetAttribs)
    {
	size = NUMBYTES (lenofFacetDataList);
	ocDest->data.TriangleStrip.facet_data.index =
	    (PEXColorIndexed *) PEXAllocBuf ((unsigned) size);
	COPY_AREA (pData,
	    ocDest->data.TriangleStrip.facet_data.index, size);
	pData += size;
    }
    else
	ocDest->data.TriangleStrip.facet_data.index = NULL;

    size = NUMBYTES (lenofVertexList);
    ocDest->data.TriangleStrip.vertices.no_data =
	(PEXCoord *) PEXAllocBuf ((unsigned) size);

    COPY_AREA (pData, ocDest->data.TriangleStrip.vertices.no_data, size);

    *ocSrc = (char *) (pData + size);
}


void _PEXDecodeQuadMesh (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexQuadrilateralMesh 	*oc = (pexQuadrilateralMesh *) *ocSrc;
    int				lenofColor;
    int				lenofFacetDataList;
    int				lenofVertexList, size;
    char			*pData;

    ocDest->data.QuadrilateralMesh.shape_hint = oc->shape;
    ocDest->data.QuadrilateralMesh.facet_attributes = oc->facetAttribs;
    ocDest->data.QuadrilateralMesh.vertex_attributes = oc->vertexAttribs;
    ocDest->data.QuadrilateralMesh.color_type = oc->colorType;
    ocDest->data.QuadrilateralMesh.col_count = oc->mPts;
    ocDest->data.QuadrilateralMesh.row_count = oc->nPts;

    lenofColor = GetColorLength (oc->colorType);
    lenofFacetDataList = ((oc->mPts - 1) * (oc->nPts - 1)) *
	GetFacetDataLength (oc->facetAttribs, lenofColor); 
    lenofVertexList = oc->mPts * oc->nPts *
	GetVertexWithDataLength (oc->vertexAttribs, lenofColor);

    pData = (char *) (oc + 1);

    if (oc->facetAttribs)
    {
	size = NUMBYTES (lenofFacetDataList);
	ocDest->data.QuadrilateralMesh.facet_data.index =
	    (PEXColorIndexed *) PEXAllocBuf ((unsigned) size);
	COPY_AREA (pData,
	    ocDest->data.QuadrilateralMesh.facet_data.index, size);
	pData += size;
    }
    else
	ocDest->data.QuadrilateralMesh.facet_data.index = NULL;
     

    size = NUMBYTES (lenofVertexList);
    ocDest->data.QuadrilateralMesh.vertices.no_data =
	(PEXCoord *) PEXAllocBuf ((unsigned) size);

    COPY_AREA (pData, ocDest->data.QuadrilateralMesh.vertices.no_data, size);

    *ocSrc = (char *) (pData + size);
}


void _PEXDecodeSOFA (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexSOFAS		*oc = (pexSOFAS *) *ocSrc;
    char		*pData;
    PEXConnectivityData	*pCon;
    PEXListOfUShort	*pList;
    int 		lenofColor;
    int 		lenofFacet;
    int 		lenofVertex;
    int			size, cbytes, i, j;

    ocDest->data.SetOfFillAreaSets.shape_hint = oc->shape;
    ocDest->data.SetOfFillAreaSets.facet_attributes = oc->FAS_Attributes;
    ocDest->data.SetOfFillAreaSets.vertex_attributes = oc->vertexAttributes;
    ocDest->data.SetOfFillAreaSets.edge_attributes =
	(oc->edgeAttributes == PEXOn) ? PEXGAEdges : 0;
    ocDest->data.SetOfFillAreaSets.contour_hint = oc->contourHint;
    ocDest->data.SetOfFillAreaSets.contours_all_one = oc->contourCountsFlag;
    ocDest->data.SetOfFillAreaSets.color_type = oc->colorType;
    ocDest->data.SetOfFillAreaSets.set_count = oc->numFAS;
    ocDest->data.SetOfFillAreaSets.vertex_count = oc->numVertices;
    ocDest->data.SetOfFillAreaSets.index_count = oc->numEdges;

    lenofColor = GetColorLength (oc->colorType);
    lenofFacet = GetFacetDataLength (oc->FAS_Attributes, lenofColor); 
    lenofVertex = GetVertexWithDataLength (oc->vertexAttributes, lenofColor);

    pData = (char *) (oc + 1);

    if (oc->FAS_Attributes)
    {
	size = NUMBYTES (lenofFacet) * oc->numFAS;
	ocDest->data.SetOfFillAreaSets.facet_data.index =
	    (PEXColorIndexed *) PEXAllocBuf ((unsigned) size);
	COPY_AREA (pData,
	    ocDest->data.SetOfFillAreaSets.facet_data.index, size);
	pData += size;
    }
    else
	ocDest->data.SetOfFillAreaSets.facet_data.index = NULL;

    size = NUMBYTES (lenofVertex) * oc->numVertices;
    ocDest->data.SetOfFillAreaSets.vertices.no_data =
	(PEXCoord *) PEXAllocBuf ((unsigned) size);
    COPY_AREA (pData, ocDest->data.SetOfFillAreaSets.vertices.no_data, size);
    pData += size;

    if (oc->edgeAttributes)
    {
	size = oc->numEdges * sizeof (CARD8);
	ocDest->data.SetOfFillAreaSets.edge_flags =
	    (PEXSwitch *) PEXAllocBuf ((unsigned) size);
	COPY_AREA (pData, ocDest->data.SetOfFillAreaSets.edge_flags, size);
	pData += PADDED_BYTES (size);
    }
    else
	ocDest->data.SetOfFillAreaSets.edge_flags = NULL;
	

    ocDest->data.SetOfFillAreaSets.connectivity = pCon = (PEXConnectivityData *)
	PEXAllocBuf ((unsigned) (oc->numFAS * sizeof (PEXConnectivityData)));

    for (i = 0; i < (int) oc->numFAS; i++, pCon++)
    {
	pCon->count = *((CARD16 *) pData);
	pData += sizeof (CARD16);
	pCon->lists = pList = (PEXListOfUShort *)
	    PEXAllocBuf ((unsigned) pCon->count * sizeof (PEXListOfUShort));

	for (j = 0; j < (int) pCon->count; j++, pList++)
	{
	    pList->count = *((CARD16 *) pData);
	    pData += sizeof (CARD16);
	    size = pList->count * sizeof (unsigned short);
	    pList->shorts = (unsigned short *) PEXAllocBuf ((unsigned) size);
	    COPY_AREA (pData, pList->shorts, size);
	    pData += size;
	}
    }
	
    cbytes = sizeof (CARD16) * (oc->numFAS + oc->numContours + oc->numEdges);

    *ocSrc = pData + PAD (cbytes);
}


void _PEXDecodeNURBSurface (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexNurbSurface	*oc = (pexNurbSurface *) *ocSrc;
    int			sizeofVertexList;
    int			sizeofUKnotList;
    int			sizeofVKnotList;
    PEXListOfTrimCurve	*pList;
    pexTrimCurve	*trimSrc;
    PEXTrimCurve	*trimDest;
    int			size, i, j;
    char		*pData;

    ocDest->data.NURBSurface.rationality = oc->type;
    ocDest->data.NURBSurface.uorder = oc->uOrder;
    ocDest->data.NURBSurface.vorder = oc->vOrder;
    ocDest->data.NURBSurface.col_count = oc->mPts;
    ocDest->data.NURBSurface.row_count = oc->nPts;

    sizeofVertexList = oc->mPts * oc->nPts *
        ((oc->type == PEXRational) ? sizeof (PEXCoord4D) : sizeof (PEXCoord));
    sizeofUKnotList = NUMBYTES (oc->uOrder + oc->mPts);
    sizeofVKnotList = NUMBYTES (oc->vOrder + oc->nPts);

    pData = (char *) (oc + 1);

    ocDest->data.NURBSurface.uknots =
	(float *) PEXAllocBuf ((unsigned) sizeofUKnotList);
    COPY_AREA (pData, ocDest->data.NURBSurface.uknots, sizeofUKnotList);
    pData += sizeofUKnotList;

    ocDest->data.NURBSurface.vknots =
	(float *) PEXAllocBuf ((unsigned) sizeofVKnotList);
    COPY_AREA (pData, ocDest->data.NURBSurface.vknots, sizeofVKnotList);
    pData += sizeofVKnotList;

    ocDest->data.NURBSurface.points.point =
	(PEXCoord *) PEXAllocBuf ((unsigned) sizeofVertexList);
    COPY_AREA (pData, ocDest->data.NURBSurface.points.point, sizeofVertexList);
    pData += sizeofVertexList;

    ocDest->data.NURBSurface.curve_count = oc->numLists;
    ocDest->data.NURBSurface.trim_curves = pList = (PEXListOfTrimCurve *)
	PEXAllocBuf ((unsigned) oc->numLists * sizeof (PEXListOfTrimCurve));

    for (i = 0; i < oc->numLists; i++, pList++)
    {
	pList->count = *((CARD32 *) pData);
	pData += sizeof (CARD32);

	pList->curves = trimDest = (PEXTrimCurve *)
	    PEXAllocBuf (pList->count * sizeof (PEXTrimCurve));

	for (j = 0; j < (int) pList->count; j++, trimDest++)
	{
	    trimSrc = (pexTrimCurve *) pData;
	    pData += sizeof (pexTrimCurve);

	    trimDest->visibility = trimSrc->visibility;
	    trimDest->order = trimSrc->order;
	    trimDest->rationality = trimSrc->type;
	    trimDest->approx_method = trimSrc->approxMethod;
	    trimDest->tolerance = trimSrc->tolerance;
	    trimDest->tmin = trimSrc->tMin;
	    trimDest->tmax = trimSrc->tMax;

	    size = NUMBYTES (trimSrc->order + trimSrc->numCoord);
	    trimDest->knots.count = trimSrc->numKnots;
	    trimDest->knots.floats = (float *) PEXAllocBuf ((unsigned) size);
	    COPY_AREA (pData, trimDest->knots.floats, size);
	    pData += size;

	    size = trimSrc->numCoord * ((trimSrc->type == PEXRational) ?
		sizeof (PEXCoord) : sizeof (PEXCoord2D));
	    trimDest->count = trimSrc->numCoord;
	    trimDest->control_points.point =
		(PEXCoord *) PEXAllocBuf ((unsigned) size);
	    COPY_AREA (pData, trimDest->control_points.point, size);
	    pData += size;
	}
    }

    *ocSrc = pData;
}


void _PEXDecodeCellArray (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexCellArray	*oc = (pexCellArray *) *ocSrc;
    int			size;

    ocDest->data.CellArray.point1.x = oc->point1.x;
    ocDest->data.CellArray.point1.y = oc->point1.y;
    ocDest->data.CellArray.point1.z = oc->point1.z;
    ocDest->data.CellArray.point2.x = oc->point2.x;
    ocDest->data.CellArray.point2.y = oc->point2.y;
    ocDest->data.CellArray.point2.z = oc->point2.z;
    ocDest->data.CellArray.point3.x = oc->point3.x;
    ocDest->data.CellArray.point3.y = oc->point3.y;
    ocDest->data.CellArray.point3.z = oc->point3.z;
    ocDest->data.CellArray.col_count = oc->dx;
    ocDest->data.CellArray.row_count = oc->dy;

    size = oc->dx * oc->dy * sizeof (pexTableIndex);
    ocDest->data.CellArray.color_indices =
	(PEXTableIndex *) PEXAllocBuf ((unsigned) size);
    COPY_AREA ((oc + 1), ocDest->data.CellArray.color_indices, size);

    *ocSrc += (sizeof (pexCellArray) + PADDED_BYTES (size));
}


void _PEXDecodeCellArray2D (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexCellArray2D	*oc = (pexCellArray2D *) *ocSrc;
    int			size;

    ocDest->data.CellArray2D.point1.x = oc->point1.x;
    ocDest->data.CellArray2D.point1.y = oc->point1.y;
    ocDest->data.CellArray2D.point2.x = oc->point2.x;
    ocDest->data.CellArray2D.point2.y = oc->point2.y;
    ocDest->data.CellArray2D.col_count = oc->dx;
    ocDest->data.CellArray2D.row_count = oc->dy;

    size = oc->dx * oc->dy * sizeof (pexTableIndex);
    ocDest->data.CellArray2D.color_indices =
	(PEXTableIndex *) PEXAllocBuf ((unsigned) size);
    COPY_AREA ((oc + 1), ocDest->data.CellArray2D.color_indices, size);

    *ocSrc += (sizeof (pexCellArray2D) + PADDED_BYTES (size));
}


void _PEXDecodeExtendedCellArray (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexExtCellArray	*oc = (pexExtCellArray *) *ocSrc;
    int			size;

    ocDest->data.ExtendedCellArray.point1.x = oc->point1.x;
    ocDest->data.ExtendedCellArray.point1.y = oc->point1.y;
    ocDest->data.ExtendedCellArray.point1.z = oc->point1.z;
    ocDest->data.ExtendedCellArray.point2.x = oc->point2.x;
    ocDest->data.ExtendedCellArray.point2.y = oc->point2.y;
    ocDest->data.ExtendedCellArray.point2.z = oc->point2.z;
    ocDest->data.ExtendedCellArray.point3.x = oc->point3.x;
    ocDest->data.ExtendedCellArray.point3.y = oc->point3.y;
    ocDest->data.ExtendedCellArray.point3.z = oc->point3.z;
    ocDest->data.ExtendedCellArray.col_count = oc->dx;
    ocDest->data.ExtendedCellArray.row_count = oc->dy;
    ocDest->data.ExtendedCellArray.color_type = oc->colorType;

    size = oc->dx * oc->dy * NUMBYTES (GetColorLength (oc->colorType));
    ocDest->data.ExtendedCellArray.colors.indexed = 
	(PEXColorIndexed *) PEXAllocBuf ((unsigned) size);
    COPY_AREA ((oc + 1), ocDest->data.ExtendedCellArray.colors.indexed, size);

    *ocSrc += (sizeof (pexExtCellArray) + size);
}


void _PEXDecodeGDP (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexGdp	*oc = (pexGdp *) *ocSrc;
    char	*pData;
    int		size;

    ocDest->data.GDP.gdp_id = oc->gdpId;
    ocDest->data.GDP.count = oc->numPoints;
    ocDest->data.GDP.length = oc->numBytes;

    size = oc->numPoints * sizeof (PEXCoord);
    ocDest->data.GDP.points = (PEXCoord *) PEXAllocBuf ((unsigned) size);

    pData = (char *) (oc + 1);
    COPY_AREA (pData, ocDest->data.GDP.points, size);
    pData += size;

    ocDest->data.GDP.data = (char *) PEXAllocBuf ((unsigned) oc->numBytes);
    COPY_AREA (pData, ocDest->data.GDP.data, oc->numBytes);

    *ocSrc = (pData + PADDED_BYTES (oc->numBytes));
}


void _PEXDecodeGDP2D (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexGdp2D	*oc = (pexGdp2D *) *ocSrc;
    char	*pData;
    int		size;

    ocDest->data.GDP2D.gdp_id = oc->gdpId;
    ocDest->data.GDP2D.count = oc->numPoints;
    ocDest->data.GDP2D.length = oc->numBytes;

    size = oc->numPoints * sizeof (PEXCoord2D);
    ocDest->data.GDP2D.points = (PEXCoord2D *) PEXAllocBuf ((unsigned) size);

    pData = (char *) (oc + 1);
    COPY_AREA (pData, ocDest->data.GDP2D.points, size);
    pData += size;

    ocDest->data.GDP2D.data = (char *) PEXAllocBuf ((unsigned) oc->numBytes);
    COPY_AREA (pData, ocDest->data.GDP2D.data, oc->numBytes);

    *ocSrc = (pData + PADDED_BYTES (oc->numBytes));
}


void _PEXDecodeNoop (float_format, ocSrc, ocDest)

int		float_format;
char		**ocSrc;
PEXOCData	*ocDest;

{
    pexNoop	*oc = (pexNoop *) *ocSrc;

    *ocSrc = (char *) (oc + 1);
}
