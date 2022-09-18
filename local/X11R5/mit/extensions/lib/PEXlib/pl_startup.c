/* $XConsortium: pl_startup.c,v 1.9 92/08/26 13:06:22 mor Exp $ */

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
#include "pl_global_def.h"
#include <stdio.h>


int
PEXInitialize (display, info_return, length, error_string)

INPUT  Display		*display;
OUTPUT PEXExtensionInfo	**info_return;
INPUT  int		length;
OUTPUT char		*error_string;

{
    pexGetExtensionInfoReq	*req;
    pexGetExtensionInfoReply	rep;
    PEXExtensionInfo		*extInfo;
    XExtCodes			*pExtCodes;
    PEXDisplayInfo		*pexDisplayInfo;
    int				enumType, match, i;
    PEXEnumTypeDesc		*enumReturn;
    unsigned long		*numReturn;
    char			*string;

    extern XExtCodes		*XInitExtension();
    extern Status		_PEXConvertMaxHitsEvent();
    Bool			_PEXConvertOCError();
    void			_PEXPrintOCError();
    int				_PEXCloseDisplay();


    /*
     * Lock the display.
     */

    LockDisplay (display);


    /*
     * Initialize the PEX extension on this display.
     */

    *info_return = NULL;

    if ((pExtCodes = XInitExtension (display, "X3D-PEX")) == NULL)
    {
        UnlockDisplay (display);
	PEXSyncHandle (display);

	XGetErrorDatabaseText (display, "PEXlibMessage", "BadExtension",
	    "Could not initialize the PEX extension on the specified display",
            error_string, length);

	return (PEXBadExtension);
    }


    /*
     * For each display initialized by PEXlib, some additional data must
     * be maintained (such as extension codes and float format).  A linked
     * list of records is maintained, one for each open display, with the
     * most recently referenced display always at the beginning.
     */

    pexDisplayInfo = (PEXDisplayInfo *)
	PEXAllocBuf ((unsigned) (sizeof (PEXDisplayInfo)));

    if (!pexDisplayInfo)
    {
        UnlockDisplay (display);
	PEXSyncHandle (display);

	XGetErrorDatabaseText (display, "PEXlibMessage", "BadLocalAlloc",
	    "Could not allocate memory for PEXlib internal usage",
            error_string, length);

	return (PEXBadLocalAlloc);
    }

    PEXAddDisplayInfo (display, pexDisplayInfo);

    pexDisplayInfo->extCodes = pExtCodes;
    pexDisplayInfo->extOpcode = pExtCodes->major_opcode;
    pexDisplayInfo->lastResID = 0;
    pexDisplayInfo->lastReqType = -1;
    pexDisplayInfo->lastReqNum = -1;


    /*
     * Check if the PEX server on this display supports the client's native
     * floating point format.  If not, choose a server supported format
     * (hopefully, the server's native floating point format is in the
     * first entry returned by PEXGetEnumTypeInfo).  In places specified by
     * the PEXlib spec, PEXlib will convert between the client's native
     * floating point format and the server supported format.
     */

    enumType = PEXETFloatFormat;

    if (PEXGetEnumTypeInfo (display, DefaultRootWindow (display), 1,
	&enumType, PEXETIndex, &numReturn, &enumReturn) == 0)
    {
        UnlockDisplay (display);
	PEXSyncHandle (display);

	XGetErrorDatabaseText (display, "PEXlibMessage", "GetEnumFailure",
	    "Implicit call to PEXGetEnumTypeInfo by PEXInitialize failed",
            error_string, length);

	return (PEXBadFloatConversion);
    }

    pexDisplayInfo->fpSupport = enumReturn;
    pexDisplayInfo->fpCount = *numReturn;

    for (i = match = 0; i < *numReturn; i++)
	if (enumReturn[i].index == NATIVE_FP_FORMAT)
	{
	    match = 1;
	    break;
	}

    if (enumReturn == NULL || *numReturn == 0)
    {
        UnlockDisplay (display);
	PEXSyncHandle (display);

	XGetErrorDatabaseText (display, "PEXlibMessage", "NoFloats",
	    "No floating point formats supported by server",
            error_string, length);

	return (PEXBadFloatConversion);
    }
    else if (match)
    {
	pexDisplayInfo->fpFormat = NATIVE_FP_FORMAT;
	pexDisplayInfo->fpConvert = 0;
    }
    else
    {
	pexDisplayInfo->fpFormat = enumReturn[0].index;
	pexDisplayInfo->fpConvert = 1;
    }

    PEXFreeBuf (numReturn);


    /*
     * Tell Xlib how to convert an Output Command error from
     * wire to client format.
     */

    XESetWireToError (display, pExtCodes->first_error + BadPEXOutputCommand,
	_PEXConvertOCError);


    /*
     * Tell Xlib how to print the OC error.
     */

    XESetPrintErrorValues (display, pExtCodes->extension, _PEXPrintOCError);


    /*
     * Tell Xlib how to convert a MaxHitReachedEvent from
     * wire to client format.
     */

    XESetWireToEvent (display, pExtCodes->first_event + PEXMaxHitsReached,
	_PEXConvertMaxHitsEvent);


    /*
     * Tell Xlib which PEXlib function to call when the display is closed.
     */

    XESetCloseDisplay (display, pExtCodes->extension, _PEXCloseDisplay);


    /*
     * Get information about the PEX server extension.
     */

    PEXGetReq (GetExtensionInfo, req);
    req->clientProtocolMajor = PEX_PROTO_MAJOR;
    req->clientProtocolMinor = PEX_PROTO_MINOR;

    if (_XReply (display,  &rep, 0, xFalse) == 0)
    {
        UnlockDisplay (display);
	PEXSyncHandle (display);

	XGetErrorDatabaseText (display, "PEXlibMessage", "GetInfoFailure",
	    "Could not get PEX extension information",
            error_string, length);

	return (PEXBadExtension);
    }


    /*
     * Get the vendor name string and null terminate it.
     */

    if (!(string = (char *) PEXAllocBuf ((unsigned) (rep.lengthName + 1))))
    {
        UnlockDisplay (display);
	PEXSyncHandle (display);

	XGetErrorDatabaseText (display, "PEXlibMessage", "BadLocalAlloc",
	    "Could not allocate memory for PEXlib internal usage",
            error_string, length);

	return (PEXBadLocalAlloc);
    }

    _XReadPad (display, (char *) string, (long) (rep.lengthName));
    string[rep.lengthName] = '\0';


    /*
     * We can unlock the display now.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);


    /*
     * Store the extension info.
     */

    extInfo = *info_return = pexDisplayInfo->extInfo = (PEXExtensionInfo *)
	PEXAllocBuf ((unsigned) (sizeof (PEXExtensionInfo)));

    if (!extInfo)
    {
	XGetErrorDatabaseText (display, "PEXlibMessage", "BadLocalAlloc",
	    "Could not allocate memory for PEXlib internal usage",
            error_string, length);

	return (PEXBadLocalAlloc);
    }

    extInfo->major_version = rep.majorVersion;
    extInfo->minor_version = rep.minorVersion;
    extInfo->release = rep.release;
    extInfo->subset_info = rep.subsetInfo;
    extInfo->vendor_name = string;
    extInfo->major_opcode = pExtCodes->major_opcode;
    extInfo->first_event = pExtCodes->first_event;
    extInfo->first_error = pExtCodes->first_error;

    if (rep.majorVersion == PEX_PROTO_MAJOR)
	return (0);
    else
    {
	char str[PEXErrorStringLength];

	XGetErrorDatabaseText (display, "PEXlibMessage", "BadProtoVersion",
	    "Client speaks PEX %d.%d; Server speaks PEX %d.%d",
            str, PEXErrorStringLength);

	sprintf (error_string, str,
            PEX_PROTO_MAJOR, PEX_PROTO_MINOR,
	    rep.majorVersion, rep.minorVersion);
  
	return (PEXBadProtocolVersion);
    }
}


