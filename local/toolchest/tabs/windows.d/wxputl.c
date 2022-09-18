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
#include "vt.h"
#include "windows.h"

/*
 *	wxputl (Winner, cp, attribute, Scrollp)
 *
 *	This procedure prints a line to the specified window.  This
 *	procedure is only used internally.
 *
 */

void
wxputl (Winner, cp, attribute, Scrollp)
register struct window  *Winner;
char  *cp;			/* string pointer */
int     attribute;
int     Scrollp;
{
	CHAR    cbuf[256];		/* line buffer */
	CHAR     i;
	register CHAR	*wm_ptr;
	unsigned int *km_ptr;
	register int      b;
	int     mb;
	int bstart;
	int blength;
	int spaces;
	int last;
	int area_on = 0;

	w_xgo (Winner, Winner -> _x_pos, Winner -> _y_pos);

	if (Need_Set_Scroll)
		_fix_map ();

	if ((Area_On) && (Area[0].bot_y) && (Area_Attribute))
		area_on = attribute & VT_AREA;
	attribute &= VT_VIDEO;

	bstart = mb = b = mcol;			/* buffer pointer */
	wm_ptr = &Winner -> _map[mline - Winner -> _top_x][b - Winner -> _top_y];
	km_ptr = kmap[mline];
	spaces = 0;

	while (TRUE)
	{
		if (b > mb)
			mb = b;
		if (b > (Winner -> _bot_y - 1))
		{
			blength = b - bstart;
			b = do_end (spaces, b, blength, cbuf);
			if ((mline + 1) >= Winner -> _bot_x)
			{
				wcflush (cbuf, b, blength);

				if ((*cp == 0) && !(Scrollp))
				{
					w_xgo (Winner, mline - Winner -> _top_x,
						b - Winner -> _top_y);
					return;
				}

				if (Winner -> _type_scroll)
				{
					if ((LOPEN) && (Winner -> _scrollable))
					{
						wvadjust (Winner,
							Winner -> _v_x_top,
							Winner -> _v_y_top,
							Winner -> _v_x_bot,
							Winner -> _v_y_bot,
							TRUE,
							-1);
					}
					else
					{
						wscroll (Winner, 1);
						Wrefresh (Winner);
					}
					mline = Winner -> _bot_x - 1;
					mcol = Winner -> _top_y;
				}
				else
				{
					mline = Winner -> _top_x;
					mcol = Winner -> _top_y;
				}
			}
			else
			{
				wcflush (cbuf, b, blength);
				mline++;
			}

			Winner -> _y_pos = 0;
			Winner -> _x_pos = mline - Winner -> _top_x;
			bstart = b = mcol = Winner -> _top_y;
			wm_ptr = &Winner -> _map[mline - Winner -> _top_x][b - Winner -> _top_y];
			km_ptr = kmap[mline];
			spaces = 0;

			last = Winner -> _bot_y + 1;

			while (last < mb)
			{
				if (b < Winner -> _bot_y)
					*wm_ptr = cbuf[last];

				if (Winner -> _key & km_ptr[b])
				{
					cbuf[b] = cbuf[last];
				}
				else
				{
					do_null_char (b, cbuf);
				}
				b++;
				wm_ptr++;
				last++;
			}
			mb = b;		/* RESET */
		}

	/* Process Next character */
#ifdef DO_META_CHARS
		i = (*cp & 0377) | attribute;
#else
		i = (*cp & 0177) | attribute;
#endif
		if ((*cp++) == 0)
		{
			Winner -> _y_pos = b - Winner -> _top_y;
			Winner -> _x_pos = mline - Winner -> _top_x;

			blength = b - bstart;
			b = do_end (spaces, b, blength, cbuf);
			wcflush (cbuf, b, blength);
			w_xgo (Winner, Winner -> _x_pos, Winner -> _y_pos);
			return;
		}

#ifdef DO_META_CHARS
		if ((i & VT_CHAR) == VTNEWLINE)
#else
		if ((i & VT_CHAR) == '\n')
#endif
		{
			blength = b - bstart;
			b = do_end (spaces, b, blength, cbuf);
			wcflush (cbuf, b, blength);

			if (++mline >= Winner -> _bot_x)
			{
				if (Winner -> _type_scroll)
				{
					if ((LOPEN) && (Winner -> _scrollable))
					{
						wvadjust (Winner,
							Winner -> _v_x_top,
							Winner -> _v_y_top,
							Winner -> _v_x_bot,
							Winner -> _v_y_bot,
							TRUE,
							-1);
					}
					else
					{
						wscroll (Winner, 1);
						Wrefresh (Winner);
					}

					mline = Winner -> _bot_x - 1;
					mcol = Winner -> _top_y;
				}
				else
				{
					mline = Winner -> _top_x;
					mcol = Winner -> _top_y;
				}
			}
			Winner -> _y_pos = 0;
			Winner -> _x_pos = mline - Winner -> _top_x;
			mcol = bstart = mb = b = Winner -> _top_y;
			wm_ptr = &Winner -> _map[mline - Winner -> _top_x][b - Winner -> _top_y];
			km_ptr = kmap[mline];
			spaces = 0;

			if (!Winner -> _type_scroll)
				wclrl (Winner);
			continue;	/* re-loop */
		}
#ifdef DO_META_CHARS
		if (i & META)
		{
			*wm_ptr = 'M' | attribute;
			if (Winner -> _key & km_ptr[b])
			{
				cbuf[b] = *wm_ptr;
			}
			else
			{
				do_null_char (b, cbuf);
			}
			b++;
			wm_ptr++;
			if (b >= Winner -> _bot_y - 1)
			{
				cp--;
				*cp -= META;
				cp--;
				*cp = '-';
				continue;
			}
			*wm_ptr = '-' | attribute;
			if (Winner -> _key & km_ptr[b])
			{
				cbuf[b] = *wm_ptr;
			}
			else
			{
				do_null_char (b, cbuf);
			}
			b++;
			wm_ptr++;
			if (b > mb)
				mb = b;
			cp--;
			cp -= META;
			continue;
		}

#endif DO_META_CHARS

reswitch:
		switch (ptype[i & VT_CHAR])
		{
			case UL: 
			case PLAIN: 
				*wm_ptr = i;
				if (Winner -> _key & km_ptr[b])
				{
					if( area_on && in_area( mline, b ) )
						*wm_ptr |= Area_Attribute;
					cbuf[b] = *wm_ptr;
				}
				else
				{
					do_null_char (b, cbuf);
				}
				if (cbuf[b] == ' ')
					spaces++;
				b++;
				wm_ptr++;
				break;

			case BACKSP:
			case CONTRL:
				*wm_ptr = '^' | attribute;
				if (Winner -> _key & km_ptr[b])
				{
					if( area_on && in_area( mline, b ) )
						*wm_ptr |= Area_Attribute;
					cbuf[b] = *wm_ptr;
				}
				else
				{
					do_null_char (b, cbuf);
				}
				b++;
				wm_ptr++;
			/* Handle things like ^_ correctly! */
				i ^= 0100;
				goto reswitch;

			case TAB: 
				last = TABSTOP - ((b - Winner -> _top_y)
						% TABSTOP);
				while (last--)
				{
					*wm_ptr = ' ' | attribute;
					if (Winner -> _key & km_ptr[b])
					{
						if( area_on && in_area( mline, b ) )
							*wm_ptr |= Area_Attribute;
						cbuf[b] = *wm_ptr;
					}
					else
					{
						do_null_char (b, cbuf);
					}
					if (cbuf[b] == ' ')
						spaces++;
					if (b >= (Winner -> _bot_y - 1))
						break;
					b++;
					wm_ptr++;
				}
				break;
		}
	}
 /* Not Reached */
}

