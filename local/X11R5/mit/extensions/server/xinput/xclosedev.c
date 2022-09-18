/* $Header: xclosedev.c,v 1.9 91/01/24 16:24:01 rws Exp $ */

/************************************************************
Copyright (c) 1989 by Hewlett-Packard Company, Palo Alto, California, and the 
Massachusetts Institute of Technology, Cambridge, Massachusetts.

			All Rights Reserved

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation, and that the names of Hewlett-Packard or MIT not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.

HEWLETT-PACKARD DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
HEWLETT-PACKARD BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

********************************************************/

/***********************************************************************
 *
 * Extension function to close an extension input device.
 *
 */

#define	 NEED_EVENTS
#define	 NEED_REPLIES
#include "X.h"				/* for inputstr.h    */
#include "Xproto.h"			/* Request macro     */
#include "inputstr.h"			/* DeviceIntPtr	     */
#include "windowstr.h"			/* window structure  */
#include "scrnintstr.h"			/* screen structure  */
#include "XI.h"
#include "XIproto.h"

extern	ScreenInfo	screenInfo;
extern	WindowPtr	*WindowTable;
extern	int 		IReqCode;
extern	int 		BadDevice;
extern	void		(* ReplySwapVector[256]) ();
DeviceIntPtr		LookupDeviceIntRec();

/***********************************************************************
 *
 * This procedure closes an input device.
 *
 */

int
SProcXCloseDevice(client)
    register ClientPtr client;
    {
    register char n;

    REQUEST(xCloseDeviceReq);
    swaps(&stuff->length, n);
    return(ProcXCloseDevice(client));
    }

/***********************************************************************
 *
 * This procedure closes an input device.
 *
 */

int
ProcXCloseDevice(client)
    register ClientPtr client;
    {
    int			i;
    WindowPtr 		pWin, p1;
    DeviceIntPtr 	d;

    REQUEST(xCloseDeviceReq);
    REQUEST_SIZE_MATCH(xCloseDeviceReq);

    d = LookupDeviceIntRec (stuff->deviceid);
    if (d == NULL)
	{
	SendErrorToClient(client, IReqCode, X_CloseDevice, 0, BadDevice);
        return Success;
	}

    if (d->grab && SameClient(d->grab, client))
	(*d->DeactivateGrab)(d);		       /* release active grab */

    /* Remove event selections from all windows for events from this device 
       and selected by this client.
       Delete passive grabs from all windows for this device.	   */

    for (i=0; i<screenInfo.numScreens; i++)
	{
	pWin = WindowTable[i];
        DeleteDeviceEvents (d, pWin, client);
	p1 = pWin->firstChild;
	DeleteEventsFromChildren (d, p1, client);
	}

    CloseInputDevice (d, client);
    return Success;
    }

/***********************************************************************
 *
 * Walk througth the window tree, deleting event selections for this client
 * from this device from all windows.
 *
 */

DeleteEventsFromChildren(dev, p1, client)
    DeviceIntPtr	dev;
    WindowPtr 		p1;
    ClientPtr		client;
    {
    WindowPtr p2;

    while (p1)
        {
        p2 = p1->firstChild;
	DeleteDeviceEvents (dev, p1, client);
	DeleteEventsFromChildren(dev, p2, client);
	p1 = p1->nextSib;
        }
    }

/***********************************************************************
 *
 * Clear out event selections and passive grabs from a window for the
 * specified device.
 *
 */

DeleteDeviceEvents (dev, pWin, client)
    DeviceIntPtr	dev;
    WindowPtr		pWin;
    ClientPtr		client;
    {
    InputClientsPtr	others;
    OtherInputMasks	*pOthers;
    GrabPtr		grab, next;

    if (pOthers=wOtherInputMasks(pWin))
	for (others=pOthers->inputClients; others; 
	    others = others->next)
	    if (SameClient(others,client))
		others->mask[dev->id] = NoEventMask;

    for (grab = wPassiveGrabs(pWin); grab; grab=next)
	{
	next = grab->next;
	if ((grab->device == dev) &&
	    (client->clientAsMask == CLIENT_BITS(grab->resource)))
		FreeResource (grab->resource, RT_NONE);
	}
    }
