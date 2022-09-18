
/* $XConsortium: wdt.h,v 5.6 91/11/26 16:01:32 hersh Exp $ */

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
 * wdt.h: implementation dependent data for workstation description table
 */

/* JSH - include so that MAXFLOAT is defined */
#if !defined(X_NOT_STDC_ENV) && (__STDC__ || !defined(sun))
#include <float.h>
#endif
#ifndef MAXFLOAT
#ifdef FLT_MAX
#define MAXFLOAT FLT_MAX
#else
#ifdef vax
#define MAXFLOAT ((float)1.701411733192644299e+38)
#else
#define MAXFLOAT ((float)3.40282346638528860e+38)
#endif /* vax */
#endif /* FLT_MAX */
#endif /* MAXFLOAT */

#ifdef PHIGS_WS_TYPE_X_TOOL

#define WSTYPE  "colour X tool"

/* ws connection id */
Pconnid ws_connid = NULL;

/* macro for opening a "tool" type workstation */
#define OPEN_WS1()  popen_ws(1, ws_connid, phigs_ws_type_x_tool);

#endif

#ifdef PHIGS_WS_TYPE_X_DRAWABLE

#define WSTYPE  "colour X drawable"

Display *ws_display;
Window ws_window;
Pconnid_x_drawable ws_conn;

/* ws connection id */
Pconnid ws_connid;

#define WIN_WIDTH 100
#define WIN_HEIGHT 100
#define WIN_X 0
#define WIN_Y 0

/* macro for opening a "xdrawable" type workstation */
#define OPEN_WS1()  \
	{\
		i_make_xwindow( &ws_display,&ws_window, &ws_conn, \
			WIN_X,WIN_Y,WIN_WIDTH,WIN_HEIGHT);\
		popen_ws(1, &ws_conn, phigs_ws_type_x_drawable);\
		ws_connid = (Pconnid) &ws_conn;\
	}



#endif


/*****************************************************
 * Section 1 - 
 * Data used by "inquire xxx facilities"  (wdt1.c)
 *****************************************************/

/* 
 * HLHSR 
 */

#ifdef INSPEX_MONOCHROME_WS
#endif

/* number and list of available HLHSR identifiers */
Pint num_hlhsr_id = 2;
Pint list_hlhsr_id[] = { PHIGS_HLHSR_ID_OFF, PHIGS_HLHSR_ID_ON };

/* number and list of available HLHSR modes */
Pint num_hlhsr_mode = 1;
Pint list_hlhsr_mode[] = { PHIGS_HLHSR_MODE_NONE };

/* 
 * View 
 */

/* number of predefined view indices */
Pint num_pred_view_idx = 6;

/* 
 * Line 
 */

/* number and list of available line types */
Pint num_line_type = 4;
Pint list_line_type[] = { PLINE_SOLID, PLINE_DASH, PLINE_DOT, PLINE_DASH_DOT };


/* number of available, nominal, minimum and maximum linewidths */
Pint num_line_width = 1;
Pfloat nom_line_width = 1.0;
Pfloat min_line_width = 1.0;
Pfloat max_line_width = 4294967296.0;

/* number of predefined polyline indices */
Pint num_pred_line_idx = 5;


/* 
 * Marker 
 */

/* number and list of available marker types */
Pint num_marker_type = 5;
Pint list_marker_type[] = { PMARKER_DOT, PMARKER_PLUS, PMARKER_ASTERISK, PMARKER_CIRCLE, PMARKER_CROSS };


/* number of available, nominal, minimum and maximum marker size */
Pint num_marker_size = 1;
Pfloat nom_marker_size = 1.0;
Pfloat min_marker_size = 1.0;
Pfloat max_marker_size = 4294967296.0;

/* number of predefined marker indices */
Pint num_pred_marker_idx = 5;

/* 
 * Text 
 */

/* number and list of text fonts and precision pairs */
Pint num_font_precision = 3;
Ptext_font_prec list_font_precision[] = { {1,PPREC_STRING}, 
                                     {1,PPREC_CHAR},
                                     {1,PPREC_STROKE} };

/* number of available, minimum, maximum character expansion factors */
Pint num_char_exp = 0.0;
Pfloat min_char_exp = 0.0;
Pfloat max_char_exp = MAXFLOAT;

/* number of available, minimum, maximum character heights */
Pint num_char_height = 0.0;
Pfloat min_char_height = 0.0;
Pfloat max_char_height = MAXFLOAT;

/* number of predefined text indices */
Pint num_pred_text_idx = 6;

/* 
 * Annotation text 
 */

/* number and list of annotation styles */
Pint num_anno_style = 2;
Pint list_anno_style[] = { 1,2 };

/* number of available, minimum, maximum annotation character heights */
Pint num_anno_char_height = 0.0;
Pfloat min_anno_char_height = 0.0;
Pfloat max_anno_char_height = MAXFLOAT;


/* 
 * Interior 
 */

/* number and list of available interior styles */
Pint num_interior_style = 3;
Pint list_interior_style[] = { PSTYLE_HOLLOW, PSTYLE_SOLID, PSTYLE_EMPTY };

/* number and list of available hatch styles */
Pint num_hatch_style = 0;
Pint list_hatch_style[] = { NULL };

/* number of predefined interior indices */
Pint num_pred_interior_idx = 5;

/*
 * Pattern
 */

/* number of predefined pattern indices */
Pint num_pred_pattern_idx = 0;

/* 
 * Edge 
 */

/* number and list of available edge types */
Pint num_edge_type = 4;
Pint list_edge_type[] = { PLINE_SOLID, PLINE_DASH, PLINE_DOT, PLINE_DASH_DOT };


/* number of available, nominal, minimum and maximum edge widths */
Pint num_edge_width = 1;
Pfloat nom_edge_width = 1.0;
Pfloat min_edge_width = 1.0;
Pfloat max_edge_width = 4294967296.0;

/* number of predefined edge indices */
Pint num_pred_edge_idx = 5;

/* 
 * Colour Model
 */

/* number and list of available, default colour models */
Pint num_col_model = 1;
Pint list_col_model[] = {PMODEL_RGB };
Pint def_col_model = PMODEL_RGB;


/*
 * Colour
 */

