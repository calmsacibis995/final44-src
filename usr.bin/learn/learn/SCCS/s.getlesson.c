h60593
s 00002/00002/00079
d D 8.1 93/06/06 14:56:17 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00072
d D 4.4 91/04/17 18:00:33 bostic 4 3
c new copyright; att/bsd/shared
e
s 00003/00002/00071
d D 4.3 89/05/10 22:47:08 bostic 3 2
c file reorg, pathnames.h, paths.h
e
s 00000/00000/00073
d D 4.2 83/04/26 01:19:31 mckusick 2 1
c 
e
s 00073/00000/00000
d D 4.1 83/04/26 01:18:13 mckusick 1 0
c date and time created 83/04/26 01:18:13 by mckusick
e
u
U
t
T
I 4
/*-
D 5
 * Copyright (c) 1986 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.proprietary.c%
 */

E 4
I 1
#ifndef lint
D 4
static char sccsid[] = "%W%	(Berkeley)	%G%";
#endif not lint
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4

#include "stdio.h"
#include "lrnref.h"
I 3
#include "pathnames.h"
E 3

char *
getlesson()
{
	register char *p;
	char ans[80], line[200];
	int isnum, found, fd[2];
	FILE *fp;

	sprintf(ans, "%s/%s/L%s", direct, sname, level);
	if (access(ans, 04) == 0)		/* there is a file */
		return(level);
	isnum = 1;
	for (p=level; *p; p++)		/* accept:  (digit|dot)*anychar  */
		if (*p != '.' && (*p < '0' || *p > '9') && *(p+1) != '\0')
			isnum = 0;
	if (isnum) {
		strcpy(line, level);
		p = level;
		while (*p != '.' && *p >= '0' && *p <= '9')
			p++;
		*p = '\0';
		strcat(level, ".1a");
		sprintf(ans, "%s/%s/L%s", direct, sname, level);
		if (access(ans, 04) == 0) {	/* there is a file */
			printf("There is no lesson %s; trying lesson %s instead.\n\n", line, level);
			return(level);
		}
		printf("There is no lesson %s.\n", line);
		return(0);
	}
	/* fgrep through lessons for one containing the string in 'level' */
	pipe(fd);
	if (fork() == 0) {
		close(fd[0]);
		dup2(fd[1], 1);
		sprintf(ans,"cd %s/%s ; fgrep '%s' L?.* L??.* L???.*", direct, sname, level);
D 3
		execl("/bin/csh", "csh", "-cf", ans, 0);
		perror("/bin/csh");
E 3
I 3
		execl(_PATH_CSHELL, "csh", "-cf", ans, 0);
		perror(_PATH_CSHELL);
E 3
		fprintf(stderr, "Getlesson:  can't do %s\n", ans);
	}
	close(fd[1]);
	fp = fdopen(fd[0], "r");
	found = 0;
	while (fgets(line, 200, fp) != NULL) {
		for (p=line; *p != ':'; p++) ;
		p++;
		if (*p == '#')
			continue;
		else {
			found = 1;
			break;
		}
	}
	/*fclose(fp);*/
	if (found) {
		*--p = '\0';
		strcpy(level, &line[1]);
		sprintf(ans, "%s/%s/L%s", direct, sname, level);
		if (access(ans, 04) == 0) {	/* there is a file */
			printf("Trying lesson %s.\n\n", level);
			return(level);
		}
	}
	printf("There is no lesson containing \"%s\".\n", level);
	return(0);
}
E 1
