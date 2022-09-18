
/* $XConsortium: wdt1.c,v 5.1 91/02/16 10:01:15 rws Exp $ */

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
 ## wdt1.c : 
 ## compares the implementation dependent data in workstation description table
 ## against the values returned from inquiries:
 ## Testing inqure xxx facilities:
 ##
 # Supplying command argument :
 ## 1: to test pinq_hlhsr_mode_facs, pinq_hlhsr_id_facs 
 ## 2: to test pinq_view_facs 
 ## 3: to test pinq_line_facs
 ## 4: to test pinq_marker_facs
 ## 5: to test pinq_text_facs
 ## 6: to test pinq_anno_facs
 ## 7: to test pinq_int_facs
 ## 8: to test pinq_pat_facs
 ## 9: to test pinq_edge_facs
 ## 10:to test pinq_colr_model_facs
 ## 11:to test pinq_colr_facs
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

static void verify_hlhsr_facilities();
static void verify_view_facilities();
static void verify_line_facilities();
static void verify_marker_facilities();
static void verify_text_facilities();
static void verify_annotation_text_facilities();
static void verify_interior_facilities();
static void verify_pattern_facilities();
static void verify_edge_facilities();
static void verify_colour_model_facilities();
static void verify_colour_facilities();

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



	sprintf(testdesc,"\"%s\" workstation facilities inquiry",WSTYPE); 
	tbegintest("wdt1",testdesc);
	i_open_phigs((char *)0, PDEF_MEM_SIZE);
	/* ws type dependent procedure to open a ws */
	OPEN_WS1()
	err = BOGUSERR;
        cid = charbuf;
        pinq_ws_conn_type(1,BUFSIZE,&err,&cid,&wstype);
        ERROR("pinq_ws_conn_type");

        if (argc < 2) {
		verify_hlhsr_facilities();
		verify_view_facilities();
		verify_line_facilities();
		verify_marker_facilities();
		verify_text_facilities();
		verify_annotation_text_facilities();
		verify_interior_facilities();
		verify_pattern_facilities();
		verify_edge_facilities();
		verify_colour_model_facilities();
		verify_colour_facilities();
        }else
        for (i = 1; i < argc; ++i) {
                test = atoi(argv[i]);
                switch(test) {
                case 1:
  			tvprintf(2,"testing pinq_hlhsr_mode_facs, pinq_hlhsr_id_facs\n");
			verify_hlhsr_facilities();
			break;
                case 2:
			tvprintf(2,"testing pinq_view_facs \n");
			verify_view_facilities();
			break;
                case 3:
  			tvprintf(2,"testing pinq_line_facs\n");
			verify_line_facilities();
			break;
                case 4:
  			tvprintf(2,"testing pinq_marker_facs\n");
			verify_marker_facilities();
			break;
                case 5:
  			tvprintf(2,"testing pinq_text_facs\n");
			verify_text_facilities();
			break;
                case 6:
  			tvprintf(2,"testing pinq_anno_facs\n");
			verify_annotation_text_facilities();
			break;
                case 7:
  			tvprintf(2,"testing pinq_int_facs\n");
			verify_interior_facilities();
			break;
                case 8:
  			tvprintf(2,"testing pinq_pat_facs\n");
			verify_pattern_facilities();
			break;
                case 9:
  			tvprintf(2,"testing pinq_edge_facs\n");
			verify_edge_facilities();
			break;
                case 10:
  			tvprintf(2,"testing pinq_colr_model_facs\n");
			verify_colour_model_facilities();
			break;
                case 11:
  			tvprintf(2,"testing pinq_colr_facs\n");
			verify_colour_facilities();
			break;
                default:
                        tabort("ERROR: invalid argument \"%s\"\n",argv[i]);
		}
	}
	tendtest();
}

/*
 * verify_hlhsr_facilities() 
 * verify the number and list of available hlhsr ids and modes
 */
