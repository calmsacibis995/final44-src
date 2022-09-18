
/* $XConsortium: wdt3.c,v 5.2 91/03/21 15:39:29 hersh Exp $ */

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
 ## wdt3.c : 
 ## compares the implementation dependent data in workstation description table
 ## against the values returned from inquiries.
 ## Testing miscellaneous workstation dependent inquires:
 ##
 #  supplying command argument:
 ## 1: to test pinq_ws_conn_type
 ## 2: to test pinq_ws_cat, 
 ## 3: to test pinq_ws_class
 ## 4: to test pinq_ws_st_table
 ## 5: to test pinqdisplayspacesize,
 ## 6: to test pinqdisplayspacesize3
 ## 7: to test pinq_dyns_ws_attrs 
 ## 8: to test pinq_dyns_structs
 ## 9: to test pinq_num_disp_pris
 ## 10:to test pinq_def_disp_upd_st
 ## 11:to test pinq_gdp, pinq_list_avail_gdp
 ## 12:to test pinq_gdp3, pinq_list_avail_gdp3
 ## 13:to test pinq_list_avail_gse
 */

#include "phigs/phigs.h"
#include "imath.h"
#include "wdt.h"
#include "logmsg.h"

/* constants */
#define BUFSIZE 1024
#define BOGUSERR -999

static void verify_ws_conn_type();
static void verify_ws_cat();
static void verify_ws_class();
static void verify_ws_st_table();
static void verify_disp_sp_size();
static void verify_disp_sp_size3();
static void verify_dyn_ws_attr();
static void verify_dyn_struct();
static void verify_num_disp_pri();
static void verify_def_disp_upd_st();
static void verify_gdp();
static void verify_gdp3();
static void verify_avail_gse();

/* commonly used variables */
Pint err;
Pint status;
Pint total;
Pint wstype;		/* specific workstation type */

#define ERROR(string) \
	if (err) { \
		tfprintf("ERROR: %d in %s\n", err,string);\
		return;\
	}

main(argc,argv)
        int argc;
        char **argv;
{
	Pconnid connid;
        char testdesc[256];
	int i, test;
	char charbuf[BUFSIZE];

        sprintf(testdesc,"\"%s\" ws miscellaneous inquires",WSTYPE);
        tbegintest("wdt3",testdesc);

	i_open_phigs((char *)0, PDEF_MEM_SIZE);
	/* ws type dependent procedure to open a ws */
	OPEN_WS1();
        err = BOGUSERR;
        connid = charbuf;
        pinq_ws_conn_type(1,BUFSIZE,&err,&connid,&wstype);
        ERROR("pinq_ws_conn_type");
	if (argc < 2) {
		verify_ws_conn_type();
		verify_ws_cat();
		verify_ws_class();
		verify_ws_st_table();
		verify_disp_sp_size();
		verify_disp_sp_size3();
		verify_dyn_ws_attr();
		verify_dyn_struct();
		verify_num_disp_pri();
		verify_def_disp_upd_st();
		verify_gdp();
		verify_gdp3();
		verify_avail_gse();
        }else
        for (i = 1; i < argc; ++i) {
                test = atoi(argv[i]);
                switch(test) {
                case 1:
			tvprintf(2,"testing pinq_ws_conn_type\n");
			verify_ws_conn_type();
			break;
                case 2:
			tvprintf(2,"testing pinq_ws_cat\n");
			verify_ws_cat();
			break;
                case 3:
			tvprintf(2,"testing pinq_ws_class\n");
			verify_ws_class();
			break;
                case 4:
			tvprintf(2,"testing pinq_ws_st_table\n");
			verify_ws_st_table();
			break;
                case 5:
			tvprintf(2,"testing pinqdisplayspacesize,\n");
			verify_disp_sp_size();
			break;
                case 6:
			tvprintf(2,"testing pinqdisplayspacesize3\n");
			verify_disp_sp_size3();
			break;
                case 7:
			tvprintf(2,"testing pinq_dyns_ws_attrs\n");
			verify_dyn_ws_attr();
			break;
                case 8:
			tvprintf(2,"testing pinq_dyns_structs\n");
			verify_dyn_struct();
			break;
                case 9:
			tvprintf(2,"testing pinq_num_disp_pris\n");
			verify_num_disp_pri();
			break;
                case 10:
			tvprintf(2,"testing pinq_def_disp_upd_st\n");
			verify_def_disp_upd_st();
			break;
                case 11:
			tvprintf(2,"testing pinq_gdp, pinq_list_avail_gdp\n");
			verify_gdp();
			break;
                case 12:
			tvprintf(2,"testing pinq_gdp3, pinq_list_avail_gdp3\n");
			verify_gdp3();
			break;
                case 13:
			tvprintf(2,"testing pinq_list_avail_gse\n");
			verify_avail_gse();
			break;
                default:
                        tabort("ERROR: invalid argument \"%s\"\n",argv[i]);
		}
	}
	tendtest();
}

