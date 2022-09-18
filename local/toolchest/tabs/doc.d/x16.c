/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/*
 *	This example demonstrates several features of the New_Match_Menu 
 *	functions.
 *
 *	The last field is a multiple selection popup menu with the 
 *	maximum	number of selections set at three and a delay of 1 sec.  
 */

#include <stdio.h>
#include <setjmp.h>
#include "vt.h"
#include "windows.h"
#include "fields.h"

#define VERTICAL	"vertical"
#define HORIZONTAL	"horizontal"
#define STATIC	"static"
#define NSELECTS	3
#define NFIELDS		5

main()
{
	struct field_item *f[NFIELDS];
	struct field_item *fcmcfm;
	register int	i;
	int	mdelay;
	char	*pchar;
	int	indexes[ NSELECTS + 1 ];
	struct keys	key_items[ 100 ];
	int	win_width;

	Start_Form( 0, 0 );
	win_width = SCRWID - 2; /* make the window 2 columns narrower than the screen */

	Def_Entry_Type( FAR_LEFT );
	Def_Editing_Type( OVERLAY );
	Def_Auto_Pos( TRUE );
/*
 *	Define Field 0
 *
 */
 	f[ 0 ] = New_Field( 4, 15, CMKEY, " ", 
	    0, "a b c de");
	Set_Label( f[ 0 ], "l", "Choice1: ", FANORMAL );
	New_Static_Menu( f[ 0 ], 2, "top" );
	Set_Auto_Advance( f[ 0 ], TRUE );

/*
 *	Define Field 1
 *
 */
 	if( ( pchar = ( char * ) getenv( "MDELAY" ) ) == NULL )
 		mdelay = 0;
 	else
 		mdelay = atoi( pchar );
 	
 	f[ 1 ] = New_Field( 8, 15, CMKEY, "  ", 
 		0, "ab cd ef ghi" );
	Set_Label( f[ 1 ], "l", "Choice2: ", FANORMAL );
	New_Popup_Menu( f[ 1 ], mdelay, NULL );
	Set_Auto_Advance( f[ 1 ], TRUE );

/*
 *	Define Field 2
 *
 */
 	
 	key_items[ 0 ].kstr = "these";
 	key_items[ 1 ].kstr = "are";
 	key_items[ 2 ].kstr = "items";
 	key_items[ 3 ].kstr = "in";
 	key_items[ 4 ].kstr = "a";
  	key_items[ 5 ].kstr = "popup";
 	key_items[ 6 ].kstr = "vertical";
 	key_items[ 7 ].kstr = "menu";
 	key_items[ 8 ].kstr = 0;

 	f[ 2 ] = New_Field( 13, 15, CMKEY_LIST, "          ", 0, key_items );
	Set_Label( f[ 2 ], "l", "Choice3: ", FANORMAL );
	
	New_Popup_Menu( f[ 2 ], mdelay, "under" );


/*
 *	Define Field 3
 *
 */
 	
 	f[ 3 ] = New_Field( 13, 40, CMKEY, 
		"                                   ",
 		0, "these are items in a popup vertical menu" );
	Set_Label( f[ 3 ], "l", "Choice4: ", FANORMAL );
	New_Popup_Menu( f[ 3 ], 0, "a" );
	Set_M_Selections( f[ 3 ], TRUE, NSELECTS, indexes );

/*
 *	Define Field 4
 *
 */
 	f[ 4 ] = New_Field( 18, 15, CMKEY, "          ", 
 		0, "these are items in a static menu at the bottom" );
	Set_Label( f[ 4 ], "l", "Choice5: ", FANORMAL );
	New_Static_Menu( f[ 4 ], 2, "bottom" );

	
/*
 *	For each field, set auto advance for completion, underline, link
 * 	to confirmation field, make forward and back not validate, and
 * 	turn on mouse.
 */

	fcmcfm = New_Field( 0, 0, CMCFM, " ", 0, 0 );
	
 	for( i = 0; i < NFIELDS; i++ )
 	{
 		Set_Attributes( f[ i ], FAUNDER );
 		Set_Tab_Movement( f[ i ], TRUE, FALSE, TRUE, TRUE, FALSE );
		Link_Fields( f[ i ], fcmcfm );
 	}

	Show_List( f, NFIELDS );

/*	display static menus */
	Show_Static_Menu( f[ 0 ] );
	Show_Static_Menu( f[ 4 ] );

	Get_List( f, NFIELDS, FALSE, FALSE );

	Push_Window( f[0]->window );
	fflush( stdout );
	sleep( 4 );
	Pop_Window( f[0] ->window, 1 );
	fflush( stdout );
	sleep( 4 );
	Push_Window( f[0]->window );
	fflush( stdout );
	End_Form();

/*	Print field values and indexes to selections */
	for( i = 0; i < NFIELDS; i++ )
	{
		if( i == 3 )
			printf( "field 3:\tnumber of responses = %d\n\t\tindexes = %d, %d, %d\n\t\tresponse = %s\n",
					indexes[ 0 ],
					indexes[ 1 ],
					indexes[ 2 ],
					indexes[ 3 ],
					f[ 3 ] -> txbuf );
		else
			printf( "field %d:\tindex = %d\tresponse = %s\n",
					i,
					f[ i ] -> fndfv,
					f[ i ] -> txbuf );
	}
}
