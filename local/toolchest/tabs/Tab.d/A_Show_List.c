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

struct window	*
Auto_Show_List( f, nfields, start_index, adj_type, between_rows, field_width, 
		field_cols, start_row, Winner, up_winner, win_row, win_col, rel_depth,
		recurse_flag )
register struct field_item	**f;
int	nfields;
int	start_index;
int	adj_type[];
register int	between_rows;
register int	field_width;
int	field_cols;
int	start_row;
struct window	*Winner;
struct window	*up_winner;
int	win_row;	/* last three have no effect if Winner != 0 */
int	win_col;
int	rel_depth;
int	recurse_flag;
{
	int	inc_field_row = 0;
	register int	col = 0;
	register int	field_row;
	int	bet_col = 2;
	register int	col_width = 0;
	register int	max_col;
	register int	width;
	int	label_len;
	struct menu	*pmenu;
	struct menu	*setup_menu();
	extern int	cmmenu();
	int	depth;
	register int	index;
	struct SWindow	setup_win;
	int	win_width;
	struct field_item	*static_bottom = 0;
	struct field_item	*static_top = 0;
	int	old_depth;
	int	old_bot_y;
	int	x_diff;
	int	y_diff;
	int	z_diff;
	int	add_field_row = 0;

	field_row = start_row;

	if( up_winner == 0 )
		up_winner = stdwindow;
	win_width = ( field_cols * field_width ) + 2;

	if( Winner == 0 )
	{
		if( win_width + col + up_winner -> _top_y > SCRWID )
			win_width = SCRWID - win_col - up_winner -> _top_y;
		if( win_width < field_width )
			win_width = field_width;
		setup_win.top_x = win_row;
		setup_win.top_y = win_col;
		setup_win.lines = SCRNLIN - win_row - 2;
		setup_win.cols = win_width;
		setup_win.depth = rel_depth - 100;
		setup_win.type_scroll = TRUE;
		setup_win.box_attribute = 0;
		setup_win.box_h = '-';
		setup_win.box_v = '|';
		/*make the window at the bottom */

		old_bot_y = stdwindow -> _bot_y;
		old_depth = stdwindow -> _depth;
		index = start_index;
		while( index < nfields )
		{
			Set_Window( f[index++], stdwindow, 0, 0 );
		}
		Pop_Window( stdwindow, INVISIBLE + 100 );
		stdwindow -> _bot_y = stdwindow -> _top_y + win_width - 2;
	}
	else
	{
		index = start_index;
		while( index < nfields )
		{
			Set_Window( f[index++], Winner, 0, stdwindow );
		}
		win_width = Winner -> _bot_y - Winner -> _top_y + 1;
	}
	index = start_index;

	/* from this point win_width is width within frame */
	win_width -= 2;


	/* turn any unreasonable parameters into reasonable ones */
	if(field_width > win_width )
		field_width = win_width;
	if( win_width < ( field_width * field_cols ) )
	{
		if( ( ( field_width - 1 ) * field_cols ) <= win_width )
		{
			bet_col--;
			field_width--;
		}
		if( ( field_cols = win_width / field_width ) <= 0 )
			field_cols = 1;
	}

	col = 0;
	if( index )
	{
		/* figure out col_width */
			col_width = f[index - 1] -> length + f[index - 1] -> y_pos;
		if( f[index - 1] -> label -> where == 'l' );
			col_width += strlen( f[index - 1] -> label -> string );
			
		
		/* find row */
		field_row = f[index - 1] -> x_pos;
	}
	else
		col_width = 0;

	while( index < nfields )
	{
		if( f[index] -> label )
			label_len = strlen( f[index] -> label -> string );
		else
			label_len = 0;
			
		width = f[index] -> length + bet_col + label_len;
				
		switch( adj_type[index] )
		{
		case C_NOADJ:
			index++;
			continue;
		case C_SKIPROW:
			field_row++;
		case C_STARTROW:
			col = 0;
			inc_field_row = 1;
			break;
		case C_SKIPCEN:
			field_row++;
		case C_CENTER:
			/* figure out where field should start */
			col = ( ( win_width - ( width - bet_col ) ) / 2 ) -
					bet_col;
			width = win_width - col - 2; /* ensures no other fields
						      * on this line
						      */
			break;
		case C_SKIPCOL:
			col += field_width;
		case C_RIGHT:
			col += col_width;
			break;
		default:
			break;
		}
		col_width = 0;

		while( ( col_width += field_width ) < width );

		if( ( col + width ) > win_width )
		{
			col = 0;
			inc_field_row = 1;
		}

		f[index] -> y_pos =  bet_col + col;
		if( f[index] -> label -> where == 'l' )
			f[index] -> y_pos += label_len;

		if( f[index] -> type == cmmenu )
		{
			pmenu = ( struct menu * ) f[index] -> user_pointer;
			
			if( pmenu -> type == 's' )
			{
				/* so knows where to put the menu */
				f[index] -> x_pos = field_row;
				switch( pmenu -> location )
				{
				case 'a':
				case 'o':
					 /* so has somewhere to put the menu */
					if( index )
						field_row += ( between_rows + 1 );
					if( col )
					{
						f[index] -> y_pos =  bet_col;
						if( f[index] -> label -> where == 'l' )
							f[index] -> y_pos += label_len;
						col = 0;
					}
					f[index] -> x_pos = pmenu -> 
						max_height + field_row;

					if( setup_static_menu( f[index] ) == 0 )
						return( 0 );
					Move_Rel_Window( pmenu -> pmenuwin,
						field_row - 1,
						pmenu -> pmenuwin -> _top_y ,
						pmenu -> pmenuwin -> _depth );

					field_row += ( pmenu -> max_height + 1 );
					inc_field_row = 0;
					break;
				case 'u':
					 /* so knows where to put menu */
					if( setup_static_menu( f[index] ) == 0 )
						return( 0 );
					add_field_row = ( pmenu -> max_height + 2 );
					break;
				case 't':
					if( recurse_flag == TRUE )
					{
						f[index] -> x_pos += 
							( pmenu -> max_height );
						if( setup_static_menu( f[index] ) == 0 )
							return( 0 );
						start_row += ( pmenu -> max_height + 1 );
						stdwindow -> _bot_y = old_bot_y;
						Pop_Window( stdwindow, old_depth );
						Free_Menus( f, index + 1 );
						return( Auto_Show_List( 
							f, 
							nfields, 
							start_index, 
							adj_type, 
							between_rows, 
							field_width, 
							field_cols, 
							start_row, 
							Winner, 
							up_winner, 
							win_row, 
							win_col, 
							rel_depth,
							FALSE ) );
					}
					static_top = f[index];
					break;
				case 'b':
					if( setup_static_menu( f[index] ) == 0 )
						return( 0 );
					Free_Rel_Window( pmenu -> pmenuwin );
					pmenu -> pmenuwin = 0;
					static_bottom = f[index];
					break;
				case 'r':
					Print_Message( f[index]->meswin,Mess_Attribute, "A static menu can not be automatically placed to the right of a field" );
					break;
				case 'l':
					Print_Message( f[index]->meswin,Mess_Attribute, "A static menu can not be automatically placed to the left of a field" );
					break;
				default:
					break;
				}
			}
		}
		
		if( inc_field_row )
			field_row += between_rows;
		inc_field_row = 0;
		
		f[index] -> x_pos = field_row;

		/* adjust start for multi-line field */
		field_row += f[index] -> length / win_width;
		/* adjust for other */
		if( add_field_row )
		{
			field_row += add_field_row;
			col = win_width;
			add_field_row = 0;
		}

		index++;
	}
	

	field_row++;

	if( static_bottom != 0 )
	{
		field_row += (( struct menu * )static_bottom -> user_pointer ) -> max_height + 1;
	}

/*	automatic windows should not have message lines because usually too
 *	small - message line should always go to stdwindow

 	if( f[ 0 ] -> meswin == Winner )
		field_row++;
*/
	if( Winner == 0 )
	{
		if( field_row > SCRNLIN - 3 )
		{
			field_row = SCRNLIN - 2;
		}
		setup_win.lines = field_row;

		if( field_row + 2 + win_row > SCRNLIN )
		{
			win_row = SCRNLIN - 2 - field_row;
			if( win_row < 1 )
			{
				/* perhaps should call Auto_Show_List recursively
				 * with wider window and more columns
				 */
				Print_Message( stdwindow, Mess_Attribute, 
					"not enough room to show all of form" );
				win_row = 1;
			}
			setup_win.top_x = win_row;
		}
		Winner = New_Rel_Window( setup_win, up_winner );
		for( index = start_index; index < nfields; index++ )
		{
			Set_Window( f[index], Winner, 0, 0 );
			if( f[index] -> type != cmmenu )
				continue;
			pmenu = ( struct menu * ) f[index] -> user_pointer;

			if( pmenu -> type != 's' ||
					pmenu -> location == 't' ||
					pmenu -> location == 'b' )
			{
				continue;
			}


			Change_Parent( pmenu -> pmenuwin, Winner );
			write_menu( f[index] );
		}
		stdwindow -> _bot_y = old_bot_y;
		Pop_Window( stdwindow, old_depth );
	}
	
	if( static_bottom )
		if( Show_Static_Menu( static_bottom ) == 0 )
			return( 0 );

	if( static_top )
		if( Show_Static_Menu( static_top ) == 0 )
			return( 0 );

	ReShow_List( f, nfields, FALSE );
	Ref_All_Windows();
	return( Winner );
}

Free_Auto_List( f_list, nfields )
register struct field_item	**f_list;
register int	nfields;
{
	register int	index = 0;

	if( f_list[0] -> window != stdwindow )
	{
		Push_Window( f_list[0] -> window );
		Free_Rel_Window( f_list[0] -> window );
		f_list[0] -> window = 0;
	}
	else
		Clear_Form( f_list[0] -> window );

	while( index < nfields ) 
	{
		if( f_list[index] -> type == cmmenu )
			Free_Match_Menu( f_list[index] );
		Free_Field( f_list[index++] );
	}
}
Free_Menus( f_list, nfields )
register struct field_item	**f_list;
register int	nfields;
{
	register int	index = 0;
	register struct menu	*pmenu;

	while( index < nfields ) 
	{
		if( f_list[index] -> type != cmmenu )
			continue;
		pmenu = ( struct menu *) f_list[index] -> user_pointer;
		if( pmenu -> type != 'p' )
		{
			Free_Rel_Window (pmenu -> pmenuwin);
			pmenu -> pmenuwin = 0;
		}
		index++;
	}
}
