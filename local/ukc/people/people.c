#ifndef lint
static char sccsid[] = "@(#)people.c	1.10 (UKC) 7/6/87";
#endif  lint
/***

* program name:
	people.c
* function:
	Acts as an enquiry agent into the name database
	Various links are used to provide various hooks
	ph	prints phone numbers
	email	prints email addresses
	work	prints work address info
	home	prints home address info
* switches:
	-f file	Name of database - defaults to ~/.people
	keys to be used for access
* libraries used:
	standard
* compile time parameters:
	cc -o people -O people.c
* history:
	Written June 1987 - Peter Collinson UKC
	From an idea from David Tilbrook

***/
#include <stdio.h>
#include <ctype.h>
#include "people.h"

/*
 *	output type
 */
int	optype;

#define DUMP	0
#define PHONE	1
#define EMAIL	2
#define WORK	3
#define HOME	4

char	*progname;

main(argc, argv)
int	argc;
char	*argv[];
{	register char *lookfor;

	progname = rindex(argv[0], '/');
	if (progname)
		progname++;
	else	progname = argv[0];
	
	switch (*progname)
	{
	case 'p':
		if (progname[1] == 'h')
			optype = PHONE;
		break;
	case 'e':
		optype = EMAIL;
		break;
	case 'h':
		optype = HOME;
		break;
	case 'w':
		optype = WORK;
		break;
	}


	lookfor = NULL;
	if (argc > 1 && *argv[1] == '-')
	{	argv++;
		argc--;
		lookfor = *argv;
		if (lookfor[1] == 'f')
		{	if (lookfor[2] == '\0')
			{	argv++;
				argc--;
				lookfor = *argv;
			}
			else	lookfor += 2;
		}
		else
			fatal("Usage: %s [-f database] list of words\n", progname);
	}

	lowervec(argc, argv);
	++argv;
	argc--;
		
	openmaster(lookfor, argc == 0 ? 1 : 0);
	
	primedbm(*argv);
	
	while (nextrecord() == FOUND)
	{	if (*argv == NULL || record_scan(argv))
			dumprec();
	}
	exit(1);
}


record_scan(av)
char	*av[];
{	register char *na;
	extern	char *match_start;
	
	if (namein("name", *av) ||
	    namein("email", *av) ||
	    namein("key", *av))
	{
		while (*(++av))
		{	na = tokstart(*av);
			if (*na && namematch(match_start, *av) == 0)
				return(0);
		}
		return (1);
	}
	return (0);
}

/*
 *	Dump the current record
 */
dumprec()
{	register Li *li = (Li *)0;
	char	*name;
	
	switch(optype)
	{
	case PHONE:
		li = search(li, "name");
		name = li->data;
		li = (Li *)0;
		while (li = search(li, "phone"))
		{	printf("%s: (work) %s\n", name, li->data);
		}
		li = (Li *)0;
		while (li = search(li, "home-phone"))
		{	printf("%s: (home) %s\n", name, li->data);
		}
		break;

	case EMAIL:
		li = search(li, "name");
		name = li->data;
		li = (Li *)0;
		while (li = search(li, "email"))
		{	printf("%s: %s\n", name, li->data);
		}
		break;

	case HOME:
		li = search(li, "name");
		name = li->data;
		li = (Li *)0;
		while (li = search(li, "home"))
		{	if (name)
			{	printf("%s,\n", name);
				name = (char *)0;
			}
			printf("%s\n", li->data);
		}
		li = (Li *)0;
		while (li = search(li, "home-phone"))
			printf("Phone: %s\n", li->data);
		break;
	case WORK:
		li = search(li, "name");
		name = li->data;
		li = (Li *)0;
		while (li = search(li, "work"))
		{	if (name)
			{	printf("%s,\n", name);
				name = (char *)0;
			}
			printf("%s\n", li->data);
		}
		li = (Li *)0;
		while (li = search(li, "phone"))
			printf("Phone: %s\n", li->data);
		li = (Li *)0;
		while (li = search(li, "fax"))
			printf("Fax: %s\n", li->data);
		li = (Li *)0;
		while (li = search(li, "telex"))
			printf("Telex: %s\n", li->data);
		li = (Li *)0;
		while (li = search(li, "email"))
			printf("Email: %s\n", li->data);
		break;
		
	default:
		for (li = rec; li->key; li++)
			printf("*%s: %s\n", li->key, li->data);
		printf("\n");
	}
}

lowervec(ac, av)
char	*av[];
{	while (--ac)
	{	av++;
		lowers(*av);
	}
}