PEXExtensionInfo *
PEXGetExtensionInfo (display)

INPUT Display	*display;

{
    PEXDisplayInfo 	*pexDisplayInfo;

    
    PEXGetDisplayInfo (display, pexDisplayInfo);
    return (pexDisplayInfo ? pexDisplayInfo->extInfo : NULL);
}


int
PEXGetProtocolFloatFormat (display)

INPUT Display	*display;

{
    PEXDisplayInfo 	*pexDisplayInfo;

    
    PEXGetDisplayInfo (display, pexDisplayInfo);
    return (pexDisplayInfo ? pexDisplayInfo->fpFormat : 0);
}


/*
 * PEXGetEnumTypeInfo is broken in the PEX spec.  For 5.1, PEXlib will
 * be compatible with the PEX SI.  In 6.0, the encoding should be fixed.
 */

Status
PEXGetEnumTypeInfo (display, drawable, numEnumTypes, enumTypes,
    itemMask, numReturn, enumInfoReturn)

INPUT Display			*display;
INPUT Drawable			drawable;
INPUT unsigned long		numEnumTypes;
INPUT int			*enumTypes;
INPUT unsigned long		itemMask;
OUTPUT unsigned long		**numReturn;
OUTPUT PEXEnumTypeDesc		**enumInfoReturn;

