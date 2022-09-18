
/* $XConsortium: datautils.h,v 5.2 91/07/24 18:41:32 hersh Exp $ */

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

#ifndef _datautils_h
#define _datautils_h

#include "phigs/phigs.h"

/* initialize array of data: 
   IA_...(number, list of structure members composing the specified type)  */
extern Ppoint4* 		IA_Ppoint4();
extern Ppoint3* 		IA_Ppoint3();
extern Ppoint* 			IA_Ppoint();
extern Pvec3* 			IA_Pvec3();
extern Pptconorm3*     		IA_Pptconorm3();
extern Pconorm3* 		IA_Pconorm3();
extern Pptnorm3*    		IA_Pptnorm3();
extern Pptco3* 	 		IA_Pptco3();

/* initialize array of data: 
   IA_...(number, list of the specified type)  */
extern Pint_list* 		IA_Pint_list();
extern Ptrimcurve_list* 	IA_Ptrimcurve_list();
extern Ptrimcurve* 		IA_Ptrimcurve();
extern Ppoint_list* 		IA_Ppoint_list();
extern Ppoint_list3* 		IA_Ppoint_list3();
extern Pelem_type*		IA_Pelem_type();
extern Pint*			IA_Pint();
extern Pfloat*			IA_Pfloat();
extern Pline_vdata_list3* 	IA_Pline_vdata_list3();
extern Pedge_data_list* 	IA_Pedge_data_list();
extern Pedge_data_list_list* 	IA_Pedge_data_list_list();
extern Pfacet_vdata_list3* 	IA_Pfacet_vdata_list3();
extern Pint_list_list*		IA_Pint_list_list();
extern Pelem_ref_list*     	IA_Pelem_ref_list();
extern Pelem_ref*     		IA_Pelem_ref();
extern Pfilter*			IA_Pfilter();
extern Par_file*		IA_Par_file();
extern Ppick_path_elem*		IA_Ppick_path_elem();
extern Ppick_path*		IA_Ppick_path();

/* initialize array of data: 
   IA_...(number, union_type,list of data whose format depends on union_type) */
extern Pcoval* 			IA_Pcoval();
extern Pline_vdata_list3	I_Pline_vdata_list3_from_data();
extern Ppoint_list		I_Ppoint_list_from_data();
extern Ppoint_list3		I_Ppoint_list3_from_data();

/* initialize array of data: 
   IA_...(... special cases)  */
extern Ppoint*			IA_2_Ppoint();
extern Ppoint*			IA_3_Ppoint();
extern Ppoint*			IA_5_Ppoint();
extern Ppoint3*			IA_2_Ppoint3();
extern Ppoint3*			IA_3_Ppoint3();
extern Ppoint3*			IA_5_Ppoint3();


/* initialize simple data 
   I_...(list of structure members composing the specified type)  */
extern Ptrimcurve 		I_Ptrimcurve();
extern Ptrimcurve_list 		I_Ptrimcurve_list();
extern Pparal 			I_Pparal();
extern Ppoint_list 		I_Ppoint_list();
extern Ppoint_list3 		I_Ppoint_list3();
extern Ppoint_list_list 	I_Ppoint_list_list();
extern Ppoint_list_list3 	I_Ppoint_list_list3();
extern Pelem_type_list 		I_Pelem_type_list();
extern Par_file_list 		I_Par_file_list();
extern Pint_list 		I_Pint_list();
extern Pfloat_list 		I_Pfloat_list();
extern Pdata			I_Pdata();
extern Prect 			I_Prect();
extern Ppoint3 			I_Ppoint3();
extern Ppoint 			I_Ppoint();
extern Pvec3 			I_Pvec3();
extern Pvec 			I_Pvec();
extern Pint_size 			I_Pint_size();
extern Phalf_space3 		I_Phalf_space3();
extern Phalf_space 		I_Phalf_space();
extern Ptext_align 		I_Ptext_align();
extern Pint_list_list 		I_Pint_list_list();
/*extern Ppcs_limit 		I_Ppcs_limit();*/
extern Plimit3 			I_Plimit3();
extern Plimit 			I_Plimit();
extern Pconorm3  		I_Pconorm3();
extern Pfacet_vdata_list3  	I_Pfacet_vdata_list3();
extern Pedge_data_list_list  	I_Pedge_data_list_list();
extern Pedge_data_list  	I_Pedge_data_list();
extern Pline_vdata_list3  	I_Pline_vdata_list3();
extern Prefl_props 		I_Prefl_props();
extern Pline_bundle 		I_Pline_bundle();
extern Ptext_bundle 		I_Ptext_bundle();
extern Pmarker_bundle 		I_Pmarker_bundle();
extern Pint_bundle 		I_Pint_bundle();
extern Pedge_bundle 		I_Pedge_bundle();
extern Ppat_rep 		I_Ppat_rep();
extern Pline_bundle_plus 	I_Pline_bundle_plus();
extern Ptext_bundle_plus 	I_Ptext_bundle_plus();
extern Pmarker_bundle_plus 	I_Pmarker_bundle_plus();
extern Pint_bundle_plus 		I_Pint_bundle_plus();
extern Pedge_bundle_plus 	I_Pedge_bundle_plus();
extern Ppat_rep_plus 		I_Ppat_rep_plus();
extern Pcolr_rep 		I_Pcolr_rep();
extern Pview_rep3			I_Pview_rep3();
extern Pview_rep			I_Pview_rep();
extern Pview_map3		I_Pview_map3();
extern Pview_map		I_Pview_map();
/*extern Ploc3			I_Ploc3();*/
/*extern Ploc			I_Ploc();*/
/*extern Pstroke			I_Pstroke();*/
extern Pelem_ref_list_list	I_Pelem_ref_list_list();
extern Pelem_ref_list	I_Pelem_ref_list();
extern Pelem_ref		I_Pelem_ref();
extern Pfilter			I_Pfilter();
extern Pfilter_list		I_Pfilter_list();
extern Par_file			I_Par_file();
extern Ppick_path_elem		I_Ppick_path_elem();
extern Ppick_path		I_Ppick_path();

/* initialize simple data: 
   I_...(union_type, list of data whose format depends on union_type) */
extern Ppara_surf_characs 	I_Ppara_surf_characs();
extern Pval_data 		I_Pval_data();
extern Pgcolr 			I_Pgcolr();
extern Plight_src_bundle	I_Plight_src_bundle();
extern Pline_vdata_arr3 	I_Pline_vdata_arr3();
extern Pedge_data_arr  		I_Pedge_data_arr();
extern Pfacet_data_arr3 	I_Pfacet_data_arr3();
extern Pfacet_data3 		I_Pfacet_data3();
extern Pfacet_vdata_arr3 	I_Pfacet_vdata_arr3();
extern Pcoval 			I_Pcoval();
extern Pelem_data 		I_Pelem_data();


/* initialize simple data: 
   I_...(number, list of specified type */
extern Phalf_space_list		I_Phalf_space_list();
extern Phalf_space_list3	I_Phalf_space_list3();

/* initialize simple data 
   I_...(...special cases) */
extern void			I_Pmatrix();
extern void			I_Pmatrix3();
extern Ppoint_list23 		I_Ppoint_list23();
extern Ppoint_list34 		I_Ppoint_list34();
extern Ppoint_grid34 		I_Ppoint_grid34();
extern Pdcue_bundle 		I_Pdcue_bundle();

#endif /* _datautils_h */
