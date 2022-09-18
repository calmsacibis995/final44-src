h36005
s 00002/00002/00090
d D 8.1 93/06/04 16:52:41 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00092
d D 5.4 92/07/16 13:58:19 marc 4 3
c import tty line editing chars (actually, this version isn't quite right yet, but keith needs a checked in copy).
e
s 00022/00001/00070
d D 5.3 92/07/03 00:24:01 christos 3 2
c Up-to-date with cornell's last RCS version
e
s 00001/00001/00070
d D 5.2 92/06/22 18:24:06 marc 2 1
c merge editline.h and history.h
e
s 00071/00000/00000
d D 5.1 92/06/22 18:08:40 bostic 1 0
c date and time created 92/06/22 18:08:40 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Christos Zoulas of Cornell University.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * el.term.h: Termcap header
 */
#ifndef _h_el_term
#define _h_el_term

D 2
#include "editline.h"
E 2
I 2
#include "histedit.h"
E 2

I 3
typedef struct {	/* Symbolic function key bindings	*/
    char       *name;	/* name of the key			*/
    int     	key;	/* Index in termcap table		*/
    key_value_t fun;	/* Function bound to it			*/
    int	        type;	/* Type of function			*/
} fkey_t;

E 3
typedef struct {
    coord_t t_size;			/* # lines and cols	*/
    bool_t  t_flags;
#define TERM_CAN_INSERT		0x01	/* Has insert cap	*/
#define TERM_CAN_DELETE		0x02	/* Has delete cap	*/
#define TERM_CAN_CEOL		0x04	/* Has CEOL cap		*/
#define TERM_CAN_TAB		0x08	/* Can use tabs		*/
#define TERM_CAN_ME		0x10	/* Can turn all attrs.	*/
#define TERM_CAN_UP		0x20	/* Can move up		*/
#define TERM_HAS_META		0x40	/* Has a meta key	*/
    char   *t_buf;			/* Termcap buffer	*/
    int	    t_loc;			/* location used	*/
    char  **t_str;			/* termcap strings	*/
    int	   *t_val;			/* termcap values	*/
    char   *t_cap;			/* Termcap buffer	*/
I 3
    fkey_t *t_fkey;			/* Array of keys	*/
E 3
} el_term_t;

I 3
/*
 * fKey indexes
 */
#define A_K_DN		0
#define A_K_UP		1
#define A_K_LT		2
#define A_K_RT		3
#define A_K_NKEYS	4
E 3

protected void term_move_to_line	__P((EditLine *, int));
protected void term_move_to_char	__P((EditLine *, int));
protected void term_clear_EOL		__P((EditLine *, int));
protected void term_overwrite		__P((EditLine *, char *, int));
protected void term_insertwrite		__P((EditLine *, char *, int));
protected void term_deletechars		__P((EditLine *, int));
protected void term_clear_screen	__P((EditLine *));
protected void term_beep		__P((EditLine *));
protected void term_change_size		__P((EditLine *, int, int));
protected int  term_get_size		__P((EditLine *, int *, int *));
protected int  term_init		__P((EditLine *));
D 3
protected void term_bind_arrows		__P((EditLine *));
E 3
I 3
protected void term_bind_arrow		__P((EditLine *));
protected void term_print_arrow		__P((EditLine *, char *));
protected int  term_clear_arrow		__P((EditLine *, char *));
protected int  term_set_arrow		__P((EditLine *, char *, 
					     key_value_t *, int));
E 3
protected void term_end			__P((EditLine *));
I 3
protected int  term_set			__P((EditLine *, char *));
E 3
protected int  term_settc		__P((EditLine *, int, char **));
protected int  term_telltc		__P((EditLine *, int, char **));
protected int  term_echotc		__P((EditLine *, int, char **));

protected void term__putc		__P((int));
protected void term__flush		__P((void));

/*
 * Easy access macros
 */
#define EL_FLAGS	(el)->el_term.t_flags

#define EL_CAN_INSERT	(EL_FLAGS & TERM_CAN_INSERT)
#define EL_CAN_DELETE	(EL_FLAGS & TERM_CAN_DELETE)
#define EL_CAN_CEOL	(EL_FLAGS & TERM_CAN_CEOL)
#define EL_CAN_TAB	(EL_FLAGS & TERM_CAN_TAB)
#define EL_CAN_ME	(EL_FLAGS & TERM_CAN_ME)
#define EL_HAS_META	(EL_FLAGS & TERM_HAS_META)

#endif /* _h_el_term */
E 1
