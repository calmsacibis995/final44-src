/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	input.c,v $
 * Revision 2.4  89/03/09  21:34:24  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:40:35  gm0w
 * 	Changes for cleanup.
 * 
 * 08-Feb-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Removed else leg of KERNEL conditionals and fixed 
 *	includes as part of kernel cleanup.
 *
 * 29-Jan-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Conditionalized kdb code under KERNEL in order to make
 *	kdb part of the kernel rather than a separate library.
 *
 *  5-Sep-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Converted into kernel debugger, "kdb".
 *
 */
#ifndef	lint
static	char sccsid[] = "@(#)input.c 1.1 86/02/03 SMI";
#endif
/*
 * adb - input routines
 */

#include <sun3/kdb/adb.h>

char	line[BUFSIZ];
int	infile;
int	eof;
char	lastc = '\n';

eol(c)
	char c;
{

	return (c == '\n' || c == ';');
}

rdc()
{

	do
		(void) readchar();
	while (lastc == ' ' || lastc == '\t');
	return (lastc);
}

char erasec[] = {'\b', ' ', '\b'};

char *
editchar(line, lp)
char *line;
register char *lp;
{
    switch (*lp)
    {
	case 0177:
	case 'H'&077:
	    if (lp > line)
	    {
		write(1, erasec, sizeof(erasec));
		lp--;
	    }
	    break;
	case 'U'&077:
	    while (lp > line)
	    {
		write(1, erasec, sizeof(erasec));
		lp--;
	    }
	    break;
	case 'R'&077:
	    write(1, "^R\n", 3);
	    if (lp > line)
		write(1, line, lp-line);
	    break;
	default:
	    return(++lp);
    }
    return(lp);
}

readchar()
{

	if (eof) {
		lastc = 0;
		return (0);
	}
	if (lp == 0) {
		lp = line;
		do {
			eof = read(infile, lp, 1) <= 0;
			if (interrupted)
				error((char *)0);
			lp = editchar(line, lp);
		} while (eof == 0 && (lp == line || lp[-1] != '\n'));
		*lp = 0;
		lp = line;
	}
	if (lastc = peekc)
		peekc = 0;
	else
		if (lastc = *lp)
			lp++;
	return (lastc);
}

nextchar()
{

	if (eol(rdc())) {
		lp--;
		return (0);
	}
	return (lastc);
}

quotchar()
{

	if (readchar() == '\\')
		return (readchar());
	if (lastc=='\'')
		return (0);
	return (lastc);
}

getformat(deformat)
	char *deformat;
{
	register char *fptr = deformat;
	register int quote = 0;

	while (quote ? readchar() != '\n' : !eol(readchar()))
		if ((*fptr++ = lastc)=='"')
			quote = ~quote;
	lp--;
	if (fptr != deformat)
		*fptr++ = '\0';
}
