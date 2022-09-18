#ifndef lint
static char sccsid[] = "@(#)peoplesort.c	1.4 (UKC) 6/6/87";
#endif  lint
/***

* program name:
	peoplesort.c
* function:
	Sorts the people database into name order and outputs
	it to standard output
* switches:
	-f peoplefile
	none
* libraries used:
	standard dbase.o
* compile time parameters:
	cc -o peoplesort -O peoplesort.c
* history:
	Written June 1987 Peter Collinson UKC

***/
#include <stdio.h>
#include <ctype.h>
#include "people.h"

char	*progname;
/*
 *	Structure used for sorting
 */
 
struct sortrec
{	long	pos;	/* position in the file of the record */
	char	*name;	/* name to be sorted */
	char	*last;	/* pointer to last element of the name line */
};

typedef struct sortrec Sortrec;

Sortrec	*sbase;
int	maxsr;
int	srinx;
#define SRCHUNK	500

char	usage[] = "Usage: peoplesort [-f peoplefile]\n";

char	*strstore();

main(argc, argv)
int	argc;
char	*argv[];
{	extern FILE *file;
	register char *pt;
	char	*fname;

	progname = rindex(argv[0], '/');
	if (progname)
		progname++;
	else	progname = argv[0];

	fname = NULL;
	if (argc > 1)
	{	argv++;
		if (**argv != '-')
			fatal(usage);
		pt = *argv;
		if (pt[1] != 'f')
			fatal(usage);
		if (pt[2])
			fname = pt + 2;
		else
		{	argv++;
			argc--;
			fname = *argv;
		}
	}
		
	openmaster(fname, 1);		/* Don't use dbm */
	
	while (nextrecord() == FOUND)
		stash();
	clearerr(file);
	rewind(file);
	sort_recs();
/*
	dumpsr();
 */
	dump();
	exit(0);
}

/*
 *	Store the data from the current record
 */
stash()
{	register Li *lp;
	extern	long sorpos;
	
	lp = search((Li *)0, "name");
	if (lp)
		store_sr(sorpos, lp->data);
}

/*
 *	Store a sortrec
 */
store_sr(pos, nm)
long pos;
char *nm;
{	Sortrec *sp;

	if (sbase == (Sortrec *)0)
	{	sbase = (Sortrec *)malloc(SRCHUNK*sizeof (Sortrec));
		if (sbase == (Sortrec *)0)
			fatal("No memory for sort record\n");
		srinx = 0;
		maxsr = SRCHUNK;
	}
	if (srinx >= maxsr)
	{	sbase = (Sortrec *)realloc((char *)sbase, 
			(maxsr+SRCHUNK)*sizeof (Sortrec));
		if (sbase == (Sortrec *)0)
			fatal("No memory for sort record\n");
		maxsr += SRCHUNK;
	}
	sp = &sbase[srinx++];
	sp->pos = pos;
	sp->name = strstore(nm);
	sp->last = rindex(sp->name, ' ');
	if (sp->last)
		sp->last++;
	else	sp->last = sp->name;
}

sort_recs()
{	extern	sr_sort();

	qsort(sbase, srinx, sizeof (Sortrec), sr_sort);
	
}

sr_sort(a, b)
register Sortrec *a, *b;
{	register rv;

	if (*a->last < *b->last)
		return (-1);
	if (*a->last > *b->last)
		return (1);
	rv = strcmp(a->last, b->last);
	if (rv == 0)
		rv = strcmp(a->name, b->name);
	return(rv);
}

dumpsr()
{	register i;

	for (i = 0; i < srinx; i++)
		printf("%d: %s\n", sbase[i].pos, sbase[i].name);
}

dump()
{	register Sortrec *sp;
	extern FILE *file;

	for (sp = sbase; sp < sbase + srinx; sp++)
	{	fseek(file, sp->pos, 0);
		if (nextrecord() != FOUND)
			fatal("Input data botch\n");
		dumprec();
	}
}

/*
 *	Dump the current record
 */
dumprec()
{	register Li *li = (Li *)0;
	
	for (li = rec; li->key; li++)
		printf("*%s: %s\n", li->key, li->data);
	printf("\n");
}

char *
strstore(str)
register char *str;
{	register len = strlen(str);
	register char *newstr;
	
	newstr = malloc(++len);
	if (newstr == NULL)
		fatal("No memory for string storage\n");
	bcopy(str, newstr, len);
	return (newstr);
}
	
