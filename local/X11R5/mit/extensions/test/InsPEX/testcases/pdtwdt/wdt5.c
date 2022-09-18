
/* $XConsortium: wdt5.c,v 5.2 91/07/15 12:20:17 hersh Exp $ */

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
 ## wdt5.c : 
 ## compares the implementation dependent data in workstation description table
 ## against the values returned from inquiries:
 ## Testing PHIGS+ inqure xxx facilities and ws state tables
 ##
 # Supplying command argument :
 ## 1: to test pinq_line_facs_plus
 ## 2: to test pinq_int_facs_plus
 ## 3: to test pinq_dcue_facs
 ## 4: to test pinq_light_src_facs
 ## 5: to test pinq_curv_surf_facs
 ## 6: to test pinq_direct_colr_model_facs
 ## 7: to test pinq_rendering_colr_model_facs
 ## 8: to test pinq_colr_map_facs
 ## 9: to test pinq_ws_st_table_plus
 ## 10: to test pinq_dyns_ws_attrs_plus
 */

#include "phigs/phigs.h"
#include "imath.h"
#include "wdt.h"
#include "logmsg.h"

/* constants */
#define BUFSIZE 1024
#define BOGUSERR -999

#define ERROR(string) \
	if (err) { \
		tfprintf("ERROR: %d in %s\n", err,string);\
		return;\
	}

static void verify_line_facilities_plus();
static void verify_interior_facilities_plus();
static void verify_depth_cue_facilities();
static void verify_light_source_facilities();
static void verify_curve_surface_facilities();
static void verify_direct_colour_model_facilities();
static void verify_rendering_colour_model_facilities();
static void verify_colour_mapping_facilities();
static void verify_ws_state_table_plus();
static void verify_ws_dynamics_plus();

/* commonly used variables */
Pint err;
Pint status;
Pint total;
Pint wstype;		/* specific workstation type */

main(argc,argv)
        int argc;
        char **argv;
{
        char charbuf[BUFSIZE];
        Pconnid cid;
        char testdesc[256];
	int i,test;



	sprintf(testdesc,"\"%s\" PHIGS+ workstation facilities inquiry",WSTYPE); 
	tbegintest("wdt5",testdesc);
	i_open_phigs((char *)0, PDEF_MEM_SIZE);
	/* ws type dependent procedure to open a ws */
	OPEN_WS1()
	err = BOGUSERR;
        cid = charbuf;
        pinq_ws_conn_type(1,BUFSIZE,&err,&cid,&wstype);
        ERROR("pinq_ws_conn_type");

        if (argc < 2) {
            	verify_line_facilities_plus();
            	verify_interior_facilities_plus();
            	verify_depth_cue_facilities();
            	verify_light_source_facilities();
            	verify_curve_surface_facilities();
            	verify_direct_colour_model_facilities();
            	verify_rendering_colour_model_facilities();
            	verify_colour_mapping_facilities();
            	verify_ws_state_table_plus();
		verify_ws_dynamics_plus();
        }else
        for (i = 1; i < argc; ++i) {
                test = atoi(argv[i]);
                switch(test) {
                case 1:
  			tvprintf(2,"testing pinq_line_facs_plus\n");
            		verify_line_facilities_plus();
			break;
                case 2:
			tvprintf(2,"testing pinq_int_facs_plus \n");
            		verify_interior_facilities_plus();
			break;
                case 3:
  			tvprintf(2,"testing pinq_dcue_facs\n");
            		verify_depth_cue_facilities();
			break;
                case 4:
  			tvprintf(2,"testing pinq_light_src_facs\n");
            		verify_light_source_facilities();
			break;
                case 5:
  			tvprintf(2,"testing pinq_curv_surf_facs\n");
            		verify_curve_surface_facilities();
			break;
                case 6:
  			tvprintf(2,"testing pinq_direct_colr_model_facs\n");
            		verify_direct_colour_model_facilities();
			break;
                case 7:
  			tvprintf(2,"testing pinq_rendering_colr_model_facs\n");
            		verify_rendering_colour_model_facilities();
			break;
                case 8:
  			tvprintf(2,"testing pinq_colr_map_facs\n");
            		verify_colour_mapping_facilities();
			break;
                case 9:
 			tvprintf(2,"to test pinq_ws_st_table_plus\n");
            		verify_ws_state_table_plus();
			break;
                case 10:
			verify_ws_dynamics_plus();
 			tvprintf(2,"to test pinq_dyns_ws_attrs_plus\n");
			break;
                default:
                        tabort("ERROR: invalid argument \"%s\"\n",argv[i]);
		}
	}
	tendtest();
}

