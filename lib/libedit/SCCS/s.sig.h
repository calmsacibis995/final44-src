h45124
s 00002/00002/00042
d D 8.1 93/06/04 16:52:17 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00044
d D 5.3 92/07/03 00:23:58 christos 3 2
c Up-to-date with cornell's last RCS version
e
s 00001/00001/00043
d D 5.2 92/06/22 18:24:05 marc 2 1
c merge editline.h and history.h
e
s 00044/00000/00000
d D 5.1 92/06/22 18:08:37 bostic 1 0
c date and time created 92/06/22 18:08:37 by bostic
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
 * el.sig.h: Signal handling functions
 */
#ifndef _h_el_sig
#define _h_el_sig

#include <signal.h>

D 2
#include "editline.h"
E 2
I 2
#include "histedit.h"
E 2

/*
 * Define here all the signals we are going to handle
 * The _DO macro is used to iterate in the source code
 */
#define ALLSIGS 	\
    _DO(SIGINT)		\
    _DO(SIGTSTP)	\
    _DO(SIGSTOP)	\
    _DO(SIGQUIT)	\
    _DO(SIGHUP)		\
    _DO(SIGTERM)	\
    _DO(SIGCONT)	\
    _DO(SIGWINCH)

typedef sig_t *el_signal_t;

protected void	sig_end		__P((EditLine*));
protected int	sig_init	__P((EditLine*));
protected void	sig_set		__P((EditLine*));
protected void	sig_clr		__P((EditLine*));

#endif /* _h_el_sig */
E 1
