h16539
s 00002/00002/00054
d D 8.1 93/06/05 11:03:57 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00056
d D 5.1 92/07/13 15:47:29 pendry 3 2
c move to rev 5
e
s 00001/00001/00055
d D 1.2 92/07/13 15:46:02 pendry 2 1
c portal.h moved
e
s 00056/00000/00000
d D 1.1 92/07/09 14:47:43 pendry 1 0
c date and time created 92/07/09 14:47:43 by pendry
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 * All rights reserved.
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * $Id: portald.h,v 1.1 1992/05/25 21:43:09 jsp Exp jsp $
 */

#include <sys/cdefs.h>
D 2
#include <portal/portal.h>
E 2
I 2
#include <miscfs/portal/portal.h>
E 2

/*
 * Meta-chars in an RE.  Paths in the config file containing
 * any of these characters will be matched using regexec, other
 * paths will be prefix-matched.
 */
#define RE_CHARS ".|()[]*+?\\^$"

typedef struct qelem qelem;

struct qelem {
	qelem *q_forw;
	qelem *q_back;
};

typedef struct provider provider;
struct provider {
	char *pr_match;
	int (*pr_func) __P((struct portal_cred *,
				char *key, char **v, int so, int *fdp));
};
extern provider providers[];

/*
 * Portal providers
 */
extern int portal_exec __P((struct portal_cred *,
				char *key, char **v, int so, int *fdp));
extern int portal_file __P((struct portal_cred *,
				char *key, char **v, int so, int *fdp));
extern int portal_tcp __P((struct portal_cred *,
				char *key, char **v, int so, int *fdp));

/*
 * Global functions
 */
extern void activate __P((qelem *q, int so));
extern char **conf_match __P((qelem *q, char *key));
extern void conf_read __P((qelem *q, char *conf));
E 1
