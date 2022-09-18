/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include <jerq.h>
#include <font.h>
#include "netty.h"

#ifdef dmd_old_version
#undef  ringbell()
#define ringbell()	if (VALKEYTONE) DUART->b_data = TTY_ALARM;\
			else DUART -> b_data = (TTY_CHIRP | TTY_ALARM)
			/* ring bell -- sgs problem prevents A?B:C */
#endif

/*
 *
 * netty.c
 *
 * Terminal program for use in a layer on the DMD, Blit, or BitGraph.
 * netty.c has a sufficient set of cursor controls to be usable with
 * BTL and CMU Emacs's, Vi, More, Rogue, and other programs that use
 * the curses library and/or termcap.  From vitty.c on the Blit
 * distribution tape.
 *
 * Extensively modified by Tim Mann and D. L. Bayer.
 *
 * Selectable regions by Warren Montgomery
 *
 * All of the rest - C. Douglas Blewett
 *
 *
 *	Control sequences
 *
 *		^G	BELL
 *		^L	CLEAR
 *
 *
 *	ESCAPE PREFIXED SEQUENCES
 *
 *	The letter "~" in the following sequences is a letter in the range
 *	"@ABCD...Z" for specifying the numbers "0 1 2 3 4 ... 26".  For
 *	setting modes the letters "@" and "A" (0 and 1) should be used.
 *
 *	The letters "x" and "y" are used to specify column and row positions
 *	encoded as one letter.  "l" and "w" are used to specify lenght and
 *	width encoded as one letter.  The encoding is performed by adding 32
 *	to the desired number.
 *
 *		R~	Inverse Video on and off
 *		U~	Underline on and off
 *		^R	Toggle Invert
 *		^P	Toggle MIT scrolling
 *		^W	Toggle MORE processing
 *		C~	Graphics Character set on and off
 *		Yxy	Cursor movement
 *		I~	Insert mode on and off
 *		d	Delete a character
 *		Z	Clear to end of line
 *		A	Up one line
 *		{~	Mouse mode on and off
 *		[~	vi mode on and off
 *		X	ixon mode on and off
 *		#~	Select menu
 *		M~!m!	Download menu item
 *		m~!v!	Download menu value
 *		K~!k!	Download Olson key
 *		F~!f!	Download arrow and function keys
 *		T...	Download a Blit texture (Concept100 encoding)
 *		t~...	Download a Blit icon (Concept100 encoding)
 *		.xy!t!!r!
 *			Set icon number y at location x with title t
 *			and return value r
 *		b!m!	Send a message to the banner line
 *		Bxyxy	Draw a border line from point to point
 *		vxylw	Define a view - Concept100 style window
 *		wxylw	Define a Blit sub-layer
 *		^D~	Delete a Blit sub-layer
 *		 ~	Select a Blit sub-layer
 *		Dx	Delete x lines
 *		Sx	Scroll x lines
 *		Ox	Open x lines
 *		P~	Mit Scrolling on and off
 *		W~	More processing on and off
 *		^	Dispose of banner line and icon area - full screen
 *
 *	The sequences above that are used to send arbitrary length strings to
 *	the Blit are followed by notation that looks something like the
 *	following "XX!m!" - the sequence "!m!" should be interpreted as
 *	a delimiting character ("!"), the message string ("m"), and the
 *	delimiting character again ("!").
 *
 *	The return values from menu selection or from function keys will be
 *	transmitted as if they were entered by the user from the keyboard.
 *	Sequences that are prefixed by "##" will be executed locally.
 *
 */

