h23538
s 00006/00002/00081
d D 4.5 91/04/18 16:39:02 bostic 5 4
c new copyright; att/bsd/shared
e
s 00002/00001/00081
d D 4.4 89/05/11 10:04:42 bostic 4 3
c file reorg, pathnames.h, paths.h
e
s 00001/00001/00081
d D 4.3 87/05/04 16:16:29 bostic 3 2
c bug report 4.2BSD/bin/169
e
s 00000/00001/00082
d D 4.2 83/06/23 14:20:35 garrison 2 1
c Removed extraneous fclose
e
s 00083/00000/00000
d D 4.1 83/05/06 23:47:24 tut 1 0
c date and time created 83/05/06 23:47:24 by tut
e
u
U
t
T
I 5
/*-
 * %sccs.include.proprietary.c%
 */

E 5
I 1
#ifndef lint
D 5
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

#include <stdio.h>
#include <assert.h>
I 4
#include "pathnames.h"
E 4
#define unopen(fil) {if (fil!=NULL) {fclose(fil); fil=NULL;}}

extern long indexdate, gdate();
extern FILE *iopen();
runbib (s)
char *s;
{
	/* make a file suitable for fgrep */
	char tmp[200];
D 3
	sprintf(tmp, "/usr/lib/refer/mkey %s >%s.ig", s,s);
E 3
I 3
D 4
	sprintf(tmp, "/usr/lib/refer/mkey '%s' > '%s.ig'", s,s);
E 4
I 4
	sprintf(tmp, "%s '%s' > '%s.ig'", _PATH_MKEY,s,s);
E 4
E 3
	system(tmp);
}

makefgrep(indexname)
char *indexname;
{
	FILE *fa, *fb;
	if (ckexist(indexname, ".ig"))
	{
		/* existing gfrep -type index */
# if D1
		fprintf(stderr, "found fgrep\n");
# endif
		fa = iopen(indexname, ".ig");
		fb = iopen(indexname, "");
		if (gdate(fb)>gdate(fa))
		{
			if (fa!=NULL)
				fclose(fa);
			runbib(indexname);
			fa= iopen(indexname, ".ig");
		}
		indexdate = gdate(fa);
		unopen(fa); 
		unopen(fb);
	}
	else
		if (ckexist(indexname, ""))
		{
			/* make fgrep */
# if D1
			fprintf(stderr, "make fgrep\n");
# endif
			runbib(indexname);
			time(&indexdate);
D 2
			unopen(fb);
E 2
		}
		else /* failure */
		return(0);
	return(1); /* success */
}

ckexist(s, t)
char *s, *t;
{
	char fnam[100];
	strcpy (fnam, s);
	strcat (fnam, t);
	return (access(fnam, 04) != -1);
}

FILE *
iopen(s, t)
char *s, *t;
{
	char fnam[100];
	FILE *f;
	strcpy (fnam, s);
	strcat (fnam, t);
	f = fopen (fnam, "r");
	if (f == NULL)
	{
		err("Missing expected file %s", fnam);
		exit(1);
	}
	return(f);
}
E 1
