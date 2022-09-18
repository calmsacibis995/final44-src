#ifndef lint
static char sccsid[] = "@(#)dbase.c	1.6 (UKC) 6/6/87";
#endif  lint
/*
 *	Data base management routines for the people database system
 */
#include <dbm.h>
#undef NULL
#include <stdio.h>
#include <ctype.h>
#include "people.h"
#include <sys/types.h>
#include <sys/stat.h>

FILE	*file;		/* current main input file */

Li	rec[MAXLINES];	/* Current input record */
long	sorpos;		/* position in file of start of record */
long	solpos;		/* current input line position */

int	lineno = 0;

char	*match_start;	/* start of current successful match */

char	srcfile[BUFSIZ];

int	dont_use_dbm;	/* can be defined as 1 to never use the dbm index */

char	*nextpos;	/* next item in the position list for dbm access */

/*
 *	Open the master database
 *	Check also on the presence of a dbm database
 */
openmaster(fname, dont)
char *fname;
{	register char *lookfor;
	
	if (fname == NULL)
	{	lookfor = getenv("PEOPLE");
		if (lookfor)
			strcpy(srcfile, lookfor);
		else
		{	lookfor = getenv("HOME");
			if (lookfor)
			{	strcpy(srcfile, lookfor);
				strcat(srcfile, "/");
			}
			strcat(srcfile, ".people");
		}
		fname = srcfile;
	}
	if ((file = fopen(fname, "r")) == NULL)
		fatal("Cannot open: %s\n", fname);
	lineno = 0;
	if ((dont_use_dbm = dont) == 0)
		dont_use_dbm = checkdbmfiles(fname);
}

/*
 *	Get the next record into rec
 */
nextrecord()
{	register Li *li;
	register char	*pt;
	
	li = rec;

	if (dont_use_dbm == 0)
	{	if (posusingdbm() == EOF)
			return(EOF);
	}
	
	init_li(li);
	if (sor(li->base) != FOUND)
		return (EOF);
	do
	{	if (*li->base != '*')
			break;
		li->key = li->base + 1;
		li->data = index(li->key, ':');
		if (li->data == NULL)
		{	error("line %d: no `:' found\n", lineno);
			li->key = NULL;
			break;
		}
		*li->data++ = '\0';
		while (*li->data == ' ' || *li->data == '\t')
			li->data++;
		pt = index(li->data, '\n');
		if (pt)
			*pt = '\0';
		li++;
		if (li > &rec[MAXLINES])
			fatal("Line %d: Too many lines in record\n", lineno);
		init_li(li);
	} while (nextline(li->base) == FOUND);

	if (rec[0].key)
		return (FOUND);
	return (EOF);
}

/*
 *	set up the new record line
 */
init_li(li)
register Li *li;
{	if (li->base == NULL)
	{	li->base = malloc(MAXCHARS);
		if (li->base == NULL)
			fatal("No more memory\n");
	}
	li->key = NULL;
	li->data = NULL;
}
			
/*
 *	get a line in from the currently open file
 */
nextline(dest)
char	*dest;
{	
	for (;;)
	{	solpos = ftell(file);
		if (fgets(dest, MAXCHARS, file))
		{	lineno++;
			if (*dest != '#')
				return (FOUND);
		}
		else
			break;
	}
	return (EOF);
}

/*
 *	find start of record in currently open file
 */
sor(dest)
char *dest;
{	while (nextline(dest) == FOUND)
	{	if (*dest == '*')
		{	sorpos = solpos;
			return (FOUND);
		}
	}
	return (EOF);
}

/*
 *	Search the current record for a keyword
 *	Start from position given by parameter
 */
Li *
search(li, key)
register Li *li;
char	*key;
{
	if (li == (Li *)0)
		li = rec;
	else	li++;
	for (;li->key; li++)
		if (STREQ(key, li->key))
			return(li);
	return((Li *)0);
}

/*
 *	Given a key and a name
 *	already lower-cased
 *	search in current record for possibly several lines containing
 *	the key.
 */
namein(key, name)
char	*key;
char	*name;
{	register Li *li = (Li *)0;

	while (li = search(li, key))
	{	if (namematch(li->data, name))
			return (1);
	}
	return(0);
}

/*
 *	name matching code
 */
namematch(line, look)
char *line;
char *look;
{	register char *tok = line;
	register char *last;
	
	for(;;)
	{	tok = tokstart(tok);
		if (*tok == '\0')
			break;
		if (lexequ(look, tok))
		{	last = tok + strlen(look);
			if (!isalnum(*last))
			{	match_start = tokend(tok);
				return (1);
			}
		}
		tok = tokend(tok);
		if (*tok == '\0')
			break;
	}
	return (0);
}

char *
tokstart(str)
register char *str;
{	while (*str && !isalnum(*str))
		str++;
	return (str);
}

char *
tokend(str)
register char *str;
{	while (*str && (isalnum(*str) || *str == '\'' || *str == '-'))
		str++;
	return (str);
}

lexequ(na, pt)
register char *na;
register char *pt;
{
	for (;*na; na++, pt++)
	{	if (*na == *pt)
			continue;
		if (isupper(*pt))
		{	if (*na == tolower(*pt))
				continue;
		}
		return (0);
	}
	return (1);
}

lowers(str)
register char *str;
{
	for (;*str; str++)
		if (isupper(*str))
			*str = tolower(*str);
}

/*
 *	Error routines
 */
error(fmt, a, b, c, d, e, f)
char	*fmt;
{	extern char *progname;
	fprintf(stderr, "%s: ", progname);
	fprintf(stderr, fmt, a, b, c, d, e, f);
}

fatal(fmt, a, b, c, d, e, f)
char	*fmt;
{	error(fmt, a, b, c, d, e, f);
	exit(1);
}


/*
 *	Dbm access routines
 */
checkdbmfiles(fn)
char	*fn;
{	char	fname[BUFSIZ];
	char	*upderr;
	struct	stat	file_stat;
	struct	stat	dbm_file;
	
	if (fstat(fileno(file), &file_stat) < 0)
		fatal("Cannot stat: %s\n", fn);
	upderr = "Run peopledbm to update your dbm index files\n";
	strcpy(fname, fn);
	strcat(fname, ".pag");
	
	if (stat(fname, &dbm_file) < 0)
		return(1);
	if (file_stat.st_ctime >= dbm_file.st_ctime)
	{	error(upderr);
		return(1);
	}
	strcpy(fname, fn);
	strcat(fname, ".dir");
	
	if (stat(fname, &dbm_file) < 0)
		return(1);
	if (file_stat.st_ctime >= dbm_file.st_ctime)
	{	error(upderr);
		return(1);
	}
	dbminit(fn);
	return (0);
}

/*
 *	Prime the dbm routines with an initial key
 */
primedbm(ky)
char *ky;
{	datum key;
	datum content;

	if (dont_use_dbm)
		return;
	key.dptr = ky;
	key.dsize = strlen(key) + 1;
	content = fetch(key);
	if (content.dptr == NULL)
	{	dont_use_dbm = 1;
		return;
	}
	nextpos = content.dptr;
}

/*
 *	seek to the next position in poslist
 */
posusingdbm()
{	long	offset;

	if (nextpos == NULL || *nextpos == '\0')
		return (EOF);
	offset = atol(nextpos);
	nextpos = index(nextpos, ',');
	if (nextpos)
		nextpos++;
	fseek(file, offset, 0);
	return (FOUND);
}
