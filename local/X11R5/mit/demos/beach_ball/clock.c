/* $XConsortium: clock.c,v 5.1 91/02/16 09:32:49 rws Exp $ */

/***********************************************************
Copyright 1989,1990, 1991 by Sun Microsystems, Inc. and the X Consortium.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Sun Microsystems,
the X Consortium, and MIT not be used in advertising or publicity 
pertaining to distribution of the software without specific, written 
prior permission.  

SUN MICROSYSTEMS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, 
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT 
SHALL SUN MICROSYSTEMS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL 
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

/*
 * Copyright (c) 1989,1990, 1991 by M.I.T. and Sun Microsystems, Inc.
 */

#include <stdio.h>
#include <sys/time.h>

static int    clock_tick_count;
static struct timeval clock_start;

void
clock_reset()
{
    clock_tick_count = 0;
    gettimeofday(&clock_start, NULL);
}

void
clock_tick()
{
    struct timeval clock_stop;
    int    t;
    double f, diff;

    clock_tick_count++;
    if( !(clock_tick_count % 10) ) {
        gettimeofday(&clock_stop, NULL);
        t  = ( clock_stop.tv_usec - clock_start.tv_usec ) / 1000;
        t += ( (int)(clock_stop.tv_sec - clock_start.tv_sec) ) * 1000;
        f = t;
        diff = f/1000;
        printf("time for 10 frames %7.3fsec\n", diff);
        clock_reset();
    }
}