#ifdef INSPEX_MONOCHROME_WS
#endif

/* luminance values and chromaticity coordinates of display primaries */
/*
Pchrom_coeff chromaticity[3] = { {0.628,0.346}, {0.268,0.588}, {0.150,0.070} };
*/

/* colour availability */
Pcolr_avail col_avail = PAVAIL_COLR;

/* number of available, number of predefined colour indices */
Pint num_col_idx = 256;
Pint num_pred_col_idx = 8;


/***************************************************
 * Section 2 - 
 * Data used by "inqure predefined xxx", 
 * and "inqure list of xxx indices" (wdt2.c)
 ***************************************************/

/*
   Note: The nth element of "pred_xxx_reps" refers to 
	 the nth element of "list_pred_xxx_idx" 
*/


/* 
   list of predifined view indices  and
   tables of predefined view representation: 
	. view index 
	. view representation:
		orientation and mapping matrix, clipping limits,
		x-y, back and front clipping indicator
*/

Pint list_pred_view_idx[] = {0,1,2,3,4,5};
Pview_rep3 pred_view_reps[] = {
	/* view 0 */
	{{{1.0, 0.0, 0.0, 0.0},
	{0.0, 1.0, 0.0, 0.0},
	{0.0, 0.0, 1.0, 0.0},
	{0.0, 0.0, 0.0, 1.0}},
	{{1.0, 0.0, 0.0, 0.0},
	{0.0, 1.0, 0.0, 0.0},
	{0.0, 0.0, 1.0, 0.0},
	{0.0, 0.0, 0.0, 1.0}},
	{0.0, 1.0, 0.0, 1.0, 0.0, 1.0},
	PIND_CLIP, PIND_CLIP, PIND_CLIP} ,
	/* view 1 */
	{{{1.0, 0.0, 0.0, 0.0},
	{0.0, 1.0, 0.0, 0.0},
	{0.0, 0.0, 1.0, 0.0},
	{0.0, 0.0, 0.0, 1.0}},
	{{0.3, 0.0, 0.0, 0.1},
	{0.0, 0.3, 0.0, 0.1},
	{0.0, 0.0, 1.0, 0.0},
	{0.0, 0.0, 0.0, 1.0}},
	{0.0, 1.0, 0.0, 1.0, 0.0, 1.0},
	PIND_CLIP, PIND_CLIP, PIND_CLIP} ,
	/* view 2 */
	{{{1.0, 0.0, 0.0, 0.0},
	{0.0, 0.0, -1.0, 0.0},
	{0.0, 1.0, 0.0, 0.0},
	{0.0, 0.0, 0.0, 1.0}},
	{{0.3, 0.0, 0.0, 0.1},
	{0.0, 0.3, 0.0, 0.9},
	{0.0, 0.0, 1.0, 0.0},
	{0.0, 0.0, 0.0, 1.0}},
	{0.0, 1.0, 0.0, 1.0, 0.0, 1.0},
	PIND_CLIP, PIND_CLIP, PIND_CLIP} ,
	/* view 3 */
	{{{0.0, 0.0, -1.0, 0.0},
	{0.0, 1.0, 0.0, 0.0},
	{1.0, 0.0, 0.0, 0.0},
	{0.0, 0.0, 0.0, 1.0}},
	{{0.3, 0.0, 0.0, 0.9},
	{0.0, 0.3, 0.0, 0.1},
	{0.0, 0.0, 1.0, 0.0},
	{0.0, 0.0, 0.0, 1.0}},
	{0.0, 1.0, 0.0, 1.0, 0.0, 1.0},
	PIND_CLIP, PIND_CLIP, PIND_CLIP} ,
	/* view 4 */
	{{{0.7071, 0.0, -0.7071, 0.0},
	{-0.4082, 0.8165, -0.4082, 0.0},
	{0.5774, 0.5774, 0.5774, 0.0},
	{0.0, 0.0, 0.0, 1.0}},
	{{0.2121, 0.0, 0.0, 0.75},
	{0.0, 0.2121, 0.0, 0.75},
	{0.0, 0.0, 0.5774, 0.0},
	{0.0, 0.0, 0.0, 1.0}},
	{0.0, 1.0, 0.0, 1.0, 0.0, 1.0},
	PIND_CLIP, PIND_CLIP, PIND_CLIP},
	/* view 5 */
	{{{0.7071, 0.0, -0.7071, 0.0},
	{-0.4082, 0.8165, -0.4082, 0.0},
	{0.5774, 0.5774, 0.5774, 0.0},
	{0.0, 0.0, 0.0, 1.0}},
	{{0.3536, 0.0, -0.025, 0.5},
	{0.0, 0.3536, -0.025, 0.5},
	{0.0, 0.0, 0.5274, 0.0},
	{0.0, 0.0, -0.05, 1.0}},
	{0.0, 1.0, 0.0, 1.0, 0.0, 1.0},
	PIND_CLIP, PIND_CLIP, PIND_CLIP}
	};

/* 
   list of predifined polyline indices  and
   table of predefined polyline bundles: type, width and colour 
*/
Pint list_pred_line_idx[] = {1,2,3,4,5};
Pline_bundle pred_line_reps[] = { {PLINE_SOLID, 1.0, 1} ,
                                  {PLINE_DASH, 1.0, 1} ,
                                  {PLINE_DOT, 1.0, 1} ,
                                  {PLINE_DASH_DOT, 1.0, 1} ,
                                  {PLINE_SOLID, 2.0, 1} 
				};

/* 
   list of predifined polymarker indices  and
   table of predefined polymarker bundles: type, size and colour 
*/
Pint list_pred_marker_idx[] = {1,2,3,4,5};
Pmarker_bundle pred_marker_reps[] = { {PMARKER_DOT, 1.0, 1}, 
                                  {PMARKER_PLUS, 1.0, 1} ,
                                  {PMARKER_ASTERISK, 1.0, 1} ,
                                  {PMARKER_CIRCLE, 1.0, 1} ,
                                  {PMARKER_CROSS, 1.0, 1} 
				};

