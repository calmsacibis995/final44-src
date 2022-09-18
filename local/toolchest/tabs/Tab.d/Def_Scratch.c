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
#include <string.h>
#include "vt.h"
#include "windows.h"
#include "fields.h"

/* marked area operations */
#define AREA_KOPY_MODE	7
#define AREA_KUT_MODE	6
#define AREA_APPEND	5
#define AREA_DELETE	4
#define AREA_COPY	3
#define AREA_CUT	2
#define AREA_UNMARK	1
#define AREA_MARK	0

struct pad
{
	struct pad	*next;
	struct pad	*previous;
	char	*txbuf;
};
static struct pad	*First_Pad = 0;
static struct pad	*Last_Pad = 0;

static struct field_item *Field_Ptr;

/*
 *	This routine handles the input of an area character.
 */
Def_Scratchpad( flag )
int	flag;
{
	extern int	area_char();
	
	if( flag )
		Def_Char_Action( CTRL(X), CORRECT, area_char, 0 );
	else
		Def_Char_Action( CTRL(X), NORMAL, 0, 0 );
	Def_Keep_Position( TRUE );
	Def_Marked_Areas( TRUE );
	Def_Area_Attributes( FAREVV );
}

area_char (field_ptr, rc)
register struct field_item *field_ptr;
register char    rc;
{
	register int	i;
	char	c;
	int	area_op;
	int	y_pos;

	switch (rc & 0377)
	{
	case CTRL(X):
		c = getachar( field_ptr );
		switch( c & 0377 )
		{
		case 'c':
		case 'C':
			area_op = AREA_COPY;
			break;
		case 'a':
		case 'A':
			area_op = AREA_APPEND;
			break;
		case 'X':
		case 'x':
			area_op = AREA_CUT;
			break;
		case 'u':
		case 'U':
			Clear_Marked_Areas();
/*			move_txcursor( field_ptr, Area[0].top_y - field_ptr -> window -> _top_y ); */
			return( FALSE );
		case 'd':
		case 'D':
			area_op = AREA_DELETE;
			break;
		case 'P':
		case 'p':
			y_pos = mcol;
			paste_a_buf( field_ptr );
/*			move_txcursor( field_ptr, y_pos - field_ptr -> window -> _top_y); */
			return( FALSE );
		default:
			_ungetc( c );
			return( FALSE );
		}
		if( area_op && Area[0].bot_y )
		{
			for( i = 0; i < 3; i++ )
			if( Area[i].bot_y )
				do_area( field_ptr, &Area[i], area_op, 0 );
			Clear_Marked_Areas();

			if( field_ptr != Field_Ptr )
			{
				/* treat as a break character and position cursor */
				MOUSE_X = Area[0].top_x;
				MOUSE_Y = Area[0].top_y;
				*((field_ptr->txptr)++) = K_MOUSE;
				field_ptr -> txflg |= TXBRK;
				return( TRUE );
			}
/*			else
				move_txcursor( Field_Ptr, Area[0].top_y - Field_Ptr -> window -> _top_y );
*/
		}
		else
			Print_Message( field_ptr -> meswin, Mess_Attribute,
				"No area marked" );
		break;
	default:
		break;
	}
	return( FALSE );
}

