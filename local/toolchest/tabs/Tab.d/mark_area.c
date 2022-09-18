/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include	<signal.h>
#include	<termio.h>
#include	<stdio.h>
#include	<setjmp.h>
#include	<string.h>
#include	"vt.h"
#include	"windows.h"
#include	"fields.h"

static char	Area_Buf[ BUFSIZ ];

move_cursor( field_ptr, y_pos )
register struct field_item	*field_ptr;
register int	y_pos;
{
	int	width;
	char	buf[ FORM_BUF ];
	char	*pch;
	int	tx_length;

	/* figure out where the txcursor should be */
	if( gl_touchedp( field_ptr ) )
		return;
	*field_ptr -> txptr = '\0';
	tx_length = f_length( field_ptr -> y_pos, field_ptr -> txbuf );
	width = y_pos - field_ptr -> y_pos;

	if( field_ptr -> txbuf == field_ptr -> txptr )
		y_pos = field_ptr -> y_pos;
	else if( width > tx_length )
	{
		width = tx_length;
		y_pos = field_ptr -> y_pos + width;
		field_ptr -> txcursor = field_ptr -> txptr;
	}
	else
	{
		strcpy( buf, field_ptr -> txbuf );
		pch = &buf[ width ];
		*pch = '\0';
	
		while( f_length( field_ptr -> y_pos, buf ) > width )
		{
			--pch;
			*pch = '\0';
		}
		field_ptr -> txcursor = field_ptr -> txbuf + ( pch - buf );
	}
	w_xgo( field_ptr -> window, field_ptr -> x_pos, y_pos );
	return( FALSE );
}

find_field( field_ptr, x_pos, y_pos )
struct field_item	*field_ptr;
int	x_pos;
int	y_pos;
{
	register struct arg_stack	*arg_stack_ptr;

	for( arg_stack_ptr = GL_Arg_Stack; arg_stack_ptr;
			arg_stack_ptr = arg_stack_ptr -> previous )
	{
		return( check_field( arg_stack_ptr -> f, arg_stack_ptr -> count, 
				field_ptr, x_pos, y_pos ) );
	}
}

struct field_item	*
check_field( f, count, field_ptr, x_pos, y_pos )
struct field_item	**f;
register int	count;
struct field_item	*field_ptr;
int	x_pos;
int	y_pos;
{
	register struct field_item	*field_p;
	register int	index = 0;

	while( index < count )
	{
		field_p = f[index++];
		if( x_pos == field_p -> x_pos )
		{
			if( y_pos >= field_p -> y_pos &&
				y_pos <= field_p -> y_pos + 
				field_p -> length )
			{
				if( !good_field( field_p ) )
				{
					continue;
				}
				return( field_p );
			}
		}
	}
	return( 0 );
}
good_field( field_ptr )
register struct field_item	*field_ptr;
{
	unsigned int *kptr;
	unsigned int key;
	register int	index = 0;
	int	length;


	if( gl_touchedp( field_ptr ) )
		return( 0 );
	if( field_ptr -> x_pos  < 0 )
		return( 0 );
	if( field_ptr -> x_pos >= 512 )
		return( 0 );
	if( field_ptr -> window -> _depth >= INVISIBLE )
		return( 0 );

	kptr = &kmap[field_ptr -> window -> _top_x + field_ptr -> x_pos]
			[field_ptr -> window -> _top_y + field_ptr -> y_pos];
	key = field_ptr -> window -> _key;
	length = strlen( field_ptr -> fill_char );

	while( index++ <= length )
	{
		if (key & *kptr++)
			/* visible */
			return( 1 );
	}
	return( 1 );
}
