/* $XConsortium: OCattr.h,v 5.1 91/02/16 09:57:23 rws Exp $ */

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

LOCAL_FLAG ErrorCode
	SwapPEXMarkerType (),
	SwapPEXMarkerScale (),
	SwapPEXMarkerColourIndex (),
	SwapPEXMarkerBundleIndex (),
	SwapPEXAtextStyle (),
	SwapPEXTextPrecision (),
	SwapPEXCharExpansion (),
	SwapPEXCharSpacing (),
	SwapPEXCharHeight (),
	SwapPEXCharUpVector (),
	SwapPEXTextPath (),
	SwapPEXTextAlignment (),
	SwapPEXLineType (),
	SwapPEXLineWidth (),
	SwapPEXLineColourIndex (),
	SwapPEXCurveApproximation (),
	SwapPEXPolylineInterp (),
	SwapPEXInteriorStyle (),
	SwapPEXSurfaceColourIndex (),
	SwapPEXSurfaceReflModel (),
	SwapPEXSurfaceInterp (),
	SwapPEXSurfaceApproximation (),
	SwapPEXCullingMode (),
	SwapPEXDistinguishFlag (),
	SwapPEXPatternSize (),
	SwapPEXPatternRefPt (),
	SwapPEXPatternAttr (),
	SwapPEXSurfaceEdgeFlag (),
	SwapPEXSurfaceEdgeType (),
	SwapPEXSurfaceEdgeWidth (),
	SwapPEXSetAsfValues (),
	SwapPEXLocalTransform (),
	SwapPEXLocalTransform2D (),
	SwapPEXGlobalTransform (),
	SwapPEXGlobalTransform2D (),
	SwapPEXModelClip (),
	SwapPEXRestoreModelClip (),
	SwapPEXLightState (),
	SwapPEXPickId (),
	SwapPEXHlhsrIdentifier (),
	SwapPEXExecuteStructure (),
	SwapPEXLabel (),
	SwapPEXApplicationData (),
	SwapPEXGse (),
	SwapPEXRenderingColourModel (),
	SwapPEXOCUnused ();

LOCAL_FLAG unsigned char * SwapCoord4DList ();
LOCAL_FLAG unsigned char * SwapCoord3DList ();
LOCAL_FLAG unsigned char * SwapCoord2DList ();
LOCAL_FLAG unsigned char * SwapColour ();
LOCAL_FLAG unsigned char * SwapOptData();
LOCAL_FLAG unsigned char * SwapVertex();
LOCAL_FLAG unsigned char * SwapTrimCurve();

LOCAL_FLAG void
	SwapSurfaceApprox(),
	SwapHalfSpace (),
	SwapHalfSpace2D ();
	
