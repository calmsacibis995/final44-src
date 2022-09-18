/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char sccsid[] = "@(#)s_paus.c	5.2 (Berkeley) 4/12/91";
#endif /* not lint */

#include <stdio.h>
#define PAUSESIG 15

s_paus(s, n)
char *s;
long int n;
{
int i;
int waitpause();

fprintf(stderr, "PAUSE: ");
if(n > 0)
	{
	for(i = 0; i<n ; ++i)
		putc(*s++, stderr);
	putc('\n', stderr);
	}
if( isatty(fileno(stdin)) )
	{
	fprintf(stderr, "To resume execution, type:   go\nAny other input will terminate the program.\n");
	if( getchar()!='g' || getchar()!='o' || getchar()!='\n' )
		{
		fprintf(stderr, "STOP\n");
		f_exit();
		_cleanup();
		exit(0);
		}
	}
else
	{
	fprintf(stderr, "To resume execution, type:    kill -%d %d\n",
		PAUSESIG, getpid() );
	signal(PAUSESIG, waitpause);
	pause();
	}
fprintf(stderr, "Execution resumed after PAUSE.\n");
}





static waitpause()
{
return;
}
