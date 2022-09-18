/* $XConsortium: computils.c,v 5.4 91/07/24 18:43:05 hersh Exp $ */

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
 * computils.c - comparison utilities.
 * This file contains PHIGS testing utilties for data comparison
 */
#include <phigs/phigs.h>
#include "stdio.h"
#include "logmsg.h"
#include "imath.h"
#include "computils.h"

#ifdef NEWT
#include "NewTvararg.h"
#else
#include "varargs.h"
#endif

/*
 * global variables
 */

/*
 * forward declaration
 */
/*
 * export routines
 */
int i_compare_Ppoint_list();
int i_compare_Ppoint_list3();
int i_compare_Ppick_path();
int i_compare_Pdcue_bundle();
int i_compare_Plight_src_bundle();
int i_compare_Pline_bundle_plus();
int i_compare_Pmarker_bundle_plus();
int i_compare_Ptext_bundle_plus();
int i_compare_Pedge_bundle_plus();
int i_compare_Pint_bundle_plus();
int i_compare_Ppat_rep_plus();
int i_compare_Pgcolr();
int i_compare_Prefl_props();
int i_compare_Pview_rep3();
int i_compare_Pline_bundle();
int i_compare_Pmarker_bundle();
int i_compare_Ptext_bundle();
int i_compare_Pedge_bundle();
int i_compare_Pint_bundle();
int i_compare_Ppat_rep();
int i_compare_Pcolr_rep();
int i_compare_Pcoval();
int i_compare_Pelem_ref_list();
int i_compare_Pelem_ref_list_list();
int i_compare_Pint_list();
int i_compare_ordered_Pint_list();
int i_compare_Pgse_id_deplst();
int i_compare_Pmatrix();
int i_compare_Pmatrix3();
int i_compare_Ppoint();
int i_compare_Ppoint3();
int i_compare_Pvec();
int i_compare_Pvec3();
int i_compare_Pattrs_array();

int i_compare_Ptext_font_prec_array();
int i_compare_Pint_style_array();

int i_compare_Pint_list_to_ints();
int i_compare_Par_file_list_to_data();
int i_compare_Plimit3();
int i_compare_Plimit();

int i_compare_Pfacet_data_arr3();
int i_compare_Pfacet_vdata_arr3();

int i_check_current_element();
int i_check_element();
int i_compare_element_content();
/*
 * local routines
 */
static void printPlimit();
static void printPlimit3();

/*
 * The following functions return 1 if the inquired and expected structure
 * carry the same values, 0 otherwise.
 */

/*
 * i_compare_Ppoint_list() 
 */
int
i_compare_Ppoint_list(lst,explst) 
	Ppoint_list lst,explst;
{
	int status = 0;
	int i;

	if (lst.num_points == explst.num_points) {
		for (i=0;i<lst.num_points;i++) 
			if (fne(lst.points[i].x,explst.points[i].x) ||
			    fne(lst.points[i].y,explst.points[i].y) ) {
				break;
			}
		if (i==lst.num_points)
			status = 1;
	}
	if (verbosity >=3 || (verbosity >= 1 && status == 0)) {
		tvprintf(1,"i_compare_Ppoint_list: num points = %d, points =",
			lst.num_points);
		for (i=0;i<lst.num_points;i++)
			printf("(%.4f,%.4f)",lst.points[i].x,
			                    lst.points[i].y);
		printf("; expected: num points = %d, points =",
			explst.num_points);
		for (i=0;i<explst.num_points;i++)
			printf("(%.4f,%.4f)",explst.points[i].x,
			                    explst.points[i].y);
		puts("");
	}
	return(status);
}

/*
 * i_compare_Ppoint_list3() 
 */
int
i_compare_Ppoint_list3(lst,explst) 
	Ppoint_list3 lst,explst;
{
	int status = 0;
	int i;

	if (lst.num_points == explst.num_points) {
		for (i=0;i<lst.num_points;i++) 
			if (fne(lst.points[i].x,explst.points[i].x) ||
			    fne(lst.points[i].y,explst.points[i].y) ||
			    fne(lst.points[i].z,explst.points[i].z) ) {
				break;
			}
		if (i==lst.num_points)
			status = 1;
	}
	if (verbosity >=3 || (verbosity >= 1 && status == 0)) {
		tvprintf(1,"i_compare_Ppoint_list3: num points = %d, points =",
			lst.num_points);
		for (i=0;i<lst.num_points;i++)
			printf("(%.4f,%.4f,%.4f)",lst.points[i].x,
			                    lst.points[i].y,
			                    lst.points[i].z);
		printf("; expected: num points = %d, points =",
			explst.num_points);
		for (i=0;i<explst.num_points;i++)
			printf("(%.4f,%.4f,%.4f)",explst.points[i].x,
			                    explst.points[i].y,
			                    explst.points[i].z);
		puts("");
	}
	return(status);
}

/*
 * i_compare_Ppick_path() 
 */
int
i_compare_Ppick_path(path,exppath) 
	Ppick_path path,exppath;
{
	int status = 0;
	int i;

	if (path.depth == exppath.depth) {
		for (i=0;i<path.depth;i++) 
			if (path.path_list[i].struct_id!=exppath.path_list[i].struct_id ||
			    path.path_list[i].pick_id!=exppath.path_list[i].pick_id ||
			    path.path_list[i].elem_pos!=exppath.path_list[i].elem_pos) {
				break;
			}
		if (i==path.depth)
			status = 1;
	}
	if (verbosity >=3 || (verbosity >= 1 && status == 0)) {
		tvprintf(1,"i_compare_Ppick_path: path depth = %d, path ="
			,path.depth);
		for (i=0;i<path.depth;i++)
			printf("(%d,%d,%d)",path.path_list[i].struct_id,
			                    path.path_list[i].pick_id,
			                    path.path_list[i].elem_pos);
		printf("; expected: path depth = %d, path =",exppath.depth);
		for (i=0;i<exppath.depth;i++)
			printf("(%d,%d,%d)",exppath.path_list[i].struct_id,
			                    exppath.path_list[i].pick_id,
			                    exppath.path_list[i].elem_pos);
		puts("");
	}
	return(status);
}

/*
 * i_compare_Prefl_props() 
 */
int
i_compare_Prefl_props(rep,exprep) 
	Prefl_props rep,exprep;
{
	int status = 0;

	if (i_compare_Pgcolr(rep.specular_colr,exprep.specular_colr)&&
	    feq(rep.ambient_coef,exprep.ambient_coef) && 
	    feq(rep.diffuse_coef,exprep.diffuse_coef) &&
	    feq(rep.specular_coef,exprep.specular_coef) &&
	    feq(rep.specular_exp,exprep.specular_exp)
	    )
		status = 1;

	if (verbosity >=3 || (verbosity >= 1 && status == 0)) {
		tvprintf(1,"i_compare_Prefl_props: ambient_coef,diffuse_coef,specular_coef,specular_exp = (%.4f,%.4f,%.4f,%.4f); expected (%.4f,%.4f,%.4f,%.4f)\n",
			rep.ambient_coef,rep.diffuse_coef,rep.specular_coef,
			rep.specular_exp, 
			exprep.ambient_coef,exprep.diffuse_coef,
			exprep.specular_coef,exprep.specular_exp );
	}
	return(status);
}

/*
 * i_compare_Pgcolr() 
 */
int
i_compare_Pgcolr(col,expcol) 
	Pgcolr col,expcol;
{
	int status = 0;

	if (col.type == expcol.type) {
		if (col.type == PINDIRECT) {
			if (col.val.ind == expcol.val.ind)
				status = 1;
		} else { 
			if (feq(col.val.general.x ,expcol.val.general.x) &&
			    feq(col.val.general.y ,expcol.val.general.y) &&
			    feq(col.val.general.z ,expcol.val.general.z) ) 
				status = 1;
		}
	}
	if (verbosity >=3 || (verbosity >= 1 && status == 0)) {
		tvprintf(1,"i_compare_Pgcolr: colour type %d,expected %d\n",
			col.type,expcol.type);
		if (col.type == expcol.type) {
			if (col.type == PINDIRECT)	
				tvprintf(1,"i_compare_Pgcolr: colour index %d,expected %d\n",
					col.val.ind,expcol.val.ind);
			else
				tvprintf(1,"i_compare_Pgcolr: general colour (%.2f,%.2f,%.2f),expected (%2f,%.2f,%.2f)\n",
					col.val.general.x,col.val.general.y,
					col.val.general.z,expcol.val.general.x,
					expcol.val.general.y,expcol.val.general.z);
		}
	}
	return(status);
}

/*
 * i_compare_Pview_rep3() 
 */
int
i_compare_Pview_rep3(rep,exprep) 
	Pview_rep3 rep,exprep;
{
	int status = 0;

	if (i_compare_Pmatrix3(rep.ori_matrix, exprep.ori_matrix) &&
	    i_compare_Pmatrix3(rep.map_matrix, exprep.map_matrix) &&
	    i_compare_Plimit3(rep.clip_limit, exprep.clip_limit) &&
	    rep.xy_clip == exprep.xy_clip &&
	    rep.front_clip == exprep.front_clip &&
	    rep.back_clip == exprep.back_clip ) 
		status = 1;
	if (verbosity >=3 || (verbosity >= 1 && status == 0)) {
		tvprintf(1,"i_compare_Pview_rep3: xy,front,back clip ind=(%d,%d,%d); expected (%d,%d,%d)\n",
			rep.xy_clip,rep.front_clip,rep.back_clip,
			exprep.xy_clip,exprep.front_clip,exprep.back_clip);
	}
	return(status);
}

/*
 * i_compare_Pline_bundle() 
 */
int
i_compare_Pline_bundle(rep,exprep) 
	Pline_bundle rep,exprep;
{
	int status = 0;

	if (rep.type == exprep.type && 
	    feq(rep.width,exprep.width) &&
	    rep.colr_ind == exprep.colr_ind)
		status = 1;

	if (verbosity >=3 || (verbosity >= 1 && status == 0)) {
		tvprintf(1,"i_compare_Pline_bundle: type,width,colour = (%d,%.4f,%d); expected (%d,%.4f,%d)\n",
			rep.type,rep.width,rep.colr_ind,
			exprep.type,exprep.width,exprep.colr_ind);
	}
	return(status);
}

/*
 * i_compare_Pline_bundle_plus() 
 */
int
i_compare_Pline_bundle_plus(rep,exprep) 
	Pline_bundle_plus rep,exprep;
{
	int status = 0;

	if (i_compare_Pgcolr(rep.colr,exprep.colr) &&
	    rep.type == exprep.type && 
	    feq(rep.width,exprep.width) &&
	    rep.shad_meth == exprep.shad_meth && 
	    rep.approx_type == exprep.approx_type && 
	    feq(rep.approx_val,exprep.approx_val))
		status = 1;

	if (verbosity >=3 || (verbosity >= 1 && status == 0)) {
		tvprintf(1,"i_compare_Pline_bundle_plus: type,width,shading,approx_type,approx_value = (%d,%.4f,%d,%d,%.4f); expected (%d,%.4f,%d,%d,%.4f)\n",
			rep.type,rep.width,
			rep.shad_meth,rep.approx_type,rep.approx_val,
			exprep.type,exprep.width,
			exprep.shad_meth,exprep.approx_type,exprep.approx_val);
	}
	return(status);
}

/*
 * i_compare_Pmarker_bundle() 
 */
int
i_compare_Pmarker_bundle(rep,exprep) 
	Pmarker_bundle rep,exprep;
{

	int status = 0;

	if (rep.type == exprep.type && 
	    rep.colr_ind == exprep.colr_ind && 
	    feq(rep.size,exprep.size) )
		status = 1;
	if (verbosity >=3 || (verbosity >= 1 && status == 0)) {
		tvprintf(1,"i_compare_Pmarker_bundle: type,size,color = (%d,%.4f,%d); expected (%d,%.4f,%d)\n",
			rep.type,rep.size,rep.colr_ind,
			exprep.type,exprep.size,exprep.colr_ind);
	}
	return(status);
}

