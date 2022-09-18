/* $XConsortium: pexRndrPick.c,v 1.8 92/12/14 16:17:44 hersh Exp $ */

/************************************************************
Copyright 1992 by The Massachusetts Institute of Technology

Permission to use, copy, modify, and distribute this
software and its documentation for any purpose and without
fee is hereby granted, provided that the above copyright
notice appear in all copies and that both that copyright
notice and this permission notice appear in supporting
docu- mentation, and that the name of MIT not be used in
advertising or publicity pertaining to distribution of the
software without specific prior written permission.
M.I.T. makes no representation about the suitability of
this software for any purpose. It is provided "as is"
without any express or implied warranty.

MIT DISCLAIMS ALL WARRANTIES WITH REGARD TO  THIS  SOFTWARE,
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FIT-
NESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL MIT BE  LI-
ABLE  FOR  ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,  DATA  OR
PROFITS,  WHETHER  IN  AN  ACTION OF CONTRACT, NEGLIGENCE OR
OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION  WITH
THE USE OR PERFORMANCE OF THIS SOFTWARE.

******************************************************************/



/*++
 *  --- Renderer Picking ---
 *      PEXBeginPickOne
 *      PEXEndPickOne
 *      PEXPickOne
 *      PEXBeginPickAll
 *      PEXEndPickAll
 *      PEXPickAll
 --*/

#include "X.h"
#define NEED_EVENTS
#include "Xproto.h"
#include "pexError.h"
#include "dipex.h"
#include "PEXprotost.h"
#include "pex_site.h"
#include "ddpex3.h"
#include "ddpex4.h"
#include "pexLookup.h"

#ifdef min
#undef min
#endif
 
#ifdef max
#undef max
#endif


/*++  Renderer Picking ++*/

ErrorCode
PEXBeginPickOne( cntxtPtr, strmPtr )
pexContext      	*cntxtPtr;
pexBeginPickOneReq      *strmPtr;
{
    ErrorCode err = Success;
    ddRendererStr *prend = 0;
    pexPickRecord *pr = (pexPickRecord *)(strmPtr+1);
    ddPickPath    *sIDpp;

    LU_RENDERER(strmPtr->rdr, prend);
    LU_DRAWABLE(strmPtr->drawable, prend->pDrawable);
    prend->drawableId = strmPtr->drawable;
    /* this is evil but necessary, use the pickid field of the
       sIDlist to store the structure ID that corresponds to the 
       top level fake structure
    */
    sIDpp = (ddPickPath *)(prend->pickstr.sIDlist)->pList;
    sIDpp->pickid = strmPtr->sid;

    prend->pickstr.pick_method = strmPtr->method;
    prend->pickstr.state = DD_PICK_ONE;
    prend->pickstr.server = DD_CLIENT;

    err = ChangePseudoPickMeasure (prend, pr);
    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);

    /* This is set up to use this instead of defining a BeginPickOne */
    err = BeginPicking(prend, prend->pickstr.pseudoPM);
    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);

    return( err );
} /* end-PEXBeginPickOne() */

ErrorCode
PEXEndPickOne( cntxtPtr, strmPtr )
pexContext      	*cntxtPtr;
pexEndPickOneReq        *strmPtr;
{
    ErrorCode err = Success;
    ddRendererStr *prend = 0;
    extern ddBufferPtr pPEXBuffer;
    pexEndPickOneReply *reply = (pexEndPickOneReply*)(pPEXBuffer->pHead);

    LU_RENDERER(strmPtr->rdr, prend);

    if (prend->pickstr.state != DD_PICK_ONE)
	PEX_ERR_EXIT(PEX_ERROR_CODE(PEXRendererStateError),0,cntxtPtr);

    SETUP_INQ(pexEndPickOneReply);

    err = EndPickOne(prend, pPEXBuffer, &(reply->numPickElRefs),
		     &(reply->pickStatus), &(reply->betterPick));
    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);

    err = EndPicking(prend);
    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);

    {
	reply->length = LWORDS(pPEXBuffer->dataSize);
	WritePEXBufferReply(pexEndPickOneReply);

    }
    return( err );
} /* end-PEXEndPickOne() */

ErrorCode
PEXPickOne( cntxtPtr, strmPtr )
pexContext      	*cntxtPtr;
pexPickOneReq           *strmPtr;
{
    ErrorCode err = Success;
    extern ddBufferPtr pPEXBuffer;
    ddRendererStr *prend = 0;
    pexPickRecord *pr = (pexPickRecord *)(strmPtr+1);
    pexPickOneReply *reply = (pexPickOneReply*)(pPEXBuffer->pHead);

    /* do stuff same as BeginPickOne */
    LU_RENDERER(strmPtr->rdr, prend);
    LU_DRAWABLE(strmPtr->drawable, prend->pDrawable);
    prend->drawableId = strmPtr->drawable;
    LU_STRUCTURE(strmPtr->sid, prend->pickstr.strHandle);

    prend->pickstr.pick_method = strmPtr->method;
    prend->pickstr.state = DD_PICK_ONE;
    prend->pickstr.server = DD_SERVER;

    err = ChangePseudoPickMeasure (prend, pr);
    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);

    err = BeginPicking(prend, prend->pickstr.pseudoPM);
    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);

    /* now call PickOne which does set up and calls the traverser */
    err = PickOne(prend);

    /* now do stuff same as EndPickOne */
    SETUP_INQ(pexPickOneReply);

    err = EndPickOne(prend, pPEXBuffer, &(reply->numPickElRefs),
		     &(reply->pickStatus), &(reply->betterPick));
    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);

    err = EndPicking(prend);
    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);

    {
	reply->length = LWORDS(pPEXBuffer->dataSize);
	WritePEXBufferReply(pexPickOneReply);
    }
    return( err );
} /* end-PEXPickOne() */

