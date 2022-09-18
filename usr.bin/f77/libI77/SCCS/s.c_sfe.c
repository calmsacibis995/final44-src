h62441
s 00008/00005/00066
d D 5.4 91/04/12 15:23:06 bostic 5 4
c new copyright; att/bsd/shared
e
s 00002/00002/00069
d D 5.3 90/02/25 19:15:50 donn 4 3
c For GCC's (and ANSI's) sake, don't name a formal parameter after a typedef.
e
s 00002/00001/00069
d D 5.2 85/07/30 16:30:58 jerry 3 2
c sequential & external should always be set to YES or NO.
e
s 00007/00001/00063
d D 5.1 85/06/07 23:41:49 kre 2 1
c Add copyright
e
s 00064/00000/00000
d D 1.1 85/05/21 20:08:48 libs 1 0
c date and time created 85/05/21 20:08:48 by libs
e
u
U
t
T
I 1
D 5
/*
D 2
char id_csfe[] = "%W%";
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
 * sequential formatted external I/O - common read & write routines
 */

#include "fio.h"

D 4
c_sfe(a,flag,mode,str) cilist *a; char *str; /* check */
E 4
I 4
c_sfe(a,flg,mode,str) cilist *a; char *str; /* check */
E 4
{	unit *p;
	int n;

D 3
	external=formatted=FORMATTED;
E 3
I 3
	external=YES;
	formatted=FORMATTED;
E 3
	fmtbuf=a->cifmt;
	lfname = NULL;
	elist = NO;
	errflag = a->cierr;
	endflag = a->ciend;
	lunit = a->ciunit;
	if(not_legal(lunit)) err(errflag,F_ERUNIT,str);
	curunit = p = &units[lunit];
D 4
	if(!p->ufd && (n=fk_open(flag,mode,FMT,(ftnint)lunit)) )
E 4
I 4
	if(!p->ufd && (n=fk_open(flg,mode,FMT,(ftnint)lunit)) )
E 4
		err(errflag,n,str)
	cf = curunit->ufd;
	elist = YES;
	lfname = curunit->ufnm;
	if(!p->ufmt) err(errflag,F_ERNOFIO,str)
	cursor=recpos=scale=reclen=0;
	radix = 10;
	signit = YES;
	cblank = curunit->ublnk;
	cplus = NO;
	return(OK);
}

x_tab()
{	int n;
	if(reclen < recpos) reclen = recpos;
	if(curunit->useek)
	{	if((recpos+cursor) < 0) cursor = -recpos;	/* to BOR */
		n = reclen - recpos;	/* distance to eor, n>=0 */
		if((cursor-n) > 0)
		{	fseek(cf,(long)n,1);  /* find current eor */
			recpos = reclen;
			cursor -= n;
		}
		else
		{	fseek(cf,(long)cursor,1);  /* do not pass go */
			recpos += cursor;
			return(cursor=0);
		}
	}
	else
		if(cursor < 0) return(F_ERSEEK);   /* can't go back */
	while(cursor--)
	{	if(reading)
		{	n = (*getn)();
			if(n=='\n') return(cursor=0);	/* be tolerant */
			if(n==EOF) return(EOF);
		}
		else	(*putn)(' ');	/* fill in the empty record */
	}
	return(cursor=0);
}
E 1
