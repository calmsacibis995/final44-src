h50635
s 00002/00002/00041
d D 8.1 93/05/31 16:04:55 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00000/00028
d D 5.2 90/04/30 21:24:13 bostic 2 1
c Berkeley headers, SCCS id's
e
s 00028/00000/00000
d D 5.1 90/04/30 21:00:33 bostic 1 0
c date and time created 90/04/30 21:00:33 by bostic
e
u
U
t
T
I 1
%{
I 2
/*-
D 3
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Ed James.
 *
 * %sccs.include.redist.c%
 */

E 2
/*
 * Copyright (c) 1987 by Ed James, UC Berkeley.  All rights reserved.
 *
 * Copy permission is hereby granted provided that this notice is
 * retained on all partial or complete copies.
 *
 * For more info on this and all of my stuff, mail edjames@berkeley.edu.
 */

I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 2
#include "y.tab.h"
extern int	line;
I 2

E 2
%}
%%
[0-9]+			{ yylval.ival = atoi(yytext);  return(ConstOp); }
height			{ return(HeightOp); }
width			{ return(WidthOp); }
newplane		{ return(NewplaneOp); }
update			{ return(UpdateOp); }
airport			{ return(AirportOp); }
line			{ return(LineOp); }
exit			{ return(ExitOp); }
beacon			{ return(BeaconOp); }
[wedcxzaq]		{ yylval.cval = *yytext; return (DirOp); }
[ \t]+			{ }
#[^\n]*\n		{ line++; }
\n			{ line++; }
.			{ return *yytext; }
E 1
