h22408
s 00002/00002/00130
d D 8.1 93/06/04 16:51:00 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00130
d D 5.3 92/07/03 00:23:38 christos 3 2
c Up-to-date with cornell's last RCS version
e
s 00001/00001/00130
d D 5.2 92/06/22 18:24:00 marc 2 1
c merge editline.h and history.h
e
s 00131/00000/00000
d D 5.1 92/06/22 18:08:09 bostic 1 0
c date and time created 92/06/22 18:08:09 by bostic
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
 * el.chared.h: Character editor interface
 */
#ifndef _h_el_chared
#define _h_el_chared

#include <ctype.h>
#include <string.h>

D 2
#include "editline.h"
E 2
I 2
#include "histedit.h"
E 2

#define EL_MAXMACRO 10

/*
 * This is a issue of basic "vi" look-and-feel. Defining VI_MOVE works
 * like real vi: i.e. the transition from command<->insert modes moves
 * the cursor.
 *
 * On the other hand we really don't want to move the cursor, because 
 * all the editing commands don't include the character under the cursor.
 * Probably the best fix is to make all the editing commands aware of
 * this fact.
 */
#define VI_MOVE


typedef struct c_macro_t {
    int    level;
    char **macro;
I 3
    char  *nline;
E 3
} c_macro_t;

/* 
 * Undo information for both vi and emacs
 */
typedef struct c_undo_t {
    int   action;
    int   isize;
    int   dsize;
    char *ptr;
    char *buf;
} c_undo_t;

/*
 * Current action information for vi
 */
typedef struct c_vcmd_t {
    int   action;
    char *pos;
    char *ins;
} c_vcmd_t;

/*
 * Kill buffer for emacs
 */
typedef struct c_kill_t {
    char *buf;
    char *last;
    char *mark;
} c_kill_t;

/*
 * Note that we use both data structures because the user can bind
 * commands from both editors!
 */
typedef struct el_chared_t {
    c_undo_t    c_undo;
    c_kill_t    c_kill;
    c_vcmd_t    c_vcmd;
    c_macro_t   c_macro;
} el_chared_t;


#define STReof "^D\b\b"
#define STRQQ  "\"\""

#define isglob(a) (strchr("*[]?", (a)) != NULL)
#define isword(a) (isprint(a))

#define NOP    	  0x00
#define DELETE 	  0x01
#define INSERT 	  0x02
#define CHANGE 	  0x04

#define CHAR_FWD	0
#define CHAR_BACK	1

#define MODE_INSERT	0
#define MODE_REPLACE	1
#define MODE_REPLACE_1	2

I 3
#include "common.h"
E 3
#include "vi.h"
#include "emacs.h"
D 3
#include "common.h"
E 3
#include "search.h"
#include "fcns.h"


protected int   cv__isword	__P((int));
protected void  cv_delfini	__P((EditLine *));
protected char *cv__endword	__P((char *, char *, int));
protected int   ce__isword	__P((int));
protected void  cv_undo		__P((EditLine *, int, int, char *));
protected char *cv_next_word	__P((EditLine*, char *, char *, int, 
				     int (*)(int)));
protected char *cv_prev_word	__P((EditLine*, char *, char *, int,
				     int (*)(int)));
protected char *c__next_word	__P((char *, char *, int, int (*)(int)));
protected char *c__prev_word	__P((char *, char *, int, int (*)(int)));
protected void  c_insert	__P((EditLine *, int));
protected void  c_delbefore	__P((EditLine *, int));
protected void  c_delafter	__P((EditLine *, int));
protected int   c_gets		__P((EditLine *, char *));
protected int   c_hpos		__P((EditLine *));

protected int   ch_init		__P((EditLine *));
protected void  ch_reset	__P((EditLine *));
protected void  ch_end		__P((EditLine *));

#endif /* _h_el_chared */
E 1
