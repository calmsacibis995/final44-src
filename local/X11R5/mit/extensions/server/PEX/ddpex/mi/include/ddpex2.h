/* $XConsortium: ddpex2.h,v 5.1 91/02/16 09:54:51 rws Exp $ */

/***********************************************************
Copyright 1990, 1991 by Sun Microsystems, Inc. and the X Consortium.

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

#ifndef DDPEX2_H
#define DDPEX2_H 1

#include "miRender.h"

/*
No!  this is just the same as miGenericStr
typedef	struct {
	ddUSHORT	ocNumber;
	ddUSHORT	pexOCLength;
} ddGenericOCStr, *ddGenericOCPtr;
*/

typedef listofColour miColourStruct;

typedef miListHeader	miMarkerStruct;

typedef struct {
    ddCoord3D          *pOrigin;	/* origin of the string */
    ddCoord3D          *pDirections;	/* 2 orientation vectors */
    ddUSHORT            numEncodings;   /* # of mono encodings */
    pexMonoEncoding    *pText;		/* text strings */
} miTextStruct;

typedef struct {
    ddCoord2D          *pOrigin;  /* origin of the string */
    ddUSHORT            numEncodings;   /* # of mono encodings */
    pexMonoEncoding    *pText;		/* text strings */
} miText2DStruct;

typedef struct {
    ddCoord3D          *pOrigin;  /* origin of the string */
    ddCoord3D          *pOffset;  /* offset */
    ddUSHORT            numEncodings;   /* # of mono encodings */
    pexMonoEncoding    *pText;		/* text string */
} miAnnoTextStruct;

typedef struct {
    ddCoord2D          *pOrigin;  /* origin of the string */
    ddCoord2D          *pOffset;  /* offset */
    ddUSHORT            numEncodings;   /* # of mono encodings */
    pexMonoEncoding    *pText;		/* text string */
} miAnnoText2DStruct;

typedef miListHeader	miPolylineStruct;

typedef struct {
    ddUSHORT	    order;	/* curve order */
    ddFLOAT	    uMin;
    ddFLOAT	    uMax;
    ddUSHORT	    numKnots;
    ddFLOAT	    *pKnots;
    ddListBounds    bounds;
    miListHeader    points;
} miNurbStruct;

typedef struct {
    ddUSHORT	    shape;
    ddUCHAR	    ignoreEdges;
    ddUCHAR	    contourHint;
    listofddFacet   *pFacets;
    ddListBounds    bounds;
    miListHeader    points;
} miFillAreaStruct;

typedef struct {
    ddUSHORT	numLists;
    ddUSHORT	maxData;
    ddUSHORT	*pConnects;
} miConnList;

typedef struct {
    ddUSHORT	numLists;
    ddUSHORT	maxData;
    miConnList	*pConnLists;
} miConnListList;

typedef struct {
    ddUSHORT	    numListLists;
    ddUSHORT	    maxData;
    miConnListList *data;
} miConnHeader;

typedef struct {
    ddUSHORT	    shape;
    ddUSHORT	    edgeAttribs;
    ddUCHAR	    contourHint;
    ddUCHAR	    contourCountsFlag;
    ddUSHORT	    numFAS;
    ddUSHORT	    numEdges;
    ddUCHAR	    *edgeData;
    listofddFacet   pFacets;
    ddListBounds    bounds;
    miListHeader    points;
    miConnHeader    connects;
} miSOFASStruct;

typedef struct {
    listofddFacet   *pFacets;
    ddListBounds    bounds;
    miListHeader    points;
} miTriangleStripStruct;

typedef struct {
    ddUSHORT	    mPts;
    ddUSHORT	    nPts;
    ddUSHORT	    shape;
    listofddFacet   *pFacets;
    ddListBounds    bounds;
    miListHeader    points;
} miQuadMeshStruct;

typedef struct {
    ddUSHORT	    uOrder;
    ddUSHORT	    vOrder;
    ddUSHORT	    mPts;
    ddUSHORT	    nPts;
    ddULONG	    numUknots;
    ddFLOAT	    *pUknots;
    ddULONG	    numVknots;
    ddFLOAT	    *pVknots;
    miListHeader    points;
    ddULONG	    numTrimCurveLists;
    listofTrimCurve *trimCurves;
} miNurbSurfaceStruct;


typedef struct {
    ddEnumTypeIndex	type;
    union {
	char			    *pNone;
	char			    *pImpDep;
	ddPSC_IsoparametricCurves   *pIsoCurves;
	ddPSC_LevelCurves	    *pMcLevelCurves;
	ddPSC_LevelCurves	    *pWcLevelCurves;
    } data;
} miPSurfaceCharsStruct;

typedef struct {
    listofObj       *enableList;
    listofObj       *disableList;
} miLightStateStruct;

typedef struct {
    ddUSHORT		operator;
    listofObj		*halfspaces;
} miMCVolume_Struct;

typedef struct {
    ddULONG	    dx;
    ddULONG	    dy;
    ddListBounds    bounds;
    miListHeader    point;
    listofColour    colours;
} miCellArrayStruct;


typedef struct {
    ddULONG	    GDPid;
    ddULONG	    numBytes;
    miListHeader    points;
    ddPointer	    pData;
} miGdpStruct;


#endif