static void
verify_hlhsr_facilities() 
{

	Pint_list	ids,modes,expids,expmodes;
	Pint intbuf1[BUFSIZE];
	Pint intbuf2[BUFSIZE];
	Pint total_id,total_mode;


	ids.ints = intbuf1;
	modes.ints = intbuf2;
	err = BOGUSERR;
	pinq_hlhsr_mode_facs(wstype,BUFSIZE,0,&err,&modes,&total_mode);
	ERROR("pinq_hlhsr_mode_facs");
	expmodes.num_ints = num_hlhsr_mode;
	expmodes.ints = list_hlhsr_mode;
	if (! i_compare_Pint_list(modes,expmodes))
		tfprintf("failed: list of hlhsr modes != expected\n");

	pinq_hlhsr_id_facs(wstype,BUFSIZE,0,&err,&ids,&total_id);
	ERROR("pinq_hlhsr_mode_facs");
	expids.num_ints = num_hlhsr_id;
	expids.ints = list_hlhsr_id;
	if (! i_compare_Pint_list(ids,expids))
		tfprintf("failed: list of hlhsr ids != expected\n");
}

/*
 * verify_view_facilities() 
 * verify the number of predefined view indices
 */
static void
verify_view_facilities() 
{
	Pint num;

	err = BOGUSERR;
	pinq_view_facs(wstype, &err,&num);
	ERROR("pinq_view_facs");
	if (num != num_pred_view_idx)
		tfprintf("failed: # of predefined view idx = %d, expected %d\n",
			num,num_pred_view_idx);
}

/*
 * verify_line_facilities() 
 * verify the number and list of available line types
 * 	  number of available, nominal, minimum and maximum linewidths
 *        number of predefined polyline indices
 */
static void
verify_line_facilities() 
{

	Pint_list	explinetype;
	Pint intbuf[BUFSIZE];
	Pline_facs lnfacil;

	lnfacil.types.ints = intbuf;
	err = BOGUSERR;
	pinq_line_facs(wstype,BUFSIZE,0,&err,&lnfacil,&total);
	ERROR("pinq_line_facs");

	explinetype.num_ints = num_line_type;
	explinetype.ints = list_line_type;
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
}

/*
 * verify_marker_facilities() 
 * verify the number and list of available marker types
 * 	  number of available, nominal, minimum and maximum marker size
 *        number of predefined marker indices
 */
static void
verify_marker_facilities() 
{

	Pint_list	expmarkertype;
	Pint intbuf[BUFSIZE];
	Pmarker_facs mkfacil;

	mkfacil.types.ints = intbuf;
	err = BOGUSERR;
	pinq_marker_facs(wstype,BUFSIZE,0,&err,&mkfacil,&total);
	ERROR("pinq_marker_facs");

	expmarkertype.num_ints = num_marker_type;
	expmarkertype.ints = list_marker_type;
	if (! i_compare_Pint_list(mkfacil.types,expmarkertype))
		tfprintf("failed: list of marker types != expected\n");

	if (fne( mkfacil.nom_size, nom_marker_size))
		tfprintf("failed: nominal marker width = %.4f, expected %.4f\n",
			mkfacil.nom_size, nom_marker_size);

	if (fne( mkfacil.min_size, min_marker_size))
		tfprintf("failed: minimum marker size = %.4f, expected %.4f\n",
			mkfacil.min_size, min_marker_size);

	if (fne( mkfacil.max_size, max_marker_size))
		tfprintf("failed: maximum marker size = %.4f, expected %.4f\n",
			mkfacil.max_size, max_marker_size);

	if (mkfacil.num_pred_inds != num_pred_marker_idx)
		tfprintf("failed: # of predefined marker idx = %d, expected %d\n",
			mkfacil.num_pred_inds,num_pred_marker_idx);
}

/*
 * verify_text_facilities() 
 * verify the number and list of available text font and precision pairs
 * 	  number of available, minimum and maximum charactor expansion factors
 * 	  number of available, minimum and maximum charactor heights
 *        number of predefined text indices
 */