static int
do_end (spaces, b, blength, cbuf)
int spaces;
int b;
int blength;
CHAR cbuf[];
{
	register CHAR *cm_ptr;
	register CHAR *cb_ptr;
	register CHAR *ce_ptr;
	int jnk;
	int got_one;

	if (blength < DLOOK)
		return (b);

	jnk = scrjnk[mline];
	got_one = 0;

	cb_ptr = &cbuf[b];
	cm_ptr = &cmap[mline][b];
	ce_ptr = &cbuf[jnk];

	while (cb_ptr < ce_ptr)
	{
		*cb_ptr = *cm_ptr;

		if (*cb_ptr == 0)
			*cb_ptr = ' ';

		if (*cb_ptr != ' ')
			got_one++;

		cb_ptr++;
		cm_ptr++;
	}

	if (got_one == 0)
	{
		if (CLINE)
		{
			if (spaces == blength)
				clrl ();
		}
		cbuf[b] = 0;
		return (b);
	}
	return (jnk);
}

static int
do_null_char (b, cbuf)
register int b;
register CHAR cbuf[];
{
	if (b >= scrjnk[mline])
	{
		cbuf[b] = ' ';
	}
	else
	{
		cbuf[b] = cmap[mline][b];
		if (cbuf[b] == 0)
			cbuf[b] = ' ';
	}
}

in_area( x, y )
register int	x;
register int	y;
{
	register int	i;

	for( i = 0 ; i < 3 ; i++ )
	{
		if( Area[i].bot_y && x >= Area[i].top_x && y >= Area[i].top_y && 
				x <= Area[i].bot_x && y <= Area[i].bot_y )
			return( 1 );
	}
	return( 0 );
}
