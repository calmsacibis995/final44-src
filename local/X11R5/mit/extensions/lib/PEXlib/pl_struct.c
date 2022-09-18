/* $XConsortium: pl_struct.c,v 1.7 92/08/26 13:06:23 mor Exp $ */

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


PEXStructure
PEXCreateStructure (display)

INPUT Display		*display;

{
    pexCreateStructureReq	*req;
    pexStructure		s;


    /*
     * Get a structure resource id from X.
     */

    s = XAllocID (display);


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (CreateStructure, req);
    req->id = s;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (s);
}


void
PEXDestroyStructures (display, numStructures, structures)

INPUT Display		*display;
INPUT unsigned long	numStructures;
INPUT PEXStructure	*structures;

{
    pexDestroyStructuresReq	*req;
    int 			size;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    size = numStructures * sizeof (pexStructure);

    PEXGetReqExtra (DestroyStructures, size, req);
    req->numStructures = numStructures;

    COPY_AREA ((char *) structures, ((char *) &req[1]), size);


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXCopyStructure (display, srcStructure, destStructure)

INPUT Display		*display;
INPUT PEXStructure	srcStructure;
INPUT PEXStructure	destStructure;

{
    pexCopyStructureReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (CopyStructure, req);
    req->src = srcStructure;
    req->dst = destStructure;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


Status
PEXGetStructureInfo (display, structure, float_format,
    value_mask, info_return)

INPUT Display			*display;
INPUT PEXStructure		structure;
INPUT int			float_format;
INPUT unsigned long		value_mask;
OUTPUT PEXStructureInfo		*info_return;

{
    pexGetStructureInfoReq	*req;
    pexGetStructureInfoReply	rep;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetReq (GetStructureInfo, req);
    req->fpFormat = float_format;
    req->sid = structure;
    req->itemMask = value_mask;

    if (_XReply (display, &rep, 0, xTrue) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
	return (0);            /* return an error */
    }


    if (value_mask & PEXEditMode)
	info_return->edit_mode = rep.editMode;
    if (value_mask & PEXElementPtr)
	info_return->element_pointer = rep.elementPtr;
    if (value_mask & PEXNumElements)
	info_return->element_count = rep.numElements;
    if (value_mask & PEXLengthStructure)
	info_return->size = rep.lengthStructure;
    if (value_mask & PEXHasRefs)
	info_return->has_refs = rep.hasRefs;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (1);
}


Status
PEXGetElementInfo (display, structure, whence1, offset1, whence2, offset2,
    float_format, numElementInfoReturn, infoReturn)

INPUT Display		*display;
INPUT PEXStructure	structure;
INPUT int		whence1;
INPUT long		offset1;
INPUT int		whence2;
INPUT long		offset2;
INPUT int		float_format;
OUTPUT unsigned long	*numElementInfoReturn;
OUTPUT PEXElementInfo	**infoReturn;

{
    pexGetElementInfoReq	*req;
    pexGetElementInfoReply	rep;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetReq (GetElementInfo, req);
    req->fpFormat = float_format;
    req->sid = structure;
    req->range.position1.whence = whence1;
    req->range.position1.offset = offset1;
    req->range.position2.whence = whence2;
    req->range.position2.offset = offset2;

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
	*numElementInfoReturn = 0;
	*infoReturn = NULL;
	return (0);        /* return an error */
    }

    *numElementInfoReturn = rep.numInfo;


    /*
     * Allocate a buffer for the replies to pass back to the client.
     */

    *infoReturn = (PEXElementInfo *) PEXAllocBuf (
	(unsigned) (rep.length << 2));

    _XRead (display, (char *) *infoReturn, (long) (rep.length << 2));


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (1);
}


PEXStructure *
PEXGetStructuresInNetwork (display, structure, which, numStructuresReturn)

INPUT Display		*display;
INPUT PEXStructure	structure;
INPUT int		which;
OUTPUT unsigned long	*numStructuresReturn;

{
    pexGetStructuresInNetworkReq	*req;
    pexGetStructuresInNetworkReply	rep;
    pexStructure			*ps;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetReq (GetStructuresInNetwork, req);
    req->sid = structure;
    req->which = which;

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
	*numStructuresReturn = 0;
	return (NULL);             /* return an error */
    }

    *numStructuresReturn = rep.numStructures;


    /*
     * Allocate a buffer for the replies to pass back to the client.
     */

    ps = (pexStructure *) PEXAllocBuf ((unsigned) (rep.length << 2));

    _XRead (display, (char *) ps, (long) (rep.length << 2));


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return ((PEXStructure *) ps);
}


