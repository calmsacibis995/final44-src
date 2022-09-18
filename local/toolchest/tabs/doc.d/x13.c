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

main ()
{
    extern int  N_M_pre_pop_up ();
    struct field_item  *f[2];
    struct field_item **fregion;
    int     count;

    Start_Form (0, 0);

/*
 *	Field 0 - a pop-up keyword
 *
 */
    f[0] = New_Field (6, 33, CMKEY, "_____________________", 0,
	    "a fair sized list of my favorite few key words to choose from four score and seven years ago our fore fathers brought forth upon this land new nation etc.");

    Set_Label (f[0], "left", "Keyword: ", FANORMAL);
    Set_Actions (f[0], N_M_pre_pop_up, 0);

    if (New_Menu (f[0], 9, 20, 8, 40, "hvertizontal", &fregion, &count))
    {
	f[0] -> user_pointer = (char *) fregion;
	f[0] -> user_mask = count;
    }

/*
 *	Field 1 - a confirmation field
 *
 */
    f[1] = New_Field (19, 33, CMCFM, "_", 0, 0);
    Set_Label (f[1], "left", "Confirm: ", FANORMAL);
    Set_Tab_Movement (f[1], TRUE, FALSE, TRUE, FALSE, FALSE);

    Def_Char_Action (CTRL (_), CORRECT, corchar, 0);/* Dump to screen.out */

/*
 *	Collect the data
 *
 */
    Print_Center (stdwindow, 1, FANORMAL, "Menu Field Type Example");

    Show_List (f, 2);
    Get_List (f, 2, FALSE, FALSE);

    End_Form ();
}
