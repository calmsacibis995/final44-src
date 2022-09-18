/* $XConsortium: elemcon9.c,v 5.3 91/07/24 18:45:04 hersh Exp $ */

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
## elemcon9.c - test pinq_elem_type_size, pinq_elem_content,
## pinq_cur_elem_type_size, and pinq_cur_elem_content, as well
## as archiving and structure copying, for all element types.
## Command line switches turn on or off the different
## types of testing, and integer arguments specify structure
## elements to be stored; these two types of arguments can
## be freely intermixed.  Test execution scripts may choose
## to execute this test multiple times with different sets
## of elements.
 *
 * Usage: command line arguments consist of integers specifying test
 * cases, and the following flags:
 * -a (+a) : turn off (on) archive testing; the default is off
 * -c (+c) : turn off (on) element content testing; default is on
 * 
 * These flags may be freely intermixed with the integers specifying
 * cases; they will only have effect on the cases following them in 
 * the command line (thus, they should be placed first, unless 
 * you want to perform different tests later in the test set).
 * 
 * The integers specifying element types correspond solely to
 * where they occur in the big switch statement in main(), not
 * to anything in any standard.  This list currently consists
 * of Phigs elements in roughly alphabetical order, followed by
 * Phigs+ elements in alphabetical order, but this is not
 * guaranteed to remain true (i.e. elements may be added that
 * are out of alphabetical order).
 * 
 * To add new elements, add a new case in the big switch,
 * a handler for the element in i_compare_element() in 
 * tools/pexint/computils.c, and adjust the number in the
 * error message printed in the default case at the end of 
 *the big switch. 
 *
 * To add new test types, add: a new flag variable, a new case
 * in element_test, new cases in both argument switches at the beginning
 * of main(), a new letter in the error output message at the
 * very end of the big switch, and a new line in the comment above.
 */

#include "phigs/phigs.h"
#include "X11/Xlib.h"
#include "X11/Xutil.h"
#include "X11/Xatom.h"
#include <strings.h>
#include "logmsg.h"
#include "imath.h"
#include "computils.h"
#include "testutils.h"

#define STR1    1
#define WS1     1
#define DEST_STR 88   

/*
 * Sample data for some simple-valued items
 */
#define SAMPLE_ANNOT_STYLE 2
#define SAMPLE_TEXT_HEIGHT 5.5

/* 
 * flag variables specifying what kinds of testing are performed
 */

int test_content = 1; 
int test_archive = 0;
int test_copy    = 0;

/*
 * element_test() - perform a set of tests on the specified element
 * according to current values of test_content and test_archive.
 * if test_content is true, then the element's content is read
 * back and compared against the expected (assumes that the current
 * element in the current structure is the one being compared against).
 * if test_archive is true, then archive tests are performed.
 */
void
element_test(type_num,struct_id, element, expecttype, expectdata, element_name)
    int             type_num;	  /* number of test case, corresponding */
                                  /* to element type (where the number  */
                                  /* of a type is determined solely by  */
				  /* where it is placed in the big switch */
				  /* in main() ) */
    Pint	    struct_id;
    Pint	    element;
    Pelem_type         expecttype;
    Pelem_data        *expectdata;
    char           *element_name;	/* string naming the element type */
{

    Pint_list strs;

    Popen_struct_status st_status;  /* for inquiring current open struct */
    Pint error;
    Pint saved_ptr, saved_struct;  /* original element pointer and structid */
    Pint dest_ptr;		   /* starting elemptr in destination struct */
    char elname_plus_note[100];    /* element name plus comment */

    strs.num_ints = 1;
    strs.ints = &struct_id;
    if (test_content) {
	/* perform test of inquiring element content */
	tvprintf(2, "testing content of element %d, type %d=%s\n", 
		 element, type_num, element_name);
	i_check_element(struct_id, element, expecttype, expectdata,
			element_name);
	i_check_current_element(expecttype, expectdata, element_name);
    }
    if (test_archive) {
	/* perform archive tests */
	tvprintf(2,"testing archiving for element %d, type %d=%s\n", 
		 element, type_num, element_name);
	unlink("archfile");
	popen_ar_file(1,"archfile");
	par_all_structs(1);
	pclose_struct();
	punpost_struct(WS1,STR1);
	pdel_all_structs();
	pret_all_structs(1);
	pclose_ar_file(1);
	i_check_element(struct_id, element, expecttype, expectdata, 
			element_name);
	popen_struct(STR1);
	ppost_struct(WS1,STR1,1.0);
    }
    if (test_copy) {
	pinq_open_struct(&error, &st_status, &saved_struct);
	if (st_status == PSTRUCT_OPEN) {
	    /* save element pointer, struct id for later restoration */
	    pinq_elem_ptr(&error, &saved_ptr);
	    pclose_struct();
	}
	popen_struct(DEST_STR);
	pinq_elem_ptr(&error, &dest_ptr);
	pcopy_all_elems_struct(struct_id);
	sprintf(elname_plus_note, "%s(copied)", element_name);
	i_check_element(DEST_STR, element+dest_ptr, expecttype, expectdata,
			elname_plus_note);
	pclose_struct();
	if (st_status == PSTRUCT_OPEN) {
	    popen_struct(saved_struct);
	    pset_elem_ptr(saved_ptr);
	}
    }
}

