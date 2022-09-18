h10189
s 00002/00002/00101
d D 8.1 93/06/04 16:51:10 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00102
d D 5.5 92/07/18 18:03:48 christos 5 4
c Fixed regexp search, and tty chars inheritance.
e
s 00001/00001/00102
d D 5.4 92/07/16 11:35:40 marc 4 3
c ANCHOR broken
e
s 00000/00003/00103
d D 5.3 92/07/03 14:03:09 christos 3 2
c Removed #ifdef sun
e
s 00001/00001/00105
d D 5.2 92/07/03 00:23:41 christos 2 1
c Up-to-date with cornell's last RCS version
e
s 00106/00000/00000
d D 5.1 92/06/22 18:08:14 bostic 1 0
c date and time created 92/06/22 18:08:14 by bostic
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Christos Zoulas of Cornell University.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * el.h: Internal structures.
 */
#ifndef _h_el
#define _h_el
/*
 * Local defaults
 */
#define KSHVI
#define VIDEFAULT
D 4
#define ANCHOR
E 4
I 4
D 5
/* (XXX - broken) #define ANCHOR*/
E 5
I 5
#define ANCHOR
E 5
E 4

#include <stdio.h>
D 3
#ifdef sun
#include <malloc.h>
#endif
E 3
#include <sys/types.h>

#define EL_BUFSIZ	1024		/* Maximum line size		*/

#define HANDLE_SIGNALS	1

typedef int bool_t;			/* True or not			*/

typedef unsigned char el_action_t;	/* Index to command array	*/

typedef struct coord_t {		/* Position on the screen	*/
    int h, v;
} coord_t;

typedef struct el_line_t {
    char *buffer, 			/* Input line 			*/
	 *cursor, 			/* Cursor position 		*/
	 *lastchar,			/* Last character 		*/
	 *limit;			/* Max position			*/
} el_line_t;

/*
 * Editor state
 */
typedef struct el_state_t {
    int 	inputmode;		/* What mode are we in? 	*/
    int 	doingarg;		/* Are we getting an argument?	*/
    int	        argument;		/* Numeric argument 		*/
    int		metanext;		/* Is the next char a meta char */
    el_action_t lastcmd;		/* Previous command		*/
} el_state_t;

/*
 * Until we come up with something better...
 */
#define el_malloc(a)	malloc(a)
#define el_realloc(a,b)	realloc(a, b)
#define el_free(a)	free(a)

#include "tty.h"
#include "prompt.h"
I 2
#include "key.h"
E 2
#include "term.h"
#include "refresh.h"
#include "chared.h"
#include "common.h"
#include "search.h"
#include "hist.h"
D 2
#include "key.h"
E 2
#include "map.h"
#include "parse.h"
#include "sig.h"
#include "help.h"

struct editline {
    char	 *el_prog;	/* the program name 			*/
    FILE         *el_outfile;	/* Stdio stuff				*/
    FILE         *el_errfile;	/* Stdio stuff				*/
    int           el_infd;	/* Input file descriptor		*/
    int		  el_flags;	/* Various flags.			*/
    coord_t       el_cursor;	/* Cursor location			*/
    char        **el_display, 	/* Real screen image = what is there	*/
	        **el_vdisplay;	/* Virtual screen image = what we see	*/

    el_line_t     el_line;	/* The current line information		*/
    el_state_t	  el_state;	/* Current editor state			*/
    el_term_t     el_term;	/* Terminal dependent stuff		*/
    el_tty_t	  el_tty;	/* Tty dependent stuff			*/
    el_refresh_t  el_refresh;	/* Refresh stuff			*/
    el_prompt_t   el_prompt;	/* Prompt stuff				*/
    el_chared_t	  el_chared;	/* Characted editor stuff		*/
    el_map_t	  el_map;	/* Key mapping stuff			*/
    el_key_t	  el_key;	/* Key binding stuff			*/
    el_history_t  el_history;	/* History stuff			*/
    el_search_t	  el_search;	/* Search stuff				*/
    el_signal_t	  el_signal;	/* Signal handling stuff		*/
};

#endif /* _h_el */
E 1