main (argc, argv)
int     argc;
char  **argv;
{
    register struct window *wp;
    register int    device;
    register char   buf[2];
    register int    key;
    char   *pfstr;
    char   *mit_ptr;
    char   *more_ptr;
    char   *invert_ptr;
    short   nextwindow = -1;
    unsigned int    len;
    struct Proc *p = P;
#ifdef DO_ICONS
    int     icons;
    Point xp;
    struct icon_object *ti_object;
#endif

/*
 *	Initialize the Blit and the Menu stuff
 *
 */
    jinit ();
    request (RCV | KBD | SEND | MOUSE);

    gwp = &w[0];
    wp = gwp;
    for (device = 1; device < NWINDOW; device++)
	w[device].w_layer = 0;

    menu.item = menuchars[0];
    mit_ptr = menuchars[0][MIT_ITEM];
    more_ptr = menuchars[0][MORE_ITEM];
    invert_ptr = menuchars[0][INVERT_ITEM];
    for (key = 0; key < 13; key++)	/* Just the first 13 items */
	menuchars[VI_MENU][key] = menuchars[EMACS_MENU][key];
    if (highest_mem < lowest_mem)	/* all this because we have no edata */
    {
	pfstr = lowest_mem;
	lowest_mem = highest_mem;
	highest_mem = pfstr;
    }

#ifdef OLSON_BLIT
    for (key = 0; key < 128; key++)
	kstr[key] = 0;
#endif OLSON_BLIT

/*
 *	Initialize the assorted flags/modes
 *
 */
    freeze = FALSE;
    ixon_mode = FALSE;
    marked_mode = FALSE;
    MIT_mode = FALSE;
    graphics_chars = FALSE;
    more_mode = FALSE;
    mouse_mode = FALSE;
    vi_mode = FALSE;
    under_mode = FALSE;
    current_menu = 0;
    banner_type = 0;

/*
 *	Initialize the read ahead buffer
 *
 */
    for (device = 0; device < KBD_SIZE; device++)
	kbd_buf[device] = '\0';
    kbd_ptr = kbd_buf;
    kbd_count = 0;

/*
 *	Establish the Banner type
 *
 */
    for (key = 1; key < argc; key++)
    {
	pfstr = argv[key];
	while (*pfstr)
	{
	    if (*pfstr == 'T')
		banner_type |= TOP_BANNER | BANNER;
	    else
		if (*pfstr == 't')
		    banner_type |= TEXTURE_BANNER | BANNER;
		else
#ifdef DO_ICONS
		    if (*pfstr == 'i')
		    {
			banner_type |= ICONS;
			icons = TRUE;
		    }
		    else
#endif
			banner_type |= BANNER;
	/* Assume any arg means banner */

	    pfstr++;
	}
    }
    Re_Size (TRUE);
    P -> state &= ~(RESHAPED | MOVED);
    Curse ();

/*
 *	At Last - The Read Loop
 *
 */
    buf[1] = 0;

    for (;;)
    {
	Check_Changes ();
	if (*kbd_ptr == 0)
	{
	    if (freeze)
	    {
		device = wait (MOUSE | KBD);
	    }
	    else
	    {
		device = wait (RCV | KBD | MOUSE);
	    }
	    if ((device == MOUSE) &&
		    (bttn123 () == 0))
	    {
		Flicker (TRUE);
#ifdef DO_ICONS
		if (icons == FALSE)
			continue;
		else
		{
			if (ptinrect (mouse.xy, dir) == FALSE)
			{
			    if (cur_icon_rect.corner.y)
			    {
				rectf (&display, cur_icon_rect, F_XOR);
				cur_icon_rect.corner.y = 0;
			    }
			    continue;
			}
		}
#endif
	    }
	}
	else
	    device = INTERN_BUFFER;
/*
 *	Characters from the host
 *
 */
	if (device & (RCV | INTERN_BUFFER))
	{
	    Curse ();

	    if (device == INTERN_BUFFER)
		buf[0] = _Get_Old ();
	    else
		buf[0] = rcvchar ();

    Nocurse: 
	    *buf &= 0177;
	    switch (buf[0])
	    {
		case '\0': 
		    break;

		case CTRL (G): 		/* bell */
		    ringbell ();
		    break;

		case '\b': 		/* backspace */
		    if (X > 0)
			--X;
		    break;

		case '\t': 		/* tab modulo 8 */
		    X = (X | 7) + 1;
		    break;

		case '\n': 		/* linefeed */
		    New_Line ();
		    break;

		case CTRL (L): 		/* clear screen */
		    xstipple (L, wp -> w_Drect);
		    X = 0;
		    Y = 0;
		    if ((wp == &w[0]) &&
			    (invert_mode == FALSE) &&
			    (under_mode == FALSE) &&
			    (graphics_chars == FALSE))
			marked_mode = FALSE;
		    break;

		case '\r': 		/* carriage return */
		    X = 0;
		    break;

#ifdef GRAPHICS_BORDERS		
#ifndef VT_TERMINFO
		case CTRL (X): 		/* Graphics Outline Characters */
		    Line_Border (B_UPLEFT, 0, X, Y);
		    X++;
		    marked_mode = TRUE;
		    goto Check_Length;

		case CTRL (Y): 
		    Line_Border (B_UPRIGHT, 0, X, Y);
		    X++;
		    marked_mode = TRUE;
		    goto Check_Length;

		case CTRL (Z): 
		    Line_Border (B_LORIGHT, 0, X, Y);
		    X++;
		    marked_mode = TRUE;
		    goto Check_Length;

		case CTRL (\\): 
		    Line_Border (B_LOLEFT, 0, X, Y);
		    X++;
		    marked_mode = TRUE;
		    goto Check_Length;

		case CTRL (]): 		/* Horizontal Bar */
		    Line_Border (X, Y, X + 1, Y);
		    X++;
		    marked_mode = TRUE;
		    goto Check_Length;

		case CTRL (^): 		/* Vertical Bar */
		    Line_Border (X, Y, X, Y + 1);
		    X++;
		    marked_mode = TRUE;
		    goto Check_Length;

#endif NOT VT_TERMINFO
#endif GRAPHICS_BORDERS		

		case ESC: 
		    switch (Get_Char ())
		    {
			case CTRL (P): 	/* toggle MIT */
			    Toggle_State (&MIT_mode, !MIT_mode, mit_ptr);
			    break;

			case CTRL (R): 	/* toggle invert */
			    Toggle_State (&invert_mode, !invert_mode, invert_ptr);
			    rectf (&display, P -> rect, F_XOR);
			    marked_mode += invert_mode;
			    break;

			case CTRL (W): 	/* toggle more processing */
			    Toggle_State (&more_mode, !more_mode, more_ptr);
			    break;

			case '#': 	/* Select Menu # */
			    key = Get_Flag ();
			    if ((key >= 0) && (key <= MENUS))
			    {
				current_menu = key;
				menu.item = menuchars[key];
				menu.lasty = 0;
			    }
			    break;

#ifdef DO_ICONS
			case '.': 
			    key = Get_Flag ();/* Position # */
			    if (key >= TOTAL_OBJECTS)
			    {
				Get_Flag ();
				Get_String ();
				Get_String ();
				break;
			    }
			/* Icon Id */
			    if ((ti_object = Get_N_Icon (Get_Flag (), FALSE)) == 0)
			    {
				Get_String ();
				Get_String ();
			    }
			    else
			    {
				Change_String (&(list[key].title), 0);
				if (strlen (list[key].title) > ICON_CHARS)
				    list[key].title[ICON_CHARS] = '\0';
				Change_String (&(list[key].ret_value), 0);
			    }
			    list[key].datum = (char *) ti_object;
			    list[key].type = TYPE_ICON;
			    if ((banner_type & ICONS) == 0)
			    {
				banner_type |= ICONS;
				icons = TRUE;
				Drect = P -> rect;
				xstipple (&display, Drect);
				Re_Size (TRUE);
				P -> state &= ~(RESHAPED | MOVED);
				break;
			    }

			    xp.x = dir.origin.x +
				(((ICON_CHARS * CW + 2) - ICON_SIZE) / 2) +
				(ICON_CHARS * CW + 2) * key;
			    xp.y = dir.origin.y;

			    if (cur_icon_rect.corner.y)
			    {
				rectf (&display, cur_icon_rect, F_XOR);
				cur_icon_rect.corner.y = 0;
			    }

			    rxstipple (&display, Rpt (
					Pt (xp.x + 2, xp.y + 2),
					Pt (xp.x + ICON_CHARS * CW + 1,
					    xp.y + ICON_SIZE + NS + 9)));

			    Draw_One_Icon (key, xp);
			    break;
#endif

			case '?':
			/* who are we */
			    sendnchars (6, "netty\r");
			    break;

			case 'A': 
			/* Cursor up. */
			    if (Y > 0)
				--Y;
			    break;

#ifdef GRAPHICS_BORDERS		
			case 'B': 
			/* Character Border */
			    Get_Border ();
			    break;

#ifdef VT_TERMINFO
			case 'C': 
			    graphics_chars = Get_Flag ();
			    marked_mode += graphics_chars;
			    break;
#endif VT_TERMINFO
#endif GRAPHICS_BORDERS		

			case 'D': 
			/* Delete N lines (DLB) */
			    Forward_Scroll (Y, Get_Concept ());
			    break;

			case 'F': 
			/* download function key */
			    key = Get_Flag ();
			    if (key >= 0 && key < N_KEYS)
			    {
#ifdef mc68000
			    /* Beware of the hole between 3 and 4 */
				if (key > 3)
				    key++;
#endif
				Change_String (pfkey, key);
			    }
			    break;

			case 'I': 
			/* insert character mode (DLB) */
			    wp -> w_insert = Get_Flag ();
			    break;

#ifdef OLSON_BLIT
			case 'K': 
			    key = getchar ();
			    Change_String (kstr, key);
			    break;
#endif OLSON_BLIT

			case 'M': 
			/* download menu item */
			    key = Get_Flag ();
			    if ((key < 0) || (key > MENU_ITEMS))
				break;
			    Change_String (menuchars[current_menu], key);
			    break;

			case 'O': 
			/* Open N lines (DLB) */
			    Open_Lines (Get_Concept ());
			    break;

			case 'P': 
			/* MIT Scrolling */
			    Toggle_State (&MIT_mode, Get_Flag (), mit_ptr);
			    break;

			case 'R': 	/* inverse video mode on */
			    Toggle_State (&invert_mode, Get_Flag (), invert_ptr);
			    marked_mode += invert_mode;
			    break;

			case 'S': 
			/* Scroll N lines (DLB) */
			    Forward_Scroll (0, Get_Concept ());
			    break;

			case 'T': 
			/* Read a Texture */
			    cursinhibit ();
			    Read_Texture (&Text_Cursor);
			    cursallow ();
			    break;

			case 'U': 	/* underline on */
			    under_mode = Get_Flag ();
			    marked_mode += under_mode;
			    break;

			case 'W': 
			    Toggle_State (&more_mode, Get_Flag (), more_ptr);
			    break;

			case 'X': 
			/* enter ixon mode */
			    ixon_mode = Get_Flag ();
			    break;

			case 'Y': 
			/* position cursor */
			    X = Get_Char () - ' ';
			    Y = Get_Char () - ' ';

			    if (X < 0)
				X = 0;
			    if (X > MAXCOLUMN)
				X = MAXCOLUMN;
			    if (Y < 0)
				Y = 0;
			    if (Y > MAXLINE)
				Y = MAXLINE;
			    break;

			case 'Z': 
			/* clear to EOL */
			    Clear_To_Eol ();
			    break;

			case '[': 
			/* E[c		send terminal id string */
			    if ((key = Get_Char ()) == 'c')
				sendnchars(9, "\033[?8;7;3c");
			    else
			/* enter VI mode for mouse pointing */
				vi_mode = key & 037;
			    break;

			case '^': 	/* Delete Icon and banner */
			    banner_type = 0;
#ifdef DO_ICONS
			    icons = FALSE;
#endif
			    Drect = P -> rect;
			    xstipple (&display, Drect);
			    Re_Size (TRUE);
			    P -> state &= ~(RESHAPED | MOVED);
			    break;

			case 'b': 
			/* Banner line */
			    len = Get_String ();
			    if ((banner_type & BANNER) == 0)
			    {
				banner_type |= TOP_BANNER | BANNER;
				Drect = P -> rect;
				xstipple (&display, Drect);
				Re_Size (TRUE);
				P -> state &= ~(RESHAPED | MOVED);
			    }
			    Draw_Banner ();
			    if (len > w[0].w_xmax + 1)
				len = w[0].w_xmax + 1;
			    str_buffer[len] = 0;
			    if (len == (w[0].w_xmax + 1))
			    {
				len = 2;
			    }
			    else
			    {
				len = (w[0].w_xmax - len) / 2;
				len = len * CW + 2;
			    }
			    banner.origin.x += len;
			    banner.origin.y += 2;
			    string (&defont, str_buffer, &display, banner.origin, F_XOR);
			    banner.origin.x -= len;
			    banner.origin.y -= 2;
			    break;

			case 'd': 
			/* delete character */
			    if (X < MAXCOLUMN)
			    {
				bitblt (L, Rpt (Etty_Pt (X + 1, Y), Etty_Pt (MAXCOLUMN + 1, Y + 1)), L, Etty_Pt (X, Y), F_STORE);
				string (&defont, " ", L, Etty_Pt (MAXCOLUMN, Y), F_STORE);
			    }
			    break;

			case 'm': 
			/* download menu values */
			    key = Get_Flag ();
			    if ((key < 0) || (key > MENU_ITEMS))
				break;
			    Change_String (menuvalues[current_menu], key);
			    break;

#ifdef DO_ICONS
			case 't': 
			/* Read an Icon */
			    if ((ti_object = Get_N_Icon (Get_Flag (), TRUE)) == 0)
				break;
			    if (ti_object -> map)
				bfree (ti_object -> map);
			    ti_object -> map = Load_Icon ();
			    break;
#endif

#ifdef NEW_WINDOWS
			case 'v': 
			/* Concept window not in a layer This is almost
			   identical to the Concept 100 version of a window.
			   (DLB) This will always work - given a large enugh
			   window is created - does not eat screen space
			   Patched up to be exactly Like Concept - CDB */
			    New_Window (nextwindow, 1);
			    nextwindow = -1;
			    wp = gwp;
			    break;

#endif NEW_WINDOWS

#ifdef NEW_LAYERS
			case 'w': 
			/* Concept 100 style create window. Returns 2
			   characters: window number followed by newline.  This
			   won't always work - hence the return (DLB) */
			    sendchar (New_Window (nextwindow, 0) + ' ');
			    sendchar ('\n');
			    nextwindow = -1;
			    wp = gwp;
			    break;

			case CTRL (D): 
			/* Concept 100 style delete window (DLB) */
			    Del_Window (nextwindow);
			    nextwindow = -1;
			    wp = gwp;
			    break;

			case ' ': 
			/* goto Concept style window (DLB) */
			    if ((key = Get_Char ()) == 'z')
			    {
				if ((key = Get_Concept ()) < 0 ||
					key > NWINDOW)
				    break;
				nextwindow = key;
				if (w[key].w_layer == 0)
				    break;
				wp = &w[key];
				upfront (wp -> w_layer);
				Layer_Border ();
			    }
			    wp = gwp;
			    break;
#endif NEW_LAYERS
			case '{': 	/* } */
			/* enter mouse mode */
			    mouse_mode = Get_Flag ();
			    request (RCV | KBD | SEND);
			    request (RCV | KBD | SEND | MOUSE);
			    if (mouse_mode)
				cursswitch (&Text_Cursor);
			    break;
		    }
		    break;

		default: 
		/* ordinary char */
		/* chars are drawn at baseline; hence y+1 */

		    if (wp -> w_insert != 0 && X < MAXCOLUMN)
		    {
			bitblt (L, Rpt (Etty_Pt (X, Y),
				    Etty_Pt (MAXCOLUMN, Y + 1)),
				L, Etty_Pt (X + 1, Y), F_STORE);
		    }

#ifdef GRAPHICS_BORDERS
#ifdef VT_TERMINFO
		    if (graphics_chars)
		    {
			xstipple (L, Rpt (Etty_Pt (X, Y), Etty_Pt (X + 1, Y + 1)));
			switch (buf[0])
			{
			    case 'j': 
				Line_Border (B_LORIGHT, 0, X, Y);
				break;

			    case 'k': 
				Line_Border (B_UPRIGHT, 0, X, Y);
				break;

			    case 'l': 
				Line_Border (B_UPLEFT, 0, X, Y);
				break;

			    case 'm': 
				Line_Border (B_LOLEFT, 0, X, Y);
				break;

			    case 'q': 	/* Horizontal Bar */
				Line_Border (X, Y, X + 1, Y);
				break;

			    case 'x': 	/* Vertical Bar */
				Line_Border (X, Y, X, Y + 1);
				break;
			}

			X++;
			goto Check_Length;
		    }
#endif VT_TERMINFO
#endif GRAPHICS_BORDERS		

		    if ((marked_mode == 0) && (own () & MOUSE))
		    {
			string (&defont, buf, wp -> w_layer, Etty_Pt (X, Y), F_STORE);
		    }
		    else
		    {
			xstipple (L, Rpt (Etty_Pt (X, Y), Etty_Pt (X + 1, Y + 1)));
			string (&defont, buf, wp -> w_layer, Etty_Pt (X, Y), F_XOR);
		    }

		    if (under_mode)
			Underline_Char ();

		    X++;
		    break;
	    }
    Check_Length: 
	    if (X > MAXCOLUMN)
	    {
		X = 0;
		New_Line ();
	    }
	    if (device == INTERN_BUFFER)
	    {
		if (*kbd_ptr)
		{
		    buf[0] = _Get_Old ();
		    goto Nocurse;
		}
		Curse ();
		continue;
	    }
	    else
		if (own () & RCV)
		{
		    buf[0] = rcvchar ();
		    goto Nocurse;
		}
	    Curse ();
	}

/*
 *	Characters from the Keyboard
 *
 */
	if (device & KBD)
	{
	    Read_Kbd ();
	    continue;
	}

/*
 *	Mouse Action
 *
 */
	if ((device & MOUSE) &&
		(bttn123 ()
#ifdef DO_ICONS
		           || (icons && ptinrect (mouse.xy, dir))
#endif
		           					 ))
	    Read_Mouse ();
    }
}

