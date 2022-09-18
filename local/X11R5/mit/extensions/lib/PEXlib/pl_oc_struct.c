/* $XConsortium: pl_oc_struct.c,v 1.5 92/08/26 13:06:15 mor Exp $ */

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
PEXExecuteStructure (display, resource_id, req_type, structure)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT PEXStructure	structure;

{
    PEXAddSimpleOC (display, resource_id, req_type, PEXOCExecuteStructure,
	sizeof (PEXStructure), &structure);
}


void
PEXLabel (display, resource_id, req_type, label)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT long		label;

{
    PEXAddSimpleOC (display, resource_id, req_type, PEXOCLabel,
	sizeof (INT32), &label);
}


void
PEXNoop (display, resource_id, req_type)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;

{
    PEXAddSimpleOC (display, resource_id, req_type, PEXOCNoop, 0, NULL);
}


void
PEXApplicationData (display, resource_id, req_type, length, data)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT int		length;
INPUT char		*data;

{
    PEXAddListOC (display, resource_id, req_type, PEXOCApplicationData,
	True /* count needed */,
	length, sizeof (char), data);
}


void
PEXGSE (display, resource_id, req_type, id, length, data)

INPUT Display		*display;
INPUT XID		resource_id;
INPUT PEXOCRequestType	req_type;
INPUT long		id;
INPUT int		length;
INPUT char		*data;

{
    pexGse		*pReq;


    /*
     * Initialize the OC request.
     */

    PEXInitOC (display, resource_id, req_type, PEXOCGSE,
	LENOF (pexGse), NUMWORDS (length), pexGse, pReq);

    if (pReq == NULL) return;


    /* 
     * Store the GSE request header data. 
     */

    pReq->id = id;
    pReq->numElements = length;


    /*
     * Copy the GSE data to the oc.
     */

    _PEXCopyPaddedBytesToOC (display, length, (char *) data);

    PEXFinishOC (display);
    PEXSyncHandle (display);
}