/*
   list of predifined text indices  and
   table of predefined text bundles: 
	text font and precision, 
	character expansion factor and spacing 
	text colour
*/
Pint list_pred_text_idx[] = {1,2,3,4,5,6};
Ptext_bundle pred_text_reps[] = { {1, PPREC_STROKE, 1.0, 0.0, 1}, 
                                  {1, PPREC_STROKE, 1.5, 0.0, 1}, 
                                  {1, PPREC_STROKE, 2.0, 0.0, 1}, 
                                  {1, PPREC_STROKE, 2.5, 0.0, 1}, 
                                  {1, PPREC_STROKE, 3.0, 0.0, 1}, 
                                  {1, PPREC_STROKE, 3.5, 0.0, 1}
				};
		
/*
   list of predifined interior indices  and
   table of predefined interior bundles: style, index and colour 
*/
Pint list_pred_interior_idx[] = {1,2,3,4,5};
Pint_bundle pred_interior_reps[] = { {PSTYLE_SOLID, 1, 1},
                                     {PSTYLE_HOLLOW, 1, 1},
                                     {PSTYLE_EMPTY, 1, 1},
                                     {PSTYLE_SOLID, 1, 1},
                                     {PSTYLE_SOLID, 1, 1}
				};

/*
   list of predifined edge indices  and
   table of predefined edge bundles: flag, type, scale and colour 
*/
Pint list_pred_edge_idx[] = {1,2,3,4,5};
Pedge_bundle pred_edge_reps[] = { {PEDGE_ON, PLINE_SOLID, 1.0, 1},
                                  {PEDGE_ON, PLINE_DASH, 1.0, 1},
                                  {PEDGE_ON, PLINE_DOT, 1.0, 1},
                                  {PEDGE_ON, PLINE_DASH_DOT, 1.0, 1},
                                  {PEDGE_ON, PLINE_SOLID, 3.0, 1}
				};

/*
   list of predifined pattern indices  and
   table of predefined pattern bundles: flag, type, scale and colour 
*/
Pint list_pred_pattern_idx[] = {NULL};
Ppat_rep pred_pattern_reps[] = { {NULL} };

/*
   list of predifined colour indices  and
   table of predefined colour bundles: x,y,z 
*/
Pint list_pred_col_idx[] = {0,1,2,3,4,5,6,7};
Pfloat pred_col_reps[][3] = { {0.0,0.0,0.0}, 
			{1.0,1.0,1.0},
			{1.0,0.0,0.0},
			{0.0,1.0,0.0},
			{0.0,0.0,1.0},
			{1.0,1.0,0.0},
			{0.0,1.0,1.0},
			{1.0,0.0,1.0}};


/*******************************************
 * Section 3 - 
 * Data used by misc inquiries  (wdt3.c)
 *******************************************/

/* workstation category */
Pws_cat wscat = PCAT_OUTIN;

/* workstation classification */
Pws_class wsclass = PCLASS_RASTER;

/* workstation display size */
Pdc_units device_coor_units = PDC_OTHER;

#ifdef PHIGS_WS_TYPE_X_TOOL
	Pvec device_max_disp_size = {600.0, 600.0};
	Pint_size raster_max_disp_size = {600, 600};
#endif 
#ifdef PHIGS_WS_TYPE_X_DRAWABLE
	Pvec device_max_disp_size = {WIN_WIDTH , WIN_HEIGHT};
	Pint_size raster_max_disp_size = {WIN_WIDTH, WIN_HEIGHT};
#endif
 
/* workstation display size3 */
Pdc_units device_coor_units3 = PDC_OTHER;

#ifdef PHIGS_WS_TYPE_X_TOOL
	Pvec3 device_max_disp_size3 = {600.0, 600.0, 1.0};
	Pint_size3 raster_max_disp_size3 = {600, 600, 8};
#endif

#ifdef PHIGS_WS_TYPE_X_DRAWABLE
	Pvec3 device_max_disp_size3 = {WIN_WIDTH, WIN_HEIGHT, 1.0};
	Pint_size3 raster_max_disp_size3 = {WIN_WIDTH, WIN_HEIGHT, 8};
#endif

/* 
 * GDP
 */

/*
   Note: The nth element of "list_gdp_attrs" must corresponds to 
	 the nth element of "list_gdp" and "list_gdp_num_attrs"
*/

/* number and list of available Generalized Drawing Primitives */
/* for each gdp, the number and list of attributes used */
Pint num_gdp = 0;
Pint list_gdp[] = { NULL };
Pint list_gdp_num_attrs[] = { NULL };
Pattrs list_gdp_attrs[][5] = {NULL};

/* 
 * GDP3
 */
/*
   Note: The nth element of "list_gdp3_attrs" must corresponds to 
	 the nth element of "list_gdp3" and "list_gdp3_num_attrs"
*/

/* number and list of available Generalized Drawing Primitives 3 */
/* for each gdp3, the number and list of attributes used */
Pint num_gdp3 = 0;
Pint list_gdp3[] = { NULL };
Pint list_gdp3_num_attrs[] = { NULL };
Pattrs list_gdp3_attrs[][5] = {NULL};

/* 
 * GSE 
 */

/* number and list of available Generalized Structure Elements */
Pint num_gse = 0;
Pint list_gse[] = { NULL };

/* 
   dynamic modification of workstation : 
   	polyline,polymarker,text,interior,edge,pattern,
	and colour bundle representation;
   	view representation; workstation transformation; 
   	highlighting and invisibility filter; HLHSR 
*/

Pdyns_ws_attrs ws_dyn_mods = { PDYN_IRG, PDYN_IRG, PDYN_IRG, PDYN_IRG, PDYN_IRG, PDYN_IRG, PDYN_IRG, 
		      PDYN_IRG, PDYN_IRG, PDYN_IRG, PDYN_IRG, PDYN_IRG };

/* 
   dynamic modification of structure : 
	structure content modification, 
	post structure, unpost structure,
	delete structure, reference modification 
*/

Pdyns_structs str_dyn_mods = { PDYN_IRG, PDYN_IRG, PDYN_IRG, PDYN_IRG, PDYN_IRG };

/* default display deferral/modification mode */
Pdefer_mode  def_defer_mode = PDEFER_ASAP;
Pmod_mode  def_mod_mode = PMODE_UQUM;

/* number of display priorities supported */
Pint num_display_pri = 0;

