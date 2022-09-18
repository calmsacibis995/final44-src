/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include	<errno.h>
#include	<stdio.h>
#include	<setjmp.h>
#include	<string.h>
#include	"vt.h"
#include	"windows.h"
#include	"fields.h"
#include	"menus.h"

struct menu	*
New_Popup_Menu (field_ptr, delay, location)
struct field_item      *field_ptr;
int	delay;
char	*location;
{
	struct window	*init_window();
	
	F_Ok (field_ptr, "New_Popup_Menu");
	init_menu( field_ptr );

	PMENU -> location = *location;
	PMENU -> type = 'p';
	PMENU -> orient = 'v';
	PMENU -> delay = delay;

	if( Pmenuwin == 0 )
		Pmenuwin = init_window( SCRNLIN );

	PMENU -> pmenuwin = Pmenuwin;
	return ( PMENU );
}

popup_window( field_ptr )
register struct field_item	*field_ptr;
{
	int	max_width;
	int	xorigin;
	int	yorigin;

	PMENU -> max_height = 100;

	/* xorigin and yorigin will be  relative coordinates to current window */
	locate_window( field_ptr, &xorigin, &yorigin, &max_width, PMENU -> location );

	Clear_Form( Pmenuwin );
	Pmenuwin -> _top_x = 0;
	Pmenuwin -> _top_y = 0;
	Pmenuwin -> _bot_x = PMENU -> max_height;
	Pmenuwin -> _bot_y = ++max_width;
	Move_Window( Pmenuwin, xorigin + field_ptr -> window -> _top_x, 
		yorigin + field_ptr -> window -> _top_y, INVISIBLE );
	PMENU -> pmenuwin = Pmenuwin;

	write_menu( field_ptr );
}
