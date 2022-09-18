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

#define OTHER 32767

/*
 *	This is a sample interface to a menu system that exists on eagle.
 *	The program creates keyword menus with embedded spaces.  These
 *	are used in a pop-up menu format.
 *
 *	Jeff Langer
 *
 */

main ()
{
    extern int  whereis ();
    extern int  N_M_pre_pop_up ();
    struct field_item  *f[5];
    struct field_item **fregion;
    struct keys keywords[100];
    int     count;
    char    buf[100];

    Start_Form (0, 0);

/*
 *	Field 0 - a pop-up keyword
 *
 */
    f[0] = New_Field (6, 33, CMKEY, "____________", 0,
	    "chinese italian french japanese mexican indian thai american other");

    if (New_Menu (f[0], 19, 20, 8, 40, "hvertizontal", &fregion, &count))
    {
	f[0] -> user_pointer = (char *) fregion;
	f[0] -> user_mask = count;
	Set_Label (f[0], "left", "Cuisine: ", FANORMAL);
	Set_Actions (f[0], N_M_pre_pop_up, 0);
    }
    else	/* Not Enough Memory */
    {
    	End_Form ();
    	exit (0);
    }

/*
 *	Field 1 - a pop-up keyword
 *
 */
    f[1] = New_Field (8, 33, CMKEY_LIST, "_______________", 0, keywords);

    keywords[0].kstr = "midtown";
    keywords[0].kval = 1;
    keywords[1].kstr = "uptown";
    keywords[1].kval = 2;
    keywords[2].kstr = "downtown";
    keywords[2].kval = 3;
    keywords[3].kstr = "village";
    keywords[3].kval = 4;
    keywords[4].kstr = "west village";
    keywords[4].kval = 5;
    keywords[5].kstr = "chinatown";
    keywords[5].kval = 6;
    keywords[6].kstr = "little italy";
    keywords[6].kval = 7;
    keywords[7].kstr = "soho";
    keywords[7].kval = 8;
    keywords[8].kstr = "columbus ave";
    keywords[8].kval = 9;
    keywords[9].kstr = "lincoln center";
    keywords[9].kval = 10;
    keywords[10].kstr = "carnegie hall";
    keywords[10].kval = 11;
    keywords[11].kstr = "bloomingdales";
    keywords[11].kval = 12;
    keywords[12].kstr = "other";
    keywords[12].kval = 13;
    keywords[13].kstr = 0;
    keywords[13].kval = 0;

/*
 *	If you use embedded spaces in keywords re-define the space key
 *	with the following procedure call
 *
 *	Def_Char_Action (' ', NORMAL, regchar, 0);
 *
 */

    Set_Label (f[1], "left", "Location: ", FANORMAL);

    if (New_Menu (f[1], 19, 20, 8, 40, "hvertizontal", &fregion, &count))
    {
	f[1] -> user_pointer = (char *) fregion;
	f[1] -> user_mask = count;
/*
	Set_Actions (f[1], N_M_pre_pop_up, whereis);
*/
	Set_Actions (f[1], N_M_pre_pop_up, 0);
    }
    else	/* Not Enough Memory */
    {
    	End_Form ();
    	exit (0);
    }

/*
 *	Field 2 - number of blocks
 *
 */
    f[2] = New_Field (10, 33, CMNUM, "_____", 0, "0,0,100");

    Set_Help (f[2], "Enter the distance (in blocks) within which to search.",
	    TRUE, TRUE, 0);
    Set_Label (f[2], "left", "Distance: ", FANORMAL);

/*
 *	Field 3 - a confirmation field
 *
 */
    f[3] = New_Field (12, 33, CMCFM, "_", 0, 0);
    Set_Label (f[3], "left", "Confirm: ", FANORMAL);
    Set_Tab_Movement (f[3], TRUE, FALSE, TRUE, FALSE, FALSE);

    Def_Char_Action (CTRL (_), CORRECT, corchar, 0);/* Dump to screen.out */

/*
 *	Collect the data
 *
 */
    Print_Center (stdwindow, 1, FANORMAL, "Manhattan restaurant database interface");

    Show_List (f, 4);
    Get_List (f, 4, FALSE, FALSE);

    Free_Menu (f[0] -> user_pointer, f[0] -> user_mask);
    Free_Menu (f[1] -> user_pointer, f[1] -> user_mask);

    End_Form ();

/* Run the eat command on eagle

 	printf ("%s %s %d %d %s\n", "/usr/lbin/eat", f[0]->txbuf,
			f[1]->user_mask, f[1]->user_pointer, f[2]->txbuf);
 	sprintf (buf,"%s %s %d %d %s\n", "/usr/lbin/eat", f[0]->txbuf,
			f[1]->user_mask, f[1]->user_pointer,
			f[2]->txbuf);
	system (buf);
*/
}

whereis (f, count, index, rc)
register struct field_item **f;
register int    count;
register int    index;
int     rc;
{
    char    buf[100];
    FILE * fp;
    int     i;
    extern int  atoi ();

    if (strcmp (f[index] -> txbuf, "other") == 0)
    {
	f[index] -> user_mask = OTHER;
	f[index] -> user_pointer = (char *) OTHER;
	return (index);
    }
    sprintf (buf, "%s %s\n", "/data/bin/whereis", f[index] -> txbuf);
    fp = popen (buf, "r");
    fgets (buf, 100, fp);
    fclose (fp);

 /* pack the 2 ints into user_mask and user_pointer */
    f[index] -> user_mask = atoi (&buf[0]);
    for (i = 0; buf[i] != ','; i++);
    f[index] -> user_pointer = (char *) atoi (&buf[i + 1]);
    return (index);
}
