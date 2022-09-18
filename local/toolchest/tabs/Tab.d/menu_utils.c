/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/*	New_Match_Menu (field_ptr, xorigin, yorigin, max_height, max_width,
 *			orient, type)
 *
 *	struct field_item	*field_ptr;
 *	int	xorigin;
 *	int	yorigin;
 *	int	max_height;
 *	int	max_width;
 *	char	*orient;
 *	char	*type;
 *
 *	Written by Ken Hicks and Doug Blewett. 
 *	The best-match menu technique was developed
 *	by Ken for SOFT (a menu-driven version of SOLID that has
 *	evolved into the Text Manager).  Bob Glushko and Mike Bianchi 
 *	provided valuable feedback in that effort.
 *
 *	Creates menus from keywords defined in existing CMKEY or CMKEY_LIST
 *	fields.  Menus are displayed in a separate window created by 
 *	New_Match_Menu.  The CMKEY or CMKEY_LIST field is a response field
 *	for the menu.  As characters are typed into the response field, the
 *	response is matched against the items in the menu.  The closest 
 *	match as determined by the crosscor() function.  The item most
 *	closely matching the user's input is highlighted and 
 *	pointed at with ">".  This is repeated for each character entered
 *	by the user until the user goes to the next field.
 *
 *	The contents of the response field determines what match is made.
 *	The number of selections for the menu can be set with the function
 *	Set_M_Selections, described below.  The default is one selection.
 *	The user hits the multiple selection character to begin a new 
 *	match area in the response field.  
 *	The field is divided into sections separated by the
 *	multiple selection character (default '|', see Def_M_Char
 *	below).  For each match area a separate best match
 *	is determined.  The item in the menu that matches the 
 *	contents of the match area where the cursor is located is marked
 *	with a '>'.  THe other matched items are marked with a '+'.
 *	When the user tries to select too many items, the leftmost 
 *	match area in the response field is deleted.   With a single 
 *	character field, the effect is 	the same as hitting the key that 
 *	erases the field.
 *
 *	The display of the menu window can be delayed (see Set_M_Delay).
 *	Delaying the menu allows users to move much faster within a form 
 *	that has popup menus in it and allows experienced users to turn
 *	off menus when they are not needed.  Providing user-selectable 
 *	delays for menus is one way to allow users to adapt the system
 *	to their own level of expertise.
 *
 *	There are two types of menus: popup and static.  Popup menus only
 *	appear when the cursor is in the response field.  Static menus
 *	are always at one depth less than the response field.  
 *	Menus can either be vertical or horizontal.  Items in 
 *	Vertical menus are left justified and are listed top to bottom.
 *	Additional columns are added as needed up to a the maximum allowed
 *	by the width of the menu window.  Items in horizontal
 *	menus are centered and listed left to right.  Additional rows
 *	are added as needed up to the maximum height of the menu window.
 *	
 *	The size of a menu window is adjusted to fit the number of items.
 *	For vertical menus, the window is collapsed right to left, then
 *	bottom to top.  For horizontal menus, the window is collapsed
 *	bottom to top, then right to left.  If the items don't fit in
 *	the window, the menu is not displayed.  The help message will
 *	show what items can be selected, and the user can find out what item(s)
 *	matches the contents of the response area with the completion key or 
 *	by going to another field.  The contents of the response area
 *	are always expanded when the user leaves the field.
 *
 *	If the xorigin or yorigin is less than zero the size and location
 *	of the window are set by the menu function.  The menu window is
 *	centered above the response field if the field is in the bottom
 *	half of the screen and below the response field if the field is
 *	in the top half of the screen.  If you choose to let the menu
 *	function determine the location of the window you do not have to
 *	refigure where the menu window should go each time you move the
 *	response field.
 *
 *	The user_pointer in the field_items structure for the response field
 *	is used to point to the menu structure (see below).  The selected
 *	item is in the usual place, field_ptr->txbuf.  The index to the first 
 *	item in the response field is in field_ptr->fndfv and is 0 based.  See
 *	Set_M_Selections for what happens when there is more than one 
 *	selection.
 *
 *	Menus created with New_Match_Menu need a post_action routine,  
 *	Post_Match_Menu (see below).  It is assigned as the post_action
 *	routine in the call to New_Match_Menu.  If you write a post_action 
 *	routine, call Post_Match_Menu from that routine and assign the 
 *	post_action routine after the call to New_Match_Menu.
 *
 ***	field_ptr
 *
 *	This is a pointer to a field structure created with a call to
 *	New_Field().  The field must be a CMKEY ro CMKEY_LIST type.
 *
 ***	xorigin
 *
 *	This is the row origin (upper left corner) for the menu window.
 *	If xorigin is less than 0, the location size of the menu window
 *	are determined for you.
 *
 ***	yorigin
 *
 *	This is the column origin for the menu window.
 *	If yorigin is less than 0, the location size of the menu window
 *	are determined for you.
 *
 ****	max_height
 *
 *	This is the maximum possible height for the menu window and
 *	the maximum possible number of rows of items.  Ignored if
 *	xorigin or yorigin is less than 0.
 *
 ***	max_width
 *
 *	This is the maximum possible width for the menu window.  This is 
 *	used to determine the maximum possible number of columns =
 *	max_width / (length of longest item + 3 ).  Ignored if xorigin
 *	or yorigin is less than zero.
 *
 ***	orient
 *
 *	This is the orientation for the menu window.  The first character
 *	of the string should be an "h" for horizontal and a "v" for 
 *	vertical.  See above for a description of what vertical and 
 *	horizontal mean.
 *
 ***	type
 *
 *	Type is either popup or static.  The first letter must be a "p"
 *	for popup and an "s" for static.
 *
 *
 ***********************************************************************
 *
 *	New_Popup_Menu (field_ptr, delay);
 *
 *	struct field_item	*field_ptr;
 *	int	delay;
 *
 *	A more convenient way to create popup menus.  The popup menu is
 *	positioned as near as possible to the center of the field.  It
 *	is positioned above the field if the field is in the lower half of
 *	the screen and below the field if the field is in the upper half
 *	of the screen.
 *
 *	The delay argument is the minimum number of seconds before the 
 *	popup menu will appear after the user enters the field.  a value
 *	of -1 will cause the menu to remain invisible.  See Set_M_Delay
 *	below.
 *	
 *
 ***********************************************************************
 *
 ***********************************************************************
 ***********************************************************************
 *
 *	Free_Match_Menu (field_ptr)
 *	
 *	struct field_item	*field_ptr;
 *
 *	Frees any space created by the call to New_Match_Menu for the 
 *	appropriate field_ptr.
 *
 *
 ***********************************************************************
 *
 *	Def_M_Char (mult_char)
 *
 *	char	mult_char;
 *
 *	The menu response field is divided into sections separated by the
 *	multiple selection character, mult_char.
 *	For each response section a separate best match is determined.  
 *	The user may type this key to end one selection area and begin another.
 *	The defualt key is '|'.
 *
 *
 ***********************************************************************
 *
 *	Set_M_Selections (field_ptr, max_selections, match_index)
 *
 *	struct field_item	*field_ptr;
 *	intg	max_selections;;
 *	int	match_index[];
 *
 *
 *	Sets the maximum number of selections for a menu created with
 *	New_Match_Menu().  The defualt is one.  Match areas in the
 *	response field are separated by the multiple selection character 
 *	(default '|', see Def_M_Char).  For each match area a 
 *	separate best match is determined.  When the user tries to
 *	make more than max_selections number of selections, the leftmost
 *	match area in the response field is removed. For a single
 *	selection menu, the multiple selection character has the same
 *	effect as the erase field character.  When using the mouse, items
 *	are added by clicking the leftmost button when the pointer is over 
 *	the item in the menu.
 *	To delete an item, click the leftmost button when the mouse is
 *	over the item in the response field.
 *
 *	Match_index is an array that will contain the selections made by
 *	the end user.  The default items are set with Show_Default_Field.
 *	The contents of match_index does not influence the default items.
 *	Match_index must have at least max_selections + 1 elements.
 *	The 0th element of the def_indexes array is the number of selections.
 *
 *	field_ptr -> txbuf points to the contents of the response area.
 *	Selections are separated with the multiple selection character.
 *
 *
 ***********************************************************************
 *
 *	Set_M_Delay (field_ptr, delay)
 *	
 *	struct field_item	*field_ptr;
 *	int	delay;
 *
 *	Delay is the number of seconds the user must wait between keystrokes 
 *	before a popup menu created with New_Match_Menu will appear.  
 *	The menu window will not appear as long as the user hits a key every
 *	delay or fewer seconds.  It is useful to delay the presentation
 *	of the menu at least one second in case the user is just passing
 *	through the field enroute to another field.  Otherwise the
 *	menu pops up and disappears every time the user enters and leaves
 *	the field.  The delay also means that experienced users do not
 *	have to look at the menus except when they want to.
 *
 *
 ***********************************************************************
 *
 *	Post_Match_Menu (field_ptr, count, index, rc)
 *
 *	struct field_item	*field_ptr;
 *	int	count;
 *	int	index;
 *	int	rc;
 *
 *	This is the post_action routine required by menus created with 
 *	New_Match_Menu.  It is assigned as the post_action
 *	routine in the call to New_Match_Menu.  If you write a post_action 
 *	routine, call Post_Match_Menu from that routine and assign the 
 *	post_action routine after the call to New_Match_Menu.  Post_Match_Menu
 *	resets global menu variables and copies the index to the first 
 *	selection from the response field into field_ptr -> fndfv. It requires 
 *	the standard arguments for a post_action routine and always returns 
 *	the index to the current field.
 *
 ***********************************************************************
 *
 *	EXAMPLE
 *
 *	The following is a code fragment that uses New_Match_Menu() to 
 *	create a popup menu.
 *
 *	f[index] = New_Field (6, 33, CMKEY, "__________", 0, "a few items");
 *	Set_Label (f[index], "left", "Choice: ", FANORMAL);
 *
 *	New_Match_Menu (f[index], 8, 33, 10, 45, "vertical", "popup");
 *
 *	index++;
 *
 *	Show_List (f, index);
 *
 *	Get_List (f, index);
 */

