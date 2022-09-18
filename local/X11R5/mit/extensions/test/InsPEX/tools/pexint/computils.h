
/* $XConsortium: computils.h,v 5.1 91/02/16 10:00:28 rws Exp $ */

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

#ifndef _computils_h
#define _computils_h

extern int i_compare_Ppoint_list();
extern int i_compare_Ppoint_list3();
extern int i_compare_Ppick_path();
extern int i_compare_Pgcolr();
extern int i_compare_Prefl_props();
extern int i_compare_Pline_bundle_plus();
extern int i_compare_Pmarker_bundle_plus();
extern int i_compare_Ptext_bundle_plus();
extern int i_compare_Pedge_bundle_plus();
extern int i_compare_Pint_bundle_plus();
extern int i_compare_Ppat_rep_plus();
extern int i_compare_Pdcue_bundle();
extern int i_compare_Plight_src_bundle();
extern int i_compare_Pview_rep3();
extern int i_compare_Pline_bundle();
extern int i_compare_Pmarker_bundle();
extern int i_compare_Ptext_bundle();
extern int i_compare_Pedge_bundle();
extern int i_compare_Pint_bundle();
extern int i_compare_Ppat_rep();
extern int i_compare_Pcolr_rep();
extern int i_compare_Pelem_ref_list();
extern int i_compare_Pelem_ref_list_list();
extern int i_compare_Plimit();
extern int i_compare_Plimit3();
extern int i_compare_Pint_list();
extern int i_compare_ordered_Pint_list();
extern int i_compare_Pattrs_list();
extern int i_compare_Pgse_id_dep_list();
extern int i_compare_Pmatrix();
extern int i_compare_Pmatrix3();
extern int i_compare_Ppoint();
extern int i_compare_Ppoint3();
extern int i_compare_Pvec();
extern int i_compare_Pvec3();
extern int i_compare_Pattrs_list();

extern int i_compare_Ptext_font_prec_array();
extern int i_compare_Pint_style_array();

extern int i_compare_Pint_list_to_ints();
extern int i_compare_Par_file_list_to_ids_names();
extern int i_compare_Plimit3();
extern int i_compare_Plimit();

extern int i_check_current_element();
extern int i_check_element();
extern int i_compare_element_content();

#endif /* _computils_h */
