/*-
 * Copyright (c) 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char sccsid[] = "@(#)getlesson.c	8.1 (Berkeley) 6/6/93";
#endif /* not lint */

#include "stdio.h"
#include "lrnref.h"
#include "pathnames.h"

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
		execl(_PATH_CSHELL, "csh", "-cf", ans, 0);
		perror(_PATH_CSHELL);
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