#include	<sys/signal.h>
#include	<errno.h>
#include	<stdio.h>
#include	<setjmp.h>
#include	<string.h>
#include	"vt.h"
#include	"windows.h"
#include	"fields.h"
#include	"menus.h"

#define INDEX	field_ptr -> fndfv
#define	BETCOL 3
#define PMENU	( ( struct menu * ) field_ptr->user_pointer )
#define POINTER	"+"
#define CUR_POINTER ">"
#define MAX_SELECTIONS	25
#define NO_MATCH	"No menu item matches response"

struct window	*Pmenuwin;
int	(*Match_Routine)() = crosscor;

static char *help1 = "Select an item by typing an abbreviation into the response area.  ";
static char *help2 = "You can select up to ";
static char *help3 = " items.  To create a new match area in the response area, ";
static int	match_index[ MAX_SELECTIONS ];

static char   *nullstr = "\0";
static int	pop_flag;
static char	gresponse[FORM_BUF];
static char	match[FORM_BUF];
static char	mult_add_char = '|';	/* char used to add an item in a 
					 * multiple selection menu */

init_menu( field_ptr )
register struct	field_item	*field_ptr;
{
	extern int      cmmenu ();/* menu validation routine */
	extern int      read_menu ();/* menu read routine */
	extern int	delay_alarm();/* sig routine for popping menus */
	extern int	Post_Match_Menu();
	int     length;
	register struct keys   *pkeywd;


	if( field_ptr -> type != cmmenu || PMENU == 0 )
	{
		while( signal( SIGALRM, delay_alarm ) == -1 );
		if ((field_ptr -> user_pointer = 
			(char *) malloc (sizeof (struct menu))) == NULL)
			return (FALSE);

		if (field_ptr -> type == CMKEY_LIST) 
			PMENU -> key_type = TRUE;
		else
			PMENU -> key_type = FALSE;

		field_ptr -> type = cmmenu;
		field_ptr -> read_routine = read_menu;
		field_ptr -> post_action = Post_Match_Menu;
	}
	else
	{
		Free_Rel_Window (PMENU -> pmenuwin);
	}
	
	PMENU -> nitems = 0;
	PMENU -> maxlength = 0;
	PMENU -> first_time = 1;
	PMENU -> max_num_sel = 1;
	PMENU -> index_sel = (int *) malloc( 12 );
	PMENU -> index_sel[ 0 ] = 0;
	PMENU -> index_sel[ 1 ] = -1;
	INDEX = -1;

}
_get_items( field_ptr )
register struct field_item	*field_ptr;
{
	struct keys	*pkeywd;
	register int	length;
/*	get keyword list from response field	*/

	if (PMENU -> key_type == TRUE)
		pkeywd = (struct keys  *) field_ptr -> keywords;
	else
		pkeywd = (struct keys  *) cm_get_keys (field_ptr, FALSE);

/*	determine number of items	*/
	PMENU -> nitems = 0;
	PMENU -> maxlength = 0;
	while (pkeywd -> kstr)
	{
		if (PMENU -> maxlength < (length = strlen (pkeywd -> kstr)))
			PMENU -> maxlength = length;
		PMENU -> nitems++;
		pkeywd++;
	}

/*	leave room between columns for pointer */
	PMENU -> maxlength += BETCOL;
}