Check_Changes ()
{
    if (P -> state & RESHAPED)
    {
	m_own_bug = TRUE;	/* xstipple() looks at own() which fails */
	Re_Size (TRUE);
	Curse ();
	m_own_bug = FALSE;
    }
    else
    if (P -> state & MOVED)
    {
	m_own_bug = TRUE;
	Re_Size (FALSE);
	m_own_bug = FALSE;
    }
    P -> state &= ~(RESHAPED | MOVED);
}

void
Change_String (str, key)
register char  *str[];
register int    key;
{
    register unsigned int   len;

    if ((str[key]) && (Allocd (str[key])))
	free (str[key]);
    str[key] = 0;
    if ((len = Get_String ()))
    {
	if ((str[key] = alloc (len + 1)) == 0)
	    return;
	strcpy (str[key], str_buffer);
    }
}

int
Allocd (ptr)
register char  *ptr;
{
    if ((ptr > lowest_mem) && (ptr < highest_mem))
	return (FALSE);
    return (TRUE);
}

void
Toggle_State (mode, value, str)
register int   *mode;
register int    value;
register char  *str;
{
    *mode = value;

    while (*str)
    {
	if (value)
	{
	    if (*str > '\`')
		*str &= 0137;
	}
	else
	{
	    if (*str > '@')
		*str |= 040;
	}
	str++;
    }
}

int
Get_Flag ()
{
    return (Get_Concept () & 037);
}

int
Int_To_Str (ptr, x)		/* numbers in the range 1 to 999 */
register char  *ptr;
register int    x;
{
    register int    inc;
    register int    len;

    if (x < 1)				/* Negative or Zero in the dumper */
    {
	*ptr++ = '0';
	return (1);
    }
    inc = 1;
    if (x > 9)
	inc++;
    if (x > 99)
	inc++;

    len = inc;
    while (inc)
    {
	inc--;
	ptr[inc] = '0' + x - ((x / 10) * 10);
	x /= 10;
    }
    return (len);
}