/* 
   workstation table length :
   	polyline, polymarker, text, interior, edge, pattern, colour, view 
*/
Pws_st_tables ws_tbl_lengths  =  { 20, 20, 20, 20, 20, 0, 256, 6 };


/*******************************************
 * Section 4 - 
 * Data used by input inquiries  (wdt4.c)
 *******************************************/

/* 
  number of logical device of class:
	locator, stroke, valuator, pick and string
*/

Pint  num_locator_dev = 3;
Pint  num_stroke_dev = 1;
Pint  num_valuator_dev = 12;
Pint  num_choice_dev = 3;
Pint  num_pick_dev = 1;
Pint  num_string_dev = 1;

/*
  default data for every logical device of class locator(3):
	initial position, list of prompt and echo types and echo area/volume.

  The followings are :
	list of device number,
	list of initial positions,
	list of number of available prompt and echo types,
	list of list of available prompt and echo types,
	list of echo areas/volume,
  Note: 
	1. the nth element of list_* refers to the nth element of
	   list_locator_dev_num[].

	2. locator data records are ommited, since they will not be verified 
*/

Pint list_locator_dev_num [] = {1,2,3};
Ppoint list_locator_init_pos[] = {{0.0,0.0},{0.0,0.0},{0.0,0.0}};
Pint list_locator_num_pet[] = {1,1,1};
Pint list_locator_list_pet[][10] = { {1},{1},{1} };

#ifdef PHIGS_WS_TYPE_X_TOOL
Plimit list_locator_def_echo_area[] = { {0.0,600.0, 0.0,600.0},
                                        {0.0,600.0, 0.0,600.0},
                                        {0.0,600.0, 0.0,600.0}};
#endif
#ifdef PHIGS_WS_TYPE_X_DRAWABLE
Plimit list_locator_def_echo_area[] = { {0.0,WIN_WIDTH,0.0,WIN_HEIGHT},
                                        {0.0,WIN_WIDTH, 0.0,WIN_HEIGHT},
                                        {0.0,WIN_WIDTH, 0.0,WIN_HEIGHT}};
#endif

Pint list_locator3_dev_num [] = {1,2,3};
Ppoint3 list_locator3_init_pos[] = {{0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0}};
Pint list_locator3_num_pet[] = {1,1,1};
Pint list_locator3_list_pet[][10] = { {1},{1},{1} };

#ifdef PHIGS_WS_TYPE_X_TOOL
Plimit3 list_locator3_def_echo_volume[] = { {0.0,600.0, 0.0,600.0, 0.0,1.0},
                                            {0.0,600.0, 0.0,600.0, 0.0,1.0},
                                            {0.0,600.0, 0.0,600.0, 0.0,1.0} };
#endif
#ifdef PHIGS_WS_TYPE_X_DRAWABLE
Plimit3 list_locator3_def_echo_volume[] = { 
				{0.0,WIN_WIDTH,0.0,WIN_HEIGHT,0.0,1.0},
                                {0.0,WIN_WIDTH,0.0,WIN_HEIGHT, 0.0,1.0},
                                {0.0,WIN_WIDTH,0.0,WIN_HEIGHT, 0.0,1.0} };
#endif

/*
  default data for every logical device of class choice(3):
	max # of choices, list of prompt and echo types and echo area/volume.

  The followings are :
	list of device number,
	list of maximum number of choices,
	list of number of available prompt and echo types,
	list of list of available prompt and echo types,
	list of echo areas/volume,
  Note: 
	1. the nth element of list_* refers to the nth element of
	   list_choice_dev_num[].

	2. choice data records are ommited, since they will not be verified 
*/

Pint list_choice_dev_num [] = {1};
Pint list_choice_max_num_choice[] = {100};
Pint list_choice_num_pet[] = {2};
Pint list_choice_list_pet[][10] = { {1,3} };
#ifdef PHIGS_WS_TYPE_X_TOOL
Plimit list_choice_def_echo_area[] = { {0.0,600.0, 0.0,600.0} };
#endif
#ifdef PHIGS_WS_TYPE_X_DRAWABLE
Plimit list_choice_def_echo_area[] = { {0.0,WIN_WIDTH,0.0,WIN_HEIGHT} };
#endif

Pint list_choice3_dev_num [] = {1};
Pint list_choice3_max_num_choice[] = {100};
Pint list_choice3_num_pet[] = {2};
Pint list_choice3_list_pet[][10] = { {1,3} };
#ifdef PHIGS_WS_TYPE_X_TOOL
Plimit3 list_choice3_def_echo_volume[] = { {0.0,600.0, 0.0,600.0, 0.0,1.0} };
#endif
#ifdef PHIGS_WS_TYPE_X_DRAWABLE
Plimit3 list_choice3_def_echo_volume[] = { {0.0,WIN_WIDTH,0.0,WIN_HEIGHT,0.0,1.0} };
#endif
 
/*
  default data for every logical device of class valuator(3):
	initial position, list of prompt and echo types and echo area/volume.

  The followings are :
	list of device number,
	list of default initial value,
	list of number of available prompt and echo types,
	list of list of available prompt and echo types,
	list of echo areas/volume,
  Note: 
	1. the nth element of list_* refers to the nth element of
	   list_valuator_dev_num[].

	2. valuator data records are ommited, since they will not be verified 
*/

