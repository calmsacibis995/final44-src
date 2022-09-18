h10559
s 00002/00002/00008
d D 8.1 93/06/02 20:07:07 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00066/00006
d D 5.8 90/05/15 19:03:05 bostic 10 9
c string.h is the official one
e
s 00053/00011/00019
d D 5.7 90/03/06 16:33:58 bostic 9 8
c add ANSI C prototypes
e
s 00001/00001/00029
d D 5.6 88/12/12 20:41:09 bostic 8 7
c add strdup for S5
e
s 00004/00002/00026
d D 5.5 88/11/16 16:38:53 bostic 7 6
c add strsep, strerror
e
s 00022/00025/00006
d D 5.4 88/09/09 11:49:13 bostic 6 5
c make complete and don't overlap
e
s 00008/00000/00023
d D 5.3 87/11/18 08:42:11 bostic 5 4
c add S5 routines
e
s 00002/00000/00021
d D 5.2 87/08/03 20:10:15 bostic 4 2
c added strcasecmp, strncasecmp
e
s 00002/00000/00021
d R 5.2 87/07/02 09:20:56 bostic 3 2
c added strcasecmp(), strcasencmp()
e
s 00007/00001/00014
d D 5.1 85/05/30 09:40:45 dist 2 1
c Add copyright
e
s 00015/00000/00000
d D 4.1 83/05/26 10:53:48 sam 1 0
c date and time created 83/05/26 10:53:48 by sam
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
D 10
/*
D 6
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
 * Copyright (c) 1988 The Regents of the University of California.
E 10
I 10
/*-
D 11
 * Copyright (c) 1990 The Regents of the University of California.
E 10
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
E 6
 *
I 6
D 10
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
E 10
I 10
 * %sccs.include.redist.c%
E 10
 *
E 6
 *	%W% (Berkeley) %G%
 */
E 2

D 6
/*
 * External function definitions
 * for routines described in string(3).
 */
char	*strcat();
char	*strncat();
int	strcmp();
int	strncmp();
I 4
int	strcasecmp();
int	strncasecmp();
E 4
char	*strcpy();
char	*strncpy();
int	strlen();
char	*index();
char	*rindex();
E 6
I 6
D 9
/* Routines described in string(3) */
char	*strcat(), *strncat(), *strcpy(), *strncpy(), *index(), *rindex();
int	strcmp(), strncmp(), strcasecmp(), strncasecmp(), strlen();
E 6
I 5

D 6
/* S5 compatibility */
char	*strchr();
char	*strrchr();
char	*strpbrk();
int	strspn();
int	strcspn();
char	*strtok();
E 6
I 6
/* Routines described in memory(BA_LIB); System V compatibility */
D 7

E 7
char	*memccpy(), *memchr(), *memcpy(), *memset(), *strchr(),
D 7
	*strpbrk(), *strrchr(), *strtok();
E 7
I 7
D 8
	*strpbrk(), *strrchr(), *strsep(), *strtok();
E 8
I 8
	*strdup(), *strpbrk(), *strrchr(), *strsep(), *strtok();
E 8
E 7
int	memcmp(), strcspn(), strspn();
I 7

/* Routines from ANSI X3J11 */
char	*strerror();
E 9
I 9
D 10
#ifdef __STDC__
extern int memcmp(const char *, const char *, int);
extern int strcasecmp(const char *, const char *);
extern int strcmp(const char *, const char *);
extern int strcspn(const char *, const char *);
extern int strlen(const char *);
extern int strncasecmp(const char *, const char *, int);
extern int strncmp(const char *, const char *, int);
extern int strspn(const char *, const char *);
extern char *index(const char *, int);
extern char *memccpy(char *, const char *, int, int);
extern char *memchr(const char *, int, int);
extern char *memcpy(char *, const char *, int);
extern char *memset(char *, int, int);
extern char *rindex(const char *, int);
extern char *strcat(char *, const char *);
extern char *strchr(const char *, int);
extern char *strcpy(char *, const char *);
extern char *strdup(const char *);
extern char *strerror(int);
extern char *strncat(char *, const char *, int);
extern char *strncpy(char *, const char *, int);
extern char *strpbrk(const char *, const char *);
extern char *strrchr(const char *, int);
extern char *strsep(char *, const char *);
extern char *strtok(char *, const char *);
#else
extern int memcmp();
extern int strcasecmp();
extern int strcmp();
extern int strcspn();
extern int strlen();
extern int strncasecmp();
extern int strncmp();
extern int strspn();
extern char *index();
extern char *memccpy();
extern char *memchr();
extern char *memcpy();
extern char *memset();
extern char *rindex();
extern char *strcat();
extern char *strchr();
extern char *strcpy();
extern char *strdup();
extern char *strerror();
extern char *strncat();
extern char *strncpy();
extern char *strpbrk();
extern char *strrchr();
extern char *strsep();
extern char *strtok();
#endif
E 10
I 10
#include <string.h>
E 10
E 9
E 7
E 6
E 5
E 1
