/* $XConsortium: pexNs.c,v 5.2 92/12/01 17:17:57 hersh Exp $ */

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


#include "X.h"
#include "Xproto.h"
#include "pexError.h"
#include "PEXproto.h"
#include "dipex.h"
#include "pexLookup.h"

#ifdef min
#undef min
#endif
 
#ifdef max
#undef max
#endif



/*++	PEXCreateNameSet
 --*/
ErrorCode
PEXCreateNameSet (cntxtPtr, strmPtr)
pexContext              *cntxtPtr;
pexCreateNameSetReq     *strmPtr;
{
    ErrorCode err = Success;
    ErrorCode FreeNameSet (), CreateNameSet ();
    diNSHandle nsptr;

    if (!LegalNewID(strmPtr->id, cntxtPtr->client))
	PEX_ERR_EXIT(BadIDChoice,strmPtr->id,cntxtPtr);


    nsptr = (diNSHandle) Xalloc ((unsigned long)sizeof(ddNSResource));
    if (!nsptr) PEX_ERR_EXIT(BadAlloc,0,cntxtPtr);
    nsptr->id = strmPtr->id;
    err = CreateNameSet(nsptr);
    if (err) Xfree((pointer)nsptr);

    ADDRESOURCE(strmPtr->id, PEXNameType, nsptr);

    return( err );

} /* end-PEXCreateNameSet() */

/*++	PEXCopyNameSet
 --*/
ErrorCode
PEXCopyNameSet (cntxtPtr, strmPtr)
pexContext              *cntxtPtr;
pexCopyNameSetReq       *strmPtr;
{
    ErrorCode err = Success;
    diNSHandle nsrc = 0, ndst = 0;

    LU_NAMESET(strmPtr->src, nsrc);
    LU_NAMESET(strmPtr->dst, ndst);

    err = CopyNameSet (nsrc, ndst);
    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);
    return( err );

} /* end-PEXCopyNameSet() */

/*++	PEXFreeNameSet
 --*/
ErrorCode
PEXFreeNameSet (cntxtPtr, strmPtr)
pexContext              *cntxtPtr;
pexFreeNameSetReq       *strmPtr;
{
    ErrorCode err = Success;
    diNSHandle pns = 0;

    if ((strmPtr == NULL) || (strmPtr->id == 0)) {
	err = PEX_ERROR_CODE(PEXNameSetError);
	PEX_ERR_EXIT(err,0,cntxtPtr);
    }

    LU_NAMESET(strmPtr->id, pns);

    FreeResource(strmPtr->id, RT_NONE);

    return(err);

} /* end-PEXFreeNameSet() */

/*++	PEXGetNameSet
 --*/
ErrorCode
PEXGetNameSet( cntxtPtr, strmPtr )
pexContext      	*cntxtPtr;
pexGetNameSetReq    	*strmPtr;
{
    ErrorCode err = Success;
    diNSHandle pns;
    extern ddBufferPtr pPEXBuffer;
    CARD32 numNames;

    LU_NAMESET(strmPtr->id, pns);

    SETUP_INQ(pexGetNameSetReply);

    err = InquireNameSet (pns, &numNames, pPEXBuffer);
    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);

    {
	SETUP_VAR_REPLY(pexGetNameSetReply);
	reply->numNames = numNames;
	WritePEXBufferReply(pexGetNameSetReply);
    }
    return( err );

} /* end-PEXGetNameSet() */

/*++	PEXChangeNameSet
 --*/
ErrorCode
PEXChangeNameSet( cntxtPtr, strmPtr )
pexContext      	*cntxtPtr;
pexChangeNameSetReq    	*strmPtr;
{
    ErrorCode err = Success;
    diNSHandle pns = 0;

    LU_NAMESET(strmPtr->ns, pns);

    err = ChangeNameSet(    pns, strmPtr->action, 
			    (strmPtr->length - (sizeof(pexChangeNameSetReq)
				/ sizeof(pexNameSet))),
			    (ddULONG *)(strmPtr + 1));
    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);
    return( err );

} /* end-PEXChangeNameSet() */
/*++
 *
 * 	End of File
 --*/