Set_M_Delay( field_ptr, delay )
register struct field_item	*field_ptr;
register int	delay;
{
	PMENU -> delay = delay;
}

Def_M_Char( add_char )
char	add_char;
{
	mult_add_char = add_char;
}

Set_M_Selections( field_ptr, mult_flag, max_selects, def_indexes )
register struct field_item	*field_ptr;
int	max_selects;
register int	def_indexes[];
{
	register int	i;
	
	free( PMENU -> index_sel );
	PMENU -> index_sel = def_indexes;
	PMENU -> max_num_sel = max_selects;
	if( PMENU -> max_num_sel < 1 )
		PMENU -> max_num_sel = 1;
	PMENU -> index_sel[ 0 ] = 0;
	for( i = 1; i < PMENU -> max_num_sel; PMENU -> index_sel[ i++ ] = -1 );
}

Free_Match_Menu (field_ptr)
register struct field_item      *field_ptr;
{
	if (PMENU)
	{
		if (PMENU -> type != 'p')
		{
			Free_Rel_Window (PMENU -> pmenuwin);
		}
		else 
			Pop_Window (PMENU -> pmenuwin, INVISIBLE);

		free (PMENU);
		field_ptr -> user_pointer = 0;
	}
	return (0);
}

Post_Match_Menu ( field_list, count, index, rc )
struct field_item	**field_list;
int	count;
int	index;
int	rc;
{
	register int	i;
	register struct field_item	*field_ptr;

	field_ptr = field_list[ index ];
	
	PMENU -> first_time = 1;

	/* copy array of selection indexes */
	for( i = 0; i <= match_index[ 0 ]; i++ )
		PMENU ->index_sel[ i ] = match_index[ i ];

	/* put -1 in remaining elements of indexes */
	while( i <= PMENU -> max_num_sel )
	{
		PMENU -> index_sel[ i ] = -1;
		i++;
	}

	/* copy first item into INDEX */
	if( match_index[ 0 ] > 0 )
		INDEX = match_index[ 1 ];
	else
		INDEX = -1;

	if (PMENU -> type == 'p')
	{
		alarm(0);
		if (PMENU -> pmenuwin)
			Pop_Window( PMENU -> pmenuwin, INVISIBLE );
	}
	if( PMENU -> type == 'f' )
		if( PMENU -> pmenuwin )
		{
			Clear_Form( PMENU -> pmenuwin );
		}

			

	return( index );
}

/*
 *	cmmenu (field_ptr)
 *
 *	validation routine for menus
 *
 */

cmmenu (field_ptr)
struct field_item      *field_ptr;
{
	register struct keys   *key_list;
	char   *error;
	char	buf[ 256 ];

	error = "The current string has no matches";

	if (!cm_start (field_ptr, error, error))
	{
		return;
	}

