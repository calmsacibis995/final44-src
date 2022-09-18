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

static struct window	*Globalwin = 0;

struct menu	*			
New_Fixed_Menu (field_ptr, window, orient)
struct field_item      *field_ptr;
struct window	*window;
char	*orient;
{
	F_Ok (field_ptr, "New_Fixed_Menu");
	init_menu( field_ptr );
	_get_items( field_ptr );

	PMENU -> type = 'f';
	PMENU -> orient = *orient;

	/* used until setup_menu only */
	if( window == 0 )
	{
		global_window( field_ptr );
		PMENU ->max_height = 1;
	}
	else
	{
		PMENU -> pmenuwin = window;
		PMENU -> max_height = window -> _bot_x - window -> _top_x;
	}
	PMENU -> ncols = ( PMENU -> pmenuwin -> _bot_y - PMENU -> pmenuwin -> _top_y )
				/ PMENU -> maxlength;

	return( PMENU );
}

global_window( field_ptr )
struct field_item      *field_ptr;
{
	register struct SWindow	menuwin;

	if( Globalwin == 0 )
	{
		menuwin.top_x = 0;
		menuwin.top_y = 0;
		menuwin.lines = 1;
		menuwin.cols = SCRWID;
		menuwin.depth = 1;
		menuwin.box_attribute = 0;
		menuwin.box_h = 0;
		menuwin.box_v = 0;
		Globalwin = New_Window ( menuwin );
	}
	PMENU -> pmenuwin = Globalwin;
}