/*
 * verify_line_facilities_plus() 
 * verify the number and list of available line types
 * 	  number of available, nominal, minimum and maximum linewidths
 *        number of predefined polyline indices
 *        number and list of line shading methods
 */
static void
verify_line_facilities_plus() 
{

	Pint_list	explinetype;
	Pint_list	expshades;
	Pint intbuf1[BUFSIZE];
	Pint intbuf2[BUFSIZE];
	Pline_facs_plus lnfacil;
	Pint total_line_type, total_shade_method;

	lnfacil.types.ints = intbuf1;
	lnfacil.shads.ints = intbuf2;
	err = BOGUSERR;
	pinq_line_facs_plus(wstype,BUFSIZE,0,BUFSIZE,0,&err,
		&total_line_type,&total_shade_method,&lnfacil);
	ERROR("pinq_line_facs_plus");

	explinetype.num_ints = num_line_type;
	explinetype.ints = list_line_type;
	expshades.num_ints = num_line_shading_method;
	expshades.ints = list_line_shading_method;
	if (! i_compare_Pint_list(lnfacil.types,explinetype))
		tfprintf("failed: list of line types != expected\n");

	if (fne( lnfacil.nom_width, nom_line_width))
		tfprintf("failed: nominal line width = %.4f, expected %.4f\n",
			lnfacil.nom_width, nom_line_width);

	if (fne( lnfacil.min_width, min_line_width))
		tfprintf("failed: minimum line width = %.4f, expected %.4f\n",
			lnfacil.min_width, min_line_width);

	if (fne( lnfacil.max_width, max_line_width))
		tfprintf("failed: maximum line width = %.4f, expected %.4f\n",
			lnfacil.max_width, max_line_width);

	if (lnfacil.num_pred_inds != num_pred_line_idx)
		tfprintf("failed: # of predefined line idx = %d, expected %d\n",
			lnfacil.num_pred_inds,num_pred_line_idx);

	if (! i_compare_Pint_list(lnfacil.shads,expshades))
		tfprintf("failed: list of line shading methods != expected\n");
}

/*
 * verify_interior_facilities_plus() 
 * verify the number and list of available interior types
 *        number and list of available hatch styles
 *        number of predefined interior indices
 *        number and list of interior shading methods
 *        number and list of reflectance equations
 */
