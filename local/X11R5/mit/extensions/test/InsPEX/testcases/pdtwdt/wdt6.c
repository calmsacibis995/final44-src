
/* $XConsortium: wdt6.c,v 5.1 91/02/16 10:01:20 rws Exp $ */

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
 ## wdt6.c : 
 ## compares the implementation dependent data in workstation description table
 ## against the values returned from inquiries:
 ## Testing PHIGS+'s "inqure predefined xxx representations" and
 ## "inquire list of xxx indices":
 ##
 # Supply a command line argument :
 ## 1: to test pinq_list_light_src_inds, pinq_pred_light_src_rep
 ## 2: to test pinq_list_dcue_inds, pinq_pred_dcue_rep
 ## 3: to test pinq_list_colr_map_inds, pinq_pred_colr_map_rep
 ## 4: to test pinq_pred_line_rep_plus
 ## 5: to test pinq_pred_marker_rep_plus
 ## 6: to test pinq_pred_int_rep_plus
 ## 7: to test pinq_pred_text_rep_plus
 ## 8: to test pinq_pred_edge_rep_plus
 ## 9: to test pinq_pred_pat_rep_plus
 */

#include "phigs/phigs.h"
#include "imath.h"
#include "wdt.h"
#include "logmsg.h"
#include "computils.h"

/* constants */
#define BUFSIZE 1024
#define BOGUSERR -999

static void verify_light_src_rep_idx();
static void verify_depth_cue_rep_idx();
static void verify_cmap_rep_idx();
static void verify_line_rep_idx_plus();
static void verify_marker_rep_idx_plus();
static void verify_text_rep_idx_plus();
static void verify_interior_rep_idx_plus();
static void verify_edge_rep_idx_plus();
static void verify_pattern_rep_idx_plus();

/* commonly used variables */
Pint err;
Pint status;
Pint total;
Pint wstype;         /* specific workstation type */


#define ERROR(string) \
	if (err) { \
		tfprintf("ERROR: %d in %s\n",err,string);\
		return;\
	}

main(argc,argv)
        int argc;
        char **argv;

{
        Pconnid cid;
        char charbuf[BUFSIZE];
        char testdesc[256];
	int i,test;



        sprintf(testdesc,"\"%s\" PHIGS+ ws's pred rep & list of indices inquiries",WSTYPE);
	tbegintest("wdt6",testdesc);
	i_open_phigs((char *)0, PDEF_MEM_SIZE);
	/* ws type dependent procedure to open a ws */
	OPEN_WS1();
	err = BOGUSERR;
        cid = charbuf;
        pinq_ws_conn_type(1,BUFSIZE,&err,&cid,&wstype);
        ERROR("pinq_ws_conn_type");
        if (argc < 2) {
		verify_light_src_rep_idx();
		verify_depth_cue_rep_idx();
		verify_cmap_rep_idx();
		verify_line_rep_idx_plus();
		verify_marker_rep_idx_plus();
		verify_text_rep_idx_plus();
		verify_interior_rep_idx_plus();
		verify_pattern_rep_idx_plus();
        } else
        for (i = 1; i < argc; ++i) {
                test = atoi(argv[i]);
                switch(test) {
                case 1:
		tvprintf(2,"testing pinq_list_light_src_inds, pinq_pred_light_src_rep\n");
			verify_light_src_rep_idx();
			break;
                case 2:
		tvprintf(2,"testing pinq_depth_cue_inds,pinq_pred_depth_cue_rep\n");
			verify_depth_cue_rep_idx();
			break;
                case 3:
		tvprintf(2,"testing pinq_colr_map_inds,pinq_pred_colr_map_rep\n");
			verify_cmap_rep_idx();
			break;
                case 4:
		tvprintf(2,"testing pinq_pred_line_rep_plus\n");
			verify_line_rep_idx_plus();
			break;
                case 5:
		tvprintf(2,"testing pinq_pred_marker_rep_plus\n");
			verify_marker_rep_idx_plus();
			break;
                case 6:
		tvprintf(2,"testing pinq_pred_text_rep_plus\n");
			verify_text_rep_idx_plus();
			break;
                case 7:
		tvprintf(2,"testing pinq_pred_int_rep_plus\n");
			verify_interior_rep_idx_plus();
			break;
                case 8:
		tvprintf(2,"testing pinq_pred_edge_rep_plus\n");
			verify_edge_rep_idx_plus();
			break;
                case 9:
		tvprintf(2,"testing pinq_pred_pat_rep_plus\n");
			verify_pattern_rep_idx_plus();
			break;
                default:
                        tabort("ERROR: invalid argument \"%s\"\n",argv[i]);
		}
	}
	tendtest();
}

