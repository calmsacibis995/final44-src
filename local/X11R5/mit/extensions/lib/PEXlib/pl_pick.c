/* $XConsortium: pl_pick.c,v 1.7 92/08/26 13:06:19 mor Exp $ */

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

/*
 *  NEED EVENTS needs to be defined when including Xproto.h so xEvent can be
 *  sucked in.  Turn it on here in case Xproto.h is grabbed earlier
 */ 

#define NEED_EVENTS

#include <X11/Xlib.h>      /* for XEvent */
#include <X11/Xproto.h>    /* for xEvent */

#undef NEED_EVENTS

#include "PEXlib.h"
#include "PEXlibint.h"


PEXPickMeasure
PEXCreatePickMeasure (display, wks, devType)

INPUT Display		*display;
INPUT PEXWorkstation	wks;
INPUT int		devType;

{
    pexCreatePickMeasureReq	*req;
    PEXPickMeasure		pm;


    /*
     * Get a Pick Measure resource id from X.
     */

    pm = XAllocID (display);


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (CreatePickMeasure, req);
    req->wks = wks;
    req->pm = pm;
    req->devType = devType;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (pm);
}


void
PEXFreePickMeasure (display, pm)

INPUT Display		*display;
INPUT PEXPickMeasure	pm;

{
    pexFreePickMeasureReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (FreePickMeasure, req);
    req->id = pm;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


PEXPMAttributes *
PEXGetPickMeasure (display, pm, valueMask)

INPUT Display			*display;
INPUT PEXPickMeasure		pm;
INPUT unsigned long		valueMask;

{
    pexGetPickMeasureReq	*req;
    pexGetPickMeasureReply	rep;
    PEXPMAttributes		*ppmi;
    unsigned long		*pv;
    unsigned long		f;
    int				i, tmp;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetReq (GetPickMeasure, req);
    req->pm = pm;
    req->itemMask = valueMask;

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
	UnlockDisplay (display);
	PEXSyncHandle (display);
	return (NULL);		  /* return an error */
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

    ppmi = (PEXPMAttributes *)
	PEXAllocBuf ((unsigned) (sizeof (PEXPMAttributes)));

    ppmi->pick_path.count = 0;
    ppmi->pick_path.elements = NULL;

    for (i = 0; i < (PEXPMMaxShift + 1); i++)
    {
	f = (1L << i);
	if (valueMask & f)
	{
	    switch (f)
	    {
	    case PEXPMStatus:
		ppmi->status = *pv;
		pv++;
		break;
	    case PEXPMPath:
		tmp = *(int *) pv;
		pv++;
		ppmi->pick_path.count = tmp;
		tmp *= sizeof (PEXPickElementRef);
		ppmi->pick_path.elements =
		    (PEXPickElementRef *) PEXAllocBuf ((unsigned) tmp);
		COPY_AREA ((char *) pv,
		    (char *) (ppmi->pick_path.elements), tmp);
		pv += NUMWORDS (tmp);
		break;
	    }
	}
    }


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (ppmi);
}


void
PEXUpdatePickMeasure (display, pick_measure, pick_device_type, pick_record)

INPUT Display		*display;
INPUT PEXPickMeasure	pick_measure;
INPUT int		pick_device_type;
INPUT PEXPickRecord	*pick_record;

{
    pexUpdatePickMeasureReq	*req;
    int				numBytes;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    numBytes = (pick_device_type == PEXPickDeviceDCHitBox) ?
	sizeof (PEXPDDCHitBox) : sizeof (PEXPDNPCHitVolume);

    PEXGetReqExtra (UpdatePickMeasure, numBytes, req);
    req->pm = pick_measure;
    req->numBytes = numBytes;

    COPY_AREA (pick_record, ((char *) &req[1]), numBytes);


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


PEXPDAttributes *
PEXGetPickDevice (display, wks, devType, valueMask)

INPUT Display			*display;
INPUT PEXWorkstation		wks;
INPUT int			devType;
INPUT unsigned long		valueMask;

{
    pexGetPickDeviceReq		*req;
    pexGetPickDeviceReply	rep;
    PEXPDAttributes		*ppdi;
    unsigned long		*pv;
    unsigned long		f;
    int				i, tmp;
    int				convertFP;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetFPReq (GetPickDevice, req, convertFP);
    req->wks = wks;
    req->itemMask = valueMask;
    req->devType = devType;

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
	UnlockDisplay (display);
	PEXSyncHandle (display);
	return (NULL);		  /* return an error */
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

    ppdi = (PEXPDAttributes *)
	PEXAllocBuf ((unsigned) (sizeof (PEXPDAttributes)));

    ppdi->path.count = 0;
    ppdi->path.elements = NULL;

    for (i = 0; i < (PEXPDMaxShift + 1); i++)
    {
	f = (1L << i);
	if (valueMask & f)
	{
	    switch (f)
	    {
	    case PEXPDPickStatus:
		ppdi->status = *pv;
		pv++;
		break;
	    case PEXPDPickPath:
		tmp = *(int *) pv;
		pv++;
		ppdi->path.count = tmp;
		tmp *= sizeof (PEXPickElementRef);
		ppdi->path.elements = (PEXPickElementRef *)
		    PEXAllocBuf ((unsigned) tmp);
		COPY_AREA ((char *) pv, (char *) (ppdi->path.elements), tmp);
		pv += NUMWORDS (tmp);
		break;
	    case PEXPDPickPathOrder:
		ppdi->path_order = *pv;
		pv++;
		break;
	    case PEXPDPickIncl:
		ppdi->inclusion = *((PEXNameSet *) pv);
		pv++;
		break;
	    case PEXPDPickExcl:
		ppdi->exclusion = *((PEXNameSet *) pv);
		pv++;
		break;
	    case PEXPDPickDataRec:
		tmp = *(int *) pv;
		pv++;
		COPY_AREA ((char *) pv, (char *) &(ppdi->pick_record), tmp);
		pv += NUMWORDS (tmp);
		break;
	    case PEXPDPromptEchoType:
		ppdi->prompt_echo_type = *pv;
		pv++;
		break;
	    case PEXPDEchoVolume:
		ppdi->echo_volume = *((PEXViewport *) pv);
		pv += LENOF (PEXViewport);
		break;
	    case PEXPDEchoSwitch:
		ppdi->echo_switch = *pv;
		pv++;
		break;
	    }
	}
    }


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (ppdi);
}


void
PEXChangePickDevice (display, wks, devType, valueMask, values)

INPUT Display		*display;
INPUT PEXWorkstation	wks;
INPUT int		devType;
INPUT unsigned long	valueMask;
INPUT PEXPDAttributes	*values;

{
    pexChangePickDeviceReq	*req;
    unsigned long		*pv, *pvSend;
    unsigned long		f, size;
    int				i, tmp, length;
    int				convertFP;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetFPReq (ChangePickDevice, req, convertFP);
    req->wks = wks;
    req->itemMask = valueMask;
    req->devType = devType;


    /*
     * Allocate a scratch buffer used to pack the attributes.  It's not
     * worth computing the exact amount of memory needed, so assume the
     * worse case.
     */

    size = 6 * sizeof (CARD32) +
	(sizeof (PEXPickElementRef) * ((valueMask & PEXPDPickPath) ?
	    values->path.count : 0)) +
	sizeof (PEXNameSet) * 2 +
	sizeof (PEXPickRecord) +
	sizeof (PEXViewport);

    pv = pvSend = (CARD32 *) _XAllocScratch (display, (unsigned long) size);

    for (i = 0; i < (PEXPDMaxShift + 1); i++)
    {
	f = (1L << i);
	if (valueMask & f)
	{
	    switch (f)
	    {
	    case PEXPDPickStatus:
		*pv = values->status;
		pv++;
		break;
	    case PEXPDPickPath:
		tmp = *((unsigned long *) pv) = values->path.count;
		pv++;
		tmp *= sizeof (PEXPickElementRef);
		COPY_AREA ((char *) (values->path.elements), (char *) pv, tmp);
		pv += NUMWORDS (tmp);
		break;
	    case PEXPDPickPathOrder:
		*pv = values->path_order;
		pv++;
		break;
	    case PEXPDPickIncl:
		*((PEXNameSet *) pv) = values->inclusion;
		pv += LENOF (PEXNameSet);
		break;
	    case PEXPDPickExcl:
		*((PEXNameSet *) pv) = values->exclusion;
		pv += LENOF (PEXNameSet);
		break;
	    case PEXPDPickDataRec:
		tmp = *((unsigned long *) pv) =
		    (devType == PEXPickDeviceDCHitBox) ?
		    sizeof (PEXPDDCHitBox) : sizeof (PEXPDNPCHitVolume);
		pv++;
		COPY_AREA ((char *) &(values->pick_record), (char *) pv, tmp);
		pv += NUMWORDS (tmp);
		break;
	    case PEXPDPromptEchoType:
		*pv = values->prompt_echo_type;
		pv++;
		break;
	    case PEXPDEchoVolume:
		*((PEXViewport *) pv) = values->echo_volume;
		pv += LENOF (PEXViewport);
		break;
	    case PEXPDEchoSwitch:
		*pv = values->echo_switch;
		pv++;
		break;
	    }
	}
    }

    length = pv - pvSend;
    req->length += length;

    Data (display, (char *) pvSend, (length << 2));


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}




/*
 * Routine to convert a protocol-format event (wire) to a client event
 * structure (client) for a PEXMaxHitsReachedEvent.  XESetWireToEvent is
 * called in PEXInitialize to set this up with Xlib.
 */

Status
_PEXConvertMaxHitsEvent (display, client, wire)

INPUT	Display		*display;
INPUT	XEvent		*client;
INPUT	xEvent		*wire;

{
    pexMaxHitsReachedEvent	*wireevent;
    PEXMaxHitsReachedEvent	*clientevent;


    /*
     * Set up the pointers.
     */

    wireevent = (pexMaxHitsReachedEvent *) wire;
    clientevent = (PEXMaxHitsReachedEvent *) client;


    /*
     * Now fill in the client structure.
     */

    clientevent->type = wireevent->type & 0x7f;
    clientevent->serial = wireevent->sequenceNumber;
    clientevent->send_event = (wireevent->type & 0x80) != 0;


    /*
     * MSB set if event came from SendEvent request.
     */

    clientevent->display = display;
    clientevent->renderer = wireevent->rdr;


    /*
     * Tell Xlib to add this to the event queue.
     */

    return (True);
}


#define GetPickRecordSize(_pickType) \
    (_pickType == PEXPickDeviceNPCHitVolume ? \
    sizeof (PEXPDNPCHitVolume) : sizeof (PEXPDDCHitBox));


void
PEXBeginPickOne (display, drawable, renderer, structure_id,
    method, pick_device_type, pick_record)

INPUT Display		*display;
INPUT Drawable		drawable;
INPUT PEXRenderer	renderer;
INPUT long		structure_id;
INPUT int		method;
INPUT int		pick_device_type;
INPUT PEXPickRecord	*pick_record;
{
    pexBeginPickOneReq	*req;
    unsigned int 	rec_size;
    int			convertFP;
    PEXEnumTypeIndex	*ptr;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    rec_size = GetPickRecordSize (pick_device_type);

    PEXGetFPReqExtra (BeginPickOne, (4 + rec_size), req, convertFP);
    req->method = method;
    req->rdr = renderer;
    req->drawable = drawable;
    req->sid = structure_id;

    ptr = (PEXEnumTypeIndex *) &req[1];
    *ptr = pick_device_type;
    ptr += 2;

    COPY_AREA ((char *) pick_record, (char *) ptr, rec_size);


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


PEXPickPath *
PEXEndPickOne (display, renderer, status_return, undetectable_return)

INPUT Display			*display;
INPUT PEXRenderer		renderer;
OUTPUT int			*status_return;
OUTPUT int			*undetectable_return;

{
    pexEndPickOneReq		*req;
    pexEndPickOneReply		rep;
    PEXPickPath			*pathRet;
    unsigned int		size;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetReq (EndPickOne, req);
    req->rdr = renderer;

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
        return (NULL);               /* return an error */
    }

    *status_return = rep.pickStatus;
    *undetectable_return = rep.betterPick;


    /*
     * Allocate a buffer for the path to pass back to the client.
     * If possible, use the pick path cache.
     */

    size = sizeof (PEXPickPath) + 
	rep.numPickElRefs * sizeof (PEXPickElementRef);

    if (!PEXPickCacheInUse && size <= PEXPickCacheSize)
    {
	pathRet = PEXPickCache;
	PEXPickCacheInUse = 1;
    }
    else
	pathRet = (PEXPickPath *) PEXAllocBuf ((unsigned) size);

    pathRet->elements = (PEXPickElementRef *) (pathRet + 1);
    pathRet->count = rep.numPickElRefs;

    _XRead (display, (char *) (pathRet->elements), (long) (rep.length << 2));


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (pathRet);
}


PEXPickPath *
PEXPickOne (display, drawable, renderer, structure, method,
    pick_device_type, pick_record, status_return, undetectable_return)

INPUT Display			*display;
INPUT Drawable			drawable;
INPUT PEXRenderer		renderer;
INPUT PEXStructure      	structure;
INPUT int			method;
INPUT int			pick_device_type;
INPUT PEXPickRecord		*pick_record;
OUTPUT int			*status_return;
OUTPUT int			*undetectable_return;

{
    pexPickOneReq	*req;
    pexPickOneReply	rep;
    unsigned int 	rec_size, size;
    int			convertFP;
    PEXEnumTypeIndex	*ptr;
    PEXPickPath		*pathRet;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    rec_size = GetPickRecordSize (pick_device_type);

    PEXGetFPReqExtra (PickOne, (4 + rec_size), req, convertFP);
    req->method = method;
    req->rdr = renderer;
    req->drawable = drawable;
    req->sid = structure;

    ptr = (PEXEnumTypeIndex *) &req[1];
    *ptr = pick_device_type;
    ptr += 2;

    COPY_AREA ((char *) pick_record, (char *) ptr, rec_size);

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
        return (NULL);               /* return an error */
    }

    *status_return = rep.pickStatus;
    *undetectable_return = rep.betterPick;


    /*
     * Allocate a buffer for the path to pass back to the client.
     * If possible, use the pick path cache.
     */

    size = sizeof (PEXPickPath) + 
	rep.numPickElRefs * sizeof (PEXPickElementRef);

    if (!PEXPickCacheInUse && size <= PEXPickCacheSize)
    {
	pathRet = PEXPickCache;
	PEXPickCacheInUse = 1;
    }
    else
	pathRet = (PEXPickPath *) PEXAllocBuf ((unsigned) size);

    pathRet->elements = (PEXPickElementRef *) (pathRet + 1);
    pathRet->count = rep.numPickElRefs;

    _XRead (display, (char *) (pathRet->elements), (long) (rep.length << 2));


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (pathRet);
}


void
PEXBeginPickAll (display, drawable, renderer, structure_id, method,
    send_event, max_hits, pick_device_type, pick_record)

INPUT Display		*display;
INPUT Drawable		drawable;
INPUT PEXRenderer	renderer;
INPUT long		structure_id;
INPUT int		method;
INPUT int		send_event;
INPUT int		max_hits;
INPUT int		pick_device_type;
INPUT PEXPickRecord	*pick_record;
{
    pexBeginPickAllReq	*req;
    unsigned int	rec_size;
    int			convertFP;
    PEXEnumTypeIndex	*ptr;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    rec_size = GetPickRecordSize (pick_device_type);

    PEXGetFPReqExtra (BeginPickAll, (4 + rec_size), req, convertFP);
    req->method = method;
    req->rdr = renderer;
    req->drawable = drawable;
    req->sid = structure_id;
    req->sendEvent = send_event;
    req->pickMaxHits = max_hits;

    ptr = (PEXEnumTypeIndex *) &req[1];
    *ptr = pick_device_type;
    ptr += 2;

    COPY_AREA ((char *) pick_record, (char *) ptr, rec_size);


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


PEXPickPath *
PEXEndPickAll (display, renderer, status_return, more_return, count_return)

INPUT Display		*display;
INPUT PEXRenderer	renderer;
OUTPUT int		*status_return;
OUTPUT int		*more_return;
OUTPUT unsigned long	*count_return;

{
    pexEndPickAllReq		*req;
    pexEndPickAllReply		rep;
    PEXPickPath			*psp, *pspRet;
    char			*prep, *prep_save;
    PEXPickElementRef		*per;
    int				i;
    int				numElements;
    unsigned int		total_size, size;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetReq (EndPickAll, req);
    req->rdr = renderer;

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
	*count_return = 0;
	return (NULL);           /* return an error */
    }

    *status_return = rep.pickStatus;
    *more_return = rep.morePicks;
    *count_return = rep.numPicked;


    /*
     * Allocate a scratch buffer and copy the reply data to the buffer.
     */

    prep = _XAllocScratch (display, (unsigned long) (rep.length << 2));

    _XRead (display, (char *) prep, (long) (rep.length << 2));


    /*
     * Allocate a buffer for the replies to pass back to the client.
     * If possible, use the pick path cache.
     */

    prep_save = prep;
    total_size = rep.numPicked * sizeof (PEXPickPath);

    for (i = 0; i < rep.numPicked; i++)
    {
	numElements = *((CARD32 *) prep);
	prep += sizeof (CARD32);
	size = numElements * sizeof (PEXPickElementRef);
	prep += size;
	total_size += size;
    }

    if (!PEXPickCacheInUse && total_size <= PEXPickCacheSize)
    {
	pspRet = PEXPickCache;
	PEXPickCacheInUse = 1;
    }
    else
	pspRet = (PEXPickPath *) PEXAllocBuf ((unsigned) total_size);

    psp = pspRet;
    prep = prep_save;
    per = (PEXPickElementRef *) ((char *) psp +
	rep.numPicked * sizeof (PEXPickPath));

    for (i = 0; i < rep.numPicked; i++)
    {
	numElements = *((CARD32 *) prep);
	prep += sizeof (CARD32);
	size = numElements * sizeof (PEXPickElementRef);
	COPY_AREA (prep, (char *) per, size);
	psp->count = numElements;
	psp->elements = per;
	psp++;
	per += numElements;
	prep += size;
    }


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (pspRet);
}


PEXPickPath *
PEXPickAll (display, drawable, renderer, method, max_hits, pick_device_type,
    pick_record, status_return, more_return, count_return)

INPUT Display		*display;
INPUT Drawable		drawable;
INPUT PEXRenderer	renderer;
INPUT int		method;
INPUT int		max_hits;
INPUT int		pick_device_type;
INPUT PEXPickRecord	*pick_record;
OUTPUT int		*status_return;
OUTPUT int		*more_return;
OUTPUT unsigned long	*count_return;


{
    pexPickAllReq		*req;
    pexPickAllReply		rep;
    PEXPickPath			*psp, *pspRet;
    char			*prep, *prep_save;
    PEXPickElementRef		*per;
    int				numElements, i;
    unsigned int		rec_size, total_size, size;
    int				convertFP;
    PEXEnumTypeIndex		*ptr;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    rec_size = GetPickRecordSize (pick_device_type);

    PEXGetFPReqExtra (PickAll, (4 + rec_size), req, convertFP);
    req->method = method;
    req->rdr = renderer;
    req->drawable = drawable;
    req->pickMaxHits = max_hits;

    ptr = (PEXEnumTypeIndex *) &req[1];
    *ptr = pick_device_type;
    ptr += 2;

    COPY_AREA ((char *) pick_record, (char *) ptr, rec_size);

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
	*count_return = 0;
	return (NULL);           /* return an error */
    }

    *status_return = rep.pickStatus;
    *more_return = rep.morePicks;
    *count_return = rep.numPicked;


    /*
     * Allocate a scratch buffer and copy the reply data to the buffer.
     */

    prep = _XAllocScratch (display, (unsigned long) (rep.length << 2));

    _XRead (display, (char *) prep, (long) (rep.length << 2));


    /*
     * Allocate a buffer for the replies to pass back to the client.
     * If possible, use the pick path cache.
     */

    prep_save = prep;
    total_size = rep.numPicked * sizeof (PEXPickPath);

    for (i = 0; i < rep.numPicked; i++)
    {
	numElements = *((CARD32 *) prep);
	prep += sizeof (CARD32);
	size = numElements * sizeof (PEXPickElementRef);
	prep += size;
	total_size += size;
    }

    if (!PEXPickCacheInUse && total_size <= PEXPickCacheSize)
    {
	pspRet = PEXPickCache;
	PEXPickCacheInUse = 1;
    }
    else
	pspRet = (PEXPickPath *) PEXAllocBuf ((unsigned) total_size);

    psp = pspRet;
    prep = prep_save;
    per = (PEXPickElementRef *) ((char *) psp +
	rep.numPicked * sizeof (PEXPickPath));

    for (i = 0; i < rep.numPicked; i++)
    {
	numElements = *((CARD32 *) prep);
	prep += sizeof (CARD32);
	size = numElements * sizeof (PEXPickElementRef);
	COPY_AREA (prep, (char *) per, size);
	psp->count = numElements;
	psp->elements = per;
	psp++;
	per += numElements;
	prep += size;
    }


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (pspRet);
}
