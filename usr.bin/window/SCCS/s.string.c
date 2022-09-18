h01071
s 00002/00002/00125
d D 8.1 93/06/06 22:29:43 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00124
d D 3.13 90/06/06 21:44:13 bostic 13 12
c fix contrib notice (Edward Wang)
e
s 00001/00011/00123
d D 3.12 90/06/02 15:21:14 bostic 12 11
c new copyright notice
e
s 00010/00005/00124
d D 3.11 88/06/29 21:36:31 bostic 11 10
c install approved copyright notice
e
s 00013/00007/00116
d D 3.10 88/02/21 13:37:27 bostic 10 9
c written by Edward Wang; attach Berkeley specific copyright
e
s 00000/00001/00123
d D 3.9 87/10/22 19:38:43 bostic 9 8
c ANSI C; sprintf now returns an int.
e
s 00006/00000/00118
d D 3.8 85/04/24 16:20:15 edward 8 7
c copyright messages
e
s 00001/00001/00117
d D 3.7 84/05/23 02:00:09 edward 7 6
c new sccs id
e
s 00020/00000/00098
d D 3.6 84/04/05 16:52:10 edward 6 5
c string operators, +, <<, >>
e
s 00002/00004/00096
d D 3.5 84/03/23 18:17:21 edward 5 4
c compile with -R
e
s 00002/00002/00098
d D 3.4 84/01/09 14:57:03 edward 4 3
c gross bug
e
s 00039/00011/00061
d D 3.3 84/01/05 15:47:24 edward 3 2
c consistency checking
e
s 00001/00000/00071
d D 3.2 83/11/25 11:21:34 edward 2 1
c lint
e
s 00071/00000/00000
d D 3.1 83/11/22 12:48:03 edward 1 0
c date and time created 83/11/22 12:48:03 by edward
e
u
U
t
T
I 1
D 10
#ifndef lint
D 7
static	char *sccsid = "%W% %E%";
E 7
I 7
static char sccsid[] = "%W% %G%";
E 7
#endif

E 10
I 8
/*
D 10
 * Copyright (c) 1983 Regents of the University of California,
 * All rights reserved.  Redistribution permitted subject to
 * the terms of the Berkeley Software License Agreement.
E 10
I 10
D 14
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
I 13
 * This code is derived from software contributed to Berkeley by
 * Edward Wang at The University of California, Berkeley.
 *
E 13
D 12
 * Redistribution and use in source and binary forms are permitted
D 11
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 11
I 11
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
E 12
I 12
 * %sccs.include.redist.c%
E 12
E 11
E 10
 */
I 10

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 10

E 8
#include "string.h"

char *malloc();
I 2
D 9
char *sprintf();
E 9
E 2

char *
str_cpy(s)
register char *s;
{
	char *str;
	register char *p;

D 3
	str = p = malloc((unsigned) strlen(s) + 1);
E 3
I 3
	str = p = str_alloc(strlen(s) + 1);
E 3
	if (p == 0)
		return 0;
	while (*p++ = *s++)
		;
	return str;
}

char *
I 6
str_ncpy(s, n)
register char *s;
register n;
{
	int l = strlen(s);
	char *str;
	register char *p;

	if (n > l)
		n = l;
	str = p = str_alloc(n + 1);
	if (p == 0)
		return 0;
	while (--n >= 0)
		*p++ = *s++;
	*p = 0;
	return str;
}

char *
E 6
str_itoa(i)
int i;
{
	char buf[30];

	(void) sprintf(buf, "%d", i);
	return str_cpy(buf);
}

char *
str_cat(s1, s2)
char *s1, *s2;
{
	char *str;
	register char *p, *q;

D 3
	str = p = malloc((unsigned) strlen(s1) + strlen(s2) + 1);
E 3
I 3
	str = p = str_alloc(strlen(s1) + strlen(s2) + 1);
E 3
	if (p == 0)
		return 0;
	for (q = s1; *p++ = *q++;)
		;
	for (q = s2, p--; *p++ = *q++;)
		;
	return str;
}

D 3
str_free(str)
char *str;
{
	extern char end[];

	if (str >= end)
		free(str);
}

E 3
/*
 * match s against p.
 * s can be a prefix of p with at least min characters.
 */
str_match(s, p, min)
register char *s, *p;
register min;
{
	for (; *s && *p && *s == *p; s++, p++, min--)
		;
	return *s == *p || *s == 0 && min <= 0;
}
I 3

#ifdef STR_DEBUG
D 5
struct string str_head = {
	&str_head, &str_head
};

E 5
char *
str_alloc(l)
int l;
{
	register struct string *s;

	s = (struct string *) malloc((unsigned)l + str_offset);
	if (s == 0)
		return 0;
I 5
	if (str_head.s_forw == 0)
		str_head.s_forw = str_head.s_back = &str_head;
E 5
	s->s_forw = str_head.s_forw;
	s->s_back = &str_head;
	str_head.s_forw = s;
	s->s_forw->s_back = s;
	return s->s_data;
}

str_free(str)
char *str;
{
D 4
	register struct string *s = str_stos(s);
E 4
I 4
	register struct string *s;
E 4

	for (s = str_head.s_forw; s != &str_head && s->s_data != str;
	     s = s->s_forw)
		;
	if (s == &str_head)
		abort();
	s->s_back->s_forw = s->s_forw;
	s->s_forw->s_back = s->s_back;
D 4
	free(s->s_data);
E 4
I 4
	free((char *)s);
E 4
}
#endif
E 3
E 1
