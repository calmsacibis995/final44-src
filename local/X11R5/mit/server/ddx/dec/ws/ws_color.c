/***********************************************************
Copyright 1991 by Digital Equipment Corporation, Maynard, Massachusetts,
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
/* $XConsortium: ws_color.c,v 1.4 91/07/08 13:32:31 keith Exp $ */

/* 
 * ws_color.c - device specific color routines, stored in screen
 * 
 * Author:	Jim Gettys
 * 		Digital Equipment Corporation
 * 		Cambridge Research Laboratory
 * Date:	Sat January 24 1990
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/time.h>
#include <sys/tty.h>
#include <errno.h>
#include <sys/devio.h>
#include "X.h"          /* required for DoRed ... */
#include "Xproto.h"     /* required for xColorItem */

#include "misc.h"       /* required for colormapst.h */
#include "resource.h"
#include "scrnintstr.h"
#include "colormapst.h"
/* XXX */
#include <sys/workstation.h>

#include "ws.h"



/* these next two are DIX routines */
extern int      TellLostMap();
extern int      TellGainedMap();

extern int wsFd;
extern ws_screen_descriptor screenDesc[];

void
wsStoreColors(pmap, ndef, pdefs)
    ColormapPtr pmap;
    int         ndef;
    xColorItem  *pdefs;
{
    xColorItem	directDefs[256];
    ws_color_cell cell;
    ws_color_map_data cd;
    wsScreenPrivate *pPrivScreen = (wsScreenPrivate *) 
    pmap->pScreen->devPrivates[wsScreenPrivateIndex].ptr;
    if (pmap != pPrivScreen->pInstalledMap) return;

    if ((pmap->pVisual->class | DynamicClass) == DirectColor)
    {
	ndef = cfbExpandDirectColors (pmap, ndef, pdefs, directDefs);
	pdefs = directDefs;
    }
    cd.screen = screenDesc[pmap->pScreen->myNum].screen;
    cd.map = 0;		/* only one... */
    cd.start = 0;
    cd.ncells = ndef;
    /* 
     * we will be evil, and note that the server and drive use the same
     * structure.
     */
    cd.cells = (ws_color_cell *)pdefs;
    if (ioctl(wsFd, WRITE_COLOR_MAP, &cd) == -1) {
	ErrorF("error writing color map\n");
	return;
    }
}

#define _DUPRGB(C,V) ( (( (C) << (V)->offsetRed   ) & (V)->redMask  )\
		      |(( (C) << (V)->offsetGreen ) & (V)->greenMask)\
		      |(( (C) << (V)->offsetBlue  ) & (V)->blueMask ) )

void
wsInstallColormap(pcmap)
	ColormapPtr	pcmap;
{
    int         entries = pcmap->pVisual->ColormapEntries;
    Pixel *     ppix;
    xrgb *      prgb;
    xColorItem *defs;
    int         i;
    wsScreenPrivate *pPrivScreen = (wsScreenPrivate *) 
      pcmap->pScreen->devPrivates[wsScreenPrivateIndex].ptr;

    if (pcmap == pPrivScreen->pInstalledMap)  return;
    if ( pPrivScreen->pInstalledMap != NOMAPYET)
        WalkTree( pcmap->pScreen, TellLostMap, 
		 &pPrivScreen->pInstalledMap->mid);

    pPrivScreen->pInstalledMap = pcmap;

    /* if Turbochannel mfb (2 entry StaticGray), do not store any colors */
    if (pcmap->class != StaticGray || entries != 2) {

	/* If we have an 8 entry TrueColor map, then get all 256 pixel
	    values so we can fake a TrueColor visual with an undecomposed
	    hardware colormap (ie. devPriv == 0).
	*/
	if (pcmap->devPriv == 0 && pcmap->class == TrueColor && entries == 8) {
	    entries = 256;
	}

	ppix = (Pixel *)ALLOCATE_LOCAL( entries * sizeof(Pixel));
	prgb = (xrgb *)ALLOCATE_LOCAL( entries * sizeof(xrgb));
	defs = (xColorItem *)ALLOCATE_LOCAL(entries * sizeof(xColorItem));
    
	/* devPriv == 1 means decomposed hardware colormap */
	if ((int) pcmap->devPriv == 1
	    && ((pcmap->class | DynamicClass) == DirectColor))
	    for( i = 0; i < entries; i++)
		   ppix[i] = _DUPRGB( i, pcmap->pVisual);
	else
	    for ( i=0; i<entries; i++)  ppix[i] = i;

	QueryColors( pcmap, entries, ppix, prgb);

	for ( i=0; i<entries; i++) { /* convert xrgbs to xColorItems */
	    defs[i].pixel = ppix[i] & 0xff;  	/* change pixel to index */
	    defs[i].red = prgb[i].red;
	    defs[i].green = prgb[i].green;
	    defs[i].blue = prgb[i].blue;
	    defs[i].flags =  DoRed|DoGreen|DoBlue;
	}
	wsStoreColors( pcmap, entries, defs);
    
	DEALLOCATE_LOCAL(ppix);
	DEALLOCATE_LOCAL(prgb);
	DEALLOCATE_LOCAL(defs);
    }
    WalkTree(pcmap->pScreen, TellGainedMap, &pcmap->mid);
}


void
wsUninstallColormap(pcmap)
    ColormapPtr pcmap;
{
    /*  Replace installed colormap with default colormap */

    ColormapPtr defColormap;
    wsScreenPrivate *pPrivScreen = (wsScreenPrivate *) 
      pcmap->pScreen->devPrivates[wsScreenPrivateIndex].ptr;

    if ( pcmap != pPrivScreen->pInstalledMap) return;

    defColormap = (ColormapPtr) LookupIDByType( pcmap->pScreen->defColormap,
                        RT_COLORMAP);

    if (defColormap == pPrivScreen->pInstalledMap) return;

    (*pcmap->pScreen->InstallColormap) (defColormap);
}

int
wsListInstalledColormaps( pscr, pcmaps)
    ScreenPtr   pscr;
    Colormap *  pcmaps;
{
    wsScreenPrivate *pPrivScreen = (wsScreenPrivate *) 
    	pscr->devPrivates[wsScreenPrivateIndex].ptr;
    *pcmaps = pPrivScreen->pInstalledMap->mid;
    return 1;
}