/*
 * i_compare_Pmarker_bundle_plus() 
 */
int
i_compare_Pmarker_bundle_plus(rep,exprep) 
	Pmarker_bundle_plus rep,exprep;
{
	int status = 0;

	if (i_compare_Pgcolr(rep.colr,exprep.colr)&& 
	   rep.type == exprep.type && 
	   feq(rep.size,exprep.size)) 
		status = 1;
	if (verbosity >=3 || (verbosity >= 1 && status == 0)) {
		tvprintf(1,"i_compare_Pmarker_bundle_plus: type,size,colour = (%d,%.4f,%d); expected (%d,%.4f,%d)\n",
			rep.type,rep.size,exprep.type,exprep.size);
	}
	return(status);
}

/*
 * i_compare_Ptext_bundle() 
 */
int 
i_compare_Ptext_bundle(rep,exprep) 
	Ptext_bundle rep,exprep;
{

	int status = 0;

	if (rep.font == exprep.font && 
	    rep.prec == exprep.prec && 
	    feq(rep.char_expan,exprep.char_expan) &&
	    feq(rep.char_space,exprep.char_space) &&
	    rep.colr_ind == exprep.colr_ind)
		status = 1;

	if (verbosity >=3 || (verbosity >= 1 && status == 0)) {
		tvprintf(1,"i_compare_Ptext_bundle: font,prec,expan,space,col= (%d,%d,%.4f,%.4f,%d); expected (%d,%d,%.4f,%.4f,%d)\n",
			rep.font,rep.prec, rep.char_expan, rep.char_space, rep.colr_ind,
			exprep.font,exprep.prec, exprep.char_expan, exprep.char_space, exprep.colr_ind);
	}
	return(status);
}

/*
 * i_compare_Ptext_bundle_plus() 
 */
int 
i_compare_Ptext_bundle_plus(rep,exprep) 
	Ptext_bundle_plus rep,exprep;
{

	int status = 0;

	if (i_compare_Pgcolr(rep.colr,exprep.colr) &&
	    rep.font == exprep.font && 
	    rep.prec == exprep.prec && 
	    feq(rep.char_expan,exprep.char_expan) &&
	    feq(rep.char_space,exprep.char_space) )
		status = 1;

	if (verbosity >=3 || (verbosity >= 1 && status == 0)) {
		tvprintf(1,"i_compare_Ptext_bundle_plus: font,prec,expan,space = (%d,%d,%.4f,%.4f); expected (%d,%d,%.4f,%.4f)\n",
			rep.font,rep.prec, rep.char_expan, rep.char_space,
			exprep.font,exprep.prec, exprep.char_expan, exprep.char_space);
	}
	return(status);
}

/*
 * i_compare_Pedge_bundle() 
 */
int
i_compare_Pedge_bundle(rep,exprep) 
	Pedge_bundle rep,exprep;
{
	int status = 0;

	if (rep.flag == exprep.flag && 
	    rep.type == exprep.type && 
	    feq(rep.width,exprep.width) &&
	    rep.colr_ind == exprep.colr_ind)
		status = 1;

	if (verbosity >=3 || (verbosity >= 1 && status == 0)) {
		tvprintf(1,"i_compare_Pedge_bundle: flag,type,width,colour = (%d,%d,%.4f,%d); expected (%d,%d,%.4f,%d)\n",
			rep.flag,rep.type,rep.width,rep.colr_ind,
			exprep.flag,exprep.type,exprep.width,exprep.colr_ind);
	}
	return(status);
}

/*
 * i_compare_Pedge_bundle_plus() 
 */
int
i_compare_Pedge_bundle_plus(rep,exprep) 
	Pedge_bundle_plus rep,exprep;
{
	int status = 0;

	if (i_compare_Pgcolr(rep.colr,exprep.colr) &&
	    rep.flag == exprep.flag && 
	    rep.type == exprep.type && 
	    feq(rep.width,exprep.width) )
		status = 1;

	if (verbosity >=3 || (verbosity >= 1 && status == 0)) {
		tvprintf(1,"i_compare_Pedge_bundle_plus: flag,type,width= (%d,%d,%.4f); expected (%d,%d,%.4f)\n",
			rep.flag,rep.type,rep.width,
			exprep.flag,exprep.type,exprep.width);
	}
	return(status);
}

/*
 * i_compare_Pint_bundle() 
 */
int
i_compare_Pint_bundle(rep,exprep) 
	Pint_bundle rep,exprep;
{
	int status = 0;

	if (rep.style == exprep.style && 
	    rep.style_ind == exprep.style_ind &&
	    rep.colr_ind == exprep.colr_ind)
		status = 1;

	if (verbosity >=3 || (verbosity >= 1 && status == 0)) {
		tvprintf(1,"i_compare_Pint_bundle: style,style index,colour = (%d,%d,%d); expected (%d,%d,%d)\n",
			rep.style,rep.style_ind,rep.colr_ind,
			exprep.style,exprep.style_ind,exprep.colr_ind);
	}
	return(status);
}

/*
 * i_compare_Pint_bundle_plus() 
 */
int
i_compare_Pint_bundle_plus(rep,exprep) 
	Pint_bundle_plus rep,exprep;
{
	int status = 0;

	if (i_compare_Pgcolr(rep.colr,exprep.colr) &&
	   i_compare_Pgcolr(rep.back_colr,exprep.back_colr) &&
	   i_compare_Prefl_props(rep.refl_props,exprep.refl_props) &&
	   i_compare_Prefl_props(rep.back_refl_props,exprep.back_refl_props) &&
	   rep.style == exprep.style && 
	   rep.style_ind == exprep.style_ind &&
	   rep.refl_eqn == exprep.refl_eqn &&
	   rep.shad_meth == exprep.shad_meth &&
	   rep.back_style == exprep.back_style)
			status = 1;

	if (verbosity >=3 || (verbosity >= 1 && status == 0)) {
		tvprintf(1,"i_compare_Pint_bundle_plus: style,style index,refl_eqn,shading,back_style,back_style_index,back_refl_eqn,back_shading,approx_type,approx_values = (%d,%d,%d,%d,%d,%d,%d,%d,%d,[%.4f,%.4f]); expected (%d,%d,%d,%d,%d,%d,%d,%d,[%.4f,%.4f])\n",
		rep.style,rep.style_ind,rep.refl_eqn,rep.shad_meth,
		rep.back_style,rep.back_style_ind,
		rep.back_refl_eqn,rep.back_refl_eqn,
		rep.approx_type,rep.approx_val[0],rep.approx_val[1],
		exprep.style,exprep.style_ind,
		exprep.refl_eqn,exprep.shad_meth,
		exprep.back_style,exprep.back_style_ind,
		exprep.back_refl_eqn,exprep.back_refl_eqn,
		exprep.approx_type,exprep.approx_val[0],
		exprep.approx_val[1]);
	}
	return(status);
}

/*
 * i_compare_Ppat_rep() 
 */
int
i_compare_Ppat_rep(rep,exprep) 
	Ppat_rep rep,exprep;
{
	int status = 0;
	int i,n;

	n = rep.dims.size_x * rep.dims.size_y;
	if (rep.dims.size_x == exprep.dims.size_x && 
	    rep.dims.size_y == exprep.dims.size_y && 
	    memcmp((char*)rep.colr_array,(char*)exprep.colr_array,
		n * sizeof(int)) == 0)
		status = 1;
	if (verbosity >=3 || (verbosity >= 1 && status == 0)) {
		tvprintf(1,"i_compare_Ppat_rep: x_dim,y_dim = (%d,%d); expected (%d,%d)\n",
			rep.dims.size_x,rep.dims.size_y,
			exprep.dims.size_x,exprep.dims.size_y);
		if (rep.dims.size_x == exprep.dims.size_x &&
		    rep.dims.size_y == exprep.dims.size_y &&
		    n > 0) {
			tvprintf(1,"i_compare_Ppat_rep: colour index array [(inquired,expected)...] = [");
			for (i=0;i<n; i++)
				printf("(%d,%d)",rep.colr_array[i],
			                	exprep.colr_array[i]);
			printf("]\n");
		}
	}
	return(status);
}

/*
 * i_compare_Ppat_rep_plus() 
 */
int
i_compare_Ppat_rep_plus(rep,exprep) 
	Ppat_rep_plus rep,exprep;
{
	int status = 0;
	int i,n;

	n = rep.dims.size_x * rep.dims.size_y;
	if (rep.dims.size_x == exprep.dims.size_x && 
	    rep.dims.size_y == exprep.dims.size_y && 
	    rep.type == exprep.type)
 	  if (rep.type == PINDIRECT) {
		for (i=0; i<n; i++) {
			if (rep.colr_array[i].ind != 
			    exprep.colr_array[i].ind)
				break;
		}
		if (i==n) /* all elements are equal */
			status = 1;
	  } else {
		for (i=0; i<n; i++) {
			if (i_compare_Pcolr_rep(rep.colr_array[i].direct,
	                           exprep.colr_array[i].direct) == 0)
				break;
		}
		if (i==n) /* all elements are equal */
			status = 1;
          }

	if (verbosity >=3 || (verbosity >= 1 && status == 0)) {
		tvprintf(1,"i_compare_Ppat_rep_plus: x_dim,y_dim,colour type = (%d,%d,%d); expected (%d,%d,%d)\n",
			rep.dims.size_x,rep.dims.size_y,rep.type,
			exprep.dims.size_x,exprep.dims.size_y,exprep.type);
		if (rep.dims.size_x == exprep.dims.size_x &&
		    rep.dims.size_y == exprep.dims.size_y  &&
		    rep.type == exprep.type &&
		    rep.type == PINDIRECT &&
		    n > 0) {
			tvprintf(1,"i_compare_Ppat_rep: colour index array [(inquired,expected)...] = [");
			for (i=0;i<n; i++)
				printf("(%d,%d)",rep.colr_array[i],
			                	exprep.colr_array[i]);
			printf("]\n");
		}
	}
	return(status);
}

/*
 * i_compare_Pdcue_bundle() 
 */
int
i_compare_Pdcue_bundle(rep,exprep) 
	Pdcue_bundle rep,exprep;
{
	int status = 0;

	if (i_compare_Pgcolr(rep.colr,exprep.colr) &&
	    rep.mode == exprep.mode && 
	    feq(rep.ref_planes[0],exprep.ref_planes[0]) &&
	    feq(rep.ref_planes[1],exprep.ref_planes[1]) &&
	    feq(rep.scaling[0],exprep.scaling[0]) &&
	    feq(rep.scaling[1],exprep.scaling[1]))
		status = 1;

	if (verbosity >=3 || (verbosity >= 1 && status == 0)) {
		tvprintf(1,"i_compare_Pdcue_bundle: mode,refplanes,scaling = (%d,[%.4f,%.4f],[%.4f,%.4f]); expected (%d,[%.4f,%.4f],[%.4f,%.4f])\n",
			rep.mode,rep.ref_planes[0],rep.ref_planes[1],
			rep.scaling[0],rep.scaling[1],
			exprep.mode,exprep.ref_planes[0],exprep.ref_planes[1],
			exprep.scaling[0],exprep.scaling[1]);
	}
	return(status);
}

/*
 * i_compare_Plight_src_bundle() 
 */
