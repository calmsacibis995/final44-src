
/* $XConsortium: datautils.m,v 5.2 91/07/24 18:39:19 hersh Exp $ */

/*****************************************************************
Copyright (c) 1989, 1990, 1991,1990 by Sun Microsystems, Inc. and the X Consortium.

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



/* initialize array of data:
   IA_...(number, list of structure members composing the specified type)  */
Ppoint4*		IA_Ppoint4(int,VARARG)
Ppoint3*		IA_Ppoint3(int,VARARG)
Ppoint*			IA_Ppoint(int,VARARG)
Pvec3*			IA_Pvec3(int,VARARG)
Pptconorm3*		IA_Pptconorm3(int,VARARG)
Pconorm3* 		IA_Pconorm3(int,VARARG)
Pptnorm3*		IA_Pptnorm3(int,VARARG)
Pptco3*			IA_Pptco3(int,VARARG)

/* initialize array of data:
   IA_...(number, list of the specified type)  */
Pint_list*     		IA_Pint_list(int,VARARG);
Ptrimcurve_list*     	IA_Ptrimcurve_list(int,VARARG);
Ptrimcurve*     	IA_Ptrimcurve(int,VARARG);
Ppoint_list*		IA_Ppoint_list(int,VARARG)
Ppoint_list3*		IA_Ppoint_list3(int,VARARG)
Pelem_type*		IA_Pelem_type(int,VARARG)
Pint*			IA_Pint(int,VARARG)
Pfloat*			IA_Pfloat(int,VARARG)
Pline_vdata_list3* 	IA_Pline_vdata_list3(int,VARARG)
Pedge_data_list* 	IA_Pedge_data_list(int,VARARG)
Pedge_data_list_list* 	IA_Pedge_data_list_list(int,VARARG)
Pfacet_vdata_list3* 	IA_Pfacet_vdata_list3(int,VARARG)
Pint_list_list*		IA_Pint_list_list(int,VARARG)
Pelem_ref_list*	IA_Pelem_ref_list(int,VARARG)
Pelem_ref*		IA_Pelem_ref(int,VARARG)
Pfilter*		IA_Pfilter(int,VARARG)
Par_file*		IA_Par_file(int,VARARG)
Ppick_path*		IA_Ppick_path(int,VARARG)
Ppick_path_elem*	IA_Ppick_path_elem(Pint,VARARG)

/* initialize array of data:
   IA_...(number, union_type,list of data whose format depends on union_type) */
Pcoval* 		IA_Pcoval(int,int,VARARG)

/* initialize complex structure from fundamental data:
   IA_...(number, datatype,colortype,list of data of appropriate format) */
Pline_vdata_list3 	I_Pline_vdata_list3_from_data(VARARG)
Ppoint_list		I_Ppoint_list_from_data(Pint,VARARG)
Ppoint_list3		I_Ppoint_list3_from_data(Pint,VARARG)

/* initialize array of data:
   IA_...(...special cases) */
Ppoint*			IA_2_Ppoint(Pfloat,Pfloat,Pfloat,Pfloat)
Ppoint*			IA_3_Ppoint(Pfloat,Pfloat,Pfloat,Pfloat,Pfloat,Pfloat)
Ppoint*			IA_5_Ppoint(Pfloat,Pfloat,Pfloat,Pfloat,Pfloat,Pfloat,Pfloat,Pfloat,Pfloat,Pfloat)
Ppoint3*		IA_2_Ppoint3(Pfloat,Pfloat,Pfloat,Pfloat,Pfloat,Pfloat)
Ppoint3*		IA_3_Ppoint3(Pfloat,Pfloat,Pfloat,Pfloat,Pfloat,Pfloat,Pfloat,Pfloat,Pfloat)
Ppoint3*		IA_5_Ppoint3(Pfloat,Pfloat,Pfloat,Pfloat,Pfloat,Pfloat,Pfloat,Pfloat,Pfloat,Pfloat,Pfloat,Pfloat,Pfloat,Pfloat,Pfloat)

/* initialize simple data
   I_...(list of structure members composing the specified type)  */
