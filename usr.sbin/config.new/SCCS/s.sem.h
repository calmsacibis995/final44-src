h20130
s 00002/00002/00033
d D 8.1 93/06/06 13:55:11 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00035
d D 5.2 93/04/18 04:23:20 torek 2 1
c rm rcs headers (commit to maintenance on vangogh)
e
s 00037/00000/00000
d D 5.1 93/01/12 02:18:46 torek 1 0
c date and time created 93/01/12 02:18:46 by torek
e
u
U
t
T
I 1
/* 
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Lawrence Berkeley Laboratories.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
D 2
 *
 * from: $Header: sem.h,v 1.5 93/01/12 03:57:14 torek Exp $
E 2
 */

void		enddefs __P((const char *));

void		setdefmaxusers __P((int, int, int));
void		setmaxusers __P((int));
int		defattr __P((const char *, struct nvlist *));
void		defdev __P((struct devbase *, int, struct nvlist *,
			struct nvlist *, struct nvlist *, struct nvlist *));
struct devbase *getdevbase __P((const char *name));
struct attr    *getattr __P((const char *name));
void		setmajor __P((struct devbase *d, int n));
void		addconf __P((struct config *));
void		setconf __P((struct nvlist **, const char *, struct nvlist *));
void		adddev __P((const char *, const char *, struct nvlist *, int));
void		addpseudo __P((const char *name, int number));
const char     *ref __P((const char *name));
const char     *starref __P((const char *name));
const char     *wildref __P((const char *name));
E 1
