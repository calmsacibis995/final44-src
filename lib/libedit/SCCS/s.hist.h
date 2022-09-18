h26692
s 00002/00002/00047
d D 8.1 93/06/04 16:51:19 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00049
d D 5.3 92/07/03 00:23:43 christos 3 2
c Up-to-date with cornell's last RCS version
e
s 00001/00002/00048
d D 5.2 92/06/22 18:24:01 marc 2 1
c merge editline.h and history.h
e
s 00050/00000/00000
d D 5.1 92/06/22 18:08:17 bostic 1 0
c date and time created 92/06/22 18:08:17 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Christos Zoulas of Cornell University.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * el.hist.c: History functions
 */
#ifndef _h_el_hist
#define _h_el_hist

D 2
#include "editline.h"
#include "history.h"
E 2
I 2
#include "histedit.h"
E 2

typedef const HistEvent *	(*hist_fun_t) __P((ptr_t, int, ...));

typedef struct el_history_t {
    char *buf;				/* The history buffer		*/
    char *last;				/* The last character		*/
    int eventno;			/* Event we are looking for	*/
    ptr_t ref;				/* Argument for history fcns	*/
    hist_fun_t fun;			/* Event access			*/
    const HistEvent *ev;		/* Event cookie			*/
} el_history_t;

#define HIST_FUN(el, fn, arg)	\
    ((((el)->el_history.ev = \
       (*(el)->el_history.fun)((el)->el_history.ref, fn, arg)) == NULL) ? \
     NULL : (el)->el_history.ev->str)

#define	HIST_NEXT(el)		HIST_FUN(el, H_NEXT, NULL)
#define	HIST_FIRST(el)		HIST_FUN(el, H_FIRST, NULL)
#define	HIST_LAST(el)		HIST_FUN(el, H_LAST, NULL)
#define	HIST_PREV(el)		HIST_FUN(el, H_PREV, NULL)
#define	HIST_EVENT(el, num)	HIST_FUN(el, H_EVENT, num)

protected int 		hist_init	__P((EditLine *));
protected void 		hist_end	__P((EditLine *));
protected el_action_t	hist_get	__P((EditLine *));
protected int		hist_set	__P((EditLine *, hist_fun_t, ptr_t));
protected int		hist_list	__P((EditLine *, int, char **));

#endif /* _h_el_hist */
E 1