int
i_compare_Plight_src_bundle(rep,exprep) 
	Plight_src_bundle rep,exprep;
{
	int status = 0;

	if (rep.type == exprep.type)
	  switch (rep.type) {
	  case PLIGHT_AMBIENT:
		if (i_compare_Pgcolr(rep.rec.ambient.colr,
			exprep.rec.ambient.colr)) 
			status = 1;
		break;
	  case PLIGHT_DIRECTIONAL:
		if (i_compare_Pgcolr(rep.rec.directional.colr,
			exprep.rec.directional.colr) &&
		    i_compare_Pvec3(rep.rec.directional.dir,
		        exprep.rec.directional.dir))
			status = 1;
		break;
	  case PLIGHT_POSITIONAL:
		if (i_compare_Pgcolr(rep.rec.positional.colr,
			exprep.rec.positional.colr) &&
		    i_compare_Ppoint3(rep.rec.positional.pos,
		        exprep.rec.positional.pos) &&
		    feq(rep.rec.positional.coef[0],
		        exprep.rec.positional.coef[0]) &&
		    feq(rep.rec.positional.coef[1],
		        exprep.rec.positional.coef[1]))
			status = 1;
		break;
	  case PLIGHT_SPOT:
		if (i_compare_Pgcolr(rep.rec.spot.colr,
			exprep.rec.spot.colr) &&
		    i_compare_Ppoint3(rep.rec.spot.pos,
		        exprep.rec.spot.pos) &&
		    i_compare_Pvec3(rep.rec.spot.dir,
		        exprep.rec.spot.dir) &&
		    feq(rep.rec.spot.exp,exprep.rec.spot.exp) &&
		    feq(rep.rec.spot.angle,exprep.rec.spot.angle) &&
		    feq(rep.rec.spot.coef[0],
		        exprep.rec.spot.coef[0]) &&
		    feq(rep.rec.spot.coef[1],
		        exprep.rec.spot.coef[1]))
		break;
	  default:
		tvprintf(1,"i_compare_Plight_src_bundle: unknown type %d\n",
			rep.type);
	  }
	if (verbosity >=3 || (verbosity >= 1 && status == 0)) {
		/* TODO */
	}
	return(status);
}

/*
 * i_compare_Pcolr_rep() 
 */
int
i_compare_Pcolr_rep(rep,exprep) 
	Pcolr_rep rep,exprep;
{
	int status = 0;

	if (feq(rep.rgb.red,exprep.rgb.red) && 
		feq(rep.rgb.green,exprep.rgb.green) && 
		feq(rep.rgb.blue,exprep.rgb.blue))
		status = 1;

	if (verbosity >=3 || (verbosity >= 1 && status == 0)) {
		tvprintf(1,"i_compare_Pcolr_rep: x,y,z = (%.4f,%.4f,%.4f); expected (%.4f,%.4f,%.4f)\n",
			rep.rgb.red, rep.rgb.green, rep.rgb.blue, 
			exprep.rgb.red, exprep.rgb.green, exprep.rgb.blue);
	}
	return(status);
}

/*
 * i_compare_Pcoval(colr, expcolr)
 * compare two Pcoval structures; return 1 if they match, 0 otherwise.
 * comparison is according to specified colour model: by index
 * if PINDIRECT, by Pcolr_rep otherwise.
 */
int
i_compare_Pcoval(colr,expcolr,model)
    Pcoval colr, expcolr;
    Pint model;
{
    int status = 0;

    if (model == PINDIRECT ? 
	(colr.ind == expcolr.ind) :
	i_compare_Pcolr_rep(colr.direct, expcolr.direct))
	status = 1;

    if (verbosity >= 3 || (verbosity >= 1 && status == 0)) {
	if (model==PINDIRECT)
	    tvprintf(1, "i_compare_Pcoval:  PINDIRECT index = %d; expected %d\n",
		     colr.ind ,expcolr.ind );
	else  /* mismatched Pcolr_Bundle printed by i_compare_Pcolr_Bundle */
	    tvprintf(1, "i_compare_Pcoval: color model %d\n",
		      model); 
	}
    return (status);
}    

/*
 * i_compare_Pelem_ref_list(lst,explst)
 * compare 2 Pelem_ref_list
 * return 1 if success, 0 otherwise
 * Note: two list are equal even if the order of the elements differs
 */
int
i_compare_Pelem_ref_list(lst,explst)
	Pelem_ref_list lst,explst;	
{
	int i,j,k,status,found,match;

	status = 1;
	if (lst.num_elem_refs != explst.num_elem_refs) 
		status = 0;
	for (i=0;i<lst.num_elem_refs && status == 1;++i) {
		for (found=0,j=0;j<lst.num_elem_refs;++j) {
			if (lst.elem_refs[i].struct_id == explst.elem_refs[j].struct_id &&  
			    lst.elem_refs[i].elem_pos == explst.elem_refs[j].elem_pos ) {
				found = 1;
				break;
			}
		}
		if (!found)
			status = 0;
	}
	if ((verbosity >= 1 && status == 0) || verbosity >= 3) {	
	tvprintf(1,"i_compare_Pelem_ref_list: number=%d,list=",
			lst.num_elem_refs); 
		for (i=0;i<lst.num_elem_refs;++i) {
			printf("(%d,%d)",lst.elem_refs[i].struct_id
				        ,lst.elem_refs[i].elem_pos);
		}
		printf("; expected: number=%d,list=",
			explst.num_elem_refs); 
		for (i=0;i<explst.num_elem_refs;++i) {
			printf("(%d,%d)",explst.elem_refs[i].struct_id
				        ,explst.elem_refs[i].elem_pos);
		}
		printf("\n");
	}
	return(status);
}

/*
 * i_compare_Pelem_ref_list_list(lstlst,explstlst)
 * compare 2 Pelem_ref_list_list 
 * return 1 if success, 0 otherwise
 * Note: two list are equal even if the order of the elements differs
 */
int
i_compare_Pelem_ref_list_list(lstlst,explstlst)
	Pelem_ref_list_list lstlst,explstlst;	
{
	int i,j,k,status,found,match;
	Pelem_ref_list lst1,lst2;

	status = 1;
	if (lstlst.num_elem_ref_lists != explstlst.num_elem_ref_lists) 
		status = 0;
	for (i=0;i<lstlst.num_elem_ref_lists && status == 1;++i) {
		lst1 = lstlst.elem_ref_lists[i];
		for (found=0,j=0;j<lstlst.num_elem_ref_lists;++j) {
		  lst2 = explstlst.elem_ref_lists[j];
		    if (lst1.num_elem_refs != lst2.num_elem_refs) 
			continue;
		    for (match=1,k=0;k<lst1.num_elem_refs && match==1 ;++k) {
			if (lst1.elem_refs[k].struct_id != lst2.elem_refs[k].struct_id ||
		    		lst1.elem_refs[k].elem_pos != lst2.elem_refs[k].elem_pos) 
					match = 0;
		    }
		    if (match) {
			found = 1;
			break;
		    }
		}
		if (!found)
			status = 0;
	}
	if ((verbosity >= 1 && status == 0) || verbosity >= 3) {	
		tvprintf(1,"i_compare_Pelem_ref_list_list: number=%d,list=",
			lstlst.num_elem_ref_lists); 
		for (i=0;i<lstlst.num_elem_ref_lists;++i) {
			lst1 = lstlst.elem_ref_lists[i];
			for (j=0;j<lst1.num_elem_refs;++j) {
				printf("(%d,%d)",lst1.elem_refs[j].struct_id
				                ,lst1.elem_refs[j].elem_pos);
			}
			printf("-");
		}
		printf("; expected: number=%d,list=",
			explstlst.num_elem_ref_lists); 
		for (i=0;i<explstlst.num_elem_ref_lists;++i) {
			lst2 = explstlst.elem_ref_lists[i];
			for (j=0;j<lst2.num_elem_refs; ++j) {
				printf("(%d,%d)",lst2.elem_refs[j].struct_id
				                ,lst2.elem_refs[j].elem_pos);
			}
			printf("-");
		}
		printf("\n");
	}
	return(status);
}

/*
 * i_compare_Plimit(lim,explim)
 * compare two Plimit type
 * return 1 if equal, 0 otherwise
 * Note: we cannot just compare the structure because the floating points 
 * precision may be lost across the wire
 */ 
int
i_compare_Plimit(lim,explim)
	Plimit lim,explim;
{
	int status = 0;

	if (feq(lim.x_min,explim.x_min) && feq(lim.x_max,explim.x_max) &&
	    feq(lim.y_min,explim.y_min) && feq(lim.y_max,explim.y_max) )
		status = 1;
	if ((verbosity >= 1 && status == 0) || verbosity >= 3) {	
                tvprintf(1,"i_compare_Plimit:");
		printPlimit(lim);
                printf("; expected:");
		printPlimit(explim);
		printf("\n");
	}
	return(status);
}
/*
 * i_compare_Plimit3(lim,explim)
 * compare two Plimit3 type
 * return 1 if equal, 0 otherwise
 * Note: we cannot just compare the structure because the floating points 
 * precision may be lost across the wire
 */ 
int
i_compare_Plimit3(lim,explim)
	Plimit3 lim,explim;
{
	int status = 0;

	if (feq(lim.x_min,explim.x_min) && feq(lim.x_max,explim.x_max) &&
	    feq(lim.y_min,explim.y_min) && feq(lim.y_max,explim.y_max) &&
	    feq(lim.z_min,explim.z_min) && feq(lim.z_max,explim.z_max) )
		status = 1;
	if ((verbosity >= 1 && status == 0) || verbosity >= 3) {	
                tvprintf(1,"i_compare_Plimit3:");
		printPlimit3(lim);
                printf("; expected:");
		printPlimit3(explim);
		printf("\n");
	}
	return(status);
}


/*
 * i_compare_Pint_list(lst,explst)
 * compare two Pint_list
 * return 1 if success, 0 otherwise
 * Note: two list are equal even if the order of the elements differs
 */
int
i_compare_Pint_list(lst,explst)
        Pint_list lst,explst;   	/* integer list */
{
        int i,j,item,found,status;

        status = 1;
        if (lst.num_ints != explst.num_ints)
                status = 0;
        for (i=0;i<lst.num_ints && status == 1;++i) {
                for (found=0,j=0;j<lst.num_ints;++j) {
                        if (lst.ints[i] == explst.ints[j]) {
                                found = 1;
                                break;
                        }
                }
                if (!found)
                        status = 0;
        }
        if ((verbosity >= 1 && status == 0) || verbosity >=3) {
                tvprintf(1,"i_compare_Pint_list: number=%d, ints=",
                        lst.num_ints);
                for (i=0;i<lst.num_ints;++i)
                        printf("%d,",lst.ints[i]);
                printf("; expected: number=%d, ints=", explst.num_ints);
                for (i=0;i<explst.num_ints;++i)
                        printf("%d,",explst.ints[i]);
                printf("\n");
        }
	return(status);
}

/*
 * i_compare_ordered_Pint_list(lst,explst)
 * compare two Pint_list
 * return 1 if success, 0 otherwise
 * Note: two list are NOT equal even if the order of the elements differs
 */
int
i_compare_ordered_Pint_list(lst,explst)
        Pint_list lst,explst;   	/* integer list */
{
        int i,status;

        status = 0;
        if (lst.num_ints == explst.num_ints) {
        	for (i=0;i<lst.num_ints ;++i) {
                        if (lst.ints[i] != explst.ints[i]) 
                                break;
                }
                if (i==lst.num_ints)
                        status = 1;
        }
        if ((verbosity >= 1 && status == 0) || verbosity >=3) {
                tvprintf(1,"i_compare_ordered_Pint_list: number=%d, ints=",
                        lst.num_ints);
                for (i=0;i<lst.num_ints;++i)
                        printf("%d,",lst.ints[i]);
                printf("; expected: number=%d, ints=", explst.num_ints);
                for (i=0;i<explst.num_ints;++i)
                        printf("%d,",explst.ints[i]);
                printf("\n");
        }
	return(status);
}

/*
 * i_compare_Pattrs_array(num,lst,explst)
 * compare two array of Pattrs
 * return 1 if success, 0 otherwise
 * Note: two arrays are equal even if the order of the elements differs
 */
int
i_compare_Pattrs_array(num,lst,explst)
	Pint num;
        Pattrs *lst,*explst;   	
{
        int i,j,item,found,status;

        status = 1;
        for (i=0;i<num && status == 1;++i) {
                for (found=0,j=0;j<num;++j) {
                        if (lst[i] == explst[j]) {
                                found = 1;
                                break;
                        }
                }
                if (!found)
                        status = 0;
        }
        if ((verbosity >= 1 && status == 0) || verbosity >= 3) {
                tvprintf(1,"i_compare_Pattrs_array: attrs:");
                for (i=0;i<num;++i)
                        printf("%d,",lst[i]);
                printf("; expected: ");
                for (i=0;i<num;++i)
                        printf("%d,",explst[i]);
                printf("\n");
        }
	return(status);
}