PEXStructurePath *
PEXGetAncestors (display, structure, pathPart, pathDepth, numPathsReturn)

INPUT Display		*display;
INPUT PEXStructure	structure;
INPUT int		pathPart;
INPUT unsigned long	pathDepth;
OUTPUT unsigned long	*numPathsReturn;

{
    pexGetAncestorsReq		*req;
    pexGetAncestorsReply	rep;
    PEXStructurePath		*psp, *pathsReturn;
    pexElementRef		*per;
    char			*prep;
    int				numElements, size, i;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetReq (GetAncestors, req);
    req->sid = structure;
    req->pathOrder = pathPart;
    req->pathDepth = pathDepth;

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
	*numPathsReturn = 0;
	return (NULL);           /* return an error */
    }

    *numPathsReturn = rep.numPaths;


    /*
     * Allocate a scratch buffer and copy the reply data to the buffer.
     */

    prep = _XAllocScratch (display, (unsigned long) (rep.length << 2));

    _XRead (display, (char *) prep, (long) (rep.length << 2));


    /*
     * Allocate a buffer for the replies to pass back to the client.
     */

    pathsReturn = psp = (PEXStructurePath *) PEXAllocBuf
	((unsigned) (rep.numPaths * sizeof (PEXStructurePath)));

    for (i = 0; i < rep.numPaths; i++)
    {
	numElements = *((CARD32 *) prep);
	prep += sizeof (CARD32);
	size = numElements * sizeof (pexElementRef);
	per = (pexElementRef *) PEXAllocBuf ((unsigned) size);
	COPY_AREA ((char *) prep, (char *) per, size);
	psp->count = numElements;
	psp->elements = (PEXElementRef *) per;
	psp++;
	prep += size;
    }


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (pathsReturn);
}



PEXStructurePath *
PEXGetDescendants (display, structure, pathPart, pathDepth, numPathsReturn)

INPUT Display		*display;
INPUT PEXStructure	structure;
INPUT int		pathPart;
INPUT unsigned long	pathDepth;
OUTPUT unsigned long	*numPathsReturn;

{
    pexGetDescendantsReq	*req;
    pexGetDescendantsReply	rep;
    PEXStructurePath		*psp, *pathsReturn;
    pexElementRef		*per;
    char			*prep;
    int				numElements, size, i;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetReq (GetDescendants, req);
    req->sid = structure;
    req->pathOrder = pathPart;
    req->pathDepth = pathDepth;

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
	*numPathsReturn = 0;
	return (NULL);          /* return an error */
    }

    *numPathsReturn = rep.numPaths;


    /*
     * Allocate a scratch buffer and copy the reply data to the buffer.
     */

    prep = _XAllocScratch (display, (unsigned long) (rep.length << 2));

    _XRead (display, (char *) prep, (long)(rep.length << 2));


    /*
     * Allocate a buffer to pass the replies back to the client.
     */

    pathsReturn = psp = (PEXStructurePath *) PEXAllocBuf
	((unsigned) (rep.numPaths * sizeof (PEXStructurePath)));

    for (i = 0; i < rep.numPaths; i++)
    {
	numElements = *((CARD32 *) prep);
	prep += sizeof (CARD32);
	size = numElements * sizeof (pexElementRef);
	per = (pexElementRef *) PEXAllocBuf ((unsigned) size);
	COPY_AREA ((char *) prep, (char *) per, size);
	psp->count = numElements;
	psp->elements = (PEXElementRef *) per;
	psp++;
	prep += size;
    }


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (pathsReturn);
}


Status
PEXFetchElements (display, structure, whence1, offset1, whence2, offset2,
    float_format, numElementsReturn, sizeReturn, ocsReturn)

INPUT Display		*display;
INPUT PEXStructure	structure;
INPUT int		whence1;
INPUT long		offset1;
INPUT int		whence2;
INPUT long		offset2;
INPUT int		float_format;
OUTPUT unsigned long	*numElementsReturn;
OUTPUT unsigned long	*sizeReturn;
OUTPUT char		**ocsReturn;

