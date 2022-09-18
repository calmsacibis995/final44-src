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
 * Please pardon all of the *#!* defines in netty.  Netty is used on a lot
 * of odd hardware and in a lot of odd configurations.  The optional
 * parts are #defined in as described below:
 *
 *	NEW_WINDOWS		- firmware windows like the Concept 100
 *	GRAPHICS_BORDERS	- enables a small graphics character set
 *	VT_TERMINFO		- for use with cures driven stuff
 *	NEW_LAYERS		- allows layers to be created internally
 *	DO_ICONS		- icon hacks
 *
 *	WARREN			- for Warren Montgomery
 *	OLSON_BLIT		- Olson Blits from IH
 *	BBN			- BitGraphs from BBN
 *	mc68000			- Motorola 68000 based
 *	dmd			- DMD (this is assumed ifndef mc68000
 *
 */

#define NEW_WINDOWS		1
#define GRAPHICS_BORDERS	1
#define VT_TERMINFO		1
#define DO_ICONS		1
#undef NEW_LAYERS

#ifndef NEW_WINDOWS
#undef NEW_LAYERS
#endif

#ifdef WARREN
#define OLSON_BLIT		1	/* compile for Olson Blit */
#endif WARREN

#ifdef OLSON_BLIT || BBN || BLIT
#define mc68000			1
#endif

#ifndef mc68000
#define dmd	1
#endif

#ifdef  BBN
#define KBDDR		((char *)0x10009)
#else
#define KBDDR		((char *)(384*1024L+062))
#endif

/* use bttn instead of button for blit type programs.*/

#ifdef mc68000
#define bttn1	button1
#define bttn2	button2
#define bttn3	button3
#define bttn12	button12
#define bttn23	button23
#define bttn123	button123
#endif

/* use Texture16 now rather that Texture for blit type code */
#ifdef mc68000
#define Texture16	Texture
#define texture16	texture
#endif

#ifdef mc68000
#define ringbell()	(*KBDDR = 2)
#endif

#define GLINE(x)	(x>>8)
#define GCH(x)		(x&0377)
#define MKADD(x,y)	((x<<8)+y)

#define TRUE		1
#define FALSE		0

 /* Font properties */
#define	CW		9
#undef NS
#define	NS		16
#define	CURSOR		"\1"

#ifdef mc68000

#define PFK_START	0xf1

#define UPARROW		0xf1
#define DOWNARROW	0xf2
#define LEFTARROW	0xf3
#define RIGHTARROW	0xf4

#define	PF1		0xf6
#define	PF2		0xf7
#define	PF3		0xf8
#define PF4		0xf9
#define N_KEYS		9

#else

#define PFK_START	0x82

#define	PF1		0x82
#define	PF2		0x83
#define	PF3		0x84
#define PF4		0x85
#define	PF5		0x86
#define	PF6		0x87
#define	PF7		0x88
#define PF8		0x89

#define CLEARARROW	0x8A

#define HOMEARROW	0x8B
#define UPARROW		0x8C
#define BOTTOMARROW	0x8D

#define LEFTARROW	0x8E
#define DOWNARROW	0x8F
#define RIGHTARROW	0x90

#define N_KEYS		15

#define BREAK_KEY	0x80
#define DISCON_KEY	0x81

#endif

#define STRINGLEN	128
#define MENUS		4
#define MENU_ITEMS	16

#define B_SQUARE	97
#define B_UPLEFT	98
#define B_UPRIGHT	99
#define B_LORIGHT	100
#define B_LOLEFT	101

#define	NUL		0x00
#define ESC		0x1B

#ifdef OLSON_BLIT
#define NOSCRL		0xED
char   *kstr[128];			/* Gross, but covers the * whole
					   keyboard */
#else
#define NOSCRL		0xb0
#endif OLSON_BLIT

#define BANNER		01
#define TOP_BANNER	02
#define TEXTURE_BANNER	04
#define ICONS		010

#define INSET		3
#define	XMARGIN		3
#define	YMARGIN		3

#ifdef NEW_LAYERS
#define NWINDOW		10		/* # windows handled / process */
#else
#define NWINDOW		2
#endif

#define CTRL(x)		('x' & 037)

#define X		wp->w_x
#define Y		wp->w_y
#define MAXCOLUMN	wp->w_xmax
#define MAXLINE		wp->w_ymax
#define L		wp->w_layer
#define WXMARGIN	wp->w_xmargin
#define WYMARGIN	wp->w_ymargin

/*
 *	Functions and Procedures in Etty
 *
 */
int     Get_Flag ();
int     Allocd ();
int     Int_To_Str ();
int     Get_String ();
int     New_Window ();
int     Get_Concept ();
int     chad ();
int     read_one ();
char    _Get_Old ();
char    Get_Char ();
char    Translate_Char ();
Point Etty_Pt ();
Bitmap *Load_Icon ();
struct icon_object * Get_N_Icon ();
void blank ();
void rxstipple ();
void xstipple ();
void Re_Shape ();
void Re_Size ();
void Change_String ();
void Toggle_State ();
void Read_Texture ();
void Clear_To_Eol ();
void Invert_Char ();
void Underline_Char ();
void _C_Unget ();
void _Str_Unget ();
void Flicker ();
void Read_Mouse ();
void Read_Kbd ();
void New_Line ();
void Get_More ();
void Curse ();
void Forward_Scroll ();
void Open_Lines ();
void Init_Window ();
void Del_Window ();
void Layer_Border ();
void Get_Border ();
void Line_Border ();

/*
 *	Globals - could hide this stuff by declaring it in main ()
 *	this is a little faster and smaller - reduced argument
 *	passing.
 *
 */
struct window
{
    int     w_x;			/* current character position */
    int     w_y;
    int     w_xmargin;
    int     w_ymargin;
    int     w_xmax;			/* # characters / line */
    int     w_ymax;			/* # lines of characters in window */
    int     w_ox;			/* window origin in characters */
    int     w_oy;			/* window origin in characters */
    int     w_inset;			/* width of border in pixels */
    int     w_insert;			/* character insert mode flag */
            Rectangle w_Drect;
            Layer * w_layer;
};

struct window   w[NWINDOW];
struct window  *gwp;
char    str_buffer[STRINGLEN];
int     mouse_mode;
int     vi_mode;
int     under_mode;
int     current_menu;
int     MIT_mode;
int     graphics_chars;
int     more_mode;
int     invert_mode;
int     freeze;
int     ixon_mode;
int     marked_mode;
int     banner_type;
Rectangle banner;

 /* KBD_SIZE must be a power of 2 */
#define KBD_SIZE	128

char    kbd_buf[KBD_SIZE];
char   *kbd_ptr = kbd_buf;
int     kbd_count = 0;

Texture16 Dots =
{
    0xFFFE, 0xFFFF, 0xFFFF, 0xFFFF,
	0xFEFF, 0xFFFF, 0xFFFF, 0xFFFF,
	0xFFFE, 0xFFFF, 0xFFFF, 0xFFFF,
	0xFEFF, 0xFFFF, 0xFFFF, 0xFFFF,
};

 /* White Outlined Square with a Very Small Arrow */
Texture16 Text_Cursor =
{
    0xC9FF, 0xE9FF, 0x7803, 0x3803,
	0xF803, 0x0003, 0x0003, 0xC003,
	0xC003, 0xC003, 0xC003, 0xC003,
	0xC003, 0xC003, 0xFFFF, 0xFFFF,
};

 /* Assume that "A" and "B" encloses the menus */

Menu menu;

char   *lowest_mem = "A";

#define INVERT_ITEM	1
#define MIT_ITEM	2
#define MORE_ITEM	3

#define EMACS_MENU	1
#define VI_MENU		2

char   *menuchars[MENUS][MENU_ITEMS + 1] =
{
    {					/* Top Level Menu */
	"clear",
	"invert",
	"mit scroll",
	"more",
	"reset",
	0
    },
    {					/* EMACS menu */
	"Top of File",
	"Bottom of File",
	"Page Back",
	"Page Forward",
	"Scroll Back",
	"Scroll Forward",
	"Set Mark",
	"Show Mark",
	"Insert Last Kill",
	"Kill Marked Area",
	"Button 1 Marks",
	"Button 1 Snarfs",
	"Button 1 Kills",
	0
    },
    {					/* vi menu */
	0
    }
};

char   *menuvalues[MENUS][MENU_ITEMS] =
{
    {					/* Top Level Menu Values */
	"##\014",
	"##\033\022",
	"##\033\020\033Y z\033Z",
	"##\033\027",
	"##\033R@\033U@\033C@\033I@\033X@\033{@\033[@\033#@\033P@\033W@\033v  \01 \01 \014",
	0
    },
    {					/* EMACS Menu Values */
	"\033<",
	"\033>",
	"\033v",
	"\026",
	"\033\020",
	"\033\016",
	"\033 ",
	"\030\030",
	"\031",
	"\027",
	"\033\061\030\066",
	"\033\062\030\066",
	"\033\063\030\066",
	0
    },
    {					/* vi Menu Values */
	"1G",
	"G",
	"\025",
	"\04",
	"\031",
	"\05",
	"m`",
	"``",
	"P",
	"d``",
	":map \030\035 m`\030\037\r",	/* Mouse Marks */
	":map \030\035 m`y\030\037\r",	/* Mouse Snarfs */
	":map \030\035 m`d\030\037\r",	/* Mouse Deletes */
	0
    }
};

static char *pfkey[N_KEYS] =
{
#ifdef mc68000
    "\030OA",
    "\030OB",
    "\030OC",
    "\030OD",
    "\0",
    "\030OE",
    "\030OF",
    "\030OG",
    "\030OH"
#else
    "\030OE",				/* PF1 - '@' */
    "\030OH",				/* PF2 - 'A' */
    0,					/* PF3 - 'B' */
    0,					/* PF4 - 'C' */
    0,					/* PF5 - 'D' */
    0,					/* PF6 - 'E' */
    0,					/* PF7 - 'F' */
    0,					/* PF8 - 'G' */

/*
 *	These are laid out left to right top to bottom as they
 *	appear on the numberic keypad.
 */

    "##\014",				/* CLEARARROW	- 'H' */

    "\030OF",				/* HOMEARROW	- 'I' */
    "\030OA",				/* UPARROW	- 'J' */
    "\030OG",				/* BOTTOMARROW	- 'K' */

    "\030OC",				/* LEFTARROW	- 'L' */
    "\030OB",				/* DOWNARROW	- 'M' */
    "\030OD"				/* RIGHTARROW	- 'N' */
#endif
};

char   *highest_mem = "B";


 /* mpx internal to reset ioctl() size */
#define	C_RESHAPE	8
int m_own_bug = FALSE;

 /* Fake device type - should be larger than anything returned from wait() */
#define INTERN_BUFFER	512

struct icon_object
{
	Bitmap *map;
	int id;
	struct icon_object *next_icon;
};

struct menu_object
{
	char *vals[2][MENU_ITEMS];
	int id;
	struct menu_object *next_menu;
};

struct object
{
	char *title;
	char *ret_value;
	char *datum;
	Rectangle trect;
	char type;
};

#define TOTAL_OBJECTS		12

#ifdef DO_ICONS

struct object list[TOTAL_OBJECTS];
struct icon_object *i_object = 0;
Rectangle cur_icon_rect;
Rectangle dir;

#endif DO_ICONS

 /* The width of an icon - must be > 64 bits (CW * ICON_CHARS) */
#define ICON_CHARS	8

#define TYPE_MENU	1
#define TYPE_ICON	2

 /* bits on each edge of an icon */
#define ICON_SIZE	50