/*
 * i_compare_Pgse_id_dep_list(lst,explst)
 * compare two Pgse_id_dep_list
 * return 1 if success, 0 otherwise
 * Note: two list are equal even if the order of the elements differs
 */
int
i_compare_Pgse_id_dep_list(lst,explst)
        Pgse_id_dep_list lst,explst; /* gse list */
{
        int i,j,item,found,status;

        status = 1;
        if (lst.num_id_facs != explst.num_id_facs)
                status = 0;
        for (i=0;i<lst.num_id_facs && status == 1;++i) {
                for (found=0,j=0;j<lst.num_id_facs;++j) {
                    if (lst.id_facs[i].id == explst.id_facs[j].id &&
          		lst.id_facs[i].ind == explst.id_facs[j].ind) {
                                found = 1;
                                break;
                        }
                }
                if (!found)
                        status = 0;
        }
        if ((verbosity >= 1 && status == 0) || verbosity >=3 ) {
                tvprintf(1,"i_compare_Pgse_id_dep_list: number=%d, list=",
                        lst.num_id_facs);
                for (i=0;i<lst.num_id_facs;++i)
                        printf("(%d,%d),",lst.id_facs[i].id,lst.id_facs[i].ind);
                printf("; expected: number=%d, list=", explst.num_id_facs);
                for (i=0;i<explst.num_id_facs;++i)
                        printf("(%d,%d),",explst.id_facs[i].id,explst.id_facs[i].ind);
                printf("\n");
        }
	return(status);
}


/*
 * i_compare_Pmatrix3(mtx,expmtx) compare two Pmatrix3
 * OUT status = 0 if match, 1 otherwise
 */
int
i_compare_Pmatrix3(mtx,expmtx)
	Pmatrix3 mtx;			/* matrix */
	Pmatrix3 expmtx;		/* matrix */
{
	int i,j,status;

#define PRINTMTX3(matrix) \
		printf("(");					\
		for (i = 0; i < 4; i++) {			\
			printf("[");				\
			for (j = 0; j < 4; j++) 		\
				printf("%.4f ",matrix[i][j]);	\
			printf("]");				\
		}						\
		printf(")");

	status = 1;
	for (i = 0; i < 4 && status == 1; i++)
		for (j = 0; j < 4; j++) {
			if (fne(mtx[i][j],expmtx[i][j])) {
				status = 0;
				break;
			}
		}
	if ((verbosity >= 1 && status == 0) || verbosity >= 3) {
		tvprintf(1,"i_compare_Pmatrix3: ");
		PRINTMTX3(mtx);
		printf("; expected:");
		PRINTMTX3(expmtx);
		puts("");
	}
	return(status);
}

/*
 * i_compare_Pmatrix(mtx,expmtx,status) compare two Pmatrix
 * returns 1 if success , 0 otherwise
 */
int
i_compare_Pmatrix(mtx,expmtx)
	Pmatrix mtx;		/* matrix */
	Pmatrix expmtx;		/* matrix */
{
	int i,j,status;

#define PRINTMTX(matrix) \
		printf("(");					\
		for (i = 0; i < 3; i++) {			\
			printf("[");				\
			for (j = 0; j < 3; j++) 		\
				printf("%.4f ",matrix[i][j]);	\
			printf("]");				\
		}						\
		printf(")");					

	status = 1;
	for (i = 0; i < 3 && status == 1; i++)
		for (j = 0; j < 3; j++) {
			if (fne(mtx[i][j],expmtx[i][j])) {
				status = 0;
				break;
			}
		}
	if ((verbosity >= 1 && status == 0) || verbosity >= 3) {
		tvprintf(1,"i_compare_Pmatrix: ");
		PRINTMTX(mtx);
		printf("; expected:");
		PRINTMTX(expmtx);
		puts("");
	}
	return(status);
}

/*
 * i_compare_Ppoint(pt,exppt) compare two Ppoint
 * returns 1 if success , 0 otherwise
 */
int
i_compare_Ppoint(pt,exppt)
	Ppoint pt,exppt;		/* points */
{
	int status = 1;

	if (fne(pt.x,exppt.x) && fne(pt.y,exppt.y)) {
		status = 0;
	}
	if ((verbosity >= 1 && status == 0) || verbosity >= 3) {
		tvprintf(1,"i_compare_Ppoint: (%.4f,%.4f); expected:(%.4f,%.4f)\n",
			pt.x,pt.y,exppt.x,exppt.y);
	}
	return(status);
}

/*
 * i_compare_Ppoint3(pt,exppt) compares two Ppoint3
 * returns 1 if success , 0 otherwise
 */
int
i_compare_Ppoint3(pt,exppt)
	Ppoint3 pt,exppt;		/* points */
{
	int status = 1;		

	if (fne(pt.x,exppt.x) && fne(pt.y,exppt.y) 
		&& fne(pt.z,exppt.z)) {
		status = 0;
	}
	if ((verbosity >= 1 && status == 0) || verbosity >= 3) {
		tvprintf(1,"i_compare_Ppoint3: (%.4f,%.4f,%.4f); expected (%.4f,%.4f,%.4f)\n",
		pt.x,pt.y,pt.z,exppt.x,exppt.y,exppt.z);
	}
	return(status);
}

/*
 * i_compare_Pvec(pt,exppt) compare two Pvec
 * returns 1 if success , 0 otherwise
 */
int
i_compare_Pvec(vec,expvec)
	Pvec vec,expvec;		/* points */
{
	int status = 1;

	if (fne(vec.delta_x,expvec.delta_x) && fne(vec.delta_y,expvec.delta_y)) {
		status = 0;
	}
	if ((verbosity >= 1 && status == 0) || verbosity >= 3) {
		tvprintf(1,"i_compare_Pvec: (%.4f,%.4f);expected:(%.4f,%.4f)\n",
			vec.delta_x,vec.delta_y,expvec.delta_x,expvec.delta_y);
	}
	return(status);
}

/*
 * i_compare_Pvec3(vec,expvec) compares two Pvec3
 * returns 1 if success , 0 otherwise
 */
int
i_compare_Pvec3(vec,expvec)
	Pvec3 vec,expvec;		/* points */
{
	int status = 1;		

	if (fne(vec.delta_x,expvec.delta_x) && fne(vec.delta_y,expvec.delta_y) 
		&& fne(vec.delta_z,expvec.delta_z)) {
		status = 0;
	}
	if ((verbosity >= 1 && status == 0) || verbosity >= 3) {
		tvprintf(1,"i_compare_Pvec3: (%.4f,%.4f,%.4f); expected:(%.4f,%.4f,%.4f)\n",
			vec.delta_x,vec.delta_y,vec.delta_z,
			expvec.delta_x,expvec.delta_y,expvec.delta_z);
	}
	return(status);
}


/*
 * i_compare_Ptext_font_prec_array(num,fps,expfps)
 * compare two array of Ptext_font_prec
 * return 1 if success, 0 otherwise
 * Note: two arrays are equal even if the order of the elements differs
 */
int
i_compare_Ptext_font_prec_array(num,fps,expfps)
        int num;        	/* number of items in array */
        Ptext_font_prec *fps,*expfps;   	/* array of fp pairs */
{
        int i,j,item,found,status;

        status = 1;
        for (i=0;i<num && status == 1;++i) {
                for (found=0,j=0;j<num;++j) {
                        if (fps[i].font == expfps[j].font &&
                            fps[i].prec == expfps[j].prec) {
                                found = 1;
                                break;
                        }
                }
                if (!found)
                        status = 0;
        }
        if ((verbosity >= 1 && status == 0) || verbosity >= 3) {
                tvprintf(1,"i_compare_Ptext_font_prec_array: font and prec pairs:");
                for (i=0;i<num;++i)
                        printf("(%d,%d),",fps[i].font,fps[i].prec);
                printf("; expected: ");
                for (i=0;i<num;++i)
                        printf("(%d,%d),",expfps[i].font,expfps[i].prec);
                printf("\n");
        }
	return(status);
}

/*
 * i_compare_Pint_style_array(num,styles,expstyles)
 * compare two array of Pint_style
 * return 1 if success, 0 otherwise
 * Note: two list are equal even if the order of the elements differs
 */
int 
i_compare_Pint_style_array(num,styles,expstyles)
        int num;            		/* number of items in array */
        Pint_style *styles,*expstyles;   /* array of interior style list */
{
        int i,j,item,found,status;

        status = 1;
        for (i=0;i<num && status == 1;++i) {
                for (found=0,j=0;j<num;++j) {
                        if (styles[i] == expstyles[j]) {
                                found = 1;
                                break;
                        }
                }
                if (!found)
                        status = 0;
        }
        if ((verbosity >= 1 && status == 0) || verbosity >= 3) {
                tvprintf(1,"i_compare_Pint_style_array: interior style list:");
                for (i=0;i<num;++i)
                        printf("%d,",styles[i]);
                printf("; expected:");
                for (i=0;i<num;++i)
                        printf("%d,",expstyles[i]);
                printf("\n");
        }
	return(status);
}

/*
 * i_compare_Pint_list_to_ints(lst,n,va_alist)
 * compare a Pint_list to a variable list of integers
 * return 1 if success, 0 otherwise
 * Note: two list are equal even if the order of the elements differs
 */
int
i_compare_Pint_list_to_ints(lst,n,va_alist)
	Pint_list lst;		/* integer list */
	Pint n;			/* number */
	va_dcl
{
	int i,j,item,found;
	va_list ap;
	int status;

	status = 1;
	va_start(ap);
	if (lst.num_ints != n)
		status = 0;
	for (i=0;i<n && status == 1;++i) {
		item = va_arg(ap,Pint);
		for (found=0,j=0;j<n;++j) {
			if (item == lst.ints[j]) {
				found = 1;
				break;
			}
		}
		if (!found) 
			status = 0;
	}
	va_end(ap);
	if ( (verbosity >= 1  && status == 0) || verbosity >= 3) {	
		tvprintf(1,"i_compare_Pint_list_to_ints: number=%d, ints=",
			lst.num_ints); 
		for (i=0;i<lst.num_ints;++i)
			printf("%d,",lst.ints[i]);
		va_start(ap);
		printf("; expected: number = %d, ints = ",n);
		for (i=0;i<n;++i)
			printf("%d,",va_arg(ap,Pint));
		va_end(ap);
		printf("\n");
	}
	return(status);
}
	
/*
 * i_compare_Par_file_list_to_ids_names(lst,n,va_alist)
 * compare a Parchivefilelst to a variable list of archive file 
 * numbers and names
 * return 1 if success, 0 otherwise
 * Note: two list are equal even if the order of the elements differs
 */
int
i_compare_Par_file_list_to_ids_names(lst,n,va_alist)
	Par_file_list lst;	/* archive file list */
	Pint n;			/* number */
	va_dcl
{
	int i,j,id,found;
	char *name;
	int status;	
	va_list ap;

	status = 1;
	va_start(ap);
	if (lst.num_ar_files != n) 
		status = 0;
	for (i=0;i<n && status == 1;++i) {
		id = va_arg(ap,Pint);
		name = va_arg(ap,char*);
		for (found=0,j=0;j<n;++j) { 
			if (id == lst.ar_files[j].id && 
				strcmp(name,lst.ar_files[j].name)==0) {
	 			found = 1; 
				break;
			}
		}
		if (!found) 
			status = 0;
	}
	va_end(ap);
	if ((verbosity >= 1 && status == 0) || verbosity >= 3) {	
		tvprintf(1,"i_compare_Par_file_list_to_ids_names: number = %d, files = ",
			lst.num_ar_files); 
		for (i=0;i<lst.num_ar_files;++i)
			printf("(%d,%s),",lst.ar_files[i].id,lst.ar_files[i].name);
		va_start(ap);
		printf("; expected: number = %d, files = ",n);
		for (i=0;i<n;++i) {
			id = va_arg(ap,Pint);
			name = va_arg(ap,char*);
			printf("(%d,%s),",id,name);
		}
		va_end(ap);
		printf("\n");
	}
	return(status);
}