Pint list_valuator_dev_num [] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
Pfloat list_valuator_def_init_value[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
Pint list_valuator_num_pet[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
Pint list_valuator_list_pet[][10] = { {1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1} };
#ifdef PHIGS_WS_TYPE_X_TOOL
Plimit list_valuator_def_echo_area[] = { {0.0,600.0, 0.0,600.0} ,
{0.0,600.0, 0.0,600.0} , {0.0,600.0, 0.0,600.0} , {0.0,600.0, 0.0,600.0} ,
{0.0,600.0, 0.0,600.0} , {0.0,600.0, 0.0,600.0} , {0.0,600.0, 0.0,600.0} ,
{0.0,600.0, 0.0,600.0} , {0.0,600.0, 0.0,600.0} , {0.0,600.0, 0.0,600.0} ,
{0.0,600.0, 0.0,600.0} , {0.0,600.0, 0.0,600.0} };
#endif
#ifdef PHIGS_WS_TYPE_X_DRAWABLE
Plimit list_valuator_def_echo_area[] = { {0.0,WIN_WIDTH,0.0,WIN_HEIGHT},
{0.0,WIN_WIDTH,0.0,WIN_HEIGHT}, {0.0,WIN_WIDTH,0.0,WIN_HEIGHT},
{0.0,WIN_WIDTH,0.0,WIN_HEIGHT}, {0.0,WIN_WIDTH,0.0,WIN_HEIGHT},
{0.0,WIN_WIDTH,0.0,WIN_HEIGHT}, {0.0,WIN_WIDTH,0.0,WIN_HEIGHT},
{0.0,WIN_WIDTH,0.0,WIN_HEIGHT}, {0.0,WIN_WIDTH,0.0,WIN_HEIGHT},
{0.0,WIN_WIDTH,0.0,WIN_HEIGHT}, {0.0,WIN_WIDTH,0.0,WIN_HEIGHT},
{0.0,WIN_WIDTH,0.0,WIN_HEIGHT} };
#endif

Pint list_valuator3_dev_num [] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
Pfloat list_valuator3_def_init_value[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
Pint list_valuator3_num_pet[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
Pint list_valuator3_list_pet[][10] = { {1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1} };
#ifdef PHIGS_WS_TYPE_X_TOOL
Plimit3 list_valuator3_def_echo_volume[] = { {0.0,600.0, 0.0,600.0, 0.0,1.0},
{0.0,600.0, 0.0,600.0, 0.0,1.0}, {0.0,600.0, 0.0,600.0, 0.0,1.0},
{0.0,600.0, 0.0,600.0, 0.0,1.0}, {0.0,600.0, 0.0,600.0, 0.0,1.0},
{0.0,600.0, 0.0,600.0, 0.0,1.0}, {0.0,600.0, 0.0,600.0, 0.0,1.0},
{0.0,600.0, 0.0,600.0, 0.0,1.0}, {0.0,600.0, 0.0,600.0, 0.0,1.0},
{0.0,600.0, 0.0,600.0, 0.0,1.0}, {0.0,600.0, 0.0,600.0, 0.0,1.0},
{0.0,600.0, 0.0,600.0, 0.0,1.0} };
#endif
#ifdef PHIGS_WS_TYPE_X_DRAWABLE
Plimit3 list_valuator3_def_echo_volume[] = { {0.0,WIN_WIDTH,0.0,WIN_HEIGHT,0.0,1.0},
{0.0,WIN_WIDTH,0.0,WIN_HEIGHT,0.0,1.0}, {0.0,WIN_WIDTH,0.0,WIN_HEIGHT,0.0,1.0},
{0.0,WIN_WIDTH,0.0,WIN_HEIGHT,0.0,1.0}, {0.0,WIN_WIDTH,0.0,WIN_HEIGHT,0.0,1.0},
{0.0,WIN_WIDTH,0.0,WIN_HEIGHT,0.0,1.0}, {0.0,WIN_WIDTH,0.0,WIN_HEIGHT,0.0,1.0},
{0.0,WIN_WIDTH,0.0,WIN_HEIGHT,0.0,1.0}, {0.0,WIN_WIDTH,0.0,WIN_HEIGHT,0.0,1.0},
{0.0,WIN_WIDTH,0.0,WIN_HEIGHT,0.0,1.0}, {0.0,WIN_WIDTH,0.0,WIN_HEIGHT,0.0,1.0},
{0.0,WIN_WIDTH,0.0,WIN_HEIGHT,0.0,1.0} };
#endif
/*
  default data for every logical device of class stroke(3):
	initial position, list of prompt and echo types and echo area/volume.

  The followings are :
	list of device number,
	list of available input buffer size,
	list of number of available prompt and echo types,
	list of list of available prompt and echo types,
	list of echo areas/volume,
  Note: 
	1. the nth element of list_* refers to the nth element of
	   list_stroke_dev_num[].

	2. stroke data records are ommited, since they will not be verified 
*/

Pint list_stroke_dev_num [] = {1};
Pint list_stroke_avail_bufsize[] = {200};
Pint list_stroke_num_pet[] = {1};
Pint list_stroke_list_pet[][10] = { {1} };
#ifdef PHIGS_WS_TYPE_X_TOOL
Plimit list_stroke_def_echo_area[] = { {0.0,600.0, 0.0,600.0} };
#endif
#ifdef PHIGS_WS_TYPE_X_DRAWABLE
Plimit list_stroke_def_echo_area[] = { {0.0,WIN_WIDTH,0.0,WIN_HEIGHT} };
#endif

Pint list_stroke3_dev_num [] = {1};
Pint list_stroke3_avail_bufsize[] = {200};
Pint list_stroke3_num_pet[] = {1};
Pint list_stroke3_list_pet[][10] = { {1} };
#ifdef PHIGS_WS_TYPE_X_TOOL
Plimit3 list_stroke3_def_echo_volume[] = { {0.0,600.0, 0.0,600.0, 0.0,1.0} };
#endif
#ifdef PHIGS_WS_TYPE_X_DRAWABLE
Plimit3 list_stroke3_def_echo_volume[] = { {0.0,WIN_WIDTH,0.0,WIN_HEIGHT,0.0,1.0} };
#endif

/*
  default data for every logical device of class string(3):
	initial position, list of prompt and echo types and echo area/volume.

  The followings are :
	list of device number,
	list of available input buffer size,
	list of number of available prompt and echo types,
	list of list of available prompt and echo types,
	list of echo areas/volume,
  Note: 
	1. the nth element of list_* refers to the nth element of
	   list_string_dev_num[].

	2. string data records are ommited, since they will not be verified 
*/

Pint list_string_dev_num [] = {1};
Pint list_string_avail_bufsize[] = {1024};
Pint list_string_num_pet[] = {1};
Pint list_string_list_pet[][10] = { {1} };
#ifdef PHIGS_WS_TYPE_X_TOOL
Plimit list_string_def_echo_area[] = { {0.0,600.0, 0.0,600.0} };
#endif
#ifdef PHIGS_WS_TYPE_X_DRAWABLE
Plimit list_string_def_echo_area[] = { {0.0,WIN_WIDTH,0.0,WIN_HEIGHT} };
#endif

Pint list_string3_dev_num [] = {1};
Pint list_string3_avail_bufsize[] = {1024};
Pint list_string3_num_pet[] = {1};
Pint list_string3_list_pet[][10] = { {1} };
#ifdef PHIGS_WS_TYPE_X_TOOL
Plimit3 list_string3_def_echo_volume[] = { {0.0,600.0, 0.0,600.0, 0.0,1.0} };
#endif
#ifdef PHIGS_WS_TYPE_X_DRAWABLE
Plimit3 list_string3_def_echo_volume[] = { {0.0,WIN_WIDTH,0.0,WIN_HEIGHT,0.0,1.0} };
#endif

/*
  default data for every logical device of class pick(3):
	initial position, list of prompt and echo types and echo area/volume.

  The followings are :
	list of device number,
	list of number of available prompt and echo types,
	list of list of available prompt and echo types,
	list of echo areas/volume,
  Note: 
	1. the nth element of list_* refers to the nth element of
	   list_pick_dev_num[].

	2. pick data records are ommited, since they will not be verified 
*/

Pint list_pick_dev_num [] = {1};
Pint list_pick_num_pet[] = {1};
Pint list_pick_list_pet[][10] = { {1} };
#ifdef PHIGS_WS_TYPE_X_TOOL
Plimit list_pick_def_echo_area[] = { {0.0,600.0, 0.0,600.0} };
#endif
#ifdef PHIGS_WS_TYPE_X_DRAWABLE
Plimit list_pick_def_echo_area[] = { {0.0,WIN_WIDTH,0.0,WIN_HEIGHT} };
#endif

Pint list_pick3_dev_num [] = {1};
Pint list_pick3_num_pet[] = {1};
Pint list_pick3_list_pet[][10] = { {1} };
#ifdef PHIGS_WS_TYPE_X_TOOL
Plimit3 list_pick3_def_echo_volume[] = { {0.0,600.0, 0.0,600.0, 0.0,1.0} };
#endif
#ifdef PHIGS_WS_TYPE_X_DRAWABLE
Plimit3 list_pick3_def_echo_volume[] = { {0.0,WIN_WIDTH,0.0,WIN_HEIGHT,0.0,1.0} };
#endif

/*******************************************
 * Section 5 - 
 * Data used by PHIGS+ "inquire xxx facilities"  (wdt5.c)
 * and PHIGS+ "inqure workstation table length plus"
 *******************************************/


/* number and list of available line shading methods */
Pint num_line_shading_method = 1;
Pint list_line_shading_method[] = { PSD_NONE};

/* number and list of available interior shading methods */
Pint num_interior_shading_method = 1;
Pint list_interior_shading_method[] = { PSD_NONE};

/* number and list of available reflectance equations */
Pint num_reflectance_equation = 4;
Pint list_reflectance_equation[] = { PREFL_NONE,
	PREFL_AMBIENT,PREFL_AMB_DIFF,PREFL_AMB_DIFF_SPEC };

/* number of predefined depth cue indices */
Pint num_pred_depth_cue_idx = 2;

/* number and list of available light source types */
Pint num_light_src_type = 4;
Pint list_light_src_type[] = { PLIGHT_AMBIENT, PLIGHT_DIRECTIONAL,
                               PLIGHT_POSITIONAL, PLIGHT_SPOT};

/* maximum number of simultaneously active non-ambient lights */
Pint max_num_simult_light = 64;

/* number of predefined light source indices */
Pint num_pred_light_src_idx = 2;

/* maximum non-uniform B-spline order */
Pint max_nurb_order = 10;

/* maximum parametric polynomial order */
Pint max_para_poly_order = 0;

/* maximum trimming curve order */
Pint max_trim_curve_order = 6;

/* number of predefined parametric surface indices */
Pint num_pred_para_surface_idx = 0;

/* number and list of available parametric polynomial curve types */
Pint num_para_poly_curve_type = 0;
Pint list_para_poly_curve_type[] = {NULL};

/* number and list of available parametric polynomial surface types */
Pint num_para_poly_surface_type = 0;
Pint list_para_poly_surface_type[] = {NULL};

/* number and list of available curve approximation criteria types */
Pint num_curve_approx_type = 6;
Pint list_curve_approx_type[] = {PCURV_WS_DEP,
	PCURV_CONSTANT_PARAMETRIC_BETWEEN_KNOTS,
	PCURV_CHORDAL_SIZE_WC,
	PCURV_CHORDAL_SIZE_NPC,
	PCURV_CHORDAL_DEVIATION_WC,
	PCURV_CHORDAL_DEVIATION_NPC
	};

/* number and list of available surface approximation criteria types */
Pint num_surface_approx_type = 6;
Pint list_surface_approx_type[] = {PSURF_WS_DEP,
	PSURF_CONSTANT_PARAMETRIC_BETWEEN_KNOTS,
	PSURF_CHORDAL_SIZE_WC,
	PSURF_CHORDAL_SIZE_NPC,
	PSURF_PLANAR_DEVIATION_WC,
	PSURF_PLANAR_DEVIATION_NPC
	};

/* number and list of available trimming curve approximation criteria types */
Pint num_trim_curve_approx_type = 2;
Pint list_trim_curve_approx_type[] = {PCURV_WS_DEP,
	PCURV_CONSTANT_PARAMETRIC_BETWEEN_KNOTS,
	};

/* number and list of available parametric surface characteristics types */
Pint num_para_surface_type = 3;
Pint list_para_surface_type[] = {
	PSC_NONE,
	PSC_WS_DEP,
	PSC_ISOPARAMETRIC_CURVES
	};

/* number and list of available direct colour models */
Pint num_direct_col_model = 1;
Pint list_direct_col_model[] = {PMODEL_RGB};

/* number and list of available rendering colour models */
Pint num_rendering_col_model = 1;
Pint list_rendering_col_model[] = {PRCM_RGB};

/* number and list of colour mapping methods */
Pint num_cmap_method = 2;
Pint list_cmap_method[] = {PCOLR_MAP_TRUE, PCOLR_MAP_PSEUDO};

/* number of predefined colour mapping indices */
Pint num_pred_cmap_idx = 1;

/* 
   PHIGS+ workstation table length :
   	polyline, polymarker, text, interior, edge, pattern, colour, view 
	general interior, depth cue, light source, colour mapping, cull size
*/
Pws_tables_plus ws_tbl_lengths_plus  =  { 20, 20, 20, 20, 20, 0, 256, 6,
				     6, 16, 1};

/* 
   dynamic modification of workstation attributes plus: 
   	light source, depth cue and colour map  representation
*/

Pdyns_ws_attrs_plus ws_dyn_mods_plus = {PDYN_IRG, PDYN_IRG, PDYN_IRG};

/***************************************************
 * Section 6 - 
 * Data used by PHIGS+ "inqure predefined xxx", 
 * and "inqure list of xxx indices" (wdt6.c)
 ***************************************************/

/*
   Note: The nth element of "pred_xxx_reps" refers to 
	 the nth element of "list_pred_xxx_idx" 
*/

/* 
   list of predifined light source indices  and
   table of predefined light source bundles: type, content
   macro to initialize list of predefined light source representations
*/
Pint list_pred_light_src_idx[] = {1,2};
Plight_src_bundle pred_light_src_reps[2]; 
#define INIT_PRED_LIGHT_SRC_REPS() {\
	pred_light_src_reps[0].type = PLIGHT_AMBIENT;\
	pred_light_src_reps[0].rec.ambient.colr.type = PINDIRECT;\
	pred_light_src_reps[0].rec.ambient.colr.val.ind = 1;\
	pred_light_src_reps[1] = pred_light_src_reps[0];\
	}

/* 
   list of predifined depth cue indices  and
   table of predefined depth cue bundles:mode, reference planes, scaling, 
   	general colour
   macro to initialize list of predefined depth cue representations
*/
Pint list_pred_depth_cue_idx[] = {0,1};
Pdcue_bundle pred_depth_cue_reps[2]; 
#define INIT_PRED_DEPTH_CUE_REPS() {\
	pred_depth_cue_reps[0].mode = PSUPPRESSED;\
	pred_depth_cue_reps[0].ref_planes[0] = 0.0;\
	pred_depth_cue_reps[0].ref_planes[1] = 1.0;\
	pred_depth_cue_reps[0].scaling[0] = 0.0;\
	pred_depth_cue_reps[0].scaling[1] = 1.0;\
	pred_depth_cue_reps[0].colr.type = PINDIRECT;\
	pred_depth_cue_reps[0].colr.val.ind = 0;\
	pred_depth_cue_reps[1] = pred_depth_cue_reps[0];\
	pred_depth_cue_reps[1].mode = PALLOWED;\
	}

/* 
   list of predifined colour mapping indices  and
   macro to initialize list of predefined colour mapping representations
*/
Pint list_pred_cmap_idx[] = {0};
Pint pred_cmap_reps_method[1]; 
Pcolr_map_data pred_cmap_reps_data[1]; 
#define INIT_PRED_CMAP_REPS() {\
	pred_cmap_reps_method[0] = PCOLR_MAP_TRUE;\
	}

/* 
   list of predifined polyline indices plus and
   table of predefined polyline bundles plus: type, width and general colour 
   macro to initialize list of predefined line representations plus
*/
Pint list_pred_line_idx_plus[] = {1,2,3,4,5};
Pline_bundle_plus pred_line_reps_plus[5];
#define INIT_PRED_LINE_REPS_PLUS() {\
	pred_line_reps_plus[0].type = PLINE_SOLID;\
	pred_line_reps_plus[0].width = 1.0;\
	pred_line_reps_plus[0].shad_meth = PSD_NONE;\
	pred_line_reps_plus[0].approx_type = PCURV_WS_DEP;\
	pred_line_reps_plus[0].approx_val = 1.0;\
	pred_line_reps_plus[0].colr.type = PINDIRECT;\
	pred_line_reps_plus[0].colr.val.ind = 1;\
	pred_line_reps_plus[1] = pred_line_reps_plus[0];\
	pred_line_reps_plus[2] = pred_line_reps_plus[0];\
	pred_line_reps_plus[3] = pred_line_reps_plus[0];\
	pred_line_reps_plus[4] = pred_line_reps_plus[0];\
	pred_line_reps_plus[1].type = PLINE_DASH;\
	pred_line_reps_plus[2].type = PLINE_DOT;\
	pred_line_reps_plus[3].type = PLINE_DASH_DOT;\
	pred_line_reps_plus[4].width = 2.0;\
	}

