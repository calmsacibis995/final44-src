h38803
s 00001/00000/00051
d D 8.4 95/04/21 09:56:45 eric 34 33
c update copyright notice
e
s 00001/00001/00050
d D 8.3 95/03/31 15:21:30 eric 33 32
c change "bool" to be an int -- prototypes just don't grok it otherwise
e
s 00006/00002/00045
d D 8.2 93/09/24 06:44:16 eric 32 31
c ANSI C
e
s 00002/00002/00045
d D 8.1 93/06/07 10:32:36 bostic 31 30
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00009/00047
d D 6.6 93/05/17 10:28:05 eric 30 29
c first cut at merged map/alias implementation
e
s 00006/00004/00050
d D 6.5 93/04/18 09:47:27 eric 29 28
c oops...  fix botch in previous delta
e
s 00003/00003/00051
d D 6.4 93/04/18 09:33:16 eric 28 27
c use UCB standard for __P
e
s 00007/00000/00047
d D 6.3 93/04/18 09:32:03 eric 27 26
c add defines for prototype compatibility
e
s 00003/00003/00044
d D 6.2 93/03/31 07:19:29 eric 26 25
c ANSI changes
e
s 00000/00000/00047
d D 6.1 92/12/21 16:08:05 eric 25 24
c Release 6
e
s 00004/00014/00043
d D 4.7 92/11/14 11:32:35 eric 24 23
m 
c (partially) ANSI-fy it
e
s 00001/00011/00056
d D 4.6 90/06/01 19:04:56 bostic 23 22
m new
m copyright
m notice
c 
e
s 00000/00010/00067
d D 4.5 88/12/28 20:34:39 bostic 22 21
m 
c cleanup; remove V6 and VMUNIX
e
s 00010/00005/00067
d D 4.4 88/06/29 21:56:18 bostic 21 20
m install
m approved
m copyright
m notice
c install approved copyright notice
e
s 00012/00004/00060
d D 4.3 88/03/24 14:50:55 bostic 20 19
m 
c add Berkeley specific headers
e
s 00000/00001/00064
d D 4.2 87/10/22 20:03:32 bostic 19 18
m ANSI
m C;
m sprintf
m now
m returns
m an
m int.
c ANSI C; sprintf now returns an int.
e
s 00000/00000/00065
d D 4.1 83/07/25 19:10:51 eric 18 17
m 
c 4.2 release version
e
s 00004/00004/00061
d D 3.13 83/03/26 12:42:39 eric 17 16
m 214
c u_short should be unsigned short; actually this is a punt
e
s 00001/00001/00064
d D 3.12 83/03/26 12:12:41 eric 16 15
m 214
c Undo glickman's change of types.h => param.h -- why did he do this?
e
s 00006/00000/00059
d D 3.11 83/01/04 10:54:16 eric 15 14
m 
c add min and max
e
s 00001/00001/00058
d D 3.10 82/06/07 22:19:14 eric 14 13
c make bitset work even on an implicit cast to bool across subr calls
e
s 00001/00001/00058
d D 3.9 82/05/05 20:26:40 eric 13 12
c (glickman) Changed include of types.h to param.h for ndir.h.
e
s 00003/00002/00056
d D 3.8 82/03/22 22:02:15 eric 12 11
c make better assumptions about definition of u_long, etc.
e
s 00020/00001/00038
d D 3.7 81/12/06 12:39:00 eric 11 10
c cleanup so it will go through lint without any fancy grep -v's;
c change the way SCCS Id's are handled.
e
s 00002/00002/00037
d D 3.6 81/12/05 12:13:28 eric 10 9
c add strncpy and strncat
e
s 00001/00001/00038
d D 3.5 81/11/08 17:26:37 eric 9 8
c LINT
e
s 00006/00001/00033
d D 3.4 81/09/24 10:30:34 eric 8 7
c changes to work under a V6 system -- mostly compilation flags
e
s 00007/00003/00027
d D 3.3 81/08/17 09:37:30 eric 7 6
c cleanup -- dispose of setbit clrbit rot, include sys/types.h
e
s 00013/00000/00017
d D 3.2 81/08/09 15:03:10 eric 6 5
c lint it
e
s 00004/00000/00013
d D 3.1 81/03/07 14:27:12 eric 5 4
c ----- delivermail ==> postbox -----
e
s 00000/00000/00013
d D 2.1 80/11/05 11:00:03 eric 4 3
c release 2
e
s 00001/00001/00012
d D 1.3 80/10/11 18:11:13 eric 3 2
c cleanup to simplify configuration & fix minor bugs
e
s 00002/00000/00011
d D 1.2 80/07/25 22:02:10 eric 2 1
c add ID keywords
e
s 00011/00000/00000
d D 1.1 80/05/14 10:05:27 eric 1 0
e
u
bostic
eric
U
f b 
f i 
t
T
I 1
/*
I 34
 * Copyright (c) 1995 Eric P. Allman
E 34
D 20
**  USEFUL.H -- Some useful stuff.
I 2
**
D 11
**	%W%	%G%
E 11
I 11
**	%W%	%Y%	%G%
E 11
E 2
*/
E 20
I 20
D 31
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 31
I 31
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 31
 *