void
Read_Texture (tex)
register Texture16 * tex;
{
    register int    i;
    register int    sh1;

    for (i = 0; i < 16; i++)
    {
	sh1 = Get_Concept ();
	tex -> bits[i] = (sh1 << 8) | Get_Concept ();

/* This doesn't work - although it should
	tex -> bits[i] = ((Get_Concept () << 8) + Get_Concept ());
*/
    }
}

void
Clear_To_Eol ()
{
    register struct window *wp = gwp;

    xstipple (L, Rpt (Etty_Pt (X, Y), Etty_Pt (MAXCOLUMN + 1, Y + 1)));
}

/*	History
void
Invert_Char ()
{
    register struct window *wp = gwp;

    rectf (wp -> w_layer, Rpt (Etty_Pt (X, Y), Etty_Pt (X + 1, Y + 1)), F_XOR);
}
*/

void
Underline_Char ()
{
    register struct window *wp = gwp;
    register    Point s;
    register    Point e;

    s = Etty_Pt (X, Y);
    e.x = s.x + CW;
    e.y = s.y + NS - 2;
    s.y = e.y - 1;
    rectf (wp -> w_layer, Rpt (s, e), F_XOR);
}

int
Get_String ()
{
    register int    size;
    register char   end;
    register char  *ptr;

    ptr = str_buffer;

    end = Get_Char ();
    size = 0;
    while (end != (*ptr = Get_Char ()))
    {
	ptr++;
	size++;
	if (size >= (STRINGLEN - 1))
	    break;
    }
    *ptr = '\0';
    return (size);
}

char
_Get_Old ()
{
    register char   c;

    c = *kbd_ptr;
    *kbd_ptr = '\0';
    kbd_count++;
    kbd_count &= KBD_SIZE - 1;
    kbd_ptr = &kbd_buf[kbd_count];
    return (c);
}

void
_C_Unget (c)
register char   c;
{
    kbd_count--;
    kbd_count &= KBD_SIZE - 1;
    kbd_ptr = &kbd_buf[kbd_count];
    *kbd_ptr = c;
}

void
_Str_Unget (str_ptr)
register char  *str_ptr;
{
    register char  *ptr;

    if (*str_ptr == '\0')
	return;

    ptr = &str_ptr[strlen (str_ptr) - 1];

    while (ptr >= str_ptr)
    {
	_C_Unget (*ptr--);
    }
}

char
Get_Char ()
{
    register int    device;

    if (*kbd_ptr)
	return _Get_Old ();

    while (((device = wait (RCV | KBD | MOUSE)) & RCV) == 0)
    {
	if (device & KBD)
	{
	    Read_Kbd ();
	}
	else
	    if (device & MOUSE)
	    {
		Read_Mouse ();
	    }
	if (*kbd_ptr)
	    return _Get_Old ();
	Flicker (FALSE);
    }
    return rcvchar ();
}

void
Flicker (type)
register int type;
{
    static int  _flicker;

    if (_flicker >= 16)
    {
	Curse ();
	sleep (6);
	Curse ();
	_flicker = 0;
    }
    else
    {
	_flicker++;
	sleep (2);
    }
}

Etty_Send_Char (str)
register char  *str;
{
    if ((str[0] == '#') && (str[1] == '#'))
    {
	_Str_Unget (&str[2]);
    }
    else
    {
	sendnchars (strlen (str), str);
    }
}

void
Read_Mouse ()
{
    register struct window *wp = gwp;
    register int    key;
    register char   coords[8];
    register char   mouse_buffer[16];
    register struct object *list_ptr;

    coords[0] = CTRL (X);
    coords[1] = CTRL (_);

#ifdef DO_ICONS
    if ((banner_type & ICONS) &&
	    (ptinrect (mouse.xy, dir)) &&
	    (bttn23 () == FALSE))
    {
	for (key = 0; key < TOTAL_OBJECTS; key++)
	{
	    list_ptr = &list[key];
	    if ((list_ptr -> type == TYPE_ICON) &&
		    (list_ptr -> datum) &&
		    (ptinrect (mouse.xy, list_ptr -> trect)))
	    {
		if (eqrect (cur_icon_rect, list_ptr -> trect) == FALSE)
		{
		    if (cur_icon_rect.corner.y)
			rectf (&display, cur_icon_rect, F_XOR);
		    cur_icon_rect = list_ptr -> trect;
		    rectf (&display, cur_icon_rect, F_XOR);
		}
		Flicker (FALSE);
		while (bttn1 () && ptinrect (mouse.xy, cur_icon_rect))
		{
		    Flicker (FALSE);
		    if (bttn1 () == 0)
		    {			/* Got One */
			rectf (&display, cur_icon_rect, F_XOR);
			Flicker (FALSE);
			Etty_Send_Char (list_ptr -> ret_value);
			rectf (&display, cur_icon_rect, F_XOR);
			return;
		    }
		}
		return;
	    }
	}
	if (cur_icon_rect.corner.y)
	{
	    rectf (&display, cur_icon_rect, F_XOR);
	    cur_icon_rect.corner.y = 0;
	}
	return;
    }
#endif DO_ICONS

    if ((mouse_mode == FALSE) && bttn1 ())
	return;

    if (bttn3 ())
    {
	while (bttn3 ())
	{
	    request (RCV | KBD | SEND);
	    sleep (15);
	    Flicker (FALSE);
	    request (RCV | KBD | SEND | MOUSE);
	    if (mouse_mode)
		cursswitch (&Text_Cursor);
	}
	return;
    }

 /* send escape sequence and */
 /* menu selection by number */
    if ((coords[2] = "-32-1---"[mouse.buttons & 7]) == '-')
	return;

/*
 *	Warren Montgomery area marking stuff - very neat
 *
 */
    if ((mouse_mode == 2) && bttn1 ())
    {
    /* jim style selection */

	int     start;
	int     end;
	int     current;

	current = chad ();
	end = current;
	start = end;
	while (bttn1 ())
	{
	    end = chad ();
	    if (end != current)
	    {
		blank (end, current);
		current = end;
	    }
	}

	if (ptinrect (mouse.xy, Drect) == FALSE)
	{
	    blank (start, current);
	    return;
	}
	if (start != current)
	{

	    coords[3] = GCH (start) + 32;
	    coords[4] = GLINE (start) + 32;
	    sendnchars (5, coords);
	    blank (start, current);
	    coords[3] = GCH (end) + 32;
	    coords[4] = GLINE (end) + 32;
	    coords[1] = CTRL (]);
	    sendnchars (5, coords);
	    return;
	}
    /* Fall through to handle single hits */
    }

    if ((menuchars[current_menu][0]) &&
	    bttn2 ())
    {
	key = menuhit (&menu, 2);
	if (key >= 0)
	{
	/* send menu selection */
	    if (menuvalues[current_menu][key])
	    {
		Etty_Send_Char (menuvalues[current_menu][key]);
	    }
	    else
	    {
		if (mouse_mode)
		{
		    coords[3] = coords[4] = key + 32;
		    sendnchars (5, coords);
		}
	    }
	}
	return;
    }

    if (mouse_mode == FALSE)
	return;

 /* buttons 1 and 2 for pointing */
    while (bttn12 ())
	Flicker (FALSE);

    coords[3] = (mouse.xy.x - (Drect.origin.x + XMARGIN)) / CW;
    coords[4] = (mouse.xy.y - (Drect.origin.y + YMARGIN)) / NS;

 /* don't send if menu miss or too many buttons */
    if (coords[3] == (-1))
	return;

    if (vi_mode)
    {
    /* 
     * Construct a vi command to do the positioning
     * Does not handle wrapped lines.  This clever
     * technique courtesy of Jerry Schwartz
     */
	if (coords[4] != Y)
	{
	    if (coords[4] > Y)
	    {
		key = Int_To_Str (mouse_buffer, coords[4] - Y);
		mouse_buffer[key++] = 'j';
	    }
	    else
	    {
		key = Int_To_Str (mouse_buffer, Y - coords[4]);
		mouse_buffer[key++] = 'k';
	    }
	    sendnchars (key, mouse_buffer);
	}
	key = Int_To_Str (mouse_buffer, coords[3] + 1);
	mouse_buffer[key++] = '|';
	sendnchars (key, mouse_buffer);
    }
    else
    {
	coords[3] += 32;
	coords[4] += 32;
	sendnchars (5, coords);
    }
}