static void
verify_interior_facilities_plus() 
{

	Pint_list	exphatchstyle;
	Pint_list	expshades;
	Pint_list	exprefeqs;
	Pint intbuf1[BUFSIZE];
	Pint intbuf2[BUFSIZE];
	Pint intbuf3[BUFSIZE];
	Pint_facs_plus interfacil;
	Pint total_int_style,total_hatch_style,total_refeqs,total_shades;
	Pint_style interstyle[BUFSIZE];

	interfacil.hatch_styles.ints = intbuf1;
	interfacil.refl_eqns.ints = intbuf2;
	interfacil.shad_meths.ints = intbuf3;
	interfacil.int_styles = interstyle;
	err = BOGUSERR;
	pinq_int_facs_plus(wstype,BUFSIZE,0,BUFSIZE,0,BUFSIZE,0,BUFSIZE,0,
		&err,&interfacil,&total_int_style,&total_hatch_style,
		&total_refeqs,&total_shades);
	ERROR("pinq_int_facs_plus");

	if (interfacil.num_int_styles != num_interior_style)
		tfprintf("failed: # of interior style = %d, expected %d\n",
			interfacil.num_int_styles,num_interior_style);
	else {
		if (! i_compare_Pint_style_array(interfacil.num_int_styles,
			interfacil.int_styles, list_interior_style))
			tfprintf("failed: list of interior styles != expected\n");
	}
	exphatchstyle.num_ints = num_hatch_style;
	exphatchstyle.ints = list_hatch_style;
	if (! i_compare_Pint_list(interfacil.hatch_styles,exphatchstyle))
		tfprintf("failed: list of hatch styles != expected\n");

	exprefeqs.num_ints = num_reflectance_equation;
	exprefeqs.ints = list_reflectance_equation;
	if (! i_compare_Pint_list(interfacil.refl_eqns,exprefeqs))
		tfprintf("failed: list of reflectance equations != expected\n");

	expshades.num_ints = num_interior_shading_method;
	expshades.ints = list_interior_shading_method;
	if (! i_compare_Pint_list(interfacil.shad_meths,expshades))
		tfprintf("failed: list of shading methods != expected\n");

	if (interfacil.num_pred_inds != num_pred_interior_idx)
		tfprintf("failed: # of predefined interior idx = %d, expected %d\n",
			interfacil.num_pred_inds,num_pred_interior_idx);
}

/*
 * verify_depth_cue_facilities() 
 * Verify the number of predefined depth cue indices
 */
static void
verify_depth_cue_facilities() 
{

	Pint num;

	err = BOGUSERR;
	pinq_dcue_facs(wstype,&err,&num);
	ERROR("pinq_dcue_facs");
	if (num != num_pred_depth_cue_idx)
		tfprintf("failed: # of predefined depth cue idx=%d,expected %d\n",
			num,num_pred_depth_cue_idx);
}

/*
 * verify_light_source_facilities() 
 * verify the number and list of available light source types
 * 	  maximum number of simultaneously active lights
 *        number of predefined light source indices
 */
static void
verify_light_source_facilities() 
{

	Pint_list	exptype;
	Pint intbuf[BUFSIZE];
	Plight_src_facs lightsrcfacil;

	lightsrcfacil.types.ints = intbuf;
	err = BOGUSERR;
	pinq_light_src_facs(wstype,BUFSIZE,0,&err,&total,&lightsrcfacil);
	ERROR("pinq_light_src_facs");

	exptype.num_ints = num_light_src_type;
	exptype.ints = list_light_src_type;
	if (! i_compare_Pint_list(lightsrcfacil.types,exptype))
		tfprintf("failed: list of light source types != expected\n");

	if (lightsrcfacil.max != max_num_simult_light)
		tfprintf("failed: max # of simultaneously active lights = %d, expected %d\n",
			lightsrcfacil.max, max_num_simult_light);

	if (lightsrcfacil.num_pred_inds != num_pred_light_src_idx)
		tfprintf("failed: # of predefined light_src idx = %d, expected %d\n",
			lightsrcfacil.num_pred_inds,num_pred_light_src_idx);
}

/*
 * verify_curve_surface_facilities() 
 */
