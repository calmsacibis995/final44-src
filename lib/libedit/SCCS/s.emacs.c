h56473
s 00002/00002/00480
d D 8.1 93/06/04 16:51:13 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00479
d D 5.2 92/07/03 00:23:42 christos 2 1
c Up-to-date with cornell's last RCS version
e
s 00482/00000/00000
d D 5.1 92/06/22 18:08:15 bostic 1 0
c date and time created 92/06/22 18:08:15 by bostic
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
 * el.emacs.c: Emacs functions
E 2
I 2
 * emacs.c: Emacs functions
E 2
 */
#include "sys.h"
#include "el.h"

/* em_delete_or_list():
 *	Delete character under cursor or list completions if at end of line
 *	[^D]
 */
protected el_action_t
/*ARGSUSED*/
em_delete_or_list(el, c)
    EditLine *el;
    int c;
{
    if (el->el_line.cursor == el->el_line.lastchar) {	/* if I'm at the end */
#ifdef notyet
	if (el->el_line.cursor == el->el_line.buffer) {	/* and the beginning */
#endif
	    term_overwrite(el, STReof, 4);/* then do a EOF */
	    term__flush();
	    return CC_EOF;
#ifdef notyet
	}
	else {
	    re_goto_bottom(el);
	    *el->el_line.lastchar = '\0';		/* just in case */
	    return CC_LIST_CHOICES;
	}
#endif
    }
    else {
	c_delafter(el, el->el_state.argument);	/* delete after dot */
	if (el->el_line.cursor > el->el_line.lastchar)
	    el->el_line.cursor = el->el_line.lastchar;	/* bounds check */
	return CC_REFRESH;
    }
}


/* em_delete_next_word():
 *	Cut from cursor to end of current word
 *	[M-d]
 */
protected el_action_t
/*ARGSUSED*/
em_delete_next_word(el, c)
    EditLine *el;
    int c;
{
    char *cp, *p, *kp;

    if (el->el_line.cursor == el->el_line.lastchar)
	return CC_ERROR;

    cp = c__next_word(el->el_line.cursor, el->el_line.lastchar, 
		      el->el_state.argument, ce__isword);

    for (p = el->el_line.cursor, kp = el->el_chared.c_kill.buf; p < cp; p++)
	/* save the text */
	*kp++ = *p;
    el->el_chared.c_kill.last = kp;

    c_delafter(el, cp - el->el_line.cursor);		/* delete after dot */
    if (el->el_line.cursor > el->el_line.lastchar)
	el->el_line.cursor = el->el_line.lastchar;	/* bounds check */
    return CC_REFRESH;
}


/* em_yank():
 *	Paste cut buffer at cursor position
 *	[^Y]
 */
protected el_action_t
/*ARGSUSED*/
em_yank(el, c)
    EditLine *el;
    int c;
{
    char *kp, *cp;

    if (el->el_chared.c_kill.last == el->el_chared.c_kill.buf)
	return CC_ERROR;

    if (el->el_line.lastchar + 
	(el->el_chared.c_kill.last - el->el_chared.c_kill.buf) >= 
	el->el_line.limit)
	return CC_ERROR;

    el->el_chared.c_kill.mark = el->el_line.cursor;
    cp = el->el_line.cursor;

    /* open the space, */
    c_insert(el, el->el_chared.c_kill.last - el->el_chared.c_kill.buf);	
    /* copy the chars */
    for (kp = el->el_chared.c_kill.buf; kp < el->el_chared.c_kill.last; kp++)	
	*cp++ = *kp;

    /* if an arg, cursor at beginning else cursor at end */
    if (el->el_state.argument == 1)		
	el->el_line.cursor = cp;

    return CC_REFRESH;
}


/* em_kill_line():
 *	Cut the entire line and save in cut buffer
 *	[^U]
 */
protected el_action_t
/*ARGSUSED*/
em_kill_line(el, c)
    EditLine *el;
    int c;
{
    char *kp, *cp;

    cp = el->el_line.buffer;
    kp = el->el_chared.c_kill.buf;
    while (cp < el->el_line.lastchar)
	*kp++ = *cp++;		/* copy it */
    el->el_chared.c_kill.last = kp;
    el->el_line.lastchar = el->el_line.buffer;	/* zap! -- delete all of it */
    el->el_line.cursor = el->el_line.buffer;
    return CC_REFRESH;
}


/* em_kill_region():
 *	Cut area between mark and cursor and save in cut buffer
 *	[^W]
 */
