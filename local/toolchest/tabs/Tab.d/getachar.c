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
#include <termio.h>
#include "vt.h"
#include "windows.h"
#include "fields.h"

 /*
  * Assume that all function keys transmit READAHEAD or
  * less including the leadin.
  *
  * READAHEAD must be a power of 2.
  *
  */

#define READAHEAD	8
#define CL_SIZE		READAHEAD*2

static char clist[CL_SIZE];
static char *cptr;
static int cl_count;

/*
 *	getachar ()
 *
 *	This function is the general purpose read routine for the forms
 *	stuff.  This function recognizes cursor pad keys and mouse tracks.
 *	The current mouse stuff is for Blits using etty.
 *
 */

getachar (field_ptr)
struct field_item *field_ptr;
{
	extern int mline;
	extern int mcol;
	extern struct termio    nttybuf;
	extern struct termio    rttybuf;
	extern char _get_old ();

	register int	i;
	register int    rc;
	register int len;
	char    ch;
	register char    ch2[READAHEAD + 1];

	if (field_ptr)
		w_mgo (field_ptr -> window,
			field_ptr -> window -> _x_pos,
			field_ptr -> window -> _y_pos);
	else
		mgo (mline, mcol);

	fflush (stdout);

	i = 0;
Read_One:
	if ((cptr) && (*cptr))
	{
		rc = 1;
		ch = _get_old ();
	}
	else
		rc = read (0, &ch, 1);

	if (((rc == 0) || (ch == nttybuf.c_cc[VEOF])) &&
		(chartyp[nttybuf.c_cc[VEOF]] == BREAK))
		return (K_EOF);

	if (rc == -1)
	{
		if (i++ > 5)	/* Retry 6 times */
				return (K_EOF);
		goto Read_One;
	}

	if (KLEADIN && (ch == *KLEADIN))
	{
		if ((cptr) && (*cptr))
		{
			for (rc = 0; rc < READAHEAD; )
			{
				if ((ch2[rc] = _get_old ()) == 0)
				{
					rc += _delay_read (&ch2[rc], READAHEAD - rc);
					break;
				}
				rc++;
			}
		}
		else
		{
			rc = _delay_read (ch2, READAHEAD);
		}

		if (rc != 0)
		{
			ch2[rc] = '\0';
			MOUSE_TYPE = 0;
			if (_Key( K_MOUSE2 ) && (len = _strcmp (ch2, _Key( K_MOUSE2 ))))
			{
				MOUSE_TYPE = K_MOUSE2;
				goto mouse;
			}

			if (_Key (K_MOUSE) && (len = _strcmp (ch2, _Key(K_MOUSE))))
			{
				MOUSE_TYPE = K_MOUSE;
			}

mouse:			if( MOUSE_TYPE )
			{
				if( ch2[ len ] != '\0' )
					_unget_str( &ch2[ len ] );

				ch2[len] = getachar( field_ptr );
				ch2[len + 1] = getachar( field_ptr );
				ch2[len + 2] = getachar( field_ptr );
				ch2[len + 3] = '\0';
				MOUSE_BUTTON = ch2[len] & 0377;
				MOUSE_Y = ch2[len + 1] & 0377;
				MOUSE_X = ch2[len + 2] & 0377;
				
				MOUSE_Y -= 32;
				MOUSE_X -= 32;

				return (MOUSE_TYPE);
			}
			else for( i = 0; i < _NKEYS; i++ )
			{
				if (PAD_KEYS[i] && (len = _strcmp (ch2, PAD_KEYS[i])))
				{
					_unget_str (&ch2[len]);
					return (i + K_HOME);
				}
			}


			return (K_NULL);
		}
	}

	return (ch & 0377);
}

static int
_strcmp (string, target)
register char *string;
register char *target;
{
	register int count;

	count = 0;

	while (*target)
	{
		if (*string == '\0')
			return (0);
		if (*target != *string)
			return (0);
		target++;
		string++;
		count++;
	}

	return (count);
}

static char
_get_old ()
{
	register char c;

	c = *cptr;
	*cptr = '\0';
	cl_count++;
	cl_count &= CL_SIZE - 1;
	cptr = &clist[cl_count];
	return (c);
}

_ungetc (c)
register char c;
{
	cl_count--;
	cl_count &= CL_SIZE - 1;
	cptr = &clist[cl_count];
	*cptr = c;
}

int
_unget_str (string)
register char *string;
{
	register char *ptr;

	if (*string == '\0')
		return;

	ptr = &string[strlen(string) - 1];

	while (ptr >= string)
	{
		_ungetc (*ptr--);
	}
}

static int
_delay_read (buffer, count)
register char *buffer;
register int count;
{
	register int len;
	unsigned char	old_VTIME;
	unsigned char	old_VMIN;
	extern struct termio    rttybuf;

	old_VTIME = rttybuf.c_cc[VTIME];
	rttybuf.c_cc[VTIME] = 1;
	old_VMIN = rttybuf.c_cc[VMIN];
	rttybuf.c_cc[VMIN] = 0;
	ioctl (0, TCXONC, 1);
	ioctl (0, TCSETA, &rttybuf);
	len = read (0, buffer, count);
	if (len < 0) len = 0;
	rttybuf.c_cc[VTIME] = old_VTIME;
	rttybuf.c_cc[VMIN] = old_VMIN;
	ioctl (0, TCSETA, &rttybuf);
	return (len);
}
