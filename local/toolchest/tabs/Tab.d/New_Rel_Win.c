/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/* Create a window within a hierarchical tree of windows.  A window is positioned
	relative to another window so that when the other window is moved or deleted
	all windows below it in the tree are appropriately moved or deleted
	User level commands contained here are New_Rel_Window,Free_Rel_Window
	and Move_Rel_Window.
*/

#include	<stdio.h>
#include	<setjmp.h>
#include	<errno.h>
#include	"vt.h"
#include	"windows.h"
#include	"fields.h"

struct node
{
	struct node	*up;
	struct node	*down;
	struct node	*right;
	struct node	*left;
	struct window	*window;
};

struct node	*start_node = 0;

struct window *
New_Rel_Window( SWindow, up_window )
struct SWindow	SWindow; /* pointer to definition of new window */
struct window	*up_window; /* pointer to window that new window is to be
			       positioned relative to and placed under in the
			       hierarchical list of windows */
{
	register struct node	*new_node;
	register struct node	*next_node;
	register struct node	*up_node;
	struct window	*new_window;
	struct node	*find_node();
	struct node	*make_node();

	/* find up_window structure - if none, find_node makes a new node */
	up_node = find_node( up_window, TRUE );

	/* make new window */
	SWindow.top_x += up_node -> window -> _top_x;
	SWindow.top_y += up_node -> window -> _top_y;
	SWindow.depth += up_node -> window -> _depth;
	
	if( ( new_window = New_Window( SWindow ) ) < 0 )
		return( (struct window *) -1 );
	new_node = make_node( new_window );

	/* position the node in the tree */

	new_node -> up = up_node;
	if( up_node -> down )
	{
		next_node = up_node -> down;
		while( next_node -> right )
			next_node = next_node -> right;
		next_node -> right = new_node;
		new_node -> left = next_node;
	}
	else
	{
		up_node -> down = new_node;
	}
	return( new_window );

}

struct node *
find_node( window, create_flag )
struct window	*window;
int	create_flag;
{
	register struct node	*next_node;
	register struct node	*cur_node;
	register struct node	*new_node;
	struct node	*make_node();
	
	W_Ok( window, "find_node" );
	if( create_flag == FALSE && start_node == 0 )
		return( NULL );
	if( start_node == 0 )
	{
		new_node = make_node( window );
		start_node = new_node;
		new_node -> left = 0;
		return( new_node );
	}
	next_node = start_node;

	/* order to try to go:
		down
		right
		up until can go to right (go back to down) or at end
	 */

		
	while( TRUE )
	{
		cur_node = next_node;
		if( cur_node -> window == window )
			return( cur_node );

		/* go down if can */
		if( next_node = cur_node -> down );

		/* go up if can */
		else if( next_node = cur_node -> right );

		else 
		{
			next_node = cur_node;
			while( TRUE )
			{
				cur_node = next_node;
				if( next_node = cur_node -> up )
				{
					if( next_node -> right )
					{
						next_node = next_node -> right;
						break;
					}
				}
				else
				{
					if( create_flag == FALSE )
					{
						/* end of list, unknown
						 * window - return error
						 */
						return( NULL );
					}
					/* end of list, unknown window - add */
					new_node = make_node(window);
					cur_node -> right = new_node;
					new_node -> left = cur_node;
					return( new_node );
				}
			}
		}
	}
}

struct node *
make_node( window )
struct window	*window;
{
	struct node	*new_node;
	
	W_Ok( window, "make_node" );
	new_node = ( struct node * ) malloc( sizeof( struct node ) );
	new_node -> window = window;
	new_node -> right = 0;
	new_node -> up = 0;
	new_node -> down = 0;
	new_node -> left = 0;
	return( new_node );
}

Free_Rel_Window( window )
struct window	*window;
{
	register struct node	*cur_node;
	register struct node	*next_node;
	struct node	*find_node();
	
	/* find node */
	W_Ok( window, "Free_Rel_Window" );
 	if( ( next_node = find_node( window, FALSE ) ) == NULL )
	{
		Free_Window( window );
		return(0);
	}
	
	
	/* free all dependent nodes and cur_node, then eliminate
	   current node from list and set
	   node -> up = 0 so can figure out when to stop */

	if( next_node -> up -> down == next_node )
		if( next_node -> right )
			next_node -> up -> down = next_node -> right;
		else
			next_node -> up -> down = 0;
	if( next_node -> left )
		next_node -> left -> right = next_node -> right;
	if( next_node -> right )
		next_node -> right -> left = next_node -> left;
	next_node -> up = 0;
	next_node -> right = 0;
		
/*	free if can not go down or if on the way up */

	while( TRUE )
	{
		cur_node = next_node;

		if( cur_node -> down )
		{
			next_node = cur_node -> down;
			/* won't go down this way again */
			cur_node -> down = 0;
			continue;
		}
		if( next_node = cur_node -> right );
		else if( next_node = cur_node -> up );
		else
		{
			/* done */
			Free_Window( cur_node -> window );
			free( cur_node );
			cur_node = 0;
			return( 0 );
		}
		Free_Window( cur_node -> window );
		free( cur_node );
		cur_node = 0;
	}
}

Move_Rel_Window( window, toprow, topcolumn, depth )
struct window	*window;
int	toprow;
int	topcolumn;
int	depth;
{
	struct node	*find_node();
	register struct node	*cur_node;
	register struct node	*next_node;
	register int	delta_x;
	register int	delta_y;
	register int	delta_z;

	W_Ok( window, "Move_Rel_Window" );
	/* find node - do not create a node if not already a node */
	if( ( cur_node = find_node( window, FALSE ) ) == NULL )
	{
		Move_Window( window, toprow, topcolumn, depth );
		return( -1 );
	}
	
	/* find distance and depth to move window */
	if( toprow <= stdwindow -> _top_x )
		toprow = stdwindow -> _top_x  + 1;

	if( topcolumn <= stdwindow -> _top_y )
		topcolumn = stdwindow -> _top_y + 1;

	delta_x = cur_node -> window -> _top_x;
	delta_y = cur_node -> window -> _top_y;
	delta_z = cur_node -> window -> _depth;

	Move_Window( cur_node -> window, toprow, topcolumn, depth );

	if( cur_node -> down == 0 )
		return( 0 );

	delta_x -= cur_node -> window -> _top_x;
	delta_y -= cur_node -> window -> _top_y;
	delta_z -= cur_node -> window -> _depth;

	/* create check to determine when done */	

	next_node = cur_node -> down;
	
	/* move all windows in dependent nodes */
	
	while( TRUE )
	{
		cur_node = next_node;
		
		Move_Window( cur_node -> window,
				cur_node -> window -> _top_x - delta_x,
				cur_node -> window -> _top_y - delta_y,
				cur_node -> window -> _depth - delta_z );

/*		Ref_All_Windows (); */

		if( next_node = cur_node -> down );

		else if( next_node = cur_node -> right );

		else 
		{
		    next_node = cur_node;
		    while( TRUE )
		    {
			if( next_node = next_node -> up )
			{
				if( next_node -> window == window )
					/* done */
					return( 0 );
				else
					if( next_node = next_node -> right );
						break;
			}
			else
				return( -1 );
		    }
		}
	}
}