/* 
   list of predifined polymarker indices plus and
   table of predefined polymarker bundles plus: type, size and general colour 
   macro to initialize list of predefined marker representations plus
*/
Pint list_pred_marker_idx_plus[] = {1,2,3,4,5};
Pmarker_bundle_plus pred_marker_reps_plus[5];
#define INIT_PRED_MARKER_REPS_PLUS() {\
	pred_marker_reps_plus[0].type = PMARKER_DOT;\
	pred_marker_reps_plus[0].size = 1.0;\
	pred_marker_reps_plus[0].colr.type = PINDIRECT;\
	pred_marker_reps_plus[0].colr.val.ind = 1;\
	pred_marker_reps_plus[1] = pred_marker_reps_plus[0];\
	pred_marker_reps_plus[2] = pred_marker_reps_plus[0];\
	pred_marker_reps_plus[3] = pred_marker_reps_plus[0];\
	pred_marker_reps_plus[4] = pred_marker_reps_plus[0];\
	pred_marker_reps_plus[1].type = PMARKER_PLUS;\
	pred_marker_reps_plus[2].type = PMARKER_ASTERISK;\
	pred_marker_reps_plus[3].type = PMARKER_CIRCLE;\
	pred_marker_reps_plus[4].type = PMARKER_CROSS;\
	}