/*
 * verify_light_src_rep_idx() 
 */
static void
verify_light_src_rep_idx() 
{
        Plight_src_bundle rep,exprep;
        Pint intbuf[BUFSIZE];
        Pint_list idxlst,expidxlst;
        int i,idx;
 
	INIT_PRED_LIGHT_SRC_REPS();
        idxlst.ints = intbuf;
        err = BOGUSERR;
        pinq_list_light_src_inds(1,BUFSIZE,0,&err,&idxlst,&total);
        ERROR("pinq_list_light_src_inds");
        expidxlst.num_ints = num_pred_light_src_idx;
        expidxlst.ints = list_pred_light_src_idx;
        if (! i_compare_Pint_list(idxlst,expidxlst))
                tfprintf("failed: list of predefined light source indices != expected\n");
        else
          for (i=0; i<num_pred_light_src_idx; ++i) {
                idx = list_pred_light_src_idx[i];
                exprep = pred_light_src_reps[i];
                err = BOGUSERR;
                pinq_pred_light_src_rep(wstype,idx,&err,&rep);
                ERROR("pinq_pred_light_src_rep");
                if (! i_compare_Plight_src_bundle(rep,exprep))
                        tfprintf("failed: index(%d): predefined light_src bundle != expected\n",idx);
          }
}


/*
 * verify_depth_cue_rep_idx() 
 */
static void
verify_depth_cue_rep_idx() 
{
        Pdcue_bundle rep,exprep;
        Pint intbuf[BUFSIZE];
        Pint_list idxlst,expidxlst;
        int i,idx;
 
	INIT_PRED_DEPTH_CUE_REPS();
        idxlst.ints = intbuf;
        err = BOGUSERR;
        pinq_list_dcue_inds(1,BUFSIZE,0,&err,&idxlst,&total);
        ERROR("pinq_list_dcue_inds");
        expidxlst.num_ints = num_pred_depth_cue_idx;
        expidxlst.ints = list_pred_depth_cue_idx;
        if (! i_compare_Pint_list(idxlst,expidxlst))
                tfprintf("failed: list of predefined depth cue indices != expected\n");
        else
          for (i=0; i<num_pred_depth_cue_idx; ++i) {
                idx = list_pred_depth_cue_idx[i];
                exprep = pred_depth_cue_reps[i];
                err = BOGUSERR;
                pinq_pred_dcue_rep(wstype,idx,&err,&rep);
                ERROR("pinq_pred_dcue_rep");
                if (! i_compare_Pdcue_bundle(rep,exprep))
                        tfprintf("failed: index(%d): predefined depth cue bundle != expected\n",idx);
          }
}

/*
 * verify_cmap_rep_idx() 
 */
static void
verify_cmap_rep_idx() 
{
        Pint intbuf[BUFSIZE];
        Pint_list idxlst,expidxlst;
        int i,idx;
	Pstore store;
	Pcolr_map_data *rep_data,*exprep_data;
	Pint rep_method, exprep_method;
 
	INIT_PRED_CMAP_REPS();
        idxlst.ints = intbuf;
        err = BOGUSERR;
        pinq_list_colr_map_inds(1,BUFSIZE,0,&err,&idxlst,&total);
        ERROR("pinq_list_colr_map_inds");
        expidxlst.num_ints = num_pred_cmap_idx;
        expidxlst.ints = list_pred_cmap_idx;
        if (! i_compare_Pint_list(idxlst,expidxlst))
                tfprintf("failed: list of predefined cmap indices != expected\n");
        else {
	  pcreate_store(&err,&store);
	  ERROR("pcreate_store");
          for (i=0; i<num_pred_cmap_idx; ++i) {
                idx = list_pred_cmap_idx[i];
                exprep_method = pred_cmap_reps_method[i];
                err = BOGUSERR;
                pinq_pred_colr_map_rep(wstype,idx,store,&err,
			&rep_method,&rep_data);
                ERROR("pinq_pred_colr_map_rep");
		if (rep_method != exprep_method)
                        tfprintf("failed: index(%d): predefined cmap method = %d, expected %d\n",idx,rep_method,exprep_method);
/*
                exprep_data = &pred_cmap_reps_data[i];
                if (! i_compare_Pcolr_map_data(*rep_data,*exprep_data))
                        tfprintf("failed: index(%d): predefined cmap data != expected\n",idx);
*/
          }
	  pdel_store(store);
	}
}

/*
 * verify_line_rep_idx_plus() 
 */