static void
verify_text_facilities() 
{

	Ptext_font_prec fpbuf[BUFSIZE];
	Ptext_facs txfacil;

	txfacil.font_precs= fpbuf;
	err = BOGUSERR;
	pinq_text_facs(wstype,BUFSIZE,0,&err,&txfacil,&total);
	ERROR("pinq_text_facs");

	if (txfacil.num_font_precs != num_font_precision)
		tfprintf("failed: # of text font, prec pairs=%d, expected %d\n",
			txfacil.num_font_precs, num_font_precision);
	else {
		if (! i_compare_Ptext_font_prec_array(txfacil.num_font_precs,
			txfacil.font_precs,list_font_precision))
		tfprintf("failed: list of text font, prec pairs != expected\n");
	}
	if (txfacil.num_char_hts != num_char_height)
		tfprintf("failed: # of avail char heights = %d, expected %d\n",
			txfacil.num_char_hts, num_char_height);

	if (fne( txfacil.min_char_ht, min_char_height))
		tfprintf("failed: minimum char height = %.4f, expected %.4f\n",
			txfacil.min_char_ht, min_char_height);

	if (fne( txfacil.max_char_ht, max_char_height))
		tfprintf("failed: maximum char height = %.4f, expected %.4f\n",
			txfacil.max_char_ht, max_char_height);

	if (txfacil.num_char_expans != num_char_exp)
		tfprintf("failed: # of avail char exps = %d, expected %d\n",
			txfacil.num_char_expans, num_char_exp);

	if (fne( txfacil.min_char_expan, min_char_exp))
		tfprintf("failed: minimum char exp = %.4f, expected %.4f\n",
			txfacil.min_char_expan, min_char_exp);

	if (fne( txfacil.max_char_expan, max_char_exp))
		tfprintf("failed: maximum char exp = %.4f, expected %.4f\n",
			txfacil.max_char_expan, max_char_exp);

	if (txfacil.num_pred_inds != num_pred_text_idx)
		tfprintf("failed: # of predefined text idx = %d, expected %d\n",
			txfacil.num_pred_inds,num_pred_text_idx);
}

/*
 * verify_annotation_text_facilities() 
 * verify the number and list of available annotation styles
 */
static void
verify_annotation_text_facilities() 
{

	Pint_list	style,expstyle;
	Pint intbuf[BUFSIZE];
	Pint numht;
	Pfloat minht,maxht;

	style.ints = intbuf;
	err = BOGUSERR;
	pinq_anno_facs(wstype,BUFSIZE,0,&err,&style,&total,&numht,&minht,&maxht);
	ERROR("pinq_anno_facs");

	expstyle.num_ints = num_anno_style;
	expstyle.ints = list_anno_style;
	if (! i_compare_Pint_list(style,expstyle))
		tfprintf("failed: list of annotation styles != expected\n");
	if (numht != num_anno_char_height)
		tfprintf("failed: # of avail annotation char heights = %d, expected %d\n",
			numht, num_anno_char_height);
	if (fne( minht, min_anno_char_height))
		tfprintf("failed: minimum annotation char height = %.4f, expected %.4f\n",
			minht, min_anno_char_height);
	if (fne( maxht, max_anno_char_height))
		tfprintf("failed: maximum annotation char height = %.4f, expected %.4f\n",
			maxht, max_anno_char_height);
}

/*
 * verify_interior_facilities() 
 * verify the number and list of available interior types
 *        number and list of available hatch styles
 *        number of predefined interior indices
 */
static void
verify_interior_facilities() 
{

	Pint_list	exphatchstyle;
	Pint intbuf[BUFSIZE];
	Pint_facs interfacil;
	Pint total_type,total_style;
	Pint_style interstyle[BUFSIZE];

	interfacil.hatch_styles.ints = intbuf;
	memcpy((char*)interfacil.int_styles,(char*)interstyle,
		sizeof(Pint_style) * 5);
	err = BOGUSERR;
	pinq_int_facs(wstype,BUFSIZE,0,&err,&interfacil,&total_style);
	ERROR("pinq_int_facs");

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

	if (interfacil.num_pred_inds != num_pred_interior_idx)
		tfprintf("failed: # of predefined interior idx = %d, expected %d\n",
			interfacil.num_pred_inds,num_pred_interior_idx);
}

