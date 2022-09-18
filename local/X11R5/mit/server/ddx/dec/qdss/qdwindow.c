/***********************************************************
Copyright 1987, 1988 by Digital Equipment Corporation, Maynard, Massachusetts,
and the Massachusetts Institute of Technology, Cambridge, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Digital or MIT not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

#include "X.h"
#include "windowstr.h"
#include "qd.h"
#include "gcstruct.h"
#include "scrnintstr.h"
#include "regionstr.h"
#include "mi.h"

extern WindowPtr *WindowTable;

Bool
qdDestroyWindow(pWin)
WindowPtr pWin;
{
    return (TRUE);
}

Bool
qdChangeWindowAttributes(pWin, mask)
    register WindowPtr pWin;
    register int mask;
{
    return TRUE;
}

Bool
qdMapWindow(pWindow)
WindowPtr pWindow;
{
}

Bool
qdUnmapWindow(pWindow, x, y)
WindowPtr pWindow;
int x, y;
{
}

Bool
qdPositionWindow(pWindow)
WindowPtr pWindow;
{
}

extern	int	Nplanes;

/*
 * DDX CopyWindow is required to translate prgnSrc by
 * pWin->absCorner - ptOldOrg .
 *
 * This change appears to have been made by MIT.  -dwm
 */
void
qdCopyWindow(pWin, ptOldOrg, prgnSrc)
    WindowPtr pWin;
    DDXPointRec ptOldOrg;
    RegionPtr prgnSrc;
{
    GCPtr pcopyGC;
    WindowPtr pwinRoot;
    ScreenPtr pScreen;
    int               dx, dy;
    BoxRec	box;    
    RegionPtr	clientClip;
    int		n;
    int		x, y, w, h;
    int		sx, sy;
    XID		subwindowMode = IncludeInferiors;

    dx = QDWIN_X(pWin) - ptOldOrg.x;
    dy = QDWIN_Y(pWin) - ptOldOrg.y;
    pScreen = pWin->drawable.pScreen;
    pwinRoot = WindowTable[pScreen->myNum];

    (*pScreen->TranslateRegion) (prgnSrc, dx, dy);

    pcopyGC = GetScratchGC( Nplanes, pScreen);
    DoChangeGC( pcopyGC, GCSubwindowMode, &subwindowMode, 0);

    clientClip = (*pScreen->RegionCreate) (NULL, 1);
    (*pScreen->Intersect) (clientClip, &pWin->borderClip, prgnSrc);
    box = * (*pScreen->RegionExtents) (clientClip);
    qdChangeClip(pcopyGC, CT_REGION, (pointer) clientClip, 0);

    ValidateGC( pwinRoot, pcopyGC);

    x = box.x1;
    y = box.y1;
    w = ((int) box.x2) - x;
    h = ((int) box.y2) - y;
    sx = x - dx;
    sy = y - dy;

    qdCopyAreaWin(pwinRoot, pwinRoot, pcopyGC, sx, sy, w, h, x, y);
    (*pwinRoot->drawable.pScreen->BlockHandler) ();
    qdChangeClip(pcopyGC, CT_NONE, (pointer) NULL, 0);

    FreeScratchGC( pcopyGC);
}


Bool
qdCreateWindow(pWin)
WindowPtr pWin;
{
    return TRUE;
}