{
    pexGetEnumTypeInfoReq	*req;
    pexGetEnumTypeInfoReply	rep;
    char			*prepbuf, *pstartrep;
    PEXEnumTypeDesc		*penum;
    unsigned long		*pcounts;
    char			*pstring;
    CARD16			*dstEnumType;
    int				*srcEnumType;
    int				numDescs, totDescs, length, i, j;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetReqExtra (GetEnumTypeInfo, numEnumTypes * sizeof (CARD16), req);

    req->drawable = drawable;
    req->itemMask = itemMask;
    req->numEnums = numEnumTypes;

    for (i = 0, dstEnumType = (CARD16 *) &req[1], srcEnumType = enumTypes;
	 i < numEnumTypes;
	 i++, dstEnumType++, srcEnumType++)
    {
	*dstEnumType = (CARD16) *srcEnumType;
    }

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
	UnlockDisplay (display);
	PEXSyncHandle (display);
	*numReturn = NULL;
	*enumInfoReturn = NULL;
	return (0);			/* return an error */
    }


    /*
     * Error if fewer than numEnumTypes lists returned.
     */

    if (rep.numLists < numEnumTypes) 
    {
	UnlockDisplay (display);
	PEXSyncHandle (display);
	*numReturn = NULL;
	*enumInfoReturn = NULL;
	return (0);			/* return an error */
    }


    /*
     * Allocate a scratch buffer and copy the reply data to the buffer.
     */

    pstartrep = (char *) _XAllocScratch (display,
	(unsigned long) (rep.length << 2));

    _XRead (display, pstartrep, (long) (rep.length << 2));


    /*
     * Count total number of enums returned.
     */

    for (i = 0, totDescs = 0, prepbuf = pstartrep; i < rep.numLists; i++)
    { 
         numDescs = *((CARD32 *) prepbuf);
	 totDescs += numDescs; 

         prepbuf += sizeof (CARD32);
         if (i == rep.numLists - 1)
	     break;

	 if (itemMask == PEXETIndex)
	 {
	     prepbuf += PADDED_BYTES (numDescs * sizeof (INT16));
	 }
	 else if (itemMask == PEXETMnemonic)
	 {
	     for (j = 0; j < numDescs; j++)
	     {
	        length = *((CARD16 *) prepbuf);
	        prepbuf += PADDED_BYTES (sizeof (CARD16) + length);
	     }
	 }
	 else if (itemMask == PEXETAll)
	 {
	     for (j = 0; j < numDescs; j++)
	     {
	        prepbuf += sizeof (INT16);
	        length = *((CARD16 *) prepbuf);
	        prepbuf += (sizeof (CARD16) + PADDED_BYTES (length));
	     }
	 }
    }


    /*
     * Allocate storage for enum data to be returned to the client.
     */

    *enumInfoReturn = penum = (PEXEnumTypeDesc *)
	PEXAllocBuf ((unsigned) (totDescs * sizeof (PEXEnumTypeDesc)));


    /*
     * Allocate storage to return the counts to the client.
     */

    *numReturn = pcounts = (unsigned long *)
       PEXAllocBuf ((unsigned) (numEnumTypes * sizeof (unsigned long)));


    /*
     * Retrieve the lists of enum info.
     */

    for (i = 0, prepbuf = pstartrep; i < rep.numLists; i++, pcounts++)
    {
        *pcounts = numDescs = *((CARD32 *) prepbuf);
        prepbuf += sizeof (CARD32);

	if (itemMask == PEXETIndex)
	{
	    for (j = 0; j < numDescs; j++, penum++)
	    {
		penum->descriptor = NULL;
	        penum->index = *((INT16 *) prepbuf);
	        prepbuf += sizeof (INT16);
	    }

	    if (numDescs & 1)
	        prepbuf += sizeof (INT16);
	}
	else if (itemMask == PEXETMnemonic)
	{
	    for (j = 0; j < numDescs; j++, penum++)
	    {
		penum->index = 0;

		length = *((CARD16 *) prepbuf);
		prepbuf += sizeof (CARD16);
		penum->descriptor = pstring =
		    (char *) PEXAllocBuf ((unsigned) (length + 1));
		COPY_AREA ((char *) prepbuf, (char *) pstring, length);
		pstring[length] = '\0';       /* null terminate */

		prepbuf += (PADDED_BYTES (sizeof (CARD16) + length) - 
		    sizeof (CARD16));
	    }
	}
	else if (itemMask == PEXETAll)
	{
	    for (j = 0; j < numDescs; j++, penum++)
	    {
		penum->index = *((INT16 *) prepbuf);
		prepbuf += sizeof (INT16);
		
		length = *((CARD16 *) prepbuf);
		prepbuf += sizeof (CARD16);
		penum->descriptor = pstring =
		    (char *) PEXAllocBuf ((unsigned) (length + 1));
		COPY_AREA ((char *) prepbuf, (char *) pstring, length);
		pstring[length] = '\0';       /* null terminate */

		prepbuf += PADDED_BYTES (length);
	    }
	}
    }


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (1);
}


