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

#define TRUE		1
#define FALSE		0

#define CTRL(x)		('x' & 037)
#define ESC		0x1B

 /* Font properties */
#define	CW		9
#undef NS
#define	NS		16
#define	CURSOR		"\1"

 /* Border things */
#define INSET		3
#define	XMARGIN		3
#define	YMARGIN		3

 /* The width of an icon - must be > 64 bits (CW * ICON_CHARS) */
#define ICON_CHARS	8
#define MENU_ITEMS	16

#define TYPE_MENU	1
#define TYPE_ICON	2

 /* bits on each edge of an icon */
#define ICON_SIZE	50

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

struct object list[TOTAL_OBJECTS];
struct icon_object *i_object = 0;
int Trim_Icons;
int Box_Icons;

extern Point mpt ();
extern char Get_Char ();
extern Bitmap * Load_Icon ();
extern struct icon_object * Get_N_Icon ();

main ()
{
	register int    device;
	register char   buf[2];
	struct icon_object     *ti_object;
	int     X;
	int     Y;
	int     key;

	jinit ();
	request (RCV | SEND);

	X = Y = 0;
	buf[1] = '\0';
	Trim_Icons = FALSE;
	Box_Icons = TRUE;

	while (TRUE)
	{
		device = wait (RCV);
		if (device & RCV)
			buf[0] = rcvchar ();
		else
			continue;

		*buf &= 0177;
		switch (buf[0])
		{
		case '\r':
		case '\n':
			X = 0;
			break;
		case ESC: 
			switch (Get_Char ())
			{
			case 't': 
			/* Read an Icon */
				key = Get_Flag ();
				if ((ti_object = Get_N_Icon (key, TRUE)) == 0)
					break;
				if (ti_object -> map)
					bfree (ti_object -> map);
				ti_object -> map = Load_Icon ();
				list[key].title = "Some Title";
				list[key].datum = (char *) ti_object;
				list[key].type = TYPE_ICON;
				Draw_One_Icon (key,
				    Pt (Drect.origin.x + 50, Drect.origin.y + 50));
				break;
			}
			break;
			
		default: 
			if (buf[0] < ' ')
				break;
			stipple (Rpt (mpt (X, Y), mpt (X + 1, Y + 1)));
			string (&defont, buf, &display, mpt (X, Y), F_XOR);
			X++;
			if (X > 40)
				X = 0;

		}
	}
}

char
Get_Char ()
{
	while (wait (RCV) != RCV)
		;
	return rcvchar ();
}

int
Get_Flag ()
{
    return (Get_Concept () & 037);
}

int
Get_Concept ()
{
	register c;
	register next;

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

Draw_One_Icon (key, xp)
register int    key;
register        Point xp;
{
	register struct icon_object    *ti_object;
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

		if (Box_Icons)
			Draw_Box (inset (ptr_object -> trect, -3), FALSE);

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

Draw_Box (xr, type)
register    Rectangle xr;
register int    type;
{
    stipple (xr);
    if (type)
	    rectf (&display, xr, F_XOR);
    rectf (&display, inset (xr, 1), F_XOR);
    rectf (&display, inset (xr, 2), F_XOR);
}

/*
 * The icon hacking stuff follows the general hackery in the icon program.
 * Most of the intelligence (and I use the word losely) is in the
 * downloading routine.  Use Trim_Icons if you want the icons trimmed to
 * minimum size.
 *
 */

extern  Rectangle OpLoad ();

Bitmap *
Load_Icon ()
{
	register Bitmap * text;

	text = balloc (Rect (0, 0, ICON_SIZE, ICON_SIZE));
	rectf (text, text -> rect, F_CLR);

	if (Trim_Icons)
		text -> rect = OpLoad (text);
	else
		OpLoad (text);

	return (text);
}

Rectangle
OpLoad (bitmap)
Bitmap * bitmap;
{
	Rectangle rect;
	register int    ch;
	register int    i;
	register int    j;
	int     xsize = 0;
	int     ysize;

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

			if (Trim_Icons)
				xsize = max (xsize, i - rect.origin.x);

			i = rect.origin.x;
			j++;
			continue;
		}
	/*    if (ch == 259) */
		break;
	}

	if (Trim_Icons)
	{
		ysize = j - rect.origin.y;
		rect.origin.x = 0;
		rect.origin.y = 0;
		rect.corner.x = xsize;
		rect.corner.y = ysize;
	}
	return (rect);
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

struct icon_object     *
Get_N_Icon (key, type)
register int    key;
register int    type;
{
	register struct icon_object    *object;

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

Point
mpt (x, y)
register        x;
register        y;
{
	return add (Drect.origin, Pt (x * CW + XMARGIN, y * NS + YMARGIN));
}
