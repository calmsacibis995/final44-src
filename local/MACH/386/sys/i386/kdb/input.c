/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	input.c,v $
 * Revision 1.4.1.1  90/01/08  13:27:44  rvb
 * 	Code cleanup -- flush dead code.
 * 	[90/01/08            rvb]
 * 
 * Revision 1.4  89/03/09  20:00:50  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/27  21:32:45  mrt
 * 	We will minimally sanitize this kdb till something better comes
 * 	along.
 * 	[89/02/27            rvb]
 * 
 */

/*
 *
 *	UNIX debugger
 *
 */

#include "defs.h"

INT		mkfault;
char		line[LINSIZ];
INT		infile;
char		*lp;
char		peekc,lastc = EOR;
INT		eof;

/* input routines */

eol(c)
char	c;
{
	return(c==EOR || c==';');
}

rdc()
{
	do {
		readchar();
	}
	while( lastc==' ' || lastc=='\t' );
	return(lastc);
}

char erasec[] = {
	' ', '\b'};

char *
editchar(_line_, _lp_)
char *_line_;
register char *_lp_;
{
	switch (*_lp_)
	{
	case 0177:
	case 'H'&077:
		if (_lp_ > _line_)
		{
			write(1, erasec, sizeof(erasec));
			_lp_--;
		}
		break;
	case 'U'&077:
		while (_lp_ > _line_)
		{
			write(1, erasec, sizeof(erasec));
			_lp_--;
		}
		break;
	case 'R'&077:
		write(1, "^R\n", 3);
		if (_lp_ > _line_)
			write(1, _line_, _lp_-_line_);
		break;
	default:
		return(++_lp_);
	}
	return(_lp_);
}

readchar()
{
	if ( eof ) {
		lastc=0;
	} 
	else {
		if ( lp==0 ) {
			lp=line;
			do {
				eof = read(infile,lp,1)==0;
				if ( mkfault ) {
					error(0);
				}
				lp = editchar(line, lp);
			}
			while( eof==0 && (lp == line || lp[-1]!=EOR) ) ;
			*lp=0;
			lp=line;
		}
		if ( lastc = peekc ) {
			peekc=0;
		} else if ( lastc = *lp ) {
			lp++;
		}
	}
	return(lastc);
}

nextchar()
{
	if ( eol(rdc()) ) {
		lp--;
		return(0);
	} else {
		return(lastc);
	}
}

quotchar()
{
	if ( readchar()=='\\' ) {
		return(readchar());
	} else if ( lastc=='\'' ) {
		return(0);
	} else {
		return(lastc);
	}
}

getformat(deformat)
string_t		deformat;
{
	register string_t	fptr;
	register BOOL	quote;
	fptr=deformat;
	quote=FALSE;
	while ( (quote ? readchar()!=EOR : !eol(readchar())) ) {
		if ( (*fptr++ = lastc)=='"' ) {
			quote = ~quote;
		}
	}
	lp--;
	if ( fptr!=deformat ) {
		*fptr++ = '\0';
	}
}
