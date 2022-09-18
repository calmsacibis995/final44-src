/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char sccsid[] = "@(#)c_sfe.c	5.4 (Berkeley) 4/12/91";
#endif /* not lint */

/*
 * sequential formatted external I/O - common read & write routines
 */

#include "fio.h"

c_sfe(a,flg,mode,str) cilist *a; char *str; /* check */
{	unit *p;
	int n;

	external=YES;
	formatted=FORMATTED;
	fmtbuf=a->cifmt;
	lfname = NULL;
	elist = NO;
	errflag = a->cierr;
	endflag = a->ciend;
	lunit = a->ciunit;
	if(not_legal(lunit)) err(errflag,F_ERUNIT,str);
	curunit = p = &units[lunit];
	if(!p->ufd && (n=fk_open(flg,mode,FMT,(ftnint)lunit)) )
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