/*
 * i_compare_Pfacet_data_arr3(fflag, cmodel, data, edata, num)
 * compare the facet data arrays specified by data and edata,
 * given the facet data flag flag, color model cmodel, and number of 
 * facets num.  Return 1 if they match, 0 otherwise.
 * Based on chkfdataarr.
 */
int
i_compare_Pfacet_data_arr3(fflag, cmodel, data, edata, num)
    Pfacet_data_arr3    data, edata;
    int                 fflag, num, cmodel;
{
    int                 i;
    int			status = 1;

    /*
     * Printed diagnostics are minimal, since underlying routines
     * will give more detail.
     */

    switch (fflag) {
    case PFACET_NONE:
	break;
    case PFACET_COLOUR:
	    for (i = 0; i < num; i++) {
		if (!i_compare_Pcoval(data.colrs[i], edata.colrs[i], cmodel))
		    status = 0;
		if ((verbosity >= 1 && status == 0) || verbosity >= 3)
		    tvprintf(1, "i_compare_Pfacet_data_arr3: was facet %d color\n",i);
		if (status == 0) return (0);
	    }
	break;
    case PFACET_NORMAL:
	for (i = 0; i < num; i++) {
	    if (!i_compare_Pvec3(data.norms[i],edata.norms[i]))
		status = 0;
	    if ((verbosity >= 1 && status == 0) || verbosity >= 3)
		tvprintf(1, "i_compare_Pfacet_data_arr3: was facet normal %d\n",i);
	    if (status == 0) return (0);
	}
	break;
    case PFACET_COLOUR_NORMAL:
	for (i = 0; i < num; i++) {
	    if (!i_compare_Pvec3(data.conorms[i].norm,edata.conorms[i].norm))
		status = 0;
	    if ((verbosity >= 1 && status == 0) || verbosity >= 3)
		tvprintf(1, "i_compare_Pfacet_data_arr3: was facet normal %d\n",i);
	    if (status == 0) return (0);

	    if (!i_compare_Pcoval(data.conorms[i].colr, edata.conorms[i].colr, cmodel))
		status = 0;
	    if ((verbosity >= 1 && status == 0) || verbosity >= 3)
		tvprintf(1, "i_compare_Pfacet_data_arr3: was facet %d color\n", i);
	    if (status == 0) return (0);
	}
	break;
    }
    return (1);
} /* i_compare_Pfacet_data_arr3 */


/*
 * i_compare_Pfacet_vdata_arr3(vflag, cmodel, data, edata, num)
 * compare the facet vertex data arrays specified by data and edata,
 * given the vertex data flag vflag, colour model cmodel, and number
 * of vertices num.
 */
int
i_compare_Pfacet_vdata_arr3(vflag, cmodel, data, edata, num)
    Pfacet_vdata_arr3   data, edata;
    int                 vflag, num, cmodel;
{
    int                 i;
    int			status = 1;

    /*
     * Printed diagnostics are minimal, since underlying routines
     * will give more detail.
     */

    switch (vflag) {
    case PVERT_COORD:
	for (i = 0; i < num; i++) {
	    if (!i_compare_Ppoint3(data.points[i], edata.points[i]))
		status = 0;
	    if ((verbosity >= 1 && status == 0) || verbosity >= 3)
		tvprintf(1, "i_compare_Pfacet_vdata_arr3: vertex %d\n", i);
	    if (status == 0) return (0);
	}
	break;
    case PVERT_COORD_COLOUR:
	for (i = 0; i < num; i++) {
	    if (!i_compare_Ppoint3(data.ptcolrs[i].point, edata.ptcolrs[i].point))
		status = 0;
	    if ((verbosity >= 1 && status == 0) || verbosity >= 3)
		tvprintf(1, "i_compare_Pfacet_vdata_arr3: vertex %d\n", i);
	    if (status == 0) return (0);

	    if (!i_compare_Pcoval(data.ptcolrs[i].colr, data.ptcolrs[i].colr, cmodel))
		status = 0;
	    if ((verbosity >= 1 && status == 0) || verbosity >= 3)
		tvprintf(1, "i_compare_Pfacet_vdata_arr3: vertex %d color\n",i);
	    if (status == 0) return (0);
	}
	break;
    case PVERT_COORD_NORMAL:
	for (i = 0; i < num; i++) {
	    if (!i_compare_Ppoint3(data.ptnorms[i].point, edata.ptnorms[i].point))
		status = 0;
	    if ((verbosity >= 1 && status == 0) || verbosity >= 3)
		tvprintf(1, "i_compare_Pfacet_vdata_arr3: vertex %d\n", i);
	    if (status == 0) return (0);

	    if (!i_compare_Pvec3(data.ptnorms[i].norm, edata.ptnorms[i].norm))
		status = 0;
	    if ((verbosity >= 1 && status == 0) || verbosity >= 3)
		tvprintf(1, "i_compare_Pfacet_vdata_arr3: vertex %d normal\n", i);
	    if (status == 0) return (0);
	}
	break;
    case PVERT_COORD_COLOUR_NORMAL:
	for (i = 0; i < num; i++) {
	    if (!i_compare_Ppoint3(data.ptconorms[i].point, edata.ptconorms[i].point))
		status = 0;
	    if ((verbosity >= 1 && status == 0) || verbosity >= 3)
		tvprintf(1, "i_compare_Pfacet_vdata_arr3: vertex %d\n", i);
	    if (status == 0) return (0);

	    if (!i_compare_Pvec3(data.ptconorms[i].norm, edata.ptconorms[i].norm))
		status = 0;
	    if ((verbosity >= 1 && status == 0) || verbosity >= 3)
		tvprintf(1, "i_compare_Pfacet_vdata_arr3: vertex %d normal\n", i);
	    if (status == 0) return (0);

	    if (!i_compare_Pcoval(data.ptconorms[i].colr, data.ptconorms[i].colr, cmodel))
		status = 0;
	    if ((verbosity >= 1 && status == 0) || verbosity >= 3)
		tvprintf(1, "i_compare_Pfacet_vdata_arr3: vertex %d color\n",i);
	    if (status == 0) return (0);
	}
	break;
    }
    return (1);
} /* chkvdataarr */


/*
 * i_check_current_element(expecttype, expectdata, element_name)
 *
 *  This fcn inquires the current element type and content, and compares the
 * inquired values to those expected.  This function returns 1 if
 * the inquired and expected values match, 0 otherwise.  
 * If the values do not match, and the string element_name is supplied,
 * an error message is printed (and the error count incremented) 
 * with tfprintf().  if element_name is NULL, tfprintf() is not called.
 */
int
i_check_current_element(expecttype, expectdata, element_name)
    Pelem_type         expecttype;
    Pelem_data        *expectdata;
    char           *element_name;
{
    Pint            size, err, status;
    char            *buffer;
    Pelem_type         inqtype;
    Pelem_data         *inqdata;
    Pstore	    store;

    err = 0;
    pinq_cur_elem_type_size(&err, &inqtype, &size);
    if (err) {
	if (element_name) 
	    tfprintf("failed: error %d in function pinq_cur_elem_type_size (element %s)\n", 
		    err, element_name);
	return (0);
    }
    if (inqtype != expecttype) {
	if (element_name)  tfprintf("failed: inq'd eltype %d != expected %d (%s)\n",
				    inqtype, expecttype, element_name);
	return (0);
    }

    pcreate_store(&err,&store);
    if (err) {
	    tfprintf("failed: error %d in function pcreate_store (element %s)\n", 
		    err, element_name);
	    return(0);
    }
    pinq_cur_elem_content(store, &err, &inqdata);
    if (err) {
	if (element_name) 
	    tfprintf("failed: error %d in function pinq_cur_elem_content (element %s)\n", 
		    err, element_name);
	return (0);
    }
    status = i_compare_element_content(expecttype, inqdata, expectdata,
				       element_name);
    pdel_store(store);
    return (status);
}

/*
 * i_check_element(struct_id, element, expecttype, expectdata, element_name)
 *
 *  This fcn inquires the specified element's type and content, compares the
 * inquired values to those expected.  This function returns 1 if
 * the inquired and expected values match, 0 otherwise.
 * If the values do not match, and the string element_name is supplied,
 * an error message is printed (and the error count incremented) 
 * with tfprintf().  if element_name is NULL, tfprintf() is not called.
 */
int
i_check_element(struct_id, element, expecttype, expectdata, element_name)
    Pint	    struct_id;
    Pint	    element;
    Pelem_type         expecttype;
    Pelem_data        *expectdata;
    char           *element_name;
{
    Pint            size, err, status;
    char            *buffer;
    Pelem_type         inqtype;
    Pelem_data         *inqdata;
    Pstore	    store;

    err = 0;
    pinq_elem_type_size(struct_id, element, &err, &inqtype, &size);
    if (err) {
	if (element_name) 
	    tfprintf("failed: error %d in function pinq_elem_type_size (element %s)\n", 
		    err, element_name);
	return (0);

    }
    if (inqtype != expecttype) {
	if (element_name) tfprintf("failed: inq'd eltype %d != expected %d (%s)\n",
				   inqtype, expecttype, element_name);
	return (0);
    }
    pcreate_store(&err,&store);
    if (err) {
	    tfprintf("failed: error %d in function pcreate_store (element %s)\n", 
		    err, element_name);
	    return(0);
    }
    pinq_elem_content(struct_id, element, store, &err, &inqdata);
    if (err) {
	if (element_name) 
	    tfprintf("failed: error %d in function pinq_cur_elem_content (element %s)\n", 
		    err, element_name);
	return (0);
    }
    status = i_compare_element_content(expecttype, inqdata, expectdata, element_name);
    pdel_store(store);
    return (status);

}


/* int
 * i_compare_element_content(type,data,expectdata, element_name)
 * check PHIGS element data against the expected values.
 * If the data match, return 1.  Otherwise, return 0.
 * If element_name is supplied, failure causes an error
 * message to be printed (and the error count incremented) with
 * tfprintf().  If element_name is NULL, tfprintf() is not called.
 *
 */
