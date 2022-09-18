h45930
s 00002/00002/00088
d D 8.1 93/06/04 13:08:31 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00022/00024/00068
d D 5.7 92/06/25 09:15:11 bostic 7 6
c general cleanup, KNF; no bug fixes
e
s 00011/00010/00081
d D 5.6 91/06/04 13:56:15 karels 6 5
c KNF
e
s 00005/00003/00086
d D 5.5 91/02/23 22:56:42 donn 5 4
c Adjustments and bug fixes after adding prototypes to include files.
e
s 00001/00011/00088
d D 5.4 90/06/01 14:44:43 bostic 4 3
c new copyright notice
e
s 00009/00009/00090
d D 5.3 90/05/16 12:08:09 bostic 3 2
c use right include files, malloc takes size_t now
e
s 00010/00005/00089
d D 5.2 88/06/27 17:34:13 bostic 2 1
c install approved copyright notice
e
s 00094/00000/00000
d D 5.1 87/12/24 15:33:23 bostic 1 0
c includes bug fix 4.3BSD/lib/70
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1987 Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1987, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 4
 * Redistribution and use in source and binary forms are permitted
D 2
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 2
I 2
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 2
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

D 3
#include <sys/types.h>
#include <stdio.h>
E 3
I 3
#include <stddef.h>
#include <stdlib.h>
I 5
#include <string.h>
E 5
E 3

I 7
char *__findenv __P((const char *, int *)); 

E 7
/*
 * setenv --
 *	Set the value of the environmental variable "name" to be
 *	"value".  If rewrite is set, replace any current value.
 */
setenv(name, value, rewrite)
D 5
	register char *name, *value;
E 5
I 5
	register const char *name;
	register const char *value;
E 5
	int rewrite;
{
	extern char **environ;
	static int alloced;			/* if allocated space before */
D 7
	register char *C;
E 7
I 7
	register char *c;
E 7
	int l_value, offset;
D 3
	char *malloc(), *realloc(), *_findenv();
E 3
I 3
D 7
	char *_findenv();
E 7
E 3

	if (*value == '=')			/* no `=' in value */
		++value;
	l_value = strlen(value);
D 7
	if ((C = _findenv(name, &offset))) {	/* find if already exists */
E 7
I 7
	if ((c = __findenv(name, &offset))) {	/* find if already exists */
E 7
		if (!rewrite)
D 6
			return(0);
E 6
I 6
			return (0);
E 6
D 7
		if (strlen(C) >= l_value) {	/* old larger; copy over */
			while (*C++ = *value++);
E 7
I 7
		if (strlen(c) >= l_value) {	/* old larger; copy over */
			while (*c++ = *value++);
E 7
D 6
			return(0);
E 6
I 6
			return (0);
E 6
		}
D 6
	}
	else {					/* create new slot */
E 6
I 6
	} else {					/* create new slot */
E 6
D 7
		register int	cnt;
		register char	**P;
E 7
I 7
		register int cnt;
		register char **p;
E 7

D 7
		for (P = environ, cnt = 0; *P; ++P, ++cnt);
E 7
I 7
		for (p = environ, cnt = 0; *p; ++p, ++cnt);
E 7
		if (alloced) {			/* just increase size */
			environ = (char **)realloc((char *)environ,
D 3
			    (u_int)(sizeof(char *) * (cnt + 2)));
E 3
I 3
			    (size_t)(sizeof(char *) * (cnt + 2)));
E 3
			if (!environ)
D 6
				return(-1);
E 6
I 6
				return (-1);
E 6
		}
		else {				/* get new space */
			alloced = 1;		/* copy old entries into it */
D 3
			P = (char **)malloc((u_int)(sizeof(char *) *
E 3
I 3
D 7
			P = (char **)malloc((size_t)(sizeof(char *) *
E 3
			    (cnt + 2)));
			if (!P)
E 7
I 7
			p = malloc((size_t)(sizeof(char *) * (cnt + 2)));
			if (!p)
E 7
D 6
				return(-1);
E 6
I 6
				return (-1);
E 6
D 7
			bcopy(environ, P, cnt * sizeof(char *));
			environ = P;
E 7
I 7
			bcopy(environ, p, cnt * sizeof(char *));
			environ = p;
E 7
		}
		environ[cnt + 1] = NULL;
		offset = cnt;
	}
D 5
	for (C = name; *C && *C != '='; ++C);	/* no `=' in name */
E 5
I 5
D 7
	for (C = (char *)name; *C && *C != '='; ++C);	/* no `=' in name */
E 7
I 7
	for (c = (char *)name; *c && *c != '='; ++c);	/* no `=' in name */
E 7
E 5
	if (!(environ[offset] =			/* name + `=' + value */
D 3
	    malloc((u_int)((int)(C - name) + l_value + 2))))
E 3
I 3
D 7
	    malloc((size_t)((int)(C - name) + l_value + 2))))
E 7
I 7
	    malloc((size_t)((int)(c - name) + l_value + 2))))
E 7
E 3
D 6
		return(-1);
	for (C = environ[offset]; (*C = *name++) && *C != '='; ++C);
	for (*C++ = '='; *C++ = *value++;);
	return(0);
E 6
I 6
		return (-1);
D 7
	for (C = environ[offset]; (*C = *name++) && *C != '='; ++C)
		;
	for (*C++ = '='; *C++ = *value++; )
		;
E 7
I 7
	for (c = environ[offset]; (*c = *name++) && *c != '='; ++c);
	for (*c++ = '='; *c++ = *value++;);
E 7
	return (0);
E 6
}

/*
 * unsetenv(name) --
 *	Delete environmental variable "name".
 */
void
unsetenv(name)
D 5
	char	*name;
E 5
I 5
D 7
	const char	*name;
E 7
I 7
	const char *name;
E 7
E 5
{
D 3
	extern	char	**environ;
	register char	**P;
	int	offset;
E 3
I 3
	extern char **environ;
D 7
	register char **P;
E 7
I 7
	register char **p;
E 7
	int offset;
E 3

D 7
	while (_findenv(name, &offset))		/* if set multiple times */
		for (P = &environ[offset];; ++P)
			if (!(*P = *(P + 1)))
E 7
I 7
	while (__findenv(name, &offset))	/* if set multiple times */
		for (p = &environ[offset];; ++p)
			if (!(*p = *(p + 1)))
E 7
				break;
}
E 1
