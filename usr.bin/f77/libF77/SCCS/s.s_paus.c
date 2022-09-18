h44500
s 00008/00006/00049
d D 5.2 91/04/12 15:00:14 bostic 3 2
c new copyright; att/bsd/shared
e
s 00005/00001/00050
d D 5.1 85/06/07 22:35:30 kre 2 1
c Add copyright
e
s 00051/00000/00000
d D 1.1 83/01/21 11:19:01 dlw 1 0
c date and time created 83/01/21 11:19:01 by dlw
e
u
U
t
T
I 1
D 3
/*
D 2
 *	"%W%"
E 2
I 2
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 3
 *
D 3
 *	%W%	%G%
E 3
I 3
 * %sccs.include.proprietary.c%
E 3
E 2
 */

I 3
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 3
#include <stdio.h>
#define PAUSESIG 15
D 3

E 3

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
E 1