	if (field_ptr -> cmflg & CMHLP)
	{
		if( PMENU -> pmenuwin -> _depth >= INVISIBLE && PMENU -> type == 'p' )
		{
			if( PMENU -> max_num_sel > 1 )
			{
				sprintf( buf, "%s%s%d%stype a '%c'.",
						help1,
						help2,
						PMENU -> max_num_sel, 
						help3, 
						mult_add_char );
				prhlp( field_ptr, buf, FALSE, FALSE );
			}
			else
				prhlp (field_ptr, help1, FALSE, FALSE);

			if( PMENU -> delay > 0 && PMENU -> type == 'p' )
			{
				sprintf( buf, "If you wait %d seconds between keystrokes a menu of the items will appear.", PMENU -> delay );
				prhlp( field_ptr, buf, FALSE, FALSE );
			}
			if (PMENU -> key_type == TRUE)
				key_list = (struct keys *) field_ptr -> 
						keywords;
			else
				key_list = (struct keys *) cm_get_keys
						(field_ptr, FALSE);

			while (key_list -> kstr)
			{
				prhlp (field_ptr, (key_list++) -> kstr, 
						TRUE, TRUE);
			}
			prhlp( field_ptr, "Enter an abbreviation.", 
					FALSE, FALSE );
		} 
		else if ((field_ptr -> fnflg & FNHLP) == 0)
		{
			if( PMENU -> max_num_sel > 1 )
			{
				sprintf( buf, "%s%s%d%stype a '%c'.",
						help1,
						help2,
						PMENU -> max_num_sel, 
						help3, 
						mult_add_char );
				prhlp( field_ptr, buf, FALSE, FALSE );
				prhlp( field_ptr, 
"A '>' points to the item that best matches the contents of the match area the cursor is in. A '+' is in front of the other matched items.",
						FALSE, FALSE );
			}
			else
			{
				prhlp (field_ptr, help1, FALSE, FALSE );
				prhlp (field_ptr, "A > points to the item that best matches the contents of the response area.",
						FALSE, FALSE);
			}
		}
		field_ptr -> cmflg |= CMNOP;
		return;
	}

/*	if we got here via something other than read_menu ()
 *	this will happen if the read match routine is linked to
 *	another field
 */
	if (PMENU == NULL)
	{
		check_menu (field_ptr, FALSE);
	}

	else
	{
		check_menu( field_ptr, TRUE );
		if( field_ptr -> cmflg & CMCMP )
		{
			if( items_expand( field_ptr ) )
				field_ptr -> cmflg |= CMNOP;
			field_ptr -> cmflg |= CMREP;
			return;
		}
		else
		{
			if( items_expand( field_ptr ) )
				field_ptr -> cmflg |= CMNOP;
			return;
		}
	}

	field_ptr -> cmflg |= CMNOP;
	error_fields = error;

	return;
}

read_menu (field_ptr)
register struct field_item     *field_ptr;
{
	register int     rc;

	if( PMENU -> first_time )
	{
		if( PMENU -> type == 'f' )
		{
			write_menu( field_ptr );
			Wrefresh( PMENU -> pmenuwin );
		}
		check_menu( field_ptr, TRUE );
		match_index[ 0 ] = 0;
	}

	if (PMENU -> pmenuwin -> _depth >= INVISIBLE)
	{
		if( PMENU -> delay > 0 )
		{
			if( PMENU -> first_time )
				pop_flag = FALSE;
			alarm( PMENU -> delay );
		}
		else if (PMENU -> first_time && PMENU -> delay == 0)
		{
			if( popup_window (field_ptr) != FALSE )
				Pop_Window( PMENU -> pmenuwin, 1 );
		}
	}
	
	if( PMENU -> first_time )
		PMENU -> first_time = 0;

	check_menu( field_ptr, TRUE );
		
	while( TRUE )
	{
		rc = getachar (field_ptr);
		if( pop_flag == TRUE )
		{
			pop_flag = FALSE;
			if( popup_window( field_ptr ) != FALSE )
			{
				match_index[ 0 ] = 0;
				check_menu(field_ptr, TRUE);
				Pop_Window (PMENU -> pmenuwin, 1 );
			}
		}
		if( ( rc == 0177 || rc == 0 ) && errno == EINTR )
		{
			errno = 0;
			continue;
		}
		switch( chartyp[ rc ] )
 		{
		case BREAK:
			if( rc != K_MOUSE )
			{
				alarm( 0 );
				return( rc );
			}

		default:
			if( rc != K_MOUSE && rc != K_MOUSE2 )
				return( rc );
			if( ( rc = Get_Menu_Index (field_ptr) ) < 0 )
			{
				if( rc == -1 )
					return( K_TAB );
				else if( rc == -2 )
					return( MOUSE_TYPE );
			}
			break;
		}
	}
}

/*
 *	This function determines which menu item is the best match	
 *	with the user's response.  This routine calls crosscor() to
 *	get a score between each item and the user's response.  If
 *	the score is less than zero, best match is "no match".
 *
 *	This function depends on the work done in the function crosscor
 */

