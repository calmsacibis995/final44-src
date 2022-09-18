h65388
s 00002/00002/00147
d D 8.3 94/02/24 14:24:04 bostic 10 9
c toupper() and tolower() were backwards
c From: Paul Borman <prb@BSDI.COM>
e
s 00005/00000/00144
d D 8.2 94/01/21 17:02:52 bostic 9 8
c add USL's copyright notice
e
s 00002/00002/00142
d D 8.1 93/06/04 12:43:04 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00034/00015/00110
d D 5.7 93/05/26 20:27:50 bostic 7 6
c rune support from Paul Borman
e
s 00011/00011/00114
d D 5.6 92/03/13 15:04:24 bostic 6 5
c change _ctype_ to __ctype
e
s 00002/00002/00123
d D 5.5 91/12/28 15:49:12 bostic 5 4
c ANSI C: tolower/toupper only work if isupper/islower is true for char
e
s 00016/00002/00109
d D 5.4 91/11/10 13:57:26 bostic 4 3
c add isascii/toascii routines
e
s 00020/00013/00091
d D 5.3 91/10/23 16:41:23 bostic 3 2
c add isblank, minor KNF whacks
e
s 00001/00011/00103
d D 5.2 90/06/01 14:12:13 bostic 2 1
c new copyright notice
e
s 00114/00000/00000
d D 5.1 89/05/27 10:55:21 bostic 1 0
c date and time created 89/05/27 10:55:21 by bostic
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
I 9
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 9
E 8
 *
I 7
 * This code is derived from software contributed to Berkeley by
 * Paul Borman at Krystal Technologies.
 *
E 7
D 2
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#define _ANSI_LIBRARY
#include <ctype.h>

#undef isalnum
I 7
int
E 7
isalnum(c)
	int c;
{
D 3
	return((_ctype_ + 1)[c] & (_U|_L|_N));
E 3
I 3
D 6
	return ((_ctype_ + 1)[c] & (_U|_L|_N));
E 6
I 6
D 7
	return ((__ctype + 1)[c] & (_U|_L|_N));
E 7
I 7
	return(__istype((c), (_A|_D)));
E 7
E 6
E 3
}

#undef isalpha
I 7
int
E 7
isalpha(c)
	int c;
{
D 3
	return((_ctype_ + 1)[c] & (_U|_L));
E 3
I 3
D 6
	return ((_ctype_ + 1)[c] & (_U|_L));
E 6
I 6
D 7
	return ((__ctype + 1)[c] & (_U|_L));
E 7
I 7
	return (__istype((c), _A));
E 7
E 6
E 3
}

I 4
#undef isascii
I 7
int
E 7
isascii(c)
	int c;
{
D 7
	return (c <= 0177);
E 7
I 7
	return((c & ~0x7F) == 0);
E 7
}

E 4
I 3
#undef isblank
I 7
int
E 7
isblank(c)
	int c;
{
D 7
	return (c == '\t' || c == ' ');
E 7
I 7
	return (__istype((c), _B));
E 7
}

E 3
#undef iscntrl
I 7
int
E 7
iscntrl(c)
	int c;
{
D 3
	return((_ctype_ + 1)[c] & _C);
E 3
I 3
D 6
	return ((_ctype_ + 1)[c] & _C);
E 6
I 6
D 7
	return ((__ctype + 1)[c] & _C);
E 7
I 7
	return (__istype((c), _C));
E 7
E 6
E 3
}

#undef isdigit
I 7
int
E 7
isdigit(c)
	int c;
{
D 3
	return((_ctype_ + 1)[c] & _N);
E 3
I 3
D 6
	return ((_ctype_ + 1)[c] & _N);
E 6
I 6
D 7
	return ((__ctype + 1)[c] & _N);
E 7
I 7
	return (__isctype((c), _D));
E 7
E 6
E 3
}

#undef isgraph
I 7
int
E 7
isgraph(c)
	int c;
{
D 3
	return((_ctype_ + 1)[c] & (_P|_U|_L|_N));
E 3
I 3
D 6
	return ((_ctype_ + 1)[c] & (_P|_U|_L|_N));
E 6
I 6
D 7
	return ((__ctype + 1)[c] & (_P|_U|_L|_N));
E 7
I 7
	return (__istype((c), _G));
E 7
E 6
E 3
}

