h25098
s 00002/00002/00221
d D 8.1 93/06/11 15:13:55 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00219
d D 7.2 92/10/11 12:45:40 bostic 2 1
c make kernel includes standard
e
s 00223/00000/00000
d D 7.1 92/07/13 00:43:47 torek 1 0
c date and time created 92/07/13 00:43:47 by torek
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to the Computer Systems
 * Engineering Group at Lawrence Berkeley Laboratory and to the University
 * of California at Berkeley by Jef Poskanzer.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * from: $Header: raster_text.c,v 1.15 92/06/17 08:14:45 torek Exp $
 */

/*
 * Text routines for raster library.
 */

#ifdef KERNEL
D 2
#include "sys/param.h"
#include "raster.h"
E 2
I 2
#include <sys/param.h>
#include <sparc/rcons/raster.h>
E 2
#ifdef COLORFONT_CACHE
D 2
#include "sys/malloc.h"
E 2
I 2
#include <sys/malloc.h>
E 2
#define NEW(size) malloc(size, M_DEVBUF, M_NOWAIT)
#endif
#else
#include <sys/types.h>
D 2
#include "raster.h"
E 2
I 2
#include <sparc/rcons/raster.h>
E 2
#ifdef COLORFONT_CACHE
#include <malloc.h>
#define NEW(size) malloc(size)
#endif
#endif


/* Draws text.  Returns 0 on success, -1 on failure. */
int
raster_text( r, x, y, rop, rf, text )
    register struct raster* r;
    int x, y;
    int rop;
    struct raster_font* rf;
    char* text;
    {
    return raster_textn( r, x, y, rop, rf, text, strlen( text ) );
    }

/* Draws n characters of text.  Returns 0 on success, -1 on failure. */
int
raster_textn( r, x, y, rop, rf, text, n )
    register struct raster* r;
    int x, y;
    int rop;
    struct raster_font* rf;
    char* text;
    int n;
    {
    int clip;
    int x1, y1;
    struct raster_char* c;
    struct raster* charrast;
    int i;
    register char ch;
    int thisx, thisy;
    int phase;

    /* Check whether we can avoid clipping. */
    clip = 0;
    if ( rf->flags & RASFONT_FIXEDWIDTH &&
	 rf->flags & RASFONT_NOVERTICALMOVEMENT )
	{
	/* This font is well-behaved, we can compute the extent cheaply. */
	c = &(rf->chars['@']);
	charrast = c->r;
	if ( x + c->homex < 0 || y + c->homey < 0 ||
	     x + c->homex + n * c->nextx > r->width ||
	     y + c->homey + charrast->height > r->height )
	    clip = 1;
	}
    else
	{
	/* Got to step through the string to compute the extent. */
	for ( i = 0, x1 = x, y1 = y;
	      i < n;
	      ++i, x1 += c->nextx, y1 += c->nexty )
	    {
	    c = &(rf->chars[text[i]]);
	    charrast = c->r;
	    if ( charrast != (struct raster*) 0 )
		{
		if ( x1 + c->homex < 0 || y1 + c->homey < 0 ||
		     x1 + c->homex + charrast->width > r->width ||
		     y1 + c->homey + charrast->height > r->height )
		    {
		    clip = 1;
		    break;
		    }
		}
	    }
	}

    /* Now display the text. */
    for ( i = 0, x1 = x, y1 = y;
	  i < n;
	  ++i, x1 += c->nextx, y1 += c->nexty )
	{
	ch = text[i];
	c = &(rf->chars[ch]);
	charrast = c->r;
	if ( charrast != (struct raster*) 0 )
	    {
	    thisx = x1 + c->homex;
	    thisy = y1 + c->homey;

	    phase = 0;
#ifdef COLORFONT_CACHE
	    if ( r->depth == 8 )
		{
		/* Initialize color font cache if necessary. */
		if ( rf->cache == (struct raster_fontcache*) -1 )
		    {
		    int c;

		    rf->cache = (struct raster_fontcache*)
			NEW( sizeof(struct raster_fontcache) );
		    if ( rf->cache != (struct raster_fontcache*) 0 )
			for ( c = 0; c < 256; ++c )
			    rf->cache->cr[c] = (struct raster*) 0;
		    }

		if ( rf->cache != (struct raster_fontcache*) 0 )
		    {
		    int color;
		    struct raster* cr;

		    color = RAS_GETCOLOR( rop );
		    cr = rf->cache->cr[ch];
		    /* Is this character cached yet? */
		    if ( cr != (struct raster*) 0 )
			{
			/* Yes, but is it the right color? */
			if ( rf->cache->color[ch] == color )
			    {
			    /* Yes - switch rasters. */
			    charrast = cr;
			    }
			else
			    {
			    /* No, re-draw it. */
			    if ( raster_op_noclip(
				 cr, 0, 0, charrast->width,
				 charrast->height, rop, charrast, 0, 0 ) == 0 )
				{
				rf->cache->color[ch] = color;
				charrast = cr;
				}
			    }
			}
		    else
			{
			/* It's not cached, so cache it. */
			cr = raster_alloc(
			    charrast->width, charrast->height, 8 );
			if ( cr != (struct raster*) 0 )
			    if ( raster_op_noclip(
				 cr, 0, 0, charrast->width, charrast->height,
				 rop, charrast, 0, 0 ) == 0 )
				{
				rf->cache->color[ch] = color;
				charrast = rf->cache->cr[ch] = cr;
				}
			}
		    }
		}
#endif /*COLORFONT_CACHE*/

	    if ( clip )
		{
		if ( raster_op(
			 r, thisx, thisy, charrast->width, charrast->height,
			 rop, charrast, phase, 0 ) < 0 )
		    return -1;
		}
	    else
		{
		if ( raster_op_noclip(
			 r, thisx, thisy, charrast->width, charrast->height,
			 rop, charrast, phase, 0 ) < 0 )
		    return -1;
		}
	    }
	}

    return 0;
    }

#ifdef COLORFONT_CACHE
/* Allocates a raster.  Returns (struct raster*) 0 on failure. */
struct raster*
raster_alloc( width, height, depth )
    int width, height, depth;
    {
    struct raster* r;
    int linelongs;

    if ( width <= 0 || height <= 0 || ( depth != 1 && depth != 8 ) )
	return (struct raster*) 0;
    linelongs = ( ( width * depth + 31 ) >> 5 );
    r = (struct raster*)
	NEW( sizeof(struct raster) + height * linelongs * sizeof(u_long));
    if ( r == (struct raster*) 0 )
	return (struct raster*) 0;

    r->width = width;
    r->height = height;
    r->depth = depth;
    r->linelongs = linelongs;
    r->pixels = (u_long*) (r + 1);
    r->data = (caddr_t) 0;
    return r;
    }
#endif
E 1
