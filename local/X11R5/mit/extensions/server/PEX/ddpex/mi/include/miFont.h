/* $XConsortium: miFont.h,v 5.3 91/07/12 17:53:07 hersh Exp $ */

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

/* 
 * font internal format
 */
#ifndef MI_FONT_H
#define MI_FONT_H

#include "ddpex.h"
#include "ddpex3.h"
#include "miRender.h"
#include "PEXprotost.h"

#ifndef SEEK_SET
#define	SEEK_SET	0	/* Set file pointer to "offset" */
#endif
#define START_PROPS 0x100
#define START_DISPATCH(_num_props)  (START_PROPS + 160 * _num_props)
#define START_PATH(_num_ch_, _num_props)  (START_DISPATCH(_num_props) + sizeof(Dispatch) * _num_ch_)
#define NUM_DISPATCH    128

#ifndef PADDING
#define PADDING(n) ( (n)%4 ? (4 - (n)%4) : 0)
#endif /* PADDING */

/* definitions in the local font coordinate system */
#define FONT_COORD_HEIGHT   100.0
#define FONT_COORD_BASE	    0.0
#define FONT_COORD_CAP	    100.0
#define FONT_COORD_HALF	    50.0

typedef enum {
    PATH_2D=0,
    PATH_3D=1,
    PATH_4D=2
} Font_path_type;

typedef struct {
    Font_path_type  type;
    ddFLOAT	    center;
    ddFLOAT	    right;
    ddULONG	    n_vertices;
    miListHeader    strokes;
} Ch_stroke_data;

typedef enum {
    FONT_POLYLINES=0,
    FONT_SPLINES=1,
    FONT_POLYGONS=2
} Font_type;

typedef struct {
    Font_type		font_type;
    char		name[80];
    unsigned long	num_ch;
    float		top, bottom, max_width;
    Ch_stroke_data    **ch_data;    /* list of *Ch_stroke_data, one per char */
    pexFontInfo		font_info;
    pexFontProp	       *properties; /* list of associated properties */
    int		       lutRefCount;/* number of LUTs referencing this font */
    int			freeFlag;   /* should this be freed when no more refs */
} miFontHeader;

typedef struct {
    ddFLOAT    top, bottom, width;
} Meta_font;

typedef struct {
  char      propname[80];
  char      propvalue[80];
}Property;

typedef struct
{
    int     magic;	  /* magic number */
    char    name[80];     /* name of this font */
    float   top,	  /* extreme values */
            bottom,
            max_width;
    int     num_ch;       /* no. of fonts in the set */
    int     num_props;    /* no. of font properties */
    Property *properties; /* array of properties */
} Font_file_header;

typedef struct
{
    float   center,	  /* center of the character */
            right;	  /* right edge */
    long    offset;	  /* offset in the file of the character
			   * description */
} Dispatch;

#endif	/* MI_FONT_H */
