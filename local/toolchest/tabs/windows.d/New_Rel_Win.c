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

struct win_node
{
	struct win_node	*up;
	struct win_node	*down;
	struct win_node	*right;
	struct window	*window;
};

struct win_node	*First_Node = 0;

struct window *
New_Rel_Window( SWindow, parent_window )
struct SWindow	SWindow; /* structure that defines new window */
struct window	*parent_window; /* pointer to window that new window is to be
			       positioned relative to and placed under in the
			       hierarchical list of windows */
{
	register struct win_node	*new_win_node;
	register struct win_node	*parent_node;
	struct window	*new_window;
	struct win_node	*find_win_node();
	struct win_node	*make_win_node();

	/* find parent_window structure - if none, find_win_node makes a new node */
	parent_node = find_win_node (parent_window);

	/* make new window */
	SWindow.top_x += parent_node -> window -> _top_x;
	SWindow.top_y += parent_node -> window -> _top_y;
	SWindow.depth += parent_node -> window -> _depth;
	
	if( ( new_window = New_Window( SWindow ) ) == 0 )
		return( (struct window *) -1 );

	/* make the node and then position the node in the hierarchy */
	new_win_node = make_win_node (new_window);
	remove_win_node (new_win_node);
	position_win_node (new_win_node, parent_node);
	return( new_window );
}

struct win_node *
find_win_node (window)
struct window	*window;
{
	struct win_node	*win_node;
	struct win_node	*find_win_node();
	struct win_node	*find_node();
	struct win_node	*make_win_node();
	
	/* First_Node is top node in the hierarchy */
	if ((win_node = find_node (window, First_Node)) == 0)
		/* no node - make one */
		win_node = make_win_node (window);
	return (win_node);
}

struct win_node *
find_node (window, win_node)
struct window	*window;
struct win_node	*win_node;
{
	struct win_node	*found;

	if (win_node == 0) return (0);

	/* end search if windows match */
	if (window == win_node -> window) return (win_node);

	/* recurse downward */
	if ((found = find_node (window, win_node -> down)) != 0) return (found);

	/* recurse to right */
	return (find_node (window, win_node -> right));
}

struct win_node *
make_win_node( window )
struct window	*window;
{
	struct win_node	*new_node;

	if (window == 0)
		return (First_Node);

	new_node = (struct win_node * ) malloc (sizeof (struct win_node));
	new_node -> window = window;
	new_node -> right = 0;
	new_node -> up = 0;
	new_node -> down = 0;
	if (First_Node == 0)
		First_Node = new_node;
	else
		position_win_node (new_node, First_Node);
	return( new_node );
}

Free_Rel_Window (window)
struct window	*window;	/* top window to be freed */
{
	struct win_node	*find_win_node();
	struct win_node	*win_node;

	if ( window == 0 || window -> _bot_x == 0 )	/* Already Freed */
		return (-1);

	W_Ok( window, "Free_Rel_Window" );
	win_node = find_win_node (window);
	remove_win_node (win_node); /* isolates hierarchy to free */
	free_win_node (win_node);   /* recurses */
}

free_win_node (win_node)
struct win_node	*win_node;
{
	if (win_node == 0) return;
	free_win_node (win_node -> down);	/* recurse downward */
	free_win_node (win_node -> right);	/* recurse to right */

	/* free node */
	Free_Window (win_node -> window);
	win_node -> window = 0;
	free( win_node );
	win_node = 0;
}

Move_Rel_Window (window, row, col, depth)
struct window	*window;	/* top window in hierarchy to be moved */
int	row;
int	col;
int	depth;
{
	int	d_x;		/* delta x */
	int	d_y;		/* delta y */
	int	d_z;		/* delta z */

	W_Ok( window, "Move_Rel_Window" );

	/* find distance and depth to move relatedwindows */
	d_x = window -> _top_x - row;
	d_y = window -> _top_y - col;
	d_z = window -> _depth - depth;

	Move_Window (window, row, col, depth);
	move_win_node (find_win_node (window) -> down, d_x, d_y, d_z);
}

move_win_node (win_node, d_x, d_y, d_z)
struct win_node	*win_node;
int	d_x;
int	d_y;
int	d_z;
{
	if (win_node == 0) return;

	Move_Window (win_node -> window,
			win_node -> window -> _top_x - d_x,
			win_node -> window -> _top_y - d_y,
			win_node -> window -> _depth - d_z);

	move_win_node (win_node -> down, d_x, d_y, d_z); /* recurse downward */
	move_win_node (win_node -> right, d_x, d_y, d_z); /* recurse to right */
}

