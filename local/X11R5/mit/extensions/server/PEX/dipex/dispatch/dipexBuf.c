/* $XConsortium: dipexBuf.c,v 5.2 93/01/25 16:11:56 hersh Exp $ */

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

#include "ddpex.h"

ddBuffer *pPEXBuffer;

#define INIT_PEX_BUFFER_SIZE	1024

ddBuffer *
diInitPEXBuffer()
{
    ddBuffer *temp;
    if (!(temp = (ddBuffer *)Xalloc((unsigned long)(sizeof(ddBuffer)))))
	return (0);
    if (!(temp->pHead =(ddPointer)Xalloc((unsigned long)(INIT_PEX_BUFFER_SIZE))))
    {
  	Xfree(temp);
   	return (0);
    }
    temp->bufSize = (ddULONG)INIT_PEX_BUFFER_SIZE;
    temp->dataSize = 0;
    temp->pBuf = temp->pHead;
    return (temp);
}

  
void diFreePEXBuffer(buffer)
    ddBuffer *buffer;
{
    Xfree(buffer->pHead);
    Xfree(buffer);
}