Ptrimcurve      	I_Ptrimcurve(Pedge_flag,Prational,Pint,Pint,Pfloat,Pfloat_list,Pfloat,Pfloat,Ppoint_list23);                                          
Ptrimcurve_list   	I_Ptrimcurve_list(Pint,Ptrimcurve*); 
Pparal			I_Pparal(Ppoint3,Ppoint3,Ppoint3)
Ppoint_list3		I_Ppoint_list3(Pint,Ppoint3*)
Ppoint_list		I_Ppoint_list(Pint,Ppoint*)
Ppoint_list_list3	I_Ppoint_list_list3(Pint,Ppoint_list3*)
Ppoint_list_list	I_Ppoint_list_list(Pint,Ppoint_list*)
Pelem_type_list		I_Pelem_type_list(Pint,Pelem_type*)
Par_file_list 		I_Par_file_list(Pint,Par_file*)
Pint_list 		I_Pint_list(int,Pint*)
Pfloat_list 		I_Pfloat_list(int,Pfloat*)
Pdata			I_Pdata(Pint,char*)
Prect			I_Prect(Ppoint,Ppoint)
Ppoint3			I_Ppoint3(Pfloat,Pfloat,Pfloat)
Ppoint			I_Ppoint(Pfloat,Pfloat)
Pvec3			I_Pvec3(Pfloat,Pfloat,Pfloat)
Pvec			I_Pvec(Pfloat,Pfloat)
Pint_size			I_Pint_size(Pint,Pint)
Phalf_space3		I_Phalf_space3(Ppoint3,Pvec3)
Phalf_space		I_Phalf_space(Ppoint,Pvec)
Ptext_align		I_Ptext_align(Phor_text_align,Pvert_text_align)
Pint_list_list 		I_Pint_list_list(int,Pint_list*)
/*Ppcs_limit  		I_Ppcs_limit(Pfloat,Pfloat,Pfloat,Pfloat)*/
Plimit3  		I_Plimit3(Pfloat,Pfloat,Pfloat,Pfloat,Pfloat,Pfloat)
Plimit  		I_Plimit(Pfloat,Pfloat,Pfloat,Pfloat)
Pconorm3  		I_Pconorm3(Pcoval,Pvec3)
Pfacet_vdata_list3 	I_Pfacet_vdata_list3(int,Pfacet_vdata_arr3)
Pedge_data_list_list 	I_Pedge_data_list_list(int,Pedge_data_list*)
Pedge_data_list		I_Pedge_data_list(int,Pedge_data_arr)
Pline_vdata_list3  	I_Pline_vdata_list3(int,Pline_vdata_arr3)
Prefl_props  		I_Prefl_props(Pfloat,Pfloat,Pfloat,Pgcolr,Pfloat,Pfloat)
Pcolr_rep  		I_Pcolr_rep(Pint,Pfloat,Pfloat,Pfloat)
Pline_bundle  		I_Pline_bundle(Pint,Pfloat,Pint)
Pmarker_bundle 		I_Pmarker_bundle(Pint,Pfloat,Pint)
Pint_bundle  		I_Pint_bundle(Pint,Pint,Pint)
Ptext_bundle  		I_Ptext_bundle(Pint,Ptext_prec,Pfloat,Pfloat,Pint)
Pedge_bundle  		I_Pedge_bundle(Pedge_flag,Pint,Pfloat,Pint)
Ppat_rep  		I_Ppat_rep(Pint_size,Pint*)
Pline_bundle_plus  	I_Pline_bundle_plus(Pint,Pfloat,Pgcolr,Pint,Pint,Pfloat)
Pmarker_bundle_plus 	I_Pmarker_bundle_plus(Pint,Pfloat,Pgcolr)
Pint_bundle_plus  	I_Pint_bundle_plus(Pint,Pint,Pgcolr,Pint,Pint,Prefl_props,
				Pint,Pint,Pgcolr,Pint,Pint,Prefl_props,
				Pint,Pfloat,Pfloat)
Ptext_bundle_plus  	I_Ptext_bundle_plus(Pint,Ptext_prec,Pfloat,Pfloat,Pgcolr)
Pedge_bundle_plus  	I_Pedge_bundle_plus(Pedge_flag,Pint,Pfloat,Pgcolr)
Ppat_rep_plus  	I_Ppat_rep_plus(Pint_size,Pint,Pcoval*)
Pview_rep3			I_Pview_rep3(Pmatrix3,Pmatrix3,Plimit3,Pclip_ind,Pclip_ind,Pclip_ind)
Pview_rep			I_Pview_rep(Pmatrix,Pmatrix,Plimit,Pclip_ind)
Pview_map3		I_Pview_map3(Plimit,Plimit3,Pproj_type,Ppoint3,Pfloat,Pfloat,Pfloat)
Pview_map		I_Pview_map(Plimit,Plimit)
/*Ploc3			I_Ploc3(Pint,Ppoint3)*/
/*Ploc			I_Ploc(Pint,Ppoint)*/
/*Pstroke			I_Pstroke(Pint,Pint,Ppoint*)*/
Pelem_ref_list_list	I_Pelem_ref_list_list(int,Pelem_ref_list*)
Pelem_ref_list	I_Pelem_ref_list(int,Pelem_ref*)
Pelem_ref		I_Pelem_ref(Pint,Pint)
Pfilter			I_Pfilter(Pint_list,Pint_list)
Pfilter_list		I_Pfilter_list(Pint,Pfilter*)
Par_file		I_Par_file(Pint,char*)
Ppick_path_elem		I_Ppick_path_elem(Pint,Pint,Pint)
Ppick_path		I_Ppick_path(Pint,Ppick_path_elem*)

/* initialize simple of data:
   I_...(union_type, list of data whose format depends on union_type) */
Ppara_surf_characs  	I_Ppara_surf_characs(int,VARARG)
Pval_data  		I_Pval_data(int,Pfloat,Pfloat,VARARG)
Pgcolr  		I_Pgcolr(int,VARARG)
Plight_src_bundle  	I_Plight_src_bundle(int,VARARG)
Pline_vdata_arr3  	I_Pline_vdata_arr3(int,VARARG)
Pedge_data_arr 		I_Pedge_data_arr(int,VARARG)
Pfacet_data_arr3 	I_Pfacet_data_arr3(int,VARARG)
Pfacet_data3 		I_Pfacet_data3(int,VARARG)
Pfacet_vdata_arr3 	I_Pfacet_vdata_arr3(int,VARARG)
Pcoval 			I_Pcoval(int,VARARG)
Pelem_data		I_Pelem_data(int,VARARG)

/* initialize simple of data:
   I_...(number, list of specified type */
Phalf_space_list	I_Phalf_space_list(int,VARARG)
Phalf_space_list3	I_Phalf_space_list3(int,VARARG)

/* initialize simple data
   I_...(...special cases) */

void			I_Pmatrix(Pmatrix,float,float,float,float,float,float,float,float,float)
void			I_Pmatrix3(Pmatrix3,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float)

Ppoint_list23 		I_Ppoint_list23(int,char*,VARARG)
Ppoint_list34 		I_Ppoint_list34(int,char*,VARARG)
Ppoint_grid34 		I_Ppoint_grid34(int,int,char*,VARARG)
Pdcue_bundle  		I_Pdcue_bundle(Pdcue_mode,Pfloat,Pfloat,Pfloat,Pfloat,Pgcolr)

