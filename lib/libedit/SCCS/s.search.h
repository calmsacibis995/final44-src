h23034
s 00002/00002/00040
d D 8.1 93/06/04 16:52:10 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00041
d D 5.3 92/07/03 00:23:56 christos 3 2
c Up-to-date with cornell's last RCS version
e
s 00001/00001/00040
d D 5.2 92/06/22 18:24:04 marc 2 1
c merge editline.h and history.h
e
s 00041/00000/00000
d D 5.1 92/06/22 18:08:35 bostic 1 0
c date and time created 92/06/22 18:08:35 by bostic
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
 * el.search.h: Line and history searching utilities
 */
#ifndef _h_el_search 
#define _h_el_search 

D 2
#include "editline.h"
E 2
I 2
#include "histedit.h"
E 2

typedef struct el_search_t {
    char *patbuf;		/* The pattern buffer		*/
    int  patlen;		/* Length of the pattern buffer	*/
    int  patdir;		/* Direction of the last search	*/
    int  chadir;		/* Character search direction	*/
    char chacha;		/* Character we are looking for	*/
} el_search_t;


I 3
protected int 		el_match	__P((const char *, const char *));
E 3
protected int		search_init	__P((EditLine *));
protected void		search_end	__P((EditLine *));
protected int		c_hmatch	__P((EditLine *, const char *));
protected void		c_setpat	__P((EditLine *));
protected el_action_t	ce_inc_search	__P((EditLine *, int));
protected el_action_t	cv_search	__P((EditLine *, int));
protected el_action_t	ce_search_line	__P((EditLine *, char *, int));
protected el_action_t	cv_repeat_srch	__P((EditLine *, int));
protected el_action_t	cv_csearch_back	__P((EditLine *, int, int, int));
protected el_action_t	cv_csearch_fwd	__P((EditLine *, int, int, int));

#endif /* _h_el_search */
E 1