check_menu (field_ptr, interactive)
register struct field_item      *field_ptr;
int     interactive;
{
	register char  *resp_ptr;
	register char  *txbuf_ptr;
	int     index;
	int	i;
	int	k;
	int	keep;
	int	old_sel[ MAX_SELECTIONS ];
	register char	*pch;
	register char	*tresponse;
	int	display;
	register struct keys   *key_list;
	int	cur_index;
	int	new_area;

	txbuf_ptr = field_ptr -> txbuf;

	if( PMENU -> key_type == TRUE || field_ptr -> type == CMKEY_LIST )
		for( resp_ptr = gresponse; txbuf_ptr < field_ptr -> txptr;
				*resp_ptr++ = *txbuf_ptr++ );
	else
	{
	/* 	remove leading punctuations (spaces, etc)	 */

		while ((chartyp[*txbuf_ptr] == PUNC) &&
				(txbuf_ptr < field_ptr -> txptr))
		{
			txbuf_ptr++;
		}

	/* 	put all characters until next punction into response	 */

		for (resp_ptr = gresponse; txbuf_ptr < field_ptr -> txptr &&
				(chartyp[*txbuf_ptr] != PUNC);
				*resp_ptr++ = *txbuf_ptr++ );
	}

	*resp_ptr = '\0';
	
	/* get list of keywords */
	
	if( PMENU -> key_type == TRUE || field_ptr -> type == CMKEY_LIST )
		key_list = (struct keys *) field_ptr -> keywords;
	else
		key_list = (struct keys *) cm_get_keys (field_ptr, FALSE);

	/* save old list */
	i = -1;
	while( i++ < match_index[ 0 ] )
		old_sel[ i ] = match_index[ i ];

	/* get list of matches */		
	tresponse = gresponse;
	match_index[ 0 ] = 0;
	while( TRUE )
	{
		if( pch = strchr( tresponse, mult_add_char ) )
		{
			*pch = '\0';
			score_match (field_ptr, key_list, tresponse );
			tresponse = ++pch;
		}
		else
		{
			score_match (field_ptr, key_list, tresponse );
			break;
		}
	}
	

	if( !interactive )
		return;

		
	/* use location of cursor to determine what to display as current item
	 */

	new_area = FALSE;
	display = TRUE;
	pch = field_ptr -> txcursor;
	if( pch == field_ptr -> txptr || *pch == mult_add_char )
	{
		if( pch == field_ptr -> txbuf )
			display = FALSE;
		else if( *( pch - 1 ) == mult_add_char )
		{
			new_area = TRUE;
			display = FALSE;
		}
	}
		
	if( display == TRUE )
	{
		index = match_index[ find_index( pch, 
				field_ptr -> txbuf ) + 1 ];
		if( index < 0 )
			print_nomatch( field_ptr );
		else
		{
			print_erase( field_ptr );
			cur_index = index;
		}
	}
	
	/* if item in old list not in new list, delete it */
	k = 0;
	while( k++ < old_sel[ 0 ] )
	{
		i = 0;
		keep = FALSE;
		while( i++ < match_index[ 0 ] )
			if( old_sel[ k ] == match_index[ i ] )
			{
				keep = TRUE;
				break;
			}
		if( keep == FALSE )
		{
			del_item (field_ptr, old_sel[ k ]);
			old_sel[ k ] = -1;
		}
	}

	/* if item in new list not in old list, display it */
	k = 0;
	while( k++ < match_index[ 0 ] )
	{
		i = 0;
		display = TRUE;
		while( i++ < old_sel[ 0 ] )
			if( old_sel[ i ] == match_index[ k ] )
				display = FALSE;

		if( display == TRUE )
		{
			if( cur_index == match_index[ k ] && new_area == FALSE)
				print_match( field_ptr, FAREVV, CUR_POINTER, 
						match_index[ k ], TRUE );
			else
				print_match( field_ptr, FAREVV, POINTER, 
						match_index[ k ], TRUE );
		}
		else
			if( cur_index == match_index[ k ] )
				print_match( field_ptr, FAREVV, CUR_POINTER, 
						match_index[ k ], FALSE );
			else
				print_match( field_ptr, FAREVV, POINTER, 
						match_index[ k ], FALSE );

	}

	/* if too many items, remove the first */
	if( match_index[ 0 ] > PMENU -> max_num_sel )
	{
		del_sel_area( field_ptr, 1 );
		check_menu( field_ptr, TRUE );
	}

}

Get_Menu_Index (field_ptr)
register struct field_item      *field_ptr;
{
	register int    x;
	register int    y;
	register int    index;
	int     col;
	struct keys    *key_list;
	register int	i;
	int	advance;
	char	*pch;
	char	*pchend;

	if (PMENU -> key_type == TRUE)
		key_list = (struct keys *) field_ptr -> keywords;
	else
		key_list = (struct keys *) cm_get_keys (field_ptr, FALSE);

/*	determine index from X and Y position	*/

	x = MOUSE_X - PMENU -> pmenuwin -> _top_x;

	y = MOUSE_Y - PMENU -> pmenuwin -> _top_y;

	/* check if in menu window */
	if (y > (PMENU -> ncols * PMENU -> maxlength) || 
			y < 0 ||
			x >= PMENU -> pmenuwin -> _bot_x - 
			PMENU -> pmenuwin -> _top_x || 
			x < 0)
	{
		return( -2 );
		/* check to see if in field for deleting an item*/
/*		if( ( MOUSE_X - field_ptr -> window -> _top_x ) !=
				field_ptr -> x_pos )
			return( -2 );
		y = MOUSE_Y - field_ptr -> window -> _top_y - 
				field_ptr -> y_pos;
		pchend = y + field_ptr -> txbuf;
		if( y < 0 || pchend > field_ptr -> txptr )
			return( -2 );
*/
		/* find which section of resonse field */
/*		i = 1;
		pch = field_ptr -> txbuf;
		while( pch < pchend )
			if( *pch++ == mult_add_char )
				i++;
*/
		/* del match from gresponse */
/*		del_sel_area( field_ptr, i );
		check_menu( field_ptr, TRUE );
		return;
*/
	}

	col = (y / PMENU -> maxlength);
	index = col + PMENU -> ncols * x;

	/* if already displayed, FIELD_ADVANCE, otherwise, add */
	i = 0;
	advance = TRUE;
	while( i++ < match_index[ 0 ] )
		if( match_index[ i ] == index )
			advance = FALSE;
	if( advance == TRUE )
		/* add match to gresponse */
		add_sel_area( field_ptr, key_list, index );
	else
		return( -1 );

	check_menu( field_ptr, TRUE );
	return;
}