protected el_action_t
/*ARGSUSED*/
em_kill_region(el, c)
    EditLine *el;
    int c;
{
    char *kp, *cp;

    if (!el->el_chared.c_kill.mark)
	return CC_ERROR;

    if (el->el_chared.c_kill.mark > el->el_line.cursor) {
	cp = el->el_line.cursor;
	kp = el->el_chared.c_kill.buf;
	while (cp < el->el_chared.c_kill.mark)
	    *kp++ = *cp++;	/* copy it */
	el->el_chared.c_kill.last = kp;
	c_delafter(el, cp - el->el_line.cursor);
    }
    else {			/* mark is before cursor */
	cp = el->el_chared.c_kill.mark;
	kp = el->el_chared.c_kill.buf;
	while (cp < el->el_line.cursor)
	    *kp++ = *cp++;	/* copy it */
	el->el_chared.c_kill.last = kp;
	c_delbefore(el, cp - el->el_chared.c_kill.mark);
	el->el_line.cursor = el->el_chared.c_kill.mark;
    }
    return CC_REFRESH;
}


/* em_copy_region():
 *	Copy area between mark and cursor to cut buffer
 *	[M-W]
 */
protected el_action_t
/*ARGSUSED*/
em_copy_region(el, c)
    EditLine *el;
    int c;
{
    char *kp, *cp;

    if (el->el_chared.c_kill.mark)
	return CC_ERROR;

    if (el->el_chared.c_kill.mark > el->el_line.cursor) {
	cp = el->el_line.cursor;
	kp = el->el_chared.c_kill.buf;
	while (cp < el->el_chared.c_kill.mark)
	    *kp++ = *cp++;	/* copy it */
	el->el_chared.c_kill.last = kp;
    }
    else {
	cp = el->el_chared.c_kill.mark;
	kp = el->el_chared.c_kill.buf;
	while (cp < el->el_line.cursor)
	    *kp++ = *cp++;	/* copy it */
	el->el_chared.c_kill.last = kp;
    }
    return CC_NORM;
}


/* em_gosmacs_traspose():
 *	Exchange the two characters before the cursor
 *	Gosling emacs transpose chars [^T]
 */
protected el_action_t
em_gosmacs_traspose(el, c)
    EditLine *el;
    int c;
{

    if (el->el_line.cursor > &el->el_line.buffer[1]) {
   	/* must have at least two chars entered */
	c = el->el_line.cursor[-2];
	el->el_line.cursor[-2] = el->el_line.cursor[-1];
	el->el_line.cursor[-1] = c;
	return CC_REFRESH;
    }
    else 
	return CC_ERROR;
}


/* em_next_word():
 *	Move next to end of current word
 *	[M-f]
 */
protected el_action_t
/*ARGSUSED*/
em_next_word(el, c)
    EditLine *el;
    int c;
{
    if (el->el_line.cursor == el->el_line.lastchar)
	return CC_ERROR;

    el->el_line.cursor = c__next_word(el->el_line.cursor, el->el_line.lastchar, 
				      el->el_state.argument,
				      ce__isword);

    if (el->el_map.type == MAP_VI) 
	if (el->el_chared.c_vcmd.action & DELETE) {
	    cv_delfini(el);
	    return CC_REFRESH;
	}

    return CC_CURSOR;
}

/* em_upper_case():
 *	Uppercase the characters from cursor to end of current word
 *	[M-u]
 */
protected el_action_t
/*ARGSUSED*/
em_upper_case(el, c)
    EditLine *el;
    int c;
{
    char   *cp, *ep;

    ep = c__next_word(el->el_line.cursor, el->el_line.lastchar, 
		      el->el_state.argument, ce__isword);

    for (cp = el->el_line.cursor; cp < ep; cp++)
	if (islower(*cp))
	    *cp = toupper(*cp);

    el->el_line.cursor = ep;
    if (el->el_line.cursor > el->el_line.lastchar)
	el->el_line.cursor = el->el_line.lastchar;
    return CC_REFRESH;
}


/* em_capitol_case():
 *	Capitalize the characters from cursor to end of current word
 *	[M-c]
 */
