h22220
s 00002/00002/00109
d D 8.1 93/06/04 12:03:31 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00020/00093
d D 5.8 92/04/29 08:30:59 bostic 9 8
c extern -> static for gcc2.1; KNF, use #defined shell names and paths
e
s 00004/00001/00109
d D 5.7 91/02/23 19:49:47 donn 8 7
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00109
d D 5.6 90/06/01 14:11:26 bostic 7 6
c new copyright notice
e
s 00014/00003/00106
d D 5.5 88/07/21 11:30:16 bostic 6 5
c add Berkeley specific copyright
e
s 00010/00014/00099
d D 5.4 86/07/25 18:03:49 bloom 5 3
c fix comments at beginning of line, fix buffer pointer handling
e
s 00002/00005/00108
d R 5.4 86/07/18 17:27:37 bloom 4 3
c clean up comment handling some more, keep shells straight
e
s 00002/00000/00111
d D 5.3 86/07/18 14:10:23 bloom 3 2
c ignore comments starting at beginning of line
e
s 00002/00002/00109
d D 5.2 86/03/09 19:49:15 donn 2 1
c added LIBC_SCCS condition for sccs ids
e
s 00111/00000/00000
d D 5.1 85/11/08 18:14:31 mckusick 1 0
c date and time created 85/11/08 18:14:31 by mckusick
e
u
U
t
T
I 1
/*
D 10
 * Copyright (c) 1985 Regents of the University of California.
D 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 7
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 6
 */

D 2
#ifndef lint
E 2
I 2
#if defined(LIBC_SCCS) && !defined(lint)
E 2
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif not lint
E 2
I 2
D 6
#endif LIBC_SCCS and not lint
E 6
I 6
#endif /* LIBC_SCCS and not lint */
E 6
E 2

#include <sys/param.h>
#include <sys/file.h>
#include <sys/stat.h>
D 9
#include <ctype.h>
E 9
#include <stdio.h>
I 9
#include <ctype.h>
E 9
I 8
#include <stdlib.h>
#include <unistd.h>
I 9
#include <paths.h>
E 9
E 8

D 9
#define SHELLS "/etc/shells"

E 9
/*
D 9
 * Do not add local shells here.  They should be added in /etc/shells
E 9
I 9
 * Local shells should NOT be added here.  They should be added in
 * /etc/shells.
E 9
 */
D 9
static char *okshells[] =
    { "/bin/sh", "/bin/csh", 0 };
E 9

D 5
static int inprogress;
E 5
D 9
static char **shells, *strings;
I 5
static char **curshell = NULL;
E 5
extern char **initshells();
E 9
I 9
static char *okshells[] = { _PATH_BSHELL, _PATH_CSHELL, NULL };
static char **curshell, **shells, *strings;
static char **initshells __P((void));
E 9

/*
D 9
 * Get a list of shells from SHELLS, if it exists.
E 9
I 9
 * Get a list of shells from _PATH_SHELLS, if it exists.
E 9
 */
char *
getusershell()
{
	char *ret;
D 5
	static char **shells;
E 5

D 5
	if (!inprogress)
		shells = initshells();
	ret = *shells;
	if (*shells != NULL)
		shells++;
E 5
I 5
	if (curshell == NULL)
		curshell = initshells();
	ret = *curshell;
	if (ret != NULL)
		curshell++;
E 5
	return (ret);
}

I 8
void
E 8
endusershell()
{
	
	if (shells != NULL)
D 9
		free((char *)shells);
E 9
I 9
		free(shells);
E 9
	shells = NULL;
	if (strings != NULL)
		free(strings);
	strings = NULL;
D 5
	inprogress = 0;
E 5
I 5
	curshell = NULL;
E 5
}

I 8
void
E 8
setusershell()
{

D 5
	shells = initshells();
E 5
I 5
	curshell = initshells();
E 5
}

static char **
initshells()
{
	register char **sp, *cp;
	register FILE *fp;
	struct stat statb;
D 8
	extern char *malloc(), *calloc();
E 8

D 5
	inprogress = 1;
E 5
	if (shells != NULL)
D 9
		free((char *)shells);
E 9
I 9
		free(shells);
E 9
	shells = NULL;
	if (strings != NULL)
		free(strings);
	strings = NULL;
D 9
	if ((fp = fopen(SHELLS, "r")) == (FILE *)0)
		return(okshells);
E 9
I 9
	if ((fp = fopen(_PATH_SHELLS, "r")) == NULL)
		return (okshells);
E 9
	if (fstat(fileno(fp), &statb) == -1) {
		(void)fclose(fp);
D 9
		return(okshells);
E 9
I 9
		return (okshells);
E 9
	}
D 9
	if ((strings = malloc((unsigned)statb.st_size)) == NULL) {
E 9
I 9
	if ((strings = malloc((u_int)statb.st_size)) == NULL) {
E 9
		(void)fclose(fp);
D 9
		return(okshells);
E 9
I 9
		return (okshells);
E 9
	}
D 9
	shells = (char **)calloc((unsigned)statb.st_size / 3, sizeof (char *));
E 9
I 9
	shells = calloc((unsigned)statb.st_size / 3, sizeof (char *));
E 9
	if (shells == NULL) {
		(void)fclose(fp);
		free(strings);
		strings = NULL;
D 9
		return(okshells);
E 9
I 9
		return (okshells);
E 9
	}
	sp = shells;
	cp = strings;
	while (fgets(cp, MAXPATHLEN + 1, fp) != NULL) {
I 3
D 5
		if (*cp == '#')
			continue;
E 3
		while (*cp != '/' && *cp != '\0')
E 5
I 5
		while (*cp != '#' && *cp != '/' && *cp != '\0')
E 5
			cp++;
D 5
		if (*cp == '\0')
E 5
I 5
		if (*cp == '#' || *cp == '\0')
E 5
			continue;
		*sp++ = cp;
		while (!isspace(*cp) && *cp != '#' && *cp != '\0')
			cp++;
		*cp++ = '\0';
	}
D 9
	*sp = (char *)0;
E 9
I 9
	*sp = NULL;
E 9
	(void)fclose(fp);
	return (shells);
}
E 1