del_item (field_ptr, index)
register struct field_item      *field_ptr;
register int	index;
{
	print_match (field_ptr, FANORMAL, " ", index, TRUE);
}

print_match (field_ptr, attribute, pointer, index, disp_flag)
register struct field_item      *field_ptr;
int     attribute;
char	*pointer;
register int	index;
int	disp_flag;
{
	char    string[FORM_BUF];
	char   *str_ptr;
	register int    pointrow;
	register int	pointcol;
	register int    i;

	if( index < 0 || PMENU -> ncols == 0 )
		return;

	pointrow = (index / PMENU -> ncols);
	pointcol = (PMENU -> maxlength *
			(index - pointrow *
			PMENU -> ncols)) + 1;

	Print_Form (PMENU -> pmenuwin, pointrow, pointcol,
			attribute, pointer);
	if( disp_flag == FALSE )
		return;
	str_ptr = string;
	for (i = pointcol; i < pointcol + PMENU -> maxlength
			- 1;)
		*str_ptr++ = PMENU -> pmenuwin -> 
				_map[pointrow][i++] & VT_CHAR;
	*str_ptr = '\0';

	Print_Form (PMENU -> pmenuwin, pointrow, pointcol,
			attribute, string);
}

delay_alarm( sig )
int	sig;
{
	while( signal( SIGALRM, delay_alarm ) == -1 );
	pop_flag = TRUE;
}

write_menu( field_ptr)
register struct field_item	*field_ptr;
{
	int     col;
	int     hlength;
	int     line;
	register struct keys   *pkeywd;
	struct keys    *pklast;
	struct keys    *pkendcol;
	struct keys    *pkendline;

/*	get keyword list from response field	*/

	if (PMENU -> key_type == TRUE)
		pkeywd = (struct keys  *) field_ptr -> keywords;
	else
		pkeywd = (struct keys  *) cm_get_keys (field_ptr, FALSE);

/*	write items to screen	*/

	col = BETCOL;
	pklast = pkeywd + PMENU -> nitems;
	pklast--;

	hlength = PMENU -> maxlength - BETCOL;
	line = 0;
	while (pkeywd <= pklast)
	{
		pkendline = pkeywd + PMENU -> ncols;
		if (pkendline > pklast)
		{
			pkendline = pklast;
			pkendline++;
		}
		col = BETCOL;
		while (pkeywd < pkendline)
		{
			if( PMENU -> orient != 'v' )
			{
				/* center items */
				Print_Form (PMENU -> pmenuwin, line, col +
					(int)((hlength - strlen (pkeywd -> kstr)) /
					2), 0, pkeywd -> kstr);
				pkeywd++;
			}
			else
				Print_Form( PMENU -> pmenuwin, line, col, 0, 
						(pkeywd++) -> kstr );
						
			col += PMENU -> maxlength;
		}
		line++;
	}
}

struct window	*
init_window( height )
int	height;
{
	register struct SWindow	newwin;

	newwin.top_x = 0;
	newwin.top_y = 0;
	newwin.lines = height;
	newwin.cols = SCRWID;
	newwin.type_scroll = TRUE;
	newwin.depth = INVISIBLE;
	newwin.box_attribute = 0;
	newwin.box_h = '-';
	newwin.box_v = '|';
	return( New_Window (newwin) );
}

find_index( pch, pbegin )
register char	*pch;
register char	*pbegin;
{
	register int	sel_index = 0;
	
	while( pch > pbegin )
	{
		pch--;
		if( *pch == mult_add_char )
			sel_index++;
	}
	return( sel_index );
}

print_nomatch( field_ptr )
register struct field_item	*field_ptr;
{
	w_xgo (field_ptr -> window,
			field_ptr -> window -> _x_pos,
			field_ptr -> window -> _y_pos);
	Print_Message ( field_ptr -> meswin, Mess_Attribute, NO_MATCH);
}

print_erase( field_ptr )
register struct field_item	*field_ptr;
{
	w_xgo (field_ptr -> window,
			field_ptr -> window -> _x_pos,
			field_ptr -> window -> _y_pos);
	Print_Message ( field_ptr -> meswin, Mess_Attribute, "" );
}

score_match( field_ptr, key_list, response )
register struct field_item	*field_ptr;
register struct keys	*key_list;
char	*response;
{
	struct keys    *best_key;
	struct keys    *kstart;
	register int    score;
	int    biggest;
	
	/* score match */
	biggest = 0;
	kstart = key_list;
	while (key_list -> kstr)
	{
		score = Match_Routine (response, key_list -> kstr, 0);
		if (score > biggest)
		{
			biggest = score;
			best_key = key_list;
		}
		key_list++;
	}
	
	if (biggest)
		match_index[ ++match_index[ 0 ] ] = best_key - kstart;
	else
		match_index[ ++match_index[ 0 ] ] = -1;
}