/*
 *	blank and chad - Warren Montgomery routines for marking regions
 *
 */
void
blank (from, to)
int     from;
int     to;
{
    register int    x;
    register int    y;
    register    Rectangle brect;
    register Rectangle *ptr_drect = &Drect;

    if (from > to)
    {
	x = from;
	from = to;
	to = x;
    }

    y = GLINE (to);
    while ((x = GLINE (from)) != y)
    {
	brect.origin.x = ptr_drect -> origin.x + XMARGIN + GCH (from) * CW;
	brect.corner.x = ptr_drect -> corner.x - XMARGIN;
	brect.origin.y = ptr_drect -> origin.y + YMARGIN + x * NS;
	brect.corner.y = brect.origin.y + NS;
	rectf (&display, brect, F_XOR);
	from = MKADD (x + 1, 0);
    }

    brect.origin.x = ptr_drect -> origin.x + XMARGIN + GCH (from) * CW;
    brect.origin.y = ptr_drect -> origin.y + YMARGIN + x * NS;
    brect.corner.x = ptr_drect -> origin.x + XMARGIN + GCH (to) * CW;
    brect.corner.y = brect.origin.y + NS;
    rectf (&display, brect, F_XOR);
}

int
chad ()
{
    register int    x;
    register int    y;
    register Rectangle *ptr_drect = &Drect;

    x = (mouse.xy.x - (ptr_drect -> origin.x + XMARGIN)) / CW;
    y = (mouse.xy.y - (ptr_drect -> origin.y + YMARGIN)) / NS;

    if (x < 0)
	x = 0;
    if (y < 0)
	y = 0;
    if (x > (ptr_drect -> corner.x - ptr_drect -> origin.x) / CW)
	x = (ptr_drect -> corner.x - ptr_drect -> origin.x) / CW;
    if (y > (ptr_drect -> corner.y - ptr_drect -> origin.y) / NS)
	y = (ptr_drect -> corner.y - ptr_drect -> origin.y) / NS;

    return (MKADD (y, x));
}

void
Read_Kbd ()
{
    register int    key;
    register char  *pfstr;

    key = kbdchar ();

    switch (key)
    {
	case CTRL (S): 
	    if (ixon_mode)
		sendchar (key);
	    else
		freeze = !(freeze);
	    break;

	case CTRL (Q): 
	    if (ixon_mode)
		sendchar (key);
	    else
		freeze = FALSE;
	    break;

#ifdef mc68000
	case NOSCRL: 			/* No Scroll */
	    freeze = !freeze;
	    break;

#else	/* DMD */
	case BREAK_KEY:
	case DISCON_KEY:
	    freeze = FALSE;
	    sendchar (-1);
	    return;

	case ESC: 
	    freeze = FALSE;
	    key = read_one ();
	    if (key == '[')
	    {
		key = read_one ();
		switch (key)
		{
		    case 'A': 		/* UP Arrow */
			key = UPARROW;
			break;
		    case 'B': 		/* DOWN Arrow */
			key = DOWNARROW;
			break;
		    case 'C': 		/* RIGHT Arrow */
			key = RIGHTARROW;
			break;
		    case 'D': 		/* LEFT Arrow */
			key = LEFTARROW;
			break;

		    case 'H': 		/* HOME */
			key = HOMEARROW;
			break;
		    case '7': 		/* BOTTOM */
			read_one ();	/* 0 */
			read_one ();	/* ; */
			read_one ();	/* 1 */
			read_one ();	/* H */
			key = BOTTOMARROW;
			break;
		    case '2': 		/* CLEAR */
			read_one ();	/* J */
			key = CLEARARROW;
			break;
		    default: 
			sendchar (ESC);
			sendchar ('[');
			if (key != -1)
			    sendchar (key);
			return;
		}
	    }
	    else
	    {
		sendchar (ESC);
		if (key != -1)
		    sendchar (key);
		return;
	    }
#endif
	case UPARROW: 			/* Arrow keys */
	case DOWNARROW: 
	case LEFTARROW: 
	case RIGHTARROW: 
	case PF1: 			/* PF keys */
	case PF2: 
	case PF3: 
	case PF4: 
#ifdef dmd
	case PF5: 
	case PF6: 
	case PF7: 
	case PF8: 
	case HOMEARROW: 
	case BOTTOMARROW: 
	case CLEARARROW: 
#endif
	    freeze = FALSE;
	    pfstr = pfkey[key - PFK_START];
	    if ((pfstr != 0) && (*pfstr != 0))
	    {
		Etty_Send_Char (pfstr);
	    }
	    return;
	default: 
	    freeze = FALSE;
#ifdef OLSON_BLIT:
	    if (key & 0200)
	    {
		pfstr = kstr[key - 0200];
		if (pfstr)
		{
		    sendnchars (strlen (pfstr), pfstr);
		    break;
		}
	    }
#else

#ifdef mc68000
	    sendchar (Translate_Char (key));
#else	/* DMD */
	    sendchar (key);
#endif mc68000

#endif
	    break;
    }
}

int
read_one ()
{
    if      ((wait (MOUSE | KBD) & KBD) == 0)
    {
	        return (-1);
    }
    return (kbdchar ());
}

void
New_Line ()
{
    register struct window *wp = gwp;
    static int  line_count;

    Y++;

    if (MIT_mode)
    {
	if ((more_mode) && (Y == MAXLINE))
	    Get_More ();

	if (Y > MAXLINE)
	    Y = 0;

	Clear_To_Eol ();
    }
    else
    {
	if (Y > MAXLINE)
	{
	    Forward_Scroll (0, 1);
	    Y = MAXLINE;
	}

	if (more_mode)
	{
	    line_count++;

	    if ((line_count >= MAXLINE) && (Y == MAXLINE))
	    {
		Get_More ();
		Clear_To_Eol ();
		line_count = 0;
	    }
	}
    }
}

void
Get_More ()
{
    register struct window *wp = gwp;
    register int    device;

    Clear_To_Eol ();
    string (&defont, "- More -", wp -> w_layer, Etty_Pt (X, Y), F_XOR);
    rectf (wp -> w_layer, Rpt (Etty_Pt (X, Y), Etty_Pt (X + 8, Y + 1)), F_XOR);
/*
 *	Beep if you want it
 *
	ringbell();
 */
    while (1)
    {
	device = wait (MOUSE | KBD);
	if (device & KBD)
	{
	    freeze = TRUE;		/* if they use ^S to move on */
	    return;
	}
	if (device & MOUSE)
	{
	    if (bttn123 ())
	    {
		Read_Mouse ();
		return;
	    }
	    Read_Mouse ();
	}
    }
}

void
Curse ()
{
    register struct window *wp = gwp;

    string (&defont, CURSOR, wp -> w_layer, Etty_Pt (X, Y), F_XOR);
}

Point
Etty_Pt (x, y)
register    x;
register    y;
{
    register struct window *wp = gwp;

    return add (wp -> w_Drect.origin, Pt (x * CW + WXMARGIN, y * NS + WYMARGIN));
}

void
Forward_Scroll (sy, nlines)		/* starting line, number of lines */
register int    sy;
register int    nlines;
{
    register struct window *wp = gwp;

    if (nlines < 0)
	return;
    if (sy + nlines <= MAXLINE)
	bitblt (L, Rpt (Etty_Pt (0, sy + nlines),
		    Etty_Pt (MAXCOLUMN + 1, MAXLINE + 1)),
		L, Etty_Pt (0, sy), F_STORE);
    else
	nlines = MAXLINE - sy + 1;
    xstipple (L, Rpt (Etty_Pt (0, MAXLINE + 1 - nlines),
		Etty_Pt (MAXCOLUMN + 1, MAXLINE + 1)));
}