Status
PEXGetImpDepConstants (display, drawable, numNames, names, constantsReturn)

INPUT Display			*display;
INPUT Drawable			drawable;
INPUT unsigned long		numNames;
INPUT unsigned short		*names;
OUTPUT PEXImpDepConstant	**constantsReturn;

{
    pexGetImpDepConstantsReq	*req;
    pexGetImpDepConstantsReply	rep;
    int				convertFP;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetFPReqExtra (GetImpDepConstants,
	numNames * sizeof (CARD16), req, convertFP);

    req->drawable = drawable;
    req->numNames = numNames;

    COPY_AREA ((char *) names, (char *) &req[1], numNames * sizeof (CARD16));

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
	*constantsReturn = NULL;
        return (0);            /* return an error */
    }


    /*
     * Allocate a buffer for the client.
     */

    *constantsReturn = (PEXImpDepConstant *) PEXAllocBuf (
	(unsigned) (numNames * sizeof (PEXImpDepConstant)));


    /*
     * Copy the values into the buffer.
     */

    _XRead (display, (char *) *constantsReturn,
	(long) (numNames * sizeof (CARD32)));


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (1);
}


Status
PEXMatchRenderingTargets (display, drawable, depth, type, visual,
    maxTargets, numTargets, targets)

INPUT Display			*display;
INPUT Drawable			drawable;
INPUT int			depth;
INPUT int			type;
INPUT Visual			*visual;
INPUT unsigned long  	        maxTargets;
OUTPUT unsigned long		*numTargets;
OUTPUT PEXRenderingTarget	**targets;

