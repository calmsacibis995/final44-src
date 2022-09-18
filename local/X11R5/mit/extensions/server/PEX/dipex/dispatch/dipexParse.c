/* $XConsortium: dipexParse.c,v 5.1 91/02/16 09:56:41 rws Exp $ */

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
#include "PEXproto.h"
#include "Xproto.h"
#include "misc.h"
#include "dixstruct.h"
#include "dix.h"
#include "pexError.h"
#include "pexSwap.h"

extern RequestFunction set_tables[];
extern pexContext * InitPexClient();

/*++    pexErrorHandler
 --*/

ErrorCode
pexErrorHandler(client, err)
    ClientPtr client;
    ErrorCode	err;
{
    ErrorF( "PEX Error %d Detected.  Continuing...\n", err);
/*
 * The following code is snitched from Dispatch
    if (client->noClientException != Success)
	CloseDownClient(client);
    else
	Oops(client, 0, err);
*/
/*
 * used to do this	
 */
    return(err);
 
} /* end-pexErrorHandler() */


/*++    ProcPEXDispatch
 */

ProcPEXDispatch( client )
ClientPtr client;
{
    XID		pexId;
    pexContext	*cntxtPtr;
    CARD8	op;
    ErrorCode  err = Success;

    REQUEST( xReq );

    pexId = PEXID( client, PEXCONTEXTTABLE );
    cntxtPtr = (pexContext *)LookupIDByType(pexId, PEXContextType);
      
    if( !cntxtPtr ) {

	if (!(cntxtPtr = InitPexClient(client))) return (BadAlloc);

    }

    op  = ((pexReq *)stuff)->opcode;

    if ((op >= PEX_GetExtensionInfo) && (op <= PEXMaxRequest)) {

	if (!(err = set_tables[op](cntxtPtr, stuff))) {
	    cntxtPtr->current_req = (pexReq *)stuff;
	    err = cntxtPtr->pexRequest[ op ]( cntxtPtr, stuff ); }

    } else {
	err = BadRequest;
    }

    return( err );

}


/*++	PEXRequestUnused -- stub for unimplemented requests
 --*/
ErrorCode
PEXRequestUnused(context)
pexContext      	*context;
{
ErrorCode	err = PEX_ERROR_CODE(BadRequest);
return ( err );

} /* end-PEXRequestUnused */