static void
verify_curve_surface_facilities() 
{

	Pint_list	exptype;
	Pint intbuf1[BUFSIZE],intbuf2[BUFSIZE],intbuf3[BUFSIZE];
	Pint intbuf4[BUFSIZE], intbuf5[BUFSIZE],intbuf6[BUFSIZE];
	Pcurvsurf_facs facil;
	Pint total_c,total_s,total_tc,total_ps;

	facil.cat_types.ints = intbuf3;
	facil.sat_types.ints = intbuf4;
	facil.tcat_types.ints = intbuf5;
	facil.psc_types.ints = intbuf6;
	err = BOGUSERR;
	pinq_curv_surf_facs(wstype,BUFSIZE,0,BUFSIZE,0,BUFSIZE,0,BUFSIZE,0,
		&err,&facil,&total_c,&total_s,&total_tc,&total_ps);
	ERROR("pinq_curv_surf_facs");

	if (facil.max_bsp_order != max_nurb_order)
		tfprintf("failed: max non-uniform B-spline order = %d, expected %d\n",
			facil.max_bsp_order, max_nurb_order);
	if (facil.max_tc_order != max_trim_curve_order)
		tfprintf("failed: max trim curve order = %d, expected %d\n",
			facil.max_tc_order, max_trim_curve_order);


	exptype.num_ints = num_curve_approx_type;
	exptype.ints = list_curve_approx_type;
	if (! i_compare_Pint_list(facil.cat_types,exptype))
		tfprintf("failed: list of curve approximation types != expected\n");
	exptype.num_ints = num_surface_approx_type;
	exptype.ints = list_surface_approx_type;
	if (! i_compare_Pint_list(facil.sat_types,exptype))
		tfprintf("failed: list of surface approximation types != expected\n");
	exptype.num_ints = num_trim_curve_approx_type;
	exptype.ints = list_trim_curve_approx_type;
	if (! i_compare_Pint_list(facil.tcat_types,exptype))
		tfprintf("failed: list of trimming curve approximation types != expected\n");

	exptype.num_ints = num_para_surface_type;
	exptype.ints = list_para_surface_type;
	if (! i_compare_Pint_list(facil.psc_types,exptype))
		tfprintf("failed: list of parametric surface characteristics != expected\n");

}

/*
 * verify_direct_colour_model_facilities() 
 * verify the number and list of available direct colour model 
 */
static void
verify_direct_colour_model_facilities() 
{

	Pint_list	model,expmodel;
	Pint intbuf[BUFSIZE];

	model.ints = intbuf;
	err = BOGUSERR;
	pinq_direct_colr_model_facs(wstype,BUFSIZE,0,&err,&total,&model);
	ERROR("pinq_direct_colr_model_facs");

	expmodel.num_ints = num_direct_col_model;
	expmodel.ints = list_direct_col_model;
	if (! i_compare_Pint_list(model,expmodel))
		tfprintf("failed: list of direct colour model != expected\n");
}

/*
 * verify_rendering_colour_model_facilities() 
 * verify the number and list of available rendering colour model 
 */
static void
verify_rendering_colour_model_facilities() 
{

	Pint_list	model,expmodel;
	Pint intbuf[BUFSIZE];

	model.ints = intbuf;
	err = BOGUSERR;
	pinq_rendering_colr_model_facs(wstype,BUFSIZE,0,&err,&model,&total);
	ERROR("pinq_rendering_colr_model_facs");

	expmodel.num_ints = num_rendering_col_model;
	expmodel.ints = list_rendering_col_model;
	if (! i_compare_Pint_list(model,expmodel))
		tfprintf("failed: list of rendering colour model != expected\n");
}

/*
 * verify_colour_mapping_facilities() 
 * verify the number and list of available rendering colour model 
 */
static void
verify_colour_mapping_facilities() 
{

	Pint_list expmethod;
	Pint intbuf[BUFSIZE];
	Pcolr_map_facs cmapfacs;

	cmapfacs.meths.ints = intbuf;
	err = BOGUSERR;
	pinq_colr_map_facs(wstype,BUFSIZE,0,&err,&cmapfacs,&total);
	ERROR("pinq_colr_map_facs");

	expmethod.num_ints = num_cmap_method;
	expmethod.ints = list_cmap_method;
	if (! i_compare_Pint_list(cmapfacs.meths,expmethod))
		tfprintf("failed: list of colour mapping method != expected\n");

	if (cmapfacs.num_pred_inds != num_pred_cmap_idx )
		tfprintf("failed: # of predefined colour mapping method = %d, expected %d\n",cmapfacs.num_pred_inds, num_pred_cmap_idx);
}

/*
 * verify_ws_state_table_plus
 */