/*
 * verify_ws_conn_type()
 */
static void
verify_ws_conn_type()
{

        Pconnid cid;

        err = BOGUSERR;
        pinq_ws_conn_type(1,BUFSIZE,&err,&cid,&wstype);
        ERROR("pinq_ws_conn_type");
        if (cid != ws_connid)
                tfprintf("failed: workstation connection id=%d, expected %d\n",
                       cid,ws_connid);
}

/*
 * verify_ws_cat
 */
static void
verify_ws_cat() 
{

	Pws_cat cat;

	err = BOGUSERR;
	pinq_ws_cat(wstype,&err,&cat);
	ERROR("pinq_ws_category");
	if (cat != wscat) 
		tfprintf("failed: workstation category = %d, expected %d\n",
			cat, wscat);
}

/*
 * verify_ws_class
 */
static void
verify_ws_class() 
{

	Pws_class class;

	err = BOGUSERR;
	pinq_ws_class(wstype,&err,&class);
	ERROR("pinq_ws_class");
	if (class != wsclass) 
		tfprintf("failed: workstation classification = %d, expected %d\n",
			class, wsclass);
}

/*
 * verify_def_disp_upd_st
 */
static void
verify_def_disp_upd_st() 
{

	Pdefer_mode defer_mode;
	Pmod_mode mod_mode;

	err = BOGUSERR;
	pinq_def_disp_upd_st(wstype,&err,&defer_mode,&mod_mode);
	ERROR("pinq_def_disp_upd_st");
	if (def_defer_mode != defer_mode) 
		tfprintf("failed: default display deferral mode = %d, expected %d\n",
			defer_mode,def_defer_mode );
	if (def_mod_mode != mod_mode) 
		tfprintf("failed: default display modification mode = %d, expected %d\n",
			mod_mode,def_mod_mode);
}

/*
 * verify_avail_gse
 */
static void
verify_avail_gse() 
{

	Pint_list gse,expgse;

	err = BOGUSERR;
	pinq_list_avail_gse(wstype,BUFSIZE,0,&err,&gse,&total);
	ERROR("pinq_list_avail_gse");
	expgse.num_ints = num_gse;
	expgse.ints = list_gse;
	if (! i_compare_Pint_list(gse,expgse))
		tfprintf("failed: list of available gse != expected \n");
}


/*
 * verify_gdp
 */
static void
verify_gdp() 
{

	Pint_list gdp,expgdp;
	Pint intbuf[BUFSIZE];
	Pattrs attr[5];
	int i,gdpid,num;

	gdp.ints = intbuf;
	err = BOGUSERR;
	pinq_list_avail_gdp(wstype,BUFSIZE,0,&err,&gdp,&total);
	ERROR("pinq_list_avail_gdp");
	expgdp.num_ints = num_gdp;
	expgdp.ints = list_gdp;
	if (! i_compare_Pint_list(gdp,expgdp))
		tfprintf("failed: available list of gdp != expected \n");
	else 
	  for (i=0; i<num_gdp; ++i) {
		err = BOGUSERR;
		gdpid = list_gdp[i];
		pinq_gdp(wstype,gdpid,&err,&num,attr);
		if (num != list_gdp_num_attrs[i])
			tfprintf("failed: gdp id: %d, # of attributes = %d, expected %d\n",gdpid,num,list_gdp_num_attrs[i]);
		else {
			if (! i_compare_Pattrs_array(num,attr,list_gdp_attrs[i]))
				tfprintf("failed: gdp id: %d, list of attributes != expected \n",gdpid);
		}
	  }
}

/*
 * verify_gdp3
 */
static void
verify_gdp3() 
{

	Pint_list gdp3,expgdp3;
	Pint intbuf[BUFSIZE];
	Pattrs attr[5];
	int i,gdp3id,num;

	gdp3.ints = intbuf;
	err = BOGUSERR;
	pinq_list_avail_gdp3(wstype,BUFSIZE,0,&err,&gdp3,&total);
	ERROR("pinq_list_avail_gdp3");
	expgdp3.num_ints = num_gdp3;
	expgdp3.ints = list_gdp3;
	if (! i_compare_Pint_list(gdp3,expgdp3))
		tfprintf("failed: available list of gdp3 != expected \n");
	else 
	  for (i=0; i<num_gdp3; ++i) {
		err = BOGUSERR;
		gdp3id = list_gdp3[i];
		pinq_gdp3(wstype,gdp3id,&err,&num,attr);
		if (num != list_gdp3_num_attrs[i])
			tfprintf("failed: gdp3 id: %d, # of attributes = %d, expected %d\n",gdp3id,num,list_gdp3_num_attrs[i]);
		else {
			if (! i_compare_Pattrs_array(num,attr, list_gdp_attrs[i]))
				tfprintf("failed: gdp3 id: %d, list of attributes != expected \n",gdp3id);
		}
	  }
}

