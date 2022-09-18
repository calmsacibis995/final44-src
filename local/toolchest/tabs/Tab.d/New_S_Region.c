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

struct field_item	*
New_Scroll_Region( row, col, height, width, sample_list, count, repetitions, skip,
		region_list, rel_window)
int	row;
int	col;
int	height;
int	width;
struct field_item	**sample_list;
int	count;
int	repetitions;
int	skip;
struct field_item	**region_list;
{
	register int	i;
	char	*sub_name;
	struct SWindow	setup_win;
	struct window	*reg_window;

	sub_name = "New_Scroll_Region";
	for( i = 0; i < count; i++ )
		F_Ok( sample_list[i], sub_name );
	if( rel_window )
		W_Ok( rel_window, sub_name );

	if( count <= 0 )
	{
		Print_Message( sample_list[0]->meswin, Mess_Attribute, "count <= 0 in %s", sub_name );
		return( 0 );
	}
	if( repetitions <= 0 )
	{
		Print_Message( sample_list[0]->meswin, Mess_Attribute, "repetitions <= 0 in %s", sub_name );
		return( 0 );
	}
	if( skip <= 0 )
	{
		Print_Message( sample_list[0]->meswin, Mess_Attribute, "skip < 0 in %s", sub_name );
		return( 0 );
	}

	setup_win.top_x = row;
	setup_win.top_y = col;
	setup_win.lines = height;
	setup_win.cols = width;
	setup_win.box_h = '-';
	setup_win.box_v = '|';
	if( rel_window )
		setup_win.depth = -1;
	else
		setup_win.depth = sample_list[0] -> window -> _depth - 1;
	setup_win.box_attribute = FANORMAL;
	reg_window = New_Rel_Window( setup_win, rel_window );
	if( reg_window == 0 )
	{
		Print_Message( sample_list[0]->meswin, Mess_Attribute, "row, column, height or width incorrectly specified in %s", sub_name );
		return( 0 );
	}

	New_Region( reg_window, sample_list, count, repetitions * count, region_list, skip );
	return( New_Field( row, col, CMREGN, (char *) region_list, 
			(char *) repetitions, 0) );
}	
