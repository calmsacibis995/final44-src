h18170
s 00006/00002/00095
d D 4.2 91/04/18 16:41:07 bostic 2 1
c new copyright; att/bsd/shared
e
s 00097/00000/00000
d D 4.1 83/05/06 23:47:37 tut 1 0
c date and time created 83/05/06 23:47:37 by tut
e
u
U
t
T
I 2
/*-
 * %sccs.include.proprietary.c%
 */

E 2
I 1
#ifndef lint
D 2
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

#include <stdio.h>

extern char *comname;	/* "/usr/lib/eign" */
int wholefile = 0;
int keycount = 100;
int labels = 1;
int minlen = 3;
extern int comcount;
char *iglist = "XYZ#";

main (argc,argv)
char *argv[];
{
	/* this program expects as its arguments a list of
	 * files and generates a set of lines of the form
	 *	filename:byte-add,length (tab) key1 key2 key3
	 * where the byte addresses give the position within
	 * the file and the keys are the strings off the lines
	 * which are alphabetic, first six characters only.
	 */

	int i;
	char *name, qn[200];
	char *inlist = 0;

	FILE *f, *ff;

	while (argc>1 && argv[1][0] == '-')
	{
		switch(argv[1][1])
		{
		case 'c':
			comname = argv[2];
			argv++; 
			argc--;
			break;
		case 'w':
			wholefile = 1;  
			break;
		case 'f':
			inlist = argv[2];
			argv++; 
			argc--;
			break;
		case 'i':
			iglist = argv[2];
			argv++; 
			argc--;
			break;
		case 'l':
			minlen = atoi(argv[1]+2);
			if (minlen<=0) minlen=3;
			break;
		case 'n': /* number of common words to use */
			comcount = atoi(argv[1]+2);
			break;
		case 'k': /* number  of keys per file max */
			keycount = atoi(argv[1]+2);
			break;
		case 's': /* suppress labels, search only */
			labels = 0;
			break;
		}
		argc--; 
		argv++;
	}
	if (inlist)
	{
		ff = fopen(inlist, "r");
		while (fgets(qn, 200, ff))
		{
			trimnl(qn);
			f = fopen (qn, "r");
			if (f!=NULL)
				dofile(f, qn);
			else
				fprintf(stderr, "Can't read %s\n",qn);
		}
	}
	else
		if (argc<=1)
			dofile(stdin, "");
		else
			for(i=1; i<argc; i++)
			{
				f = fopen(name=argv[i], "r");
				if (f==NULL)
					err("No file %s",name);
				else
					dofile(f, name);
			}
	exit(0);
}
E 1
