#ifndef lint
static char sccsid[] = "@(#)peopledbm.c	1.2 (UKC) 6/6/87";
#endif  lint
/***

* program name:
	peopledbm.c
* function:
	Create a dbm index for tokens from the people database
* switches:
	-f database stem
* libraries used:
	dbase.o standard 
* compile time parameters:
	cc -o peopledbm -O peopledbm.c
* history:
	Written June 1987 Peter Collinson UKC

***/
#include <stdio.h>
#include <ctype.h>
#include <dbm.h>
#include "people.h"

char	*progname;

char	*usage[] = "Usage: peopledbm [-f peoplefile]\n";

typedef datum Datum;	/* allow my idea of typedefs */

struct	tok_store
{	char	*tok;
};
typedef struct tok_store Tok;
Tok	*toks;		/* base of list */
int	tokmax;		/* max number */
int	tokinx;		/* current index */
#define TOKCHUNK	300

char	*srchfor[] =
{	"name",
	"email",
	"key",
	0
};

char	*strstore();

main(argc, argv)
int	argc;
char	*argv[];
{	register char *fname;
	register char *pt;
	
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

	/*
	 *	Create the dbm database files
	 */
	dbmcreate(fname);
	
	while (nextrecord() == FOUND)
	{	maketokens();
		sorttoks();
		storetoks();
	}
	exit(0);
}

/*
 *	Create the dbm files
 */
dbmcreate(fn)
char *fn;
{	extern char srcfile[];
	char	dname[BUFSIZ];
	register fd;
	
	if (fn == NULL)
		fn = srcfile;
	
	strcpy(dname, fn);
	strcat(dname, ".pag");
	
	fd = creat(dname, 0644);
	if (fd < 0)
		fatal("Cannot create: %s\n", dname);
	close(fd);
	
	strcpy(dname, fn);
	strcat(dname, ".dir");
	
	fd = creat(dname, 0644);
	if (fd < 0)
		fatal("Cannot create: %s\n", dname);
	close(fd);
	
	dbminit(fn);
	
}

/*
 *	Scan the current record - making tokens
 */
maketokens()
{	register Li	*lp;
	register char	**lf;
	register char	*tstart;
	register char	*tend;
	char	tendch;
	
	for (lf = srchfor; *lf; lf++)
	{	lp = (Li *)0;
		while (lp = search(lp, *lf))
		{	for (tstart = lp->data; tstart = tokstart(tstart); tstart = tend)
			{	if (*tstart == '\0')
					break;
				tend = tokend(tstart);
				tendch = *tend;
				*tend = '\0';
				lowers(tstart);
				storetok(tstart);
				*tend = tendch;
			}
		}
	}
}

/*
 *	Store a token in the array
 */
storetok(st)
char *st;
{	if (toks == (Tok *)0)
	{	toks = (Tok *)malloc(TOKCHUNK * sizeof (Tok));
		if (toks == (Tok *)0)
			fatal("No memory for token storage\n");
		tokmax = TOKCHUNK;
		tokinx = 0;
	}
	if (tokinx >= tokmax)
	{	toks = (Tok *)realloc((char *)toks, (tokmax + TOKCHUNK)*sizeof (Tok));
		if (toks == (Tok *)0)
			fatal("No memory for token storage\n");
		tokmax += TOKCHUNK;
	}
	toks[tokinx++].tok = strstore(st);
}

char *
strstore(str)
register char *str;
{	register len = strlen(str);
	register char *newstr;
	
	newstr = malloc(len+1);
	if (newstr == NULL)
		fatal("No memory for string storage\n");
	bcopy(str, newstr, len+1);
	return (newstr);
}

sorttoks()
{	extern tk_sort();

	qsort(toks, tokinx, sizeof (Tok), tk_sort);
}

tk_sort(a, b)
Tok *a, *b;
{	register char *ap = a->tok;
	register char *bp = b->tok;
	
	if (*ap < *bp)
		return (-1);
	if (*ap > *bp)
		return (1);
	return (strcmp(ap, bp));
}

dumptoks()
{	register char *p;
	register i;
	
	for (i = 0; i < tokinx; i++)
	{	p = toks[i].tok;
		printf("%s ", p);
		free(toks[i].tok);
	}
	printf("\n");
	tokinx = 0;
}

storetoks()
{	Datum	key;
	Datum	content;
	Datum	oldcontent;
	char	newval[BUFSIZ];
	char	sortxt[32];
	char	*lastval = NULL;
	char	*p;
	register int i;
	extern	long sorpos;
	
	(void) sprintf(sortxt, ",%d", sorpos);
	
	for (i = 0; i < tokinx; i++)
	{	p = toks[i].tok;
		if (STREQ(p, lastval))
			continue;
		lastval = p;
		key.dptr = lastval;
		key.dsize = strlen(lastval) + 1;
		oldcontent = fetch(key);

		if (oldcontent.dptr == NULL)
			strcpy(newval, &sortxt[1]);
		else
		{	strcpy(newval, oldcontent.dptr);
			strcat(newval, sortxt);
		}
		content.dptr = newval;
		content.dsize = strlen(newval) + 1;
		store(key, content);
	}
	for (i = 0; i < tokinx; i++)
		free(toks[i].tok);

	tokinx = 0;
}
