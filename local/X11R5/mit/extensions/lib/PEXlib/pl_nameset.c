/* $XConsortium: pl_nameset.c,v 1.4 92/08/26 13:06:10 mor Exp $ */

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


PEXNameSet
PEXCreateNameSet (display)

INPUT Display		*display;

{
    pexCreateNameSetReq	*req;
    PEXNameSet		ns;


    /*
     * Get a nameset resource id from X.
     */

    ns = XAllocID (display);


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (CreateNameSet, req);
    req->id = ns;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (ns);
}


void
PEXFreeNameSet (display, ns)

INPUT Display		*display;
INPUT PEXNameSet	ns;

{
    pexFreeNameSetReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (FreeNameSet, req);
    req->id = ns;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXCopyNameSet (display, srcNs, destNs)

INPUT Display		*display;
INPUT PEXNameSet	srcNs;
INPUT PEXNameSet	destNs;

{
    pexCopyNameSetReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (CopyNameSet, req);
    req->src = srcNs;
    req->dst = destNs;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


Status
PEXGetNameSet (display, ns, numNamesReturn, namesReturn)

INPUT Display		*display;
INPUT PEXNameSet	ns;
OUTPUT unsigned long	*numNamesReturn;
OUTPUT PEXName		**namesReturn;

{
    pexGetNameSetReq	*req;
    pexGetNameSetReply	rep;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetReq (GetNameSet, req);
    req->id = ns;

    if (_XReply (display,  &rep, 0, xFalse) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
	*numNamesReturn = 0;
	*namesReturn = NULL;
	return (0); 		/* return an error */
    }

    *numNamesReturn = rep.numNames;


    /*
     * Allocate a buffer for the replies to pass back to the user.
     */

    *namesReturn = (PEXName *) PEXAllocBuf ((unsigned) (rep.length << 2));

    if (rep.numNames)
        _XRead (display, (char *) *namesReturn, (long) (rep.length << 2));


   /*
    * Done, so unlock and check for synchronous-ness.
    */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (1);
}


void
PEXChangeNameSet (display, ns, action, numValues, values)

INPUT Display		*display;
INPUT PEXNameSet	ns;
INPUT int		action;
INPUT unsigned long	numValues;
INPUT PEXName		*values;

{
    pexChangeNameSetReq	*req;
    int			size;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    size = numValues * sizeof (PEXName);

    PEXGetReqExtra (ChangeNameSet, size, req);
    req->ns = ns;
    req->action = action;

    COPY_AREA ((char *) values, ((char *) &req[1]), size);


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}
