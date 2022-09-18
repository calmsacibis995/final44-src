h19387
s 00002/00002/00065
d D 8.1 93/06/02 20:07:04 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00064
d D 5.11 92/06/22 21:27:44 bostic 11 10
c prefix all ANSI #define's with BSD_ so don't collide with other vendors
e
s 00001/00001/00066
d D 5.10 91/03/09 17:56:07 bostic 10 9
c create {hp300,i386,tahoe,vax}/include/ansi.h
e
s 00001/00001/00066
d D 5.9 91/02/24 14:09:09 bostic 9 8
c swab takes void *'s, not char *'s
e
s 00003/00003/00064
d D 5.8 91/02/22 10:18:54 bostic 8 7
c b{cmp,copy,zero} all take void *, not char *
e
s 00039/00083/00028
d D 5.7 91/02/05 17:10:53 bostic 7 6
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00001/00110
d D 5.6 91/01/20 22:05:33 bostic 6 5
c strsep had an incorrect function prototype
e
s 00002/00002/00109
d D 5.5 91/01/17 13:54:07 bostic 5 4
c kernel reorg, make strmode take an int.
e
s 00007/00008/00104
d D 5.4 90/05/29 19:26:56 bostic 4 3
c C++ wants the prototypes, too
e
s 00106/00014/00006
d D 5.3 90/05/17 16:05:48 bostic 3 2
c start of an ANSI C library
e
s 00015/00024/00005
d D 5.2 88/09/09 11:49:15 bostic 2 1
c make complete and don't overlap
e
s 00029/00000/00000
d D 5.1 85/08/05 21:21:47 kre 1 0
c date and time created 85/08/05 21:21:47 by kre
e
u
U
t
T
I 1
D 3
/*
D 2
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
 * Copyright (c) 1988 The Regents of the University of California.
E 3
I 3
/*-
D 12
 * Copyright (c) 1990 The Regents of the University of California.
E 3
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
E 2
 *
D 2
 *	%W% (Berkeley) %E%
E 2
I 2
D 3
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
E 2
 */

D 3
#include <strings.h>
E 3
I 3
#ifndef _STRING_H_
#define	_STRING_H_
D 5
#include <machine/machtypes.h>
E 5
I 5
D 10
#include <machine/types.h>
E 10
I 10
#include <machine/ansi.h>
E 10
E 5

D 11
#ifdef	_SIZE_T_
typedef	_SIZE_T_	size_t;
#undef	_SIZE_T_
E 11
I 11
#ifdef	_BSD_SIZE_T_
typedef	_BSD_SIZE_T_	size_t;
#undef	_BSD_SIZE_T_
E 11
#endif

#ifndef	NULL
#define	NULL	0
#endif

D 4
/* ANSI C standard routines */
#ifdef __STDC__
E 4
I 4
D 7
#if __STDC__ || c_plusplus
E 7
I 7
#include <sys/cdefs.h>
E 7
E 4

D 7
void	*memchr(const void *, int, size_t);
int	 memcmp(const void *, const void *, size_t);
void	*memcpy(void *, const void *, size_t);
void	*memmove(void *, const void *, size_t);
void	*memset(void *, int, size_t);
char	*strcat(char *, const char *);
char	*strchr(const char *, int);
int	 strcmp(const char *, const char *);
int	 strcoll(const char *, const char *);
char	*strcpy(char *, const char *);
size_t	 strcspn(const char *, const char *);
char	*strerror(int);
size_t	 strlen(const char *);
char	*strncat(char *, const char *, size_t);
int	 strncmp(const char *, const char *, size_t);
char	*strncpy(char *, const char *, size_t);
char	*strpbrk(const char *, const char *);
char	*strrchr(const char *, int);
size_t	 strspn(const char *, const char *);
char	*strstr(const char *, const char *);
char	*strtok(char *, const char *);
size_t	 strxfrm(char *, const char *, size_t);
E 7
I 7
__BEGIN_DECLS
void	*memchr __P((const void *, int, size_t));
int	 memcmp __P((const void *, const void *, size_t));
void	*memcpy __P((void *, const void *, size_t));
void	*memmove __P((void *, const void *, size_t));
void	*memset __P((void *, int, size_t));
char	*strcat __P((char *, const char *));
char	*strchr __P((const char *, int));
int	 strcmp __P((const char *, const char *));
int	 strcoll __P((const char *, const char *));
char	*strcpy __P((char *, const char *));
size_t	 strcspn __P((const char *, const char *));
char	*strerror __P((int));
size_t	 strlen __P((const char *));
char	*strncat __P((char *, const char *, size_t));
int	 strncmp __P((const char *, const char *, size_t));
char	*strncpy __P((char *, const char *, size_t));
char	*strpbrk __P((const char *, const char *));
char	*strrchr __P((const char *, int));
size_t	 strspn __P((const char *, const char *));
char	*strstr __P((const char *, const char *));
char	*strtok __P((char *, const char *));
size_t	 strxfrm __P((char *, const char *, size_t));
E 7

