h34002
s 00066/00000/00000
d D 8.1 95/05/08 13:01:58 mckusick 1 0
c date and time created 95/05/08 13:01:58 by mckusick
e
u
U
t
T
I 1
/*
 * Copyright (c) 1995
 *	The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int		  checkvfsname __P((const char *, const char **));
const char	**makevfslist __P((char *));
static int	  skipvfs;

int
checkvfsname(vfsname, vfslist)
	const char *vfsname;
	const char **vfslist;
{

	if (vfslist == NULL)
		return (0);
	while (*vfslist != NULL) {
		if (strcmp(vfsname, *vfslist) == 0)
			return (skipvfs);
		++vfslist;
	}
	return (!skipvfs);
}

const char **
makevfslist(fslist)
	char *fslist;
{
	const char **av;
	int i;
	char *nextcp;

	if (fslist == NULL)
		return (NULL);
	if (fslist[0] == 'n' && fslist[1] == 'o') {
		fslist += 2;
		skipvfs = 1;
	}
	for (i = 0, nextcp = fslist; *nextcp; nextcp++)
		if (*nextcp == ',')
			i++;
	if ((av = malloc((size_t)(i + 2) * sizeof(char *))) == NULL) {
		warn(NULL);
		return (NULL);
	}
	nextcp = fslist;
	i = 0;
	av[i++] = nextcp;
	while ((nextcp = strchr(nextcp, ',')) != NULL) {
		*nextcp++ = '\0';
		av[i++] = nextcp;
	}
	av[i++] = NULL;
	return (av);
}
E 1
