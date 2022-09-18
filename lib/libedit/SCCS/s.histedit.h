h39914
s 00010/00010/00136
d D 8.2 94/01/03 17:53:41 bostic 5 4
c use latest BSDI version of <sys/cdefs.h>, change to __keyword
e
s 00002/00002/00144
d D 8.1 93/06/04 16:51:24 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00021/00015/00125
d D 5.3 92/07/03 00:24:08 christos 3 2
c Up-to-date with cornell's last RCS version
e
s 00038/00001/00102
d D 5.2 92/06/22 18:33:52 marc 2 1
c merge history.h and editline.h into histedit.h
e
s 00103/00000/00000
d D 5.1 92/06/22 18:08:12 bostic 1 0
c date and time created 92/06/22 18:08:12 by bostic
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
D 2
 * editline.h: Line editor interface
E 2
I 2
 * histedit.h: Line editor and history interface.
E 2
 */
#ifndef _h_editline
#define _h_editline

#include <sys/types.h>
#include <stdio.h>

I 2
/*
 * ==== Editing ====
 */
E 2
typedef struct editline EditLine;

/*
 * For user-defined function interface
 */
typedef struct lineinfo {
D 5
    const char *buffer;
    const char *cursor;
    const char *lastchar;
E 5
I 5
    __const char *buffer;
    __const char *cursor;
    __const char *lastchar;
E 5
} LineInfo;

D 3
/*
 * el_set/el_get parameters
 */
#define EL_PROMPT	0
#define EL_FILE		1
#define EL_TERMINAL	2
#define EL_EDITOR	3
#define EL_SIGNAL	4
#define	EL_BIND		5
#define	EL_TELLTC	6
#define	EL_SETTC	7
#define	EL_ECHOTC	8
#define	EL_SETTY	9
#define	EL_ADDFN	10
#define EL_HIST		11
E 3

/*
 * EditLine editor function return codes.
 * For user-defined function interface
 */
#define	CC_NORM		0
#define	CC_NEWLINE	1
#define	CC_EOF		2
#define CC_ARGHACK	3
#define CC_REFRESH	4
#define	CC_CURSOR	5
#define	CC_ERROR	6
#define CC_FATAL	7

/*
 * Initialization, cleanup, and resetting
 */
EditLine	*el_init	__P((const char *, FILE *, FILE *));
void		 el_reset	__P((EditLine *));
void		 el_end		__P((EditLine *));


/*
 * Get a line, a character or push a string back in the input queue
 */
D 5
const char      *el_gets	__P((EditLine *, int *));
E 5
I 5
__const char    *el_gets	__P((EditLine *, int *));
E 5
int		 el_getc	__P((EditLine *, char *));
void		 el_push	__P((EditLine *, const char *));

/*
 * High level function internals control
 * Parses argc, argv array and executes builtin editline commands
 */
int		 el_parse	__P((EditLine *, int, char **)); 

/*
 * Low level editline access function
 */
int 		 el_set		__P((EditLine *, int, ...));
I 3

/*
 * el_set/el_get parameters
 */
#define EL_PROMPT	0	/* , el_pfunc_t);		*/
#define EL_TERMINAL	1	/* , const char *);		*/
#define EL_EDITOR	2	/* , const char *);		*/
#define EL_SIGNAL	3	/* , int);			*/
#define	EL_BIND		4	/* , const char *, ..., NULL);	*/
#define	EL_TELLTC	5	/* , const char *, ..., NULL);	*/
#define	EL_SETTC	6	/* , const char *, ..., NULL);	*/
#define	EL_ECHOTC	7	/* , const char *, ..., NULL);	*/
#define	EL_SETTY	8	/* , const char *, ..., NULL);	*/
#define	EL_ADDFN	9	/* , const char *, const char *	*/
				/* , el_func_t);		*/
#define EL_HIST		10	/* , hist_fun_t, const char *);	*/

/*
 * Source named file or $PWD/.editrc or $HOME/.editrc
 */
int		el_source	__P((EditLine *, const char *));
E 3

/*
 * Must be called when the terminal changes size; If EL_SIGNAL
 * is set this is done automatically otherwise it is the responsibility
 * of the application
 */
void		 el_resize	__P((EditLine *));


/*
 * User-defined function interface.
 */
D 5
const LineInfo	*el_line	__P((EditLine *));
int   		 el_insertstr	__P((EditLine *, char *));
void		 el_deletestr	__P((EditLine *, int));
E 5
I 5
__const LineInfo *el_line	__P((EditLine *));
int   		  el_insertstr	__P((EditLine *, char *));
void		  el_deletestr	__P((EditLine *, int));
E 5
I 2

/*
 * ==== History ====
 */

typedef struct history History;

typedef struct HistEvent {
D 5
    int 	num;
    const char* str;
E 5
I 5
    int 	  num;
    __const char *str;
E 5
} HistEvent;

/*
 * History access functions.
 */
History *		history_init	__P((void));
void 			history_end	__P((History *));

D 5
const HistEvent *	history		__P((History *, int, ...));
E 5
I 5
__const HistEvent *	history		__P((History *, int, ...));
E 5

#define H_FUNC		 0	/* , UTSL		*/
#define H_EVENT		 1	/* , const int);	*/
#define H_FIRST		 2	/* , void);		*/
#define H_LAST		 3	/* , void);		*/
#define H_PREV		 4	/* , void);		*/
#define H_NEXT		 5	/* , void);		*/
#define H_CURR		 6	/* , void);		*/
#define H_ADD		 7	/* , const char*);	*/
#define H_ENTER		 8	/* , const char*);	*/
#define H_END		 9	/* , void);		*/
#define H_NEXT_STR	10	/* , const char*);	*/
#define H_PREV_STR	11	/* , const char*);	*/
#define H_NEXT_EVENT	12	/* , const int);	*/
#define H_PREV_EVENT	13	/* , const int);	*/
E 2

#endif /* _h_editline */
E 1
