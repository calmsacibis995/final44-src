
/* $XConsortium: wdt2.c,v 5.1 91/02/16 10:01:17 rws Exp $ */

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
 ## wdt2.c : 
 ## compares the implementation dependent data in workstation description table
 ## against the values returned from inquiries:
 ## Testing "inqure predefined xxx representations" and
 ## "inquire list of xxx indices":
 ##
 # Supply a command line argument :
 ## 1: to test pinq_list_view_inds, pinq_pred_view_rep
 ## 2: to test pinq_list_line_inds, pinq_pred_line_rep
 ## 3: to test pinq_list_marker_inds, pinq_pred_marker_rep
 ## 4: to test pinq_list_text_inds, pinq_pred_text_rep
 ## 5: to test pinq_list_int_inds, pinq_pred_int_rep
 ## 6: to test pinq_list_edge_inds, pinq_pred_edge_rep
 ## 7: to test pinq_list_pat_inds, pinq_pred_pat_rep
 ## 8: to test pinq_list_colr_inds, pinq_pred_colr_rep
 */

#include "phigs/phigs.h"
#include "imath.h"
#include "wdt.h"
#include "logmsg.h"
#include "computils.h"

/* constants */
#define BUFSIZE 1024
#define BOGUSERR -999

static void verify_view_rep_idx();
static void verify_line_rep_idx();
static void verify_marker_rep_idx();
static void verify_text_rep_idx();
static void verify_interior_rep_idx();
static void verify_edge_rep_idx();
static void verify_pattern_rep_idx();
static void verify_colour_rep_idx();

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



        sprintf(testdesc,"\"%s\" ws's pred rep & list of indices inquiries",WSTYPE);
	tbegintest("wdt2",testdesc);
	i_open_phigs((char *)0, PDEF_MEM_SIZE);
	/* ws type dependent procedure to open a ws */
	OPEN_WS1();
	err = BOGUSERR;
        cid = charbuf;
        pinq_ws_conn_type(1,BUFSIZE,&err,&cid,&wstype);
        ERROR("pinq_ws_conn_type");
        if (argc < 2) {
		verify_view_rep_idx();
		verify_line_rep_idx();
		verify_marker_rep_idx();
		verify_text_rep_idx();
		verify_interior_rep_idx();
		verify_pattern_rep_idx();
		verify_colour_rep_idx();
        } else
        for (i = 1; i < argc; ++i) {
                test = atoi(argv[i]);
                switch(test) {
                case 1:
		tvprintf(2,"testing pinq_list_view_inds, pinq_pred_view_rep\n");
			verify_view_rep_idx();
			break;
                case 2:
		tvprintf(2,"testing pinq_list_line_inds, pinq_pred_line_rep\n");
			verify_line_rep_idx();
			break;
                case 3:
		tvprintf(2,"testing pinq_list_marker_inds, pinq_pred_marker_rep\n");
			verify_marker_rep_idx();
			break;
                case 4:
		tvprintf(2,"testing pinq_list_text_inds, pinq_pred_text_rep\n");
			verify_text_rep_idx();
			break;
                case 5:
		tvprintf(2,"testing pinq_list_int_inds, pinq_pred_int_rep\n");
			verify_interior_rep_idx();
			break;
                case 6:
		tvprintf(2,"testing pinq_list_edge_inds, pinq_pred_edge_rep\n");
			verify_edge_rep_idx();
			break;
                case 7:
		tvprintf(2,"testing pinq_list_pat_inds, pinq_pred_pat_rep\n");
			verify_pattern_rep_idx();
			break;
                case 8:
		tvprintf(2,"testing pinq_list_colr_inds, pinq_pred_colr_rep\n");
			verify_colour_rep_idx();
			break;
                default:
                        tabort("ERROR: invalid argument \"%s\"\n",argv[i]);
		}
	}
	tendtest();
}

/*
 * verify_view_rep_idx() 
 */
static void
verify_view_rep_idx() 
{

	Pview_rep3 rep,exprep;
	Pint intbuf[BUFSIZE];
	Pint_list idxlst,expidxlst;
	int i,idx;

	idxlst.ints = intbuf;
	err = BOGUSERR;
	pinq_list_view_inds(1,BUFSIZE,0,&err,&idxlst,&total);
	ERROR("pinq_list_view_inds");
	expidxlst.num_ints = num_pred_view_idx;
	expidxlst.ints = list_pred_view_idx;
	if (! i_compare_Pint_list(idxlst,expidxlst))
		tfprintf("failed: list of predefined view indices != expected\n");
	else
	  for (i=0; i<num_pred_view_idx; ++i) {
		idx = list_pred_view_idx[i];
		exprep = pred_view_reps[i];
		err = BOGUSERR;
		pinq_pred_view_rep(wstype,idx,&err,&rep);
		ERROR("pinq_pred_view_rep");
		if (! i_compare_Pview_rep3(rep,exprep))
			tfprintf("failed: index(%d): predefined view representation3 != expected\n",idx);
	  }
}