do_line( field_ptr, left_y, right_y, area_op, attribute )
register struct field_item	*field_ptr;
int	left_y;
int	right_y;
int	area_op;
int	attribute;
{
	register int	width;
	register int	i;
	register char	*pch;
	register char	*pch2;
	char	ch;
	int	tx_y_end;
	int	y_plus = 0;
	char	buf[ FORM_BUF ];
	char	buf2[ FORM_BUF ];
	struct pad	*new_pad();
	int	win_width;
	int	field_y_p;

	*field_ptr -> txptr = '\0';
	win_width = field_ptr -> window -> _bot_y - field_ptr -> window -> _top_y;
	field_y_p = field_ptr -> y_pos + field_ptr->window->_top_y;

	tx_y_end = field_y_p + f_length( field_ptr -> y_pos, 
			field_ptr -> txbuf );
	if( left_y > tx_y_end || right_y < field_y_p )
		return(0);
	if( right_y > tx_y_end )
		right_y = tx_y_end;
	if( left_y < field_y_p )
		left_y = field_y_p;

	/* figure out where the txcursor is for right_y */
		
	width = right_y - field_y_p;
	strcpy( buf, field_ptr -> txbuf );
	pch = &buf[ width ];
	ch = buf[ width ];
	*pch = '\0';

	while( f_length( field_ptr -> y_pos, buf ) > width )
	{
		*pch = ch;
		--pch;
		ch = *pch;
		*pch = '\0';
	}
	pch2 = pch;
	/* do same for left_y */
	width = left_y - field_y_p;
	strcpy( buf2, field_ptr -> txbuf );
	pch = &buf2[ width ];
	*pch = '\0';

	while( f_length( field_ptr -> y_pos, buf2 ) > width )
	{
		--pch;
		*pch = '\0';
	}
	y_plus = pch - buf2;
	/* copy to buffer */
	if( area_op != AREA_DELETE )
	{
		Last_Pad = new_pad( Last_Pad, &buf[ y_plus ], TRUE );
	}

	/*	restore missing character from buf */
	*pch2 = ch;

	if( area_op == AREA_COPY || area_op == AREA_APPEND )
		return( field_ptr -> y_pos + 
				field_ptr -> txcursor - 
				field_ptr -> txbuf );
			
	field_ptr -> txcursor = field_ptr -> txbuf + y_plus;
	strcat( buf2, pch2 );
	strcpy( field_ptr -> txbuf, buf2 );
	y_plus = field_ptr -> y_pos + y_plus;

	LeftString( field_ptr -> window,
			field_ptr -> x_pos,
			field_ptr -> y_pos,
			field_ptr -> fill_char,
			field_ptr -> txbuf,
			field_ptr -> attribute );
	field_ptr -> txptr = field_ptr -> txbuf + strlen( field_ptr -> txbuf );
	return( y_plus );
}