main(argc,argv)
    int argc;
    char *argv[];
{
    int 	    i,j, length;
    char	    *description;
    int		    argument;
    int		    testcase;
    Window          ws_window;
    Display	    *ws_display;
    int		curr_element = 0;

    /* variables and structures for sample data */
    Pelem_data		peldata;

    static Pint		tenpints[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
    			sixpints[6] = {11, 12, 13, 14, 15, 16};
    static Pint_list	pintlist = {10, tenpints},
    			pintlist2 = {6, sixpints};
    static Ptext_align	ptxalign = { PHOR_LEFT, PVERT_HALF };
    static Pvec		pvector = { 19.5, 6.25 } ;
    static Pfloat_size	pfloat_s = { 19.5, 6.25 } ;
    static Pvec3	pvector3a = {0.0, 1.0, 0.0},
    			ref_vectors[2] = {{0.0, 0.9, 0.1}, {0.2, 0.5, 0.5}};
    static Pvec3	pvector3_array[] = {{0.0, 1.0, 0.0},
					    {0.5, 0.5, 0.2},
					    {0.5, 0.2, 0.1},
					    {0.1, 0.7, 0.2},
					    {0.2, 0.5, 0.3},
					    {0.1, 0.1, 0.8}};    
    static Ppoint	ppoint = { 12.5, 4.0 };
    static Ppoint3	ppoint3 = { 4.25, 5.0, 6.05};
    static Pdata	pdata = { 29, "some sample application data"};
    static Prect 	prect = { {0.3, 0.3} , {0.7, 0.7}};
    static Pint_size		pdim = { 4, 3 };
    static Pint		color_array[3][4] = { {2, 2, 2, 2},
					{2, 4, 4, 2},
					{2, 4, 4, 2} };
    static Ppat_rep	patrep = {{4, 3}, color_array[0]};
    static Pparal	pgram = {{0.1, 0.1, 0.1},
				    {0.9, 0.1, 0.3},
				    {0.2, 0.7, -1.0}};
    static Ppoint	ppoints[] = { {0.5, 0.2},
				       {0.7, 0.2},
				       {0.1, 0.8} },
    			ppoints_b[] = { {0.1, 0.1},
					{0.3, 0.1},
					{0.9, 0.8},
					{0.1, 0.15} };
    static Ppoint3	ppoint3s[] = { {0.5, 0.5, 0.5},
				      {0.7, 0.3, 0.6},
				      {0.1, 2.3, 0.1} },
    			ppoint3s_b[] = { {0.5, 0.1, 1.2},
					 {0.4, 0.2, 0.0},
					 {0.8, 0.1, 0.0},
					 {0.2, 0.1, 0.0},
					 {0.1, 0.4, 0.1},
					 {0.5, 0.4, 0.2}};
    static Ppoint_list   two_ppoints[] = { {3, ppoints},
					 {4, ppoints_b} };
    static Ppoint_list_list   ppoints_list;
    static Ppoint_list3  two_ppoint3s[] = { {3, ppoint3s},
					  {4, ppoint3s_b} };
    static Ppoint_list_list3  ppoints_list3;
    static Pmatrix	pmatrix = { {1.0, 0.0, 0.0},
				    {0.0, 1.0, 0.0},
				    {3.2, 1.5, 1.0}};
    static Pmatrix3	pmatrix3 = { {1.0, 0.0, 0.0, 0.0},
				     {0.0, 1.0, 0.0, 0.0},
				     {0.0, 0.0, 1.0, 0.0},
				     {4.5, 3.2, 1.5, 1.0}};
    static Phalf_space	phalf[3] = {{{0.5, 0.2},{1.0, 0.0}},  /* halfspace 1 */
				    {{0.2, 0.0},{0.0, 1.0}},  /* halfspace 2 */
				    {{0.9, 0.9},{-1.0,0.0}}}; /* halfspace 3 */
    static Phalf_space_list phalflst = { 3, phalf};

    static Phalf_space3	phalf3[3] = {{{0.5, 0.2, 0.0},
				      {1.0, 0.0, 0.0}},  /* halfspace 1 */
				     {{0.2, 0.0, 0.5},
				      {0.0, 1.0, 0.0}},  /* halfspace 2 */
				     {{0.9, 0.9, 0.2},
				      {-1.0, 0.0, 0.0}}}; /* halfspace 3 */
    static Phalf_space_list3 phalflst3 = { 3, phalf3};
    Pgcolr 		pgcolr;
    Prefl_props 	parea_props;

    /* for fill area set3 w/ data */
    Pfacet_data3 	pfacet_data;
    static Pedge_flag 	flags[] = {PEDGE_ON, PEDGE_OFF, PEDGE_ON, PEDGE_OFF};
    static Pedge_data_list pedge_data[2];
    Pptconorm3 		ptconorm1[3], ptconorm2[4];
    static struct {	/* hsv colors for vertices */
	Pfloat h;
	Pfloat s;
	Pfloat v;
    } vcolors1[3] = {0.1,0.1,0.1, 0.2,0.2,0.2, 0.3,0.3,0.3},
      vcolors2[4] = {0.4,0.4,0.4, 0.5,0.5,0.5, 0.6,0.6,0.6, 0.7,0.7,0.7};
    static Pvec3       normals1[] = { {0.5, 0.5, 0.0}, /* normals for */
				      {0.7, 0.3, 0.1}, /* vertices */
				      {0.1, 0.3, 0.1} },
    			normals2[] = { {0.5, 0.1, 0.3},
					 {0.4, 0.2, 0.0},
					 {0.8, 0.1, 0.0},
					 {0.2, 0.1, 0.6} };
    Pfacet_vdata_list3 	pfacet_vdata[2];

    /* for ppolyline_set3_data: */
    Pptco3 ptco1[3], ptco2[4];
    Pline_vdata_list3 pline_vdata[2];

    /* for quad3_data and tri3_data: */
    Pfacet_data_arr3 	facet_arr;
    Pconorm3		conorms[2];
    Pfacet_vdata_arr3	vertex_arr;
    Pptconorm3		ptconorms[6];
    static Pint_size	quad_dims = { 2, 3 };


    /* put arguments into test description string */
    for (i=1, length=0; i < argc; i++) 
	length += strlen(argv[i]) + 1;  /* one extra for space */
    description = (char *) malloc(length + 50);
    strcpy(description, "inquiring element type, size, content (");
    for (i=1; i < argc; i++) {
	strcat(description, argv[i]);
	if (i != argc-1) strcat(description, " ");
    }
    strcat(description, ")");

    tbegintest("elemcon9", description);

    /* Set up phigs, workstation, and structure */
    i_open_phigs(NULL, PDEF_MEM_SIZE);
    i_open_x_ws(WS1, &ws_display, &ws_window, 300, 100, 200, 200);
    popen_struct(STR1);
    ppost_struct(WS1, STR1, 1.0);
	

    /*
     * For every integer argument, execute the appropriate test case.
     */
    
    
    for (argument=1; argument<argc; argument++)  {
	if (argv[argument][0] == '+') {
	    /* adding a test type */
	    switch(argv[argument][1]) {
	    case 'a':
		test_archive = 1;
		break;
	    case 'c':
		test_content = 1;
		break;
	    case 'p':
		test_copy = 1;
		break;
	    default:
	        tabort("ERROR: invalid switch %s - exiting\n", argv[argument]);
	    }
	} else if (argv[argument][0] == '-') {
	    /* removing a test type */
	    switch (argv[argument][1]) {
	    case 'a':
		test_archive = 0; break;
	    case 'c':
		test_content = 0; break;
	    case 'p':
		test_content = 0; break;
	    default:
	        tabort("ERROR: invalid switch %s - exiting\n", argv[argument]);
	    }
	} else {
	    testcase = atoi(argv[argument]);
	    switch(testcase) {
		/* 
		 * note that these cases start at 1 -- 0 might be the
		 * result of a non-integer argument, and is handled
		 * gracefully by the default case below.
		 */
	    case 1:
		/* 
		 *## ADD NAMES TO SET
		 */
		padd_names_set(&pintlist);  
		peldata.names = pintlist;
		element_test(testcase, STR1, ++curr_element, PELEM_ADD_NAMES_SET, &peldata,
				"PELEM_ADD_NAMES_SET");
		break;
		
	    case 2:
		/*
		 *## ANNOTATION STYLE
		 */
		pset_anno_style(SAMPLE_ANNOT_STYLE);
		peldata.int_data = SAMPLE_ANNOT_STYLE;
		element_test(testcase, STR1, ++curr_element, PELEM_ANNO_STYLE, &peldata,
				"PELEM_ANNO_STYLE");
		break;

	    case 3:
		/*
		 *## ANNOTATION TEXT ALIGNMENT
		 */
		pset_anno_align(&ptxalign);
		peldata.text_align = ptxalign;
		element_test(testcase, STR1, ++curr_element, PELEM_ANNO_ALIGN,
				&peldata, "PELEM_ANNO_ALIGN");
		
		break;
		
	    case 4:
		/*
		 *## ANNOTATION TEXT CHARACTER HEIGHT
		 */
		pset_anno_char_ht(SAMPLE_TEXT_HEIGHT);
		peldata.float_data = SAMPLE_TEXT_HEIGHT;
		element_test(testcase, STR1, ++curr_element, PELEM_ANNO_CHAR_HT,
				&peldata, "PELEM_ANNO_CHAR_HT");
		break;

	    case 5:
		/*
		 *## ANNOTATION TEXT CHARACTER UP VECTOR
		 */
		pset_anno_char_up_vec(&pvector);
		peldata.char_up_vec = pvector;
		element_test(testcase, STR1, ++curr_element, PELEM_ANNO_CHAR_UP_VEC,
				&peldata, "PELEM_ANNO_CHAR_UP_VEC");
		break;

	    case 6:
		/*
		 *## PELEM_ANNO_PATH
		 */
		pset_anno_path(PPATH_DOWN);
		peldata.text_path = PPATH_DOWN;
		element_test(testcase, STR1, ++curr_element, PELEM_ANNO_PATH,
				&peldata, "PELEM_ANNO_PATH");
		break;

	    case 7:
		/*
		 *## PELEM_ANNO_TEXT_REL
		 */
		panno_text_rel(&ppoint, &pvector, "sample");
		peldata.anno_text_rel.ref_point = ppoint;
		peldata.anno_text_rel.offset = pvector;
		peldata.anno_text_rel.char_string = "sample";
		element_test(testcase, STR1, ++curr_element, PELEM_ANNO_TEXT_REL,
				&peldata, "PELEM_ANNO_TEXT_REL");
		break;

	    case 8:
		/*
		 *## PELEM_ANNO_TEXT_REL3
		 */
		panno_text_rel3(&ppoint3, &pvector3a, "sample3");
		peldata.anno_text_rel3.ref_point = ppoint3;
		peldata.anno_text_rel3.offset = pvector3a;
		peldata.anno_text_rel3.char_string = "sample3";
		element_test(testcase, STR1, ++curr_element, PELEM_ANNO_TEXT_REL3,
				&peldata, "PELEM_ANNO_TEXT_REL3");
		break;

	    case 9:
		/*
		 *## PELEM_APPL_DATA
		 */
		pappl_data(&pdata);
		peldata.appl_data = pdata;
		element_test(testcase, STR1, ++curr_element, PELEM_APPL_DATA,
				&peldata, "PELEM_APPL_DATA");
		break;		
		
	    case 10:
		/*
		 *## PELEM_CELL_ARRAY
		 */
		  pcell_array(&prect, &patrep);
		  peldata.cell_array.rect = prect;
		  peldata.cell_array.colr_array.dims = pdim;
		  peldata.cell_array.colr_array.colr_array = color_array[0];
		  element_test(testcase, STR1, ++curr_element, PELEM_CELL_ARRAY,
		  &peldata, "PELEM_CELL_ARRAY");
		break;

	    case 11:
		/*
		 *## PELEM_CELL_ARRAY3
		 */
		  pcell_array3(&pgram, &patrep);
		  peldata.cell_array3.paral = pgram;
		  peldata.cell_array3.colr_array.dims = pdim;
		  peldata.cell_array3.colr_array.colr_array = color_array[0];
		  element_test(testcase, STR1, ++curr_element, PELEM_CELL_ARRAY3,
		  &peldata, "PELEM_CELL_ARRAY3");
		break;
		
	    case 12:
		/*
		 *## PELEM_CHAR_EXPAN
		 */
		pset_char_expan(3.5);
		peldata.float_data = 3.5;
		element_test(testcase, STR1, ++curr_element, PELEM_CHAR_EXPAN,
				&peldata, "PELEM_CHAR_EXPAN");
		break;
	       
	    case 13:
		/*
		 *## PELEM_CHAR_HT
		 */
		pset_char_ht(4.5);
		peldata.float_data = 4.5;
		element_test(testcase, STR1, ++curr_element, PELEM_CHAR_HT,
				&peldata, "PELEM_CHAR_HT");
		break;

	    case 14:
		/*
		 *## PELEM_CHAR_SPACE
		 */
		pset_char_space(1.5);
		peldata.float_data = 1.5;
		element_test(testcase, STR1, ++curr_element, PELEM_CHAR_SPACE,
				&peldata, "PELEM_CHAR_SPACE");
		break;
		
	    case 15:
		/*
		 *## PELEM_CHAR_UP_VEC
		 */
		pset_char_up_vec(&pvector);
		peldata.char_up_vec = pvector;
		element_test(testcase, STR1, ++curr_element, PELEM_CHAR_UP_VEC,
				&peldata, "PELEM_CHAR_UP_VEC");
		break;
		
	    case 16:
		/*
		 *## PELEM_EDGE_COLR_IND
		 */
		pset_edge_colr_ind(5);
		peldata.int_data = 5;
		element_test(testcase, STR1, ++curr_element, PELEM_EDGE_COLR_IND,
				&peldata, "PELEM_EDGE_COLR_IND");
		break;

	    case 17:
		/*
		 *## PELEM_EDGE_FLAG
		 */
		pset_edge_flag(PEDGE_OFF);
		peldata.edge_flag = PEDGE_OFF;
		element_test(testcase, STR1, ++curr_element, PELEM_EDGE_FLAG,
				&peldata, "PELEM_EDGE_FLAG");
		break;

	    case 18:
		/*
		 *## PELEM_EDGE_IND
		 */
		pset_edge_ind(35);
		peldata.int_data = 35;
		element_test(testcase, STR1, ++curr_element, PELEM_EDGE_IND,
				&peldata, "PELEM_EDGE_IND");
		break;

	    case 19:
		/*
		 *## PELEM_EDGETYPE
		 */
		pset_edgetype(PLINE_DASH_DOT);
		peldata.int_data = PLINE_DASH_DOT;
		element_test(testcase, STR1, ++curr_element, PELEM_EDGETYPE,
				&peldata, "PELEM_EDGETYPE");
		break;
		
	    case 20:
		/*
		 *## PELEM_EDGEWIDTH
		 */
		pset_edgewidth(6.0);
		peldata.float_data = 6.0;
		element_test(testcase, STR1, ++curr_element, PELEM_EDGEWIDTH,
				&peldata, "PELEM_EDGEWIDTH");
		break;

	    case 21:
		/*
		 *## PELEM_EXEC_STRUCT
		 */
		pexec_struct(10);
		peldata.int_data = 10;
		element_test(testcase, STR1, ++curr_element, PELEM_EXEC_STRUCT,
				&peldata, "PELEM_EXEC_STRUCT");
		break;
		
	    case 22:
		/*
		 *## PELEM_FILL_AREA
		 */
		pfill_area(&two_ppoints[0]);
		peldata.point_list = two_ppoints[0];
		element_test(testcase, STR1, ++curr_element, PELEM_FILL_AREA,
				&peldata, "PELEM_FILL_AREA");
		break;

	    case 23:
		/*
		 *## PELEM_FILL_AREA_SET
		 */
                ppoints_list.num_point_lists = 2;
                ppoints_list.point_lists = two_ppoints;
		pfill_area_set(&ppoints_list);
		peldata.point_list_list.num_point_lists = 2;
		peldata.point_list_list.point_lists = two_ppoints;
		element_test(testcase, STR1, ++curr_element, PELEM_FILL_AREA_SET,
				&peldata, "PELEM_FILL_AREA_SET");
		break;
		
	    case 24:
		/*
		 *## PELEM_FILL_AREA_SET3
		 */
                ppoints_list3.num_point_lists = 2;
                ppoints_list3.point_lists = two_ppoint3s;
		pfill_area_set3(&ppoints_list3);
		peldata.point_list_list3.num_point_lists = 2;
		peldata.point_list_list3.point_lists = two_ppoint3s;
		element_test(testcase, STR1, ++curr_element, PELEM_FILL_AREA_SET3,
				&peldata, "PELEM_FILL_AREA_SET3");
		break;
		
	    case 25:
		/*
		 *## PELEM_FILL_AREA3
		 */
		pfill_area3(&two_ppoint3s[0]);
		peldata.point_list3 = two_ppoint3s[0];
		element_test(testcase, STR1, ++curr_element, PELEM_FILL_AREA3,
				&peldata, "PELEM_FILL_AREA3");
		break;
		
	    case 26:
		/*
		 *## PELEM_GLOBAL_MODEL_TRAN	
		 */
		pset_global_tran(pmatrix);
		for (i=0; i<3; i++)
		    for (j=0; j<3; j++)
			peldata.global_tran[i][j] = pmatrix[i][j];
		element_test(testcase, STR1, ++curr_element, PELEM_GLOBAL_MODEL_TRAN,
				&peldata, "PELEM_GLOBAL_MODEL_TRAN");
		break;
		
	    case 27:
		/*
		 *## PELEM_GLOBAL_MODEL_TRAN3	
		 */
		pset_global_tran3(pmatrix3);
		for (i=0; i<4; i++)
		    for (j=0; j<4; j++)
			peldata.global_tran3[i][j] = pmatrix3[i][j];
		element_test(testcase, STR1, ++curr_element, PELEM_GLOBAL_MODEL_TRAN3,
				&peldata, "PELEM_GLOBAL_MODEL_TRAN3");
		break;
		
	    case 28:
		/*
		 *## PELEM_HLHSR_ID
		 */
		pset_hlhsr_id(PHIGS_HLHSR_ID_ON);
		peldata.int_data = PHIGS_HLHSR_ID_ON;
		element_test(testcase, STR1, ++curr_element, PELEM_HLHSR_ID,
				&peldata, "PELEM_HLHSR_ID");
		break;

	    case 29:
		/*
		 *## PELEM_INDIV_ASF
		 */
		pset_indiv_asf(PASPECT_MARKER_TYPE, PASF_BUNDLED);
		peldata.asf.id = PASPECT_MARKER_TYPE;
		peldata.asf.source = PASF_BUNDLED;
		element_test(testcase, STR1, ++curr_element, PELEM_INDIV_ASF,
				&peldata, "PELEM_INDIV_ASF");
		break;

	    case 30:
		/*
		 *## PELEM_INT_COLR_IND
		 */
		pset_int_colr_ind(5);
		peldata.int_data = 5;
		element_test(testcase, STR1, ++curr_element, PELEM_INT_COLR_IND,
				&peldata, "PELEM_INT_COLR_IND");
		break;

	    case 31:
		/*
		 *## PELEM_INT_IND
		 */
		pset_int_ind(3);
		peldata.int_data = 3;
		element_test(testcase, STR1, ++curr_element, PELEM_INT_IND,
				&peldata, "PELEM_INT_IND");
		break;

	    case 32:
		/*
		 *## PELEM_INT_STYLE
		 */
		pset_int_style(PSTYLE_HATCH);
		peldata.int_style = PSTYLE_HATCH;
		element_test(testcase, STR1, ++curr_element, PELEM_INT_STYLE,
				&peldata, "PELEM_INT_STYLE");
		break;
		
	    case 33:
		/*
		 *## PELEM_INT_STYLE_IND
		 */
		pset_int_style_ind(7);
		peldata.int_data = 7;
		element_test(testcase, STR1, ++curr_element, PELEM_INT_STYLE_IND,
				&peldata, "PELEM_INT_STYLE_IND");
		break;

	    case 34:
		/*
		 *## PELEM_LABEL
		 */
		plabel(99);
		peldata.int_data = 99;
		element_test(testcase, STR1, ++curr_element, PELEM_LABEL,
				&peldata, "PELEM_LABEL");
		break;

	    case 35:
		/*
		 *## PELEM_LINETYPE
		 */
		pset_linetype(PLINE_DASH_DOT);
		peldata.int_data = PLINE_DASH_DOT;
		element_test(testcase, STR1, ++curr_element, PELEM_LINETYPE,
				&peldata, "PELEM_LINETYPE");
		break;

	    case 36:
		/*
		 *## PELEM_LINEWIDTH
		 */
		pset_linewidth(5.5);
		peldata.float_data = 5.5;
		element_test(testcase, STR1, ++curr_element, PELEM_LINEWIDTH,
				&peldata, "PELEM_LINEWIDTH");
		break;

	    case 37:
		/*
		 *## PELEM_LOCAL_MODEL_TRAN
		 */
		pset_local_tran(pmatrix, PTYPE_REPLACE);
		for (i=0; i<3; i++)
		    for (j=0; j<3; j++)
			peldata.local_tran.matrix[i][j] = pmatrix[i][j];
		peldata.local_tran.compose_type = PTYPE_REPLACE;
		element_test(testcase, STR1, ++curr_element, PELEM_LOCAL_MODEL_TRAN,
				&peldata, "PELEM_LOCAL_MODEL_TRAN");
		break;

	    case 38:
		/*
		 *## PELEM_LOCAL_MODEL_TRAN3
		 */
		pset_local_tran3(pmatrix3, PTYPE_POSTCONCAT);
		for (i=0; i<4; i++)
		    for (j=0; j<4; j++)
			peldata.local_tran3.matrix[i][j] = pmatrix3[i][j];
		peldata.local_tran3.compose_type = PTYPE_POSTCONCAT;
		element_test(testcase, STR1, ++curr_element, PELEM_LOCAL_MODEL_TRAN3,
				&peldata, "PELEM_LOCAL_MODEL_TRAN3");
		break;
		
	    case 39:
		/*
		 *## PELEM_MARKER_COLR_IND
		 */
		pset_marker_colr_ind(2);
		peldata.int_data = 2;
		element_test(testcase, STR1, ++curr_element, PELEM_MARKER_COLR_IND,
				&peldata, "PELEM_MARKER_COLR_IND");
		break;
		
	    case 40:
		/*
		 *## PELEM_MARKER_SIZE
		 */
		pset_marker_size(11.1);
		peldata.float_data = 11.1;
		element_test(testcase, STR1, ++curr_element, PELEM_MARKER_SIZE,
				&peldata, "PELEM_MARKER_SIZE");
		break;
		
	    case 41:
		/*
		 *## PELEM_MARKER_TYPE
		 */
		pset_marker_type(PMARKER_ASTERISK);
		peldata.int_data = PMARKER_ASTERISK;
		element_test(testcase, STR1, ++curr_element, PELEM_MARKER_TYPE,
				&peldata, "PELEM_MARKER_TYPE");
		break;

	    case 42:
		/*
		 *## PELEM_MODEL_CLIP_IND
		 */
		pset_model_clip_ind(PIND_NO_CLIP);
		peldata.clip_ind = PIND_NO_CLIP;
		element_test(testcase, STR1, ++curr_element, PELEM_MODEL_CLIP_IND,
				&peldata, "PELEM_MODEL_CLIP_IND");
		break;

	    case 43:
		/*
		 *## PELEM_MODEL_CLIP_VOL
		 */
		pset_model_clip_vol(PMC_REPLACE, &phalflst);
		peldata.model_clip.op = PMC_REPLACE;
		peldata.model_clip.half_spaces = phalflst;
		element_test(testcase, STR1, ++curr_element, PELEM_MODEL_CLIP_VOL,
				&peldata, "PELEM_MODEL_CLIP_VOL");
		break;

	    case 44:
		/*
		 *## PELEM_MODEL_CLIP_VOL3
		 */
		pset_model_clip_vol3(PMC_REPLACE, &phalflst3);
		peldata.model_clip3.op = PMC_REPLACE;
		peldata.model_clip3.half_spaces = phalflst3;
		element_test(testcase, STR1, ++curr_element, PELEM_MODEL_CLIP_VOL3,
				&peldata, "PELEM_MODEL_CLIP_VOL3");
		break;

	    case 45:
		/*
		 *## PELEM_PAT_REF_POINT
		 */
		pset_pat_ref_point(&ppoint);
		peldata.pat_ref_point = ppoint;
		element_test(testcase, STR1, ++curr_element, PELEM_PAT_REF_POINT,
				&peldata, "PELEM_PAT_REF_POINT");
		break;

	    case 46:
		/*
		 *## PELEM_PAT_REF_POINT_VECS
		 */
		pset_pat_ref_point_vecs(&ppoint3, ref_vectors);
		peldata.pat_ref_point_vecs.ref_point = ppoint3;
		peldata.pat_ref_point_vecs.ref_vec[0] = ref_vectors[0];
		peldata.pat_ref_point_vecs.ref_vec[1] = ref_vectors[1];
		element_test(testcase, STR1, ++curr_element, PELEM_PAT_REF_POINT_VECS,
				&peldata, "PELEM_PAT_REF_POINT_VECS");
		break;

	    case 47:
		/*
		 *## PELEM_PAT_SIZE
		 */
		pset_pat_size(pfloat_s.size_x, pfloat_s.size_y);
		peldata.pat_size = pfloat_s;
		element_test(testcase, STR1, ++curr_element, PELEM_PAT_SIZE,
				&peldata, "PELEM_PAT_SIZE");
		break;

	    case 48:
		/*
		 *## PELEM_PICK_ID
		 */
		pset_pick_id(666);
		peldata.int_data = 666;
		element_test(testcase, STR1, ++curr_element, PELEM_PICK_ID,
				&peldata, "PELEM_PICK_ID");
		break;

	    case 49:
		/*
		 *## PELEM_POLYLINE
		 */
		ppolyline(&two_ppoints[0]);
		peldata.point_list = two_ppoints[0];
		element_test(testcase, STR1, ++curr_element, PELEM_POLYLINE,
				&peldata, "PELEM_POLYLINE");
		break;
		
	    case 50:
		/*
		 *## PELEM_LINE_COLR_IND
		 */
		pset_line_colr_ind(2);
		peldata.int_data = 2;
		element_test(testcase, STR1, ++curr_element, PELEM_LINE_COLR_IND,
				&peldata, "PELEM_LINE_COLR_IND");
		break;

	    case 51:
		/*
		 *## PELEM_LINE_IND
		 */
		pset_line_ind(22);
		peldata.int_data = 22;
		element_test(testcase, STR1, ++curr_element, PELEM_LINE_IND,
				&peldata, "PELEM_LINE_IND");
		break;

	    case 52:
		/*
		 *## PELEM_POLYLINE3
		 */
		ppolyline3(&two_ppoint3s[0]);
		peldata.point_list3 = two_ppoint3s[0];
		element_test(testcase, STR1, ++curr_element, PELEM_POLYLINE3,
				&peldata, "PELEM_POLYLINE3");
		break;
		
	    case 53:
		/*
		 *## PELEM_POLYMARKER
		 */
		ppolymarker(&two_ppoints[1]);
		peldata.point_list = two_ppoints[1];
		element_test(testcase, STR1, ++curr_element, PELEM_POLYMARKER,
				&peldata, "PELEM_POLYMARKER");
		break;
		
	    case 54:
		/*
		 *## PELEM_MARKER_IND
		 */
		pset_marker_ind(3);
		peldata.int_data = 3;
		element_test(testcase, STR1, ++curr_element, PELEM_MARKER_IND,
				&peldata, "PELEM_MARKER_IND");
		break;
		
	    case 55:
		/*
		 *## PELEM_POLYMARKER3
		 */
		ppolymarker3(&two_ppoint3s[1]);
		peldata.point_list3 = two_ppoint3s[1];
		element_test(testcase, STR1, ++curr_element, PELEM_POLYMARKER3,
				&peldata, "PELEM_POLYMARKER3");
		break;

	    case 56:
		/*
		 *## PELEM_REMOVE_NAMES_SET
		 */
		premove_names_set(&pintlist);
		peldata.names = pintlist;
		element_test(testcase, STR1, ++curr_element, PELEM_REMOVE_NAMES_SET,
				&peldata, "PELEM_REMOVE_NAMES_SET");
		break;
		
	    case 57:
		/*
		 *## PELEM_RESTORE_MODEL_CLIP_VOL
		 */
		prestore_model_clip_vol();
		element_test(testcase, STR1, ++curr_element, 
			  PELEM_RESTORE_MODEL_CLIP_VOL,
			  &peldata, "PELEM_RESTORE_MODEL_CLIP_VOL");
		break;

	    case 58:
		/*
		 *## PELEM_TEXT
		 */
		ptext(&ppoint, "hello world");
		peldata.text.pos = ppoint;
		peldata.text.char_string = "hello world";
		element_test(testcase, STR1, ++curr_element, PELEM_TEXT,
				&peldata, "PELEM_TEXT");
		break;
		
	    case 59:
		/*
		 *## PELEM_TEXT_ALIGN
		 */
		pset_text_align(&ptxalign);
		peldata.text_align = ptxalign;
		element_test(testcase, STR1, ++curr_element, PELEM_TEXT_ALIGN,
				&peldata, "PELEM_TEXT_ALIGN");
		break;
		
	    case 60:
		/*
		 *## PELEM_TEXT_COLR_IND
		 */
		pset_text_colr_ind(6);
		peldata.int_data = 6;
		element_test(testcase, STR1, ++curr_element, PELEM_TEXT_COLR_IND,
				&peldata, "PELEM_TEXT_COLR_IND");
		break;
		
	    case 61:
/* NOTE - duplicate case */
		/*
		 *## PELEM_TEXT_ALIGN
		 */
		pset_text_align(&ptxalign);
		peldata.text_align = ptxalign;
		element_test(testcase, STR1, ++curr_element, PELEM_TEXT_ALIGN,
				&peldata, "PELEM_TEXT_ALIGN");
		break;
		
	    case 62:
/* NOTE - duplicate case */
		/*
		 *## PELEM_TEXT_COLR_IND
		 */
		pset_text_colr_ind(5);
		peldata.int_data = 5;
		element_test(testcase, STR1, ++curr_element, PELEM_TEXT_COLR_IND,
				&peldata, "PELEM_TEXT_COLR_IND");
		break;
		
	    case 63:
		/*
		 *## PELEM_TEXT_FONT
		 */
		pset_text_font(PFONT_MONO);
		peldata.int_data = PFONT_MONO;
		element_test(testcase, STR1, ++curr_element, PELEM_TEXT_FONT,
				&peldata, "PELEM_TEXT_FONT");
		break;
		
	    case 64:
		/*
		 *## PELEM_TEXT_IND
		 */
		pset_text_ind(4);
		peldata.int_data = 4;
		element_test(testcase, STR1, ++curr_element, PELEM_TEXT_IND,
				&peldata, "PELEM_TEXT_IND");
		break;
		
	    case 65:
		/*
		 *## PELEM_TEXT_PATH
		 */
		pset_text_path(PPATH_DOWN);
		peldata.text_path = PPATH_DOWN;
		element_test(testcase, STR1, ++curr_element, PELEM_TEXT_PATH,
				&peldata, "PELEM_TEXT_PATH");
		break;
		
	    case 66:
		/*
		 *## PELEM_TEXT_PREC
		 */
		pset_text_prec(PPREC_STROKE);
		peldata.text_prec = PPREC_STROKE;
		element_test(testcase, STR1, ++curr_element, PELEM_TEXT_PREC,
				&peldata, "PELEM_TEXT_PREC");
		break;
		
	    case 67:
		/*
		 *## PELEM_TEXT3
		 */
		ptext3(&ppoint3, pvector3_array, "hello again");
		peldata.text3.pos = ppoint3;
		peldata.text3.dir[0] = pvector3_array[0];
		peldata.text3.dir[1] = pvector3_array[1];
		peldata.text3.char_string = "hello again";
		element_test(testcase, STR1, ++curr_element, PELEM_TEXT3,
				&peldata, "PELEM_TEXT3");
		break;
		
	    case 68:
		/*
		 *## PELEM_VIEW_IND
		 */
		pset_view_ind(11);
		peldata.int_data = 11;
		element_test(testcase, STR1, ++curr_element, PELEM_VIEW_IND,
				&peldata, "PELEM_VIEW_IND");
		break;

     /***********************************************************/
     /*    THE FOLLOWING CASES ARE PHIGS-PLUS ELEMENTS          */
     /***********************************************************/

	    case 69:
		/*
		 *## PELEM_REFL_PROPS
		 */
		parea_props.ambient_coef = 0.5;
		parea_props.diffuse_coef = 0.2;
		parea_props.specular_coef = 0.1;
		pgcolr.type = PMODEL_RGB;
		pgcolr.val.general.x = 0.3;
		pgcolr.val.general.y = 0.32;
		pgcolr.val.general.z = 0.35;
		parea_props.specular_colr = pgcolr;
		parea_props.specular_exp = 1.2;
		pset_refl_props(&parea_props);
		peldata.props = parea_props;
		element_test(testcase, STR1, ++curr_element,
			     PELEM_REFL_PROPS, &peldata,
			     "PELEM_REFL_PROPS");
		break;
	    case 70:
		/*
		 *## PELEM_BACK_REFL_PROPS
		 */
		parea_props.ambient_coef = 0.4;
		parea_props.diffuse_coef = 0.2;
		parea_props.specular_coef = 0.1;
		pgcolr.type = PINDIRECT;
		pgcolr.val.ind = 5;
		parea_props.specular_colr = pgcolr;
		parea_props.specular_exp = 1.0;
		pset_back_refl_props(&parea_props);
		peldata.props = parea_props;
		element_test(testcase, STR1, ++curr_element,
			     PELEM_BACK_REFL_PROPS, &peldata,
			     "PELEM_BACK_REFL_PROPS");
		break;
	    case 71:
		/*
		 *## PELEM_BACK_INT_COLR
		 */
		pgcolr.type = PMODEL_RGB;
		pgcolr.val.general.x = 0.3;
		pgcolr.val.general.y = 0.32;
		pgcolr.val.general.z = 0.35;
		pset_back_int_colr(&pgcolr);
		peldata.colr = pgcolr;
		element_test(testcase, STR1, ++curr_element,
			     PELEM_BACK_INT_COLR, &peldata,
			     "PELEM_BACK_INT_COLR");
		break;
	    case 72:
		/*
		 *## PELEM_BACK_INT_REFL_EQN
		 */
		pset_back_refl_eqn(PREFL_AMBIENT);
		peldata.int_data = PREFL_AMBIENT;
		element_test(testcase, STR1, ++curr_element,
			     PELEM_BACK_INT_REFL_EQN, &peldata,
			     "PELEM_BACK_INT_REFL_EQN");
		break;
	    case 73:
		/*
		 *## PELEM_BACK_INT_SHAD_METH
		 */
		pset_back_int_shad_meth(PSD_COLOUR);
		peldata.int_data = PSD_COLOUR;
		element_test(testcase, STR1, ++curr_element,
			     PELEM_BACK_INT_SHAD_METH, &peldata,
			     "PELEM_BACK_INT_SHAD_METH");
		break;
	    case 74:
		/*
		 *## PELEM_BACK_INT_STYLE
		 */
		pset_back_int_style(PSTYLE_PAT);
		peldata.int_style = PSTYLE_PAT;
		element_test(testcase, STR1, ++curr_element,
			     PELEM_BACK_INT_STYLE, &peldata,
			     "PELEM_BACK_INT_STYLE");
		break;
	    case 75:
		/*
		 *## PELEM_BACK_INT_STYLE_IND
		 */
		pset_back_int_style_ind(7);
		peldata.int_data = 7;
		element_test(testcase, STR1, ++curr_element, 
			     PELEM_BACK_INT_STYLE_IND,
			     &peldata, "PELEM_BACK_INT_STYLE_IND");
		break;
	    case 76:
		/*
		 *## PELEM_CURVE_APPROX_CRIT		
		 */
	        pset_curve_approx(PCURV_WS_DEP, 2.5);
		peldata.curv_approx.type = PCURV_WS_DEP;
		peldata.curv_approx.value = 2.5;
		element_test(testcase, STR1, ++curr_element,
			     PELEM_CURVE_APPROX_CRIT,
			     &peldata, "PELEM_CURVE_APPROX_CRIT");
		break;
	    case 77:
		/*
		 *## PELEM_DCUE_IND
		 */
	        pset_dcue_ind(3);
		peldata.int_data = 3;
		element_test(testcase, STR1, ++curr_element,
			     PELEM_DCUE_IND,
			     &peldata, "PELEM_DCUE_IND");
		break;
	    case 78:
		/*
		 *## PELEM_EDGE_COLR
		 */
       		pgcolr.type = PMODEL_HSV;
		pgcolr.val.general.x = 0.7;
		pgcolr.val.general.y = 0.2;
		pgcolr.val.general.z = 0.5;
		pset_edge_colr(&pgcolr);
		peldata.colr = pgcolr;
		element_test(testcase, STR1, ++curr_element,
			     PELEM_EDGE_COLR,
			     &peldata, "PELEM_EDGE_COLR");
		break;
	    case 79:
		/*
		 *## PELEM_FACE_CULL_MODE
		 */
	        pset_face_cull_mode(peldata.cull_mode = PCULL_BACKFACE);
		element_test(testcase, STR1, ++curr_element,
			     PELEM_FACE_CULL_MODE,
			     &peldata, "PELEM_FACE_CULL_MODE");
		break;
	    case 80:
		/*
		 *## PELEM_FACE_DISTING_MODE
		 */
	        pset_face_disting_mode(peldata.disting_mode = PDISTING_YES);
		element_test(testcase, STR1, ++curr_element,
			     PELEM_FACE_DISTING_MODE,
			     &peldata, "PELEM_FACE_DISTING_MODE");
		break;
	    case 81:
		/*
		 *## PELEM_FILL_AREA_SET3_DATA
		 */
	        /* create a fill area set of a triange and a quad, with
		 * color and normal data,
		 * color and normal info for each vertex, and
		 * visibility info for each edge.
		 */
		/* facet HSV colours, and normal: */
		pfacet_data.conorm.colr.direct.hsv.hue = 0.3;
		pfacet_data.conorm.colr.direct.hsv.satur = 0.9;
		pfacet_data.conorm.colr.direct.hsv.value = 0.5;
		pfacet_data.conorm.norm = pvector3a;
		/* edge data: flags */
		pedge_data[0].num_edges = 3;
		pedge_data[0].edgedata.edges = flags;
		pedge_data[1].num_edges = 4;
		pedge_data[1].edgedata.edges = flags;
		/* vertex data: coordinates, color, and normal */
		for (i=0; i<3; i++) {
		    ptconorm1[i].point = ppoint3s[i];
		    ptconorm1[i].colr.direct.hsv.hue = vcolors1[i].h;
		    ptconorm1[i].colr.direct.hsv.satur = vcolors1[i].s;
		    ptconorm1[i].colr.direct.hsv.value = vcolors1[i].v;
		    ptconorm1[i].norm = normals1[i];
		}
		for (i=0; i<4; i++) {
		    ptconorm2[i].point = ppoint3s_b[i];
		    ptconorm2[i].colr.direct.hsv.hue = vcolors2[i].h;
		    ptconorm2[i].colr.direct.hsv.satur = vcolors2[i].s;
		    ptconorm2[i].colr.direct.hsv.value = vcolors2[i].v;
		    ptconorm2[i].norm = normals2[i];
		}
		pfacet_vdata[0].num_vertices = 3;
		pfacet_vdata[0].vertex_data.ptconorms = ptconorm1;
		pfacet_vdata[1].num_vertices = 4;
		pfacet_vdata[1].vertex_data.ptconorms = ptconorm2;
		pfill_area_set3_data(peldata.fasd3.fflag = PFACET_COLOUR_NORMAL,
			       peldata.fasd3.eflag = PEDGE_VISIBILITY,
			       peldata.fasd3.vflag = PVERT_COORD_COLOUR_NORMAL,
			       peldata.fasd3.colr_model = PMODEL_HSV,
			       &pfacet_data,
			       peldata.fasd3.nfa = 2,
			       peldata.fasd3.edata = pedge_data,
			       peldata.fasd3.vdata = pfacet_vdata);
		peldata.fasd3.fdata = pfacet_data;
		element_test(testcase, STR1, ++curr_element,
			     PELEM_FILL_AREA_SET3_DATA,
			     &peldata, "PELEM_FILL_AREA_SET3_DATA");
		break;
	    case 82:
		/*
		 *## PELEM_INT_COLR
		 */
		pgcolr.type = PMODEL_CIELUV;
		pgcolr.val.general.x = 0.3;
		pgcolr.val.general.y = 0.2;
		pgcolr.val.general.z = 0.8;
		pset_int_colr(&pgcolr);
		peldata.colr = pgcolr;
		element_test(testcase, STR1, ++curr_element,
			     PELEM_INT_COLR,
			     &peldata, "PELEM_INT_COLR");
		break;
	    case 83:
		/*
		 *## PELEM_INT_REFL_EQN
		 */
		pset_refl_eqn(PREFL_AMB_DIFF);
		peldata.int_data = PREFL_AMB_DIFF;
		element_test(testcase, STR1, ++curr_element,
			     PELEM_INT_REFL_EQN, &peldata,
			     "PELEM_INT_REFL_EQN");
		break;
	    case 84:
		/*
		 *## PELEM_INT_SHAD_METH
		 */
		pset_int_shad_meth(PSD_COLOUR);
		peldata.int_data = PSD_COLOUR;
		element_test(testcase, STR1, ++curr_element,
			     PELEM_INT_SHAD_METH, &peldata,
			     "PELEM_INT_SHAD_METH");
		break;
	    case 85:
		/*
		 *## PELEM_LIGHT_SRC_STATE
		 */
	        pset_light_src_state(&pintlist, &pintlist2);
		peldata.lss.activation = pintlist;
		peldata.lss.deactivation = pintlist2;
		element_test(testcase, STR1, ++curr_element,
			     PELEM_LIGHT_SRC_STATE,
			     &peldata, "PELEM_LIGHT_SRC_STATE");
		break;
	    case 86:
		/*
		 *## PELEM_LINE_COLR
		 */
		pgcolr.type = PMODEL_RGB;
		pgcolr.val.general.x = 0.1;
		pgcolr.val.general.y = 1.0;
		pgcolr.val.general.z = 0.5;
		pset_line_colr(&pgcolr);
		peldata.colr = pgcolr;
		element_test(testcase, STR1, ++curr_element,
			     PELEM_LINE_COLR,
			     &peldata, "PELEM_LINE_COLR");
		break;
	    case 87:
		/*
		 *## PELEM_POLYLINE_SET3_DATA		
		 */
		/* re-use some data declared for pfillarea_set3_data */
		for (i=0; i<3; i++) {
		    ptco1[i].point = ppoint3s[2-i];  /* re-arrange */
		    ptco1[i].colr.direct.rgb.red = vcolors1[i].h;
		    ptco1[i].colr.direct.rgb.blue = vcolors1[i].s;
		    ptco1[i].colr.direct.rgb.green = vcolors1[i].v;
		}
		for (i=0; i<4; i++) {
		    ptco2[i].point = ppoint3s_b[3-i];  /* re-arrange */
		    ptco2[i].colr.direct.rgb.green = vcolors2[i].h;
		    ptco2[i].colr.direct.rgb.blue = vcolors2[i].s;
		    ptco2[i].colr.direct.rgb.red = vcolors2[i].v;
		}
		pline_vdata[0].num_vertices = 3;
		pline_vdata[0].vertex_data.ptcolrs = ptco1;
		pline_vdata[1].num_vertices = 4;
		pline_vdata[1].vertex_data.ptcolrs = ptco2;

	        ppolyline_set3_data(peldata.plsd3.vflag = PVERT_COORD_COLOUR,
				    peldata.plsd3.colr_model = PMODEL_RGB,
				    peldata.plsd3.npl = 2,
				    peldata.plsd3.vdata = pline_vdata);
		element_test(testcase, STR1, ++curr_element,
			     PELEM_POLYLINE_SET3_DATA,
			     &peldata, "PELEM_POLYLINE_SET3_DATA");
		break;
	    case 88:
		/*
		 *## PELEM_LINE_SHAD_METH
		 */
	        pset_line_shad_meth(peldata.int_data = PSD_COLOUR);
		element_test(testcase, STR1, ++curr_element,
			     PELEM_LINE_SHAD_METH,
			     &peldata, "PELEM_LINE_SHAD_METH");
		break;
	    case 89:
		/*
		 *## PELEM_MARKER_COLR
		 */
		pgcolr.type = PMODEL_HSV;
		pgcolr.val.general.x = 0.7;
		pgcolr.val.general.y = 1.0;
		pgcolr.val.general.z = 0.2;
		pset_marker_colr(&pgcolr);
		peldata.colr = pgcolr;
		element_test(testcase, STR1, ++curr_element,
			     PELEM_MARKER_COLR,
			     &peldata, "PELEM_MARKER_COLR");
		break;
	    case 90:
		/*
		 *## PELEM_QUAD_MESH3_DATA
		 */
		/* Make up some bogus data for a 2x3 quad mesh. */
		/* facets: */
		for (i=0; i<2; i++) {
		    conorms[i].colr.direct.hsv.hue = 0.1 * i;
		    conorms[i].colr.direct.hsv.satur = 0.2 * i;
		    conorms[i].colr.direct.hsv.value = 0.3 * i;
		    conorms[i].norm = normals1[i];
		}
		facet_arr.conorms = conorms;

	        /* vertices: make up points, colors, normals */
		for (i=0; i<6; i++) {
		    ptconorms[i].point = ppoint3s_b[i];
		    ptconorms[i].colr.direct.hsv.hue = ppoint3s_b[i].y;
		    ptconorms[i].colr.direct.hsv.satur = ppoint3s_b[i].x;
		    ptconorms[i].colr.direct.hsv.value = ppoint3s_b[i].z;
		    ptconorms[i].norm = pvector3_array[i];
		}
		vertex_arr.ptconorms = ptconorms;
		peldata.qmd3.dim = quad_dims;
		pquad_mesh3_data(peldata.qmd3.fflag = PFACET_COLOUR_NORMAL,
			    peldata.qmd3.vflag = PVERT_COORD_COLOUR_NORMAL,
			    peldata.qmd3.colr_model = PMODEL_HSV,
			    &peldata.qmd3.dim,
			    &facet_arr,
			    &vertex_arr);
		peldata.qmd3.fdata = facet_arr;
		peldata.qmd3.vdata = vertex_arr;
		element_test(testcase, STR1, ++curr_element,
			     PELEM_QUAD_MESH3_DATA,
			     &peldata, "PELEM_QUAD_MESH3_DATA");
		break;
	    case 91:
		/*
		 *## PELEM_SURF_APPROX_CRIT
		 */
	        pset_surf_approx(peldata.surf_approx.type = 
				            PSURF_CHORDAL_SIZE_WC,
				 peldata.surf_approx.u_val = 0.5,
				 peldata.surf_approx.v_val = 0.4);
		element_test(testcase, STR1, ++curr_element,
			     PELEM_SURF_APPROX_CRIT,
			     &peldata, "PELEM_SURF_APPROX_CRIT");
		break;
	    case 92:
		/*
		 *## PELEM_TEXT_COLR
		 */
		pgcolr.type = PMODEL_HLS;
		pgcolr.val.general.x = 0.7;
		pgcolr.val.general.y = 0.3;
		pgcolr.val.general.z = 0.9;
		pset_text_colr(&pgcolr);
		peldata.colr = pgcolr;
		element_test(testcase, STR1, ++curr_element,
			     PELEM_TEXT_COLR,
			     &peldata, "PELEM_TEXT_COLR");
		break;
	    case 93:
		/* 
		 *## PELEM_TRI_STRIP3_DATA
		 */
		/* Make up some bogus data for a 2 triangle strip. */
		/* facets: */
		for (i=0; i<2; i++) {
		    conorms[i].colr.direct.hsv.hue = 0.08 * i;
		    conorms[i].colr.direct.hsv.satur = 0.1 * i;
		    conorms[i].colr.direct.hsv.value = 0.4 * i;
		    conorms[i].norm = normals1[2-i];
		}
		facet_arr.conorms = conorms;

	        /* vertices: make up points, colors, normals */
		for (i=0; i<4; i++) {
		    ptconorms[i].point = ppoint3s_b[3-i];
		    ptconorms[i].colr.direct.hsv.hue = ppoint3s_b[i].z;
		    ptconorms[i].colr.direct.hsv.satur = ppoint3s_b[i].y;
		    ptconorms[i].colr.direct.hsv.value = ppoint3s_b[i].x;
		    ptconorms[i].norm = pvector3_array[3-i];
		}
		vertex_arr.ptconorms = ptconorms;
		ptri_strip3_data(peldata.tsd3.fflag = PFACET_COLOUR_NORMAL,
			    peldata.tsd3.vflag = PVERT_COORD_COLOUR_NORMAL,
			    peldata.tsd3.colr_model = PMODEL_HSV,
			    peldata.tsd3.nv = 4,
			    &facet_arr,
			    &vertex_arr);
		peldata.tsd3.fdata = facet_arr;
		peldata.tsd3.vdata = vertex_arr;
		element_test(testcase, STR1, ++curr_element,
			     PELEM_TRI_STRIP3_DATA,
			     &peldata, "PELEM_TRI_STRIP3_DATA");
		break;


		/************** END OF TEST CASES *********************/
		/* IF ADDING MORE, PLEASE ADJUST NUMBER IN OUTPUT     */
		/* STRING OF tabort() CALL BELOW!                     */
		/******************************************************/
	    default:
		tabort("ERROR: invalid argument %s\n  arguments should be [-+][acp] or an integer from 1 to 93\n", argv[argument]);
	    }
	}
    }   
    tendtest();
    return (0);
}
