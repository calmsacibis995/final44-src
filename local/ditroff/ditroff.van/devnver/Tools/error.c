#ifndef lint
static char sccsid[] = "%W% (CWI) %E%";
#endif lint

#include <stdio.h>
#include <errno.h>

error(s, s1, s2, s3, s4)
	char *s, *s1, *s2, *s3, *s4;
{
	extern char *sys_errlist[];
	extern int errno, sys_nerr;

	fprintf(stderr, s, s1, s2, s3, s4);
	if (errno > 0 && errno < sys_nerr)
		fprintf(stderr, " (%s)", sys_errlist[errno]);
	fprintf(stderr, "\n");
	exit(1);
}
