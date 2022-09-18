/* $XConsortium: pl_sc.c,v 1.7 92/08/26 13:06:21 mor Exp $ */

/******************************************************************************
Copyright 1987,1991 by Digital Equipment Corporation, Maynard, Massachusetts
Copyright 1992 by ShoGraphics, Inc., Mountain View, California
Copyright 1992 by the Massachusetts Institute of Technology

                        All Rights Reserved

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that copyright
notice and this permission notice appear in supporting documentation, and that
the name of Digital, ShowGraphics, or M.I.T. not be used in advertising or
publicity pertaining to distribution of the software without specific, written
prior permission.  Digital, ShowGraphics, and M.I.T. make no representations
about the suitability of this software for any purpose.  It is provided "as is"
without express or implied warranty.

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

SHOGRAPHICS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
SHOGRAPHICS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.
*************************************************************************/

#include "PEXlib.h"
#include "PEXlibint.h"

static void _PEXGenerateSCList();


PEXSearchContext
PEXCreateSearchContext (display, valueMask, values)

INPUT Display		*display;
INPUT unsigned long	valueMask;
INPUT PEXSCAttributes	*values;

{
    pexCreateSearchContextReq	*req;
    PEXSearchContext		id;
    int				convertFP;


    /*
     * Get a search context resource id from X.
     */

    id = XAllocID (display);


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetFPReq (CreateSearchContext, req, convertFP);
    req->sc = id;
    req->itemMask = valueMask;

    _PEXGenerateSCList (display, (pexReq *) req, valueMask, values);


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (id);
}


void
PEXFreeSearchContext (display, sc)

INPUT Display		*display;
INPUT PEXSearchContext	sc;