{
    pexFetchElementsReq		*req;
    pexFetchElementsReply	rep;
    long			repSize;
    int				server_float_format;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    server_float_format = PEXGetProtocolFloatFormat (display);

    PEXGetReq (FetchElements, req);
    req->fpFormat = server_float_format;
    req->sid = structure;
    req->range.position1.whence = whence1;
    req->range.position1.offset = offset1;
    req->range.position2.whence = whence2;
    req->range.position2.offset = offset2;

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
    	*sizeReturn = *numElementsReturn = 0;
	*ocsReturn = NULL;
        return (0);		/* return an error */
    }

    *numElementsReturn = rep.numElements;

    if (server_float_format != float_format)
    {
	/*
	 * Convert from server's float format to the float format
	 * specified by the application.
	 */

	*sizeReturn = 0;
	*ocsReturn = NULL;
    }
    else
    {
	/*
	 * No float conversion necessary.
	 */

	*sizeReturn = repSize = rep.length << 2;
	*ocsReturn = (char *) PEXAllocBuf (repSize);
	if (*ocsReturn != NULL)
	    _XRead (display, *ocsReturn, (long) repSize);
    }


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (1);
}


Status
PEXFetchElementsAndSend (display, structure,
    whence1, offset1, whence2, offset2, dstDisplay, resID, reqType)

INPUT Display		*display;
INPUT PEXStructure	structure;
INPUT int		whence1;
INPUT long		offset1;
INPUT int		whence2;
INPUT long		offset2;
INPUT Display		*dstDisplay;
INPUT XID		resID;
INPUT PEXOCRequestType	reqType;

{
    PEXDisplayInfo 		*srcDisplayInfo, *dstDisplayInfo;
    pexFetchElementsReq		*req;
    pexFetchElementsReply	rep;
    char	 		*ocAddr;
    PEXEnumTypeDesc		*srcFloats, *dstFloats;
    long			bytesLeft;
    int				getSize, size, i, j;
    int				fp_match, float_format;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Determine which floating point format to use.
     */

    PEXGetDisplayInfo (display, srcDisplayInfo);
    PEXGetDisplayInfo (dstDisplay, dstDisplayInfo);

    if (display == dstDisplay)
    {
	float_format = dstDisplayInfo->fpFormat;
	fp_match = 1;
    }
    else
    {
	srcFloats = srcDisplayInfo->fpSupport;
	dstFloats = dstDisplayInfo->fpSupport;

	fp_match = 0;
	for (i = 0; i < dstDisplayInfo->fpCount && !fp_match; i++)
	    for (j = 0; j < srcDisplayInfo->fpCount; j++)
	    {
		if (dstFloats[i].index == srcFloats[j].index)
		{
		    float_format = dstFloats[i].index;
		    fp_match = 1;
		    break;
		}
	    }

	if (!fp_match)
	{
	    /*
	     * Will have to convert from source display float format to
	     * destination display float format.
	     */

	    float_format = srcDisplayInfo->fpFormat;
	}
    }


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetReq (FetchElements, req)
    req->fpFormat = float_format;
    req->sid = structure;
    req->range.position1.whence = whence1;
    req->range.position1.offset = offset1;
    req->range.position2.whence = whence2;
    req->range.position2.offset = offset2;

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
        return (0);		/* return an error */
    }


    /*
     * If no floating point conversion has to take place, fetch the element
     * info directly into the destination display connection.
     */

    if (fp_match)
    {
	if (display == dstDisplay)
	    UnlockDisplay (display);

	if (PEXStartOCs (dstDisplay, resID, reqType, float_format,
	    rep.numElements, rep.length))
	{
	    bytesLeft = rep.length << 2;
	    getSize = PEXGetOCAddrMaxSize (dstDisplay);

	    while (bytesLeft > 0)
	    {
		size = min (bytesLeft, getSize);

		if (ocAddr = PEXGetOCAddr (dstDisplay, size))
		    _XRead (display, ocAddr, (long) size);
		else
		{
		    PEXFinishOC (dstDisplay);
		    if (display != dstDisplay)
			UnlockDisplay (display);
		    PEXSyncHandle (dstDisplay);
		    return (0);
		}

		bytesLeft -= size;
	    }

	    PEXFinishOC (dstDisplay);
	}

	if (display != dstDisplay)
	    UnlockDisplay (display);
    }
    else
    {
	/*
	 * Floating point conversion necessary.
	 */

    }

    PEXSyncHandle (dstDisplay);

    return (1);
}


void
PEXSetEditingMode (display, structure, mode)

INPUT Display		*display;
INPUT PEXStructure	structure;
INPUT int		mode;