/*
 * verify_line_rep_idx() 
 */
static void
verify_line_rep_idx() 
{

	Pline_bundle rep,exprep;
	Pint intbuf[BUFSIZE];
	Pint_list idxlst,expidxlst;
	int i,idx;

	idxlst.ints = intbuf;
	err = BOGUSERR;
	pinq_list_line_inds(1,BUFSIZE,0,&err,&idxlst,&total);
	ERROR("pinq_list_line_inds");
	expidxlst.num_ints = num_pred_line_idx;
	expidxlst.ints = list_pred_line_idx;
	if (! i_compare_Pint_list(idxlst,expidxlst))
		tfprintf("failed: list of predefined line indices != expected\n");
	else
	  for (i=0; i<num_pred_line_idx; ++i) {
		idx = list_pred_line_idx[i];
		exprep = pred_line_reps[i];
		err = BOGUSERR;
		pinq_pred_line_rep(wstype,idx,&err,&rep);
		ERROR("pinq_pred_line_rep");
		if (! i_compare_Pline_bundle(rep,exprep))
			tfprintf("failed: index(%d): predefined line bundle != expected\n",idx);
	  }
}

/*
 * verify_marker_rep_idx() 
 */
static void
verify_marker_rep_idx() 
{

	Pmarker_bundle rep,exprep;
	Pint intbuf[BUFSIZE];
	Pint_list idxlst,expidxlst;
	int i,idx;

	idxlst.ints = intbuf;
	err = BOGUSERR;
	pinq_list_marker_inds(1,BUFSIZE,0,&err,&idxlst,&total);
	ERROR("pinq_list_marker_inds");
	expidxlst.num_ints = num_pred_marker_idx;
	expidxlst.ints = list_pred_marker_idx;
	if (! i_compare_Pint_list(idxlst,expidxlst))
		tfprintf("failed: list of predefined marker indices != expected\n");
	else
	  for (i=0; i<num_pred_marker_idx; ++i) {
		idx = list_pred_marker_idx[i];
		exprep = pred_marker_reps[i];
		err = BOGUSERR;
		pinq_pred_marker_rep(wstype,idx,&err,&rep);
		ERROR("pinq_pred_marker_rep");
		if (! i_compare_Pmarker_bundle(rep,exprep))
			tfprintf("failed: index(%d): predefined marker bundle != expected\n",idx);
	  }
}

/*
 * verify_text_rep_idx() 
 */
static void
verify_text_rep_idx() 
{

	Ptext_bundle rep,exprep;
	Pint intbuf[BUFSIZE];
	Pint_list idxlst,expidxlst;
	int i,idx;

	idxlst.ints = intbuf;
	err = BOGUSERR;
	pinq_list_text_inds(1,BUFSIZE,0,&err,&idxlst,&total);
	ERROR("pinq_list_text_inds");
	expidxlst.num_ints = num_pred_text_idx;
	expidxlst.ints = list_pred_text_idx;
	if (! i_compare_Pint_list(idxlst,expidxlst))
		tfprintf("failed: list of predefined text indices != expected\n");
	else
	  for (i=0; i<num_pred_text_idx; ++i) {
		idx = list_pred_text_idx[i];
		exprep = pred_text_reps[i];
		err = BOGUSERR;
		pinq_pred_text_rep(wstype,idx,&err,&rep);
		ERROR("pinq_pred_text_rep");
		if (! i_compare_Ptext_bundle(rep,exprep))
			tfprintf("failed: index(%d): predefined text bundle != expected\n",idx);
	  }
}

/*
 * verify_edge_rep_idx() 
 */
