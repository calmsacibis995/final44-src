/* $XConsortium: pexError.h,v 5.2 92/12/04 18:45:00 hersh Exp $ */

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

#ifndef PEX_ERROR_H
#define PEX_ERROR_H

#define NEED_EVENTS
#include "Xproto.h"
#include "dipex.h"

extern unsigned short MinorOpcodeOfRequest();
extern SendErrorToClient();
extern WriteEventsToClient();

#define PEX_ERROR_CODE(error_code) ((error_code) + PexErrorBase)

#define PEX_ERR_EXIT(error_code, problem, cntxt) { \
    (cntxt)->client->errorValue = problem;	\
    return(error_code); }


/*	output command errors	*/

#define PEX_OC_ERROR(ptr, cntxt) {				    \
	(ptr)->type = X_Error;					    \
	(ptr)->sequenceNumber = (cntxt)->client->sequence;	    \
	(ptr)->majorCode = PexReqCode;				    \
	(ptr)->minorCode = MinorOpcodeOfRequest((cntxt)->client);   \
	WriteEventsToClient((cntxt)->client, 1, (xEvent *)(ptr));   }

#endif /* PEX_ERROR_H */
