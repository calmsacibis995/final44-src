/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */

#define INDEX	field_ptr -> fndfv
#define	BETCOL 3
#define PMENU	( ( struct menu * ) field_ptr->user_pointer )
#define POINTER	"+"
#define CUR_POINTER ">"
#define MAX_SELECTIONS	25
#define NO_MATCH	"No menu item matches response"

struct menu
{
	char	key_type;	  /* field type - CMKEY or CMKEY_LIST */
	char	type;		  /* type of menu - popup or static */
	char	orient;		  /* oientation = vertical or horizontal */
	int     nitems;		  /* number of items (keywords) */
	int     ncols;		  /* no. of columns of items in menu area */
	int     maxlength;	  /* length of longest menu item/keyword */
	struct window  *pmenuwin; /* window that menu is in */
	int	delay;		  /* delay before putting up menu */
	int	max_num_sel;	  /* maximum number of allowed selections*/
	int	*index_sel;	  /* array of indexes if multiple selections */
	int	first_time;	  /* 1 if first time through reader, else 0 */
	int	max_height;	  /* max number of rowsfor static menus */
	char	location;	  /* one of r,l,u,d,t,b or -1 */
};

extern struct window	*Pmenuwin;
extern int	Menu_Delay;
extern int	(*Match_Routine) ();
extern int	crosscor ();