Change_Parent (window, parent_window)
struct window	*window;
struct window	*parent_window;
{
	struct win_node	*win_node;
	struct win_node *find_win_node();
	int	d_x; /* delta_x (delta row) */
	int	d_y; /* delta_y (delta column) */
	int	d_z; /* delta_z (delta depth) */
	struct window	*old_parent;

	win_node = find_win_node (window);
	old_parent = win_node -> up -> window;
	remove_win_node (win_node);
	d_x =  window -> _top_x - old_parent -> _top_x;
	d_y =  window -> _top_y - old_parent -> _top_y;
	d_z =  window -> _depth - old_parent -> _depth;
	if (old_parent -> _box_h == 0 && window -> _box_h)
		d_x++;
	if (old_parent -> _box_v == 0 && window -> _box_v)
		d_y++;
	if (old_parent -> _box_h && window -> _box_h == 0)
		d_x--;
	if (old_parent -> _box_v && window -> _box_v == 0)
		d_y--;
	position_win_node (win_node, find_win_node (parent_window));
	Move_Rel_Window (window, 
			parent_window -> _top_x + d_x,
			parent_window -> _top_y + d_y,
			parent_window ->_depth + d_z);
}

remove_win_node (win_node)
struct win_node	*win_node;
{
	if (win_node == 0 || win_node == First_Node)
		return;

	/* repair the hole while removing the node from the hierarchy */
	if (win_node -> up -> down == win_node)
		/* make parent point to new first child */
		win_node -> up -> down = win_node -> right;
	else
		del_win_node (win_node -> up -> down, win_node);


	win_node -> right = 0;
	win_node -> up = 0;
}

del_win_node (test_node, win_node)
struct win_node	*test_node;
struct win_node	*win_node;
{
	/* find node to left of win_node, then delete win_node from list */
	while (test_node -> right != win_node)
		if ((test_node = test_node -> right) == 0)
			return;
	test_node -> right = win_node -> right;
}

position_win_node (new_node, parent_node)
struct win_node	*new_node;
struct win_node	*parent_node;
{
	new_node -> up = parent_node;
	/* make new node the left-most child */
	if (parent_node -> down != 0)
		new_node -> right = parent_node -> down;
	parent_node -> down = new_node;
}
struct window *
Dup_Rel_Window (window, type)
struct window	*window;	/* top window to be freed */
char	*type; /* type of duplication - "all" children or "none" */
{
	struct win_node	*find_win_node();
	struct win_node	*win_node;
	struct win_node	*new_node;
	struct win_node	*dup_node();

	W_Ok( window, "Free_Rel_Window" );
	new_node = find_win_node (window);
	new_node = dup_node (win_node, win_node -> up);
	if (*type == 'a')
		dup_win_node (new_node -> down); /* duplicate children */
	else
		new_node -> down = 0; /* give up children */
	return (new_node -> window);
}

dup_win_node (win_node, parent_node)
struct win_node	*win_node;
struct win_node	*parent_node;
{
	struct win_node *dup_node();

	if (win_node == 0) return;
	win_node = dup_node (win_node, parent_node);

	dup_win_node (win_node -> down, win_node);	/* recurse downward */
	dup_win_node (win_node -> right, parent_node);	/* recurse to right */
}

struct win_node *
dup_node (win_node, parent_node)
struct win_node *win_node;
struct win_node *parent_node;
{
	struct win_node	*new_node;
	struct window	*Dup_Window();

	new_node = ( struct win_node * ) malloc( sizeof( struct win_node ) );
	new_node -> window = Dup_Window (win_node -> window);
	new_node -> down = win_node -> down;
	position_win_node (new_node, parent_node);
	return (new_node);
}

struct window *
Dup_Window (window)
struct window	*window;
{
	struct SWindow	dup_win;

	W_Ok( window, "Dup_Window" );
	dup_win.top_x = window -> _top_x;
	dup_win.top_y = window -> _top_y;
	dup_win.lines = window -> _bot_x - window -> _top_x;
	dup_win.cols = window -> _bot_y - window -> _top_y;
	dup_win.box_h = window -> _box_h;
	dup_win.box_v = window -> _box_v;
	dup_win.depth = window -> _depth - 1;
	dup_win.box_attribute = window -> _box_attribute;
	dup_win.type_scroll = window -> _type_scroll;
	return (New_Window (dup_win));
}
