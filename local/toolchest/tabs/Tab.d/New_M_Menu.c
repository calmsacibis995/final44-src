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
New_Match_Menu (field_ptr, xorigin, yorigin, max_height, max_width,
	orient, type)
struct field_item      *field_ptr;
int     xorigin;
int     yorigin;
int     max_height;
int     max_width;
char   *orient;
char   *type;
{
	int	adj_xorigin;
	int	adj_yorigin;
	int     length;
	
	register struct keys   *pkeywd;

	F_Ok (field_ptr, "New_Match_Menu");
	if( *type == 'p' )
	{
		return( ( struct menu * ) New_Popup_Menu( field_ptr, 0, 0 ) );
	}
	if( *type == 'l' || *type == 'r' || *type == 't' || *type == 'b' ||
			*type == 'o' || *type == 'u' )
	{
		return( ( struct menu * ) New_Static_Menu( field_ptr, max_height, type ) );
	}
	init_menu( field_ptr );
	_get_items( field_ptr );
	if( xorigin < 0 || yorigin < 0 )
	{
		xorigin = field_ptr -> window -> _top_x + field_ptr -> x_pos;
		yorigin = 0;
		adj_yorigin = 1;
		max_width = stdwindow -> _bot_y - stdwindow -> _top_y;

		if( xorigin + xorigin > stdwindow -> _bot_x )
		{
			/* bottom half */
			xorigin = xorigin - 1;
			max_height = xorigin;
			adj_xorigin = 1;
		}
		else
		{
			/* top half */
			adj_xorigin = 0;
			xorigin = xorigin + 2;
			max_height = field_ptr -> window -> _bot_x - xorigin;
		}
		max_height--;
	}
	else
	{
		adj_xorigin = 0;
		adj_yorigin = 0;
	}
		
	PMENU -> ncols = (--max_width) / PMENU -> maxlength;

	/* check if items fit - if not - check max length for MORE stuff */
	if( ( max_height * PMENU -> ncols ) < PMENU -> nitems )
	{
		PMENU -> delay = -1;
		return( PMENU );
	}
	
	else if (*orient == 'v')
	{
	/*	all items fit - adjust width, then height */

		PMENU -> ncols = PMENU -> nitems / max_height;
		if (PMENU -> nitems != (PMENU -> ncols * max_height))
		{
			max_height = PMENU -> nitems /
				(++PMENU -> ncols);
			if (PMENU -> nitems != (max_height *
						PMENU -> ncols))
				max_height++;
		}
	}
	else
	{
		/*	all items fit - adjust height, then width */

		max_height = PMENU -> nitems / PMENU -> ncols;
		if (PMENU -> nitems != (PMENU -> ncols * max_height))
		{
			PMENU -> ncols = PMENU -> nitems / (++max_height);
			if (PMENU -> nitems != (max_height * PMENU -> ncols))
				PMENU -> ncols++;
		}
	}

	if( adj_xorigin )
		xorigin -= max_height;
	if( adj_yorigin )
		yorigin = field_ptr -> window -> _top_y + field_ptr -> y_pos + 
				( strlen( field_ptr -> fill_char ) / 2 ) - 2 -
				( ( PMENU -> ncols * PMENU -> maxlength ) / 2);

/*	save useful stuff	*/

	PMENU -> type = 's';
	PMENU -> delay = 0;
	PMENU -> first_time = 1;
	PMENU -> max_num_sel = 1;
	PMENU -> index_sel = (int *) malloc( 12 );
	PMENU -> index_sel[ 0 ] = 0;
	PMENU -> index_sel[ 1 ] = -1;
	INDEX = -1;

	make_window (field_ptr, field_ptr -> window -> _depth - 1, max_height,
			 xorigin, yorigin );

	return (PMENU);
}
make_window( field_ptr, depth, height, row, column )
register struct field_item	*field_ptr;
int	depth;
int	height;
int	row;
int	column;
{
	register struct SWindow	menuwin;
	int	max_width;
	
	max_width = PMENU -> ncols * PMENU -> maxlength;

	menuwin.top_x = row;
	menuwin.top_y = column;
	menuwin.lines = height;
	menuwin.cols = ++max_width;
	menuwin.type_scroll = TRUE;
	menuwin.depth = depth;
	menuwin.box_attribute = 0;
	menuwin.box_h = '-';
	menuwin.box_v = '|';
	PMENU -> pmenuwin = New_Window (menuwin);
	Ref_All_Windows ();
	
	write_menu( field_ptr );
}