{
    pexMatchRenderingTargetsReq		*req;
    pexMatchRenderingTargetsReply       rep;
    PEXRenderingTarget			*info;
    pexRendererTarget			*matchRec;
    int					i;


    /*
     * Lock around the critical section, for multithreading.
     */

    LockDisplay (display);


    /*
     * Put the request in the X request buffer and get a reply.
     */

    PEXGetReq (MatchRenderingTargets, req);

    req->drawable = drawable;
    req->depth = depth;
    req->type = type;
    req->visualID = visual ? visual->visualid : 0;
    req->maxTriplets = maxTargets;

    if (_XReply (display, &rep, 0, xFalse) == 0)
    {
        UnlockDisplay (display);
        PEXSyncHandle (display);
	*numTargets = 0;
	*targets = NULL;
        return (0);               /* return an error */
    }

    *numTargets = rep.length / 2;


    /*
     * Allocate a scratch buffer and copy the reply data to the buffer.
     */

    matchRec = (pexRendererTarget *) _XAllocScratch (display,
	(unsigned long) (rep.length << 2));

    _XRead (display, (char *) matchRec, (long) (rep.length << 2));


    /*
     * Allocate a buffer for the target list to pass back to the client.
     */

    *targets = info = (PEXRenderingTarget *) PEXAllocBuf (
	(unsigned) (*numTargets * sizeof (PEXRenderingTarget)));

    for (i = 0; i < *numTargets; i++)
    {
	info->depth = matchRec->depth;
	info->type = matchRec->type;
	info->visual = _XVIDtoVisual (display, matchRec->visualID);
	info++;
	matchRec++;
    }


    /*
     * Done, so unlock and check for synchronous-ness.
     */

    UnlockDisplay (display);
    PEXSyncHandle (display);

    return (1);
}


/*
 * Routine called to convert an Output Command error from wire format
 * to client format.  The callback is set up in PEXInitialize.
 */

Bool
_PEXConvertOCError (display, client_error, wire_error)

INPUT Display		*display;
OUTPUT XErrorEvent	*client_error;
INPUT xError		*wire_error;

{
    PEXOCErrorEvent		*client = (PEXOCErrorEvent *) client_error;
    pexOutputCommandError	*wire = (pexOutputCommandError *) wire_error;


    /*
     * PEXOCErrorEvent = XErrorEvent + oc_op_code + ocs_processed_count
     * Xlib will convert all of the XErrorEvent fields.  We must
     * convert the op code and count.
     */

    client->op_code = wire->opcode;
    client->count = wire->numCommands;

    return (True);
}


/*
 * Routine called when an Output Command error is printed.
 * The callback is set up in PEXInitialize.
 */

void
_PEXPrintOCError (display, error, fp)

INPUT Display		*display;
INPUT XErrorEvent	*error;
#ifdef __STDC__
INPUT void		*fp;
#else
INPUT FILE		*fp;
#endif
{
    /*
     * Xlib bug - extension codes should be passed to this function,
     * but they're not.  We must get them ourselves.
     */

    PEXDisplayInfo 	*pexDisplayInfo;
    char		opcode_message[PEXErrorStringLength];
    char		oc_count_message[PEXErrorStringLength];


    PEXGetDisplayInfo (display, pexDisplayInfo);

    if (error->error_code ==
	pexDisplayInfo->extCodes->first_error + BadPEXOutputCommand)
    {
	PEXOCErrorEvent	*oc_error = (PEXOCErrorEvent *) error;

	XGetErrorDatabaseText (display,
	    "PEXlibMessage", "OCErrorOpCode",
	    "Opcode of failed output command : %d\n",
            opcode_message, PEXErrorStringLength);

	XGetErrorDatabaseText (display,
	    "PEXlibMessage", "OCErrorCount",
	    "Number of output commands processed before error : %d\n",
            oc_count_message, PEXErrorStringLength);

	fprintf (fp, "  ");
	fprintf (fp, opcode_message, oc_error->op_code);

	fprintf (fp, "  ");
	fprintf (fp, oc_count_message, oc_error->count);
    }
}


/*
 * Routine called when a display is closed via XCloseDisplay.
 * The callback is set up in PEXInitialize.
 */

int
_PEXCloseDisplay (display, codes)

INPUT Display	*display;
INPUT XExtCodes	*codes;

{
    PEXDisplayInfo	*pexDisplayInfo;


    /*
     * Free the extension codes and other info attached to this display.
     */

    PEXRemoveDisplayInfo (display, pexDisplayInfo);

    if (pexDisplayInfo == NULL)
	return (0);

    PEXFreeBuf ((char *) (pexDisplayInfo->extInfo->vendor_name));
    PEXFreeBuf ((char *) (pexDisplayInfo->extInfo));
    PEXFreeBuf ((char *) (pexDisplayInfo->fpSupport));
    PEXFreeBuf ((char *) pexDisplayInfo);


    /*
     * Free the pick path cache (if it's not in use)
     */

    if (PEXPickCache && !PEXPickCacheInUse)
	PEXFreeBuf ((char *) PEXPickCache);

    return (1);
}
