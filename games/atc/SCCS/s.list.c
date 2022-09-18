h14188
s 00002/00002/00087
d D 8.1 93/05/31 16:03:58 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00014/00000/00075
d D 5.2 90/04/30 21:24:14 bostic 2 1
c Berkeley headers, SCCS id's
e
s 00075/00000/00000
d D 5.1 90/04/30 21:00:34 bostic 1 0
c date and time created 90/04/30 21:00:34 by bostic
e
u
U
t
T
I 2
/*-
D 3
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Ed James.
 *
 * %sccs.include.redist.c%
 */

E 2
I 1
/*
 * Copyright (c) 1987 by Ed James, UC Berkeley.  All rights reserved.
 *
 * Copy permission is hereby granted provided that this notice is
 * retained on all partial or complete copies.
 *
 * For more info on this and all of my stuff, mail edjames@berkeley.edu.
 */
I 2

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

#include "include.h"

PLANE	*
newplane()
{
	return ((PLANE *) calloc(1, sizeof (PLANE)));
}

append(l, p)
	LIST	*l;
	PLANE	*p;
{
	PLANE 	*q = NULL, *r = NULL;

	if (l->head == NULL) {
		p->next = p->prev = NULL;
		l->head = l->tail = p;
	} else {
		q = l -> head;

		while (q != NULL && q->plane_no < p->plane_no) {
			r = q;
			q = q -> next;
		}

		if (q) {
			if (r) {
				p->prev = r;
				r->next = p;
				p->next = q;
				q->prev = p;
			} else {
				p->next = q;
				p->prev = NULL;
				q->prev = p;
				l->head = p;
			}
		} else {
			l->tail->next = p;
			p->next = NULL;
			p->prev = l->tail;
			l->tail = p;
		}
	}
}

delete(l, p)
	LIST	*l;
	PLANE	*p;
{
	if (l->head == NULL)
		loser(p, "deleted a non-existant plane! Get help!");
	
	if (l->head == p && l->tail == p)
		l->head = l->tail = NULL;
	else if (l->head == p) {
		l->head = p->next;
		l->head->prev = NULL;
	} else if (l->tail == p) {
		l->tail = p->prev;
		l->tail->next = NULL;
	} else {
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}
}
E 1
