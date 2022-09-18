/* $XConsortium: imagelib.h,v 5.1 91/02/16 09:59:42 rws Exp $ */

/*****************************************************************
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

/*
 * imagelib.h - header file for image library functions
 */
#include "portable.h"

#define MAXCOLOR 256

typedef struct i_image {
	XImage *image;
	Unsign16 width;
	Unsign16 height;
	Unsign8 *imagedata;
} I_image;		

typedef struct i_cmap {
	Colormap cmap;
	unsigned long blackpixel;
	Unsign8 ctbl[MAXCOLOR][3];
} I_cmap;		

/*
 * external table of contents
 */
extern void i_diff_image();
extern void i_load_image();
extern void i_load_image2();
extern void i_display_image();
extern void i_free_image();
extern void i_free_cmap();