protected el_action_t
/*ARGSUSED*/
em_capitol_case(el, c)
    EditLine *el;
    int c;
{
    char   *cp, *ep;

    ep = c__next_word(el->el_line.cursor, el->el_line.lastchar, 
		      el->el_state.argument, ce__isword);

    for (cp = el->el_line.cursor; cp < ep; cp++) {
	if (isalpha(*cp)) {
	    if (islower(*cp))
		*cp = toupper(*cp);
	    cp++;
	    break;
	}
    }
    for (; cp < ep; cp++)
	if (isupper(*cp))
	    *cp = tolower(*cp);

    el->el_line.cursor = ep;
    if (el->el_line.cursor > el->el_line.lastchar)
	el->el_line.cursor = el->el_line.lastchar;
    return CC_REFRESH;
}

/* em_lower_case():
 *	Lowercase the characters from cursor to end of current word
 *	[M-l]
 */
protected el_action_t
/*ARGSUSED*/
em_lower_case(el, c)
    EditLine *el;
    int c;
{
    char   *cp, *ep;

    ep = c__next_word(el->el_line.cursor, el->el_line.lastchar, 
		      el->el_state.argument, ce__isword);

    for (cp = el->el_line.cursor; cp < ep; cp++)
	if (isupper(*cp))
	    *cp = tolower(*cp);

    el->el_line.cursor = ep;
    if (el->el_line.cursor > el->el_line.lastchar)
	el->el_line.cursor = el->el_line.lastchar;
    return CC_REFRESH;
}


/* em_set_mark():
 *	Set the mark at cursor
 *	[^@]
 */
protected el_action_t
/*ARGSUSED*/
em_set_mark(el, c)
    EditLine *el;
    int c;
{
    el->el_chared.c_kill.mark = el->el_line.cursor;
    return CC_NORM;
}


/* em_exchange_mark():
 *	Exchange the cursor and mark 
 *	[^X^X]
 */
protected el_action_t
/*ARGSUSED*/
em_exchange_mark(el, c)
    EditLine *el;
    int c;
{
    register char *cp;

    cp = el->el_line.cursor;
    el->el_line.cursor = el->el_chared.c_kill.mark;
    el->el_chared.c_kill.mark = cp;
    return CC_CURSOR;
}

/* em_universal_argument():
 *	Universal argument (argument times 4)
 *	[^U]
 */
protected el_action_t
/*ARGSUSED*/
em_universal_argument(el, c)
    EditLine *el;
    int c;
{				/* multiply current argument by 4 */
    if (el->el_state.argument > 1000000)
	return CC_ERROR;
    el->el_state.doingarg = 1;
    el->el_state.argument *= 4;
    return CC_ARGHACK;
}

/* em_meta_next():
 *	Add 8th bit to next character typed
 *	[<ESC>]
 */
protected el_action_t
/*ARGSUSED*/
em_meta_next(el, c)
    EditLine *el;
    int c;
{
    el->el_state.metanext = 1; 
    return CC_ARGHACK;
}


/* em_toggle_overwrite():
 *	Switch from insert to overwrite mode or vice versa
 */
protected el_action_t
/*ARGSUSED*/
em_toggle_overwrite(el, c)
    EditLine *el;
    int c;
{
    el->el_state.inputmode = 
	(el->el_state.inputmode == MODE_INSERT) ? MODE_REPLACE : MODE_INSERT;
    return CC_NORM;
}


/* em_copy_prev_word():
 *	Copy current word to cursor
 */
protected el_action_t
/*ARGSUSED*/
em_copy_prev_word(el, c)
    EditLine *el;
    int c;
{
    char *cp, *oldc, *dp;

    if (el->el_line.cursor == el->el_line.buffer)
	return CC_ERROR;

    oldc = el->el_line.cursor;
    /* does a bounds check */
    cp = c__prev_word(el->el_line.cursor, el->el_line.buffer, 
		      el->el_state.argument, ce__isword);	

    c_insert(el, oldc - cp);
    for (dp = oldc; cp < oldc && dp < el->el_line.lastchar; cp++)
	*dp++ = *cp;

    el->el_line.cursor = dp;		/* put cursor at end */

    return CC_REFRESH;
}


/* em_inc_search_next():
 *	Emacs incremental next search
 */
protected el_action_t
/*ARGSUSED*/
em_inc_search_next(el, c)
    EditLine *el;
    int c;
{
    el->el_search.patlen = 0;
    return ce_inc_search(el, ED_SEARCH_NEXT_HISTORY);
}


/* em_inc_search_prev():
 *	Emacs incremental reverse search
 */
protected el_action_t
/*ARGSUSED*/
em_inc_search_prev(el, c)
    EditLine *el;
    int c;
{
    el->el_search.patlen = 0;
    return ce_inc_search(el, ED_SEARCH_PREV_HISTORY);
}
E 1
