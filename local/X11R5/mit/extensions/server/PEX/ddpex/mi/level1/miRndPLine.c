/* $XConsortium: miRndPLine.c,v 5.1 91/02/16 09:55:04 rws Exp $ */


/***********************************************************
Copyright (c) 1989, 1990, 1991 by Sun Microsystems, Inc. and the X Consortium.

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
#include "mipex.h"
#include "misc.h"
#include "miscstruct.h"
#include "PEXErr.h"
#include "miRender.h"
#include "extnsionst.h"
#include "gcstruct.h"
#include "ddpex2.h"

#include <stdio.h>

/*++
 |
 |  Function Name:	miRenderPolyLine
 |
 |  Function Description:
 |	 Renders Polylines to the screen.
 |
 |  Note(s):
 |
 --*/

ddpex3rtn
miRenderPolyLine(pRend, pddc, input_list)
/* in */
    ddRendererPtr       pRend;          /* renderer handle */
    miDDContext         *pddc;          /* dd context handle */
    miListHeader        *input_list;    /* fill area data */
{
/* calls */
      ddpex3rtn		miFilterPath();
      ddpex3rtn		miClipPolyLines();

/* Local variable definitions */
      listofddPoint	*pddlist;
      ddPointUnion	pt;
      ddCoord2DS	line[2];
      GCPtr		pGC;
      ddULONG		colourindex;
      ddColourSpecifier	intcolour;
      int		j;
      int		count;

   /*
    * Update the fill area GC to reflect the current 
    * polyline  attributes 
    */
   if (pddc->Static.misc.flags & POLYLINEGCFLAG)
     miDDC_to_GC_polyline(pRend, pddc, pddc->Static.misc.pPolylineGC);

   /* Polyline with Data ? */
   if (!DD_IsVertColour(input_list->type))
     {

      /* validate GC prior to start of rendering */
      if (pddc->Static.misc.pPolylineGC->serialNumber != 
	  pRend->pDrawable->serialNumber)
        ValidateGC(pRend->pDrawable, pddc->Static.misc.pPolylineGC);

      /* We should have DC paths here; Render them */
      for (j = 0, pddlist = input_list->ddList; 
	   j < input_list->numLists; j++, pddlist++) {
        if (pddlist->numPoints > 0) {

	  /* Call ddx to render the polylines */
	  (*GetGCValue(pddc->Static.misc.pPolylineGC, ops->Polylines)) 
			(pRend->pDrawable,
			pddc->Static.misc.pPolylineGC, 
			CoordModeOrigin, 
			pddlist->numPoints, 
			pddlist->pts.p2DSpt);
        }
      }
    }
   else
    {
      pGC = pddc->Static.misc.pPolylineGC;

      intcolour.colourType = PEXRgbFloatColour;

      /* Render each bound as a polyline */
      for (j = 0, pddlist = input_list->ddList; 
	   j < input_list->numLists; j++, pddlist++) {

         if ((count = pddlist->numPoints) <= 1) continue;

	 pt = pddlist->pts;

	 /* Each polyline segment has a (potentially) different color */
         while (--count) {

	   /* Compute index value for ddx */
	   line[0] = *(pt.p2DSpt++);
	   /* Use first vertex color for line color if no interpolation 
	    * Use line color attribute if highlighting.
	    */
	   if (!MI_DDC_IS_HIGHLIGHT(pddc))  
	   	intcolour.colour.rgbFloat = *(pt.pRgbFloatClr++);
	   else {
	   	intcolour.colour.rgbFloat = 
			pddc->Static.attrs->lineColour.colour.rgbFloat;
		pt.pRgbFloatClr++;
	   }
	   /* Note, can't have any other per-vertex data other than color */
	   line[1] = *pt.p2DSpt;

	   miColourtoIndex( pRend, pddc->Dynamic->pPCAttr->colourApproxIndex,
			    &intcolour, &colourindex);

	   /* Only set GC value if necessary */
	   if (colourindex != pGC->fgPixel) {
	     pGC->fgPixel = colourindex;
	     /* Register changes with ddx */
	     pGC->serialNumber |= GC_CHANGE_SERIAL_BIT;
	     pGC->stateChanges |= GCForeground;
	     (*pGC->funcs->ChangeGC)(pGC, GCForeground);
	     /* Insure that the GC is reset to proper color next time */
	     pddc->Static.misc.flags |= POLYLINEGCFLAG;
	   }

	   /* validate GC prior to start of rendering */
	   if (pGC->serialNumber != pRend->pDrawable->serialNumber)
	     ValidateGC(pRend->pDrawable, pGC);

	   /* Call ddx to render the polyline */
	   (*GetGCValue(pGC, ops->Polylines)) 
		        (pRend->pDrawable,
		        pGC,
		        CoordModeOrigin, 
		        2,
		        line);
	   }
         }
    }

    return (Success);
}
