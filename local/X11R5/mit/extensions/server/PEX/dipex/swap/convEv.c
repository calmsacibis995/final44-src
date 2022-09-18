/* $XConsortium: convEv.c,v 1.1 92/03/04 14:19:24 hersh Exp $ */

/************************************************************
Copyright 1992 by The Massachusetts Institute of Technology

Permission to use, copy, modify, and distribute this
software and its documentation for any purpose and without
fee is hereby granted, provided that the above copyright
notice appear in all copies and that both that copyright
notice and this permission notice appear in supporting
docu- mentation, and that the name of MIT not be used in
advertising or publicity pertaining to distribution of the
software without specific prior written permission.
M.I.T. makes no representation about the suitability of
this software for any purpose. It is provided "as is"
without any express or implied warranty.

MIT DISCLAIMS ALL WARRANTIES WITH REGARD TO  THIS  SOFTWARE,
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FIT-
NESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL MIT BE  LI-
ABLE  FOR  ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,  DATA  OR
PROFITS,  WHETHER  IN  AN  ACTION OF CONTRACT, NEGLIGENCE OR
OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION  WITH
THE USE OR PERFORMANCE OF THIS SOFTWARE.

******************************************************************/


#include "X.h"
#include "Xproto.h"
#include "misc.h"
#include "PEX.h"
#include "PEXproto.h"
#include "PEXprotost.h"
#include "pexError.h"
#include "pexSwap.h"
#include "pex_site.h"
#include "ddpex.h"
#include "pexLookup.h"
#include "convertStr.h"

#undef LOCAL_FLAG
#define LOCAL_FLAG extern


/****************************************************************
 *  		EVENTS   					*
 ****************************************************************/



void
SwapPEXMaxHitsReachedEvent(from, to)
pexMaxHitsReachedEvent *from, *to;
{
    to->type = from->type;
    cpswaps (from->sequenceNumber, to->sequenceNumber);
    cpswapl (from->rdr, to->rdr);
}


