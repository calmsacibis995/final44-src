h61562
s 00008/00005/00058
d D 5.2 91/04/12 15:23:35 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00056
d D 5.1 85/06/07 23:57:21 kre 2 1
c Add copyright
e
s 00057/00000/00000
d D 1.1 85/05/21 20:09:02 libs 1 0
c date and time created 85/05/21 20:09:02 by libs
e
u
U
t
T
I 1
D 3
/*
D 2
char id_wdfe[] = "%W%";
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
E 2
 *
I 2
D 3
 *	%W%	%G%
E 3
I 3
 * %sccs.include.proprietary.c%
E 3
 */
I 3

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

/*
E 2
 * write direct formatted external i/o
 */

#include "fio.h"

extern int w_ed(),w_ned();
int y_putc(),y_wnew(),y_tab();

LOCAL char wdfe[] = "write dfe";

s_wdfe(a) cilist *a;
{
	int n;
	reading = NO;
	if(n=c_dfe(a,WRITE,wdfe)) return(n);
	curunit->uend = NO;
	if(!curunit->uwrt && ! nowwriting(curunit)) err(errflag, errno, wdfe)
	putn = y_putc;
	doed = w_ed;
	doned = w_ned;
	dotab = y_tab;
	dorevert = doend = donewrec = y_wnew;
	if(pars_f()) err(errflag,F_ERFMT,wdfe)
	fmt_bg();
	return(OK);
}

e_wdfe()
{
	en_fio();
	return(OK);
}

LOCAL
y_putc(c)
{
	if(curunit->url!=1 && recpos++ >= curunit->url) err(errflag,F_EREREC,wdfe)
	putc(c,cf);
	return(OK);
}

LOCAL
y_wnew()
{	if(curunit->url != 1)
	{	if(reclen > recpos)
		{	fseek(cf,(long)(reclen-recpos),1);
			recpos = reclen;
		}
		while(recpos < curunit->url) (*putn)(' ');
		recnum++;
		recpos = reclen = cursor = 0;
	}
	return(OK);
}
E 1
