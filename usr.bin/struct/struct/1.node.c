/*-
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char sccsid[] = "@(#)1.node.c	8.1 (Berkeley) 6/6/93";
#endif /* not lint */

#include <stdio.h>
#include "def.h"
#include "1.incl.h"

makenode(type,addimp,addcom, labe,arcnum,arctype,arclab)
LOGICAL addimp,addcom;
int type, arctype[], arcnum;
long arclab[], labe;
	{
	int i;
	VERT num;
	
	ASSERT(arcsper[type] < 0 || arcnum == arcsper[type], makenode);
	num = create(type,arcnum);
	
	if (addimp)  fiximp(num,labe);
	
	for (i = 0; i < arcnum; ++i)
		{
		if (arctype[i] == -2)
			addref(arclab[i],&ARC(num,i));
		else
			ARC(num,i) = arctype[i];
		}
	
	
	if (hascom[type] )
		{
		if (!addcom || endcom < begline)
			BEGCOM(num) = UNDEFINED;
		else
			BEGCOM(num) = begchar - rtnbeg;
		}
	return(num);
	}





fiximp(num,labe)		/* fix implicit links, check nesting */
VERT num;
long labe;
	{
	fixvalue(implicit, num);		/* set implicit links to this node */
	clear(implicit);
	if(labe != implicit) fixvalue(labe, num);
	}