/*
 * verify_num_disp_pri
 */
static void
verify_num_disp_pri() 
{
	Pint num;

	err = BOGUSERR;
	pinq_num_disp_pris(wstype,&err,&num);
	ERROR("pinq_num_disp_pris");
	if (num != num_display_pri) 
		tfprintf("failed: # of display priorities = %d, expected %d\n",
			num, num_display_pri);
}

/*
 * verify_ws_st_table
 */
static void
verify_ws_st_table() 
{
	Pws_st_tables tables;

	err = BOGUSERR;
	pinq_ws_st_table(wstype,&err,&tables);
	ERROR("pinq_ws_st_table");
	if (tables.line_bundles != ws_tbl_lengths.line_bundles) 
		tfprintf("failed: line table length = %d, expected %d\n",
			tables.line_bundles, ws_tbl_lengths.line_bundles);
	if (tables.mark_bundles != ws_tbl_lengths.mark_bundles) 
		tfprintf("failed: marker table length = %d, expected %d\n",
			tables.mark_bundles, ws_tbl_lengths.mark_bundles);
	if (tables.text_bundles != ws_tbl_lengths.text_bundles) 
		tfprintf("failed: text table length = %d, expected %d\n",
			tables.text_bundles, ws_tbl_lengths.text_bundles);
	if (tables.int_bundles != ws_tbl_lengths.int_bundles) 
		tfprintf("failed: interior table length = %d, expected %d\n",
			tables.int_bundles, ws_tbl_lengths.int_bundles);
	if (tables.edge_bundles != ws_tbl_lengths.edge_bundles) 
		tfprintf("failed: edge table length = %d, expected %d\n",
			tables.edge_bundles, ws_tbl_lengths.edge_bundles);
	if (tables.pat_reps != ws_tbl_lengths.pat_reps) 
		tfprintf("failed: pattern table length = %d, expected %d\n",
			tables.pat_reps, ws_tbl_lengths.pat_reps);
	if (tables.colr_reps != ws_tbl_lengths.colr_reps) 
		tfprintf("failed: colour table length = %d, expected %d\n",
			tables.colr_reps, ws_tbl_lengths.colr_reps);
	if (tables.view_reps != ws_tbl_lengths.view_reps) 
		tfprintf("failed: view table length = %d, expected %d\n",
			tables.view_reps, ws_tbl_lengths.view_reps);
}

/*
 * verify_dyn_ws_attr
 */
static void
verify_dyn_ws_attr() 
{
	Pdyns_ws_attrs wsmods;

	err = BOGUSERR;
	pinq_dyns_ws_attrs(wstype,&err,&wsmods);
	ERROR("pinq_dyns_ws_attrs");
	if (wsmods.line_bundle != ws_dyn_mods.line_bundle) 
		tfprintf("failed: dynamic modification line = %d, expected %d\n",
			wsmods.line_bundle, ws_dyn_mods.line_bundle);
	if (wsmods.marker_bundle != ws_dyn_mods.marker_bundle) 
		tfprintf("failed: dynamic modification for marker rep = %d, expected %d\n",
			wsmods.marker_bundle, ws_dyn_mods.marker_bundle);
	if (wsmods.text_bundle != ws_dyn_mods.text_bundle) 
		tfprintf("failed: dynamic modification for text rep = %d, expected %d\n",
			wsmods.text_bundle, ws_dyn_mods.text_bundle);
	if (wsmods.int_bundle != ws_dyn_mods.int_bundle) 
		tfprintf("failed: dynamic modification for interior rep = %d, expected %d\n",
			wsmods.int_bundle, ws_dyn_mods.int_bundle);
	if (wsmods.edge_bundle != ws_dyn_mods.edge_bundle) 
		tfprintf("failed: dynamic modification for edge rep = %d, expected %d\n",
			wsmods.edge_bundle, ws_dyn_mods.edge_bundle);
	if (wsmods.pat_rep != ws_dyn_mods.pat_rep) 
		tfprintf("failed: dynamic modification for pattern rep = %d, expected %d\n",
			wsmods.pat_rep, ws_dyn_mods.pat_rep);
	if (wsmods.colr_rep != ws_dyn_mods.colr_rep) 
		tfprintf("failed: dynamic modification for colour rep = %d, expected %d\n",
			wsmods.colr_rep, ws_dyn_mods.colr_rep);
	if (wsmods.view_rep != ws_dyn_mods.view_rep) 
		tfprintf("failed: dynamic modification for view rep = %d, expected %d\n",
			wsmods.view_rep, ws_dyn_mods.view_rep);
	if (wsmods.ws_tran != ws_dyn_mods.ws_tran) 
		tfprintf("failed: dynamic modification for workstation xform rep = %d, expected %d\n",
			wsmods.ws_tran, ws_dyn_mods.ws_tran);
	if (wsmods.highl_filter != ws_dyn_mods.highl_filter) 
		tfprintf("failed: dynamic modification for highlight filter = %d, expected %d\n",
			wsmods.highl_filter, ws_dyn_mods.highl_filter);
	if (wsmods.invis_filter != ws_dyn_mods.invis_filter) 
		tfprintf("failed: dynamic modification for invisibility filter = %d, expected %d\n",
			wsmods.invis_filter, ws_dyn_mods.invis_filter);
	if (wsmods.hlhsr_mode != ws_dyn_mods.hlhsr_mode) 
		tfprintf("failed: dynamic modification for HLHSR mode = %d, expected %d\n",
			wsmods.hlhsr_mode, ws_dyn_mods.hlhsr_mode);
}

