/* $XConsortium: miRndText.c,v 5.1 91/02/16 09:55:04 rws Exp $ */


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
#include "miRender.h"
#include "misc.h"
#include "miscstruct.h"
#include "PEXErr.h"
#include "extnsionst.h"
#include "gcstruct.h"
#include "ddpex2.h"

#include <stdio.h>

/*++
 |
 |  Function Name:	miRenderText
 |
 |  Function Description:
 |	 Renders Text to the screen.
 |
 |  Note(s):
 |
 --*/

ddpex3rtn
miRenderText(pRend, pddc, input_list)
/* in */
    ddRendererPtr       pRend;          /* renderer handle */
    miDDContext         *pddc;          /* dd context handle */
    miListHeader        *input_list;    /* fill area data */
{
/* calls */
      ddpex3rtn		miFilterPath();

/* Local variable definitions */
      miListHeader	*temp_list;
      listofddPoint	*sp;
      int		j;
      ddpex3rtn		err = Success;

      /* Remove all data  but vertex coordinates */
      if ((DD_IsVertNormal(input_list->type)) ||
	  (DD_IsVertEdge(input_list->type)) ||
	  (DD_IsVertColour(input_list->type)) ) {
	err = miFilterPath(pddc, input_list, &temp_list, 1);
	if (err) return (err);
	input_list = temp_list;
      }

      /*
       * Update the text GC to reflect the current 
       * text attributes 
       */
      if (pddc->Static.misc.flags & TEXTGCFLAG)
	miDDC_to_GC_text(pRend, pddc, pddc->Static.misc.pTextGC);

      /* Validate GC prior to start of rendering */

      if (pddc->Static.misc.pTextGC->serialNumber != 
	  pRend->pDrawable->serialNumber)
        ValidateGC(pRend->pDrawable, pddc->Static.misc.pTextGC);

      /* We should have DC paths here; Render them */

      for (j = 0, sp = input_list->ddList; 
	   j < input_list->numLists; j++, sp++) {
        if (sp->numPoints > 0) {

	  /* Call ddx to render the polylines */
	  (*GetGCValue(pddc->Static.misc.pTextGC, ops->Polylines)) 
			(pRend->pDrawable,
			 pddc->Static.misc.pTextGC, 
			CoordModeOrigin, 
			sp->numPoints, 
			sp->pts.p2DSpt);
        }
      }
}