paste_a_buf( field_ptr )
register struct field_item	*field_ptr;
{
	register int	y_pos;
	int	ret_code = 0;
	register char	buf2[ FORM_BUF ];
	register char	buf3[ FORM_BUF ];
	int	kount;
	register struct field_item	*field_p;
	register int	i;
	register char	ch;
	int	buf_length;
	int	width;
	register char	*pch;
	char	*pend;
	register int	index;
	int	length;
	register struct pad	*pad;

	if( First_Pad == 0 )
	{
		Print_Message( field_ptr -> meswin, Mess_Attribute, 
				"There is nothing to paste" );
		return( -1 );
	}

	i = *GL_Arg_Stack -> ptr_index;
	kount = GL_Arg_Stack -> count;
	for( pad = First_Pad; pad; pad = pad -> next, i++ )
	{
		if( i > kount )
		{
			i--;
			ret_code = -1;
			break;
		}
		field_p = GL_Arg_Stack -> f[i];
		*field_p -> txptr = '\0';

		if( gl_touchedp( field_p ) ) continue;
			
		width = field_p -> txcursor - field_p -> txbuf;

		strcpy( buf2, field_p -> txbuf );
		pch = &buf2[ width ];
		strcpy( buf3, pch );

		strcpy( pch, pad -> txbuf );
		strcat( pch, buf3 );

		/* see if it fits into field */
		
		pend = buf2 + strlen( buf2 );
		while( ( f_length( field_p -> y_pos, buf2 ) ) > 
				field_p -> length )
		{
			*(--pend) = '\0';
			ret_code = -1;
		}
		Show_Default_Field( field_p, buf2 );
	}

ret:	if( ret_code < 0 )
	{
		Print_Message( field_ptr -> meswin, Mess_Attribute, 
			"Could not paste everything because a field was too small or was protected." );
		return( ret_code );
	}
	return( i );
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

do_area( field_ptr, area_ptr, area_op, attribute )
register struct field_item	*field_ptr;
struct Area	*area_ptr;
int	area_op;
int	attribute;
{
	register int	i;
	register struct field_item	*field_p;
	register x_pos;
	register y_pos;
	int	end_y_pos;
	int	end_x_pos;
	int	top_x;		/* top rowof area area */
	int	bottom_x;	/* bottom row of area area */
	int	top_y;		/* column on top row of area area */
	int	bottom_y;	/* column on bottom row of area area */
	int	left_y;		/* leftmost column of either top or bottom area */
	int	right_y;	/* rightmost column of either top or botom area */
	int	end_y = 0;
	int	kount;
	int	temp_y;
	int	field_x_p;
	
	end_x_pos = area_ptr -> bot_x;
	end_y_pos = area_ptr -> bot_y + 1;
	x_pos = area_ptr -> top_x;
	y_pos = area_ptr -> top_y;
	
	if( x_pos > end_x_pos )
	{
		bottom_x = x_pos;
		top_x = end_x_pos;
		bottom_y = y_pos;
		top_y = end_y_pos;
	}
	else
	{
		bottom_x = end_x_pos;
		top_x = x_pos;;
		bottom_y = end_y_pos;
		top_y = y_pos;
	}
	if( y_pos > end_y_pos )
	{
		left_y = end_y_pos;
		right_y = y_pos;
	}
	else
	{
		left_y = y_pos;
		right_y = end_y_pos;
	}
	if( area_op == AREA_COPY || area_op == AREA_CUT )
		free_pad();
	kount = GL_Arg_Stack -> count;
	Field_Ptr = 0;
	for( i = 0; i < kount; i++ )
	{
		field_p = GL_Arg_Stack -> f[i];
		if( !good_field( field_p ) )
			continue;
		if ((field_p->attribute & FAINVISIBLE) && (area_op != AREA_DELETE))
		{
			Print_Message( field_p->meswin, Mess_Attribute, "You cannot write to the scratchpad from an invisible field");
			sleep( 2 );
			continue;
		}

		/* we don't do multi-line fields yet */
		field_x_p = field_p -> x_pos + field_p->window->_top_x;
		if( field_x_p >= top_x && field_x_p <= bottom_x )
			temp_y = do_line( field_p, left_y, right_y, area_op, attribute );

		if( Field_Ptr == 0 && temp_y > 0 )
			Field_Ptr = field_p;
	}

	return;
}

struct pad	*
new_pad( old_pad, string, after )
struct pad	*old_pad;
char	*string;
int	after;
{
	register struct pad	*pad;

	pad = (struct pad *) malloc( sizeof( struct pad ) );
	if( pad == NULL )
	{
		mal_err( "scratchpad" );
	}
	if( after )
	{
		pad -> previous = old_pad;
		if( pad -> previous )
			pad -> next = pad -> previous -> next;
		else
			pad -> next = 0;
	}
	else
	{
		pad -> next = old_pad;
		if( pad -> next )
			pad -> previous = pad -> next -> previous;
		else
			pad -> previous = 0;
	}
	if( pad -> previous )
		pad -> previous -> next = pad;
	else
		First_Pad = pad;
	if( pad -> next )
		pad -> next -> previous = pad;
	pad -> txbuf = (char *)malloc( strlen( string) + 1 );
	if( pad -> txbuf == NULL )
		mal_err( "scratchpad string" );
	strcpy( pad -> txbuf, string );
	return( pad );
}

free_pad()
{
	register struct pad	*pad;
	pad = First_Pad;
	if( pad )
	{
		free( pad -> txbuf );
		free( pad );
		pad = pad -> next;
	}
	First_Pad = 0;
	Last_Pad = 0;
}

mal_err( string )
register char	*string;
{
	Print_Message( Field_Ptr -> window, Mess_Attribute, "Could not allocate space for %s", string );
	sleep( 5 );
	End_Form();
	exit( 1 );
}

