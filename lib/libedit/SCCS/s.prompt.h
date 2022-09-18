h43188
s 00002/00002/00031
d D 8.1 93/06/04 16:51:54 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00033
d D 5.3 92/07/03 00:23:52 christos 3 2
c Up-to-date with cornell's last RCS version
e
s 00001/00001/00032
d D 5.2 92/06/22 18:24:02 marc 2 1
c merge editline.h and history.h
e
s 00033/00000/00000
d D 5.1 92/06/22 18:08:30 bostic 1 0
c date and time created 92/06/22 18:08:30 by bostic
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
 * el.prompt.h: Prompt printing stuff
 */
#ifndef _h_el_prompt
#define _h_el_prompt

D 2
#include "editline.h"
E 2
I 2
#include "histedit.h"
E 2

typedef char * (*el_pfunc_t) __P((EditLine*));

typedef struct el_prompt_t {
    el_pfunc_t p_func;		/* Function to return the prompt	*/
    coord_t    p_pos;		/* position in the line after prompt	*/
} el_prompt_t;

protected void prompt_print	__P((EditLine *));
protected int  prompt_set	__P((EditLine *, el_pfunc_t));
protected int  prompt_init	__P((EditLine *));
protected void prompt_end	__P((EditLine *));

#endif /* _h_el_prompt */
E 1