print_toomany( field_ptr )
register struct field_item	*field_ptr;
{
	char	*pch;

	if( PMENU -> max_num_sel == 1 )
		pch = " is";
	else
		pch = "s are";
	beep();
	w_xgo (field_ptr -> window, field_ptr -> window -> _x_pos, field_ptr ->
			window -> _y_pos);
	Print_Message (field_ptr -> meswin, Mess_Attribute, "Only %d selection%s allowed in this field.", PMENU -> max_num_sel, pch);
}

items_expand( field_ptr )
register struct field_item	*field_ptr;
{
	register struct keys	*key_list;
	register int	i;
	int	k;
	char	response[ FORM_BUF ];
	register char	*pch;
	register char	*pch2;
	int	rc = 0;
	
	if (PMENU -> key_type == TRUE)
		key_list = (struct keys *) field_ptr -> keywords;
	else
		key_list = (struct keys *) cm_get_keys (field_ptr,
		                        FALSE);
	gresponse[ 0 ] = '\0';
	i = 0;
	*field_ptr -> txptr = '\0';
	while( i++ < match_index[ 0 ] )
	{
		if( match_index[ i ] < 0 )
		{
			/* non-matching or null entry */
			rc = 1;
			k = 1;
			strcpy( response, field_ptr -> txbuf );
			pch = response;
			while( k++ < i )
			{
				pch = strchr( pch, mult_add_char );
				pch++;
			}
			if( ( pch - 1 ) != NULL )
				pch2 = pch;
			else
				pch2 = response;
			while( *pch2 != '\0' && *pch2 != mult_add_char )
				pch2++;
			*pch2 = '\0';
			strcat( gresponse, pch );
		}
		else
			strcat( gresponse, ( key_list + match_index[ i ] ) -> 
					kstr );
		if( i < match_index[ 0 ] )
			strcat( gresponse, &mult_add_char );
	}
	field_ptr -> cmflg |= CMCMP;
	if( strlen( gresponse ) <= field_ptr -> length )
	{
		field_ptr -> txptr = field_ptr -> txbuf;
		*(field_ptr -> txbuf ) = '\0';
		complete( field_ptr, gresponse );
	}
	return( rc );
}

del_sel_area( field_ptr, index )
register struct field_item	*field_ptr;
int	index; /* index to item in txbuf */
{
	register int	i;
	register char	*pch;
	register char	*to_pch;

	*field_ptr -> txptr = '\0';
	strcpy( gresponse, field_ptr -> txbuf );
	pch = gresponse;
	
	/* find beginning of selection area */
	i = 1;
	while( index != i )
	{
		while( *pch && *pch++ != mult_add_char );
		i++;
	}
	
	to_pch = pch;
	if( *pch && i > 1 )
		to_pch--;

	/* skip string to be deleted */
	while( *pch != '\0' && *pch != mult_add_char )
		pch++;

	if( *pch && i == 1 )
		pch++;

	/* copy reamining characters over characters to be deleted. */
	while( *to_pch++ = *pch++ );

	Show_Default_Field ( field_ptr, gresponse );
	w_mgo (field_ptr -> window, field_ptr -> window -> _x_pos,
			field_ptr -> y_pos + strlen (field_ptr -> txbuf));
}

add_sel_area( field_ptr, key_list, index )
register struct field_item	*field_ptr;
struct keys	*key_list;
int	index; /* index to match in key_list */
{
	register int	num;
	char	*get_abbr();
	
	/* remove unwanted selection areas */
	num = match_index[ 0 ];
	while( num >= PMENU -> max_num_sel )
	{
		del_sel_area( field_ptr, 1 );
		num--;
	}
		
	*field_ptr -> txptr = '\0';
	strcpy( gresponse, field_ptr -> txbuf );
	
	if( *field_ptr -> txbuf != '\0' && 
			*( field_ptr -> txptr - 1 ) != mult_add_char )
		strcat( gresponse, &mult_add_char );
	strcat( gresponse, get_abbr( ( key_list + index ) -> kstr, key_list ) );
/*	strcat( gresponse, ( key_list + index ) -> kstr ); */
	
	Show_Default_Field ( field_ptr, gresponse );
	w_mgo (field_ptr -> window, field_ptr -> window -> _x_pos,
			field_ptr -> y_pos + strlen (field_ptr -> txbuf));
}

char	*
get_abbr( resp, key_list )
char	*resp;
struct keys	*key_list;
{
	char	abbr[ 100 ];
	char	*list[ FORM_BUF ];
	register int	key_index = 0;
	register int	list_index = 0;
	register int	index;
	register int	min_score;
	register char	*cur_resp;
	register char	*abbr_pos;
	register char	*resp_pos;
	register char	*last_resp;
	
/*	setup abbreviation and response variables */
	abbr[ 0 ] = *resp;
	abbr[ 1 ] = '\0';
	abbr_pos = &abbr[0];
	resp_pos = &resp[0];
	last_resp = strchr( resp, '\0' );
	cur_resp = last_resp;
	

/*	reduce number of items matching to those with the same first character */
	min_score = Match_Routine( abbr, resp );
	while( ( key_list + key_index ) -> kstr )
	{
		if( abbr[ 0 ] == *( key_list + key_index ) -> kstr )
			list[ list_index++ ] = ( key_list + key_index ) -> kstr;
		key_index++;
	}
	if( list_index == 1 )
		return( abbr );
	list[ list_index ] = 0;

/*	go until find abbreviation with only one match, the response */
	index = list_index;
	while( TRUE )
	{
		index = 0;
		list_index = 0;
		min_score = Match_Routine( abbr, resp, 0 );
		while( list[ list_index ] )
		{
			if( Match_Routine( abbr, list[ list_index ], 0 ) >= min_score )
				index++;
			list_index++;
		}
		if( index == 1 )
			break;

		/* change abbreviation */
		if( cur_resp == last_resp )
		{
			/* add next response character permanently onto abbr */
			if( resp_pos == last_resp )
				break;
			*abbr_pos++ = *resp_pos++;
			cur_resp = resp_pos;
			*( abbr_pos + 1 ) = '\0';
		}
		*abbr_pos = *cur_resp++;
	}
	return( abbr );
}