/*
   list of predifined text indices plus and
   table of predefined text bundles plus: 
	text font and precision, 
	character expansion factor and spacing 
	general text colour
   macro to initialize list of predefined text representations plus
*/
Pint list_pred_text_idx_plus[] = {1,2,3,4,5,6};
Ptext_bundle_plus pred_text_reps_plus[6]; 
#define INIT_PRED_TEXT_REPS_PLUS() {\
	pred_text_reps_plus[0].font = 1;\
	pred_text_reps_plus[0].prec = PPREC_STROKE;\
	pred_text_reps_plus[0].char_expan = 1.0;\
	pred_text_reps_plus[0].char_space = 0.0;\
	pred_text_reps_plus[0].colr.type = PINDIRECT;\
	pred_text_reps_plus[0].colr.val.ind = 1;\
	pred_text_reps_plus[1] = pred_text_reps_plus[0];\
	pred_text_reps_plus[2] = pred_text_reps_plus[0];\
	pred_text_reps_plus[3] = pred_text_reps_plus[0];\
	pred_text_reps_plus[4] = pred_text_reps_plus[0];\
	pred_text_reps_plus[5] = pred_text_reps_plus[0];\
	pred_text_reps_plus[1].char_expan = 1.5;\
	pred_text_reps_plus[2].char_expan = 2.0;\
	pred_text_reps_plus[3].char_expan = 2.5;\
	pred_text_reps_plus[4].char_expan = 3.0;\
	pred_text_reps_plus[5].char_expan = 3.5;\
	}

