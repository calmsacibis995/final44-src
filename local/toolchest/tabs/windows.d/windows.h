/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/*
 * Struct for windows
 *
 */

#ifndef TRUE
#define TRUE  1
#define FALSE 0
#endif

/* Total Windows is limited by the size of an int in kmap - can be set to 32 */
#define TOTAL_WINDOWS 16

struct _do_clear
{
	char need;
	int old_x;
	int old_xb;
	int old_y;
	int old_yb;
	int old_depth;
};

struct window				/* Hidden data to be type def later */
{
	int _x_pos;			/* In the window */
	int _y_pos;
	int _top_x;			/* In Cmap */
	int _top_y;
	int _bot_x;			/* In Cmap */
	int _bot_y;
	int _depth;
	int _v_x_top;
	int _v_x_bot;
	int _v_y_top;
	int _v_y_bot;
	unsigned int _key;
	char _scrollable;
	char _type_scroll;
	int  _user_flag;
	char _box_h;
	char _box_v;
	int  _box_attribute;
	struct _do_clear _clear_list;
	CHAR *_map[NSCRLIN];
};

struct SWindow				/* User setup structure */
{
	int top_x;			/* In Cmap */
	int top_y;
	int lines;
	int cols;
	int depth;
	char box_h;
	char box_v;
	char type_scroll;
	int  box_attribute;
};

struct Area
{
	int	top_x;
	int	top_y;
	int	bot_x;
	int	bot_y;
};

extern struct window  *New_Window();
extern struct window  *New_Rel_Window();
extern void Key_Map();
extern void Un_Map();
extern int Free_Window();
extern void Refresh();
extern void Ref_All_Windows();
extern void Wrefresh();
extern void s_werase();
extern void w_xgo();
extern void w_mgo();
extern void w_sgo();
extern void box();
extern void w_erase_char();
extern void wc_erase();
extern void wclrl();
extern void wscroll();
extern void wxprintf();
extern void wsputc();
extern void wxputl();
extern void wstart();
extern void get_x_y();
extern int getnumber();
extern void Move_Window();
extern void wvadjust();
extern void wshift();


/* Windows_vt Specific Declarations */

#define INVISIBLE	200

 /* Extra bit for malloc's */
#ifndef MXTRA
#define MXTRA	8
#endif

/* Globals for windows_vt */

extern int	Area_On;
extern int	Area_Attribute;
extern struct Area	Area[];
extern int     Total_Windows;
extern struct window   _Windows[TOTAL_WINDOWS];
extern int Need_Set_Scroll;
extern unsigned int   *kmap[NSCRLIN];
extern CHAR *cmap2[NSCRLIN];
extern struct window  *C_window;
