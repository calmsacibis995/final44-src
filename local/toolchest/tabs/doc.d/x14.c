/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include <stdio.h>
#include <setjmp.h>
#include "vt.h"
#include "windows.h"
#include "fields.h"

/*
#include "switch.h"

	/ff5/lsrp/devenv/src/include/s.switch.h
	switch.h	1.1	6/15/83 16:50:26
	defines for the SWITCH construct for selecting among character strings
*/
static	char	switch_h[] = "@(#)  switch.h 1.1";

#define	WoRD(x)x


#define	SWITCH(a)	{  char *s_w_i_t_c_h; s_w_i_t_c_h = a;  WoRD(/)WoRD(*)

#define	CASE(a)	} else WoRD(/)WoRD(*) WoRD(*)WoRD(/) \
		if( !strcmp(s_w_i_t_c_h, a) ) {

#define	CASE2(a1,a2)	} else WoRD(/)WoRD(*) WoRD(*)WoRD(/)\
		if( !strcmp(s_w_i_t_c_h, a1)  ||\
		!strcmp(s_w_i_t_c_h, a2) ) {

#define	CASE3(a1,a2,a3)	} else WoRD(/)WoRD(*) WoRD(*)WoRD(/)\
		if( !strcmp(s_w_i_t_c_h, a1)  ||\
		!strcmp(s_w_i_t_c_h, a2)  ||\
		!strcmp(s_w_i_t_c_h, a3) ) {

#define	CASEN(a)	} else WoRD(/)WoRD(*) WoRD(*)WoRD(/)\
		if( !strncmp(s_w_i_t_c_h, a, sizeof(a)-1) ) {

#define	CASEN2(a1,a2)	} else WoRD(/)WoRD(*) WoRD(*)WoRD(/)\
		if( !strncmp(s_w_i_t_c_h, a1, sizeof(a1)-1)  ||\
		!strncmp(s_w_i_t_c_h, a2, sizeof(a2)-1) ) {

#define	CASEN3(a1,a2,a3)	} else WoRD(/)WoRD(*) WoRD(*)WoRD(/)\
		if( !strncmp(s_w_i_t_c_h, a1, sizeof(a1)-1)  ||\
		!strncmp(s_w_i_t_c_h, a2, sizeof(a2)-1)  ||\
		!strncmp(s_w_i_t_c_h, a3, sizeof(a3)-1) ) {

#define	DEFAULT		} else WoRD(/)WoRD(*) WoRD(*)WoRD(/) {

#define	ENDSW		}  WoRD(/)WoRD(*) WoRD(*)WoRD(/) }


main ()
{
	char nex_action[80];
	char *ptr;
	int i, n;

	struct field_item *pg1fld[9];
	struct SWindow  setpg1_window;
	struct window  *regpg1_window;

	struct field_item *pg2fld[4];
	struct field_item *num;
	struct field_item *conf;
	struct field_item *conf1;

	struct field_item *workrb[2];
	struct field_item *fregion[60];
	struct SWindow  setup_window;
	struct window  *reg_window;

	struct field_item *workctx[2];
	struct field_item *fregion2[60];
	struct SWindow  setup2_window;
	struct window  *reg2_window;

	struct field_item *workpbx[2];
	struct field_item *fregion3[60];
	struct SWindow  setup3_window;
	struct window  *reg3_window;

	Start_Form (0, 0);

/*
 *	Allow for tabbing through the fields.
 */

	conf = New_Field (0, 0, CMCFM, "_", 0, 0);
	conf1 = New_Field (0, 0, CMCFM, "_", 0, 0);

/*
 *	Create a screen size window for page 1 fields.
 *	This will allow for efficient showing of the 2 pages.
 */

	setpg1_window.top_x = 0;
	setpg1_window.top_y = 0;
	setpg1_window.lines = 24;
	setpg1_window.cols = 79;
	setpg1_window.box_h = 0;
	setpg1_window.box_v = 0;
	setpg1_window.type_scroll = FALSE;
	setpg1_window.depth = 5;
	setpg1_window.box_attribute = FANORMAL;

	regpg1_window = New_Window (setpg1_window);

/*
 *	Define page 1 fields
 *
 *	Define Field 0
 *
 */
	pg1fld[0] = New_Field(3, 17, CMNUM, "...",
			"Building number must be in the range of",
			 "0,1,999");


	Set_Attributes (pg1fld[0], FALEFT);

	Set_Label (pg1fld[0], "l", "Building Number: ", FANORMAL);

	Set_Tab_Movement (pg1fld[0], TRUE, TRUE, TRUE, FALSE);

	Link_Fields (pg1fld[0], conf);

/*
 *
 *	Define Field 1
 *
 */
	pg1fld[1] = New_Field(4, 17, CMSTR, "........",
			"Enter the Common Language Location Identification (CLLI) Code for the building.", 0);


	Set_Attributes (pg1fld[1], FALEFT);

	Set_Label (pg1fld[1], "l", "CLLI Code: ", FANORMAL);

	Set_Tab_Movement (pg1fld[1], TRUE, TRUE, TRUE, FALSE);

	Link_Fields (pg1fld[1], conf);
/*
 *
 *	Define Field 2
 *
 */

	pg1fld[2] = New_Field(6, 40, CMSTR, "....................",
			"Type name of building.",
			0);

	Set_Tab_Movement (pg1fld[2], TRUE, TRUE, TRUE, FALSE);

	Set_Label (pg1fld[2], "l", "Building Name: ", FANORMAL);

	Link_Fields (pg1fld[2], conf);


/*
 *
 *	Define Field 3
 *
 */
	pg1fld[3] = New_Field(8, 40, CMNUM, "..",
			"Growth machine number must be 1 to 8.",
			 "0,1,8");

	Set_Attributes (pg1fld[3], FALEFT);

	Set_Label (pg1fld[3], "l", "Growth Machine Number: ", FANORMAL);

	Set_Tab_Movement (pg1fld[3], TRUE, TRUE, TRUE, FALSE);

	Link_Fields (pg1fld[3], conf);

/*
 *
 *	Define Field 4
 *
 */
	pg1fld[4] = New_Field(10, 40, CMSTR, "...",
			"Future machine type must be 1 to 8.",
			 "0,1,8");

	Set_Attributes (pg1fld[4], FALEFT);

	Set_Label (pg1fld[4], "l", "Future Machine Type: ", FANORMAL);

	Set_Tab_Movement (pg1fld[4], TRUE, TRUE, TRUE, FALSE);

	Link_Fields (pg1fld[4], conf);

/*
 *
 *	Define Field 5
 *
 */
	pg1fld[5] = New_Field(12, 40, CMNUM, "....",
			"This field is used fo enter the fraction of total trafic that is within private branch exchanges {PBXs} or Centrex {CTX-CU} units.  Note that this entry is mandatory if CTX-CU is forecast for the building (see BSPs Page 159.)", "2,0.0,1.0");

	Set_Attributes (pg1fld[5], FALEFT);

	Set_Label (pg1fld[5], "l", "Fract. of Intratraf. in PBX/CTX-CU: ", FANORMAL);

	Set_Tab_Movement (pg1fld[5], TRUE, TRUE, TRUE, FALSE);

	Link_Fields (pg1fld[5], conf);

/*
 *
 *	Define Field 6
 *
 */
	pg1fld[6] = New_Field(14, 40, CMNUM, "....",
			"This field is used to enter the fraction of total non-CTX Residence and Business lines serving only business.", "3,0,1.0");


	Set_Label (pg1fld[6], "l", "Fract. of R&B Serving Business: ", FANORMAL);

	Set_Attributes (pg1fld[6], FALEFT);

	Set_Tab_Movement (pg1fld[6], TRUE, TRUE, TRUE, FALSE);

	Link_Fields (pg1fld[6], conf);

/*
 *
 *	Define Field 7
 *
 */
	pg1fld[7] = New_Field(16, 40, CMNUM, "....",
			"This field is used to enter the fraction of originating building calls that are intrabuilding. The intrabuilding traffic includes both intermachine and intramachine traffic for all machines in the building.", "1,0,1.0");


	Set_Label (pg1fld[7], "l", "Fract. of Calls Intrabuilding: ", FANORMAL);

	Set_Attributes (pg1fld[7], FALEFT);

	Set_Tab_Movement (pg1fld[7], TRUE, TRUE, TRUE, FALSE);

	Link_Fields (pg1fld[7], conf);

/*
 *
 *	Define field 8/NEXT operation field
 *
 */
	pg1fld[8] = New_Field (21, 8, CMKEY, ".............", "'WRITE' is to validate the data on the screen and to place it in the data base. 'ERASE' is to clear all the data from the fields on the screens. 'MENU' is to go back to the menu which contained the present screen. 'LOG-OFF' is to break out LSRP. 'NEXT-PAGE' is to go the next set of fields for this n. An d 'PREVIOUS-PAGE' is to go previous set of fields for this screen.", "WRITE ERASE MENU LOG-OFF NEXT-PAGE PREVIOUS-PAGE ARM DMM BLM BCO BCO1 BCO2");

	Set_Label (pg1fld[8], "l", "NEXT: ", FANORMAL);

	Set_Label (pg1fld[8], "r", " (W)RITE, (E)RASE, (M)ENU, (L)OG_OFF, (N)EXT-PG,", FANORMAL);
	Set_Label (pg1fld[8], "b", "                      (P)REVIOUS-PG, or SCREEN ID", FANORMAL);

	Set_Attributes (pg1fld[8], FACASE);

	for (i = 0; i < 9; i++)
		{
		Set_Window (pg1fld[i], regpg1_window, errwindow, regpg1_window);
		Set_EOF (pg1fld[i], TRUE, TRUE);
		}

/*
 *	Define page 2 fields
 *
 *	Define field 0
 *
 *	Create the scrollable region 
 *
 *	REGION: Create the window first
 *
 */
	setup_window.top_x = 10;
	setup_window.top_y = 0;
	setup_window.lines = 9;
	setup_window.cols = 18;
	setup_window.box_h = '-';
	setup_window.box_v = '|';
	setup_window.type_scroll = TRUE;
	setup_window.depth = 6;
	setup_window.box_attribute = FANORMAL;

	reg_window = New_Window (setup_window);

/*
 *	REGION: Create the two fields
 *
 */
	workrb[0] = New_Field (0, 5, CMNUM,
		"..", "Enter the last 2 digits of the workrb your forcasting.",
		"0,0,99");
	Set_Tab_Movement (workrb[0], TRUE, TRUE, TRUE, TRUE, FALSE);
	Set_Auto_Advance (workrb[0], TRUE);
	Set_EOF (workrb[0], TRUE, TRUE);
	Link_Fields (workrb[0], conf1);

	workrb[1] = New_Field (0, 10, CMNUM,
		".......", "Enter the number of working residence & business (non-CTX) lines.",
		"0,0,9999999");
	Set_Tab_Movement (workrb[1], TRUE, TRUE, TRUE, TRUE, FALSE);
	Set_Auto_Advance (workrb[1], TRUE);
	Set_EOF (workrb[1], TRUE, TRUE);
	Link_Fields (workrb[1], conf1);

/*
 *	REGION: Link the one line field to allow blank entries
 *		The user may enter a value or a year or
 *		hit the tab or return keys.
 *
 *	REGION: Create the scrollable region and add it to the list
 *		of fields.
 *
 */
	New_Region (reg_window, workrb, 2, 30, fregion, 1);
	pg2fld[0] = New_Field (10, 0, CMREGN,
			(char *) fregion, (char *) (2 * 30), 0);

/*
 *	Label the lines in the window with line numbers
 */

	for (i = n = 0; i < 60; i++)
	{
		ptr = (char *) malloc (8);
		if (ptr == 0)
			break;
		Set_Window (fregion[i], 0, 0, stdwindow);
		if ((i % 2) != 0) continue;
		n++;
		sprintf (ptr, "%d: ", n);
		Set_Label (fregion[i], "left", ptr, FANORMAL);
	}

/*
 *
 *	Define field 1
 *
 *	Create the scrollable region 
 *
 *	REGION: Create the window first
 *
 */
	setup2_window.top_x = 10;
	setup2_window.top_y = 30;
	setup2_window.lines = 9;
	setup2_window.cols = 18;
	setup2_window.box_h = '-';
	setup2_window.box_v = '|';
	setup2_window.type_scroll = TRUE;
	setup2_window.depth = 6;
	setup2_window.box_attribute = FANORMAL;

	reg2_window = New_Window (setup2_window);

/*
 *	REGION: Create the two fields
 *
 *	The year field 1st
 */
	workctx[0] = New_Field (0, 5, CMNUM,
		"..", "Enter the last 2 digits of the working CTX-CO lines your forcasting.",
		"0,0,99");
	Set_Tab_Movement (workctx[0], TRUE, TRUE, TRUE, TRUE, FALSE);
	Set_Auto_Advance (workctx[0], TRUE);
	Set_EOF (workctx[0], TRUE, TRUE);
	Link_Fields (workctx[0], conf1);

/*
 *	The forecast field 2nd
 */
	workctx[1] = New_Field (0, 10, CMNUM,
		".......", "Enter the number of working CTX-CO lines.",
		"0,0,9999999");
	Set_Tab_Movement (workctx[1], TRUE, TRUE, TRUE, TRUE, FALSE);
	Set_Auto_Advance (workctx[1], TRUE);
	Set_EOF (workctx[1], TRUE, TRUE);
	Link_Fields (workctx[1], conf1);

/*
 *	REGION: Link the one line field to allow blank entries
 *		The user may enter a year or a value or
 *		hit the tab or return keys.
 *
 *	REGION: Create the scrollable region and add it to the list
 *		of fields.
 *
 */
	New_Region (reg2_window, workctx, 2, 30, fregion2, 1);
	pg2fld[1] = New_Field (10, 0, CMREGN,
			(char *) fregion2, (char *) (2 * 30), 0);

/*
 *	Label the lines in the window with line numbers
 */

	for (i = n = 0; i < 60; i++)
	{
		ptr = (char *) malloc (8);
		if (ptr == 0)
			break;
		Set_Window (fregion2[i], 0, 0, stdwindow);
		if ((i % 2) != 0) continue;
		n++;
		sprintf (ptr, "%d: ", n);
		Set_Label (fregion2[i], "left", ptr, FANORMAL);
	}
/*
 *
 *	Define field 2
 *
 *	Create the scrollable region 
 *
 *	REGION: Create the window first
 *
 */
	setup3_window.top_x = 10;
	setup3_window.top_y = 60;
	setup3_window.lines = 9;
	setup3_window.cols = 18;
	setup3_window.box_h = '-';
	setup3_window.box_v = '|';
	setup3_window.type_scroll = TRUE;
	setup3_window.depth = 6;
	setup3_window.box_attribute = FANORMAL;

	reg3_window = New_Window (setup3_window);

/*
 *	REGION: Create the two fields
 *
 *	The year field 1st
 */
	workpbx[0] = New_Field (0, 5, CMNUM,
		"..", "Enter the last 2 digits of the working PBX or CTX-CU trunks your forcasting.",
		"0,0,99");
	Set_Tab_Movement (workpbx[0], TRUE, TRUE, TRUE, TRUE, FALSE);
	Set_Auto_Advance (workpbx[0], TRUE);
	Set_EOF (workpbx[0], TRUE, TRUE);
	Link_Fields (workpbx[0], conf1);

/*
 *	The forecast field 2nd
 */
	workpbx[1] = New_Field (0, 10, CMNUM,
		".......", "Enter the number of working PBX or CTX-CU trunks.",
		"0,0,9999999");
	Set_Tab_Movement (workpbx[1], TRUE, TRUE, TRUE, TRUE, FALSE);
	Set_Auto_Advance (workpbx[1], TRUE);
	Set_EOF (workpbx[1], TRUE, TRUE);
	Link_Fields (workpbx[1], conf1);

/*
 *	REGION: Link the one line field to allow blank entries
 *		The user may enter a year or a value or
 *		hit the tab or return keys.
 *
 *	REGION: Create the scrollable region and add it to the list
 *		of fields.
 *
 */
	New_Region (reg3_window, workpbx, 2, 30, fregion3, 1);
	pg2fld[2] = New_Field (10, 0, CMREGN,
			(char *) fregion3, (char *) (2 * 30), 0);

/*
 *	Label the lines in the window with line numbers
 */

	for (i = n = 0; i < 60; i++)
	{
		ptr = (char *) malloc (8);
		if (ptr == 0)
			break;
		Set_Window (fregion3[i], 0, 0, stdwindow);
		if ((i % 2) != 0) continue;
		n++;
		sprintf (ptr, "%d: ", n);
		Set_Label (fregion3[i], "left", ptr, FANORMAL);
	}
/*
 *
 *	Define the field 3/NEXT operation field
 *
 */
	pg2fld[3] = New_Field (21, 8, CMKEY, ".............", "'WRITE' is to validate the data on the screen and to place it in the data base. 'ERASE' is to clear all the data from the fields on the screens. 'MENU' is to go back to the menu which contained the present screen. 'LOG-OFF' is to break out LSRP. 'NEXT-PAGE' is to go the next set of fields for this n. An d 'PREVIOUS-PAGE' is to go previous set of fields for this screen.", "WRITE ERASE MENU LOG-OFF NEXT-PAGE PREVIOUS-PAGE ARM DMM BLM BCO BCO1 BCO2");

	Set_Label (pg2fld[3], "l", "NEXT: ", FANORMAL);

	Set_Label (pg2fld[3], "r", " (W)RITE, (E)RASE, (M)ENU, (L)OG_OFF, (N)EXT-PG,", FANORMAL);
	Set_Label (pg2fld[3], "b", "                      (P)REVIOUS-PG, or SCREEN ID", FANORMAL);

	Set_Attributes (pg2fld[3], FACASE);

	Pop_Window (regpg1_window, 5);

/*
 *	Process the fields
 *
 */
	Print_Center (regpg1_window, 0, FANORMAL, "LSRP");
	Print_Form   (regpg1_window, 0, 66, FANORMAL, "Page 1 of 2");
	Print_Center (regpg1_window, 2, FANORMAL, "Building Level Input");

/*
 *	Pop the 1st page window on the screen
 */


	Print_Form (stdwindow, 0, 66, FANORMAL, "Page 2 of 2");

	Print_Form (stdwindow, 6, 0, FANORMAL, "Working Res. & Bus.");
	Print_Form (stdwindow, 7, 2, FANORMAL, "(Non-CTX) Lines");
	Print_Form (stdwindow, 8, 5, FANORMAL, "Year  Forcast");

	Print_Form (stdwindow, 6, 35, FANORMAL, "Working");
	Print_Form (stdwindow, 7, 32, FANORMAL, "CTX-CO Lines");
	Print_Form (stdwindow, 8, 34, FANORMAL, "Year  Forcast");

	Print_Form (stdwindow, 6, 62, FANORMAL, "Working PBX");
	Print_Form (stdwindow, 7, 60, FANORMAL, "or CTX-CU Trunks");
	Print_Form (stdwindow, 8, 64, FANORMAL, "Year  Forcast");

/*
 *	show the fields for the 1st page
 */

firstpg:
	Pop_Window (regpg1_window, 5);

	Show_List (pg1fld, 9);

 	Get_List (pg1fld, 9, TRUE, TRUE);

	Field_Value (pg1fld[8], nex_action);
	
	SWITCH(nex_action)
	CASE("NEXT-PAGE")
		goto secondpg;
	CASE("PREVIOUS-PAGE")
		goto firstpg;
	DEFAULT
		End_Form();
		return;
	ENDSW

/*
 *	Now get the values for the fields on the 2nd page
 *	remove page 1 fields and the page 1 number from the screen
 */


/*
 *	Print the labels of the scrollable fields and pop there windows
 *	onto the screen so there are visible
 */
secondpg:
	Push_Window (regpg1_window);

	Show_List (pg2fld, 4);

	Get_List (pg2fld, 4, TRUE, TRUE);

	Field_Value (pg2fld[3], nex_action);

/*	
 *	check for paging by the user
 */

	SWITCH(nex_action)
	CASE("PREVIOUS-PAGE")
		goto firstpg;
	CASE("NEXT-PAGE")
		goto secondpg;
	ENDSW

	End_Form();
}

