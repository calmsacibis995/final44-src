h04427
s 00002/00002/00056
d D 8.1 93/06/02 20:07:36 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00056
d D 5.10 92/02/05 11:39:00 bostic 10 9
c don't pass chars to functions
e
s 00005/00000/00053
d D 5.9 91/04/03 16:48:31 bostic 9 8
c protect all user-level include files against reinclusion
e
s 00001/00001/00052
d D 5.8 91/02/23 19:34:15 donn 8 7
c Make unvis() have more reasonable argument types.
e
s 00001/00001/00052
d D 5.7 91/02/23 14:24:20 donn 7 6
c Goof in order of arguments for vis() prototype.
e
s 00002/00000/00051
d D 5.6 91/02/22 08:03:41 donn 6 5
c Added new prototype declarations and cleaned up.
e
s 00007/00009/00044
d D 5.5 91/02/05 17:11:04 bostic 5 4
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00032/00038/00021
d D 5.4 90/06/26 14:22:27 marc 4 3
c new copyright, STDC prototypes, new flags
e
s 00001/00001/00058
d D 5.3 90/05/11 18:21:41 marc 3 2
c oops, cvis -> vis
e
s 00031/00017/00028
d D 5.2 90/05/11 18:20:23 marc 2 1
c cencode.h -> vis.h , re-implementation
e
s 00045/00000/00000
d D 5.1 89/10/13 16:03:54 marc 1 0
c date and time created 89/10/13 16:03:54 by marc
e
u
U
t
T
I 1
D 4
/*
 * Copyright (c) 1989 The Regents of the University of California.
E 4
I 4
/*-
D 11
 * Copyright (c) 1990 The Regents of the University of California.
E 4
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
 */

I 9
#ifndef _VIS_H_
#define	_VIS_H_

E 9
I 2
D 4

E 4
E 2
/*
D 2
 * cencode flags
E 2
I 2
D 4
 * vis flags
E 2
 */
D 2
#define	CENC_CSTYLE	1	/* use C-style backslash sequences */
#define	CENC_GRAPH	2	/* encode as ^? and M- sequences */
#define	CENC_OCTAL	4	/* encode as octal sequences */
#define	CENC_ALL	(CENC_CSTYLE|CENC_GRAPH|CENC_OCTAL)
#define	CENC_WHITE	8	/* encode white-space chars (sp-tb-nl) */
#define	CENC_RACHAR	0x10	/* look at read-ahead char */
E 2

/*
E 4
D 2
 * cdecode flags
E 2
I 2
 * to select alternate encoding format
E 2
 */
D 2
#define	CDEC_HAT	1	/* treat ^ as special */
#define	CDEC_END	2	/* reset decode machine */
E 2
I 2
#define	VIS_OCTAL	0x01	/* use octal \ddd format */
D 4
#define	VIS_CSTYLE	0x02	/* use \[nrft...] where appropiate */
E 4
I 4
#define	VIS_CSTYLE	0x02	/* use \[nrft0..] where appropiate */

E 4
/*
D 4
 * to alter set of characters encoded
 * (default is to encode all non-graphic except space, tab, and newline)
E 4
I 4
 * to alter set of characters encoded (default is to encode all
 * non-graphic except space, tab, and newline).
E 4
 */
D 4
#define	VIS_TAB		0x04	/* also encode tab */
#define	VIS_WHITE	0x08	/* also encode space, tab, and newline */
#define	VIS_SAFE	0x10	/* only encode "unsafe" characters */
E 4
I 4
#define	VIS_SP		0x04	/* also encode space */
#define	VIS_TAB		0x08	/* also encode tab */
#define	VIS_NL		0x10	/* also encode newline */
#define	VIS_WHITE	(VIS_SP | VIS_TAB | VIS_NL)
#define	VIS_SAFE	0x20	/* only encode "unsafe" characters */

E 4
/*
 * other
 */
D 4
#define	VIS_NOSLASH	0x20	/* inhibit printing '\' */
#define	VIS_NEXTC	0x40	/* nextc character is valid */
E 4
I 4
#define	VIS_NOSLASH	0x40	/* inhibit printing '\' */
E 4
E 2

I 2
D 3
extern char *cvis();
E 3
I 3
D 4
extern char *vis();
E 3

E 4
E 2
/*
D 2
 * cdecode return codes
E 2
I 2
D 4
 * unvis flags
E 4
I 4
 * unvis return codes
E 4
E 2
 */
I 4
#define	UNVIS_VALID	 1	/* character valid */
#define	UNVIS_VALIDPUSH	 2	/* character valid, push back passed char */
#define	UNVIS_NOCHAR	 3	/* valid sequence, no character produced */
#define	UNVIS_SYNBAD	-1	/* unrecognized escape sequence */
#define	UNVIS_ERROR	-2	/* decoder in unknown state (unrecoverable) */
E 4
D 2
#define	CDEC_NEEDMORE	0	/* not done, feed another char */
#define	CDEC_OK		1	/* done, character ready */
#define	CDEC_OKPUSH	2	/* done, push back passed char */
#define	CDEC_NOCHAR	3	/* done, no character ready (hidden newline) */
#define	CDEC_SYNBAD	-1	/* unrecognized escape sequence */
E 2

D 2
extern char *cencode();
E 2
I 2
D 4
#define	UNVIS_HAT	0x01	/* treat ^ as special */
#define	UNVIS_END	0x02	/* reset decode machine */

E 4
/*
D 4
 * return codes
E 4
I 4
 * unvis flags
E 4
 */
D 4
#define	UNVIS_NEEDMORE	0	/* not done, feed another char */
#define	UNVIS_OK		1	/* done, character ready */
#define	UNVIS_OKPUSH	2	/* done, push back passed char */
#define	UNVIS_NOCHAR	3	/* done, no character ready (hidden newline) */
#define	UNVIS_SYNBAD	-1	/* unrecognized escape sequence */
E 4
I 4
#define	UNVIS_END	1	/* no more characters */

D 5
#if __STDC__ || c_plusplus
char *vis(char *, char, char, int);
int   strvis(char *, const char *, int);
int   strvisx(char *, const char *, size_t, int);
#else
char *vis();
int   strvis();
int   strvisx();
#endif
E 5
I 5
#include <sys/cdefs.h>

__BEGIN_DECLS
D 7
char	*vis __P((char *, char, char, int));
E 7
I 7
D 10
char	*vis __P((char *, char, int, char));
E 10
I 10
char	*vis __P((char *, int, int, int));
E 10
E 7
int	strvis __P((char *, const char *, int));
int	strvisx __P((char *, const char *, size_t, int));
I 6
int	strunvis __P((char *, const char *));
D 8
int	unvis __P((u_char *, u_char, int *, int));
E 8
I 8
D 10
int	unvis __P((char *, char, int *, int));
E 10
I 10
int	unvis __P((char *, int, int *, int));
E 10
E 8
E 6
__END_DECLS
I 9

#endif /* !_VIS_H_ */
E 9
E 5
E 4
E 2
E 1