static void
verify_line_rep_idx_plus() 
{

	Pline_bundle_plus rep,exprep;
	Pint intbuf[BUFSIZE];
	int i,idx;

	INIT_PRED_LINE_REPS_PLUS();
	for (i=0; i<num_pred_line_idx; ++i) {
		idx = list_pred_line_idx_plus[i];
		exprep = pred_line_reps_plus[i];
		err = BOGUSERR;
		pinq_pred_line_rep_plus(wstype,idx,&err,&rep);
		ERROR("pinq_pred_line_rep_plus");
		if (! i_compare_Pline_bundle_plus(rep,exprep))
			tfprintf("failed: index(%d): predefined line bundle plus != expected\n",idx);
	}
}

/*
 * verify_marker_rep_idx_plus() 
 */
static void
verify_marker_rep_idx_plus() 
{

	Pmarker_bundle_plus rep,exprep;
	Pint intbuf[BUFSIZE];
	int i,idx;

	INIT_PRED_MARKER_REPS_PLUS();
	for (i=0; i<num_pred_marker_idx; ++i) {
		idx = list_pred_marker_idx_plus[i];
		exprep = pred_marker_reps_plus[i];
		err = BOGUSERR;
		pinq_pred_marker_rep_plus(wstype,idx,&err,&rep);
		ERROR("pinq_pred_marker_rep_plus");
		if (! i_compare_Pmarker_bundle_plus(rep,exprep))
			tfprintf("failed: index(%d): predefined marker bundle plus != expected\n",idx);
	}
}

/*
 * verify_text_rep_idx_plus() 
 */
static void
verify_text_rep_idx_plus() 
{

	Ptext_bundle_plus rep,exprep;
	Pint intbuf[BUFSIZE];
	int i,idx;

	INIT_PRED_TEXT_REPS_PLUS();
	for (i=0; i<num_pred_text_idx; ++i) {
		idx = list_pred_text_idx_plus[i];
		exprep = pred_text_reps_plus[i];
		err = BOGUSERR;
		pinq_pred_text_rep_plus(wstype,idx,&err,&rep);
		ERROR("pinq_pred_text_rep_plus");
		if (! i_compare_Ptext_bundle_plus(rep,exprep))
			tfprintf("failed: index(%d): predefined text bundle plus != expected\n",idx);
  	}
}

/*
 * verify_edge_rep_idx_plus() 
 */
static void
verify_edge_rep_idx_plus() 
{

	Pedge_bundle_plus rep,exprep;
	Pint intbuf[BUFSIZE];
	int i,idx;

	INIT_PRED_EDGE_REPS_PLUS();
	for (i=0; i<num_pred_edge_idx; ++i) {
		idx = list_pred_edge_idx_plus[i];
		exprep = pred_edge_reps_plus[i];
		err = BOGUSERR;
		pinq_pred_edge_rep_plus(wstype,idx,&err,&rep);
		ERROR("pinq_pred_edge_rep_plus");
		if (! i_compare_Pedge_bundle_plus(rep,exprep))
			tfprintf("failed: index(%d): predefined edge bundle plus != expected\n",idx);
	}
}

/*
 * verify_interior_rep_idx_plus() 
 */
static void
verify_interior_rep_idx_plus() 
{

	Pint_bundle_plus rep,exprep;
	Pint intbuf[BUFSIZE];
	int i,idx;

	INIT_PRED_INTERIOR_REPS_PLUS();
	for (i=0; i<num_pred_interior_idx; ++i) {
		idx = list_pred_interior_idx_plus[i];
		exprep = pred_interior_reps_plus[i];
		err = BOGUSERR;
		pinq_pred_int_rep_plus(wstype,idx,&err,&rep);
		ERROR("pinq_pred_int_rep_plus");
		if (! i_compare_Pint_bundle_plus(rep,exprep))
			tfprintf("failed: index(%d): predefined interior bundle plus != expected\n",idx);
	}
}

/*
 * verify_pattern_rep_idx_plus() 
 */
static void
verify_pattern_rep_idx_plus() 
{

	Ppat_rep_plus rep,exprep;
	Pint intbuf[BUFSIZE];
	int i,idx;
	Pstore store;

	INIT_PRED_PATTERN_REPS_PLUS();
	pcreate_store(&err,&store);
	ERROR("pcreate_store");
	for (i=0; i<num_pred_pattern_idx; ++i) {
		idx = list_pred_pattern_idx_plus[i];
		exprep = pred_pattern_reps_plus[i];
		err = BOGUSERR;
		pinq_pred_pat_rep_plus(wstype,idx,store,&err,&rep);
		ERROR("pinq_pred_pat_rep_plus");
		if (! i_compare_Ppat_rep_plus(rep,exprep))
			tfprintf("failed: index(%d): predefined pattern bundle plus != expected\n",idx);
	}
	pdel_store(store);
}

