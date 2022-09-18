h31836
s 00002/00002/00026
d D 8.1 93/06/09 21:42:41 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00006/00021
d D 7.5 91/04/17 17:38:10 bostic 7 6
c new copyright; att/bsd/shared
e
s 00001/00001/00026
d D 7.4 85/06/07 18:19:09 bloom 6 5
c fix sccsid and copyright for xstr
e
s 00010/00001/00017
d D 7.3 85/05/31 13:54:12 dist 5 3
c Add copyright
e
s 00010/00000/00019
d D 1.1.1.1 85/05/31 11:58:56 dist 4 1
c Add copyright
e
s 00001/00003/00017
d D 7.2 81/07/26 20:02:45 mark 3 2
c fixes for 3b
e
s 00001/00000/00019
d D 7.1 81/07/09 22:07:05 mark 2 1
c fixed to work on the 3B
e
s 00019/00000/00000
d D 1.1 81/07/09 22:03:05 mark 1 0
c date and time created 81/07/09 22:03:05 by mark
e
u
U
t
T
I 2
D 5
static char *sccs_id = "%W%	%G%";
E 5
I 5
D 7
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
/*-
D 8
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * %sccs.include.proprietary.c%
E 7
 */

#ifndef lint
D 6
static char sccsid[] = "%W% (Berkeley) %G%";
E 6
I 6
D 7
static char *sccsid = "%W% (Berkeley) %G%";
E 6
#endif not lint
E 7
I 7
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 7

E 5
E 2
I 1
/*
I 4
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint

/*
E 4
 * Provide defs of the global variables.
 * This crock is brought to you by the turkeys
 * who broke Unix on the Bell Labs 3B machine,
 * all in the name of "but that's what the C
 * book says!"
 */

D 3
# define extern 	/* nothing */
E 3
I 3
# define var 	/* nothing */
E 3
# include "ex.h"
# include "ex_argv.h"
# include "ex_re.h"
# include "ex_temp.h"
# include "ex_tty.h"
# include "ex_tune.h"
# include "ex_vars.h"
# include "ex_vis.h"
D 3

short tfile = -1;
E 3
E 1