/*
 * verify_dyn_struct
 */
static void
verify_dyn_struct() 
{
	Pdyns_structs structmods;

	err = BOGUSERR;
	pinq_dyns_structs(wstype,&err,&structmods);
	ERROR("pinq_dyns_structs");
	if (structmods.content != str_dyn_mods.content) 
		tfprintf("failed: dynamic modification structure content = %d, expected %d\n",
			structmods.content, str_dyn_mods.content);
	if (structmods.post != str_dyn_mods.post) 
		tfprintf("failed: dynamic modification for post structure = %d, expected %d\n",
			structmods.post, str_dyn_mods.post);
	if (structmods.unpost != str_dyn_mods.unpost) 
		tfprintf("failed: dynamic modification for unpost structure = %d, expected %d\n",
			structmods.unpost, str_dyn_mods.unpost);
	if (structmods.del != str_dyn_mods.del) 
		tfprintf("failed: dynamic modification for delete structure = %d, expected %d\n",
			structmods.del, str_dyn_mods.del);
	if (structmods.ref != str_dyn_mods.ref) 
		tfprintf("failed: dynamic modification for structure reference = %d, expected %d\n",
			structmods.ref, str_dyn_mods.ref);
}

/*
 * verify_disp_sp_size
 */
static void
verify_disp_sp_size() 
{

	Pdisp_space_size size;

	err = BOGUSERR;
	pinq_disp_space_size(wstype,&err,&size);
	ERROR("pinq_disp_space_size");

	if (size.dc_units != device_coor_units) 
		tfprintf("failed: device coordinates units= %d, expected %d\n",
			size.dc_units, device_coor_units);

	if (! i_compare_Pvec(size.size_dc,device_max_disp_size))
		tfprintf("failed: max display size in device coordinates != expected\n");
	if (size.size_raster.size_x != raster_max_disp_size.size_x || 
		size.size_raster.size_y != raster_max_disp_size.size_y )
		tfprintf("failed: max display size in raster coordinates= (%d,%d), expected (%d,%d)\n",
			size.size_raster.size_x, size.size_raster.size_y,
			raster_max_disp_size.size_x,raster_max_disp_size.size_y);
}
/*
 * verify_disp_sp_size3
 */
static void
verify_disp_sp_size3() 
{

	Pdisp_space_size3 size;

	err = BOGUSERR;
	pinq_disp_space_size3(wstype,&err,&size);
	ERROR("pinq_disp_space_size3");

	if (size.dc_units != device_coor_units3) 
		tfprintf("failed: device coordinates units3= %d, expected %d\n",
			size.dc_units, device_coor_units3);

	if (! i_compare_Pvec3(size.size_dc,device_max_disp_size3))
		tfprintf("failed: max display size3 in device coordinates != expected\n");
	if (size.size_raster.size_x != raster_max_disp_size3.size_x || 
		size.size_raster.size_y != raster_max_disp_size3.size_y ||
		size.size_raster.size_z != raster_max_disp_size3.size_z )
		tfprintf("failed: max display size3 in raster coordinates= (%d,%d,%d), expected (%d,%d,%d)\n",
			size.size_raster.size_x, size.size_raster.size_y, 
			size.size_raster.size_z,
			raster_max_disp_size3.size_x,raster_max_disp_size3.size_y,
			raster_max_disp_size3.size_z);
}