void
Open_Lines (nlines)
register int    nlines;
{
    register struct window *wp = gwp;

    if (nlines < 0)
	return;
    if (Y + nlines <= MAXLINE)
	bitblt (L, Rpt (Etty_Pt (0, Y),
		    Etty_Pt (MAXCOLUMN + 1, MAXLINE + 1 - nlines)),
		L, Etty_Pt (0, Y + nlines), F_STORE);
    else
	nlines = MAXLINE - Y + 1;

    rectf (L, Rpt (Etty_Pt (0, Y),
		Etty_Pt (MAXCOLUMN + 1, Y + nlines)), invert_mode ? F_OR : F_CLR);
}

void
Init_Window (type)
register int    type;
{
    register struct window *wp;
    register int    i;
    Layer *old_layer = gwp -> w_layer;

    wp = &w[0];

    wp -> w_Drect = Drect;
    wp -> w_layer = (Layer *) & display;
    wp -> w_xmax = (wp -> w_Drect.corner.x - wp -> w_Drect.origin.x - 2 * XMARGIN) / CW - 1;
    wp -> w_ymax = (wp -> w_Drect.corner.y - wp -> w_Drect.origin.y - 2 * YMARGIN) / NS - 1;
    wp -> w_xmargin = XMARGIN;
    wp -> w_ymargin = YMARGIN;
    if (type)
    {
	wp -> w_x = 0;
	wp -> w_y = 0;
	wp -> w_ox = 0;
	wp -> w_oy = 0;
    }
    for (i = 1; i < NWINDOW; i++)
    {
	if (w[i].w_layer == old_layer)
	    w[i].w_layer = wp -> w_layer;
    }
    wp -> w_inset = Drect.origin.x - display.rect.origin.x;
    if (invert_mode)
	rectf (wp -> w_layer, wp -> w_Drect, F_XOR);
}

#ifdef NEW_WINDOWS
int
New_Window (newindx, layerflag)
register short  newindx;
int     layerflag;
{
    register struct window *wp = gwp;
    register short  nxmax;
    register short  nymax;
    register Rectangle r;
    short   xorg;
    short   yorg;
    struct window  *oldwp;

    if ((yorg = Get_Concept ()) < 0)
	return (0);
    if ((xorg = Get_Concept ()) < 0)
	return (0);
    if ((nymax = Get_Concept ()) < 1)
	return (0);
    if ((nxmax = Get_Concept ()) < 1)
	return (0);

#ifdef NEW_LAYERS
    if (layerflag)
#endif NEW_LAYERS
    {
	if ((xorg == 0) &&
		(yorg == 0) &&
		(nxmax >= w[0].w_xmax) &&
		(nymax >= w[0].w_ymax))
	{
	    wp = &w[0];
	    wp -> w_xmargin = XMARGIN;
	    wp -> w_ymargin = YMARGIN;
	    wp -> w_x = 0;
	    wp -> w_insert = 0;
	    wp -> w_inset = INSET;
	    gwp = wp;
	    return (0);
	}

	r.origin.y = Drect.origin.y + yorg * NS + INSET;
	r.corner.y = NS * nymax;

	r.corner.y += r.origin.y;
	r.origin.x = Drect.origin.x + xorg * CW + INSET;
	r.corner.x = nxmax * CW;

	r.corner.x += r.origin.x;
	if (r.corner.y > YMAX || r.corner.x > XMAX)
	    return (0);

	w[1].w_layer = 0;		/* Always use w[1] */

	newindx = 1;
    }
#ifdef NEW_LAYERS
    else
    {
	r.origin.y = Drect.origin.y + yorg * NS - (INSET);
	if ((r.corner.y = NS * nymax + 2 * (YMARGIN + INSET)) < 50)
	    return (0);
	r.corner.y += r.origin.y;
	r.origin.x = Drect.origin.x + xorg * CW - (INSET);
	if ((r.corner.x = nxmax * CW + 2 * (XMARGIN + INSET)) < 100)
	    return (0);
	r.corner.x += r.origin.x;
	if (r.corner.y > YMAX || r.corner.x > XMAX)
	    return (0);

	w[1].w_layer = (Layer *) - 1;	/* Never use w[1] */

	oldwp = wp;
	if (newindx > 0)
	{
	    if (w[newindx].w_layer != 0)
	    {
		Del_Window (newindx);
	    }
	}
	else
	    for (newindx = 0; TRUE; newindx++)
	    {
		if (newindx == NWINDOW)
		    return (0);
		if (w[newindx].w_layer == (Layer *) 0)
		    break;
	    }
    }
#endif NEW_LAYERS

    wp = &w[newindx];
    wp -> w_xmax = nxmax - 1;
    wp -> w_ymax = nymax - 1;
    wp -> w_ox = xorg;
    wp -> w_oy = yorg;
    wp -> w_x = 0;
    wp -> w_y = 0;
    wp -> w_insert = FALSE;

#ifdef NEW_LAYERS
    if (layerflag)
#endif NEW_LAYERS
    {
	wp -> w_inset = 0;
	wp -> w_Drect.origin.x = r.origin.x;
	wp -> w_Drect.origin.y = r.origin.y;
	wp -> w_Drect.corner.x = r.corner.x;
	wp -> w_Drect.corner.y = r.corner.y;
	wp -> w_xmargin = 0;
	wp -> w_ymargin = 0;
	wp -> w_layer = w[0].w_layer;
    }
#ifdef NEW_LAYERS
    else
    {
	wp -> w_inset = INSET;
	wp -> w_Drect = inset (r, INSET);
	wp -> w_xmargin = XMARGIN;
	wp -> w_ymargin = YMARGIN;
	w[1].w_layer = 0;
	if ((wp -> w_layer = newlayer (r)) == 0)
	{
	    wp = oldwp;
	    gwp = wp;
	    return (0);
	}
	Layer_Border ();
	Curse ();
    }
#endif NEW_LAYERS
    gwp = wp;
    return (newindx);
}
#endif NEW_WINDOWS

int
Get_Concept ()
{
    register short  c;
    register short  next;

    c = Get_Char ();
    next = 0;
    switch (c)
    {
	case CTRL (A): 
	    next = 96;
	    c = Get_Char ();
	    break;

	case CTRL (B): 
	    next = 192;
	    c = Get_Char ();
	    break;
    }
    if (c < ' ')
	return (-1);
    return (next + c - ' ');
}

#ifdef NEW_LAYERS

void
Del_Window (windx)
register short  windx;
{
    register struct window *wp = gwp;
    register struct window *owp;

    if (windx < 0)
	windx = wp - &w[0];
    if (windx == 0)
	return;
    owp = wp--;
    while (wp -> w_layer == 0)
	wp--;
    if (owp -> w_layer != w[0].w_layer)
    {
	dellayer (owp -> w_layer);
	upfront (wp -> w_layer);
    }
    else
	rectf (owp -> w_layer, inset (owp -> w_Drect, -owp -> w_inset), F_CLR);
    Layer_Border ();
    owp -> w_layer = 0;
    gwp = wp;
}

/*
 * Redraw the border around the underlying
 * rectrangle.
 *
 */

void
Layer_Border ()
{
    register struct window *wp = gwp;
    register    Rectangle r;

    r = inset (wp -> w_Drect, -wp -> w_inset);
    rectf (L, Rpt (r.origin, Pt (r.corner.x, wp -> w_Drect.origin.y)), F_STORE);
    rectf (L, Rpt (Pt (r.origin.x, wp -> w_Drect.corner.y), r.corner), F_STORE);
    rectf (L, Rpt (r.origin, Pt (wp -> w_Drect.origin.x, wp -> w_Drect.corner.y)), F_STORE);
    rectf (L, Rpt (Pt (wp -> w_Drect.corner.x, wp -> w_Drect.origin.y), r.corner), F_STORE);
}

#endif NEW_LAYERS

#ifdef GRAPHICS_BORDERS		
void
Get_Border ()
{
    register int    x1;
    register int    y1;
    register int    x2;
    register int    y2;

    x1 = Get_Concept ();
    y1 = Get_Concept ();
    x2 = Get_Concept ();
    y2 = Get_Concept ();

    Line_Border (x1, y1, x2, y2);
}

