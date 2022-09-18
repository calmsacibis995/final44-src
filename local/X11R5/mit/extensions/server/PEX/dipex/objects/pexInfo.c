/* $XConsortium: pexInfo.c,v 5.2 92/03/04 14:16:15 hersh Exp $ */

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


/*++    pexInfo.c
 *
 *	Contents:   PEXGetExtensionInfo
 *		    PEXGetEnumeratedTypeInfo
 *		    PEXGetImpDepConstants
 *		    PEXMatchRendererTargets
 *		    PEXEscape
 *		    PEXEscapeWithReply
 *
 --*/

#include "X.h"
#include "Xproto.h"
#include "pex_site.h"
#include "PEX.h"
#include "dipex.h"
#include "pexError.h"
#include "pexLookup.h"
#include "pexExtract.h"
#ifdef min
#undef min
#endif
 
#ifdef max
#undef max
#endif


/*++	PEXGetExtensionInfo
 *
 * The client_protocol_major_version and the 
 * client_protocol_minor_version indicate what 
 * version of the protocol the client expects the 
 * server to implement. 
 --*/

ErrorCode
PEXGetExtensionInfo( cntxtPtr, strmPtr )
pexContext		*cntxtPtr;
pexGetExtensionInfoReq	*strmPtr;
{
    ErrorCode err = Success;
    extern ddBuffer *pPEXBuffer;
    pexGetExtensionInfoReply *reply =
				   (pexGetExtensionInfoReply *)pPEXBuffer->pHead;

    reply->majorVersion = PEX_PROTO_MAJOR;
    reply->minorVersion = PEX_PROTO_MINOR;
    reply->release = PEX_RELEASE_NUMBER;
    reply->lengthName = strlen(PEX_VENDOR);
    reply->length = LWORDS(reply->lengthName);
    reply->subsetInfo = PEX_SUBSET;
    bcopy(PEX_VENDOR, (char *)(reply+1), (int)(reply->lengthName));

    WritePEXReplyToClient(  cntxtPtr, strmPtr,
			    sizeof(pexGetExtensionInfoReply) + reply->lengthName,
			    reply);

    return( err );

} /* end-PEXGetExtensionInfo() */

/*++	PEXGetEnumeratedTypeInfo
 --*/

ErrorCode
PEXGetEnumeratedTypeInfo( cntxtPtr, strmPtr )
pexContext			*cntxtPtr;
pexGetEnumeratedTypeInfoReq	*strmPtr;
{
    ErrorCode err = Success;
    DrawablePtr d;
    extern ddBuffer *pPEXBuffer;
    ddULONG numLists;

    LU_DRAWABLE (strmPtr->drawable, d);

    SETUP_INQ(pexGetEnumeratedTypeInfoReply);

    err = InquireEnumTypeInfo(	d, strmPtr->itemMask, strmPtr->numEnums,
				(ddUSHORT *)(strmPtr+1), &numLists, pPEXBuffer);
    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);
			
    {
	SETUP_VAR_REPLY(pexGetEnumeratedTypeInfoReply);
	reply->numLists = numLists;
	WritePEXBufferReply(pexGetEnumeratedTypeInfoReply);
    }
    return( err );

} /* end-PEXGetEnumeratedTypeInfo() */

/*++	PEXGetImpDepConstants
 --*/

ErrorCode
PEXGetImpDepConstants( cntxtPtr, strmPtr )
pexContext			*cntxtPtr;
pexGetImpDepConstantsReq	*strmPtr;
{
    ErrorCode err = Success;
    DrawablePtr d;
    extern ddBuffer *pPEXBuffer;

    LU_DRAWABLE (strmPtr->drawable, d);

    SETUP_INQ(pexGetImpDepConstantsReply);

    err = InquireImpDepConstants(   d, strmPtr->numNames, 
				    (ddUSHORT *)(strmPtr+1), pPEXBuffer);
    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);

    {
	SETUP_VAR_REPLY(pexGetImpDepConstantsReply);
	WritePEXBufferReply(pexGetImpDepConstantsReply);
    }
    return( err );

} /* end-PEXGetImpDepConstants() */

ErrorCode
PEXMatchRendererTargets( cntxtPtr, strmPtr )
pexContext			*cntxtPtr;
pexMatchRendererTargetsReq      *strmPtr;
{
    ErrorCode err = Success;
    DrawablePtr d;
    extern ddBuffer *pPEXBuffer;

    LU_DRAWABLE (strmPtr->drawable, d);

    /* no way to check visualID besides doing the work of Match */

    SETUP_INQ(pexMatchRendererTargetsReply);

    err = MatchRendererTargets(d, (int)strmPtr->depth, (int)strmPtr->type, 
			   (VisualID)strmPtr->visualID,
			   (int)strmPtr->maxTriplets, pPEXBuffer );
    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);

    {
	SETUP_VAR_REPLY(pexMatchRendererTargetsReply);
	WritePEXBufferReply(pexMatchRendererTargetsReply);
    }
    return( err );

} /* end-PEXMatchRendererTargets() */

ErrorCode
PEXEscape( cntxtPtr, strmPtr )
pexContext		  	*cntxtPtr;
pexEscapeReq	   	 	*strmPtr;
{
    ErrorCode err = Success;
    ddRendererStr *prend = 0;
    pexEscapeSetEchoColourData *ptr;
    CARD8 *pcs;

    ptr = (pexEscapeSetEchoColourData *)(strmPtr + 1);
    pcs = (CARD8 *)(ptr+1); 

    LU_RENDERER(ptr->rdr, prend);

    /* Support the one Registered Escape, Set Echo Color */
    switch (strmPtr->escapeID) {
	case  PEXEscapeSetEchoColour: {
	  EXTRACT_COLOUR_SPECIFIER(prend->echoColour,pcs);
	  break;
	}
    }


    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);

    return( err );

} /* end-PEXEscape() */


ErrorCode
PEXEscapeWithReply( cntxtPtr, strmPtr )
pexContext		  	*cntxtPtr;
pexEscapeWithReplyReq	   	*strmPtr;
{
    ErrorCode err = Success;

    /* Do nothing here, Escape is not implemented in SI 
    */

    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);

    return( err );

} /* end-PEXEscapeWithReply() */
/*++
 *
 *	End of File
 *
 --*/