D 4
#else /* !__STDC__ */
E 4
I 4
D 7
#else
E 4

void	*memchr();
int	 memcmp();
void	*memcpy();
void	*memmove();
void	*memset();
char	*strcat();
char	*strchr();
int	 strcmp();
int	 strcoll();
char	*strcpy();
size_t	 strcspn();
char	*strerror();
size_t	 strlen();
char	*strncat();
int	 strncmp();
char	*strncpy();
char	*strpbrk();
char	*strrchr();
size_t	 strspn();
char	*strstr();
char	*strtok();
size_t	 strxfrm();

D 4
#endif /* __STDC__ */
E 4
I 4
#endif
E 4

E 7
/* Nonstandard routines */
#ifndef _ANSI_SOURCE
D 4
#ifdef __STDC__ */
E 4
I 4
D 7
#if __STDC__ || c_plusplus
E 4

int	 bcmp(const char *, const char *, size_t);
void	 bcopy(const char *, char *, size_t);
void	 bzero(char *, size_t);
int	 ffs(int);
char	*index(const char *, int);
void	*memccpy(void *, const void *, int, size_t);
char	*rindex(const char *, int);
int	 strcasecmp(const char *, const char *);
char	*strdup(const char *);
D 5
void	 strmode(mode_t, char *);
E 5
I 5
void	 strmode(int, char *);
E 5
int	 strncasecmp(const char *, const char *, size_t);
D 6
char	*strsep(char *, const char *);
E 6
I 6
char	*strsep(char **, const char *);
E 6
void	 swab(const char *, char *, size_t);

D 4
#else /* !__STDC__ */
E 4
I 4
#else
E 4

int	 bcmp();
void	 bcopy();
void	 bzero();
int	 ffs();
char	*index();
void	*memccpy();
char	*rindex();
int	 strcasecmp();
char	*strdup();
void	strmode();
int	 strncasecmp();
char	*strsep();
void	 swab();

D 4
#endif /* __STDC__ */
#endif /* _ANSI_SOURCE */
E 4
I 4
#endif
E 7
I 7
D 8
int	 bcmp __P((const char *, const char *, size_t));
void	 bcopy __P((const char *, char *, size_t));
void	 bzero __P((char *, size_t));
E 8
I 8
int	 bcmp __P((const void *, const void *, size_t));
void	 bcopy __P((const void *, void *, size_t));
void	 bzero __P((void *, size_t));
E 8
int	 ffs __P((int));
char	*index __P((const char *, int));
void	*memccpy __P((void *, const void *, int, size_t));
char	*rindex __P((const char *, int));
int	 strcasecmp __P((const char *, const char *));
char	*strdup __P((const char *));
void	 strmode __P((int, char *));
int	 strncasecmp __P((const char *, const char *, size_t));
char	*strsep __P((char **, const char *));
D 9
void	 swab __P((const char *, char *, size_t));
E 9
I 9
void	 swab __P((const void *, void *, size_t));
E 9
E 7
#endif 
I 7
__END_DECLS

E 7
E 4
#endif /* _STRING_H_ */
E 3
D 2

/*
 * these next few are obsolete trash
 */

extern char *strcpyn();
extern char *strcatn();
extern int strcmpn();

/*
 * and the rest are Sys5 functions supported just so
 * Sys5 progs will compile easily.
 */

extern char *strchr();
extern char *strrchr();
extern char *strpbrk();
extern int strspn();
extern int strcspn();
extern char *strtok();
E 2
E 1