/*
   list of predifined interior indices plus  and
   table of predefined interior bundles plus: style, index and general colour 
   macro to initialize list of predefined interior representations plus
*/
Pint list_pred_interior_idx_plus[] = {1,2,3,4,5};
Pint_bundle_plus pred_interior_reps_plus[5]; 
#define INIT_PRED_INTERIOR_REPS_PLUS() {\
	pred_interior_reps_plus[0].style = PSTYLE_SOLID;\
	pred_interior_reps_plus[0].style_ind = 1;\
	pred_interior_reps_plus[0].refl_eqn = PREFL_NONE;\
	pred_interior_reps_plus[0].shad_meth = PSD_NONE;\
	pred_interior_reps_plus[0].refl_props.ambient_coef = 1.0;\
	pred_interior_reps_plus[0].refl_props.diffuse_coef = 1.0;\
	pred_interior_reps_plus[0].refl_props.specular_coef = 0.0;\
	pred_interior_reps_plus[0].refl_props.specular_colr.type = PINDIRECT;\
	pred_interior_reps_plus[0].refl_props.specular_colr.val.ind = 1;\
	pred_interior_reps_plus[0].refl_props.specular_exp = 0.0;\
	pred_interior_reps_plus[0].colr.type = PINDIRECT;\
	pred_interior_reps_plus[0].colr.val.ind = 1;\
	pred_interior_reps_plus[0].back_style = PSTYLE_SOLID;\
	pred_interior_reps_plus[0].back_style_ind = 1;\
	pred_interior_reps_plus[0].back_refl_eqn = PREFL_NONE;\
	pred_interior_reps_plus[0].back_shad_meth = PSD_NONE;\
	pred_interior_reps_plus[0].back_refl_props.ambient_coef = 1.0;\
	pred_interior_reps_plus[0].back_refl_props.diffuse_coef = 1.0;\
	pred_interior_reps_plus[0].back_refl_props.specular_coef = 0.0;\
	pred_interior_reps_plus[0].back_refl_props.specular_colr.type = PINDIRECT;\
	pred_interior_reps_plus[0].back_refl_props.specular_colr.val.ind = 1;\
	pred_interior_reps_plus[0].back_refl_props.specular_exp = 0.0;\
	pred_interior_reps_plus[0].back_colr.type = PINDIRECT;\
	pred_interior_reps_plus[0].back_colr.val.ind = 1;\
	pred_interior_reps_plus[0].approx_type = PSURF_WS_DEP;\
	pred_interior_reps_plus[0].approx_val[0] = 1.0;\
	pred_interior_reps_plus[0].approx_val[1] = 1.0;\
	pred_interior_reps_plus[1] = pred_interior_reps_plus[0];\
	pred_interior_reps_plus[2] = pred_interior_reps_plus[0];\
	pred_interior_reps_plus[3] = pred_interior_reps_plus[0];\
	pred_interior_reps_plus[4] = pred_interior_reps_plus[0];\
	pred_interior_reps_plus[1].style = PSTYLE_HOLLOW;\
	pred_interior_reps_plus[1].back_style = PSTYLE_HOLLOW;\
	pred_interior_reps_plus[2].style = PSTYLE_EMPTY;\
	pred_interior_reps_plus[2].back_style = PSTYLE_EMPTY;\
	pred_interior_reps_plus[3].style = PSTYLE_SOLID;\
	pred_interior_reps_plus[3].back_style = PSTYLE_HOLLOW;\
	pred_interior_reps_plus[4].style = PSTYLE_SOLID;\
	pred_interior_reps_plus[4].back_style = PSTYLE_EMPTY;\
	}

/*
   list of predifined edge indices plus and
   table of predefined edge bundles plus: flag, type, scale and general colour 
   macro to initialize list of predefined edge representations plus
*/
Pint list_pred_edge_idx_plus[] = {1,2,3,4,5};
Pedge_bundle_plus pred_edge_reps_plus[5];
#define INIT_PRED_EDGE_REPS_PLUS() {\
	pred_edge_reps_plus[0].flag = PEDGE_ON;\
	pred_edge_reps_plus[0].type = PLINE_SOLID;\
	pred_edge_reps_plus[0].width = 1.0;\
	pred_edge_reps_plus[0].colr.type = PINDIRECT;\
	pred_edge_reps_plus[0].colr.val.ind = 1;\
	pred_edge_reps_plus[1] = pred_edge_reps_plus[0];\
	pred_edge_reps_plus[2] = pred_edge_reps_plus[0];\
	pred_edge_reps_plus[3] = pred_edge_reps_plus[0];\
	pred_edge_reps_plus[4] = pred_edge_reps_plus[0];\
	pred_edge_reps_plus[1].type = PLINE_DASH;\
	pred_edge_reps_plus[2].type = PLINE_DOT;\
	pred_edge_reps_plus[3].type = PLINE_DASH_DOT;\
	pred_edge_reps_plus[4].width = 2.0;\
	}

/*
   list of predifined pattern indices plus and
   table of predefined pattern bundles plus: flag,type,scale and general colour 
   macro to initialize list of predefined pattern representations plus
*/
Pint list_pred_pattern_idx_plus[] = {NULL};
Ppat_rep_plus pred_pattern_reps_plus[] = { {NULL} };
#define INIT_PRED_PATTERN_REPS_PLUS()    