ErrorCode
PEXBeginPickAll( cntxtPtr, strmPtr )
pexContext      	*cntxtPtr;
pexBeginPickAllReq      *strmPtr;
{
    ErrorCode err = Success;
    ddRendererStr *prend = 0;
    pexPickRecord *pr = (pexPickRecord *)(strmPtr+1);
    ddPickPath    *sIDpp;

    LU_RENDERER(strmPtr->rdr, prend);
    LU_DRAWABLE(strmPtr->drawable, prend->pDrawable);
    prend->drawableId = strmPtr->drawable;
    /* this is evil but necessary, use the pickid field of the
       sIDlist to store the structure ID that corresponds to the 
       top level fake structure
    */
    sIDpp = (ddPickPath *)(prend->pickstr.sIDlist)->pList;
    sIDpp->pickid = strmPtr->sid;

    prend->pickstr.pick_method = strmPtr->method;
    prend->pickstr.state = DD_PICK_ALL;
    prend->pickstr.server = DD_CLIENT;
    prend->pickstr.send_event = strmPtr->sendEvent;
    prend->pickstr.max_hits = strmPtr->pickMaxHits;
    prend->pickstr.client = cntxtPtr->client;

    err = ChangePseudoPickMeasure (prend, pr);
    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);

    /* This is set up to use this instead of defining a BeginPickOne */
    err = BeginPicking(prend, prend->pickstr.pseudoPM);
    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);


    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);
    return( err );
} /* end-PEXBeginPickAll() */

ErrorCode
PEXEndPickAll( cntxtPtr, strmPtr )
pexContext      	*cntxtPtr;
pexEndPickAllReq        *strmPtr;
{
    ErrorCode err = Success;
    extern ddBufferPtr pPEXBuffer;
    ddRendererStr *prend = 0;

    LU_RENDERER(strmPtr->rdr, prend);

    if (prend->pickstr.state != DD_PICK_ALL)
	PEX_ERR_EXIT(err,0,cntxtPtr);

    SETUP_INQ(pexEndPickAllReply);

    err = EndPickAll(prend, pPEXBuffer);
    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);

    err = EndPicking(prend);
    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);

    {
	SETUP_VAR_REPLY(pexEndPickAllReply);
	WritePEXBufferReply(pexEndPickAllReply);
    }
    return( err );
} /* end-PEXEndPickAll() */

ErrorCode
PEXPickAll( cntxtPtr, strmPtr )
pexContext      	*cntxtPtr;
pexPickAllReq           *strmPtr;
{
    ErrorCode err = Success;
    extern ddBufferPtr pPEXBuffer;
    ddRendererStr *prend = 0;
    pexPickRecord *pr = (pexPickRecord *)(strmPtr+1);

    /* do stuff same as BeginPickAll */
    LU_RENDERER(strmPtr->rdr, prend);
    LU_DRAWABLE(strmPtr->drawable, prend->pDrawable);
    prend->drawableId = strmPtr->drawable;

    prend->pickstr.pick_method = strmPtr->method;
    prend->pickstr.state = DD_PICK_ALL;
    prend->pickstr.server = DD_SERVER;
    prend->pickstr.max_hits = strmPtr->pickMaxHits;

    err = ChangePseudoPickMeasure (prend, pr);
    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);

    err = BeginPicking(prend, prend->pickstr.pseudoPM);
    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);

    /* now call PickAll which does set up and calls RenderElements */
    err = PickAll(prend);

    /* now do stuff same as EndPickOne */
    SETUP_INQ(pexPickAllReply);

    err = EndPickAll(prend, pPEXBuffer);
    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);

    err = EndPicking(prend);
    if (err) PEX_ERR_EXIT(err,0,cntxtPtr);

    {
	SETUP_VAR_REPLY(pexPickAllReply);

	WritePEXBufferReply(pexPickAllReply);
    }
    return( err );
} /* end-PEXPickAll() */


/**** Renderer Pick Events ****/

ErrorCode
PEXMaxHitsReachedNotify(client, rendId)
ClientPtr           client;
ddULONG             rendId;
{
    pexMaxHitsReachedEvent mhre;

    mhre.type = PexEventBase + PEXMaxHitsReached; 
    mhre.sequenceNumber = client->sequence;
    mhre.rdr = rendId;

    WriteEventsToClient (client, 1, (xEvent *) &mhre);
    return(client->noClientException);
}
/*++
 *
 *	End of File
 *
 --*/
