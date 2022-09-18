/*-
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char sccsid[] = "@(#)hunt5.c	4.4 (Berkeley) 4/18/91";
#endif /* not lint */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char *soutput, *tagout, usedir[];

result(master, nf, fc)
unsigned *master;
FILE *fc;
{
	int i, c;
	char *s;
	long lp;
	extern int iflong;
	char res[100];
	union ptr {
		unsigned *a; 
		long *b;
	} umaster;

	if (iflong)
		umaster.b = (long *) master;
	else
		umaster.a = master;
	for(i=0; i<nf; i++)
	{
		lp = iflong ? umaster.b[i] : umaster.a[i];
		fseek(fc,lp, 0);
		fgets(res, 100, fc);
		for(s=res; c = *s; s++)
			if (c== ';')
			{
				*s=0;
				break;
			}
		if (tagout !=0)
		{
			if (res[0]=='/' || usedir[0]==0)
				sprintf(tagout, "%s", res);
			else
				sprintf(tagout, "%s/%s", usedir, res);
			while (*tagout) tagout++;
		}
		else
		{
			if (res[0]!='/' || usedir[0]==0)
				printf("%s/", usedir);
			printf("%s\n", res);
		}
	}
}

long
gdate(f)
FILE *f;
{
	struct stat sb;
	fstat (f->_file, &sb);
	return  (sb . st_mtime);
}