void
Line_Border (x1, y1, x2, y2)
int    x1;
int     y1;
int     x2;
int     y2;
{
    register struct window *wp = gwp;
    register    Point s;
    register    Point e;

    if (x1 < 0)
	return;
    if (y1 < 0)
	return;
    if (x2 < 0)
	return;
    if (y2 < 0)
	return;
    if ((x1 >= B_SQUARE) && (x1 <= B_LOLEFT))
    {
	s = Etty_Pt (x2, y2);
	e.x = s.x + CW;
	e.y = s.y + NS;
	rectf (wp -> w_layer, Rpt (s, e), F_CLR);

	switch (x1)
	{
	    case B_SQUARE: 		/* Black Square */
		rectf (wp -> w_layer, Rpt (s, e), F_STORE);
		return;

	    case B_UPLEFT: 		/* Upper Left Corner */
		e.x = s.x + CW / 2 + 1;
		s.x = e.x - 2;
		e.y = s.y + NS;
		s.y = s.y + NS / 2 + 1;
		rectf (wp -> w_layer, Rpt (s, e), F_STORE);
		e.y = s.y;
		s.y = e.y - 2;
		s.x = e.x - 2;
		e.x += CW / 2 + 1;
		rectf (wp -> w_layer, Rpt (s, e), F_STORE);
		return;

	    case B_UPRIGHT: 		/* Upper Right Corner */
		e.x = s.x + CW / 2 + 1;
		s.x = e.x - 2;
		e.y = s.y + NS;
		s.y = s.y + NS / 2;
		rectf (wp -> w_layer, Rpt (s, e), F_STORE);
		s.x = e.x - CW / 2 - 1;
		s.y = e.y - NS;
		e.y = s.y + NS / 2 + 1;
		s.y = e.y - 2;
		rectf (wp -> w_layer, Rpt (s, e), F_STORE);
		return;

	    case B_LORIGHT: 		/* Lower Right Corner */
		e.x = s.x + CW / 2 + 1;
		s.x = e.x - 2;
		e.y = s.y + NS / 2 + 1;
		rectf (wp -> w_layer, Rpt (s, e), F_STORE);
		s.y = e.y - 2;
		s.x = e.x - CW / 2 - 1;
		rectf (wp -> w_layer, Rpt (s, e), F_STORE);
		return;

	    case B_LOLEFT: 		/* Lower Left Corner */
		e.x = s.x + CW / 2 + 1;
		s.x = e.x - 2;
		e.y = s.y + NS / 2 + 1;
		rectf (wp -> w_layer, Rpt (s, e), F_STORE);
		s.y = e.y - 2;
		s.x = e.x - 1;
		e.x = e.x - CW / 2 - 1 + CW;
		rectf (wp -> w_layer, Rpt (s, e), F_STORE);
		return;
	}
    }

    if (x1 == x2)
    {
	s = Etty_Pt (x1, y1);
	e = Etty_Pt (x1 + 1, y2);
	rectf (wp -> w_layer, Rpt (s, e), F_CLR);
	e.x = s.x + CW / 2 + 1;
	s.x = e.x - 2;
	rectf (wp -> w_layer, Rpt (s, e), F_STORE);
	return;
    }
    if (y1 == y2)
    {
	s = Etty_Pt (x1, y1);
	e = Etty_Pt (x2, y1 + 1);
	rectf (wp -> w_layer, Rpt (s, e), F_CLR);
	e.y = s.y + NS / 2 + 1;
	s.y = e.y - 2;
	rectf (wp -> w_layer, Rpt (s, e), F_STORE);
    }
}

#endif GRAPHICS_BORDERS		

#ifdef mc68000

char
Translate_Char (c)
{
    static char xtab[] =
    {
	0,				/* 0xb0 [NO SCRL] */
	'0',				/* 0xb1 [   0	] */
	'.',				/* 0xb2 [   .	] */
	0,				/* 0xb3 */
	0,				/* 0xb4 */
	0,				/* 0xb5 */
	0,				/* 0xb6 */
	0,				/* 0xb7 */
	0,				/* 0xb8 */
	0,				/* 0xb9 */
	0,				/* 0xba */
	0,				/* 0xbb */
	0,				/* 0xbc */
	0,				/* 0xbd */
	0,				/* 0xbe */
	0,				/* 0xbf */
	'1',				/* 0xc0 [   1   ] */
	'2',				/* 0xc1 [   2   ] */
	'3',				/* 0xc2 [   3   ] */
	'\r',				/* 0xc3 [ ENTER ] */
	0,				/* 0xc4 */
	0,				/* 0xc5 */
	0,				/* 0xc6 */
	0,				/* 0xc7 */
	0,				/* 0xc8 */
	0,				/* 0xc9 */
	0,				/* 0xca */
	0,				/* 0xcb */
	0,				/* 0xcc */
	0,				/* 0xcd */
	0,				/* 0xce */
	0,				/* 0xcf */
	'4',				/* 0xd0 [   4   ] */
	'5',				/* 0xd1 [   5   ] */
	'6',				/* 0xd2 [   6   ] */
	',',				/* 0xd3 [   ,   ] */
	0,				/* 0xd4 */
	0,				/* 0xd5 */
	0,				/* 0xd6 */
	0,				/* 0xd7 */
	0,				/* 0xd8 */
	0,				/* 0xd9 */
	0,				/* 0xda */
	0,				/* 0xdb */
	0,				/* 0xdc */
	0,				/* 0xdd */
	0,				/* 0xde */
	0,				/* 0xdf */
	-1,				/* 0xe0 [ BREAK ] */
	'7',				/* 0xe1 [   7   ] */
	'8',				/* 0xe2 [   8   ] */
	'9',				/* 0xe3 [   9   ] */
	'-',				/* 0xe4 [   -   ] */
	0,				/* 0xe5 [ctrl-3 ] */
	0,				/* 0xe6 */
	0,				/* 0xe7 */
	0,				/* 0xe8 */
	0,				/* 0xe9 */
	0,				/* 0xea [shift-BREAK]      */
	0,				/* 0xeb [ctrl-BREAK]       */
	0,				/* 0xec [ctrl-shift-BREAK] */
	0,				/* 0xed */
	0,				/* 0xee */
	0,				/* 0xef */
	0,				/* 0xf0 */
	'\020',				/* 0xf1 [UPARROW]    */
	'\016',				/* 0xf2 [DOWNARROW]  */
	'\02',				/* 0xf3 [LEFTARROW]  */
	'\06',				/* 0xf4 [RIGHTARROW] */
	0,				/* 0xf5 */
	0,				/* 0xf6 [ PF1 ] */
	0,				/* 0xf7 [ PF2 ] */
	0,				/* 0xf8 [ PF3 ] */
	0,				/* 0xf9 [ PF4 ] */
	0,				/* 0xfa */
	0,				/* 0xfb */
	0,				/* 0xfc */
	0,				/* 0xfd */
	0,				/* 0xfe [SET UP] */
	0				/* 0xff */
    };

    if (c & 0x80)
	return xtab[c - 0xb0];
    else
	return c;
}

#endif mc68000

void
rxstipple (l, r)
register Layer * l;
register Rectangle r;
{
    invert_mode = !(invert_mode);
    xstipple (l, r);
    invert_mode = !(invert_mode);
}

void
xstipple (l, r)				/* dmr's stipple routine */
register Layer * l;
register Rectangle r;
{
    static  Texture16
    plain =
    {
	0
    }      ,
    fancy =
    {
	0x1000
    }      ,
    rvplain =
    {
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
    }      ,
    rvfancy =
    {
	0xEFFF, 0xFFFF, 0xFFFF, 0xFFFF,
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
    };
    register Texture16 * tp;

    if (invert_mode)
	tp = ((own () & MOUSE) || (m_own_bug)) ? &rvplain : &rvfancy;
    else
	tp = ((own () & MOUSE) || (m_own_bug)) ? &plain : &fancy;

    rectclip (&r, P -> rect);
    texture16 (l, r, tp, F_STORE);
}

void
Re_Shape ()
{
    register struct Proc   *p = P;
    register    Rectangle r;

    r = p -> rect;
    p -> rect = Drect;
    p -> state |= RESHAPED;
    mpxnewwind (p, C_RESHAPE);
    p -> rect = r;
}