#undef islower
I 7
int
E 7
islower(c)
	int c;
{
D 3
	return((_ctype_ + 1)[c] & _L);
E 3
I 3
D 6
	return ((_ctype_ + 1)[c] & _L);
E 6
I 6
D 7
	return ((__ctype + 1)[c] & _L);
E 7
I 7
	return (__istype((c), _L));
E 7
E 6
E 3
}

#undef isprint
I 7
int
E 7
isprint(c)
	int c;
{
D 3
	return((_ctype_ + 1)[c] & (_P|_U|_L|_N|_B));
E 3
I 3
D 6
	return ((_ctype_ + 1)[c] & (_P|_U|_L|_N|_B));
E 6
I 6
D 7
	return ((__ctype + 1)[c] & (_P|_U|_L|_N|_B));
E 7
I 7
	return (__istype((c), _R));
E 7
E 6
E 3
}

#undef ispunct
I 7
int
E 7
ispunct(c)
	int c;
{
D 3
	return((_ctype_ + 1)[c] & _P);
E 3
I 3
D 6
	return ((_ctype_ + 1)[c] & _P);
E 6
I 6
D 7
	return ((__ctype + 1)[c] & _P);
E 7
I 7
	return (__istype((c), _P));
E 7
E 6
E 3
}

#undef isspace
I 7
int
E 7
isspace(c)
	int c;
{
D 3
	return((_ctype_ + 1)[c] & _S);
E 3
I 3
D 6
	return ((_ctype_ + 1)[c] & _S);
E 6
I 6
D 7
	return ((__ctype + 1)[c] & _S);
E 7
I 7
	return (__istype((c), _S));
E 7
E 6
E 3
}

#undef isupper
I 7
int
E 7
isupper(c)
	int c;
{
D 3
	return((_ctype_ + 1)[c] & _U);
E 3
I 3
D 6
	return ((_ctype_ + 1)[c] & _U);
E 6
I 6
D 7
	return ((__ctype + 1)[c] & _U);
E 7
I 7
	return (__istype((c), _U));
E 7
E 6
E 3
}

#undef isxdigit
I 7
int
E 7
isxdigit(c)
	int c;
{
D 3
	return((_ctype_ + 1)[c] & (_N|_X));
E 3
I 3
D 6
	return ((_ctype_ + 1)[c] & (_N|_X));
E 6
I 6
D 7
	return ((__ctype + 1)[c] & (_N|_X));
E 7
I 7
	return (__isctype((c), _X));
E 7
E 6
E 3
}

I 4
#undef toascii
I 7
int
E 7
toascii(c)
	int c;
{
	return (c & 0177);
}

E 4
#undef tolower
I 7
int
E 7
tolower(c)
	int c;
{
D 3
	return((c) - 'A' + 'a');
E 3
I 3
D 4
	return ((c) - 'A' + 'a');
E 4
I 4
D 5
	return (c - 'A' + 'a');
E 5
I 5
D 7
	return (isupper(c) ? c - 'A' + 'a' : c);
E 7
I 7
D 10
        return((c & _CRMASK) ? ___toupper(c) : _CurrentRuneLocale->mapupper[c]);
E 10
I 10
        return((c & _CRMASK) ? ___tolower(c) : _CurrentRuneLocale->maplower[c]);
E 10
E 7
E 5
E 4
E 3
}

#undef toupper
I 7
int
E 7
toupper(c)
	int c;
{
D 3
	return((c) - 'a' + 'A');
E 3
I 3
D 4
	return ((c) - 'a' + 'A');
E 4
I 4
D 5
	return (c - 'a' + 'A');
E 5
I 5
D 7
	return (islower(c) ? c - 'a' + 'A' : c);
E 7
I 7
D 10
        return((c & _CRMASK) ? ___tolower(c) : _CurrentRuneLocale->maplower[c]);
E 10
I 10
        return((c & _CRMASK) ? ___toupper(c) : _CurrentRuneLocale->mapupper[c]);
E 10
E 7
E 5
E 4
E 3
}
E 1
