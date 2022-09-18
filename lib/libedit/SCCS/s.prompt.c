h64975
s 00002/00002/00095
d D 8.1 93/06/04 16:51:51 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00094
d D 5.2 92/07/03 00:23:51 christos 2 1
c Up-to-date with cornell's last RCS version
e
s 00097/00000/00000
d D 5.1 92/06/22 18:08:29 bostic 1 0
c date and time created 92/06/22 18:08:29 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Christos Zoulas of Cornell University.
 *
 * %sccs.include.redist.c%
 */

D 2
#ifndef lint
E 2
I 2
#if !defined(lint) && !defined(SCCSID)
E 2
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif /* not lint */
E 2
I 2
#endif /* not lint && not SCCSID */
E 2

/*
D 2
 * el.prompt.c: Prompt printing functions
E 2
I 2
 * prompt.c: Prompt printing functions
E 2
 */
#include "sys.h"
#include <stdio.h>
#include "el.h"

private char *prompt_default	__P((EditLine *));

/* prompt_default():
 *	Just a default prompt, in case the user did not provide one
 */
private char *
/*ARGSUSED*/
prompt_default(el)
    EditLine *el;
{
    static char a[3] = { '?', ' ', '\0' };
    return a;
}


/* prompt_print():
 *	Print the prompt and update the prompt position.
 *	We use an array of integers in case we want to pass
 * 	literal escape sequences in the prompt and we want a
 *	bit to flag them
 */
protected void
prompt_print(el)
    EditLine *el;
{
    char *p = (*el->el_prompt.p_func)(el);
    while (*p)
	re_putc(el, *p++);

    el->el_prompt.p_pos.v = el->el_refresh.r_cursor.v;
    el->el_prompt.p_pos.h = el->el_refresh.r_cursor.h;

} /* end prompt_print */


/* prompt_init():
 *	Initialize the prompt stuff
 */
protected int 
prompt_init(el)
    EditLine *el;
{
    el->el_prompt.p_func = prompt_default;
    el->el_prompt.p_pos.v = 0;
    el->el_prompt.p_pos.h = 0;
    return 0;
} /* end prompt_init */


/* prompt_end():
 *	Clean up the prompt stuff
 */
protected void
/*ARGSUSED*/ 
prompt_end(el)
    EditLine *el;
{
} /* end prompt_end */


/* prompt_set():
 *	Install a prompt printing function
 */
protected int 
prompt_set(el, prf)
    EditLine *el;
    el_pfunc_t prf;
{
    if (prf == NULL)
	el->el_prompt.p_func = prompt_default;
    else
	el->el_prompt.p_func = prf;
    el->el_prompt.p_pos.v = 0;
    el->el_prompt.p_pos.h = 0;
    return 0;
} /* end prompt_set */
E 1
