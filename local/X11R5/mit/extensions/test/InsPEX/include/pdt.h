
/* $XConsortium: pdt.h,v 5.1 91/02/16 10:04:33 rws Exp $ */

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
 * pdt.h: implementation dependent data for PHIGS description table
 */

/* number of available workstation types */
Pint num_ws_type = 2;

/* list of available workstation types */
/* Note: C compiler does not allowed initilization of a variable using
   other variables, but allow pointer to variables */
Pint *list_ws_type_ptr[] =
        { &phigs_ws_type_x_drawable, &phigs_ws_type_x_tool};

/* maximum number of simultaneously open workstations */
Pint max_open_ws = 20;

/* maximum number of simultaneously archive files */
Pint max_open_ar = 25;

/* number of available names for name sets */
Pint num_names_nameset = 256;

/* number of available characters sets */
Pint num_char_set = 1;

/* list of available character sets */
Pint list_char_set[] = { PCS_ASCII };

/* maximum number of normal filter list for ISS */
Pint max_norm_filter = 100;

/* maximum number of inverted filter list for ISS */
Pint max_inv_filter = 100;

/* number of available generalized structure elements */
Pint num_gse = 0;

/* list of generalized structure element's identifier and its workstation-
   dependency */
Pgse_id_dep list_gse_id_wsdep[] = {NULL};

/* maximum number of distinct planes in modelling clipping volumes */
Pint max_distinct_planes = 64;

/* number of available modelling clipping operators */
Pint num_model_clip_op = 2;

/* list of available modelling clipping operators */
Pint list_model_clip_op[] = {PMC_REPLACE,PMC_INTERSECT};