static void
verify_edge_rep_idx() 
{

	Pedge_bundle rep,exprep;
	Pint intbuf[BUFSIZE];
	Pint_list idxlst,expidxlst;
	int i,idx;

	idxlst.ints = intbuf;
	err = BOGUSERR;
	pinq_list_edge_inds(1,BUFSIZE,0,&err,&idxlst,&total);
	ERROR("pinq_list_edge_inds");
	expidxlst.num_ints = num_pred_edge_idx;
	expidxlst.ints = list_pred_edge_idx;
	if (! i_compare_Pint_list(idxlst,expidxlst))
		tfprintf("failed: list of predefined edge indices != expected\n");
	else
	  for (i=0; i<num_pred_edge_idx; ++i) {
		idx = list_pred_edge_idx[i];
		exprep = pred_edge_reps[i];
		err = BOGUSERR;
		pinq_pred_edge_rep(wstype,idx,&err,&rep);
		ERROR("pinq_pred_edge_rep");
		if (! i_compare_Pedge_bundle(rep,exprep))
			tfprintf("failed: index(%d): predefined edge bundle != expected\n",idx);
	  }
}

/*
 * verify_interior_rep_idx() 
 */
static void
verify_interior_rep_idx() 
{

	Pint_bundle rep,exprep;
	Pint intbuf[BUFSIZE];
	Pint_list idxlst,expidxlst;
	int i,idx;

	idxlst.ints = intbuf;
	err = BOGUSERR;
	pinq_list_int_inds(1,BUFSIZE,0,&err,&idxlst,&total);
	ERROR("pinq_list_int_inds");
	expidxlst.num_ints = num_pred_interior_idx;
	expidxlst.ints = list_pred_interior_idx;
	if (! i_compare_Pint_list(idxlst,expidxlst))
		tfprintf("failed: list of predefined interior indices != expected\n");
	else
	  for (i=0; i<num_pred_interior_idx; ++i) {
		idx = list_pred_interior_idx[i];
		exprep = pred_interior_reps[i];
		err = BOGUSERR;
		pinq_pred_int_rep(wstype,idx,&err,&rep);
		ERROR("pinq_pred_int_rep");
		if (! i_compare_Pint_bundle(rep,exprep))
			tfprintf("failed: index(%d): predefined interior bundle != expected\n",idx);
	  }
}

/*
 * verify_pattern_rep_idx() 
 */
static void
verify_pattern_rep_idx() 
{

	Ppat_rep rep,exprep;
	Pint intbuf[BUFSIZE];
	Pint_list idxlst,expidxlst;
	int i,idx;
	Pstore store;

	idxlst.ints = intbuf;
	err = BOGUSERR;
	pinq_list_pat_inds(1,BUFSIZE,0,&err,&idxlst,&total);
	ERROR("pinq_list_pat_inds");
	expidxlst.num_ints = num_pred_pattern_idx;
	expidxlst.ints = list_pred_pattern_idx;
	if (! i_compare_Pint_list(idxlst,expidxlst))
		tfprintf("failed: list of predefined pat indices != expected\n");
	else {
	  pcreate_store(&err,&store);
	  ERROR("pcreate_store");
	  for (i=0; i<num_pred_pattern_idx; ++i) {
		idx = list_pred_pattern_idx[i];
		exprep = pred_pattern_reps[i];
		err = BOGUSERR;
		pinq_pred_pat_rep(wstype,idx,store,&err,&rep);
		ERROR("pinq_pred_pat_rep");
		if (! i_compare_Ppat_rep(rep,exprep))
			tfprintf("failed: index(%d): predefined pattern bundle != expected\n",idx);
	  }
	  pdel_store(store);
	}
}

/*
 * verify_colour_rep_idx() 
 */
static void
verify_colour_rep_idx() 
{

	Pcolr_rep rep,exprep;
	Pint intbuf[BUFSIZE];
	Pint charbuf[BUFSIZE];
	Pint_list idxlst,expidxlst;
	int i,idx;

	idxlst.ints = intbuf;
	err = BOGUSERR;
	pinq_list_colr_inds(1,BUFSIZE,0,&err,&idxlst,&total);
	ERROR("pinq_list_colr_inds");
	expidxlst.num_ints = num_pred_col_idx;
	expidxlst.ints = list_pred_col_idx;
	if (! i_compare_Pint_list(idxlst,expidxlst))
		tfprintf("failed: list of predefined colour indices != expected\n");
	else
	  for (i=0; i<num_pred_col_idx; ++i) {
		idx = list_pred_col_idx[i];
		exprep.rgb.red = pred_col_reps[i][0];
		exprep.rgb.green = pred_col_reps[i][1];
		exprep.rgb.blue = pred_col_reps[i][2];
		err = BOGUSERR;
		pinq_pred_colr_rep(wstype,idx,&err,&rep);
		ERROR("pinq_pred_colr_rep");
		if (! i_compare_Pcolr_rep(rep,exprep))
			tfprintf("failed: index(%d): predefined colour bundle != expected\n",idx);
	  }
}