static void
verify_ws_state_table_plus()
{
        Pws_tables_plus tables;
 
        err = BOGUSERR;
        pinq_ws_st_table_plus(wstype,&err,&tables);
        ERROR("pinq_ws_st_table_plus");
        if (tables.line_bundles != ws_tbl_lengths_plus.line_bundles)
                tfprintf("failed: line table length = %d, expected %d\n",
                        tables.line_bundles, ws_tbl_lengths_plus.line_bundles);
        if (tables.mark_bundles != ws_tbl_lengths_plus.mark_bundles)
                tfprintf("failed: marker table length = %d, expected %d\n",
                        tables.mark_bundles, ws_tbl_lengths_plus.mark_bundles);
        if (tables.text_bundles != ws_tbl_lengths_plus.text_bundles)
                tfprintf("failed: text table length = %d, expected %d\n",
                        tables.text_bundles, ws_tbl_lengths_plus.text_bundles);
        if (tables.int_bundles != ws_tbl_lengths_plus.int_bundles)
                tfprintf("failed: interior table length = %d, expected %d\n",
                        tables.int_bundles, ws_tbl_lengths_plus.int_bundles);
        if (tables.edge_bundles != ws_tbl_lengths_plus.edge_bundles)
                tfprintf("failed: edge table length = %d, expected %d\n",
                        tables.edge_bundles, ws_tbl_lengths_plus.edge_bundles);
        if (tables.pat_reps != ws_tbl_lengths_plus.pat_reps)
                tfprintf("failed: pattern table length = %d, expected %d\n",
                        tables.pat_reps, ws_tbl_lengths_plus.pat_reps);
        if (tables.colr_reps != ws_tbl_lengths_plus.colr_reps)
                tfprintf("failed: colour table length = %d, expected %d\n",
                        tables.colr_reps, ws_tbl_lengths_plus.colr_reps);
        if (tables.view_reps != ws_tbl_lengths_plus.view_reps)
                tfprintf("failed: view table length = %d, expected %d\n",
                        tables.view_reps, ws_tbl_lengths_plus.view_reps);
        if (tables.dcue_rep != ws_tbl_lengths_plus.dcue_rep)
                tfprintf("failed: depth cue table length = %d, expected %d\n",
                        tables.dcue_rep, ws_tbl_lengths_plus.dcue_rep);
        if (tables.light_src_rep != ws_tbl_lengths_plus.light_src_rep)
                tfprintf("failed: light source table length = %d, expected %d\n",
                        tables.light_src_rep, ws_tbl_lengths_plus.light_src_rep);
        if (tables.colr_map_rep != ws_tbl_lengths_plus.colr_map_rep)
                tfprintf("failed: colour mapping table length = %d, expected %d\n",
                        tables.colr_map_rep, ws_tbl_lengths_plus.colr_map_rep);
}

/*
 * verify_ws_dynamics_plus
 */
static void
verify_ws_dynamics_plus()
{
        Pdyns_ws_attrs_plus wsmods;
 
        err = BOGUSERR;
        pinq_dyns_ws_attrs_plus(wstype,&err,&wsmods);
        ERROR("pinq_dyns_ws_attrs_plus");
        if (wsmods.light_src_rep != ws_dyn_mods_plus.light_src_rep)
                tfprintf("failed: dynamics light src rep = %d, expected %d\n", 
                        wsmods.light_src_rep, ws_dyn_mods_plus.light_src_rep);
        if (wsmods.dcue_rep != ws_dyn_mods_plus.dcue_rep)
                tfprintf("failed: dynamic dcue rep = %d, expected %d\n",
                        wsmods.dcue_rep, ws_dyn_mods_plus.dcue_rep);
        if (wsmods.colr_map_rep != ws_dyn_mods_plus.colr_map_rep)
                tfprintf("failed: dynamic colour map rep = %d, expected %d\n",
                        wsmods.colr_map_rep, ws_dyn_mods_plus.colr_map_rep);
}