D 23
 * Redistribution and use in source and binary forms are permitted
D 21
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 21
I 21
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
E 23
I 23
 * %sccs.include.redist.c%
E 23
E 21
 *
 *	%W% (Berkeley) %G%
 */
E 20

D 3
# define bool	int
E 3
I 3
D 7
# define bool	char
E 7
I 7
D 22
# ifndef makedev
E 22
D 13
# include <sys/types.h>
E 13
I 13
D 16
# include <sys/param.h>
E 16
I 16
# include <sys/types.h>
E 16
E 13
D 22
# endif
E 22

I 27
D 30
/* support for ANSI prototypes (or not, as the case may be) */
D 28
#if defined(__STDC__) && defined(_FORGIVING_CC_)
#define P(protos)	protos
E 28
I 28
D 29
#if defined(__STDC__) && defined(_FORGIVING_CC_) && !defined(__P)
#define __P(protos)	protos
E 28
#else
D 28
#define P(protos)	()
E 28
I 28
#define __P(protos)	()
E 29
I 29
#ifndef __P
# if defined(__STDC__) && defined(_FORGIVING_CC_)
#  define __P(protos)	protos
# else
#  define __P(protos)	()
# endif
E 29
E 28
#endif

E 30
E 27
/* support for bool type */
D 33
typedef char	bool;
E 33
I 33
typedef int	bool;
E 33
E 7
E 3
# define TRUE	1
# define FALSE	0

# ifndef NULL
# define NULL	0
D 24
# endif NULL
E 24
I 24
# endif /* NULL */
E 24
I 5

D 7
# define setbit(bit, word)	(word |= bit)
# define clrbit(bit, word)	(word &= ~bit)
E 7
I 7
/* bit hacking */
E 7
D 14
# define bitset(bit, word)	((word) & (bit))
E 14
I 14
# define bitset(bit, word)	(((word) & (bit)) != 0)
E 14
I 11

I 15
/* some simple functions */
# ifndef max
# define max(a, b)	((a) > (b) ? (a) : (b))
# define min(a, b)	((a) < (b) ? (a) : (b))
D 26
# endif max
E 26
I 26
# endif
E 26

E 15
/* assertions */
# ifndef NASSERT
# define ASSERT(expr, msg, parm)\
	if (!(expr))\
	{\
		fprintf(stderr, "assertion botch: %s:%d: ", __FILE__, __LINE__);\
		fprintf(stderr, msg, parm);\
	}
D 24
# else NASSERT
E 24
I 24
# else /* NASSERT */
E 24
# define ASSERT(expr, msg, parm)
D 24
# endif NASSERT
E 24
I 24
# endif /* NASSERT */
E 24

/* sccs id's */
# ifndef lint
D 32
# define SCCSID(arg)	static char SccsId[] = "arg";
E 32
I 32
#  ifdef __STDC__
#   define SCCSID(arg)	static char SccsId[] = #arg;
#  else
#   define SCCSID(arg)	static char SccsId[] = "arg";
#  endif
E 32
D 24
# else lint
E 24
I 24
D 26
# else /* lint */
E 26
I 26
# else
E 26
E 24
D 32
# define SCCSID(arg)
E 32
I 32
#  define SCCSID(arg)
E 32
D 26
# endif lint
E 26
I 26
# endif
E 26
E 11
I 6
D 24

/* define the types of some common functions */
D 10
extern char	*strcpy();
extern char	*strcat();
E 10
I 10
extern char	*strcpy(), *strncpy();
extern char	*strcat(), *strncat();
E 10
extern char	*malloc();
extern char	*index(), *rindex();
extern int	errno;
D 19
extern char	*sprintf();
E 19
D 9
extern long	time();
E 9
I 9
extern time_t	time();
E 9
extern char	*ctime();
D 22
# ifndef V6
E 22
extern char	*getenv();
E 24
D 8
# endif
E 8
I 8
D 12
# else V6
E 12
I 12
D 22
# endif V6
# ifndef VMUNIX
E 12
D 17
typedef char	*u_short;
typedef long	u_long;
typedef char	u_char;
typedef int	void;
E 17
I 17
typedef unsigned short	u_short;
typedef long		u_long;
typedef char		u_char;
typedef int		void;
E 17
D 12
# endif V6
E 12
I 12
# endif VMUNIX
E 22
E 12
E 8
E 6
E 5
E 1
