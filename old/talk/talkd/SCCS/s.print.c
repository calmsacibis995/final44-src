h47995
s 00005/00004/00034
d D 5.3 94/04/02 15:23:56 bostic 3 2
c put redistributable notice on it, I'm putting it in 4.4BSD-Lite
e
s 00001/00001/00037
d D 5.2 92/10/17 13:26:51 bostic 2 1
c TWO BUGS (printf doesn't take a FILE *, plus wrong arg to gettimeofday)
c lint to make cc shut up
e
s 00038/00000/00000
d D 5.1 92/10/17 13:25:48 bostic 1 0
c date and time created 92/10/17 13:25:48 by bostic
e
u
U
t
T
I 1
D 3
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
 * Copyright (c) 1983, 1985
 *	The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.c%
E 3
 */

#ifndef lint
static char sccsid[] = "@(#)print.c	5.1 (Berkeley) 6/6/85";
#endif not lint

/* debug print routines */

#include <stdio.h>
#include "ctl.h"

print_request(request)
	CTL_MSG *request;
{
    	extern FILE *debugout;
	
	fprintf(debugout
		, "type is %d, l_user %s, r_user %s, r_tty %s\n"
		, request->type, request->l_name, request->r_name
		, request->r_tty);
	fprintf(debugout, "		id = %d\n", request->id_num);
	fflush(debugout);
}

print_response(response)
	CTL_RESPONSE *response;
{
    	extern FILE *debugout;
	
D 2
	printf(debugout
E 2
I 2
	fprintf(debugout
E 2
		, "type is %d, answer is %d, id = %d\n\n", response->type
		, response->answer, response->id_num);
	fflush(debugout);
}
E 1
