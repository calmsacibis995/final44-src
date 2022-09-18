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
New_Static_Menu (field_ptr, max_height, location)
struct field_item      *field_ptr;
int     max_height;
char	*location;
{
	F_Ok (field_ptr, "New_Static_Menu");
	init_menu( field_ptr );
	_get_items( field_ptr );

	PMENU -> location = *location;
	PMENU -> type = 's';
	PMENU -> orient = 'h';
	PMENU -> pmenuwin = 0;

	/* used until setup_menu only */
	PMENU -> max_height = max_height;

	return( PMENU );
}

static_window( field_ptr, depth )
register struct field_item	*field_ptr;
int	depth;
{
	register struct SWindow	menuwin;
	int	xorigin;
	int	yorigin;
	int	width;
	struct window	*New_Rel_Window();

	width = field_ptr -> window -> _bot_y - field_ptr -> window -> _top_y;
	/* xorigin and yorigin are relative to current window */
	if( locate_window( field_ptr, &xorigin, &yorigin, &width, PMENU -> location	 ) == FALSE )
	{
		return( 1 );
	}

	if( xorigin < 0 )
		xorigin = 0;
	if( yorigin < 0 )
		yorigin = 0;
	menuwin.top_x = xorigin;
	menuwin.top_y = yorigin;
	menuwin.lines = PMENU -> max_height;
	menuwin.cols = ++width;
	menuwin.type_scroll = TRUE;
	menuwin.depth = depth;
	menuwin.box_attribute = 0;
	menuwin.box_h = '-';
	menuwin.box_v = '|';
	PMENU -> pmenuwin = New_Rel_Window ( menuwin, field_ptr -> window );
	return( 0 );
}
struct menu *
setup_static_menu( field_ptr )
register struct field_item	*field_ptr;
{
	Free_Rel_Window (PMENU -> pmenuwin);
	PMENU -> pmenuwin = 0;
	if( static_window (field_ptr, -1 ) )
		return( 0 );
	else
		return( PMENU );
}

struct menu	*
Show_Static_Menu( field_ptr )
register struct field_item	*field_ptr;
{
	if( setup_static_menu( field_ptr ) == 0 )
		return( 0 );
	write_menu (field_ptr);
	Ref_All_Windows();

	return( PMENU );
}