int
i_compare_element_content(type,data,expectdata, element_name)
	Pelem_type type;		/* element type */
	Pelem_data *data;		/* data content */
	Pelem_data *expectdata;	/* expected data content */
        char    *element_name;  /* string name of the element type, for error msg. */
{
    int i,j;
    int status = 1;			/* assume data match until shown otherwise */
    Ppoint *inqpt, *exppt;
    Ppoint3 *inqpt3, *exppt3;
    Phalf_space *inqhs, *exphs;		/* inquired & expected half-spaces */
    Phalf_space3 *inqhs3, *exphs3;

    switch (type) {
    case PELEM_ADD_NAMES_SET:
    case PELEM_REMOVE_NAMES_SET:
	if (!i_compare_Pint_list(data->names, expectdata->names)) {
	    if (element_name)
		tfprintf("failed: inquired names list for %s != expected\n",
			 element_name);
	    return (0);
	}
	break;
    /* lump all idata cases together */
    case PELEM_ANNO_STYLE:
    case PELEM_BACK_INT_REFL_EQN:
    case PELEM_BACK_INT_SHAD_METH:
    case PELEM_BACK_INT_STYLE_IND:
    case PELEM_DCUE_IND:
    case PELEM_EDGETYPE:
    case PELEM_EDGE_COLR_IND:
    case PELEM_EDGE_IND:
    case PELEM_EXEC_STRUCT:
    case PELEM_HLHSR_ID:
    case PELEM_INT_COLR_IND:
    case PELEM_INT_IND:
    case PELEM_INT_REFL_EQN:
    case PELEM_INT_SHAD_METH:
    case PELEM_INT_STYLE_IND:
    case PELEM_LABEL:
    case PELEM_LINETYPE:
    case PELEM_LINE_SHAD_METH:
    case PELEM_MARKER_COLR_IND:
    case PELEM_MARKER_TYPE:
    case PELEM_PICK_ID:
    case PELEM_LINE_COLR_IND:
    case PELEM_LINE_IND:
    case PELEM_MARKER_IND:
    case PELEM_TEXT_COLR_IND:
    case PELEM_TEXT_FONT:
    case PELEM_TEXT_IND:
    case PELEM_VIEW_IND:
        if (expectdata->int_data != data->int_data) {
	    if (element_name) 
		tfprintf("failed: inquired value for %s (%d) != expected (%d)\n",
			 element_name, data->int_data, expectdata->int_data);
            return (0);
        }
        break;
    case PELEM_ANNO_ALIGN:
    case PELEM_TEXT_ALIGN:
	if ((expectdata->text_align.hor != data->text_align.hor) ||
	    (expectdata->text_align.vert != data->text_align.vert)) {
	    if (element_name)
		tfprintf("failed: inquired alignment for %s (hor=%d,vert=%d) != expected (%d,%d)\n",
			 element_name, data->text_align.hor, data->text_align.vert,
			 expectdata->text_align.hor, expectdata->text_align.vert);
	    return (0);
	}
	break;
    /* here are all the fdata cases */
    case PELEM_ANNO_CHAR_HT:
    case PELEM_CHAR_EXPAN:
    case PELEM_CHAR_HT:
    case PELEM_CHAR_SPACE:
    case PELEM_EDGEWIDTH:
    case PELEM_LINEWIDTH:
    case PELEM_MARKER_SIZE:
        if (!feq(expectdata->float_data, data->float_data)) {
	    if (element_name)
		tfprintf("failed: inquired value for %s (%f) != expected (%f)\n",
			 element_name, data->float_data, expectdata->float_data);
            return (0);
        }
        break;
    case PELEM_ANNO_CHAR_UP_VEC:
    case PELEM_CHAR_UP_VEC:
	if (!feq(expectdata->char_up_vec.delta_x, data->char_up_vec.delta_x) ||
	    !feq(expectdata->char_up_vec.delta_y, data->char_up_vec.delta_y)) {
	    if (element_name)
		tfprintf("failed: inquired value for %s != expected\n",
			 element_name);
	    return (0);
	}
	break;
    case PELEM_ANNO_PATH:
    case PELEM_TEXT_PATH:
	if (expectdata->text_path != data->text_path) {
	    if (element_name)
		tfprintf("failed: inquired value for %s != expected\n",
			 element_name);
	    return (0);
	}
	break;
    case PELEM_ANNO_TEXT_REL:
	if (!i_compare_Ppoint(data->anno_text_rel.ref_point, 
			      expectdata->anno_text_rel.ref_point) ||
	    !i_compare_Ppoint(data->anno_text_rel.offset, 
			      expectdata->anno_text_rel.offset)) {
	    if (element_name)
		tfprintf("failed: inquired value for %s != expected\n",
			 element_name);
	    return (0);
	} else if (strcmp(expectdata->anno_text_rel.char_string, 
			  data->anno_text_rel.char_string)) {
	    if (element_name)
		tfprintf("failed: inquired string for %s (%s) != expected (%s)\n",
			 element_name, data->anno_text_rel.char_string,
			 expectdata->anno_text_rel.char_string);
	    return (0);
	}
	break;
    case PELEM_ANNO_TEXT_REL3:
	if (!i_compare_Ppoint3(data->anno_text_rel3.ref_point, 
			      expectdata->anno_text_rel3.ref_point) ||
	    !i_compare_Ppoint3(data->anno_text_rel3.offset, 
			      expectdata->anno_text_rel3.offset)) {
	    if (element_name)
		tfprintf("failed: inquired value for %s != expected\n",
			 element_name);
	    return (0);
	} else if (strcmp(expectdata->anno_text_rel3.char_string, 
			  data->anno_text_rel3.char_string)) {
	    if (element_name)
		tfprintf("failed: inquired string for %s (%s) != expected (%s)\n",
			 element_name, data->anno_text_rel3.char_string,
			 expectdata->anno_text_rel3.char_string);
	    return (0);
	}
	break;
    case PELEM_APPL_DATA:
	if (expectdata->appl_data.size != data->appl_data.size) {
	    if (element_name)
		tfprintf("failed: inquired size for %s (%d) != expected (%d)\n",
			 element_name, data->appl_data.size,
			 expectdata->appl_data.size);
	    return (0);
	} else if (memcmp(expectdata->appl_data.data, data->appl_data.data,
			  data->appl_data.size)) {
	    if (element_name)
		tfprintf("failed: inquired data for %s doesn't match expected\n",
			 element_name);
	    return (0);
	}
	break;
    case PELEM_REFL_PROPS:
    case PELEM_BACK_REFL_PROPS:
	if (expectdata->props.ambient_coef != 
	      data->props.ambient_coef ||
	    expectdata->props.diffuse_coef != 
	      data->props.diffuse_coef ||
	    expectdata->props.specular_coef != 
	      data->props.specular_coef ||
	    expectdata->props.specular_exp != 
	      data->props.specular_exp) {
	    if (element_name)
		tfprintf("failed: inquired float data for %s doesn't match expected\n", element_name);
	    return (0);
	}
	if (!i_compare_Pgcolr(data->props.specular_colr,
			     expectdata->props.specular_colr)) {
	    if (element_name)
		tfprintf("failed: inquired general color of element %s doesn't match expected\n", element_name);
	    return(0);
	}
	break;
    case PELEM_BACK_INT_COLR:
    case PELEM_EDGE_COLR:
    case PELEM_INT_COLR:
    case PELEM_LINE_COLR:
    case PELEM_MARKER_COLR:
    case PELEM_TEXT_COLR:
	if (!i_compare_Pgcolr(data->colr,expectdata->colr)) {
	    if (element_name)
		tfprintf("failed: inquired %s doesn't match expected\n", 
			 element_name);
	    return(0);
	}
	break;

    case PELEM_CELL_ARRAY:
	if (!i_compare_Ppoint(data->cell_array.rect.p, expectdata->cell_array.rect.p) ||
	    !i_compare_Ppoint(data->cell_array.rect.q, expectdata->cell_array.rect.q) ||
	    expectdata->cell_array.colr_array.dims.size_x != data->cell_array.colr_array.dims.size_x  ||
	    expectdata->cell_array.colr_array.dims.size_y != data->cell_array.colr_array.dims.size_y  ||
	    memcmp(expectdata->cell_array.colr_array.colr_array, data->cell_array.colr_array.colr_array,
		   data->cell_array.colr_array.dims.size_x * data->cell_array.colr_array.dims.size_y 
		   * sizeof(Pint))) {
	    if (element_name)
		tfprintf("failed: inquired data for %s doesn't match expected\n",
			 element_name);
	    return (0);
	}
	break;
    case PELEM_CELL_ARRAY3:
	if (!i_compare_Ppoint3(&(expectdata->cell_array3.paral.p), 
			       &(data->cell_array3.paral.p)) ||
	    !i_compare_Ppoint3(&(expectdata->cell_array3.paral.q), 
			       &(data->cell_array3.paral.q)) ||
	    !i_compare_Ppoint3(&(expectdata->cell_array3.paral.r), 
			       &(data->cell_array3.paral.r)) ||
	    expectdata->cell_array3.colr_array.dims.size_x != data->cell_array3.colr_array.dims.size_x  ||
	    expectdata->cell_array3.colr_array.dims.size_y != data->cell_array3.colr_array.dims.size_y  ||
	    memcmp(expectdata->cell_array3.colr_array.colr_array, data->cell_array3.colr_array.colr_array,
		   data->cell_array3.colr_array.dims.size_x * data->cell_array3.colr_array.dims.size_y
		   * sizeof(Pint))) {
	    if (element_name)
		if (element_name)
		tfprintf("failed: inquired data for %s doesn't match expected\n",
			 element_name);
	    return (0);
	}
	break;
    case PELEM_CURVE_APPROX_CRIT:
	if (expectdata->curv_approx.type != data->curv_approx.type ||
	    !feq(expectdata->curv_approx.value, data->curv_approx.value)) {
	    if (element_name)
		tfprintf("failed: inquired  %s (%d,%f) != expected (%d,%f)\n", 
			 element_name, data->curv_approx.type, 
			 data->curv_approx.value, expectdata->curv_approx.type,
			 expectdata->curv_approx.value);
	    return (0);
	}
	break;
    case PELEM_EDGE_FLAG:
	if (expectdata->edge_flag != data->edge_flag) {
	    if (element_name)
		tfprintf("failed: inquired value for %s (%d) != expected (%d)\n",
			 element_name, expectdata->edge_flag, data->edge_flag);
	    return (0);
	}
	break;
    case PELEM_FACE_CULL_MODE:
	if (expectdata->cull_mode != data->cull_mode) {
	    if (element_name)
		tfprintf("failed: inquired element %s (%d) != expected (%d)\n",
			 element_name, data->cull_mode, expectdata->cull_mode);
	    return (0);
	}
	break;
    case PELEM_FACE_DISTING_MODE:
	if (expectdata->disting_mode != data->disting_mode) {
	    if (element_name)
		tfprintf("failed: inquired element %s (%d) != expected (%d)\n",
			 element_name, data->disting_mode, expectdata->disting_mode);
	    return (0);
	}
	break;
    case PELEM_FILL_AREA:
    case PELEM_POLYLINE:
    case PELEM_POLYMARKER:
        if (expectdata->point_list.num_points != data->point_list.num_points) {
	    if (element_name)
		tfprintf("failed: inquired num pts for %s (%d) != expected(%d)\n",
			 element_name, data->point_list.num_points, 
			 expectdata->point_list.num_points);
	    return (0);
	} 
	for (i = 0; i < data->point_list.num_points; i++) {
	    if (!i_compare_Ppoint(data->point_list.points[i], 
				  expectdata->point_list.points[i])) {
		if (element_name)
		    tfprintf("failed: inquired value for item %d in %s (%f,%f) != expected (%f,%f)\n",
			     i, element_name, 
			     data->point_list.points[i].x,
			     data->point_list.points[i].y,
			     expectdata->point_list.points[i].x,
			     expectdata->point_list.points[i].y);
		return (0);
	    }
        }    
        break;
    case PELEM_FILL_AREA_SET:
        if (expectdata->point_list_list.num_point_lists != data->point_list_list.num_point_lists) {
	    if (element_name)
		tfprintf("failed: inquired num sets for %s (%d) != expected(%d)\n",
			 element_name, data->point_list_list.num_point_lists,
			 expectdata->point_list_list.num_point_lists);
	    return (0);
	} else {
	    for (i=0; i < data->point_list_list.num_point_lists; i++) {
		for (j=0; j < data->point_list_list.point_lists[i].num_points; j++) {
		    if (!i_compare_Ppoint(data->point_list_list.point_lists[i].points[j],
		               expectdata->point_list_list.point_lists[i].points[j])) {
			if (element_name)
			    tfprintf("failed: coords of inquired point %d in set %d of %s != expected \n",
				     j, i, element_name);
			return (0);
		    }
		}
	    }
        }    
        break;
    case PELEM_FILL_AREA_SET3:
        if (expectdata->point_list_list3.num_point_lists != data->point_list_list3.num_point_lists) {
	    if (element_name)
		tfprintf("failed: inquired num sets for %s (%d) != expected(%d)\n",
			 element_name, data->point_list_list3.num_point_lists,
			 expectdata->point_list_list3.num_point_lists);
	    return (0);
	} else {
	    for (i=0; i < data->point_list_list3.num_point_lists; i++) {
		for (j=0; j < data->point_list_list3.point_lists[i].num_points; j++) {
		    inqpt3 = &data->point_list_list3.point_lists[i].points[j];
		    exppt3 = &expectdata->point_list_list3.point_lists[i].points[j];
		    if (!feq(inqpt3->x, exppt3->x)||
			!feq(inqpt3->y, exppt3->y)||
			!feq(inqpt3->z, exppt3->z)) {
			if (element_name)
			    tfprintf("failed: inquired value for item %d in set %d of %s (%f,%f,%f) != expected (%f,%f,%f)\n",
				     j, i, element_name, 
				     inqpt3->x, inqpt3->y, inqpt3->z,
				     exppt3->x, exppt3->y, exppt3->z);
			return (0);
		    }
		}
	    }
        }    
        break;
    case PELEM_FILL_AREA_SET3_DATA:
    {
	Pfacet_data_arr3	facet_data_arr, expfacet_data_arr;
						  /* needed to cleanly get facet */
						   /* into comparison routine */
	Pedge_data_list inqedges, expedges;	/* edge data list for a facet */
	int facet, edge;

	/* flags, color model, and number of facets */
	if (expectdata->fasd3.fflag != data->fasd3.fflag ||
	    expectdata->fasd3.eflag != data->fasd3.eflag ||
	    expectdata->fasd3.vflag != data->fasd3.vflag ||
	    expectdata->fasd3.colr_model != data->fasd3.colr_model ||
	    expectdata->fasd3.nfa != data->fasd3.nfa) {
	    status = 0;
	    if (element_name) tfprintf("failed: inquired value for %s != expected\n",
			 element_name);
	}
	if ((verbosity >= 1 && status == 0) || verbosity >= 3) {
	    tvprintf(1, "inquired facet, edge, vertex, color mod, num facets: %d, %d, %d, %d, %d\n",
		     data->fasd3.fflag, data->fasd3.eflag,
		     data->fasd3.vflag, data->fasd3.colr_model,
		     data->fasd3.nfa);
	    tvprintf(1,"expected facet, edge, vertex, color mod, num facets: %d, %d, %d, %d, %d\n",
		     expectdata->fasd3.fflag, expectdata->fasd3.eflag,
		     expectdata->fasd3.vflag, expectdata->fasd3.colr_model,
		     expectdata->fasd3.nfa);
	}
	if (status == 0)  return (0);

	/* facet data: first get data into a Pfacet_data_arr3, and call */
	/* comparison routine i_compare_Pfacet_data_arr3(). */
	if (data->fasd3.fflag ==PFACET_COLOUR) {
	    facet_data_arr.colrs = &(data->fasd3.fdata.colr);
	    expfacet_data_arr.colrs = &(expectdata->fasd3.fdata.colr);
	} else if (data->fasd3.fflag == PFACET_COLOUR_NORMAL) {
	    facet_data_arr.conorms = &(data->fasd3.fdata.conorm);
	    expfacet_data_arr.conorms = &(expectdata->fasd3.fdata.conorm);
	} else if (data->fasd3.fflag == PFACET_NORMAL) {
	    facet_data_arr.norms = &(data->fasd3.fdata.norm);
	    expfacet_data_arr.norms = &(expectdata->fasd3.fdata.norm);
	} else {
	    if (element_name) tfprintf("failed: invalid facet data flag %d\n",
				       data->fasd3.fflag);
	    return(0);
	}
	if (!i_compare_Pfacet_data_arr3(data->fasd3.fflag, data->fasd3.colr_model,
					facet_data_arr, expfacet_data_arr, 1)) {
	    if (element_name) tfprintf("failed: facet data for %s not equal expected\n",
					   element_name);
		return (0);
	}
				   
	/* 
	 * check edge data for each facet 
	 */

	for (facet=0; facet < data->fasd3.nfa; facet++) {
	    inqedges = data->fasd3.edata[facet];
	    expedges = expectdata->fasd3.edata[facet];
	    if (inqedges.num_edges != expedges.num_edges) {
		if (element_name) 
		    tfprintf("failed: inquired number of edges for facet %d of %s (%d) != expected (%d)\n", 
			     facet, element_name, inqedges.num_edges, 
			     expedges.num_edges);
		return (0);
	    }
	    for (edge=0; edge < inqedges.num_edges; edge++)
		if (inqedges.edgedata.edges[edge] != expedges.edgedata.edges[edge]) {
		    if (element_name) 
			tfprintf("failed: inquired edge flag %d of facet %d of %s (%d) != expected (%d)\n", 
				 edge, facet, element_name,
				 inqedges.edgedata.edges[edge], 
				 expedges.edgedata.edges[edge]);
		return (0);
	    }
	}

	/* 
	 * for each facet i, check number of vertices and call 
	 * comparison routine for facet data.
	 */

	for (facet=0; facet < data->fasd3.nfa; facet++) {
	    if (data->fasd3.vdata[facet].num_vertices != 
		expectdata->fasd3.vdata[facet].num_vertices) {
		if (element_name) 
		    tfprintf("failed: inquired number of vertices for facet %d of %s (%d) != expected (%d)\n", 
			     facet, element_name, data->fasd3.vdata[facet].num_vertices, 
			     expectdata->fasd3.vdata[facet].num_vertices);
		return (0);
	    }

	    if (!i_compare_Pfacet_vdata_arr3(data->fasd3.vflag,
					     data->fasd3.colr_model,
					     data->fasd3.vdata[facet].vertex_data,
					     expectdata->fasd3.vdata[facet].vertex_data,
					     data->fasd3.vdata[facet].num_vertices)) {
		if (element_name)
		    tfprintf("failed: vertex data for facet %d of %s != expected\n",
			     facet, element_name);
		return(0);
	    }


	}

    }

	break;
    case PELEM_FILL_AREA3:
    case PELEM_POLYLINE3:
    case PELEM_POLYMARKER3:
        if (expectdata->point_list3.num_points != data->point_list3.num_points) {
	    if (element_name)
		tfprintf("failed: inquired num pts for %s (%d) != expected (%d)\n",
			 element_name, data->point_list3.num_points,
			 expectdata->point_list3.num_points);
	    return (0);
	} else {
	    for (i = 0; i < data->point_list3.num_points; i++) {
		if (!i_compare_Ppoint3(data->point_list3.points[i], 
				       expectdata->point_list3.points[i])) {
		    if (element_name)
			tfprintf("failed: inquired value for point %d in %s != expected\n",
				 i, element_name);
		    return (0);
		}
	    }
        }    
        break;
    case PELEM_GLOBAL_MODEL_TRAN:
	for (i=0; i<3; i++)
	    for (j=0; j<3; j++)
		if (!feq(expectdata->global_tran[i][j],
			 data->global_tran[i][j])) {
		    if (element_name)
			tfprintf("failed: inquired transform element [%d][%d] of %s was %f != expected %f\n",
				 i, j, element_name, data->global_tran[i][j],
				 expectdata->global_tran[i][j]);
		    return (0);
		}
	break;
    case PELEM_GLOBAL_MODEL_TRAN3:
	for (i=0; i<4; i++)
	    for (j=0; j<4; j++)
		if (!feq(expectdata->global_tran3[i][j],
			 data->global_tran3[i][j])) {
		    if (element_name)
			tfprintf("failed: inquired transform element [%d][%d] of %s was %f != expected %f\n",
				 i, j, element_name, data->global_tran3[i][j],
				 expectdata->global_tran3[i][j]);
		    return (0);
		}
	break;
    case PELEM_INDIV_ASF:
	if (data->asf.id != expectdata->asf.id ||
	    data->asf.source != expectdata->asf.source) {
	    if (element_name) 
		tfprintf("failed: inquired value for %s (%d, %d) != expected (%d, %d)\n", 
			 element_name, data->asf.id, data->asf.source,
			 expectdata->asf.id, expectdata->asf.source);
	    return (0);
	}
	break;
    case PELEM_INT_STYLE:
    case PELEM_BACK_INT_STYLE:
	if (expectdata->int_style != data->int_style) {
	    if (element_name)
		tfprintf("failed: inquired value for %s (%d) != expected (%d)\n",
			 element_name, expectdata->int_style, data->int_style);
	    return (0);
	}
	break;
    case PELEM_LIGHT_SRC_STATE:
	if (!i_compare_Pint_list(data->lss.activation,
				 expectdata->lss.activation)) {
	    if (element_name)
		tfprintf("failed: activation list for %s != expected\n",
			 element_name);
	    return (0);
	}
	if (!i_compare_Pint_list(data->lss.deactivation,
				 expectdata->lss.deactivation)) {
	    if (element_name)
		tfprintf("failed: deactivation list for %s != expected\n",
			 element_name);
	    return (0);
	}
	break;
    case PELEM_LOCAL_MODEL_TRAN:
	if (expectdata->local_tran.compose_type != data->local_tran.compose_type) {
	    if (element_name)
		tfprintf("failed: inquired composition type for %s (%d) != expected (%d)\n",
			 element_name, data->local_tran.compose_type,
			 expectdata->local_tran.compose_type);
	    return (0);
	}
	for (i=0; i<3; i++)
	    for (j=0; j<3; j++)
		if (!feq(expectdata->local_tran.matrix[i][j],
			 data->local_tran.matrix[i][j])) {
		    if (element_name)
			tfprintf("failed: inquired transform element [%d][%d] of %s was %f != expected %f\n",
				 i, j, element_name, data->local_tran.matrix[i][j],
				 expectdata->local_tran.matrix[i][j]);
		    return (0);
		}
	break;
    case PELEM_LOCAL_MODEL_TRAN3:
	if (expectdata->local_tran3.compose_type != data->local_tran3.compose_type) {
	    if (element_name)
		tfprintf("failed: inquired composition type for %s (%d) != expected (%d)\n",
			 element_name, data->local_tran3.compose_type,
			 expectdata->local_tran3.compose_type);
	    return (0);
	}
	for (i=0; i<4; i++)
	    for (j=0; j<4; j++)
		if (!feq(expectdata->local_tran3.matrix[i][j],
			 data->local_tran3.matrix[i][j])) {
		    if (element_name)
			tfprintf("failed: inquired transform element [%d][%d] of %s was %f != expected %f\n",
				 i, j, element_name, data->local_tran3.matrix[i][j],
				 expectdata->local_tran3.matrix[i][j]);
		    return (0);
		}
	break;
    case PELEM_MODEL_CLIP_IND:
	if (data->clip_ind != expectdata->clip_ind) {
	    if (element_name)
		tfprintf("failed: inquired %s (%d) != expected (%d)\n",
			 element_name, data->clip_ind, expectdata->clip_ind);
	    return (0);
	}
	break;
    case PELEM_MODEL_CLIP_VOL:
	if (data->model_clip.op != expectdata->model_clip.op) {
	    if (element_name)
		tfprintf("failed: inquired op for %s (%d) != expected (%d)\n",
			 element_name, data->model_clip.op, expectdata->model_clip.op);
	    return (0);
	}
        if (data->model_clip.half_spaces.num_half_spaces != expectdata->model_clip.half_spaces.num_half_spaces) {
	    if (element_name)
		tfprintf("failed: inquired half space number for %s (%d) != expected (%d)\n",
			 element_name, data->model_clip.half_spaces.num_half_spaces, 
			 expectdata->model_clip.half_spaces.num_half_spaces);
	    return (0);
	}
	for (i=0; i < data->model_clip.half_spaces.num_half_spaces; i++) {
	    inqhs = &data->model_clip.half_spaces.half_spaces[i];
	    exphs = &expectdata->model_clip.half_spaces.half_spaces[i];
	    if (!i_compare_Ppoint(&inqhs->point, &exphs->point) ||
		!i_compare_Pvec(&inqhs->norm, &exphs->norm)) {
		if (element_name)
		    tfprintf("failed: inquired half_space %d for %s != expected\n",
			     i, element_name);
		return (0);
	    }
	}
	break;
    case PELEM_MODEL_CLIP_VOL3:
	if (data->model_clip3.op != expectdata->model_clip3.op) {
	    if (element_name)
		tfprintf("failed: inquired op for %s (%d) != expected (%d)\n",
			 element_name, data->model_clip3.op, expectdata->model_clip3.op);
	    return (0);
	}
	if (data->model_clip3.half_spaces.num_half_spaces != expectdata->model_clip3.half_spaces.num_half_spaces) {
	    if (element_name)
		tfprintf("failed: inquired half space number for %s (%d) != expected (%d)\n",
			 element_name, data->model_clip3.half_spaces.num_half_spaces, 
			 expectdata->model_clip3.half_spaces.num_half_spaces);
	    return (0);
	}
	for (i=0; i < data->model_clip3.half_spaces.num_half_spaces; i++) {
	    inqhs3 = &data->model_clip3.half_spaces.half_spaces[i];
	    exphs3 = &expectdata->model_clip3.half_spaces.half_spaces[i];
	    if (!i_compare_Ppoint3(&inqhs3->point, &exphs3->point) ||
		!i_compare_Pvec3(&inqhs3->norm, &exphs3->norm)) {
		if (element_name)
		    tfprintf("failed: inquired half_space %d for %s != expected\n",
			     i, element_name);
		return (0);
	    }
	}
	break;
    case PELEM_PAT_REF_POINT:
    case PELEM_PAT_SIZE:
	if (!i_compare_Ppoint(data->pat_ref_point, expectdata->pat_ref_point)) {
	    if (element_name)
		tfprintf("failed: inquired %s (%f,%f) != expected (%f,%f)\n",
			 element_name, data->pat_ref_point.x, data->pat_ref_point.y,
			 expectdata->pat_ref_point.x, expectdata->pat_ref_point.y);
	    return (0);
	}
	break;
    case PELEM_PAT_REF_POINT_VECS:
	if (!i_compare_Ppoint3(&data->pat_ref_point_vecs.ref_point, 
		&expectdata->pat_ref_point_vecs.ref_point) ||
	    !i_compare_Pvec3(&data->pat_ref_point_vecs.ref_vec[0], 
		&expectdata->pat_ref_point_vecs.ref_vec[0]) ||
	    !i_compare_Pvec3(&data->pat_ref_point_vecs.ref_vec[1], 
		&expectdata->pat_ref_point_vecs.ref_vec[1])) {
	    if (element_name)
		tfprintf("failed: inquired %s != expected\n",
			 element_name);
	    return (0);
	}
	break;
    case PELEM_POLYLINE_SET3_DATA:
	if (data->plsd3.vflag != expectdata->plsd3.vflag ||
	    data->plsd3.colr_model != expectdata->plsd3.colr_model ||
	    data->plsd3.npl != expectdata->plsd3.npl) {
	    if (element_name)
		tfprintf("failed: inquired value for %s != expected\n",
			 element_name);
	    status = 0;
	}
	if ((verbosity >= 1 && status == 0) || verbosity >= 3) {
	    tvprintf(1, "inquired vflag=%d, colr_model=%d, num polylines=%d\n",
		     data->plsd3.vflag, data->plsd3.colr_model,
		     data->plsd3.npl);
	    tvprintf(1, "expected vflag=%d, colr_model=%d, num polylines=%d\n",
		     expectdata->plsd3.vflag, expectdata->plsd3.colr_model,
		     expectdata->plsd3.npl);
	}
	if (status == 0)  return (0);

	/* 
	 * check vertex data for each vertex of each polyline.
	 */
    {
	Pline_vdata_list3 inqverts, expverts;  /* vertex data for a polyline */
	int pline, vertex;

	for (pline=0; pline < data->plsd3.npl; pline++) {
	    inqverts = data->plsd3.vdata[pline];
	    expverts = expectdata->plsd3.vdata[pline];

	    if (inqverts.num_vertices != expverts.num_vertices) {
		if (element_name) 
		    tfprintf("failed: inquired number of vertices for pline %d of %s (%d) != expected (%d)\n", 
			     pline, element_name, inqverts.num_vertices, 
			     expverts.num_vertices);
		return (0);
	    }

	    if (data->plsd3.vflag == PVERT_COORD) {
		for (vertex=0; vertex < inqverts.num_vertices; vertex++)
		    if (!i_compare_Ppoint3(inqverts.vertex_data.points[vertex],
					   expverts.vertex_data.points[vertex])) {
			if (element_name)
			    tfprintf("failed: coords of vertex %d of pline %d of %s != expected\n", 
				     vertex, pline, element_name);
			return (0);
		    }
	    } else if (data->plsd3.vflag == PVERT_COORD_COLOUR) {
		for (vertex=0; vertex < inqverts.num_vertices; vertex++) {
		    if (!i_compare_Ppoint3(inqverts.vertex_data.ptcolrs[vertex].point,
					expverts.vertex_data.ptcolrs[vertex].point)) {
			if (element_name)
			    tfprintf("failed: coords of vertex %d of pline %d of %s != expected\n", 
				     vertex, pline, element_name);
			return (0);
		    }
		    if (!i_compare_Pcoval(
			      inqverts.vertex_data.ptcolrs[vertex].colr, 
			      expverts.vertex_data.ptcolrs[vertex].colr,
			      data->plsd3.colr_model)) {
			if (element_name) tfprintf("failed: vertex color for vertex %s of pline %s != expected\n",
					   vertex, pline, element_name);
			return (0);
		    }
		}
	    } else {
		if (element_name)
		    tfprintf("failed: invalid vertex flag for %s (%d)\n",
			     element_name, data->plsd3.vflag);
		return (0);
	    }

	}

    }
	
	break;
    case PELEM_QUAD_MESH3_DATA:
    {
	Pedge_data_list inqedges, expedges;	/* edge data list for a facet */
	int facet, edge;

	/* check flags, color model, and mesh dimensions */
	if (expectdata->qmd3.fflag != data->qmd3.fflag ||
	    expectdata->qmd3.vflag != data->qmd3.vflag ||
	    expectdata->qmd3.colr_model != data->qmd3.colr_model ||
	    expectdata->qmd3.dim.size_x != data->qmd3.dim.size_x,
	    expectdata->qmd3.dim.size_y != data->qmd3.dim.size_y) {
	    status = 0;
	    if (element_name) tfprintf("failed: inquired value for %s != expected\n",
			 element_name);
	}
	if ((verbosity >= 1 && status == 0) || verbosity >= 3) {
	    tvprintf(1, "inquired facet &  vertex flag, color mod, dims: %d, %d, %d, %d, (%d,%d)\n",
		     data->qmd3.fflag, data->qmd3.vflag, data->qmd3.colr_model,
		     data->qmd3.dim.size_x, data->qmd3.dim.size_y);
	    tvprintf(1,"expected facet & vertex flag, color mod, dims: %d, %d, %d, %d, (%d,%d)\n",
		     expectdata->qmd3.fflag, 
		     expectdata->qmd3.vflag, expectdata->qmd3.colr_model,
		     expectdata->qmd3.dim.size_x, expectdata->qmd3.dim.size_y);
	}
	if (status == 0)  return (0);

	/* check facet data */
	if (!i_compare_Pfacet_data_arr3(data->qmd3.fflag, data->qmd3.colr_model,
			data->qmd3.fdata, expectdata->qmd3.fdata,
			((data->qmd3.dim.size_x - 1) * (data->qmd3.dim.size_x - 1)))) {
	    if (element_name) tfprintf("failed: facet data for %s not equal expected\n",
				       element_name);
	    return(0);
	}				   

	/* check vertex data */
	if (!i_compare_Pfacet_vdata_arr3(data->qmd3.vflag,
				data->qmd3.colr_model,
				data->qmd3.vdata,
				expectdata->qmd3.vdata,
			        (data->qmd3.dim.size_x - 1) * (data->qmd3.dim.size_x - 1))) {
	    if (element_name)
		tfprintf("failed: vertex data for %s != expected\n",
			 facet, element_name);
	    return(0);
	}

    }
	break;
    case PELEM_RESTORE_MODEL_CLIP_VOL:
	/* has no data -- do nothing */
	break;
    case PELEM_SURF_APPROX_CRIT:
	if (data->surf_approx.type != expectdata->surf_approx.type ||
	    !feq(data->surf_approx.u_val, expectdata->surf_approx.u_val) ||
	    !feq(data->surf_approx.v_val, expectdata->surf_approx.v_val)) {
	    if (element_name)
		tfprintf("failed: inquired %s (%d,%f,%f) != expected (%d,%f,%f)\n",
			 element_name, data->surf_approx.type,
			 data->surf_approx.u_val, data->surf_approx.v_val,
			 expectdata->surf_approx.type,
			 expectdata->surf_approx.u_val, expectdata->surf_approx.v_val);
	    return (0);
	}
	break;
    case PELEM_TEXT:
	if (!i_compare_Ppoint(data->text.pos, expectdata->text.pos)) {
	    if (element_name)
		tfprintf("failed: inquired position for %s != expected\n",
			 element_name);
	    return (0);
	} else if (strcmp(expectdata->text.char_string, 
			  data->text.char_string)) {
	    if (element_name)
		tfprintf("failed: inquired string for %s (%s) != expected (%s)\n",
			 element_name, data->text.char_string, 
			  expectdata->text.char_string);
	    return (0);
	}
       break;
    case PELEM_TEXT3:
	if (!i_compare_Ppoint3(expectdata->text3.pos, data->text3.pos) ||
	    !i_compare_Pvec3(expectdata->text3.dir[0], 
			     data->text3.dir[0]) ||
	    !i_compare_Pvec3(expectdata->text3.dir[1], 
			     data->text3.dir[1]) ||
	    strcmp(expectdata->text3.char_string, data->text3.char_string)) {
	    if (element_name)
		tfprintf("failed: inquired value for %s != expected\n",
			 element_name);
	    return (0);
	}
	break;
    case PELEM_TEXT_PREC:
	if (expectdata->text_prec != data->text_prec) {
	    if (element_name)
		tfprintf("failed: inquired value for %s != expected\n",
			 element_name);
	    return (0);
	}
	break;
    case PELEM_TRI_STRIP3_DATA:
    {
	Pedge_data_list inqedges, expedges;	/* edge data list for a facet */
	int facet, edge;

	/* check flags, color model, and mesh dimensions */
	if (expectdata->tsd3.fflag != data->tsd3.fflag ||
	    expectdata->tsd3.vflag != data->tsd3.vflag ||
	    expectdata->tsd3.colr_model != data->tsd3.colr_model ||
	    expectdata->tsd3.nv != data->tsd3.nv) {
	    status = 0;
	    if (element_name) tfprintf("failed: inquired value for %s != expected\n",
			 element_name);
	}
	if ((verbosity >= 1 && status == 0) || verbosity >= 3) {
	    tvprintf(1, "inquired facet &  vertex flag, color mod, num verts: %d, %d, %d, %d\n",
		     data->tsd3.fflag, data->tsd3.vflag, data->tsd3.colr_model,
		     data->tsd3.nv);
	    tvprintf(1,"expected facet & vertex flag, color mod, num verts: %d, %d, %d, %d\n",
		     expectdata->tsd3.fflag, expectdata->tsd3.vflag, 
		     expectdata->tsd3.colr_model, expectdata->tsd3.nv);
	}
	if (status == 0)  return (0);

	/* check facet data */
	if (!i_compare_Pfacet_data_arr3(data->tsd3.fflag, data->tsd3.colr_model,
					data->tsd3.fdata, expectdata->tsd3.fdata,
					data->tsd3.nv - 2)) {
	    if (element_name) tfprintf("failed: facet data for %s not equal expected\n",
				       element_name);
	    return(0);
	}				   

	/* check vertex data */
	if (!i_compare_Pfacet_vdata_arr3(data->tsd3.vflag,
					 data->tsd3.colr_model,
					 data->tsd3.vdata,
					 expectdata->tsd3.vdata,
					 data->tsd3.nv)) {
	    if (element_name)
		tfprintf("failed: vertex data for %s != expected\n",
			 facet, element_name);
	    return(0);
	}

    }
	break;

    default:
        tfprintf("ERROR - i_compare_element_content: Unknown element type %d (\"%s\"\n", 
		 type, element_name);
        exit (1);
    }

    /* if we got here, data matched */
    return (1);
}


/*
 * printPlimit(limit)
 */
static void
printPlimit(limit)
        Plimit limit;
{
        printf("(%.2f,%.2f,%.2f,%.2f) ",
                limit.x_min,limit.x_max, limit.y_min,limit.y_max);
}

	
	
/*
 * printPlimit3(msg,limit3)
 */
static void
printPlimit3(limit3)
        Plimit3 limit3;
{
        printf("(%.2f,%.2f,%.2f,%.2f,%.2f,%.2f) ",
                limit3.x_min,limit3.x_max,limit3.y_min,limit3.y_max,
                limit3.z_min,limit3.z_max);
}