{
    pexFreeSearchContextReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (FreeSearchContext, req);
    req->id = sc;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXCopySearchContext (display, valueMask, srcSc, destSc)

INPUT Display		*display;
INPUT unsigned long	valueMask;
INPUT PEXSearchContext	srcSc;
INPUT PEXSearchContext	destSc;

{
    pexCopySearchContextReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (CopySearchContext, req);
    req->src = srcSc;
    req->dst = destSc;
    req->itemMask = valueMask;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


PEXSCAttributes *
PEXGetSearchContext (display, sc, valueMask)

INPUT Display		*display;
INPUT PEXSearchContext	sc;
INPUT unsigned long	valueMask;

{
    pexGetSearchContextReply	rep;
    pexGetSearchContextReq	*req;
    PEXSCAttributes		*scattr;
    unsigned long		*pv, f;
    int				tmp, i;
    int				convertFP;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetFPReq (GetSearchContext, req, convertFP);
    req->sc = sc;
    req->itemMask = valueMask;

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
	UnlockDisplay (display);
  	PEXSyncHandle (display);
 	return (NULL);               /* return an error */
    }


    /*
     * Allocate a scratch buffer and copy the reply data to the buffer.
     */

    pv = (unsigned long *) _XAllocScratch (display,
	(unsigned long) (rep.length << 2));

    _XRead (display, (char *) pv, (long) (rep.length << 2));


    /*
     * Allocate a buffer for the replies to pass back to the client.
     */

    scattr = (PEXSCAttributes *)
	PEXAllocBuf ((unsigned) (sizeof (PEXSCAttributes)));

    scattr->start_path.count = 0;
    scattr->start_path.elements = NULL;
    scattr->normal.count = 0;
    scattr->normal.pairs = NULL;
    scattr->inverted.count = 0;
    scattr->inverted.pairs = NULL;

    for (i = 0; i < (PEXSCMaxShift + 1); i++)
    {
	f = (1L << i);
	if (valueMask & f)
	{
	    switch (f)
	    {
	    case PEXSCPosition:
		scattr->position = *((PEXCoord *) pv);
		pv = (unsigned long *) ((char *) pv + sizeof (PEXCoord));
	  	break;
	    case PEXSCDistance:
		scattr->distance = *((float *) pv);
		pv = (unsigned long *) ((char *) pv + sizeof (float));
		break;
	    case PEXSCCeiling:
		scattr->ceiling = *pv;
		pv++;
		break;
	    case PEXSCModelClipFlag:
		scattr->model_clip_flag = *pv;
		pv++;
		break;
	    case PEXSCStartPath:
		tmp = *pv;
		pv++;
		scattr->start_path.count = tmp;
		tmp *= sizeof (PEXElementRef);
		scattr->start_path.elements =
		    (PEXElementRef *) PEXAllocBuf ((unsigned) tmp);
		COPY_AREA ((char *) pv,
		    (char *) (scattr->start_path.elements), tmp);
		pv = (unsigned long *) ((char *) pv + tmp);
		break;
	    case PEXSCNormalList:
		tmp = *pv;
		pv++;
		scattr->normal.count = tmp;
		tmp *= sizeof (PEXNameSetPair);
		scattr->normal.pairs =
		    (PEXNameSetPair *) PEXAllocBuf ((unsigned) tmp);
		COPY_AREA ((char *) pv, (char *) (scattr->normal.pairs), tmp);
		pv = (unsigned long *) ((char *) pv + tmp);
		break;
	    case PEXSCInvertedList:
		tmp = *pv;
		pv++;
		scattr->inverted.count = tmp;
		tmp *= sizeof (PEXNameSetPair);
		scattr->inverted.pairs =
		    (PEXNameSetPair *) PEXAllocBuf ((unsigned) tmp);
		COPY_AREA ((char *) pv,
		    (char *) (scattr->inverted.pairs), tmp);
		pv = (unsigned long *) ((char *) pv + tmp);
		break;
	    }
	}
    }


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (scattr);
}


void
PEXChangeSearchContext (display, sc, valueMask, values)

INPUT Display		*display;
INPUT PEXSearchContext	sc;
INPUT unsigned long	valueMask;
OUTPUT PEXSCAttributes	*values;

{
    pexChangeSearchContextReq	*req;
    int				convertFP;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetFPReq (ChangeSearchContext, req, convertFP);
    req->sc = sc;
    req->itemMask = valueMask;

    _PEXGenerateSCList (display, (pexReq *) req, valueMask, values);


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


Status
PEXSearchNetwork (display, sc, path_return)

INPUT Display			*display;
INPUT PEXSearchContext		sc;
OUTPUT PEXStructurePath		**path_return;

{
    pexSearchNetworkReply	rep;
    pexSearchNetworkReq		*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetReq (SearchNetwork, req);
    req->id = sc;

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
	*path_return = NULL;
        return (0);               /* return an error */
    }


    /*
     * Allocate a buffer for the path to pass back to the client.
     */

    *path_return = (PEXStructurePath *)
	PEXAllocBuf ((unsigned) (sizeof (PEXStructurePath)));

    (*path_return)->count = rep.numItems;
    (*path_return)->elements = (PEXElementRef *)
	PEXAllocBuf ((unsigned) (rep.numItems * sizeof (PEXElementRef)));

    _XRead (display, (char *) ((*path_return)->elements),
	(long) (rep.length << 2));


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (1);
}


/*
 * Routine to write a packed list of SC attributes into the transport buf.
 */

static void
_PEXGenerateSCList (display, req, valueMask, values)

INPUT Display		*display;
INPUT pexReq		*req;
INPUT unsigned long	valueMask;
INPUT PEXSCAttributes	*values;

{
    CARD32		*pv;
    CARD32		*pvSend;
    unsigned long       f;
    int			length, tmp, i;


    /*
     * It's not worth the time of determining exactly how much
     * scratch space to allocate, so assume worse case.
     */

    f = sizeof (PEXCoord) +
	sizeof (float) +
	(5 * sizeof (CARD32)) +
	(sizeof (PEXElementRef) * ((valueMask & PEXSCStartPath) ?
	    values->start_path.count : 0)) +
	(sizeof (PEXNameSetPair) * ((valueMask & PEXSCNormalList) ?
	    values->normal.count : 0)) +
	(sizeof (PEXNameSetPair) * ((valueMask & PEXSCInvertedList) ?
	    values->inverted.count : 0));

    pv = pvSend = (CARD32 *) _XAllocScratch (display, (unsigned long) f);

    for (i = 0; i < (PEXSCMaxShift + 1); i++)
    {
	f = (1L << i);
	if (valueMask & f)
	{
	    switch (f)
	    {
	    case PEXSCPosition:
		*((PEXCoord *) pv) = values->position;
		pv = (CARD32 *) ((char *) pv + sizeof (PEXCoord));
		break;
	    case PEXSCDistance:
		*((float *) pv) = values->distance;
		pv = (CARD32 *) ((char *) pv + sizeof (float));
		break;
	    case PEXSCCeiling:
		*pv = values->ceiling;
		pv++;
		break;
            case PEXSCModelClipFlag:
		*pv = values->model_clip_flag;
		pv++;
		break;
	    case PEXSCStartPath:
		tmp = *((CARD32 *) pv) = values->start_path.count;
		pv++;
		tmp *= sizeof (PEXElementRef);
		COPY_AREA ((char *) (values->start_path.elements),
		    (char *) pv, tmp);
		pv = (CARD32 *) ((char *) pv + tmp);
		break;
	    case PEXSCNormalList:
		tmp = *((CARD32 *) pv) = values->normal.count;
		pv++;
		tmp *= sizeof (PEXNameSetPair);
		COPY_AREA ((char *) (values->normal.pairs), (char *) pv, tmp);
		pv = (CARD32 *) ((char *) pv + tmp);
		break;
	    case PEXSCInvertedList:
		tmp = *((CARD32 *) pv) = values->inverted.count;
		pv++;
		tmp *= sizeof (PEXNameSetPair);
		COPY_AREA ((char *) (values->inverted.pairs),
		    (char *) pv, tmp);
		pv = (CARD32 *) ((char *) pv + tmp);
		break;
	    }
	}
    }

    length = pv - pvSend;
    req->length += length;

    Data (display, (char *) pvSend, (length << 2));
}
