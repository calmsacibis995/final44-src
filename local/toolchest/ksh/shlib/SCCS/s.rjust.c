h58270
s 00094/00000/00000
d D 1.1 88/07/21 17:35:49 marc 1 0
c date and time created 88/07/21 17:35:49 by marc
e
u
U
t
T
I 1
/*

 *      Copyright (c) 1984, 1985, 1986 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/* %W% */

/*
 *   RJUST.C
 *
 *   Programmer:  D. G. Korn
 *
 *        Owner:  D. A. Lambeth
 *
 *         Date:  April 17, 1980
 *
 *
 *
 *   RJUST (STR, SIZE, FILL)
 *
 *      Right-justify STR so that it contains no more than 
 *      SIZE non-blank characters.  If necessary, pad with
 *      the character FILL.
 *
 *
 *
 *   See Also:  
 */

#ifdef KSHELL
#include	"shtype.h"
#else
#include	<ctype.h>
#endif	/* KSHELL */

/*
 *   RJUST (STR, SIZE, FILL)
 *
 *        char *STR;
 *
 *        int SIZE;
 *
 *        char FILL;
 *
 *   Right-justify STR so that it contains no more than
 *   SIZE characters.  If STR contains fewer than SIZE
 *   characters, left-pad with FILL.  Trailing blanks
 *   in STR will be ignored.
 *
 *   If the leftmost digit in STR is not a digit, FILL
 *   will default to a blank.
 */

void	rjust(str,size,fill)
char *str,fill;
int size;
{
	register int n;
	register char *cp,*sp;
	n = strlen(str);

	/* ignore trailing blanks */

	for(cp=str+n;n && *--cp == ' ';n--);
	if (n == size) return;
	if(n > size)
        {
        	*(str+n) = 0;
        	for (sp = str, cp = str+n-size; sp <= str+size; *sp++ = *cp++);
        	return;
        }
	else *(sp = str+size) = 0;
	if (n == 0)  
        {
        	while (sp > str)
               		*--sp = ' ';
        	return;
        }
	while(n--)
		*--sp = *cp--;
	if(!isdigit(*str))
		fill = ' ';
	while(sp>str)
		*--sp = fill;
	return;
}

E 1