locate_window( field_ptr, xorig, yorig, wid, location )register struct field_item	*field_ptr;
int	*xorig;
int	*yorig;
int	*wid;
char	location;
{
	register int	max_height;
	register int	ncols;
	register int	xorigin;
	register int	yorigin;
	int	maxlength;
	int	nitems;
	int	height;
	int	width;
	int	adj_xorigin = 0;
	int	adj_yorigin;
	int	row;
	int	column;

	if( PMENU -> type == 'p' )
	{
		_get_items( field_ptr );
		width = SCRWID;
		height = SCRNLIN - 1;
		xorigin = field_ptr -> x_pos + field_ptr -> window -> _top_x;
		max_height = 256;
	}
	else
	{
		max_height = PMENU -> max_height;
		width = field_ptr -> window -> _bot_y - field_ptr -> window -> _top_y;
		height = field_ptr -> window -> _bot_x - field_ptr -> window -> _top_x;
		xorigin = field_ptr -> x_pos;
	}
	maxlength = PMENU -> maxlength;
	nitems = PMENU -> nitems;
	yorigin = 0;
	switch( location )
	{
	default:

/*	Area is adjusted so that items
 *	fit cleanly in the area.  If there are more items than fit in
 *	area, else PMENU -> delay is set to -1 and no window will be displayed
 */

		if( xorigin + xorigin > height )
		{
			/* bottom half */
			xorigin--;
			max_height = xorigin;
			adj_xorigin = 1;
		}
		else
		{
			/* top half */
			adj_xorigin = 0;
			xorigin = xorigin + 2;
			max_height = height - xorigin;
		}
		max_height--;
		break;
	case 'r':
		/* right of field */
		max_height = height - 2;
		yorigin = field_ptr -> y_pos + field_ptr -> length + 2;
		width -= yorigin;
		break;
	case 'l':
		/* left of field */
		max_height = height - 2;
		width = field_ptr -> y_pos - strlen( field_ptr -> label ->
				string ) - 3;
		break;
	case 'o':
	case 'a':
		max_height = xorigin - 2;
		adj_xorigin = 1;
		break;
	case 't':
		PMENU -> orient = 'h';
		if( PMENU -> type == 'p' )
			max_height = xorigin - 2;
		break;
	case 'u':
		xorigin += 2;
		max_height = height - xorigin;
		break;
	case 'b':
		width = field_ptr -> window -> _bot_y - field_ptr -> window -> _top_y;
		PMENU -> orient = 'h';
		max_height = field_ptr -> window -> _bot_x - field_ptr -> x_pos;
		break;
	}
		
	ncols = (--width) / maxlength;

	if( max_height < PMENU -> max_height )
		PMENU -> max_height = max_height;
	else
		max_height = PMENU -> max_height;
		
	/* check if items fit */
	if( ( max_height * ncols ) < nitems )
	{
		PMENU -> delay = -1;
		PMENU -> max_height = -1;
		return( FALSE );
	}
	if( PMENU -> orient == 'h' )
	{
		/*	all items fit - adjust height, then width */

		max_height = nitems / ncols;
		if (nitems != (ncols * max_height))
		{
			ncols = nitems / (++max_height);
			if (nitems != (max_height * ncols))
				ncols++;
		}
	}
	else
	{
		/* all items fit, adjust width, then height */
		
		ncols = nitems / max_height;
		if( nitems != (ncols * max_height ) )
		{
			max_height = nitems / (++ncols);
			if( nitems != (max_height * ncols))
				max_height++;
		}
	}		

	if( PMENU -> type == 'p' )
		xorigin -= field_ptr -> window -> _top_x;

	switch( location )
	{
	case 'r':
		/* right of field */
		break;
	case 'l':
		/* left of field */
		yorigin = width;
		width = ncols * maxlength;
		yorigin -= width;
		break;
	case 't':
		/* top of form */
		xorigin = 0;
		break;
	case 'b':
		/* bottom of form */
		xorigin = height - max_height - 2;
		if( PMENU -> type == 'p' )
			xorigin = xorigin - field_ptr -> window -> _top_x;
		if( field_ptr -> meswin != field_ptr -> window )
			xorigin += 2;
		break;
	case 'o':
	case 'a':
		/* above or over field */
		xorigin--;
	case 'u':
		/* under field */
	default:
		if( adj_xorigin )		
			xorigin -= max_height;
		yorigin = field_ptr -> y_pos +
					( ( field_ptr -> length ) / 2 ) - 2 -
					( ( ncols * maxlength ) / 2);
		if( PMENU -> type == 's' )
		{
			/* make sure do not go past right side of widow */
			width = ncols * maxlength;
			if( yorigin + width >= field_ptr -> window -> _bot_y )
				yorigin = field_ptr -> window -> _bot_y - width;
		}
		break;
	}
	width = ncols * maxlength;

	PMENU -> ncols = ncols;
	PMENU -> max_height = max_height;

	*xorig = xorigin;
	*yorig = yorigin;
	*wid = width;
	return( TRUE );
}
