h28475
s 00006/00002/00057
d D 4.3 91/04/18 16:41:08 bostic 3 2
c new copyright; att/bsd/shared
e
s 00003/00001/00056
d D 4.2 89/05/11 10:04:49 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00057/00000/00000
d D 4.1 83/05/06 23:47:41 tut 1 0
c date and time created 83/05/06 23:47:41 by tut
e
u
U
t
T
I 3
/*-
 * %sccs.include.proprietary.c%
 */

E 3
I 1
#ifndef lint
D 3
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

#include <stdio.h>
I 2
#include "pathnames.h"

E 2
#define COMNUM 500
#define COMTSIZE 997

D 2
char *comname = "/usr/lib/eign";
E 2
I 2
char *comname = _PATH_EIGN;
E 2
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
E 1
