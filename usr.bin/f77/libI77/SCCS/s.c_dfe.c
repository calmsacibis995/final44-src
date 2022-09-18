h01526
s 00008/00005/00064
d D 5.4 91/04/12 15:23:04 bostic 5 4
c new copyright; att/bsd/shared
e
s 00002/00002/00067
d D 5.3 90/02/25 19:15:51 donn 4 3
c For GCC's (and ANSI's) sake, don't name a formal parameter after a typedef.
e
s 00002/00001/00067
d D 5.2 85/07/30 16:31:03 jerry 3 2
c sequential & external should always be set to YES or NO.
e
s 00007/00001/00061
d D 5.1 85/06/07 23:40:27 kre 2 1
c Add copyright
e
s 00062/00000/00000
d D 1.1 85/05/21 20:08:54 libs 1 0
c date and time created 85/05/21 20:08:54 by libs
e
u
U
t
T
I 1
D 5
/*
D 2
char id_c_dfe[] = "%W%";
E 2
I 2
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 5
E 2
 *
I 2
D 5
 *	%W%	%G%
E 5
I 5
 * %sccs.include.proprietary.c%
E 5
 */
I 5

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

/*
E 2
 * direct formatted external i/o - common read/write routines
 */

#include "fio.h"

D 4
c_dfe(a,flag,str) cilist *a; char *str;
E 4
I 4
c_dfe(a,flg,str) cilist *a; char *str;
E 4
{	int n;
	sequential = NO;
D 3
	external = formatted = FORMATTED;
E 3
I 3
	external = YES;
	formatted = FORMATTED;
E 3
	lfname = NULL;
	elist = NO;
	cursor=scale=recpos=reclen=0;
	radix = 10;
	signit = YES;
	fmtbuf = a->cifmt;
	errflag = a->cierr;
	endflag = a->ciend;
	lunit = a->ciunit;
	if(not_legal(lunit)) err(errflag,F_ERUNIT,str);
	curunit = &units[lunit];
D 4
	if(!curunit->ufd && (n=fk_open(flag,DIR,FMT,(ftnint)lunit)))
E 4
I 4
	if(!curunit->ufd && (n=fk_open(flg,DIR,FMT,(ftnint)lunit)))
E 4
		err(errflag,n,str)
	cf = curunit->ufd;
	elist = YES;
	lfname = curunit->ufnm;
	if(!curunit->ufmt) err(errflag,F_ERNOFIO,str)
	if(!curunit->useek || !curunit->url) err(errflag,F_ERNODIO,str)
	recnum = a->cirec - 1;
	fseek(cf, (long)curunit->url * recnum, 0);
	cblank = curunit->ublnk;
	cplus = NO;
	return(OK);
}

y_tab()
{	int n;
	if(curunit->url==1)
	{
		if(cursor < 0 && -cursor > ftell(cf)) rewind(cf);
		else	fseek(cf,(long)cursor,1);
		return(cursor=0);
	}
	else
	{	if(reclen < recpos) reclen = recpos;
		if((recpos + cursor) < 0) cursor = -recpos;	/* BOR */
		n = reclen - recpos;		/* n >= 0 */
		if(!reading && (cursor-n) > 0)
		{	recpos = reclen;
			cursor -= n;
			fseek(cf,(long)n,1);
			while(cursor--) if(n=(*putn)(' ')) return(n);
			return(cursor=0);
		}
		recpos += cursor;
		if(recpos >= curunit->url) err(errflag,F_EREREC,"dfe")
	}
	fseek(cf,(long)cursor,1);
	return(cursor=0);
}
E 1
