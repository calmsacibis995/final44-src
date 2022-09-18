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

sputc(c)
register char c;
{
	char pbuf[2];

	if(c == '\n') *pbuf = VTNEWLINE;
	else *pbuf = c;
	pbuf[1] = 0;

	xputl(pbuf, 0);
}