void
Re_Size (type)
register int    type;
{
    register Rectangle *ptr_drect = &Drect;
    register Rectangle *ptr_banner = &banner;

    if (banner_type)
    {
	if ((banner_type & (TOP_BANNER | BANNER)) &&
		(ptr_drect -> origin.y > (ptr_drect -> corner.y - (2 * NS))))
		banner_type &= ~(TOP_BANNER | BANNER);

	if (banner_type & TOP_BANNER)	/* Code in document style */
	{
	    ptr_drect -> origin.y += NS;
	    ptr_banner -> origin.x = ptr_drect -> origin.x;
	    ptr_banner -> origin.y = ptr_drect -> origin.y - NS;
	    ptr_banner -> corner.x = ptr_drect -> corner.x;
	    ptr_banner -> corner.y = ptr_drect -> origin.y;
	}
	else
	{
	    if (banner_type & BANNER)
	    {
		ptr_drect -> corner.y -= NS;
		ptr_banner -> origin.x = ptr_drect -> origin.x;
		ptr_banner -> origin.y = ptr_drect -> corner.y;
		ptr_banner -> corner.x = ptr_drect -> corner.x;
		ptr_banner -> corner.y = ptr_drect -> corner.y + NS;
	    }
	}

#ifdef DO_ICONS
	if ((banner_type & ICONS) &&
		(ptr_drect -> origin.y > (ptr_drect -> corner.y - (ICON_SIZE + 2 * NS + 11))))
		banner_type &= ~(ICONS);
	
	if (banner_type & ICONS)
	{				/* 5 pixels above + icon + 5 pixels
					   above + 1 line */
	    ptr_drect -> corner.y = ptr_drect -> corner.y - (ICON_SIZE + NS + 11);
	    dir.origin.x = ptr_drect -> origin.x;
	    dir.origin.y = ptr_drect -> corner.y;
	    dir.corner.x = ptr_drect -> corner.x;
	    dir.corner.y = ptr_drect -> corner.y + ICON_SIZE + NS + 11;
	}
#endif DO_ICONS
    }
    Re_Shape ();

    if (banner_type & (BANNER | TOP_BANNER))
	Draw_Banner ();

#ifdef DO_ICONS
    if (banner_type & ICONS)
	Draw_Icons ();
#endif DO_ICONS

/*
 *	Initialize the Main Window
 *
 */
    Init_Window (type);
}

Draw_Box (xr, type)
register    Rectangle xr;
register int    type;
{
    if (type)
	rxstipple (&display, xr);
    else
	xstipple (&display, xr);
    rectf (&display, inset (xr, 1), F_XOR);
    rectf (&display, inset (xr, 2), F_XOR);
}

Draw_Banner ()
{
    rxstipple (&display, banner);
    if (banner_type & TEXTURE_BANNER)
	texture16 (&display, banner, &Dots, F_XOR);
}

#ifdef DO_ICONS

Draw_Icons ()
{
    register int    key;
    register int    len;
    register    Point xp;

    cur_icon_rect.corner.y = 0;

    Draw_Box (Rpt (dir.origin,
		Pt (Drect.corner.x, dir.origin.y + ICON_SIZE + NS + 11)), TRUE);

 /* Add the inter-icon distance */
    xp.x = dir.origin.x + ((ICON_CHARS * CW + 2) - ICON_SIZE) / 2;
    xp.y = dir.origin.y;
    for (key = 0; key < TOTAL_OBJECTS; key++)
    {
	Draw_One_Icon (key, xp);
	xp.x += ICON_CHARS * CW + 2;
    }
}

Draw_One_Icon (key, xp)
register int    key;
register    Point xp;
{
    register struct icon_object *ti_object;
    register struct object *ptr_object;

    ptr_object = &list[key];

    ti_object = (struct icon_object *) ptr_object -> datum;

    if ((ti_object) &&
	    (xp.x < (Drect.corner.x - (ICON_CHARS * CW + 2))))
    {
	ptr_object -> trect.origin.x = xp.x + 2;
	ptr_object -> trect.origin.y = xp.y + 6;
	ptr_object -> trect.corner.x = xp.x + ICON_SIZE + 2;
	ptr_object -> trect.corner.y = xp.y + ICON_SIZE + 6;

/* Box the icon
	Draw_Box (inset (ptr_object -> trect, -3), FALSE);
*/
	bitblt (ti_object -> map,
		ti_object -> map -> rect,
		&display,
		ptr_object -> trect.origin,
		F_XOR);

	string (&defont, ptr_object -> title,
		&display,
		Pt (ptr_object -> trect.origin.x, ptr_object -> trect.corner.y + 5),
		F_XOR);
    }
    else
	ptr_object -> trect.corner.y = 0;
}

/*
 * The icon hacking stuff follows the general hackery in the icon program.
 * Most of the intelligence (and I use the word losely) is in the
 * downloading routine.  Use TRIM_RECT if you want the icons trimmed to
 * minimum size.
 *
 */

#ifdef TRIM_RECT
extern  Rectangle OpLoad ();
#else
void OpLoad ();
#endif TRIM_RECT

Bitmap *
Load_Icon ()
{
    register    Bitmap * text;

    text = balloc (Rect (0, 0, ICON_SIZE, ICON_SIZE));
    rectf (text, text -> rect, F_CLR);

#ifdef TRIM_RECT
    text -> rect = OpLoad (text);
#else
    OpLoad (text);
#endif TRIM_RECT

    return (text);
}

#ifdef TRIM_RECT
Rectangle
#else
void
#endif TRIM_RECT

OpLoad (bitmap)
Bitmap * bitmap;
{
    Rectangle rect;
    register int    ch;
    register int    i;
    register int    j;

#ifdef TRIM_RECT
    int     xsize = 0;
    int     ysize;
#endif TRIM_RECT

    rect = bitmap -> rect;

    i = rect.origin.x;
    j = rect.origin.y;

    for (;;)
    {
	while ((ch = Get_Concept ()) < 258)
	{
	    putnibble (ch, bitmap, rect, Pt (i, j));
	    i += 8;
	}
	if (ch == 258)
	{

#ifdef TRIM_RECT
	    xsize = max (xsize, i - rect.origin.x);
#endif TRIM_RECT

	    i = rect.origin.x;
	    j++;
	    continue;
	}
    /*    if (ch == 259) */
	break;
    }

#ifdef TRIM_RECT
    ysize = j - rect.origin.y;
    rect.origin.x = 0;
    rect.origin.y = 0;
    rect.corner.x = xsize;
    rect.corner.y = ysize;
    return (rect);
#endif TRIM_RECT

}

/*
 * This is poorly named - but matches the stuff in icon.c
 * this adds 8 bits worth of stuff
 *
 */
putnibble (nibble, b, clipr, p)
register int    nibble;
Bitmap * b;
Rectangle clipr;
Point p;
{
    register int    i;
    register int    k;

    for (i = 1 << 7, k = 0; k < 8; k++)
    {
	if (nibble & i)
	{
	    if (ptinrect (p, clipr))
		point (b, p, F_OR);
	}
	p.x++;
	i = i >> 1;
    }
}

struct icon_object *
Get_N_Icon (key, type)
register int    key;
register int    type;
{
    register struct icon_object *object;

    object = i_object;
    while (object)
    {
	if (object -> id == key)
	    return (object);
	object = object -> next_icon;
    }
    if (type)
    {
	object = (struct icon_object   *) alloc (sizeof (struct icon_object));
	if (object)
	{
	    object -> next_icon = i_object;
	    object -> id = key;
	    i_object = object;
	}
    }
    return (object);
}

#endif DO_ICONS

/* For debugging */
/*
ettyprint (s)
char   *s;
{
    register struct window *wp = gwp;
    register struct window *winp;
    char    buf[2];

    winp = wp;
    wp = &w[0];
    buf[1] = 0;
    while ((buf[0] = *s++) != 0)
    {
	string (&defont, buf, L, Etty_Pt (X, Y), F_STORE);
	X++;
	if (X > MAXCOLUMN)
	{
	    X = 0;
	    New_Line ();
	}
    }
    wp = winp;
}
*/
