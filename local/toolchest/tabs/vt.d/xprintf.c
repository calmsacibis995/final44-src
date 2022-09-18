/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include <stdio.h>
#include "vt.h"

xprintf (string, a1, a2, a3, a4, a5, a6)
char   *string;
unsigned        a1;
{
	char    pbuf[256];
	register char  *ptr;

	sprintf (pbuf, string, a1, a2, a3, a4, a5, a6);

	for (ptr = pbuf; *ptr; ptr++)
	{
		if (*ptr == '\n')
			*ptr = VTNEWLINE;
	}

	xputl (pbuf, 0);
}

axprintf (attribute, string, a1, a2, a3, a4, a5, a6)
int attribute;
char   *string;
unsigned        a1;
{
	char    pbuf[256];
	register char  *ptr;

	sprintf (pbuf, string, a1, a2, a3, a4, a5, a6);

	for (ptr = pbuf; *ptr; ptr++)
	{
		if (*ptr == '\n')
			*ptr = VTNEWLINE;
	}

	xputl (pbuf, attribute);
}
