/* $XConsortium: miText.h,v 5.1 91/02/16 09:54:52 rws Exp $ */

/***********************************************************
Copyright (c) 1989,1990, 1991 by Sun Microsystems, Inc. and the X Consortium.

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

#ifndef MI_TEXT_H
#define MI_TEXT_H

#include "miRender.h"

#define HEIGHT      100.0

typedef struct {
    ddVector2D          trans;    /* Translation per character */
    miListHeader        *path;    /* Strokes for char */
  }miCharPath;

typedef struct {
              /* Following can be cached */
    miCharPath          *paths;      /* Char data */
    ddFLOAT             xform[4][4]; /* CC_to_MC_Xform */
              /* More cache data may follow, e.g. text attrs. */
  }miTextElement;

#endif	/*MI_TEXT_H*/