{
    pexSetEditingModeReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (SetEditingMode, req);
    req->sid = structure;
    req->mode = mode;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXSetElementPtr (display, structure, whence, offset)

INPUT Display		*display;
INPUT PEXStructure	structure;
INPUT int		whence;
INPUT long		offset;

{
    pexSetElementPointerReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (SetElementPointer, req);
    req->sid = structure;
    req->position.whence = whence;
    req->position.offset = offset;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXSetElementPtrAtLabel (display, structure, label, offset)

INPUT Display		*display;
INPUT PEXStructure	structure;
INPUT long		label;
INPUT long		offset;

{
    pexSetElementPointerAtLabelReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (SetElementPointerAtLabel, req);
    req->sid = structure;
    req->label = label;
    req->offset = offset;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


Status
PEXElementSearch (display, structure, whence, offset, direction,
	numIncl, inclList, numExcl, exclList, offsetReturn)

INPUT Display		*display;
INPUT PEXStructure	structure;
INPUT int		whence;
INPUT long		offset;
INPUT int		direction;
INPUT unsigned long	numIncl;
INPUT unsigned short	*inclList;
INPUT unsigned long	numExcl;
INPUT unsigned short	*exclList;
OUTPUT unsigned long	*offsetReturn;

{
    pexElementSearchReq		*req;
    pexElementSearchReply	rep;
    char			*ptr;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetReqExtra (ElementSearch,  sizeof (CARD16) *
	(numIncl + (numIncl & 1) + numExcl + (numExcl & 1)), req);
    req->sid = structure;
    req->position.whence = whence;
    req->position.offset = offset;
    req->direction = direction;
    req->numIncls = numIncl;
    req->numExcls = numExcl;

    ptr = (char *) &req[1];
    COPY_AREA ((char *) inclList, ptr, numIncl * sizeof (CARD16));
    ptr += ((numIncl + (numIncl & 1)) * sizeof (CARD16));
    COPY_AREA ((char *) exclList, ptr, numExcl * sizeof (CARD16));

    if (_XReply (display, &rep, 0, xTrue) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
	*offsetReturn = 0;
	return (0);               /* return an error */
    }

    *offsetReturn = rep.foundOffset;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (rep.status);
}


void
PEXDeleteElements (display, structure, whence1, offset1, whence2, offset2)

INPUT Display		*display;
INPUT PEXStructure	structure;
INPUT int		whence1;
INPUT long		offset1;
INPUT int		whence2;
INPUT long		offset2;

{
    pexDeleteElementsReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (DeleteElements, req);
    req->sid =  structure;
    req->range.position1.whence = whence1;
    req->range.position1.offset = offset1;
    req->range.position2.whence = whence2;
    req->range.position2.offset = offset2;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXDeleteToLabel (display, structure, whence, offset, label)

INPUT Display		*display;
INPUT PEXStructure	structure;
INPUT int		whence;
INPUT long		offset;
INPUT long		label;

{
    pexDeleteElementsToLabelReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (DeleteElementsToLabel, req);
    req->sid =  structure;
    req->position.whence = whence;
    req->position.offset = offset;
    req->label = label;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXDeleteBetweenLabels (display, structure, label1, label2)

INPUT Display		*display;
INPUT PEXStructure	structure;
INPUT long		label1;
INPUT long		label2;

{
    pexDeleteBetweenLabelsReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (DeleteBetweenLabels, req);
    req->sid =  structure;
    req->label1 = label1;
    req->label2 = label2;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXCopyElements (display, srcStructure, srcWhence1, srcOffset1, srcWhence2,
    srcOffset2, destStructure, destWhence, destOffset)

INPUT Display		*display;
INPUT PEXStructure	srcStructure;
INPUT int		srcWhence1;
INPUT long		srcOffset1;
INPUT int		srcWhence2;
INPUT long		srcOffset2;
INPUT PEXStructure	destStructure;
INPUT int		destWhence;
INPUT long		destOffset;

{
    pexCopyElementsReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (CopyElements, req);
    req->src = srcStructure;
    req->srcRange.position1.whence = srcWhence1;
    req->srcRange.position1.offset = srcOffset1;
    req->srcRange.position2.whence = srcWhence2;
    req->srcRange.position2.offset = srcOffset2;
    req->dst = destStructure;
    req->dstPosition.whence = destWhence;
    req->dstPosition.offset = destOffset;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}


void
PEXChangeStructureRefs (display, oldStructure, newStructure)

INPUT Display		*display;
INPUT PEXStructure	oldStructure;
INPUT PEXStructure	newStructure;

{
    pexChangeStructureRefsReq	*req;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer.
     */

    PEXGetReq (ChangeStructureRefs, req);
    req->old_id = oldStructure;
    req->new_id = newStructure;


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);
}
