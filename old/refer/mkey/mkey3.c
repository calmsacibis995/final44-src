/*-
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char sccsid[] = "@(#)mkey3.c	4.3 (Berkeley) 4/18/91";
#endif /* not lint */

#include <stdio.h>
#include "pathnames.h"

#define COMNUM 500
#define COMTSIZE 997

char *comname = _PATH_EIGN;
static int cgate = 0;
extern char *comname;
int comcount = 100;
static char cbuf[COMNUM*9];
static char *cwds[COMTSIZE];
static char *cbp;

common (s)
char *s;
{
	if (cgate==0) cominit();
	return (c_look(s, 1));
}

cominit()
{
	int i;
	FILE *f;
	cgate=1;
	f = fopen(comname, "r");
	if (f==NULL) return;
	cbp=cbuf;
	for(i=0; i<comcount; i++)
	{
		if (fgets(cbp, 15, f)==NULL)
			break;
		trimnl(cbp);
		c_look (cbp, 0);
		while (*cbp++);
	}
	fclose(f);
}

c_look (s, fl)
char *s;
{
	int h;
	h = hash(s) % (COMTSIZE);
	while (cwds[h] != 0)
	{
		if (strcmp(s, cwds[h])==0)
			return(1);
		h = (h+1) % (COMTSIZE);
	}
	if (fl==0)
		cwds[h] = s;
	return(0);
}
