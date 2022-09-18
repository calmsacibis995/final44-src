h39965
s 00024/00006/00030
d D 5.2 90/03/11 16:51:02 bostic 2 1
c add Berkeley specific copyright notices
e
s 00036/00000/00000
d D 5.1 90/03/11 16:48:11 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 1
/*
I 2
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * Copyright (c) 1988, 1989 by Adam de Boor
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	%W% (Berkeley) %G%
 */

/*
E 2
 * varargs.h --
 *
 *	Declarations used by procedures to deal gracefully (and
 *	in a portable fashion) with variable numbers of arguments.
 *	See the man page for detailed documentation of what's in here.
D 2
 *
 * Copyright (C) 1985 Regents of the University of California
 * All rights reserved.
 *
 *
 * $Id: varg.h,v 2.1 89/07/03 15:58:38 adam Exp $ SPRITE (Berkeley)
E 2
 */

#ifndef _VARARGS
#define _VARARGS

typedef struct {
    char *vl_first;			/* Pointer to first arg in list. */
    char *vl_next;			/* Pointer to next to traverse. */
} Varg_List;

#define Varg_Decl int Varg_Args

#define Varg_Start(list) \
    (list).vl_first = (char *) &Varg_Args; \
    (list).vl_next = (list).vl_first

#define Varg_Restart(list) \
    (list).vl_next = (list).vl_first

#define Varg_Next(list, type) \
    ((list).vl_next += sizeof(type), \
     ((type *) (list).vl_next)[-1])

#endif _VARARGS
E 1