/*
 * verify_pattern_facilities() 
 * Verify the number of predefined pattern indices
 */
static void
verify_pattern_facilities() 
{

	Pint num;

	err = BOGUSERR;
	pinq_pat_facs(wstype,&err,&num);
	ERROR("pinq_pat_facs");
	if (num != num_pred_pattern_idx)
		tfprintf("failed: # of predefined pattern idx=%d,expected %d\n",
			num,num_pred_pattern_idx);
}

/*
 * verify_edge_facilities() 
 * verify the number and list of available edge types
 * 	  number of available, nominal, minimum and maximum edgewidths
 *        number of predefined edge indices
 */
static void
verify_edge_facilities() 
{

	Pint_list	expedgetype;
	Pint intbuf[BUFSIZE];
	Pedge_facs edgefacil;

	edgefacil.types.ints = intbuf;
	err = BOGUSERR;
	pinq_edge_facs(wstype,BUFSIZE,0,&err,&edgefacil,&total);
	ERROR("pinq_edge_facs");

	expedgetype.num_ints = num_edge_type;
	expedgetype.ints = list_edge_type;
	if (! i_compare_Pint_list(edgefacil.types,expedgetype))
		tfprintf("failed: list of edge types != expected\n");

	if (fne( edgefacil.nom_width, nom_edge_width))
		tfprintf("failed: nominal edge width = %.4f, expected %.4f\n",
			edgefacil.nom_width, nom_edge_width);

	if (fne( edgefacil.min_width, min_edge_width))
		tfprintf("failed: minimum edge width = %.4f, expected %.4f\n",
			edgefacil.min_width, min_edge_width);

	if (fne( edgefacil.max_width, max_edge_width))
		tfprintf("failed: maximum edge width = %.4f, expected %.4f\n",
			edgefacil.max_width, max_edge_width);

	if (edgefacil.num_pred_inds != num_pred_edge_idx)
		tfprintf("failed: # of predefined edge idx = %d, expected %d\n",
			edgefacil.num_pred_inds,num_pred_edge_idx);
}

/*
 * verify_colour_model_facilities() 
 * verify the number and list of available colour model 
 */
static void
verify_colour_model_facilities() 
{

	Pint_list	model,expmodel;
	Pint intbuf[BUFSIZE];
	Pint defcol;

	model.ints = intbuf;
	err = BOGUSERR;
	pinq_colr_model_facs(wstype,BUFSIZE,0,&err,&model,&total,&defcol);
	ERROR("pinq_colr_model_facs");

	expmodel.num_ints = num_col_model;
	expmodel.ints = list_col_model;
	if (! i_compare_Pint_list(model,expmodel))
		tfprintf("failed: list of colour model != expected\n");
	if (defcol != def_col_model)
		tfprintf("failed: default colour model = %d, expected %d\n",
			defcol,def_col_model);
}

/*
 * verify_colour_facilities() 
 * verify the chromaticity coordinates of display primaries
 *        number of predefined colour indices 
 *        colour availability
 */
static void
verify_colour_facilities() 
{

	Pint num;
	Pcolr_facs cofacil;

	err = BOGUSERR;
	pinq_colr_facs(wstype,&err,&cofacil);
	ERROR("pinq_colr_facs");

/*
	if (! i_compare_Pchrom_coeff_array(3,cofacil.primary,chromaticity))
		tfprintf("failed: chromaticity coordinates of primaries != expected\n");
*/
	if (cofacil.num_colrs != num_col_idx)
		tfprintf("failed: # of available colour indices = %d, expected %d\n",
			cofacil.num_colrs,num_col_idx);
	if (cofacil.num_pred_inds != num_pred_col_idx)
		tfprintf("failed: # of predefined colour indices = %d, expected %d\n",
			cofacil.num_pred_inds,num_pred_col_idx);
	if (cofacil.colr_avail != col_avail)
		tfprintf("failed: colour availability = %d, expected %d\n",
			cofacil.colr_avail,col_avail);
}

