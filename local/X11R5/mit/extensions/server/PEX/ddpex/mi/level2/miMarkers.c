/* $XConsortium: miMarkers.c,v 5.4 92/12/29 17:14:17 mor Exp $ */


/***********************************************************
Copyright 1989, 1990, 1991 by Sun Microsystems, Inc. and the X Consortium.

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
#include "ddpex3.h"
#include "PEXErr.h"
#include "miRender.h"
#include "miStruct.h"
#include "extnsionst.h"
#include "gcstruct.h"
#include "ddpex2.h"
#include "miMarkers.h"
#include "miClip.h"

#include <stdio.h>



/*++
 |
 |  Function Name:	miPolyMarker
 |
 |  Function Description:
 |	 Handles the Polymarker 3D,  and Polymarker 2D ocs.
 |
 |  Note(s):
 |
 --*/

ddpex3rtn
miPolyMarker(pRend, pExecuteOC)
/* in */
    ddRendererPtr       pRend;	  	/* renderer handle */
    miGenericStr       *pExecuteOC;
{
/* calls */
    ddpex3rtn	miTransform();
    ddpex3rtn	miClipPointList();

/* Local variable definitions */
    miMarkerStruct	*ddmarker = (miMarkerStruct *)(pExecuteOC+1);
    miListHeader	*input_list = (miListHeader *)ddmarker;
    miDDContext		*pddc = (miDDContext *)(pRend->pDDContext);
    ddpex3rtn		status;
    miListHeader	*mc_list,
			*mc_clist,
			*cc_list, 
			*clip_list,
			*dc_list;
    ddUSHORT            clip_mode;      /* view or model clipping */
    ddPointType         out_type;

    /* Check for Model clipping */

    if (pddc->Dynamic->pPCAttr->modelClip == PEXClip) {

      ComputeMCVolume(pRend, pddc);      /* Compute  modelling coord version
                                   		of clipping volume */
      clip_mode = MI_MCLIP;

      /* Tranform points to 4D for clipping */
      out_type = input_list->type;
      if (status = miTransform(pddc, input_list, &mc_clist,
				 ident4x4,
				 ident4x4,
				 DD_SetVert4D(out_type)))
          return (status);

      if (status = miClipPointList(pddc, mc_clist, &mc_list, clip_mode)) 
		return(status);

    } else mc_list = input_list;
 
    clip_mode = MI_VCLIP;


    /* 
     * Transform and clip the input list of marker positions. 
     */
    if (status = miTransform(pddc, mc_list, &cc_list, 
			     pddc->Dynamic->mc_to_cc_xform,
			     NULL4x4,
			     DD_HOMOGENOUS_POINT))
   	return (status);

    /* Note that miClipPointList discards clipped points */
    if (status = miClipPointList(pddc, cc_list, &clip_list, clip_mode)) 
		return(status);

    /* if nothing left, return early */
    if (clip_list->numLists <= 0) return(Success);


    /* Transform to DC coordinates */
    if (status = miTransform(pddc, clip_list, &dc_list, 
		 	     pddc->Dynamic->cc_to_dc_xform,
			     NULL4x4,
			     DD_2DS_POINT))
	  return (status);


    return (pddc->Static.RenderProcs[MARKER_RENDER_TABLE_INDEX](pRend,
                                                                pddc,
                                                                dc_list));
}
