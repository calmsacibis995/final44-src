/* $XConsortium: copyall2.c,v 5.1 91/02/16 10:00:41 rws Exp $ */

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
## copyall2.c - test pcopy_all_elems_struct() on some variable-length
## data - copy a structure with some variable-length elements,
## confirm with pinq_elem_content().
 */

#include "phigs/phigs.h"
#include "X11/Xlib.h"
#include "X11/Xutil.h"
#include "X11/Xatom.h"
#include <strings.h>
#include "logmsg.h"
#include "imath.h"
#include "computils.h"

#define WS1     1
#define STR1    1
#define STR2	2


main()
{
    Pint            error;
    Pint            actual;
    Pint         wstype;
    Pconnid_x_drawable ws_conn;
    Pint            elemsize;
    Window          ws_window;
    Display	    *ws_display;
    Pelem_type         inqtype;
    Pelem_data	    inqdata;
    Pint            inqsize, totalsize;
    int		curr_element = 0;
    int 	    i, j;
    char            *buffer;

    /* variables and structures for sample data */

    Pelem_data		peldata;

    static Pint tenpints[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    static Pint_list pintlst = {10, tenpints};

    static Ppoint3	ppoint3s[] = { {0.5, 0.5, 0.5},
				      {0.7, 0.3, 0.6},
				      {0.1, 2.3, 0.1} };
    static Ppoint3	ppoint3 = {0.4, 0.3, 0.1};
    static Ppoint_list3  pointlist = {3, ppoint3s};
    static Pvec3	pvector3_array[2] = {{0.0, 1.0, 0.0},
					     {0.5, 0.5, 0.2}};


    tbegintest("copyall2", "test COPY ALL ELEMENTS FROM STRUCTURE w/ variable length data\n");

    /* 
     * Set up phigs, workstation, and first structure
     */
    i_open_phigs(NULL, PDEF_MEM_SIZE);
    i_open_ws(WS1);
    popen_struct(STR1);
    ppost_struct(WS1, STR1, 1.0);

    /*
     * Put an add names to set, a polyline3, and a text3 into first structure
     */
    padd_names_set(&pintlst);
    ppolyline3(&pointlist);
    ptext3(&ppoint3, pvector3_array, "hello world");


    /* 
     * Close the first structure, open a new one, copy the 
     * first structure into the second
     */
    pclose_struct();
    popen_struct(STR2);
    pcopy_all_elems_struct(STR1);

    /*
     * Confirm the copied data
     */
    peldata.names = pintlst;
    i_check_element(STR2, 1, PELEM_ADD_NAMES_SET, &peldata,
		    "PELEM_ADD_NAMES_SET");

    peldata.point_list3 = pointlist;
    i_check_element(STR2, 2, PELEM_POLYLINE3,
		    &peldata, "PELEM_POLYLINE3");

    peldata.text3.pos = ppoint3;
    peldata.text3.dir[0] = pvector3_array[0];
    peldata.text3.dir[1] = pvector3_array[1];
    peldata.text3.char_string = "hello world";
    i_check_element(STR2, 3, PELEM_TEXT3,
		    &peldata, "PELEM_TEXT3");


    tendtest();
}
